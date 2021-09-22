#ifndef CD_PQPH
#define CD_PQPH

/** \file cd_pqp.h

    \brief Headers of the C interface for the pqp collision detection engine.

    Headers of the C interface for the pqp collision detection engine.

    \sa cd_pqp.cpp
*/

#if _HAVE_PQP

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
      \brief The PQP object.

      The pqp object.
  */
  typedef void Tpqp;

  /** 
      \brief Adds a polyhedron to the pqp object.

      Adds a polyhedron to the pqp system. Note that pqp only accepts triangulated geometry. So
      spsheres and cylinders need to be triangulated to send them to pqp. This implies a reduction in
      the accuracy of the collision detection. Moreover, non-triangular faces of the polyhedron must be
      triangulated.

      \param v The vertexes of the polyhedron.
      \param nf Number of faces.
      \param nvf Number of vertices per face.
      \param fv The indexes of the vertexes forming each face.

      \return The identifier assigned to the new object.
  */
  Tpqp *DefinePQPModel(double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv);

  /** 
      \brief Test for collision.

      Test for collision.

      \param t1 The transform to apply to the first PQP model. NULL if no transform need to be applied.
      \param m1 The first PQP model.
      \param t2 The transform to apply to the second PQP model. NULL if no transform need to be applied.
      \param m2 The second PQP model.

      \return TRUE if there is a collision.
  */
  boolean PQPTest(THTransform *t1,Tpqp *m1,THTransform *t2,Tpqp *m2);

  /** 
      \brief Deletes a given PQP object.

      Deletes a given PQP object.

      \param m The PQP object to modify.
  */
  void DeletePQPModel(Tpqp *m);

#ifdef __cplusplus
}
#endif

#endif

#endif
