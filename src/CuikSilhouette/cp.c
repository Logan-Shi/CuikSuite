#include "cp.h"

#include "boolean.h"
#include "interval.h"
#include "monomial.h"
#include "equation.h"
#include "variable.h"
#include "defines.h"
#include "box_list.h"
#include "random.h"
#include "jacobian.h"

#include <math.h>


/** 
    \file cp.c

    \brief Implementation of the functions operating on Tcp.

    Implementation of the functions dealing with  critial points, i.e., 
    recursion points for the silhouette algorithm.

    \sa cp.h, Tcp.
*/

/**
   \brief Generates a cuiksystem whose solution is a silhouette or a set
          of critical points.

   Generates a cuiksystem whose solution is a silhouette or a set
   of critical points. The cuiksystem is generated form an \e extended Jacobian
   of the original cuiksystem. The \e extended comes from the fact that we
   add the projection planes to the system Jacobian.
   The silhouette/critical points are the points where this \e extended Jacobian
   is not full rank. To identify these points, we generate a system with the
   linear combinations of the equations in the Jacobian and we search from points
   where this linear combination is zero (excluding the trivial solution by imposing
   the norm of the scale factor of the linear combinations to be 1).

   \param silhouette TRUE if we have to generate a system to determine a silhouette
                     and FALSE to generate a system to isolate critical points.
   \param p A set of parameters
   \param planes Two arrays of doubles with one entry for each variables in the system
                 defining the projection planes in which the silhouette or the critical
		 points are defined.
                 When parameter \e silhouette is FALSE only one plane is used.
   \param cp The that triggered the generation of the system.
   \param cs The original cuiksystem.
   \param originalSystemVars An array of flags with as many entries as the number of variables 
                             in the output cuiksystem (\e csR) with entries to TRUE only
		             for the system variables in the original cuiksystem 
			     (\e cs parameter).
   \param csR The output cuiksystem.
*/
void GetSCpSystem(boolean silhouette,Tparameters *p,
		  double **planes,Tcp *cp,TCuikSystem *cs,
		  boolean **originalSystemVars,TCuikSystem *csR);

/**
   \brief Generates \e n orthonormals planes.

   Generates \e n orthonormals planes in a space of dimension \e dim that
   we use for projection. 
   
   \e m is level at which these planes are fixed: values up to \e m are zero in
   the output vectors.

   \param p A set of parameters.
   \param n The number of planes to generate
   \param dim The number variables in the original cuiksystem.
   \param m The number of variables already fixed.
   \param v Room for the vectors.
 
*/
void GenerateProjectionPlanes(Tparameters *p,
			      unsigned int n,unsigned int dim,unsigned int m,double **v);


/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

