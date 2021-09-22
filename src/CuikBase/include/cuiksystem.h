#ifndef CUIKSYSTEMH
#define CUIKSYSTEMH

#include "constants.h"
#include "equations.h"
#include "variables.h"
#include "statistics.h"
#include "list.h"
#include "box_list.h"
#include "parameters.h"
#include "box.h"
#include "boolean.h"
#include "vector.h"
#include "csmapping.h"
#include "jacobian.h"
#include "nhessian.h"
#include "njacobian.h"

#include <stdlib.h>


/** \file cuiksystem.h
    \brief Definition of the TCuikSystem type and the associated functions.

    Definition of the TCuikSystem type and the associated functions.

    \sa TCuikSystem, cuiksystem.c, readcuiksystem.l, readcuiksystem.y,
*/
/************************************************************************************/

/** \brief Set to 1 to sort boxes according to the evaluation in its center.

    Boxes to be reduced can be sorted according to a given equation.
    If this is set to 1 we evaluate this equation in the center of each box
    If set to 1 we evaluate the equation interval-wise and take the center of
    the resulting interval.

    \todo Just select the evaluation method that is better and remove the other.
*/
#define EQ_MIN_IN_CENTER 0

/** \brief Set to one to avoid Newton to scape from boxes.
   
    Set to one to avoid Newton to scape from boxes.

    \todo Remove this if box limits do not help at all
*/
#define NEWTON_WITHIN_RANGES 0

/************************************************************************************/
/** \brief Depth first search.

   In this mode, boxes to be reduced are sorted so that boxes with a
   higher level (i.e., resulting from more bisections) are treated first. 
*/
#define DEPTH_FIRST_SEARCH 1
/************************************************************************************/

/************************************************************************************/
/** \brief Breadth first search.

   In this mode, boxes to be reduced are sorted so that boxes with a
   smaller level (i.e., resulting from less bisections) are treated first.
*/
#define BREADTH_FIRST_SEARCH 2
/************************************************************************************/

/************************************************************************************/
/** \brief Search based on a minimum value of a given equation.

   In this mode, boxes to be reduced are sorted so that we tread first boxes
   whose value with repect to a given equation are minimal (among all boxes 
   pending to be treated).

   In the current implementation the center of the box is used to evaluate the
   criterion to be minimized.
*/
#define MINIMIZATION_SEARCH 3
/************************************************************************************/

/************************************************************************************/
/** \brief Point, relative to the size of the selected box side, where we
           split a box.

   Point, relative to the size of the selected box side, where we 
   split a box. 
*/

#if (RANDOMNESS)
  #define CUT_POINT 0.45+0.1*randomDouble()
#else
  #define CUT_POINT 0.5
#endif
/************************************************************************************/

/************************************************************************************/
/** \brief MPI child-process timeout.

    Maximum time (in seconds) we give a child-process to reduce a box. Only used
    when \b cuik is executed in a multi-processor environment.
*/
#define MPI_TREAT_BOX_TIMEOUT(cs) (cs->nvariables*SIMPLEX_TIMEOUT*10)
/************************************************************************************/


/************************************************************************************/
/** \brief One of the possible outputs of the Newton iteration.

    Returned by \ref CuikNewtonInBox when the Newton iteration was repeated
    for more than \ref CT_MAX_NEWTON_ITERATIONS times without reaching a stationary 
    point.
*/
#define DIVERGED 1
/************************************************************************************/

/************************************************************************************/
/** \brief One of the possible outputs of the Newton iteration.

    Returned by \ref CuikNewtonInBox when the Newton iteration converged to a point
    inside the given box.

    Note that if the Newton converges in the current box it also converges in the
    initial box however the more restrictive condition (convergence in local box) 
    is returned.
*/
#define CONVERGED_IN_BOX 2
/************************************************************************************/


/************************************************************************************/
/** \brief One of the possible outputs of the Newton iteration.

    Returned by \ref CuikNewtonInBox when the Newton iteration converged to a point
    outside the given box, but inside the initial box.

    Note that if the Newton converges in the current box it also converges in the
    initial box however the more restrictive condition (convergence in local box) 
    is returned.
*/
#define CONVERGED_IN_GLOBAL 4
/************************************************************************************/

/************************************************************************************/
/** \brief One of the possible outputs of the Newton iteration.

    Returned by \ref CuikNewtonInBox when the Newton iteration converged but to a point
    that is outside the initial box.

    Note that this is only returned if the process converged but outside the global
    box.
*/
#define CONVERGED_OUTSIDE_GLOBAL 8
/************************************************************************************/

/** \brief Union of all possible convergence cases for Newton interation.

    The union of all possible convergence cases for Newton iteration. Provide
    to facilitate the test whether or not a call actually converged (to anywhere)
*/
#define CONVERGED (CONVERGED_IN_BOX|CONVERGED_IN_GLOBAL|CONVERGED_OUTSIDE_GLOBAL)
/************************************************************************************/

/** 
 \brief A cuiksystem, i.e., a set of variables and equations defining a position analysis problem.

 This structure includes all the information defining a position analysis problem, that is,
 a set of varaibles and a set of equations using these variables.
 <br>
 We store the variables/equations as defined by the user, a simplified version where some
 variables/equations are removed (because they are constant or they can be defined in function
 of other variables), and a simplified+dummified version where equations that can not be
 directly handled by linear relaxations are re-wrote into simpler equations.
 <br>
 Note that the two simplified cuiksystems are for internal use and its existence is transparent:
 all function calls refer to the original variables and equations.
 <br>
 Finally, this structure also includes information about variables and equations that is cached 
 to speed up the process. Everytime there is a change in the system this information must be
 recomputed.

 \sa cuiksystem.h cuiksystem.c Tmapping 
*/
typedef struct { 
  Tconstants constants;    /**< Constants defined when reading the cuiksystem from file */

  boolean updated;         /**< TRUE if the cached information is up to date. */
  boolean consistent;      /**< TRUE if the system is consistent (it does not turn trivially 
			        inconsisted while simplifying it). */
  boolean empty;           /**< TRUE if the system includes no equations.  */
  boolean scalar;          /**<  TRUE for scalar systems (i.e., non-including). */

  Tstatistics st;          /**< Set of statistics including information about the last attempt 
			         to solve the problem */
 
  unsigned int searchMode; /**< Criterion to be used when sorting the boxes pending to be processed. */
  Tequation orig_eqMin;    /**< Equation to be minimized when searcMode is set to \ref MINIMIZATION_SEARCH
			        in its original form. */

  /******************************************************************************/
  /* SIMPLIFIED AND DUMMIFIED SUB-SYTEM                                         */
  /* The dummified system is for internal use only and only used for the linear
     relaxation methods. Other higher-level methods can operate on the simplified
     sistem, without dummification. */
  Tmapping *orig2sd;       /**< Mappings to relate the original and the simplified+dummified variables. */

  Tequations equations;    /**< Simplified+dummified set of equations*/
  Tvariables variables;    /**< Simplified+dummified set of variables*/

  unsigned int nequations; /**< Total number of equations in the simplified+dummified system. */
  unsigned int nvariables; /**< Total num. of variables in the simplified+dummified system. */
  boolean *systemVar;      /**< TRUE if the <em>'i'-th</em> variable in the simplified+dummified 
			        system is a system var. */
  boolean *notDummyVar;    /**< TRUE if the <em>'i'-th</em> variable in the simplified+dummified 
			        system is not a dummy var. */
  unsigned int *varType;   /**< Type for each original variable (system, dummy, ...) in the 
			        simplified+dummified system. */

  Tequation eqMin;         /**< Equation to be minimized when searcMode is set to \ref MINIMIZATION_SEARCH
			        in its simplified+dummified form. */

  /******************************************************************************/
  /* SIMPLIFIED SUB-SYTEM                                                       */
  Tmapping *orig2s;             /**< Mappings to relate the original and the simplified variables. */

  boolean simp_empty;           /**< TRUE if the simplified system includes no equations.  */

  Tequations simp_equations;    /**< Simplified set of equations*/
  Tvariables simp_variables;    /**< Simplified set of variables*/

  unsigned int simp_nequations; /**< Total number of equations in the simplified system. */
  unsigned int simp_nvariables; /**< Total num. of variables in the simplified system. */
  unsigned int simp_nee;        /**< Number of equalities in the simplified set of equations. */

  unsigned int *simp_tp;        /**< Topology of the variables in the simplified system. 
				     NULL if all variables are real. */

  Tequation simp_eqMin;         /**< Equation to be minimized when searcMode is set to \ref MINIMIZATION_SEARCH
				     in its simplified form. */
  
  TJacobian J;                  /**< Jacobian of the simplified set of equations (only for equalities). */
  
  /******************************************************************************/
  /* ORIGINAL SUB-SYTEM                                                         */
  Tequations orig_equations;    /**< Equations as given by the user*/
  Tvariables orig_variables;    /**< Variables as given by the user*/

  unsigned int orig_nequations; /**< Total number of equations in the original system. */
  unsigned int orig_nvariables; /**< Total number of variables in the original system. */
  boolean *orig_systemVar;      /**< TRUE if the <em>'i'-th</em> original variable is a system var
				   or a secondary var. This array is basically used to select
				   the variables when printing solutions. We include the secondary
				   variables since, although they can be computed from the system
				   ones, we have no explicit equations to do so and, therefore.
				   the presence of the secondary variables in solutions is a must.
				   This basically caches the output of \ref GetCSSystemVars */
  boolean *orig_notDummyVar;    /**< TRUE if the <em>'i'-th</em> original variable is not a dummy var. */

  char **orig_varNames;         /**< Pointers to the name of the variables. Used when printing boxes.*/

} TCuikSystem;


