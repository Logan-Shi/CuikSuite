#ifndef WCSH
#define WCSH

#include "boolean.h"
#include "parameters.h"

#include "cuiksystem.h"
#include "world.h"

#ifdef _OPENMP
  #include <omp.h>
#endif

/** \file wcs.h

    \brief Macros and functions to operate on worlds/cuiksystems.

    Interface that unifies the access to world and cuiksystems so that
    the atlas related applications can operate on both structures.
*/

/** 
    \brief Type defining the equations on which the atlas is defined.
    
    Type including the equations on which the atlas is defined.
    Note that equations are sometimes
    in explicit form (when using cuik files) or in implicit way
    (when using world files). 
*/
typedef struct {
  boolean isCS;    /**< TRUE if the equations are taken from a cuik file */
  TCuikSystem *cs; /**< The equations info in the form of a cuik system. 
		        Only used if \e isCS is TRUE. */
  Tworld *w;       /**< The equations info in the form of a world. 
		        Only used if \e isCS is FALSE. */
} TAtlasBase;


/**  \def CS_WD_EXT

    \brief Possible extensions for the equation files.
    
    Extension for the equation files. 
    This is only used for printing.

    \sa CUIK_EXT, WORLD_EXT
*/ 
#define CS_WD_EXT "world/cuik"


/** 
    \brief Initializes a world or a CuikSystem structre.

    Initializes the equations from a file. First we try to read the
    equations from cuik file. If this fails, we try to read them
    from a world file. If not possible, we trigger and error.

    The cuik files are typically derived from the world ones
    (using \ref cuikequations.c "cuikequations"). So if the cuik
    file has been generated, then it probably means you want
    to work with it. Otherwise just delete (or rename) it and
    we will read the world file instead.

    We have two main set of equation. One (the original system) is the one
    as given in the given file. The other (the simplified system) is the
    same after introducing trivial simplifications (removing variables
    with constant values, replacing variables by equivalent ones,...).
    Typically we operate with the simplified system but input and output
    points are given in the original system. Therefore we have to
    translate between them when necessary. But this is out of the
    scope of this function.

    \sa  InitCuikSystemFromFile, InitWorldFromFile
*/
void InitCSWDFromFile(Tparameters *pr,char *name,TAtlasBase *wcs);

/**  \def CS_WD_INIT

    \brief Initializes the equations from a file.
    
    Initializes the equations from a file.

    \param pr Pointer to the set of parameters.
    \param name The file name given by the caller.
    \param wcs Pointer to the equation structure to initialize.
    
    \sa InitCSWDFromFile
*/  
#define CS_WD_INIT(pr,name,wcs) InitCSWDFromFile(pr,name,wcs)

/**  \def CS_WD_FROM_WORLD

    \brief Initializes the equations from a world structure.
    
    Initializes the equations from a world structure.

    CAUTION: Do not use \ref CS_WD_DELETE for structures 
             created using this macro. The internal pointer 
             to world in \e wcs copies the
	     input pointer. Thus a delete would produce
	     a double free.

    \param ptr A pointer to the world structure.
    \param wcs Pointer to the equation structure to initialize.
    
    \sa InitCSWDFromFile
*/  
#define CS_WD_FROM_WORLD(ptr,wcs) { (wcs)->isCS=FALSE; (wcs)->cs=NULL; (wcs)->w=ptr; } 

/**  \def CS_WD_FROM_CUIKSYSTEM

    \brief Initializes the equations from a CuikSystem structure.
    
    Initializes the equations from a CuikSystem structure.

    CAUTION: Do not use \ref CS_WD_DELETE for structures 
             created using this macro. The internal pointer 
             to CuikSystem  \e wcs copies the
	     input pointer. Thus a delete would produce
	     a double free.

    \param ptr A pointer to the CuikSystem structure.
    \param wcs Pointer to the equation structure to initialize.
    
    \sa InitCSWDFromFile
*/  
#define CS_WD_FROM_CUIKSYSTEM(ptr,wcs) { (wcs)->isCS=TRUE; (wcs)->cs=ptr; (wcs)->w=NULL; } 

