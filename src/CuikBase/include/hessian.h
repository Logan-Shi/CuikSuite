#ifndef HESSIANH
#define HESSIANH

#include "variables.h"
#include "equations.h"
#include "jacobian.h"

/** 
    \file hessian.h

    \brief Definition of the THessian type and the associated functions.

    Definition of the THessian type and the associated functions.

    \sa THessian, hessian.c.
*/

/** 
   \brief Hessian of a set of equations.

   Symbolic Hessian of a set of equations, i.e., the double derivative
   of the equations with respect to each pair of variables.
*/
typedef struct {
  unsigned int neqs;  /**< Number of equations. */
  unsigned int nvars; /**< Number of variables */
  Tequations **H;     /**< Double derivative of the equations w.r.t the
			   variables. */
} THessian;

/** 
   \brief Constructor.

   Initializes the Hessian deriving the Jacobian of a 
   set of equations.

   \param j The Jacobian
   \param h The resulting Hessian.
*/
void InitHessian(TJacobian *j,THessian *h);

/** 
   \brief Number of variables.

   Number of variables in the Hessian.

   \return Number of variables.
 */
unsigned int GetHessianNVars(THessian *h);

/** 
   \brief Number of equations.

   Number of equations in the Hessian.

   \return Number of equations.
 */
unsigned int GetHessianNEqs(THessian *h);


/** 
   \brief Allocate space for the Hessian evaluation.
   
   Allocate space for the Hessian evaluation.

   \param m The allocated space.
   \param h The Hessian.
*/
void AllocateHessianEvaluation(double ****m,THessian *h);

/** 
    \brief Allocates space for the Hessian evaluation.

    This is allocates the space in sub-matrices, one for each equation where
    each submatrix (of size nvars x nvars) is stored as a vector. This
    format is specific to speed up the execution of \ref EvaluateHessianVector

    \param nie Number of independent equations. NO_UINT if all equations are
               independent.
    \param m The allocated space.
    \param h The Hessian.
*/
void AllocateHessianEvaluationAsVectors(unsigned int nie,double ***m,THessian *h);

/** 
   \brief Evaluates the Hessian

   Evaluates the Hessian for a given value of the variables.

   \param v The value for the variables.
   \param m The matrix where to store the result (see \ref AllocateHessianEvaluation).
   \param h The Hessian to evalute.
*/
void EvaluateHessian(double *v,double ***m,THessian *h);

/** 
   \brief Evaluates an scalar Hessian

   Evaluates the Hessian for a given value of the variables.

   Here the Hessian is supossed to include only the scalar part of a larger system
   and we implicitly assume that the scalar part is always the first part of the
   larger system.

   A Hessian with only the position scalar equations is obtained from a Jacobian
   including only these equations (see \ref InitScalarPositionJacobian).

   This is the similar to \ref EvaluateHessian but the output matrix \e m is organized
   in a different way. Instead of being numEqs x numVars x numVars it is
   numVars x numEqs x  numVars and the (numEqs x  numVars) matrices are stored
   as vectors.

   So, the matrix \e m IS NOT allocated with \e AllocateHessianEvaluationAsVectors
   but must be allocated by the caller

   \param v The value for the variables.   
   \param independentEq The independent equations. NULL if all equations are independent.
                        This is a vector over all the equations in the system and we are
			only interested in the scalar ones (the first part).
   \param neq Rows of each matrix m[i]. This is the number of equations including
              both the scalar and the matrix ones.
   \param m The matrices where to store the result.
   \param h The Hessian to evalute.

   \return The number of independent scalar equations. The size of the top part of each
            matrix m[] filled in this function.
*/
unsigned int EvaluateScalarHessian(double *v,boolean *independentEq,
				   unsigned int neq,double **m,THessian *h);

/** 
   \brief Evaluates the product of the Hessian with a vector.

   Evaluates H*v. This has to be interpreted as

     - [ H[1][]*v H[2][]*v ... H[n][]*v] 
     .
   were H[i][j] is the derivative of the whole set of equation with respect to
   variables i and j. That is, H[i][j] is a vector with as many elements as
   equations in the system. Then, H[i][] is a matrix of neqs x nvars elements 
   and H[i][]*v  is a vector of neqs elements. Such vectors for all variables i
   for a matrix of neqs x nvars elements. 

   \param x The point where to evaluate the Hessian.
   \param v The vector to use in the products. The size of this vector is the
            number of variables in the system.
   \param nie Number of independent equations. NO_UINT if all equations are independent.
   \param independentEq The independent equations. NULL if all equations are independent.
   \param m The space where to evaluate the hessian. See \ref AllocateHessianEvaluationAsVectors.
            If NULL the space is allocated internally.
   \param mf Space for the matrix resulting from the Hessian-vector product.
             The size of this is neqs x nvars.
             If NULL, the space is allocated internally
   \param h The Hessian to evaluate.
*/
void EvaluateHessianVector(double *x,double*v,
			   unsigned int nie,boolean *independentEq,
			   double **m,double *mf,THessian *h);

/** 
   \brief Evaluates the double product of the Hessian with a vector.

   Evaluates H*v*v. This has to be interpreted as

     - [ H[1][]*v H[2][]*v ... H[n][]*v] *v
     .
   were H[i][j] is the derivative of the whole set of equation with respect to
   variables i and j. That is, H[i][j] is a vector with as many elements as
   equations in the system. Then, H[i][] is a matrix of neqs x nvars elements 
   and H[i][]*v  is a vector of neqs elements. Such vectors for all variables i
   form a matrix of neqs x nvars elements. This matrix, when multiplied by
   'v' generate a vector (the output 'o') of neqs elements.

   \param x The point where to evaluate the Hessian.
   \param v The vector to use in the products. The size of this vector is the
            number of variables in the system.
   \param nie Number of independent equations. NO_UINT if all equations are independent.
   \param independentEq The independent equations. NULL if all equations are independent.
   \param m The space where to evaluate the hessian. See \ref  AllocateHessianEvaluationAsVectors.
            If null the space is allocated internally.
   \param mf Space for the matrix resulting from the first Hessian-vector product.
             The size of this is neqs x nvars.
             If null, the space is allocated internally
   \param o The output vector. Must be allocated/deallocated externally. The size of
            this vector is number of equations in the system.
   \param h The Hessian to evaluate.
*/
void EvaluateHessianVector2(double *x,double *v,
			    unsigned int nie,boolean *independentEq,
			    double **m,double *mf,double *o,THessian *h);

/** 
   \brief Release space for the Hessian evaluation.

   Release space for the Hessian evaluation typically 
   allocated using \ref AllocateHessianEvaluation.

   \param m The space to release.
   \param h The corresponding Hessian.
*/
void FreeHessianEvaluation(double ***m,THessian *h);

/** 
   \brief Release space for the Hessian evaluation.

   Release space for the Hessian evaluation typically 
   allocated using \ref AllocateHessianEvaluationAsVectors.

   \param m The space to release.
   \param h The corresponding Hessian.
*/
void FreeHessianEvaluationAsVectors(double **m,THessian *h);

/** 
   \brief Destructor.

   Release a Hessian structure.

   \param h The Hessian structure to release.
*/
void DeleteHessian(THessian *h);

#endif 