void GetSCpSystem(boolean silhouette,Tparameters *p,double **planes,
		  Tcp *cp,TCuikSystem *cs,boolean **originalSystemVars,TCuikSystem *csR)
{
  unsigned int maxLevel,i,nvars,neqs,nvarsR;

  maxLevel=(unsigned int)GetParameter(CT_N_DOF,p)-1;

  if ((cp->level==maxLevel)&&(!silhouette))
    Error("In the last recursion level only silhouette are computed");

  /*Copy the original system*/
  CopyCuikSystem(csR,cs);

  /*Get the equations/variables of the original system*/ 
  nvars=GetCSNumVariables(cs);
  neqs=GetCSNumEquations(cs);
  
  /*Set the already fixed ranges (ranges up to level)*/
  for(i=0;i<cp->level;i++)
    SetCSVariableRange(i,GetBoxInterval(i,&(cp->fixedRanges)),csR);

  if ((!silhouette)&&(cp->level==maxLevel))
    Error("Computing critical points on a terminal silhouette");

  /* For 1 degree of freedom remaining we do not need the Jacobian */
  if (cp->level<maxLevel)
    {
      unsigned int j,npp,nl,*nvl;
      char vname[100];
      Tequation eq,eq1;
      Tmonomial f;
      TJacobian J; /*The Jacobian Matrix*/ 
      #if (BOUNDED_LAMBDAS)
        Tinterval one_one,zero_one;
      #else
        Tinterval allR,one;
      #endif

      /*Determine the number of projection planes to use*/
      npp=(silhouette?2:1); /*number of projection planes to use*/
      nl=neqs+npp;    /*rows of the Jacobian matrix*/
     
      /*Add the lambda_i variables*/

      #if (BOUNDED_LAMBDAS)
        NewInterval(-1.0,1.0,&one_one);
        NewInterval( 0.0,1.0,&zero_one);
      #else
        NewInterval(-INF,INF,&allR);
        NewInterval(1.0,1.0,&one);
      #endif

      NEW(nvl,nl,unsigned int);
      for(i=0;i<nl;i++)
	{
	  Tvariable v;
	  /*lambda_i*/
	  sprintf(vname,"_lambda_%u",i+1);

	  NewVariable(SYSTEM_VAR,vname,&v);
	  #if (BOUNDED_LAMBDAS)
	    SetVariableInterval((i==0?&zero_one:&one_one),&v);
	  #else
	    SetVariableInterval((i<nl-1?&allR:&one),&v);
	  #endif
	  
	  nvl[i]=AddVariable2CS(&v,csR);
      
	  DeleteVariable(&v);
	}

      #if (BOUNDED_LAMBDAS)
        /*Add the equation \sum_i lambda_i^2 =1*/
        GenerateGeneralNormEquation(nl,nvl,1.0,&eq);
	AddEquation2CS(p,&eq,csR);
	DeleteEquation(&eq);
      #endif

      /*Generate the Jacobian matrix (a matrix of equations (possibly ct))*/
      GetCSJacobian(&J,cs);
  
      /*Generate the equations from the extended Jacobian matrix (for the non-fixed 
	variables up to now)*/
      InitMonomial(&f);
      for(j=cp->level;j<nvars;j++)
	{ 
	  /* eq=\sum_i lambda_i*J(i,j)=\sum_i lambda_i \sum_{k (monomials in J(i,j))} f_{i,j,k}   
	     The monomials in J(i,j) include the ct monomial that is stored as 
	     the value of equation J(i,j) */

	  InitEquation(&eq);
	  SetEquationCmp(EQU,&eq);
	  SetEquationType(SYSTEM_EQ,&eq);

	  for(i=0;i<neqs;i++)
	    {
	      CopyEquation(&eq1,GetJacobianEquation(i,j,&J));
	      VarScaleEquation(nvl[i],&eq1);
	      AccumulateEquations(&eq1,1.0,&eq);
	      DeleteEquation(&eq1);
	    }

	  for(i=0;i<npp;i++)
	    {
	      InitMonomial(&f);
	      AddVariable2Monomial(NFUN,nvl[neqs+i],1,&f);
	      AddCt2Monomial(planes[i][j],&f);
	      AddMonomial(&f,&eq);
	      DeleteMonomial(&f);
	    }
	  AddEquation2CS(p,&eq,csR);
	  DeleteEquation(&eq);
	}

      /*Remove the stored data*/
      DeleteJacobian(&J);
      free(nvl);
    }
  
  /* The variables possibly added to csR are marked as non
     original variables.*/
  nvarsR=GetCSSystemVars(originalSystemVars,csR);
  for(i=nvars;i<nvarsR;i++)
    (*originalSystemVars)[i]=FALSE; 
}

/*
 *  Generates 'n' orthonormals planes in a space of dimension 'dim' that
 *  we use for projection. 'm' is level at which these planes are fixed ->
 *  values up to m are zero
 */
void GenerateProjectionPlanes(Tparameters *p,
			      unsigned int n,unsigned int dim,unsigned int m,double **v)
{
#if (RANDOM_PLANES) 
  unsigned int i,j;

  /*generate 'n' random planes*/
  for(i=0;i<n;i++)
    {
      for(j=0;j<m;j++) 
	v[i][j]=0;
      for(j=m;j<dim;j++)
	v[i][j]=randomDouble();
    }

  if (n>0)
    {
      double norm;

      /*The first plane is normalized*/
      norm=0;
      for(j=m;j<dim;j++)
	norm+=(v[0][j]*v[0][j]);
      norm=sqrt(norm);
      for(j=m;j<dim;j++)
	v[0][j]/=norm;
      
      if (n>1)
	{
	  double p; /*norm of the projection of v1 on v0*/

	  /*Second vector is made orthonormal w.r.t. vector 1*/
	  /* v1=v1-proj(v1,v0) and then normalized. */

	  /* compute the norm of the projection of 'v1' on 'v0' */
	  p=0;
	  for(j=m;j<dim;j++)
	    p+=(v[1][j]*v[0][j]);
	  /*Substract from v1 the component on v0*/
	  for(j=m;j<dim;j++)
	    v[1][j]-=p*v[0][j];
	  /*Normalize the resulting v1 (othonormal w.r.t. v0*/
	  norm=0;
	  for(j=m;j<dim;j++)
	    norm+=(v[1][j]*v[1][j]);
	  norm=sqrt(norm);
	  for(j=m;j<dim;j++)
	    v[1][j]/=norm;
	}
    }
#else
  unsigned int i,j;

  for(i=0;i<n;i++)
    {
      for(j=0;j<m;j++) 
	v[i][j]=0;
      for(j=m;j<dim;j++)
	v[i][j]=(i==(j-m));
    }
#endif
}

