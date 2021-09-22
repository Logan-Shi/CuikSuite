#ifndef DYNAMICSH
#define DYNAMICSH

#include "jacobian.h"
#include "njacobian.h"
#include "hessian.h"
#include "nhessian.h"
#include "algebra.h"
#include "basic_algebra.h"
#include "parameters.h"
#include "chart.h"
#include "rrt.h"
#include "wcs.h"

#include <math.h>
#include <string.h>

/** 
   \file dynamics.h
   \brief Dynamical functions.

   Functions related with dynamics. They are used to implement the
   planning with dynamical constraints.
*/

/** 
   \brief Debug the dynamic procedures.

   Set to 1 to print information about the dynamic procedures.
*/
#define DEBUG_DYNAMICS (_DEBUG>3?_DEBUG-3:0)


/** 
   \brief Print information on the optimal LQR policy computation.

   If set we print information on the optimal LQR policy cost
   as computed for each time. This is an extra debug flag.
*/
#define PRINT_J 0

/** 
    \brief Define a max J.

    If set we define a maximum J in \ref LQRComputePolicy (or \ref LQRComputePolicy_t):
    The optimal cost computed in this function is only accepted if it is below
    maxJ.

    This is experimental and for normal operation should be 0.
 */
#define MAX_J 0

/** 
   \brief Debug the HandC procedure.

   Set to 1 to print information about the HandC execution.
   We print detailed information to facilitate the comparison with the Matlab code. 
*/
#define DEBUG_HandC (_DEBUG>4?1:0)

/** 
    \brief Thread to debug.

    When debugging HandC we only print information about one of the threads
    running in parallel
*/
#define HandC_Thread 1

/** 
    \brief Compute the position Jacobian/Hessian in HandC

    If set, the position Function/Jacobian/Hessian used to find out the acceleration is
    computed in HandC, re-using other computations. 
    Otherwise it is computed from the system Jacobian.
    Note that we do not compute exactly the same Jacobian matrix
    but matrices that expand the same linear sub-space.

    Typically the HandC computations are significantly faster.
 */
#define HandC_FJH 1

/** 
    \brief Debug the computation of the Jacobian/Hessian via HandC.

    If set we print the Jacobian/Hessian computed in HandC and the
    Jacobian evaluated from the equations. Note that, if set, 
    the HandC Jacobian is computed but not used (the one
    from the equations is stored in the corresponding matrices
    overwritting the HandC computations).

    NOTE: To get exactly the same jacobian in both cases you should
    deactivate the SIMPLIFY_TS flag in trans_seq.h
    
    Used only for debug.
*/
#define DEBUG_HandC_FJH 0

/** 
    \brief Determines the loop equations defined in HandC.

    If set, the equation generated in HandC for each loop
    is A*B^-1, where A and B are alternative transforms
    to the loop closure link (transfroms computed from 
    alternative paths from the root to the link).

    If not set, the loop equations are computed as A-B.

    Used only for experimentation. Typically this should be 1.
*/
#define HandC_EQ_INV 1

/** 
    \brief Where to start the Broyden iteration.

    If set the Broyden iteration is started froma point in the manifold: we use
    Euler in tangent space and then we project to the manifold. Otherwise
    we directly use Euler in ambient space and the initial point is not
    on the manifold.

    Used only for experimentation. Typicaly this should be 0.
*/
#define START_BROYDEN_ON_MANIFOLD 0

/** 
   \brief Use the product of homogenous transforms and spatial algebra vectors.

   If set, the product of homogenous transforms and spatial algebra vectors is
   performed without explicitly defining the spatial algebra matrix
   corresponding to the transform.
*/
#define USE_HTxSAV 1 

/** 
   \brief Explicitly build the CRM matrix.

   If set, we explicitly build the CRM 6x6 matrix. Otherwise, we direclty
   use the \ref CRMxSAV method (which is supposed to be faster).
*/
#define EXPLICIT_CRM 1

/** 
   \brief Explicitly build the CRF matrix.

   If set, we explicitly build the CRF 6x6 matrix. Otherwise, we direclty
   use the \ref CRFxSAM method (which is supposed to be faster, 
   but it is not).
*/
#define EXPLICIT_CRF 1

/** 
   \brief Define Xup using an homogeneous transform.

   If set, Xup is also defined as an homogeneous transform. In this way,
   we can choose whether to use the homogenous transform or the spatial
   algebre matrix, depending on the case.
*/
#define USE_XUPTR  0

/** 
   \brief Cut at links.

   If set, the kinematic tree used in HandC cuts the loops in the middle of some
   links and not in a joint. In this way all joints apperar in the kinematic
   tree.
*/
#define CUT_AT_LINK 1

/** 
   \brief Integration method in \ref LQRComputePolicy

   We can select the integration methods to be used in \ref LQRComputePolicy.
   We can chose Euler (1), fast but innacurate in the long term or
   Runge-Kutta 4 (0).
*/
#define EULER_LQR_COMPUTE_POLICY 0

#if (COMPUTE_LQRPOLICY_IN_T)
  /** 
     \brief Select the pocedure to compute the policy

     Use the time-based (closed-form expressions) procedure.
  */
  #define LQR_COMPUTE_POLICY LQRComputePolicy_t
#else
  /** 
     \brief Select the pocedure to compute the policy

     Use the recursive procedure based on the Runge-Kutta rule.
  */
  #define LQR_COMPUTE_POLICY LQRComputePolicy
#endif


/** 
   \brief LQR action saturation.

   If set, actions computed with an LQR policy are saturated to the maximum
   value set by the user (in the world file).
   If set to 0, actions are not saturated.

   This should be 1 and only set to 0 for debugging purposes.

   If set to zero, we assume that we are performing an LQR steering test and
   we deactivate many options.
*/
#define SATURATE_ACTIONS 1

/** 
  \brief Select actions randomly.

  If set, the actions are selected randomly, otherwise bang-bang control is used.
*/
#define RANDOM_DYNAMIC_ACTION 1

/** 
   \brief Use time to go metric.

   When defining an RRT in a problem with dynamics, we can use time
   to go metric instead than the Euclidean metric.

   Only a first order approximation of the time to go is computed
   (see \ref Time2Go) and the computation is slow, but it is
   supposed to give more effective RRT extensions.

   This is only active in dynamical systems and when \ref NN_IN_CHART
   is active.

   In particular this flag determines if Time2Go metric is to be used
   when looking for nearest neighbours when extending the RRT.
*/
#define T2G_METRIC_NN_EXTEND 0

