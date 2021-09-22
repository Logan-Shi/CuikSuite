#include "defines.h"
#include "filename.h"
#include "world.h"

#include <stdlib.h>

/** \file cuiksamples2atoms.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksamples2atoms    [label="cuiksamples2atoms"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      atoms   [label="atoms"   color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      param -> cuiksamples2atoms
      world -> cuiksamples2atoms
      samples -> cuiksamples2atoms
      cuiksamples2atoms -> atoms;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuiksamples2atoms.c "cuiksamples2atoms" application.

    A tool to create files with atom coordinates from sample files.
    The pdb files typically include low reliable atom positions, i.e. atom positions
    that do not fullfill the rigid geometry hypothesis (each pair of atoms is
    at a different distance, and each bond angle is also different).
    Moreover, the PDB standard defines the atom positions wiht low accuracy
    (4 digits only).
    For these reasons, when defining worlds from PDB files using \ref cuikpdb2world.c "cuikpdb2world"
    the atom positions can be taken from an .atoms file, if
    available. This applications generates this .atoms files from a world
    and a valid sample.

    Moreover, the atom positions can be used to transfer samples from automatically generated
    worlds to user-defined ones, both describing the same molecule.
    The world generated with \ref cuikpdb2world.c "cuikpdb2world" is the one that can be used, for instance,
    to evaluate energies since it is "syncronized" with a given PDB. The automatically
    generated world has reference frames for each link that can be different from those
    in the user-generated world. Thus, files with samples can not be direclty shared
    between the user and the generated worlds. However, we can generate the atom
    positions from the user-generated world (with 
    \ref cuiksamples2atoms.c "cuiksamples2atoms") and then
    recover the sample for the automatically generated world (with 
    \ref cuikatoms2samples.c "cuikatoms2samples").

    Note that this process reads sample or dof files according the parameters.
    Thus, this could be also called cuikdofs2atoms.
*/

/** 
    \brief Main body of the \ref cuiksamples2atoms.c "cuiksamples2atoms" application.

    Main body of the \ref cuiksamples2atoms.c "cuiksamples2atoms" application.
   
    A tool to create files with atom coordinates from sample files.
    The pdb files typically include low reliable atom positions, i.e. atom positions
    that do not fullfill the rigid geometry hypothesis (each pair of atoms is
    at a different distance, and each bond angle is also different).
    Moreover, the pdb standard defines the atom positions wiht low accuracy
    (4 digits only).
    For these reasons, when defining worlds from pdb files using \ref cuikpdb2world.c "cuikpdb2world"
    the atom positions can be taken not from the pdb but from an .atoms file, if
    available. This applications generates this .atoms files from a world
    and a valid sample.

    Moreover, the atom positions can be used to transfer samples from automatically generated
    worlds to user-defined ones, both describing the same molecule.
    The world generated with \ref cuikpdb2world.c "cuikpdb2world" is the one that can be used, for instance,
    to evaluate energies since it is "syncronized" with a given PDB. The automatically
    generated world has reference frames for each link that can be different from those
    in the user-generated world. Thus, files with samples can not be direclty shared
    between the user and the generated worlds. However, we can generate the atom
    positions from the user-generated world (with 
    \ref cuiksamples2atoms.c "cuiksamples2atoms") and then
    recover the sample for the automatically generated world (with 
    \ref cuikatoms2samples.c "cuikatoms2samples").

    Note that this process reads sample or dof files according the parameters.
    Thus, this could be also called cuikdofs2atoms.


    CAUTION: This only works for carefully defined worlds where the atoms are in the same 
    order as in the PDB. This is NOT the case for automatically generated world (as those 
    generated for protein loops).

    Use:<br>
       - \b cuiksamples2atoms \e problem_name \e out_name
       .
    where
       - \e problem_name is used to generate the input and output file names.
       - \e out_name [optional] The output atom file.
       .

   The extension are optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksamples2atoms command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{ 
  if (argc>1)
    {
      Tparameters parameters;
      Tworld world;

      Tfilename fparam;
      Tfilename fsamples;
      Tfilename fatoms;

      boolean nv;
      double *sample;

      char *fn;
      FILE *fs;

      unsigned int i,r;
      boolean end;
      int token;

      FILE *fout;

      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);      
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));

      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /* Read the problem file */
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      if (!IsMechanismInWorldAllSpheres(&world))
	Warning("The world is not sphere-only");

      /* Open the file from where to read the samples */
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (r==REP_JOINTS)
	CreateFileName(NULL,arg[1],NULL,JOINTS_EXT,&fsamples);
      else
	CreateFileName(NULL,arg[1],NULL,LINKS_EXT,&fsamples);

      fprintf(stderr,"Reading one sample from           : %s\n",GetFileFullName(&fsamples));

      fs=fopen(GetFileFullName(&fsamples),"r");

      if (!fs)
	Error("Could not open the file to read the samples");

      if (argc>2)
	fn=arg[2];
      else
	fn=arg[1];

      /* Open the file where to store the bio-information */
      CreateFileName(NULL,fn,NULL,ATOM_EXT,&fatoms);
      fprintf(stderr,"Writing atoms to                  : %s\n",GetFileFullName(&fatoms));

      /* Allocate space for the sample/dof */
      nv=GetWorldNumSystemVariables(&world);
      NEW(sample,nv,double);

      /* Read one sample from the file of samples */
      fout=fopen(GetFileFullName(&fatoms),"w");
      if (!fout)
	Error("Could not open the file to store the atom positions");

      end=FALSE;
      do {
	for(i=0;((!end)&&(i<nv));i++)
	  {
	    token=fscanf(fs,"%lf",&(sample[i]));
	    if ((token==EOF)||(token==0))
	      end=TRUE;
	  }
	/* If the sample could be read correctly, save the atom positions */
	if (!end)
	  WorldPrintAtoms(&parameters,fout,sample,&world);
      } while (!end);

      fclose(fout);
  
      /* Close the input file */
      fclose(fs);

      /* Release memeory */
      free(sample);
      DeleteWorld(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fsamples); 
      DeleteFileName(&fatoms);    
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuiksamples2atoms <problem_name> <out_name>\n");
      fprintf(stderr,"    <problem_name> the prefix to define the world,\n");
      fprintf(stderr,"        .params and .samples files.\n");
      fprintf(stderr,"    <out_name> [optional] The output atom file.\n");
      fprintf(stderr,"CAUTION: This only works for carefully defined worlds\n");
      fprintf(stderr,"         where the atoms are in the same order as in\n");
      fprintf(stderr,"         the PDB. This is NOT the case for automatically\n");
      fprintf(stderr,"         generated worlds (as those generated for protein loops)\n");
    }
 
  return(EXIT_SUCCESS);
}
