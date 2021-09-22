#ifndef EQUATIONH
#define EQUATIONH 

#include "boolean.h"
#include "interval.h"
#include "variables.h"
#include "variable_set.h"
#include "monomial.h"
#include "linear_constraint.h"
#include "csmapping.h"

#include <stdlib.h>


/** \file equation.h
    \brief Definition of the Tequation type and the associated functions.

    Definition of the Tequation type and the associated functions.

    \sa Tequation, equation.c.
*/

/** 
   \brief Maximum number of terms to be used in the simplifications.

   Maximum number of terms to be used in the simplifications. 

   This variable is defined for experimental purposes. Do not use a value
   larger than 1.
*/
#define MAX_TERMS_SIMP 1

/************************************************************************************/
/** \brief Initial room for monomials.

    Initial room for monomials in an equation. It will be enlarged if necessary.

    \sa Tequation
*/
#define INIT_NUM_MONOMIALS 100
/************************************************************************************/

/************************************************************************************/


/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define EMPTY_EQUATION   NO_UINT

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define LINEAR_EQUATION   0

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define BILINEAR_EQUATION 1

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define CIRCLE_EQUATION 2

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define SADDLE_EQUATION 3

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define BILINEAL_MONOMIAL_EQUATION 4

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define PARABOLA_EQUATION 5

/** \brief One of the possible type of equations.

    One of the possible type of equations according to the
    type of monomials it includes.

    \sa Tequation
*/
#define SPHERE_EQUATION 6

/** \brief One of the possible type of equations.

    One of the possible type of equations. This is used for
    equations not of the types listed above but that there
    are still of order below 3.

    \sa Tequation
*/
#define GENERAL_EQUATION 7

/** \brief Used for equations with non-assigned type.

    Used for equations with non-assigned type, i.e., equations
    not fully processed.

    \sa Tequation
*/
#define UNKNOWN_EQ_TYPE 8

/************************************************************************************/
/************************************************************************************/
/** \brief One of the possible type of equations.

    One of the possible type of equations according its
    role in the cuiksytem.

    \sa TCuikSystem
*/
#define SYSTEM_EQ   0

/** \brief One of the possible type of equations.

    One of the possible type of equations according its
    role in the cuiksytem.

    \sa TCuikSystem
*/
#define COORD_EQ    1

/** \brief One of the possible type of equations.

    One of the possible type of equations according its
    role in the cuiksytem.

    \sa TCuikSystem
*/
#define DUMMY_EQ    2

/** \brief One of the possible type of equations.

    One of the possible type of equations according its
    role in the cuiksytem. This is for equations resulting
    from a derivative.

    \sa TCuikSystem
*/
#define DERIVED_EQ  3

/** \brief One of the possible type of equations.

    Used for velocity equations, i.e., those defining
    the product of the Jacobian with the velocity
    variables.

    \sa TCuikSystem
*/
#define VELOCITY_EQ   4

/** \brief One of the possible type of equations.

    Used for the equation not involved in the definition
    of motion. Such equations are not used in the 
    computation of the (constrained) dynamics.

    \sa TCuikSystem
*/
#define NON_DYNAMIC_EQ   5


/** \brief One of the possible type of equations.

    Used for equations with non assigned role yet.

    \sa TCuikSystem
*/
#define NOTYPE_EQ   6

/************************************************************************************/
/************************************************************************************/
/** \brief In a Tequation, the equation relational operator is great equal.

    In a Tequation, the equation relational operator is great equal.
 */
#define GEQ    0

/** \brief In a Tequation, the equation relational operator is less equal.

    In a Tequation, the equation relational operator is less equal.
 */
#define LEQ    1

/** \brief In a Tequation, the equation relational operator is equal.

    In a Tequation, the equation relational operator is equal.
 */
#define EQU    2

/** \brief In a Tequation, the equation relational operator is not defined yet.

    In a Tequation, the equation relational operator is not definet yet.
 */
#define NOCMP  3

/************************************************************************************/

