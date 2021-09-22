#include "htransform.h"

#include "error.h"
#include "basic_algebra.h"

#include <math.h>
#include <string.h>
#include <basic_algebra.h>

/** 
    \file htransform.c

    \brief Implementation of the functions operating on THTransform.

    Implementation of the functions to generate homogeneous transforms in R^3.

    \sa THTransform, htransform.h.
*/

/*THTransforms[i][j] -> row i   column j */


/** 
   \brief A global constant that defines the identity matrix.
    
   A global constant that defines the identity matrix.
*/
const THTransform matrix_identity={{1.0, 0.0, 0.0, 0.0},
				   {0.0, 1.0, 0.0, 0.0},
				   {0.0, 0.0, 1.0, 0.0},
				   {0.0, 0.0, 0.0, 1.0}};

/** 
   \brief A global constant that defines the zero matrix.
    
   A global constant that defines the zero matrix.
*/
const THTransform matrix_zero={{0.0, 0.0, 0.0, 0.0},
		               {0.0, 0.0, 0.0, 0.0},
			       {0.0, 0.0, 0.0, 0.0},
			       {0.0, 0.0, 0.0, 0.0}};

#ifdef _CBLAS
  /** 
     \brief A fast way to copy one matrix (to) into another matrix(td)

     A fast way to copy one matrix (to) into another matrix(td)
   
     \param td The homogeneous matrix where to copy.
     \param to The homogeneous matrix from where to copy.
  */
  #define MATRIX_INT_COPY(td,to) cblas_dcopy(16,(double*)(to),1,(double*)(td),1)
#else
  /** 
     \brief A fast way to copy one matrix (to) into another matrix(td)

     A fast way to copy one matrix (to) into another matrix(td)
   
     \param td The homogeneous matrix where to copy.
     \param to The homogeneous matrix from where to copy.
  */
  #define MATRIX_INT_COPY(td,to) memcpy((td),(to),sizeof(THTransform))
#endif


/*
 * Returns the identity matrix in t
 */
void HTransformIdentity(THTransform *t /*Resulting matrix*/
		    )
{
  MATRIX_INT_COPY((*t),&matrix_identity);
}

void HTransformZero(THTransform *t)
{
  MATRIX_INT_COPY((*t),&matrix_zero);
}

/*
* Copies to in td
*/
inline void HTransformCopy(THTransform *t_dst, /*HTransform where to copy the original*/
			   THTransform *t_src  /*Original matrix*/
			   )
{
  MATRIX_INT_COPY((*t_dst),(*t_src));
}

/* Identify the identity matrix*/
boolean HTransformIsIdentity(THTransform *t)
{
  return(Distance(16,(double *)t,(double *)matrix_identity)<16*ZERO);
}

/* Identify the zero matrix*/
boolean HTransformIsZero(THTransform *t)
{
  return(Distance(16,(double *)t,(double *)matrix_zero)<16*ZERO);
}

boolean HTransformIsTranslation(THTransform *t)
{
  return((fabs((*t)[AXIS_X][AXIS_X]-1)<ZERO)&&
	 (fabs((*t)[AXIS_Y][AXIS_Y]-1)<ZERO)&&
	 (fabs((*t)[AXIS_Z][AXIS_Z]-1)<ZERO));
}

/*
 * Returns a matrix that produces a translation of size tx along axis x.
 */
void HTransformTx(double tx, /*Translation parameter*/
		  THTransform *t /*Resulting matrix*/
		  )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_H]=tx;
}

/*
 * Returns a matrix that produces a translation of size ty along axis y.
 */
void HTransformTy(double ty, /*Translation parameter*/
		  THTransform *t /*Resulting matrix*/
		  )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_Y][AXIS_H]=ty;
}

/*
 * Returns a matrix that produces a translation of size tz along axis z.
 */
void HTransformTz(double tz, /*Translation parameter*/
		  THTransform *t /*Resulting matrix*/
		  )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_Z][AXIS_H]=tz;
}

/*
 * Returns a matrix that produces a translation of size tx along axis x,
 * of size ty along axis y, and along tz along axis z.
 */
