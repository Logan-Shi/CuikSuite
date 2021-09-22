#include "bioworld.h"
#include "parameters.h"

#include "atlas.h"
#include "filename.h"
#include "samples.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/** \file cuikbiominimize.c

    \brief Main body of the \ref cuikbiominimize.c "cuikbiominimize" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikbiominimize    [label="cuikatlasrrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];
      pdb     [label="pdb"     color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikbiominimize
      pdb -> cuikbiominimize
      samples -> cuikbiominimize
      cuikbiominimize -> path;
    }
    \enddot
    </center>

    Gradient-based minimization of the energy of a conformation.

    This energy minmization respectes the rigid-geometry all the time and
    it even respect the loop closure constraitns, if any. This is something
    not usually considered in molecular biology.

    The minimization tries to detect the bifurcations (if the corresponding
    parameter is set to 1). If a bifurcation is crossed, the minimization
    branches and follows different branches to different local minima.
    In some cases, however, the minimization a point is just on a
    singularity. In this case we can not determine if it is a bifurcation
    and a warning is printed. (We can only detect bifurcation if we have
    a point at each side of a singularity.)
    To solve this issue you can eigher decrease
    epsilon (to increase the numerical accuracy and, thus to decrease
    the areas around a singularity that are considered singular) or to
    increase delta (to step over this area).

*/

/** 
   \brief Main body of the \ref cuikbiominimize.c "cuikbiominimize" application.

   Main body of the \ref cuikbiominimize.c "cuikbiominimize" application.

   Use:
       - \b cuikbiominimize \e problem_name.pdb
       .
   where
       - \e problem_name.pdb contains the molecule information.
       .
   The \e .pdb extension is compulsatory (however any extension valid for OpenBabel can
   be used).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikbiominimize command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{      
  if (argc>1)
    { 
      TBioWorld bioWorld;      /* The molecular information.  */
      Tatlas atlas;            /* The atlas defined during minimization. */
      Tparameters parameters;  /* Parameters used in the Cuik process. */

      Tfilename fparam;
      Tfilename fatlas;
  
      double *s1;              /* Starting point for the minimization. */

      TAtlasBase ab;
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));	    
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      if (!InitBioWorld(&parameters,arg[1],NO_UINT,&s1,&bioWorld))
	Error("Could not read the molecular information");
      free(s1);
      CS_WD_FROM_WORLD(BioWorldWorld(&bioWorld),&ab);

      /* Read the start sample */
      ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&ab),&s1);
     
      /* Minimize */
      MinimizeOnAtlas(&parameters,arg[1],s1,&ab,100,
		      BioWorldEnergy,(void *)(&bioWorld),NULL,&atlas);
      

      /* Save the results (the tracked paths are already saved in MinimizeOnAtlas) */
      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Writing atlas to                  : %s\n",GetFileFullName(&fatlas));
      SaveAtlas(&parameters,&fatlas,&atlas);

      /* Release memory */
      free(s1);
      DeleteAtlas(&atlas);
      DeleteParameters(&parameters);
      DeleteBioWorld(&bioWorld);

      DeleteFileName(&fparam);
      DeleteFileName(&fatlas);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikbiominimize <problem filename>.pdb\n");
     fprintf(stderr,"  where <problem filename>.pdb contains the molecular information\n");
     fprintf(stderr,"  The extension for the problem file (ex. pdb) is required.\n");
     fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
   }
  return(EXIT_SUCCESS);
}

