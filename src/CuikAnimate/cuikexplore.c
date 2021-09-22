#include "cuikexplore.h"

#include "world.h"
#include "interval.h"
#include "chart.h"
#include "defines.h"
#include "jacobian.h"
#include "samples.h"
#include "error.h"
#include "algebra.h"

#include "cuikexplore_interface.h"
#include "cuikplay_support.h"

#include <gtk/gtk.h>

#include <string.h>
#include <unistd.h>
#include <time.h>

/** \file cuikexplore.c

    \brief Main body of the \ref cuikexplore.c "cuikexplore" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikexplore    [label="cuikexplore"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      joints  [label="joints"     color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];

      param -> cuikexplore
      world -> cuikexplore
      joints -> cuikexplore
      cuikexplore -> joints;
    }
    \enddot
    </center>

    This application allows to navigate manifolds.

    This application allows to move a mechanism interactivelly navigating its
    manifold configuration space.
*/


/** 
   \brief Main body of the \ref cuikexplore.c "cuikexplore"  application.

   Main body of the \ref cuikexplore.c "cuikexplore" application.

   Use: <br>
     - \b cuikexplore \e world_name.world  [dof_1 dof_2 ... dof_k] 
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e dof_1 dof_2... dof_k [optional] The variables used as parameters.
     .
   File extension is optional. The two las parameters are optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  
  if (argc>1)
    {
      TAtlasBase world;
      Tworld *worldBase;
      Tparameters parameters;

      Tfilename fparam;

      Tplot3d pt;

      TCuikexploreControl status;
      unsigned int i,j,me;
      double epsilon,delta;

      unsigned int k,m,ms,d,nit;
      double r,e,ce;

      TJacobian J;

      GtkWidget *window_cuikexplore;
      
      Tchart chart,chartTmp;
      Tbox ambient;
      unsigned int *tp;
      boolean hasS;
      boolean collide,in;

      Tinterval range;

      /* We differentiate between the internal representation of the equations
         and the DOF-based representation. They are not necessarily the same. */
      double *newPointDOF;
      double *simpPoint;
      double *t;
      double *initialPoint,*initialPointDOF,*initialSimpPoint;
     
      boolean ndxOK;
      boolean outside,outsideInit;
      boolean collision,collisionInit;
      double *pointWithDummies;
      
      status.fw=arg[1];

      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      status.dynamics=(GetParameter(CT_DYNAMICS,&parameters)>0);
      if (status.dynamics)
	{
	  /* De-activate the dynamics (assume zero velocity) */
	  ChangeParameter(CT_DYNAMICS,0,&parameters);
	}
      
      nit=(unsigned int)(GetParameter(CT_MAX_NEWTON_ITERATIONS,&parameters));
      if (nit==0)
	ChangeParameter(CT_MAX_NEWTON_ITERATIONS,50,&parameters);

      /* Read the equation info from world  */
      NEW(worldBase,1,Tworld);
      InitWorldFromFile(&parameters,TRUE,TRUE,arg[1],worldBase);
      InitWorldCD(&parameters,1,worldBase);
      CS_WD_FROM_WORLD(worldBase,&world); /* Necessary to generate charts */

      /* Number of system variables */
      m=GetWorldNumSystemVariables(worldBase);
      status.m=m;
      
      /* Read the initial point */
      ReadOneSample(&parameters,arg[1],m,&status.point);
      
      /* anotate the underlying representation */
      status.rep=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      
      epsilon=GetParameter(CT_EPSILON,&parameters);
      delta=GetParameter(CT_DELTA,&parameters);
      r=GetParameter(CT_R,&parameters);
      e=GetParameter(CT_E,&parameters);
      ce=GetParameter(CT_CE,&parameters);
      k=(unsigned int)GetParameter(CT_N_DOF,&parameters);  /* DOF of the manifold */
      if (k==0)
	k=WorldManifoldDimension(&parameters,status.point,worldBase);
      else
	{
	  if (status.dynamics)
	    k=k/2;
	}
      if (k>=m)
	Error("The mobility is larger than the number of variables?");
      status.k=k;
      
      /* space for projections to the charts */
      NEW(t,k,double);

      /* number of degrees of freedom */
      d=GetWorldNDOF(worldBase);
      if (k>d) /* k can be equal to d for non-constrained system */
	Error("The mobility is larger than the number of dof?");
      status.d=d;

      /* number of simplified variables and topology */
      ms=GetWorldSimpTopology(&parameters,&tp,worldBase);

      /* Space for the vector of displacements in DOF space */
      NEW(status.vectDOF,d,double);
      NEW(status.e2d,d,unsigned int); /* menu entry to dof */
      NEW(status.d2e,d,unsigned int)  /* dof to meny entry */
      me=0;
      for(i=0;i<d;i++)
	{
	  status.vectDOF[i]=0;
	  GetWorldRangeDOF(i,&range,worldBase);
	  if (IntervalSize(&range)<ZERO)
	    {
	      /* fixed dof -> not to be shown in the menu */
	      status.d2e[i]=NO_UINT;
	    }
	  else
	    {
	      status.d2e[i]=me;
	      status.e2d[me]=i;
	      me++;
	    }
	  DeleteInterval(&range);
	}
      if (me<k)
	Error("Insuficient non-fixed degrees of freedom");
      
      /* simplify the initial point */
      
      RegenerateWorldSolutionPoint(&parameters,status.point,&pointWithDummies,worldBase);
      WorldGenerateSimplifiedPoint(&parameters,pointWithDummies,&(status.simpPoint),worldBase);
      free(pointWithDummies);
      /* convert the start configuration to DOF */
      NEW(status.pointDOF,d,double);
      WorldSample2DOF(&parameters,status.point,status.pointDOF,worldBase);
      
      /* Temporary space for the new points/dofs */
      NEW(newPointDOF,d,double);
      
      /* Copy of the initial point/DOF used in the reset */
      NEW(initialPointDOF,d,double);
      memcpy(initialPointDOF,status.pointDOF,d*sizeof(double));
      NEW(initialPoint,m,double);
      memcpy(initialPoint,status.point,m*sizeof(double));
      NEW(initialSimpPoint,ms,double);
      memcpy(initialSimpPoint,status.simpPoint,ms*sizeof(double));

      /* Initialize the chart */
      GetWorldSimpInitialBox(&parameters,&ambient,worldBase);
      
      /* Search for a non-real variable */
      hasS=FALSE;
      i=0;
      while((i<ms)&&(!hasS))
	{
	  hasS=(tp[i]==TOPOLOGY_S);
	  i++;
	}
      if (!hasS)
	{
	  free(tp);
	  tp=NULL;
	}
      GetWorldSimpJacobian(&parameters,&J,worldBase);
      
      if (InitChart(&parameters,TRUE,&ambient,tp,ms,k,status.simpPoint,e,ce,r,
		    &J,&world,&chart)!=0)
	Error("Could not define a chart in the start configuration.");
      
      /* It can be the case that the initial point is out of the domain or in collision
         In this case, we initially ignore the inDocmain and inCollision checks.
         When we finally find a inDomain and collision-free configuration, these
         checks are activated again. */
      outside=(!PointInBoxTopology(NULL,TRUE,ms,status.simpPoint,epsilon,tp,&ambient));
      outsideInit=outside;
      if (outside)
	fprintf(stderr,"Initial point is out of domain\n");

      CS_WD_ALL_COLLISIONS(collision,&parameters,status.simpPoint,NULL,&world);
      collisionInit=collision;
      if (collision)
	fprintf(stderr,"Initial point is in collision\n");
      
      /* indices of the dofs used as a parameters */
      NEW(status.ndx,k,unsigned int);
      ndxOK=TRUE;
      if ((unsigned int)argc>1+k)
	{
	  for(i=0;((ndxOK)&&(i<k));i++)
	    {
	      status.ndx[i]=atoi(arg[2+i]);
	      ndxOK=(status.d2e[status.ndx[i]]!=NO_UINT);
	    }
	}
      
      if ((!ndxOK)||((unsigned int)argc<=1+k))
	{	  
	  i=0;
	  /* Select the 'k' actuated (effort-limited) dof */
	  j=0;
	  while((i<status.d)&&(j<k)&&(0))
	    {
	      if ((status.d2e[i]!=NO_UINT)&&(GetJointEffort(GetWorldJoint(i,worldBase))<INF))
		{
		  status.ndx[j]=i;
		  j++;
		}
	      i++;
	    }
	  
	  /* if not enough actuated degrees of freedom are available, just select the first 'k' non-fixed dof  */
	  if (i<k)
	    {
	      i=0;
	      j=0;
	      while((i<status.d)&&(j<k))
		{
		  if (status.d2e[i]!=NO_UINT)
		    {
		      status.ndx[j]=i;
		      j++;
		    }
		  i++;
		}
	      if (i<k)
		Error("Can not select enough input parameters");
	    }
	}
      
      status.changed=FALSE;
      status.end=FALSE;
      status.reset=FALSE;
      status.step=delta; /* default value is 0.05 */

      status.p=&parameters;
      status.w=&world;
      
      gtk_disable_setlocale();
      gtk_init(&argc,&arg);
      
      window_cuikexplore=create_window_cuikexplore((gpointer)(&status));
      gtk_widget_show(window_cuikexplore);
      
      InitPlot3d(NULL,FALSE,argc,arg,&pt);

      PlotWorld(&parameters,&pt,0.0,worldBase);
      MoveWorldDOF(&parameters,&pt,status.pointDOF,worldBase);
      LookPlot3d(&pt);
      
      while(!status.end)
	{
	  if (status.changed)
	    { 
	      /* Change the DOF */
	       for(i=0;i<d;i++)
		 newPointDOF[i]=status.pointDOF[i]+status.vectDOF[i];
	       /* Generate the solution point form the DOF. The result is not a solution
		  of the system of equations */
	       WorldDOF2Sol(&parameters,newPointDOF,&pointWithDummies,NULL,worldBase);
	       /* and simplify the solution point (even if 'pointWithDummies' is not a solution) */
	       WorldGenerateSimplifiedPoint(&parameters,pointWithDummies,&simpPoint,worldBase);
	       free(pointWithDummies);
	       
	       /* Verify that we are not moving orthogonaly to the tangent space */
	       Manifold2Chart(simpPoint,tp,t,&chart);
	       if (Norm(k,t)>(1e-3*status.step))
		 {
		   /* Enforce the equations */
		   if (Chart2Manifold(&parameters,&J,t,tp,NULL,simpPoint,&chart)<INF)
		     {
		       /* Check that the solution point is in domain. Only after we are inside the
			  domain for the first time */
		       in=PointInBoxTopology(NULL,TRUE,ms,simpPoint,epsilon,tp,&ambient);
		       if ((outside)||(in))
			 {
			   /* and not in collision. Collision are not considered, thouth, while ouside
			      the domain */
			   CS_WD_ALL_COLLISIONS(collide,&parameters,simpPoint,status.simpPoint,&world);
			   if ((collision)||(!collide))
			     {
			       /* here we have a new valid solution point where it should be possible
				  to generate a new chart */
			       CopyChart(&chartTmp,&chart);
			       DeleteChart(&chart);
			       
			       if (InitChart(&parameters,TRUE,&ambient,tp,ms,k,simpPoint,e,ce,r,
					     &J,&world,&chart)==0)
				 {
				   memcpy(status.simpPoint,simpPoint,sizeof(double)*ms);
				   free(status.point);
				   /* chart2manifold changed the simpPoint -> regenerate the original form it */
				   RegenerateWorldOriginalSystemPoint(&parameters,simpPoint,&(status.point),worldBase);
				   /* and the DOF from the original */
				   WorldSample2DOF(&parameters,status.point,status.pointDOF,worldBase);
				   /* and plot using DOF */
				   MoveWorldDOF(&parameters,&pt,status.pointDOF,worldBase);

				   if (outside)
				     {
				       /* Check if whe already reached the valid domain */
				       outside=(!in);
				       if (!outside)
					 fprintf(stderr,"Entering the domain-----------------------------------------------------------\n"); /* outside flag will remain to false from now on */
				     }
				   if (collision)
				     {
				       collision=collide;
				       if (!collision)
					 fprintf(stderr,"Entering C-free -----------------------------------------------------------\n"); /* outside flag will remain to false from now on */
				     }
				 }
			       else
				 {
				   CopyChart(&chart,&chartTmp);
				   fprintf(stderr,"Error defining chart. Staying in previous point.\n");
				 }
			       DeleteChart(&chartTmp);
			     }
			   else
			     fprintf(stderr,"Collision\n");
			 }
		       else
			 fprintf(stderr,"Out of the ambient space\n");
		     }
		   else
		     fprintf(stderr,"Error in parametrization. Change it?\n");
		 }
	       else
		 fprintf(stderr,"Singularity (%f). Change the parametrization?\n",Norm(k,t));

	       free(simpPoint);
	       
	       /* Reset the displacement vector (if only one step must be executed) */
	       if (status.oneStep)
		 {
		   for(i=0;i<d;i++)
		     status.vectDOF[i]=0;
		   status.changed=FALSE;
		   status.oneStep=FALSE;	      
		 }
	       else
		 usleep(10000);
	    }
	  if (status.reset)
	    {
	      memcpy(status.pointDOF,initialPointDOF,d*sizeof(double));
	      memcpy(status.point,initialPoint,m*sizeof(double));
	      memcpy(status.simpPoint,initialSimpPoint,ms*sizeof(double));
	      DeleteChart(&chart);
	      if (InitChart(&parameters,TRUE,&ambient,tp,ms,k,status.simpPoint,e,ce,r,
			    &J,&world,&chart)!=0)
		Error("Can not move to the initial point?");
	      
	      MoveWorldDOF(&parameters,&pt,status.pointDOF,worldBase);
	      status.reset=FALSE;
	      outside=outsideInit;
	      collision=collisionInit;
	    }
	  gtk_main_iteration_do(FALSE);
	}      

      ClosePlot3d(TRUE,&pt);

      DeleteChart(&chart);
      DeleteBox(&ambient);
      if (tp!=NULL)
	free(tp);
      DeleteJacobian(&J);

      free(newPointDOF);
      free(t);
      free(initialPointDOF);
      free(initialPoint);
      free(initialSimpPoint);

      free(status.pointDOF);
      free(status.point);
      free(status.simpPoint);
      free(status.ndx);
      free(status.vectDOF);
      free(status.d2e);
      free(status.e2d);

      CS_WD_DELETE(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikexplore <world>.world [dof_1 ... dof_k]\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem.\n");
      fprintf(stdout,"     [dof_1 ... dof_k] Index of the variables to be used\n");
      fprintf(stdout,"                       as parameters.\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
