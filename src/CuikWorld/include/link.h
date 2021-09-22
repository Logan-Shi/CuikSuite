#ifndef LINKH
#define LINKH

#include "vector.h"
#include "interval.h"
#include "equation.h"
#include "cuiksystem.h"
#include "box.h"
#include "polyhedron.h"
#include "plot3d.h"
#include "color.h"
#include "htransform.h"
#include "parameters.h"

#include <stdlib.h>

/** 
    \file link.h
    \brief Definition of the Tlink type and the associated functions.

    Definition of the Tlink type and the associated functions.

    \sa Tlink, link.c.
*/

/** 
    \brief Redundancy in the generated equations.

    When \ref CT_REPRESENTATION is FLINKS, we can generate some redundant 
    equations regarding the orthonormality
    of the three coordinates axis.
    By setting this constant to 0 these redundancy is avoided.

*/     
#define ROT_REDUNDANCY 0

/************************************************************************************/
/** \brief Initial room for shapes in a link. 

    Initial room for shapes in a link. Each shape is a convex
    polyhedron. It will be enlarged if necessary.

    \sa Tlink, Tpolyhedron.
*/
#define INIT_NUM_SHAPES 2

/****************************************************************************/
/** \brief  Red component of the default color for links.

    Red component of the default color for links.

    \sa Tplot3d
*/
#define DLC_R 0.5

/** \brief  Green component of the default color for links.

    Green component of the default color for links.

    \sa Tplot3d
*/
#define DLC_G 0.5

/** \brief  Blue component of the default color for links.

    Blue component of the default color for links.

    \sa Tplot3d
*/
#define DLC_B 0

/** \brief A full rotation link.

    A link where the full pose is relevant.
*/
#define LINK_FullRot 0

/** \brief An axis X link.

    A link where only the X axis is relevant (the actual pose of the
    Y and Z axis is not relevant).
    This is used, for instance, in composite joints (sph_sph,
    sph_prs_sph, strut, bar, cables).

    Irrespectively of the representation, axis-X links are
    represented by a single vector since this is the simpler
    possible representation.
*/
#define LINK_AxisX 1

/** \brief A deformable link.

    A link of type LINK_AxisX that can elongate along the X axis.
*/
#define LINK_DeformX 2

/** \brief A prismatic link.

    A link of type LINK_AxisX that can elongate along the X axis,
    but in a prismatic way (without streching).
*/
#define LINK_PrismaticX 3

/** \brief A no rotation link.

    A link where the rotation is not relevant.
    This is the case, for instance, of the links appearing in
    tensegrity structures.
*/
#define LINK_NoRot 4

/** \brief A connection link.

    This is a particular type of link which is not included in the kinematic
    tree and whose pose is not directly included in the configuration, but
    deduced when the pose of other links is fixed. 

    Rigth now links of this class include cables and springs (and possibly legs)
    added between porticular points of some other links, whose pose
    can be directly deduced from the configuration.

    This class of links can be seen as a \ref LINK_DeformX link, but
    the deformation parameters and the parameters of the joints around the
    link are not included in the configuration.

    Right not connection links are only used for representation and collision
    detection, but they do not impose any kink of constraint, i.e., they are
    of variable lenght. Imposing a fixed length would imply to add equations
    to the problem. Such equations would involve the rotation/translation
    of the connected links and this would result in complex expressions which
    we can not generate at this point. In non-DOF representations they require
    the explicit representaiton of rotations (which are long expression 
    depending on the kinematic chains). In DOF representations they would
    require the matrix x vector product (which leads to 3 equations), which
    is not implemented yet. Note that the matrix in this case is actually
    a product of several matrices.
    
    \todo Automatically generate constraints from connection links (only
          for those with fixed length).

    \todo Connection links have no force model. If their length is variable
          we can add a linear force model, for instance. The problem is that
	  the length is not direclty available and, thus, this force
	  must be computed from upper levels (or at least the lenght must
	  be provided).
*/
#define LINK_Connect 5

/************************************************************************************/

/** 
    \brief One of the possible force models.

    Force model used for links that do not support/exert compression/tension.
    This is the force model we use more frequently since non-null forces
    are only used in tensegrities.
*/
#define NO_FORCE     0

/** 
    \brief One of the possible force models.

    Force model used for links that can support/exert compression/tension
    but the resulting force is unrelated with the link length.
    This is used, for instance, for tensegrity elements with
    constant length (e.g. struts, bars or fixed length cables) 
    that can apply some force.
    If we use a linear model for this case, the have to introduce
    another variable (the rest length or the stitffness) that will
    vary as the force varies. This extra variable is actually
    useless.
    Note that introducing both the rest length and the stiffness
    will introduce a fake degree of freedom.
*/
#define VAR_FORCE    1

/** 
    \brief One of the possible force models.

    Force model used some of the tensegrity links such as variable
    length cables or springs.
    In this model the compression/tension is computed as
        - f=k(l-r) 
	.
    Where 'f' is the compression/tension force, 'k' is the stiffness
    constant, 'l' is the link length, and 'r' is the rest length.

    This model is basically used for elements in tension, which
    are the ones that typically vary in length.

    Note that these are the only links contributing to the
    potential energy of the tensegrity (see \ref LinkPotentialEnergy).
*/
#define LINEAR_FORCE 2

/************************************************************************************/

/** 
   \brief One of the types of connection links.

   A cable between two links.
*/
#define C_CABLE 0

/** 
   \brief One of the types of connection links.

   A spring between two links.
*/
#define C_SPRING 1

/** 
   \brief One of the types of connection links.

   A leg between two links.
*/
#define C_LEG 2

/************************************************************************************/

/** 
    \brief A test that return TRUE if the given identifier is that of the ground link.

    A test that return TRUE if the given identifier is the one correcponding to 
    the ground link.
*/
#define IsGroundLink(id) (id==0)


