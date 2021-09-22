#ifndef CDH
#define CDH

#include "htransform.h"
#include "mechanism.h"
#include "environment.h"

/** \file cd.h

    \brief Headers of the interface with the collision detection engine.

    Headers and definitions of the interface with the collision detection engine.

    \sa cd.c
*/

#ifdef _HAVE_SOLID
  #include <solid/SOLID.h>
#endif

#ifdef _HAVE_VCOLLIDE
  #include "cd_vcollide.h"
#endif

#ifdef _HAVE_PQP
  #include "cd_pqp.h"
#endif

#ifdef _HAVE_FCL
  #include "cd_fcl.h"
#endif

#ifdef _HAVE_BULLET
  #include "cd_bullet.h"
#endif

#ifdef _HAVE_RIGIDCLL
  #include "cd_rigidCLL.h"
#endif

/** 
   \brief Information on the detected collisions.

   Information on a particular collision. 

   Right now only SOLID and FCL store this information.
   The rest of collison detection engines are only
   able to detect the fisrt collision, but not
   all the collisions and the related information.

   Note that for the same problem SOLID and FCL will
   store slightly different information (from slightly
   different collision points and normals and even
   different collision sets).

   PQP anc VCOLLIDE do not return the collision point
   but the pair of collising triangles. They do not
   return the normal at the conctact either. 
*/
typedef struct {
  boolean isLink1;        /**< TRUE if the first colliding object is a link. */
  unsigned int id1;       /**< Identifier of the first colliding object. This is
			       a linkID of a objectID, depending on isLink1. */
  boolean isLink2;        /**< TRUE if the second colliding object is a link. */
  unsigned int id2;       /**< Identifier of the second colliding object. This is
			       a linkID of a objectID, depending on isLink2. */
  double point[3];        /**< The contact point. In the global frame. */
  double normal[3];       /**< The normal at the contact point. In the global frame. */
  THTransform t1;         /**< Pose for the first object in collision */
  THTransform t2;         /**< Pose for the second object in collision */
} TCollisionInfo;

#ifdef _HAVE_SOLID

  /** 
     \brief Information of each object
  */
  typedef struct {
    unsigned int id;              /**< The identifier.*/
    unsigned int linkID;          /**< Identifier of the link for each part. */
    unsigned int bodyID;          /**< Identifier of the body for each part. If
				       NO_UINT the linkID refers to an 
				       obstacle. */
    DT_ShapeHandle shape;         /**< One shape per object. */
    DT_ObjectHandle handler;      /**< One handler per object. */
    DT_ResponseClass respClass;   /**< One resp class per object. */
    THTransform t;                /**< Last transform applied to this object
				       (without the correction). Used to collect
				       information on the collisions. */
    THTransform tc;               /**< Cache the transformation to align the 
				       geometry stored in the collision detector 
				       with the actual position.*/
    boolean correction;           /**< TRUE if t[i] is not the identity. */
  } TsolidObj;

  /** 
      \brief Information associated with the solid collision detection engine.
    
      Information associated with the solid collision detection engine.

      \sa TworldCD
  */
  typedef struct {
    DT_SceneHandle scene;         /**< The scene with all objects. */
    DT_RespTableHandle respTable; /**< Table with the response classes for the scene. */
    unsigned int np;              /**< Number of parts involved in the collision chekcking.*/
    TsolidObj *object;            /**< Information about the objects passed to Solid. */
    boolean simple;               /**< TRUE if we only want to determine whether or not
				       there is a collision, but not to collect information
				       about all collisions. */
    unsigned int nc;              /**< Number of collision detected in the last test. */ 
    unsigned int mc;              /**< Maximum space allocated to store collision info. */
    TCollisionInfo *collision;   /**< Information about the detected collisions. */
  } TsolidCD;
#endif


#ifdef _HAVE_VCOLLIDE
  /** 
      \brief Information associated with the Vcollide collision detection engine.
    
      Information associated with the Vcollide collision detection engine.

      \sa TworldCD
  */
  typedef struct {
    Tvcollide *vc;                /**< The Vcollide object provided by the C Vcollide interface. */
    unsigned int np;              /**< Number of bodies in the Vcollide object. */
    unsigned int *linkID;         /**< Link for each body. */
    unsigned int *bodyID;         /**< Number of this body in the link. */
    unsigned int *vcID;           /**< Identifier of the bodies in the Vcollide object. */
  } TvcollideCD;
#endif


#ifdef _HAVE_PQP
  /** 
      \brief Information associated with the PQP collision detection engine.
    
      Information associated with the PQP collision detection engine.

      \sa TworldCD
  */
  typedef struct {
    unsigned int np;              /**< Number of objects represented as PQP models. */
    unsigned int *linkID;         /**< Link for each body. */
    unsigned int *bodyID;         /**< Number of this body in the link. */
    Tpqp **model;                 /**< The PQP models. */
    unsigned int nPairs;          /**< Number of pairs to be checked for collision */
    unsigned int *p1;             /**< First element of the pairs to be checked for collision. */
    unsigned int *p2;             /**< Second element of the pairs to be checked for collision. */
  } TpqpCD;
