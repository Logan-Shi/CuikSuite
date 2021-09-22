#ifndef ALGEBRAH
#define ALGEBRAH

/** \file algebra.h

    Header of the lineal algebra routines used in the CuikSuite.

    This file includes high level routines which require LU or
    QR decompositions, and similar procedures.

   \sa algebra.c 
*/

#include "basic_algebra.h"

#if !defined(_LAPACK) && !defined(_GSL)
  #error CuikSuite requires LAPACK or GSL
#endif

#if !defined(_EXPOKIT)
  #error CuikSuite requires EXPOKIT (for matrix exponential)
#endif

/** 
   \brief Damped Newton process

   If 1, the Newton correction step is damped: it is multiplied
   by a factor alpha in [0,1] to reduce overshooting and to improve 
   converged.

   The alpha factor is initialized to DN_F and increased towards
   DN_MF using the DN_W weight at each step.

   Only experimental. Not actually used.
*/
#define DAMPED_NEWTON 0

/** 
   \brief Damping Newton initial factor.

   Initial value for the constant used to damp the Newton step.
*/
#define DN_F 0.1

/** 
   \brief Damping Newton maximum factor.

   Maximum value for the constant used to damp the Newton step.
*/
#define DN_MF 0.95

/** 
   \brief Damping Newton update ratio.

   Factor used to damp the Newton step.

   The update rule is alpha=alpha+DM_W*(DM_MF-alpha)
   with alpha initialized to DN_F.
*/
#define DN_W 0.25

#ifdef _GSL
  #include <gsl/gsl_linalg.h>

  /** 
      \brief Data structure used in the Newton iterations.

      Data structure used in each Newton iteration.
      
      Each Newton iteration solves the sytem A w = b

      The contents of this structure depends
      on the system used to solve the (under-determined) lineal system and of the
      lineal algebra library being used. 

      This definition assumes GSL and solves the lineal system
      using SVD and, thus we need some auxiliary variables (V,S) that are allocated
      once and re-used in the different iterations.
  */
  typedef struct {
    unsigned int nr;        /**< Number of rows (equations) of the matrix defining the  lineal system. */
    unsigned int nc;        /**< Number of columns (variables) of the matrix defining the lineal system. */

    double *Ab;             /**< Buffer where to store the matrix (nr x nc). */
    double *bb;             /**< Buffer where to store the RHs vector (nr). */

    gsl_matrix_view A;      /**< Matrix defining the lineal system. */
    gsl_vector_view b;      /**< Vector defining the lineal system. */

    gsl_matrix *V;          /**< Space for the V matrix of the SVD (nc x nc). */
    gsl_vector *S;          /**< Space for the eigen values (nc). */
    gsl_vector *tmp;        /**< Temporary space to compute the SVD (min{nr,nc}). */

    
    gsl_matrix_view VT;     /**< For wide matrices we have to compute SVD of A from that of A^t (nc x nr). */
    gsl_matrix_view UT;     /**< For wide matrices we have to compute SVD of A from that of A^t (nr x nr). */
    gsl_vector_view ST;     /**< For wide matrices we have to compute SVD of A from that of A^t (nr). */
    
    gsl_vector *w;          /**< Space for the solution of the lineal system. */
    
    #if (DAMPED_NEWTON)
      double alpha;         /**< Damping factor. Updated at each step. */
    #endif
  } TNewton;

  /** 
     \brief Data used when solving a linear system of equations.

     Data used when solving a well-constrained or over-constrained linear system of equations
     in the form A x = b.
     This is used when we use an iterative process where at each step we have to solve
     a linear system. This structure is used to allocate the data once (see \ref InitLS).
  */
  typedef struct {
    unsigned int nr;    /**< Number of rows of matrix A. */
    unsigned int nc;    /**< Number of columns of matrix A. */
    unsigned int nrh;   /**< Number of right hand terms. Number of columns of bb. */

    double *Ab;         /**< Buffer to store matrix A. */
    double *bb;         /**< Buffer to store vector/matrix b. */
    double *xb;         /**< Buffer to store vector/vector x. */ 
    
    gsl_matrix_view A;  /**< The A matrix. */
    gsl_vector_view b;  /**< The b vector. */
    gsl_vector_view x;  /**< The x vector. */

    gsl_permutation *p; /**< For squared systems we use a LU decomposition. */

    gsl_vector *tau;    /**< Auxiliary vector for the QR decomposition (only used
			     for overconstrained systems. */
    gsl_vector *res;    /**< Auxiliary vector for the QR decomposition (only used
		  	     for over-constrained system, i.e., nr>nc). */
    gsl_vector *work;   /**< Auxiliary vector to compute the condition number from
			     the QR decomposition. */
    
  } TLinearSystem;
