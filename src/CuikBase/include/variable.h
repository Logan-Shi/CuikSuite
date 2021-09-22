#ifndef VARIABLEH
#define VARIABLEH

#include "interval.h"

/** 
   \file variable.h

   \brief Definition of the Tvariable type and the associated functions. 

   Definition of the Tvariable type and the associated functions. 

   \sa Tvariable, variable.c.
*/

/************************************************************************************/
/** \brief One of the possible type of variables.

    One of the possible type of variables. System variables
    are those defining the motion of the mechanism at hand.

    \sa TCuikSystem
*/
#define SYSTEM_VAR     1

/************************************************************************************/
/** \brief One of the possible type of variables.

    One of the possible type of variables. Secondary vars are
    system variables that are not necessary to
    completely determine the configuration of the mechanisms.
    For instance, the variables for sph-sph joints (i.e, the
    director vector for the cylinder defined in the joint) 
    can be determined from the pose of the connected links.
    The variables associated with ranges (vectors, cosinus,...)
    are also secondary variables.

    In practice, secondary vars are not used for bisection and
    are not taken into account when computing the size/volume
    for a given box.

    \sa TCuikSystem
*/
#define SECONDARY_VAR     2

/** \brief One of the possible type of variables.

    One of the possible type of variables. Dummy variables
    are variables that appear in the linearization process.

    \sa TCuikSystem, DUMMY_EQ
*/
#define DUMMY_VAR      4

/** \brief One of the possible type of variables.

    One of the possible type of variables. Cartesian variables
    are those given coordinates for points in the mechanism structure.

    \sa TCuikSystem, COORD_EQ
*/
#define CARTESIAN_VAR  8

/** \brief One of the possible type of variables.

    One of the possible type of variables. Velocity variables
    appear when considering dynamics.

    \sa TCuikSystem, VELOCITY_EQ
*/
#define VELOCITY_VAR  16

/** \brief One of the possible type of variables.

    One of the possible type of variables. Non dynanmic
    variables are introduced as extra constraints after
    the definition of world files (variables and equations
    automatically defined).
    These variables are not used in the computation
    of the acceleration (or other related dynamic operations).

    \sa TCuikSystem, NON_DYNBAMIC_EQ
*/
#define NON_DYNAMIC_VAR  32

/** \brief Union of variables of any type.

    Auxiliary definition to jointly refer to variables of any type.
*/
#define ANY_TYPE_VAR (SYSTEM_VAR|SECONDARY_VAR|DUMMY_VAR|CARTESIAN_VAR|VELOCITY_VAR|NON_DYNAMIC_VAR)

/** \brief One of the possible type of variables.

    Used for equations with non-assigned role yet.
*/
#define NOTYPE_VAR    64
/************************************************************************************/

/** 
   \brief Data associated with each variable in the problem. 

   Data associated with each variable in the problem. 

   \sa variable.h, variable.c
*/
typedef struct
{
  unsigned int type;      /**< Type of variable: SYSTEM_VAR, 
			       SECONDARY_VAR, CARTESIAN_VAR, 
			       DUMMY_VAR, VELOCITY_VAR,
			       NON_DYNAMIC_VAR or NOTYPE_VAR. */
  unsigned int topology; /**< Variable topology (Real/Sphere) */
  char *name;            /**< Variable name. */
  Tinterval is;          /**< Valid range for this variable. */
} Tvariable;

/** 
   \brief Constructor.

   Creates a new variable.

   \param type Type for the new variable.
   \param name Name for the new variable.
   \param v The variable to create.
*/
void NewVariable(unsigned int type,char *name,Tvariable *v);

/** 
   \brief Copy constructor.
   
   Creates a new variable from another one.
   
   \param v_dst The variable to create.
   \param v_src The variable from where to copy.
*/
void CopyVariable(Tvariable *v_dst,Tvariable *v_src);

/** 
   \brief Sets the topology of the variable.

   Changes the topology of the variable.
   The default value for the topology is TOPOLOGY_R.

   \param t The new topology.
   \param v The variable to modify.
*/
void SetVariableTopology(unsigned int t,Tvariable *v);

/** 
   \brief Gets the topology of the variable.
   
   Returns the topology of the variable. Note that even if a variable
   has TOPOLOGY_S, it is set to TOPOLOGY_R if its associated range
   is smaller than 2*pi. Only variables with ranges larger than 2*pi
   have to routes to connect any two given points.

   \param v The variable to query.

   \return The variable's topology.
*/
unsigned int GetVariableTopology(Tvariable *v);

/** 
   \brief Gets the variable type.

   Gets the variable type.

   \param v The variable to query.

   \return The variable type.
 */
unsigned int GetVariableType(Tvariable *v);

/** 
   \brief Gets the variable name.

   Gets the variable name.

   \param v The variable to query.

   \return The a pointer to the variable name.
 */
char *GetVariableName(Tvariable *v);

/** 
   \brief Sets the new range for the variable.

   Sets the new range for the variable.

   \param i The new range for the variable.
   \param v The variable to query.

*/
void SetVariableInterval(Tinterval *i,Tvariable *v);

/** 
   \brief Gets the  range of valid values for the variable.

   Gets the  range of valid values for the variable.

   \param v The variable to query.
   
   \return A pointer to the range of valid values for the variable.
*/
Tinterval *GetVariableInterval(Tvariable *v);

/** 
   \brief Prints a variable.

   Prints a variable (name plus valid range) to a stream that can be \e stdout.

   \param f The file where to print.
   \param v The variable to print.
*/
void PrintVariable(FILE *f,Tvariable *v);

/** 
   \brief Destructor.

   Deletes the Tvariable structure and frees the allocated memory.

   \param v The variable to delete.
*/
void DeleteVariable(Tvariable *v);

#endif