/** 
  \brief An equation.
 
  An equation with linear, quadratic or bilinear terms.<br>

  \b NOTE: An equation can be seen as a polynomial (in)equated to a constant value
  and, thus, as a polynomial with an offset (equal to the opposite of the righ-hand
  value of the equation). Therefore in many places in the CuikSuite equations are
  used as polynomials, ignoring the associated (in)equality. This can be a bit
  confusing but implementing a separate type for the polynomials will let the
  equation type almost empty.

  We can have different types of equations according to their role in the 
  problem:
  - SYSTEM_EQ An equation obtained from the kinematic constraints.
  - COORD_EQ Equations defined to obtain cartesian variables (i.e., variables
             for corners of the mechanism links and bodies) from system ones (i.e.,
	     variables defining the valid mechanism poses).
  - DUMMY_EQ Parabolas and saddle equations obtained from the linealization of
             non-linear equations.
  - DERIVED_EQ Equation obtained via the function DeriveEquation
  .

  \sa equation.h equation.c
*/
typedef struct {
  unsigned int type; /**< Type of equation SYSTEM_EQ, COORD_EQ, DUMMY_EQ, DERIVED_EQ, VELOCITY_EQ. */

  boolean polynomial; /**< \ref TRUE if the equation is polynomial */
  
  unsigned int cmp; /**< Relational operator in the equation LEQ, GEQ, EQU. */
  unsigned int order; /**< Order of the equation (1-lineal, 2-bilineal, 2-quadratic).*/
  double value; /**< Right-hand value of the equation.*/

  unsigned int maxMonomials;/**< Maximum number of monomials in the equation.*/
  unsigned int nMonomials;/**< Current number of monomials in the equation.*/
  Tmonomial **monomials;/**< Array with pointers to the monomials of the equation.*/

  Tvariable_set vars;/**< Variables involved in the equation monomials.*/
} Tequation;

/** 
  \brief Constructor.
 
  Creates an empty equation.

  \param eq The equation to create.
*/
void InitEquation(Tequation *eq);

/** 
  \brief Reset equation information.
 
  Removes the information stored in the equation, but does not frees the memory.
  It is more efficient to use ResetEquation instead of DeleteEquation plus 
  InitEquation again.

  \param eq The equation to reset.
*/
void ResetEquation(Tequation *eq);


/** 
  \brief Defines a new equation from a linear constraint.

  Defines a new equation from a linear constraint. Only linear
  constraint with a constant right-hand term can be converted to
  equations. For other linear constraints this funtion triggers
  an error.

  \param lc The linear constraint to convert to an equation.
  \param eq The new equation
*/
void EquationFromLinearConstraint(TLinearConstraint *lc,Tequation *eq);

/** 
  \brief Defines a new equation from the product of two linear constraints.

  Defines a new equation from the product of two linear constraint. Only linear
  constraint with a constant right-hand term are considered. 
  For other linear constraints this funtion triggers an error.

  \param lc1 The first linear constraint to multiply.
  \param lc2 The second linear constraint to multiply.
  \param eq The new equation
*/
void EquationFromLinearConstraintProduct(TLinearConstraint *lc1,TLinearConstraint *lc2,Tequation *eq);

/** 
  \brief Copy constructor.
 
  Creates one equation copying the information from another equation.

  \param eq_dst The equation to create via copy.
  \param eq_orig The equation from where to copy.
*/
void CopyEquation(Tequation *eq_dst,Tequation *eq_orig);

/** 
   \brief Applies the simplification mapping to an equation.

   Transform an equation expressed in a given set of variables
   into an equation in the simplified set of variables.
   The relation between the two sets of variables is given by a
   mapping.

   \param epsilon When replacing variables, monomials with a constant 
                  value below epsilon are removed.
   \param map The mapping relating the two sets of variables.
   \param eqOut The output of the re-write (The simplified equation).
   \param eq The equation in the original system.

   \sa Tmapping
*/
void RewriteEquation2Simp(double epsilon,Tmapping *map,Tequation *eqOut,Tequation *eq);


/** 
   \brief Applies the un-simplification mapping to an equation.

   Transform an equation expressed in a simplified set of variables
   into an equation in the original set of variables.
   The relation between the two sets of variables is given by a
   mapping.

   \param map The mapping relating the two sets of variables.
   \param eq The equation to rewrite.

   \sa Tmapping
*/
void RewriteEquation2Orig(Tmapping *map,Tequation *eq);

