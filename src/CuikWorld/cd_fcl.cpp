/** \file cd_fcl.cpp

    \brief Implementation of the C interface for the FCL collision detection library.

    Implementation of the C interface for the FCL collision detection library.

    \sa cd_fcl.h
*/

#if _HAVE_FCL

#include "cd_fcl.h"

#include "fcl/config.h"


#if FCL_MINOR_VERSION==5
  #include "fcl/shape/geometric_shapes.h"
  #include "fcl/traversal/traversal_node_bvhs.h"
  #include "fcl/collision.h"
  #include "fcl/continuous_collision.h"

  using namespace fcl;

  void *DefineFCLSphere(double r)
  {
    Sphere *h=new Sphere(r);
  
    return((void *)h);
  }

  void *DefineFCLCylinder(double r,double l)
  {
    Cylinder *h=new Cylinder(r,l);

    return((void *)h);
  }  

  void *DefineFCLMesh(unsigned int nv,double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv)
  {
    BVHModel<RSS> *h;
    std::vector<Vec3f> vert;
    std::vector<Triangle> triang;
    unsigned int i,j;

    vert.clear();
    for(i=0;i<nv;i++)
      vert.push_back(Vec3f(v[i][0],v[i][1],v[i][2]));

    triang.clear();
    for(i=0;i<nf;i++)
      {
	/* Triangulate the faces */
	for(j=1;j<nvf[i]-1;j++)
	  triang.push_back(Triangle(fv[i][0],fv[i][j],fv[i][j+1]));
      }

    h=new BVHModel<RSS>;
    h->beginModel();
    h->addSubModel(vert,triang);
    h->endModel();

    return((void *)h);
  }

  boolean FCLTest(boolean info,
		  void *h1,THTransform *tr1,
		  void *h2,THTransform *tr2,
		  double *point,double *normal)
  {
    /* request -> capture the first collision between these objects */
    CollisionRequest request(1,true);
    CollisionResult result;

    Matrix3f r1(HTransformGetElement(0,0,tr1),HTransformGetElement(0,1,tr1),HTransformGetElement(0,2,tr1),
		HTransformGetElement(1,0,tr1),HTransformGetElement(1,1,tr1),HTransformGetElement(1,2,tr1),
		HTransformGetElement(2,0,tr1),HTransformGetElement(2,1,tr1),HTransformGetElement(2,2,tr1));

    Vec3f d1(HTransformGetElement(0,3,tr1),HTransformGetElement(1,3,tr1),HTransformGetElement(2,3,tr1));
    Transform3f pose1(r1,d1);
  
    Matrix3f r2(HTransformGetElement(0,0,tr2),HTransformGetElement(0,1,tr2),HTransformGetElement(0,2,tr2),
		HTransformGetElement(1,0,tr2),HTransformGetElement(1,1,tr2),HTransformGetElement(1,2,tr2),
		HTransformGetElement(2,0,tr2),HTransformGetElement(2,1,tr2),HTransformGetElement(2,2,tr2));

    Vec3f d2(HTransformGetElement(0,3,tr2),HTransformGetElement(1,3,tr2),HTransformGetElement(2,3,tr2));
    Transform3f pose2(r2,d2);
  
    unsigned int nc;
  
    collide((CollisionGeometry *)h1,pose1,(CollisionGeometry *)h2,pose2,request,result);

    nc=result.numContacts();

    if ((info)&&(nc>0))
      {
	unsigned int k;
	Contact c;

	/* Typically a contact is detected as a set of
	   contact points. We just get the first one. 
	   We could also compute the average... */
	c=result.getContact(0);
	for(k=0;k<3;k++)	
	  {
	    point[k]=c.pos[k];
	    normal[k]=c.normal[k];
	  }
      }

    return(nc>0);
  }

  boolean FCLCTest(void *h1,THTransform *tr1,THTransform *tr2,
		   void *h2,THTransform *tr3,THTransform *tr4)
  {
    ContinuousCollisionRequest request;
    ContinuousCollisionResult result;

    Matrix3f r1(HTransformGetElement(0,0,tr1),HTransformGetElement(0,1,tr1),HTransformGetElement(0,2,tr1),
		HTransformGetElement(1,0,tr1),HTransformGetElement(1,1,tr1),HTransformGetElement(1,2,tr1),
		HTransformGetElement(2,0,tr1),HTransformGetElement(2,1,tr1),HTransformGetElement(2,2,tr1));
    Vec3f d1(HTransformGetElement(0,3,tr1),HTransformGetElement(1,3,tr1),HTransformGetElement(2,3,tr1));

    Transform3f pose1(r1,d1);
  
    Matrix3f r2(HTransformGetElement(0,0,tr2),HTransformGetElement(0,1,tr2),HTransformGetElement(0,2,tr2),
		HTransformGetElement(1,0,tr2),HTransformGetElement(1,1,tr2),HTransformGetElement(1,2,tr2),
		HTransformGetElement(2,0,tr2),HTransformGetElement(2,1,tr2),HTransformGetElement(2,2,tr2));
    Vec3f d2(HTransformGetElement(0,3,tr2),HTransformGetElement(1,3,tr2),HTransformGetElement(2,3,tr2));
    Transform3f pose2(r2,d2);

    Matrix3f r3(HTransformGetElement(0,0,tr3),HTransformGetElement(0,1,tr3),HTransformGetElement(0,2,tr3),
		HTransformGetElement(1,0,tr3),HTransformGetElement(1,1,tr3),HTransformGetElement(1,2,tr3),
		HTransformGetElement(2,0,tr3),HTransformGetElement(2,1,tr3),HTransformGetElement(2,2,tr3));
    Vec3f d3(HTransformGetElement(0,3,tr3),HTransformGetElement(1,3,tr3),HTransformGetElement(2,3,tr3));
    Transform3f pose3(r3,d3);
  
    Matrix3f r4(HTransformGetElement(0,0,tr4),HTransformGetElement(0,1,tr4),HTransformGetElement(0,2,tr4),
		HTransformGetElement(1,0,tr4),HTransformGetElement(1,1,tr4),HTransformGetElement(1,2,tr4),
		HTransformGetElement(2,0,tr4),HTransformGetElement(2,1,tr4),HTransformGetElement(2,2,tr4));
    Vec3f d4(HTransformGetElement(0,3,tr4),HTransformGetElement(1,3,tr4),HTransformGetElement(2,3,tr4));
    Transform3f pose4(r4,d4);

    continuousCollide((CollisionGeometry *)h1,pose1,pose2,(CollisionGeometry *)h2,pose3,pose4,request,result);

    return(result.is_collide);
  }

  void DeleteFCLObject(void *h)
  {
    delete (CollisionGeometry *)h;
  }

