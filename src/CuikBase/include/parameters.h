#ifndef PARAMETERSH
#define PARAMETERSH 

#include "boolean.h"

#include <stdio.h>

/** 
   \file parameters.h

   \brief  Definition of the functions to deal with parameters. 

   Definition of the functions to deal with the parameters given in a <b>.param</b> file.
   The available parameters are:


   - <b>General parameters:</b>
      - \ref CT_EPSILON "EPSILON" Numerical accuracy
      - \ref CT_REPRESENTATION "REPRESENTATION" Representation of the problems
      .
   - <b>Parameters used in position analysis</b> (branch-and-prune techniques)
      - \ref CT_RHO "RHO" Reduction ration for boxes.
      - \ref CT_SMALL_SIGMA "SMALL_SIGMA" Minimum size for boxes while reducing them.
      - \ref CT_SIGMA "SIGMA" Minimun size for boxes when splitting them.
      - \ref CT_N_SOLUTIONS "N_SOLUTIONS" Number of solutions required.
      - \ref CT_DUMMIFY "DUMMIFY" Dummification level.
      - \ref CT_SPLIT_TYPE "SPLIT_TYPE" Method used to split boxes.
      - \ref CT_SAFE_SIMPLEX "SAFE_SIMPLEX" Safety method to ensure correctness in the simplex output.
      - \ref CT_SIMPLIFICATION_LEVEL "SIMPLIFICATION_LEVEL" Simplification level
      - \ref CT_LR2TM_Q "LR2TM_Q" Theshold to use linear relaxations in quadratic equations.
      - \ref CT_LR2TM_S "LR2TM_S" Theshold to use linear relaxations in saddle equations.
      - \ref CT_STATE_PERIOD "STATE_PERIOD" Interval between two consecutive saves of the internal state.
      .
   - <b>Parameters for altas construction</b> (also used in atlas-based planning): 
      - \ref CT_E "E" Error from tangent to manifold.
      - \ref CT_CE "CE" Curvature error.
      - \ref CT_R "R" Radius of the chart.
      - \ref CT_MAX_CHARTS "MAX_CHARTS" Maximum number of charts.
      - \ref CT_DETECT_BIFURCATIONS "DETECT_BIFURCATIONS" Bifurcation detection.
      .
   - <b>Parameters used in planning</b> (higher-dimensional continuation techniques)
      - \ref CT_N_DOF "N_DOF" Number of degrees of freedom.
      - \ref CT_CD_ENGINE "CD_ENGINE" Select the collision detection library.
      - \ref CT_DELTA "DELTA" Step in tangent space.
      - \ref CT_MAX_PLANNING_TIME "MAX_PLANNING_TIME" Maximum planning time.
      - \ref CT_MAX_NEWTON_ITERATIONS "MAX_NEWTON_ITERATIONS" Maximum number of iterations in the Newton processes.
      - <b>RRT-based planning</b>
         - \ref CT_SAMPLING "SAMPLING" Sampling method to use (in RRT).
         - \ref CT_SR "SR" Sampling radious (in RRT). 
         - \ref CT_MAX_NODES_RRT "MAX_NODES_RRT" Maximum number of nodes in the RRT.
         - \ref CT_BI_RRT "BI_RRT" If true, the planning uses a bidirectional RRT.
         - <b>Kinodynamic motion planning</b>
            - \ref CT_DYNAMICS "DYNAMICS" if >0, the problem takes into account dynamic parameters.
            - \ref CT_INTEGRATION_TIME "INTEGRATION_TIME" Integration time.
            - \ref CT_DEFAULT_MAX_VELOCITY "DEFAULT_MAX_VELOCITY" Default maximum velocity for joints.
            - \ref CT_DYNAMIC_GOAL_ERROR "DYNAMIC_GOAL_ERROR" Tolerance for goal reaching (or tree connection).
            - \ref CT_NEG_LM "NEG_LM" Reject positive Lagrange multipliers (experimental).
            - \ref CT_G_COMPENSATION "G_COMPENSATION" Gravity compensation (experimetal).
            - \ref CT_G_AXIS "G_AXIS" Axis giving the gravity vector.
            - \ref CT_N_DYNAMIC_ACTIONS "N_DYNAMIC_ACTIONS" Number of actions to sample. If 0, use LQR to select the action.
	    - <b>LQR-based policy computation</b>
               - \ref CT_TAU "TAU" Balance between time and action cost in the LQR.
               - \ref CT_LQR_PLANNING_TIME "LQR_PLANNING_TIME" Planning horizon for the LQR.
	       .
	    .
         - <b>Transition-based RRT</b>
            - \ref CT_COEF_TEMP "COEF_TEMP" Temperature coefficient.
            - \ref CT_NFAIL_MAX "NFAIL_MAX" Maximum number of fails.
            .
         - <b>Dynamic domain</b>
            - \ref CT_DYNAMIC_DOMAIN "DYNAMIC_DOMAIN" If true, the dynamic domain technique is used.
            .
         - <b>Asymptotically-optimal path planning</b> 
            - \ref CT_RRT_GRAPH "RRT_GRAPH" If true, the RRT stores a graph structure (not only a tree).
            - \ref CT_GAMMA "GAMMA" Constant part of the nearest-neighbour radious used in AtlasRRT*.
            - \ref CT_MAX_PLANNING_ITERATIONS "MAX_PLANNING_ITERATIONS" Maximum planning iterations.
            .
         .
      - <b>GBF-based planning</b>
        - \ref CT_ATLASGBF_BETA "ATLASGBF_BETA" Penalty in AtlasGBF.
	.
      .
   - <b>Parameter for representation</b> 
      - \ref CT_CUT_X "CUT_X" Cut plane in X.
      - \ref CT_CUT_Y "CUT_Y" Cut plane in Y.
      - \ref CT_CUT_Z "CUT_Z" Cut plane in Z.
   - <b>Parameter for tensegrity problems</b>  
      - \ref CT_PRETENSION "PRETENSION" Pretension of the tensegrity structure.
      .
   - <b>Parameter for molecular problems</b> 
      - \ref CT_VDW_RATIO "VDW_RATIO" Ration on Van der Waals radious used to detect collisions between atoms.
      .
   .   

   Note that internal names for parameters are preceded  by CT_, so, for instance EPSILON is called CT_EPSILON in the code


   \sa Tparameters, parameters.c, readparameters.l readparameters.y.
*/

