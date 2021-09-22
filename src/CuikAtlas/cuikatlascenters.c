
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"

#include <stdlib.h>

/** \file cuikatlascenters.c

    \brief Main body of the \ref cuikatlascenters.c "cuikatlascenters" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlascenters    [label="cuikatlascenters"  color="#99ff99" shape=ellipse];
      
      world   [label="world" color="#ff9999" ];
      atlas   [label="atlas" color="#ff9999" ];
      param   [label="param" color="#ff9999" ];
      sol    [label="sol" color="#ff9999" ];

      world -> cuikatlascenters;
      atlas -> cuikatlascenters;
      param -> cuikatlascenters;
      cuikatlascenters -> sol;
    }
    \enddot
    </center>

    Extracts the centers of the atlas and stores them in a file in the form of
    boxes (sols).

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikatlascenters.c "cuikatlascenters" application.

   Main body of the \ref cuikatlascenters.c "cuikatlascenters" application.

   Use:
       - \b cuikatlascenters \e problem_name.world [dummies] [inside] [middle] 
       .
   where
       - \e problem_name is used to load .atlas file from where
         to extract the centres.
       - [dummies] optional. If 1, output has to include de dummies.
                   This is necessary only if you plan to unsimplify the output
		   points (default is 0).
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlascenters command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Tatlas atlas;            /* The atlas to process. */

  Tfilename fparam;
  Tfilename fatlas;

  boolean withDummies;
  
  if (argc>1)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Reading atlas from                : %s\n",GetFileFullName(&fatlas));
      LoadAtlas(&parameters,&fatlas,&world,&atlas);
    
      if (argc>2)
	withDummies=atoi(arg[2]);
      else
	withDummies=FALSE;

      SaveChartCenters(&parameters,arg[1],withDummies,&atlas);
      
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
     fprintf(stderr,"      cuikatlascenters <problem filename>.%s [dummies] [insied] [middle]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> is the atlas with the center to extract.\n");
     fprintf(stderr,"        [dummies] is 1 if you want the dummy variables in the output.\n");
     fprintf(stderr,"                  This is only necessary if you plan to unsimplify the\n");
     fprintf(stderr,"                  output points (default 0).\n");
   }
  return(EXIT_SUCCESS);
}

