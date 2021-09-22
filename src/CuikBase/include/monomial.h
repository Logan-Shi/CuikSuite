#ifndef MONOMIALH
#define MONOMIALH 

#include "boolean.h"
#include "interval.h"
#include "variables.h"
#include "variable_set.h"

#include <stdlib.h>

/** 
   \file monomial.h
   \brief Definition of the Tmonomial type and the associated functions. 
   
    Definition of the Tmonomial type and the associated functions.

   \sa Tmonomial, monomial.c.
*/


/** 
   \brief A scaled product of powers of variables. 
   
   A scaled product of powers of variables, possibly with functions applied
   to each individial variable.

   Since functions can be applied to variables, the name monomial is probably
   not adequate but used for legacy reasons.

   \sa Tvariabe_set, monomial.h, monomial.c
*/
typedef struct {
  boolean empty;      /**< TRUE if the monomial is empty.  */
  double ct;          /**< Scale factor.*/
  Tvariable_set vars; /**< Product of powers of variables. */
} Tmonomial;


/** 
   \brief Constructor.
   
   Defines an empty monomial.

   \param f The monomial to be initialized.
*/
void InitMonomial(Tmonomial *f);


/** 
   \brief Reset the monomial information.
   
   Removes the information stored in the monomial, but does not frees the memory.
   It is more efficient to use ResetMonomial instead of DeleteMonomial plus 
   InitMonomial again.

   \param f The monomial to be initialized.
*/
void ResetMonomial(Tmonomial *f);

/** 
   \brief Sets the monomial to zero.
   
   Clears the variable set and sets the constant to 0.
   Please, note that a zero monomial is not an empty (i.e., not yet used
   monomial). For instance, we can not add new variables to a 
   zero monomial until the constant is not zero. In an empty
   monomial anything can be added.

   \param f The monomial to be initialized.
*/
void ZeroMonomial(Tmonomial *f);

/** 
   \brief Replaces a variable by a constant.
   

   Removes a variable from a monomial converting it into a constant.
   Note, that variables are indexed and that removing a variable shifts down
   the index of variables with index above the removed variable.
   
   \param nv Numerical identifier of the variable to remove.
   \param v Value for the variable to remove.
   \param f The monomial to be updated.
*/
void FixVariableInMonomial(unsigned int nv,double v,Tmonomial *f);

/** 
  \brief Replaces a variable.
 
  Replaces a variable from a monomial converting it into a another variable
  via a linear relation
  <br>
  <center>VarToBeReplaced = a * NewVar + b</center>
  <br>
  Note, that variables are indexed and that removing a variable shifts down
  the index of variables with index above the removed variable.

  \param nv Numerical identifier of the variable to remove.
  \param ct Scale factor for the new variable.
  \param nvNew Numerical identifier of the new variable.
  \param f The monomial to be updated.
*/
void ReplaceVariableInMonomial(unsigned int nv,double ct,unsigned int nvNew,Tmonomial *f);


/** 
  \brief Checks if a monomial is empty.

  Checks if a monomial is empty.

  \param f The monomial to be checked.

  \return TRUE if the input monomia is empty.
*/
boolean EmptyMonomial(Tmonomial *f);


/** 
  \brief Checks if a monomial is constant.

  Checks if a monomial is constant.

  \param f The monomial to be checked.

  \return TRUE if the input monomial is constant.
*/
boolean CtMonomial(Tmonomial *f);

/** 
  \brief Checks if a monomial is quadratic: <em>K*x^2</em>, with \e K a constant.

  Checks if a monomial is quadratic: <em>K*x^2</em>, with \e K a constant.

  \param f The monomial to be checked.

  \return TRUE if the input monomial is quadratic.
*/
boolean QuadraticMonomial(Tmonomial *f);


/** 
  \brief Checks if a monomial is bilienal: <em>K*x*y</em>, with \e K a constant.

  Checks if a monomial is bilineal: <em>K*x*y</em>, with \e K a constant.

  \param f The monomial to be checked.

  \return TRUE if the input monomial is bilienal.
*/
boolean BilinearMonomial(Tmonomial *f);

/** 
  \brief Checks if a monomial is lienal: <em>K*x</em>, with \e K a constant.

  Checks if a monomial is bilineal: <em>K*y</em>, with \e K a constant.

  \param f The monomial to be checked.

  \return TRUE if the input monomial is lineal.
*/
boolean LinearMonomial(Tmonomial *f);

/** 
   \brief Identifies monimials not involving any kind of (trigonomitric function).

   Identifies monimials not involving any kind of (trigonomitric function).

   Note that mathematically all monomials are polynomials. In this implementation this
   is not the case since the monomial structrue is used also for the case where variables
   are affected by (trigonometric) function. To be correct we should not use the term
   monomial to refer to a product of constants, variables, and functions.

   \todo Replace the term monomial by factor.

   \param f The monomial to query.

   \return TRUE if the monomial is purelly polynomial.
*/
boolean PolynomialMonomial(Tmonomial *f);