/** 
   \brief Use time to go metric.

   The same as \ref T2G_METRIC_NN_EXTEND but this determines
   if  Time2Go metric is to be used when looking for nearest
   neighbours when trying to connect trees.
*/
#define T2G_METRIC_NN_CONNECT 0

/** 
   \brief Use time to go metric.

   If \ref T2G_METRIC_NN_EXTEND is active, we can additionally
   use the Time2Go metric inside the extension (to determine
   reachability sets and alike).
*/
#define T2G_METRIC_INSIDE_EXTEND ((T2G_METRIC_NN_EXTEND)&&(0))

/** 
   \brief Use time to go metric.

   If \ref T2G_METRIC_NN_CONNECT is active, we can additionally
   use the Time2Go metric inside the connection (to determine
   reachability sets and alike).
*/
#define T2G_METRIC_INSIDE_CONNECT ((T2G_METRIC_NN_CONNECT)&&(0))

/** 
   \brief Use time to go metric.

   TRUE if any of the time2go flatgs is active.
   Defined for convenience.
*/
#define T2G_METRIC ((T2G_METRIC_NN_EXTEND)||(T2G_METRIC_NN_CONNECT))


/** 
   \brief One random action.

   In some modes (specially when using T2G_METRIC) it makes
   sense to execute just one action (generated at random or
   computed as you which) instead of simulating several
   candidate actions and selecting the best one.

   In paticular this flag is used for the extension of
   the RRT (when aiming at a random sample).

   This is typically active only when \ref T2G_METRIC_NN_EXTEND
   is also active.
*/
#define DYNAMICS_ONE_ACTION_EXTEND 0

/** 
   \brief One random action.

   The same as \ref DYNAMICS_ONE_ACTION_EXTEND but used
   when trying to connect the two trees.

   This is typically active only when \ref T2G_METRIC_NN_CONNECT
   is also active.
*/
#define DYNAMICS_ONE_ACTION_CONNECT 0