void HTransformTxyz(double tx, /*Translation parameter along the x axis*/
		    double ty, /*Translation parameter along the y axis*/
		    double tz, /*Translation parameter along the z axis*/
		    THTransform *t /*Resulting matrix*/
		    )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_H]=tx;
  (*t)[AXIS_Y][AXIS_H]=ty;
  (*t)[AXIS_Z][AXIS_H]=tz;
}

/*
 * Returns a matrix that produces a rotation of size rx around axis x.
 */
void HTransformRx(double rx, /*Rotation parameter*/
		  THTransform *t /*Resulting matrix*/
		  )
{
  double s,c;

  s=sin(rx);
  c=cos(rx);

  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_Y][AXIS_Y]=c; (*t)[AXIS_Y][AXIS_Z]=-s;
  (*t)[AXIS_Z][AXIS_Y]=s; (*t)[AXIS_Z][AXIS_Z]= c;
}

/*
 * Returns a matrix that produces a rotation of size rt around axis y.
 */
void HTransformRy(double ry, /*Rotation parameter*/
		  THTransform *t /*Resulting matrix*/
		  )
{
  double s,c;

  s=sin(ry);
  c=cos(ry);

  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_X]= c; (*t)[AXIS_X][AXIS_Z]=s;
  (*t)[AXIS_Z][AXIS_X]=-s; (*t)[AXIS_Z][AXIS_Z]=c;
}

/*
 * Returns a matrix that produces a rotation of size rz around axis z.
 */
void HTransformRz(double rz, /*Rotation parameter*/
		  THTransform *t /*Resulting matrix*/
		  )
{
  double s,c;

  s=sin(rz);
  c=cos(rz);

  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_X]=c; (*t)[AXIS_X][AXIS_Y]=-s;
  (*t)[AXIS_Y][AXIS_X]=s; (*t)[AXIS_Y][AXIS_Y]=c;
}

/*
 * Init a rotation matrix around the x axis from a sinus and cosinus value 
 */
void HTransformRx2(double s,double c,THTransform *t)
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_Y][AXIS_Y]=c; (*t)[AXIS_Y][AXIS_Z]=-s;
  (*t)[AXIS_Z][AXIS_Y]=s; (*t)[AXIS_Z][AXIS_Z]= c;
}

/*
 * Init a rotation matrix around the y axis from a sinus and cosinus value 
 */
void HTransformRy2(double s,double c,THTransform *t)
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_X]= c; (*t)[AXIS_X][AXIS_Z]=s;
  (*t)[AXIS_Z][AXIS_X]=-s; (*t)[AXIS_Z][AXIS_Z]=c;
}

/*
 * Init a rotation matrix around the z axis from a sinus and cosinus value 
 */
void HTransformRz2(double s,double c,THTransform *t)
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_X]=c; (*t)[AXIS_X][AXIS_Y]=-s;
  (*t)[AXIS_Y][AXIS_X]=s; (*t)[AXIS_Y][AXIS_Y]=c;
}

void HTransformScale(double s,     /*Scale factor*/
		    THTransform *t /*Resulting matrix*/
		    )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_X]=s;
  (*t)[AXIS_Y][AXIS_Y]=s;
  (*t)[AXIS_Z][AXIS_Z]=s;
}

void HTransformScaleX(double s,     /*Scale factor*/
		     THTransform *t /*Resulting matrix*/
		     )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_X][AXIS_X]=s;
}

void HTransformScaleY(double s,     /*Scale factor*/
		     THTransform *t /*Resulting matrix*/
		     )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_Y][AXIS_Y]=s;
}

void HTransformScaleZ(double s,     /*Scale factor*/
		     THTransform *t /*Resulting matrix*/
		     )
{
  MATRIX_INT_COPY(*t,&matrix_identity);
  (*t)[AXIS_Z][AXIS_Z]=s;
}

/*
 * Returns a transformation matrix of size v along/arond the desired
 * axis. There are six predefined constants (TX,TY,TZ,RX,RY,RX) to
 * facilitate the use of this function.
 */
void HTransformCreate(unsigned int dof_r3, /*DOF*/
		      double v,            /*displacement along/around the DOF*/
		      THTransform *t           /*Resulting matrix*/
		      )
{
  switch (dof_r3)
    {
    case TX:
      HTransformTx(v,t);
      break;
    case TY:
      HTransformTy(v,t);
      break;
    case TZ:
      HTransformTz(v,t);
      break;
    case RX:
      HTransformRx(v,t);
      break;
    case RY:
      HTransformRy(v,t);
      break;
    case RZ:
      HTransformRz(v,t);
      break;
    default:
      Error("Wrong type of transform in HTransformCreate");
    }
}

