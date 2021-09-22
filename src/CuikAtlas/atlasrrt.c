#include "atlasrrt.h"

#include "chart.h"
#include "filename.h"
#include "random.h"
#include "algebra.h"
#include "samples.h"
#include "vector.h"
#include "heap.h"

#include "boolean.h"

#include <string.h>
#include <math.h>

/** 
   \file atlasrrt.c

   \brief Implementation of the AtlasRRT functions.

   Implementation of the AtlasRRT functions.

   \sa atlasrrt.h, Tatlasrrt
*/

/** 
   \brief One of the addition modes for AddBranchToAtlasRRT

   Adds all nodes generated in the branch extension.
*/
#define ADD_ALL  0

/** 
   \brief One of the addition modes for AddBranchToAtlasRRT

   Adds all nodes generated in the branch extension, but
   avoiding repetitions.
*/
#define ADD_ALL_NO_REP  1

/** 
   \brief One of the addition modes for AddBranchToAtlasRRT

   Adds anly the last generated node during the branch extension.
*/
#define ADD_LAST 2

/** 
   \brief One of the addition modes for AddBranchToAtlasRRT

   Adds anly the last generated node during the branch extension if it is not
   already in the tree.
*/
#define ADD_LAST_NO_REP 3

/** 
   \brief One of the addition modes for AddBranchToAtlasRRT

   Adds the last generated node during the branch extension and all
   the samples where a chart is generated. In all cases
   repetitions are avoided.
*/
#define ADD_CHART_AND_LAST_NO_REP 4

/** 
   \brief One of the addition modes for AddBranchToAtlasRRT

   Do not add any node during the branch extension.
*/
#define ADD_NONE 5

/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief One of the pre-defined branch configurations

   Extends a AtlasRRT towards a random sample.

   All the generated samples are added to the RRT.
*/
#define EXTEND_RRT      0

/** 
   \brief One of the pre-defined branch configurations

   Extends a AtlasRRT towards a node already in a RRT
   (i.e., tries to connect a the two RRTs in a bi-directinal RRT).

   All the generated samples are added to the RRT.
*/
#define CONNECT_RRTs    1

/** 
   \brief One of the pre-defined branch configurations

   Checks if it is possible to connect two samples on the manifold.
*/
#define CONNECT_SAMPLES 2

/** 
   \brief One of the pre-defined branch configurations

   Checks if it is possible to connect two samples on the manifold but
   without checking for collisions (the connection is already known to
   be collision free).
*/
#define CONNECT_SAFE    3

/** 
   \brief One of the pre-defined branch configurations

   Simulates the effects of a particular action taking into account dynamics.
*/
#define SIMULATE_DYNAMICS 4

/** 
   \brief One of the pre-defined branch configurations

   Simulates the effects of a particular action taking into account dynamics.
   This is used when extending an RRT towards a random sample.
*/
#define EXTEND_RRT_DYNAMICS 5

/** 
   \brief One of the pre-defined branch configurations

   Simulates the effects of a particular action taking into account dynamics.
   This is used when extending an RRT towards a point already in the RRT
   (i.e., when trying to connect trees)
*/
#define CONNECT_RRT_DYNAMICS 6


/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Branch blocked state.

   The blocked state is defined as a bit-wise and of different possible reasons to stop the branch extension.

   The branch is not blocked so far.
*/
#define NO_BLOCKED 0

/** 
   \brief Branch blocked state.

   The branch is blocked because we can not determine a clear advance direction (the x_rand projects
   too close to x_near).
*/
#define NO_DIR (1<<0)

/** 
   \brief Branch blocked state.

   The branch is blocked because we can not determine a LQR policy.
*/
#define NO_POLICY (1<<1)

/** 
   \brief Branch blocked state.

   The branch is blocked because we do not have more data to replay a previous branch extension.
*/
#define NO_REPLAY (1<<2)

/** 
   \brief Branch blocked state.

   The branch is blocked because we reached a singular region (a region where we can not define
   charts).
*/
#define SINGULARITY (1<<3)

/** 
   \brief Branch blocked state.

   The branch is blocked because we repeated a point in the RRT.
*/
#define REPEATED_SAMPLE (1<<4)

/** 
   \brief Branch blocked state.

   The branch is blocked because the impossible happened. We have several imposible situations
   that may appear due to (numerical) errors. For instance, we must always be able to create
   a new chart close enough to a previous chart. If this is not true, the impossible happened.

   Typically an error is triggered in this cases.
*/
#define THE_IMPOSSIBLE (1<<5)

/** 
   \brief Branch blocked state.

   The branch is blocked because the branch entered in a previously created chart and the current
   branch extension configuration prevends this to happen. This is typically used to
   avoid branch crossing in kinematic planning.
*/
#define REVISITED_CHART (1<<6)

/** 
   \brief Branch blocked state.

   The branch is blocked because the branch entered in a chart already visited along the branch and the current
   branch extension configuration prevends this to happen. This is typically used to
   avoid branch crossing in kinematic planning.
*/
#define REPEATED_CHART (1<<7)

/** 
   \brief Branch blocked state.

   The branch is blocked because a transition test failed.
*/
#define TRANSITION_TEST_FAILS (1<<8)

/** 
   \brief Branch blocked state.

   The branch is blocked because it is already too far from the origin.
*/
#define TOO_FAR (1<<9)

/** 
   \brief Branch blocked state.

   The branch is blocked because it is already too long.
*/
#define TOO_LONG (1<<10)

/** 
   \brief Branch blocked state.

   The branch is blocked because a collision is detected.
*/
#define COLLISION (1<<11)

/** 
   \brief Branch blocked state.

   The branch is blocked because the branch reaches the limit of the domain.
*/
#define NOT_IN_DOMAIN (1<<12)

/** 
   \brief Branch blocked state.

   The branch is blocked because there is an error in a dynamic-related computation.
*/
#define DYNAMIC_ERROR (1<<13)

/** 
   \brief Branch blocked state.

   The branch is blocked because we reached the maximum integration time.
*/
#define MAX_INT_TIME (1<<14)

/** 
   \brief Branch blocked state.

   The branch is blocked because the LQR optimal policy would take too long to reach the goal.
*/
#define MAX_OPT_TIME (1<<15)


/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Configuration of the branch extension.

   Parameters describing the operation of the
   \ref AddBranchToAtlasRRT function.

   These parameters are grouped in a struct just to
   clarify the code.
*/
typedef struct {
  unsigned int addMode;      /**< Samples to add during the brach extension: all, none, last. */
  unsigned int chartAddMode; /**< In problems with dynamics branches are often simulated and
				  there is no need to add the temporary charts to the atlas.
				  Therefore this can be add_all or add_none */
  boolean revisitCharts;     /**< TRUE if we the chart can enter previously defined charts (in the same tree).
				  FALSE to reduce the branch crossing effect. */
  boolean repeatCharts;      /**< TRUE if we the chart can enter charts already visited along the branch extension.
				  FALSE to reduce the branch crossing effect. */
  boolean checkCollisions;   /**< TRUE if collision stop the branch extension. */
  boolean onManifold;        /**< TRUE if the random sample is on the manifold (and not in
				  tangent bundle). */
  boolean explorationSample; /**< TRUE if we build an exploration branch: a branch towards the unkonwn.
				  FALSE if the branch tries to connect to another tree. */
  double maxLength;          /**< Maximum lenght for the branch. */
  double (*costF)(Tparameters*,boolean,double*,void*); /**< Cost function, if any. Only used for T-RRT. */
  void *costData;            /**< Data to sent to the cost function. */
  boolean dynamics;          /**< TRUE if the dynamics has to be taken into account. */
  double maxIntTime;         /**< Maximum integration time (only if dynamics is TRUE). */
  double currentMaxIntTime;  /**< When using LQR and relinearizing we can re-adjust the max integration
			          time several times along a branch. */
  double topt;               /**< Optimal time for LQR-based policies. */
  double maxTopt;            /**< Maximum optimal time. LQR policies reaching the goal with time larger
				  than this value are not considered. This is used to measure the 
				  advance toward goal: the time to goal should decrease as the
			          branch grows. */
  double tLastLinearization; /**< Time when we last linearized the system to compute the LQR policy. */
  boolean randLQRAction;     /**< TRUE when using LQR, but executing a random action. */
} TAtlasRRTBranchConfig;


/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Satus of the branch extension.

   Information related with the branch extensions process.

   These parameters are grouped in a struct just to
   clarify the code.
*/
typedef struct {
  boolean reachedGoal;    /**< TRUE if we managed to reach the goal. */
  boolean reachedQrand;   /**< TRUE if the random sample is reached. */
  boolean reachedTmpQrand;/**< TRUE if the intermediate random sample is reached.
			       This is the random sample projected to the current
			       chart. */

  unsigned int blocked;   /**< The branch is stopped for any reason (obstacles, singularities,...) */
  
  boolean validChart;     /**< TRUE if the current chart is valid.
			       FALSE if a new chart has to be generated at the current point. */

  unsigned int lastID;    /**< Identifier of the last sample added to the branch.
			     Initialized to i_near */

  unsigned int nCreatedCharts; /**< Number of transitions between charts so far. */

  unsigned int tree;      /**< Tree including the current branch. */

  double *deltaParam;     /**< Direction of advance in tangent space (normalized vector). */

  Tvector traversedCharts;/**< List of charts traversed by the branch. Used to avoid infinite loops. */

  double desiredLength;   /**< Desired length for the new branch. Distance to the initial Qrand
			     or maxLength, if given. */
  double maxLength;       /**< Maximum length of the branch. */
  double length;          /**< Branch lenght so far */
  double stepLength;      /**< Length of the last step in the branch. */

  double distQrand;       /**< Distance from current to rand sample (as given in the input). */

  double distGoal;        /**< Distance from current sample to goal. */

  double distOrigin;      /**< Distance form current sample to the root of the branch. */
  double maxDistOrigin;   /**< Maximum distance from the end to the start of the branch. */

  double delta;           /**< Current step size.*/

  double cost;            /**< Cost of the next node to be added to the branch. */

  double intTime;         /**< Integration time so far (only used in dynamic branches). */
  double h;               /**< Time in the last temptative step. */

  boolean chartInAtlas;   /**< TRUE if the current chart belongs to the atlas. FALSE if the
			       chart in the state is being used. */
  Tchart c;               /**< A temporary chart. Used when chartInAtlas is FALSE. */

} TAtlasRRTBranchState;

/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Information necessary when extending a tree in dynamic mode.

   In dynamic mode the trees are extended by simulating several actions
   and selecting the best one (the one closer to x_rand or to the goal),
   if any.

   This structure groups information and space used during the simulation
   of the several branches. It is grouped for convinience: allocate and
   deallocate it in block and pass less parameters to funcions like
   \ref AddBranchToAtlasDynamicRRT
*/
typedef struct {
  TSampleInfo *sample;                 /**< Sample at the end of each simulated action. */

  TAtlasRRTBranchState *state;         /**< State at the end of each action simulation. */

  double **action;                     /**< Current action. */
  double **qrandb;                     /**< Local qrand for each branch simulation. */

  double *dAction;                     /**< Distance to random point for each branch. */
  double **tr;                         /**< Space to project random samples. Only used
					    with T2G_METRIC. */

  unsigned int *nsReplay;              /**< Number of states in the branch. Used for replay. */
  double ***statesReplay;              /**< States in the branch. Used for replay. */
  boolean **newChartReplay;            /**< TRUE if a chart has to be created at the corresponding
					    state. Used for replay. */
  double **timeReplay;                 /**< Time lapse with respect to the previous state. Used for replay. */
  double **costReplay;                 /**< Transition from the previous state. Used for replay. */
} TDynamicBranches;

/**********************************************************************************************************/
/**********************************************************************************************************//**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Initializes a branch configuration.

   Initializes a branch configuration with one of the predefined pre-sets.

   Note that the particular algorithms may use one of the pre-sets and then
   adjust several of the fields at its convenience.

   \param mode The mode. See \ref EXTEND_RRT, \ref CONNECT_RRTs,
               \ref CONNECT_SAMPLES, \ref CONNECT_SAFE \ref SIMULATE_DYNAMICS
   \param config The branch configuration to initizlize.
*/
void InitBranchConfig(unsigned int mode,TAtlasRRTBranchConfig *config);


/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Initializes the branch state.

   Sets the values of the state structure to start a branch creation.

   \param pr The set of parameters.
   \param config The branch mode configuration.
   \param near The information of the nearest node (node to extend) from the RRT.
   \param randSample Ramdom sample guiding the expansion.
   \param goalSample Goal sample of the path planning process.
   \param ds Space for dynamic computations. Only required if a time2go metric is
             used (in problems with dynamics!). Otherwise it can be NULL.
   \param ar The AtlasRRT
   \param state The branch state structure to initialize.
*/
void InitBranchState(Tparameters *pr,TAtlasRRTBranchConfig *config,
		     TSampleInfo *near,double *randSample,double *goalSample,
		     TDynamicSpace *ds,
		     Tatlasrrt *ar,TAtlasRRTBranchState *state);

/** 
   \brief Tests if the branch can be continued.

   Tests if the branch can be further extended.

   \param dynamics TRUE if the problem has dynamic constratins.
   \param config The branch extension configuration.
   \param state The current branch state.

   \return TRUE if everything is ok and the branch can be further extended.
*/
boolean canContinueBranch(boolean dynamics,TAtlasRRTBranchConfig *config,TAtlasRRTBranchState *state);

/** 
   \brief Prints information about the blocked status.

   Prints the reason to stop a branch extension.

   If the branch is not blocked, nothing is printed.

   \param f The file where to write the information (typically stderr).
   \param prefix String to print before the information (typically white spaces used for indent).
   \param config Branch configuration.
   \param state The state with the information to print.
*/
void PrintBranchBlockedState(FILE *f,char *prefix,TAtlasRRTBranchConfig *config,TAtlasRRTBranchState *state);

/** 
   \brief Destructor.

   Releases the memory allocated by \ref InitBranchState but keeps all the
   information flags.

   \param state The structure to deallocate.
*/
void DeleteBranchState(TAtlasRRTBranchState *state);

/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Allocates space for the generation of dynamic branches.

   Allocates space for the generation of dynamic branches (one for each possible action).
   Such branches are simulated when extending RRTs on problems with dynamic constraints.

   \param pr The set of parameters.
   \param db The dinamic branch structure to initialize.
   \param ar The atlasRRT.
*/
void InitDynamicBranches(Tparameters *pr,TDynamicBranches *db,Tatlasrrt *ar);

/** 
   \brief Release memory.

   Releases the memory allocated wiht \ref InitDynamicBranches.

   \param db The dinamic branch structure to release.
   \param ar The atlasRRT.
*/
void DeleteDynamicBranches(TDynamicBranches *db,Tatlasrrt *ar);



/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief Initializes the space to hold a parametrized point.

   Allocates space for a parametrized point.

   \param m The dimension of the ambien space.
   \param k The dimension of the manifold.
   \param si The parametrized point to allocate.
*/
void InitSampleInfo(unsigned int m,unsigned int k,TSampleInfo *si);

/** 
   \brief Initializes a parametrized point from another parametrized point.

   Copy constructor.

   \param m The dimension of the ambien space.
   \param k The dimension of the manifold.
   \param si_dst The point to set. It is assumed to be initialzied.
   \param si_src The point from where to get the data.
*/
void SetSampleInfo(unsigned int m,unsigned int k,TSampleInfo *si_dst,TSampleInfo *si_src);

/** 
   \brief Sets the sample info to taking data from an AtlasRRT node.

   Copies the informaion of an AtlasRRT node.

   Note that this does not allocate space.

   \param n Index of the node to use in the initialization.
   \param ar The Atlas RRT.
   \param si The parametrized point to allocate.
*/
void SetSampleInfoFromNode(unsigned int n,Tatlasrrt *ar,TSampleInfo *si);

/** 
   \brief Deallocates a paramterized point.

   Destructor.

   \param si The parametrized point to deallocate.
*/
void DeleteSampleInfo(TSampleInfo *si);

/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/

/** 
   \brief New branch creation.

   To be called every time we start a new atlasRRT branch.

   In the context of RRT* this must be interpreted as the number of
   possible edges (number of sample pairs whose connections is
   attempted).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTBranch(TAtlasRRTStatistics *arst);

/** 
   \brief New dynamic extension.

   To be called every time we start a new extension to an atlasRRT branch.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTDynamicExtension(TAtlasRRTStatistics *arst);

/** 
   \brief New improved dynamic extensions.

   To be called every time a dynamic extension gets closer to
   the random sample (distance from the end of the branch
   to x_rand is smaller than the distance from x_near
   to x_rand).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTImprovedDynamicExtension(TAtlasRRTStatistics *arst);

/** 
   \brief New no empty branch.

   To be called every time we managed to add a non-emtpy branch
   to the AtlasRRT.

   In the context of RRT* this must be interpreted as the number of
   edges (number of sample pairs whose connections is
   valid).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoEmptyBranch(TAtlasRRTStatistics *arst);

/** 
   \brief New attempt to connect the two trees.

   New attempt to connect the two trees. This is only updated
   in bi-directional Atlas RRTs.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTTreeConnection(TAtlasRRTStatistics *arst);

/** 
   \brief New non-void attempt to connect the two trees.

   New attempt to connect the two trees that resulted in a
   non empty branch. This is only updated
   in bi-directional Atlas RRTs.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoEmptyTreeConnection(TAtlasRRTStatistics *arst);

/** 
   \brief New distance to x_rand.

   New distance from x_rand to the tree. These distances are
   accumulated and then we compute the average using the number
   of attempts for branch extension.

   \param dqr New tree-x_rand distance.
   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTDistanceQrand(double dqr,TAtlasRRTStatistics *arst);

/** 
   \brief New step in branch extension.

   To be called everytime we add a new step to a branch.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTStep(TAtlasRRTStatistics *arst);

/** 
   \brief Problems with convergence.

   To be called when we create a new chart due to
   convergence issues in the current chart.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoConvergentStep(TAtlasRRTStatistics *arst);

/** 
   \brief Random sample reached.

   To be called every time the random sample is reached.

   \param dqr Distance to x_rand when we considere it reached.
              This is only relevant in problems with dynamics
	      and using LQR as a steering method.
   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTQrandReached(double dqr,TAtlasRRTStatistics *arst);

/** 
   \brief New node not in the given domain.

   To be called everty time a branch is stopped since it
   leaves the given domain.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNotInDomain(TAtlasRRTStatistics *arst);

/** 
   \brief New collision.

   To be called every time a branch extension is stopped
   due to a collision.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTCollision(TAtlasRRTStatistics *arst);

/** 
   \brief New long branch.

   To be called every time a branch extension is stopped
   because the branch is already too long.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTTooLong(TAtlasRRTStatistics *arst);

/** 
   \brief New lack of advance direction.

   The advance direction can not be determined (the
   projection is too close to current sample).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoAdvanceDirection(TAtlasRRTStatistics *arst);
  
/** 
   \brief New lack of LQR policy.

   The LQR policy can not be computed safely

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoLQRPolicy(TAtlasRRTStatistics *arst);

/** 
   \brief New increment in LQR optimal time.

   The LQR policy is not applied since the optimal time increases.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTLQRToptIncreases(TAtlasRRTStatistics *arst);

/** 
   \brief New impossible situation.

   An impossible situation is detected.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTImpossible(TAtlasRRTStatistics *arst);
  
/** 
   \brief New replay error.

   A replay branch is stopped due to lack of data.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoReplay(TAtlasRRTStatistics *arst);
      
/** 
   \brief New large step.

   To be called every time a branch extension is stopped
   because the brach is scaping the ball defined
   with x_near, x_rand.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTTooFar(TAtlasRRTStatistics *arst);

/** 
   \brief New revisited chart.

   To be called every time a branch extension is stopped
   to avoid revisiting a previously existing chart.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTRevisitedChart(TAtlasRRTStatistics *arst);

/** 
   \brief New repeated chart.

   To be called every time a branch extension is stopped
   to avoid re-entering a chart already visited along the
   branch (aka repated chart).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTRepeatedChart(TAtlasRRTStatistics *arst);

/** 
   \brief New branch blocked at chart creation.

   To be called every time a branch extension is stopped
   after creating a chart. This typically happens when the
   projection of the random sample in the new chart is not
   giving a clear direction to advance (it is on the
   center of the new chart).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTChartBlocked(TAtlasRRTStatistics *arst);

/** 
   \brief New branch stopped due to time limits.

   To be called every time a branch extension is stopped
   when the integration time is reached.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTIntTimeReached(TAtlasRRTStatistics *arst);

/** 
   \brief New branch stopped for lack of valid action.

   To be called every time a branch extension is stopped
   when there is no valid action to keep on growing the
   branch. This may potentially happen when using the
   time2go metric.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTNoAction(TAtlasRRTStatistics *arst);

/** 
   \brief New action computation from an LQR policy.

   To be called every time compute the action to execute from a policy 
   computed using LQR.

   \param s Number of saturated actions.
   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTLQRPolicy(double s,TAtlasRRTStatistics *arst);

/** 
   \brief New LQR input executed.

   Collects statistics on whether or not the LQR actions
   are saturated. If so, the action cost (parameter
   \ref CT_TAU "TAU") must be increased.

   \param s The ratio of saturated actions (0=none 1=all).
   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTLQRinput(double s,TAtlasRRTStatistics *arst);

/** 
   \brief New LQR steer executed.

   Collects statistic on the value of the optimal time
   resulting from calling \ref LQRComputePolicy. 

   \param t The optimal time as determined by LQRComputePolicy.
   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTLQRComputePolicy(double t,TAtlasRRTStatistics *arst); 

/** 
   \brief New call to Broyden.

   For debugging purposes, se collect statistics on the number
   of iterations of the Broyden process. In this way we
   can compare different methods to compute the gradient
   (via nJacobian, via HandC, etc).

   \param it Number of iterations of the last call to Broyden
             (returned by \ref NextDynamicState).
   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTBroyden(unsigned int it,TAtlasRRTStatistics *arst);

/** 
   \brief The transition test failed.

   To be called every time the transition test fails
   and the branch extension is stopped.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTTransTestFail(TAtlasRRTStatistics *arst);

/** 
   \brief Error in the dynamic computations.

   To be called every time there is an error
   in the dynamics compuations.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTDynamicError(TAtlasRRTStatistics *arst);

/** 
   \brief New chart due to error when trying to create a chart.

   To be called every time the attempt to create a chart fails.
   This triggers the creation of a new chart in the precedent sample
   (where the chart was successfully created before).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTInitChartError(TAtlasRRTStatistics *arst);

/** 
   \brief New chart due to radius.

   To be called every time we create a new chart since  a node
   reached the border of the current chart (i.e., it leaves
   the ball defining the maximum chart validity area).

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTOutOfChart(TAtlasRRTStatistics *arst);

/** 
   \brief New chart due large curvature between two charts

   Called when there is a large curvature along a branch, and
   thus, a new chart has to be created.
   In this case the new chart has too large curvature error with
   respect to the current chart.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTLargeCurvature(TAtlasRRTStatistics *arst);

/** 
   \brief New chart due to the curvature in the expansion direction

   Called every time we create a new chart as it is the
   a cheap test that do not require the creation of temporary chart

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTDirLargeCurvature(TAtlasRRTStatistics *arst);

/** 
   \brief Step reduction.

   To be called everytime we have to reduce the default
   size between two nodes on a atlasRRT branch to be
   able to generate a valid new node.
   The default step size is given by the \ref CT_DELTA "DELTA"
   parameter.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTStepReduction(TAtlasRRTStatistics *arst);

/** 
   \brief New sample.

   To be called every time we actually add a node (or sample)
   to the atlasRRT.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTSample(TAtlasRRTStatistics *arst);

/** 
   \brief New repeated sample.

   To be called every time an RRT extension end up
   in repeated sample

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTRepeatedSample(TAtlasRRTStatistics *arst);

/** 
   \brief New Chart.

   To be called every time we actualy add a chart to the
   atlasRRT.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTChart(TAtlasRRTStatistics *arst);

/** 
   \brief A chart that does not intersect with its parent.

   When creating a new chart it should intersect with its
   parent chart. If this does not happen we have to
   record it.

   \param arst The statistics to update.
*/
void NewAtlasRRTNoConnectToParent(TAtlasRRTStatistics *arst);

/** 
   \brief Number of times we try to create a char at a singular regions.

   Number of times we try to create a char at a singular regions.

   Note that singularities are zero volume areas but due to the
   numerical tolerances they have some thickness and, thus,the
   probability of having points on this almost singular regions
   is not null.

   A point on a singularity blocks the extension of branches.
   If the number of times this happens is large, we
   could fail to solve a problem because we can not cross singular
   regions. A typical solution is to decrease parameter 'epsilon'.

   \param arst The AtlasRRT statistics to modify.
*/
void NewAtlasRRTBlockBySingularity(TAtlasRRTStatistics *arst);

/** 
   \brief New random sample.

   Counts the number of random samples generated.

   \param arst The statistics to update.
*/
void NewAtlasRRTRandomSample(TAtlasRRTStatistics *arst);

/** 
   \brief New sample rejection.

   Counts the number os random samples rejected.
   In particular the ones rejected directly at the generation
   process.

   \param arst The statistics to update.
*/
void NewAtlasRRTSampleRejection1(TAtlasRRTStatistics *arst);

/** 
   \brief New sample rejection.

   Counts the number os random samples rejected.
   In particular the ones rejected after the generation
   process (dynamic domain and alike).

   \param arst The statistics to update.
*/
void NewAtlasRRTSampleRejection2(TAtlasRRTStatistics *arst);

/** 
   \brief New sample rejection.

   Counts the number os random samples rejected.
   In particular the ones rejected because blocked nodes.
   This is a subset of those counted by \ref NewAtlasRRTSampleRejection2.

   \param arst The statistics to update.
*/
void NewAtlasRRTSampleRejection3(TAtlasRRTStatistics *arst);

/** 
   \brief New sample rejection.

   Counts the number os random samples rejected.
   In particular the ones rejected because the dynamic cone is not well
   oriented with the radom sample.
   This is a subset of those counted by \ref NewAtlasRRTSampleRejection2.

   \param arst The statistics to update.
*/
void NewAtlasRRTSampleRejection4(TAtlasRRTStatistics *arst);

/** 
   \brief New collision check.

   New collision check.

   \param arst The statistics to update.
*/
void NewAtlasRRTCollisionCheck(TAtlasRRTStatistics *arst);
 
/** 
   \brief Number of neighbours per chart.

   This is used to store the average number of neighbours for each charts
   after the generation of an atlasrrt (after planning).

   \param an The average number of neighbours.
   \param arst The statistics to update.
*/
void NewAverageNumNeighbours(double an,TAtlasRRTStatistics *arst);

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void InitAtlasRRTStatistics(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL)
    {
      arst->n=0;

      arst->nBranch=0;
      arst->nNoEmptyBranch=0;

      arst->nDynamicExtension=0;
      arst->nImprovedDynamicExtension=0;

      arst->nTreeConnection=0;
      arst->nNoEmptyTreeConnection=0;

      arst->nStep=0;
      arst->dQrand=0.0;

      arst->nQrandReached=0;
      arst->dQrandReached=0.0;
      arst->nNotInDomain=0;
      arst->nCollision=0;
      arst->nTooFar=0;
      arst->nTooLong=0;
      arst->nRevisitedChart=0;
      arst->nRepeatedChart=0;
      arst->nChartBlocked=0;
      arst->nIntTimeReached=0;
      arst->nNoDir=0;
      arst->nNoPolicy=0;
      arst->nToptIncrements=0;
      arst->nImpossible=0;
      arst->nNoReplay=0;

      arst->satAction=0.0;
      arst->nLQRPolicy=0;

      arst->topt=0.0;
      arst->nLQRComputePolicy=0;

      arst->nB=0;
      arst->itB=0;
      
      arst->nNoAction=0;
      arst->nTransTestFailed=0;
      arst->nDynamicErrors=0;

      arst->nErrorNewChart=0;
      arst->nNoConvergent=0;
      arst->nOutOfChart=0;
      arst->nLargeCurvature=0;
      arst->nDirLargeCurvature=0;

      arst->nStepReduction=0;

      arst->nSample=0;
      arst->nRepeatedSample=0;
      arst->nChart=0;
      arst->nNoConnect=0;
      arst->nSingular=0;

      arst->nRandom=0;
      arst->nRejections1=0;
      arst->nRejections2=0;
      arst->nRejections3=0;
      arst->nRejections4=0;

      arst->nCollisionChecks=0;

      arst->nAverageNeighbours=0.0;
    }
}

void NewAtlasRRTBranch(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nBranch++;
}

void NewAtlasRRTDynamicExtension(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nDynamicExtension++;
}

void NewAtlasRRTImprovedDynamicExtension(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nImprovedDynamicExtension++;
}

void NewAtlasRRTNoEmptyBranch(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoEmptyBranch++;
}

void NewAtlasRRTTreeConnection(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nTreeConnection++;
}

void NewAtlasRRTNoEmptyTreeConnection(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoEmptyTreeConnection++;
}

void NewAtlasRRTDistanceQrand(double dqr,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->dQrand+=dqr;
}

void NewAtlasRRTStep(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nStep++;
}

void NewAtlasRRTNoConvergentStep(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoConvergent++;
}

void NewAtlasRRTQrandReached(double dqr,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL)
    {
      arst->nQrandReached++;
      arst->dQrandReached+=dqr;
    }
}

void NewAtlasRRTNotInDomain(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNotInDomain++;
}

void NewAtlasRRTCollision(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nCollision++;
}

void NewAtlasRRTTooLong(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nTooLong++;
}

void NewAtlasRRTNoAdvanceDirection(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoDir++;
}

void NewAtlasRRTNoLQRPolicy(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoPolicy++;
}

void NewAtlasRRTLQRToptIncreases(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nToptIncrements++;
}

void NewAtlasRRTImpossible(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nImpossible++;
}

void NewAtlasRRTNoReplay(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoReplay++;
}

void NewAtlasRRTTooFar(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nTooFar++;
}

void NewAtlasRRTRevisitedChart(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRevisitedChart++;
}

void NewAtlasRRTRepeatedChart(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRepeatedChart++;
}

void NewAtlasRRTChartBlocked(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nChartBlocked++;
}

void NewAtlasRRTIntTimeReached(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nIntTimeReached++;
}

void NewAtlasRRTNoAction(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoAction++;
}

void NewAtlasRRTLQRPolicy(double s,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL)
    {
      arst->satAction+=s;
      arst->nLQRPolicy++;
    }
}

void NewAtlasRRTLQRComputePolicy(double t,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL)
    {
      arst->topt+=t;
      arst->nLQRComputePolicy++;
    }
}

void NewAtlasRRTBroyden(unsigned int it,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL)
    {
      arst->nB++;
      arst->itB+=it;
    } 
}
  
void NewAtlasRRTTransTestFail(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nTransTestFailed++;
}

void NewAtlasRRTDynamicError(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nDynamicErrors++;
}

void NewAtlasRRTOutOfChart(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nOutOfChart++;
}

void NewAtlasRRTInitChartError(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nErrorNewChart++;
}

void NewAtlasRRTLargeCurvature(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nLargeCurvature++;
}

void NewAtlasRRTDirLargeCurvature(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nDirLargeCurvature++;
}

void NewAtlasRRTStepReduction(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nStepReduction++;
}

void NewAtlasRRTSample(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nSample++;
}

void NewAtlasRRTRepeatedSample(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRepeatedSample++;
}

void NewAtlasRRTChart(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nChart++;
}

void NewAtlasRRTNoConnectToParent(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nNoConnect++;
}

void NewAtlasRRTBlockBySingularity(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nSingular++;
}

void NewAtlasRRTRandomSample(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRandom++;
}

void NewAtlasRRTSampleRejection1(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRejections1++;
}

void NewAtlasRRTSampleRejection2(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRejections2++;
}

void NewAtlasRRTSampleRejection3(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRejections3++;
}

void NewAtlasRRTSampleRejection4(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nRejections4++;
}

void NewAtlasRRTCollisionCheck(TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nCollisionChecks++;
}

void NewAverageNumNeighbours(double an,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL) arst->nAverageNeighbours+=an;
}

void AccumulateAtlasRRTStatistics(TAtlasRRTStatistics *arst1,TAtlasRRTStatistics *arst2)
{
  if ((arst1!=NULL)&&(arst2!=NULL))
    {
      if (arst1->n==0)
	arst2->n++;
      else
	arst2->n+=arst1->n;

      arst2->nBranch+=arst1->nBranch;
      arst2->nNoEmptyBranch+=arst1->nNoEmptyBranch;

      arst2->nDynamicExtension+=arst1->nDynamicExtension;
      arst2->nImprovedDynamicExtension+=arst1->nImprovedDynamicExtension;

      arst2->nTreeConnection+=arst1->nTreeConnection;
      arst2->nNoEmptyTreeConnection+=arst1->nNoEmptyTreeConnection;

      arst2->nStep+=arst1->nStep;
      arst2->dQrand+=arst1->dQrand;

      arst2->nQrandReached+=arst1->nQrandReached;
      arst2->dQrandReached+=arst1->dQrandReached;
      arst2->nNotInDomain+=arst1->nNotInDomain;
      arst2->nCollision+=arst1->nCollision;
      arst2->nTooLong+=arst1->nTooLong;
      arst2->nTooFar+=arst1->nTooFar;
      arst2->nRevisitedChart+=arst1->nRevisitedChart;
      arst2->nRepeatedChart+=arst1->nRepeatedChart;
      arst2->nChartBlocked+=arst1->nChartBlocked;
      arst2->nIntTimeReached+=arst1->nIntTimeReached;
      arst2->nNoDir+=arst1->nNoDir;
      arst2->nNoPolicy+=arst1->nNoPolicy;
      arst2->nToptIncrements+=arst1->nToptIncrements;
      arst2->nImpossible+=arst1->nImpossible;
      arst2->nNoReplay+=arst1->nNoReplay;

      arst2->satAction+=arst1->satAction;
      arst2->nLQRPolicy+=arst1->nLQRPolicy;
 
      arst2->topt+=arst1->topt;
      arst2->nLQRComputePolicy+=arst1->nLQRComputePolicy;

      arst2->nB+=arst1->nB;
      arst2->itB+=arst1->itB;
      
      arst2->nNoAction+=arst1->nNoAction;
      arst2->nTransTestFailed+=arst1->nTransTestFailed;
      arst2->nDynamicErrors+=arst1->nDynamicErrors;

      arst2->nErrorNewChart+=arst1->nErrorNewChart;
      arst2->nNoConvergent+=arst1->nNoConvergent;
      arst2->nOutOfChart+=arst1->nOutOfChart;
      arst2->nLargeCurvature+=arst1->nLargeCurvature;
      arst2->nDirLargeCurvature+=arst1->nDirLargeCurvature;

      arst2->nStepReduction+=arst1->nStepReduction;

      arst2->nSample+=arst1->nSample;
      arst2->nRepeatedSample+=arst1->nRepeatedSample;
      arst2->nChart+=arst1->nChart;

      arst2->nNoConnect+=arst1->nNoConnect;
      arst2->nSingular+=arst1->nSingular;

      arst2->nRandom+=arst1->nRandom;
      arst2->nRejections1+=arst1->nRejections1;
      arst2->nRejections2+=arst1->nRejections2;
      arst2->nRejections3+=arst1->nRejections3;
      arst2->nRejections4+=arst1->nRejections4;

      arst2->nCollisionChecks+=arst1->nCollisionChecks;

      arst2->nAverageNeighbours+=arst1->nAverageNeighbours;
    }
}

