#ifndef RRTH
#define RRTH

#include "parameters.h"
#include "vector.h"
#include "heap.h"
#include "wcs.h"

#if (_KDTREE==1)
  #include <cuik-kdtree/cuik-kdtree.h>
#endif
#if (_KDTREE==2)
  #include <DNN/ANN_C.h>
#endif

/** 
   \file rrt.h
   \brief Definition of a rrt on a manifold.

   Definition of a rrt on a point on a manifold. This is implemented for
   comparison with atlas and, eventually to complement atlas.

   \sa Trrt,rrt.c.
*/

/** 
   \brief Vebosity of the RRT operations

   Vebosity of the RRT operations. If set to 0 only  minimalistic
   information is printed.
*/
#define RRT_VERBOSE (_DEBUG>3?_DEBUG-3:0)

/** 
    \brief Weighted nearest neighbours.
    
    If set, the distance used in nearest neightbour search is weighted
    so that the differences in each dimension are homogeneous.

    The weighs are computed as the inverse of the domain size for
    each variable.
*/
#define WEIGTHED_NN 1

/** 
   \brief Block the expansion of blocked nodes.

   If set to 1 blocked RRT nodes (nodes close to obstacles or to the borders
   of the domain) are used to expand new RRT branches with less probability.
*/
#define PENALIZE_BLOCKED_NODES 0

/** 
    \brief Penalize parent nodes.

    If a node is added to the RRT after detecting a collision or a limit in
    the domain, the parent node may also be in the region of inevitable collision.
    If this flag is set, parent nodes of blocked nodes are also blocked.

    This flag is only used if \ref PENALIZE_BLOCKED_NODES is also set)

    Recall that penalized nodes are also expanded, but with less probability.
*/
#define PENALIZE_PARENT_NODES 1

/** 
    \brief Weighted distance in goal reaching.
    
    If not null, the distance used to determine if the goal is reached is
    weighted. Otherwise, we use the standard Euclidean distance.

    If set to 2, the weighted distance is also used to evaluated
    the progress of the RRT extension to the random sample (or, eventually,
    the goal). When the branch approaches the random sample (goal),
    the extension is repeated
    
    \sa WEIGTHED_NN
*/
#define WEIGTHED_REACHED_GOAL 2

/** 
   \brief Set this to one to gather statistics of RRT construction.

   Set this to one to gather statistics of RRT construction process.
   These statistics are printed at the end of the RRT construction.
 */
#define GET_RRT_STATISTICS 1

/** 
   \brief Whether to use an heuristic in  AtlarRRT*

   If true we use an heuristic stratetgy in the AtlasRRT*.
   There are four heuristic that can be applied separately
     - 1: Reject to expand nodes that are already far from the root.
     - 2: gamma is set to 0 until the goal is reached.
     .
   The different heuristics can be combined via
   HEURISTIC_ATLASRRT_STAR (1+2)
*/
#define HEURISTIC_RRT_STAR (0) //(1+2)

/** 
  \brief On the fly update of the cost in the RRTstar.

  On the fly update of the cost in the RRTstar. If set to one, we cost
  for the tree nodes for RRT* are updated for the nodes close to the
  just added node to the tree (in a gamma-ball). The cost is updated
  by accumulating cost to parent for all the neighbouring nodes.

  This option also affects AtlasRRTStar.
*/
#define RRTSTAR_UPDATE_COSTS 0

/** 
   \brief TRUE (or 1) if cost(a,b)=cost(b,a)

   Set to true if the cost are symmetrical, i.e. if cost(a,b)=cost(b,a).
   This can save a significant amount of time in the RRT*.
*/
#define RRTSTAR_SYMMETRIC_COST 1

/** 
    \brief Initial temperature used in Transition based rrt searches
 */
#define TEMPERATURE_INIT 0.001

/** 
   \brief Select between exploration and goal driven RRT.

   When 0 we use the normal RRT with bias to goal and that stops as
   soon as the goal is found.

   If 1 the RRT is build without considering the goal and
   the construction stops when the tree includes the given number of samples
   (or nodes).

   Normally this should be 0. We only use it to test the coverage properties
   of the RRT.

   This is also used for AtlasRRT.

   \todo Set this as a parameter and not as a compilation flag.
*/
#define EXPLORATION_RRT 0

/** 
   \brief Selects the way RRTs are plotted.

   RRTs are plotted with red lines connecting nodes and blue crosses defining each
   node. If this flag is set to 0, the crosses are not plotted (only
   the lines are shown).
*/
#define RRT_PLOT_NODES 1

/** 
    \brief Set to 1 to use the topology in the search for nearest-neighbours.

    This flag can be used to activate of de-activate the topology in the search
    for nearest-neighbours.

    This is basically used for testing purposes.
*/
#define RRT_NN_TOPOLOGY 1

/** 
   \brief Initial room for samples of an rrt.

   Initial room for samples in th rrt. It will be expanded as needed.
   Should be at least 1.
*/
#define INIT_NUM_SAMPLES_RRT  100

/** 
    \brief One of the modes for the RRT.

    In this mode only one tree (start to goal) is defined.
*/
#define ONE_TREE 0

/** 
    \brief One of the modes for the RRT.

    In this mode only two trees are defined, one from start to goal
    and one from goal to start. Once assigned to a tree samples
    never move to the other tree.
*/
#define TWO_TREES 1

/** 
    \brief One of the modes for the RRT.

    In this mode only two trees are defined, one from start to goal
    and one from goal to start. In  this mode samples can change
    between trees. This is only used for bidirectional RRT*.

    In this mode only one big pool of samples (i.e., one KD-tree) is maintained
    for NN searching. This is so since the kd-tree implementation
    does not allow samples to be removed from the kd-tree.
*/
#define TWO_TREES_WITH_SWAP 2

/** 
   \brief Used for samples not assigned to any tree.

   Used for samples not assigned to any tree.
*/
#define NOTREE 0

/** 
   \brief One of the possible trees.

   Search direction of one of the possible trees. This one is used always.
*/
#define START2GOAL 1

/** 
   \brief One of the possible trees.

   Search direction of one of the possible trees. This one is only used
   when using the bidirectional search strategy.
*/
#define GOAL2START 2

/** 
   \brief Used for samples in both trees.

   Used for samples in both trees.
*/
#define BOTHTREES (START2GOAL|GOAL2START)

