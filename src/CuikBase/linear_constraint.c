#include "linear_constraint.h"

#include "defines.h"
#include "interval.h"

#include <string.h>
#include <math.h>

/** \file linear_constraint.c
    \brief Implementaton of the function operating on TLinearConstraint.
    
    Implementaton of the function operating on TLinearConstraint.

    \sa TLinearConstraint, linear_constraint.h.
*/

void InitLinearConstraint(TLinearConstraint *lc)
{
  lc->max=INIT_NUM_TERMS_LC;
  NEW(lc->ind,lc->max,unsigned int);
  NEW(lc->val,lc->max,double);
  ResetLinearConstraint(lc);
}

void ResetLinearConstraint(TLinearConstraint *lc)
{
  lc->n=0;
  NewInterval(0,0,&(lc->error)); /*This is updated via intersections -> INF works */
}

void CopyLinearConstraint(TLinearConstraint *lc_dst,TLinearConstraint *lc_src)
{
  lc_dst->n=lc_src->n;
  lc_dst->max=lc_src->max;
  NEW(lc_dst->ind,lc_src->max,unsigned int);
  NEW(lc_dst->val,lc_src->max,double);

  memcpy(lc_dst->ind,lc_src->ind,lc_dst->n*sizeof(unsigned int)); 
  memcpy(lc_dst->val,lc_src->val,lc_dst->n*sizeof(double));

  CopyInterval(&(lc_dst->error),&(lc_src->error));
}

boolean BoundedLinearConstraint(TLinearConstraint *lc)
{
  return((LowerLimit(&(lc->error))!=-INF)||(UpperLimit(&(lc->error))!=+INF));
}

inline unsigned int GetNumTermsInLinearConstraint(TLinearConstraint *lc)
{
  return(lc->n);
}

inline double *GetLinearConstraintCoefficients(TLinearConstraint *lc)
{
  return(lc->val);
}

inline double GetLinearConstraintCoefficient(unsigned int i,TLinearConstraint *lc)
{
  return((i<lc->n)?lc->val[i]:0.0);
}

inline unsigned int *GetLinearConstraintVariables(TLinearConstraint *lc)
{
  return(lc->ind);
}

inline unsigned int GetLinearConstraintVariable(unsigned int i,TLinearConstraint *lc)
{
  return((i<lc->n)?lc->ind[i]:NO_UINT);
}

inline void GetLinearConstraintError(Tinterval *error,TLinearConstraint *lc)
{
  CopyInterval(error,&(lc->error));
}

double GetLinearConstraintErrorSize(TLinearConstraint *lc)
{
  return(IntervalSize(&(lc->error)));
}

void SetLinearConstraintError(Tinterval *error,TLinearConstraint *lc)
{
  CopyInterval(&(lc->error),error); 
}

void AddCt2LinearConstraint(double ct,TLinearConstraint *lc)
{
  IntervalOffset(&(lc->error),-ct,&(lc->error));
}

void AddTerm2LinearConstraint(unsigned int ind,double val,TLinearConstraint *lc)
{
  if (val!=0.0)
    {
      boolean found;
      unsigned int i;

      found=FALSE;
      i=0;
      while((!found)&&(i<lc->n))
	{
	  found=(lc->ind[i]==ind);
	  if (!found) i++;
	}
      if (!found)
	{
	  if (lc->n==lc->max) /* i==lc->n  */
	    {
	      MEM_DUP(lc->ind,lc->max,unsigned int);
	      MEM_EXPAND(lc->val,lc->max,double);
	    }
	  lc->ind[lc->n]=ind;
	  lc->val[lc->n]=val;
	  lc->n++;
	}
      else
	lc->val[i]+=val;
    }
}

