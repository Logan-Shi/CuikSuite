#include "dynamics.h"

#include "error.h"
#include "random.h"
#include "samples.h"
#include "sa.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

/* Workaround to avoid repeated complex conditions inside the code */
#ifndef _OPENMP
  #if (DEBUG_HandC)
    #define omp_get_thread_num() 0
    #define omp_in_parallel() FALSE
  #endif
#endif

/** 
   \file dynamics.c
   \brief Implementation of the dynamic-related functions.

   Implementation of the dynamic-related functions used to
   implement path planning with differential constraints.
*/

/** 
   \brief Evaluates the position Jacobian.

   Evaluates the position Jacobian. Only the independent equations are relevant.

   \param p The position variables.
   \param x The full state.
   \param epsilon Numerical accuracy.
   \param hasIE If the independent equations are already computed.
   \param c The chart.
   \param ds The dynamic space.
*/
void GetPositionJacobian(double *p,double *x,double epsilon,boolean hasIE,Tchart *c,TDynamicSpace *ds);

/** 
   \brief Computes the acceleration.

   Given a dynamic space with all the relevant dynamic information, we
   compute the acceleration at a given state.

   \param pr The set of parameters.
   \param hasIE TRUE if the independent equations in \e ds are already computed.
   \param x The state (including both position and velocity).
   \param u The action (forces, moments) to apply.
   \param c The current chart. Used to obtain the basis of the Jacobian (if possible).
   \param fullJ The Jacobian of the full system (i.e., the system including both
                position and velocity equations) can be easily obtained as a side
                product of the acceleration computation. If this pointer is not NULL
                it provides space where to store this Jacobian. This is exploited in
                \ref NextDynamicState where the acceleration and the Jacobian of the
                full system are necessary.
   \param ds The dynamic information.
*/
void ComputeAcceleration(Tparameters *pr,boolean hasIE,double *x,double *u,
			 Tchart *c,double *fullJ,TDynamicSpace *ds);

/** 
   \brief Constant part of the projection residue

   Computes the constant part of the projection residue. Used in the Broyden's before
   entering the iteration to find the solution.

   NOTE: This assumes \ref ComputeAcceleration has been called before with the current
   state (not passed as a parameter since all we need from it is the acceleration, stored
   as ds->g).

   \param ds The dynamic space with the acceleration.
*/
void DynamicStepCtResidue(TDynamicSpace *ds);

/** 
   \brief Constant part of the projection residue

   Computes the constant part of Broyden's residue.

   NOTE: This assumes \ref ComputeAcceleration has been called before with \e x (so
   that the acceleration is for \e x is included in \e ds) and that the constant
   part of the projection error is also precomputed (and stored in \e ds) calling
   \e DynamicStepCtResidue

   \param pr The set of parameters.
   \param h The integration step.
   \param yn Parameters in the chart of the previous point.
   \param x The current state and also the state used in the last call to \e ComputeAcceleration.
   \param c The current chart.
   \param ds The dynamic space with the acceleration at \e x.

   \return The norm of the residue.
*/
double DynamicStepResidue(Tparameters *pr,double h,
			  double *yn,double *x,Tchart *c,TDynamicSpace *ds);

/** 
   \brief Defines a permutation matrix.

   Defines a permutation matrix to select particular actions in the
   inverse dynamics.

   \param ds The dynamic space.
*/
void EvaluatePermutation(TDynamicSpace *ds);

/** 
   \brief Validades a dynamic state.

   Checks if the the dynamic state is valid. For instance if the contact
   forces are the required ones. For instance, in the cable-driven robot
   ensures that the cables are always in tension.

   This is used when computing the next dynamic step.

   This assumes that ComputeAcceleration has been just used
   to update 'ds'. This is the case at the end of \ref NextDynamicState
   which is wehre we use this function right now.

   \param negLag TRUE if Lagrange multipliers should be negative.
   \param ds The dynamic information.

   \return TRUE if the state is valid.
*/
boolean ValidState(boolean negLag,TDynamicSpace *ds);

/** 
   \brief Initializes data requred by the HandC.

   Initializes the data fields in \e ds necessary to compute
   the H and C (see \ref HandC).
 
   \todo Extend the HandC procedure to deal with 

   \param pr The set of paremeters.
   \param wo The world structure (with links, joints, etc).
   \param ds The dynamic space to initialize.
*/
void InitHandC(Tparameters *pr,Tworld *wo,TDynamicSpace *ds);

/** 
   \brief Computes the function, the Jacobian and the Hessian.

   Computes the function, the Jacobian and the Hessian re-using data computed in HandC.
   
   \param pr The set of parameters.
   \param x The state.
   \param computeEq if true we compute the equations.
   \param computeHpv If true we compute the Hessian velocity matrix.
   \param ds The dynamic space with auxiliary data.
*/
void ComputeHandC_FJH(Tparameters *pr,double *x,boolean computeEq,boolean computeHpv,TDynamicSpace *ds);

/** 
   \brief Apply the external forces to the dynamic computations.

   Auxiliary function of \ref HandC that applies the external forces to the computation
   of C.

   \param pr The set of parameters.
   \param x The state.
   \param ds The dynamic space with auxiliary data.
*/
void ApplyExternalForces(Tparameters *pr,double *x,TDynamicSpace *ds);

/** 
   \brief Auxiliary function of \ref HandC.

   Compute the C term of HandC

   \param x The state.
   \param u The action.
   \param C The space for C
   \param ds The dynamic space information
*/
void ComputeC(double *x,double *u,double *C,TDynamicSpace *ds);

/** 
   \brief Auxiliary function of \ref HandC.

   Compute the H term of HandC

   \param x The state.
   \param H The space for C
   \param ds The dynamic space information
*/
void ComputeH(double *x,double *H,TDynamicSpace *ds);


/** 
   \brief H and C function.

   This replicates the HandC function in the code by
   <a href="http://royfeatherstone.org/spatial">Featherstone</a>.
   The only difference is that our \e C includes the action, thus,
   it is tau-C in Featherstone code.

   \param pr The set of parameters.
   \param x The state.
   \param u The action.
   \param H The mass matrix to computed.
   \param C The action vector to comptute.
   \param computeEq if true we compute the equations.
   \param computeHpv If true we compute the Hessian velocity matrix.
   \param ds The dynamic space with auxiliary data.
*/
void HandC(Tparameters *pr,double *x,double *u,double *H,double *C,boolean computeEq,boolean computeHpv,TDynamicSpace *ds);

/** 
   \brief Destructor.

   Deletes the data allocated with \ref InitHandC.

   \param ds The dynamic space with the fields to delete.
*/
void DeleteHandC(TDynamicSpace *ds);

/** 
   \brief Auxiliary function for \ref LQRComputePolicy.

   Computes the derivative of 'r' on a given point. This is used to
   integrate 'r' possibly with different methods (Euler, RK4,...)

   The output is stored in ds->dr_LQR.

   \param r The point.
   \param mA Matrix A of the dynamic linearization.
   \param vc Free term of the dynamic linearization.
   \param ds The dynamic space.
*/
void dr(double *r,double *mA,double *vc,TDynamicSpace *ds);

/** 
   \brief Auxiliary function for \ref LQRComputePolicy.

   Computes the derivative of 'G' on a given point. This is used to
   integrate 'G' possibly with different methods (Euler, RK4,...)

   The output is stored in ds->dG_LQR.

   \param G The point.
   \param mA Matrix A of the dynamic linearization.
   \param BiRBt Another term of the dynamic linearization.
   \param ds The dynamic space.
*/
void dG(double *G,double *mA,double *BiRBt,TDynamicSpace *ds);

/** 
   \brief Auxiliary function for \ref LQRComputePolicy.

   Computes the derivative of G in terms of time. This is used as 
   for an alternative way to compute G (as an integration on
   time instead than an integration over G).

   The output is stored in ds->dG_LQR.

   \param mA Matrix A of the dynamic linearization.
   \param t The time.
   \param BiRBt Another term of the dynamic linearization.
   \param eA Space to store expm(t*A)
   \param ds The dynamic space.
*/

void dGt(double *mA,double t,double *BiRBt,double *eA,TDynamicSpace *ds);

/* --------------------------------------------------------------------------------------------------------
   --------------------------------------------------------------------------------------------------------
   private dynamic methods
   --------------------------------------------------------------------------------------------------------
   --------------------------------------------------------------------------------------------------------*/
void GetPositionJacobian(double *p,double *x,double epsilon,boolean hasIE,Tchart *c,TDynamicSpace *ds)
{
  unsigned int i;

  /* If the independent equations are not identified (hasIE=TRUE), we use the independent set
     of the provided chart, if any */  
  if ((!hasIE)&&(c!=NULL))
    {
      memcpy(ds->bJ,GetChartJacobianBasis(c),sizeof(boolean)*ds->ne);
      
      for(i=0;i<ds->npe;i++)
	ds->bJp[i]=ds->bJ[ds->ndxPE[i]];
      
      hasIE=TRUE;
    }
  
  if (hasIE)
    {
      if (ds->nJp!=NULL)
	{
	  EvaluateTransposedNJacobianSubSetInVector(p,ds->nipe,ds->bJp,ds->Jp,ds->nJp);
	  //PrintMatrix(stderr,"nJt",ds->npv,ds->nipe,ds->Jp);
	}
      else
	{
	  //PrintMatrix(stderr,"nJt",ds->npv,ds->nipe,ds->Jp);
	  EvaluateTransposedJacobianSubSetInVector(p,ds->bJp,ds->npv,ds->nipe,ds->Jp,&(ds->sJp));
	  //PrintMatrix(stderr,"sJt",ds->npv,ds->nipe,ds->Jp);
	}
    }
  else
    {
      boolean singular;

      /* The procedure next is not very efficient (we evaluate the Jacobian and not
	 the faster numeric Jacobian and we have to determine the base of the full
	 Jacobian) but it is not usually executed. */
      EvaluateTransposedJacobianInVector(x,ds->nv,ds->ne,ds->cJ,ds->sJ);

      /* save the Jacobian evaluation because FindIndependentRows re-writes the input buffer */
      memcpy(ds->J,ds->cJ,sizeof(double)*ds->nv*ds->ne);

      #if (DEBUG_DYNAMICS>3)
        /* The Jacobian (not trasposed) */
        PrintTMatrix(stderr,"      J",ds->nv,ds->ne,ds->J);
      #endif

      /* free bJ since they will be allocated next (if necessary) */
      free(ds->bJ);
      FindIndependentRows(ds->ne,ds->nv,ds->cJ,ds->dof,epsilon,&singular,&(ds->bJ));
      if (singular)
	Error("Singular point in GetPositionJacobian");
      
      for(i=0;i<ds->npe;i++)
	ds->bJp[i]=ds->bJ[ds->ndxPE[i]];
      
      /* Get a submatrix (rows and columns) from a matrix!!!! (the position equations and variables) */	    
      SelectMatrixRows(ds->pVars,ds->nv,ds->ne,ds->J);
      VectorAnd(ds->ne,ds->pEqs,ds->bJ,ds->selEqs);
      SelectMatrixColumns(ds->selEqs,ds->npv,ds->ne,ds->J);
      memcpy(ds->Jp,ds->J,ds->nipe*ds->npv*sizeof(double));
    }
}

void ComputeAcceleration(Tparameters *pr,boolean hasIE,double *x,double *u,
			 Tchart *c,double *fullJ,TDynamicSpace *ds)
{
  unsigned int i;
  #if ((!HandC_FJH)||(DEBUG_HandC_FJH))
    double epsilon;

    epsilon=GetParameter(CT_EPSILON,pr);
  #endif
  
  /* Direct access to position and velocity (just for convinence) */
  for(i=0;i<ds->npv;i++)
    {
      ds->pos[i]=x[ds->ndxPV[i]];
      ds->vel[i]=x[ds->ndxVV[i]];
    }
  
  #if (DEBUG_DYNAMICS>2)
    if (hasIE)
      fprintf(stderr,"         Computing acceleration =================================================================\n");
    else
      fprintf(stderr,"         Computing acceleration =================================================================\n");
    PrintVector(stderr,"           x",ds->nv,x);
  #endif
  
  /* Fill in the LS matrix */ 
  HandC(pr,x,u,ds->Mm,ds->Qa,TRUE,(fullJ!=NULL),ds);
  
  #if (DEBUG_HandC)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	/** -------------------------------------------------------------------------------------------------- */
	fprintf(stderr,"              HandC =================================================================\n");
	if (omp_in_parallel())
	  fprintf(stderr,"                Thread: %u\n",omp_get_thread_num());
	PrintVector(stderr,"                x",ds->nv,x);
	if (u!=NULL)
	  PrintVector(stderr,"                u",ds->da,u);
	PrintMatrix(stderr,"                M",ds->npv,ds->npv,ds->Mm);
	PrintVector(stderr,"                Qa",ds->npv,ds->Qa);
	/** -------------------------------------------------------------------------------------------------- */
      }
  #endif
    
  /*Initial position of M is: row = 0 col=nieq (it was flipped) */
  memset(ds->mA,0,sizeof(double)*ds->lsSize*ds->lsSize);
  SubMatrixFromMatrix(ds->npv,ds->npv,ds->Mm,0,ds->nipe,ds->lsSize,ds->lsSize,ds->mA);
  if (ds->nipe>0)
    {
      #if (HandC_FJH)
        /* Here Jp contains the position Jacobian (not transposed) */
        #if (DEBUG_HandC_FJH)
          // For debug (prints and re-computes using the standard, well-tested procedure)
          // To check this in Matlab execute
          //    L=J1'\J2';  % To find the linear relation between J1 and J2
          //    EJ=J1'*L-J2';  % Error in J
          PrintMatrix(stderr,"J1",ds->nipe,ds->npv,ds->Jp);
	  memcpy(ds->Jp2,ds->Jp,ds->nipe*ds->npv*sizeof(double)); /* Save the Jacobian computed by HandC */
	  /* If we do not have a chart, GetPositionJacobian will compute the independent equations overwritting
	     the full jacobian computed in HandC -> error! */
	  if (c==NULL)
	    Error("We need a chart here!");
	  GetPositionJacobian(ds->pos,x,epsilon,FALSE,c,ds); /* Compute with the standard methods */
	  PrintTMatrix(stderr,"J2",ds->npv,ds->nipe,ds->Jp); 
	  memcpy(ds->Jp,ds->Jp2,ds->nipe*ds->npv*sizeof(double));/* Recover the HandC Jacobian */
	#endif
	/* HandC computed the Jacobian, Just store it in the mA matrix. */
	SubMatrixFromTMatrix(ds->nipe,ds->npv,ds->Jp,0,0,ds->lsSize,ds->lsSize,ds->mA);
	SubMatrixFromMatrix(ds->nipe,ds->npv,ds->Jp,ds->npv,ds->nipe,ds->lsSize,ds->lsSize,ds->mA);
      #else
	/* This computes the TRANSPOSED position Jacobian */
        GetPositionJacobian(ds->pos,x,epsilon,hasIE,c,ds); /* Only independent equations */
	
	/* If the independent equations where not identified at the beginning of ComputeAcceleration
	   GetPositionJacobian will take care of identifying them (init ds->bJp) */
	SubMatrixFromMatrix(ds->npv,ds->nipe,ds->Jp,0,0,ds->lsSize,ds->lsSize,ds->mA);
	SubMatrixFromTMatrix(ds->npv,ds->nipe,ds->Jp,ds->npv,ds->nipe,ds->lsSize,ds->lsSize,ds->mA);	
      #endif
      
      /* gamma = -Phi_qq*v*v (= - Hessian*v*v) */
      #if (HandC_FJH)
	/* Code for debug: compare gamma from HandC with gamma compute in the traditional way */

	#if (DEBUG_HandC_FJH)
	  // Debug information (complementary to the Jacobian one).
	  // To test in matlab execute (requires the L computed using the Jacobian):
          //    EH=Hpv1'*L-Hpv2'; % Error in Hpv
          //    Eg=gamma1*L-gamma2;  % Error in gamma
          //    Eg1=Hpv1*qd'-gamma1'; % Error in gamma1
	  PrintVector(stderr,"qd",ds->npv,&(x[ds->npv]));
	  PrintVector(stderr,"gamma1",ds->nipe,ds->gamma);
	  if (fullJ!=NULL)
	    PrintMatrix(stderr,"Hpv1",ds->nipe,ds->npv,ds->Hpv);
	  
	  if (ds->nHp!=NULL)
	    EvaluateNHessianVector2(x,ds->vel,ds->nipe,ds->bJp,ds->Hpv2,ds->gamma2,ds->nHp);
	  else
	    EvaluateHessianVector2(x,ds->vel,ds->nipe,ds->bJp,ds->Hp,ds->Hpv2,ds->gamma2,&(ds->sHp));
	  PrintVector(stderr,"gamma2",ds->nipe,ds->gamma2);
	  if (fullJ!=NULL)
	    PrintMatrix(stderr,"Hpv2",ds->nipe,ds->npv,ds->Hpv2);
	#endif
      #else
        if (ds->nHp!=NULL)
   	  EvaluateNHessianVector2(x,ds->vel,ds->nipe,ds->bJp,ds->Hpv,ds->gamma,ds->nHp);
	else
	  {
	    //PrintVector(stderr,"nH",ds->nipe,ds->gamma);
	    EvaluateHessianVector2(x,ds->vel,ds->nipe,ds->bJp,ds->Hp,ds->Hpv,ds->gamma,&(ds->sHp));
	    //PrintVector(stderr,"sH",ds->nipe,ds->gamma);
	  }
      #endif
      /* Irrespectively of how gamma is computed, we have to change its sign */
      ScaleVector(-1.0,ds->nipe,ds->gamma);

      /* Here we have all the data necessary to define the Jacobian of the full
	 system, if requested */
      if (fullJ!=NULL)
	{
	  memset(fullJ,0,sizeof(double)*ds->nie*ds->nv);
	  
	  if (ds->noe>0)
	    {
	      EvaluateJacobianInVector(x,ds->noe,ds->npv,ds->Jop,&(ds->sJop));
	      EvaluateJacobianInVector(x,ds->noe,ds->nov,ds->Joo,&(ds->sJoo));
	    }
	  
	  #if (HandC_FJH)
	    /* We use a different order of equations because evaluate the equations and the Jacobian
	       and everything inside HandC and not using calls to the basic cuik structures.
	       We arrange equations in this order (position, non-dynamic eqs, velocity)

	       With respect to the variables, we have (position, non-dynamic vars, velocity) */
	    SubMatrixFromMatrix(ds->nipe,ds->npv,ds->Jp,0,0,ds->nie,ds->nv,fullJ);
	    SubMatrixFromMatrix(ds->nipe,ds->npv,ds->Hpv,ds->nipe+ds->noe,0,ds->nie,ds->nv,fullJ);
	    SubMatrixFromMatrix(ds->nipe,ds->npv,ds->Jp,ds->nipe+ds->noe,ds->npv+ds->nov,ds->nie,ds->nv,fullJ);
	    if (ds->noe>0)
	      {
		SubMatrixFromMatrix(ds->noe,ds->npv,ds->Jop,ds->nipe,0,ds->nie,ds->nv,fullJ);
		SubMatrixFromMatrix(ds->noe,ds->nov,ds->Joo,ds->nipe,ds->npv,ds->nie,ds->nv,fullJ);
	      }
	  #else
	    unsigned int kp,kv,ko,k,i,l; /* number of independent position and velocity equations */
	  
	    kp=0;
	    kv=0;
	    ko=0;
	    k=0;
	    for(i=0;i<ds->ne;i++)
	      {
		if (ds->pvEqs[i])
		  {
		    if (ds->pEqs[i])
		      {
			if (ds->bJ[i])
			  {
			    for(l=0;l<ds->npv;l++)
			      {
				fullJ[RC2INDEX(k,ds->ndxPV[l],ds->nie,ds->nv)]=ds->Jp[RC2INDEX(l,kp,ds->npv,ds->nipe)];
			      }
			    //SubMatrixFromSubMatrix(0,kp,ds->npv,1,ds->npv,ds->nipe,ds->Jp,k,0,TRUE,ds->nie,ds->nv,fullJ);
			    kp++;
			    k++;
			  }
		      }
		    else
		      {
			if (ds->bJ[i])
			  {
			    for(l=0;l<ds->npv;l++)
			      {
				fullJ[RC2INDEX(k,ds->ndxPV[l],ds->nie,ds->nv)]=ds->Hpv[RC2INDEX(kv,l,ds->nipe,ds->npv)];
				fullJ[RC2INDEX(k,ds->ndxVV[l],ds->nie,ds->nv)]=ds->Jp[RC2INDEX(l,kv,ds->npv,ds->nipe)];
			      }
			  
			    //SubMatrixFromSubMatrix(kv,0,1,ds->npv,ds->nipe,ds->npv,ds->Hpv,k,0,FALSE,ds->nie,ds->nv,fullJ);	  
			    //SubMatrixFromSubMatrix(0,kv,ds->npv,1,ds->npv,ds->nipe,ds->Jp,k,ds->npv,TRUE,ds->nie,ds->nv,fullJ);
			    kv++;
			    k++;
			  }
		      }
		  }
		else
		  {
		    if (ds->bJ[i])
		      {
			for(l=0;l<ds->npv;l++)
			  fullJ[RC2INDEX(k,ds->ndxPV[l],ds->nie,ds->nv)]=ds->Jop[RC2INDEX(ko,l,ds->noe,ds->npv)];
			for(l=0;l<ds->nov;l++)
			  fullJ[RC2INDEX(k,ds->ndxOV[l],ds->nie,ds->nv)]=ds->Joo[RC2INDEX(ko,l,ds->noe,ds->nov)];

			k++;
		      
			//SubMatrixFromSubMatrix(ko,0,1,ds->npv,ds->noe,ds->npv,ds->Jop,k,0,FALSE,ds->nie,ds->nv,fullJ); 
		      }
		    /* else -> Error!! : all 'other' equations should be independent, between them and w.r.t. postion/velocity equations */
		    ko++;
		  }
	      }
	  #endif
	}
    }
  
  #if (DEBUG_DYNAMICS>3)
    fprintf(stderr,"                Solving for acceleration\n");
    PrintVector(stderr,"                x",ds->nv,x);
  
    /* The matrix in the linear system to compute acceleration */
    PrintMatrix(stderr,"                  A",ds->lsSize,ds->lsSize,ds->mA);

    /* The bottom part of the rhs of the linear system */
    PrintVector(stderr,"                  rhs",ds->lsSize,ds->rhsA);
  #endif

  /* Solve */
  if (LSSolve(&(ds->A)))
    Error("Singular linear system in ComputeAcceleration");

  #if (DEBUG_DYNAMICS>3)
    /* The solution of the linear system */
    PrintVector(stderr,"                  sol",ds->lsSize,ds->solA);
  #endif

  /* here ds->qdd holds the acceleration: assemble (v,qdd)*/
  for(i=0;i<ds->npv;i++)
    {
      ds->g[ds->ndxPV[i]]=ds->vel[i];
      ds->g[ds->ndxVV[i]]=ds->qdd[i];
    }
  if (ds->noe>0)
    {
      if (fullJ==NULL)
	{
	  EvaluateJacobianInVector(x,ds->noe,ds->npv,ds->Jop,&(ds->sJop));
	  EvaluateJacobianInVector(x,ds->noe,ds->nov,ds->Joo,&(ds->sJoo));
	}
      LSSolve(&(ds->Jot));
      MatrixVectorProduct(ds->noe,ds->npv,GetLSSolutionBuffer(&(ds->Jot)),ds->vel,ds->o);
      
      for(i=0;i<ds->nov;i++) /* we have as many 'other' equations as variables nov=noe */
	ds->g[ds->ndxOV[i]]=-ds->o[i];
    }
 
  #if (DEBUG_HandC>0)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	PrintVector(stderr,"           g",ds->nv,ds->g);
      }
  #endif
  #if (DEBUG_DYNAMICS>2)
    /* The top part of the rhs of the linear system */
    PrintVector(stderr,"           g",ds->nv,ds->g);
    if (hasIE)
      fprintf(stderr,"         End computing acceleration =================================================================\n");
    else
      fprintf(stderr,"         End computing acceleration =================================================================\n");
  #endif
}

