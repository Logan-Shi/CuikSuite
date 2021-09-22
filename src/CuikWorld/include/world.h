#ifndef WORLDH
#define WORLDH

#include "vector.h"
#include "environment.h"
#include "mechanism.h"
#include "cuiksystem.h"
#include "equations.h"
#include "plot3d.h"
#include "box.h"
#include "csmapping.h"
#include "parameters.h"
#include "filename.h"
#include "statistics.h"
#include "list.h"
#include "jacobian.h"
#include "cd.h"

#include <stdlib.h>


/** 
     \file world.h
    \brief Definition of the Tworld type and the associated functions.

    Definition of the Tworld type and the associated functions.

    \sa Tworld, world.c.
   
*/

/*****************************************************************************/

/** \brief When generating 3d animations, delay before starting the animation.

    When generating 3d animations, delay before starting the animation (in 
    seconds).
*/
#define INITIAL_FRAME_DELAY 5.0

/** \brief When generating 3d animations, frame rate.

    When generating 3d animations, frames per second.
*/
#define FRAME_RATE (1.0/10) 

/** \brief When generating 3d animations, delay between the end of the 
           animation and the exit of the animation browser.

    When generating 3d animations, delay between the end of the animation and
    the exit of the animation browser (in seconds).
*/
#define FINAL_FRAME_DELAY 500.0
/*****************************************************************************/
/*****************************************************************************/

/** \brief One of the stages of  the \ref Tworld structure definition.

    The world is in the stage of adding new elements (links, joints, obstacles,...).
*/
#define WORLD_IN_DEFINITION 0

/** \brief One of the stages of  the \ref Tworld structure definition.

    The world is concluded and we can analyze it (define the equations, etc).
*/
#define WORLD_DEFINED 1

/*****************************************************************************/

/** 
   \brief One of the possible variables to couple in tensegrities.

   Use when the length of some tensegrity elements must be the same.
   This only make sense when the length of both elements is variable.
*/
#define COUPLE_LENGTH      0

/** 
   \brief One of the possible variables to couple in tensegrities.

   Use when the rest length of some tensegrity elements must be the same.
   This only make sense when the rest lengh of both elements is variable.
*/
#define COUPLE_REST        1

/** 
   \brief One of the possible variables to couple in tensegrities.

   Use when the force of some tensegrity elements must be the same.
   This only make sense when the force of both elements is variable.
*/
#define COUPLE_FORCE       2

/** 
   \brief One of the possible variables to couple in tensegrities.

   Use when the orientation of some tensegrity elements must be the same.
   This only make sense when the orientation of both elements is variable.

   \todo Generalize the orientation constraint betwee tensegrity elements
         so that we can set a fixed rotation between them.
*/
#define COUPLE_ORIENTATION 3

/*****************************************************************************/

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.
     This is the normal leg with fixed length used for parallel platforms.
     No force information is associated.
*/
#define LEG           0

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.
     This is the normal leg with variable length used for parallel platforms.
     The range of extension must be realistic: range of displacements below
     the minimum extension.
     No force information is associated.
*/
#define PRISMATIC_LEG 1

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.
     This is a fixed length tensegrity element which can only support compression.
*/
#define STRUT         2

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.
     This is a fixed length tensegrity element which can support both tension and compression.
*/
#define BAR           3

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.
     This is a fixed/variable length tensegrity element which can only support tensions.
*/
#define CABLE         4

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.
     This is a variable length tensegrity element which can only support tension.
     The difference with cables is that the length is always variable and the representation.
*/
#define SPRING        5

/** 
    \brief One of the possible types of legs.

    This is a spring but without force model.
*/
#define KSPRING        6

/** 
    \brief One of the possible types of legs.

     One of the possible types of legs.

     This is a variable length tensegrity element which can support both tension and compression.
     It is basically a prismatic bar.
     The range of extension must be realistic: range of displacements below
     the minimum extension.
*/
#define PRISMATIC_BAR 7

/*****************************************************************************/


/** 
    \brief A step in a kinematic branch.

   A kinematic branch is a series of joints connecting two given link in
   a mechanism, typically, the ground link and any other link.

   This structure define the a basic step in a kinematic chain (see 
   \ref Tbranch).
*/
typedef struct {
  Tjoint *joint; /**< The joint used in the step.*/
  double sign; /**< The sign (i.e., the orientation) of this joint. Remember 
                    that joint relate a joint \e a with a joint \e b and it 
                    could be the case that the branch step need to be from 
                    \e b to \e a instead of from \e a to \e b.*/
} TBranchStep;

/** 
    \brief A kinematic branch.

   A kinematic branch taking from one link to another, typically from the
   ground link to any one of the links in the mechanisms. 
   
   Kinematic branches are used to derive the equations to give coordinates
   of one link in the global reference frame (i.e., in the frame of reference
   of the ground link).

   Kinematic branches are also used to derive loop equations. In this case we 
   have closed kinematic brances, that is, branches that depart and arribe at  
   the same link.

   In any case, kinematic branches are generated expanding a tree from the 
   ground link.

   This is only defined here since it is used by \ref Tworld, but all of the 
   methods associated with this object are hidden.
*/
typedef struct {
  Tvector steps; /**< Sequence of steps forming the kinematic chain.*/
} Tbranch;

/** 
    \brief All the necessary information to generate equations for mechanisms.

   All the necessary information to generate equations for mechanisms and the
   equations themselves.

   It also includes the information about the obstacles around the 
   mechanisms and, thus, provide methods to detect collisions.

   Finally, the functions associated to this structure allow to animate
   solution paths (i.e. to move the mechanisms along a set of configurations).
*/
typedef struct {
  unsigned int stage; /**< Stage of the world structure: EMPTY_WORLD, 
			   WORLD_WITH_GEOMETRY, WORLD_WITH_COLLISIONS, 
			   WORLD_WITH_EQUATIONS. Latter stages imply
		           the previous ones. */

  Tenvironment e; /**< The environment. */
  Tmechanism m;   /**< The mechanism. */

  unsigned int nl; /**< Number of links in the mechanism.*/
  unsigned int ncl;/**< Number of connection links in the mechanism.*/
  unsigned int nb; /**< Number of convex bodies forming the links.*/
  unsigned int nj; /**< Number of joints.*/
  unsigned int no; /**< Number of obstacles.*/
  unsigned int np; /**< Number of convex bodies in the links and in the 
		        environment (nb+no).*/

  unsigned int endEffector; /**<  Identifier of the link that has to be considered
			          as the manipulated object (or end effector). */
  double maxCoord; /**< Sum of the maximum coordinate values for all objects 
		        in the mechanism. */

  boolean **checkCollisionsLL;/**< TRUE if we have to chek the collision 
				   between the corresponding pair of links. 
				   Note that in the wold definition file we can
			           not activate/desactive the collision 
				   checking for sub-parts
			           of a link. To get this effect you can use 
				   assign the DECOR
			           type to the link sub-parts not to be 
				   considered in the collision detection.*/ 
  boolean **checkCollisionsLO;/**< TRUE if we have to chek the collision 
				   between the corresponding link and object 
				   in the environment. 
				   Note that in the wold definition file we can
				   not activate/desactive the collision 
				   checking for sub-parts
			           of a link. To get this effect you can 
				   use assign the DECOR
			           type to the link sub-parts not to be 
				   considered in the collision detection.*/

  TCuikSystem kinCS; /**< The cuiksystem derived form the mechanism. */

  unsigned int nvars;  /**< Number of variables in the kinCS */
  unsigned int nsvars; /**< Number of system variables in the kinCS */
  boolean *systemVars; /**< Array of booleans with as many elements as 
			    variables has the cuiksystem
			    and where each entry is TRUE if the corresponding 
			    variable is a system variable. */
  
  unsigned int *sortedLinks; /**< Links as they are encountered when expanding
		 	          graph implicitly defined by links and joints. */
  unsigned int *predLink;    /**< Predecesor link (in the tree of links spanning
			          the kinematic graph). */
  unsigned int *jointTo;     /**< Joint taking to a given link when expanding 
		 	          graph implicitly defined by links and joints. */
  signed int *jointS;        /**< Orientation of jointTo. */
  Tbranch *branch2Link; /**< Sequence of joints taking from the ground link 
			     to each of the other links. This is used to 
			     compute the refEqs (see below)
		             and to transfrom from dof to matrices. 
			     This informatin is redundant with the one
			     encoded in 'sortedLinks' and 'joinsTo' but we keep
			     it for convenience. */

  Tequations refEqs;    /**< Equations giving (part of) the forward kinemtics
			     for all links.
 			     In matrix-like representations this includes
			     three equations for each link giving the position 
			     of the frame of reference of each link in the 
			     global frame of reference. They define the 
			     translations using rotation variables and fixed 
			     vectors.
			     When using a REP_DOF this includes matrix equations
			     giving the homogeneous matrix for each link. */
  TJacobian refEqsJ;    /**< Jacobian of the equations in refEqs. This is computed
			     in all the cases, but only actually used if the
			     representation is DOF-based in the \ref WorldAtomJacobian
			     function. Note that the
			     refEqs are given in the original variables (i.e.,
			     without any simplification) and so it is the
			     Jacobian. */

  boolean *openLink;    /**< TRUE if the link is at the end of an open branch. 
			     In this case the kinematic system includes 
			     variables with the position of this
			     link and we have to take this into account when 
			     generating configurations from degrees of freedom 
			     (see \ref WorldDOF2Sol)*/

  unsigned int nLoops;          /**< Number of loops in the mechanisms. */
  boolean *closingJoint;        /**< TRUE for joints closing loop. */
  unsigned int *sortedClosures; /**< Loop closures in order of appearance. */
  
  unsigned int nwcd;    /**< Number of wcd structures being initialized. When
			     using OpenMP we initiliaze as many wcd structures
			     as threads so that we can check for collision detection
			     in parallel. */
  TworldCD *wcd;        /**< The collision detection information, if any. */

  unsigned int ndof;       /**< Number of degrees of freedom. */
  unsigned int da;         /**< Dimension of the action space. */

  unsigned int *link2dof;  /**< Mapping from links to degrees of freedom. */
  unsigned int *dof2link;  /**< Mapping from degrees of freedom to link. */
  unsigned int *dof2param; /**< Mapping from degrees of freedom to specific 
			        configuration of each link. */
  
  unsigned int *joint2dof; /**< Mapping from joints to degrees of freedom. */
  unsigned int *dof2joint; /**< Mapping from degrees of freedom to joints. */
  unsigned int *dof2range; /**< Mapping from degrees of freedom to specific 
			        range of each joint. */
} Tworld;