void PrintAtlasRRTStatistics(Tatlasrrt *ar,TAtlasRRTStatistics *arst)
{
  if (arst!=NULL)
    {
      unsigned int m,nExt,nNoEmptyExt;

      if (arst->n==0)
	arst->n=1;

      nExt=arst->nBranch+arst->nTreeConnection;
      nNoEmptyExt=(arst->nNoEmptyBranch+arst->nNoEmptyTreeConnection);

      fprintf(stderr,"%% **************************************************\n");
      if (arst->n>1)
	fprintf(stderr,"AtlasRRT Statistics (averaged over %u repetitions)\n",arst->n);
      else
	fprintf(stderr,"AtlasRRT Statistics\n\n");
      if (arst->nRandom>0)
	{
	  fprintf(stderr,"  Num. random samples             : %.2f\n",
		  (double)arst->nRandom/(double)arst->n);
	  fprintf(stderr,"  Out of chart borders            : %.2f (%.2f)\n",
		  (double)arst->nRejections1/(double)arst->n,
		  (double)arst->nRejections1/(double)arst->nRandom);
	  fprintf(stderr,"  Not valid samples               : %.2f (%.2f)\n",
		  (double)arst->nRejections2/(double)arst->n,
		  (double)arst->nRejections2/(double)arst->nRandom);
	  fprintf(stderr,"  Blocked near nodes              : %.2f (%.2f)\n",
		  (double)arst->nRejections3/(double)arst->n,
		  (double)arst->nRejections3/(double)arst->nRandom);
	  fprintf(stderr,"  Missaligned with dynamic cones  : %.2f (%.2f)\n",
		  (double)arst->nRejections4/(double)arst->n,
		  (double)arst->nRejections4/(double)arst->nRandom);
	  fprintf(stderr,"  Num. accepted random samples    : %.2f (%.2f)\n",
		  (double)(arst->nRandom-arst->nRejections1-arst->nRejections2)/(double)arst->n,
		  (double)(arst->nRandom-arst->nRejections1-arst->nRejections2)/(double)arst->nRandom);

	  
          /* if the chart sampling radius is potentially different for each chart
	     we print information about the extreme/average chart sampling radius. */
          #if (ADJUST_SA==1)
	    if ((arst->n==1)&&(ar!=NULL))
	      {
		unsigned int i;
		double miSr,maSr,avSr,sr;

		miSr=+INF;
		maSr=-INF;
		avSr=0.0;
		for(i=0;i<ar->nc;i++)
		  {
		    sr=GetChartSamplingRadius(GetAtlasChart(i,&(ar->atlas)));
		    if (sr<miSr)
		      miSr=sr;
		    if (sr>maSr)
		      maSr=sr;
		    avSr+=sr;
		  }
		fprintf(stderr,"  Sampling radius info            : %.2f <-- %.2f --> %.2f\n",
			miSr,avSr/(double)ar->nc,maSr);
	      }
          #endif
	}
	
      if ((arst->n==1)&&(ar!=NULL)&&(DynamicDomainRRT(&(ar->rrt))))
	{
	  unsigned int i,n;
	  double miDD,maDD,avDD,r;

	  miDD=+INF;
	  maDD=-INF;
	  avDD=0.0;
	  n=0;
	  for(i=0;i<ar->ns;i++)
	    {
	      r=GetDynamicDomainRadius(i,&(ar->rrt));
	      if (r>0)
		{
		  if (r<miDD)
		    miDD=r;
		  if (r>maDD)
		    maDD=r;
		  avDD+=r;
		  n++;
		}
	    }
	  if (n==0)
	    fprintf(stderr,"  No dynamic domain effect.");
	  else
	    fprintf(stderr,"  Dynamic domain radius           : %.2f <-- %.2f --> %.2f (%u/%u)\n",
		    miDD,avDD/(double)n,maDD,n,ar->ns);
	}
      
      if (arst->nBranch>0)
	{
	  fprintf(stderr,"  Average  distance to Qrand      : %.2f\n",
		  arst->dQrand/(double)arst->nBranch);
	  
	  fprintf(stderr,"  Num. direct RRT extensions      : %.2f\n",
		  (double)arst->nBranch/(double)arst->n);
	  m=arst->nNoEmptyBranch;
	  fprintf(stderr,"  Num. no-empty direct extensions : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nBranch);

	  fprintf(stderr,"  Num. RRT connections            : %.2f\n",
		  (double)arst->nTreeConnection/(double)arst->n);
	  m=arst->nNoEmptyTreeConnection;
	  fprintf(stderr,"  Num. no-empty RRT connections   : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nTreeConnection);

	  fprintf(stderr,"  Total branches                  : %.2f\n",
		  (double)nExt/(double)arst->n);

	  m=nExt-(arst->nNoEmptyBranch+arst->nNoEmptyTreeConnection);
	  fprintf(stderr,"  Total empty branches            : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=(arst->nNoEmptyBranch+arst->nNoEmptyTreeConnection);
	  fprintf(stderr,"  Total no-empty branches         : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  //nExt=m;
	}
      
      if (arst->nDynamicExtension>0)
	{
	  m=arst->nDynamicExtension;
	  fprintf(stderr,"  Dynamic extensions              : %.2f\n",
		  (double)m/(double)arst->n);
	  
	  m=arst->nImprovedDynamicExtension;
	  fprintf(stderr,"    Improved extensions           : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nDynamicExtension);
	  
	  m=arst->nIntTimeReached;
	  fprintf(stderr,"    Integration time reached      : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nDynamicExtension);
	  
	  m=arst->nRepeatedSample;
	  fprintf(stderr,"    Blocked at repeated sample    : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nDynamicExtension);
	  
	  if (arst->nLQRPolicy>0)
	    fprintf(stderr,"    Saturated actions             : %.2f\n",
		    arst->satAction/(double)arst->nLQRPolicy);
	  
	  fprintf(stderr,"    Computed LQR policies         : %.2f (%.2f)\n",
		  (double)arst->nLQRComputePolicy/(double)arst->n,
		  1.0-(double)arst->nToptIncrements/(double)arst->nLQRComputePolicy);
	  
	  if (arst->nLQRComputePolicy>0)
	    fprintf(stderr,"    Optimal time                  : %.2f\n",
		    arst->topt/(double)arst->nLQRComputePolicy);
	  
	}
      
      if ((nExt>0)&&((ar==NULL)||(!ar->dynamics)||(!ar->parallel)))
	{
	  /* When ar->dynamics and ar->parallel, some statistics are
	     not collected (due to the reply mode) */
	  fprintf(stderr,"  Reasons to stop the branch/connection:\n");
	  
	  m=arst->nNoAction;
	  fprintf(stderr,"    No good action                : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  m=arst->nQrandReached;
	  fprintf(stderr,"    y_rand reached                : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  if (arst->nDynamicExtension>0)
	    {
	      /* These only happens with dynamics  */
	      if (m>0)
		fprintf(stderr,"    Distance to y_rand reached    : %.2f\n",
			arst->dQrandReached/(double)m);
	      
	      m=arst->nNoReplay;
	      fprintf(stderr,"    Error in replay               : %.2f (%.2f)\n",
		      (double)m/(double)arst->n,
		      (double)m/(double)nExt);
	      
	      m=arst->nNoPolicy;
	      fprintf(stderr,"    No LQR policy                 : %.2f (%.2f)\n",
		      (double)m/(double)arst->n,
		      (double)m/(double)nExt);
	      
	      m=arst->nToptIncrements;
	      fprintf(stderr,"    Topt increments               : %.2f (%.2f)\n",
		      (double)m/(double)arst->n,
		      (double)m/(double)nExt);
	    }
	  
	  m=arst->nNotInDomain;
	  fprintf(stderr,"    Out of domain                 : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=arst->nCollision;
	  fprintf(stderr,"    Collision                     : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=arst->nTooLong;
	  fprintf(stderr,"    Long branch                   : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=arst->nTooFar;
	  fprintf(stderr,"    Too far from x_near           : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=arst->nRevisitedChart;
	  fprintf(stderr,"    Avoid revisiting charts       : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  m=arst->nRepeatedChart;
	  fprintf(stderr,"    Avoid repeating charts        : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=arst->nChartBlocked;
	  fprintf(stderr,"    Blocked in chart creation     : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  m=arst->nSingular;
	  fprintf(stderr,"    Singularity                   : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  m=arst->nImpossible;
	  fprintf(stderr,"    Impossible cases              : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  m=arst->nDynamicErrors;
	  fprintf(stderr,"    Dynamic error                 : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);

	  m=arst->nTransTestFailed;
	  fprintf(stderr,"    Transtion test failed         : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	  
	  m=arst->nNoDir;
	  fprintf(stderr,"    No advance direction          : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)nExt);
	}

      if (arst->nB>0)
	fprintf(stderr,"  Broyden iterations              : %.2f\n",
		(double)arst->itB/(double)arst->nB);
      
      fprintf(stderr,"  Num. extension steps            : %.2f\n",
	      (double)arst->nStep/(double)arst->n);
      if (nExt>0)
	fprintf(stderr,"    Num. steps per branch         : %.2f\n",
		(double)arst->nStep/(double)nExt);
      /* When ar->dynamics and ar->parallel, some statistics are
	 not collected (due to the reply mode) */
      if ((ar==NULL)||(!ar->dynamics)||(!ar->parallel))
	  fprintf(stderr,"    Num. step reductions          : %.2f\n",
		  (double)arst->nStepReduction/(double)arst->n);
      else
	  fprintf(stderr,"    Num. steps per dynamic branch : %.2f\n",
		  (double)arst->nStep/(double)arst->nDynamicExtension);

      fprintf(stderr,"  Num. collision checks           : %.2f\n",
	      (double)arst->nCollisionChecks/(double)arst->n);

      fprintf(stderr,"  Num. samples in (bi)RRT         : %.2f\n",
	      (double)arst->nSample/(double)arst->n);
      if (nNoEmptyExt>0)
	fprintf(stderr,"    Samples per non-empty extens. : %.2f\n",
		(double)arst->nSample/(double)nNoEmptyExt);

      fprintf(stderr,"  Num. charts                     : %.2f\n",
	      (double)arst->nChart/(double)arst->n);

      if ((ar==NULL)||(!ar->dynamics)||(!ar->parallel))
	{
	  /* When ar->dynamics and ar->parallel, some statistics are
	     not collected (due to the reply mode) */
	  fprintf(stderr,"  Reasons to create charts\n");

	  m=arst->nErrorNewChart;
	  fprintf(stderr,"    Error defining chart          : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nChart);

	  m=arst->nOutOfChart;
	  fprintf(stderr,"    Out of radius                 : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nChart);

	  m=arst->nNoConvergent;
	  fprintf(stderr,"    Large or convergence error    : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nChart);

	  #if (GET_ATLASRRT_GLOBAL_CURV_CHECK)
	    m=arst->nLargeCurvature;
	    fprintf(stderr,"    Curvature error               : %.2f (%.2f)\n",
		    (double)m/(double)arst->n,
		    (double)m/(double)arst->nChart);
	  #endif

	  m=arst->nDirLargeCurvature;
	  fprintf(stderr,"    Directional curvature error   : %.2f (%.2f)\n",
		  (double)m/(double)arst->n,
		  (double)m/(double)arst->nChart);
	}
      
      m=arst->nNoConnect;
      fprintf(stderr,"  Num. no-intersect with parent   : %.2f (%.2f)\n",
	      (double)m/(double)arst->n,
	      (double)m/(double)arst->nChart);

      fprintf(stderr,"  Samples per chart               : %.2f\n",
	      (double)arst->nSample/(double)arst->nChart);
      
      fprintf(stderr,"  Neighbours per chart            : %.2f\n",
	      (double)arst->nAverageNeighbours/(double)arst->n);
    }
}

void DeleteAtlasRRTStatistics(TAtlasRRTStatistics *arst)
{
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/** 
   \brief Recomputes the LQR policy.

   Recomputes the LQR policy.

   \param pr The set of parameters.
   \param config The branch configuration.
   \param c_lqr The chart where to compute the policy.
   \param t_near The parameters of the start point in the chart.
   \param t_rand The parameters of the goal point in the chart.
   \param state The branch state.
   \param st The statistics, if any.
   \param ds The dynamics space to use.
   \param ar Tha atlas rrt structure.
*/
void UpdateLQRPolicy(Tparameters *pr,TAtlasRRTBranchConfig *config,
		     Tchart *c_lqr,double *t_near,double *t_rand,
		     TAtlasRRTBranchState *state,void *st,
		     TDynamicSpace *ds,Tatlasrrt *ar);

/** 
   \brief Adds a new branch to the AtlasRRT.

   Add a new branch to the AtlasRRT. The branch is extened until the given
   goal is reached or until a problem in the extension occurs (obstacles,
   convergence problems, singularities, etc.).

   Note that this function is also used to check if a given sample can be
   connected to the tree but without actually adding a branch to the tree.
   In this case, though the charts necessaries to connect the tree and
   the given sample are generated if not ye defined (i.e., while we do not
   add samples we might add charts. This extension-without-addition
   is basically used for RRT*.

   \param pr The set of parametes.
   \param it The current iteration.
   \param config Configuration defining the brach extension mode.
                 See \ref TAtlasRRTBranchConfig.
   \param nsReplay Number of steps in the replay sequence.
   \param replayPath If not NULL, new samples are not computed on the fly but
                     taken from this vector. This is useful to replicate
		     replabranch extensions previously simulated.
   \param replayNewChart If not NULL indicates the steps in the branch replay
                         where to create a new chart. This is only used if
			 \e replayPath is also not NULL.
			 CAUTION: This information is destroyed when replaying
			 the trajectory and, thus the same trajectory can not
			 be replayed twice. Make a copy of it, if necessary.
   \param replayTime If not NULL gives the time lapse for each element in
                     \e replayPath with respect to the previous step.
   \param replayCost If not NULL gives the transition cost for each element in
                     \e replayPath with respect to the previous step.
   \param action Action to execute (only used in dynamic systems).
   \param i_near Identifier of the node in the AtlasRRT from where to
                 extend the branch.
   \param randSample The radom sample to reach (or at least to aim at).
   \param goalSample The goal sample of the path planning problem.
   \param st Structure to collect statistics about the path planning
             process.
   \param state State of the branch extension. Used to return
                information to the caller. Please see \ref TAtlasRRTBranchState.
   \param ns Number of samples in the branch. Only updated if different from NULL.
   \param path Samples along the path between the two given points. Only used
               if different from NULL. This is typically used to recover paths on
	       trees. In this case we do not want to store the nodes in the
	       tree (i.e. addMode is ADD_NONE) but to retrive them.
	       This can also be used as paramter \e replayPath to reproduce
	       branches.
   \param newChart Arraly of flags indicating at which step in the \e path a new
                   chart is created. Only set if it is different from NULL.
		   This is used later on to reproduce branches, i.e.,
		   it is used as parameter \e replayNewChart.
   \param tStep Time lapse from the previous step. This can be used as input
                \e replayTime.
   \param cStep Cost of the step. This can be used as input \e replayCost.
   \param lastSample Buffer to store the last sample along the branch.
                     NULL if the last sample is not relevant to the caller.
   \param ds Space for dynamic computations. Only required in problems with
             dynamics. Otherwise it can be NULL.
   \param ar The AtlasRRT to extend.

   \return The branch length if the random sample is reached and INF otherwise.
*/
double AddBranchToAtlasRRT(Tparameters *pr,unsigned int it,TAtlasRRTBranchConfig *config,
			   unsigned int nsReplay,double **replayPath,boolean *replayNewChart,double *replayTime,double *replayCost,
			   double *action,
			   unsigned int i_near,double *randSample,double *goalSample,
			   void *st,TAtlasRRTBranchState *state,
			   unsigned int *ns,double ***path,boolean **newChart,double **tStep,double **cStep,
			   TSampleInfo *lastSample,TDynamicSpace *ds,
			   Tatlasrrt *ar);

/** 
   \brief Adds a new branch to the AtlasRRT for problems with dynamics.

   Variant of \ref AddBranchToAtlasRRT for dynamical systems. Here instead
   of growing just one branch we grow a branch for each different acion
   and keep the one that is closer to x_rand

   \param pr The set of parametes.
   \param oneAction If not 0, only one action (selected at random or
                    with any available complex method) is used
		    to extend the RRT. There is no simulation of
		    alternative actions. It basically makes sense
		    with Time2Go metric.
   \param t2g If set (not 0) the Time2Go metric is used.
   \param it The current iteration.
   \param config Configuration defining the brach extension mode.
                 See \ref TAtlasRRTBranchConfig.
   \param i_near Identifier of the node in the AtlasRRT from where to
                 extend the branch.
   \param randSample The radom sample to reach (or at least to aim at).
   \param goalSample The goal sample of the path planning problem.
   \param st Structure to collect statistics about the path planning
             process.
   \param db Space for the simulatin of the different actions, one
             for each valid action. See \ref InitDynamicBranches
   \param lastSample Identifer of the last sample added to the branh.
   \param reachedGoal TRUE if the goal is eventually reached.
   \param ar The AtlasRRT to extend.

   \return The length of the adde branch or 0 if no action is good enough.
*/
double AddBranchToAtlasDynamicRRT(Tparameters *pr,
				  unsigned int oneAction,unsigned int t2g,
				  unsigned int it,TAtlasRRTBranchConfig *config,
				  unsigned int i_near,double *randSample,double *goalSample,
				  void *st,TDynamicBranches *db,unsigned int *lastSample,
				  boolean *reachedGoal,Tatlasrrt *ar);

/** 
   \brief Generates a new sample in between x_near and x_rand.

   Generates a new sample interpolating in between x_near and x_rand
   and projecting to the manifold.

   This is used to extend a AtlasRRT branch.

   This function consideres the possible transition to a neighbouring chart
   of the new sample. If this transition occurs, the random point is also
   translated to the new chart.

   \param pr The set of parameters.
   \param it Current iteration. Used to stop the branch extension if we enter
             in an existing chart from a just created one.
   \param config The branch extension configuration.
   \param state The branch extension state.
   \param current The current point along the branch.
   \param action Action to execute (only used in dynamical systems).
   \param next The temptative next point to generate.
   \param rand The random point we are aiming at.
   \param randSample The random sample (as given in the input of the branch extnsion).
   \param st Statistics about chart construction.
   \param ds Space for dynamic computations. Only required in problems with
             dynamics. Otherwise it can be NULL.
   \param ar The atlas RRT.
*/
void NewTemptativeSample(Tparameters *pr,unsigned int it,
			 TAtlasRRTBranchConfig *config,
			 TAtlasRRTBranchState *state,
			 TSampleInfo *current,double *action,TSampleInfo *next,
			 TSampleInfo *rand,double *randSample,
			 void * st,TDynamicSpace *ds,Tatlasrrt *ar);

/** 
   \brief Adds a sample to the AtlasRRT.

   Adds a sample to the AtlasRRT connected to a given sample already in the
   tree.

   \param pr The set of parameteres.
   \param tree In which tree (\ref START2GOAL or \ref GOAL2START) to insert
               the sample.
	       Only considered if the altasRRT is bidirectional.
   \param currentID Identifier of the current sample. Parent of the sample
                    to add.
   \param nextChart Chart for the new sample.
   \param nextParam Parameters in the chart of the sample to add.
   \param nextSample Sample to add.
   \param dp Distance to parent sample.
   \param cost Cost for this node. This can be different thinks: the cost
               of the node evaluated with a user-given funcion (in TRRT) or the
	       distance from the root of the tree (in RRT*)
   \param blocked TRUE for nodes close to domain borders or obstacles. Can be used
                  later on to minimize expansions from this nodes.
   \param action Action executed to reach the node (only used in dynamical systems).
   \param time Time necessary to reach the node (only used in dynamical systems).
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
   \param ar The AtlasRRT.

   \return Distance from the new sample to its parent.
*/
double AddSample2AtlasRRT(Tparameters *pr,unsigned int tree,
			  unsigned int *currentID,
			  unsigned int nextChart,double *nextParam,double *nextSample,
			  double dp,double cost,boolean blocked,double *action,double time,
			  unsigned int ns,double **path,double **actions,double *times,
			  Tatlasrrt *ar);

/** 
   \brief Adds a chart to the Atlas RRT.

   Used when a sample triggers the generation of a new chart.

   We can generate a chart on:
   - A sample already added to the RRT: The currentSampleInfo.id gives
   the identifier of this sample and currentSampleInfo is a pointer
   to the node in the tree.
   - A cophy of a sample already added to the RRT: The currentSampleInfo.id gives
   the identifier of this sample and currentSampleInfo is a pointer
   to the copy of the node in the tree.
   - A temporary sample not in the RRT: currentSampleInfo.id is NO_UINT.
   .

   \param pr The set of parameters.
   \param tree The identifier of the tree to which the sample belongs.
   \param it Current iteration. Used to timestamp the charts.
   \param config The branch configuration. Can be NULL if not given.
   \param state The branch state. Can be NULL if not given.
   \param currentSampleInfo Information relative to the sample from where to
                            generate the next sample.
   \param intersectParent (Output) TRUE if the added chart intersects
                          with its parent. Used for debug.
   \param ar The AtlasRRT.

   \return TRUE if the chart can actually be generated. If not, it is
           most likely because the given point is at a (almost)
	   singular region.
*/
boolean AddChart2AtlasRRT(Tparameters *pr,unsigned int tree,unsigned int it,
			  TAtlasRRTBranchConfig *config,TAtlasRRTBranchState *state,
			  TSampleInfo *currentSampleInfo,
			  boolean *intersectParent,Tatlasrrt *ar);

/** 
   \brief Assign samples to a newly created chart.

   After generating a new chart (with identifier \e id) some of the
   samples assigned to their neighbours have to be assigned to the new
   chart.

   \param pr The set of parameters.
   \param id Identifier of the new chart.
   \param ar The atlasRRT.
*/
void PopulateWithSamples(Tparameters *pr,unsigned int id,Tatlasrrt *ar);

/** 
   \brief Add a chart to a tree

   Add a visited chart to the list of chart reached by a given tree. This is
   used to select charts when sampling.
   We avoid storing the same chart twice to avoid bias in the sampling.

   \param tree The identidier for the tree.
   \param chartId The identifier for the chart.
   \param ar The AtlasRRT.
*/
void AddChart2Tree(unsigned int tree,unsigned int chartId,Tatlasrrt* ar);


/** 
   \brief Determines the motion on the current chart to approach x_rand.

   Determines a unitary vector on the current chart that points towards
   the random sample. Additionally, project the random sample to the
   current chart.

   \param config The configuration determining how the branch has to be extended.
   \param samplingMode The sampling mode (AMBIENT, KDTREE, TANGENT).
   \param randSample The (original) random sample.
   \param state The current state of the branch extension.
   \param current The current sample.
   \param rand The random sample.
   \param ar The atlasrrt.
*/
boolean PointTowardRandSample(TAtlasRRTBranchConfig *config,
			      unsigned int samplingMode,double *randSample,
			      TAtlasRRTBranchState *state,
			      TSampleInfo *current,TSampleInfo *rand,Tatlasrrt *ar);

/** 
   \brief Collects samples from the tree root to a given sample.

   Reconstruct the path from the tree root to the sample in the tree
   closer to the goal.
   This is typically used to get the  targed is reached.

   \param pr The set of parameters.
   \param sID Sample to connect to the root of the tree.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of samples in the output path.
   \param path The output path.
   \param ar The AtlasRRT structure to query.

   \return The size of each path step (system variables stored for each step).
*/
unsigned int ReconstructAtlasRRTPath(Tparameters *pr,unsigned int sID,
				     double *pl,unsigned int *ns,
				     double ***path,Tatlasrrt *ar);

/** 
   \brief Defines a path from a vector of steps.

   Defines a path (a collection of close enough samples) from a set
   of steps defined as nodes in a AtlasRRT.

   \param pr The set of parameters.
   \param steps The vector of steps to follow.
   \param pl The length of the output path, if any. If no path is found.
             this is undefined.
   \param pc The cost of the output path, if any. If no path is found.
             this is undefined.
   \param ns Number of samples in the output path.
   \param path The output path.
   \param ar The AtalsRRT structure to query.

   \return The size of each path step (system variables stored for each step).
*/
unsigned int Steps2PathinAtlasRRT(Tparameters *pr,Tvector *steps,double *pl,double* pc,
				  unsigned int *ns,double ***path,Tatlasrrt *ar);

/** 
   \brief Local optimiziation of the path to a node.

   Local optimiziation of the length of the path to a node.
   Tries to re-wire the tree to minimize the path from the root
   to a given node.

   \param pr The set of parameters.
   \param sID The node.
   \param ar The atlasRRT.
*/
void SmoothPathInAtlasRRT(Tparameters *pr,unsigned int sID,Tatlasrrt* ar);

/** 
   \brief Adds a node to an AtlasRRT*.

   Tries to generate a node from i_near toward x_rand and, if possible, adds
   it to the AtlasRRT and updates the cost of the new node.
   Moreover, we check if the goal is actually reached.
   If so, we add another node to the tree representing the goal.

   \param pr The set of parameters.
   \param it Current iteration.
   \param expand2Goal TRUE if x_rand is actually the goal.
   \param onManifold TRUE if the sample is on the manifold.
   \param i_near Node from which to expand.
   \param x_rand Targed for the expansion.
   \param id_goal Identifier of the goal sample, if any. Otherwise NO_UINT.
                  Only used if goal is not NULL.
   \param goal The goal sample. NULL if no goal is given.
   \param arst Statistics on the AtlasRRT construction process.
   \param ar The AtlasRRT.
*/
unsigned int AddStepToAtlasRRTstar(Tparameters* pr,
				   unsigned int it,boolean expand2Goal,boolean onManifold,
				   unsigned int i_near,double *x_rand,
				   unsigned int *id_goal,double *goal,
				   TAtlasRRTStatistics *arst,
				   Tatlasrrt *ar);

/** 
   \brief Wires a node to the AtlasRRT star.

   Selects the best parent among all neighbouring nodes for a node just
   added to the tree.

   \param pr The set of parameters.
   \param id_new Identifier of the last node added to the tree.
   \param i_near Parent of the node just added to the tree.
   \param gamma Radius of search used to determine the neighbours.
   \param nn Number of neighbours.
   \param n Array with the indices of the neighbouring nodes.
   \param c Array where we store the cost to the neighbours. This is
            useful in re-wire to avoid recomputing symmetrical costs.
	    (see \ref RRTSTAR_SYMMETRIC_COST).
   \param h Heuristic cost to the goal. Only used if
            the RRT is in graph mode.
   \param q Priority queue to propagate changes in the tree. Only
            used the RRT is in graph mode.
   \param t The trees of the neighbouring nodes. This in only relevant
            in bi-directional RRTs
   \param arst Statistics on the AtlasRRT construction process.
   \param ar The AtlasRRT.
*/
void WireAtlasRRTstar(Tparameters *pr,
		      unsigned int id_new,unsigned int i_near,double gamma,
		      unsigned int nn,unsigned int *n,double **c,
		      double h,Theap *q,unsigned int *t,
		      TAtlasRRTStatistics *arst,Tatlasrrt *ar);

/** 
   \brief Rewires an AtlasRRT star.

   Uses the last added node to the AtlasRRT to try to reduce the cost
   of the neighbouring nodes.


   \param pr The set of parameters.
   \param id_new Identifier of the last node added to the tree.
   \param gamma Radius of search used to determine the neighbours.
   \param nn Number of neighbours.
   \param n Array with the indices of the neighbouring nodes.
   \param c Array where we with the cost to the neighbours.
            Computed in \ref WireAtlasRRTstar
	    if \ref RRTSTAR_SYMMETRIC_COST is 1.
   \param steps The steps forming the solution path.
   \param l Cost of the path from start to goal via s1 and s2.
            Only used in mode==TWO_TREES_WITH_SWAP.
   \param arst Statistics on the AtlasRRT construction process.
   \param ar The AtlasRRT.
*/
void ReWireAtlasRRTstar(Tparameters *pr,
			unsigned int id_new,double gamma,
			unsigned int nn,unsigned int *n,double *c,
			Tvector *steps,double *l,
			TAtlasRRTStatistics *arst,Tatlasrrt *ar);

/** 
   \brief Prints information about the AtlasRRT* iteration.

   Prints information about the AtlasRRT* iteration.

   \param it The current iteration.
   \param id_goal The identifier of the goal. If not found yet, NO_UINT.
   \param time Elapsed time from the start of the  AtlasRRT*
   \param gamma Value of the threshold for nearest neighbours.
   \param times Array to store information about the execution time per
                iteration.
   \param costs Array to store information about the cost to the goal per
                iteration.
   \param ar The AtlasRRT.
*/
void AtlasRRTstarCloseIteration(unsigned int it,unsigned int id_goal,
				double time,double gamma,
				double *times,double *costs,
				Tatlasrrt *ar);

/** 
   \brief Prints information about the BiAtlasRRT* iteration.

   Prints information about the Bi-directional AtlasRRT* iteration.

   \param it The current iteration.
   \param l Current cost to goal. INF if no path found yet.
   \param time Elapsed time from the start of the  AtlasRRT*
   \param gamma Value of the threshold for nearest neighbours.
   \param times Array to store information about the execution time per
                iteration.
   \param costs Array to store information about the cost to the goal per
                iteration.
   \param ar The AtlasRRT.
*/
void AtlasBiRRTstarCloseIteration(unsigned int it,double l,
				  double time,double gamma,
				  double *times,double *costs,
				  Tatlasrrt *ar);

/** 
   \brief Saves the information associated with a sample in an AtlasRRT.

   Saves the information relating a given sample to charts in an AtlasRRT.

   \param f The file where to store the information.
   \param si The sample information to store.
   \param ar The AtlasRRT.
*/
void SaveAtlasRRTSampleInfo(FILE *f,TSampleInfo *si,Tatlasrrt *ar);

/** 
   \brief Saves the information associated with a chart in an AtlasRRT.

   Saves the information relating a given chart to the samples it contains

   \param f The file where to store the information.
   \param ci The chart information to store.
   \param ar The AtlasRRT.
*/
void SaveAtlasRRTChartInfo(FILE *f,TChartInfo *ci,Tatlasrrt *ar);


/** 
   \brief Reads the information associated with a sample in an AtlasRRT.

   Reads the information relating a given sample to charts in an AtlasRRT.

   \param f The file where to store the information.
   \param si The sample information to initialize.
   \param ar The AtlasRRT.
*/
void LoadAtlasRRTSampleInfo(FILE *f,TSampleInfo *si,Tatlasrrt *ar);

/** 
   \brief Reads the information associated with a chart in an AtlasRRT.

   Reads the information relating a given chart to the samples it contains

   \param f The file where to store the information.
   \param ci The chart information to initialize.
   \param ar The AtlasRRT.
*/
void LoadAtlasRRTChartInfo(FILE *f,TChartInfo *ci,Tatlasrrt *ar);

/** 
   \brief Plots a point where x_rang is and a line to its chart.

   Small debug utility to plot the position of x_rand.

   \param pr The set of parameters.
   \param prefix Prefix used to generate the plot file name.
   \param inear Nearest neighbour.
   \param c_rand The chart where x_rand was selected.
   \param t_rand The parameters for x_rand
   \param x_rand The point in ambient coordinates
   \param xID The first ambient dimension where to project
              (in the original system including system vars and dummies).
   \param yID The second ambient dimension where to project
              (in the original system including system vars and dummies).
   \param zID The thrid ambient dimension where to project
              (in the original system including system vars and dummies).
   \param ar The AtlasRRT.
*/
void PlotQrand(Tparameters *pr,char *prefix,unsigned int inear,
	       unsigned int c_rand,double *t_rand,double *x_rand,
	       unsigned int xID,unsigned int yID,unsigned int zID,
	       Tatlasrrt *ar);

/** 
   \brief Graphical representation of the attempt to connect two trees.

   Graphical representation of the attempt to connect two trees.

   \param pr The set of parameters.
   \param prefix Prefix used to generate the plot file name.
   \param target Point to reach in the tree
   \param near Point from where to extend the connection branch
   \param end Point finally reached in the connection attempt.
   \param xID The first ambient dimension where to project
              (in the original system including system vars and dummies).
   \param yID The second ambient dimension where to project
              (in the original system including system vars and dummies).
   \param zID The thrid ambient dimension where to project
              (in the original system including system vars and dummies).
   \param ar The AtlasRRT.
*/
void PlotConnection(Tparameters *pr,char *prefix,
		    unsigned int target,unsigned int near,unsigned int end,
		    unsigned int xID,unsigned int yID,unsigned int zID,
		    Tatlasrrt *ar);

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void InitBranchState(Tparameters *pr,TAtlasRRTBranchConfig *config,
		     TSampleInfo *near,double *randSample,double *goalSample,
		     TDynamicSpace *ds,
		     Tatlasrrt *ar,TAtlasRRTBranchState *state)
{
  double delta,epsilon;
    
  delta=GetParameter(CT_DELTA,pr);
  epsilon=GetParameter(CT_EPSILON,pr);

  if (randSample==NULL)
    {
      state->reachedQrand=FALSE;
      state->distQrand=INF;
    }
  else
    {
      /* Check if x_rand is already in the tree almost reached by the tree */
      state->distQrand=DistanceTopology(ar->m,ar->tp,near->s,randSample);

      if (config->onManifold)
	state->reachedQrand=(state->distQrand<(ar->dynamics?delta:epsilon));
      else
	state->reachedQrand=FALSE;
    }
  /* initially the temporay x_rand will be the same as x_rand */
  state->reachedTmpQrand=state->reachedQrand;

  /* The new brach will belong to the tree of i_near */
  state->tree=GetRRTNodeTree(near->id,&(ar->rrt));

  /* Check if goal is already reached */

  #if (EXPLORATION_RRT)
    state->distGoal=INF;
  #else
    if (goalSample!=NULL)
      state->distGoal=DistanceTopology(ar->m,ar->tp,near->s,goalSample);
    else
      state->distGoal=INF;
  #endif
  #if (WEIGTHED_REACHED_GOAL)
    if (goalSample!=NULL)
      state->reachedGoal=(WeightedDistanceTopology(ar->m,ar->tp,ar->weights,near->s,goalSample)<(ar->dynamics?ar->dge:epsilon));
    else
      state->reachedGoal=FALSE;
  #else
    state->reachedGoal=(state->distGoal<(ar->dynamics?ar->dge:delta));
  #endif
    
  state->nCreatedCharts=0;

  /* last sample in the branch */
  state->lastID=near->id;

  /* Interpolation step */
  state->delta=delta;

  /* Advance direction in tangent space (this is set in
     PointTowardRandSample) */
  NEW(state->deltaParam,ar->k,double);

  /* Vector of visited charts */
  InitVector(sizeof(unsigned int),CopyID,NULL,100,&(state->traversedCharts));
  NewVectorElement((void*)&(near->c),&(state->traversedCharts));

  /* Severbal branh advance diagnostics */
  state->blocked=NO_BLOCKED; /* The branch is stopped for whatever reason */
  
  state->validChart=TRUE; /* The current chart is not valid. */
  
  /* Cost of the next node (this value is actually not used) */
  state->cost=0;

  /* Set the parameters defining the maximum span of the branch */
  if (ar->dynamics)
    {
      /* branch extension controlled in time */
      state->desiredLength=+INF;
      state->maxLength=+INF;
    }
  else
    {
      if (config->maxLength<=0.0)
	{
	  /* maxLenght not set -> auto-setting of the parameres */
	  state->desiredLength=state->distQrand;
	  state->maxLength=2.0*state->distQrand;
	}
      else
	{
	  /* Use the parameters given by the user.
	     Set desired=max to make the branch to grow to its maximum, if needed. */
	  state->desiredLength=config->maxLength;
	  state->maxLength=config->maxLength;
	}
    }

  /* Branch length so far */
  state->length=0.0;

  /* maximum distance to origin (even if dynamics!!) */
  state->maxDistOrigin=state->distQrand;
  if ((randSample!=NULL)&&(config->onManifold))
    state->maxDistOrigin*=1.1; /* add some margin */

  /* distance from the last node of the branch (so far) to the first one */
  state->distOrigin=0;

  /* Length of the last step along the branch */
  state->stepLength=0.0;

  /* integration time so far (only used in dynamics) */
  state->intTime=0.0;

  /* Time in the last step */
  state->h=0.0;

  /* initially we use a chart in the atlas */
  state->chartInAtlas=TRUE;
}

void PrintBranchBlockedState(FILE *f,char *prefix,TAtlasRRTBranchConfig *config,TAtlasRRTBranchState *state)
{
  if (state->blocked & NO_DIR)
    fprintf(f,"%sBranch stopped: no advance direction\n",prefix);
  if (state->blocked & NO_POLICY)
    fprintf(f,"%sBranch stopped: can not compute the LQR policy\n",prefix);
  if (state->blocked & DYNAMIC_ERROR)
    fprintf(f,"%sBranch stopped: dynamic error\n",prefix);
  if (state->blocked & COLLISION)
    fprintf(f,"%sBranch stopped: collision\n",prefix);
  if (state->blocked & NOT_IN_DOMAIN)
    fprintf(f,"%sBranch stopped: not in domain\n",prefix);
  if (state->blocked & TOO_FAR)
    fprintf(f,"%sBranch stopped: too far\n",prefix);
  if (state->blocked & TRANSITION_TEST_FAILS)
    fprintf(f,"%sBranch stopped: transition test failed\n",prefix);
  if (state->blocked & REVISITED_CHART)
    fprintf(f,"%sBranch stopped: revisited chart\n",prefix);
  if (state->blocked & REPEATED_CHART)
    fprintf(f,"%sBranch stopped: repeated chart\n",prefix);
  if (state->blocked & THE_IMPOSSIBLE)
    fprintf(f,"%sBranch stopped: the impossible happened\n",prefix);
  if (state->blocked & REPEATED_SAMPLE)
    fprintf(f,"%sBranch stopped: repeated sample\n",prefix);
  if (state->blocked & SINGULARITY)
    fprintf(f,"%sBranch stopped: singularity found\n",prefix);
  if (state->blocked & NO_REPLAY)
    fprintf(f,"%sBranch stopped: end of data when replaying\n",prefix);
  if (state->blocked & TOO_LONG)
    fprintf(f,"%sBranch stopped: too long\n",prefix);
  if (state->blocked & MAX_INT_TIME)
    fprintf(f,"%sBranch stopped: max integration time reached [%f %f]\n",prefix,state->intTime,config->currentMaxIntTime);
  if (state->blocked & MAX_OPT_TIME)
    fprintf(f,"%sBranch stopped: too large optimal time\n",prefix);
	
  if (state->reachedTmpQrand)
    fprintf(f,"%sBranch stopped: TmpQrand reached\n",prefix);
  if (state->reachedGoal)
    fprintf(f,"%sBranch stopped: Goal reached\n",prefix);
  if (state->reachedQrand)
    fprintf(f,"%sBranch stopped: Qrand reached\n",prefix);
}

void DeleteBranchState(TAtlasRRTBranchState *state)
{
  free(state->deltaParam);
  DeleteVector(&(state->traversedCharts));
  if (!state->chartInAtlas)
    DeleteChart(&(state->c));
}

boolean canContinueBranch(boolean dynamics,
			  TAtlasRRTBranchConfig *config,
			  TAtlasRRTBranchState *state)
{ 
  return((state->blocked==NO_BLOCKED)&&
	 (!state->reachedTmpQrand)&&
	 (!state->reachedGoal)&&
	 (!state->reachedQrand));
}

void InitBranchConfig(unsigned int mode,TAtlasRRTBranchConfig *config)
{
  switch (mode)
    {
    case EXTEND_RRT:
      config->addMode=ADD_ALL;
      config->chartAddMode=ADD_ALL;
      config->revisitCharts=REVISIT_CHARTS;
      config->repeatCharts=REPEAT_CHARTS;
      config->checkCollisions=TRUE;
      config->onManifold=FALSE; /* will vary */
      config->explorationSample=FALSE; /* vary */
      config->maxLength=0.0;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=FALSE;
      config->maxIntTime=INF;
      config->currentMaxIntTime=INF;
      config->topt=INF;
      config->maxTopt=INF;
      config->tLastLinearization=INF;
      config->randLQRAction=FALSE;
      break;
    case CONNECT_RRTs:
      config->addMode=ADD_ALL;
      config->chartAddMode=ADD_ALL;
      config->revisitCharts=TRUE;
      config->repeatCharts=TRUE;
      config->checkCollisions=TRUE;
      config->onManifold=TRUE;
      config->explorationSample=FALSE;
      config->maxLength=0.0;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=FALSE;
      config->maxIntTime=INF;
      config->currentMaxIntTime=INF;
      config->topt=INF;
      config->maxTopt=INF;
      config->tLastLinearization=INF;
      config->randLQRAction=FALSE;
      break;
    case CONNECT_SAMPLES:
      config->addMode=ADD_NONE;
      config->chartAddMode=ADD_ALL;
      config->revisitCharts=TRUE;
      config->repeatCharts=TRUE;
      config->checkCollisions=TRUE;
      config->onManifold=TRUE;
      config->explorationSample=FALSE;
      config->maxLength=0.0;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=FALSE;
      config->maxIntTime=INF;
      config->currentMaxIntTime=INF;
      config->topt=INF;
      config->maxTopt=INF;
      config->tLastLinearization=INF;
      config->randLQRAction=FALSE;
      break;
    case CONNECT_SAFE:
      config->addMode=ADD_NONE;
      config->chartAddMode=ADD_ALL;
      config->revisitCharts=TRUE;
      config->repeatCharts=TRUE;
      config->checkCollisions=FALSE;
      config->onManifold=TRUE;
      config->explorationSample=FALSE;
      config->maxLength=0.0;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=FALSE;
      config->maxIntTime=INF;
      config->currentMaxIntTime=INF;
      config->topt=INF;
      config->maxTopt=INF;
      config->tLastLinearization=INF;
      config->randLQRAction=FALSE;
      break;
    case SIMULATE_DYNAMICS:
      config->addMode=ADD_LAST;
      config->chartAddMode=ADD_ALL;
      config->revisitCharts=TRUE;
      config->repeatCharts=TRUE;
      config->checkCollisions=TRUE;
      config->onManifold=TRUE;
      config->explorationSample=TRUE;
      config->maxLength=INF;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=TRUE;
      config->maxIntTime=0; /* will vary */
      config->currentMaxIntTime=0;
      config->topt=0; /* may vary */
      config->maxTopt=INF;
      config->tLastLinearization=0;
      config->randLQRAction=FALSE;
      break;
    case EXTEND_RRT_DYNAMICS:
      config->addMode=ADD_NONE;
      config->chartAddMode=ADD_NONE;
      config->revisitCharts=(SATURATE_ACTIONS?REVISIT_CHARTS:TRUE);
      config->repeatCharts=(SATURATE_ACTIONS?REPEAT_CHARTS:TRUE);
      config->checkCollisions=TRUE;
      config->onManifold=FALSE; /* is set to TRUE when expanding to goal */
      config->explorationSample=FALSE; /* vary */
      config->maxLength=INF;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=TRUE;
      config->maxIntTime=0; /* will vary */ 
      config->currentMaxIntTime=0;
      config->topt=0; /* may vary */
      config->maxTopt=INF; /* may vary */
      config->tLastLinearization=0;
      config->randLQRAction=FALSE;
      break;
    case CONNECT_RRT_DYNAMICS:
      config->addMode=ADD_NONE;
      config->chartAddMode=ADD_NONE;
      config->revisitCharts=(SATURATE_ACTIONS?REVISIT_CHARTS:TRUE);
      config->repeatCharts=(SATURATE_ACTIONS?REPEAT_CHARTS:TRUE);
      config->checkCollisions=TRUE;
      config->onManifold=TRUE;
      config->explorationSample=FALSE;
      config->maxLength=INF;
      config->costF=NULL;
      config->costData=NULL;
      config->dynamics=TRUE;
      config->maxIntTime=0; /* will vary */
      config->currentMaxIntTime=0;
      config->topt=0; /* may vary */
      config->maxTopt=INF; /* may vary */
      config->tLastLinearization=0;
      config->randLQRAction=FALSE;
      break;
    default:
      Error("Unknown mode in InitBranchConfig");
    }
}

void InitSampleInfo(unsigned int m,unsigned int k,TSampleInfo *si)
{
  si->id=NO_UINT;
  NEW(si->s,m,double);
  NEW(si->t,k,double);
  si->pc=NO_UINT;
  si->c=NO_UINT;
  si->generateChart=0; /* FALSE */
  si->lsc=NO_UINT;
}

void SetSampleInfo(unsigned int m,unsigned int k,
		   TSampleInfo *si_dst,TSampleInfo *si_src)
{
  si_dst->id=si_src->id;
  memcpy(si_dst->s,si_src->s,m*sizeof(double));
  memcpy(si_dst->t,si_src->t,k*sizeof(double));
  si_dst->pc=si_src->pc;
  si_dst->c=si_src->c;
  si_dst->generateChart=si_src->generateChart;
  si_dst->lsc=si_src->lsc;
}

void SetSampleInfoFromNode(unsigned int n,Tatlasrrt *ar,TSampleInfo *si)
{
  SetSampleInfo(ar->m,ar->k,si,ar->si[n]);
}

void DeleteSampleInfo(TSampleInfo *si)
{

  free(si->s);
  free(si->t);
}

void UpdateLQRPolicy(Tparameters *pr,TAtlasRRTBranchConfig *config,
		     Tchart *c_lqr,double *t_near,double *t_rand,
		     TAtlasRRTBranchState *state,void *st,TDynamicSpace *ds,
		     Tatlasrrt *ar)
{
  double epsilon,delta,planningHorizon,tg,ph;
  double *mA,*mAt,*mB,*vc,*vd,*iRBt,*BiRBt;
   
  epsilon=GetParameter(CT_EPSILON,pr);
  delta=GetParameter(CT_DELTA,pr);
  ph=GetParameter(CT_LQR_PLANNING_TIME,pr);
  if (config->maxTopt==INF)
    planningHorizon=ph; 
  else
    {
      planningHorizon=config->maxTopt; //+2*delta; /* policies with time larger than maxTopt won't be accepted anyway */
      if (planningHorizon>ph)
	planningHorizon=ph;
    }

  if (planningHorizon<1e-3)
    {
      state->blocked=NO_POLICY;
      #if (ATLASRRT_VERBOSE)
        fprintf(stderr,"  Too short planning horizon [%f]\n",planningHorizon);
      #endif
      #if (GET_ATLASRRT_STATISTICS)
	NewAtlasRRTNoLQRPolicy((TAtlasRRTStatistics *)st);
      #endif
    }
  else
    {
  
      GetLinearizedDynamics(&mA,&mAt,&mB,&vc,&vd,&iRBt,&BiRBt,c_lqr);
      
      if (mA==NULL)
	{
	  /* The linearized dynamics is not yet defined for c_near. Define it now */
	  LinearizeDynamics(pr,c_lqr,NULL,GetChartCenter(c_lqr),NULL,GetChartTangentSpace(c_lqr),&mA,&mB,&vc,ar->ds);
	  SetLinearizedDynamics(ar->da,mA,mB,vc,GetInverseActionCostMatrix(ar->ds),c_lqr);
	  GetLinearizedDynamics(&mA,&mAt,&mB,&vc,&vd,&iRBt,&BiRBt,c_lqr);
	}

      if (state->tree==START2GOAL)
	config->topt=LQR_COMPUTE_POLICY(pr,t_near,t_rand,planningHorizon,mA,mB,vc,vd,iRBt,BiRBt,ds);	      	
      else
	config->topt=LQR_COMPUTE_POLICY(pr,t_rand,t_near,planningHorizon,mA,mB,vc,vd,iRBt,BiRBt,ds);

      if (config->topt==INF)
	{
	  state->blocked=NO_POLICY; /* This aborts the branch generation */
      
	  #if (ATLASRRT_VERBOSE)
	    fprintf(stderr,"  Computing LQR policy failed\n");
	  #endif
	  #if (GET_ATLASRRT_STATISTICS)
	    NewAtlasRRTNoLQRPolicy((TAtlasRRTStatistics *)st);
	  #endif
	}
      else
	{
	  if (config->topt<1e-3)
	    {
	      state->blocked=NO_POLICY;
	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr,"  Too short optimal time [%f]\n",config->topt);
	      #endif
	      #if (GET_ATLASRRT_STATISTICS)
		NewAtlasRRTNoLQRPolicy((TAtlasRRTStatistics *)st);
	      #endif
	    }
	  else
	    {
	      #if (GET_ATLASRRT_STATISTICS)
	      NewAtlasRRTLQRComputePolicy(config->topt,(TAtlasRRTStatistics *)st);
	      #endif
  
	      //config->topt+=state->intTime; /* change topt to a global time (not starting in the current linearization) */
	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr, "***********************************************\n");
		fprintf(stderr,"Updating LQR policy\n");
		PrintVector(stderr,"  y_near",ar->k,t_near);
		PrintVector(stderr,"  y_rand",ar->k,t_rand);
		fprintf(stderr,"  d=%f\n",Distance(ar->k,t_near,t_rand));
		fprintf(stderr, "  time=%f\n",state->intTime);
		fprintf(stderr, "  planningHorizon=%f\n",planningHorizon);
		fprintf(stderr,"  t_opt=%f\n",config->topt);
		fprintf(stderr,"  maxIntTime=%f\n",config->maxIntTime);
	        #if (ATLASRRT_VERBOSE>1)
		  fprintf(stderr, "   tree=%d\n",state->tree);
		  PrintMatrix(stderr,"   Uc",ar->m,ar->k,GetChartTangentSpace(c_lqr));
		  PrintVector(stderr,"   x0",ar->m,GetChartCenter(c_lqr));
		  PrintMatrix(stderr,"   A",ar->k,ar->k,mA);
		  PrintMatrix(stderr,"   B",ar->k,ar->k/2,mB);
		  PrintVector(stderr,"   c",ar->k,vc);
	        #endif
	      #endif

	      if (config->topt+epsilon>config->maxTopt) /* Strictly decreasing to avoid infinite loops */
		{	  
		  state->blocked=MAX_OPT_TIME;
	  
		  #if (ATLASRRT_VERBOSE)
		    fprintf(stderr,"  Too large optimal time. Not approaching goal (%f vs %f).\n",config->topt,config->maxTopt);
		    fprintf(stderr, "***********************************************\n");
		  #endif
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTLQRToptIncreases((TAtlasRRTStatistics *)st);
		  #endif  
		}
	      else
		{
		  /* Time at which we expect to reach the goal */
		  tg=state->intTime+config->topt;
	    
		  if (tg<config->maxIntTime)
		    config->currentMaxIntTime=tg;
		  else
		    config->currentMaxIntTime=config->maxIntTime;
	    
		  /* Next time we try to grow a branch, the optimal time must be lower than this */
		  config->maxTopt=config->topt;
	  
		  #if (ATLASRRT_VERBOSE)
		    fprintf(stderr,"  currentMaxIntTime: %f\n",config->currentMaxIntTime);
		    fprintf(stderr, "***********************************************\n");
		  #endif
		}
	      config->tLastLinearization=state->intTime;
	    }
	}
    }
}


double AddBranchToAtlasRRT(Tparameters *pr,unsigned int it,TAtlasRRTBranchConfig *config,
			   unsigned int nsReplay,double **replayPath,boolean *replayNewChart,double *replayTime,double *replayCost,
			   double *action,
			   unsigned int i_near,double *randSample,double *goalSample,
			   void *st,TAtlasRRTBranchState *state,
			   unsigned int *ns,double ***path,boolean **newChart,double **tStep,double **cStep,
			   TSampleInfo *lastSample,TDynamicSpace *ds,
			   Tatlasrrt *ar)
{
  TSampleInfo current,next,rand,*near;
  boolean initData,intersectParent;
  double epsilon,delta;
  unsigned int ms,maxNodes,samplingMode;
  unsigned int ms1,ns1;
  double **path1,**actions1,*times1;
  unsigned int nSamples;
  boolean replayMode;
  double pl,pt;
  /* Variable used in LQR computation */	
  Tchart *c_lqr;
  
  /* Sanity checks */
  if (i_near==NO_UINT)
    Error("Extending a branch from nowhere");

  if ((config->chartAddMode==ADD_NONE)&&(config->addMode!=ADD_NONE))
    Error("Can not add samples if charts are not added too");

  /* Get the parameters */
  epsilon=GetParameter(CT_EPSILON,pr);
  delta=GetParameter(CT_DELTA,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);
  
  /* Info on the neareast sample */
  near=ar->si[i_near];

  /* Initialize the state of the branch */
  InitBranchState(pr,config,near,randSample,goalSample,ds,ar,state);

  replayMode=((nsReplay>0)&&(replayPath!=NULL)&&(replayNewChart!=NULL)&&(replayTime!=NULL)&&(replayCost!=NULL));

  /* If we have to store the path, init the storage*/
  if ((ns!=NULL)&&(path!=NULL))
    {
      if (replayMode)
	Error("Can not reply and store at the same time!");
      
      InitSamplesReplay(&ms,ns,path,newChart,tStep,cStep);
      /* In dynamic problems, we add the first sample to the trace just in case we have to
         create a chart on it. */
      if (ar->dynamics)
	AddSample2SamplesReplay(ar->m,ar->si[i_near]->s,FALSE,0,0,ar->m,NULL,&ms,ns,path,newChart,tStep,cStep);
    }
  
  if ((state->reachedQrand)||(state->reachedGoal))
    /* If x_rand/goal are alrady reached, there is not point
       in initializing the structures. */
    initData=FALSE;
  else
    {
      /* If the goal sample is not already reached, we prepare for the
         branch extension */
      initData=TRUE;

      /* For problems with dynamics and in ADD_LAST mode, we keep all the steps
	 and add them in the edge of the RRT when adding the last sample along
	 the new branch. These samples in the edge are not considered when
	 searching for nearest-neighbours (not used to extend the tree) but
	 are used when plotting (we get nicher plots) */
      if ((ar->dynamics)&&((config->addMode==ADD_LAST)||
			   (config->addMode==ADD_LAST_NO_REP)||
			   (config->addMode==ADD_CHART_AND_LAST_NO_REP)))
	InitTrajectory(&ms1,&ns1,&path1,ar->da,&actions1,&times1);
      else
	{
	  ms1=0;
	  ns1=0;
	  path1=NULL;
	  actions1=NULL;
	  times1=NULL;
	}

      /* x_near is the first 'current' (sample) of the branch */
      InitSampleInfo(ar->m,ar->k,&current);
      SetSampleInfoFromNode(i_near,ar,&current);

      InitSampleInfo(ar->m,ar->k,&next);

      if (randSample!=NULL)
	{
	  /* in dynamics there is no random sample to guide the extension
	     but a given action */
	  InitSampleInfo(ar->m,ar->k,&rand);

	  /* get a copy of the random sample. This will be modified while
	     extending the branch. 'rand' is a temporary representation of
	     'randSample' in the current chart, which changes along the
	     branch */
	  memcpy(rand.s,randSample,ar->m*sizeof(double));

	  /* Detemine the direction of motion toward 'rand' from the 'current' */
	  if (PointTowardRandSample(config,samplingMode,randSample,state,&current,&rand,ar))
	    {
	      state->blocked=NO_DIR;
	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTNoAdvanceDirection((TAtlasRRTStatistics *)st);
	      #endif
	    }
	}

      #if (ATLASRRT_VERBOSE>2)
        if (!ar->parallel)
	  {
	    fprintf(stderr,"      Adding branch to RRT from sample %u (chart %u):\n",i_near,current.c);
	    PrintVector(stderr,"        x_near",ar->m,current.s);
	    PrintVector(stderr,"        y_near",ar->k,current.t);
	  }
      #endif
    }

  /* If we have to use LQR to determine the best action at each step, we have to fix the policy at this point */
  if ((initData)&&(state->blocked==NO_BLOCKED)&&(ar->dynamics)&&(ar->nda==0)&&(!replayMode)&&(!config->randLQRAction))
    { 
      if (randSample==NULL)
	Error("Using LQR without a random sample");
	
      c_lqr=GetAtlasChart(current.c,&(ar->atlas));

      #if (ATLASRRT_VERBOSE)
        fprintf(stderr,"Initializing policy [chart: %u]\n",current.c);
      #endif
      UpdateLQRPolicy(pr,config,c_lqr,current.t,rand.t,state,st,ds,ar);
    }

  nSamples=0;
  pl=0.0; /* previous lenght. Only used when adding samples in chart creation */
  pt=0.0; /* previous time */

  /* We stop if blocked, after a maximum dist extansion or
     if it gets farther than the ambient dist to the randSample. This
     is measured in two ways: the distance traveled over the monifold
     (state->length) and the distance from the current sample to x_near
     (flag state->tooFar).
     The new branch should not scape the ball of radious maxR centered
     at x_near. We allow for a larger displacement over the manifold to
     account for curvature effects.
  */
  while (canContinueBranch(ar->dynamics,config,state)&&((config->addMode==ADD_NONE)||(ar->ns<maxNodes)))
    {
      #if (GET_ATLASRRT_STATISTICS)
        NewAtlasRRTStep((TAtlasRRTStatistics *)st);
      #endif
	
      /* Generate the new sample from current and rand. */
      if (replayMode)
	{
	  #if (ATLASRRT_VERBOSE>2)
	    fprintf(stderr,"    Replaying sample %u\n",nSamples);
	  #endif
	  if (replayNewChart[nSamples])
	    {
	      #if (ATLASRRT_VERBOSE>2)
	        fprintf(stderr,"      Create new chart: %u\n",ar->nc);
	      #endif
	      state->validChart=FALSE;
	      replayNewChart[nSamples]=FALSE; /* next iteration we will move forward (using the new chart) */
	    }
	  else
	    {
	      unsigned int ndx;

	      /* get next sample */
	      /* first sample not used (already in the tree) */
	      /* may only be used to generate a chart */
	      ndx=nSamples+1;
	      if (ndx<nsReplay)
		{
		  Tchart *cc; /* current chart */

		  memcpy(next.s,replayPath[ndx],sizeof(double)*ar->m);
		  #if (ATLASRRT_VERBOSE>2)
		    PrintVector(stderr,"      s",ar->m,next.s);
	          #endif
		  if (state->chartInAtlas)
		    cc=GetAtlasChart(current.c,&(ar->atlas));
		  else
		    cc=&(state->c);
		  Manifold2Chart(next.s,ar->tp,next.t,cc);
		  next.c=current.c;
		  next.pc=current.c;
		  next.generateChart=FALSE;

		  state->h=(replayTime==NULL?0.0:replayTime[ndx]);
		  state->cost=(replayCost==NULL?0.0:replayCost[ndx]);
		}
	      else
		{
		  state->blocked=NO_REPLAY;
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTNoReplay((TAtlasRRTStatistics *)st);
		  #endif	  
		}
	    }
	}
      else
	NewTemptativeSample(pr,it,config,state,&current,action,&next,&rand,randSample,st,ds,ar);

      if (state->blocked==NO_BLOCKED)
	{	  
	  /* If we actually managed to generate the temptative sample */
	  if (!state->validChart)
	    {
	      /* We need to create a new chart in the current sample
	         (i.e., the new temptative sample is not valid) */
	      if (current.generateChart)
		{		   
		  if (replayMode)
		    Error("This should not happen");
		    
		  /* But current samples was already been used to create
		     a chart. We reduce the step size with the aim of finding
		     a point close to the current one where to create a chart. */
		  state->delta*=0.5;
		  state->validChart=TRUE; /* re-try with the previous chart */
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTStepReduction((TAtlasRRTStatistics *)st);
		  #endif
		} 
	      else
		{
                  #if (!HALF_PLANES)
		  /* When not using half planes in the charts we may generate charts on samples
		     where another chart is already generated. This is problematic */
		  unsigned int nn;
		  double dnn;

		  nn=GetRRTNN(state->tree,current.s,&(ar->rrt));
		  dnn=DistanceTopology(ar->m,ar->tp,ar->si[nn]->s,current.s);
		  if (dnn<0.1*delta)
		    {
		      state->blocked=REPEATED_SAMPLE;
		      
		      #if (GET_ATLASRRT_STATISTICS)
		        NewAtlasRRTRepeatedSample((TAtlasRRTStatistics *)st);
		      #endif
		    }
		  else
		    {
                  #endif
		      /* We generate the new chart (this will change 'current') */
		      if (AddChart2AtlasRRT(pr,state->tree,it,config,state,&current,
					    &intersectParent,ar))
			{
			  if (current.c!=NO_UINT) /* if the chart was actually inserted in the atlas (not a temporary chart) */
			    { 
			      #if (ATLASRRT_VERBOSE>1)
			        PrintVector(stderr,"      New chart",ar->m,current.s);
				fprintf(stderr,"        Chart ID: %u\n",current.c);
			      #endif

			      if (config->addMode==ADD_CHART_AND_LAST_NO_REP)
				{
				  #if (HALF_PLANES)
				    unsigned int nn;
				    double dnn;

				    nn=GetRRTNN(state->tree,current.s,&(ar->rrt));
				    dnn=DistanceTopology(ar->m,ar->tp,ar->si[nn]->s,current.s);
				  #endif
				  if (dnn>0.1*delta)
				    {
				      AddSample2AtlasRRT(pr,state->tree,
							 &(state->lastID),
							 current.c,current.t,current.s,
							 state->length-pl,
							 state->cost,FALSE,action,state->intTime-pt,
							 ns1,path1,actions1,times1,ar);

				      #if (ATLASRRT_VERBOSE>1)
				        fprintf(stderr,"        Sample ID: %u\n",state->lastID);
				      #endif
				      /* keep track of the length / time when we added the last sample to the atlasRRT */
				      pl=state->length;
				      pt=state->intTime;
			  
				      if (ar->dynamics)
					{
					  /* We do not need to delete the trajectory so far (it is keep inside the RRT).
					     We just initialize a new trajectory segment. We only delete stored trajectories
					     when the sample is not added to the RRT */
					  InitTrajectory(&ms1,&ns1,&path1,ar->da,&actions1,&times1);
					}
			  
				      ar->si[state->lastID]->generateChart=TRUE; 

				      #if (GET_ATLASRRT_STATISTICS)
				        NewAtlasRRTSample((TAtlasRRTStatistics *)st);
				      #endif
				    }
				}
		      
			      /* the chart generation was fine */
			      #if (GET_ATLASRRT_STATISTICS)
			        NewAtlasRRTChart((TAtlasRRTStatistics *)st);
				if(!intersectParent)
				  NewAtlasRRTNoConnectToParent((TAtlasRRTStatistics *)st);
			      #endif

			      /* Keep track of the new visited chart  */
		      
			      NewVectorElement((void*)&(current.c),&(state->traversedCharts));	  
			    }
		      
			  /* The branch created one new more chart */
			  state->nCreatedCharts++;

			  /* We have a new valid chart */
			  state->validChart=TRUE;

			  /* Reset the advance step */
			  state->delta=delta;

			  if (randSample!=NULL)
			    {
			      /* Re-define the advance direction (i.e., rand and
				 state.deltaParam) in the new chart */
			      if (PointTowardRandSample(config,samplingMode,randSample,state,&current,&rand,ar))
				{
				  state->blocked=NO_DIR;
				  #if (GET_ATLASRRT_STATISTICS)
				    NewAtlasRRTNoAdvanceDirection((TAtlasRRTStatistics *)st);
				  #endif		  
				}
			    }

			  /* If we are recording the simulation, we have to annotate that
			     we created a chart in the current sample. */
			  if ((!replayMode)&&(newChart!=NULL))
			    (*newChart)[nSamples]=TRUE;
			
			  /* Created a new chart, see if we have to re-compute the LQR policy */
			  #if (RELINEALIZE_DYNAMICS)
			    /* Note that this is not executed when extending branches in parallel (in this case nda>0) */
			    if ((ar->dynamics)&&(ar->nda==0)&&(!config->randLQRAction)&&(randSample!=NULL))
			      {
				if (current.c!=NO_UINT)
				  c_lqr=GetAtlasChart(current.c,&(ar->atlas));
				else
				  c_lqr=&(state->c); /* This should never happen: LQR is not only used when actually modifying the atlas (not simulations) */
				
				#if (ATLASRRT_VERBOSE)
				  fprintf(stderr,"Computing the policy at the new chart [chart: %u]\n",current.c);
				#endif
				UpdateLQRPolicy(pr,config,c_lqr,current.t,rand.t,state,st,ds,ar);
			      }
			  #endif
			}
		      else
			{
			  /* There was an error creating the chart: Stop the
			     branch extension.
			     TODO: Implement a more sophisticated stratetgy to deal
			     with singular regions.
			  */
			  state->blocked=SINGULARITY;
			  fprintf(stderr,"  Point in singularity (decrease epsilon?)\n");
			  #if (GET_ATLASRRT_STATISTICS)
			    NewAtlasRRTBlockBySingularity((TAtlasRRTStatistics *)st);
			  #endif
			}
		  #if (!HALF_PLANES)
		    }
		  #endif
		}
	    }
	  else
	    {
	      /* Note that in the following many blocking condition may be detected, but
	         we accept the sample (except if it is already in the RRT) */
	      if (ar->dynamics)
		{
		  state->intTime+=state->h;
		  if (state->intTime>=config->currentMaxIntTime)
		    {
		      state->blocked=MAX_INT_TIME;
		      #if (GET_ATLASRRT_STATISTICS)
		        NewAtlasRRTIntTimeReached((TAtlasRRTStatistics *)st);
		      #endif
		    }
		}

	      if (randSample!=NULL)
		{
		  /* The temptative sample is correct. We can advance along the branch. */
		  state->reachedTmpQrand=((rand.c==next.c)&&
					  (Distance(ar->k,rand.t,next.t)<(ar->dynamics?delta:epsilon)));

		  state->distQrand=DistanceTopology(ar->m,ar->tp,next.s,randSample);

		  if (config->onManifold)
		    state->reachedQrand=(state->distQrand<(ar->dynamics?delta:epsilon));
		}

	      #if (!EXPLORATION_RRT)
	        if (goalSample!=NULL)
		  {
		    state->distGoal=DistanceTopology(ar->m,ar->tp,next.s,goalSample);
		    #if (WEIGTHED_REACHED_GOAL)
		      state->reachedGoal=(WeightedDistanceTopology(ar->m,ar->tp,ar->weights,next.s,goalSample)<(ar->dynamics?ar->dge:epsilon));
		    #else
		      state->reachedGoal=(state->distGoal<(ar->dynamics?ar->dge:epsilon));
		    #endif
		  }
	      #endif

	      #if (GET_ATLASRRT_STATISTICS)
	        if ((state->reachedQrand)||(state->reachedTmpQrand))
		  NewAtlasRRTQrandReached(Distance(ar->k,rand.t,next.t),(TAtlasRRTStatistics *)st);
	      #endif

	      state->distOrigin=DistanceTopology(ar->m,ar->tp,next.s,near->s);
	      if ((!replayMode)&&(!ar->dynamics)&&(state->distOrigin>state->maxDistOrigin))
		{
		  state->blocked=TOO_FAR;
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTTooFar((TAtlasRRTStatistics *)st);
		  #endif
		}

	      /* Add the sample to the tree, if required */
	      state->stepLength=DistanceTopology(ar->m,ar->tp,current.s,next.s);

	      if ((config->addMode==ADD_ALL)||(config->addMode==ADD_ALL_NO_REP))
		{
		  if (config->addMode==ADD_ALL_NO_REP)
		    {
		      unsigned int nn;

		      nn=GetRRTNN(state->tree,next.s,&(ar->rrt));
		      if (DistanceTopology(ar->m,ar->tp,ar->si[nn]->s,next.s)<0.1*delta)
			{
			  state->blocked=REPEATED_SAMPLE;
			  #if (GET_ATLASRRT_STATISTICS)
			    NewAtlasRRTRepeatedSample((TAtlasRRTStatistics *)st);
			  #endif
			}
		    }
		  if (state->blocked==NO_BLOCKED)
		    {
		      #if (ATLASRRT_VERBOSE>1)
		        PrintVector(stderr,"      New sample",ar->m,next.s);
		        fprintf(stderr,"        Sample ID: %u\n",state->lastID);
		      #endif
		      state->length+=AddSample2AtlasRRT(pr,state->tree,
							&(state->lastID),
							next.c,next.t,next.s,
							state->stepLength,
							state->cost,FALSE,action,state->h,
							0,NULL,NULL,NULL,ar);
							/* Current is the last node added to the AtlasRRT */
		      SetSampleInfoFromNode(state->lastID,ar,&current);
		      #if (GET_ATLASRRT_STATISTICS)
		        NewAtlasRRTSample((TAtlasRRTStatistics *)st);
		      #endif
		    }
		}
	      else
		{
		  /* ADD_LAST or ADD_LAST_NO_REP or ADD_CHART_AND_LAST_NO_REP or ADD_NONE */
		  if (ms1>0)
		    {
		      /* ADD_LAST or ADD_LAST_NO_REP or ADD_CHART_AND_LAST_NO_REP */
		      AddStep2Trajectory(ar->m,next.s,ar->m,NULL,action,state->h,
					 &ms1,&ns1,&path1,ar->da,&actions1,&times1);
		    }

		  state->length+=state->stepLength;
		  /* current <- next (this sets current.generateChart=0) */
		  SetSampleInfo(ar->m,ar->k,&current,&next);
		}

	      /* Reset the advance step */
	      state->delta=delta;

	      if ((!ar->dynamics)&&(state->length>=state->maxLength))
		{
		  state->blocked=TOO_LONG;
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTTooLong((TAtlasRRTStatistics *)st);
		  #endif
		}

	      nSamples++;

	      /* Add the sample the path, if required. In dynamic mode we add all samples
		 to the path. Otherwise the last step is skipped to avoid repetions (for
		 instance when smoothing a path). */
	      if ((!replayMode)&&(ns!=NULL)&&(path!=NULL)&&
		  ((ar->dynamics)||
		   ((!state->reachedTmpQrand)&&(!state->reachedQrand)&&(!state->reachedGoal))))
		AddSample2SamplesReplay(ar->m,next.s,FALSE,state->h,state->cost,ar->m,NULL,&ms,ns,path,newChart,tStep,cStep);
	    }
	}
    }

  #if (ATLASRRT_VERBOSE)
    if ((initData)&&(!ar->parallel))
      PrintBranchBlockedState(stderr,"        ",config,state);
  #endif

  /* Final adjust of the branch lenght: Add the distance from the last
     sample in the branch to the goal/x_rand (this is epsilon/delta size) */

  if (state->reachedGoal)
    {
      state->length+=state->distGoal;
      if ((initData)&&(goalSample!=NULL))
	{
	  if (!ar->parallel)
	    {
	      #if (WEIGTHED_REACHED_GOAL)
	          
	        fprintf(stderr,"Weighted error in connection: %f (%f)\n",
			WeightedDistanceTopology(ar->m,ar->tp,ar->weights,next.s,goalSample),(ar->dynamics?ar->dge:epsilon));
	      #else
		fprintf(stderr,"Weighted error in connection: %f (%f)\n",
			DistanceTopology(ar->m,ar->tp,current.s,goalSample),(ar->dynamics?ar->dge:epsilon));
	      #endif
	    }
	  memcpy(current.s,goalSample,ar->m*sizeof(double));
	}
    }
  else
    {
      if (state->reachedQrand)
	{
	  state->length+=state->distQrand;
	  if ((initData)&&(randSample!=NULL))
	    memcpy(current.s,randSample,ar->m*sizeof(double));
	}
    }

  /* The branch is alrady defined. Check what to do with the last sample along
     the branch, release memory, and adjust the final branch lenght. */
  if (initData)
    {
      if ((state->length>0)&&
	  ((config->addMode==ADD_LAST)||
	   (config->addMode==ADD_LAST_NO_REP)||
	   (config->addMode==ADD_CHART_AND_LAST_NO_REP)))
	{
	  boolean noRep;

	  /* In some branch configurations, the last sample has to be added
	     to the RRT, in some cases avoiding repetitions. */
	  if ((config->addMode==ADD_LAST_NO_REP)||
	      (config->addMode==ADD_CHART_AND_LAST_NO_REP))
	    {
	      if (state->blocked&REPEATED_SAMPLE)
		noRep=FALSE;
	      else
		{
		  unsigned int nn;

		  nn=GetRRTNN(state->tree,current.s,&(ar->rrt));
		  noRep=(DistanceTopology(ar->m,ar->tp,ar->si[nn]->s,current.s)>0.1*delta); //epsilon
		  #if (GET_ATLASRRT_STATISTICS)
		    if (!noRep)
		      NewAtlasRRTRepeatedSample((TAtlasRRTStatistics *)st);
		  #endif
		}
	    }
	  else
	    noRep=TRUE;

	  if (noRep)
	    {
	      if ((!current.generateChart)&&(Norm(ar->k,current.t)<epsilon))
		Warning("Adding a sample on a chart center");

	      /* avoid a possible repetition of the last point in the RRT edge and
	         the point actually added to the RRT */
	      if (ns1>0)
		{
		  ns1--;
		  free(path1[ns1]);
		  free(actions1[ns1]);
		}
 
	      /* If it was required to advance toward x_rand and we actually
		 moved in that direction and we have to add the last computed
		 sample -> add it (with distance to parent = branch length) */
	      /* Here lastID will be i_near if no sample was added yet */
	      AddSample2AtlasRRT(pr,state->tree,&(state->lastID),
				 current.c,current.t,current.s,
				 state->length-pl,state->cost,
				 ((ar->dynamics)&&((state->blocked & NOT_IN_DOMAIN)||(state->blocked & COLLISION))),
				 action,state->intTime-pt,
				 ns1,path1,actions1,times1,ar);
	      /* In some rare ocassions, the last sample of the branch
	         (the one we just added to the tree) has been used to
	         generate a chart.  Mark it to avoid the generation of
	         a new chart on this same sample latter on. When adding
	         all samples along the branch to the RRT, none of the
	         added samples can be the center of a chart (charts are
	         only defined on samples already in the tree). When adding
	         only the last sample to the tree, charts are created on
	         temporary samples that might be included in the tree if
	         they are the last sample along a branch. */
	      ar->si[state->lastID]->generateChart=current.generateChart;

              #if (ATLASRRT_VERBOSE>1)
	        PrintVector(stderr,"      New sample",ar->m,current.s);
		fprintf(stderr,"        Sample ID: %u\n",state->lastID);
	      #endif
		
	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTSample((TAtlasRRTStatistics *)st);
	      #endif
	    }
	  else
	    {
	      if (ms1>0)
		DeleteTrajectory(ns1,path1,actions1,times1);
	    }
	}
      else
	{
	  if (ms1>0)
	    DeleteTrajectory(ns1,path1,actions1,times1);
	}

      /* Update the statistic of how far we can get from i_near */
      /* This only has effect if paramter DYNAMIC_DOMAIN is >0 */
      AdjustDynamicDomain(i_near,state->blocked & COLLISION,&(ar->rrt));

      /* If the caller needs it, we store the last sample in a buffer */
      if (lastSample!=NULL)
	SetSampleInfo(ar->m,ar->k,lastSample,&current);

      DeleteSampleInfo(&current);
      DeleteSampleInfo(&next);
      if (randSample!=NULL)
	DeleteSampleInfo(&rand);
    }

  /* Release the possible memory allocated by the InitBranchState, if any */
  DeleteBranchState(state);

  return(state->length);
}


void InitDynamicBranches(Tparameters *pr,TDynamicBranches *db,Tatlasrrt *ar)
{
  unsigned int ca,n;
  if(ar->nda==0)
    n=1;
  else
    n=ar->nda;

  /* Simulted sample */
  NEW(db->sample,n,TSampleInfo);
  for(ca=0;ca<n;ca++)
    InitSampleInfo(ar->m,ar->k,&(db->sample[ca]));

  NEW(db->action,n,double*); /* action */
  NEW(db->qrandb,n,double*); /* local qrand */
  for(ca=0;ca<n;ca++)
    {
      NEW(db->action[ca],ar->da,double);
      NEW(db->qrandb[ca],ar->m,double);
    }

  /* Branch estate */
  NEW(db->state,n,TAtlasRRTBranchState);

  /* distance of the end of the branch to the rand sample */
  NEW(db->dAction,n,double);

  /* space to project random samples */
  /* only used with T2G_METRIC */
  NEW(db->tr,n,double*);
  for(ca=0;ca<n;ca++)
    {
      NEW(db->tr[ca],ar->k,double);
    }

  /* The replay information is initialized inside the branch, but
     we have to make space for the replay information for each branch */
  NEW(db->nsReplay,n,unsigned int);
  NEW(db->statesReplay,n,double**);
  NEW(db->newChartReplay,n,boolean*);
  NEW(db->timeReplay,n,double*);
  NEW(db->costReplay,n,double*);
}

void DeleteDynamicBranches(TDynamicBranches *db,Tatlasrrt *ar)
{
  unsigned int ca,n;

  if(ar->nda==0)
    n=1;
  else
    n=ar->nda;

  for(ca=0;ca<n;ca++)
    DeleteSampleInfo(&(db->sample[ca]));
  free(db->sample);

  for(ca=0;ca<n;ca++)
    {
      free(db->action[ca]);
      free(db->qrandb[ca]);
    }
  free(db->action);
  free(db->qrandb);

  free(db->state);

  free(db->dAction);

  for(ca=0;ca<n;ca++)
    free(db->tr[ca]);
  free(db->tr);

  free(db->nsReplay);
  free(db->statesReplay);
  free(db->newChartReplay);
  free(db->timeReplay);
  free(db->costReplay);
}

double AddBranchToAtlasDynamicRRT(Tparameters *pr,
				  unsigned int oneAction,unsigned int t2g,
				  unsigned int it,TAtlasRRTBranchConfig *config,
				  unsigned int i_near,double *randSample,double *goalSample,
				  void *st,TDynamicBranches *db,unsigned int *lastSample,
				  boolean *reachedGoal,Tatlasrrt *ar)
{
  double dst,de,dInit,dEnd,dBest,epsilon;
  unsigned int bAction;
  boolean haveAction,done,advance,blocked;
  unsigned int ca,tree;
  int nt;
  unsigned int nRep;
  Tchart *c_near; /* Chart including i_near */
  double *t_rand; /* random sample parameters in c_near */

  *lastSample=i_near; /* last sample added to the branch */
  *reachedGoal=FALSE;

  dst=0.0;

  epsilon=GetParameter(CT_EPSILON,pr);
  tree=GetRRTNodeTree(i_near,&(ar->rrt)); /* Extended tree */
	
  if (t2g)
    {
      NEW(t_rand,ar->k,double); /* paramter space used for t2g and lqr */
      
      c_near=GetAtlasChart(ar->si[i_near]->c,&(ar->atlas));
      Manifold2Chart(randSample,ar->tp,t_rand,c_near);

      dInit=Time2Go(pr,tree,c_near,
		    ar->si[i_near]->t,ar->si[i_near]->s,
		    t_rand,randSample,&de,ar->ds);
      #if (ATLASRRT_VERBOSE)
        if (dInit==INF)
	  Error("Dynamic branch from a wrong node?");
      #endif
    }
  else
    {
      #if (WEIGTHED_REACHED_GOAL>1)
        dInit=WeightedDistanceTopology(ar->m,ar->tp,ar->weights,ar->si[i_near]->s,randSample);
      #else
        dInit=DistanceTopology(ar->m,ar->tp,ar->si[i_near]->s,randSample);
      #endif
    }
	      
  advance=TRUE; /* when using LQR this will not be used */
  config->maxTopt=INF; /* Initially we accept any optimal time. When repeating we will accept only decreasing optimal times. */
  nRep=0;
  
  while (advance)
    {
      #if (ATLASRRT_VERBOSE)
        fprintf(stderr,"---------------------------------------------------------------------------------------------------------\n");
      #endif
      #if (GET_ATLASRRT_STATISTICS)
        NewAtlasRRTDynamicExtension((TAtlasRRTStatistics *)st);
      #endif

      advance=FALSE;
      done=FALSE;
      nRep++;
      
      #if (ATLASRRT_VERBOSE>2)
      fprintf(stderr,"  Simulation from sample %u (it: %u  chart: %u  tree: %u maxIntTime: %f [%f])\n",i_near,it,ar->si[i_near]->c,GetRRTNodeTree(i_near,&(ar->rrt)),config->currentMaxIntTime,config->maxIntTime);
	PrintVector(stderr,"    x_rand",ar->m,randSample);
	PrintVector(stderr,"    x_near",ar->m,ar->si[i_near]->s);
	if (t2g)
	  fprintf(stderr,"    Distance[x_near,x_rand]=%f\n",
		  Time2Go(pr,tree,c_near,
			  ar->si[i_near]->t,ar->si[i_near]->s,
			  t_rand,randSample,&de,ar->ds));
	else
	  fprintf(stderr,"    Distance[x_near,x_rand]=%f\n",
		  DistanceTopology(ar->m,ar->tp,ar->si[i_near]->s,randSample));
      #endif
      
      if ((oneAction)||(ar->nda==0))
	{
	  if ((ar->nda==0)&&((nRep>1)||(config->onManifold)||(randomDouble()<=(1.0-RANDOMIZED_LQR))))
	    {
	      /* Action will be determined via LQR while generating the branch */
	      bAction=0;
	      haveAction=TRUE;
	      config->randLQRAction=FALSE;
	    }
	  else
	    {
	      /* We only want to execute one action generated at random */
	      if (GetActionFromID(randomMax(ar->nda),db->action[0],ar->ds))
		{
		  bAction=0;
		  haveAction=TRUE;

		  if (ar->nda==0)
		    {
		      config->randLQRAction=TRUE;
		      config->currentMaxIntTime=config->maxIntTime;
		      #if (RANDOM_INT_TIME)
		        config->currentMaxIntTime*=randomDouble();
  	              #endif
		    }
		  
		  #if (ATLASRRT_VERBOSE>1)
		    fprintf(stderr,"  Selected one action at random\n");
		    PrintVector(stderr,"  u",ar->da,db->action[0]);
		    fprintf(stderr,"  t: %f\n",config->currentMaxIntTime);
		  #endif
		}
	      else
		{
		  bAction=NO_UINT;
		  haveAction=FALSE;
		  #if (ATLASRRT_VERBOSE>1)
		    fprintf(stderr,"  Invalid random action\n");
		  #endif
		}
	    }
	}
      else
	{
	  #if (ATLASRRT_VERBOSE>2)
	    /* If in verbose mode (aka debug) we make sure that actions are 
	       pre-generated is sequence (not in parallel) to ensure replicability
	       and to get the same results even if executing in parallel */
	    for(ca=0;ca<ar->nda;ca++)
	      {	
		if (GetActionFromID(ca,db->action[ca],&(ar->ds[0])))
		    db->nsReplay[ca]=1; /* use this as a flag to mark if the action was properly generated */
		else
		  db->nsReplay[ca]=0;
	      }
	  #endif

	  #pragma omp parallel for private(ca,nt) schedule(dynamic) if (ar->parallel)
	  for(ca=0;ca<ar->nda;ca++)
	    {
	      #ifdef _OPENMP
	        if (ar->parallel)
		  nt=omp_get_thread_num();
		else
		  nt=0; /* need to be defined since this is a local variable in omp (even if parallel is FALSE) */
	      #else
		nt=0;
	      #endif
		    
	      /* Generate the action to simulate */
	      #if (ATLASRRT_VERBOSE>2)
	      if (db->nsReplay[ca]>0)
	      #else
	      if (GetActionFromID(ca,db->action[ca],&(ar->ds[nt])))
	      #endif
		{
		  #if (ATLASRRT_VERBOSE>2)
		    fprintf(stderr,"    Simulating action %u/%u ",ca,ar->nda-1);
		    PrintVector(stderr,"   u",ar->da,db->action[ca]);
		  #endif
		  /* copy the rand sample (it is modified internally) */
		  memcpy(db->qrandb[ca],randSample,ar->m*sizeof(double));

		  /* Simulate the action */
		  /* TODO: do not simulate if we already have a similar action in the reachability set */
		  AddBranchToAtlasRRT(pr,it,config,0,NULL,NULL,NULL,NULL,
				      db->action[ca],i_near,db->qrandb[ca],goalSample,
				      NULL,&(db->state[ca]),
				      &(db->nsReplay[ca]),&(db->statesReplay[ca]),&(db->newChartReplay[ca]),&(db->timeReplay[ca]),&(db->costReplay[ca]),
				      &(db->sample[ca]),&(ar->ds[nt]),ar);

		  /* If we actually simulated something ... */
		  if ((db->state[ca].intTime>0)||(db->state[ca].reachedGoal))
		    {
		      /* compute the distance from the end of the branch to x_rand */
		      if (t2g)
			{
			  Manifold2Chart(db->sample[ca].s,ar->tp,db->tr[ca],c_near);
			  db->dAction[ca]=Time2Go(pr,tree,c_near,
						  db->tr[ca],db->sample[ca].s,
						  t_rand,randSample,&de,&(ar->ds[nt]));
			}
		      else
			{
			  #if (WEIGTHED_REACHED_GOAL>1)
			    db->dAction[ca]=WeightedDistanceTopology(ar->m,ar->tp,ar->weights,db->sample[ca].s,randSample);
			  #else
			    db->dAction[ca]=DistanceTopology(ar->m,ar->tp,db->sample[ca].s,randSample);
			  #endif
			}
		    }
		}
	      else
		{
		  db->nsReplay[ca]=0;
		  db->state[ca].intTime=0.0;
		}
	    }

	  ca=0;
	  bAction=NO_UINT; /* No good action so far */
	  dBest=INF;
	  
	  #if (ATLASRRT_VERBOSE>1)
	    fprintf(stderr,"  Distance to Qrand: %f\n",dInit);
	    fprintf(stderr,"  Summary of actions\n");
	  #endif
	  while((!done)&&(ca<ar->nda))
	    {
	      if ((db->state[ca].intTime>0)||(db->state[ca].reachedGoal))
		{
		  #if (ATLASRRT_VERBOSE>1)
		    fprintf(stderr,"  Action %u\n",ca);
		    PrintVector(stderr,"    u",ar->da,db->action[ca]);
		    fprintf(stderr,"    Action time %f\n",db->state[ca].intTime);
		    fprintf(stderr,"    Branch length %f\n",db->state[ca].length);
		    PrintVector(stderr,"    x_next",ar->m,db->sample[ca].s);
		    fprintf(stderr,"    Distance [%u]: %f\n",ca,db->dAction[ca]);
		    if (t2g)
		      fprintf(stderr,"    DistanceE [%u]: %f\n",ca,DistanceTopology(ar->m,ar->tp,db->sample[ca].s,randSample));
		    fprintf(stderr,"    Reached Qrand %u\n",db->state[ca].reachedQrand);
		    fprintf(stderr,"    Reached TmpQrand %u\n",db->state[ca].reachedTmpQrand);
		    fprintf(stderr,"    Reached goal %u\n",db->state[ca].reachedGoal);
		  #endif

		  /* .. check if the goal is already reached or if the current action is the best so far */
		  *reachedGoal=db->state[ca].reachedGoal;

		  done=((db->state[ca].reachedGoal)||
			(db->state[ca].reachedQrand)||
			(db->state[ca].reachedTmpQrand));
	      
		  if ((done)||(db->dAction[ca]<dBest))
		    {
		      /* If so keep this action */
		      bAction=ca;
		      dBest=db->dAction[ca];
		    }
		}
	      #if (ATLASRRT_VERBOSE>1)
	      else
		{
		  fprintf(stderr,"  Action %u\n",ca);
		  PrintVector(stderr,"    u",ar->da,db->action[ca]);
		  fprintf(stderr,"    Action time %f\n",db->state[ca].intTime);
		  fprintf(stderr,"    Branch length %f\n",db->state[ca].length);
		}

	      PrintBranchBlockedState(stderr,"    ",config,&(db->state[ca]));
	      #endif

	      ca++;
	    }

	  #if (ATLASRRT_VERBOSE)
	    if (bAction!=NO_UINT)
	      {
		if (t2g)
		  fprintf(stderr,"  Best action[it:%u] %u (%f)\n",it,bAction,dBest);
		else
		  fprintf(stderr,"  Best action[it:%u] %u (%f)\n",it,bAction,dBest);
	      }
	  #endif

	  haveAction=((bAction!=NO_UINT)&&
		      ((done)||(
				((nRep==1)||(dBest<dInit))&&
				(db->state[bAction].length>epsilon)&&
				(!PointInRRT(1e-5,db->state[bAction].tree,db->sample[bAction].s,&(ar->rrt)))
				)
		       )
		      );

	  /* Blocked for any reason, but for MAX_INT_TIME since in this case
	     we can try to repeat the branch extension */
	  if (haveAction)
	    blocked=((db->state[bAction].blocked & (~MAX_INT_TIME))||
		     (ar->ns>=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr)));
	  
	} /* end of else if ((oneAction)||(ar->nda==0)) */

      /* If there is a 'good' action -> repeat it but now adding the samples and charts to the tree and the atlas */
      if (haveAction)
	{
	  #if (ATLASRRT_VERBOSE>1)
	    if (nRep==1)
	      fprintf(stderr,"  Executing the best action from sample %u\n",i_near);
	    else
	      fprintf(stderr,"  Re-executing the best action from sample %u\n",i_near);
	  #endif
	    
	  /* The branch to be generated next is not a simulation but a good one */
	  #if (DYNAMICS_ADD_ALL==0)
	    config->addMode=ADD_LAST_NO_REP;
	  #else
	    #if (DYNAMICS_ADD_ALL==1)
	      config->addMode=ADD_CHART_AND_LAST_NO_REP;
	    #else
	      config->addMode=ADD_ALL_NO_REP;
	    #endif
	  #endif
 
	  config->chartAddMode=ADD_ALL;

	  if ((oneAction)||(ar->nda==0)||(ATLASRRT_VERBOSE>0))
	    { 
	      /* There was no previous simulation of actions: do not replay anything
	         but directly generate a new branch. */
	      AddBranchToAtlasRRT(pr,it,config,
				  0,NULL,NULL,NULL,NULL,
				  db->action[bAction],i_near,randSample,goalSample,
				  st,&(db->state[bAction]),NULL,NULL,NULL,NULL,NULL,
				  &(db->sample[bAction]),ar->ds,ar);
	      
	      *reachedGoal=db->state[bAction].reachedGoal;
	      
	      done=((db->state[bAction].reachedGoal)||
		    (db->state[bAction].reachedQrand)||
		    (db->state[bAction].reachedTmpQrand));

	      /* Blocked for any reason, but for MAX_INT_TIME since in this case
		 we can try to repeat the branch extension */
	      blocked=((db->state[bAction].blocked & (~MAX_INT_TIME))||
		       (ar->ns>=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr)));
	      
	      #if (ATLASRRT_VERBOSE>2)
	        fprintf(stderr,"    Action time %f\n",db->state[bAction].intTime);
		fprintf(stderr,"    Branch length %f\n",db->state[bAction].length);
		PrintVector(stderr,"    x_next",ar->m,db->sample[bAction].s);
		fprintf(stderr,"    Dist2rand: %f\n",DistanceTopology(ar->m,ar->tp,db->sample[bAction].s,randSample));
		fprintf(stderr,"    Reached Qrand %u\n",db->state[bAction].reachedQrand);
		fprintf(stderr,"    Reached TmpQrand %u\n",db->state[bAction].reachedTmpQrand);
		fprintf(stderr,"    Reached goal %u\n",db->state[bAction].reachedGoal);
	      #endif
	    }
	  else
	    {
	      /* We previously simulated many branches. Now we just have to replay the best one */
	      AddBranchToAtlasRRT(pr,it,config,
				  //0,NULL,NULL,NULL,NULL,
				  db->nsReplay[bAction],db->statesReplay[bAction],
				  db->newChartReplay[bAction],db->timeReplay[bAction],db->costReplay[bAction],
				  db->action[bAction],i_near,randSample,goalSample,
				  st,&(db->state[bAction]),NULL,NULL,NULL,NULL,NULL,
				  &(db->sample[bAction]),ar->ds,ar);
	    }

	  config->addMode=ADD_NONE;
	  config->chartAddMode=ADD_NONE;

	  *lastSample=db->state[bAction].lastID;
	  dst+=db->state[bAction].length;
	  #if (ATLASRRT_VERBOSE>2)
	    fprintf(stderr,"End adding branch\n");
	  #endif

	  if (t2g)
	    dEnd=Time2Go(pr,tree,c_near,
			 ar->si[*lastSample]->t,ar->si[*lastSample]->s,
			 t_rand,randSample,&de,ar->ds);
	  else
	    {
	      #if (WEIGTHED_REACHED_GOAL>1)
	        dEnd=WeightedDistanceTopology(ar->m,ar->tp,ar->weights,ar->si[*lastSample]->s,randSample);
              #else
		dEnd=DistanceTopology(ar->m,ar->tp,ar->si[*lastSample]->s,randSample);
	      #endif
	    }

	  if ((!done)&&(!blocked))
	    {
	      #if (ATLASRRT_DYNAMIC_CONNECT)
 	        if ((ar->nda==0)&&(!config->randLQRAction))
		  advance=TRUE; /* In this case the 'advance' is based on time and decided at the beginning of the branch extension. */
		else
		  {
		    advance=(dEnd<dInit);
		    #if (ATLASRRT_VERBOSE)
		      fprintf(stderr,"  Repeat extension [%f %f]\n",dInit,dEnd);
		    #endif
		  }
	      #endif
	      dInit=dEnd;
	      if (advance)
		i_near=*lastSample;
	    }
	  #if (ATLASRRT_VERBOSE)
	  else
	    {
	      if (ar->ns>=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr))
		fprintf(stderr,"  Max number of nodes in RRT reached\n");
	      else
		{
		  if (done)
		    fprintf(stderr,"  Goal reached %f\n",dEnd);
		  else
		    fprintf(stderr,"  Branch blocked\n");
		}
	    }
	  #endif
	}
      else
	{
	  #if (GET_ATLASRRT_STATISTICS)
	    NewAtlasRRTNoAction((TAtlasRRTStatistics *)st);
	  #endif
	  #if (ATLASRRT_VERBOSE)
	  if (bAction!=NO_UINT)
	    {
	      if (db->state[bAction].length<=epsilon)
		fprintf(stderr,"  Empty simulation\n");
	      else
		{
		  if ((nRep>1)&&(dEnd>=dInit))
		    fprintf(stderr,"  Going away from goal %f vs %f\n",dInit,dBest);
		  else
		    fprintf(stderr,"  Repeated point\n");
		}
	    }
	  else
	    fprintf(stderr,"  Best action undefined\n");
	  #endif
	}

      #if (GET_ATLASRRT_STATISTICS)
        if (nRep>1)
	  {
	    /* We are extending a branch (i.e., and improvement over previous branches) */
	    NewAtlasRRTImprovedDynamicExtension((TAtlasRRTStatistics *)st);
	  }
      #endif
	
      /* Forget the simulated branches, if used */
      if ((!oneAction)&&(ar->nda>0))
	{
	  for(ca=0;ca<ar->nda;ca++)
	    {
	      if (db->nsReplay[ca]>0)
		DeleteSamplesReplay(db->nsReplay[ca],db->statesReplay[ca],db->newChartReplay[ca],db->timeReplay[ca],db->costReplay[ca]);
	    }
	}

      
    } /* if advancing in the good direction, repeat the branch extension (iff in RRT_CONNECT mode) */

  
  if (t2g)
    free(t_rand);
  
  return(dst);
}

void NewTemptativeSample(Tparameters *pr,unsigned int it,
			 TAtlasRRTBranchConfig *config,
			 TAtlasRRTBranchState *state,
			 TSampleInfo *current,double *action,TSampleInfo *next,
			 TSampleInfo *rand,double *randSample,
			 void *st,TDynamicSpace *ds,Tatlasrrt *ar)
{
  double epsilon;
  unsigned int samplingMode,itB;
  double dif;
  Tchart *nextChart;
  Tchart *currentChart;

  epsilon=GetParameter(CT_EPSILON,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

  /* new samples do not generated a chart (yet) */
  next->generateChart=0;

  /* In principle, 'next' sample is in the same chart as the
     'current' sample */
  next->c=current->c;
  /* and it is generated in this same sample */
  next->pc=current->c;

  if (state->chartInAtlas)
    currentChart=GetAtlasChart(current->c,&(ar->atlas));
  else
    currentChart=&(state->c);
	  
  if (state->delta<epsilon)
    {
      /* The advance step is too small. This means we are trying to generate
	 a sample (i.e., a chart center) very close to another sample and
	 even being very close we didn't manage to to it. This should never
	 happen for smooth manifolds. */
      Warning("The impossible happened (III)");
      state->blocked=THE_IMPOSSIBLE;
      #if (GET_ATLASRRT_STATISTICS)
        NewAtlasRRTImpossible((TAtlasRRTStatistics *)st);
      #endif
    }
  else
    {
      if (ar->dynamics) /* dynamics>0 */
	{
	  unsigned int dOut; /* output of the dynamic step */
	  double md,sat;

	  md=(config->currentMaxIntTime-state->intTime); /* maximum "displacement" in time */
	  if (md>state->delta)
	    md=state->delta;

	  if (ar->dynamics<4)
	    {
	      /* Local integration methods */
	      dOut=0;
	      if ((ar->nda==0)&&(!config->randLQRAction))
		{
		  /* Use LQR to compute the action */
		  if (state->tree==START2GOAL)
		    sat=LQRPolicy(pr,action,(state->intTime-config->tLastLinearization),ds);
		  else
		    sat=LQRPolicy(pr,action,config->topt-(state->intTime-config->tLastLinearization),ds);
		  
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTLQRPolicy(sat,(TAtlasRRTStatistics *)st);
		  #endif
		  #if (ATLASRRT_VERBOSE)
		    if (state->tree==START2GOAL)
		      fprintf(stderr,"      LQR action(t=%f,t_lqr=%f):\n",state->intTime,(state->intTime-config->tLastLinearization));
		    else
		      fprintf(stderr,"      LQR action(t=%f,t_lqr=%f):\n",state->intTime,config->topt-(state->intTime-config->tLastLinearization));
		    #if (ATLASRRT_VERBOSE>1)
		      PrintVector(stderr,"        u",ds->dof,action);
		    #endif
		  #endif
		}

	      switch(ar->dynamics)
		{
		case 1:
		  /* Implicit trapezoidal rule */
		  dOut=NextDynamicState(pr,state->tree,state->delta,FALSE,
					current->s,current->t,currentChart,action,
					&(state->h),md,
					next->s,&itB,ds);
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTBroyden(itB,(TAtlasRRTStatistics *)st);
		  #endif
		  break;
		case 2:
		  dOut=NextDynamicStateLocalEuler(pr,state->tree,state->delta,
						  current->s,current->t,currentChart,action,
						  &(state->h),md,
						  next->s,ds);
		  break;
		case 3:
		  dOut=NextDynamicStateLocalRK4(pr,state->tree,state->delta,
						current->s,current->t,currentChart,action,
						&(state->h),md,
						next->s,ds);
		  break;
		default:
		  Error("Undefined dynamic mode");
		}
	    }
	  else
	    {
	      /* Euler/Runge-Kutta integration methods without projection to the manifold */
	      state->h=state->delta;
	      if (state->h>md)
		state->h=md;
	      
	      if (ar->dynamics==4)
		dOut=NextDynamicStateEuler(pr,state->tree,&(state->h),state->delta,current->s,action,next->s,ds);
	      else
		dOut=NextDynamicStateRK4(pr,state->tree,&(state->h),state->delta,current->s,action,next->s,ds);
	    }
	  
	  if (dOut>0)
	    {
	      state->blocked=DYNAMIC_ERROR;
	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTDynamicError((TAtlasRRTStatistics *)st);
	      #endif
	    }
	  else
	    {
	      Manifold2Chart(next->s,ar->tp,next->t,currentChart);
	      
	      #if (ATLASRRT_VERBOSE)
		if (randSample!=NULL)
		  fprintf(stderr,"        d2r=%f\n",Distance(ar->k,next->t,rand->t));
	        #if (ATLASRRT_VERBOSE>1)
		  PrintVector(stderr,"        y_new",ar->k,next->t);
		#endif
	      #endif
	      #if (ATLASRRT_VERBOSE>2)
	        if (!ar->parallel)
		  {
		    if (next->c==NO_UINT)
		      fprintf(stderr,"      New sample (tmp chart, t:%f/%f):\n",state->intTime+state->h,config->currentMaxIntTime);
		    else
		      fprintf(stderr,"      New sample (c:%u t:%f/%f):\n",next->c,state->intTime+state->h,config->currentMaxIntTime);
		    PrintVector(stderr,"        x",ar->m,next->s);
		    PrintVector(stderr,"        y",ar->k,next->t);
		  }
	      #endif
	    }
	}
      else
	{
	  /* Move a step of (max) size 'delta' from current towards rand  */
	  dif=Distance(ar->k,current->t,rand->t);
	  if (dif<state->delta)
	    memcpy(next->t,rand->t,ar->k*sizeof(double));
	  else
	    SumVectorScale(ar->k,current->t,state->delta,
			   state->deltaParam,next->t);
	}

      if (state->blocked==NO_BLOCKED)
	{
	  if (state->chartInAtlas)
	    nextChart=GetAtlasChart(next->c,&(ar->atlas));
	  else
	    nextChart=&(state->c);
	      
	  if (Norm(ar->k,next->t)>ar->r)
	    {
	      /* 'next' is out of the validity area (ball) of the current
		 chart. Its time to generate a new chart (in the previous
		 sample that is still inside the chart). */
	      state->validChart=FALSE;

	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTOutOfChart((TAtlasRRTStatistics *)st);
	      #endif
	      #if (ATLASRRT_VERBOSE>2)
	        if (!ar->parallel)
		  fprintf(stderr,"       Out of radius->Generate chart\n");
	      #endif
	    }
	  else
	    { 
	      /* temporary charts have empty polytopes and, thus, the points
		 are always inside the polytope... */
	      if (!InsideChartPolytope(next->t,nextChart))
		{
	          #if (ATLASRRT_VERBOSE>2)
		    if (!ar->parallel)
		      fprintf(stderr,"       Crossed a chart border -> Move to a neighboring chart\n");
		  #endif

		  /* 'next' is outside the polytope of the chart -> it might
		     be in a neighbouring chart */
		  //if ((!config->revisitCharts)&&(!config->onManifold)&&
		  //	((config->explorationSample)||(state->nCreatedCharts>0)))
		  if ((!config->revisitCharts)&&(!config->onManifold)&&(config->explorationSample))
		    {
		      /* A branch aiming a random point in tangent space that is
			 a exploration branch or that generated new charts while
			 growing. It is stopped to enter a pre-existing chart.
			 This tries to avoid branch crossing. */
		      state->blocked=REVISITED_CHART;
		      #if (GET_ATLASRRT_STATISTICS)
		        NewAtlasRRTRevisitedChart((TAtlasRRTStatistics *)st);
		      #endif
		      #if (ATLASRRT_VERBOSE>2)
		        if (!ar->parallel)
			  {
			    if (state->nCreatedCharts>0)
			      fprintf(stderr,"       Branch stopped (created charts>1)\n");
			    else
			      fprintf(stderr,"       Branch stopped (exploration)\n");
			  }
		      #endif
		    }
		  else
		    {
		      /* Determine the neighbouring chart including the
			 'next' sample */
		      next->c=DetermineChartNeighbour(epsilon,next->t,nextChart);

		      /* if repeatCharts=FALSE, the branch can not enter already visited charts */
		      if ((!config->repeatCharts)&&
			  (ElementInVector((void*)&(next->c),CmpID,&(state->traversedCharts))))
			{
			  state->blocked=REPEATED_CHART;
			  #if (GET_ATLASRRT_STATISTICS)
			    NewAtlasRRTRepeatedChart((TAtlasRRTStatistics *)st);
			  #endif
			  #if (ATLASRRT_VERBOSE>2)
			    if (!ar->parallel)
			      fprintf(stderr,"       Branch stopped (no revisit)\n");
			  #endif
			}
		      else
			{
			  /* Transition between pre-existing charts -> continue normally.
			     We basically repeat all the steps for the new chart */
			  #if (ATLASRRT_VERBOSE>2)
			    if (!ar->parallel)
			      fprintf(stderr,"       Branch moved to chart: %u\n",next->c);
			  #endif

			  /* Get the new chart */
			  nextChart=GetAtlasChart(next->c,&(ar->atlas));
			  
			  /* Project the current sample to the new chart: we need current
			     and next in the same chart to use the same local parametrization */
			  Manifold2Chart(current->s,ar->tp,current->t,nextChart);
			  current->c=next->c;

			  /* Keep track of the visited charts */
			  NewVectorElement((void*)&(next->c),&(state->traversedCharts));

			  /* Any chart traversed by the tree must be included in the list of charts for this tree */
			  AddChart2Tree(state->tree,next->c,ar);
			  			  
			  /* Ensure some overlap between neighbouring charts: current is in both charts */
			  if (config->chartAddMode!=ADD_NONE) /* in simulation mode charts are not modified */
			    EnlargeChart(current->t,nextChart);

			  if (randSample!=NULL)
			    {
			      /* Determine the advance direction in the new chart */
			      if (PointTowardRandSample(config,samplingMode,randSample,state,current,rand,ar))
				{
				  state->blocked=NO_DIR;
				  #if (GET_ATLASRRT_STATISTICS)
				    NewAtlasRRTNoAdvanceDirection((TAtlasRRTStatistics *)st);
				  #endif
				}
			    }

			  if (state->blocked==NO_BLOCKED)
			    {
			      if (ar->dynamics)
				Manifold2Chart(next->s,ar->tp,next->t,nextChart); /* project next sample to the new chart */
			      else
				{
				  /* Moved to a new chart and succesfully projected the random sample to it
				     Now recompute the advance step */
				  dif=Distance(ar->k,current->t,rand->t);
				  if (dif<state->delta)
				    memcpy(next->t,rand->t,ar->k*sizeof(double));
				  else
				    SumVectorScale(ar->k,current->t,state->delta,state->deltaParam,next->t);
				}

			      /* and just check that it is inside the ball */
			      if (Norm(ar->k,next->t)>ar->r)
				{
				  /* 'next' is out of the validity area (ball) of the current
				     chart. Its time to generate a new chart (in the previous
				     sample that is still inside the chart). */
				  state->validChart=FALSE;
				  #if (GET_ATLASRRT_STATISTICS)
				    NewAtlasRRTOutOfChart((TAtlasRRTStatistics *)st);
				  #endif
				  #if (ATLASRRT_VERBOSE>2)
				    if (!ar->parallel)
				    fprintf(stderr,"       Branch stopped (out of radius in transition)\n");
				  #endif
				}
                              #if (RELINEALIZE_DYNAMICS>1)
			      else
				{
				  /* Moved to a new chart, see if we have to re-compute the LQR policy */
				  if ((ar->dynamics)&&(ar->nda==0)&&(!config->randLQRAction)&&(randSample!=NULL))
				    {
				      #if (ATLASRRT_VERBOSE)
				        fprintf(stderr,"Computing the policy at the neighbour chart [chart: %u]\n",current->c);
				      #endif
				      UpdateLQRPolicy(pr,config,nextChart,current->t,rand->t,state,st,ds,ar);
				    }
				}
			      #endif
			    }
			  #if (GET_ATLASRRT_STATISTICS)
			  else
			    {
			      NewAtlasRRTChartBlocked((TAtlasRRTStatistics *)st);
			      #if (ATLASRRT_VERBOSE>2)
			        if (!ar->parallel)
				  fprintf(stderr,"       Branch stopped (at chart creation)\n");
			      #endif
			    }
			  #endif
			}
		    }
		}
	    }
	}
      #if (ATLASRRT_VERBOSE>2)
      else
	{
	  if (!ar->parallel)
	    {
	      if (state->blocked & DYNAMIC_ERROR)
		fprintf(stderr,"       Dynamic error\n");
	      if (state->blocked & NOT_IN_DOMAIN)
		fprintf(stderr,"       Out of dynamic domain\n");
	    }
	}
      #endif

      /* Here we have a sample that is correctly parametrized inside
	 the validity area (ball) of a given chart.
	 Now we have to check for the sample validity like in any
	 other path planner. */

      if ((state->validChart)&&(state->blocked==NO_BLOCKED)&&
	  ((ar->dynamics)||
	   (Chart2Manifold(pr,&(ar->J),next->t,
			   ar->tp,current->s,
			   next->s,nextChart)<ar->e)))
	{
	  double dp;
	  double dt;
	  boolean inDomain,tooCurved;
	  boolean trans=TRUE;

	  /* Check error curvature (only along the expansion direction) */
	  dp=DistanceTopology(ar->m,ar->tp,current->s,next->s);

	  /* In dynamics the actual displacement in tangent space may be slightly
	     different from the intended one */
	  if (ar->dynamics)
	    dt=Distance(ar->k,current->t,next->t); 
	  else
	    dt=state->delta;
	  
	  tooCurved=((dt/dp)<(1-ar->ce));
	  if (!tooCurved)
	    {
	      /* Check the bounds respect to the ambient space */
	      inDomain=((PointInBoxTopology(NULL,FALSE,ar->m,next->s,
					    epsilon,ar->tp,
					    &(ar->ambient)))&&
			(CS_WD_SIMP_INEQUALITIES_HOLD(pr,next->s,ar->w)));
	      if (inDomain)
		{
		  /* Check if the transition test is passed */
		  if (config->costF!=NULL)
		    {
		      dp=DistanceTopology(ar->m,ar->tp,current->s,next->s);
		      trans=TransitionTestRRT(pr,current->id,next->s,dp,
					      &(state->cost),
					      config->costF,config->costData,
					      &(ar->rrt));
		    }

		  if (trans)
		    {
		      /* Check the collisions (only if necessary) */
		      if (config->checkCollisions)
			{
			  boolean collision;
			  
			  CS_WD_IN_COLLISION(collision,pr,next->s,
					     current->s,ar->w);
			  if (collision)
			    state->blocked=COLLISION;
			  #if (GET_ATLASRRT_STATISTICS)
			    NewAtlasRRTCollisionCheck((TAtlasRRTStatistics *)st);
			  #endif
			}

		      if (state->blocked & COLLISION)
			{
			  #if (GET_ATLASRRT_STATISTICS)
			    NewAtlasRRTCollision((TAtlasRRTStatistics *)st);
			  #endif
			  #if (ATLASRRT_VERBOSE>2)
			    if (!ar->parallel)
			      fprintf(stderr,"       Branch stopped (collision)\n");
			  #endif
			}
		      #if (GET_ATLASRRT_GLOBAL_CURV_CHECK)
		      else
			{
			  Tchart cTmp;
			  boolean closeEnough,canInitChart;

			  /* The curvature check (tooCurved) can be computed
			     in a more accurate way than the test above.
			     This is expensive and not commontly used. */

			  /* We further check if we are able to create a
			     chart at the current sample and if this chart
			     is not too different from its parent chart. */

			  /* Create a temporary chart at 'next' */
			  canInitChart=(InitChart(pr,TRUE,&(ar->ambient),
						  ar->tp,ar->m,ar->k,
						  next->s,ar->e,ar->ce,
						  ar->r,&(ar->J),
						  ar->w,&cTmp)==0);
			  if (canInitChart)
			    {
			      /* Check if new chart respects distance
				 and angular tolerances */
			      closeEnough=CloseCharts(pr,ar->tp,
						      nextChart,&cTmp);
			      if (!closeEnough)
				{
				  /* next sample is out of the domain of the
				     current chart due to excesive curvature
				     We generate a new chart closer to the
				     area of interst. */
				  state->validChart=FALSE;
				  #if (GET_ATLASRRT_STATISTICS)
				    NewAtlasRRTLargeCurvature((TAtlasRRTStatistics *)st);
				  #endif
				  #if (ATLASRRT_VERBOSE>2)
				    if (!ar->parallel)
				      fprintf(stderr,"       Branch stopped (full curvature)\n");
				  #endif
				}
			      DeleteChart(&cTmp); /* Delete only if canInit */
			    }
			  else
			    {
			      /* We did not manage to create the chart:
				 - Point not on manifold
				 - error in QR
				 - singular point
				 (typically the last one).
				 We could implement more complex procedures
				 to skip the singular area. */
			      state->blocked=SINGULARITY;
			      #if (GET_ATLASRRT_STATISTICS)
			        NewAtlasRRTInitChartError((TAtlasRRTStatistics *)st);
			      #endif
			      #if (ATLASRRT_VERBOSE>2)
			        if (!ar->parallel)
				  fprintf(stderr,"       Branch stopped (atlas init error)\n");
			      #endif
			    }
			}
		        #endif
		    }
		  else
		    {
		      /*Transition test failed -> rejected step */
		      state->blocked=TRANSITION_TEST_FAILS;
		      #if (GET_ATLASRRT_STATISTICS)
		         NewAtlasRRTTransTestFail((TAtlasRRTStatistics *)st);
		      #endif
		      #if (ATLASRRT_VERBOSE>2)
		        if (!ar->parallel)
			  fprintf(stderr,"       Branch stopped (transition test failed)\n");
		      #endif
		    }
		}
	      else
		{
		  /* next sample is out of the domain */
		  state->blocked=NOT_IN_DOMAIN;
		  #if (GET_ATLASRRT_STATISTICS)
		    NewAtlasRRTNotInDomain((TAtlasRRTStatistics *)st);
		  #endif
		  #if (ATLASRRT_VERBOSE>2)
		    if (!ar->parallel)
		      fprintf(stderr,"       Branch stopped (out of domain)\n");
		  #endif
		}
	    }
	  else
	    {
	      /* The new sample is out of the validity area of the chart
		 due to a excesive curvature. */
	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTDirLargeCurvature((TAtlasRRTStatistics *)st);
	      #endif

	      #if (ATLASRRT_VERBOSE>2)
	        if (!ar->parallel)
		  fprintf(stderr,"       Branch stopped (curvature)\n");
	      #endif

	      state->validChart=FALSE;
	    }
	}
      else
	{
	  /* The projection from the sample in tangent space to the
	     manifold failed */
	  if ((state->validChart)&&(state->blocked==NO_BLOCKED)&&(!ar->dynamics))
	    {
	      #if (ATLASRRT_VERBOSE>2)
	        if (!ar->parallel)
		  fprintf(stderr,"       Chart2Manifold failed\n");
	      #endif

	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTNoConvergentStep((TAtlasRRTStatistics *)st);
	      #endif

	      state->validChart=FALSE;
	    }
	}
    }
}

boolean PointTowardRandSample(TAtlasRRTBranchConfig *config,
			      unsigned int samplingMode,double *randSample,
			      TAtlasRRTBranchState *state,
			      TSampleInfo *current,TSampleInfo *rand,
			      Tatlasrrt *ar)
{
  Tchart *c;
  double n;

  /* We will project 'rand' to the chat of the current sample */
  rand->c=current->c;

  /* Get current chart */
  if (state->chartInAtlas)
    c=GetAtlasChart(current->c,&(ar->atlas));
  else
    c=&(state->c);

  /* If the sample is in tangent space, it will be moved as we project it to the
     tangent space of x_near (i.e., randSample changes as we project it). 
     If the sample is on the manifold, it does not change. In other words,
     randSample is the original random sample the first time and the 
     last projected sample from then on (when sampling on the tangent space) */
  Manifold2Chart(randSample,ar->tp,rand->t,c);

#if (0)
  /* The random sample to pursue changes depending on whether it
     is on the manifold of in the tangent space */
  if ((samplingMode!=TANGENT_SAMPLING)||(config->onManifold))
    Manifold2Chart(randSample,ar->tp,rand->t,c);  /* Sample not in the tangent space. Use the orignal sample */
  else
    Manifold2Chart(rand->s,ar->tp,rand->t,c);     /* sample in the tangent space (of previous chart)
						     In the first call, this is the same as randSample */
#endif
  
  /* deltaParam: Vector from 'current' to 'rand' (in tangent space) */
  DifferenceVector(ar->k,rand->t,current->t,state->deltaParam);

  /* Ensure that the new rand far from 'current' */
  n=Norm(ar->k,state->deltaParam);
  if (n>1e-3)
    {
      Normalize(ar->k,state->deltaParam);
      /* Displace rand->t far enough, but without modifying the
         advance direction. */
      if ((samplingMode==TANGENT_SAMPLING)&&(!config->onManifold))
	{
	  if (ar->dynamics)
	    SumVectorScale(ar->k,current->t,state->distQrand,state->deltaParam,rand->t);
	  else
	    SumVectorScale(ar->k,current->t,(ar->dynamics?5.0*ar->r:state->maxLength),state->deltaParam,rand->t);
	}

      /* Update rand->s so that it correspond to the new rand->t  */
      Local2Global(rand->t,ar->tp,rand->s,c);
      
      #if (ATLASRRT_VERBOSE>2)
        if (!ar->parallel)
	  {
	    fprintf(stderr,"      Original random sample:\n");
	    PrintVector(stderr,"        x_rand",ar->m,randSample);
	    if (current->c==NO_UINT)
	      fprintf(stderr,"      Random sample moved to a temporary chart\n");
	    else
	      fprintf(stderr,"      Random sample moved to chart %u:\n",current->c);
	    #if (ATLASRRT_VERBOSE>3)
	      PrintVector(stderr,"        x0",ar->m,GetChartCenter(c));
	      PrintMatrix(stderr,"         U",ar->m,ar->k,GetChartTangentSpace(c));
	    #endif
	    PrintVector(stderr,"        x_rand",ar->m,rand->s);
	    PrintVector(stderr,"        y_rand",ar->k,rand->t);
	  }
      #endif

      /* When sampling on tangent space, we move the random sample to the tangent space of x_near and
         forget about the original sample....*/
      if ((samplingMode==TANGENT_SAMPLING)&&(!config->onManifold))
	memcpy(randSample,rand->s,sizeof(double)*ar->m);
      
      return(FALSE);
    }
  else
    {
      /* The projection of 'rand' to the current chart coincides
	 with the current sample -> the direction of advance is
	 not clear -> stop the branch extension*/
      #if (ATLASRRT_VERBOSE)
        if (!ar->parallel)
	  fprintf(stderr,"        TmpQrand reached\n");
      #endif
      return(TRUE);
    }
}

double AddSample2AtlasRRT(Tparameters *pr,unsigned int tree,
			  unsigned int *currentID,
			  unsigned int nextChart,double *nextParam,double *nextSample,
			  double dp,double cost,boolean blocked,double *action,double time,
			  unsigned int ns,double **path,double **actions,double *times,
			  Tatlasrrt *ar)
{
  double d;
  double *currentSample;
  unsigned int k;
  TSampleInfo *currentSampleInfo;
  TChartInfo *currentChartInfo;

  /* Distance to parent sample */
  currentSample=ar->si[*currentID]->s;
  d=DistanceTopology(ar->m,ar->tp,nextSample,currentSample);
  
  #if (ATLASRRT_VERBOSE>2)
    fprintf(stderr,"  New sample atlasrrt %u (dp:%f)\n",ar->ns,d);
  #endif

  /* Add the sample to the RRT */
  if (ar->ns==ar->ms)
    MEM_DUP(ar->si,ar->ms,TSampleInfo *);

  /* Store the new sample in the RRT */
  AddNodeToRRT(pr,tree,*currentID,nextSample,nextSample,&k,NULL,
	       dp,cost,blocked,action,time,
	       ns,path,actions,times,NULL,&(ar->rrt));
  if (k!=ar->ns)
    Error("Incongruent node identifier in AtlasRRT (vs RRT inside)");

  /* Set up the information for the new sample */
  NEW(ar->si[ar->ns],1,TSampleInfo);
  currentSampleInfo=ar->si[ar->ns];
  currentChartInfo=ar->ci[nextChart];

  /* Pointer to the just added sample. The sample is stored in the RRT. */
  currentSampleInfo->s=GetRRTNode(ar->ns,&(ar->rrt));
  currentSampleInfo->id=ar->ns;

  /* Parent chart: Chart at which the sample is created.
     At initialization this is the same as currentSampleInfo->c
     but currentSampleInfo->c can change as new charts are
     created and currentSampleInfo->pc will remain the same */
  currentSampleInfo->pc=nextChart;

  /* There is no chart at the new sample (yet) */
  currentSampleInfo->generateChart=0;

  /* The chart including the current sample must be associated with
     the tree including this sample. */
  AddChart2Tree(tree,nextChart,ar);

  /* Store the projection into the current chart */
  NEW(currentSampleInfo->t,ar->k,double);
  memcpy(currentSampleInfo->t,nextParam,ar->k*sizeof(double));

  /* Assign the sample to the corresponding chart */
  currentSampleInfo->c=nextChart;

  /* Add the sample to the list of samples of the corresponding chart */
  currentSampleInfo->lsc=currentChartInfo->lc;
  currentChartInfo->lc=ar->ns;

  /*Move the pointer to current to the new sample */
  *currentID=ar->ns;

  ar->ns++;

  return(d);
}

void AddChart2Tree(unsigned int tree,unsigned int chartId,Tatlasrrt* ar)
{
  if ((ar->birrt)&&(!(ar->ci[chartId]->tree&tree)))
    {
      boolean found;
      unsigned int *m,*n,**ct,i;
      
      
      ar->ci[chartId]->tree|=tree;
      if (tree==START2GOAL)
	{
	  n=&(ar->nct1);
	  m=&(ar->mct1);
	  ct=&(ar->chartsAtTree1);
	}
      else
	{
	  n=&(ar->nct2);
	  m=&(ar->mct2);
	  ct=&(ar->chartsAtTree2);
	}

      found=FALSE;
      i=0;
      while((!found)&&(i<(*n)))
	{
	  found=((*ct)[i]==chartId);
	  i++;
	}
      if (!found)
	{
	  if(*n==*m)
	    MEM_DUP(*ct,*m,unsigned int);
	  (*ct)[*n]=chartId;
	  (*n)++;
	}   
    }
}

boolean AddChart2AtlasRRT(Tparameters *pr,unsigned int tree,unsigned int it,
			  TAtlasRRTBranchConfig *config,TAtlasRRTBranchState *state,
			  TSampleInfo *currentSampleInfo,boolean *intersectParent,
			  Tatlasrrt *ar)
{
  unsigned int j,ncp,newChart;
  unsigned  nn,i,id;
  Tchart* ce;
  TChartInfo *currentChartInfo;
  unsigned int currentID;
  boolean sing;
  boolean initOK;


  #if (ATLASRRT_VERBOSE>2)
    if (!ar->parallel)
      {
	if ((config!=NULL)&&(config->chartAddMode==ADD_NONE))
	  {
	    fprintf(stderr,"     Sample at temporary chart generated a new chart:\n");
	    PrintVector(stderr,"       s",ar->m,currentSampleInfo->s);
	    PrintVector(stderr,"       t",ar->k,currentSampleInfo->t);
	  }
	else
	  {
	    fprintf(stderr,"     Chart %u generated from sample at chart %u:\n",ar->nc,currentSampleInfo->c);
	    PrintVector(stderr,"       x",ar->m,currentSampleInfo->s);
	    PrintVector(stderr,"       y",ar->k,currentSampleInfo->t);
	  }
      }
  #endif

  currentID=currentSampleInfo->id;

  if ((config!=NULL)&&(config->chartAddMode==ADD_NONE))
    {
      if (!state->chartInAtlas)
	{
	  /* Previous chart was already temporal */
	  Tchart c;

	  initOK=(InitTrustedChart(pr,TRUE,&(ar->ambient),ar->tp,ar->m,ar->k,currentSampleInfo->s,
				   ar->e,ar->ce,ar->r,&(ar->J),ar->w,&c)==0);

	  if (initOK)
	    {
	      DeleteChart(&(state->c));
	      CopyChart(&(state->c),&c);
	      DeleteChart(&c);
	    }
	}
      else
	initOK=(InitTrustedChart(pr,TRUE,&(ar->ambient),ar->tp,ar->m,ar->k,currentSampleInfo->s,
				 ar->e,ar->ce,ar->r,&(ar->J),ar->w,&(state->c))==0);
      if (initOK)
	{
	  /* Sample not in the tree: temporary sample. The new chart is defined on a
	     temporary sample. The sample is the center of the chart (just enforce it) */
	  currentSampleInfo->c=NO_UINT;
	  currentSampleInfo->pc=NO_UINT;
	  for(j=0;j<ar->k;j++)
	    currentSampleInfo->t[j]=0;
	  currentSampleInfo->generateChart=NO_UINT;
	  *intersectParent=TRUE;
	  state->chartInAtlas=FALSE;
	}
    }
  else
    {
      /* need to generate a new chart at the current sample */
      /* change cID */
      ncp=ar->nc;

      /* This does not enforce the neighbouring relation with parent chart !!
	 but tries to detect singularities, if any (and enabled) */
      newChart=AddTrustedChart2Atlas(pr,currentSampleInfo->s,
				     currentSampleInfo->pc,&sing,&(ar->atlas));

      initOK=(newChart!=NO_UINT);

      if (initOK)
	{
	  ar->nc=GetAtlasNumCharts(&(ar->atlas));

	  /* Check if the newChart is neighbour with its parent chart */
	  if (ncp<(ar->birrt?2:1))
	    *intersectParent=TRUE; /* for the chart at the query points -> do not check */
	  else
	    {
	      (*intersectParent)=FALSE;
	      ce=GetAtlasChart(newChart,&(ar->atlas));
	      if (SingularChart(ce))
		Warning("Singular chart in AtlasRRT (decrease epsilon?)");
	      nn=ChartNumNeighbours(ce);

	      for(i=0;((!(*intersectParent))&&(i<nn));i++)
		{
		  id=ChartNeighbourID(i,ce);
		  if ((id!=NO_UINT)&&(id==currentSampleInfo->pc))
		    (*intersectParent)=TRUE;
		}

	      if ((!(*intersectParent))&&(currentSampleInfo->pc!=NO_UINT))
		{
		  Tchart *parentChart;

		  parentChart=GetAtlasChart(currentSampleInfo->pc,&(ar->atlas));
		  ForceChartCut(pr,ar->tp,&(ar->ambient),newChart,ce,currentSampleInfo->pc,parentChart);
		}
	    }

	  /* expand chart info if necessary */
	  if (ar->nc>ar->mc)
	    {
	      ar->mc=ar->nc+INIT_NUM_CHARTS;
	      MEM_EXPAND(ar->ci,ar->mc,TChartInfo *);
	    }

	  /* and initialize an empty list of samples for the new charts */
	  for(j=ncp;j<ar->nc;j++)
	    {
	      NEW(ar->ci[j],1,TChartInfo);
	      ar->ci[j]->lc=NO_UINT;
	      ar->ci[j]->it=it;
	      ar->ci[j]->tree=0; /* chart in no tree initially */
	      AddChart2Tree(tree,j,ar);
	    }

	  /* Now that the list of samples for the new charts is already initialized,
	     we assign samples to the newly created charts */
	  for(j=ncp;j<ar->nc;j++)
	    PopulateWithSamples(pr,j,ar);

	  /* Up to here we accomodated the new chart in the atlas and populated it
	     with samples. Now we have to set up the information in the sample. */

	  if (currentID==NO_UINT)
	    {
	      /* Sample not in the tree: temporary sample. The new chart is defined on a
		 temporary sample. The sample is the center of the chart (just enforce it) */
	      currentSampleInfo->c=newChart;
	      currentSampleInfo->pc=newChart;
	      for(j=0;j<ar->k;j++)
		currentSampleInfo->t[j]=0;
	      /* 1+newChart -> we can find out which chart was created at each
		 sample just by substracting one (used for debug). */
	      currentSampleInfo->generateChart=1+newChart;
	    }
	  else
	    {
	      TSampleInfo *sampleInTree;

	      /* A sample that is in the tree -> operate with the copy in the tree */

	      sampleInTree=ar->si[currentID];
	      sampleInTree->generateChart=1+newChart; /* just created a chart on the tree sample */
	      if (sampleInTree->c!=newChart)
		{
		  unsigned int n;
		  boolean found;
		  Tchart *ce;
		  TChartInfo *newChartInfo;
		  TSampleInfo *previousSampleInfo,*sampleInfo;

		  /* If for some reason the sample in the tree is not assigned to the
		     new chart, correct the situation, stealing the sample from
		     the chart where it is currently assigned */

		  n=sampleInTree->c; /*Chart from where to steal the center*/
		  currentChartInfo=ar->ci[n];
		  newChartInfo=ar->ci[newChart]; /* The new chart -> this must receive the sample */

		  /* iterate over the samples assigned to 'currentChart' until we find
		     'currentSampleID'. Then we re-assign it to 'newChart', properly adjusting
		     the lists of samples. */

		  previousSampleInfo=NULL; /* previous sample in the list */
		  j=currentChartInfo->lc;  /* first sample in the list */
		  found=FALSE;
		  while((j!=NO_UINT)&&(!found))
		    {
		      sampleInfo=ar->si[j];
		      if (j==currentID)
			{
			  /* remove the sample from the list of chart c*/
			  if (previousSampleInfo==NULL)
			    currentChartInfo->lc=sampleInfo->lsc;
			  else
			    previousSampleInfo->lsc=sampleInfo->lsc;

			  /* add to the list of the new chart */
			  sampleInfo->lsc=newChartInfo->lc;
			  newChartInfo->lc=j;
			  sampleInfo->c=newChart;

			  /* Project the sample to the chart. This must result
			     in zero but....*/
			  ce=GetAtlasChart(newChart,&(ar->atlas));
			  Manifold2Chart(sampleInfo->s,ar->tp,sampleInfo->t,ce);
			  EnlargeChart(sampleInfo->t,ce);

			  found=TRUE;
			}
		      else
			{
			  /* Move to next */
			  previousSampleInfo=sampleInfo;
			  j=sampleInfo->lsc;
			}
		    }
		  if (!found)
		    Error("A sample is not where it should be");
		}

	      if (currentSampleInfo!=sampleInTree)
		{
		  /* The input parameter is a copy of the node in the tree
		     We have to update the copy too (basically copy the
		     sample, the chartID, the parent chart, and the
		     projection to the chart) */
		  SetSampleInfo(ar->m,ar->k,currentSampleInfo,sampleInTree);
		}
	    }
	}
    }
  return(initOK);
}

void PopulateWithSamples(Tparameters *pr,unsigned int id,Tatlasrrt *ar)
{
  Tchart *c,*c1,*ce;
  unsigned int i,j,jt,n,nn,ne;
  double *t;
  double epsilon;
  TSampleInfo *currentSampleInfo;
  TSampleInfo *previousSampleInfo;
  TChartInfo *currentChartInfo;
  TChartInfo *newChartInfo;

  epsilon=GetParameter(CT_EPSILON,pr);

  NEW(t,ar->k,double);

  c=GetAtlasChart(id,&(ar->atlas));
  nn=ChartNumNeighbours(c);

  for(i=0;i<nn;i++)
    {
      /* The neighbouring chart from where to steal some samples */
      n=ChartNeighbourID(i,c);
      if (n!=NO_UINT)
	{
	  currentChartInfo=ar->ci[n];
	  c1=GetAtlasChart(n,&(ar->atlas));

	  previousSampleInfo=NULL; /* previous sample in the list */
	  j=currentChartInfo->lc; /* first sample in the list */
	  while(j!=NO_UINT)
	    {
	      currentSampleInfo=ar->si[j];
	      ne=DetermineChartNeighbour(epsilon,currentSampleInfo->t,c1);
	      if (ne!=NO_UINT)
		{
		  /* Sample 'j' is not any more in chart 'c1' (chart 'n') but in a
		     neighbouring one, typically the one just created (ne==id),
		     but can be any other neighbour */

		  newChartInfo=ar->ci[ne]; /* This should be the new chart */

		  #if (_DEBUG>2)
		    fprintf(stderr,"    Sample %u moves from chart %u to %u\n",j,n,ne);
		  #endif

		  /* Typically 'ce' will be 'c', but not for sure */
		  ce=GetAtlasChart(ne,&(ar->atlas));
		  Manifold2Chart(currentSampleInfo->s,ar->tp,currentSampleInfo->t,ce);
		  EnlargeChart(currentSampleInfo->t,ce);

		  currentSampleInfo->c=ne;

		  /* we will change lsc[j] in the following -> backup it */
		  jt=currentSampleInfo->lsc;

		  /* remove the sample from the list of chart c*/
		  if (previousSampleInfo==NULL)
		    currentChartInfo->lc=currentSampleInfo->lsc;
		  else
		    previousSampleInfo->lsc=currentSampleInfo->lsc;

		  /* add to the list of chart 'ne' (typically ne==id) */
		  currentSampleInfo->lsc=newChartInfo->lc;
		  newChartInfo->lc=j;

		  /* The chart importing the sample must be associated with
		     the tree including this sample. */
		  AddChart2Tree(GetRRTNodeTree(j,&(ar->rrt)),ne,ar);

		  /* Set 'j' to the next in the list of samples for the current
		     chart (previously backed up) */
		  j=jt;

		  /* Since we removed one element from the list the
		     previous pointed by 'previousSampleInfo' remains the same. */
		}
	      else
		{
		  /* move to next sample in the list of samples assigned to
		     chart 'n' */
		  previousSampleInfo=currentSampleInfo;
		  j=currentSampleInfo->lsc;
		}
	    }
	}
    }

  free(t);
}

unsigned int ReconstructAtlasRRTPath(Tparameters *pr,unsigned int sID,
				     double *pl,unsigned int *ns,double ***path,Tatlasrrt *ar)
{
  unsigned int nv,nvs,i,ms;
  signed int j;
  double *o,c;
  boolean *systemVars;
  unsigned int lns;
  double **lpath;
  unsigned int p;
  TAtlasRRTBranchConfig configConnect;
  TAtlasRRTBranchState stateConnect;

  InitBranchConfig(CONNECT_SAFE,&configConnect);

  *pl=0;

  /* Get the sample in the tree close to the goal */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,ar->w);
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }

  InitSamples(&ms,ns,path);

  i=sID;
  while (i!=NO_UINT)
    {
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,ar->si[i]->s,&o,ar->w);
      AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
      free(o);
      p=GetRRTParent(i,&(ar->rrt));
      if (p!=NO_UINT)
	{
	  /* Check that the two samples can be actually connected and
	     measure the distance between them. */
	  c=AddBranchToAtlasRRT(pr,NO_UINT,&configConnect,0,NULL,NULL,NULL,NULL,NULL,p,ar->si[i]->s,NULL,NULL,
				&stateConnect,&lns,&lpath,NULL,NULL,NULL,NULL,NULL,ar);

	  if (!stateConnect.reachedQrand)
	    Warning("Path segment could not be reconstructed in ReconstructAtlasRRTPath");

	  (*pl)+=c;
	  #if (ATLASRRT_VERBOSE)
	    fprintf(stderr,"{%u->%u}[%g]",i,p,c);
	  #endif

	  for(j=lns-1;j>=0;j--)
	    {
	      CS_WD_REGENERATE_ORIGINAL_POINT(pr,lpath[j],&o,ar->w);
	      AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
	      free(o);
	    }

	  DeleteSamples(lns,lpath);
	}
      i=p;
    }
  ReverseSamples(*ns,*path);

  free(systemVars);

  return(nvs);
}

unsigned int Steps2PathinAtlasRRT(Tparameters *pr,Tvector *steps,double *pl,double *pc,
				  unsigned int *ns,double ***path,Tatlasrrt *ar)
{
  unsigned int nv,nvs,ms,n,i,j,k,current,next;
  double *o,c;
  boolean *systemVars;
  unsigned int lns;
  double **lpath;
  double epsilon,dc;
  double delta;
  TAtlasRRTBranchConfig configConnect;
  TAtlasRRTBranchState stateConnect;

  InitBranchConfig(CONNECT_SAFE,&configConnect);
  delta=GetParameter(CT_DELTA,pr);
  
  #if (ATLASRRT_VERBOSE)
    fprintf(stderr,"*****************************************************\n");
    fprintf(stderr,"Defining the solution path\n");
    fprintf(stderr,"*****************************************************\n");
  #endif

  *pl=0; /* path length */
  if (pc!=NULL) /* path cost (mechanical work) */
    {
      *pc=0;
      epsilon=GetParameter(CT_EPSILON,pr);
    }

  /* Identify system variables */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,ar->w);
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }

  InitSamples(&ms,ns,path);

  current=*(unsigned int *)GetVectorElement(0,steps);
  n=VectorSize(steps);
  k=1;
  while (k<n)
    {
      next=*(unsigned int *)GetVectorElement(k,steps);

      CS_WD_REGENERATE_ORIGINAL_POINT(pr,ar->si[current]->s,&o,ar->w);
      AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
      free(o);

      c=AddBranchToAtlasRRT(pr,NO_UINT,&configConnect,0,NULL,NULL,NULL,NULL,NULL,current,ar->si[next]->s,NULL,NULL,
			    &stateConnect,&lns,&lpath,NULL,NULL,NULL,NULL,NULL,ar);

      #if (ATLASRRT_VERBOSE)
        fprintf(stderr,"{%u->%u}[%g]",current,next,c);
      #endif

      (*pl)+=c; /* Update the path length */
      if(pc!=NULL) /* Update the path cost (mechanical work) */
	{
	  dc=GetRRTNodeCost(current,&(ar->rrt))-GetRRTNodeCost(next,&(ar->rrt));
	  (*pc)+=(dc>0?dc:0)+epsilon*c;
	}

      if (stateConnect.distQrand>delta)
	Warning("Path segment could not be reconstructed in Steps2PathinAtlasRRT");
      else
	{
	  for(j=0;j<lns;j++)
	    {
	      CS_WD_REGENERATE_ORIGINAL_POINT(pr,lpath[j],&o,ar->w);
	      AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
	      free(o);
	    }
	  DeleteSamples(lns,lpath);
	}

      current=next;
      k++;
    }

  free(systemVars);

  #if (ATLASRRT_VERBOSE)
    fprintf(stderr,"*****************************************************\n");
    fprintf(stderr,"*****************************************************\n");
  #endif

  return(nvs);
}

void SmoothPathInAtlasRRT(Tparameters *pr,unsigned int sID,Tatlasrrt* ar)
{
  unsigned int i,j,k,l,s,n,n1,n2,o;
  unsigned int *path;
  double c12,c2_new,c1,c2;
  TAtlasRRTBranchConfig configConnect;
  TAtlasRRTBranchState stateConnect;

  InitBranchConfig(CONNECT_SAMPLES,&configConnect);

  n=StepsToRoot(sID,&(ar->rrt));
  NEW(path,n,unsigned int);
  l=n-1;
  s=sID;
  while (s!=NO_UINT)
    {
      path[l]=s;
      s=GetRRTParent(s,&(ar->rrt));
      l--;
    }
  s=n; /* initial size of the path */
  for(l=0;l<s;l++)
    {
      /* Select a node at random in the path */
      i=randomMax(n-2);
      j=i+1+randomMax(n-2-i);

      n1=path[i];
      n2=path[j];

      c1=GetRRTNodeCost(n1,&(ar->rrt));
      c2=GetRRTNodeCost(n2,&(ar->rrt));

      /* Try to connect the two samples with a shorcut and measure its length */
      configConnect.maxLength=c2-c1;
      configConnect.maxTopt=INF;
      c12=AddBranchToAtlasRRT(pr,NO_UINT,&configConnect,0,NULL,NULL,NULL,NULL,NULL,n1,ar->si[n2]->s,NULL,NULL,
			      &stateConnect,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);

      /* If node n2 can be reached from node n1 */
      if (stateConnect.reachedQrand)
	{
	  /* and the cost is smaller */
	  c2_new=c1+c12;
	  if (c2_new<c2)
	    {
	      /* Set n1 as a parent of n2*/
	      SetRRTNodeCost(n2,c12,c2_new,&(ar->rrt));
	      SetRRTParent(n2,n1,&(ar->rrt));

	      /* Shrink the path */
	      for(k=j,o=i+1;k<n;k++,o++)
		path[o]=path[k];
	      n=o;
	    }
	}
    }
  free(path);
}

boolean RandomPointInAtlasTree(Tparameters *pr,
			       double scale,unsigned int tree,
			       unsigned int *nm,double *t,double *p,
			       Tatlasrrt* ar)
{
  boolean havePoint;

  /* This is the place where to implement different sampling strategies,
     if desired. We can, for instance, we can select the charts taking
     into account the number of samples (more samples, less probability
     of selecting them). This will approximate the AtlasRRT to an EST. */

  if ((ar->birrt)&&(tree!=BOTHTREES))
    {
      /* If the sampling radius is potentially different for each chart,
	 we have to take into account the size of sampling area for each chart to
         uniformly sample on the part of the C-space explored so far. */
      #if (ADJUST_SA==1)
      {
	double *w,s;
	unsigned int i,nc;
	unsigned int *c;

	if (tree==START2GOAL)
	  {
	    nc=ar->nct1;
	    c=ar->chartsAtTree1;
	  }
	else
	  {
	    nc=ar->nct2;
	    c=ar->chartsAtTree2;
	  }
	NEW(w,nc,double);
	s=0.0;
	for(i=0;i<nc;i++)
	  {
	    /* The 'scale' factor, if any affects all charts and, thus it can be
	       ruled out. */
	    w[i]=GetChartSamplingRadius(GetAtlasChart(c[i],&(ar->atlas)));
	    w[i]=pow(w[i],(double)ar->k);
	    s+=w[i];
	  }
	*nm=c[randomWithDistribution(nc,s,w)];
	free(w);
      }
      #else
        /* Uniform distribution on charts of the tree */
        if (tree==START2GOAL)
	  *nm=ar->chartsAtTree1[randomMax(ar->nct1-1)];
	else
	  *nm=ar->chartsAtTree2[randomMax(ar->nct2-1)];
      #endif

      /* Get a point from the selected chart */
      havePoint=RandomPointInChart(pr,scale,ar->tp,t,p,GetAtlasChart(*nm,&(ar->atlas)));
    }
  else
    {
      double *w=NULL;

      #if (ADJUST_SA==1)
      {
	double s;
	unsigned int i,nc;

	nc=GetAtlasNumCharts(&(ar->atlas));
	NEW(w,nc,double);
	s=0.0;
	for(i=0;i<nc;i++)
	  {
	    w[i]=GetChartSamplingRadius(GetAtlasChart(i,&(ar->atlas)));
	    w[i]=pow(w[i],(double)ar->k);
	    s+=w[i];
	  }
	*nm=randomWithDistribution(nc,s,w);
      }
      #endif

      havePoint=RandomPointInAtlas(pr,scale,w,nm,t,p,&(ar->atlas));

      #if (ADJUST_SA==1)
        free(w);
      #endif
    }

  return(havePoint);
}

void PlotQrand(Tparameters *pr,char *prefix,unsigned int inear,
	       unsigned int c_rand,double *t_rand,double *x_rand,
	       unsigned int xID,unsigned int yID,unsigned int zID,
	       Tatlasrrt *ar)
{
  Tfilename fplot;
  double *point,*center,*near;
  double *o1,*o2,*o3;
  Tchart *chart;
  Tcolor color;
  Tplot3d p3d;
  double x[2],y[2],z[2];

  CreateFileName(NULL,prefix,"_qrand",PLOT3D_EXT,&fplot);
  fprintf(stderr,"Plotting Qrand to                 : %s\n",GetFileFullName(&fplot));

  NewColor(1,0,1,&color); /*magenta*/
  InitPlot3d(GetFileFullName(&fplot),FALSE,0,NULL,&p3d);
  DeleteFileName(&fplot);

  NEW(point,ar->m,double);
  chart=GetAtlasChart(c_rand,&(ar->atlas));

  Local2Global(t_rand,ar->tp,point,chart); /* point must be the same as x_rand */
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,point,&o1,ar->w);

  center=GetChartCenter(chart);
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,center,&o2,ar->w);

  StartNew3dObject(&color,&p3d);

  /* A large cross at x_rand  */
  x[0]=o1[xID]-0.15;
  y[0]=o1[yID];
  z[0]=o1[zID];

  x[1]=o1[xID]+0.15;
  y[1]=o1[yID];
  z[1]=o1[zID];

  PlotVect3d(2,x,y,z,&p3d);

  x[0]=o1[xID];
  y[0]=o1[yID]-0.15;
  z[0]=o1[zID];

  x[1]=o1[xID];
  y[1]=o1[yID]+0.15;
  z[1]=o1[zID];

  PlotVect3d(2,x,y,z,&p3d);

  x[0]=o1[xID];
  y[0]=o1[yID];
  z[0]=o1[zID]-0.15;

  x[1]=o1[xID];
  y[1]=o1[yID];
  z[1]=o1[zID]+0.15;

  PlotVect3d(2,x,y,z,&p3d);

  /* A line from x_rand to its chart center */
  x[0]=o1[xID];
  y[0]=o1[yID];
  z[0]=o1[zID];

  x[1]=o2[xID];
  y[1]=o2[yID];
  z[1]=o2[zID];

  PlotVect3d(2,x,y,z,&p3d);

  /* A line to x_near */
  near=ar->si[inear]->s;
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,near,&o3,ar->w);

  x[0]=o1[xID];
  y[0]=o1[yID];
  z[0]=o1[zID];

  x[1]=o3[xID];
  y[1]=o3[yID];
  z[1]=o3[zID];

  PlotVect3d(2,x,y,z,&p3d);

  DeleteColor(&color);
  Close3dObject(&p3d);
  ClosePlot3d(FALSE,&p3d);

  free(o1);
  free(o2);
  free(o3);
  free(point);
}

void PlotConnection(Tparameters *pr,char *prefix,
		    unsigned int target,unsigned int near,unsigned int end,
		    unsigned int xID,unsigned int yID,unsigned int zID,
		    Tatlasrrt *ar)
{
  Tfilename fplot;
  double *point;
  double *o1,*o2,*o3;
  Tcolor color;
  Tplot3d p3d;
  double x[2],y[2],z[2];

  CreateFileName(NULL,prefix,"_connect",PLOT3D_EXT,&fplot);
  fprintf(stderr,"Plotting connection to            : %s\n",GetFileFullName(&fplot));

  NewColor(1,0,1,&color); /*magenta*/
  InitPlot3d(GetFileFullName(&fplot),FALSE,0,NULL,&p3d);
  DeleteFileName(&fplot);

  point=ar->si[target]->s;
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,point,&o1,ar->w);

  point=ar->si[near]->s;
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,point,&o2,ar->w);

  point=ar->si[end]->s;
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,point,&o3,ar->w);

  StartNew3dObject(&color,&p3d);

  x[0]=o1[xID];
  y[0]=o1[yID];
  z[0]=o1[zID];

  x[1]=o2[xID];
  y[1]=o2[yID];
  z[1]=o2[zID];

  PlotVect3d(2,x,y,z,&p3d);

  x[0]=o1[xID];
  y[0]=o1[yID];
  z[0]=o1[zID];

  x[1]=o3[xID];
  y[1]=o3[yID];
  z[1]=o3[zID];

  PlotVect3d(2,x,y,z,&p3d);

  DeleteColor(&color);
  Close3dObject(&p3d);
  ClosePlot3d(FALSE,&p3d);

  free(o1);
  free(o2);
  free(o3);
}

void SaveAtlasRRTSampleInfo(FILE *f,TSampleInfo *si,Tatlasrrt *ar)
{
  unsigned int i;

  fprintf(f,"%u\n",si->id);
  for(i=0;i<ar->k;i++)
    fprintf(f,"%.16f ",si->t[i]);
  fprintf(f,"\n");
  fprintf(f,"%u\n",si->pc);
  fprintf(f,"%u\n",si->c);
  fprintf(f,"%u\n",si->generateChart);
  fprintf(f,"%u\n",si->lsc);
}

void SaveAtlasRRTChartInfo(FILE *f,TChartInfo *ci,Tatlasrrt *ar)
{
  fprintf(f,"%u\n",ci->lc);
  fprintf(f,"%u\n",ci->tree);
  fprintf(f,"%u\n",ci->it);
}

void LoadAtlasRRTSampleInfo(FILE *f,TSampleInfo *si,Tatlasrrt *ar)
{
  unsigned int i;

  fscanf(f,"%u",&(si->id));
  si->s=GetRRTNode(si->id,&(ar->rrt));
  NEW(si->t,ar->k,double);
  for(i=0;i<ar->k;i++)
    fscanf(f,"%lf",&(si->t[i]));
  fscanf(f,"%u",&(si->pc));
  fscanf(f,"%u",&(si->c));
  fscanf(f,"%u",&(si->generateChart));
  fscanf(f,"%u",&(si->lsc));
}

void LoadAtlasRRTChartInfo(FILE *f,TChartInfo *ci,Tatlasrrt *ar)
{
  fscanf(f,"%u",&(ci->lc));
  fscanf(f,"%u",&(ci->tree));
  fscanf(f,"%u",&(ci->it));
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void InitAtlasRRT(Tparameters *pr,boolean parallel,double *ps,unsigned int mode,boolean graph,
		  double *pg,TAtlasBase *w,Tatlasrrt *ar)
{
  unsigned int i;
  boolean intersectParent;
  TSampleInfo *currentSampleInfo;

  /*************************************************************/
  /* Init the basic AtlasRRT information */
  ar->w=w;
  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&(ar->ambient),ar->w);
  ar->m=GetBoxNIntervals(&(ar->ambient));
  ar->e=GetParameter(CT_E,pr);
  ar->ce=GetParameter(CT_CE,pr);
  ar->r=GetParameter(CT_R,pr);
  /* Exploration trees are forced to be one-directional */

  ar->dynamics=(unsigned int)GetParameter(CT_DYNAMICS,pr);
  ar->birrt=((!EXPLORATION_RRT)&&(mode!=ONE_TREE));
  if (!ar->birrt)
    mode=ONE_TREE;

  if (ar->dynamics)
    ar->nda=(unsigned int)GetParameter(CT_N_DYNAMIC_ACTIONS,pr);
  else
    ar->nda=0;

  #ifdef _OPENMP
    if ((ar->dynamics)&&(ar->nda==0))
      ar->parallel=FALSE;
    else
      ar->parallel=(omp_get_max_threads()>1?parallel:FALSE);
  #else
    ar->parallel=FALSE;
  #endif
  
  /*************************************************************/
  /* Init the Atlas */
  /* The atlas is initilized on the initial point only, latter
     on we add a chart for the final point if the AtlasRRT is
     bidirectional. */
  if (!InitAtlasFromPoint(pr,FALSE,TRUE,ps,w,&(ar->atlas)))
    Error("Can not start the atlas at the given point");
  ar->mc=INIT_NUM_CHARTS;

  ar->nc=GetAtlasNumCharts(&(ar->atlas));

  /* Note that InitAtlasFromPoint can change this parameter */
  ar->k=(unsigned int)GetParameter(CT_N_DOF,pr);

  /*************************************************************/
  /* Since atlas are defined on the simplified system we get the
     corresponding Jacobian. */
  CS_WD_GET_SIMP_JACOBIAN(pr,&(ar->J),ar->w);

  /*************************************************************/
  /* Space for dynamic computations */
  if (ar->dynamics)
    {
      unsigned int nt;

      ar->dge=GetParameter(CT_DYNAMIC_GOAL_ERROR,pr);

      #ifdef _OPENMP
        /* When the AtlasRRT is executed in parallel: exploring actions
	   in parallel or computing finite differences (inside dynamics)
	   in parallel. */
        if (ar->parallel)
	  nt=omp_get_max_threads();
	else
	  nt=1;
      #else
        nt=1;
      #endif

      NEW(ar->ds,nt,TDynamicSpace);
      for(i=0;i<nt;i++)
	InitDynamicSpace(pr,ar->parallel,&(ar->J),ar->w,&(ar->ds[i])); /* This requires the Jacobian!! */

      ar->da=ActionSpaceDimension(ar->ds);	
    }
  else
    {
      /* these fields should not be used but must be initialized anyway */
      ar->dge=INF;
      ar->ds=NULL;
      ar->da=0;
    }

  /*************************************************************/
  /* Init the RRT */
  /* This verifies that the initial point are valid (on
     the manifold, collision free, in domain,...). It also
     checks this for the final point on bidirectional RRTs */
  ar->ms=INIT_NUM_SAMPLES_RRT;
  InitRRT(pr,ar->parallel,FALSE,ps,mode,graph,pg,ar->m,ar->da,w,&(ar->rrt));
  ar->ns=GetRRTNumNodes(&(ar->rrt));

  /*************************************************************/
  /* Init the mapping from samples to charts */
  NEW(ar->ci,ar->mc,TChartInfo*);
  for(i=0;i<ar->nc;i++)
    {
      NEW(ar->ci[i],1,TChartInfo);
      ar->ci[i]->lc=NO_UINT; /* No samples in any chart */
      ar->ci[i]->tree=START2GOAL;
      ar->ci[i]->it=0;
    }

  NEW(ar->si,ar->ms,TSampleInfo*);

  /* InitSampleInfo(0) */
  NEW(ar->si[0],1,TSampleInfo);
  /* This sets t[0] to zero (sample[0] is the center of the first chart) */
  currentSampleInfo=ar->si[0];

  NEW(currentSampleInfo->t,ar->k,double);
  for(i=0;i<ar->k;i++)
    currentSampleInfo->t[i]=0.0;

  /* Chart 0 is not generated from any other chart */
  currentSampleInfo->pc=NO_UINT;

  /* Pointer to the first sample in the RRT */
  currentSampleInfo->s=GetRRTNode(0,&(ar->rrt));
  currentSampleInfo->id=0;

  /* assign the first sample to the first chart */
  currentSampleInfo->c=0; /* fist sample is in chart 0 */
  ar->ci[0]->lc=0; /* list of samples for chart 0 start at sample 0 */
  currentSampleInfo->lsc=NO_UINT; /* and there is no other sample next */

  /* we have a chart on sample 0 */
  currentSampleInfo->generateChart=1;

  /* end InitSampleInfo(0) */

  /*************************************************************/
  /* Init the mapping betwen charts and trees */
  if (ar->birrt)
    {
      /* InitSampleInfo(1) */
      NEW(ar->si[1],1,TSampleInfo);
      currentSampleInfo=ar->si[1];

      /* The goal samples has param 0 in its own chart */
      NEW(currentSampleInfo->t,ar->k,double);

      for(i=0;i<ar->k;i++)
	currentSampleInfo->t[i]=0.0;

      /* Allocate the samples 2 tree mapping  */
      ar->mct1=ar->mc;
      NEW(ar->chartsAtTree1,ar->mct1,unsigned int);

      ar->mct2=ar->mc;
      NEW(ar->chartsAtTree2,ar->mct2,unsigned int);

      /* Assign char 0 to the first tree */
      ar->chartsAtTree1[0]=0;
      ar->nct1=1;

      ar->nct2=0;
      /* The chart for the goal sample is added to the tree
	 using AddChart2AtlasRRT (see below) and this automatically
	 updates ar->chartsAtTree2, ar->nct2,...*/

      /* Chart 1 is not generated from any other chart */
      currentSampleInfo->pc=NO_UINT;

      /* Pointer to the sample in the RRT */
      currentSampleInfo->s=GetRRTNode(1,&(ar->rrt));
      currentSampleInfo->id=1;

      /* By setting c[1]=1, AddChart2AtlasRRT does not
	 re-assigns the new sample. We do it manually
	 after the chart creation. */
      currentSampleInfo->c=1;

      /* This sets currentSampleInfo->generateChart to 1 */
      if (!AddChart2AtlasRRT(pr,GOAL2START,0,NULL,NULL,currentSampleInfo,&intersectParent,ar))
	Error("Could not init the AtlasRRT on the given point (is it singular? decrease epsilon?)");

      /* Manually assign sample 1 to chart 1 */
      ar->ci[1]->lc=1;
      currentSampleInfo->lsc=NO_UINT;

      /* end InitSampleInfo(1) */
    }

  /*************************************************************/
  /* Get the topology for all variables */
  ar->tp=GetRRTTopology(&(ar->rrt));
  
  /*************************************************************/
  /* Get the weights for all variables */
  ar->weights=GetRRTWeights(&(ar->rrt));
}

boolean AtlasRRTSample(Tparameters *pr,unsigned int samplingMode,
		       unsigned int it,unsigned int tree,
		       double *goal,double scale,boolean *exploration,boolean *onManifold,
		       unsigned int *c_rand,double *t_rand,double *x_rand,
		       TAtlasRRTStatistics *arst,Tatlasrrt *ar)
{
  boolean expand2Goal,validSample;
  #if (ATLASRRT_VERBOSE)
    unsigned int s;

    fprintf(stderr,"  Generating sample\n");
  #endif

  *onManifold=FALSE; /* In general this funcion does not generate samples on the manifold (just close to it) */
    
  expand2Goal=((goal!=NULL)&&((it==0)||((!ar->birrt)&&(randomDouble()<0.01))));

  if (expand2Goal)
    {
      memcpy(x_rand,goal,ar->m*sizeof(double));
      #if (GET_ATLASRRT_STATISTICS)
        NewAtlasRRTRandomSample(arst);
      #endif
      #if (ATLASRRT_VERBOSE)
        fprintf(stderr,"    Expanding to goal-----------------------------------------------------------------\n");
      #endif
      *exploration=FALSE;
      *c_rand=NO_UINT;
    }
  else
    {
      #if (ATLASRRT_VERBOSE)
        s=0;
      #endif
      switch(samplingMode)
	{
	case AMBIENT_SAMPLING:
	case KDTREE_SAMPLING:
	  do {
	    RRTSample(samplingMode,tree,NULL,x_rand,NULL,&(ar->rrt));
	    validSample=CS_WD_SIMP_INEQUALITIES_HOLD(pr,x_rand,ar->w);
	    #if (ATLASRRT_VERBOSE)
	      s++;
	    #endif
	    #if (GET_ATLASRRT_STATISTICS)
	      NewAtlasRRTRandomSample(arst);
	      if (!validSample)
		NewAtlasRRTSampleRejection1(arst);
	    #endif
	  } while (!validSample);
	  *exploration=FALSE;
	  *c_rand=NO_UINT;
	  #if (ATLASRRT_VERBOSE)
	    fprintf(stderr,"  Random point in ambient. Rej: %u\n",s);
	  #endif
	  break;

	case TANGENT_SAMPLING:
	  do {
	    validSample=RandomPointInAtlasTree(pr,scale,tree,c_rand,t_rand,x_rand,ar);
	    #if (ATLASRRT_VERBOSE)
	      s++;
	    #endif
	    #if (ADJUST_SA==1)
	      if (!validSample)
		DecreaseChartSamplingRadius(GetAtlasChart(*c_rand,&(ar->atlas)));
	    #endif
	    #if (GET_ATLASRRT_STATISTICS)
	      NewAtlasRRTRandomSample(arst);
	      if (!validSample)
		NewAtlasRRTSampleRejection1(arst);
	    #endif
	  } while (!validSample);

	  #if (ADJUST_SA==1)
	    IncreaseChartSamplingRadius(GetAtlasChart(*c_rand,&(ar->atlas)));
	  #endif
	  *exploration=(Norm(ar->k,t_rand)>ar->r);

	  if (!(*exploration))
	    {
	      double *p;
	      
	      /* Move the sample to the manifold (only if we are close to the chart center) */
	      NEW(p,ar->m,double);
	      if (Chart2Manifold(pr,&(ar->J),t_rand,ar->tp,x_rand,p,GetAtlasChart(*c_rand,&(ar->atlas)))<INF)
		{
		  memcpy(x_rand,p,ar->m*sizeof(double));
		  *onManifold=TRUE;
		}
	      
	      free(p);
	    }
	  
	  #if (ATLASRRT_VERBOSE)
	    fprintf(stderr,"  Random point on chart %u (rej: %u) [%g:%s, %s]\n",*c_rand,s,
		    Norm(ar->k,t_rand),(*exploration?"exp":"non-exp"),(*onManifold?"tangent":"manifold"));
	  #endif
	  break;
	default:
	  Error("Unknow sampling mode in AtlasRRTSample");
	  break;
	}
    }

  return(expand2Goal);
}

boolean AtlasRRTValidateSample(Tparameters *pr,unsigned int c_rand,double *t_rand,double *x_rand,
			       unsigned int tree,boolean expand2goal,
			       unsigned int lastNN2Goal,double *goal,double l,double *h,unsigned int *i_near,
			       TAtlasRRTStatistics *arst,Tatlasrrt *ar)
{
  boolean validSample=TRUE;

  #if (ATLASRRT_VERBOSE)
    fprintf(stderr,"  Validating sample\n");
  #endif

  /* check if the sample in invalid due to a heuristic used in optimal path planning */
  if ((expand2goal)||(goal==NULL))
    *h=0;
  else
    {
      *h=DistanceTopology(ar->m,ar->tp,x_rand,goal);
      if ((l<INF)&&((HEURISTIC_RRT_STAR)&(1)))
	validSample=((DistanceTopology(ar->m,ar->tp,ar->si[0]->s,x_rand)+*h)<=l);
    }

  /* Now check if the sample is invalid due to its nearest neighbour (dynamic domain et al.) */
  if (validSample)
    {	
      /* Determine i_near  */
      #if (NN_IN_CHART)
        double d;

        if ((expand2goal)||(c_rand==NO_UINT)||(t_rand==NULL))
	  *i_near=GetRRTNN(tree,x_rand,&(ar->rrt));
	else
	  {
	    *i_near=GetRRTNNInChart(pr,T2G_METRIC_NN_EXTEND,tree,c_rand,x_rand,&d,ar);

	    #if (NN_IN_NEIGHBOUR_CHART)
	    {
	      Tchart *c,*cc;
	      unsigned int i,n,cn,in;
	      double d1,*p0,*p,*t;
	      
	      c=GetAtlasChart(c_rand,&(ar->atlas));
	      
	      NEW(p0,ar->m,double);
	      NEW(p,ar->m,double);
	      NEW(t,ar->k,double);

	      /* Try to get the point on the manifold. If not possible just keep the tangent space point */
	      if (Chart2Manifold(pr,&(ar->J),t_rand,ar->tp,x_rand,p0,c)==INF)
		memcpy(p0,x_rand,ar->m*sizeof(double));

	      /* Iterate over all neighbouring charts */
	      n=ChartNumNeighbours(c);
	      for(i=0;i<n;i++)
		{
		  /* Get the neighbouring chart */
		  cn=ChartNeighbourID(i,c);
		  cc=GetAtlasChart(cn,&(ar->atlas));

		  /* Move the random sample to the neighbouring chart */
		  Manifold2Chart(p0,ar->tp,t,cc);
		  Local2Global(t,ar->tp,p,cc);

		  /* Look for neighbours in this chart */
		  in=GetRRTNNInChart(pr,T2G_METRIC_NN_EXTEND,tree,cn,p,&d1,ar);

		  /* Keep the closest sample */
		  if (d1<d)
		    {
		      d=d1;
		      *i_near=in;
		    }
		}
	      
	      free(t);
	      free(p);
	      free(p0);
	     
	    }
	    #endif
	    
	    /* If all the samples in the AtlasRRT have null velocities,
	       GetRRTNNInChart returns NO_UINT (if using a Time2Go metric).
	       In initial stages of the AtlasRRT we can have all points
	       with null velocity (specially when we ony have the start
	       and goal samples). In this case we use standard NN */
	    if ((*i_near==NO_UINT)&&(ar->ns<25))
	      *i_near=GetRRTNN(tree,x_rand,&(ar->rrt));
	  }
      #else
        /*search in the entire atlas */
        #if (T2G_METRIC)
          Error("Time2Go metric can only be used if NN_IN_CHART is active");
        #endif
	//*i_near=ar->ns-1;
	*i_near=GetRRTNN(tree,x_rand,&(ar->rrt));
      #endif

      /* Check if the random sample is in the domain of the nearest neighbour */
      /* This only has effect if paramter DYNAMIC_DOMAIN is >0 */
      validSample=((*i_near!=NO_UINT)&&
		   ((!expand2goal)||(lastNN2Goal!=*i_near))&&
		   (InDynamicDomain(*i_near,x_rand,&(ar->rrt))));
      
      #if (PENALIZE_BLOCKED_NODES)
        if ((validSample)&&(ar->dynamics)&&(randomDouble()<RRTBlockedProb(*i_near,&(ar->rrt))))
	  {
	    validSample=FALSE;
	    #if (GET_ATLASRRT_STATISTICS)
	      NewAtlasRRTSampleRejection3(arst);
	    #endif
	  }
      #endif

      #if (REJECT_USING_DYNAMIC_CONE)
	if ((validSample)&&(ar->dynamics))
	  {
	    Tchart *c_near;
	    double *xd,*u,*txd,n1,n2,*t;
		
	    NEW(xd,ar->m,double);
	    NEWZ(u,ar->da,double);
	    NEW(txd,ar->k,double);   /* xdot in tangent space of i_near */

	    c_near=GetAtlasChart(ar->si[*i_near]->c,&(ar->atlas));
	    
	    /*
	    u[0]=-8;
	    Getxdot(pr,ar->si[*i_near]->s,u,xd,ar->ds);
	    TMatrixVectorProduct(ar->m,ar->k,GetChartTangentSpace(c_near),xd,txd);
	    PrintVector(stderr,"xd_min",ar->k,txd);
	    
	    u[0]=+8;
	    Getxdot(pr,ar->si[*i_near]->s,u,xd,ar->ds);
	    TMatrixVectorProduct(ar->m,ar->k,GetChartTangentSpace(c_near),xd,txd);
	    PrintVector(stderr,"xd_max",ar->k,txd);
	    
	    u[0]=0;
	    */
	    
	    Getxdot(pr,ar->si[*i_near]->s,u,xd,ar->ds);
	    TMatrixVectorProduct(ar->m,ar->k,GetChartTangentSpace(c_near),xd,txd);
	    //PrintVector(stderr,"xd_0",ar->k,txd);
	    
	    n1=Norm(ar->k,txd);
	    
	    //fprintf(stderr,"n0=%f;\n",n1);
	    
	    if (n1>1e-2)
	      {	
		NEW(t,ar->k,double);   /* x_rand in the tangent space of i_near */
		
		n2=Manifold2Chart(x_rand,NULL,t,c_near);
		/*
		PrintVector(stderr,"r",ar->k,t);
		fprintf(stderr,"near=%u;\n",*i_near);
		fprintf(stderr,"gc=%u;\n",ar->si[*i_near]->generateChart);
		PrintVector(stderr,"n",ar->k,ar->si[*i_near]->t);
		*/
		
		SubtractVector(ar->k,t,ar->si[*i_near]->t);
		//PrintVector(stderr,"t",ar->k,t);
		
		n2=Norm(ar->k,t);
		
		//fprintf(stderr,"nt=%f;\n",n2);
		//fprintf(stderr,"c=%f;\n",GeneralDotProduct(ar->k,t,txd)/(n1*n2));
	    
		validSample=(GeneralDotProduct(ar->k,t,txd)/(n1*n2)>=0);
		
		#if (GET_ATLASRRT_STATISTICS)
		  if (!validSample)
		    NewAtlasRRTSampleRejection4(arst);
	        #endif
		
		free(t);
	      }
	    free(u);
	    free(xd);
	    free(txd);
	  }
      #endif
    }

  #if (ATLASRRT_VERBOSE)
    if (validSample)
      {
	fprintf(stderr,"    Nearest point %u on chart %u. Distance: %f\n",*i_near,ar->si[*i_near]->c,
		DistanceTopology(ar->m,ar->tp,ar->si[*i_near]->s,x_rand));
	PrintVector(stderr,"      x_near",ar->m,ar->si[*i_near]->s);
	PrintVector(stderr,"      x_rand",ar->m,x_rand);
      }
    else
      fprintf(stderr,"    Invalid sample\n");
  #endif
  
  #if (GET_ATLASRRT_STATISTICS)
    if (!validSample)
      NewAtlasRRTSampleRejection2(arst);
  #endif

  return(validSample);
}

void RefineTrajectory(Tparameters *pr,boolean id,unsigned int *ns,double ***path,
		      double ***actions,double **times,Tatlasrrt *ar)
{
  unsigned int ms,new_ns,ns_connect;
  double **new_path,**path_connect;
  double **new_actions,**actions_connect;
  double *new_times,*times_connect;
  unsigned int i,j;
  double delta,e,t;

  delta=GetParameter(CT_DELTA,pr);

  /* Empty trajectory */
  InitTrajectory(&ms,&new_ns,&new_path,ar->da,&new_actions,&new_times);

  AddStep2Trajectory(ar->m,(*path)[0],ar->m,NULL,(*actions)[0],(*times)[0],
		     &ms,&new_ns,&new_path,ar->da,&new_actions,&new_times);

  for(i=1;i<*ns;i++)
    {
      if ((id)&&((*times)[i]==0))
	{
	  if (i<*ns-1)
	    (*times)[i]=((*times)[i-1]+(*times)[i+1])/2.0;
	  else
	    (*times)[i]=(*times)[i-1];
	}
      if ((*times)[i]>0)
	{
	  if (id)
	    e=ConnectDynamicStatesID(pr,ar->tp,&(ar->ambient),FALSE,ar->m,ar->k,ar->da,
				     (*path)[i-1],(*actions)[i],(*times)[i],
				     (*path)[i],
				     &ns_connect,&path_connect,&actions_connect,&times_connect,
				     &(ar->J),ar->ds,ar->w);
	  else
	    e=ConnectDynamicStates(pr,ar->tp,&(ar->ambient),FALSE,ar->m,ar->k,ar->da,
				   (*path)[i-1],(*actions)[i],(*times)[i],
				   (*path)[i],
				   &ns_connect,&path_connect,&actions_connect,&times_connect,
				   &(ar->J),ar->ds,ar->w);

	  /* Since we use different charts, the integration may not reach exactly the goal,
	     but typically the error is very small. Using delta is a very safe
	     threshold. */
	  if (e>2*delta)
	    {
	      if (e==INF)
		fprintf(stderr,"Collision or invalid next dynamic step\n");
	      else
		fprintf(stderr,"Connection failed in RefineTrajectory: %f\n",e);
	    }
	  else
	    {
	      t=0.0;
	      for(j=1;j<ns_connect;j++) /* from 1!! fist step already adde in previous iteration*/
		{
		  if ((t+times_connect[j]>=0.1)|| /* frames are separated at least 0.1 */
		      (j==ns_connect-1))
		    {
		      if (j==ns_connect-1)
			AddStep2Trajectory(ar->m,(*path)[i],ar->m,NULL,actions_connect[j],t+times_connect[j],
					   &ms,&new_ns,&new_path,ar->da,&new_actions,&new_times);
		      else
			AddStep2Trajectory(ar->m,path_connect[j],ar->m,NULL,actions_connect[j],t+times_connect[j],
					   &ms,&new_ns,&new_path,ar->da,&new_actions,&new_times);
		      t=0.0;
		    }
		  else
		    t+=times_connect[j];
		}

	    }
	  DeleteTrajectory(ns_connect,path_connect,actions_connect,times_connect);
	}
      else
	{
	  /* The connection between two trees for which we do not have any action
	     TODO: Use inverse dynamics to find out a valid action at the connection.
	  */
	  (*times)[i]=((*times)[i-1]+(*times)[i+1])/2.0; /* Fix the time */
	  AddStep2Trajectory(ar->m,(*path)[i],ar->m,NULL,(*actions)[i],(*times)[i],
			     &ms,&new_ns,&new_path,ar->da,&new_actions,&new_times);
	}
    }

  DeleteTrajectory(*ns,*path,*actions,*times);
  *ns=new_ns;
  *path=new_path;
  *actions=new_actions;
  *times=new_times;
}

void AtlasRRTSimulate(Tparameters *pr,unsigned int da,double *u,
		      unsigned int steps,unsigned int *ns,double ***path,
		      double ***actions,double **times,Tatlasrrt *ar)
{
  unsigned int i,nv,nvs;
  boolean *systemVars,blocked;
  unsigned int ms;
  unsigned int ns_step;
  double **path_step;
  double *o;
  double *goal;
  TAtlasRRTBranchConfig configExtend;
  TAtlasRRTBranchState stateExtend;
  #if (DEBUG_SIMULATION)
    TAtlasRRTStatistics arst;

    InitAtlasRRTStatistics(&arst);
  #endif
  
  if ((unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr)>0)
    Error("AtlasRRT can not deal with bifurcations (yet)");

  /* relevant variables in the original system */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,ar->w);
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }

  /* Dimension of the action space */
  if (da!=ActionSpaceDimension(ar->ds))
    Error("Wrong number of input actions in AtlasRRTSimulate");

  /* Empty trajectory */
  InitTrajectory(&ms,ns,path,da,actions,times);

  /* Set the first step in the trajectory with no action and time 0 */
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,ar->si[0]->s,&o,ar->w);
  AddStep2Trajectory(nv,o,nvs,systemVars,NULL,0.0,&ms,ns,path,da,actions,times);
  free(o);
  InitBranchConfig(SIMULATE_DYNAMICS,&configExtend);

  /* Configure the branch extension */
  configExtend.maxIntTime=GetParameter(CT_INTEGRATION_TIME,pr);
  configExtend.currentMaxIntTime=configExtend.maxIntTime;
  
  /* In some cases the simulation does not follow the action given by
     the user but determines the optimal action using LQR*/
  if (ar->nda==0)
    {	  
      /* Use LQR */
      fprintf(stderr,"Using LQR to determine the action\n");
      if (ar->ns<2)
	Error("Goal missing to guide LQR");
      if ((ar->ns!=2)||(ar->nc!=2))
	Error("AtlasRRT must be used on a just initialized AtlasRRTSimulate");
      goal=ar->si[1]->s;
    }
  else
    {
      if ((ar->ns!=1)||(ar->nc!=1))
	Error("AtlasRRT must be used on a just initialized AtlasRRTSimulate");
      goal=NULL;
    }
  
  /* We repeat integration steps of time maxIntTime and only
     take the point at the end of the step. */
  i=0;
  blocked=FALSE;
  while((i<steps)&&(!blocked))
    {
      #if (_DEBUG>0)
        fprintf(stderr,"Simulation step: %u\n",i);
      #endif

      configExtend.maxTopt=INF; /* to avoid stopping branches if they do not advance toward goal */
      #if (DEBUG_SIMULATION)
        AddBranchToAtlasRRT(pr,i,&configExtend,0,NULL,NULL,NULL,NULL,u,(i==0?0:ar->ns-1),goal,goal,
			    (void *)&arst,&stateExtend,&ns_step,&path_step,NULL,NULL,NULL,NULL,ar->ds,ar);
      #else
	AddBranchToAtlasRRT(pr,i,&configExtend,0,NULL,NULL,NULL,NULL,u,(i==0?0:ar->ns-1),goal,goal,
	                    NULL,&stateExtend,&ns_step,&path_step,NULL,NULL,NULL,NULL,ar->ds,ar);
      #endif
      
      if (stateExtend.intTime>0)
	{
	  CS_WD_REGENERATE_ORIGINAL_POINT(pr,path_step[ns_step-1],&o,ar->w);
	  AddStep2Trajectory(nv,o,nvs,systemVars,u,stateExtend.intTime,&ms,ns,path,da,actions,times);
	  free(o);

	  #if (_DEBUG>0)
	    fprintf(stderr,"   Integration time: %f (%u) (%f %f)\n",stateExtend.intTime,ns_step,configExtend.currentMaxIntTime,configExtend.topt);
	  #endif

	  DeleteSamples(ns_step,path_step);
	}
      /* we stop the simulation if the integration time can not be compleated (for whatever reason) */
      blocked=((stateExtend.intTime<configExtend.currentMaxIntTime)||(stateExtend.reachedGoal));
      i++;
    }
  free(systemVars);

  #if (DEBUG_SIMULATION)
    PrintAtlasRRTStatistics(ar,&arst);
    DeleteAtlasRRTStatistics(&arst);
  #endif
}

boolean AtlasRRT(Tparameters *pr,double *pg,double *time,
		 double *pl,unsigned int *ns,double ***path,
		 unsigned int *da,double ***actions,double **times,
		 TAtlasRRTStatistics *str,Tatlasrrt *ar)
{
  boolean done;
  double dst;
  unsigned int it,n;
  double er,epsilon,h;
  double *pWithDummies,*initialPoint,*finalPoint,*x_rand,*x_goal,*t_rand;
  boolean expand2Goal,pathFound;
  unsigned int samplingMode;
  unsigned int i_near1,i_near2;
  unsigned int t1,t2;
  unsigned int lastSample;
  unsigned int lastSample2;
  TAtlasRRTStatistics *arst;
  Tstatistics stime; /* used just to measure execution time */
  boolean collision=FALSE;
  unsigned int target;
  unsigned int lastNN2Goal;
  unsigned int db;
  double maxTime;
  unsigned int maxNodes;
  boolean exploration;
  double scale; /* Global scale factor for the sampling areas */
  boolean validSample;
  unsigned int c_rand;
  TAtlasRRTBranchConfig configExtend,configConnect;
  TAtlasRRTBranchState stateExtend,stateConnect;
  /* If dynamics is used we need to simulate several actions */
  TDynamicBranches dBranches;
  boolean reachedGoal; /* reached in a dynamic expansion */

  db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr);
  if (db>0)
    Error("AtlasRRT can not deal with bifurcations (yet)");

  if (ar->dynamics)
    {
      InitDynamicBranches(pr,&dBranches,ar);

      InitBranchConfig(EXTEND_RRT_DYNAMICS,&configExtend);

      InitBranchConfig(CONNECT_RRT_DYNAMICS,&configConnect);

      *da=ar->da; /* dimension of the action space */
    }
  else
    {
      InitBranchConfig(EXTEND_RRT,&configExtend);
      InitBranchConfig(CONNECT_RRTs,&configConnect);

      *da=0;
    }

  configExtend.maxIntTime=GetParameter(CT_INTEGRATION_TIME,pr);
  configConnect.maxIntTime=configExtend.maxIntTime;
  
  configExtend.checkCollisions=CS_ANY_COLLISION(ar->w);
  configConnect.checkCollisions=CS_ANY_COLLISION(ar->w);
  
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

  scale=1.0; /* Not used yet...  */

  /* Initially the AtlasRRT must only include one sample and one chart or
     two sample and two chart for bidirectional trees */
  n=(ar->birrt?2:1);
  if ((ar->ns!=n)||(ar->nc!=n))
    Error("AtlasRRT must be used on a just initialized AtlasRRT");

  #if (GET_ATLASRRT_STATISTICS)
  {
    unsigned int i;

    NEW(arst,1,TAtlasRRTStatistics);
    InitAtlasRRTStatistics(arst);
    for(i=0;i<ar->nc;i++)
      NewAtlasRRTChart(arst);
    for(i=0;i<ar->ns;i++)
      NewAtlasRRTSample(arst);
  }
  #else
    arst=NULL;
  #endif

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);

  /* For bi-directional AtlasRRTs the goal is already in the RRT
     and it is already verified */
  initialPoint=ar->si[0]->s;
  if (ar->birrt)
    finalPoint=ar->si[1]->s;
  else
    {
      if (EXPLORATION_RRT)
	finalPoint=NULL;
      else
	{
	  /* For one-directional RRTS, the goal is given as a parameter when
	     calling this function and we must ensure that it is valid */
	  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,ar->w);
	  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&finalPoint,ar->w);

	  if ((!PointInBoxTopology(NULL,TRUE,ar->m,finalPoint,epsilon,ar->tp,&(ar->ambient)))||
	      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,finalPoint,ar->w)))
	    Error("The goal point for the AtlasRRT is not in domain");

	  if (ar->m==ar->k) /* empty system of equations */
	    er=0;
	  else
	    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,finalPoint,ar->w);
	  if (er>epsilon)
	    Error("The target point of the AtlasRRT is not on the manifold");

	  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,ar->w);
	  if (collision)
	    Error("Target point for the AtlasRRT is in collision");
	  free(pWithDummies);
	}
    }
  // Ids of the last samples added to the trees. Init just in case
  lastSample=0;
  lastSample2=1;
  
  NEW(x_rand,ar->m,double);
  if (ar->birrt)
    NEW(x_goal,ar->m,double);
  NEW(t_rand,ar->k,double);

  done=FALSE;
  lastNN2Goal=NO_UINT;
  it=0;
  if (ar->parallel) /* may be true in dynamic problems */
    InitStatistics(2,0,&stime);
  else
    InitStatistics(0,0,&stime);

  *time=0.0;

  /* The two trees. This is only used for bidirectiononal RRTs. In normal
     RRTs only the START2GOAL tree is extended*/
  t1=START2GOAL;
  t2=GOAL2START;

  while((!done)&&(*time<maxTime)&&(ar->ns<maxNodes))
    {
      #if (!ATLASRRT_VERBOSE)
      if ((it%(ar->dynamics?100:1000))==0)
      #endif
	{
	  #if (ATLASRRT_VERBOSE)
	    fprintf(stderr,"===============================================================================================\n");
	    fprintf(stderr,"===============================================================================================\n");
	  #endif
	  fprintf(stderr,"Iteration: %u (s:%u c:%u t:%u tm:%g sc:%.2f)\n",it,ar->ns,ar->nc,t1,*time,scale);
	}

      /*******************************************************************/
      /* Sample */
      exploration=FALSE;
      do {
	/* Generate a random sample */
	expand2Goal=AtlasRRTSample(pr,samplingMode,it,t1,finalPoint,scale,
				   &exploration,&(configExtend.onManifold),
				   &c_rand,t_rand,x_rand,arst,ar);

	/* validate the random sample */
	validSample=AtlasRRTValidateSample(pr,c_rand,t_rand,x_rand,t1,expand2Goal,lastNN2Goal,NULL,INF,
					   &h,&i_near1,arst,ar);
      } while (!validSample);

      if (expand2Goal)
	lastNN2Goal=i_near1;

      /*******************************************************************/
      /* Extend the RRT from x_near toward x_rand */
      #if (GET_ATLASRRT_STATISTICS)
        NewAtlasRRTBranch(arst);
        NewAtlasRRTDistanceQrand(DistanceTopology(ar->m,ar->tp,ar->si[i_near1]->s,x_rand),arst);
      #endif

      configExtend.onManifold=expand2Goal; /* can eventually be true for oneDirectional RRTs */
      configExtend.explorationSample=exploration;

      if (ar->dynamics)
	{
	  configExtend.currentMaxIntTime=configExtend.maxIntTime;
	  #if (RANDOM_INT_TIME)
	    configExtend.currentMaxIntTime*=randomDouble();
	  #endif

	  dst=AddBranchToAtlasDynamicRRT(pr,DYNAMICS_ONE_ACTION_EXTEND,T2G_METRIC_INSIDE_EXTEND,
					 it,&configExtend,i_near1,x_rand,
					 (((!ar->birrt)||(t1==START2GOAL))?finalPoint:initialPoint),
					 (void*)arst,&dBranches,&lastSample,&reachedGoal,ar);
	  done=((!EXPLORATION_RRT)&&(reachedGoal));
	  if ((ar->birrt)&&(done))
	    {
	      /* We are building a bi-RRT but accidentally we reached the goal while exteding one
	         of the trees. We just set up the variables so that the path can be properly
	         reconstructed. */
	      lastSample2=(t1==START2GOAL?1:0);
	      i_near2=lastSample2;
	    }
	}
      else
	{
	  dst=AddBranchToAtlasRRT(pr,it,&configExtend,0,NULL,NULL,NULL,NULL,NULL,i_near1,x_rand,
				  (((!ar->birrt)||(t1==START2GOAL))?finalPoint:initialPoint),
				  (void*)arst,&stateExtend,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);

	  lastSample=stateExtend.lastID;
	  reachedGoal=stateExtend.reachedGoal;
	  done=((!EXPLORATION_RRT)&&(!ar->birrt)&&(reachedGoal));
	}

      #if (GET_ATLASRRT_STATISTICS)
	if (dst>0)
	  NewAtlasRRTNoEmptyBranch(arst);
      #endif

      if ((!done)&&(ar->ns<maxNodes)&&(ar->birrt))
	{
	  /* in trivial problems the start and the goal are already close enough. */
	  if (lastSample!=i_near1)  /* == (dst>0) */
	    //if ((lastSample!=i_near1)&&
	    // ((dst>0)||((ar->ns==2)&&(reachedGoal)))) 
	    {
	      /* Try to connect to the other tree */

	      /* Get the node of the just added branch closer to the other tree (and the node of
		 the other tree closer to this just added node).
		 target: is a sample in the last added branch (in tree1)
		 i_near2: is the closer sample in the other tree (tree2)
		 We try to connect tree2 (i_near2) with tree1 (target)
	      */
	      #if (T2G_METRIC_NN_CONNECT)
	        target=lastSample;
		i_near2=Time2GoNNToTree(pr,t2,lastSample,ar);
	      #else
	        GetRRTNNInBranch(t2,i_near1,lastSample,&target,&i_near2,&(ar->rrt));
	      #endif

	      #if (ATLASRRT_VERBOSE)
		fprintf(stderr,"===============================================================================================\n");
	        if (i_near2==NO_UINT)
		  fprintf(stderr,"No good candidate to connect to the other three\n");
		else
		  {
		    fprintf(stderr,"Connecting to the other tree (t: %u): %u -> %u\n",t2,i_near2,target);
		    fprintf(stderr,"    Nearest point %u on chart %u. Distance: %f\n",i_near2,ar->si[i_near2]->c,
		    DistanceTopology(ar->m,ar->tp,ar->si[i_near2]->s,ar->si[target]->s));
		    PrintVector(stderr,"      x_near",ar->m,ar->si[i_near2]->s);
		    PrintVector(stderr,"      x_rand",ar->m,ar->si[target]->s);
		  }
	      #endif

	      lastSample=target;

	      memcpy(x_rand,ar->si[target]->s,ar->m*sizeof(double));
	      memcpy(x_goal,x_rand,ar->m*sizeof(double)); /* copy of Qrand */

	      /* Try to connect the '2nd' tree to the last node added to the '1st' tree */
	      #if (GET_ATLASRRT_STATISTICS)
	        NewAtlasRRTTreeConnection(arst);
	      #endif

	      if (i_near2!=NO_UINT)
		{
		  if (ar->dynamics)
		    {
		      configConnect.currentMaxIntTime=configConnect.maxIntTime;
			  
		      dst=AddBranchToAtlasDynamicRRT(pr,DYNAMICS_ONE_ACTION_CONNECT,T2G_METRIC_INSIDE_CONNECT,
						     it,&configConnect,i_near2,x_rand,x_goal,
						     (void*)arst,&dBranches,&lastSample2,&reachedGoal,ar);
		      done=((!EXPLORATION_RRT)&&(reachedGoal));
		    }
		  else
		    {
		      /* We may add some validity test for x_rand and i_near2 (dynamic domain, etc) */
		      dst=AddBranchToAtlasRRT(pr,it,&configConnect,0,NULL,NULL,NULL,NULL,NULL,i_near2,x_rand,x_goal,
					      (void*)arst,&stateConnect,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);

		      lastSample2=stateConnect.lastID;
		      reachedGoal=stateConnect.reachedGoal;
		      done=((!EXPLORATION_RRT)&&(stateConnect.reachedGoal));
		    }
		}
	      else
		dst=0.0;

	      #if (GET_ATLASRRT_STATISTICS)
	        if (dst>0)
		  NewAtlasRRTNoEmptyTreeConnection(arst);
	      #endif
	    }

	  /* Swap the trees */
	  if ((it%2)==0)
	    {
	      t1=START2GOAL;
	      t2=GOAL2START;
	    }
	  else
	    {
	      t1=GOAL2START;
	      t2=START2GOAL;
	    }
	}
      #if (ADJUST_SA)
      if ((!done)&&(samplingMode==TANGENT_SAMPLING))
	{
	  if (dst<epsilon)
	    {
	      #if (ADJUST_SA==2)
	        /* Troubles extending branches: reduce the sampling areas to focus on refinement */
	        scale*=(1-MOV_AVG_DOWN);
	        if (scale<0.05) scale=0.05;
	      #else
	        /* an alternative is to adjust the sampling radius locally */
	        if (!expand2Goal)
		  DecreaseChartSamplingRadius(GetAtlasChart(c_rand,&(ar->atlas)));
	      #endif
	    }
	  else
	    {
	      #if (ADJUST_SA==2)
	        /* No trouble extending branches: increase sampling area to focus on exploration */
	        ////scale=1.0;
	        scale*=(1+MOV_AVG_UP);
		if (scale>1.0) scale=1.0;
	      #else
		/* an alternative is to adjust the sampling radius locally (ADJUST_SA==1) */
		if (!expand2Goal)
		  IncreaseChartSamplingRadius(GetAtlasChart(c_rand,&(ar->atlas)));
	      #endif
	    }
	}
      #endif

      it++;
      *time=GetElapsedTime(&stime);
    }
  DeleteStatistics(&stime);
  
  #if (GET_ATLASRRT_STATISTICS)
    NewAverageNumNeighbours(AverageNumNeighbours(&(ar->atlas)),arst);
    if (str==NULL)
      PrintAtlasRRTStatistics(ar,arst);
    else
      AccumulateAtlasRRTStatistics(arst,str);
    DeleteAtlasRRTStatistics(arst);
    free(arst);
  #endif

  fprintf(stderr,"Final number of samples: %u\n",ar->ns);


  /* Reconstruct the path (if any) */
  if (EXPLORATION_RRT)
    pathFound=FALSE;
  else
    {  
      pathFound=PathStart2GoalInRRT(pr,finalPoint,lastSample,lastSample2,
				    pl,NULL,ns,path,actions,times,&(ar->rrt));

      #if (!DYNAMICS_ADD_ALL)
        /* In problems with dynamics if only the end-points of the simulated
	   steps are added to the tree, the final path may be too
	   coarse. */
        if ((0)&&(pathFound)&&(ar->dynamics))
	  RefineTrajectory(pr,FALSE,ns,path,actions,times,ar);
      #endif
    }
  
  free(t_rand);
  free(x_rand);
  if (ar->birrt)
    free(x_goal);
  else
    {
      if (finalPoint!=NULL)
	free(finalPoint);
    }
  
  if (ar->dynamics)
    DeleteDynamicBranches(&dBranches,ar);

  return(pathFound);
}

