#include "world.h"
#include "error.h"


/** \file cuikworld2world.c

    \brief Main body of the \ref cuikworld2world.c "cuikworld2world" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikworld2world    [label="cuikworld2world"  color="#99ff99" shape=ellipse];
      
      param    [label="param"   color="#ff9999" ];
      worldIn  [label="world"   color="#ff9999" ];
      worldOut [label="world"   color="#ff9999" ];

      param -> cuikworld2world;
      worldIn -> cuikworld2world;
      cuikworld2world -> worldOut;
    }
    \enddot
    </center>

    This application flattens a world definition: reads a world file possibly including
    many other world files and generates a single world file with all the information.
    Moreover, it unifies the collision information that can be split in the different
    included files.

    This is basically used for debug and also to compact the world definitions.
*/

/** 
   \brief Main body of the \ref cuikworld2world.c "cuikworld2world"  application.

   Main body of the \ref cuikworld2world.c "cuikworld2world" application.

   Use: <br>
     - \b cuikworld2world \e world_in.world \e world_out.world
     .
   Where: 
     - \e world_in:  File describing the problem.
     - \e world_out: The output world file.
     .

   File extensions are optional. 

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  
  if (argc>2)
    {
      Tworld world;
      Tparameters parameters;

      Tfilename fparam;
      Tfilename fworldOut;
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      InitWorldFromFile(&parameters,TRUE,TRUE,arg[1],&world);

      CreateFileName(NULL,arg[2],NULL,WORLD_EXT,&fworldOut);
      PrintWorld(GetFileFullName(&fworldOut),argc,arg,&world);

      DeleteFileName(&fworldOut);  
      DeleteFileName(&fparam);

      DeleteParameters(&parameters);

      return(EXIT_SUCCESS);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikworld2world <world_in>.world <world_out>.world\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world_in> :  File describing the problem\n");
      fprintf(stdout,"     <world_out>:  File to generate.\n");
      fprintf(stdout,"  File extensions are not required\n");

      return(EXIT_FAILURE);
    }
}
