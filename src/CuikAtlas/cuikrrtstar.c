
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
#include <math.h>

/** \file cuikrrtstar.c

    \brief Main body of the \ref cuikrrtstar.c "cuikrrtstar" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikrrtstar    [label="cuikrrtstar"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikrrtstar
      world -> cuikrrtstar
      samples -> cuikrrtstar
      cuikrrtstar -> atlas;
      cuikrrtstar -> path;
    }
    \enddot
    </center>

    Defines an otpimal RRT on a manifold following the RRT* proposed by

      - S. Karaman and E. Frazzoli "Sampling-based algorithms for optimal motion planning" International Journal of Robotics Research, 2011
      .

    but adapted to operate on manifolds. In this case sample is done
    in the ambient space and the connections
    between points on the manifold is done using the
    method by 

     - Berenson, D., Srinivasa, S., and Kuffner, J. (2011). Task space regions: A framework for pose-constrained manipulation planning. International Journal of Robotics Research. doi 10.1177/0278364910396389.
     .

    The RRT* is different from other RRT's in that the tree construction is
    not stopped when the goal is reached, but the path is continuously
    improved. In the limit the optimal path is returned.

    \sa world.h world.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuikrrtstar.c "cuikrrtstar" application.

   Main body of the \ref cuikrrtstar.c "cuikrrtstar" application.
   
   Defines a RRT* on a manifold combining the works by
       - S. Karaman and E. Frazzoli "Sampling-based algorithms for optimal 
         motion planning" International Journal of Robotics Research, 2011
       - Berenson, D., Srinivasa, S., and Kuffner, J. (2011). 
         Task space regions: A framework for pose-constrained manipulation planning. 
         International Journal of Robotics Research. doi 10.1177/0278364910396389.
       .

   Use:
       - \b cuikrrtstar \e problem_name.world [num repetitions]
       .
   where
       - \e problem_name contains the world information, including the mechanism
         and the obstacles. The name is also used to read the sample file 
         including the origin/goal poses.
       - [num repetitions] Optional parameter to get statistics.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikrrtstar command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  
  double *s1,*s2;         /* Origin/goal of the RRT. */
  
  unsigned int nvs;

  Trrt rrt;

  boolean connected;
  double planningTime;
  double pl;
  unsigned int ns;
  double **path;
  boolean birrt;
  boolean rrtgraph;

  unsigned int it,nRepetitions;
  Taverages averages;

  unsigned int ri;
  time_t t;

  /* Statistics about the time take up to each iteration and
     the path lengh at that point */
  unsigned int maxIt,execIt;
  double *times,*costs;

  TRRTStatistics *rst;

  if (argc>1)
    {
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikrrtstar is wrong");
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
	Error("cuikrrtstar do not work for problems with dynamics");
      
      birrt=(GetParameter(CT_BI_RRT,&parameters)>0.5);
      rrtgraph=(GetParameter(CT_RRT_GRAPH,&parameters)>0.5);

      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read samples */
      nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);

      /* Random seed initialization */
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1406813613;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      /* Maximum number of iterations (set to NO_UINT to limit execution only in time)  */
      maxIt=(unsigned int)GetParameter(CT_MAX_PLANNING_ITERATIONS,&parameters);

      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,FALSE,TRUE,maxIt,&averages);

      /* Buffer to store statistics about the path length */
      if (maxIt!=NO_UINT)
	{
	  NEW(times,maxIt,double);
	  NEW(costs,maxIt,double);
	}

      for(it=0;it<nRepetitions;it++)
	{
	  /* Init a RRT (bi-directional and with graph structure depending on parameters) */
	  InitRRT(&parameters,TRUE,FALSE,s1,(birrt?TWO_TREES_WITH_SWAP:ONE_TREE),rrtgraph,s2,nvs,0,&world,&rrt);
	  fprintf(stderr,"************************************************\n");	  

	  /* Try to connect the goal with a tree from the start with
	     an optimal path */
	  connected=RRTstar(&parameters,s2,
			    &execIt,times,costs,
			    &planningTime,&pl,&ns,&path,
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
				     (execIt==maxIt?times:NULL),
				     (execIt==maxIt?costs:NULL),
				     &averages);
	      DeleteSamples(ns,path);
	    }
	  else
	    fprintf(stderr,"  Execution failed\n");
	    
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

	  #if (GET_ATLASRRT_STATISTICS)
	    PrintAtlasRRTStatistics(NULL,arst);
	    DeleteAtlasRRTStatistics(arst);
	    free(arst);
	  #endif

	  PrintAverages(stderr,&averages);

	  fprintf(stderr,"%% **************************************************\n");
	}

      /* Release memory */
      if (maxIt!=NO_UINT)
	{
	  free(times);
	  free(costs);
	}

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
     fprintf(stderr,"      cuikrrtstar <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}