/*
 * Modifies the value of the element of row i and column j of the matrix t and
 * sets it to v.
*/
inline void HTransformSetElement(unsigned int i, /*row*/
				 unsigned int j, /*column*/
				 double v,       /*New value*/
				 THTransform *t  /*HTransform to be modified*/
				 ) 
{
  #if (_DEBUG>1)
    if ((i>AXIS_H)||(j>AXIS_H))
      Error("Element out of range in HTransformSetElement");
  #endif
  (*t)[i][j]=v;
}

/*
 * Returns the element of row i and column j of matrix t
 */

inline double HTransformGetElement(unsigned int i,/*row*/ 
				   unsigned int j,/*column*/
				   THTransform *t     /*HTransform to be queried*/
				   )
{  
  #if (_DEBUG>1)
    if ((i>AXIS_H)||(j>AXIS_H))
      Error("Element out of range in HTransformGetElement");
  #endif
  return((*t)[i][j]);
}

void HTransformFromVectors(double *x,double *y,double *z,double *h,THTransform *t)
{
  unsigned int i;

  for(i=0;i<3;i++) /* row */
    {
      (*t)[i][AXIS_X]=x[i];
      (*t)[i][AXIS_Y]=y[i];
      (*t)[i][AXIS_Z]=z[i];
      (*t)[i][AXIS_H]=h[i];

      (*t)[AXIS_H][i]=0.0; /* Last row is 0 */
    }
  (*t)[AXIS_H][AXIS_H]=1.0;
}

CBLAS_INLINE void HTransform2GLMatrix(double *m,THTransform *t)
{
  #ifdef _CBLAS
    cblas_dcopy(4,&((*t)[0][0]),4,&(m[ 0]),1);
    cblas_dcopy(4,&((*t)[0][1]),4,&(m[ 4]),1);
    cblas_dcopy(4,&((*t)[0][2]),4,&(m[ 8]),1);
    cblas_dcopy(4,&((*t)[0][3]),4,&(m[12]),1);
  #else
    unsigned int i,j;
    double *ptr;

    ptr=m;
    for(j=0;j<=AXIS_H;j++)
      {
	for(i=0;i<=AXIS_H;i++,ptr++)
	  {
	    *ptr=(*t)[i][j];
	  }
      }
  #endif
}

CBLAS_INLINE void HTransformFromGLMatrix(double *m,THTransform *t)
{
  #ifdef _CBLAS
    cblas_dcopy(4,&(m[ 0]),1,&((*t)[0][0]),4);
    cblas_dcopy(4,&(m[ 4]),1,&((*t)[0][1]),4);
    cblas_dcopy(4,&(m[ 8]),1,&((*t)[0][2]),4);
    cblas_dcopy(4,&(m[12]),1,&((*t)[0][3]),4);
  #else
    unsigned int i,j;
    double *ptr;

    ptr=m;
    for(j=0;j<=AXIS_H;j++)
      {
	for(i=0;i<=AXIS_H;i++,ptr++)
	  {
	    (*t)[i][j]=*ptr;
	  }
      }
  #endif
}

/*
 * Makes the product of two matrixes and returns it on t3.
 *                     t3=t1*t2
 * The procedure is safe enough and enables t3 no to be
 * different from t1 or t2.
 * 
 * This is a CRITICAL function and, thus, we try to accelerate it
 * as much as possible.
 */
CBLAS_INLINE void HTransformProduct(THTransform *t1, /*First matrix*/
				    THTransform *t2, /*Second matrix*/
				    THTransform *t3  /*Resulting matrix*/
				    ) 
{
  #ifdef _CBLAS
    if ((t3!=t1)&&(t3!=t2))
      cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,4,4,4,1.0,(double*)t1,4,(double*)t2,4,0.0,(double*)t3,4);
    else
      {
	THTransform t4;
	
	cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,4,4,4,1.0,(double*)t1,4,(double*)t2,4,0.0,(double*)t4,4);
	MATRIX_INT_COPY(*t3,&t4);
      }
  #else
    THTransform t4;
    unsigned int i,j,k;

    for(i=0;i<(DIM_SP+1);i++)
      {
	for(j=0;j<(DIM_SP+1);j++)
	  {
	    t4[i][j]=0.0;
	    for(k=0;k<(DIM_SP+1);k++)
	      {
		t4[i][j]+=(*t1)[i][k]*(*t2)[k][j];
	      }
	  }
      }
    MATRIX_INT_COPY(*t3,&t4);
  #endif
}

