#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "cuiksystem.h"
#include "link.h"

#include <stdlib.h>

/** \file cuikgradient.c

    \brief Main body of the \ref cuikgradient.c "cuikgradient" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikgradient    [label="cuikgradient"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      kin     [label="cuik"   color="#ff9999" ];
      sol     [label="sol/stdout"     color="#ff9999" ];

      param -> cuikgradient
      kin -> cuikgradient
      cuikgradient -> sol;
    }
    \enddot
    </center>

     Find a solution of a cuiksystem set of equations using a gradient descent method.
     It is based on an iterative process starting from a random point sampled in the initial box. 
     <br>
     We have a system of equations of the form:
         - f_1(x_1....x_m)=0
         - ...
         - f_n(x_1....x_m)=0
	 .
     The gradient descent method minimizes an error function defined as
         - E(x_1....x_m)=f_1(x_1....x_m)^2+....f_n(x_1....x_m)^2
	 .
     Observe that the gradient of this function is
         - dif E / dif x_i = 2*f_1(x_1....x_m)*dif f_1/dif x_i + ... + 2*f_n(x_1....x_m)*dif f_n/dif x_i
	 .
     Which can be expressed as
         - J_f^t * (f_1....f_n)
	 .
     Where J_f^t is the transposed of the Jacobian of the initial system and
     (f_1....f_n) is the evaluation of this system.
     <br>
     Inequalities and domain boundaries are not (yet) taken into account.
     <br>
     The method can converge to a local minima or to a point out of the domain
     boundaries.

     \sa cuikgradientworld.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuikgradient.c "cuikgradient" application.

   Main body of the \ref cuikgradient.c "cuikgradient" application.

   Use:
      - \b cuikgradient \e num_samples \e problem_name.cuik
      .
   where 
      - \e problem_name contains the kinematic equations. 
      - \e num_samples is the number of times we want to apply the gradient descent process.
      .
   In this case we sample points at random in the initial box and try to
   converge to the manifold. If the gradient process succeeds, we print the
   solution point, a tiny box around it, and the error in the solution point.

   The program can also be used as:
      - \b cuikgradient \e problem_name.cuik
      .
   where 
      - \e problem_name contains the kinematic equations. 
      .
   In this case we search for a solution file and we try to converge to a point
   for each one of the boxes in the solution file. If the solution file does not
   exists an error is triggered.

   In any cases \em .cuik extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikgradient command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  if (argc>1)
    {
      Tparameters parameters;
      TCuikSystem cuiksystem;

      Tfilename fcuik;
      Tfilename fparam;

      boolean dynamics;
      
      unsigned int i,n,k,m,ns;
      double *sol;
      boolean state;
      boolean *systemVars;
      boolean *systemVarsDynamics;
      boolean *posVars;

      Tbox b_sol,b_dynamics;
      unsigned int n_sol;

      unsigned int ri;
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam)); 

      if (GetParameter(CT_DYNAMICS,&parameters)>0)
	{
	  /* In problems with dynamics we considere only position constraints
	     and set the velocity to 0 */
	  dynamics=TRUE;
	  /* Des-activate the automatic generation of velocity equations */
	  ChangeParameter(CT_DYNAMICS,0,&parameters);
	}
      else
	dynamics=FALSE;
      
      /* Read the problem file */
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);
      fprintf(stderr,"Reading cuik file                 : %s\n",GetFileFullName(&fcuik));
      
      /* Even if the automatic generation of velocity equations is deactivated,
	 the input file may already include such equations. Ifso the user wants to
         execte gradient over the state manifold -> deactivate the zero
         velocity generation */
      if (CuikHasVelocity(&parameters,&cuiksystem))
	dynamics=FALSE;
      
      ri=(unsigned int)time(NULL);
      //ri=1405333052;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);
      
      n=GetCSSystemVars(&systemVars,&cuiksystem);
      ns=GetCSNumSystemVariables(&cuiksystem);
      NEW(sol,n,double);
      if (dynamics)
	{
	  InitBox(2*n,NULL,&b_dynamics); /* initialized as zeros */
	  NEW(systemVarsDynamics,2*n,boolean);
	  NEW(posVars,2*n,boolean);
	  for(i=0;i<n;i++)
	    {
	      posVars[i]=TRUE;
	      posVars[n+i]=FALSE;
	      systemVarsDynamics[i]=systemVars[i];
	      systemVarsDynamics[n+i]=systemVars[i];
	    }
	}
 
      if (argc>2)
	{
	  unsigned int nErrors;

	  m=atoi(arg[2]);
	  n_sol=1;

	  nErrors=0;
	  for(k=0;k<m;k++)
	    {
	      state=CuikGradient(&parameters,sol,&b_sol,&cuiksystem);
	      
	      printf("Sample: %u\n",k+1);
	      if (state)
		{
		  printf("   Solution %u\n",n_sol);
		  n_sol++;
		  printf("   Solution Point: ");
		  for(i=0;i<n;i++)
		    {
		      if (systemVars[i])
			printf("%.16g ",sol[i]);
		    }
		  if (dynamics)
		    {
		      /* Zero velocity. This always fulfill the velocity equations */
		      for(i=0;i<ns;i++)
			printf("0 ");
		    }
		  printf("\n   Solution Box  : ");
		  
		  if (dynamics)
		    {
		      /* b_dynamics is a box with b_sol at the first positon and zeros at the end */
		      SetBoxSubset(posVars,&b_sol,&b_dynamics);
		      /* Print the system variables for b_dynamics. fullSystemVariables is a 
		         duplicate of systemVariables */
		      PrintBoxSubset(stdout,systemVarsDynamics,NULL,&b_dynamics);
		    }
		  else  
		    PrintBoxSubset(stdout,systemVars,NULL,&b_sol);
		  
		  printf("   Solution error: %g\n",ErrorInSolution(&b_sol,&cuiksystem));
		  printf("   Solution error: %g\n",ErrorInCSEquations(&parameters,sol,&cuiksystem));
		}
	      else
		{
		  printf("   Error in gradient\n");
		  nErrors++;
		}
	      
	      DeleteBox(&b_sol);
	    } 
	  printf("Gradient error ratio: %.2f\n",(double)nErrors/(double)m);
	}
      else
	{
	  /* iterate over all boxes */ 
	  Tfilename fsol,fgradient;
	  FILE *fin;
	  FILE *fout;
	  Tbox box,b_sol;
	  unsigned int out;
	  int token;
	  unsigned int nb;
	  unsigned int rep;

	  CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsol);
	  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
	  if (rep==REP_JOINTS)
	    CreateFileName(NULL,arg[1],"_gradient",JOINTS_EXT,&fgradient);
	  else
	    CreateFileName(NULL,arg[1],"_gradient",LINKS_EXT,&fgradient);

	  fin=fopen(GetFileFullName(&fsol),"r");
	  if (!fin)
	    Error("Could not open the input file with the solutions");
	  fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsol));

	  fout=fopen(GetFileFullName(&fgradient),"w");
	  fprintf(stderr,"Writing samples to                : %s\n",GetFileFullName(&fgradient));

	  nb=0;
	  do {
	    token=ReadBox(fin,&box);
	    if (token!=EOF)
	      { 
		out=CuikGradientInBox(&parameters,&box,sol,&b_sol,&cuiksystem);
		nb++;
		
		switch(out)
		  {
		  case DIVERGED:
		    fprintf(fout,"*DV \n");
		    break;
		  case CONVERGED_OUTSIDE_GLOBAL:
		    /* Use the center of the box */
		    fprintf(fout,"*CO(%g) \n   ",ErrorInSolution(&b_sol,&cuiksystem));
		    break;
		  case CONVERGED_IN_GLOBAL:
		    fprintf(fout,"*CG(%g) \n   ",ErrorInSolution(&b_sol,&cuiksystem));
		    break;
		  case CONVERGED_IN_BOX:
		    fprintf(fout,"*CV(%g) \n   ",ErrorInSolution(&b_sol,&cuiksystem));
		    break;
		  default:
		    Error("Unknown output from CuikGradientInBox");
		  }

		for(i=0;i<n;i++)
		  {
		    if (systemVars[i])
		      fprintf(fout,"%.12g ",sol[i]);
		  }
		if (dynamics)
		  {
		    /* Zero velocity. This always fulfill the velocity equations */
		    for(i=0;i<ns;i++)
		      printf("0 ");
		  }
		fprintf(fout,"\n");

		DeleteBox(&box);
		DeleteBox(&b_sol);
	      }
	  } while (token!=EOF);
	  
	  fclose(fin);
	  fclose(fout);
	  DeleteFileName(&fsol);
	  DeleteFileName(&fgradient);
	}

      free(systemVars);
      free(sol);

      DeleteCuikSystem(&cuiksystem);
      DeleteParameters(&parameters);

      DeleteFileName(&fcuik);
      DeleteFileName(&fparam);
    }
  else
    { 
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuikgradient <problem filename>.cuik <n>\n");
      fprintf(stderr,"      cuikgradient <problem filename>.cuik \n");
      fprintf(stderr,"  where\n"); 
      fprintf(stderr,"    <n> is the number of gradient descents to execute\n");
      fprintf(stderr,"    <problem filename> contains the kinematic equations\n");
      fprintf(stderr,"              (the '.cuik' extension is not required)\n");
      fprintf(stderr,"  In the first case, we attempt to generate <n> random samples.\n");
      fprintf(stderr,"  In the second case, we generte one sample for each one of\n");
      fprintf(stderr,"  the solution boxes in the  <problem filename>.sol file.\n");
    }

  return(EXIT_SUCCESS);
}
