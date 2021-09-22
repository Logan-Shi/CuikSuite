#include "cd.h"

#include "defines.h"
#include "algebra.h"
#include "error.h"

#include <math.h>

/** \file cd.c

    \brief Implementation of the interface with the collision detection engine.

    Implementation of the interface with the collision detection engine.

    Different collision detection engines offer different performances and
    even different capabilities. Moreover, some applications require
    specific collision detection procedures (distance between bodies,
    interpretration, separating normal, etc). In general, the more the
    functionality of the collision detection engine the slower the
    process. Thus, a trade off must be reached for each application.

    \sa cd.h
*/

/** 
    \brief Stores the information collected during last collision check into a file.

    Stores the information collected during last collision check into a file.

    The information printed is in the form of a matlab script that 
    can be directly used to generate contact variables and equations from
    the collision info. This relies on the existence of additiona matlab
    scripts describing the geometry of the objects.

    We used this to generate contact aware cuik systems by using 
    \ref cuikmove.c "cuikmove"
    to select the initial grasp. This is part of our grasping pipeline.

    This function assumes that the object ot grasp is the last link in the
    world file.

    \see StoreCollisionInfo for more details.

    \param f File where to write the collision script.
    \param fname File from where we obtained the world information. The last
                 part of the filename (from the last '_' to the end) is assumed
		 to be the name of the object. This name is the one used to
		 call the sub-matlab scripts giving contact points and normals
    on the object.   
    \param objectID Identifier of the object being manipulated. This is
                    assumed to be a link. Use NO_UINT to print all the
		    collisions (wihtout any filter).
    \param m The mechanism description.
    \param nc Number of detected collisions.
    \param c The array of detected collisions.
*/
void StoreCollisionInfoInt(FILE *f,char *fname,unsigned int objectID,
			   Tmechanism *m,unsigned int nc,TCollisionInfo *c);

/** 
    \brief Prints information about the last collision check.

    Prints information about the last collision check.
     
    See \ref PrintCollisionInfo for more details.

    \param tl The transforms positioning the links.
    \param m The mechanism description. 
    \param e The environment description.
    \param nc Number of detected collisions.
    \param c The array of detected collisions.
*/
void PrintCollisionInfoInt(THTransform *tl,Tmechanism *m,Tenvironment *e,
			   unsigned int nc,TCollisionInfo *c);

#ifdef _HAVE_SOLID

  /** 
     \brief Callback called whenever a collision is detected.

     Callback called whenever a collision is detected.
     This is the version where we print info about the collisions: colliding links,
     collision points, and normal in the collision.

     We only print information about the first detected collision.
   
     \param client_data Point to user data given when defining the intraction between
                        objects.
     \param obj1 Pointer to the object given when creating the object.
     \param obj2 Pointer to the object given when creating the object.
     \param cd Collision detection information provided by Solid including the collision
     points and normal in global coordinates.
  */
  DT_Bool CDCallBackInfo(void *client_data,void *obj1,void *obj2,const DT_CollData *cd);

  /** 
     \brief Adds a shape to the collision detection data.

     Adds the shape to the current collision detection.
     Note that the collision detection structure is not passed as a parameter
     to this function since we use SOLID that relies on global variables
     (not so good programming style).

     \param p The convex polyhedron to add to the collision detection structure.
   
     \return The new SOLID shape handle.
  */
  DT_ShapeHandle AddShape2Solid(Tpolyhedron *p);

  /** 
     \brief Returns a transform that corrects the position of a polyhedron.

     The SOLID collision detection software define shapes in a pre-defined positions
     (spheres centered at 0, cylinders aligned with the Y axis,...).
     This function returns a homogeneous matrix that places the convex polyhedron
     in its correct position from the default position of the collision detector.

     \param t The returned correction transform.
     \param p The convex polyhedron.

     \return TRUE if the correction is not the identity.
  */
  boolean SolidCorrection(THTransform *t,Tpolyhedron *p);

  /** 
      \brief Initializes the Solid collision engine.

      Initializes the Solid collision engine.

      \param parallel TRUE if we are in a parallel situation, where
                      different collision detection queries can be executed
		      in parallel. In this case, we configure Solid just
		      to detect the collision, but not to inform about the
		      collision point (apparently this part of Solid 
		      is not re-entrant).
      \param m The machanism.
      \param e The enviroment.
      \param checkCollisionsLL Link-link collision to be checked.
      \param checkCollisionsLO Link-obstacle collision to be checked.
      \param s The solid collision information.
  */
  void InitSolidCD(boolean parallel,Tmechanism *m,Tenvironment *e,
		   boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		   TsolidCD *s);

  /** 
      \brief Determines if there is a collision using the SOLID collision engine.

      Determines if there is a collision using the SOLID collision engine.

      \param all TRUE if we want to detect all the collision. FALSE just to detect
                 the first one.
      \param tl The transforms to apply to the links.
      \param def The deformation parameters for each link.
      \param s The solid collision information.

      \return TRUE if there is a collision.
  */
  boolean CheckCollisionSolid(boolean all,THTransform *tl,TLinkConf *def,TsolidCD *s);

  /** 
      \brief Deletes the Solid related collision information.

      Deletes the Solid related collision information.

      \param s The solid collision information to delete.
  */
  void DeleteSolidCD(TsolidCD *s);
#endif

#ifdef _HAVE_VCOLLIDE

  /** 
      \brief Initializes the Vcollide collision engine.

      Initializes the Vcollide collision engine.

      \param m The machanism.
      \param e The enviroment. 
      \param checkCollisionsLL Link-link collision to be checked.
      \param checkCollisionsLO Link-obstacle collision to be checked.
      \param vc The Vcollide collision information.
  */
  void InitVcollideCD(Tmechanism *m,Tenvironment *e,
		      boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		      TvcollideCD *vc);


  /** 
      \brief Determines if there is a collision using the VCOLLIDE collision engine.

      Determines if there is a collision using the VCOLLIDE collision engine.

      \param tl The transforms to apply to the links.
      \param vc The Vcollide collision information.

      \return TRUE if there is a collision.
  */
  boolean CheckCollisionVcollide(THTransform *tl,TvcollideCD *vc);

  /** 
      \brief Deletes the Vcollide related collision information.

      Deletes the Vcollide related collision information.

      \param vc The Vcollide collision information to delete.
  */
  void DeleteVcollideCD(TvcollideCD *vc);

#endif

#ifdef _HAVE_PQP

  /** 
      \brief Initializes the PQP collision engine.

      Initializes the PQP collision engine.

      \param m The machanism.
      \param e The enviroment. 
      \param checkCollisionsLL Link-link collision to be checked.
      \param checkCollisionsLO Link-obstacle collision to be checked.
      \param p The PQP collision information.
  */
  void InitPQPCD(Tmechanism *m,Tenvironment *e,
		 boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		 TpqpCD *p);

  /** 
      \brief Determines if there is a collision using the PQP collision engine.

      Determines if there is a collision using the PQP collision engine.

      \param tl The transforms to apply to the links.
      \param p The PQP collision information.

      \return TRUE if there is a collision.
  */
  boolean CheckCollisionPQP(THTransform *tl,TpqpCD *p);

  /** 
      \brief Deletes the PQP related collision information.

      Deletes the PQP related collision information.

      \param p The PQP collision information.
  */
  void DeletePQPCD(TpqpCD *p);

#endif


#if _HAVE_FCL

  /** 
      \brief Defines an FCL object.

      Defines an FCL object and the associated information
      (type, calibration transform, etc).

      \param shape The polyhedron from which to generate the FCL object.
      \param p The FCL object to generate.
  */
  void DefineFCLObject(Tpolyhedron *shape,TfclCD *p);

  /** 
      \brief Initializes the FLC collision engine.

      Initializes the FCL collision engine.

      \param m The machanism.
      \param e The enviroment. 
      \param checkCollisionsLL Link-link collision to be checked.
      \param checkCollisionsLO Link-obstacle collision to be checked.
      \param p The FCL collision information.
  */
  void InitFCLCD(Tmechanism *m,Tenvironment *e,
		 boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		 TfclCD *p);

  /** 
      \brief Determines if there is a collision using the FCL collision engine.

      Determines if there is a collision using the FCL collision engine.

      \param all TRUE if we want to detect all the collision. FALSE just to detect
                 the first one.
      \param tl The transforms to apply to the links.
      \param p The FCL collision information.

      \return TRUE if there is a collision.
  */
  boolean CheckCollisionFCL(boolean all,THTransform *tl,TfclCD *p);

  /** 
      \brief Determines if there is a collision along a path using the FCL collision engine.

      Determines if there is a collision along a path using the FCL collision engine. The
      motion along the path is assumed to be lineal.

      \param tl The transforms to apply to the links in the final position of the path.
      \param tlPrev The transforms to apply to the links in the initial position of the path.
      \param p The FCL collision information.

      \todo Use the output of the continuous collision detection to adjust the advance 
            step of the RRTs.

      \return TRUE if there is a collision.
  */
  boolean CheckContCollisionFCL(THTransform *tl,THTransform *tlPrev,TfclCD *p);

  /** 
      \brief Deletes the FCL related collision information.

      Deletes the FCL related collision information.

      \param p The FCL collision information.
  */
  void DeleteFCLCD(TfclCD *p);

