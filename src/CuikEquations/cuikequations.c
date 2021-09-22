#include "parameters.h"
#include "defines.h"
#include "world.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>
#include <string.h>

/** \file cuikequations.c

    \brief Main body of the \ref cuikequations.c "cuikequations" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikequations    [label="cuikequations"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      kin     [label="_kin.cuik"    color="#ff9999" ];
      kinparam   [label="_kin.param"   color="#ff9999" ];

      param -> cuikequations
      world -> cuikequations
      cuikequations -> kin;
      cuikequations -> kinparam;
    }
    \enddot
    </center>

    Takes as input a <em>world</em> description and generates a 
    <em>_kin.cuik</em> file with the equations derived from the kinematic constraints.

    \sa world.c

*/

/** 
   \brief Main body of the \ref cuikequations.c "cuikequations" application.

   Main body of the \ref cuikequations.c "cuikequations" application.

   Use:<br>
       - \b cuikequations \e problem_name.world \e obs
       .
   where 
     - \e problem_name is the world file from which to generate the equations.
     - \e obs [optional, default to 0] is 1 if the obstacle related equations
       must be generated.
     .
     

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikequations command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;     /* Parameters */
  Tworld world;               /* Environemtn and mechanisms */

  Tfilename fparam;
  
  if (argc>1)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      #if (_DEBUG>0)
        printf("Reading parameter file            : %s\n",GetFileFullName(&fparam));
      #endif
	InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Init world*/
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      PrintWorldCS(&parameters,arg[1],&world);
     
      /* Delete the data structures */
      DeleteWorld(&world);
      DeleteParameters(&parameters);

      /* Delete the file names */
      DeleteFileName(&fparam);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuikequations <Sing> <problem name>\n");
      fprintf(stderr,"  where \n");
      fprintf(stderr,"       <problem name> is the world file from which to generate the equations\n");
    }

  return(EXIT_SUCCESS);
}