/** 
    \brief Constructor.

   Initializes an empty world.

   The expected way to initialize worlds is using the \ref InitWorldFromFile
   function. If you decide to do it yourself (i.e., using \ref InitWorld
   and then adding links, joints, obstacles, etc) the function
   \ref GenerateWorldEquations when all the information is already added
   to the world. Once this function is called no more information
   (links, joints, etc) can be possibly added to the world.

   \param w The world to initialize.
*/
void InitWorld(Tworld *w);

/** 
   \brief Constructor.

   Initializes an world from the information stored in a \e .world file.

   This is the intended way to initialize worlds. See the comments in
   \ref InitWorld.

   We don't have documentation yet about how to define world files. Please,
   have a look to the examples directory.

   \param p A set of parameters. Used, for instance, when defining the 
            equations (dummification level, etc).
   \param visualization TRUE for visualization tasks (i.e., animations)
                        and FALSE for task where nice but detailed decoration
			objects are not used (e.g., planning where the collision
			detection is typically based in rough approximations of
			the true links).
   \param error TRUE if the execution must be aborted if the file 
                does not exist.
   \param fn The name of the file from where to read the information.
   \param w The world to initialize.

   \return TRUE if the world file could actually be read.
           If the file exists but there is an error reading the file, this 
	   function throws an exception an aborts the execution.
*/
boolean InitWorldFromFile(Tparameters *p,boolean visualization,boolean error,char *fn,
			  Tworld *w);

/** 
   \brief Constructor.

   Initializes an world from the information stored in a \e .tens 
   file (a file describing a tensegrity structure).

   The utilities to deal with tensegrities are implemented in the
   src/CuikTensegrity folder and they are only used if the
   cuik-tensegrity library is available.

   We don't have documentation yet about how to define tensegrity files. Please,
   have a look to the examples directory.

   \todo Right now we use a link-based representation for tensegrities since it
         is clear  and  close to the representations used for
	 parallel platforms. In this way, the integration of the tensegrities
	 in the CuikSuite is relatively simpel. However this representation
	 uses too many variables. We could think on implementing a particular
	 type of representation for tensegrities based on representing only
	 the coordinates of the tensegrity nodes. This will be more compact.
	 However it introduces complexity in the translation from/to
	 degrees of freedom and other related procedues. In this yet to
	 implement representatoin we need coordinates (x,y,z) for the
	 tensegrity nodes, the norm of the tensegrity elements
	 l=||n_1-n_2|| (which can be fixed or variable) and auxiliary
	 variable 'd' such that l*d=l-r, with r the rest length.
	 with this variable the force of an element is f=k*d*n_1-k*d*n_2,
	 with n1, n2 the coordiantes of the connected nodes. The main
	 issue with this representation is the absence of loops
	 which is a core-assumption in the CuikSuite.

   \param p A set of parameters. Used, for instance, when defining the 
            equations (dummification level, etc).
   \param fn The name of the file from where to read the information.
   \param w The world to initialize.

   \return TRUE if the tensegrity file could be actually read.
*/
boolean InitTensegrityFromFile(Tparameters *p,char *fn,
			       Tworld *w);

/** 
    \brief Adds a link to the mechanism in the world.

   Adds a link to the mechanism in the world.

   \param l The link to add.
   \param object TRUE if the link has to be used as the object being
                 manipulated by the rest of the mechanisms. This
		 can be also seen as the end effector. Each mechanism
		 only manipulates one object, the last link declared
		 as such.
   \param w The world to update.

   \return The identifier assigned to the new link.
*/
unsigned int AddLink2World(Tlink *l,boolean object,Tworld *w);


/** 
   \brief Adds a joint to the mechanism in the world.

   Adds a joint to the mechanism in the world.

   \param j The joint to add.
   \param w The world to update.

   \return The identifier assigned to the new joint.
*/
unsigned int AddJoint2World(Tjoint *j,Tworld *w);

/** 
   \brief Adds a sph-sph joint to the world.

   Adds the links and joints defining a composite spherical-sphercial
   joint to the world. Such joint is composed by two spherical joints
   connected by a cylindrical strut. This rotation of the cylinder
   about its axis is not relevant. Thus, this composite joint is
   useful to avoid representing irrelevant degrees of freedom (i.e.,
   to obtain simpler equation systems).

   \param name Name for the link to generate. If NULL an default
               link name is used.
   \param planar TRUE if the leg must be constrained to the XY plane.
   \param type Type of leg: \ref LEG, \ref PRISMATIC_LEG, \ref STRUT,
               \ref BAR, \ref CABLE, \ref SPRING, \ref PRISMATIC_BAR
   \param lID1 Identifier of the first link to connect.
   \param lID2 Identifier of the second link to connect.
   \param points A point in the first link and a point in the 
                 second link given the position of the spherical 
		 joints.
   \param length Length of the cylinder connecting the two spherical joints.
                 Can be a range for cables (springs actually). Then this
		 gives the deformation range. Must be positive. If not it
		 is modified.
   \param stiffness Stiffnes of the central element of the composite joint.
                    Must be <0 for struts, >0 for cables, different from
		    0 for bars and 0 for non-tensegrity elements.
		    If it is not in the correct range, it is modified.
   \param rest Rest length for the central element. Must be positive. 
               If not it is modified.
   \param force Range of forces that the central element can support.
                Must be <0 for struts, >0 for cables, different from
		0 for bars and 0 for non-tensegrity elements.
		If it is not in the correct range, it is modified.
   \param radius Radius of the cylinder connecting the two sperical joints.
   \param gr Granularity to represent spheres and cylinders. For springs,
             it is used to give the number of loops of the spring.
   \param color Color of the cylinder connecting the two spherical joints.
   \param bs Body status: normal, hidden, decoration, etc.
   \param mass The mass of the leg. If the leg has more than one link the 
               same value is used for all of them.
   \param iMatrix The inertia matrix of the leg. If the leg has more than 
                  one link the same value is used for all of them.
   \param iFrame The inertial frame of the leg. If the leg has more than 
                 one link the same value is used for all of them.
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct (LQR) cost.
   \param fr Friction.
   \param da Damping.
   \param w The world where to add the leg.
 */
void AddLeg2World(char *name,boolean planar,unsigned int type,
		  unsigned int lID1,unsigned int lID2,
		  double **points,
		  Tinterval *length,double stiffness,
		  Tinterval *rest,Tinterval *force,
		  double radius,unsigned int gr,
		  Tcolor *color,unsigned int bs,
		  double mass,double **iMatrix,THTransform *iFrame,
		  double ve,double ac,double ef,double ct,double fr,double da,
		  Tworld *w);

/** 
   \brief Adds an obstacle to the environment in the world.

   Adds an obstacle to the environment in the world.

   \param name The name of the obstacle.
   \param o The convex object representing the obstacle.
   \param w The world to update.
*/
void AddObstacle2World(char *name,Tpolyhedron *o,Tworld *w);

/** 
   \brief Returns the number of degrees of freedom of the mechanism in the
          world.

  Returns the number of degrees of freedom of the mechanism in the world.
  This consideres the presenceo of loops constraining the mobility.

  \param w The world to query.

  \return The number of degrees of freedom of the mechanism in the world.

  \sa GetMechanismMobility.
*/
unsigned int GetWorldMobility(Tworld *w);

/** 
    \brief TRUE if the mechanisms in the world is based on spheres.

    Returns TRUE if the mechanisms in the world is composed by spheres only.

    \param w The world to query.

    \return TRUE if the mechanism in the world is sphere-based.
*/
boolean IsMechanismInWorldAllSpheres(Tworld *w);

/** 
   \brief Determines if a world includes velocity information.

   Determines if a world includes velocity information.

   \param p The set of parameters.
   \param w The world to query.
*/
boolean WorldHasVelocity(Tparameters *p,Tworld *w);

/** 
    \brief Gets the identifier of a link from its name.

   Gets the identifier of a link from its name (NO_UINT if there is
   no link with the given name).

   \param linkName The name of the link.
   \param w The world to query.

   \return The identifier assigned to the new link.
*/
unsigned int GetWorldLinkID(char *linkName,Tworld *w);

/** 
    \brief Gets the identifier of an obstacle from its name.

   Gets the identifier of an obstacle from its name (NO_UINT if there is
   no obstacle with the given name).

   \param obsName The name of the obstacle.
   \param w The world to query.

   \return The identifier assigned to the new link.
*/
unsigned int GetWorldObstacleID(char *obsName,Tworld *w);

/** 
    \brief Gets the name of a given obstacle.

    Gets the name given to an obstacle.
    
    \param id The identifier of the obstacle in the environment.
    \param w The workd to query.

    \return A pointer ot the name.
*/
char *GetWorldObstacleName(unsigned int id,Tworld *w);

