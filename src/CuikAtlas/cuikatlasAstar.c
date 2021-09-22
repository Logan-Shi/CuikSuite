
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "random.h"
#include "geom.h"
#include "samples.h"
#include "rrt.h"
#include "averages.h"

#include <stdlib.h>
#include <time.h>

/** \file cuikatlasAstar.c

    \brief Main body of the \ref cuikatlasAstar.c "cuikatlasAstar" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlasAstar    [label="cuikatlasAstar"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="cuik/world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikatlasAstar
      world -> cuikatlasAstar
      samples -> cuikatlasAstar
      cuikatlasAstar -> atlas;
      cuikatlasAstar -> path;
    }
    \enddot
    </center>

    This applications tries to connect two given samples with a path on the manifold 
    defined by a set of equations.

    \sa world.h world.c cuikplan.c
*/


/** 
   \brief Main body of the \ref cuikatlasAstar.c "cuikatlasAstar" application.

   Main body of the \ref cuikatlasAstar.c "cuikatlasAstar" application.

   Use:
       - \b cuikatlasAstar \e problem_name.cuik/world
       .
   where
       - \e problem_name contains the problem definition. The extension is not necessary. We first
         check if a file with .cuik extension exists. Othersiwe, we try to read a .world file. 
	 The name is also used to read the sample file 
         including the origin/goal poses.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlasAstar command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{

  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  
  double *s1,*s2;          /* Two points on the manifold to connect. */

  unsigned int nvs;

  boolean connected;
  double pl;
  unsigned int ns;
  double **path;

  double planningTime;

  Tatlas atlas;

  unsigned int it,nRepetitions;
  Taverages averages;

  unsigned int ri;
  time_t t;

  if (argc>1)
    {
      if (argc>2)
	{
	  nRepetitions=atoi(arg[2]);
	  if (nRepetitions==0)
	    Error("Second parameter for cuikatlasAstar is wrong");
	}
      else
	nRepetitions=1;
      
      if ((nRepetitions>1)&&(ATLAS_VERBOSE))
	Warning("To get accurate execution time statistics, set GET_ATLASRRT_STATISTICS to 0");

      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      if (GetParameter(CT_DYNAMICS,&parameters)>0)
	Error("cuikatlasAstar do not work for problems with dynamics");
      
      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read two samples (start/goal) */
      nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);

      /* Random seed initialization */
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,TRUE,FALSE,NO_UINT,&averages);

      for(it=0;it<nRepetitions;it++)
	{
	  /* Initialize the atlas */
	  if (!InitAtlasFromPoint(&parameters,TRUE/*parallel*/,FALSE,s1,&world,&atlas))
	    Error("Can not start an atlas from the given point");

	  /* Completed the path to the goal */

	    connected=AtlasAStar(&parameters,s2,
				 &planningTime,
				 &pl,&ns,&path,&atlas);

	  /* Save the results (only if one shot execution) */
	  if (nRepetitions==1)
	    {
	      Tfilename fatlas;

	      if (connected)
		{
		  SaveSamples(arg[1],FALSE,nvs,ns,path);
		  // fprintf(stderr,"Path lenght %f\n",pl);
		}

	      // fprintf(stderr,"  Ambient space dim: %u\n",GetAtlasAmbientDim(&atlas));
	      
	      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
	      fprintf(stderr,"Writing atlas to                  : %s\n",GetFileFullName(&fatlas));
	      SaveAtlas(&parameters,&fatlas,&atlas);
	      DeleteFileName(&fatlas);
	    }
	  
	  /* Summarize and delete the information for this repetition */
	  if (connected)
	    { 
	      NewSuccesfulExperiment(planningTime,AtlasMemSize(&atlas),pl,0,
				     (double)GetAtlasNumCharts(&atlas),
				     NO_UINT,NULL,NULL,
				     &averages);
	      DeleteSamples(ns,path);
	    }
	  else
	    fprintf(stderr,"  Execution failed (%f sec)\n",planningTime);
	    
	  DeleteAtlas(&atlas);	

	  fprintf(stderr,"Execution compleated %u/%u\n",it+1,nRepetitions);  
	}

      /* Print statistics about the execution (only if many iterations) */
      if (nRepetitions>1)
	{
	  PrintAveragesHeader(stderr,argc,arg,&averages);

	  fprintf(stderr,"%% **************************************************\n");
	  fprintf(stderr,"   Random seed : %u\n",ri);
	  PrintAtlasDefines(stderr);
	  PrintParameters(stderr,&parameters);

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
     fprintf(stderr,"      cuikatlasAstar <problem filename>.%s [num Repetitions]\n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This parameter is optional.\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}

