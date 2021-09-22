#ifndef JOINTH
#define JOINTH

#include "interval.h"
#include "link.h"
#include "boolean.h"
#include "cuiksystem.h"
#include "color.h"
#include "htransform.h"
#include "eqvector.h"

#include <stdlib.h>


/** 
    \file joint.h
    \brief Definition of the Tjoint type and the associated functions.

    Definition of the Tjoint type and the associated functions.

    \sa Tjoint, joint.c.
*/

/************************************************************************************/
/** \brief  One of the possible type of joints.

     One of the possible type of joints. This is used for uninitialized joints.

    \sa Tjoint
*/
#define NO_JOINT NO_UINT

/** \brief  One of the possible type of joints.

     One of the possible type of joints. A free joint: imposes no
     constraint between two links. Used to define free flying robots.

    \sa Tjoint
*/
#define FREE_JOINT 0

/** \brief  One of the possible type of joints.

     One of the possible type of joints. A fix joint: 
     fixes the translation and the orientation of one link 
     with respect to another link
     using an homogeneous transform. 

    \sa Tjoint
*/
#define FIX_JOINT 1

/** \brief  One of the possible type of joints.

     One of the possible type of joints.  A revolute joint.

    \sa Tjoint
*/
#define REV_JOINT  2

/** \brief  One of the possible type of joints.

     One of the possible type of joints.  An universal joint.

    \sa Tjoint
*/
#define UNV_JOINT  3

/** \brief  One of the possible type of joints.

     One of the possible type of joints.  A spherical joint.

    \sa Tjoint
*/
#define SPH_JOINT  4

/** \brief  One of the possible type of joints.

     One of the possible type of joints.  The lower joint of a 
     spherical-spherical composite joint.

    \sa Tjoint
*/
#define SPH_SPH_LOW_JOINT  5

/** \brief  One of the possible type of joints.

     One of the possible type of joints.  The upper joint of a 
     spherical-spherical composite joint.

    \sa Tjoint
*/
#define SPH_SPH_UP_JOINT  6

/** \brief  One of the possible type of joints.

     The planar version of \ref SPH_SPH_LOW_JOINT

    \sa Tjoint
*/
#define REV_LOW_JOINT  7

/** \brief  One of the possible type of joints.

     The planar version of \ref SPH_SPH_UP_JOINT

    \sa Tjoint
*/
#define REV_UP_JOINT  8

/** \brief  One of the possible type of joints.

     One of the possible type of joints.  A prismatic joint.

    \sa Tjoint
*/
#define PRS_JOINT  9

/** \brief  One of the possible type of joints.

    Defines a generalized plannar joint where a point in the first link
    is constrainted to be inside a patch in the second link and the normal
    of the first link at the given point is aligned with the normal of the
    patch.

    The patch is defined as a order-one Bezier patch that is given by 4 points.
    If those for points are co-planar this joint is a plannar joint with
    a plane limited by the 4 given points.

    \sa Tjoint
*/
#define IN_PATCH_JOINT  10


/************************************************************************************/

