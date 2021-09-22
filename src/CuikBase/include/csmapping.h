#ifndef CSMAPPINGH
#define CSMAPPINGH

#include "boolean.h"
#include "variables.h"
#include "box.h"
#include "linear_constraint.h"

/** \file csmapping.h
    \brief Definition of the Tmapping type and the associated functions. 
    
    Definition of the Tmapping type and the associated functions. 

    \sa Tmapping, TCuikSystem, Tvariables.
*/

/************************************************************************************/
/** \brief In a Tmapping, variable no related with any variable.

    In a Tmapping, variable no related with any variable.
*/
#define NOREL   0

/** \brief In a Tmapping, variable related to another variable.

    In a Tmapping, variable related to another variable.
*/
#define REL2VAR 1

/** \brief In a Tmapping, variable related to constant value.

    In a Tmapping, variable related to a constant value.
*/
#define REL2CT  2 
/************************************************************************************/

/** 
   \brief Mapping between the sets of variables in two different cuiksystems.

   We define the relation between the variables of a original cuiksystem
   and the variables of a simplified version of this cuiksystem.
   The simplification can be either a sub-system (variables in the
   simplified set are a sub-set of the variables in the original system)
   or the result of linear simplifications, i.e., simplifications that replace
   a variable by a linear combination of other variables (including the trivial
   assigment to a constant).

   Variables in the simple system are always included in the original system
   but the reverse is not true.

   \sa csmapping.h csmapping.c
*/
typedef struct {
  Tvariables *original;  /**< Variables in the original cuiksystem.*/
  Tvariables *simple;    /**< Variables in the simplified cuiksystem.*/

  unsigned int sizeO;    /**< Number of variables in the original cuiksystem.*/
  unsigned int sizeS;    /**< Number of variables in the simplified cuiksystem.*/

  unsigned int *orig;    /**< Variable in the original system equivalent to the a
		              particular variable in the simple system. */

  boolean *related;      /**< TRUE if the variable in the original system is related to
		              a variable/constant in the simplified system. */
  TLinearConstraint *lc; /**< Linear combination that define the value of a \e related
			      variable in the original system in function of the
			      variables in the simple system. */
} Tmapping;

/** 
    \brief Constructor.

    Generates a trivial mapping between two variable sets. The mapping is defined
    by checking which variables in one set are also present in the other. We identify
    variables using their name.<br>
    The mapping includes a copy of the variable sets. In this way, posterior modificications
    of the sets does not affect the mapping. The variable sets, though, are only used
    to pretty print the mappings.

    \param o Variables in the original system.
    \param s Variables in the simplified system.
    \param m The mapping to initialize.
*/
void InitMapping(Tvariables *o,Tvariables *s,Tmapping *m);

/** 
    \brief Copy constructor.

    Copies one mapping into another.

    \param m_dst The mapping to create via copy.
    \param m_src The original mapping.
*/
void CopyMapping(Tmapping *m_dst,Tmapping *m_src);

/** 
    \brief Size of the variable set in the original system.

    Size of the variable set in the original system.

    \param m The mapping to query.

    \return The number of variables in the set of variables in the original system.
*/
unsigned int GetSizeOriginal(Tmapping *m);

/** 
    \brief Size of the variable set in the simplified system.

    Size of the variable set in the simplified system.

    \param m The mapping to query.

    \return The number of variables in the set of variables in the simplified system.
*/
unsigned int GetSizeSimple(Tmapping *m);

/** 
    \brief Set a relation for a variable in the original set.

    Links a variable in the original problem with a variable in the simplified problem
    via a linear relation <br>
    <center>nvo=a*nvs+b</center>

    \param nvo Numerical identifier of the variable in the original set.
    \param lc The linear combination defining the relation.
    \param m The mapping where to store the relation.
*/
void SetOriginalVarRelation(unsigned int nvo,TLinearConstraint *lc,Tmapping *m);

/** 
    \brief Gets the relation for a variable in the original set with the variables in 
           the simple set.

    Returns the linear constraint of variables in the simple set that defines 
    a variable in the original set.

    The output linear constraint is defined inside this function.

    \param nvo Numerical identifier of the variable in the original set.
    \param lc The output linear combination defining the relation.
    \param m The mapping to query.
*/
void GetOriginalVarRelation(unsigned int nvo,TLinearConstraint *lc,Tmapping *m);