/** 
    \brief Information about each rigid part of a mechanisms.

    Information about each rigid part of a mechanisms. Each link is formed
    by one of more convex bodies.

    \sa link.h, link.c.
*/
typedef struct {
  char *name; /**< Name given to the links.*/

  unsigned int type; /**< Type of link: \ref LINK_FullRot, \ref LINK_AxisX, \ref LINK_DeformX, \ref LINK_NoRot. */

  double s; /**< Sinus between the vectors defining the internal reference frame for the
	          link. <br> The default value is 1.<br>
		  See \ref ChangeLinkReferenceFrame.*/

  double c; /**< Cosinus between the vectors defining the internal reference frame for the
	         link. <br> The default value is 0. <br>
		 See \ref ChangeLinkReferenceFrame.*/

  THTransform R; /**< Rotation matrix defining the internal reference frame from
		      the reference frame where bodies are defined.  <br> 
		      In some cases the links do not have an orthonormal basis associated
		      but a non-orthonormal one. In this case the variables for the link
		      encode M*iR with M the orthonormal basis and iR a basis change to
		      a non-orthonormal basis. Where in normal links points (p) are taken
		      to the global frame using M*p, here we have to compute
		      (M*iR)*R*p=M*p. The link variables encode M*iR all together and, thus
		      we need R to  compute R*p, when necessary.
		      The default value is the identity.<br>
		      \b Note: For convenience, we use a homogeneous transform structure
		      to hold the basis change but the matrix is not a homogeneous 
		      transform (the new rotation basis is not necessarilyt orthonormal).
		      The two only operations we use from the homogeneous transform
		      implementation are a matrix per vector product and a matrix
		      matrix operation
		      See \ref ChangeLinkReferenceFrame.*/
  THTransform iR; /**< Inverse of R. This is necessary to recover M*iR for a given M 
		       (the link rotation using a orthonormal basis). In this case
		       M*iR gives the values for the variables used internally to
		       represent the rotation for the link. */

  Tvector bodies; /**< Set of sub-parts of the link where each part is a convex object.<br>
		       All these convex objects are defined a common reference frame, i.e.,
		       the link's reference frame.<br> 
		       Bodies are convex polyhedrons (see Tpolyhedron).*/

  boolean allSpheres; /**< TRUE if all non-DECOR bodies (i.e., bodies that ar considered
			   in collision detection) are spheres. If all bodies in all links
			   are spheres, we implement a speciall collision detectio prodedure
			   based on the distance between the centers and not on separating planes. */

  unsigned int axisID[3]; /**< Identifier of the three objects (lines) representing 
			       the reference frame for the link.<br>
			       These identifiers are only used if \e axes parameter
			       of \ref PlotLink is larger than 0. 
			       Otherwise they are set to NO_UINT.
			  */
  double maxCoord;    /**< Maximum coordinate value used in any of the bodies of the link. */

  TCuikSystem *csvID; /**< Last cuik system used to get the variable identifiers of this link.
			   If in the new calls to \ref GetTransform2Link, \ref RegenerateLinkBox,
			   or \ref RegenerateLinkSolution the input cuiksystem is the same as this
			   one, we could reuse the values stored in \e vID. Otherwise we have to
			   recompute them. */
  unsigned int *vID;  /**< Identifiers of the variables for this link defined over \e csvID. */
  unsigned int nvID;  /**< Number of elements in vID. This depends on the 
		 	   \ref CT_REPRESENTATION parameter. */

  double mass;          /**< Mass of the link. Default is 0. If 0, we assume that the link
			     has no dynamic information. */
  double **iMatrix;     /**< Inertia (3x3) matrix of the link. Default is a null matrix. */
  THTransform iFrame;   /**< Transfrom from the reference frame of the link to the inertial frame.
		             The default is the identity. */
  
  double extForce[3];       /**< External force applied to the link. Only used in tensegrity 
			         structures. */

  boolean forceEquilibrium; /**< TRUE for links where there must be a force equilibrium. This
			         is FALSE for most links, except for some NoRot links used
			         in tensegrities.  The 'extForce' is only relevant if this
			         flag is TRUE. */
  
  double fixedDim[3];  /**< Used to fix the translation of the link. Only used in tensegrity 
			    structures. */

  Tinterval length;    /**< Link length. Only used for tensegrities. Cables, springs and 
			    prismatic bars can vary in length. */
  boolean varLength;   /**< TRUE for links with variable lenth. */

  unsigned int forceModel;  /**< The force model of the link: \ref NO_FORCE, \ref VAR_FORCE,
			         \ref LINEAR_FORCE. */
  Tinterval force;          /**< Range of forces that can be supported/exerted by the link. 
			         Only used for tensegrities. 
			         It is both used for VAR_FORCE and for LINEAR_FORCE links. */
  
  double stiffness;         /**< Link stiffness range. Only used for tensegrities and for 
			         LINEAR_FORCE models. */
  Tinterval rest;           /**< Link rest length. Only used for tensegrities and for 
			         LINEAR_FORCE models. */
  
  unsigned int l1;          /**< For \ref LINK_Connect links, the first connected link. */ 
  unsigned int l2;          /**< For \ref LINK_Connect links, the second connected link. */ 
  double p1[3];             /**< For \ref LINK_Connect links, the point on the first connected link. */ 
  double p2[3];             /**< For \ref LINK_Connect links, the point on the second connected link. */ 
} Tlink;


/** 
    \brief Link configuration.

    Collects the  link internal configuration (other than its pose).
    Part of this information is related to the link deformation, but
    also force information is stored here since in tensegrities, such
    information is part of the link configuration.
*/
typedef struct {
  Tlink *l;         /**< Link for this configuration. */
  unsigned int ndp; /**< Number of internal parameters for the link. */
  double *p;        /**< Value of the configuration parameters.  */
} TLinkConf;

/** 
    \brief Identifies empty link internal configuration.

    Determines if a link internal configuration is empty, i.e., if
    it is a link without internal deformation degrees of freedom
    (it may have internal force degrees of freedom but those are
    not relevant ot the kinematics).

    \param ld The link configuration.

    \return TRUE if the configuration is kinematically irrelevant.
*/
boolean EmptyLinkConf(TLinkConf *ld);

/** 
   \brief Extension of the link.

   Extension of the link. Only defined for prismatic links.
   For other links it triggers an error.

   \param ld The link configuration to query.

   \return The link extension.
*/
double GetLinkConfExtension(TLinkConf *ld);

/** 
    \brief Builds the internal transformation.

    Defines a transformation that traverses the link,
    taking into account the possible link deformation..

    \param bID The body identifier (the transform can be different
               for each body)
    \param t The output transformation. 
    \param ld The information about the link deformation.
*/
void GetLinkConfTransform(unsigned int bID,THTransform *t,TLinkConf *ld);

