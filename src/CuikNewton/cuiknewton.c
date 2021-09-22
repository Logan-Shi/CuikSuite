#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "cuiksystem.h"
#include "link.h"

#include <stdlib.h>

/** \file cuiknewton.c

    \brief Main body of the \ref cuiknewton.c "cuiknewton" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiknewton    [label="cuiknewton"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      kin     [label="cuik"   color="#ff9999" ];
      sol     [label="sol/stdout"     color="#ff9999" ];

      param -> cuiknewton
      kin -> cuiknewton
      cuiknewton -> sol;
    }
    \enddot
    </center>

     Find a solution of a cuiksystem set of equations using the Newton-Rhapson method.
     It is based on an iterative process starting from a random point sampled in the initial box. 
     <br>
     If the system is undetermined, i.e. number of variables higher than number of equations, 
     the method is based on the Moor-Penrose generalised inverse.  
     <br>
     The method can diverge if the initial point is far from the solutions of the system.

     \sa cuiknewtonworld.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuiknewton.c "cuiknewton" application.

   Main body of the \ref cuiknewton.c "cuiknewton" application.

   Use:
      - \b cuiknewton \e num_samples \e problem_name.cuik
      .
   where 
      - \e problem_name contains the kinematic equations. 
      - \e num_samples is the number of times we want to apply the Newton process.
      .
   In this case we sample points at random in the initial box and try to
   converge to the manifold. If the Newton process succeeds, we print the
   solution point, a tiny box around it, and the error in the solution point.

   The program can also be used as:
      - \b cuiknewton \e problem_name.cuik
      .
   where 
      - \e problem_name contains the kinematic equations. 
      .
   In this case we search for a solution file and we try to converge to a point
   for each one of the boxes in the solution file. If the solution file does not
   exists an error is triggered.

   In any cases \em .cuik extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiknewton command itself and its arguments).
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
      
      if (GetParameter(CT_MAX_NEWTON_ITERATIONS,&parameters)<1)
	ChangeParameter(CT_MAX_NEWTON_ITERATIONS,100,&parameters);

      /* Read the problem file */
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);
      fprintf(stderr,"Reading cuik file                 : %s\n",GetFileFullName(&fcuik));

      /* Even if the automatic generation of velocity equations is deactivated,
	 the input file may already include such equations. Ifso the user wants to
         execte Newton over the state manifold -> deactivate the zero
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
	      state=CuikNewton(&parameters,sol,&b_sol,&cuiksystem);
	      
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
		  printf("   Error in Newton\n");
		  nErrors++;
		}
	      
	      DeleteBox(&b_sol);
	    } 
	  printf("Newton error ratio: %.2f\n",(double)nErrors/(double)m);
	}
      else
	{
	  /* iterate over all boxes */ 
	  Tfilename fsol,fnewton;
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
	    CreateFileName(NULL,arg[1],"_newton",JOINTS_EXT,&fnewton);
	  else
	    CreateFileName(NULL,arg[1],"_newton",LINKS_EXT,&fnewton);

	  fin=fopen(GetFileFullName(&fsol),"r");
	  if (!fin)
	    Error("Could not open the input file with the solutions");
	  fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsol));

	  fout=fopen(GetFileFullName(&fnewton),"w");
	  fprintf(stderr,"Writing samples to                : %s\n",GetFileFullName(&fnewton));

	  nb=0;
	  do {
	    token=ReadBox(fin,&box);
	    if (token!=EOF)
	      { 
		out=CuikNewtonInBox(&parameters,&box,sol,&b_sol,&cuiksystem);
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
		    Error("Unknown output from CuikNewtonInBox");
		  }

		for(i=0;i<n;i++)
		  {
		    if (systemVars[i])
		      fprintf(fout,"%.16g ",sol[i]);
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
	  DeleteFileName(&fnewton);
	}

      if (dynamics)
	{
	  DeleteBox(&b_dynamics);
	  free(systemVarsDynamics);
	  free(posVars);
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
      fprintf(stderr,"      cuiknewton <problem filename>.cuik <n>\n");
      fprintf(stderr,"      cuiknewton <problem filename>.cuik \n");
      fprintf(stderr,"  where\n"); 
      fprintf(stderr,"    <n> is the number of Newtons to execute\n");
      fprintf(stderr,"    <problem filename> contains the kinematic equations\n");
      fprintf(stderr,"              (the '.cuik' extension is not required)\n");
      fprintf(stderr,"  In the first case, we attempt to generate <n> random samples.\n");
      fprintf(stderr,"  In the second case, we generte one sample for each one of\n");
      fprintf(stderr,"  the solution boxes in the  <problem filename>.sol file.\n");
    }

  return(EXIT_SUCCESS);
}