/** 
    \brief Gets a link from its identifier.

   Gets a pointer to a link in the mechanism included in the world from its 
   identifier (NULL if there is no link with the given identifier).

   \param linkID The identifier of the link to retrive.
   \param w The world to query.

   \return The pointer to the requested link, if any.
*/
Tlink *GetWorldLink(unsigned int linkID,Tworld *w);

/** 
    \brief Gets a joint from its identifier.

   Gets a pointer to a joint in the mechanism included in the world from its 
   identifier (NULL if there is no joint with the given identifier).

   \param jointID The identifier of the joint to retrive.
   \param w The world to query.

   \return The pointer to the requested joint, if any.
*/
Tjoint *GetWorldJoint(unsigned int jointID,Tworld *w);

/** 
    \brief Gets an obstacle shape.

    Gets a pointer to the description of one obstacle in
    the environment.
    
    \param obsID The identifier of the obstacle in the environment.
    \param w The world to query.

    \return A pointer to the obstacle description.
*/
Tpolyhedron *GetWorldObstacle(unsigned int obsID,Tworld *w);

/** 
    \brief Gets the number of links in the mechanism included in the world.

   Gets the number of links in the mechanism included in the world.

   \param w The world to query.

   \return The number of links in the mechanism included in the world.
*/
unsigned int GetWorldNLinks(Tworld *w);

/** 
    \brief Gets the number of joints in the mechanism included in the world.

   Gets the number of joints in the mechanism included in the world.

   \param w The world to query.

   \return The number of joints in the mechanism included in the world.
*/
unsigned int GetWorldNJoints(Tworld *w);

/** 
    \brief Gets the number of obstacles in the environment included in the 
          world.

   Gets the number of obstacles in the environment included in the world.
   Note that each obstacle is a convex polyhedron (see \ref Tpolyhedron).

   \param w The world to query.

   \return The number of obstacles in the environment included in the world.
*/
unsigned int GetWorldNObstacles(Tworld *w);

/** 
    \brief Gets the number of convex polyhedrons that define the mechanism 
          included in the world.

   Each link can include more than one convex polyhedron. This
   function returns the sum of the number of convex polyhedrons defined
   over all links

   \param w The world to query.

   \return The number of convex bodies in the mechanism included in the world.
*/
unsigned int GetWorldNConvexBodiesInLinks(Tworld *w);

/** 
    \brief Gets the number of convex polyhedrons that define the mechanism 
          and the environment included in the world.

   Each link can include more than one convex polyhedron. Moreover, the 
   environment is also defined as a set of convex polyhedrons.
   This function returns the sum of the number of convex polyhedrons defined
   over all links and the environment.

   \param w The world to query.

   \return The number of convex parts in the mechanism and in the environment
           included in the world.
*/
unsigned int GetWorldNConvexBodies(Tworld *w);

/** 
    \brief Gets the number of degrees of freedom in the world.

   Gets the number of degrees of freedom in the world. Each joint
   introduces one or more degrees of freedom.

   Note that this is different from \ref GetWorldMobility. Here we
   return the sum of degrees of freedom of the joints.

   \param w The world to query.

   \return The number of degrees of freedom in the world.
*/
unsigned int GetWorldNDOF(Tworld *w);

/** 
    \brief Gets the dimension of the action space.

   Gets the dimension of the vector representing an action.
   This is the number of actuated degrees of freedom in
   the mechanism. Note that this is not necessarily the
   number of actuated joints since each joint can
   have more than one degree of freedom.

   \param w The world to query.

   \return The dimension of the action space.
*/
unsigned int GetWorldActionDimension(Tworld *w);

/** 
    \brief Gets the range for a given degree of freedom.

   Returns the valid range for a given degree of freedom.

   \param ndof The identifier for the degree of freedom.
   \param r The output range.
   \param w The world to query.
*/
void GetWorldRangeDOF(unsigned int ndof,Tinterval *r,Tworld *w);

/** 
    \brief Returns a label identifying each joint.

   Returns a label identifying eachjoint. This is used
   to generate interfaces.
   Right now we only return a valid label for the first degree of
   freedom of each joint and the label identifies the joint and not
   the particular degree of freedom.
   In all other cases the output is NULL.

   Note that, if different from NULL, the string is initialized
   inside this call but must be deallocated by the caller.

   \param ndof The identifier for the degree of freedom.
   \param string The output label. Possibly NULL.
   \param w The world to query.
*/
void GetWorldJointLabel(unsigned int ndof,char **string,Tworld *w);

/** 
    \brief Returns a label identifying each degree of freedom.

   Returns a label identifying each degree of freedom. This is used
   to generate interfaces.
   This is a variant of \ref GetWorldJointLabel but where all
   dof get an identifier.

   Note that, if different from NULL, the string is initialized
   inside this call but must be deallocated by the caller.

   \param ndof The identifier for the degree of freedom.
   \param string The output label. Possibly NULL.
   \param w The world to query.
*/
void GetWorldDOFLabel(unsigned int ndof,char **string,Tworld *w);

/** 
   \brief Mapping from joint index to dof.

   Returns the index in the vector of degrees of freedom corresponding
   to a given joint (the initial position of the dof variables corresponding
   to the joint)
   
   \param n The joint index.
   \param w The world to query.
   
   \return The index over the vector of dof (configuration vector).
*/
unsigned int GetWorldJoint2Dof(unsigned int n,Tworld *w);

/** 
   \brief Joint taking to a given link.

   Joint taking to a given link in the kinematic tree spanning
   the kinematic graph. This is basically used to compute
   dynamic quantities such as the mass matrix.

   \param n The identifier of the link.
   \param s Output. The orientation of the joint.   
   \param w The world information.
   
   \return The identifier of the joint taking to the link.
*/
unsigned int GetWorldJointTo(unsigned int n,signed int *s,Tworld *w);

/** 
   \brief Identifier of th n-th link.

   Returns the identifier of the n-th link in a breadth-first
   exploration of the kinematic graph.

   \param n The identifier of the link.
   \param w The world information.
   
   \return The identifier of the n-th link.
*/
unsigned int GetWorldLinkN(unsigned int n,Tworld *w);

/** 
   \brief Previous link to a given link.

   Predecesor link to a given link in the kinematic tree spanning
   the kinematic graph. This is basically used to compute
   dynamic quantities such as the mass matrix.

   \param n The identifier of the link.
   \param w The world information.
   
   \return The identifier of the previous link.
*/
unsigned int GetWorldPredLink(unsigned int n,Tworld *w);

/** 
   \brief Identifies the n-th closure link.

   Identies the link closing the n-th loop.

   \param n The identifier of the closure joint.
   \param w The world information.

   \return The identifier of the n-th closure joint.
*/
unsigned int GetWorldClosureN(unsigned int n,Tworld *w);

/** 
   \brief Identifies joints closing loops.

   Identifes joint closing loops.

   \param n The joint identifer.
   \param w The world to query.
   
   \return TRUE if the joint is used to close a loop.
*/
boolean IsClosingJoint(unsigned int n,Tworld *w);

/** 
   \brief Number of loops.

   Number of loops.

   \param w The world to query.

   \return The number of loops in the problem.
*/
unsigned int NumLoops(Tworld *w);

/** 
    \brief Checks if the system of equations is polynomial.

   Checks if the system of equations derived from the world
   is polynomial.

   \param w The world to query.

   \return TRUE if the system is polynomial.
*/
boolean IsWorldPolynomial(Tworld *w);

/** 
    \brief Activates all the possible collision between links and links and 
          obstacles.

   Activates all the possible collision betwen links and links and obstacles.

   \param fl First link. Use 0 if not sure what to use. This is used when
             including files where this function must affect
	     only the links/objects defined in the current file and in files
	     included here, but not to links/objects defined in the files
	     that include the current file.
   \param fo First object. Use 0 if not sure what to use.
   \param w The world to update.
*/
void CheckAllCollisions(unsigned int fl,unsigned int fo,Tworld *w);

/** 
    \brief Desactivates all the possible collision between links and links 
          and obstacles.

   Desactivates all the possible collision betwen links and links and 
   obstacles.

   \param fl First link. Use 0 if not sure what to use. This is used when
             including files where this function must affect
	     only the links/objects defined in the current file and in files
	     included here, but not to links/objects defined in the files
	     that include the current file.
   \param fo First object. Use 0 if not sure what to use.
   \param w The world to update.
*/
void NoCheckAllCollisions(unsigned int fl,unsigned int fo,Tworld *w);

/** 
    \brief Determines if we want to avoid any collision.

    Determines if any collision is activated and must be avoided.

    \param w The world to query.

    \return TRUE if there is at least one collision to avoid.
*/
boolean AnyCollision(Tworld *w);

/** 
    \brief Stores the collision information into a file.

   Stores the collision information into a file in the format 
   valid to be read by \ref InitWorldFromFile.

   \param f The file where to store the information.
   \param w The world with the collision information to print.
*/
void PrintCollisions(FILE *f,Tworld *w);

/** 
    \brief Activates all the possible collision between links.

   Activates all the possible collision betwen links.

   \param fl First link. Use 0 if not sure what to use. This is used when
             including files where this function must affect
	     only the links/objects defined in the current file and in files
	     included here, but not to links/objects defined in the files
	     that include the current file.
   \param w The world to update.
*/
void CheckSelfCollisions(unsigned int fl,Tworld *w);

/** 
    \brief Desactivates all the possible collision between links.

   Desactivates all the possible collision betwen links.

   \param fl First link. Use 0 if not sure what to use. This is used when
             including files where this function must affect
	     only the links/objects defined in the current file and in files
	     included here, but not to links/objects defined in the files
	     that include the current file.
   \param w The world to update.
*/
void NoCheckSelfCollisions(unsigned int fl,Tworld *w);