/** 
   \brief Statistics on the RRT construction

   Statistics collected during the RRT constructin to characterize
   different algorithms or parameter sets.

   Statistics should only be used in debug/analysis mode. Otherwise it is
   better to skip collecting them (for efficiency reasons).
   See \ref GET_RRT_STATISTICS

   Note that this structure is not thread-save. Thus, we must only collect
   statistics when executing in single core mode.

   \todo Switch to thread-save statistics before implementing a parallel
         version of the RRT.
*/
typedef struct {
  unsigned int n;                      /**< Number of statistics accumulated in
					    the structure. */

  unsigned int nBranch;                /**< Number of branch extensions. */
  unsigned int nNoEmptyBranch;         /**< Number of non-empty branches. */

  unsigned int nTreeConnection;        /**< Number of attemps to connect the two trees. */
  unsigned int nNoEmptyTreeConnection; /**< Number of non-empty attemps of tree connection. */

  unsigned int nStep;                  /**< Number of steps in branch extension. */
  double dQrand;                       /**< Accumulated distances from q_rand-tree. */

  /* Reasons to stop a branch extension */
  unsigned int nQrandReached;          /**< Times we actually reached q_rand. */
  unsigned int nConvergenceError;      /**< Error converging to the manifold. */
  unsigned int nHighCost;              /**< A high cost configuration is reached (TRRT only). */
  unsigned int nOutOfDomain;           /**< The brach leaves the domain. */
  unsigned int nDistanceIncreases;     /**< The distance to q_rand increases. */
  unsigned int nCollision;             /**< Stopped due to collisions. */
  unsigned int nTooFar;                /**< Stopped due ot a large step. */
  unsigned int nStalled;               /**< Stopped when the branch extension is stalled. */

  unsigned int nSample;                /**< Total of samples in the RRT. */

  /* Information about sampling */
  unsigned int nRandom;                /**< Number of times we generated a random
				            sample */
  unsigned int nRejections;            /**< Number of rejected random samples */

  /* Information aobut collison checking */
  unsigned int nCollisionChecks;       /**< Number of collision checks */
}  TRRTStatistics;

/*******************************************************************************/

/** 
   \brief Step in a solution path.

   Step in solution path. Used in bi-RRTs.

   Note that steps in a solution path are always valid transitions
   between nodes (collion free) and that the cost corresponds
   to that of the direct connection between the nodes (it can
   not be improved).
*/

typedef struct {
  unsigned int id; /**< Next node in the path. */
  double cost;     /**< Cost to the next node. */
} TRRTStep;

/** 
    \brief Copy constructor for RRTSteps.

    Copy constructor for RRTSteps.

    \param a Pointer to the RRTStep where to copy.
    \param b Pointer to the RRTStep from where to take the data.
*/
void CopyRRTStep(void *a,void *b);

/*******************************************************************************/

/** 
   \brief Information for each sample in a RRT.

   Emcompasses the information associated with each sample in a RRT that
   is not already included in the underlying RRT.

   If the ambient space has circular topology in any dimension, the same point
   can be represented in infinite many different ways. In the RRT we only
   store points in canonical form (i.e., in the -pi, pi range).

   When searching for the shortest path between samples (i.e., the straight line
   between them) we have to take into account the topology since each pair of
   samples can be connected in many different ways. If we do not advance along
   the shortest path, the RRT would be strange.

   The search for nearest-neighbours should be also done taking into account
   the topology.
 */
typedef struct {
  double *samples;      /**< The sample. */
  unsigned int parent;  /**< Parent sample for each sample. This defines the tree structure.
			     When in graph mode this is one of the neighbours in 'n'. */
  double costp;         /**< Distance to the parent (when cost is related to path).
			     When in graph mode this is of the costs in field 'cn'. */
  double cost;          /**< Cost of a given node. This can have two different meanings:
			     The cost of the node as evaluated with a user-given function
			     (in T-RRT) or the length of the path form the root of the
			     tree (in RRT*). In this second case,
			     when using bi-directional trees the root can be either the
			     goal or the start sample. When in graph mode
			     this is actually the 'rhs', the min cost to this node via any
			     of its neighbours. This is always a better approximation to the
			     cost than that stored in 'g'. */

  double blocked;       /**< Used to determine the likelihood of a node to lead to a collision
			     or to domain limit when expended. */
  
  double ddr;           /**< Dynamic domain radius. 0 if not used. */

  double g;             /**< Cost of the node. Then g>cost we have to propagate the
			     cost update. Used in RRT* in graph mode. */

  unsigned int m;       /**< Maximum number of neigbours. */
  unsigned int nn;      /**< Number of neighbours. */
  unsigned int *n;      /**< Vector of neighbours.*/
  double *cn;           /**< Cost to reach each neighbour.*/

  unsigned int tree;    /**< Tree including the sample */

  double *u;            /**< Action executed to reach this node from the parent node.
			     Only used in problems with dynamics. */

  double time;          /**< Time action 'u' has to be executed to reach the current
 			     state from the parent. Only used in problems wiht dynamics. */

  unsigned int ns;      /**< Number of steps taking from the parent to the current sample. */
  double **path;        /**< Configuration/state for each step taking from the parent to the
			     current sample. */
  double **actions;     /**< Action executed at each step taking from the parent to the
			     current sample. Right now all actions are the same and equal
			     to \e u, but we may . */
  double *times;        /**<  The time for each individual step. Field \e time is the sum
			      of this vector, if used. */
  
  void *userInfo;       /**< General information provided by caller. */
} TRRTSampleInfo;