/**  \def ON_CUIKSYSTEM

    \brief TRUE if the atlas is defined on a cuiksystem.
    
    TRUE if the equations defining the implicit conf. space are
    given by a cuiksystem and FALSE if they are given by a world file
    (possibly involving obstacles,...)

    \param wcs Pointer to the equation structure to query.
*/  
#define ON_CUIKSYSTEM(wcs) (wcs)->isCS


/**  \def GET_WORLD

    \brief Returns the world from an TAtlasBase.
    
    Returns the world from an TAtlasBase.

    \param wcs Pointer to the equation structure to query.
*/  
#define GET_WORLD(wcs) (wcs)->w

/**  \def GET_CUIKSYSTEM

    \brief Returns the CuikSystem from an TAtlasBase.
    
    Returns the CuikSystem from an TAtlasBase.

    \param wcs Pointer to the equation structure to query.
*/  
#define GET_CUIKSYSTEM(wcs) (wcs)->cs

/**  \def CS_WD_EVALUATE_SIMP_EQUATIONS

    \brief Evaluates the simplified set of equations.
    
    Evaluates the simplified set of equations.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param r Pointer to the result.
    \param wcs Pointer to the equation set.

    \sa EvaluateSimpCSEquations, WorldEvaluateSimpEquations
*/
#define CS_WD_EVALUATE_SIMP_EQUATIONS(pr,p,r,wcs) if ((wcs)->isCS) EvaluateSimpCSEquations(pr,p,r,(wcs)->cs); else WorldEvaluateSimpEquations(pr,p,r,(wcs)->w);

/**  \def CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS

    \brief Evaluates a subset of the simplified set of equations.
    
    Evaluates a subset of the simplified set of equations.

    \param pr Pointer to the set of parameters.
    \param st Array of booleans indicating the subset to evaluate. 
    \param p Pointer to the point.
    \param r Pointer to the result.
    \param wcs Pointer to the equation set.

    \sa EvaluateSimpCSEquations, WorldEvaluateSimpEquations
*/
#define CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS(pr,st,p,r,wcs) if ((wcs)->isCS) EvaluateSubSetSimpCSEquations(pr,st,p,r,(wcs)->cs); else WorldEvaluateSubSetSimpEquations(pr,st,p,r,(wcs)->w);

/**  \def CS_WD_SIMP_INEQUALITIES_HOLD

    \brief Cheks if all inequalities hold.
    
    Determines if the set of inequalities in the simplified set of
    equations actually hold for a given point.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param wcs Pointer to the equation set.

    \sa SimpInequalitiesHoldOnPoint, WorldSimpInequalitiesHold
*/
#define CS_WD_SIMP_INEQUALITIES_HOLD(pr,p,wcs) ((wcs)->isCS ? SimpInequalitiesHoldOnPoint(pr,p,(wcs)->cs) : WorldSimpInequalitiesHold(pr,p,(wcs)->w))

/**  \def CS_WD_SIMP_INEQUALITIES_ERROR

    \brief Maximum error in the inequalities.
    
    Determines the maximum error in the inequalities in the simplified set of
    equations actually hold for a given point.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param wcs Pointer to the equation set.

    \sa ErrorInSimpInequalitiesOnPoint, WorldErrorInSimpInequalities
*/
#define CS_WD_SIMP_INEQUALITIES_ERROR(pr,p,wcs) ((wcs)->isCS ? ErrorInSimpInequalitiesOnPoint(pr,p,(wcs)->cs) : WorldErrorInSimpInequalities(pr,p,(wcs)->w))

/**  \def CS_WD_GET_SYSTEM_VARS

    \brief Gets the system variables.
    
    Gets an array of booleans with TRUE for the system variables.

    \param sv Pointer to the array where to store the system var flags.
    \param wcs Pointer to the equation set.

    \return The number of variables in the problem.

    \sa GetCSSystemVars, GetWorldSystemVars
*/
#define CS_WD_GET_SYSTEM_VARS(sv,wcs) ((wcs)->isCS ? GetCSSystemVars(sv,(wcs)->cs) : GetWorldSystemVars(sv,(wcs)->w))

