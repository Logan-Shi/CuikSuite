#include "joint.h"

#include "error.h"
#include "defines.h"
#include "algebra.h"
#include "varnames.h"

#include <math.h>
#include <string.h>

/** \file joint.c
    \brief Implementaton of the function operating on Tjoint.
    
    Implementaton of the function operating on Tjoint.

    \sa Tjoint, joint.h.
*/

/** 
    \brief Initializes all fields for a joint with dummy values.

    Initializes all fields for a joint with dummy/defalult values.
    In this way the functions defining new joints only have to worry about
    setting the right values in the right.

    Using this set up functions defining new joints MUST call this
    function at the beginning of the definition of the new joint.

    \param t  Type of joint.
    \param id Unique identifier given to the joint. 
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct Cost of actions. Used in LQR to penalize deviations from 0.
              For joints with many degrees of freedom the same cost is used
	      for all of them.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize
*/
void InitJoint(unsigned int t,unsigned int id,
	       unsigned int linkID1,Tlink *link1,
	       unsigned int linkID2,Tlink *link2,
	       double ve,double ac,double ef,double ct,double fr,double da,
	       Tjoint *j);

void InitJoint(unsigned int t,unsigned int id,
	       unsigned int linkID1,Tlink *link1,
	       unsigned int linkID2,Tlink *link2,
	       double ve,double ac,double ef,double ct,double fr,double da,
	       Tjoint *j)
{
  unsigned int i,k;

  j->t=t;
  j->id=id;

  if ((linkID1==linkID2)||(link1==link2))
    Error("Setting up a joint on a single link");

  if ((GetLinkType(link1)==LINK_Connect)||
      (GetLinkType(link2)==LINK_Connect))
    Error("Connection links can not be used in joints");
  
  j->linkID[0]=linkID1;
  j->linkID[1]=linkID2;
  j->link[0]=link1;
  j->link[1]=link2;

  for(i=0;i<6;i++)
    {
      for(k=0;k<3;k++)
	j->points[i][k]=0.0;
    }

  for(i=0;i<3;i++)
    {
      for(k=0;k<3;k++)
	j->normals[i][k]=0.0;
    }

  NewInterval(-INF,INF,&(j->normRange));

  j->hasLimits=FALSE;
  j->hasReference=FALSE;

  j->coupled=NULL;

  j->avoidLimits=FALSE;
  j->avoidLimitsWeight=0.0;

  NewInterval(-INF,INF,&(j->range));
  NewInterval(-INF,INF,&(j->range2));

  j->offset=0;
  j->offset2=0;

  HTransformIdentity(&(j->preT));
  HTransformIdentity(&(j->postT));

  j->maxCoord=0.0;

  if (ve<0.0)
    Error("Negative max velocity");
  j->velocity=ve;
  if (ac<0.0)
    Error("Negative max acceleration");
  j->acceleration=ac;
  if (ef<0.0)
    Error("Negative max effort");
  j->effort=ef;
  if (ct<=0)
    Error("Non-positive LQR cost");
  j->cost=ct;
  if (fr<0.0)
    Error("Negative friction");
  j->friction=fr;
  if (da<0.0)
    Error("Negative damping");
  j->damping=da;
}

void NewFreeJoint(unsigned int id,
		  unsigned int linkID1,Tlink *link1,
		  unsigned int linkID2,Tlink *link2,
		  double ve,double ac,double ef,double ct,double fr,double da,
		  Tjoint *j)
{
  InitJoint(FREE_JOINT,id,linkID1,link1,linkID2,link2,ve,ac,ef,ct,fr,da,j);
  j->maxCoord=INF;
}

void NewFixJoint(unsigned int id,
		 unsigned int linkID1,Tlink *link1,
		 unsigned int linkID2,Tlink *link2,
		 THTransform *t,
		 Tjoint *j)
{ 
  InitJoint(FIX_JOINT,id,linkID1,link1,linkID2,link2,0,0,INF,1.0,INF,INF,j);
  
  HTransformCopy(&(j->preT),t);
  
  /*
    The translation form link1 to link2 is used in loops.
    We store it in points[0] to speed up the access 
    (see GenerateJointEquationsInBranch)
   */
  j->points[0][0]=HTransformGetElement(0,3,t);
  j->points[0][1]=HTransformGetElement(1,3,t);
  j->points[0][2]=HTransformGetElement(2,3,t);

  j->maxCoord=Norm(3,j->points[0]);
}

void NewRevoluteJoint(unsigned int id,unsigned int r,
		      unsigned int linkID1,Tlink *link1,
		      unsigned int linkID2,Tlink *link2,
		      double **points,
		      boolean hasLimits,boolean hasReference,
		      Tinterval *range,double **rPoints,
		      boolean avoidLimits,double avoidLimitsWeight,Tjoint *coupled,
		      double ve,double ac,double ef,double ct,double fr,double da,
		      Tjoint *j)
{
  unsigned int i,k;
  double nr;
  double *x,*y,z[3],v[3],c;

  InitJoint(REV_JOINT,id,linkID1,link1,linkID2,link2,ve,ac,ef,ct,fr,da,j);

  j->maxCoord=0;
  for(i=0;i<4;i++)
    {
      for(k=0;k<3;k++)
	j->points[i][k]=ADJUST_REAL(points[i][k]);
      c=Norm(3,j->points[i]);
      if (c>j->maxCoord) j->maxCoord=c;
    }

  /* compute the normalized vectors along the rotation axis */
  for(i=0;i<2;i++)
    {
      nr=0.0;
      for(k=0;k<3;k++)
	{
	  j->normals[i][k]=j->points[2*i+1][k]-j->points[2*i][k];
	  nr+=(j->normals[i][k]*j->normals[i][k]);
	}
      nr=sqrt(nr);
      if (nr<ZERO)
	Error("Null rotation axis in NewRevoluteJoint");
      for(k=0;k<3;k++)
	j->normals[i][k]/=nr;
    }

  j->hasLimits=hasLimits;
  j->hasReference=hasReference;
  if ((j->hasLimits)&&(!j->hasReference))
    Error("Revolute joints with limits must have also a reference");

  if (j->hasReference)
    {
      double c;

      for(i=0;i<2;i++)
	{
	  /*normalize the reference vectors*/
	  nr=0.0;
	  for(k=0;k<3;k++)
	    {
	      j->vrange[i][k]=ADJUST_REAL(rPoints[i][k])-j->points[2*i][k];
	      nr+=(j->vrange[i][k]*j->vrange[i][k]);
	    }
	  nr=sqrt(nr);
	  if (nr<ZERO)
	    Error("Null reference vector in NewRevoluteJoint");
	  for(k=0;k<3;k++)
	    j->vrange[i][k]/=nr;

	  /*Test that the rotation vectors are orthogonal to the rotation axes*/
	  c=0; /*cosinus between the two vectors*/
	  for(k=0;k<3;k++)
	    c+=(j->vrange[i][k]*j->normals[i][k]);

	  if (fabs(c)>ZERO)
	    Error("Rotation axes and rotation reference vectors are not orthonormal (Revolute Joint)");
	}
    }
  if (j->hasLimits)
    CopyInterval(&(j->range),range); /*Copy of the range for the rotation angle*/

  /* The pre-post transform matrices are computed before applying any offset to the
     reference axis, if any. */
  x=j->normals[0];
  if (j->hasReference)
    y=j->vrange[0];
  else
    {
      DefineNormalVector(v,x);
      y=v;
    }
  CrossProduct(x,y,z);
  HTransformFromVectors(x,y,z,j->points[0],&(j->preT));

  x=j->normals[1];
  if (j->hasReference)
    y=j->vrange[1];
  else
    {
      DefineNormalVector(v,x);
      y=v;
    }
  CrossProduct(x,y,z);
  HTransformFromVectors(x,y,z,j->points[2],&(j->postT));
  HTransformInverse(&(j->postT),&(j->postT));

  /* Now offset the references for those representation that need it */
  if ((j->hasLimits)&&(r!=REP_JOINTS))  /* hasLimits -> hasReference */
    {
      THTransform t,rx,a;
      double zero[3]={0,0,0};

      /*We offset the range so that it is zero-centered*/
      j->offset=IntervalCenter(&(j->range));
      IntervalOffset(&(j->range),-j->offset,&(j->range));

      /* Since we moved the rotation range to make it zero-centered, we 
	 have to rotate the reference vectors accordingly. 
	 In this way, the angle between the reference vectors is changed in 
	 the same  way as the offset applied to the range interval. */
      /* The rotation is around the vector defining the revolute joint for
	 the current link. This rotation is defined by rotating the axis 
	 vector to the X axis, rotating around X and then rotating the 
	 vector back to the its original position.*/

      HTransformX2Vect(1,1,zero,j->normals[0],&t); /* this rotates X to the
						      revolute axis vector*/
      HTransformRx(j->offset,&rx); /*rotation around X*/
      
      HTransformInverse(&t,&a); /*this rotates the axis vector to X*/
      HTransformProduct(&rx,&a,&a);
      HTransformProduct(&t,&a,&a);
      
      HTransformApply(j->vrange[0],j->vrange[0],&a); 
      
      HTransformDelete(&a);
      HTransformDelete(&rx);
      HTransformDelete(&t);
    }

  if (IntervalSize(&(j->range))>0)
    {
      j->avoidLimits=avoidLimits;
      j->avoidLimitsWeight=avoidLimitsWeight;
    }
  else
    {
      j->avoidLimits=FALSE;
      j->avoidLimitsWeight=0;
    }
      
  if (coupled!=NULL)
    {
      if (coupled->t!=REV_JOINT)
	Error("Revolute joints can only be coupled with other revolute joints");

      if (!coupled->hasLimits)
	Error("Revolute joints can not be coupled to an unbounded revolute joint");

      j->coupled=(void *)coupled;
    }	
}


void NewUniversalJoint(unsigned int id,unsigned int r,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       boolean hasLimits,boolean hasReference,
		       Tinterval*range1,Tinterval *range2,double **rPoints,
		       boolean avoidLimits,double avoidLimitsWeight,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j)
{
  unsigned int i,k;
  double nr;
  double *x,*y,z[3],v[3],c;

  InitJoint(UNV_JOINT,id,linkID1,link1,linkID2,link2,ve,ac,ef,ct,fr,da,j);
  
  j->maxCoord=0;
  for(i=0;i<4;i++)
    {
      for(k=0;k<3;k++)
	j->points[i][k]=ADJUST_REAL(points[i][k]);
      c=Norm(3,j->points[i]);
      if (c>j->maxCoord) j->maxCoord=c;
    }

  /* compute the normalized vectors along the rotation axis */
  for(i=0;i<2;i++)
    {
      nr=0.0;
      for(k=0;k<3;k++)
	{
	  j->normals[i][k]=j->points[2*i+1][k]-j->points[2*i][k];
	  nr+=(j->normals[i][k]*j->normals[i][k]);
	}
      if (nr<ZERO)
	Error("Null rotation axis in NewUniversalJoint");
      nr=sqrt(nr);
      for(k=0;k<3;k++)
	j->normals[i][k]/=nr;
    }

  j->hasLimits=hasLimits;
  j->hasReference=hasReference;
  if ((j->hasLimits)&&(!j->hasReference))
    Error("Universal joints with limits must have also a reference");

  if (j->hasReference)
    {
      double c;

      for(i=0;i<2;i++)
	{
	  /*normalize the reference vectors*/
	  nr=0.0;
	  for(k=0;k<3;k++)
	    {
	      j->vrange[i][k]=ADJUST_REAL(rPoints[i][k])-j->points[2*i][k];
	      nr+=(j->vrange[i][k]*j->vrange[i][k]);
	    }
	  nr=sqrt(nr);
	  if (nr<ZERO)
	    Error("Null reference vector in NewUniversalJoint");
	  for(k=0;k<3;k++)
	    j->vrange[i][k]/=nr;

	  /*Test that the rotation vectors are orthogonal to the rotation axes*/
	  c=0; /*cosinus between the two vectors*/
	  for(k=0;k<3;k++)
	    c+=(j->vrange[i][k]*j->normals[i][k]);

	  if (fabs(c)>ZERO)
	    Error("Rotation axes and rotation reference vectors are not orthonormal (Universal Joint)");
	}
    }
  
  /*Copy of the ranges for the 2 rotation angles*/
  /*and we offset them so that they are zero-centered*/
  if (j->hasLimits)
    {
      CopyInterval(&(j->range),range1);
      CopyInterval(&(j->range2),range2);
    }
  
  /* The pre-post transform matrices are computed before applying any offset to the
     reference axis, if any. */
  x=j->normals[0];
  if (j->hasReference)
    y=j->vrange[0];
  else
    {
      DefineNormalVector(v,x);
      y=v;
    }
  CrossProduct(x,y,z);
  HTransformFromVectors(x,y,z,j->points[0],&(j->preT));

  x=j->normals[1];
  if (j->hasReference)
    y=j->vrange[1];
  else
    {
      DefineNormalVector(v,x);
      y=v;
    }
  CrossProduct(x,y,z);
  HTransformFromVectors(x,y,z,j->points[2],&(j->postT));
  HTransformInverse(&(j->postT),&(j->postT));

  /* Now offset the references for those representation that need it */
  if ((j->hasLimits)&&(r!=REP_JOINTS))
    {
      THTransform t,rx,a;
      double zero[3]={0,0,0};
      Tinterval *rd; 
      double *center;

      for(k=0;k<2;k++)
	{
	  if (k==0)
	    {
	      rd=&(j->range);
	      center=&(j->offset);
	    }
	  else
	    {
	      rd=&(j->range2);
	      center=&(j->offset2);
	    }

	  /*We offset the ranges so that they are zero-centered*/
	  *center=IntervalCenter(rd);
	  IntervalOffset(rd,-(*center),rd);
	  
	  /* Since we moved the rotation range to make it zero-centered, we 
	     have to rotate ONE of the the reference vectors accordingly. 
	     In this way, the angle between the reference vectors is changed 
	     in the same way as the offset applied to the range interval. */
	  /* The rotation is around the vector defining the revolute joint 
	     for the current link. This rotation is defined by rotating the 
	     axis vector to the X axis, rotating around X and then rotating 
	     the vector back to the its original position.*/
	  HTransformX2Vect(1,1,zero,j->normals[k],&t); /* this rotates X to 
							  to the revolute 
							  axis vector*/
	  HTransformRx((k==0?1:-1)*(*center),&rx); /* rotation around X */
	  
	  HTransformInverse(&t,&a); /* this rotates the axis vector to X */
	  HTransformProduct(&rx,&a,&a);
	  HTransformProduct(&t,&a,&a);
	  
	  HTransformApply(j->vrange[k],j->vrange[k],&a);
      
	  HTransformDelete(&a);
	  HTransformDelete(&rx);
	  HTransformDelete(&t);
	}
    }
  if ((IntervalSize(&(j->range))>0)&&
      (IntervalSize(&(j->range2))>0))
    {
      j->avoidLimits=avoidLimits;
      j->avoidLimitsWeight=avoidLimitsWeight;
    }
  else
    {
      j->avoidLimits=FALSE;
      j->avoidLimitsWeight=0;
    }
}