/** 
   \brief Variables used in the dynamic simulation.

   Variables used in the dynamic simulation assembled in a
   single struct for convenience.
*/
typedef struct {
  TAtlasBase *w;        /**< The system of equations. */

  boolean parallel;     /**< TRUE if we can to execute parts of the dynamics in parallel.
			     Right now this is only used to compute finite differences
			     and only in OPENMP is present. */
  
  unsigned int dof;     /**< Dimension of the position manifold.
		             The state space manifold has two times this dimension. */

  double *action;       /**< Space for actions. */
  unsigned int da;      /**< Dimension of the action space. */

  TJacobian *sJ;        /**< The full symbolic Jacobian */
  
  unsigned int nv;      /**< Number of variables in the problem. */
  unsigned int ne;      /**< Number of equations in the problem. */

  Tbox domain;          /**< Domain of the variables. */
  unsigned int *tp;     /**< Topology of the space. */
  
  unsigned int npv;     /**< Number of position variables in the problem. */
  unsigned int npe;     /**< Number of position equations in the problem. */
  unsigned int nie;     /**< Number of independent equations in the problem. */
  unsigned int nipe;    /**< Number of independent position equations in the problem. */

  unsigned int noe;     /**< Number of other (i.e., non position/velocity) equations. */
  unsigned int nov;     /**< Number of other (i.e., non position/velocity) variables. */

  double *pos;          /**< Space to store the position. */
  double *vel;          /**< Space to store the velocity. */
  
  boolean *pvVars;      /**< Position/velocity variables. This is used to account for 
			     dynamic vs non-dynamic variables and alike. */
  
  boolean *pvEqs;       /**< Position/velocity equations. This is used to account for 
			     dynamic vs non-dynamic equations and alike. */
  
  boolean *pVars;       /**< Identify the position variables. */
  boolean *pEqs;        /**< Identify the position equations. */
  boolean *vEqs;        /**< Identify the velocity equations. */
  boolean *oEqs;        /**< Identifies non-position/velocity equations (i.e., other equations). */
  boolean *selEqs;      /**< Used to combine flags of arrays over equations. */
  
  unsigned int *ndxPE;  /**< Global index of the i-th position equation: npe */
  unsigned int *ndxVE;  /**< Global index of the i-th velocity equation: npe */
  unsigned int *ndxOE;  /**< Global index of the i-th non position/velocity equation: noe */
  
  unsigned int *ndxPV;  /**< Global index of the i-th position variable: npv */
  unsigned int *ndxVV;  /**< Global index of the i-th velocity varialbe: npv */
  unsigned int *ndxOV;  /**< Global index of the i-th non position/velocity variable: nov */
  
  TJacobian sJp;        /**< The symbolic position Jacobian. */
  TJacobian sJop;       /**< The symbolic non position/velocity Jacobian. This is actually the
			     derivative of the non-dynamic related equations (non position nor velocity) 
			     with respect to the position variables. This block of the full 
			     Jacobian times the velocity vector gives the derivative of the
			     non-dynamic equations w.r.t. time (simple chain rule). */
  TJacobian sJoo;       /**< The derivative of the non-dynamic equations with respect to the
			     non-dynamic variables. */
  TNJacobian *nJp;      /**< The numerical position Jacobian. Used instead of the symbolic one
			     in some problems. */

  THessian sHp;         /**< The symbolic position Hessian. */
  TNHessian *nHp;       /**< The numeric position Hessian. In some (common) problems
			     it is more efficient to evaluate the Hessian numerically
			     instead than symbolically. Numerically, we save many
			     operations which are repeated in the symbolic Hessian. */

  double *Jp;           /**< Space for the evaluation of sJp: npe x npv */
  double *Jop;          /**< Space for the evaluation of sJop: noe x npv */
  double *Joo;          /**< Space for the evaluation of sJoo: noe x nov */
  TLinearSystem Jot;    /**< Linear system used to compute the temporal derivative of the non-dynamic
			     equations. This system is Joo * D = Jop, where 'D' is the temporal
			     derivative. Size of D is nov x npv */
  double *o;            /**< Space for the evalutation of the matrix vector product 'D' x vel: noe.  */
   
  double *J;            /**< Space to evaluate the Jacobian: ne x nv */
  double *cJ;           /**< Copy of the transposed position Jacobian. */
  
  boolean *bJ;          /**< Independent equations: ne */
  boolean *bJp;         /**< Independent position equations: npe */
  
  double **Hp;          /**< Space to evaluate the Hessian: npe x npv x npv */
  double *Hpv;          /**< Space to evaluate the Hessian * velocity vector: npe x npv */

  double *Mm;           /**< Space to evaluate the mass matrix: npv x npv */
  double *Qa;           /**< Direct acces to the space for the forces: npv */
  double *gamma;        /**< Direct acces to the space for the Hessian * v * v: npe */

  double lsSize;        /**< Size of the linear system A: npv+npe */
  TLinearSystem A;      /**< The linear system giving the acceleration (and the Lagrange multipliers): (npv+npe) x (npv+npe) */
  double *mA;           /**< Direct access to the matrix in A. */
  double *rhsA;         /**< Direct access to the rhs in A. This is (Qa,gamma) */
  double *solA;         /**< Direct access to the solution in A. */

  double *lambda;       /**< Direct access to the Lagrange multipliers inside the solution of the linear system: npe */
  double *qdd;          /**< Direct access to the acceleration inside the solution of the linear system: npv */
  double *g;            /**< Tangent vector including both the velocity and the acceleration.
		             Assembled together just for convinence: nv */
  double *gy;           /**< Acceleration expressed in local coordinates: 2*dof */
  
  double *k1;           /**< Acceleration computed in the RK4 method: nv 
			     Re-used to compute the same acceleration in tangent space: 2*dof */
  double *k2;           /**< Acceleration computed in the RK4 method: nv
			     Re-used to compute the same acceleration in tangent space: 2*dof */
  double *k3;           /**< Acceleration computed in the RK4 method: nv
			     Re-used to compute the same acceleration in tangent space: 2*dof */
  
  double *xa;           /**< Auxiliary variable to compute the error of the implicit trapezoid rule: nv
                             Also used as temporary state in the Euler and RK4 integration rules. */
  double *y;            /**< Auxiliary variable to compute the error of the implicit trapezoid rule
			     Also used in the Euler and RK4 in local coordinates: 2*dof */
  double *gn;           /**< Acceleration at the point where we start the Broyden iteration: nv */
  TBroyden B;           /**< Broyden structure used to compute next state. */
  double *mB;           /**< Direct access to the Jacobian matrix in Broyden's method */
  double *fe;           /**< Direct access to the Broyden's buffer where to store the function error: nv*/
  double *pe;           /**< Direct access to the Broyden's buffer where to store the projection error: 2*ds->dof */

  double lsSize_ID;     /**< Size of the linear system A_ID: npv */
  TLinearSystem A_ID;   /**< The linear system to solve the inverse dynamics: (npv) x (npv) */
  double *mA_ID;        /**< Direct access to the matrix in A_ID. */
  double *rhsA_ID;      /**< Direct access to the rhs in A_ID. This is (u) */
  double *solA_ID;      /**< Direct access to the solution in A_ID. */
  double *P;            /**< Permutation matrix of action P. */

  unsigned int *a2j;    /**< Mapping from action to joints (identifies actuated/controlled joints): da
			     We assume that the actuated joints are the ones with limited effort. */
  unsigned int *a2x;    /**< Mapping from action to state variables (a joint can have more than one var): da
			     We assume that the actuated joints are the ones with limited effort. */

  unsigned int nl;      /**< Number of links. */
  Tlink **l;            /**< Direct access to the links. */
  unsigned int nj;      /**< Number of joints. */
  Tjoint **j;           /**< Direct access to the joints. */
  double *effort;       /**< Max force/torque for each joint. */

  #if (MAX_J)
    double maxJ;        /**< The optimal cost, computed in \ref LQRComputePolicy (or \ref LQRComputePolicy_t)
  			     must be below this value. */
  #endif
  double *iR;           /**< Inverse of the matrix giving the cost of each action. This is used
			     in the context of the steering method implementing a linear quadratic
			     regulator. It must be stored here because here we have the relation
			     between actions and joints, often used to initialize this matrix. */

  double lsSize_LQR;    /**< Size of the linear system A_LQR: 2*dof */
  TLinearSystem A_LQR;  /**< The linear system to solve the inverse dynamics: (2dof) x (2dof) */
  double *mA_LQR;       /**< Direct access to the matrix in A_LQR. This is G */
  double *rhsA_LQR;     /**< Direct access to the rhs in A_LQR. This is d=(x(f)-r(t)) */
  double *solA_LQR;     /**< Direct access to the solution in A_LQR. This is G^-1*d */

  double *Gd;           /**< Vector G^(-1)d used both in LQRComputePolicying and LQRPolicy */
  double topt;          /**< Optimal time used both in LQRComputePolicying and LQRPolicy */
  double *mAt;          /**< At matrix used in LQRPolicy */
  double *iRBt;         /**< Product of matrices R^-1 and B^t, where R is
                             the regulation costs. Matrix k/2 x k */

  double *eA_LQR;       /**< Space for the exponential of A. */
  double *d0_LQR;       /**< Temporary space for LQR computation */
  
  double *x0_LQR;       /**< Temporary space for LQR computation */
  double *x_LQR;        /**< Temporary space for LQR computation */
  double *y_LQR;        /**< Temporary space for LQR computation */
  double *fE_LQR;       /**< Temporary space for LQR computation */

  double *r_LQR;        /**< Temporary space for LQR computation */
  double *dr_LQR;       /**< Temporary space for LQR computation */
  double *rtemp_LQR;    /**< Temporary space for LQR computation */
  double *rnew_LQR;     /**< Temporary space for LQR computation */
  double *d_LQR;        /**< Temporary space for LQR computation */
  double *G_LQR;        /**< Temporary space for LQR computation */
  double *dG_LQR;       /**< Temporary space for LQR computation */
  double *dGtemp_LQR;   /**< Temporary space for LQR computation */
  double *Gtemp_LQR;    /**< Temporary space for LQR computation */
  double *Gnew_LQR;     /**< Temporary space for LQR computation */

  /* Data for the HandC computation. For most of these computations we
     take into account the links as they appear in the kinematic tree.
     lID/oID are the arrays to convert the indices from ordered
     links to link ID. */
  
  unsigned int nlHC;    /**< Number of links inside the HandC procedure. In this procedure we use
			     some virtual links so that all joints appear in the kinematic tree.
			     In the kinematic tree used for generating the loop equations, some
			     of the joints (the loop closure joints) do not apper. */
  
  Tworld *wo;           /**< Pointer to the world definition */

  unsigned int nLoops;  /**< Number of loops in the problem. */
  unsigned int *cJoint; /**< Closure joints. */

  boolean *bJHC;        /**< Basis of the Jacobian when computed in HandC. This is only relevant
			     in mechanisms where not all equations are relevant (e.g., planar
			     mechanisms). Otherwise this is not used.
			     Not to be confused with \e bJ which is the basis of the independent
			     equations (computed form the symbolic Jacobian). 
			     Size: 6*nLoops */
  double *a_grav;       /**< Gravity vector. Note that for convinience we store  -a_grav (it
			     appears with negative sign in the computations). */
  unsigned int *lID;    /**< Link identifier of the i-th link in the kinematic tree. In
			     this tree parent links appear before than their children. */
  unsigned int *oID;    /**< Reverse mapping of oID: For each link it gives its order in
			     the kinematic tree. */
  double **IM;          /**< Rigid body inertia matrix for each link. The indices are in order of appearance
			     in the kinematic tree. */
  unsigned int *pLink;  /**< Parent for each link. The indices are in order of appearance
			     in the kinematic tree, and the index is also given in this order!. */
  unsigned int *jID;    /**< Joint taking to each link from the parent. The indices are in order of appearance
			     in the kinematic tree but the indices are int  the global joint order. */
  signed int *jSgn;     /**< Orientation of the joint.  The indices are in order of appearance
			     in the kinematic tree. */
  unsigned int *j2x;    /**< First configuration variable used for each joint.  The indices are in order of appearance
			     in the kinematic tree. */
  unsigned int *njx;    /**< Number of configuration variables used for each joint.  The indices are in order of appearance
			     in the kinematic tree. */
  double **Xtree;       /**< Transform from joint to joint in the kinematic tree.  The indices are in order of appearance
			     in the kinematic tree. */
  THTransform *iXtreeTr;/**< iXtree stored as an homogeneous transform. */
  THTransform *closeTr; /**< A constant homogeneous transform that closes loops. Loops are represented duplicating links
			     but each one of the copies of the closure link has a different reference frame. We neee the
			     constant transform between these alternative reference frames. */
  double **S;           /**< Instantaneous velocity for each joint. The indices are in order of appearance
			     in the kinematic tree. */
  double *XJ;           /**< Transform of each joint (just considering the joint movement). The indices are in order of appearance
			     in the kinematic tree.  */
  THTransform iXJTr;    /**< iXJ stored as an homogeneous transform. */
  double *vJ;           /**< Scaled velocity of the joint. The indices are in order of appearance
			     in the kinematic tree. */
  #if (USE_XUPTR)
    THTransform XJTr;   /**< XJ in the form of an homogenous transform. */
    THTransform *XtreeTr;/**< Xtree in the form of an homogenous transform. */
    THTransform *XupTr; /**< Accumulated transform from the root to the currnet link. The indices are in order of appearance
			     in the kinematic tree. */
  #endif
  double **Xup;       /**< Accumulated transform from the root to the currnet link. The indices are in order of appearance
			     in the kinematic tree. */
  
  THTransform *iXupTr;  /**< Inverse of Xup stored as a homogeneous transform. */

  #if (!USE_HTxSAV)
    double **iXa;       /**< Inverse of Xa, i.e., the spatial algebra transform from local coordinates of the link
			     to the global frame (Xa as defined
			     by Featherstone is the spatial transform to local coordinates of the link). */
  #endif
  
  THTransform *iXaTr;   /**< iXa stored as an homogeneous transform. Actually we compute iXaTr and at the end, we 
			     put int in the for of a spatial algebre matrix. */
  double **v;           /**< Velocity of each link. The indices are in order of appearance
			     in the kinematic tree. */
  double *vxS;          /**< Matrix to store crm(v)*S for each joint. This is latter used to define Hpv if the Hessian is computed
			     in HandC: 6*nvp */  
  double *feHC;         /**< Space to evaluate the equations. The final result is copied to 'fe': 2*6*nLoops+noe
			     Actually, for spatial problems, feHC directly points to 'fe' and no copy is necessary. */
  double *gammaHC;      /**< Space for \e gamma as calculated in the HandC procedure. The final result is copied in 'gamma': 6*nLoops 
			     Actually, for spatial problems, gammaHC directly points to 'gamma' and no copy is necessary.*/
  double **avp;         /**< Acceleration of each link. The indices are in order of appearance
			     in the kinematic tree. */
  double **fvp;         /**< Forces on each link. The indices are in order of appearance
			     in the kinematic tree. */
  double **fout;        /**< Forces after applying external forces. The indices are in order of appearance
			     in the kinematic tree. */
  double **IC;          /**< Accumulated inertia matrices. The indices are in order of appearance
			     in the kinematic tree. */
  double *fh;           /**< Force on a given link. */
  double *dh;           /**< Space to compute sub-matrices of H. Only used when
			     composite joints (universal, spherical,...) appear in the problem. */
  unsigned int nef;     /**< Number of external forces. */
  boolean damped;       /**< TRUE if any joint is damped. */
  boolean friction;     /**< TRUE if any joint has dry friction. */
  double *wr1;          /**< Wrench of springs on the first body. */
  double *wr2;          /**< Wrench of springs on the first body. */
  double *auxSAV1;      /**< Auxiliary spatial algebra vector. */
  double *auxSAV2;      /**< Auxiliary spatial algebra vector. */
  double *auxSAV3;      /**< Auxiliary spatial algebra vector. */
  double *auxSAM1;      /**< Auxiliary spatial algebra matrix. */
  double *auxSAM2;      /**< Auxiliary spatial algebra matrix. */
  #if (DEBUG_HandC_FJH)
    double *Jp2;        /**< Space for an alternative computation of Jp. */
    double *Hpv2;       /**< Space for an alternative computation of Hpv. */
    double *gamma2;     /**< Space for an alternative computation of gamma. */
    double *fe2;        /**< Space for an alternative computation of fe. */
  #endif
  
} TDynamicSpace;

