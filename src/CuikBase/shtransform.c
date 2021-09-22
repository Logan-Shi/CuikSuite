#include "shtransform.h"

#include <math.h>

/** 
    \file shtransform.c

    \brief Implementation of the TSHTransform type and the associated functions.

    Implementation of the module to manage symbolic homogeneous transforms 
    in R^3.

    \sa shtransform.c, TSHTransform, THTransform.
*/

/** 
   \brief Initializes an empty symbolic transform.

   Initializes an empty symbolic transform.

   \param t The transform to initialize.
*/
void SHTransformInit(TSHTransform *t);

void SHTransformInit(TSHTransform *t)
{
  unsigned int i,j;

  NEW((*t),(DIM_SP+1),Tequation**);
  for(i=0;i<(DIM_SP+1);i++)
    {
      NEW((*t)[i],(DIM_SP+1),Tequation*);
      for(j=0;j<(DIM_SP+1);j++)
	{
	  NEW((*t)[i][j],1,Tequation);
	  InitEquation((*t)[i][j]);
	  SetEquationCmp(EQU,(*t)[i][j]);
	  SetEquationType(SYSTEM_EQ,(*t)[i][j]);
	}
    }
}

void SHTransformIdentity(TSHTransform *t)
{
  unsigned int i;

  SHTransformInit(t);

  for(i=0;i<=AXIS_H;i++)
    SetEquationValue(-1.0,(*t)[i][i]);
}

void SHTransformFromEqVectors(TEqVector *x,TEqVector *y,
			      TEqVector *d,TSHTransform *t)
{
  unsigned int i,j;
  TEqVector z;

  NEW((*t),(DIM_SP+1),Tequation**);
  for(i=0;i<(DIM_SP+1);i++)
    {
      NEW((*t)[i],(DIM_SP+1),Tequation*);
      for(j=0;j<(DIM_SP+1);j++)
	{
	  NEW((*t)[i][j],1,Tequation);
	  /* Only initialize the last row (the rest will be
	     directly set) */
	  if (i==DIM_SP)
	    InitEquation((*t)[i][j]);
	}
    }

  SetEquationValue(-1.0,(*t)[AXIS_H][AXIS_H]);

  for(i=0;i<DIM_SP;i++)
    CopyEquation((*t)[i][AXIS_X],GetEqVectorElement(i,x));

  for(i=0;i<DIM_SP;i++)
    CopyEquation((*t)[i][AXIS_Y],GetEqVectorElement(i,y));
  
  CrossProductEqVectors(x,y,&z);
  for(i=0;i<DIM_SP;i++)
    CopyEquation((*t)[i][AXIS_Z],GetEqVectorElement(i,&z));
  DeleteEqVector(&z);

  for(i=0;i<DIM_SP;i++)
    CopyEquation((*t)[i][AXIS_H],GetEqVectorElement(i,d));
}

void SHTransformCopy(TSHTransform *t_dst,TSHTransform *t_org)
{
 
  unsigned int i,j;

  NEW((*t_dst),(DIM_SP+1),Tequation**);
  for(i=0;i<(DIM_SP+1);i++)
    {
      NEW((*t_dst)[i],(DIM_SP+1),Tequation*);
      for(j=0;j<(DIM_SP+1);j++)
	{
	  NEW((*t_dst)[i][j],1,Tequation);
	  CopyEquation((*t_dst)[i][j],(*t_org)[i][j]);
	}
    } 
}

void SHTransformTx(double tx,TSHTransform *t)
{
  SHTransformIdentity(t);
  SetEquationValue(-tx,(*t)[AXIS_X][AXIS_H]);
}

void SHTransformVarTx(unsigned int x,TSHTransform *t)
{
  Tmonomial f;

  SHTransformIdentity(t);

  InitMonomial(&f);
  AddVariable2Monomial(NFUN,x,1,&f);
  AddMonomial(&f,(*t)[AXIS_X][AXIS_H]);
  DeleteMonomial(&f);
}

void SHTransformTy(double ty,TSHTransform *t)
{
  SHTransformIdentity(t);
  SetEquationValue(-ty,(*t)[AXIS_Y][AXIS_H]);
}

void SHTransformVarTy(unsigned int y,TSHTransform *t)
{
  Tmonomial f;

  SHTransformIdentity(t);

  InitMonomial(&f);
  AddVariable2Monomial(NFUN,y,1,&f);
  AddMonomial(&f,(*t)[AXIS_Y][AXIS_H]);
  DeleteMonomial(&f);
}

void SHTransformTz(double tz,TSHTransform *t)
{
  SHTransformIdentity(t);
  SetEquationValue(-tz,(*t)[AXIS_Z][AXIS_H]);
}

