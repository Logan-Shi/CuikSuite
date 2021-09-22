#ifndef HTRANSFORMH
#define HTRANSFORMH

#include "boolean.h"
#include "defines.h" /*for the DIM_SP,... constants*/

#include <stdio.h>

/** 
    \file htransform.h

    \brief Definition of the THTransform type and the associated functions.

    Module to manage homogeneous transforms in R^3 used to manipulated
    3D geometry.

    \sa htransform.c, THTransform, Tplot3d, plot3d.c.
*/

/************************************************************************************/
/** \brief  Dimensions of R^3.

    Dimensions of R^3.
        
    \sa THTransform
*/
#define DIM_SP 3

/** \brief  One of the types of homogeneous transforms in R^3.

    One of the types of homogeneous transforms in R^3: Translation along X.

    \sa THTransform
*/
#define TX 0

/** \brief  One of the types of homogeneous transforms in R^3.

    One of the types of homogeneous transforms in R^3: Translation along Y.

    \sa THTransform
*/
#define TY 1

/** \brief  One of the types of homogeneous transforms in R^3.

    One of the types of homogeneous transforms in R^3: Translation along Z.

    \sa Thtransform
*/
#define TZ 2

/** \brief  One of the types of homogeneous transforms in R^3.

    One of the types of homogeneous transforms in R^3: Rotation about X.

    \sa THTransform
*/
#define RX 3

/** \brief  One of the types of homogeneous transforms in R^3.

    One of the types of homogeneous transforms in R^3: Rotation about Y.

    \sa THTransform
*/
#define RY 4

/** \brief  One of the types of homogeneous transforms in R^3.

    One of the types of homogeneous transforms in R^3: Rotation about Z.

    \sa THTransform
*/
#define RZ 5

/** \brief  One of the dimension of R^3.

    One of the axis of R^3.

    \sa THTransform
*/
#define AXIS_X 0

/** \brief  One of the dimension of R^3.

    One of the axis of R^3.

    \sa THTransform
*/
#define AXIS_Y 1

/** \brief  One of the dimension of R^3.

    One of the axis of R^3.

    \sa THTransform
*/
#define AXIS_Z 2

/** \brief  The homogeneous dimension in R^3.

    The 4-th dimension used to represent rotations
    with a lineal mapping.

    \sa THTransform
*/
#define AXIS_H 3  
/************************************************************************************/

/** 
   \struct  THTransform
   \brief A homgeneous transform in R^3.

   A 4x4 matrix representing a homogenous matrix in R^3.

   \sa htransform.h, htransform.c
*/

/** 
   \brief A homgeneous transform in R^3.

   A 4x4 matrix typically representing a homogenous matrix in R^3.
   This is also used to represent generic 4x4 matrices sometimes. Therefor
   operations do not assume any structure in the matrix.

   \sa htransform.h, htransform.c
*/
typedef double THTransform[DIM_SP+1][DIM_SP+1];

/** 
   \brief Constructor.

   Initializes a homogeneous transform with the identity matrix.

   \param t The matrix to initialize.
*/
void HTransformIdentity(THTransform *t); 

/** 
   \brief Constructor.

   Initializes a homogeneous transform with the zero matrix.

   \param t The matrix to initialize.
*/
void HTransformZero(THTransform *t); 

/** 
   \brief Copy constructor.

   Initializes a homogeneous transform from another transform.

   \param t_dst The matrix to initialize.
   \param t_org The matrix from where to copy.
*/
void HTransformCopy(THTransform *t_dst,THTransform *t_org); 

/** 
   \brief Identify the identity matrix.

   Identifies identity matrix (up to a tiny error).

   \param t The matrix to check.

   \return TRUE if the given matrix is the identity.
*/
boolean HTransformIsIdentity(THTransform *t); 

/** 
   \brief Identify the zero matrix.

   Identifies the null matrix (up to a tiny error).

   \param t The matrix to check.

   \return TRUE if the given matrix is zero.
*/
boolean HTransformIsZero(THTransform *t);

/** 
   \brief Identify the translation matrices.

   Identifies translation matrices (up to a tiny error), i.e.,
   it does not include any rotation. It returns TRUE 
   also for the identity (no rotation and no translation).

   \param t The matrix to check.

   \return TRUE if the given matrix includes no rotation.
*/
boolean HTransformIsTranslation(THTransform *t);

