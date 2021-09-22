
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "rrt.h"

#include <stdlib.h>

/** \file cuikrrtcosts.c

    \brief Main body of the \ref cuikrrtcosts.c "cuikrrtcosts" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikrrtcosts    [label="cuikrrtcosts"  color="#99ff99" shape=ellipse];
      
      world   [label="world" color="#ff9999" ];
      rrt     [label="rrt" color="#ff9999" ];
      param   [label="param" color="#ff9999" ];
      sols    [label="sol" color="#ff9999" ];

      world -> cuikrrtcosts;
      rrt -> cuikrrtcosts;
      param -> cuikrrtcosts;
      cuikrrtcosts -> sols;
    }
    \enddot
    </center>

    Extracts the nodes in a RRT in the form of a file of solutions.

    \sa cuikatlasrrt.c cuikcbirrt.c cuiktrrt.c cuikccrrt.c cuikcctrrt.c cuikatlasrrtstar.c cuikbiotrrt.c
*/

/** 
   \brief Main body of the \ref cuikrrtcosts.c "cuikrrtcosts" application.

   Main body of the \ref cuikrrtcosts.c "cuikrrtcosts" application.

   Use:
       - \b cuikrrtcosts \e problem_name.world [dummies]
       .
   where
       - \e problem_name is used to load .rrt file from where
         to extract the nodes.
       - [dummies] optional. If 1, output has to include de dummies.
                   This is necessary only if you plan to unsimplify the output
		   points (default is 0).
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikrrtcosts command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Trrt rrt;                /* The rrt to process. */

  Tfilename fparam;
  Tfilename frrt;
  
  if (argc>1)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      CreateFileName(NULL,arg[1],NULL,RRT_EXT,&frrt);
      fprintf(stderr,"Reading rrt from                  : %s\n",GetFileFullName(&frrt));

      LoadRRT(&parameters,&frrt,&world,&rrt);

      SaveRRTCosts(&parameters,arg[1],&rrt);
      
      DeleteParameters(&parameters);

      CS_WD_DELETE(&world);
      DeleteRRT(&rrt);

      DeleteFileName(&frrt);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikrrtcosts <problem filename>.%s\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> is the RRT with the costs to extract.\n");
     
   }
  return(EXIT_SUCCESS);
}