/*
 * Makes the addition of two matrixes and returns it on t3.
 *                     t3=t1+t2
 * The procedure is safe enough and enables t3 no to be
 * different from t1 or t2.
 */
CBLAS_INLINE void HTransformAdd(THTransform *t1, /*First matrix*/
				THTransform *t2, /*Second matrix*/
				THTransform *t3  /*Resulting matrix*/
				)
{
  THTransform t4;
  #ifdef _CBLAS
    MATRIX_INT_COPY(&t4,t2);
    cblas_daxpy(16,1.0,(double*)t1,1,(double*)&t4,1);
  #else
    unsigned int i,j;

    for(i=0;i<(DIM_SP+1);i++)
      {
	for(j=0;j<(DIM_SP+1);j++)
	  {
	    t4[i][j]=(*t1)[i][j]+(*t2)[i][j];
	  }
      }
  #endif
  MATRIX_INT_COPY(*t3,&t4);
}

/*
 * Makes the substraction of two matrixes and returns it on t3.
 *                     t3=t1-t2
 * The procedure is safe enough and enables t3 no to be
 * different from t1 or t2.
 */
CBLAS_INLINE void HTransformSubstract(THTransform *t1, /*First matrix*/
				      THTransform *t2, /*Second matrix*/
				      THTransform *t3  /*Resulting matrix*/
				      )
{
  THTransform t4;
  #ifdef _CBLAS
    MATRIX_INT_COPY(&t4,t1);
    cblas_daxpy(16,-1.0,(double*)t2,1,(double*)&t4,1);
  #else
    unsigned int i,j;

    for(i=0;i<(DIM_SP+1);i++)
      {
	for(j=0;j<(DIM_SP+1);j++)
	  {
	    t4[i][j]=(*t1)[i][j]-(*t2)[i][j];
	  }
      }
  #endif
  MATRIX_INT_COPY(*t3,&t4);
}

/*
 * Invert t and returns the results on ti.
 * Description of the inversion method:
 *  t=t_trans*t_rot
 *  t^-1=t_rot^-1*t_trans^-1 
 *    t_rot^-1=t_rot transposed
 *    t_trans^-1=-t_trans
 */
void HTransformInverse(THTransform *t, /*Input matrix*/
		       THTransform *ti /*Resulting matrix (inverse of the input one)*/
		       )
{
  THTransform t_trans;
  THTransform t_rot;
  unsigned int i,j;

  MATRIX_INT_COPY(&t_trans,&matrix_identity);
  MATRIX_INT_COPY(&t_rot,&matrix_identity);

  /* invert the translation */
  t_trans[AXIS_X][AXIS_H]=-(*t)[AXIS_X][AXIS_H];
  t_trans[AXIS_Y][AXIS_H]=-(*t)[AXIS_Y][AXIS_H];
  t_trans[AXIS_Z][AXIS_H]=-(*t)[AXIS_Z][AXIS_H];
 
  /* invert (transpose) the rotation */
  for(i=0;i<AXIS_H;i++)
    {
      for(j=0;j<AXIS_H;j++)
	t_rot[i][j]=(*t)[j][i];
    }
 
  HTransformProduct(&t_rot,&t_trans,ti);
}