/** 
   \brief Identify original variables also present in the simple system.

   Returns TRUE if there is a variable in the simple system with the
   same name as variable \e v in the original system.

   \param v Identifier of the variable in the original system.
   \param m The mapping to query.

   \return TRUE if there is a variable in the simple system with the
   same name as variable \e v in the original system.
*/
boolean IsInSimple(unsigned int v,Tmapping *m);

/** 
    \brief Gets the original identifier of a simplified variable.

    Gets the numerical identifier in the original set of variables corresponding
    to a variable in the simplified set (given by its numerical identifier).

    \param v Identifier of the variable in the simplified set.
    \param m The mapping from where to get the relation.

    \return The numerical identifier of the variable in the original set corresponding
            to the given variable identifier in the simplified set.
*/
unsigned int GetVarIDInOriginal(unsigned int v,Tmapping *m);

/** 
    \brief Gets a simple box from an original one.

    Applies the mapping to define a box corresponding to the simple system from a
    box corresponding to the original system. We simply get the sub-set of the original
    variables used in the simplified one and join them into a box.

    The box \e s is create inside this function.

    \param o The box in the original system.
    \param s The box in the simplified system.
    \param m The mapping to apply.
*/
void SimpleFromOriginal(Tbox *o,Tbox *s,Tmapping *m);

/** 
    \brief Gets a simple point from an original one.

    The same as \ref SimpleFromOriginal but operating on points and not
    on boxes.

    \param o The point in the original system.
    \param s The point in the simplified system. The space for this point is
             allocated inside this function.
    \param m The mapping to apply.
*/
void SimplePointFromOriginal(double *o,double **s,Tmapping *m);

/** 
    \brief Gets a original box from an simplified one.

    Applies the mapping to define a box corresponding to the original system from a
    box corresponding to the simple system. <br>
    In this case, the values of the box in the simple system override the values
    of the given box in the original system. The rationale is that if we take care
    of the simplified box to be defined properly, then we do not need to take
    care of undoing the mapping.

    Variables in the original, not included in the simplification are not changed.

    Note the difference with \ref SimpleFromOriginal : here the output box \e o is
    just updated and not created from scratch.

    \param s The box in the simplified system.
    \param o The box in the original system.
    \param m The mapping to apply.
*/
void UpdateOriginalFromSimple(Tbox *s,Tbox *o,Tmapping *m);

/** 
    \brief Gets a original point from an simplified one.

    The same as \ref UpdateOriginalFromSimple but operating on points
    instead of on boxes.
   
    \param s The point in the simplified system.
    \param o The point in the original system.
    \param m The mapping to apply.
*/
void UpdateOriginalPointFromSimple(double *s,double *o,Tmapping *m);

/** 
    \brief Prints a mapping.

    Prints a the linear relations defining a mapping into a stream, 
    possibly <em>stdout</em>. The mapping
    is printed in the form
    <center>vo=a*vs+b</center><br>
    or<br>
    <center>vo=b</center>
    where
    <em>vo</em> is an original variable and <em>vs</em> is a simplifed one.

    \param f The stream where to print the mapping
    \param m The mapping to apply.
*/
void PrintMapping(FILE *f,Tmapping *m);

/**
   \brief Constructor. Loads the mapping information from a file.

   Loads the mapping information into a file.

   Note that the variable sets are load from the file and, thus,
   the mappings build from a file have no access to the variable
   names (this is used only for pretty printing the mappings).
   
   \param f The file from where to read the mapping.
   \param m The mapping to defined.
*/
void LoadMapping(FILE *f,Tmapping *m);

/**
   \brief Saves the mapping information into a file.

   Saves the mapping information into a file.

   Note that the variable sets are not stored in the files.
   See \ref LoadMapping for more about the consequences of this.
   
   \param f The file where to store the mapping.
   \param m The mapping to save.
*/
void SaveMapping(FILE *f,Tmapping *m);

/** 
    \brief Destructor.

    Deletes a mapping.

    \param m The mapping to delete.
*/
void DeleteMapping(Tmapping *m);

#endif