/** 
   \brief A RRT on a manifold.

   Defines a RRT on a manifold. It implements the basic operations to define
   a RRT on a manifold sampling from ambient space.

   Note that RRTs are internally defined in the simplified (but not yet dummified) system
   of equations (comming from a cuiksystem or from a world structure).
*/
typedef struct {
  TAtlasBase *w;                   /**< The world on which the RRT is defined */

  unsigned int m;                  /**< Number of variables. Dimension of the ambient space.
				        This is the space where q_rand is sampled. */
  unsigned int k;                  /**< Dimension of the manifold */
  unsigned int n;                  /**< Number of equations defining the manifold. */

  double delta;                    /**< Advance step. This is used in dynamic domain */

  double temperature;              /**<  Current temperature for Transition based exploration */
  unsigned int nFail;              /**< Consecutive number of transition failures
				        in Transition based exploration */

  unsigned int nCores;             /**< Available computing cores.  */
  boolean parallel;                /**< TRUE if it is worth to use parallelism. Right now ony the RRT*
				        construction exploits parallelism. */

  unsigned int *tp;                /**< Topology for each variable. */

  unsigned int ns;                 /**< Number of samples in the RRT so far. */
  unsigned int ms;                 /**< Maximum number of samples in the RRT. Expanded as needed. */

  Tbox *ambient;                   /**< Ambient space. Place where samples are generated. */

  TRRTSampleInfo **si;             /**< Information associated with each sample */

  unsigned int mode;               /**< One of the three modes in which the RRT can be defined
				        \ref ONE_TREE, \ref TWO_TREES, \ref TWO_TREES_WITH_SWAP. */
  boolean graph;                   /**< If TRUE the RRT is in graph mode and it is not a tree but a graph
				        since we store the neighbours for each node and not just the
				        parent. In graph mode the costs are assumed to be symmetric
				        (see \ref RRTSTAR_SYMMETRIC_COST) */
  double dd;                       /**< Initial dynamic domain radius. 0 if dynamic domain is not used. */

  unsigned int da;                 /**< Dimension of the action space. Only used in problems with dynamics. */

  double *weight;                  /**< Weight in each dimension of the (Euclidean) distance between samples. */
  #if (_KDTREE==1)
    TKDtree *treeS2G;              /**< Kd-tree with samples. Tree from the start node. */
    TKDtree *treeG2S;              /**< Kd-tree with samples. Tree from the goal node.
				        Only used in bidirectional RRTs. */
  #endif
  #if (_KDTREE==2)
    TKDTree *treeS2G;              /**< Kd-tree with samples. Tree from the start node. */

    TKDTree *treeG2S;              /**< Kd-tree with samples. Tree from the goal node.
				        Only used in bidirectional RRTs. */
    unsigned int nodesT1;          /**< Number of nodes in the first tree.
				        Only used in bidirectional RRTs.  */
    unsigned int nodesT2;          /**< Number of nodes in the second tree.
				        Only used in bidirectional RRTs.  */
    unsigned int maxNodesT1;       /**< Maximum number of nodes in the first tree.
				        Only used in bidirectional RRTs.  */
    unsigned int maxNodesT2;       /**< Maximum number of nodes in the second tree.
				        Only used in bidirectional RRTs. */
    unsigned int *t1ToId;          /**< Translates from identifiers of tree 1 to global identifiers.
				        Only used in bidirectional RRTs.  */
    unsigned int *t2ToId;          /**< Translates from identifiers of tree 2 to global identifiers.
				        Only used in bidirectional RRTs.  */

  #endif

} Trrt;

/*******************************************************************************/

/** 
    \brief Init the RRT statistics.

    Init the  RRT statistics.

    \param rst The RRT statistics to initialize.
*/
void InitRRTStatistics(TRRTStatistics *rst);

/** 
    \brief Accumulates two sets of  RRT statistics.

    Accumulates two sets of  RRT statistics.
    This is used to accumulate statistics when executing a long
    sequence of experiments.

    \param rst1 The RRT statistics to accumulate.
    \param rst2 The RRT statistics where to accumulate.
*/
void AccumulateRRTStatistics(TRRTStatistics *rst1,TRRTStatistics *rst2);

/** 
    \brief Prints the summary of RRT statistics.

    Prints a report about the collected RRT statistics.

    \param rrt The RRT (might be NULL).
    \param rst The RRT statistics to print.
*/
void PrintRRTStatistics(Trrt *rrt,TRRTStatistics *rst);

/** 
    \brief Destructor.

    Deletes the RRT statistics object.

    \param rst The RRT statistics to delete.
*/
void DeleteRRTStatistics(TRRTStatistics *rst);

/*******************************************************************************/

/** 
   \brief Defines a RRT from a given point.

   Defines a RRT with a single sample, the root.

   \param pr The set of parameters.
   \param parallel TRUE if the RRT construction will involve any kind of
                   parallelism via OpenMP. Up to now some algorithms (RRT*)
		   include some degree of parallelism and others (eg. RRT) not.
   \param simp TRUE if the point is given in the simplified form and \ref FALSE
               if it is in the global system (including redundant values).
	       In any case, the sample includes only system variables.
   \param ps A point on the manifold from where to start the RRT. The RRT root.
   \param mode Mode for the RRT: \ref ONE_TREE, \ref TWO_TREES, \ref TWO_TREES_WITH_SWAP.
   \param graph If TRUE the RRT is actually a graphs since we store the neighbours for
                each node, not just the parent. This is used to propagate improvements
		for RRT*.
   \param pg The goal point for the RRT. Only used when mode is not \ref ONE_TREE.
   \param m The dimension of the sample space. Size of the samples. Only used if
            simp is TRUE.
   \param da Dimension of the action space. Only used in problems with dynamics.
   \param w The base type with the equations (and possibly obstacles).
   \param rrt The RRT to create.
*/
void InitRRT(Tparameters *pr,boolean parallel,boolean simp,double *ps,
	     unsigned int mode,boolean graph,double *pg,
	     unsigned int m,unsigned int da,TAtlasBase *w,Trrt *rrt);

/** 
    \brief Temperature of the T-RRT.

    Returns the current value for the temperature of the T-RRT.

    \param rrt The T-RRT to query.

    \return The temperature.
*/
double GetTRRTTemperature(Trrt *rrt);

/** 
    \brief Identifies RRT with a graph structure.

    Identifies RRTs where we store the whole set of neighnbours for each node.
    This is  used in some variants of RRT* to accelerate the propagation
    of the path improvements.

    \param rrt The T-RRT to query.

    \return TRUE if the RRT has graph structure.
*/
boolean IsRRTGraph(Trrt *rrt);

