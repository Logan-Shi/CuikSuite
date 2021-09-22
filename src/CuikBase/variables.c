#include "variables.h"

#include "error.h"
#include "boolean.h"
#include "defines.h"

#include <stdlib.h>
#include <string.h>


/** 
   \file variables.c

   \brief Implementation of the functions operating on box Tvariables. 

   Implementation of the functions operating on box Tvariables. 

   \sa Tvariables, variables.h.
*/

/*
 * Init the set of variables.
 */
void InitVariables(Tvariables *vs)
{
  unsigned int i;

  vs->max_variables=INIT_NUM_VARIABLES;
  NEW(vs->vs,vs->max_variables,Tvariable *);
  vs->n=0; /*total*/
  vs->sys=0; /*system*/
  vs->sec=0; /*secondary*/
  vs->dum=0; /*dummies*/
  vs->car=0; /*cartesian*/
  vs->vel=0; /*velocity*/
  vs->ndy=0; /*non-dynamic*/

  for(i=0;i<vs->max_variables;i++)
    vs->vs[i]=NULL;
}

void CopyVariables(Tvariables *vs_dst,Tvariables *vs_src)
{
  unsigned int i;

  vs_dst->sys=vs_src->sys;
  vs_dst->sec=vs_src->sec;
  vs_dst->dum=vs_src->dum;
  vs_dst->car=vs_src->car;
  vs_dst->vel=vs_src->vel;
  vs_dst->ndy=vs_src->ndy;

  vs_dst->n=vs_src->n;

  vs_dst->max_variables=vs_src->max_variables;
  NEW(vs_dst->vs,vs_dst->max_variables,Tvariable *);

  for(i=0;i<vs_src->max_variables;i++)
    {
      if (vs_src->vs[i]!=NULL)
	{
	  NEW(vs_dst->vs[i],1,Tvariable);
	  CopyVariable(vs_dst->vs[i],vs_src->vs[i]);
	}
      else
	vs_dst->vs[i]=NULL;
    }
}

/*
 * Returns the number of variables included in the set 'vs'
 */
unsigned int NVariables(Tvariables *vs)
{
  return(vs->n);
}

/*
 * Returns the number of cartesian  variables
 */
unsigned int GetNumCartesianVariables(Tvariables *vs)
{
  return(vs->car);
}

unsigned int GetNumDummyVariables(Tvariables *vs)
{
  return(vs->dum);
}

unsigned int GetNumPositionVariables(Tvariables *vs)
{
  return(vs->n-vs->vel-vs->ndy);
}

unsigned int GetNumVelocityVariables(Tvariables *vs)
{
  return(vs->vel);
}

unsigned int GetNumNonDynamicVariables(Tvariables *vs)
{
  return(vs->ndy);
}

/*
 * Returns the number of system  variables
 */
unsigned int GetNumSystemVariables(Tvariables *vs)
{
  return(vs->sys);
}

/*
 * Returns the number of secondary  variables
 */
unsigned int GetNumSecondaryVariables(Tvariables *vs)
{
  return(vs->sec);
}

boolean IsSystemVariable(unsigned int n,Tvariables *vs)
{  
  return((n<vs->n)&&(GetVariableType(vs->vs[n])==SYSTEM_VAR));
}

boolean IsSecondaryVariable(unsigned int n,Tvariables *vs)
{  
  return((n<vs->n)&&(GetVariableType(vs->vs[n])==SECONDARY_VAR));
}

boolean IsDummyVariable(unsigned int n,Tvariables *vs)
{
  return((n<vs->n)&&(GetVariableType(vs->vs[n])==DUMMY_VAR));
}

boolean IsCartesianVariable(unsigned int n,Tvariables *vs)
{
  return((n<vs->n)&&(GetVariableType(vs->vs[n])==CARTESIAN_VAR));
}

