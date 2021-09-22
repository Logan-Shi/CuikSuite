#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "dynamics.h"
#include "samples.h"

#include <stdlib.h>

/** \file cuikME.c

    \brief Main body of the \ref cuikME.c "cuikME" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      param             [label="param"   color="#ff9999" ];
      world             [label="world"   color="#ff9999" ];
      cuikME            [label="cuikME"  color="#99ff99" shape=ellipse];
      path              [label="path"    color="#ff9999" ];

      param -> cuikME;
      world -> cuikME;
      path -> cuikME;
    }
    \enddot
    </center>

    Compute the mechanical (potential/kinetic) energy of the path.
*/

/** 
   \brief Main body of the \ref cuikME.c "cuikME" application.

   Main body of the \ref cuikME.c "cuikME" application.

   Use:
       - \b cuikME \e base_name [\e path_file]
       .
   where
       - \e base_name base name for the parameter, world and path files.
       - \e path_file [optional] the file with the path.
       .

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikME command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  Tfilename ftraj;
  Tfilename fme;

  FILE *fout;

  unsigned int i;
  double t,pe,ke;
  
  /* input path */
  unsigned int nvs,ns;
  double **path;
  double **action;
  unsigned int da;
  double *time;

  TDynamicSpace dynamicSpace;
  TJacobian sJ;
  
  if (argc>=2)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      if (GetParameter(CT_DYNAMICS,&parameters)<0.5)
	Error("CuikME only works on problems with dynamics");
      
      /*Read the world from file*/ 
      CS_WD_INIT(&parameters,arg[1],&world);

      if (ON_CUIKSYSTEM(&world))
	Error("cuikME can not operate on cuiksystems (only on worlds)");
      
      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&ftraj);
      else
	CreateFileName(NULL,arg[1],"_traj",SOL_EXT,&ftraj);

      if (LoadTrajectory(&ftraj,&nvs,&ns,&path,&da,&action,&time))
	{
	  if (argc>2)
	    CreateFileName(NULL,arg[2],NULL,ENERGY_EXT,&fme);
	  else
	    CreateFileName(NULL,arg[1],NULL,ENERGY_EXT,&fme);
	  
	  fprintf(stderr,"Writing energy file               : %s\n",GetFileFullName(&fme));
	  
	  fout=fopen(GetFileFullName(&fme),"w");
	  if (!fout)
	    Error("Output file for energies can not be opened");
	  
	  /* Initialize the dynamic space */
	  CS_WD_GET_SIMP_JACOBIAN(&parameters,&sJ,&world);
	  InitDynamicSpace(&parameters,FALSE,&sJ,&world,&dynamicSpace);
	  
	  t=0;
	  for(i=0;i<ns;i++)
	    {
	      t+=time[i];
	      MechEnergy(&parameters,path[i],&pe,&ke,&dynamicSpace);
	      fprintf(fout,"%f %.12f %.12f %.12f\n",t,pe,ke,pe+ke);
	    }

	  fclose(fout);

	  DeleteJacobian(&sJ);
	  DeleteDynamicSpace(&dynamicSpace);
	  DeleteTrajectory(ns,path,action,time);
	}
      else
	Error("Could not read the input trajectory file");

      
      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);

      DeleteFileName(&fparam);
      DeleteFileName(&ftraj);
      DeleteFileName(&fme);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikME <base filename> [<path file>]\n");
     fprintf(stderr,"  where <base filename> is used for the parameters, world, and path files.\n");
     fprintf(stderr,"        <path file> [optional] is the file with the path.\n");
   }
  return(EXIT_SUCCESS);
}

