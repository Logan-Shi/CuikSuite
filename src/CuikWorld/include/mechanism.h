#ifndef MECHANISMH
#define MECHANISMH

#include "vector.h"
#include "cuiksystem.h"
#include "box.h"
#include "link.h"
#include "joint.h"
#include "plot3d.h"
#include "color.h"

/** 
    \file mechanism.h
    \brief Definition of the Tmechanism type and the associated functions.

    Definition of the Tmechanism type and the associated functions.

    \sa Tmechanism, mechanism.c.
*/

/****************************************************************************/
/** \brief Initial room for links in a mechanism. 

    Initial room for links in a mechanisms. It will be enlarged if necessary.

    \sa Tmechanism
*/
#define INIT_NUM_LINKS 10
/****************************************************************************/
/** \brief Initial room for joints in a mechanism. 

    Initial room for joints in a mechanisms. It will be enlarged if necessary.

    \sa Tmechanism
*/
#define INIT_NUM_JOINTS 10
/****************************************************************************/

/** 
   \brief A mechanism description.

   Description of a mechanism composed by links (i.e., rigid parts composed
   by convex sub-parts) and joints connecting this links. We assume the
   mechanism is fully connected (i.e., there are not links not-connected
   to the ground link). Note that, thanks to the use of the FREE_JOINT, 
   several independent sub-mechanisms can be seen as a single \e connected 
   mechanism.
   
   \sa  mechanism.h, mechanism.c.
*/
typedef struct {
  Tvector joints; /**< Set of relations (revolutions/sliding/...) between links. */
  Tvector links;  /**< Set of rigid parts of a mechanisms. Each link is composed
		       by one or more convex parts. */

  unsigned int nbodies; /**< The number of convex parts added over all links. */
  boolean allSpheres;   /**< TRUE if all the bodeis in the mechanism are spheres. */
  double maxCoord;      /**< Sum of the maximum coordinate values used in all 
			     the links and joints of the mechanism.*/
  boolean isTensegrity;/**< TRUE if the mechanism is a tensegrity structure.
			    This is deduced by the links added to the mechanism. */
} Tmechanism;

/** 
   \brief Constructor.

   Defines an empty mechanism.

   \param m The mechanism to initialize.
*/
void InitMechanism(Tmechanism *m);

/** 
   \brief Gets the number of links of a mechanism.

   Gets the number of links of a mechanism.
   
   \param m The mechanism to query.

   \return The number of links of a mechanism.
*/   
unsigned int GetMechanismNLinks(Tmechanism *m);

/** 
   \brief Gets the number of joints of a mechanism.

   Gets the number of joints of a mechanism.
   
   \param m The mechanism to query.

   \return The number of joints of a mechanism.
*/ 
unsigned int GetMechanismNJoints(Tmechanism *m);

/** 
   \brief Gets the number of convex sub-parts (or bodies) of a mechanism.

   Gets the number of convex sub-parts of a mechanism added all over
   the links of the mechanism.
   
   \param m The mechanism to query.

   \return The number of convex bodies of a mechanism.
*/ 
unsigned int GetMechanismNBodies(Tmechanism *m);

/** 
    \brief TRUE if the mechanism is composed by spheres only.

    Identifies mechanisms composed by spheres only.
    Mechanism derived from molecules are typically composed by spheres
    only and we can take advantage of this by implementing speciallzed
    collision detection precedures.

    \param m The mechanism to query.

   \return TRUE if all (relevant) bodies are spheres.
*/
boolean IsMechanismAllSpheres(Tmechanism *m);

/** 
   \brief Returns the sum of the maximum coordinate value for all the links and joints
          in the mechanism.

   Returns the sum of the maximum coordinate value for all the links and joints
   in the mechanism.
   This is used in higher levels to define an over-estimate
   bounding-box of the mechanism. This bounding box is used to define the ranges for some
   of the coordinate and separating planes variables.

   \param m The mechanism to query.

   \return The sum of the maximum coordinate values for all links and joints.
*/
double GetMechanismMaxCoordinate(Tmechanism *m);