/** 
  \brief Adds a scaled equation to another equation.
 
  Adds a scaled equation to another equation.

  \param eqn The equation to scale and add.
  \param ct The scale factor.
  \param eq The equation where to add the result.
*/
void AccumulateEquations(Tequation *eqn,double ct,Tequation *eq);


/** 
  \brief Adds an equation scaled with a variable to another equation.
 
  Adds a scaled equation to another equation. This is like 
  \ref AccumulateEquations but here the scale is with a variable and
  not with a constnat

  \param eqn The equation to scale and add.
  \param v The variable scale factor.
  \param eq The equation where to add the result.
*/
void VarAccumulateEquations(Tequation *eqn,unsigned int v,Tequation *eq);

/** 
   \brief Product of two equations.

   Generates an equations that is the product of two given equations.
   
  \param eq1 The first equation to operate.
  \param eq2 The second equation to operate.
  \param eqOut The resulting equation.
*/
void ProductEquations(Tequation *eq1,Tequation *eq2,Tequation *eqOut);

/** 
  \brief Turns a variable into a constant.
 
  Removes a variable from an equation converting it into a constant.
  Note, that variables are indexed and that removing a variable shifts down
  the index of variables with index above the removed variable.

  \param epsilon Monomials with a constant value below epsilon are removed.
  \param nv Numerical identifier of the variable to remove.
  \param b Value for the variable to remove.
  \param eq The equation from where to remove the variable.
*/
unsigned int FixVariableInEquation(double epsilon,unsigned int nv,double b,Tequation *eq);

/** 
  \brief Replaces a variable.
 
  Replaces a variable from an equation converting it to a linear combination
  of variables.

  Note, that variables are indexed and that removing a variable shifts down
  the index of variables with index above the removed variable.

  \param epsilon Monomials with a constant value below epsilon are removed.
  \param nv Numerical identifier of the variable to remove.
  \param lc The linear constraint that replaces the equation.
  \param eq The equation from where to remove the variable.
*/
unsigned int ReplaceVariableInEquation(double epsilon,unsigned int nv,
				       TLinearConstraint *lc,Tequation *eq);

/** 
   \brief Scales an equation by a constant factor.

   Scales the equation by a constant factor.

   Only equalities are scaled and if the scale factor 
   is 0 this function triggers an error.

   \param ct The factor to use as a scale factor.
   \param eq The equation to scale.
*/
void CtScaleEquation(double ct,Tequation *eq);

/** 
   \brief Scales an equation with a variable factor.

   Scales the equation by a variable factor.

   Only equalities are scaled.

   \param v The variable to use as a scale factor.
   \param eq The equation to scale.
*/
void VarScaleEquation(unsigned int v,Tequation *eq);

/** 
  \brief Normalizes an equation.

  Simple form of normalization to avoid numerical inestabilities.
  If all monomials have the same ct (up to ZERO) we make them
  all equal to one. 
  This helps in many cases when we replace variables to avoid
  transforming, for instance, a circle equation into a scaled circle equation
  (that is not identified as a circle!)

  \param eq The equation to be normalized.
*/
void NormalizeEquation(Tequation *eq);

/** 
   \brief Removes the monomials that evaluate to inf.

   Evaluates each one of the monomials in the equation and moves those
   evaluating to inf to the right hand side of the equation.
   Note that this can transform EQU to LEQ or GEQ. 
   In the extreme case, the right hand side of the equation
   becomes unbounded (-inf,inf). In this case the equation
   does not constrain anything.

   \param eq_in The equation to process.
   \param varValues Ranges for the variables.
   \param changed Is set to TRUE if the equation actually changes.
   \param eq_out The resulting equation.

   \return TRUE if the right-hand side is bounded (not (-inf.inf)).
*/
boolean CleanInfEquation(Tequation *eq_in,Tinterval *varValues,boolean *changed,Tequation *eq_out);

