#ifndef SHTRANSFORMH
#define SHTRANSFORMH


#include "defines.h" /*for the DIM_SP,... constants*/
#include "htransform.h"
#include "equation.h"
#include "eqvector.h"

#include <stdio.h>

/** 
    \file shtransform.h

    \brief Definition of the TSHTransform type and the associated functions.

    Module to manage symbolic homogeneous transforms in R^3.

    \sa shtransform.c, TSHTransform, THTransform.
*/

/** 
   \struct  TSHTransform
   \brief A homgeneous transform in R^3.

   A 4x4 matrix representing a symbolic homogenous matrix in R^3.

   \sa shtransform.h, shtransform.c
*/

/** 
   \brief A symbolid homogeneous transform in R^3.

   A 4x4 matrix representing a homogenous matrix in R^3.

   \sa shtransform.h, shtransform.c
*/
typedef Tequation ***TSHTransform;

/** 
   \brief Constructor.

   Initializes a homogeneous transform with the identity matrix.

   \param t The matrix to initialize.
*/
void SHTransformIdentity(TSHTransform *t); 

/** 
   \brief Initializes a symbolic homogeneous transform from vectors.

   Initializes a symbolic homogeneous transform from 3D symbolic vectors.
   No test is done to check the orthonomality of the give vectors. The caller
   must take care of this.
   
   The third column of the matrix is computed as the cross product of x and y.

  \param x The first column of the symbolic transform.
  \param y The second column of the symbolic transform.
  \param d The fourth column of the symbolic transform.
  \param t The matrix to initialize.
*/
void SHTransformFromEqVectors(TEqVector *x,TEqVector *y,
			      TEqVector *d,TSHTransform *t); 

/** 
   \brief Copy constructor.

   Initializes a homogeneous transform from another transform.

   \param t_dst The matrix to initialize.
   \param t_org The matrix from where to copy.
*/
void SHTransformCopy(TSHTransform *t_dst,TSHTransform *t_org); 

/** 
   \brief Constructor.

   Initializes a symbolic homogeneous transform as a constant translation along \e X.

   \param tx The constant displacement along X.
   \param t The matrix to initialize.
*/
void SHTransformTx(double tx,TSHTransform *t);

