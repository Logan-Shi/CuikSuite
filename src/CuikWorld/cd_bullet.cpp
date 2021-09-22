/** \file cd_bullet.cpp

    \brief Implementation of the C interface for the Bullet collision detection library.

    Implementation of the C interface for the Bullet collision detection library.

    \sa cd_bullet.h
*/

#if _HAVE_BULLET

#include "cd_bullet.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"

#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#ifdef _HAVE_HACD
  #if (USE_HACD)
    #include "HACD/hacdHACD.h"
  #else
    #include "BulletCollision/Gimpact/btGImpactShape.h"
    #include "BulletCollision/Gimpact/btCompoundFromGimpact.h"
  #endif
#else
  #include "BulletCollision/Gimpact/btGImpactShape.h"
  #include "BulletCollision/Gimpact/btCompoundFromGimpact.h"
#endif

#pragma GCC diagnostic pop

extern "C" {
  #include "error.h"
}

/**
   \brief The world collision structure.

   The world collision structure and related information.
*/
typedef struct {
  btCollisionWorld *w; /**< The Bullet world collision structure. */
  boolean cont;        /**< TRUE if we need to perform continuous collision detection. */
} TBulletInt;

/**
   \brief Callback called by Bullet when a collsion is detected.

   Callback called by Bullet when a collision is detected using the contactPairTest method.
*/
struct ContactCallback:public btCollisionWorld::ContactResultCallback {

  boolean info;     /**< TRUE if we have to store contact information. */
  unsigned int nc;  /**<  The number of detected contacts. */
  double point[3];  /**< The (last) contact point. */
  double normal[3]; /**< The (last) contact normal. */

  /**
      \brief Constructor.

      Constructor.

      \param i TRUE if we have to record the collision information.
  */
  ContactCallback(boolean i):btCollisionWorld::ContactResultCallback()
  { 
    nc=0; 
    info=i;
  }
 
  /** 
     \brief Method called when a collision is detected.

     The actual callback called when a collision is detected.

     \param cp The contact point.
     \param colObj0 First colliding object.
     \param partId0 part ID?
     \param index0 index?
     \param colObj1 Second colliding object.
     \param partId1 part ID?
     \param index1 index?

     \return An unused value.
  */
  virtual btScalar addSingleResult(btManifoldPoint& cp,
				   const btCollisionObjectWrapper* colObj0,int partId0,int index0,
				   const btCollisionObjectWrapper* colObj1,int partId1,int index1)
  {
    /* store the contact point and the normal (only of the last detected point) */
    if (info)
      {
	unsigned int i;

	for(i=0;i<3;i++)
	  {
	    point[i]=cp.m_positionWorldOnB[i];
	    normal[i]=cp.m_normalWorldOnB[i];
	  }
      }

    nc++; /* we detected one contact more */

    return(0); /* apparently not used */
  }
};


void *InitBulletWorld(boolean cont)
{
  btDefaultCollisionConfiguration *collisionConfiguration=new btDefaultCollisionConfiguration();
  btCollisionDispatcher *dispatcher=new btCollisionDispatcher(collisionConfiguration);
  /* AABB broadphase */
  btBroadphaseInterface *broadphase=new btDbvtBroadphase();

  TBulletInt *b=new TBulletInt;

  b->w=new btCollisionWorld(dispatcher,broadphase,collisionConfiguration);
  b->cont=cont;

  return((void*)b);
}

void *DefineBulletSphere(boolean fixed,double r)
{
  btSphereShape *sphere=new btSphereShape(r);

  btCollisionObject *o=new btCollisionObject();

  o->setCollisionShape(sphere);

  if (fixed)
    o->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

  return((void*)o);
}

void *DefineBulletCylinder(boolean fixed,double r,double l)
{
  btCylinderShapeX *cylinder=new btCylinderShapeX(btVector3(l,r,r));

  btCollisionObject *o=new btCollisionObject();

  o->setCollisionShape(cylinder);
  if (fixed)
    o->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

  return((void*)o);
}

