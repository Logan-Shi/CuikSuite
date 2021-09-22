#include "mequation.h"

#include "error.h"
#include "basic_algebra.h"

#include <string.h>
#include <math.h>


/** 
    \file mequation.c
 
    \brief Implementation of the matrix equation operations.

     Implementation of the matrix equation operations.

    \sa TMequation, mequation.h.
*/

/** 
   \brief Determines the scalar equations derived from a metrix one.

   Determines the scalar equations derived from a matrix one taking into
   account the used dof.

   \param me The matrix equation to update.
*/
void RecomputeScalarEquations(TMequation *me);

void RecomputeScalarEquations(TMequation *me)
{
#if (0)
  unsigned int nRot,nTrans;
  
  me->neq=0;
  nRot=1;
  nTrans=1;
#else
  unsigned int i,nRot,nTrans;
  boolean ctAllTrans;
  unsigned int dof[6]={0,0,0,0,0,0};

 for(i=0;i<me->n;i++)
   UpdateUsedDOF(dof,me->ts[i]);

 nRot=(dof[RX]+dof[RY]+dof[RZ]);
 nTrans=(dof[TX]+dof[TY]+dof[TZ]);

 /* Check if all ct transforms are translations */
 ctAllTrans=TRUE;
 for(i=0;((ctAllTrans)&&(i<me->n));i++)
   ctAllTrans=(!HasCtRotTransSeq(me->ts[i]));

 me->neq=0;
 if ((ctAllTrans)&&(nRot>0)&&(nTrans==0))
   {
     /* Check if all rotations are aligned -> plannar mechanism */
     if (dof[RX]==nRot)
       {
	 #if (REDUNDANT_EQ_MATRIX)
	   me->r[0]=AXIS_Z; me->c[0]=AXIS_Y;
	   me->r[1]=AXIS_Y; me->c[1]=AXIS_Z;
	   me->r[2]=AXIS_Y; me->c[2]=AXIS_Y;
	   me->r[3]=AXIS_Z; me->c[3]=AXIS_Z;
	   me->r[4]=AXIS_Y; me->c[4]=AXIS_H;
	   me->r[5]=AXIS_Z; me->c[5]=AXIS_H;
	   me->neq=6;
	 #else
	   me->r[0]=AXIS_Z; me->c[0]=AXIS_Y;
	   me->r[1]=AXIS_Y; me->c[1]=AXIS_Z;
	   me->r[2]=AXIS_Y; me->c[2]=AXIS_H;
	   me->r[3]=AXIS_Z; me->c[3]=AXIS_H;
	   me->neq=4;
	 #endif
	  
       }
    if (dof[RY]==nRot)
       {
	 #if (REDUNDANT_EQ_MATRIX)
	   me->r[0]=AXIS_X; me->c[0]=AXIS_Z;
	   me->r[1]=AXIS_Z; me->c[1]=AXIS_X;
	   me->r[2]=AXIS_X; me->c[2]=AXIS_X;
	   me->r[3]=AXIS_Z; me->c[3]=AXIS_Z;
	   me->r[4]=AXIS_X; me->c[4]=AXIS_H;
	   me->r[5]=AXIS_Z; me->c[5]=AXIS_H;
	   me->neq=6;
	 #else
	   me->r[0]=AXIS_X; me->c[0]=AXIS_Z;
	   me->r[1]=AXIS_Z; me->c[1]=AXIS_X;
	   me->r[2]=AXIS_X; me->c[2]=AXIS_H;
	   me->r[3]=AXIS_Z; me->c[3]=AXIS_H;
	   me->neq=4;
	 #endif
       }
    if (dof[RZ]==nRot)
       {
	 #if (REDUNDANT_EQ_MATRIX)
	   me->r[0]=AXIS_Y; me->c[0]=AXIS_X;
	   me->r[1]=AXIS_X; me->c[1]=AXIS_Y;
	   me->r[2]=AXIS_X; me->c[2]=AXIS_X;
	   me->r[3]=AXIS_Y; me->c[3]=AXIS_Y;
	   me->r[4]=AXIS_X; me->c[4]=AXIS_H;
	   me->r[5]=AXIS_Y; me->c[5]=AXIS_H;
	   me->neq=6;
	 #else
	   me->r[0]=AXIS_Y; me->c[0]=AXIS_X;
	   me->r[1]=AXIS_X; me->c[1]=AXIS_Y;
	   me->r[2]=AXIS_X; me->c[2]=AXIS_H;
	   me->r[3]=AXIS_Y; me->c[3]=AXIS_H;
	   me->neq=4;
	 #endif
       }
   }
#endif

 /* If none of the special cases -> general case  */
 /* Ct equations also define equations (ct equations) */
 if (me->neq==0)
   {
     #if (REDUNDANT_EQ_MATRIX)
       me->r[0]=AXIS_Z; me->c[0]=AXIS_Y;
       me->r[1]=AXIS_X; me->c[1]=AXIS_Z;
       me->r[2]=AXIS_Y; me->c[2]=AXIS_X;
       me->r[3]=AXIS_X; me->c[3]=AXIS_X;
       me->r[4]=AXIS_Y; me->c[4]=AXIS_Y;
       me->r[5]=AXIS_Z; me->c[5]=AXIS_Z;
       me->r[6]=AXIS_X; me->c[6]=AXIS_H;
       me->r[7]=AXIS_Y; me->c[7]=AXIS_H;
       me->r[8]=AXIS_Z; me->c[8]=AXIS_H;
       me->neq=9;
     #else
       me->r[0]=AXIS_Z; me->c[0]=AXIS_Y;
       me->r[1]=AXIS_X; me->c[1]=AXIS_Z;
       me->r[2]=AXIS_Y; me->c[2]=AXIS_X;
       me->r[3]=AXIS_X; me->c[3]=AXIS_H;
       me->r[4]=AXIS_Y; me->c[4]=AXIS_H;
       me->r[5]=AXIS_Z; me->c[5]=AXIS_H;
       me->neq=6;
     #endif
       
   }
}

