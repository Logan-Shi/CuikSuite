
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "rrt.h"
#include "random.h"
#include "geom.h"
#include "samples.h"
#include "averages.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/** \file cuikkinoest.c

    \brief Main body of the \ref cuikkinoest.c "cuikkinoest" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikkinoest    [label="cuikkinoest"  color="#99ff99" shape=ellipse];

      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikkinoest
      world -> cuikkinoest
      samples -> cuikkinoest
      cuikkinoest -> atlas;
      cuikkinoest -> path;
    }
    \enddot
    </center>

    Defines a kinodynamic EST on a manifold using the method proposed in

      - D. Hsu, J-C. Latombe, R. Motwani, Path Planning in Expansive Configuration Spapces,
        International Journal of Computational Geometry and Applications, Vol 9, N. 4, 1999.
      .

    \sa world.h world.c cuikplan.c
*/
 
/** 
   \brief Main body of the \ref cuikkinoest.c "cuikkinoest" application.

   Main body of the \ref cuikkinoest.c "cuikkinoest" application.

   Defines a kinodynamic EST using the method described in

      - D. Hsu, J-C. Latombe, R. Motwani, Path Planning in Expansive Configuration Spapces,
        International Journal of Computational Geometry and Applications, Vol 9, N. 4, 1999.
      .

   This method only uses the differential constraints (even converting the
   holonomic constraints to its differencial form) and, thus, it does
   not exploit the underlaying manifold structure. Different integration
   methods (Euler, RK4) provide different accuracy as far as error w.r.t. the
   manifold. However, they all accumulate error in the long term.

   Use:
       - \b cuikkinoest \e problem_name.world
       .
   where
       - \e problem_name contains the world information, including the mechanism
         and the obstacles. The name is also used to read the sample file
         including the origin/goal poses.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikkinoest command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;

  double *s1,*s2;         /* Origin/goal of the EST. */

  unsigned int nvs;

  Trrt rrt;

  boolean connected;
  double pl;
  unsigned int ns;
  double **path;
  double **actions;
  double *times;
  unsigned int da,dof;
  
  double planningTime;

  unsigned int dynamics;
  boolean birrt;
  
  unsigned int it,nRepetitions;
  Taverages averages;

  unsigned int ri;
  time_t t;
  Tintegrator *intFunction;

  TRRTStatistics *rst;

  if (argc>1)
    {
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikkinoest is wrong");
	}
      else
	nRepetitions=1;

      if ((nRepetitions>1)&&((RRT_VERBOSE)||(GET_RRT_STATISTICS)))
	Warning("To get accurate execution time statistics, set RRT_VERBOSE and GET_RRT_STATISTICS to 0");

      if ((GET_RRT_STATISTICS)&&(nRepetitions>1))
	{
	  NEW(rst,1,TRRTStatistics);
	  InitRRTStatistics(rst);
	}
      else
	rst=NULL;

      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      dynamics=(unsigned int)GetParameter(CT_DYNAMICS,&parameters);
      
      switch(dynamics)
	{
	case 0:
	Error("cuikkinorrt operates in problems with dynamics");
	  break;
	case 1:
	Error("cuikkinorrt does not operate with local coordinates (only Euler or RK4). Use: cuikatlasrrt");
	  break;
	case 2:
	  intFunction=NextDynamicStateEuler;
	  break;
	case 3:
	  intFunction=NextDynamicStateRK4;
	  break;
	default:
	  Error("Wrong value for parameter DYNAMICS (must be 0..3)");
	}
            
      birrt=(boolean)GetParameter(CT_BI_RRT,&parameters);
      if (birrt)
	Error("bi-EST is not implemented yet");
	  
      dof=(unsigned int)GetParameter(CT_N_DOF,&parameters);
      
      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read samples */
      nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);

      /* Random seed initialization */
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,FALSE,TRUE,NO_UINT,&averages);

      for(it=0;it<nRepetitions;it++)
	{
	  /* Init an EST */
	  InitRRT(&parameters,FALSE,FALSE,s1,(birrt?TWO_TREES:ONE_TREE),FALSE,s2,nvs,dof/2,&world,&rrt);
	  fprintf(stderr,"**************************************************\n");

	  /* Try to connect the goal with a tree from the start */
	  if (birrt)
	    Error("bi-EST is not implemented yet");
	  else
	    connected=kinoEST(&parameters,intFunction,s2,
			      &planningTime,
			      &pl,&ns,&path,
			      &da,&actions,&times,
			      rst,&world,&rrt);

	  /* Save the results (only if one shot execution) */
	  if (nRepetitions==1)
	    {
	      Tfilename frrt;

	      if (connected)
		SaveTrajectory(arg[1],FALSE,nvs,ns,path,da,actions,times);

	      CreateFileName(NULL,arg[1],NULL,RRT_EXT,&frrt);
	      fprintf(stderr,"Writing RRT to                    : %s\n",GetFileFullName(&frrt));
	      SaveRRT(&frrt,&rrt);
	      DeleteFileName(&frrt);
	    }

	  /* Summarize and release allocated objects for this repetition*/
	  if (connected)
	    {
	      NewSuccesfulExperiment(planningTime,RRTMemSize(&rrt),pl,0,
				     NO_UINT,
				     (double)GetRRTNumNodes(&rrt),
				     NULL,NULL,
				     &averages);
	      DeleteSamples(ns,path);
	    }
	  else
	    fprintf(stderr,"  Execution failed (%f sec)\n",planningTime);

	  DeleteRRT(&rrt);

	  fprintf(stderr,"Execution compleated %u/%u\n",it+1,nRepetitions);
	}

      /* Print statistics about the execution (only if many iterations) */
      if (nRepetitions>1)
	{
	  PrintAveragesHeader(stderr,argc,arg,&averages);

	  fprintf(stderr,"%% **************************************************\n");
	  fprintf(stderr,"   Random seed : %u\n",ri);
	  PrintRRTDefines(stderr);
	  PrintParameters(stderr,&parameters);

	  #if (GET_RRT_STATISTICS)
	    PrintRRTStatistics(NULL,rst);
	    DeleteRRTStatistics(rst);
	    free(rst);
	  #endif

	  PrintAverages(stderr,&averages);

	  fprintf(stderr,"%% **************************************************\n");
	}

      /* Release memory */
      DeleteAverages(&averages);

      free(s1);
      free(s2);

      DeleteParameters(&parameters);

      CS_WD_DELETE(&world);

      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");
     fprintf(stderr,"      cuikkinoest <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}