void *DefineBulletMesh(boolean fixed,unsigned int nv,double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv)
{
#if (ASSUME_CONVEX)
  unsigned int i;

  btConvexHullShape *hull=new btConvexHullShape();

  for(i=0;i<nv;i++)
    {
      btScalar a1=btScalar(v[i][0]);
      btScalar a2=btScalar(v[i][1]);
      btScalar a3=btScalar(v[i][2]);
      btVector3 pt(a1,a2,a3);
      hull->addPoint(pt,(i==(nv-1)));
    }

  btCollisionObject *o=new btCollisionObject();

  #if (0)
    // define a simplified hull-> get the hull of the hull
    btShapeHull *shapeHull=new btShapeHull(hull);
    shapeHull->buildHull(0);
    btConvexHullShape* shull=new btConvexHullShape((btScalar*)shapeHull->getVertexPointer(),shapeHull->numVertices());

    shull->setMargin(0);

    o->setCollisionShape(shull);
  #else
    /* let's assume that the user already simplified the mesh if desired */
    /* We have to set a negative margin to objects to enforc them to be in contact */
    hull->setMargin(-0.15);
    o->setCollisionShape(hull);
  #endif

  if (fixed)
    o->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
  
  return((void*)o);
#else
  #if (USE_HACD)
    /* convex decomposition code taken from the Bullet ConvexDecompsitionDemo */
    /* This is completely impractical for large problems */

    std::vector< HACD::Vec3<HACD::Real> > points;
    std::vector< HACD::Vec3<long> > triangles;

    for(unsigned int i=0; i<nv; i++ ) 
      {
	HACD::Vec3<HACD::Real> vertex(HACD::Real(v[i][0]),HACD::Real(v[i][1]),HACD::Real(v[i][2]));
	points.push_back(vertex);
      }

    for(unsigned int i=0;i<nf;i++)
      {
	for(unsigned int j=2;j<nvf[i];j++)
	  {
	    HACD::Vec3<long> triangle(long(fv[i][0]),long(fv[i][j-1]),long(fv[i][j]));
	    triangles.push_back(triangle);
	  }
      }

    HACD::HACD myHACD;
    myHACD.SetPoints(&points[0]);
    myHACD.SetNPoints(points.size());
    myHACD.SetTriangles(&triangles[0]);
    myHACD.SetNTriangles(triangles.size());
    myHACD.SetCompacityWeight(0.1);
    myHACD.SetVolumeWeight(0.0);

    // HACD parameters
    // Recommended parameters: 2 100 0 0 0 0
    myHACD.SetNClusters(2);                     // minimum number of clusters
    myHACD.SetNVerticesPerCH(100);              // max of 100 vertices per convex-hull
    myHACD.SetConcavity(100);                   // maximum concavity
    myHACD.SetAddExtraDistPoints(false);   
    myHACD.SetAddNeighboursDistPoints(false);   
    myHACD.SetAddFacesPoints(false);

    fprintf(stderr,"computing hacd (%u)\n",nv);fflush(stderr);


    myHACD.Compute();
    size_t nClusters=myHACD.GetNClusters();	

    fprintf(stderr,"computed hacd\n");fflush(stderr);

    btCompoundShape *compound=new btCompoundShape();
    btTransform trans;
    trans.setIdentity();

    for (unsigned int c=0;c<nClusters;c++)
      {
	//generate convex result
	size_t nPoints=myHACD.GetNPointsCH(c);
	size_t nTriangles=myHACD.GetNTrianglesCH(c);

	btScalar *vertices=new btScalar[nPoints*3];
	int *triangles=new int[nTriangles*3];
				
	HACD::Vec3<HACD::Real> *pointsCH=new HACD::Vec3<HACD::Real>[nPoints];
	HACD::Vec3<long> *trianglesCH=new HACD::Vec3<long>[nTriangles];
	myHACD.GetCH(c,pointsCH,trianglesCH);

	// points
	for(size_t v=0;v<nPoints;v++)
	  {
	    vertices[3*v]=pointsCH[v].X();
	    vertices[3*v+1]=pointsCH[v].Y();
	    vertices[3*v+2]=pointsCH[v].Z();
	  }

	// triangles
	for(size_t f=0;f<nTriangles;f++)
	  {
	    triangles[3*f]=trianglesCH[f].X();
	    triangles[3*f+1]=trianglesCH[f].Y();
	    triangles[3*f+2]=trianglesCH[f].Z();
	  }

	delete [] pointsCH;
	delete [] trianglesCH;

	btTriangleIndexVertexArray *indexVertexArrays=new btTriangleIndexVertexArray(nTriangles,triangles,3*sizeof(int),nPoints,vertices,3*sizeof(btScalar));
	btConvexTriangleMeshShape *convexShape=new btConvexTriangleMeshShape(indexVertexArrays);
           
	compound->addChildShape(trans,convexShape);
      }

    btCollisionObject *o=new btCollisionObject();

    o->setCollisionShape(compound);
    if (fixed)
      o->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

    return((void*)o);
  #else
  
    btScalar vertex[3*nv];
    unsigned int i,j,k,nt;

    /* Use a simple procedure to define a composed collision shape, one that does not requires the
       Bullet extra libraries. In this procedure each triangle is transformed into a small
       tetrahedron and all the tetrahedra define a composed shape. */

    /* transform from double to btScalar and store in an array */
    k=0;
    for(i=0;i<nv;i++)
      {
	for(j=0;j<3;j++)
	  vertex[k++]=btScalar(v[i][j]);
      }
  
    /* Triangulate the faces in a simple way (typically they are already triangulated) */
    nt=0; /* number of triangles */
    for(i=0;i<nf;i++)
      nt+=(nvf[i]-2);

    int triangle[3*nt];
  
    /* We assume that the faces are convex and easy to triangulate (if not
       triangles already) */
    k=0;
    for(i=0;i<nf;i++)
      {
	for(j=2;j<nvf[i];j++)
	  {
	    triangle[k++]=fv[i][0];
	    triangle[k++]=fv[i][j-1];
	    triangle[k++]=fv[i][j];
	  }
      }
 
    btTriangleIndexVertexArray *indexVertexArrays=new btTriangleIndexVertexArray(nt,triangle,3*sizeof(int),nv,vertex,3*sizeof(btScalar));
    btGImpactMeshShape *trimesh=new btGImpactMeshShape(indexVertexArrays);

    trimesh->updateBound(); 

    btCollisionShape *mesh=btCreateCompoundFromGimpactShape(trimesh,0.00001);

    mesh->setMargin(0);

    btCollisionObject *o=new btCollisionObject();

    o->setCollisionShape(mesh);
    if (fixed)
      o->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

    return((void*)o);

  #endif
#endif
}