void InitMEquation(TMequation *me)
{
  me->n=1;
  me->simp=FALSE;
  me->velocity=FALSE;
  me->nonDynamic=FALSE;

  NEW(me->vID,me->n,unsigned int);
  me->vID[0]=NO_UINT;
  
  NEW(me->ts,me->n,TTransSeq*);
  NEW(me->ts[0],1,TTransSeq);
  InitTransSeq(me->ts[0]);
  HTransformIdentity(&(me->rhs));
  AddCtTrans2TransSeq(&(me->rhs),me->ts[0]);

  me->neq=0;
  RecomputeScalarEquations(me);
}

void CopyMEquation(TMequation *me_dst,TMequation *me_src)
{
  unsigned int i;
  
  me_dst->n=me_src->n;
  me_dst->simp=me_src->simp;
  me_dst->velocity=me_src->velocity;
  me_dst->nonDynamic=me_src->nonDynamic;

  NEW(me_dst->vID,me_dst->n,unsigned int);
  NEW(me_dst->ts,me_dst->n,TTransSeq*);
  for(i=0;i<me_dst->n;i++)
    {
      me_dst->vID[i]=me_src->vID[i];
      
      NEW(me_dst->ts[i],1,TTransSeq);
      CopyTransSeq(me_dst->ts[i],me_src->ts[i]);
    }
  HTransformCopy(&(me_dst->rhs),&(me_src->rhs));
  me_dst->neq=me_src->neq;
  for(i=0;i<me_dst->neq;i++)
    {
      me_dst->r[i]=me_src->r[i];
      me_dst->c[i]=me_src->c[i];
    }
}

void ResetMEquation(TMequation *me)
{
  if (me->n>1)
    Error("Reseting a non-basic matrix equation.");

  ResetTransSeq(me->ts[0]);
  me->vID[0]=NO_UINT;
  HTransformIdentity(&(me->rhs));
  me->neq=0;
  me->simp=FALSE;
  me->velocity=FALSE;
  me->nonDynamic=FALSE;
}

boolean IsEmptyMEquation(TMequation *me)
{
  return(me->neq==0);
}

unsigned int MEquationNTerms(TMequation *me)
{
  return((IsEmptyMEquation(me)?0:me->n));
}

unsigned int MEquationMaxVars(TMequation *me)
{
  unsigned int i,n,m;

  m=0;
  for(i=0;i<me->n;i++)
    {
      n=TransSeqMaxVars(me->ts[i]);
      if (n>m) m=n;
    }
  
  return(m);
}