/** 
   \brief Destructor.

   Release memory.

   \param ld The link deformation information structure to delete.
*/
void DeleteLinkConf(TLinkConf *ld);

/** 
    \brief Constructor.

    Initializes a link structure with no bodies.
   
    \param name  The name to give to the link.
    \param mass The mass of the link. If 0, the link has no dinyamic information.
    \param iMatrix Inertia matrix. If null a zero matrix is set.
    \param iFrame Inertial frame. If null the identity is used.
    \param l The links to initialize.
*/
void InitLink(char *name,double mass,double **iMatrix,THTransform *iFrame,Tlink *l);

/** 
    \brief Constructor.

    Initializes a link structure with no bodies.
    In this particular type of links the orientation 
    of the link is not relevant. Up to now we only use
    this kink of links for tensegrities where the relevant
    information is in the connections between links and not
    in the links themselves.
   
    In principle NoRot links have to be in force equilibrium,
    except if it is explicitly de-activated 
    (see \ref NoForceEquilibriumLink)

    \param name  The name to give to the link.
    \param l The links to initialize.
*/
void InitNoRotLink(char *name,Tlink *l);

/** 
    \brief Constructor.

    Initializes a link structure with no bodies.
    In this particular type of links only the
    X axis of the frame attached to the link is relevant
    for the problem. This is used, for instance, when
    defining composite links (e.g. spherical-spherical)
    where the internal rotation of the link is not
    relevant.
   
    \param name The name to give to the link.
    \param forceModel Force model of the link: \ref NO_FORCE or
                      \ref VAR_FORCE. Can not be \ref LINEAR_FORCE.
    \param length Link length. Only relevant for struts, i.e., in
                  tensegrities and must be constant (a range
		  with null size).
    \param force The maximum force supported by the link. 
                 Only relevant for tensegrities.
    \param mass The mass of the link. If 0, the link has no dinyamic information.
    \param iMatrix Inertia matrix. If null a zero matrix is set.
    \param iFrame Inertial frame. If null the identity is used.
    \param l The links to initialize.
*/
void InitAxisXLink(char *name,unsigned int forceModel,
		   Tinterval *length,Tinterval *force,
		   double mass,double **iMatrix,THTransform *iFrame,Tlink *l);

/** 
    \brief Constructor.

    Initializes an axis X link that can
    elongate along the X axis (i.e., a 
    deformable Axis X link).

    \todo Adjust the dynamic parameters according to the deformation.
   
    \param name  The name to give to the link.
    \param forceModel Force model of the link: \ref NO_FORCE,
                      \ref VAR_FORCE, \ref LINEAR_FORCE.
    \param length Link length. Only relevant for struts, i.e., in
                  tensegrities and must be constant (a range
		  with null size).
    \param stiffness Stiffness of the link. Only relevant for
                     tensegrities.
    \param rest The rest length. Only relevant for tensegrities.
    \param force The maximum force supported by the link. 
                 Only relevant for tensegrities.
    \param mass The mass of the link. If 0, the link has no dinyamic information.
    \param iMatrix Inertia matrix. If null a zero matrix is set.
    \param iFrame Inertial frame. If null the identity is used.
    \param l The links to initialize.
*/
void InitDeformXLink(char *name,unsigned int forceModel,
		     Tinterval *length,double stiffness,
		     Tinterval *rest,Tinterval *force,
		     double mass,double **iMatrix,THTransform *iFrame,Tlink *l);

/** 
   \brief Constructor.

    Initializes an axis X link that can
    extend along the X axis in a prismatic way. It can be seen
    as the same as a LINK_DeformX but here the deformation is 
    an extension of a prismatic element.
   
    \todo Adjust the dynamic parameters according to the extension of the prismatic link.

    \param name  The name to give to the link.
    \param forceModel Force model of the link: \ref NO_FORCE,
                      \ref VAR_FORCE, \ref LINEAR_FORCE.
    \param length Link length. Only relevant for struts, i.e., in
                  tensegrities and must be constant (a range
		  with null size).
    \param stiffness Stiffness of the link. Only relevant for
                     tensegrities.
    \param rest The rest length. Only relevant for tensegrities.
    \param force The maximum force supported by the link. 
                 Only relevant for tensegrities.
    \param mass The mass of the link. If 0, the link has no dinyamic information.
    \param iMatrix Inertia matrix. If null a zero matrix is set.
    \param iFrame Inertial frame. If null the identity is used.
    \param l The links to initialize.
*/
void InitPrismaticXLink(char *name,unsigned int forceModel,
			Tinterval *length,double stiffness,
			Tinterval *rest,Tinterval *force,
			double mass,double **iMatrix,THTransform *iFrame,Tlink *l);
/** 
   \brief Constructor.

    Initializes a connection link: a cable, spring or leg connecting two different
    links.
   
    \param name  The name to give to the link.
    \param type Type of connection: C_CABLE, C_SPRING, C_LEG. 
    \param l1 The identifier of the first link to connect.
    \param l2 The identifier of the second link to connect.
    \param p1 The point in the first link.
    \param p2 The point in the second link.
    \param r The radious of the link.
    \param c The color of the link.
    \param gr The granularity of the link.
    \param bs Status of the body: NORMAL, HIDDEN, DECOR. 
    \param rest Rest length. Only used for springs.
    \param stiffness Stiffness constant. Only used for springs.
    \param l The links to initialize.
*/
void InitConnectLink(char *name,unsigned int type,
		     unsigned int l1,unsigned int l2,double *p1,double *p2,
		     double r,Tcolor *c,unsigned int gr,unsigned int bs,
		     Tinterval *rest,double stiffness,
		     Tlink *l);
/** 
    \brief Copy constructor.

    Initializes a link copying the information from another link.

    \param l_dst The link to initialize.
    \param l_src The link from where to copy.
*/
void CopyLink(Tlink *l_dst,Tlink *l_src);

/** 
    \brief Defines the mass of the link.

    Sets the mass of the link.
    If set to 0, the dynamic information is reseted.

    \param mass The new mass.
    \param l The link to modify.
*/
void SetLinkMass(double mass,Tlink *l);

/** 
    \brief Defines the inertia matrix of the link.

    Sets the inertia matrix of the link.

    \param m The new inertia matrix (a 3x3 symmetric matrix).
    \param l The link to modify.
*/
void SetLinkInertiaMatrix(double **m,Tlink *l);

