#include "trans_seq.h"

#include "geom.h"
#include "csmapping.h"
#include "basic_algebra.h"

#include <math.h>
#include <string.h>

/** \file trans_seq.c
    \brief Implementation of the functions operating on TTransSeq.

    Implementation of the functions operating on TTransSeq.

    \sa trans_seq.h, TTransSeq.
*/

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

void InitCtTrans(THTransform *ct,TTrans *t)
{
  t->t=CT_TRANS;
  t->s=1;
  t->v=NO_UINT;
  t->u=NO_UINT;
  t->val=0.0;
  NEW(t->ct,1,THTransform);
  HTransformCopy(t->ct,ct);
  t->vect=NULL;
  t->p=NULL;
}

void InitVarTrans(unsigned int tp,int s,unsigned int v,TTrans *t)
{
  if ((tp==CT_TRANS)||(IS_PATCH_TRANS(tp))||(tp==TV))
    Error("InitVarTrans should not be used for CT_TRANS, TV, or PA transforms");
  t->t=tp;
  t->s=s;
  t->v=v;
  t->u=NO_UINT;
  t->val=0.0;
  t->ct=NULL;
  t->vect=NULL;
  t->p=NULL;
}

void InitTVTrans(int s,unsigned int v,double *vect,TTrans *t)
{
  t->t=TV;
  t->s=s;
  t->v=v;
  t->u=NO_UINT;
  t->val=0.0;
  t->ct=NULL;
  NEW(t->vect,3,double);
  memcpy(t->vect,vect,3*sizeof(double));
  t->p=NULL;
}

void InitPatchTrans(unsigned int tp,int s,unsigned int u,unsigned int v,
		    double **p,TTrans *t)
{
  unsigned int i;

  if (!IS_PATCH_TRANS(tp))
    Error("Using InitPatchTrans to define a non-PA transform");

  if (u==v)
    Error("Repeated parameter in InitPatchTrans");
  
  t->t=tp;
  t->s=s;
  t->v=v;
  t->u=u;
  t->val=0.0;
  t->ct=NULL;
  t->vect=NULL;
  NEW(t->p,7,double*);
  for(i=0;i<7;i++)
    { NEW(t->p[i],3,double); }
  if (tp==PA)
    {
      memcpy(t->p[0],p[0],3*sizeof(double)); /* (p_0)  t->p_0=p_0 */
      DifferenceVector(3,p[2],p[0],t->p[1]); /* (p_02) t->p_1=p_2-p_0 */
      DifferenceVector(3,p[1],p[0],t->p[2]); /* (p_01) t->p_2=p_1-p_0 */
      DifferenceVector(3,p[0],p[1],t->p[3]); /* (d)    t->p_3=p_0-p_1-p_2+p_3 */
      DifferenceVector(3,t->p[3],p[2],t->p[3]);
      AccumulateVector(3,p[3],t->p[3]); /* t->p[3]+=p[3] */
    }
  else
    {
      /* For derived patches, we already have the four points computed */
      for(i=0;i<4;i++)
	memcpy(t->p[i],p[i],3*sizeof(double));
    }

  CrossProduct(t->p[1],t->p[2],t->p[4]); /* (n0) t_p_4=p_0_2 x p_0_1 */
  CrossProduct(t->p[1],t->p[3],t->p[5]); /* (n1) t_p_5=p_0_2 x d */
  CrossProduct(t->p[3],t->p[2],t->p[6]); /* (n2) t_p_6=d x p_0_1 */
}

void CopyTrans(TTrans *t_dst,TTrans *t_src)
{
  unsigned int i;

  t_dst->t=t_src->t;
  t_dst->s=t_src->s;
  t_dst->v=t_src->v;
  t_dst->u=t_src->u;
  t_dst->val=t_src->val;
  if (t_src->ct!=NULL)
    {
      NEW(t_dst->ct,1,THTransform);
      HTransformCopy(t_dst->ct,t_src->ct);
    }
  else
    t_dst->ct=NULL;

  if (t_src->vect!=NULL)
    {
      NEW(t_dst->vect,3,double);
      memcpy(t_dst->vect,t_src->vect,3*sizeof(double));
    }
  else
    t_dst->vect=NULL;

  if (t_src->p!=NULL)
    {
       NEW(t_dst->p,7,double*);
       for(i=0;i<7;i++)
	 {
	   NEW(t_dst->p[i],3,double);
	   memcpy(t_dst->p[i],t_src->p[i],3*sizeof(double));
	 }
    }
  else
    t_dst->p=NULL;
}

void TransInvert(TTrans *ti,TTrans *t)
{
  CopyTrans(ti,t);
  if (ti->t==CT_TRANS)
    HTransformInverse(ti->ct,ti->ct);
  else
    ti->s=-ti->s;
}

boolean TransHasVar(unsigned int v,TTrans *t)
{
  return((v==t->v)||(v==t->u));
}

void EvaluateVectorsPATrans(double u,double v,double *x,double *y,double *h,
			    TTrans *t)
{
 if (!IS_PATCH_TRANS(t->t))
    Error("Using EvaluatePATrans to evaluate a non-PA transform");

  /* x=n0+u*n1+v*n2 */
  SumVectorScale(3,t->p[4],u,t->p[5],x);
  SumVectorScale(3,x,v,t->p[6],x);

  /* y=p_02+v*d */
  SumVectorScale(3,t->p[1],v,t->p[3],y);
		
  /* t=p_0+u*p_02+v*p_01+u*v*d */
  SumVectorScale(3,t->p[0],u,t->p[1],h);
  SumVectorScale(3,h,v,t->p[2],h);
  SumVectorScale(3,h,u*v,t->p[3],h);
}