/** 
   \brief Computes the mobility of a given mechanism

   Computes the degrees of freedom of a mechanism. 

   The degrees of freedom are computed as 6 per link (but for the 
   ground link) less the degrees of freedom reduced by the joints
   (6-the degrees of freedom of the joint given by \ref GetJointDOF).
   Of course, this computation assumes that all link dimensions
   are general. For special link sizes/joint points the mechanisms
   can have more degrees of freedom than the returned by this function
   (i.e., the mechanism can be architecturally singular). 

   \param m The mechanism to query.

   \return The degrees of freedom of the mechanism.
*/
signed int GetMechanismMobility(Tmechanism *m);

/** 
   \brief Gets a point from the mechanism.

   Gets a 3d point from the mechanism, i.e., from a convex
   body of a link of the mechanism.
   
   Note that identifier are numbered form 0.

   \param lID Identifier of the link.
   \param bID Identifier of the convex body.
   \param pID Identifier of the point.
   \param p 3d vector where to store the point.
   \param m The mechanisms to query.
*/
void GetMechanismDefiningPoint(unsigned int lID,unsigned int bID,unsigned int pID,
			       double *p,Tmechanism *m);

/** 
   \brief Adds a link to a mechanism.

   Adds a link to a mechanism.

   \param l The link to add.
   \param m The mechanism to update.

   \return The identifier assigned to the new link (in principle this is the
           position of the vector of links where the new link is stored).
*/ 
unsigned int AddLink2Mechanism(Tlink *l,Tmechanism *m);

/** 
   \brief Adds a joint to a mechanism.

   Adds a joint to a mechanism.

   \param j The joint to add.
   \param m The mechanism to update.

   \return The identifier assigned to the new joint (in principle this is the
           position of the vector of joints where the new joint is stored).
*/ 
unsigned int AddJoint2Mechanism(Tjoint *j,Tmechanism *m);

/** 
   \brief Adds a convex sub-part to a mechanism.

   Adds a convex sub-part to a mechanism.

   \param lID The link where the new sub-part has to be added.
   \param b The convex sub-part to add.
   \param m The mechanism to update.

   \return The total number of convex bodies in the mechanism after adding the new body.
*/ 
unsigned int AddBody2Mechanism(unsigned int lID,Tpolyhedron *b,Tmechanism *m);

/** 
   \brief Gets the identifier of a link given its name.

   Gets the identifier of a link given its name.

   \param name The name of the link.
   \param m The mechanisms to query

   \return The identifier of the link with the given name or NO_UINT if
           the mechanisms does not include any link with that name.
*/
unsigned int GetLinkID(char *name,Tmechanism *m);

/** 
   \brief Gets a link given its identifier.

   Gets a link given its identifier.

   \param i The identifier of the link to retrive.
   \param m The mechanism to query.

   \return A pointer to the link with the given identifier or NULL if there is
           no link with the provided identifier.
*/
Tlink *GetMechanismLink(unsigned int i,Tmechanism *m);

/** 
   \brief Gets a link identifier given its name.

   Gets a link identifier given its name.

   \param ln The name of the link.
   \param m The mechanism to query.

   \return The identifier of the link with the given name or NO_UINT if there is
           no link with the provided name.
*/
unsigned int GetMechanismLinkID(char *ln,Tmechanism *m);

/** 
   \brief Gets a joint given its identifier.

   Gets a joint given its identifier.

   \param i The identifier of the joint to retrive.
   \param m The mechanism to query.

   \return A pointer to the joint with the given identifier or NULL if there is
           no joint with the provided identifier.
*/
Tjoint *GetMechanismJoint(unsigned int i,Tmechanism *m);

/** 
   \brief TRUE if all joints are revolute joints.

   Determines if all the joints in a mechanisms are revolute joints.
   
   In mechanisms that are all revolute-based and that have revolute
   binary links, the reference for some links are adjusted so that we
   get simpler equations.
   (see \ref ChangeLinkReferenceFrame)

   \param m The mechanism.

   \return  TRUE if all joints are revolute joints.
*/
boolean AllRevolute(Tmechanism *m);

/** 
   \brief Adds a mechanism to a 3d scene.

   Adds a mechanism to a 3d scene. All convex parts of all links are added using
   the same frame of reference (i.e, the global one) and thus they will be
   displayed colliding unless they are moved.

   \param pt The 3d scene where to add the mechanism.
   \param axesLength Length for the axes for each link. 0 not to display them.
   \param m The mechanism display.

   \sa MoveMechanismFromTransforms
*/
void PlotMechanism(Tplot3d *pt,double axesLength,Tmechanism *m);