/** 
   \brief Relation between two links.

   Constraints on the relative moments between two links.

   We store the pointers to the links related by the joint and also
   their identifiers. This is so because the identifiers are not stored
   in the links itselfs (they are the indexes of the links as stored 
   in the mechanism).

   Note that the \e .world syntax allow to define universal joints. However,
   we do not have a joint of type \e universal, since universal joints are
   two co-punctual revolute joints with orthogonal rotation axes. When
   we define a universal joint between link1 and link2, we add a \e ghost link between
   link1 and link2 with the X axis aligned with the first revolute joint of
   the universal joint (fixed w.r.t. link1) and the Y axis aligned with the second
   revolute joint of the universal joint (fixes w.r.t. link2). If we define ranges
   for the rotations of the universal joint, then the first range refers to the  angle
   between the link1 and the \e ghost link defined from the joint and the second
   angle refers to the angle between the \e ghost link and link2.

   \todo Right now only prismatic, spherical, revolute, universal 
         and spherical-spherical joints are defined.
         Although it is not urgent, we have to define more types of joints:
	 CYL_JOINT (cylindrical joint), and HEL_JOINT (helical joint).<br>
	 To define a new type of joint, we have to define a new constructor,
	 to to extend the \ref GenerateJointEquations and the \ref GenerateJointRangeEquations
	 functions. 

   \sa joint.h, joint.c.
*/
typedef struct {
  unsigned int t; /**< Type of joint: REV_JOINT (revolute joint), 
                       PRS_JOINT (prismatic joint), FREE_JOINT (free joint), etc.*/

  unsigned int id; /**< Unique identifier assigned to the joint. This is used to generate
		        unique names for the variables associated with the joint. Using the
			names of the links is informative but not enough since we can have
			several joint between the same couple of links. */

  unsigned int linkID[2]; /**< Identifiers of the links constrained by the joint.*/
  Tlink *link[2]; /**< Pointers to the links constrained by the joint.*/

  double points[6][3]; /**< In general, a joint constraints the relative motion between links
			    stablishing relations between a vector defined in the
			    first link reference frame and a vector defined in the
			    second link reference frame.<br>
			    In this case 4 points are used to define the
			    two vectors (two points in the frame of reference of the first
			    link and two points in that of the second link).<br>
			    In some cases less than four points are necessary
		            (for instance, for SPH_JOINTS only one point in each
			    reference frame is required).<br>
			    In other cases (for instance the IN_PATCH joint) 6 points
			    are necessary: two to define the point and normal in the first
			    link and 4 to define the patch in the second link. */ 

  double normals[3][3]; /**< In general, normalized version of the two vectors defined from the
			     \e points. In this case only 2 vectors are defined.<br>
			     For the \ref IN_PATCH_JOINT, normals at the corners of the patch used
			     to compute the normal at any point in the patch. In this case
			     tree vectors are defined */

  Tinterval normRange; /**< For \ref IN_PATCH_JOINT the range for the norm of the normal vector
			    to any point in the patch. Not used for other joints. */

  boolean hasLimits;   /**< TRUE if the joint has some limit constraints.*/
  boolean hasReference;/**< TRUE if a revolute joint has some reference position (only used
			    for revolute joints).*/
  void *coupled;       /**< Pointer for the joint coupled with this one. This is only not
                            NULL for some revolute joints coupled with the previous joint
			    (revolute too and both joints with limits). */

  boolean avoidLimits; /**< TRUE if the search process has to be focussed in the center
			    of the valid ranges for the joint */
  double avoidLimitsWeight; /**< If avoidLimits is TRUE, this is the strength of the
        		         limit avoidance for this joint. */
  Tinterval range;  /**< Range of valid joint values. Used only if hasLimits is TRUE.*/
  Tinterval range2; /**< For universal joints a second range is used 
		         (only if hasLimits is TRUE). */
  double offset; /**< Offset for range. Ranges are sometimes zero centered. We store the
		      offset applied to zero-center the ranges to be able to recover the
		      original ranges when necessary. */
  double offset2; /**< Offset for range2. */
  double vrange[2][3]; /**< Vectors defining the reference position for rotations,
			    spherical, and universal joints.*/

  double velocity;     /**< Maximum velocity. The same maximum velocity is used for all 
			    of the dof of the joint. */
  double acceleration; /**< Maximum acceleration. The same maximum acceleration is used 
			    for all  of the dof of the joint. */
  double effort;       /**< Maximum effort. The same maximum effort is used for all 
			    of the dof of the joint. */
  double cost;         /**< LQR cost. Cost of the deviation from the null action.
			    For joints with many degrees of freedom, the same cost is used
			    for all of them. */
  double friction;     /**< Friction. The same friction is used for all 
			    of the dof of the joint. */
  double damping;      /**< Damping. The same damping is used for all 
			    of the dof of the joint. */
  
  THTransform preT; /**< Transform used to obtain the reference frame of the second link
		         involved in the joint from the first one. In particular this matrix
		         accumulates the constant transforms to be applied before the applying
		         the joint degrees of freedom. */
  THTransform postT; /**< Transform used to obtain the reference frame of the second link
		          involved in the joint from the first one. In particular this matrix
		          accumulates the constant transforms to be applied after the applying
		          the joint degrees of freedom. */
  double maxCoord;   /**< Maximum coordinate value used in the joint. */
} Tjoint;

/** 
   \brief Constructor.

   Defines a free joint between links. A free joint is a dummy joint
   imposing no constraint between the relative movements of the links.
   It is used to see a different free flying mechanisms 
   as a single mechanism. This basically simplify the structures we
   use (we don't have to implement a multi-mechanism stucture, for instance)
   and the generation of equations from the mechanism definition can
   be easily implemented with a single ground link.

   Up to now we hardly used/tested this type of joints.

   \param id Unique identifier given to the joint.
   \param linkID1 Identifier of the first link to relate.
   \param link1 Pointer to the first link to relate.
   \param linkID2 Identifier of the second link to relate.
   \param link2 Pointer to the first link to relate.
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct LQR cost.
   \param fr Friction.
   \param da Damping.
   \param j The joint to initialize.
*/
void NewFreeJoint(unsigned int id,
		  unsigned int linkID1,Tlink *link1,
		  unsigned int linkID2,Tlink *link2,
		  double ve,double ac,double ef,double ct,double fr,double da,
		  Tjoint *j);

/** 
   \brief Constructor.

   Defines a fix joint between links. A fix joint fixes the relative
   translation and orientation between two links.
   
   Fix joints are typically used when placing the end effector of a robot
   to compute its inverse kinematics.

   \param id Unique identifier given to the joint.
   \param linkID1 Identifier of the first link to relate.
   \param link1 Pointer to the first link to relate.
   \param linkID2 Identifier of the second link to relate.
   \param link2 Pointer to the first link to relate.
   \param t Homogeneous transform defining the relative position between the two links.
   \param j The joint to initialize.
*/
void NewFixJoint(unsigned int id,
		 unsigned int linkID1,Tlink *link1,
		 unsigned int linkID2,Tlink *link2,
		 THTransform *t,
		 Tjoint *j);
