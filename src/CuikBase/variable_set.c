#include "variable_set.h"

#include "defines.h"

#include <string.h>
#include <math.h>


/** 
   \file variable_set.c

   \brief Implementation of the functions operating on box Tvariable_set.
 
   Implementation of the functions operating on box Tvariable_set.

   \sa Tvariable_set, variable_set.h.
*/

/*private function of adding a var to vs*/

/** 
  \brief Adds an element to a variable set.

  Adds a variable index with a given power to a variable set. 
  Private function used by different public functions.

  \param f (Trigonometric) Function to be applied to the variable 
           (\ref NFUN to use the variable as it is).
  \param varid The index of the variable to be added to the set.
  \param p The power for this variable
  \param vs The set of variables to update.
*/
void AddVariableInt(unsigned int f,unsigned int varid,unsigned int p,
		    Tvariable_set *vs);

void AddVariableInt(unsigned int f,unsigned int varid,unsigned int p,
		    Tvariable_set *vs)
{  
  signed int j;
  unsigned int s;

  if (vs->nvars==vs->maxvars)
    {
      MEM_DUP(vs->var_id,vs->maxvars,unsigned int);
      MEM_EXPAND(vs->power,vs->maxvars,unsigned int);
      MEM_EXPAND(vs->fun,vs->maxvars,unsigned int);
    }
  
  vs->var_id[vs->nvars]=varid;
  vs->power[vs->nvars]=p;
  vs->fun[vs->nvars]=f;
  vs->nvars++;

  /* Keep variables in order from lower to upper ID. For
     all functions applied to the same variable, keep
     an order from lower to upper (function ID
     NFUN < SINV < COSV < TANV < SEC2V < SEC2TANV < dSEC2TANV < EXPV < PWPV < PWLV < PWCV */
  j=vs->nvars-1;
  while((j>0)&&
	((vs->var_id[j-1]>vs->var_id[j])||
	 ((vs->var_id[j-1]==vs->var_id[j])&&(vs->fun[j-1]>vs->fun[j]))))
    {
      SWAP(vs->var_id[j],vs->var_id[j-1],s);
      SWAP(vs->power[j],vs->power[j-1],s);
      SWAP(vs->fun[j],vs->fun[j-1],s);
      j--;
    }
}

void InitVarSet(Tvariable_set *vs)
{
  vs->nvars=0;
  vs->maxvars=INIT_NUM_VARIABLES;
  NEW(vs->var_id,vs->maxvars,unsigned int);
  NEW(vs->power,vs->maxvars,unsigned int);
  NEW(vs->fun,vs->maxvars,unsigned int);
}

void ResetVarSet(Tvariable_set *vs)
{
  vs->nvars=0;
}

void CopyVarSet(Tvariable_set *vs_dst,Tvariable_set *vs_orig)
{
  vs_dst->nvars=vs_orig->nvars;

  vs_dst->maxvars=vs_orig->maxvars;

  NEW(vs_dst->var_id,vs_dst->maxvars,unsigned int);
  NEW(vs_dst->power,vs_dst->maxvars,unsigned int);
  NEW(vs_dst->fun,vs_dst->maxvars,unsigned int);

  memcpy(vs_dst->var_id,vs_orig->var_id,vs_dst->nvars*sizeof(unsigned int));
  memcpy(vs_dst->power,vs_orig->power,vs_dst->nvars*sizeof(unsigned int));
  memcpy(vs_dst->fun,vs_orig->fun,vs_dst->nvars*sizeof(unsigned int));
}

void ShiftVarIndexes(unsigned int nv,Tvariable_set *vs)
{
  unsigned int i;

  for(i=0;i<vs->nvars;i++)
    {
      if (vs->var_id[i]==nv)
	Error("Remove the variable before shifting the var indexes for the remaining vars");
      if (vs->var_id[i]>nv)
	vs->var_id[i]--;
    }
}