/** 
    \brief One of the possible values of the \ref CT_REPRESENTATION "REPRESENTATION" parameter.

    In this representation we use 6 parameters to represent two 
    vectors of the rotation matrices for each link. The third
    vector is the cross product of the two represented vectors.

    \sa REP_FLINKS, REP_QLINKS, REP_JOINTS
*/
#define REP_LINKS       0

/** 
    \brief One of the possible values of the \ref CT_REPRESENTATION "REPRESENTATION" parameter.

    In this representation we use 9 parameters to represent the 
    full rotation matrices for each link.
   
    \sa  REP_LINKS, REP_QLINKS, REP_JOINT
*/
#define REP_FLINKS      1


/** 
    \brief One of the possible values of the \ref CT_REPRESENTATION "REPRESENTATION" parameter.

    In this representation we use 4 parameters to represent 
    rotation matrices for each link relying on quaternions.
   
    \sa REP_LINKS, REP_FLINKS, REP_JOINTS
*/
#define REP_QLINKS      2

/** 
    \brief One of the possible values of the \ref CT_REPRESENTATION "REPRESENTATION" parameter.

    In this representation we do not use any variable for links
    but only for joints. This is similar to the classical DH
    non redundant formulation, but includes some auxliary/dummy
    variables for some kind of joints (in_patch).
   
    \sa REP_LINKS, REP_FLINKS, REP_QLINKS
*/
#define REP_JOINTS      3

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.

   \sa VCOLLIDE, PQP, FCL, CFLC, BULLET, C_BULLET, RIGIDCLL, NOCD