void DynamicStepCtResidue(TDynamicSpace *ds)
{
  /* Save the current acceleration (acceleration at the previous step) */
  memcpy(ds->gn,ds->g,sizeof(double)*ds->nv);
}

double DynamicStepResidue(Tparameters *pr,double h,
			  double *yn,double *x,Tchart *c,TDynamicSpace *ds)
{   
  #if ((!HandC_FJH)||(DEBUG_HandC_FJH))
    /* If using HandC the system is already evaluated at this point */
    #if (DEBUG_HandC_FJH)
      PrintVector(stderr,"fe_hc",ds->nie,ds->fe);
    #endif
    if (ds->nie>0)
      {
	/* FUNCTION ERROR: Compute the error w.r.t. the manifold  */
	if (ds->nJp!=NULL)
	  {
	    if (ds->noe>0)
	      {
		/* select the independent, non-dynamic (aka 'other') equations (this should be all of them but...) */
		VectorAnd(ds->ne,ds->oEqs,ds->bJ,ds->selEqs);
		CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS(pr,ds->selEqs,x,ds->xa,ds->w);
	      }
	    #if (DEBUG_HandC_FJH)
	      EvaluateSystemFromNJacobian(x,ds->ndxVV,ds->ne,ds->nipe,ds->bJ,ds->bJp,ds->pvEqs,ds->pEqs,ds->xa,ds->fe2,ds->nJp);
	    #else
	      EvaluateSystemFromNJacobian(x,ds->ndxVV,ds->ne,ds->nipe,ds->bJ,ds->bJp,ds->pvEqs,ds->pEqs,ds->xa,ds->fe,ds->nJp);
	    #endif
	  }
	else
	  {
	    //PrintVector(stderr,"nJ",2*ds->nipe,ds->fe);
	    #if (DEBUG_HandC_FJH)
	      CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS(pr,ds->bJ,x,ds->fe2,ds->w);
	    #else
	      CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS(pr,ds->bJ,x,ds->fe,ds->w);
	    #endif
	  }
      }
    #if (DEBUG_HandC_FJH)
      PrintVector(stderr,"fe",ds->nie,ds->fe2);
    #endif
  #endif
  
  /* And the PROJECTION ERROR. The whole projection error is
     U^t * [x - x0 - 0.5 * h * (gn+g) ] - yn

     where gn is stored in \e DynamicStepCtResidue
  */
  /* xa=g+gn */
  SumVector(ds->nv,ds->gn,ds->g,ds->xa);

  /* xa = x - 0.5*h*xa = x - 0.5*h*(gn+g) */
  SumVectorScale(ds->nv,x,-0.5*h,ds->xa,ds->xa);

  /* y = U^t*(xa - x0) = U^t*(x - 0.5*h*(gn+g) - x0) */
  Manifold2Chart(ds->xa,ds->tp,ds->y,c);
  
  /* pe = y - yn = U^t*(x - 0.5*h*(gn+g) - x0) - yn */
  DifferenceVector(2*ds->dof,ds->y,yn,ds->pe);
      
  /* Return the norm of the residue */
  return(Norm(ds->nv,ds->fe));
}

void InitHandC(Tparameters *pr,Tworld *wo,TDynamicSpace *ds)
{
  unsigned int i,j,k,id,op;
  unsigned int ga;
  THTransform preT,postT,postT2,*iFrame,iFrameNew;
  double **iMatrix;
  double *c;
  Tjoint *jo;
  double *F,*IM,*Tmp;
  #if (CUT_AT_LINK)
    unsigned int *splitLink; /* links where we split loops. */
  #endif
  
  #if (DEBUG_HandC>1)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	fprintf(stderr,"------------------------------------------------------------------\n");
	fprintf(stderr,"Init HandC -------------------------------------------------------\n");
	fprintf(stderr,"------------------------------------------------------------------\n");
	fprintf(stderr,"Thread: %u  (%p)\n",omp_get_thread_num(),ds);
      }
  #endif
  
  NEW(c,3,double);  /* center of gravity */
  NEW(F,9,double);  /* Inertia frame */
  NEW(IM,9,double);  /* Inertia matrix */
  NEW(Tmp,9,double);/* F*I (temporal storage) */
  #if (CUT_AT_LINK)
    NEW(splitLink,ds->nl,unsigned int); /* Links where a loops is break */
  #endif
  
  /* We need access to the underlying world structure to deal with
     external forces */
  ds->wo=wo;

  ds->nLoops=NumLoops(wo);
  #if (CUT_AT_LINK)
    /* Note that if nlHC is the same as nl, we cut loops at joints and not at links. In this case
       some joints (i.e., the loop closure joints) are not used in the HandC procedure. 
       In general, we prefer to use all joints. */
    ds->nlHC=ds->nl+ds->nLoops;
  #else
    ds->nlHC=ds->nl;
  #endif
  
  /* Allocate space */

  /* These are constant and pre-computed */
  NEW(ds->cJoint,ds->nLoops,unsigned int);
  ds->bJHC=NULL;
  
  NEW(ds->a_grav,6,double);
  NEW(ds->IM,ds->nlHC,double *);
  NEW(ds->lID,ds->nlHC,unsigned int);
  NEW(ds->oID,ds->nlHC,unsigned int);
  NEW(ds->pLink,ds->nlHC,unsigned int);
  NEW(ds->jID,ds->nlHC,unsigned int);
  NEW(ds->jSgn,ds->nlHC,signed int);
  NEW(ds->j2x,ds->nlHC,unsigned int);
  NEW(ds->njx,ds->nlHC,unsigned int);
  NEW(ds->Xtree,ds->nlHC,double *);
  NEW(ds->iXtreeTr,ds->nlHC,THTransform);
  NEW(ds->closeTr,ds->nLoops,THTransform);
  NEW(ds->S,ds->nlHC,double *);

  /* These are used in each call to HandC */
  NEW(ds->XJ,36,double);
  NEW(ds->vJ,6,double);
  #if (USE_XUPTR)
    NEW(ds->XupTr,ds->nlHC,THTransform);
    NEW(ds->XtreeTr,ds->nlHC,THTransform);
  #endif
  NEW(ds->Xup,ds->nlHC,double *);
  NEW(ds->iXupTr,ds->nlHC,THTransform);
  #if (!USE_HTxSAV)
    NEW(ds->iXa,ds->nlHC,double *);
  #endif
  NEW(ds->iXaTr,ds->nlHC,THTransform);
  NEW(ds->v,ds->nlHC,double *);
  NEW(ds->vxS,6*ds->npv,double);
  if (ds->nipe<6*ds->nLoops)
    {
      NEW(ds->gammaHC,6*ds->nLoops,double);
      NEW(ds->feHC,2*6*ds->nLoops+ds->noe,double);
    }
  else
    {
      ds->gammaHC=ds->gamma;
      ds->feHC=ds->fe;
    }
  NEW(ds->avp,ds->nlHC,double *);
  NEW(ds->fvp,ds->nlHC,double *);
  NEW(ds->fout,ds->nlHC,double *);
  NEW(ds->IC,ds->nlHC,double *);
  NEW(ds->fh,6*6,double); /* In the extreme (Free_Joint) can be 6x6 */
  NEW(ds->dh,6*6,double); /* In the extreme (Free_Joint) can be 6x6 */
  NEW(ds->wr1,6,double);
  NEW(ds->wr2,6,double);
  NEW(ds->auxSAV1,6,double);
  NEW(ds->auxSAV2,6,double);
  NEW(ds->auxSAV3,6,double);
  NEW(ds->auxSAM1,36,double);
  NEW(ds->auxSAM2,36,double);
  ds->nef=0;

  for(i=0;i<ds->nLoops;i++)
    ds->cJoint[i]=GetWorldClosureN(i,wo);
  
  #if (CUT_AT_LINK)
    /* Identify the links that will be used to split the loops */
    for(i=0;i<ds->nl;i++)
      splitLink[i]=1;
    for(i=0;i<ds->nLoops;i++)
      splitLink[JointToID(ds->j[ds->cJoint[i]])]++;
  #endif
  
  for(i=0;i<ds->nlHC;i++)
    {
      /* The constant part (pre-computed) */
      NEW(ds->IM[i],36,double); /* sa matrix */
      NEW(ds->Xtree[i],36,double); /* sa matrix */

      /* The variable part (re-defined at each call of HandC) */
      NEW(ds->S[i],6*6,double); /* sa in the extreme (Free_Joints) can be a 6x6 matrix */
      NEW(ds->Xup[i],36,double); /* sa matrix */
      #if (!USE_HTxSAV)
        NEW(ds->iXa[i],36,double); /* sa matrix */
      #endif
      NEW(ds->v[i],6,double); /* sa vector */
      NEW(ds->avp[i],6,double); /* sa vector */
      NEW(ds->fvp[i],6,double); /* sa vector */
      NEW(ds->fout[i],6,double); /* sa vector */
      NEW(ds->IC[i],36,double); /* sa matrix */
    }

  /* Fill in the constant data */
  /* Set the gravity +/- X/Y/Z */
  memset(ds->a_grav,0,sizeof(double)*6);
  ga=(unsigned int)GetParameter(CT_G_AXIS,pr);
  if (ga>0)
    ds->a_grav[2+(ga>3?ga-3:ga)]=-1.0*(ga>3?-1.0:+1.0)*M_G;

  for(i=0;i<ds->nlHC;i++)
    {
      if (i<ds->nl)
	ds->lID[i]=GetWorldLinkN(i,wo); /* Links in order as they appear in the kinematic tree */
      else
	ds->lID[i]=JointToID(ds->j[ds->cJoint[i-ds->nl]]); /* Virtual link: index of the real link (repeated index!) */
      
      if (ds->lID[i]==NO_UINT)
	{
	  /* The i-th link is a link not actually used in the tree (e.g., a connection link) */
	  ds->pLink[i]=NO_UINT;
	  /* springs introduce external forces */
	  if (IsConnectionSpring(ds->l[i]))
	    ds->nef++; /* number of external forces */
	}
      else
	{
	  /* Loop closure links appear twice in the system. Just keep the fist index */
	  if (i<ds->nl)
	    ds->oID[ds->lID[i]]=i; /* position of link lID[i] in the kinematic tree */
      
	  if ((i==0)&&(ds->lID[i])!=0)
	    Error("Kin-tree does not start at the root?");
      
	  if ((i<ds->nl)&&(ds->lID[i]==0))
	    {
	      /* root node */
	      ds->pLink[0]=NO_UINT; /* no parent */
	      ds->jID[0]=NO_UINT;   /* no joint connecting to parent */
	      ds->j2x[0]=NO_UINT;   /* no variable used in the joint */
	      ds->njx[0]=0;         /* 0 degrees of freedom in the joint */
	  
	      IdentitySAM(ds->Xtree[0]); /* Transfrom from joint to joint */
	      #if (USE_XUPTR)
	        HTransformIdentity(&(ds->XtreeTr[0]));
	      #endif
	      HTransformIdentity(&(ds->iXtreeTr[0]));
	    }
	  else
	    {
	      /* a link which is not the root */
	      if (i<ds->nl)
		op=GetWorldPredLink(ds->lID[i],wo); /* get the parent link (in global ordering!) */
	      else
		op=JointFromID(ds->j[ds->cJoint[i-ds->nl]]); /* parent for virtual link */

	      /* Convert the index to parent to the kinematic tree order. Note that in any case 'op' is < nl ... */
	      ds->pLink[i]=ds->oID[op]; 

	      /* ID of the Joint taking to the link from parent */
	      if (i<ds->nl)
		ds->jID[i]=GetWorldJointTo(ds->lID[i],&(ds->jSgn[i]),wo); /* joint connecting to parent */
	      else
		{
		  ds->jID[i]=ds->cJoint[i-ds->nl];
		  ds->jSgn[i]=+1;
		}

	      jo=ds->j[ds->jID[i]]; /* the joint itself */
      
	      ds->j2x[i]=GetWorldJoint2Dof(ds->jID[i],wo); /* Part of the state representing the joint dof */
	      ds->njx[i]=GetJointDOF(jo); /* number of dof of the joint */
	      
	      /* Init Xtree: transform from one joint to the next (in coordinates of the child) */
	      GetJointPreT(ds->jSgn[i],&preT,jo);   /* recall that this is selected taking into account the orientation of the joint */
	      
	      if (ds->pLink[i]!=0)
		{
		  /* Identifier of the parent link in the kinematic tree */
		  op=ds->pLink[i];
		  
		  jo=ds->j[ds->jID[op]]; /* joint taken to the grand-parent to parent */
		  GetJointPostT(ds->jSgn[op],&postT,jo);

		  #if (DEBUG_HandC>1)
		    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		      {
			fprintf(stderr,"parent link: %u (%u)  joint(gp->p): %u  sg:%d\n",ds->lID[op],op,ds->jID[op],ds->jSgn[op]);
			HTransformPrint(stderr,&postT);
		      }
		  #endif
		  
		  HTransformProduct(&postT,&preT,&preT);
		}
	      
	      /* HandC requires to store the transfrom from child to parent (the inverse of what we just computed) */
	      	      
	      HTransformCopy(&(ds->iXtreeTr[i]),&preT);
	      
	      HTransformInverse(&preT,&preT);
	      #if (USE_XUPTR)
	        HTransformCopy(&(ds->XtreeTr[i]),&preT);
	      #endif
	      HTransform2SAM(&preT,ds->Xtree[i]);
	      
	      if (i>=ds->nl)
		{
		  /* A closure link (duplicated). We need to compute the closure */
		  GetJointPostT(ds->jSgn[i],&postT,ds->j[ds->jID[i]]); /* the closure joint */
		  
		  id=ds->oID[ds->lID[i]]; /* index (in the kinematic tree order) of the first apparition 
					     of the closure (duplicated) link in the kinematic tree */
		  GetJointPostT(ds->jSgn[id],&postT2,ds->j[ds->jID[id]]); /* first joint connecting this 
									     closure link to the three */
		  
		  HTransformInverse(&postT2,&postT2);
		  HTransformProduct(&postT,&postT2,&(ds->closeTr[i-ds->nl]));
		}
	    }

	  /* Set the inertia (not used for the root link but...) */
	  //if ((i==0)||(ds->pLink[i]!=NO_UINT)) /* some links (e.g. connection links) are not in the three */
	  if (ds->lID[i]!=NO_UINT)
	    {
	      iFrame=GetLinkInertialFrame(ds->l[ds->lID[i]]);
	      if (i>0)
		{
		  /* Determine the gravity center w.r.t the joint reference (not link reference) 
		     joint=joint connecting to parent. This is the "new" reference for the link. */
		  jo=ds->j[ds->jID[i]];
		  GetJointPostT(ds->jSgn[i],&postT,jo);
		  HTransformProduct(&postT,iFrame,&iFrameNew);
		}
	      else
		HTransformCopy(&iFrameNew,iFrame);
	      
	      iMatrix=GetLinkInertiaMatrix(ds->l[ds->lID[i]]);

	      /* center of mass (from child to parent) */
	      c[0]=HTransformGetElement(AXIS_X,AXIS_H,&iFrameNew);
	      c[1]=HTransformGetElement(AXIS_Y,AXIS_H,&iFrameNew);
	      c[2]=HTransformGetElement(AXIS_Z,AXIS_H,&iFrameNew);

	      /* rotated inertia matrix 
		 IM: Inertia matrix 
		 F: Inertia frame (rotation part) */
	      for(j=0;j<3;j++)
		{
		  for(k=0;k<3;k++)
		    {
		      IM[RC2INDEX(j,k,3,3)]=iMatrix[j][k];
		      F[RC2INDEX(j,k,3,3)]=HTransformGetElement(j,k,&iFrameNew);
		    }
		}
	      #if (DEBUG_HandC>1)
	        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		  {
		    fprintf(stderr,"i:%u  lID[%u]:%u  oID[%u]:%u- - - - - - - - - - - - \n",
			    i,i,ds->lID[i],ds->lID[i],ds->oID[ds->lID[i]]);
		    if (i>0)
		      fprintf(stderr,"jID:%u   pID: %u - - - - - - - - - - - - - - - - - \n",
			      ds->jID[i],ds->pLink[i]);
		    
		    fprintf(stderr,"c:[%f %f %f]\n",c[0],c[1],c[2]);
		    PrintMatrix(stderr,"F",3,3,F);
		    PrintMatrix(stderr,"I",3,3,IM);
		  }
	      #endif
	  
	      /* (F^-1)'*I*(F^-1) = F*I*F' */
	      MatrixMatrixProduct(3,3,F,3,IM,Tmp);
	      MatrixTMatrixProduct(3,3,Tmp,3,F,IM);

	      mci2rbi(GetLinkMass(ds->l[ds->lID[i]]),c,IM,ds->IM[i]); /* Not used for root */
	      
	      #if (CUT_AT_LINK)
	        /* we split the mass of closure links */
	        if (splitLink[ds->lID[i]]>1)
		  ScaleVector(1.0/(double)splitLink[ds->lID[i]],36,ds->IM[i]);
	      #endif
		
	      #if (DEBUG_HandC>1)
		if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		  {
		    PrintMatrix(stderr,"Xtree",6,6,ds->Xtree[i]);
		    fprintf(stderr,"mass: %f\n",GetLinkMass(ds->l[ds->lID[i]]));
		    PrintMatrix(stderr,"I",6,6,ds->IM[i]);
		  }
	      #endif
	    }
	} 
    }

  /* Pre-defined values for the root. Not actually used in HandC but initialitzed just 
     in case they are used in other functions. */
  #if (!USE_HTxSAV)
    IdentitySAM(ds->iXa[0]);
  #endif
  HTransformIdentity(&(ds->iXaTr[0]));
  memset(ds->v[0],0,sizeof(double)*6);
  memset(ds->avp[0],0,sizeof(double)*6);
  memset(ds->fvp[0],0,sizeof(double)*6);
  
  /* The system is damped if there is any joint with a non-null damping constant */
  ds->damped=FALSE;
  i=0;
  while((!ds->damped)&&(i<ds->nj))
    {
      ds->damped=((GetJointType(ds->j[i])!=FIX_JOINT)&&(GetJointDamping(ds->j[i])>0.0));
      i++;
    }

  ds->friction=FALSE;
  i=0;
  while((!ds->friction)&&(i<ds->nj))
    {
      ds->friction=((GetJointType(ds->j[i])!=FIX_JOINT)&&(GetJointFriction(ds->j[i])>0.0));
      i++;
    }
	  
  free(c);
  free(F);
  free(IM);
  free(Tmp);
  #if (CUT_AT_LINK)
    free(splitLink);
  #endif
}

void ComputeHandC_FJH(Tparameters *pr,double *x,boolean computeEq,boolean computeHpv,TDynamicSpace *ds)
{
  double epsilon;
  unsigned int i,k,k1,k2,ne;
  THTransform jt;
  #if (HandC_EQ_INV)
    THTransform ijt;
  #endif
  
  epsilon=GetParameter(CT_EPSILON,pr);
  ne=6*ds->nLoops; /* we may pre-compute this somewhere */
    
  memset(ds->Jp,0,sizeof(double)*ne*ds->npv);
    
  for(i=0;i<ds->nLoops;i++) 
    {
      /* One part of the loop: From the virtual-closure link to the root */
      k=ds->nl+i;
      k1=k;
      while(k!=0)
	{
	  #if (USE_HTxSAV)
	    HTransformXSAV(&(ds->iXaTr[k]),ds->njx[k],ds->S[k],ds->auxSAM1);
	  #else
	    MatrixMatrixProduct(6,6,ds->iXa[k],ds->njx[k],ds->S[k],ds->auxSAM1);
	  #endif
	  AddSubMatrix(+1.0,6,ds->njx[k],ds->auxSAM1,6*i,ds->j2x[k],ne,ds->npv,ds->Jp);
	  k=ds->pLink[k];
	}

      /* The other part of the loop: from the closed link to the root */
      k=ds->oID[JointToID(ds->j[ds->cJoint[i]])]; /* position of the to link in the HandC kinematic tree */
      k2=k;
      while(k!=0)
	{
	  #if (USE_HTxSAV)
	    HTransformXSAV(&(ds->iXaTr[k]),ds->njx[k],ds->S[k],ds->auxSAM1);
	  #else
	    MatrixMatrixProduct(6,6,ds->iXa[k],ds->njx[k],ds->S[k],ds->auxSAM1);
	  #endif
	  AddSubMatrix(-1.0,6,ds->njx[k],ds->auxSAM1,6*i,ds->j2x[k],ne,ds->npv,ds->Jp);
	  k=ds->pLink[k];
	}
	
      /* Now compute the position equations, if required */
      if (computeEq)
	{ 
	  HTransformProduct(&(ds->iXaTr[k1]),&(ds->closeTr[i]),&jt);

	  #if (HandC_EQ_INV)
	    HTransformInverse(&(ds->iXaTr[k2]),&ijt);
	    HTransformProduct(&jt,&ijt,&jt);
	  #else
	    HTransformSubstract(&jt,&(ds->iXaTr[k2]),&jt);
	  #endif
	    
	  #if (DEBUG_HandC_FJH)
	    /* When debugging we want exactly the same equations as those we have in cuik */
	    ds->feHC[6*i+0]=HTransformGetElement(AXIS_Z,AXIS_Y,&jt); 
	    ds->feHC[6*i+1]=HTransformGetElement(AXIS_X,AXIS_Z,&jt);
	    ds->feHC[6*i+2]=HTransformGetElement(AXIS_Y,AXIS_X,&jt); 
	  #else
	    ds->feHC[6*i+0]=(HTransformGetElement(AXIS_Z,AXIS_Y,&jt)-HTransformGetElement(AXIS_Y,AXIS_Z,&jt))/2.0;
	    ds->feHC[6*i+1]=(HTransformGetElement(AXIS_X,AXIS_Z,&jt)-HTransformGetElement(AXIS_Z,AXIS_X,&jt))/2.0;
	    ds->feHC[6*i+2]=(HTransformGetElement(AXIS_Y,AXIS_X,&jt)-HTransformGetElement(AXIS_X,AXIS_Y,&jt))/2.0; 
	  #endif
	  ds->feHC[6*i+3]=HTransformGetElement(AXIS_X,AXIS_H,&jt);
	  ds->feHC[6*i+4]=HTransformGetElement(AXIS_Y,AXIS_H,&jt);
	  ds->feHC[6*i+5]=HTransformGetElement(AXIS_Z,AXIS_H,&jt);
	}
    }

  if (computeEq)
    {
      /* And now the other equations (non-dynamical) if any */
      if (ds->noe>0)
	{
	  CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS(pr,ds->oEqs,x,&(ds->feHC[ne]),ds->w);
	}
	
      /* Now compute the velocity equations: J * v */
      MatrixVectorProduct(ne,ds->npv,ds->Jp,&(x[ds->npv+ds->nov]),&(ds->feHC[ne+ds->noe]));
    }
    
  if (ds->nipe<ne)
    {
      /* This is only used mechanisms where the loops are defined with less
	 than 6 equations (e.g., planar mechanisms) */
      if (ds->bJHC==NULL)
	{
	  NEW(ds->bJHC,2*ne+ds->noe,boolean);
	  for(i=0;i<ne;i++)
	    {
	      ds->bJHC[i]=(sqrt(RowsDotProduct(i,i,ne,ds->npv,ds->Jp))>epsilon);
	      ds->bJHC[ne+ds->noe+i]=ds->bJHC[i];
	    }
	  for(i=0;i<ds->noe;i++)
	    ds->bJHC[ne+i]=TRUE;
	}
      SelectMatrixRows(ds->bJHC,ne,ds->npv,ds->Jp);
	
      if (computeEq)
	{
	  SelectMatrixRows(ds->bJHC,2*ne+ds->noe,1,ds->feHC);
	  memcpy(ds->fe,ds->feHC,ds->nie*sizeof(double));
	}
    }

  if (computeHpv)
    memset(ds->Hpv,0,sizeof(double)*ne*ds->npv);

  for(i=0;i<ds->nLoops;i++)
    {
      /* avp predecesor (transformed to global frame) */
      k=ds->nl+i;
      #if (USE_HTxSAV)
        HTransformXSAV(&(ds->iXaTr[k]),1,ds->avp[k],&(ds->gammaHC[6*i]));
      #else
        MatrixVectorProduct(6,6,ds->iXa[k],ds->avp[k],&(ds->gammaHC[6*i]));
      #endif
      if (computeHpv)
	{
	  while(k!=0)
	    {
	      MatrixFromSubMatrix(6,ds->npv,ds->vxS,0,ds->j2x[k],6,ds->njx[k],ds->auxSAM1);
	      #if (USE_HTxSAV)
	        HTransformXSAV(&(ds->iXaTr[k]),ds->njx[k],ds->auxSAM1,ds->auxSAM2);
	      #else
	        MatrixMatrixProduct(6,6,ds->iXa[k],ds->njx[k],ds->auxSAM1,ds->auxSAM2);
	      #endif
	      AddSubMatrix(+1.0,6,ds->njx[k],ds->auxSAM2,6*i,ds->j2x[k],ne,ds->npv,ds->Hpv);
	      k=ds->pLink[k];
	    }
	}
	
      /* avp of succesor (transformed to global frame) */
      k=ds->oID[JointToID(ds->j[ds->cJoint[i]])];
      #if (USE_HTxSAV)
        HTransformXSAV(&(ds->iXaTr[k]),1,ds->avp[k],ds->auxSAV1);
      #else
        MatrixVectorProduct(6,6,ds->iXa[k],ds->avp[k],ds->auxSAV1);
      #endif
      if (computeHpv)
	{
	  while(k!=0)
	    {
	      MatrixFromSubMatrix(6,ds->npv,ds->vxS,0,ds->j2x[k],6,ds->njx[k],ds->auxSAM1);
	      #if (USE_HTxSAV)
	        HTransformXSAV(&(ds->iXaTr[k]),ds->njx[k],ds->auxSAM1,ds->auxSAM2);
	      #else
	        MatrixMatrixProduct(6,6,ds->iXa[k],ds->njx[k],ds->auxSAM1,ds->auxSAM2);
	      #endif
	      AddSubMatrix(-1.0,6,ds->njx[k],ds->auxSAM2,6*i,ds->j2x[k],ne,ds->npv,ds->Hpv);
	      k=ds->pLink[k];
	    }
	}

      /* avp succesor - avp predecesor */
      SubtractVector(6,&(ds->gammaHC[6*i]),ds->auxSAV1);
    }
  if (ds->nipe<ne)
    {
      SelectMatrixRows(ds->bJHC,ne,1,ds->gammaHC);
      memcpy(ds->gamma,ds->gammaHC,ds->nipe*sizeof(double));
	
      if (computeHpv)
	SelectMatrixRows(ds->bJHC,ne,ds->npv,ds->Hpv);
    }
}

