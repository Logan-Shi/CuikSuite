
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikplotatlas.c

    \brief Main body of the \ref cuikplotatlas.c "cuikplotatlas" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplotatlas    [label="cuikplotatlas"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      cost    [label="cost"    color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuikplotatlas;
      world -> cuikplotatlas;
      atlas -> cuikplotatlas;
      cost -> cuikplotatlas;
      cuikplotatlas -> gcl;
    }
    \enddot
    </center>

    Plots a 3d projection of an atlas generated with cuikatlas.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuikplotatlas.c "cuikplotatlas" application.

   Main body of the \ref cuikplotatlas.c "cuikplotatlas" application.

   Use:
       - \b cuikplotatlas \e problem_name \e cost_file \e xID \e yID \e zID
       .
   where
       - \e problem_name is used to load the .world and .atlas files necessary
         to generate the .cgl plot.
       - \e cost_file [Optional] A file with one cost for each one of the charts in
                      the atlas. This is used when we want a colored atlas.
       - \e xID \e yID \e zID are the identifier of the variables on which to project.
         These are indices of system variables, numbered consecutively and without 
         considering dummy ones (these are the ones stored, for instance, in the
	 solution path files).  
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikplotatlas command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Tatlas atlas;            /* The atlas to plot. */

  unsigned int nx,ny,nz;
  unsigned int xID,yID,zID;
  FILE *fc;
  unsigned int i,nv,nvs;  
  boolean *systemVars;

  Tfilename fparam;
  Tfilename fplot;
  Tfilename fatlas;
  Tfilename fcost;
  
  
  if ((argc==5)||(argc==6))
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
      if (argc>5)
	{
	  CreateFileName(NULL,arg[2],NULL,COST_EXT,&fcost);
	  fprintf(stderr,"Reading cost from                 : %s\n",GetFileFullName(&fcost));
	  fc=fopen(GetFileFullName(&fcost),"r");
	  if (!fc)
	    Error("Can not open the cost file");

	  nx=atoi(arg[3]);
	  ny=atoi(arg[4]);
	  nz=atoi(arg[5]);
	}
      else
	{
	  fc=NULL;
	  nx=atoi(arg[2]);
	  ny=atoi(arg[3]);
	  nz=atoi(arg[4]);
	}

      if (nx>=nv)
	Error("First index out of range");
      if (ny>=nv)
	Error("Second index out of range");
      if (nz>=nv)
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

      /*Read the atlas from file*/
      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Reading atlas from                : %s\n",GetFileFullName(&fatlas));
      LoadAtlas(&parameters,&fatlas,&world,&atlas);
      
      /* Create the plot */
      CreateFileName(NULL,arg[1],"_atlas",PLOT3D_EXT,&fplot);
      fprintf(stderr,"Generating atlas plot to          : %s\n",GetFileFullName(&fplot));

      PlotAtlas(GetFileFullName(&fplot),argc,arg,&parameters,fc,xID,yID,zID,&atlas); 

      if (fc!=NULL)
	fclose(fc);

      DeleteParameters(&parameters);

      free(systemVars);

      CS_WD_DELETE(&world);

      DeleteAtlas(&atlas);

      DeleteFileName(&fplot);
      DeleteFileName(&fatlas);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikplotatlas <problem filename> <cost file> <xID> <yID> <zID>\n");
     fprintf(stderr,"  where <problem filename> is the atlas to plot.\n");
     fprintf(stderr,"        <cost file> [optional] file with associated costs for each chart.\n");
     fprintf(stderr,"        <xID> <yID> <zID> are the 3 projection dimensions.\n");
     fprintf(stderr,"          (indices of system variables as those in the _path.sol file from 0)\n");
     
   }
  return(EXIT_SUCCESS);
}

