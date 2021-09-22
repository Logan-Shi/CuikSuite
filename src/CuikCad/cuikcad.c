
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>

/** \file cuikcad.c

    \brief Main body of the \ref cuikcad.c "cuikcad" application.

    Main body of the \ref cuikcad.c "cuikcad" application. This application is supposed to
    translate geometric information (points, lines, parallelism and coincidence relations, etc.) 
    to a \e cuik file (a file with equations) that will be later processed with the \e cuik tools.

    \todo Implement cuikcad.c. 

    \sa cuiksystem.h cuiksystem.c 
*/

/** 
   \brief Main body of the \ref cuikcad.c "cuikcad" application.

   Main body of the \ref cuikcad.c "cuikcad" application.

   Use:
       - \b cuikcad \e problem_name.cad
       .
   where
       - \e problem_name contains the CAD information.
       .
   The \e .cad extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikcad command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TCuikSystem cuiksystem;  /* The set of equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */

  Tfilename fcad;
  Tfilename fparam;
  
  
  if (argc>1)
    {
     
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the problem from file*/
      CreateFileName(NULL,arg[1],NULL,CAD_EXT,&fcad);
      
      InitCuikSystem(&cuiksystem);

      Error("Not implemented yet. Sorry....\n");
      
      DeleteParameters(&parameters);
      DeleteCuikSystem(&cuiksystem);

      DeleteFileName(&fparam);
      DeleteFileName(&fcad);

    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikcad <problem filename>.cad \n");
     fprintf(stderr,"  where <problem filename> contains the CAD information\n");
     fprintf(stderr,"    (the '.cad' extension is not required)\n");
   }
  return(EXIT_SUCCESS);
}