/** 
    \brief Constructor.
    
    Defines a new revolute joint between two links.

    Note that we assume centered rotations, that is, if there is any
    limit in the rotation it is always in the for of a symmetric interval
    [-range,range]. This is completely general (by defining appropriate
    reference vectors  the rotation range can be made symmetric around 0
    and it helps when defining constraints.

   \param id Unique identifier given to the joint.
   \param r Type of represention used. Value for \ref CT_REPRESENTATION.
   \param linkID1 Identifier of the first link to relate.
   \param link1 Pointer to the first link to relate.
   \param linkID2 Identifier of the second link to relate.
   \param link2 Pointer to the first link to relate.
   \param points Four points defining the rotation axis. The first two points
                 define the rotation axis in the reference frame of link1 and
		 the two other points are the same vector in the frame of
		 reference of link2.
   \param hasLimits TRUE if the joint to create include limits for the rotation
                    movement.
   \param hasReference TRUE if the joint to create include a reference for the rotation
                       movement, i.e., two vectors which must coincide when the
		       revolute angle is 0.
   \param range If hasLimits is TRUE, this is the valid range for the rotation 
                (in radiants).
   \param rPoints If hasLimits is TRUE, two points that define the reference
                  position (i.e., the zero position) for the rotation. Actually
		  points[0]->rPoints[0] define one vector in link1 and 
		  points[2]->rPoints[1] another vector in link2 that must coincide
		  when the angle is 0. In other works, the angle between these vectors
		  is the angle between the links and we only allow it to move
		  from \e -range, to \e range. <br>
		  The vector  points[0]->rPoints[0] must be orthogonal to  points[0]->points[1]
		  and the same applies to points[2]->rPoints[1] and points[2]->points[3].
   \param avoidLimits TRUE if the search process has to be focussed in the center
		      of the valid ranges for the joint. This flag in only considered if
		      hasLimits is true.
   \param avoidLimitsWeight If avoidLimits is TRUE, this is the strength of the
	 	            limit avoidance for this joint. 
   \param coupled  Pointer for the joint coupled with this one. This is only not
                   NULL for some revolute joints coupled with the previous joint
		   (revolute too and both joints with limits).
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct LQR cost.
   \param fr Friction.
   \param da Damping.
   \param j The joint to initialize.
*/
void NewRevoluteJoint(unsigned int id,unsigned int r,
		      unsigned int linkID1,Tlink *link1,
		      unsigned int linkID2,Tlink *link2,
		      double **points,
		      boolean hasLimits,boolean hasReference,
		      Tinterval *range,double **rPoints,
		      boolean avoidLimits,double avoidLimitsWeight,
		      Tjoint *coupled,
		      double ve,double ac,double ef,double ct,double fr,double da,
		      Tjoint *j);
/** 
    \brief Constructor. 
    
    Defines a new universal joint between two links.

   \param id Unique identifier given to the joint. 
   \param r Type of represention used. Value for \ref CT_REPRESENTATION.
   \param linkID1 Identifier of the first link to relate. 
   \param link1 Pointer to the first link to relate. 
   \param linkID2 Identifier of the second link to relate. 
   \param link2 Pointer to the first link to relate. 
   \param points Four points defining the two rotation axes. The first two points 
                 define the rotation axis in the reference frame of link1 and 
		 the second pair of points point is the same point in the frame of 
		 reference of link2. The constraint imposed by the universal joint
		 forces these two vectors to be orthogonal.
   \param hasLimits TRUE if the joint to create include limits.
   \param hasReference TRUE if the joint to create include a reference for the rotation
                       movement, i.e., two vectors which must coincide when the
		       revolute angle is 0.
   \param range1 If hasLimits is TRUE, this is the valid range for the first rotation 
                 (in radiants).
   \param range2 If hasLimits is TRUE, this is the valid range for the second rotation 
                 (in radiants).
   \param rPoints points[0]->rPoints[0] define the vector in link1 that must
                  coincide with vector points[2]->points[3] when the first rotation
		  is zero.<br>
		  points[2]->rPoints[1] define the vector in link2 that must
                  coincide with vector points[0]->points[1] when the second rotation
		  is zero.
   \param avoidLimits TRUE if the search process has to be focussed in the center
		      of the valid ranges for the joint. This flag in only considered if
		      hasLimits is true.
   \param avoidLimitsWeight If avoidLimits is TRUE, this is the strength of the
	 	            limit avoidance for this joint. 
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct LQR cost.
   \param fr Friction.
   \param da Damping.
   \param j The joint to initialize. 
*/
void NewUniversalJoint(unsigned int id,unsigned int r,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       boolean hasLimits,boolean hasReference,
		       Tinterval *range1,Tinterval *range2,double **rPoints,
		       boolean avoidLimits,double avoidLimitsWeight,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j);

/** 
    \brief Constructor.
    
    Defines a new spherical joint between two links.

    The limits for a spherical joint are defined symmetrically around an axis
    rigidly linked to the first link.

   \param id Unique identifier given to the joint.
   \param linkID1 Identifier of the first link to relate.
   \param link1 Pointer to the first link to relate.
   \param linkID2 Identifier of the second link to relate.
   \param link2 Pointer to the first link to relate.
   \param points Two points defining the rotation point. The first point
                 define the rotation point in the reference frame of link1 and
		 the second point is the same point in the frame of
		 reference of link2.
   \param hasLimits TRUE if the joint to create include limits.
   \param range If hasLimits is TRUE, the valid value of rotation angle between
                the two links is <em> [-range,range] </em>.
   \param rPoints points[0]->rPoints[0] and points[2]->rPoints[1] define the
                  vectors in link1 and link2 respectively that must coincide
		  when the angle between links is 0.  In other works, the angle 
		  between these vectors
		  is the angle between the links and we only allow it to move
		  from \e -range, to \e range.
   \param avoidLimits TRUE if the search process has to be focussed in the center
		      of the valid ranges for the joint. This flag in only considered if
		      hasLimits is true.
   \param avoidLimitsWeight If avoidLimits is TRUE, this is the strength of the
	 	            limit avoidance for this joint.
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct LQR cost.
   \param fr Friction.
   \param da Damping.
   \param j The joint to initialize.
*/
void NewSphericalJoint(unsigned int id,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       boolean hasLimits,double range,double **rPoints,
		       boolean avoidLimits,double avoidLimitsWeight,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j);

