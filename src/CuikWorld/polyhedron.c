#include "polyhedron.h"

#include "htransform.h"
#include "error.h"
#include "algebra.h"
#include "geom.h"
#include "boolean.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <locale.h>
#include <sys/stat.h>

#if (_ASSIMP)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wattributes"
    #include <assimp/scene.h>
    #include <assimp/postprocess.h>
    #include <assimp/cimport.h>
    #include <assimp/cexport.h>
  #pragma GCC diagnostic pop
#endif

/** \file polyhedron.c
    \brief Implementaton of the function operating on Tpolyhedron.
    
    Implementaton of the function operating on Tpolyhedron.

    \sa Tpolyhedron, polyhedron.h.
*/

/** 
   \brief Constructor

   Constructs a convex polyhedrom from a general mesh file via the assimp library. 

   \param fn The file name from where to read the information.
   \param p The convex polyhedron to create.

   \return TRUE if the file can be read successfully.
*/
boolean ReadGeneralMesh(char *fn,Tpolyhedron *p);

/** 
   \brief Constructor.

   Constructs a convex polyhedrom from a binary STL file. 

   The parsing of the STL file is done following the instructions given
   <a href="http://en.wikipedia.org/wiki/STL_(file_format)">here</a>.

   \param fn The file name from where to read the information.
   \param p The convex polyhedron to create.
*/
void ReadSTL(char *fn,Tpolyhedron *p);

/** 
   \brief Constructor.

   Constructs a convex polyhedrom from a file. This function is to be used
   when the heading of the file is already processed and the file
   includes for sure the definition of an OFF.

   \param f The file from where to read the information.
   \param color TRUE if the off includes color information for each vertex (it
                is actually a COFF).
   \param p The convex polyhedron to create.
*/
void ReadOFF(FILE *f,boolean color,Tpolyhedron *p);

/** 
   \brief Generates an OFF that approximates a cylinder.

   Generates and OFF that approximates a cylinder. This polyhedric approximation
   is the one used int collision detection.

   Note that only the vertexes of the OFFS are generates (no face information
   is created) since for collision detection only the vertexes of the convex
   polyhedrons are used.

   \param g The granularity to use to create the polytope that approximates
            the cylinder.
   \param p The cylinder to approximate.
*/
void GenerateCylinderOFF(unsigned int g,Tpolyhedron *p);

/** 
   \brief Constructor.

   Constructs a convex polyhedrom from a file. This function is to be used
   when the heading of the file is already processed and the file
   includes for sure the definition of an LINE.

   \param f The file from where to read the information.
   \param p The convex polyhedron to create.
*/
void ReadLine(FILE *f,Tpolyhedron *p);

/** 
   \brief Constructor.

   Constructs a convex polyhedrom from a file. This function is to be used
   when the heading of the file is already processed and the file
   includes for sure the definition of an SEGMENT.

   \param f The file from where to read the information.
   \param p The convex polyhedron to create.
*/
void ReadSegments(FILE *f,Tpolyhedron *p);

/** 
   \brief Constructor.

   Constructs a convex polyhedrom from a file. This function is to be used
   when the heading of the file is already processed and the file
   includes for sure the definition of an CYLINDER.

   \param f The file from where to read the information.
   \param g The granularity to use to create the polytope that approximates
            the cylinder.
   \param p The convex polyhedron to create.
*/
void ReadCylinder(FILE *f,unsigned int g,Tpolyhedron *p);

/** 
   \brief Generates an OFF that approximates a sphere.

   Generates and OFF that approximates a sphere. This polyhedric approximation
   is the one used int collision detection.

   Note that only the vertexes of the OFFS are generates (no face information
   is created) since for collision detection only the vertexes of the convex
   polyhedrons are used.

   \param g The granularity to use to create the polytope that approximates
            the sphere.
   \param p The sphere to approximate.
*/
void GenerateSphereOFF(unsigned int g,Tpolyhedron *p);

/** 
   \brief Constructor.

   Constructs a convex polyhedrom from a file. This function is to be used
   when the heading of the file is already processed and the file
   includes for sure the definition of an SPHERE.

   \param f The file from where to read the information.
   \param g The granularity to use to create the polytope that approximates
            the sphere.
   \param p The convex polyhedron to create.
*/
void ReadSphere(FILE *f,unsigned int g,Tpolyhedron *p);

#if (_ASSIMP)
/** 
   \brief Counts the number of vertices and faces in a given scene node.

   Counts the number of vertices and faces in a given scene node including those in the
   child nodes.

   \param sc The scene.
   \param nv The number of vertices.
   \param nf The number of faces.
   \param nd The current node in the scene.
*/
void CountSceneVF(const struct aiScene *sc,unsigned int *nv,unsigned int *nf,const struct aiNode *nd);

/** 
    \brief Process the information in a geometry node.

    Process the information in a node (and in their children nodes). We basically
    search for meshes and their relative transformation w.r.t. the world reference
    system.

    For meshes with colors in the vertices, we only take into account the first color
    (we can not specify more than one color per vertex in geomview). 
    It can be the case that some meshes have colors and others not. In the case of
    missing colors, we use the default color of the object, which must be initialized
    before calling this function.
    
    \param tParent Transform from the root to the parent node.
    \param oV Number of vertexes so far.
    \param oF Number of faces so far.
    \param p The polyhedron to defined.
    \param sc The scene.
    \param nd The current node in the scene.
*/
void ProcessSceneNode(THTransform *tParent,unsigned int *oV,unsigned int *oF,
		      Tpolyhedron *p,const struct aiScene *sc,const struct aiNode *nd);

void CountSceneVF(const struct aiScene *sc,unsigned int *nv,unsigned int *nf,const struct aiNode *nd)
{
  unsigned int k,nv1,nf1;
  const struct aiMesh *mesh;

  *nv=0;
  *nf=0;
  for(k=0;k<nd->mNumMeshes;k++)
    {
      mesh=sc->mMeshes[nd->mMeshes[k]];
      (*nv)+=mesh->mNumVertices;
      (*nf)+=mesh->mNumFaces;
    }

  /* Recursively process the sub-scenes */
  for(k=0;k<nd->mNumChildren;k++)
    {
      CountSceneVF(sc,&nv1,&nf1,nd->mChildren[k]);
      (*nv)+=nv1;
      (*nf)+=nf1;
    }
}

