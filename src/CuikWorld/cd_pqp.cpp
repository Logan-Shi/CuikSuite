/** \file cd_pqp.cpp

    \brief Implementation of the C interface for the PQP collision detection engine.

    Implementation of the C interface for the PQP collision detection engine.

    \sa cd_pqp.h
*/

#if _HAVE_PQP

#include "cd_pqp.h"

#include <PQP/PQP.h>

extern "C" {
  #include "error.h"
}

Tpqp *DefinePQPModel(double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv)
{
  PQP_Model *m;
  unsigned int i,j,k;

  m=new(PQP_Model);

  m->BeginModel();

  k=0;
  for(i=0;i<nf;i++)
    {
      /* If the face has more then 3 vertexes, we trivially triangulate it.
         In this triangulation we assume the face to be convex. */
      if (nvf[i]<3)
	Error("Detected a face with less than 3 vertexes in DefinePQPModel");

      for(j=2;j<nvf[i];j++)
	{
	  m->AddTri(v[fv[i][0]],v[fv[i][j-1]],v[fv[i][j]],k);
	  k++;
	}
    }

  m->EndModel();

  return((Tpqp *)m);
}


boolean PQPTest(THTransform *t1,Tpqp *m1,THTransform *t2,Tpqp *m2)
{
  unsigned int i,j;
  PQP_Model *m1o,*m2o;
  PQP_CollideResult report;
  double R1[3][3]={{1,0,0},{0,1,0},{0,0,1}},T1[3]={0,0,0};
  double R2[3][3]={{1,0,0},{0,1,0},{0,0,1}},T2[3]={0,0,0};
  
  m1o=(PQP_Model *)m1;
  m2o=(PQP_Model *)m2;
  
  if (t1!=NULL)
    {
      for(i=0;i<3;i++)
	{
	  T1[i]=HTransformGetElement(i,AXIS_H,t1);
	  for(j=0;j<3;j++)
	    R1[i][j]=HTransformGetElement(i,j,t1);
	}
    }
  if (t2!=NULL)
    {
      for(i=0;i<3;i++)
	{
	  T2[i]=HTransformGetElement(i,AXIS_H,t2);
	  for(j=0;j<3;j++)
	    R2[i][j]=HTransformGetElement(i,j,t2);
	}
    }
  
  PQP_Collide(&report,R1,T1,m1o,R2,T2,m2o,PQP_FIRST_CONTACT);

  if (report.NumPairs()>0)
    return(TRUE);
  else
    return(FALSE);
}

void DeletePQPModel(Tpqp *m)
{
  PQP_Model *mo;
  
  mo=(PQP_Model *)m;

  delete mo;
}


#endif
