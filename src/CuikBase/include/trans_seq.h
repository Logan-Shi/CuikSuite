#ifndef TRANS_SEQH
#define TRANS_SEQH

#include "htransform.h"
#include "csmapping.h"
#include "boolean.h"

#include <stdio.h>

/** \file trans_seq.h
    \brief Sequence (product) of homogeneous transforms.

    Sequence (product) of homogeneous transforms including constant and
    variable terms. Used to defined matrix equations.

    \sa TTransSeq, trans_seq.c.
*/

/** \brief Simplify sequences.

    If set, the tranform sequences are simplified removing constant
    terms at the end (they are accumulated at the beginning)

    \sa SimplifyTransSeq
*/
#define SIMPLIFY_TS 1

/** \brief Displacement along a vector.

    Displacement along a vector. The vector is stored in the form
    of a constant transform.
*/
#define TV (RZ+1)

/** \brief Point on a patch.

    Point on a patch given by two parameters. This defines
    a parametrized transform.
*/
#define PA (TV+1)

/** \brief Constant transform.

    One of the possible transforms in the sequence.
    These are added to the types of transforms defined in \ref htransform.h
*/
#define CT_TRANS (PA+1)

/** \brief Derivative of a Rx transform.

    Derivative of a Rx transform.
*/
#define dRX (CT_TRANS+1)

/** \brief Derivative of a Ry transform.

    Derivative of a Rx transform.
*/
#define dRY (dRX+1)

/** \brief Derivative of a Rz transform.

    Derivative of a Rx transform.
*/
#define dRZ (dRY+1)

/** \brief Derivative of a PA transform.

    Derivative of a PA transform with respect to the
    first parameter.
*/
#define dPA_U (dRZ+1)

/** \brief Derivative of a PA transform.

    Derivative of a PA transform with respect to the
    second parameter.
*/
#define dPA_V (dPA_U+1)

/** \brief Double derivative of a Rx transform.

    Double derivative of a Rx transform.
*/
#define ddRX (dPA_V+1)

/** \brief Double derivative of a Rx transform.

    Double derivative of a Ry transform.
*/
#define ddRY (ddRX+1)

/** \brief Double derivative of a Rx transform.

    Double derivative of a Rz transform.
*/
#define ddRZ (ddRY+1)

/** \brief Double derivative of a PA transform.

    Double derivative of a PA transform with respect to the
    first parameter.
*/
#define ddPA_UU (ddRZ+1)

/** \brief Double derivative of a PA transform.

    Derivative of a PA transform with respect to the
    first parameter and then with respect to the second
*/
#define ddPA_UV (ddPA_UU+1)

/** \brief Double derivative of a PA transform.

    Double derivative of a PA transform with respect to the
    second parameter.
*/
#define ddPA_VV (ddPA_UV+1)

/** \brief Initial room for terms in a transform sequence. 

    Initial room for terms in a transform sequence. It will be enlarged if necessary.

    \sa TTransSeq
*/
#define INIT_NUM_TERMS_TS 10

/** 
   \brief Checks if a transform is a parametrized patch (or derived).

    Checks if a transform is a parametrized patch or a derived transform.

   \param t The type of transform to check.
*/
#define IS_PATCH_TRANS(t) ((t==PA)||(t==dPA_U)||(t==dPA_V)||(t==ddPA_UU)||(t==ddPA_UV)||(t==ddPA_VV))

/** 
   \brief A step in a transform sequence.

   A step in a transform sequence. Defined here to
   simplify the definition of \ref TTransSeq (TTranSeq methods
   would have direct access to the elements in TTrans, but
   it is easy to add 
*/
typedef struct {
  unsigned int t;  /**< Type of transform. */
  unsigned int v;  /**< First variable involved in the transform. */
  unsigned int u;  /**< Second variable involved in the transform. Only
		        used in Parametrized-Patch transforms */
  double val;      /**< If either variable \e v or \e u are fixed but the other
		        variable is still free, the value of the fixed
		        variable is stored here. If both variables are fixed,
		        the transform is constant. This only make sense for
		        PA-like transform where which use two variables.
		        The rest of transforms become constant if one variable
		        is fixed. */
  int s;           /**< Sign of the transform. If negative the transform
		        has to be inverted */
  THTransform *ct; /**< Constant transforms. One per transform. For variable
		        transforms is not used.*/
  double *vect;    /**< Displacement vector for TV transforms */
  double **p;      /**< Auxiliary 3D points associated with the transform.
		        Only used for Parametrized-Patch transforms */
} TTrans;

