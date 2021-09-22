#include "defines.h"
#include "filename.h"
#include "world.h"

#include <stdlib.h>

/** \file cuiksamples2rgroups.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksamples2rgroups    [label="cuiksamples2rgroups"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      rgroups [label="rgroups" color="#ff9999" ];
      samples [label="samples" color="#ff9999" ];

      param -> cuiksamples2rgroups
      world -> cuiksamples2rgroups
      samples -> cuiksamples2rgroups
      cuiksamples2rgroups -> rgroups;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuiksamples2rgroups.c "cuiksamples2rgroups" application.

    This application takes a world file and a sample and generates a file with the atoms
    grouped by rigid groups. These input files are used to test the RigidCLL library. This
    is a proximity/collision detection library specially designed to be efficient when
    the atoms are grouped in rigid groups. This algorithm is described in our paper:

          - V. Ruiz de Angulo, J. Cort&eacute;s, J. M. Porta, <a href="http://www.iri.upc.edu/people/porta/Docs/jcc12.pdf">Rigid-CLL: Avoiding Constant-distance Computations in Cell Linked-Lists Algorithms</a>, Journal of Computational Chemistry, Vol. 33, No. 3, pp. 294-300, 2012.
	  .

    Thus, this application is only used to generate test files for the RigidCLL library
    and, therefore, it is not directly used in the CuikSuite application.

    Note that this application can operate on any world file, irrespectively whether it comes from a molecule or not. 
    The operation basically considers any sphere in the world as an atom and stores its center and radius in
    the given configuration.
*/

/** 
    \brief Main body of the \ref cuiksamples2rgroups.c "cuiksamples2rgroups" application.

    This application takes a world file and a sample and generates a file with the atoms
    grouped by rigid groups. These input files are used to test the RigidCLL library. This
    is a proximity/collision detection library specially designed to be efficient when
    the atoms are grouped in rigid groups. This algorithm is described in our paper:

          - V. Ruiz de Angulo, J. Cort&eacute;s, J. M. Porta, <a href="http://www.iri.upc.edu/people/porta/Docs/jcc12.pdf">Rigid-CLL: Avoiding Constant-distance Computations in Cell Linked-Lists Algorithms</a>, Journal of Computational Chemistry, Vol. 33, No. 3, pp. 294-300, 2012.
	  .

    Thus, this application is only used to generate test files for the RigidCLL library
    and, therefore, it is not directly used in the CuikSuite application.

    Note that this application can operate on any world file, irrespectively whether it comes from a molecule or not. 
    The operation basically considers any sphere in the world as an atom and stores its center and radius in
    the given configuration.

    Use:<br>
       - \b cuiksamples2rgroups \e problem_name \e out_name
       .
    where
       - \e problem_name is used to generate the input and output file names.
       - \e out_name [optional] The output rgroups file.
       .

   The extension are optional.

   An example of use can be
       - bin/cuiksamples2rgroups examples/Bio/1EJ0 ~/RigidCLL/data/ex1
       .
    This generates a file (ex1.rgroups) into the RigidCLL folder form the information
    in the examples/Bio/1EJ0.world (which in turns comes from a PDB file using the
    \ref cuikpdb2world.c "cuikpdb2world" application).

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksamples2rgroups command itself and its arguments).
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
      Tfilename frgroups;

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
      CreateFileName(NULL,fn,NULL,RGROUPS_EXT,&frgroups);
      fprintf(stderr,"Writing rigid groups to           : %s\n",GetFileFullName(&frgroups));

      /* Allocate space for the sample/dof */
      nv=GetWorldNumSystemVariables(&world);
      NEW(sample,nv,double);

      /* Read one sample from the file of samples */
      fout=fopen(GetFileFullName(&frgroups),"w");
      if (!fout)
	Error("Could not open the file to store the rigid groups");

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
	  WorldStoreRigidGroups(&parameters,fout,sample,&world);
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
      DeleteFileName(&frgroups);   

      return(EXIT_SUCCESS); 
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuiksamples2rgroups <problem_name> <out_name>\n");
      fprintf(stderr,"    <problem_name> the prefix to define the world,\n");
      fprintf(stderr,"        .params and .samples files.\n");
      fprintf(stderr,"    <out_name> [optional] The output atom file.\n");

      return(EXIT_FAILURE);
    }
}