#endif

#ifdef _LAPACK
  #ifdef _LAPACKE
    #include <lapacke.h>
  #else
    /* assuming clapack */
    #include <clapack.h>
  #endif
  /** 
      \brief Data structure used in the Newton iterations.

      Data structure used in each Newton iteration.
      
      Each Newton iteration solves the sytem A w = b

      The contents of this structure depends
      on the system used to solve the (under-determined) lineal system and of the
      lineal algebra library being used. 

      This definition assumes GSL and solves the lineal system
      using SVD and, thus we need some auxiliary variables (V,S) that are allocated
      once and re-used in the different iterations.
  */
  typedef struct {
    int nr;                 /**< Number of rows (equations) of the matrix defining the  lineal system. */
    int nc;                 /**< Number of columns (variables) of the matrix defining the lineal system. */

    double *Ab;             /**< Buffer where to store the matrix (nr x nc). */
    double *bb;             /**< Buffer where to store the RHs vector (nr). */

    double *s;              /**< Space for the eigenvalues. */

    int lwork;              /**< Size of the buffer 'work'. */
    double *work;           /**< Buffer for temporary operations. */
    
    #if (DAMPED_NEWTON)
      double alpha;         /**< Damping factor. Updated at each step. */
    #endif
  } TNewton;

  /** 
     \brief Data used when solving a linear system of equations.

     Data used when solving a well-constrained or over-constrained linear system of equations
     in the form A x =b.
     This is used when we use an iterative process where at each step we have to solve
     a linear system. This structure is used to allocate the data once (see \ref InitLS).
  */
  typedef struct {
    int nr;             /**< Number of rows of matrix A. */
    int nc;             /**< Number or columns of matrix A. */
    int nrh;            /**< Number of right hand terms. Columns in bb (and in xb). */

    double *Ab;         /**< Buffer to store matrix A. */
    double *bb;         /**< Buffer to store vector/matrix b. */
    double *xb;         /**< Buffer to store vector/matrix x. */ 
    
    int *p;             /**< Permutation (for nr==nc). */
    
    int lwork;          /**< Size of the buffer 'work' (for nr>nc). */
    double *work;       /**< Buffer for temporary operations (for nr>nc). */

    double *w;          /**< Space to compute condition number (4*nr).  */
    int *iw;            /**< Space to compute condition number (nr). */
    
  } TLinearSystem;
#endif

/** 
   \brief Broyden method.
   
   Implements th Broyden method: a quasi Newton method where the Jacobian matrix
   (Matrix Ab in the Newton structure) is not recomputed at each step but an intial
   estimation is adjusted using rank-one updates.

   Note that we implement only the Broyden method for squared matrices.
   Moreover, we implement the method that updates B and not B^-1. This
   second one may be faster, but requires an initial approximation of
   B^-1, which is not easily available.
*/
typedef struct {
  TLinearSystem ls;  /**< The newton structure. */
  unsigned int it;   /**< Iteration. */

  double *resp;      /**< Residue at the previous iteration. */
  double *r;         /**< Difference between residues. */
  double *p;         /**< Auxiliary vector to compute the rank-one update.*/

  double *An;        /**< LS Jacobian matrix. Direct pointer. */
  double *bn;        /**< LS residue vector. Direct pointer. */
  double *s;         /**< LS solution. Direct pointer. */
  
  double *B;         /**< Current Jacobian matrix. */
  double *res;       /**< Right hand side. Residue */
  
  unsigned int n;    /**< Number of rows/columns of B. */
} TBroyden;

/*******************************************************************************/
/* The functions below have different implemenatation depending on the helper  */
/* library being used (gsl, eigen, etc). In other words, these are the         */
/* functions to re-implement to change to another helper library.              */