/****************************************************************************/
/* Methods to initialize/define/re-define CuikSystems (constructors et al.) */
/****************************************************************************/

/** 
    \brief Constructor.

    Creates an empty cuiksystem.

    \param cs The cuiksystem to initialize.
*/
void InitCuikSystem(TCuikSystem *cs);


/** 
    \brief Constructor from a file.

    Creates an cuiksystem from the information on a file. Right now we do not
    have a manual of the syntax of the ".cuik" files so check the examples
    in the CuikSuite examples directory or in the 
    <a href="http://www-iri.upc.es/groups/gmr/cuikweb/benchmarks.html">benchmarks</a> 
    section of our web page

    \param p A set of parameters.
    \param filename The name of the file from which to read the variables and equations.
    \param cs The cuiksystem to initialize.
*/
void InitCuikSystemFromFile(Tparameters *p,char *filename,TCuikSystem *cs);

/** 
    \brief Adds information from a file.

    Adds information (constants/variables/equations) to a cuiksystem from another
    file. This is typically used to build a cuiksystem from a set of files where
    each file assumes we already loaded the previous ones (when adding contact equations
    to a cuiksystem or eigengrasp equations or singularity equations or....).

    This function is exacty the same as \ref InitCuikSystemFromFile but the system
    is not initialized from scratch but assumed pre-initialized.

    \param p A set of parameter.
    \param prefix TRUE if the cuiksystem has been automatically generated. In this case
                  the variables and constants have '_' as a prefix. This is the case
		  when inserting a cuik file into a world file. In this case, the names
		  of the variables are generated accordingly (adding '_').
    \param cts Optional set constants so that they can be used in the new added cuiksystem. 
               This is only useful when adding equations to those automatically generated
	       equation set. In this case we may need the new added equations to re-used
	       some of the constants appearing in the world file. Thus the world constants
	       are used to initialize the constants in the cuiksystem to add.
	       Otherwise, this paremeter should be NULL.
    \param filename The name of the file from which to read the variables and equations.
    \param cs The cuiksystem to initialize.
*/
void AddCuikSystemFromFile(Tparameters *p,boolean prefix,Tconstants *cts,
			   char *filename,TCuikSystem *cs);

/** 
    \brief Checks the consistency of the cuiksystem.

    Checks the consistency of the cuiksystem. If the system is inconsistent
    an error is trigered.
    Note that if new equations/variables are added to the cuiksystem
    its consistancy might no longer hold.

    \param p The set of parameters.
    \param cs The cuiksystem to verify.
*/
void VerifyCuikSystem(Tparameters *p,TCuikSystem *cs);

/** 
    \brief Copy constructor.

    Creates an cuiksystem from another cuiksystem.

    \param cs_dst The cuiksystem to create via copy.
    \param cs_src The cuiksystem from where to copy.
*/
void CopyCuikSystem(TCuikSystem *cs_dst,TCuikSystem *cs_src);

/** 
    \brief Produces the union of two cuik systems.

    Defines a new cuiksystem by union of two given cuiksystems.
    
    \b CAUTION!
      - The variables for one of the input systems must be a subset
        (or equal) of  the variable set of the other system.
	If this is not so the result is undefined.
      .

    \param p The set of parameters.
    \param cs1 The first cuik system merge.
    \param cs2 The second cuiksystem to merge.
    \param cs The output merged cuiksystem.
*/
void CuikSystemMerge(Tparameters *p,TCuikSystem *cs1,TCuikSystem *cs2,TCuikSystem *cs);


/** 
   \brief Determines which box to explore first in minimization mode.

   Determines which box to explore first in minimization mode.
   In this mode boxes are sorted according to an objective function
   given by an equation in the problem file. 
   The equation is evaluated at the center of the box and the box
   with a minimum value is processed first.
   
   \param b1 The first box.
   \param b2 The second box.  
   \param cs The TCuikSystem structure storing the equation to
             use when evaluating

   \return TRUE if the first box is to be explored before than the
           second one when in minimization mode.

   \sa EvaluateEqMin
*/
boolean CmpBoxesEquation(void *b1,void *b2,void *cs);

/** 
   \brief Sets the search mode for the cuiksystem.

   Defines the criterion to be used sorting the boxes to be treated when
   searching for a solution.

   Possible critera are
      - Depth First
      - Breadth First
      - Minimum value for a given equation first.

   \param sm Search mode: \ref DEPTH_FIRST_SEARCH, \ref BREADTH_FIRST_SEARCH
             or \ref MINIMIZATION_SEARCH.
   \param eqMin When the search mode is \ref MINIMIZATION_SEARCH, the criterion
                to be minimized. Otherwise it is not used.
   \param cs The cuiksystem to update.
*/
void SetCSSearchMode(unsigned int sm,Tequation *eqMin,TCuikSystem *cs);

/** 
   \brief Adds penalty terms to the search criterion.

   Adds the
   <center>\f$w(v-val)^2\f$</center>
   to the equation guiding the search.<br>
   This is useful when incrementally defining a penalty function where we aim
   of finding solutions in the center of the range of some variables.

   This function automatically calls \ref SetCSSearchMode to set the search mode
   to \ref MINIMIZATION_SEARCH it is is not so.

   \param w Weight for the new constraint to add.
   \param v Variable for the new constraint to add.
   \param val Targed value for the new variable. Typically the center of the
              variable range.
   \param cs The cuiksystem to update.
*/
void AddTerm2SearchCriterion(double w,unsigned int v,double val,TCuikSystem *cs);

/****************************************************************************/
/*     Methods to add individual variables/equations to the cuik system     */
/****************************************************************************/