/** 
  \brief Identify equations than can trigger variable simplifications.

  Checks if a given variable can be remove from the system and replaced by a
  linear combination of the surving variables.

  The output variables (\e v and \e lc) are only initilized if some simplification
  is possible (i.e., if the return is TRUE).

  Note that only non-velocity equations are used for simplification.

  \param simpLevel Agressiveness of the simplification process:
                      - 0 No simplification is applied.
                      - 1 Only equations of the form \f$x=a\f$ or \f$x^2=0\f$ are considered 
                          (with \e x a variable and \e a a constant).
                      - 2 Equations of the form \f$x + a y=b\f$ are also considered
                          (with \e x and \e y variables and \e a and \e b constants).
                      - 3 Equations of the form \f$a x + b y=c\f$ are also considered
                          (with \e x and \e y variables and \e a and \e b constants).
                      .
                   The more the simplification the more the chances to get numerical 
		   problems.
  \param nTerms Number of terms (i.e., variables) in the linear constraint to use in the
                simplification.
  \param polynomial TRUE if the system of equations only includes polynomial equations.
                    (not matrix or trigonometric equations).
  \param systemVars Array of booleans marking the main variables. We first try to remove
                    the non-system variables (i.e., to put them in function of the
		    system ones). If this is not possible we proceed to remove system 
		    variables.
  \param cb Box with the current ranges for the variables.
  \param v Output. The variable to eliminate from the system.
  \param lc Output. The linear constraint to use to replace the eliminated variable.
  \param eq The equation.

  \return TRUE if some variable can be eliminated.
*/
boolean IsSimplificable(unsigned int simpLevel,unsigned int nTerms,boolean polynomial,
			boolean *systemVars,Tbox *cb,
			unsigned int *v,TLinearConstraint *lc,
			Tequation *eq);

/** 
  \brief Changes the relational operator (LEQ, GEQ, EQU) of the equation.

  Sets a new relational operator for the equation.

  \param cmp The new relational operator.
  \param eq The equation.
*/
void SetEquationCmp(unsigned int cmp,Tequation *eq);

/** 
  \brief Changes the type of the equation (SYSTEM_EQ, CARTESIAN_EQ, DUMMY_EQ, DERIVED_EQ).

  Sets a new type for the equation.

  \param type The new type.
  \param eq The equation.
*/
void SetEquationType(unsigned int type,Tequation *eq);


/** 
  \brief Changes the right-hand value of the equation.

  Sets a new rigth-hand value for the equation.

  \param v The new right-hand value.
  \param eq The equation.
*/
void SetEquationValue(double v,Tequation *eq);

/** 
  \brief Identify empty equations.

  Identify empty equations: equatoins with no
  monomias and with left value 0 (i.e., basically
  a 0=0 equation).

  \param eq The equation.

  \return TRUE if the given equation is empty.
*/
boolean EmptyEquation(Tequation *eq);

/** 
  \brief Identify linear equations.

  Identify linear equations.

  \param eq The equation.

  \return TRUE if the given equation is linear.
*/
boolean LinearEquation(Tequation *eq);

/** 
  \brief Identify bilinear equations.

  Identify bilinear equations.

  \param eq The equation.

  \return TRUE if the given equation is bilinear.
*/
boolean BilinearEquation(Tequation *eq);

/** 
  \brief Identify circle equations.

  Identify circle equations (with arbitrary radius).

  \f$x^2 + y^2 + z^2=r^2\f$.

  \param eq The equation.

  \return TRUE if the given equation define a circle.
*/
boolean CircleEquation(Tequation *eq);

/** 
  \brief Identify sphere equations.

  Identify sphere equations (with arbitrary radius).

  \f$x^2 + y^2 =r^2\f$.

  \param eq The equation.

  \return TRUE if the given equation define a sphere.
*/
boolean SphereEquation(Tequation *eq);

/** 
  \brief Identify scaled saddle equations.

  Identify scaled saddle equations, i.e., equations of the form
  \f$x y + \alpha z =\beta\f$.

  \param eq The equation.

  \return TRUE if the given equation define a saddle.
*/
boolean SaddleEquation(Tequation *eq);