/** 
   \brief Constructor.

   Initializes a homogeneous transform as a translation along \e X.

   \param tx The displacement along X.
   \param t The matrix to initialize.
*/
void HTransformTx(double tx,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a translation along \e Y.

   \param ty The displacement along Y.
   \param t The matrix to initialize. 
*/
void HTransformTy(double ty,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a translation along \e Z.

   \param tz The displacement along Z.
   \param t The matrix to initialize. 
*/
void HTransformTz(double tz,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a translation.

   \param tx The displacement along X.
   \param ty The displacement along Y.
   \param tz The displacement along Z.
   \param t The matrix to initialize. 
*/
void HTransformTxyz(double tx,double ty,double tz,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a rotation about X.

   \param rx The rotation about X in radiants.
   \param t The matrix to initialize. 
*/
void HTransformRx(double rx,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a rotation about Y.

   \param ry The rotation about Y in radiants.
   \param t The matrix to initialize. 
*/
void HTransformRy(double ry,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a rotation about Z.

   \param rz The rotation about Z in radiants.
   \param t The matrix to initialize. 
*/
void HTransformRz(double rz,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a rotation about X.

   \param s The cosinus of the rotation about X.
   \param c The sinus of the rotation about X.
   \param t The matrix to initialize. 
*/
void HTransformRx2(double s,double c,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a rotation about Y.

   \param s The cosinus of the rotation about Y.
   \param c The sinus of the rotation about Y.
   \param t The matrix to initialize. 
*/
void HTransformRy2(double s,double c,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a rotation about Z.

   \param s The cosinus of the rotation about Z.
   \param c The sinus of the rotation about Z.
   \param t The matrix to initialize. 
*/
void HTransformRz2(double s,double c,THTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a scale matrix.

   \param s The ccale factor.
   \param t The matrix to initialize. 
*/
void HTransformScale(double s,THTransform *t); 
		

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a scale matrix along the X axis.

   \param s The ccale factor.
   \param t The matrix to initialize. 
*/
void HTransformScaleX(double s,THTransform *t); 

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a scale matrix along the Y axis.

   \param s The ccale factor.
   \param t The matrix to initialize. 
*/
void HTransformScaleY(double s,THTransform *t); 

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a scale matrix along the Z axis.

   \param s The ccale factor.
   \param t The matrix to initialize. 
*/
void HTransformScaleZ(double s,THTransform *t); 
    
/** 
   \brief Constructor. 

   Initializes a homogeneous transform as translation/rotation in a
   given degree of freedom.

   \param dof_r3 The degree of freedom: TX, TY, TZ, RX, RY, RZ.
   \param v The translation or rotation (in radiants) for the selected
            degree of freedom.
   \param t The matrix to initialize. 
*/
void HTransformCreate(unsigned int dof_r3,double v,THTransform *t);


/** 
   \brief Sets an element in a homogeneous transform. 

   Sets an element in a homogeneous transform. Note that if the
   element value is not carefully computed the result of using
   this function could not be an homogeneous matrix anymore
   (recall that the 3x3 top left sub-matrix must be orthonormal).

   \param i Row of the element to set.
   \param j Column of the element to set.
   \param v The new value for the element
   \param t The matrix to update. 
*/
void HTransformSetElement(unsigned int i,unsigned int j,double v,THTransform *t);

/** 
   \brief Gets an element in a homogeneous transform. 

   Gets an element from a homogeneous transform.

   \param i Row of the element to get.
   \param j Column of the element to get.
   \param t The matrix to update. 

   \return The element at row \e i column \e j of homogeneous transform \e t.
*/
double HTransformGetElement(unsigned int i,unsigned int j,THTransform *t);

/** 
   \brief Defines a homogeneous transform from 4 vectors.

   Defines a homogeneous transform from 4 vectors defining its columns.
   No check is performed to verify if the rotation part (x,y,z columns) is
   actually a rotation matrix.

   \param x The 3 values for the first column.
   \param y The 3 values for the second column.
   \param z The 3 values for the third column.
   \param h The 3 values for the fourth (translation) column.
   \param t The transform to define.
*/
void HTransformFromVectors(double *x,double *y,double *z,double *h,THTransform *t);

/** 
   \brief Defines a GL column-major matrix from a homogeneous transform.

   Defines a homogeneous transform a la GL (colum-major) from our format
   of homogeneous transforms.

   \param m Space where to store the GL matrix.
   \param t The homogeneous transfrom.
*/
void HTransform2GLMatrix(double *m,THTransform *t);

/** 
   \brief Defines homogeneous transform from a GL  matrix.

   The reverse of \ref HTransform2GLMatrix.

   \param m Space from where to get the GL matrix.
   \param t The homogeneous transfrom to define.
*/
void HTransformFromGLMatrix(double *m,THTransform *t);
/** 
   \brief Product of two homogeneous transforms. 

   Product of two homogeneous transforms.

   \param t1 The first transform to operate.
   \param t2 The second transform to operate.
   \param t3 The result. 
*/
void HTransformProduct(THTransform *t1,THTransform *t2,THTransform *t3);

/** 
   \brief Addition of two homogeneous transforms. 

   Addition of two homogeneous transforms.

   \param t1 The first transform to operate.
   \param t2 The second transform to operate.
   \param t3 The result: t3=t1+t2. 
*/
void HTransformAdd(THTransform *t1,THTransform *t2,THTransform *t3);

/** 
   \brief Substraction of two homogeneous transforms. 

   Substraction of two homogeneous transforms.

   \param t1 The first transform to operate.
   \param t2 The second transform to operate.
   \param t3 The result: t3=t1-t2. 
*/
void HTransformSubstract(THTransform *t1,THTransform *t2,THTransform *t3);

/** 
   \brief Inverse of a homogeneous transform. 

   Addition of a homogeneous transform.

   \param t The transform to invert.
   \param ti The result transform with the inverse of the output. 
*/
void HTransformInverse(THTransform *t,THTransform *ti);

/** 
   \brief Orthonormalizes the rotation part of a homogenouos transform.

   Orthonormalizes the rotation part of a homogenouos transform. 

   This is to be used when we have an \e approximated homogeneous
   transform (for instance, a homogeneous transform that is derived after
   several floating point operations). If the rotation part is not orthonormal
   then the homogeneous transform is no longer a rigid transform (it produces
   deformations in the objects).

   Right now this is implemented in a simple way
   - The first (column) vector of the matrix is normalized.
   - We substract the projectio of the first vector from the second one
     and we normalize it.
   - The third vector is the cross product of the two first vectors.
   .

   An alternative implementation could be based in a SVD  of the rotation
   matrix: after the decomposition the diagonal matrix of (squared) eigenvalues is 
   set to the identity and the matrix is reconstucted. In this way we could
   avoid the bias of adjusting the matrix from the first column.

   \param t The transform to be orthonormalized
   \param ta The resulting transform with the rotation part orthonormalized.
*/
void HTransformOrthonormalize(THTransform *t,THTransform *ta);

/** 
   \brief Transform a unitary vector along the X axis to a generic vector.

   Computes the homogeneous matrix that transform a unitary vector along
   the X axis into a generic vector.

   The resulting transform includes, scaling, rotation and translation.

   This function is typically used when plotting cylinders. This is the reason
   to include scale factors in Y and Z (to deform the unitary cylinder along X
   with radii 1 so that we get the cylinder in the desired position and with
   the desired witdh, typically the same in Y and Z). The length is controlled
   by the start-end points of the cilynder.

   \param sy Scale factor to apply in the Y axes.
   \param sz Scale factor to apply in the Z axes.
   \param p1 Initial point of the vector.
   \param p2 Final point of the vector.
   \param t The resulting homogeneous transform.
*/
void HTransformX2Vect(double sy,double sz,
		      double *p1,double *p2,THTransform *t);

/** 
    \brief Defines a rotation matrix from the yaw, pitch, and roll parameters.

    Defines de rotation matrix resulting from

    R=Rz(a)Ry(b)Rx(c)

    This is the invers of \ref GetYawPitchRoll.

   \param a Yaw. Rotation around z. This is the last being applied.
   \param b Pitch. Rotation around y. This is the second being applied.
   \param c Roll. Rotation around x. This is the fisrt being applied.
   \param t The homogeneous transform with the rotation.    
*/
void HTransformYawPitchRoll(double a,double b,double c,THTransform *t);

/** 
   \brief Recovers the Euler angles from a rotation matrix.

   Recovers the Yaw, Pitch, and Roll angles from the rotation part of a homogeneous matrix,
   i.e., recovers the parameters such that

          Rz(a)Ry(b)Rx(c)=R

   with R the rotation part of the given transform. Note that in the expression

          Rz(a)Ry(b)Rx(c)

   we first apply the roll, then the pitch, and finally the yaw.

   The implementation uses the method taken from http://planning.cs.uiuc.edu/node103.html

   This is the inverse of \ref HTransformYawPitchRoll

   \param a Output. Yaw. Rotation around z.
   \param b Output. Pitch. Rotation around y.
   \param c Output. Roll. Rotation around x.
   \param t The homogeneous transform with the rotation.
*/
void GetYawPitchRoll(double *a,double *b,double *c,THTransform *t);

/** 
   \brief Transpose of a homogeneous transform. 
 
   Transpose of a homogeneous transform. Note that, in general the
   transpose of a homogeneous transform is not a homogeneous transform.

   \param t The transform to transpose.
   \param tt The result with the transposed matrix. 
*/
void HTransformTranspose(THTransform *t,THTransform *tt);

/** 
   \brief Computes the result of multiplying a homogeneous transform
          by a translation matrix with parameters tx, ty, tz.
	
    Computes the result of multiplying a homogeneous transform
    by a translation matrix with parameters tx, ty, tz. The result
    is accumulated in the given transform.

   \param tx The displacement along X.
   \param ty The displacement along Y.
   \param tz The displacement along Z.
   \param t The matrix where to accumulate the result of the product.

   \sa HTransformAcumTrans2 
*/
void HTransformAcumTrans(double tx,double ty,double tz,THTransform *t);


/** 
   \brief Computes the result of multiplying a homogeneous transform
          by a translation matrix with parameters tx, ty, tz.
	
    Computes the result of multiplying a homogeneous transform
    by a translation matrix with parameters tx, ty, tz. The result
    is accumulated in the given transform.

   \param t_in The base transform where to accumulate the translation.
   \param tx The displacement along X.
   \param ty The displacement along Y.
   \param tz The displacement along Z.
   \param t The matrix where to store the result. 

   \sa HTransformAcumTrans
*/
void HTransformAcumTrans2(THTransform *t_in,double tx,double ty,double tz,THTransform *t);

/** 
   \brief Computes the result of multiplying a homogeneous transform
          by a rotation matrix.

    Computes the result of multiplying a homogeneous transform
    by a rotation matrix. The result is accumulated in the given transform.

   \param type Type of rotation to accumulate: RX, RY, RZ.
   \param s sinus of the angle to rotate.
   \param c cosinus of the angle to rotate.
   \param t The matrix from where to depart and where to store the result. 

   \sa HTransformAcumRot2
*/
void HTransformAcumRot(unsigned int type,double s,double c,THTransform *t);

/** 
   \brief Computes the result of multiplying a homogeneous transform
          by a rotation matrix.

    Computes the result of multiplying a homogeneous transform
    by a rotation matrix.

    
   \param t_in The base transform where to accumulate the translation.
   \param type Type of rotation to accumulate: RX, RY, RZ.
   \param s sinus of the angle to rotate.
   \param c cosinus of the angle to rotate.
   \param t The matrix from where to store the result. 

   \sa HTransformAcumRot
*/
void HTransformAcumRot2(THTransform *t_in,unsigned int type,double s,double c,THTransform *t);

/** 
   \brief Multiply a homogeneous transform and a vector.

   Multiply a homogeneous transform and a vector.

   \param p_in A input vector in R^3.
   \param p_out The resulting vector in R^3.
   \param t The matrix to apply to the input vector. 
*/
void HTransformApply(double *p_in,double *p_out,THTransform *t);

/** 
   \brief Multiply the rotation part of the homogeneous transform and a vector.

   Applies the rotation encoded in a homogeneous transform to a vector (i.e., rotates
   the vector).

   \param p_in A input vector in R^3.
   \param p_out The resulting vector in R^3.
   \param t The matrix with the rotation to apply to the input vector. 
*/
void HTransformApplyRot(double *p_in,double *p_out,THTransform *t);

/** 
   \brief Prints the a homogeneous transform to a file.

   Prints the a homogeneous transform to a stream that can be \e stdtout.

   \param f The file where to print.
   \param t The matrix to print. 
*/
void HTransformPrint(FILE *f,THTransform *t);

/** 
   \brief Prints the transpose of a homogeneous transform to a file.

   Prints the transpose of a homogeneous transform to a stream that can be \e stdtout.
   This is implemented because computer graphics community use transposed
   homogeneous transforms and, consequently, this is how geomview requires the
   transforms to be printed.
   

   \param f The file where to print.
   \param t The matrix to print. 
   
   \sa plot3d.h
*/
void HTransformPrintT(FILE *f,THTransform *t);

/** 
   \brief Prints a homogenoeus transform compactly.

   Prints a homogenoeus transform compactly using basic
   transforms, whenever possible.

   \param f The file where to print.
   \param t The matrix to print. 
*/
void HTransformPrettyPrint(FILE *f,THTransform *t);

/** 
   \brief Destructor.

    Deletes the information stored in the THTransform and frees the allocated memory space.

   \param t The transform to delete.
*/
void HTransformDelete(THTransform *t);

#endif