void ProcessSceneNode(THTransform *tParent,unsigned int *oV,unsigned int *oF,
		      Tpolyhedron *p,const struct aiScene *sc,const struct aiNode *nd)
{
  unsigned int i,j,k;
  THTransform tr;
  const struct aiMesh *mesh;
  unsigned int ndxV,ndxF;
  double r,g,b,mr,mg,mb;
  struct aiColor4D mColor;

  /* Get the transform for this node */
  HTransformSetElement(0,0,nd->mTransformation.a1,&tr);
  HTransformSetElement(0,1,nd->mTransformation.a2,&tr);
  HTransformSetElement(0,2,nd->mTransformation.a3,&tr);
  HTransformSetElement(0,3,nd->mTransformation.a4,&tr);

  HTransformSetElement(1,0,nd->mTransformation.b1,&tr);
  HTransformSetElement(1,1,nd->mTransformation.b2,&tr);
  HTransformSetElement(1,2,nd->mTransformation.b3,&tr);
  HTransformSetElement(1,3,nd->mTransformation.b4,&tr);

  HTransformSetElement(2,0,nd->mTransformation.c1,&tr);
  HTransformSetElement(2,1,nd->mTransformation.c2,&tr);
  HTransformSetElement(2,2,nd->mTransformation.c3,&tr);
  HTransformSetElement(2,3,nd->mTransformation.c4,&tr);

  HTransformSetElement(3,0,nd->mTransformation.d1,&tr);
  HTransformSetElement(3,1,nd->mTransformation.d2,&tr);
  HTransformSetElement(3,2,nd->mTransformation.d3,&tr);
  HTransformSetElement(3,3,nd->mTransformation.d4,&tr);
  
  HTransformProduct(tParent,&tr,&tr);

  /* Add the meshes to the polyhedron structure */
  for(k=0;k<nd->mNumMeshes;k++)
    {
      mesh=sc->mMeshes[nd->mMeshes[k]];

      if (aiGetMaterialColor(sc->mMaterials[mesh->mMaterialIndex],AI_MATKEY_COLOR_DIFFUSE,&mColor)==aiReturn_SUCCESS)
	{
	  mr=(double)mColor.r;
	  mg=(double)mColor.g;
	  mb=(double)mColor.b;
	}
      else
	{
	  /* if we do not have color in the material, use the user provided color */
	  mr=GetRed(&(p->color));
	  mg=GetGreen(&(p->color));
	  mb=GetBlue(&(p->color));
	}

      for(i=0;i<mesh->mNumVertices;i++)
	{	    
	  ndxV=(*oV)+i;
	  
	  NEW(p->v[ndxV],3,double);
	  p->v[ndxV][0]=(double)mesh->mVertices[i].x;
	  p->v[ndxV][1]=(double)mesh->mVertices[i].y;
	  p->v[ndxV][2]=(double)mesh->mVertices[i].z;
	  
	  HTransformApply(p->v[ndxV],p->v[ndxV],&tr);

	  if (p->cv!=NULL) /* we can have colors per vertex */
	    {
	      /* If possible get the color directly assigned to the vertex */
	      /* We only consider one color per vertex */
	      if (mesh->mColors[0]!=NULL)
		{
		  r=(double)mesh->mColors[0][i].r;
		  g=(double)mesh->mColors[0][i].g;
		  b=(double)mesh->mColors[0][i].b;
		}
	      else
		{
		  /* If we do not have individual colors per vertes,
		     get the color from the mesh material, if available, and
		     otherwise, from the user provided color (see above) */
		  r=mr;
		  b=mb;
		  g=mg;
		}
	      NewColor(r,g,b,&(p->cv[ndxV]));
	    }
	}
      
      for(i=0;i<mesh->mNumFaces;i++)
	{
	  ndxF=(*oF)+i;
	  p->nvf[ndxF]=mesh->mFaces[i].mNumIndices;
	  NEW(p->fv[ndxF],p->nvf[i],unsigned int);
	  for(j=0;j<p->nvf[ndxF];j++)
	    p->fv[ndxF][j]=((*oV)+mesh->mFaces[i].mIndices[j]);
	}
      (*oV)+=mesh->mNumVertices;
      (*oF)+=mesh->mNumFaces;
    }

  /* Recursively process the child nodes */
  for(i=0;i<nd->mNumChildren;i++)
    ProcessSceneNode(&tr,oV,oF,p,sc,nd->mChildren[i]);
}
#endif

boolean WriteDAEMesh(char *fn,Tpolyhedron *p)
{
  boolean ok=FALSE;

  #if (_ASSIMP)
    const struct aiScene *sc;

    if ((p->type!=OFF)&&(p->type!=COFF))
      Error("Can only export meshes to collada (dae)");
    
    ok=TRUE;
	
    SavePolyhedron("/tmp/tmp.off",p);
    sc=aiImportFile("/tmp/tmp.off",0);
    if ((sc)&&(sc->mNumMeshes>0))
      {
	char command[2000];
      
	/* Valid export formats:
	   id: collada
	   dsc: COLLADA - Digital Asset Exchange Schema
	   ext: dae

	   id: obj
	   dsc: Wavefront OBJ format
	   ext: obj
	   
	   id: stl
	   dsc: Stereolithography
	   ext: stl
	   
	   id: ply
	   dsc: Stanford Polygon Library
	   ext: ply
	*/
      
	if (aiExportScene(sc,"collada",fn,aiProcess_Triangulate|aiProcess_GenNormals)!=aiReturn_SUCCESS)
	  Error("Error writting the geometry file");

	/* This is to fix a bug in the assimp library (labels can not include '<' of '>') */
	sprintf(command,"gsed -i 's/<node id=\"<OFFRoot>\" name=\"<OFFRoot>\">/<node id=\"OFFRoot\" name=\"OFFRoot\">/g' %s",fn);
	system(command);
	/* Set the scale to meters (the default in gazebo) */
	sprintf(command,"gsed -i 's/centimeter\" meter=\"0.01/meter\" meter=\"1/g' %s",fn);
	system(command);
      
	aiReleaseImport(sc);
      }
    else
      Error("Error reading the geometry file");
  #else
    Error("The assimp library is missing");
  #endif

  return(ok);
}
  
boolean ReadGeneralMesh(char *fn,Tpolyhedron *p)
{
  boolean ok=FALSE;

  #if (_ASSIMP)
    const struct aiScene *sc;
    
    /* We triangulate (as required by some collision detection
       engines). */
    sc=aiImportFile(fn,aiProcess_Triangulate);

    if ((sc)&&(sc->mNumMeshes>0))
      {
	unsigned int oV,oF;
	THTransform t0;

	/* For general meshes, we assume that the files include
	   color information */
	p->type=COFF;

	ok=TRUE;
	    
	/* Count the total number of vertices and faces
	   in the scene. */
	CountSceneVF(sc,&(p->nv),&(p->nf),sc->mRootNode);
 
	p->ne=0;/* Number of edges not used */

	/* allocate enough space for all the vertices */
	NEW(p->v,p->nv,double*);
	NEW(p->cv,p->nv,Tcolor);	
	
	/* allocate space  for all the faces */
	NEW(p->nvf,p->nf,unsigned int);
	NEW(p->fv,p->nf,unsigned int*);

	/* Recursively process all the nodes in the scene */
	oV=0;
	oF=0;
	HTransformIdentity(&t0);
	ProcessSceneNode(&t0,&oV,&oF,p,sc,sc->mRootNode);

	aiReleaseImport(sc);
      }
    else
      {
	fprintf(stderr,"File: %s\n",fn);
	Error("Error reading the geometry file (ReadGeneralMesh)");
      }
  #else
    Error("The assimp library is missing");
  #endif

  return(ok);
}

