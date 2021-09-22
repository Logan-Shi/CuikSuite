#ifndef BASICALGEBRAH

/** \file basic_algebra.h

    Header of the basic lineal algebra routines used in the CuikSuite.

    These are the routines that can be implemented using BLAS:
    vector and matrix manipulations (sums, differences, norms, products, etc).

    More complex operations (matrix decompositions, etc) are implemented in
    algebra.c and might use different libraries (gls, eigen, etc).

    \sa basic_algebra.c algebra.c
*/

#include "defines.h"
#include "boolean.h"

#include <stdio.h>

#if !defined(_LAPACK) && !defined(_GSL)
  #error "CuikSuite requires LAPACK or GSL (LAPACK preferred)"
#endif

#ifdef _CBLAS
  // #ifdef _GSL_CBLAS
  //   /* Use the CBLAS included in the GSL */
    #include <gsl/gsl_cblas.h>
  // #else
  //   /* Use the system CBLAS */
  //   #include <cblas.h>
  // #endif

  /** 
     \brief Inline BLAS-based functions.

     When using BLAS we inline the trivial numerical functions to
     gain some efficiency.
  */
  #define CBLAS_INLINE inline
#else
  /** 
     \brief Inline BLAS-based functions.

     When using BLAS we inline the trivial numerical functions to
     gain some efficiency.
  */
  #define CBLAS_INLINE
#endif

#ifdef _GSL
  /** \brief How matrices are stored in vectors

     Set this to 1 if matrices are stored in vectors in
     row major mode (row by row). If 0, column major mode
     is assumed.
  */
  #define ROW_MAJOR 1
#endif

#ifdef _LAPACK
  /** \brief How matrices are stored in vectors

     Set this to 1 if matrices are stored in vectors in
     row major mode (row by row). If 0, column major mode
     is assumed.
  */
  #define ROW_MAJOR 0
#endif

/** 
    \brief Index in a vector of a matrix element.

    Derermines the index in a vector of a given matrix element.

    \param i Row index.
    \param j Column index.
    \param nr Numer of rows of the matrix.
    \param nc Number of columns of the matrix.
*/
#define RC2INDEX(i,j,nr,nc) (ROW_MAJOR?(i)*(nc)+(j):(j)*(nr)+(i))



/*******************************************************************************/
/* The functions below have a naif implementation and a more efficient one     */
/* based on blas                                                               */

/** 
   \brief Set a vector to zero.

   Sets a vector to 0.

   \param n The size of the vector.
   \param v The vector.
*/
void ClearVector(unsigned int n,double *v);

/** 
   \brief And of two vectors.

   Generates a vector with the 'and' of two vectors of flags.

   \param s Size of the vectors.
   \param v1 The first vector to operate.
   \param v2 The second vector to operate.
   \param vo The output vector (and of v1, v2).
*/
void VectorAnd(unsigned int s,boolean *v1,boolean *v2,boolean *vo);

/** 
   \brief Or of two vectors.

   Generates a vector with the 'or' of two vectors of flags.

   \param s Size of the vectors.
   \param v1 The first vector to operate.
   \param v2 The second vector to operate.
   \param vo The output vector (or of v1, v2).
*/
void VectorOr(unsigned int s,boolean *v1,boolean *v2,boolean *vo);

/** 
   \brief Computes the dot product of two general vectors.

   Computes the dot product of two general vectors.

   \param s The dimensionality of the vectors.
   \param v1 First vector.
   \param v2 Second vector.

   \return The dot produt.
*/
double GeneralDotProduct(unsigned int s,double *v1,double *v2);

/** 
   \brief Computes the weighted dot product of two general vectors.

   Computes weighted the dot product of two general vectors.

   \param s The dimensionality of the vectors.
   \param W The matrix of weights.
   \param v1 First vector.
   \param v2 Second vector.

   \return The dot produt.
*/
double MatrixWeigthedDotProduct(unsigned int s,double *W,double *v1,double *v2);

/** 
   \brief Scales a vector.

   Multiplies all the elements of a vector by a given factor.

   \param f The factor.
   \param s Number of elements in the vector.
   \param v The vector.
*/
void ScaleVector(double f,unsigned int s,double *v);

/** 
   \brief Scales a vector.

   Multiplies all the elements of a vector by a given factor and
   stores the result in a new vector.

   \param f The factor.
   \param s Number of elements in the vector.
   \param v The vector.
   \param vout The output vector.
*/
void ScaleVector2(double f,unsigned int s,double *v,double *vout);

/** 
   \brief Offsets a vector.

   Adds a constant to all the elements of a vector.

   \param o The constant (or offset) to add.
   \param s The size of the vector.
   \param v The vector.
*/
void OffsetVector(double o,unsigned int s,double *v);

/** 
   \brief Adds a vector to another vectors.

   Adds a vector to another vector

   \param s Number of elements in the vector.
   \param v1 The vector to add.
   \param v2 The vector where to add v1.
*/
void AccumulateVector(unsigned int s,double *v1,double *v2);

/** 
   \brief Adds two vectors.

   Adds two vectors and stores the result in another vector..

   \param s Number of elements in the vector.
   \param v1 The first vector to add.
   \param v2 The second vector to add.
   \param v The vector where to store the result.
*/
void SumVector(unsigned int s,double *v1,double *v2,double *v);