void HTransformOrthonormalize(THTransform *t,THTransform *ta)
{
  THTransform t_new;
  double c,n;
  unsigned int i;

  MATRIX_INT_COPY(&t_new,&matrix_identity);

  /*normalize the first vector*/
  n=0.0;
  for(i=0;i<3;i++)
    n+=((*t)[i][0]*(*t)[i][0]);
  n=sqrt(n);
  for(i=0;i<3;i++)
    t_new[i][0]=(*t)[i][0]/n;

  /*substract from the second vector, the projection of the 
    second vector onto the first one (i.e., keep an the part of the
    second vector that is orthononal to the first one). */
  c=0.0; /*cosinus between the two vectors*/
  for(i=0;i<3;i++)
    c+=(t_new[i][0]*(*t)[i][1]);
  for(i=0;i<3;i++)
    t_new[i][1]=(*t)[i][1]-c*t_new[i][0];

  /*normalize the second vector*/
  n=0.0;
  for(i=0;i<3;i++)
    n+=(t_new[i][1]*t_new[i][1]);
  n=sqrt(n);
  for(i=0;i<3;i++)
    t_new[i][1]=t_new[i][1]/n;

  /*The third vector is the cross product of the two first*/
  t_new[0][2]= t_new[1][0]*t_new[2][1]-t_new[1][1]*t_new[2][0];
  t_new[1][2]=-t_new[0][0]*t_new[2][1]+t_new[0][1]*t_new[2][0];
  t_new[2][2]= t_new[0][0]*t_new[1][1]-t_new[0][1]*t_new[1][0];

  /*The translation is just copied*/
  for(i=0;i<3;i++)
    t_new[i][AXIS_H]=(*t)[i][AXIS_H];

  MATRIX_INT_COPY(*ta,&t_new);
}

void HTransformX2Vect(double sy,double sz,double *p1,double *p2,THTransform *t)
{
  double x,y,z,l,theta,phi,h;
  THTransform s,r1,r2;
  
  x=p2[0]-p1[0];
  y=p2[1]-p1[1];
  z=p2[2]-p1[2]; 

  l=sqrt(x*x+y*y+z*z);

  if (l<1e-6)
    Error("Too small vector in HTransformX2Vect");

  h=sqrt(x*x+y*y);
  if (h<1e-3)
    {
      /* A vector along the z axis */
      theta=0;
      if (z>0)
	phi=-M_PI_2; /* -pi/2 */
      else
	phi= M_PI_2; /* +pi/2 */
    }
  else
    {
      theta=atan2(y,x); /*rotation in z*/
      phi=-atan2(z,h); /*rotation in y*/
    }

  /*Scale matrix*/
  HTransformIdentity(&s);
  HTransformSetElement(0,0,l,&s);
  HTransformSetElement(1,1,sy,&s);
  HTransformSetElement(2,2,sz,&s);
 
  /*Rotation around Y*/
  HTransformRy(phi,&r1);

  /*Rotation around Z*/
  HTransformRz(theta,&r2);

  /*translation to the origin*/
  HTransformTxyz(p1[0],p1[1],p1[2],t);

  /*accumulate the transform from last to first*/
  HTransformProduct(t,&r2,t);
  HTransformProduct(t,&r1,t);
  HTransformProduct(t,&s,t);
}

void HTransformYawPitchRoll(double a,double b,double c,THTransform *t)
{
  /*Rz(a)Ry(b)Rx(c)*/

  HTransformRz(a,t);
  HTransformAcumRot(RY,sin(b),cos(b),t);
  HTransformAcumRot(RX,sin(c),cos(c),t);
}

void GetYawPitchRoll(double *a,double *b,double *c,THTransform *t)
{
  double r11,r21,r31;

  /* Taken from http://planning.cs.uiuc.edu/node103.html */
  r11=(*t)[AXIS_X][AXIS_X];
  r21=(*t)[AXIS_Y][AXIS_X];
  r31=(*t)[AXIS_Z][AXIS_X];

  if ((r11==0.0)&&(r21==0.0))
    {
      double r12,r22;

      /* Treat the singular case. Several solutions
         are possible for this case. Just pick one. */
      r12=(*t)[AXIS_X][AXIS_Y];
      r22=(*t)[AXIS_Y][AXIS_Y];
  
      *c=0.0;
      *b=(r31>0?-M_PI_2:M_PI_2);
      *a=-atan2(r12,r22);
    }
  else
    {
      double r32,r33;
      
      r32=(*t)[AXIS_Z][AXIS_Y];
      r33=(*t)[AXIS_Z][AXIS_Z];
  
      *a=atan2(r21,r11);
      *b=atan2(-r31,sqrt(r32*r32+r33*r33));
      *c=atan2(r32,r33);
    }
}

/*
 * Returns in tt the transposed matrix of t.
*/
void HTransformTranspose(THTransform *t, /*Input matrix*/
			 THTransform *tt /*Resulting matrix (Transposed of the input one)*/
			 )
{
  THTransform t4;
  unsigned int i,j;
  
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	t4[i][j]=(*t)[j][i];
    }
  MATRIX_INT_COPY(*tt,&t4);
}