void ReadSTL(char *fn,Tpolyhedron *p)
{
  char header[75];
  short int u;
  float v[3];
  double vd[3];
  unsigned int nt,i,j,k;
  boolean found;
  FILE *f;

  f=fopen(fn,"rb");
  if (!f)
    Error("Can not open STL file");

  p->type=OFF;

  fread(header,sizeof(char),5,f);
  header[5]=0;
  if (strcasecmp(header,"SOLID")==0)
    Error("Can not read ASCII STL files yet");
  /* skip the rest of the header */
  fread(header,sizeof(char),75,f);

  /* read the number of triangles */
  fread(&nt,sizeof(int),1,f);
  
  p->nv=0; /* this will be increased as needed */
  p->nf=nt;
  p->ne=0; /* not used */

  /* allocate enough space for all the vertices */
  NEW(p->v,nt,double*);

  /* Cancel the color per vertex information */
  p->cv=NULL;
  
  /* and for all the faces */
  NEW(p->nvf,nt,unsigned int);
  NEW(p->fv,nt,unsigned int*);
  
  for(i=0;i<nt;i++)
    {
      /* skip the normal */
      fread(v,sizeof(float),3,f);

      p->nvf[i]=3; /* all faces have 3 vertices */
      NEW(p->fv[i],p->nvf[i],unsigned int);

      for(j=0;j<3;j++)
	{
	  /* read the vertex and convert it to double */
	  fread(v,sizeof(float),3,f);
	  vd[0]=(double)v[0];
	  vd[1]=(double)v[1];
	  vd[2]=(double)v[2];

	  /* Check if we already have this vertex (with 1e-3 accuracy) */
	  found=FALSE;
	  k=0;
	  while((!found)&&(k<p->nv))
	    {
	      found=(Distance(3,vd,p->v[k])<1e-3);
	      if (!found) k++;
	    }
	  if (!found)
	    {
	      /* k==p->nv */
	      NEW(p->v[k],3,double);
	      p->v[k][0]=vd[0];
	      p->v[k][1]=vd[1];
	      p->v[k][2]=vd[2];
	      p->nv++;
	    }
	  p->fv[i][j]=k;
	}

      /* skip the tail (supposed to be 0 always) */
      fread(&u,sizeof(short),1,f);
    }
  fclose(f);
}

void ReadOFF(FILE *f,boolean color,Tpolyhedron *p)
{
  unsigned int i,j;
  double av,r,g,b,a;

  if (color)
    p->type=COFF;
  else
    p->type=OFF;

  fscanf(f,"%u",&(p->nv));
  fscanf(f,"%u",&(p->nf));
  fscanf(f,"%u",&(p->ne));
  if ((p->nv==0)||(p->nf==0))
    Error("Empty OFF");

  NEW(p->v,p->nv,double*);
  if (color)
    { NEW(p->cv,p->nv,Tcolor); }
  else
    p->cv=NULL;
  for(i=0;i<p->nv;i++)
    {
      NEW(p->v[i],3,double);
      fscanf(f,"%lf",&(p->v[i][0]));
      fscanf(f,"%lf",&(p->v[i][1]));
      fscanf(f,"%lf",&(p->v[i][2]));
      if (color)
	{
	  fscanf(f,"%lf",&r);
	  fscanf(f,"%lf",&g);
	  fscanf(f,"%lf",&b);
	  fscanf(f,"%lf",&a); // Alpha channel: always 1, not used
	  NewColor(r,g,b,&(p->cv[i]));
	}	
    }
  
  NEW(p->nvf,p->nf,unsigned int);
  NEW(p->fv,p->nf,unsigned int*);
  for(i=0;i<p->nf;i++)
    {
      fscanf(f,"%u",&(p->nvf[i]));
      if (p->nvf[i]==0)
	Error("Empty face in OFF");

      NEW(p->fv[i],p->nvf[i],unsigned int); 

      for(j=0;j<p->nvf[i];j++)
	fscanf(f,"%u",&(p->fv[i][j]));
    }

  /* Cancel the sphere information */
  p->rad=0;
  p->gr=0;
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /* and the cylinder information too */
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /* Compute the bounding box */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }
}

void GenerateCylinderOFF(unsigned int g,Tpolyhedron *p)
{
  unsigned int i,j,k,n;
  THTransform m;
  double a,av;

  if ((p->type!=CYLINDER)&&(p->type!=LINE))
    Error("Using GenerateCylinderOFF in a non cylindric/line convex polyhedron");

  /*The points are defined on the reference cylinder (aligned along axis X
    and with length 1 and radii 1) that is later on scaled and enlarged */
  n=4+g;
  p->nv=2*n;
  NEW(p->v,p->nv,double*);
  for(i=0;i<n;i++)
    {
      NEW(p->v[i],3,double);
      NEW(p->v[n+i],3,double);

      p->v[i][0]=0;
      p->v[n+i][0]=1;

      a=((double)i/(double)n)*M_2PI;
      p->v[i][1]=p->v[n+i][1]=cos(a);
      p->v[i][2]=p->v[n+i][2]=sin(a);
    }
  
  /*Now rotate the points according to the cylinder orientation defined by p1,p2*/
  HTransformX2Vect(p->rad,p->rad,p->p1,p->p2,&m);

  for(i=0;i<p->nv;i++)
    HTransformApply(p->v[i],p->v[i],&m);

  HTransformDelete(&m);

  /* face information */
  p->nf=n+2*(n-2);
  p->ne=0; /* not used */

  /* Cancel the color per vertex information */
  p->cv=NULL;
  
  NEW(p->nvf,p->nf,unsigned int);
  NEW(p->fv,p->nf,unsigned int*);
  /* lateral faces */
  for(i=0;i<n;i++)
    {
      j=(i+1)%n;

      p->nvf[i]=4;
      NEW(p->fv[i],4,unsigned int);
      p->fv[i][0]=i;
      p->fv[i][1]=i+n;
      p->fv[i][2]=j+n;
      p->fv[i][3]=j;
    }
  /* up faces */
  for(i=2;i<n;i++)
    {
      k=n+i-2;
      p->nvf[k]=3;
      NEW(p->fv[k],3,unsigned int);
      p->fv[k][0]=n+0;
      p->fv[k][1]=n+i;
      p->fv[k][2]=n+i-1;
    }
  for(i=2;i<n;i++)
    {
      k=n+(n-2)+i-2;
      p->nvf[k]=3;
      NEW(p->fv[k],3,unsigned int);
      p->fv[k][0]=i-1;
      p->fv[k][1]=i;
      p->fv[k][2]=0;
    }

  /* Compute the bounding box using the points that approximate the cylinder */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }
}

void ReadLine(FILE *f,Tpolyhedron *p)
{
  p->type=LINE;

  p->rad=0.01;

  fscanf(f,"%lf",&(p->p1[0]));
  fscanf(f,"%lf",&(p->p1[1]));
  fscanf(f,"%lf",&(p->p1[2]));

  fscanf(f,"%lf",&(p->p2[0]));
  fscanf(f,"%lf",&(p->p2[1]));
  fscanf(f,"%lf",&(p->p2[2]));

  /*Cancel sphere information*/
  p->gr=0;
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /*Generate the OFF information*/
  GenerateCylinderOFF(0,p);
}

void ReadSegments(FILE *f,Tpolyhedron *p)
{
  unsigned int i,j;
  double av;

  p->type=SEGMENTS;

 fscanf(f,"%u",&(p->nv));

 NEW(p->v,p->nv,double*);
 for(i=0;i<p->nv;i++)
   {
     NEW(p->v[i],3,double);
     fscanf(f,"%lf",&(p->v[i][0]));
     fscanf(f,"%lf",&(p->v[i][1]));
     fscanf(f,"%lf",&(p->v[i][2]));
   }
 /* Compute the bounding box */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }

  /*Cancel sphere information*/
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /* Cancel cylinder/line info */
  p->rad=0;
  p->gr=0;
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /*Cancel OFF information*/
  p->nf=0;
  p->nvf=0;
  p->ne=0;
  
  /* Cancel the color per vertex information */
  p->cv=NULL;
}

void ReadCylinder(FILE *f,unsigned int g,Tpolyhedron *p)
{
  p->type=CYLINDER;

  fscanf(f,"%lf",&(p->rad));

  fscanf(f,"%lf",&(p->p1[0]));
  fscanf(f,"%lf",&(p->p1[1]));
  fscanf(f,"%lf",&(p->p1[2]));

  fscanf(f,"%lf",&(p->p2[0]));
  fscanf(f,"%lf",&(p->p2[1]));
  fscanf(f,"%lf",&(p->p2[2]));

  /* Keep granularity */
  p->gr=g;
  
  /*Cancel sphere information*/
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /*Generate the OFF information*/
  GenerateCylinderOFF(g,p);
}