unsigned int CmpVarSet(Tvariable_set *vs1,Tvariable_set *vs2)
{
  unsigned int r;
  unsigned int i;

  if (vs1->nvars>vs2->nvars)
    r=2;
  else
    {
      if (vs2->nvars>vs1->nvars)
	r=1;
      else
	{
	  i=0;
	  while((i<vs1->nvars)&&
		(vs1->var_id[i]==vs2->var_id[i])&&
		(vs1->power[i]==vs2->power[i])&&
		(vs1->fun[i]==vs2->fun[i])) 
	    i++;
  
	  if (i==vs1->nvars)
	    r=0;
	  else
	    {
	      if((vs1->fun[i]>vs2->fun[i])||
		 (vs1->power[i]>vs2->power[i])||
		 (vs2->var_id[i]>vs1->var_id[i]))
		r=2;
	      else
		r=1;
	    }
	}
    }
  return(r);
}

boolean EmptyVarSet(Tvariable_set *vs)
{
  return(vs->nvars==0);
}

boolean PolynomialVarSet(Tvariable_set *vs)
{
  boolean found;
  unsigned int i;

  found=FALSE;
  for(i=0;((!found)&&(i<vs->nvars));i++)
    found=(vs->fun[i]!=NFUN);

  return(!found);
}

unsigned int GetPlaceinSet(unsigned int id,Tvariable_set *vs)
{ 
  boolean found=FALSE;
  unsigned int i;

  i=0;
  while((i<vs->nvars)&&(!found))
    {
      found=(id==vs->var_id[i]);
      if (!found) i++;
    }
    
  if (found)
    return(i);
  else
    return(NO_UINT); 
}

boolean VarIncluded(unsigned int id,Tvariable_set *vs)
{ 
  return((boolean)(GetPlaceinSet(id,vs)!=NO_UINT));
}

boolean Included(unsigned int f,unsigned int id,
		 unsigned int p,Tvariable_set *vs)
{
  boolean found=FALSE;
  unsigned int i;

  i=0;
  while((i<vs->nvars)&&(!found))
    {
      found=((id==vs->var_id[i])&&(f==vs->fun[i])&&(p==vs->power[i]));
      if (!found) i++;
    }
  
  return(found);
}

/*True if they share a variable with the SAME exponent and function */
boolean VarSetIntersect(Tvariable_set *vs1,Tvariable_set *vs2)
{
  boolean found=FALSE;
  unsigned int i;
  
  i=0;
  while((i<vs1->nvars)&&(!found))
    {
      found=Included(vs1->fun[i],vs1->var_id[i],vs1->power[i],vs2);
      if (!found) i++;
    }
  return(found);
}

/*result of v1+v2 : we want to keep all the variables and the maximum of the exponents
  in v1,v2 */
void UnionVarSet(boolean fun,Tvariable_set *vs_new,Tvariable_set *vs)
{
  unsigned int i,j,n,id;
  boolean found;

  for(i=0;i<vs_new->nvars;i++)
    {  
      /* Size of 'vs' changes as we add variables (and the order
         of variables in 'vs' change!!) */
      n=vs->nvars;

      id=vs_new->var_id[i];
      found=FALSE;
      j=0;
      if (fun)
	{
	  while((j<n)&&(!found)&&(vs->var_id[j]<=id))
	    {
	      found=((vs->var_id[j]==id)&&
		     (vs_new->fun[j]==vs->fun[i]));
	      if (!found)
		j++;
	    }
	}
      else
	{
	  while((j<n)&&(!found)&&(vs->var_id[j]<=id))
	    {
	      found=(vs->var_id[j]==id);
	      if (!found)
		j++;
	    }
	}
      if (found)
	{
	  if (vs_new->power[i]>vs->power[j])
	    vs->power[j]=vs_new->power[i]; /*we keep the maximum order for this variable*/
	}
      else
	AddVariableInt(vs_new->fun[i],id,vs_new->power[i],vs);
    }
}