/**  \def CS_WD_GET_POSITION_VARS

    \brief Gets the position variables.
    
    Gets an array of booleans with TRUE for the position variables
    (i.e., non-velocity variables).

    \param pv Pointer to the array where to store the system var flags.
    \param wcs Pointer to the equation set.

    \return The number of variables in the problem.

    \sa GetCSPositionVars, GetWorldPositionVars
*/
#define CS_WD_GET_POSITION_VARS(pv,wcs) ((wcs)->isCS ? GetCSPositionVars(pv,(wcs)->cs) : GetWorldPositionVars(pv,(wcs)->w))

/**  \def CS_WD_GET_POSITION_VELOCITY_VARS

    \brief Gets the position/velocity variables.
    
    Gets an array of booleans with TRUE for the position or velocity variables
    (i.e., non-velocity variables). This is used to do not take into account
    the equations not related with dynamics.

    \param pv Pointer to the array where to store the system var flags.
    \param wcs Pointer to the equation set.

    \return The number of variables in the problem.

    \sa GetCSPositionVelocityVars, GetWorldPositionVelocityxVars
*/
#define CS_WD_GET_POSITION_VELOCITY_VARS(pv,wcs) ((wcs)->isCS ? GetCSPositionVelocityVars(pv,(wcs)->cs) : GetWorldPositionVelocityVars(pv,(wcs)->w))

/**  \def CS_WD_GET_POSITION_EQS

    \brief Gets the position equations.
    
    Gets an array of booleans with TRUE for the position equations
    (i.e., non-velocity equations).

    \param pe Pointer to the array where to store the system var flags.
    \param wcs Pointer to the equation set.

    \return The number of equations in the problem.

    \sa GetCSPositionEqs, GetWorldPositionEqs
*/
#define CS_WD_GET_POSITION_EQS(pe,wcs) ((wcs)->isCS ? GetCSPositionEqs(pe,(wcs)->cs) : GetWorldPositionEqs(pe,(wcs)->w))

/**  \def CS_WD_GET_POSITION_VELOCITY_EQS

    \brief Gets the position and velocity equations.
    
    Gets an array of booleans with TRUE for the position or velocity equations
    (i.e., non-velocity equations). This is used to do not take into account
    equations not related with the dynamics (e.g., discriminant equations).

    \param pe Pointer to the array where to store the system var flags.
    \param wcs Pointer to the equation set.

    \return The number of equations in the problem.

    \sa GetCSPositionVelocityEqs, GetWorldPositionVelocityEqs
*/
#define CS_WD_GET_POSITION_VELOCITY_EQS(pe,wcs) ((wcs)->isCS ? GetCSPositionVelocityEqs(pe,(wcs)->cs) : GetWorldPositionVelocityEqs(pe,(wcs)->w))

/** 
   \brief Name of a particular system variables.

   Returns the name of a particular system variable. This is used 
   to print the names of the variables used in several applications
   such as \ref cuikplotpath.c "cuikplotpath", 
   \ref cuikplotforcefield.c "cuikplotforcefield", 
   \ref cuikplotatlas.c "cuikplotatlas", etc.

   \param id The index of the variable (over the system variables only).
   \param wcs The structure to query.
*/
#define CS_WD_GET_SYSTEM_VAR_NAME(id,wcs) ((wcs)->isCS ? GetCSSystemVariableName(id,(wcs)->cs) : GetWorldSystemVarName(id,(wcs)->w))

/**  \def CS_WD_GET_NUM_SYSTEM_VARS

    \brief Gets the number of system variables.
    
    Number of system vars.

    \param wcs Pointer to the equation set.

    \sa GetCSNumSystemVars, GetWorldNumSystemVars
*/
#define CS_WD_GET_NUM_SYSTEM_VARS(wcs) ((wcs)->isCS ? GetCSNumSystemVariables((wcs)->cs) : GetWorldNumSystemVariables((wcs)->w))


/**  \def CS_WD_GET_VAR_TOPOLOGY

    \brief Gets the variable topology.
    
    Gets an array with the topology flag for each variable in the original system.

    \param varID Identifier of the variaable whose topology is required.
    \param wcs Pointer to the equation set.

    \sa GetCSVarTopology, GetWorldVarTopology
*/
#define CS_WD_GET_VAR_TOPOLOGY(varID,wcs)  ((wcs)->isCS ? GetCSVarTopology(varID,(wcs)->cs) : GetWorldVarTopology(varID,(wcs)->w))