void NewSphericalJoint(unsigned int id,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       boolean hasLimits,double range,double **rPoints,
		       boolean avoidLimits,double avoidLimitsWeight,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j)
{
  unsigned int i,k;
  double nr,c;
  double zero[3]={0.0,0.0,0.0};

  InitJoint(SPH_JOINT,id,linkID1,link1,linkID2,link2,ve,ac,ef,ct,fr,da,j);

  /*for spherical joints only one point in each link is given, we replicate
    if as if we are given two points. */
  for(k=0;k<3;k++)
    {
      j->points[0][k]=ADJUST_REAL(points[0][k]);
      j->points[1][k]=ADJUST_REAL(points[0][k]);
    }
  for(k=0;k<3;k++)
    {
      j->points[2][k]=ADJUST_REAL(points[1][k]);
      j->points[3][k]=ADJUST_REAL(points[1][k]);
    }
  j->maxCoord=0;
  for(k=0;k<4;k++)
    {
      c=Norm(3,j->points[k]);
      if (c>j->maxCoord) j->maxCoord=c;
    }

  j->hasLimits=hasLimits;

  if (j->hasLimits)
    {
      NewInterval(-range,range,&(j->range));
      j->offset=0;
      /*normalize the reference vectors*/
      for(i=0;i<2;i++)
	{
	  nr=0.0;
	  for(k=0;k<3;k++)
	    {
	      j->vrange[i][k]=ADJUST_REAL(rPoints[i][k])-j->points[2*i][k];
	      nr+=(j->vrange[i][k]*j->vrange[i][k]);
	    }
	  nr=sqrt(nr); 
	  if (nr<ZERO)
	    Error("Null reference vector in NewSphericalJoint");
	  for(k=0;k<3;k++)
	    j->vrange[i][k]/=nr;
	}

      if (IntervalSize(&(j->range))>0)
	{
	  j->avoidLimits=avoidLimits;
	  j->avoidLimitsWeight=avoidLimitsWeight;
	}
      else
	{
	  j->avoidLimits=FALSE;
	  j->avoidLimitsWeight=0;
	}
    }

  HTransformTxyz(j->points[0][0],j->points[0][1],j->points[0][2],
		 &(j->preT));
  if (j->hasLimits)
    {
      THTransform ref;

      HTransformX2Vect(1,1,zero,j->vrange[0],&ref);
      HTransformProduct(&(j->preT),&ref,&(j->preT));
    }
  
  HTransformTxyz(j->points[2][0],j->points[2][1],j->points[2][2],
		 &(j->postT));
  if (j->hasLimits)
    {
      THTransform ref;

      HTransformX2Vect(1,1,zero,j->vrange[1],&ref);
      HTransformProduct(&(j->postT),&ref,&(j->postT));
    }
  HTransformInverse(&(j->postT),&(j->postT));
}

void NewPrismaticJoint(unsigned int id,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,Tinterval *range,
		       boolean avoidLimits,double avoidLimitsWeight,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j)
{
  unsigned int i,k;
  double nr,c;
  //double *x,v[3],z[3];

  InitJoint(PRS_JOINT,id,linkID1,link1,linkID2,link2,ve,ac,ef,ct,fr,da,j);

  j->maxCoord=0;
  for(i=0;i<4;i++)
    {
      for(k=0;k<3;k++)
	j->points[i][k]=ADJUST_REAL(points[i][k]);

      c=Norm(3,j->points[i]);
      if (c>j->maxCoord) j->maxCoord=c;
    }

  for(i=0;i<2;i++)
    {
      nr=0.0;
      for(k=0;k<3;k++)
	{
	  j->normals[i][k]=j->points[2*i+1][k]-j->points[2*i][k];
	  nr+=(j->normals[i][k]*j->normals[i][k]);
	}
      nr=sqrt(nr);
      if (nr<ZERO)
	Error("Null axis in NewPrismaticJoint");
      for(k=0;k<3;k++)
	j->normals[i][k]/=nr;
    }

  j->hasLimits=TRUE;
  CopyInterval(&(j->range),range);
  c=IntervalSize(range);
  if (c>j->maxCoord) j->maxCoord=c;

  if (IntervalSize(&(j->range))>0)
    {
      j->avoidLimits=avoidLimits;
      j->avoidLimitsWeight=avoidLimitsWeight;
    }

  HTransformTxyz(j->points[0][0],j->points[0][1],j->points[0][2],
		 &(j->preT));
  HTransformTxyz(j->points[2][0],j->points[2][1],j->points[2][2],
		 &(j->postT));
  HTransformInverse(&(j->postT),&(j->postT));
  /*
  x=j->normals[0];
  DefineNormalVector(v,x);
  CrossProduct(x,v,z);
  HTransformFromVectors(x,v,z,j->points[0],&(j->preT));

  x=j->normals[1];
  DefineNormalVector(v,x);
  CrossProduct(x,v,z);
  HTransformFromVectors(x,v,z,j->points[2],&(j->postT));
  HTransformInverse(&(j->postT),&(j->postT));
  */
}

void NewSphSphLowJoint(unsigned int id,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j)
{
  NewSphericalJoint(id,linkID1,link1,linkID2,link2,points,
		    FALSE,INF,NULL,FALSE,1,ve,ac,ef,ct,fr,da,j);
  j->t=SPH_SPH_LOW_JOINT;
}

void NewSphSphUpJoint(unsigned int id,
		      unsigned int linkID1,Tlink *link1,
		      unsigned int linkID2,Tlink *link2,
		      double **points,
		      double ve,double ac,double ef,double ct,double fr,double da,
		      Tjoint *j)
{
  NewSphericalJoint(id,linkID1,link1,linkID2,link2,points,
		    FALSE,INF,NULL,FALSE,1,ve,ac,ef,ct,fr,da,j);
  /* If following a deform link, the deformation will already
     take care of diaplacing the joints. */
  if (IsVariableLengthLink(link1))
    HTransformIdentity(&(j->preT));
  j->t=SPH_SPH_UP_JOINT;
}

void NewRevLowJoint(unsigned int id,
		    unsigned int linkID1,Tlink *link1,
		    unsigned int linkID2,Tlink *link2,
		    double **points,
		    double ve,double ac,double ef,double ct,double fr,double da,
		    Tjoint *j)
{
  unsigned int i;
  double **p;

  if ((fabs(points[0][2])>ZERO)||(fabs(points[1][2])>ZERO))
    Error("REV_LOW_JOINT should be defined in the XY plane");
  
  NEW(p,4,double*);
  for(i=0;i<4;i++)
    NEW(p[i],3,double);
   
  /* no point should have Z */
  for(i=0;i<3;i++)
    {
      p[0][i]=points[0][i];
      p[1][i]=points[0][i];
      p[2][i]=points[1][i]; /* This is likely to be 0,0,0 */
      p[3][i]=points[1][i];
    }
  p[1][2]+=1; /* rotation in z */
  p[3][2]+=1;
  
  NewRevoluteJoint(id,REP_JOINTS, /* only used when limits are given (not the case here) */
		   linkID1,link1,linkID2,link2,
		   p,
		   FALSE,FALSE,NULL,NULL,FALSE,0,NULL,
		   ve,ac,ef,ct,fr,da,j);
  j->t=REV_LOW_JOINT;

  HTransformTxyz(p[0][0],p[0][1],p[0][2],&(j->preT));  /* Txy displacement */
  HTransformTxyz(-p[2][0],-p[2][1],-p[2][2],&(j->postT)); /* Identity (in general) */
  
  for(i=0;i<4;i++)
    free(p[i]);
  free(p);
}

void NewRevUpJoint(unsigned int id,
		   unsigned int linkID1,Tlink *link1,
		   unsigned int linkID2,Tlink *link2,
		   double **points,
		   double ve,double ac,double ef,double ct,double fr,double da,
		   Tjoint *j)
{
  unsigned int i;
  double **p;

  if ((fabs(points[0][2])>ZERO)||(fabs(points[1][2])>ZERO))
    Error("REV_UP_JOINT should be defined in the XY plane");
  
  NEW(p,4,double*);
  for(i=0;i<4;i++)
    NEW(p[i],3,double);
    
  /* no point should have Z */
  for(i=0;i<3;i++)
    {
      p[0][i]=points[0][i]; 
      p[1][i]=points[0][i];
      p[2][i]=points[1][i]; 
      p[3][i]=points[1][i];
    }
  p[1][2]+=1; /* rotation in z */
  p[3][2]+=1;
  
  NewRevoluteJoint(id,REP_JOINTS, /* only used when limits are given (not the case here) */
		   linkID1,link1,linkID2,link2,
		   p,
		   FALSE,FALSE,NULL,NULL,FALSE,0,NULL,
		   ve,ac,ef,ct,fr,da,j);
  
  j->t=REV_UP_JOINT;
  
  /* If following a deform link, the deformation will already
     take care of displacing the joints. */
  if (IsVariableLengthLink(link1))
    HTransformIdentity(&(j->preT));
  else
    HTransformTxyz(p[0][0],p[0][1],p[0][2],&(j->preT)); /* basically a Tx */
  HTransformTxyz(-p[2][0],-p[2][1],-p[2][2],&(j->postT));  /* basically 0 */
  
  for(i=0;i<4;i++)
    free(p[i]);
  free(p);
}

void NewInPatchJoint(unsigned int id,
		     unsigned int linkID1,Tlink *link1,
		     unsigned int linkID2,Tlink *link2,
		     double **points,
		     double **patch,
		     boolean avoidLimits,double avoidLimitsWeight,
		     double ve,double ac,double ef,double ct,double fr,double da,
		     Tjoint *j)
{
  unsigned int k;
  double aux0[3],t1[3],t2[3];
  double n1,n2;
  Tinterval range,v,a;
  double nr,c;
  double vect[3];

  InitJoint(IN_PATCH_JOINT,id,linkID1,link1,linkID2,link2,ve,ac,ef,ct,fr,da,j);
  
  /* Store the 2 points defining the point and normal on the first link (not
     in the patch!)*/
  nr=0.0;
  for(k=0;k<3;k++)
    {
      j->points[0][k]=ADJUST_REAL(points[0][k]);
      j->points[1][k]=ADJUST_REAL(points[1][k])-j->points[0][k];
      nr+=(j->points[1][k]*j->points[1][k]);
    }
  nr=sqrt(nr);
  if (nr<ZERO)
    Error("Null normal vector in NewInPatchJoint");
  for(k=0;k<3;k++)
    {
      j->points[1][k]/=nr;
      vect[k]=j->points[0][k]+j->points[1][k]; /* Vector used to define preT */
    }

  j->maxCoord=Norm(3,j->points[0]);
  for(k=0;k<4;k++)
    {
      c=Norm(3,patch[k]);
      if (c>j->maxCoord) j->maxCoord=c;
    }

  /* Store the 4 points defining the patch in the second link. Actually we do
     not directly store the points but some differences between them
     With this we have that
       p=po+u*(p0->p2)+v*(p0->p1)+w*(p0-p1-p2+p3)
       p=points[2]+u*points[3]+v*points[4]+w*points[5]
     where
       w=u*v
  */
  for(k=0;k<3;k++)
    {
      /* p0 */
      j->points[2][k]=patch[0][k];
      /* (p0->p2)=p2-p0 */
      j->points[3][k]=patch[2][k]-patch[0][k];
      /* (p0->p1)=p1-p0 */
      j->points[4][k]=patch[1][k]-patch[0][k];
      /* d=(p0-p1-p2+p3) */
      j->points[5][k]=patch[0][k]-patch[1][k]-patch[2][k]+patch[3][k];
    }

  /* Size of the sides of the patch: must be larger than 0 */
  n1=DotProduct(j->points[3],j->points[3]);
  n2=DotProduct(j->points[4],j->points[4]);

  if ((n1<ZERO)||(n2<ZERO))
    Error("Patch is too small");

  /*Store information to recover the normal at any point in the patch.
    The normal is defined as
       n=n0+u*n1+v*n2
    with
       n0=(p0->p2)x(p0->p1)
       n1=(p0->p2)x d
       n2=d x (p0->p1)
  */
  /* (p0->p2) x (p0->p1) */
  CrossProduct(j->points[3],j->points[4],j->normals[0]);
  /* (p0->p2) x d */
  CrossProduct(j->points[3],j->points[5],j->normals[1]);
  /* d x (p0->p1) */
  CrossProduct(j->points[5],j->points[4],j->normals[2]);

  /*Check if the input points correctly define a patch.
    Points defining a patch are given as
              p2------p3
              |       |
              |       |
              p0------p1
    Thus, in a correct patch vector p0->p3 is enclosed in 
    vectors p0->p2 and p0->p1.
    We check if this is so ensuring that angle p2-p0-p3 has the
    same sign as angle p3-p0-p1
   */
  for(k=0;k<3;k++)
    aux0[k]=patch[3][k]-patch[0][k]; /*This is p0->p3*/

  if ((DotProduct(aux0,j->points[3])<ZERO)||
      (DotProduct(aux0,j->points[4])<ZERO))
    Error("Patch with overlapping points");

  CrossProduct(j->points[3],aux0,t1); /* t1=(p0->p2) x (p0->p3) */
  CrossProduct(aux0,j->points[4],t2); /* t2=(p0->p3) x (p0->p1) */
  
  /* Now we check that the above vectors have the same orientation */
  if (DotProduct(t1,t2)<ZERO)
    Error("Patch points given in the wrong order");

  /*Now we compute the range for the norm of the normal vector
       n=n0+u*n1+v*n2
   The norm is
     l=sqrt(n0+u*n1+v*n2)*(n0+u*n1+v*n2)=
       sqrt(n0*n0+u*n1*n0+v*n2*n0+n0*u*n1+u*n1*u*n1+v*n2*u*n1+v*n2*n0+v*n2*u*n1+v*n2*v*n2)=
       sqrt(n0*n0+n1*n1*u^2+n2*n2*v^2+2(n1*n0)*u+2*(n2*n0)*v+2*(n2*n1)*u*v
   The range for l is bounded via interval evaluation of the above expression
   with u=v=u^2=v^3=u*v=[0,1]
  */
  NewInterval(0,1,&v); /* range for u,v,u^2,v^2,u*v */

  n1=DotProduct(j->normals[0],j->normals[0]); /*n0*n0*/
  NewInterval(n1,n1,&range);

  n1=DotProduct(j->normals[1],j->normals[1]); /*+n1*n1*u^2*/
  IntervalScale(&v,n1,&a);
  IntervalAdd(&range,&a,&range);

  n1=DotProduct(j->normals[2],j->normals[2]); /*+n2*n2*v^2*/
  IntervalScale(&v,n1,&a);
  IntervalAdd(&range,&a,&range);
  
  n1=2*DotProduct(j->normals[0],j->normals[1]); /*+2*n0*n1*u*/
  IntervalScale(&v,n1,&a);
  IntervalAdd(&range,&a,&range);

  n1=2*DotProduct(j->normals[0],j->normals[2]); /*+2*n0*n2*v*/
  IntervalScale(&v,n1,&a);
  IntervalAdd(&range,&a,&range);

  n1=2*DotProduct(j->normals[1],j->normals[2]); /*+2*n1*n2*u*v*/
  IntervalScale(&v,n1,&a);
  IntervalAdd(&range,&a,&range);

  IntervalSqrt(&range,&(j->normRange)); /*final sqrt*/
  
  /*Now we store the avoid limit information, if any*/
  j->hasLimits=TRUE; /*Limits are given by the patch*/

  NewInterval(0,1,&(j->range));
  NewInterval(0,1,&(j->range2));

  /* For non-zero area patch considere avoidLimits */
  if ((DotProduct(j->points[3],j->points[3])>0)&&
      (DotProduct(j->points[4],j->points[4])>0))
    {
      j->avoidLimits=avoidLimits;
      j->avoidLimitsWeight=avoidLimitsWeight;
    }

  /* vect = points[0]+points[1] */
  HTransformX2Vect(1,1,j->points[0],vect,&(j->preT));
  HTransformIdentity(&(j->postT));
}

