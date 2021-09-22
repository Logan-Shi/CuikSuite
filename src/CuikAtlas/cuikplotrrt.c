
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "rrt.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikplotrrt.c

    \brief Main body of the \ref cuikplotrrt.c "cuikplotrrt" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplotrrt    [label="cuikplotrrt"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      rrt     [label="rrt"   color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      param -> cuikplotrrt;
      world -> cuikplotrrt;
      rrt -> cuikplotrrt;
      cuikplotrrt -> gcl;
    }
    \enddot
    </center>

    Plots a 3d projection of an rrt generated with cuikrrt.

    \sa cuikrrt.c
*/

/** 
   \brief Main body of the \ref cuikplotrrt.c "cuikplotrrt" application.

   Main body of the \ref cuikplotrrt.c "cuikplotrrt" application.

   Use:
       - \b cuikplotrrt \e problem_name \e xID \e yID \e zID
       .
   where
       - \e problem_name is used to load the .world and .rrt files necessary
         to generate the .cgl plot.
       - \e xID \e yID \e zID are the identifier of the variables on which to project.
         These are indices of system variables, numbered consecutively and without 
         considering dummy ones (these are the ones stored, for instance, in the
	 solution path files).  
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikplotrrt command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Trrt rrt;                /* The rrt to plot. */

  unsigned int nx,ny,nz;
  unsigned int xID,yID,zID;
  unsigned int i,nv,nvs;  
  boolean *systemVars;

  double *s1,*s2;
  double *p1,*p2;
  
  Tfilename fparam;
  Tfilename fplot;
  Tfilename frrt;
  
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
     
      /* Read the RRT */
      CreateFileName(NULL,arg[1],NULL,RRT_EXT,&frrt);
      fprintf(stderr,"Reading rrt from                  : %s\n",GetFileFullName(&frrt));
      LoadRRT(&parameters,&frrt,&world,&rrt);

      {
	Tfilename kk;
	
	CreateFileName(NULL,"kk.rrt",NULL,RRT_EXT,&kk);
	
	SaveRRT(&kk,&rrt);
      }
      
      /* Create the plot */
      CreateFileName(NULL,arg[1],"_rrt",PLOT3D_EXT,&fplot);
      fprintf(stderr,"Generating rrt plot to            : %s\n",GetFileFullName(&fplot));

      PlotRRT(GetFileFullName(&fplot),argc,arg,&parameters,xID,yID,zID,p1,p2,&rrt);

      /* Release memory */
      free(s1); free(p1);
      if (s2!=NULL) {free(s2);free(p2);}
      
      DeleteParameters(&parameters);

      free(systemVars);

      CS_WD_DELETE(&world);

      DeleteRRT(&rrt);

      DeleteFileName(&fplot);
      DeleteFileName(&frrt);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikplotrrt <problem filename> <xID> <yID> <zID>\n");
     fprintf(stderr,"  where <problem filename> is the rrt to plot\n");
     fprintf(stderr,"        <xID> <yID> <zID> are the 3 projection dimensions\n");
     
   }
  return(EXIT_SUCCESS);
}

