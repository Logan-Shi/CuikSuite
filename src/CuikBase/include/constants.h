#ifndef CONSTANTSH
#define CONSTANTSH

#include "boolean.h"

#include <stdio.h>


/** \file constants.h
    \brief Definition of a table of Tconstants.
    
    Definition of a table of constants that are pairs (identifier,value) used when processing
    input files (for instance <em>.cuik</em> files). The definition of constants are useful
    to facilitate the writting of the equations.
    
    \sa Tconstant, Tconstants, constants.c.
*/

/************************************************************************************/
/** \brief Initial room for constants.

    Initial room for constants.It will be enlarged if necessary.

    \sa Tconstants
*/
#define INIT_NUM_CONSTANTS 10
/************************************************************************************/

/** 
 \brief A constant.
 
 Holds the information about a particular constant.

 \sa constants.h constants.c Tconstants
*/
typedef struct {
  char *name; /**< Constant identifier*/
  double vs;  /**< Constant value*/
} Tconstant;

/** 
 \brief A table of constants.
 
 Holds the information about a set of constants.

 This is basically a \ref Tvector "vector"
 and is not implemented using the generic
 Tvector just for legacy reasons (\ref Tconstants was implemented 
 much before that the generic \ref Tvector "vector").

 \sa constants.h constants.c Tconstant Tvector
*/
typedef struct {
  unsigned int max_constants;  /**< Maximum number of constants in the set */
  unsigned int n;  /**< Current number of constants in the set */
  Tconstant *cts; /**< Pointers to the constants stored in the set*/
} Tconstants;

/** 
    \brief Initializes a constant set.

    Creates a new set of constants.

    \param cts Pointer to the set of constants to be initialized
*/
void InitConstants(Tconstants *cts);

/** 
   \brief Copies a set of constants.

   Initializes a set of constant with data from another set.

   \param cts_dst The new set.
   \param cts_src The source set.
*/
void CopyConstants(Tconstants *cts_dst,Tconstants *cts_src);

/** 
   \brief Fuses constant sets.

   Merges the constats in to sets into a new set.
   c1 and cout can be the same.

   \param c1 The firts set of constants to merge.
   \param c2 The second set of constants to merge.
   \param cout The output set with all the constants.
*/
void MergeConstants(Tconstants *c1,Tconstants *c2,Tconstants *cout);

/** 
    \brief Number of constants.

    Returns the number of constants currently in the set.

    \param cts Pointer to the set of constants.

    \return The number of constants held in the set.
*/
unsigned int NConstants(Tconstants *cts);

/** 
    \brief Add a constant.

    Adds a new constnat to the set.  It does not test whether or not there is another 
    constant with the same name.
    This must be tested before using AddConstant calling the function 'GetConstantWithName'

    \param name Name of the constant.
    \param v Value of the new constant.
    \param cts Pointer to the set of constants.

    \return The position at which the constant is added (i.e., the 
            numerical identifier for the constant).
	    
    \sa GetConstantWithName
*/
unsigned int AddConstant(char *name,double v,Tconstants *cts);

/** 
    \brief Retrives a constant from the set.

    Determines the numerical identifier for a constant with a given name.
    It can be used also to check if a constant is included in the set or not.

    \param name Name of the constant to retrive.
    \param cts Pointer to the set of constants.

    \return The numerical identifier for the constant and NO_UINT if there
            is no constant in the set with the given name.
*/
unsigned int GetConstantWithName(char *name,Tconstants *cts);

/** 
    \brief Retrives a the value of a constant.

    Returns the value of a constant, given the numerical identifier of
    this constant.

    \param n Numerical identifier of the constant whose value we want to retrive.
    \param cts Pointer to the set of constants.

    \return The value of the constat or 0 if there is no constant with the given
            numerical identifier.
*/
double GetConstantValue(unsigned int n,Tconstants *cts);

/** 
    \brief Prints a set of constants.

    Prints a set of constants into a stream, that can be <em>stdout</em>.

    \param f The stream where to print the constant set.
    \param cts Pointer to the set of constants to be printed.
*/
void PrintConstants(FILE *f,Tconstants *cts);

/** 
    \brief Destructor.

    Deletes a set of constants.

    \param cts Pointer to the set of constants to be deleted.
*/
void DeleteConstants(Tconstants *cts);

#endif