/** 
   \brief Adds two vectors with a scale.

   Adds two vectors /scaling the second vector) and stores the result in another vector..
   This is basically used in Gram-Smidth orthogonalization.

   \param s Number of elements in the vector.
   \param v1 The first vector to add.
   \param w The weight to scale the second vector.
   \param v2 The second vector to scale and add.
   \param v The vector where to store the result.
*/
void SumVectorScale(unsigned int s,double *v1,double w,double *v2,double *v);

/** 
   \brief Cosine on a vector.

   Compputes the cosine for all the elements of a vector.

   \param s Number of elements in the vector.
   \param v The vector.
   \param co The vector with the cosines (output, allocated externally).
*/
void CosVector(unsigned int s,double *v,double *co);

/** 
   \brief Sine on a vector.

   Compputes the sine for all the elements of a vector.

   \param s Number of elements in the vector.
   \param v The vector.
   \param si The vector with the sine (output, allocated externally).
*/
void SinVector(unsigned int s,double *v,double *si);

/** 
   \brief Adds the elements of a vector.

   Adds all the elements of a vector.

   \param m The size of the vector.
   \param v The vector.

   \return The sum of the elements of the vector.
*/
double AddVectorElements(unsigned int m,double *v);

/** 
   \brief Adds the positive elements of a vector.

   Adds all the positive elements of a vector.

   \param m The size of the vector.
   \param v The vector.

   \return The sum of the positive elements of the vector.
*/
double AddVectorPositiveElements(unsigned int m,double *v);

/** 
   \brief Index of the maximum element of a vector.

   Returns the index of the maximum element in the given vector.

   \param m The size of the vector.
   \param v The vector.

   \return The index for the maximum element or \ref NO_UINT if the vector
           is empty.
*/
unsigned int MaxVectorElement(unsigned int m,double *v);

/** 
   \brief Value of the maximum element of a vector.

   Returns the value of the maximum element in the given vector.

   \param m The size of the vector.
   \param v The vector.

   \return The value for the maximum element or 0 if the vector
           is empty.
*/
double MaxVector(unsigned int m,double *v);

/** 
   \brief Index of the minimum element of a vector.

   Returns the index of the minimum element in the given vector.

   \param m The size of the vector.
   \param v The vector.

   \return The index for the minimum element or \ref NO_UINT if the vector
           is empty.
*/
unsigned int MinVectorElement(unsigned int m,double *v);

/** 
   \brief Value of the minimum element of a vector.

   Returns the value of the minimum element in the given vector.

   \param m The size of the vector.
   \param v The vector.

   \return The value for the minimum element or 0 if the vector
           is empty.
*/
double MinVector(unsigned int m,double *v);

/** 
   \brief Scales a vector to a given range.

   Scales a vector so that their values span a given
   range.

   \param l The lower value of the range.
   \param u The upper value of the range.
   \param mode Exponential used in the transform.
               If positive we increase the resolution
	       in the upper levels. If negative,
	       the difference in lower levels are more
	       remarked.
   \param m The size of the vector.
   \param v The vector.
*/
void Vector2Range(double l,double u,double mode,
		  unsigned int m,double *v);

/** 
   \brief Subtracts a vector from another vector.

   Subtracts a vector from another vector: v1=v1-v2

   \param s Number of elements in the vector.
   \param v1 The vector from where to subtract.
   \param v2 The vector to subtract.
*/
void SubtractVector(unsigned int s,double *v1,double *v2);

/** 
   \brief Subtracts two vectors.

   Subtracts two vectors and stores the result in another vector: v=v1-v2

   \param s Number of elements in the vector.
   \param v1 The vector from where to subtract.
   \param v2 The vector to subtract.
   \param v The vector where to store the result.
*/
void DifferenceVector(unsigned int s,double *v1,double *v2,double *v);

/** 
   \brief Subtracts two vectors along some of its components.

   Subtracts two vectors and stores the result in another vector: v=v1-v2
   Only the selected components are operated. The rest are set to 0.

   \param s Number of elements in the vector.
   \param subset The selected components.
   \param v1 The vector from where to subtract.
   \param v2 The vector to subtract.
   \param v The vector where to store the result.
*/
void DifferenceVectorSubset(unsigned int s,
			    boolean *subset,
			    double *v1,double *v2,double *v);
/** 
   \brief Subtracts two vectors.

   Subtracts two vectors and stores the result in another vector
   considering the topology for each component.

   \param s Number of elements in the vector.
   \param tp The topology for each variable.
   \param v1 The vector from where to subtract.
   \param v2 The vector to subtract.
   \param v The vector where to store the result.
*/
void DifferenceVectorTopology(unsigned int s,unsigned int *tp,
			      double *v1,double *v2,double *v);

/** 
   \brief Subtracts two vectors along some of its components.

   Subtracts two vectors and stores the result in another vector
   considering the topology for the selected components.

   The output for the non-selected components are set to 0.

   \param s Number of elements in the vector.
   \param tp The topology for each variable. If NULL this
             function is the same as \ref DifferenceVector.
   \param subset The selected dimensions. If NULL this function
                 is the same as \ref DifferenceVectorTopology.
   \param v1 The vector from where to subtract.
   \param v2 The vector to subtract.
   \param v The vector where to store the result.
*/
void DifferenceVectorTopologySubset(unsigned int s,unsigned int *tp,
				    boolean *subset,
				    double *v1,double *v2,double *v);