/** 
    \brief Defines the inertial frame of the link.

    Sets the inertial frame of the link, i.e., the 
    transfrom from the link reference frame to the
    inertial reference frame. The inertial reference
    frame is centered at the center of mass of the
    link.

    \param t The new transfrom to the inertial frame.
    \param l The link to modify.
*/
void SetLinkInertialFrame(THTransform *t,Tlink *l);

/** 
    \brief Gives the mass of the link.

    Gives the mass of the link (0 if not set explicitly).

    \param l The link to query.

    \return The link mass.
*/
double GetLinkMass(Tlink *l);

/** 
    \brief Gives the inertia matrix of the link.

    Gives the (symmetric) inertia matrix of the link.

    \param l The link to query.

    \return Pointer to the inertia matrix.
*/
double **GetLinkInertiaMatrix(Tlink *l);

/** 
    \brief Gives the inertial frame of the link.

    Gives the inertial frame of the link with respect
    to the link frame. This is the identity if not
    set explicity.

    \param l The link to query.

    \return The link inertial frame (w.r.t. the link frame).
*/
THTransform *GetLinkInertialFrame(Tlink *l);

/** 
    \brief Adds a body to the link.

    Adds a body to the link.
    
    \param b The convex polyhedron to add to the link
    \param l The link where to add the new polyhedron.
*/
void AddBody2Link(Tpolyhedron *b,Tlink *l);

/** 
    \brief Adds an external force to a link.

    Adds an external force to a link. The force on the link
    is initalized to zero and several exteran forces can be
    added. Forces must be expressed in a global reference
    frame.

    This is only used in tensegrity structures. In other 
    mechanisms this is not relevant at all.

    \param fx X component of the force to add.
    \param fy Y component of the force to add.
    \param fz Z component of the force to add.
    \param l The link to modify. 
*/
void AddForce2Link(double fx,double fy,double fz,Tlink *l);

/** 
    \brief Retrives the external force applied to a link.

    Retrives the force on a link as defined using
    \ref AddForce2Link.

    This is only used in tensegrity structures. In other 
    mechanisms this is not relevant at all.

    \param dim The translation dimension to query.
    \param l The link to query. 

    \return The force in the required dimension.
*/
double GetForceOnLink(unsigned int dim,Tlink *l);

/** 
   \brief Deactivates the force equilibrium on a link.

   Deactivates the force equilibrium on a link. It only
   has effect on links of type LINK_NoRot (which have
   not been previously deactivated)

   \param l The link to modify.
*/
void NoForceEquilibriumLink(Tlink *l);

/** 
   \brief Determines if forces on link must be in equilibrium.

   Identify links where forces must be in equilibrium
   (sum to 0, including external forces).
   Only some of the links in tensegrities are of this
   type.

   \param l The link to query.

   \return TRUE if the forces on the link must be in 
           equilibrium.
*/
boolean IsForceEquilibriumLink(Tlink *l);

/** 
    \brief Fixes the translation of a link.

    Fixes one of the dimension of the translation of a link.

    This is only used in tensegrity structures. In other 
    mechanisms this is not relevant at all.

    \param dim The translation dimension to fix.
    \param t Value for the dimension.
    \param l The link to modify. 
*/
void SetLinkTrans(unsigned int dim,double t,Tlink *l);

/** 
    \brief Retrives the (eventually) fixed translation of a link.

    Retives the one of the dimension of the translation of a link.

    This is only used in tensegrity structures. In other 
    mechanisms this is not relevant at all.

    \param dim The translation dimension to fix.
    \param l The link to query.

    \return The value assigned for the given translation
            dimension. INF if queried dimesion in not fixed.
*/
double GetLinkTrans(unsigned int dim,Tlink *l);

/** 
    \brief Nominal length of the link.

    The length of the link. Only defined for Axis X links.

    \param l The link to query.

    \return The link length. 0 if it is undefined.
*/
Tinterval *GetLinkLength(Tlink *l);

/** 
    \brief Stiffness of the link.

    Stiffness of the link. Only defined for some Axis X and Deform X links.
    
    \param l The link to query.

    \return The link stiffness. 0 if it is undefined.
*/
double GetLinkStiffness(Tlink *l);

/** 
    \brief The rest value.

    The rest interval for a given link. It is a 
    zero-size interval if the rest is a constant.
    This is only relevant for tensegrites and not
    used at all for mechanisms.

    \param l The link to query.

    \return A pointer to the rest interval.
*/
Tinterval *GetLinkRest(Tlink *l);

/** 
    \brief The max force range.

    The maximum range for compression, 
    tension forces for this link.

    \param l The link to query.

    \return A pointer to the force interval.
*/
Tinterval *GetLinkMaxForce(Tlink *l);

/** 
    \brief Sets a new reference frame for the link.

   
    In order to get the simplest possible set of solutions we can
    select a reference frame for the link different from that used 
    to defined the bodies.
    This internal reference frame is defined from two
    (not necessarily orthogonal) vectors.
    Therefore, we store the sin and cos between the two vectors defining the 
    internal reference frame and the rotation from the frame where bodies are
    defined and the internal reference frame.

    This function does not change the points defining the bodies.
    (they remain in the original frame), but it changes the way they are
    interpreted  changing the workings of
    functions \ref GenerateLinkRot and \ref ApplyLinkRot.

    If the two given vectors are (almost) aligned, the 
    internal reference frame is not changed.

    When using a \ref CT_REPRESENTATION based on quaternions
    it is not possible to change the internal link reference frame.

    \param r The type of representation to use (i.e., the \ref CT_REPRESENTATION
             parameter).
    \param p1 Two 3d points defining the first vector for the new internal reference
              frame.
    \param p2 Two 3d points defining the second vector for the new internal reference
              frame.
    \param l The link whose reference frame we want to change.
*/
void ChangeLinkReferenceFrame(unsigned int r,double **p1,double **p2,Tlink *l);

/** 
    \brief Gets the number of convex parts of the link.

    Gets the number of convex parts of the link.

    \param l The link to query.
   
    \return The number of convex parts of the link.
*/   
unsigned int LinkNBodies(Tlink *l);

/** 
    \brief Gets the number of atoms in a link.

    Gets the number of atoms (i.e., spheres) in a link.

    \param l The link to query.
   
    \return The number of atoms/spheres in the link.
*/
unsigned int LinkNAtoms(Tlink *l);