void CopyJoint(Tjoint *j_dst,Tjoint *j_src)
{
  unsigned int i,k;

  j_dst->t=j_src->t;

  j_dst->id=j_src->id;

  for(i=0;i<2;i++)
    {
      j_dst->linkID[i]=j_src->linkID[i];
      j_dst->link[i]=j_src->link[i];
    }

  for(i=0;i<6;i++)
    {
      for(k=0;k<3;k++)
	j_dst->points[i][k]=j_src->points[i][k];
    }

  for(i=0;i<3;i++)
    {
      for(k=0;k<3;k++)
	j_dst->normals[i][k]=j_src->normals[i][k];
    }

  j_dst->maxCoord=j_src->maxCoord;

  j_dst->hasLimits=j_src->hasLimits;
  j_dst->hasReference=j_src->hasReference;

  j_dst->coupled=j_src->coupled;

  j_dst->avoidLimits=j_src->avoidLimits;
  j_dst->avoidLimitsWeight=j_src->avoidLimitsWeight;

  CopyInterval(&(j_dst->normRange),&(j_src->normRange));

  CopyInterval(&(j_dst->range),&(j_src->range)); 
  CopyInterval(&(j_dst->range2),&(j_src->range2)); 
  j_dst->offset=j_src->offset;
  j_dst->offset2=j_src->offset2;

  for(i=0;i<2;i++)
    {
      for(k=0;k<3;k++)
	j_dst->vrange[i][k]=j_src->vrange[i][k];
    }

  HTransformCopy(&(j_dst->preT),&(j_src->preT));
  HTransformCopy(&(j_dst->postT),&(j_src->postT));

  j_dst->velocity=j_src->velocity;
  j_dst->acceleration=j_src->acceleration;
  j_dst->effort=j_src->effort;
  j_dst->cost=j_src->cost;
  j_dst->friction=j_src->friction;
  j_dst->damping=j_src->damping;
}

unsigned int GetJointType(Tjoint *j)
{
  return(j->t);
}

double GetJointMaxCoordinate(Tjoint *j)
{
  return(j->maxCoord);
}

unsigned int GetJointID(Tjoint *j)
{
  return(j->id);
}

unsigned int JointFromID(Tjoint *j)
{
  return(j->linkID[0]);
}

Tlink *JointFrom(Tjoint *j)
{
  return(j->link[0]);
}

unsigned int JointToID(Tjoint *j)
{
  return(j->linkID[1]);
}

Tlink *JointTo(Tjoint *j)
{
  return(j->link[1]);
}

void GetJointName(char **name,Tjoint *j)
{
  char *ln1,*ln2;

  ln1=GetLinkName(j->link[0]);
  ln2=GetLinkName(j->link[1]);
  NEW(*name,strlen(ln1)+strlen(ln2)+100,char);

  switch(j->t)
    {
    case FREE_JOINT:
      sprintf(*name,"Free %s---%s",ln1,ln2);
      break;
    case FIX_JOINT:
      sprintf(*name,"Fix %s---%s",ln1,ln2);
      break;
    case PRS_JOINT:
      sprintf(*name,"Prismatic %s---%s",ln1,ln2);
      break;
    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT:
    case SPH_SPH_UP_JOINT:
      sprintf(*name,"Spheric %s---%s",ln1,ln2);
      break;
    case REV_JOINT:
    case REV_LOW_JOINT:
    case REV_UP_JOINT:
      sprintf(*name,"Revolute %s---%s",ln1,ln2);
      break;
    case UNV_JOINT:
      sprintf(*name,"Universal %s---%s",ln1,ln2);
      break;
    case IN_PATCH_JOINT:
      sprintf(*name,"In patch %s---%s",ln1,ln2);
      break;
    default:
      Error("Undefined joint type in GetJointName");
    }
}

void GetJointDOFName(unsigned int ndof,char **name,Tjoint *j)
{
  switch(j->t)
    {
    case FREE_JOINT:
      NEW(*name,5,char);
      switch(ndof)
	{
	case 0:
	  sprintf(*name,"Tx");
	  break;
	case 1:
	  sprintf(*name,"Ty");
	  break;
	case 2:
	  sprintf(*name,"Tz");
	  break;
	case 3:
	  sprintf(*name,"Rz");
	  break;
	case 4:
	  sprintf(*name,"Ry");
	  break;
	case 5:
	  sprintf(*name,"Rx");
	  break;
	default:
	  Error("Wrong dof index in GetJointDOFName");
	}
      break;
    case FIX_JOINT:
      *name=NULL;
      break;
    case PRS_JOINT:
      *name=NULL;
      break;
    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT:
      NEW(*name,5,char);
      switch(ndof)
	{
	case 0:
	  sprintf(*name,"Rz");
	  break;
	case 1:
	  sprintf(*name,"Ry");
	  break;
	case 2:
	  sprintf(*name,"Rx");
	  break;
	default:
	  Error("Wrong dof index in GetJointDOFName");
	}
      break;
    case SPH_SPH_UP_JOINT:
      NEW(*name,5,char);
      switch(ndof)
	{
	case 0:
	  sprintf(*name,"Rx");
	  break;
	case 1:
	  sprintf(*name,"Ry");
	  break;
	case 2:
	  sprintf(*name,"Rz");
	  break;
	default:
	  Error("Wrong dof index in GetJointDOFName");
	}
      break;
    case REV_JOINT:
    case REV_LOW_JOINT:
    case REV_UP_JOINT:
      *name=NULL;
      break;
    case UNV_JOINT:
      NEW(*name,5,char);
      switch(ndof)
	{
	case 0:
	  sprintf(*name,"R1");
	  break;
	case 1:
	  sprintf(*name,"R2");
	  break;
	default:
	  Error("Wrong dof index in GetJointDOFName");
	}
      break;
    case IN_PATCH_JOINT:
      NEW(*name,5,char);
      switch(ndof)
	{
	case 0:
	  sprintf(*name,"u");
	  break;
	case 1:
	  sprintf(*name,"v");
	  break;
	case 2:
	  sprintf(*name,"phi");
	  break;
	default:
	  Error("Wrong dof index in GetJointDOFName");
	}
      break;
    default:
      Error("Undefined joint type in GetJointName");
    }
}  

void GetJointPoint(unsigned int link,unsigned int point,double *p,Tjoint *j)
{
  unsigned int i,k;

  i=link*2+point;

  for(k=0;k<3;k++)
    p[k]=j->points[i][k];
}

boolean LimitedJoint(Tjoint *j)
{
  return(j->hasLimits);
}

Tinterval *GetJointRange(Tjoint *j)
{ 
  return(&(j->range));
}

Tinterval *GetJointSecondRange(Tjoint *j)
{ 
  return(&(j->range2));
}

void GetJointRangeN(unsigned int nr,double mt,Tinterval *r,Tjoint *j)
{
  switch(j->t)
    {
    case FREE_JOINT:
      if (nr<6)
	{
	  if (nr<3)
	    NewInterval(-mt,mt,r);
	  else
	    NewInterval(-M_PI,M_PI,r);
	}
      else
	Error("Unknown range number in free joint (GetJointRangeN)");
      break;
    case FIX_JOINT:
      Error("Fix Joints have no DOFs");
      break;
    case PRS_JOINT:
      if (nr<1)
	CopyInterval(r,&(j->range));
      else
	Error("Unknown range number in prismatic joint (GetJointRangeN)");
      break;
    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT: /* unlimited spherical */
    case SPH_SPH_UP_JOINT:  /* unlimited spherical */
      if (nr<3)
	{
	  if ((j->t==SPH_SPH_LOW_JOINT)&&(nr==2))
	    NewInterval(0,0,r);
	  else
	    {
	      if ((!j->hasLimits)||(nr==2))
		NewInterval(-M_PI,M_PI,r);
	      else
		CopyInterval(r,&(j->range));
	    }
	}
      else
	Error("Unknown range number in spherical joint (GetJointRangeN)");
      break;
    case REV_JOINT:
    case REV_LOW_JOINT: /* unlimited revolute */
    case REV_UP_JOINT:  /* unlimited revolute */
      if (nr<1)
	{
	  if (j->hasLimits)
	    IntervalOffset(&(j->range),j->offset,r);
	  else
	    NewInterval(-M_PI,M_PI,r);
	}
      else
	Error("Unknown range number in revolute joint (GetJointRangeN)");
      break;
    case UNV_JOINT:
      if (nr<2)
	{
	  if (!j->hasLimits)
	    NewInterval(-M_PI,M_PI,r);
	  else
	    {
	      if (nr==0)
		IntervalOffset(&(j->range),j->offset,r);
	      else
		IntervalOffset(&(j->range2),j->offset2,r);
	    }
	}
      else
	Error("Unknown range number in universal joint (GetJointRangeN)");
      break;
    case IN_PATCH_JOINT:
      if (nr<3)
	{
	  if (nr==0)
	    CopyInterval(r,&(j->range));
	  else
	    {
	      if (nr==1)
		CopyInterval(r,&(j->range2));
	      else
		NewInterval(-M_PI,M_PI,r);
	    }
	} 
      else
	Error("Unknown range number in in_patch joint (GetJointRangeN)"); 
      break;
    default:
      Error("Undefined joint type in GetJointRangeN");
    }
}

unsigned int GetJointRangeTopology(unsigned int nr,Tjoint *j)
{
  unsigned int tp=0;

  switch(j->t)
    {
    case FREE_JOINT:
      if (nr<6)
	{
	  if (nr<3)
	    tp=TOPOLOGY_R;
	  else
	    tp=TOPOLOGY_S;
	}
      else
	Error("Unknown range number in free joint (GetJointRangeTopology)");
      break;
    case FIX_JOINT:
      Error("Fix Joints have no DOFs");
      break;
    case PRS_JOINT:
      if (nr<1)
	tp=TOPOLOGY_R;
      else
	Error("Unknown range number in prismatic joint (GetJointRangeTopology)");
      break;
    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT: /* unlimited spherical */
    case SPH_SPH_UP_JOINT:  /* unlimited spherical */
      if (nr<3)
	{
	  if ((j->t==SPH_SPH_LOW_JOINT)&&(nr==2))
	    tp=TOPOLOGY_R;
	  else
	    {
	      if (nr<2)
		tp=(j->hasLimits?TOPOLOGY_R:TOPOLOGY_S);
	      else
		tp=TOPOLOGY_S;
	    }
	}
      else
	Error("Unknown range number in spherical joint (GetJointRangeTopology)");
      break;
    case REV_JOINT:
    case REV_LOW_JOINT: /* unlimited revolute */
    case REV_UP_JOINT:  /* unlimited revolute */
      if (nr<1)
	tp=(j->hasLimits?TOPOLOGY_R:TOPOLOGY_S);
      else
	Error("Unknown range number in revolute joint (GetJointRangeTopology)");
      break;
    case UNV_JOINT:
      if (nr<2)
	tp=(j->hasLimits?TOPOLOGY_R:TOPOLOGY_S);
      else
	Error("Unknown range number in universal joint (GetJointRangeTopology)");
      break;
    case IN_PATCH_JOINT:
      if (nr<3)
	{
	  if (nr!=2)
	    tp=TOPOLOGY_R;
	  else
	    tp=TOPOLOGY_S;
	} 
      else
	Error("Unknown range number in in_patch joint (GetJointRangeTopology)");
      break;
    default:
      Error("Undefined joint type in GetJointRangeTopology");
    }

  return(tp);
}

unsigned int CoupledWith(Tjoint *j)
{
  if (j->coupled==NULL)
    return(NO_UINT);
  else
    return(((Tjoint *)(j->coupled))->id);
}

unsigned int GetJointDOF(Tjoint *j)
{
  signed int ndof=0;

  switch(j->t)
    {
    case FREE_JOINT:
      ndof=6;
      break;
    case FIX_JOINT:
      ndof=0;
      break;
    case PRS_JOINT:
      ndof=1;
      break;
    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT: /* unlimited spherical */
    case SPH_SPH_UP_JOINT:  /* unlimited spherical */
      ndof=3;
      break;
    case REV_JOINT:
    case REV_LOW_JOINT: /* unlimited, uncoupled revolute */
    case REV_UP_JOINT:  /* unlimited, uncoupled revolute */
      if (j->coupled==NULL)
	ndof=1;
      else
	ndof=0;
      break;
    case UNV_JOINT:
      ndof=2;
      break;
    case IN_PATCH_JOINT:
      ndof=3;
      break;
    default:
      Error("Undefined joint type in GetJointDOF");
    }
  return(ndof);
}

double GetJointVelocity(Tjoint *j)
{
  return(j->velocity);
}

double GetJointAcceleration(Tjoint *j)
{
  return(j->acceleration);
}

double GetJointEffort(Tjoint *j)
{
  return(j->effort);
}

double GetJointCost(Tjoint *j)
{
  return(j->cost);
}

boolean ActuatedJoint(Tjoint *j)
{
  return(j->effort<INF);
}

double GetJointFriction(Tjoint *j) 
{
  return(j->friction);
}

double GetJointDamping(Tjoint *j)
{
  return(j->damping);
}

THTransform *GetJointFrame(Tjoint *j)
{
  return(&(j->preT));
}

void GetJointPreT(signed int s,THTransform *t,Tjoint *j)
{
  if (s>0)
    HTransformCopy(t,&(j->preT));
  else
    HTransformInverse(&(j->postT),t);
}

void GetJointPostT(signed int s,THTransform *t,Tjoint *j)
{
  if (s>0)
    HTransformCopy(t,&(j->postT));
  else
    HTransformInverse(&(j->preT),t);
}

