#ifndef MEQUATIONH
#define MEQUATIONH

#include "trans_seq.h"
#include "csmapping.h"
#include "boolean.h"

#include <stdio.h>

/** 
    \file mequation.h
 
    \brief Definition of the matrix equation operations.

    Definition of the matrix equation operations.

    \sa TMequation, mequation.c.
*/


/** 
   \brief Wether to generate redundant matrix equations.

   If set, we generate redundant matrix equations: all the
   matrix entries are used as scalar equations, even if
   they are redundant.

   If set, we generate 6 equations for planar mechanisms
   and 9 for 3D ones. Otherwise only 4 and 6 equations
   are generated, respectively.
*/
#define REDUNDANT_EQ_MATRIX 1

/** 
   \brief Max number of scalar equations in a matrix equation.

   Max number of scalar equations in a matrix equation.
*/
#define MAX_EQ_MATRIX (REDUNDANT_EQ_MATRIX?9:6)

/**  \brief Matrix equation.

    Matrix equation. This is basically an addition of transformation sequences (products)
    that must be equal to  the identity (or to zero in some cases).
    
    Typically only one transformation sequence is used, but when deriving
    several sequences might be added. The only way to obtain a derived matrix 
    equation is to use \ref DeriveMEquation.

    Each matrix equation defines a set of scalar equations according to the dof involved
    in the transformation product sequences.
    Typically there are 6 equations (the diagonal of the rotation part plust the translation)
    but they can be less if only one type of rotation is involved or one type of translation, etc).

    \sa mequation.h, mequation.c.
*/
typedef struct {
  boolean simp;        /**< TRUE if the matrix equation is already simplified.
			    Nothing else can be added to the matrix equation once simplified. */
  boolean velocity;    /**< True for velocity equations. */
  boolean nonDynamic;  /**< True for non-dynamic equations. */
  
  unsigned int n;      /**< Number of matrix product to add */
  TTransSeq **ts;      /**< The set of matrix product sequences. */
  unsigned int *vID;   /**< Optional variable scaling each matrix product sequence. This appears
			    when defining velocity equations. Otherwise the variable is NO_UINT
			    and has no effect. */
  
  THTransform rhs;    /**< Right hand side value. This is identity or zero (for derived equations) */
  
  unsigned int neq;   /**< Number of scalar equations defined form the
		           matrix equation. */
  unsigned int r[MAX_EQ_MATRIX];  /**< Row for the i-th scalar equation. */
  unsigned int c[MAX_EQ_MATRIX];  /**< Column of the i-th scalar equation. */
} TMequation;

/** 
   \brief Construtor.

   Initializes a matrix equation Id=Id

   \param me The matrix equation.
*/
void InitMEquation(TMequation *me);

/** 
   \brief Copy constructor.

   Copies one matix equation into another.

   \param me_dst The matrix equation to generate.
   \param me_src The matrix equation from which to get the data.
*/
void CopyMEquation(TMequation *me_dst,TMequation *me_src);

/** 
   \brief Resets the information stored in the matrix equation.

   Resets the information stored in the matrix equation so that it
   can be re-used without delete/init.

   \param me The matrix equation to reset.
*/
void ResetMEquation(TMequation *me);

/** 
    \brief Identify empty matrix equations.

    Identifies empty matrix equations.

    \param me The matrix equation to check.
*/
boolean IsEmptyMEquation(TMequation *me);

/** 
    \brief Number of terms added in the matrix equation.

    Number of terms added in the matrix equation.

    \param me The matrix equation to query.
    
    \return The number of added terms.
*/
unsigned int MEquationNTerms(TMequation *me);

/** 
    \brief Maximum number of variables.

    Maximum number of variables in each transform
    in the matrix equation.

    \param me The matrix equation to query.

    \return The maximum number of variables.
*/
unsigned int MEquationMaxVars(TMequation *me);

/** 
   \brief Identifies matrix equations with repeated variables.

   Matrix equations with repeated variables (in each term) yield more
   complex derivatives. This function identifes such
   matrix equations.

   \param me The matrix equation to query.

   \return TRUE if the equation includes any term with
           repeated variables. Note that repeated
	   variables in different terms are not 
	   detected.
*/
boolean MEquationHasRepeatedVar(TMequation *me);