/**  \def CS_WD_REGENERATE_ORIGINAL_POINT

    \brief Completes an original point from a simplified one.
    
    Compleates a point of the original system of equations from the values
    of the variables in the simplified system.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param o Pointer where to store the results.
    \param wcs Pointer to the equation set.

    \sa RegenerateOriginalPoint, RegenerateWorldOriginalPoint
*/
#define CS_WD_REGENERATE_ORIGINAL_POINT(pr,p,o,wcs) ((wcs)->isCS ? RegenerateOriginalPoint(pr,p,o,(wcs)->cs) : RegenerateWorldOriginalPoint(pr,p,o,(wcs)->w))

/**  \def CS_WD_INIT_CD

    \brief Initializes the collision detector.
    
    Initializes the collision detector. This only has effects if we are operating over
    world structures (the cuiksystem do not have obstacle information).

    \param pr The set of parameters.
    \param mt Maximum number of threads to check collision in parallel.
    \param wcs Pointer to the equation set.

    \sa InitWorldCD
*/
#define CS_WD_INIT_CD(pr,mt,wcs) { if (!(wcs)->isCS) InitWorldCD(pr,mt,(wcs)->w); }

/** \def CS_ANY_COLLISION

    \brief Determines if there is any collision to be checked.

    Determines if there is any collision to be checked.

    \param wcs Pointer to the equation set.
*/
#define CS_ANY_COLLISION(wcs) (((wcs)->isCS)?FALSE:AnyCollision((wcs)->w))

/**  \def CS_WD_TEST_COLLISION

    \brief Checks collisions.
    
    Checks the collision status of a configuration.

    \param f Output flag. TRUE if the configuration is in collision.
    \param pr Pointer to the set of parameters.
    \param all TRUE if we want to detect all collision. FALSE for only the first collision.
    \param s Pointer to the configuration in the simple system.
    \param sPrev Pointer to the previous configuration (also in the simple
                 system). Only used for continuous collision detection.
    \param wcs Pointer to the set of equations and obstacles.

    \sa RegenerateWorldOriginalPoint, MoveAndCheckCD
*/
#ifdef _OPENMP
#define CS_WD_TEST_COLLISION(f,pr,all,s,sPrev,wcs) { if (((wcs)->isCS)||(!WorldCanCollide((wcs)->w))) f=FALSE; else { double *oPrev=NULL,*o; \
                                               RegenerateWorldOriginalPoint(pr,s,&o,(wcs)->w);if ((sPrev!=NULL)&&(WorldContinuousCD((wcs)->w))) RegenerateWorldOriginalPoint(pr,sPrev,&oPrev,(wcs)->w); \
					       f=MoveAndCheckCD(pr,all,omp_get_thread_num(),o,oPrev,(wcs)->w); \
					       free(o);if (oPrev!=NULL) free(oPrev);} \
                                             }
#else
#define CS_WD_TEST_COLLISION(f,pr,all,s,sPrev,wcs) { if (((wcs)->isCS)||(!WorldCanCollide((wcs)->w))) f=FALSE; else { double *oPrev=NULL,*o; \
                                               RegenerateWorldOriginalPoint(pr,s,&o,(wcs)->w);if ((sPrev!=NULL)&&(WorldContinuousCD((wcs)->w))) RegenerateWorldOriginalPoint(pr,sPrev,&oPrev,(wcs)->w); \
					       f=MoveAndCheckCD(pr,all,0,o,oPrev,(wcs)->w); \
					       free(o);if (oPrev!=NULL) free(oPrev);} \
                                             }
#endif

/**  \def CS_WD_IN_COLLISION

    \brief Checks if a configuration is in collision.
    
    Determines the first collision of a configuration.

    \param f Output flag. TRUE if the configuration is in collision.
    \param pr Pointer to the set of parameters.
    \param s Pointer to the configuration in the simple system.
    \param sPrev Pointer to the previous configuration (also in the simple
                 system). Only used for continuous collision detection.
    \param wcs Pointer to the set of equations and obstacles.

    \sa RegenerateWorldOriginalPoint, MoveAndCheckCD
*/
#define CS_WD_IN_COLLISION(f,pr,s,sPrev,wcs) CS_WD_TEST_COLLISION(f,pr,FALSE,s,sPrev,wcs)