void GenerateJointRangeSingularityEquations(Tparameters *p,TCuikSystem *cs,Tjoint *j)
{  
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    Error("GenerateJointRangeSingularityEquations not yet implemented for JOINT-based representations.");

  if (j->hasLimits)
    {
      unsigned int i,n;
      double a,b,c,r;
      Tinterval *range;
      Tequation eq;
      Tmonomial f;
      Tinterval r1;
      unsigned int vOrig,vID1,vID2;
      char *vname,*ln1,*ln2;
      Tvariable var;
      
      ln1=GetLinkName(j->link[0]);
      ln2=GetLinkName(j->link[1]);
      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      InitMonomial(&f);
  
      switch (j->t)
	{
	case REV_JOINT:
	case SPH_JOINT:
	case UNV_JOINT:
	  /* revolute ranges given as cosinus of variables */
	  n=((j->t==UNV_JOINT)?2:1);

	  for(i=0;i<n;i++)
	    {
	      range=(i==0?&(j->range):&(j->range2));
	      
	      /*Get the original 'cos' variable*/
	      if (j->t==UNV_JOINT)
		COS_VAR_UNI(vname,j->id,ln1,ln2,i);
	      else
		COS_VAR(vname,j->id,ln1,ln2);
		
	      vOrig=GetCSVariableID(vname,cs);
	      if (vOrig==NO_UINT)
		Error("Undefined variable in GenerateJointRangeSigularityEquations");
	  

	      /* introduce the new t var */
	      if (j->t==UNV_JOINT)
		COS_VAR_UNI_SING(vname,j->id,ln1,ln2,i);
	      else
		COS_VAR_SING(vname,j->id,ln1,ln2);
	      NewInterval(0,1,&r1);

	      NewVariable(SYSTEM_VAR,vname,&var);
	      SetVariableInterval(&r1,&var);
	      
	      vID1=AddVariable2CS(&var,cs);
	      
	      DeleteVariable(&var);

	      /*introduce the new equation: t^2-cos=-cos(lower(range))
                Here we assume that range is symmetrical w.r.t. zero 
	        and, thus lower(cos(range))= cos(lower(range))*/
	      InitEquation(&eq);
	      SetEquationValue(-cos(LowerLimit(range)),&eq);

	      AddVariable2Monomial(NFUN,vID1,2,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      AddCt2Monomial(-1,&f);
	      AddVariable2Monomial(NFUN,vOrig,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      SetEquationCmp(EQU,&eq);
	      SetEquationType(SYSTEM_EQ,&eq);
	      
	      AddEquation2CS(p,&eq,cs);
	      DeleteEquation(&eq);
	    }

	  break;
	  
	case PRS_JOINT:
	case IN_PATCH_JOINT:
	  /* lineal ranges */
	  n=((j->t==IN_PATCH_JOINT)?2:1);

	  for(i=0;i<n;i++)
	    {
	      range=(i==0?&(j->range):&(j->range2));

	      a=LowerLimit(range);
	      b=UpperLimit(range);
	      c=(b+a)/2; /* center */
	      r=(b-a)/2; /* radius */
	      
	      /*Get the original 'l' variable*/
	      if (j->t==IN_PATCH_JOINT)
		IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,i);
	      else
		PRS_JOINT_VAR(vname,j->id,ln1,ln2);

	      vOrig=GetCSVariableID(vname,cs);
	      if (vOrig==NO_UINT)
		Error("Undefined variable in GenerateJointRangeSigularityEquations");

	      /* introduce the new sin var */ 
	      if (j->t==IN_PATCH_JOINT)
		IN_PATCH_JOINT_CTRL_VAR_SING_SIN(vname,j->id,ln1,ln2,i);
	      else
		PRS_JOINT_VAR_SING_SIN(vname,j->id,ln1,ln2);

	      NewVariable(SYSTEM_VAR,vname,&var);
	      NewInterval(-1,1,&r1);
	      SetVariableInterval(&r1,&var);
	  
	      vID1=AddVariable2CS(&var,cs);
	  
	      DeleteVariable(&var);
	  
	      /* introduce the new cos var */ 
	      if (j->t==IN_PATCH_JOINT)
		IN_PATCH_JOINT_CTRL_VAR_SING_COS(vname,j->id,ln1,ln2,i);
	      else
		PRS_JOINT_VAR_SING_COS(vname,j->id,ln1,ln2);

	      NewVariable(SYSTEM_VAR,vname,&var);
	      NewInterval(0,1,&r1);
	      SetVariableInterval(&r1,&var);
	  
	      vID2=AddVariable2CS(&var,cs);
	  
	      DeleteVariable(&var);
	      
	      /*Add two new equations*/

	      /*vOrig-r*vSin=c*/
	      InitEquation(&eq);
	      SetEquationValue(c,&eq);

	      AddVariable2Monomial(NFUN,vOrig,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      AddCt2Monomial(-r,&f);
	      AddVariable2Monomial(NFUN,vID1,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      SetEquationCmp(EQU,&eq);
	      SetEquationType(SYSTEM_EQ,&eq);
	      
	      AddEquation2CS(p,&eq,cs);
	      ResetEquation(&eq);

	      /* s^2+c^2=1*/
	      SetEquationValue(1,&eq);

	      AddVariable2Monomial(NFUN,vID1,2,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      AddVariable2Monomial(NFUN,vID2,2,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      SetEquationCmp(EQU,&eq);
	      SetEquationType(SYSTEM_EQ,&eq);
	      AddEquation2CS(p,&eq,cs);
	      ResetMonomial(&f);
	    }
	  DeleteEquation(&eq);
	  break;
	  
	default:
	  Error("Wrong joint type in GenerateJointRangeSingularityEquations");
	}
      free(vname);
      DeleteMonomial(&f);
    }
}

void GenerateJointRangeEquations(Tparameters *p,TCuikSystem *cs,Tjoint *j)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r!=REP_JOINTS)
    {
      /* Equations associated with the joint 
	 (not joint equations as in the paper :) */

      char *vname;
      unsigned int i,k,id,nv;
      Tequation eq[3],eq1;
      Tinterval rangeOne,rangeInf;
      Tmonomial f;
      unsigned int jointVars[4][3]; /*Reference vector used in REVOLUTE and 
				      SPHERICAL joints*/
      Tvariable var;
      char *ln1,*ln2;
      Tinterval ic;
      double r;
  
      NewInterval(-1.0,1.0,&rangeOne);
      NewInterval(-INF,INF,&rangeInf);

      InitMonomial(&f);

      ln1=GetLinkName(j->link[0]);
      ln2=GetLinkName(j->link[1]);

      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      switch(j->t)
	{
	case FREE_JOINT:
	  /* variables already generated in GenerateJointEquations */
	  break;

	case FIX_JOINT:
	  /* no variables necessary for fix joints */
	  break;

	case PRS_JOINT:
	  /*Add one variable for the displacement along the prismatic axis*/
	  PRS_JOINT_VAR(vname,j->id,ln1,ln2);
      
	  NewVariable(SYSTEM_VAR,vname,&var);
	  SetVariableInterval(&(j->range),&var);

	  nv=AddVariable2CS(&var,cs);

	  DeleteVariable(&var);

	  if (j->avoidLimits)
	    {
	      r=IntervalSize(&(j->range))/2;
	      AddTerm2SearchCriterion(j->avoidLimitsWeight/(r*r),nv,
				      IntervalCenter(&(j->range)),cs);
	    }

	  break;
   
	case UNV_JOINT:
	case REV_JOINT:
	case SPH_JOINT:
	case SPH_SPH_LOW_JOINT: /* unlimited spherical joint -> nothing will be done */
	case SPH_SPH_UP_JOINT:  /* unlimited spherical joint -> nothing will be done */
	case REV_LOW_JOINT: /* unlimited revolute -> nothing will be done */
	case REV_UP_JOINT:  /* unlimited revolute -> nothing will be done */
	  if (j->hasReference) 
	    {
	      /*We define two vectors normal to the rotation axis, one attached
		to link1 (k==0) and another attached to link2 (k==1)*/
	      for(k=0;k<2;k++)
		{ 
		  /*Define the variables for the rotation reference vectors*/
		  for(i=0;i<3;i++)
		    {      	      
		      InitEquation(&(eq[i]));
		      SetEquationValue(0.0,&(eq[i]));

		      if (j->t==REV_JOINT)
			ROT_JOINT_VAR_REF(vname,j->id,k,ln1,ln2,i);
		      else
			{
			  if (j->t==SPH_JOINT)
			    SPH_JOINT_VAR_REF(vname,j->id,k,ln1,ln2,i);
			  else
			    UNV_JOINT_VAR_REF(vname,j->id,k,ln1,ln2,i);
			}

		      NewVariable(SECONDARY_VAR,vname,&var);
		      SetVariableInterval(&rangeOne,&var);

		      id=AddVariable2CS(&var,cs);

		      DeleteVariable(&var);

		      jointVars[k][i]=id;
		      AddVariable2Monomial(NFUN,id,1,&f);
		      AddMonomial(&f,&(eq[i]));
		      ResetMonomial(&f);
		    }

		  ApplyLinkRot(p,-1.0,NO_UINT,j->vrange[k],eq,cs,
			       IsGroundLink(j->linkID[k]),j->link[k]);

		  for(i=0;i<3;i++)
		    {
		      SetEquationCmp(EQU,&(eq[i]));
		      SetEquationType(SYSTEM_EQ,&(eq[i]));

		      AddEquation2CS(p,&(eq[i]),cs);
		      DeleteEquation(&(eq[i]));
		    }
		}  

	      if (j->t==UNV_JOINT)
		{
		  /* The angles for a universal joint are defined from the two 
		     vectors defining the two copunctual, orthogonal rotation 
		     axis towards the two reference vectors given by the user.
		     The first angle is from the 1st reference vector to the 
		     second rotation vector. The second angle is from the 
		     2nd reference vector to the 1st rotation vector.

		     Above we defined variables for the two reference vectors. 
		     Below we retrive the variable identifiers for the two 
		     vectors defining the copunctual, orthogonal rotation 
		     axis (those variables are defined in function 
		     GenerateJointEquations.
		  */
		  for(k=2;k<4;k++)
		    {
		      for(i=0;i<3;i++)
			{  
			  UNV_JOINT_VAR(vname,j->id,ln1,ln2,k-2,i);
			  jointVars[k][i]=GetCSVariableID(vname,cs);
			  if (jointVars[k][i]==NO_UINT)
			    Error("Undefined variables when defining universal joint range equations");
			}
		    }
	      
		  for(k=0;k<2;k++)
		    {
		      GenerateDotProductEquation(jointVars[3-k][0],
						 jointVars[3-k][1],
						 jointVars[3-k][2],
						 jointVars[k][0],
						 jointVars[k][1],
						 jointVars[k][2],
						 NO_UINT,0,&eq1);
		   
		      COS_VAR_UNI(vname,j->id,ln1,ln2,k);
		      NewVariable(SECONDARY_VAR,vname,&var);
		      if (k==0)
			IntervalCosine(&(j->range),&ic);
		      else
			IntervalCosine(&(j->range2),&ic);
		      SetVariableInterval(&ic,&var);
		      DeleteInterval(&ic);
		      id=AddVariable2CS(&var,cs);
		      DeleteVariable(&var);
		   
		      AddVariable2Monomial(NFUN,id,1,&f);
		      AddCt2Monomial(-1,&f);
		      AddMonomial(&f,&eq1);
		      ResetMonomial(&f);
		   
		      SetEquationCmp(EQU,&eq1);
		      SetEquationType(SYSTEM_EQ,&eq1);
		      AddEquation2CS(p,&eq1,cs);
		      DeleteEquation(&eq1);

		      if (j->avoidLimits)
			{
			  r=IntervalSize(&ic);
			  AddTerm2SearchCriterion(j->avoidLimitsWeight/(r*r),id,1,cs);
			}
		    }
		}
	      else
		{
		  /* Revolute and spherical */

		  GenerateDotProductEquation(jointVars[0][0],
					     jointVars[0][1],
					     jointVars[0][2],
					     jointVars[1][0],
					     jointVars[1][1],
					     jointVars[1][2],
					     NO_UINT,0,&eq1);
	      
		  COS_VAR(vname,j->id,ln1,ln2);
		  NewVariable(SECONDARY_VAR,vname,&var);
		  IntervalCosine(&(j->range),&ic);
		  SetVariableInterval(&ic,&var);
		  DeleteInterval(&ic);
		  id=AddVariable2CS(&var,cs);
		  DeleteVariable(&var);
	      
		  AddVariable2Monomial(NFUN,id,1,&f);
		  AddCt2Monomial(-1,&f);
		  AddMonomial(&f,&eq1);
		  ResetMonomial(&f);
	      
		  SetEquationCmp(EQU,&eq1);
		  SetEquationType(SYSTEM_EQ,&eq1);
		  AddEquation2CS(p,&eq1,cs);
		  DeleteEquation(&eq1);

		  if (j->avoidLimits)
		    {
		      r=IntervalSize(&ic);
		      AddTerm2SearchCriterion(j->avoidLimitsWeight/(r*r),id,1,cs);
		    }

		  if ((j->t==REV_JOINT)&&(j->coupled!=NULL))
		    {
		      char *ln1p,*ln2p,*vnamep;
		      unsigned int c1,c2;
		      Tjoint *jp;

		      jp=(Tjoint *)j->coupled;

		      COS_VAR(vname,j->id,ln1,ln2);
		      c1=GetCSVariableID(vname,cs);
		      if (c1==NO_UINT)
			Error("Trying to couple a non-limited revolute joint");

		      ln1p=GetLinkName(jp->link[0]);
		      ln2p=GetLinkName(jp->link[1]);
		      NEW(vnamep,strlen(ln1p)+strlen(ln2p)+100,char);
		      COS_VAR(vnamep,jp->id,ln1p,ln2p);
		      c2=GetCSVariableID(vnamep,cs);
		      if (c2==NO_UINT)
			Error("Trying to couple to a non-limited revolute joint");
		      free(vnamep);

		      /* Add the equation cos1=cos2 */
		      InitEquation(&eq1);
		      SetEquationValue(0.0,&eq1);
		  
		      AddVariable2Monomial(NFUN,c1,1,&f);
		      AddMonomial(&f,&eq1);
		      ResetMonomial(&f);

		      AddVariable2Monomial(NFUN,c2,1,&f);
		      AddCt2Monomial(-1,&f);
		      AddMonomial(&f,&eq1);
		      ResetMonomial(&f);

		      SetEquationCmp(EQU,&eq1);
		      SetEquationType(SYSTEM_EQ,&eq1);
		      AddEquation2CS(p,&eq1,cs);
		      DeleteEquation(&eq1);
		    }
		}
	  
	    }
	  break;
   
	case IN_PATCH_JOINT:
	  /*In patch joints are limited by the 4 points defining the patch. 
	    These limits are implicitly given by the ranges for the control 
	    variables giving the patch. */
	  if (j->avoidLimits)
	    {
	      IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,0);
	      nv=GetCSVariableID(vname,cs);
	      AddTerm2SearchCriterion(j->avoidLimitsWeight*4,nv,0.5,cs);
	  
	      IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,1);
	      nv=GetCSVariableID(vname,cs);
	      AddTerm2SearchCriterion(j->avoidLimitsWeight*4,nv,0.5,cs);
	    }
	  break;
	  
	default:
	  Error("Undefined joint type in GenerateJointRangeEquations");
	}

      DeleteInterval(&rangeOne);
      DeleteInterval(&rangeInf);

      free(vname);
      DeleteMonomial(&f);
    }
}

void GenerateJointEquationsInBranch(Tparameters *p,double s,TCuikSystem *cs,
				    Tequation *eq,Tjoint *j)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    Error("GenerateJointEquationsInBranch should not be used with JOINT-based representation");
  else
    {
      char *l1name,*l2name,*vname;
      unsigned int i,vID,d;
      Tmonomial f;

      l1name=GetLinkName(j->link[0]);
      l2name=GetLinkName(j->link[1]);

      switch (j->t)
	{
	case FREE_JOINT:

	  NEW(vname,strlen(l1name)+strlen(l2name)+100,char);
	  InitMonomial(&f);
	  for(i=0;i<3;i++)
	    {
	      FREE_JOINT_VAR(vname,j->id,j->linkID[0],l1name,j->linkID[1],l2name,i);
	  
	      vID=GetCSVariableID(vname,cs);
	      if (vID==NO_UINT)
		Error("Undefined FREE_JOINT variable in GenerateJointEquationsInBranch");
      
	      AddVariable2Monomial(NFUN,vID,1,&f);
	      AddCt2Monomial(s,&f);
	      AddMonomial(&f,&(eq[i]));
	      ResetMonomial(&f);
	    }
	  DeleteMonomial(&f);
	  free(vname);

	  break;

	case FIX_JOINT:
	  /*The translation part of the homogeneous transform between the two 
	    links has been stored in points[0] (see NewFixJoint). We apply 
	    it here. The rotation constraints are imposed in 
	    GenerateJointEquations. */
	  ApplyLinkRot(p, s,NO_UINT,j->points[0],eq,cs,
		       IsGroundLink(j->linkID[0]),j->link[0]);
	  break;

	case UNV_JOINT:
	case REV_JOINT:
	case SPH_JOINT:
	case SPH_SPH_LOW_JOINT:
	case SPH_SPH_UP_JOINT:
	case REV_LOW_JOINT: 
	case REV_UP_JOINT: 
	  /* for SPH_SPH_UP_JOINT link[0] is
	     an axisX or even a deformX link */
	  ApplyLinkRot(p, s,NO_UINT,j->points[0],eq,cs,
		       IsGroundLink(j->linkID[0]),j->link[0]);
	  /* for SPH_SPH_LOW_JOINT points[2]
	     is zero and link[1] is an axisX link, but anyway*/
	  ApplyLinkRot(p,-s,NO_UINT,j->points[2],eq,cs,
		       IsGroundLink(j->linkID[1]),j->link[1]);
	  break;
	  
	case PRS_JOINT:
	  ApplyLinkRot(p, s,NO_UINT,j->points[0],eq,cs,
		       IsGroundLink(j->linkID[0]),j->link[0]);
		  
	  NEW(vname,strlen(l1name)+strlen(l2name)+100,char);
	  PRS_JOINT_VAR(vname,j->id,l1name,l2name);
	    
	  d=GetCSVariableID(vname,cs);
	  free(vname);
	  if (d==NO_UINT)
	    Error("Undefined PRS_JOINT variable in GenerateJointEquationsInBranch");

	  ApplyLinkRot(p, s,d,j->normals[0],eq,cs,
		       IsGroundLink(j->linkID[0]),j->link[0]);

	  ApplyLinkRot(p,-s,NO_UINT,j->points[2],eq,cs,
		       IsGroundLink(j->linkID[1]),j->link[1]);
	  break;

	case IN_PATCH_JOINT:
	  ApplyLinkRot(p, s,NO_UINT,j->points[0],eq,cs,
		       IsGroundLink(j->linkID[0]),j->link[0]);

	  ApplyLinkRot(p,-s,NO_UINT,j->points[2],eq,cs,
		       IsGroundLink(j->linkID[1]),j->link[1]);      
	  NEW(vname,strlen(l1name)+strlen(l2name)+100,char);
	  for(i=0;i<3;i++)
	    {
	      IN_PATCH_JOINT_CTRL_VAR(vname,j->id,l1name,l2name,i);
	      vID=GetCSVariableID(vname,cs);
	      if (vID==NO_UINT)
		Error("Undefined IN_PATCH_JOINT variable in GenerateJointEquationsInBranch");

	      ApplyLinkRot(p,-s,vID,j->points[3+i],eq,cs,
			   IsGroundLink(j->linkID[1]),j->link[1]);
	    }
	  free(vname);
	  break;

	default:
	  Error("Unkownd joint type"); 
	}
    }
}

