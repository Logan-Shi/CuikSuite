
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"

#include <stdlib.h>

/** \file cuikatlas2graph.c

    \brief Main body of the \ref cuikatlas2graph.c "cuikatlas2graph" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlas2graph    [label="cuikatlas2graph"  color="#99ff99" shape=ellipse];
      
      world   [label="world" color="#ff9999" ];
      atlas   [label="atlas" color="#ff9999" ];
      param   [label="param" color="#ff9999" ];
      graph   [label="graph" color="#ff9999" ];

      world -> cuikatlas2graph;
      atlas -> cuikatlas2graph;
      param -> cuikatlas2graph;
      cuikatlas2graph -> sol;
    }
    \enddot
    </center>

    Extracts the neighboring relations between the charts in the atlas.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikatlas2graph.c "cuikatlas2graph" application.

   Main body of the \ref cuikatlas2graph.c "cuikatlas2graph" application.

   Use:
       - \b cuikatlas2graph \e problem_name.world 
       .
   where
       - \e problem_name is used to load .atlas file from where
         to extract the graph information.
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlas2graph command itself and its arguments). 
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

      SaveAtlasGraph(arg[1],&atlas);
      
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
     fprintf(stderr,"      cuikatlas2graph <problem filename>.%s\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> is the atlas with the graph.\n");
     
   }
  return(EXIT_SUCCESS);
}

