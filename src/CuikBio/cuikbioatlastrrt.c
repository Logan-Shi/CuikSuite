
#include "bioworld.h"
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

/** \file cuikbioatlastrrt.c

    \brief Main body of the \ref cuikbioatlastrrt.c "cuikbioatlastrrt" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikbioatlastrrt    [label="cuikbioatlasrrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];
      pdb     [label="pdb"     color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];

      param -> cuikbioatlastrrt
      pdb -> cuikbioatlastrrt
      samples -> cuikbioatlastrrt
      cuikbioatlastrrt -> atlas;
      cuikbioatlastrrt -> path;
    }
    \enddot
    </center>

    This is the same as \ref cuikatlastrrt.c "cuikatlastrrt" but operating
    on molecules. In this case the cost is the molecular energy computed via
    OpenBabel.

    With a minimum effort we could also implement the molecular alternative of
    \ref cuikcctrrt.c "cuikcctrrt", but it is not implemented yet.
*/

/** 
   \brief Main body of the \ref cuikbioatlastrrt.c "cuikbioatlastrrt" application.

   Main body of the \ref cuikbioatlastrrt.c "cuikbioatlastrrt" application.

   Use:
       - \b cuikbioatlastrrt \e problem_name.pdb [rep] 
       .
   where
       - \e problem_name.pdb contains the molecule information.
       - \e [rep] Number of repetitions. Optional. Used to get statistics.
       .
   The \e .pdb extension is compulsatory (however any extension valid for OpenBabel can
   be used).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikbioatlastrrt command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  if (argc>1)
    {     
      #if (ATLAS_ON_CUIKSYSTEM)
	Error("cuikbioatlastrrt can ony operate on worlds");
      #else
      TBioWorld bioWorld;      /* The molecular information.  */
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
      TAtlasBase ba;

      unsigned int db;
      
      TAtlasRRTStatistics *arst;

      #if (EXPLORATION_RRT)
        nRepetitions=1;
      #else
        if (argc>2)
	  {
	    nRepetitions=atoi(arg[2]);
	    if (nRepetitions==0)
	      Error("The repetition parameter for cuikbioatlastrrt is wrong");
	  }
	else
	  nRepetitions=1;
      #endif

      if ((nRepetitions>1)&&(GET_ATLASRRT_STATISTICS))
	Error("To get meaninful statistics results, please set GET_ATLASRRT_STATISTICS to 0");

      if ((nRepetitions>1)&&(ATLASRRT_VERBOSE))
	Error("To get meaninful statistics results, please set ATLASRRT_VERBOSE to 0");

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

      /*Read the bio-information from file*/
      InitBioWorld(&parameters,arg[1],NO_UINT,&s1,&bioWorld);
      free(s1);
      CS_WD_FROM_WORLD(BioWorldWorld(&bioWorld),&ba);

      /* Read the goal sample */
      #if (EXPLORATION_RRT)
        nvs=ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&ba),&s1);
        NEW(s2,nvs,double);
        memcpy(s2,s1,sizeof(double)*nvs);
      #else
        nvs=ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&ba),&s1,&s2);
      #endif

      /* Random seed initialization */     
      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t; 
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      /* Start the process to connect the two samples */
      InitAverages(nRepetitions,TRUE,TRUE,NO_UINT,&averages);

      for(it=0;it<nRepetitions;it++)
	{
	  /* Initialize the atlas */
	  fprintf(stderr,"************************************************\n");	  
	  InitAtlasRRT(&parameters,FALSE/*parallel*/,s1,ONE_TREE,FALSE,s2,&ba,&atlasrrt);
	        
	  /* Define the path using the atlas */	  
	  connected=AtlasTRRT(&parameters,s2,
			      &planningTime,
			      &pl,&pc,&ns,&path,BioWorldEnergy,
			      (void *)&bioWorld,arst,&atlasrrt);
      
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
	  fprintf(stderr,"GlobalCurv: %u  Tree_ATLAS: %u\n",
		  GET_ATLASRRT_GLOBAL_CURV_CHECK,USE_ATLAS_TREE);
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
      DeleteBioWorld(&bioWorld);

      DeleteFileName(&fparam);
      #endif
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikbioatlastrrt <problem filename>.world [num Repetitions]\n");
     fprintf(stderr,"  where <problem filename>.pdb the equations/world description\n");
     fprintf(stderr,"        <num Repetitions> experiment repetitions to gather statistics\n");
     fprintf(stderr,"                          This is optional.\n");
     fprintf(stderr,"  The '.pab' extension is required\n");
     fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
   }
  return(EXIT_SUCCESS);
}

