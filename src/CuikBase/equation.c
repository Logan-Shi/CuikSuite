#include "equation.h"

#include "defines.h"

#include <string.h>
#include <math.h>

/** \file equation.c
    \brief Implementation of the functions operating on Tequation.

    Implementation of the functions operating on Tequation.
    
    \sa Tequation, equation.h,
*/


/** 
  \brief Resets the information about monomials stored in the equation.
 
  Removes the information about monomials stored in the equation.

  \param eq The equation to be reseted.
*/
void ResetEquationMonomials(Tequation *eq);

/** 
  \brief Removes monomial with small constant.
 
  Monomials with a constant value below \ref ZERO are removed.

  \param eq The equation to purge.
*/
void PurgeEquation(Tequation *eq);

void ResetEquationMonomials(Tequation *eq)
{
  unsigned int i;
  
  eq->polynomial=TRUE;
  
  for(i=0;i<eq->nMonomials;i++)
    {
      DeleteMonomial(eq->monomials[i]);
      free(eq->monomials[i]);
      eq->monomials[i]=NULL;
    }
  
  eq->nMonomials=0;
}

void PurgeEquation(Tequation *eq)
{
  Tequation eq1;
  unsigned int i;
  boolean changed;
  
  InitEquation(&eq1);
  
  eq1.cmp=eq->cmp;
  eq1.type=eq->type;

  changed=FALSE;
  if (fabs(eq->value)<=ZERO)
    {
      eq1.value=0.0;
      changed=(eq->value!=0.0);
    }
  else
    eq1.value=eq->value;  

  for(i=0;i<eq->nMonomials;i++)
    {
      if (fabs(GetMonomialCt(eq->monomials[i]))>ZERO)
	AddMonomial(eq->monomials[i],&eq1);
      else
	changed=TRUE;
    }
  if (changed)
    {
      DeleteEquation(eq);
      CopyEquation(eq,&eq1);
    }
  DeleteEquation(&eq1);
}

void InitEquation(Tequation *eq)
{
  unsigned int i;

  eq->cmp=NOCMP;
  eq->type=NOTYPE_EQ;
  eq->polynomial=TRUE;
  eq->order=0;
  eq->value=0.0;

  eq->maxMonomials=INIT_NUM_MONOMIALS;
  eq->nMonomials=0;
  NEW(eq->monomials,eq->maxMonomials,Tmonomial *);

  for(i=0;i<eq->maxMonomials;i++)
    eq->monomials[i]=NULL;

  InitVarSet(&(eq->vars));
}

void EquationFromLinearConstraint(TLinearConstraint *lc,Tequation *eq)
{
  Tinterval error;
  double ct=0;
  unsigned int cmp=EQU;
  Tmonomial m;
  unsigned int i,n;

  InitEquation(eq);

  GetLinearConstraintError(&error,lc);
  if (IntervalSize(&error)==0)
    {
      ct=IntervalCenter(&error);
      cmp=EQU;
    }
  else
    {
      if (LowerLimit(&error)==-INF)
	{
	  ct=UpperLimit(&error);
	  cmp=LEQ;
	}
      else
	{
	  if (UpperLimit(&error)==INF)
	    {
	      ct=LowerLimit(&error);
	      cmp=GEQ;
	    }
	  else
	    Error("The input linear constraint can not be converted into a single equation");
	}
    }
  eq->cmp=cmp;
  eq->value=ct;

  n=GetNumTermsInLinearConstraint(lc);
  for(i=0;i<n;i++)
    {
      InitMonomial(&m);
      AddCt2Monomial(GetLinearConstraintCoefficient(i,lc),&m);
      AddVariable2Monomial(NFUN,GetLinearConstraintVariable(i,lc),1,&m);
      
      AddMonomial(&m,eq);
      DeleteMonomial(&m);
    }
}


void EquationFromLinearConstraintProduct(TLinearConstraint *lc1,TLinearConstraint *lc2,Tequation *eq)
{
  Tinterval error1,error2;
  double ct1,ct2;
  Tmonomial m;
  unsigned int i,j,n1,n2;

  InitEquation(eq);

  GetLinearConstraintError(&error1,lc1);
  if (IntervalSize(&error1)==0)
    ct1=IntervalCenter(&error1);
  else
    Error("The input linear constraint can not be converted into an equation");

  GetLinearConstraintError(&error2,lc2);
  if (IntervalSize(&error2)==0)
    ct2=IntervalCenter(&error2);
  else
    Error("The input linear constraint can not be converted into an equation");
    
  n1=GetNumTermsInLinearConstraint(lc1);
  n2=GetNumTermsInLinearConstraint(lc2);
  for(i=0;i<n1;i++)
    {
      for(j=0;j<n2;j++) 
	{
	  InitMonomial(&m);
	  AddCt2Monomial(GetLinearConstraintCoefficient(i,lc1),&m);
	  AddVariable2Monomial(NFUN,GetLinearConstraintVariable(i,lc1),1,&m);

	  AddCt2Monomial(GetLinearConstraintCoefficient(j,lc2),&m);
	  AddVariable2Monomial(NFUN,GetLinearConstraintVariable(j,lc2),1,&m);
	  
	  AddMonomial(&m,eq);
	  DeleteMonomial(&m);
	}
    }

  for(i=0;i<n1;i++)
    {
      InitMonomial(&m);
      AddCt2Monomial(ct2,&m);
      AddCt2Monomial(GetLinearConstraintCoefficient(i,lc1),&m);
      AddVariable2Monomial(NFUN,GetLinearConstraintVariable(i,lc1),1,&m);
      AddMonomial(&m,eq);
      DeleteMonomial(&m);
    }

  for(j=0;j<n2;j++) 
    {
      InitMonomial(&m);
      AddCt2Monomial(ct1,&m);
      AddCt2Monomial(GetLinearConstraintCoefficient(j,lc2),&m);
      AddVariable2Monomial(NFUN,GetLinearConstraintVariable(j,lc2),1,&m);
      AddMonomial(&m,eq);
      DeleteMonomial(&m);
    }
}

void CopyEquation(Tequation *eq_dst,Tequation *eq_orig)
{
  unsigned int i;

  eq_dst->cmp=eq_orig->cmp;
  eq_dst->type=eq_orig->type;
  eq_dst->polynomial=eq_orig->polynomial;
  eq_dst->value=eq_orig->value;
  
  eq_dst->maxMonomials=eq_orig->maxMonomials;
  eq_dst->nMonomials=0;
  NEW(eq_dst->monomials,eq_dst->maxMonomials,Tmonomial*);

  InitVarSet(&(eq_dst->vars));
  eq_dst->order=0;

  
  for(i=0;i<eq_orig->nMonomials;i++)
    AddMonomial(eq_orig->monomials[i],eq_dst);
}