/** 
    \brief Adds a variable to the system.

    Adds a new variable to the system.

    \param v The variable to add.
    \param cs The cuiksystem where to add the variable.

    \return The numerical identifier assigned to the new variable.
            If there is another variable with the same name, this function
	    generates an error.
*/
unsigned int AddVariable2CS(Tvariable *v,TCuikSystem *cs);

/** 
    \brief Adds an equation to the system.

    Adds a new equation to the system. The equation must use the variables
    already added to the system. Repeated equations are not added to the system.

    \param p A set of parameters.
    \param eq The equation to add.
    \param cs The cuiksystem where to add the equation.
*/
void AddEquation2CS(Tparameters *p,Tequation *eq,TCuikSystem *cs);

/** 
    \brief Adds a matrix equation to the system.

    Adds a new matrix equation to the system. The equation must use the variables
    already added to the system. No check is performed to determine if the
    matrix equation is repeated.

    \param p A set of parameters.
    \param eq The matrix equation to add.
    \param cs The cuiksystem where to add the equation.
*/
void AddMatrixEquation2CS(Tparameters *p,TMequation *eq,TCuikSystem *cs);

/****************************************************************************/
/*        Methods to access the data stored in the CuikSystem.              */
/*  These methods provide controlled access to the stored data so that the  */
/*     higher levels can not introduce inconsistancies in the CuikSystem    */
/****************************************************************************/

/** 
    \brief Gets the cuiksystem variables.

    Returns a copy of the variables stored in the cuiksystem.
    This can be seen as a Tvariables copy constructor, thus the output
    variables does not need to be initialized beforehand.

    \param vs Pointer to the space where to copy the variables.
    \param cs The cuiksystem from where to get the variables.

    \sa CopyVaribles
*/
void GetCSVariables(Tvariables *vs,TCuikSystem *cs);

/** 
  \brief Gets points to the variable names.

  Initializes an array of pointers to variable names.

  This is used to print boxes.

  \param varNames The array where to store the pointers.
                  This array must be allocated/deallocated
		  externally.
  \param cs The cuiksystem to query.
*/
void GetCSVariableNames(char **varNames,TCuikSystem *cs);

/** 
    \brief Gets the number of variables already in the cuiksystem.

    Returns the number of variables already in the cuiksystem.

    \param cs The cuiksystem to query.

    \return The number of variables already in the cuiksystem.
*/
unsigned int GetCSNumVariables(TCuikSystem *cs);

/** 
    \brief Gets the number of system variables already in the cuiksystem.

    Returns the number of system variables in the cuiksystem.
    System variables are system+secondary (see \ref GetCSSystemVars).

    \param cs The cuiksystem to query.

    \return The number of system variables already in the cuiksystem.
*/
unsigned int GetCSNumSystemVariables(TCuikSystem *cs);

/** 
    \brief Gets the number of non dynamic variables already in the cuiksystem.

    Returns the number of non dynamic variables in the cuiksystem.

    \param cs The cuiksystem to query.

    \return The number of non dynamic variables already in the cuiksystem.
*/
unsigned int GetCSNumNonDynamicVariables(TCuikSystem *cs);

/** 
    \brief Gets the number of non-dummy variables already in the cuiksystem.

    Returns the number of non-dummy (i.e., the sum of system, secondary and 
    cartesian variables) variables already in the cuiksystem.

    \param cs The cuiksystem to query.

    \return The number of non-dummy variables already in the cuiksystem.
*/
unsigned int GetCSNumNonDummyVariables(TCuikSystem *cs);

/** 
   \brief Determines if a cuiksystem includes velocity information.

   Determines if a cuiksystem includes velocity information.

   \param p The set of parameters.
   \param cs The CuikSystem to query.
*/
boolean CuikHasVelocity(Tparameters *p,TCuikSystem *cs);

/** 
    \brief Gets the a variable from a cuiksystem.

    Returns a copy of one of the variables of the cuiksystem.
    This can be seen as a Tvariable copy constructor, thus the output
    variable does not need to be initialized beforehand.
    
    \param n Numerical identifier of the variable to get.
    \param v Place where to store the copy of the variable.
    \param cs The cuiksystem to query.

    \sa CopyVariable
*/
void GetCSVariable(unsigned int n,Tvariable *v,TCuikSystem *cs);

/** 
    \brief Gets the range of a variable from a cuiksystem.

    Returns a copy of the range of one of the variables of the cuiksystem.
    This can be seen as a Tinterval constructor, thus the output
    interval does not need to be initialized beforehand.
    
    \param n Numerical identifier of the variable to get.
    \param r Place where to store the copy of the interval.
    \param cs The cuiksystem to query.

    \sa CopyInterval
*/
void SetCSVariableRange(unsigned int n,Tinterval *r,TCuikSystem *cs);

/** 
    \brief Gets the numerical identifier of a variable given its name.

    Returns the numerical identifier of a variable given its name.
    
    \param name Name of the variable.
    \param cs The cuiksystem to query.

    \return The numerical identifier. NO_UINT if there is no variable with
            the given name in the cuiksystem.
*/
unsigned int GetCSVariableID(char *name,TCuikSystem *cs);

/** 
   \brief Gets a variable name.
   
   Gets the name of a particular variable.
   The returned pointer should not be manipulated.
   
   \param id The index of the variable.
   \param cs The CuikSystem to query.

   \return A pointer to the variable name of NULL if the variable does not exists.
*/
char *GetCSVariableName(unsigned int id,TCuikSystem *cs);


/** 
   \brief Gets a system variable name.
   
   Gets the name of a particular system variable.
   The returned pointer should not be manipulated.
   
   \param id The index of the system variable (over all
             the system variables).
   \param cs The CuikSystem to query.

   \return A pointer to the variable name of NULL if the variable does not exists.
*/
char *GetCSSystemVariableName(unsigned int id,TCuikSystem *cs);


/** 
   \brief Identifies system variables that survive in the simplified system.

   Identifies system variables that survive in the simplified system.
   
   \param p The set of parameters.
   \param v The variable name.
   \param cs The cuiksystem to query.

   \return TRUE if the variable exists in the simplified system.
*/
boolean IsSystemVarInSimpCS(Tparameters *p,char *v,TCuikSystem *cs);

/** 
    \brief Identifies the system variables.

    Creates an array of booleans with the size of the number of variables
    in the cuiksystem and set to TRUE the entries corresponding to system, 
    secondary, and velocity variables.
    
    In coherence with the definition of the orig_systemVar field of \ref TCuikSystem,
    here we identify system, secondary, and velocity varibles. Internally, though, 
    we differentiate between them (for instance, secondary varibles are not used 
    when splitting boxes).

    \param sv Pointer to the pointer of booleans to be allocated and updated.
    \param cs The cuiksystem to query.

    \return The number of variables in the cuiksystem (size of teh output array).
*/
unsigned int GetCSSystemVars(boolean **sv,TCuikSystem *cs);

/** 
    \brief Identifies the position variables.

    Creates an array of booleans with the size of the number of variables
    in the cuiksystem and set to TRUE the entries corresponding to position,
    i.e., to non-velocity variables.

    \param pv Pointer to the pointer of booleans to be allocated and updated.
    \param cs The cuiksystem to query.

    \return The number of variables in the cuiksystem (size of teh output array).
*/
unsigned int GetCSPositionVars(boolean **pv,TCuikSystem *cs);

/** 
    \brief Identifies the position equations.

    Creates an array of booleans with the size of the number of variables
    in the cuiksystem and set to TRUE the entries corresponding to position,
    i.e., to non-velocity variables.

    \param pv Pointer to the pointer of booleans to be allocated and updated.
    \param cs The cuiksystem to query.

    \return The number of variables in the cuiksystem (size of teh output array).
*/
unsigned int GetCSPositionEqs(boolean **pv,TCuikSystem *cs);