boolean AtlasTRRT(Tparameters *pr,double *pg,double *time,
		  double *pl,double *pc,unsigned int *ns,double ***path,
		  double (*costF)(Tparameters*,boolean,double*,void*),
		  void *costData,TAtlasRRTStatistics *str,Tatlasrrt *ar)
{
  boolean done;
  unsigned int it;
  double er,epsilon,h;
  unsigned int samplingMode;
  double *pWithDummies,*finalPoint,*x_rand,*t_rand;
  unsigned int c_rand;
  boolean expand2Goal,pathFound,exploration;
  unsigned int i_near1;
  TAtlasRRTStatistics *arst;
  Tstatistics stime; /* used just to measure execution time */
  boolean collision=FALSE;
  unsigned int lastNN2Goal;
  unsigned int db;
  double maxTime;
  unsigned int maxNodes;
  double scale; /* Global scale factor for sampling areas */
  boolean validSample;
  TAtlasRRTBranchConfig configExtend;
  TAtlasRRTBranchState stateExtend;

  InitBranchConfig(EXTEND_RRT,&configExtend);
  configExtend.costF=costF;
  configExtend.costData=costData;

  if (ar->dynamics)
    Error("AtlasTRRT is not yet implemented for dynamical systems");
  
  if (ar->birrt)
    Error("AtlasTRRT operates on one-directional RRTs");

  db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr);
  if (db>0)
    Error("AtlasRRT can not deal with bifurcations (yet)");

  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

  scale=1.0; /* not used yet */

  /* Initially the AtlasRRT must only include one sample and one chart or
     two sample and two chart for bidirectional trees */
  if (ar->ns>1)
    Error("AtlasRRTstar must be used to a just initilized RRT");

  #if (GET_ATLASRRT_STATISTICS)
  {
    unsigned int i;

    NEW(arst,1,TAtlasRRTStatistics);
    InitAtlasRRTStatistics(arst);
    for(i=0;i<ar->nc;i++)
      NewAtlasRRTChart(arst);
    for(i=0;i<ar->ns;i++)
      NewAtlasRRTSample(arst);
  }
  #else
    arst=NULL;
  #endif

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);

  if (EXPLORATION_RRT)
    finalPoint=NULL;
  else
    {
      /* One-directional RRTs, the goal is given as a parameter
	 and we must ensure that it is valid */
      CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,ar->w);
      CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&finalPoint,ar->w);

      if ((!PointInBoxTopology(NULL,TRUE,ar->m,finalPoint,epsilon,ar->tp,&(ar->ambient)))||
	  (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,finalPoint,ar->w)))
	Error("The goal point for the RRT is not in domain");

      if (ar->m==ar->k)
	er=0;
      else
	er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,finalPoint,ar->w);
      if (er>epsilon)
	Error("The target point is not on the manifold");

      collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,ar->w);;
      if (collision)
	Error("Target point for the RRT is in collision");
      free(pWithDummies);
    }

  /*init the cost of the first node*/
  SetRRTNodeCost(0,0,costF(pr,TRUE,GetRRTNode(0,&(ar->rrt)),costData),&(ar->rrt));

  NEW(x_rand,ar->m,double);
  NEW(t_rand,ar->k,double);

  done=FALSE;
  lastNN2Goal=NO_UINT;
  it=1;
  InitStatistics(0,0,&stime);
  *time=0.0;

  while((!done)&&(*time<maxTime)&&(ar->ns<maxNodes))
    {
      #if (!ATLASRRT_VERBOSE)
      if ((it%1000)==0)
      #endif
	fprintf(stderr,"Iteration: %u (s:%u c:%u t:%u tm:%g tmp:%g)\n",it,ar->ns,ar->nc,
		START2GOAL,*time,GetTRRTTemperature(&(ar->rrt)));


      /*******************************************************************/
      /* Sample */
      exploration=FALSE;
      do {
	/* generate the random sample */
	expand2Goal=AtlasRRTSample(pr,samplingMode,it,START2GOAL,finalPoint,scale,
				   &exploration,&(configExtend.onManifold),
				   &c_rand,t_rand,x_rand,arst,ar);

	/* validate the random sample */
	validSample=AtlasRRTValidateSample(pr,c_rand,t_rand,x_rand,START2GOAL,expand2Goal,lastNN2Goal,NULL,INF,
					   &h,&i_near1,arst,ar);

	/* There is no point in expanding the same node towards the goal twice */
      } while (!validSample);

      if (expand2Goal)
	lastNN2Goal=i_near1;

      /*******************************************************************/
      /* Extend the RRT from x_near toward x_rand */
      configExtend.onManifold=expand2Goal;
      configExtend.explorationSample=exploration;
      AddBranchToAtlasRRT(pr,it,&configExtend,0,NULL,NULL,NULL,NULL,NULL,i_near1,x_rand,finalPoint,
			  (void*)arst,&stateExtend,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);
      done=((!EXPLORATION_RRT)&&(stateExtend.reachedGoal));

      it++;
      *time=GetElapsedTime(&stime);
    }
  DeleteStatistics(&stime);

  #if (GET_ATLASRRT_STATISTICS)
    if (str==NULL)
      PrintAtlasRRTStatistics(ar,arst);
    else
      AccumulateAtlasRRTStatistics(arst,str);
    DeleteAtlasRRTStatistics(arst);
    free(arst);
  #endif

  fprintf(stderr,"Final number of samples: %u\n",ar->ns);

  /* Reconstruct the path (if any) */
  pathFound=PathStart2GoalInRRT(pr,finalPoint,stateExtend.lastID,
				NO_UINT,pl,pc,ns,path,NULL,NULL,&(ar->rrt));

  free(t_rand);
  free(x_rand);
  free(finalPoint);

  return(pathFound);
}

