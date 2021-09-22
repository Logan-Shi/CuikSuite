#include "kequation.h"

#include "equation.h"
#include "linear_constraint.h"
#include "error.h"
#include "defines.h"

/** 
    \file kequation.c
 
    \brief Implementation of the kino-equation operations.

     Implementation of the kino-equation operations.

    \sa TKequation, kequation.h.
*/


void InitKEquation(TKequation *ke)
{
  InitVector(sizeof(Tequation*),CopyVoidPtr,DeleteVoidPtr,INIT_SIZE_KEQ,&(ke->a));
}

void AddFactor2KEquation(unsigned int i,Tequation *f,TKequation *ke)
{
  if (f!=NULL)
    {
      Tequation *eq;
      
      NEW(eq,1,Tequation);
      CopyEquation(eq,f);
      SetEquationCmp(EQU,eq); /* Just in not set yet */
      SetEquationType(DERIVED_EQ,eq); /* Just in case not set yet */
      SetVectorElement(i,&eq,&(ke->a));
    }
}

Tequation *GetFactorFromKEquation(unsigned int i,TKequation *ke)
{
  Tequation **eq;
  
  eq=(Tequation **)GetVectorElement(i,&(ke->a));
  if ((eq==NULL)||(EmptyEquation(*eq)))
    return(NULL);
  else
    return(*eq);
}

void CopyKEquation(TKequation *ke_dst,TKequation *ke_src)
{
  unsigned int i,n;
  Tequation **eq;

  n=VectorSize(&(ke_src->a));
  InitVector(sizeof(Tequation*),CopyVoidPtr,DeleteVoidPtr,n,&(ke_dst->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke_src->a));
      if (eq!=NULL)
	AddFactor2KEquation(i,*eq,ke_dst);
    }
}

void RewriteKinoEquation2Orig(Tmapping *map,TKequation *ke)
{
  unsigned int n,i;
  Tequation **eq;
  
  n=VectorSize(&(ke->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	RewriteEquation2Orig(map,*eq);
    }
}

boolean VarIncludedinKEquation(unsigned int nv,TKequation *ke)
{
  unsigned int i,n;
  Tequation **eq;
  boolean found;

  /* if nv' has a non-null factor -> the variable is used */
  eq=(Tequation **)GetVectorElement(nv,&(ke->a));
  found=((eq!=NULL)&&(!EmptyEquation(*eq)));

  /* if nv appears inside any factor -> the variable is used */
  n=VectorSize(&(ke->a));
  for(i=0;((!found)&&(i<n));i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	found=VarIncluded(nv,GetEquationVariables(*eq));
    }
  
  return(found);
}

void ShiftVariablesInKEquation(unsigned int nv,TKequation *ke)
{
  unsigned int i,n;
  Tequation **eq;

  n=VectorSize(&(ke->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	{
	  if ((i==nv)&&(!EmptyEquation(*eq)))
	    Error("Removing a used var from a kino-equation");
	  if (VarIncluded(nv,GetEquationVariables(*eq)))
	    Error("Removing a used var from a kino-equation");

	  /* shift down the variables with index >nv in the factor */
	  FixVariableInEquation(0.0,nv,1,*eq); /* just to shift the indices of variables above 'nv' */
	  
	  if (i>=nv)
	    {
	      if (i==nv)
		DeleteEquation(*eq); /* relase space from a empty equation */
	      else
		SetVectorElement(i-1,eq,&(ke->a));
	      
	      RemoveVectorElement(i,&(ke->a));
	    }
	}
    }
}

void FixVarInKEquation(double epsilon,unsigned int nv,double ct,TKequation *ke)
{
  unsigned int i,n;
  Tequation **eq;

  n=VectorSize(&(ke->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	{
	  if (i!=nv)
	    FixVariableInEquation(epsilon,nv,ct,*eq); 
	  
	  if (i>=nv)
	    {
	      if (i==nv)
		DeleteEquation(*eq); 
	      else
		SetVectorElement(i-1,eq,&(ke->a));
	      
	      RemoveVectorElement(i,&(ke->a));
	    }
	}
    }
}

void ReplaceVarInKEquation(double epsilon,unsigned int nv,unsigned int nvNew,TKequation *ke)
{
  unsigned int i,n;
  Tequation **eq,**eqNew;
  TLinearConstraint lc;

  if (nv==nvNew)
    Error("Self-replacement in ReplaceVarInKEquation");

  /*
    The kino equations is \sum_i f_i v_i'
    If we have v_i=v_j then in the sum v_i' appears two times
    (the one for v_i and the one for v_j). Thus, the two factors
    need to be added and v_j can be removed.

    In the parameters i=nvNew (the variable to be used in the replacement) 
    and j=nv (the replaced variable)
   */
  eq=(Tequation **)GetVectorElement(nv,&(ke->a));
  eqNew=(Tequation **)GetVectorElement(nvNew,&(ke->a));
  if (eq!=NULL)
    {
      if (eqNew==NULL)
	{
	  NEW(*eqNew,1,Tequation);
	  CopyEquation(*eqNew,*eq);
	  SetVectorElement(nvNew,eqNew,&(ke->a));
	}
      else
	AccumulateEquations(*eq,1.0,*eqNew);
      
      /* Revove factor nv */
      DeleteEquation(*eq);
    }
  /* compact the factor vector */
  RemoveVectorElement(nv,&(ke->a));
  n=VectorSize(&(ke->a));
  for(i=nv+1;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	SetVectorElement(i-1,eq,&(ke->a));
      RemoveVectorElement(i,&(ke->a));
    }

  /* Moreover, if v_i appars in any factor, we have to replace it too */
  InitLinearConstraint(&lc);
  AddTerm2LinearConstraint(nvNew,1,&lc);
  
  n=VectorSize(&(ke->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	ReplaceVariableInEquation(epsilon,nv,&lc,*eq); 
    }
  DeleteLinearConstraint(&lc); 
}


void PrintKEquation(FILE *f,char **varNames,TKequation *ke)
{
  unsigned int i,n;
  Tequation **eq;
  boolean first;

  first=TRUE;
  fprintf(f,"   ");
  n=VectorSize(&(ke->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if ((eq!=NULL)&&(!EmptyEquation(*eq)))
	{
	  if (!first)
	    fprintf(f,"+");
	  fprintf(f,"(");
	  PrintMonomialsInLine(f,varNames,*eq);
	  fprintf(f,")*");
	  if (varNames!=NULL)
	    PRINT_VARIABLE_NAME(f,varNames[i]);
	  else
	    fprintf(f,"v_%u",i);
	  fprintf(f,"'");
	  first=FALSE;
	}
    }
  fprintf(f,"=0;\n");
}

void ResetKEquation(TKequation *ke)
{
  unsigned int i,n;
  Tequation **eq;

  n=VectorSize(&(ke->a));
  for(i=0;i<n;i++)
    {
      eq=(Tequation **)GetVectorElement(i,&(ke->a));
      if (eq!=NULL)
	{
	  DeleteEquation(*eq);
	  free(*eq);
	}
    }
  ResetVector(&(ke->a)); 
}

void DeleteKEquation(TKequation *ke)
{
  ResetKEquation(ke);
  DeleteVector(&(ke->a));
}