/** 
   \brief Constructor.
   
   Defines a new prismatic joint between two links.

   Note that prismatic joints are always limited.

   IMPORTANT: We assume that reference frames for the two links
   connected by a prismatic joint are aligned (the XYZ axis are parallel
   and just displaced).
   
   \param id Unique identifier given to the joint.
   \param linkID1 Identifier of the first link to relate.
   \param link1 Pointer to the first link to relate.
   \param linkID2 Identifier of the second link to relate.
   \param link2 Pointer to the first link to relate.
   \param points Four points defining the sliding axis. The first two points
                 define the sliding axis in the reference frame of link1 and
		 the two other points are the same vector in the frame of
		 reference of link2.
   \param range Valid range of values for the prismatic joint.
   \param avoidLimits TRUE if the search process has to be focussed in the center
		      of the valid ranges for the joint. This flag in only considered if
		      hasLimits is true.
   \param avoidLimitsWeight If avoidLimits is TRUE, this is the strength of the
	 	            limit avoidance for this joint.
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct LQR cost.
   \param fr Friction.
   \param da Damping.
   \param j The joint to intialize.
*/
void NewPrismaticJoint(unsigned int id,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       Tinterval *range,
		       boolean avoidLimits,double avoidLimitsWeight,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j);
/** 
    \brief Constructor.
    
    Defines the lower part of a spherical-spherical composite joint 
    between two links.

    NOTE: sph_sph_low joints are used to connect legs. The rotation
    about the leg axis is not relevant and thus, these joints can
    be seen as providing only two dof. However, when using a 
    joint-based representation the third dof can not be ignored.
    This is so because when using a link-based formulation the
    rotation is fixed (arbitrarily but fixed) and the third 
    dof is necessary to perfectly match the trnsformation
    when translating from joints to links and the reverse.

    \param id Unique identifier given to the joint.
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param points Two points defining the end points of the  spherical-spherical 
                  joint. The first point in given in the first link and the
		  second in the second link.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct LQR cost.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize.
*/
void NewSphSphLowJoint(unsigned int id,
		       unsigned int linkID1,Tlink *link1,
		       unsigned int linkID2,Tlink *link2,
		       double **points,
		       double ve,double ac,double ef,double ct,double fr,double da,
		       Tjoint *j);
/** 
    \brief Constructor.
   
    Defines the upper part of a spherical-spherical composite joint 
    between two links.

    \param id Unique identifier given to the joint.
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param points Two points defining the end points of the  spherical-spherical 
                  joint. The first point in given in the first link and the
		  second in the second link.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct LQR cost.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize.
*/
void NewSphSphUpJoint(unsigned int id,
		      unsigned int linkID1,Tlink *link1,
		      unsigned int linkID2,Tlink *link2,
		      double **points,
		      double ve,double ac,double ef,double ct,double fr,double da,
		      Tjoint *j);

/** 
    \brief Constructor.
    
    Defines the lower part of a spherical-spherical planar composite joint 
    between two links. The rotation is defined in the Z axis (the
    mechanism is limited to the XY plane).

    The planar version of \ref NewSphSphLowJoint.

    \param id Unique identifier given to the joint.
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param points Two points defining the end points of the spherical-spherical 
                  joint. The first point in given in the first link and the
		  second in the second link.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct LQR cost.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize.
*/
void NewRevLowJoint(unsigned int id,
		    unsigned int linkID1,Tlink *link1,
		    unsigned int linkID2,Tlink *link2,
		    double **points,
		    double ve,double ac,double ef,double ct,double fr,double da,
		    Tjoint *j);

/** 
    \brief Constructor.
   
    Defines the upper part of a spherical-spherical planar composite joint 
    between two links. The rotation is defined in the Z axis (the
    mechanism is limited to the XY plane).

    The planar version of \ref NewSphSphUpJoint

    \param id Unique identifier given to the joint.
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param points Two points defining the end points of the  spherical-spherical 
                  joint. The first point in given in the first link and the
		  second in the second link.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct LQR cost.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize.
*/
void NewRevUpJoint(unsigned int id,
		   unsigned int linkID1,Tlink *link1,
		   unsigned int linkID2,Tlink *link2,
		   double **points,
		   double ve,double ac,double ef,double ct,double fr,double da,
		   Tjoint *j);

/**  
    \brief Constructor.
    
    Defines the lower part of a spherical-prismatic-spherical composite joint between two links.

    NOTE: sph_prs_sph_low joints are used to connect legs. The rotation
    about the leg axis is not relevant and thus, these joints can
    be seen as providing only two dof. However, when using a 
    joint-based representation the third dof can not be ignored.
    This is so because when using a link-based formulation the
    rotation is fixed (arbitrarily but fixed) and the third 
    dof is necessary to perfectly match the trnsformation
    when translating from joints to links and the reverse.

    \param id Unique identifier given to the joint.
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param points Two points defining the end points of the  spherical-spherical 
                  joint. The first point in given in the first link and the
		  second in the second link.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct LQR cost.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize.
*/
void NewSphPrsSphLowJoint(unsigned int id,
			  unsigned int linkID1,Tlink *link1,
			  unsigned int linkID2,Tlink *link2,
			  double **points,
			  double ve,double ac,double ef,double ct,double fr,double da,
			  Tjoint *j);