boolean MEquationHasRepeatedVar(TMequation *me)
{
  unsigned int i;
  boolean found;

  found=FALSE;
  for(i=0;((!found)&&(i<me->n));i++)
    {
      found=HasRepeatedVar(me->ts[i]);
    }
  
  return(found);
}

unsigned int MEquationSize(TMequation *me)
{
  unsigned int i,s,l;

  s=0;
  for(i=0;i<me->n;i++)
    {
      l=TransSeqSize(me->ts[i]);
      if (l>s) s=l;
    }
  return(s);
}

boolean HasRotations(TMequation *me)
{
  unsigned int dof[6]={0,0,0,0,0,0};
  unsigned int i;

  for(i=0;i<me->n;i++)
    UpdateUsedDOF(dof,me->ts[i]);
  
  return((dof[RX]+dof[RY]+dof[RZ])>0);
}

void IdentityRHSMEquation(TMequation *me)
{
  HTransformIdentity(&(me->rhs));
}

void ZeroRHSMEquation(TMequation *me)
{
  HTransformZero(&(me->rhs));
}

void SetTranslationMEquation(TMequation *me)
{
  unsigned int i;

  if (me->neq==0)
    Error("Modifying an empty matrix equation");

  me->simp=TRUE;

  me->neq=3;
  for(i=0;i<3;i++)
    {
      me->r[i]=i;
      me->c[i]=AXIS_H;
    }
}

boolean VarIncludedinMEquation(unsigned int v,TMequation *me)
{
  unsigned int i;
  boolean found;

  found=FALSE;
  i=0;
  while((!found)&&(i<me->n))
    {
      found=((me->vID[i]==v)||(VarIncludedinTransSeq(v,me->ts[i])));
      i++;
    }
  return(found);
}

void AddDispTrans2MEquation(int s,unsigned int v,
			    double *vect,TMequation *me)
{
  if (me->n>1)
    Error("Adding a displace term to a non-basic matrix equation.");
  if (me->simp)
    Error("Adding a displace term an already simplified matrix equation.");
   
  AddDispTrans2TransSeq(s,v,vect,me->ts[0]);
  
  RecomputeScalarEquations(me);
}

void AddVarTrans2MEquation(unsigned int t,int s,unsigned int v,TMequation *me)
{
  if (me->n>1)
    Error("Adding terms to a non-basic matrix equation.");
  if (me->simp)
    Error("Adding terms an already simplified matrix equation.");

  AddVarTrans2TransSeq(t,s,v,me->ts[0]);
  
  RecomputeScalarEquations(me);
}

void AddPatchTrans2MEquation(unsigned int t,int s,unsigned int u,unsigned int v,
			     double **p,TMequation *me)
{
  if (me->n>1)
    Error("Adding terms to a non-basic matrix equation.");
  if (me->simp)
    Error("Adding terms an already simplified matrix equation.");

  AddPatchTrans2TransSeq(t,s,u,v,p,me->ts[0]);
  
  RecomputeScalarEquations(me);
}

void AddCtTrans2MEquation(THTransform *t,TMequation *me)
{
  if (me->n>1)
    Error("Adding terms to a non-basic matrix equation.");
  if (me->simp)
    Error("Adding terms an already simplified matrix equation.");

  AddCtTrans2TransSeq(t,me->ts[0]);

  RecomputeScalarEquations(me);
}

void AddTransSeq2MEquation(int s,TTransSeq *ts,TMequation *me)
{
  int i;
  unsigned int n;
  TTrans taux;
  
  if (me->n>1)
    Error("Adding terms to a non-basic matrix equation.");

  if (me->simp)
    Error("Adding terms an already simplified matrix equation.");

  n=TransSeqSize(ts);
  if (n>0)
    {
      if (s<0)
	{
	  for(i=n-1;i>=0;i--)
	    {
	      TransInvert(&taux,GetElementFromTransSeq(i,ts));
	      AddTrans2TransSeq(&taux,me->ts[0]);
	      DeleteTrans(&taux);
	    }
	}
      else
	{
	  for(i=0;i<(signed int)n;i++)
	    AddTrans2TransSeq(GetElementFromTransSeq(i,ts),me->ts[0]);
	}
      RecomputeScalarEquations(me);
    }
}

