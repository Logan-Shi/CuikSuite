
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "dynamics.h"
#include "random.h"
#include "samples.h"
#include "wcs.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/** \file cuiksimulateRK4.c

    \brief Main body of the \ref cuiksimulateRK4.c "cuiksimulateRK4" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksimulateRK4    [label="cuiksimulateRK4"  color="#99ff99" shape=ellipse];

      param      [label="param"   color="#ff9999" ];
      samples    [label="joints/links" color="#ff9999" ];
      world      [label="cuik/world"   color="#ff9999" ];
      atlas      [label="atlas"   color="#ff9999" ];
      trajectory [label="traj"    color="#ff9999" ];

      param -> cuiksimulateRK4
      world -> cuiksimulateRK4
      samples -> cuiksimulateRK4
      cuiksimulateRK4 -> atlas;
      cuiksimulateRK4 -> trajectory;
    }
    \enddot
    </center>

    Simulates the dynamical effects of a given action from a given point.

*/

/** 
   \brief Main body of the \ref cuiksimulateRK4.c "cuiksimulateRK4" application.

   Main body of the \ref cuiksimulateRK4.c "cuiksimulateRK4" application.

   Simulates the dynamical effects of an action on a given state.

   Use:
       - \b cuiksimulateRK4 \e problem_name.cuik/world \e steps \e action
       .
   where
       - \e problem_name contains the problem definition. The extension is not necessary. We first
         check if a file with .cuik extension exists. Othersiwe, we try to read a .world file.
	 The name is also used to read the sample file
         including the origin configuration.
       - \e steps How many steps of INTEGRATION_TIME (parameter) have to be executed.
       - \e action The action to apply. This takes the form of a vector with a component for
                   each independently actuated element in the system.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksimulateRK4 command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{

  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  TDynamicSpace dynamicSpace;
  Tfilename fparam;
  TJacobian sJ;

  unsigned int nvs,i;
  double *s1;         /* Origin of the simulation. */

  unsigned int ns;
  double **path;
  double *times;
  unsigned int da;
  double **actions;
  unsigned int dof,p;

  double *action;
  unsigned int steps;

  unsigned int ri; /* random seed. */
  time_t t;        /* Used to measure integration speed. */

  unsigned int db;

  if (argc>3)
    {
      steps=atoi(arg[2]);
      if (steps<1)
	Error("At least one integration step must be executed");

      da=argc-3;
      NEW(action,da,double);
      for(i=0;i<da;i++)
	action[i]=atof(arg[3+i]);

      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,&parameters);
      if (db>0)
	Error("cuiksimulateRK4 does not deal with bifurcations (yet)");

      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read starting point */
      nvs=ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1);

      /* Random seed initialization */
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1424256627;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      dof = (unsigned int) GetParameter(CT_N_DOF,&parameters);
      if(dof/2!=da)
        Error("wrong number of actions");

      p=(unsigned int) GetParameter(CT_DYNAMIC_PROBLEM,&parameters);

      CS_WD_GET_SIMP_JACOBIAN(&parameters,&sJ,&world);

      /* Initialize the dynamic space */
      InitDynamicSpace(dof,p,&sJ,&world,&dynamicSpace);

      /* Define the path using the atlas */
      Simulate(&parameters,NextDynamicStateRK4,da,action,s1,steps,&ns,&path,&actions,&times,&dynamicSpace);

      fprintf(stderr,"  Simulation concluded in %u sec\n",(unsigned int)(time(NULL)-t));

      /* Save the generated structures */
      SaveTrajectory(arg[1],FALSE,nvs,ns,path,da,actions,times);

      /* Release memory */
      DeleteTrajectory(ns,path,actions,times);
      DeleteDynamicSpace(&dynamicSpace);
      DeleteJacobian(&sJ);
      free(s1);
      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);
      DeleteFileName(&fparam);
      free(action);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");
     fprintf(stderr,"      cuiksimulateRK4 <problem filename>.%s <steps> <action>\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <steps> how many steps of INTEGRATION_TIME (parameter) have to be executed.\n");
     fprintf(stderr,"        <action> the action to apply. A vector with an element for each\n");
     fprintf(stderr,"                 independently actuated element in the system\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}