void ApplyExternalForces(Tparameters *pr,double *x,TDynamicSpace *ds)
{
  Tlink *lk;
  double *wr;
  unsigned int i,j,k,r;
  THTransform *tl;
  TLinkConf *def;
      
  #if (DEBUG_HandC>1)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	fprintf(stderr,"------------------------------------------------------------------\n");
	fprintf(stderr,"Applying externa forces-------------------------------------------\n");
	fprintf(stderr,"------------------------------------------------------------------\n");
      }
  #endif

  /* Transform to all links. Used to define the wrench in global coordinates */
  GetLinkTransformsFromSolutionPoint(pr,TRUE,x,&tl,&def,ds->wo);
      
  for(i=1;i<ds->nlHC;i++) 
    {
      #if (DEBUG_HandC>1)
        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	  fprintf(stderr,"Link %u\n",i);
      #endif
      
      if (ds->lID[i]==NO_UINT)  /* if it is a connection link (this time we do not skip them!) */
	{
	  lk=ds->l[i];
	  if (IsConnectionSpring(lk)) /* and, in particular, a spring link */
	    {
	      /* Get the wrench for this link */
	      GetConnectionLinkWrench(tl,ds->wr1,ds->wr2,lk);
	      #if (DEBUG_HandC>1)
	        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		  {
		    fprintf(stderr,"Spring between %u [%u] and %u [%u]\n",
			    GetConnectLinkFrom(lk),
			    ds->oID[GetConnectLinkFrom(lk)],
			    GetConnectLinkTo(lk),
			    ds->oID[GetConnectLinkTo(lk)]);
		    PrintVector(stderr,"wr1",6,ds->wr1);
		    PrintVector(stderr,"wr2",6,ds->wr2);
		  }
	      #endif
		
	      /* for the two involved links... */
	      for(r=0;r<2;r++)
		{
		  if (r==0)
		    {
		      j=GetConnectLinkFrom(lk);
		      wr=ds->wr1;
		    }
		  else
		    {
		      j=GetConnectLinkTo(lk);
		      wr=ds->wr2;
		    }
		  if (j>0)
		    {
		      k=ds->oID[j];

		      /* Xa inverse and transposed: inverse to get a local to global
			 transform and transposed to the duality forces-wrenches? */
		      /* fvp[k] = fvp[k] - Xa[k]' \ wr */
		      #if (USE_HTxSAV)
		        HTransformXSAV(&(ds->iXaTr[k]),1,wr,ds->auxSAV1);
		      #else
		        TSAMxSAV(ds->iXa[k],wr,ds->auxSAV1);
		      #endif
		      scaleSAV(-1,ds->auxSAV1);
		      sumSAV(ds->fvp[k],ds->auxSAV1,ds->fvp[k]);
		      
		      #if (DEBUG_HandC>1)
		        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
			  {
			    fprintf(stderr,"Updating fvp[%u]\n",k);
			    #if (USE_HTxSAV)
			      fprintf(stderr,"Xa_c_i=[");
			      HTransformPrint(stderr,&(ds->iXaTr[k]));fprintf(stderr,"];\n");
			    #else
			      PrintMatrix(stderr,"Xa_c_i",6,6,ds->iXa[k]);
			    #endif
			    PrintVector(stderr,"wr",6,wr);
			    PrintVector(stderr,"fvp_c",6,ds->fvp[k]);
			  }
		      #endif
		    }
		}
	    }
	}
    }
      
  DeleteLinkTransforms(tl,def,ds->wo);
}


void ComputeC(double *x,double *u,double *C,TDynamicSpace *ds)
{
  unsigned int i,j,p;
  double da,fr;
  
  #if (DEBUG_HandC>1)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	fprintf(stderr,"-------------------------------------------------------------------\n");
	fprintf(stderr,"Computing C -------------------------------------------------------\n");
	fprintf(stderr,"-------------------------------------------------------------------\n");
      }
  #endif
  
  memset(C,0,sizeof(double)*ds->npv);
  for(i=ds->nlHC-1;i>0;i--)
    {
      if (ds->lID[i]!=NO_UINT) /* this skips connection links */
	{
	  p=ds->pLink[i]; /* identifier of the parent link in global ordering */
	
	  /* Note that we actually compute -C (as defined by Featherstone) */
	  /* C(i) = -S(i)'*fvp(i) */
	  if (ds->njx[i]==1)
	    C[ds->j2x[i]]=-SAVxSAV(ds->S[i],ds->fvp[i]);
	  else
	    {
	      TMatrixVectorProduct(6,ds->njx[i],ds->S[i],ds->fvp[i],&(C[ds->j2x[i]]));
	      ScaleVector(-1,ds->njx[i],&(C[ds->j2x[i]]));
	    }
	  #if (DEBUG_HandC>1)
	    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	      {
		fprintf(stderr,"i: %u l: %u p:%u j:%u -------------------------------------------------------\n",
			i,ds->lID[i],p,ds->jID[i]);
		if (ds->njx[i]>0)
		  {
		    PrintMatrix(stderr,"S_c",6,ds->njx[i],ds->S[i]);
		    PrintVector(stderr,"fvp_c",6,ds->fvp[i]);
		    PrintVector(stderr,"C_c",ds->njx[i],&(C[ds->j2x[i]]));
		  }
	      }
	  #endif
	  
	  if (p>0)
	    {
	      /* fvp[p] = fvp[p] + Xup[i]'*fvp[i] */
	      TSAMxSAVAccum(ds->Xup[i],ds->fvp[i],ds->fvp[p]); /* USE_XUPTR: this operation is faster in sa matrix form */
	      //sumSAV(ds->fvp[p],ds->auxSAV1,ds->fvp[p]);
	    }
	}
    }
  
  /* Add the torques to C (and the damping and the friction!) */
  if (u!=NULL)
    {
      for(i=0;i<ds->da;i++)
	C[ds->a2x[i]]+=u[i];
    }
  
  #if (DEBUG_HandC>1)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      PrintVector(stderr,"C_f",ds->npv,C);
  #endif
  
  /* apply the damping, if necessary */
  if (ds->damped)
    {
      for(i=1;i<ds->nlHC;i++)
	{
	  if (ds->lID[i]!=NO_UINT)
	    {
	      /* Damping of the oint tanking to the i-th link.
		 All joints are used */
	      /* We do not have to invert the sign of damping despite
	         the sign of the joint since signs compensate. The sign
	         should be inverted here and later on when interpreting
	         the output.  */
	      da=GetJointDamping(ds->j[ds->jID[i]]);
	      
	      for(j=0;j<ds->njx[i];j++)
		C[ds->j2x[i]+j]-=da*x[ds->npv+ds->j2x[i]+j];
	    }
	}
      
      #if (DEBUG_HandC>1)
        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	  {
	    PrintVector(stderr,"xd",ds->npv,&(x[ds->npv]));
	    PrintVector(stderr,"C_d",ds->npv,C);
	  }
      #endif
    }
  
  /* apply the dry friction */
  if (ds->friction)
    {
      for(i=1;i<ds->nlHC;i++)
	{
	  if (ds->lID[i]!=NO_UINT)
	    {
	      /* Damping of the oint tanking to the i-th link.
		 All joints are used */ 
	      fr=GetJointFriction(ds->j[ds->jID[i]]);
	      
	      for(j=0;j<ds->njx[i];j++)
		C[ds->j2x[i]+j]-=fr*SGN(x[ds->npv+ds->j2x[i]+j]);
	    }
	}
      
      #if (DEBUG_HandC>1)
        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	  {
	    PrintVector(stderr,"xd",ds->npv,&(x[ds->npv]));
	    PrintVector(stderr,"C_f",ds->npv,C);
	  }
      #endif
    }

  #if (DEBUG_HandC>1)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	PrintVector(stderr,"u_c",ds->da,u);
	PrintVector(stderr,"Cu_c",ds->npv,C);
      }
  #endif
}

void ComputeH(double *x,double *H,TDynamicSpace *ds)
{
  unsigned int i,j,ndx;
  double v;
  
  memset(H,0,sizeof(double)*ds->npv*ds->npv);

  for(i=1;i<ds->nlHC;i++) /* skip the root!! */
    {	  
      if (ds->lID[i]!=NO_UINT) /* skip connection links */
	{
	  #if (DEBUG_HandC>1)
	    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	      {
		fprintf(stderr,"i:%u p:%u ---------------------------\n",i,p);
	      }
	  #endif

	  ndx=ds->j2x[i];
	  	  
	  if (ds->njx[i]>0) /* Skip fix-joints */
	    {
	      if (ds->njx[i]==1)
		{
		  /* fh = IC[i] * S[i] */
		  SAMxSAV(ds->IC[i],ds->S[i],ds->fh);

		  #if (DEBUG_HandC>1)
		    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		      {
			PrintVector(stderr,"fh_c",6,ds->fh);
		      }
		  #endif
	      
		  /* H[i,i] = S[i]' * fh */
		  H[RC2INDEX(ndx,ndx,ds->npv,ds->npv)]=SAVxSAV(ds->S[i],ds->fh);

		  #if (DEBUG_HandC>1)
		    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		      fprintf(stderr,"h_c: %f\n",H[RC2INDEX(ndx,ndx,ds->npv,ds->npv)]);
		  #endif
	      
		  j=i;
		  while(ds->pLink[j]>0)
		    {
		      if (ds->njx[ds->pLink[j]]==0) /* skip fix joints */
			{
			   /* j = parent[j] */
			  j=ds->pLink[j];
			}
		      else
			{
			  /* fh = Xup[j]' * fh */
			  TSAMxSAV(ds->Xup[j],ds->fh,ds->auxSAV1); /* USE_XUPTR: this operation is faster in sa matrix form */
			  copySAV(ds->fh,ds->auxSAV1);
		  	
			  /* j = parent[j] */
			  j=ds->pLink[j];

			  /* H(i,j) = S[j]' * fh */
			  v=SAVxSAV(ds->S[j],ds->fh);	  
			  H[RC2INDEX(ndx,ds->j2x[j],ds->npv,ds->npv)]=v;

			  /* H(j,i) = H(i,j)' */
			  H[RC2INDEX(ds->j2x[j],ndx,ds->npv,ds->npv)]=v;

			  #if (DEBUG_HandC>1)
			    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
			      fprintf(stderr,"  hj_c: %f\n",v);
			  #endif
			}
		    }
		}
	      else
		{
		  /* fh = IC[i] * S[i] */
		  #if (DEBUG_HandC>1)
		    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		      { 
			PrintMatrix(stderr,"IC_c",6,6,ds->IC[i]);
			PrintMatrix(stderr,"S_c",6,ds->njx[i],ds->S[i]);
		      }
		  #endif
		  
		  MatrixMatrixProduct(6,6,ds->IC[i],ds->njx[i],ds->S[i],ds->fh);
 
		  /* H[i,i] = S[i]' * fh */
		  TMatrixMatrixProduct(6,ds->njx[i],ds->S[i],ds->njx[i],ds->fh,ds->dh);

		  #if (DEBUG_HandC>1)
		    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		      PrintMatrix(stderr,"h",ds->njx[i],ds->njx[i],ds->dh);
		  #endif
	      
		  SubMatrixFromMatrix(ds->njx[i],ds->njx[i],ds->dh,ds->j2x[i],ds->j2x[i],ds->npv,ds->npv,H);
	      
		  j=i;
		  while(ds->pLink[j]>0)
		    {
		      if (ds->njx[ds->pLink[j]]==0) /* skip fix joints */
			{
			  /* j = parent[j] */
			  j=ds->pLink[j];
			}
		      else
			{
			  /* fh = Xup[j]' * fh */
			  TMatrixMatrixProduct(6,6,ds->Xup[j],ds->njx[i],ds->fh,ds->auxSAM1); /* USE_XUPTR : This operation is faster in sa matrix form */
			  memcpy(ds->fh,ds->auxSAM1,6*ds->njx[i]*sizeof(double));
		      
			  /* j = parent[j] */
			  j=ds->pLink[j];

			  #if (DEBUG_HandC>1)
			    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
			      {
				fprintf(stderr,"  p:%u\n",j);
				PrintVector(stderr,"fh",6,ds->fh);
				PrintMatrix(stderr,"S",6,ds->njx[j],ds->S[j]);
			      }
			  #endif
		  
			  /* H(i,j) = S[j]' * fh */	
			  TMatrixMatrixProduct(6,ds->njx[j],ds->S[j],ds->njx[i],ds->fh,ds->dh);

			  #if (DEBUG_HandC>1)
			    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
			      PrintMatrix(stderr,"  hp",ds->njx[j],ds->njx[i],ds->dh);
			  #endif
		      
			  SubMatrixFromMatrix(ds->njx[j],ds->njx[i],ds->dh,ds->j2x[j],ds->j2x[i],ds->npv,ds->npv,H);
		  
			  /* H(j,i) = H(i,j)' */
			  SubMatrixFromTMatrix(ds->njx[j],ds->njx[i],ds->dh,ds->j2x[i],ds->j2x[j],ds->npv,ds->npv,H);
			}
		    }
		}
	    }
	}
    }
} 

