#ifndef KEQUATIONH
#define KEQUATIONH

#include "vector.h"
#include "equation.h"
#include "boolean.h"
#include "csmapping.h"

#include <stdio.h>


/** 
    \file kequation.h
 
    \brief Definition of the kino-equation operations.

    Definition of the kino-equation operations.

    Kino-equations are equations defined on the velocity space, i.e., equations
    appearing as additional rows on the Jacobian of the system of equations
    but that are not directly derived from the derivative of a system equation.

    Kino-equations are Pfaffian equations. 

    \sa TKequation, kequation.c.
*/

/** 
   \brief Initial number of factors in a kino-equation.

   Initial number of factors in a kino-equation. Enlarged as needed.
*/
#define INIT_SIZE_KEQ 10

/**  \brief Kino-equation.

    Kino-equation or equation defined on the velocity space.
    These are pfaffian equations on the velocity and therefore, they can be
    expressed as a(x) * v^T = 0, where a(x) is a vector of expressions (or
    scalar equations) and v is the velocity vector.

    \sa mequation.h, mequation.c.
*/
typedef struct {
  Tvector a;    /**< The vector of scalar equations, one for each velocity component */ 
} TKequation;

/** 
   \brief Initializes a kino-equation.

   Initializes a kino-equation.

   \param ke The kino-equation.
*/
void InitKEquation(TKequation *ke);

/** 
   \brief Adds a factor to a kino-equation.
   
    Adds a factor to a kino-equation. Kino-equations are in the form
    a(x)*v^T = sum_{i=1}^{n} a_i(x)*v_i = 0
    In this function we are adding one of the terms a_i to the equations.

   \param i The variable index.
   \param f The factor to add.
   \param ke The kino-equation where to add the term.
*/
void AddFactor2KEquation(unsigned int i,Tequation *f,TKequation *ke);

/** 
   \brief Returns one factor from the kino-equation.

   Returns the factor for a given variable from the kino-equation.

   \param i The index of the variable whose factor is needed.
   \param ke The kino-equation.

   \return A pointer to the factor. If the factor is not defined
           yet or empty NULL is returned.
*/
Tequation *GetFactorFromKEquation(unsigned int i,TKequation *ke);

/** 
   \brief Copies a kino-equation.

   Makes a copy of a kino-equation.

   \param ke_dst The kino-equation to create.
   \param ke_src The kino-equation to copy.
*/
void CopyKEquation(TKequation *ke_dst,TKequation *ke_src);

/** 
   \brief Applies the un-simplification mapping to a kino equation.

   Transform a kino equation expressed in a simplified set of variables
   into an equation in the original set of variables.
   The relation between the two sets of variables is given by a
   mapping.

   \param map The mapping relating the two sets of variables.
   \param ke The kino equation to rewrite.

   \sa Tmapping
*/
void RewriteKinoEquation2Orig(Tmapping *map,TKequation *ke);

/** 
   \brief Determines if a variable is actually used in the kino-equation.

   Determines if the derivative of a variable is actually used in the kino-equation.

   \param nv The variable identifier.
   \param ke The kino-equation to check.
*/
boolean VarIncludedinKEquation(unsigned int nv,TKequation *ke);

/** 
   \brief Shifts down the indices in kino-equation.

   When removing a variable from the problem, we have to remove
   the corresponding kino-equation (it must be empty 0*v'=0 since
   otherwise an error is triggered). Moreover, the rest of variables
   with index above the removed equation must be decreased by one.
   In this case, the variables in the kino-factors are eventually
   modified. If any of this factors include variable 'nv' an error
   is trigered.

   \param nv The variable we are removing from the system.
   \param ke The kino-equation.
*/
void ShiftVariablesInKEquation(unsigned int nv,TKequation *ke);

/** 
   \brief Fixes a variable in a kino-equation

   Fixes a variable in all factors and removes the corresponding
   factor since if v=ct v'=0 and the corresponding factor can
   be ignored.

   \param epsilon Numerical tolerance to clean factor equations.
   \param nv The variable to remove.
   \param ct The constant to replace the variable.
   \param ke Th kino-equation.
*/
void FixVarInKEquation(double epsilon,unsigned int nv,double ct,TKequation *ke);

/** 
   \brief Replaces a variable by another variable.
   
   Replaces a variable. The factor for the removed variable is eliminated
   and added to the other variable. If nv=nvNew then
   nv'=nvNew' which implies that the factor of nv has to be added
   to the factor of nvNew to keep the kino-equation.

   \param epsilon Numerical tolerance to clean factor equations.
   \param nv The variable to replace.
   \param nvNew The variable to use in the replacement.
   \param ke The kino equation to modify.  
*/
void ReplaceVarInKEquation(double epsilon,unsigned int nv,unsigned int nvNew,TKequation *ke);

/** 
  \brief Prints a kino equation.

  Writes a kino equation to a given stream.

  \param f The stream where to print the kino equation.
  \param varNames The name of the variables.
	          If this parameter is NULL the printed
	          names for the variables are <em>v_X</em> with \e X the index
	          of the variable.
  \param ke The kino equation to print.
*/
void PrintKEquation(FILE *f,char **varNames,TKequation *ke);

/** 
   \brief Resets a kino equation

   Resets the space used by a kino-equation but the
   equation can still be re-used.

   \param ke The kino-equation to reset.
*/
void ResetKEquation(TKequation *ke);

/** 
   \brief Deletes a kino equation

   Releases the space used by a kino-equation.

   \param ke The kino-equation to delete.
*/
void DeleteKEquation(TKequation *ke);

#endif