unsigned int NumberScalarEquations(TMequation *me)
{
  return(me->neq);
}

void ShiftVariablesInMEquation(unsigned int nv,TMequation *me)
{
  unsigned int i;

  for(i=0;i<me->n;i++)
    {
      if ((me->vID[i]!=NO_UINT)&&(me->vID[i]>nv))
	me->vID[i]--;
      ShiftVariablesInTransSeq(nv,me->ts[i]);
    }
}

unsigned int FixVarInMEquation(unsigned int nv,double v,TMequation *me)
{
  unsigned int i;
  TTransSeq **tsOrig;
  unsigned int nOrig;
  unsigned int r;
  THTransform ctt;
  
  tsOrig=me->ts;
  nOrig=me->n;

  NEW(me->ts,me->n,TTransSeq *);
  me->n=0;
  
  for(i=0;i<nOrig;i++)
    {
      if (me->vID[i]==nv)
	Error("Can not fix a variable used to scale a matrix equation");
      
      if (FixVarInTransSeq(nv,v,&ctt,tsOrig[i]))
	{
	  /* tsOrig[i] is now constant */
	  HTransformSubstract(&(me->rhs),&ctt,&(me->rhs));
	  DeleteTransSeq(tsOrig[i]);
	}
      else
	{
	  /* non-ct tsOrig[i] -> just add it to tne new equation */
	  me->ts[me->n]=tsOrig[i];
	  me->n++;
	}
      HTransformDelete(&ctt);
    }
  free(tsOrig);
  
  if (me->n==0)
    {
      /* The hole matrix equation is ct */
      if (HTransformIsZero(&(me->rhs)))
	r=1; /* ct and holds */
      else
	r=2; /* ct and does not hold */
    }
  else
    r=0; /* normal case */

  me->simp=FALSE;
  SimplifyMEquation(me);
  
  return(r);
}

void ReplaceVarInMEquation(unsigned int nv,unsigned int nvNew,TMequation *me)
{
  unsigned int i;

  for(i=0;i<me->n;i++)
    {
      if (me->vID[i]==nv)
	me->vID[i]=nvNew;
      ReplaceVarInTransSeq(nv,nvNew,me->ts[i]);
    }
}

boolean SimplifiedMEquation(TMequation *me)
{
  return(me->simp);
}

void MakeTranslationMEquation(TMequation *me)
{
  me->r[0]=AXIS_X; me->c[0]=AXIS_H;
  me->r[1]=AXIS_Y; me->c[1]=AXIS_H;
  me->r[2]=AXIS_Z; me->c[2]=AXIS_H;
  me->neq=3;
}

void SimplifyMEquation(TMequation *me)
{
  if (me->simp)
    Error("Re-simplifying a matrix equation?");

  me->simp=TRUE;
  
  if ((me->neq>0)&&(me->n==1)&&(HTransformIsIdentity(&(me->rhs))))
    SimplifyTransSeq(me->ts[0]);
  
  RecomputeScalarEquations(me);
}

void MarkAsVelocityMEquation(TMequation *me)
{
  me->velocity=TRUE;
  me->nonDynamic=FALSE;
}

boolean IsVelocityMEquation(TMequation *me)
{
  return(me->velocity);
}

void MarkAsNonDynamicMEquation(TMequation *me)
{
  me->nonDynamic=TRUE;
  me->velocity=FALSE;
}

boolean IsPositionMEquation(TMequation *me)
{
  return((!me->velocity)&&(!me->nonDynamic));
}

boolean IsNonDynamicMEquation(TMequation *me)
{
  return(me->nonDynamic);
}

void RewriteMEquation2Orig(Tmapping *map,TMequation *me)
{
  unsigned int i,sf,so;

  for(i=0;i<me->n;i++)
    {
      /* Rewrite the scale factor, if any */
      sf=me->vID[i];
      if (sf!=NO_UINT)
	{
	  so=GetVarIDInOriginal(sf,map);
	  if (so==NO_UINT)
	    Error("Matrix equation scale variable disappeared in simplification");
	  me->vID[i]=so;
	}
      /* and rewrite the scaled matrix equation */
      RewriteTransSeq2Orig(map,me->ts[i]);
    }
}