unsigned int AddStepToAtlasRRTstar(Tparameters* pr,
				   unsigned int it,boolean expand2Goal,boolean onManifold,
				   unsigned int i_near,double *x_rand,
				   unsigned int *id_goal,double *goal,
				   TAtlasRRTStatistics *arst,
				   Tatlasrrt *ar)
{
  double d,epsilon;
  unsigned int id_new;
  TAtlasRRTBranchConfig configExtend;
  TAtlasRRTBranchState stateExtend;

  InitBranchConfig(CONNECT_SAMPLES,&configExtend);

  epsilon=GetParameter(CT_EPSILON,pr);

  /* Try to advance as much as possible in the direction of x_rand. Only
     the last node is added to the tree. */
  configExtend.addMode=(expand2Goal?ADD_LAST_NO_REP:ADD_LAST);
  configExtend.onManifold=((expand2Goal)||(onManifold));
  d=AddBranchToAtlasRRT(pr,it,&configExtend,0,NULL,NULL,NULL,NULL,NULL,i_near,x_rand,goal,
			(void*)arst,&stateExtend,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);
  id_new=stateExtend.lastID;

  /* if we actually added a node */
  if (id_new!=i_near)
    {
      /* Store the cost of the new node. The cost to the parent is already correct (we
         need it if 'graph's is set to TRUE) but the total cost is not set */
      SetRRTNodeCost(id_new,d,GetRRTNodeCost(i_near,&(ar->rrt))+d,&(ar->rrt));

      #if (ATLASRRT_VERBOSE)
        fprintf(stderr,"  {%u->%u}[%g]\n",id_new,GetRRTParent(id_new,&(ar->rrt)),d);
      #endif

      /* if the new point is actually the goal record it */
      if ((goal!=NULL)&&(*id_goal==NO_UINT)&&
	  ((stateExtend.reachedGoal)||((expand2Goal)&&(stateExtend.reachedQrand))))
	{
	  if (stateExtend.distGoal<epsilon)
	    /* The new node is actually the goal */
	    *id_goal=id_new;
	  else
	    {
	      /* If the branch stopped very close to the goal, we add a small
		 branch from the end of the branch to the goal and the goal itself. */
	      configExtend.addMode=ADD_LAST;
	      configExtend.onManifold=TRUE;
	      d=AddBranchToAtlasRRT(pr,it,&configExtend,0,NULL,NULL,NULL,NULL,NULL,i_near,goal,NULL,
				    (void*)arst,&stateExtend,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);
	      *id_goal=stateExtend.lastID;

	      if (!stateExtend.reachedQrand)
		Error("Could not reach goal from near-goal");

	      SetRRTNodeCost(*id_goal,d,GetRRTNodeCost(*id_goal,&(ar->rrt))+d,&(ar->rrt));

	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr,"     {%u->%u}[%g] **\n",*id_goal,GetRRTParent(*id_goal,&(ar->rrt)),d);
	      #endif
	    }
	}
    }
  return(id_new);
}

