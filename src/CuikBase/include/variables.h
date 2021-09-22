#ifndef VARIABLESH
#define VARIABLESH

#include "variable.h"
#include "box.h"
#include "boolean.h"

#include <stdio.h>

/** 
   \file variables.h

   \brief Definition of the Tvariables type and the associated functions. 

   Definition of the Tvariables type and the associated functions. 

   We have four types of variables: 
    - system variables: the variables of the mechanisms.
    - dummy variables: introduced when linearizing the problem. Dummy variables are only
      reduced using equation-wise constraints and are never bisected.
    - cartesian varibles: they refer to the cartesian position of point in the mechanisms. Thes
      variables are reduced but not bisected.
    .

   The position of a variable in the set is taken as its identifier and used to refer to
   this variable from many other structures (i.e., Tvariable_set).

   \sa Tvariables, variables.c.
*/

/** 
   \brief Set of variables of a cuiksystem. 

   Set of variables  involved in a cuiksystem.

   \sa variables.h, variables.c.
*/
typedef struct {
  unsigned int max_variables; /**< Maximum number of variables in the set.*/
  unsigned int n;  /**< Current number of variables in the set.*/
  unsigned int sys; /**< Number of system variables in the set.*/
  unsigned int sec; /**< Number of secondary variables in the set.*/
  unsigned int dum; /**< Number of dummy variables in the set.*/
  unsigned int car; /**< Number of cartesian variables in the set.*/
  unsigned int vel; /**< Number of velocity variables in the set.*/
  unsigned int ndy; /**< Number of non-dynamic variables in the set.*/
  Tvariable **vs; /**< The information for each variable.*/
} Tvariables;

/** 
   \brief Constructor.

   Defines an empty set of variables.

   \param vs The variable set to initalize.
*/
void InitVariables(Tvariables *vs);


/** 
   \brief Copy onstructor.

   Defines a set of variables from another set

   \param vs_dst The variable set to initalize.
   \param vs_src The variable set from where to copy.
*/
void CopyVariables(Tvariables *vs_dst,Tvariables *vs_src);

/** 
   \brief Gets the number of variables in a set.

   Returns the number of variables in a variable set.

   \param vs The variable set to query.

   \return The number of variables in the set.
*/
unsigned int NVariables(Tvariables *vs); 

/** 
   \brief Gets the number of system variables in a set.

   Returns the number of system variables in a variable set.

   \param vs The variable set to query.

   \return The number of system variables in the set.
*/
unsigned int GetNumSystemVariables(Tvariables *vs);

/** 
   \brief Gets the number of secondary variables in a set.

   Returns the number of secondary variables in a variable set.

   \param vs The variable set to query.

   \return The number of secondary variables in the set.
*/
unsigned int GetNumSecondaryVariables(Tvariables *vs);

/** 
   \brief Gets the number of dummy variables in a set.

   Returns the number of dummy variables in a variable set.

   \param vs The variable set to query.

   \return The number of dummy variables in the set.
*/
unsigned int GetNumDummyVariables(Tvariables *vs);

/** 
   \brief Gets the number of cartesian variables in a set.

   Returns the number of cartesian variables in a variable set.

   \param vs The variable set to query.

   \return The number of cartesian variables in the set.
*/
unsigned int GetNumCartesianVariables(Tvariables *vs);

/** 
   \brief Gets the number of position variables in a set.

   Returns the number of position variables in a variable set.

   \param vs The variable set to query.

   \return The number of position variables in the set.
*/
unsigned int GetNumPositionVariables(Tvariables *vs);

/** 
   \brief Gets the number of velocity variables in a set.

   Returns the number of velocity variables in a variable set.

   \param vs The variable set to query.

   \return The number of velocity variables in the set.
*/
unsigned int GetNumVelocityVariables(Tvariables *vs);

/** 
   \brief Gets the number of non-dynamic variables in a set.

   Returns the number of non-dynamic variables in a variable set.

   \param vs The variable set to query.

   \return The number of non-dynamic variables in the set.
*/
unsigned int GetNumNonDynamicVariables(Tvariables *vs);

/** 
   \brief Identifies system variables in a set.

   Identifies system variables in a set.

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a system variable.
*/
boolean IsSystemVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Identifies secondary variables in a set.

   Identifies secondary variables in a set.

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a secondary variable.
*/
boolean IsSecondaryVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Identifies dummy variables in a set.

   Identifies dummy variables in a set.

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a dummy variable.
*/
boolean IsDummyVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Identifies cartesian variables in a set.

   Identifies cartesian variables in a set.

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a cartesian variable.
*/
boolean IsCartesianVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Identifies position variables in a set.

   Identifies position variables in a set (only used in
   dynamical systems). 

   A variable is a position variable if it is not a velocity
   

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a position variable.
*/
boolean IsPositionVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Identifies velocity variables in a set.

   Identifies velocity variables in a set (only used in
   dynamical systems).

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a velocity variable.
*/
boolean IsVelocityVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Identifies non-dynamic variables in a set.

   Identifies non-dynamic variables in a set (only used in
   dynamical systems).

   \param n The number of variable to query
   \param vs The variable set to query.

   \return TRUE if variable number \e n is a non-dynamic variable.