/** 
   \brief Computes the norm of a vector.

   Computes the norm of a vector with the given size.

   \param s Number of elements in the vector.
   \param v The vector.

   \return The norm of the vector.
*/
double Norm(unsigned int s,double *v);

/** 
   \brief Computes the weighted norm of a vector.

   Computes the weighted norm of a vector with the given size.

   \param s Number of elements in the vector.
   \param w The weigths.
   \param v The vector.

   \return The weighted norm of the vector.
*/
double WeightedNorm(unsigned int s,double *w,double *v);

/** 
   \brief Computes the weighted norm of a vector.

   The same as \ref WeightedNorm but here the weights is given
   in the form of a matrix. Thus, were we compute v^T*W*v.

   \param s Number of elements in the vector.
   \param W The (symmetric) matrix of weigths.
   \param v The vector.

   \return The weighted norm of the vector.
*/
double MatrixWeightedNorm(unsigned int s,double *W,double *v);
  
/** 
   \brief Computes the norm of a vector.

   Computes the norm of a vector with the given size and
   whose elements might not be continuous in memory but
   separated by a given stride.

   \param s Number of elements in the vector.
   \param st The stride (separation between elements of v).
   \param v The vector.

   \return The norm of the vector.
*/
double NormWithStride(unsigned int s,unsigned int st,double *v);

/** 
   \brief Computes the squared distance of two points.

   Computes the distance between two points given as a vector
   with a given size.

   \param s Number of elements in the vectors.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double SquaredDistance(unsigned int s,double *v1,double *v2);

/** 
   \brief Computes the weighted squared distance of two points.

   Computes the weighted distance between two points given as a vector
   with a given size.

   \param s Number of elements in the vectors.
   \param w Weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The weighted distance between the points.
*/
double WeightedSquaredDistance(unsigned int s,double *w,double *v1,double *v2);

/** 
   \brief Computes the weighted squared distance of two points.

   The same as \ref WeightedSquaredDistance, but the weights are given in the
   form of a matrix. Thus, we compute (v2-v1)^t * W * (v2-v1).
   \ref WeightedSquaredDistance can be seen as a particular case of
   this function where matrix \e W is diagonal. 

   \param s Number of elements in the vectors.
   \param W Weight in the form of a (symmetric) matrix.
   \param v1 The first point.
   \param v2 The second point.

   \return The weighted distance between the points.
*/
double MatrixWeightedSquaredDistance(unsigned int s,double *W,double *v1,double *v2);

/** 
   \brief Computes the squared distance of two points along selected dimensions.

   Computes the distance between two points given as a vector
   with a given size along some of its components.

   \param s Number of elements in the vectors.
   \param subset The selected components.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double SquaredDistanceSubset(unsigned int s,boolean *subset,
			     double *v1,double *v2);

/** 
   \brief Computes the weighted squared distance of two points along selected dimensions.

   Computes the weighted distance between two points given as a vector
   with a given size along some of its components.

   \param s Number of elements in the vectors.
   \param subset The selected components.
   \param w Weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double WeightedSquaredDistanceSubset(unsigned int s,boolean *subset,double *w,double *v1,double *v2);

/** 
   \brief Computes the weighted squared distance of two points along selected dimensions.

   Computes the weighted distance between two points given as a vector
   with a given size along some of its components.

   \param s Number of elements in the vectors.
   \param subset The selected components.
   \param W The (symmetric) matrix of weights. This is of the size of the vectors but only the 
            selected rows/colums are used.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double MatrixWeightedSquaredDistanceSubset(unsigned int s,boolean *subset,double *W,double *v1,double *v2);

/** 
   \brief Computes the distance of two points.

   Computes the distance between two points given as a vector
   with a given size.

   \param s Number of elements in the vectors.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double Distance(unsigned int s,double *v1,double *v2);

/** 
   \brief Computes the weighted distance of two points.

   Computes the weighted distance between two points given as a vector
   with a given size.

   \param s Number of elements in the vectors.
   \param w Weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double WeightedDistance(unsigned int s,double *w,double *v1,double *v2);

/** 
   \brief Computes the weighted distance of two points.

   The same as \ref WeightedDistance but the weights are given in matrix form.
   Thus, the computation is: (v2-v1)^t * W * (v2-v1)

   \param s Number of elements in the vectors.
   \param W The (symmetric) matrix of weight.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double MatrixWeightedDistance(unsigned int s,double *W,double *v1,double *v2);

/** 
   \brief Computes the squared distance of two points.

   Computes the squared distance between two points given as a vector
   with a given size and considering the topology for each
   dimension.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The squared distance between the points.
*/
double SquaredDistanceTopology(unsigned int s,unsigned int *tp,double *v1,double *v2);

/** 
   \brief Computes the squared distance of two points.

   Computes the squared distance between two points given as a vector
   with a given size and considering the topology for each
   dimension.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param w Weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The squared distance between the points.
*/
double WeightedSquaredDistanceTopology(unsigned int s,unsigned int *tp,double *w,double *v1,double *v2);

/** 
   \brief Computes the squared distance of two points.

   Computes the squared distance between two points given as a vector
   with a given size and considering the topology for each
   dimension.

   The squared distance is only fully computed for points closer than
   a given threshold. This accelerates the distance computations.

   \param t2 The threshold (a square distance!).
   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The squared distance between the points.
*/
double SquaredDistanceTopologyMin(double t2,unsigned int s,unsigned int *tp,
				  double *v1,double *v2);


