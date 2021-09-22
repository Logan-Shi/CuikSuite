#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "cuiksystem.h"

#include <stdlib.h>

/** \file cuiksample.c

    \brief Main body of the \ref cuiksample.c "cuiksample" application.

    A utility to generate random samples taking as a departing
    point a <em>cuik</em> file.

    \sa cuiksampleworld.c cuikplan.c
*/

/** 
   \brief Main body of the \ref cuiksample.c "cuiksample" application.

   Main body of the \ref cuiksample.c "cuiksample" application.

   Use:
      - \b cuiksample \e problem_name.cuik \e num_samples
      .
   where 
      - \e problem_name contains the kinematic equations. 
      - \e num_samples Number of samples to generate. 
      .
   The \em .cuik extension is optional.

   The number of samples to generate as well as the degrees of freedom of the mechanism
   are taken from the corresponding paremeter file.

   If the number of degrees of freedom set in the parameter file is set to 0, we try to
   determine the rigth value from the equation structure (number of variables minus
   number of equations). However, this
   estimated value can be wrong and, therefore, it is better to set it correctly in the
   parameter file.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksample command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  if (argc>2)
    {
      Tparameters parameters;
      TCuikSystem cuiksystem;

      Tfilename fcuik;
      Tfilename fparam;

      unsigned int ndof,nsamples;
      unsigned int ri;

      ri=(unsigned int)time(NULL);
      //ri=1405333052;
      randomSet(ri);
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      fprintf(stderr,"Reading parameters from           : %s\n",GetFileFullName(&fparam));
      
      /* Read the problem file */
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);
      fprintf(stderr,"Reading cuik file                 : %s\n",GetFileFullName(&fcuik));
      
      ndof=(unsigned int)GetParameter(CT_N_DOF,&parameters);
      if (ndof==0)
	ndof=NO_UINT;

      nsamples=atoi(arg[2]);

      SampleCuikSystem(&parameters,arg[1],NULL,nsamples,NO_UINT,ndof,&cuiksystem);

      DeleteCuikSystem(&cuiksystem);
      DeleteParameters(&parameters);

      DeleteFileName(&fcuik);
      DeleteFileName(&fparam);
    }
  else
    { 
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuiksample <problem filename>.cuik <num samples>\n");
      fprintf(stderr,"  where <problem filename> contains the kinematic equations\n");
      fprintf(stderr,"        <num samples> the number of samples to generate\n");
      fprintf(stderr,"    (the '.cuik' extension is not required)\n");
    }

  return(EXIT_SUCCESS);
}
