#ifndef ATLASRRTH
#define ATLASRRTH

#include "atlas.h"
#include "rrt.h"
#include "dynamics.h"

/** 
   \file atlasrrt.h

   \brief Definition of the combination of an atlas with a RRT.

   Defines a RRT where the sampling is done using an atlas.

   Many functions are very similar to those for \ref Trrt but
   adapted to work in combination with an atlas.

   \sa atlasrrt.c, Tatlasrrt
*/

/** 
   \brief Vebosity of the AtlasRRT operations

   Vebosity of the atlasRRT operations. If set to 0 only  minimalistic
   information is printed.

   Note that some of the operations of the AtlasRRT are actually performed
   at the level of RRT. Thus to get a complete information you should
   set \ref RRT_VERBOSE to 1 too. And the same applies for \ref ATLAS_VERBOSE.
*/
#define ATLASRRT_VERBOSE (_DEBUG>1?_DEBUG-1:0)

/** 
    \brief Revisit charts

    If set, RRT branches can enter previously existing charts (charts in the
    atlas before starting the branch).

    This option is only taken into account when extending an RRT (towards and
    randomly generated sample) and not when aiming at a sample already in
    the RRT (when 
*/
#define REVISIT_CHARTS 1

/** 
    \brief Repeat charts

    If set, RRT branches can re-enter previously traversed charts (by the same branch).
*/
#define REPEAT_CHARTS 0

/** 
    \brief Randomize the integration time for each planning step.

    If set to 1, the integration time for each planning step is set at random
    with a maximum set in the parameters (\ref CT_INTEGRATION_TIME).
*/
#define RANDOM_INT_TIME 1

/** 
    \brief Re-compute the LQR at each new chart.

    If set, we re-compute the LQR policy after the creation of a new chart.
    In this way, the linearization errors may be mitigated and the system
    may converge faster to the random state (or, eventually, the goal).

    Possible values:
        - 0: We do not re-compute the LQR policy when moving to a new chart.
	- 1: We re-compute the policy when creating a new chart.
	- 2: We re-compute the policy also when moving to an existing chart.
*/
#define RELINEALIZE_DYNAMICS 2

/** 
   \brief Add all small steps along a dynamic branch.

   In dynamic branches we can add just the last step or all intermediate steps.
   This second option generates more nodes in the tree but provides more
   points for future three extension.

   - When 0, only the last state of the simulation is stored in the three.
     This is the only state that can be used for future three extensions.
     The rest of the states generated in the simulation are stored in the
     RRT edge.
   - When 1, we add the last state in the simulation plus all the states
     where a chart is generated.
   - When 2, we add all the simulated states in the RRT. This enlarges
     the places where we can extend an RRT and may be necessary in
     hihghly dynamic problems.
   .
*/
#define DYNAMICS_ADD_ALL 1

/** 
    \brief LQR randomization

    If set (i.e., larger than 0) some of the action are selected at random
    instead of using the LQR approach. This only holds when using LQR, of course.
    The value is in the range [0,1] and gives the probability of executing 
    random actions (e.g., 0.1 means a 10% of chance of selecting the action
    at random).
*/
#define RANDOMIZED_LQR (SATURATE_ACTIONS?0.01:0.0)

/** 
   \brief Set this to one to check the global curvature tolerences between charts.

   Set this to one to check the global curvature tolerences between charts.
   Otherwise, it is only the curvature along the direction of expansion that is checked.
*/
#define GET_ATLASRRT_GLOBAL_CURV_CHECK 0

/** 
   \brief Reject samples if they are not in the dynamic cone of the near sample.

   Reject samples if they are not in the dynamic cone of the near sample.
*/
#define REJECT_USING_DYNAMIC_CONE 0

/** 
    \brief Use the RRT connect strategy for problems wiht dynamics.

    If set, the RRT for problems with dynamics implement the connect
    stratey instead of the extend, i.e., braches are extended
    as far as they get closer to the random sample.
*/
#define ATLASRRT_DYNAMIC_CONNECT 1

/** 
   \brief Collect information when simulating.

   If set we collect statistics during the simulation. This is only used
   for debugging purposes and mainly to check the number of Broyden
   iterations.
*/
#define DEBUG_SIMULATION 0

