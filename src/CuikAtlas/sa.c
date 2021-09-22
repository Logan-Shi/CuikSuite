#include "sa.h"

#include "basic_algebra.h"

#include <string.h>

/** 
   \file sa.c

   \brief Implementation of the spatial algebra functions.

   Implementation of the spatial algebra functions.

   \sa sa.h
*/

inline void copySAV(double *sav_dst,double *sav_src)
{
  memcpy(sav_dst,sav_src,sizeof(double)*6);
}

inline void copySAM(double *sam_dst,double *sam_src)
{
  memcpy(sam_dst,sam_src,sizeof(double)*36);
}

void IdentitySAM(double *sam)
{
  unsigned int i;
  
  memset(sam,0,sizeof(double)*36);
  
  for(i=0;i<6;i++)
    sam[RC2INDEX(i,i,6,6)]=1.0;
}

void HTransform2SAM(THTransform *t,double *sam)
{
  unsigned int i,j;
  double v,x,y,z,v1,v2,v3;

  /* We define the matrix 
        [   R   0 ]
	[ tx*R  R ]
     with R taken from the transform and tx defined as
        [ 0 -z  y ]
	[ z  0 -x ]  
	[-y  x  0 ]
     with x,y,z taken also from the transform.
     If R is defined as row vectors
            [ v1 ]
        R = [ v2 ]
            [ v3 ]
	       [ -z*v2+y*v3 ]
        tx*R = [  z*v1-x*v3 ]
	       [ -y*v1+x*v2 ]
   */
  
  memset(sam,0,sizeof(double)*36);

  /* Define the two blocs with R */
  for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
	{
	  v=HTransformGetElement(i,j,t);
	  sam[RC2INDEX(i,j,6,6)]=v;
	  sam[RC2INDEX(i+3,j+3,6,6)]=v;
	}
    }

    x=HTransformGetElement(0,3,t);
    y=HTransformGetElement(1,3,t);
    z=HTransformGetElement(2,3,t);

    /* this is tx*R */
    for(j=0;j<3;j++)
      {
	v1=sam[RC2INDEX(0,j,6,6)];
	v2=sam[RC2INDEX(1,j,6,6)];
	v3=sam[RC2INDEX(2,j,6,6)];
	
	sam[RC2INDEX(3,j,6,6)]=-z*v2+y*v3;
	sam[RC2INDEX(4,j,6,6)]= z*v1-x*v3;
	sam[RC2INDEX(5,j,6,6)]=-y*v1+x*v2;
      }
}

void SAM2HTransform(THTransform *t,double *sam)
{
  unsigned int i,j;
  double x,y,z;
  
  /* Get R */
  for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
	{
	  HTransformSetElement(i,j,sam[RC2INDEX(i,j,6,6)],t);
	}
    }

  /* Get the translation

     t^=(t^*R)*R^t  and x,y,z are specific elements in t^:
            x = t^(2,1) = (t^*R)[2,:]*R(1,:) = sam[5,1:3]*R(1,:)
	    y = t^(0,2) = (t^*R)[0,:]*R(2,:) = sam[3,1:3]*R(2,:)
	    z = t^(1,0) = (t^*R)[1,:]*R(0,:) = sam[4,1:3]*R(0,:)
  */
  x=0;
  y=0;
  z=0;
  for(j=0;j<3;j++)
    {
      x+=sam[RC2INDEX(5,j,6,6)]*HTransformGetElement(1,j,t);
      y+=sam[RC2INDEX(3,j,6,6)]*HTransformGetElement(2,j,t);
      z+=sam[RC2INDEX(4,j,6,6)]*HTransformGetElement(0,j,t);
    }
  /*
  x=sam[RC2INDEX(5,0,6,6)]*HTransformGetElement(1,0,t)+sam[RC2INDEX(5,1,6,6)]*HTransformGetElement(1,1,t)+sam[RC2INDEX(5,2,6,6)]*HTransformGetElement(1,2,t);
  y=sam[RC2INDEX(3,0,6,6)]*HTransformGetElement(2,0,t)+sam[RC2INDEX(3,1,6,6)]*HTransformGetElement(2,1,t)+sam[RC2INDEX(3,2,6,6)]*HTransformGetElement(2,2,t);
  z=sam[RC2INDEX(4,0,6,6)]*HTransformGetElement(0,0,t)+sam[RC2INDEX(4,1,6,6)]*HTransformGetElement(0,1,t)+sam[RC2INDEX(4,2,6,6)]*HTransformGetElement(0,2,t);
  */
  
  HTransformSetElement(0,3,x,t);
  HTransformSetElement(1,3,y,t);
  HTransformSetElement(2,3,z,t);
}