/** 
    \brief Activates the possible collision between a particular pair of links.

   Activates all the possible collision betwen a particular pair of links.

   Note that we don't have an interface to activate/desactivate the
   collision checking between links sub-parts. To this end you have
   to use the DECOR keyword in the sub-part definition (DECOR sub-parts
   are not used in collision checking).

   \param a The identifier of the first link of the pair whose collision 
            has to be checked.
   \param b The identifier of the second link of the pair whose collision 
            has to be checked.
   \param w The world to update.
*/
void CheckLinkLinkCollision(unsigned int a,unsigned int b,Tworld *w);

/** 
    \brief Desactivates the possible collision between a particular pair of 
          links.

   Desactivates all the possible collision betwen a particular pair of links.

   \param a The identifier of the first link of the pair whose collision has
            not to be checked.
   \param b The identifier of the second link of the pair whose collision has 
            not to be checked.
   \param w The world to update.
*/
void NoCheckLinkLinkCollision(unsigned int a,unsigned int b,Tworld *w);

/** 
    \brief Activates the possible collision between a particular link and an 
          object in the environment.

   Activates the possible collision between a particular link and an object 
   in the environment.

   Note that we don't have an interface to activate/desactivate the
   collision checking for a given link sub-part. To this end you have
   to use the DECOR keyword in the sub-part definition (DECOR sub-parts
   are not used in collision checking).

   \param a The identifier of the link of the  whose collision has to be 
            checked.
   \param b The identifier of the obstacle whose collision has to be checked.
   \param w The world to update.
*/
void CheckLinkObstacleCollision(unsigned int a,unsigned int b,Tworld *w);

/** 
    \brief Desactivates the possible collision between a particular link and 
          an object in the environment.

   Desactivates the possible collision between a particular link and an object 
   in the environment.

   \param a The identifier of the link of the  whose collision has not to be 
            checked.
   \param b The identifier of the obstacle whose collision has not to be 
            checked.
   \param w The world to update.
*/
void NoCheckLinkObstacleCollision(unsigned int a,unsigned int b,Tworld *w);

/** 
    \brief Activates the possible collision between a particular obstacle and 
          all the links.

   Activates the possible collision with a given object.

   \param fl First link. Use 0 if not sure what to use. This is used when
             including files where this function must affect
	     only the links/objects defined in the current file and in files
	     included here, but not to links/objects defined in the files
	     that include the current file.
   \param b The identifier of the obstacle whose collision has to be checked.
   \param w The world to update.
*/
void CheckObstacleCollision(unsigned int fl,unsigned int b,Tworld *w);

/** 
    \brief Deactivates the possible collision between a particular obstacle and 
          all the links.

    Deactivates the possible collision with a given object.

    \param fl First link. Use 0 if not sure what to use. This is used when
              including files where this function must affect
 	      only the links/objects defined in the current file and in files
 	      included here, but not to links/objects defined in the files
 	      that include the current file.
    \param b The identifier of the obstacle whose collision has not to be checked.
    \param w The world to update.
*/
void NoCheckObstacleCollision(unsigned int fl,unsigned int b,Tworld *w);

/** 
    \brief Desactivates the collision detection between connected links.

    Desactivates the collision between links connected by a joint.
    Additionally, for NoRot links, deactivates the collision between
    links connected to the NoRot links.

    \param fl First link. Use 0 if not sure what to use. This is used when
              including files where this function must affect
 	      only the links/objects defined in the current file and in files
	      included here, but not to links/objects defined in the files
	      that include the current file.
   \param w The world to update.
*/
void NoCheckConnectedCollisions(unsigned int fl,Tworld *w);

/** 
    \brief Initializes the collision detector.

   Initializes the collision detector.

   This is decoupled from the world initialization so that we can init it
   only when required.
   
   In some cases (for instance when parallelizing the atlas construction
   using OpenMP) we need to perform collision detection in parallel for
   different threads. To avoid problems, in this case we initialize
   separate collision detection structures.
  
   \param pr The set of parameters.
   \param mt Maximum number of threads in parallal that might use the collision 
             detection.
   \param w The world from where to read the link/obstacle information.
*/
void InitWorldCD(Tparameters *pr,unsigned int mt,Tworld *w);

/** 
    \brief Determines if any collision is potentially possible.

    Determides if, after initializing the world collision info, any collision 
    is possible.

    This function can only be used after calling \ref InitWorldCD.

    \param w The world to query.
    
    \ref TRUE if any collision is possible.
*/
boolean WorldCanCollide(Tworld *w);

/** 
   \brief Define transforms for the links from the a solution point.

   Computes a transform giving the pose for each link from
   values for a solution point. 

   The difference with respect to \ref GetLinkTransformsFromSolution
   is that here only the system variables are given. 

   \param p The parameters.
   \param simp TRUE if the solution is given in the simplified form.
   \param sol The solution point.
   \param tl The output transforms. The space is allocated inside
             this function.
   \param def Configuration parameters for each link.
   \param w The world structure with the mechanical information.
*/
void GetLinkTransformsFromSolutionPoint(Tparameters *p,boolean simp,double *sol,
					THTransform **tl,TLinkConf **def,Tworld *w);

/** 
    \brief Determines the mechanisms configuration from the pose of all links.

    Determines the mechanisms configuration from the transforms giving the global position
    of all links.

    This is basically the inverse function of \ref GetLinkTransformsFromSolutionPoint.

    \param p The set of parameters.
    \param tl The transform giving the global pose of each link.
    \param def The configuration information for each link. Use NULL if no link can deform.
    \param sol The output configuration. The space for this array is allocated internally and
               its size depends on the \ref CT_REPRESENTATION  value. In any case
	       only values for the system variables is allocated.
    \param w The world structure with the mechanical information.

    \return The size of the solution point.
*/
unsigned int GetSolutionPointFromLinkTransforms(Tparameters *p,THTransform *tl,TLinkConf *def,
						double **sol,Tworld *w);

/** 
   \brief Deletes transforms for each link.

   Deletes the transforms computed by \ref GetLinkTransformsFromDOF
   or by \ref GetLinkTransformsFromSolution.

   \param tl The array of transforms to delete.
   \param def Configuration parameters. One per link.
   \param w The world structure.
*/
void DeleteLinkTransforms(THTransform *tl,TLinkConf *def,Tworld *w);

/** 
    \brief Determines the type of collision library used.

    Determines if the collision detection engine is discrete
    or continuous. Note that the return is only valid if
    the collision detection system has been previously
    initialized.
    
    \param w The world structure to query.

    \return TRUE if we use a continuous collision detection engine.
*/
boolean WorldContinuousCD(Tworld *w);

/** 
    \brief Checks a point for collision.

   Moves the links to the position given by the corresponding transforms and
   determines if there is any collision.

   No check is done on whether the given point is actually a solution or not.

   \param all TRUE if we want to detect all the collision. FALSE just to detect
              the first one.
   \param tID Identifier of the thread executing this collision check.
              See \ref InitWorldCD. This parameter is only relevant if parameter
	      'mt' in \ref InitWorldCD is larger than 0.
   \param tl One homogeneous transform for each link.
   \param def Configuration parameter for each link.
   \param tlPrev One homogeneous transform for each link in the previous
                 configuration. Only used for continuous collision check
		 (C_FCL collision engine).
   \param defPrev Configuration parameter for each link in the previous 
                  configuration.
   \param w The world structure to check.

   \return TRUE if there is a collision.
*/
boolean MoveAndCheckCDFromTransforms(boolean all,unsigned int tID,
				     THTransform *tl,TLinkConf *def,
				     THTransform *tlPrev,TLinkConf *defPrev,
				     Tworld *w);

/** 
    \brief Checks a point for collision.

   Computes the link transforms from the solution point and calls 
   \ref MoveAndCheckCDFromTransforms.

   The solution point is assumed to have values for all variables (including 
   the dummy ones). Recall that a solution point with values only for the system
   variables can be compleated using \ref RegenerateWorldSolutionPoint
   and that a solution point in the simplified system can be converted to a 
   solution point in the full original system using 
   \ref RegenerateWorldOriginalPoint.

   \param p The set of parameters.
   \param all TRUE if we want to detect all the collision. FALSE just to detect
              the first one.
   \param tID Identifier of the thread executing this collision check.
              See \ref InitWorldCD. This parameter is only relevant if parameter
	      'mt' in \ref InitWorldCD is larger than 0.
   \param sol The solution point (in the original system including values for 
              all variables. The transform for each link is computed from the 
	      values here.
   \param solPrev Previous configuration. Only used for continuous collision
                  detection (C_FCL collision engine).
   \param w The world structure to check.

   \return TRUE if there is a collision.
*/
boolean MoveAndCheckCD(Tparameters *p,boolean all,unsigned int tID,
		       double *sol,double *solPrev,Tworld *w);


/** 
    \brief Generates a sample from a the kinematic cuiksystem in the world 
          using the Newton algorithm.

   Generates a sample from a the kinematic cuiksystem in the world using the 
   Newton algorithm. However,
      - In many cases we do not obtain a valid sample (the Newton process 
        diverged).
      - The generated samples are not necessarily collision free.

   Note that samples include values ONLY for the system variables (the
   kinematic subsystem has the same system variables than the global system).
   Thus, the boxe returned in the \e b_sol (and in the vector \e v) only 
   include ranges (or values) for the system variables.

   \param p A set of parameters.
   \param v Space where to store the solution as a point. This must be 
            allocated by the caller.
   \param b_sol The solution as a punctual box. If the Newton diverged this 
                will be a copy of the input box. This box is allocated inside 
		the function.
   \param w The world from where to get the kinematic equation system.
   
   \return TRUE if the Newton-Raphson process converged to a solution.

   \sa CuikNewton.
*/
boolean NewtonInWorld(Tparameters *p,double *v,Tbox *b_sol,Tworld *w);