*/
boolean IsNonDynamicVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Gets the type of a particular variable.

   Returns the type of a given variable in the set.

   If the set has less than \e n variables, this function triggers an error.

   \param n The number of variable to query
   \param vs The variable set to query.

   \return The type of variable \e n.
*/
unsigned int GetVariableTypeN(unsigned int n,Tvariables *vs);

/** 
   \brief Adds a variable to the set.

   Adds a variable to the set.

   \param v The variable to add.
   \param vs The variable set to update.
*/
unsigned int AddVariable(Tvariable *v,Tvariables *vs);

/** 
   \brief Gets the information of a variable given the name of this variable.

   Returns a pointer to the variable information given the name of the variable 
   to query.

   \param name The name of the variable to retrive.
   \param vs The variable set to query. 

   \return A pointer to the information relative to the variable with the given name.
           NULL if there is no variable with the given name.
*/
Tvariable *GetVariableWithName(char *name,Tvariables *vs);

/** 
   \brief Gets the information of a variable given its number in the set (i.e., its
          identifier).

   Returns a pointer to the variable information given its position in the set (i.e.,
   its identifier).
   If the set has less than \e n variables, this function triggers an error.

   \param n The number of the variable to retrive.
   \param vs The variable set to query. 

   \return A pointer to the information relative to the variable with the given name.
*/
Tvariable *GetVariable(unsigned int n,Tvariables *vs);

/** 
   \brief Gets the variable identifier (i.e., its position in the set) given a variable name.

   Returns  the variable identifier (i.e., its position in the set) given a variable name. 

   \param name The name of the variable whose identifier we want to retrive.
   \param vs The variable set to query. 

   \return The variable indentifier or NO_UINT if there is not a variable with the given
           name in the set.
*/
unsigned int GetVariableID(char *name,Tvariables *vs);

/** 
   \brief Gets the topology for the variables in the set.

   Gets an array with the topology of the variables in the set.
   The array is allocated inside the call and must be deallocated by the caller.
   
   \param t The topology array to allocate and initialze.
   \param vs The variable set to query.
*/
unsigned int GetVariablesTopology(unsigned int **t,Tvariables *vs);

/** 
   \brief Gets the name for all the variables in the set.

   Gets a pointer to the name for all the variables in the set.

   \param varNames Space for the pointers to the variable names.
   \param vs The variable set to query. 
*/
void GetVariableNames(char **varNames,Tvariables *vs);

/** 
   \brief Gets the name for a particular variable.

   Gets a pointer to the name if a particular variable.

   \param i The identifier of the variable.
   \param vs The variable set to query. 

   \return The pointer to the variable name or NULL if the identifier
           does not correspond to a valid variable.
*/
char *VariableName(unsigned int i,Tvariables *vs);

/** 
   \brief Removes a variable from a set.

   Removes a variable from a set. After removing, the variable set is compacted, i.e., the
   gap of the remove variable is eliminated and this changes the variable indentifiers for
   the variables stored above the removed variable.

   \param n The identifier of the variable to remove.
   \param vs The variable set to update. 
*/
void RemoveVariable(unsigned int n,Tvariables *vs);

/** 
    \brief Creates a box from the ranges of a set of variables.

    Creates a box from the ranges of a set of variables.

    \param b The box to be created.
    \param vs The variable set.
*/
void BoxFromVariables(Tbox *b,Tvariables *vs);

/** 
    \brief Creates a point from the center of the ranges of a set of variables.

    Creates a point from the center of the ranges of a set of variables.

    \param p The point to be created. The space for this point is allocated
             inside this function but must be deallocated externally.
    \param vs The variable set.
*/
void PointFromVariables(double **p,Tvariables *vs);

/** 
   \brief Define the range for the variables from a box.

   Changes the ranges for all variables from the ranges given in a box.
   This is the function complementary to \ref BoxFromVariables.

   \param b The box from where to take the ranges.
   \param vs The set of variables whose ranges to changes.
*/
void VariablesFromBox(Tbox *b,Tvariables *vs);

/** 
   \brief Prints a set of variables to an stream.

   Prints a set of variables to an stream, that can be \e stdout.
   Variables are printed in a format that can be properly parsed
   by the \e .cuik file parser.

   \param f The stream where to print.
   \param vs The variable set to print. 

   \sa readcuiksystem.l, readcuiksystem.y.
*/
void PrintVariables(FILE *f,Tvariables *vs);

/** 
   \brief Destructor.

   Deletes the Tvariables structure and frees the allocated memory.

   \param vs The variable set to delete. 
*/
void DeleteVariables(Tvariables *vs);

#endif