void NewCP(unsigned int l,Tbox *b,Tcp *cp)
{
  unsigned int i;
  double center;
  Tinterval *it;

  cp->level=l;
  CopyBox(&(cp->fixedRanges),b);

  /*The first 'l' variables of the box must have punctual range*/
  /*Critical points are defined form solution boxes that are tiny but
    not punctual. We transform them to punctual taking the center of
    the solutin intervals. */
  for(i=0;i<l;i++)
    {
      it=GetBoxInterval(i,b);
      center=IntervalCenter(it);
      NewInterval(center,center,it);
    }
}

unsigned int GetCPlevel(Tcp *cp)
{
  return(cp->level);
}

Tbox *GetCPFixedRanges(Tcp *cp)
{
  return(&(cp->fixedRanges));
}

void DealWithCP(FILE *f_out,unsigned int n,Tparameters *p,TCuikSystem *cs,
		Tlist *cps,Tcp *cp)
{
  TCuikSystem csR; /* The cuik system reduced according to the 
		      information stored in the 'cp*/
  Titerator it;
  Tcp *ncp; /*new critical points recursively generated from here*/
  unsigned int l,maxLevel,nVars;
  boolean *originalSystemVars;
  Tlist solutions,points;
  char heading[20];
  double *planes[2];
  unsigned int nsols;

  maxLevel=(unsigned int)GetParameter(CT_N_DOF,p)-1;

  /* Ensure we will get all the possible solutions */
  nsols=(unsigned int)GetParameter(CT_N_SOLUTIONS,p);
  ChangeParameter(CT_N_SOLUTIONS,0,p);

  nVars=GetCSNumVariables(cs);

  NEW(planes[0],nVars,double);
  NEW(planes[1],nVars,double);
      
  GenerateProjectionPlanes(p,2,nVars,cp->level,planes);

  GetSCpSystem(TRUE,p,planes,cp,cs,&originalSystemVars,&csR); /*TRUE -> Silhouette*/

  fprintf(f_out,"SILHOUTTE LEVEL: %u/%u\n",cp->level,maxLevel);
  PrintCuikSystemWithSimplification(p,f_out,&csR);
  //exit(0);

  InitListOfBoxes(&solutions);
  SolveCuikSystem(p,FALSE,NULL,NULL,f_out,&solutions,&csR);

  sprintf(heading,"SIL %u",n);
  PrintListOfBoxes(f_out,originalSystemVars,heading,&solutions);
  DeleteListOfBoxes(&solutions);

  free(originalSystemVars);
  DeleteCuikSystem(&csR);

  if (cp->level<maxLevel) /*If the silhouette was not the terminal one*/
    {
      GetSCpSystem(FALSE,p,planes,cp,cs,&originalSystemVars,&csR);/*FALSE -> Critical points*/

      InitListOfBoxes(&solutions);
      
      SolveCuikSystem(p,FALSE,NULL,NULL,f_out,&solutions,&csR);
      
      ListOfBoxesCluster(originalSystemVars,&points,&solutions);

      InitIterator(&it,&points);
      First(&it);
      l=cp->level+1; 
      while(!EndOfList(&it))
	{
	  NEW(ncp,1,Tcp);
	  NewCP(l,(Tbox *)GetCurrent(&it),ncp);
	  AddLastElement((void *)&ncp,cps);
	  
	  Advance(&it);
	}
      
      sprintf(heading,"CP %u",n);
      PrintListOfBoxes(f_out,originalSystemVars,heading,&points); 
      
      free(originalSystemVars);
      DeleteCuikSystem(&csR);
      DeleteListOfBoxes(&points);
      DeleteListOfBoxes(&solutions);
    }
  free(planes[0]);
  free(planes[1]);
  ChangeParameter(CT_N_SOLUTIONS,nsols,p);
}


void DeleteCP(Tcp *cp)
{
  DeleteBox(&(cp->fixedRanges));
}
