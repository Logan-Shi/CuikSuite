#include "world.h"
#include "box_list.h"
#include "error.h"

/** \file cuikanimate.c

    \brief Main body of the \ref cuikanimate.c "cuikanimate" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikanimate    [label="cuikanimate"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"    color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuikanimate;
      world -> cuikanimate;
      sol -> cuikanimate;
      cuikanimate -> gcl;
    }
    \enddot
    </center>

    Animates sets of boxes. For the animation we need a description
    of the world to animate (mechanism+environment) and a set of solution boxes defining a
    movement for the mechanisms (stored in a <em>.sol</em> file).
    This set of solution boxes can be, for instance, the paths between samples obtained 
    from <b>cuikplan</b> or a set of boxes for a mechanisms with a one-dimensional 
    solution set obtained via <b>cuik</b> and sorted using <b>cuiksort</b>

    \sa cuik.c cuikplan.c cuiksort.c
*/

/** 
   \brief Main body of the \ref cuikanimate.c "cuikanimate"  application.

   Main body of the \ref cuikanimate.c "cuikanimate" application.

   Use: <br>
     - \b cuikanimate \e world_name.world \e solutions_name.sol \e axes_length \e frame_delay \e animation_name.cgl 
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e solutions_name:  Is the path of solutions to be animated.
     - \e axes_length: Is the length for the axes for each link. 0 not to display them.
     - \e frame_delay: Extra delay added in between frames. It is useful when "animating"
                       a set of isolated solutions to make each solution to be shown
                       enough time to be inspected.
     - \e animation_name:  Is the output file (can be browsed with 'geomview'). 
     .
   File extensions are optional. 

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  if (argc>5)
    {
      Tworld world;
      Tparameters parameters;
      Tfilename fsols;
      Tfilename fparam;
      Tfilename fcgl;
      Tlist sol_box_list;
      double axesLength;
      double frameDelay;
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      InitWorldFromFile(&parameters,TRUE,TRUE,arg[1],&world);

      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      if (!ReadListOfBoxes(GetFileFullName(&fsols),&sol_box_list))
	Error("Solution file can not be opened");
      
      if (ListSize(&sol_box_list)==0)
	Error("Empty list of solutions");

      axesLength=atof(arg[3]);

      frameDelay=atof(arg[4]);

      CreateFileName(NULL,arg[5],NULL,PLOT3D_EXT,&fcgl);

      AnimateWorld(&parameters,GetFileFullName(&fcgl),axesLength,
		   frameDelay,&sol_box_list,&world);

      DeleteListOfBoxes(&sol_box_list);

      DeleteWorld(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fsols);      
      DeleteFileName(&fcgl);      
      DeleteFileName(&fparam);
    }
  else
    {
     
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikanimate <world>.world <solutions>.sol <axes> <delay> <animation>.cgl\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <solutions>:  Is the path of solutions to be animated\n");
      fprintf(stdout,"     <axes>: Length for the axes for each link. 0 not to display them.\n");
      fprintf(stdout,"     <delay>: Delay (in seconds) between frames.\n");
      fprintf(stdout,"              To be added to the default delay (0.1 seconds).\n");
      fprintf(stdout,"     <animation>:  Is the output file (can be seen with 'geomview')\n");
      fprintf(stdout,"  File extensions are not required\n");
    }

  return(EXIT_SUCCESS);
}