/** 
   \brief Integration function.

   Numerical integration function. Currently we have implemented the Euler and the RK4 methods.

   See \ref NextDynamicStateEuler or \ref NextDynamicStateRK4 for an explanation of
   the function parameters.
*/

typedef unsigned int Tintegrator(Tparameters *,unsigned int,double*,double,
				 double*,double*,double*,
				 TDynamicSpace*);

/** 
   \brief Initializes the dynamics space.

   Initializes the space to be used when computing the acceleration and
   during the integration.

   \param pr The set of parameters of the problem.
   \param parallel TRUE if we allow part of the dynamic computations to be executed
                   in parallel.
   \param sJ Symbolic Jacobian of the full system.
   \param w The structure holding the equations (position and velocity).
   \param ds The dynamic space to initialize.

   \todo Include the mass matrix and force defining functions as parametres.
         We will do it when the corresponding interface is clear.
*/
void InitDynamicSpace(Tparameters *pr,boolean parallel,TJacobian *sJ,TAtlasBase *w,TDynamicSpace *ds);


/** 
   \brief Computes the derivative of a state.

   Computes the derivative of a state. This includes the velocity, the acceleration
   and the derivative of the non-dynamic equations.

   \param pr The set of parameters.
   \param x The state. This must be in the simplified form (i.e., in the internal
            representation used by Cuik). See \ref WorldGenerateSimplifiedPointFromSystem
	    to convert an input state (those typically stored in solution/trajectory files) 
	    to a simplified form.
   \param u The action.
   \param a The output acceleration.
   \param ds The dynamic space.
   
   \return The size of the output vector (\e a).

   \todo Implement the unsimplification of derivatives. 
*/
unsigned int Getxdot(Tparameters *pr,double *x,double *u,double *a,TDynamicSpace *ds);

