#ifndef SAH
#define SAH


#include "basic_algebra.h"
#include "htransform.h"

/** 
   \file sa.h

   \brief Spatial algebra.

   Implementation of some basic fuctions of the spatial algebra by Featherstone.

   This is used to define the mass matrix and the action vectors necessary
   to determine the accelerations.

   Spatial algebra uses 6x6 matrices and 6-dimensional vectors. They are all
   implemented using the basic types in the basic algebra module (and, thus
   matrices can be row major or column major depending on the underlying
   numerical library used).
*/

/** 
   \brief Copy of spatial algebra vectors.

   Copy of spatial algebra vectors.

   \param sav_dst Vector where to copy.
   \param sav_src Vector from where to copy.
*/
void copySAV(double *sav_dst,double *sav_src);

/** 
   \brief Copy of spatial algebra matrices.

   Copy of spatial algebra matrices.

   \param sam_dst Vector where to copy.
   \param sam_src Vector from where to copy.
*/
void copySAM(double *sam_dst,double *sam_src);

/** 
   \brief Identity matrix.

   Identity transform in the form of a spatial algebra matrix.

   \param sam The matrix where to store the identity.
*/
void IdentitySAM(double *sam);

/** 
   \brief Spatial algebra rigid transform

   Defines a spatial algebra rigid transform form an
   homogeneous transform.

   \param t The homogeneous transform.
   \param sam The resulting spatial algebra matrix.
*/
void HTransform2SAM(THTransform *t,double *sam);

/** 
   \brief Extracts and homogeneous transform from a spatial algebra matrix.

   Defines the homogenous transform encoded in a spatial algebra matrix.
   The reverse of \ref HTransform2SAM.

   \param t The transform to define.
   \param sam The spatial algebra matrix from where to take the values.
*/
void SAM2HTransform(THTransform *t,double *sam);

/** 
   \brief Spatial algebra rigid translation.
   
   Defines a spatial algebra rigid translations from a translation vector.

   \param t The 3D vector specifying the translation.
   \param sam The resulting spatial algebra matrix.
*/
void Translation2SAM(double *t,double *sam);

/** 
    \brief Applies an homogeneous transform to a spatial algebra vector.

    Implements sav2=SAMxSAV(HTransform2SAM(t),sav1), that is, the product
    of a spatial algebra matrix comming from an homogeneous transform and
    a spatial algebra vector, but without explicitly defining the spatial
    algebra matrix. In principle this should be more efficient (we save
    the htransform to spatial matrix computation and the product skips
    the use of the zero block that appears in any spatial algebre matrix).

    \param t The homogeneous transform.
    \param n Number of vectors
    \param sav1 The input (spatial algebra) vectors. This is taken as a matrix
                of size 6xn.
    \param sav2 The output (spatial algebra) vectors. This is taken as a matrix
                of size 6xn.
*/
void HTransformXSAV(THTransform *t,unsigned int n,double *sav1,double *sav2);

/** 
   \brief Inverse of a spatial algebra matrix representing a transform.

   Computes the inverse of a spatial algebra matrix representing a transform.

   \param sam The matrix to invert.
   \param isam The inverse matrix.
*/
void SAMinverse(double *sam,double *isam);

/** 
   \brief Spatial algebra skew matrix.

   Defines the equivalent of a skew matrix in spatial algebra.
   
   \param sav The vector.
   \param sam The resulting spatial algebra matrix.
*/
void crm(double *sav,double *sam);

/** 
   \brief CRM times a vector.

   Implements sav2=SAMxSAV(crm(sav),sav1), i.e., the product
   of a matrix resulting from calling \ref crm and a vector, but
   without explicitly defining the matrix.

   \param sav The vector defining the \ref crm matrix.
   \param sav1 The vector to operate with the matrix.
   \param sav2 The output vector.
*/
void CRMxSAV(double *sav,double *sav1,double *sav2);

/** 
   \brief Spatial algebra skew matrix in force space.

   Defines the equivalent of a force skew matrix in spatial algebra.
   This is basically the transposed of \ref crm
   
   \param sav The vector.
   \param sam The resulting spatial algebra matrix.
*/
void crf(double *sav,double *sam);

/** 
   \brief CRF times a matrix.

   Implements sam2=SAMxSAM(crf(sav),sam1), i.e., the product
   of a matrix resulting from calling \ref crm and a matrix, but
   without explicitly defining the \ref crf matrix.

   \param sav The vector defining the \ref crf matrix.
   \param sam1 The matrix to operate with the matrix.
   \param sam2 The matrix vector.
*/
void CRFxSAM(double *sav,double *sam1,double *sam2);

/** 
   \brief Scales a spatial algebra vector.

   Scales a spatial algebra vector.
   
   \param s Scale factor.
   \param sav The scaled spatial algebra vector.
*/
void scaleSAV(double s,double *sav);

/** 
   \brief Scales a spatial algebra matrix.

   Scales a spatial algebra matrix.
   
   \param s Scale factor.
   \param sam The input/scaled spatial algebra matrix.
*/
void scaleSAM(double s,double *sam);

/** 
   \brief Accumulates spatial algebra vectors.

   Accumulates two spatial algebra vectors: sav2=sav1+sav2.
   
   \param sav1 The vector to accumulate on sav2.
   \param sav2 The vector to where to sum sav1.
*/
void accumSAV(double *sav1,double *sav2);