/** 
   \brief Set this to one to gather statistics of AtlasRRT construction.

   Set this to one to gather statistics of AtlasRRT construction process.
   These statistics are printed at the end of the AtlasRRT construction.
 */
#define GET_ATLASRRT_STATISTICS 1

/** 
   \brief Set this to one to adjust the sampling area.

   If set (>0) the sampling area is adjusted (reduced/increased) taking
   into account the branch extension (if successful the sampling area is incresased
   and if a branch extension failed the sampling area is reduced).

   Two modes are possible
      - 1 the sampling area is adjusted locally (just for the chart used for sampling).
      - 2 the sampling area is adjusted globally (for all the charts).
      .

   The ratio at which the sampling area is adjusted is defined in \ref MOV_AVG_UP and
   \ref MOV_AVG_DOWN.

   \todo Set \ref ADJUST_SA as a parameter so that it can be set without re-compiling. This implies
         to add an 'scale' field to the AtlarRRT structure and to modify some
	 function interfaces and the SaveAtlasRRT (and the load) accordingly.
*/
#define ADJUST_SA 0

/** 
   \brief Set to 1 if nearest neighbours are searched in the chart including q_rand.

   If set to 1 we search for nearest neighbour inside the chart including the random sample.

   This should only be done in problems with dynamics and when using the time to go metric.
*/
#define NN_IN_CHART 0

/** 
    \brief Look for nearest neighbour in neighbouring charts.

    If \ref NN_IN_CHART is set, we can additionally look for the nearest neighbours
    in the neighbouring chart just activating this flag.
*/
#define NN_IN_NEIGHBOUR_CHART 0