/** 
   \brief Returns a pointer to the cost matrix.

   Returns a pointer to the invers of the matrix weighting the cost of each action in the LQR
   used a sterring method.

   \param ds The dynamic space to query.

   \return A pointer to the matrix.
*/
double *GetInverseActionCostMatrix(TDynamicSpace *ds);

/** 
   \brief Linear approximation of the time to go.

   Linear approximation of the time to go from a given state to another one.
   This is implemented with the aim of improving the nearest-neighbour
   metric in RRTs. The information is better than the one given by
   a simple Euclidean metric but it is significantly slower to
   compute and it is only a first order approximation.

   This is inspired in the derivation included in "An RRT-Based Algorithm for
   Testing and Validating Multi-Robot Controllers" by J. Kim, J. M. Esposito,
   and V. Kumar Robotics Science and Systems 2001.

   The main difference is that we have a constraint manifold and, thus, we
   compute the time to go in tangent space. Consequently, we can only compute
   it for samples in the same tangent space (sharing the same local
   parameterization).

   The time to go is computed as
     - \f$ t2g=d/r \f$
     .

   with d the distance between the goal and the current position and r the
   decrease ration of this distance.
   'd' is computed as the Euclidean distance (between parameterizations).
   'r' is more difficult to estimate. Actually an exact value for 'r' is
   as difficult as finding the solution to the two point boundary value
   problem (TPBVP) between the departing and the goal states. In general
   the TPBVP is hard and, thus we only find an approximation to the solution.
   This approximation is based on a linear approximation of the time
   to go evaluated at the departing state

     - \f$ r=-\partial{d}/\partial{t} = - (\partial{d}/\partial{x})^t \partial{x}/\partial{t} \f$
     .

   If 'd' is the Euclidean distance
     -\f$  \partial{d}/\partial{x} = - v/d \f$
     .
   with \f$ v=tg-t \f$. Moreover
     - \f$ \partial{x}/\partial{t} = \dot{x} \f$
     .
   Thus,
     - \f$ r=(v/d)^t \dot{x} \f$
     .
   and
     - \f$ t2g=d^2/(v^t \dot{x}) = (v^t v) / (v^t \dot{x}) \f$
     .

   In this context \f$ \dot{x}=(\dot{q},\ddot{q}) \f$. We need to estimate \f$ \ddot{q}\f$.
   Probably the easiest estimation is to take it as 0. An alternative is
   to use the acceleration resulting from u=0 (null action). Yet another
   option is to select the action which results in lower time2go. This
   optimization can be approximated via sampling in the space of
   actions or computed in closed form via linear programming if
   \f$ \ddot{q}\f$ can be expressed in linear form with respect
   to the actions (this is not implemented yet).

   Finally, note that we compute the time to go in the parameter space
   (in this way v, makes some sense). Thus, 'x' is actually 't'
   and \f$ \dot{q} \f$ is the second half of 't' (the one giving the
   velocity parameters).


   \param pr The set of parameters.
   \param tree The tree that will be extended. \ref START2GOAL is extended
               with forward dynamics (positive times) and \ref GOAL2START
	       is extended with backward dynamics (negative times).
   \param c The chart including the sample and the goal sample.
   \param t The parameters of the departing state in the current chart.
   \param x The departing state.
   \param tg The parameters of the goal state in the current chart. This
             is the chart also including the departing state.
   \param xg The goal state.
   \param de Euclidean distance (to be used if Time2Go is not giving any
             information).
   \param ds The dynamic space.

   \return The time to go or \ref INF if no action can approach \e x to \e xg.
*/
double Time2Go(Tparameters *pr,unsigned int tree,
	       Tchart *c,
	       double *t,double *x,double *tg,double *xg,
	       double *de,TDynamicSpace *ds);


/** 
    \brief Approaches a given state.

    Simulates different actions with the aim of approaching a given goal state and
    identifies the action that approaches most to the goal.

    \param pr The set of parameters.
    \param intFunction The integration function to use.
    \param tree The tree including the samples.
    \param x The state from where to start the simulation.
    \param tol Tolerance to reach q_rand.
    \param q_rand The targed state.
    \param tolg Tolerance to reach the goal.
    \param goal The goal state.
    \param st The time span of the best action.
    \param xb The best state (the closest to \e q_rand).
    \param ub The best action (the one taking from \e x to \e xb).
    \param ns Number of intermediate steps from \e x to \e xb.
    \param path Intermediated states from \e x to \e xb.
    \param actions Action to get to each intermediate step.
                   Typically the same action for all.
    \param times Time between intermediate steps.
    \param ds The dynamic space.

    \return The minimum distance to the goal, i.e., the distance
            between \e xb and the \e q_rand.
*/
double ApproachState(Tparameters *pr,Tintegrator *intFunction,unsigned int tree,
		     double *x,
		     double tol,double *q_rand,double tolg,double *goal,
		     double *st,double *xb,double *ub,
		     unsigned int *ns,double ***path,double ***actions,double **times,
		     TDynamicSpace *ds);

/** 
    \brief Extends a dynamic RRT until we reach a targed point.

    Adds as many branches as necessary to the RRT (using \ref AddBranchToRRT)
    until a targed configuration is reached (approached at a small distance).

    The tree extension is performed using the strategy defined in
    Dalibard, S., Nakhaei, A., Lamiraux, F., and Laumond, J.-P. (2009).
    Whole-body task planning for a humanoid robot: a way to integrate collision
    avoidance. In IEEE-RAS International Conference on Humanoid Robots,
    pages 355-360.

    \param pr The set of parameters.
    \param intFunction The integration function.
    \param pg A point on the manifold to reach with the RRT.
              This is also a sample including only system variables.
    \param time Actual time used in the planning.
    \param pl The length of the output path, if any. If no path is found.
              this is undefined.
    \param ns Number of steps of the output path (if any).
    \param path Configurations defining the output path (points on the manifold).
    \param da Dimension of the action space. Only used in dynamical systems.
              Otherwise is 0.
    \param actions Action executed to reach step in the soluiont. Only used in
                   dynamical systems.
    \param times Time to reach each state. Only used in dynamical systems.
    \param grst Global RRT statistics. Used when collecting averages over
                different RRT executions. Otherwise is NULL.
    \param w The base type with the equations (and possibly obstacles).
    \param rrt The RRT to expand.

    \return TRUE if the path exists.
*/
boolean kinoRRT(Tparameters *pr,Tintegrator *intFunction,double *pg,
		double *time,
		double *pl,unsigned int *ns,double ***path,
		unsigned int *da,double ***actions,double **times,
		TRRTStatistics *grst,TAtlasBase *w,Trrt *rrt);