/** 
    \brief Generates a random sample to expand the RRT.

    Generates a random sample to expand the RRT. The sample
    can be generated with different policies according to the
    mode (from the ambient space, or near the existing nodes)
    and the goal (if defined the goal is used as random sample
    1 out of 100 times).

    \param samplingMode Policy to generate the random sample. This can
                         be AMBIENT_SAMPLING (to generate it from the ambient space)
		         or KDTREE_SAMPLING (to generate it using the kd-tree). In this
		         second option the random sample is 'near' the
		         existing nodes in the tree. This option can only be
		         used if the cuik-kdtree library is available.
    \param tree The tree to use in the sampling. Only used if mode is
                KDTREE_SAMPLING.
    \param goal Goal node. NULL if we do not have goal (i.e. we are
                defining an exploration RRT) or if we can not use
		the goal as a random sample.
    \param q_rand Space to store the random sample.
    \param rst Statistics on the RRT construction process (only used if
               \ref GET_RRT_STATISTICS is set).
    \param rrt RRT to use.

    \return TRUE if the goal is used as random sample.
*/
boolean RRTSample(unsigned int samplingMode,unsigned int tree,
		  double *goal,double *q_rand,
		  TRRTStatistics *rst,Trrt *rrt);


/** 
    \brief Validates a sample generate with \ref RRTSample

    Checks if a given sample is valid to expand the RRT.

    \param pr The set of parameters.
    \param q_rand The random sample.
    \param tree The tree where to look for nearest neighbours.
    \param expand2goal TRUE if the random sample is the goal.
    \param goal The goal.
    \param l The shortest path from start to goal so far. Only used for RRT*-like
             algorithms and it only has effect if it is not INF.
    \param h A lower estimate of the distance between the random sample and the goal.
             This is only relevant in RRT*-like algorhtms.
    \param i_near The nearest neighbour in the RRT.
    \param rst Statistics on the RRT construction process (only used if
               \ref GET_RRT_STATISTICS is set).
    \param rrt RRT to use.

    \return TRUE if the random sample is valid.
*/
boolean RRTValidateSample(Tparameters *pr,double *q_rand,unsigned int tree,boolean expand2goal,
			  double *goal,double l,double *h,unsigned int *i_near,
			  TRRTStatistics *rst,Trrt *rrt);

/** 
   \brief Detects points alrady included in the RRT.

   Points should not be duplicated in the RRT. This function detects such duplicated
   points. This is speciallly relevant in problems with dynamics where the actions
   are fixed. Then, a given node is always expanded in the same way and the
   next state may be already in the tree.

   \param epsilon Numerical accuracy.
   \param tree Tree where to look for the sample.
   \param q The point
   \param rrt The RRT.
*/
boolean PointInRRT(double epsilon,unsigned int tree,double *q,Trrt *rrt);

/** 
   \brief Locates the nearest sample in the tree of samples.

   Finds the sample in the tree that is closer (in the Euclidean distance)
   to the given point.

   \param tree Which tree (\ref START2GOAL or \ref GOAL2START) to use in the search.
	       Only considered in bidirectional RRTs. Otherwise all points are added
	       in the START2GOAL tree (the only one defined).
   \param q_rand The point (in the simplified system).
   \param rrt The RRT to query.

   \return The index of the tree node closer to \e q_rand.
*/
unsigned int GetRRTNN(unsigned int tree,double *q_rand,Trrt *rrt);

/** 
   \brief Locates the all the sample closer than a given distance.

   Finds the set of samples inside a ball of radious 'r' centered at a given point.

   \param tree Which tree (\ref START2GOAL or \ref GOAL2START) to use in the search.
	       Only considered in bidirectional RRTs. Otherwise all points are added
	       in the START2GOAL tree (the only one defined).
   \param q_rand The point (in the simplified system).
   \param r The radius of the search ball.
   \param nn (output) The number of returned points.
   \param n (output) The array of indices for the in-ball nodes.
   \param rrt The RRT to query.
*/
void GetRRTNNInBall(unsigned int tree,double *q_rand,double r,
		    unsigned int *nn,unsigned int **n,Trrt *rrt);

/** 
   \brief Locates the nearest sample in the tree to a branch.

   Finds the sample in the given tree that is close to a given branch
   in another tree. The branch is defined by samples n1 and n2 where
   n1 is antecesor of n2.

   \param tree Which tree (\ref START2GOAL or \ref GOAL2START) where to
               search for the nearest sample. This must be different
	       from the tree including the query samples (n1, n2).
   \param n1 First node (parent) defining the branch in the other tree.
   \param n2 Second node (child) defining the branch in the other tree.
   \param n The index of the element in the branch (i.e., node in between
            n1 and n2 both included) close to the other 'tree'.
   \param nn The index of the node in 'tree' closer to the branch (i.e.,
             to the node whose index is returned in 'n').
   \param rrt The RRT to query.
*/
void GetRRTNNInBranch(unsigned int tree,
		      unsigned int n1,unsigned int n2,
		      unsigned int *n,unsigned int *nn,
		      Trrt *rrt);

/** 
   \brief Adds a point to a RRT.

   A debug utility to add points to RRTs without checking for collisions nor
   moving slowly toward to q_rand. It just adds the point and links it to
   the parent (i_near)

   \param pr The set of parameters.
   \param i_near Index of the sample in the RRT from where to start the extension.
                 The parent for the sample to add.
   \param tree The tree that should include the new sample. In must be the same
               tree as that of the parent sample, if defined.
   \param sample The sample to add.
   \param goal Global goal for the RRT (also given in simplified form).
               If sample is close to goal the function returns TRUE.
   \param lastSample Identifier given to the sample added to the RRT.
   \param info User information associated to the node.
   \param costp The distance to the parent.
   \param cost The cost of the node to be added. This can mean different
               things: The cost of the node evaluated with a user-given
	       function (in T-RRT) or the distance from the root of the
	       tree (in RRT*).
   \param blocked Marks (with TRUE) nodes close to obstacles or to domain
	          limits. This information can be used to bias the expansion
		  of the tree. Currently this is not used in RRT but only
		  in AtlasRRT in dynamic problems (to mark nodes in the
		  region of inevitable collision, for instance).
   \param u Action to reach the node from the parent. Only used in
            systems with dynamics.
   \param time Time to reach the node from the parent. Only used in
               systems with dynamics.
   \param ns Number of small steps from the parent to the state to add.
             May be NULL if not used.
   \param path The states in between the new node and its parent.
             May be NULL if not used.
	     CAUTION: for efficiently, we directly point to the path
	        given by the caller. Thus the caller should not deallocte
	        the information (it will be de-allocated when deleting the RRT).
                The same applies to \e actions and \e times
   \param actions Action executed in between the parent node and the node to add.
                  In general this is the same action as \e u, but it may be different.
                  The actions are only used in problems with dynamics.
                  May be NULL if not used.
   \param times Time of each step in between the parent and the new node.
                The sum of such times must be \e time (but the time to actually reach the
		node to add).
                The times are only used in problems with dynamics.
                May be NULL if not used.
   \param rst Statistics on the RRT construction process (only used if
              \ref GET_RRT_STATISTICS is set).
   \param rrt the RRT to extend.

   \return TRUE if the goal has been reached (sufficiently close) or if the
           maximum number of samples in the RRT have been reached.
           If the goal is NULL then we return \ref FALSE.
*/
boolean AddNodeToRRT(Tparameters *pr,unsigned int tree,
		     unsigned int i_near,double *sample,double *goal,
		     unsigned int *lastSample,void *info,double costp,double cost,
		     boolean blocked,
		     double *u,double time,
		     unsigned int ns,double **path,double **actions,double *times,
		     TRRTStatistics *rst,Trrt *rrt);