/** 
    \brief Gets the system vars of the kinematic cuiksystem.

   Gets the system vars of the cuiksystem in the form of an array of
   booleans, one for each variable where only entries
   corresponding to system variables are set to TRUE.

   \param sv Space where to store the output array of booleans.
   \param w The world to query.
*/
unsigned int GetWorldSystemVars(boolean **sv,Tworld *w);

/** 
    \brief Gets the position vars of the kinematic cuiksystem.

   Gets the position vars (i.e., the non-velocity vars) 
   of the cuiksystem in the form of an array of
   booleans, one for each variable where only entries
   corresponding to position variables are set to TRUE.

   \param pv Space where to store the output array of booleans.
   \param w The world to query.
*/
unsigned int GetWorldPositionVars(boolean **pv,Tworld *w);

/** 
    \brief Gets the position equations of the kinematic cuiksystem.

   Gets the position equations (i.e., the non-velocity equations) 
   of the cuiksystem in the form of an array of
   booleans, one for each equations where only entries
   corresponding to position equations are set to TRUE.

   \param pe Space where to store the output array of booleans.
   \param w The world to query.
*/
unsigned int GetWorldPositionEqs(boolean **pe,Tworld *w);

/** 
    \brief Gets the position and velocity vars of the kinematic cuiksystem.

   Gets the position and velocity vars (i.e., dynamic-related vars) 
   of the cuiksystem in the form of an array of
   booleans, one for each variable where only entries
   corresponding to position/velocity variables are set to TRUE.

   \param pv Space where to store the output array of booleans.
   \param w The world to query.
*/
unsigned int GetWorldPositionVelocityVars(boolean **pv,Tworld *w);

/** 
    \brief Gets the position and velocity equations of the kinematic cuiksystem.

   Gets the position and velocity equations (i.e., dynamics-related equations) 
   of the cuiksystem in the form of an array of
   booleans, one for each equations where only entries
   corresponding to position/velocity equations are set to TRUE.

   \param pe Space where to store the output array of booleans.
   \param w The world to query.
*/
unsigned int GetWorldPositionVelocityEqs(boolean **pe,Tworld *w);

/** 
    \brief Gets the number of kino equations.

    Returns the number of kino equations.

    \param w The world to query.

    \return The number of kino equations.
*/
unsigned int GetWorldNumKinoEquations(Tworld *w);

/** 
    \brief Get the topology of a given variable.

   Determines the topology of a given variable.

   \param vID The variable identifier.
   \param w The world to query.
   
   \return The topology of the variable.
*/
unsigned int GetWorldVarTopology(unsigned int vID,Tworld *w);

/** 
    \brief Identifies pose related variable that survied in the simplified 
          system.

   Identifies pose related variable that survied in the simplified system.

   Pose related variables are those giving the pose of a link (typically
   the system variables).

   Here we are interested in identifying those variables that survive in the
   simplified system. This is a hack to be able to generate eigengrasp.
   Note that since is eigengrasp oriented, we do not consider the last link
   in the system (i.e., the manipulated object) but only the hand links.

   \param p The set of parameters.
   \param sv A boolean array identifying the surviving variables.
   \param w The world to analyze.
*/
unsigned int GetWorldSimpVariableMask(Tparameters *p,boolean **sv,Tworld *w);


/** 
    \brief Return the variable names.

   Returns an array with pointers to the variables names for the kinematic
   cuik system. This is used to print the variable names in the solution
   boxes.
   
   \param vn Array where to store the pointers to the variable names.
             The space for this array must be allocated/deallocated by
	     the caller. The pointers themselves not.
   \param w The world to query.  
*/
void GetWorldVarNames(char **vn,Tworld *w);

/** 
   \brief Returns the name of a given system variable.

   Returns the name of a given system variable in the
   kinematic cuiksystem.

   \param nv The index of the system variable.
   \param w The world structure to query.

   \return A pointer to the name of the variable or
           NULL if the index is out of range.
*/
char *GetWorldSystemVarName(unsigned int nv,Tworld *w);

/** 
   \brief Generates all the cuiksystems derived from the world information.

   From the information stored in a \e .world file, we generate the environment
   and mechanisms structures. From this information we have to generate
   systems of equations necessary to solve the problem. This is the purpose
   of this function. Therefore, this function should be used after reading
   the \e .world file and before start to solve the problem.

   \param p A set of parameters. 
   \param cts File with the constants defined in the world. They are only
              used if eqFile is not NULL so that the equations can re-use
	      the constatns in the world definition.
   \param eqFile File with equations to be added to the problem. NULL if
                 no extra equations need to be read.
   \param w The world structure with the information from where to generate
            the equations.
*/
void GenerateWorldEquations(Tparameters *p,Tconstants *cts,char *eqFile,Tworld *w);

/** 
    \brief Adds force equilibrium equations.

   Adds the force equilibirum equations to the system generated by 
   \ref GenerateWorldEquations. 

   This only makes sense in tensegrity structures.

   \param p A set of parameters. 
   \param w The world structure with the information from where to add
            the equations.
*/
void GenerateForceEquilibriumEquations(Tparameters *p,Tworld *w);

/** 
   \brief Creates a boolean array identifying force variables.

   Creates an array to identify the force variables in the
   problem. Only force variables, not all force related variables
   (i.e., rest length) are set.

   \param p The set of paramters.
   \param fv The array of booleans. It is allocated internally but
             be deallocated externally. 
   \param w The world query.

   \return Number of force variables in the problem.
*/
unsigned int WorldForceVars(Tparameters *p,boolean **fv,Tworld *w);

/** 
   \brief Creates a boolean array to identify kinematic variables.

   Creates an array to identify kinematic variables (i.e., no force
   variables) in the simplified cuiksystem.

   This is useful, for instance, to compute path lenghts in the
   kinematic sub-space.

   If all variables are kinematic, the output array (kv) will be
   NULL. 

   \param p The set of parameters.
   \param kv The array of booleans to create.
   \param w The world to query.

   \return The number of entries in the output array, i.e., the
           number of variables in the simplified system.
*/
unsigned int WorldSimpKinematicVars(Tparameters *p,boolean **kv,Tworld *w);

/** 
   \brief Creates an array with the indices of the force variables.

   Creates an array with the indices of the force variables.
   This can be seen as a variant of \ref WorldForceVars where
   the output is in the form of a array of indices rather than
   of as an array of booleans.

   \param p The set of paramters.
   \param iv The array of indices. It is allocated internally but
             be deallocated externally. 
   \param w The world query.

   \return Number of force variables in the problem.
*/
unsigned int WorldForceVarsIndices(Tparameters *p,unsigned int **iv,Tworld *w);

/** 
    \brief Evaluates the potential energy of a configuration.

    Computes the potential energy of a configuration. It only
    returns different from 0 for tensegrities.

    The potential energy is computed modeling the links as springs.

    \param p The set of parameters.
    \param simp TRUE if the solution point is in the simplified form.
    \param sol The solution point. If simp==FALSE, it
               includes only system variables (i.e., as it is
	       stored in solution files).
    \param w The world structure including the tensegrity definition.
             (as a void* for compatibility with the \ref MinimizeOnAtlas
	     function).

    \return The value of the potential energy. 0 for non-tensegrity
            structures.
*/
double WorldPotentialEnergy(Tparameters *p,boolean simp,double *sol,void *w);

/** 
    \brief Evaluates the gradient of the potential energy of a configuration.

    Computes the gradient of the potential energy of a configuration. It only
    returns different from a null vector for tensegrities (it can also be
    null for some tensegrities, though).

    The potential energy is computed modeling the links as springs.

    \param p The set of parameters.
    \param simp TRUE if the input point is in the simplified form.
                If so, the output is also in simplified form.
    \param sol The solution point. If simp==FALSE, it
               includes only system variables (i.e., as it is
	       stored in solution files).
    \param g The output gradient. Its form/size 
             depends on parameter \e simp.
    \param w The world structure including the tensegrity definition.

    \return The number of entries of the output array.

    \sa WorldPotentialEnergy.
*/
void WorldForceField(Tparameters *p,boolean simp,double *sol,
		     double **g,void *w);

/** 
    \brief The projected gradient of the force field.

    Computes the a projection of the gradient of the force
    field. Actually we copute
       - proj^T * H
       .
    with H the Hessian matrix of the potential energy.
    This seems a rather particular function but we 
    implement it since this is the only way in which
    we use the Hessian. Moreover, this form, we avoid
    forming the Hessian matrix (a large matrix).

    Each of the columns of the Hessian is the derivative
    of the force field w.r.t. one of the variables of the
    problem. It can be easily check that these derivatives
    are:
       - [0...0] for variables other other than l/r
       - [0... 0 +K -K 0 ... 0] if the variable is l
       - [0... 0 -K +K 0 ... 0] if the variable is r
       .
    (This applies for all the l/r in the problem).
    When computing proj^T * H we obtain:
       - +K * proj_l - K * proj_r = +K * (proj_l-proj_r)
       - -K * proj_l + K * proj_r = -K * (proj_l-proj_r)
       .
    Which is exactly what is obtained from \ref WorldForceField
    using proj as a parameter. This greatly simplifies the
    implementation of this projected gradient function.
   
    \param p The set of parameters.
    \param simp TRUE if the input point is in the simplified form.
                If so, the output is also in simplified form.
    \param proj The projection vector.
    \param sol The solution point. If simp==FALSE, it
               includes only system variables (i.e., as it is
	       stored in solution files).
    \param g The diagonal of the Hessian matrix. Its form/size
             depends on parameter \e simp.
    \param w The world structure including the tensegrity definition.

    \return The number of entries of the output array.

    \sa WorldPotentialEnergy, WorldForceField.
*/
void WorldForceFieldProjectedGradient(Tparameters *p,boolean simp,
				      double *proj,double *sol,
				      double **g,void *w);

