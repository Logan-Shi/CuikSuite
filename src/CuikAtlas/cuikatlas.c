#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "atlas.h"
#include "random.h"
#include "geom.h"
#include "samples.h"

#include <stdlib.h>
#include <time.h>

/** \file cuikatlas.c

    \brief Main body of the \ref cuikatlas.c "cuikatlas" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatlas    [label="cuikatlas"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      samples [label="joints/links" color="#ff9999" ];
      world   [label="cuik/world"   color="#ff9999" ];
      atlas   [label="atlas"   color="#ff9999" ];

      param -> cuikatlas
      world -> cuikatlas
      samples -> cuikatlas
      cuikatlas -> atlas;
    }
    \enddot
    </center>

    Defines a discretization of the manifold implicitly defined by a set of
    equations. 

    This is an alternative to \ref cuik.c "cuik" based on 
    higher dimensional continuation methods. The diference is that here we only
    discretize the connected component to which the first sample belongs to.

    Note that this is \b heavely based on the  
    <a href="http://multifario.sourceforge.net/">Multifario</a> by
    <a href="http://www.research.ibm.com/people/h/henderson/">Prof. Henderson</a>.
    We could re-use the code of <a href="http://multifario.sourceforge.net/">Multifario</a>
    but we decided to re-implement it to fully understant the method and to better
    integrate it in \b CuikSuite.

    \sa world.h world.c cuikplan.c
*/


/** 
   \brief Main body of the \ref cuikatlas.c "cuikatlas" application.

   Main body of the \ref cuikatlas.c "cuikatlas" application.

   Use:
       - \b cuikatlas \e problem_name.cuik/worlds
       .
   where
       - \e problem_name contains the problem definition. The extension is not necessary. We first
         check if a file with .cuik extension exists. Othersiwe, we try to read a .world file.
	 The name is also used to read the sample file 
         including the origin/goal poses.
       .
   The \e .world extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikatlas command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */

  Tfilename fparam;
  Tfilename fatlas;
  
  double *s1;              /* One point on the manifold (values only for the system variables). */

  Tatlas atlas;
  Tstatistics st;

  unsigned int ri;

  if (argc>1)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);
 
      /* Read start sample */
      ReadOneSample(&parameters,arg[1],CS_WD_GET_NUM_SYSTEM_VARS(&world),&s1);

      /* Random seed initialization */
      ri=(unsigned int)time(NULL);
      //ri=1424688164;
      randomSet(ri);
     
      fprintf(stderr,"Random seed                       : %u\n",ri);
      
      /* The statistics here are just used to compute execution time.
         In some cases, we use parallel atlas construction. Then
         CPU time accumulates the time for all the used CPUs, which
         is significantly larger than the real execution time. 
         Wall clock time has the problem of also accumulating the
         time of concurrent processes. */
      #ifdef _OPENMP
        InitStatistics(2,0,&st); /* just to force wall clock time */
      #else
        InitStatistics(0,0,&st); /* use real cpu time */
      #endif

      /* Define the atlas */
      BuildAtlasFromPoint(&parameters,s1,FALSE,&world,&atlas);

      fprintf(stderr,"Atlas completed.\n");
      fprintf(stderr,"Elapsed time %f\n", GetElapsedTime(&st));
      
      DeleteStatistics(&st);

      /* Save the results */
      CreateFileName(NULL,arg[1],NULL,ATLAS_EXT,&fatlas);
      fprintf(stderr,"Writing atlas to                  : %s\n",GetFileFullName(&fatlas));
      SaveAtlas(&parameters,&fatlas,&atlas);
      DeleteAtlas(&atlas);
      DeleteFileName(&fatlas);

      /* Release memory */
      free(s1);

      DeleteParameters(&parameters);

      CS_WD_DELETE(&world);

      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikatlas <problem filename>.%s \n",CS_WD_EXT);
     fprintf(stderr,"  where <problem filename> the equations/world description\n");
     fprintf(stderr,"    (the '.%s' extension is not required)\n",CS_WD_EXT);
   }
  return(EXIT_SUCCESS);
}