void HandC(Tparameters *pr,double *x,double *u,double *H,double *C,boolean computeEq,boolean computeHpv,TDynamicSpace *ds)
{
  unsigned int i,j,p;
  THTransform jt,ijt;
  
  #if (DEBUG_HandC>1)
    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
      {
	fprintf(stderr,"=============================================================================================\n");
	fprintf(stderr,"=============================================================================================\n");
	fprintf(stderr,"=============================================================================================\n");
	fprintf(stderr,"HandC\n");
	fprintf(stderr,"=============================================================================================\n");
	fprintf(stderr,"=============================================================================================\n");
	fprintf(stderr,"=============================================================================================\n");
	PrintVector(stderr,"x",ds->nv,x);
	PrintVector(stderr,"u",ds->da,u);
      }
  #endif

  #if (HandC_FJH)
    if (computeHpv)
      memset(ds->vxS,0,sizeof(double)*6*ds->npv);
  #endif
    
  /* Compute velocites, accelerations and forces for each link */
  /* This loop goes in the order of links in the kinematic tree */
  for(i=1;i<ds->nlHC;i++) /* skip the root!! */
    {
      if (ds->lID[i]!=NO_UINT) /* skip connection links*/
	{
	  p=ds->pLink[i]; /* identifier of the parent link in global ordering */
      
	  /* XJ = jcalc(q,joint) */
	  /* vJ = S[i]*dq */
	  GetJointBasicTransform(&(x[ds->j2x[i]]),&(x[ds->npv+ds->j2x[i]]),
				 &jt,&ijt,ds->S[i],ds->vJ,ds->j[ds->jID[i]]);

	  /* If the sign is positive, jt is the transform from local coordinates of 
	     child to local coordinates of parent. Wee need the inverse. 
	     For negative signs, jt is already correct, but we have to correct
	     the other outputs of GetJointBasicTransform */
	  if (ds->jSgn[i]>0)
	    {
	      /* Compute S */
	      #if (USE_XUPTR)
	        HTransformCopy(&(ds->XJTr),&ijt);
	      #endif
	      HTransform2SAM(&ijt,ds->XJ); /* jt is parent->child and we need to use the inverse */
	      if ((HandC_FJH)||(ds->nef>0))
		HTransformCopy(&(ds->iXJTr),&jt);
	    }
	  else
	    { 
	      /* A joint with inverse polarity (jt is already the inverse) */
	      #if (USE_XUPTR)
	        HTransformCopy(&(ds->XJTr),&jt);
	      #endif
	      HTransform2SAM(&jt,ds->XJ); /* jt is already child->parent */
	      if ((HandC_FJH)||(ds->nef>0))
		HTransformCopy(&(ds->iXJTr),&ijt);
	      
	      if (ds->njx[i]>0)
		{
		  /* Now invert S */
		  MatrixMatrixProduct(6,6,ds->XJ,ds->njx[i],ds->S[i],ds->auxSAM1);
		  memcpy(ds->S[i],ds->auxSAM1,6*ds->njx[i]*sizeof(double));
		  ScaleVector(-1.0,6*ds->njx[i],ds->S[i]);

		  /* and vJ */
		  MatrixVectorProduct(6,6,ds->XJ,ds->vJ,ds->auxSAV1);
		  memcpy(ds->vJ,ds->auxSAV1,6*sizeof(double));
		  ScaleVector(-1.0,6,ds->vJ);
		}
	    }
	  
	  #if (DEBUG_HandC>1)
	    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	      {
		fprintf(stderr,"i:%u p:%u -----------------------------------------------------------------\n",i,p);
		fprintf(stderr,"sg: %d\n",ds->jSgn[i]);
		if (ds->njx[i]>0)
		  { 
		    PrintVector(stderr,"q",ds->njx[i],&(x[ds->j2x[i]]));
		    PrintVector(stderr,"qd",ds->njx[i],&(x[ds->npv+ds->j2x[i]]));
		    PrintMatrix(stderr,"S",6,ds->njx[i],ds->S[i]);
		    PrintVector(stderr,"vJ_c",6,ds->vJ);
		  }
		PrintMatrix(stderr,"XJ_c",6,6,ds->XJ);
		PrintMatrix(stderr,"Xtree_c",6,6,ds->Xtree[i]);
		if (p==0)
		  PrintVector(stderr,"-a_grav",6,ds->a_grav);
	      }
	  #endif

	  /* Transform child-parent including the joint displacement (in coordinates of the child) */
	  /* Xup[i] = XJ * Xtree[i] */
	  #if (USE_XUPTR)
	    HTransformProduct(&(ds->XJTr),&(ds->XtreeTr[i]),&(ds->XupTr[i])); /* USE_XUPTR : this is the main added cost of using XupTr */
	  #endif
	  SAMxSAM(ds->XJ,ds->Xtree[i],ds->Xup[i]);
	  if ((HandC_FJH)||(ds->nef>0))
	    HTransformProduct(&(ds->iXtreeTr[i]),&(ds->iXJTr),&(ds->iXupTr[i])); /* iXup[i] = iXtree[i] * iXJ  */

	  #if (DEBUG_HandC>1)
	    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	      PrintMatrix(stderr,"Xup_c",6,6,ds->Xup[i]);
	  #endif

	  if (p==0)
	    {
	      if ((HandC_FJH)||(ds->nef>0))
		{
		  /* We need iXa for the Jacobian/Hessian */
		  
		  /* Xa[i] = Xup[i]  ->  Xa[i]^-1 = Xup[i]^-1 */
		  HTransformCopy(&(ds->iXaTr[i]),&(ds->iXupTr[i]));
		}
	      
	      /* v[i] = vJ */
	      if (ds->njx[i]>0)
		copySAV(ds->v[i],ds->vJ);
	      else
		memset(ds->v[i],0,sizeof(double)*6); /*  v[i] = vJ  will also work since vJ=0 in this case */

	      /* avp[i] = Xup[i]*(-a_grav) */
	      #if (USE_XUPTR)
	        HTransformXSAV(&(ds->XupTr[i]),1,ds->a_grav,ds->avp[i]); /* USE_XUPTR : this is faster with XupTr */
	      #else
	        SAMxSAV(ds->Xup[i],ds->a_grav,ds->avp[i]);
              #endif
	    }
	  else
	    {
	      if ((HandC_FJH)||(ds->nef>0))
		{
		  /* We need iXa for the Jacobian/Hessian */
	      
		  /* Xa[i] = Xup[i] * Xa[p]  ->  Xa[i]^-1 = Xa[p]^-1 * Xup[i]^1 */
		  HTransformProduct(&(ds->iXaTr[p]),&(ds->iXupTr[i]),&(ds->iXaTr[i]));
		}
	      
	      /* v[i] = Xup[i]*v[p] + vJ */
	      if (ds->njx[i]>0)
		{
		  #if (USE_XUPTR)
		    HTransformXSAV(&(ds->XupTr[i]),1,ds->v[p],ds->auxSAV1); /* USE_XUPTR : this is faster with XupTr */
	          #else
		    SAMxSAV(ds->Xup[i],ds->v[p],ds->auxSAV1);
		  #endif
		  sumSAV(ds->auxSAV1,ds->vJ,ds->v[i]);
		}
	      else
		{
		  #if (USE_XUPTR)
		    HTransformXSAV(&(ds->XupTr[i]),1,ds->v[p],ds->v[i]); /* USE_XUPTR : this is faster with XupTr */
		  #else
		    SAMxSAV(ds->Xup[i],ds->v[p],ds->v[i]);
		  #endif
		}

	      /* compute the acceleration velocity products */
	      if (ds->njx[i]==1)
		{
		  /* avp[i] = Xup[i]*avp[p] + crm(v[i])*vJ */
		  /* Note that vJ = S*qd and, thus
		       avp[i] = Xup[i]*avp[p] + (crm(v[i])*S)*qd
		     The avp can be seen as a matrix vector product
		       avp[i] = Hpv * qd 
		     where Hpv has crm(v[i])*S in the right columns.
		     We save the Hpv matrix since it is relevant later on */
		  #if (USE_XUPTR)
		    HTransformXSAV(&(ds->XupTr[i]),1,ds->avp[p],ds->auxSAV1); /* USE_XUPTR : this is faster with XupTr */
		  #else
		    SAMxSAV(ds->Xup[i],ds->avp[p],ds->auxSAV1);
		  #endif

		  #if (HandC_FJH)
		    /* Version here Hpv is computed and saved */
		    #if (EXPLICIT_CRM)
		      crm(ds->v[i],ds->auxSAM1);
		      SAMxSAV(ds->auxSAM1,ds->S[i],ds->auxSAV2);
		    #else
		      CRMxSAV(ds->v[i],ds->S[i],ds->auxSAV2);
		    #endif
		    if (computeHpv)
		      SetColumn(ds->auxSAV2,ds->j2x[i],6,ds->npv,ds->vxS);
		    ScaleVector(x[ds->npv+ds->j2x[i]],6,ds->auxSAV2);
		  #else
		    /* Standard procedure without saving Hpv */
		    #if (EXPLICIT_CRM)
		      crm(ds->v[i],ds->auxSAM1);
		      SAMxSAV(ds->auxSAM1,ds->vJ,ds->auxSAV2);
		    #else
		      CRMxSAV(ds->v[i],ds->vJ,ds->auxSAV2);
		    #endif
		  #endif
		  sumSAV(ds->auxSAV1,ds->auxSAV2,ds->avp[i]);
		}
	      else
		{
		  double *qd;

		  /* note that this also works for ds->njx[i]==0 */
		  
		  qd=&(x[ds->npv+ds->nov+ds->j2x[i]]);

		  /* avp[i] = Xup[i] * avp[p]   (only term computed if ds->njx[i]==0)  */
		  #if (USE_XUPTR)
		    HTransformXSAV(&(ds->XupTr[i]),1,ds->avp[p],ds->avp[i]); /* USE_XUPTR : this is faster with XupTr */
		  #else
		    SAMxSAV(ds->Xup[i],ds->avp[p],ds->avp[i]);
		  #endif

		  #if (DEBUG_HandC>2)
		    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		      PrintVector(stderr,"a_0",6,ds->avp[i]);
		  #endif
		  
		  for(j=0;j<ds->njx[i];j++) /* if ds->njx[i]==0 this is skipped */
		    {
		      /* avp[i] = avp[i] + crm(sav1) * S[:,j]*qd[j] where S[:,j] is the j-th column for S */
		      /* where nitialy auxSAV1 is Xup[i]*v[p] (velocity comming from parent)  */
		      /* note that for njx[i]==1 vJ is S[:,1]*qd[1] (i.e., the same formula as before) */

		      GetColumn(j,6,ds->njx[i],ds->S[i],ds->auxSAV2);
		      
		      #if (EXPLICIT_CRM)
		        crm(ds->auxSAV1,ds->auxSAM1);
		        SAMxSAV(ds->auxSAM1,ds->auxSAV2,ds->auxSAV3);
		      #else
		        CRMxSAV(ds->auxSAV1,ds->auxSAV2,ds->auxSAV3);
		      #endif
		     
		      SumVectorScale(6,ds->avp[i],qd[j],ds->auxSAV3,ds->avp[i]);
		      
		      #if (DEBUG_HandC>2)
		        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
			  {
			    fprintf(stderr,"j:%u -----------------------------\n",j);
			    PrintVector(stderr,"   t_c",6,ds->auxSAV1);
			    //PrintMatrix(stderr,"   C_c",6,6,ds->auxSAM1);
			    fprintf(stderr,"   qd=%f\n",qd[j]);
			    PrintVector(stderr,"   S_c",6,ds->auxSAV2);
			    PrintVector(stderr,"   C_c x (S_c)",6,ds->auxSAV3);
			    PrintVector(stderr,"   a",6,ds->avp[i]);
			  }
		      #endif

                      #if (HandC_FJH)
			if (computeHpv)
			  SetColumn(ds->auxSAV3,ds->j2x[i]+j,6,ds->npv,ds->vxS);
		      #endif
			
		      /* Accumulate velocities: parent+previous dof. Note that at the end sav1 is vJ */
		      /* sav1 = sav1 +  qd[j]*S[:,j] */
		      SumVectorScale(6,ds->auxSAV1,qd[j],ds->auxSAV2,ds->auxSAV1);
		    }
		}
	    }

	  #if (DEBUG_HandC>1)
	    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	      {
		PrintVector(stderr,"v_c",6,ds->v[i]);
		PrintVector(stderr,"avp_c",6,ds->avp[i]);
	      }
	  #endif 
	  
	  /* fvp[i] = I[i]*avp(i) + crf(v[i])*I[i]*v[i] */	  
	  SAMxSAV(ds->IM[i],ds->avp[i],ds->fvp[i]);

	  #if (EXPLICIT_CRF)
	    crf(ds->v[i],ds->auxSAM1);	  
	    SAMxSAM(ds->auxSAM1,ds->IM[i],ds->auxSAM2);
	  #else
	    CRFxSAM(ds->v[i],ds->IM[i],ds->auxSAM2);
          #endif
	  
	  SAMxSAVAccum(ds->auxSAM2,ds->v[i],ds->fvp[i]);	  
	  //sumSAV(ds->auxSAV1,ds->auxSAV2,ds->fvp[i]);

	  #if (DEBUG_HandC>1)
	    if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
	      {
		PrintMatrix(stderr,"I_c",6,6,ds->IM[i]);
		PrintVector(stderr,"fvp_c",6,ds->fvp[i]);
	      }
	  #endif
	}
    }

  #if (!USE_HTxSAV)
    if ((HandC_FJH)||(ds->nef>0))
      {
	/* Convert the iXatr to spatial algebra matrix */
	for(i=1;i<ds->nlHC;i++)
	  HTransform2SAM(&(ds->iXaTr[i]),ds->iXa[i]);
      }
  #endif

  /* Compute the position Jacobian */
  #if (HandC_FJH)
    ComputeHandC_FJH(pr,x,computeEq,computeHpv,ds);
  #endif
    
  /* Apply external forces */
  if (ds->nef>0)
    ApplyExternalForces(pr,x,ds);
  
  /* Accumulate forces from tip to root */
  ComputeC(x,u,C,ds);
  
  /* Compute the composite inertia (IC) */
  /*  IC = I */
  for(i=0;i<ds->nlHC;i++)
    copySAM(ds->IC[i],ds->IM[i]);

  for(i=ds->nlHC-1;i>0;i--)
    {
      if (ds->lID[i]!=NO_UINT) /* Skip connection links */
	{
	  p=ds->pLink[i];
	  if (p!=0) /* skip links connected to root */
	    {	  
	      /* IC[p] = IC[p] + Xup[i]'*IC[i]*Xup[i] */
	      #if (DEBUG_HandC>1)
	         if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		   {
		     fprintf(stderr,"i:%u p:%u ---------------------------\n",i,p);
		     PrintMatrix(stderr,"Xup_c",6,6,ds->Xup[i]);
		     PrintMatrix(stderr,"IC_c",6,6,ds->IC[i]);
		   }
	      #endif

	      /* USE_XUPTR : next two operations are faster with Xup */
	      TSAMxSAM(ds->Xup[i],ds->IC[i],ds->auxSAM1);
	      SAMxSAMAccum(ds->auxSAM1,ds->Xup[i],ds->IC[p]);
		
	      #if (DEBUG_HandC>1)
	        if ((!omp_in_parallel())||(omp_get_thread_num()==HandC_Thread))
		  {
		    PrintMatrix(stderr,"Xup_c'*IC*Xup_c",6,6,ds->auxSAM2);
		    PrintMatrix(stderr,"IC_c",6,6,ds->IC[p]);
		  }
	      #endif
	    }
	}
    }
  
  /* define H */
  ComputeH(x,H,ds);
}

void MechEnergy(Tparameters *pr,double *x,double *pe,double *ke,TDynamicSpace *ds)
{
  unsigned int i,p;
  THTransform jt,ijt;
  double Itot[36];
  double cm[3];
  double mass;
  
  *pe=0;
  *ke=0;

  #if (DEBUG_HandC)
    fprintf(stderr,"---------------------------------------------------------------------\n");
    fprintf(stderr,"Mech energy ---------------------------------------------------------\n");
    fprintf(stderr,"---------------------------------------------------------------------\n");
    PrintVector(stderr,"x",ds->nv,x);
  #endif
  for(i=1;i<ds->nlHC;i++) /* skip the root!! */
    {
      if (ds->lID[i]!=NO_UINT) /* skip connection links*/
	{
	  p=ds->pLink[i]; /* identifier of the parent link in global ordering */
      
	  /* XJ = jcalc(q,joint) */
	  /* vJ = S[i]*dq */
	  GetJointBasicTransform(&(x[ds->j2x[i]]),&(x[ds->npv+ds->j2x[i]]),
				 &jt,&ijt,ds->S[i],ds->vJ,ds->j[ds->jID[i]]);
	  
	  /* If the sign is positive, jt is the transform from local coordinates of 
	     child to local coordinates of parent. Wee need the inverse. 
	     For negative signs, jt is already correct, but we have to correct
	     the other outputs of GetJointBasicTransform */
	  if (ds->jSgn[i]>0)
	    {
	      #if (USE_XUPTR)
	        HTransformCopy(&(ds->XJTr),&ijt);
	      #endif
	      HTransform2SAM(&ijt,ds->XJ);
	    }
	  else
	    {
	      #if (USE_XUPTR)
	        HTransformCopy(&(ds->XJTr),&jt);
	      #endif
	      /* A joint with inverse polarity (jt is already the inverse) */
	      HTransform2SAM(&jt,ds->XJ);
	      MatrixMatrixProduct(6,6,ds->XJ,ds->njx[i],ds->S[i],ds->S[i]);
	      ScaleVector(-1.0,6*ds->njx[i],ds->S[i]);

	      if (ds->njx[i]>0)
		{
		  MatrixVectorProduct(6,6,ds->XJ,ds->vJ,ds->vJ);
		  ScaleVector(-1.0,6,ds->vJ);
		}
	    }

	  /* Xup[i] = XJ * Xtree[i] */
	  #if (USE_XUPTR)
	    HTransformProduct(&(ds->XJTr),&(ds->XtreeTr[i]),&(ds->XupTr[i])); /* USE_XUPTR : extra cost of using XupTr */
	  #endif
	  SAMxSAM(ds->XJ,ds->Xtree[i],ds->Xup[i]);

	  /* Compute velocity */
	  if (p==0)
	    {
	      /* v[i] = vJ */
	      if (ds->njx[i]>0)
		copySAV(ds->v[i],ds->vJ);
	      else
		memset(ds->v[i],0,sizeof(double)*6);
	    }
	  else
	    {
	      /* v[i] = Xup[i]*v[p] + vJ */
	      #if (USE_XUPTR)
	        HTransformXSAV(&(ds->XupTr[i]),1,ds->v[p],ds->auxSAV1); /* USE_XUPTR : this is faster with XupTr */
	      #else
	        SAMxSAV(ds->Xup[i],ds->v[p],ds->auxSAV1);
	      #endif
	      if (ds->njx[i]>0)
		sumSAV(ds->auxSAV1,ds->vJ,ds->v[i]);
	    }
	  
	  /*  IC = I */
	  copySAM(ds->IC[i],ds->IM[i]);

	  /* h = IC * v */
	  SAMxSAV(ds->IC[i],ds->v[i],ds->auxSAV1);
	  
	  /* accumulate ke */
	  *ke+=0.5*SAVxSAV(ds->v[i],ds->auxSAV1);

	  #if (DEBUG_HandC>1)
	    fprintf(stderr,"i:%u -------------------------------\n",i);
	    fprintf(stderr,"  sgn:%d\n",ds->jSgn[i]);
	    PrintVector(stderr,"  q",ds->njx[i],&(x[ds->j2x[i]]));
	    PrintVector(stderr,"  qd",ds->njx[i],&(x[ds->npv+ds->j2x[i]]));
	    if (ds->njx[i]>0)
	      PrintVector(stderr,"  vJ",6,ds->vJ);
	    PrintMatrix(stderr,"  XJ_c",6,6,ds->XJ);
	    PrintMatrix(stderr,"  Xtree_c",6,6,ds->Xtree[i]);
	    PrintMatrix(stderr,"  Xup_c",6,6,ds->Xup[i]);
	    PrintVector(stderr,"  v_c",6,ds->v[i]);
	    PrintVector(stderr,"  h_c",6,ds->auxSAV1);
	    fprintf(stderr,"  ke_c: %f\n",*ke);
	  #endif
	}
    }
   
  /* Take into account springs, if any */
  if (ds->nef>0)
    {
      THTransform *tl;
      TLinkConf *def;
      Tlink *lk;

      /* Transform to all links. Used to define the wrench in global coordinates */
      GetLinkTransformsFromSolutionPoint(pr,TRUE,x,&tl,&def,ds->wo);
      
      for(i=1;i<ds->nlHC;i++) 
	{
	  if (ds->lID[i]==NO_UINT) /* if it is a connection link */
	    {
	      lk=ds->l[i];
	      if (IsConnectionSpring(lk)) /* and, in particular, a spring link */
		{
		  /* Get the wrench for this link */
		  *pe+=GetConnectionLinkPotentialEnergy(tl,lk);
		}
	    }
	}
      
      DeleteLinkTransforms(tl,def,ds->wo);
    }

  /* Compute the composite inertia */
  /* Itot=0 */
  memset(Itot,0,sizeof(double)*36);
  
  for(i=ds->nlHC-1;i>0;i--)
    {
      if (ds->lID[i]!=NO_UINT) /* Skip connection links */
	{
	  /* auxSAM2 = Xup[i]'*IC[i]*Xup[i]*/
	  /* USE_XUPTR : Next two operations are faster using */
	  TSAMxSAM(ds->Xup[i],ds->IC[i],ds->auxSAM1);
	  SAMxSAM(ds->auxSAM1,ds->Xup[i],ds->auxSAM2);

	  p=ds->pLink[i];
	  
	  #if (DEBUG_HandC>1)
	    fprintf(stderr,"i:%u p:%u -------------------------------\n",i,p);
	    PrintMatrix(stderr,"  A_c",6,6,ds->auxSAM2);
	  #endif
	      
	  if (p!=0) /* skip links connected to root */
	    {	  
	      /* IC[p] = IC[p] + auxSAM2 */
	      sumSAM(ds->IC[p],ds->auxSAM2,ds->IC[p]);
	      #if (DEBUG_HandC>1)
	        PrintMatrix(stderr,"  IC_c",6,6,ds->IC[p]);
	      #endif
	    }
	  else
	    {
	      /* Itot = Itot + auxSAM2 */
	      sumSAM(Itot,ds->auxSAM2,Itot);
	      #if (DEBUG_HandC>1)
	        PrintMatrix(stderr,"  Itot_c",6,6,Itot);
	      #endif
	    }
	}
    }
  
  rbi2mci(Itot,&mass,cm,NULL);

  /* + since a_grav is actually -a_grav */
  *pe+=mass*GeneralDotProduct(3,cm,&(ds->a_grav[3]));

  #if (DEBUG_HandC>0)
    PrintMatrix(stderr,"Itot_c",6,6,Itot);
    PrintVector(stderr,"cm_c",3,cm);
    fprintf(stderr,"m_c:%f\n",mass);
    PrintVector(stderr,"g_c",3,&(ds->a_grav[3]));
    fprintf(stderr,"pe:%f\n",*pe);
  #endif
}

void DeleteHandC(TDynamicSpace *ds)
{
  unsigned int i;

   for(i=0;i<ds->nlHC;i++)
    {
      free(ds->IM[i]);
      free(ds->Xtree[i]);
      free(ds->S[i]);
      #if (!USE_HTxSAV)
        free(ds->iXa[i]);
      #endif
      free(ds->Xup[i]);
      free(ds->v[i]);
      free(ds->avp[i]);
      free(ds->fvp[i]);
      free(ds->fout[i]);
      free(ds->IC[i]);
    }
   free(ds->auxSAV1);
   free(ds->auxSAV2);
   free(ds->auxSAV3);
   free(ds->auxSAM1);
   free(ds->auxSAM2);
   free(ds->wr1);
   free(ds->wr2);
   free(ds->fh);
   free(ds->dh);
   free(ds->IC);
   free(ds->fout);
   free(ds->fvp);
   free(ds->vxS);
   if (ds->nipe<6*ds->nLoops)
     {
       free(ds->gammaHC);
       free(ds->feHC);
     }
   free(ds->avp);
   free(ds->v);
   #if (!USE_HTxSAV)
     free(ds->iXa);
   #endif
   free(ds->iXaTr);
   #if (USE_XUPTR)
     free(ds->XtreeTr);
   #endif
   free(ds->Xup);
   free(ds->iXupTr);
   free(ds->S);
   free(ds->XJ);
   free(ds->vJ);
   free(ds->Xtree);
   free(ds->iXtreeTr);
   free(ds->closeTr);
   free(ds->njx);
   free(ds->j2x);
   free(ds->jSgn);
   free(ds->jID);
   free(ds->pLink);
   free(ds->lID);
   free(ds->oID);
   free(ds->IM);
   free(ds->a_grav);
   free(ds->cJoint);
   if (ds->bJHC!=NULL)
     free(ds->bJHC);
}

/* --------------------------------------------------------------------------------------------------------
   --------------------------------------------------------------------------------------------------------
   public dynamic methods
   --------------------------------------------------------------------------------------------------------
   --------------------------------------------------------------------------------------------------------*/