/** 
  \brief Identify single bilineal monomial equations.

  Identify equations formed by a single bilineal monomial.
  \f$x y  =\beta\f$.

  These equations typically appear after simplifications or when
  including lineal combinations of Jacobian equations and its worth
  to dectect and linearize them in a special way.

  Single quadratic monimial equations 
  \f$x^2  =\beta\f$ do not need a special treatment since they are
  treated in the crop. Moreover, they result in single variable
  lineal constraints with a single variable that are processed by
  \ref SimplifyLinearConstraint and not added to the Simplex.

  \param eq The equation.

  \return TRUE if the given equation define a saddle.
*/
boolean BilinealMonomialEquation(Tequation *eq);

/** 
  \brief Identify scaled parabola equations.

  Identify parabola equations, i.e., equations of the form
  \f$x^2 + \alpha z =\beta\f$.

  \param eq The equation.

  \return TRUE if the given equation define a parabola.
*/
boolean ParabolaEquation(Tequation *eq);

/** 
   \brief Idetify polynomial equations.

   Identify equations formed only by polynomial monomials (i.e. not
   including trionometric functions).
   
  \param eq The equation.

  \return TRUE if the given equation is polynomial.
*/
boolean PolynomialEquation(Tequation *eq);

/** 
  \brief Gets the type of relational operator of the equation.

   Gets the type of relational operator of the equation.

  \param eq The equation.

  \return The type of relational operator of the equation.
*/
unsigned int GetEquationCmp(Tequation *eq);

/** 
  \brief Gets the equation type.

   Gets the equation type.

  \param eq The equation.

  \return The equation type.
*/
unsigned int GetEquationType(Tequation *eq);

/** 
  \brief Gets the right-hand value of the equation.

  Gets the right-hand value of the equation.

  \param eq The equation.

  \return The right-hand value of the equation.
*/
double GetEquationValue(Tequation *eq);

/** 
   \brief Returns the right-hand side of the equation in the form of an interval.

   Returns the  right-hand side of the equation in the form of an interval.
   For EQU equations this is [value,value], for LEQ is [-inf,value], and
   for GEQ is [value,inf].

   \param bounds The output interval.
   \param eq The equation to query.
*/
void GetEquationBounds(Tinterval *bounds,Tequation *eq);

/** 
  \brief Gets the equation order.

  Gets the equation order: 1 for lineal, 2 for bilinear and quadratic.

  \param eq The equation.

  \return The equation order.
*/
unsigned int GetEquationOrder(Tequation *eq);

/** 
  \brief Gets the set of variables  equation used in the equation.

  Gets the set of variables  equation used in the equation.
  Note, we return a pointer to the interval equation structures so be
  careful what you do with the pointer.

  \param eq The equation.

  \return The equation variable set.
*/
Tvariable_set *GetEquationVariables(Tequation *eq);

/** 
  \brief Gets the number of variables  equation used in the equation.

  Gets the number of variables  equation used in the equation.

  \param eq The equation.

  \return The number of variables in the equation.
*/
unsigned int GetEquationNumVariables(Tequation *eq);

/** 
  \brief Equation comparison.

  Returns 1 if eq1<eq2, 0 if eq1=eq2 or 2 if eq1>eq2.
  Equations are sorted according to
  - type
  - order
  - relational operator
  - number of monomials
  .

  \param eq1 The first equation to compare.
  \param eq2 The second equation compare.

  \return The relative order between the equations.
*/
unsigned int CmpEquations(Tequation *eq1,Tequation *eq2);

/** 
  \brief Adds a new scaled monomial to the equation.

  Adds a new scaled monomial to the equation.

  When the scale factor (sc) is 1 this is exactly the
  same as \ref AddMonomial.

  \param sc The scale factor.
  \param f The monomial to add.
  \param eq The equation.

  \sa CmpMonomial
*/
void AddScaledMonomial(double sc,Tmonomial* f,Tequation *eq);

/** 
  \brief Adds a new monomial to the equation.

  Adds a new monomial to the equation.<br> 
  Monomials with the same set of variables are added. <br>
  Monomials are ordered in the equation according to CmpMonomial.

  \param f The monomial to add.
  \param eq The equation.

  \sa CmpMonomial
*/
void AddMonomial(Tmonomial*f,Tequation *eq);

