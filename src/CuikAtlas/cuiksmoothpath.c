
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "samples.h"
#include "random.h"

#include <stdlib.h>

/** \file cuiksmoothpath.c

    \brief Main body of the \ref cuiksmoothpath.c "cuiksmoothpath" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksmoothpath    [label="cuiksmoothpath"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      path    [label="path"    color="#ff9999" ];
      spath    [label="spath"    color="#ff9999" ];

      param -> cuiksmoothpath;
      world -> cuiksmoothpath;
      path -> cuiksmoothpath;
      cuiksmoothpath -> spath;
    }
    \enddot
    </center>

    Local optimization of a path. Reduces measure over a path connecting two samples.
    In general the mesasure is the path length, but in \ref GradientSmooth "EFFORT"
    mode where the control effor is minimized.
    The control effort is only relevant in structures with an associated potential energy
    (i.e., in tensegrity structures). Otherwise, the control effort is (almost) the 
    same as the path lenght.

    \sa cuikatlas.c
*/

/** 
   \brief Main body of the \ref cuiksmoothpath.c "cuiksmoothpath" application.

   Main body of the \ref cuiksmoothpath.c "cuiksmoothpath" application.

   Use:
       - \b cuiksmoothpath \e problem_name \e path_name \e mode \e iterations \e parallel
       .
   where
       - \e problem_name Name of the file describing the problem.
       - \e path_name Name of the path to smooth.
       - \e mode [optional] is the algorithm to use: \ref RandomSmooth "RANDOM", \ref GradientSmooth "GRADIENT", 
               \ref ShortcutSmooth "SHORTCUT", or \ref GradientSmooth "EFFORT".
               The default is \ref ShortcutSmooth "SHORTCUT" (is faster but might return sub-optimal paths).
       - \e iterations [optional] is the maximum number of iterations.
               The default is 2 for RANDOM smoothing and 1000 for GRADIENT smoothing.
	       For the RANDOM method this number is scaled by the number of steps in the path.
               The GRADIENT method might stop earlier if the gradient becomes 0.
       - \e parallel [optional] 1 if the smooth has to be exectued in parallel and 0 for serial execution.
               The default is 0 for RANDOM and SHORTCUT and 1 for GRADIENT.
       .
   The \e problem_name is without any extension.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksmoothpath command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/

int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  Tfilename fpath;

  char *suffix;
  boolean defaultPathName;

  /* input path */
  unsigned int nvs,ns;
  double **path;

  /* smoothed path */
  unsigned int sns;
  double **spath;
  unsigned int mode;
  boolean parallel;
  unsigned int numIterations;

  unsigned int ri;
  time_t t;
  
  if (argc>=2)
    {
      /* if only one parameter given, assume default values
         even for the path name */
      defaultPathName=(argc==2);
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));

      /*Read the world from file*/ 
      CS_WD_INIT(&parameters,arg[1],&world);

      t=time(NULL);  /* Get the time at which input files have been read */
      ri=(unsigned int)t;
      //ri=1405498615;
      randomSet(ri);
      fprintf(stderr,"Random seed                       : %u\n",ri);

      mode=SMOOTH_SHORTCUT;
      if (defaultPathName)
	suffix="_path_s";
      else
	suffix="_s";
      if (argc>=4)
	{
	  /* Select the smoothing mode */
	  switch(arg[3][0])
	    {
	    case 'G':
	    case 'g':
	      mode=SMOOTH_GRADIENT;
	      if (defaultPathName)
		suffix="_path_g";
	      else
		suffix="_g";
	      break;
	    case 'R':
	    case 'r':
	      mode=SMOOTH_RANDOM;
	      if (defaultPathName)
		suffix="_path_r";
	      else
		suffix="_r";
	      break;
	    case 'S':
	    case 's':
	      mode=SMOOTH_SHORTCUT;
	      if (defaultPathName)
		suffix="_path_s";
	      else
		suffix="_s";
	      break;
	    case 'E':
	    case 'e':
	      mode=SMOOTH_EFFORT;
	      if (defaultPathName)
		suffix="_path_e";
	      else
		suffix="_e";
	      break;
	    case 'D':
	    case 'd':
	      mode=SMOOTH_DISPERSION;
	      if (defaultPathName)
		suffix="_path_d";
	      else
		suffix="_d";
	      break;
	    default:
	      Error("Undefined smooth method");
	    }
	}
      
      if (argc>=5)
	numIterations=atoi(arg[4]);
      else
	numIterations=(mode==SMOOTH_RANDOM? 2 : 1000);
      
      if (argc>=6)
	parallel=atoi(arg[5]);
      else
	parallel=(((mode==SMOOTH_GRADIENT)||(mode==SMOOTH_EFFORT)||(mode==SMOOTH_DISPERSION))? TRUE : FALSE);

      if (defaultPathName)
	CreateFileName(NULL,arg[1],"_path",SOL_EXT,&fpath);
      else
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fpath);
	
      if (LoadSamples(&fpath,&nvs,&ns,&path))
	{
	  SmoothSamples(&parameters,parallel,mode,numIterations,ns,path,&sns,&spath,&world);

	  if (defaultPathName)
	    SaveSamples(arg[1],suffix,nvs,sns,spath);
	  else
	    SaveSamples(arg[2],suffix,nvs,sns,spath);

	  DeleteSamples(ns,path);
	  DeleteSamples(sns,spath);
	}
      else
	Error("Could not read the input path file");

      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);

      DeleteFileName(&fparam);
      DeleteFileName(&fpath);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuiksmoothpath <problem name> <path name> [<mode> <iterations> <parallel>]\n");
     fprintf(stderr,"  where <problem name> is the file describing the problem.\n");
     fprintf(stderr,"        <path name> is the file with the path to smooth.\n");
     fprintf(stderr,"        <mode> [optional] is the algorithm to use: RANDOM, GRADIENT, SHORTCUT or EFFORT.\n");
     fprintf(stderr,"               The defatul is SHORTCUT (faster but might return suboptimal paths).\n");
     fprintf(stderr,"        <iterations> [optional] is the maximum number of iterations.\n");
     fprintf(stderr,"                     The default is 2 for RANDOM smoothing and 1000 for GRADIENT smoothing.\n");
     fprintf(stderr,"                     For the RANDOM method this number is scaled by the number of steps in the path.\n");
     fprintf(stderr,"                     The GRADIENT method might stop earlier if the gradient becomes 0.\n");
     fprintf(stderr,"        <parallel> [optional] 1 if the smooth has to be exectued in parallel and 0 for serial execution.\n");
     fprintf(stderr,"                   The default is 0 for RANDOM and SHORTCUT and 1 for GRADIENT.\n");
     fprintf(stderr,"\n");
     fprintf(stderr," When called as:\n");
     fprintf(stderr,"      cuiksmoothpath <problem name>\n");
     fprintf(stderr," The default parameters and the default path name are assumed.\n");
     
   }
  return(EXIT_SUCCESS);
}

