#include "defines.h"
#include "filename.h"
#include "bioworld.h"

#include <stdlib.h>

/** \file cuikpdb2sample.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikpdb2sample    [label="cuikpdb2sample"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      pdbIn   [label="pdb"     color="#ff9999" ];
      sample  [label="sample"  color="#ff9999" ];

      param -> cuikpdb2sample
      pdbIn -> cuikpdb2sample
      cuikpdb2sample -> sample;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuikpdb2sample.c "cuikpdb2sample" application.

    A tool to generate internal coordinates from a bio-information file (e.g., pdb)
*/

/** 
   \brief Main body of the \ref cuikpdb2sample.c "cuikpdb2sample" application.

   A tool to generate internal coordinates from a bio-information file (e.g., pdb). 
   The exact form of the internal coordinates depend on the parametres used (\ref CT_REPRESENTATION).
   For \ref CT_REPRESENTATION = JOINTS, we generate the internal coordiantes
   (dihedral angles) already used in molecular modelling. Other representations
   produce equivalent information but in formats not usual in molecular biology.

   This tool could also be called cuikpdb2dof (depending on the parametres).

   Use:<br>
       - \b cuikpdb2sample \e problem_name
       .
   where
       - \e problem_name is used to generate the \e param and \e bio-info.
       .

   The extension for the problem_name is compulsatory.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikpdb2sample command itself and its arguments).
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

      boolean nv;
      double *sample;

      unsigned int i,r;

      FILE *fout;

      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);      
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /* Read the problem file */
      InitBioWorld(&parameters,arg[1],NO_UINT,&sample,&bioWorld);
      nv=BioWorldConformationSize(&bioWorld);

      /* Open the file where to store the output sample */
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (r==REP_JOINTS)
	CreateFileName(NULL,arg[1],"_pdb",JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,arg[1],"_pdb",LINKS_EXT,&fsamples);
      fprintf(stderr,"Writing sample to                 : %s\n",GetFileFullName(&fsamples));

      fout=fopen(GetFileFullName(&fsamples),"w");
      if (!fout)
	Error("Could not open the file to write the sample");

      /* Save the conformation */
      for(i=0;i<nv;i++)
	fprintf(fout,"%.16f ",sample[i]);
      fprintf(fout,"\n");

      /* Close the files */
      fclose(fout);
     
      /* Release memeory */
      free(sample);
 
      DeleteBioWorld(&bioWorld);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fsamples);  
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");
      fprintf(stderr,"    cuikpdb2sample <problem_name>.pdb\n");
      fprintf(stderr,"    where:\n");
      fprintf(stderr,"      <problem_name>.pdb the prefix to define the bio-info.\n");
      fprintf(stderr,"  The extension (e.g., '.pdb') is required\n");
      fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
      fprintf(stderr,"  The output is stored in <proble_name>_pdb.dof\n");
      fprintf(stderr,"  or in <proble_name>_pdb.sample depending on the representation used\n");
    }
 
  return(EXIT_SUCCESS);
}