/** 
    \brief Identifies the position or velocity variables.

    Creates an array of booleans with the size of the number of variables
    in the cuiksystem and set to TRUE the entries corresponding to position
    or velocity, i.e., the variables relevant for the dynamics. We essentially
    rule out discriminant variables.

    \param pv Pointer to the pointer of booleans to be allocated and updated.
    \param cs The cuiksystem to query.

    \return The number of variables in the cuiksystem (size of teh output array).
*/
unsigned int GetCSPositionVelocityVars(boolean **pv,TCuikSystem *cs);

/** 
    \brief Identifies the position or velocity equations.

    Creates an array of booleans with the size of the number of variables
    in the cuiksystem and set to TRUE the entries corresponding to position
    or velocity, i.e., the equations relevant for the dynamics. We essentially
    rule out discriminant equations.

    \param pv Pointer to the pointer of booleans to be allocated and updated.
    \param cs The cuiksystem to query.

    \return The number of variables in the cuiksystem (size of teh output array).
*/
unsigned int GetCSPositionVelocityEqs(boolean **pv,TCuikSystem *cs);

/** 
   \brief Determines the topology of a given variable.

   Determines the topology of a given variable (of the original variable set).

   \param vID Identifier of the variable (in the original system).
   \param cs The cuiksystem to query.

   \return The topology of the variable with the given identifier.
*/
unsigned int GetCSVarTopology(unsigned int vID,TCuikSystem *cs);

/** 
    \brief Gets a copy of the system equations.

    Returns a copy of the system equations. This is a Tequations copy
    constructor.
    
    \param eqs Place where to copy the system variables.
    \param cs The cuiksystem to query.

    \sa CopyEquations
*/
void GetCSEquations(Tequations *eqs,TCuikSystem *cs);

/** 
    \brief Gets the number of equations already in the cuiksystem.

    Returns the number of equations already in the cuiksystem.

    \param cs The cuiksystem to query.

    \return The number of equations already in the cuiksystem.
*/
unsigned int GetCSNumEquations(TCuikSystem *cs);

/** 
    \brief Gets the an equation from a cuiksystem.

    Returns a copy of one of the equations of the cuiksystem.
    This can be seen as a Tequation copy constructor.
    
    \param n Numerical identifier of the equation to get.
    \param eq Place where to store the copy of the equation.
    \param cs The cuiksystem to query.

    \sa CopyEquation
*/
void GetCSEquation(unsigned int n,Tequation *eq,TCuikSystem *cs);

/** 
   \brief Identifies polynomial cuiksystems.

   Returns TRUE if the cuiksystem is fully polynomial.

   We check if the original cuiksystem is polynomial since if this
   system is polynomial, so are the rest of systems (simplified,
   simplified+dummified).

   \param cs The cuiksystem to query.

   \return TRUE if the cuiksystem is fully polynomial.
*/
boolean IsCSPolynomial(TCuikSystem *cs);

/** 
   \brief Identifies scalar cuiksystems.

   Returns TRUE if the cuiksystem is fully scalar.

   \param cs The cuiksystem to query.

   \return TRUE if the cuiksystem is fully scalar.
*/
boolean IsCSScalar(TCuikSystem *cs);

/** 
   \brief Defines the Jacobian of a CuikSystem.
   
   Defines the Jacobian of a CuikSystem considering each equation as a
   function.
   
   Defines an array with as many rows as equations and as many columns as
   variables where each entry (i,j) is de derivative of equation \e i
   (considered as a function) with repect to variable \e j.

   \param J The jacobian (output).
   \param cs The cuik system from where to extract the Jacobian.

*/
void GetCSJacobian(TJacobian *J,TCuikSystem *cs);

/** 
   \brief Topology of the variables in the simplified system.

   Creates an array with the topology information for the 
   variables in the simplified system.

   The topology gives information on the type of range for each
   variable (either real or spherical). This is relevant when
   searching for nearest neighbours (in the case of spherical
   topology pi is close to -pi but not in the case of real
   topology).
   
   \param p The set of parameters.
   \param t Space for the output array.
   \param cs The cuiksystem to query.

   \return The number of entries in the output array (i.e., the
           number of variables in the simplified system).
*/
unsigned int GetSimpCSTopology(Tparameters *p,
			       unsigned int **t,TCuikSystem *cs);

/** 
   \brief Topology of the variables in the system.

   Creates an array with the topology information for the 
   variables in the system.

   The topology gives information on the type of range for each
   variable (either real or spherical). This is relevant when
   searching for nearest neighbours (in the case of spherical
   topology pi is close to -pi but not in the case of real
   topology).
   
   \param p The set of parameters.
   \param t Space for the output array.
   \param cs The cuiksystem to query.

   \return The number of entries in the output array (i.e., the
           number of variables in the system).
*/
unsigned int GetCSTopology(Tparameters *p,
			   unsigned int **t,TCuikSystem *cs);

/** 
   \brief Defines the Jacobian of a simplified CuikSystem.
   
   The same as \ref GetCSJacobian but for the simplified system.

   \param p The set of parameters
   \param J The jacobian (output).
   \param cs The cuik system from where to extract the Jacobian.

*/
void GetSimpCSJacobian(Tparameters *p,
		       TJacobian *J,
		       TCuikSystem *cs);

/** 
   \brief Defines the numerical Jacobian of a simplified CuikSystem.
   
   Defines the data necessary to numerically evaluate the Jacobian of
   the position variables/equations of the problem. Such structure
   is only defined in particular systems (systems including only
   matrix equations) and it is used to speed up the evaluation
   of the Jacobian (the evaluation of the symbolic Jacobian is slow
   since many matrix products are repated).

   \param p The set of parameters
   \param nJ The numerical Jacobian structure (output).
   \param cs The cuik system from where to extract the Jacobian.

   \return TRUE if the numerical Jacobian structure is actually created.
           If FALSE nothing is created and there is no need to delete
	   the structure.
*/
boolean GetSimpCSNJacobian(Tparameters *p,
			   TNJacobian *nJ,
			   TCuikSystem *cs);

/** 
   \brief Defines the numerical Hessian of a simplified CuikSystem.
   
   Defines the data necessary to numerically evaluate the Hessian of
   the position variables/equations of the problem. Such structure
   is only defined in particular systems (systems including only
   matrix equations) and it is used to speed up the evaluation
   of the Hessian (the evaluation of the symbolic Hessian is slow
   since many matrix products are repated).

   \param p The set of parameters
   \param sJ The Jacobian of the scalar equations, if any.
   \param nH The numerical Hessian structure (output).
   \param cs The cuik system from where to extract the Jacobian.

   \return TRUE if the numerical Hessian structure is actually created.
           If FALSE nothing is created and there is no need to delete
	   the structure.
*/
boolean GetSimpCSNHessian(Tparameters *p,
			  TJacobian *sJ,
			  TNHessian *nH,
			  TCuikSystem *cs);

/** 
   \brief Adds linear a linear combination of the Jacobian to the system.

   Adds linear a linear combination of the Jacobian to the system. Generates a new
   variable for each equation in the system and creates a linear combination of
   the Jacobian rows using the new variables. Those new variables are normalized
   to avoid getting redudant solutions.
   Only the Jacobian columns corresponding to the selectedVars is used.

   This functions is used when looking for singularities.

   \param p The set of parameters.
   \param selectedVars The variables to take into account. NULL to use all variables.
   \param cs The cuiksystem to modify.
*/
void AddJacobianEquations(Tparameters *p,boolean *selectedVars,TCuikSystem *cs);