/** 
   \brief Computes the squared distance of two points.

   Computes the squared distance between two points given as a vector
   with a given size and considering the topology for each
   dimension.

   The squared distance is only fully computed for points closer than
   a given threshold. This accelerates the distance computations.

   \param t2 The threshold (a square distance!).
   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param w Weight in each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The squared distance between the points.
*/
double WeightedSquaredDistanceTopologyMin(double t2,unsigned int s,unsigned int *tp,double *w,
					  double *v1,double *v2);

/** 
   \brief Computes the distance of two points.

   Computes the distance between two points given as a vector
   with a given size and considering the topology for each
   components.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double DistanceTopology(unsigned int s,unsigned int *tp,
			double *v1,double *v2);

/** 
   \brief Computes the distance of two points.

   Computes the distance between two points given as a vector
   with a given size and considering the topology for each
   components.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param w Weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double WeightedDistanceTopology(unsigned int s,unsigned int *tp,double *w,
				double *v1,double *v2);

/** 
   \brief Computes the square distance of two points along a subset of components.

   Computes the squared distance between two points given as a vector
   with a given size and considering the topology for the selected
   components.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param subset The components to use in the distance computation.
                 If NULL, this function is the same as
		 \ref SquaredDistanceTopology.
   \param v1 The first point.
   \param v2 The second point.

   \return The squared distance between the points in the selected dimensions.
*/
double SquaredDistanceTopologySubset(unsigned int s,unsigned int *tp,
				     boolean *subset,
				     double *v1,double *v2);

/** 
   \brief Computes the square distance of two points along a subset of components.

   Computes the squared weighted distance between two points given as a vector
   with a given size and considering the topology for the selected
   components.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param subset The components to use in the distance computation.
                 If NULL, this function is the same as
		 \ref SquaredDistanceTopology.
   \param w The weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The squared weighted distance between the points in the selected dimensions.
*/
double WeightedSquaredDistanceTopologySubset(unsigned int s,unsigned int *tp,
					     boolean *subset,double *w,
					     double *v1,double *v2);

/** 
   \brief Computes the distance of two points along a subset of components.

   Computes the distance between two points given as a vector
   with a given size and considering the topology for the selected
   components.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param subset The components to use in the distance computation.
                 If NULL, this function is the same as
		 \ref DistanceTopology.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points in the selected dimensions.
*/
double DistanceTopologySubset(unsigned int s,unsigned int *tp,
			      boolean *subset,
			      double *v1,double *v2);

/** 
   \brief Computes the distance of two points along a subset of components.

   Computes the distance between two points given as a vector
   with a given size and considering the topology for the selected
   components.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param subset The components to use in the distance computation.
                 If NULL, this function is the same as
		 \ref DistanceTopology.
   \param w Weight for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points in the selected dimensions.
*/
double WeightedDistanceTopologySubset(unsigned int s,unsigned int *tp,
				      boolean *subset,double *w,
				      double *v1,double *v2);

/** 
   \brief Computes the distance of two points, if it is below a given threshold.

   This is like \ref DistanceTopology, but it only computes the distance
   as far it is below a given threshold. This is usefuls to rapidly abort
   computing distances for points that are further away than other points
   when searching for nearest neighbours.

   Note that if the output is above the given threshold, the distance is not
   actually fully computed (the output is not the true distance between the
   given points).

   \param t The threshold.
   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double DistanceTopologyMin(double t,unsigned int s,unsigned int *tp,
			   double *v1,double *v2);

/** 
   \brief Computes the weighted distance of two points, if it is below a given threshold.

   This is like \ref DistanceTopologyMin, but including weights in each
   dimension.

   \param t The threshold.
   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param w Weight in each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return The distance between the points.
*/
double WeightedDistanceTopologyMin(double t,unsigned int s,unsigned int *tp,double *w,
				   double *v1,double *v2);

/** 
   \brief Determines if the line between two points crosses the topology boder.

   Checks if the shortest line connecting two points crosses the borders
   imposed by the topology of each variable, i.e., if it goes across the pi,-pi
   discontinuity.

   \param s Number of elements in the vectors.
   \param tp The topology for each dimension.
   \param v1 The first point.
   \param v2 The second point.

   \return TRUE if the line crosses the topology border.
*/
boolean CrossTopologyBorder(unsigned int s,unsigned int *tp,double *v1,double *v2);

/** 
   \brief Normalizes a vector

   Normalizes a generic vector with the given size.

   \param s The size of the vector.
   \param v The vector to normalize. We output overwrite the input.
*/
void Normalize(unsigned int s,double *v);

/** 
   \brief Computes the mean.

   Computes the mean of an array of doubles.

   \param s The size of the vector.
   \param v The vector with the data.

   \return The mean of the elements in the vector.
*/
double Mean(unsigned int s,double *v);

/** 
   \brief Computes the standard deviation.

   Computes the sample standard deviation of an array of doubles.

   \param s The size of the vector.
   \param m The mean of the data (see \ref Mean).
   \param v The vector with the data.

   \return The mean of the elements in the vector.
*/
double StdDev(unsigned int s,double m,double *v);

/** 
   \brief Applies \ref PI2PI to an array.

    Applies \ref PI2PI to an array but only to those elements
    that have sphere topology.

    \param n Size of the array.
    \param t The topology for each entry in the array.
    \param a The array to adjust.
*/
void ArrayPi2Pi(unsigned int n,unsigned int *t,double *a);

