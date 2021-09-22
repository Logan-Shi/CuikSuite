
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"

#include <stdlib.h>

/** \file cuiktriangulateatlas.c

    \brief Main body of the \ref cuiktriangulateatlas.c "cuiktriangulateatlas" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiktriangulateatlas    [label="cuiktriangulateatlas"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];
      cost    [label="cost"    color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuiktriangulateatlas;
      world -> cuiktriangulateatlas;
      atlas -> cuiktriangulateatlas;
      cost -> cuiktriangulateatlas;
      cuiktriangulateatlas -> gcl;
    }
    \enddot
    </center>

    Plots a 3d projection of an atlas generated with cuikatlas.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuiktriangulateatlas.c "cuiktriangulateatlas" application.

   Main body of the \ref cuiktriangulateatlas.c "cuiktriangulateatlas" application.

   Use:
       - \b cuiktriangulateatlas \e problem_name \e cost_file \e xID \e yID \e zID
       .
   where
       - \e problem_name is used to load the .world and .atlas files necessary
         to generate the .cgl plot.
       - \e cost_file [Optional] A file with one cost for each one of the charts in
                      the atlas. This is used when we want a colored atlas.
       - \e xID \e yID \e zID are the identifier of the variables on which to project.
         These are indices of system variables, numbered consecutively from 0 and without 
         considering dummy ones.  
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiktriangulateatlas command itself and its arguments). 
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
  unsigned int i,s,nv,nvs;  
  boolean *systemVars;

  Tfilename fparam;
  Tfilename fplot;  
  Tfilename fatlas;
  Tfilename fcost;
  
  
  if (argc>4)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);
      nv=CS_WD_GET_SYSTEM_VARS(&systemVars,&world);      

      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Reading atlas from                : %s\n",GetFileFullName(&fatlas));
      LoadAtlas(&parameters,&fatlas,&world,&atlas);
      
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
      nvs=0;
      s=0;
      for(i=0;i<nv;i++)
	{
	  if (systemVars[i])
	    {
	      /* Transform index from system variables only to
	         all variables (in the original system in both cases!!) */
	      if (nx==nvs) {xID=i; s++;}
	      if (ny==nvs) {yID=i; s++;}
	      if (nz==nvs) {zID=i; s++;}
	      nvs++;
	    }
	}

      if (s!=3)
	Error("Projection dimensions are beyond the ambient space dimensionality");

      CreateFileName(NULL,arg[1],"_atlas_triang",PLOT3D_EXT,&fplot);
      fprintf(stderr,"Generating triangulation to       : %s\n",GetFileFullName(&fplot));

      TriangulateAtlas(GetFileFullName(&fplot),argc,arg,&parameters,fc,xID,yID,zID,&atlas);
      
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
     fprintf(stderr,"      cuiktriangulateatlas <problem filename> <cost file> <xID> <yID> <zID>\n");
     fprintf(stderr,"  where <problem filename> is the atlas to plot.\n");
     fprintf(stderr,"        <cost file> [optional] file with associated costs for each chart.\n");
     fprintf(stderr,"        <xID> <yID> <zID> are the 3 projection dimensions.\n");
     fprintf(stderr,"          (indices of system variables numbered from 0)\n");
     
   }
  return(EXIT_SUCCESS);
}