void WireAtlasRRTstar(Tparameters *pr,
		      unsigned int id_new,unsigned int i_near,double gamma,
		      unsigned int nn,unsigned int *n,double **c,
		      double h,Theap *q,unsigned int *t,
		      TAtlasRRTStatistics *arst,Tatlasrrt *ar)
{
  unsigned int i;
  double ic,cn,epsilon,c_new;
  double *cost;
  boolean *reachedQRand;
  double *x_new;
  TDoublePair pair;
  unsigned int rrtMode;
  boolean graph;
  TAtlasRRTBranchConfig configExtend;
  TAtlasRRTBranchState *stateExtend;

  InitBranchConfig(CONNECT_SAMPLES,&configExtend);
  NEW(stateExtend,nn,TAtlasRRTBranchState);

  epsilon=GetParameter(CT_EPSILON,pr);

  /*******************************************************************/
  /* Wire: Search for the lowest cost path to the new node */
  #if (ATLASRRT_VERBOSE)
    fprintf(stderr,"  Wire %u [nn:%u g:%g]\n",id_new,nn,gamma);
  #endif
  rrtMode=GetRRTMode(&(ar->rrt));
  graph=IsRRTGraph(&(ar->rrt));
  #if (RRTSTAR_SYMMETRIC_COST)
    if (!graph)
      NEW(*c,nn,double);
  #endif
  ic=GetRRTNodeCostFromParent(id_new,&(ar->rrt)); /*cost to i_near*/
  x_new=ar->si[id_new]->s;
  *t=0; /* initially no tree in the set of neighbours */

  NEW(cost,nn,double);
  NEW(reachedQRand,nn,boolean);

  #pragma omp parallel for private(i) schedule(dynamic) if (ar->parallel)
  for(i=0;i<nn;i++)
    {
      if (n[i]==id_new)
	reachedQRand[i]=FALSE;
      else
	{
	  if (n[i]==i_near)
	    {
	      cost[i]=ic;
	      reachedQRand[i]=TRUE;
	    }
	  else
	    {
	      if (ar->parallel)
		{
		  boolean collision;

		  /* When executing in parallel we:
		     - Do not collect statistics about the connection process.
		     - Do not add new charts to the atlas. We only generate temporary charts. */
		  cost[i]=ConnectSamplesChart(pr,ar->tp,NULL,&(ar->ambient),
					      ar->m,ar->m-ar->k,ar->si[n[i]]->s,x_new,gamma,
					      TRUE,&(ar->J),&(reachedQRand[i]),&collision,NULL,NULL,NULL,ar->w);;
		}
	      else
		{
		  configExtend.maxLength=gamma;
		  cost[i]=AddBranchToAtlasRRT(pr,NO_UINT,&configExtend,0,NULL,NULL,NULL,NULL,NULL,n[i],x_new,NULL,
					      (void*)arst,&(stateExtend[i]),NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);
		  reachedQRand[i]=stateExtend[i].reachedQrand;
		}
	    }
	}
    }

  for(i=0;i<nn;i++)
    {
      if (n[i]!=id_new)
	{
	  #if (GET_ATLASRRT_STATISTICS)
	    NewAtlasRRTBranch(arst);
	  #endif
	  (*t)|=GetRRTNodeTree(n[i],&(ar->rrt)); /* take note of the tree of this neighbour (even if not reached)*/
	}

      if (reachedQRand[i])
	{
	  cn=cost[i];

	  #if (GET_ATLASRRT_STATISTICS)
	    NewAtlasRRTNoEmptyBranch(arst);
	  #endif

	  /* update the cost of the reached neighbour */
	  #if (!RRTSTAR_UPDATE_COSTS)
	  if (rrtMode==TWO_TREES_WITH_SWAP)
	  #endif
	    UpdateCostAndTree(n[i],&(ar->rrt));

	  /* There is an edge connecting id_new and n[i] */
	  if (graph)
	    AddEdgeToRRT(id_new,n[i],cn,&(ar->rrt));

	  c_new=GetRRTNodeCost(n[i],&(ar->rrt))+cn;
	  if (c_new<(GetRRTNodeCost(id_new,&(ar->rrt))-epsilon))
	    {
	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr,"     {%u->%u}[%g %g] ->",id_new,GetRRTParent(id_new,&(ar->rrt)),
			GetRRTNodeCostFromParent(id_new,&(ar->rrt)),
			GetRRTNodeCost(id_new,&(ar->rrt)));
	      #endif

	      SetRRTCostAndParent(id_new,n[i],cn,c_new,&(ar->rrt));

	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr,"{%u->%u}[%g %g]\n",id_new,GetRRTParent(id_new,&(ar->rrt)),
			GetRRTNodeCostFromParent(id_new,&(ar->rrt)),
			GetRRTNodeCost(id_new,&(ar->rrt)));
	      #endif
	    }
	}
      else
	cn=INF;

      #if (RRTSTAR_SYMMETRIC_COST)
        if (!graph)
	  (*c)[i]=cn;
      #endif
    }

  free(cost);
  free(reachedQRand);
  free(stateExtend);

  if (graph)
    {
      if (!q)
	Error("RRT must be in graph mode to use a heap");
      c_new=GetRRTNodeCost(id_new,&(ar->rrt));
      NewDoublePair(c_new+h,c_new,&pair);
      AddElement2Heap(id_new,(void *)&pair,q);
    }
}