double RemoveTermFromLinearConstraint(unsigned int ind,TLinearConstraint *lc)
{
  unsigned int i,j;
  boolean found;
  double ct;

  found=FALSE;
  i=0;
  while((!found)&&(i<lc->n))
    {
      found=(lc->ind[i]==ind);
      if (!found) i++;
    }
 
  if (found)
    {
      ct=lc->val[i];
      for(j=i+1;j<lc->n;j++)
	{
	  lc->ind[j-1]=lc->ind[j];
	  lc->val[j-1]=lc->val[j]; 
	}
      lc->n--;
    }
  else
    ct=0.0;
  
  return(ct);
}

boolean LinearConstraintIncludes(unsigned int ind,TLinearConstraint *lc)
{
  unsigned int i;
  boolean found;

  found=FALSE;
  i=0;
  while((!found)&&(i<lc->n))
    {
      found=(lc->ind[i]==ind);
      if (!found) i++;
    }

  return(found);
}

double LinearConstraintFactor(unsigned int ind,TLinearConstraint *lc)
{
  unsigned int i;
  boolean found;
  double ct;

  found=FALSE;
  i=0;
  ct=0.0;
  while((!found)&&(i<lc->n))
    {
      found=(lc->ind[i]==ind);
      if (found) ct=lc->val[i];
      else i++;
    }

  return(ct);
}

void InvertLinearConstraint(TLinearConstraint *lc)
{
  unsigned int i;

  for(i=0;i<lc->n;i++) 
    lc->val[i]=-lc->val[i];

  IntervalInvert(&(lc->error),&(lc->error));
}

void ScaleLinearConstraint(double a,TLinearConstraint *lc)
{   
  unsigned int i;
  TLinearConstraint lc2;

  InitLinearConstraint(&lc2);
    
  for(i=0;i<lc->n;i++) 
    AddTerm2LinearConstraint(lc->ind[i],lc->val[i]*a,&lc2);

  IntervalScale(&(lc->error),a,&(lc2.error));

  DeleteLinearConstraint(lc);
  CopyLinearConstraint(lc,&lc2);
  DeleteLinearConstraint(&lc2);
}

void AddLinearConstraints(TLinearConstraint *lc1,TLinearConstraint *lc2)
{
  unsigned int i;

  IntervalAdd(&(lc1->error),&(lc2->error),&(lc2->error));
  
  for(i=0;i<lc1->n;i++)
    AddTerm2LinearConstraint(lc1->ind[i],lc1->val[i],lc2);
}

/*
  This converts almost punctual ranges into points 

  A> Variables in the LC with very narrow range can be removed from the LC and
     added to the error term. This enhances the numerical robustness of the system. 
     This only makes sense if we do not convert a punctual
     error term into a narrow interval since this  would only displace the problem
     from one variable (column variable) to another (row variable).

  B> If, due to numerical roundings, we end up with a LC with a extremely narrow error
     term, we convert this error to a point. In theory this can lead to losing solutions
     but in general too narrow ranges lead to numerical inestabilities. 
*/
void CleanLinearConstraint(double epsilon,Tinterval *is,TLinearConstraint *lc)
{
  TLinearConstraint lcInt;
  Tinterval error,r;
  unsigned int i,k;

  InitLinearConstraint(&lcInt);
  
  CopyInterval(&error,&(lc->error));
  
  for(i=0;i<lc->n;i++)
    {
      k=lc->ind[i];
      
      if ((fabs(lc->val[i])<=epsilon)||
	  (IntervalSize(&(is[k]))<=epsilon))
	{
	  IntervalScale(&(is[k]),-lc->val[i],&r);
	  IntervalAdd(&r,&error,&error);
	}
      else
	AddTerm2LinearConstraint(k,lc->val[i],&lcInt);
    }
  
  CopyInterval(&(lcInt.error),&error);
  
  DeleteLinearConstraint(lc);
  CopyLinearConstraint(lc,&lcInt);
  DeleteLinearConstraint(&lcInt);
}