/*
 * Returns in t the result of multiplying t by a translation matrix with
 * parameters tx, ty, tz.
 *       t=t*HTransformTxyz(tx,ty,tz)
 *
 * Actually HTransformTxyz is not used and the product is done in a very efficient way.
 * This functions allows sequences of transformations to be concatened very fast.  
 */
CBLAS_INLINE void HTransformAcumTrans(double tx, /*Translation along the x axis*/
				      double ty, /*Translation along the y axis*/
				      double tz, /*Translation along the z axis*/
				      THTransform *t /*Input and resulting matrix after the accumulation of the translation*/
				      )
{
  unsigned int i;

  for(i=0;i<AXIS_H;i++)
    (*t)[i][AXIS_H]=(*t)[i][AXIS_X]*tx+(*t)[i][AXIS_Y]*ty+(*t)[i][AXIS_Z]*tz+(*t)[i][AXIS_H];
}

/*
 * The same as HTransformAcumTrans but with the input different from the output
 */
CBLAS_INLINE void HTransformAcumTrans2(THTransform *t_in, /*The input matrix*/
				       double tx,         /*Translation along the x axis*/
				       double ty,         /*Translation along the y axis*/
				       double tz,         /*Translation along the z axis*/
				       THTransform *t      /*Resulting matrix after the accumulation of the translation*/
				       )
{
  if (t!=t_in)
    MATRIX_INT_COPY(t,t_in);
  HTransformAcumTrans(tx,ty,tz,t);
}

/*
 * Returns in t the result of multiplying t by a rotations matrix for and angle
 * with sinus s and cosinus c around the axis indicated by the parameter type (RX,RY,RZ)
 *       t=t*HTransformCreate(type,atan2(s,c))
 */
CBLAS_INLINE void HTransformAcumRot(unsigned int type, /*Type of rotation matrix (RX,RY,RZ)*/
				    double s,          /*value of the sinus of the angle to be rotated*/
				    double c,          /*value of the cosinus of the angle to be rotated*/
				    THTransform *t     /*Input and resulting matrix after the accumulation of the translation*/
				    )
{
  unsigned int i;
  double aux;

  switch(type)
    {
    case RX:
      for(i=0;i<AXIS_H;i++)
	{
	  aux=(*t)[i][AXIS_Y];
	  (*t)[i][AXIS_Y]= aux*c+(*t)[i][AXIS_Z]*s;
	  (*t)[i][AXIS_Z]=-aux*s+(*t)[i][AXIS_Z]*c;
	}
      break;
    case RY:
      for(i=0;i<AXIS_H;i++)
	{
	  aux=(*t)[i][AXIS_X];
	  (*t)[i][AXIS_X]=aux*c-(*t)[i][AXIS_Z]*s;
	  (*t)[i][AXIS_Z]=aux*s+(*t)[i][AXIS_Z]*c;
	}
      break;
    case RZ:
      for(i=0;i<AXIS_H;i++)
	{
	  aux=(*t)[i][AXIS_X];
	  (*t)[i][AXIS_X]= aux*c+(*t)[i][AXIS_Y]*s;
	  (*t)[i][AXIS_Y]=-aux*s+(*t)[i][AXIS_Y]*c;
	}
      break;
    default:
      Error("Non rotation matrix type in function HTransformAcumRot");
      break;
    }
}
/*
 * The same as HTransformAcumRot but with the input different from the output
 */
CBLAS_INLINE void HTransformAcumRot2(THTransform *t_in, /*input matrix*/
				     unsigned int type, /*Type of rotation matrix (RX,RY,RZ)*/
				     double s,          /*value of the sinus of the angle to be rotated*/
				     double c,          /*value of the cosinus of the angle to be rotated*/
				     THTransform *t     /*Resulting matrix after the accumulation of the translation*/
				     )   
{  
  if (t!=t_in)
    MATRIX_INT_COPY(t,t_in); 
  HTransformAcumRot(type,s,c,t);
}

