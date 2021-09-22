
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/** \file cuikmerge.c

    \brief Main body of the \ref cuikmerge.c "cuikmerge" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikmerge    [label="cuikmerge"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      kinIn1   [label="1.cuik"    color="#ff9999" ];
      kinIn2   [label="2.cuik"    color="#ff9999" ];
      kinOut  [label="_suffix.cuik"    color="#ff9999" ];

      param -> cuikmerge
      kinIn2 -> cuikmerge;
      kinIn1 -> cuikmerge;
      cuikmerge -> kinOut;
    }
    \enddot
    </center>

     A utility to define one cuiksystem from serveral files.

    \sa cuiksystem.h cuiksystem.c 
*/

/** 
   \brief Main body of the  \ref cuikmerge.c "cuikmerge" application.

   Main body of the \ref cuikmerge.c "cuikmerge" application.

   Use:
       - \b cuikmerge \e suffix \e problems.cuik 
       .
   where
       - \e suffix Is the suffix added to the output cuiksystem.
       - \e problems Are the cuik files with the variables/equations to merge.
       .
   The \e .cuik  extensions are optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksimplify command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TCuikSystem cuiksystem;  /* The set of equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */

  Tfilename fcuikIn;
  Tfilename fcuikAdded;
  Tfilename fcuikOut;
  Tfilename fparam;
  
  int i;
  FILE *fs;
  
  if (argc>2)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[2],NULL,PARAM_EXT,&fparam);
      #if (_DEBUG>0)
        printf("Reading parameter file            : %s\n",GetFileFullName(&fparam));
      #endif
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /* keep equations in the original form */
      ChangeParameter(CT_DUMMIFY,0,&parameters);
      
      /* avoid the generation of velocity equations (if not present in the input file) */
      ChangeParameter(CT_DYNAMICS,0,&parameters);

      /*Read the problem from file*/
      CreateFileName(NULL,arg[2],NULL,CUIK_EXT,&fcuikIn);
      #if (_DEBUG>0)
        printf("Reading cuik file                 : %s\n",GetFileFullName(&fcuikIn));
      #endif
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuikIn),&cuiksystem);
      
      for(i=3;i<argc;i++)
	{
	  /*Read the problem from file*/
	  CreateFileName(NULL,arg[i],NULL,CUIK_EXT,&fcuikAdded);
	  #if (_DEBUG>0)
	    printf("Reading cuik file                 : %s\n",GetFileFullName(&fcuikAdded));
	  #endif
	  AddCuikSystemFromFile(&parameters,FALSE,NULL,GetFileFullName(&fcuikAdded),&cuiksystem);

	  DeleteFileName(&fcuikAdded);
	}

      /*Save the final cuiksystem */
      CreateFileName(NULL,arg[2],arg[1],CUIK_EXT,&fcuikOut);
      fs=fopen(GetFileFullName(&fcuikOut),"w");
      if (!fs)
	Error("Could not open the output file for the merged cuiksystem.");
      #if (_DEBUG>0)
        printf("Generating merged cuik file       : %s\n",GetFileFullName(&fcuikOut));
      #endif
      PrintCuikSystem(&parameters,fs,&cuiksystem);
      fclose(fs);

      /* link the parameter files (after the merge joints/links are no longer valid,
	 use cuikmerge boxes to address this issue) */
      LinkFileNameWithExtension(arg[2],PARAM_EXT ,&fcuikOut);

      /*Remove the allocated objects*/
      DeleteParameters(&parameters);
      DeleteCuikSystem(&cuiksystem);

      DeleteFileName(&fparam);
      DeleteFileName(&fcuikIn);
      DeleteFileName(&fcuikOut);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikmerge <suffx> <problem filenames>.cuik \n");
     fprintf(stderr,"  where <problem filenames> contains the kinematic equations to merge\n");
     fprintf(stderr,"    (the '.cuik' extension is not required)\n");
   }
  return(EXIT_SUCCESS);
}