void Translation2SAM(double *t,double *sam)
{
  unsigned int i;
  
  memset(sam,0,sizeof(double)*36);

  for(i=0;i<6;i++)
    sam[RC2INDEX(i,i,6,6)]=1;
 
  sam[RC2INDEX(4,2,6,6)]=-t[0];
  sam[RC2INDEX(5,1,6,6)]=+t[0];
  
  sam[RC2INDEX(5,0,6,6)]=-t[1];
  sam[RC2INDEX(3,2,6,6)]=+t[1];
  
  sam[RC2INDEX(3,1,6,6)]=-t[2];
  sam[RC2INDEX(4,0,6,6)]=+t[2];
}

void HTransformXSAV(THTransform *t,unsigned int n,double *sav1,double *sav2)
{
  unsigned int i;
  double x,y,z;

  /* Lets assume the folowing partition of vectors and matrices
     v=[v1,v2] (one of the vectors in sav1)
     t=[R t]
     w=[w1,w2]; (the corresponding vector in sav2)
     v1,v2, w1, w2 are all vectors of size 3.
     
     The spatial algebra matrix equivalent to t is
     [   R   0 ]
     [ tx*R  R ]
     with 
     [ 0 -z  y ]
     tx = [ z  0 -x ]  
     [-y  x  0 ]

     then

     w1=R*v1
     w2= R*v2 + tx*R*v1 = R*v2 + tx*w1
  */
  
  x=HTransformGetElement(0,3,t);
  y=HTransformGetElement(1,3,t);
  z=HTransformGetElement(2,3,t);
    
  #if (ROW_MAJOR)
    double vIn[3],vOut1[3],vOut2[3];

    x=HTransformGetElement(0,3,t);
    y=HTransformGetElement(1,3,t);
    z=HTransformGetElement(2,3,t);
	
    for(i=0;i<n;i++)
      {	
	vIn[0]=sav1[RC2INDEX(0,n,6,n)];
	vIn[1]=sav1[RC2INDEX(1,n,6,n)];
	vIn[2]=sav1[RC2INDEX(2,n,6,n)];
	
	HTransformApplyRot(vIn,vOut1,t);
	
	sav2[RC2INDEX(0,n,6,n)]=vOut1[0];
	sav2[RC2INDEX(1,n,6,n)]=vOut1[1];
	sav2[RC2INDEX(2,n,6,n)]=vOut1[2];
	
	/* and
	   w2= R*v2 + tx*R*v1 = R*v2 + tx*w1
	*/
	vIn[0]=sav1[RC2INDEX(3,n,6,n)];
	vIn[1]=sav1[RC2INDEX(4,n,6,n)];
	vIn[2]=sav1[RC2INDEX(5,n,6,n)];
	
	HTransformApplyRot(vIn,vOut2,t);
  
	sav2[RC2INDEX(3,n,6,n)]=vOut2[0]+(y*vOut1[2]-z*vOut1[1]);
	sav2[RC2INDEX(4,n,6,n)]=vOut2[1]+(z*vOut1[0]-x*vOut1[2]);
	sav2[RC2INDEX(5,n,6,n)]=vOut2[2]+(x*vOut1[1]-y*vOut1[0]);
      }
  #else
    /* This is the most common case */
    double *v,*w;
    
    for(i=0,v=sav1,w=sav2;i<n;i++,v+=6,w+=6)
      {
	HTransformApplyRot(v,w,t);
  
	HTransformApplyRot(&(v[3]),&(w[3]),t);
  
	w[3]+=(y*w[2]-z*w[1]);
	w[4]+=(z*w[0]-x*w[2]);
	w[5]+=(x*w[1]-y*w[0]);
      }
  #endif
}
  