/** 
    \brief Constructor.
    
    Defines the upper part of a spherical-spherical composite joint between two links.

    \param id Unique identifier given to the joint.
    \param linkID1 Identifier of the first link to relate.
    \param link1 Pointer to the first link to relate.
    \param linkID2 Identifier of the second link to relate.
    \param link2 Pointer to the first link to relate.
    \param points Two points defining the end points of the  spherical-spherical 
                  joint. The first point in given in the first link and the
		  second in the second link.
    \param ve Max velocity.
    \param ac Max acceleration.
    \param ef Max effort.
    \param ct LQR cost.
    \param fr Friction.
    \param da Damping.
    \param j The joint to initialize.
*/
void NewSphPrsSphUpJoint(unsigned int id,
			 unsigned int linkID1,Tlink *link1,
			 unsigned int linkID2,Tlink *link2,
			 double **points,
			 double ve,double ac,double ef,double ct,double fr,double da,
			 Tjoint *j);

/** 
    \brief Constructor.
    
    Defines a new in-patch joint between two links. An in-patch joint is 
    a generalization of a planar joint where the plane is replaced by
    a order one Bezier patch. This patch is defined by 4 points. When
    the four points are coplanar this joint is a planar joint.

    This type of joints are basically used to define contact between
    links.


   \param id Unique identifier given to the joint.
   \param linkID1 Identifier of the first link to relate.
   \param link1 Pointer to the first link to relate.
   \param linkID2 Identifier of the second link to relate.
   \param link2 Pointer to the first link to relate.
   \param points A point and a normal vector on the first link. This joint
                 forces the point to be in the patch and the normal vector
                 to be aligned with that of the patch at the contact point.
   \param patch Four points defining a first-order Bezier patch in the
                second link.
   \param avoidLimits TRUE if the search process has to be focussed in the center
		      of the valid ranges for the joint. This flag in only considered if
		      hasLimits is true.
   \param avoidLimitsWeight If avoidLimits is TRUE, this is the strength of the
	 	            limit avoidance for this joint.
   \param ve Max velocity.
   \param ac Max acceleration.
   \param ef Max effort.
   \param ct LQR cost. 
   \param fr Friction.
   \param da Damping.
   \param j The joint to initialize.
*/
void NewInPatchJoint(unsigned int id,
		     unsigned int linkID1,Tlink *link1,
		     unsigned int linkID2,Tlink *link2,
		     double **points,
		     double **patch,
		     boolean avoidLimits,double avoidLimitsWeight,
		     double ve,double ac,double ef,double ct,double fr,double da,
		     Tjoint *j);

/** 
   \brief Copy constructor.
   
   Defines a joint structure copying data from anther joint.

   \param j_dst The joint to create.
   \param j_src The joint from where to copy.
*/
void CopyJoint(Tjoint *j_dst,Tjoint *j_src);

/** 
   \brief Gets the joint type.
   
   Gets the joint type.

   \param j The joint to query.

   \return The joint type.
*/
unsigned int GetJointType(Tjoint *j);

/** 
   \brief Gets the maximum coordinate.
   
   Gets the maximum coordinate used in the joint definition
   (eigher in X, Y or Z).

   \param j The joint to query.

   \return The maximum coordiante.
*/
double GetJointMaxCoordinate(Tjoint *j);


/** 
   \brief Gets the joint identifier.
   
   Gets the joint identifier (given to the joint when created).

   \param j The joint to query.

   \return The joint identifier.
*/
unsigned int GetJointID(Tjoint *j);

/** 
   \brief Gets the identifier of the first link involved in the joint.

   Gets the identifier of the first link involved in the joint.

   \param j The joint to query.

   \return The identifier of the first link involved in the joint.
*/
unsigned int JointFromID(Tjoint *j);

/** 
   \brief Gets a pointer to the first link involved in the joint.

   Gets a pointer to the first link involved in the joint.

   \param j The joint to query.

   \return The pointer to the first link involved in the joint.
*/
Tlink *JointFrom(Tjoint *j);

/** 
   \brief Gets the identifier of the second link involved in the joint.

   Gets the identifier of the second link involved in the joint.

   \param j The joint to query.

   \return The identifier of the second link involved in the joint.
*/
unsigned int JointToID(Tjoint *j);


/** 
   \brief Gets a pointer to the second link involved in the joint.

   Gets a pointer to the second link involved in the joint.

   \param j The joint to query.

   \return The pointer to the second link involved in the joint.
*/
Tlink *JointTo(Tjoint *j);

/** 
   \brief Returns a string identifying the joint.

   Returns a string identifying the type of joint and the connected
   links. 
   This is basically used for interface.

   \param name The joint name. The space for this string is allocated
               inside this function but must be deallocated externally.
   \param j The joint to query.
*/
void GetJointName(char **name,Tjoint *j);

/** 
    \brief Label for a specific dof of a joint.

    Returns a label that uniquely identify a given dof in a joint.
    If the joint only has a single dof, the label is NULL (i.e. the 
    name of the joint is enough to identify the dof).

    This is used to create interfaces.

    \param ndof Number of degree of freedom to identify.
    \param name The label to create. The space is allocated in the
                function and must be deallocted by the caller.
    \param j The joint to query.
*/
void GetJointDOFName(unsigned int ndof,char **name,Tjoint *j);