/** 
   \brief Sign of the determinant of a matrix.

   Sign of the determinant of a squared matrix.
   
   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param epsilon Numerical accuracy. 
   \param n Number of rows/columsn of the matrix.
   \param A The matrix.
   
   \return The matrix determinant sign (-1,0,1).
*/
int MatrixDeterminantSgn(double epsilon,unsigned int n,double *A);

/** 
   \brief Determinant of a matrix.

   Determinant of a squared matrix.
   
   This function must be used with caution (only for small matrices) since
   the determinant can easily overflow.
   
   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param n Number of rows/columsn of the matrix.
   \param A The matrix.
   
   \return The matrix determinant.
*/
double MatrixDeterminant(unsigned int n,double *A);

/** 
   \brief Exponential of a matrix.

   Computes the exponential of a matrix (at a given
   time step).

   For a constant matrix A, the error of this function grows with the
   time 't'. Use with caution for large t's (i.e., 5, 10, is already large).

   \param m Number of rows/columsn of the matrix.
   \param A The matrix.
   \param t The time.
   \param eA The exponential of the matrix: exp(A*t).

   \return 1 if the process was succesful.
*/
unsigned int MatrixExponential(unsigned int m,double *A,double t,double *eA);

/** 
   \brief Exponential of a matrix and product by a vector.

   Computes the product of the exponential of a matrix with a vector
   at a given time step.

   For a constant matrix A, the error of this function grows with the
   time 't'. Use with caution for large t's because the error in
   this case scales much faster than when using \e MatrixExponential.
   In this case the error can be significative just
   for t=1. If accuracy is required (over speed) just use \e MatrixExponential
   and multiply the result by  vector \e v.

   \param m Number of rows/columsn of the matrix.
   \param A The matrix.
   \param t The time.
   \param v The input vector. Re-used to store the output: exp(A*t)*v.

   \return 1 if the process was succesful.
*/
unsigned int MatrixExponentialVector(unsigned int m,double *A,double t,double *v);

/** 
   \brief Determines the row-rank of a matrix.

   Determines the rank of a matrix, i.e. the dimension of the space
   spanned by the rows/column of the matrix.

   For a given problem, the number of variables minus the rank of 
   the Jacobian gives the dimensionality of the solution space, assuming
   that the Jacobian is evaluated in a regular point. The dimensionality
   of the solution space is the same as that of its tangent space.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param epsilon Numerical accuracy.
   \param nr Number of rows of the matrix (no transposed).
   \param nc Number of columns of the matrix (no transposed).
   \param mT The TRANSPOSED matrix. This matrix is overwriten 
             inside this function!!

   \return The rank of the matrix. NO_UINT if the rank can not be computed.
*/
unsigned int FindRank(double epsilon,unsigned int nr,unsigned int nc,double *mT);

/** 
   \brief Computes the kernel of a matrix.

   Defines a basis of the null space of a matrix.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param nr Number of rows of the matrix (no transposed).
   \param nc Numbe of columns of the matrix (no transposed).
   \param mT The TRANSPOSED matrix stored as a vector. This matrix is overwriten 
             inside this function!!
   \param dof Expected dimension of the kernel.
   \param check If TRUE the function introduces some consistancy checks (whether
                the kernel dimensionality is larger or smaller than the expected one).
   \param epsilon Values below epsilon are taken as zero.
   \param T The output kernel. This is a (nc x dof) matrix (stored as a vector). 
            The space for this matrix is allocated in this function but must be 
	    de-allocated externally.

   \return 0 if all the operations are correct,  1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined 
           since the kernel is too small at the given point, and 3 if there is an error while 
	   performing QR decomposition. These outputs come directly from \ref AnalyzeKernel.
*/
unsigned int FindKernel(unsigned int nr,unsigned int nc,double *mT,
			unsigned int dof,boolean check,double epsilon,double **T);