/** 
   \brief Adds the velocity equations.

   Generates the velocity variables and equations. We have as many
   velocity variables as variables in the simplified cuiksystem
   and the equations are defined as the product of the position
   Jacobian and the velocity variables.

   Note that if the input cuiksystem already includes velocity
   variables and equations nothing is actually added. Otherwise
   we will be generating acceleration equations and this requires
   some code modifications (specially with the matrix equations).

   \param p The parameters.
   \param vl The velocity limits. Optional. It only makes sense
             to give such limits if the interval problem variables
	     are directly related with degrees of freedom.
	     If not given (i.e., set ot NULL), the MAX_VELOCITY
	     parameter is used.
   \param cs The cuiksystem to extend with the velocity related
             information.
*/
void AddVelocityEquations(Tparameters *p,double *vl,TCuikSystem *cs);

/** 
   \brief Adds a linear combination of the Jacobian to the system.

   This is the same as \ref AddJacobianEquations but the we use the Jacobian of
   the simplified system instead of that of the original system.
   
   Note that the \e selectedVars refer to the original system and they can be
   missing from the original system. We try to translate variables from original
   to simple. Original variables assigned to constants are unselected and variables
   assigned to other variables are replaced accordingly.

   \param p The set of parameters.
   \param selectedVars The variables to take into account. NULL to use all variables.
   \param cs The cuiksystem to modify.
*/
void AddSimplifiedJacobianEquations(Tparameters *p,boolean *selectedVars,TCuikSystem *cs);

/****************************************************************************/
/*                    Methods to solve the CuikSystem.                      */
/****************************************************************************/

/** 
    \brief Reduces a box as much as possible.

    Reduces a box using the constraints included in the cuiksystem and using
    the algorithms described in our 
    <a href="http://www-iri.upc.es/english/publiproject.php?proj=44">papers</a>.
    
    \param p A set of parameters.
    \param varMask The type of variables to reduce (SYSTEM_VAR, CARTESIAN_VAR, DUMMY_VAR). 
                   Different types of variables can be indicated using '|'. A good
		   option is to use ~DUMMY_VAR (this reduces for all variables except
		   for dummy ones).
    \param r The reduction ration for the box.
    \param b The box to be reduced.
    \param cs The cuiksystem with the constraints to use to reduce the box.
*/
unsigned int MaxReduction(Tparameters *p,unsigned int varMask,double *r,Tbox *b,TCuikSystem *cs);

/** 
    \brief Generates samples for a cuiksystem.

    Determine points for which all the equations in the cuiksystem hold. 
    Actually it determines tiny boxes (boxes with size below EPSILON) and the
    center of the box is taken as the solution point. Since, in general, EPSILON
    is very small (1e-6) the error of the given solutions is also tiny (order of
    1e-12).<br>
    The function generates two types of output, the solution boxes (stored 
    in a <em>fname</em>_samples.sol file) and the central point for each solution point
    (stored in a <em>fname</em>.samples file).<br>
    Samples are used in the planning process, to generate roadmap vertexes.<br>
    This functions generates samples in the search space defined by the variable ranges.
    For a function that generate samples in a particular box see SampleCuikSystemInBox.
    <br>
    Note that a sample includes values only for the system variables, that are the
    ones governing the movement for the mechanisms at hand.
    <br>
    The algorithm implemented for sampling proceed by fixing <em>ndof</em> variables
    at random and then solving the problem via CuikSolve.
    <br>

    \param p A set of parameters.
    \param fname Base name for the output files. If NULL, the solutions are not
                 stored in any file.
    \param sb List of boxes where to store the solutions. If NULL, the boxes are not
              listed.
    \param nsamples The number of samples to generate.
    \param ntries Number of times we have to try to generate samples (i.e., of fixing
                  some variables at random and solving). Use \ref NO_UINT not to fix
		  any limit.
    \param ndof The number of degrees of freedom of the mechanism under considerations.
                If we use NO_UINT, the function tries to determine the number of
		degrees of freedom from the variables and equations 
		(ndof = Num Variables-Num Equations). However, our systems are typically
		overconstrained and this simple guess often fails.
    \param cs The cuiksystem from which to drawn samples.

    \return TRUE if the samples are actually generated before reaching the maximum
                 number of tries.

    \sa CuikPlan SampleCuikSystemInBox
*/
boolean SampleCuikSystem(Tparameters *p,char *fname,Tlist *sb,
			 unsigned int nsamples,unsigned int ntries,
			 unsigned int ndof,TCuikSystem *cs);

/** 
    \brief Generates samples for a cuiksystem in given box.

    This like function SampleCuikSystem but the samples are generated only in the
    given box. Morover, this function can store the (tiny) solution boxes in a list
    of boxes.


    \param p A set of parameters.
    \param fname Base name for the output files. If NULL, the solutions are not
                 stored in any file.
    \param sb List of boxes where to store the solutions. If NULL, the boxes are not
              listed.
    \param nsamples The number of samples to generate.
    \param ntries Number of times we have to try to generate samples (i.e., of fixing
                  some variables at random and solving). Use \ref NO_UINT not to fix
		  any limit.
    \param ndof The number of degrees of freedom of the mechanism under considerations.
                If we use NO_UINT, the function tries to determine the number of
		degrees of freedom from the variables and equations 
		(ndof = Num Variables-Num Equations). However, our systems are typically
		overconstrained and this simple guess often fails.
    \param init_box Box where to generate samples.
    \param cs The cuiksystem from which to drawn samples.

    \return TRUE if the samples are actually generated before reaching the maximum
                 number of tries.

    \sa SampleCuikSystem
*/
boolean SampleCuikSystemInBox(Tparameters *p,char *fname,Tlist *sb,
			      unsigned int nsamples,unsigned int ntries,
			      unsigned int ndof,
			      Tbox *init_box,TCuikSystem *cs);


/** 
    \brief Generates samples for a cuiksystem.

    This function is very similar to \ref SampleCuikSystem but degrees of freedom
    are progressively fixed instead of fixed all simultaneously.

    \param p A set of parameters.
    \param fname Base name for the output files. If NULL, the solutions are not
                 stored in any file.
    \param sb List of boxes where to store the solutions. If NULL, the boxes are not
              listed.
    \param fixVars Boolean array with the variables that can be fixed. If NULL the
                   system variables are used.
    \param nsamples The number of samples to generate.
    \param ntries Number of times we have to try to generate samples (i.e., of fixing
                  some variables at random and solving). Use \ref NO_UINT not to fix
		  any limit.
    \param ndof The number of degrees of freedom of the mechanism under considerations.
                If we use NO_UINT, the function tries to determine the number of
		degrees of freedom from the variables and equations 
		(ndof = Num Variables-Num Equations). However, our systems are typically
		overconstrained and this simple guess often fails.
    \param cs The cuiksystem from which to drawn samples.

    \return TRUE if the samples are actually generated before reaching the maximum
                 number of tries.
*/
boolean IncrementalSampleCuikSystem(Tparameters *p,char *fname,Tlist *sb,
				    boolean *fixVars,
				    unsigned int nsamples,unsigned int ntries,
				    unsigned int ndof,TCuikSystem *cs);