*/
#define SOLID 0

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.

   \sa SOLID, PQP, FCL, CFLC, BULLET, C_BULLET, RIGIDCLL, NOCD
*/
#define VCOLLIDE 1

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, FCL, C_FCL, BULLET, C_BULLET, RIGIDCLL, NOCD
*/
#define PQP 2

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, C_FCL, BULLET, C_BULLET, RIGIDCLL, NOCD
*/
#define FCL 3

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, FCL, BULLET, C_BULLET, RIGIDCLL, NOCD
*/
#define C_FCL 4

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, PQP, FCL, C_FCL, C_BULLET, RIGIDCLL NOCD
*/
#define BULLET 5

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, PQP, FCL, C_FCL, BULLET, RIGIDCLL NOCD
*/
#define C_BULLET 6

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, PQP, FCL, C_FCL, BULLET, C_BULLET, NOCD
*/
#define RIGIDCLL 7

/** 
  \brief One of the possible collison detection engines.

   One of the possible collison detection engines.
   
   \sa SOLID, VCOLLIDE, PQP, FCL, C_FCL, BULLET, C_BULLET, RIGIDCLL
*/
#define NOCD 8

/** 
    \brief  One of the possible sampling modes.

    In this sampling mode, points are generated randomly in the
    ambient space box.
    
    \sa KDTREE_SAMPLING, TANGENT_SAMPLING
*/
#define AMBIENT_SAMPLING 0

/** 
    \brief  One of the possible sampling modes.

    In this sampling mode, points are generated randomly in the
    boxes bounding the tree nodes. These boxes are defined
    in the kd-tree.

    \sa AMBIENT_SAMPLING, TANGENT_SAMPLING
*/
#define KDTREE_SAMPLING 1

/** 
    \brief  One of the possible sampling modes.

    In this sampling mode, points are generated randomly in the
    tangent spaces stored in the charts. This is only
    used in AtlasRRT. If the sampling mode is set to this value
    normal RRTs use AMBIENT_SAMPLING

    \sa AMBIENT_SAMPLING, KDTREE_SAMPLING
*/
#define TANGENT_SAMPLING 2


/************************************************************************************/
/** \brief Default file of parameters 

    Default file of parameters. This is the file of parameters read in the first
    place, before reading the file specific for the problem at hand.
    In this way, the problem specific parameter need only to include values
    for the parameters whose value is not to be the default value.
*/
#define DEFAULT_PARAMS "share/CuikSuite/default.param"
/************************************************************************************/

/** 
   \brief Numerical tolerance.
    
   Threshold to turn any number into 0.
   For position analysis problmes (relying on a linear program) it should be larger than 1e-6, 
   the threshold hard-coded in many simplex packages. For path/motion planning we typically
   use values of 1e-8 or even 1e-10, depending on the accuracy of the given initial and
   final configurations/states.
*/
#define CT_EPSILON                   0

/** 
   \brief Representation.

    The mechanisms configurations can be represented in different ways:
      - LINKS: A partial rotation matrix per link (2 vectors, 6 parameters,
               the third vector is cross product of the first two).
      - FLINKS: A full rotation matrix per link (3 vectors, 9 parametres).
      - QLINKS: A rotation matrix per link using quaternions (4 parameters).
                This is experimental (not fully tested).
      - JOINTS: Directly use the DOF of the mechanism. This is equivalent to the standard non-redundant 
		<a href="http://en.wikipedia.org/wiki/Denavit-Hartenberg_parameters">DH</a> 
		representation. In this case parameters are
                associated with joints and not with links.
      .

    When using JOINTS representation configurations/states are read form a <b>.joints</b> file. Otherwise
    they are read form a <b>.links</b> file.

    Note that if you change this parameter solutions files previosly computed
    can become invalid. This can be a source of confusion so care must be
    taken to create/manipulate solutions using the same value for this parameter.
*/
#define CT_REPRESENTATION            1

