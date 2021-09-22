
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/** \file cuiksimplify.c

    \brief Main body of the \ref cuiksimplify.c "cuiksimplify" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksimplify    [label="cuiksimplify"  color="#99ff99" shape=ellipse];
      
      paramIn   [label="param"   color="#ff9999" ];
      paramOut   [label="_simp.param"   color="#ff9999" ];
      kinIn   [label="cuik"    color="#ff9999" ];
      kinOut  [label="_simp.cuik"    color="#ff9999" ];

      paramIn -> cuiksimplify
      kinIn -> cuiksimplify;
      cuiksimplify -> paramOut;
      cuiksimplify -> kinOut;
    }
    \enddot
    </center>

     A utility to simplify problems. It takes a set of equations
     and try to reduce the number of variables (removing variables with constant 
     range,....).
     <br>
     The application produces an output <em>_simp.cuik</em> file with name
       with the simplified equations.
     <br>
     This utility is for minly for debug purposes since the simplification functionality  
     is fully included in <B>cuikplan</B> and <B>cuik</B>.

    \sa cuiksystem.h cuiksystem.c 
*/

/** 
   \brief Main body of the  \ref cuiksimplify.c "cuiksimplify" application.

   Main body of the \ref cuiksimplify.c "cuiksimplify" application.

   Use:
       - \b cuiksimplify \e problem_name.cuik
       .
   where
       - \e problem_name contains the kinematic equations.
       .
   The \e .cuik  extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksimplify command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TCuikSystem cuiksystem;  /* The set of equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */

  Tfilename fcuik;
  Tfilename fcuiksimp;
  Tfilename fparam;
  
  FILE *fs;
  
  if (argc>1)
    {
     
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      #if (_DEBUG>0)
        printf("Reading parameter file            : %s\n",GetFileFullName(&fparam));
      #endif
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*keep equations in the original form*/
      ChangeParameter(CT_DUMMIFY,0,&parameters);
      /*don not add dynamic equations (already added when generating the cuik file)*/
      ChangeParameter(CT_DYNAMICS,0,&parameters);

      /*Read the problem from file*/
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      #if (_DEBUG>0)
        printf("Reading cuik file                 : %s\n",GetFileFullName(&fcuik));
      #endif
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);

      /*Save the simplified system (with a header with the human readable 
	simplification)*/
      CreateFileName(NULL,arg[1],"_simp",CUIK_EXT,&fcuiksimp);
      fs=fopen(GetFileFullName(&fcuiksimp),"w");
      if (!fs)
	Error("Could not open the output file for the simplified cuiksystem.");
      #if (_DEBUG>0)
        printf("Generating simplified cuik file   : %s\n",GetFileFullName(&fcuiksimp));
      #endif
      PrintCuikSystemWithSimplification(&parameters,fs,&cuiksystem);
      fclose(fs);

      /* link the parameters */
      LinkFileNameWithExtension(arg[1],PARAM_EXT ,&fcuiksimp);

      /*Remove the allocated objects*/
      DeleteParameters(&parameters);
      DeleteCuikSystem(&cuiksystem);

      DeleteFileName(&fparam);
      DeleteFileName(&fcuik);
      DeleteFileName(&fcuiksimp);

    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuiksimplify <problem filename>.cuik \n");
     fprintf(stderr,"  where <problem filename> contains the kinematic equations\n");
     fprintf(stderr,"    (the '.cuik' extension is not required)\n");
   }
  return(EXIT_SUCCESS);
}