/** 
   \brief Computes the kernel and the rank of a matrix.

   Defines a basis of the null space of a matrix, without any clue about the dimension
   of this null space. The returne rank is actually the number of variables minus
   the dimension of such space.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param nr Number of rows of the matrix (no transposed).
   \param nc Numbe of columns of the matrix (no transposed).
   \param mT The TRANSPOSED matrix stored as a vector. This matrix is overwriten 
             inside this function!!
   \param rank The rank of the input matrix: number of variables (columns) minus
               dimension of the output null space (num columns of the matrix
	       representing the matrix).
   \param epsilon Values below epsilon are taken as zero.
   \param T The output kernel. This is a (nc x dof) matrix (stored as a vector). 
            The space for this matrix is allocated in this function but must be 
	    de-allocated externally.

   \return 0 if all the operations are correct and 3 if there is an error while 
	   performing QR decomposition. These outputs come directly from \ref AnalyzeKernel.
*/
unsigned int FindKernelAndRank(unsigned int nr,unsigned int nc,double *mT,
			       unsigned int *rank,double epsilon,double **T);  

/** 
   \brief Computes the kernel of a matrix and determines the independent rows of this matrix.

   Defines a basis of the null space of a matrix and determines a subset of the rows of the
   matrix that are independent.

   This is useful because in our case most (all?) the matrices have redundancy (i.e., rows
   that are linearly dependent on other rows).  However, for some purposes we need to 
   determine a subset of the rows that are linearly independent.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param nr Number of rows of the matrix (no transposed).
   \param nc Numbe of columns of the matrix (no transposed).
   \param mT The TRANSPOSED matrix stored as a vector. This matrix is overwriten 
             inside this function!!
   \param dof Expected dimension of the kernel. If zero, the function tries to determine
              the rank automatically.
   \param epsilon Values below epsilon are taken as zero.
   \param singular TRUE if the matrix is singular (has more null eigen values than
                   the expected ones). Output.
   \param IR The set of independent rows as a boolean vector with as many entriees as
             rows in the input matrix and TRUE for the independent rows. The space
	     for this vector is allocated here but must be deallocated externally.
	     If the matrix is singular this contains the most likely basis of the
	     matrix (up to the numerical accuracy). Caution must be taken to use
	     this output in this case.
   \param T The output kernel. This is a (nc x dof) matrix (stored as a vector). 
            The space for this matrix is allocated in this function but must be 
	    de-allocated externally.

   \return 0 if all the operations are correct,  1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined 
           since the kernel is too small at the given point, and 3 if there is an error while 
	   performing QR decomposition. These outputs come directly from \ref AnalyzeKernel.
*/
unsigned int FindKernelAndIndependentRows(unsigned int nr,unsigned int nc,double *mT,
					  unsigned int dof,double epsilon,boolean *singular,
					  boolean **IR,double **T);
/** 
   \brief Computes the independent rows of this matrix.

   Determines a subset of the rows of a matrix that are independent.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param nr Number of rows of the matrix (no transposed).
   \param nc Numbe of columns of the matrix (no transposed).
   \param mT The TRANSPOSED matrix stored as a vector. This matrix is overwriten 
             inside this function!!
   \param dof Expected dimension of the kernel. If zero, the function tries to determine
              the rank automatically.
   \param epsilon Values below epsilon are taken as zero.
   \param singular TRUE if the matrix is singular (has more null eigen values than
                   the expected ones). Output.
   \param IR The set of independent rows as a boolean vector with as many entriees as
             rows in the input matrix and TRUE for the independent rows. The space
	     for this vector is allocated here but must be deallocated externally.
	     If the matrix is singular this contains the most likely basis of the
	     matrix (up to the numerical accuracy). Caution must be taken to use
	     this output in this case.

   \return 0 if all the operations are correct,  1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined 
           since the kernel is too small at the given point, and 3 if there is an error while 
	   performing QR decomposition. These outputs come directly from \ref AnalyzeKernel.
*/
unsigned int FindIndependentRows(unsigned int nr,unsigned int nc,double *mT,
				 unsigned int dof,double epsilon,boolean *singular,
				 boolean **IR);

/** 
   \brief Inverse of a matrix.

  Computes the inverse of a matrix. 

  \param nr Number of rows (and columns) of the matrix.
  \param A A square matrix.   

  \return TRUE if the inverse is computed correctly. 
*/
boolean InvertMatrix(unsigned int nr,double *A);