void EvaluateTrans(double v1,double v2,THTransform *a,TTrans *t)
{
  switch (t->t)
    {
    case CT_TRANS:
      HTransformCopy(a,t->ct);
      break;
    case TX:
      HTransformTx(t->s*v1,a);
      break;
    case TY:
      HTransformTy(t->s*v1,a);
      break;
    case TZ:
      HTransformTz(t->s*v1,a);
      break;
    case TV:
      HTransformTxyz(t->s*t->vect[0]*v1,t->s*t->vect[1]*v1,t->s*t->vect[2]*v1,a);
      break;	   
    case RX:
      HTransformRx(t->s*v1,a);
      break;
    case RY:
      HTransformRy(t->s*v1,a);
      break;
    case RZ:
      HTransformRz(t->s*v1,a);
      break;
    case PA:
      EvaluatePATrans(v1,v2,a,t);
      break;
    case dRX:
      /* With negative sign we have to evaluate the derivative of the
	 inverse. However, for rotations this derivative can be
	 computed directly. */
      HTransformRx2(t->s*cos(v1),-sin(v1),a);
      HTransformSetElement(AXIS_X,AXIS_X,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case dRY:
      HTransformRy2(t->s*cos(v1),-sin(v1),a);
      HTransformSetElement(AXIS_Y,AXIS_Y,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case dRZ:
      HTransformRz2(t->s*cos(v1),-sin(v1),a);
      HTransformSetElement(AXIS_Z,AXIS_Z,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case dPA_U:
      {
	double nv[3],dnv[3],nx,ny;
	double x[3],y[3],tr[3];
	double dx[3],dy[3]={0,0,0},dz[3];

	/* Get the non-normalized x,y,t vectors (t is only used if t->s<0) */
	EvaluateVectorsPATrans(v1,v2,x,y,tr,t);

	/* dx = diff(x_normalized,u) */
	/*   x_norm x = norm(x)
	     For a generic vector'v' depending on a parameter 'u',
	     and with n_v=norm(v) (i.e., n_v is also function of 'u')
	     diff(v/n_v,u)=(1/n_v^2)*[diff(v,u)*n_v-v*diff(n_v,u)]
	     where
	     diff(n_v,u)=1/n_v*diff(v\tr*v,u)
	     =1/n_v*v\tr*diff(v,u)
	     and, thus
	     diff(v/n_v,u) = (1/n_v^2)*[diff(v,u)*n_v
	     -v*1/n_v*v\tr*diff(v,u)]
	     = diff(v,u)/n_v
	     -(v/n_v)*(v\tr/n_v)*(diff(v,u)/n_v)

	     Thus, if v_norm=v/nv and dv_norm=diff(v,u)/norm(v)
	     then     diff(v/n_v,u)=dv_norm-(v_norm\tr*dv_norm)*v_norm

	     This is used every time we have to evaluate the 
	     differential of a normalized vector w.r.t. a given variable 
	     where we have the formula giving the  unormalized vector.
	*/
	nx=Norm(3,x);
	ScaleVector2(1/nx,3,x,nv);
	/* t->p[5] = n1 = diff(x,u) */
	ScaleVector2(1/nx,3,t->p[5],dnv);  
	SumVectorScale(3,dnv,-DotProduct(nv,dnv),nv,dx);
		 
	/* dy = diff(y_norm,u) is zero */

	/* dz = diff(z_norm,u) with z_norm = x_norm X y_norm */
	ny=Norm(3,y);
	CrossProduct(dx,y,dz);
	ScaleVector2(1/ny,3,dz,dz);

	/* dt = diff(p,u) = p_02+v*d = y */

	/* Set up the matrix */
	if (t->s>0)
	  {
	    HTransformFromVectors(dx,dy,dz,y,a);
	    HTransformSetElement(AXIS_H,AXIS_H,0,a);
	  }
	else
	  {
	    /* trans=T*R -> trans\inv=R\tr*(-T)=[R\tr -R\tr*t]
	       diff(trans\inv)=[diff(R\tr) -[diff(R\tr)*t+R\tr*diff(t)]]
	    */
	    THTransform Rt,dR;
	    double h[3],z[3],y1[3];
	    double zero[3]={0,0,0};

	    /* R\tr */
	    ScaleVector2(1/nx,3,x,x);
	    ScaleVector2(1/ny,3,y,y1);
	    CrossProduct(x,y1,z);
	    HTransformFromVectors(x,y1,z,zero,&Rt);
	    HTransformTranspose(&Rt,&Rt);
		     
	    /* a=diff(R\tr) = diff(R)\tr*/
	    HTransformFromVectors(dx,dy,dz,zero,&dR);
	    HTransformSetElement(AXIS_H,AXIS_H,0,&dR);
	    HTransformTranspose(&dR,a);

	    /* Now set the homogeneous part of 'a' */
	    HTransformApplyRot(tr,h,a);  /* h=diff(R\tr)*t */
	    HTransformApplyRot(y,z,&Rt); /* z=R\tr*diff(t) */
	    AccumulateVector(3,z,h);     /* h=h+z */

	    HTransformSetElement(AXIS_X,AXIS_H,-h[0],a);
	    HTransformSetElement(AXIS_Y,AXIS_H,-h[1],a);
	    HTransformSetElement(AXIS_Z,AXIS_H,-h[2],a);
	  }
      } 
      break;
    case dPA_V:
      {
	double nv[3],dnv[3],nx,ny;
	double x[3],y[3],tr[3];
	double dx[3],dy[3],dz[3],dt[3];

	/* Get the non-normalized x,y,t vectors (t is only used if t->s<0) */
	EvaluateVectorsPATrans(v1,v2,x,y,tr,t);

	/* dx = diff(x_normalized,v) */
	nx=Norm(3,x);
	ScaleVector2(1/nx,3,x,nv);
	/* t->p[6] = n2 = diff(x,v) */
	ScaleVector2(1/nx,3,t->p[6],dnv);  
	SumVectorScale(3,dnv,-DotProduct(nv,dnv),nv,dx);
		 
	/* dy = diff(y_normalized,v) */
	ny=Norm(3,y);
	ScaleVector2(1/ny,3,y,nv);
	/* t->p[3] = d = diff(y,v) */
	ScaleVector2(1/ny,3,t->p[3],dnv); 
	SumVectorScale(3,dnv,-DotProduct(nv,dnv),nv,dy);

	/* dz = diff(z_norm,u) with z_norm = x_norm X y_norm */
	/* diff(z_norm,v) = diff(x_norm,v) X y/norm(y) 
	   + x/norm(x) X diff(y_norm,v) */
	CrossProduct(dx,y,dz);
	ScaleVector2(1/ny,3,dz,dz);
	CrossProduct(x,dy,nv);
	SumVectorScale(3,dz,1/nx,nv,dz);

	/* dt = diff(t,v) = p_01+u*d */
	SumVectorScale(3,t->p[2],v1,t->p[3],dt);

	if (t->s>0)
	  {
	    /* Set up the matrix */
	    HTransformFromVectors(dx,dy,dz,dt,a);
	    HTransformSetElement(AXIS_H,AXIS_H,0,a);
	  }
	else
	  {
	    /* trans=T*R -> trans\inv=R\tr*(-T)=[R\tr -R\tr*t]
	       diff(trans\inv)=[diff(R\tr) -[diff(R\tr)*t+R\tr*diff(t)]]
	    */
	    THTransform Rt,dR;
	    double h[3],z[3];
	    double zero[3]={0,0,0};

	    /* R\tr */
	    ScaleVector2(1/nx,3,x,x);
	    ScaleVector2(1/ny,3,y,y);
	    CrossProduct(x,y,z);
	    HTransformFromVectors(x,y,z,zero,&Rt);
	    HTransformTranspose(&Rt,&Rt);
		     
	    /* a=diff(R\tr) = diff(R)\tr*/
	    HTransformFromVectors(dx,dy,dz,zero,&dR);
	    HTransformSetElement(AXIS_H,AXIS_H,0,&dR);
	    HTransformTranspose(&dR,a);

	    /* Now set the homogeneous part of 'a' */
	    HTransformApplyRot(tr,h,a);   /* h=diff(R\tr)*t */
	    HTransformApplyRot(dt,z,&Rt); /* z=R\tr*diff(t) */
	    AccumulateVector(3,z,h);      /* h=h+z */

	    HTransformSetElement(AXIS_X,AXIS_H,-h[0],a);
	    HTransformSetElement(AXIS_Y,AXIS_H,-h[1],a);
	    HTransformSetElement(AXIS_Z,AXIS_H,-h[2],a);
	  }
      }
      break;
    case ddRX:
      /* With negative sign we have to evaluate the second derivative of the
	 inverse. However, for rotations this derivative can be
	 computed directly. */
      HTransformRx2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_X,AXIS_X,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case ddRY:
      HTransformRy2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_Y,AXIS_Y,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case ddRZ:
      HTransformRz2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_Z,AXIS_Z,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case ddPA_UU:
    case ddPA_UV:
    case ddPA_VV:
      Error("The evaluation of the second derivative of parametrized-patch transforms is not implemented yet");
      break;
    default:
      Error("Unknown transform type in EvaluateTrans");
    }
}

void EvaluateDTrans(double v1,double v2,THTransform *a,TTrans *t)
{  
  HTransformZero(a);

  switch (t->t)
    {
    case CT_TRANS:
      Error("Deriving a constant transform?");
      break;
    case TX: /* --> constant */
      HTransformSetElement(AXIS_X,AXIS_H,(double)t->s,a);
      break;
    case TY: /* --> constant */
      HTransformSetElement(AXIS_Y,AXIS_H,(double)t->s,a);
      break;
    case TZ: /* --> constant */
      HTransformSetElement(AXIS_Z,AXIS_H,(double)t->s,a);
      break;
    case TV: /* --> constant */
      HTransformSetElement(AXIS_X,AXIS_H,(double)t->s*t->vect[0],a);
      HTransformSetElement(AXIS_Y,AXIS_H,(double)t->s*t->vect[1],a);
      HTransformSetElement(AXIS_Z,AXIS_H,(double)t->s*t->vect[2],a);
      break;
    case RX: /* --> dRX */
      HTransformRx2(t->s*cos(v1),-sin(v1),a);
      HTransformSetElement(AXIS_X,AXIS_X,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case RY: /* --> dRY */
      HTransformRy2(t->s*cos(v1),-sin(v1),a);
      HTransformSetElement(AXIS_Y,AXIS_Y,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case RZ: /* --> dRZ */
      HTransformRz2(t->s*cos(v1),-sin(v1),a);
      HTransformSetElement(AXIS_Z,AXIS_Z,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case PA:
      Error("Not implemented yet");
      break;
    case dRX: /* --> ddRX */
      HTransformRx2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_X,AXIS_X,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case dRY: /* --> ddRY */
      HTransformRy2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_Y,AXIS_Y,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case dRZ: /* --> ddRZ */
      HTransformRz2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_Z,AXIS_Z,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case dPA_U:	
      Error("Not implemented yet");
      break;
    case dPA_V:	
      Error("Not implemented yet");
      break;
    default:
      Error("Unknown transform type in EvaluateDTrans");
    }
}

void EvaluateDDTrans(double v1,double v2,THTransform *a,TTrans *t)
{  
  HTransformZero(a);

  switch (t->t)
    {
    case CT_TRANS:
      Error("Double deriving a constant transform?");
      break; 
    case TX: /* --> zero */
    case TY: /* --> zero */
    case TZ: /* --> zero */
    case TV: /* --> zero */
      break;
    case RX: /* --> ddRX */
      HTransformRx2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_X,AXIS_X,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case RY: /* --> ddRY */
      HTransformRy2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_Y,AXIS_Y,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case RZ: /* --> ddRZ */
      HTransformRz2(-t->s*sin(v1),-cos(v1),a);
      HTransformSetElement(AXIS_Z,AXIS_Z,0,a);
      HTransformSetElement(AXIS_H,AXIS_H,0,a);
      break;
    case PA:
      Error("Not implemented yet");
      break;
    case dRX: /* --> dddRX ? */
      Error("Not implemented yet");
      break;
    case dRY: /* --> dddRY ? */
      Error("Not implemented yet");
      break;
    case dRZ: /* --> dddRZ ? */
      Error("Not implemented yet");
      break;
    case dPA_U:	
      Error("Not implemented yet");
      break;
    case dPA_V:	
      Error("Not implemented yet");
      break;
    default:
      Error("Unknown transform type in EvaluateDDTrans");
    }
}

void EvaluatePATrans(double u,double v,THTransform *a,TTrans *t)
{
  double x[3],y[3],z[3],h[3];

  EvaluateVectorsPATrans(u,v,x,y,h,t);
  Normalize(3,x);
  Normalize(3,y);		 
  /* z=x X y  */
  CrossProduct(x,y,z);

  HTransformFromVectors(x,y,z,h,a);
  if (t->s<0)
    HTransformInverse(a,a);
}

void DeleteTrans(TTrans *t)
{
  if (t->ct!=NULL)
    {
      HTransformDelete(t->ct);
      free(t->ct);
      t->ct=NULL;
    }
  if (t->vect!=NULL)
    {
      free(t->vect);
      t->vect=NULL;
    }
  if (t->p!=NULL)
    {
      unsigned int i;
      
      for(i=0;i<7;i++)
	free(t->p[i]);
      free(t->p);
      t->p=NULL;
    }
}


/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

void InitTransSeq(TTransSeq *ts)
{
  ts->m=INIT_NUM_TERMS_TS;
  ts->n=0;
  NEW(ts->t,ts->m,TTrans*);

}

void CopyTransSeq(TTransSeq *ts_dst,TTransSeq *ts_src)
{
  unsigned int i;

  ts_dst->m=ts_src->m;
  ts_dst->n=ts_src->n;
  
  NEW(ts_dst->t,ts_dst->m,TTrans *);
  for(i=0;i<ts_dst->n;i++)
    {
      NEW(ts_dst->t[i],1,TTrans);
      CopyTrans(ts_dst->t[i],ts_src->t[i]);
    }
}

void ResetTransSeq(TTransSeq *ts)
{ 
  unsigned int i;

  for(i=0;i<ts->n;i++)
    {
      DeleteTrans(ts->t[i]);
      free(ts->t[i]);
    }
  ts->n=0;
}

boolean IsEmptyTransSeq(TTransSeq *ts)
{
  return(ts->n==0);
}

unsigned int TransSeqMaxVars(TTransSeq *ts)
{
  unsigned int i,m,n;

  m=0;
  for(i=0;i<ts->n;i++)
    {
      n=(ts->t[i]->t==CT_TRANS?0:(ts->t[i]->u==NO_UINT?1:2));
      if (n>m) m=n;
    }
  
  return(m);
}

boolean HasRepeatedVar(TTransSeq *ts)
{
  unsigned int i,j;
  boolean found;

  found=FALSE;
  i=0;
  while((i<ts->n)&&(!found))
    {
      if (ts->t[i]->t!=CT_TRANS)
	{
	  j=i+1;
	  while((j<ts->n)&&(!found))
	    {
	      found=TransHasVar(ts->t[i]->v,ts->t[j]);
	      j++;
	    }
	  
	  if ((!found)&&(ts->t[i]->u!=NO_UINT))
	    {
	      j=i+1;
	      while((j<ts->n)&&(!found))
		{
		  found=TransHasVar(ts->t[i]->u,ts->t[j]);
		  j++;
		}
	    }
	}
      i++;
    }
  
  return(found);
}

boolean HasCtRotTransSeq(TTransSeq *ts)
{
  unsigned int i;
  boolean found;

  found=FALSE;
  for(i=0;((!found)&&(i<ts->n));i++)
    found=((ts->t[i]->t==CT_TRANS)&&(!HTransformIsTranslation(ts->t[i]->ct)));

  return(found);
}

unsigned int TransSeqSize(TTransSeq *ts)
{
  return(ts->n);
}

TTrans *GetElementFromTransSeq(unsigned int i,TTransSeq *ts)
{
  if (i>=ts->n)
    Error("Index out of range in GetVarElementFromTransSeq");

  return(ts->t[i]);
}

void AddTrans2TransSeq(TTrans *t,TTransSeq *ts)
{
  /* For CT_TRANS we try to compact, if possible */
  if (t->t==CT_TRANS)
    {
      if (t->s>0)
	AddCtTrans2TransSeq(t->ct,ts);
      else
	{
	  THTransform ict;

	  HTransformInverse(t->ct,&ict);
	  AddCtTrans2TransSeq(&ict,ts);
	  HTransformDelete(&ict);
	}
    }
  else
    {
      /* For variable transforms compact only if the previous trasform is
         the identity (this happens for just initialized transform sequences) */
      if ((ts->n>0)&&(ts->t[ts->n-1]->t==CT_TRANS)&&(HTransformIsIdentity(ts->t[ts->n-1]->ct)))
	{
	  DeleteTrans(ts->t[ts->n-1]);
	  CopyTrans(ts->t[ts->n-1],t);
	}
      else
	{
	  if (ts->n==ts->m)
	    {
	      MEM_DUP(ts->t,ts->m,TTrans *);
	    }
	  NEW(ts->t[ts->n],1,TTrans);
	  CopyTrans(ts->t[ts->n],t);
	  
	  ts->n++;
	}
    }
}

void AddCtTrans2TransSeq(THTransform *t,TTransSeq *ts)
{
  if (!HTransformIsIdentity(t))
    {
      if ((ts->n>0)&&(ts->t[ts->n-1]->t==CT_TRANS))
	{
	  HTransformProduct(ts->t[ts->n-1]->ct,t,ts->t[ts->n-1]->ct);
	  /* Identity matrix is removed (except the base one) */
	  if ((HTransformIsIdentity(ts->t[ts->n-1]->ct))&&(ts->n>1))
	    {
	      ts->n--;
	      DeleteTrans(ts->t[ts->n]);
	      free(ts->t[ts->n]);
	    }
	}
      else
	{
	  if (ts->n==ts->m)
	    {
	      MEM_DUP(ts->t,ts->m,TTrans *);
	    }
	  NEW(ts->t[ts->n],1,TTrans);
	  InitCtTrans(t,ts->t[ts->n]);

	  ts->n++;
	}
    }
}

void AddVarTrans2TransSeq(unsigned int t,int s,unsigned int v,TTransSeq *ts)
{
  if (t==CT_TRANS)
    Error("Adding a constant varaible transform in AddVarTrans2TransSeq");

  if (IS_PATCH_TRANS(t))
    Error("Do not use AddVarTrans2TransSeq to add a patch transform to a Trans Seq");

  if (t==TV)
    Error("Do not use AddVarTrans2TransSeq to add a displacement transform to a Trans Seq");

  if ((ts->n>0)&&(ts->t[ts->n-1]->t==CT_TRANS)&&(HTransformIsIdentity(ts->t[ts->n-1]->ct)))
    {
      InitVarTrans(t,s,v,ts->t[ts->n-1]);
    }
  else
    {
      if (ts->n==ts->m)
	{
	  MEM_DUP(ts->t,ts->m,TTrans *);
	}
      NEW(ts->t[ts->n],1,TTrans);
      InitVarTrans(t,s,v,ts->t[ts->n]);
      
      ts->n++;
    }
}

void AddDispTrans2TransSeq(int s,unsigned int v,double *vect,TTransSeq *ts)
{
  if ((ts->n>0)&&(ts->t[ts->n-1]->t==CT_TRANS)&&(HTransformIsIdentity(ts->t[ts->n-1]->ct)))
    {
      InitTVTrans(s,v,vect,ts->t[ts->n-1]);
    }
  else
    {
      if (ts->n==ts->m)
	{
	  MEM_DUP(ts->t,ts->m,TTrans *);
	}
      NEW(ts->t[ts->n],1,TTrans);
      InitTVTrans(s,v,vect,ts->t[ts->n]);
      
      ts->n++;
    }
}

void AddPatchTrans2TransSeq(unsigned int t,int s,unsigned int u,unsigned int v,
			    double **p,TTransSeq *ts)
{
  if ((ts->n>0)&&(ts->t[ts->n-1]->t==CT_TRANS)&&(HTransformIsIdentity(ts->t[ts->n-1]->ct)))
    {
      InitPatchTrans(t,s,u,v,p,ts->t[ts->n-1]);
    }
  else
    {
      if (ts->n==ts->m)
	{
	  MEM_DUP(ts->t,ts->m,TTrans *);
	}
      NEW(ts->t[ts->n],1,TTrans);
      InitPatchTrans(t,s,u,v,p,ts->t[ts->n]);
      
      ts->n++;
    }
}

boolean VarIncludedinTransSeq(unsigned int v,TTransSeq *ts)
{
  boolean found;
  unsigned int i;

  found=FALSE;
  i=0;
  while ((!found)&&(i<ts->n))
    {
      found=TransHasVar(v,ts->t[i]);
      i++;
    }
  return(found);
}

void UpdateUsedDOF(unsigned int *dof,TTransSeq *ts)
{
  unsigned int i;

  for(i=0;i<ts->n;i++)
    {
      switch (ts->t[i]->t)
	{
	case CT_TRANS:
	  break;
	case TX:
	  dof[TX]++;
	  break;
	case TY:
	  dof[TY]++;
	  break;
	case TZ:
	  dof[TZ]++;
	  break;
	case TV:
	  /* assuming a general displacement. */
	  dof[TX]++;
	  dof[TY]++;
	  dof[TZ]++;
	  break;
	case PA:
	case dPA_U:
	case dPA_V:
	case ddPA_UU:
	case ddPA_UV:
	case ddPA_VV:
	  /* Assuming a general patch */
	  dof[TX]++;
	  dof[TY]++;
	  dof[TZ]++;
	  dof[RX]++;
	  dof[RY]++;
	  dof[RZ]++;
	  break;
	case RX:
	case dRX:
	case ddRX:
	  dof[RX]++;
	  break;
	case RY:
	case dRY:
	case ddRY:
	  dof[RY]++;
	  break;
	case RZ:
	case dRZ:
	case ddRZ:
	  dof[RZ]++;
	  break;
	default:
	  Error("Unkown transform type in UpdateUsedDOF");
	}
    }
}
 
void ShiftVariablesInTransSeq(unsigned int nv,TTransSeq *ts)
{
  unsigned int i;

   for(i=0;i<ts->n;i++)
    {
      if (TransHasVar(nv,ts->t[i]))
	Error("Removing a variable used in a transform sequence");
      else
	{
	  if ((ts->t[i]->v!=NO_UINT)&&(ts->t[i]->v>nv))
	    {
	      ts->t[i]->v--;
	    }
	  if ((ts->t[i]->u!=NO_UINT)&&(ts->t[i]->u>nv))
	    {
	      ts->t[i]->u--;
	    }
	}
    }
}

boolean FixVarInTransSeq(unsigned int nv,double v,THTransform *ctt,TTransSeq *ts)
{
  unsigned int i,nOrig;
  TTrans **tOrig;
  THTransform a;
  boolean ct;

  /* Get a copy of the previous array of transfomrs */
  tOrig=ts->t;
  nOrig=ts->n;

  /* And start a new array of transforms */
  NEW(ts->t,ts->m,TTrans*);
  ts->n=0;
  for(i=0;i<nOrig;i++)
    {
      if ((tOrig[i]->u!=nv)&&(tOrig[i]->v!=nv))
	{
	  /* 'nv' not used in this transform: just add it to the new array */
	  if ((ts->n==1)&&(ts->t[0]->t==CT_TRANS)&&(HTransformIsIdentity(ts->t[0]->ct)))
	    {
	      DeleteTrans(ts->t[0]);
	      free(ts->t[0]);
	      
	      ts->t[0]=tOrig[i];
	    }
	  else
	    {
	      ts->t[ts->n]=tOrig[i];	      
	      ts->n++;
	    }
	}
      else
	{
	  if ((tOrig[i]->t==PA)||(tOrig[i]->t==dPA_U)||(tOrig[i]->t==dPA_V)||
	      (tOrig[i]->t==ddPA_UU)||(tOrig[i]->t==ddPA_UV)||(tOrig[i]->t==ddPA_VV))
	    {
	      /* Transforms that use two variables */
	      if ((tOrig[i]->u==nv)&&(tOrig[i]->v==NO_UINT))
		{
		  /* Fixing 'u' when 'v' is already fixed */
		  EvaluateTrans(v,tOrig[i]->val,&a,tOrig[i]);
		  AddCtTrans2TransSeq(&a,ts); /* This takes care of compacting 
						 ct transforms if necessary */
		  HTransformDelete(&a);
		  
		  DeleteTrans(tOrig[i]);
		  free(tOrig[i]);
		}
	      else
		{
		  if ((tOrig[i]->v==nv)&&(tOrig[i]->u==NO_UINT))
		    {
		      /* Fixing 'v' when 'u' is already fixed */
		      EvaluateTrans(tOrig[i]->val,v,&a,tOrig[i]);
		      AddCtTrans2TransSeq(&a,ts); /* This takes care of compacting 
						     ct transforms if necessary */
		      HTransformDelete(&a);
		      
		      DeleteTrans(tOrig[i]);
		      free(tOrig[i]);
		    }
		  else
		    {
		      /* only 'u' of 'v' become ct. Just modify the transform and
		         add it to the new array */
		      if (tOrig[i]->u==nv)
			tOrig[i]->u=NO_UINT; /* Fixing u */
		      else
			tOrig[i]->v=NO_UINT; /* Fixing v */
		      tOrig[i]->val=v;
		      
		      ts->t[ts->n]=tOrig[i];
		      ts->n++;
		    }
		}
	    }
	  else
	    {
	      /* Transform that use one variable: become constant */
	      EvaluateTrans(v,0.0,&a,tOrig[i]);
	      AddCtTrans2TransSeq(&a,ts); /* This takes care of compacting 
					     ct transforms if necessary */
	      HTransformDelete(&a);
	      
	      DeleteTrans(tOrig[i]);
	      free(tOrig[i]);
	    }
	}
    }

  /* Forget about the previous array of transforms. Individual, non-used
     elements are already deleted. */
  free(tOrig);

  /* Remove the deleted variable. */
  ShiftVariablesInTransSeq(nv,ts);

  if ((ts->n>1)||((ts->n==1)&&(ts->t[0]->t!=CT_TRANS)))
    ct=FALSE; /* non-constant sequence that holds */
  else
    {
      /* zero or one ct transform */
      ct=TRUE;
      if (ts->n==0)
	HTransformIdentity(ctt);
      else
	HTransformCopy(ctt,ts->t[0]->ct);
    }
  return(ct);
}

void ReplaceVarInTransSeq(unsigned int nv,unsigned int nvNew,TTransSeq *ts)
{
  unsigned int i;

  for(i=0;i<ts->n;i++)
    {
      if (ts->t[i]->v==nv)
	ts->t[i]->v=nvNew;  
      if (ts->t[i]->u==nv)
	ts->t[i]->u=nvNew;
    }
   
  ShiftVariablesInTransSeq(nv,ts); 
}

void RewriteTransSeq2Orig(Tmapping *map,TTransSeq *ts)
{
  unsigned int i,si,so;

  for(i=0;i<ts->n;i++)
    {
      si=ts->t[i]->v;
      if (si!=NO_UINT)
	{
	  so=GetVarIDInOriginal(si,map);
	  if (so==NO_UINT)
	    Error("Matrix equation variable (v) disappeared in simplification");
	  ts->t[i]->v=so;
	}
      si=ts->t[i]->u;
      if (si!=NO_UINT)
	{
	  so=GetVarIDInOriginal(si,map);
	  if (so==NO_UINT)
	    Error("Matrix equation variable (u) disappeared in simplification");
	  ts->t[i]->u=so;
	}
    }
}

void SimplifyTransSeq(TTransSeq *ts)
{
  #if (SIMPLIFY_TS)
    if ((ts->n>2)&&(ts->t[0]->t==CT_TRANS)&&(ts->t[ts->n-1]->t==CT_TRANS))
      {
        ts->n--;
      
	HTransformProduct(ts->t[ts->n]->ct,ts->t[0]->ct,ts->t[0]->ct);
      
	DeleteTrans(ts->t[ts->n]);
	free(ts->t[ts->n]);
      
	if (HTransformIsIdentity(ts->t[0]->ct))
	  {
	    unsigned int i;
	  
	    DeleteTrans(ts->t[0]);
	    free(ts->t[0]);
	  
	    for(i=1;i<ts->n;i++)
	      ts->t[i-1]=ts->t[i];
	    
	    ts->n--;
	  }
      }
  #endif
}

unsigned int TNumericDTransSeq(unsigned int neqs,unsigned int nvars,
			       unsigned int nse,unsigned int *r,unsigned int *c,
			       unsigned int ce,unsigned int cie,
			       boolean *independentEq,
			       double *x,double *m,TTransSeq *ts)
{
  signed int l;
  unsigned int i,k,ki,vi;
  THTransform *tr,p1,*p2,d;
  double val;

  #if (_DEBUG>1)
    if (ts->n==0)
      Error("Using TNumericDTransSeq on an empty transform sequence");
  #endif
    
  NEW(tr,ts->n,THTransform); /* Evaluation of each transform in the sequence */
  NEW(p2,ts->n,THTransform);

  HTransformIdentity(&p1);
  HTransformIdentity(&(p2[ts->n-1]));

  for(l=ts->n-1;l>=0;l--)
    {
      if (ts->t[l]->t!=CT_TRANS)
	{
	  vi=ts->t[l]->v; /* variable in the transform. */
	  val=(vi==NO_UINT?0.0:x[vi]);
	  EvaluateTrans(val,0.0,&(tr[l]),ts->t[l]);
	}

      if (l<(signed int)(ts->n-1))
	{
	  if (ts->t[l+1]->t!=CT_TRANS)
	    HTransformProduct(&(tr[l+1]),&(p2[l+1]),&(p2[l])); /* Product of the sequence of transforms */
	  else
	    HTransformProduct(ts->t[l+1]->ct,&(p2[l+1]),&(p2[l]));
	}
    }

  for(i=0;i<ts->n;i++)
    {
      /* derivative with respect tr[i] (with respect to the variable in this transform, if any) */
      
      if (ts->t[i]->t!=CT_TRANS) /* transfrom without variable -> zero derivative */
	{
	  vi=ts->t[i]->v; /* variable in the transform. We derive with respect to it */
	  val=(vi==NO_UINT?0.0:x[vi]);

	  /* Double derivative of the current transform */
	  EvaluateDTrans(val,0.0,&d,ts->t[i]); /* double derivative w.r.t. vi */
	   
	  HTransformProduct(&p1,&d,&d);
	  HTransformProduct(&d,&(p2[i]),&d);
	  /* Assign the result */
	  ki=0;
	  for(k=0;k<nse;k++)
	    {
	      if ((independentEq==NULL)||(independentEq[ce+k]))
		{
		  m[RC2INDEX(vi,cie+ki,nvars,neqs)]=HTransformGetElement(r[k],c[k],&d);
		  ki++;
		}
	    }

	  /* Concat the current transform to p1 */
	  HTransformProduct(&p1,&(tr[i]),&p1);
	}
      else
	HTransformProduct(&p1,ts->t[i]->ct,&p1); /* Concat the current transform to p1 */
    }
  
  free(tr);
  free(p2);
  
  if (independentEq==NULL)
    ki+=nse;
  else
    {
      ki=0;
      for(k=0;k<nse;k++)
	{
	  if (independentEq[ce+k])
	    ki++;
	}
    }
  
  return(ki);
}

unsigned int NumericDDTransSeq(unsigned int neqs,unsigned int nvars,
			       unsigned int nse,unsigned int *r,unsigned int *c,
			       unsigned int ce,unsigned int cie,
			       boolean *independentEq,
			       double *x,double **h,TTransSeq *ts)
{
  signed int l;
  unsigned int i,j,k,ki,vi,vj;
  THTransform *tr,*dtr,p1,*p2,p1b,d;
  double val;
  
  #if (_DEBUG>1)
    if (ts->n==0)
      Error("Using NumericDDTransSeqNew on an empty transform sequence");
  #endif
    
  NEW(tr,ts->n,THTransform); /* Evaluation of each transform in the sequence */
  NEW(p2,ts->n,THTransform); /* Product of transforms from i+1 to the end */
  NEW(dtr,ts->n,THTransform);/* Derivative of each transform in the sequence */

  HTransformIdentity(&p1);
  HTransformIdentity(&(p2[ts->n-1]));
  
  for(l=ts->n-1;l>=0;l--)
    {
      if (ts->t[l]->t!=CT_TRANS)
	{
	  vi=ts->t[l]->v; /* variable in the transform. */
	  val=(vi==NO_UINT?0.0:x[vi]);
	  
	  EvaluateTrans(val,0.0,&(tr[l]),ts->t[l]);
	  EvaluateDTrans(val,0.0,&(dtr[l]),ts->t[l]);
	}

      if (l<(signed int)(ts->n-1))
	{
	  if (ts->t[l+1]->t!=CT_TRANS)
	    HTransformProduct(&(tr[l+1]),&(p2[l+1]),&(p2[l])); /* Product of the sequence of transforms */
	  else
	    HTransformProduct(ts->t[l+1]->ct,&(p2[l+1]),&(p2[l]));
	}
    }

  for(i=0;i<ts->n;i++)
    {
      /* derivative with respect tr[i] (with respect to the variable in this transform, if any) */

      if (ts->t[i]->t!=CT_TRANS) /* transfrom without variable -> zero derivative */
	{
	  vi=ts->t[i]->v; /* variable in the transform. We derive with respect to it */
	  val=(vi==NO_UINT?0.0:x[vi]);
	  
	  EvaluateDDTrans(val,0.0,&d,ts->t[i]); /* double derivative w.r.t. vi */
	   
	  HTransformProduct(&p1,&d,&d);
	  HTransformProduct(&d,&(p2[i]),&d);
	  
	  /* Assign the result */
	  ki=0;
	  for(k=0;k<nse;k++)
	    {
	      if ((independentEq==NULL)||(independentEq[ce+k]))
		{
		  h[vi][RC2INDEX(cie+ki,vi,neqs,nvars)]=HTransformGetElement(r[k],c[k],&d);
		  ki++;
		}
	    }
	  
	  HTransformProduct(&p1,&(dtr[i]),&p1b); /* Single derivative w.r.t vi .... */

	  /* ... which will be accumulated with the derivative w.r.t. other variables
	     involved in the rest */
	  for(j=i+1;j<ts->n;j++)
	    {
	      if (ts->t[j]->t!=CT_TRANS)
		{
		  vj=ts->t[j]->v;
		  HTransformProduct(&p1b,&(dtr[j]),&d);
		  HTransformProduct(&d,&(p2[j]),&d);
		  
		  /* Assign the result */
		  ki=0;
		  for(k=0;k<nse;k++)
		    {
		      if ((independentEq==NULL)||(independentEq[ce+k]))
			{
			  h[vi][RC2INDEX(cie+ki,vj,neqs,nvars)]=HTransformGetElement(r[k],c[k],&d);
			  h[vj][RC2INDEX(cie+ki,vi,neqs,nvars)]=HTransformGetElement(r[k],c[k],&d);
			  ki++;
			}
		    }
		  
		  HTransformProduct(&p1b,&(tr[j]),&p1b);
		}
	      else
		HTransformProduct(&p1b,ts->t[j]->ct,&p1b);
	    }
	  
	  HTransformProduct(&p1,&(tr[i]),&p1);
	}
      else
	HTransformProduct(&p1,ts->t[i]->ct,&p1);
    }
  
  free(tr);
  free(p2);
  free(dtr);
  
  if (independentEq==NULL)
    ki+=nse;
  else
    {
      ki=0;
      for(k=0;k<nse;k++)
	{
	  if (independentEq[ce+k])
	    ki++;
	}
    }
  
  return(ki);
} 

void DeriveTransSeq(unsigned int v,unsigned int *n,TTransSeq ***tsd,TTransSeq *ts)
{
  unsigned int i;
  
  *n=0;
  for(i=0;i<ts->n;i++)
    {
      if (TransHasVar(v,ts->t[i]))
	(*n)++;
    }
  
  /* *n will be typically 0 or 1 but it can be larger if a variable is repeated
     in a loop equation.  */
  if (*n==0)
    tsd=NULL;
  else
    {
      THTransform a;
      unsigned int r,t;
      double sgn;

      NEW(*tsd,*n,TTransSeq*);
      for(r=0;r<*n;r++)
	{
	  /* We derive in turns for each time varible 'v' appears in the 
	     sequence. '*n' is the maximum times and 'r' is the time with
	     respect to which we are deriving now. 't' is the numbers
	     of times the variable has been encountered so far in the
	     scan over the sequence. */
	  t=0;
	  NEW((*tsd)[r],1,TTransSeq);
	  InitTransSeq((*tsd)[r]);
	  for(i=0;i<ts->n;i++)
	    {
	      if ((!TransHasVar(v,ts->t[i]))||(t!=r))
		AddTrans2TransSeq(ts->t[i],(*tsd)[r]);
	      else
		{
		  /* The r-th time variable 'v' appears in the sequence */
		  switch (ts->t[i]->t)
		    {
		    case TX:
		      HTransformZero(&a);
		      HTransformSetElement(AXIS_X,AXIS_H,(double)ts->t[i]->s,&a);
		      AddCtTrans2TransSeq(&a,(*tsd)[r]);
		      HTransformDelete(&a);
		      break;
		    case TY:
		      HTransformZero(&a);
		      HTransformSetElement(AXIS_Y,AXIS_H,(double)ts->t[i]->s,&a);
		      AddCtTrans2TransSeq(&a,(*tsd)[r]);
		      HTransformDelete(&a);
		      break;
		    case TZ:
		      HTransformZero(&a);
		      HTransformSetElement(AXIS_Z,AXIS_H,(double)ts->t[i]->s,&a);
		      AddCtTrans2TransSeq(&a,(*tsd)[r]);
		      HTransformDelete(&a);
		      break;
		    case TV:
		      sgn=(double)ts->t[i]->s;
		      HTransformZero(&a);
		      HTransformSetElement(AXIS_X,AXIS_H,sgn*ts->t[i]->vect[0],&a);
		      HTransformSetElement(AXIS_Y,AXIS_H,sgn*ts->t[i]->vect[1],&a);
		      HTransformSetElement(AXIS_Z,AXIS_H,sgn*ts->t[i]->vect[2],&a);
		      AddCtTrans2TransSeq(&a,(*tsd)[r]);
		      HTransformDelete(&a);
		      break;
		    case RX:
		      AddVarTrans2TransSeq(dRX,ts->t[i]->s,ts->t[i]->v,
					   (*tsd)[r]);
		      break;
		    case RY:
		      AddVarTrans2TransSeq(dRY,ts->t[i]->s,ts->t[i]->v,
					   (*tsd)[r]);
		      break;
		    case RZ:
		      AddVarTrans2TransSeq(dRZ,ts->t[i]->s,ts->t[i]->v,
					   (*tsd)[r]);
		      break;
		    case PA:
		      /* For parametrized transforms, we keep all the 
			 information changing the type of transform */
		      if (v==ts->t[i]->u) /* Derivative w.r.t. the 1st param */
			AddPatchTrans2TransSeq(dPA_U,ts->t[i]->s,ts->t[i]->u,
					       ts->t[i]->v,ts->t[i]->p,(*tsd)[r]);
		      else                /* Derivative w.r.t. the 2nd param */
			AddPatchTrans2TransSeq(dPA_V,ts->t[i]->s,ts->t[i]->u,
					       ts->t[i]->v,ts->t[i]->p,(*tsd)[r]);
		      break;
		    case dRX:
		      AddVarTrans2TransSeq(ddRX,ts->t[i]->s,
					   ts->t[i]->v,(*tsd)[r]);
		      break;
		    case dRY:
		      AddVarTrans2TransSeq(ddRY,ts->t[i]->s,
					   ts->t[i]->v,(*tsd)[r]);
		      break;
		    case dRZ:
		      AddVarTrans2TransSeq(ddRZ,ts->t[i]->s,
					   ts->t[i]->v,(*tsd)[r]);
		      break;
		    case dPA_U:	
		      if (v==ts->t[i]->u)  /* du du */
			AddPatchTrans2TransSeq(ddPA_UU,ts->t[i]->s,ts->t[i]->u,
					       ts->t[i]->v,ts->t[i]->p,(*tsd)[r]);
		      else                 /* du dv */
			AddPatchTrans2TransSeq(ddPA_UV,ts->t[i]->s,ts->t[i]->u,
					       ts->t[i]->v,ts->t[i]->p,(*tsd)[r]);
		      break;
		    case dPA_V:	
		      if (v==ts->t[i]->u)  /* dv du */
			AddPatchTrans2TransSeq(ddPA_UV,ts->t[i]->s,ts->t[i]->u,
					       ts->t[i]->v,ts->t[i]->p,(*tsd)[r]);
		      else                 /* dv dv */
			AddPatchTrans2TransSeq(ddPA_VV,ts->t[i]->s,ts->t[i]->u,
					       ts->t[i]->v,ts->t[i]->p,(*tsd)[r]);
		      break;
		    default:
		      Error("Unknown transform type in DeriveTransSeq");
		    }
		}
	      if (TransHasVar(v,ts->t[i]))
		t++;
	    }
	}
    }
}

void EvaluateTransSeq(double *v,THTransform *r,TTransSeq *ts)
{
  unsigned int i;
  THTransform a;
  double val;
  double d1,d2,d3;
	   
  HTransformIdentity(r);
  for(i=0;i<ts->n;i++)
    {
      /* For the more usual transform we accumulate instad than
	 generating a transform and using product. */
      switch (ts->t[i]->t)
	{
	case CT_TRANS:
	  HTransformProduct(r,ts->t[i]->ct,r);
	  break;
	case TX:
	  d1=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  HTransformAcumTrans(d1,0,0,r);
	  break;
	case TY:
	  d1=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  HTransformAcumTrans(0,d1,0,r);
	  break;
	case TZ:
	  d1=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  HTransformAcumTrans(0,0,d1,r);
	  break;
	case TV:
	  val=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  d1=ts->t[i]->vect[0];
	  d2=ts->t[i]->vect[1];
	  d3=ts->t[i]->vect[2];
	  HTransformAcumTrans(val*d1,val*d2,val*d3,r);
	  break;	   
	case RX:	   
	  val=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  HTransformAcumRot(RX,sin(val),cos(val),r);
	  break;
	case RY:
	  val=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  HTransformAcumRot(RY,sin(val),cos(val),r);
	  break;
	case RZ:
	  val=((double)(ts->t[i]->s))*v[ts->t[i]->v];
	  HTransformAcumRot(RZ,sin(val),cos(val),r);
	  break;
	case PA:
	case dPA_U:
	case dPA_V:
	case ddPA_UU:
	case ddPA_UV:
	case ddPA_VV:
	  d1=(ts->t[i]->u==NO_UINT?ts->t[i]->val:v[ts->t[i]->u]);
	  d2=(ts->t[i]->v==NO_UINT?ts->t[i]->val:v[ts->t[i]->v]);
	  EvaluateTrans(d1,d2,&a,ts->t[i]);
	  HTransformProduct(r,&a,r);
	  HTransformDelete(&a);
	  break;
	case dRX:
	case dRY:
	case dRZ:
	case ddRX:
	case ddRY:
	case ddRZ:
	  val=v[ts->t[i]->v];
	  EvaluateTrans(val,0.0,&a,ts->t[i]);
	  HTransformProduct(r,&a,r);
	  HTransformDelete(&a);
	  break;
	default:
	  Error("Unknown transform type in EvaluateTransSeq");
	}
    }
}

void PrintTransSeq(FILE *f,double *x,char **varNames,TTransSeq *ts)
{
  unsigned int i,j,k,t;
  double val;

  for(i=0;i<ts->n;i++)
    {
      t=ts->t[i]->t;
	  
      switch (t)
	{
	case CT_TRANS:
	  if (HTransformIsIdentity(ts->t[i]->ct))
	    fprintf(f,"Id");
	  else
	    {
	      /*HTransformPrettyPrint(f,ts->t[i]->ct); */
	      
	      if (x!=NULL)
		{
		  fprintf(f,"T=[");
		  HTransformPrint(f,ts->t[i]->ct);
		  fprintf(f,"];\n");
		}
	      else
		{
		  fprintf(f,"Tr(");
		  for(j=0;j<DIM_SP;j++)
		    {
		      for(k=0;k<(DIM_SP+1);k++)
			{
			  val=HTransformGetElement(j,k,ts->t[i]->ct);
			  PrintReal(f,val);
			  if (k<DIM_SP)
			    fprintf(f,",");
			}
		      if (j<DIM_SP-1)
			fprintf(f,";");
		    }
		  fprintf(f,")");
		}
	    }
	  break;
	      
	case TX:
	  fprintf(f,"Tx(");
	  break;
	case TY:
	  fprintf(f,"Ty(");
	  break;
	case TZ:
	  fprintf(f,"Tz(");
	  break;
	case TV:
	  fprintf(f,"Tv(");
	  PrintReal(f,ts->t[i]->vect[0]);fprintf(f,",");
	  PrintReal(f,ts->t[i]->vect[1]);fprintf(f,",");
	  PrintReal(f,ts->t[i]->vect[2]);fprintf(f,",");
	  break;
	case RX:
	  if (x!=NULL)
	    {
	      THTransform t;
	      
	      HTransformRx(x[ts->t[i]->v],&t);
	      fprintf(f,"R=[");
	      HTransformPrint(f,&t);
	      fprintf(f,"];\n");
	    }
	  else
	    fprintf(f,"Rx(");
	  break;
	case RY:
	  fprintf(f,"Ry(");
	  break;
	case RZ:
	  fprintf(f,"Rz(");
	  break;
	case PA:
	case dPA_U:
	case dPA_V:
	case ddPA_UU:
	case ddPA_UV:
	case ddPA_VV:
	  {
	    unsigned int k;
	    double v[3];

	    switch (t)
	      { 
	      case PA:
		fprintf(f,"Pa(");
		break;
	      case dPA_U:
		fprintf(f,"dPa_u(");
		break;
	      case dPA_V:
		fprintf(f,"dPa_v(");
		break;
	      case ddPA_UU:
		fprintf(f,"ddPa_uu(");
		break;
	      case ddPA_UV:
		fprintf(f,"ddPa_uv(");
		break;
	      case ddPA_VV:
		fprintf(f,"ddPa_vv(");
		break;
	      }	
	    /* Print the 4 vectors defining the patch */
	    if (t!=PA)
	      {
		/* For derived patches we print the already
		   processed patch extremes +
		   Derived patches typically do not appear in
		   equation files */
		for(j=0;j<4;j++)
		  {
		    for(k=0;k<3;k++)
		      {
			PrintReal(f,ts->t[i]->p[j][k]);
			if (k<2) fprintf(f,",");
		      }
		    fprintf(f,";");
		  }
	      }
	    else
	      {
		/* For oritinal patches we print the
		   orignal extremes. This facilitates the
		   unsderstanding of equation files. */
		/* p_0 */
		for(k=0;k<3;k++)
		  {
		    PrintReal(f,ts->t[i]->p[0][k]);
		    if (k<2) fprintf(f,",");
		  }
		fprintf(f,";");
		/* p_1=p_01+p_0 */
		SumVector(3,ts->t[i]->p[2],ts->t[i]->p[0],v);
		for(k=0;k<3;k++)
		  {
		    PrintReal(f,v[k]);
		    if (k<2) fprintf(f,",");
		  }
		fprintf(f,";");
		/* p_2=p_02+p_0 */
		SumVector(3,ts->t[i]->p[1],ts->t[i]->p[0],v);
		for(k=0;k<3;k++)
		  {
		    PrintReal(f,v[k]);
		    if (k<2) fprintf(f,",");
		  }
	      }
	    fprintf(f,";");
	    /* p_3=d+p_01+p_02+p_0 */
	    SumVector(3,ts->t[i]->p[3],ts->t[i]->p[2],v);
	    AccumulateVector(3,ts->t[i]->p[1],v);
	    AccumulateVector(3,ts->t[i]->p[0],v);
	    for(k=0;k<3;k++)
	      {
		PrintReal(f,v[k]);
		if (k<2) fprintf(f,",");
	      }
	    fprintf(f,";");

	    /* Now the variables */
	    if (ts->t[i]->u==NO_UINT)
	      PrintReal(f,ts->t[i]->val);
	    else
	      {
		if (varNames!=NULL)
		  { 
		    char *n;
			
		    n=varNames[ts->t[i]->u];
		    PRINT_VARIABLE_NAME(f,n);
		  }
		else
		  fprintf(f,"v_%u",ts->t[i]->u);
	      }
	    fprintf(f,",");
	  }
	  break;
	case dRX:
	  fprintf(f,"dRx(");
	  break;
	case dRY:
	  fprintf(f,"dRy(");
	  break;
	case dRZ:
	  fprintf(f,"dRz(");
	  break;
	case ddRX:
	  fprintf(f,"ddRx(");
	  break;
	case ddRY:
	  fprintf(f,"ddRy(");
	  break;
	case ddRZ:
	  fprintf(f,"ddRz(");
	  break;
	default:
	  Error("Unknown transform type in EvaluateTransSeq");
	}
      if (x==NULL)
	{
	  if (ts->t[i]->t!=CT_TRANS)
	    {
	      if (ts->t[i]->v==NO_UINT)
		PrintReal(f,ts->t[i]->val);
	      else
		{
		  if (varNames!=NULL)
		    { 
		      char *n;
		  
		      n=varNames[ts->t[i]->v];
		      PRINT_VARIABLE_NAME(f,n);
		    }
		  else
		    fprintf(f,"v_%u",ts->t[i]->v);
		}
	      fprintf(f,")");
	    }
	}
      if (ts->t[i]->s<0)
	fprintf(f,"^-1");
      
      if ((x==NULL)&&(i<(ts->n-1)))
	fprintf(f,"*");
    }
}

void DeleteTransSeq(TTransSeq *ts)
{
  ResetTransSeq(ts);
  free(ts->t);
}