/** 
   \brief Statistics on the AtlasRRT constrution

   Data collected during the AtlasRRT construction so that this
   process can be analysed.

   Statistics should only be used in debug/analysis mode. Otherwise it is
   better to skip collecting them (for efficiency reasons).
   See \ref GET_ATLASRRT_STATISTICS

   Note that this structure is not thread-save. Thus, we must only collect
   statistics when executing in single core mode.

   \todo Switch to thread-save statistics before implementing a parallel
         version of the AtlasRRT.
*/
typedef struct {
  unsigned int n;                         /**< Number of statistics accumulated in
				   	       the structure. */

  unsigned int nBranch;                   /**< Number of branch extensions. */
  unsigned int nNoEmptyBranch;            /**< Number of non-empty branches. */

  unsigned int nDynamicExtension;         /**< Number of dynamic branches. */
  unsigned int nImprovedDynamicExtension; /**< Number of dynamic branches getting 
					       closer to q_rand. */
  
  unsigned int nTreeConnection;           /**< Number of attemps to connect the two trees. */
  unsigned int nNoEmptyTreeConnection;    /**< Number of non-empty attemps of tree connection. */

  unsigned int nStep;                     /**< Number of  steps  in branch extension. */
  double dQrand;                          /**< Accumulated distances from q_rand-tree. */

  /* Reasons to stop a branch extension */
  unsigned int nQrandReached;             /**< Times we actually reached q_rand. */
  double dQrandReached;                   /**< Distance to q_rand when reached. This is only relevant in
					       problems with dynamics and using LQR steer. */
  unsigned int nNotInDomain;              /**< Stopped when we move out of the domain. */
  unsigned int nCollision;                /**< Stopped due to collisions. */
  unsigned int nTooLong;                  /**< Stopped due to its length. */
  unsigned int nTooFar;                   /**< Stopped due ot a ball centered at q_near. */
  unsigned int nRevisitedChart;           /**< Stopped to avoid re-entering previous charts. */
  unsigned int nRepeatedChart;            /**< Stopped to avoid re-visitng charts already visited along the branch. */
  unsigned int nChartBlocked;             /**< Stopped after creating a new chart. */
  unsigned int nIntTimeReached;           /**< Stopped after reaching the maximum integration time. */
  unsigned int nNoAction;                 /**< Stopped when no valid action is available. */
  unsigned int nNoDir;                    /**< Stopped since we do not have a clear advance direction. */
  unsigned int nNoPolicy;                 /**< Stopped since we can not determine a LQR policy. */
  unsigned int  nToptIncrements;          /**< Stopped due to an increment in Topt, i.e., not approaching goal. */
  unsigned int nImpossible;               /**< Stopped when an impossible situation happens. */
  unsigned int nNoReplay;                 /**< Stopped when there is no more data to replay a branch. */
  
  double satAction;                       /**< Number of times \ref LQRPolicy returns a saturated action.
					       This is normalized by the dimension of the action space. */
  unsigned int nLQRPolicy;                /**< Number of times \ref LQRPolicy is called. */
  
  double topt;                            /**< Optimal time as returned by \ref LQRComputePolicy. */
  unsigned int nLQRComputePolicy;         /**< Number of times \ref LQRComputePolicy is called. */

  unsigned int nB;                        /**< Number of times we used the Broyden method. */
  unsigned int itB;                       /**< Total iterations of the Broyden method. */
  
  unsigned int nTransTestFailed;          /**< Stopped when a transition test failed. */
  unsigned int nDynamicErrors;            /**< Stopped with there is a dynamic error (error computing acceleration). */

  /* Some of the reasons to create a new chart */
  unsigned int nErrorNewChart;            /**< Errors when creating a chart. */
  unsigned int nNoConvergent;             /**< A non convergent projection. */
  unsigned int nOutOfChart;               /**< Reached the extreme of the chart domain.*/
  unsigned int nLargeCurvature;           /**< A large curvature error between the charts. */
  unsigned int nDirLargeCurvature ;       /**< Samples that produce large curvature
					       in a given direction. */

  /* Refinements necessary in branch creation */
  unsigned int nStepReduction;            /**< Times we had to reduce the default
					     step size to create a new valid node. */

  unsigned int nSample;                   /**< Total of samples in the atlasRRT. */
  unsigned int nRepeatedSample;           /**< Total of repeated samples in the atlasRRT (branches that end up in an known sample). */
  unsigned int nChart;                    /**< Total of charts in the atlasRRT. */
  unsigned int nNoConnect;                /**< Number of new charts that do not
					     intersect with its parent */
  unsigned int nSingular;                 /**< Number of attempts to create a char in a
					       singular region */

  /* Information about sampling */
  unsigned int nRandom;                   /**< Number of times we generated a random
					       sample */
  unsigned int nRejections1;              /**< Number of rejected random samples (rejected
					       in the generation process). */
  unsigned int nRejections2;              /**< Number of rejected random samples (rejected
					       in post-process (dynamic domain and alike). */
  unsigned int nRejections3;              /**< Subset of \e nRejections2 due to the selection
					       of blocked nodes. */
  unsigned int nRejections4;              /**< Rejections due to missalignment of the dynamic 
					       cones. */

  /* Information aobut collison checking */
  unsigned int nCollisionChecks;          /**< Number of collision checks */
  
  double nAverageNeighbours;              /**< Number of average neighbours per chart. */
  
} TAtlasRRTStatistics;

/** 
   \brief Information for each sample in an AtlasRRT.

   Emcompasses the information associated with each sample in an AtlasRRT that
   is not already included in the underlying RRT. Typically this is the
   assigment of samples to charts.

   If the ambient space is spherical in any dimension, the samples are stored in
   canonical form (in the -pi,pi) range. The parameters are those corresponding
   to this representation.
 */
typedef struct {
  unsigned int id;            /**< Identifier of the sample. */
  double *s;                  /**< Pointer to the sample info. Pointer to the
			           sample stored in the RRT. */
  double *t;                  /**< Samples for the RRT projected on the charts. */
  unsigned int pc;            /**< Chart in which each sample is generated.*/
  unsigned int c;             /**< Current chart for each sample. This can be NO_UINT
			           if the sample in defined in a temporary chart. */
  unsigned int generateChart; /**< TRUE if the sample triggered the creation of a chart. */
  unsigned int lsc;           /**< Linked list with the samples for each chart.
			           Index of next sample in the chart. */
} TSampleInfo;

/** 
   \brief Information for each chart in an AtlasRRT.

   Emcompasses the information associated with each chart in an AtlasRRT that
   is not already included in the underlying Atlas. Typically this is the
   assigment of samples to charts and of charts to trees of samples.
 */