void SHTransformVarTz(unsigned int z,TSHTransform *t)
{
  Tmonomial f;

  SHTransformIdentity(t);

  InitMonomial(&f);
  AddVariable2Monomial(NFUN,z,1,&f);
  AddMonomial(&f,(*t)[AXIS_Z][AXIS_H]);
  DeleteMonomial(&f);
}

void SHTransformTxyz(double tx,double ty,double tz,TSHTransform *t)
{
  SHTransformIdentity(t);
  SetEquationValue(-tx,(*t)[AXIS_X][AXIS_H]);
  SetEquationValue(-ty,(*t)[AXIS_Y][AXIS_H]);
  SetEquationValue(-tz,(*t)[AXIS_Z][AXIS_H]);
}

void SHTransformVarTxyz(unsigned int x,unsigned int y,unsigned int z,TSHTransform *t)
{
  Tmonomial f;

  SHTransformIdentity(t);

  InitMonomial(&f);

  AddVariable2Monomial(NFUN,x,1,&f);
  AddMonomial(&f,(*t)[AXIS_X][AXIS_H]);
  ResetMonomial(&f);

  AddVariable2Monomial(NFUN,y,1,&f);
  AddMonomial(&f,(*t)[AXIS_Y][AXIS_H]);
  ResetMonomial(&f);

  AddVariable2Monomial(NFUN,z,1,&f);
  AddMonomial(&f,(*t)[AXIS_Z][AXIS_H]);
  DeleteMonomial(&f);
}


void SHTransformVarDisplacementAlongVector(double *v,unsigned int vID,TSHTransform *t)
{
  Tmonomial f;

  SHTransformIdentity(t);

  InitMonomial(&f);

  AddVariable2Monomial(NFUN,vID,1,&f);
  AddCt2Monomial(v[0],&f);
  AddMonomial(&f,(*t)[AXIS_X][AXIS_H]);
  ResetMonomial(&f);

  AddVariable2Monomial(NFUN,vID,1,&f);
  AddCt2Monomial(v[1],&f);
  AddMonomial(&f,(*t)[AXIS_Y][AXIS_H]);
  ResetMonomial(&f);

  AddVariable2Monomial(NFUN,vID,1,&f);
  AddCt2Monomial(v[2],&f);
  AddMonomial(&f,(*t)[AXIS_Z][AXIS_H]);
  DeleteMonomial(&f);
}

void SHTransformRx(double rx,TSHTransform *t)
{
  double s,c;
  
  s=sin(rx);
  c=cos(rx);

  SHTransformIdentity(t);

  SetEquationValue(-c,(*t)[AXIS_Y][AXIS_Y]);
  SetEquationValue(-c,(*t)[AXIS_Z][AXIS_Z]);

  SetEquationValue(-s,(*t)[AXIS_Z][AXIS_Y]);
  SetEquationValue( s,(*t)[AXIS_Y][AXIS_Z]);
}

void SHTransformVarRx(unsigned int x,TSHTransform *t)
{
  Tmonomial s,c;

  InitMonomial(&s);
  InitMonomial(&c);
  AddVariable2Monomial(SINV,x,1,&s);
  AddVariable2Monomial(COSV,x,1,&c);

  SHTransformInit(t);

  AddMonomial(&c,(*t)[AXIS_Y][AXIS_Y]);
  AddMonomial(&c,(*t)[AXIS_Z][AXIS_Z]);

  AddMonomial(&s,(*t)[AXIS_Z][AXIS_Y]);
  AddCt2Monomial(-1.0,&s);
  AddMonomial(&s,(*t)[AXIS_Y][AXIS_Z]);
  
  SetEquationValue(-1.0,(*t)[AXIS_X][AXIS_X]);
  SetEquationValue(-1.0,(*t)[AXIS_H][AXIS_H]);

  DeleteMonomial(&s);
  DeleteMonomial(&c);
}

void SHTransformRy(double ry,TSHTransform *t)
{
  double s,c;
  
  s=sin(ry);
  c=cos(ry);

  SHTransformIdentity(t);

  SetEquationValue(-c,(*t)[AXIS_X][AXIS_X]);
  SetEquationValue(-c,(*t)[AXIS_Z][AXIS_Z]);

  SetEquationValue(-s,(*t)[AXIS_X][AXIS_Z]);
  SetEquationValue( s,(*t)[AXIS_Z][AXIS_X]);
}

