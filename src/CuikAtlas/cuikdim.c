#include "filename.h"
#include "error.h"
#include "parameters.h"
#include "atlas.h"
#include "samples.h"


#include <stdio.h>
#include <math.h>

/** \file cuikdim.c

    \brief Main body of the \ref cuikdim.c "cuikdim" aplication.
   
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikdim    [label="cuikdim"  color="#99ff99" shape=ellipse];

      param [label="param" color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world [label="cuik/world" color="#ff9999" ];

      param -> cuikdim;
      samples -> cuikdim;
      world -> cuikdim;
    }
    \enddot
    </center>

     A tool compute the dimension of the manifold implicitly defined
     by a set of equations (or encoded in a world file). To
     compute this dimension we assume that the configuration given
     in the joints/links file is a regular configuration.

     The dimension of the implicit manifold is know typically a priori 
     (and set in the \ref CT_N_DOF "N_DOF" parameter)
     In many cases, however the presence of redundant constraints or
     special parameters (symmetries, etc) make it hard to figure
     out this dimension. To address this problems we provide
     this small application that numerically determines the
     dimension of the implicitly defined manifold. 

     Note that the dimension is computed up to the given numerical
     accuracy (parameter \ref CT_EPSILON "EPSILON").

     Additonally note that the tools relying on an atlas can automatially
     determine the dimension of the implicit manifold. This is
     achieved setting \ref CT_N_DOF "N_DOF" to 0.
*/


/** 
    \brief Main body of the \ref cuikdim.c "cuikdim" application.
   
    Main body of the \ref cuikdim.c "cuikdim" application.

    A tool compute the dimension of the manifold implicitly defined
    by a set of equations (or encoded in a world file). To
    compute this dimension we assume that the configuration given
    in the joints/links file is a regular configuration.

    The dimension of the implicit manifold is know typically a priori 
    (and set in the \ref CT_N_DOF "N_DOF" parameter)
    In many cases, however the presence of redundant constraints or
    special parameters (symmetries, etc) make it hard to figure
    out this dimension. To address this problems we provide
    this small application that numerically determines the
    dimension of the implicitly defined manifold. 

    Note that the dimension is computed up to the given numerical
    accuracy (parameter \ref CT_EPSILON "EPSILON").

    Additonally note that the tools relying on an atlas can automatially
    determine the dimension of the implicit manifold. This is
    achieved setting \ref CT_N_DOF "N_DOF" to 0.

    Use:<br>
       - \b cuikdim \e problem_name
       .
    where
       - \e problem_name is the file with the molecuar information (typically a pdb).
       .
   The file extensions are not required.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikdim command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;
  TAtlasBase world;
  Tfilename fparam;
  double *configuration;
  unsigned int k;

  if (argc>1)
    { 
      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      /* Read the world/cuik from file */
      CS_WD_INIT(&parameters,arg[1],&world);

      /* Read start sample */
      ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&configuration);

      /* Estimate the dimesion of the solution manifold*/
      k=CS_WD_MANIFOLD_DIMENSION(&parameters,configuration,&world);
      fprintf(stderr,"N_DOF = %u\n",k);

      free(configuration);
      DeleteFileName(&fparam);
      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikdim <problem_name>  \n");
      fprintf(stderr,"    <problem_name> the input problem.\n");
    }

  return(EXIT_SUCCESS);
}
