/** \file cd_rigidCLL.cpp

    \brief Implementation of the C interface for the rigidCLL collision detection engine.

    Implementation of the C interface for the rigidCLL collision detection engine.

    \sa cd_rigidCLL.h
*/

#if _HAVE_RIGIDCLL

#include "cd_rigidCLL.h"

#include <RigidCLL.h>

extern "C" {
#include "error.h"
}


TrigidCLL *InitRigidCLL()
{
  RigidCLL *r;

  r=new RigidCLL();

  return((TrigidCLL *)r);
}

unsigned int StartRigidCLLObject(TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;

  return(ro->NewRigid());
}

void AddFixedSphere2RigidCLL(unsigned int id,double *center,double rad,TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;

  ro->AddFixedAtom(id,center,rad);
}

void AddMobileSphere2RigidCLL(unsigned int id,double *center,double rad,TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;

  ro->AddAtom(id,center,rad);
}

void CloseRigidCLLObject(TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;
  
  ro->EndRigid();
}

void ActivateCollisionsRigidCLL(unsigned int nr1,unsigned int nr2,TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;

  ro->ActivateInteraction(nr1,nr2);
}

void DeactivateCollisionsRigidCLL(unsigned int nr1,unsigned int nr2,TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;
 
 ro->DeactivateInteraction(nr1,nr2);
}

boolean MoveAndCheckRigidCLL(THTransform *t,TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;

  if (ro->StericClash((RigidTransform*)t))
    return(TRUE);
  else
    return(FALSE);
}

void DeleteRigidCLL(TrigidCLL *r)
{
  RigidCLL *ro;
  
  ro=(RigidCLL *)r;

  delete ro;
}

#endif
