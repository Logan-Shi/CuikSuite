#ifndef CD_VCOLLIDEH
#define CD_VCOLLIDEH

/** \file cd_vcollide.h

    \brief Headers of the C interface for the vcollide collision detection engine.

    Headers of the C interface for the vcollide collision detection engine.

    \sa cd_vcollide.cpp
*/

#if _HAVE_VCOLLIDE

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
      \brief The Vcollide object.

      The vcollide object.
  */
  typedef void Tvcollide;

  /** 
      \brief Initializes a Vcollide object.

      Initializes a Vcollide object.

      \return The initialized object.
  */
  Tvcollide *InitVcollide();


  /** 
      \brief Adds a polyhedron to the vcollide object.

      Adds a polyhedron to the vcollide system. Note that vcollide only accepts triangulated geometry. So
      spsheres and cylinders need to be triangulated to send them to vcollide. This implies a reduction in
      the accuracy of the collision detection. Moreover, non-triangular faces of the polyhedron must be
      triangulated.

      \param v The vertexes of the polyhedron.
      \param nf Number of faces.
      \param nvf Number of vertices per face.
      \param fv The indexes of the vertexes forming each face.
      \param vc The vcollide object to modify.

      \return The identifier assigned to the new object.
  */
  unsigned int AddPolyhedron2Vcollide(double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv,Tvcollide *vc);

  /** 
      \brief Activates the collision between a pair of objects.

      Activates the collision between a pair of objects.

      \param o1 The identifier of the first object (as returned by \ref AddPolyhedron2Vcollide).
      \param o2 The identifier of the second object (as returned by \ref AddPolyhedron2Vcollide).
      \param vc The vcollide object to modify.
  */
  void ActivateCollisionsVcollide(unsigned int o1,unsigned int o2,Tvcollide *vc);

  /** 
      \brief Deactivates the collisions between a pair of object.

      Deactivates the collision between a pair of objects.

      \param o1 The identifier of the first object (as returned by \ref AddPolyhedron2Vcollide).
      \param o2 The identifier of the second object (as returned by \ref AddPolyhedron2Vcollide).
      \param vc The vcollide object to modify.
  */
  void DeactivateCollisionsVcollide(unsigned int o1,unsigned int o2,Tvcollide *vc);

  /** 
      \brief Moves a given v-collide object.

      Moves a vcollide object.

      \param o The identifier of the object (as returned by \ref AddPolyhedron2Vcollide).
      \param t The transform encoding the object motion.
      \param vc The vcollide object to modify.
  */
  void MoveVcollideObject(unsigned int o,THTransform *t,Tvcollide *vc);

  /** 
      \brief Test for collision.

      Test for collision.

      \param vc The vcollide object to use in the test.

      \return TRUE if there is a collision.
  */
  boolean VcollideTest(Tvcollide *vc);

  /** 
      \brief Deletes a given vcollide object.

      Deletes a given vcollide object.

      \param o The identifier of the object (as returned by \ref AddPolyhedron2Vcollide).
      \param vc The vcollide object to modify.
  */
  void DeleteVcollideObject(unsigned int o,Tvcollide *vc);

  /** 
      \brief Deletes a vcollide object.

      Deletes a vcollide object.

      \param vc The vcollide object to delete.
  */
  void DeleteVcollide(Tvcollide *vc);

#ifdef __cplusplus
}
#endif

#endif

#endif