void SAMinverse(double *sam,double *isam)
{
  THTransform t;

  SAM2HTransform(&t,sam);
  HTransformInverse(&t,&t);
  HTransform2SAM(&t,isam);
}

void crm(double *sav,double *sam)
{
  memset(sam,0,sizeof(double)*36);
    
  sam[RC2INDEX(1,2,6,6)]=-sav[0];
  sam[RC2INDEX(2,1,6,6)]=+sav[0];
  
  sam[RC2INDEX(2,0,6,6)]=-sav[1];
  sam[RC2INDEX(0,2,6,6)]=+sav[1];
  
  sam[RC2INDEX(0,1,6,6)]=-sav[2];
  sam[RC2INDEX(1,0,6,6)]=+sav[2];
  
  
  sam[RC2INDEX(4,5,6,6)]=-sav[0];
  sam[RC2INDEX(5,4,6,6)]=+sav[0];
  
  sam[RC2INDEX(5,3,6,6)]=-sav[1];
  sam[RC2INDEX(3,5,6,6)]=+sav[1];
  
  sam[RC2INDEX(3,4,6,6)]=-sav[2];
  sam[RC2INDEX(4,3,6,6)]=+sav[2];

  
  sam[RC2INDEX(4,2,6,6)]=-sav[3];
  sam[RC2INDEX(5,1,6,6)]=+sav[3];
  
  sam[RC2INDEX(5,0,6,6)]=-sav[4];
  sam[RC2INDEX(3,2,6,6)]=+sav[4];
  
  sam[RC2INDEX(3,1,6,6)]=-sav[5];
  sam[RC2INDEX(4,0,6,6)]=+sav[5];
}

void CRMxSAV(double *sav,double *sav1,double *sav2)
{
  sav2[0]=sav[1]*sav1[2]-sav[2]*sav1[1];
  sav2[1]=sav[2]*sav1[0]-sav[0]*sav1[2];
  sav2[2]=sav[0]*sav1[1]-sav[1]*sav1[0];
  
  sav2[3]=sav[4]*sav1[2]-sav[5]*sav1[1]+sav[1]*sav1[5]-sav[2]*sav1[4];
  sav2[4]=sav[5]*sav1[0]-sav[3]*sav1[2]+sav[2]*sav1[3]-sav[0]*sav1[5];
  sav2[5]=sav[3]*sav1[1]-sav[4]*sav1[0]+sav[0]*sav1[4]-sav[1]*sav1[3];
}

void crf(double *sav,double *sam)
{
  memset(sam,0,sizeof(double)*36);

  sam[RC2INDEX(1,2,6,6)]=-sav[0];
  sam[RC2INDEX(2,1,6,6)]=+sav[0];
  
  sam[RC2INDEX(2,0,6,6)]=-sav[1];
  sam[RC2INDEX(0,2,6,6)]=+sav[1];
  
  sam[RC2INDEX(0,1,6,6)]=-sav[2];
  sam[RC2INDEX(1,0,6,6)]=+sav[2];
  
  
  sam[RC2INDEX(4,5,6,6)]=-sav[0];
  sam[RC2INDEX(5,4,6,6)]=+sav[0];
  
  sam[RC2INDEX(5,3,6,6)]=-sav[1];
  sam[RC2INDEX(3,5,6,6)]=+sav[1];
  
  sam[RC2INDEX(3,4,6,6)]=-sav[2];
  sam[RC2INDEX(4,3,6,6)]=+sav[2];

  
  sam[RC2INDEX(1,5,6,6)]=-sav[3];
  sam[RC2INDEX(2,4,6,6)]=+sav[3];
  
  sam[RC2INDEX(2,3,6,6)]=-sav[4];
  sam[RC2INDEX(0,5,6,6)]=+sav[4];
  
  sam[RC2INDEX(0,4,6,6)]=-sav[5];
  sam[RC2INDEX(1,3,6,6)]=+sav[5];
}

