
#include "world.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"
#include "rrt.h"

#include <stdlib.h>

/** \file cuikrrterror.c

    \brief Main body of the \ref cuikrrterror.c "cuikrrterror" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikrrtnodes    [label="cuikrrterror"  color="#99ff99" shape=ellipse];
      
      world   [label="world" color="#ff9999" ];
      rrt     [label="rrt" color="#ff9999" ];
      param   [label="param" color="#ff9999" ];
      sols    [label="sol" color="#ff9999" ];

      world -> cuikrrterror;
      rrt -> cuikrrterror;
      param -> cuikrrterror;
      cuikrrterror -> sols;
    }
    \enddot
    </center>

    Extracts the error in the nodes of a RRT.

    \sa cuikatlasrrt.c cuikcbirrt.c cuiktrrt.c cuikccrrt.c cuikcctrrt.c cuikatlasrrtstar.c cuikbiotrrt.c
*/

/** 
   \brief Main body of the \ref cuikrrterror.c "cuikrrterror" application.

   Main body of the \ref cuikrrterror.c "cuikrrterror" application.

   Use:
       - \b cuikrrterror \e problem_name.world [rrt_name.rrt]
       .
   where
       - \e problem_name is used to load .atlas file from where
         to extract the centres.
       - [rrt_name] optional. It uses the rrt struct to measure the error in the nodes.
       .
   The \e problem_name is without extension (if given it is removed).

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikrrtnodes command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TAtlasBase world;        /* The set of mechanism and obstacles.  */
  Tparameters parameters;  /* Parameters used in the Cuik process. */
  Trrt rrt;                /* The rrt to process. */

  Tfilename fparam;
  Tfilename frrt;
  
  double *s;
  double me,e,time;
  char *rrtName;
  unsigned int nodes,ms,i;

  if (argc>1)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      /*Read the world/cuik from file*/
      CS_WD_INIT(&parameters,arg[1],&world);
      
      if (argc>2)
	rrtName=arg[2];
      else
	rrtName=arg[1];
	    
      CreateFileName(NULL,rrtName,NULL,RRT_EXT,&frrt);
      fprintf(stderr,"Reading rrt from                  : %s\n",GetFileFullName(&frrt));

      LoadRRT(&parameters,&frrt,&world,&rrt);

      nodes=GetRRTNumNodes(&rrt);
      fprintf(stderr,"Num of rrt nodes: %u\n",nodes);

      me=0.0;
      for (i=0;i<nodes;i++)
	{
	  s=GetRRTNode(i,&rrt);

	  time = GetRRTTimeFromRoot(i,&rrt);

	    

	  e=CS_WD_ERROR_IN_EQUATIONS(&parameters,s,&world);

	  // #if (_DEBUG>2)
	  //  fprintf(stderr,"sample id: %u\n",i);
	  fprintf(stderr,"%.16f %f\n",e,time);
	    // #endif
    
	  if (me<e)
	    {
	      me=e;
	      ms=i;
	    }
	}

      fprintf(stderr,"Maximum error %u: %.16f\n",ms,me);
      
      DeleteParameters(&parameters);

      CS_WD_DELETE(&world);
      DeleteRRT(&rrt);

      DeleteFileName(&frrt);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikrrterror <problem filename> [<rrt_file>]\n");
     fprintf(stderr,"    <problem_name> the name from which to define the  .world,\n");
     fprintf(stderr,"    <rrt_name> [optional] file with the the rrt\n");
   }
  
  return(EXIT_SUCCESS);
}

