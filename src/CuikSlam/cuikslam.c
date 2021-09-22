
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>

/** \file cuikslam.c

    \brief Main body of the \ref cuikslam.c "cuikslam" application.

     A set theoretic approach to SLAM. This is an example of how
     to use position analysis to solve problems apparently far from
     kinematics.
     
     Note that
     - This is a batch approach to SLAM
     - This is not the same technique as the one described in our
       paper ICRA2005 
       <a href="http://www-iri.upc.es/people/porta/Docs/icra05b.pdf">CuikSLAM: a kinematics approach to SLAM</a>.
       Actually this technique is better since it provides global
       consistency.
       However the introduction of the paper can be give an idea
       on how to model SLAM as a kinematic problem and the
       advantages and disadvantages of doing so.
     .

    \todo Implement cuikslam.c. This implies to find a proper way to define the constraints
    between poses and between those and landmarks.

    \sa cuiksystem.h cuiksystem.c 
*/


/**
   \brief Main body of the \ref cuikslam.c "cuikslam" application.

   Main body of the \ref cuikslam.c "cuikslam" application.

   Use:
       - \b cuikslam \e problem_name.slam
       .
   where
       - \e problem_name contains the SLAM information (robot trajectory
       and observed landmarks, if any). 
       .
   The \e .slam extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikslam command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  TCuikSystem cuiksystem;  /* The set of equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */

  Tfilename fslam;
  Tfilename fparam;
  
  
  if (argc>1)
    {
     
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the problem from file*/
      CreateFileName(NULL,arg[1],NULL,SLAM_EXT,&fslam);
      
      InitCuikSystem(&cuiksystem);

      Error("Not implemented yet. Sorry....\n");
      
      DeleteParameters(&parameters);
      DeleteCuikSystem(&cuiksystem);

      DeleteFileName(&fparam);
      DeleteFileName(&fslam);

    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikslam <problem filename>.slam \n");
     fprintf(stderr,"  where <problem filename> contains the slam information\n");
     fprintf(stderr,"    (the '.slam' extension is not required)\n");
   }
  return(EXIT_SUCCESS);
}

