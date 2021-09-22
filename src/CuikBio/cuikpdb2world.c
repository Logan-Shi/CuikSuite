
#include "world.h"
#include "bioworld.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>

/** \file cuikpdb2world.c

    \brief Main body of the \ref cuikpdb2world.c "cuikpdb2world" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikpdb2world  [label="cuikpdb2world"    color="#99ff99" shape=ellipse ];
      
      param     [label="param"   color="#ff9999"];
      pdb       [label="pdb"     color="#ff9999"];
      world     [label="world"   color="#ff9999"];

      param -> cuikpdb2world
      pdb -> cuikpdb2world
      cuikpdb2world -> world
    }
    \enddot
    </center>

    Main body of the \ref cuikpdb2world.c "cuikpdb2world" application. This application 
    translates molecular information (in pdb format) to a \e world file (a file 
    describing a robot) that will be later processed with the \e CuikSuite tools.
*/

/**  
   \brief Main body of the \ref cuikpdb2world.c "cuikpdb2world" application.

   Main body of the \ref cuikpdb2world.c "cuikpdb2world" application.

   Use:
       - \b cuikpdb2world \e problem_name.pdb [maxAtoms]
       .
   where
       - \e problem_name contains the molecular information.
       - \e maxAtoms [optional] Maximum number of atoms in a rigid compound to be represented in a fancy way.
         Rigids clusters larger than this limit are represented using wireframe. The advantage is that
	 wireframe is significantly faster when displaying conformations. The problems is that wireframe
	 is not used when computing collisions. If not given all atoms are represented in a fancy way
       .
   The extension (e.g., \e .pdb ) is COMPULSATORY. All the extensions managed by OpenBabel can be used.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikpdb2world command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TBioWorld bioWorld;      /* The description of the problem */
  Tparameters parameters;  /* Parameters  */

  Tfilename fparam;
  double *dof;
  unsigned int maxAtoms;
  
  if (argc>1)
    {
     
      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      if (argc>2)
	maxAtoms=atoi(arg[2]);
      else
	maxAtoms=NO_UINT;

      /* Read the problem from file */
      InitBioWorld(&parameters,arg[1],maxAtoms,&dof,&bioWorld);

      /* Print the world information (a world) */
      PrintBioWorld(&parameters,arg[1],argc,arg,&bioWorld);

      /* Release allocated objects. */
      free(dof);
      DeleteParameters(&parameters);
      DeleteBioWorld(&bioWorld);

      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikpdb2world <problem filename>.pdb [maxAtoms]\n");
     fprintf(stderr,"  where <problem filename>.pdb contains the molecular information\n");
     fprintf(stderr,"        maxAtoms [optional] Maximum number of atoms in a rigid compound to be represented in a fancy way.\n");
     fprintf(stderr,"        Rigids clusters larger than this limit are represented using wireframe. The advantage is that\n");
     fprintf(stderr,"        wireframe is significantly faster when displaying conformations. The problems is that wireframe\n");
     fprintf(stderr,"        is not used when computing collisions. If not given all atoms are represented in a fancy way\n");
     fprintf(stderr,"  The extension (e.g., '.pdb') is required\n");
     fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
   }
  return(EXIT_SUCCESS);
}