/** 
    \brief Adds a neighbouring relation to an RRT.

    Stores an edge between nodes 'i' and 'j' with cost 'c'

    This only has effect if the RRT is in graph mode.

    \param i The first node of the edge.
    \param j The second node of the edge.
    \param c The cost of the edge.
    \param rrt The rrt to update.
*/
void AddEdgeToRRT(unsigned int i,unsigned int j,double c,Trrt *rrt);


/** 
   \brief transition Test for Transition RRT

            transition Test for Transition RRT

   \param  pr The set of parameters.
   \param parent The parent node of the transition.
   \param q_next The configuration to be reached.
   \param deltaStep The distance step for the transition.
   \param cost The cost of q_next to be returned.
   \param costF The cost function used to evaluate the configuration cost.
   \param costData To be used as last parameter for the cost funtion.
   \param rrt The RRT.
*/
boolean TransitionTestRRT(Tparameters *pr,unsigned int parent,
			  double* q_next,double deltaStep,double* cost,
			  double (*costF)(Tparameters*,boolean,double*,void*),
			  void *costData,Trrt *rrt);

/** 
    \brief A rewire that is propagates as much as necessary over the graph.

    A version of \ref ReWireRRTstar to be used when the RRT is in graph mode.
    This re-wire uses the neighbours and cost-to-neighbour stored in the
    RRT nodes and propagages the recursively propagates the updates
    to all the necessary nodes in the graph.

    \param pr The set of parameters.
    \param q The priority queue with the nodes to update.
    \param g The goal configuration.
    \param steps Steps forming the solution. Only used in bi-directional trees.
    \param l Best estimation of the cost start-goal up to now.
             Only updated in bidirectional trees.
    \param rrt The RRT to rewire.
*/
void RecursiveReWireRRTstar(Tparameters *pr,Theap *q,double *g,Tvector *steps,double *l,
			    Trrt *rrt);
/** 
   \brief Optimal RRT on manifolds.

   Tries to determine an optimal path to the goal using the RRT*
   method by S. Karaman and E. Frazzoli "Sampling-based algorithms for optimal
   motion planning" International Journal of Robotics Research, 2011
   but adapted to operate on manifolds. In this case the connections
   of the connection between points on the manifold is done using the
   method by Berenson, D., Srinivasa, S., and Kuffner, J. (2011).
   Task space regions: A framework for pose-constrained manipulation planning.
   International Journal of Robotics Research. doi 10.1177/0278364910396389.

   Note that in this case the RRT construction is not stopped when the goal
   is reached but continues refining the path for the maximum time allowed
   for the tree construction.

   If constant GAMMA is 0 this procedure only finds the first path
   to the goal and then stops (to attempt to improve the path is done).

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the RRT.
             This is also a sample including only system variables.
   \param it [output] Number of iterations actually executed.
   \param times Optional table to store the time at each iteration.
                If not used set to NULl at call.
   \param costs Optional table to store the cost of the path at each interation.
                If not used set to NULl at call.
   \param planningTime Time actually used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output path (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param grst Global RRT statistics. Used when collecting averages over
               different RRT executions. Otherwise is NULL.
   \param rrt The RRT to expand.

   \return TRUE if the path exists.
*/
boolean RRTstar(Tparameters *pr,double *pg,
		unsigned int *it,double *times,double *costs,
		double *planningTime,double *pl,
		unsigned int *ns,double ***path,
		TRRTStatistics *grst,Trrt *rrt);
/** 
   \brief Optimal RRT on manifolds.

   This is the same as \ref RRTstar but implements a bi-directional search.

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the RRT.
             This is also a sample including only system variables.
   \param it [output] Number of iterations actually executed.
   \param times Optional table to store the time at each iteration.
                If not used set to NULl at call.
   \param costs Optional table to store the cost of the path at each interation.
                If not used set to NULl at call.
   \param planningTime Time actually used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output path (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param grst Global RRT statistics. Used when collecting averages over
               different RRT executions. Otherwise is NULL.
   \param rrt The RRT to expand.

   \return TRUE if the path exists.
*/
boolean BiRRTstar(Tparameters *pr,double *pg,
		  unsigned int *it,double *times,double *costs,
		  double *planningTime,double *pl,
		  unsigned int *ns,double ***path,
		  TRRTStatistics *grst,Trrt *rrt);

/** 
   \brief Extends a RRT until we reach a targed point.

   Adds as many branches as necessary to the RRT (using \ref AddBranchToRRT)
   until a targed configuration is reached (approached at a small distance).

   The tree extension is performed using the strategy defined in
     Dalibard, S., Nakhaei, A., Lamiraux, F., and Laumond, J.-P. (2009).
     Whole-body task planning for a humanoid robot: a way to integrate collision
     avoidance. In IEEE-RAS International Conference on Humanoid Robots,
     pages 355-360.

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the RRT.
             This is also a sample including only system variables.
   \param time Actual time used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output path (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param grst Global RRT statistics. Used when collecting averages over
               different RRT executions. Otherwise is NULL.
   \param rrt The RRT to expand.

   \return TRUE if the path exists.
*/
boolean ccRRT(Tparameters *pr,double *pg,double *time,
	      double *pl,unsigned int *ns,double ***path,
	      TRRTStatistics *grst,Trrt *rrt);