/** 
   \brief Construtor. Generates a parabola equation.

   Generates a parabola equation <em>vx^2-vy=0.</em>

   \param vx Identifier of the \e x variable.
   \param vy Identifier of the \e y variable.
   \param eq The equation to generate.
*/
void GenerateParabolaEquation(unsigned int vx,unsigned int vy,Tequation *eq);

/** 
   \brief Construtor. Generates a scaled parabola equation. 

   Generates a parabola equation <em>s*vx^2-vy=0.</em> 
 
   \param s The scale to apply.
   \param vx Identifier of the \e x variable. 
   \param vy Identifier of the \e y variable. 
   \param eq The equation to generate. 
*/
void GenerateScaledParabolaEquation(double s,unsigned int vx,unsigned int vy,Tequation *eq); 

/** 
   \brief Construtor. Generates a saddle equation.

   Generates a saddle equation <em>vx*vy-vz=0.</em>

   If \e vx is the same as \e vy a parabola equation is generated.

   \param vx Identifier of the \e x variable.
   \param vy Identifier of the \e y variable.
   \param vz Identifier of the \e z variable.
   \param eq The equation to generate.
*/
void GenerateSaddleEquation(unsigned int vx,unsigned int vy,unsigned int vz,
			    Tequation *eq);


/** 
   \brief Construtor. Generates a scaled saddle equation.

   Generates a saddle equation <em>s*vx*vy-vz=0.</em>

   If \e vx is the same as \e vy a scaled parabola equation is generated.

   \param s The scale to apply.
   \param vx Identifier of the \e x variable.
   \param vy Identifier of the \e y variable.
   \param vz Identifier of the \e z variable.
   \param eq The equation to generate.
*/
void GenerateScaledSaddleEquation(double s,
				  unsigned int vx,unsigned int vy,unsigned int vz,
				  Tequation *eq);

/** 
  \brief Construtor. Generates an equation that is the norm of a vector.

  Generates an equation  that is the norm of a  vector with \e nv
  variables \e n.
  Thus, the equation created is
  <center>\f$\sum_{i=1}^{nv}v_i^2=n\f$</center>
  
  \param nv Number of variables.
  \param v Array with the index of the variables to use.
  \param n The value for the norm.
  \param eq The equation.
*/
void GenerateGeneralNormEquation(unsigned int nv,unsigned int *v,double n,Tequation *eq);
/** 
  \brief Construtor. Generates an equation that is the norm of a 3d vector.

  This is a special case of \ref GenerateGeneralNormEquation where the 
  vector has only 3 variables.
  
  \param vx The first variable of the 3d vector.
  \param vy The second variable of the 3d vector.
  \param vz The third variable of the 3d vector.
  \param n The value for the norm.
  \param eq The equation.

  \sa GenerateDotProductEquation, GenerateCrossProductEquations, GenerateDistanceEquation
*/
void GenerateNormEquation(unsigned int vx,unsigned int vy,unsigned int vz,
			  double n,
			  Tequation *eq);
/** 
  \brief Construtor. Generates the three equations of the cross product of two unitary vectors.

  Generates the three equations of the 
  <a href="http://en.wikipedia.org/wiki/Cross_product"> cross product</a> of two unitary vectors that give
  as a result a third vector (orthogonal to the two operated vectors) scaled
  by the sinus of the angle between these two vectors.<br>
  The equations result from <br>
  <center><em>(v1x,v1y,v1z)</em> X <em>(v2x,v2y,v2z)</em> =<em>sin(v1,v2) * (v3x,v3y,v3z)</em> </center><br>
  The sinus is given as a constant (parameter \e s) or as another variable (parameter \e vs).<br>
  The input vectors are \e assumed to be unitary (i.e., it is assumed that other equations already
  included in the system ensure they have norm one).<br>
  This function can be seen as a constructor of three equations at a time.
  
  \param v1x The first variable of the first vector.
  \param v1y The second variable of the first vector.
  \param v1z The third variable of the first vector.
  \param v2x The first variable of the second vector.
  \param v2y The second variable of the second vector.
  \param v2z The third variable of the second vector.
  \param v3x The first variable of the third vector.
  \param v3y The second variable of the third vector.
  \param v3z The third variable of the third vector.
  \param vs Variable representing the sinus of the angle between \e v1 and \e v2. NO_UINT if
            this sinus is constant (given by parameter \e s).
  \param s Constant sinus between \e v1 and \e v2. Not used if \e vs is different from NO_UINT.
  \param eq Array of three equations to be created.

  \sa GenerateNormEquation, GenerateDotProductEquation, GenerateDistanceEquation
*/
void GenerateCrossProductEquations(unsigned int v1x,unsigned int v1y,unsigned int v1z,
				   unsigned int v2x,unsigned int v2y,unsigned int v2z,
				   unsigned int v3x,unsigned int v3y,unsigned int v3z,
				   unsigned int vs,
				   double s,
				   Tequation *eq);