void JointForceEquation(Tparameters *pr,unsigned int linkID,TCuikSystem *cs,Tequation *eq,Tjoint *j)
{
  /* This only works for link-based representation. This is checked at a higher-level */
  
  /* only joints incident wth the current link should be considered */
  if ((j->linkID[0]==linkID)||(j->linkID[1]==linkID))
    {
      Tlink *linkBase; /* link defining the director vector */

      /* linkBase = the "other" link in the joint (link != from linkID) */
      if (j->linkID[0]==linkID)
	linkBase=j->link[1];
      else
	linkBase=j->link[0];

      if (GetLinkForceModel(linkBase)!=NO_FORCE)
	{
	  double sg;
	  unsigned int fID; /* force variables */
	  char *lname,*vname;
	  double vectX[3]={1,0,0};

	  /* different signs depending if the joint is a the beginning or
	     at the end of the link exerting the force */
	  if (j->linkID[0]==linkID)
	    sg=+1;
	  else
	    sg=-1;
      
	  lname=GetLinkName(linkBase);
	  NEW(vname,strlen(lname)+100,char); 
	  
	  LINK_MAX_FORCE(vname,lname);
	  fID=GetCSVariableID(vname,cs);

	  ApplyLinkRotNoDeform(pr,sg,fID,vectX,eq,cs,FALSE,linkBase);
	  
	  free(vname);
	}
    }
}

void GenerateJointEquations(Tparameters *p,double maxCoord,
			    TCuikSystem *cs,Tjoint *j)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    {
      unsigned int i,n;
      char *vname;
      Tvariable var;
      Tinterval range;
      char *ln1,*ln2;
      unsigned int tp;

      ln1=GetLinkName(j->link[0]);
      ln2=GetLinkName(j->link[1]);

      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      n=GetJointDOF(j);
      for(i=0;i<n;i++)
	{
	  DOF_VAR(vname,j->id,ln1,ln2,i);
	  
	  NewVariable(SYSTEM_VAR,vname,&var);
	  GetJointRangeN(i,maxCoord,&range,j);
	  SetVariableInterval(&range,&var);
	  tp=GetJointRangeTopology(i,j);
	  if (tp==TOPOLOGY_S)
	    SetVariableTopology(TOPOLOGY_S,&var);
	  
	  AddVariable2CS(&var,cs);
	  DeleteVariable(&var);
	  DeleteInterval(&range);
	}
      free(vname);
    }
  else
    {
      double v[3];
      unsigned int i,k;
      Tequation eq[3],eq1;
      char *ln1,*ln2,*vname;
      Tinterval rangeOne,rangeInf,rangeZeroOne;	
      Tmonomial f;
      unsigned int vID[3]; /* variables generated */
      unsigned int vIDuni[2][3]; /* for the universal joints -> 2 vectors*/
      unsigned int l; /*scale variable of the normal vectors in_patch_joint*/
      Tvariable var;

      ln1=GetLinkName(j->link[0]);
      ln2=GetLinkName(j->link[1]);

      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      NewInterval(-1,1,&rangeOne);
      NewInterval(0,1,&rangeZeroOne);

      InitMonomial(&f);

      switch(j->t)
	{
	case FREE_JOINT:
	  /*We generate 3 new variables representing the (unlimited) 
	    displacement from the origin of the first link to the 
	    origin of the second link.
	    No equations constraint these variables. */
	  NewInterval(-maxCoord,maxCoord,&rangeInf);
	  for(i=0;i<3;i++)
	    {
	      FREE_JOINT_VAR(vname,j->id,j->linkID[0],ln1,j->linkID[1],ln2,i);
	  
	      NewVariable(SYSTEM_VAR,vname,&var);
	      SetVariableInterval(&rangeInf,&var);
	      AddVariable2CS(&var,cs);
	      
	      DeleteVariable(&var);
	    }
	  break;

	case FIX_JOINT: 
	  /* link1 * transform = link2 * identity */
	  /* link1 * transform - link2 * identity = 0 */
	  for(i=0;i<3;i++)
	    {    
	      for(k=0;k<3;k++)
		InitEquation(&(eq[k]));

	      for(k=0;k<3;k++)
		v[k]=HTransformGetElement(k,i,&(j->preT));

	      ApplyLinkRot(p,1,NO_UINT,v,eq,cs,
			   IsGroundLink(j->linkID[0]),j->link[0]);

	      v[0]=v[1]=v[2]=0;
	      v[i]=1;

	      ApplyLinkRot(p,-1,NO_UINT,v,eq,cs,
			   IsGroundLink(j->linkID[1]),j->link[1]);
	  
	      for(k=0;k<3;k++)
		{
		  SetEquationType(SYSTEM_EQ,&(eq[k]));
		  SetEquationCmp(EQU,&(eq[k]));
		  AddEquation2CS(p,&(eq[k]),cs);
		  DeleteEquation(&(eq[k])); 
		}
	    }
	  break;

	case PRS_JOINT:
	  /* The three reference vectors (X,Y,Z) for the two links 
	     are the same when transformed to global coordinates. */
	  for(k=0;k<3;k++)
	    InitEquation(&(eq[k]));
      
	  for(i=0;i<(j->t==PRS_JOINT?3:1);i++)
	    {
	      v[0]=v[1]=v[2]=0.0;
	      v[i]=1.0;

	      for(k=0;k<3;k++)
		InitEquation(&(eq[k]));
	  
	      for(k=0;k<2;k++)
		ApplyLinkRot(p,(k==0?+1.0:-1.0),NO_UINT,v,eq,cs,
			     IsGroundLink(j->linkID[k]),j->link[k]);

	      for(k=0;k<3;k++)
		{
		  SetEquationType(SYSTEM_EQ,&(eq[k]));
		  SetEquationCmp(EQU,&(eq[k]));
		  AddEquation2CS(p,&(eq[k]),cs);
		  DeleteEquation(&(eq[k])); 
		}
	    }
	  break;
      
	case REV_LOW_JOINT:
	case REV_UP_JOINT:
	  /* When using REV_LOW or REP_UP joints all links are in the XY plane and, thus
	     no equation is actually necessary */
	  break;
	  
	case REV_JOINT:
	  /* The vector defining the rotation axis is the same as seen 
	     from the two links. */
	  for(k=0;k<3;k++)
	    InitEquation(&(eq[k]));

	  for(k=0;k<2;k++) /* for the two links involved in the joint */
	    ApplyLinkRot(p,(k==0?+1.0:-1.0),NO_UINT,j->normals[k],eq,cs,
			 IsGroundLink(j->linkID[k]),j->link[k]);

	  for(k=0;k<3;k++)
	    {
	      SetEquationType(SYSTEM_EQ,&(eq[k]));
	      SetEquationCmp(EQU,&(eq[k]));
	      AddEquation2CS(p,&(eq[k]),cs);
	      DeleteEquation(&(eq[k])); 
	    }
	  break;

	case UNV_JOINT:
	  /* Two vectors one attached to link1 and another attached to link2 */
	  for(i=0;i<2;i++)
	    {
	      for(k=0;k<3;k++)
		InitEquation(&(eq[k]));

	      ApplyLinkRot(p,1,NO_UINT,j->normals[i],eq,cs,
			   IsGroundLink(j->linkID[i]),j->link[i]);

	      for(k=0;k<3;k++)
		{
		  UNV_JOINT_VAR(vname,j->id,ln1,ln2,i,k);
	      
		  NewVariable(SECONDARY_VAR,vname,&var);
		  SetVariableInterval(&rangeOne,&var);
	      
		  vIDuni[i][k]=AddVariable2CS(&var,cs);
	      
		  DeleteVariable(&var);

		  AddCt2Monomial(-1.0,&f);
		  AddVariable2Monomial(NFUN,vIDuni[i][k],1,&f);
		  AddMonomial(&f,&(eq[k]));
		  ResetMonomial(&f);

		  SetEquationType(SYSTEM_EQ,&(eq[k]));
		  SetEquationCmp(EQU,&(eq[k]));
		  AddEquation2CS(p,&(eq[k]),cs);
		  DeleteEquation(&(eq[k])); 
		}
	  
	    }

	  /* the two vectors must be orthogonal */
	  GenerateDotProductEquation(vIDuni[0][0],vIDuni[0][1],vIDuni[0][2],
				     vIDuni[1][0],vIDuni[1][1],vIDuni[1][2],
				     NO_UINT,0,&eq1);
	  AddEquation2CS(p,&eq1,cs);
	  DeleteEquation(&eq1);
	  break;

	case SPH_JOINT:
	case SPH_SPH_LOW_JOINT:
	case SPH_SPH_UP_JOINT:
	  /*spherical joints introduce no joint equations (all the constraints
	    of a spherical joint are in the loop equations.*/
	  break;

	case IN_PATCH_JOINT:
	  /* Define the path control variables (u,v) and the dummy w=u*w */
	  for(i=0;i<3;i++)
	    {
	      IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,i);

	      NewVariable((i<2?SYSTEM_VAR:DUMMY_VAR),vname,&var);
	      SetVariableInterval(&rangeZeroOne,&var);

	      vID[i]=AddVariable2CS(&var,cs);

	      DeleteVariable(&var);
	    }

	  /* define the variable for the norm of the normal vector */
	  IN_PATCH_JOINT_SCALE_VAR(vname,j->id,ln1,ln2);

	  NewVariable(SECONDARY_VAR,vname,&var);
	  SetVariableInterval(&(j->normRange),&var);
	  l=AddVariable2CS(&var,cs);
	  DeleteVariable(&var);

	  /* define the equation for the dummy variable w=u*v */
	  GenerateSaddleEquation(vID[0],vID[1],vID[2],&eq1);
	  AddEquation2CS(p,&eq1,cs);
	  DeleteEquation(&eq1);

	  /*Define the equation giving the (square) norm of the normal vector 
	    (i.e., the equation defining 'l')*/
	  InitEquation(&eq1);
	  SetEquationValue(0.0,&eq1);
	  /*n0*n0*/
	  AddCt2Monomial(DotProduct(j->normals[0],j->normals[0]),&f); 
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);
	  /*+n1*n1*u^2*/
	  AddCt2Monomial(DotProduct(j->normals[1],j->normals[1]),&f); 
	  AddVariable2Monomial(NFUN,vID[0],2,&f);
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);
	  /*+n2*n2*v^2*/
	  AddCt2Monomial(DotProduct(j->normals[2],j->normals[2]),&f); 
	  AddVariable2Monomial(NFUN,vID[1],2,&f);
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);
	  /*+2*n0*n1*u*/
	  AddCt2Monomial(2*DotProduct(j->normals[0],j->normals[1]),&f); 
	  AddVariable2Monomial(NFUN,vID[0],1,&f);
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);
	  /*+2*n0*n2*v*/
	  AddCt2Monomial(2*DotProduct(j->normals[0],j->normals[2]),&f); 
	  AddVariable2Monomial(NFUN,vID[1],1,&f);
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);
	  /*+2*n1*n2*u*v=2*n1*n2*w*/
	  AddCt2Monomial(2*DotProduct(j->normals[1],j->normals[2]),&f); 
	  AddVariable2Monomial(NFUN,vID[2],1,&f);
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);

	  AddCt2Monomial(-1.0,&f); /*-l^2*/
	  AddVariable2Monomial(NFUN,l,2,&f);
	  AddMonomial(&f,&eq1);
	  ResetMonomial(&f);

	  SetEquationType(SYSTEM_EQ,&eq1);
	  SetEquationCmp(EQU,&eq1);
	  AddEquation2CS(p,&eq1,cs); 

	  DeleteEquation(&eq1);

	  /* Define the equations aligning the unitary vector on non-patch 
	     link with the normal vector on the patch. Note that the vector 
	     on the non-patch link is scaled by the norm of the patch 
	     normal vector. */
	  for(k=0;k<3;k++)
	    InitEquation(&(eq[k]));
      
	  ApplyLinkRot(p, 1,l,j->points[1],eq,cs,
		       IsGroundLink(j->linkID[0]),j->link[0]);

	  ApplyLinkRot(p,-1,NO_UINT,j->normals[0],eq,cs,
		       IsGroundLink(j->linkID[1]),j->link[1]);
	  ApplyLinkRot(p,-1, vID[0],j->normals[1],eq,cs,
		       IsGroundLink(j->linkID[1]),j->link[1]);
	  ApplyLinkRot(p,-1, vID[1],j->normals[2],eq,cs,
		       IsGroundLink(j->linkID[1]),j->link[1]);

	  for(k=0;k<3;k++)
	    {
	      SetEquationType(SYSTEM_EQ,&(eq[k]));
	      SetEquationCmp(EQU,&(eq[k]));
	      AddEquation2CS(p,&(eq[k]),cs);
	      DeleteEquation(&(eq[k])); 
	    }

	  break;
	  
	default:
	  Error("Unknown joint type in GenerateJointEquations");
	}

      free(vname);
      DeleteInterval(&rangeOne);
      DeleteMonomial(&f);
    }
}


