#include "monomial.h"

#include "error.h"
#include "defines.h"

#include <math.h>

/** 
   \file monomial.c
   \brief Implementations of the functions operating on Tmonomial. 
   
   Implementations of the functions operating on Tmonomial. 

   \sa Tmonomial, monomial.h.
*/

void InitMonomial(Tmonomial *f)
{
  f->empty=TRUE;
  InitVarSet(&(f->vars));
  f->ct=0.0;
}

void ResetMonomial(Tmonomial *f)
{
  f->empty=TRUE;
  ResetVarSet(&(f->vars));
  f->ct=0.0;
}

void ZeroMonomial(Tmonomial *f)
{
  ResetVarSet(&(f->vars));
  f->ct=0.0;
}

void FixVariableInMonomial(unsigned int nv,double v,Tmonomial *f)
{
  if (!f->empty)
    {
      f->ct*=FixVariableInVarSet(nv,v,&(f->vars));
  
      if (fabs(f->ct)<=ZERO)
	ZeroMonomial(f);
   
      /*the indexes for variables with ID above 'nv' should be decreased by one*/
      ShiftVarIndexes(nv,&(f->vars)); /*has no effects for empty var sets*/
    }
}

void ReplaceVariableInMonomial(unsigned int nv,double ct,unsigned int nvNew,Tmonomial *f)
{
  if (!f->empty)
    {
      f->ct*=ReplaceVariableInVarSet(nv,ct,nvNew,&(f->vars));
  
      if (fabs(f->ct)<=ZERO)
	ZeroMonomial(f);
   
      /*the indexes for variables with ID above 'nv' should be decreased by one*/
      ShiftVarIndexes(nv,&(f->vars)); /*has no effects for empty var sets*/
    }
}

boolean EmptyMonomial(Tmonomial *f)
{
  return(f->empty);
}

boolean CtMonomial(Tmonomial *f)
{
  return((f->empty)||
	 (VariableSetSize(&(f->vars))==0)||
	 (fabs(f->ct)<=ZERO));
}

boolean QuadraticMonomial(Tmonomial *f)
{
  return((VariableSetSize(&(f->vars))==1)&&
	 (GetVariablePowerN(0,&(f->vars))==2)&&
	 (PolynomialVarSet(&(f->vars))));
}

boolean BilinearMonomial(Tmonomial *f)
{
  return((!f->empty)&&
	 (VariableSetSize(&(f->vars))==2)&&
	 (GetVariablePowerN(0,&(f->vars))==1)&&
	 (GetVariablePowerN(1,&(f->vars))==1)&&
	 (PolynomialVarSet(&(f->vars))));
}

boolean LinearMonomial(Tmonomial *f)
{
  return((!f->empty)&&
	 (VariableSetSize(&(f->vars))==1)&&
	 (GetVariablePowerN(0,&(f->vars))==1)&&
	 (PolynomialVarSet(&(f->vars))));
}

boolean PolynomialMonomial(Tmonomial *f)
{
  return((!f->empty)&&
	 (PolynomialVarSet(&(f->vars))));
}

unsigned int MonomialOrder(Tmonomial *f)
{
  return(VarSetOrder(&(f->vars)));
}

void CopyMonomial(Tmonomial *f_dst,Tmonomial *f_orig)
{
  f_dst->empty=f_orig->empty;
  f_dst->ct=f_orig->ct;
  CopyVarSet(&(f_dst->vars),&(f_orig->vars));
}

unsigned int CmpMonomial(Tmonomial *f1,Tmonomial *f2)
{
  unsigned int r;

  if ((f1->empty)&&(f2->empty))
    r=0;
  else
    {
      if (f1->empty)
	r=2;
      else
	{
	  if (f2->empty)
	    r=1;
	  else
	    {
	      r=CmpVarSet(&(f1->vars),&(f2->vars));
	      if (r==0)
		{
		  if (f1->ct>f2->ct)
		    r=1;
		  else
		    {
		      if (f1->ct<f2->ct)
			r=2;
		    }
		}
	    }
	}
    }
  return(r);
}

double GetMonomialCt(Tmonomial *f)
{
  if (f->empty)
    return(0.0);
  else
    return(f->ct);
}

