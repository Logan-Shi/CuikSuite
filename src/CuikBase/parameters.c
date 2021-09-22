#include "parameters.h"

#include "error.h"
#include "filename.h"
#include "defines.h"

#include <stdlib.h>
#include <strings.h>

/** 
   \file parameters.c

   \brief Implementation of the functions operating on Tparameters.

   Implementation of functions to deal with Tparameters.

   \sa Tparameters, parameters.h.
*/

/** 
   \brief Reads a parameter set from a file.

   Reads a parameter set from a file.

   \param file The name of the file.
   \param p The parameter set to update.

   \return TRUE if the the file with the parameter exists.
*/

boolean ReadParameters(char *file,Tparameters *p);

/*
 * Inits a parameter structure and defines all parameters equal to 0
 */
void InitParameters(Tparameters *p)
{
  unsigned int i;

  for(i=0;i<NPARAMETERS;i++)
    {
      (*p)[i].name=NULL;
      (*p)[i].value=0.0;
      (*p)[i].timesSet=0;
    }
}

/*
 * Inits a parameter structure from the given file
 */
void InitParametersFromFile(char *file,Tparameters *p)
{
  Tfilename dp;
  unsigned int i;
  boolean ok;

  InitParameters(p);

  
  CreateFileName(_CUIK_SUITE_MAIN_DIR,DEFAULT_PARAMS,NULL,PARAM_EXT,&dp);
  ok=ReadParameters(GetFileFullName(&dp),p);
  DeleteFileName(&dp);
  if (!ok)
    {
      /* try to read from a system directory (at a user given folder) */
      CreateFileName(_PARAM_PREFIX,DEFAULT_PARAMS,NULL,PARAM_EXT,&dp);
      ok=ReadParameters(GetFileFullName(&dp),p);
      DeleteFileName(&dp);
      if (!ok)
	{
	  /* try to read from a system directory (at a user general folder) */
	  CreateFileName("/usr",DEFAULT_PARAMS,NULL,PARAM_EXT,&dp);
	  if (!ReadParameters(GetFileFullName(&dp),p))
	    Error("Can not find the default parameter file");
	  DeleteFileName(&dp);
	}
    }

  /* The default initialization does not count. Reset the 'timesSet' */
  for(i=0;i<NPARAMETERS;i++)
    (*p)[i].timesSet=0;

  /* The existence of the parameter file associated with the
     problem is compulsatory */
  if (!ReadParameters(file,p))
    {
      char ErrorText[500];

      sprintf(ErrorText,"File %s does not exists. Using the default parameters",file);
      Warning(ErrorText);

      /* fix the 'timeSet' */
      for(i=0;i<NPARAMETERS;i++)
	(*p)[i].timesSet=1;
    }
}

/*
 * Returns the value of parameter number 'n'
 */
double GetParameter(unsigned int n,Tparameters *p)
{
  if (n<NPARAMETERS)
    {
      if ((*p)[n].name==NULL)
	 Error("Undefined parameter");
      else
	return((*p)[n].value);
    }
  else
    Error("Number of parameter out of range");
  return(0.0);
}

/*
 * Returns the parameter identifier given the parameter name.
 */
unsigned int GetParameterID(char *name,Tparameters *p)
{
  boolean found;
  unsigned int i;

  found=FALSE;
  i=0;
  while((!found)&&(i<NPARAMETERS))
    {
      found=(((*p)[i].name!=NULL)&&(strcasecmp((*p)[i].name,name)==0));
      if (!found) i++;
    }
  if (found)
    return(i);
  else
    return(NO_UINT);
}

/*
 * Check is a parameter is already set.
 */
boolean ParameterSet(unsigned int n,Tparameters *p)
{
  return(((*p)[n].name!=NULL)&&((*p)[n].timesSet>0));
}

/*
 * Sets a new parameter with identifier 'n', with name 'name', and with value 'v'
 */
void SetParameter(unsigned int n,char *name,double v,Tparameters *p)
{
  if (n<NPARAMETERS)
    {
      if ((*p)[n].name!=NULL)
	{
	  if ((*p)[n].timesSet>0)
	    Warning("Redefined parameter");
	  ChangeParameter(n,v,p);
	  (*p)[n].timesSet++;
	}
      else
	{
	  (*p)[n].name=name;
	  (*p)[n].value=v;
	  (*p)[n].timesSet=1;
	}
    }
  else
    Error("Number of parameter out of range");
}

/*
 * Changes the value of parameter 'n'
 */
void ChangeParameter(unsigned int n,double v,Tparameters *p)
{
  if (n<NPARAMETERS)
    {
      if ((*p)[n].name==NULL)
	Error("Changing a non-defined parameter");
      
      (*p)[n].value=v;
    }
  else
    Error("Number of parameter out of range");
}

/*
 * Prints a set of parameters.
 * Only those explicitly used are shown.
 */
