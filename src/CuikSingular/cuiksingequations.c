#include "parameters.h"
#include "defines.h"
#include "world.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** \file cuiksingequations.c

    \brief Main body of the \ref cuiksingequations.c "cuiksingequations" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksingequations    [label="cuiksingequations"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      kin    [label="_sing.cuik"    color="#ff9999" ];
      kinparam   [label="_sing.param"   color="#ff9999" ];

      param -> cuiksingequations
      world -> cuiksingequations;
      cuiksingequations -> kin;
      cuiksingequations -> kinparam;
    }
    \enddot
    </center>

    Takes as input a <em>world</em> description and generates a 
    <em>cuik</em> file with the kinematic equations and with the variables for
    joint limits properly re-written to produce singularities when their limit
    is reached. Moreover, if we are interested in the translation of a particular link
    equations giving its position in the global frame are added.

    Note that \ref cuiksingequations.c "cuiksingequations" is only part of the 
    process to generate systems charaterizing singularities. This generates a
    \e cuik file where to look for the variables of interest. Then we have
    to extend this \e cuik file with the linear combination of the Jacobian
    for the non-interesting variables.
    <br>
    The process can not be done in one step because, inintially the user
    can not guess the name for the variables in the cuiksystem.

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
   \brief Main body of the \ref cuiksingequations.c "cuiksingequations" application.

   Main body of the \ref cuiksingequations.c "cuiksingequations" application.

   Use:<br>
       - \b cuiksingequations \e link_name \e problem_name.world
       .
   where 
     - \e link_name [Optional] link on which to focus. None for no particular link.
     - \e problem_name is the world file from which to generate the equations.
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
  
  char *ln;                    /* link name */
  char *pn;                    /* problem name */
  FILE *f;

  if (argc>1)
    {
      if (argc>2)
	{
	  ln=arg[1];
	  pn=arg[2];
	}
      else
	{
	  ln=NULL;
	  pn=arg[1];
	}

      /*Init parameters*/
      CreateFileName(NULL,pn,NULL,PARAM_EXT,&fparam);
      #if (_DEBUG>0)
        printf("Reading parameter file       : %s\n",GetFileFullName(&fparam));
      #endif
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the world file*/
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      /*Add singularity equations*/
      GenerateWorldSingularityEquations(&parameters,ln,&cs,&world);
      
      /*Print resulting extended cuiksystem*/
      CreateFileName(NULL,pn,"_sing",CUIK_EXT,&fcuik);

      f=fopen(GetFileFullName(&fcuik),"w");
      if (!f)
	 Error("Could not open output file in cuiksingequations");     
      #if (_DEBUG>0)
        printf("Generating the _sin.cuik file: %s\n",GetFileFullName(&fcuik));
      #endif
      PrintCuikSystem(&parameters,f,&cs);
      fclose(f);

      /* link the parameter/joints/links files */
      LinkFileNameWithExtension(arg[1],PARAM_EXT ,&fcuik);
      LinkFileNameWithExtension(arg[1],JOINTS_EXT,&fcuik);
      LinkFileNameWithExtension(arg[1],LINKS_EXT ,&fcuik);

      /* Delete the data structures */
      DeleteCuikSystem(&cs);
      DeleteWorld(&world);
      DeleteParameters(&parameters);

      /* Delete the file names */
      DeleteFileName(&fparam);
      DeleteFileName(&fcuik);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuiksingequations <Sing> <problem name>\n");
      fprintf(stderr,"  where \n");
      fprintf(stderr,"       <Sing> [Optional] It must be the name of the link to focus\n");
      fprintf(stderr,"              None for no particular link\n");
      fprintf(stderr,"       <problem name> is the world file from which to generate the equations\n");
    }

  return(EXIT_SUCCESS);
}

