
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "box_list.h"
#include "filename.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

/** \file cuikunsimplify.c

    \brief Main body of the \ref cuikunsimplify.c "cuikunsimplify" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikunsimplify    [label="cuikunsimplify"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      kin     [label="cuik"  color="#ff9999" ];
      solIn   [label="_simp.sol" color="#ff9999" ];
      solOut  [label="sol" color="#ff9999" ];

      param -> cuikunsimplify
      kin -> cuikunsimplify
      solIn -> cuikunsimplify;
      cuikunsimplify -> solOut;
    }
    \enddot
    </center>

    A utility to recover original solution boxes from the solution boxes
    of a simplified cuiksystem.
    <br>
    The simplification of a cuiksystem can be obtained with 
    \ref cuiksimplify.c "cuiksimplify" and the solution boxes for the
    simplified cuiksystem can be obtained using \ref cuik.c "cuik".
    <br>
    Up to now we use this basically for silhouettes: cuiksimplify 
    generates a system where variables are not trivially constant 
    (and thus, where silhouettes are well defined). The resulting
    silhouettes are transformed to the original system using this
    application. With the the solutions in the original form we
    can, for instance \ref cuikanimate.c "animate" the mechanism
    along the silhouette.
    <br>
    This application is developed mainly for debugging purposes
    since, in a final stage, the simplification and unsimplificatin should be included 
    and hidden in all CuikSuite application.
    <br>
    \b CAUTION<br>
    The strenght of the simplification depends on the 
    \ref CT_SIMPLIFICATION_LEVEL "SIMPLIFICATION_LEVEL" 
    parameter. Here we suppose this parameter has the same value as that
    when the simplified file was generated. Otherwise the behavior of
    the un-simplification process is undefined.

    \sa cuiksystem.h cuiksystem.c 
*/

/** 
   \brief Main body of the  \ref cuikunsimplify.c "cuikunsimplify" application.

   Main body of the \ref cuikunsimplify.c "cuikunsimplify" application.

   Use:
       - \b cuikunsimplify \e problem_name.cuik \e solution_name.sol
       .
   where
       - \e problem_name contains the un-simplified (i.e., original) 
         kinematic equations, that is, the equations from where the
	 simplified system was derived..
       - \e solution_name contains the kinematic equations for the
         simplified system.
       .
   The \e .cuik and \e .sol extensions are optional.

   The output is stores in a \e .sol file with the same name as the
   cuik file.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksimplify command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TCuikSystem cuiksystem;  /* The set of equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */

  Tlist solutions;  /* The list with the simplified solutions. */ 
  Titerator it;     /* Iterator on the solution list */
  Tbox boxO;        /* Space where to recompose the un-simplified box. */ 

  Tfilename fcuik;
  Tfilename fsol;
  Tfilename fsolsimp;
  Tfilename fparam;

  boolean *systemVars;
  
  FILE *fs;
  
  if (argc>2)
    {
      /*Init parameters*/          
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file: %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the problem from file*/      
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      fprintf(stderr,"Reading equation file : %s\n",GetFileFullName(&fcuik));
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);
      GetCSSystemVars(&systemVars,&cuiksystem);

      /*Read the simplified boxes*/
      CreateFileName(NULL,arg[2],NULL,SOL_WITH_DUMMIES_EXT,&fsolsimp);
      fprintf(stderr,"Reading boxes file    : %s\n",GetFileFullName(&fsolsimp));
      if (!ReadListOfBoxes(GetFileFullName(&fsolsimp),&(solutions)))
	Error("Solution file can not be opened");
	
      
      /*Save the un-simplified boxes*/
      CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsol);
      fprintf(stderr,"Writting boxes file   : %s\n",GetFileFullName(&fsol));
      fs=fopen(GetFileFullName(&fsol),"w");
      if (!fs)
	Error("Could not open the output file for the un-simplified boxes.");
      


      InitIterator(&it,&solutions);
      First(&it);
      while(!EndOfList(&it))
	{
	  RegenerateOriginalBox(&parameters,(Tbox *)GetCurrent(&it),&boxO,&cuiksystem);
	  PrintBoxSubset(fs,systemVars,NULL,&boxO);
	  DeleteBox(&boxO);
	  Advance(&it);
	}
      fclose(fs);
      
      /*Remove the allocated objects*/
      DeleteListOfBoxes(&solutions);
      DeleteParameters(&parameters);
      DeleteCuikSystem(&cuiksystem);

      DeleteFileName(&fparam);
      DeleteFileName(&fcuik);
      DeleteFileName(&fsol);
      DeleteFileName(&fsolsimp);
      free(systemVars);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikunsimplify <problem filename>.cuik  <solution filename>.sol\n");
     fprintf(stderr,"  where <problem filename> contains the original kinematic equations\n");
     fprintf(stderr,"        <solution filename> contains the solutions for the simplified system\n");
     fprintf(stderr,"    (the '.cuik' and '.sol' extensions are not required)\n");
   }
  return(EXIT_SUCCESS);
}

