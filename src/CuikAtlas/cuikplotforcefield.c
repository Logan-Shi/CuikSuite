
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikplotforcefield.c

    \brief Main body of the \ref cuikplotforcefield.c "cuikplotforcefield" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplotforcefield    [label="cuikplotforcefield"  color="#99ff99" shape=ellipse URL="\ref cuikplotforcefield.c"];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"   color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuikplotforcefield;
      world -> cuikplotforcefield;
      sol -> cuikplotforcefield;
      cuikplotforcefield -> gcl;
    }
    \enddot
    </center>

    Plots a 3d projection of the force field over a set of solution points (i.e., the
    center of the charts in an atlas, the points along a solution path, etc).

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikplotforcefield.c "cuikplotforcefield" application.

   Main body of the \ref cuikplotforcefield.c "cuikplotforcefield" application.

   Use:
       - \b cuikplotforcefield \e problem_name [\e sol_name] \e xID \e yID \e zID
       .
   where
       - \e problem_name is used to load the .world and .atlas files necessary
         to generate the .cgl plot.
       - \e sol_name [optional] The file with the solution points. If not given
         the solution file is assumed to be \e problem_name.sol .
       - \e xID \e yID \e zID are the identifier of the variables on which to project.
         These are indices of system variables, numbered consecutively and without 
         considering dummy ones (these are the ones stored, for instance, in the
	 solution path files).  
       .
   The \e problem_name and \e solution_name (if given) are without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikplotforcefield command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  Tworld world;            /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  unsigned int nx,ny,nz;

  unsigned int ns,nvs;
  double **sols;

  Tfilename fparam;
  Tfilename fsols;

  //boolean smooth;
  
  if (argc>=5)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/ 
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);
          
      /* Validate the input projection dimensions */
      nvs=GetWorldNumSystemVariables(&world);
      
      if (argc>5)
	{
	  CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      
	  nx=atoi(arg[3]);
	  ny=atoi(arg[4]);
	  nz=atoi(arg[5]);
	}
      else
	{
	  CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsols);
      
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
      
      fprintf(stderr,"Projecting on variables           : ");
      PRINT_VARIABLE_NAME(stderr,GetWorldSystemVarName(nx,&world));fprintf(stderr,",");
      PRINT_VARIABLE_NAME(stderr,GetWorldSystemVarName(ny,&world));fprintf(stderr,",");
      PRINT_VARIABLE_NAME(stderr,GetWorldSystemVarName(nz,&world));fprintf(stderr,"\n");

      /* Load the points */
      if (LoadSamples(&fsols,&nvs,&ns,&sols))
	{
	  /*If the solutions were actually loaded*/
	  Tfilename fffplot;
	  Tplot3d p3d;

	  if (argc>5)
	    CreateFileName(NULL,arg[2],"_ff",PLOT3D_EXT,&fffplot);
	  else
	    CreateFileName(NULL,arg[1],"_ff",PLOT3D_EXT,&fffplot);

	  /* and plot the force field at the ponts */
	  fprintf(stderr,"Generating force field plot to    : %s\n",GetFileFullName(&fffplot));

	  InitPlot3d(GetFileFullName(&fffplot),FALSE,argc,arg,&p3d);

	  PlotForceField(&parameters,&p3d,nx,ny,nz,&world,ns,sols);

	  ClosePlot3d(FALSE,&p3d);
	  
	  DeleteFileName(&fffplot);
	  DeleteSamples(ns,sols);
	}
      else
	Error("Can not read the file with the solution points");

      DeleteParameters(&parameters);
      DeleteWorld(&world);

      DeleteFileName(&fsols);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikplotforcefield <problem filename> [<sol filename>.sol] <xID> <yID> <zID>\n");
     fprintf(stderr,"  where <problem filename> is the description of the problem.\n");
     fprintf(stderr,"        <sol filename> is the file with the solution points.\n");
     fprintf(stderr,"                        If not given we use <problem filename>.sol\n");
     fprintf(stderr,"        <xID> <yID> <zID> are the 3 projection dimensions.\n");
     fprintf(stderr,"          (indices of system variables as those in the _path.sol file from 0)\n");
   }
  return(EXIT_SUCCESS);
}