/** 
   \brief Gets one of the points defining the rotation/sliding
          axis for the joint.

   Gets one of the points defining the rotation/sliding
   axis for the joint.

   \param link 0 if we want to get the point in the first link reference
               frame and 1 if we want to get it in the frame of the second link.
   \param point 0/1 according if we want to get the origin of the axis
                or the end.
   \param p An array where to store the requested point.
   \param j The joint to query.
*/
void GetJointPoint(unsigned int link,unsigned int point,double *p,Tjoint *j);

/** 
   \brief Checks if a joint has limits.

    Checks if a joint has limits.

   \param j The joint to query.

   \return TRUE if there joint jas limits.
*/
boolean LimitedJoint(Tjoint *j);


/** 
   \brief Checks the limits of a joint.

   Checks the limits of a joint. 

   \param j The joint to query.

   \return A pointer to the interval with the limits of the joint. For joints
           with no limits, this interval will be non-meaningful.
*/
Tinterval *GetJointRange(Tjoint *j);

/** 
   \brief Checks the second limit of a universal joint.

   Checks the second limit of a universal joint. 

   Only universal joints have a second range.

   \param j The joint to query.

   \return A pointer to the interval with the limits of the joint. For joints
           with no limits, this interval will be non-meaningful.
*/
Tinterval *GetJointSecondRange(Tjoint *j);


/** 
   \brief Returns one of the ranges of the joint.

   Returns the ranges for one of the degrees of freedom of the joint.

   \param nr Number of degree of freedom.
   \param mt Maximum value for non-constrained translations.
   \param r Output range.
   \param j The joint to query.
*/
void GetJointRangeN(unsigned int nr,double mt,Tinterval *r,Tjoint *j);

/** 
   \brief Returns the topology of one of the ranges of the joint.

   Returns the topology of one of the degrees of freedom of the joint.

   \param nr Number of degree of freedom.
   \param j The joint to query.

   \return The topology (\ref TOPOLOGY_R or \ref TOPOLOGY_S).
*/
unsigned int GetJointRangeTopology(unsigned int nr,Tjoint *j);

/** 
   \brief Returns the identifier of the joint coupled with the query joint.

   Returns the identifier of the joint coupled with the query joint.

   Note that up to now we have a very  limited implementation of the 
   coupling between joints: Only revolute joints (with limits) can be
   coupled and always with a 1 to 1 relation.

   If we have a pair of joints coupled (j1,j2) with j1 having a lower
   identifier than j2 (i.e., appearing before in the mechanism definition),
   this function only returns something different from \ref NO_UINT
   for j2. In other words, the function only identifies the coupled 
   but not the original joint.

   \param j The joint to query.

   \return The identifier of the coupled joint of \ref NO_UINT if the
           joint is not coupled.
*/
unsigned int CoupledWith(Tjoint *j);

/** 
   \brief Computes the degrees of freedom allowed by a given joint.

   Computes the degrees of freedom allowed by a given joint. The degrees
   of freedom constrained by the joint are 6-the allowed ones (i.e., the
   returned by this function.

   \param j The joint to query.

   \return The degrees of freedom allowed by the joint.
*/
unsigned int GetJointDOF(Tjoint *j);

/** 
    \brief Maximum velocity.

    Returns the maximum velocity of the joint.
    
    \param j The joint to query.
    
    \return The maximum velocity of the joint.
*/
double GetJointVelocity(Tjoint *j);

/** 
    \brief Maximum acceleration.

    Returns the maximum acceleration of the joint.
    
    \param j The joint to query.
    
    \return The maximum acceleration of the joint.
*/
double GetJointAcceleration(Tjoint *j);

/** 
    \brief Maximum effort.

    Returns the maximum effort of the joint.
    
    \param j The joint to query.
    
    \return The maximum effort of the joint.
*/
double GetJointEffort(Tjoint *j);

/** 
    \brief The (LQR) cost.

    Returns (LQR) cost of the joint.
    
    \param j The joint to query.
    
    \return The (LQR) cost.
*/
double GetJointCost(Tjoint *j);

/** 
    \brief Identifies acctuated joints.

    Identifies acctuated joints. Right now the actuated
    joints are those with a limited joint effort.

    \param j The joint to query.
    
    \return TRUE if the joint is actuated.
*/
boolean ActuatedJoint(Tjoint *j);

/** 
    \brief Joint friction.

    Returns the friction of the joint.
    
    \param j The joint to query.
    
    \return The friction of the joint.
*/
double GetJointFriction(Tjoint *j);

/** 
    \brief Joint damping.

    Returns the damping of the joint.
    
    \param j The joint to query.
    
    \return The damping of the joint.
*/
double GetJointDamping(Tjoint *j);

/** 
    \brief Joint frame.

    Returns a transfrom from the reference frame of the parent
    link to a reference frame on the joint.

    \param j The joint to query.

    \return The transform.
*/
THTransform *GetJointFrame(Tjoint *j);

/** 
    \brief Pre-joint transform.

    Returns a transfrom from the reference frame of the parent
    link to a reference frame on the joint.

    This is just the same as \ref GetJointFrame

    \param s The orientation of the joint. If <0 the joint
             is reversed (the roles of parent and child are swaped).
    \param t Space where to store the output transform.
    \param j The joint to query.
*/
void GetJointPreT(signed int s,THTransform *t,Tjoint *j);

