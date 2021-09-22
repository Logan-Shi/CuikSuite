#ifndef CD_BULLETH
#define CD_BULLETH

/** \file cd_bullet.h

    \brief Headers of the C interface for the Bullet collision detection library.

    Headers of the C interface for the Bullet collision detection library.

    \sa cd_bullet.cpp
*/

#if _HAVE_BULLET

#ifdef __cplusplus
extern "C" {
#endif
  #include "htransform.h"
  #include "boolean.h"
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif


  /** 
     \brief If set, all given objects are assumed convex.

     If set, we assume that all the objects given for collision detection
     are convex. This is the case many of our examples and it largely
     simplifies the code.

     Be aware that this option is set by default, which means that
     using Bullet as a collision detection can lead to errors
     in some cases (non convex bodies).
  */
  #define ASSUME_CONVEX 1

  /** 
     \brief Use HACD for convex decomposition.

     Bullet needs the convex decomposition of all non-convex objects.
     If this is set to 1 HACD (part of the extra libraries in Bullet) is
     used to perform this decomposition.

     This procedure is sound but no efficient in large objects (with
     large sets of vertices).

     Note that this is only used if ASSUME_CONVEX is 0.
  */
  #define USE_HACD 0

  /** 
      \brief One of the basic objects in Bullet library.
      
      One of the basic objects in Bullet library: A sphere.
  */
  #define BULLET_SPHERE   0

  /** 
      \brief One of the basic objects in Bullet library.
      
      One of the basic objects in Bullet library: A cylinder.
  */
  #define BULLET_CYLINDER 1

  /** 
      \brief One of the basic objects in Bullet library.
      
      One of the basic objects in Bullet library: A general mesh.
  */
  #define BULLET_MESH     2

  /** 
     \brief Initializes the Bullet internal structures.

     Initializes a Bulled collision detection world structure.
     This only has to be called once, for instance when defining
     the collision model.

     \param cont TRUE if we want to perform continuous collision detection.

     \return The world structure to pass latter on to \ref BulletTest
             or \ref BulletCTest.
  */
  void *InitBulletWorld(boolean cont);

  /** 
      \brief Defines a Bullet-sphere object.

      Defines a Bullet-sphere object

      \param fixed TRUE if the sphere will never move.
      \param r The radius of the sphere.

      \return A pointer to the new Bullet sphere object.
  */
  void *DefineBulletSphere(boolean fixed,double r);

  /** 
      \brief Defines a Bullet-cylinder object.

      Defines a Bullet-cylinder object. The cylinder is
      zero-centered and aligned with the Z axis.

      \param fixed TRUE if the sphere will never move.
      \param r The radius of the cylinder.
      \param l The length of the sphere.

      \return A pointer to the new Bullet cylinder object.
  */
  void *DefineBulletCylinder(boolean fixed,double r,double l);

  /** 
      \brief Defines a Bullet-mesh object.

      Defines a Bullet-mesh object

      \param fixed TRUE if the sphere will never move.
      \param nv The number of vertexes.
      \param v The vertexes of the polyhedron.
      \param nf Number of faces.
      \param nvf Number of vertices per face.
      \param fv The indexes of the vertexes forming each face.

      \return A pointer to the new Bullet mesh object.
  */
  void *DefineBulletMesh(boolean fixed,unsigned int nv,double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv);

  /** 
      \brief Test for discrete collision.

      Moves two Bullet objects and test for its possible collision.

      \param info TRUE if we want to get information about the possible collision. 
                  FALSE just to detect if. Currently we assume that there is only
		  one collision between each pair of objects.
      \param h1 Handler to the first object (pointer obtained when creating it).
      \param tr1 Transform to move the first object.
      \param h2 Handler to the second object (pointer obtained when creating it).
      \param tr2 Transform to move the second object.
      \param point Collision point. Only used if 'info' is TRUE.
      \param normal Normat at the collision. Only used if 'info' is TRUE.
      \param cw The pointer returned by \ref InitBullet.

      \return TRUE if the two objects are in collision.
  */
  boolean BulletTest(boolean info,
		     void *h1,THTransform *tr1,
		     void *h2,THTransform *tr2,
		     double *point,double *normal,
		     void *cw);

  /** 
      \brief Test for continuous collision.

      Test the possible interference between to objects when moving between two
      given positions.

      \param h1 Handler to the first object (pointer obtained when creating it).
      \param tr1 Transform giving the inital configuration for the first object.
      \param tr2 Transform giving the final configuration for the first object.
      \param h2 Handler to the second object (pointer obtained when creating it).
      \param tr3 Transform giving the inital configuration for the second object.
      \param tr4 Transform giving the final configuration for the second object.
      \param cw The pointer returned by \ref InitBullet.
      
      \return TRUE if the two objects are in collision along the trajectory.
  */
  boolean BulletCTest(void *h1,THTransform *tr1,THTransform *tr2,
		      void *h2,THTransform *tr3,THTransform *tr4,
		      void *cw);

  /** 
      \brief Deletes a Bullet object.

      \param h Handler to the object to delete (pointer obtained when creating it).
  */
  void DeleteBulletObject(void *h);

  /** 
     \brief Deletes a Bulled structure.

     Deletes a Bulled structure created with \ref InitBulletWorld.

     \param cw The pointer returned by \ref InitBulletWorld.
  */
  void DeleteBulletWorld(void *cw);


#ifdef __cplusplus
}
#endif

#endif

#endif