/** 
    \brief Gets one of the convex parts of the link.

    Gets one of the convex parts of the link.

    \param i The identifier of the convex part to retrive. The identifier
             of a part is given by the order at which they are added
	     to the link.
    \param l The link to query.
   
    \return A pointer to the requested convex part or NULL if the link
            does not have any part with the given identifier.
*/  
Tpolyhedron *GetLinkBody(unsigned int i,Tlink *l);

/** 
    \brief Gets the status of one of the convex parts of the link.

    Gets the status of one of the convex parts of the link.

    \param i The identifier of the convex part to query. The identifier
              of a part is given by the order at which they are added
	      to the link.
    \param l The link to query.
   
    \return The status (NORMAL, HIDDEN, DECOR) of the requested part
            or NO_UINT if the link
            does not have any part with the given identifier.
*/  
unsigned int GetLinkBodyStatus(unsigned int i,Tlink *l);

/** 
    \brief Gets the name of a link.

    Gets the name of a link.
   
    \param l The link to query.
    \return A pointer to a string with the name of the link.
*/
char *GetLinkName(Tlink *l);

/** 
    \brief Gets the type of a link.

    Gets the type of a link.
   
    \param l The link to query.
    \return The type of link (\ref LINK_FullRot, \ref LINK_AxisX, \ref LINK_DeformX, \ref LINK_NoRot).
*/
unsigned int GetLinkType(Tlink *l);

/** 
    \brief Identies links with variable length.

    Used to determine wheter a link has variable length (up to now only
    Deform_X links have variable length).

    \param l The link to query.

    \return TRUE if the link has variable length.
*/
boolean IsVariableLengthLink(Tlink *l);

/** 
    \brief Identify the force model of the link.

    Use to determine the force model of the link: \ref NO_FORCE,
    \ref VAR_FORCE, \ref LINEAR_FORCE.

    \param l The link to query.

    \return The type of force model of the link.
*/
unsigned int GetLinkForceModel(Tlink *l);

/** 
    \brief Get the identifier of the force-related variables of the link.

    Get the identifiers of the force-related of the link, if any.

    \param r Type of representation used (REP_JOINS, REP_LINKS,...).
    \param xID x component of the director vector of the tensegrity element.
    \param yID y component of the director vector of the tensegrity element.
    \param zID z component of the director vector of the tensegrity element.
    \param le Identifier of the link length.
    \param re Identifier of the rest length.
    \param f Identifier of the force (f=st*(le-re))
    \param cs The CuikSystem including the variables.
    \param l The link to query.
*/
void GetLinkForceVars(unsigned int r,
		      unsigned int *xID,unsigned int *yID,unsigned int *zID,
		      unsigned int *le,
		      unsigned int *re,unsigned int *f,
		      TCuikSystem *cs,
		      Tlink *l);

/** 
    \brief Potential energy stored in the link.

    Evaluates the potential energy stored in the link. It only works
    for tensegrity related links with variable length. For other
    links the output is 0. Thus, we capture the potential energy
    in the springs, cables, and prismatic legs of tensegrity structures.
    This energy is somehow compensated by struts (i.e., the compressive 
    elements with constant length).
    but we do not model this part. We assume that the energy of the
    struts comes "for free" as a reaction of the energy in the
    active elements (mainly cables).
    If the energy of the struts need to be taken into account too,
    just model the struts as prismatic legs (with low motion raange and
    high stiffness). Prismatic legs have an associated force model that
    can be used to compute the associated energy.

    In structures with struts, this energy function might not be
    in equilibrium (i.e., null gradient) in the valid tensegrity
    configurations.

    \param r Type of representation used (REP_JOINS, REP_LINKS,...).
    \param cs The cuiksysem on which the dof variables are defined.
    \param p A solution point (in the original form, not in the simplified form).
    \param l The link to query.

    \return The pontential energy considering the link as a spring.
*/
double LinkPotentialEnergy(unsigned int r,TCuikSystem *cs,double *p,Tlink *l);

/** 
    \brief Gradient of the potential energy stored in the link.

    Evaluates the gradient of the potential energy stored in the link. It only works
    for tensegrity related links. For other
    links the output is a null vector. 

    IMPORTANT: see the notes in \ref  LinkPotentialEnergy

    \param r Type of representation used (REP_JOINS, REP_LINKS,...).
    \param cs The cuiksysem on which the dof variables are defined.
    \param p A solution point (in the original form, not in the simplified form).
    \param g The gradient to define
    \param l The link to query.
*/
void LinkForceField(unsigned int r,TCuikSystem *cs,double *p,
		    double *g,Tlink *l);

/** 
   \brief Build the sequence of transforms passing through the link.
   
   Build the sequence of transforms traversing the link.

   Only has effects for deformable links since in them the shape and thus
    the transform tot traverse them varies with the configuration.

   Note that  here we accumulate *homogeneous* transform traversing
   the deformable link. This is NOT the the non-homogeneous
   transform used to model the link deformation.

   \param p The set of parameters.
   \param cs The cuiksysem on which the dof variables are defined.
   \param ts The resulting sequence of transforms.
   \param l The link.
*/
void GetLinkTransSeq(Tparameters *p,TCuikSystem *cs,TTransSeq *ts,Tlink *l);

/** 
    \brief The homogeneous transform traversing the link.
    
    Builds the homogeneous transform traversing the link.

    This only works for deformable links since in them the shape and thus
    the transform tot traverse them varies with the configuration.

    This is like \ref GetLinkTransSeq but here the transform is constant
    instead of symbolic.

    \param dof The degrees of freedom (deformation parameters) for the link.
    \param t The transform to generate.
    \param l The link.
*/
void GetLinkTransform(double *dof,THTransform *t,Tlink *l);

/** 
    \brief  The homogeneous transform traversing the link.

    The same as \ref GetLinkTransform but here the degrees of freedom
    are taken from the information stored in a link deformation
    structure.

    \param def The link deformation information.
    \param t The transform to create.
    \param l The link to query.
*/
void GetLinkTransformFromConf(TLinkConf *def,THTransform *t,Tlink *l);

/** 
  \brief Computes a link configuration.

   Defines a link configuration from the a solution point.

   This sets the link configuration from the solution. 
   For the reverse see \ref GenerateSolutionFromLinkConf

   \param r The type of representation used (REP_JOINTS, REP_LINKS...)
   \param cs The cuiksystem where the variables are defined.
   \param sol The solution point.
   \param def The output deformation information.
   \param l The link.
*/
void GetLinkConfFromSolution(unsigned int r,TCuikSystem *cs,double *sol,TLinkConf *def,Tlink *l);

