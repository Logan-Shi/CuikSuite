#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"
#include "random.h"

#include <stdlib.h>

/** \file cuikpathlength.c

    \brief Main body of the \ref cuikpathlength.c "cuikpathlength" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      param             [label="param"   color="#ff9999" ];
      world             [label="world"   color="#ff9999" ];
      cuikpathlength    [label="cuikpathlength"  color="#99ff99" shape=ellipse];
      path              [label="path"    color="#ff9999" ];

      param -> cuikpathlength;
      world -> cuikpathlength;
      path -> cuikpathlength;
    }
    \enddot
    </center>

    Compute the length of the path.
*/

/** 
   \brief Main body of the \ref cuikpathlength.c "cuikpathlength" application.

   Main body of the \ref cuikpathlength.c "cuikpathlength" application.

   Use:
       - \b cuikpathlength \e base_name [\e path_file]
       .
   where
       - \e base_name base name for the parameter, world and path files.
       - \e path_file [optional] the file with the path.
       .

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikpathlength command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  Tfilename fpath;

  unsigned int *tp;        /* topology */
  
  /* input path */
  unsigned int nvs,ns;
  double **path;
  boolean *sv;  /* variables to use in the path length computation */
  
  if (argc>=2)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/ 
      CS_WD_INIT(&parameters,arg[1],&world);

      CS_WD_GET_TOPOLOGY(&parameters,&tp,&world);
 
      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fpath);
      else
	CreateFileName(NULL,arg[1],"_path",SOL_EXT,&fpath);

      
      if ((!KINEMATIC_SUBSPACE)||(ON_CUIKSYSTEM(&world)))
	sv=NULL;
      else
	WorldSimpKinematicVars(&parameters,&sv,GET_WORLD(&world)); /* Path length on kinematic variables only */
      
      if (LoadSamples(&fpath,&nvs,&ns,&path))
	{
	  fprintf(stderr,"Path length                       : %g\n",PathLength(tp,sv,nvs,ns,path));
	  DeleteSamples(ns,path);
	}
      else
	Error("Could not read the input path file");

      free(tp);
      if (sv!=NULL)
	free(sv);
      
      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);

      DeleteFileName(&fparam);
      DeleteFileName(&fpath);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikpathlength <base filename> [<path file>]\n");
     fprintf(stderr,"  where <base filename> is used for the parameters, world, and path files.\n");
     fprintf(stderr,"        <path file> [optional] is the file with the path.\n");
   }
  return(EXIT_SUCCESS);
}