/** 
   \brief Size of the matrix equation.

   Size of the matrix equation where the size is considered
   as the lenght of the largest tranform sequence included
   in the matrix equation.

   \param me The matrix equation to query.

   \return The size of the matrix equation.
*/
unsigned int MEquationSize(TMequation *me);

/** 
   \brief Cheks if a matrix equation includes rotations.

   Cheks if a matrix equation includes rotations.

   \param me The matrix equation to check.

   \return TRUE if the matrix equation includes rotations.
*/
boolean HasRotations(TMequation *me);

/** 
   \brief Sets the rhs to identity.

   Sets the rhs of the matrix equation to identity.

   \param me The matrix equation to modify.
*/
void IdentityRHSMEquation(TMequation *me);

/** 
   \brief Sets the rhs to zero.

   Sets the rhs of the matrix equation to zero.

   \param me The matrix equation to modify.
*/
void ZeroRHSMEquation(TMequation *me);

/** 
   \brief Sets a matrix equation as a translation equation.

   Modifies a matrix equation so that only their translation part
   is taken into consideration when evaluating them.

   \param me The matrix to modify.
*/
void SetTranslationMEquation(TMequation *me);

/** 
   \brief Checks if the matrix equation includes a given variable.

   Checks if the matrix equation includes a given variable.

   \param v The variable identifier.
   \param me The matrix equation to check.

   \return TRUE if the matrix equations includes variable 'v'.
*/
boolean VarIncludedinMEquation(unsigned int v,TMequation *me);

/** 
   \brief Adds a variable transform to the matrix equation.

   Adds a variable transform at the end of a matrix equation.

   \param t Type of transform.
   \param s The sign for 'v'.
   \param v Variable involved in the transform.
   \param me The matrix equation to enlarge.
*/
void AddVarTrans2MEquation(unsigned int t,int s,unsigned int v,TMequation *me);

/** 
   \brief Adds a displacement along a vector.

   Adds a variable transform that represents a scaled displacement
   along a vector.

   \param s The sign for 'v'.
   \param v Variable involved in the transform.
   \param vect Vector defining the displacement. 
   \param me The matrix equation to enlarge.
*/
void AddDispTrans2MEquation(int s,unsigned int v,
			    double *vect,TMequation *me);

/** 
   \brief Adds a Parametrized-Patch transform to a matrix equation.

   Adds a Parametrized-Patch transform to a matrix equation.

   \param t Subtype of PA transform (PA,dPA_U,dPA_V,ddPA_UU,d2PA_UV,ddPA_VV).
   \param s The sign of the transform (-1 means to invert the transform).
   \param u First variable (parameter) involved in the transform.
   \param v Second variable (parameter) involved in the transform.
   \param p The four points defining the patch.
   \param me The matrix equation to enlarge.
*/
void AddPatchTrans2MEquation(unsigned int t,int s,unsigned int u,unsigned int v,
			     double **p,TMequation *me);

/** 
   \brief Adds a constant transform to a matrix equation.

   Adds a constant transform at the end of a matrix equation.

   Note that identity transforms or matrices that result in identity
   transforms when added at the end of the sequence are skipped.

   \param t The transform to add.
   \param me The matrix equation to enlarge..
*/
void AddCtTrans2MEquation(THTransform *t,TMequation *me);

/** 
   \brief Concatenates a transform sequence to the matrix equation.

   Concatenates a transform sequence to the matrix equation.

   \param s The sign of the transform. If below 0, the tranform sequence
            has to be inverted before adding it.
   \param ts The transform to add.
   \param me The matrix equation to update.
*/
void AddTransSeq2MEquation(int s,TTransSeq *ts,TMequation *me);

/** 
   \brief Number of scaler equations defined by a matrix equation.
   
   Number of scaler equations defined by a matrix equation.

   \param me The matrix equation to check.

   \return Number of scaler equations defined by a matrix equation.
*/
unsigned int NumberScalarEquations(TMequation *me);

/** 
   \brief Adjust variable indices after removina a variable.

   After removing a variable not used in the system we have to
   shift down the  indices of the variables with larger index
   than the removed one.

   \param nv The removed variable.
   \param me The matrix equation.
*/
void  ShiftVariablesInMEquation(unsigned int nv,TMequation *me);

/** 
    \brief Set a variable to a constant value.

    Replaces a variable by a constant value. Used when simplifying
    problems.

    \param nv The identifier of the variable to replace.
    \param v The value to use.
    \param me The matrix equation to modify.

    \return  0: normal case  1: the equation becomes constant and it holds
             2: the equation becomes constant and it does not hold
*/
unsigned int FixVarInMEquation(unsigned int nv,double v,TMequation *me);

