
#include "cuiksystem.h"

#include "parameters.h"
#include "filename.h"
#include "defines.h"
#include "error.h"
#include "box_list.h"
#include "random.h"

#include "cp.h"

#include <stdlib.h>

/** \file cuiksilhouette.c

    \brief Main body of the \ref cuiksilhouette.c "cuiksilhouette" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksilhouette    [label="cuiksilhouette"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      cuik    [label="cuik"   color="#ff9999" ];
      sol     [label="sol"   color="#ff9999" ];

      param -> cuiksilhouette
      cuik -> cuiksilhouette
      cuiksilhouette -> sol;
    }
    \enddot
    </center>

    A tool to generate <a href="http://planning.cs.uiuc.edu/node298.html">Canny's silhouette roadmaps</a> of 
    configuration spaces. Up to now it is only an example of how to use <B>cuik</B> to 
    deal with complex problems, but the current implementation is only effective with 
    moderately complex problems and does not take into account obstacles.

    Note that, as in the original work by Canny, we assume that the input system
    is in generic position and has generic parameters. Otherwise the algorithm will fail.

    Moreover, we assume that the CuikSystem includes only system and dummy variables,
    i.e., no cartesian variables are included.

    To use CuikSilhouette use a small (i.e., 1e-4) \ref CT_SMALL_SIGMA "SMALL_SIGMA"
    and a relatively large (i.e., 1e-1) \ref CT_SIGMA "SIGMA". The first one is
    used to accurately determine critical points and the second one is the resolution
    for the silhouettes (i.e., the paths connecting critical points).

    An example of how to use this application:

       - \ref cuiksilhouette.c "bin/cuiksilhouette" examples/Torus/torus_canny
       - \ref cuikplot3d.c "bin/cuikplot3d" examples/Torus/torus_canny_sil.sol 1 2 3 0 torus_canny_sil.gcl
       - geomview torus_canny_sil.gcl
       .
     
    With this you will obtain the cuiksilhouette of the torus

    <center>
    <img src="../images/Torus/torus_canny.png">
    </center>

    The cuiksilhouette takes care of generating the initial silhouette, the critical points of this
    curve and recursively applies the procedure for the slices at these critical points.
    The total execution time is below 8 seconds in the case of the torus. The final solution
    files includes all the silhouettes and the critical points. To separate them in files
    you can execute:

       - grep "SIL 0" examples/Torus/torus_canny_sil.sol > torus_canny_sl0.sol
       - grep "CP 0" examples/Torus/torus_canny_sil.sol > torus_canny_cp0.sol
       - grep "SIL 1" examples/Torus/torus_canny_sil.sol > torus_canny_sl1.sol
       - grep "SIL 2" examples/Torus/torus_canny_sil.sol > torus_canny_sl2.sol
       - grep "SIL 3" examples/Torus/torus_canny_sil.sol > torus_canny_sl3.sol
       - grep "SIL 4" examples/Torus/torus_canny_sil.sol > torus_canny_sl4.sol
       .
 
    Note that 2 out of the 4 silhouettes of the second level are actually critical
    points (they correspond to the recursion for the critical points on the extremes
    of the torus).

    The plots of the separated files can be visualized executing

       - \ref cuikplot3d.c "bin/cuikplot3d" torus_canny_sl0.sol 1 2 3 0 torus_canny_sl0.gcl
       - \ref cuikplot3d.c "bin/cuikplot3d" torus_canny_cp0.sol 1 2 3 0.05 torus_canny_cp0.gcl
       - \ref cuikplot3d.c "bin/cuikplot3d" torus_canny_sl1.sol 1 2 3 0 torus_canny_sl1.gcl
       - \ref cuikplot3d.c "bin/cuikplot3d" torus_canny_sl2.sol 1 2 3 0 torus_canny_sl2.gcl
       - \ref cuikplot3d.c "bin/cuikplot3d" torus_canny_sl3.sol 1 2 3 0 torus_canny_sl3.gcl
       - \ref cuikplot3d.c "bin/cuikplot3d" torus_canny_sl4.sol 1 2 3 0 torus_canny_sl4.gcl
       - geomview torus_canny_sl0.gcl torus_canny_cp0.gcl torus_canny_sl1.gcl torus_canny_sl2.gcl torus_canny_sl3.gcl torus_canny_sl4.gcl
       .

    Note that we enlarge the critical points to make them visible. After some tunning of the
    colors in geomview you can obtain something like this.

    <center>
    <img src="../images/Torus/torus_canny_color.png">
    </center>


    Note however that this silhouettes computation procedure is only effective for simple problems.

    \sa cuik.c.
*/

/** 
   \brief Main body of the \ref cuiksilhouette.c "cuiksilhouette" application.

   Main body of the \ref cuiksilhouette.c "cuiksilhouette" application.

   Use:
       - \b cuiksilhouette \e problem_name.cuik
       .
   where 
       - \e problem_name contains the kinematic equations 
       .
   The \e .cuik extension is optional.
     
   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksilhouette command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TCuikSystem cuiksystem;  /* The set of equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */
  Tbox binit;
  Tcp *cp;
  Tlist cps;
  unsigned int ncp;
  Tfilename fparam;
  Tfilename fcuik;
  Tfilename fout;
  FILE *f_out;

  if (argc>1)
    { 
      randomReset();
      
      /*Read the parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Init the CuikSystem*/
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);

      /*Start the output file (where the output boxes will be stored)*/
      CreateFileName(NULL,arg[1],"_sil",SOL_EXT,&fout);
      f_out=fopen(GetFileFullName(&fout),"w"); 
      if (!f_out)
	Error("Could not open main output file");

      /*Create a fake critical point with an empty box to bootstratp the process*/
      InitBox(1,NULL,&binit);
      NEW(cp,1,Tcp);
      NewCP(0,&binit,cp);
      DeleteBox(&binit);

      /*Add the first critical point to the list*/
      InitList(sizeof(Tcp *),&cps);
      AddFirstElement(&cp,&cps);
      ncp=0; /*This is a counter of the number of control points processed*/

      /*Process all critical points in the list (when processin new
	critical points are generated) */
      while(!ListEmpty(&cps))
	{
	  ExtractFirst(&cp,&cps);

	  DealWithCP(f_out,ncp,&parameters,&cuiksystem,&cps,cp);
	  ncp++;

	  DeleteCP(cp);
	  free(cp);
	}

      fclose(f_out);

      DeleteFileName(&fout);
      DeleteFileName(&fcuik);
      DeleteFileName(&fparam);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuiksilhouette <problem filename>.cuik \n");
      fprintf(stderr,"  where <problem filename> contains the kinematic equations\n");
      fprintf(stderr,"    (the '.cuik' extension is not required)\n");
    }
  
  return(EXIT_SUCCESS);
}