/** 
   \brief Initializes a constant transform.

   Initializes a constant transform.

   \param ct The constant transform.
   \param t The transform to initialize.
*/
void InitCtTrans(THTransform *ct,TTrans *t);

/** 
   \brief Initializes a variable transform.

   Initializes a variable transform (all variable transforms but
   those of type TV or PA).

   \param tp The type of transform.
   \param s The sign of the transform (-1 to invert the transform).
   \param v The variable involved in the transform.
   \param t The transform to initialize.
*/
void InitVarTrans(unsigned int tp,int s,unsigned int v,TTrans *t);

/** 
   \brief Initializes a TV transform.

   Initializes a TV transform: a displacement along a vector
   scaled by a variable.

   \param s The sign of the transform (-1 to invert the transform).
   \param v The variable involved in the transform.
   \param vect Vector giving the displacement direction.
   \param t The transform to initialize.
*/
void InitTVTrans(int s,unsigned int v,double *vect,TTrans *t);

/** 
   \brief Initializes a parametrized-patch transform.

   Initializes a parametrized-patch transform.

   Note that the given points are NOT the vertices defining the patch but
   some combinations of them
        - p_0
	- p_1-p_0
	- p_2-p_0
	- p_0-p_1-p_2+p_3
	.
   
   \param tp Subtype of PA transform (PA,dPA_U,dPA_V,ddPA_UU,d2PA_UV,ddPA_VV).
   \param s The sign of the transform (-1 to invert the transform).
   \param u The first variable (parametre) of the parametrized-patch transform.
   \param v The second variable (parametre) of the parametrized-patch transform.
   \param p The 4 auxiliary points defining the patch. If we define a
            PA transform these are the four points defining its
	    extremes. Otherwise, these are points derived from those
	    original points.
   \param t The transform to initialize.
*/
void InitPatchTrans(unsigned int tp,int s,unsigned int u,unsigned int v,
		    double **p,TTrans *t);

/** 
   \brief Constructor.

   Initializes a transform form another transform.
*/
void CopyTrans(TTrans *t_dst,TTrans *t_src);

/** 
   \brief Invert a transform.

   Invert a transform.

   \param ti The resulting inverted transform.
   \param t The transform to invert.
*/
void TransInvert(TTrans *ti,TTrans *t);

/** 
   \brief Identifies if a variable is involved in a given transform.

   Checks if a variable is involved in a given transform.

   \param v The variable to check.
   \param t The transform to query.

   \return TRUE if the variable is involved in the transform.
*/
boolean TransHasVar(unsigned int v,TTrans *t);

/** 
   \brief Computes the vectors defining a PA transform.

    Computes the basic, unnormalized vectors defining a PA transform. 
    This can be applied to PA transforms
    and to their derivatives (dPA_U, dPA_V, ddPA_UU, ddPA_UV, and ddPA_VV)
    BUT in all cases it returns the vector for the original PA

    \param u Value for the 1st parameter.
    \param v Value for the 2nd parameter.
    \param x Output vector with the non-normalized 1st column of the transform.
    \param y Output vector with the non-normalized 2nd column of the transform.
    \param h Output vector with the 4th column of the transform (translation).
    \param t The PA-like transform to evaluate.
*/
void EvaluateVectorsPATrans(double u,double v,double *x,double *y,double *h,TTrans *t);

/** 
    \brief Evaluates a transform.

    Computes the homogeneous transform corresponding to a given variable
    transform given values for the involved variables.

    If used on a constant transform, the constant matrix is returned.

    \param v1 Value of the first variable of the transform. This
              is the value of variable \e v, except for PA-like transform.
    \param v2 Value of the second variable of the transform. Only used
             in PA-like transforms. This is the value of variable \e u,
	     except for PA-like transforms. Sorry for the mesh.
    \param a The output homogeneous transform.
    \param t The transform to evaluate.
*/
void EvaluateTrans(double v1,double v2,THTransform *a,TTrans *t);

