
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikplotpath.c

    \brief Main body of the \ref cuikplotpath.c "cuikplotpath" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplotpath    [label="cuikplotpath"  color="#99ff99" shape=ellipse URL="\ref cuikplotpath.c"];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      path    [label="path"   color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuikplotpath;
      world -> cuikplotpath;
      path -> cuikplotpath;
      cuikplotpath -> gcl;
    }
    \enddot
    </center>

    Plots a 3d projection of a path, typically optained wiht a planning
    process or even a smoothed path.
*/

/** 
   \brief Main body of the \ref cuikplotpath.c "cuikplotpath" application.

   Main body of the \ref cuikplotpath.c "cuikplotpath" application.

   Use:
       - \b cuikplotpath \e problem_name [\e path_name] \e xID \e yID \e zID
       .
   where
       - \e problem_name is used to load the .world/cuik/tens files necessary
         to generate the .gcl plot.
       - \e path_name [optional] The file with the path to plot. If not given
         the path filename is assumed to be \e problem_name_path.sol .
       - \e xID \e yID \e zID are the identifier of the variables on which to project.
         These are indices of system variables, numbered consecutively and without 
         considering dummy ones (these are the ones stored, for instance, in the
	 solution path files).  
       .
   The \e problem_name and \e path_name (if given) are without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikplotpath command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  unsigned int nx,ny,nz;
  unsigned int nvs;  

  unsigned int ns;
  double **path;

  Tfilename fparam;
  Tfilename fpath;

  //boolean smooth;
  
  if (argc>=5)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/ 
      CS_WD_INIT(&parameters,arg[1],&world);
          
      /* Validate the input projection dimensions */
      nvs=CS_WD_GET_NUM_SYSTEM_VARS(&world);
      
      if (argc>5)
	{
	  CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fpath);
      
	  nx=atoi(arg[3]);
	  ny=atoi(arg[4]);
	  nz=atoi(arg[5]);
	}
      else
	{
	  CreateFileName(NULL,arg[1],"_path",SOL_EXT,&fpath);
      
	  nx=atoi(arg[2]);
	  ny=atoi(arg[3]);
	  nz=atoi(arg[4]);
	}

      if (nx>=nvs)
	Error("First index out of range");
      if (ny>=nvs)
	Error("Second index out of range");
      if (nz>=nvs)
	Error("Third index out of range");

      /* Load the path  */
      if (LoadSamples(&fpath,&nvs,&ns,&path))
	{
	  /*If the path was actually loaded*/
	  Tfilename fpathplot;
	  Tplot3d p3d;

	  if (argc>5)
	    CreateFileName(NULL,arg[2],NULL,PLOT3D_EXT,&fpathplot);
	  else
	    CreateFileName(NULL,arg[1],"_path",PLOT3D_EXT,&fpathplot);

	  /* Plot the path */
	  fprintf(stderr,"Generating path plot to           : %s\n",GetFileFullName(&fpathplot));

	  InitPlot3d(GetFileFullName(&fpathplot),FALSE,argc,arg,&p3d);

	  PlotSamples(&parameters,&p3d,nx,ny,nz,ns,path);

	  ClosePlot3d(FALSE,&p3d);
	  
	  DeleteFileName(&fpathplot);
	  DeleteSamples(ns,path);
	}
      else
	Error("Can not read the file with the path");

      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);

      DeleteFileName(&fpath);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikplotpath <problem filename> [<path filename>] <xID> <yID> <zID>\n");
     fprintf(stderr,"  where <problem filename> is the description of the problem.\n");
     fprintf(stderr,"        <path filename> is the path to plot. If not given we use <problem filename>_path.sol\n");
     fprintf(stderr,"        <xID> <yID> <zID> are the 3 projection dimensions.\n");
     fprintf(stderr,"          (indices of system variables as those in the _path.sol file from 0)\n");
   }
  return(EXIT_SUCCESS);
}

