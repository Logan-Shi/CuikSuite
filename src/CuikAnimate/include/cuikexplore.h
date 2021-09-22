#ifndef CUIKEXPLOREH
#define CUIKEXPLOREH

#include "boolean.h"
#include "parameters.h"
#include "chart.h"

/** \file cuikexplore.h

    \brief Definition of the \ref cuikexplore.c "cuikexplore" control structure.

    Definition of the control structure shared betweeen \ref cuikexplore.c "cuikexplore"
    and the interface callbacks.
*/

/**
   \brief Definition of the \ref cuikexplore.c "cuikexplore" control structure.

   \ref cuikexplore.c "cuikexplore" control structure. This is shared
   between the \ref cuikexplore.c "cuikexplore"  main application and the
   interface callbacks.
*/
typedef struct {
  boolean dynamics;      /**< TRUE for problems with dynamics. */
  boolean end;           /**< TRUE if cuikexplore is to be closed. */
  boolean changed;       /**< TRUE if any of the degrees of freedom changed. */
  boolean oneStep;       /**< TRUE if only one step has to be executed. */
  boolean reset;         /**< TRUE if we have to move to the initial configuration. */
  double step;           /**< Size of each movement/step. */
  unsigned int k;        /**< Dimension of the conf. space manifold. */
  unsigned int *ndx;     /**< Index of the k variables used as parameters */
  unsigned int *e2d;     /**< Map from menu entry to dof. Necessary becaus some
			      dofs (those with null range) are not shown in the menu. */
  unsigned int *d2e;     /**< Map from dof meny entries. */
  unsigned int d;        /**< Number of degrees of freedom in the problem. */
  unsigned int m;        /**< Number of variables in the problem. */
  unsigned int rep;      /**< Representatino (JOINTS, LINKS) of the input. */
  double *point;         /**< Current point on the manifold. */
  double *simpPoint;     /**< Current point in simplified form. */
  double *pointDOF;      /**< The same as 'point' but expressed in DOF. */
  double *vectDOF;       /**< Displacement in ambient space along the variables
			      used as parameters. */
  char *fw;              /**< File from where we read the world information. */
  Tparameters *p;        /**< The set of parameters to use. */
  TAtlasBase *w;         /**< The world structure to move. */
} TCuikexploreControl;

#endif
