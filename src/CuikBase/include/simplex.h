#ifndef SIMPLEXH
#define SIMPLEXH

#include "box.h"
#include "interval.h"
#include "linear_constraint.h"
#include "equation.h"

#if (_SIMPLEX_ENGINE==_GUROBI)
  #include "vector.h"
  #include <gurobi_c.h>  
  /** 
     \brief Encapsulate the Gurobi environment and model.
  */
  typedef struct {
    GRBenv   *env;      /**< The environment. */
    GRBmodel *model;    /**< The model. */
    unsigned int ncols; /**< The number of variables. */
    unsigned int nAdded;/**< Number of slack variables added. */
    unsigned int nrows; /**< Number of constraints. */
    Tvector rangeVar;   /**< Indices of the variables used to
			     represent row ranges (for double bounded constraints). */
  } Tgurobi;
  /** 
     \brief The simples tableau type when using 
            <A HREF="http://www.gurobi.com">Gurobi</A>.
  */
  #define SimplexType Tgurobi
#endif

#if (_SIMPLEX_ENGINE==_CLP)
  #include <coin/Clp_C_Interface.h>  
  /** 
     \brief The simples tableau type when using 
            <A HREF="http://www.coin-or.org/projects/Clp.xml">Clp</A>.
  */
  #define SimplexType __attribute__ ((aligned(8))) Clp_Simplex
#endif

#if (_SIMPLEX_ENGINE==_GLPK)
  #include <glpk.h>
  /** 
     \brief The simples tableau type when using 
            <A HREF="http://www.gnu.org/software/glpk/">Glpk</A>.
  */
  #define SimplexType LPX
#endif

#if (_SIMPLEX_ENGINE==_LP_SOLVE)
  #include <lp_solve/lp_lib.h>
  /** 
     \brief The simples tableau type when using 
            <A HREF="http://sourceforge.net/projects/lpsolve">Lp_solve</A>.
  */
  #define SimplexType lprec
#endif

/** 
   \file simplex.h

   \brief Definition of the TSimplex type and the associated functions. 

   Definition of the TSimplex type and the associated functions. This interface
   is common to the different simplex engines. To add a new simplex engine 
   you have to re-implement these functions for the new engine.<br>
   Right now we have three possible simplex backends
   - <A HREF="http://www.coin-or.org/projects/Clp.xml">Clp</A>: See simplex_clp.c for the implementation.
   - <A HREF="http://www.gnu.org/software/glpk/">Glpk</A>: See simplex_glpk.c for the implementation.
   - <A HREF="http://sourceforge.net/projects/lpsolve">Lp_solve</A>: See simplex_lpsolve.c for the implementation.
   .

   Clp is the preferred option. The rest of options are either experimental or
   tested many years ago (with ancient versions of the simplex libraries).
   It is not difficult to update these interfaces, but it is not our priority now
   (we leave this as an exercise for the reader).

   \sa TSimplex, simplex_clp.c, simplex_glpk.c,  simplex_lpsolve.c.
*/

/************************************************************************************/
/** \brief Simplex timeout.

    Maximum time (in seconds) we give the simplex process to return a solution when
    minimizing/mazimizing for a single variable.
   
    This figure is scaled by the number of columns in the simplex.
*/
#define SIMPLEX_TIMEOUT  10
/************************************************************************************/

/** 
   \brief A simplex tableau structure.

   A simplex tableau structure.
   
   \sa simplex.h, simplex_clp.c, simplex_glpk.c,  simplex_lpsolve.c.
 */
typedef struct {

  SimplexType *lp; /**< The simplex tableau. */

  #if (_SIMPLEX_ENGINE==_CLP)
    unsigned int fakeRows; /**< Number of fake rows added to the tableau (only used when using
			      <A HREF="http://www.coin-or.org/projects/Clp.xml">Clp</A>). */
    double *lower; /**< Lower limit for the variables.*/
    double *upper; /**< Upper limit for the variables. */
    double *obj; /**< Objective coefficients. */
  #endif

  #if (_SIMPLEX_ENGINE==_LP_SOLVE)
    double inf; /**< Cached value for infinite (only used when using
		     <A HREF="http://sourceforge.net/projects/lpsolve">Lp_solve</A>). */
  #endif

} TSimplex;