/** 
  \brief Construtor. Generates the equation of the dot product of two unitary vectors.

  Generates the equation corresponding to the 
  <a href="http://en.wikipedia.org/wiki/Dot_product">dot product</a> of two unitary vectors that give
  as a result the cosinus of the angle between these two vectors.<br>
  The equation result from <br>
  <center><em>(v1x,v1y,v1z)</em> * <em>(v2x,v2y,v2z)</em> =<em>cos(v1,v2) </em> </center><br>
  The cosinus is given as a constant (parameter \e c) or as another variable (parameter \e vc).<br>
  The input vectors are \e assumed to be unitary (i.e., it is assumed that other equations already
  included in the system ensure they have norm one)..<br>
  This function can be seen as an equation constructor.
  
  \param v1x The first variable of the first vector.
  \param v1y The second variable of the first vector.
  \param v1z The third variable of the first vector.
  \param v2x The first variable of the second vector.
  \param v2y The second variable of the second vector.
  \param v2z The third variable of the second vector.
  \param vc Variable representing the cosinus of the angle between \e v1 and \e v2. NO_UINT if
            this cosinus is constant (given by parameter \e s).
  \param c Constant cosinus between \e v1 and \e v2. Not used if \e vc is different from NO_UINT.
  \param eq The equation to be created.

  \sa GenerateNormEquation, GenerateDistanceEquation
*/
void GenerateDotProductEquation(unsigned int v1x,unsigned int v1y,unsigned int v1z,
				unsigned int v2x,unsigned int v2y,unsigned int v2z,
				unsigned int vc,
				double c,
				Tequation *eq);


/** 
  \brief Construtor. Generates the equation of the distance between two points.

  Generates the equation corresponding to the distance between two points:
  (x1-x2)^2+(y1-y2)^2+(z1-z2)^2.
  
  \param v1x The first variable of the first point.
  \param v1y The second variable of the first point.
  \param v1z The third variable of the first point.
  \param v2x The first variable of the second point.
  \param v2y The second variable of the second point.
  \param v2z The third variable of the second point.
  \param vc Variable representing the distance between the points.
  \param c Constant giving the distance between the two points. 
           Not used if \e vc is different from NO_UINT.
  \param eq The equation to be created.

  \sa GenerateNormEquation, GenerateDotProductEquation
*/
void GenerateDistanceEquation(unsigned int v1x,unsigned int v1y,unsigned int v1z,
			      unsigned int v2x,unsigned int v2y,unsigned int v2z,
			      unsigned int vc,
			      double c,
			      Tequation *eq);

/** 
  \brief Searches for a given monomial in the equation.

  Searches for a given monomial in the equation.<br>
  In this functions,  monomials are compare equal taking into account
  \b only the variables they involve.

  \param f The monomial to look for.
  \param eq The equation where to look for.

  \return The identifier of the monomial in the equation of NO_UINT if the
          given monomial is not present in the equation.
*/
unsigned int FindMonomial(Tmonomial *f,Tequation *eq);

/** 
  \brief Gets a monomial from an equation.

  Gets a monomial from an equation.

  \param i The identifier of the monimial to retrive.
  \param eq The equation.

  \return A pointer to the \e i-th monomial in the equation or NULL if
          the equation has less than \e i monomials.
*/
Tmonomial *GetMonomial(unsigned int i,Tequation *eq);

