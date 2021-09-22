#include "defines.h"
#include "filename.h"
#include "bioworld.h"

#include <stdlib.h>

/** \file cuikatoms2samples.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatoms2samples    [label="cuikatoms2samples"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      pdbIn   [label="pdb"     color="#ff9999" ];
      atoms   [label="atoms"   color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      param -> cuikatoms2samples
      pdbIn -> cuikatoms2samples
      atoms -> cuikatoms2samples
      cuikatoms2samples -> samples;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuikatoms2samples.c "cuikatoms2samples" application.

    A tool to generate internal coordinates from atom positions. The exact form
    of the internal coordinates depend on the parametres used (\ref CT_REPRESENTATION).
    For \ref CT_REPRESENTATION = JOINTS, we generate the internal coordiantes
    (dihedral angles) already used in molecular modelling. Other representations
    produce equivalent information but in formats not usual in molecular biology.

    This application can be used to generate conformations for path planning
    (for \ref cuikbioatlastrrt.c "cuikbioatlastrrt" for instance) from atom positions.
    Those atom positions can be generated form user-defined world representing
    a molecule via \ref cuiksamples2atoms.c "cuiksamples2atoms".
*/

/** 
   \brief Main body of the \ref cuikatoms2samples.c "cuikatoms2samples" application.

    A tool to generate internal coordinates from atom positions. The exact form
    of the internal coordinates depend on the parametres used (\ref CT_REPRESENTATION).
    For \ref CT_REPRESENTATION = JOINTS, we generate the internal coordiantes
    (dihedral angles) already used in molecular modelling. Other representations
    produce equivalent information but in formats not usual in molecular biology.

    This application can be used to generate conformations for path planning
    (for \ref cuikbioatlastrrt.c "cuikbioatlastrrt" for instance) from atom positions.
    Those atom positions can be generated form user-defined world representing
    a molecule via \ref cuiksamples2atoms.c "cuiksamples2atoms".

   Use:<br>
       - \b cuikatoms2samples \e problem_name
       .
   where
       - \e problem_name is used to generate the \e param, bio-info, and \e sample files.
       .

   The extension for the problem_name is compulsatory.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikatoms2samples command itself and its arguments).
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
      Tfilename fatoms;

      boolean nv;
      double *sample;

      unsigned int na;
      double *atoms;

      unsigned int i,j,k,r;
      boolean end;
      int token;

      FILE *fin;
      FILE *fout;

      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);      
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /* Read the problem file */
      InitBioWorld(&parameters,arg[1],NO_UINT,&sample,&bioWorld);
      free(sample);

      /* File from where to read the atoms */
      CreateFileName(NULL,arg[1],NULL,ATOM_EXT,&fatoms);
      fin=fopen(GetFileFullName(&fatoms),"r");
      if (!fin)
	Error("Can not open the input file with the atom positions");

      /* Open the file where to store the output samples */
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (r==REP_JOINTS)
	CreateFileName(NULL,arg[1],"_a2s",JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,arg[1],"_a2s",LINKS_EXT,&fsamples);
      fprintf(stderr,"Writing samples to                : %s\n",GetFileFullName(&fsamples));

      fout=fopen(GetFileFullName(&fsamples),"w");
      if (!fout)
	Error("Could not open the file to write the samples");
 
      /* Allocate space for the atoms and the sample */
      na=BioWorldNAtoms(&bioWorld);
      NEW(atoms,3*na,double);

      /* Read one sample from the file of samples */
      end=FALSE;
      do {
	k=0;
	for(i=0;((!end)&&(i<na));i++)
	  {
	    for(j=0;((!end)&&(j<3));j++,k++)
	      {
		token=fscanf(fin,"%lf",&(atoms[k]));
		if ((token==EOF)||(token==0))
		  end=TRUE;
	      }
	  }

	if (!end)
	  {
	    /* Deduce the conformation from the atom positions */
	    nv=BioWordConformationFromAtomPositions(&parameters,atoms,&sample,&bioWorld);

	    /* Save the conformation */
	    for(i=0;i<nv;i++)
	      fprintf(fout,"%.16f ",sample[i]);
	    fprintf(fout,"\n");

	    free(sample);
	  }

      } while(!end);

      /* Close the files */
      fclose(fin);
      fclose(fout);

      /* Release memeory */
      free(atoms);
 
      DeleteBioWorld(&bioWorld);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fsamples);  
      DeleteFileName(&fatoms);   
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");
      fprintf(stderr,"    cuikatoms2samples <problem_name>.pdb\n");
      fprintf(stderr,"  where <problem_name>.pdb contains the molecular information\n");
      fprintf(stderr,"  The '.pab' extension is required\n");
      fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
    }
 
  return(EXIT_SUCCESS);
}