typedef struct {
  unsigned int lc;      /**< Begining of the linked list of samples for each chart. */
  unsigned int tree;    /**< Tree to which the chart belongs to. */
  unsigned int it;      /**< Iteration at which the chart was created */
} TChartInfo;

/** 
   \brief RRT with an atlas for sampling.

   This can be seen in two ways:

   - Defines a RRT where the sampling is guided using an atlas.
   - Defines an atlas where the expansion is guided by an RRT.

*/
typedef struct {
  TAtlasBase *w;                /**< The world on which the atlas is defined */

  unsigned int m;               /**< Number of variables. Dimension of the ambient space. */
  unsigned int k;               /**< Dimension of the manifold */
  double e;                     /**< Maximum error for the linear approximation of the manifold. */
  double ce;                    /**< Maximum  error cuvature between the charts and the manifold */
  double r;                     /**< Radius around \e p (in tangent space) where the
				     linearization holds. */

  unsigned int dynamics;        /**< Not null if the problem invoves dynamic variables and equations. 
				      The value indicates the integration method to use:
				             1: Local coordinates
				             2: Euler
				             3: Runge-Kutta4  */
  unsigned int nda;             /**< Number of dynamic actions to simulate in each AtlasRRT extension
				     attempt. */
  
  double dge;                   /**< Tolerance with respect to the goal in problems with dynamics. */
  unsigned int da;              /**< Dimension of the action space (if dynamics only). */
  TDynamicSpace *ds;            /**< Space for dynamic computations. Only used if dynamics is TRUE.
				     We allocate as many dynamic spaces as parallel threads.
				     In many non-parallel functions, though, (\ref RefineTrajectory,
				     \ref AtlasRRTSimulate) only
				     the first dynamics space (ds[0]) is used */

  boolean birrt;                /**< TRUE if the atlaRRT is to be bidirectional: one tree
				     from the start sample and one from the goal.
				     FALSE if the tree is to be one-dimensinal. */

  boolean parallel;             /**< TRUE if the AtlasRRT wil be processed (e.g., build)
				     in parallel. Up to now this is always FALSE but when
				     using the AtlasRRT* procedure where the wire is
				     executed in parallel and for problems with dynamic
				     constraints where different actions are simulated in parallel. */

  Tbox ambient;                 /**< Axis aligned bounding box enclosing the manifolds. */
  unsigned int *tp;             /**< Topology for each variable. */
  double *weights;              /**< Weights of the Euclidean distance. Only use if \ref WEIGTHED_REACHED_GOAL
				     is not null. */
  
  TJacobian J;                  /**< Symbolic Jacobian of the underlying system of equations. */

  Trrt rrt;                     /**< The RRT (includes the samples and the trees for NN search). */
  Tatlas atlas;                 /**< The atlas (includes the charts and their relations). */

  unsigned int ms;              /**< Space for samples so far. */
  unsigned int ns;              /**< Space for samples used so far. */
  TSampleInfo **si;             /**< Information associated with each sample */

  unsigned int mc;              /**< Space for list of samples per chart. */
  unsigned int nc;              /**< Number of charts so far. */
  TChartInfo **ci;              /**< Information associated with each chart */

  unsigned int mct1;            /**< Maximum number of charts of the first tree. */
  unsigned int nct1;            /**< Number of charts of the first tree. */
  unsigned int* chartsAtTree1;  /**< Charts of the first tree. */

  unsigned int mct2;            /**< Maximum number of charts of the second tree. */
  unsigned int nct2;            /**< Number of charts of the second tree. */
  unsigned int* chartsAtTree2;  /**< Charts of the second tree. */
} Tatlasrrt;

/** *****************************************************************************/

/** 
    \brief Init the Atlas RRT statistics.

    Init the Atlas RRT statistics.

    \param arst The AtlasRRT statistics to initialize.
*/
void InitAtlasRRTStatistics(TAtlasRRTStatistics *arst);