void CRFxSAM(double *sav,double *sam1,double *sam2)
{
  unsigned int ndx[4];
  double s[4];

  ndx[0]=1;
  ndx[1]=2;
  ndx[2]=4;
  ndx[3]=5;
  s[0]=-sav[2];
  s[1]=+sav[1];
  s[2]=-sav[5];
  s[3]=+sav[4];
  ScaledAddRows(6,6,sam1,4,ndx,s,(ROW_MAJOR?1:6),&(sam2[RC2INDEX(0,0,6,6)]));

  ndx[0]=0;
  ndx[1]=2;
  ndx[2]=3;
  ndx[3]=5;
  s[0]=+sav[2];
  s[1]=-sav[0];
  s[2]=+sav[5];
  s[3]=-sav[3];
  ScaledAddRows(6,6,sam1,4,ndx,s,(ROW_MAJOR?1:6),&(sam2[RC2INDEX(1,0,6,6)]));
  
  ndx[0]=0;
  ndx[1]=1;
  ndx[2]=3;
  ndx[3]=4;
  s[0]=-sav[1];
  s[1]=+sav[0];
  s[2]=-sav[4];
  s[3]=+sav[3];
  ScaledAddRows(6,6,sam1,4,ndx,s,(ROW_MAJOR?1:6),&(sam2[RC2INDEX(2,0,6,6)]));
   
  ndx[0]=4;
  ndx[1]=5;
  s[0]=-sav[2];
  s[1]=+sav[1];
  ScaledAddRows(6,6,sam1,2,ndx,s,(ROW_MAJOR?1:6),&(sam2[RC2INDEX(3,0,6,6)]));
  
  ndx[0]=3;
  ndx[1]=5;
  s[0]=+sav[2];
  s[1]=-sav[0];
  ScaledAddRows(6,6,sam1,2,ndx,s,(ROW_MAJOR?1:6),&(sam2[RC2INDEX(4,0,6,6)]));
  
  ndx[0]=3;
  ndx[1]=4;
  s[0]=-sav[1];
  s[1]=+sav[0];
  ScaledAddRows(6,6,sam1,2,ndx,s,(ROW_MAJOR?1:6),&(sam2[RC2INDEX(5,0,6,6)]));
}

inline void scaleSAV(double s,double *sav)
{
  ScaleVector(s,6,sav);
}

inline void scaleSAM(double s,double *sam)
{
  ScaleVector(s,36,sam);
}

inline void accumSAV(double *sav1,double *sav2)
{
  AccumulateVector(6,sav1,sav2);
}

inline void sumSAV(double *sav1,double *sav2,double *sav3)
{
  SumVector(6,sav1,sav2,sav3);
}

inline void accumSAM(double *sam1,double *sam2)
{
  AccumulateVector(36,sam1,sam2);
}

inline void sumSAM(double *sam1,double *sam2,double *sam3)
{
  SumVector(36,sam1,sam2,sam3);
}

inline void SAMxSAV(double *sam,double *sav1,double *sav2)
{
  MatrixVectorProduct(6,6,sam,sav1,sav2);
}

inline void SAMxSAVAccum(double *sam,double *sav1,double *sav2)
{
  MatrixVectorProductAccum(6,6,sam,sav1,sav2);
}

inline void SAMxSAM(double *sam1,double *sam2,double *sam3)
{
  MatrixMatrixProduct(6,6,sam1,6,sam2,sam3);
}

inline void SAMxSAMAccum(double *sam1,double *sam2,double *sam3)
{
  MatrixMatrixProductAccum(6,6,sam1,6,sam2,sam3);
}

inline void TSAMxSAM(double *sam1,double *sam2,double *sam3)
{
  TMatrixMatrixProduct(6,6,sam1,6,sam2,sam3);
}

inline void TSAMxSAV(double *sam,double *sav1,double *sav2)
{
  TMatrixVectorProduct(6,6,sam,sav1,sav2);
}

inline void TSAMxSAVAccum(double *sam,double *sav1,double *sav2)
{
  TMatrixVectorProductAccum(6,6,sam,sav1,sav2);
}

inline void TSAVxSAM(double *sav1,double *sam,double *sav2)
{
  MatrixMatrixProduct(1,6,sav1,6,sam,sav2);
}

inline double SAVxSAV(double *sav1,double *sav2)
{
  return(GeneralDotProduct(6,sav1,sav2));
}

