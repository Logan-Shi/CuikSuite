#ifndef CD_FCLH
#define CD_FCLH

/** \file cd_fcl.h

    \brief Headers of the C interface for the FCL collision detection library.

    Headers of the C interface for the FCL collision detection library.

    \sa cd_fcl.cpp
*/

#if _HAVE_FCL

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
      \brief One of the basic objects in FCL library.
      
      One of the basic objects in FCL library: A sphere.
  */
  #define FCL_SPHERE   0

  /** 
      \brief One of the basic objects in FCL library.
      
      One of the basic objects in FCL library: A cylinder.
  */
  #define FCL_CYLINDER 1

  /** 
      \brief One of the basic objects in FCL library.
      
      One of the basic objects in FCL library: A general mesh.
  */
  #define FCL_MESH     2

  /** 
      \brief Defines a FCL-sphere object.

      Defines a FCL-sphere object

      \param r The radius of the sphere.

      \return A pointer to the new FCL sphere object.
  */
  void *DefineFCLSphere(double r);

  /** 
      \brief Defines a FCL-cylinder object.

      Defines a FCL-cylinder object. The cylinder is
      zero-centered and aligned with the Z axis.

      \param r The radius of the cylinder.
      \param l The length of the sphere.

      \return A pointer to the new FCL cylinder object.
  */
  void *DefineFCLCylinder(double r,double l);

  /** 
      \brief Defines a FCL-mesh object.

      Defines a FCL-mesh object

      \param nv The number of vertexes.
      \param v The vertexes of the polyhedron.
      \param nf Number of faces.
      \param nvf Number of vertices per face.
      \param fv The indexes of the vertexes forming each face.

      \return A pointer to the new FCL mesh object.
  */
  void *DefineFCLMesh(unsigned int nv,double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv);

  /** 
      \brief Test for discrete collision.

      Moves two FCL objects and test for its possible collision.

      \param info TRUE if we want to get information about the possible collision. 
                  FALSE just to detect if. Currently we assume that there is only
		  one collision between each pair of objects.
      \param h1 Handler to the first object (pointer obtained when creating it).
      \param tr1 Transform to move the first object.
      \param h2 Handler to the second object (pointer obtained when creating it).
      \param tr2 Transform to move the second object.
      \param point Collision point. Only used if 'info' is TRUE.
      \param normal Normat at the collision. Only used if 'info' is TRUE.

      \return TRUE if the two objects are in collision.
  */
  boolean FCLTest(boolean info,
		  void *h1,THTransform *tr1,
		  void *h2,THTransform *tr2,
		  double *point,double *normal);

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
      
      \return TRUE if the two objects are in collision along the trajectory.
  */
  boolean FCLCTest(void *h1,THTransform *tr1,THTransform *tr2,
		   void *h2,THTransform *tr3,THTransform *tr4);

  /** 
      \brief Deletes a FCL object.

      \param h Handler to the object to delete (pointer obtained when creating it).
  */
  void DeleteFCLObject(void *h);

#ifdef __cplusplus
}
#endif

#endif

#endif