void SetMonomialCt(double k,Tmonomial *f)
{
  f->empty=FALSE; /* may not be empty */
  if (fabs(k)<=ZERO)
    ZeroMonomial(f);
  else
    f->ct=k;
}

Tvariable_set *GetMonomialVariables(Tmonomial *f)
{
  return(&(f->vars));
}

void AddCt2Monomial(double k,Tmonomial *f)
{
  if (f->empty)
    f->ct=k;
  else
    f->ct*=k;

  f->empty=FALSE;

  if (fabs(f->ct)<=ZERO)
    ZeroMonomial(f);
}

void AddVariable2Monomial(unsigned int fn,unsigned int varid,unsigned int p,Tmonomial *f)
{
  if (f->empty)
    {
      f->empty=FALSE;
      f->ct=1.0;
      AddVariable2Set(fn,varid,p,&(f->vars));
    }
  else
    {
      if (fabs(f->ct)>ZERO)
	AddVariable2Set(fn,varid,p,&(f->vars));
    }
}

void MonomialProduct(Tmonomial *f1,Tmonomial *f2,Tmonomial *f)
{
  InitMonomial(f);
  f->empty=((f1->empty)&&(f2->empty));
  if (!f->empty)
    {
      f->ct=f1->ct*f2->ct;
      if (fabs(f->ct)>ZERO)
	ProductVarSet(&(f1->vars),&(f2->vars),&(f->vars));
      else
	ZeroMonomial(f);
    }
}

inline double EvaluateMonomial(double *varValues,Tmonomial *f)
{
  if (f->empty)
    return(0.0);
  else
    {
      if (VariableSetSize(&(f->vars))>0)
	return(f->ct*EvaluateVarSet(varValues,&(f->vars)));
      else
	return(f->ct);
    }
}

void EvaluateMonomialInt(Tinterval *varValues,Tinterval *i_out,Tmonomial *f)
{  
  if (f->empty)
    NewInterval(0,0,i_out);
  else
    {
      if (VariableSetSize(&(f->vars))>0)
	{
	  Tinterval ct;

	  EvaluateVarSetInt(varValues,i_out,&(f->vars));

	  /* The coefficients of the equations can be affected by some noise
	     due to floating point roundings when operating them. We add a small
	     range (1e-11) to compensate for those possible errors. */
	  NewInterval(f->ct-ZERO,f->ct+ZERO,&ct);
	  IntervalProduct(&ct,i_out,i_out);
	}
      else
	{
	  /* The coefficients of the equations can be affected by some noise
	     due to floating point roundings when operating them. We add a small
	     range (1e-11) to compensate for those possible errors. */
	  NewInterval(f->ct-ZERO,f->ct+ZERO,i_out);
	}
    }
}

void DeriveMonomial(unsigned int nv,Tmonomial *df,Tmonomial *f)
{
  if ((f->empty)||(!VarIncluded(nv,&(f->vars))))
    InitMonomial(df);
  else
    {
      double s;

      /* The output of 'DeriveVarSet' is >0 since we now for sure the
         var set includes variable 'nv;*/
      s=DeriveVarSet(nv,&(df->vars),&(f->vars));
      df->ct=f->ct*s;
      df->empty=(s==0.0);
    }
}


void PrintMonomial(FILE *file,boolean first,char **varNames,Tmonomial *f)
{
  if (!f->empty)
    {
      if (first)
	{
	  if (fabs(f->ct-1)>ZERO)
	    {
	      fprintf(file,"%.16g",f->ct);
	      if (!EmptyVarSet(&(f->vars)))
		fprintf(file,"*");
	    }
	}
      else
	{
	  if (fabs(f->ct-1)<ZERO)
	    fprintf(file,"+");
	  else
	    {
	      if (fabs(f->ct+1)<ZERO)
		fprintf(file,"-");
	      else
		{
		  fprintf(file,"%+.16g",f->ct);
		  if (!EmptyVarSet(&(f->vars)))
		    fprintf(file,"*");
		}
	    }
	}

      PrintVarSet(file,varNames,&(f->vars));
    }
}

void DeleteMonomial(Tmonomial *f)
{
  DeleteVarSet(&(f->vars));
}