/**   
    \brief Generates samples for a cuiksystem in given box.

    This function is very similar to \ref SampleCuikSystemInBox but degrees of freedom
    are progressively fixed instead of fixed all simultaneously.

    \param p A set of parameters.
    \param fname Base name for the output files. If NULL, the solutions are not
                 stored in any file.
    \param sb List of boxes where to store the solutions. If NULL, the boxes are not
              listed.
    \param fixVars Boolean array with the variables that can be fixed. If NULL the
                   system variables are used.
    \param nsamples The number of samples to generate.
    \param ntries Number of times we have to try to generate samples (i.e., of fixing
                  some variables at random and solving). Use \ref NO_UINT not to fix
		  any limit.
    \param ndof The number of degrees of freedom of the mechanism under considerations.
                If we use NO_UINT, the function tries to determine the number of
		degrees of freedom from the variables and equations 
		(ndof = Num Variables-Num Equations). However, our systems are typically
		overconstrained and this simple guess often fails.
    \param init_box Box where to generate samples.
    \param cs The cuiksystem from which to drawn samples.

    \return TRUE if the samples are actually generated before reaching the maximum
                 number of tries.
*/
boolean IncrementalSampleCuikSystemInBox(Tparameters *p,char *fname,Tlist *sb,
					 boolean *fixVars,
					 unsigned int nsamples,unsigned int ntries,
					 unsigned int ndof,
					 Tbox *init_box,TCuikSystem *cs);

/** 
   \brief CuikNewton on the simplified system.

   This is simplified a version of \ref CuikNewtonInBox since
     - It operates in the simplified system.
     - It can not include inequality constraints in the system.
     - It does not takes into account the original box.
     - It does not check the equation error at the end of the iteration
       (we assume convervenge if the step is small)
     .

   This used when defining a RRT: we sample points in ambient space (of the simplified
   system) and we want to converge to the manifold (if possible).
   
   If you want to understand what is done in \ref CuikNewtonInBox it is better
   to start by this function.
   
   \todo Reduce the duplicity of code between \ref CuikNewtonSimp and \ref CuikNewtonInBox.
         This is not easy since \ref CuikNewtonInBox includes lots of code to take into account
	 box bondaries and inequalitites and code to convert from boxes in the original system
	 to boxes in the simplified system at the beggining of the function and the revese change
	 at the end of the function.

   \param p The set of parameters.
   \param x The initial and output point. This is a point in the \b simplified system.
   \param cs The cuiksystem.

   \return \ref DIVERGED if we could not reach a solution point or \ref CONVERGED_IN_GLOBAL 
           if a solution point is found.
*/
unsigned int CuikNewtonSimp(Tparameters *p,double *x,TCuikSystem *cs);

/** 
   \brief Applies Newton-Rhapson to a set of equations.

   Find a solution of a cuiksystem set of equations
   using the Newton-Rhapson method. 

   The initial point is sampled form the given box.

   \param p A set of parameters.
   \param bIn The box from where sample the initial point.
   \param sol The space where to store solution of the cuik system as a point.
              This must be allocated by the caller.
   \param b_sol The solution as a punctual box. If the Newton diverged this will
                be a copy of the input box. The space is allocated inside this
		function.
   \param cs The cuiksystem to solve.

   \return \ref DIVERGED, \ref CONVERGED_IN_BOX, \ref CONVERGED_IN_GLOBAL, 
           \ref CONVERGED_OUTSIDE_GLOBAL.

   \sa CuikNewton
*/
unsigned int CuikNewtonInBox(Tparameters *p,
			     Tbox *bIn,double *sol,Tbox *b_sol,TCuikSystem *cs);

/** 
   \brief Applies Newton-Rhapson to a set of equations.

   Find a solution of a cuiksystem set of equations
   using the Newton-Rhapson method.
   
   This function is only a wrapper of \ref CuikNewtonInBox 
   using the initial box (i.e., the one defined form the variable ranges)
   to sample the initial point.

   \param p A set of parameters.
   \param sol Space where to store the solution as a point. This must be allocated
              by the caller.
   \param b_sol The solution as a punctual box. If the Newton diverged this will
                be a copy of the input box. This box is allocated inside the function.
   \param cs The cuiksystem to solve.

   \return TRUE if the Newton-Raphson process converged to a solution in the
           initial box.

   \sa CuikNewtonInBox, GenerateInitialBox.
*/
boolean CuikNewton(Tparameters *p,double *sol,Tbox *b_sol,TCuikSystem *cs);

/** 
   \brief Applies gradient descent to a set of equations.

   Find a solution of a cuiksystem set of equations
   using the gradient descent method. 

   The initial point is sampled form the given box.

   \param p A set of parameters.
   \param bIn The box from where sample the initial point.
   \param sol The space where to store solution of the cuik system as a point.
              This must be allocated by the caller.
   \param b_sol The solution as a punctual box. If the Newton diverged this will
                be a copy of the input box. The space is allocated inside this
		function.
   \param cs The cuiksystem to solve.

   \return \ref DIVERGED, \ref CONVERGED_IN_BOX, \ref CONVERGED_IN_GLOBAL, 
           \ref CONVERGED_OUTSIDE_GLOBAL.

   \sa CuikGradient
*/
unsigned int CuikGradientInBox(Tparameters *p,
			       Tbox *bIn,double *sol,Tbox *b_sol,TCuikSystem *cs);

/** 
   \brief Applies gradient descent to a set of equations.

   Find a solution of a cuiksystem set of equations
   using gradient descent method.
   
   This function is only a wrapper of \ref CuikGradientInBox 
   using the initial box (i.e., the one defined form the variable ranges)
   to sample the initial point.

   \param p A set of parameters.
   \param sol Space where to store the solution as a point. This must be allocated
              by the caller.
   \param b_sol The solution as a punctual box. If the Newton diverged this will
                be a copy of the input box. This box is allocated inside the function.
   \param cs The cuiksystem to solve.

   \return TRUE if the gradient descent process converged to a solution in the
           initial box.

   \sa CuikGradientInBox, GenerateInitialBox.
*/
boolean CuikGradient(Tparameters *p,double *sol,Tbox *b_sol,TCuikSystem *cs);


/** 
    \brief Determines the solution set for a cuiksystem.

    This is the entry function for the Cuik solver. It takes as input
    a cuiksystem and returns a set of boxes bounding the solution set.
    If the solutions are isolated (zero-dimensional) the output is
    a set of isolated boxes. If the solution is continuous the output
    is a set of boxes bounding the solution space. Be aware that
    isolating solution sets with high dimensionality can be expensive.
    To this end it is recommended to use the parallel version of cuik


    \param p A set of parameters.
    \param restart TRUE is the process has be re-started from a previous execution
                   that was, for some reason, crashed.
    \param fstate Name of the file from which to read the state (if restart is TRUE)
                  and where to save the state from time to time (concretely every
		  STATE_PERIOD boxes).
    \param searchSpace Box defining the search space where to look for the solutions. 
                       If null, the global search space is used (the one defined from 
		       the user-given variable ranges).
    \param f_out File where to store the solution boxes and the related information
                 such as the parameters, the compilation flags and the statistics
		 of the solving process (time, number of processed boxes,...). If NULL
		 the boxes are not stored in the file (in this case <em>sols</em> must
		 not be NULL).
    \param sol List of boxes where to store the solutions. If NULL, the boxes are not
               listed.
    \param cs The cuiksystem to solve.

    \sa MPI_SolveCuikSystem
*/
void SolveCuikSystem(Tparameters *p,
		     boolean restart,char *fstate,Tbox *searchSpace,
		     FILE *f_out,Tlist *sol,TCuikSystem *cs);

#if (_USE_MPI)
/** 
    \brief Determines the solution set for a cuiksystem. Main scheduler.

    This is the parallel version of SolveCuikSystem. Actually this function is
    the main scheduler, i.e., the one in charge of managing the boxes to be
    processes to send them to the child processors. to collec the result, and
    to deal with them accordingly (bisect, consider solutions, discard if they
    are empty,...).<br>
    The main difference with SolveCuikSystem is that solutions are not included
    in any list but only stored in a file.

    \param p A set of parameters.
    \param restart TRUE is the process has be re-started from a previous execution
                   that was, for some reason, crashed.
    \param fstate Name of the file from which to read the state (if restart is TRUE)
                  and where to save the state from time to time (concretely every
		  STATE_PERIOD boxes).    
    \param searchSpace Box defining the search space where to look for the solutions. 
                       If null, the global search space is used (the one defined from 
		       the user-given variable ranges).
    \param f_out File where to store the solution boxes and the related information
                 such as the parameters, the compilation flags and the statistics
		 of the solving process (time, number of processed boxes,...).
    \param cs The cuiksystem to solve.

    \sa SolveCuikSystem
*/
void MPI_SolveCuikSystem(Tparameters *p,
			 boolean restart,char *fstate,Tbox *searchSpace,
			 FILE *f_out,TCuikSystem *cs);