/** 
   \brief Extends a T-RRT until we reach a targed point.

   Adds as many branches as necessary to the RRT (using \ref AddBranchToRRT)
   until a targed configuration is reached (approached at a small distance).

   The difference with respect ccRRT is that here we take into account
   a cost function using the strategy proposed in

     L. Jaillet, J. Cortes, T. Simeon,
     Sampling-based path planning on configuration-space costmaps
     IEEE Transactions on Robotics, Vol. 26(4), pp. 635 - 646, 2010.
     http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=5477164

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the RRT.
             This is also a sample including only system variables.
   \param time Actual time used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param pc The cost of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output path (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param costF The cost function.
   \param costData User data to be provided to the cost function as a last
                   parameter.
   \param grst Global RRT statistics. Used when collecting averages over
              different RRT executions. Otherwise is NULL.
   \param rrt The RRT to expand.

   \return TRUE if the path exists.
*/
boolean ccTRRT(Tparameters *pr,double *pg,
	       double *time,
	       double *pl, double* pc, unsigned int *ns,double ***path,
	       double (*costF)(Tparameters*,boolean,double*,void*),
	       void *costData,
	       TRRTStatistics *grst,Trrt *rrt);



/** 
   \brief Extends a RRT until we reach a targed point.

   Adds as many branches as necessary to the RRT (using \ref AddBranchToRRT)
   until a targed configuration is reached (approached at a small distance).

   The tree extension is performed using the strategy defined in
     Berenson, D., Srinivasa, S., and Kuffner, J. (2011).
     Task space regions: A framework for pose-constrained manipulation planning.
     International Journal of Robotics Research. doi 10.1177/0278364910396389.

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the RRT.
             This is also a sample including only system variables.
   \param time Actual time used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output path (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param grst Global RRT statistics. Used when collecting averages over
               different RRT executions. Otherwise is NULL.
   \param rrt The RRT to expand.

    \return TRUE if the path exists.
*/
boolean cBiRRT(Tparameters *pr,double *pg,
	       double *time,
	       double *pl,unsigned int *ns,double ***path,
	       TRRTStatistics *grst,Trrt *rrt);

/** 
    \brief Produces a vector with the nodes in a given branch.

    Produces a vector with the nodes connecting a given node with the
    root of the RRT.

    The vector is created inside this function but must be destroyed
    externally.

    \param sID The sample to connect to the root.
    \param path The vector with the samples to visit along the path.
    \param rrt The RRT.

    \return The length of the path.
*/
double RRTPathSteps(unsigned int sID,Tvector *path,Trrt *rrt);


/** 
   \brief Changes the optimal path in a bidirectional RRT.

   Replaces a given path by another passing by two nodes in the two trees of a
   bidirectional RRT.

   Note that in this case the path is just a list of nodes to be visited in order.
   The actual path between them is not computed, but will be computed at the end
   of the planning (this saves time during planning).

   \param l1 Sample in the first tree that can be connected to the second tree.
   \param l2 Sample in the second tree that can be connected to the first tree.
   \param c12 Cost of the transition from l1 to l2.
   \param steps Vector of nodes forming the path. This vector must be initialitzed
                externally.
   \param rrt The RRT to query.

   \return The length of the new path.
*/
double ChangeBiRRTSteps(unsigned int l1,unsigned int l2,double c12,
			Tvector *steps,Trrt *rrt);

/** 
    \brief Updates the current optimal path.

    Tries to incorporate the recent changes in the trees to the optimal path.

    The optimal paths in a BiRRT are defined from two nodes, each one in a different tree.
    This path is represented by a list of nodes. However,
    the optimal path can be improved taking into accont the wires and rewires
    in the trees. This functions takes the list of nodes that define the optimal
    path and incorporates the shortcuts discobered in the tree since the path
    was defined.

    \param steps Vector of nodes forming the path. This vector must be initialitzed
                 externally.
    \param rrt The RRT to query.

    \return The new lenght of the optimal path.
*/
double UpdateBiRRTSteps(Tvector *steps,Trrt *rrt);

/** 
   \brief Collects samples from the tree root to a given sample.

   Reconstruct the path from the tree root to the sample in the tree
   closer to the goal.
   This is typically used to get the  targed is reached.

   \param pr The set of parameters.
   \param sID Sample to connect to the root of the tree.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param pc The cost of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of samples in the output path.
   \param path The output path.
   \param action Action taking to each configuration. Only used in problems with
                 dynamics.
   \param time Time for each action. Only used for problems with dynamics.
   \param rrt The RRT structure to query.

   \return The size of each path step (system variables stored for each step).
*/
unsigned int ReconstructRRTPath(Tparameters *pr,unsigned int sID,
				double *pl,double *pc,
				unsigned int *ns,double ***path,double ***action,double **time,
				Trrt *rrt);

/** 
   \brief Determines the path from start to goal using an RRT.

   Determines the path from start to goal using an RRT, if one exists.


   \param pr The set of parameters.
   \param pgs A point on the manifold to reach in SIMPLIFIED form.
   \param l1 Sample in the first tree close to the second tree. Used only
             for bidirectional RRTs.
   \param l2 Sample in the second tree close to the first tree. Used only
             for bidirectional RRTs.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param pc The cost of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output path (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param action Action taking to each configuration. Only used in problems with
                 dynamics.
   \param time Time for each action. Only used for problems with dynamics.
   \param rrt The RRT to query.

   \return TRUE if the path exists.
*/
boolean PathStart2GoalInRRT(Tparameters *pr,double *pgs,
			    unsigned int l1,unsigned int l2,
			    double *pl,double *pc,
			    unsigned int *ns,double ***path,double ***action,double **time,
			    Trrt *rrt);

/** 
    \brief Identifies bidirectional RRTs.

    Identifies bidirectional RRTs.

    \param rrt The RRT to query.

    \return TRUE if the RRT is bidirectional (i.e., \ref TWO_TREES, or \ref TWO_TREES_WITH_SWAP).
*/
boolean Bidirectional(Trrt *rrt);

/** 
    \brief Identifies mode of the RRTs.

    Identifies mode of the RRTs.

    \param rrt The RRT to query.

    \return \ref ONE_TREE, \ref TWO_TREES, or \ref TWO_TREES_WITH_SWAP.
*/
unsigned int GetRRTMode(Trrt *rrt);

/** 
    \brief Checks if a sample is in the dynamic domaiin of a given node.

    Checks if a sample is in the dynamic domaiin of a given node. Random samples
    out of the dynamic domain should be rejected.

    \param i The index of the sample giving the dynamic domain.
    \param q The random sample.
    \param rrt The RRT to query.

    \return TRUE if the random sample is in the dynamic domain.
*/
boolean InDynamicDomain(unsigned int i,double *q,Trrt *rrt);