/** 
    \brief Extends a dynamic bi-directional RRT until we reach a targed point.

    Adds as many branches as necessary to the RRT (using \ref AddBranchToRRT)
    until a targed configuration is reached (approached at a small distance).

    The tree extension is performed using the strategy defined in
    Dalibard, S., Nakhaei, A., Lamiraux, F., and Laumond, J.-P. (2009).
    Whole-body task planning for a humanoid robot: a way to integrate collision
    avoidance. In IEEE-RAS International Conference on Humanoid Robots,
    pages 355-360.

    \param pr The set of parameters.
    \param intFunction The integration function.
    \param pg A point on the manifold to reach with the RRT.
              This is also a sample including only system variables.
    \param time Actual time used in the planning.
    \param pl The length of the output path, if any. If no path is found.
              this is undefined.
    \param ns Number of steps of the output path (if any).
    \param path Configurations defining the output path (points on the manifold).
    \param da Dimension of the action space. Only used in dynamical systems.
              Otherwise is 0.
    \param actions Action executed to reach step in the soluiont. Only used in
                   dynamical systems.
    \param times Time to reach each state. Only used in dynamical systems.
    \param grst Global RRT statistics. Used when collecting averages over
                different RRT executions. Otherwise is NULL.
    \param w The base type with the equations (and possibly obstacles).
    \param rrt The RRT to expand.

    \return TRUE if the path exists.
*/
boolean kinobiRRT(Tparameters *pr,Tintegrator *intFunction,double *pg,
		  double *time,
		  double *pl,unsigned int *ns,double ***path,
		  unsigned int *da,double ***actions,double **times,
		  TRRTStatistics *grst,
		  TAtlasBase *w,Trrt *rrt);

/** 
    \brief Extends a dynamic EST until we reach a targed point.

    Adds as many branches as necessary to the EST (using \ref AddBranchToRRT)
    until a targed configuration is reached (approached at a small distance).

    The tree extension is performed using the strategy defined in HSU et al.

    \param pr The set of parameters.
    \param intFunction The integration function.
    \param pg A point on the manifold to reach with the RRT.
              This is also a sample including only system variables.
    \param time Actual time used in the planning.
    \param pl The length of the output path, if any. If no path is found.
              this is undefined.
    \param ns Number of steps of the output path (if any).
    \param path Configurations defining the output path (points on the manifold).
    \param da Dimension of the action space. Only used in dynamical systems.
              Otherwise is 0.
    \param actions Action executed to reach step in the soluiont. Only used in
                   dynamical systems.
    \param times Time to reach each state. Only used in dynamical systems.
    \param grst Global RRT statistics. Used when collecting averages over
                different RRT executions. Otherwise is NULL.
    \param w The base type with the equations (and possibly obstacles).
    \param rrt The RRT to expand.

    \return TRUE if the path exists.
*/
boolean kinoEST(Tparameters *pr,Tintegrator *intFunction,double *pg,
		double *time,
		double *pl,unsigned int *ns,double ***path,
		unsigned int *da,double ***actions,double **times,
		TRRTStatistics *grst,TAtlasBase *w,Trrt *rrt);

/** 
   \brief Computed the potential and kinetic energy of a system.

   This replicates part of the the EnerMo function in the code by
   <a href="http://royfeatherstone.org/spatial">Featherstone</a>.

   \param pr The set of parameters.
   \param x The state.
   \param pe The computed potential energy.
   \param ke The computed kinetic energy.
   \param ds The dynamic space with auxiliary data.
*/
void MechEnergy(Tparameters *pr,double *x,double *pe,double *ke,TDynamicSpace *ds);

/** 
    \brief Inverse Dynamics problem

    Computes the input u for the inverse dynamics of a closed kinematic chain.

    \param pr The set of parameters.
    \param hasIE TRUE if the independent equations in \e ds are already computed.
    \param c The chart parametrizing x.
    \param x The state (including both position and velocity).
    \param acc Desired acceleration.
    \param u The action (forces, moments) of the inverse dynamics (output).
    \param ds The dynamic information.
*/
void ComputeInverseDynamics(Tparameters* pr,boolean hasIE,Tchart *c,
			    double *x,double *acc,double *u,TDynamicSpace *ds);


/** 
   \brief Next dynamical state.

   Computes next state using the implicit trapezoid method.

   \param pr System parameters.
   \param tree Tree being extended. If the tree is \ref GOAL2START
               the integration is done back in time (although the
	       returned integration time is positive).
   \param delta Expected step size. We try to adjust the time (h) so
                that the distance moved in tangent space is delta.
		This bound is not enforced thought (the actual displacement
		may be different from delta).
   \param gc Gravity compensation. If true the action is interpreted
             as an increment over the gravity compensantion.
   \param xn Current state.
   \param yn Parameters of the current state in the currrent chart.
   \param c Current chart.
   \param u Applied action.
   \param h The integration time (output).
   \param hmax Maximum value for h.
   \param x Next state (output).
   \param it Number of iterations in the Broyden. This information is 
             returned for collecting statistics at the level of AtlasRRT
	     (the caller of this function).
   \param ds The dynamic information.

   \return 0 if the step is executed normally, 1 if there is a problem
           converging to the next state, and 2 if the next state is
	   not valid due to dynamic constraints.
*/
unsigned int NextDynamicState(Tparameters *pr,unsigned int tree,
			      double delta,boolean gc,
			      double *xn,double *yn,Tchart *c,double* u,
			      double *h,double hmax,double *x,
			      unsigned int *it,
			      TDynamicSpace *ds);