void RewriteEquation2Simp(double epsilon,Tmapping *map,Tequation *eqOut,Tequation *eq)
{
  unsigned int i,nv,o;
  double ct;
  unsigned int v,v1,v2;
  TLinearConstraint lc,lc1,lc2;
  Tvariable_set *vars;
  Tequation eqTmp,eqRw;

  InitEquation(&eqRw);
  eqRw.cmp=eq->cmp;
  eqRw.polynomial=eq->polynomial;
  eqRw.type=eq->type;
  eqRw.value=eq->value;
  
  for(i=0;i<eq->nMonomials;i++)
    {
      vars=GetMonomialVariables(eq->monomials[i]);
      nv=VariableSetSize(vars);
      switch (nv)
	{
	case 0:
	  AddMonomial(eq->monomials[i],&eqRw);
	  break;

	case 1:
	  if (GetVariableFunctionN(0,vars)!=NFUN)
	    AddMonomial(eq->monomials[i],&eqRw);
	  else
	    {
	      v=GetVariableN(0,vars);
	      GetOriginalVarRelation(v,&lc,map);
	      o=MonomialOrder(eq->monomials[i]);
	      
	      if (o==1)
		EquationFromLinearConstraint(&lc,&eqTmp);
	      else
		{
		  if (o==2)
		EquationFromLinearConstraintProduct(&lc,&lc,&eqTmp);
		  else
		    Error("Cubic factor in a equation");
		}
	      ct=GetMonomialCt(eq->monomials[i]);
	      AccumulateEquations(&eqTmp,ct,&eqRw);
	      
	      DeleteLinearConstraint(&lc);
	      DeleteEquation(&eqTmp);
	    }
	  break;

	case 2:
	  if ((GetVariableFunctionN(0,vars)!=NFUN)||
	      (GetVariableFunctionN(1,vars)!=NFUN))
	    AddMonomial(eq->monomials[i],&eqRw);
	  else
	    {
	      v1=GetVariableN(0,vars);
	      GetOriginalVarRelation(v1,&lc1,map);

	      v2=GetVariableN(1,vars);
	      GetOriginalVarRelation(v2,&lc2,map);
	      
	      EquationFromLinearConstraintProduct(&lc1,&lc2,&eqTmp);
	      ct=GetMonomialCt(eq->monomials[i]);
	      AccumulateEquations(&eqTmp,ct,&eqRw);
	      
	      DeleteLinearConstraint(&lc1);
	      DeleteLinearConstraint(&lc2);
	      DeleteEquation(&eqTmp);
	    }
	  break;

	default:
	  Error("Only constant, linear or bilinear monomials are allowed");
	}
    }
  PurgeEquation(&eqRw);
  if (eq==eqOut)
    DeleteEquation(eq);
  CopyEquation(eqOut,&eqRw);
  DeleteEquation(&eqRw);
}

void RewriteEquation2Orig(Tmapping *map,Tequation *eq)
{
  if (eq->nMonomials>0)
    {
      unsigned int i,j,nv,vID;
      Tmonomial f;
      Tvariable_set *vars;
      Tequation eqRw;

      /*
	All the variables in the simplified system are also in the original one
	and thus, we only need to replace variable the identifiers for all the monomials
	in the equation.
      */
      InitEquation(&eqRw);
      eqRw.cmp=eq->cmp;
      eqRw.type=eq->type;
      eqRw.polynomial=eq->polynomial;
      eqRw.value=eq->value;
  
      InitMonomial(&f);

      for(i=0;i<eq->nMonomials;i++)
	{
	  vars=GetMonomialVariables(eq->monomials[i]);
	  nv=VariableSetSize(vars);
	  for(j=0;j<nv;j++)
	    {
	      vID=GetVarIDInOriginal(GetVariableN(j,vars),map);
	      if (vID==NO_UINT)
		Error("Simplied var is not in original (RewriteEquation2Orig)");
	      AddVariable2Monomial(GetVariableFunctionN(j,vars),vID,
				   GetVariablePowerN(j,vars),&f);
	    }
      

	  SetMonomialCt(GetMonomialCt(eq->monomials[i]),&f);
	  AddMonomial(&f,&eqRw);
	  ResetMonomial(&f);
	} 
      DeleteMonomial(&f);
  
      DeleteEquation(eq);
      CopyEquation(eq,&eqRw);
      DeleteEquation(&eqRw);
    }
}

void AccumulateEquations(Tequation *eqn,double ct,Tequation *eq)
{
  unsigned int i;

  for(i=0;i<eqn->nMonomials;i++)
    AddScaledMonomial(ct,eqn->monomials[i],eq);
     
  eq->value+=(ct*eqn->value);
  PurgeEquation(eq);
}

void VarAccumulateEquations(Tequation *eqn,unsigned int v,Tequation *eq)
{
  unsigned int i;
  Tmonomial fnew;

  for(i=0;i<eqn->nMonomials;i++)
    {
      CopyMonomial(&fnew,eqn->monomials[i]);
      AddVariable2Monomial(NFUN,v,1,&fnew);
      AddMonomial(&fnew,eq);
      DeleteMonomial(&fnew);
    }
  InitMonomial(&fnew);
  SetMonomialCt(-eqn->value,&fnew);
  AddVariable2Monomial(NFUN,v,1,&fnew);
  AddMonomial(&fnew,eq);
  DeleteMonomial(&fnew);
  
  PurgeEquation(eq);
}

void ProductEquations(Tequation *eq1,Tequation *eq2,Tequation *eqOut)
{
  unsigned int i,j;
  Tmonomial fnew;
  Tequation *eq;

  if ((eq1->cmp!=eq2->cmp)||(eq1->type!=eq2->type))
    Error("Product of equations of different type in ProductEquations");

  if ((eqOut==eq1)||(eqOut==eq2))
    NEW(eq,1,Tequation)
  else
    eq=eqOut;
  
  InitEquation(eq);
  eq->cmp=eq->cmp;
  eq->type=eq->type;

  for(i=0;i<eq1->nMonomials;i++)
    {
      for(j=0;j<eq2->nMonomials;j++)
	{
	  MonomialProduct(eq1->monomials[i],eq2->monomials[j],&fnew);
	  AddMonomial(&fnew,eq);
	  DeleteMonomial(&fnew);
	}
    }

  AccumulateEquations(eq1,-eq2->value,eq);
  AccumulateEquations(eq2,-eq1->value,eq);

  eq->value+=(eq1->value*eq2->value);

  PurgeEquation(eq);
  
  if ((eqOut==eq1)||(eqOut==eq2))
    {
      DeleteEquation(eqOut);
      CopyEquation(eqOut,eq);
      DeleteEquation(eq);
      free(eq);
    }
}

void ResetEquation(Tequation *eq)
{
  eq->cmp=NOCMP;
  eq->type=NOTYPE_EQ;
  eq->polynomial=TRUE;
  eq->value=0.0;
  eq->order=0;

  ResetEquationMonomials(eq);

  ResetVarSet(&(eq->vars));
}

/*
    Returns
      0: normal case 
      1: the equation becomes constant and it holds
      2  the equation becomes constant and it does not hold
*/
unsigned int FixVariableInEquation(double epsilon,unsigned int nv,double b,Tequation *eq)
{ 
  TLinearConstraint lc;
  unsigned int r;

  InitLinearConstraint(&lc);

  AddCt2LinearConstraint(b,&lc);
  r=ReplaceVariableInEquation(epsilon,nv,&lc,eq);
  DeleteLinearConstraint(&lc);
  
  return(r);
}

