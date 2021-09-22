
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

/** \file cuikcbirrt.c

    \brief Main body of the \ref cuikcbirrt.c "cuikcbirrt" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikcbirrt    [label="cuikcbirrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikcbirrt
      world -> cuikcbirrt
      samples -> cuikcbirrt
      cuikcbirrt -> atlas;
      cuikcbirrt -> path;
    }
    \enddot
    </center>

    Defines a RRT on a manifold using the method proposed by

     Berenson, D., Srinivasa, S., and Kuffner, J. (2011). 
     Task space regions: A framework for pose-constrained manipulation planning. 
     International Journal of Robotics Research. doi 10.1177/0278364910396389.

    \sa world.h world.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuikcbirrt.c "cuikcbirrt" application.

   Main body of the \ref cuikcbirrt.c "cuikcbirrt" application implementing the
   bidirectional RRT proposed in

     Berenson, D., Srinivasa, S., and Kuffner, J. (2011). 
     Task space regions: A framework for pose-constrained manipulation planning. 
     International Journal of Robotics Research. doi 10.1177/0278364910396389.

   Use:
       - \b cuikcbirrt \e problem_name.world
       .
   where
       - \e problem_name contains the world information, including the mechanism
         and the obstacles. The name is also used to read the sample file 
         including the origin/goal poses.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikcbirrt command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc,char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  
  double *s1,*s2;         /* Origin/goal of the RRT. */
  
  unsigned int nvs;

  Trrt rrt;

  boolean connected;
  double pl;
  unsigned int ns;
  double **path;

  double planningTime;

  unsigned int it,nRepetitions;
  Taverages averages;

  unsigned int ri;
  time_t t;

  TRRTStatistics *rst;

  #if (EXPLORATION_RRT)
    Error("cuikcbirrt can not be used in exploration mode (use ccrrt)");
  #endif


  if (argc>1)
    {
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikcbirrt is wrong");
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

      if (GetParameter(CT_DYNAMICS,&parameters)>0)
	Error("cuikcbirrt do not work for problems with dynamics");
      
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
	  /* Init a bi-directional RRT (bi-directional despite the value of BI_RRT parameter) */
	  InitRRT(&parameters,FALSE,FALSE,s1,TWO_TREES,FALSE,s2,nvs,0,&world,&rrt);
	  fprintf(stderr,"**************************************************\n");

	  /* Try to connect the two trees */
	  connected=cBiRRT(&parameters,s2,
			   &planningTime,
			   &pl,&ns,&path,
			   rst,&rrt);

	  /* Save the results (only if one shot execution) */
	  if (nRepetitions==1)
	    {
	      Tfilename frrt;

	      if (connected)
		SaveSamples(arg[1],FALSE,nvs,ns,path);

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
     fprintf(stderr,"      cuikcbirrt <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}