/** 
    \brief Accumulates two sets of Atlas RRT statistics.

    Accumulates two sets of Atlas RRT statistics.
    This is used to accumulate statistics when executing a long
    sequence of experiments.

    \param arst1 The atlas RRT statistics to accumulate.
    \param arst2 The atlas RRT statistics where to accumulate.
*/
void AccumulateAtlasRRTStatistics(TAtlasRRTStatistics *arst1,TAtlasRRTStatistics *arst2);

/** 
    \brief Prints the summary of atlasRRT statistics.

    Prints a report about the collected atlasRRT statistics.

    \param ar The AtlasRRT (might be NULL).
    \param arst The AtlasRRT statistics to print.
*/
void PrintAtlasRRTStatistics(Tatlasrrt *ar,TAtlasRRTStatistics *arst);

/** 
    \brief Destructor.

    Deletes the atlasRRT statistics object.

    \param arst The AtlasRRT statistics to delete.
*/
void DeleteAtlasRRTStatistics(TAtlasRRTStatistics *arst);

/** *****************************************************************************/


/** 
   \brief Defines a Atlas-RRT from a given point.

   Defines a Atlas-RRT with a single sample, the root.

   \param pr The set of parameters.
   \param parallel TRUE if tha AtlasRRT will be processed (build, etc) in parallel.
                   Right now only AtlasRRT* executes in parallel. The rest of
		   processes are still not parallelized.
   \param ps A point on the manifold from where to start the RRT. The RRT root.
             This is a sample including only system variables.
   \param mode Mode for the RRT: \ref ONE_TREE, \ref TWO_TREES, \ref TWO_TREES_WITH_SWAP.
   \param graph If TRUE the RRT is actually a graphs since we store the neighbours for
                each node, not just the parent. This is used to propagate improvements
		for RRT*.
   \param pg The goal for the planning. Only used if the AtlasRRT is
             bidirectional.
   \param w The base type with the equations (and possibly obstacles).
   \param ar The Atlas-RRT to create.
*/
void InitAtlasRRT(Tparameters *pr,boolean parallel,double *ps,unsigned int mode,boolean graph,
		  double *pg,TAtlasBase *w,Tatlasrrt *ar);

/** 
    \brief Generates a random sample to expand the AtlasRRT.

    Generates a random sample to expand the AtlasRRT. The sample
    can be generated with different policies according to the
    mode (from the ambient space, or near the existing nodes)
    and the goal (if defined the goal is used as random sample
    1 out of 100 times).

    \param pr The set of parameters.
    \param samplingMode Policy to generate the random sample. This can
                         be AMBIENT_SAMPLING (to generate it from the ambient space)
		         or KDTREE_SAMPLING (to generate it using the kd-tree).
			 or TANGENT_SAMPLING (to use the charts).
			 The KDTREE_SAMPLING only works if you use the cuik-kdtree
			 library. Otherwise AMBIENT_SAMPLING is used instead
    \param it Current iteration.
    \param tree The tree to use in the sampling. Only used if mode is
                KDTREE_SAMPLING.
    \param goal Goal node. NULL if we do not have goal (i.e. we are
                defining an exploration RRT) or if we can not use
		the goal as a random sample.
    \param scale  The global scale factor for the sampling areas of the charts.
    \param exploration Set to TRUE if samplingMode is TANGENT_SAMPLING and
                       the random sample is in the outer parts of the chart
		       used for sampling.
    \param onManifold TRUE if the sample is on the manifold.
    \param c_rand The index of the chart used for the sampling.
                  Only set if samplingMode is TANGENT_SAMPLING.
    \param t_rand The parameters on the chart used for the sampling.
                  Only set if samplingMode is TANGENT_SAMPLING.
    \param q_rand Space to store the random sample.
    \param arst Atlas statistics.
                This is only used we are repeating experiments. Otherwise is is NULL.
    \param ar AtlasRRT to use.

    \return TRUE if the goal is used as random sample.
*/
boolean AtlasRRTSample(Tparameters *pr,unsigned int samplingMode,
		       unsigned int it,unsigned int tree,
		       double *goal,double scale,boolean *exploration,boolean *onManifold,
		       unsigned int *c_rand,double *t_rand,double *q_rand,
		       TAtlasRRTStatistics *arst,Tatlasrrt *ar);