/*
    Returns
      0: normal case 
      1: the equation becomes constant and it holds
      2  the equation becomes constant and it does not hold
*/
unsigned int ReplaceVariableInEquation(double epsilon,unsigned int nv,
				       TLinearConstraint *lc,Tequation *eq)
{ 
  unsigned int n;

  n=GetNumTermsInLinearConstraint(lc);

  if ((n<2)||(eq->polynomial))
    {
      /* We are either in the case x=ct or x=y or dealing with a monomial without
         (trigonometric) functions. */
      unsigned int i,j,k;
      Tequation eqNew;
      Tmonomial m;
      unsigned int np;
      unsigned int p;
      Tvariable_set *vm; 
      Tinterval error;
      double a,a1,ct;
      unsigned int ind,ind1;
      unsigned int nvNew;

      if ((!eq->polynomial)&&(n==1))
	{
	  nvNew=GetLinearConstraintVariable(0,lc);
	  if (fabs(GetLinearConstraintCoefficient(0,lc)-1.0)>ZERO)
	    Error("For non-polynomial equations only x=ct of x=y replacements are possible");
	}
      else
	nvNew=NO_UINT;
      
      InitEquation(&eqNew);
      SetEquationCmp(GetEquationCmp(eq),(&eqNew));
      SetEquationType(GetEquationType(eq),(&eqNew));
      SetEquationValue(GetEquationValue(eq),(&eqNew));

      GetLinearConstraintError(&error,lc);
      if (IntervalSize(&error)>ZERO)
	Error("Only linear constraints with constant offset can be used in simplification");
      ct=-IntervalCenter(&error);

      i=0;
      while(i<eq->nMonomials)
	{ 
	  vm=GetMonomialVariables(eq->monomials[i]);
	  np=GetPlaceinSet(nv,vm);
	  if (np!=NO_UINT)
	    {
	      /*The variable is in the monomial  */
	      if (!PolynomialMonomial(eq->monomials[i]))
		{
		  CopyMonomial(&m,eq->monomials[i]);
		  if (nvNew==NO_UINT)
		    FixVariableInMonomial(nv,ct,&m); /* Replace var=ct */
		  else
		    ReplaceVariableInMonomial(nv,1.0,nvNew,&m); /* Replace x=y */
		  AddMonomial(&m,&eqNew);
		  DeleteMonomial(&m);
		}
	      else
		{
		  /* Replace var=linear_constraint inside a polynomial monomial */
		  p=GetVariablePowerN(np,vm);
		  if (p==1)
		    {
		      for(k=0;k<n;k++)
			{
			  a=GetLinearConstraintCoefficient(k,lc);
			  ind=GetLinearConstraintVariable(k,lc);

			  CopyMonomial(&m,eq->monomials[i]);
			  AddVariable2Monomial(NFUN,ind,1,&m);
			  FixVariableInMonomial(nv,1,&m);
			  AddCt2Monomial(a,&m);
			  AddMonomial(&m,&eqNew);
			  DeleteMonomial(&m);
			}

		      CopyMonomial(&m,eq->monomials[i]);
		      FixVariableInMonomial(nv,1,&m);
		      AddCt2Monomial(ct,&m);
		      AddMonomial(&m,&eqNew);
		      DeleteMonomial(&m);
		    }
		  else
		    {
		      /* if we fix a variable (n==0) we do not care about the degree (p).
			 In this case, we do not enter the loop below and  we have to take 
			 into account that the degree can be larger than 2 */
		      if ((n>0)&&
			  ((p>2)||(VariableSetSize(vm)>1)))
			Error("Monomials should be lineal, bilineal or quadratic");
		      /* here we have a monomial of the form c*x^2 and we need to
			 apply a subtitution x=a*y+b that gives
			 c*(a*y+b)^2=c*(a^2*y^2+2*a*y*b+b^2)=c*(a*y)^2+c*(2*a*b*y)+c*(b^2)
		      */
 
		      for(k=0;k<n;k++)
			{
			  a=GetLinearConstraintCoefficient(k,lc);
			  ind=GetLinearConstraintVariable(k,lc);

			  for(j=0;j<n;j++)
			    {
			      a1=GetLinearConstraintCoefficient(j,lc);
			      ind1=GetLinearConstraintVariable(j,lc);

			      CopyMonomial(&m,eq->monomials[i]);
			      AddVariable2Monomial(NFUN,ind,1,&m);
			      AddVariable2Monomial(NFUN,ind1,1,&m);
			      FixVariableInMonomial(nv,1,&m);
			      AddCt2Monomial(a*a1,&m);
			      AddMonomial(&m,&eqNew);
			      DeleteMonomial(&m);
			    }

			  CopyMonomial(&m,eq->monomials[i]);
			  AddVariable2Monomial(NFUN,ind,1,&m);
			  FixVariableInMonomial(nv,1,&m);
			  AddCt2Monomial(2*a*ct,&m);
			  AddMonomial(&m,&eqNew);
			  DeleteMonomial(&m);
			}

		      /* Take into account the constant term (the only term if
			 the variable is replaced by a ct) */
		      CopyMonomial(&m,eq->monomials[i]);
		      FixVariableInMonomial(nv,1,&m);
		      AddCt2Monomial(pow(ct,(double)p),&m);
		      AddMonomial(&m,&eqNew);
		      DeleteMonomial(&m);
		    }
		}
	    }
	  else
	    {
	      CopyMonomial(&m,eq->monomials[i]);
	      ShiftVarIndexes(nv,GetMonomialVariables(&m));
	      AddMonomial(&m,&eqNew);
	      DeleteMonomial(&m);
	    }
	  i++;
	}

      DeleteEquation(eq);
      CopyEquation(eq,&eqNew);
      DeleteEquation(&eqNew);

      NormalizeEquation(eq);

      if (eq->nMonomials>0)
	return(0);
      else
	{
	  boolean hold=TRUE;

	  switch (eq->cmp)
	    {
	    case EQU:
	      hold=(fabs(eq->value)<=epsilon);
	      break;
	    case LEQ:
	      hold=(-epsilon<=eq->value);
	      break;
	    case GEQ:
	      hold=( epsilon>=eq->value);
	      break;
	    }

	  if (!hold)
	    {	  
	      printf("Ct equation does not hold: %g\n",eq->value);
	      return(2);
	    }
	  else
	    return(1);
	}
    }
  else
    return(1); /* No replacement */
}

void CtScaleEquation(double ct,Tequation *eq)
{
  if (eq->cmp==EQU)
    {
      unsigned int i;
      
      if (fabs(ct)<ZERO)
	Error("Scaling an equation by 0");
      
      for(i=0;i<eq->nMonomials;i++)
	AddCt2Monomial(ct,eq->monomials[i]);
      eq->value*=ct;
    }
   else
     Error("CtScaleEquation for non-equalities is not implemented yet");
}

void VarScaleEquation(unsigned int v,Tequation *eq)
{
   if (eq->cmp==EQU)
    {
      unsigned int i;
      Tmonomial m;
      
      ResetVarSet(&(eq->vars));
      for(i=0;i<eq->nMonomials;i++)
	{
	  AddVariable2Monomial(NFUN,v,1,eq->monomials[i]);
	  UnionVarSet(FALSE,GetMonomialVariables(eq->monomials[i]),&(eq->vars));
	}
      
      InitMonomial(&m);
      AddCt2Monomial(-eq->value,&m);
      AddVariable2Monomial(NFUN,v,1,&m);
      AddMonomial(&m,eq); 
      DeleteMonomial(&m);
      
      eq->value=0;
    } 
   else
     Error("VarScaleEquation for non-equalities is not implemented yet");
}