/** 
    \brief Evaluates the derivative of a transform.

    Computes the homogeneous transform corresponding to the 
    derivative of a given variable transform with respect to 
    the variable involved in the transform.
    The derivative is evaluated numericaly (for the given values 
    for the involved variables) and not symbolically.

    Note that this is not yet implemented for all types of
    transforms, but only for transforms involving only one
    variable. For other transforms it triggers an error.

    \param v1 Value of the first variable of the transform.
    \param v2 Value of the second variable of the transform. Only used
             in PA-like transforms. Actually this is not used since
	     right now this methods is only implemented for transforms
	     involving only one variable.
    \param a The output homogeneous transform.
    \param t The transform to evaluate.
*/
void EvaluateDTrans(double v1,double v2,THTransform *a,TTrans *t);

/** 
    \brief Evaluates the double derivative of a transform.

    Computes the homogeneous transform corresponding to the 
    double derivative of a given variable transform
    with respect to the variable involved in the transform. 
    The derivative is evaluated numericaly (for the given values 
    for the involved variables) and not symbolically.

    Note that this is not yet implemented for all types of
    transforms, but only for transforms involving only one
    variable. For other transforms it triggers an error.

    \param v1 Value of the first variable of the transform.
    \param v2 Value of the second variable of the transform. Only used
             in PA-like transforms.Actually this is not used since
	     right now this methods is only implemented for transforms
	     involving only one variable.
    \param a The output homogeneous transform.
    \param t The transform to evaluate.
*/
void EvaluateDDTrans(double v1,double v2,THTransform *a,TTrans *t);

/** 
   \brief Evaluates a PA transform.

    Evaluates a PA transform. This can be applied to PA transforms
    and to their derivatives (dPA_U, dPA_V, ddPA_UU, ddPA_UV, and ddPA_VV)
    BUT in all cases it returns the evaluation of the original PA

    \param u Value for the 1st parameter.
    \param v Value for the 2nd parameter.
    \param a The resulting transform (inverted if the transform is 
             "negative".
    \param t The PA-like transform to evaluate.

    \sa EvaluateVectorsPATrans.
*/
void EvaluatePATrans(double u,double v,THTransform *a,TTrans *t);

/** 
   \brief Destructor.

   Releases the memory used in a transform.

   \param t The transform to delete.
*/
void DeleteTrans(TTrans *t);

/** 
  \brief A sequence of transforms.

  A sequence (product) of homogeneous transforms including constant and
  variable terms. This is used to define matrix equations.
  
  This is somehow equivalent to the Tvariable_set for scalar equations: it
  is a product (in sequence) of functions applied to variables that is latter
  used to define equations.

 \sa trans_seq.h
*/
typedef struct {
  unsigned int m;     /**< Max transforms involved in the sequence. */
  unsigned int n;     /**< Number of transforms in the sequence. */
  TTrans **t;         /**< The transforms. */
} TTransSeq;

/** 
   \brief Constructor.

   Initializes an empty sequence of transforms.

   \param ts The transform sequence to initilize.
*/
void InitTransSeq(TTransSeq *ts);

/** 
   \brief Constructor.

   Copy constructor.

   \param ts_dst The sequence to initialize.
   \param ts_src the sequence from where to copy.
*/
void CopyTransSeq(TTransSeq *ts_dst,TTransSeq *ts_src);

/** 
   \brief Semi-destructor.

   Resets a sequence of transforms. Removes all the
   elements but does not release memory.

   \param ts The transform sequence to reset.
*/
void ResetTransSeq(TTransSeq *ts);

/** 
    \brief Identify empty transform sequences.

    Identifies empty transform sequences.

    \param ts The transform sequence to check.
*/
boolean IsEmptyTransSeq(TTransSeq *ts);

/** 
    \brief Maximum numbr of variables in the transforms.

    Returns the maximum number of variables in the
    transform sequence.

    \param ts The transform sequence to check.

    \return The maximum number of variables in each transform.
*/
unsigned int TransSeqMaxVars(TTransSeq *ts);

/** 
   \brief Identifies transform sequences with repeated variables.

   Transform sequences with repeated variables yield more complex
   derivatives. This function identifies them.

   \param ts The transform sequence to check.

   \return TRUE if the sequence has repeated varaibles.
*/
boolean HasRepeatedVar(TTransSeq *ts);

/** 
   \brief Checks if the tranform sequence includes contant rotations.

   Determines if the transform sequence includes a rotation among
   its constants elements.

   Transform sequences without constant rotations are typicaly used
   in planar manipulators. We want to detect them in order to
   avoid considering redundant equations.

   \param ts The transforms sequence to check.
   
   \return TRUE if the sequence includes at least one constnat rotation.
*/
boolean HasCtRotTransSeq(TTransSeq *ts);