void mci2rbi(double m,double *c,double *IM,double *saI)
{
  memset(saI,0,sizeof(double)*36);

  /*              0       -c(3)     c(2)
     C=skew(c) =  c(3)     0       -c(1)
                 -c(2)     c(1)     0     */
  
  /* rbi[0..2,0..2]=I + m * C*C' */
  saI[RC2INDEX(0,0,6,6)]=IM[RC2INDEX(0,0,3,3)]+m*(c[1]*c[1]+c[2]*c[2]);
  saI[RC2INDEX(0,1,6,6)]=IM[RC2INDEX(0,1,3,3)]-m*c[0]*c[1];
  saI[RC2INDEX(0,2,6,6)]=IM[RC2INDEX(0,2,3,3)]-m*c[0]*c[2];
  saI[RC2INDEX(1,0,6,6)]=IM[RC2INDEX(1,0,3,3)]-m*c[0]*c[1];
  saI[RC2INDEX(1,1,6,6)]=IM[RC2INDEX(1,1,3,3)]+m*(c[0]*c[0]+c[2]*c[2]);
  saI[RC2INDEX(1,2,6,6)]=IM[RC2INDEX(1,2,3,3)]-m*c[1]*c[2];
  saI[RC2INDEX(2,0,6,6)]=IM[RC2INDEX(2,0,3,3)]-m*c[0]*c[2];
  saI[RC2INDEX(2,1,6,6)]=IM[RC2INDEX(2,1,3,3)]-m*c[1]*c[2];
  saI[RC2INDEX(2,2,6,6)]=IM[RC2INDEX(2,2,3,3)]+m*(c[0]*c[0]+c[1]*c[1]);

  /* rbi[0..2,3..5]=m*C */
  saI[RC2INDEX(0,4,6,6)]=-m*c[2];
  saI[RC2INDEX(0,5,6,6)]= m*c[1];
  saI[RC2INDEX(1,3,6,6)]= m*c[2];
  saI[RC2INDEX(1,5,6,6)]=-m*c[0];
  saI[RC2INDEX(2,3,6,6)]=-m*c[1];
  saI[RC2INDEX(2,4,6,6)]= m*c[0];

  /* rbi[3..5,0..2]=m*C' */
  saI[RC2INDEX(3,1,6,6)]= m*c[2];
  saI[RC2INDEX(3,2,6,6)]=-m*c[1];
  saI[RC2INDEX(4,0,6,6)]=-m*c[2];
  saI[RC2INDEX(4,2,6,6)]= m*c[0];
  saI[RC2INDEX(5,0,6,6)]= m*c[1];
  saI[RC2INDEX(5,1,6,6)]=-m*c[0];

  /* rbi[3..5,3..5]=m*Id */
  saI[RC2INDEX(3,3,6,6)]= m;
  saI[RC2INDEX(4,4,6,6)]= m;
  saI[RC2INDEX(5,5,6,6)]= m;
}

void rbi2mci(double *saI,double *m,double *c,double *IM)
{
  double mC[9],mCmCt[9];
  
  *m=saI[RC2INDEX(5,5,6,6)];

  if ((c!=NULL)||(IM!=NULL))
    {
      /* mC=saI(1:3,4:6) */
      MatrixFromSubMatrix(6,6,saI,0,3,3,3,mC);

      if (c!=NULL)
	{
	  /* c=skew(mC)/m */
	  c[0]=mC[RC2INDEX(2,1,3,3)]/(*m);
	  c[1]=mC[RC2INDEX(0,2,3,3)]/(*m);
	  c[2]=mC[RC2INDEX(1,0,3,3)]/(*m);
	}
  
      if (IM!=NULL)
	{
	  /* mCmCt = (mC*mC') / m */
	  MatrixTMatrixProduct(3,3,mC,3,mC,mCmCt);
	  ScaleVector(1.0/(*m),9,mCmCt);
      
	  /* I = saI(1:3,1:3) - mCmCt */
	  MatrixFromSubMatrix(6,6,saI,0,0,3,3,IM);
	  SubtractMatrix(3,3,IM,mCmCt);
	}
    }
}
