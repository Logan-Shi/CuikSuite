#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"
#include "random.h"

#include <stdlib.h>

/** \file cuikpatheffort.c

    \brief Main body of the \ref cuikpatheffort.c "cuikpatheffort" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      param             [label="param"   color="#ff9999" ];
      world             [label="world"   color="#ff9999" ];
      cuikpatheffort    [label="cuikpatheffort"  color="#99ff99" shape=ellipse];
      path              [label="path"    color="#ff9999" ];

      param -> cuikpatheffort;
      world -> cuikpatheffort;
      path -> cuikpatheffort;
    }
    \enddot
    </center>

    Compute the (approximatted) control effort of the path.
*/

/** 
   \brief Main body of the \ref cuikpatheffort.c "cuikpatheffort" application.

   Main body of the \ref cuikpatheffort.c "cuikpatheffort" application.

   Use:
       - \b cuikpatheffort \e base_name [\e path_file]
       .
   where
       - \e base_name base name for the parameter, world and path files.
       - \e path_file [optional] the file with the path.
       .

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikpatheffort command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  Tworld world;            /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  Tfilename fpath;
  
  /* input path */
  unsigned int nvs,ns;
  double **path;
  
  if (argc>=2)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      if (GetParameter(CT_DYNAMICS,&parameters)>0)
	Error("cuikpatheffort do not work for problems with dynamics");
      
      /*Read the world from file*/
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fpath);
      else
	CreateFileName(NULL,arg[1],"_path",SOL_EXT,&fpath);

      if (LoadSamples(&fpath,&nvs,&ns,&path))
	{
	  fprintf(stderr,"Path control effort               : %g\n",PathEffort(&parameters,nvs,ns,path,&world));
	  DeleteSamples(ns,path);
	}
      else
	Error("Could not read the input path file");

      DeleteWorld(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fpath);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikpatheffort <base filename> [<path file>]\n");
     fprintf(stderr,"  where <base filename> is used for the parameters, world, and path files.\n");
     fprintf(stderr,"        <path file> [optional] is the file with the path.\n");
   }
  return(EXIT_SUCCESS);
}

