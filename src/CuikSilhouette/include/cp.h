#ifndef CPH
#define CPH

#include "cuiksystem.h"
#include "parameters.h"
#include "box.h"
#include "list.h"

#include <string.h>
#include <stdlib.h>


/**
   \brief Whether or not to bound the range for the lambdas.

   Set this constant to 1 (TRUE) if you want have bounded ranges for the
   new variables (the \e lambdas) appearing when defining the equation systems
   to find silhouettes and critical points.

   At this point this should be always 1  as the unbounded version is
   not working fine. <br>
   To be removed when we identify the correct, most useful variant.
*/
#define BOUNDED_LAMBDAS 1

/**
   \brief Whether or not to use randomly generated projection planes.

   Set this constant to 1 (TRUE) if you want have use randomly generated
   projection planes when defining the silhouette/critical points equation systems.

   At this point this should be always 1  as the non-random version is
   not working fine (projection planes should be in general position). <br>
   To be removed when we identify the correct, most useful variant.
*/
#define RANDOM_PLANES   0

/** 
    \file cp.h

    \brief Definition of the Tcp type and the associated functions.

    Module to critial points, i.e., recursion points for the silhouette
    algorithm.

    \sa cp.c, Tcp.
*/


/**
  \brief Critical point structure.

  Critical point structure. This is used to start recursions and queries.

  \sa cp.h, cp.c.
*/
typedef struct {
  unsigned int level; /**< Recursion level at which this critical point is generated. 
			   Variables are fixed in the order in which the appear in the 
			   system of equations.
		           A critical point at level \e l, has \e l variables already fixed. */
  Tbox fixedRanges;   /**< Box with the already fixed variables (intervals in the box 
			   up t i<level are fixed)*/
} Tcp; 

/**
   \brief Constructor.

   Defines a new critical point.

   \param l The recursion level at which the critical point is created.
   \param b The box with the already fixed ranges
   \param cp The Tcp structure to create.
*/
void NewCP(unsigned int l,Tbox *b,Tcp *cp);

/**
   \brief Gets the creation level of a critical point.
   
   Gets the creation level of a critical point.
   
   \param cp The critical point to query.

   \return The recursion level at which the critical point was created.
*/
unsigned int GetCPlevel(Tcp *cp);

/**
   \brief Gets the collection of fixed ranges for a critical point.
   
   Gets the collection of fixed ranges for a critical point.

   \return A box with the fixed ranges to create the critical point.
*/
Tbox *GetCPFixedRanges(Tcp *cp);

/**
   \brief Processes a critical point.
   
   A critical point is a recursion point for the silhouette algorithm, i.e., a point
   where the range for one variable is fixed and the silhouette algorithms is
   launched in a sub-space with one degree of freedom less than the original space

   The process of the critical point is the following
     - Given the ranges fixed and not fixed stored in the Tcp structure, we
       generate a TCuikSystem whose solution is a silhouette traced at this
       critical point.
     - We solve the TCuikSystem and add the resulting silhouette to the solution
       file \e f_out. Boxes in this file corresponding to a given silhouette are
       identified with a prefix in the for "SL n" with \e n the number of the silhouette.
     - If the resulting silhouette is just a point, we are in the end case of the
       recursion and nothing else need to be done.
     - If the resulting silhouette is a proper one-dimensional curbe, we 
       generate a TCuikSystem whose solutions are critical points on the silhouette
       previously defined.
     - We solve the TCuikSystem to get the new critical points. 
     - For each one of the solutions, we store them in the output file (\e f_out) and 
       we generate a Tcp structure and we add it to the
       list of critical points pending to be processed (\e cps).
     .

   This is just a brute-force approach to the silhouette algorithm and the result
   is not very efficient. Many refinements are possible to speed up the execution.
   We will introduce them as time is available, but this is not a priority right now.

   \param f_out File where to store the silhouettes and critical points.
   \param n
   \param p The set of parameters to use when solving the cuiksystem generated in this function.
   \param cs The cuiksystem whose solution space we want to characterize using the silhouette algorithm.
   \param cps The list of critical points pending to be processed.
   \param cp The critical point to be processed (typically extracted from \e cps by the caller)
*/
void DealWithCP(FILE *f_out,unsigned int n,Tparameters *p,TCuikSystem *cs,Tlist *cps,Tcp *cp);

/**
   \brief Destructor.
   
   Deletes the information stored in the critical point and frees the allocated memory space.
*/
void DeleteCP(Tcp *cp);

#endif
