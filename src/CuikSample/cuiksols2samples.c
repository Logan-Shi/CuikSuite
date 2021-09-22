#include "filename.h"
#include "box_list.h"
#include "sample.h"
#include "error.h"
#include "defines.h"
#include "parameters.h"
#include "link.h"


#include <stdio.h>

/** \file cuiksols2samples.c

    \brief Main body of the \ref cuiksols2samples.c "cuiksols2samples" application.
   
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksols2samples    [label="cuiksols2samples"  color="#99ff99" shape=ellipse];
      
      sol   [label="sol" color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      sol -> cuiksols2samples;
      cuiksols2samples -> samples;
    }
    \enddot
    </center>

     A tool to transform solutions to samples. Solutions are given
     with ranges for each system variable while samples are given
     as points. This application simply reads the list of
     solutions and stores the central point of each solution box
     in the sample output file.

*/


/** 
   \brief Main body of the \ref cuiksols2samples.c "cuiksols2samples" application.

   Main body of the \ref cuiksols2samples.c "cuiksols2samples" application.

   A tool to transform solutions to samples. Solutions are given
   with ranges for each system variable while samples are given
   as points. This application simply reads the list of
   solutions and  stores the central point of each solution box
   in the sample output file.

   Use:<br>
       - \b cuiksols2samples \e sol_name \e sample_name
       .
   where
       - \e solution_name is the .sol file with the solutions.
       - \e sample_name [optional] is the output \e .links (or \e dof) file.
         If not given sol_file.links (sol_file.joints) is used.
       .
   The file extensions are not required.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksols2samples command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;
  Tfilename fparam,fsols,fsamples;
  Tbox box;
  FILE *fin,*fout;
  Tsample s;
  int token;
  unsigned int rep;
  char *fn;
  
  if (argc>1)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      if (argc>2)
	fn=arg[2];
      else
	fn=arg[1];

      CreateFileName(NULL,fn,NULL,SOL_EXT,&fsols);     
      fprintf(stderr,"Reading boxes file                : %s\n",GetFileFullName(&fsols));
      fin=fopen(GetFileFullName(&fsols),"r");
      if (!fin)
	Error("Input file with boxes can not be opened");

      rep=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (rep==REP_JOINTS)
	CreateFileName(NULL,fn,NULL,JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,fn,NULL,LINKS_EXT,&fsamples);
      fprintf(stderr,"Writing samples file              : %s\n",GetFileFullName(&fsamples));
      fout=fopen(GetFileFullName(&fsamples),"w");
      if (!fout)
	Error("Output file for samples can not be opened");

      do {
	token=ReadBox(fin,&box);
	if (token!=EOF)
	  {
	    InitSampleFromBox(NO_UINT,NULL,&box,NO_UINT,&s);
	    PrintSample(fout,&s);
	    
	    DeleteSample(&s);
	    DeleteBox(&box);
	  }
      } while(token!=EOF);

      fclose(fout);

      DeleteFileName(&fsols);
      DeleteFileName(&fsamples);
      DeleteFileName(&fparam);
      
      DeleteParameters(&parameters);
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuiksols2samples <sols_name>  <samples_name> \n");
      fprintf(stderr,"    <sols_name> the input .sol file.\n");
      fprintf(stderr,"    <samples_name> [optional] the output file for the samples.\n");
      fprintf(stderr,"        If not given <sol_nam>.links or <sol_name>.dof is used (depending on the problem parameters).\n");
    }

  return(EXIT_SUCCESS);
}
