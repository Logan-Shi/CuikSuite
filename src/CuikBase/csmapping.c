#include "csmapping.h"
#include "defines.h"

#include <math.h>

/** \file csmapping.c
    \brief Implementation of the functions operating on Tmapping.

    Implementation of the functions operating on Tmapping.

    \sa Tmapping, csmapping.h.
*/

void InitMapping(Tvariables *o,Tvariables *s,Tmapping *m)
{
  unsigned int i,vID;

  NEW(m->original,1,Tvariables);
  CopyVariables(m->original,o);
  NEW(m->simple,1,Tvariables);
  CopyVariables(m->simple,s);

  m->sizeO=NVariables(o); /* The number of variables is cached */
  m->sizeS=NVariables(s);

  /*
    Some of the variables in the simple system are included in the original one.
    This is a one to one relation and, thus, it can be straighforwardly defined.
    However this is of little use (only used in GetVarIDInOriginal)
  */
  NEW(m->orig,m->sizeS,unsigned int);

  for(i=0;i<m->sizeS;i++)
    {
      /* this can be NO_UINT if the variable in the simplified system is not
         in the original one (ex. dummies!!)*/
      m->orig[i]=GetVariableID(GetVariableName(GetVariable(i,s)),o);
    }

  /* 
     The variables in the original system can be not linked to any variable in the
     simple system or be linearly related with a variable in the simple system.
     Observe that identity (copy) is a form of linear relation (with ct 1 and offest 0).
     Only this last relation (identity) can be automatically detected and set.
     Other type of relations have to be set by upper levels (using 'SetOriginalVarRelation').
  */
  NEW(m->related,m->sizeO,boolean);
  NEW(m->lc,m->sizeO,TLinearConstraint);

  for(i=0;i<m->sizeO;i++)
    {
      vID=GetVariableID(GetVariableName(GetVariable(i,o)),s);

      m->related[i]=(vID!=NO_UINT);
      InitLinearConstraint(&(m->lc[i]));
      if (m->related[i])
	{
	  /* Var 'i' in the original system is var vID in the simplified one */
	  AddTerm2LinearConstraint(vID,1,&(m->lc[i]));
	}
    }
}

void CopyMapping(Tmapping *m_dst,Tmapping *m_src)
{
  unsigned int i;

  if (m_src->original==NULL)
    m_dst->original=NULL;
  else
    {
      NEW(m_dst->original,1,Tvariables);
      CopyVariables(m_dst->original,m_src->original);
    }

  if (m_src->simple==NULL)
    m_dst->simple=NULL;
  else
    {
      NEW(m_dst->simple,1,Tvariables);
      CopyVariables(m_dst->simple,m_src->simple);
    }

  m_dst->sizeO=m_src->sizeO;
  m_dst->sizeS=m_src->sizeS;

  NEW(m_dst->orig,m_dst->sizeS,unsigned int);
  for(i=0;i<m_src->sizeS;i++)
    m_dst->orig[i]=m_src->orig[i];

  NEW(m_dst->related,m_dst->sizeO,boolean);
  NEW(m_dst->lc,m_dst->sizeO,TLinearConstraint);
  for(i=0;i<m_src->sizeO;i++)
    {
      m_dst->related[i]=m_src->related[i];
      CopyLinearConstraint(&(m_dst->lc[i]),&(m_src->lc[i]));
    }
}

void SetOriginalVarRelation(unsigned int nvo,TLinearConstraint *lc,Tmapping *m)
{
  if (nvo<m->sizeO)
    {
      m->related[nvo]=TRUE;
      DeleteLinearConstraint(&(m->lc[nvo]));
      CopyLinearConstraint(&(m->lc[nvo]),lc);
    }
  else
    Error("Var index out of range in SetOriginalVarRelation");
}

void GetOriginalVarRelation(unsigned int nvo,TLinearConstraint *lc,Tmapping *m)
{
  if (m->related[nvo])
    CopyLinearConstraint(lc,&(m->lc[nvo]));
  else
    InitLinearConstraint(lc);
}

unsigned int GetSizeOriginal(Tmapping *m)
{
  return(m->sizeO);
}

unsigned int GetSizeSimple(Tmapping *m)
{
  return(m->sizeS);
}

boolean IsInSimple(unsigned int v,Tmapping *m)
{
  return(GetVariableID(GetVariableName(GetVariable(v,m->original)),m->simple)!=NO_UINT);
}

unsigned int GetVarIDInOriginal(unsigned int v,Tmapping *m)
{
  if (v<m->sizeS)
    return(m->orig[v]);
  else
    return(NO_UINT);
}

void SimpleFromOriginal(Tbox *o,Tbox *s,Tmapping *m)
{
  /* The same variable in the system */
  /* All ranges in the simple box change (recall that the
     simple system is a strict subset of the original system) */

  /*When applying this mapping the information in 'o' is considered the
    most up to date and, thus, the one in 's' is discarted*/

  /*When accumulating (intersecting) the several constraints that define the 
    range for the variables in the simple system we can discover that there
    is no solution (empty intersection)*/
  unsigned int i;

  BoxFromVariables(s,m->simple);
  for(i=0;i<m->sizeS;i++)
    {
      if (m->orig[i]!=NO_UINT)
	CopyInterval(GetBoxInterval(i,s),GetBoxInterval(m->orig[i],o));
    }
}