void ScaleMEquation(unsigned int v,TMequation *me)
{
  if (HTransformIsZero(&(me->rhs)))
    {
      unsigned int i;

      for(i=0;i<me->n;i++)
	{
	  if (me->vID[i]!=NO_UINT)
	    Error("Scaling an already scaled matrix equation");
	  me->vID[i]=v;
	}
    }
  else
    Error("Scaling a matrix equation with a non-null rhs");
}

void AccumulateMEquations(unsigned int  nv,TMequation *me1,TMequation *me)
{
  unsigned int i,j,n;

  if ((!HTransformIsZero(&(me->rhs)))||
      (!HTransformIsZero(&(me1->rhs))))
    Error("Accumulating matrix equations with a non-null rhs");
  
  n=me->n+me1->n;
    
  MEM_EXPAND(me->ts,n,TTransSeq*);
  MEM_EXPAND(me->vID,n,unsigned int);
  for(i=me->n,j=0;i<n;i++,j++)
    {
      NEW(me->ts[i],1,TTransSeq);
      CopyTransSeq(me->ts[i],me1->ts[j]);
      if (me1->vID[j]!=NO_UINT)
	{
	  if (nv!=NO_UINT)
	    Error("Scaling an already scaled matrix equation in AccumulateMEquations");
	  me->vID[i]=me1->vID[j];
	}
      else
	me->vID[i]=nv;
    }
  me->n=n;
}

unsigned int NumericDDMatrixEquation(unsigned int neqs,unsigned int nvars,
				     unsigned int ce,unsigned int cie,
				     boolean *independentEq,
				     double *x,double **h,TMequation *me)
{
  if (me->n>1)
    Error("NumericDDMatrixEquation can only be used on matrix equations with a single factor");

  if (me->neq==0)
    Error("Using NumericDDMatrixEquation on an empty equation?");

  return(NumericDDTransSeq(neqs,nvars,me->neq,me->r,me->c,ce,cie,independentEq,x,h,me->ts[0]));
}

unsigned int TNumericDMatrixEquation(unsigned int neqs,unsigned int nvars,
				     unsigned int ce,unsigned int cie,
				     boolean *independentEq,
				     double *x,double *m,TMequation *me)
{
  if (me->n>1)
    Error("TNumericDMatrixEquation can only be used on matrix equations with a single factor");

  if (me->neq==0)
    Error("Using TNumericDMatrixEquation on an empty equation?");

  return(TNumericDTransSeq(neqs,nvars,me->neq,me->r,me->c,ce,cie,independentEq,x,m,me->ts[0]));
}

void DeriveMEquation(unsigned int v,TMequation *dme,TMequation *me)
{
  if (!me->simp)
    Error("Deriving a non simplified equation");

  if (me->neq==0)
    //InitMEquation(dme);
    Error("Deriving an empty equation?");
  else
    {
      unsigned int i,k,n,m,l;
      TTransSeq **ts;

      dme->n=0;
      dme->simp=TRUE; /* == me->simp */
      dme->velocity=FALSE;
      dme->nonDynamic=FALSE;
      /* an empty deriative */
      dme->ts=NULL;
      dme->vID=NULL;
      for(i=0;i<me->n;i++)
	{
	  m=((me->vID[i]==v)?1:0);

	  DeriveTransSeq(v,&n,&ts,me->ts[i]);
	  l=n+m;
	  if (l>0)
	    {
	      unsigned int j;
	      
	      k=dme->n+l;
	      if (dme->n==0)
		{
		  NEW(dme->ts,k,TTransSeq*);
		  NEW(dme->vID,k,unsigned int);
		}
	      else
		{
		  MEM_EXPAND(dme->ts,k,TTransSeq*);
		  MEM_EXPAND(dme->vID,k,unsigned int);
		}
	      if (n>0)
		{
		  memcpy(&(dme->ts[dme->n]),ts,sizeof(TTransSeq*)*n);
		  free(ts);
		  for(j=dme->n;j<dme->n+n;j++)
		    dme->vID[j]=me->vID[i];
		  dme->n+=n;
		}
	      if (m>0)
		{
		  NEW(dme->ts[dme->n],1,TTransSeq);
		  CopyTransSeq(dme->ts[dme->n],me->ts[i]);
		  dme->vID[dme->n]=NO_UINT;
		  dme->n++;
		}
	    }
	}

      HTransformZero(&(dme->rhs));

      dme->neq=me->neq;
      for(i=0;i<me->neq;i++)
	{
	  dme->r[i]=me->r[i];
	  dme->c[i]=me->c[i];
	}
    }
}

