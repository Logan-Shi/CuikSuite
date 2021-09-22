#ifndef JACOBIANH
#define JACOBIANH

#include "variables.h"
#include "equations.h"
#include "csmapping.h"

#include <stdio.h>

/** \file jacobian.h
    \brief Definition of the TJacobian type and the associated functions.

    Definition of the TJacobian type and the associated functions.

    \sa TJacobian, jacobian.c.
*/

/** 
    \brief The Jacobian of a set of equations.

    Represents the symbolic Jacobian of a set of equations including the derivative
    of each equation with respect to each variable.

    \todo Take advantage of the velocity flags for variables and equations to
          speed up the Jacobian evaluation.
*/
typedef struct {
  Tvariables *vars;   /**< Variable set. */
  Tequations *eqs;    /**< Equation set. */
  unsigned int neqs;  /**< Number of equations. Number of rows of the Jacobian */
  unsigned int nvars; /**< Number of variables. Number of columns of the Jacobian */
  Tequations *J;      /**< Set of columns of the Jacobian, each one corresponding 
			   to the derivative with respect to a given variable. */
} TJacobian;

/** 
   \brief Constructor.

   Initializes the Jacobian deriving a set of equations.

   \param vs The variables involved in the equations.
   \param eqs The equations to derive.
   \param j The resulting Jacobian.
*/
void InitJacobian(Tvariables *vs,Tequations *eqs,TJacobian *j);

/** 
   \brief Constructor.

   Initializes the Jacobian deriving the subset of position of equations.

   \param vs The variables involved in the equations.
   \param eqs The equations to derive.
   \param j The resulting Jacobian.
*/
void InitPositionJacobian(Tvariables *vs,Tequations *eqs,TJacobian *j);

/** 
   \brief Constructor.

   Initializes the Jacobian deriving the subset of scalar position of equations.

   \param vs The variables involved in the equations.
   \param eqs The equations to derive.
   \param j The resulting Jacobian.
*/
void InitScalarPositionJacobian(Tvariables *vs,Tequations *eqs,TJacobian *j);

/** 
   \brief Constructor.

   Initializes a Jacobian from another Jacobian.

   \param j_dst The Jacobian to initialize.
   \param j_src The Jacobian from where to get the data.
*/
void CopyJacobian(TJacobian *j_dst,TJacobian *j_src);

/** 
   \brief Copies the non-dynamics Jacobian.

   Gets a copy of the part of the Jacobian not directly related
   with the dynamics: equations not related to position/velocity
   derived with respect to the position equations. 
   This block is used in a chain rule to obtain the time
   derivative of the non-dynamics (non position/velocity) equations.

   \param j_dstP The Jacobian with respect to position variables.
   \param j_dstO The Jacobian with respect to the nont-dynamic variables.
   \param j_src The Jacobian from where to get the data.
*/
void CopyNonDynamicsJacobian(TJacobian *j_dstP,TJacobian *j_dstO,
			     TJacobian *j_src);

/** 
   \brief Copies the position Jacobian.

   Gets a copy of the position Jacobian (part of the Jacobian
   corresponding to position variables and equations).

   \param j_dst The Jacobian to initialize.
   \param j_src The Jacobian from where to get the data.
*/
void CopyPositionJacobian(TJacobian *j_dst,
			  TJacobian *j_src);

/** 
   \brief Returns the size of the Jacobian.
   
   Gives the Jacobian size.
   
   \param nr Number of rows of the Jacobian (output).
   \param nc Number of columns of the Jacobian (output).
   \param j The Jacobian to query.
*/
void GetJacobianSize(unsigned int *nr,unsigned int *nc,TJacobian *j);

/** 
  \brief Returns one of the Jacobian element.

  Returns the derivative of all equations with respect to a given variable,
  i.e, one of the columns of the Jacobian.

  \param nv The derivation variable.
  \param J The Jacobian to query.

  \return A pointer to the equations giving the column of the Jacobian.
 */