/** 
    \brief Replaces a variable.

    Replaces a variable by another variable. Used when simplifying
    problems.

    \param nv The identifier of the variable to replace.
    \param nvNew The identifier of the new variable.
    \param me The matrix equation to modify.
*/
void ReplaceVarInMEquation(unsigned int nv,unsigned int nvNew,TMequation *me);

/** 
   \brief Identifies simplified equations.

   Identifies simplified equations. The simplification is the last step in 
   the definition of a matrix equation. Only simplified equations can be added
   to cuiksystem.

   \param me The equation to query.

   \return TRUE if the equation is already simplified.
*/
boolean SimplifiedMEquation(TMequation *me);

/** 
   \brief Defines a translation matrix equation.

   Adjust the scalar equations considered in the matrix equation
   so that only the translation part is taken into account.

   IMPORTANT: This must be used AFTER calling \ref SimplifyMEquation
   since \ref SimplifyMEquation redefines the relevant equations.

   \param me The equation to modify.
*/
void MakeTranslationMEquation(TMequation *me);

/** 
  \brief Tries to reduce the complexity of the matrix equation.

  Performs operations in order to simplify the computations with
  the matrix equation. This should only be used when the matrix
  equation is fully defined. If new terms are added to the matrix
  equatoin after the simplification, the equation might become
  inconsistent.

  Right now we only simplify single transforms sequence equated
  to the identity. Other simplifications might be possible
  (i,e, move to the right hand side constant terms in the sum of
  matrix expressions). Howerver these cases are less frequent
  and, thus we do not consider them.

  \param me The equaton to simplify.
*/
void SimplifyMEquation(TMequation *me);

/** 
   \brief Mark the matrix equation as a velocity equation.

   Mark the matrix equation (and, thus, the scalar equations
   it encodes) as velocity equations. This can be used latter
   on to differencitate between velocity and non velocity
   equations. This is useful to selct parts of the Jacobian
   to evaluate. It may be even useful to evaluate the
   Jacobian in blocks (which will be more efficient).

   \param me The matrix equation to mark.
*/
void MarkAsVelocityMEquation(TMequation *me);

/** 
   \brief Identifes velocity matrix equations.

   Identify the matrix equations (and, thus, the scalar
   equations it encodes) that are velocity equation.

   \param me The matrix to query.
*/
boolean IsVelocityMEquation(TMequation *me);

/** 
   \brief Mark the matrix equation as a non-dynamic equation.

   Mark the matrix equation (and, thus, the scalar equations
   it encodes) as non-dynamic equations. 

   \param me The matrix equation to mark.
*/
void MarkAsNonDynamicMEquation(TMequation *me);

/** 
   \brief Identifes position matrix equations.

   Identify the matrix equations (and, thus, the scalar
   equations it encodes) that are position equation (i.e.,
   not velocity and not non-dynamic equations).

   \param me The matrix to query.
*/
boolean IsPositionMEquation(TMequation *me);

/** 
   \brief Identifes non-dynamic matrix equations.

   Identify the matrix equations (and, thus, the scalar
   equations it encodes) that are non-dynamic equation.

   \param me The matrix to query.
*/
boolean IsNonDynamicMEquation(TMequation *me);

/** 
   \brief Applies the un-simplification mapping to a matrix equation.

   Transform a matrix equation expressed in a simplified set of variables
   into an equation in the original set of variables.
   The relation between the two sets of variables is given by a
   mapping.

   \param map The mapping relating the two sets of variables.
   \param me The matrix equation to rewrite.

   \sa Tmapping
*/
void RewriteMEquation2Orig(Tmapping *map,TMequation *me);

/** 
   \brief Scales a matrix equation.

   Scales a matrix equation with a given variable.
   Right now, this is only used when generatin velocity equations.
   
   \param v The variable to use when scaling.
   \param me The matrix equation to scale.
*/
void ScaleMEquation(unsigned int v,TMequation *me);

/** 
   \brief Accumulates two matrix equations.

   Adds a possibly scaled matrix equation into another matrix equation.

   \param nv The optional scale variable. NO_UINT if scale is not given.
             Note that if given, the added matrix equation can not be
	     scaled.
   \param me1 The matrix equation to (scale and) add.
   \param me The matrix equation where to add the (scaled) other 
             matrix equation.
*/
void AccumulateMEquations(unsigned int  nv,TMequation *me1,TMequation *me);