/*If already in the set, we just increse the exponent. We implement: (var_set)*x^p */
void AddVariable2Set(unsigned int f,unsigned int varid,unsigned int p,Tvariable_set *vs)
{
  boolean found=FALSE;
  unsigned int i;

  i=0;
  while((i<vs->nvars)&&(!found))
    {
      found=((varid==vs->var_id[i])&&(f==vs->fun[i]));
      if (!found) i++;
    }
  if (found)
    vs->power[i]+=p;
  else   
    AddVariableInt(f,varid,p,vs);
}

void ProductVarSet(Tvariable_set *vs1,Tvariable_set *vs2,Tvariable_set *v_out)
{
  Tvariable_set *v1,*v2;
  unsigned int i;

  if ((vs1->nvars>vs2->nvars)||(vs1==v_out))
    {
      v1=vs1;
      v2=vs2;
    }
  else
    {
      v1=vs2;
      v2=vs1;
    }

  if (v1!=v_out)
    CopyVarSet(v_out,v1);
  for(i=0;i<v2->nvars;i++)
    AddVariable2Set(v2->fun[i],v2->var_id[i],v2->power[i],v_out);
}

/*Independent of the exponent and function*/
void RemoveVariableFromSet(unsigned int varid,Tvariable_set *vs)
{
  unsigned int i,k;

  k=0;
  for(i=0;i<vs->nvars;i++)
    {
      if (vs->var_id[i]!=varid)
	{
	  vs->var_id[k]=vs->var_id[i];
	  vs->power[k]=vs->power[i];
	  vs->fun[k]=vs->fun[i];
	  k++;
	}
    }
  vs->nvars=k;
}

double FixVariableInVarSet(unsigned int varid,double ct,Tvariable_set *vs)
{
  double r,v,c;
  unsigned int i,k;

  r=1.0;
  k=0;
  for(i=0;i<vs->nvars;i++)
    {
      if (vs->var_id[i]==varid)
	{
	  switch(vs->fun[i])
	    {
	    case NFUN:
	      v=ct;
	      break;
	    case SINV:
	      v=sin(ct);
	      break;
	    case COSV:
	      v=cos(ct);
	      break;
	    case TANV:
	      v=tan(ct);
	      break;
	    case SEC2V:
	      c=cos(ct);
	      if (fabs(c)<ZERO)
		Error("Division by zero when fixing a variable (secant^2)");
	      v=1/(c*c);
	      break;
	    case SEC2TANV:
	      c=cos(ct);
	      if (fabs(c)<ZERO)
		Error("Division by zero when fixing a variable (secant^2*tan)");
	      v=tan(ct)/(c*c); /* sec(ct)^2*tan(ct) */
	      break;
	    case dSEC2TANV:
	      c=cos(ct);
	      if (fabs(c)<ZERO)
		Error("Division by zero when fixing a variable (diff secant^2*tan)");
	      c=1.0/c*c; /* sec(ct)^2 */
	      v=2*c*tan(ct)+c*c; /* 2*sec(ct)^2*tan(ct)^2+sec(ct)^4 */
	      break;
	    case EXPV:
	      v=exp(ct);
	      break;
	    case PWPV:
	      if (ct<0)
		v=ct*ct;
	      else
		v=0.0;
	      break;
	    case PWLV:
	      if (ct<0)
		v=2.0*ct;
	      else
		v=0.0;
	      break;
	    case PWCV:
	      if (ct<0)
		v=2.0;
	      else
		v=0.0;
	      break;
	    default:
	      Error("Unknown function in FixVariableInVarSet");;
	    }
	  r*=pow(v,vs->power[i]);
	}
      else
	{
	  vs->var_id[k]=vs->var_id[i];
	  vs->power[k]=vs->power[i];
	  vs->fun[k]=vs->fun[i];
	  k++;
	}
    }
  vs->nvars=k;
  return(r);
}