#endif

#if _HAVE_BULLET

  /** 
      \brief Defines an Bullet object.

      Defines an Bullet object and the associated information
      (type, calibration transform, etc).
      
      \param fixed TRUE if the object will never move.
      \param shape The polyhedron from which to generate the Bullet object.
      \param p The Bullet object to generate.
  */
  void DefineBulletObject(boolean fixed,Tpolyhedron *shape,TBulletCD *p);

  /** 
      \brief Initializes the FLC collision engine.

      Initializes the Bullet collision engine.

      \param m The machanism.
      \param e The enviroment. 
      \param checkCollisionsLL Link-link collision to be checked.
      \param checkCollisionsLO Link-obstacle collision to be checked.
      \param cont TRUE if we will check for continuous collision detection.
      \param p The Bullet collision information.
  */
  void InitBulletCD(Tmechanism *m,Tenvironment *e,
		    boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		    boolean cont,TBulletCD *p);

  /** 
      \brief Determines if there is a collision using the Bullet collision engine.

      Determines if there is a collision using the Bullet collision engine.

      \param all TRUE if we want to detect all the collision. FALSE just to detect
                 the first one.
      \param tl The transforms to apply to the links.
      \param p The Bullet collision information.

      \return TRUE if there is a collision.
  */
  boolean CheckCollisionBullet(boolean all,THTransform *tl,TBulletCD *p);

  /** 
      \brief Determines if there is a collision along a path using the Bullet collision engine.

      Determines if there is a collision along a path using the Bullet collision engine. The
      motion along the path is assumed to be lineal.

      \param tl The transforms to apply to the links in the final position of the path.
      \param tlPrev The transforms to apply to the links in the initial position of the path.
      \param p The Bullet collision information.

      \todo Use the output of the continuous collision detection to adjust the advance 
            step of the RRTs.

      \return TRUE if there is a collision.
  */
  boolean CheckContCollisionBullet(THTransform *tl,THTransform *tlPrev,TBulletCD *p);

  /** 
      \brief Deletes the Bullet related collision information.

      Deletes the Bullet related collision information.

      \param p The Bullet collision information.
  */
  void DeleteBulletCD(TBulletCD *p);

#endif

#ifdef _HAVE_RIGIDCLL

  /** 
      \param Comparens the collision pattern of the obstacles and the ground link.

      Determines if the collision patter of the obstacles (all of them) is the same as that of the ground link.
      If so, the obstacles can be added as a part of the ground link. 

      This is only used in the RigidCLL collision detection engine.

      \param nl Number of links.
      \param no Number of obstacles.
      \param checkCollisionsLL Allowed collisions between links.
      \param checkCollisionsLO Allowed collisions between links and obstacles.
      
      \return TRUE if all the obstacles behave as the ground link.
  */
  boolean ObstaclesCollideLikeGround(unsigned int nl,unsigned int no,boolean **checkCollisionsLL,boolean **checkCollisionsLO);

  /** 
      \brief Initializes the RigidCLL collision engine.

      Initializes the RigidCLL collision engine.

      \param m The machanism.
      \param e The enviroment. 
      \param checkCollisionsLL Link-link collision to be checked.
      \param checkCollisionsLO Link-obstacle collision to be checked.
      \param r The RigidCLL collision information.
  */
  void InitRigidCLLCD(Tmechanism *m,Tenvironment *e,
		      boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		      TrigidCLLCD *r);

  /** 
      \brief Determines if there is a collision using the RigidCLL collision engine.

      Determines if there is a collision using the RigidCLL collision engine.

      \param tl The transforms to apply to the links.
      \param r The RigidCLL collision information.

      \return TRUE if there is a collision.
  */
  boolean CheckCollisionRigidCLL(THTransform *tl,TrigidCLLCD *r);

  /** 
      \brief Deletes the RigidCLL related collision information.

      Deletes the RigidCLL related collision information.

      \param r The RigidCLL collision information.
  */
  void DeleteRigidCLLCD(TrigidCLLCD *r);

#endif