/** 
    \brief Validates a sample generate with \ref AtlasRRTSample

    Checks if a given sample is valid to expand the AtlasRRT.

    \param pr The set of parameters.
    \param c_rand Chart used to generate the random sample.
    \param t_rand The parameters of the random sample in the chart.
    \param q_rand The random sample.
    \param tree The tree where to look for nearest neighbours.
    \param expand2goal TRUE if the random sample is the goal.
    \param lastNN2Goal Last nearest-neighbour used when expanding to goal. We can
                       avoid expanding the same sample to the goal if it was not
		       succesful in a previous attempt.
    \param goal The goal.
    \param l The shortest path from start to goal so far. Only used for RRT*-like
             algorithms and it only has effect if it is not INF.
    \param h A lower estimate of the distance between the random sample and the goal.
             This is only relevant in RRT*-like algorhtms.
    \param i_near The nearest neighbour in the RRT.
    \param arst Statistics on the AtlasRRT construction process (only used if
                \ref GET_RRT_STATISTICS is set).
    \param ar AtlasRRT to use.

    \return TRUE if the random sample is valid.
*/
boolean AtlasRRTValidateSample(Tparameters *pr,unsigned int c_rand,double *t_rand,double *q_rand,
			       unsigned int tree,boolean expand2goal,
			       unsigned int lastNN2Goal,double *goal,double l,double *h,unsigned int *i_near,
			       TAtlasRRTStatistics *arst,Tatlasrrt *ar);

/** 
   \brief Increases the resolution of a trajectory.

   In problems with dynamics only the end-point of the simulated RRT branches
   are added to the tree. Thus, the resolution of the resulting trajectories
   are sometimes too coarse. This function simulates the trajectories between
   the steps in the trajectory to increase the time resolution of the
   trajectory. In this way, the animations are smoother.

   \param pr The set of parameters.
   \param id TRUE to use inverse dynamics to adjust the actions.
   \param ns The number of steps in the trajectory.
   \param path The states in the trajectory.
   \param actions The actions executed along the trajectory.
   \param times The time for each action.
   \param ar The atlas RRT.
*/
void RefineTrajectory(Tparameters *pr,boolean id,unsigned int *ns,double ***path,
		      double ***actions,double **times,Tatlasrrt *ar);

/** 
   \brief Dynamic simulation with a given action.

   Dynamic simulation from the first point in the atlasrrt (it is supposed to
   include only one point) applying a given action for the integration time
   fixed in the paremeter structure.

   \param pr The set of parameters.
   \param da Dimension of the action space. Number of elements in  \e u and in
             each vector in \e actions.
   \param u The action to apply.
   \param steps Steps to simulate (each of time INTEGRATION_TIME).
   \param ns Number of steps of the output paht (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param actions The action executed at each configuration. In this particular
                  function this is just a repetition of the input action \e u.
   \param times The time between each configuration.
   \param ar The Atlas-RRT.
*/
void AtlasRRTSimulate(Tparameters *pr,unsigned int da,double *u,
		      unsigned int steps,unsigned int *ns,double ***path,
		      double ***actions,double **times,Tatlasrrt *ar);

/** 
   \brief Extends a Atlas-RRT until we reach a targed point.

   Adds as many branches as necessary to the Atlas-RRT
   until a targed configuration is reached (approached at a small distance).

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the AtlasRRT.
             This is also a sample including only system variables.
	     It is only used for one-directional RRTs. For bidirectional
	     ones we use the one given in \ref InitAtlasRRT.
   \param time Time actually used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output paht (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param da Dimension of the action space. Only used in dynamical systems.
             Otherwise is 0.
   \param actions Action executed to reach step in the soluiont. Only used in
                  dynamical systems.
   \param times Time to reach each state. Only used in dynamical systems.
   \param str Structure to accumulate statistics on the Atlas RRT construction.
              This is only used we are repeating experiments. Otherwise is is NULL.
   \param ar The Atlas-RRT to expand.
*/
boolean AtlasRRT(Tparameters *pr,double *pg,
		 double *time,
		 double *pl,unsigned int *ns,double ***path,
		 unsigned int *da,double ***actions,double **times,
		 TAtlasRRTStatistics *str,Tatlasrrt *ar);