/** 
   \brief Gets a row from a matrix.

   Defines a vector taking the values from the row of a matrix.

   \param k The row to use.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix.
   \param v The vector to define.
*/
void GetRow(unsigned int k,unsigned int r,unsigned int c,double *m,double *v);

/** 
   \brief Gets a column from a matrix.

   Defines a vector taking the values from the column of a matrix.

   \param k The column to use.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix.
   \param v The vector to define.
*/
void GetColumn(unsigned int k,unsigned int r,unsigned int c,double *m,double *v);

/** 
   \brief Sets a row of a matrix.

   Defines a row of a matrix taking the values from a vector.

   \param v The vector with the values to use.
   \param k The row to replace.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void SetRow(double *v,unsigned int k,unsigned int r,unsigned int c,double *m);

/** 
   \brief Sets a column of a matrix.

   Defines a column of a matrix taking the values from a vector.

   \param v The vector with the values to use.
   \param k The column to replace.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void SetColumn(double *v,unsigned int k,unsigned int r,unsigned int c,double *m);

/** 
   \brief Scales a row of a matrix.

   Multiples a row of a matrix by a given factor.

   \param k The row to scale.
   \param sc The scale factor.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void ScaleRow(unsigned int k,double sc,unsigned int r,unsigned int c,double *m);

/** 
   \brief Defines a vector as a scaled sum of rows of a matrix.

   Defines a vector as a scaled sum of rows of a matrix.

   \param r Number of rows.
   \param c Number of columns.
   \param m The matrix.
   \param n The number of selected rows.
   \param sr The selection of rows.
   \param sc The scale factor for each row.
   \param sv Stride in the 'v' vector.
   \param v The vector to define.
*/
void ScaledAddRows(unsigned int r,unsigned int c,double *m,
		   unsigned int n,unsigned int *sr,double *sc,
		   unsigned int sv,double *v);

/** 
   \brief Scales a column of a matrix.

   Multiples a column of a matrix by a given factor.

   \param k The column to scale.
   \param sc The scale factor.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void ScaleColumn(unsigned int k,double sc,unsigned int r,unsigned int c,double *m);

/** 
   \brief Dot product between two rows of a matrix.

   Dot product between two rows of a matrix.

   \param i The first row to operate.
   \param j The second row to operate.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix.
*/
double RowsDotProduct(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m);

/** 
   \brief Dot product between two columns of a matrix.

   Dot product between two columns of a matrix.

   \param i The first column to operate.
   \param j The second column to operate.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix.
*/
double ColumnsDotProduct(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m);

/** 
   \brief Computes the squared norm of a row of a matrix.

   Computes the squared norm of a row of a matrix.

   \param k The row to use.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.

   \return The squared norm of the selected row.
*/
double RowSquaredNorm(unsigned int k,unsigned int r,unsigned int c,double *m);

/** 
   \brief Computes the squared norm of a column of a matrix.

   Computes the squared norm of a column of a matrix.

   \param k The column to use.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.

   \return The squared norm of the selected column.
*/
double ColumnSquaredNorm(unsigned int k,unsigned int r,unsigned int c,double *m);

/** 
   \brief Accumulates in a given row another row, with a scale factor.

   Accumulates in row 'i' the values in row 'j' scaled by factor 'sc'.

   \param i Index of the row where to accumulate.
   \param sc The scale factor.
   \param j Index of the row to scale and to accumulate in x.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void SumRowsScale(unsigned int i,double sc,unsigned int j,unsigned int r,unsigned int c,double *m);

/** 
   \brief Accumulates in a given column another column, with a scale factor.

   Accumulates in column 'i' the values in column 'j' scaled by factor 'sc'.

   \param i Index of the column where to accumulate.
   \param sc The scale factor.
   \param j Index of the column to scale and accumulated.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void SumColumnsScale(unsigned int i,double sc,unsigned int j,unsigned int r,unsigned int c,double *m);

/** 
   \brief Copies a row into another row.

   Row copy.

   \param i The index of the row where to copy.
   \param j The index of the row from where to copy.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void CopyRow(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m);

/** 
   \brief Copies a column into another column.

   Column copy.

   \param i The index of the column where to copy.
   \param j The index of the column from where to copy.
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix to update.
*/
void CopyColumn(unsigned int i,unsigned int j,unsigned int r,unsigned int c,double *m);

/** 
   \brief Initializes an identiy matrix.

   Creates an identity matrix.

   \param n The number of rows/columns of the matrix.
   \param M The matrix.
*/
void IdentityMatrix(unsigned int n,double *M);

/** 
  \brief Initializes a diagonal matrix.

  Creates a diagonal matrix.

  \param n The number of rows/columns of the matrix.
  \param v The values for the diagonal.
  \param M The matrix.
*/
void DiagonalMatrix(unsigned int n,double *v,double *M);

/** 
   \brief Symmetrizes a matrix.

   Enforces the symmetry of a squared matrix.

   \param n The size of the matrix.
   \param M The matrix.
*/
void SymmetrizeMatrix(unsigned int n,double *M);

