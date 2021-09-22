#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "chart.h"

#include <stdlib.h>

/** \file cuiksamples2sols.c

    \brief Main body of the \ref cuiksamples2sols.c "cuiksamples2sols" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksamples2sols    [label="cuiksamples2sols"  color="#99ff99" shape=ellipse];
      
      problem [label="cuik/world" color="#ff9999" ];
      sol   [label="sol" color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      problem -> cuiksamples2sols;
      samples -> cuiksamples2sols;
      cuiksamples2sols -> sol;
    }
    \enddot
    </center>

     A tool to transform samples to solutions. Solutions are given
     with ranges for each system variable while samples are given
     as points. This application simply reads the list of
     samples and defines a small box around each sample. 
     The result is stored in a file with extension "_samples.sols".

     The purpose of this application is to define boxes from samples. Then, this
     boxes can be used by \ref cuiknewton.c "cuiknewton" to define a new sample for each box.
     The Newton process reduces the possible error in the sample and avoids
     problems during planning.
*/


/** 
   \brief Main body of the \ref cuiksamples2sols.c "cuiksamples2sols" application.

   Main body of the \ref cuiksamples2sols.c "cuiksamples2sols" application.

   A tool to transform samples to solutions. Solutions are given
   with ranges for each system variable while samples are given
   as points. This application simply reads the list of
   samles and  stores a small box around each one of them.

   Use:<br>
       - \b cuiksamples2sols \e problem_name \e sol_file
       .
   where
       - \e problem_name is the name from where to generate the \e .world
       - \e sol_file [optional] If not given the output is stored in \e problem_name_sample.sols
       .
 
   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksamples2sols command itself and its arguments).
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
      Tfilename fboxes;
      FILE *fs,*fb;

      boolean *sv;
      unsigned int i,nv,nvs;
      double s;
      Tbox b;
      Tinterval r;

      double epsilon;

      boolean end;
      int token;

      unsigned int rep;

      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      epsilon=GetParameter(CT_EPSILON,&parameters);

      /* Read the problem file (cuik or world) */
      InitCSWDFromFile(&parameters,arg[1],&wcs);
      nv=CS_WD_GET_SYSTEM_VARS(&sv,&wcs);
   
      nvs=0;
      for(i=0;i<nv;i++)
	{
	  if (sv[i])
	    nvs++;
	}
      free(sv);
      
      /* Open the the sample file */
      rep=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (rep==REP_JOINTS)
	CreateFileName(NULL,arg[1],NULL,JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,arg[1],NULL,LINKS_EXT,&fsamples);
      fprintf(stderr,"Reading samples from              : %s\n",GetFileFullName(&fsamples));
      fs=fopen(GetFileFullName(&fsamples),"r");
      if (!fs)
	Error("Could not open the file with the samples");

      /* Create the box file */
      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fboxes);
      else
	CreateFileName(NULL,arg[1],"_samples",SOL_EXT,&fboxes);
      fprintf(stderr,"Writing solutions to              : %s\n",GetFileFullName(&fboxes));
      fb=fopen(GetFileFullName(&fboxes),"w");
      if (!fb)
	Error("Could no open the file to store the solutions");

      InitBox(nvs,NULL,&b);

      end=FALSE;
      do {
	token=fscanf(fs,"%lf",&s);
	if ((token==EOF)||(token==0))
	  end=TRUE;
	else
	  {
	    NewInterval(s-epsilon,s+epsilon,&r);
	    SetBoxInterval(0,&r,&b);

	    for(i=1;i<nvs;i++)
	      {
		if (fscanf(fs,"%lf",&s)==EOF)
		  Error("Not enough values in the sample");

		NewInterval(s-epsilon,s+epsilon,&r);
		SetBoxInterval(i,&r,&b);	
	      }
	    PrintBox(fb,&b);
	  }
      } while (!end);

      DeleteBox(&b);

      fclose(fs);
      DeleteFileName(&fsamples);

      fclose(fb);
      DeleteFileName(&fboxes);

      CS_WD_DELETE(&wcs);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuiksamples2sols <problem_name> [<sol_file>]\n");
      fprintf(stderr,"    <problem_name> the name from which to define the  .world,\n");
      fprintf(stderr,"    <sol_name> [optional] file where to store the solutions\n");
      fprintf(stderr,"       if not given they are stored in <problem_name>_samples.sols\n");
    }
 
  return(EXIT_SUCCESS);
}