void RegenerateJointSolution(Tparameters *p,TCuikSystem *cs,double *sol,
			     Tjoint *j)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  /* for DOF representations -> nothing to reconstruct */
  if (r!=REP_JOINTS)
    {
      unsigned int i;
      unsigned int vID[3];
      char *vname,*ln1,*ln2;

      ln1=GetLinkName(j->link[0]);
      ln2=GetLinkName(j->link[1]);
  
      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      switch(j->t)
	{
	case IN_PATCH_JOINT:
	  
	  for(i=0;i<3;i++)
	    {
	      IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,i);
	      vID[i]=GetCSVariableID(vname,cs);
	    }
	  
	  sol[vID[2]]=sol[vID[0]]*sol[vID[1]];
	  break;
	}
      free(vname);
    }
}

void RegenerateJointBox(Tparameters *p,TCuikSystem *cs,Tbox *b,Tjoint *j)
{  
  unsigned int r;
  char *vname,*ln1,*ln2;

  ln1=GetLinkName(j->link[0]);
  ln2=GetLinkName(j->link[1]);
  NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  /* for DOF representations -> nothing to reconstruct */
  if (r!=REP_JOINTS)
    {
      unsigned int i;
      unsigned int vID[3];
      Tinterval r;

      switch(j->t)
	{
	case IN_PATCH_JOINT:
	  for(i=0;i<3;i++)
	    {
	      IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,i);
	      vID[i]=GetCSVariableID(vname,cs);
	    }

	  IntervalProduct(GetBoxInterval(vID[0],b),
			  GetBoxInterval(vID[1],b),&r);

	  SetBoxInterval(vID[2],&r,b);

	  break;
	}
    }      
  free(vname);
}

void GenerateJointSolution(Tparameters *p,double *dof,
			   THTransform *t1,THTransform *t2,
			   TCuikSystem *cs,double *sol,
			   Tjoint *j)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    Error("GenerateJointSolution is not defined for JOINTS-based representations");
  else
    {
      char *vname,*ln1,*ln2;
      unsigned int i,k,vID;
      double vector[4][3];
      
      ln1=GetLinkName(j->link[0]);
      ln2=GetLinkName(j->link[1]);

      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      switch(j->t)
	{
	case FREE_JOINT:
	  for(i=0;i<3;i++)
	    {
	      FREE_JOINT_VAR(vname,j->id,j->linkID[0],ln1,j->linkID[1],ln2,i);
	  
	      vID=GetCSVariableID(vname,cs);
	      if (vID==NO_UINT)
		Error("Undefined variable in GenerateJointSolution");

	      sol[vID]=dof[i];
	    }
	  break;
	  
	case FIX_JOINT:
	  /* Fix joints do not define any variable */
	  break;

	case PRS_JOINT:
		  
	  PRS_JOINT_VAR(vname,j->id,ln1,ln2); 
      
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GenerateJointSolution");
      
	  sol[vID]=dof[0];
	  break;

	case UNV_JOINT:
 	  for(i=0;i<2;i++)
	    {
	      /* We only rotate vectors (do not use the translation in
		 the homogeneous matrix).  */
	      HTransformApplyRot(j->normals[i],vector[2+i],(i==0?t1:t2));

	      for(k=0;k<3;k++)
		{
		  UNV_JOINT_VAR(vname,j->id,ln1,ln2,i,k);

		  vID=GetCSVariableID(vname,cs);
		  if (vID==NO_UINT)
		    Error("Undefined variable in GenerateJointSolution");
		  sol[vID]=vector[2+i][k];
		}
	    }
	  /* we continue to the following block (no break here) */

	case REV_JOINT:
	case SPH_JOINT:
	case SPH_SPH_LOW_JOINT: /* unlimited spherical -> nothing will be done */
	case SPH_SPH_UP_JOINT:  /* unlimited spherical -> nothing will be done */
	case REV_LOW_JOINT: /* unlimited revolute -> nothing will be done */
	case REV_UP_JOINT:  /* unlimited revolute -> nothing will be done */
	  if (j->hasLimits)
	    {
	      for(i=0;i<2;i++)
		{
		  /* We only rotate vectors (do not use the translation in
		     the homogeneous matrix).  */
		  HTransformApplyRot(j->vrange[i],vector[i],(i==0?t1:t2));
		
		  for(k=0;k<3;k++)
		    {
		      if (j->t==REV_JOINT)
			ROT_JOINT_VAR_REF(vname,j->id,i,ln1,ln2,k);
		      else
			{
			  if (j->t==SPH_JOINT)
			    SPH_JOINT_VAR_REF(vname,j->id,i,ln1,ln2,k);
			  else
			    UNV_JOINT_VAR_REF(vname,j->id,i,ln1,ln2,k);
			}
		  
		      vID=GetCSVariableID(vname,cs);
		      if (vID==NO_UINT)
			Error("Undefined variable in GenerateJointSolution");

		      sol[vID]=vector[i][k];
		    }
		}
	      if (j->t==UNV_JOINT)
		{
		  for(k=0;k<2;k++)
		    {
		      COS_VAR_UNI(vname,j->id,ln1,ln2,k);
		      vID=GetCSVariableID(vname,cs);
		      if (vID==NO_UINT)
			Error("Undefined variable in GenerateJointSolution");

		      sol[vID]=DotProduct(vector[3-k],vector[k]);
		    }
		}
	      else
		{
		  COS_VAR(vname,j->id,ln1,ln2); 
		  vID=GetCSVariableID(vname,cs);
		  if (vID==NO_UINT)
		    Error("Undefined variable in GenerateJointSolution");
	       
		  sol[vID]=DotProduct(vector[0],vector[1]);
		}
	    }
	  break;

	case IN_PATCH_JOINT:
	  IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,0);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GenerateJointSolution");

	  sol[vID]=dof[0];

	  IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,1);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GenerateJointSolution");

	  sol[vID]=dof[1];

	  IN_PATCH_JOINT_CTRL_VAR(vname,j->id,ln1,ln2,2);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GenerateJointSolution");

	  sol[vID]=dof[0]*dof[1];

	  IN_PATCH_JOINT_SCALE_VAR(vname,j->id,ln1,ln2); 
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GenerateJointSolution");

	  sol[vID]=sqrt(DotProduct(j->normals[0],j->normals[0])+
			DotProduct(j->normals[1],j->normals[1])*dof[0]*dof[0]+
			DotProduct(j->normals[2],j->normals[2])*dof[1]*dof[1]+
			2*DotProduct(j->normals[0],j->normals[1])*dof[0]+
			2*DotProduct(j->normals[0],j->normals[2])*dof[1]+
			2*DotProduct(j->normals[1],j->normals[2])*dof[0]*dof[1]);

	  break;
	  
	default:
	  Error("Unknown joint type in GenerateJointSolution");
      
	} 
      free(vname);
    }
}

void GetJointBasicTransform(double *dof,double *vdof,THTransform *t,THTransform *it,double *s,double *vj,Tjoint *j)
{
  THTransform T;
  unsigned int ndof;
  
  ndof=GetJointDOF(j);
  memset(s,0,6*ndof*sizeof(double));
  
  switch(j->t)
    {
    case FREE_JOINT:
      {
	double c3,s3,c4,s4,c5,s5;
	
	c3=cos(3);
	s3=sin(3);
	
	c4=cos(4);
	s4=sin(4);
	
	c5=cos(5);
	s5=sin(5);
	
	HTransformRx2(s5,c5,t);
	HTransformRy2(s4,c4,&T);HTransformProduct(&T,t,t);
	HTransformRz2(s3,c3,&T);HTransformProduct(&T,t,t);
	HTransformTxyz(dof[0],dof[1],dof[2],&T);HTransformProduct(&T,t,t);
	HTransformDelete(&T);

	HTransformInverse(t,it);

	/* The free joint is defined as

	   Tx(d0) * Ty(d1) * Tz(d2) * Rz(d3) * Ry(d4) * Rx(d5)

	   This is the transform from child to parent: takes coordinates in child's frame
	   and returns them in parent's frame.
	   In dynamics we use the inverse transform (from parent to child): take coordinates
	   in parent's frame and get the same coordiantes in child's frame. In this way we
	   have local (child) coordinates where inertia matrices are constant.
	   Thus, in dynamics we consider

	   Rx(-d5) * Ry(-d4) * Rz(-d3) * Tz(-d2) * Ty(-d1) * Tx(-d0)

	   The effect of d5 is direct (rotation about the Z axis), but the
	   effects of the remaining degrees of freedom depend on the transforms
	   previously applied. For instance the effect of d4 has to take into
	   account Rx(-d5), the effect of d3 is influenced by Rx(-d5)*Ry(-d4), etc.
	   In other words, d4 is a rotation about axis Y, but the actual position
	   of this axis is affected by Rx(-d5). Thus, the actual velocity is

	   vJ_4=Rx(-d5) * [0,dot(d4),0]

	   where vJ_4 is the column of vJ for d4. In 's' we actually store the
	   positioning (i.e. non-velocity) factors (the second column of Rx(-d5) 
	   in this case).
	*/
	
	s[RC2INDEX(3,0,6,ndof)]=c4*c3;
	s[RC2INDEX(4,0,6,ndof)]=c3*s5*s4-s3*c5;
	s[RC2INDEX(5,0,6,ndof)]=c3*c5*s4+s3*s5;
      
	s[RC2INDEX(3,1,6,ndof)]=c4*s3;
	s[RC2INDEX(4,1,6,ndof)]=s3*s5*s4+c3*c5;
	s[RC2INDEX(5,1,6,ndof)]=s3*c5*s4-c3*s5;
      
	s[RC2INDEX(3,2,6,ndof)]=-s4;
	s[RC2INDEX(4,2,6,ndof)]= s5*c4;
	s[RC2INDEX(5,2,6,ndof)]= c5*c4;
      
	s[RC2INDEX(0,3,6,ndof)]=-s4;
	s[RC2INDEX(1,3,6,ndof)]= s5*c4;
	s[RC2INDEX(2,3,6,ndof)]= c5*c4;
      
	s[RC2INDEX(1,4,6,ndof)]= c5;
	s[RC2INDEX(2,4,6,ndof)]=-s5;

	s[RC2INDEX(0,5,6,ndof)]=1;
      }
      break;

    case FIX_JOINT:
      HTransformIdentity(t);
      
      HTransformIdentity(it);
      break;

    case REV_LOW_JOINT: 
    case REV_UP_JOINT:
      {
	double si,co;
	
	si=sin(dof[0]);
	co=cos(dof[0]);
	
	HTransformRz2(si,co,t);
	
	HTransformRz2(-si,co,it);

	s[2]=1;
      }
      break;
      
    case REV_JOINT:
      {
	double si,co;
	
	si=sin(dof[0]);
	co=cos(dof[0]);
      
	HTransformRx2(si,co,t);
      
	HTransformRx2(-si,co,it);
      
	s[0]=1;
      }
      break;
      
    case UNV_JOINT:
      {
	double si0,co0,si1,co1;
	
	si0=sin(dof[0]);
	co0=cos(dof[0]);

	si1=sin(dof[1]);
	co1=cos(dof[1]);
      
	HTransformRx2(si0,co0,t);
	HTransformAcumRot(RZ,1,0,t);
	HTransformAcumRot(RX,-si1,-co1,t); /* rotation of M_PI+dof[1] */

	// Previous version with one product more
	//HTransformRx(dof[0],&T);
	//HTransformAcumRot(RZ,1,0,&T);
	//HTransformRx(M_PI+dof[1],t);
	//HTransformProduct(&T,t,t);
	//HTransformDelete(&T);
      
	HTransformRx2(si1,-co1,it); /* rotation of -(M_PI+dof[1]) */
	HTransformAcumRot(RZ,-1,0,it);
	HTransformAcumRot(RX,-si0,co0,it);

	/* Cuik transfrom:

	   Rx(d0) * Rz(pi/2) * Rx(pi) * Rx(q1)

	   The inverse (relevant in dynamics) is

	   Rx(-q1)*Rx(-pi)*Rz(-pi/2)*Rx(-d0)

	   Thus, the effect of q1 is directly a rotation
	   about X, but the effect of q0 depend on

	   Rx(-q1)*Rx(-pi)*Rz(-pi/2)*[dot{q0],0,0]

	   In other words, q0 is a rotation about X but, the
	   the actual rotation axis is determined by 

	   Rx(-q1)*Rx(-pi)*Rz(-pi/2)
	*/
      
	s[RC2INDEX(1,0,6,ndof)]= co1;
	s[RC2INDEX(2,0,6,ndof)]=-si1;
      
	s[RC2INDEX(0,1,6,ndof)]=1;
      }
      break;

    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT:
      {
	double si0,co0,si1,co1,si2,co2;

	si0=sin(dof[0]);
	co0=cos(dof[0]);
	
	si1=sin(dof[1]);
	co1=cos(dof[1]);
	
	si2=sin(dof[2]);
	co2=cos(dof[2]);
	
	HTransformRz2(si0,co0,t);
	HTransformAcumRot(RY,si1,co1,t);
	HTransformAcumRot(RX,si2,co2,t);
      
	HTransformRx2(-si2,co2,it);
	HTransformAcumRot(RY,-si1,co1,it);
	HTransformAcumRot(RZ,-si0,co0,it);
      
	s[RC2INDEX(0,0,6,ndof)]=-si1;
	s[RC2INDEX(1,0,6,ndof)]= co1*si2;
	s[RC2INDEX(2,0,6,ndof)]= co1*co2;
      
	s[RC2INDEX(1,1,6,ndof)]= co2;
	s[RC2INDEX(2,1,6,ndof)]=-si2;
      
	s[RC2INDEX(0,2,6,ndof)]= 1;
      }
      break;

    case SPH_SPH_UP_JOINT:
      {
	double si0,co0,si1,co1,si2,co2;

	si0=sin(dof[0]);
	co0=cos(dof[0]);
	
	si1=sin(dof[1]);
	co1=cos(dof[1]);
	
	si2=sin(dof[2]);
	co2=cos(dof[2]);
	
	HTransformRx2(si0,co0,t);
	HTransformAcumRot(RY,si1,co1,t);
	HTransformAcumRot(RZ,si2,co2,t);

	HTransformRz2(-si2,co2,it);
	HTransformAcumRot(RY,-si1,co1,it);
	HTransformAcumRot(RX,-si0,co0,it);
      
	s[RC2INDEX(0,0,6,ndof)]= co2*co1;
	s[RC2INDEX(1,0,6,ndof)]= co2*si1;
	s[RC2INDEX(2,0,6,ndof)]= si1;
      
	s[RC2INDEX(0,1,6,ndof)]= si2;
	s[RC2INDEX(1,1,6,ndof)]= co2;
      
	s[RC2INDEX(2,2,6,ndof)]= 1;
      }
      break;
      
    case PRS_JOINT:
      HTransformTxyz(dof[0]*j->normals[0][0],
		     dof[0]*j->normals[0][1],
		     dof[0]*j->normals[0][2],t);

      HTransformTxyz(-dof[0]*j->normals[0][0],
		     -dof[0]*j->normals[0][1],
		     -dof[0]*j->normals[0][2],it);
      
      s[3]=j->normals[0][0];
      s[4]=j->normals[0][1];
      s[5]=j->normals[0][2];
      break;
      
    case IN_PATCH_JOINT:
      {
	double x[3],y[3],z[3],p[3];

	Error("GetJointBasicTransform is not yet implemented for IN_PATCH joints");

	/* The code below is an approximation of what has to be done. */
	
	HTransformRx(dof[2],t);

	/* Normal to the patch */
	/* x=n0+u*n1+v*n2 */
	SumVectorScale(3,j->normals[0],dof[0],j->normals[1],x);
	SumVectorScale(3,x,dof[1],j->normals[2],x);
	Normalize(3,x);

	/*  */
	/* y=p02+v*d */
	SumVectorScale(3,j->points[3],dof[1],j->points[5],y);
	Normalize(3,y);

	/* z=x X y  */
	CrossProduct(x,y,z);

	/* p=p0+u*p02+v*p01+u*v*d */
	SumVectorScale(3,j->points[2],dof[0],j->points[3],p);
	SumVectorScale(3,p,dof[1],j->points[4],p);
	SumVectorScale(3,p,dof[0]*dof[1],j->points[5],p);

	HTransformFromVectors(x,y,z,p,&T);
	HTransformInverse(&T,&T);

	HTransformProduct(t,&T,t);
	
	HTransformInverse(t,it);
	     
	/* TODO: the s and vj below are not correct */
	s[RC2INDEX(0,0,6,ndof)]=1;
	s[RC2INDEX(4,1,6,ndof)]=1;
	s[RC2INDEX(5,2,6,ndof)]=1;
       
	Error("The dynamics of in_patch joints is not implemented yet");
      }
      break;

    default:
      Error("Unknown joint type in GetJointBasicTransform");
    }

  /* compute the velocity of the joint from 's' */
  if (ndof>0)
    MatrixVectorProduct(6,ndof,s,vdof,vj);
}