/**  
   \brief Generate equations to fix some links.

   Generate equations to fix (some dimensions) of the translation
   of a some links.

   This is only used in tensegrity structures (in particular to
   avoid the tensegrity to be free-flying).

   \param p A set of parameters. 
   \param w The world structure with the information from where to add
            the equations.
*/
void FixLinks(Tparameters *p,Tworld *w);

/** 
   \brief Fixes a tensegrity addon.

   Tensegrity addons are geometric objects that are attached to
   tensgrity nodes. This is a form of adding rich geometry
   to tensegrities, which otherwise are only composed by
   struts, cables, and springs.

   Each addons has to be fixed to three tensegrity nodes to
   fully determine its pose. In this way the 9 dof of the
   addon (3 translations and 3 rotations) are cancelled and
   the addon is effectively fixed to the tensegrity structure.

   Note that by attaching an addon to a tensegrity, the relative
   distances between the three points used to fix the addon are
   fixed

   \param p The set of parameters.
   \param linkID The identifier of the addon.
   \param point The coordinates of three on the addon.
   \param n The identifier of three nodes in the tensegrity.
   \param w The world structure holding the tensegrity description.
*/
void WorldFixTensegrityAddon(Tparameters *p,unsigned int linkID,
			     double **point,unsigned int *n,Tworld *w);
  
/** 
   \brief Generate equations to fix the Z components of the links.

   Generate equations to define a planar tensegrity, fixing the
   Z component of the director vectors of the links.

   This is only used in tensegrity structures.

   \param p A set of parameters. 
   \param w The world structure with the information from where to add
            the equations.
*/
void FixZToZero(Tparameters *p,Tworld *w);

/** 
    \brief Couple variables from different elements of a tensegrity.

    In tensegrities many times elements share a variable: they
    have the same length, stiffness, rest length, force or even
    orientation. This function fixes the variables and must
    be used AFTER defining such variables, i.e., after
    using \ref GenerateWorldEquations.

    \param p The set of parameters.
    \param t The type of couple: length, stiffness, rest length,
             force, orientation.
    \param lID1 The identifier of the first link to couple.
    \param lID2 The identifier of the second link to couple.
    \param scale Scale factor between the variables. Only used for
                 non-orientation couplings.
    \param r Rotation between orientations. Only used in
             orientation coupling.
    \param w The world where to add the couple equations.
*/
void WorldCoupleTensegrityVariable(Tparameters *p,
				   unsigned int t,
				   unsigned int lID1,unsigned int lID2,
				   double scale,THTransform *r,
				   Tworld *w);
/** 
    \brief Adds variables/equations to detect singularities

   Extends the kinematic subsystem with variables/equations to deal with
   singularities.

   We re-defined the variables giving bounds for the joints so that
   introducing a singularity in the extreme of its range.
   Moreover, if requiered, we add equations giving the position of a link
   in the global frame.

   Note that this only part of the process to generate a system of equations 
   to detect singularities. 
   The equations to detect the loss of rank of the Jacobian are to be added 
   later.
   They are not added here to allow the user to select the variables for which
   the singularities are to be detected. This is to be done with a separate
   utility.

   \param p A set of parameters.
   \param ln If we want to find position singularities, the name of the link 
             link we want to focus on. If different from NULL, the equations 
	     giving the origin of the link in the global frame are added to 
	     the system.
   \param cs The resulting cuiksystem. The kinematic one from \e w plus the 
             added information.
   \param w The world structure with the mechism to analyze.
*/
void GenerateWorldSingularityEquations(Tparameters *p,char *ln,TCuikSystem *cs,
				       Tworld *w);

/** 
    \brief Adds variables/equations to detect translational workspace 
          boundaries.

   Extends the kinematic subsystem with variables/equations to detect
   translational workspace boundaries.

   This is a composition of \ref GenerateWorldSingularityEquations and
   \ref AddJacobianEquations to detect a particular set of singularities.


   \param p A set of parameters.
   \param ln The link whose translation we want to bound.
   \param cs The resulting cuiksystem. The kinematic one from \e w plus the 
             added information.
   \param w The world structure with the mechism to analyze.
*/
void GenerateWorldTWSEquations(Tparameters *p,char *ln,TCuikSystem *cs,
			       Tworld *w);

/** 
    \brief Gets the kinematic Jacobian.

   Returns the symbolic Jacobian for the
   kinematic equations on a given point

   The size of the Jacobian matrix is the number of equations of the
   kinematic system times the number of variables.

   \param J The returned Jacobian.
   \param w The world to query.

   \sa GetCSJacobian.
*/
void GetWorldJacobian(TJacobian *J,Tworld *w);

/** 
    \brief Gets the simplified kinematic Jacobian.

   Returns the symbolic Jacobian for the simplified
   kinematic equations on a given point.

   The size of the Jacobian matrix is the number of equations of the
   simplified kinematic system times the number of variables.

   \param p  The set of parameters.
   \param J The returned Jacobian matrix.
   \param w The world to query.

   \sa GetSimpCSJacobian.
*/
void GetWorldSimpJacobian(Tparameters *p,TJacobian *J,Tworld *w);

/** 
    \brief Gets the simplified numerical Jacobian.

   Returns the structure necessary to numericall evaluate
   the Jacobian at a given point. 

   Note that the numerical Jacobian can only be defined in
   particular problems (problems wih only matrix equations)
   since these are the systems where a clever evaluation
   (re-using matrix products) can result in computational
   savings.

   \param p  The set of parameters.
   \param nJ The returned numerical Jacobian structure.
   \param w The world to query.

   \return TRUE if the numerical Jacobian structure is actually created.
           If FALSE nothing is created and there is no need to delete
	   the structure.

   \sa GetSimpCSNJacobian.
*/
boolean GetWorldSimpNJacobian(Tparameters *p,TNJacobian *nJ,Tworld *w);

/** 
    \brief Gets the simplified numerical Hessian.

   Returns the structure necessary to numericall evaluate
   the Hessian at a given point. 

   Note that the numerical Hessian can only be defined in
   particular problems (problems wih only matrix equations)
   since these are the systems where a clever evaluation
   (re-using matrix products) can result in computational
   savings.

   \param p  The set of parameters.
   \param sJ The Jacobian of the scalar equations, if any.
   \param nH The returned numerical Hessian structure.
   \param w The world to query.

   \return TRUE if the numerical Hessian structure is actually created.
           If FALSE nothing is created and there is no need to delete
	   the structure.

   \sa GetSimpCSNHessian.
*/
boolean GetWorldSimpNHessian(Tparameters *p,TJacobian *sJ,TNHessian *nH,Tworld *w);


/** 
    \brief Gets the topology of the variables.

    Gets the topology of the variables in simplified kinematic
    equations.

    \param p The set of parameters.
    \param t Space for the output array (one entry per variable, allocated
             inside this function).
    \param w The world to query.
  
    \return The number of variables in the simplified kinematic
            system (i.e., the number of entries in the output
	    array).

    \sa GetSimpCSTopology
*/
unsigned int GetWorldSimpTopology(Tparameters *p,
				  unsigned int **t,Tworld *w);

/** 
    \brief Gets the topology of the variables.

    Gets the topology of the variables in kinematic
    equations.

    \param p The set of parameters.
    \param t Space for the output array (one entry per variable, allocated
             inside this function).
    \param w The world to query.
  
    \return The number of variables in the kinematic
            system (i.e., the number of entries in the output
	    array).

    \sa GetCSTopology
*/
unsigned int GetWorldTopology(Tparameters *p,
			      unsigned int **t,Tworld *w);

/** 
    \brief Gets the topology of the degrees of freedom.

    Gets the topology of the degrees of freedom of the mechanism.

    \param t Space for the output array (one entry per variable, allocated
             inside this function).
    \param w The world to query.
    
    \return The number of dof of the mechanism.
*/
unsigned int WorldDOFTopology(unsigned int **t,Tworld *w);

/** 
    \brief Gets the simplified kinematic Jacobian.

   Returns the symbolic Jacobian for the
   simplified kinematic equations on a given point

   The size of the Jacobian matrix is the number of equations of the
   kinematic system times the number of variables of the simplified system.

   \param p The set of parameters.
   \param nr The number of rows of the returned Jacobian matix 
             (i.e., the number of equations of the simplified system).
   \param nc The number of columns of the returned Jacobian matix 
             (i.e., the number of variables of the simplified system).
   \param J The returned Jacobian matrix. This is an array of equations.
   \param w The world to query.

   \sa GetSimpCSJacobian.
*/
void GetWorldKinJacobian(Tparameters *p,unsigned int *nr,unsigned int *nc,
			 Tequation ***J,Tworld *w);
/** 
    \brief Tries to reach the kinematic manifold.
   
   Tries to reach the kinematic manifold from a given point. This point
   in given in the simplified space (without un-used variables nor dummies).

   \param p The set of parameters.
   \param pt The initial/output point (in the simplified space).
   \param w The world with the kinematic equations.

   \return \ref DIVERGED if we could not reach a solution point or 
           \ref CONVERGED_IN_GLOBAL  if a solution point is found.

   \sa CuikNewtonSimp.
*/
unsigned int WorldSimpCuikNewton(Tparameters *p,double *pt,Tworld *w);

/** 
    \brief Evaluates the kinematic Jacobian.

   Returns the matrix resulting from evaluating the Jacobian for the
   kinematic equations on a given point

   The size of the Jacobian matrix is the number of equations of the
   kinematic system times the number of variables.

   \param p The point on which to evalutate the Jacobian.
   \param J The returned Jacobian matrix. This is allocated internally
            and must be deallocated externally.
   \param w The world to query.

   \sa EvaluateCSJacobian.
*/
void EvaluateWorldJacobian(double *p,double ***J,Tworld *w);