/** 
   \brief Product of a  matrix and a vector.

   Product of a matrix with \e r rows and \e c columns by
   a vector with \e c elements. The output is a vector of \e r entries.

   The input and output vectors must be allocated externally. Here we assume
   they have the correct size.

   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param A The matrix (stored as a vector row/column major).
   \param b The vector.
   \param o The resulting vector.
*/
void MatrixVectorProduct(unsigned int r,unsigned int c,double *A,double *b,double *o);

/** 
   \brief Accumulate the product of a matrix and a vector.

   Accumulates in 'o' the product of a matrix with \e r rows and \e c columns by
   a vector with \e c elements. 

   Note that 'o' must be different of A and 'b'. Otherwise the result would
   not be correct (and eventually an error is triggered).

   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param A The matrix (stored as a vector row/column major).
   \param b The vector.
   \param o The resulting vector. o=o+A*b
*/
void MatrixVectorProductAccum(unsigned int r,unsigned int c,double *A,double *b,double *o);

/** 
   \brief Product of a transposed matrix and a vector.

   Product of a transposed matrix with \e r rows and \e c columns by
   a vector with \e r elements. The output is a vector of \e c entries.

   The input and output vectors must be allocated externally. Here we assume
   they have the correct size.

   \param r Number of rows of the matrix (before transposing).
   \param c Number of columns of the matrix (before transposing).
   \param A The matrix (before transposing) stored as a vector (row or column major).
   \param b The vector (of size r).
   \param o The resulting vector.
*/
void TMatrixVectorProduct(unsigned int r,unsigned int c,double *A,double *b,double *o);

/** 
   \brief Accumulates the product of a transposed matrix and a vector.

   Accumulates the product of a transposed matrix with \e r rows and \e c columns by
   a vector with \e r elements. The output is a vector of \e c entries.

   Note that 'o' must be different of A and 'b'. Otherwise the result would
   not be correct (and eventually an error is triggered).

   \param r Number of rows of the matrix (before transposing).
   \param c Number of columns of the matrix (before transposing).
   \param A The matrix (before transposing) stored as a vector (row or column major).
   \param b The vector (of size r).
   \param o The resulting vector: o = o + A * b
*/
void TMatrixVectorProductAccum(unsigned int r,unsigned int c,double *A,double *b,double *o);

/** 
   \brief Product of a transposed matrix and a vector.

   Product of a transposed matrix with \e r rows and \e c columns by
   a vector with \e r elements where the elements are separeted by
   \e stride positions.
   The output is a vector of \e c entries.

   The input and output vectors must be allocated externally. Here we assume
   they have the correct size.

   \param r Number of rows of the matrix (before transposing).
   \param c Number of columns of the matrix (before transposing).
   \param A The matrix (before transposing) stored as a vector (row or column major).
   \param s The stride between elements in b.
   \param b The vector (of size r).
   \param o The resulting vector.
*/
void TMatrixVectorStrideProduct(unsigned int r,unsigned int c,double *A,unsigned int s,double *b,double *o);

/** 
   \brief A=A+B

   Compute the sum of two matrices.

   \param nr Number of rows of the matrices.
   \param nc Number of columns of the matrices.
   \param B The matrix to add.
   \param A The matrix where to add.
*/
void AccumulateMatrix(unsigned int nr,unsigned int nc,double *B,double *A);

/** 
   \brief A=A+B^t

   Compute the sum of a matrix and the transposed of another matrix.
   Both matrices are squared (otherwise the sizes would not match).

   \param nr Number of rows (and columns) of the matrices.
   \param B The matrix to transpose and add.
   \param A The matrix where to add.
*/
void AccumulateTMatrix(unsigned int nr,double *B,double *A);

/** 
   \brief A=A-B

   Compute the subtraction of two matrices.

   \param nr Number of rows of the matrices.
   \param nc Number of columns of the matrices.
   \param A The matrix from where to subtract.
   \param B The matrix to subtract.
*/
void SubtractMatrix(unsigned int nr,unsigned int nc,double *A,double *B);

/** 
   \brief C = A * B

   Computes the product of a matrix by another matrix.

   \param ra Number of rows of A.
   \param ca Numer of columns of A. This also gives the
             number of rows of B.
   \param A The first matrix (ra x ca).
   \param cb Number of columns of B.
   \param B The second matrix (ca x cb)
   \param C The resulting matrix (ra x cb). The space for this matrix
            must be allocated (deallocated) externally.
 */
void MatrixMatrixProduct(unsigned int ra,unsigned int ca,double *A,
			 unsigned int cb,double *B,double *C);

/** 
   \brief C = C + A * B

   Accumulates the product of a matrix by another matrix.
   
   Note that C must be different of A and B. Otherwise the result would
   not be correct (and eventually an error is triggered).

   \param ra Number of rows of A.
   \param ca Numer of columns of A. This also gives the
             number of rows of B.
   \param A The first matrix (ra x ca).
   \param cb Number of columns of B.
   \param B The second matrix (ca x cb)
   \param C The resulting matrix (ra x cb). The space for this matrix
            must be allocated (deallocated) externally.
 */
void MatrixMatrixProductAccum(unsigned int ra,unsigned int ca,double *A,
			      unsigned int cb,double *B,double *C);

/** 
   \brief C = A * B^t

   Computes the product of a matrix by another matrix transposed.

   \param ra Number of rows of A (without transposing). This also gives the
             number of rows of B.
   \param ca Numer of columns of A (without transposing).
   \param A The first matrix (ra x ca).
   \param rb Number of rows of B.
   \param B The second matrix (rb x ca)
   \param C The resulting matrix (ca x rb). The space for this matrix
            must be allocated (deallocated) externally.
*/
void MatrixTMatrixProduct(unsigned int ra,unsigned int ca,double *A,
			  unsigned int rb,double *B,double *C);