void PrintParameters(FILE *f,Tparameters *p)
{
  unsigned int i;
  unsigned int v;
  
  fprintf(f,"%% **************************************************\n");
  fprintf(f,"%% COMPILATION FLAGS:\n");
  fprintf(f,"%%   DEBUG: %u\n",_DEBUG);
  fprintf(f,"%%   SIMPLEX ENGINE: ");
  switch(_SIMPLEX_ENGINE)
    {
    case _GLPK:
      fprintf(f,"glpk\n");
      break;
    case _CLP:
      fprintf(f,"clp\n");
      break;
    case _LP_SOLVE:
      fprintf(f,"lp_solve\n");
      break;
    case _GUROBI:
      fprintf(f,"gurobi\n");
      break;
    default:
      fprintf(f,"unknown\n");
    }
  fprintf(f,"%%   MPI: %u\n",_USE_MPI);
  #ifdef _OPENMP
    fprintf(f,"%%   OpenMP: 1\n");
  #else
    fprintf(f,"%%   OpenMP: 0\n");
  #endif
  #ifdef _LAPACK
    fprintf(f,"%%   Lapack: 1\n");
  #else
    fprintf(f,"%%   Lapack: 0\n");
  #endif
  #ifdef _CBLAS
    fprintf(f,"%%   Cblas: 1\n");
  #else
    fprintf(f,"%%   Cblas: 0\n");
  #endif
  fprintf(f,"%%   KDTree: %u\n",_KDTREE);
  fprintf(f,"%%\n");
  fprintf(f,"%% PARAMETERS:\n");
  for(i=0;i<NPARAMETERS;i++)
    {
      if ((*p)[i].name!=NULL)
	{
	  fprintf(f,"   %s = ",(*p)[i].name);
	  switch(i)
	    {
	    case CT_REPRESENTATION:
	      v=(unsigned int)(*p)[i].value;
	      switch (v)
		{
		case REP_LINKS:
		  fprintf(f,"LINKS");
		  break;
		case REP_FLINKS:
		  fprintf(f,"FLINKS");
		  break;
		case REP_QLINKS:
		  fprintf(f,"QLINKS");
		  break;
		case REP_JOINTS:
		  fprintf(f,"JOINTS");
		  break;
		default:
		  Error("Wrong value for parameter REPRESENTATION");
		}
	      break;
	    case CT_SPLIT_TYPE:
	      v=(unsigned int)(*p)[i].value;
	      fprintf(f,"%u",v); 		
	      break;
	    case CT_SAMPLING:
	      v=(unsigned int)(*p)[i].value;
	      switch (v)
		{
		case AMBIENT_SAMPLING:
		  fprintf(f,"AMBIENT_SAMPLING");
		  break;
		case KDTREE_SAMPLING:
		  fprintf(f,"KDTREE_SAMPLING");
		  break;
		case TANGENT_SAMPLING:
		  fprintf(f,"TANGENT_SAMPLING");
		  break;
		default:
		  Error("Wrong value for parameter SAMPLING");
		}
	      break;
	    case CT_CD_ENGINE:
	      v=(unsigned int)(*p)[i].value;
	      switch (v)
		{
		case SOLID:
		  fprintf(f,"SOLID");
		  break;
		case VCOLLIDE:
		  fprintf(f,"VCOLLIDE");
		  break;
		case PQP:
		  fprintf(f,"PQP");
		  break;
		case FCL:
		  fprintf(f,"FCL");
		  break;
		case C_FCL:
		  fprintf(f,"C_FCL");
		  break;
		case RIGIDCLL:
		  fprintf(f,"RIGIDCLL");
		  break;
		case NOCD:
		  fprintf(f,"NONE");
		  break;
		default:
		  Error("Wrong value for parameter CD_ENGINE");
		}
	      break;
	    case CT_CUT_X:
	    case CT_CUT_Y:
	    case CT_CUT_Z:
	      if ((*p)[i].value==INF)
		fprintf(f,"+INF");
	      else
		{
		  if ((*p)[i].value==-INF)
		    fprintf(f,"-INF");
		  else
		    fprintf(f,"%g",(*p)[i].value); 
		}
	      break;
	    case CT_G_AXIS:
	      v=(unsigned int)(*p)[i].value;
	      switch (v)
		{
		case 0:
		  fprintf(f,"0"); // no gravity
		  break;
                case 1:
		  fprintf(f,"X");
		  break;
                case 2:
		  fprintf(f,"Y");
		  break;
                case 3:
		  fprintf(f,"Z");
		  break;
                case 4:
		  fprintf(f,"-X");
		  break;
                case 5:
		  fprintf(f,"-Y");
		  break;
                case 6:
		  fprintf(f,"-Z");
		  break;
		default:
		  Error("Wrong value for parameter CD_G_AXIS");
                }
	      break;
	    default:
	      fprintf(f,"%g",(*p)[i].value); 
	    }
	  fprintf(f,"\n");
	}
    }
}

void DeleteParameters(Tparameters *p)
{
}
 
