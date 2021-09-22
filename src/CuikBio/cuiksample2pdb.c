#include "defines.h"
#include "filename.h"
#include "bioworld.h"

#include <stdlib.h>

/** \file cuiksample2pdb.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksample2pdb    [label="cuiksample2pdb"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      pdbIn   [label="pdb"     color="#ff9999" ];
      pdbOut  [label="pdb"     color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      param -> cuiksample2pdb
      pdbIn -> cuiksample2pdb
      samples -> cuiksample2pdb
      cuiksample2pdb -> pdbOut;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuiksample2pdb.c "cuiksample2pdb" application.

    A tool to generate bio-info files (e.g. pdb) for a particular configuration.
    It basically reads a bio-info file, replaces the atom positions by the ones
    computed form the given sample, and generates a new bio-info file.
    This output can be latter used in any software for molecular analysis.

    Note that we usually work with pdb files but that any other file format
    accepted by OpenBabel can be used.
*/

/** 
   \brief Main body of the \ref cuiksample2pdb.c "cuiksample2pdb" application.

   Main body of the \ref cuiksample2pdb.c "cuiksample2pdb" application.

   A tool to generate bio-info files (e.g. pdb) for a particular configuration.
   It basically reads a bio-info file, replaces the atom positions by the ones
   computed form the given sample, and generates a new bio-info file.
   This output can be latter used in any software for molecular analysis.

   Use:<br>
       - \b cuiksample2pdb \e problem_name
       .
   where
       - \e problem_name is used to generate the \e param, bio-info, and \e sample files.
       .

   The extension are optional, except of the \e out_name parameter, if provided.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksample2pdb command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{ 
  if (argc>1)
    {
      Tparameters parameters;
      TBioWorld bioWorld;

      Tfilename fparam;
      Tfilename fsamples;
      Tfilename fbio;

      boolean nv;
      double *sample;

      FILE *fs;
      char *fout;

      double *conf;
      unsigned int i,r;
      boolean end;
      int token;

      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);      
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));

      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /* Read the problem file */
      InitBioWorld(&parameters,arg[1],NO_UINT,&conf,&bioWorld);

      /* Open the file from where to read the samples */
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (r==REP_JOINTS)
	CreateFileName(NULL,arg[1],"_center",JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,arg[1],"_center",LINKS_EXT,&fsamples);

      fprintf(stderr,"Reading one sample from           : %s\n",GetFileFullName(&fsamples));

      fs=fopen(GetFileFullName(&fsamples),"r");
      if (!fs)
	Error("Could not open the file to read the samples");
      
      /* Open the file where to store the bio-information */
      CreateFileName(NULL,arg[1],"_sample",PDB_EXT,&fbio);
      fout=GetFileFullName(&fbio);
      fprintf(stderr,"Writing bio-info to               : %s\n",fout);

      /* Allocate space for the sample and dof */
      nv=BioWorldConformationSize(&bioWorld);
      NEW(sample,nv,double);

      /* Read one sample from the file of samples */
      end=FALSE;
      for(i=0;((!end)&&(i<nv));i++)
	{
	  token=fscanf(fs,"%lf",&(sample[i]));
	  if ((token==EOF)||(token==0))
	    end=TRUE;
	}

      /* If the sample could be read correctly, use the sample to define a pdb 
	 and write it to a file */
      if (!end)
	SaveBioWorldBioInfo(&parameters,fout,FALSE,sample,&bioWorld);

      /* Close the input file */
      fclose(fs);

      /* Release memeory */
      free(sample);
      free(conf);
 
      DeleteBioWorld(&bioWorld);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fbio);
      DeleteFileName(&fsamples);    
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");
      fprintf(stderr,"    cuiksample2pdb <problem_name>\n");
      fprintf(stderr,"  where:\n");
      fprintf(stderr,"    <problem_name>.pdb the prefix to define the bio-info.\n");
      fprintf(stderr,"  The extension (e.g., '.pdb') is required\n");
      fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
      fprintf(stderr,"  The output is stored in <proble_name>_sample.pdb\n");
    }
 
  return(EXIT_SUCCESS);
}
