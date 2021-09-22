#include "world.h"
#include "dynamics.h"
#include "error.h"

#include <math.h>

/** \file cuikxdot.c

    \brief Main body of the \ref cuikxdot.c "cuikxdot" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikxdot    [label="cuikxdot"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"     color="#ff9999" ];
      acc     [label="sol"  color="#ff9999" ];

      param -> cuikxdot
      world -> cuikxdot
      sol -> cuikxdot
      cuikxdot -> acc;
    }
    \enddot
    </center>

    This application extracts accelerations from a set of solution boxes.
*/

/** 
   \brief Main body of the \ref cuikxdot.c "cuikxdot"  application.

   Main body of the \ref cuikxdot.c "cuikxdot" application.

   Use: <br>
     - \b cuikxdot \e world_name.world \e solutions_name.sol 
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e solutions_name: Is the solution set for which to extract the accelerations.
     - \e action: Action for which to compute the acceleration.
     .
   File extensions are optional. 

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  
  if (argc>2)
    {
      TAtlasBase w;
      Tworld *world;
      Tparameters parameters;

      TDynamicSpace ds; 
      double *u;
      double *point,*spoint;
      double *acc;
      unsigned int sz,ns,j,n,k,ndof,nBoxes;
      Tlist boxList;
      Tbox *box;
      Titerator i;
      TJacobian sJ;

      FILE *fout;
  
      Tfilename facc;
      Tfilename fsols;
      Tfilename fparam;

      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      if (GetParameter(CT_DYNAMICS,&parameters)<0.5)
	Error("cuikxdot requires the dynamics");

      ndof=GetParameter(CT_N_DOF,&parameters);
      if (ndof%2)
	Error("The degrees of freedom must be even");
      ndof/=2;
      if (argc-2<(int)ndof)
	Error("Not enough input parameters to define an action");
      NEW(u,ndof,double);
      for(j=0;j<ndof;j++)
	u[j]=atof(arg[j+2]);

      InitCSWDFromFile(&parameters,arg[1],&w);
      world=GET_WORLD(&w);

      CS_WD_GET_SIMP_JACOBIAN(&parameters,&sJ,&w);
      InitDynamicSpace(&parameters,FALSE,&sJ,&w,&ds);
      
      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      ReadListOfBoxes(GetFileFullName(&fsols),&boxList);
      nBoxes=ListSize(&boxList);
      if (nBoxes==0)
	Error("Empty solution file");
      
      CreateFileName(NULL,arg[2],"_dot",SOL_EXT,&facc);
      fprintf(stderr,"Writing acceleration file         : %s\n",GetFileFullName(&facc));

      fout=fopen(GetFileFullName(&facc),"w");
      if (!fout)
	Error("Output file for accelerations can not be opened");
      
      /* Compute the energy for each conformation */
      InitIterator(&i,&boxList);
      First(&i);
      k=0;
      while(!EndOfList(&i))
	{
	  box=(Tbox *)GetCurrent(&i);
	  if (k==0)
	    {
	      n=GetBoxNIntervals(box);
	      NEW(point,n,double);
	      NEW(acc,n,double); /* The size of acc is always less than n (less due to possible simplifications) */
	    }
	  GetBoxCenter(NULL,point,box);

	  ns=WorldGenerateSimplifiedPointFromSystem(&parameters,point,&spoint,world);
	  
	  sz=Getxdot(&parameters,spoint,u,acc,&ds);

	  if (ns!=sz)
	    Error("xdot size missmatch");
	  
	  PrintVector(fout,"",sz,acc);

	  free(spoint);
	  
	  k++;
	  Advance(&i);
	}
	
      fclose(fout);

      DeleteFileName(&fsols);
      DeleteFileName(&facc);
      DeleteFileName(&fparam);

      free(acc);
      free(u);
      free(point);
      DeleteListOfBoxes(&boxList);
      DeleteParameters(&parameters);

      DeleteFileName(&facc);  
      DeleteFileName(&fsols);      
      DeleteFileName(&fparam);

      DeleteDynamicSpace(&ds);
      DeleteJacobian(&sJ);
      CS_WD_DELETE(&w);
      DeleteParameters(&parameters);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikxdot <world>.world <solutions>.sol <action>\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <solutions>:  Solutions for which to extract the acceleratinos.\n");
      fprintf(stdout,"     action: Action for which to compute the acceleration\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