/** 
   \brief Reduction threshold.
    
   If boxes in a prune process reduce more that \e RHO, the reduction process is repeated.
*/
#define CT_RHO                       2

/** 
   \brief Box size threshold.
    
   A prune process that reduces the size of a box is stoppes when the box reaches this size.
   This is typically the size of the boxes bounding isolated solutions.
*/
#define CT_SMALL_SIGMA               3

/** 
   \brief Box size threshold.
    
   If at the beginning of a prune process the box is smaller than this size, it is already considered
   a solution. 
   Typically this is the size of the boxes bounding continuous solution sets.
*/
#define CT_SIGMA                     4

/** 
   \brief Chart error in atlas.

   Maximum error between the manifold and the tangent space for each chart.
*/
#define CT_E                         5

/** 
   \brief Chart error in atlas.

   Maximum oriented curvature error of the local maps for each chart.
*/
#define CT_CE                        6

/** 
   \brief Ball radius in atlas.

   Maximum radius of the local maps when building atlas (or part of atlas).
*/
#define CT_R                         7

/** 
   \brief Sampling ball in atlas.

   Radius of the ball used to generate samples. This must be larger than \ref CT_R.

   \sa InitEmptySPolytope
*/
#define CT_SR                         8

/** 
   \brief Size of the steps in the path connecting two configurations.

   Step size for the paths connecting two given configurations. In between
   two steps no collision detetion is performed so, indirectly, this parameter
   defines the maximum penetrability between any two bodies in the problem.
*/
#define CT_DELTA                      9

/** 
   \brief Cost penalty factor for atlasGBF.

   Cost penalty factor for \ref cuikatlasGBF.c "cuikatlasGBF". The \ref cuikatlasGBF.c "cuikatlasGBF" was
   our first planning algorihtm using higher-dimensional continuation but we hardly use it nowadays since
   the \ref cuikatlasrrt.c "cuikatlasrrt" typically performs better (spacially in high dimensions).
   
   See this <a href="http://www.iri.upc.edu/people/porta/Docs/ijrr12.pdf">paper</a> for more details.
*/
#define CT_ATLASGBF_BETA             10

/** 
   \brief Period between two consecutive savings of the state.
    
   Period between two consecutive savings of the internal \b cuik state.
   If the computation is interrupted, the solving process is re-started from the last
   saved state.
*/
#define CT_STATE_PERIOD             11

/** 
   \brief Number of solution boxes to deliver.
    
   Number of output solutions boxes we need.
   Use 0 to obtain all possible solution boxes for the problem at hand.
*/
#define CT_N_SOLUTIONS              12

/** 
   \brief Maximum number of iterations in the Newton-Raphson function.
    
   Maximum number iterations in the Newton-Raphson function. This is used, for
   instance, to implement the tangent-to-manifold map used in the chart
   implementation.
*/
#define CT_MAX_NEWTON_ITERATIONS    13

/** 
   \brief Dimensionality of the solution space for the mechanism at hand.
    
   Dimensionality of the solution space for the mechanism at hand.

   If set to 0, the system tries to guess this value automatically assuming that
   the first point in the joints/links file is regular.
*/
#define CT_N_DOF                    14

/** 
   \brief Contant part of the search radius for nearest neightours in RRT*.
    
    Contant part of the search radius for nearest neightours in RRT*.
    See this <a href="http://www.iri.upc.edu/people/porta/Docs/ras13.pdf">paper</a> for details.
*/
#define CT_GAMMA                    15