boolean IsPositionVariable(unsigned int n,Tvariables *vs)
{
  return((n<vs->n)&&
	 (GetVariableType(vs->vs[n])!=VELOCITY_VAR)&&
	 (GetVariableType(vs->vs[n])!=NON_DYNAMIC_VAR));
}

boolean IsVelocityVariable(unsigned int n,Tvariables *vs)
{
  return((n<vs->n)&&(GetVariableType(vs->vs[n])==VELOCITY_VAR));
}

boolean IsNonDynamicVariable(unsigned int n,Tvariables *vs)
{
  return((n<vs->n)&&(GetVariableType(vs->vs[n])==NON_DYNAMIC_VAR));
}

unsigned int GetVariableTypeN(unsigned int n,Tvariables *vs)
{
  if (n>=vs->n)
    Error("Unknown variable ID in GetVariableTypeN");

  return(GetVariableType(vs->vs[n]));
}

/*
 * Add a new variable (pointed by 'v') to the set 'vs'.
 * If 'v' has the same name of an already existing variable in 'vs' and error is issued (and
 * the program stopped).
 * Returns the ID assigned to this variable (the position where it is inserted) and not its order
 * in the set (first, second,...)
 */
unsigned int AddVariable(Tvariable *v,Tvariables *vs)
{
  if (GetVariableWithName(GetVariableName(v),vs)!=NULL)
    Error("Duplicated variable");
  else
    {
      unsigned int t;
      
      /*look for a  free position*/
      if (vs->n==vs->max_variables)
	{
	  unsigned int i,k;

	  k=vs->max_variables;
	  MEM_DUP(vs->vs,vs->max_variables,Tvariable *);
	  for(i=k;i<vs->max_variables;i++)
	    vs->vs[i]=NULL;
	}

      NEW(vs->vs[vs->n],1,Tvariable);
      CopyVariable(vs->vs[vs->n],v);

      t=GetVariableType(v);

      if (t==SYSTEM_VAR) vs->sys++;
      if (t==SECONDARY_VAR) vs->sec++;
      if (t==DUMMY_VAR) vs->dum++;
      if (t==CARTESIAN_VAR) vs->car++;
      if (t==VELOCITY_VAR) vs->vel++;
      if (t==NON_DYNAMIC_VAR) vs->ndy++;
      vs->n++;
    }
  return(vs->n-1);
}

/*
 * Returns a pointer to the variable description of the variable with the given 'name'
 * If there is no variable with that name NULL is returned.
 */
Tvariable *GetVariableWithName(char *name,Tvariables *vs)
{
  unsigned int i;

  i=GetVariableID(name,vs);
  if (i==NO_UINT)
    return(NULL);
  else
    return(vs->vs[i]);
}

/*
 * Returns a pointer to the variable with n
 */ 
Tvariable *GetVariable(unsigned int n,Tvariables *vs)
{
  if (n>=vs->n)
    Error("Undefined variable referenced in function GetVariable");

  return(vs->vs[n]);    
}

/*
 * Returns the ID of variable with name 'name'.
 * returns -1 if there is no variable with this name
 */
unsigned int GetVariableID(char *name,Tvariables *vs)
{
  boolean found;
  unsigned int i;

  found=FALSE;
  i=0;
  while((!found)&&(i<vs->n))
    {
      if (strcmp(name,GetVariableName(vs->vs[i]))==0)
	found=TRUE;
      else
	i++;
    }
  
  if (found)
    return(i);
  else
    return(NO_UINT);
}

unsigned int GetVariablesTopology(unsigned int **t,Tvariables *vs)
{
  unsigned int i;

  NEW(*t,vs->n,unsigned int);

  for(i=0;i<vs->n;i++)
    (*t)[i]=GetVariableTopology(vs->vs[i]);

  return(vs->n);
}

void GetVariableNames(char **varNames,Tvariables *vs)
{
  unsigned int i;
  
  for(i=0;i<vs->n;i++)
    varNames[i]=GetVariableName(vs->vs[i]);
}