/* Functions implemented in particular for each simplex engine
   (GLPK,CLP,...) in simplex_glpk.c simplex_clp.c,.... */

/** 
   \brief Constructor.

   Creates a simplex structure with a given number of columns (i.e., variables) but with
   no rows (i.e., constraints).

   \param epsilon Threshold to decide if a value is too small to be added to the
                  tableau. It is also used to set up internal simplex parameters.
   \param ncols Number of columns for the tableau.
   \param s The simplex structure.
 */
void SimplexCreate(double epsilon,unsigned int ncols,TSimplex *s);


/** 
   \brief Resets the simplex structure.

   Reset the internal information of the simplex structure.
   This is sometimes used in case of errors to improve stability.

   \param s The simplex structure.
 */
void ResetSimplex(TSimplex *s);

/** 
   \brief Gets the number of columns (i.e., variables) of the simplex structure.

   Gets the number of columns (i.e., variables) of the simplex structure.

   \param s The simplex structure.

   \return The number of columns (i.e., variables) of the simplex structure.
 */
unsigned int SimplexNColumns(TSimplex *s);


/** 
   \brief Gets the number of rows (i.e., constraints) of the simplex structure.

   Gets the number of rows (i.e., constraints) of the simplex structure.

   \param s The simplex structure.

   \return The number of rows (i.e., constraints) of the simplex structure.
 */
unsigned int SimplexNRows(TSimplex *s);

/** 
   \brief Sets the bounds for a given column (i.e., variable).

   Sets the bounds for a given column (i.e., variable).

   \param ncol The column whose range we have to update.
   \param epsilon The minimum ranges width. Numerical accuracy.
   \param i The new range for the column.
   \param s The simplex structure.
 */
void SimplexSetColBounds(unsigned int ncol,double epsilon,Tinterval *i,TSimplex *s);

/** 
   \brief Gets the bounds for a given column (i.e., variable).

   Gets the bounds for a given column (i.e., variable).

   \param ncol The column whose range we have to update.
   \param i The output range with the column bounds.
   \param s The simplex structure.
 */
void SimplexGetColBounds(unsigned int ncol,Tinterval *i,TSimplex *s);

/** 
   \brief Gets a column from the simplex in the form of a linear constraint.

   Gets a column from the simplex in the form of a linear constraint.

   \param ncol The column whose constraint we want to get.
   \param lc The output linear constraint.
   \param s The simplex structure.
 */
void SimplexGetColConstraint(unsigned int ncol,TLinearConstraint *lc,TSimplex *s);

/** 
   \brief Checks if a simplex column is empty.

   Gets a column constraint from the simplex.

   \param ncol The column whose constraint we want to get.
   \param s The simplex structure.
   
   \return TRUE if the simplex column is empty.
 */
boolean SimplexColEmpty(unsigned int ncol,TSimplex *s);

/** 
   \brief Get the lower bounds for all rows.

   Get the lower bounds for all rows.

   \param lower The space to store the lower bounds.
   \param s The simplex structure to query.
*/
void SimplexGetRowsLowerBounds(double *lower,TSimplex *s);

/** 
   \brief Get the upper bounds for all rows.

   Get the upper bounds for all rows.

   \param upper The space to store the upper bounds.
   \param s The simplex structure to query.
*/
void SimplexGetRowsUpperBounds(double *upper,TSimplex *s);

/** 
   \brief Gets a row dual value after solving the simplex.

   Gets a row dual value after solving the simplex.

   \param nrow The row whose dual value we need.
   \param s The simplex structure.
   
   \return The dual value for the row.
 */
double SimplexGetRowDual(unsigned int nrow,TSimplex *s);

/** 
   \brief Gets the dual value for all rows.

   Gets the dual value for all rows. This us like
   \ref SimplexGetRowDual but for all rows in a single
   call.

   \param duals Space where to store the duals. One per row.
   \param s The simplex structure to query.
*/
void SimplexGetDuals(double *duals,TSimplex *s);

