#ifndef NJACOBIANH
#define NJACOBIANH

#include "equations.h"
#include "jacobian.h"

/** 
    \file njacobian.h

    \brief Definition of the TNJacobian type and the associated functions.

    Definition of the TNJacobian type and the associated functions.

    \sa TNJacobian, djacobian.c.
*/

/** 
   \brief Jacobian of a set of equations for problems with dynamics.

   For problems with dynamics where all the position equations are matrix equations,
   the Jacobian (of the position equations) can be efficiently evaluated (numerically 
   and for a given state, instead than symbolically as done in \ref jacobian.h).

   For such numeric evaluation only the position equations are considered.
   The derivative is computed on-the-fly (not computed symbolically
   beforehand). This saves a lot of repeated matrix multiplications.

   This can be seen as a particular procedure for systems including
   only matrix equations. It is a quite usual case and the use of
   the particular procedures implemented here can result in 
   high efficiency gains in the simulation of systems with dynamics.
*/
typedef struct {
  Tequations *eqs;    /**< The set of equations. Only used if the 
		           equation set includes scalar equations. */
  TJacobian sJ;       /**< The symbolic Jacobian of the scalar equations
			   in the equation set, if any. */
  unsigned int nvars; /**< Number of position variables. */
  unsigned int nEq;   /**< Number of position equations, including both
		           matrix and scalar equations, if any. */
  unsigned int nsEq;  /**< Number of scalar equations, if any. */
  unsigned int nmEq;  /**< Number of matrix scalar equations. */
  double *m;          /**< Space for the Jacobian. This is a matrix
			   of neqs x nvars (stored in vector form).
		           Only used when evaluating the system
		           (see \ref EvaluateSystemFromNJacobian). */
  double *v;          /**< Temporary space used in 
			   \ref EvaluateSystemFromNJacobian) to store
			   the velocity. 
		           Thus, this is of size nvars. */
  double *f;          /**< Temporary space used in 
			   \ref EvaluateSystemFromNJacobian) to evaluate
		           the position and the velocity equations. 
		           Thus, this is of size 2*nEq. */
  TMequation **me;    /**< Matrix position equations. */
} TNJacobian;

/** 
   \brief Initializes the jacobian with dynamics.

   Initializes the \ref TNJacobian structure keeping only the
   position matrix equations.

   Note that the input parameters include all the variables
   and equations in the (simplified) system but that internally
   we only use the position ones.

   \param vs The variables in the problem.
   \param eqs The equations in the problem.
   \param nj the structure to initialize.

   \return FALSE if the problem has not the features required for
           the fast numerical jacobian evaluation: All equations
	   must be in matrix form. If FALSE, the
	   structure is not actually initialized (you
	   do not need to delete it).
*/
boolean InitNJacobian(Tvariables *vs,Tequations *eqs,TNJacobian *nj);

/** 
   \brief Gets the Jacobian of the scalar position equations.

   Returns a pointer to the Jacobian of the scalar position equations or
   NULL if the underlying system does not include scalar position equations.

   \param nj The numerical Jacobian to query.

   \return A pointer to the scalar Jacobian, if defined.
*/
TJacobian *GetScalarJacobian(TNJacobian *nj);

/** 
    \brief Evaluates the system equations.

    Replacement for \ref CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS. 
    This is implemented taking advantage that the nJacobian structure
    has all the data necessary to efficiently evaluate the system equations.
    This can result in some computational savings (not as large as when
    numerically evaluating the residue and musch less than when
    numerically evaluationg the hessian).
    
    \param x The state where to evaluate the system. Incudes position and
             velocities (in the second half of the vector).
    \param ndxV Index of the velocity variables inside \e x.
    \param ne Total number of equations in the problem. Size of \e iE.
    \param nie Number of independent position equations. 
               NO_UINT if all equations are independent.
    \param iE The independent equations. 
              NULL if all position equations are independent.
    \param ipE The independent position equations. 
               NULL if all position equations are independent.
    \param pvEq Identifies postion or velocity equations in the system.
    \param pEq Identifes position equations in the system.
    \param o Value for the non-position/velocity variables.
    \param f The output vector. Must be allocated/deallocated externally. The size of
             this vector is number of independent position equations in the system.
    \param nj The numeric Jacobian structure to evaluate.
    
*/
void EvaluateSystemFromNJacobian(double *x,unsigned int *ndxV,unsigned int ne,unsigned int nie,
				 boolean *iE,boolean *ipE,boolean *pvEq,boolean *pEq,
				 double *o,double *f,TNJacobian *nj);

/** 
    \brief Evaluates the Transposed Jacobian.

    This is a replacement for \ref EvaluateTransposedJacobianSubSetInVector. 
    This is an expensive operation in the dynamic simulation.

    This computes the Jacobian of the position equations, which are the only
    ones stored.

    \param x The state where to evaluate the Jacobian. Incudes position and
             velocities (in the second half of the vector).
    \param nie Number of independent position equations. 
               NO_UINT if all equations are independent.
    \param independentEq The independent position equations. 
                         NULL if all position equations are independent.
    \param m The output Jacobian transposed matrix. The size of this
             matrix is nvars x nie (independent position equations).
    \param nj The numeric Jacobian structure to evaluate.
    
*/
void EvaluateTransposedNJacobianSubSetInVector(double *x,unsigned int nie,boolean *independentEq,
					       double *m,TNJacobian *nj);

/** 
    \brief Destructor.

    Deletes the numeric jacobian structure.
    
    \param nj The structure to delete.
*/
void DeleteNJacobian(TNJacobian *nj);


#endif