void ReWireAtlasRRTstar(Tparameters *pr,
			unsigned int id_new,double gamma,
			unsigned int nn,unsigned int *n,double *c,
			Tvector *steps,double *l,
			TAtlasRRTStatistics *arst,Tatlasrrt *ar)
{

  unsigned int i,parent;
  double cn,epsilon,c_new;
  unsigned int rrtMode;
  boolean reachedQRand;
  #if (!RRTSTAR_SYMMETRIC_COST)
    TAtlasRRTBranchConfig configExtend;
    TAtlasRRTBranchState stateExtend;

    InitBranchConfig(CONNECT_SAMPLES,&configExtend);
  #endif

  epsilon=GetParameter(CT_EPSILON,pr);

  #if (ATLASRRT_VERBOSE)
    fprintf(stderr,"  Rewire\n");
  #endif
  rrtMode=GetRRTMode(&(ar->rrt));
  /* best parent for the new node */
  parent=GetRRTParent(id_new,&(ar->rrt));
  for(i=0;i<nn;i++)
    {
      if ((n[i]==id_new)||(n[i]==parent))
	reachedQRand=FALSE;
      else
	{
	  #if (RRTSTAR_SYMMETRIC_COST)
	    cn=c[i];
	    reachedQRand=(cn<INF);
	  #else
	    /* cost to go from id_new to n[i] */
	    /* the branch is virtual-> nothing is added to the RRT */
	    configExtend.maxLength=gamma;
	    cn=AddBranchToAtlasRRT(pr,NO_UINT,&configExtend,0,NULL,NULL,NULL,NULL,NULL,id_new,ar->si[n[i]]->s,NULL,
				   (void*)arst,&stateExtend,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);
	    reachedQRand=stateExtend.reachedQrand;
	  #endif
	}

      if (reachedQRand)
	{
	  /* Ensure that any previous-rewire is propagated to the currently tested node */
	  if (rrtMode==TWO_TREES_WITH_SWAP)
	    UpdateCostAndTree(n[i],&(ar->rrt));

	  c_new=GetRRTNodeCost(id_new,&(ar->rrt))+cn;
	  if (c_new<(GetRRTNodeCost(n[i],&(ar->rrt))-epsilon))
	    {
	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr,"     {%u->%u}[%g] ->",n[i],GetRRTParent(n[i],&(ar->rrt)),
		        GetRRTNodeCostFromParent(n[i],&(ar->rrt)));
	      #endif

	      SetRRTCostAndParent(n[i],id_new,cn,c_new,&(ar->rrt));

	      #if (ATLASRRT_VERBOSE)
	        fprintf(stderr,"{%u->%u}[%g]\n",n[i],GetRRTParent(n[i],&(ar->rrt)),
		        GetRRTNodeCostFromParent(n[i],&(ar->rrt)));
	      #endif
	    }
	  else
	    {
	      /* if the node is connected to a sample in a different tree, update the optimal path */
	      if ((rrtMode==TWO_TREES_WITH_SWAP)&&(steps!=NULL)&&(l!=NULL)&&
		  (GetRRTNodeTree(n[i],&(ar->rrt))!=GetRRTNodeTree(id_new,&(ar->rrt))))
		{
		  c_new+=GetRRTNodeCost(n[i],&(ar->rrt)); /* cost of start to goal via this connection
							     between trees.*/
		  if (c_new<*l)
		    *l=ChangeBiRRTSteps(n[i],id_new,cn,steps,&(ar->rrt));
		}
	    }
	}
    }
}