/** 
   \brief Extends a Atlas-TRRT until we reach a targed point.

   Adds as many branches as necessary to the Atlas-TRRT
   until a targed configuration is reached (approached at a small distance).

   The difference with respect AtlasRRT is that here we take into account
   a cost function using the strategy proposed in

     L. Jaillet, J. Cortes, T. Simeon,
     Sampling-based path planning on configuration-space costmaps
     IEEE Transactions on Robotics, Vol. 26(4), pp. 635 - 646, 2010.
     http://ieeexplore.ieee.org/xpls/abs_all.jsp?arnumber=5477164

   \param pr The set of parameters.
   \param pg A point on the manifold to reach with the AtlasTRRT.
             This is also a sample including only system variables.
	     It is only used for one-directional RRTs. No bidirectional
	      search with AtlasTRRT.
   \param time Time actually used in the planning.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param pc The cost of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of steps of the output paht (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param costF The cost function, if any.
   \param costData The last parameter of the cost funtion, if any.
   \param str Structure to accumulate statistics on the Atlas RRT construction.
              This is only used whe repeating experiments. Otherwise is is NULL.
   \param ar The Atlas-RRT to expand.
*/
boolean AtlasTRRT(Tparameters *pr,double *pg,double *time,
		  double *pl,double *pc,unsigned int *ns,double ***path,
		  double (*costF)(Tparameters*,boolean,double*,void*),
		  void *costData,TAtlasRRTStatistics *str,Tatlasrrt *ar);

/** 
   \brief Optimal AtlasRRT on manifolds.

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

   This is the atlas-based version of \ref RRTstar. The main difference is
   that the atlas is used to sample new nodes and to determine paths
   between samples.

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
   \param str Structure to accumulate statistics on the Atlas RRT construction.
              This is only used whe repeating experiments. Otherwise is is NULL.
   \param ar The AtlasRRT to expand.

   \return TRUE if the path exists.
*/
boolean AtlasRRTstar(Tparameters *pr,double *pg,
		     unsigned int *it,double *times,double *costs,
		     double *planningTime,double *pl,unsigned int *ns,double ***path,
		     TAtlasRRTStatistics *str,Tatlasrrt *ar);

/** 
   \brief Bidirectional version of \ref AtlasRRTstar.

   The same as \ref AtlasRRTstar but here a bi-directional RRT is built.

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
   \param str Structure to accumulate statistics on the Atlas RRT construction.
              This is only used whe repeating experiments. Otherwise is is NULL.
   \param ar The AtlasRRT to expand.

   \return TRUE if the path exists.
*/
boolean AtlasBiRRTstar(Tparameters *pr,double *pg,
		       unsigned int *it,double *times,double *costs,
		       double *planningTime,double *pl,unsigned int *ns,double ***path,
		       TAtlasRRTStatistics *str,Tatlasrrt *ar);

/** 
   \brief Number of nodes in the AtlasRRT.

   Returns the number of nodes (samples) in the AtlasRRT.

   \param ar The AtlasRRT to query.

   \return The number of samples stored in the AtlasRRT so far.
*/
unsigned int GetAtlasRRTNumNodes(Tatlasrrt *ar);

/** 
   \brief Number of charts in the AtlasRRT.

   Returns the number of charts in the AtlasRRT.

   \param ar The AtlasRRT to query.

   \return The number of charts in the AtlasRRT so far.
*/
unsigned int GetAtlasRRTNumCharts(Tatlasrrt *ar);


/** 
\brief  Selects a random point in the set of charts of the tree.

   Selects a random point in the set of charts reached by a given tree.

   \param pr The set of parameters.
   \param tree The tree.
   \param nm The indice of selected chart.
   \param scale The global scale factor for the sampling areas of the charts.
   \param t The parameters of the random point on the chart.
   \param p The random point on the manifold.
   \param ar The atlasRRT to query

   \return TRUE if the random point could be actually determined.
 */
boolean RandomPointInAtlasTree(Tparameters *pr,
			       double scale,unsigned int tree,
 			       unsigned int *nm,
			       double *t,double *p,
			       Tatlasrrt* ar);