#ifdef _HAVE_SOLID

  DT_Bool CDCallBackInfo(void *client_data,void *obj1,void *obj2,
			 const DT_CollData *cd)
  { 
    TsolidCD *s;

    s=(TsolidCD *)client_data;

    if ((s->simple)||(s->collision==NULL))
      /* in simple collision detection mode. Stop as soon as a collision is
         detected, without collecing information about the collisions. */
      return(DT_DONE);
    else
      {
	unsigned int id1,id2,k;
	double nr;

	if (s->nc==s->mc)
	  {
	    MEM_DUP(s->collision,s->mc,TCollisionInfo);
	  }

	id1=*((unsigned int*)obj1);
	id2=*((unsigned int*)obj2);

	if (s->object[id1].linkID==NO_UINT)
	  {
	    /* the first object is a body in the environment */
	    s->collision[s->nc].isLink1=FALSE;
	    s->collision[s->nc].id1=s->object[id1].bodyID;
	    HTransformIdentity(&(s->collision[s->nc].t1));
	  }
	else
	  {
	    s->collision[s->nc].isLink1=TRUE;
	    s->collision[s->nc].id1=s->object[id1].linkID;
	    HTransformCopy(&(s->collision[s->nc].t1),&(s->object[id1].t));
	  }

	if (s->object[id2].linkID==NO_UINT)
	  {
	    /* the second object is a body in the environment */
	    s->collision[s->nc].isLink2=FALSE;
	    s->collision[s->nc].id2=s->object[id2].bodyID;
	    HTransformIdentity(&(s->collision[s->nc].t2));
	  }
	else
	  {
	    s->collision[s->nc].isLink2=TRUE;
	    s->collision[s->nc].id2=s->object[id2].linkID;   
	    HTransformCopy(&(s->collision[s->nc].t2),&(s->object[id2].t));
	  }

	for(k=0;k<3;k++)
	  {
	    s->collision[s->nc].point[k]=cd->point2[k];
	    s->collision[s->nc].normal[k]=cd->normal[k];
	  }
	/* Just in case ;) */
	nr=Norm(3,s->collision[s->nc].normal);
	if (nr>ZERO) /* In some cases is very tiny */
	  ScaleVector(1.0/nr,3,s->collision[s->nc].normal);

	s->nc++;

	/* The transforms are computed after the detection */
	return DT_CONTINUE;
      }
  }

  DT_ShapeHandle AddShape2Solid(Tpolyhedron *p)
  {
    unsigned int i,j,k,n;
    unsigned int nv,nf;
    double **v;
    unsigned int *nvf,**fv;
    DT_ShapeHandle s=0;
    DT_Scalar ps[3];
    double rad;

    if (GetPolyhedronStatus(p)==DECOR_SHAPE)
      Error("DECOR shapes can not be included into collision detection");

    /* hidden shapes are added to the collision detection, although they
       are not displayed  */
    /*
     IMPORTANT: The following block can not be executed in parallel. SOLID stores all
     the shapes in the same pool of shapes, which can not be updated
     concurrently. 
    */
    #pragma omp critical
    {
      switch(GetPolyhedronType(p))
	{
	case OFF:
	case COFF:
	case LINE:
	  GetOFFInfo(&nv,&v,&nf,&nvf,&fv,p);
	
	  s=DT_NewComplexShape(NULL);
	  for(i=0;i<nf;i++)
	    {
	      DT_Begin();
	      for(j=0;j<nvf[i];j++)
		{
		  n=fv[i][j];
		  for(k=0;k<3;k++)
		    ps[k]=(DT_Scalar)v[n][k];
		  DT_Vertex(ps);
		}
	      DT_End();
	    }
	  DT_EndComplexShape();
	  break;
	case CYLINDER:
	  /* Define a unitary cylinder along the Y axis CENTERED at the origin */
	  rad=GetPolyhedronRadius(p);
	  s=DT_NewCylinder((DT_Scalar)rad,1.0f);
	  break;
	case SPHERE:
	  rad=GetPolyhedronRadius(p);
	  s=DT_NewSphere((DT_Scalar)rad);
	  break;
	case SEGMENTS:
	  Error("Segment-based structures can not be included in collision detection");
	  break;
	}
    }
    return(s);
  }

  boolean SolidCorrection(THTransform *t,Tpolyhedron *p)
  {
    THTransform t2;
    double c[3],p1[3],p2[3];
  
    if (GetPolyhedronStatus(p)==DECOR_SHAPE)
      Error("DECOR shapes can not be included into collision detection");

    switch(GetPolyhedronType(p))
      {
      case OFF:
      case COFF:
      case LINE:
	HTransformIdentity(t);
	break;
      case CYLINDER:
	/* The transforms below have to be interpreted from last to first */

	/* rotate the unitary cylinder along the X positive axis to an
	   arbitrary position (this includes scaling to the appropiate lenght
	   since we defined it with lenght 1) */

	GetPolyhedronDefiningPoint(0,p1,p);
	GetPolyhedronDefiningPoint(1,p2,p);

	HTransformX2Vect(1,1,p1,p2,t);
	/* rotate to align the cylinder with the X axis */
	HTransformRz2(-1,0,&t2);
	HTransformProduct(t,&t2,t);
	/* move the unitary cylinder to the positive Y axis */
	HTransformTy(0.5,&t2);
	HTransformProduct(t,&t2,t);
	break;
      case SPHERE:
	GetPolyhedronCenter(c,p);
	HTransformTxyz(c[0],c[1],c[2],t);
	break;
      case SEGMENTS:
	Error("Segment-based structures can not be included in collision detection");
	break;
      }
    return(!(HTransformIsIdentity(t)));
  }

  void InitSolidCD(boolean parallel,Tmechanism *m,Tenvironment *e,
 		   boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		   TsolidCD *s)
  {
    unsigned int i,j;
    unsigned int lID,bID,oID,lID1,lID2;
    unsigned int nB;
    Tlink *l; 
    Tpolyhedron *shape;
    double matrix[16];
    unsigned int np,nl,no;

    nl=GetMechanismNLinks(m);
    no=GetEnvironmentNObstacles(e);
    np=GetMechanismNBodies(m)+no;

    /* Create the shapes */

    /* np is always larger (or equal) than the number of part that can actually
       collide. */
    NEW(s->object,np,TsolidObj);

    /* Generate the shapes */
    s->np=0;
    for(lID=0;lID<nl;lID++)
      {
	if (LinkCanCollide(lID,nl,no,checkCollisionsLL,checkCollisionsLO))
	  {
	    l=GetMechanismLink(lID,m);
	    nB=LinkNBodies(l);

	    for(bID=0;bID<nB;bID++)
	      {
		if (GetLinkBodyStatus(bID,l)!=DECOR_SHAPE)
		  {
		    s->object[s->np].id=s->np;
		    s->object[s->np].linkID=lID;
		    s->object[s->np].bodyID=bID;

		    shape=GetLinkBody(bID,l);
		    s->object[s->np].shape=AddShape2Solid(shape);
  
		    s->object[s->np].correction=SolidCorrection(&(s->object[s->np].tc),shape);
		
		    s->np++;
		  }
	      }
	  }
      }

    for(oID=0;oID<no;oID++)
      {
	if ((ObstacleCanCollide(oID,nl,checkCollisionsLO))&&
	    (GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE))
	  {
	    s->object[s->np].id=s->np;
	    s->object[s->np].linkID=NO_UINT;
	    s->object[s->np].bodyID=oID;
	  
	    shape=GetObstacleShape(oID,e); 
	    s->object[s->np].shape=AddShape2Solid(shape);

	    s->object[s->np].correction=SolidCorrection(&(s->object[s->np].tc),shape);

	    s->np++;
	  }
      } 

    /* Serialize the access to the internal SOLID structuers */
    #pragma omp critical
    {
      s->scene=DT_CreateScene();
      s->respTable=DT_CreateRespTable();

      for(i=0;i<s->np;i++)
	{
	  s->object[i].handler=DT_CreateObject((void*)&(s->object[i].id),s->object[i].shape);
	  DT_AddObject(s->scene,s->object[i].handler);
	  s->object[i].respClass=DT_GenResponseClass(s->respTable);
	  DT_SetResponseClass(s->respTable,s->object[i].handler,s->object[i].respClass);
	}
    }

    s->simple=TRUE; /* default mode check for first collision only */

    for (i=0;i<s->np;i++)
      {
	lID=s->object[i].linkID;
	if (lID!=NO_UINT)
	  {
	    /* shape 'i' is part of a link */
	    for (j=i+1;j<s->np;j++)
	      {
		/* partj 'j' can be a link or an obstacle */
		lID=s->object[j].linkID;
		if (lID==NO_UINT)
		  {
		    /*link-obstacle intersection*/
		    lID=s->object[i].linkID;
		    oID=s->object[j].bodyID;
		    if (checkCollisionsLO[lID][oID])
		      {
			DT_AddPairResponse(s->respTable,
					   s->object[i].respClass,s->object[j].respClass,
					   &CDCallBackInfo,(parallel?DT_SIMPLE_RESPONSE:DT_DEPTH_RESPONSE),s);
		      }
		  }
		else
		  {
		    /*link-link intesection*/
		    lID1=s->object[i].linkID;
		    lID2=s->object[j].linkID;
		    if (checkCollisionsLL[lID1][lID2])
		      {
			DT_AddPairResponse(s->respTable,
					   s->object[i].respClass,s->object[j].respClass,
					   &CDCallBackInfo,(parallel?DT_SIMPLE_RESPONSE:DT_DEPTH_RESPONSE),s);
		      }
		  }
	      }
	  }
      }
  
    /* Reset the collision information (only actually used if s->simple is FALSE) */
    s->nc=0;
    if (parallel)
      {
	s->mc=0;
	s->collision=NULL;
      }
    else
      {
	s->mc=10;
	NEW(s->collision,s->mc,TCollisionInfo);
      }

    /* For the obstacle the pre-computed correction is used only once
       (they do not move) and we do it now*/
    for(i=0;i<s->np;i++) 
      {
	lID=s->object[i].linkID;
	if ((lID==NO_UINT)&&(s->object[i].correction))
	  {
	    HTransform2GLMatrix(matrix,&(s->object[i].tc));
	    DT_SetMatrixd(s->object[i].handler,matrix);
	  }
	/* Set a default value for all parts (mobile or not) */
	HTransformIdentity(&(s->object[i].t));
      }
  }

  boolean CheckCollisionSolid(boolean all,THTransform *tl,TLinkConf *def,TsolidCD *s)
  {
    unsigned int i;
    double m[16];
    THTransform t,*to;
    unsigned int lID;

    /* This is the only function where we actually move
       checking for collisions. This is the place where we
       reset the collision information before checking. */
    
    for(i=0;i<s->np;i++)
      {
	lID=s->object[i].linkID;
	if (lID!=NO_UINT)
	  {
	    /*this part can move -> move it !*/
	    
	    /* Keep the transform before the inernal_conf/correction. */
	    to=&(s->object[i].t);
	    HTransformCopy(to,&(tl[lID]));

	    /* The transform for the current link */
	    HTransformCopy(&t,to);
	    
	    /* if necessary, apply an object internal configuration */
	    if (!EmptyLinkConf(&(def[lID])))
	      {
		THTransform d;

		GetLinkConfTransform(s->object[i].bodyID,&d,&(def[lID]));
		HTransformProduct(&t,&d,&t);
		HTransformDelete(&d);
	      }
	    
	    /* if necessary apply the correction */
	    if (s->object[i].correction)
	      HTransformProduct(&t,&(s->object[i].tc),&t);
	      
	    HTransform2GLMatrix(m,&t);
	    HTransformDelete(&t);

	    /* Here send the transform to SOLID */
	    DT_SetMatrixd(s->object[i].handler,m);
	  }
      }

    /* set the work mode */
    s->simple=((!all)||(s->collision==NULL));

    /* Reset the number of collisions detected so far (only used if all=TRUE). */
    s->nc=0;

    /* Test */
    return(DT_Test(s->scene,s->respTable)>0);
  }

  void DeleteSolidCD(TsolidCD *s)
  {
     #pragma omp critical
     {
       unsigned int i;
       
       for(i=0;i<s->np;i++)
	 {
	   DT_RemoveObject(s->scene,s->object[i].handler);
	   DT_DestroyObject(s->object[i].handler);
	   DT_DeleteShape(s->object[i].shape);
	   HTransformDelete(&(s->object[i].t));
	   HTransformDelete(&(s->object[i].tc));
	 }

       DT_DestroyRespTable(s->respTable);
       DT_DestroyScene(s->scene);
     }
     free(s->object);
     if (s->collision!=NULL)
       free(s->collision);
  }
#endif