void InitDynamicSpace(Tparameters *pr,boolean parallel,TJacobian *sJ,TAtlasBase *w,TDynamicSpace *ds)
{
  unsigned int dof,i,kv,kp,ko,j,k,na,nx,nv,ne;
  Tworld *wo;
  boolean hasS;

  if (ON_CUIKSYSTEM(w))
    Error("The dynamic parameters are not given in a cuik file. Use the world file.");
    
  if ((unsigned int)GetParameter(CT_REPRESENTATION,pr)!=REP_JOINTS)
    Error("The dynamics can only be defined when using a joint-based representation");
    
  dof=(unsigned int)GetParameter(CT_N_DOF,pr);

  #ifdef _OPENMP
    #if (DEBUG_HandC)
      ds->parallel=FALSE;
    #else
      ds->parallel=parallel;
    #endif
  #else
    ds->parallel=FALSE;
  #endif
  
  ds->w=w;

  /* The world in the AtlasRRT base structure */
  wo=GET_WORLD(w);
  
  #if (DEBUG_DYNAMICS>2)
    if (dof%2!=0)
      Error("The dimension of the satate space manifold should be even");
  #endif
  ds->dof=dof/2; /* dimension of the position manifold */

  ds->sJ=sJ;  /* just a pointer, not a copy! */

  GetJacobianSize(&(ds->ne),&(ds->nv),ds->sJ);

  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&(ds->domain),w);

  if (CS_WD_GET_SIMP_TOPOLOGY(pr,&(ds->tp),ds->w)!=ds->nv)
    Error("Missmatch number of variables in InitDynamicSpace");

  /* Search for a non-real variable */
  hasS=FALSE;
  i=0;
  while((i<ds->nv)&&(!hasS))
    {
      hasS=(ds->tp[i]==TOPOLOGY_S);
      i++;
    }
  if (!hasS)
    {
      /* if all variables are real no need to consider topology */
      free(ds->tp);
      ds->tp=NULL;
    }
  
  nv=CS_WD_GET_POSITION_VELOCITY_VARS(&(ds->pvVars),w);
  if (nv!=ds->nv)
    Error("Missmatch in the number of variables (InitDynamicSpace)");

  ds->nov=0; /*number of non position/velocity variables*/
  for(i=0;i<ds->nv;i++)
    {
      if (!ds->pvVars[i])
	ds->nov++;
    }
  
  ne=CS_WD_GET_POSITION_VELOCITY_EQS(&(ds->pvEqs),w);
  if (ne!=ds->ne)
    Error("Missmatch in the number of equations (InitDynamicSpace)");

  NEW(ds->oEqs,ds->ne,boolean);
  ds->noe=0; /*number of non position/velocity variables*/
  for(i=0;i<ds->ne;i++)
    {
      if (!ds->pvEqs[i])
	{
	  ds->oEqs[i]=TRUE;
	  ds->noe++;
	}
      else
	ds->oEqs[i]=FALSE;
    }
  if (ds->noe!=ds->nov)
    Error("The number of non-dynamics equations/variables must be the same");
  
  NEW(ds->selEqs,ds->ne,boolean); /* space to combine flags over variables */
  
  #if (DEBUG_DYNAMICS>2)
    if ((ds->nv-ds->nov)%2!=0)
      Error("Number of variables must be even in state spaces");
    if ((ds->ne-ds->noe)%2!=0)
      Error("Number of equations must be even in state spaces");
  #endif
    
  ds->npv=(ds->nv-ds->nov)/2; /* half of the variables are position (1st ones) */
  ds->npe=(ds->ne-ds->noe)/2; /* half of the equations are position (not ordered) */

  ds->nie=ds->nv-2*ds->dof;
  ds->nipe=ds->npv-ds->dof;

  NEW(ds->pos,ds->npv,double); /* space to get the position values of a state */
  NEW(ds->vel,ds->npv,double); /* space for the velocity values */
      
  CS_WD_GET_POSITION_VARS(&(ds->pVars),w);
    
  if (ds->npe+ds->noe>0)
    {
      if (ds->npe>0)
	{
	  CS_WD_GET_POSITION_EQS(&(ds->pEqs),w);
	  
	  NEW(ds->ndxPE,ds->npe,unsigned int);
	  NEW(ds->ndxVE,ds->npe,unsigned int);
	}
      else
	{
	  ds->pEqs=NULL;
	  ds->ndxPE=NULL;
	  ds->ndxVE=NULL;
	}
      
      if (ds->noe>0)
	{
	  NEW(ds->ndxOE,ds->noe,unsigned int);
	}
      else
	ds->ndxOE=NULL;
      
      kv=0;
      kp=0;
      ko=0;
      for(i=0;i<ds->ne;i++)
	{
	  if (ds->pvEqs[i])
	    {
	      if (ds->pEqs[i])
		{
		  ds->ndxPE[kp]=i;
		  kp++;
		}
	      else
		{
		  ds->ndxVE[kv]=i;
		  kv++;
		}
	    }
	  else
	    {
	      ds->ndxOE[ko]=i;
	      ko++;
	    }
	}
      
      if (ds->npv>0)
	{
	  NEW(ds->ndxPV,ds->npv,unsigned int);
	  NEW(ds->ndxVV,ds->npv,unsigned int);
	}
      else
	{
	  ds->ndxPV=NULL;
	  ds->ndxVV=NULL;
	}
      
      if (ds->nov>0)
	{
	  NEW(ds->ndxOV,ds->nov,unsigned int);
	}
      else
	ds->ndxOV=NULL;
	
      kv=0;
      kp=0;
      ko=0;
      for(i=0;i<ds->nv;i++)
	{
	  if (ds->pvVars[i])
	    {
	      if (ds->pVars[i])
		{
		  ds->ndxPV[kp]=i;
		  kp++;
		}
	      else
		{
		  ds->ndxVV[kv]=i;
		  kv++;
		}
	    }
	  else
	    {
	      ds->ndxOV[ko]=i;
	      ko++;
	    }
	}

      /* Define the position Jacobian */
      if (ds->noe>0)
	{
	  CopyNonDynamicsJacobian(&(ds->sJop),&(ds->sJoo),ds->sJ);
	  
	  NEW(ds->o,ds->nov,double);
	  InitLS(ds->nov,ds->noe,ds->npv,&(ds->Jot));
	  ds->Joo=GetLSMatrixBuffer(&(ds->Jot));
	  ds->Jop=GetLSRHBuffer(&(ds->Jot));  
	}
      
      /* Define the position Jacobian */
      CopyPositionJacobian(&(ds->sJp),ds->sJ);
      
      /* Numeric Jacobian (of the position equations only) */
      NEW(ds->nJp,1,TNJacobian);
      if (!CS_WD_GET_SIMP_NJACOBIAN(pr,ds->nJp,ds->w))
	{
	  free(ds->nJp);
	  ds->nJp=NULL;
	}

      /* Symbolic / Numeric hessian (can only be defined in some problems) */
      NEW(ds->nHp,1,TNHessian);  
      if ((ds->nJp==NULL)||(!CS_WD_GET_SIMP_NHESSIAN(pr,GetScalarJacobian(ds->nJp),ds->nHp,ds->w)))
	{
	  free(ds->nHp);
	  ds->nHp=NULL;

	  /* Compute symbolic the position Hessian */
	  InitHessian(&(ds->sJp),&(ds->sHp));

	  /* Space for the evaluation of the symbolic hessian */
	  AllocateHessianEvaluationAsVectors(ds->nipe,&(ds->Hp),&(ds->sHp));
	}

      #if (HandC_FJH)
        NEW(ds->Hpv,6*NumLoops(wo)*ds->npv,double);
      #else
        NEW(ds->Hpv,ds->nipe*ds->npv,double);
      #endif

      /* Allocate space for evaluations in dynamic computations: acceleration,... */
      NEW(ds->J,ds->ne*ds->nv,double);  /* Full Jacobian or its transposed */
      NEW(ds->cJ,ds->ne*ds->nv,double); /* Copy of the full Jacobian or its transposed */

      NEW(ds->Jp,ds->npe*ds->npv,double); /* Position Jacobian or its transposed */
      
      NEW(ds->bJ,ds->ne,boolean);   /* Set of independent equations */
      NEW(ds->bJp,ds->npe,boolean); /* Set of independent position equations */

      #if (DEBUG_HandC_FJH)
        NEW(ds->Jp2,ds->npe*ds->npv,double);
	NEW(ds->Hpv2,ds->nipe*ds->npv,double);
	NEW(ds->gamma2,ds->nipe,double);
	NEW(ds->fe2,ds->nv,double);
      #endif
    }
  else
    {
      ds->pVars=NULL;
      ds->pEqs=NULL;
      
      ds->ndxPE=NULL;
      ds->ndxVE=NULL;
      ds->ndxOE=NULL;
      
      ds->ndxPV=NULL;
      ds->ndxVV=NULL;
      ds->ndxOV=NULL;

      ds->nJp=NULL;
      ds->nHp=NULL;
      ds->Hpv=NULL;
      ds->J=NULL;
      ds->cJ=NULL;
    }
  
  /* Mass matrix */
  NEW(ds->Mm,ds->npv*ds->npv,double);

  /* dimension of linear system is nvp + niep (we only use Independent equations) */
  ds->lsSize=ds->npv+ds->nipe;
  InitLS(ds->lsSize,ds->lsSize,1,&(ds->A));
  ds->mA=GetLSMatrixBuffer(&(ds->A));
  ds->rhsA=GetLSRHBuffer(&(ds->A));
  ds->solA=GetLSSolutionBuffer(&(ds->A));
  ds->Qa=ds->rhsA;
  ds->gamma=&(ds->rhsA[ds->npv]);
  ds->qdd=&(ds->solA[ds->nipe]);

  NEW(ds->g,ds->nv,double); /* it will include the velocity for non-dynamic variables in some cases */
  NEW(ds->gy,2*ds->dof,double);

  NEW(ds->k1,ds->nv,double);
  NEW(ds->k2,ds->nv,double);
  NEW(ds->k3,ds->nv,double);

  NEW(ds->xa,ds->nv,double);
  NEW(ds->gn,ds->nv,double);
  NEW(ds->y,2*dof,double);

  InitBroyden(ds->nv,ds->nv,&(ds->B));

  ds->mB=GetBroydenMatrixBuffer(&(ds->B));
  ds->fe=GetBroydenRHBuffer(&(ds->B));
  ds->pe=&(ds->fe[ds->nie]); // ds->nv-2*ds->dof

  /* Cache dynamic parameters */

  ds->nl=GetWorldNLinks(wo);

  NEW(ds->l,ds->nl,Tlink*);
  for(i=0;i<ds->nl;i++)
    ds->l[i]=GetWorldLink(i,wo);

  ds->nj=GetWorldNJoints(wo);
  NEW(ds->j,ds->nj,Tjoint*);
  for(i=0;i<ds->nj;i++)
    ds->j[i]=GetWorldJoint(i,wo);

  ds->da=GetWorldActionDimension(GET_WORLD(ds->w));
  
  ds->nj=GetWorldNJoints(wo);
  NEW(ds->effort,ds->nj,double);
  NEW(ds->a2j,ds->da,unsigned int);
  NEW(ds->a2x,ds->da,unsigned int);
  na=0;
  nx=0;
  for(i=0;i<ds->nj;i++)
    {
      k=GetJointDOF(ds->j[i]);
      if (k>0) /* Fix joints may have effort=0 but they are irrelevant */
	{
	  ds->effort[i]=GetJointEffort(ds->j[i]);
	  if (ActuatedJoint(ds->j[i]))
	    {
	      for(j=0;j<k;j++)
		{
		  ds->a2j[na]=i;
		  ds->a2x[na]=nx+j;
		  na++;
		}
	    }
	  nx+=k;
	}
    }

  if (ds->da!=na)
    Error("Wrong action dimension in InitDynamicSpace");
  
  NEW(ds->action,ds->da,double);

  /* Init Inverse Dynamics variables */
  ds->lsSize_ID=ds->npv;
  InitLS(ds->lsSize_ID,ds->lsSize_ID,1,&(ds->A_ID));

  ds->mA_ID=GetLSMatrixBuffer(&(ds->A_ID));
  ds->rhsA_ID=GetLSRHBuffer(&(ds->A_ID));
  ds->solA_ID=GetLSSolutionBuffer(&(ds->A_ID));

  NEW(ds->P,ds->npv*ds->da,double);
  /* end init Inverse Dynamics */
  
  /* Initializing the inverse of the action cost matrix */
  NEW(ds->iR,ds->da*ds->da,double);
  /* Right now we use the identity matrix, but this can be initialized
     taking into account the max effort of the joints. */
  IdentityMatrix(ds->da,ds->iR);
  #if (MAX_J)
    ds->maxJ=(1.0/GetParameter(CT_TAU,pr));
  #endif
  for(j=0;(j<ds->da);j++)
    {
      //ds->iR[RC2INDEX(j,j,ds->da,ds->da)]=pow(ds->effort[ds->a2j[j]],2.0);
      ds->iR[RC2INDEX(j,j,ds->da,ds->da)]=GetJointCost(ds->j[ds->a2j[j]]);
      #if (MAX_J)
        ds->maxJ+=(pow(ds->effort[ds->a2j[j]],2.0)/ds->iR[RC2INDEX(j,j,ds->da,ds->da)]);
      #endif
    }

  /* Init LQR variables */
  ds->lsSize_LQR=2*ds->dof;
  InitLS(ds->lsSize_LQR,ds->lsSize_LQR,1,&(ds->A_LQR));

  ds->mA_LQR=GetLSMatrixBuffer(&(ds->A_LQR));
  ds->rhsA_LQR=GetLSRHBuffer(&(ds->A_LQR));
  ds->solA_LQR=GetLSSolutionBuffer(&(ds->A_LQR));

  /* Init Common variables used in LQR */
  NEW(ds->Gd,2*ds->dof,double);
  NEW(ds->mAt,4*ds->dof*ds->dof,double);
  NEW(ds->iRBt,2*ds->dof*ds->da,double);

  NEW(ds->eA_LQR,ds->lsSize_LQR*ds->lsSize_LQR,double);
  
  NEW(ds->d0_LQR,ds->lsSize_LQR,double);
  
  NEW(ds->x0_LQR,ds->nv,double);
  NEW(ds->x_LQR,ds->nv,double);
  NEW(ds->y_LQR,ds->lsSize_LQR,double);
  NEW(ds->fE_LQR,ds->lsSize_LQR,double);

  NEW(ds->r_LQR,ds->lsSize_LQR,double);
  NEW(ds->dr_LQR,ds->lsSize_LQR,double);
  NEW(ds->rtemp_LQR,ds->lsSize_LQR,double);
  NEW(ds->rnew_LQR,ds->lsSize_LQR,double);
  NEW(ds->d_LQR,ds->lsSize_LQR,double);
  NEW(ds->G_LQR,ds->lsSize_LQR*ds->lsSize_LQR,double);
  NEW(ds->dG_LQR,ds->lsSize_LQR*ds->lsSize_LQR,double);
  NEW(ds->dGtemp_LQR,ds->lsSize_LQR*ds->lsSize_LQR,double);
  NEW(ds->Gtemp_LQR,ds->lsSize_LQR*ds->lsSize_LQR,double);
  NEW(ds->Gnew_LQR,ds->lsSize_LQR*ds->lsSize_LQR,double);

  /* Init the HandC computation (mass matrix,...) */
  InitHandC(pr,wo,ds);
}

unsigned int Getxdot(Tparameters *pr,double *x,double *u,double *a,TDynamicSpace *ds)
{
  ComputeAcceleration(pr,FALSE,x,u,NULL,NULL,ds);
  
  memcpy(a,ds->g,ds->nv*sizeof(double));
  
  return(ds->nv);
}

double *GetInverseActionCostMatrix(TDynamicSpace *ds)
{
  return(ds->iR);
}

double Time2Go(Tparameters *pr,unsigned int tree,
	       Tchart *c,
	       double *t,double *x,double *tg,double *xg,
	       double *de,TDynamicSpace *ds)
{
  double *v,r,t2g,ndt;
  double epsilon;
  double *dt;
  double *T;
  /*
    Please, see the documentation of this function in dynamics.h to understand
    the implementation.
  */
  epsilon=GetParameter(CT_EPSILON,pr);

  /* Projection of dot(x) on the tangent space */
  NEW(dt,ds->dof*2,double);

  /* Vector from start to goal (in tangent space) */
  NEW(v,ds->dof*2,double);
  DifferenceVector(2*ds->dof,tg,t,v);

  /* Euclidean distance between start and goal (in tangent space) */
  *de=Norm(2*ds->dof,v);

  if (*de<epsilon)
    t2g=0.0; /* if the two points are very close, the time to go is null */
  else
    {
      /* Compute dot(x) and its projection in the tangent space */
  
      /* Compute the acceleration for u=0
	 Actually we compute dot(x), which includes dot(q) and ddot(q) */

      /* Acceleration for action 0 (dot(x) for u=0) */
      memset(ds->action,0,ds->da*sizeof(double));
      ComputeAcceleration(pr,FALSE,x,ds->action,c,NULL,ds); /* This computes ds->g=(dq,ddq,do) at x */

      if (ds->nie==0)
	memcpy(dt,ds->g,sizeof(double)*ds->nv);
      else
	{
	  /* Basis of the tangent space */
	  T=GetChartTangentSpace(c);
	    
	  /* Projection of the acceleration at x for action 0 */
	  TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,dt);
	}

      /* Norm of the projection for dot(x) (in tangent space) */
      ndt=Norm(2*ds->dof,dt);

      if (ndt<epsilon)
	t2g=+INF; /* with velocity 0 the time to go is infinite */
      else
	{
	  /* Note that r is Norm(ds->dof,v)*nv*cos(alpha) where
	     alpha is the angle between the two vectors.
	     This is why we consider the cases nv<epsilon and
	     Norm(ds->dof,v)<epsilon  before (to avoid division
	     by zero). */
	  r=GeneralDotProduct(2*ds->dof,v,dt);
	  if (r>0)
	    t2g=((*de)*(*de))/r;
	  else
	    t2g=+INF;
	}
    }

  free(v);
  free(dt);

  return(t2g);
}

double ApproachState(Tparameters *pr,Tintegrator *intFunction,unsigned int tree,
		     double *x,
		     double tolq,double *q_rand,
		     double tolg,double *goal,
		     double *st,double *xb,double *ub,
		     unsigned int *ns,double ***path,double ***actions,double **times,
		     TDynamicSpace *ds)
{
  double minDistance,distance,*xa,*u;
  unsigned int na,nda;
  double intTime,delta,stepTime;
  unsigned int nsStep;
  double **pathStep,**actionsStep,*timesStep;

  nda=(unsigned int)GetParameter(CT_N_DYNAMIC_ACTIONS,pr);
  #if (RANDOM_INT_TIME)
    intTime=randomDouble()*GetParameter(CT_INTEGRATION_TIME,pr);
  #else
    intTime=GetParameter(CT_INTEGRATION_TIME,pr);
  #endif
  delta=GetParameter(CT_DELTA,pr);

  NEW(xa,ds->nv,double);
  NEW(u,ds->da,double);

  minDistance=INF;
  for(na=0;na<nda;na++)
    {
      GetActionFromID(na,u,ds);
      NumericIntegration(pr,intFunction,tree,x,u,delta,intTime,
			 tolq,q_rand,tolg,goal,
			 &nsStep,&pathStep,&actionsStep,&timesStep,
			 &stepTime,xa,ds);

      distance=DistanceTopology(ds->nv,ds->tp,xa,q_rand);

      if (distance<minDistance)
	{
	  memcpy(xb,xa,sizeof(double)*ds->nv);
	  memcpy(ub,u,sizeof(double)*ds->da);

	  *st=stepTime; /* best step time */

	  if (minDistance!=INF)
	    DeleteTrajectory(*ns,*path,*actions,*times);
	  *ns=nsStep;
	  *path=pathStep;
	  *actions=actionsStep;
	  *times=timesStep;

	  minDistance=distance;
	}
      else
	DeleteTrajectory(nsStep,pathStep,actionsStep,timesStep);
    }

  free(xa);
  free(u);

  return(minDistance);
}

boolean kinoRRT(Tparameters *pr,Tintegrator *intFunction,double *pg,
		double *time,
		double *pl,unsigned int *ns,double ***path,
		unsigned int *da,double ***actions,double **times,
		TRRTStatistics *grst,
		TAtlasBase *w,Trrt *rrt)
{
  double *pWithDummies,*pgs,*q_rand;
  unsigned int it,i_near;
  double epsilon;
  boolean pathFound,done,expand2Goal;
  unsigned int lastSample;
  double er,h;
  Tstatistics st; /* used just to measure execution time */
  boolean collision;
  double maxTime,delta;
  unsigned int maxNodes;
  unsigned int samplingMode;
  boolean validSample;
  double dge;
  double *xb,*ub,bt;
  TDynamicSpace ds;
  TJacobian sJ;
  unsigned int nsStep;
  double **pathStep,**actionsStep,*timesStep;

  if (GetRRTMode(rrt)!=ONE_TREE)
    Error("kinoRRT operates on one-directional RRTs");

  if (GetRRTNumNodes(rrt)!=1)
    Error("Wrong number of nodes in the kinoRRT");

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);
  dge=GetParameter(CT_DYNAMIC_GOAL_ERROR,pr);
  delta=GetParameter(CT_DELTA,pr);

  CS_WD_GET_SIMP_JACOBIAN(pr,&sJ,w);

  /* Initialize the dynamic space */
  InitDynamicSpace(pr,FALSE,&sJ,w,&ds);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,w);

  if ((!PointInBoxTopology(NULL,TRUE,ds.nv,pgs,epsilon,ds.tp,&(ds.domain)))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,w)))
    Error("The targed point for the RRT is not in domain");

  if (ds.ne==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,w);
  if (er>epsilon)
    Error("The target point for the RRT is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,w);
  if (collision)
    Warning("The target point for the RRT is in collision");
  free(pWithDummies);

  /* Room for the randomly generated samples (and its correspoinding point
     on the manifold) */
  NEW(q_rand,ds.nv,double);

  /* Room space to save samples */
  NEW(xb,ds.nv,double);
  NEW(ub,ds.da,double);

  done=FALSE;
  it=0;

  InitStatistics(1,0,&st);
  *time=0.0;

  while ((!done)&&(*time<maxTime)&&(GetRRTNumNodes(rrt)<maxNodes))
    {
      if ((RRT_VERBOSE)||((it%1000)==0))
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,GetRRTNumNodes(rrt),*time);
	  fflush(stdout);
	}

      /*******************************************************************/
      /* Sample in ambient space (with bias toward goal) */
      do {
	/* Generate a random sample */
	expand2Goal=RRTSample(samplingMode,START2GOAL,(EXPLORATION_RRT?NULL:pgs),
			      q_rand,NULL,rrt);
	/* Check the sample is valid */
	validSample=RRTValidateSample(pr,q_rand,START2GOAL,expand2Goal,NULL,INF,
				      &h,&i_near,NULL,rrt);

      	*time=GetElapsedTime(&st);
      } while((!validSample)&&(*time<maxTime));

      if (*time<maxTime)
	{
	  /********************************************************************/
	  /* Extend the RRT from q_near to q_rand simulting different actions */
	  ApproachState(pr,intFunction,START2GOAL,GetRRTNode(i_near,rrt),
			(expand2Goal?dge:delta),q_rand,dge,pgs,
			&bt,xb,ub,
			&nsStep,&pathStep,&actionsStep,&timesStep,
			&ds);

	  if (!PointInRRT(epsilon,START2GOAL,xb,rrt))
	    {
	      AddNodeToRRT(pr,START2GOAL,i_near,xb,NULL,&lastSample,NULL,0,0,FALSE,ub,bt,
			   (nsStep>0?nsStep-1:0),pathStep,actionsStep,timesStep,NULL,rrt);
	      /* The last intermediate step is the one in the new RRT node -> we do not have to keep it */
	      if (nsStep>0)
		{
		  free(pathStep[nsStep-1]);
		  free(actionsStep[nsStep-1]);
		}

	      done=(DistanceTopology(ds.nv,ds.tp,xb,pgs)<dge);
	    }
	  else
	    DeleteTrajectory(nsStep,pathStep,actionsStep,timesStep);

	  *time=GetElapsedTime(&st);
	  it++;
	}
    }

  fprintf(stderr,"Final number of samples: %u\n",GetRRTNumNodes(rrt));

  /* Reconstruct the path (if any) */
  pathFound=PathStart2GoalInRRT(pr,pgs,NO_UINT,NO_UINT,pl,NULL,ns,path,actions,times,rrt);
  *da=ds.da;

  /* Release memory */
  DeleteStatistics(&st);

  free(q_rand);
  free(pgs);
  free(xb);
  free(ub);
  DeleteJacobian(&sJ);
  DeleteDynamicSpace(&ds);
  
  return(pathFound);
}

boolean kinobiRRT(Tparameters *pr,Tintegrator *intFunction,double *pg,
		  double *time,
		  double *pl,unsigned int *ns,double ***path,
		  unsigned int *da,double ***actions,double **times,
		  TRRTStatistics *grst,
		  TAtlasBase *w,Trrt *rrt)
{
  double *pWithDummies,*pgs,*q_rand;
  unsigned int it,i_near;
  double epsilon;
  boolean pathFound,done,expand2Goal;
  unsigned int lastSample,lastSample2;
  double er,h;
  Tstatistics st; /* used just to measure execution time */
  boolean collision;
  double maxTime,delta;
  unsigned int maxNodes;
  unsigned int samplingMode;
  boolean validSample;
  unsigned int t1,t2;
  double dge;
  double *xb,*ub,bt;
  TDynamicSpace ds;
  TJacobian sJ;
  unsigned int nsStep;
  double **pathStep,**actionsStep,*timesStep;

  if (GetRRTMode(rrt)!=TWO_TREES)
    Error("dynamicbiRRT operates on bidirectional RRTs");

  if (GetRRTNumNodes(rrt)!=2)
    Error("Wrong number of nodes in the dynamicbiRRT");

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);
  dge=GetParameter(CT_DYNAMIC_GOAL_ERROR,pr);
  delta=GetParameter(CT_DELTA,pr);

  CS_WD_GET_SIMP_JACOBIAN(pr,&sJ,w);

  /* Initialize the dynamic space */
  InitDynamicSpace(pr,FALSE,&sJ,w,&ds);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,w);

  if ((!PointInBoxTopology(NULL,TRUE,ds.nv,pgs,epsilon,ds.tp,&(ds.domain)))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,w)))
    Error("The targed point for the RRT is not in domain");

  if (ds.ne==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,w);
  if (er>epsilon)
    Error("The target point for the RRT is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,w);
  if (collision)
    Warning("The target point for the RRT is in collision");
  free(pWithDummies);

  /* Room for the randomly generated samples (and its correspoinding point
     on the manifold) */
  NEW(q_rand,ds.nv,double);

  /* Room space to save samples */
  NEW(xb,ds.nv,double);
  NEW(ub,ds.da,double);

  /* The two trees. This is only used for bidirectiononal RRTs. In norma
     RRTs only the START2GOAL tree is extended*/
  t1=START2GOAL;
  t2=GOAL2START;

  done=FALSE;
  it=0;

  InitStatistics(1,0,&st);
  *time=0.0;

  while ((!done)&&(*time<maxTime)&&(GetRRTNumNodes(rrt)<maxNodes))
    {
      if ((RRT_VERBOSE)||((it%1000)==0))
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,GetRRTNumNodes(rrt),*time);
	  fflush(stdout);
	}

      /*******************************************************************/
      /* Sample in ambient space (withOUT bias toward goal, the bias is in the connection to other tree) */
      do {
	/* Generate a random sample */
	expand2Goal=RRTSample(samplingMode,t1,NULL,q_rand,NULL,rrt);
	/* Check the sample is valid */
	validSample=RRTValidateSample(pr,q_rand,t1,expand2Goal,NULL,INF,
				      &h,&i_near,NULL,rrt);

      	*time=GetElapsedTime(&st);
      } while((!validSample)&&(*time<maxTime));

      if (*time<maxTime)
	{
	  /********************************************************************/
	  /* Extend the RRT from q_near to q_rand simulting different actions */
	  ApproachState(pr,intFunction,t1,GetRRTNode(i_near,rrt),
			(expand2Goal?dge:delta),q_rand,dge,pgs,
			&bt,xb,ub,
			&nsStep,&pathStep,&actionsStep,&timesStep,
			&ds);

	  if (!PointInRRT(epsilon,t1,xb,rrt))
	    {
	      AddNodeToRRT(pr,t1,i_near,xb,NULL,&lastSample,NULL,0,0,FALSE,ub,bt,
			   (nsStep>0?nsStep-1:0),pathStep,actionsStep,timesStep,NULL,rrt);
	      /* The last intermediate step is the one in the new RRT node -> we do not have to keep it */
	      if (nsStep>0)
		{
		  free(pathStep[nsStep-1]);
		  free(actionsStep[nsStep-1]);
		}

	      // we will check connection to the other tree later
	      //done=(DistanceTopology(ds.nv,ds.tp,xb,pgs)<dge);
	      /* The last node added to t1 is used as random sample */
	      memcpy(q_rand,GetRRTNode(lastSample,rrt),ds.nv*sizeof(double));

	      /* Find NN in t2 from the last sample in t1 */
	      i_near=GetRRTNN(t2,q_rand,rrt);

	      /*******************************************************************/
	      /* Extend the RRT t2 towards the last sample added to t1 (only if we have added a point in the RRT) */
	      ApproachState(pr,intFunction,t2,GetRRTNode(i_near,rrt),
			    (expand2Goal?dge:delta),q_rand,dge,pgs,
			    &bt,xb,ub,
			    &nsStep,&pathStep,&actionsStep,&timesStep,
			    &ds);

	      if (!PointInRRT(epsilon,t2,xb,rrt))
		{
		  AddNodeToRRT(pr,t2,i_near,xb,NULL,&lastSample2,NULL,0,0,FALSE,ub,bt,
			       (nsStep>0?nsStep-1:0),pathStep,actionsStep,timesStep,NULL,rrt);
		  /* The last intermediate step is the one in the new RRT node -> we do not have to keep it */
		  if (nsStep>0)
		    {
		      free(pathStep[nsStep-1]);
		      free(actionsStep[nsStep-1]);
		    }
		  /*******************************************************************/
		  /* Check whether we connect the '2nd' tree (xb) to the last node added to the '1st' tree (q_rand) */
		  done=(DistanceTopology(ds.nv,ds.tp,q_rand,xb)<dge);
		}
	      else
		DeleteTrajectory(nsStep,pathStep,actionsStep,timesStep);
	    }
	  else
	    DeleteTrajectory(nsStep,pathStep,actionsStep,timesStep);

	  /*******************************************************************/
	  /* Swap the trees (t1 and t2) */
	  if ((it%2)==0)
	    {
	      t1=GOAL2START;
	      t2=START2GOAL;
	    }
	  else
	    {
	      t1=START2GOAL;
	      t2=GOAL2START;
	    }

	  *time=GetElapsedTime(&st);
	  it++;
	}
    }

  fprintf(stderr,"Final number of samples: %u\n",GetRRTNumNodes(rrt));

  /* Reconstruct the path (if any) */
  pathFound=PathStart2GoalInRRT(pr,pgs,lastSample,lastSample2,pl,NULL,ns,path,actions,times,rrt);
  *da=ds.da;

  /* Release memory */
  DeleteStatistics(&st);

  free(q_rand);
  free(pgs);
  free(xb);
  free(ub);
  DeleteJacobian(&sJ);
  DeleteDynamicSpace(&ds);

  return(pathFound);
}

