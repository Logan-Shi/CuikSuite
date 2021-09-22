#include "parameters.h"
#include "defines.h"
#include "world.h"
#include "error.h"
#include "filename.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** \file cuikaddjacobian.c

    \brief Main body of the \ref cuikaddjacobian.c "cuikaddjacobian" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikaddjacobian    [label="cuikaddjacobian"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      kinIn   [label="cuik"  color="#ff9999" ];
      kinOut  [label="_J.cuik" color="#ff9999" ];

      param -> cuikaddjacobian
      kinIn -> cuikaddjacobian;
      cuikaddjacobian -> kinOut;
    }
    \enddot
    </center>

    Note that this only works if the system \ref CT_REPRESENTATION "representation"
    is not DOF-based.

    Takes as input a <em>cuik</em> file resulting from 
    \ref cuiksingequations.c "cuiksingequations" and adds equations to detect
    then rank deficiency of the Jacobian for a given set of variables.
    
    The result of this application is a system of equations that encodes
    a given set of singularities for the mechanism in the initial <em>world</em>
    file.

    In most of the cases it would be better to use  \ref cuikaddjacobian.c "cuikaddjacobian"
    on the simplification (via \ref cuiksimplify.c "cuiksimplify") of the system
    derived from \ref cuiksingequations.c "cuiksingequations". Thus the whole process
    will be
        - \ref cuiksingequations.c "cuiksingequations" \e name
	- \ref cuiksimplify.c "cuiksimplify" \e name_sing
	- \ref cuikaddjacobian.c "cuikaddjacobian" \e name_sing_simp
        .
    which will produce a \e name_sing_simp_J.cuik file.

    The process of generating singularity equations is splitted in two parts since,
    in principle, equations introduced by  \ref cuiksingequations.c "cuiksingequations" are
    necessary independently of the type of singularities to analyze whereas the
    Jacobian equations affects different sets of variables according to the
    singularity set to study (end effector, actuator, etc).

    See \ref examples/WSSingularities for examples of how to use
    this application.

    <b>IMPORTANT:</b> The automatic generation of equations to detect singularities is still
    in development. The tools currently included in the CuikSuite (including
    this one) can only deal with simple cases (e.g. planar robots with 3 degrees
    of freedom). Thus, right now it is advisable to
    manually generate these equations following the instructions given in the
    work by <a href="http://www.iri.upc.edu/people/obohigas/">O. Bohigas</a>, 
    <a href="http://www.iri.upc.edu/people/mmanuben/Welcome.html">M. Manubens</a>, 
    and <a href="http://www.iri.upc.edu/people/ros/">L. Ros</a>.

    \todo Define tools to generate equation systems to detect particular singularities
          (end effector, actuator,...). These tools will be less flexible that the
	  combined use of \ref cuiksingequations.c "cuiksingequations" and
          \ref cuikaddjacobian.c "cuikaddjacobian" but will be useful for most of 
	  the cases.

    \sa world.c
*/

/** 
   \brief Main body of the \ref cuikaddjacobian.c "cuikaddjacobian" application.

   Main body of the \ref cuikaddjacobian.c "cuikaddjacobian" application.

   Use:<br>
       - \b cuikaddjacobian \e problem_name.cuik \e var_names
       .
   where 
     - \e problem_name is the _sing.cuik file resulting from  \ref cuiksingequations.c "cuiksingequations".
     - \e var_names is a list of the variable of interest (the ones not included in the Jacobian).
     .
     

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuiksingequations command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;     /* Parameters */
  TCuikSystem cuik;           /* The cuiksystem to enrich with the Jacobian equations*/

  Tfilename fparam;
  Tfilename fcuik;
  Tfilename fcuikOut;
  
  FILE *f;
  boolean *selectedVars;
  unsigned int i,nv,vID;

  if (argc>1)
    {
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      #if (_DEBUG>0)
        printf("Reading parameter file     : %s\n",GetFileFullName(&fparam));
      #endif
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Init cuik*/
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);      
      #if (_DEBUG>0)
        printf("Reading .cuik file         : %s\n",GetFileFullName(&fcuik));
      #endif
      /*Read the cuik file*/
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuik);

      /*determine the variables*/
      nv=GetCSNumVariables(&cuik);
      
      if (argc>2)
	{
	  NEW(selectedVars,nv,boolean);
	  /*in principle all variables are to be used in the Jacobian*/
	  for(i=0;i<nv;i++)
	    selectedVars[i]=TRUE; 
	  /*but we exclude those given by the user*/
	  for(i=2;i<(unsigned int)argc;i++)
	    {
	      vID=GetCSVariableID(arg[i],&cuik);
	      if (vID==NO_UINT)
		fprintf(stderr,"ERROR: Variable %s is not included in the cuiksystem\n",arg[i]);
	      else
		{
		  fprintf(stderr,"   Focusing on variable    : %s (%u)\n",arg[i],vID);
		  selectedVars[vID]=FALSE;
		}
	    }
	}
      else
	selectedVars=NULL;
      
      /*Add singularity equations*/
      AddJacobianEquations(&parameters,selectedVars,&cuik);
      
      /*Print resulting extended cuiksystem*/
      CreateFileName(NULL,arg[1],"_J",CUIK_EXT,&fcuikOut);

      f=fopen(GetFileFullName(&fcuikOut),"w");
      if (!f)
	 Error("Could not open output file in cuikaddjacobian");     
      #if (_DEBUG>0)
        printf("Generating the _J.cuik file: %s\n",GetFileFullName(&fcuikOut));
      #endif
      PrintCuikSystem(&parameters,f,&cuik);
      fclose(f);

      /* link the parameter/joints/links files */
      LinkFileNameWithExtension(arg[1],PARAM_EXT ,&fcuikOut);
      LinkFileNameWithExtension(arg[1],JOINTS_EXT,&fcuikOut);
      LinkFileNameWithExtension(arg[1],LINKS_EXT ,&fcuikOut);

      /* Delete the data structures */
      if (selectedVars!=NULL)
	free(selectedVars);
      DeleteCuikSystem(&cuik);
      DeleteParameters(&parameters);

      /* Delete the file names */
      DeleteFileName(&fparam);
      DeleteFileName(&fcuik);
      DeleteFileName(&fcuikOut);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");   
      fprintf(stderr,"      cuikaddjacobian <problem name> <varname1> <varname2> ...\n");
      fprintf(stderr,"  where \n");
      fprintf(stderr,"       <problem name> is the cuik file resulting from cuiksingequations\n");
      fprintf(stderr,"       <varnames> is the list of variables of interest\n");
    }

  return(EXIT_SUCCESS);
}

