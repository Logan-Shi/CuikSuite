#include "world.h"
#include "basic_algebra.h"
#include "error.h"

#include <math.h>

/** \file cuikworldforces.c

    \brief Main body of the \ref cuikworldforces.c "cuikworldforces" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikworldforces    [label="cuikworldforces"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"     color="#ff9999" ];
      forces  [label="forces"  color="#ff9999" ];

      param -> cuikworldforces
      world -> cuikworldforces
      sol -> cuikworldforces
      cuikworldforces -> forces;
    }
    \enddot
    </center>

    This application extracts forces from a set of solution boxes.
*/

/** 
   \brief Main body of the \ref cuikworldforces.c "cuikworldforces"  application.

   Main body of the \ref cuikworldforces.c "cuikworldforces" application.

   Use: <br>
     - \b cuikworldforces \e world_name.world \e solutions_name.sol [num force [mode]]
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e solutions_name: Is the solution set for which to extract the forces.
     - \e num_force: Optional. Use when only the force on one element is required.
                     In this case the ouput file is a cost file and the 
                     force is scaled to [0,1]. Used for plotting.
     - \e mode: Optional and only if num_force is given. Exponential used when
                scaling the values to the [0,1] range. If possitive
		differences in values close to 1 are increased. If negative
		the differences in the lower levels are increased. 
		The default value is 1 (no deformation is applied).
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
      Tworld world;
      Tparameters parameters;

      Tbox box;
      int token;
      unsigned int i,k,nf;
      unsigned int *forceVars;

      Tfilename fforces;
      Tfilename fsols;
      Tfilename fparam;

      FILE *fin,*fout;

      boolean oneForce;
      unsigned int fndx,nb;
      double *force;
      double mode;
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      nf=WorldForceVarsIndices(&parameters,&forceVars,&world);
      if (nf==0)
	Error("The input world does not include any force variable");
      
      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      fin=fopen(GetFileFullName(&fsols),"r");
      if (!fin)
	Error("The file with the solution boxes can not be opened");

      mode=1.0;
      if (argc>3)
	{
	  oneForce=TRUE;
	  fndx=atoi(arg[3]);
	  if (fndx>=nf)
	    Error("Too large force index");
	  if (argc>4)
	    mode=atof(arg[4]);
	}
      else
	oneForce=FALSE;

      if (oneForce)
	{
	  /* Single force to output: cost file */
	  CreateFileName(NULL,arg[2],NULL,COST_EXT,&fforces);
	  fprintf(stderr,"Writing force to file             : %s\n",GetFileFullName(&fforces));

	  /* Count the number of boxes in the input file */
	  nb=0;
	  do {
	    token=ReadBox(fin,&box);
	    if (token!=EOF)
	      {
		nb++;
		DeleteBox(&box);
	      }
	  } while(token!=EOF);
	  /* re-open the input file for a second reading */
	  fclose(fin);
	  fin=fopen(GetFileFullName(&fsols),"r");
	  
	  /* allocate space for the selected force */
	  NEW(force,nb,double);
	}
      else
	{
	  /* all forces to output: forces file */
	  CreateFileName(NULL,arg[2],NULL,FORCES_EXT,&fforces);
	  fprintf(stderr,"Writing forces file               : %s\n",GetFileFullName(&fforces));
	}
      fout=fopen(GetFileFullName(&fforces),"w");
      if (!fout)
	Error("The file for the forces can not be opened");

      k=0;
      do {
	token=ReadBox(fin,&box);
	if (token!=EOF)
	  {
	    /* the box must contain at lasat as many variables
	       as those in the force index array */
	    if (GetBoxNIntervals(&box)<forceVars[nf-1])
	      Error("Box size missmatch");
	    
	    if (oneForce)
	      /* if we only need one force, store it */
	      force[k]=fabs(IntervalCenter(GetBoxInterval(forceVars[fndx],&box)));
	    else
	      {
		/* When we need all forces, we can store them on the fly */
		for (i=0;i<nf;i++)
		  fprintf(fout,"%.12f ",IntervalCenter(GetBoxInterval(forceVars[i],&box)));
		fprintf(fout,"\n");
	      }
	    DeleteBox(&box);
	    k++;
	  }
      } while(token!=EOF);

      if (oneForce)
	{
	  /* In the case of just one force -> scale it (we will use it for plotting) */
	  /* do not use <1e-4 as lower limit (charts with cost 0 are not plotted or 
	     are plotted in black!) */
	  Vector2Range(1e-3,1.0,mode,nb,force);
	  SaveVector(fout,nb,force);
	}
      
      fclose(fin);
      fclose(fout);

      free(forceVars);
      
      DeleteFileName(&fforces);  
      DeleteFileName(&fsols);      
      DeleteFileName(&fparam);

      DeleteWorld(&world);
      DeleteParameters(&parameters);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikworldforces <world>.world <solutions>.sol [num force [mode]]\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <solutions>:  Solutions for which to extract the forces.\n");
      fprintf(stdout,"     [num force]:  Optional. The element in which we are intersted\n");
      fprintf(stdout,"                   In this case the output is a cost file and the force\n");
      fprintf(stdout,"                   is scaled to [0,1], as required for plotting.\n");
      fprintf(stdout,"     [mode]: Optional and only if num_force is given. Exponential used when\n");
      fprintf(stdout,"             scaling the values to the [0,1] range. This is used to exaggerate\n");
      fprintf(stdout,"             the values around 0 or around 1 depending of whether this parameter\n");
      fprintf(stdout,"             is negative of possitive. The larger the absolute value, the larger the\n");
      fprintf(stdout,"             exageration.\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