/** 
   \brief Number of elements in the transform sequence.

   Number of elements in the transform sequence.

   \param ts The transform sequence to query.

   \return Number of elements in the transform sequence.
*/
unsigned int TransSeqSize(TTransSeq *ts);

/** 
   \brief Returns an element from a transform sequence.

   Returns an element from a transform sequence.

   \param i The index of the transform to retrive.
   \param ts The transform sequence to query.

   \return A pointer to the trans structure. Be careful with the use
           of this pointer.
*/
TTrans *GetElementFromTransSeq(unsigned int i,TTransSeq *ts);

/** 
   \brief Adds a transform to a transform sequence.
   
    Adds a transform to a transform sequence.

    \brief t The transform to add.
    \brief ts The sequence where to add the transform.
*/
void AddTrans2TransSeq(TTrans *t,TTransSeq *ts);

/** 
   \brief Adds a constant transform to the sequence.

   Adds a constant transform at the end of a transform sequence.

   Note that identity transforms or matrices that result in identity
   transforms when added at the end of the sequence are skipped.

   \param t The transform to add.
   \param ts The transform sequence to enlarge.
*/
void AddCtTrans2TransSeq(THTransform *t,TTransSeq *ts);

/** 
   \brief Adds a variable transform to the sequence.

   Adds a variable transform at the end of a transform sequence.

   \param t Type of transform.
   \param s The sign of the variable.
   \param v Variable involved in the transform.
   \param ts The transform sequence to enlarge.
*/
void AddVarTrans2TransSeq(unsigned int t,int s,unsigned int v,TTransSeq *ts);

/** 
   \brief Adds a displacement transform to the sequence.

   Adds a variable scaled displacement along a vector.

   \param s The sign of the variable.
   \param v Variable involved in the transform.
   \param vect Vector defining the displacement. Used only for Tv Transforms.
   \param ts The transform sequence to enlarge.
*/
void AddDispTrans2TransSeq(int s,unsigned int v,double *vect,TTransSeq *ts);

/** 
   \brief Adds a Parametrized-Patch transform to a transform sequence.

   Adds a Parametrized-Patch transform to a transform sequence.

   \param t Subtype of PA transform (PA,dPA_U,dPA_V,ddPA_UU,d2PA_UV,ddPA_VV).
   \param s The sign of the transform (-1 means to invert the transform).
   \param u First variable (parameter) involved in the transform.
   \param v Second variable (parameter) involved in the transform.
   \param p The four points defining the patch.
   \param ts The transform sequence to enlarge.
*/
void AddPatchTrans2TransSeq(unsigned int t,int s,unsigned int u,unsigned int v,
			    double **p,TTransSeq *ts);

/** 
   \brief Determines if the sequence includes a given variable.
   
   Determines if the sequence includes a given variable. Used in the
   derivation of transform sequence.
   
   \param v The variable identifier.
   \param ts The transform sequence to check.
*/
boolean VarIncludedinTransSeq(unsigned int v,TTransSeq *ts);

/** 
   \brief Determines the dof used in a transform sequence.

   Determines the dof used in a transform sequence. This is done by adding
   the transforms used in each degree of freedom into a given array.

   \param dof 6-dim array where we add the types of dof used in the
          transform sequence.
   \param ts The transform sequence to analyze.
*/
void UpdateUsedDOF(unsigned int *dof,TTransSeq *ts);

/** 
   \brief Adjust variable indices after removing a variable.

   After removing a variable not used in the system we have to
   shift down the  indices of the variables with larger index
   than the removed one.

   This triggers an error if the variable is actually in use
   in the transform sequence.

   \param nv The removed variable.
   \param ts The transform sequence to update.
*/
void ShiftVariablesInTransSeq(unsigned int nv,TTransSeq *ts);

/** 
    \brief Set a variable to a constant value.

    Replaces a variable by a constant value. Used when simplifying
    problems.

    \param nv The identifier of the variable to replace.
    \param v The value to use.
    \param ctt The transform when the transformation sequence becomes
             constant (output 1 or 2).
    \param ts The transform sequence to modify.

    \return  TRUE if the transform became constant.
*/
boolean FixVarInTransSeq(unsigned int nv,double v,THTransform *ctt,TTransSeq *ts);

/** 
    \brief Replaces a variable.

    Replaces a variable by another variable. Used when simplifying
    problems.

    \param nv The identifier of the variable to replace.
    \param nvNew The identifier of the new variable.
    \param ts The transform sequence to modify.
*/
void ReplaceVarInTransSeq(unsigned int nv,unsigned int nvNew,TTransSeq *ts);