/** 
   \brief C = A^t * B

   Computes the product of a matrix transposed by another matrix.

   \param ra Number of rows of A (without transposing). This also gives the
             number of rows of B.
   \param ca Numer of columns of A (without transposing).
   \param A The first matrix (ra x ca).
   \param cb Number of columns of B.
   \param B The second matrix (ra x cb)
   \param C The resulting matrix (ca x cb). The space for this matrix
            must be allocated (deallocated) externally.
*/
void TMatrixMatrixProduct(unsigned int ra,unsigned int ca,double *A,
			  unsigned int cb,double *B,double *C);

/** 
   \brief Computes the cosinus of the maximum angle between two lineal sub-spaces.

   We determine the cosinus of the maximum angle between tangent spaces.

   Note that we actually return the minimum of the absolute values of the cosinus.
   This is so since aligned tangent spaces form an angle of 0 or of pi (with
   cosinus 1 or -1 respectively).

   In other words, for subspaces to be equal this function should return 1.
   If the output is 0, the subspaces are orthogonal.

   In any case, we assume that the matrices defining the subspaces are orthonormal.

   \param m Rows of the matrices defining the sub-spaces.
   \param k Columns  of the matrices defining the sub-spaces.
   \param T1 The matrix with the first sub-space.
   \param T2 The matrix with the second sub-space.

   \return The cosinus of the maximum angle (i.e., the minimum cosinus)
           between the sub-spaces.
*/
double MinCosinusBetweenSubSpaces(unsigned int m,unsigned int k,double *T1,double *T2);


/** 
   \brief Orthonormalize the rows of a matrix.

   Applies the Gram-Schmidt process to the rows of a matrix.
   Note that the input matrix might not have independent rows. The output
   may have only few non-null rows (as many as those indicated by
   the return value of this function). The orthonormalized rows
   are returned in the first rows of the output matrix.

   \param r The number of rows of the matrix.
   \param c The number of columns of the matrix.
   \param m The matrix.

   \return The number of indepentdent columns in the input matrix.
*/
unsigned int OrthonormalizeRows(unsigned int r,unsigned int c,double *m);

/** 
   \brief Orthonormalize the columns of a matrix.

   The same as \ref OrthonormalizeRows but operating on columns.

   \param r The number of rows of the matrix.
   \param c The number of columns of the matrix.
   \param m The matrix.

   \return The number of independent columns in the input matrix.
*/
unsigned int OrthonormalizeColumns(unsigned int r,unsigned int c,double *m);

/** 
   \brief Projects to the subpace spanned by the columns of a matrix.

   Projects a set of vectors into the sub-space spanned by the columns of
   a matrix.

   Note that despite projecting, the returnted vectors are in the original
   space (i.e., not given as components in the sub-space of the columns of
   \e me).

   We assume that the sub-space is given by a set of normalized vectors.

   \param rs Number of rows of the matrix spanning the sub-space of interest.
             Number of rows of the matrix to project.
   \param cs Number of columns of the matrix spanning the sub-space of interest.
   \param ms Matrix spanning the sub-space of interest. Each column must be
             a normal vector.
   \param c The number of columns of the matrix to project.
            Number of vectors to project into the sub-space spanned by \e ms.
   \param m The matrix to project. The vectors in the columns of this matrix
            are the ones projected. At the output, this containts the ambient
	    space coordinates of the vectors inside the given subspace.
*/
void ProjectToColumnSubSpace(unsigned int rs,unsigned int cs,double *ms,
			     unsigned int c,double *m);


/** 
   \brief Rank-one update of a matrix.

   Updates a matrix with a rank-one update.

   \param sc Scale factor.
   \param nr Number of rows of the matrix. Number of elements in the
            first vector.
   \param vr The first vector.
   \param nc Number of columns of the matrix. Number of elements in the
            second vector.
   \param vc The second vector.
   \param m The matrix.
*/
void RankOneUpdate(double sc,unsigned int nr,double *vr,
		   unsigned int nc,double *vc,
		   double *m);

/** 
    \brief Defines a submatrix in a matrix.

    Inserts a matrix as a submatrix of a larger matrix.

    \param nr1 Number of rows of the matrix to insert.
    \param nc1 Number of columns of the matrix to insert.
    \param m1 The matrix to insert.
    \param nri Row defining the position where to insert the matrix.
    \param nci Column defining the positon where to insert the matrix.
    \param nr Number of rows of the matrix to modify.
    \param nc Number of columns of the matrix to modify.
    \param m The matrix to modify.
*/
void SubMatrixFromMatrix(unsigned int nr1,unsigned int nc1,double *m1,
			 unsigned int nri,unsigned int nci,
			 unsigned int nr,unsigned int nc,double *m);

/** 
    \brief Accumulates a submatrix.

    Adds a submatrix into a particular position of a larger matrix.

    \param sc Scale factor.
    \param nr1 Number of rows of the matrix to add.
    \param nc1 Number of columns of the matrix to add.
    \param m1 The matrix to add.
    \param nri Row defining the position where to add the matrix.
    \param nci Column defining the positon where to add the matrix.
    \param nr Number of rows of the matrix to modify.
    \param nc Number of columns of the matrix to modify.
    \param m The matrix to modify.
*/
void AddSubMatrix(double sc,
		  unsigned int nr1,unsigned int nc1,double *m1,
		  unsigned int nri,unsigned int nci,
		  unsigned int nr,unsigned int nc,double *m);