void GenerateSphereOFF(unsigned int g,Tpolyhedron *p)
{
  unsigned int i,j,k,in,r1,r2,n,m;
  double **meridian;
  THTransform tr,t;
  double a,offset,av;

  if (p->type!=SPHERE)
    Error("Using GenerateSphereOFF in a non spheric convex polyhedron");

  /*Vertex information for collision avoidance (in the future refined according to 'g')*/
  n=3+g;
  m=4+g;

  offset=M_PI/((double)n-1);
  a=-M_PI_2;

  NEW(meridian,n,double*);
  for(i=0;i<n;i++)
    {
      NEW(meridian[i],3,double);
      meridian[i][0]=p->rad*cos(a);
      meridian[i][1]=0.0;
      meridian[i][2]=p->rad*sin(a);

      a+=offset;
    }

  p->nv=n*m;
  NEW(p->v,p->nv,double*);
  for(i=0;i<p->nv;i++)
    NEW(p->v[i],3,double);

  a=0.0;
  offset=M_2PI/(double)m;

  HTransformTxyz(p->center[0],p->center[1],p->center[2],&t);
  for(j=0;j<m;j++)
    {
      HTransformRz(a,&tr);
      HTransformProduct(&t,&tr,&tr);
      for(i=0;i<n;i++)
	HTransformApply(meridian[i],p->v[j*n+i],&tr);

      a+=offset;
      
      HTransformDelete(&tr);
    }
  HTransformDelete(&t);
  
  for(i=0;i<n;i++)
    free(meridian[i]);
  free(meridian);

  /* Cancel the color per vertex information */
  p->cv=NULL;
  
  /* face information */
  p->nf=m*(n-2)+m;
  p->ne=0; /* not used */ 
  
  NEW(p->nvf,p->nf,unsigned int);
  NEW(p->fv,p->nf,unsigned int*);
  k=0;
  for(j=0;j<m;j++) /* for each meridian */
    {
      r1=j*n;         //first point in this meridian
      r2=((j+1)%m)*n; //first point in next meridian

      for(i=0;i<n-1;i++) /* for each point in the meridian */
	{
	  in=i+1; // Next point in meridian. Never goes to 0 (i<n-1)

	  // Define a face
	  if (i==0)
	    {
	      p->nvf[k]=3;
	      NEW(p->fv[k],3,unsigned int);
	      p->fv[k][0]=r1+i; // == r2+i
	      p->fv[k][1]=r2+in;
	      p->fv[k][2]=r1+in;
	    }
	  else
	    {
	      if (i==(n-2))
		{
		  p->nvf[k]=3;
		  NEW(p->fv[k],3,unsigned int);
		  p->fv[k][0]=r1+i;
		  p->fv[k][1]=r2+i;
		  p->fv[k][2]=r1+in; // == r2+in
		}
	      else
		{
		  p->nvf[k]=4;
		  NEW(p->fv[k],4,unsigned int);
		  p->fv[k][0]=r1+i;
		  p->fv[k][1]=r2+i;
		  p->fv[k][2]=r2+in;
		  p->fv[k][3]=r1+in;
		}
	    }
	  k++;
	}
    }

  /* Compute the bounding box using the points that approximate the sphere */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }
}

void ReadSphere(FILE *f,unsigned int g,Tpolyhedron *p)
{
  p->type=SPHERE;

  fscanf(f,"%lf",&(p->rad));

  fscanf(f,"%lf",&(p->center[0]));
  fscanf(f,"%lf",&(p->center[1]));
  fscanf(f,"%lf",&(p->center[2]));

  /* keep granularity */
  p->gr=g;
  
  /*Cancel cylinder information*/
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /*Generate the OFF information*/
  GenerateSphereOFF(g,p);
}

void InitPolyhedronFromFile(Tfilename *fname,Tcolor *c,
			     unsigned int gr,unsigned int bs,Tpolyhedron *p)
{
  char *ext; 

  p->status=bs; /* normal, hidden, decoration*/

  if (bs==HIDDEN_SHAPE)
    NewColor(1.0,1.0,1.0,c); /* for hidden shapes we use a default color */
  else
    CopyColor(&(p->color),c);
  
  p->obj3d=NO_UINT;
 
  ext=GetFileExtension(fname);
  if ((ext==NULL)||(strcasecmp(ext,"OFF")==0))
    {
      /* Note that the CuikSuite uses and extended OFF 
         files which can also include the definition of
         cylinders, spheres, lines, or sets of segments. 
      */
      FILE *f;
      char *stmp; 
      boolean off,coff,cylinder,sphere,line,segments;

      NEW(stmp,20,char); /* 20 is enough to read OFF/SPHERE/CYLINDER */

      f=fopen(GetFileFullName(fname),"r");
      if (!f)
	Error("Could not open Polyhedron file");

      fscanf(f,"%s",stmp); /* OFF -> skip it */

      off=(strcasecmp(stmp,"OFF")==0);
      coff=(strcasecmp(stmp,"COFF")==0);
      cylinder=(strcasecmp(stmp,"CYLINDER")==0);
      sphere=(strcasecmp(stmp,"SPHERE")==0);
      line=(strcasecmp(stmp,"LINE")==0);
      segments=(strcasecmp(stmp,"SEGMENTS")==0);

      if ((!off)&&(!coff)&&(!cylinder)&&(!sphere)&&(!line)&&(!segments))
	Error("Unknow type of shape");

      if (off)
	ReadOFF(f,FALSE,p);
  
      if (coff)
	ReadOFF(f,TRUE,p);
      
      if (cylinder)
	ReadCylinder(f,gr,p);

      if (line)
	ReadLine(f,p);

      if (segments)
	ReadSegments(f,p);

      if (sphere)
	ReadSphere(f,gr,p);

      free(stmp);
      fclose(f);
    }
  else
    {
      #if (_ASSIMP)
        if (!ReadGeneralMesh(GetFileFullName(fname),p))
	  Error("Error reading geometry from file in InitPolyhedronFromFile");
      #else
        if (strcasecmp(ext,"STL")==0)
	  ReadSTL(GetFileFullName(fname),p);
        else
	  Error("Unknown file type in InitPolyhedronFromFile. Try compiling with the Assimp library");
      #endif
    }
}

void InitPolyhedronFromTriangles(unsigned int nv,double **v,
				  unsigned int nt,unsigned int **t,
				  Tcolor *c,unsigned int bs,Tpolyhedron *p)
{
  unsigned int i,j;
  double av;

  p->type=OFF;

  p->status=bs; /* normal, hidden, decoration*/
  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;

  p->nv=nv;
  p->nf=nt;
  p->ne=3*nt; /* not used */

  NEW(p->v,p->nv,double*);
  for(i=0;i<p->nv;i++)
    {
      NEW(p->v[i],3,double);
      for(j=0;j<3;j++)
	p->v[i][j]=v[i][j];
    }
  
  /* Cancel the color per vertex information */
  p->cv=NULL; 
  
  NEW(p->nvf,p->nf,unsigned int);
  NEW(p->fv,p->nf,unsigned int*);
  for(i=0;i<p->nf;i++)
    { 
      p->nvf[i]=3; /* three vertices per face */
      NEW(p->fv[i],p->nvf[i],unsigned int);
      for(j=0;j<3;j++)
	p->fv[i][j]=t[i][j];
    }
  
  /* Cancel the sphere information */
  p->rad=0;
  p->gr=0;
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /* and the cylinder information too */
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /* Compute the bounding box */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }
}
boolean EmptyPolyhedron(Tpolyhedron *p)
{
  return(p->type==EMPTY_BODY);
}

