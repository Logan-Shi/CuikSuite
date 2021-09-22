#ifndef CUIKMOVEH
#define CUIKMOVEH

#include "boolean.h"
#include "parameters.h"
#include "world.h"

/** \file cuikmove.h

    \brief Definition of the \ref cuikmove.c "cuikmove" control structure.

    Definition of the control structure shared betweeen \ref cuikmove.c "cuikmove"
    and the interface callbacks.
*/

/** 
   \brief Definition of the \ref cuikmove.c "cuikmove" control structure.

   \ref cuikmove.c "cuikmove" control structure. This is shared
   between the \ref cuikmove.c "cuikmove"  main application and the
   interface callbacks.
*/
typedef struct {
  boolean end;           /**< TRUE if cuikmove is to be closed. */
  boolean changed;       /**< TRUE if any of the degrees of freedom changed. */
  unsigned int accuracy; /**< Step size for each degree of freedom. In decimal digits. */
  unsigned int ndof;     /**< Number of degrees of freedom to move. */
  double *min;           /**< Mininum value for each degree of freedom. */
  double *max;           /**< Maximum value for each degree of freedom. */
  double *dof;           /**< Current value for the degrees of freedom. */
  boolean *shown;        /**< TRUE for the DOF to show. DOF with constant
			      range are not shown. */
  unsigned int nShown;   /**< Number of DOF actually shown. */
  Tparameters *p;        /**< The set of parameters to use. */
  Tworld *w;             /**< The world structure to move. */
  char *fw;              /**< File from where we read the world information. */
  boolean dynamics;      /**< TRUE if the problem includes dynamics. If true
			      zero velocity is added to the saved configurations. */
} TCuikMoveControl;

#endif
