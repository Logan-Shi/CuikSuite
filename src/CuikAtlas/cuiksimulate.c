
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlasrrt.h"
#include "dynamics.h"
#include "random.h"
#include "samples.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/** \file cuiksimulate.c

    \brief Main body of the \ref cuiksimulate.c "cuiksimulate" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksimulate    [label="cuiksimulate"  color="#99ff99" shape=ellipse];
      
      param      [label="param"   color="#ff9999" ];
      samples    [label="joints/links" color="#ff9999" ];
      world      [label="cuik/world"   color="#ff9999" ];
      atlas      [label="atlas"   color="#ff9999" ];
      trajectory [label="traj"    color="#ff9999" ];

      param -> cuiksimulate
      world -> cuiksimulate
      samples -> cuiksimulate
      cuiksimulate -> atlas;
      cuiksimulate -> trajectory;
    }
    \enddot
    </center>

    Simulates the dynamical effects of a given action from a given point.

*/

/** 
   \brief Main body of the \ref cuiksimulate.c "cuiksimulate" application.

   Main body of the \ref cuiksimulate.c "cuiksimulate" application.
   
   Simulates the dynamical effects of an action on a given state.
   The particular integration method used in the simulation (local parameterizatinos, Euler, RK4)
   is selected according to parameter \ref CT_DYNAMICS "DYNAMICS".

   Use:
       - \b cuiksimulate \e problem_name.cuik/world \e steps \e action
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
               \b cuiksimulate command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{

  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;

  unsigned int nvs,i;
  double *s1;         /* Origin of the simulation. */
  double *s2;         /* Goal of the simulation (only used in LQR mode) */

  Tatlasrrt atlasrrt;
  TDynamicSpace dynamicSpace;
  
  unsigned int ns=0;
  double **path=NULL;
  double *times=NULL;
  unsigned int da,nda;
  double **actions=NULL;
  
  double *action;
  unsigned int steps;

  unsigned int ri; /* random seed. */
  time_t t;        /* Used to measure integration speed. */

  unsigned int dynamics,db; //,dof;
  TJacobian sJ;
  
  /*Init parameters*/

  if (argc>2)
    {
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));	    
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      dynamics=(unsigned int)GetParameter(CT_DYNAMICS,&parameters);
      if (dynamics==0)
	Error("cuiksimulate only works on problems with dynamics");
  
      nda=(unsigned int)GetParameter(CT_N_DYNAMIC_ACTIONS,&parameters);
    }
  else
    nda=0;
  
  if (((nda==0)&&(argc==3))||((nda>0)&&(argc>3)))
    {      
      steps=atoi(arg[2]);
      if (steps<1)
	Error("At least one integration step must be executed");

      //dof=(unsigned int)GetParameter(CT_N_DOF,&parameters);
      
      db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,&parameters);
      if (db>0)
	Error("cuiksimulate does not deal with bifurcations (yet)");
      
      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);
      if (ON_CUIKSYSTEM(&world))
	Error("cuiksimulate can only operate on world files (not on cuik files)");

      da=GetWorldActionDimension(GET_WORLD(&world)); //argc-3;
      NEW(action,da,double);
      if (nda==0)
	{   
	  for(i=0;i<da;i++)
	    action[i]=0.0; /* Will be computed via LQR */
	}
      else
	{
	  if (da!=((unsigned int)(argc-3)))
	    {
	      fprintf(stderr,"Expected %u actions but %u given\n",da,((unsigned int)(argc-3)));
	      Error("Wrong action dimension (wrong number of parameteres to define the action)");
	    }
	  for(i=0;i<da;i++)
	    action[i]=atof(arg[3+i]);
	}

      
      /* Read starting point */
      if (nda==0)
	/* If the action is to be decided via LQR, we need the goal */
	nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);
      else
	{
	  nvs=ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1);
	  s2=NULL;
	}

      /* Random seed initialization */     
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1424256627;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      switch (dynamics)
	{
	case 1:
	case 2:
	case 3:
	  if (dynamics==1)
	    fprintf(stderr,"  Integration using the implicity trapezoidal rule in local coordinates\n");
	  else
	    {
	      if (dynamics==2)
		fprintf(stderr,"  Integration using the Euler method in local coordinates\n");
	      else
		fprintf(stderr,"  Integration using the RK4 method in local coordinates\n");
	    }
	  
	  /* Initialize the atlas */ 
	  InitAtlasRRT(&parameters,FALSE/*parallel*/,s1,(s2==NULL?ONE_TREE:TWO_TREES),FALSE/*graph*/,s2,&world,&atlasrrt);
	  
	  /* Define the path using the atlas */
	  AtlasRRTSimulate(&parameters,da,action,steps,&ns,&path,&actions,&times,&atlasrrt);
	  break;
	  
	case 4:
	case 5:
	  if (dynamics==4)
	    fprintf(stderr,"  Integration using the Euler method\n");
	  else
	    fprintf(stderr,"  Integration using the RK4 method\n");
	  
	  /* Initialize the dynamic space */
	  CS_WD_GET_SIMP_JACOBIAN(&parameters,&sJ,&world);

	  InitDynamicSpace(&parameters,FALSE,&sJ,&world,&dynamicSpace);

	  /* Define the path using the atlas */
	  if (dynamics==2)
	    Simulate(&parameters,NextDynamicStateEuler,da,action,s1,steps,&ns,&path,&actions,&times,&dynamicSpace);
	  else
	    Simulate(&parameters,NextDynamicStateRK4,da,action,s1,steps,&ns,&path,&actions,&times,&dynamicSpace);

	  break;
	  
	default:
	  Error("Unknown integration method in cuiksimulate.");
	}

      fprintf(stderr,"  Simulation concluded in %u sec\n",(unsigned int)(time(NULL)-t));
      
      /* Save the generated structures */
      SaveTrajectory(arg[1],FALSE,nvs,ns,path,da,actions,times);

      /* Release memory */
      if (dynamics==1)
	{
	  SaveAtlasRRT(&parameters,arg[1],&atlasrrt);     
	  DeleteAtlasRRT(&atlasrrt);
	}
      else
	{
	  DeleteDynamicSpace(&dynamicSpace);
	  DeleteJacobian(&sJ);
	}
      
      DeleteTrajectory(ns,path,actions,times);
      free(s1);
      if (nda==0)
	free(s2);
      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);
      DeleteFileName(&fparam);
      free(action);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  For problems where parameter N_DYNAMIC_ACTIONS is larger than 0 use:\n");   
     fprintf(stderr,"      cuiksimulate <problem filename>.%s <steps> <action>\n",WORLD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <steps> how many steps of INTEGRATION_TIME (parameter) have to be executed.\n");
     fprintf(stderr,"        <action> the action to apply. A vector with an element for each\n");
     fprintf(stderr,"                 independently actuated element in the system\n\n");
     fprintf(stderr,"  For problems where parameter N_DYNAMIC_ACTIONS is 0 use:\n");
     fprintf(stderr,"      cuiksimulate <problem filename>.%s <steps>\n",WORLD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <steps> how many steps of INTEGRATION_TIME (parameter) have to be executed.\n");
     fprintf(stderr,"  and where the action is computed via LQR with the aim of going to the goal.\n\n");
     if (argc>2)
       {
	 if (nda==0)
	   fprintf(stderr,"  In the given problem N_DYNAMIC_ACTIONS is 0\n");
	 else
	   fprintf(stderr,"  In the given problem N_DYNAMIC_ACTIONS is larger than 0\n");
       }
   }
  return(EXIT_SUCCESS);
}

