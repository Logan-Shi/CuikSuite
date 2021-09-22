#ifndef BTREEH
#define BTREEH

#include "boolean.h"
#include "box.h"
#include "chart.h"

#if (_KDTREE==1)
  #include <cuik-kdtree/cuik-kdtree.h>
#endif
#if (_KDTREE==2)
  #include <DNN/ANN_C.h>
#endif

/** 
   \file btree.h
   \brief Definition binary tree of charts.

   Definition a binary tree to speed up the search for neighouring charts in the atlas.

   \sa Tbtree,btree.c,Tatlas,atlas.c
*/

/** 
   \brief Initial number of points in the tree.

   Initial number of points in the tree. Enlarged as needed.
*/
#define INIT_NUM_POINTS_IN_BTREE 1000

/** 
   \brief Weighted distances.

   If set, the distances in the tree use weights so that all dimensions have the same relevance.
   In general this should be 0. Do not confuse this with the nearest-neighbours used in planning.
*/
#define W_BTREE 0

/** 
   \brief Binary tree of charts.

   The tree is defined recursively using nodes as basic blocks. Those nodes can be either
   a leave or an internal.

   The recursive definition allows for an easy recursive implementation.

   Note that tree includes only the central points and the identifiers of the charts and
   not the full charts themselves.
*/
typedef struct {
  unsigned int m;       /**< Dimension of the space where the tree is defined. */
  double r;             /**< Radius used for the search for neighbours. */
  unsigned int *tp;     /**< The topology for each variable */

  #if (_KDTREE==1)
    TKDtree *kdtree;    /**< The kd-tree (cuik-kdtree). */ 
  #endif
  #if (_KDTREE==2)
    TKDTree *kdtree;    /**< The kd-tree (DNN-kdtree). */ 
    unsigned int mp;    /**< Maximun number of points in the tree. Extended as needed. */
    unsigned int np;    /**< Curent number of points in the tree. */
    unsigned int *n2id; /**< The kd-tree automatically assigns an identifier to
		             the added points that is the cardinal of the point.
		             The identifiers we use might be different. */
  #endif
} TBTree;

/** 
   \brief Initializes a binary tree of charts

   Creates a binary tree of charts from the central point of one chart.

   \param id Identifier of the chart used to initialize the tree.
   \param mp The chart used to initialize the tree.
   \param ambient The ambient space.
   \param topology Topology for each variable/dimension. 1 for Real and 2
                   for circle. Set to NULL if all variables are real.
   \param t The tree to create.
*/
void InitBTree(unsigned int id,Tchart *mp,Tbox *ambient,unsigned int *topology,TBTree *t);

/** 
   \brief Adds a chart to the tree.

   Adds a new chart to the tree of charts.

   \param id Identifier of the chart to add to the tree.
   \param mp The chart to add.
   \param t The tree where to add the chart.
*/
void AddChart2Btree(unsigned int id,Tchart *mp,TBTree *t);

/** 
   \brief Point in a tree.

   Determines if we already have a point in the tree.

   \param eps Precision to use in the comparision between points.
              In debug mode, the cuik-kdtree library uses a hard-coded 
              threshold of 1e-6. So this is a good value for this threshold.
   \param p The query point.
   \param t The tree.

   \return The index of the nearest chart.
*/
boolean PointInBTree(double eps,double *p,TBTree *t);

/** 
   \brief Search for neighbouring charts.

   Uses the tree of charts to efficiently detect neighbouring charts to a given chart.
   
   We assume that the charts all have the same domain radius as the original chart (the
   one used to initialize the tree).

   Note that the output of this search is not the set of neighbours but the set of
   potential neighbours (identifiers of points in tree leaves close to the test point).
   This is not an issue since the intersection test that typically follows the search
   for neighbours takes care of actually detecting the true neighbours.

   \param mp The chart for which we want to get the neighbours.
   \param nn The number of neighbours returned. This is a return parameter.
   \param n The identifier of the neighbouring charts found. The space for this array
            is allocated internally but must be released by the caller.
   \param t The tree to use for the query.
*/
void SearchInBtree(Tchart *mp,unsigned int *nn,unsigned int **n,TBTree *t);

/** 
   \brief Chart tree destructor.

   Deletes a tree of charts and releases the allocated memory.
*/
void DeleteBTree(TBTree *t);

#endif