/** 
    \brief Post-joint transform.

    Returns a transfrom from the joint frame to the
    reference frame of the child link.

    \param s The orientation of the joint. If <0 the joint
             is reversed (the roles of parent and child are swaped).
    \param t Space where to store the output transform.
    \param j The joint to query.
*/
void GetJointPostT(signed int s,THTransform *t,Tjoint *j);


/** 
   \brief Modifies the cuik system to detect end range singularities.

   Workspace boundaries are detected as singularities. Here we introduce
   some changes in the range variables so that we force a singularity
   in the extremes of the ranges for the joints.
   
   \param p A set of parameters. They include, for instance the dummification
            level.
   \param cs The cuiksystem where to add the variables and equations.
   \param j The joint from where to generate the variables and equations.
*/
void GenerateJointRangeSingularityEquations(Tparameters *p,TCuikSystem *cs,Tjoint *j);

/** 
   \brief Generate the constraints related with the joint limits.

   Adds to the given cuiksystem the variables and equations necessary to deal
   with the joint ranges. For prismatic joints this is one variable and its
   associated range. For revolute joints, we have to define two vectors
   one associted with link1 and the other link2 and define the scalar and
   vector products (this produces a third vector aligned with the
   rotation axis) to get the cosinus/sinus of the rotated angle that are
   then bounded given the range for the allowed rotation between the two links.

   \param p A set of parameters. They include, for instance the dummification
            level.
   \param cs The cuiksystem where to add the variables and equations.
   \param j The joint from where to generate the variables and equations.
*/
void GenerateJointRangeEquations(Tparameters *p,TCuikSystem *cs,Tjoint *j);


/** 
   \brief Generate the constraints of a joint in a sequence.

   Adds to the given equations the constraints of a joint

   Before using this method, the variables and equations for individual
   joints have to be generated (using \ref GenerateJointEquations).
   
   When considered in a sequence, joints define a sum of vectors taking
   from the origin of the frame of reference of one link to the origin
   of the frame of reference for the next link. When these sums are taken
   on a closed branch, we get the loop equations. 

   Since links and joints are defined in 3D, summing vectors defined on links 
   and joints define 3 equations, one for X, one for Y, and another for Z.

   \param p The set of parameters.
   \param s Orientation of the joint in the sequence (1 for positive and -1 for
            negative).
   \param cs The cuiksystem where the joint variables are defined.
   \param eq Three equations (X, Y, and Z) where to add the joint constraints.
   \param j The joint from where to generate the variables and equations.
*/
void GenerateJointEquationsInBranch(Tparameters *p,double s,TCuikSystem *cs,
				    Tequation *eq,Tjoint *j);

/** 
   \brief Add the force terms derived from a given joint.

   In tensegrity systems the forces exerced by the joints
   coincident in a given link should be balanced.

   Only STRUT, BAR, and CABLE joints can be used in tenegrities.
   STRUTS and BARS are compressed and CABLEs are in tension.
   The sum of compressions and tensions should vanish at each
   link (i.e. node).

   \param pr The set of parameters.
   \param linkID The link in process.
   \param cs The CuikSystem where the joint variables are defined.
   \param eq The equations to extend.
   \param j The joint to process.
*/
void JointForceEquation(Tparameters *pr,unsigned int linkID,TCuikSystem *cs,
			Tequation *eq,Tjoint *j);

/** 
   \brief Generate the constraints related with the joint.

   Adds to the given cuiksystem the variables and equations necessary to deal
   with the joint. Intutively, we have to add equations so that the
   revolute/sliding axis is the same as view from link1 and from link2.

   \param p A set of parameters. They include, for instance the dummification
            level.
   \param maxCoord The maximum value for the variables in the system.
   \param cs The cuiksystem where to add the variables and equations.
   \param j The joint from where to generate the variables and equations.
*/
void GenerateJointEquations(Tparameters *p,double maxCoord,
			    TCuikSystem *cs,Tjoint *j);

/** 
  \brief Computes the values for the dummy variables used in the joint equations.

  Solution points only include values for the system variables (and secondary). However,
  in some formulations, the frame joint equations use not only system/secondary variables, 
  but, for instance, dummy variable too.
  This function computes the values for the joint-related non-basis variables form
  the basic ones for a given joint.
  
  Currently only the \ref IN_PATCH_JOINT uses dummy variables but this can change
  in the future.

  \param p The set of parameters.
  \param cs The cuik system on which the boxes are defiend. It is used to, given
            the name of the variables corresponding the reference frame of the
	    given link, retrive its numerical identifiers, i.e., the
	    number of range of the \e box to use to instantiate each variable.
  \param sol The solution point with the values for the system variables.
             At the end of the function, this vector also has values for
  \param j The joint.
*/
void RegenerateJointSolution(Tparameters *p,TCuikSystem *cs,double *sol,Tjoint *j);

/** 
  \brief Computes the values for the dummy variables used in the joint equations.

  This is the same as \ref RegenerateJointSolution but working on solution boxes
  instead of on solution points (i.e. it is interval-based instead of
  floating point based)
  
  \param p The set of parameters.
  \param cs The cuik system on which the boxes are defiend. It is used to, given
            the name of the variables corresponding the reference frame of the
	    given link, retrive its numerical identifiers, i.e., the
	    number of range of the \e box to use to instantiate each variable.
  \param b The solution box with the values for the system variables.
           At the end of the function, this box also has values for dummy ones.
  \param j The joint.
*/
void RegenerateJointBox(Tparameters *p,TCuikSystem *cs,Tbox *b,Tjoint *j);