/** 
    \brief Determines the solution set for a cuiksystem. Child process.

    This is the function executed by the child processors when solving
    a problem in a multi-processor environment.

    \param p A set of parameters.
    \param cs The cuiksystem to solve.

    \sa MPI_SolveCuikSystem
*/
  void MPI_TreatBox(Tparameters *p,TCuikSystem *cs);
#endif


/****************************************************************************/
/*                           Auxiliary Methods.                             */
/****************************************************************************/
/** 
    \brief Gives the search space in the form of a box.

    Determines the search space for the solutions of a cuiksystem in the form
    of a box defined from the variable ranges.
    <br>
    This can be seen as a box constructor.

    \param box The output box with the variable ranges.
    \param cs The cuiksystem.
*/
void GenerateInitialBox(Tbox *box,TCuikSystem *cs);

/** 
    \brief Gives the search space in the form of a box for the simplified system.

    The same as \ref GenerateInitialBox but for the simplified system.

    \param p The set of parameters.
    \param box The output box with the variable ranges.
    \param cs The cuiksystem.
*/
void GenerateSimpInitialBox(Tparameters *p,Tbox *box,TCuikSystem *cs);

/** 
   \brief Regenerates a box from the system variables.

   Generates values for all variables in the box (including dummies and
   cartesian ones) from the values of the system variables.

   In general, solutions only include system variables and for many operations
   the cartesian/dummy ones are also needed (for plotting, for refining a 
   solution,...). This functions reverses the removal of the non-system variables
   in a box.

   Observe that the box must be given in the original system and with values
   only for the system variables. This is different of what happens with
   \ref RegenerateOriginalBox where the input box has values for all
   variables in the simplified system.

   \param p The set of parameters.
   \param b The box to regenerate. It must have the correct dimensionality 
            (i.e., the number of variables in the cuiksystem including
	    the system and dummy ones) but with values only for the system
	    variables. At the end of the call the values for dummy/cartesian
	    variables will be also defined.
   \param cs The cuiksystem.

   \return TRUE if the regeneration process can be compleated without problems 
          and \ref FALSE if during the reconstruction we realize that the input
	  box is and \ref EMPTY_BOX "empty box".
*/
boolean RegenerateSolution(Tparameters *p,Tbox *b,TCuikSystem *cs);

/** 
   \brief Regenerates a solution point from the system variables.

   Defines a solution point including the dummy and cartesian variables from an
   array with only values for the system variables.

   This function is based on \ref RegenerateSolution.

   \param p The set of parameters.
   \param pt Values for the system variables.
   \param rp Reconstructed solution with values for all variables. The space for
             this array is allocated in this function.
   \param cs The cuiksystem

   \return The number of entries of the output array \e rp.
*/
unsigned int RegenerateSolutionPoint(Tparameters *p,double *pt,double **rp,TCuikSystem *cs);

/** 
   \brief Generates a box in the original cuiksystem from a
          box of the simplified one.

   Generates a box in the original cuiksystem from a
   box of the simplified one.

   You can generate a simplified cuiksystem using
   \ref cuiksimplify.c "cuiksimplify" and then solve it. To obtain the
   solution boxes in the un-simplified (or original) system
   using the \ref cuikunsimplify.c "cuikunsimplify" 
   application that basically relies on this function.

   \param p The set of parameters.
   \param boxS The input box in the simplified and dummified system.
   \param boxO The output box in the original system. The box
               is created insided this function.
   \param cs The cuiksystem to which boxes are supposed to refer to.
             If this is not so the behavior is undefined.
	  
*/
void RegenerateOriginalBox(Tparameters *p,Tbox *boxS,Tbox *boxO,TCuikSystem *cs);
  
/** 
   \brief Generates an original point from a simplified point.

   Defines a point in the original system from a point in the simplified system.

   It is like \ref RegenerateOriginalBox but on points and not on boxes and taking
   points from the simplified system and not the simplified+dummified.

   This is basically used from \ref cuikatlas.c "cuikatlas" that operates on the
   simplified system.

   \param p The set of parameters.
   \param s The point in the simplified system.
   \param o The output on in the original system. Space allocated internally.
   \param cs The cuiksystem.

   \return The size of the output array (number of variables in the original system).
*/
unsigned int RegenerateOriginalPoint(Tparameters *p,double *s,double **o,TCuikSystem *cs);

/** 
   \brief Generates a simplified point.

   Generates a simplified point from an original one. This is the inverse mapping
   of \ref RegenerateOriginalPoint.

   \param p The set of parameters.
   \param o The point in the original system.
   \param s The output in the simplified system. Space allocated internally.
   \param cs The cuiksystem.

   \return The size of the output array (number of variables in the simplified system).
*/
unsigned int GenerateSimplifiedPoint(Tparameters *p,double *o,double **s,TCuikSystem *cs);

/** 
   \brief Transforms arrays of booleans from the original to the simplified system.

   Transforms an array of booleans that selects a subset of the variables
   in the original system to a subset of variables in the simplified
   system. Only the entries for the variables of the original system
   also used in the simplified system are preserved.

   \param p The set of parameters.
   \param bo The array of booleans in the original system.
   \param bs The array of boolans in the simplified system. The space for this
             array is allocated internally and must be deallocated by the caller.
   \param cs The cuiksystem.

   \return The number of entries in the output array (i.e., the number of
           variables in the simplified cuiksystem).
*/
unsigned int SimplifyBooleanArray(Tparameters *p,boolean *bo,boolean **bs,
				  TCuikSystem *cs);

/** 
    \brief Determines the best dimensions to split a given box.

    Determines the dimension for which it is more advisable to
    split a box. The criterion to determine the split dimension
    can  be selected through the parameters.

    \param p A set of parameters.
    \param b The box to be split.
    \param cs The cuiksystem.

    \return The dimension along to which the box is to be bisected.
*/
unsigned int ComputeSplitDim(Tparameters *p,Tbox *b,TCuikSystem *cs);

/** 
    \brief Determines if a given point is fully included in the
           system sub-box (i.e., the sub-box fot the system variables).

    Determines if a given point is fully included in the
    system sub-box (i.e., the sub-box fot the system variables).
    The point is typically one obtained via sampling.

    \param v A vector of doubles with one entry for each one of
             the system variables.
    \param b The box with the ranges for the variables (including the system
             ones).
    \param cs The cuiksystem.

    \return TRUE if the point is fully included in the system sub-box.

    \sa SampleCuikSystemInBox SampleCuikSystem
*/
boolean PointInSystemBox(Tvector *v,Tbox *b,TCuikSystem *cs);

/** 
  \brief Evaluates the equation set on a point.

  Evaluates the equation set on a point. 

  Only equalities are evaluated and thus only space for as many ouputs as equalities
  is needed in \e r.

  \param p The evaluation point.
  \param r The array with the evaluation of each equation. The space for
           this array should be allocated externally.
  \param cs The cuiksystem to query.
*/
void EvaluateCSEquations(double *p,double *r,TCuikSystem *cs);