void AtlasRRTstarCloseIteration(unsigned int it,unsigned int id_goal,
				double time,double gamma,
				double *times,double *costs,
				Tatlasrrt *ar)
{
  /* Print information about the quality of the path so far */

  if ((ATLASRRT_VERBOSE)||((it%1000)==0))
    {
      if (id_goal!=NO_UINT)
	{
	  fprintf(stderr,"Iteration: %u (s:%u nc:%u t:%g g:%g c:%g [%g] [%u])\n",it,ar->ns,ar->nc,
		  time,gamma,GetRRTNodeCost(id_goal,&(ar->rrt)),CostToRoot(id_goal,&(ar->rrt)),id_goal);
	}
      else
	fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,ar->ns,time);
      fflush(stdout);
    }

  /*******************************************************************/
  /* Store information about the quality of the path so far and
     conclude the iteration */

  if (times!=NULL)
    times[it]=time;

  if (costs!=NULL)
    {
      if (id_goal==NO_UINT)
	costs[it]=-1.0;
      else
	costs[it]=GetRRTNodeCost(id_goal,&(ar->rrt)); //CostToRoot(id_goal,&(ar->rrt));
    }
}

void AtlasBiRRTstarCloseIteration(unsigned int it,double l,
				  double time,double gamma,
				  double *times,double *costs,
				  Tatlasrrt *ar)
{
  if ((ATLASRRT_VERBOSE)||((it%1000)==0))
    {
      if (l<INF)
	{
	  fprintf(stderr,"Iteration: %u (s:%u nc: %u t:%g g:%g c:%g)\n",it,ar->ns,ar->nc,
		  time,gamma,l);
	}
      else
	fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,ar->ns,time);
      fflush(stdout);
    }

  if (times!=NULL)
    times[it]=time;

  if (costs!=NULL)
    {
      if (l<INF)
	costs[it]=l;
      else
	costs[it]=-1.0;
    }
}


boolean AtlasRRTstar(Tparameters *pr,double *pg,
		     unsigned int *it,double *times,double *costs,
		     double *planningTime,double *pl,unsigned int *ns,double ***path,
		     TAtlasRRTStatistics *str,Tatlasrrt *ar)
{
  if (EXPLORATION_RRT)
    Error("AtlasRRTstart is not designed for exploration RRTs");

  if (ar->birrt)
    return(AtlasBiRRTstar(pr,pg,it,times,costs,planningTime,pl,ns,path,str,ar));
  else
    {
      double *pWithDummies,*pgs,*t_rand,*x_rand,*x_new;
      unsigned int i,id_new,id_goal,c_rand,samplingMode;
      unsigned int i_near;
      double time,epsilon,delta,er,gamma,ct_gamma;
      Tstatistics st; /* used just to measure execution time */
      boolean collision,expand2Goal,done,optimal,validSample,exploration,onManifold;
      /* cost of paths to neighbouring nodes */
      double *c;
      /* neighbours for each new node */
      unsigned int nn;
      unsigned int *n;
      TAtlasRRTStatistics *arst;
      double maxTime;
      unsigned int maxIterations;
      double h,l;
      Theap q;
      boolean graph;
      unsigned int vt; /* trees in  set of neighbours, only relevant in bi-RRTs */
      double numSamples;
      double scale; /* Global adjustment of sampling areas */

      if (ar->dynamics)
	Error("AtlasRRTstar is not yet implemented for dynamical systems");
      
      if (ar->ns>1)
	Error("AtlasRRTstart must be used to a just initilized RRT");

      #if (GET_ATLASRRT_STATISTICS)
      {
	unsigned int i;

	NEW(arst,1,TAtlasRRTStatistics);
	InitAtlasRRTStatistics(arst);
	for(i=0;i<ar->nc;i++)
	  NewAtlasRRTChart(arst);
	for(i=0;i<ar->ns;i++)
	  NewAtlasRRTSample(arst);
      }
      #else
        arst=NULL;
      #endif

      scale=1.0; /* not used yet */

      /* Init the AtlasRRT structure */
      epsilon=GetParameter(CT_EPSILON,pr);
      delta=GetParameter(CT_DELTA,pr);
      ct_gamma=GetParameter(CT_GAMMA,pr);
      maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
      maxIterations=(unsigned int)GetParameter(CT_MAX_PLANNING_ITERATIONS,pr);
      samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

      graph=IsRRTGraph(&(ar->rrt));

      CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,ar->w);
      CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,ar->w);

      if ((!PointInBoxTopology(NULL,TRUE,ar->m,pgs,epsilon,ar->tp,&(ar->ambient)))||
	  (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,ar->w)))
	Error("The targed point for the AtlasRRTstar is not in domain");

      if (ar->m==ar->k)
	er=0;
      else
	er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,ar->w);
      if (er>epsilon)
	Error("The target point for the AtlasRRTstar is not on the manifold");

      collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,ar->w);
      if (collision)
	Error("The target point for the AtlasRRTstar is in collision");
      free(pWithDummies);

      /* Room for the randomly generated samples (and its correspoinding point
	 on the manifold) */
      NEW(x_rand,ar->m,double);
      NEW(t_rand,ar->k,double);

      /* Reset the output statistics (just in case maxIterations
	 is not reached) */
      for(i=0;i<maxIterations;i++)
	{
	  times[i]=0;
	  costs[i]=-1;
	}

      if (graph)
	InitHeap(sizeof(TDoublePair),CopyDoublePair,NULL,
		 LessThanDoublePair,NULL,TRUE,ar->ms,&q);

      gamma=ct_gamma;
      optimal=(ct_gamma>0);

      id_goal=NO_UINT;
      *it=0;

      InitStatistics((ar->parallel?2:1),0,&st); /* 2 just to indicated multi-core process */
      time=0.0;
      done=FALSE;
      l=INF; /* cost to goal (INF while goal not found) */
      c=NULL; /* default -> no cache of costs to neighbours */

      while ((!done)&&(time<maxTime)&&(*it<maxIterations))
	{
	  #if (HEURISTIC_RRT_STAR&(1))
	    /* keep the cost to goal up to date so that the heuristic
	       is more effective*/
	    if (id_goal!=NO_UINT)
	      UpdateCostAndTree(id_goal,&(ar->rrt));
	  #endif

	  /*******************************************************************/
	  /* best estimation of the cost to goal (up to now) */
	  if (id_goal==NO_UINT)
	    l=INF;
	  else
	    l=GetRRTNodeCost(id_goal,&(ar->rrt));

	  /*******************************************************************/
	  /* Generate a random sample */
	  do {
	    /* Generate the sample */
	    expand2Goal=AtlasRRTSample(pr,samplingMode,*it,START2GOAL,(id_goal==NO_UINT?pgs:NULL),
				       scale,&exploration,&onManifold,
				       &c_rand,t_rand,x_rand,arst,ar);


	    /* validate the random sample */
	    validSample=AtlasRRTValidateSample(pr,c_rand,t_rand,x_rand,START2GOAL,expand2Goal,NO_UINT,
					       pgs,l,&h,&i_near,arst,ar);
	  } while (!validSample);

	  /*******************************************************************/
	  /* Extend the AtlasRRT from x_near to x_rand */
	  /* Note that here we use a connect strategy but we only add the last sample */
	  id_new=AddStepToAtlasRRTstar(pr,*it,expand2Goal,onManifold,i_near,x_rand,
				       &id_goal,pgs,(void*)arst,ar);

	  /*******************************************************************/
	  if (!optimal)
	    {
	      if (id_goal!=NO_UINT)
		done=TRUE;
	    }
	  else
	    {
	      /* If we actually added something */
	      if ((id_new!=i_near)&&((((HEURISTIC_RRT_STAR)&(2))==0)||(id_goal!=NO_UINT)))
		{
		  /* x_new is the last samples added to the tree */
		  x_new=ar->si[id_new]->s;
		  h=DistanceTopology(ar->m,ar->tp,x_new,pgs);

		  /* Wire and re-wire the tree, only we we are interested in an optimal path
		     If heristic #4 is active optimization is delayed until the goal is found */

		  /*******************************************************************/
		  /* Search for the set of potential neighbours */
		  numSamples=(double)(ar->ns<3?3:ar->ns);
		  gamma=ct_gamma*pow(log(numSamples)/numSamples,1.0/(double)ar->k);
		  gamma=(gamma<delta?delta:gamma);

		  GetRRTNNInBall(START2GOAL,x_new,gamma,&nn,&n,&(ar->rrt));

		  /*******************************************************************/
		  /* Wire: Search for the lowest cost path to the new node */
		  WireAtlasRRTstar(pr,id_new,i_near,gamma,nn,n,&c,h,(graph?&q:NULL),&vt,arst,ar);

		  /*******************************************************************/
		  /* Rewire the tree around the new point */
		  if (graph)
		    RecursiveReWireRRTstar(pr,&q,pgs,NULL,&l,&(ar->rrt));
		  else
		    ReWireAtlasRRTstar(pr,id_new,gamma,nn,n,c,NULL,&l,arst,ar);

		  /*******************************************************************/
		  /* release the data for this iteration */
		  if (c!=NULL)
		    free(c);
		  free(n);
		}
	      #if (ATLASRRT_VERBOSE)
	      else
		{
		  if (id_new==i_near)
		    fprintf(stderr,"  Blocked [%u]\n",i_near);
		}
	      #endif
	    }

	  /*******************************************************************/
	  /* Print a summary about this iteration */
	  time=GetElapsedTime(&st);

	  AtlasRRTstarCloseIteration(*it,id_goal,time,gamma,times,costs,ar);

	  (*it)++;
	}

      if (graph)
	DeleteHeap(&q);

      *planningTime=time;

      DeleteStatistics(&st);

      fprintf(stderr,"Final number of samples: %u\n",ar->ns);

      /* Reconstruct the path (if any) */
      if (id_goal!=NO_UINT)
	ReconstructAtlasRRTPath(pr,id_goal,pl,ns,path,ar);

      /* Release memory */
      free(t_rand);
      free(x_rand);
      free(pgs);

      #if (GET_ATLASRRT_STATISTICS)
        if (str==NULL)
	  PrintAtlasRRTStatistics(ar,arst);
	else
	  AccumulateAtlasRRTStatistics(arst,str);
	DeleteAtlasRRTStatistics(arst);
	free(arst);
      #endif

      return(id_goal!=NO_UINT);
    }
}