/** 
    \brief Sets the dynamic domain.

    If the dynamic domain technique is used, and a problem is detected
    when extending a branch from a given node, we set the dynamic domain
    for this node so that new random samples outside the dynamic domain
    are rejected.

    \param i The node whose dynamic domain need to be adjusted.
    \param collision TRUE if the branch is stopped due to a collision.
    \param rrt The RRT to update.
*/
void AdjustDynamicDomain(unsigned int i,boolean collision,Trrt *rrt);

/** 
    \brief Returns the current dynamic domain radius for a given sample.

    Return the dynamic domain radious for a given sample. If the dynamic
    domain technique is not active or the radiius for the sample has not
    been set yet, this function returns 0.

    \param i The sample identifier.
    \param rrt The RRT structure to query.

    \return The dynamic domain for sample 'i'.
*/
double GetDynamicDomainRadius(unsigned int i,Trrt *rrt);

/** 
    \brief TRUE if the dynamic domain is active.

    TRUE if the dynamic domain technique is used. Using this technique
    the random sample are rejected if they are no in the dynamic domain
    of the nearest-neighbour sample.

    \param rrt The RRT to query.

    \return TRUE if the RRT uses the dynamic domain technique.
*/
boolean DynamicDomainRRT(Trrt *rrt);

/** 
   \brief Number of nodes in the RRT.

   Returns the number of nodes (samples) in the RRT.

   \param rrt The RRT to query.

   \return The number of samples stored in the RRT so far.
*/
unsigned int GetRRTNumNodes(Trrt *rrt);

/** 
   \brief Space of the action dimension.

   Space of the action dimension.

   \param rrt The RRT to query.

   \return The dimension of the action space.
*/
unsigned int GetRRTActionSpaceDimension(Trrt *rrt);

/** 
   \brief Returns one of the nodes of the RRT.

   Returns a pointer to the sample in the  RRT with the given identifier.

   \param i The identifier of the node.
   \param rrt The RRT to query.

   \return A pointer to the sample or NULL if the samples does not exists in the tree.
*/
double *GetRRTNode(unsigned int i,Trrt *rrt);

/** 
   \brief Returns the tree for a given node.

   In bidirectional RRTs, identifies the tree including a given node.

   \param i The identifier of the node.
   \param rrt The RRT to query.

   \return The tree (START2GOAL or GOAL2START) including the given node.
*/
unsigned int GetRRTNodeTree(unsigned int i,Trrt *rrt);

/** 
   \brief Returns identifier of the parent of one of the nodes of the RRT.

   Returns the identifier of the parent for a given RRT node.

   \param i The identifier of the node.
   \param rrt The RRT to query.

   \return The parent identifier or NU_UINT if the node does not exists or if it is
           the root (it has not parent).
*/
unsigned int GetRRTParent(unsigned int i,Trrt *rrt);

/** 
    \brief Changes the parent for a given node.

    Changes the parent for a given node in the RRT.
    By changing the parent we also change the tree of the node
    to that of its new parent.

    \param i The node whose parent we want to change.
    \param p The new parent node.
    \param rrt The RRT to modify.
*/
void SetRRTParent(unsigned int i,unsigned int p,Trrt *rrt);

/** 
   \brief Action taking to the RRT node.

   Action executed to get the RRT node from the parent node.
   Only used in dynamical systems.

   \param i The identifier of the node.
   \param rrt The RRT to query.

   \return Pointer to the action. NULL if the action is not defined.
*/
double *GetRRTAction(unsigned int i,Trrt *rrt);

/** 
   \brief Time taken to reach the RRT node from the parent node.

   Time taken to reach the RRT node form the parent node executing
   the action returned by \ref GetRRTAction
   Only used in dynamical systems.

   \param i The identifier of the node.
   \param rrt The RRT to query.

   \return The time.
*/
double GetRRTTime(unsigned int i,Trrt *rrt);

/** 
   \brief Time taken to reach the RRT node from the root node.

   Time taken to reach the RRT node form the root node.
   Only used in dynamical systems.

   \param i The identifier of the node.
   \param rrt The RRT to query.

   \return The time.
*/
double GetRRTTimeFromRoot(unsigned int i,Trrt *rrt);

/** 
    \brief Returns the user info associated with a node.

    Returns the user info associated with a node.

    \param i The identifier of the node.
    \param rrt The RRT to query.

    \return The pointer to the info associated with the node.
*/
void *GetRRTNodeInfo(unsigned int i,Trrt *rrt);

/** 
    \brief Changes the user info associated with a node.

    Changes the user info associated with a node.

    \param i The identifier of the node.
    \param info The new user info.
    \param rrt The RRT to query.
 */
void SetRRTNodeInfo(unsigned int i,void *info,Trrt *rrt);

/** 
    \brief Returns the cost associated with a node.

    Returns the cost associated with a node.

    \param i The identifier of the node.
    \param rrt The RRT to query.

    \return The cost associated with the node.
*/
double GetRRTNodeCost(unsigned int i,Trrt *rrt);

/** 
    \brief Returns the cost from the parent node, if defined.

    Returns the cost from the parent node.

    \param i The identifier of the node.
    \param rrt The RRT to query.

    \return The cost associated with the node.
*/
double GetRRTNodeCostFromParent(unsigned int i,Trrt *rrt);

/** 
    \brief Changes the cost associated with a node.

    Changes the cost associated with a node.

    \param i The identifier of the node.
    \param costp The new cost from the parent sample, if defined.
    \param cost The new cost.
    \param rrt The RRT to query.
 */
void SetRRTNodeCost(unsigned int i,double costp,double cost,Trrt *rrt);

/** 
    \brief Changes the cost and the parent associated with a node.

    Changes the cost and the parent associated with a node.

    \param i The identifier of the node.
    \param p The parent node
    \param costp The new cost from the parent sample, if defined.
    \param cost The new cost.
    \param rrt The RRT to query.
 */
void SetRRTCostAndParent(unsigned int i,unsigned int p,double costp,double cost,Trrt *rrt);

/** 
   \brief Probability of leading to a unfruitfuill extension.

   Estimates the prob of a node to lead to an unfruitfull extension (to a collision or
   to a domain limit). There is always a marginal prob of a node of leading to a good
   extension. In this way the prob. completeness is maintained.

   \param i The identifier of the node.
   \param rrt The RRT to query.
*/
double RRTBlockedProb(unsigned int i,Trrt *rrt);