void SimplifyPolyhedron(Tpolyhedron *p)
{
  if ((p->type==OFF)||(p->type==COFF))
    {
      
      unsigned int i,j,nnv;
      boolean *repeated;
      unsigned int *newPos;

      NEW(repeated,p->nv,boolean);
      NEW(newPos,p->nv,unsigned int);

      repeated[0]=FALSE;
      newPos[0]=0;
      nnv=1; /* new number of vertices */
      for(i=1;i<p->nv;i++)
	{
	  repeated[i]=FALSE;
	  for(j=0;((j<i)&&(!repeated[i]));j++)
	    if ((!repeated[j])&&(Distance(3,p->v[i],p->v[j])<1e-3)&&
		((p->cv==NULL)||(SameColor(&(p->cv[i]),&(p->cv[j])))))
	      {
		repeated[i]=TRUE;
		free(p->v[i]);
		newPos[i]=newPos[j];
	      }
	  if (!repeated[i])
	    {
	      newPos[i]=nnv;
	      nnv++;
	    }
	}
      for(i=0;i<p->nf;i++)
	{
	  for(j=0;j<p->nvf[i];j++)
	    p->fv[i][j]=newPos[p->fv[i][j]];
	}

      for(i=0;i<p->nv;i++)
	{
	  if (!repeated[i])
	    {
	      p->v[newPos[i]]=p->v[i];
	      if (p->cv!=NULL)
		CopyColor(&(p->cv[newPos[i]]),&(p->cv[i]));
	    }
	}
      
      p->nv=nnv;
      
      free(repeated);
      free(newPos);
    }
}


void NewTriangularPrism(double *p1,double *p2,double *p3,
			double h,
			Tcolor *c,unsigned int bs,Tpolyhedron *p)
{
  unsigned int i,j;
  double av;
  double n[3];
  double pt1[3],pt2[3],pt3[3];
  
  p->type=OFF;

  p->status=bs; /* normal, hidden, decoration*/
  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;
      
  p->nv=6;
  p->nf=5;
  p->ne=9; /* not used */

  NEW(p->v,p->nv,double*);
  for(i=0;i<p->nv;i++)
    NEW(p->v[i],3,double);

  DifferenceVector(3,p2,p1,pt1);
  DifferenceVector(3,p3,p1,pt2);
  CrossProduct(pt1,pt2,n);
  Normalize(3,n);
  SumVectorScale(3,p1,h,n,pt1);
  SumVectorScale(3,p2,h,n,pt2);
  SumVectorScale(3,p3,h,n,pt3);
  
  for(i=0;i<3;i++)
    {
      p->v[0][i]=p1[i];
      p->v[1][i]=p2[i];
      p->v[2][i]=p3[i];
      p->v[3][i]=pt1[i];
      p->v[4][i]=pt2[i];
      p->v[5][i]=pt3[i];
    }

  /* Cancel the color per vertex information */
  p->cv=NULL;
  
  NEW(p->nvf,p->nf,unsigned int);
  NEW(p->fv,p->nf,unsigned int*);

  p->nvf[0]=3;
  NEW(p->fv[0],p->nvf[0],unsigned int);
  p->fv[0][0]=0; p->fv[0][1]=1; p->fv[0][2]=2;
  
  p->nvf[1]=3;
  NEW(p->fv[1],p->nvf[1],unsigned int);
  p->fv[1][0]=5; p->fv[1][1]=4; p->fv[1][2]=3;
  
  p->nvf[2]=4;
  NEW(p->fv[2],p->nvf[2],unsigned int);
  p->fv[2][0]=3; p->fv[2][1]=4; p->fv[2][2]=1; p->fv[2][3]=0;
  
  p->nvf[3]=4;
  NEW(p->fv[3],p->nvf[3],unsigned int);
  p->fv[3][0]=4; p->fv[3][1]=5; p->fv[3][2]=2; p->fv[3][3]=1;
  
  p->nvf[4]=4;
  NEW(p->fv[4],p->nvf[4],unsigned int);
  p->fv[4][0]=5; p->fv[4][1]=3; p->fv[4][2]=0; p->fv[4][3]=2;
  
  /* Cancel the sphere information */
  p->rad=0;
  p->gr=0;
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /* and the cylinder information too */
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /* Compute the bounding box */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }
}

void NewBox(double xl,double yl,double zl,
	    double xu,double yu,double zu,
	    Tcolor *c,unsigned int bs,Tpolyhedron *p)
{
  unsigned int i,j;
  double av;

  if ((xu<xl)||(yu<yl)||(zu<zl))
    Error("Incorrect ranges in the box definition");

  if ((xu==xl)&&(yu==yl)&&(zu==zl))
    p->type=EMPTY_BODY;
  else
    {
      p->type=OFF;

      p->status=bs; /* normal, hidden, decoration*/
      CopyColor(&(p->color),c);
      p->obj3d=NO_UINT;

      p->nv=8;
      p->nf=6;
      p->ne=12; /* not used */

      NEW(p->v,p->nv,double*);
      for(i=0;i<p->nv;i++)
	NEW(p->v[i],3,double);

      p->v[0][0]=xl; p->v[0][1]=yl; p->v[0][2]=zl;
      p->v[1][0]=xl; p->v[1][1]=yu; p->v[1][2]=zl;
      p->v[2][0]=xu; p->v[2][1]=yu; p->v[2][2]=zl;
      p->v[3][0]=xu; p->v[3][1]=yl; p->v[3][2]=zl;
      p->v[4][0]=xl; p->v[4][1]=yl; p->v[4][2]=zu;
      p->v[5][0]=xl; p->v[5][1]=yu; p->v[5][2]=zu;
      p->v[6][0]=xu; p->v[6][1]=yu; p->v[6][2]=zu;
      p->v[7][0]=xu; p->v[7][1]=yl; p->v[7][2]=zu;

      /* Cancel the color per vertex information */
      p->cv=NULL;
  
      NEW(p->nvf,p->nf,unsigned int);
      NEW(p->fv,p->nf,unsigned int*);
      for(i=0;i<p->nf;i++)
	{ 
	  p->nvf[i]=4; /* four vertices per face */
	  NEW(p->fv[i],p->nvf[i],unsigned int);
	}
  
      p->fv[0][0]=0; p->fv[0][1]=1; p->fv[0][2]=2; p->fv[0][3]=3;
      p->fv[1][0]=6; p->fv[1][1]=5; p->fv[1][2]=4; p->fv[1][3]=7;
      p->fv[2][0]=3; p->fv[2][1]=2; p->fv[2][2]=6; p->fv[2][3]=7;
      p->fv[3][0]=2; p->fv[3][1]=1; p->fv[3][2]=5; p->fv[3][3]=6;
      p->fv[4][0]=4; p->fv[4][1]=5; p->fv[4][2]=1; p->fv[4][3]=0;
      p->fv[5][0]=0; p->fv[5][1]=3; p->fv[5][2]=7; p->fv[5][3]=4;

      /* Cancel the sphere information */
      p->rad=0;
      p->gr=0;
      p->center[0]=p->center[1]=p->center[2]=0.0;

      /* and the cylinder information too */
      p->p1[0]=p->p1[1]=p->p1[2]=0.0;
      p->p2[0]=p->p2[1]=p->p2[2]=0.0;

      /* Compute the bounding box */
      p->maxCoord=0;
      for(i=0;i<p->nv;i++)
	{
	  for(j=0;j<3;j++)
	    {
	      av=fabs(p->v[i][j]);
	      if (av>p->maxCoord)
		p->maxCoord=av;
	    }
	}
    }
}