/** 
   \brief Defines a Newton structure.

   Initializes the structure to be used in a iterative Newton process.

   Note that the dimensionality of the solution set can be deduced at
   each Newton step (using the QR with pivoting)  but it is more efficient
   if we know it beforehand.

   \param nr Number of rows.
   \param nc Number of columns.
   \param n The Newton structure to initialize.
*/
void InitNewton(unsigned int nr,unsigned int nc,TNewton *n);

/** 
    \brief Buffer to store the Newton matrix.
    
     Buffer to store the Newton matrix.

     This buffer must be accessed using the \ref RC2INDEX macro since
     the matrix can be stored row major or column major depending on the
     underlying lineal algebra library being used.

     \param n The Newton structure.

     \return A pointer to the buffer where to store the matrix.
*/
double *GetNewtonMatrixBuffer(TNewton *n);

/** 
    \brief Buffer to store the Newton right hand.
    
     Buffer to store the Newton RH.

     \param n The Newton structure.

     \return A pointer to the buffer where to store the RH.
*/
double *GetNewtonRHBuffer(TNewton *n);

/** 
   \brief Defines the matrix being used in a Newton step.

   Sets one element of the matrix to be used in one Newton step.
   This matrix is typically initilized externally, but here we provide
   a mehtod to set it.

   \param i The row.
   \param j The column.
   \param v The new value.
   \param n The Newton structure to set.
*/
void NewtonSetMatrix(unsigned int i,unsigned int j,double v,TNewton *n);

/** 
   \brief Defines the vector being used in a Newton step.

   Sets one element of the vector to be used in one Newton step.
   This vector is typically initilized externally, but here we provide
   a mehtod to set it.

   \param i The index in the vector.
   \param v The new value.
   \param n The Newton structure to set.
*/
void NewtonSetRH(unsigned int i,double v,TNewton *n);


/** 
   \brief One step in a Newton iteration.

   Computes and applies the correction in one step of a Newton iteration.

   This function allows to easily apply Newton processes just defining
   the input data (\e A, \e b), setting the initial value for \e x, and
   allocating space for the process. The space for the process is not
   allocated inside this function to avoid continous malloc/free calls
   since this function is typically used many times in a row.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param nullSingularValue Singular values below this are set to zero.
   \param x The current approximation to the system solution. This is
            updated internally.
   \param dif Norm of the change applied to \e x.
   \param n The Newton information.

   \return 0 if no error is encountered in the Newton step.
*/
int NewtonStep(double nullSingularValue,double *x,double *dif,
	       TNewton *n);

/** 
   \brief Releases a Newton structure.

   Releases the memory allocated for a Newton step.

   \param n A Newton structure.
*/
void DeleteNewton(TNewton *n);


/** 
   \brief Defines a Broyden structure.

   Initializes the structure to be used in a iterative Broyden process.

   Note that the dimensionality of the solution set can be deduced at
   each Broyden step (using the QR with pivoting)  but it is more efficient
   if we know it beforehand.

   \param nr Number of rows.
   \param nc Number of columns.
   \param b The Broyden structure to initialize.
*/
void InitBroyden(unsigned int nr,unsigned int nc,TBroyden *b);

/** 
   \brief Resets a Broyden structure.

   Resets the Broyden structure (the internal iteration) without
   releasing memory.

   \param b The Broyden structure to initialize.
*/
void ResetBroyden(TBroyden *b);

/** 
    \brief Buffer to store the Broyden matrix.
    
     Buffer to store the Broyden matrix.

     This buffer must be accessed using the \ref RC2INDEX macro since
     the matrix can be stored row major or column major depending on the
     underlying lineal algebra library being used.

     \param b The Broyden structure.

     \return A pointer to the buffer where to store the matrix.
*/
double *GetBroydenMatrixBuffer(TBroyden *b);

/** 
    \brief Buffer to store the Broyden right hand.
    
     Buffer to store the Broyden RH.

     \param b The Broyden structure.

     \return A pointer to the buffer where to store the RH.
*/
double *GetBroydenRHBuffer(TBroyden *b);
  