/*
  Simple form of normalization to avoid numerical inestabilities
  If all monomials have the same ct (up to ZERO) we make them
  all equal to one. 
  This helps in many cases when we replace variables to avoid
  transforming a circle equation into a scaled circle equation
  (that is not identified as a circle!)
*/
void NormalizeEquation(Tequation *eq)
{
  boolean equal;
  unsigned int i;
  double s,s1;

  PurgeEquation(eq);
  if ((eq->nMonomials>0)&&(eq->cmp==EQU))
    {
      /*first monomial is set to possitive*/
      s=GetMonomialCt(eq->monomials[0]);
      s=(s<0?-1.0:1.0); 
      for(i=0;i<eq->nMonomials;i++)
	AddCt2Monomial(s,eq->monomials[i]);
      eq->value*=s;

      /* if all constants in the momomials are "almost" the same
         we set all them to 1 (or -1)*/
      equal=TRUE;
      s=GetMonomialCt(eq->monomials[0]); /* s is possitive !! */
      for(i=1;((equal)&&(i<eq->nMonomials));i++)
	{
	  s1=GetMonomialCt(eq->monomials[i]);
	  equal=((fabs(s-s1)<=ZERO)||(fabs(s+s1)<=ZERO));
	}

      if (equal)
	{
	  if (fabs(eq->value-s)<=ZERO)
	    eq->value=1;
	  else
	    {
	      if (fabs(eq->value+s)<=ZERO)
		eq->value=-1;
	      else
		eq->value/=s;
	    }
	  for(i=0;i<eq->nMonomials;i++)
	    {
	      s1=GetMonomialCt(eq->monomials[i]);
	      if (s1>0)
		SetMonomialCt(+1,eq->monomials[i]);
	      else
		SetMonomialCt(-1,eq->monomials[i]);
	    }
	}
    }
}

boolean CleanInfEquation(Tequation *eq_in,Tinterval *varValues,boolean *changed,Tequation *eq_out)
{
  Tinterval m,rhs;
  boolean bounded;
  unsigned int i;

  #if (_DEBUG>6)
    printf("       Cleaning equation inf\n");
  #endif
  InitEquation(eq_out);
  
  NewInterval(0,0,&rhs);
  *changed=FALSE;
  for(i=0;i<eq_in->nMonomials;i++)
    {
      EvaluateMonomialInt(varValues,&m,eq_in->monomials[i]);  
      if (IntervalSize(&m)==INF)
	{
	  IntervalSubstract(&rhs,&m,&rhs);
	  *changed=TRUE;
	}
      else
	AddMonomial(eq_in->monomials[i],eq_out);

     #if (_DEBUG>6)
        printf("         Monomial %u ",i);
	PrintInterval(stdout,&m);
	printf(" ->");
	PrintInterval(stdout,&rhs);
	printf("\n");
      #endif
    }

  if (*changed)
    {
      #if (_DEBUG>6)
        printf("       Changing equation to rhs ");
	PrintInterval(stdout,&rhs);
	printf("\n");
      #endif
      if ((LowerLimit(&rhs)==-INF)&&(UpperLimit(&rhs)==+INF))
	{
	  bounded=FALSE;
	  #if (_DEBUG>6)
	    printf("       Unbounded\n");
	  #endif
	}
      else
	{
	  /* Only one of the extremes of rhs is INF */
	  bounded=TRUE;
	  IntervalOffset(&rhs,eq_in->value,&rhs);
    	  #if (_DEBUG>6)
  	    printf("       rhs arter offset ");
	    PrintInterval(stdout,&rhs);
	    printf("\n");
          #endif
	  if (LowerLimit(&rhs)==-INF)
	    {
	      /* upper limit is finite -> <= */
	      eq_out->value=UpperLimit(&rhs);
	      eq_out->cmp=LEQ;
	      #if (_DEBUG>6)
	        printf("       Changing to LEQ %f\n",eq_out->value);
	      #endif
	    }
	  else
	    {
	      /* lower limit is finite -> >= */
	      eq_out->value=UpperLimit(&rhs);
	      eq_out->cmp=GEQ;
	      #if (_DEBUG>6)
	        printf("       Changing to GEQ %f\n",eq_out->value);
	      #endif
	    }
	}
    }
  else
    {
      eq_out->cmp=eq_in->cmp;
      eq_out->type=eq_in->type;
      eq_out->value=eq_in->value;
      bounded=TRUE;
    }

  return((bounded)&&(eq_out->nMonomials>0));
}