void GetJointTransform(double *dof,THTransform *t,Tjoint *j)
{
  THTransform T;

  switch(j->t)
    {
    case FREE_JOINT:
      HTransformRx(dof[5],t);
      HTransformRy(dof[4],&T);HTransformProduct(&T,t,t);
      HTransformRz(dof[3],&T);HTransformProduct(&T,t,t);
      HTransformTxyz(dof[0],dof[1],dof[2],&T);HTransformProduct(&T,t,t);
      HTransformDelete(&T);
      break;

    case FIX_JOINT:
      HTransformCopy(t,&(j->preT));
      break;

    case REV_LOW_JOINT: 
    case REV_UP_JOINT: 
      HTransformCopy(t,&(j->preT));
      HTransformAcumRot(RZ,sin(dof[0]),cos(dof[0]),t);
      HTransformProduct(t,&(j->postT),t);
      break;
      
    case REV_JOINT: 
      HTransformCopy(t,&(j->preT));
      HTransformAcumRot(RX,sin(dof[0]),cos(dof[0]),t);
      HTransformProduct(t,&(j->postT),t);
      break;
      
    case UNV_JOINT:
      HTransformRx(dof[0],&T); 
      HTransformAcumRot(RZ,1,0,&T);      
      HTransformRx(M_PI+dof[1],t);
      HTransformProduct(&T,t,&T);
      
      HTransformProduct(&(j->preT),&T,t);
      HTransformProduct(t,&(j->postT),t);
      
      HTransformDelete(&T);
      break;

    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT:
      HTransformCopy(t,&(j->preT));
      HTransformAcumRot(RZ,sin(dof[0]),cos(dof[0]),t);
      HTransformAcumRot(RY,sin(dof[1]),cos(dof[1]),t);
      HTransformAcumRot(RX,sin(dof[2]),cos(dof[2]),t);
      HTransformProduct(t,&(j->postT),t);
      break;

    case SPH_SPH_UP_JOINT:
      HTransformCopy(t,&(j->preT));
      HTransformAcumRot(RX,sin(dof[0]),cos(dof[0]),t);
      HTransformAcumRot(RY,sin(dof[1]),cos(dof[1]),t);
      HTransformAcumRot(RZ,sin(dof[2]),cos(dof[2]),t);
      HTransformProduct(t,&(j->postT),t);
      break;
      
    case PRS_JOINT:
      HTransformTxyz(dof[0]*j->normals[0][0],
		     dof[0]*j->normals[0][1],
		     dof[0]*j->normals[0][2],&T);

      HTransformProduct(&(j->preT),&T,t);
      HTransformProduct(t,&(j->postT),t);

      HTransformDelete(&T);
      break;
      
    case IN_PATCH_JOINT:
      {
	double x[3],y[3],z[3],p[3];

	HTransformRx(dof[2],t);

	/* x=n0+u*n1+v*n2 */
	SumVectorScale(3,j->normals[0],dof[0],j->normals[1],x);
	SumVectorScale(3,x,dof[1],j->normals[2],x);
	Normalize(3,x);
	
	/* y=p02+v*d */
	SumVectorScale(3,j->points[3],dof[1],j->points[5],y);
	Normalize(3,y);

	/* z=x X y  */
	CrossProduct(x,y,z);

	/* p=p0+u*p02+v*p01+u*v*d */
	SumVectorScale(3,j->points[2],dof[0],j->points[3],p);
	SumVectorScale(3,p,dof[1],j->points[4],p);
	SumVectorScale(3,p,dof[0]*dof[1],j->points[5],p);

	HTransformFromVectors(x,y,z,p,&T);
	HTransformInverse(&T,&T);

	HTransformProduct(t,&T,t);

	HTransformProduct(&(j->preT),t,t);
      }
      break;

    default:
      Error("Unknown joint type in GetJointTransform");
    }
}

void GetJointDOFValues(Tparameters *p,THTransform *t1,THTransform *t2,double *dof,Tjoint *j)
{
  THTransform it1,rel,it;
  double s,c;
  
  /* Get the parameters from the relative transfrom from t1 to t2 */
  /* t1*rel=t2 -> rel = inv(t1)*t2 */
  HTransformInverse(t1,&it1);
  HTransformProduct(&it1,t2,&rel);
  HTransformDelete(&it1);

  /* Discount the pre-post matrices */
  HTransformInverse(&(j->preT),&it);
  HTransformProduct(&it,&rel,&rel);
  HTransformDelete(&it1);
      
  HTransformInverse(&(j->postT),&it);
  HTransformProduct(&rel,&it,&rel);
  HTransformDelete(&it);
  
  switch(j->t)
    {
    case FREE_JOINT:
      /* Translation is direct */
      dof[0]=HTransformGetElement(AXIS_X,AXIS_H,&rel);
      dof[1]=HTransformGetElement(AXIS_Y,AXIS_H,&rel);
      dof[2]=HTransformGetElement(AXIS_Z,AXIS_H,&rel);
      /* Euler Angles from a Transform matrix */
      GetYawPitchRoll(&(dof[3]),&(dof[4]),&(dof[5]),&rel);
      break;

    case SPH_JOINT:
    case SPH_SPH_LOW_JOINT:
      /* Euler Angles from a Transform matrix */
      GetYawPitchRoll(&(dof[0]),&(dof[1]),&(dof[2]),&rel);
      break;
      
    case SPH_SPH_UP_JOINT:
      /* Euler Angles from a Transform matrix */
      GetYawPitchRoll(&(dof[2]),&(dof[1]),&(dof[0]),&rel);
      break;
      
    case FIX_JOINT:
      /* Check if 'rel' is actually Id? */
      break;

    case REV_LOW_JOINT:
    case REV_UP_JOINT:	
      /* Check if 'rel' is actually a Rz transform? */
      c=HTransformGetElement(AXIS_X,AXIS_X,&rel);
      s=HTransformGetElement(AXIS_Y,AXIS_X,&rel);
	      
      dof[0]=atan2(s,c);
      break;
      
    case REV_JOINT:	
      if (j->coupled==NULL)
	{
	  /* Check if 'rel' is actually a Rx transform? */
	  c=HTransformGetElement(AXIS_Y,AXIS_Y,&rel);
	  s=HTransformGetElement(AXIS_Z,AXIS_Y,&rel);
	      
	  dof[0]=atan2(s,c);
	}
      break;

    case UNV_JOINT:
      /* An universal joint with a1, and a2 the dof is 
	 Rx(a1)*Rz(pi/2)*Rx(pi)*Rx(a2)
	 that evaluates to
         [       0,          cos(a2),         -sin(a2), 0]
         [ cos(a1),  sin(a1)*sin(a2),  cos(a2)*sin(a1), 0]
         [ sin(a1), -cos(a1)*sin(a2), -cos(a1)*cos(a2), 0]
         [       0,                0,                0, 1]
      */
      c=HTransformGetElement(AXIS_Y,AXIS_X,&rel);
      s=HTransformGetElement(AXIS_Z,AXIS_X,&rel);
      dof[0]=atan2(s,c);

      c= HTransformGetElement(AXIS_X,AXIS_Y,&rel);
      s=-HTransformGetElement(AXIS_X,AXIS_Z,&rel);
      dof[1]=atan2(s,c);
      break;

    case PRS_JOINT:
      { 
	double d[3];

	d[0]=HTransformGetElement(AXIS_X,AXIS_H,&rel);
	d[1]=HTransformGetElement(AXIS_Y,AXIS_H,&rel);
	d[2]=HTransformGetElement(AXIS_Z,AXIS_H,&rel);

	dof[0]=DotProduct(j->normals[0],d);

	/* Check that fabs(dof[0]) is Norm(3,d) -> d and j->normals[0] are aligned */
      }
      break;
	  
    case IN_PATCH_JOINT:
      {
	double x[3],y[3],z[3],t[3];
	THTransform R,P;
	double d;

	/* Here rel = Rx * P\inv  
	   = Rx * (T(u,v) * R(u,v))\inv
	   = Rx * R(u,v)\tr * (-T(u,v))
	   = R * (-T(u,v))
	   where R is a rotation resulting from Rx * R(u,v)\tr
	   That is, R is the rotation part of 'rel'
	   and T(u,v) = -R\inv * rel
	   and Rx=rel*P(u,v)
	*/
	HTransformCopy(&R,&rel);
	HTransformSetElement(AXIS_X,AXIS_H,0,&R);
	HTransformSetElement(AXIS_Y,AXIS_H,0,&R);
	HTransformSetElement(AXIS_Z,AXIS_H,0,&R);
	HTransformInverse(&R,&R);
	HTransformProduct(&R,&rel,&R);

	t[0]=-HTransformGetElement(AXIS_X,AXIS_H,&R);
	t[1]=-HTransformGetElement(AXIS_Y,AXIS_H,&R);
	t[2]=-HTransformGetElement(AXIS_Z,AXIS_H,&R);
	HTransformDelete(&R);
	DifferenceVector(3,t,j->points[2],t);

	if (Norm(3,j->points[5])<ZERO)
	  {
	    double c1[2],c2[2],c3[2];
		
	    /* t-p0=u*p02+v*p01 */
	    /* solve the overconstrained system */
	    c1[0]=DotProduct(j->points[3],j->points[3]);
	    c1[1]=DotProduct(j->points[4],j->points[3]);

	    c2[0]=c1[1];
	    c2[1]=DotProduct(j->points[4],j->points[4]);

	    c3[0]=DotProduct(j->points[3],t);
	    c3[1]=DotProduct(j->points[4],t);

	    d=Det2x2(c1,c2);
	    dof[0]=Det2x2(c3,c2)/d;
	    dof[1]=Det2x2(c1,c3)/d;
	  }
	else
	  {
	    /* t-p0=u*p02+v*p01+u*v*d */
	    /* solve the lineal system to recover u,v, and w=u*v */
	    d=Det3x3(j->points[3],j->points[4],j->points[5]);
	    dof[0]=Det3x3(t,j->points[4],j->points[5])/d;
	    dof[1]=Det3x3(j->points[3],t,j->points[5])/d;
	    /* There is no need to recover the last variable 
	       (it is u*v) */
	  }

	/*Now define P(u,v) to recover Rx*/

	/* x=n0+u*n1+v*n2 */
	SumVectorScale(3,j->normals[0],dof[0],j->normals[1],x);
	SumVectorScale(3,x,dof[1],j->normals[2],x);
	Normalize(3,x);
	    
	/* y=p02+v*d */
	SumVectorScale(3,j->points[3],dof[1],j->points[5],y);
	Normalize(3,y);
	    
	/* z=x X y  */
	CrossProduct(x,y,z);

	/* t=p0+u*p02+v*p01+u*v*d */
	SumVectorScale(3,j->points[2],dof[0],j->points[3],t);
	SumVectorScale(3,t,dof[1],j->points[4],t);
	SumVectorScale(3,t,dof[0]*dof[1],j->points[5],t);
	    
	HTransformFromVectors(x,y,z,t,&P);

	HTransformProduct(&rel,&P,&rel);
	HTransformDelete(&P);
	    
	/* Chec that rel is actually a Rx? */

	/* Now just recover the rotation */
	s=HTransformGetElement(AXIS_Z,AXIS_Y,&rel);
	c=HTransformGetElement(AXIS_Y,AXIS_Y,&rel);
	dof[2]=atan2(s,c);
      }
      break;

    default:
      Error("Unknow joint type in GetJointDOFValues");
    }
  HTransformDelete(&rel);
}