/** 
   \brief Constructor.

   Initializes a homogeneous transform as a variable translation along \e X.

   \param x The variable displacement along X.
   \param t The matrix to initialize.
*/
void SHTransformVarTx(unsigned int x,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a symbolic homogeneous transform as a constant translation along \e Y.

   \param ty The displacement along Y.
   \param t The matrix to initialize. 
*/
void SHTransformTy(double ty,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a symbolic homogeneous transform as a variable translation along \e Y.

   \param y The variable displacement along Y.
   \param t The matrix to initialize. 
*/
void SHTransformVarTy(unsigned int y,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a constant translation along \e Z.

   \param tz The constant displacement along Z.
   \param t The matrix to initialize. 
*/
void SHTransformTz(double tz,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a variable translation along \e Z.

   \param z The variable displacement along Z.
   \param t The matrix to initialize. 
*/
void SHTransformVarTz(unsigned int z,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a constant translation.

   \param tx The constant displacement along X.
   \param ty The constant displacement along Y.
   \param tz The constant displacement along Z.
   \param t The matrix to initialize. 
*/
void SHTransformTxyz(double tx,double ty,double tz,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a variable translation.

   \param x The variable displacement along X.
   \param y The variable displacement along Y.
   \param z The variable displacement along Z.
   \param t The matrix to initialize. 
*/
void SHTransformVarTxyz(unsigned int x,unsigned int y,unsigned int z,TSHTransform *t);

/** 
   \brief Constructor.

   Initializes a homogeneous transform as a scaled variable translation.
   This is basically used define a scaled displacements along a given vector.

   \param v The vector with the scale factors. The vector definig the
            translation direction.
   \param vID The variable displacement along the vector.
   \param t The matrix to initialize. 
*/
void SHTransformVarDisplacementAlongVector(double *v,unsigned int vID,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a constant rotation about X.

   \param rx The constant rotation about X in radiants.
   \param t The matrix to initialize. 
*/
void SHTransformRx(double rx,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a constant rotation about X.

   \param x The variable rotation about X.
   \param t The matrix to initialize. 
*/
void SHTransformVarRx(unsigned int x,TSHTransform *t);

/**
   \brief Constructor. 

   Initializes a homogeneous transform as a constant rotation about Y.

   \param ry The constant rotation about Y in radiants.
   \param t The matrix to initialize. 
*/
void SHTransformRy(double ry,TSHTransform *t);

/**
   \brief Constructor. 

   Initializes a homogeneous transform as a constant rotation about Y.

   \param y The variable rotation about Y.
   \param t The matrix to initialize. 
*/
void SHTransformVarRy(unsigned int y,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a constant rotation about Z.

   \param rz The constant rotation about X in radiants.
   \param t The matrix to initialize. 
*/
void SHTransformRz(double rz,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as a constant rotation about Z.

   \param z The variable rotation about Z.
   \param t The matrix to initialize. 
*/
void SHTransformVarRz(unsigned int z,TSHTransform *t);


/** 
   \brief Constructor. 

   Initializes a homogeneous transform as xonstant translation/rotation in a
   given degree of freedom.

   \param dof_r3 The degree of freedom: TX, TY, TZ, RX, RY, RZ.
   \param v The constant translation or rotation (in radiants) for the selected
            degree of freedom.
   \param t The matrix to initialize. 
*/
void SHTransformCreate(unsigned int dof_r3,double v,TSHTransform *t);

/** 
   \brief Constructor. 

   Initializes a homogeneous transform as variable translation/rotation in a
   given degree of freedom.

   \param dof_r3 The degree of freedom: TX, TY, TZ, RX, RY, RZ.
   \param v The variable translation or rotation (in radiants) for the selected
            degree of freedom.
   \param t The matrix to initialize. 
*/
void SHTransformVarCreate(unsigned int dof_r3,unsigned int v,TSHTransform *t);

/** 
   \brief Gets an element in a homogeneous transform. 

   Gets an element from a homogeneous transform.

   \param i Row of the element to get.
   \param j Column of the element to get.
   \param t The matrix to update. 

   \return The element at row \e i column \e j of homogeneous transform \e t.
*/
Tequation *SHTransformGetElement(unsigned int i,unsigned int j,TSHTransform *t);

/** 
   \brief Product of two symbolic homogeneous transforms. 

   Product of two homogeneous transforms.

   \param t1 The first transform to operate.
   \param t2 The second transform to operate.
   \param t3 The result. 
*/
void SHTransformProduct(TSHTransform *t1,TSHTransform *t2,TSHTransform *t3);

/** 
   \brief Product of a constant and a symbolic homogeneous transforms. 

   Product of constnat and a symbolic homogeneous transforms.

   \param t1 The constant transform to operate.
   \param t2 The symbolic transform to operate.
   \param t3 The result. 
*/
void SHTransformPreCtProduct(THTransform *t1,TSHTransform *t2,TSHTransform *t3);

/** 
   \brief Product of a symbolic and a constant homogeneous transforms. 

   Product of a symbolic and a constant homogeneous transforms.

   \param t1 The symbolic transform to operate.
   \param t2 The constant transform to operate.
   \param t3 The result. 
*/
void SHTransformPostCtProduct(TSHTransform *t1,THTransform *t2,TSHTransform *t3);

/** 
   \brief Addition of two homogeneous transforms. 

   Addition of two homogeneous transforms.

   \param t1 The first transform to operate.
   \param t2 The second transform to operate.
   \param t3 The result. 
*/
void SHTransformAdd(TSHTransform *t1,TSHTransform *t2,TSHTransform *t3);

/** 
   \brief Inverse of a homogeneous transform. 

   Addition of a homogeneous transform.

   \param t The transform to invert.
   \param ti The result transform with the inverse of the output. 
*/
void SHTransformInverse(TSHTransform *t,TSHTransform *ti);

/**  
   \brief Transpose of a homogeneous transform. 
 
   Transpose of a homogeneous transform. Note that, in general the
   transpose of a homogeneous transform is not a homogeneous transform.

   \param t The transform to transpose.
   \param tt The result with the transposed matrix. 
*/
void SHTransformTranspose(TSHTransform *t,TSHTransform *tt);

/** 
   \brief Multiply a symbolic homogeneous transform and a vector.

   Multiply a symbolic homogeneous transform and a vector.

   \param p_in A input vector in R^3.
   \param p_out The resulting 3 equation vector.
   \param t The matrix to apply to the input vector. 
*/
void SHTransformApply(double *p_in,Tequation *p_out,TSHTransform *t);

/** 
   \brief Multiply the rotation part of the homogeneous transform and a vector.

   Applies the rotation encoded in a homogeneous transform to a vector (i.e., rotates
   the vector).

   \param p_in A input vector in R^3.
   \param p_out The resulting vector (3 equations).
   \param t The matrix with the rotation to apply to the input vector. 
*/
void SHTransformApplyRot(double *p_in,Tequation *p_out,TSHTransform *t);

/** 
   \brief Evaluates a symbolic homogeneous transform.

   Evaluates a symbolic homogeneus transform to produce a constant
   homogeneous transform.

   \param varValues Values for the variables involved in the symbolic
                    homogeneous transform.
   \param tc The output constant transform.
   \param t The input symbolic transform.
*/
void SHTransformEvaluate(double *varValues,THTransform *tc,TSHTransform *t);

/** 
   \brief Prints the a homogeneous transform to a file.

   Prints the a homogeneous transform to a stream that can be \e stdtout.

   \param f The file where to print.
   \param varNames Name of the variables involved int the symbolic transform.
                   Can be NULL and then generic names are used.
   \param t The matrix to print. 
*/
void SHTransformPrint(FILE *f,char **varNames,TSHTransform *t);

/** 
   \brief Destructor.

    Deletes the information stored in the TSHTransform and frees the allocated memory space.

   \param t The transform to delete.
*/
void SHTransformDelete(TSHTransform *t);

#endif