/** 
   \brief Next dynamical state.

   Computes next state using the explicit Euler method in local coordinates.
   
   The difference with respect \ref NextDynamicStateEuler is that here the
   final point is foced to be on the manifold. The Euler method is applied
   in local coordinates the final parameter is projected to the manifold.

   \param pr System parameters.
   \param tree Tree being extended. If the tree is \ref GOAL2START
               the integration is done back in time (although the
	       returned integration time is positive).
   \param delta Expected step size. We try to adjust the time (h) so
                that the distance moved in tangent space is delta.
		This bound is not enforced thought (the actual displacement
		may be different from delta).
   \param xn Current state.
   \param yn Parameters of the current state in the currrent chart.
   \param c Current chart.
   \param u Applied action.
   \param h The integration time (output).
   \param hmax Maximum value for h.
   \param x Next state (output).
   \param ds The dynamic information.

   \return 0 if the step is executed normally, 1 if there is a problem
           converging to the next state, and 2 if the next state is
	   not valid due to dynamic constraints.
*/
unsigned int NextDynamicStateLocalEuler(Tparameters *pr,unsigned int tree,
					double delta,
					double *xn,double *yn,Tchart *c,double *u,
					double *h,double hmax,double *x,TDynamicSpace *ds);

/** 
   \brief Next dynamical state.

   Computes next state using the explicit RK4 method in local coordinates.
   
   The difference with respect \ref NextDynamicStateRK4 is that here the
   final point is foced to be on the manifold. The RK4 method is applied
   in local coordinates the final parameter is projected to the manifold.

   \param pr System parameters.
   \param tree Tree being extended. If the tree is \ref GOAL2START
               the integration is done back in time (although the
	       returned integration time is positive).
   \param delta Expected step size. We try to adjust the time (h) so
                that the distance moved in tangent space is delta.
		This bound is not enforced thought (the actual displacement
		may be different from delta).
   \param xn Current state.
   \param yn Parameters of the current state in the currrent chart.
   \param c Current chart.
   \param u Applied action.
   \param h The integration time (output).
   \param hmax Maximum value for h.
   \param x Next state (output).
   \param ds The dynamic information.

   \return 0 if the step is executed normally, 1 if there is a problem
           converging to the next state, and 2 if the next state is
	   not valid due to dynamic constraints.
*/
unsigned int NextDynamicStateLocalRK4(Tparameters *pr,unsigned int tree,
				      double delta,
				      double *xn,double *yn,Tchart *c,double *u,
				      double *h,double hmax,double *x,TDynamicSpace *ds);


/** 
   \brief Next dynamical state using the Euler method.

   Computes next state using forward Euler method.

   \param pr The set of parameters.
   \param tree Tree being extended. If the tree is \ref GOAL2START
               the integration is done back in time (although the
	       returned integration time is positive).
   \param h Time interval. We need to approximate the average acceleration in
            this interval. It may be negative.
   \param delta The maximum distance between consecutive states. If not \ref INF
                the time interval \e h will be adapted accordingly. 
		We try to adjust the time (h) so
                that the distance moved in tangent space is delta.
		This bound is not enforced thought (the actual displacement
		may be different from delta).
   \param x Current state.
   \param u Applied action.
   \param xNew Next state (output).
   \param ds The dynamic information.

   \return 0 if the step is executed normally, 1 if there is a problem
           with the next state (the integration could not be
	   fully computed up to the given integration time).
*/
unsigned int NextDynamicStateEuler(Tparameters *pr,unsigned int tree,double *h,double delta,
				   double *x,double *u,double *xNew,
				   TDynamicSpace *ds);

/** 
   \brief Next dynamical state using the RK4 method.

   Computes next state using 4th order Runge-Kutta.

   \param pr The set of parameters.
   \param tree Tree being extended. If the tree is \ref GOAL2START
               the integration is done back in time (although the
	       returned integration time is positive).
   \param h Time interval. We need to approximate the average acceleration in
            this interval. It may be negative.
   \param delta The maximum distance between consecutive states. If not \ref INF
                the time interval \e h will be adapted accordingly. 
		We try to adjust the time (h) so
                that the distance moved in tangent space is delta.
		This bound is not enforced thought (the actual displacement
		may be different from delta).
   \param x Current state.
   \param u Applied action.
   \param xNew Next state (output).
   \param ds The dynamic information.

   \return 0 if the step is executed normally, 1 if there is a problem
           with the next state (the integration could not be
	   fully computed up to the given integration time).
*/
unsigned int NextDynamicStateRK4(Tparameters *pr,unsigned int tree,double *h,double delta,
				 double *x,double *u,double *xNew,
				 TDynamicSpace *ds);

/** 
   \brief System integration for some time interval.

   Computes the state after some time using a given numerical procedure
   to approximte the average acceleration in the given time interval.
   During the integration we check for
   possible non-valid dynamic states (this is actually done in the \e intFunction)
   and possible collisions with obstacles. In this case, the integration is
   stopped before compleating the given integration time.

   \param pr System parameters.
   \param intFunction The function to use to compute the average acceleration.
                      Typical procedures are the Euler or the RK4 methods.
   \param tree Tree being extended. If the tree is \ref GOAL2START
               the integration is done back in time (although the
	       returned integration time is positive).
   \param xn Current state.
   \param u Applied action.
   \param delta The time step size for each individual integration step.
   \param intTime Total integration time.
   \param tolq Tolerance for reaching q_rand.
   \param q_rand q_rand
   \param tolg Tolerance for reaching the goal.
   \param goal The goal.
   \param ns Number of steps taken to complete the integration. Only used
             if not NULL.
   \param path The states in each individual integration step. This includes
               all the generated states but the firt one. Only used
               if not NULL.
   \param actions Action executed to in each integration step. Right now
                  the same action is used, but we may use a smooth transition
		  between actions in the future. Only used if not NULL.
   \param times Time of each individual integration step.
   \param time The actual integration time: accumulated for all integration
               steps. Should be \e intTime if nothing extrange was found
	       in intermediate states: collision... (output).
   \param x Next state. The last state of the integration (output).
   \param ds The dynamic information.

   \return 0 if the step is executed normally, 1 if there is a problem
           with the next state (the integration could not be
	   fully computed up to the given integration time).
*/
unsigned int NumericIntegration(Tparameters *pr,Tintegrator *intFunction,
				unsigned int tree,
				double *xn,double *u,double delta,double intTime,
				double tolq,double *q_rand,double tolg,double *goal,
				unsigned int *ns,double ***path,double ***actions,double **times,
				double *time,double *x,TDynamicSpace *ds);

/** 
   \brief Dynamic simulation with a given action using the Euler method.

   Dynamic simulation from a given point applying a given action for the integration time
   fixed in the paremeter structure using the Euler method

   \param pr The set of parameters.
   \param intFunction The integration function.
   \param da Dimension of the action space. Number of elements in  \e u and in
             each vector in \e actions.
   \param u The action to apply.
   \param s The initial sample.
   \param steps Steps to simulate (each of time INTEGRATION_TIME).
   \param ns Number of steps of the output paht (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param actions The action executed at each configuration. In this particular
                  function this is just a repetition of the input action \e u.
   \param times The time between each configuration.
   \param ds The dynamic information.
*/
void Simulate(Tparameters *pr,Tintegrator *intFunction,unsigned int da,double *u,double *s,
	      unsigned int steps,unsigned int *ns, double ***path, double ***actions,
	      double **times,TDynamicSpace *ds);