/** 
   \brief Dummification level.
    
   Dummification level.
   - 0 keep in original form
   - 1 keep lineal equations, circles and spheres (the rest are transformed into lineal, parabola and saddle equations).
   - 2 keep lineal equations (the rest are transformed into lineal, parabolas, and saddle equations).
   - 3 keep lineal equations, circles, spheres and all inequalities (the rest are transformed into linear, parabola and saddle equations).
   - 4 keep lineal equations and all inequalities (the rest are transformed into linear, parabola and saddle equations).
   .
*/
#define CT_DUMMIFY                  16
/** 
   \brief Split type.
   
   Select the criterion used to determine the split dimension for a box in a branch-and-prune process:
     - 0: if we use a size-based criterion (split along the largest side of the box)
     - 1: if we use an error-basedcriterion (split along the variable that introduces a larger linearization error).
     - 2: if we select the split dimension at random.
     .
*/
#define CT_SPLIT_TYPE               17
/** 
   \brief  Trade off between speed and numerical stability when using the simplex

   Trade off between speed and numerical stability when using the simplex
   Possible values are 
    - 0 : no special numerical tricks are used
    - 1 : 0 + The output of the simplex are "corrected" to get safe bounds for the new ranges 
    - 2 : 1 + The simplex tableau is reseted before the  min/max for each range
    - 3 : 2 + The simlpex tableau is reseted before all optimization.
    .
*/
#define CT_SAFE_SIMPLEX             18

/** 
   \brief Simplification level.
    
   Simplification level:
    - 0 No simplification is applied.
    - 1 Only equations of the form \f$x=a\f$ or \f$x^2=0\f$ are considered 
      (with \e x a variable and \e a a constant).
    - 2 Equations of the form \f$x + a y=b\f$ are also considered
      (with \e x and \e y variables and \e a and \e b constants).
    - 3 Equations of the form \f$a x + b y=c\f$ are also considered
      (with \e x and \e y variables and \e a and \e b constants).
    .
   
   The less the simplification the more the numerical stability, but the slower the
   solution process.

   A simplification level 2 should be Ok except for extremely ill conditioned cases.
*/
#define CT_SIMPLIFICATION_LEVEL     19

/** 
   \brief  Threshold to switch from linear relaxations to Taylor models
           for quadratic equations.

    Threshold to switch from a specific linearization (one based on
    linear relaxations) to a general one (based on Taylor models)
    for purely quadratic equations: parabolas, circles, and spheres.

*/
#define CT_LR2TM_Q                  20
/** 
   \brief  Threshold to switch from linear relaxations to Taylor models
           for saddle equations. 

   Threshold to switch from a specific linearization (one based on
   linear relaxations) to a general one (based on Taylor models)
   for saddle equations.
*/
#define CT_LR2TM_S                  21

/** 
    \brief Ratio over over the Van der Waals radius.

    Reduction ratio [0,1] over the Van der Waals radius used to detect
    steric clashes. The reduction is used to ensure that only
    very high energy conformations are discarded by considering
    the collisions between atoms (as if atoms where solid spheres).
*/
#define CT_VDW_RATIO                22

/** 
   \brief Limit of domain of the X dimension of 3d plots.

   Limit of domain of the X dimension of 3d plots when the variables have
   circular ranges. The default limits are [-pi,pi] and this sometimes produce
   cutted plots. Using these constants the range of the plot can be adjusted
   at will to avoid those cuts.   

   This is basically used when plotting atlas the DOF \ref CT_REPRESENTATION.
*/
#define CT_CUT_X                    23

/** 
   \brief Limit of domain of the Y dimension of 3d plots.

   Limit of domain of the Y dimension of 3d plots when the variables have
   circular ranges. The default limits are [-pi,pi] and this sometimes produce
   cutted plots. Using these constants the range of the plot can be adjusted
   at will to avoid those cuts.   

   This is basically used when plotting atlas the DOF \ref CT_REPRESENTATION.
*/
#define CT_CUT_Y                    24

/** 
   \brief Limit of domain of the Z dimension of 3d plots.

   Limit of domain of the Z dimension of 3d plots when the variables have
   circular ranges. The default limits are [-pi,pi] and this sometimes produce
   cutted plots. Using these constants the range of the plot can be adjusted
   at will to avoid those cuts.   

   This is basically used when plotting atlas the DOF \ref CT_REPRESENTATION.
*/
#define CT_CUT_Z                    25