/** 
  \brief Computes a link configuration.

   Defines a link configuration from an array of degrees of freedom.

   This sets the link configuration from the dof. 
   For the reverse see \ref GenerateDOFFromLinkConf.

   \param dof Values for the deformation paramters of the link. Part of the
              global dof of the system.
   \param def The output deformation information.
   \param l The link.
*/
void GetLinkConfFromDOF(double *dof,TLinkConf *def,Tlink *l);

/** 
    \brief Sets the solution entries corresponding to a link configuration.

    Sets the solution entries corresponding to the link configuration.
    
    This sets the solution from the link configuration. 
    For the reverse see \ref GetLinkConfFromSolution.

    \param r The type of reperesentation used (REP_JOINT, REP_LINK...)
    \param cs The cuiksystem where the variables are defined.
    \param def The output deformation information.
    \param sol The solution point to set.
    \param l The link.
*/
void GenerateSolutionFromLinkConf(unsigned int r,TCuikSystem *cs,TLinkConf *def,double *sol,Tlink *l);

/** 
    \brief Sets the dof entries corresponding to a link configuration.

    Sets the dof entries corresponding to the link configuration.
    
    This sets the dof from the link configuration. 
    For the reverse see \ref GetLinkConfFromDOF.

    \param def The deformation information.
    \param dof The dof array to set.
    \param l The link.
 */
void GenerateDOFFromLinkConf(TLinkConf *def,double *dof,Tlink *l);

/** 
    \brief Gets the number of configuration parameters for a given link.

    \param l The link to query.
    
    \return The number of configuration parameters for the link.
*/
unsigned int NumLinkDOF(Tlink *l);

/** 
    \brief Gets a given DOF range.

    Returns a given link DOF range.

    \param i Index of the deformation parameter. 
    \param l The link to query.

    \return The DOF range.
*/
Tinterval *GetLinkDOFRange(unsigned int i,Tlink *l);

/** 
    \brief Returns a label for a given configuration parameter.

    Creates a string with a label for a configuration parameter.

    This is used to create interfaces.

    \param i The deformation index.
    \param n The string to create. NULL if actuall not created.
             The space for the string is allocated here and must
	     be deallocated externally.
    \param l The link to query.
*/
void GetLinkDOFLabel(unsigned int i,char **n,Tlink *l);

/** 
    \brief Identifies links formed only by spheres.

    Returns TRUE if all non-DECOR bodies in the link (i.e., bodies that are considered
    in the collision checking) are spheres.
   
    This function is used when generating the collision avoidance related equations.
    If all involved bodies are spheres we do not use separating planes but we directly
    bound the squared distance between the sphere centers to be larger than the squared sum of
    radii.
   
    \param l The link to query.

    \return TRUE if all non-DECOR bodies in the link are spheres.
*/
boolean IsLinkAllSpheres(Tlink *l);


/** 
    \brief Identifies the variables giving the pose of the link.

    Sets to TRUE the translations/rotation variables for the
    given link in the given array of variables.   
   
    \param r The type of representation used (REP_JOINTS, REP_LINKS,..).
    \param vars The array of booleans to set.
    \param cs The cuiksystem where the link variables are included.
    \param l The link.   
*/
void SetPoseVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l);

/** 
    \brief Identifies the variable giving the force of the link.

    Sets to TRUE the force variables for the
    given link in the given array of variables.   
    Note that only the force variable is set. Not all the force
    related variables (like rest length, for instance).
   
    \param r The type of representation used (REP_JOINTS, REP_LINKS,..).
    \param vars The array of booleans to set.
    \param cs The cuiksystem where the link variables are included.
    \param l The link.   
    
    \return The number of force variables of the link.
*/
unsigned int SetForceVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l);

/** 
    \brief Identifies the force-related variables of the link.

    Sets to TRUE the force and rest-length variables, i.e., the
    variables without a geometric impact.

    It is like \ref SetForceVars but the rest-length variable 
    is also set, if necesary.
   
    \param r The type of representation used (REP_JOINTS, REP_LINKS,..).
    \param vars The array of booleans to set.
    \param cs The cuiksystem where the link variables are included.
    \param l The link.   
    
    \return The number of force variables of the link.
*/
unsigned int SetForceRelatedVars(unsigned int r,boolean *vars,TCuikSystem *cs,Tlink *l);

/** 
    \brief Identifies the simplified variables giving the rotation of the link.

    Identifies variables that give the rotation of the links that survive
    in the simplified cuiksystem.

    Thes variables are identified in an array of booleans and their name
    is printed to a file (one name per row).

    \param p The set of parameters.
    \param sv The array of booleans to set to TRUE for the good variables.
    \param cs The cuiksystem on which the variable are defined.
    \param l The link.
*/
void GetLinkPoseSimpVars(Tparameters *p,boolean *sv,TCuikSystem *cs,Tlink *l);

/** 
    \brief Generate the variables and constraints related with the rotation of the
    link reference frame.

    Each link has a 3D reference frame formed by three vectors (in general
    orthonormal vectors unless \ref ChangeLinkReferenceFrame is used).
    This functions add the variales representing the rotation of this reference
    frame with respect to the gobal reference frame.
    The translation from this global reference frame to the origin of the
    frame attached to the link is given by equations involving only
    rotation variables (and fixed vectors) and can only be computed at the level
    where we have together links (mechanisms) and cuiksystems, that is, at the
    \ref world.h level.
  
    Note that the rotation representation depends on the 
    \ref CT_REPRESENTATION setting.
   
    \param p A set of parameters. They include, for instance the dummification
             level.
    \param lID The identifier of the link in the mechanism. Used to generate
               unique names for the new variables.
    \param cs The cuiksystem where to add the variables and equations.	
    \param l The link from where to generate the variables and equation.
*/
void GenerateLinkRot(Tparameters *p,unsigned int lID,
		     TCuikSystem *cs,Tlink *l);