/** 
  \brief Computes the values for the non-system variables used to represent
         the rotation matrices for all links in the mechanism.

  Solution points only include values for the system variables. However,
  in some formulations, the frame of reference for each link is represented
  using not only system variables, but dummy variable too.
  This function computes the values for the link-related dummy variables form
  the system ones for all the links in the mechanism.

  \param p The set of parameters.
  \param cs  The cuik system on which the solutions are defiened. It is used to, given
             the name of the variables corresponding the reference frame of the
	     given link, retrive its numerical identifiers, i.e., the
	     number of range of the \e box to use to instantiate each variable.
  \param sol The solution point with the values for the system variables.
             At the end of the function, this vector also has values for
	     the link-related dummy variables.
  \param m The mechanism.
*/
void RegenerateMechanismSolution(Tparameters *p,TCuikSystem *cs,
				 double *sol,Tmechanism *m);


/** 
  \brief Computes the values for the non-system variables.

  This is the same as \ref RegenerateMechanismSolution but it works in solution
  boxes instead of on solution points (i.e. it is interval-based instead of
  floating point based).

  \param p The set of parameters.
  \param cs  The cuik system on which the solutions are defiened. It is used to, given
             the name of the variables corresponding the reference frame of the
	     given link, retrive its numerical identifiers, i.e., the
	     number of range of the \e box to use to instantiate each variable.
  \param b The solution box with the values for the system variables.
           At the end of the function, this box also has values for
	   the link-related dummy variables.
  \param m The mechanism.
*/
void RegenerateMechanismBox(Tparameters *p,TCuikSystem *cs,Tbox *b,Tmechanism *m);


/** 
   \brief Extract the joint DOF values form the poses of all links.

   Obtains the value of the degrees of freedom given the poses for all links.

   \param p The set of parameters.
   \param tl Homogeneous transform giving the pose of the link in global coordinates.
   \param def The configuration of each link. Use NULL if no link can actually deform.
   \param dof The space where to store the computed dof.
   \param m The mechanism to query.
*/
void GetMechanismDOFsFromTransforms(Tparameters *p,THTransform *tl,TLinkConf *def,
				    double *dof,Tmechanism *m);


/** 
    \brief Prints the center of the atoms in a mechanism.

    Stores the centers of the atoms in a mechanism.

    This is used only whent the world represents a molecule and we want
    to store the atom (i.e., the sphere) positions into a file.
    
    \param f The file where to store the atom centers.
    \param tl Array of transforms giving the global pose for each link.
    \param m The mechanism to process.
*/
void MechanismPrintAtoms(FILE *f,THTransform *tl,Tmechanism *m);

/** 
    \brief Auxiliary function for \ref WorldStoreRigidGroups.

    Auxiliary function for \ref WorldStoreRigidGroups. It basically stores
    the spheres giving its center and radius.
    
    \param f The file where to store the atom centers.
    \param tl Array of transforms giving the global pose for each link.
    \param m The mechanism to process.
*/
void MechanismStoreRigidAtoms(FILE *f,THTransform *tl,Tmechanism *m);

/** 
   \brief Displaces a mechanism in a 3d scene.

   Displaces a mechanism previously added to a 3d scene to a given solution piont.

   \param pr The set of parameters. Only used for debug.
   \param pt The 3d scene where the apply the displacement.
   \param tl Homogeneous transform giving the pose of the link in global coordinates.
   \param def Configuration parameters. One per link (up to now).
   \param m The mechanism to move.
*/
void MoveMechanismFromTransforms(Tparameters *pr,Tplot3d *pt,
				 THTransform *tl,TLinkConf *def,
				 Tmechanism *m);

/** 
   \brief Stores the mechanisms information into a file.

   Stores the link/joint information into a file in the format 
   valid to be read by \ref InitWorldFromFile.
   
   \param f The file where to store the information.
   \param path The working folder.
   \param prefix Prefix to add to the sub-files generated to describe
                 the mechanisms (i.e., files with the geometry, mainly).
   \param m The mechanism with the links/joints to store.
*/
void PrintMechanism(FILE *f,char *path,char *prefix,Tmechanism *m);

/** 
   \brief Destructor.

   Deletes the information stored in a mechanism and frees the allocated memory.
   
   \param m The mechanism to delete.
*/
void DeleteMechanism(Tmechanism *m);

#endif