/** 
   \brief Scale factor of the temperature parameter for Transition-based RRT

    Scale factor of the temperature parameter for Transition-based RRT.

    This is part of our implementation of the Transition-based RRT that we used in
    this <a href="http://www.iri.upc.edu/people/porta/Docs/jcc13.pdf">paper</a>.
    For more details on the Transition-based RRT see this  <a href="https://ieeexplore.ieee.org/document/4650993">paper</a>.
*/
#define CT_COEF_TEMP                26

/** 
   \brief Number of successive trnasition test failues requiered before 
          increasing the temperature 

   Number of successive trnasition test failues requiered before 
   increasing the temperature.

   This is part of our implementation of the Transition-based RRT that we used in
   this <a href="http://www.iri.upc.edu/people/porta/Docs/jcc13.pdf</a>.
   For more details on the Transition-based RRT see this  <a href="https://ieeexplore.ieee.org/document/4650993">paper</a>.
*/
#define CT_NFAIL_MAX                27

/** 
   \brief TRUE (or 1) if bifurcation must be detected.

   To activate/deactivate the search for bifurcations during the atlas
   construction.

   See this <a href="https://www.iri.upc.edu/publications/show/1301">report</a> for more details
   about branch switching.
*/
#define CT_DETECT_BIFURCATIONS      28

/** 
   \brief Maximum time for path planning.

   Maximum time in seconds for the path planning algorihtms (cuikatlasGBF, cuikaltasrrt, cuikccrrt,....).
*/
#define CT_MAX_PLANNING_TIME        29

/** 
   \brief Maximum iterations for path planning.

   Maximum iterations for the path planning algorihtms (currently only used in AtlasRRT* and RRT* since
   the rest of algorithms are limited in time only).
*/
#define CT_MAX_PLANNING_ITERATIONS  30

/** 
   \brief Maximum number of charts in an atlas.

   Maximum number of charts in at atlas.
*/
#define CT_MAX_CHARTS               31

/** 
   \brief Maximum number of nodes in an RRT.

   Maximum number of nodes in an RRT.
*/
#define CT_MAX_NODES_RRT            32

/** 
   \brief Bi-directional RRT.

   TRUE if the RRT search is bi-directional.
   \ref cuikccrrt.c "cuikccrrt" is one-directional despite the value of this parameter.<br>
   \ref cuikcbirrt.c "cuikcbirrt" is bi-directional despite the value of this parameter.<br>
   The rest of rrt-like planners (\ref cuikatlasrrt.c "cuikatlasrrt" or \ref cuikatlasrrtstar.c "cuikatalsrrtstar") properly
   honor this parameter.
*/
#define CT_BI_RRT                   33

/** 
   \brief Graph RRT.

   TRUE if the RRT has to store all the neighbours for each
   new node. This is only used in \ref cuikatlasrrtstar.c "cuikatlasrrtstar"
   to speed up the propagation of improvements of the path to the
   nodes.

   See this <a href="http://www.iri.upc.edu/people/porta/Docs/ras13.pdf">paper</a> for more details.
*/
#define CT_RRT_GRAPH                34

/** 
   \brief Dynamic domain.

   TRUE if the RRT-like planners have to use dynamic domains.

   See this <a href="https://ieeexplore.ieee.org/document/1545607">paper</a>
   for more details on this technique.
*/
#define CT_DYNAMIC_DOMAIN           35

/** 
   \brief Collision detection engine.

   Collision detection engine. Right now four options
   are available: \ref SOLID, \ref VCOLLIDE, \ref PQP, \ref FCL, \ref C_FCL, \ref BULLET, \ref RIGIDCLL, NONE.

*/
#define CT_CD_ENGINE                36

/** 
   \brief Sampling mode.

   Parameter used to select the mode to generate
   samples to expand the (Atlas)RRT.
   Three modes are available: 

     - \ref TANGENT_SAMPLING is the default mode for Atlas RRT
       and uses the charts to sample.

     - \ref AMBIENT_SAMPLING is the default mode for RRTs.
       This mode generate samples from the ambient space.

     - \ref KDTREE_SAMPLING is a mode where the samples are generated
       from boxes bounding the nodes in the RRT. This boxes
       are defined by a kd-tree (also used to accelerate the
       searches for neighbour nodes). 
     .

   See this <a href="https://arxiv.org/abs/1407.2544">report</a> for
   more details.
*/
#define CT_SAMPLING                 37