#ifdef _HAVE_VCOLLIDE

  void InitVcollideCD(Tmechanism *m,Tenvironment *e,
		      boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		      TvcollideCD *vc)
  {
    unsigned int i,j,lID1,lID2,bID2,np,nl,no,nB,lID,bID,oID;
    double **v;
    unsigned int nv,nf,*nvf,**fv;
    Tpolyhedron *shape;
    Tlink *l;

    vc->vc=InitVcollide();

    nl=GetMechanismNLinks(m);
    no=GetEnvironmentNObstacles(e);
    np=GetMechanismNBodies(m)+no;

    /* Create the shapes */

    /* np is always larger (or equal) than the number of part that can actually
       collide. */
    NEW(vc->bodyID,np,unsigned int);
    NEW(vc->linkID,np,unsigned int);
    NEW(vc->vcID,np,unsigned int);
  
    /* Generate the shapes */
    vc->np=0;
    for(lID=0;lID<nl;lID++)
      {
	if (LinkCanCollide(lID,nl,no,checkCollisionsLL,checkCollisionsLO))
	  {
	    l=GetMechanismLink(lID,m);
	    nB=LinkNBodies(l);

	    for(bID=0;bID<nB;bID++)
	      {
		if (GetLinkBodyStatus(bID,l)!=DECOR_SHAPE)
		  {
		    vc->linkID[vc->np]=lID;
		    vc->bodyID[vc->np]=bID;

		    shape=GetLinkBody(bID,l);
		    GetOFFInfo(&nv,&v,&nf,&nvf,&fv,shape);
		    vc->vcID[vc->np]=AddPolyhedron2Vcollide(v,nf,nvf,fv,vc->vc);

		    vc->np++;
		  }
	      }
	  }
      }

    for(oID=0;oID<no;oID++)
      {
	if ((ObstacleCanCollide(oID,nl,checkCollisionsLO))&&
	    (GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE))
	  {
	    vc->linkID[vc->np]=NO_UINT;
	    vc->bodyID[vc->np]=oID;

	    shape=GetObstacleShape(oID,e); 
	    GetOFFInfo(&nv,&v,&nf,&nvf,&fv,shape);
	    vc->vcID[vc->np]=AddPolyhedron2Vcollide(v,nf,nvf,fv,vc->vc);

	    vc->np++;
	  }
      } 

    /* Now define the possible collisions */
    for(i=0;i<vc->np;i++)
      {
	lID1=vc->linkID[i];
	if (lID1!=NO_UINT) /* if link1 is an obstacle, skip */
	  {
	    for(j=i+1;j<vc->np;j++)
	      {
		lID2=vc->linkID[j];
		if (lID2!=NO_UINT)
		  {
		    /* link-link */
		    if (checkCollisionsLL[lID1][lID2])
		      ActivateCollisionsVcollide(vc->vcID[i],vc->vcID[j],vc->vc);
		    else
		      DeactivateCollisionsVcollide(vc->vcID[i],vc->vcID[j],vc->vc);
		  }
		else
		  {
		    /* link-obstacle */
		    bID2=vc->bodyID[j];
		    if (checkCollisionsLO[lID1][bID2])
		      ActivateCollisionsVcollide(vc->vcID[i],vc->vcID[j],vc->vc);
		    else
		      DeactivateCollisionsVcollide(vc->vcID[i],vc->vcID[j],vc->vc);
		  }
	      }
	  }
      }
  }

  boolean CheckCollisionVcollide(THTransform *tl,TvcollideCD *vc)
  {
    unsigned int i,lID;
    
    /* move */
    for(i=0;i<vc->np;i++)
      {
	lID=vc->linkID[i];
	if (lID!=NO_UINT) /* if link is an obstacle, do not move */
	  MoveVcollideObject(vc->vcID[i],&(tl[lID]),vc->vc);
      }
    
    /* and check */
    return(VcollideTest(vc->vc));
  }

  void DeleteVcollideCD(TvcollideCD *vc)
  {
    unsigned int i;

    for(i=0;i<vc->np;i++)
      DeleteVcollideObject(vc->vcID[i],vc->vc);
    
    DeleteVcollide(vc->vc);

    free(vc->vcID);
    free(vc->linkID);
    free(vc->bodyID);
  }

#endif

#ifdef _HAVE_PQP

  void InitPQPCD(Tmechanism *m,Tenvironment *e,
		 boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		 TpqpCD *p)
  {
    unsigned int i,j,lID1,lID2,bID2,np,nl,no,nB,lID,bID,oID;
    double **v;
    unsigned int nv,nf,*nvf,**fv;
    Tpolyhedron *shape;
    Tlink *l;

    nl=GetMechanismNLinks(m);
    no=GetEnvironmentNObstacles(e);
    np=GetMechanismNBodies(m)+no;

    /* np is always larger (or equal) than the number of part that can actually
       collide. */
    NEW(p->bodyID,np,unsigned int);
    NEW(p->linkID,np,unsigned int);
    NEW(p->model,np,Tpqp *);
  
    /* Generate the shapes */
    p->np=0;
    for(lID=0;lID<nl;lID++)
      {
	if (LinkCanCollide(lID,nl,no,checkCollisionsLL,checkCollisionsLO))
	  {
	    l=GetMechanismLink(lID,m);
	    nB=LinkNBodies(l);

	    for(bID=0;bID<nB;bID++)
	      {
		if (GetLinkBodyStatus(bID,l)!=DECOR_SHAPE)
		  {
		    p->linkID[p->np]=lID;
		    p->bodyID[p->np]=bID;

		    shape=GetLinkBody(bID,l);
		    GetOFFInfo(&nv,&v,&nf,&nvf,&fv,shape);
		    p->model[p->np]=DefinePQPModel(v,nf,nvf,fv);

		    p->np++;
		  }
	      }
	  }
      }

    for(oID=0;oID<no;oID++)
      {
	if ((ObstacleCanCollide(oID,nl,checkCollisionsLO))&&
	    (GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE))
	  {
	    p->linkID[p->np]=NO_UINT;
	    p->bodyID[p->np]=oID;

	    shape=GetObstacleShape(oID,e); 
	    GetOFFInfo(&nv,&v,&nf,&nvf,&fv,shape);
	    p->model[p->np]=DefinePQPModel(v,nf,nvf,fv);

	    p->np++;
	  }
      } 

    /* Now define the possible collisions */

    NEW(p->p1,p->np*(p->np-1),unsigned int);
    NEW(p->p2,p->np*(p->np-1),unsigned int);
    p->nPairs=0;
    for(i=0;i<p->np;i++)
      {
	lID1=p->linkID[i];
	if (lID1!=NO_UINT) /* if link1 is an obstacle, skip */
	  {
	    for(j=i+1;j<p->np;j++)
	      {
		lID2=p->linkID[j];
		if (lID2!=NO_UINT)
		  {
		    /* link-link */
		    if (checkCollisionsLL[lID1][lID2])
		      {
			p->p1[p->nPairs]=i;
			p->p2[p->nPairs]=j;
			p->nPairs++;
		      }
		  }
		else
		  {
		    /* link-obstacle */
		    bID2=p->bodyID[j];
		    if (checkCollisionsLO[lID1][bID2])
		      {
			p->p1[p->nPairs]=i;
			p->p2[p->nPairs]=j;
			p->nPairs++;
		      }
		  }
	      }
	  }
      }
  }

  boolean CheckCollisionPQP(THTransform *tl,TpqpCD *p)
  {
    boolean collision;
    unsigned int n,i,j,l1,l2;
    THTransform *t1,*t2;

    n=0;
    collision=FALSE;
    while((!collision)&&(n<p->nPairs))
      {
	i=p->p1[n];
	j=p->p2[n];

	l1=p->linkID[i];
	l2=p->linkID[j];

	if (l1!=NO_UINT)
	  t1=&(tl[l1]);
	else
	  t1=NULL;

	if (l2!=NO_UINT)
	  t2=&(tl[l2]);
	else
	  t2=NULL;

	collision=PQPTest(t1,p->model[i],t2,p->model[j]);

	n++;
      }
    return(collision);
  }

  void DeletePQPCD(TpqpCD *p)
  {
    unsigned int i;

    for(i=0;i<p->np;i++)
      DeletePQPModel(p->model[i]);

    free(p->model);
    free(p->linkID);
    free(p->bodyID);
    free(p->p1);
    free(p->p2);
  }

#endif

