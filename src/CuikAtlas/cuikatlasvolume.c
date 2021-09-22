
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikatlasvolume.c

    \brief Main body of the \ref cuikatlasvolume.c "cuikatlasvolume" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlasvolume    [label="cuikatlasvolume"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];

      param -> cuikatlasvolume;
      world -> cuikatlasvolume;
      atlas -> cuikatlasvolume;
    }
    \enddot
    </center>

    Measures the volume of an atlas generated with cuikatlas.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikatlasvolume.c "cuikatlasvolume" application.

   Main body of the \ref cuikatlasvolume.c "cuikatlasvolume" application.

   Use:
       - \b cuikatlasvolume \e problem_name \e collisionFree
       .
   where
       - \e problem_name is used to load the .world and .atlas files necessary
         to generate compute the volume.
       - \e collisionFree [Optional] 1 if only the volume of C-free is required.
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlasvolume command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Tatlas atlas;            /* The atlas to measure. */

  boolean collisionFree;
  double v;

  Tfilename fparam;
  Tfilename fatlas;
  
  
  if ((argc==2)||(argc==3))
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from  : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/ 
      CS_WD_INIT(&parameters,arg[1],&world);

      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Reading atlas from       : %s\n",GetFileFullName(&fatlas));
      LoadAtlas(&parameters,&fatlas,&world,&atlas);
      
      if (argc==2)
	collisionFree=FALSE;
      else
	collisionFree=atoi(arg[2]);

      v=AtlasVolume(&parameters,collisionFree,&atlas); 
      
      if (collisionFree)
	fprintf(stderr,"Volume of C-free         : %g\n",v);
      else
	fprintf(stderr,"Volume of C              : %g\n",v);

      DeleteParameters(&parameters);

      CS_WD_DELETE(&world);

      DeleteAtlas(&atlas);

      DeleteFileName(&fatlas);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikatlasvolume <problem filename> <collisionFree>\n");
     fprintf(stderr,"  where <problem filename> is the atlas.\n");
     fprintf(stderr,"        <collisionFree> [optional] 1 if only the volume of the .\n");
     fprintf(stderr,"                collisionFree part of the atlas is necessary.\n");
     
   }
  return(EXIT_SUCCESS);
}