/** 
    \brief Fixes the Z compoment of the vector giving the pose of the link.

     Fixes the Z compoment of the vector giving the pose of the link. This
     only works for links represented by a single vector (i.e., AxisX, DeforX,
     PrismaticX links) and when the representation is not REP_JOINTS)

    \param p A set of parameters.
    \param lID The identifier of the link in the mechanism.
    \param cs The cuiksystem where to add the Z=0 equations.	
    \param l The link to process.
*/
void FixLinkZToZero(Tparameters *p,unsigned int lID,TCuikSystem *cs,Tlink *l);

/** 
    \brief Transforms a vector from the local reference frame to the global one
           and accumulates the resulting expression into the given equations.

    Apply the changes of basis given by the link reference frame
    to a vector. This results in an expression that
    transforms the vector from the local reference frame to the global one.
    These expressions are added to the given equations (one expression for X,
    another for Y, and another for Z).

    \param pr The set of parameters.
    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRot(Tparameters *pr,double sf,unsigned int sv,double *p,Tequation *eq,
		  TCuikSystem *cs,boolean groundLink,Tlink *l);

/** 
    \brief Variant of \ref ApplyLinkRot.

    Version of \ref ApplyLinkRot for deformable links where the deformation
    is not considered. For non-deformable links this is the same as \ref ApplyLinkRot.

    This can also be seen as a \ref ApplyLinkRot for a deformable links with
    a particular deformation status (i.e., a default deformation) that is given
    in the 'sf' and 'sv' parameters.

    \param pr The set of parameters.
    \param sf Constant scale factor to apply to the input vector.
    \param sv Variable scale factor given as the identifier of the
              range in the given \e box whose center have to be used as scale factor.
	      If no variable scale factor is to be used this parameter should be
	      NO_UINT.
    \param p The 3D vector in the link reference frame that we want to transform to
             the global one and to add to \e trans.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotNoDeform(Tparameters *pr,
			  double sf,unsigned int sv,double *p,Tequation *eq,
			  TCuikSystem *cs,boolean groundLink,Tlink *l);
/** 
    \brief Transforms a variable vector from the local reference frame to the global one
           and accumulates the resulting expression into the given equations.

    Apply the changes of basis given by the link reference frame
    to a vector of variables representing a point in local coordinates 
    of the link.

    \param pr The set of parameters.
    \param sf Constant scale factor to apply to the input vector.
    \param vID The 3D vector of variables to rotate.
    \param eq Set of 3 equations where to add the 3 expressions resulting from this
              function (one for the X component of the vector in the globla frame,
	      another for the Y expression and, finally the expression for the Z
	      component). 
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers. The numerical identifier
	      of the variable is used to generate a unique name for it.
    \param groundLink TRUE if the given link is the ground link.
    \param l The link to use to rotate the given input vector \e p.
*/
void ApplyLinkRotVar(Tparameters *pr,double sf,unsigned int *vID,Tequation *eq,
		     TCuikSystem *cs,boolean groundLink,Tlink *l);

/** 
    \brief Computes the values for the dummy variables used to
    represent the rotation matrices for a given link.

    Solution points only include values for the system (and secondary) variables. However,
    in some formulations, the frame of reference for each link is represented
    using not only system variables, but dummy or force variables too.
    This function computes the values for the link-related non-basic variables form
    the basic ones for a given link.
  
    \param p The set of parameters.
    \param cs The cuik system on which the boxes are defiend. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point with the values for the system variables.
               At the end of the function, this vector also has values for
	       the link-related non-basic variables.
    \param groundLink TRUE if the given link is the ground link. The rotation matrix
                      for the ground link is fixed (the identity) and, its rotation
		      matrix generates no variables (nor system nor dummy).
    \param l The link.
*/
void RegenerateLinkSolution(Tparameters *p,TCuikSystem *cs,double *sol,
			    boolean groundLink,Tlink *l);

/** 
    \brief Computes the values for the dummy variables.

    This is the same as \ref RegenerateLinkSolution but working on solution boxes
    instead of on solution points (i.e. it is interval-based instead of
    floating point based).
  
    \param p The set of parameters.
    \param cs The cuik system on which the boxes are defiend. It is used to, given
               the name of the variables corresponding the reference frame of the
	       given link, retrive its numerical identifiers, i.e., the
	       number of range of the \e box to use to instantiate each variable.
    \param b The solution box with the values for the system variables.
             At the end of the function, this box also has values for
	     the link-related dummy variables.
    \param groundLink TRUE if the given link is the ground link. The rotation matrix
                      for the ground link is fixed (the identity) and, its rotation
		      matrix generates no variables (nor system nor dummy).
    \param l The link.
*/
void RegenerateLinkBox(Tparameters *p,TCuikSystem *cs,Tbox *b,
		       boolean groundLink,Tlink *l);

/** 
    \brief Gets the homogeneous transform associated with a link for a given solution point.

    Returns the  homogeneous transform with the position and orientation of the
    link for a given solution point.

    \param p The set of parameters.
    \param cs The cuik system on which the boxes are defined. It is used to, given
              the name of the variables corresponding the reference frame of the
	      given link, retrive its numerical identifiers, i.e., the
	      number of range of the \e box to use to instantiate each variable.
    \param sol The solution point including values for all variables (i.e., already regenerated
               using \ref RegenerateLinkSolution before calling this function). 
    \param groundLink TRUE if the given link is the ground link.
    \param trans 3d vector with the translation from the ground link to this link.
                 The variables for these translations are removed from the cuiksystems
		 and computed from rotations and fixed vectors. Consequently they can
		 only be computed at the level where we have cuiksystems and links
		 (i.e. in \ref world.h).
    \param t The returned homogeneous transform.
    \param def Configuration parameter. Complements 't' for visualization.
    \param l The link whose reference frame we want to retrive.
*/
void GetTransform2Link(Tparameters *p,TCuikSystem *cs,double *sol,boolean groundLink,
		       double *trans,THTransform *t,TLinkConf *def,Tlink *l);

/** 
   \brief Transform to a connnection link.

   Computes the transform to a connectin link given the transforms to the normal links.

   \param tl The transforms to the different \e normal links.
   \param t The transform to compute.
   \param def The link configuration.
   \param l The link.
*/
void GetTransform2ConnectionLink(THTransform *tl,THTransform *t,TLinkConf *def,Tlink *l);