#if _HAVE_FCL

  void DefineFCLObject(Tpolyhedron *shape,TfclCD *p)
  {
    double p1[3],p2[3],r,l;
    double **v;
    unsigned int nv,nf,*nvf,**fv;
    THTransform t1,t2;
    TFCLObject *obj;

    obj=&(p->object[p->np]);
	
    switch(GetPolyhedronType(shape))
      {
      case SPHERE:
	r=GetPolyhedronRadius(shape);
	obj->model=DefineFCLSphere(r);
	GetPolyhedronCenter(p1,shape);
	HTransformTxyz(p1[0],p1[1],p1[2],&(obj->tc));

	/* Set the type */
	obj->type=FCL_SPHERE;
	break;

      case CYLINDER:
	/* vector with unit length along the Z axis (zero centered) */
	r=GetPolyhedronRadius(shape);
	GetPolyhedronDefiningPoint(0,p1,shape);
	GetPolyhedronDefiningPoint(1,p2,shape);
	SubtractVector(3,p2,p1); /* p2=p2-p1 */
 	l=Norm(3,p2);
	obj->model=DefineFCLCylinder(r,l);

	/* define the correction: apply from end to top */
	/* the transforms must be proper rigid transforms (do not use
	   scale/deformation) */
	/* Move the x-aligned cylinder to an arbitrary position (3) */
	SumVectorScale(3,p1,1.0/l,p2,p2);
	HTransformX2Vect(1,1,p1,p2,&t1);
	/* rotate to align the cylinder with the X axis (2) */
	HTransformRy2(1,0,&t2);
	HTransformProduct(&t1,&t2,&t1);
	/* move the cylinder to the positive Z axis (1) */
	HTransformTz(0.5*l,&t2);
	HTransformProduct(&t1,&t2,&(obj->tc));

	/* Set the type */
	obj->type=FCL_CYLINDER;
	break;

      default:
	/* The soup of triangles is defined and works for any body */
	GetOFFInfo(&nv,&v,&nf,&nvf,&fv,shape);
	obj->model=DefineFCLMesh(nv,v,nf,nvf,fv);
	HTransformIdentity(&(obj->tc));

	/* Set the type */
	obj->type=FCL_MESH;
      }
  }

  void InitFCLCD(Tmechanism *m,Tenvironment *e,
		 boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		 TfclCD *p)
  {
    unsigned int i,j,k,lID1,lID2,bID2,np,nl,no,nB,lID,bID,oID;
    Tpolyhedron *shape;
    Tlink *l;

    nl=GetMechanismNLinks(m);
    no=GetEnvironmentNObstacles(e);
    np=GetMechanismNBodies(m)+no;

    /* np is always larger (or equal) than the number of part that can actually
       collide. */
    NEW(p->object,np,TFCLObject);

    /* Generate the shapes */
    p->np=0;
    for(lID=0;lID<nl;lID++)
      {
	if (LinkCanCollide(lID,nl,no,checkCollisionsLL,checkCollisionsLO))
	  {
	    l=GetMechanismLink(lID,m);
	    nB=LinkNBodies(l);

	    for(bID=0;bID<nB;bID++)
	      {
		if (GetLinkBodyStatus(bID,l)!=DECOR_SHAPE)
		  {
		    p->object[p->np].linkID=lID;
		    p->object[p->np].bodyID=bID;

		    shape=GetLinkBody(bID,l);
		    DefineFCLObject(shape,p);
		    p->np++;
		  }
	      }
	  }
      }
    k=p->np; /* mobile parts */
    for(oID=0;oID<no;oID++)
      {
	if ((ObstacleCanCollide(oID,nl,checkCollisionsLO))&&
	    (GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE))
	  {
	    p->object[p->np].linkID=NO_UINT;
	    p->object[p->np].bodyID=oID;

	    shape=GetObstacleShape(oID,e); 
	    DefineFCLObject(shape,p);
	    p->np++;
	  }
      } 

    /* Now define the possible collisions */
    k=k*(p->np-1); /* k=k*(k-1)+k*(p->np-k)  link-link link-obs */
    NEW(p->p1,k,unsigned int);
    NEW(p->p2,k,unsigned int);

    p->nPairs=0;
    for(i=0;i<p->np;i++)
      {
	lID1=p->object[i].linkID;
	if (lID1!=NO_UINT) /* if object is an obstacle, skip */
	  {
	    for(j=i+1;j<p->np;j++)
	      {
		lID2=p->object[j].linkID;
		if (lID2!=NO_UINT)
		  {
		    /* link-link */
		    if (checkCollisionsLL[lID1][lID2])
		      {
			p->p1[p->nPairs]=i;
			p->p2[p->nPairs]=j;
			p->nPairs++;
		      }
		  }
		else
		  {
		    /* link-obstacle */
		    bID2=p->object[j].bodyID;
		    if (checkCollisionsLO[lID1][bID2])
		      {
			p->p1[p->nPairs]=i;
			p->p2[p->nPairs]=j;
			p->nPairs++;
		      }
		  }
	      }
	  }
      }

    p->nc=0;
    p->mc=10;
    NEW(p->collision,p->mc,TCollisionInfo);
    
    /* set the default transform for each part */
    for(i=0;i<p->np;i++)
      HTransformCopy(&(p->object[i].t),&(p->object[i].tc));
  }

  boolean CheckCollisionFCL(boolean all,THTransform *tl,TfclCD *p)
  {
    boolean collision,done,newCollision;
    unsigned int i,j,lID,n;
    double point[3],normal[3];
    TFCLObject *obj1,*obj2;
    
    /* Precompute the transforms for each part */
    for(i=0;i<p->np;i++)
      {
	lID=p->object[i].linkID;
	/* the transforms for static objecs are already pre-computed */
	if (lID!=NO_UINT)
	  {
	    if (p->object[i].type==FCL_MESH) /* meshes have no offset */
	      HTransformCopy(&(p->object[i].t),&(tl[lID]));
	    else
	      HTransformProduct(&(tl[lID]),&(p->object[i].tc),&(p->object[i].t));
	  }
      }

    p->nc=0; /* Reset the collision information. Will be updated probably. */
    n=0;
    collision=FALSE;
    done=FALSE;
    while((!done)&&(n<p->nPairs))
      {
	i=p->p1[n];
	j=p->p2[n];
	obj1=&(p->object[i]);
	obj2=&(p->object[j]);
      
	newCollision=FCLTest(all,
			     obj1->model,&(obj1->t),
			     obj2->model,&(obj2->t),
			     point,normal);

	if ((all)&&(newCollision))
	  {
	    unsigned int l1,l2,k;
	    TCollisionInfo *col;

	    /* collect the collision results */
	    if (p->nc==p->mc)
	      {
		MEM_DUP(p->collision,p->mc,TCollisionInfo);
	      }

	    col=&(p->collision[p->nc]);

	    l1=obj1->linkID;
	    if (l1==NO_UINT)
	      {
		col->isLink1=FALSE;
		col->id1=obj1->bodyID;
	      }
	    else
	      {
		col->isLink1=TRUE;
		col->id1=l1;
	      }

	    l2=obj2->linkID;
	    if (l2==NO_UINT)
	      {
		col->isLink2=FALSE;
		col->id2=obj2->bodyID;
	      }
	    else
	      {
		col->isLink2=TRUE;
		col->id2=l2;
	      }
	    
	    for(k=0;k<3;k++)
	      {
		col->point[k]=point[k];
		col->normal[k]=normal[k];
	      }
	    /* Just in case ;) */
	    Normalize(3,col->normal);
	    
	    /* Store the transforms as given by the user */
	    if (col->isLink1)
	      HTransformCopy(&(col->t1),&(tl[col->id1]));
	    else
	      HTransformIdentity(&(col->t1));

	    if (col->isLink2)
	      HTransformCopy(&(col->t2),&(tl[col->id2]));
	    else
	      HTransformIdentity(&(col->t2));

	    p->nc++;
	  }

	collision=((collision)||(newCollision));

	done=((!all)&&(newCollision));

	n++;
      }
    return(collision);
  }

  boolean CheckContCollisionFCL(THTransform *tl,THTransform *tlPrev,TfclCD *p)
  {
    if (tlPrev==NULL)
      return(CheckCollisionFCL(FALSE,tl,p));
    else
      {
	boolean collision;
	unsigned int n,i,j,lID;
	THTransform *tp;
	TFCLObject *obj1,*obj2;

	/* Precompute the transform */
	NEW(tp,p->np,THTransform);

	/* Precompute the transforms for each part */
	for(i=0;i<p->np;i++)
	  {
	    obj1=&(p->object[i]);

	    lID=obj1->linkID;

	    if (lID!=NO_UINT)
	      {
		if (obj1->type==FCL_MESH)
		  {
		    HTransformCopy(&(obj1->t),&(tl[lID]));
		    HTransformCopy(&(tp[i]),&(tlPrev[lID]));
		  }
		else
		  {
		    HTransformProduct(&(tl[lID]),&(obj1->tc),&(obj1->t));
		    HTransformProduct(&(tlPrev[lID]),&(obj1->tc),&(tp[i]));
		  }
	      }
	    else
	      HTransformCopy(&(tp[i]),&(obj1->tc)); /* static object -> copy the offset, if any */
	  }


	p->nc=0; /* Reset the collision information. Not updated here. */
	n=0;
	collision=FALSE;
	while((!collision)&&(n<p->nPairs))
	  {
	    i=p->p1[n];
	    j=p->p2[n];
	    obj1=&(p->object[i]);
	    obj2=&(p->object[j]);

	    collision=FCLCTest(obj1->model,&(tp[i]),&(obj1->t),
			       obj2->model,&(tp[j]),&(obj2->t));

	    n++;
	  }
	
	/* release the allocated memory */
	free(tp);

	return(collision);
      }
  }

  void DeleteFCLCD(TfclCD *p)
  {
    unsigned int i;
    
    for(i=0;i<p->np;i++)
      DeleteFCLObject(p->object[i].model);

    free(p->object);
    free(p->p1);
    free(p->p2);
    free(p->collision);
  }

#endif

