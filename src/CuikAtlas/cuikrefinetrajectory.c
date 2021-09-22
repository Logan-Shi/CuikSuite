
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlasrrt.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikrefinetrajectory.c

    \brief Main body of the \ref cuikrefinetrajectory.c "cuikrefinetrajectory" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikrefinetrajectory    [label="cuikrefinetrajectory"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      traj    [label="traj"    color="#ff9999" ];
      rtraj   [label="r_traj"    color="#ff9999" ];

      param -> cuikrefinetrajectory;
      world -> cuikrefinetrajectory;
      traj -> cuikrefinetrajectory;
      cuikrefinetrajectory -> rtraj;
    }
    \enddot
    </center>

    Refines a trajectory obtained with \ref cuikatlasrrt.c "cuikatlasrrt".
    
    Trajetories obtained with long integration times include states separated by
    long periods of time. This function adds intermediate states so that the
    simulations are smoother.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikrefinetrajectory.c "cuikrefinetrajectory" application.

   Main body of the \ref cuikrefinetrajectory.c "cuikrefinetrajectory" application.

   Use:
       - \b cuikrefinetrajectory \e problem_name [\e traj_name]
       .
   where
       - \e problem_name Name of the file describing the problem.
       - \e traj_name [optional] Name of the trajectory to refine.
       .
   The \e problem_name is without any extension.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikrefinetrajectory command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/

#include "basic_algebra.h"

int main(int argc, char **arg)
{
  Tworld w;                /* The world */
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tatlasrrt atlasRRT;      /* The atlasRRT structure. */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  Tfilename ftraj;

  /* input path */
  unsigned int nvs,ns,da;
  double **path;
  double *times;
  double **actions;
  
  if (argc>1)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      
      /*Read the world from file*/ 
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&w);
      CS_WD_FROM_WORLD(&w,&world);
      LoadAtlasRRT(&parameters,arg[1],&world,&atlasRRT);
      
      if (argc==2)
	CreateFileName(NULL,arg[1],"_traj",SOL_EXT,&ftraj);
      else
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&ftraj);
	
      if (LoadTrajectory(&ftraj,&nvs,&ns,&path,&da,&actions,&times))
	{
	  RefineTrajectory(&parameters,FALSE,&ns,&path,&actions,&times,&atlasRRT);

	  if (argc==2)
	    SaveTrajectory(arg[1],"_traj_r",nvs,ns,path,da,actions,times);
	  else
	    SaveTrajectory(arg[2],"_traj_r",nvs,ns,path,da,actions,times);

	  DeleteTrajectory(ns,path,actions,times);
	}
      else
	Error("Could not read the input trajectory file");

      DeleteAtlasRRT(&atlasRRT);
      DeleteWorld(&w);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&ftraj);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikrefinetrajectory <problem name> [<traj name>]\n");
     fprintf(stderr,"  where <problem name> is the file describing the problem.\n");
     fprintf(stderr,"        <path name> is the file with the trajectory to refine.\n");
     fprintf(stderr,"\n");
     fprintf(stderr," When called as:\n");
     fprintf(stderr,"      cuikrefinetrajectory <problem name>\n");
     fprintf(stderr," The default parameters and the default trajectory name are assumed.\n");
     
   }
  return(EXIT_SUCCESS);
}