/** 
   \brief Generates a solution point from degrees of freedom.

   Generates the joint related variables in a solution from the homogeneous transforms of 
   the two links involved in the joint and the values of the degrees of freedom for this
   joint.

   This is part of the mechanism to transform from dof information to a solution point in  the
   cuik form (so that in can be plotted, etc).

   This is transforms2samples, but using the dofs to facilitate the computations. Actually
   the dofs could be computed from the transforms using \ref GetJointTransform but having
   them facilitates the computation (see \ref GetLinkTransformsFromSolution for the inverse
   operation, i.e samples2transforms).
   
   Since the dofs are finally (marginally) used, this can also be seen as dof2samples 
   (see \ref GetJointDOFValues for the inverse).
   The rest of the dof2samples is implemented in \ref GenerateLinkSolution.   

   \param p The parameter set.
   \param dof Values for the degrees of freedom of this joint.
   \param t1 Homogenous transform given the pose of the first link in the joint.
   \param t2 Homogenous transform given the pose of the second link in the joint.
   \param cs The cuik system to retrive the identifier of the variables for the joint.
   \param sol Solution vector where to store the output values.
   \param j The joint.
*/
void GenerateJointSolution(Tparameters *p,double *dof,
			   THTransform *t1,THTransform *t2,
			   TCuikSystem *cs,double *sol,Tjoint *j);


/** 
   \brief Computes the elementary transform induced by the joint.

   Computes the homogeneous trasform at a joint, without the prev/post
   transforms, i.e., the transform of the degrees of freedom at the joint.

   Note that the s and vj for IN_PATCH joints are not correctly computed.
   If used with this kind of joints, and error is generated.

   \param dof Values for the DOF of the joint.
   \param vdof Velocity in the DOf of the joint.
   \param t The output transform.
   \param it The inverse of \e t. 
   \param s Spatial algebra matrix indicating the instantaneous velocity axis
            in each degree of freedom (size 6 x dof). 
   \param vj Spatial algebra vector with the velocity along each axis.
   \param j The joint.
*/
void GetJointBasicTransform(double *dof,double *vdof,THTransform *t,THTransform *it,double *s,double *vj,Tjoint *j);
  
/** 
   \brief Computes the transform induced by the joint.

   Computes the homogeneous trasform taking from the first link involved in the
   joint to the second link, considering a given value for the degrees of freedom
   of the joint.

   This is the dof2transforms (see \ref GetJointDOFValues for the inverse).

   \param dof Values for the DOF of the joint.
   \param t The output transform.
   \param j The joint.
*/
void GetJointTransform(double *dof,THTransform *t,Tjoint *j);

/** 
   \brief Recovers the joint DOFs from the absolute poses of the links.

   Recovers the joint DOFs given the poses of the two links connected
   by the joint.

   This function recovers the joint parameters such that
   t2=t1*T where T is the transform sequence resulting from 
   \ref GetJointTransSeq.

   This is the transforms2dof (the inverse of \ref GetJointTransform)

   Since the transforms are computed from samples, this is also
   samples2dof, i.e., the inverse of \ref GenerateJointSolution +
   \ref GenerateLinkSolution. Note that dofs are only associated
   with joints and, thus there is no need for a  GetLinkDOFValues
   to complete the inverse.

   \param p The set of parameters.
   \param t1 The transform giving the absolute pose of the first link
             involved in the joint.
   \param t2 The transform giving the absolute pose of the second link
             involved in the joint.
   \param dof Space where to store the computed values.
   \param j The joint to query.
*/
void GetJointDOFValues(Tparameters *p,THTransform *t1,THTransform *t2,double *dof,
		       Tjoint *j);


/** 
   \brief Build the sequence of transforms passing through the joint.

   Build the sequence of transforms taking from one link to the next via
   the joint.

   \param p The set of parameters.
   \param cs The cuiksysem on which the dof variables are defined.
   \param ts The resulting sequence of transforms.
   \param j The joint.
*/
void GetJointTransSeq(Tparameters *p,TCuikSystem *cs,TTransSeq *ts,Tjoint *j);


/** 
   \brief Prints the joint axis in world coordinates.

   Print a point and a vector for the joint axis. This is latter used to generate
   the Jacobian of the mechanism at a given point.

   \param p The set of parameters.
   \param f The file where to store the data. 
   \param cs  The cuik system on which the boxes are defiend. It is used to, given
             the name of the variables corresponding the reference frame of the
	     given link, retrive its numerical identifiers, i.e., the
	     number of range of the \e box to use to instantiate each variable.
   \param sol The solution point. Only values for system variables are used.
   \param r Array with the translation from the ground link to
            each link.
   \param j The joint to query.
*/
void PrintJointAxes(Tparameters *p,FILE *f,TCuikSystem *cs,double *sol,
		    double *r,Tjoint *j);

/** 
   \brief Stores the joint information into a file.

   Stores the joint information into a file in the format 
   valid to be read by \ref InitWorldFromFile.
   
   \param f The file where to store the information.
   \param j The joint to print.
*/
void PrintJoint(FILE *f,Tjoint *j);

/** 
   \brief Destructor.
   
    Deletes the information stored in a joint and frees the allocated memory.

   \param j The joint to delete.
*/
void DeleteJoint(Tjoint *j);

#endif