#ifdef _HAVE_BULLET

  void DefineBulletObject(boolean fixed,Tpolyhedron *shape,TBulletCD *p)
  {
    double p1[3],p2[3],r,l;
    double **v;
    unsigned int nv,nf,*nvf,**fv;
    THTransform t1,t2;
    TBulletObject *obj;

    obj=&(p->object[p->np]);
	
    switch(GetPolyhedronType(shape))
      {
      case SPHERE:
	r=GetPolyhedronRadius(shape);
	obj->model=DefineBulletSphere(fixed,r);
	GetPolyhedronCenter(p1,shape);
	HTransformTxyz(p1[0],p1[1],p1[2],&(obj->tc));

	/* Set the type */
	obj->type=BULLET_SPHERE;
	break;

      case CYLINDER:
	/* vector with unit length along the X axis (zero centered) */
	r=GetPolyhedronRadius(shape);
	GetPolyhedronDefiningPoint(0,p1,shape);
	GetPolyhedronDefiningPoint(1,p2,shape);
	SubtractVector(3,p2,p1); /* p2=p2-p1 */
 	l=Norm(3,p2);
	obj->model=DefineBulletCylinder(fixed,r,l);

	/* define the correction: apply from end to top */
	/* the transforms must be proper rigid transforms (do not use
	   scale/deformation) */
	/* Move the x-aligned cylinder to an arbitrary position (3) */
	SumVectorScale(3,p1,1.0/l,p2,p2);
	HTransformX2Vect(1,1,p1,p2,&t1);

	/* move the cylinder to the positive X axis (1) */
	HTransformTx(0.5*l,&t2);
	HTransformProduct(&t1,&t2,&(obj->tc));

	/* Set the type */
	obj->type=BULLET_CYLINDER;
	break;

      default:
	/* The soup of triangles is defined and works for any body */
	GetOFFInfo(&nv,&v,&nf,&nvf,&fv,shape);
	obj->model=DefineBulletMesh(fixed,nv,v,nf,nvf,fv);
	HTransformIdentity(&(obj->tc));

	/* Set the type */
	obj->type=BULLET_MESH;
      }
  }

  void InitBulletCD(Tmechanism *m,Tenvironment *e,
		    boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		    boolean cont,TBulletCD *p)
  {
    unsigned int i,j,k,lID1,lID2,bID2,np,nl,no,nB,lID,bID,oID;
    Tpolyhedron *shape;
    Tlink *l;

    nl=GetMechanismNLinks(m);
    no=GetEnvironmentNObstacles(e);
    np=GetMechanismNBodies(m)+no;

    /* np is always larger (or equal) than the number of part that can actually
       collide. */
    NEW(p->object,np,TBulletObject);

    /* Generate the shapes */
    p->np=0;
    for(lID=0;lID<nl;lID++)
      {
	if (LinkCanCollide(lID,nl,no,checkCollisionsLL,checkCollisionsLO))
	  {
	    l=GetMechanismLink(lID,m);
	    nB=LinkNBodies(l);

	    for(bID=0;bID<nB;bID++)
	      {
		if (GetLinkBodyStatus(bID,l)!=DECOR_SHAPE)
		  {
		    p->object[p->np].linkID=lID;
		    p->object[p->np].bodyID=bID;

		    shape=GetLinkBody(bID,l);
		    DefineBulletObject(IsGroundLink(lID),shape,p);
		    p->np++;
		  }
	      }
	  }
      }
    k=p->np; /* mobile parts */
    for(oID=0;oID<no;oID++)
      {
	if ((ObstacleCanCollide(oID,nl,checkCollisionsLO))&&
	    (GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE))
	  {
	    p->object[p->np].linkID=NO_UINT;
	    p->object[p->np].bodyID=oID;

	    shape=GetObstacleShape(oID,e); 
	    DefineBulletObject(TRUE,shape,p);
	    p->np++;
	  }
      } 

    /* Now define the possible collisions */
    k=k*(p->np-1); /* k=k*(k-1)+k*(p->np-k)  link-link link-obs */
    NEW(p->p1,k,unsigned int);
    NEW(p->p2,k,unsigned int);

    p->nPairs=0;
    for(i=0;i<p->np;i++)
      {
	lID1=p->object[i].linkID;
	if (lID1!=NO_UINT) /* if object is an obstacle, skip */
	  {
	    for(j=i+1;j<p->np;j++)
	      {
		lID2=p->object[j].linkID;
		if (lID2!=NO_UINT)
		  {
		    /* link-link */
		    if (checkCollisionsLL[lID1][lID2])
		      {
			p->p1[p->nPairs]=i;
			p->p2[p->nPairs]=j;
			p->nPairs++;
		      }
		  }
		else
		  {
		    /* link-obstacle */
		    bID2=p->object[j].bodyID;
		    if (checkCollisionsLO[lID1][bID2])
		      {
			p->p1[p->nPairs]=i;
			p->p2[p->nPairs]=j;
			p->nPairs++;
		      }
		  }
	      }
	  }
      }

    p->nc=0;
    p->mc=10;
    NEW(p->collision,p->mc,TCollisionInfo);
    
    /* set the default transform for each part */
    for(i=0;i<p->np;i++)
      HTransformCopy(&(p->object[i].t),&(p->object[i].tc));

    /* Initialize the bullet world structure */
    p->bulletWorld=InitBulletWorld(cont);
  }

  boolean CheckCollisionBullet(boolean all,THTransform *tl,TBulletCD *p)
  {
    boolean collision,done,newCollision;
    unsigned int i,j,lID,n;
    double point[3],normal[3];
    TBulletObject *obj1,*obj2;
    
    /* Precompute the transforms for each part */
    for(i=0;i<p->np;i++)
      {
	lID=p->object[i].linkID;
	/* the transforms for static objecs are already pre-computed */
	if (lID!=NO_UINT)
	  {
	    if (p->object[i].type==BULLET_MESH) /* meshes have no offset */
	      HTransformCopy(&(p->object[i].t),&(tl[lID]));
	    else
	      HTransformProduct(&(tl[lID]),&(p->object[i].tc),&(p->object[i].t));
	  }
      }

    p->nc=0; /* Reset the collision information. Will be updated probably. */
    n=0;
    collision=FALSE;
    done=FALSE;
    while((!done)&&(n<p->nPairs))
      {
	i=p->p1[n];
	j=p->p2[n];
	obj1=&(p->object[i]);
	obj2=&(p->object[j]);
      
	newCollision=BulletTest(all,
				obj1->model,&(obj1->t),
				obj2->model,&(obj2->t),
				point,normal,p->bulletWorld);

	if ((all)&&(newCollision))
	  {
	    unsigned int l1,l2,k;
	    TCollisionInfo *col;

	    /* collect the collision results */
	    if (p->nc==p->mc)
	      {
		MEM_DUP(p->collision,p->mc,TCollisionInfo);
	      }

	    col=&(p->collision[p->nc]);

	    l1=obj1->linkID;
	    if (l1==NO_UINT)
	      {
		col->isLink1=FALSE;
		col->id1=obj1->bodyID;
	      }
	    else
	      {
		col->isLink1=TRUE;
		col->id1=l1;
	      }

	    l2=obj2->linkID;
	    if (l2==NO_UINT)
	      {
		col->isLink2=FALSE;
		col->id2=obj2->bodyID;
	      }
	    else
	      {
		col->isLink2=TRUE;
		col->id2=l2;
	      }
	    
	    for(k=0;k<3;k++)
	      {
		col->point[k]=point[k];
		col->normal[k]=normal[k];
	      }
	    /* Just in case ;) */
	    Normalize(3,col->normal);
	    
	    /* Store the transforms as given by the user */
	    if (col->isLink1)
	      HTransformCopy(&(col->t1),&(tl[col->id1]));
	    else
	      HTransformIdentity(&(col->t1));

	    if (col->isLink2)
	      HTransformCopy(&(col->t2),&(tl[col->id2]));
	    else
	      HTransformIdentity(&(col->t2));

	    p->nc++;
	  }

	collision=((collision)||(newCollision));

	done=((!all)&&(newCollision));

	n++;
      }
    return(collision);
  }

  boolean CheckContCollisionBullet(THTransform *tl,THTransform *tlPrev,TBulletCD *p)
  {
    if (tlPrev==NULL)
      return(CheckCollisionBullet(FALSE,tl,p));
    else
      {
	boolean collision;
	unsigned int n,i,j,lID;
	THTransform *tp;
	TBulletObject *obj1,*obj2;

	/* Precompute the transform */
	NEW(tp,p->np,THTransform);

	/* Precompute the transforms for each part */
	for(i=0;i<p->np;i++)
	  {
	    obj1=&(p->object[i]);

	    lID=obj1->linkID;

	    if (lID!=NO_UINT)
	      {
		if (obj1->type==BULLET_MESH)
		  {
		    HTransformCopy(&(obj1->t),&(tl[lID]));
		    HTransformCopy(&(tp[i]),&(tlPrev[lID]));
		  }
		else
		  {
		    HTransformProduct(&(tl[lID]),&(obj1->tc),&(obj1->t));
		    HTransformProduct(&(tlPrev[lID]),&(obj1->tc),&(tp[i]));
		  }
	      }
	    else
	      HTransformCopy(&(tp[i]),&(obj1->tc)); /* static object -> copy the offset, if any */
	  }


	p->nc=0; /* Reset the collision information. Not updated here. */
	n=0;
	collision=FALSE;
	while((!collision)&&(n<p->nPairs))
	  {
	    i=p->p1[n];
	    j=p->p2[n];
	    obj1=&(p->object[i]);
	    obj2=&(p->object[j]);

	    collision=BulletCTest(obj1->model,&(tp[i]),&(obj1->t),
				  obj2->model,&(tp[j]),&(obj2->t),p->bulletWorld);

	    n++;
	  }
	
	/* release the allocated memory */
	free(tp);

	return(collision);
      }
  }

  void DeleteBulletCD(TBulletCD *p)
  {
    unsigned int i;
    
    for(i=0;i<p->np;i++)
      DeleteBulletObject(p->object[i].model);

    free(p->object);
    free(p->p1);
    free(p->p2);
    free(p->collision);

    DeleteBulletWorld(p->bulletWorld);
  }
#endif