void NewSphere(double r,double *center,Tcolor *c,
	       unsigned int gr,unsigned int bs,Tpolyhedron *p)
{
  p->type=SPHERE;
  p->status=bs; /* normal, hidden, decoration*/

  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;

  /*Set the sphere information*/
  p->rad=r;

  /* keep granularity */
  p->gr=gr;

  p->center[0]=center[0];
  p->center[1]=center[1];
  p->center[2]=center[2];

  /*Cancel cylinder information*/
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /*Generate the OFF information*/
  GenerateSphereOFF(gr,p);
}

void NewCylinder(double r,double *p1,double *p2,Tcolor *c,
		 unsigned int gr,unsigned int bs,Tpolyhedron *p)
{
  p->type=CYLINDER;
  p->status=bs; /* normal, hidden, decoration*/

  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;

  /*Set the cylinder information*/
  p->rad=r;

  /* keep granularity */
  p->gr=gr;
  
  p->p1[0]=p1[0];
  p->p1[1]=p1[1];
  p->p1[2]=p1[2];

  p->p2[0]=p2[0];
  p->p2[1]=p2[1];
  p->p2[2]=p2[2];

  /*Cancel sphere information*/
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /*Generate the OFF information*/
  GenerateCylinderOFF(gr,p);
}

void NewLine(double *p1,double *p2,Tcolor *c,
	     unsigned int bs,Tpolyhedron *p)
{
  p->type=LINE;
  p->status=bs; /* normal, hidden, decoration*/

  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;

  /*Set the line information*/
  p->rad=0.01; /* small radius for collision detection */

  p->p1[0]=p1[0];
  p->p1[1]=p1[1];
  p->p1[2]=p1[2];

  p->p2[0]=p2[0];
  p->p2[1]=p2[1];
  p->p2[2]=p2[2];

  /*Cancel sphere information*/
  p->gr=0;
  p->center[0]=p->center[1]=p->center[2]=0.0;

  /*Generate the OFF information*/
  GenerateCylinderOFF(0,p);
}

void NewSegments(unsigned int n,double *x,double *y,double *z,Tcolor *c,
		 Tpolyhedron *p)
{
  unsigned int i,j;
  double av;

  p->type=SEGMENTS;
  p->status=DECOR_SHAPE; /* never included in collision detection */

  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;

  /*Set the segments information*/
  p->nv=n;
  NEW(p->v,n,double*);
  for(i=0;i<n;i++)
    {
      NEW(p->v[i],3,double);
      p->v[i][0]=x[i];
      p->v[i][1]=y[i];
      p->v[i][2]=z[i];
    }

  /* Cancel the color per vertex information */
  p->cv=NULL;
  
  /* Compute the bounding box */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }

  /*Cancel sphere/cylinder information*/
  p->center[0]=p->center[1]=p->center[2]=0.0;
  p->rad=0;
  p->gr=0;
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /*Cancel the OFF information*/
  p->nf=0;
  p->ne=0;
  p->nvf=0;
}

void NewSpring(double length,double start,double rad,unsigned int lps,
	       Tcolor *c,Tpolyhedron *p)
{
  double end,step;
  unsigned int loops,pointsXLoop;
  unsigned int i,j,n;
  double x,a,av;

  /*  */
  p->type=SEGMENTS;
  p->status=DECOR_SHAPE; /* never included in collision detection */

  CopyColor(&(p->color),c);
  p->obj3d=NO_UINT;

  /* some hard-coded parameters of the spring */
  end=1.0-start; /* size of the last segment */
  loops=(unsigned int)((lps==0?80:lps)*length); /* number of loops in the central part */
  pointsXLoop=20; /* points to represent each loop */
  
  n=loops*pointsXLoop;
  step=(end-start)/(double)n;

  /* To reuse the SEGMENTS structure we define each
     segment with initialPoint-finalPoint*/
  p->nv=(3+n)*2;
  NEW(p->v,p->nv,double*);

  /* initial point */
  NEW(p->v[0],3,double);
  p->v[0][0]=0;
  p->v[0][1]=0;
  p->v[0][2]=0;

  /* firt point of the loops point */
  NEW(p->v[1],3,double);
  p->v[1][0]=start*length;
  p->v[1][1]=0;
  p->v[1][2]=0;

  x=start;
  for(i=0,j=2;i<n;i++,x+=step)
    {
      /* copy the previous point */
      NEW(p->v[j],3,double);
      p->v[j][0]=p->v[j-1][0];
      p->v[j][1]=p->v[j-1][1];
      p->v[j][2]=p->v[j-1][2];
      j++;

      /* define a new point */
      NEW(p->v[j],3,double);
      a=M_2PI*loops*(x-start)/(end-start);
      p->v[j][0]=x*length;
      p->v[j][1]=rad*sin(a);
      p->v[j][2]=rad*cos(a);
      j++;
    }
  
  /* copy the previous point */
  NEW(p->v[j],3,double);
  p->v[j][0]=p->v[j-1][0];
  p->v[j][1]=p->v[j-1][1];
  p->v[j][2]=p->v[j-1][2];
  j++;
    
  /* last point of the loops */
  NEW(p->v[j],3,double);
  p->v[j][0]=end*length;
  p->v[j][1]=0;
  p->v[j][2]=0;
  j++;
  
 /* copy the previous point */
  NEW(p->v[j],3,double);
  p->v[j][0]=p->v[j-1][0];
  p->v[j][1]=p->v[j-1][1];
  p->v[j][2]=p->v[j-1][2];
  j++;
    
  /* last point */
  NEW(p->v[j],3,double);
  p->v[j][0]=length;
  p->v[j][1]=0;
  p->v[j][2]=0;
  j++;

  if (j!=p->nv)
    Error("Wrong number or points in spring");
  
  /* Compute the bounding box */
  p->maxCoord=0;
  for(i=0;i<p->nv;i++)
    {
      for(j=0;j<3;j++)
	{
	  av=fabs(p->v[i][j]);
	  if (av>p->maxCoord)
	    p->maxCoord=av;
	}
    }

  /*Cancel sphere/cylinder information*/
  p->center[0]=p->center[1]=p->center[2]=0.0;
  p->rad=0;
  p->p1[0]=p->p1[1]=p->p1[2]=0.0;
  p->p2[0]=p->p2[1]=p->p2[2]=0.0;

  /*Cancel the OFF information*/
  p->nf=0;
  p->ne=0;
  p->nvf=0;
  
  /* Cancel the color per vertex information */
  p->cv=NULL; 
}