/** 
   \brief Numerical double derivative of a matrix equation.

   Numerical double derivative of a matrix equation. This only works
   for matrix equations with a single term (not a sum of matrix products).

   \param neqs Total number of (independent) equations in the problem. 
               Gives the size of the output matrix.
   \param nvars Total number of variables in the problem.
                Gives the size of the output matrix.
   \param ce Current equation. Equation defined by the current
             matrix equation in the current system of equations.
   \param cie Current independent equation.
   \param independentEq Array indicating the independent equations
                        (the only ones to use).
   \param x The point where to evaluate the derivative.
   \param h Space where to store the results. This is a space of
            nvars matrices of size neqs x nvars where the matrix
	    is stored in a vector form. The space is
	    allocated for neqs but only the independent equations
	    are used.
   \param me The matrix to (numerically) derive.
*/
unsigned int NumericDDMatrixEquation(unsigned int neqs,unsigned int nvars,
				     unsigned int ce,unsigned int cie,
				     boolean *independentEq,
				     double *x,double **h,TMequation *me);

/** 
   \brief Transposed numerical derivative of a matrix equation.

   Transposed numerical derivative of a matrix equation. This only works
   for matrix equations with a single term (not a sum of matrix products).

   \param neqs Total number of (independent) equations in the problem. 
               Gives the size of the output matrix.
   \param nvars Total number of variables in the problem.
                Gives the size of the output matrix.
   \param ce Current equation. Equation defined by the current
             matrix equation in the current system of equations.
   \param cie Current independent equation.
   \param independentEq Array indicating the independent equations
                        (the only ones to use).
   \param x The point where to evaluate the derivative.
   \param m Output matrix. This is a nvars x neqs entries (i.e.,
            the transposed Jacobian).
   \param me The matrix to (numerically) derive.
*/
unsigned int TNumericDMatrixEquation(unsigned int neqs,unsigned int nvars,
				     unsigned int ce,unsigned int cie,
				     boolean *independentEq,
				     double *x,double *m,TMequation *me);

/** 
   \brief Derives a matrix equation.

   Derives a matrix equation. This results in one or more matrix
   product sequences equated to zero.

   \param v The derivation variable.
   \param dme The output derived matrix equation.
   \param me The matrix equation to derive.
*/
void DeriveMEquation(unsigned int v,TMequation *dme,TMequation *me);

/** 
   \brief Evaluates a matrix equation.
   
   Evaluates a matrix equation and stores the result on a given array.
   Note that the result only includes values for the scalar equations derived
   from the matrix equation.

   \param v Value for the variables.
   \param r The array where to store the results.
   \param me The matrix equation to evaluate.

   \return The number of output values stores in r (\sa NumberScalarEquations).
*/
unsigned int EvaluateMEquation(double *v,double *r,TMequation *me);

/** 
    \brief Equation x vector evaluation.

    Evalutes a matrix equation and returns the result of muliplying
    the resulting matrix with a set of 3D vectors.

    See \ref EvaluateJacobianXVectors why this is useful at all.

    \param v The value for the variables.
    \param n The number of vectors.
    \param p The 3D vectors (stacked in one array).
    \param r The output vector with the evaluation.
    \param me The matrix equation to use in the evaluation.
*/
void EvaluateMEquationXVectors(double *v,unsigned int n,double *p,
			       double *r,TMequation *me);

/** 
   \brief Prints a Transform sequence to a file.

   Prints a Transform sequence to a file.

   Note that we can print matrix equations which can not be actually
   parsed. Such equations are the ones internally generated (via
   derivation of when generating velocity equations). We do not
   parse such equations because they should never be in an input file.

   \param f The file.
   \param x The state. Only used for debug (to print the elements in a 
            matrix equation evaluated at a given point).
   \param varNames The variable names, if available (otherwise set thie
                   to NULL).
   \param me The matrix equation to print.
*/
void PrintMEquation(FILE *f,double *x,char **varNames,TMequation *me);

/** 
   \brief Destructor.

   Releases the memeory stored by a matrix equation.

   \param me The matrix equation to delete.
*/
void DeleteMEquation(TMequation *me);

#endif