/** 
    \brief Pre-tension.

    Norm of the tension/compression forces in the tensegrity.
    In equilibrium, these forces can be arbitrarily scaled preserving
    the equilibrium. By imposing a norm to the forces this scale
    factor (a short of useless degree of freedom) is cancelled.
    If set to 0, the scale factor is not fixed.
    Note that in general, the equilibrium forces can have more than
    one degree of freedom (the kernel of the equilibrium matrix
    can be larger than one). We only cancel one degree of fredom.
    If there are more, they can be cancelled by fixing some tensions
    or compressions to a constant value.

    See this <a href="">paper</a> for more details.
*/
#define CT_PRETENSION               38

/** 
    \brief Dynamics.

    If larger than 0, if the dynamics must be considered. If so, the
    problems are defined in phase space (position and velocity) 
    where the velocity variables and equations are automatically
    generated.

    Moreover, when de dynamics is considered, the (Atlas)RRT is
    extended integrating the dynamic equation.

    The value (>0) is used to select the integration method:
          -  LOCAL_TRAPEZOID (1): Implicit trapezoidal methods in local coordiantes (Broyden...)
          -  LOCAL_EULER     (2): Euler in local coordinates
          -  LOCAL_RK4       (3): RK4 in local coordinates
          -  EULER           (4): Euler (disregarding the manifold)
          -  RK4             (5): RK4 (disregarding the manifold)
	  .

*/
#define CT_DYNAMICS                 39

/** 
    \brief Integration time.

    When considering dynamics, this fixes the integration time
    for each selected action.
*/
#define CT_INTEGRATION_TIME     40

/** 
    \brief Max velocity.

    The maximum velocity (in absolute value). Only used
    if the maximum velocity can not be taken from the
    world file.
*/
#define CT_DEFAULT_MAX_VELOCITY   41

/** 
    \brief Number of dynamic actions.

    Number of valid actions when performing dynamic
    simulations/planning. Typically, such actions are
    samples in a continuous domain of valid forces/torques
    which lead to valid accelerations.

    If set to 0, an LQR-based method is used to determine the
    action to execute.
*/
#define CT_N_DYNAMIC_ACTIONS    42

/** 
    \brief Goal error in dynamic problems.

    Tolerance when aiming at a goal state (or the
    connection between thress) in a 
    problem with dynamics.

    This is call beta in our papers on kinodynamic planning.
    Not to be confused with \ref CT_ATLASGBF_BETA "ATLASGBF_BETA".
*/
#define CT_DYNAMIC_GOAL_ERROR    43

/** 
    \brief Gravity compensation.

    If set, actions are interpreted as variations over the action
    that compensates the gravity effects.
*/
#define CT_G_COMPENSATION  44

/** 
    \brief Negative Lagrange multipliers.

    If set the Lagrange multipliers should be negative for a state
    to be valid. So far this is only used in cable-driven robots, to
    ensure that cables are in tension since the sign of the
    Lagrange multipliers is related with the sign of the internal
    forces in the mechanisms. See this 
    <a href="http://www.iri.upc.edu/people/porta/Docs/cc17.pdf"paper</a> for more details.
*/
#define CT_NEG_LM         45

/** 
   \brief Gravity axis.

   Select the gravity axis: 0 for no gravity, 1 for X, 2 for Y, 3 for Z,
   4 for -X, 5 for -Y and 6 for Z
*/
#define CT_G_AXIS     46

/** 
   \brief Balance between time and action effort.

   Balance between the relevance of time and the relevance of the action
   effort when computing the optimal action via LQR.   
*/
#define CT_TAU     47