void CopyPolyhedron(Tpolyhedron *p_dst,Tpolyhedron *p_src)
{
  unsigned int i,j;

  p_dst->type=p_src->type;
  p_dst->status=p_src->status;

  /*plot3d information*/
  CopyColor(&(p_dst->color),&(p_src->color));
 
  p_dst->obj3d=p_src->obj3d;

  /* off information */
  p_dst->nv=p_src->nv;
  p_dst->nf=p_src->nf;
  p_dst->ne=p_src->ne;

  if (p_dst->nv>0)
    {
      NEW(p_dst->v,p_src->nv,double*);
      if (p_src->cv!=NULL)
	{ NEW(p_dst->cv,p_src->nv,Tcolor);}
      else
	p_dst->cv=NULL;
      for(i=0;i<p_dst->nv;i++)
	{
	  NEW(p_dst->v[i],3,double);
	  p_dst->v[i][0]=p_src->v[i][0];
	  p_dst->v[i][1]=p_src->v[i][1];
	  p_dst->v[i][2]=p_src->v[i][2];
	  if (p_src->cv!=NULL)
	    CopyColor(&(p_dst->cv[i]),&(p_src->cv[i]));
	}
    }
  else
    {
      p_dst->v=NULL;
      p_dst->cv=NULL;
    }

  if (p_dst->nf>0)
    {
      NEW(p_dst->nvf,p_dst->nf,unsigned int);
      NEW(p_dst->fv,p_dst->nf,unsigned int*);
      for(i=0;i<p_dst->nf;i++)
	{
	  p_dst->nvf[i]=p_src->nvf[i];
	  NEW(p_dst->fv[i],p_dst->nvf[i],unsigned int);
	  
	  for(j=0;j<p_dst->nvf[i];j++)
	    p_dst->fv[i][j]=p_src->fv[i][j];
	}
    }
  else
    {
      p_dst->nvf=NULL;
      p_dst->fv=NULL;
    }

  /*Sphere - Cylinder - Line information (if any)*/
  p_dst->rad=p_src->rad;
  p_dst->gr=p_src->gr;
  for(i=0;i<3;i++)
    {
      p_dst->center[i]=p_src->center[i];
      p_dst->p1[i]=p_src->p1[i];
      p_dst->p2[i]=p_src->p2[i];
    }

  p_dst->maxCoord=p_src->maxCoord;
}

void TransformPolyhedron(THTransform *t,Tpolyhedron *p)
{
  /* if the transform is the identity just do not apply it */
  if (!HTransformIsIdentity(t))
    {
      unsigned int i,j;
      double av;

      if (p->nv>0)
	{
	  /*Off information*/
	  p->maxCoord=0;
	  for(i=0;i<p->nv;i++)
	    {
	      HTransformApply(p->v[i],p->v[i],t);
	      for(j=0;j<3;j++)
		{
		  av=fabs(p->v[i][j]);
		  if (av>p->maxCoord)
		    p->maxCoord=av;
		}
	    }
	}

      /*Sphere - Cylinder - Line information*/
      /* recall that sphere,cylinder,line also have vertices */
      HTransformApply(p->center,p->center,t);
      HTransformApply(p->p1,p->p1,t);
      HTransformApply(p->p2,p->p2,t);
    }
}

void GetPolyhedronCenter(double *c,Tpolyhedron *p)
{
  if (p->type!=SPHERE)
    Error("GetPolyhedronCenter is only defined for spheres");

  c[0]=p->center[0];
  c[1]=p->center[1];
  c[2]=p->center[2];
}

unsigned int GetPolyhedronType(Tpolyhedron *p)
{
  return(p->type);
}

void SetPolyhedronColor(Tcolor *c,Tpolyhedron *p)
{
  CopyColor(&(p->color),c);
}

void GetPolyhedronColor(Tcolor *c,Tpolyhedron *p)
{
  CopyColor(c,&(p->color));
}

unsigned int GetPolyhedronStatus(Tpolyhedron *p)
{
  return(p->status);
}

void GetOFFInfo(unsigned int *nv,double ***v,unsigned int *nf,
		unsigned int **nvf,unsigned int ***fv,Tpolyhedron *p)
{
  *nv=p->nv;
  *v=p->v;
  *nf=p->nf;
  *nvf=p->nvf;
  *fv=p->fv;
}

unsigned int GetPolyhedronNVertex(Tpolyhedron *p)
{
  return(p->nv);
}

void GetPolyhedronDefiningPoint(unsigned int i,double *point,Tpolyhedron *p)
{
  unsigned int j;

  switch(p->type)
    {
    case CYLINDER:
    case LINE:
      if (i>1)
	Error("Point counter out of range in GetPolyhedronDefiningPoint");
      
      if (i==0)
	{
	  for(j=0;j<3;j++)
	    point[j]=p->p1[j];
	}
      else
	{
	  for(j=0;j<3;j++)
	    point[j]=p->p2[j];
	}
      break;

    case SPHERE:
      if (i>0)
	Error("Point counter out of range in GetPolyhedronDefiningPoint");
      
      for(j=0;j<3;j++)
	point[j]=p->center[j];
      break;

    case OFF:
    case COFF:
    case SEGMENTS:
      GetPolyhedronVertex(i,point,p);
      break;

    default:
      Error("Undefined Polyhedron type in GetPolyhedronDefiningPoint");
      break;
    }
}

double GetPolyhedronGranularity(Tpolyhedron *p)
{
  return(p->gr);
}

double GetPolyhedronRadius(Tpolyhedron *p)
{
  if ((p->type==OFF)||(p->type==LINE)||(p->type==SEGMENTS))
    Error("Radius is not defined for OFFs,LINEs, or SEGMENTS");
  return(p->rad);
}

void GetPolyhedronVertex(unsigned int i,double *point,Tpolyhedron *p)
{
  unsigned int j;

  if (i>=p->nv)
    Error("Vertex counter out of range");

  for(j=0;j<3;j++)
    point[j]=p->v[i][j];
}

double GetPolyhedronMaxCoordinate(Tpolyhedron *p)
{
  return(p->maxCoord);
}

void PlotPolyhedron(Tplot3d *pt,Tpolyhedron *p)
{
  if (p->status!=HIDDEN_SHAPE)
    {
      p->obj3d=StartNew3dObject(&(p->color),pt);

      switch(p->type)
	{
	case OFF:
	  Plot3dObject(p->nv,p->nf,p->ne,p->v,p->nvf,p->fv,pt);					
	  break;
	case COFF:
	  Plot3dObjectWithColors(p->nv,p->nf,p->ne,p->v,p->cv,p->nvf,p->fv,pt);
	  break;
	case LINE:
	  PlotLine(p->p1,p->p2,pt);
	  break;
	case CYLINDER:
	  //PlotCylinder(p->rad,p->p1,p->p2,pt);
	  Plot3dObject(p->nv,p->nf,p->ne,p->v,p->nvf,p->fv,pt);	
	  break;
	case SPHERE:
	  //fprintf(stderr,"sphere dice %u ------------------- \n",p->gr);
	  if (p->gr==DEFAULT_DICE)
	    PlotSphere(p->rad,p->center[0],p->center[1],p->center[2],pt);
	  else
	    Plot3dObject(p->nv,p->nf,p->ne,p->v,p->nvf,p->fv,pt);
	  break;
	case SEGMENTS:
	  PlotSegments(p->nv,p->v,pt);
	  break;
	}
      if (p->type==COFF)
	Close3dObjectNoColor(pt);
      else
	Close3dObject(pt);
    }
}

void PolyhedronPrintCenter(FILE *f,THTransform *t,Tpolyhedron *p)
{
  if (p->type==SPHERE)
    {
      double v[3];
	    
      HTransformApply(p->center,v,t);
	    
      fprintf(f,"%.16f %.16f %.16f\n",v[0],v[1],v[2]);
    }
}

void PolyhedronPrintCenterAndRadius(FILE *f,THTransform *t,Tpolyhedron *p)
{
  if (p->type==SPHERE)
    {
      double v[3];
	    
      HTransformApply(p->center,v,t);
	    
      fprintf(f,"%.16f %.16f %.16f %.16f\n",v[0],v[1],v[2],p->rad);
    }
}