/** 
   \brief Adds a row (i.e., a constraint) to the simplex.

   Adds a row (i.e., a constraint) to the simplex. This function
   adds the row without any process of the constraint.
   
   The input linear constraint must have the bound properly expanded
   (see \ref SimplexExpandBounds) before using this function.

   \param lc The linear constraint to add to the simplex.
   \param s The simplex structure.

   \sa SimplexAddNewConstraint
 */
void SimplexAddNewConstraintRaw(TLinearConstraint *lc,
				TSimplex *s);

/** 
   \brief Adds a circle equation to the simplex.

   Ok, it makes no sense to add a non linear equation to the Simplex.
   However, some of the optimization libraries we use are able
   to deal with quadratic constraints. See
   <a href="http://en.wikipedia.org/wiki/Quadratically_constrained_quadratic_program">here</a>
   for an explanation. 

   This function is defined to test these advanced optimization
   features. 

   Note that it only works in few solvers (Gurobi) and it is only
   experimental. The first test are decibing, however.

   \param x Index of the first variable involved in the circle equation.
   \param y Index of the second variable involved in the circle equation.
   \param r2 Squared radius of the circle.
   \param s The simplex structure.
*/
void SimplexAddCircle(unsigned int x,unsigned int y,double r2,TSimplex *s);

/** 
   \brief Updates the simplex internal structures.

   Updates the simplex internal structures. To be called after
   adding all the constraints and before solving.
   This only has effects in Gurobi. The rest of simplex engines
   are updated as we add constraints.

   \param s  The simplex structure to update.
*/
void UpdateSimplex(TSimplex *s);

/** 
   \brief Sets a new objective function.

   Sets a new objective function. We always minimize the objective functions. 
   To maximize just invert the linear constraint before setting it as an
   optimal function.
   
   \param obj The linear constraint representing the new objective function.
   \param s The simplex structure.

   \sa SimplexAddNewConstraint, InvertLinearConstraint.
 */
void SimplexSetOptimizationFunction(TLinearConstraint *obj,TSimplex *s);

/** 
   \brief Get the coefficients of the objective function.

   Returns the coefficients of the objective function. 
   This assumes that offest of the the objective function is null,
   which is the case in practice

   \param coef Space to store the coefficients.
   \param s The simplex to query.
*/
void SimplexGetOptimizationCoefficients(double *coef,TSimplex *s);

/** 
   \brief Gets the optimal value after optimizing the problem.

   Gets the optimal value after optimizing the problem. This function returns
   the value as given by the simplex engine in use. See SimplexGetOptimalValue
   for a procedure that adjusts this raw value to get a numerically safe optimal
   (i.e., it compensates for floating points rounding errors).

   \param s The simplex structure.

   \return The optimal value.

   \sa SimplexGetOptimalValue
*/
double SimplexGetOptimalValueRaw(TSimplex *s);

/** 
   \brief Determines an optimal value.
   
   Determines an optimal value given a set of constraints and an objective
   function.

   \param s The simplex structure.

   \return The state after solving: \ref REDUCED_BOX, \ref EMPTY_BOX, 
           \ref UNBOUNDED_BOX, \ref ERROR_IN_PROCESS.
*/
unsigned int SimplexSolve(TSimplex *s);


/** 
   \brief Destructor.
   
   Deletes the TSimplex structure and frees the allocated memory.

   \param s The simplex structure.
*/
void SimplexDelete(TSimplex *s);


/** 
   \brief Expands an interval according to the equation type.
   
   Expands an interval according to the equation type. 
   - For EQU equations nothing is done. 
   - For LEQ equations the lower limit is set to infinity.
   - For GEQ equations the upper limit is set to infinity.
   .
   
   This is an auxiliary function used when defining the bounds
   for a given simplex constraint. The implementation of this
   function is common to all simplex engines. The definition
   of the constant \ref INF is the one that differs between
   simplex engines.

   \param eq_type EQU, LEQ, GEQ. Used to set the right bounds
          for the interval.
   \param b The interval to expand.
*/
void SimplexExpandBounds(unsigned int eq_type,Tinterval *b);