/** 
    \brief Evaluates the kinematic equations.

   Evaluates the set of kinematic equations on a given point.

   \param pt The evaluation point.
   \param r The array where to store the evaluation for each equation (must be
            allocated externally).
   \param w The world with the kinematic equations.

   \sa EvaluateCSEquations.
*/
void WorldEvaluateEquations(double *pt,double *r,Tworld *w);

/** 
    \brief Check if the inequalities hold.

   Checks if all the intequalities in the system hold for
   a given point.

   \param pt The point.
   \param w The world to query.
   
   \return TRUE if all inequalities hold.
*/
boolean WorldInequalitiesHold(double *pt,Tworld *w);

/** 
    \brief Check if the inequalities hold for the simplified system.

   Checks if all the intequalities in the system hold for
   a given point for the simplified system.

   \param p The set of parameters.
   \param pt The point in the simplified system.
   \param w The world to query.
   
   \return TRUE if all inequalities hold for the simplified system.
*/
boolean WorldSimpInequalitiesHold(Tparameters *p,double *pt,Tworld *w);

/** 
   \brief Determines the maximum error in the inequalites for the simplified system.

   Determines the maximum error in the inequalites for the simplified system.

   \param p The set of parameters.
   \param pt The point in the simplified system.
   \param w The world to query.

   \return The maximum error in the inequalities in the simplified system.
*/
double WorldErrorInSimpInequalities(Tparameters *p,double *pt,Tworld *w);

/** 
   \brief Evaluates the simplified kinematic equations.

   Evaluates the simplified kinematic equations on a given point.

   \param p The set of parameters.
   \param pt The evaluation point (in the simplified space).
   \param r The array where to store the evaluation for each equation (must be
            allocated externally).
   \param w The world with the kinematic equations.

   \sa EvaluateSimpCSEquations.
*/
void WorldEvaluateSimpEquations(Tparameters *p,double *pt,double *r,
				Tworld *w);

/** 
   \brief Evaluates a subset of the simplified kinematic equations.

   Evaluates a subset of the  simplified kinematic equations on a given point.

   \param p The set of parameters.
   \param se The array of booleans selecting the equations to evaluate.
   \param pt The evaluation point (in the simplified space).
   \param r The array where to store the evaluation for each equation (must be
            allocated externally).
   \param w The world with the kinematic equations.

   \sa EvaluateSimpCSEquations.
*/
void WorldEvaluateSubSetSimpEquations(Tparameters *p,boolean *se,double *pt,double *r,
				      Tworld *w);

/** 
    \brief Evalates the norm of the error in the kinematic equations for a 
          given point.

   Evaluates the kinematic equations on a point and returns the norm of the 
   error.
   
   \param p The set of parameters,
   \param pt The point on which to evaluate the kinematic equations.
   \param w The world with the equations to evaluate.

   \return The norm of the error for the given point.

   \sa ErrorInCSEquations.
*/
double WorldErrorInEquations(Tparameters *p,double *pt,Tworld *w);

/** 
    \brief Evalates the norm of the error in the kinematic equations for a 
          given point.

   The same as \ref WorldErrorInEquations but working on the simplified 
   set of kinematic equations.
   
   \param p The set of parameters.
   \param pt The point on which to evaluate the kinematic equations.
   \param w The world with the equations to evaluate.

   \return The norm of the error for the given point.

   \sa ErrorInSimpCSEquations.
*/
double WorldErrorInSimpEquations(Tparameters *p,double *pt,Tworld *w);

/** 
    \brief Error in equations from DOFs.

    Error in equation from the configuration given as degrees of freedom.
    If the internal representation is not DOF, the configuration is
    converted before computing the error.

    \param p The set of parameters.
    \param dof The degrees of freedom given the configuration.
    \param w The world with the equations to evaluate.

    \return The norm of the error for the given configuration.
*/
double WorldErrorFromDOFs(Tparameters *p,double *dof,Tworld *w);

/** 
    \brief Evaluates the functions cost defined in a world.

    Evaluates the functions cost defined in a world in a given point.
    This is basically used by T-RRT (see also \ref EvaluateCSCost).
    
    \param p The set of parameters.
    \param simp TRUE if the solution point is given in the simplified sytem.
    \param pt The solution point 
    \param w The cuiksystem with the equation to evaluate.
*/
double EvaluateWorldCost(Tparameters *p,boolean simp,double *pt,void *w);

/** 
    \brief Number of variables in the kinematic subsystem.

   Return the number of variables in the kinematic subsystem (as defined and
   without any simplification).

   \param w The world to query.

   \return The number of variables in the kinematic subsystem.
*/
unsigned int GetWorldNumVariables(Tworld *w);

/** 
    \brief Number of system variables in the kinematic subsystem.

   Return the number of system variables in the kinematic subsystem (as defined and
   without any simplification).

   \param w The world to query.

   \return The number of variables in the kinematic subsystem.
*/
unsigned int GetWorldNumSystemVariables(Tworld *w);

/** 
   \brief Reconstruct a point in original kinematic system from a simplified 
          point.
   
   Reconstruct a point in original kinematic system from a point in the 
   simplified system.

   \param p The set of parameters.
   \param s The point in the simplified system.
   \param o The output on in the original system. Space allocated internally.
            Includes all the variables (system and non-system).
   \param w The world to query.

   \return The size of the output array (number of variables in the original 
           system).

   \sa RegenerateOriginalPoint RegenerateWorldOriginalSystemPoint.
*/
unsigned int RegenerateWorldOriginalPoint(Tparameters *p,double *s,
					  double **o,Tworld *w);

/** 
   \brief Reconstruct a point in original kinematic system from a simplified 
          point.
   
   Reconstruct a point in original kinematic system from a point in the 
   simplified system. The difference with \ref RegenerateWorldOriginalPoint
   is that here the output pointo only includes the system variables.

   \param p The set of parameters.
   \param s The point in the simplified system.
   \param o The output on in the original system. Space allocated internally.
            Only includes the system variables.
   \param w The world to query.

   \return The size of the output array (number of variables in the original 
           system).

   \sa RegenerateOriginalPoint.
*/
unsigned int RegenerateWorldOriginalSystemPoint(Tparameters *p,double *s,
						double **o,Tworld *w);

/** 
    \brief Reconstruct a point in simplified kinematic system from an original 
          point.
   
   Reconstruct a point in the simplified kinematic system from a point in the 
   original system.

   \param p The set of parameters.
   \param o The point in the original system. System and non-system variables!
   \param s The output in the simplified system. Space allocated internally.
   \param w The world to query.

   \return The size of the output array (number of variables in the simplified 
           system).

   \sa GenerateSimplifiedPoint WorldGenerateSimplifiedPointFromSystem
*/
unsigned int WorldGenerateSimplifiedPoint(Tparameters *p,double *o,
					  double **s,Tworld *w);
/** 
    \brief Reconstruct a point in simplified kinematic system from an original 
          point.
   
   Reconstruct a point in the simplified kinematic system from a point in the 
   original system. The difference with respec to \ref WorldGenerateSimplifiedPoint
   is that here 'o' only includes the system variables.

   \param p The set of parameters.
   \param o The point in the original system. System variables only.
   \param s The output in the simplified system. Space allocated internally.
   \param w The world to query.

   \return The size of the output array (number of variables in the simplified 
           system).

   \sa GenerateSimplifiedPoint WorldGenerateSimplifiedPoint
*/
unsigned int WorldGenerateSimplifiedPointFromSystem(Tparameters *p,double *o,
						    double **s,Tworld *w);

/** 
    \brief Gets the kinematic search space for a given problem.

   Gets the kinematic search space for a given problem. The search space is 
   deduced from the ranges of the kinematic variables involved in the problem.

   This can be seen as a box from world constructor.

   \param b The output box with the search space.
   \param w The world to query.
*/
void GetWorldInitialBox(Tbox *b,Tworld *w);

/** 
    \brief Gets the kinematic simplified search space for a given problem.

   The same \ref GetWorldInitialBox

   \param p The set of parameters.
   \param b The output box with the search space.
   \param w The world to query.
*/
void GetWorldSimpInitialBox(Tparameters *p,Tbox *b,Tworld *w);

/** 
   \brief Dimensionality of the solution manifold.+

   Computes the dimensionality of the solution manifold assuming that
   the given point is regular.

   \param p The set of parameters.
   \param point The point on the manifold. In the original (not simplified
                form).
   \param w The world to  query.

   \return The dimension of the solution manifold.
*/
unsigned int WorldManifoldDimension(Tparameters *p,double *point,Tworld *w);

/** 
    \brief Reduces the system variables as much as possible using the kinematic 
          constraints.

   Reduces the system variables as much as possible taking into account only 
   the system equations (i.e., using only the \ref Tworld::kinCS).
   
   \param p The set of parameters to use when solving the cuiksystems (RHO, 
            SIGMA,...).
   \param b The box with the ranges to reduce.
   \param reduction The reduction ratio (size of the output box / size of the
                    input box).
   \param w The world to use in the reduction.

   \return The box status after the reduction: EMPTY_BOX, REDUCED_BOX, 
           REDUCED_BOX_WITH_SOLUTION, ERROR_IN_PROCESS.
*/
unsigned int MaxWorldReduction(Tparameters *p,Tbox *b,
			       double *reduction,Tworld *w);