#else

  // Assuming fcl version 0.6.0
  // This version is templated (such radical changes from version 0.5 to 0.6 are not reasonable)

  #include "fcl/fcl.h"

  using namespace fcl;

  void *DefineFCLSphere(double r)
  {
    Sphere<double> *h=new Sphere<double>((double)r);
  
    return((void *)h);
  }

  void *DefineFCLCylinder(double r,double l)
  {
    Cylinder<double> *h=new Cylinder<double>((double)r,(double)l);

    return((void *)h);
  }

  void *DefineFCLMesh(unsigned int nv,double **v,unsigned int nf,unsigned int *nvf,unsigned int **fv)
  {
    BVHModel<RSS<double>> *h;
    std::vector<Vector3<double>> vert;
    std::vector<Triangle> triang;
    unsigned int i,j;

    vert.clear();
    for(i=0;i<nv;i++)
      vert.push_back(Vector3<double>(v[i][0],v[i][1],v[i][2]));

    triang.clear();
    for(i=0;i<nf;i++)
      {
	/* Triangulate the faces */
	for(j=1;j<nvf[i]-1;j++)
	  triang.push_back(Triangle(fv[i][0],fv[i][j],fv[i][j+1]));
      }

    h=new BVHModel<RSS<double>>;
    h->beginModel();
    h->addSubModel(vert,triang);
    h->endModel();

    return((void *)h);
  }

  boolean FCLTest(boolean info,
		  void *h1,THTransform *tr1,
		  void *h2,THTransform *tr2,
		  double *point,double *normal)
  {
    /* request -> capture the first collision between these objects */
    CollisionRequest<double> request(1,true);
    CollisionResult<double> result;

    Matrix3<double> r1;
    r1 << HTransformGetElement(0,0,tr1),HTransformGetElement(0,1,tr1),HTransformGetElement(0,2,tr1),
      HTransformGetElement(1,0,tr1),HTransformGetElement(1,1,tr1),HTransformGetElement(1,2,tr1),
      HTransformGetElement(2,0,tr1),HTransformGetElement(2,1,tr1),HTransformGetElement(2,2,tr1);

    Vector3<double> d1(HTransformGetElement(0,3,tr1),HTransformGetElement(1,3,tr1),HTransformGetElement(2,3,tr1));
    Transform3<double> pose1=Transform3<double>::Identity();
    pose1.translate(d1);
    pose1.rotate(r1);

  
    Matrix3<double> r2;
    r2<< HTransformGetElement(0,0,tr2),HTransformGetElement(0,1,tr2),HTransformGetElement(0,2,tr2),
      HTransformGetElement(1,0,tr2),HTransformGetElement(1,1,tr2),HTransformGetElement(1,2,tr2),
      HTransformGetElement(2,0,tr2),HTransformGetElement(2,1,tr2),HTransformGetElement(2,2,tr2);

    Vector3<double> d2(HTransformGetElement(0,3,tr2),HTransformGetElement(1,3,tr2),HTransformGetElement(2,3,tr2));
    Transform3<double> pose2=Transform3<double>::Identity();
    pose2.translate(d2);
    pose2.rotate(r2);
  
    unsigned int nc;
  
    collide((CollisionGeometry<double> *)h1,pose1,(CollisionGeometry<double> *)h2,pose2,request,result);

    nc=result.numContacts();

    if ((info)&&(nc>0))
      {
	unsigned int k;
	Contact<double> c;

	/* Typically a contact is detected as a set of
	   contact points. We just get the first one. 
	   We could also compute the average... */
	c=result.getContact(0);
	for(k=0;k<3;k++)	
	  {
	    point[k]=c.pos[k];
	    normal[k]=c.normal[k];
	  }
      }

    return(nc>0);
  }

  boolean FCLCTest(void *h1,THTransform *tr1,THTransform *tr2,
		   void *h2,THTransform *tr3,THTransform *tr4)
  {
    ContinuousCollisionRequest<double> request;
    ContinuousCollisionResult<double> result;

    Matrix3<double> r1;
    r1 << HTransformGetElement(0,0,tr1),HTransformGetElement(0,1,tr1),HTransformGetElement(0,2,tr1),
      HTransformGetElement(1,0,tr1),HTransformGetElement(1,1,tr1),HTransformGetElement(1,2,tr1),
      HTransformGetElement(2,0,tr1),HTransformGetElement(2,1,tr1),HTransformGetElement(2,2,tr1);
    Vector3<double> d1(HTransformGetElement(0,3,tr1),HTransformGetElement(1,3,tr1),HTransformGetElement(2,3,tr1));

    Transform3<double> pose1=Transform3<double>::Identity();
    pose1.translate(d1);
    pose1.rotate(r1);
  
    Matrix3<double> r2;
    r2 << HTransformGetElement(0,0,tr2),HTransformGetElement(0,1,tr2),HTransformGetElement(0,2,tr2),
      HTransformGetElement(1,0,tr2),HTransformGetElement(1,1,tr2),HTransformGetElement(1,2,tr2),
      HTransformGetElement(2,0,tr2),HTransformGetElement(2,1,tr2),HTransformGetElement(2,2,tr2);
    Vector3<double> d2(HTransformGetElement(0,3,tr2),HTransformGetElement(1,3,tr2),HTransformGetElement(2,3,tr2));
    Transform3<double> pose2=Transform3<double>::Identity();
    pose2.translate(d2);
    pose2.rotate(r2);

    Matrix3<double> r3;
    r3 << HTransformGetElement(0,0,tr3),HTransformGetElement(0,1,tr3),HTransformGetElement(0,2,tr3),
      HTransformGetElement(1,0,tr3),HTransformGetElement(1,1,tr3),HTransformGetElement(1,2,tr3),
      HTransformGetElement(2,0,tr3),HTransformGetElement(2,1,tr3),HTransformGetElement(2,2,tr3);
    Vector3<double> d3(HTransformGetElement(0,3,tr3),HTransformGetElement(1,3,tr3),HTransformGetElement(2,3,tr3));
    Transform3<double> pose3=Transform3<double>::Identity();
    pose3.translate(d3);
    pose3.rotate(r3);

  
    Matrix3<double> r4;
    r4 << HTransformGetElement(0,0,tr4),HTransformGetElement(0,1,tr4),HTransformGetElement(0,2,tr4),
      HTransformGetElement(1,0,tr4),HTransformGetElement(1,1,tr4),HTransformGetElement(1,2,tr4),
      HTransformGetElement(2,0,tr4),HTransformGetElement(2,1,tr4),HTransformGetElement(2,2,tr4);
    Vector3<double> d4(HTransformGetElement(0,3,tr4),HTransformGetElement(1,3,tr4),HTransformGetElement(2,3,tr4));
    Transform3<double> pose4=Transform3<double>::Identity();
    pose4.translate(d4);
    pose4.rotate(r4);

    continuousCollide((CollisionGeometry<double> *)h1,pose1,pose2,(CollisionGeometry<double> *)h2,pose3,pose4,request,result);

    return(result.is_collide);
  }

  void DeleteFCLObject(void *h)
  {
    delete (CollisionGeometry<double> *)h;
  }

#endif

#endif

