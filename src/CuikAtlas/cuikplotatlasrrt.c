
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlasrrt.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikplotatlasrrt.c

    \brief Main body of the \ref cuikplotatlasrrt.c "cuikplotatlasrrt" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplotatlasrrt    [label="cuikplotatlasrrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuikplotatlasrrt;
      world -> cuikplotatlasrrt;
      atlas -> cuikplotatlasrrt;
      cuikplotatlasrrt -> gcl;
    }
    \enddot
    </center>

    Plots a 3d projection of an atlas generated with cuikatlas.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikplotatlasrrt.c "cuikplotatlasrrt" application.

   Main body of the \ref cuikplotatlasrrt.c "cuikplotatlasrrt" application.

   Use:
       - \b cuikplotatlasrrt \e problem_name \e xID \e yID \e zID
       .
   where
       - \e problem_name is used to load the .world and .atlas files necessary
         to generate the .cgl plot.
       - \e xID \e yID \e zID are the identifier of the variables on which to project.
         These are indices of system variables, numbered consecutively and without 
         considering dummy ones (these are the ones stored, for instance, in the
	 solution path files).  
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikplotatlasrrt command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Tatlasrrt atlasRRT;      /* The atlas to plot. */

  unsigned int nx,ny,nz;
  unsigned int xID,yID,zID;
  unsigned int i,nv,nvs;  
  boolean *systemVars;

  double *s1,*s2;
  double *p1,*p2;

  Tfilename fparam;
  Tfilename fpath;

  boolean havePath,traj;
  unsigned int ns;
  double **path;
  unsigned int da;
  double **actions;
  double *times;
    
  
  if (argc==5)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Validate the input projection dimensions */
      nv=CS_WD_GET_SYSTEM_VARS(&systemVars,&world);
      nvs=CS_WD_GET_NUM_SYSTEM_VARS(&world);
      
      nx=atoi(arg[2]);
      ny=atoi(arg[3]);
      nz=atoi(arg[4]);
      	  
      if (nx>=nvs)
	Error("First index out of range");
      if (ny>=nvs)
	Error("Second index out of range");
      if (nz>=nvs)
	Error("Third index out of range");
      
      fprintf(stderr,"Projecting on variables           : ");
      PRINT_VARIABLE_NAME(stderr,CS_WD_GET_SYSTEM_VAR_NAME(nx,&world));fprintf(stderr,",");
      PRINT_VARIABLE_NAME(stderr,CS_WD_GET_SYSTEM_VAR_NAME(ny,&world));fprintf(stderr,",");
      PRINT_VARIABLE_NAME(stderr,CS_WD_GET_SYSTEM_VAR_NAME(nz,&world));fprintf(stderr,"\n");
      
      nvs=0;
      for(i=0;i<nv;i++)
	{
	  if (systemVars[i])
	    {
	      /* Transform index from system variables only to
	         all variables (in the original system in both cases!!) */
	      if (nx==nvs) xID=i;
	      if (ny==nvs) yID=i;
	      if (nz==nvs) zID=i;
	      nvs++;
	    }
	}

      /* Read the Atlas, the RRT, and information linking them */
      LoadAtlasRRT(&parameters,arg[1],&world,&atlasRRT);

      /* Read the start and goal of the RRT */
      NEW(p1,3,double);
      if (EXPLORATION_RRT)
	{
	  ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1);
	  s2=NULL;
	  p2=NULL;
	}
      else
	{
	  ReadTwoSamples(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1,&s2);
	  NEW(p2,3,double);
	  p2[0]=s2[nx];
	  p2[1]=s2[ny];
	  p2[2]=s2[nz];
	}
      p1[0]=s1[nx];
      p1[1]=s1[ny];
      p1[2]=s1[nz];
      
      /* Plot the atlas, the RRT and the information linking them */
      PlotAtlasRRT(arg[1],argc,arg,&parameters,xID,yID,zID,p1,p2,&atlasRRT);

      traj=TRUE;
      CreateFileName(NULL,arg[1],"_traj",SOL_EXT,&fpath);

      havePath=traj=LoadTrajectory(&fpath,&nv,&ns,&path,&da,&actions,&times);
      if (!traj)
	{
	  DeleteFileName(&fpath);
	  CreateFileName(NULL,arg[1],"_path",SOL_EXT,&fpath);
	  havePath=LoadSamples(&fpath,&nv,&ns,&path);
	}
  
      if (havePath)
	{
	  Tfilename fpathplot;
	  Tplot3d p3d;
	  Tcolor red;
	    
	  double *x,*y,*z;
  
	  NEW(x,ns,double);
	  NEW(y,ns,double);
	  NEW(z,ns,double);

	  for(i=0;i<ns;i++)
	    {
	      /* For the paths we only store system variables */
	      x[i]=path[i][nx];
	      y[i]=path[i][ny];
	      z[i]=path[i][nz];
	    }

	  if (traj)
	    CreateFileName(NULL,arg[1],"_traj",PLOT3D_EXT,&fpathplot);
	  else
	    CreateFileName(NULL,arg[1],"_path",PLOT3D_EXT,&fpathplot);
	  fprintf(stderr,"Generating path plot to           : %s\n",GetFileFullName(&fpathplot));

	  NewColor(1,0,0,&red);
	      
	  InitPlot3d(GetFileFullName(&fpathplot),TRUE,argc,arg,&p3d);
	  StartNew3dObject(&red,&p3d);
	    PlotVect3d(ns,x,y,z,&p3d);
	  Close3dObject(&p3d);
	  ClosePlot3d(FALSE,&p3d);
	  
	  DeleteColor(&red);

	  DeleteFileName(&fpathplot);
      
	  free(x);
	  free(y);
	  free(z);
	  DeleteTrajectory(ns,path,actions,times);
	}      

      /* Release memory */
      free(s1); free(p1);
      if (s2!=NULL) {free(s2);free(p2);}
      
      DeleteParameters(&parameters);

      free(systemVars);

      CS_WD_DELETE(&world);

      DeleteAtlasRRT(&atlasRRT);

      DeleteFileName(&fpath);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikplotatlasrrt <problem filename> <xID> <yID> <zID>\n");
     fprintf(stderr,"  where <problem filename> is the atlas to plot.\n");
     fprintf(stderr,"        <xID> <yID> <zID> are the 3 projection dimensions.\n");
     fprintf(stderr,"          (indices of system variables as those in the _path.sol file from 0)\n");
     
   }
  return(EXIT_SUCCESS);
}