/** 
   \brief Computes the linear system y = Ay+Bu+c in parameter space.

   Computes the matrices of the linear system and store them in the chart info. Note that
   the linearization is made around the zero input trajectory.

   \param pr The set of parameters.
   \param c The chart including the sample and the goal sample.
   \param y0 The parameter where to linearize.
   \param x0 The state where to linearize.
   \param u0 The input where to linearize.
   \param Uc Basis of the current tangent space. 
   \param mA Linearization w.r.t. the parameters (matrix 2*dof x 2*dof).
   \param mB Linearization w.r.t. the actions (matrix 2*dof x dof).
   \param vc The independent term of the linearization (vector 2*dof).
   \param ds The dynamic information. If the linearization is to be executed in parallel
             (i.e., if OPENMP is available and this function is not called from 
	     a parallel code), \e ds must be an array of DynamicSpaces (with the size
	     of the available threads).
*/
void LinearizeDynamics(Tparameters *pr,Tchart *c,double *y0,double *x0,double *u0,double *Uc,
		       double **mA,double **mB,double **vc,TDynamicSpace *ds);

/** 
   \brief Determines a LQR policy in parameter space.

   Determines an open loop LQR policy in parameter spac, i.e., find sthe optimal u(t) that
   connects the initial y0 with the random sample y1 for the linear system
   of the form y_dot = A*y+B*u+C

   \param pr The set of parameters.
   \param y0 The initial parameter.
   \param y1 The goal parameter.
   \param tmax Maximum horizon.
   \param mA A matrix of the linear system (linearization from nonlinear system).
   \param mB B matrix of the linear system (linearization from nonlinear system).
   \param vc c vector of the linear system (linearization from nonlinear system).
   \param vd Not used. Just defined for compatibility with \ref LQRComputePolicy_t
   \param iRBt The product of R^-1 and B^t
   \param BiRBt The proecut B*R^-1*B^t
   \param ds The dynamic information.

   \return Optimal time (the time at which y1 will be reached, according to the
           computed policy).
*/
double LQRComputePolicy(Tparameters *pr,double *y0,double *y1,double tmax,
			double *mA,double *mB,double *vc,double *vd,double *iRBt,double *BiRBt,
			TDynamicSpace *ds);

/** 
   \brief Determines a LQR policy in parameter space.

   Alternative version of \ref LQRComputePolicy where G is computed as an integral
   in time (not in G itself).

   \param pr The set of parameters.
   \param y0 The initial parameter.
   \param y1 The goal parameter.
   \param tmax Maximum horizon.
   \param mA A matrix of the linear system (linearization from nonlinear system).
   \param mB B matrix of the linear system (linearization from nonlinear system).
   \param vc c vector of the linear system (linearization from nonlinear system).
   \param vd vd=A^-1*vc. Computed before to avoid repetitions.
   \param iRBt The product of R^-1 and B^t
   \param BiRBt The proecut B*R^-1*B^t
   \param ds The dynamic information.

   \return Optimal time (the time at which y1 will be reached, according to the
           computed policy).
*/
double LQRComputePolicy_t(Tparameters *pr,double *y0,double *y1,double tmax,
			  double *mA,double *mB,double *vc,double *vd,double *iRBt,double *BiRBt,
			  TDynamicSpace *ds);

/** 
   \brief Determines the optimal action given the policy computed in \ref LQRComputePolicy.

   Determines the optimal action for a given time from 
   the policy computed in \ref LQRComputePolicy.

   \param pr The set of parameters.
   \param u The input vector (output).
   \param t The time t where the optimal input will be evaluated: u(t).
   \param ds The dynamic information.

   \return The ratio of actions non-saturated actions (0 = none is saturated
           1 = all are saturated).
*/
double LQRPolicy(Tparameters *pr,double *u,double t,TDynamicSpace *ds);

/** 
   \brief Dynamic simulation with a given action using the RK4 method.

   Dynamic simulation from a given point applying a given action for the integration time
   fixed in the paremeter structure using the RK4 method

   \param pr The set of parameters.
   \param da Dimension of the action space. Number of elements in  \e u and in
             each vector in \e actions.
   \param action The action to apply.
   \param steps Steps to simulate (each of time INTEGRATION_TIME).
   \param ns Number of steps of the output paht (if any).
   \param path Configurations defining the output path (points on the manifold).
   \param actions The action executed at each configuration. In this particular
                  function this is just a repetition of the input action \e u.
   \param times The time between each configuration.
   \param ds The dynamic information.
*/
void SimulateRK4(Tparameters *pr,unsigned int da,double *action,
		 unsigned int steps,unsigned int *ns, double ***path, double ***actions,
		 double **times,TDynamicSpace *ds);

/** 
   \brief Dimension of the action space.

   Returns the dimension of the action space.

   The action space can be seen as a box in Rn space with n the value
   returned by this function. Any point in this box is a valid
   action. The limits of the box are the
   maximum forces and torques of the actuators.

   \param ds The dynamic information.

   \return The dimension of the action space.
*/
unsigned int ActionSpaceDimension(TDynamicSpace *ds);

/** 
   \brief Converts an indentifier to an action vector.

   Defines an action given an identifier. This mapping can be
   fixed (the same action is returned given an identifer) or
   varible (a random action is returned each time the function
   is used with the same indentifier).

   The identifier is from 0 to
   \ref CT_N_DYNAMIC_ACTIONS "N_DYNAMIC_ACTIONS-1".

   The size of the action vector is given by \ref ActionSpaceDimension

   \param id The action identifier.
   \param u The action vector to generate. The space must be allocated
            and deallocated by the caller.
   \param ds The dynamic information.

   \return TRUE if the action can actually be defined.
*/
boolean GetActionFromID(unsigned int id,double *u,TDynamicSpace *ds);

/** 
   \brief Prints defines.

   Prints the defines in chart.h

   This is used only for debug purposes.
   
   \param f The file where to store the values.
*/
void PrintDynamicsDefines(FILE *f);

/** 
   \brief Deletes the dynamic space.

   Destructor. Frees the memory included in a dynamic space strucure.

   \param ds The dynamic space to delete.
*/
void DeleteDynamicSpace(TDynamicSpace *ds);

#endif