/** 
   \brief Sums spatial algebra vectors.

   Sums two spatial algebra vectors.
   
   \param sav1 The first vector to sum.
   \param sav2 The second vector to sum.
   \param sav3 The resulting spatial algebra vector.
*/
void sumSAV(double *sav1,double *sav2,double *sav3);

/** 
   \brief Accumulates spatial algebra matrices.

   Accumulates two spatial algebra matries: sam2=sam1+sam2.
   
   \param sam1 The vector to accumulate on sam2.
   \param sam2 The vector to where to sum sam1.
*/
void accumSAM(double *sam1,double *sam2);

/** 
   \brief Sums spatial algebra matrices.

   Sums two spatial algebra matrices.
   
   \param sam1 The first matrix to sum.
   \param sam2 The second matrix to sum.
   \param sam3 The resulting spatial algebra matrix.
*/
void sumSAM(double *sam1,double *sam2,double *sam3);

/** 
   \brief Matrix vector product
    
   Product of a spatial algebra matrix and vector.

   \param sam Spatial algebra matrix.
   \param sav1 Spatial algebra vector to multiply.
   \param sav2 Resulting spatial algebra vector.
*/
void SAMxSAV(double *sam,double *sav1,double *sav2);

/** 
   \brief Accumulates a matrix vector product
   
   Accumulates a product of a spatial algebra matrix and vector.

   \param sam Spatial algebra matrix.
   \param sav1 Spatial algebra vector to multiply.
   \param sav2 Resulting spatial algebra vector: sav2 = sav2 + sam * sav1
*/
void SAMxSAVAccum(double *sam,double *sav1,double *sav2);

/** 
   \brief Accumulates a transposed matrix vector product
   
   Accumulates a transposed product of a spatial algebra matrix and vector.

   \param sam Spatial algebra matrix (without transposing).
   \param sav1 Spatial algebra vector to multiply.
   \param sav2 Resulting spatial algebra vector: sav2 = sav2 + sam^t * sav1
*/
void TSAMxSAVAccum(double *sam,double *sav1,double *sav2);

/** 
   \brief Matrix matrix product
    
   Product of two spatial algebra matrices.

   \param sam1 Spatial algebra matrix.
   \param sam2 Spatial algebra matrix to multiply.
   \param sam3 Resulting spatial algebra matrix.
*/
void SAMxSAM(double *sam1,double *sam2,double *sam3);

/** 
   \brief Accumulates a matrix matrix product
    
   Accumulates a product of two spatial algebra matrices.

   \param sam1 Spatial algebra matrix.
   \param sam2 Spatial algebra matrix to multiply.
   \param sam3 Resulting spatial algebra matrix: sam3 = sam3 + sam1 * sam2
*/
void SAMxSAMAccum(double *sam1,double *sam2,double *sam3);

/** 
   \brief Transposed matrix matrix product
    
   Product of two spatial algebra matrices. The first one is
   transposed before the product.

   \param sam1 Spatial algebra matrix.
   \param sam2 Spatial algebra matrix to multiply.
   \param sam3 Resulting spatial algebra matrix.
*/
void TSAMxSAM(double *sam1,double *sam2,double *sam3);

/** 
   \brief Transposed matrix vector product.

   Product of a trnasposed algebra matrix and a vector.
   
   \param sam Spatial algebra matrix (to be transosed and multiplied).
   \param sav1 Spatial algebra vector to be multiplied.
   \param sav2 Resulting spatial algebra vector.
*/
void TSAMxSAV(double *sam,double *sav1,double *sav2);

/** 
   \brief Transposed vector matrix product.

   Product of a spatial algebra transposed vector and a matrix.
   
   \param sav1 Spatial algebra vector (to be transosed and multiplied).
   \param sam Spatial algebra matrix to be multiplied.
   \param sav2 Resulting spatial algebra vector.
*/
void TSAVxSAM(double *sav1,double *sam,double *sav2);

/** 
   \brief Dot product between to spatial algebra vectors.

   Dot product between to spatial algebra vectors.

   \param sav1 The first vector.
   \param sav2 The second vector.

   \return The product.
*/
double SAVxSAV(double *sav1,double *sav2);

/** 
   \brief Rigid body inertia matrix.

   Defines a spatial algebra rigid body inertia matrix.

   \param m The mass [input].
   \param c Position of the center of mass from the point [input].
            where we define the rigid body inertia matrix
	    (i.e., the predecesor joint) [input].
    \param IM Rotational inertial about the center of mass [input].
    \param saI The defined spatial algebra inertia matrix [output].
*/
void mci2rbi(double m,double *c,double *IM,double *saI);

/** 
   \brief Inverse of mci2rbi.

   Gets the mass, center of gravity and rotational inertia
   from a spatial algebra rigid body inertia matrix.

   \param saI The spatial algebra inertia matrix [input].
   \param m The mass [output].
   \param c Position of the center of mass from the point
            where we define the rigid body inertia matrix
	    (i.e., the predecesor joint). Can be NULL
	    if not required [output].
   \param IM Rotational inertial about the center of mass 
            Can be NUll if not required [output].
*/
void rbi2mci(double *saI,double *m,double *c,double *IM);


#endif
