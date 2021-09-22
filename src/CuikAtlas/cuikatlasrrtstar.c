
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlasrrt.h"
#include "random.h"
#include "geom.h"
#include "samples.h"
#include "averages.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/** \file cuikatlasrrtstar.c

    \brief Main body of the \ref cuikatlasrrtstar.c "cuikatlasrrtstar" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlasrrtstar    [label="cuikatlasrrtstar"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="cuik/world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikatlasrrtstar
      world -> cuikatlasrrtstar
      samples -> cuikatlasrrtstar
      cuikatlasrrtstar -> atlas;
      cuikatlasrrtstar -> path;
    }
    \enddot
    </center>

    Version of \ref cuikrrtstar.c "cuikrrtstar" where the sampling and tree
    growing uses the atlas (like in \ref cuikatlasrrt.c "cuikatlasrrt").

    This is the algorithm introduced in our <a href="http://www.iri.upc.edu/people/porta/Docs/rss12.pdf">RSS-12</a> paper.

    \sa world.h world.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuikatlasrrtstar.c "cuikatlasrrtstar" application.

   Main body of the \ref cuikatlasrrtstar.c "cuikatlasrrtstar" application.
   
  
   Version of \ref cuikrrtstar.c "cuikrrtstar" where the sampling and tree
   growing uses the atlas (like in \ref cuikatlasrrt.c "cuikatlasrrt").

   This is the algorithm introduced in our <a href="http://www.iri.upc.edu/people/porta/Docs/rss12.pdf">RSS-12</a> paper.


   Use:
       - \b cuikatlasrrtstar \e problem_name.cuik/world [num repetitions]
       .
   where
       - \e problem_name contains the problem definition. The extension is not necessary. We first
         check if a file with .cuik extension exists. Othersiwe, we try to read a .world file. 
         The name is also used to read the sample file 
         including the origin/goal poses.
       - [num repetitions] Optional parameter to get statistics.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlasrrtstar command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  
  double *s1,*s2;         /* Origin/goal of the AtlasRRT. */

  unsigned int nvs;

  Tatlasrrt atlasrrt;

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

  TAtlasRRTStatistics *arst;

  if (argc>1)
    {
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikatlasrrtstar is wrong");
	}
      else
	nRepetitions=1;
      
      if ((nRepetitions>1)&&(RRT_VERBOSE))
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

      if (GetParameter(CT_DYNAMICS,&parameters)>0)
	Error("cuikatlasrrtstar do not work for problems with dynamics");
      
      birrt=(GetParameter(CT_BI_RRT,&parameters)>0.5);
      rrtgraph=(GetParameter(CT_RRT_GRAPH,&parameters)>0.5);

      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read samples */
      nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);

      /* Random seed initialization */
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1341338413; // with gamma=0 the c8 give a long path
      //ri=1341346253; // seed used to generate the growing RRTs for c8
      ri=1416402361;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);
      
      /* Maximum of iteraitons (set to NO_UINT to limit execution only in time) */
      maxIt=(unsigned int)GetParameter(CT_MAX_PLANNING_ITERATIONS,&parameters);

      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,TRUE,TRUE,maxIt,&averages);

      /* Buffer to store statistics about the path length */
      if (maxIt!=NO_UINT)
	{
	  NEW(times,maxIt,double);
	  NEW(costs,maxIt,double);
	}

      for(it=0;it<nRepetitions;it++)
	{  
	  /* Init an AtlasRRT (bi-directional or with graph structure depending on parameters) */
	  InitAtlasRRT(&parameters,TRUE/*parallel*/,s1,(birrt?TWO_TREES_WITH_SWAP:ONE_TREE),rrtgraph,s2,&world,&atlasrrt);
	  fprintf(stderr,"************************************************\n");	

	  /* Try to connect the goal with a tree from the start with
	     an optimal path */
	  connected=AtlasRRTstar(&parameters,s2,
				 &execIt,
				 times,costs,
				 &planningTime,&pl,&ns,&path,arst,&atlasrrt);

	  /* Save the results (only if one shot execution) */
	  if (nRepetitions==1)
	    {
	      if (connected)
		SaveSamples(arg[1],FALSE,nvs,ns,path);
	      
	      SaveAtlasRRT(&parameters,arg[1],&atlasrrt);
	    }

	  /* Summarize and release allocated objects for this repetition*/
	  if (connected)
	    {
	      NewSuccesfulExperiment(planningTime,AtlasRRTMemSize(&atlasrrt),pl,0,
				     (double)GetAtlasRRTNumCharts(&atlasrrt),
				     (double)GetAtlasRRTNumNodes(&atlasrrt),
				     (execIt==maxIt?times:NULL),
				     (execIt==maxIt?costs:NULL),
				     &averages);

	      DeleteSamples(ns,path);
	    }
	  else
	    fprintf(stderr,"  Execution failed\n");
	    
	  DeleteAtlasRRT(&atlasrrt);

	  fprintf(stderr,"Execution compleated %u/%u\n",it+1,nRepetitions);
	}

      /* Print data about the path length at each iteration. 0 means no path
         to goal found yet */

      /* Print statistics about the execution (only if many iterations) */
	  
      if (nRepetitions>1)
	{	  
	  PrintAveragesHeader(stderr,argc,arg,&averages);

	  fprintf(stderr,"%% **************************************************\n");
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
     fprintf(stderr,"      cuikatlasrrtstar <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}