/** 
   \brief Planning time for LQR.

   This parameter determines the planning time when using LQR to determine the policy.
   It is typically related to \ref CT_INTEGRATION_TIME
*/
#define CT_LQR_PLANNING_TIME   48

/** 
   \brief  Total number of parameters.

   Total number of parameters.
*/
#define NPARAMETERS (CT_LQR_PLANNING_TIME+1)

/** 
   \brief Information about a single parameter.
   
   Information about a single parameter (name and value).
*/
typedef struct
 {
   char *name;            /**< Name of the parameter. */
   double value;          /**< Value of the parameter. */
   unsigned int timesSet; /**< Times this parameter has been set. */
} Tparameter;

/** 
   \struct Tparameters 
   \brief A table of parameters.

   A set of parameters. Each parameter is identified with a constant
   defined in file parameters.h (check the source code).

   \sa parameters.h, parameters.c
*/

/** 
   \brief A table of parameters.

   A set of parameters. Each parameter is identified with a constant
   defined in file parameters.h.

   This is basically a set of constants, but only a small, predefined
   set of constants are allowed. This is why we do not re-use
   \ref Tconstants but provide a different implementation.
   
   \sa parameters.h, parameters.c
*/
typedef Tparameter Tparameters[NPARAMETERS];

/** 
   \brief Constructor.

   Defines an empty set of parameters.

   \param p The set to be initialized.
*/
void InitParameters(Tparameters *p);

/** 
   \brief Constructor from a file.

   Defines an set of parameters from a file. It first read the default
   set of parameters and then the given set of parameters.

   \param file Name of the file with the set of parameters particular
               for the problem at hand.
   \param p Set of parameters to define.

   \sa ReadParameters, defines.h
*/
void InitParametersFromFile(char *file,Tparameters *p);

/** 
   \brief Gets the value for a particular parameter.
   
   Gets the value for a particular parameter.

   \param n Number of parameter.
   \param p Set of parameters.

   \return The value of the parameter. If there is no parameter with the
           given number this functions triggers an error.
*/
double GetParameter(unsigned int n,Tparameters *p);

/** 
  \brief Returns the parameter identifier given the paramete name.

  Determines the parameter identifier for a given parameter name.

  \param name The paremeter name.
  \param p The set of parameteres.

  \return The paremeter identifier or NO_UINT if there is not a parameter with the given name.
*/
unsigned int GetParameterID(char *name,Tparameters *p);

/** 
  \brief Checks if a parameter is already defined.

  Determines is a parameter is already defined. The default initialization (the one from
  the default set of parameters) is not taken into account. Only explicit initializations
  from the users are considered.
  
  Only parameters alrady defined can be used in the definition of other parameters.

  \param n The identifier of the parameter.
  \param p The parameter set.
  
  \return TRUE if the parameter is already defined.
*/
boolean ParameterSet(unsigned int n,Tparameters *p);

/** 
   \brief Sets the name and value for a particular parameter.
   
   Sets the name and value for a particular parameter.

   \param n Number of parameter.
   \param name The name for the parameter. This is a string that is used
               when printing the parameter.
   \param v The value.
   \param p Set of parameters.
*/
void SetParameter(unsigned int n,char *name,double v,Tparameters *p);

/** 
   \brief Sets the value for a particular parameter.
   
   Sets the value for a particular parameter.

   \param n Number of parameter.
   \param v The new value for the parameter.
   \param p Set of parameters.
*/
void ChangeParameter(unsigned int n,double v,Tparameters *p);

/** 
   \brief Prints a parameter set.
   
   Writes a parameter set to a stream, that can be \e stdout.

   In  principle the output of this function can be used as a parameter file
   (i.e., it can be parsed correctly with \ref InitParametersFromFile).

   \param f The stream
   \param p Set of parameters to print. 
*/
void PrintParameters(FILE *f,Tparameters *p);

/** 
   \brief Destructor.
   
   Deletes a set of parameters and frees the allocated memory.

   \param p Set of parameters to be deleted. 
*/
void DeleteParameters(Tparameters *p);

#endif