boolean kinoEST(Tparameters *pr,Tintegrator *intFunction,double *pg,
		double *time,
		double *pl,unsigned int *ns,double ***path,
		unsigned int *da,double ***actions,double **times,
		TRRTStatistics *grst,TAtlasBase *w,Trrt *rrt)
{
  double *pWithDummies,*pgs;
  unsigned int it,i_near,i;
  double epsilon,gamma,c;
  boolean pathFound,done;
  unsigned int lastSample,numNodes;
  double er;
  Tstatistics st; /* used just to measure execution time */
  boolean collision;
  double maxTime,intTime,actionTime,delta;
  unsigned int maxNodes;
  unsigned int nda,n,*nn;
  double dge;
  double *xNext,*u,stepTime;
  TDynamicSpace ds;
  TJacobian sJ;
  double sumCost,r,s1;
  unsigned int nsStep;
  double **pathStep,**actionsStep,*timesStep;

  if (GetRRTMode(rrt)!=ONE_TREE)
    Error("kinoEST operates on one-directional ESTs");

  if (GetRRTNumNodes(rrt)!=1)
    Error("Wrong number of nodes in the kinoEST");

  SetRRTNodeCost(0,0,1,rrt);
  sumCost=1;

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  gamma=GetParameter(CT_GAMMA,pr);
  intTime=GetParameter(CT_INTEGRATION_TIME,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);
  nda=(unsigned int)GetParameter(CT_N_DYNAMIC_ACTIONS,pr);
  dge=GetParameter(CT_DYNAMIC_GOAL_ERROR,pr);
  delta=GetParameter(CT_DELTA,pr);

  CS_WD_GET_SIMP_JACOBIAN(pr,&sJ,w);

  /* Initialize the dynamic space */
  InitDynamicSpace(pr,FALSE,&sJ,w,&ds);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,w);

  if ((!PointInBoxTopology(NULL,TRUE,ds.nv,pgs,epsilon,ds.tp,&(ds.domain)))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,w)))
    Error("The targed point for the EST is not in domain");

  if (ds.ne==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,w);
  if (er>epsilon)
    Error("The target point for the EST is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,w);
  if (collision)
    Warning("The target point for the EST is in collision");
  free(pWithDummies);

  /* Room space to save samples */
  NEW(xNext,ds.nv,double);
  NEW(u,ds.da,double);

  done=FALSE;
  it=0;

  InitStatistics(1,0,&st);
  *time=0.0;
  numNodes=GetRRTNumNodes(rrt);

  while ((!done)&&(*time<maxTime)&&(numNodes<maxNodes))
    {
      if ((RRT_VERBOSE)||((it%1000)==0))
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,numNodes,*time);
	  fflush(stdout);
	}

      /*******************************************************************/
      /* Sample a node at random in the tree */

      r=sumCost*randomDouble();

      i_near=0;
      s1=GetRRTNodeCost(0,rrt);
      while((r>s1)&&(i<(numNodes-1)))
	{
	  i_near++;
	  s1+=GetRRTNodeCost(i_near,rrt);
	}

      /*******************************************************************/
      /* Extend the EST */

      /* using a random action */
      GetActionFromID(randomMax(nda-1),u,&ds);

      /* and executing it for a random time */
      actionTime=randomDouble()*intTime;

      NumericIntegration(pr,intFunction,START2GOAL,GetRRTNode(i_near,rrt),u,delta,actionTime,
			 dge,pgs,0,NULL,
			 &nsStep,&pathStep,&actionsStep,&timesStep,
			 &stepTime,xNext,&ds);

      if ((stepTime>0)&&(!PointInRRT(epsilon,START2GOAL,xNext,rrt)))
	{

	  AddNodeToRRT(pr,START2GOAL,i_near,xNext,NULL,&lastSample,NULL,0,0,FALSE,u,stepTime,
		       (nsStep>0?nsStep-1:0),pathStep,actionsStep,timesStep,NULL,rrt);
	  /* The last intermediate step is the one in the new RRT node -> we do not have to keep it */
	  if (nsStep>0)
	    {
	      free(pathStep[nsStep-1]);
	      free(actionsStep[nsStep-1]);
	    }

	  numNodes=GetRRTNumNodes(rrt);

	  GetRRTNNInBall(START2GOAL,xNext,gamma,&n,&nn,rrt);

	  c=1.0/((double)n+1);
	  SetRRTNodeCost(lastSample,0,c,rrt);
	  sumCost+=c;

	  for(i=0;i<n;i++)
	    {
	      c=GetRRTNodeCost(nn[i],rrt);
	      SetRRTNodeCost(nn[i],0,c/(1+c),rrt);
	      sumCost-=c*c/(1+c);
	    }

	  if (n>0) free(nn);

	  done=(DistanceTopology(ds.nv,ds.tp,xNext,pgs)<dge);
	}
      else
	DeleteTrajectory(nsStep,pathStep,actionsStep,timesStep);

      *time=GetElapsedTime(&st);
      it++;

    }

  fprintf(stderr,"Final number of samples: %u\n",numNodes);

  /* Reconstruct the path (if any) */
  pathFound=PathStart2GoalInRRT(pr,pgs,NO_UINT,NO_UINT,pl,NULL,ns,path,actions,times,rrt);
  *da=ds.da;


  /* Release memory */
  DeleteStatistics(&st);

  free(pgs);
  free(xNext);
  free(u);
  DeleteJacobian(&sJ);
  DeleteDynamicSpace(&ds);

  return(pathFound);
}

/*****************************************************************************************************************/

void ComputeInverseDynamics(Tparameters *pr,boolean hasIE,Tchart *c,double *x,double *acc,double *u,TDynamicSpace *ds)

{
  unsigned int i;
  #if (!HandC_FJH)
    double epsilon;

    epsilon=GetParameter(CT_EPSILON,pr);
  #endif
    
  for(i=0;i<ds->npv;i++)
    ds->pos[i]=x[ds->ndxPV[i]];

  /* no action */
  memset(u,0,sizeof(double)*ds->da);
  
  /* Fill in the rhs term: M*q_dotdot - Q(u=0) */
  HandC(pr,x,u,ds->Mm,ds->Qa,FALSE,FALSE,ds);
  
  /* M(q)*q_dotdot */
  MatrixVectorProduct(ds->npv,ds->npv,ds->Mm,acc,ds->rhsA_ID);
  /* M*q_dotdot - Q(u=0) */
  SubtractVector(ds->npv,ds->rhsA_ID,ds->Qa);

  /*Fill the LHS: [P Phi_q^T] */
  memset(ds->mA_ID,0,sizeof(double)*ds->lsSize_ID*ds->lsSize_ID);
  EvaluatePermutation(ds);
      
  SubMatrixFromMatrix(ds->npv,ds->da,ds->P,0,0,ds->lsSize_ID,ds->lsSize_ID,ds->mA_ID); // P matrix

  if (ds->nipe>0)
    {
      #if (HandC_FJH)
        /* HandC already computed the (non-transposed) Jacobian. Just use it */
        SubMatrixFromTMatrix(ds->nipe,ds->npv,ds->Jp,0,ds->da,ds->lsSize_ID,ds->lsSize_ID,ds->mA_ID);
      #else
        /* This computes the transposed Jocobian */
        GetPositionJacobian(ds->pos,x,epsilon,hasIE,c,ds);
        SubMatrixFromMatrix(ds->npv,ds->nipe,ds->Jp,0,ds->da,ds->lsSize_ID,ds->lsSize_ID,ds->mA_ID);
      #endif
    }
  
  /* Solve Inverse Dynamics */
  if (LSSolve(&(ds->A_ID)))
    Error("Singular linear system in InverseDynamics");

  /* Use one or another */
  //u = ds->solA_ID;
  memcpy(u,ds->solA_ID,sizeof(double)*ds->da);
}

unsigned int NextDynamicState(Tparameters *pr,unsigned int tree,
			      double delta,boolean gc,
			      double *xn,double *yn,Tchart *c,double *u,
			      double *h,double hmax,double *x,unsigned int *it,TDynamicSpace *ds)
{
  double e,epsilon,*T;
  unsigned int maxIt;
  unsigned int out;
  boolean negLag;
  
  epsilon=GetParameter(CT_EPSILON,pr);
  maxIt=GetParameter(CT_MAX_NEWTON_ITERATIONS,pr);
  negLag=(GetParameter(CT_NEG_LM,pr)>0);

  /* If we have to compensate gravity */
  if (gc)
    {
      unsigned int i;
      
      memset(ds->g,0,sizeof(double)*ds->nv);
      memset(&ds->xa,0,sizeof(double)*ds->nv);
      for(i=0;i<ds->npv;i++)
	ds->xa[ds->ndxPV[i]]=x[ds->ndxPV[i]];

      ComputeInverseDynamics(pr,FALSE,c,ds->xa,ds->g,ds->action,ds);
      //u = u + gravity correction;
      AccumulateVector(ds->da,u,ds->action);

      for(i=0;i<ds->da;i++)
	{
	  e=ds->effort[ds->a2j[i]];
	  if (ds->action[i]>e)
	    ds->action[i]=e;
	  if (ds->action[i]<-e)
	    ds->action[i]=-e;
	}
    }
  else
    memcpy(ds->action,u,sizeof(double)*ds->da);

  ResetBroyden(&(ds->B));

  /* Initialize the dynamic data for the current state and action
     Important: This evaluates the Jacobian */
  ComputeAcceleration(pr,gc,xn,ds->action,c,NULL,ds);
  DynamicStepCtResidue(ds);
    
  /* Initialize the Broyden matrix */
  /* The full Jacobian is already obtained as a by-product of the ComputeAcceleration */

  /* Adjust the integration step */
  if (ds->nie==0)
    *h=delta/Norm(ds->nv,ds->g);
  else
    {
      T=GetChartTangentSpace(c);      
      TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,ds->gy);
      *h=delta/Norm(2*ds->dof,ds->gy);
    }
    
  if (*h>hmax)
    *h=hmax;
  
  #if (DEBUG_DYNAMICS>1)
      /* The matrix in the linear system to compute acceleration */
    fprintf(stderr,"          h=%.16f  (%f)\n",*h,delta);
  #endif

  if (tree==GOAL2START)
    *h=-*h; /* Backward integration in time */
  
  /* Initial estimation of the solution */
  #if (START_BROYDEN_ON_MANIFOLD)
    /* Euler in tangen space + Projection to manifold */
    SumVectorScale(2*ds->dof,yn,*h,ds->gy,ds->gy);
    if (Chart2Manifold(pr,ds->sJ,ds->gy,ds->tp,xn,x,c)==INF)
      SumVectorScale(ds->nv,xn,*h,ds->g,x); /* Euler in ambient */
  #else
    /* Euler in ambient space:  x = xn + h*g  */
    SumVectorScale(ds->nv,xn,*h,ds->g,x);
  #endif
  
  /* Set up the Broyden's residue at the initial estimation (this requires h!!) */
  ComputeAcceleration(pr,TRUE,x,ds->action,c,ds->J,ds); /* We changed 'x' -> recompute the acceleration to get a correct residue */
  e=DynamicStepResidue(pr,*h,yn,x,c,ds); /* this can only be used after calling DynamicStepCtResidue and ComputeAcceleration */

  /* Build 1st guess of Broyden jacobian at the initial estiamtion: [F_x; U0^t] 
     and fix the integration step: steps must be of size delta (approx) in tangent space
     U0^T*y is acc vector in tangent space */
  if (ds->nie==0)
    IdentityMatrix(ds->nv,ds->mB);
  else
    {
      SubMatrixFromMatrix(ds->nv-2*ds->dof,ds->nv,ds->J,0,0,ds->nv,ds->nv,ds->mB);
      T=GetChartTangentSpace(c);
      SubMatrixFromTMatrix(ds->nv,2*ds->dof,T,ds->nv-2*ds->dof,0,ds->nv,ds->nv,ds->mB);
    }
  
  #if (DEBUG_DYNAMICS>1)
    fprintf(stderr,"\n");
    /* Broyden's initial conditions */
    fprintf(stderr,"          Broyden iteration -------------------------------------------------------------\n");
    PrintVector(stderr,"            x0",ds->nv,GetChartCenter(c));
    if (ds->nipe>0)
      PrintTMatrix(stderr,"            T",ds->nv,2*ds->dof,T);
    PrintMatrix(stderr,"            B",ds->nv,ds->nv,ds->mB);
    PrintVector(stderr,"            xn",ds->nv,xn); /*  == x initital estimation of next state */
    PrintVector(stderr,"            gn",ds->nv,ds->gn); /* == initial g */
    PrintVector(stderr,"            yn",2*ds->dof,yn);
    PrintVector(stderr,"            res",ds->nv,ds->fe);
    fprintf(stderr,"            e: %.19f\n",e);
  #endif
    
  *it=0;
  while((*it<maxIt)&&(e>epsilon))
    {
      #if (DEBUG_DYNAMICS>1) 
	fprintf(stderr,"          Iteration %u\n",*it);
      #endif

      BroydenStep(epsilon,ds->tp,x,&(ds->B)); /* This updates x */
      
      /* Recompute Broyden's residue */
      ComputeAcceleration(pr,TRUE,x,ds->action,c,NULL,ds); /* this updates g and possibly the evaluation
							      of the funcionts, which are then used when 
							      computing the residue */

      e=DynamicStepResidue(pr,*h,yn,x,c,ds);
      
      if ((*it>0)&&(*it<maxIt)&&(e>epsilon))
	BroydenUpdateJacobian(epsilon,&(ds->B));
      	
      #if (DEBUG_DYNAMICS>1)
        fprintf(stderr,"              it: %u\n",*it);
        fprintf(stderr,"              h=%f\n",*h);
        PrintMatrix(stderr,"              B",ds->nv,ds->nv,ds->mB);
	PrintVector(stderr,"              x",ds->nv,x);
        PrintVector(stderr,"              g",ds->nv,ds->g);
	PrintVector(stderr,"              res",ds->nv,ds->fe);
	fprintf(stderr,"              e=%.15g vs %g\n",e,epsilon);
      #endif

      (*it)++;
    }

  if (*it<maxIt)
    {
      if (ValidState(negLag,ds))
	{
	  out=0;
	  
	  #if (DEBUG_DYNAMICS>1)
	    fprintf(stderr,"          Final error=%g (%u)\n",e,*it-1);
	  #endif
	}
      else
	{
	  out=2;

	  #if (DEBUG_DYNAMICS>1)
	    fprintf(stderr,"          Invalid dynamic state\n");
	  #endif
	}
    }
  else
    {
      #if (DEBUG_DYNAMICS>1)
        fprintf(stderr,"          Broyden diverged\n");
      #endif
	
      /* Use explicit RK4 method as a fallback method */
      out=NextDynamicStateLocalRK4(pr,tree,delta,xn,yn,c,u,h,hmax,x,ds);
	  
      #if (DEBUG_DYNAMICS>1)
        if (out==0)
          fprintf(stderr,"          Explicit method succeeded\n");
        else
          fprintf(stderr,"          Dynamic error\n");
      #endif

    }
  
  /* just in case we are integrating backward */
  *h=fabs(*h);

  return(out);
}

unsigned int NextDynamicStateLocalEuler(Tparameters *pr,unsigned int tree,
					double delta,
					double *xn,double *yn,Tchart *c,double *u,
					double *h,double hmax,double *x,TDynamicSpace *ds)
{
  unsigned int out;
      
  if (ds->nie==0)
    out=NextDynamicStateEuler(pr,tree,h,delta,xn,u,x,ds);
  else
    {
      boolean negLag;
      double *T;

      negLag=(GetParameter(CT_NEG_LM,pr)>0);
      
      /* Compute acceleration */
      ComputeAcceleration(pr,FALSE,xn,u,c,NULL,ds);
      
      if (ValidState(negLag,ds))
	{
          /* Project acceleration to tangent space */
          T=GetChartTangentSpace(c);
	  TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,ds->gy);
	  
	  /* Adjust integration step so that consecutive points in tangent
	     space are at distance 'delta' */
	  *h=delta/Norm(2*ds->dof,ds->gy);
	  if (*h>hmax)
	    *h=hmax;
	  
	  if (tree==GOAL2START)
	    *h=-*h;
      
	  /* Apply Euler in tangent space */
	  SumVectorScale(2*ds->dof,yn,*h,ds->gy,ds->y);
	  
	  /* just in case we are integrating backward */
	  *h=fabs(*h);

	  /* Project to the manifold */
	  if (Chart2Manifold(pr,ds->sJ,ds->y,ds->tp,xn,x,c)<INF)
	    out=0;
	  else
	    out=1;
	}
      else
	out=2;
    }
  
  return(out);
}

unsigned int NextDynamicStateLocalRK4(Tparameters *pr,unsigned int tree,
				      double delta,
				      double *xn,double *yn,Tchart *c,double *u,
				      double *h,double hmax,double *x,TDynamicSpace *ds)
{
  unsigned int out;
  
  if (ds->nie==0)
    out=NextDynamicStateRK4(pr,tree,h,delta,xn,u,x,ds);
  else
    {
      boolean negLag;
      double *T;

      negLag=(GetParameter(CT_NEG_LM,pr)>0);
  
      /* Compute acceleration */
      /* k1 = f(x,u) */
      ComputeAcceleration(pr,FALSE,xn,u,c,NULL,ds);

      if (ValidState(negLag,ds))
	{
	  /* Project acceleration to tangent space */
	  T=GetChartTangentSpace(c);
	  TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,ds->k1);

	  /* Adjust integration step so that consecutive points in tangent
	     space are at distance 'delta'. This is just an estimation assuming
	     all the accelerations are of similar norm. */
	  *h=delta/Norm(2*ds->dof,ds->k1);
	  if (*h>hmax)
	    *h=hmax;
	  
	  if (tree==GOAL2START)
	    *h=-*h;
      
	  /* k2 = f(yn+h/2*k1,u) */
	  SumVectorScale(2*ds->dof,yn,(*h)/2,ds->k1,ds->y);
	  if (Chart2Manifold(pr,ds->sJ,ds->y,ds->tp,xn,x,c)<INF)
	    {
	      ComputeAcceleration(pr,TRUE,x,u,c,NULL,ds);
	      TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,ds->k2);

	      /* k3 = f(yn+h/2*k2,u) */
	      SumVectorScale(2*ds->dof,yn,(*h)/2,ds->k2,ds->y);
	      if (Chart2Manifold(pr,ds->sJ,ds->y,ds->tp,xn,x,c)<INF)
		{
		  ComputeAcceleration(pr,TRUE,x,u,c,NULL,ds);
		  TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,ds->k3);

		  /* k4 = f(yn+h*k3,u)  (k4 stored in ds->gy) */
		  SumVectorScale(2*ds->dof,yn,(*h),ds->k3,ds->y);
		  if (Chart2Manifold(pr,ds->sJ,ds->y,ds->tp,xn,x,c)<INF)
		    {
		      ComputeAcceleration(pr,TRUE,x,u,c,NULL,ds);
		      TMatrixVectorProduct(ds->nv,2*ds->dof,T,ds->g,ds->gy);

		      /* y = yn + (1/6*h) * (k1 +2*k2 +2*k3 +k4) */
		      SumVector(2*ds->dof,ds->gy,ds->k1,ds->y); // y = k4 + k1
		      SumVectorScale(2*ds->dof,ds->y,2.0,ds->k2,ds->y); // y = k4 + k1 + 2*k2
		      SumVectorScale(2*ds->dof,ds->y,2.0,ds->k3,ds->y); // y = k4 + k1 + 2*k2 + 2*k3
		      SumVectorScale(2*ds->dof,yn,(*h)/6.0,ds->y,ds->y);/* y = yn + h/6 * y */
		  
		      /* Project to the manifold */
		      if (Chart2Manifold(pr,ds->sJ,ds->y,ds->tp,xn,x,c)<INF)
			out=0;
		      else
			out=1;
		    }
		  else
		    out=1;
		}
	      else
		out=1;
	    }
	  else
	    out=1;
	  
	  /* just in case we are integrating backward */
	  *h=fabs(*h);
	}
      else
	out=2;
    }

  /* Use Euler method as a fallback method */
  if (out==1)
    out=NextDynamicStateLocalEuler(pr,tree,delta,xn,yn,c,u,h,hmax,x,ds);
  
  return(out);
}

