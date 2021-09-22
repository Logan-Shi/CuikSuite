#include "box.h"
#include "random.h"
#include "defines.h"
#include "filename.h"
#include "geom.h"
#include "world.h"

#include <stdlib.h>

/** \file cuikjoints2links.c

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikjoints2links    [label="cuikjoints2links"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      joints  [label="joints"  color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      links   [label="links" color="#ff9999" ];
      vmask   [label="vmask"   color="#ff9999" ];

      param -> cuikjoints2links
      world -> cuikjoints2links
      joints -> cuikjoints2links
      cuikjoints2links -> links;
      cuikjoints2links -> vmask;
    }
    \enddot
    </center>

    \brief Main body of the \ref cuikjoints2links.c "cuikjoints2links" application.

     A tool to transform articular variables to cuik variables
*/

/** 
   \brief Main body of the \ref cuikjoints2links.c "cuikjoints2links" application.

   Main body of the \ref cuikjoints2links.c "cuikjoints2links" application.

   A tool to transform articular variables to cuik variables.

   It additonally store the samples in the form of boxes (in a .sol file) and
   give the variable names and the system variables in the simplified form
   (in a .vname and .vmask files). These two last files are used when
   generating eigengrasp from files in JOINTS. These files are transformed
   to .sample files and we need to retain which of the dimensions of the
   samples are independent. The variable names are used to generate the
   eigen-grasp equations that are latter added to the cuiksystem.

   Use:<br>
       - \b cuikjoints2links \e problem_name.world \e output_file
       .
   where
       - \e problem_name is used to define the input \e world file.
       - \e output_file [optional] is name of the joints (input), links, sol, vnames, 
         and vmask (ouput) files.
         If not given the inputs is taked form proble_file.joints and the 
	 output values are stored in problem_name.links, 
	 problem_name.sol, problem_name.vnames, and problem_name.vmask
       .
   The extensions are optional.
   
   This *.vmaks output is an array of booleans that indicate which of the variables used
   in the problem are related to the pose of the main links in the problem and are
   present in the simplified system.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikjoints2links command itself and its arguments).
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
      Tfilename fboxes;
      Tfilename fjoints;
      Tfilename fvmask;
      Tfilename fvname;

      unsigned int r;
      unsigned int i,j;

      unsigned int ndof;
      double *dof;
      unsigned int nv;
      boolean *sv,*mask;
      double *sample;
      Tbox bsample;
      char **varNames;

      FILE *fd,*fs,*fb;

      boolean end;
      int token;

      char **vn;

      /* Init parameters */
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);      
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));

      if (r==REP_JOINTS)
	Error("Please, set a REPRESENTATION different from JOINTS in the parameter file");

      /* Read the problem file */
      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);
      
      /* Open the the dof file */
      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,JOINTS_EXT,&fjoints);
      else
	CreateFileName(NULL,arg[1],NULL,JOINTS_EXT,&fjoints);
      fprintf(stderr,"Reading dof from                  : %s\n",GetFileFullName(&fjoints));
      fd=fopen(GetFileFullName(&fjoints),"r");
      if (!fd)
	Error("Could not open the file with the dof");

      /* Open the file to store the link poses */
      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,LINKS_EXT,&flinks);
      else
	CreateFileName(NULL,arg[1],NULL,LINKS_EXT,&flinks);
      fprintf(stderr,"Writing link poses to             : %s\n",GetFileFullName(&flinks));
      fs=fopen(GetFileFullName(&flinks),"w");
      if (!fs)
	Error("Could not open the file to store the link poses");

      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fboxes);
      else
	CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fboxes);
      fprintf(stderr,"Writing boxes to                  : %s\n",GetFileFullName(&fboxes));
      fb=fopen(GetFileFullName(&fboxes),"w");
      if (!fb)
	Error("Could not open the file to store the boxes");
      
      /* Allocate space to read the dof */
      nv=GetWorldSystemVars(&sv,&world);

      ndof=GetWorldNDOF(&world);
      NEW(dof,ndof,double);

      end=FALSE;
      do {
	for(i=0;((!end)&&(i<ndof));i++)
	  {
	    token=fscanf(fd,"%lf",&(dof[i]));
	    if ((token==EOF)||(token==0))
	      end=TRUE;
	  }
	if (!end)
	  {
	    if (WorldDOF2Sol(&parameters,dof,&sample,&bsample,&world)!=nv)
	      Error("Missmatch variable number in cuikjoints2links");
	    for(j=0;j<nv;j++)
	      {
		if (sv[j])
		  { PrintReal(fs,sample[j]);fprintf(fs," "); }
	      }
	    fprintf(fs,"\n");
	    free(sample);
	    NEW(vn,nv,char *);
	    GetWorldVarNames(vn,&world);
	    PrintBoxSubset(fb,sv,vn,&bsample);
	    free(vn);
	    DeleteBox(&bsample);
	  }
      } while (!end);

      fclose(fd);
      fclose(fs);
      fclose(fb);

      free(dof);

      /* Now write a file with the array of booleans indicating the good
         variables: the ones refering to link poses that are keept in
         the simplified cuiksystem. This is very adhoc for generating
         eigengrasps.... We dot it that way to have an automatic
         way to generate the eigengrasp without resorting to a manual
         procedure prone to errors. */
      
      nv=GetWorldSimpVariableMask(&parameters,&mask,&world);

      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,"vname",&fvname);
      else
	CreateFileName(NULL,arg[1],NULL,"vname",&fvname);
      fprintf(stderr,"Writting variable names to        : %s\n",GetFileFullName(&fvname));
      fs=fopen(GetFileFullName(&fvname),"w");
      if (!fs)
	Error("Could not open the file to store the variable names");
      
      NEW(varNames,nv,char*);
      GetWorldVarNames(varNames,&world);

      for(j=0;j<nv;j++)
	{
	  if (sv[j])
	    {
	      PRINT_VARIABLE_NAME(fs,varNames[j]);
	      fprintf(fs,"\n");
	    }
	}
      fclose(fs);
      free(varNames);


      if (argc>2)
	CreateFileName(NULL,arg[2],NULL,"vmask",&fvmask);
      else
	CreateFileName(NULL,arg[1],NULL,"vmask",&fvmask);
      fprintf(stderr,"Writting variable mask to         : %s\n",GetFileFullName(&fvmask));
      fs=fopen(GetFileFullName(&fvmask),"w");
      if (!fs)
	Error("Could not open the file to store the variable mask");

      for(j=0;j<nv;j++)
	{
	  if (sv[j])
	    {
	      if (mask[j])
		fprintf(fs,"1 ");
	      else
		fprintf(fs,"0 ");
	    }
	}
      fprintf(fs,"\n");

      free(sv);
      free(mask);
      fclose(fs);

      DeleteWorld(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fparam);
      DeleteFileName(&fjoints);
      DeleteFileName(&flinks);
      DeleteFileName(&fboxes);
      DeleteFileName(&fvmask);
      DeleteFileName(&fvname);
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikjoints2links <problem_name> <output_name>\n");
      fprintf(stderr,"    <problem_name> the file with the .world description.\n");
      fprintf(stderr,"    <output_name> [optional] Prefix for the .joints file and to generate the .links.\n");
      fprintf(stderr,"        .sol, .vname, and .vmask files. If not given the <problem_name> is used.\n");
    }
 
  return(EXIT_SUCCESS);
}