/** 
    \brief Sets the columns bounds for the simplex.

    Uses the ranges in a box to set the valid ranges for the primary variables
    of the simplex (i.e., the ranges for the column variables).

    \param epsilon Minimim ranges size for the variables. Numerical accuracy.
    \param b The box from where to get the ranges.
    \param lp The simplex to set up.
*/
void SetSimplexBounds(double epsilon,Tbox *b,TSimplex *lp);

/** 
   \brief Adds a row (i.e., a constraint) to the simplex.

   Adds a row (i.e., a constraint) after pre-processing it:
   - The linear constraint is simplified removing terms with tiny constants
     (i.e., with a value below \e epsilon).
   - If the linear constraint only involves one equation it is not added
     to the tableau but it is directly used to reduce the range for the
     variable.
   - Finally, linear constraints not removed in the previous steps are
     added to the simplex.


   \param epsilon Used to remove tiny elements in the input linear constraint.
   \param safeSimplex The degree of numerical stability as indicated by the
                      user in the \ref CT_SAFE_SIMPLEX "SAFE SIMPLEX" parameter.
   \param lc The linear constraint to add to the simplex.
   \param eq_type EQU, LEQ, GEQ. Used to set the right bounds
          for the new simplex row.
   \param is Ranges for the variables in the problem. 
   \param s The simplex structure.

   \return TRUE if the constraint could be added without any problem.
*/
boolean SimplexAddNewConstraint(double epsilon,
				unsigned int safeSimplex,
				TLinearConstraint *lc,
				unsigned int eq_type,
				Tinterval *is,
				TSimplex *s);

/** 
   \brief Returns the optimal value determined by the simplex corrected to compensate
          for possible rounding effects.

    Returns the optimal value determined by the simplex corrected to compensate
    for possible rounding effects.

    The procedure implemented in this function is described in<br>
        - Arnold neumaier and Oleg Shcherbina,
	  <a href="http://www.springerlink.com/content/1had0wg711ed8hdl/">Safe bounds in linear and mixed-integer linear programming</a>
	  Mathematical Programming, Volume 99, Number 2, pp. 283-296, 2004.
	.

    \param safeSimplex 0 not to apply the numerical correction for the optimal value.
    \param m A lower bound for the optimal value. The returned value can not be below this threshold.
    \param b A box with the bounds for the problem variables.
    \param s The simplex structure.

    \return The (possibly) corrected optimal value.
	
*/
double SimplexGetOptimalValue(unsigned int safeSimplex,double m,Tbox *b,TSimplex *s);

/** 
    \brief Reduces a variable range using the simplex.

    Reduces a variable range using the given simplex. The reduction basically consists
    in minimizing and maximizing with an objective function that only takes into account
    the selected variable.<br>
    The simplex algorithm is quite sensible numerically and for some inputs it can
    produce numerical errors. The frequency of these errors depend on the simplex
    implementation you use.<br>
    Since this operation takes into account all constraints simultaneously, it gives
    global consistancy.

    \param epsilon Numerical tolerance used to remove tiny elements in the input linear constraint.
    \param safeSimplex If >1 the simplex process is reseted before the range reduction. If >2
                       we also resed the simplex process in between the minimization/maximization. 
	               All this is done only for simplex engines other that CLP since in CLP 
                       the reset has no effect. Finally, with a value >0, we apply the numerical
                       processes to ensure that the optimal value for the simplex are safe
                       (see \ref SimplexGetOptimalValue).
    \param nv The variable whose range we want to reduce.
    \param b The box with the ranges for all variables.
    \param lp The simplex with the constraints to take into account.

    \return The status of the box after the reduction (EMPTY_BOX, REDUCED_BOX, ERROR_IN_PROCESS)
*/
unsigned int ReduceRange(double epsilon,unsigned int safeSimplex,unsigned int nv,Tbox *b,TSimplex *lp);
#endif