/** 
  \brief Gets the order of a monomial.

  Gets the order of a monomial. Here the order is the sum
  of the powers of the variables in the monomial 
  (0 for constant, 1 for lineal, 2 for quadratic and bilineal). 

  \param f The monomial to be checked.

  \return The monomial order as defined above.
*/
unsigned int MonomialOrder(Tmonomial *f);

/** 
  \brief Copy constructor.

  Copies a constructor copying the data from another monomial.

  \param f_dst The monomial to be created.
  \param f_orig The monomial from where to copy.
*/
void CopyMonomial(Tmonomial *f_dst,Tmonomial *f_orig);

/** 
  \brief Monomial comparison.

  Compare two given monomials. Monomials are compared first
  taking into account the variables and then their scale factor.

  \param f1 The first monomial to compare.
  \param f2 The second monomial to compare.

  \return 1 if \e f1 is larger than \e f2, 0 if they are equal and
          2 if \e f2 is larger than \e f1.
       
  \sa CmpVarSet
*/
unsigned int CmpMonomial(Tmonomial *f1,Tmonomial *f2);


/** 
  \brief Changes the scale factor of a monomial.

  Changes the scale factor of a monomial.
 
  \param k the new monomial scale factor.
  \param f The monomial to update.
*/
void SetMonomialCt(double k,Tmonomial *f);


/** 
  \brief Gets the scale factor of a monomial.

  Gets the scale factor of a monomial.
 
  \param f The monomial to update.

  \returns The scale factor of the monomial.
*/
double GetMonomialCt(Tmonomial *f);

/** 
  \brief Gets the variables of a monomial.

  Gets the variables of a monomial.
 
  \param f The monomial to update.

  \returns A pointer to the set of variables in the monomial.
*/
Tvariable_set *GetMonomialVariables(Tmonomial *f);

/** 
  \brief Scales a monomial.

   Scales  a monomial.
 
  \param k The scale factor to apply to the monomial.
  \param f The monomial to update.
*/
void AddCt2Monomial(double k,Tmonomial *f);

/** 
  \brief Adds a power variable to the monomial.

  Adds a power variable to the monomial.

  \param fn Function to be applied to the variable (\ref SINV, \ref COSV, or 
         \ref NFUN for no function).
  \param varid The identifier of the variable to be added to the monomial.
  \param p The power for the variable.
  \param f The monomial to update.
*/
void AddVariable2Monomial(unsigned int fn,unsigned int varid,unsigned int p,Tmonomial *f);

/** 
   \brief Product of two monomials.

   Produces a monomial that is the product of the two other given monomials.

   \param f1 The firt monomial to product.
   \param f2 The second one.
   \param f The output monomial.
*/
void MonomialProduct(Tmonomial *f1,Tmonomial *f2,Tmonomial *f);

/** 
  \brief Evaluates a monomial for a given set of value for the variables.
  
  Evaluates a monomial for a given set of value for the variables.

  \param varValues An array of doubles with the values for the variables in the problem.
  \param f The monomial to evaluate.

  \return The value of the monomial.
*/
double EvaluateMonomial(double *varValues,Tmonomial *f);

/** 
  \brief Evaluates a monomial for a given set of ranges for the variables.
  
  Evaluates a monomial for a given set of ranges for the variables using interval
  arithmetics.

  \param varValues An array with the ranges for the variables in the problem.  
  \param i_out The output interval.
  \param f The monomial to evaluate.
*/
void EvaluateMonomialInt(Tinterval *varValues,Tinterval *i_out,Tmonomial *f);

/** 
  \brief Derives an monomial.

  Derives a monomial with respect to a given variable.

  \param nv Identifier of the variable with respect to the one we have to derive.
  \param df Output monomial with the derived monomial.
  \param f The monomial to derive.
*/
void DeriveMonomial(unsigned int nv,Tmonomial *df,Tmonomial *f);


/** 
  \brief Prints a monomial.

  Writes a monomial to a given stream.

  \param file The stream where to print the monomial.
  \param first TRUE if the monomial is the first one in an equation. This is used
               to avoid a '+' sign at the beginning of the equation.
  \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
  \param f The monomial to print.
*/
void PrintMonomial(FILE *file,boolean first,char **varNames,Tmonomial *f);


/** 
  \brief Destructor.

  Deletes the information stored in the monomial and frees the allocated memory space.
  
  \param f The monomial to be deleted.
*/
void DeleteMonomial(Tmonomial *f);

#endif