void HTransformApply(double *p_in,double *p_out,THTransform *t)
{
  unsigned int i,j;
  double pAux[3];
  
  for(i=0;i<DIM_SP;i++)
    {
      pAux[i]=(*t)[i][AXIS_H]; /*The homogeneous term*/

      for(j=0;j<DIM_SP;j++)
	pAux[i]+=((*t)[i][j]*p_in[j]);
    }
  
  p_out[0]=pAux[0];
  p_out[1]=pAux[1];
  p_out[2]=pAux[2];
}


CBLAS_INLINE void HTransformApplyRot(double *p_in,double *p_out,THTransform *t)
{

  #if _CBLAS
    if (p_out!=p_in) /* most requent case */
      {
	p_out[0]=cblas_ddot(3,&((*t)[0][0]),1,p_in,1);
	p_out[1]=cblas_ddot(3,&((*t)[1][0]),1,p_in,1);
	p_out[2]=cblas_ddot(3,&((*t)[2][0]),1,p_in,1);
      }
    else
      {
	double pAux[3];

	pAux[0]=cblas_ddot(3,&((*t)[0][0]),1,p_in,1);
	pAux[1]=cblas_ddot(3,&((*t)[1][0]),1,p_in,1);
	pAux[2]=cblas_ddot(3,&((*t)[2][0]),1,p_in,1);
      
	p_out[0]=pAux[0];
	p_out[1]=pAux[1];
	p_out[2]=pAux[2];
      }
  #else
    unsigned int i,j;
    double pAux[3];
    
    for(i=0;i<DIM_SP;i++)
      {
	pAux[i]=0.0; /*No homogeneous term*/
	
	for(j=0;j<DIM_SP;j++)
	  pAux[i]+=((*t)[i][j]*p_in[j]);
      }
  
    p_out[0]=pAux[0];
    p_out[1]=pAux[1];
    p_out[2]=pAux[2];
  #endif
}

/*
 * Prints matrix t on file f
 */
void HTransformPrint(FILE *f,   /*File*/
		     THTransform *t /*matrix to be printed*/
		     )
{
  unsigned int i,j;
  
  for(i=0;i<DIM_SP+1;i++)
    {
      for(j=0;j<(DIM_SP+1);j++)
	{
	  fprintf(f,"%.16f ",(*t)[i][j]);
	}
      fprintf(f,"\n");
    }
}

/*
 * Prints the transposed of matrix t on file f.
 * This is useful to print homogeneous transform in the Geomview way
 * Geomview uses row vectors. In this way what for column vectors
 * (the usual ones!) is
 *                A x 
 *  becomes
 *                (A x)^t= x^t A^t
 *  This is way we print A^t instead of A.
 */  
void HTransformPrintT(FILE *f,   /*File*/
		      THTransform *t /*matrix to be transposed and printed*/
		      )
{
  unsigned int i,j;
  
  for(i=0;i<(DIM_SP+1);i++)
    {
      for(j=0;j<DIM_SP+1;j++)
	{
	  fprintf(f,"%f ",(*t)[j][i]);
	}
    }
}

void HTransformPrettyPrint(FILE *f,THTransform *t)
{
  if (HTransformIsIdentity(t))
    fprintf(f,"ID");
  else
    {
      double x,y,z;
      boolean p=FALSE;

      x=(*t)[AXIS_X][AXIS_H];
      y=(*t)[AXIS_Y][AXIS_H];
      z=(*t)[AXIS_Z][AXIS_H];
      if ((x*x+y*y+z*z)>1e-6)
	{
	  fprintf(f,"Txyz(%g,%g,%g)",x,y,z);
	  p=TRUE;
	}
      if (!HTransformIsTranslation(t))
	{
	  double a,b,c;

	  GetYawPitchRoll(&a,&b,&c,t);
	  if (a!=0.0) { if (p) fprintf(f,"*"); fprintf(f,"Rz(%.16f)",a); p=TRUE;}
	  if (b!=0.0) { if (p) fprintf(f,"*"); fprintf(f,"Ry(%.16f)",b); p=TRUE;}
	  if (c!=0.0) { if (p) fprintf(f,"*"); fprintf(f,"Rx(%.16f)",c); }

	  //fprintf(f,"*Rz(%lf)*Ry(%lf)*Rx(%lf)",a,b,c);
	}
    }
}

/*
 * Deletes a matrix structure
 */
inline void HTransformDelete(THTransform *t /*HTransform to be deleted*/
	  	            )
{}