/**  \def CS_WD_ALL_COLLISIONS

    \brief Checks if a configuration is in collision.
    
    Determines all the collisions of a configuration.

    \param f Output flag. TRUE if the configuration is in collision.
    \param pr Pointer to the set of parameters.
    \param s Pointer to the configuration in the simple system.
    \param sPrev Pointer to the previous configuration (also in the simple
                 system). Only used for continuous collision detection.
    \param wcs Pointer to the set of equations and obstacles.

    \sa RegenerateWorldOriginalPoint, MoveAndCheckCD
*/
#define CS_WD_ALL_COLLISIONS(f,pr,s,sPrev,wcs) CS_WD_TEST_COLLISION(f,pr,TRUE,s,sPrev,wcs)

/**  \def CS_WD_ORIGINAL_IN_COLLISION

    \brief Checks if a configuration is in collision.
    
    Determines if a configuration given in the original form is in
    collision.

    This is typically used instead of \ref CS_WD_IN_COLLISION when
    we already have the point in the original system
    (i.e., after using \ref CS_WD_REGENERATE_ORIGINAL_POINT).

    \param pr Pointer to the set of parameters.
    \param o Pointer to the configuration in the original system.
    \param oPrev Pointer to the previous configuration in the original system.
                 Only used for continuous collision detection.
    \param wcs Pointer to the set of equations and obstacles.

    \sa CS_WD_IN_COLLISION, MoveAndCheckCD
*/
#ifdef _OPENMP
  #define CS_WD_ORIGINAL_IN_COLLISION(pr,o,oPrev,wcs) (((wcs)->isCS)||(!WorldCanCollide((wcs)->w)) ? FALSE : MoveAndCheckCD(pr,FALSE,omp_get_thread_num(),o,oPrev,(wcs)->w))
#else
  #define CS_WD_ORIGINAL_IN_COLLISION(pr,o,oPrev,wcs) (((wcs)->isCS)||(!WorldCanCollide((wcs)->w)) ? FALSE : MoveAndCheckCD(pr,FALSE,0,o,oPrev,(wcs)->w))
#endif

/** \def CS_WD_COST_PTR

    \brief  Pointer to the base type.

    Returns the pointer to the base type. This is used as a parameter for the cost function.

    \sa CS_WD_COST_FN
*/
#define CS_WD_COST_PTR(wcs) ((wcs)->isCS ? (void *)((wcs)->cs) : (void *)((wcs)->w))

/** \def CS_WD_COST_FN

    \brief  Cost function for a given configution.

    Gives the cost function used to evaluate a given set of configurations.

    \sa EvaluateCSCost, EvaluateWorldCost
*/
#define CS_WD_COST_FN(wcs) ((wcs)->isCS ? EvaluateCSCost : EvaluateWorldCost)

/** \def CS_WD_COST

    \brief Evaluates the cost of a given configution.

    Computes the cost of a given set of configurations.
    In the world files the cost is defined using the "avoid limit" clause.
    In the cuik files it can be defined as an arbitrary equation invoving the
    problem variables.

    \param pr Pointer to the set of parameters.
    \param simp TRUE if the point is in simplified form
    \param p Pointer to the point
    \param wcs Pointer to the set of equations.

    \sa EvaluateCSCost, EvaluateWorldCost
*/
#define CS_WD_COST(pr,simp,p,wcs) ((wcs)->isCS ? EvaluateCSCost(pr,simp,p,(void *)((wcs)->cs)) : EvaluateWorldCost(pr,simp,p,(void *)((wcs)->w)))

/**  \def CS_WD_GET_SIMP_TOPOLOGY

    \brief Gets the simplified variable topology.
    
    Gets an array with the topology flag for each variable in the simplified system.

    \param pr Pointer to the set of parameters.
    \param tp Pointer to the array where to store the topology.
    \param wcs Pointer to the set of equations.

    \sa CS_WD_GET_VAR_TOPOLOGY, GetSimpCSTopology, GetWorldSimpTopology
*/
#define CS_WD_GET_SIMP_TOPOLOGY(pr,tp,wcs) ((wcs)->isCS ? GetSimpCSTopology(pr,tp,(wcs)->cs) : GetWorldSimpTopology(pr,tp,(wcs)->w))