double ReplaceVariableInVarSet(unsigned int varid,double ct,unsigned int newID,Tvariable_set *vs)
{
  double r;
  unsigned int i;
  Tvariable_set vTmp;

  InitVarSet(&vTmp);
  r=1.0;
  for(i=0;i<vs->nvars;i++)
    {
      if ((vs->var_id[i]==varid)&&(ct!=1.0)&&(vs->var_id[i]!=NFUN))
	Error("Variables in trigonometric expression can not be scaled");
      
      r*=pow(ct,vs->power[i]);

      AddVariable2Set(vs->fun[i],
		      (vs->var_id[i]==varid?newID:vs->var_id[i]),
		      vs->power[i],&vTmp);
    }
  DeleteVarSet(vs);
  CopyVarSet(vs,&vTmp);
  
  return(r);
}

unsigned int VarSetOrder(Tvariable_set *vs)
{
  unsigned int i,o;
  
  o=0;
  for(i=0;i<vs->nvars;i++)
    o+=vs->power[i];
    
/*
  o=0;
  for(i=0;i<vs->nvars;i++)
    {
      if (vs->power[i]>o)
	o=vs->power[i];
    }
*/
  return(o);
}

inline unsigned int VariableSetSize(Tvariable_set *vs)
{
  return(vs->nvars);
}

unsigned int GetVariableN(unsigned int n,Tvariable_set *vs)
{
  if (n<vs->nvars)
    return(vs->var_id[n]);
  else
    {
      Error("Requested an element not included in VarSet");
      return(0);
    }
}

unsigned int *GetVariables(Tvariable_set *vs)
{
  return(vs->var_id);
}

unsigned int GetVariablePowerN(unsigned int n,Tvariable_set *vs)
{
  if (n<vs->nvars)
    return(vs->power[n]);
  else
    {
      Error("Requested an element not included in VarSet");
      return(0);
    }
}

unsigned int GetVariableFunctionN(unsigned int n,Tvariable_set *vs)
{
  if (n<vs->nvars)
    return(vs->fun[n]);
  else
    {
      Error("Requested an element not included in VarSet");
      return(0);
    }
}

unsigned int *GetPowers(Tvariable_set *vs)
{
  return(vs->power);
}

inline double EvaluateVarSet(double *varValues,Tvariable_set *vs)
{
  double v,f,c;
  unsigned int i,n;

  #if (_DEBUG>2)
    if (vs->nvars==0)
      Error("Should not evalute empty var sets");
  #endif

  f=1.0;
  for(i=0;i<vs->nvars;i++)
    {
      n=vs->var_id[i];
      v=varValues[n];
      switch(vs->fun[i])
	{
	case NFUN:
	  break;
	case SINV:
	  v=sin(v);
	  break;
	case COSV:
	  v=cos(v);
	  break;
	case TANV:
	  v=tan(v);
	  break;
	case SEC2V:
	  c=cos(v);
	  if (fabs(c)<ZERO)
	    Error("Division by zero when evaluating a variable (secant^2)");
	  v=1/(c*c);
	  break;
	case SEC2TANV:
	  c=cos(v);
	  if (fabs(c)<ZERO)
	    Error("Division by zero when evaluating a variable (secant^2*tan)");
	  v=tan(v)/(c*c); /* sec(v)^2*tan(v) */
	  break;
	case dSEC2TANV:
	  c=cos(v);
	  if (fabs(c)<ZERO)
	    Error("Division by zero when evaluating a variable (diff secant^2*tan)");
	  c=1.0/(c*c); /* sec(v)^2 */
	  v=2*c*tan(v)+c*c; /* 2*sec(v)^2*tan(v)^2+sec(v)^4 */
	  break;
	case EXPV:
	  v=exp(v);
	  break;
	case PWPV:
	  if (v<0.0)
	    v=v*v;
	  else
	    v=0.0;
	  break;
	case PWLV:
	  if (v<0.0)
	    v=2.0*v;
	  else
	    v=0.0;
	  break;
	case PWCV:
	  if (v<0.0)
	    v=2.0;
	  else
	    v=0.0;
	  break;
	default:
	  Error("Unknown function in EvaluateVarSet");
	}

      if (vs->power[i]==1)
	f*=v;
      else
	f*=pow(v,(double)(vs->power[i]));
    }

  return(f);
}