unsigned int NextDynamicStateEuler(Tparameters *pr,unsigned int tree,double *h,double delta,
				   double *x,double *u,double *xNew,
				   TDynamicSpace *ds)
{
  unsigned int out;
  boolean negLag;

  negLag=(GetParameter(CT_NEG_LM,pr)>0);
  
  /* Compute acceleration */
  ComputeAcceleration(pr,FALSE,x,u,NULL,NULL,ds);

  if (ValidState(negLag,ds))
    {
      /* If we have a limit in the distance between consecutive steps */
      if (delta<INF)
	{
	  double n;

	  n=Norm(ds->nv,ds->g);
	  if ((*h)*n>delta)
	    *h=delta/n;
	}
      
      if (tree==GOAL2START)
	*h=-*h;
 
      /* Forward Euler Method */
      /* x_{n+1}=x_n+h*g(x_n,u) */
      SumVectorScale(ds->nv,x,*h,ds->g,xNew);

      /* just in case we are integrating backward */
      *h=fabs(*h);
  
      out=0;
    }
  else
    out=1;
  
  return(out);
}

unsigned int NextDynamicStateRK4(Tparameters *pr,unsigned int tree,double *h,double delta,
				 double *x,double *u,double *xNew,
				 TDynamicSpace *ds)
{
  unsigned int out;
  boolean negLag;

  negLag=(GetParameter(CT_NEG_LM,pr)>0);

  /* Runge Kutta */
  /* k1 = f(x,u) */
  ComputeAcceleration(pr,FALSE,x,u,NULL,NULL,ds);

  if (ValidState(negLag,ds))
    {
      if (delta<INF)
	{
	  double n;

	  n=Norm(ds->nv,ds->g);
	  if ((*h)*n>delta)
	    *h=delta/n;
	}

      if (tree==GOAL2START)
	*h=-*h;
      
      memcpy(ds->k1,ds->g,sizeof(double)*ds->nv);

      /* k2 = f(x+h/2*k1,u) */
      SumVectorScale(ds->nv,x,(*h)/2,ds->k1,xNew);
      ComputeAcceleration(pr,TRUE,xNew,u,NULL,NULL,ds);
      memcpy(ds->k2,ds->g,sizeof(double)*ds->nv);

      /* k3 = f(x+h/2*k2,u) */
      SumVectorScale(ds->nv,x,(*h)/2,ds->k2,xNew);
      ComputeAcceleration(pr,TRUE,xNew,u,NULL,NULL,ds);
      memcpy(ds->k3,ds->g,sizeof(double)*ds->nv);

      /* k4 = f(x+h*k3,u)  (k4 stored in ds->g) */
      SumVectorScale(ds->nv,x,(*h),ds->k3,xNew);
      ComputeAcceleration(pr,TRUE,xNew,u,NULL,NULL,ds);

      /* xNew = x + (1/6*h) * (k1 +2*k2 +2*k3 +k4) */
      SumVector(ds->nv,ds->g,ds->k1,xNew); // xa = k4 + k1
      SumVectorScale(ds->nv,xNew,2.0,ds->k2,xNew); // xNew = k4 + k1 + 2*k2
      SumVectorScale(ds->nv,xNew,2.0,ds->k3,xNew); // xNew = k4+ k1 + 2*k2 + 2*k3
      SumVectorScale(ds->nv,x,(*h)/6.0,xNew,xNew);/* xNew = x + h/6 * xa */

      /* just in case we are integrating backward */
      *h=fabs(*h);
  
      out=0;
    }
  else
    out=1;
  
  return(out);
}

unsigned int NumericIntegration(Tparameters *pr,Tintegrator *intFunction,
				unsigned int tree,
				double *xn,double *u,double delta,double intTime,
				double tolq,double *q_rand,double tolg,double *goal,
				unsigned int *ns,double ***path,double ***actions,double **times,
				double *time,double *x,TDynamicSpace *ds)
{
  double epsilon;
  unsigned int out;
  double h,hmax;
  boolean inCollision;
  double *xTemp;
  boolean reached;
  boolean traj;
  unsigned int ms;

  NEW(xTemp,ds->nv,double);

  epsilon=GetParameter(CT_EPSILON,pr);

  /* The current state: can not modify 'xn' since it may be used
     externally */
  memcpy(x,xn,sizeof(double)*ds->nv);

  if ((ns!=NULL)&&(path!=NULL)&&(actions!=NULL)&&(times!=NULL))
    {
      InitTrajectory(&ms,ns,path,ds->da,actions,times);
      traj=TRUE;
    }
  else
    traj=FALSE;

  *time=0.0;
  out=0;
  reached=FALSE;
  while ((*time<intTime)&&(out==0)&&(!reached))
    {
      /* integration step */
      /* Use the step size given by delta, only reduce it if we exceed hmax */
      h=delta;
      hmax=intTime-(*time);
      if (h>hmax)
	h=hmax;

      /* Compute acceleration using, e.g., the Euler or RK4 methods */
      out=intFunction(pr,tree,&h,INF,x,u,xTemp,ds);


      if (out==0)
	{
	  if (!PointInBoxTopology(NULL,FALSE,ds->nv,xTemp,epsilon,ds->tp,&(ds->domain)))
	    out=2;
	  else
	    {
	      CS_WD_IN_COLLISION(inCollision,pr,xTemp,x,ds->w);
	      if (inCollision)
		out=2;
	      else
		{
		  memcpy(x,xTemp,sizeof(double)*ds->nv);
		  *time+=h;

		  if (traj)
		    AddStep2Trajectory(ds->nv,x,ds->nv,NULL,u,h,&ms,ns,path,ds->da,actions,times);

		  if (goal!=NULL)
		    reached=(DistanceTopology(ds->nv,ds->tp,x,goal)<tolg);

		  if ((!reached)&&(q_rand!=NULL))
		    reached=(DistanceTopology(ds->nv,ds->tp,x,q_rand)<tolq);
		}
	    }
	}
      else
	out=1;
    }
  free(xTemp);

  return(out);
}

void Simulate(Tparameters *pr,Tintegrator *intFunction,unsigned int da,double *u,double *s,
	      unsigned int steps,unsigned int *ns,double ***path,double ***actions,
	      double **times,TDynamicSpace *ds)
{
  unsigned int i,nv,nvs;
  boolean *systemVars,blocked;
  double intTime;
  unsigned int ms;
  double *o,*x,*xn,*pWithDummies,h,delta;

  intTime=GetParameter(CT_INTEGRATION_TIME,pr);
  delta=GetParameter(CT_DELTA,pr);

  /* relevant variables in the original system */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,ds->w);
  if (nv!=ds->nv)
    Error("Wrong state space dimension in Simulate");
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }

  /* Initialize the collision detection system */
  CS_WD_INIT_CD(pr,1,ds->w);

  /* Dimension of the action space */
  if (da!=ActionSpaceDimension(ds))
    Error("Wrong action space dimension in AtlasRRTSimulate");

  /* Empty trajectory */
  InitTrajectory(&ms,ns,path,da,actions,times);

  /* Set the first step in the trajectory with no action and time 0 */
  AddStep2Trajectory(nv,s,nvs,systemVars,NULL,0.0,&ms,ns,path,da,actions,times);

  /* Generate the internal state form the given initial state */
  CS_WD_REGENERATE_SOLUTION_POINT(pr,s,&pWithDummies,ds->w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&xn,ds->w);
  free(pWithDummies);

  /* Space for the next state */
  NEW(x,ds->nv,double);

  /* We repeat integration steps of time maxIntTime and only
     take the point at the end of the step. */
  i=0;
  blocked=FALSE;
  while ((i<steps)&&(!blocked))
    {
      #if (DEBUG_DYNAMICS>0)
        fprintf(stderr,"Simulation step: %u\n",i);
      #endif

      /* Integrate for intTime (or until obstacles or invalid dynamic state) */
      blocked=(NumericIntegration(pr,intFunction,START2GOAL,xn,u,delta,intTime,
				  0.0,NULL,0.0,NULL,
				  NULL,NULL,NULL,NULL,
				  &h,x,ds)>0);

      if (!blocked)
	{
	  /* Generate the full state and add it to the trajectory */
	  CS_WD_REGENERATE_ORIGINAL_POINT(pr,x,&o,ds->w);
	  AddStep2Trajectory(nv,o,nvs,systemVars,u,h,&ms,ns,path,da,actions,times);
	  free(o);

	  /* continue the integration from the next state: xn <- x */
	  memcpy(xn,x,sizeof(double)*ds->nv);

	  #if (DEBUG_DYNAMICS>0)
	    fprintf(stderr,"   Integration time: %f \n",h);
	  #endif
	}

      i++;
    }

  free(systemVars);
  free(xn);
  free(x);
}

void LinearizeDynamics(Tparameters *pr,Tchart *c,double *y0,double *x0,double *u0,double *Uc,
		       double **mA,double **mB,double **vc,TDynamicSpace *ds)
{
  unsigned int i;
  double epsilon,epsilon1;
  unsigned int nt;
  #ifdef _OPENMP
    boolean parallel;
    
    /* The finite differences can be parallelized, if the caller is not already executed
       in parallel. Note that, when parallelizing we acces ds->xxx for the basic
       constant parmeters (ndof, da, etc). This is like accessing ds[0].xxx 
       We only make explicit the use of aparticular ds space (ds[nt].xxx) for
       variables that can be written in parallel. */
    parallel=((ds->parallel)&&(!omp_in_parallel()));
  #endif
  
  epsilon=GetParameter(CT_EPSILON,pr);
  epsilon1=10000.0*epsilon;

  NEW(*mA,4*ds->dof*ds->dof,double);
  NEW(*mB,2*ds->dof*ds->da,double);
  NEW(*vc,2*ds->dof,double);

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /* Determine the linearization points is state and action spaces */
  
  /* Project y0 to manifold (x0)  <----  We can prabably pass this as a parameter -------------*/
  if (x0!=NULL)
    memcpy(ds->x0_LQR,x0,sizeof(double)*ds->nv);
  else
    Chart2Manifold(pr,ds->sJ,y0,ds->tp,NULL,ds->x0_LQR,c);

  /* Forward dynamics for action the given action (dot(x)=f(x0,u0) for u0).
     Typically u0=0 */
  if (u0==NULL)
    memset(ds->action,0,sizeof(double)*ds->da);
  else
    memcpy(ds->action,u0,ds->da*sizeof(double));
  
  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /* Compute the acceleration at eh linearizatio point, and project to the tangent space */
  ComputeAcceleration(pr,FALSE,ds->x0_LQR,ds->action,c,NULL,ds); /* This computes ds->g=(dq,ddq) at x0,u0 */
  /* Compute c=f(y0,u0)=Uc^T*f(x0,u0) and store it in chart */
  if (ds->nie==0)
    memcpy(*vc,ds->g,sizeof(double)*ds->nv);
  else
    TMatrixVectorProduct(ds->nv,2*ds->dof,Uc,ds->g,*vc);
  
  #if (0)
    if (ds->nie>0)
      PrintMatrix(stderr,"    Uc",ds->nv,2*ds->dof,Uc);
    PrintVector(stderr,"    x0",ds->nv,ds->x0_LQR);
    PrintVector(stderr,"    f0",ds->nv,ds->g);
    PrintVector(stderr,"    c",2*ds->dof,*vc);
  #endif
    
  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /* Finite differences in tangent space */

  nt=0; /* default thread number */
    
  /* Finite differences to compute A and B */
    
  //#pragma omp parallel for private(i,nt) schedule(dynamic) if (parallel)  
  for(i=0;i<2*ds->dof;i++)
    {
      #ifdef _OPENMP
        if (parallel)
	  nt=omp_get_thread_num();
        else
	  nt=0;
      #else
        nt=0;
      #endif
      
      /* y = y0+E */
      if (y0==NULL)
	memset(ds[nt].y_LQR,0,sizeof(double)*2*ds->dof);
      else
	memcpy(ds[nt].y_LQR,y0,sizeof(double)*2*ds->dof);
      
      ds[nt].y_LQR[i]+=epsilon1;

      /* Project y0+E to manifold (x)	*/
      Chart2Manifold(pr,ds->sJ,ds[nt].y_LQR,ds->tp,NULL,ds[nt].x_LQR,c);

      /* fwd difference for y = y0+epsilon */
      ComputeAcceleration(pr,FALSE,ds[nt].x_LQR,ds->action,c,NULL,&(ds[nt])); /* This computes ds[nt].g=(dq,ddq) at x */
      
      if (ds[nt].nie==0)
	memcpy(ds[nt].fE_LQR,ds[nt].g,sizeof(double)*ds->nv); /* This computes f(y0+E,u0) = Uc^T f(x,u0) for Uc=Id */
      else
	TMatrixVectorProduct(ds->nv,2*ds->dof,Uc,ds[nt].g,ds[nt].fE_LQR); /* This computes f(y0+E,u0) = Uc^T f(x,u0) */
      
      SubtractVector(2*ds->dof,ds[nt].fE_LQR,*vc); /* This computes (f(y0+E,u0)-f0) */
            
      #if (0)
        if (nt==0)
	  {
	    PrintVector(stderr,"    y0+eps1",2*ds->dof,ds[nt].y_LQR);
	    PrintVector(stderr,"    x=xi(y0+eps1)",ds->nv,ds[nt].x_LQR);
	    PrintVector(stderr,"    f(x)",ds->nv,ds[nt].g);
	    PrintVector(stderr,"    Uct*f",2*ds->dof,ds[nt].fE_LQR);
	  }
      #endif
	
      ScaleVector(1.0/epsilon1,2*ds->dof,ds[nt].fE_LQR); /* This computes (f(y0+E,u0)-f0)/epsilon */
      
      /* Fill A matrix */
      SetColumn(ds[nt].fE_LQR,i,2*ds->dof,2*ds->dof,*mA);
    }
    
  #pragma omp parallel for private(i,nt) schedule(dynamic) if (parallel)
  for(i=0;i<ds->da;i++)
    {
      #ifdef _OPENMP
        if (parallel)
	  nt=omp_get_thread_num();
       else
	  nt=0;
      #else
        nt=0;
      #endif
	
      /* u = u0+E */
      if (u0==NULL)
	memset(ds[nt].action,0,sizeof(double)*ds->da);
      else
	memcpy(ds[nt].action,u0,ds->da*sizeof(double));
      
      ds[nt].action[i]+=epsilon1;

      /* fwd difference for u = u0+epsilon */
      ComputeAcceleration(pr,FALSE,ds->x0_LQR,ds[nt].action,c,NULL,&(ds[nt])); /* This computes ds[nt].g=(dq,ddq) at x */
      
      if (ds[nt].nie==0)
	memcpy(ds[nt].fE_LQR,ds[nt].g,sizeof(double)*ds->nv); /* This computes f(y0,u0+E) = Uc^T f(x,u0+E) for Uc=Id */
      else
	TMatrixVectorProduct(ds->nv,2*ds->dof,Uc,ds[nt].g,ds[nt].fE_LQR); /* This computes f(y0,u0+E) = Uc^T f(x,u0+E) */

      SubtractVector(2*ds->dof,ds[nt].fE_LQR,*vc);  /* This computes (f(y0,u0+E)-f0) */
      
      ScaleVector(1.0/epsilon1,2*ds->dof,ds[nt].fE_LQR); /* This computes (f(y0,u0+E)-f0)/epsilon */

      /* Fill B matrix */
      SetColumn(ds[nt].fE_LQR,i,2*ds->dof,ds->da,*mB);
    }
  #if (0)
    PrintMatrix(stderr,"      A",2*ds->dof,2*ds->dof,*mA);
    PrintMatrix(stderr,"      B",2*ds->dof,ds->da,*mB);
  #endif
}

void dr(double *r,double *mA,double *vc,TDynamicSpace *ds)
{
  MatrixVectorProduct(ds->lsSize_LQR,ds->lsSize_LQR,mA,r,ds->dr_LQR); /* A*r(k) */
  AccumulateVector(ds->lsSize_LQR,vc,ds->dr_LQR); /* A*r(k)+c */
}

void dG(double *G,double *mA,double *BiRBt,TDynamicSpace *ds)
{
  MatrixMatrixProduct(ds->lsSize_LQR,ds->lsSize_LQR,mA,ds->lsSize_LQR,G,ds->dG_LQR); /* A*G(k) */
  AccumulateTMatrix(ds->lsSize_LQR,ds->dG_LQR,ds->dG_LQR); /* A*G(k)+G(k)*At */
  //MatrixTMatrixProduct(ds->lsSize_LQR,ds->lsSize_LQR,G,ds->lsSize_LQR,mA,ds->dGtemp_LQR); /* G(k)*At */
  //AccumulateVector(ds->lsSize_LQR*ds->lsSize_LQR,ds->dGtemp_LQR,ds->dG_LQR); /* A*G(k)+G(k)*At */
  AccumulateVector(ds->lsSize_LQR*ds->lsSize_LQR,BiRBt,ds->dG_LQR); /* (A*G(k)+G(k)*At+BRBt) */
}


double LQRComputePolicy(Tparameters *pr,double *y0,double *y1,double tmax,
			double *mA,double *mB,double *vc,double *vd,double *iRBt,double *BiRBt,
			TDynamicSpace *ds)
{
  double J,Jmin,t,h;
  boolean stop;
  double delta;
  double tau;
  double rcond;
  unsigned int it;
  
  /* We elavaluate the cost for different time horizons and keep the lower one.
     We estimate the slope of the cost and stop the evaluation as soon as the
     slope gets close to 0. The slope estimation is filtered to cancel out
     oscilations. */
  
  delta=GetParameter(CT_DELTA,pr);
  tau=GetParameter(CT_TAU,pr);

  /* Minum time for policy computation */
  if (tmax<3*delta)
    tmax=3*delta;

  h=0.001;
  //h=delta/2.0;   /* Step size in the integration */
  
  #if (0)
    fprintf(stderr, "h=%f\n",h);
    fprintf(stderr, "tmax=%f\n",tmax);
    PrintVector(stderr,"      y0",ds->lsSize_LQR,y0);
    PrintVector(stderr,"      y1",ds->lsSize_LQR,y1);
    PrintMatrix(stderr,"      A",ds->lsSize_LQR,ds->lsSize_LQR,mA);
    PrintMatrix(stderr,"      B",ds->lsSize_LQR,ds->da,mB);
    PrintMatrix(stderr,"      R^-1",ds->da,ds->da,ds->iR);
    PrintMatrix(stderr,"      RBt",ds->da,ds->lsSize_LQR,iRBt);
    PrintMatrix(stderr,"      BRBt",ds->lsSize_LQR,ds->lsSize_LQR,BiRBt);
    PrintVector(stderr,"      vc",ds->lsSize_LQR,vc);
  #endif
    
  /* r(0)=y0 */
  memcpy(ds->r_LQR,y0,ds->lsSize_LQR*sizeof(double));
  /* G(0)=0 */
  memset(ds->G_LQR,0,ds->lsSize_LQR*ds->lsSize_LQR*sizeof(double));
  
  /* Jmin */
  Jmin=INF;
  ds->topt=INF;
  
  stop=FALSE;
  it=0;
  t=h;

  #if (PRINT_J)
    fprintf(stderr,"-------------------------------------------------------------------------------------\n");
    fprintf(stderr,"t_m=%g\n",tmax);
    fprintf(stderr,"J=[");
  #endif
  
  while ((!stop)&&(t<tmax))
    {
      if (t>delta)
	h=delta/2.0;
      
      /* Integrate r from t to t+h*/
      dr(ds->r_LQR,mA,vc,ds);                                                    /* k1 = dr(r) = A*r+c -> stored in dr_LQR */
      #if (EULER_LQR_COMPUTE_POLICY)
        SumVectorScale(ds->lsSize_LQR,ds->r_LQR,h,ds->dr_LQR,ds->r_LQR);         /* r = r + h*k1 */
      #else
	SumVectorScale(ds->lsSize_LQR,ds->r_LQR,h/6,ds->dr_LQR,ds->rnew_LQR);    /*  r_new = r + (h/6)*k1 */
	
        SumVectorScale(ds->lsSize_LQR,ds->r_LQR,h/2,ds->dr_LQR,ds->rtemp_LQR);   /* rtemp = r + h/2*k1 */
	dr(ds->rtemp_LQR,mA,vc,ds);                                              /* k2 = dr(rtemp) -> stored in dr_LQR */
      	SumVectorScale(ds->lsSize_LQR,ds->rnew_LQR,h/3,ds->dr_LQR,ds->rnew_LQR); /* r_new = r_new + (h/3)*k2 */
	
        SumVectorScale(ds->lsSize_LQR,ds->r_LQR,h/2,ds->dr_LQR,ds->rtemp_LQR);   /* rtemp = r+h/2*k2 */
	dr(ds->rtemp_LQR,mA,vc,ds);                                              /* k3 = dr(rtemp) -> stored in dr_LQR */
      	SumVectorScale(ds->lsSize_LQR,ds->rnew_LQR,h/3,ds->dr_LQR,ds->rnew_LQR); /* r_new = r_new + (h/3)*k3 */
	
        SumVectorScale(ds->lsSize_LQR,ds->r_LQR,h,ds->dr_LQR,ds->rtemp_LQR);     /* rtemp = r + h*k3 */
	dr(ds->rtemp_LQR,mA,vc,ds);                                              /* k4 = dr(rtemp) -> stored in dr_LQR */
      	SumVectorScale(ds->lsSize_LQR,ds->rnew_LQR,h/6,ds->dr_LQR,ds->r_LQR);    /* r = r_new + (h/6)*k4 */
      #endif
      
      /* Integrate G */
      dG(ds->G_LQR,mA,BiRBt,ds);                                                   /* k1 = dG(G) = A*G+G*A^t+BiRB^t -> stored in dG_LQR */
      //PrintMatrix(stderr,"      dG",ds->lsSize_LQR,ds->lsSize_LQR,ds->dG_LQR);
      #if (EULER_LQR_COMPUTE_POLICY)
        SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h,ds->dG_LQR,ds->G_LQR);        /* G = G + h*k1 */
      #else
	SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h/6,ds->dG_LQR,ds->Gnew_LQR);   /* G_new = G + (h/6)*k1 */

        SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h/2,ds->dG_LQR,ds->Gtemp_LQR);  /* Gtemp = G + h/2*k1 */
	dG(ds->Gtemp_LQR,mA,BiRBt,ds);                                             /* k2 = dG(Gtemp) -> stored in dG_LQR */
      	SumVectorScale(4*ds->dof*ds->dof,ds->Gnew_LQR,h/3,ds->dG_LQR,ds->Gnew_LQR);/* G_new = G_new + (h/3)*k2 */

        SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h/2,ds->dG_LQR,ds->Gtemp_LQR);  /* temp = G + h/2*k2 */
	dG(ds->Gtemp_LQR,mA,BiRBt,ds);                                             /* k3 = dG(Gtemp) -> stored in dG_LQR */
      	SumVectorScale(4*ds->dof*ds->dof,ds->Gnew_LQR,h/3,ds->dG_LQR,ds->Gnew_LQR);/* G_new = G_new + (h/3)*k3 */

        SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h,ds->dG_LQR,ds->Gtemp_LQR);    /* temp = G + h*k3 */
	dG(ds->Gtemp_LQR,mA,BiRBt,ds);                                             /* k4 = dG(Gtemp)   ->  stored in dG_LQR */
      	SumVectorScale(4*ds->dof*ds->dof,ds->Gnew_LQR,h/6,ds->dG_LQR,ds->G_LQR);   /* G = G_new + (h/6)*k4 */
      #endif
      	
      #if (0)
	fprintf(stderr,"t=%f\n",t);
        PrintMatrix(stderr,"      G",ds->lsSize_LQR,ds->lsSize_LQR,ds->G_LQR);
        PrintVector(stderr,"      r",ds->lsSize_LQR,ds->r_LQR);
      #endif

      /* Wait until estimation of r and G stabilize */
 
      /* J=t+d'*G^(-1)*d */
      /* Fill in the rhs term: d=y1-r(k) */
      SumVectorScale(ds->lsSize_LQR,y1,-1.0,ds->r_LQR,ds->d_LQR);
      memcpy(ds->rhsA_LQR,ds->d_LQR,ds->lsSize_LQR*sizeof(double));
      /*Fill the LHS: G */
      memcpy(ds->mA_LQR,ds->G_LQR,ds->lsSize_LQR*ds->lsSize_LQR*sizeof(double));
      /* Solve G^(-1)*d, note that G is destroyed! this is why we copy G to a new buffer */

      if (LSSolveCond(&rcond,&(ds->A_LQR)))
	{
	  #if (PRINT_J)
	    fprintf(stderr,"LSSolve error: %g\n",t);
	  #endif
	  stop=TRUE; /* Error in computing solA_LQR=G^-1*d most likely to ill-conditioning of matrix A_LQR */
	}
      else
	{
	  if (rcond<1e-15)
	    {
	      #if (PRINT_J)
	        fprintf(stderr,"%u %f 0 %g\n",it,t,rcond);
	      #endif
	      if (it>8)
		{
		  #if (PRINT_J)
		    fprintf(stderr,"Ill conditioned problem %f/%f. rcond=%g\n",t,2*delta,rcond);
		  #endif
		  stop=TRUE; /* Error in computing solA_LQR=G^-1*d most likely to ill-conditioning of matrix A_LQR */
		}
	    }
	  else
	    {
	      /* Compute the action cost */
	      J=GeneralDotProduct(ds->lsSize_LQR,ds->d_LQR,ds->solA_LQR); /* d'*G^(-1)*d */
 
	      /* for small t, G may be illconditioned, leading to negative d'*G^(-1)*d
		 when G is positive definite. Set infinite cost */
	      if (J<0)
		{
		  #if (PRINT_J)
		    fprintf(stderr,"%u %f %f %g\n",it,t,J,rcond);
		  #endif
		  if (it>4)
		    stop=TRUE; /* We get a negative cost (impossible). The integration is unstable: stop it  */
		}
	      else
		{
		  #if (0)
		    PrintVector(stderr,"    d",ds->lsSize_LQR,ds->d_LQR);
		    PrintVector(stderr,"    G^(-1)*d",ds->lsSize_LQR,ds->solA_LQR);
		    fprintf(stderr, "   d'*G^(-1)*d=%f\n",J);
		  #endif
		    
		  J+=t/tau; /* t+d'*G^(-1)*d */

		  #if (PRINT_J)
		    fprintf(stderr,"%u %f %f %g\n",it,t,J,rcond);
		  #endif
		    
		  /* Find min J */
		  #if (MAX_J)
		  if ((J<ds->maxJ*t)&&(J<Jmin))
		  #else
		  if (J<Jmin)
		  #endif
		    {
		      /* Keep the minimum cost along the integration horizon */
		      Jmin=J;
		      ds->topt=t;
		      memcpy(ds->Gd,ds->solA_LQR,ds->lsSize_LQR*sizeof(double));
		    }
		}
	    }
	}
      
      /* t=t+h */
      t+=h;
      it++;
    }

  #if (PRINT_J)
    fprintf(stderr,"];\n");
  #endif
  
  #if (MAX_J)
    if ((!stop)&&(ds->topt==INF))
      {
	ds->topt=tmax;
	memcpy(ds->Gd,ds->solA_LQR,ds->lsSize_LQR*sizeof(double));	
      }
  #endif
    
  if (ds->topt<INF) /* If we have an optimal policy */
    {
      /* Copy a couple of matrices that are used when computing the policy (besides Gd) */
      
      /* Transpose A matrix */
      SubMatrixFromTMatrix(ds->lsSize_LQR,ds->lsSize_LQR,mA,0,0,ds->lsSize_LQR,ds->lsSize_LQR,ds->mAt);
      /* Copy iRBt matrix */
      memcpy(ds->iRBt,iRBt,ds->lsSize_LQR*ds->da*sizeof(double));
  
      #if (0)
        fprintf(stderr,"J=%f\n",J);
	fprintf(stderr,"Jmin=%f\n",Jmin);
	fprintf(stderr,"tmin=%f\n",ds->topt);
      #endif
    }

  return(ds->topt);
}