void SHTransformVarRy(unsigned int y,TSHTransform *t)
{
  Tmonomial s,c;

  InitMonomial(&s);
  InitMonomial(&c);
  AddVariable2Monomial(SINV,y,1,&s);
  AddVariable2Monomial(COSV,y,1,&c);

  SHTransformInit(t);

  AddMonomial(&c,(*t)[AXIS_X][AXIS_X]);
  AddMonomial(&c,(*t)[AXIS_Z][AXIS_Z]);

  AddMonomial(&s,(*t)[AXIS_X][AXIS_Z]);
  AddCt2Monomial(-1.0,&s);
  AddMonomial(&s,(*t)[AXIS_Z][AXIS_X]);
  
  SetEquationValue(-1.0,(*t)[AXIS_Y][AXIS_Y]);
  SetEquationValue(-1.0,(*t)[AXIS_H][AXIS_H]);
  
  DeleteMonomial(&s);
  DeleteMonomial(&c);
}

void SHTransformRz(double rz,TSHTransform *t)
{
  double s,c;
  
  s=sin(rz);
  c=cos(rz);

  SHTransformIdentity(t);

  SetEquationValue(-c,(*t)[AXIS_X][AXIS_X]);
  SetEquationValue(-c,(*t)[AXIS_Y][AXIS_Y]);

  SetEquationValue(-s,(*t)[AXIS_Y][AXIS_X]);
  SetEquationValue( s,(*t)[AXIS_X][AXIS_Y]);
}

void SHTransformVarRz(unsigned int z,TSHTransform *t)
{
  Tmonomial s,c;

  InitMonomial(&s);
  InitMonomial(&c);
  AddVariable2Monomial(SINV,z,1,&s);
  AddVariable2Monomial(COSV,z,1,&c);

  SHTransformInit(t);

  AddMonomial(&c,(*t)[AXIS_X][AXIS_X]);
  AddMonomial(&c,(*t)[AXIS_Y][AXIS_Y]);

  AddMonomial(&s,(*t)[AXIS_Y][AXIS_X]);
  AddCt2Monomial(-1.0,&s);
  AddMonomial(&s,(*t)[AXIS_X][AXIS_Y]);
  
  SetEquationValue(-1.0,(*t)[AXIS_Z][AXIS_Z]);
  SetEquationValue(-1.0,(*t)[AXIS_H][AXIS_H]);
  
  DeleteMonomial(&s);
  DeleteMonomial(&c);
}

void SHTransformCreate(unsigned int dof_r3,double v,TSHTransform *t)
{
  switch (dof_r3)
    {
    case TX:
      SHTransformTx(v,t);
      break;
    case TY:
      SHTransformTy(v,t);
      break;
    case TZ:
      SHTransformTz(v,t);
      break;
    case RX:
      SHTransformRx(v,t);
      break;
    case RY:
      SHTransformRy(v,t);
      break;
    case RZ:
      SHTransformRz(v,t);
      break;
    }
}

void SHTransformVarCreate(unsigned int dof_r3,unsigned int v,TSHTransform *t)
{
  switch (dof_r3)
    {
    case TX:
      SHTransformVarTx(v,t);
      break;
    case TY:
      SHTransformVarTy(v,t);
      break;
    case TZ:
      SHTransformVarTz(v,t);
      break;
    case RX:
      SHTransformVarRx(v,t);
      break;
    case RY:
      SHTransformVarRy(v,t);
      break;
    case RZ:
      SHTransformVarRz(v,t);
      break;
    }
}

Tequation *SHTransformGetElement(unsigned int i,unsigned int j,TSHTransform *t)
{
  /* We do not return the elements in the last row (they are always constant) */
  if ((i<AXIS_H)&&(j<=AXIS_H))
   return((*t)[i][j]);
  else
    Error("Element out of range in SHTransformGetElement");
  return(NULL);
}

void SHTransformProduct(TSHTransform *t1,TSHTransform *t2,TSHTransform *t3)
{
  TSHTransform t4;
  unsigned int i,j,k;
  Tequation eq;

  SHTransformInit(&t4);
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  for(k=0;k<(DIM_SP+1);k++)
	    {
	      ProductEquations((*t1)[i][k],(*t2)[k][j],&eq);
	      AccumulateEquations(&eq,1.0,t4[i][j]);
	      DeleteEquation(&eq);
	    }
	}
    }

  if ((t3==t1)||(t3==t2))
    SHTransformDelete(t3);
  SHTransformCopy(t3,&t4);
  SHTransformDelete(&t4);
}

void SHTransformPreCtProduct(THTransform *t1,TSHTransform *t2,TSHTransform *t3)
{
  TSHTransform t4;
  unsigned int i,j,k;
  double ct;

  SHTransformInit(&t4);
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  for(k=0;k<(DIM_SP+1);k++)
	    {
	      ct=HTransformGetElement(i,k,t1);
	      AccumulateEquations((*t2)[k][j],ct,t4[i][j]);
	    }
	}
    }
  if (t3==t2)
    SHTransformDelete(t3);
  SHTransformCopy(t3,&t4);
  SHTransformDelete(&t4);
}