void EvaluateVarSetInt(Tinterval *varValues,Tinterval *i_out,Tvariable_set *vs)
{
  unsigned int i,n;
  Tinterval i_aux,*v;

  if (vs->nvars==0)
    Error("Should not evalute empty var sets");
  
  NewInterval(1,1,i_out);
  i=0;
  while(i<vs->nvars)
    {
      n=vs->var_id[i];
      v=&(varValues[n]);
      switch(vs->fun[i])
	{
	case NFUN:
	  CopyInterval(&i_aux,v);
	  break;
	case SINV:
	  IntervalSine(v,&i_aux);
	  break;
	case COSV:
	  IntervalCosine(v,&i_aux);
	  break;
	case TANV:
	  IntervalTangent(v,&i_aux);
	  break;
	case SEC2V:
	  IntervalSecant2(v,&i_aux);
	  break;
	case SEC2TANV:
	  IntervalSecant2Tangent(v,&i_aux);
	  break;
	case dSEC2TANV:
	  Error("Not implemented yet");
	  break;
	case EXPV:
	  IntervalExp(v,&i_aux);
	  break;
	case PWPV:
	  {
	    double l;

	    l=LowerLimit(v);
	    if (l<0.0)
	      {
		if (UpperLimit(v)>0.0)
		  NewInterval(l*l,0.0,&i_aux);
		else
		  IntervalPow(v,2,&i_aux);
	      }
	    else
	      NewInterval(0,0,&i_aux);
	  }
	  break;
	case PWLV:
	  {
	    double l;
	    
	    l=LowerLimit(v);
	    if (l<0.0)
	      {
		if (UpperLimit(v)>0.0)
		  NewInterval(2*l,0.0,&i_aux);
		else
		  IntervalScale(v,2,&i_aux);
	      }
	    else
	      NewInterval(0,0,&i_aux);
	  }
	  break;
	case PWCV:
	  if (LowerLimit(v)<0.0)
	    {
	      if (UpperLimit(v)>0.0)
		NewInterval(0.0,2.0,&i_aux);
	      else
		NewInterval(2.0,2.0,&i_aux);
	    }
	  else
	    NewInterval(0,0,&i_aux);
	  break;
	default:
	  Error("Unknown function in EvaluateVarSetInt");
	}

      if (vs->power[i]!=1)
	IntervalPow(&i_aux,vs->power[i],&i_aux);

      IntervalProduct(i_out,&i_aux,i_out);

      i++;
    }
}

