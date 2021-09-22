
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlasrrt.h"
#include "random.h"
#include "geom.h"
#include "chart.h"
#include "samples.h"
#include "averages.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/** \file cuikatlastrrt.c

    \brief Main body of the \ref cuikatlastrrt.c "cuikatlastrrt" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlastrrt    [label="cuikatlasrrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikatlastrrt
      world -> cuikatlastrrt
      samples -> cuikatlastrrt
      cuikatlastrrt -> atlas;
      cuikatlastrrt -> path;
    }
    \enddot
    </center>

    Defines an atlas RRT on a manifold but considering a cost function so that
    low cost regions are explored first. The exploration is guided by the
    method described in

         L. Jaillet, J. Cortes, T. Simeon,
	 Sampling-based path planning on configuration-space costmaps
	 IEEE Transactions on Robotics, Vol. 26(4), pp. 635 - 646, 2010.
	 http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=5477164

    \sa world.h world.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuikatlastrrt.c "cuikatlastrrt" application.

   Main body of the \ref cuikatlastrrt.c "cuikatlastrrt" application.

   Use:
       - \b cuikatlastrrt \e problem_name.world
       .
   where
       - \e problem_name contains the world information, including the mechanism
         and the obstacles. The name is also used to read the sample file 
         including the origin/goal poses.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlastrrt command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{

  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  
  double *s1,*s2;          /* Origin/goal of the RRT. */
  
  unsigned int nvs;

  Tatlasrrt atlasrrt;

  boolean connected;
  double pl, pc;
  unsigned int ns;
  double **path;

  double planningTime;

  unsigned int it,nRepetitions;
  Taverages averages;

  unsigned int ri; /* random seed*/
  time_t t;        /* Used to timestamp the results */

  unsigned int db;

  TAtlasRRTStatistics *arst;

  if (argc>1)
    {      
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikatlastrrt is wrong");
	}
      else
	nRepetitions=1;

      if ((nRepetitions>1)&&(GET_ATLASRRT_STATISTICS))
	Warning("To get accurate execution time statistics, set GET_ATLASRRT_STATISTICS to 0");

      if ((nRepetitions>1)&&(ATLASRRT_VERBOSE))
	Warning("To get accurate execution time statistics, set GET_ATLASRRT_STATISTICS to 0");

      if ((GET_ATLASRRT_STATISTICS)&&(nRepetitions>1))
	{
	  NEW(arst,1,TAtlasRRTStatistics);
	  InitAtlasRRTStatistics(arst);
	}
      else
	arst=NULL;

      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));	    
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,&parameters);
      if (db>0)
	Error("cuikatlastrrt does not deal with bifurcations (yet)");

      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read samples */
      #if (EXPLORATION_RRT)
	nvs=ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1);
	NEW(s2,nvs,double);
	memcpy(s2,s1,sizeof(double)*nvs);
      #else
	nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);
      #endif

      /* Random seed initialization */     
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1532025502;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,TRUE,TRUE,NO_UINT,&averages);

      for(it=0;it<nRepetitions;it++)
	{
	  /* Initialize the atlas */  
	  InitAtlasRRT(&parameters,FALSE/*parallel*/,s1,ONE_TREE,FALSE,s2,&world,&atlasrrt);
	  fprintf(stderr,"************************************************\n");	
	        
	  /* Define the path using the atlas */
	  connected=AtlasTRRT(&parameters,s2,
			      &planningTime,
			      &pl,&pc,&ns,&path,CS_WD_COST_FN(&world),
			      CS_WD_COST_PTR(&world),arst,&atlasrrt);
      
	  /* Save the results (only if one shot execution) */
	  if (nRepetitions==1)
	    {
	      if (connected)
		SaveSamples(arg[1],FALSE,nvs,ns,path);

	      SaveAtlasRRT(&parameters,arg[1],&atlasrrt);
	    }

	  /* Summarize and release allocated objects for this repetition*/

	  if ((EXPLORATION_RRT)||(connected))
	    {
	      NewSuccesfulExperiment(planningTime,AtlasRRTMemSize(&atlasrrt),pl,pc,
				     (double)GetAtlasRRTNumCharts(&atlasrrt),
				     (double)GetAtlasRRTNumNodes(&atlasrrt),
				     NULL,NULL,
				     &averages);
	      DeleteSamples(ns,path);
	    }
	  else
	    fprintf(stderr,"  Execution failed (%f sec)\n",planningTime);

	  DeleteAtlasRRT(&atlasrrt);

	  fprintf(stderr,"Execution compleated %u/%u\n",it+1,nRepetitions);
	}
      
      /* Print statistics about the execution (only if many iterations) */
      if (nRepetitions>1)
	{	  
	  PrintAveragesHeader(stderr,argc,arg,&averages);

	  fprintf(stderr,"%% **************************************************\n");
	  fprintf(stderr,"Random seed : %u\n",ri);
	  fprintf(stderr,"   Random seed : %u\n",ri);
	  PrintAtlasRRTDefines(stderr);
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
      DeleteAverages(&averages);

      /* Release memory */
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
     fprintf(stderr,"      cuikatlastrrt <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}