boolean IsSimplificable(unsigned int simpLevel,unsigned int nTerms,boolean polynomial,
			boolean *systemVars,Tbox *cb,
			unsigned int *v,TLinearConstraint *lc,
			Tequation *eq)
{
  boolean s;

  s=FALSE;
  *v=NO_UINT;

  if ((eq->polynomial)&&
      (eq->cmp==EQU)&&
      (eq->type!=VELOCITY_EQ)&&
      (eq->type!=NON_DYNAMIC_EQ)&&
      (simpLevel>0)&&
      (((simpLevel==1)&&(nTerms==0))||
       ((simpLevel==2)&&(nTerms<=MAX_TERMS_SIMP))||
       ((simpLevel==3)&&(nTerms<=MAX_TERMS_SIMP))
       ))
    {
      unsigned int o,nveq,l,r;
      signed int i;
      double ct;
      boolean found;
            
      o=GetEquationOrder(eq);
      nveq=VariableSetSize(&(eq->vars));

      switch(o)
	{
	case 1:
	  if (nveq==(nTerms+1))
	    {
	      if (simpLevel<3) /*simpLevel=1,2 -> nTerms = 0,1 -> nveq=1,2*/
		{
		  /* x=ct */
		  /* x + a * y = ct */

		  found=FALSE;
		  /* two loops, in the first one we try to find a non-system variable
		     we can put in function of other (including system) variables.
		     If this is not possible, we try, as a last resort, to put remove
		     system variables (to put them in function of other variables, possibly
		     non system ones) */
		  for(r=0;((!found)&&(r<2));r++)
		    {
		      /* The loop is tail to head just to get nice results in a particular
			 example. It can be also head to tail without any problem. */
		      i=eq->nMonomials-1;
		      while((!found)&&(i>=0))
			{
			  l=GetVariableN(0,GetMonomialVariables(eq->monomials[i]));

			  if (((r==0)&&(!systemVars[l]))|| 
			      ((r==1)&&(systemVars[l])))
			    {
			      ct=GetMonomialCt(eq->monomials[i]);
			      
			      if ((ct==1)||(ct==-1))
				found=TRUE;
			      else
				i--;
			    }
			  else
			    i--;
			}
		    }
		  /* When we have matrix or trigonometric equations we are more strict in the variable
		     replacements and only x=ct and x=y are allowed*/
		  if ((found)&&(!polynomial)&&(nveq==2))
		    {
		      double a,b;
		      
		      /* in the case x + a y = ct ensure that we actually have x - y = 0  (or -x + y =0) -> x=y */
		      a=GetMonomialCt(eq->monomials[i]);
		      b=GetMonomialCt(eq->monomials[(i==0?1:0)]);
		      found=(((b==1.0)||(b==-1.0))&&(a!=b)&&(eq->value==0.0));
		    }
		}
	      else
		{
		  /*simpLevel=3 -> nTerms=2*/
		  /*General case: a*x+b*y=ct*/
		  unsigned int k;
		  double d,d1,d2,ct1,dm;

		  found=FALSE;
		  /* two loops, in the first one we try to find a non-system variable
		     we can put in function of other (including system) variables.
		     If this is not possible, we try, as a last resort, to put remove
		     system variables (to put them in function of other variables, possibly
		     non system ones) */
		  for(r=0;((!found)&&(r<2));r++)
		    {
		      dm=INF;
		      for(k=0;((!found)&&(k<eq->nMonomials));k++)
			{
			  l=GetVariableN(0,GetMonomialVariables(eq->monomials[k]));

			  if (((r==0)&&(!systemVars[l]))||
			      ((r==1)&&(systemVars[l])))
			    {
			      ct1=GetMonomialCt(eq->monomials[k]);
			      d1=fabs(ct1-1);
			      d2=fabs(ct1+1);
			      d=(d1<d2?d1:d2);
			      if (d<dm)
				{
				  found=TRUE;
				  i=k;
				  ct=ct1;
				  dm=d;
				}
			    }
			}
		    }
		}

	      if (found)
		{
		  unsigned int j;
		  
		  InitLinearConstraint(lc);
		  *v=GetVariableN(0,GetMonomialVariables(eq->monomials[i]));
		  s=TRUE;
		  for(j=0;j<eq->nMonomials;j++)
		    {
		      if (j!=(unsigned int)i)
			{
			  AddTerm2LinearConstraint(GetVariableN(0,GetMonomialVariables(eq->monomials[j])),
						   -GetMonomialCt(eq->monomials[j]),
						   lc
						   );
			}
		    }
		  AddCt2LinearConstraint(eq->value,lc);
		  if (ct!=1)
		    {
		      if (ct==-1)
			InvertLinearConstraint(lc);
		      else
			ScaleLinearConstraint(1/ct,lc);	  
		    }
		}
	    }	  
	  break;
	case 2:
	  /* if nveq==1 -> the equation can only have one monomial */
	  if ((nveq==1)&&(nTerms==0))
	    {
	      if (eq->value==0)
		{
		  /* a x^2 =0  -> x=0 */
		  s=TRUE;
		  
		  InitLinearConstraint(lc);
		  *v=GetVariableN(0,GetMonomialVariables(eq->monomials[0]));
		}
	      else
		{
		  if (simpLevel>1)
		    {
		      /* a x^2 = b with x in [c,d] c>0 or d<0 -> unique solution */
		      *v=GetVariableN(0,GetMonomialVariables(eq->monomials[0]));

		      if (LowerLimit(GetBoxInterval(*v,cb))>=0)
			{
			  s=TRUE;
			  InitLinearConstraint(lc);
			  AddCt2LinearConstraint(sqrt(eq->value/GetMonomialCt(eq->monomials[0])),lc); 
			}
		      else
			{
			  if (UpperLimit(GetBoxInterval(*v,cb))<=0)
			    {
			      s=TRUE;
			      InitLinearConstraint(lc);
			      AddCt2LinearConstraint(-sqrt((eq->value/GetMonomialCt(eq->monomials[0]))),lc); 
			    }
			}
		    }
		}
	    }
	  else
	    {
	      if ((nveq==2)&&(eq->nMonomials==1)&&(eq->value==0))
		{
		  Tinterval *range;
		  unsigned int n;

		  
		  /* a x y = 0 */
		  n=GetVariableN(0,GetMonomialVariables(eq->monomials[0]));
		  range=GetBoxInterval(n,cb);
		  if (!IsInside(0.0,0.0,range))
		    {
		      /* x can not be zero -> y must be zero*/
		      *v=GetVariableN(1,GetMonomialVariables(eq->monomials[0]));
		      range=GetBoxInterval(*v,cb);
		      if (!IsInside(0.0,0.0,range))
			Error("Inconsistent input system"); /* y can not be 0 either?? */
		      InitLinearConstraint(lc);
		      s=TRUE;
		    }
		  else
		    {
		      n=GetVariableN(1,GetMonomialVariables(eq->monomials[0]));
		      range=GetBoxInterval(n,cb);
		      if (!IsInside(0.0,0.0,range))
			{
			  /* y can not be zero -> x must be zero*/
			  *v=GetVariableN(0,GetMonomialVariables(eq->monomials[0]));
			  range=GetBoxInterval(*v,cb);
			  if (!IsInside(0.0,0.0,range))
			    Error("Inconsistent input system"); /* x can not be 0 either?? */
			  InitLinearConstraint(lc);
			  s=TRUE;
			}
		    }
		}
	    }
	  break;
	}
    }

  return(s);
}


void SetEquationType(unsigned int type,Tequation *eq)
{
  eq->type=type;
}

void SetEquationCmp(unsigned int cmp,Tequation *eq)
{
  if ((cmp!=EQU)&&(cmp!=LEQ)&&(cmp!=GEQ))
    Error("Unknow equation cmp");

  eq->cmp=cmp;
}

void SetEquationValue(double v,Tequation *eq)
{
  eq->value=v;
}

boolean EmptyEquation(Tequation *eq)
{
  return((eq->nMonomials==0)&&(fabs(eq->value)<ZERO));
}

boolean LinearEquation(Tequation *eq)
{
  boolean l;
  unsigned int i;

  l=eq->polynomial;
  for(i=0;((l)&&(i<eq->nMonomials));i++)
    {
      l=((CtMonomial(eq->monomials[i]))||(LinearMonomial(eq->monomials[i])));
    }
  return(l);
}

boolean BilinearEquation(Tequation *eq)
{  
  /* A polynomial equation with monomial of order at most two (quadratic or involving
     at most two variables) */

  boolean b;
  unsigned int i;

  b=eq->polynomial;
  for(i=0;((b)&&(i<eq->nMonomials));i++)
    {
      b=((CtMonomial(eq->monomials[i]))||
	 (LinearMonomial(eq->monomials[i]))||
	 (QuadraticMonomial(eq->monomials[i]))||
	 (BilinearMonomial(eq->monomials[i])));
    }
  return(b);
}

boolean CircleEquation(Tequation *eq)
{
  /* x^2 + y^2 = r^2 */

  boolean c=FALSE;

  if ((eq->polynomial)&&(eq->nMonomials==2)&&(eq->value>0.0)&&
      (GetMonomialCt(eq->monomials[0])==1.0)&&(QuadraticMonomial(eq->monomials[0]))&&
      (GetMonomialCt(eq->monomials[1])==1.0)&&(QuadraticMonomial(eq->monomials[1])))
    c=TRUE;
    
  return(c);
}

boolean SphereEquation(Tequation *eq)
{
  /* x^2 + y^2 + z^2 = r^2 */
  boolean s=FALSE;

  if ((eq->polynomial)&&(eq->nMonomials==3)&&(eq->value>0.0)&&
      (GetMonomialCt(eq->monomials[0])==1.0)&&(QuadraticMonomial(eq->monomials[0]))&&
      (GetMonomialCt(eq->monomials[1])==1.0)&&(QuadraticMonomial(eq->monomials[1]))&&
      (GetMonomialCt(eq->monomials[2])==1.0)&&(QuadraticMonomial(eq->monomials[2])))
    s=TRUE;

  return(s);
}

boolean SaddleEquation(Tequation *eq)
{  
  /* x*y + \alpha*z = \beta  */
  boolean s=FALSE;
  
  if ((eq->polynomial)&&(eq->nMonomials==2)&&(eq->cmp==EQU)&&
      (GetMonomialCt(eq->monomials[0])==1.0)&&(BilinearMonomial(eq->monomials[0]))&&
      (LinearMonomial(eq->monomials[1])))
    s=TRUE;

  return(s);
}