void SHTransformPostCtProduct(TSHTransform *t1,THTransform *t2,TSHTransform *t3)
{
  TSHTransform t4;
  unsigned int i,j,k;
  double ct;

  SHTransformInit(&t4);
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  for(k=0;k<(DIM_SP+1);k++)
	    {
	      ct=HTransformGetElement(k,j,t2);
	      AccumulateEquations((*t1)[i][k],ct,t4[i][j]);
	    }
	}
    }
  if (t3==t1)
    SHTransformDelete(t3);
  SHTransformCopy(t3,&t4);
  SHTransformDelete(&t4);
}

void SHTransformAdd(TSHTransform *t1,TSHTransform *t2,TSHTransform *t3)
{
  TSHTransform t4;
  unsigned int i,j;

  SHTransformInit(&t4);
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  AccumulateEquations((*t1)[i][j],1.0,t4[i][j]);
	  AccumulateEquations((*t2)[i][j],1.0,t4[i][j]);
	}
    }
  if ((t3==t1)||(t3==t2))
    SHTransformDelete(t3);
  SHTransformCopy(t3,&t4);
  SHTransformDelete(&t4);
}

void SHTransformInverse(TSHTransform *t,TSHTransform *ti)
{
  unsigned int i,j;
  TSHTransform tt,tr;

  SHTransformIdentity(&tt);
  for(i=0;i<DIM_SP;i++)
    AccumulateEquations((*t)[i][AXIS_H],-1.0,tt[i][AXIS_H]);

  SHTransformInit(&tr);
  for(i=0;i<DIM_SP;i++)
    {
      for(j=0;j<DIM_SP;j++)
	{
	  DeleteEquation(tr[i][j]);
	  CopyEquation(tr[i][j],(*t)[j][i]);
	}
    }
  SetEquationValue(1.0,tr[AXIS_H][AXIS_H]);

  if (t==ti)
    SHTransformDelete(ti);

  SHTransformProduct(&tr,&tt,ti);

  SHTransformDelete(&tr);
  SHTransformDelete(&tt);
}

void SHTransformTranspose(TSHTransform *t,TSHTransform *tt)
{
  TSHTransform ta;
  unsigned int i,j;

  NEW(ta,(DIM_SP+1),Tequation**);
  for(i=0;i<(DIM_SP+1);i++)
    {
      NEW(ta[i],(DIM_SP+1),Tequation*);
      for(j=0;j<(DIM_SP+1);j++)
	{
	  NEW(ta[i][j],1,Tequation);
	  CopyEquation(ta[i][j],(*t)[j][i]);
	}
    }
  
  if (tt==t)
    SHTransformDelete(tt);
  SHTransformCopy(tt,&ta);
  SHTransformDelete(&ta);
}

void SHTransformApply(double *p_in,Tequation *p_out,TSHTransform *t)
{
  unsigned int i,j;
  
  for(i=0;i<DIM_SP;i++)
    {
      CopyEquation(&(p_out[i]),(*t)[i][AXIS_H]); /*The homogeneous term*/

      for(j=0;j<DIM_SP;j++)
	AccumulateEquations((*t)[i][j],p_in[j],&(p_out[i]));
    }
}

void SHTransformApplyRot(double *p_in,Tequation *p_out,TSHTransform *t)
{
  unsigned int i,j;
  
  for(i=0;i<DIM_SP;i++)
    {
      InitEquation(&(p_out[i])); /* Do not use homogeneous term */

      for(j=0;j<DIM_SP;j++)
	AccumulateEquations((*t)[i][j],p_in[j],&(p_out[i]));
    }
}

void SHTransformEvaluate(double *varValues,THTransform *tc,TSHTransform *t)
{
  unsigned int i,j;
  double ct;
  
  HTransformIdentity(tc); /* Just initialize */
  for(i=0;i<DIM_SP;i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  ct=EvaluateWholeEquation(varValues,(*t)[i][j]);
	  HTransformSetElement(i,j,ct,tc);
	}
    } 
}


void SHTransformPrint(FILE *f,char **varNames,TSHTransform *t)
{
  unsigned int i,j;
  
  for(i=0;i<DIM_SP;i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  fprintf(f,"   ST[%u,%u]=",i,j);
	  PrintMonomials(f,varNames,(*t)[i][j]);
	}
    }
}

void SHTransformDelete(TSHTransform *t)
{
  unsigned int i,j;
  
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  DeleteEquation((*t)[i][j]);
	  free((*t)[i][j]);
	}
      free((*t)[i]);
    }
  free(*t);
}