Tequations *GetJacobianColumn(unsigned int nv,TJacobian *J);

/** 
   \brief Returns one element of the Jacobian.

   Returns a pointer to one element of the Jacobian.
   This only works for scalar systems.
   
   \param r Row of the element to retrive.
   \param c Column of the element to retrive. 
   \param j The Jacobian to query.
*/
Tequation *GetJacobianEquation(unsigned int r,unsigned int c,TJacobian *j);

/** 
   \brief Rewrites the equations in a Jacobian to the original system.

   For a Jacobian of a simplified system of equations, we change the variable
   identifiers by those in the orignal system. Note that this is just
   a variable identifier replacement since all the variables in the
   simplified system are also in the original.
   
   \param map The map from the simplified system to the original.
   \param j The Jacobian to map.
*/
void RewriteJacobian2Orig(Tmapping *map,TJacobian *j);

/** 
   \brief Linear combination of the columns of the Jacobian.

   Generate linear combinations of the columns of the Jacobian and
   adds them to a given equation set.

   This is used when defining velocity equations.

   \param selectedVars If not NULL, it allows selecting the
                       columns of the Jacobian to be combined.
		       Also only the selected variables are
		       actually used.
   \param nv The variable identifier to use as coefficients of the
             linear combination to generate.
   \param eqs The equation set where to add the linear combination.
   \param j The Jacobian with the columns to combine.
*/
void JacobianLinearCombination(boolean *selectedVars,unsigned int *nv,
			       Tequations *eqs,TJacobian *j);

/** 
   \brief Allocate space for the Jacobian evaluation.
   
   Allocate space for the Jacobian evaluation.

   \param m The allocated space.
   \param j The Jacobian to evaluate.
*/
void AllocateJacobianEvaluation(double ***m,TJacobian *j);

/** 
   \brief Evaluates the Jacobian

   Evaluates the Jacobian for a given value of the variables.

   \param v The value for the variables.
   \param m The matrix where to store the result (see \ref AllocateJacobianEvaluation).
   \param j The Jacobian to evalute.
*/
void EvaluateJacobian(double *v,double **m,TJacobian *j);

/** 
   \brief Evaluates the Jacobian.

   Evaluates the Jacobian for a given value of the variables and stores the result
   in a vector instead of in a matrix. 

   \param v The value for the variables.
   \param nr Number of rows of the space to store the Jacobian.
   \param nc Number of columns of the space to store the Jacobian.
   \param m The vector where to store the result.
   \param j The Jacobian to evalute.
*/
void EvaluateJacobianInVector(double *v,
			      unsigned int nr,unsigned int nc,double *m,TJacobian *j);

/** 
   \brief Evaluates some of the Jacobian equations.

   Evaluates some of the Jacobian equations for a given value of the variables 
   and stores the result in a vector instead of in a matrix.

   \param v The value for the variables.
   \param sr Boolean array with the selected rows to store in the output.
   \param nr Number of rows. This typically is the number of equations but can be larger
             in cases where extra constratins are added to the system.
   \param nc Number of columns. This typically is the number of variables but can be larger
             in cases where extra variables are added to the system.
   \param m The vector where to store the result.
   \param j The Jacobian to evalute.
*/
void EvaluateJacobianSubSetInVector(double *v,boolean *sr,
				    unsigned int nr,unsigned int nc,double *m,TJacobian *j);

/** 
   \brief Evaluates the transposed Jacobian.

   Evaluates the transposed Jacobian for a given value of the variables and stores the result
   in a vector instead of in a matrix. The vector is organized column wise (1st column
   2nr column, etc).

   \param v The value for the variables.
   \param nr Number of rows of the space to store the transposed Jacobian
   \param nc Number of columns of the space to store the transposed Jacobian.
   \param m The vector where to store the result.
   \param j The Jacobian to evalute.
*/
void EvaluateTransposedJacobianInVector(double *v,
					unsigned int nr,unsigned int nc,double *m,TJacobian *j);