boolean BilinealMonomialEquation(Tequation *eq)
{  
  /* x*y = \beta  */
  boolean s=FALSE;
  
  if ((eq->polynomial)&&(eq->nMonomials==1)&&(eq->cmp==EQU)&&
      (GetMonomialCt(eq->monomials[0])==1.0)&&(BilinearMonomial(eq->monomials[0])))
    s=TRUE;

  return(s);
}

boolean ParabolaEquation(Tequation *eq)
{  
  /* x^2 + \alpha*y = \beta  */
  boolean s=FALSE;
  
  if ((eq->polynomial)&&(eq->nMonomials==2)&&(eq->cmp==EQU)&&
      (GetMonomialCt(eq->monomials[0])==1.0)&&(QuadraticMonomial(eq->monomials[0]))&&
      (LinearMonomial(eq->monomials[1])))
    s=TRUE;

  return(s);
}

boolean PolynomialEquation(Tequation *eq)
{
  return(eq->polynomial);
}

inline unsigned int GetEquationCmp(Tequation *eq)
{
  return(eq->cmp);
}

inline unsigned int GetEquationType(Tequation *eq)
{
  return(eq->type);
}

inline double GetEquationValue(Tequation *eq)
{
  return(eq->value);
}

void GetEquationBounds(Tinterval *bounds,Tequation *eq)
{
  switch(eq->cmp)
    {
    case EQU:
      NewInterval(eq->value,eq->value,bounds);
      break;
    case GEQ:
      NewInterval(eq->value,+INF,bounds);
      break;
    case LEQ:
      NewInterval(-INF,eq->value,bounds);
      break;
    case NOCMP:
      Error("Undefined equation cmp in GetEquationBounds");
      break;
    }
}

unsigned int GetEquationOrder(Tequation *eq)
{
  return(eq->order);
}

Tvariable_set *GetEquationVariables(Tequation *eq)
{
  return(&(eq->vars));
}

unsigned int GetEquationNumVariables(Tequation *eq)
{
  return(VariableSetSize(GetEquationVariables(eq)));
}

unsigned int CmpEquations(Tequation *eq1,Tequation *eq2)
{  

  unsigned int r;
  
  if (eq1->polynomial<eq2->polynomial)
    r=2;
  else
    if (eq2->polynomial<eq1->polynomial)
      r=1;
    else
      {
	if (eq1->type<eq2->type)
	  r=2;
	else
	  {
	    if (eq2->type<eq1->type)
	      r=1;
	    else
	      {
		/* Here both equations are of the same type */
		unsigned int o1,o2;

		o1=GetEquationOrder(eq1);
		o2=GetEquationOrder(eq2);

		if ((eq1->cmp>eq2->cmp)||
		    ((eq1->cmp==eq2->cmp)&&(o1>o2))||
		    ((eq1->cmp==eq2->cmp)&&(o1==o2)&&(eq1->nMonomials>eq2->nMonomials)))
		  r=1;
		else
		  {
		    if ((eq2->cmp>eq1->cmp)||
			((eq1->cmp==eq2->cmp)&&(o2>o1))||
			((eq1->cmp==eq2->cmp)&&(o1==o2)&&(eq2->nMonomials>eq1->nMonomials)))
		      r=2;
		    else
		      {
			/*the two equations have the same cmp, order, and number of monomials*/
			unsigned int i;
	  
			i=0;
			r=0;
			while ((i<eq1->nMonomials)&&(r==0))
			  {
			    r=CmpMonomial(eq1->monomials[i],eq2->monomials[i]);
			    if (r==0)
			      i++;
			  }

			if (r==0)
			  {
			    /*the 2 equations have the same order and the same
			      set of monomials. We compare the value*/
			    if (eq1->value>eq2->value)
			      r=1;
			    else
			      {
				if (eq2->value>eq1->value)
				  r=2;
				else
				  r=0;
			      }
			  }
		      }
		  }
	      }
	  }
      }
  if (r!=0)
    return(2);
  else
    return(r);
}

void AddScaledMonomial(double sc,Tmonomial* f,Tequation *eq)
{
  double ct;

  ct=sc*GetMonomialCt(f);

  /* Ensure that we are not adding an empty monomial */
  if ((!EmptyMonomial(f))&&(fabs(ct)>ZERO))
    {
      if (CtMonomial(f))
	eq->value-=ct;
      else
	{
	  unsigned int j;

	  j=FindMonomial(f,eq);

	  if (j!=NO_UINT)
	    {
	      /* The equation already has a monomial with the same equations as the
		 one we are adding -> just add the constants*/
	      SetMonomialCt(GetMonomialCt(eq->monomials[j])+ct,eq->monomials[j]);

	      if (CtMonomial(eq->monomials[j]))
		{
		  unsigned int n,o;

		  /* A non-constant monomial can only become constant if it
		     becomes 0 */
		  if (fabs(GetMonomialCt(eq->monomials[j]))>ZERO)
		    Error("Non zero constant monomial");
		  
		  /*If the monomial becomes ct (i.e., 0) we have to compact the
		    monomials and recompute the varset for the equation*/

		  /*Remove the Zeroed monomial from the equation*/
		  DeleteMonomial(eq->monomials[j]);
		  free(eq->monomials[j]);

		  for(n=j+1;n<eq->nMonomials;n++)
		    eq->monomials[n-1]=eq->monomials[n];
		  eq->nMonomials--;
		  eq->monomials[eq->nMonomials]=NULL;

		  /*Recompute the variables in the equation, the monomial flag, and the order */
		  ResetVarSet(&(eq->vars));
		  eq->polynomial=TRUE;
		  eq->order=0;
		  for(n=0;n<eq->nMonomials;n++)
		    {
		      UnionVarSet(FALSE,GetMonomialVariables(eq->monomials[n]),&(eq->vars));
		      eq->polynomial=((eq->polynomial)&&(PolynomialMonomial(eq->monomials[n])));
		      o=MonomialOrder(f);
		      if (o>eq->order)
			eq->order=o;
		    }
		}
	    }
	  else
	    {
	      /* A new (not null) monomial -> add it to the equation */
	      unsigned int o,j;
	      Tmonomial *s;

	      if (eq->nMonomials==eq->maxMonomials)
		MEM_DUP(eq->monomials,eq->maxMonomials,Tmonomial*);

	      NEW(eq->monomials[eq->nMonomials],1,Tmonomial);
	      CopyMonomial(eq->monomials[eq->nMonomials],f);
	      AddCt2Monomial(sc,eq->monomials[eq->nMonomials]);
	      eq->nMonomials++;
      
	      o=MonomialOrder(f);
	      if (eq->order<o)
		eq->order=o;
	      
	      UnionVarSet(FALSE,GetMonomialVariables(f),&(eq->vars));

	      j=eq->nMonomials-1;
	      while((j>0)&&(CmpMonomial(eq->monomials[j-1],eq->monomials[j])==1))
		{
		  s=eq->monomials[j-1];
		  eq->monomials[j-1]=eq->monomials[j];
		  eq->monomials[j]=s;

		  j--;
		}
	      eq->polynomial=((eq->polynomial)&&(PolynomialMonomial(f)));
	    }
	}
    }
}