boolean SimplifyLinearConstraint(boolean *full,Tinterval *is,TLinearConstraint *lc)
{
  boolean simplified;

  /* \sum k_i x_i = error  */
  /* for just one variable in the linear constraint */
  /* k*x = error */
  /* x= error/k */
  *full=TRUE;
  simplified=FALSE;

  if (lc->n==1)
    {
      Tinterval a,one;
      unsigned int k;

      simplified=TRUE;
      
      NewInterval(1,1,&one);
      /* The coefficients of the linear constraint can be affected by some noise
         due to floating point roundings when operating them. We add a small
         range (1e-11) to compensate for those possible errors. */
      NewInterval(lc->val[0]-ZERO,lc->val[0]-ZERO,&a);
      IntervalDivision(&one,&a,&a);
      IntervalProduct(&a,&(lc->error),&a);
      
      k=lc->ind[0];

      *full=Intersection(&a,&(is[k]),&(is[k]));      
    }

  return(simplified);
}

unsigned int CropLinearConstraint(double epsilon,unsigned int varType,Tbox *b,Tvariables *vs,
				  TLinearConstraint *lc)
{
  #if (_DEBUG>6)
    printf("            Cropping linear constraint: ");
    PrintLinearConstraint(stdout,TRUE,NULL,lc);
  #endif

  if ((lc->n==0)||(IntervalSize(&(lc->error))>=INF))
    return(NOT_REDUCED_BOX);
  else
    {
      Tinterval out,new_range,range,a,ct,one,zero;
      unsigned int j,k,x_j;
      unsigned int status;
      Tinterval *is;
      boolean haveInf;

      is=GetBoxIntervals(b);
      
      /* We have 
	          \sum k_i x_i = error
	          \sum k_i x_i - k_j x_j + k_j x_j = error 
	           k_j x_j= error - \sum(i!=k) k_i x_i  
                   x_j = (error + \sum(i!=k) - k_i x_i))/k_j
	         
	 We evaluate the equation using interval arithmetics and then
	 we use the result
      */
  
      status=NOT_REDUCED_BOX;

      for(j=0;((j<lc->n)&&(status!=EMPTY_BOX));j++)
	{
	  x_j=lc->ind[j];

	  /* if still makes sense to crop the range x_j */
	  if ((GetVariableTypeN(x_j,vs)&varType)&&
	      (IntervalSize(&(is[x_j]))>=10*epsilon))
	    {
	      #if (_DEBUG>6)
	        printf("              Cropping var v[%u] with range ",x_j);
		PrintInterval(stdout,&(is[x_j]));
		printf(" (%f)\n",IntervalSize(&(is[x_j])));
	      #endif

	      CopyInterval(&out,&(lc->error));

	      /* The linear constraint error can be affected by some noise
		 due to floating point roundings when operating them. We add a small
		 range (1e-11) to compensate for those possible errors. */
	      NewInterval(-ZERO,ZERO,&zero);
	      IntervalAdd(&out,&zero,&out);

	      haveInf=FALSE; /* if one of the ranges other than 'x_j' is infinite
			        it is not worth th reduce x_j */

	      for(k=0;((!haveInf)&&(k<lc->n));k++)
		{
		  if (k!=j)
		    {
		      if (IntervalSize(&(is[lc->ind[k]]))<INF)
			{
			  /* The coefficients of the linear constraint can be affected by some noise
			     due to floating point roundings when operating them. We add a small
			     range (1e-11) to compensate for those possible errors. */
			  NewInterval(-lc->val[k]-ZERO,-lc->val[k]+ZERO,&ct);
			  IntervalProduct(&(is[lc->ind[k]]),&ct,&a);
			  IntervalAdd(&out,&a,&out);
			}
		      else
			haveInf=TRUE;
		    }
		}

	      if (!haveInf)
		{
		  
		  #if (_DEBUG>6)
		    printf("                %.12f*v[%u]=",lc->val[j],x_j);
		    PrintInterval(stdout,&out);
		    printf(" (%f)\n",IntervalSize(&out));
		  #endif
		    
		  /* The coefficients of the linear constraint can be affected by some noise
		     due to floating point roundings when operating them. We add a small
		     range (1e-11) to compensate for those possible errors. */
		  NewInterval(lc->val[j]-ZERO,lc->val[j]+ZERO,&ct);
		      
		  if (fabs(lc->val[j])<=10*epsilon)  
		    {
		      /* We have a very small coefficient. Since the coeficient is used to divide,
		         we have to avoid a "division by zero" numerical error. In these cases
		         we just check if the linear constraint holds, i.e., if 
			 ct*range_var intersects with the linear constraint error.
		      */
		      IntervalProduct(&ct,&(is[x_j]),&range);

		      #if (_DEBUG>6)
		        printf("                Small constant. Avoid division by zero\n");
			printf("                Forward range: ");
			PrintInterval(stdout,&range);
			printf(" (%f)\n",IntervalSize(&range));

			Intersection(&range,&out,&new_range);
			printf("                Intersection range: ");
			PrintInterval(stdout,&new_range);
			printf(" (%f)\n",IntervalSize(&new_range));
		      #endif

		      if (!Intersection(&range,&out,&new_range))
			status=EMPTY_BOX;
		    }
		  else
		    {
		      NewInterval(1-ZERO,1+ZERO,&one);
		      IntervalDivision(&one,&ct,&ct);
		      IntervalProduct(&ct,&out,&range);	      
		      
		      #if (_DEBUG>6)
		        printf("                Temptative new range v[%u]: ",x_j);
			PrintInterval(stdout,&range);
			printf(" (%f)\n",IntervalSize(&range));
		      #endif

		      if (Intersection(&(is[x_j]),&range,&new_range))
			{
			  double s1,s2;
			  
			  #if (_DEBUG>6)
			    printf("                New range v[%u]: ",x_j);
			    PrintInterval(stdout,&new_range);
			    printf(" (%f)\n",IntervalSize(&new_range));
			  #endif
			  
			  s1=IntervalSize(&(is[x_j]));
			  s2=IntervalSize(&new_range);
			  if (s2<(s1-ZERO))
			    {
			      CopyInterval(&(is[x_j]),&new_range);
			      status=REDUCED_BOX;
			    }
			}
		      else
			status=EMPTY_BOX;
		    }
		}
	    }
	}

      return(status);
    }
}

