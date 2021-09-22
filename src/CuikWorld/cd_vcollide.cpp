/** \file cd_vcollide.cpp

    \brief Implementation of the C interface for the vcollide collision detection engine.

    Implementation of the C interface for the vcollide collision detection engine.

    \sa cd_vcollide.h
*/

#if _HAVE_VCOLLIDE

#include "cd_vcollide.h"

#include <VCollide.H>

extern "C" {
  #include "error.h"
}


Tvcollide *InitVcollide()
{
  VCollide *vc;

  vc=new(VCollide);

  return((Tvcollide *)vc);
}

unsigned int AddPolyhedron2Vcollide(double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv,Tvcollide *vc)
{
  int id;
  VCollide *vco;
  unsigned int i,j,k;

  vco=(VCollide *)vc;

  vco->NewObject(&id);

  k=0;
  for(i=0;i<nf;i++)
    {
      /* If the face has more then 3 vertexes, we trivially triangulate it.
         In this triangulation we assume the face to be convex. */
      if (nvf[i]<3)
	Error("Detected a face with less than 3 vertexes in AddPolyhedron2Vcollide");

      for(j=2;j<nvf[i];j++)
	{
	  vco->AddTri(v[fv[i][0]],v[fv[i][j-1]],v[fv[i][j]],k);
	  k++;
	}
    }

  vco->EndObject();

  return((unsigned int)id);
}

void ActivateCollisionsVcollide(unsigned int o1,unsigned int o2,Tvcollide *vc)
{
  VCollide *vco;
  
  vco=(VCollide *)vc;

  vco->ActivatePair((int)o1,(int)o2);
}

void DeactivateCollisionsVcollide(unsigned int o1,unsigned int o2,Tvcollide *vc)
{
  VCollide *vco;
  
  vco=(VCollide *)vc;

  vco->DeactivatePair((int)o1,(int)o2);
}

void MoveVcollideObject(unsigned int o,THTransform *t,Tvcollide *vc)
{
  VCollide *vco;
  
  vco=(VCollide *)vc;

  vco->UpdateTrans((int)o,*t);
}

boolean VcollideTest(Tvcollide *vc)
{
  VCollide *vco;
  VCReport report;
  
  vco=(VCollide *)vc;

  vco->Collide(&report,VC_FIRST_CONTACT);

  if (report.numObjPairs()>0)
    return(TRUE);
  else
    return(FALSE);
}

void DeleteVcollideObject(unsigned int o,Tvcollide *vc)
{
  VCollide *vco;
  
  vco=(VCollide *)vc;

  vco->DeleteObject((int)o);
}

void DeleteVcollide(Tvcollide *vc)
{
  VCollide *vco;
  
  vco=(VCollide *)vc;

  delete vco;
}

#endif
