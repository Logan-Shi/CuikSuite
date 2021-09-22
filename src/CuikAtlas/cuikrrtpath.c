
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "rrt.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikrrtpath.c

    \brief Main body of the \ref cuikrrtpath.c "cuikrrtpath" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikrrtpath    [label="cuikrrtpath"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      rrt     [label="rrt"     color="#ff9999" ];
      sol     [label="sol"    color="#ff9999" ];

      param -> cuikrrtpath;
      world -> cuikrrtpath;
      rrt -> cuikrrtpath;
      cuikrrtpath -> sol;
    }
    \enddot
    </center>

    Extracts a branch from an RRT.

    \sa cuikrrt.c
*/

/** 
   \brief Main body of the \ref cuikrrtpath.c "cuikrrtpath" application.

   Main body of the \ref cuikrrtpath.c "cuikrrtpath" application.

   Use:
       - \b cuikrrtpath \e problem_name \e sampleID 
       .
   where
       - \e problem_name is used to load the .world and .rrt files necessary
         to generate the .sol plot.
       - \e sampleID The identifier of the sample to track to the root.  
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikrrtpath command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Trrt rrt;                /* The rrt to plot. */

  unsigned int sampleID;

  unsigned int nvs;
  unsigned int da;
  double pl,pc;
  unsigned int ns;
  double **path;
  double **actions;
  double *times;
  
  Tfilename fparam;
  Tfilename frrt;
  Tfilename fpath;

  
  if (argc==3)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);
      
      /* Read the RRT */
      CreateFileName(NULL,arg[1],NULL,RRT_EXT,&frrt);
      fprintf(stderr,"Reading rrt from                  : %s\n",GetFileFullName(&frrt));
      LoadRRT(&parameters,&frrt,&world,&rrt);

      /* The sample id */
      sampleID=atoi(arg[2]);

      if (sampleID>=GetRRTNumNodes(&rrt))
	Error("SampleID out of range");
      fprintf(stderr,"Reading rrt from                  : %s\n",GetFileFullName(&frrt));
      fprintf(stderr,"Path to sample                    : %u/%u\n",sampleID,GetRRTNumNodes(&rrt));
      fprintf(stderr,"Sample in tree                    : %s\n",(GetRRTNodeTree(sampleID,&rrt)==START2GOAL?"Start2Goal":"Goal2Start"));
      
      /* Get the trajectory */
      nvs=ReconstructRRTPath(&parameters,sampleID,&pl,&pc,&ns,&path,&actions,&times,&rrt);

      fprintf(stderr,"Path steps                        : %u\n",ns);
      fprintf(stderr,"Path length                       : %f\n",pl);
            
      /* save the trajectory */
      da=GetRRTActionSpaceDimension(&rrt);
      SaveTrajectory(arg[1],"_traj",nvs,ns,path,da,actions,times);
      
      /* Release memory */
      DeleteTrajectory(ns,path,actions,times);
      
      DeleteParameters(&parameters);

      CS_WD_DELETE(&world);

      DeleteRRT(&rrt);

      DeleteFileName(&fpath);
      DeleteFileName(&frrt);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikrrtpath <problem filename> <sampleID> \n");
     fprintf(stderr,"  where <problem filename> is the rrt to plot\n");
     fprintf(stderr,"        <sampleID> ID of the sample to track to the root\n");
     
   }
  return(EXIT_SUCCESS);
}