/** 
  \brief Number of monomials in an equation.

  Returns the number of monomials in an equation.

  \param eq The equation.

  \return The number of monomials in an equation.
*/
unsigned int GetNumMonomials(Tequation *eq);

/** 
  \brief Converts a linear equation into a linear constraint.

  Converts a linear equation into a linear constraint.
  
  A linear constraint is just a particular case of equation. We implemented
  the linear constraints as a different type just for convenience (i.e., to
  facilitate the simplex implementation).

  If the input equation is not linear, the output is empty.
  To approximate a general equation with a linear constraint use
  \ref GetFirstOrderApproximationToEquation.

  \param lc The resulting linear constraint.
  \param eq The equation to convert.
*/
void LinearEquation2LinearConstraint(TLinearConstraint *lc,Tequation *eq);

/** 
   
  \brief Evaluates an equation in a given point.

  Evaluates an equation in a given point including its right-hand side.
  This is like a combination of \ref EvaluateEquation and \ref GetEquationValue
  into a single function.

  \param varValues Values defining the point where to evaluate the equation. The
                   array must include values for \b all the variables in the system 
		   (from where the function selects the values for the variables 
		   included in the equation).
  \param eq The equation.

  \return The value of the equation including the right-hand side.  
*/
double EvaluateWholeEquation(double *varValues,Tequation *eq);

/** 
  \brief Evaluates an equation in a given point.

  Evaluates an equation in a given point.

  \b NOTE:  The right-hand side value of the equation is not used in the evaluation.

  \param varValues Values defining the point where to evaluate the equation. The
                   array must include values for \b all the variables in the system 
		   (from where the function selects the values for the variables 
		   included in the equation).
  \param eq The equation.

  \return The value of the equation.
*/
double EvaluateEquation(double *varValues,Tequation *eq);

/** 
  \brief Interval evaluation of an equation.

  Evaluates an equation for a given ranges of the variables using interval
  arithmetics.<br>
  \b NOTE: The right-hand side value of the equation is not used in the evaluation.

  \param varValues Intervals for the variables in the system of equations. This
                   function only uses the ranges for the variables in the equation.
  \param i_out The result of the evalution.
  \param eq The equation.
*/
void EvaluateEquationInt(Tinterval *varValues,Tinterval *i_out,Tequation *eq);

/** 
  \brief Derives an equation.

  Derives an equation with respect to a given variable.

  \param nv Identifier of the variable with respect to the one we have to derive.
  \param d Output equation with the derivative.
  \param eq The equation to derive.
*/
void DeriveEquation(unsigned int nv,Tequation *d,Tequation *eq);

/** 
  \brief Prints an equation as a set if monomials.

  Writes an equation to a given stream as a sequence of monomials and with
  the right-hand value moved to the left.
 
  The differences with respect to PrintMonomials is that here we print
  the monomial set assuming that it is an equality (even if it is not) 
  and that no return is printed at the end.

  \param f The stream where to print the equation.
  \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
  \param eq The equation with the monomials to print.

  \sa PrintEquation
*/
void PrintMonomialsInLine(FILE *f,char **varNames,Tequation *eq);

/** 
  \brief Prints an equation as a set if monomials.

  Writes an equation to a given stream as a sequence of monomials and with
  the right-hand value moved to the left.
 
  This only works if the equation is a equality. Inequalities are always printed
  as a normal equations

  \param f The stream where to print the equation.
  \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
  \param eq The equation with the monomials to print.

  \sa PrintMonomialsInLine
*/
void PrintMonomials(FILE *f,char **varNames,Tequation *eq);

/** 
  \brief Prints an equation.

  Writes an equation to a given stream.

  \param f The stream where to print the equation.
  \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
  \param eq The equation to print.

  \sa PrintMonomial PrintVarSet
*/
void PrintEquation(FILE *f,char **varNames,Tequation *eq);

/** 
  \brief Destructor.

  Deletes the information stored in the equation and frees the allocated memory space.
  
  \param eq The equation to delete.
*/
void DeleteEquation(Tequation *eq);

#endif