/**  \def CS_WD_GET_TOPOLOGY

    \brief Gets the variable topology.
    
    Gets an array with the topology flag for each variable in the system.

    \param pr Pointer to the set of parameters.
    \param tp Pointer to the array where to store the topology.
    \param wcs Pointer to the set of equations.

    \sa CS_WD_GET_VAR_TOPOLOGY, GetCSTopology, GetWorldTopology
*/
#define CS_WD_GET_TOPOLOGY(pr,tp,wcs) ((wcs)->isCS ? GetCSTopology(pr,tp,(wcs)->cs) : GetWorldTopology(pr,tp,(wcs)->w))

/**  \def CS_WD_REGENERATE_SOLUTION_POINT

    \brief Compleates a solution point with the dummy variables.
    
    Compleates a solution point including only values for the system
    variables with the values for the non-system (dummy) variables.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param r Pointer to the array where to store the result.
    \param wcs Pointer to the set of equations.

    \sa RegenerateSolutionPoint, RegenerateWorldSolutionPoint
*/
#define CS_WD_REGENERATE_SOLUTION_POINT(pr,p,r,wcs) ((wcs)->isCS ? RegenerateSolutionPoint(pr,p,r,(wcs)->cs) : RegenerateWorldSolutionPoint(pr,p,r,(wcs)->w))

/**  \def CS_WD_GENERATE_SIMPLIFIED_POINT

    \brief Generates a simplified point from an original one.
    
    Generates a point in the simplified system from a point in the original system.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param r Pointer to where to store the result.
    \param wcs Pointer to the set of equations.

    \sa GenerateSimplifiedPoint, WorldGenerateSimplifiedPoint
*/
#define CS_WD_GENERATE_SIMPLIFIED_POINT(pr,p,r,wcs)  ((wcs)->isCS ? GenerateSimplifiedPoint(pr,p,r,(wcs)->cs) : WorldGenerateSimplifiedPoint(pr,p,r,(wcs)->w))

/**  \def CS_WD_ERROR_IN_SIMP_EQUATIONS

    \brief Computes the error in the simplified system for a given point.
    
    Computes the error in the simplified system for a given point.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param wcs Pointer to the set of equations.

    \sa ErrorInSimpCSEquations, WorldErrorInSimpEquations
*/
#define CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,p,wcs) ((wcs)->isCS ? ErrorInSimpCSEquations(pr,p,(wcs)->cs) : WorldErrorInSimpEquations(pr,p,(wcs)->w))

/**  \def CS_WD_ERROR_IN_EQUATIONS

    \brief Computes the error for a given point.
    
    Computes the error in the for a given point. The difference with respect 
    to \ref CS_WD_ERROR_IN_SIMP_EQUATIONS is that here the point in not
    simplified.
    
    \param pr The parameters.
    \param p Pointer to the point.
    \param wcs Pointer to the set of equations.

    \sa ErrorInCSEquations, WorldErrorInEquations
*/
#define CS_WD_ERROR_IN_EQUATIONS(pr,p,wcs) ((wcs)->isCS ? ErrorInCSEquations(pr,p,(wcs)->cs) : WorldErrorInEquations(pr,p,(wcs)->w))

/**  \def CS_WD_GENERATE_SIMP_INITIAL_BOX

    \brief Computes the global box for the simplified system.
    
    Computes a box with the valid range for the variables of the simplifed system.

    \param pr Pointer to the set of parameters.
    \param b Pointer to the output box.
    \param wcs Pointer to the set of equations.

    \sa GenerateSimpInitialBox, GetWorldSimpInitialBox
*/
#define CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,b,wcs) { if ((wcs)->isCS) GenerateSimpInitialBox(pr,b,(wcs)->cs); else GetWorldSimpInitialBox(pr,b,(wcs)->w); }

