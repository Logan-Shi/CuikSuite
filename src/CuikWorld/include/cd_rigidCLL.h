#ifndef CD_RIGIDCLLH
#define CD_RIGIDCLLH

/** \file cd_rigidCLL.h

    \brief Headers of the C interface for the rigidCLL collision detection engine.

    Headers of the C interface for the rigidCLL collision detection engine.

    \sa cd_rigidCLL.cpp
*/

#if _HAVE_RIGIDCLL

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
      \brief The RigidCLL object.

      The rigidCLL object.
  */
  typedef void TrigidCLL;

  /** 
      \brief Initializes a RigidCLL object.

      Initializes a RigidCLL object.

      \return The initialized object.
  */
  TrigidCLL *InitRigidCLL();

  /** 
      \brief Starts a rigid.

      Start the definition of a rigid group of atoms in the rigidCLL structure.

      \param r The RigidCLL structure.

      \return The internal identifier assigned ot the rigid. The identifiers start
              at 1 since 0 is reserved for the \e fixed rigid.
  */
  unsigned int StartRigidCLLObject(TrigidCLL *r);

  /** 
      \brief Adds an atom at a fixed position.

      Adds an atom that will neve move during query. This kink of atoms
      can be added at any moment.

      \param id The identifier of the atom.
      \param center The center of the atom.
      \param rad  The radius of the atom.
      \param r The RigidCLL structure.
  */
  void AddFixedSphere2RigidCLL(unsigned int id,double *center,double rad,TrigidCLL *r);

  /** 
      \brief Adds an atom to a rigid.

      Adds an atom to the rigid that is under definition
      (see \ref StartRigidCLLObject and \ref CloseRigidCLLObject).

      \param id The identifier of the atom.
      \param center The center of the atom.
      \param rad  The radius of the atom.
      \param r The RigidCLL structure.
  */
  void AddMobileSphere2RigidCLL(unsigned int id,double *center,double rad,TrigidCLL *r);

    /** 
      \brief Closes a rigid.

      Concludes the definition of a rigid group of atoms in the rigidCLL structure.

      \param r The RigidCLL structure.
  */
  void CloseRigidCLLObject(TrigidCLL *r);

  /** 
      \brief Activates collision.

      Activates the collision between a given pair of rigid objects.
      This function has to be called after using \ref WarmUpRigidCLL and
      before the collision check. Note that \ref WarmUpRigidCLL activates
      all the collisions, but they can be deactivated using 
      \ref DeactivateCollisionsRigidCLL.
      
      \param nr1 Identifier of the first object as returned by \ref StartRigidCLLObject,
                 or 0 to indicate the \e fixed object.
      \param nr2 Identifier of the second object as returned by \ref StartRigidCLLObject,
                 or 0 to indicate the \e fixed object.
      \param r The RigidCLL structure.
  */
  void ActivateCollisionsRigidCLL(unsigned int nr1,unsigned int nr2,TrigidCLL *r);

  /** 
      \brief Deactivates collision.

      Deactivates the collision between a given pair of rigid objects.
      This function has to be called after using \ref WarmUpRigidCLL and
      before the collision check. Note that \ref WarmUpRigidCLL activates
      all the collisions.
      
      \param nr1 Identifier of the first object as returned by \ref StartRigidCLLObject,
                 or 0 to indicate the \e fixed object.
      \param nr2 Identifier of the second object as returned by \ref StartRigidCLLObject,
                 or 0 to indicate the \e fixed object.
      \param r The RigidCLL structure.
  */
  void DeactivateCollisionsRigidCLL(unsigned int nr1,unsigned int nr2,TrigidCLL *r);

  /** 
      \brief RigidCLL collision check.

      Moves the rigids using the provided transforms and checks if there is a collision between
      then (taking into accoun the activated/deactivated collisions).

      \param t The tarnsforms to move the rigids. One transform for each rigid object with the
               encoding returned by \ref StartRigidCLLObject.
      \param r The RigidCLL structure.

      \return TRUE if there is a collision between the rigids.
  */
  boolean MoveAndCheckRigidCLL(THTransform *t,TrigidCLL *r);

  /** 
      \brief Deletes a rigidCLL object.

      Deletes a rigidCLL object.

      \param vc The rigidCLL object to delete.
  */
  void DeleteRigidCLL(TrigidCLL *vc);

#ifdef __cplusplus
}
#endif

#endif

#endif