void SimplePointFromOriginal(double *o,double **s,Tmapping *m)
{
  unsigned int i;

  PointFromVariables(s,m->simple);
  for(i=0;i<m->sizeS;i++)
    {
      if (m->orig[i]!=NO_UINT)
	(*s)[i]=o[m->orig[i]];
    }
}

void UpdateOriginalFromSimple(Tbox *s,Tbox *o,Tmapping *m)
{
  unsigned int i;
  Tinterval r,rc,e,*is;

  is=GetBoxIntervals(s);
  for(i=0;i<m->sizeO;i++)
    {
      if (m->related[i])
	{
	  EvaluateLinearConstraintInt(is,&r,&(m->lc[i]));
	  GetLinearConstraintError(&e,&(m->lc[i]));
	  IntervalInvert(&e,&e);
	  IntervalAdd(&e,&r,&r);
	  if (Intersection(GetBoxInterval(i,o),&r,&rc))
	    SetBoxInterval(i,&rc,o);
	  else
	    SetBoxInterval(i,&r,o);   
	}
    }
}

void UpdateOriginalPointFromSimple(double *s,double *o,Tmapping *m)
{
  unsigned int i;
  Tinterval e;

  for(i=0;i<m->sizeO;i++)
    {
      if (m->related[i])
	{
	  GetLinearConstraintError(&e,&(m->lc[i]));
	  o[i]=EvaluateLinearConstraint(s,&(m->lc[i]))-IntervalCenter(&e);
	}
    }
}

/* Since all variables in simple are also in original, the only information
   relevant to be printed in how the variables in the original system
   depend on those in the simple one
*/
void PrintMapping(FILE *f,Tmapping *m)
{
  unsigned int i;
  char *n;
  char **varNamesO,**varNamesS;

  if (m->original==NULL)
    varNamesO=NULL;
  else
    {
      NEW(varNamesO,m->sizeO,char *);
      GetVariableNames(varNamesO,m->original);
    }

  if (m->simple==NULL)
    varNamesS=NULL;
  else
    {
      NEW(varNamesS,m->sizeS,char *);
      GetVariableNames(varNamesS,m->simple);
    }

  for(i=0;i<m->sizeO;i++)
    {
      fprintf(f,"%%   ");
      if (varNamesO==NULL)
	fprintf(f,"v_%u",i);
      else
	{
	  n=varNamesO[i];
	  PRINT_VARIABLE_NAME(f,n);
	}
      fprintf(f,"=");
      if (m->related[i])
	PrintLinearConstraint(f,FALSE,varNamesS,&(m->lc[i]));
      else
	{
	  //PRINT_VARIABLE_NAME(f,n);
	  fprintf(f,"No in simplification\n");
	}
    } 
  if (varNamesO!=NULL)
    free(varNamesO);
  
  if (varNamesS!=NULL)
    free(varNamesS);
}

void LoadMapping(FILE *f,Tmapping *m)
{
  unsigned int i;

  m->original=NULL;
  m->simple=NULL;

  fscanf(f,"%u",&(m->sizeS));
  NEW(m->orig,m->sizeS,unsigned int);
  for(i=0;i<m->sizeS;i++)
    fscanf(f,"%u ",&(m->orig[i]));
  
  fscanf(f,"%u",&(m->sizeO));
  NEW(m->related,m->sizeO,boolean);
  NEW(m->lc,m->sizeO,TLinearConstraint);
  for(i=0;i<m->sizeO;i++)
    {
      fprintf(f,"%u",m->related[i]);
      if (m->related[i])
	LoadLinearConstraint(f,&(m->lc[i]));
      else
	InitLinearConstraint(&(m->lc[i]));
    }
}

void SaveMapping(FILE *f,Tmapping *m)
{
  unsigned int i;

  fprintf(f,"%u\n",m->sizeS);
  for(i=0;i<m->sizeS;i++)
    fprintf(f,"%u ",m->orig[i]);
  fprintf(f,"\n");

  fprintf(f,"%u\n",m->sizeO);
  for(i=0;i<m->sizeO;i++)
    {
      fprintf(f,"%u ",m->related[i]);
      if (m->related[i])
	SaveLinearConstraint(f,&(m->lc[i]));
      fprintf(f,"\n");
    } 
}

void DeleteMapping(Tmapping *m)
{
  unsigned int i;

  if (m->original!=NULL)
    {
      DeleteVariables(m->original);
      free(m->original);
    }

  if (m->simple!=NULL)
    {
      DeleteVariables(m->simple);
      free(m->simple);
    }

  free(m->orig);
  for(i=0;i<m->sizeO;i++)
    DeleteLinearConstraint(&(m->lc[i]));
  free(m->lc);
  free(m->related);
}