boolean AtlasBiRRTstar(Tparameters *pr,double *pg,
		       unsigned int *it,double *times,double *costs,
		       double *planningTime,double *pl,unsigned int *ns,double ***path,
		       TAtlasRRTStatistics *str,Tatlasrrt *ar)
{

  if (EXPLORATION_RRT)
    Error("AtlasBiRRTstart is not designed for exploration RRTs");

  if (!ar->birrt)
    return(AtlasRRTstar(pr,pg,it,times,costs,planningTime,pl,ns,path,str,ar));
  else
    {
      double *x_rand,*t_rand,*g;
      unsigned int c_rand;
      unsigned int i_near;
      double delta;
      Tstatistics st; /* used just to measure execution time */
      double time;
      /* if the cost function is symmetrical, we cache
	 the evaluation of the cost to neighbour. */
      double *c;
      /* neighbours for each new node */
      unsigned int nn;
      unsigned int *n;
      /* distance x_rand,tree */
      double gamma,ct_gamma;
      unsigned int i,id_new,samplingMode;
      double *x_new;
      boolean done,optimal,validSample,exploration,onManifold;
      double l;           /* length of the shortest path so far */
      double h;
      Theap q;
      Tvector steps;
      TAtlasRRTStatistics *arst;
      double maxTime;
      unsigned int maxIterations;
      boolean graph;
      unsigned int vt;
      double l1,c12;
      double numSamples;
      double scale; /* Global adjust of sampling areas */
      TAtlasRRTBranchConfig configExtend;
      TAtlasRRTBranchState stateExtend;
      
      if (ar->dynamics)
	Error("AtlasBiRRTstar is not yet implemented for dynamical systems");
      
      InitBranchConfig(CONNECT_SAMPLES,&configExtend);

      if (ar->ns>2)
	Error("AtlasBiRRTstart must be used to a just initilized RRT");

      #if (GET_ATLASRRT_STATISTICS)
      {
	unsigned int i;

	NEW(arst,1,TAtlasRRTStatistics);
	InitAtlasRRTStatistics(arst);
	for(i=0;i<ar->nc;i++)
	  NewAtlasRRTChart(arst);
	for(i=0;i<ar->ns;i++)
	  NewAtlasRRTSample(arst);
      }
      #else
        arst=NULL;
      #endif

      scale=1.0; /* not used yet */

      /* Init the RRT structure */
      delta=GetParameter(CT_DELTA,pr);
      ct_gamma=GetParameter(CT_GAMMA,pr);
      maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
      maxIterations=(unsigned int)GetParameter(CT_MAX_PLANNING_ITERATIONS,pr);
      samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

      graph=IsRRTGraph(&(ar->rrt));

      /* Room for the randomly generated samples (and its correspoinding point
	 on the manifold) */
      NEW(x_rand,ar->m,double);
      NEW(t_rand,ar->k,double);

      /* Reset the output statistics (just in case maxIterations
	 is not reached) */
      for(i=0;i<maxIterations;i++)
	{
	  times[i]=0;
	  costs[i]=-1;
	}

      if (graph)
	InitHeap(sizeof(TDoublePair),CopyDoublePair,NULL,
		 LessThanDoublePair,NULL,TRUE,ar->ms,&q);

      gamma=ct_gamma;
      optimal=(ct_gamma>0);

      *it=0;

      InitStatistics((ar->parallel?2:1),0,&st); /* if parallel 2 indicates multi-core */
      time=0.0;
      done=FALSE;

      InitVector(sizeof(TRRTStep),CopyRRTStep,NULL,100,&steps);
      l=INF;
      c=NULL;

      while ((!done)&&(time<maxTime)&&(*it<maxIterations))
	{
	  /* keep the optimal path up to date (if any) */
	  if (l<INF)
	    l=UpdateBiRRTSteps(&steps,&(ar->rrt));

	  /*******************************************************************/
	  do {
	    /* Geerate a random sample */
	    AtlasRRTSample(pr,samplingMode,*it,BOTHTREES,NULL,scale,
			   &exploration,&onManifold,&c_rand,t_rand,x_rand,arst,ar);

	    /* validate the random sample */
	    validSample=AtlasRRTValidateSample(pr,c_rand,t_rand,x_rand,BOTHTREES,FALSE,NO_UINT,
					       ar->si[1]->s,l,&h,&i_near,arst,ar);
	  } while (!validSample);

	  /*******************************************************************/
	  /* decide who is the goal (for the heuristic)  */
	  if (GetRRTNodeTree(i_near,&(ar->rrt))==START2GOAL)
	    g=ar->si[1]->s;
	  else
	    g=ar->si[0]->s;
	  h=DistanceTopology(ar->m,ar->tp,x_rand,g);


	  /*******************************************************************/
	  /* Extend the AtlasRRT from x_near to x_rand using the cbiRRT extend method */
	  /* Note that here we use a extend strategy (we only add one sample) */

	  id_new=AddStepToAtlasRRTstar(pr,*it,FALSE,onManifold,i_near,x_rand,
				       NULL,NULL,(void*)arst,ar);

	  /* If we actually added something */
	  if ((id_new!=i_near)&&((((HEURISTIC_RRT_STAR)&(2))==0)||(l<INF)))
	    {
	      /* x_new is the last samples added to the tree */
	      x_new=ar->si[id_new]->s;
	      h=DistanceTopology(ar->m,ar->tp,x_new,g);

	      /*******************************************************************/
	      /* Search for the set of potential neighbours */
	      numSamples=(double)(ar->ns<3?3:ar->ns);
	      gamma=ct_gamma*pow(log(numSamples)/numSamples,1.0/(double)ar->k);
	      gamma=(gamma<delta?delta:gamma);

	      GetRRTNNInBall(BOTHTREES,x_new,gamma,&nn,&n,&(ar->rrt));

	      /*******************************************************************/
	      /* Wire: Search for the lowest cost path to the new node */
	      WireAtlasRRTstar(pr,id_new,i_near,gamma,nn,n,&c,h,(graph?&q:NULL),&vt,arst,ar);

	      /*******************************************************************/
	      /* Rewire the tree around the new point */
	      if (graph)
		RecursiveReWireRRTstar(pr,&q,g,&steps,&l,&(ar->rrt));
	      else
		ReWireAtlasRRTstar(pr,id_new,gamma,nn,n,c,&steps,&l,arst,ar);

	      /*******************************************************************/
	      /* release the data for this iteration (cost and neighbours) */
	      if (c!=NULL)
		free(c);
	      free(n);

	      /*******************************************************************/
	      /* If the set of neighbours does not include nodes in the two trees
		 and we do not have a path start<->goal we try to connect the two
		 trees (this is hardly used since when l=INF, gamma is large and
		 the neighbours always include nodes in the two trees) */
	      //if ((vt!=BOTHTREES)&&(l==INF))
	      if (vt!=BOTHTREES)
		{
		  /* In the re-wire the current sample might end up in tree 't2'
		     and the connection must be always with the other tree */
		  if (GetRRTNodeTree(id_new,&(ar->rrt))==START2GOAL)
		    i_near=GetRRTNN(GOAL2START,x_new,&(ar->rrt));
		  else
		    i_near=GetRRTNN(START2GOAL,x_new,&(ar->rrt));

		  l1=GetRRTNodeCost(id_new,&(ar->rrt))+GetRRTNodeCost(i_near,&(ar->rrt));

		  configExtend.maxLength=(l<INF?l-l1:0.0);
		  c12=AddBranchToAtlasRRT(pr,NO_UINT,&configExtend,0,NULL,NULL,NULL,NULL,NULL,id_new,ar->si[i_near]->s,NULL,
					  (void*)arst,&stateExtend,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ar);

		  if (stateExtend.reachedQrand)
		    {
		      if (graph)
			AddEdgeToRRT(id_new,i_near,c12,&(ar->rrt));
		      l1+=c12;
		      if (l1<l)
			l=ChangeBiRRTSteps(id_new,i_near,c12,&steps,&(ar->rrt));
		    }
		}
	    }
	  #if (ATLASRRT_VERBOSE)
	  else
	    {
	      if (id_new==i_near)
		fprintf(stderr,"  Blocked [%u]\n",i_near);
	    }
	  #endif

	  if (!optimal)
	    done=(l<INF);

	  /*******************************************************************/
	  /* Conclude the iteration */
	  time=GetElapsedTime(&st);

	  AtlasBiRRTstarCloseIteration(*it,l,time,gamma,times,costs,ar);

	  (*it)++;
	}

      if (graph)
	DeleteHeap(&q);

      *planningTime=GetElapsedTime(&st);

      DeleteStatistics(&st);

      fprintf(stderr,"Final number of samples: %u\n",ar->ns);

      /* Reconstruct the path (if any) */
      if (l<INF)
	Steps2PathinAtlasRRT(pr,&steps,pl,NULL,ns,path,ar);

      /* Release memory */
      free(x_rand);
      free(t_rand);
      DeleteVector(&steps);

      #if (GET_ATLASRRT_STATISTICS)
        if (str==NULL)
	  PrintAtlasRRTStatistics(ar,arst);
	else
	  AccumulateAtlasRRTStatistics(arst,str);
	DeleteAtlasRRTStatistics(arst);
	free(arst);
      #endif

      return(l<INF);
    }
}

unsigned int GetAtlasRRTNumNodes(Tatlasrrt *ar)
{
  return(ar->ns);
}

unsigned int GetAtlasRRTNumCharts(Tatlasrrt *ar)
{
  return(ar->nc);
}

unsigned int GetRRTNNInChart(Tparameters *pr,unsigned int t2g,unsigned int tree,
			     unsigned int chartId,double *x_rand,
			     double *d,Tatlasrrt *ar)
{
  double d1;
  unsigned int j,inear;
  double de;
  Tchart *c;
  double *t_rand;

  c=GetAtlasChart(chartId,&(ar->atlas));

  NEW(t_rand,ar->k,double);
  Manifold2Chart(x_rand,ar->tp,t_rand,c);
  
  #if (ATLASRRT_VERBOSE>2)
    PrintVector(stderr,"  t_rand",ar->k,t_rand);
  #endif

  *d=INF;
  inear=NO_UINT;
  j=ar->ci[chartId]->lc;
  while(j!=NO_UINT)
    {
      if ((!ar->birrt)||(GetRRTNodeTree(j,&(ar->rrt))==tree))
	{
	  if (t2g)
	    {
	      #if (ATLASRRT_VERBOSE>2)
	        fprintf(stderr,"  Point: %u ",j);PrintVector(stderr,"t",ar->k,ar->si[j]->t);
	      #endif
	      d1=Time2Go(pr,tree,c,ar->si[j]->t,ar->si[j]->s,t_rand,x_rand,&de,ar->ds);
	    }
	  else
	    d1=DistanceTopologyMin(*d,ar->k,NULL,t_rand,ar->si[j]->t);

	  if (d1<*d)
	    {
	      *d=d1;
	      inear=j;
	    }
	}
      j=ar->si[j]->lsc;
    }

  #if (ATLASRRT_VERBOSE>2)
    if (*d==INF)
      fprintf(stderr,"  No NN in chart\n");
    else
      fprintf(stderr,"  NN in chart %u: %u %f\n",chartId,inear,*d);
  #endif
    
  free(t_rand);

  return(inear);
}

unsigned int Time2GoNNToTree(Tparameters *pr,unsigned int tree,unsigned int goal,Tatlasrrt *ar)
{
  double *gt,*gs;
  unsigned int i,i_near,n,nct=0,*chartsAtTree;
  double d,dm;

  if (GetRRTNodeTree(goal,&(ar->rrt))==tree)
    Error("Time2GoNNToTree used with a goal in the same tree");

  NEW(gt,ar->k,double);

  dm=INF;
  i_near=NO_UINT;

  if (tree==START2GOAL)
    {
      nct=ar->nct1;
      chartsAtTree=ar->chartsAtTree1;
    }
  else
    {
      if (tree==GOAL2START)
	{
	  nct=ar->nct2;
	  chartsAtTree=ar->chartsAtTree2;
	}
      else
	Error("Time2GoNNToTree used with a wrong tree");
    }

  gs=ar->si[goal]->s;

  /* Time to go for the samples in all the charts of the tree */
  #if (0)
  {
    unsigned int n1;

    for(i=0;i<nct;i++)
      {
	n=chartsAtTree[i];
	n1=GetRRTNNInChart(pr,T2G_METRIC_NN_CONNECT,tree,n,gs,&d,ar);
	if (d<dm)
	  {
	    dm=d;
	    i_near=n1;
	  }
      }
  }
  #endif

  /* Time to go for the samples in the chart closer to the goal
     (closer in Euclidean terms) */
  #if (1)
  {
    Tchart *c;
    double *tc;
    double de;

    /* all charts's centers have parameters =0 */
    NEWZ(tc,ar->k,double);

    for(i=0;i<nct;i++)
      {
	n=chartsAtTree[i];
	c=GetAtlasChart(n,&(ar->atlas));
	Manifold2Chart(gs,ar->tp,gt,c);
	d=Time2Go(pr,tree,c,tc,GetChartCenter(c),gt,gs,&de,ar->ds);
	if (d<dm)
	  {
	    dm=d;
	    i_near=i;
	  }
      }

    free(tc);

    if (i_near!=NO_UINT)
      i_near=GetRRTNNInChart(pr,T2G_METRIC_NN_CONNECT,tree,i_near,gs,&dm,ar);
  }
  #endif

  free(gt);

  return(i_near);
}

void PlotAtlasRRT(char *prefix,int argc,char **arg,Tparameters *pr,
		  unsigned int xID,unsigned int yID,unsigned int zID,
		  double *p1,double *p2,Tatlasrrt *ar)
{
  Tfilename fplot;
  unsigned int i;
  Tchart *chart1,*chart2;
  double *sample1,*sample2;
  unsigned int parent;
  double x[4],y[4],z[4];
  double *point1,*point2;
  double *o1,*o2,*o3,*o4;
  Tcolor color;
  Tplot3d p3d;
  double cx,cy,cz;

  cx=GetParameter(CT_CUT_X,pr);
  cy=GetParameter(CT_CUT_Y,pr);
  cz=GetParameter(CT_CUT_Z,pr);

  CreateFileName(NULL,prefix,"_rrt",PLOT3D_EXT,&fplot);
  fprintf(stderr,"Plotting RRT to                   : %s\n",GetFileFullName(&fplot));
  PlotRRT(GetFileFullName(&fplot),argc,arg,pr,xID,yID,zID,p1,p2,&(ar->rrt));
  DeleteFileName(&fplot);

  if ((!PLOT_AS_POLYGONS)||(ar->k<4))
    {
      CreateFileName(NULL,prefix,"_atlas",PLOT3D_EXT,&fplot);
      fprintf(stderr,"Plotting Atlas to                 : %s\n",GetFileFullName(&fplot));
      PlotAtlas(GetFileFullName(&fplot),argc,arg,pr,NULL,xID,yID,zID,&(ar->atlas));
      DeleteFileName(&fplot);
    }
  else
    fprintf(stderr,"Skipping the plot of the atlas (too large dimension)\n");

  /* Now we plot the RRT in the tangent space and a line from tangent space to
     the RRT. This basically replicates the plot of the RRT but in the tangent
     space */

  CreateFileName(NULL,prefix,"_atlasrrt",PLOT3D_EXT,&fplot);
  fprintf(stderr,"Plotting AtlasRRT to              : %s\n",GetFileFullName(&fplot));

  InitPlot3d(GetFileFullName(&fplot),FALSE,argc,arg,&p3d);
  DeleteFileName(&fplot);

  NEW(point1,ar->m,double);
  NEW(point2,ar->m,double);

  NewColor(0.5,0,0,&color); /*red*/
  StartNew3dObject(&color,&p3d);

  for(i=(ar->birrt?2:1);i<ar->ns;i++)
    {
      if ((!ar->birrt)||(GetRRTNodeTree(i,&(ar->rrt))==START2GOAL))
	{
	  parent=GetRRTParent(i,&(ar->rrt));

	  chart1=GetAtlasChart(ar->si[i]->c,&(ar->atlas));
	  chart2=GetAtlasChart(ar->si[parent]->c,&(ar->atlas));

	  //if (chart1==chart2)
	  {
	    sample1=ar->si[i]->s;
	    sample2=ar->si[parent]->s;

	    CS_WD_REGENERATE_ORIGINAL_POINT(pr,sample1,&o1,ar->w);
	    CS_WD_REGENERATE_ORIGINAL_POINT(pr,sample2,&o2,ar->w);

	    Local2Global(ar->si[i]->t,NULL,point1,chart1);
	    Local2Global(ar->si[parent]->t,NULL,point2,chart2);

	    CS_WD_REGENERATE_ORIGINAL_POINT(pr,point1,&o3,ar->w);
	    CS_WD_REGENERATE_ORIGINAL_POINT(pr,point2,&o4,ar->w);

	    x[0]=o1[xID];
	    y[0]=o1[yID];
	    z[0]=o1[zID];
	    CORRECT_POINT_PLOT(cx,cy,cz,x[0],y[0],z[0]);

	    x[1]=o3[xID];
	    y[1]=o3[yID];
	    z[1]=o3[zID];
	    CORRECT_POINT_PLOT(cx,cy,cz,x[1],y[1],z[1]);

	    x[2]=o4[xID];
	    y[2]=o4[yID];
	    z[2]=o4[zID];
	    CORRECT_POINT_PLOT(cx,cy,cz,x[2],y[2],z[2]);

	    x[3]=o2[xID];
	    y[3]=o2[yID];
	    z[3]=o2[zID];
	    CORRECT_POINT_PLOT(cx,cy,cz,x[3],y[3],z[3]);

	    PlotVect3d(4,x,y,z,&p3d);

	    free(o1);
	    free(o2);
	    free(o3);
	    free(o4);
	  }
	}
    }
  DeleteColor(&color);
  Close3dObject(&p3d);

  if (ar->birrt)
    {
      NewColor(0,0.5,0,&color); /*green*/
      StartNew3dObject(&color,&p3d);

      for(i=2;i<ar->ns;i++)
	{
	  if (GetRRTNodeTree(i,&(ar->rrt))==GOAL2START)
	    {
	      parent=GetRRTParent(i,&(ar->rrt));

	      chart1=GetAtlasChart(ar->si[i]->c,&(ar->atlas));
	      chart2=GetAtlasChart(ar->si[parent]->c,&(ar->atlas));

	      //if (chart1==chart2)
	      {
		sample1=ar->si[i]->s;
		sample2=ar->si[parent]->s;

		CS_WD_REGENERATE_ORIGINAL_POINT(pr,sample1,&o1,ar->w);
		CS_WD_REGENERATE_ORIGINAL_POINT(pr,sample2,&o2,ar->w);

		Local2Global(ar->si[i]->t,NULL,point1,chart1);
		Local2Global(ar->si[parent]->t,NULL,point2,chart2);

		CS_WD_REGENERATE_ORIGINAL_POINT(pr,point1,&o3,ar->w);
		CS_WD_REGENERATE_ORIGINAL_POINT(pr,point2,&o4,ar->w);

		x[0]=o1[xID];
		y[0]=o1[yID];
		z[0]=o1[zID];
		CORRECT_POINT_PLOT(cx,cy,cz,x[0],y[0],z[0]);

		x[1]=o3[xID];
		y[1]=o3[yID];
		z[1]=o3[zID];
		CORRECT_POINT_PLOT(cx,cy,cz,x[1],y[1],z[1]);

		x[2]=o4[xID];
		y[2]=o4[yID];
		z[2]=o4[zID];
		CORRECT_POINT_PLOT(cx,cy,cz,x[2],y[2],z[2]);

		x[3]=o2[xID];
		y[3]=o2[yID];
		z[3]=o2[zID];
		CORRECT_POINT_PLOT(cx,cy,cz,x[3],y[3],z[3]);

		PlotVect3d(4,x,y,z,&p3d);

		free(o1);
		free(o2);
		free(o3);
		free(o4);
	      }
	    }
	}
      DeleteColor(&color);
      Close3dObject(&p3d);
    }

  #if (RRT_PLOT_NODES)
    /* Dots, one per node */
    NewColor(0,0,0,&color); /*black*/
    StartNew3dObject(&color,&p3d);

    for(i=0;i<ar->ns;i++)
      {
	chart1=GetAtlasChart(ar->si[i]->c,&(ar->atlas));
	Local2Global(ar->si[i]->t,NULL,point1,chart1);
	CS_WD_REGENERATE_ORIGINAL_POINT(pr,point1,&o1,ar->w);

	x[0]=o1[xID]-0.005;
	y[0]=o1[yID];
	z[0]=o1[zID];
	CORRECT_POINT_PLOT(cx,cy,cz,x[0],y[0],z[0]);

	x[1]=o1[xID]+0.005;
	y[1]=o1[yID];
	z[1]=o1[zID];
	CORRECT_POINT_PLOT(cx,cy,cz,x[1],y[1],z[1]);

	PlotVect3d(2,x,y,z,&p3d);

	x[0]=o1[xID];
	y[0]=o1[yID]-0.005;
	z[0]=o1[zID];
	CORRECT_POINT_PLOT(cx,cy,cz,x[0],y[0],z[0]);

	x[1]=o1[xID];
	y[1]=o1[yID]+0.005;
	z[1]=o1[zID];
	CORRECT_POINT_PLOT(cx,cy,cz,x[1],y[1],z[1]);

	PlotVect3d(2,x,y,z,&p3d);

	x[0]=o1[xID];
	y[0]=o1[yID];
	z[0]=o1[zID]-0.005;
	CORRECT_POINT_PLOT(cx,cy,cz,x[0],y[0],z[0]);

	x[1]=o1[xID];
	y[1]=o1[yID];
	z[1]=o1[zID]+0.005;
	CORRECT_POINT_PLOT(cx,cy,cz,x[1],y[1],z[1]);

	PlotVect3d(2,x,y,z,&p3d);

	free(o1);
      }

    DeleteColor(&color);
    Close3dObject(&p3d);
  #endif

  ClosePlot3d(FALSE,&p3d);

  free(point1);
  free(point2);
}

unsigned int AtlasRRTMemSize(Tatlasrrt *ar)
{
  unsigned int b;

  b=RRTMemSize(&(ar->rrt));
  b+=AtlasMemSize(&(ar->atlas));

  return(b);
}

void SaveAtlasRRT(Tparameters *pr,char *prefix,Tatlasrrt *ar)
{
  Tfilename fsave;
  FILE *f;
  unsigned int i;

  CreateFileName(NULL,prefix,NULL,RRT_EXT,&fsave);
  fprintf(stderr,"Writing RRT to                    : %s\n",GetFileFullName(&fsave));
  SaveRRT(&fsave,&(ar->rrt));
  DeleteFileName(&fsave);

  CreateFileName(NULL,prefix,NULL,ATLAS_EXT,&fsave);
  fprintf(stderr,"Writing atlas to                  : %s\n",GetFileFullName(&fsave));
  SaveAtlas(pr,&fsave,&(ar->atlas));
  DeleteFileName(&fsave);

  CreateFileName(NULL,prefix,NULL,ATLAS_RRT_EXT,&fsave);
  fprintf(stderr,"Writing AtlasRRT to               : %s\n",GetFileFullName(&fsave));
  f=fopen(GetFileFullName(&fsave),"w");
  if (!f)
    Error("Could not open file to write the AtlasRRT information");
  DeleteFileName(&fsave);

  fprintf(f,"%u\n",ar->m);
  fprintf(f,"%u\n",ar->k);
  fprintf(f,"%.12f\n",ar->e);
  fprintf(f,"%.12f\n",ar->ce);
  fprintf(f,"%.12f\n",ar->r);
  fprintf(f,"%u\n",ar->dynamics);
  if (ar->dynamics)
    {
      fprintf(f,"%.12f\n",ar->dge);
      fprintf(f,"%u\n",ar->da);
    }
  fprintf(f,"%u\n",ar->birrt);

  fprintf(f,"%u\n",ar->ms);
  fprintf(f,"%u\n",ar->ns);
  for(i=0;i<ar->ns;i++)
    SaveAtlasRRTSampleInfo(f,ar->si[i],ar);

  fprintf(f,"%u\n",ar->mc);
  fprintf(f,"%u\n",ar->nc);
  for(i=0;i<ar->nc;i++)
    SaveAtlasRRTChartInfo(f,ar->ci[i],ar);

  if (ar->birrt)
    {
      fprintf(f,"%u\n",ar->mct1);
      fprintf(f,"%u\n",ar->nct1);
      for(i=0;i<ar->nct1;i++)
	fprintf(f,"%u ",ar->chartsAtTree1[i]);
      fprintf(f,"\n");

      fprintf(f,"%u\n",ar->mct2);
      fprintf(f,"%u\n",ar->nct2);
      for(i=0;i<ar->nct2;i++)
	fprintf(f,"%u ",ar->chartsAtTree2[i]);
      fprintf(f,"\n");
    }
  fclose(f);
}

void LoadAtlasRRT(Tparameters *pr,char *prefix,TAtlasBase *w,Tatlasrrt *ar)
{
  Tfilename fload;
  FILE *f;
  unsigned int i;

  CreateFileName(NULL,prefix,NULL,RRT_EXT,&fload);
  fprintf(stderr,"Reading RRT from                  : %s\n",GetFileFullName(&fload));
  LoadRRT(pr,&fload,w,&(ar->rrt));
  DeleteFileName(&fload);

  CreateFileName(NULL,prefix,NULL,ATLAS_EXT,&fload);
  fprintf(stderr,"Reading atlas from                : %s\n",GetFileFullName(&fload));
  LoadAtlas(pr,&fload,w,&(ar->atlas));
  DeleteFileName(&fload);

  CreateFileName(NULL,prefix,NULL,ATLAS_RRT_EXT,&fload);
  fprintf(stderr,"Reading AtlasRRT from             : %s\n",GetFileFullName(&fload));
  f=fopen(GetFileFullName(&fload),"r");
  if (!f)
    Error("Could not open file to load the AtlasRRT information");
  DeleteFileName(&fload);

  ar->w=w;

  fscanf(f,"%u",&(ar->m));
  fscanf(f,"%u",&(ar->k));
  fscanf(f,"%lf",&(ar->e));
  fscanf(f,"%lf",&(ar->ce));
  fscanf(f,"%lf",&(ar->r));
  fscanf(f,"%u",&(ar->dynamics));
  if (ar->dynamics)
    {
      fscanf(f,"%lf",&(ar->dge));
      fscanf(f,"%u",&(ar->da));
    }
  else
    {
      ar->dge=INF;
      ar->da=0;
    }
  fscanf(f,"%u",&(ar->birrt));
  ar->parallel=FALSE; /* AtlasRRts loaded from files are not processed in parallel */

  fscanf(f,"%u",&(ar->ms));
  fscanf(f,"%u",&(ar->ns));
  NEW(ar->si,ar->ms,TSampleInfo *);
  for(i=0;i<ar->ns;i++)
    {
      NEW(ar->si[i],1,TSampleInfo);
      LoadAtlasRRTSampleInfo(f,ar->si[i],ar);
    }

  fscanf(f,"%u",&(ar->mc));
  fscanf(f,"%u",&(ar->nc));
  NEW(ar->ci,ar->mc,TChartInfo *);
  for(i=0;i<ar->nc;i++)
    {
      NEW(ar->ci[i],1,TChartInfo);
      LoadAtlasRRTChartInfo(f,ar->ci[i],ar);
    }

  if (ar->birrt)
    {
      fscanf(f,"%u",&(ar->mct1));
      fscanf(f,"%u",&(ar->nct1));
      NEW(ar->chartsAtTree1,ar->mct1,unsigned int);
      for(i=0;i<ar->nct1;i++)
	fscanf(f,"%u",&(ar->chartsAtTree1[i]));

      fscanf(f,"%u",&(ar->mct2));
      fscanf(f,"%u",&(ar->nct2));
      NEW(ar->chartsAtTree2,ar->mct2,unsigned int);
      for(i=0;i<ar->nct2;i++)
	fscanf(f,"%u",&(ar->chartsAtTree2[i]));
    }
  fclose(f);

  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&(ar->ambient),ar->w);
  
  ar->tp=GetRRTTopology(&(ar->rrt));
  
  ar->weights=GetRRTWeights(&(ar->rrt));
  
  CS_WD_GET_SIMP_JACOBIAN(pr,&(ar->J),ar->w);
  if (ar->dynamics)
    {
      unsigned int nt;

      #ifdef _OPENMP
        if (ar->parallel)
	  nt=omp_get_max_threads();
	else
	  nt=1;
      #else
	nt=1;
      #endif

      NEW(ar->ds,nt,TDynamicSpace);
      for(i=0;i<nt;i++)
	InitDynamicSpace(pr,ar->parallel,&(ar->J),ar->w,&(ar->ds[i])); /* This requires the Jacobian!! */
    }
}

void PrintAtlasRRTDefines(FILE *f)
{
  PrintAtlasDefines(f);
  PrintRRTDefines(f);
  fprintf(f,"\n   %% AtlasRRT defines\n");
  fprintf(f,"   REVISIT_CHARTS %u\n",REVISIT_CHARTS);
  fprintf(f,"   REPEAT_CHARTS %u\n",REPEAT_CHARTS);
  fprintf(f,"   ATLASRRT_VERBOSE %u\n",ATLASRRT_VERBOSE);
  fprintf(f,"   DEBUG_SIMULATION %u\n",DEBUG_SIMULATION);
  fprintf(f,"   GET_ATLASRRT_STATISTICS %u\n",GET_ATLASRRT_STATISTICS);
  fprintf(f,"   RANDOM_INT_TIME %u\n",RANDOM_INT_TIME);
  fprintf(f,"   RANDOMIZED_LQR %.2f\n",RANDOMIZED_LQR);
  fprintf(f,"   DYNAMICS_ADD_ALL %u\n",DYNAMICS_ADD_ALL);
  fprintf(f,"   RELINEALIZE_DYNAMICS %u\n",RELINEALIZE_DYNAMICS);
  fprintf(f,"   ATLASRRT_DYNAMIC_CONNECT %u\n",ATLASRRT_DYNAMIC_CONNECT);
  fprintf(f,"   ADJUST_SA %u\n",ADJUST_SA);
  fprintf(f,"   NN_IN_CHART %u\n",NN_IN_CHART);
  fprintf(f,"   NN_IN_NEIGHBOUR_CHART %u\n",NN_IN_NEIGHBOUR_CHART);
  fprintf(f,"   GET_ATLASRRT_GLOBAL_CURV_CHECK %u\n",GET_ATLASRRT_GLOBAL_CURV_CHECK);
  fprintf(f,"   REJECT_USING_DYNAMIC_CONE %u\n",REJECT_USING_DYNAMIC_CONE);
  PrintDynamicsDefines(f);
}

void DeleteAtlasRRT(Tatlasrrt *ar)
{
  unsigned int i;

  DeleteBox(&(ar->ambient));

  DeleteAtlas(&(ar->atlas));
  DeleteRRT(&(ar->rrt));

  /* Release sample info */
  for(i=0;i<ar->ns;i++)
    {
      /* DeleteSampleInfo(i) */

      /* ar->si[i]->s Is a pointer to the RRT structure -> do not free it */
      free(ar->si[i]->t);
      free(ar->si[i]);
    }
  free(ar->si);

  /* Release chart info */
  for(i=0;i<ar->nc;i++)
    free(ar->ci[i]);

  free(ar->ci);

  /* Release the assignment of charts to trees */
  if (ar->birrt)
    {
      free(ar->chartsAtTree1);
      free(ar->chartsAtTree2);
    }

  DeleteJacobian(&(ar->J));

  if (ar->dynamics)
    {
      unsigned int nt;

      #ifdef _OPENMP
        if (ar->parallel)
	  nt=omp_get_max_threads();
	else 
	  nt=1;
      #else
	nt=1;
      #endif

      for(i=0;i<nt;i++)
	DeleteDynamicSpace(&(ar->ds[i]));
      free(ar->ds);
    }
}