/** 
   \brief Wrench exerced by a spring on the connected links.

   Computes the wrench exerced by a spring on the connected links.
   For connection links that are not springs, the output wrenches are zero.

   \param tl The transforms to the different \e normal links.
   \param wr1 The wrench on the first link in global coordinates.
   \param wr2 The wrench on the second link in global coordinates.
   \param l The connection link.
*/
void GetConnectionLinkWrench(THTransform *tl,double *wr1,double *wr2,Tlink *l);


/** 
   \brief Potential energy of a link.

   This is a generalization of \ref LinkPotentialEnergy which works in general
   (not only for tensegrity structures).

   It is used when computing the potential (mechanical) energy of a dynamical
   system.

   \param tl The transforms to the different \e normal links.
   \param l The connection link.

   \return The potential energy stored in the link (spring).
*/
double GetConnectionLinkPotentialEnergy(THTransform *tl,Tlink *l);

/** 
    \brief Defines the link variables from a transform.

    Generate the solution variables form an homogenous transform giving the pose of 
    the link and the internal link configuration.

    \param p The set of parameters.
    \param t The transform giving the link pose.
    \param def The internal configuration of the link.
    \param cs The cuik system on which the variables are defined.
    \param sol The solution point where to store the generated values.
    \param groundLink TRUE for the ground link.
    \param l The link.
*/
void GenerateLinkSolution(Tparameters *p,THTransform *t,TLinkConf *def,TCuikSystem *cs,
			  double *sol,boolean groundLink,Tlink *l);

/** 
    \brief Identifies connection cables.

    Identifies connection cables.

    \param l The link to query.

    \return TRUE for connection cables.
*/
boolean IsConnectionCable(Tlink *l);

/** 
    \brief Identifies connection springs.

    Identifies connection springs.

    \param l The link to query.

    \return TRUE for connection springs.
*/
boolean IsConnectionSpring(Tlink *l);

/** 
    \brief Identifies connection legs.

    Identifies connection legs.

    \param l The link to query.

    \return TRUE for connection legs.
*/
boolean IsConnectionLeg(Tlink *l);


/** 
   \brief First link connected by a connection link.

   Returns the first link connected by a connection link.

   \param l The connection link.

   \return The first connected link.
*/
unsigned int GetConnectLinkFrom(Tlink *l);

/** 
   \brief Second link connected by a connection link.

   Returns the second link connected by a connection link.

   \param l The connection link.

   \return The second connected link.
*/
unsigned int GetConnectLinkTo(Tlink *l);

/** 
   \brief Point on the first link connected by a connection link.

   Returns the point on the first link connected by a connection link.

   \param p The returned point.
   \param l The connection link.
*/
void GetConnectLinkPointFrom(double *p,Tlink *l);

/** 
   \brief Point on the second link connected by a connection link.

   Returns the point on the second link connected by a connection link.

   \param p The returned point.
   \param l The connection link.
*/
void GetConnectLinkPointTo(double *p,Tlink *l);

/** 
    \brief Checks if a links has some visible parts.
   
    Checks if a links has some visible parts, i.e., if not all the parts of the
    link are HIDDEN.
   
    \param l The link to query.

    \return TRUE if the link has, at least, one NORMAL of DECOR part.
*/
boolean VisibleLink(Tlink *l);

/** 
    \brief Returns the sum of the maximum coordinate value for all the convex polyhedrons
    in the link.

    Returns the sum of the maximum coordinate value (either for X,Y or Z) for all the 
    convex polyhedrons in the link.
    This is used in higher levels to define an over-estimate
    bounding-box of the world. This bounding box is used to define the ranges for some
    of the coordinate and separating planes variables.

    \param l The link to query.

    \return The sum of the maximum coordinate values for all bodies in the link.
*/
double GetLinkMaxCoordinate(Tlink *l);

/** 
    \brief Prints the center of the atoms in a link in gobal coordinates.

    Stores the centers of the atoms in a given link in global coordinates.

    This is used only whent the world represents a molecule and we want
    to store the atom (i.e., the sphere) positions into a file.
    
    \param f The file where to store the atom centers.
    \param tl The transform to get the global coordinates of the link.
    \param l The link to process.
*/
void LinkPrintAtoms(FILE *f,THTransform *tl,Tlink *l);

/** 
    \brief Prints the center of the atoms in a link in gobal coordinates.

    Stores the centers of the atoms and their radius in a given link in 
    global coordinates.

    This is an auxiliary function of \ref MechanismStoreRigidAtoms.
    
    \param f The file where to store the atom centers.
    \param tl The transform to get the global coordinates of the link.
    \param l The link to process.
*/
void LinkStoreAtoms(FILE *f,THTransform *tl,Tlink *l);

/** 
    \brief Adds a link to a 3d scene.

    Adds a link to a 3d scene. It adds the diffent parts of the link
    as if they are expressed in the global frame. To displace the use
    \ref MoveLinkFromTransform

    \param pt The 3d geometry where to add the link.
    \param axesLength >0 to display the link axes. The value is the length of the
                     lines representing the axes. The reference axes for
		     the link are represeted as red for X, green for Y and
		     blue for Z.
    \param l The link to add to the scene.
*/
void PlotLink(Tplot3d *pt,double axesLength,Tlink *l);


/** 
    \brief Displaces a link in a 3d scene.

    Displaces a link previously added to a 3d scene from the transform giving
    the pose of the link.
   
    This function triggers an error (actually the error is triggered in 
    GetTransform2Link) if applied to the groundlink. Note that the groundLink
    is not suposed to move.

    \param pt The 3d scene where the apply the displacement.
    \param t The transform giving the pose of the link.
    \param def The configuration parameters for the link.
    \param l The link to move.
*/
void MoveLinkFromTransform(Tplot3d *pt,THTransform *t,TLinkConf *def,Tlink *l);

/** 
    \brief Stores the link information into a file.

    Stores the link information into a file in the format 
    valid to be read by \ref InitWorldFromFile.
   
    \param f The file where to store the information.
    \param path The working folder.
    \param prefix Prefix to add to the file names for the bodies
                  in this link, if any.
    \param l1 Name of the first connected link. Only used in connector links.
    \param l2 Name of the second connected link. Only used in connector links. 
    \param l The link to print.
*/
void PrintLink(FILE *f,char *path,char *prefix,
	       char *l1,char *l2,Tlink *l);

/** 
    \brief Destructor.

    Deletes the information stored in a link and frees the allocated memory.
   
    \param l The link to delete.
*/
void DeleteLink(Tlink *l);

#endif