boolean BulletTest(boolean info,
		   void *h1,THTransform *tr1,
		   void *h2,THTransform *tr2,
		   double *point,double *normal,
		   void *cw)
{
  TBulletInt *bw;
  btCollisionObject *o1,*o2;
  btMatrix3x3 r1(HTransformGetElement(0,0,tr1),HTransformGetElement(0,1,tr1),HTransformGetElement(0,2,tr1),
		 HTransformGetElement(1,0,tr1),HTransformGetElement(1,1,tr1),HTransformGetElement(1,2,tr1),
		 HTransformGetElement(2,0,tr1),HTransformGetElement(2,1,tr1),HTransformGetElement(2,2,tr1));
  btVector3 t1(HTransformGetElement(0,3,tr1),HTransformGetElement(1,3,tr1),HTransformGetElement(2,3,tr1));
  btMatrix3x3 r2(HTransformGetElement(0,0,tr2),HTransformGetElement(0,1,tr2),HTransformGetElement(0,2,tr2),
		 HTransformGetElement(1,0,tr2),HTransformGetElement(1,1,tr2),HTransformGetElement(1,2,tr2),
		 HTransformGetElement(2,0,tr2),HTransformGetElement(2,1,tr2),HTransformGetElement(2,2,tr2));
  btVector3 t2(HTransformGetElement(0,3,tr2),HTransformGetElement(1,3,tr2),HTransformGetElement(2,3,tr2));
  ContactCallback resultCB(info);
      
  bw=(TBulletInt*)cw;

  if (bw->cont)
    Error("Using BulletTest with a non-continuous collision Bullet init");

  o1=(btCollisionObject*)h1;
  o2=(btCollisionObject*)h2;

  o1->getWorldTransform().setBasis(r1);
  o1->getWorldTransform().setOrigin(t1);
  
  o2->getWorldTransform().setBasis(r2);
  o2->getWorldTransform().setOrigin(t2);
  
  bw->w->contactPairTest(o1,o2,resultCB);

  if ((info)&&(resultCB.nc>0))
    {
      unsigned int i;
      
      for(i=0;i<3;i++)
	{
	  point[i]=resultCB.point[i];
	  normal[i]=resultCB.normal[i];
	}
    }
      
  return(resultCB.nc>0);
}

boolean BulletCTest(void *h1,THTransform *tr1,THTransform *tr2,
		    void *h2,THTransform *tr3,THTransform *tr4,
		    void *cw)
{
  Error("BulletCTest not implemented yet");
  return(false);
}

void DeleteBulletObject(void *h)
{
  btCollisionObject *o;

  o=(btCollisionObject*)h;

  delete o;
}

void DeleteBulletWorld(void *cw)
{
  TBulletInt *bw;

  bw=(TBulletInt*)cw;

  delete bw->w;
  delete bw;
}

#endif