#ifdef _HAVE_RIGIDCLL

  boolean ObstaclesCollideLikeGround(unsigned int nl,unsigned int no,boolean **checkCollisionsLL,boolean **checkCollisionsLO)
  {  
    unsigned int i,j;
    boolean same;

    same=TRUE;
    for(i=0;((same)&&(i<no));i++)
      {
	for(j=0;((same)&&(j<nl));j++)
	  same=(checkCollisionsLO[j][i]==checkCollisionsLL[j][0]);
      }
    return(same);
  }


  void InitRigidCLLCD(Tmechanism *m,Tenvironment *e,
		      boolean **checkCollisionsLL,boolean **checkCollisionsLO,
		      TrigidCLLCD *r)
  {
    unsigned int lID1,lID2,np,no,npl,nB,lID,bID,oID,atomID;
    double *center,rad;
    Tpolyhedron *shape;
    Tlink *l;
    boolean obsLikeGround,added;

    r->r=InitRigidCLL();

    r->nl=GetMechanismNLinks(m);
    no=GetEnvironmentNObstacles(e);

    /* Create the shapes */
    NEW(center,3,double);
    NEW(r->objID,r->nl+no,unsigned int);

    /* Generate the shapes */
    np=0;
    atomID=0;
    for(lID=0;lID<r->nl;lID++)
      {
	if (LinkCanCollide(lID,r->nl,no,checkCollisionsLL,checkCollisionsLO))
	  {
	    l=GetMechanismLink(lID,m);
	    
	    if (!IsGroundLink(lID))
	      r->objID[lID]=StartRigidCLLObject(r->r);
	    else
	      r->objID[lID]=0;
	    added=FALSE;

	    nB=LinkNBodies(l);

	    for(bID=0;bID<nB;bID++)
	      {
		if (GetLinkBodyStatus(bID,l)!=DECOR_SHAPE)
		  {
		    shape=GetLinkBody(bID,l);
		    if (GetPolyhedronType(shape)!=SPHERE)
		      Error("The RigidCLL collision engine can only be used on spheres");
		    
		    GetPolyhedronCenter(center,shape);
		    rad=GetPolyhedronRadius(shape);

		    if (IsGroundLink(lID))
		      AddFixedSphere2RigidCLL(atomID,center,rad,r->r);
		    else
		      AddMobileSphere2RigidCLL(atomID,center,rad,r->r);
		    atomID++;
		    added=TRUE;
		  }
	      }

	    if (!added)
	      Error("Empty link in InitRigidCLL");

	    if (!IsGroundLink(lID))
	      CloseRigidCLLObject(r->r);
	    np++;
	  }
	else
	  r->objID[lID]=NO_UINT;
      }
    npl=np;

    /* molecular problems typically do not have 'environment' we
       treat them as rigids that will not move (will move with
       the identity transform). 
       If we ever have 'environment' it will be composed by
       a list of spheres, each acting as a single rigid.*/
    if (ObstaclesCollideLikeGround(r->nl,no,checkCollisionsLL,checkCollisionsLO))
      {
	/* Add the obstacle spheres to the ground link (in case we have obstacles
	   this will be the most usual case). */
	obsLikeGround=TRUE;
	for(oID=0;oID<no;oID++)
	  {
	    if (GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE)
	      {
		shape=GetObstacleShape(oID,e); 

		if (GetPolyhedronType(shape)!=SPHERE)
		  Error("The RigidCLL collision engine can only be used on spheres");

		GetPolyhedronCenter(center,shape);
		rad=GetPolyhedronRadius(shape);

		AddFixedSphere2RigidCLL(atomID,center,rad,r->r);
		atomID++;
	      }
	  }
      }
    else
      {
	/* add  the obstacles spheres individually */
	obsLikeGround=FALSE;
	for(oID=0;oID<no;oID++)
	  {
	    if ((ObstacleCanCollide(oID,r->nl,checkCollisionsLO))&&
		(GetObstacleShapeStatus(oID,e)!=DECOR_SHAPE))
	      {
		shape=GetObstacleShape(oID,e); 

		if (GetPolyhedronType(shape)!=SPHERE)
		  Error("The RigidCLL collision engine can only be used on spheres");

		r->objID[r->nl+oID]=StartRigidCLLObject(r->r);

		GetPolyhedronCenter(center,shape);
		rad=GetPolyhedronRadius(shape);

		AddMobileSphere2RigidCLL(atomID,center,rad,r->r);
		atomID++;

		CloseRigidCLLObject(r->r);
		np++;
	      }
	  } 
      }
    
    /* init the space for the transforms */
    NEW(r->t,np,THTransform);
    /* the ground link does not move */
    HTransformIdentity(&(r->t[0]));
    /* The obstacles will never move */
    if (!obsLikeGround)
      {
	for(no=npl;no<np;no++)
	  HTransformIdentity(&(r->t[no]));
      }

    /* Now define the possible collisions */
    for(lID1=0;lID1<r->nl;lID1++)
      {
	for(lID2=lID1+1;lID2<r->nl;lID2++)
	  {
	    if (checkCollisionsLL[lID1][lID2])
	      ActivateCollisionsRigidCLL(r->objID[lID1],r->objID[lID2],r->r);
	    else
	      DeactivateCollisionsRigidCLL(r->objID[lID1],r->objID[lID2],r->r);
	  }
	if (!obsLikeGround)
	  {
	    for(oID=0;oID<no;oID++)
	      {
		if (checkCollisionsLO[lID1][oID])
		  ActivateCollisionsRigidCLL(r->objID[lID1],r->objID[r->nl+oID],r->r);
		else
		  DeactivateCollisionsRigidCLL(r->objID[lID1],r->objID[r->nl+oID],r->r);
	      }
	  }
      }
    free(center);
  }

  boolean CheckCollisionRigidCLL(THTransform *tl,TrigidCLLCD *r)
  {
    unsigned int i;

    for(i=0;i<r->nl;i++)
      {
	if (r->objID[i]!=NO_UINT)
	  HTransformCopy(&(r->t[r->objID[i]]),&(tl[i]));
      }

    return(MoveAndCheckRigidCLL(r->t,r->r));
  }

  void DeleteRigidCLLCD(TrigidCLLCD *r)
  {
    DeleteRigidCLL(r->r);
    free(r->t);
    free(r->objID);
  }

#endif


/************************************************************************************************/
/* Private functions: generic functions on arrays of detected collisions. Only some engines
   are able to generate such arrays (SOLID and FCL) */

void StoreCollisionInfoInt(FILE *f,char *fname,unsigned int objectID,Tmechanism *m,unsigned int nc,TCollisionInfo *c)
{
  if (nc>0)
    {
      unsigned int i,j;
      unsigned int lID1,lID2;
      boolean isLink1,isLink2;
      THTransform *t1,*t2;
      char *ln1,*ln2;
      char *wname="world";

      fprintf(f,"fname='%s';\n\n",fname);
      for(i=0;i<nc;i++)
	{
	  /* We are only interested on collisions with respect to the manipulated object (which actually is a link) */
	  if ((objectID==NO_UINT)||
	      ((c[i].isLink1)&&(c[i].id1==objectID))||
	      ((c[i].isLink2)&&(c[i].id2==objectID)))
	    {
	      j=i+1; /* printed indices start at 1 */

	      if ((objectID==NO_UINT)||((c[i].isLink1)&&(c[i].id1==objectID)))
		{
		  isLink1=c[i].isLink1;
		  isLink2=c[i].isLink2;
		  lID1=c[i].id1;
		  lID2=c[i].id2;
		  t1=&(c[i].t1);
		  t2=&(c[i].t2);
		}
	      else
		{
		  isLink1=c[i].isLink2;
		  isLink2=c[i].isLink1;
		  lID1=c[i].id2;
		  lID2=c[i].id1;
		  t1=&(c[i].t2);
		  t2=&(c[i].t1);
		}

	      ln1=(isLink1?GetLinkName(GetMechanismLink(lID1,m)):wname);
	      ln2=(isLink2?GetLinkName(GetMechanismLink(lID2,m)):wname);

	      fprintf(f,"p_%u=[%.16f %.16f %.16f 1]';\n\n",j,c[i].point[0],c[i].point[1],c[i].point[2]);

	      fprintf(f,"T1_%u=[",j);
	      HTransformPrint(f,t1);
	      fprintf(f,"];\nlname1_%u='%s';\n\n",j,ln1);
      
	      fprintf(f,"T2_%u=[",j);
	      HTransformPrint(f,t2);
	      fprintf(f,"];\nlname2_%u='%s';\n\n\n\n",j,ln2);
	    }
	}
      for(i=0;i<nc;i++)
	{
	  j=i+1;
	  fprintf(f,"GenerateContactEqs(%u,fname,p_%u,lname1_%u,T1_%u,lname2_%u,T2_%u);\n",j,j,j,j,j,j);
	}
      fprintf(f,"\n\n\nexit\n");
    }
}


void PrintCollisionInfoInt(THTransform *tl,Tmechanism *m,Tenvironment *e,
			   unsigned int nc,TCollisionInfo *c)
{
  char *ln1,*ln2;
  unsigned int i;
  double p1[3],p2[3];
  THTransform t1,t2;

  /* if we stored any the collision information */
  for(i=0;i<nc;i++)
    {
      ln1=(c[i].isLink1?GetLinkName(GetMechanismLink(c[i].id1,m)):GetObstacleName(c[i].id1,e));
      ln2=(c[i].isLink2?GetLinkName(GetMechanismLink(c[i].id2,m)):GetObstacleName(c[i].id2,e));

      /* Transform the contact point given in global coordinates to local 
	 coordinates of the two involved bodies*/
      HTransformInverse(&(c[i].t1),&t1);
      HTransformApply(c[i].point,p1,&t1);

      HTransformInverse(&(c[i].t2),&t2);
      HTransformApply(c[i].point,p2,&t2);
	
      fprintf(stderr,"   - %s and %s collide at (%.16f,%.16f,%.16f) (%.16f,%.16f,%.16f)\n",
	      ln1,ln2,p1[0],p1[1],p1[2],p2[0],p2[1],p2[2]);

      HTransformDelete(&t1);
      HTransformDelete(&t2);
    }
}