/** 
   \brief Returns a pointer to an array with the topology for each variable.

   Gives access to the topology for each variable stored in the RRT

   \param rrt The RRT to query.

   \return A pointer to the RRT topology array.
 */
unsigned int *GetRRTTopology(Trrt *rrt);

/** 
   \brief Weights for the distances between samples.

   Returns the weights for the distances between samples.
   Such weights are eventually used for nearest-neightbour determination
   (see \ref WEIGTHED_NN) and for determining the distance to the 
   goal (see \ref WEIGTHED_REACHED_GOAL).

   \param rrt The RRT to query.

   \return The pointer to the vector of weights of NULL if no
           weights are defined (i.e., all weights are the same).
*/
double *GetRRTWeights(Trrt *rrt);

/** 
    \brief Computes the cost from a node to the root.

    Computes the cost from a node to the root by adding the
    individual cost of the node-parent relations.

    During re-wires the cost of a node can change without being
    reflected in the cost associated with this node due to changes
    in the branch including the node that are not yet propagated.
    This function computes the true cost with full propagation given
    the current tree.

    \param sID Identifier of the node whose cost we have to computed.
    \param rrt The RRT.
*/
double CostToRoot(unsigned int sID,Trrt* rrt);

/** 
    \brief Updates the cost from a node to the root.

    Updates the cost from a node to the root by adding the
    individual cost of the node-parent relations.

    \param sID Identifier of the node whose cost we have to updated.
    \param rrt The RRT.
*/
void UpdateCostToRoot(unsigned int sID,Trrt* rrt);

/** 
    \brief Updates the tree assignment a node to the root.

    Checks the tree including the current node and assigns it to this tree.
    During re-wires the actual tree of a node can change due to changes along
    the branch including this tree that are not propagated to it. This
    functions makes sure there is no inconsistency at least for the
    selected node.

    \param sID Identifier of the node whose tree we have to computed.
    \param rrt The RRT.
*/
void UpdateTree(unsigned int sID,Trrt* rrt);

/** 
    \brief A combination of \ref UpdateCostToRoot and \ref UpdateTree.

    A combination of \ref UpdateCostToRoot and \ref UpdateTree defined to
    gain some efficiency.

    \param sID Identifier of the node to update.
    \param rrt The RRT.
*/
void UpdateCostAndTree(unsigned int sID,Trrt* rrt);


/** 
    \brief Computes the number of steps from a node to the root.

    Computes the number of steps from a node to the root.

    \param sID Identifier of the node whose cost we have to computed.
    \param rrt The RRT.
*/
unsigned int StepsToRoot(unsigned int sID,Trrt* rrt);

/** 
   \brief Pots a projection of a RRT.

   Plots a 3d projection of a RRT defined on a manifold.

   Although the ambient space can have arbitrary dimension we project
   it on 3 dimensions. Only 2D manifolds plots can be properly visualized.

   The output plot can be visualized using geomview.

   \param fname File where to store the plot.
   \param argc Number arguments given to the program calling this function.
               This is used to write commnets in the output \e gcl file so that the
	       plot can be easiy reproduced.
   \param arg Arguments given to the program calling this function. This is used
              This is used to write commnets in the output \e gcl file so that the
	      plot can be easiy reproduced.
   \param pr The set of parameters.
   \param xID The first ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param yID The second ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param zID The thrid ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param p1 Start sample of the RRT (vector with 3 components, i.e., already in the projected
             space). NULL if not given.
   \param p2 Goal sample of the RRT (vector with 3 components, i.e., already in the projected
             space). NULL if not given.
   \param rrt The RRT to plot.

   \sa PlotMap.
*/
void PlotRRT(char *fname,int argc, char **arg,Tparameters *pr,
	     unsigned int xID,unsigned int yID,unsigned int zID,
	     double *p1,double *p2,Trrt *rrt);

/** 
   \brief Stores the nodes of the RRT.

   Stores the nodes of the RRT in the form of boxes.

   \param pr The set of parameters.
   \param fname Name to use for the two output file.
   \param saveWithDummies TRUE if the output has to include de dummies.
                          This is necessary only if you plan to unsimplify the output
			  points.
   \param rrt The RRT process.
*/
void SaveRRTNodes(Tparameters *pr,char *fname,boolean saveWithDummies,Trrt *rrt);

/** 
   \brief Stores the cost associated with the nodes of the RRT.

   Stores the cost associated with the nodes of the RRT. This is typically  used
   when dealing with molecules. In this case the cost is the energy.

   \param pr The set of parameters.
   \param fname Name to use for the two output file.
   \param rrt The RRT process.
*/
void SaveRRTCosts(Tparameters *pr,char *fname,Trrt *rrt);

/** 
    \brief Memory used by a given RRT.

    Returns the approximated memory used (in bytes) by a given RRT.

    \param rrt The RRT.

    \return The size of the RRT in bytes.
*/
unsigned int RRTMemSize(Trrt *rrt);

/** 
   \brief Stores the RRT information on a file.

   Stores all the information in the RRT in a file.

   \todo Save RRT in binary format.

   \param fname Name of the file where to store the RRT.
   \param rrt The RRT to store.
*/
void SaveRRT(Tfilename *fname,Trrt *rrt);

/** 
   \brief Defines a RRT from the information on a file.

   Construct a RRT from the information previously stored in a file
   by \ref SaveRRT.

   The user information stored in the node (see \ref GetRRTNodeInfo and
   \ref SetRRTNodeInfo) is lost when storing the RRT in a file.
   Right now we never store user info in the RRT nodes and, thus this
   limitation has no effect.

   \param pr The set of parameters.
   \param fname The name of the file from where to get the information.
   \param w The world with the equations defining the manifold where the RRT
            is defined. This is not stored in the file and must be provided
	    externally.
   \param rrt The RRT to define.
*/
void LoadRRT(Tparameters *pr,Tfilename *fname,TAtlasBase *w,Trrt *rrt);

/** 
   \brief Prints defines.

   Prints the defines in rrt.h

   This is used only for debug purposes.
   
   \param f The file where to store the values.
*/
void PrintRRTDefines(FILE *f);


/** 
   \brief Destructor.

   Deletes the information stored in the RRT.

   \param rrt The RRT to delete.

*/
void DeleteRRT(Trrt *rrt);

#endif