/** 
    \brief Defines a submatrix in a matrix.

    Inserts a submatrix taken from a matrix 
    as a submatrix of a second matrix.


    \param nrs Row defining the position from where to take the submatrix
               to copy.
    \param ncs Column defining the position from where to take the submatrix
               to copy.
    \param nrc Number of rows of the submatrix to copy.
    \param ncc Number of columns of the submatrix to copy.
    \param nr1 Total number of rows of the matrix from where to take the 
               submatrix to insert.
    \param nc1 Total number of columns of the matrix from where to take the 
               submatrix to insert.
    \param m1 The matrix from where to take the submatrix to insert.
    \param nri Row defining the position where to insert the matrix.
    \param nci Column defining the positon where to insert the matrix.
    \param trans TRUE if the input is transposed in the copy. 
    \param nr Number of rows of the matrix to modify.
    \param nc Number of columns of the matrix to modify.
    \param m The matrix to modify.
*/
void SubMatrixFromSubMatrix(unsigned int nrs,unsigned int ncs,
			    unsigned int nrc,unsigned int ncc,
			    unsigned int nr1,unsigned int nc1,double *m1,
			    unsigned int nri,unsigned int nci,
			    boolean trans,
			    unsigned int nr,unsigned int nc,double *m);

/** 
   \brief Initializes a matrix with a block from another matrix.

   Copies a sub-matrix into a matrix.

   Note that rs+r_dst should be lower or equal than r_src and the
   same for the columns, but no error check is performed.

   \param r_src Number of rows of the matrix from where to copy.
   \param c_src Number of columns of the matrix from where to copy.
   \param m_src The matrix from where to copy.
   \param rs Row of the position from where to take the block to copy.
   \param cs Column of the position from where to take the block to copy.
   \param r_dst Number of rows of the matrix where to copy.
                Size in rows of the block to take from \e m_src.
   \param c_dst Number of columns of the matrix where to copy.
                Size in columns of the block to take from \e m_src.
   \param m_dst The matrix to initialize.
*/
void MatrixFromSubMatrix(unsigned int r_src,unsigned int c_src,double *m_src,
			 unsigned int rs,unsigned int cs,
			 unsigned int r_dst,unsigned int c_dst,double *m_dst);

/** 
    \brief Defines a submatrix in a matrix.

    Inserts a transposed matrix as a submatrix of a larger matrix.

    \param nr1 Number of rows of the matrix to insert (before transposing it).
    \param nc1 Number of columns of the matrix to insert (before transposing it).
    \param m1 The matrix to insert.
    \param nri Row defining the position where to insert the matrix.
    \param nci Column defining the positon where to insert the matrix.
    \param nr Number of rows of the matrix to modify.
    \param nc Number of columns of the matrix to modify.
    \param m The matrix to modify.
*/
void SubMatrixFromTMatrix(unsigned int nr1,unsigned int nc1,double *m1,
			  unsigned int nri,unsigned int nci,
			  unsigned int nr,unsigned int nc,double *m);

/** 
   \brief Selects some of the columns of a matrix.

   Reduces the size of a matrix selecting some of their columns, for instance,
   the linearly independent ones.

   \param sc The selected columns (boolean array).
   \param nr Number of rows in the matrix.
   \param nc Number of columns in the matrix.
   \param m The matrix (stored as a matrix).
*/
void SelectMatrixColumns(boolean *sc,unsigned int nr,unsigned int nc,double *m);

/** 
   \brief Selects some of the rows of a matrix.

   Reduces the size of a matrix selecting some of their rows, for instance,
   the linearly independent ones.

   \param sr The selected rows (boolean array).
   \param nr Number of rows in the matrix.
   \param nc Number of columns in the matrix.
   \param m The matrix (stored as a matrix).
*/
void SelectMatrixRows(boolean *sr,unsigned int nr,unsigned int nc,double *m);

/** 
   \brief Prints a vector.

   Prints a vector into a file.

   \param f The file where to store the vector.
   \param label The name of the vector (possibly NULL).
   \param n The size of the vector.
   \param v The vector.
*/
void PrintVector(FILE *f,char *label,unsigned int n,double *v);

/** 
   \brief Saves a vector.

   Saves a vector into a file.

   \param f The file where to store the vector.
   \param n The size of the vector.
   \param v The vector.
*/
void SaveVector(FILE *f,unsigned int n,double *v);

/** 
   \brief Prints a matrix.

   Prints a matrix into a file.

   \param f The file where to print the matrix.
   \param label Tne name of the matrix (possibly NULL)
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix.
*/
void PrintMatrix(FILE *f,char *label,unsigned int r,unsigned int c,double *m);

/** 
   \brief Prints a transposed matrix.

   Prints a transposed matrix into a file.

   \param f The file where to print the matrix.
   \param label Tne name of the matrix (possibly NULL)
   \param r Number of rows of the matrix.
   \param c Number of columns of the matrix.
   \param m The matrix.
*/
void PrintTMatrix(FILE *f,char *label,unsigned int r,unsigned int c,double *m);

#endif