/************************************************************************************************/


void InitCD(unsigned int engine,boolean parallel,
	    Tmechanism *m,Tenvironment *e,
	    boolean **checkCollisionsLL,boolean **checkCollisionsLO,
	    TworldCD *cd)
{
  cd->solid=NULL;
  cd->vcollide=NULL;
  cd->pqp=NULL;
  cd->fcl=NULL;
  cd->rigidCLL=NULL;

  switch(engine)
    {
    case SOLID:
      #ifdef _HAVE_SOLID
        NEW(cd->solid,1,TsolidCD);
        InitSolidCD(parallel,m,e,checkCollisionsLL,checkCollisionsLO,cd->solid);
	cd->engine=SOLID;
      #else
        Error("SOLID collision detection engine is not available");
      #endif
      break;

    case VCOLLIDE:
      #ifdef _HAVE_VCOLLIDE
        NEW(cd->vcollide,1,TvcollideCD);
	InitVcollideCD(m,e,checkCollisionsLL,checkCollisionsLO,cd->vcollide);
	cd->engine=VCOLLIDE;
      #else
        Error("VCOLLIDE collision detection engine is not available");
      #endif
      break;

    case PQP:
      #ifdef _HAVE_PQP
        NEW(cd->pqp,1,TpqpCD);
	InitPQPCD(m,e,checkCollisionsLL,checkCollisionsLO,cd->pqp);
	cd->engine=PQP;
      #else
        Error("PQP collision detection engine is not available");
      #endif
      break;

    case FCL:
    case C_FCL:
      #ifdef _HAVE_FCL
        NEW(cd->fcl,1,TfclCD);
	InitFCLCD(m,e,checkCollisionsLL,checkCollisionsLO,cd->fcl);
	cd->engine=engine; 
      #else
        Error("FCL collision detection engine is not available");
      #endif
      break;

    case BULLET:
    case C_BULLET:
      #ifdef _HAVE_BULLET
        NEW(cd->bullet,1,TBulletCD);
	InitBulletCD(m,e,checkCollisionsLL,checkCollisionsLO,(engine==C_BULLET),cd->bullet);
	cd->engine=engine; 
      #else
        Error("BULLET collision detection engine is not available");
      #endif
      break;

    case RIGIDCLL:
      #ifdef _HAVE_RIGIDCLL
        NEW(cd->rigidCLL,1,TrigidCLLCD);
	InitRigidCLLCD(m,e,checkCollisionsLL,checkCollisionsLO,cd->rigidCLL);
	cd->engine=RIGIDCLL;
      #else
        Error("RigidCLL collision detection engine is not available");
      #endif
      break;

    case NOCD:
      break;

    default:
      Error("Undefined collision detection engine");
    }
}

boolean LinkCanCollide(unsigned int l,unsigned int nl,unsigned int no,
		       boolean **checkCollisionsLL,boolean **checkCollisionsLO)
{
  unsigned int i;
  boolean found;
    
  found=FALSE;
  i=0;
  while((!found)&&(i<nl))
    {
      found=checkCollisionsLL[l][i];
      i++;
    }
  i=0;
  while((!found)&&(i<no))
    {
      found=checkCollisionsLO[l][i];
      i++;
    }
  return(found); 
}

boolean ObstacleCanCollide(unsigned int o,unsigned int nl,boolean **checkCollisionsLO)
{
  unsigned int i;
  boolean found;

  found=FALSE;
  i=0;
  while((!found)&&(i<nl))
    {
      found=checkCollisionsLO[i][o];
      i++;
    }
  return(found);
}

unsigned int GetCDEngine(TworldCD *cd)
{
  return(cd->engine);
}

boolean CheckCollision(boolean all,
		       THTransform *tl,TLinkConf *def,
		       THTransform *tlPrev,TLinkConf *defPrev,
		       TworldCD *cd)
{
  boolean collision=FALSE;

  switch (cd->engine)  
    {
    case SOLID:
      #ifdef _HAVE_SOLID
        collision=CheckCollisionSolid(all,tl,def,cd->solid);
      #else
        Error("SOLID collision detection engine is not available");
      #endif
      break;

    case VCOLLIDE:
      #ifdef _HAVE_VCOLLIDE
        /* flag 'all' is not honored */
        collision=CheckCollisionVcollide(tl,cd->vcollide);
      #else
        Error("VCOLLIDE collision detection engine is not available");
      #endif
      break;

    case PQP:
      #ifdef _HAVE_PQP
        /* flag 'all' is not honored */
        collision=CheckCollisionPQP(tl,cd->pqp);
      #else
        Error("PQP collision detection engine is not available");
      #endif
      break;

    case FCL:
      #ifdef _HAVE_FCL
        collision=CheckCollisionFCL(all,tl,cd->fcl);
      #else
        Error("FCL collision detection engine is not available");
      #endif
      break;

    case C_FCL:
      #ifdef _HAVE_FCL
        collision=CheckContCollisionFCL(tl,tlPrev,cd->fcl);
      #else
        Error("FCL collision detection engine is not available");
      #endif
      break;

    case BULLET:
      #ifdef _HAVE_BULLET
        collision=CheckCollisionBullet(all,tl,cd->bullet);
      #else
        Error("BULLET collision detection engine is not available");
      #endif
      break;

    case C_BULLET:
      #ifdef _HAVE_BULLET
        collision=CheckContCollisionBullet(tl,tlPrev,cd->bullet);
      #else
        Error("BULLET collision detection engine is not available");
      #endif
      break;

    case RIGIDCLL:
      #ifdef _HAVE_RIGIDCLL
        /* flag 'all' is not honored */
        collision=CheckCollisionRigidCLL(tl,cd->rigidCLL);
      #else
        Error("RigidCLL collision detection engine is not available");
      #endif
      break;

    case NOCD:
      break;

    default:
      Error("Undefined collision detection engine");
    }

  return(collision);
}

void StoreCollisionInfo(FILE *f,char *fname,unsigned int objectID,Tmechanism *m,TworldCD *cd)
{
  switch (cd->engine)  
    {
    case SOLID:
      #ifdef _HAVE_SOLID
        StoreCollisionInfoInt(f,fname,objectID,m,cd->solid->nc,cd->solid->collision);
      #else
        Error("SOLID collision detection engine is not available");
      #endif
      break;
    case FCL:
      #ifdef _HAVE_FCL
        StoreCollisionInfoInt(f,fname,objectID,m,cd->fcl->nc,cd->fcl->collision);
      #else
        Error("FCL collision detection engine is not available");
      #endif
      break;
    case BULLET:
      #ifdef _HAVE_BULLET
        StoreCollisionInfoInt(f,fname,objectID,m,cd->bullet->nc,cd->bullet->collision);
      #else
        Error("Bullet collision detection engine is not available");
      #endif
      break;
    }
}

void PrintCollisionInfo(THTransform *tl,Tmechanism *m,Tenvironment *e,TworldCD *cd)
{
  switch (cd->engine)  
    {
    case SOLID:
      #ifdef _HAVE_SOLID
        PrintCollisionInfoInt(tl,m,e,cd->solid->nc,cd->solid->collision);
      #else
        Error("SOLID collision detection engine is not available");
      #endif
      break;
    case FCL:
      #ifdef _HAVE_FCL
        PrintCollisionInfoInt(tl,m,e,cd->fcl->nc,cd->fcl->collision);
      #else
        Error("FCL collision detection engine is not available");
      #endif
      break;
    case BULLET:
      #ifdef _HAVE_BULLET
        PrintCollisionInfoInt(tl,m,e,cd->bullet->nc,cd->bullet->collision);
      #else
        Error("Bullet collision detection engine is not available");
      #endif
      break;
    }
}


void DeleteCD(TworldCD *cd)
{
  switch (cd->engine)
    {
    case SOLID:
      #ifdef _HAVE_SOLID
        DeleteSolidCD(cd->solid);
        free(cd->solid);
      #endif
      cd->solid=NULL;
      break;

    case VCOLLIDE:
      #ifdef _HAVE_VCOLLIDE
        DeleteVcollideCD(cd->vcollide);
	free(cd->vcollide);
      #endif
      cd->vcollide=NULL;
      break;

    case PQP:
      #ifdef _HAVE_PQP
        DeletePQPCD(cd->pqp);
	free(cd->pqp);
      #endif
      cd->pqp=NULL;
      break;

    case FCL:
    case C_FCL:
      #ifdef _HAVE_FCL
        DeleteFCLCD(cd->fcl);
	free(cd->fcl);
      #endif
      cd->fcl=NULL;
      break;

    case BULLET:
    case C_BULLET:
      #ifdef _HAVE_BULLET
        DeleteBulletCD(cd->bullet);
	free(cd->bullet);
      #endif
      cd->bullet=NULL;
      break;

    case RIGIDCLL:
      #ifdef _HAVE_RIGIDCLL
        DeleteRigidCLLCD(cd->rigidCLL);
	free(cd->rigidCLL);
      #endif
      cd->rigidCLL=NULL;
      break;

    case NOCD:
      break;

    default:
      Error("Undefined collision detection engine (d)");
    }
}

