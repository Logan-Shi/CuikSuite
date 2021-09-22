#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "world.h"

#include <stdlib.h>

/** \file cuiklinks2joints.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiklinks2joints    [label="cuiklinks2joints"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      joints  [label="joints"     color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      links   [label="links" color="#ff9999" ];
      vmask   [label="vmask"   color="#ff9999" ];

      param -> cuiklinks2joints
      world -> cuiklinks2joints
      joints -> cuiklinks2joints
      cuiklinks2joints -> links;
      cuiklinks2joints -> vmask;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuiklinks2joints.c "cuiklinks2joints" application.

     A tool to transform cxuik variables to articular variables.
*/

/** 
   \brief Main body of the \ref cuiklinks2joints.c "cuiklinks2joints" application.

   Main body of the \ref cuiklinks2joints.c "cuiklinks2joints" application.

   A tool to transform variables giving the links poses to joint variables.

   Use:<br>
       - \b cuiklinks2joints \e problem_name \e output_name
       .
   where
       - \e problem_name is used to generate the \e world and \e links files.
       - \e output_name [optional] is name of the dof file. If not given
         the problem_name is used.
       .
   The extension are optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiklinks2joints command itself and its arguments).
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
      Tfilename flinks;
      Tfilename fjoints;

      unsigned int i,j;

      unsigned int ndof;
      double *dof;
      unsigned int nv,nvs;
      boolean *sv;
      double *sample;

      FILE *fd,*fs;

      boolean end;
      int token;

      unsigned int r;

      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);      
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (r==REP_JOINTS)
	Error("The system representation can not be JOINTS when converting to JOINTS");

      /* Read the problem file */
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      /* Open the file from where to read the samples */
      CreateFileName(NULL,arg[1],NULL,LINKS_EXT,&flinks);
      fprintf(stderr,"Reading link poses from           : %s\n",GetFileFullName(&flinks));
      fs=fopen(GetFileFullName(&flinks),"r");
      if (!fs)
	Error("Could not open the file to read the link poses");
      
      /* Open the file where to store the dof */
      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,JOINTS_EXT,&fjoints);
      else
	CreateFileName(NULL,arg[1],NULL,JOINTS_EXT,&fjoints);
      fprintf(stderr,"Writing dof to                    : %s\n",GetFileFullName(&fjoints));
      fd=fopen(GetFileFullName(&fjoints),"w");
      if (!fd)
	Error("Could not open the file to store the dof");

      /* Allocate space for the sample and dof */
      nv=GetWorldSystemVars(&sv,&world);
      nvs=0;
      for(i=0;i<nv;i++)
	{
	  if (sv[i])
	    nvs++;
	}
      NEW(sample,nvs,double);

      ndof=GetWorldNDOF(&world);
      NEW(dof,ndof,double);

      end=FALSE;
      do {
	for(i=0;((!end)&&(i<nvs));i++)
	  {
	    token=fscanf(fs,"%lf",&(sample[i]));
	    if ((token==EOF)||(token==0))
	      end=TRUE;
	  }
	if (!end)
	  {
	    WorldSample2DOF(&parameters,sample,dof,&world);
	    for(j=0;j<ndof;j++)	
	      fprintf(fd,"%.16f ",dof[j]);
	    fprintf(fd,"\n");
	  }
      } while (!end);

      free(sv);
      free(dof);
      free(sample);

      fclose(fd);
      fclose(fs);
 
      DeleteWorld(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fjoints);
      DeleteFileName(&flinks);    
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuiklinks2joints <problem_name> <dof_name>\n");
      fprintf(stderr,"    <problem_name> the prefix to define the .world and.\n");
      fprintf(stderr,"        .links files.\n");
      fprintf(stderr,"    <dof_name> [optional] The prefis to define the .dof.\n");
      fprintf(stderr,"        file. If not given the <problem_name> is used.\n");
    }
 
  return(EXIT_SUCCESS);
}