void GetJointTransSeq(Tparameters *p,TCuikSystem *cs,TTransSeq *ts,Tjoint *j)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r!=REP_JOINTS)
    Error("GetJointSTransform is only defined for JOINT-based representations");
  else
    {
      THTransform cT;
      char *vname;
      unsigned int uID,vID;
      unsigned int i,id;
      char *ln1,*ln2;

      InitTransSeq(ts);

      if ((j->t==REV_JOINT)&&(j->coupled!=NULL))
	{
	  ln1=GetLinkName(((Tjoint *)j->coupled)->link[0]);
	  ln2=GetLinkName(((Tjoint *)j->coupled)->link[1]);
	  id=((Tjoint *)j->coupled)->id;
	}
      else
	{
	  ln1=GetLinkName(j->link[0]);
	  ln2=GetLinkName(j->link[1]);
	  id=j->id;
	}
      NEW(vname,strlen(ln1)+strlen(ln2)+100,char);

      switch(j->t)
	{
	case FREE_JOINT:
	  for(i=0;i<6;i++)
	    {
	      DOF_VAR(vname,id,ln1,ln2,i);
	      vID=GetCSVariableID(vname,cs);
	      if (vID==NO_UINT)
		Error("Undefined variable in GetJointTransSeq");
	      switch(i)
		{
		case 0:
		case 1:
		case 2:
		  AddVarTrans2TransSeq(i,1,vID,ts);
		  break;
		case 3:
		  AddVarTrans2TransSeq(RZ,1,vID,ts);
		  break;
		case 4:
		  AddVarTrans2TransSeq(RY,1,vID,ts);
		  break;
		case 5:
		  AddVarTrans2TransSeq(RX,1,vID,ts);
		  break;
		}
	    }
	  break;

	case FIX_JOINT:
	  AddCtTrans2TransSeq(&(j->preT),ts);
	  break;

	case REV_LOW_JOINT:
	case REV_UP_JOINT:
	  AddCtTrans2TransSeq(&(j->preT),ts);
	  DOF_VAR(vname,id,ln1,ln2,0);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GetJointTransSeq");
	  AddVarTrans2TransSeq(RZ,1,vID,ts);	 
	 
	  AddCtTrans2TransSeq(&(j->postT),ts);
	  break;
	  
	case REV_JOINT:
	  AddCtTrans2TransSeq(&(j->preT),ts);
	  DOF_VAR(vname,id,ln1,ln2,0);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GetJointTransSeq");
	  AddVarTrans2TransSeq(RX,1,vID,ts);	 
	 
	  AddCtTrans2TransSeq(&(j->postT),ts);
	  break;

	case UNV_JOINT:
	  AddCtTrans2TransSeq(&(j->preT),ts);

	  DOF_VAR(vname,id,ln1,ln2,0);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GetJointTransSeq");
	  AddVarTrans2TransSeq(RX,1,vID,ts);

	  HTransformRz2(1,0,&cT); /* Rz(pi/2) */
	  AddCtTrans2TransSeq(&cT,ts);

	  HTransformRx2(0,-1,&cT); /* Rx(pi) */
	  AddCtTrans2TransSeq(&cT,ts);
	  
	  DOF_VAR(vname,id,ln1,ln2,1);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GetJointTransSeq");
	  AddVarTrans2TransSeq(RX,1,vID,ts);
	  
	  AddCtTrans2TransSeq(&(j->postT),ts);
	  break;

	case SPH_JOINT: 
	case SPH_SPH_LOW_JOINT:
	  AddCtTrans2TransSeq(&(j->preT),ts);
	  
	  for(i=0;i<3;i++)
	    { 
	      DOF_VAR(vname,id,ln1,ln2,i);
	      vID=GetCSVariableID(vname,cs);
	      if (vID==NO_UINT)
		Error("Undefined variable in GetJointTransSeq");
	      AddVarTrans2TransSeq(RZ-i,1,vID,ts); /* Rz Ry Rx */
	    }
	  
	  AddCtTrans2TransSeq(&(j->postT),ts);
	  break;
	  
	case SPH_SPH_UP_JOINT:
	  AddCtTrans2TransSeq(&(j->preT),ts);
	  
	  for(i=0;i<3;i++)
	    { 
	      DOF_VAR(vname,id,ln1,ln2,i);
	      vID=GetCSVariableID(vname,cs);
	      if (vID==NO_UINT)
		Error("Undefined variable in GetJointTransSeq");
	      AddVarTrans2TransSeq(RX+i,1,vID,ts); /* Rx Ry Rz */
	    }
	  
	  AddCtTrans2TransSeq(&(j->postT),ts);
	  
	  break;
	case PRS_JOINT: 
	  AddCtTrans2TransSeq(&(j->preT),ts);

	  DOF_VAR(vname,id,ln1,ln2,0);
	  vID=GetCSVariableID(vname,cs);
	  if (vID==NO_UINT)
	    Error("Undefined variable in GetJointTransSeq");
	  AddDispTrans2TransSeq(1,vID,j->normals[0],ts);

	  AddCtTrans2TransSeq(&(j->postT),ts);
	  break;

	case IN_PATCH_JOINT:	  
	  AddCtTrans2TransSeq(&(j->preT),ts);

	  DOF_VAR(vname,id,ln1,ln2,2);
	  vID=GetCSVariableID(vname,cs);
	  AddVarTrans2TransSeq(RX,1,vID,ts);

	  DOF_VAR(vname,id,ln1,ln2,0);
	  uID=GetCSVariableID(vname,cs);

	  DOF_VAR(vname,id,ln1,ln2,1);
	  vID=GetCSVariableID(vname,cs);

	  /* The patch transform inverted */
	  {
	    /* Get the combination of points defined from the patch vertices */
	    unsigned int k;
	    double **p;

	    NEW(p,4,double*);
	    for(k=0;k<4;k++)
	      { NEW(p[k],3,double); }
	    memcpy(p[0],j->points[2],3*sizeof(double));  /* p_0=p_0 */
	    SumVector(3,j->points[4],j->points[2],p[1]); /* p_1=p_01+p_0 */
	    SumVector(3,j->points[3],j->points[2],p[2]); /* p_2=p_02+p_0 */
	    SumVector(3,j->points[5],j->points[2],p[3]); /* p_3=d+p_01+p_02+p_0 */
	    SumVector(3,p[3],j->points[3],p[3]);
	    SumVector(3,p[3],j->points[4],p[3]);

	    AddPatchTrans2TransSeq(PA,-1,uID,vID,p,ts);

	    for(k=0;k<4;k++)
	      free(p[k]);
	    free(p);
	  }
	  break;

	default:
	  Error("Unknow joint type in GetJointTransSeq");
	}
      free(vname);
    }
}

void PrintJointAxes(Tparameters *p,FILE *f,TCuikSystem *cs,double *sol,
		    double *r,Tjoint *j)
{
  THTransform t;
  TLinkConf def;
  double point[3];

  switch(j->t)
    {
    case REV_JOINT:
    case PRS_JOINT:
      GetTransform2Link(p,cs,sol,IsGroundLink(j->linkID[0]),&(r[j->linkID[0]*3]),
			&t,&def,j->link[0]);
      HTransformApply(j->points[0],point,&t);
      fprintf(f,"%.12f %.12f %.12f ",point[0],point[1],point[2]);
      HTransformApplyRot(j->normals[0],point,&t);
      fprintf(f,"%.12f %.12f %.12f ",point[0],point[1],point[2]);
      break;
    case UNV_JOINT:
      GetTransform2Link(p,cs,sol,IsGroundLink(j->linkID[0]),&(r[j->linkID[0]*3]),
			&t,&def,j->link[0]);
      HTransformApply(j->points[0],point,&t);
      fprintf(f,"%.12f %.12f %.12f ",point[0],point[1],point[2]);
      HTransformApplyRot(j->normals[0],point,&t);
      fprintf(f,"%.12f %.12f %.12f ",point[0],point[1],point[2]);
      
      GetTransform2Link(p,cs,sol,IsGroundLink(j->linkID[1]),&(r[j->linkID[1]*3]),
			&t,&def,j->link[1]);
      HTransformApply(j->points[2],point,&t);
      fprintf(f,"%.12f %.12f %.12f ",point[0],point[1],point[2]);
      HTransformApplyRot(j->normals[1],point,&t);
      fprintf(f,"%.12f %.12f %.12f ",point[0],point[1],point[2]);
      break;
    case FREE_JOINT:
      break;
    default:
      Error("PrintJointAxes is not fully implemented yet");
    }
}

void PrintJoint(FILE *f,Tjoint *j)
{ 
  char *ln1,*ln2;
  unsigned int l;

  ln1=GetLinkName(j->link[0]);
  ln2=GetLinkName(j->link[1]);

  switch(j->t)
    {
    case FREE_JOINT:
      break;

    case FIX_JOINT:
      l=3; //strlen("fix")
      fprintf(f,"  fix : %s %s ",ln1,ln2);
      HTransformPrettyPrint(f,&(j->preT));
      fprintf(f,"\n");
      break;

    case PRS_JOINT:
      l=9; // strlent("prismatic")
      fprintf(f,"  prismatic : %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln1,
	      j->points[0][0],j->points[0][1],j->points[0][2],
	      j->points[1][0],j->points[1][1],j->points[1][2]);
      fprintf(f,"              %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln2,
	      j->points[2][0],j->points[2][1],j->points[2][2],
	      j->points[3][0],j->points[3][1],j->points[3][2]);
      fprintf(f,"              range ");
      PrintInterval(f,&(j->range));
      fprintf(f,"\n");
      if (j->avoidLimits)
	fprintf(f,"              avoid limits\n");
      break;

    case SPH_JOINT:
      l=9; // strlent("spherical")
      fprintf(f,"  spherical : %s (%.16f,%.16f,%.16f)\n",ln1,
	      j->points[0][0],j->points[0][1],j->points[0][2]);
      fprintf(f,"              %s (%.16f,%.16f,%.16f)\n",ln2,
	      j->points[2][0],j->points[2][1],j->points[2][2]);
      if (j->hasLimits)
	{
	  fprintf(f,"              range ");
	  PrintInterval(f,&(j->range));
	  fprintf(f," +(%.16f,%.16f,%.16f)",
		  j->vrange[0][0],j->vrange[0][1],j->vrange[0][2]);
	  fprintf(f," +(%.16f,%.16f,%.16f)\n",
		  j->vrange[1][0],j->vrange[1][1],j->vrange[1][2]);
	}
      if (j->avoidLimits)
	fprintf(f,"              avoid limits\n");
      break;

    case REV_JOINT:
      l=8; // strlent("revolute")	
      fprintf(f,"  revolute : %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln1,
	      j->points[0][0],j->points[0][1],j->points[0][2],
	      j->points[1][0],j->points[1][1],j->points[1][2]);  
      fprintf(f,"             %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln2,
	      j->points[2][0],j->points[2][1],j->points[2][2],
	      j->points[3][0],j->points[3][1],j->points[3][2]);

      if (j->hasLimits) /* hasLimits -> hasReference */
	{
	  fprintf(f,"             range ");
	  PrintInterval(f,&(j->range));
	  fprintf(f," +(%.16f,%.16f,%.16f)",
		  j->vrange[0][0],j->vrange[0][1],j->vrange[0][2]);
	  fprintf(f," +(%.16f,%.16f,%.16f)\n",
		  j->vrange[1][0],j->vrange[1][1],j->vrange[1][2]);
	}
      else
	{
	  if (j->hasReference)
	    {
	      fprintf(f,"             reference ");
	      fprintf(f," +(%.16f,%.16f,%.16f)",
		      j->vrange[0][0],j->vrange[0][1],j->vrange[0][2]);
	      fprintf(f," +(%.16f,%.16f,%.16f)\n",
		      j->vrange[1][0],j->vrange[1][1],j->vrange[1][2]);
	    }
	}
      if (j->avoidLimits)
	fprintf(f,"             avoid limits\n");
      break;

    case UNV_JOINT:
      l=9; // strlent("universal")
      fprintf(f,"  universal : %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln1,
	      j->points[0][0],j->points[0][1],j->points[0][2],
	      j->points[1][0],j->points[1][1],j->points[1][2]);
      fprintf(f,"              %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln2,
	      j->points[2][0],j->points[2][1],j->points[2][2],
	      j->points[3][0],j->points[3][1],j->points[3][2]);
      if (j->hasLimits) /* hasLimts -> hasReference */
	{
	  fprintf(f,"              range ");
	  PrintInterval(f,&(j->range));
	  fprintf(f," +(%.16f,%.16f,%.16f)",
		  j->vrange[0][0],j->vrange[0][1],j->vrange[0][2]);
	  PrintInterval(f,&(j->range2));
	  fprintf(f," +(%.16f,%.16f,%.16f)\n",
		  j->vrange[1][0],j->vrange[1][1],j->vrange[1][2]);
	}
      else
	{
	  if (j->hasReference)
	    {
	      fprintf(f,"              reference ");
	      fprintf(f," +(%.16f,%.16f,%.16f)",
		      j->vrange[0][0],j->vrange[0][1],j->vrange[0][2]);
	      fprintf(f," +(%.16f,%.16f,%.16f)\n",
		      j->vrange[1][0],j->vrange[1][1],j->vrange[1][2]);
	    }
	}
      if (j->avoidLimits)
	fprintf(f,"             avoid limits\n");
      break;

    case SPH_SPH_LOW_JOINT:
    case SPH_SPH_UP_JOINT:
    case REV_LOW_JOINT:
    case REV_UP_JOINT:
      /* nothing to print */
      Error("Composite joint are printed at a higher level");
      break;
      
    case IN_PATCH_JOINT:
      {
	double v[3];

	l=8; // strlent("in_patch")
	fprintf(f,"  in_patch : %s (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",ln1,
		j->points[0][0],j->points[0][1],j->points[0][2],
		j->points[1][0],j->points[1][1],j->points[1][2]);
	/* p_0 is directly stored */
	fprintf(f,"             %s (%.16f,%.16f,%.16f)",ln2,
		j->points[2][0],j->points[2][1],j->points[2][2]);
	/* p_1=p_01+p_0 */
	SumVector(3,j->points[4],j->points[2],v);	
	fprintf(f," (%.16f,%.16f,%.16f)",v[0],v[1],v[2]);
	/* p_2=p_02+p_0 */
	SumVector(3,j->points[3],j->points[2],v);
	fprintf(f," (%.16f,%.16f,%.16f)",v[0],v[1],v[2]);
	/* p_3=d+p_01+p_02+p_0 */
	SumVector(3,j->points[5],j->points[2],v);
	SumVector(3,v,j->points[3],v);
	SumVector(3,v,j->points[4],v);
	fprintf(f," (%.16f,%.16f,%.16f)\n",v[0],v[1],v[2]);
	if (j->avoidLimits)
	  fprintf(f,"            avoid limits\n");
      }
      break;

    default:
      Error("Undefined joint type in PrintJoint");
    }
  
  if (j->t!=FIX_JOINT)
    {
      unsigned int i;
      char s[20];

      for(i=0;i<l;i++)
	s[i]=' ';
      s[i]=0;
      
      if (j->velocity<INF)
	fprintf(f,"  %s   velocity %.16f\n",s,j->velocity);
      if (j->acceleration<INF)
	fprintf(f,"  %s   acceleration %.16f\n",s,j->acceleration);
      if (j->effort<INF)
	fprintf(f,"  %s   effort %.16f\n",s,j->effort);
      if (j->friction>0)
	fprintf(f,"  %s   friction %.16f\n",s,j->friction);
      if (j->damping>0)
	fprintf(f,"  %s   damping %.16f\n",s,j->damping);
    }
  fprintf(f,"\n");
}

void DeleteJoint(Tjoint *j)
{
  DeleteInterval(&(j->range));  
  DeleteInterval(&(j->range2));
  HTransformDelete(&(j->preT)); 
  HTransformDelete(&(j->postT));
}
