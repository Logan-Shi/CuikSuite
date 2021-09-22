
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

/** \file cuikatlasrrt.c

    \brief Main body of the \ref cuikatlasrrt.c "cuikatlasrrt" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlasrrt    [label="cuikatlasrrt"  color="#99ff99" shape=ellipse];

      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="cuik/world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikatlasrrt
      world -> cuikatlasrrt
      samples -> cuikatlasrrt
      cuikatlasrrt -> atlas;
      cuikatlasrrt -> path;
    }
    \enddot
    </center>

    Defines a RRT on a manifold.

    This is the algorithm introduced in our <a href="http://www.iri.upc.edu/people/porta/Docs/isrr11.pdf">ISRR-11</a> paper
    and in our <a href="http://www.iri.upc.edu/people/porta/Docs/tro13a.pdf">TRO-13</a> paper.

    \sa world.h world.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuikatlasrrt.c "cuikatlasrrt" application.

   Main body of the \ref cuikatlasrrt.c "cuikatlasrrt" application.

   This is the algorithm introduced in our <a href="http://www.iri.upc.edu/people/porta/Docs/isrr11.pdf">ISRR-12</a> paper
   and in our <a href="http://www.iri.upc.edu/people/porta/Docs/tro13a.pdf">TRO-13</a> paper.

   Use:
       - \b cuikatlasrrt \e problem_name.cuik/world
       .
   where
       - \e problem_name contains the problem definition. The extension is not necessary. We first
         check if a file with .cuik extension exists. Othersiwe, we try to read a .world file.
	 The name is also used to read the sample file
         including the origin/goal poses.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikatlasrrt command itself and its arguments).
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

  Tatlasrrt atlasrrt;

  boolean connected;
  double pl;
  unsigned int ns;
  double **path;
  double **actions;
  double *times;
  boolean birrt;
  boolean parallel;

  double planningTime;

  unsigned int it,nRepetitions;
  Taverages averages;

  unsigned int ri; /* random seed*/
  time_t t;  /* Used to timestamp the results */

  unsigned int db,da;

  TAtlasRRTStatistics *arst;
  
  if (argc>1)
    {
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikatlasrrt is wrong");
	}
      else
	nRepetitions=1;

      if ((nRepetitions>1)&&(GET_ATLASRRT_STATISTICS))
	Warning("To get accurate execution time statistics, set GET_ATLASRRT_STATISTICS to 0");

      if ((nRepetitions>1)&&(ATLASRRT_VERBOSE))
	Warning("To get accurate execution time statistics, set ATLASRRT_VERBOSE to 0");

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
	Error("cuikatlasrrt does not deal with bifurcations (yet)");

      if (EXPLORATION_RRT)
	birrt=FALSE;
      else
	birrt=(GetParameter(CT_BI_RRT,&parameters)>0.5);

      #if (_DEBUG>1)
        parallel=FALSE;
      #else
        parallel=(GetParameter(CT_DYNAMICS,&parameters)>0.5);
      #endif   
      
      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);
      
      /* Read samples */
      if (EXPLORATION_RRT)
	{
	  nvs=ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1);
	  s2=NULL;
	}
      else
	nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);

      /* Random seed initialization */
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1585753154;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      if (nRepetitions==1)
	{
	  fprintf(stderr,"%% **************************************************\n");
	  fprintf(stderr,"   Random seed : %u\n",ri);
	  PrintAtlasRRTDefines(stderr);
	  PrintParameters(stderr,&parameters);
	}
      
      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,TRUE,TRUE,NO_UINT,&averages);

      for(it=0;it<nRepetitions;it++)
	{
	  /* Initialize the atlas */
	  InitAtlasRRT(&parameters,parallel,s1,(birrt?TWO_TREES:ONE_TREE),FALSE/*graph*/,s2,&world,&atlasrrt);
	  fprintf(stderr,"************************************************\n");

	  /* Define the path using the atlas */
	  connected=AtlasRRT(&parameters,s2,&planningTime,&pl,&ns,&path,&da,&actions,&times,arst,&atlasrrt);

	  /* Save the results (only if one shot execution) */
	  if (nRepetitions==1)
	    {
	      if (connected)
		SaveTrajectory(arg[1],FALSE,nvs,ns,path,da,actions,times);

	      SaveAtlasRRT(&parameters,arg[1],&atlasrrt);
	    }

	  /* Summarize and release allocated objects for this repetition*/

	  if (EXPLORATION_RRT)
	    fprintf(stderr,"  Exploration concluded in %f sec\n",planningTime);
	  else
	    {
	      if (connected)
		{
		  double pt; /* path time */

		  if (times==NULL)
		    pt=0.0;
		  else
		    pt=AddVectorPositiveElements(ns,times); /* avoid the -1 in the trajectory connection */

		  fprintf(stderr,"  Execution succeeded\n");
		  
		  NewSuccesfulExperiment(planningTime,AtlasRRTMemSize(&atlasrrt),pl,pt,
					 (double)GetAtlasRRTNumCharts(&atlasrrt),
					 (double)GetAtlasRRTNumNodes(&atlasrrt),
					 NULL,NULL,
					 &averages);
		  DeleteTrajectory(ns,path,actions,times);
		}
	      else
		fprintf(stderr,"  Execution failed (%f sec)\n",planningTime);
	    }

	  DeleteAtlasRRT(&atlasrrt);

	  fprintf(stderr,"Execution compleated %u/%u\n",it+1,nRepetitions);
	}

      /* Print statistics about the execution (only if many iterations) */
 
      if (nRepetitions>1)
	{
	  fprintf(stderr,"%% **************************************************\n");
	  fprintf(stderr,"Random seed : %u\n",ri);
	  PrintAtlasRRTDefines(stderr);
	  PrintParameters(stderr,&parameters);	  
	  fprintf(stderr,"%% **************************************************\n");
	  
	  PrintAveragesHeader(stderr,argc,arg,&averages);

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
     fprintf(stderr,"      cuikatlasrrt <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}