void MovePolyhedron(Tplot3d *pt,THTransform *t,Tpolyhedron *p)
{
  if ((p->obj3d!=NO_UINT)&&(p->status!=HIDDEN_SHAPE))
    Move3dObject(p->obj3d,t,pt);
}

void SavePolyhedron(char *fileName,Tpolyhedron *p)
{
  FILE *f;
  unsigned int i,j;
  
  f=fopen(fileName,"w");
  if (!f)
    Error("Could not open output file for a convex polyhedron");

  switch(p->type)
    {
    case OFF:
      fprintf(f,"OFF\n");
      fprintf(f,"%u %u 1\n",p->nv,p->nf);
      for(i=0;i<p->nv;i++)
	fprintf(f,"%f %f %f\n",p->v[i][0],p->v[i][1],p->v[i][2]);
      fprintf(f,"\n");
      for(i=0;i<p->nf;i++)
	{
	  fprintf(f,"%u ",p->nvf[i]);
	  for(j=0;j<p->nvf[i];j++)
	    fprintf(f," %u",p->fv[i][j]);
	  fprintf(f,"\n");
	}
      break;
    case COFF:
      fprintf(f,"COFF\n");
      fprintf(f,"%u %u 1\n",p->nv,p->nf);
      for(i=0;i<p->nv;i++)
	fprintf(f,"%f %f %f %f %f %f 1\n",p->v[i][0],p->v[i][1],p->v[i][2],
		GetRed(&(p->cv[i])),GetGreen(&(p->cv[i])),GetBlue(&(p->cv[i])));
      fprintf(f,"\n");
      for(i=0;i<p->nf;i++)
	{
	  fprintf(f,"%u ",p->nvf[i]);
	  for(j=0;j<p->nvf[i];j++)
	    fprintf(f," %u",p->fv[i][j]);
	  fprintf(f,"\n");
	}
      break;
    case LINE:
      fprintf(f,"LINE\n");
      fprintf(f,"%.16f %.16f %.16f\n",p->p1[0],p->p1[1],p->p1[2]);
      fprintf(f,"%.16f %.16f %.16f\n",p->p2[0],p->p2[1],p->p2[2]);
      break;
    case CYLINDER:
      fprintf(f,"CYLINDER\n");
      fprintf(f,"%.16f\n",p->rad);
      fprintf(f,"%.16f %.16f %.16f\n",p->p1[0],p->p1[1],p->p1[2]);
      fprintf(f,"%.16f %.16f %.16f\n",p->p2[0],p->p2[1],p->p2[2]);
      break;
    case SPHERE:
      fprintf(f,"SPHERE\n");
      fprintf(f,"%.16f\n",p->rad);
      fprintf(f,"%.16f %.16f %.16f\n",p->center[0],p->center[1],p->center[2]);
      break;
    case SEGMENTS:
      fprintf(f,"SEGMENTS\n");
      fprintf(f,"%u\n",p->nv);
      for(i=0;i<p->nv;i++)
	fprintf(f,"%f %f %f\n",p->v[i][0],p->v[i][1],p->v[i][2]);
      break;
    }
  fclose(f);
}

void PrintPolyhedron(FILE *f,char *path,unsigned int l,char *label,unsigned int n,Tpolyhedron *p)
{
  unsigned int i;
  char *s;

  
  NEW(s,l+6,char);
  for(i=0;i<l+5;i++)
    s[i]=' ';
  s[i]=0;
  
  if (n>0)
    fprintf(f,"%s",s);

  free(s);
  
  switch(p->type)
    {
    case OFF:
    case COFF:
      {
	unsigned int l;
	char *pname;
	Tfilename fbody;
	
	/* ensure that folder "bodies" exists */
	CreateFileName(path,"bodies",NULL,NULL,&fbody);
	mkdir(GetFileFullName(&fbody),0777);
	DeleteFileName(&fbody);

	/* store the object in file */
	if (label!=NULL)
	  {
	    l=strlen(label);
	    NEW(pname,l+30,char);
	    sprintf(pname,"bodies/%s_%u",label,n);
	  }
	else
	  {
	    NEW(pname,30,char);
	    sprintf(pname,"bodies/_body_%u",n);
	  }
	
	CreateFileName(path,pname,NULL,OFF_EXT,&fbody);

	SavePolyhedron(GetFileFullName(&fbody),p);
	fprintf(f,"body \"%s\"",GetFileFullName(&fbody));

	DeleteFileName(&fbody);
	free(pname);
      }
      break;
    case LINE:
      fprintf(f,"line (");
      Print3Reals(f,p->p1[0],p->p1[1],p->p1[2]);
      fprintf(f,") (");
      Print3Reals(f,p->p2[0],p->p2[1],p->p2[2]);
      fprintf(f,")");
      break;
    case CYLINDER:
      fprintf(f,"cylinder %g (",p->rad);
      Print3Reals(f,p->p1[0],p->p1[1],p->p1[2]);
      fprintf(f,") (");
      Print3Reals(f,p->p2[0],p->p2[1],p->p2[2]);
      fprintf(f,")");
      break;
    case SPHERE:
      fprintf(f,"sphere %g (",p->rad);
      Print3Reals(f,p->center[0],p->center[1],p->center[2]);
      fprintf(f,")");
      break;
    case SEGMENTS:
      {
	/* Print the segments in blocks to avoid memory overflow in the parser*/
	unsigned int s,e;
	boolean end;

	end=FALSE;
	s=0;
	while(!end) 
	  {
	    e=s+1000; /* Adjust this if you have memory overflow in the parser */
	    if (e>=p->nv)
	      {
		e=p->nv;
		end=TRUE;
	      }
	    fprintf(f,"segments (");
	    for(i=s;i<e;i++)
	      {
		Print3Reals(f,p->v[i][0],p->v[i][1],p->v[i][2]); 
		if (i<e-1) 
		  {
		    fprintf(f,";");
		    if (((i-s)%2)==1) fprintf(f,"\n                      ");
		  }
	      }
	    fprintf(f,") color (%g,%g,%g)\n            ",
		    GetRed(&(p->color)),GetGreen(&(p->color)),GetBlue(&(p->color)));
	    s=e;
	  }
      }
      break;
    }

  if (p->type!=SEGMENTS)
    {
      if (p->status!=HIDDEN_SHAPE)
	fprintf(f," color (%g,%g,%g)",
		GetRed(&(p->color)),GetGreen(&(p->color)),GetBlue(&(p->color)));
	
      switch(p->status)
	{
	case NORMAL_SHAPE:
	  break;
	case HIDDEN_SHAPE:
	  fprintf(f," hidden");
	  break;
	case DECOR_SHAPE:
	  fprintf(f," decoration");
	  break;
	default:
	  Error("Unknown body display status in PrintPolyhedron");
	}
    }
  fprintf(f,"\n");
}

void DeletePolyhedron(Tpolyhedron *p)
{
  if (p->type!=EMPTY_BODY)
    {
      unsigned int i;

      if (p->nv>0)
	{
	  for(i=0;i<p->nv;i++)
	    free(p->v[i]);
	  free(p->v);
	  if (p->cv!=NULL)
	    free(p->cv);
	}

      if (p->nf>0)
	{
	  for(i=0;i<p->nf;i++)
	    free(p->fv[i]);
      
	  free(p->fv);
	  free(p->nvf);
	}
    }
}