double DeriveVarSet(unsigned int nv,Tvariable_set *dvs,Tvariable_set *vs)
{
  unsigned int i,p;
  boolean found;
  double ct;

  dvs->maxvars=2*vs->maxvars; 

  NEW(dvs->var_id,dvs->maxvars,unsigned int);
  NEW(dvs->power,dvs->maxvars,unsigned int);
  NEW(dvs->fun,dvs->maxvars,unsigned int);

  dvs->nvars=0;
  found=FALSE;
  ct=1.0;
  for(i=0;i<vs->nvars;i++)
    {
      if (vs->var_id[i]==nv)
	{
	  found=TRUE;

	  p=vs->power[i];

	  /* d ([f(x)]^n)/dx = n [f(x)]^(n-1) * df(x)/dx*/

	  ct*=(double)p;
	  if (p>1)
	    {
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=p-1;
	      dvs->fun[dvs->nvars]=vs->fun[i];
	      dvs->nvars++;
	    }

	  switch(vs->fun[i])
	    {
	    case NFUN:
	      break;
	    case SINV:
	      /* d(sin(x))/dx = cos(x) */
	      dvs->fun[dvs->nvars]=COSV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case COSV:
	      /* d(cos(x))/dx = (-1) * sin(x)*/
	      ct=-ct;
	      dvs->fun[dvs->nvars]=SINV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case TANV:
	      /* d(tan(x))/dx = sec^2(x)*/
	      dvs->fun[dvs->nvars]=SEC2V;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case SEC2V:
	      /* d(sec^2(x))/dx = 2 * sec^2(x) * tan(x)*/
	      ct*=2;
	      dvs->fun[dvs->nvars]=SEC2TANV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case SEC2TANV:
	      dvs->fun[dvs->nvars]=dSEC2TANV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case EXPV:
	      /* d(exp(x))/dx = exp(x)*/
	      dvs->fun[dvs->nvars]=EXPV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case PWPV:
	      /* d(pwp(x))/dx = pwl(x)*/
	      dvs->fun[dvs->nvars]=PWLV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case PWLV:
	      /* d(pwl(x))/dx = pwc(x)*/
	      dvs->fun[dvs->nvars]=PWCV;
	      dvs->var_id[dvs->nvars]=vs->var_id[i];
	      dvs->power[dvs->nvars]=1;
	      dvs->nvars++;
	      break;
	    case PWCV:
	      /* d(pwc(x))/dx = 0 */
	      ct=0.0;
	      break;
	    default:
	      Error("Unknown function in DeriveVarSet");
	    }
	}
      else
	{
	  dvs->var_id[dvs->nvars]=vs->var_id[i];
	  dvs->power[dvs->nvars]=vs->power[i];
	  dvs->fun[dvs->nvars]=vs->fun[i];
	  dvs->nvars++;
	}
    }
  if ((found)&&(ct!=0.0))
    return(ct);
  else
    {
      ResetVarSet(dvs);
      return(0.0);
    }
}

void PrintVarSet(FILE *f,char **varNames,Tvariable_set *vs)
{
  unsigned int i;
  boolean hasFun;

  if (vs->nvars>0)
    {
      for(i=0;i<vs->nvars;i++)
	{
	  if (i>0) 
	    fprintf(f,"*");

	  switch(vs->fun[i])
	    {
	    case NFUN:
	      hasFun=FALSE;
	      break;
	    case SINV:
	      fprintf(f,"sin(");
	      hasFun=TRUE;
	      break;
	    case COSV:
	      fprintf(f,"cos(");
	      hasFun=TRUE;
	      break;
	    case TANV:
	      fprintf(f,"tan(");
	      hasFun=TRUE;
	      break;
	    case SEC2V:
	      fprintf(f,"sec2(");
	      hasFun=TRUE;
	      break;
	    case SEC2TANV:
	      fprintf(f,"sec2_tan(");
	      hasFun=TRUE;
	      break;  
	    case dSEC2TANV:
	      fprintf(f,"dsec2_tan(");
	      hasFun=TRUE;
	      break;  
	    case EXPV:
	      fprintf(f,"exp(");
	      hasFun=TRUE;
	      break;
	    case PWPV:
	      fprintf(f,"pwp(");
	      hasFun=TRUE;
	      break;
	    case PWLV:
	      fprintf(f,"pwl(");
	      hasFun=TRUE;
	      break;
	    case PWCV:
	      fprintf(f,"pwc(");
	      hasFun=TRUE;
	      break;
	    default:
	      Error("Unknown function in PrintVarSet");
	    }
 
	  if (varNames!=NULL)
	    { 
	      char *n;

	      n=varNames[vs->var_id[i]];
	      PRINT_VARIABLE_NAME(f,n);
	    }
	  else
	    fprintf(f,"v_%u",vs->var_id[i]);

	  if (hasFun)
	    {
	      fprintf(f,")");
	    }

	  if (vs->power[i]>1)
	    fprintf(f,"^%d",vs->power[i]);
	}
    }
}

void DeleteVarSet(Tvariable_set *vs)
{
  free(vs->var_id);
  free(vs->power);
  free(vs->fun);
}