/** 
   \brief Selects the nearest neighbour from the random point in a given chart.

   Selects the nearest neighbour from the random point in the chart including
   the random sample.

   \param pr The set of parameters.
   \param t2g Not zero if using a time2go metric.
   \param tree The tree. Only samples of this tree are considered as potential
               nearest-neighbours.
   \param chartId The chart including the random sample.
   \param q_rand The random sample.
   \param d The distance to the nearest neighbour. At input: minimu distance
            to considere points. At output: minimum distance to a neighbour.
   \param ar The atlasRRT to query.

   \return The identifier of the nearest-neighbour of \ref NO_UINT if no sample
           is a valid neighbour.
*/
unsigned int GetRRTNNInChart(Tparameters *pr,unsigned int t2g,unsigned int tree,
			     unsigned int chartId,double *q_rand,
			     double *d,Tatlasrrt *ar);

/** 
   \brief Time to go nearest neighbour of a tree to a given sample.

   Determines the closest sample in a given tree to another sample (in the other
   tree) using the time2go metric. This gives the point of the tree from where
   it is more likely to connec to the given sample.

   \param pr The set of parameters.
   \param tree The tree where to look for nearest neighbours.
   \param goal The identifier of the sample ot reach from the tree.
   \param ar The atlas RRT.

   \return The index of the sample in the tree closer (in time to go metric) 
           the goal sample. Can be NO_UINT if there is no good candidate
	   for connection.
*/
unsigned int Time2GoNNToTree(Tparameters *pr,unsigned int tree,
			     unsigned int goal,Tatlasrrt *ar);

/** 
   \brief Pots a projection of a Atlas-RRT.

   Combines the plot of the Atlas and the RRT.

   \param prefix Prefix for the name of the file where to store the plots.
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
   \param zID The third ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param p1 Root sample of the RRT (vector with 3 components, i.e., already in the projected
             space). NULL if not given.
   \param p2 Goal sample of the RRT (vector with 3 components, i.e., already in the projected
             space). NULL if not given.
   \param ar The Atlas-RRT to plot.

   \sa PlotAtlas, PlotRRT.
*/
void PlotAtlasRRT(char *prefix,int argc, char **arg,Tparameters *pr,
		  unsigned int xID,unsigned int yID,unsigned int zID,
		  double *p1,double *p2,Tatlasrrt *ar);

/** 
    \brief Memory used by a given atlasRRT.

    Returns the approximated memory used (in bytes) by a given atlasRRT.

    \param ar The atlasRRT.

    \return The size of the atlasRRT in bytes.
*/
unsigned int AtlasRRTMemSize(Tatlasrrt *ar);

/** 
   \brief Stores the Atlas-RRT information on a file.

   Stores the atlasRRT as a normal \ref Tatlas "atlas"  and a
   \ref Trrt "RRT" than can be latter
   read/plotted with the usual programs.

   Note that this does not save all the information stored in the AtlasRRT
   but only that necessary for plotting.

   \param pr The parameter set.
   \param prefix Prefix for the name of the files where to store the RRT, the Atlas
                 and the information linking the RRT and the Atlas.
   \param ar The Atlas-RRT to store.
*/
void SaveAtlasRRT(Tparameters *pr,char *prefix,Tatlasrrt *ar);

/** 
   \brief Defines an atlasRRT from the information on a file.

   Construct an atlasRRT from the information previously stored in a file
   by \ref SaveAtlasRRT.

   \param pr The set of parameters.
   \param prefix Prefix for the name of the files where to store the RRT the Atlas
                 and the information linking the RRT and the Atlas.
   \param w The world with the equations defining the manifold where the atlas
            is defined. This is not stored in the file and must be provided
	    externally.
   \param ar The atlasRRT to define.
*/
void LoadAtlasRRT(Tparameters *pr,char *prefix,TAtlasBase *w,Tatlasrrt *ar);

/** 
   \brief Prints defines.

   Prints the defines in atlasrrt.h

   This is used only for debug purposes.
   
   \param f The file where to store the values.
*/
void PrintAtlasRRTDefines(FILE *f);

/** 
   \brief Destructor.

   Deletes the information stored in the RRT.

   \param ar The RRT to delete.

*/
void DeleteAtlasRRT(Tatlasrrt *ar);


#endif
