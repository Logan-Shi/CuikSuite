#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "chart.h"

#include <stdlib.h>

/** \file cuikerror.c

    \brief Main body of the \ref cuikerror.c "cuikerror" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikerror    [label="cuikerror"  color="#99ff99" shape=ellipse];
      
      problem [label="cuik/world" color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      problem -> cuikerror;
      samples -> cuikerror;
    }
    \enddot
    </center>

     A tool to evaluate the error in a set of solutions
*/


/** 
   \brief Main body of the \ref cuikerror.c "cuikerror" application.

   Main body of the \ref cuikerror.c "cuikerror" application.

   A tool to evaluate the error in a set of solutions.

   Use:<br>
       - \b cuikerror \e problem_name [sol_name]
       .
   where
       - \e problem_name is the name from where to generate the \e .world
       - \e sol_name [optional] The file with the solutions.
       .
 
   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikerror command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{ 
  if (argc>1)
    {
      Tparameters parameters;
      TAtlasBase wcs;

      Tfilename fparam;
      Tfilename fsamples;
      FILE *fs;
      char *solName;

      unsigned int i,nv;
      double *s;

      boolean end;
      int token;

      unsigned int rep;
      unsigned int ns;
      double *fullS;

      unsigned int ms;
      double me,e;
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      /* Read the problem file (cuik or world) */
      CS_WD_INIT(&parameters,arg[1],&wcs);
      nv=CS_WD_GET_NUM_SYSTEM_VARS(&wcs);

      NEW(s,nv,double);
      
      /* Open the the sample file */
      if (argc>2)
	solName=arg[2];
      else
	solName=arg[1];
      rep=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (rep==REP_JOINTS)
	CreateFileName(NULL,solName,NULL,JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,solName,NULL,LINKS_EXT,&fsamples);
      fprintf(stderr,"Reading samples from              : %s\n",GetFileFullName(&fsamples));
      fs=fopen(GetFileFullName(&fsamples),"r");
      if (!fs)
	Error("Could not open the file with the samples");

      end=FALSE;
      ns=1;
      me=0.0;
      do {
	token=fscanf(fs,"%lf",&(s[0]));
	if ((token==EOF)||(token==0))
	  end=TRUE;
	else
	  {
	    for(i=1;i<nv;i++)
	      {
		if (fscanf(fs,"%lf",&(s)[i])==EOF)
		  Error("Not enough values in the sample");
	      }
	    CS_WD_REGENERATE_SOLUTION_POINT(&parameters,s,&fullS,&wcs);
	    e=CS_WD_ERROR_IN_EQUATIONS(&parameters,fullS,&wcs);
	    if (me<e)
	      {
		me=e;
		ms=ns;
	      }
	    fprintf(stderr,"  Error %u: %.16f\n",ns,e);
	    free(fullS);
	    ns++;
	  }
      } while (!end);
      
      fprintf(stderr,"\n  Maximum error %u: %.16f\n",ms,me);
      
      free(s);
      fclose(fs);
      DeleteFileName(&fsamples);

      CS_WD_DELETE(&wcs);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikerror <problem_name> [<sol_file>]\n");
      fprintf(stderr,"    <problem_name> the name from which to define the  .world,\n");
      fprintf(stderr,"    <sol_name> [optional] file with the the solution points\n");
    }
 
  return(EXIT_SUCCESS);
}
