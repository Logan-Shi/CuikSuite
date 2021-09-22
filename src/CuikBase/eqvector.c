#include "eqvector.h"

#include "htransform.h"

/** 
    \file eqvector.c

    \brief Implementation of the TEqVEctor type and the associated functions.

    Implementation of the module to manage symbolic vectors in R^3.

    \sa eqvector.c, TEqVector.
*/

void InitEqVector(TEqVector *ev)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    InitEquation(&((*ev)[i]));
}

void CopyEqVector(TEqVector *ev_dst,TEqVector *ev_src)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    CopyEquation(&((*ev_dst)[i]),&((*ev_src)[i]));
}

void EqVectorFromVector(double *v,TEqVector *ev)
{
  unsigned int i;

  InitEqVector(ev);

  for(i=0;i<DIM_SP;i++)
    SetEquationValue(-v[i],&((*ev)[i]));
}

Tequation *GetEqVectorElement(unsigned int i,TEqVector *ev)
{
  if (i<DIM_SP)
    return(&((*ev)[i]));
  else
    {
      Error("Index out of range in GetEqVectorElement");
      return(NULL);
    }
}

void ScaleEqVector(double ct,TEqVector *ev)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    CtScaleEquation(ct,&((*ev)[i]));
}

void VarScaleEqVector(unsigned int v,TEqVector *ev)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    VarScaleEquation(v,&((*ev)[i]));
}

void AccumulateEqVectors(TEqVector *ev,double ct,TEqVector *evOut)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    AccumulateEquations(&((*ev)[i]),ct,&((*evOut)[i])); 
}

void VarAccumulateEqVectors(TEqVector *ev,unsigned int v,TEqVector *evOut)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    VarAccumulateEquations(&((*ev)[i]),v,&((*evOut)[i]));  
}

void VarAccumulateVector2EqVector(double *c,unsigned int v,TEqVector *evOut)
{
  unsigned int i;
  Tmonomial f;

  InitMonomial(&f);
  for(i=0;i<DIM_SP;i++)
    {
      AddCt2Monomial(c[i],&f);
      AddVariable2Monomial(NFUN,v,1,&f);
      AddMonomial(&f,&((*evOut)[i]));
      ResetMonomial(&f);
    }
  DeleteMonomial(&f);
}

void Var2AccumulateVector2EqVector(double *c,unsigned int v1,
				   unsigned int v2,TEqVector *evOut)
{
  unsigned int i;
  Tmonomial f;

  InitMonomial(&f);
  for(i=0;i<DIM_SP;i++)
    {
      AddCt2Monomial(c[i],&f);
      AddVariable2Monomial(NFUN,v1,1,&f);
      AddVariable2Monomial(NFUN,v2,1,&f);
      AddMonomial(&f,&((*evOut)[i]));
      ResetMonomial(&f);
    }
  DeleteMonomial(&f);
}

void AccumulateVector2EqVector(double *v,TEqVector *ev)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    SetEquationValue(GetEquationValue(&((*ev)[i]))-v[i],&((*ev)[i]));
}

void CrossProductEqVectors(TEqVector *ev1,TEqVector *ev2,TEqVector *evOut)
{
  Tequation eq;
  TEqVector ev;

  ProductEquations(&((*ev1)[1]),&((*ev2)[2]),&(ev[0]));
  ProductEquations(&((*ev1)[2]),&((*ev2)[1]),&eq);
  AccumulateEquations(&eq,-1.0,&(ev[0])); 
  DeleteEquation(&eq);
  
  ProductEquations(&((*ev1)[2]),&((*ev2)[0]),&(ev[1]));
  ProductEquations(&((*ev1)[0]),&((*ev2)[2]),&eq);
  AccumulateEquations(&eq,-1.0,&(ev[1])); 
  DeleteEquation(&eq);

  ProductEquations(&((*ev1)[0]),&((*ev2)[1]),&(ev[2]));
  ProductEquations(&((*ev1)[1]),&((*ev2)[0]),&eq);
  AccumulateEquations(&eq,-1.0,&(ev[2])); 
  DeleteEquation(&eq);

  if ((evOut==ev1)||(evOut==ev2))
    DeleteEqVector(evOut);
  CopyEqVector(evOut,&ev);
  DeleteEqVector(&ev);
}

void CrossProductVectorEqVector(double *v,TEqVector *ev,TEqVector *evOut)
{
  TEqVector evAux;

  CopyEquation(&(evAux[0]),&((*ev)[2]));
  CtScaleEquation(v[1],&(evAux[0]));
  AccumulateEquations(&((*ev)[1]),-v[2],&(evAux[0]));

  CopyEquation(&(evAux[1]),&((*ev)[0]));
  CtScaleEquation(v[2],&(evAux[1]));
  AccumulateEquations(&((*ev)[2]),-v[0],&(evAux[1]));

  CopyEquation(&(evAux[2]),&((*ev)[1]));
  CtScaleEquation(v[0],&(evAux[2]));
  AccumulateEquations(&((*ev)[0]),-v[1],&(evAux[2]));
  
  if (evOut==ev)
    DeleteEqVector(evOut);
  CopyEqVector(evOut,&evAux);
  DeleteEqVector(&evAux);
}


void DotProductEqVectors(TEqVector *ev1,TEqVector *ev2,Tequation *eqOut)
{
  unsigned int i;
  Tequation eq;

  InitEquation(eqOut);

  for(i=0;i<DIM_SP;i++)
    {
      ProductEquations(&((*ev1)[i]),&((*ev2)[i]),&eq);
      AccumulateEquations(&eq,1.0,eqOut); 
      DeleteEquation(&eq);
    }
}

void DotProductVectorEqVector(double *v,TEqVector *ev,Tequation *eqOut)
{
  CopyEquation(eqOut,&((*ev)[0]));
  CtScaleEquation(v[0],eqOut);
  AccumulateEquations(&((*ev)[1]),v[1],eqOut);
  AccumulateEquations(&((*ev)[2]),v[2],eqOut);
}

void EvaluateEqVector(double *v,double *o,TEqVector *ev)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    o[i]=EvaluateWholeEquation(v,&((*ev)[i]));
}

void EvaluateEqVectorInt(Tinterval *v,Tinterval *o,TEqVector *ev)
{
  double ct;
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    {
      ct=GetEquationValue(&((*ev)[i]));
      EvaluateEquationInt(v,&(o[i]),&((*ev)[i]));
      IntervalOffset(&(o[i]),-ct,&(o[i]));
    }
}

void DeleteEqVector(TEqVector *ev)
{
  unsigned int i;

  for(i=0;i<DIM_SP;i++)
    DeleteEquation(&((*ev)[i]));
}