/** 
   \brief Evaluates a subset of the transposed Jacobian.

   Evaluates a subset of the transposed Jacobian for a given value of the variables and stores the result
   in a vector instead of in a matrix. The vector is organized column wise (1st column
   2nr column, etc).

   \param v The value for the variables.
   \param sr Selection of the rows of the Jacobian to store (they becoome columns in the 
             output array).
   \param nr Number of rows of the the space to store the transposed Jacobian.
   \param nc Number of columns of the space to store the transposed Jacobian.
   \param m The vector where to store the result.
   \param j The Jacobian to evalute.
*/
void EvaluateTransposedJacobianSubSetInVector(double *v,boolean *sr,
					      unsigned int nr,unsigned int nc,double *m,TJacobian *j);

/** 
   \brief Prints the result of evaluating the Jacobian.

   Prints the result of evaluating the Jacobian. This is basically used for debug.

   \param f The file where to store the jacobian.
   \param m The matrix with the Jacobian evaluation.
   \param j The Jacobian.
*/
void PrintJacobianEvaluation(FILE *f,double **m,TJacobian *j);

/** 
   \brief Release space for the Jacobian evaluation.

   Release space for the Jacobian evaluation typically 
   allocated using \ref AllocateJacobianEvaluation.

   \param m The space to release.
   \param j The corresponding Jacobian.
*/
void FreeJacobianEvaluation(double **m,TJacobian *j);

/** 
    \brief Evaluates the Jacobian multiplied by some given vectors.

    This is a funcition with a very particular purpose. It evaluates
    the matrix equations in the Jacobian on a given point and then, 
    for each matrix equation in the Jacobian, M, it evaluates M*v[i]
    for a set of 3D vectors, v[i].
    This is used when generating the Jacobian of a given set of
    atom positions with respect ot the internal coordinates.
    In this case the Jacobian is derived from equations giving
    the pose P of each link from the internal coordinates. The position
    of an atom is P*v[i], with v[i] the center of the atom.
    The derivative of P*v[i] is M*v[i] with M the derivative of
    P w.r.t. the internal variables.

    The output of this function is a matrix with 3*n rows and m
    columns (n=number of atoms and m= number of internal coordinates).
 
    This is not the default size of the Jacobian and, thus,
    \ref FreeJacobianEvaluation can not be used to de-allocate the
    space for the evaluation.

    IMPORTANT: This only operates on matrix equations.
 
    \param p The point where to evaluate the Jacobian.
    \param n The number of 3D vectors in \e v (number of atoms).
    \param ng Number of rigid groups of atoms (groups of vectors in \e v).
    \param g The nubmer of atoms to apply to each matrix equation.
             In principle the Jacobian must include one matrix equation
	     for each link (i.e., rigid group of atoms).
    \param v The vector with the atom positions.
    \param nr The number of rows of the output Jacobian.
    \param nc The number of columsn of the output Jacobian.
    \param m The output Jacobian.
    \param j The Jacobian to use in the evaluation.
*/
void EvaluateJacobianXVectors(double *p,
			      unsigned int n,unsigned int ng,unsigned int *g,double *v,
			      unsigned int *nr,unsigned int *nc,double ***m,
			      TJacobian *j);

/** 
   \brief Prints the symbolic Jacobian.

   Prints the equations in the symbolic Jacobian column-wise.

   \param f The file where to store the equations.
   \param varNames The name for each variable. Use NULL to print generic names.
   \param j The Jacobian structure.
*/
void PrintJacobian(FILE *f,char **varNames,TJacobian *j);

/** 
   \brief Destructor.

   Release a Jacobian structure.

   \param j The Jacobian structure to release.
*/
void DeleteJacobian(TJacobian *j);

#endif 