/** 
   \brief Evaluates the simplified equation set on a point.

   The same as \ref EvaluateCSEquations but on the simplified system.

   The direct access to the simplified equations is needed to obtain an efficient
   \ref cuikatlas.c "cuikatlas" (and associated utilities). If defined on the original systems
   they will include too many (trivial) equations and fixed variables.

   Note that in this case the input point \e p must be defined on the simplified
   space.
   
   \param pr The set of parameters.
   \param p The evaluation point.
   \param r The array with the evaluation of each equation. The space for
            this array should be allocated externally.
   \param cs The cuiksystem to query.
*/
void EvaluateSimpCSEquations(Tparameters *pr,double *p,double *r,TCuikSystem *cs);

/** 
   \brief Evaluates a subset of the simplified equation set on a point.

   The same as \ref EvaluateSimpCSEquations but on a subset of equations.

   This is used to evaluate the independent subset of equations during
   the atlas construction.
   
   \param pr The set of parameters.
   \param se The array of booleans selecting the equations to evaluate.
   \param p The evaluation point.
   \param r The array with the evaluation of each equation. The space for
            this array should be allocated externally.
   \param cs The cuiksystem to query.
*/
void EvaluateSubSetSimpCSEquations(Tparameters *pr,boolean *se,double *p,double *r,TCuikSystem *cs);

/** 
   \brief Evalates the norm of the error in a point.

   Evaluates the equations on a point and returns the norm of the error.
   Recall that solution points should have zero error. 
   This is similar to \ref ErrorInSolution but works on points and not
   on boxes and takes into account all equations and not only system ones.

   \param pr The set of parameters.
   \param p The point on which to evaluate the equations (including values
            for all variables).
   \param cs The cuiksystem with the equations to evaluate.

   \return The norm of the error for the given point.
*/
double ErrorInCSEquations(Tparameters *pr,double *p,TCuikSystem *cs);

/** 
   \brief Evaluates the norm of the error in a point for the simplified equations.

   The same as \ref ErrorInCSEquations but in the simplified set of
   equations.

   The direct access to the simplified equations is needed to obtain an efficient
   \ref cuikatlas.c "cuikatlas" (and associated utilities). If defined on the original systems
   they will include too many (trivial) equations and fixed variables.

   Note that in this case the input point \e p must be defined on the simplified
   space.

   \param pr The set of parameters.
   \param p The point on which to evaluate the equations (including values
            for all variables in the simplified system).
   \param cs The cuiksystem with the equations to evaluate.

   \return The norm of the error for the given point.
*/
double ErrorInSimpCSEquations(Tparameters *pr,double *p,TCuikSystem *cs);

/** 
   \brief Evalutes the equation to minimize in a given point.

   This interface is provided to use it form T-RRT. The same
   interface is used for other cost function.

   \param p The set of parameters.
   \param simp TRUE if the solution point is given in the simplified sytem.
   \param s The solution point 
   \param cs The cuiksystem with the equation to evaluate.
*/
double EvaluateCSCost(Tparameters *p,boolean simp,double *s,void *cs);

/** 
   \brief Evaluates the Jacobian of the system in a given point.

   Returns the matrix resulting from evaluationg the Jacobian of 
   the system in a given point.

   The Jacobian is defined on the original cuiksystem (without
   simplification nor dummyfications).
   
   \param p The evaluation point.
   \param J The Jacobian matrix to be defined.
   \param cs The cuiksystem

   \sa GetCSJacobian, DeleteCSJacobian.
*/
void EvaluateCSJacobian(double *p,double ***J,TCuikSystem *cs);

/** 
    \brief Maximum error for a box.

    Computes the error for the solution represented by a box. The error
    is computed taking the central point of the box and replacing the
    values in the equation set.
    
    Only system equality equations are taken into account in the error.

    \param b The solution box.
    \param cs The cuiksystem.

    \return Maximum error for the equations for the central point of the
            box.
*/
double ErrorInSolution(Tbox *b,TCuikSystem *cs);

/** 
    \brief Maximum inequality error for a box.

    Computes the error for the solution represented by a box
    as far as inequalities is concerned. The error
    is computed taking the central point of the box and replacing the
    values in the equation set.
    
    This can be seen as a complement of \ref ErrorInSolution when
    inequalities are also to be taken into account.

    \param b The solution box.
    \param cs The cuiksystem.

    \return Maximum error for the inequality equations for the central 
            point of the box.
*/
double ErrorInInequalities(Tbox *b,TCuikSystem *cs);

/** 
   \brief Tests if all inqualities hold for a given point.

   Checks if all inqualities hold for a given point.
   For many processes (i.e., continuation, etc) only
   the equalities are taken into account. Thus, we need
   a function to check if the inequalities hold.

   \param p The point.
   \param cs The cuiksystem to check.

   \return TRUE if all the inequalities hold for the given point.
*/
boolean InequalitiesHoldOnPoint(double *p,TCuikSystem *cs);

/** 
   \brief Tests if all simplified inqualities hold for a given point.

   Checks if all inqualities hold for a given point for the simplified
   system.

   \param pr the set of parameters.
   \param p The point (in the simplified system).
   \param cs The cuiksystem to check.

   \return TRUE if all the inequalities hold for the given point.

   \sa InequalitiesHoldOnPoint
*/
boolean SimpInequalitiesHoldOnPoint(Tparameters *pr,double *p,TCuikSystem *cs);

/** 
   \brief Computes the maximum error in all the simplified inqualities for a given point.

   Determines the maximum error in the inequalities in the simplified system.

   \param pr the set of parameters.
   \param p The point (in the simplified system).
   \param cs The cuiksystem to check.

   \return The error in the inequalities in the simplified system.

   \sa SimpInequalitiesHoldOnPoint
*/
double ErrorInSimpInequalitiesOnPoint(Tparameters *pr,double *p,TCuikSystem *cs);


/** 
   \brief Computes the dimension of the solution space.

   Computes the dimension of the solution space assuming that the given
   point 'p' is a regular point.

   \param pr The set of parameters.
   \param p The regular solution point. Given in the original format (not
            in the simplified one).
   \param cs The cuiksystem to query.

   \return The dimension of the solution manifold.
*/
unsigned int ManifoldDimension(Tparameters *pr,double *p,TCuikSystem *cs);

/****************************************************************************/
/*               Output the information in the CuikSystem                   */
/****************************************************************************/

/** 
    \brief Prints a cuiksystem.

    Writes the cuiksystem in a file that can be <em>stdout</em>.

    \param p A set of parameters.
    \param f The stream where to write the cuiksystem.
    \param cs The cuiksystem.
*/
void PrintCuikSystem(Tparameters *p,FILE *f,TCuikSystem *cs);

/** 
    \brief Prints the simplified cuiksystem.

    Writes the simplified cuiksystem in a file that can be <em>stdout</em>.
    If the DEBUG mode is above 1 it first print the original system and
    then the simplified one (in the same file)

    \param p A set of parameters.
    \param f The stream where to write the simplified cuiksystem.
    \param cs The cuiksystem.

    \sa PrintCuikSystem
*/
void PrintCuikSystemWithSimplification(Tparameters *p,FILE *f,TCuikSystem *cs);


/** 
   \brief Saves the simplification information associated with a cuiksystem.

   Saves the simplification information associated with a cuiksystem. 

   \param p A set of parameters.
   \param f The stream where to write the simplification information.
   \param cs The cuiksystem. 
*/
void SaveCuikSystemSimplification(Tparameters *p,FILE *f,TCuikSystem *cs);


/****************************************************************************/
/*                                 Destructor                               */
/****************************************************************************/

/** 
    \brief Destructor.

    Deletes a cuiksystem.

    \param cs The cuiksystem to be deleted.
*/
void DeleteCuikSystem(TCuikSystem *cs);

#endif