unsigned int EvaluateMEquation(double *v,double *r,TMequation *me)
{
  if (me->neq>0)
    {
      unsigned int i,j,sf;
      double sc;
      THTransform a;

      for(j=0;j<me->neq;j++)
      	r[j]=-HTransformGetElement(me->r[j],me->c[j],&(me->rhs));

      for(i=0;i<me->n;i++)
	{  
	  sf=me->vID[i];
	  sc=(sf==NO_UINT?1.0:v[sf]);
 	  EvaluateTransSeq(v,&a,me->ts[i]);
	  /*
	  {
	    fprintf(stderr,"Eq=[");
	    HTransformPrint(stderr,&a);
	    fprintf(stderr,"]\n");
	  }
	  */
	  for(j=0;j<me->neq;j++)
	    {
	      r[j]+=sc*HTransformGetElement(me->r[j],me->c[j],&a);
	    }
	  
	  HTransformDelete(&a);
	}
    }
  return(me->neq);
}

void EvaluateMEquationXVectors(double *v,unsigned int n,double *p,
			       double *r,TMequation *me)
{
  if (me->neq>0)
    {
      unsigned int i,k,sf;
      double sc;
      THTransform a;
      double p1[3];

      /* The rhs is not used since this function is only used
	 for derivatives (rhs=0)*/

      /* Initialize the result to zero */
      for(i=0;i<n;i++)
	{
	  for(k=0;k<3;k++)
	    r[3*i+k]=0;
	}
	
      /* Sum for all the terms in the matrix equation */
      for(i=0;i<me->n;i++)
	{  
	  sf=me->vID[i];
	  sc=(sf==NO_UINT?1.0:v[sf]);
	  EvaluateTransSeq(v,&a,me->ts[i]);

	  /* Now apply the matrix to all vectors */
	  for(k=0;k<n;k++)
	    {
	      HTransformApply(&(p[3*k]),p1,&a);
	      ScaleVector(sc,3,p1);
	      AccumulateVector(3,p1,&(r[3*k]));
	    }
	      
	  HTransformDelete(&a);
	}
    }
}

void PrintMEquation(FILE *f,double *x,char **varNames,TMequation *me)
{
  unsigned int i,k,sf;
  char *n;

  k=NumberScalarEquations(me);
  fprintf(f,"   %% %u scalar equations:",k);
  for(i=0;i<k;i++)
    fprintf(f," (%s,%s)",
	    (me->r[i]==AXIS_X?"x":(me->r[i]==AXIS_Y?"y":(me->r[i]==AXIS_Z?"z":"t"))),
	    (me->c[i]==AXIS_X?"x":(me->c[i]==AXIS_Y?"y":(me->c[i]==AXIS_Z?"z":"t"))));
  fprintf(f,"\n   ");
  for(i=0;i<me->n;i++)
    {
      PrintTransSeq(f,x,varNames,me->ts[i]);
      
      sf=me->vID[i];
      if (sf!=NO_UINT)
	{
	  fprintf(f,"*");
	  if (varNames!=NULL)
	    {
	      n=varNames[sf];
	      PRINT_VARIABLE_NAME(f,n);
	    }
	  else
	    fprintf(f,"v_%u",sf);
	}
      if (i<(me->n-1))
	fprintf(f,"+\n   ");
    } 
  fprintf(f,"=");
  if (HTransformIsIdentity(&(me->rhs)))
    fprintf(f,"Id;\n");
  else
    fprintf(f,"Z;\n");
}


void DeleteMEquation(TMequation *me)
{
  unsigned int i;

  if (me->ts!=NULL)
    {
      for(i=0;i<me->n;i++)
	{
	  DeleteTransSeq(me->ts[i]);
	  free(me->ts[i]);
	}
      free(me->ts);
      free(me->vID);
    }
  HTransformDelete(&(me->rhs));
}