#endif

#if _HAVE_FCL
  /** 
     \brief Information about each object passed to FCL.

     Information about each object passed to FCL.
  */
  typedef struct {
    unsigned int linkID;         /**< Link for each body. */
    unsigned int bodyID;         /**< Number of this body in the link. */
    unsigned int type;           /**< Type of FCL object. */
    void *model;                 /**< The FCL object handler. */
    THTransform t;               /**< Last transform applied to each object. */
    THTransform tc;              /**< Cache the transformation to align the 
				      geometry stored in the collision detector 
			              with the actual position.*/
  } TFCLObject;

  /** 
      \brief Information associated with the FCL collision detection libary.
    
      Information associated with the FCL collision detection library.

      \sa TworldCD
  */
  typedef struct {
    unsigned int np;              /**< Number of objects represented as FCL models. */
    TFCLObject *object;           /**< Objects passed to FCL. */
    unsigned int nPairs;          /**< Number of pairs to be checked for collision */
    unsigned int *p1;             /**< First element of the pairs to be checked for collision. */
    unsigned int *p2;             /**< Second element of the pairs to be checked for collision. */

    unsigned int nc;              /**< Number of collision detected in the last call. */
    unsigned int mc;              /**< Space allocated for collision info. */
    TCollisionInfo *collision;    /**< Collisions detected in the last call. */
  } TfclCD;
#endif


#if _HAVE_BULLET
 /** 
     \brief Information about each object passed to Bullet.

     Information about each object passed to Bullet.
  */
  typedef struct {
    void *bulletWorld;           /**< The Bullet world structre. */
    unsigned int linkID;         /**< Link for each body. */
    unsigned int bodyID;         /**< Number of this body in the link. */
    unsigned int type;           /**< Type of Bullet object. */
    void *model;                 /**< The Bullet object handler. */
    THTransform t;               /**< Last transform applied to each object. */
    THTransform tc;              /**< Cache the transformation to align the 
				      geometry stored in the collision detector 
			              with the actual position.*/
  } TBulletObject;

/** 
      \brief Information associated with the Bullet collision detection libary.
    
      Information associated with the Bullet collision detection library.

      \sa TworldCD
  */
  typedef struct {
    unsigned int np;              /**< Number of objects represented as FCL models. */
    void * bulletWorld;           /**< Bullet world structure. */
    TBulletObject *object;        /**< Objects passed to FCL. */
    unsigned int nPairs;          /**< Number of pairs to be checked for collision */
    unsigned int *p1;             /**< First element of the pairs to be checked for collision. */
    unsigned int *p2;             /**< Second element of the pairs to be checked for collision. */

    unsigned int nc;              /**< Number of collision detected in the last call. */
    unsigned int mc;              /**< Space allocated for collision info. */
    TCollisionInfo *collision;    /**< Collisions detected in the last call. */
  } TBulletCD;
#endif

#ifdef _HAVE_RIGIDCLL
  /** 
      \brief Information associated with the RigidCLL collision detection engine.
    
      Information associated with the RigidCLL collision detection engine.

      \sa TworldCD
  */
  typedef struct {
    TrigidCLL *r;                 /**< The RigidCLL object provided by the C RigidCLL interface. */
    unsigned int nl;              /**< Number of links. */
    unsigned int *objID;          /**< RigidCLL identifier assigned to each link/obstacle. */
    THTransform *t;               /**< Array of transforms for the rigids stored in the RigidCLL object. */
  } TrigidCLLCD;
#endif


/** 
    \brief Auxiliary data for the collision detection.

   Structure storing the data necessary for the collision detection 
   on Tworld structures (than include environtment and mechanism).

   Note that this collision detection is only used for a given solution point
   and is different from the collision avoidance based on separating planes.
*/
typedef struct {

  unsigned int engine;         /**< Engine being used for collision detection */

  #ifdef _HAVE_SOLID
    TsolidCD *solid;            /**< Information for the SOLID collision detection engine. */
  #else
    void *solid;              /**< Information for the SOLID collision detection engine. */
  #endif

  #ifdef _HAVE_VCOLLIDE
    TvcollideCD *vcollide;    /**< Information for the VCOLLIDE collision detection engine. */
  #else
    void *vcollide;           /**< Information for the VCOLLIDE collision detection engine. */
  #endif

  #ifdef _HAVE_PQP
    TpqpCD *pqp;              /**< Information for the PQP collision detection engine. */
  #else
    void *pqp;                /**< Information for the PQP collision detection engine. */
  #endif

  #ifdef _HAVE_FCL
    TfclCD *fcl;              /**< Information for the FCL collision detection library. */
  #else
    void *fcl;                /**< Information for the FCL collision detection library. */
  #endif

  #ifdef _HAVE_BULLET
    TBulletCD *bullet;        /**< Information for the Bullet collision detection library. */
  #else
    void *bullet;             /**< Information for the Bullet collision detection library. */
  #endif

  #ifdef _HAVE_RIGIDCLL
    TrigidCLLCD *rigidCLL;    /**< Information for the RigidCLL collision detection engine. */
  #else
    void *rigidCLL;           /**< Information for the RigidCLL collision detection engine. */
  #endif

} TworldCD;