/**  \def CS_WD_GET_SIMP_JACOBIAN

    \brief Computes the Jacobian of the simplified system.
    
    Computes the symbolic Jacobian of the simplified system.

    \param pr Pointer to the set of parameters.
    \param J Pointer to the Jacobian.
    \param wcs Pointer to the set of equations.

    \sa GetSimpCSJacobian, GetWorldSimpJacobian
*/
#define CS_WD_GET_SIMP_JACOBIAN(pr,J,wcs) { if ((wcs)->isCS)  GetSimpCSJacobian(pr,J,(wcs)->cs); else GetWorldSimpJacobian(pr,J,(wcs)->w); }

/**  \def CS_WD_GET_SIMP_NJACOBIAN

    \brief Computes the numerical Jacobian of the simplified system.
    
    Defines the structure.

    \param pr Pointer to the set of parameters.
    \param nJ Pointer to the numerical structure to create.
    \param wcs Pointer to the set of equations.

    \return TRUE if the structure is actually created (it can only be created on particular systems).

    \sa GetSimpCSNJacobian, GetWorldSimpNJacobian
*/
#define CS_WD_GET_SIMP_NJACOBIAN(pr,nJ,wcs) ((wcs)->isCS?GetSimpCSNJacobian(pr,nJ,(wcs)->cs):GetWorldSimpNJacobian(pr,nJ,(wcs)->w))

/**  \def CS_WD_GET_SIMP_NHESSIAN

    \brief Computes the numerical Hessian of the simplified system.
    
    Defines the structure.

    \param pr Pointer to the set of parameters.
    \param sJ The Jacobian for the position scalar equations.
    \param nH Pointer to the numerical structure to create.
    \param wcs Pointer to the set of equations.

    \return TRUE if the structure is actually created (it can only be created on particular systems).

    \sa GetSimpCSNHessian, GetWorldSimpNHessian
*/
#define CS_WD_GET_SIMP_NHESSIAN(pr,sJ,nH,wcs) ((wcs)->isCS?GetSimpCSNHessian(pr,sJ,nH,(wcs)->cs):GetWorldSimpNHessian(pr,sJ,nH,(wcs)->w))


/**  \def CS_WD_MANIFOLD_DIMENSION

    \brief Computes the dimension of the solution set.
    
    Computes the dimension of the solution set assuming that we have a regular solution point.

    \param pr Pointer to the set of parameters.
    \param p The regular solution point (in the original form, not in the simplified).
    \param wcs Pointer to the set of equations.
*/
#define CS_WD_MANIFOLD_DIMENSION(pr,p,wcs) ((wcs)->isCS ?  ManifoldDimension(pr,p,(wcs)->cs) : WorldManifoldDimension(pr,p,(wcs)->w))

/**  \def CS_WD_NEWTON_IN_SIMP

    \brief Applies a Newton procedure to move a point towads the manifold.
    
    Applies a Newton procedure to move a point towads the manifold defined by the equations.

    \param pr Pointer to the set of parameters.
    \param p Pointer to the point.
    \param wcs Pointer to the set of equations.

    \sa CuikNewtonSimp, WorldSimpCuikNewton
*/ 
#define CS_WD_NEWTON_IN_SIMP(pr,p,wcs) ((wcs)->isCS ? CuikNewtonSimp(pr,p,(wcs)->cs) : WorldSimpCuikNewton(pr,p,(wcs)->w))

/**  \def CS_WD_HAS_VELOCITY

    \brief Determines if the problem includes velocity information.
    
    Determines if the problem includes velocity variables and equations.

    \param pr Pointer to the set of parameters.
    \param wcs Pointer to the set of equations.
*/
#define CS_WD_HAS_VELOCITY(pr,wcs) ((wcs)->isCS ? CuikHasVelocity(pr,(wcs)->cs) : WorldHasVelocity(pr,(wcs)->w))

/**  \def CS_WD_DELETE

    \brief Destructor of the equation structure.
    
    Releases the memory used to store the equation structure.

    \param wcs Pointer to the set of equations.

    \sa DeleteCuikSystem, DeleteWorld
*/
#define CS_WD_DELETE(wcs)  { if ((wcs)->isCS) { DeleteCuikSystem((wcs)->cs); free((wcs)->cs); } else { DeleteWorld((wcs)->w); free((wcs)->w); } }

#endif