inline void AddMonomial(Tmonomial* f,Tequation *eq)
{
  AddScaledMonomial(1.0,f,eq);
}

void GenerateParabolaEquation(unsigned int vx,unsigned int vy,Tequation *eq)
{
  GenerateScaledParabolaEquation(1,vx,vy,eq);
}

void GenerateScaledParabolaEquation(double s,
				    unsigned int vx,unsigned int vy,Tequation *eq)
{
  Tmonomial f;

  if (s==0)
    Error("Defining a scaled parabola equation with scale equal to 0.");

  InitEquation(eq);
  InitMonomial(&f); 

  AddVariable2Monomial(NFUN,vx,2,&f);
  AddMonomial(&f,eq);
  ResetMonomial(&f);

  AddVariable2Monomial(NFUN,vy,1,&f);
  AddCt2Monomial(-s,&f);
  AddMonomial(&f,eq);
  
  DeleteMonomial(&f);

  SetEquationCmp(EQU,eq);
  SetEquationValue(0,eq);
  SetEquationType(DUMMY_EQ,eq);
}

void GenerateSaddleEquation(unsigned int vx,unsigned int vy,unsigned int vz,
			    Tequation *eq)
{
  GenerateScaledSaddleEquation(1,vx,vy,vz,eq);
}

void GenerateScaledSaddleEquation(double s,
				  unsigned int vx,unsigned int vy,unsigned int vz,
				  Tequation *eq)
{
  if (s==0)
    Error("Defining a scaled saddle equation with scale equal to 0.");

  if (vx==vy)
    GenerateScaledParabolaEquation(s,vx,vz,eq);
  else
    {
      Tmonomial f;

      InitEquation(eq);
      InitMonomial(&f); 
      
      AddVariable2Monomial(NFUN,vx,1,&f);
      AddVariable2Monomial(NFUN,vy,1,&f);
      AddMonomial(&f,eq);
      ResetMonomial(&f);
      
      AddVariable2Monomial(NFUN,vz,1,&f);
      AddCt2Monomial(-s,&f);
      AddMonomial(&f,eq);
      
      DeleteMonomial(&f);
      
      SetEquationCmp(EQU,eq); 
      SetEquationValue(0,eq);
      SetEquationType(DUMMY_EQ,eq);
    }
}

void GenerateNormEquation(unsigned int vx,unsigned int vy,unsigned int vz,
			  double n,
			  Tequation *eq)
{
  unsigned int v[3];

  v[0]=vx;
  v[1]=vy;
  v[2]=vz;
  GenerateGeneralNormEquation(3,v,n,eq);
}

void GenerateGeneralNormEquation(unsigned int nv,unsigned int *v,double n,Tequation *eq)
{
  Tmonomial f;
  unsigned int i;

  InitEquation(eq);

  InitMonomial(&f);
  for(i=0;i<nv;i++)
    {
      AddVariable2Monomial(NFUN,v[i],2,&f);
      AddMonomial(&f,eq);
      ResetMonomial(&f);
    }
  DeleteMonomial(&f);

  SetEquationCmp(EQU,eq);
  SetEquationValue(n,eq);
  SetEquationType(SYSTEM_EQ,eq);
}

void GenerateCrossProductEquations(unsigned int v1x,unsigned int v1y,unsigned int v1z,
				   unsigned int v2x,unsigned int v2y,unsigned int v2z,
				   unsigned int v3x,unsigned int v3y,unsigned int v3z,
				   unsigned int vs,
				   double s,
				   Tequation *eq)
{
  Tmonomial f;
  unsigned int i;

  for(i=0;i<3;i++)
    InitEquation(&(eq[i]));
  
  InitMonomial(&f);

  AddCt2Monomial(+1.0,&f);AddVariable2Monomial(NFUN,v1y,1,&f);AddVariable2Monomial(NFUN,v2z,1,&f);
  AddMonomial(&f,&(eq[0]));ResetMonomial(&f);
  AddCt2Monomial(-1.0,&f);AddVariable2Monomial(NFUN,v1z,1,&f);AddVariable2Monomial(NFUN,v2y,1,&f);
  AddMonomial(&f,&(eq[0]));ResetMonomial(&f);
  AddCt2Monomial(-1,&f);
  if (vs==NO_UINT)
    AddCt2Monomial(s,&f);
  else
    AddVariable2Monomial(NFUN,vs,1,&f);
  AddVariable2Monomial(NFUN,v3x,1,&f);
  AddMonomial(&f,&(eq[0]));ResetMonomial(&f);

  AddCt2Monomial(+1.0,&f);AddVariable2Monomial(NFUN,v1z,1,&f);AddVariable2Monomial(NFUN,v2x,1,&f);
  AddMonomial(&f,&(eq[1]));ResetMonomial(&f);
  AddCt2Monomial(-1.0,&f);AddVariable2Monomial(NFUN,v1x,1,&f);AddVariable2Monomial(NFUN,v2z,1,&f);
  AddMonomial(&f,&(eq[1]));ResetMonomial(&f);
  AddCt2Monomial(-1,&f);
  if (vs==NO_UINT)
    AddCt2Monomial(s,&f);
  else
    AddVariable2Monomial(NFUN,vs,1,&f);
  AddVariable2Monomial(NFUN,v3y,1,&f);
  AddMonomial(&f,&(eq[1]));ResetMonomial(&f);

  AddCt2Monomial(+1.0,&f);AddVariable2Monomial(NFUN,v1x,1,&f);AddVariable2Monomial(NFUN,v2y,1,&f);
  AddMonomial(&f,&(eq[2]));ResetMonomial(&f);
  AddCt2Monomial(-1.0,&f);AddVariable2Monomial(NFUN,v1y,1,&f);AddVariable2Monomial(NFUN,v2x,1,&f);
  AddMonomial(&f,&(eq[2]));ResetMonomial(&f);
  AddCt2Monomial(-1,&f);
  if (vs==NO_UINT)
    AddCt2Monomial(s,&f);
  else
    AddVariable2Monomial(NFUN,vs,1,&f);
  AddVariable2Monomial(NFUN,v3z,1,&f);
  AddMonomial(&f,&(eq[2]));

  DeleteMonomial(&f);

  for(i=0;i<3;i++)
    {
      SetEquationCmp(EQU,&(eq[i]));
      SetEquationValue(0.0,&(eq[i]));
      SetEquationType(SYSTEM_EQ,&(eq[i]));
    }
}