/* 
   We compare the linear constraints using the angle between them (i.e., between
   the vectors defining the hyperplane of the constraint).
   The output "scale" gives ct so tath lc1*scale=lc2
*/
boolean CmpLinearConstraints(double *scaleOne2Two,TLinearConstraint *lc1,TLinearConstraint *lc2)
{
  boolean equal;
  
  equal=FALSE;

  if (lc1->n==lc2->n)
    {
      unsigned int j,l;
      double n1,n2,n12,c;
      
      n12=0;
      equal=TRUE;
      j=0;
      while((equal)&&(j<lc1->n))
	{
	  /* look for ind[j] in lc */
	  equal=FALSE;
	  l=0;
	  while((!equal)&&(l<lc2->n))
	    {
	      equal=(lc1->ind[j]==lc2->ind[l]);
	      if (equal)
		n12+=(lc1->val[j]*lc2->val[l]);
	      else
		l++;
	    }
	  j++;
	}

      if(equal)
	{
	  n1=0.0;
	  n2=0.0;
	  for(j=0;j<lc1->n;j++)
	    {
	      n1+=(lc1->val[j]*lc1->val[j]);
	      n2+=(lc2->val[j]*lc2->val[j]);
	    }
	  n1=sqrt(n1);
	  n2=sqrt(n2);

	  /* If the cosinus between the to normals defining the constrain planes
	     is close to one, then the constraints are almost equivalent (up to the
	     error than can be cleverly merged) */
	  c=n12/(n1*n2); /*cosinus -> [-1,1]*/
	  equal=((fabs(c-1.0)<=ZERO)||(fabs(c+1.0)<=ZERO));
	  
	  if (equal)
	    {
	      /*This scale converts lc1 into lc2*/

	      /*define scale: the cosinus (known to be close to -1 or to 1) gives
	        the sign and the norms the magnituge*/
	      *scaleOne2Two=(c<0?-1.0:1.0)*n2/n1;
	      
	      /*Could also be c*n2/n1 because c is very close to one*/
	    }
	}
    }
  return(equal);
}