/** 
   \brief One step in a Broyden iteration.

   Computes and applies the correction in one step of a Broyden iteration.
   Calls the Newton iteration with the current Jacobian matrix and updates
   this matrix.

   The result is stored in the right-hand side buffer.

   \param epsilon Numerical accuracy.
   \param tp Topology of the variables.
   \param x The current approximation to the system solution. This is
            updated internally.
   \param b The Broyden information.

   \return 0 if no error is encountered in the Broyden step.
*/
int BroydenStep(double epsilon,unsigned int *tp,
		double *x,TBroyden *b);


/** 
   \brief Updates the approximated Jacobian.

   Applies the Broyden's Jacobian update procedure.
   This can only be used after using \ref BroydenStep at
   least once.

   \param epsilon The numerical accuracy.
   \param b The Broyden structure.
*/
void BroydenUpdateJacobian(double epsilon,TBroyden *b);
 

/** 
   \brief Releases a Broyden structure.

   Releases the memory allocated for a Broyden step.

   \param b A Broyden structure.
*/
void DeleteBroyden(TBroyden *b);


/** 
   \brief Defines a linear system structure.

   Initializes the structure to be used when solving a linear system.
 
   \param nr Number of rows.
   \param nc Number of columns.
   \param nrh Number of right hand terms.
   \param ls The linear system structure to initialize.
*/
void InitLS(unsigned int nr,unsigned int nc,unsigned int nrh,TLinearSystem *ls);

/** 
    \brief Buffer to store the A matrix.
    
     Buffer to store the A matrix.

     This buffer must be accessed using the \ref RC2INDEX macro since
     the matrix can be stored row major or column major depending on the
     underlying lineal algebra library being used.

     \param ls The linear system structure.

     \return A pointer to the buffer where to store the matrix.
*/
double *GetLSMatrixBuffer(TLinearSystem *ls);

/** 
    \brief Buffer to store the linear system right hand (RH).
    
     Buffer to store the linear system RH.

     \param ls The linear system structure.

     \return A pointer to the buffer where to store the RH.
*/
double *GetLSRHBuffer(TLinearSystem *ls);

/** 
    \brief Buffer to store the linear system solution.
    
     Buffer to store the linear sytem solution. Note that
     this maybe the same as the buffer for the rhs.

     \param ls The linear system structure.

     \return A pointer to the buffer where to store the solution.
*/
double *GetLSSolutionBuffer(TLinearSystem *ls);

/** 
   \brief Defines the matrix being used in a linear system.

   Sets one element of the matrix to be used in a linear system.

   \param i The row.
   \param j The column.
   \param v The new value.
   \param ls The linear system structure.
*/
void LSSetMatrix(unsigned int i,unsigned int j,double v,TLinearSystem *ls);

/** 
   \brief Defines the vector being used in a linear system.

   Sets one element of the right hand vector of a linear system.

   \param i The row index.
   \param j The column index.
   \param v The new value.
   \param ls The linear system structure.
*/
void LSSetRH(unsigned int i,unsigned int j,double v,TLinearSystem *ls);

/** 
   \brief Solves the linear sytem.

   Computes the solution of a linear system.

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param ls The linear system to solve.
	      
   \return 0 if no error is encountered when solving the system.
*/
int LSSolve(TLinearSystem *ls);

/** 
   \brief Solves the linear sytem.

   Computes the solution of a linear system only and returns the the reciprocal of the condition 
   number of the system matrix. This provides information about the confidence in the solution
   (solutions with low condition number are not reliable).

   Since we compute 1 / ( norm(A) * norm(inv(A)) ), we only implement this option for 
   squared systems (otherwise inv(A) would not be defined).

   IMPORTANT: The intput matrix may be modified inside this function. The caller
              CAN NOT assume that it remains unchanged.

   \param rcond The condition number. Returned mainly for debugging purposes. 
   \param ls The linear system to solve.
	      
   \return 0 if no error is encountered when solving the system.
*/
int LSSolveCond(double *rcond,TLinearSystem *ls);

/** 
   \brief Releases a linear system structure.

   Releases the memory allocated for a linear system.

   \param ls A linear system structure. 
*/
void DeleteLS(TLinearSystem *ls);

#endif

#ifdef _LAPACK



#endif