/** 
    \brief Adds a world (environment plus mechanism) in a 3D scene.

   Adds a world (environment plus mechanism) in a 3D scene. 
   Note that the the mechanism is not set in any valid configuration but
   all links are plotted with its local frame overlapped with the global one.
   To actually display the mechanism in a correct configuration you should use
   \ref MoveWorld.

   \param pr The set of parameters.
   \param pt The 3d scene where we add the geometry.
   \param axesLength Length for the axes for each link. 0 not to display them.
   \param w The wold to plot.
*/
void PlotWorld(Tparameters *pr,Tplot3d *pt,double axesLength,Tworld *w);

/** 
    \brief Computes the missing values in a kinematic solution.

   Computes the non-system variable in a kinematic solution.

   \param pr The set of parameters.
   \param p The input kinematic solution point with values for the system 
            variables only.
   \param v The output kinematic solution point with values for all variables. 
            The space for this point is allocated internally.
   \param w The world.

   \return Then dimensionality of the output point.
*/
unsigned int RegenerateWorldSolutionPoint(Tparameters *pr,double *p,
					  double **v,Tworld *w);

/** 
    \brief Generates a file with the atom centers in global coordiantes.

    Generates a file with the atom centers in global coordiantes. The global coordinates
    are those given by a solution point (parameter \e pt).

    This is used only when the world represents a molecule and we want
    to store the atom (i.e., the sphere) positions into a file.
    (world where the mechanisms is formed by spheres only are considered molecules).

    The atoms centers are latter used by \ref cuikpdb2world.c "cuikpdb2world" that coordinates biological
    inforamation (pdb file) and a world. It is very important that the atoms in the world are given
    exactly in the same order as those in the pdb.

    This function assumes that the enviroment is empty (i.e., the world is fully defined by
    the links).

    NOTE: the file with the atom positions generated by this functions is only used
          to generate world from pdb files. This is somehow weird since to generate
	  the atom files we already need a world file. We proceed in way since
	  the generated world is "sync" with the pdb and then, the results fo
	  \ref cuikatlas.c "cuikatlas", \ref cuikatlascenters.c "cuikatlascenters", 
	  ... can be incorporated to the pdb (to generate new pdb's that can be analyzed with
	  any standard molecular analysis software).
    
    \param pr The set of parameters.
    \param f The file where to store the atom centers.
    \param pt The solution point.
    \param w The world with the atoms.
*/
void WorldPrintAtoms(Tparameters *pr,FILE *f,double *pt,Tworld *w);

/** 
    \brief Generates a file with the atoms grouped in rigid clusters.

    Generates files where the atoms (centers and radius) are stored grouped
    in rigid clusters. These files are not used within the \b CuikSuite,
    but only when testing the RigidCLL. We basically use the \b CuikSuite
    machinery to easily generate testing files for the RigidCLL package.
 
    This function assumes that the enviroment is empty (i.e., the world is fully defined by
    the links). Moreover, for proper operation, all links must be composed by spheres
    (atoms).

    \param pr The set of parameters.
    \param f The file where to store the atom centers.
    \param pt The solution point.
    \param w The world with the atoms.
*/
void WorldStoreRigidGroups(Tparameters *pr,FILE *f,double *pt,Tworld *w);

/** 
    \brief Jacobian of the atom position w.r.t. the variables.

    Jacobian of the atom position w.r.t. the variables. In this context we assume
    that all balls in the mechanism represent an atom. 

    This is mainly used when manipulating worlds derived form biological information.

    This Jacobian is used to transform the gradient of the energy in atom coordinates
    to a gradient in internal coordinates.

    If the world is not only formed by spheres an error is triggered.

    \param pr The set of parameters.
    \param sol The configuration.
    \param nr Number of rows of the output Jacobian.
    \param nc Number of columns of the output Jacobian.
    \param J The output matrix with the Jacobian.
    \param w The world.
*/
void WorldAtomJacobian(Tparameters *pr,double *sol,unsigned int *nr,unsigned int *nc,double ***J,Tworld *w);

/** 
    \brief Moves the mechanisms defined in a \e world information to a
          given configuration.
   
   Moves the mechanisms defined in a \e world information to a
   given configuration.	 

   Note that the box should only include ranges for the system variables.
   Therefore, the box given as a parameter is a sub-box of the box associated
   with \ref Tworld::kinCS.

   \param pr The set of parameters.
   \param pt The 3d scene where the world has been previously added 
             (see \ref PlotWorld).
   \param b The box from where to get the configuration. The configuration 
            used to plot the mechanism is defined from the center of the 
	    interval for the system variables.
	    Note that by taking the center it is not warranteed the 
	    configuration to be valid but if boxes are small enough the 
	    committed error will be small too.
   \param w The world with the mechanism to move.
*/
void MoveWorld(Tparameters *pr,Tplot3d *pt,Tbox *b,Tworld *w);

/** 
    \brief Prints the axes of the mechanism.

   Prints a point and the axis for each of the different joints in the
   mechanisms. This is latter used to generate the mechanism Jacobian.
   
   The values are all in global coordinates.

   \param pr The set of parameters.
   \param f The file where to store the information.
   \param b The box with the solution to use.
   \param w The world to query.
*/
void PrintWorldAxes(Tparameters *pr,FILE *f,Tbox *b,Tworld *w);

/** 
   \brief Prints information collected durint last collision check.

   Prints information collected durint last collision check. 

   See \ref StoreCollisionInfo for more details. 

   This function implicitly assumes that the last link
   is an abject being manipulated by the rest of links.

   \param f File where to write the collision script.
   \param fname File from where we obtained the world information. The last
                part of the filename (from the last '_' to the end) is assumed
		to be the name of the object. This name is the one used to
		call the sub-matlab scripts giving contact points and normals
		on the object.
   \param w The world.
*/
void PrintWorldCollisionInfo(FILE *f,char *fname,Tworld *w);

/** 
    \brief Moves a mechanisms to a configuration given by the degrees of 
          freedom.

   Moves a mechanisms to a configuration given by values for the different
   degrees of freedom of the joints forming the mechanisms.
   This might be a configuration not fulfilling the whole set of equations 
   (loop closures might be violated). 

   This basically generates a configuration in our formulation from the 
   degrees of freedom values and calls \ref MoveWorld.

   \param pr The set of parameters.
   \param pt The 3d scene where the world has been previously added (see 
             \ref PlotWorld).
   \param dof The array of doubles given the values for all the degrees of 
              freedom in the mechanism.
   \param w The world with the mechanism to move.
*/
void MoveWorldDOF(Tparameters *pr,Tplot3d *pt,double *dof,Tworld *w);

/** 
    \brief Transforms from degrees of freedom to cuik variables.
   
   Defines a configuration in cuik variables from a configuration given by 
   degrees of freedom.

   There is no guarantee that the ouput box fulfill all equations (it is 
   generated from a dof probably adjusted in open loop).

   \param p The set of parameters.
   \param dof The values for each of the degrees of freedom of the mechanism.
   \param sol The re-constructed solution point (including system and non-system
              variables an in the origional, non-simplified, system !!).
   \param b The solution point in form of a box. Only initialized if 'b' is not NULL.
   \param w The world with the mechanism description.

   \return The number of elements in the solution.
*/
unsigned int WorldDOF2Sol(Tparameters *p,double *dof,double **sol,Tbox *b,Tworld *w);

/** 
    \brief Transforms a sample degrees of freedom.

   Transform a configuration given in cuik variables to configuratoin given 
   in degrees of freedom.

   In some sense this is the inverse of \ref WorldDOF2Sol. Note the difference
   in what here the sample must include only system variables.

   \param p The set of parameters.
   \param sample The array with the sample to convert. This MUST include only
                 system variables.
   \param dof Space where to store the ouput. It must have as many entries
              as dof of the mechanisms (see \ref GetWorldNDOF).
   \param w the world with the mechanism description.
*/
void WorldSample2DOF(Tparameters *p,double *sample,double *dof,Tworld *w);

/** 
    \brief Produces an animation along a path.

   Produces an animation along a path. An animation is a 3d geometry
   that can be browsed with <a href="http://www.geomview.org">geomview</a>.

   Note that the boxes in the list should only include ranges for the system 
   variables.
   Therefore, the box given as a parameter is a sub-box of the box associated
   with \ref Tworld::kinCS.

   \param pr The set of parameters.
   \param pname Name for the file with the geometry to generate.
   \param axesLength Length for the axes for each link. 0 not to display them.
   \param frameDelay Extra time (in seconds) added in between frames. In the 
                     default mode animations show 10 frames per second (i.e., 
		     the frame delay is 0.1).
                     This parameter can be used to slow down animations. This 
		     is very useful when animating sets of isolated solutions: 
		     we can freeze each frame time
                     enough to inspect each solution separately.
   \param p The list of boxes with the \e frames of the animation.
   \param w The world. 
*/
void AnimateWorld(Tparameters *pr,char *pname,double axesLength,
		  double frameDelay,Tlist *p,Tworld *w);

/** 
    \brief Prints the cuiksystems derived from a world.

   Generate a  file with the cuiksystem generated from the
   world information. 

   \param p A set of parameters.
   \param fname The base name for the file names to create
   \param w The world with the cuiksystems to print.
*/
void PrintWorldCS(Tparameters *p,char *fname,Tworld *w);

/** 
    \brief Prints the world.

    Prints the world in a form that can be read by \ref InitWorldFromFile.

    Parameters artc and arg can be used to add information in the world about
    how it was generated. Use 0 and NULL to add no information.

    \param fname The file where to store the world information.
    \param argc Number of strings to be added to the world file header as comments.
    \param arg Strings to be added to the world file as comments. Right now, this is used
              to store in the command line used to create it.
    \param w The world to print.
*/
void PrintWorld(char *fname,int argc,char **arg,Tworld *w);

/** 
    \brief Destructor.

   Deletes the information stored in a world and frees the allocated memory.
   
   \param w The world to delete.
*/
void DeleteWorld(Tworld *w);

#endif
