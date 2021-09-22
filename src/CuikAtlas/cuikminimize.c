#include "world.h"
#include "atlas.h"
#include "filename.h"
#include "samples.h"
#include "error.h"
#include "parameters.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/** \file cuikminimize.c

    \brief Main body of the \ref cuikminimize.c "cuikminimize" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikminimize    [label="cuikatlasrrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];
      tens    [label="tens"    color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikminimize
      tens -> cuikminimize
      samples -> cuikminimize
      cuikminimize -> path;
    }
    \enddot
    </center>

    Gradient-based minimization of the potential energy of a conformation.

    This only works for tensegrity structures. Other structures do not
    have potential energy.
*/

/** 
   \brief Main body of the \ref cuikminimize.c "cuikminimize" application.

   Main body of the \ref cuikminimize.c "cuikminimize" application.

   Use:
       - \b cuikminimize \e problem_name.tens [max_iterations]
       .
   where
       - \e problem_name.tens contains the tensegrity description.
       - \e max_iterations is the optional maximum number of iterations. The default is 1000.
       .
   The \e .tens extension is optional

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikminimize command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{      
  if (argc>1)
    { 
      Tworld world;            /* The tensegrity description. */
      Tatlas atlas;            /* The atlas defined during minimization. */
      Tparameters parameters;  /* Parameters used in the Cuik process. */

      Tfilename fparam;
      Tfilename fatlas;
  
      double *s1;              /* Starting point for the minimization. */

      unsigned int maxIterations;
      
      TAtlasBase ab;
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));	    
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      if (GetParameter(CT_DYNAMICS,&parameters)>0)
	Error("cuikminimize do not work (yet) for problems with dynamics");
      
      /*Init the world (tensegrity only)*/
      if (!InitTensegrityFromFile(&parameters,arg[1],&world))
	Error("Can not open the tensegrity file");
      CS_WD_FROM_WORLD(&world,&ab);

      /* Read the start sample */
      ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&ab),&s1);

      if (argc>2)
	{
	  maxIterations=atoi(arg[2]);
	  if (maxIterations==0)
	    Error("Wrong maximum number of iterations");
	}
      else
	maxIterations=1000;
      fprintf(stderr,"Number of iterations              : %u\n",maxIterations);
      
      /* Minimize */
      MinimizeOnAtlas(&parameters,arg[1],s1,&ab,maxIterations,
		      WorldPotentialEnergy,
		      WorldForceField,
		      (void *)(&world),&atlas);
      

      /* Save the results (the tracked paths are already saved in MinimizeOnAtlas) */
      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Writing atlas to                  : %s\n",GetFileFullName(&fatlas));
      SaveAtlas(&parameters,&fatlas,&atlas);

      /* Release memory */
      free(s1);
      DeleteAtlas(&atlas);
      DeleteParameters(&parameters);
      DeleteWorld(&world);

      DeleteFileName(&fparam);
      DeleteFileName(&fatlas);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikminimize <problem filename>.tens [max iterations]\n");
     fprintf(stderr,"  where <problem filename>.tens contains the tensegrity description\n");
     fprintf(stderr,"        [max iterations] is the optional maximum number of iterations\n");
     fprintf(stderr,"                         The default is 1000\n");
     fprintf(stderr,"  The extension for the problem file (ex. tens) is not required.\n");
   }
  return(EXIT_SUCCESS);
}