double EvaluateLinearConstraint(double *varValues,TLinearConstraint *lc)
{
  double v;
  unsigned int kk;

  v=0;
  for(kk=0;kk<lc->n;kk++)
    v+=(lc->val[kk]*varValues[lc->ind[kk]]);

  return(v);
}

void EvaluateLinearConstraintInt(Tinterval *varValues,Tinterval *i_out,TLinearConstraint *lc)
{
  unsigned int kk;
  Tinterval a,r;

  NewInterval(0,0,i_out);
  for(kk=0;kk<lc->n;kk++)
    {
      /* The coefficients of the linear constraint can be affected by some noise
	 due to floating point roundings when operating them. We add a small
	 range (1e-11) to compensate for those possible errors. */
      NewInterval(lc->val[kk]-ZERO,lc->val[kk]+ZERO,&a);
      IntervalProduct(&(varValues[lc->ind[kk]]),&a,&r);
      IntervalAdd(&r,i_out,i_out);
    }
}

void PrintLinearConstraint(FILE *f,boolean eq,char **varName,TLinearConstraint *lc)
{
  unsigned int kk;
  Tinterval e;

  for(kk=0;kk<lc->n;kk++)
    {
      if (lc->val[kk]==1)
	{
	  if (kk>0)
	   fprintf(f,"+"); 
	}
      else
	{
	  if (lc->val[kk]==-1)
	    fprintf(f,"-");
	  else
	    fprintf(f,"%+.12g*",lc->val[kk]);
	}

      if (varName==NULL)
	fprintf(f,"v_%u",lc->ind[kk]);
      else
	fprintf(f,"%s",varName[lc->ind[kk]]);
	
    }
  if (eq)
    {
      fprintf(f," = ");
      PrintInterval(f,&(lc->error));
      fprintf(f," (s:%g)",IntervalSize(&(lc->error)));
    }
  else
    {
      if (IntervalSize(&(lc->error))<ZERO)
	{
	  double c;
	  
	  c=IntervalCenter(&(lc->error));
	  if ((c!=0.0)||(lc->n==0))
	    fprintf(f," %+.12g",-c);
	}
      else
	{
	  IntervalInvert(&(lc->error),&e);
	  fprintf(f," + ");
	  PrintInterval(f,&e);
	}
    }
  fprintf(f,"\n");
}

void SaveLinearConstraint(FILE *f,TLinearConstraint *lc)
{
  unsigned int i;

  fprintf(f,"%u %u ",lc->n,lc->max);

  for(i=0;i<lc->n;i++)
    fprintf(f,"%u %f ",lc->ind[i],lc->val[i]);

  fprintf(f," %f %f ",LowerLimit(&(lc->error)),UpperLimit(&(lc->error)));
}

void LoadLinearConstraint(FILE *f,TLinearConstraint *lc)
{  
  unsigned int i;
  double l,u;

  fscanf(f,"%u %u",&(lc->n),&(lc->max));
  NEW(lc->ind,lc->max,unsigned int);
  NEW(lc->val,lc->max,double);
  
  for(i=0;i<lc->n;i++)
    {
      fscanf(f,"%u",&(lc->ind[i]));
      fscanf(f,"%lf",&(lc->val[i]));
    }
  fscanf(f,"%lf",&l);
  fscanf(f,"%lf",&u);
  NewInterval(l,u,&(lc->error));
}


void DeleteLinearConstraint(TLinearConstraint *lc)
{
  free(lc->ind);
  free(lc->val);
  DeleteInterval(&(lc->error));
}


