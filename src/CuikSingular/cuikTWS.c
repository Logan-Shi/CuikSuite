#include "parameters.h"
#include "defines.h"
#include "world.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** \file cuikTWS.c

    \brief Main body of the \ref cuikTWS.c "cuikTWS" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikTWS    [label="cuikTWS"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      kin     [label="_TWS.cuik"    color="#ff9999" ];

      param -> cuikTWS
      world -> cuikTWS;
      cuikTWS -> kin;
    }
    \enddot
    </center>

    Takes as input a <em>world</em> description and a link identifier and generates a 
    <em>cuik</em> file with the kinematic equations and with the variables 
    to detect the  translational limits of the workspace.

    This is a particular composition of \ref cuiksingequations.c "cuiksingequations"
    and \ref cuikaddjacobian.c "cuikaddjacobian" for a particular set of
    singularities.

    The resulting cuiksystem is not directly solved, but written to a file so that
    the user can select to execute it on single or multiple processors.

    See \ref examples/WSSingularities for examples of how to use
    this application.

    <b>IMPORTANT:</b> The automatic generation of equations to detect singularities is still
    in development. The tools currently included in the CuikSuite (including
    this one) can only deal with simple cases (e.g. planar robots with 3 degrees
    of freedom). Thus, right now it is advisable to
    manually generate these equations following the instructions given in the
    work by <a href="http://www.iri.upc.edu/people/obohigas/">O. Bohigas</a>, 
    <a href="http://www.iri.upc.edu/people/mmanuben/Welcome.html">M. Manubens</a>, 
    and <a href="http://www.iri.upc.edu/people/ros/">L. Ros</a>.

    \sa world.c
*/

/** 
   \brief Main body of the \ref cuikTWS.c "cuikTWS" application.

   Main body of the \ref cuikTWS.c "cuikTWS" application.

   Use:<br>
       - \b cuikTWS \e problem_name.world \e link_name
       .
   where 
     - \e problem_name is the world file from which to generate the equations.
     - \e link_name link on which to focus. None for no particular link.
     .
     
   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksingequations command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;     /* Parameters */
  Tworld world;               /* Environemtn and mechanisms */
  TCuikSystem cs;             /* The cuiksystem to generate*/

  Tfilename fparam;
  Tfilename fcuik;
  
  FILE *f;

  if (argc>2)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      #if (_DEBUG>0)
        printf("Reading parameter file            : %s\n",GetFileFullName(&fparam));
      #endif
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*keep equations in the original form*/
      ChangeParameter(CT_DUMMIFY,0,&parameters);
      
      /*Read the world file*/
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      /*Add TWS equations*/
      GenerateWorldTWSEquations(&parameters,arg[2],&cs,&world);
      
      /*Print resulting extended cuiksystem*/
      CreateFileName(NULL,arg[1],"_TWS",CUIK_EXT,&fcuik);

      f=fopen(GetFileFullName(&fcuik),"w");
      if (!f)
	 Error("Could not open output file in cuiksingequations");     
      #if (_DEBUG>0)
        printf("Generating the _TWS.cuik file     : %s\n",GetFileFullName(&fcuik));
      #endif
      PrintCuikSystemWithSimplification(&parameters,f,&cs);
      fclose(f);

      /* link the parameter/joints/links files */
      LinkFileNameWithExtension(arg[1],PARAM_EXT ,&fcuik);
      LinkFileNameWithExtension(arg[1],JOINTS_EXT,&fcuik);
      LinkFileNameWithExtension(arg[1],LINKS_EXT ,&fcuik);

      /* Delete the data structures */
      DeleteCuikSystem(&cs);
      DeleteParameters(&parameters);

      /* Delete the file names */
      DeleteFileName(&fparam);
      DeleteFileName(&fcuik);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuikTWS <Sing> <problem name>\n");
      fprintf(stderr,"  where \n");
      fprintf(stderr,"       <problem name> is the world file from which to generate the equations\n");
      fprintf(stderr,"       <Sing> It must be the name of the link to focus\n");
    }

  return(EXIT_SUCCESS);
}