/** 
   \brief Applies the un-simplification mapping to a transform sequence.

   Transform a transform sequence expressed in a simplified set of variables
   into the equivalent sequence in the original set of variables.
   The relation between the two sets of variables is given by a
   mapping.

   \param map The mapping relating the two sets of variables.
   \param ts The transform sequenceto rewrite.

   \sa Tmapping
*/
void RewriteTransSeq2Orig(Tmapping *map,TTransSeq *ts);

/** 
   \brief Reduces the complexity of the tranform sequence.

   Accumulates the constant transform at the end of the sequence with
   the first one (if this is also constant). This produces no change in
   the expression if the transform sequence is equal to the identity.
   otherwise the change is dramatic and the simplification is not
   valid.

   This is only used from SimplifyMEquation. Do not use in
   another context.

   \param ts The transform sequence to simplify.
*/
void SimplifyTransSeq(TTransSeq *ts);

/** 
   \brief Transposed numerical derivative of a sequence of transforms.

   Transposed numerical derivative of a sequence of transforms.

   \param neqs Total number of (independent) equations in the problem. 
               Gives the size of the output matrix.
   \param nvars Total number of variables in the problem.
                Gives the size of the output matrix.
   \param nse Number of scalar equations in the matrix product.
   \param r Rows of the scalar equations.
   \param c Columns of the scalar equations.
   \param ce Current equation. Equation defined by the current
             matrix equation in the current system of equations.
   \param cie Current independent equation.
   \param independentEq Array indicating the independent equations
                        (the only ones to use).
   \param x The point where to evaluate the derivative.
   \param m Output matrix. This is a nvars x neqs entries (i.e.,
            the transposed Jacobian). We only fill in part of it.
   \param ts The transform sequence to (numerically) derive.
*/
unsigned int TNumericDTransSeq(unsigned int neqs,unsigned int nvars,
			       unsigned int nse,unsigned int *r,unsigned int *c,
			       unsigned int ce,unsigned int cie,
			       boolean *independentEq,
			       double *x,double *m,TTransSeq *ts);

/** 
   \brief Numerical double derivative of a sequence of transforms.

    Numerical double derivative of a sequence of transforms.

   \param neqs Total number of (independent) equations in the problem. 
               Gives the size of the output matrix.
   \param nvars Total number of variables in the problem.
                Gives the size of the output matrix.
   \param nse Number of scalar equations in the matrix product.
   \param r Rows of the scalar equations.
   \param c Columns of the scalar equations.
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
   \param ts The transform sequence to (numerically) derive.
*/
unsigned int NumericDDTransSeq(unsigned int neqs,unsigned int nvars,
			       unsigned int nse,unsigned int *r,unsigned int *c,
			       unsigned int ce,unsigned int cie,
			       boolean *independentEq,
			       double *x,double **h,TTransSeq *ts);

/** 
   \brief Derive a sequence of transforms.

   Derive a sequence of transforms with respect to a given variable

   If a given sequence includes the same variable more than once, the output
   can be a set of transform sequences 
   (basically diff(a*b) = diff(a) *b + a * diff(b))

   \param v The derivation variable
   \param n Number of transform sequences returned
   \param tsd The derived sequences (initialized internally. not initialized
              if the variable is not used in the given sequence).
   \param ts the sequence to derive.
*/
void DeriveTransSeq(unsigned int v,unsigned int *n,TTransSeq ***tsd,TTransSeq *ts);

/** 
   \brief Evaluates the transform sequence.

   Evaluates the transform sequence given some values for the variables.

   \param v The variable values.
   \param r The resulting transform.
   \param ts The transform sequence to evaluate.
*/
void EvaluateTransSeq(double *v,THTransform *r,TTransSeq *ts);

/** 
   \brief Prints a transform sequence to a file.

   Prints a transform sequence to a file.

   \param f The file.
   \param x The state. Only used for debug.
   \param varNames The variable names, if available (otherwise set thie
                   to NULL).
   \param ts The transform sequence to print.
*/
void PrintTransSeq(FILE *f,double *x,char **varNames,TTransSeq *ts);

/** 
   \brief Destructor.

   Deleltes a transform sequence.

   \param ts The transform sequence to delete.
*/
void DeleteTransSeq(TTransSeq *ts);

#endif
