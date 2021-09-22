#ifndef NHESSIANH
#define NHESSIANH

#include "equations.h"
#include "hessian.h"

/** 
    \file nhessian.h

    \brief Definition of the TNHessian type and the associated functions.

    Definition of the TNHessian type and the associated functions.

    \sa TNHessian, dhessian.c.
*/

/** 
   \brief Hessian of a set of equations for problems with dynamics.

   For problems with dynamics where all the equations are matrix equations,
   the Hessian can be efficiently evaluated (numerically and for a given
   state, instead than symbolically as done in \ref hessian.h).

   For such numeric evaluation only the position equations are required.
   The derivative is computed on-the-fly (not computed symbolically
   beforehand). This saves a lot of repeated matrix multiplications.
   Moreover, we take advantage of the symmetry fo the double-derivative
   (diff(f)/(diff(i) diff(j))=diff(f)/(diff(j) diff(i))) to save
   even more computations.

   This can be seen as a particular procedure for systems including
   only matrix equations. It is a quite usual case and the use of
   the particular procedures implemented here can result in 
   high efficiency gains in the simulation of systems with dynamics.
*/
typedef struct {
  unsigned int nvars; /**< Number of position variables. */
  unsigned int nEq;   /**< Number of position equations (either scalar or matrix). */
  THessian sH;        /**< Hessian of the scalar equations, if any. */
  unsigned int nsEq;  /**< Number of position scalar equations */
  unsigned int nmEq;  /**< Number of matrix scalar equations. */
  double **h;         /**< Space to evaluate the hessian. This will be a set of nvar matrices 
			   (stored in vector form) of neqs x nvars.  */
  TMequation **me;    /**< Matrix position equations. */
} TNHessian;

/** 
   \brief Initializes the hessian with dynamics.

   Initializes the \ref TNHessian structure keeping only the
   position matrix equations.

   Note that the input parameters include all the variables
   and equations in the (simplified) system but that internally
   we only use the position ones.

   \param vs The variables in the problem.
   \param eqs The equations in the problem.
   \param sJ Jacobian of the scalar position equations, if any.
   \param nh the structure to initialize.

   \return FALSE if the problem has not the features required for
           the fast numerical hessian evaluation: All equations
	   must be in matrix form. If FALSE, the
	   structure is not actually initialized (you
	   do not need to delete it).
*/
boolean InitNHessian(Tvariables *vs,Tequations *eqs,TJacobian *sJ,TNHessian *nh);

/** 
    \brief Evaluates the double product of the Hessian with a vector.

    This is a replacement for \ref EvaluateHessianVector2, which is
    the most expensive function in the dynamic simulation. It is
    used to compute the acceleration and it takes about most of
    the execution time.

    See \ref EvaluateHessianVector2 for more information about
    what is computed here.
    
    \param x The point where to evaluate the Hessian.
    \param v The vector to use in the products. The size of this vector is the
             number of variables in the system.
    \param nie Number of independent position equations. 
               NO_UINT if all equations are independent.
    \param independentEq The independent position equations.
                         NULL if all position equations are independent.
    \param m Space for h*v.  This is a matrix of nieqs x nvars (stored in vector form).
    \param o The output vector. Must be allocated/deallocated externally. The size of
             this vector is number of independent position equations in the system.
    \param nh The numeric Hessian structure to evaluate.
    
*/
void EvaluateNHessianVector2(double *x,double *v,
			     unsigned int nie,boolean *independentEq,
			     double *m,double *o,TNHessian *nh);

/** 
    \brief Destructor.

    Deletes the numeric hessian structure.
    
    \param nh The structure to delete.
*/
void DeleteNHessian(TNHessian *nh);


#endif