char *VariableName(unsigned int i,Tvariables *vs)
{
  if (i<vs->n)
    return(GetVariableName(vs->vs[i]));
  else
    return(NULL);
}

/*
 * Remove a variable from the set.
 * WARNING: if you remove a variable from a set used in a
 * cuiksystem without removing the variable from all the
 * equations (for instance, by fixing it to zero) you
 * will generate an inconsistency on the cuiksystem
 */
void RemoveVariable(unsigned int n,Tvariables *vs)
{ 
  if (n<vs->n)
    {
      unsigned int i,t;
      
      t=GetVariableType(vs->vs[n]);
      
      DeleteVariable(vs->vs[n]);
      free(vs->vs[n]);

      for(i=n+1;i<vs->n;i++)
	vs->vs[i-1]=vs->vs[i];
      vs->vs[vs->n-1]=NULL;

      if (t==SYSTEM_VAR) vs->sys--;
      if (t==SECONDARY_VAR) vs->sec--;
      if (t==DUMMY_VAR) vs->dum--;
      if (t==CARTESIAN_VAR) vs->car--;
      if (t==VELOCITY_VAR) vs->vel--;
      if (t==NON_DYNAMIC_VAR) vs->ndy--;
      vs->n--;
    }
}

/*
  Define the initial search space from a set of variables
*/
void BoxFromVariables(Tbox *b,Tvariables *vs)
{
  unsigned int i,n;

  n=NVariables(vs);
  InitBox(n,NULL,b);

  for(i=0;i<n;i++) 
    SetBoxInterval(i,GetVariableInterval(GetVariable(i,vs)),b);
}

void PointFromVariables(double **p,Tvariables *vs)
{
  unsigned int i,n;

  n=NVariables(vs);
  NEW(*p,n,double);

  for(i=0;i<n;i++) 
    (*p)[i]=IntervalCenter(GetVariableInterval(GetVariable(i,vs)));
}

void VariablesFromBox(Tbox *b,Tvariables *vs)
{
  unsigned int i,n;

  n=NVariables(vs);

  for(i=0;i<n;i++) 
    SetVariableInterval(GetBoxInterval(i,b),GetVariable(i,vs));
}

/*
 * Prints the set of variables 'vs' on the file 'f'
 */
void PrintVariables(FILE *f,Tvariables *vs)
{
  unsigned int i;
  unsigned int t,tn;

  for(i=0;i<vs->n;i++)
    {
      tn=GetVariableType(GetVariable(i,vs));
      if ((i==0)||(t!=tn))
	{
	  switch (tn)
	    {
	    case SYSTEM_VAR:
	      fprintf(f,"\n[SYSTEM VARS]\n");
	      break;
	    case NON_DYNAMIC_VAR:
	      fprintf(f,"\n[NON DYNAMIC VARS]\n");
	      break;
	    case SECONDARY_VAR:
	      fprintf(f,"\n[SECONDARY VARS]\n");
	      break;
	    case DUMMY_VAR:
	      fprintf(f,"\n[DUMMY VARS]\n");
	      break;
	    case CARTESIAN_VAR:
	      fprintf(f,"\n[CARTESIAN VARS]\n");
	      break;
	    case VELOCITY_VAR:
	      fprintf(f,"\n[VELOCITY VARS]\n");
	      break;
	    default:
	      Error("Unknown variable type in PrintVariables");
	    }
	}
      fprintf(f,"   ");PrintVariable(f,vs->vs[i]);fprintf(f,"\n");//fprintf(f," %% %u\n",i);
      t=tn;
    }
}

/*
 * Deletes the set of variables 'vs' (recursively deleting all the included variables).
 */
void DeleteVariables(Tvariables *vs)
{
  unsigned int i;

  for(i=0;i<vs->n;i++)
    {
      DeleteVariable(vs->vs[i]);
      free(vs->vs[i]);
    }
  free(vs->vs);
  vs->vs=NULL;
}