void GenerateDotProductEquation(unsigned int v1x,unsigned int v1y,unsigned int v1z,
				unsigned int v2x,unsigned int v2y,unsigned int v2z,
				unsigned int vc,
				double c,
				Tequation *eq)
{
  Tmonomial f;  
  
  InitEquation(eq);

  InitMonomial(&f); 
  
  AddCt2Monomial(+1.0,&f);AddVariable2Monomial(NFUN,v1x,1,&f);AddVariable2Monomial(NFUN,v2x,1,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddCt2Monomial(+1.0,&f);AddVariable2Monomial(NFUN,v1y,1,&f);AddVariable2Monomial(NFUN,v2y,1,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddCt2Monomial(+1.0,&f);AddVariable2Monomial(NFUN,v1z,1,&f);AddVariable2Monomial(NFUN,v2z,1,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);

  if (vc!=NO_UINT)
    {
      AddCt2Monomial(-1.0,&f);AddVariable2Monomial(NFUN,vc,1,&f);
      AddMonomial(&f,eq);ResetMonomial(&f);
      SetEquationValue(0.0,eq);
    }
  else
    SetEquationValue(c,eq);

  DeleteMonomial(&f); 
    
  SetEquationCmp(EQU,eq);
  SetEquationType(SYSTEM_EQ,eq);
 
}

void GenerateDistanceEquation(unsigned int v1x,unsigned int v1y,unsigned int v1z,
			      unsigned int v2x,unsigned int v2y,unsigned int v2z,
			      unsigned int vc,
			      double c,
			      Tequation *eq)
{
  Tmonomial f;  
  
  InitEquation(eq);

  InitMonomial(&f);

  /* (a-b)^2=a^2-2*a*b+b^2  added for X, Y, and Z*/
  AddVariable2Monomial(NFUN,v1x,2,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddCt2Monomial(-2.0,&f);AddVariable2Monomial(NFUN,v1x,1,&f);AddVariable2Monomial(NFUN,v2x,1,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddVariable2Monomial(NFUN,v2x,2,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);

  AddVariable2Monomial(NFUN,v1y,2,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddCt2Monomial(-2.0,&f);AddVariable2Monomial(NFUN,v1y,1,&f);AddVariable2Monomial(NFUN,v2y,1,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddVariable2Monomial(NFUN,v2y,2,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  
  AddVariable2Monomial(NFUN,v1z,2,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddCt2Monomial(-2.0,&f);AddVariable2Monomial(NFUN,v1z,1,&f);AddVariable2Monomial(NFUN,v2z,1,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  AddVariable2Monomial(NFUN,v2z,2,&f);
  AddMonomial(&f,eq);ResetMonomial(&f);
  
  if (vc!=NO_UINT)
    {
      AddCt2Monomial(-1.0,&f);AddVariable2Monomial(NFUN,vc,1,&f);
      AddMonomial(&f,eq);ResetMonomial(&f);
      SetEquationValue(0.0,eq);
    }
  else
    SetEquationValue(c,eq);

  DeleteMonomial(&f); 
    
  SetEquationCmp(EQU,eq);
  SetEquationType(SYSTEM_EQ,eq);
}

unsigned int FindMonomial(Tmonomial *f,Tequation *eq)
{
  unsigned int j;
  boolean found;
  Tvariable_set *vf;

  vf=GetMonomialVariables(f);

  found=FALSE;
  j=0;
  while((j<eq->nMonomials)&&(!found))
    {
      if (CmpVarSet(vf,GetMonomialVariables(eq->monomials[j]))==0)
	found=TRUE;
      else
	j++;
    }
  if (found)
    return(j);
  else
    return(NO_UINT);
}

Tmonomial *GetMonomial(unsigned int i,Tequation *eq)
{
  if (i<eq->nMonomials)
    return(eq->monomials[i]);
  else
    return(NULL);
}

unsigned int GetNumMonomials(Tequation *eq)
{
  return(eq->nMonomials);
}

void LinearEquation2LinearConstraint(TLinearConstraint *lc,Tequation *eq)
{
  InitLinearConstraint(lc);
  if ((eq->polynomial)&&(GetEquationOrder(eq)<2))
    {
      unsigned int i,v;
      double ct;

      for(i=0;i<eq->nMonomials;i++)
	{
	  v=GetVariableN(0,GetMonomialVariables(eq->monomials[i]));
	  ct=GetMonomialCt(eq->monomials[i]);
	  AddTerm2LinearConstraint(v,ct,lc);
	}
      AddCt2LinearConstraint(-eq->value,lc);
    }
}

inline double EvaluateWholeEquation(double *varValues,Tequation *eq)
{
  double v;
  unsigned int i;

  #if (_DEBUG>2)
    if (eq->cmp==NOCMP)
      Error("Evaluation of an undefined equation");
  #endif

  v=-eq->value;

  for(i=0;i<eq->nMonomials;i++)
    v+=EvaluateMonomial(varValues,eq->monomials[i]);

  return(v);
}

double EvaluateEquation(double *varValues,Tequation *eq)
{
  double v;
  unsigned int i;

  if (eq->cmp==NOCMP)
    Error("Evaluation of an undefined equation");

  v=0.0;

  for(i=0;i<eq->nMonomials;i++)
    v+=EvaluateMonomial(varValues,eq->monomials[i]);

  return(v);
}

void EvaluateEquationInt(Tinterval *varValues,Tinterval *i_out,Tequation *eq)
{
  unsigned int i;
  Tinterval i_aux;

  if (eq->cmp==NOCMP)
    Error("Evaluation of an undefined equation");

  NewInterval(0,0,i_out);
  for(i=0;i<eq->nMonomials;i++)
    {
      EvaluateMonomialInt(varValues,&i_aux,eq->monomials[i]);
      IntervalAdd(i_out,&i_aux,i_out);
    }
}

void DeriveEquation(unsigned int nv,Tequation *d,Tequation *eq)
{
  Tmonomial f;
  unsigned int i;

  d->cmp=EQU;
  d->type=DERIVED_EQ;
  d->polynomial=TRUE;
  d->order=0.0;
  d->value=0.0;
  
  d->maxMonomials=eq->maxMonomials;
  d->nMonomials=0;
  NEW(d->monomials,d->maxMonomials,Tmonomial*);

  for(i=0;i<d->maxMonomials;i++)
    d->monomials[i]=NULL;
  InitVarSet(&(d->vars));

  for(i=0;i<eq->nMonomials;i++)
    {
      DeriveMonomial(nv,&f,eq->monomials[i]);
      AddMonomial(&f,d);
      DeleteMonomial(&f);
    }
}


void PrintMonomialsInLine(FILE *f,char **varNames,Tequation *eq)
{
  unsigned int i;

  for(i=0;i<eq->nMonomials;i++)
    PrintMonomial(f,(i==0),varNames,eq->monomials[i]);

  if (fabs(eq->value)>ZERO)
    fprintf(f,"%+.12g",-eq->value);
  else
    {
      if (eq->nMonomials==0)
	fprintf(f,"0");
    }
}

void PrintMonomials(FILE *f,char **varNames,Tequation *eq)
{
  if (eq->cmp!=EQU)
    PrintEquation(f,varNames,eq);
  else
    {
      PrintMonomialsInLine(f,varNames,eq);
      fprintf(f,"\n");
    }
}

void PrintEquation(FILE *f,char **varNames,Tequation *eq)
{
  unsigned int i;
  double s;

  fprintf(f,"   ");
  for(i=0;i<eq->nMonomials;i++)
    PrintMonomial(f,(i==0),varNames,eq->monomials[i]);

  if (eq->nMonomials>0)
    {
      switch(eq->cmp)
	{
	case EQU:
	  fprintf(f," = ");
	  break;
	case GEQ:
	  fprintf(f," >= ");
	  break;
	case LEQ:
	  fprintf(f," <= ");
	  break;
	case NOCMP:
	  fprintf(f,"??\n");
	  Error("Unkown equation type in PrintEquation");
	  break;
	}
      s=1.0;
    }
  else
    s=-1.0;
  fprintf(f,"%.12g;\n",s*eq->value);
}

void DeleteEquation(Tequation *eq)
{  
  ResetEquationMonomials(eq);
  free(eq->monomials);
  
  DeleteVarSet(&(eq->vars));
}