/** 
   \brief Initializes the collision detector.

   Initializes the collision detector.

   \param engine The engine to use
   \param parallel TRUE if we are in a contex of parallel execution, where
                   different collision queries can be executed in parallel.
   \param m The machanism.
   \param e The enviroment.
   \param checkCollisionsLL Link-link collision to be checked.
   \param checkCollisionsLO Link-obstacle collision to be checked.
   \param cd The collision information to define.
*/
void InitCD(unsigned int engine,boolean parallel,
	    Tmechanism *m,Tenvironment *e,
	    boolean **checkCollisionsLL,boolean **checkCollisionsLO,
 	    TworldCD *cd);

/** 
    \brief Identifies links than can collide.

   Identifies links that can collide either with other links or with obstacles.

   \param l The identifier of the link to check.
   \param nl Number of links.
   \param no Number of obstacles.
   \param checkCollisionsLL Allowed collisions between links.
   \param checkCollisionsLO Allowed collisions between links and obstacles.

   \return TRUE if the link collision is activated with respect to any other link or obstacle.
*/
boolean LinkCanCollide(unsigned int l,unsigned int nl,unsigned int no,
		       boolean **checkCollisionsLL,boolean **checkCollisionsLO);

/** 
   \brief Identifies obstacles than can collide.

   Identifies obstacles that can collide a given link..

   \param o The identifier of the obstacle to check.
   \param nl Number of obstacles.
   \param checkCollisionsLO Allowed collisions between links and obstacles.

   \return TRUE if the obstacle collision is activated with respect to any link.
*/
boolean ObstacleCanCollide(unsigned int o,unsigned int nl,boolean **checkCollisionsLO);

/** 
   \brief Determines the collision engine.

   Determines the collision library used.

   \param cd The collision information to query.

   \return The identifier of the collision detection library in use.
*/
unsigned int GetCDEngine(TworldCD *cd);

/** 
   \brief Determines if there is a collision.

   Determines if there is a collision.

   \param all TRUE if we want to detect all the collision. FALSE just to detect
              the first one. Right now this flag is only honored when using
	      the Solid or the FCL collision libraries. The rest only detect
	      the first collision and stop irrespectively of the value of this
	      paramater.
   \param tl The transforms to apply to the links.
   \param def Deformation parameter. IMPORTANT: Up to now SOLID  is the only
              collision detection engine that uses the deformation.
   \param tlPrev The transforms to apply to the links in the previous
                 configuration. Only used for the continuous collision
		 checker (C_FCL). The rest of collision detection
		 libraries are discrete and ignore this parameter.
   \param defPrev Deformation parameter in the previous configuration.
   \param cd The collision information to use in the check.

   \todo Implement link deformation in CD engines other than SOLID. 
 
   \return TRUE if there is a collision.
*/
boolean CheckCollision(boolean all,
		       THTransform *tl,TLinkConf *def,
		       THTransform *tlPrev,TLinkConf *defPrev,
		       TworldCD *cd);

/** 
   \brief Stores the information collected during last collision check into a file.

   Stores information collected during last collision check into a file. This is only
   used from the \ref cuikmove.c "cuikmove" application, when using the "save" option.
   The information to be stored is collected during the collision detection and
   latter compleated in a call to \ref PrintCollisionInfo. In other words, this
   function can only be used after detecting a collision and after calling
   \ref PrintCollisionInfo. The \ref cuikmove.c "cuikmove" alrady coordinates
   these steps: it first uses \ref MoveWorldDOF and if the user press the "Save"
   button, it then calls this function.

   Up to now this only works for the SOLID collision engine.

   See \ref StoreCollisionInfoInt for more deatils.

   \param f File where to write the collision script.
   \param fname File from where we obtained the world information. The last
                part of the filename (from the last '_' to the end) is assumed
		to be the name of the object. This name is the one used to
		call the sub-matlab scripts giving contact points and normals
		on the object.
   \param objectID Identifier of the object being manipulated. This is
                   assumed to be a link. Use NO_UINT to print all the information
		   without any filtering.
   \param m The mechanism description.
   \param cd The collision information.
*/
void StoreCollisionInfo(FILE *f,char *fname,unsigned int objectID,Tmechanism *m,TworldCD *cd);

/** 
   \brief Prints some information collected during last collision check.

   Prints some information collected during last collision check. 

   Up to now this only works for the SOLID collision engine.

   This is used when obtain contact information while interactively
   moving the robots.

   \param tl The transforms positioning the links.
   \param m The mechanism description.
   \param e The environment description.
   \param cd The collision information.
*/
void PrintCollisionInfo(THTransform *tl,Tmechanism *m,Tenvironment *e,TworldCD *cd);

/** 
   \brief Collision information destructor.

   Releases the structures used for collision detection.

   \param cd The collision detection information to be released.
*/
void DeleteCD(TworldCD *cd);

#endif