void dGt(double *mA,double t,double *BiRBt,double *eA,TDynamicSpace *ds)
{ 
  MatrixExponential(ds->lsSize_LQR,mA,t,eA);  /* eA = exp(A,t) */
  MatrixMatrixProduct(ds->lsSize_LQR,ds->lsSize_LQR,eA,ds->lsSize_LQR,BiRBt,ds->Gtemp_LQR); /* Gtemp_LQR = exp(A,t)*BiRBt = dA*BiRtB */
  MatrixTMatrixProduct(ds->lsSize_LQR,ds->lsSize_LQR,ds->Gtemp_LQR,ds->lsSize_LQR,eA,ds->dG_LQR); /* G = exp(A,t)*BiRBt*exp(A,t)^t = Gtemp_LQR*eA^t */
  SymmetrizeMatrix(ds->lsSize_LQR,ds->dG_LQR); /* Compensate numerical errors */
}

double LQRComputePolicy_t(Tparameters *pr,double *y0,double *y1,double tmax,
			  double *mA,double *mB,double *vc,double *vd,
			  double *iRBt,double *BiRBt,
			  TDynamicSpace *ds)
{
  double J,Jmin,t,h;
  boolean stop;
  double delta;
  double tau;
  double rcond;
  unsigned int it;

  //LQRComputePolicy(pr,y0,y1,tmax,mA,mB,vc,vd,iRBt,BiRBt,ds);
  
  /* We elavaluate the cost for different time horizons and keep the lower one.
     We estimate the slope of the cost and stop the evaluation as soon as the
     slope gets close to 0. The slope estimation is filtered to cancel out
     oscilations. */
  
  delta=GetParameter(CT_DELTA,pr);
  tau=GetParameter(CT_TAU,pr);
  
  /* Minum time for policy computation */
  //if (tmax<3*delta)
  //  tmax=3*delta;

  //h=0.001;
  //h=delta/2;  /* Step size in the integration */
  
  h=0.001;
  if (tmax/h<10)
    h=tmax/10;
  
  #if (0)
    fprintf(stderr, "h=%f\n",h);
    fprintf(stderr, "tmax=%f\n",tmax);
    PrintVector(stderr,"      y0",ds->lsSize_LQR,y0);
    PrintVector(stderr,"      y1",ds->lsSize_LQR,y1);
    PrintMatrix(stderr,"      A",ds->lsSize_LQR,ds->lsSize_LQR,mA);
    PrintMatrix(stderr,"      B",ds->lsSize_LQR,ds->da,mB);
    PrintMatrix(stderr,"      R^-1",ds->da,ds->da,ds->iR);
    PrintMatrix(stderr,"      RBt",ds->da,ds->lsSize_LQR,iRBt);
    PrintMatrix(stderr,"      BRBt",ds->lsSize_LQR,ds->lsSize_LQR,BiRBt);
    PrintVector(stderr,"      vc",ds->lsSize_LQR,vc);
    PrintVector(stderr,"      vd",ds->lsSize_LQR,vd);
  #endif

  SumVector(ds->lsSize_LQR,y0,vd,ds->d0_LQR);/* d0=r(0)+vd  with r(0)=y0 */
    
  /* G(0)=0 */
  memset(ds->G_LQR,0,ds->lsSize_LQR*ds->lsSize_LQR*sizeof(double));
  
  /* Jmin */
  Jmin=INF;
  ds->topt=INF;

  /* First derivative out of the loop to avoid repetions: dGt(t=0) = Id*BiRBt*Id = BiRBt */
  memcpy(ds->dG_LQR,BiRBt,ds->lsSize_LQR*ds->lsSize_LQR*sizeof(double));
  
  stop=FALSE;
  it=0;
  t=h;
  
  #if (PRINT_J)
    fprintf(stderr,"-------------------------------------------------------------------------------------\n");
    fprintf(stderr,"t_m=%g\n",tmax);
    #if (MAX_J)
      fprintf(stderr,"max_J=%g\n",ds->maxJ);
    #endif
    fprintf(stderr,"J_t=[");
  #endif
           
  while ((!stop)&&(t<=tmax))
    {
      if (t>delta)
	h=delta/2;
      
      /* Integrate G from t to t+h using the time expression and the Simpson's rule */
      SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h/6,ds->dG_LQR,ds->G_LQR);    /* re-use the derivative computed for t-h (was t in the previous step) */
      dGt(mA,t-h/2,BiRBt,ds->eA_LQR,ds);
      SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,2*h/3,ds->dG_LQR,ds->G_LQR);  /* add the derivative for t-h/2 */
      dGt(mA,t,BiRBt,ds->eA_LQR,ds);
      SumVectorScale(4*ds->dof*ds->dof,ds->G_LQR,h/6,ds->dG_LQR,ds->G_LQR);    /* add the derivative for t (will be re-used at next step, if any) */
      
      /* Compute r(t) Note that we re-use the exp(t*A) computed in the last call to dGt  */
      MatrixVectorProduct(ds->lsSize_LQR,ds->lsSize_LQR,ds->eA_LQR,ds->d0_LQR,ds->r_LQR);
      SubtractVector(ds->lsSize_LQR,ds->r_LQR,vd); /* r = exp(t*A)*(y0-A^-1*c) - A^-1*c */
      
      #if (0)
        fprintf(stderr,"t=%f\n",t);
	PrintMatrix(stderr,"      G_t",ds->lsSize_LQR,ds->lsSize_LQR,ds->G_LQR);
	PrintVector(stderr,"      r_t",ds->lsSize_LQR,ds->r_LQR);
      #endif
	    
      if (Norm(ds->lsSize_LQR,ds->r_LQR)>1e10)
	{
	  #if (PRINT_J)
	    fprintf(stderr,"Too large r: %g\n",t);
	  #endif
	  stop=TRUE; /* Error in computing solA_LQR=G^-1*d most likely to ill-conditioning of matrix A_LQR */
	}
      else 
	{
	  /* J=t+d'*G^(-1)*d */
	  /* Fill in the rhs term: d=y1-r(k) */
	  SumVectorScale(ds->lsSize_LQR,y1,-1.0,ds->r_LQR,ds->d_LQR);
	  memcpy(ds->rhsA_LQR,ds->d_LQR,ds->lsSize_LQR*sizeof(double));
	  /*Fill the LHS: G */
	  memcpy(ds->mA_LQR,ds->G_LQR,ds->lsSize_LQR*ds->lsSize_LQR*sizeof(double));
	  /* Solve G^(-1)*d, note that G is destroyed! this is why we copy G to a new buffer */

	  if (LSSolveCond(&rcond,&(ds->A_LQR)))
	    {
	      #if (PRINT_J)
	       fprintf(stderr,"LSSolve error: %g\n",t);
	      #endif
	      stop=TRUE; /* Error in computing solA_LQR=G^-1*d most likely to ill-conditioning of matrix A_LQR */
	    }
	  else
	    {
	      if (rcond<1e-15)
		{
		  #if (PRINT_J)
		    fprintf(stderr,"%u %f 0 %g\n",it,t,rcond);
		  #endif
		  if (it>8)
		    {
		      #if (PRINT_J)
		        fprintf(stderr,"Ill conditioned problem %f/%f. rcond=%g\n",t,2*delta,rcond);
		      #endif
		      stop=TRUE; /* Error in computing solA_LQR=G^-1*d most likely to ill-conditioning of matrix A_LQR */
		    }
		}
	      else
		{
		  /* Compute the action cost */
		  J=GeneralDotProduct(ds->lsSize_LQR,ds->d_LQR,ds->solA_LQR); /* d'*G^(-1)*d */
 
		  /* for small t, G may be illconditioned, leading to negative d'*G^(-1)*d
		     when G is positive definite. Set infinite cost */
		  if (J<0)
		    {
		      #if (PRINT_J)
		        fprintf(stderr,"%u %f %f %g\n",it,t,J,rcond);
		      #endif
		      if (it>4)
			{
			  #if (PRINT_J)
			    fprintf(stderr,"Negative cost\n");
			  #endif
			  stop=TRUE; /* We get a negative cost (impossible). The integration is unstable: stop it  */
			}
		    }
		  else
		    {
		      #if (0)
		        PrintVector(stderr,"    d",ds->lsSize_LQR,ds->d_LQR);
			PrintVector(stderr,"    G^(-1)*d",ds->lsSize_LQR,ds->solA_LQR);
			fprintf(stderr, "   d'*G^(-1)*d=%f\n",J);
		      #endif
		    
		      J+=t/tau; /* t+d'*G^(-1)*d */

		      #if (PRINT_J)
		        fprintf(stderr,"%u %f %f %g\n",it,t,J,rcond);
		      #endif
					    
		      /* Find min J */
		      #if (MAX_J)
		      if ((J<ds->maxJ*t)&&(J<Jmin))
		      #else
		      if (J<Jmin)
		      #endif
			{
			  /* Keep the minimum cost along the integration horizon */
			  Jmin=J;
			  ds->topt=t;
			  memcpy(ds->Gd,ds->solA_LQR,ds->lsSize_LQR*sizeof(double));
			}
		    }
		}
	    }
	}
      /* t=t+h */
      if (t<tmax)
	{
	  t+=h;
	  if (t>tmax)
	    t=tmax;
	}
      else
	t+=h; // just to get t>tmax
      it++;
    }
  #if (PRINT_J)
    fprintf(stderr,"];\n");
  #endif
    
  #if (MAX_J)
    if ((!stop)&&(ds->topt==INF))
      {
	ds->topt=tmax;
	memcpy(ds->Gd,ds->solA_LQR,ds->lsSize_LQR*sizeof(double));	
      }
  #endif 
    
  if (ds->topt<INF) /* If we have an optimal policy */
    {
      /* Copy a couple of matrices that are used when computing the policy (besides Gd) */
      
      /* Transpose A matrix */
      SubMatrixFromTMatrix(ds->lsSize_LQR,ds->lsSize_LQR,mA,0,0,ds->lsSize_LQR,ds->lsSize_LQR,ds->mAt);
      /* Copy iRBt matrix */
      memcpy(ds->iRBt,iRBt,ds->lsSize_LQR*ds->da*sizeof(double));
  
      #if (0)
        fprintf(stderr,"J=%f\n",J);
	fprintf(stderr,"Jmin=%f\n",Jmin);
	fprintf(stderr,"tmin=%f\n",ds->topt);
      #endif
    }
  
  return(ds->topt);
}


double LQRPolicy(Tparameters *pr,double *u,double t,TDynamicSpace *ds)
{
  #if (SATURATE_ACTIONS)
    unsigned int i;
  #endif
  unsigned int dOut;

  if(ds->topt+1e-6<t)
    fprintf(stderr,"Input time is larger than trajectory time in LQRPolicy (%f vs %f %g)\n",ds->topt,t,t-ds->topt);

  /* exp(At,(topt-t))*G^(-1)*d where G^(-1)*d is already stored in ds->Gd */
  if (!MatrixExponential(ds->lsSize_LQR,ds->mAt,ds->topt-t,ds->eA_LQR))
    Error("Matrix exponential error in LQRPolicy");
  MatrixVectorProduct(ds->lsSize_LQR,ds->lsSize_LQR,ds->eA_LQR,ds->Gd,ds->rtemp_LQR);

  //PrintVector(stderr,"    exp",ds->lsSize_LQR,ds->rtemp_LQR);
  
  /* u = iRBt * exp(At,(topt-t))*G^(-1)*d  */
  MatrixVectorProduct(ds->da,ds->lsSize_LQR,ds->iRBt,ds->rtemp_LQR,u);
  //PrintVector(stderr,"    u",ds->dof,u);
  //PrintVector(stderr,"   max u",ds->dof,ds->effort);

  dOut=0;
  #if (SATURATE_ACTIONS)
    for(i=0;i<ds->da;i++)
      {
	if (u[i]>ds->effort[ds->a2j[i]])
	  {
	    u[i]=ds->effort[ds->a2j[i]];
	    dOut++;
	  }
	else
	  {	
	    if (u[i]<-ds->effort[ds->a2j[i]])
	      {
		u[i]=-ds->effort[ds->a2j[i]];
		dOut++;
	      }
	  }
      }
  #endif
  
  return((double)dOut/(double)ds->da);
}

inline void EvaluatePermutation(TDynamicSpace *ds)
{
  unsigned int i;

  memset(ds->P,0,sizeof(double)*ds->da*ds->npv);
  for(i=0;i<ds->da;i++)
    ds->P[RC2INDEX(ds->a2x[i],i,ds->npv,ds->da)]=1.0;
}

unsigned int ActionSpaceDimension(TDynamicSpace *ds)
{
  return(ds->da);
}

inline boolean GetActionFromID(unsigned int id,double *u,TDynamicSpace *ds)
{
  #if (RANDOM_DYNAMIC_ACTION)
    unsigned int i;
    double m;

    for(i=0;i<ds->da;i++)
      {
	m=ds->effort[ds->a2j[i]];
	u[i]=randomDouble()*(2.0*m)-m;
      }
    return(TRUE);
  #else
    /* Use bang-bang control for each action: +/- maximum effort
       independenly applied to each action. Thus we have 2*da max 
       actions */
    unsigned int i;
    double m;

    if (id<2*ds->da)
      {
	memset(u,0,sizeof(double)*ds->da);
	i=id/2;
	m=ds->effort[ds->a2j[i]];
	if (id%2==1)
	  u[i]=+m;
	else
	  u[i]=-m;
      }
    else
      return(FALSE);
  #endif
}

inline boolean ValidState(boolean negLag,TDynamicSpace *ds)
{
  if (negLag)
    {
      boolean ok;
      unsigned int i;

      /* Lagrage multipliers must be negative */
      ok=TRUE;
      i=0;
      while((ok)&&(i<ds->nipe))
	{
	  ok=(ds->solA[i]<0.0);
	  //  if (!ok)
	  //printf(stderr,"Multiplier %u is not in negative (%f)\n",i,ds->solA[i]);
	  i++;
	}
      return(ok);
    }
  else
    return(TRUE);
}

void PrintDynamicsDefines(FILE *f)
{
  fprintf(f,"\n   %% Dynamics defines\n");
  fprintf(f,"   DEBUG_DYNAMICS %u\n",DEBUG_DYNAMICS);
  fprintf(f,"   PRINT_J %u\n",PRINT_J);
  fprintf(f,"   DEBUG_HandC %u\n",DEBUG_HandC);
  fprintf(f,"   HandC_Thread %u\n",HandC_Thread);
  fprintf(f,"   HandC_FJH %u\n",HandC_FJH);
  fprintf(f,"   DEBUG_HandC_FJH %u\n",DEBUG_HandC_FJH);
  fprintf(f,"   HandC_EQ_INV %u\n",HandC_EQ_INV);
  fprintf(f,"   START_BROYDEN_ON_MANIFOLD %u\n",START_BROYDEN_ON_MANIFOLD);
  fprintf(f,"   USE_HTxSAV %u\n",USE_HTxSAV);
  fprintf(f,"   EXPLICIT_CRM %u\n",EXPLICIT_CRM);
  fprintf(f,"   EXPLICIT_CRF %u\n",EXPLICIT_CRF);
  fprintf(f,"   USE_XUPTR %u\n",USE_XUPTR);
  fprintf(f,"   CUT_AT_LINK %u\n",CUT_AT_LINK);
  fprintf(f,"   EULER_LQR_COMPUTE_POLICY %u\n",EULER_LQR_COMPUTE_POLICY);
  fprintf(f,"   SATURATE_ACTIONS %u\n",SATURATE_ACTIONS);
  fprintf(f,"   RANDOM_DYNAMIC_ACTION %u\n",RANDOM_DYNAMIC_ACTION);
  fprintf(f,"   T2G_METRIC_NN_EXTEND %u\n",T2G_METRIC_NN_EXTEND);
  fprintf(f,"   T2G_METRIC_NN_CONNECT %u\n",T2G_METRIC_NN_CONNECT);
  fprintf(f,"   T2G_METRIC_INSIDE_EXTEND %u\n",T2G_METRIC_INSIDE_EXTEND);
  fprintf(f,"   T2G_METRIC_INSIDE_CONNECT %u\n",T2G_METRIC_INSIDE_CONNECT);
  fprintf(f,"   T2G_METRIC %u\n",T2G_METRIC);
  fprintf(f,"   DYNAMICS_ONE_ACTION_EXTEND %u\n",DYNAMICS_ONE_ACTION_EXTEND);
  fprintf(f,"   DYNAMICS_ONE_ACTION_CONNECT %u\n",DYNAMICS_ONE_ACTION_CONNECT);
  fprintf(f,"   MAX_J %u\n",MAX_J);
}

void DeleteDynamicSpace(TDynamicSpace *ds)
{
  DeleteBroyden(&(ds->B));
  free(ds->xa);
  free(ds->gn);
  free(ds->y);
  free(ds->g);
  free(ds->gy);
  free(ds->k1);
  free(ds->k2);
  free(ds->k3);
  DeleteLS(&(ds->A_ID));
  DeleteLS(&(ds->A));
  free(ds->Mm);

  DeleteBox(&(ds->domain));

  if (ds->tp!=NULL)
    free(ds->tp);
  
  if (ds->npe+ds->noe>0)
    {
      free(ds->bJ);
      free(ds->bJp);

      free(ds->J);
      free(ds->cJ);

      free(ds->Jp);

      if (ds->nHp!=NULL)
	{
	  DeleteNHessian(ds->nHp);
	  free(ds->nHp);
	}
      else
	{
	  FreeHessianEvaluationAsVectors(ds->Hp,&(ds->sHp));
	  DeleteHessian(&(ds->sHp));
	}

      free(ds->Hpv);

      if (ds->nJp!=NULL)
	{
	  DeleteNJacobian(ds->nJp);
	  free(ds->nJp);
	}
      if (ds->noe>0)
	{
	  DeleteJacobian(&(ds->sJop));
	  DeleteJacobian(&(ds->sJoo));
	  DeleteLS(&(ds->Jot));
	  free(ds->o);
	}
      DeleteJacobian(&(ds->sJp));

      free(ds->pVars);
      
      if (ds->npe>0)
	{
	  free(ds->pEqs);
	  free(ds->ndxPE);
	  free(ds->ndxVE);
	}
      if (ds->noe>0)
	free(ds->ndxOE);
      if (ds->npv>0)
	{
	  free(ds->ndxPV);
	  free(ds->ndxVV);
	}
      if (ds->nov>0)
	free(ds->ndxOV);
    }

  free(ds->pos);
  free(ds->vel);
  
  free(ds->pvVars);
  free(ds->pvEqs);
  free(ds->oEqs);
  free(ds->selEqs);
  
  free(ds->action);
  free(ds->P);

  free(ds->l);
  free(ds->j);
  free(ds->effort);
  free(ds->a2j);
  free(ds->a2x);

  free(ds->iR);
  DeleteLS(&(ds->A_LQR));
  free(ds->Gd);
  free(ds->mAt);
  free(ds->iRBt);
  free(ds->eA_LQR);
  free(ds->d0_LQR);
  free(ds->x0_LQR);
  free(ds->x_LQR);
  free(ds->y_LQR);
  free(ds->fE_LQR);

  free(ds->r_LQR);
  free(ds->rtemp_LQR);
  free(ds->rnew_LQR);
  free(ds->dr_LQR);
  free(ds->d_LQR);
  free(ds->G_LQR);
  free(ds->Gtemp_LQR);
  free(ds->dG_LQR);
  free(ds->dGtemp_LQR);
  free(ds->Gnew_LQR);

  #if (DEBUG_HandC_FJH)
    free(ds->Jp2);
    free(ds->Hpv2);
    free(ds->gamma2);
    free(ds->fe2);
  #endif
  
  DeleteHandC(ds);
}

