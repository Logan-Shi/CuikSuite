#include "cpolytope.h"

#include "defines.h"
#include "random.h"
#include "algebra.h"
#include "chart.h"

#include "math.h"
#include "string.h"

/** 
   \file cpolytope.c
   \brief Implementation of a polytope associated to a chart.

   Implements the functions for the polytope defined in a chart
   (i.e., in the tangent space to a variety defined on a given point).

   \sa Tcpolytope,cpolytope.h
*/

/** 
   \brief Identifies vertices connected by an edge.

   Determines if a couple of vertices are connected by a vertex and returns
   the set of faces defining the edge.

   This is for internal use only and no check is done if the vertices are 
   actually used (properly defined) in the chart. This check must be done
   before calling this function.

   \param i Index of the first vertex.
   \param j Index of the second vertex.
   \param l Number of faces in common between the two vertices. This must be k-1
            for an edge to exist between \e i and \e j.
   \param faces Index of the common faces between the vertices. The space for this
                must be allocated externally.
   \param mp The chart to query.

   \return \ref TRUE if the edge exists.
*/
boolean HaveEdge(unsigned int i,unsigned int j,unsigned int *l,unsigned int *faces,Tcpolytope *mp);

/** 
   \brief Auxiliary function to get a boundary point for a given external vertex.

   This is an auxiliary function for \ref PolytopeBoundaryPointFromExternalCorner
   and for \ref PolytopeBoundaryPointsFromExternalCorners. In the first case
   the external corner is selected at random or just the first external corner is
   used (depending on parameter \e rand). In the second case all external corners
   are used (in sequence).
   
   \param nc The index of the external corner (from 0 to nExternal-1).
   \param rSample Radious to use in the sampling. This is typically the radius
                  of the ball initially inside the polytope but it can be smaller
 		  if many attempts to sample points fail.
   \param nv The identifier of the selected vertex.
   \param t The output point on the chart ball boundary (if any)
   \param mp The polytope to sample.

   \return TRUE if the sampled point is actually on the boundary of the chart.
*/
boolean PolytopeBoundaryPointFromExternalCornerInt(unsigned int nc,double rSample,
						   unsigned int *nv,double *t,Tcpolytope *mp);

void InitEmptyPolytope(unsigned int k,double r,Tcpolytope *mp)
{
  mp->r=r;
  mp->k=k;

  mp->emptyPolytope=TRUE;

  mp->v=PolytopeMaxVolume(mp);

  mp->open=TRUE;
}

void DefinePolytope(Tcpolytope *mp)
{
  if (mp->emptyPolytope)
    {
      unsigned int *c;
      unsigned int i,j,nv;
      double r;
      Tinterval ri;

      /*The polytope is slighly larger than the ball*/
      
      r=POLYTOPE_R_ENLARGEMENT*mp->r;

      /*make enough room for the vertices to define below and for many more*/
      /*To save space non-used vertices are  no initialized at all*/
      mp->maxVertices=(1<<(mp->k+1)); /* 2^(k+1)*/
      NEW(mp->vertex,mp->maxVertices,double *);
      NEW(mp->maxIndices,mp->maxVertices,unsigned int);
      NEW(mp->nIndices,mp->maxVertices,unsigned int);
      NEW(mp->indices,mp->maxVertices,unsigned int *);
      NEW(mp->expandible,mp->maxVertices,boolean);

      for(i=0;i<mp->maxVertices;i++)
	{
	  mp->vertex[i]=NULL;
	  /* mp->maxIndices[i]==0 indicates a un-used vertex */
	  mp->maxIndices[i]=0;
	  /*nIndices is used to link free vertices.*/
	  mp->nIndices[i]=i+1;
      
	  mp->indices[i]=NULL;

	  mp->expandible[i]=FALSE; /*not used*/
	}
      mp->nExpandible=0;
      mp->nVertices=0;
      mp->nIndices[mp->maxVertices-1]=NO_UINT;
      mp->freeVertex=0;

      /* Now define the faces */
      mp->nFaces=2*mp->k;
      mp->maxFaces=2*mp->nFaces; 
      NEW(mp->face,mp->maxFaces,double *);
      NEW(mp->ID,mp->maxFaces,unsigned int);
     
      for(i=0;i<mp->k;i++)
	{
	  NEW(mp->face[2*i],mp->k+1,double);
	  NEW(mp->face[2*i+1],mp->k+1,double);
	  for(j=0;j<mp->k+1;j++)
	    {
	      mp->face[2*i][j]=0;
	      mp->face[2*i+1][j]=0;
	    }
	  /* Faces are defined such that the center of the ball is
	     negative in the linear constraint. This corresponds to the
	     circle convention x^2+y^2-r^2=0 is negative for (0,0)*/
	  /* -x_i-r=0 (== x_i=-r) */
	  mp->face[2*i][i]=-1;
	  mp->face[2*i][mp->k]=-r;
	  /* x_i-r=0 (== x_i=+r) */
	  mp->face[2*i+1][i]=1;
	  mp->face[2*i+1][mp->k]=-r;

	  mp->ID[2*i]=NO_UINT;
	  mp->ID[2*i+1]=NO_UINT;
	}
  
      /* Now define the vertices and the indices*/
      NEW(c,mp->k,unsigned int);
      FirstCombination(mp->k,1,c);
      do{
	/*Take a free vertex. We know we have enough free
	  vertices -> no test for new space is done. */
	nv=mp->freeVertex;
	mp->freeVertex=mp->nIndices[mp->freeVertex];

	/*Allocate space for the vertex*/
	NEW(mp->vertex[nv],mp->k,double);

	/*define the vertex*/
	for(i=0;i<mp->k;i++)
	  mp->vertex[nv][i]=(c[i]==0?-r:r);

	/*and all vertices are valid for expansion */
	mp->expandible[nv]=TRUE;
	mp->nExpandible++;
    
	mp->nVertices++;

	/*set the planes defining the vertices*/
	mp->maxIndices[nv]=mp->k;
	mp->nIndices[nv]=mp->k;
	NEW(mp->indices[nv],mp->k,unsigned int);
	for(i=0;i<mp->k;i++)
	  mp->indices[nv][i]=(c[i]==0?2*i:2*i+1);
      } while(NextCombination(mp->k,1,c));

      free(c);
      
      /*Bounding box for the polytope -> the polytope itself*/
      InitBox(mp->k,NULL,&(mp->bb));
      NewInterval(-r,r,&ri);
      for(i=0;i<mp->k;i++)
	SetBoxInterval(i,&ri,&(mp->bb));

      mp->emptyPolytope=FALSE;

      mp->open=TRUE;
      
      #if (CIRCULAR_POLYTOPE>0)
      if (mp->k==2)
	{
	  double a,b;
	  double *p1,*p2,*f,s;
      
	  NEW(p1,2,double);
	  NEW(p2,2,double);
	  NEW(f,3,double);

	  s=M_2PI/(double)CIRCULAR_POLYTOPE;

	  p1[0]=0.9*r;
	  p1[1]=0;
      
	  for(i=1;i<=CIRCULAR_POLYTOPE;i++)
	    {
	      if (i==CIRCULAR_POLYTOPE)
		{
		  p2[0]=0.9*r;
		  p2[1]=0;
		}
	      else
		{
		  p2[0]=0.9*r*cos(i*s);
		  p2[1]=0.9*r*sin(i*s);
		}

	      /* Define a line form p1 to p2 (with 0,0 being negative) */
	      a=p2[0]-p1[0];
	      b=p2[1]-p1[1];
	      f[0]=b;
	      f[1]=-a;
	      f[2]=-p1[0]*b+p1[1]*a;

	      //fprintf(stderr,"%+f x %+f y %+f<=0\n",f[0],f[1],f[2]);
	  
	      CutPolytopeWithFace(NULL,f,f[2],NO_UINT,NULL,NULL,0,NULL,NULL,mp);
	  
	      memcpy(p1,p2,2*sizeof(double));
	    }
      
	  free(p1);
	  free(p2);
	  free(f);

	  //exit(0);
	}
      #endif
    }
}

void SPolytope2Polytope(Tparameters *pr,Tscpolytope *sp,Tcpolytope *p)
{
  unsigned int k;
  double *f;
  unsigned int i,id,nf;
  //double l;

  //l=GetSPolytopeBoxSide(sp);
  k=GetSPolytopeDim(sp);
  //InitEmptyPolytope(k,l/2,p);

  InitEmptyPolytope(k,GetSPolytopeRadius(sp),p);
  DefinePolytope(p);
  
  NEW(f,k+1,double);
  
  nf=GetSPolytopeNFaces(sp);
  for(i=0;i<nf;i++)
    {
      GetSPolytopeFace(i,f,sp);
      id=SPolytopeNeighbourID(i,sp);
      CutPolytopeWithFace(pr,f,f[k],id,NULL,NULL,0,NULL,NULL,p);
    }
  free(f);
}

void Polytope2SPolytope(Tparameters *pr,Tcpolytope *p,Tscpolytope *sp)
{
  unsigned int i;
  double sr,delta;

  sr=GetParameter(CT_SR,pr);
  delta=GetParameter(CT_DELTA,pr);
  
  InitEmptySPolytope(delta,p->k,p->r,sr,sp);
  DefineSPolytope(sp);
  for(i=0;i<p->nFaces;i++)
    {
      if (p->face[i]!=NULL)
	CutSPolytopeWithFace(p->face[i],p->face[i][p->k],p->ID[i],sp);
    }
}

void CopyPolytope(Tcpolytope *mp_dst,Tcpolytope *mp_src)
{
  mp_dst->k=mp_src->k;
  mp_dst->r=mp_src->r;
  mp_dst->v=mp_src->v;

  mp_dst->open=mp_src->open;

  mp_dst->emptyPolytope=mp_src->emptyPolytope;
  if (!mp_src->emptyPolytope)
    {
      unsigned int i,j;

      mp_dst->nFaces=mp_src->nFaces;
      mp_dst->maxFaces=mp_src->maxFaces;
      NEW(mp_dst->face,mp_dst->maxFaces,double *);
      NEW(mp_dst->ID,mp_dst->maxFaces,unsigned int);
      for(i=0;i<mp_dst->nFaces;i++)
	{
	  if (mp_src->face[i]==NULL)
	    mp_dst->face[i]=NULL;
	  else
	    {
	      NEW(mp_dst->face[i],mp_dst->k+1,double);
	      for(j=0;j<mp_dst->k+1;j++)
		mp_dst->face[i][j]=mp_src->face[i][j];
	    }
	  mp_dst->ID[i]=mp_src->ID[i];
	}

      mp_dst->maxVertices=mp_src->maxVertices;
      NEW(mp_dst->vertex,mp_dst->maxVertices,double *);
      NEW(mp_dst->nIndices,mp_dst->maxVertices,unsigned int);
      NEW(mp_dst->maxIndices,mp_dst->maxVertices,unsigned int);
      NEW(mp_dst->indices,mp_dst->maxVertices,unsigned int *);
      NEW(mp_dst->expandible,mp_dst->maxVertices,boolean);
      
      for(i=0;i<mp_dst->maxVertices;i++)
	{
	  if (mp_src->maxIndices[i]==0)
	    {
	      mp_dst->maxIndices[i]=0;
	      /*reproduce the free list*/
	      mp_dst->nIndices[i]=mp_src->nIndices[i];
	      mp_dst->vertex[i]=NULL;
	      mp_dst->indices[i]=NULL;
	      mp_dst->expandible[i]=FALSE; /*not used*/
	    }
	  else
	    {
	      NEW(mp_dst->vertex[i],mp_src->k,double);
	      for(j=0;j<mp_src->k;j++)
		mp_dst->vertex[i][j]=mp_src->vertex[i][j];

	      mp_dst->maxIndices[i]=mp_src->maxIndices[i];
	      mp_dst->nIndices[i]=mp_src->nIndices[i];
	      NEW(mp_dst->indices[i],mp_dst->maxIndices[i],unsigned int);
	      for(j=0;j<mp_dst->maxIndices[i];j++)
		mp_dst->indices[i][j]=mp_src->indices[i][j];
	      mp_dst->expandible[i]=mp_src->expandible[i];
	    }
	}
      mp_dst->freeVertex=mp_src->freeVertex;

      mp_dst->nExpandible=mp_src->nExpandible;
     
      mp_dst->nVertices=mp_src->nVertices;

      CopyBox(&(mp_dst->bb),&(mp_src->bb));
    }
}

void PolytopeCenter(double *t,Tcpolytope *mp)
{
  unsigned int i;
  
  for(i=0;i<mp->k;i++)
    t[i]=0;

  if (!mp->emptyPolytope)
    {
      unsigned int j;
      double w;

      if (mp->nVertices==0)
	Error("Computing the center of a polytope with no vertices");
      
      w=1/(double)mp->nVertices;
      
      for(i=0;i<mp->maxVertices;i++)
	{
	  if (mp->maxIndices[i]>0)
	    {
	      for(j=0;j<mp->k;j++)
		t[j]+=(w*mp->vertex[i][j]);
	    }
	}
    }
}

boolean InsidePolytope(double *t,Tcpolytope *mp)
{
  unsigned int i;
  boolean inside;

  if (mp->emptyPolytope)
    {
      inside=TRUE;
      i=0;
      while((i<mp->k)&&(inside))
	{
	  inside=(fabs(t[i])<=mp->r);
	  i++;
	}
    }
  else
    {
      if (mp->nVertices==0)
	inside=FALSE;
      else
	{ 
	  inside=TRUE;
	  i=0;
	  while((i<mp->nFaces)&&(inside))
	    {
	      if (mp->face[i]!=NULL)
		inside=(GeneralDotProduct(mp->k,mp->face[i],t)+mp->face[i][mp->k]<=0);
	      i++;
	    }
	}
    }
  return(inside);
}


boolean HaveEdge(unsigned int i,unsigned int j,unsigned int *l,unsigned int *faces,Tcpolytope *mp)
{ 
  if (mp->emptyPolytope)
    return(FALSE);
  else
    {
      unsigned int li,lj;

      li=0;
      lj=0;
      (*l)=0;
      while((li<mp->nIndices[i])&&(lj<mp->nIndices[j]))
	{
	  if (mp->indices[i][li]<mp->indices[j][lj])
	    li++;
	  else
	    {
	      if (mp->indices[i][li]>mp->indices[j][lj])
		lj++;
	      else
		{
		  faces[*l]=mp->indices[i][li];
		  (*l)++;
		  li++;
		  lj++;
		}
	    }
	}
      return((*l)==mp->k-1);
    }
}

boolean CutPolytope(Tparameters *pr,double *t,double r,unsigned int id,void *wcs,void *c,
		    unsigned int m,unsigned int *tp,Tbox *ambient,Tcpolytope *mp)
{
  double n;
  boolean ok;

  if (mp->emptyPolytope)
    DefinePolytope(mp);

  /*The plane separating the two spheres has parameters 't'
    and the offset is computed here */
  n=Norm(mp->k,t);
  
  /* Note that typically mp->r==r and thus  -(mp->r*mp->r-r*r+n*n)/2.0 = -n*n/2.0*/
  ok=CutPolytopeWithFace(pr,t,-(mp->r*mp->r-r*r+n*n)/2.0,id,wcs,c,m,tp,ambient,mp);
  
  return(ok);
}

boolean CutPolytopeWithFace(Tparameters *pr,double *t,double offset,unsigned int id,
			    void *wcs,void *c,unsigned int m,unsigned int *tp,Tbox *ambient,
			    Tcpolytope *mp)
{
  if ((!mp->emptyPolytope)&&(mp->nVertices>0))
    {
      unsigned int i,j;
      double *pos,*pt;
      unsigned int *faces;
      unsigned int ni;
      unsigned int l,d,s,*mIndices,tv;
      double o;
      boolean *usedFace;
      unsigned int nPos,nNeg;
      boolean firstVertex;
      double eps=0; /* tolerance. Used for debug only */

      NEW(pt,m,double);

      /*Evaluate the vertexes w.r.t. the plane */
      nPos=0;
      nNeg=0;
      NEW(pos,mp->maxVertices,double);
      for(i=0;i<mp->maxVertices;i++)
	{
	  if (mp->maxIndices[i]>0)
	    {
	      pos[i]=GeneralDotProduct(mp->k,t,mp->vertex[i])+offset;
	      if (pos[i]<-eps)
		nNeg++;
	      else
		{
		  if (pos[i]>eps)
		    nPos++;
		  else
		    pos[i]=0.0;
		}
	    }
	}

      if ((nPos>0)&&(nNeg>0))
	{
	  tv=mp->maxVertices; /*this can change inside the loop*/
	  /*The occupied vertices can also change -> backup the flags */
	  NEW(mIndices,tv,unsigned int);
	  memcpy(mIndices,mp->maxIndices,sizeof(unsigned int)*tv);

	  /*Look for vertices at different position w.r.t. the plane 
	    joined by an edge */
	  for(i=0;i<tv;i++)
	    {
	      if (mIndices[i]>0) /* if vertex in use */
		{
		  ni=mp->nIndices[i]+1; /*max num common indices + 1 for current face */
		  NEW(faces,ni,unsigned int);
		  for(j=i+1;j<tv;j++)
		    {
		      /*if in-use and at the other side of the new face */
		      if ((mIndices[j]>0)&&(pos[i]*pos[j]<0))
			{
			  /*check if there is an edge between the two vertices*/
			  if (HaveEdge(i,j,&l,faces,mp))
			    {
			      /*We have an edgge! -> cut it and add one new vertex*/
			      if (mp->freeVertex==NO_UINT)
				{
				  /*Allocate new space for vertexes*/
				  d=mp->maxVertices;
				  MEM_DUP(mp->vertex,mp->maxVertices,double *);
				  MEM_EXPAND(mp->nIndices,mp->maxVertices,unsigned int);
				  MEM_EXPAND(mp->maxIndices,mp->maxVertices,unsigned int);
				  MEM_EXPAND(mp->indices,mp->maxVertices,unsigned int *);
				  MEM_EXPAND(mp->expandible,mp->maxVertices,boolean);
			  
				  for(s=d;s<mp->maxVertices;s++)
				    {
				      mp->vertex[s]=NULL;
				      mp->nIndices[s]=s+1;
				      mp->maxIndices[s]=0;
				      mp->indices[s]=NULL;
				      mp->expandible[s]=FALSE;
				    }
				  mp->nIndices[mp->maxVertices-1]=NO_UINT;
				  mp->freeVertex=d;
				}
			      s=mp->freeVertex;
			      mp->freeVertex=mp->nIndices[mp->freeVertex];
			  
			      /*at a new vertex at position 's' interpolating between vi and vj*/
			      NEW(mp->vertex[s],mp->k,double);
			      o=-pos[i]/(pos[j]-pos[i]);
			      for(d=0;d<mp->k;d++)
				mp->vertex[s][d]=mp->vertex[i][d]+(mp->vertex[j][d]-mp->vertex[i][d])*o;

			      mp->maxIndices[s]=l+3;
			      NEW(mp->indices[s],mp->maxIndices[s],unsigned int);
			      memcpy(mp->indices[s],faces,sizeof(unsigned int)*l);
			      mp->indices[s][l]=mp->nFaces;
			      mp->nIndices[s]=l+1;

			      /* Vertices outside the ball are suitable for expansion */
			      mp->expandible[s]=(Norm(mp->k,mp->vertex[s])>(mp->r+eps));
			      /* except if they are out of the domain. The following test is disconnected since
				 it can produce wrong results in some cases (large charts). Morever, the atlas
			         constructions tools already have strategies to detect the intersection with the
			         domain. */
			      if ((0)&&(mp->expandible[s])&&(c!=NULL)&&(ambient!=NULL)&&(m>0)&&(wcs!=NULL)&&(pr!=NULL))
				{
				  /* We should use chart2manifold but it is more expensive, Local2Global
				     already provides a good indicator of vertexes out of the domain */
				  /* Note that this test is only meaningful if the charts are relatively small (large
				     charts might expand out of the domain but still beint useful. Large charts
				     are typically used in planning (AtlasRRT,...), but in this case we use
				     spolytopes instead than polytopes */
				  Local2Global(mp->vertex[s],tp,pt,(Tchart*)c);
				  mp->expandible[s]=((DistancePointToBoxTopology(pt,tp,ambient)>0.1*mp->r)||
						     (CS_WD_SIMP_INEQUALITIES_ERROR(pr,pt,(TAtlasBase*)wcs)>0.1*mp->r));
				}
			      if (mp->expandible[s])
				mp->nExpandible++;

			      mp->nVertices++;
			    }
			}
		    }
		  free(faces);
		}
	    }

	  /*Remove all vertexes outside the plane*/
	  for(i=0;i<tv;i++)
	    { 
	      /* if vertex in use and outside the plane*/
	      if ((mIndices[i]>0)&&(pos[i]>0)) 
		{
		  mp->nIndices[i]=mp->freeVertex;
		  mp->freeVertex=i;
		  mp->maxIndices[i]=0;
		  free(mp->indices[i]);
		  mp->indices[i]=NULL;
		  free(mp->vertex[i]);
		  mp->vertex[i]=NULL;
		  
		  if (mp->expandible[i])
		    mp->nExpandible--;

		  mp->nVertices--;
		  mp->expandible[i]=FALSE; /* not used */
		}
	  
	      if (eps>0)
		{
		  /* Vertex on the new plane -> add face index to vertex list */
		  if ((mIndices[i]>0)&&(pos[i]==0))
		    {
		      /*Add a new plane to the list of*/
		      if (mp->nIndices[i]==mp->maxIndices[i])
			MEM_DUP(mp->indices[i],mp->maxIndices[i],unsigned int);

		      mp->indices[i][mp->nIndices[i]]=mp->nFaces;
		      mp->nIndices[i]++;
		    }
		}
	    }
      
	  free(mIndices);

	  /*re-compute the bounding box*/
	  firstVertex=TRUE;
	  for(i=0;i<mp->maxVertices;i++)
	    {
	      if (mp->maxIndices[i]>0)
		{
		  if (firstVertex)
		    {
		      DeleteBox(&(mp->bb));
		      InitBoxFromPoint(mp->k,mp->vertex[i],&(mp->bb));
		      firstVertex=FALSE;
		    }
		  else
		    ExpandBox(mp->vertex[i],&(mp->bb));
		} 
	    }

	  /*Store the new face*/
	  if (mp->nFaces==mp->maxFaces)
	    {
	      MEM_DUP(mp->face,mp->maxFaces,double *);
	      MEM_EXPAND(mp->ID,mp->maxFaces,unsigned int);
	    }
  
	  NEW(mp->face[mp->nFaces],mp->k+1,double);
	  for(i=0;i<mp->k;i++)
	    mp->face[mp->nFaces][i]=t[i];
	  mp->face[mp->nFaces][mp->k]=offset;
	  mp->ID[mp->nFaces]=id;
	  mp->nFaces++;
  
	  /*Remove unused faces (faces that do not participate
	    of any vertex)*/
	  NEW(usedFace,mp->nFaces,boolean);
	  for(i=0;i<mp->nFaces;i++)
	    usedFace[i]=FALSE;
  
	  for(i=0;i<mp->maxVertices;i++)
	    {
	      if (mp->maxIndices[i]>0)
		{
		  for(j=0;j<mp->nIndices[i];j++)
		    usedFace[mp->indices[i][j]]=TRUE;
		}
	    }

	  /* While eliminating the unused faces, we update the "open" flag */
	  mp->open=FALSE;
	  for(i=0;i<mp->nFaces;i++)
	    {
	      if (usedFace[i])
		mp->open=((mp->open)||(mp->ID[i]==NO_UINT));
	      else
		{
		  if (mp->face[i]!=NULL)
		    {
		      mp->ID[i]=NO_UINT;
		      
		      free(mp->face[i]);
		      mp->face[i]=NULL;
		    }
		}
	    }

	  free(usedFace);
	}
      free(pos);

      mp->v=-1; /* the volume is invalidated */

      free(pt);
    }
  return(mp->open);
}

double GetPolytopeRadius(Tcpolytope *mp)
{
  return(mp->r);
}

unsigned int GetPolytopeDim(Tcpolytope *mp)
{
  return(mp->k);
}

Tbox *GetPolytopeBB(Tcpolytope *mp)
{
  if (mp->emptyPolytope)
    return(NULL);
  else
    return(&(mp->bb));
}

void SetPolytopeBB(Tbox *bb,Tcpolytope *mp)
{
  if (!mp->emptyPolytope)
    DeleteBox(&(mp->bb));
  CopyBox(&(mp->bb),bb);
}

boolean ExpandiblePolytope(Tcpolytope *mp)
{
  return((mp->emptyPolytope)||(mp->nExpandible>0));
}

void WrongPolytopeCorner(unsigned int nv,Tcpolytope *mp)
{
  if ((!mp->emptyPolytope)&&(nv<mp->maxVertices)&&(mp->expandible[nv]))
    {
      mp->expandible[nv]=FALSE;
      mp->nExpandible--;
    }
}

boolean GetPolytopeInteriorPoint(double rSample,double *t,Tcpolytope *mp)
{
  boolean haveInterior;

  if (mp->nVertices==0)
    haveInterior=FALSE;
  else
    {
      unsigned int i,l;
      double n,m;

      /* In most of the cases the center of the chart is
	 interior to the polytope */
      for(i=0;i<mp->k;i++)
	t[i]=0;

      if (InsidePolytope(t,mp))
	haveInterior=TRUE;
      else
	{
	  /* If the center is not inside the polytope, use
	     the polytope vertex inside the ball with minor
	     norm (minor norm=closest to the chart center where
	     the chartping is more likely to be valid) */
	  haveInterior=FALSE;
	  m=INF;
	  i=0;
	  while(i<mp->maxVertices)
	    {
	      if (mp->maxIndices[i]>0)
		{
		  n=Norm(mp->k,mp->vertex[i]);

		  if ((n<=rSample)&&(n<m))
		    {
		      l=i;
		      n=m;
		      haveInterior=TRUE;
		    }
		}
	      i++;
	    }
	  if (haveInterior)
	    {
	      for(i=0;i<mp->k;i++)
		t[i]=mp->vertex[l][i];
	    }
	  else
	    {
	      PolytopeCenter(t,mp);
	      haveInterior=(Norm(mp->k,t)<=rSample);
	    }
	}
    }
  return(haveInterior);
}

boolean PolytopeBoundaryPointFromExternalCornerInt(unsigned int nc,double rSample,
						   unsigned int *nv,double *t,Tcpolytope *mp)
{
  boolean ok;
  unsigned int i,s;
  double a,b,c,q,l,l1,l2;
  boolean found;

  ok=TRUE;

  /* look for the 'nc' expandible vertex */
  i=0;
  found=FALSE;
  s=0;
  while((!found)&&(i<mp->maxVertices))
    {
      if ((mp->maxIndices[i]>0)&& /*if vertex in use*/
	  (mp->expandible[i])) /*and is expandible */
	{
	  if (s==nc)
	    found=TRUE;
	  else
	    {
	      s++;
	      i++;
	    }
	}
      else
	i++;
    }
  if (!found)
    Error("Inconsistancy in the number of external vertices");

  /* We selected vertex 'i' */
  (*nv)=i;

  if (Norm(mp->k,mp->vertex[i])<mp->r)
    {
      /* Not actually an external point, just return it .... (?) */
      //memcpy(t,mp->vertex[i],mp->k*sizeof(double));
      Warning("A vertex that should be exterior is interior (in PolytopeBoundaryPointFromExternalCornerInt)");
      ok=FALSE;
    }
  else
    {
      /* Get a point inside the rSample ball (and inside the polytope) */
      if (!GetPolytopeInteriorPoint(rSample,t,mp)) 
	ok=FALSE;
      else
	{
	  /*Connect the external vertex and the point and
	    intersect with the ball (with radius rSample)*/
	  /* and we re-use t to store t-vertex[i] and we store the final
	     result in t also*/
	  SubtractVector(mp->k,t,mp->vertex[i]);
	  
	  /* intersect the line between t and vertex[i] and the ball with
	     radius rSample */
	  a=GeneralDotProduct(mp->k,t,t);
	  b=2.0*GeneralDotProduct(mp->k,mp->vertex[i],t);
	  c=GeneralDotProduct(mp->k,mp->vertex[i],mp->vertex[i])-rSample*rSample;

	  q=-0.5*(b+SGN(b)*sqrt(b*b-4*a*c));
	  l1=q/a;
	  l2=c/q;

	  /* If the two solutions are valid we pick the one closest
	     to the interior point (the largest one). At least
	     one of the solutions must be valid */
	  if ((l1>=0)&&(l1<=1))
	    {
	      if ((l2>=0)&&(l2<=1))
		l=(l1>l2?l1:l2);
	      else
		l=l1;
	    }
	  else
	    l=l2;
	  
	  ScaleVector(l,mp->k,t);
	  AccumulateVector(mp->k,mp->vertex[i],t);
	}
    }

  if (!ok)
    {
      /* The vertex is already in the ball (?) or there is no way
         to generate a point on the ball -> just remove the vertex
         from the list o candidates for expansion. This might leave
         a chart without being fully expanded... */
      WrongPolytopeCorner(*nv,mp);
      *nv=NO_UINT;
    }

  return(ok);
}

boolean PolytopeBoundaryPointFromExternalCorner(double rSample,boolean rand,
						unsigned int *nv,double *t,Tcpolytope *mp)
{
  boolean ok;

  if (mp->emptyPolytope)
    DefinePolytope(mp);
    
  if (mp->nExpandible==0)
    {
      ok=FALSE;
      *nv=NO_UINT;
    }
  else
    {
      unsigned int nc;

      /* Pick one expandible vertex at random */
      if (rand)
	nc=randomMax(mp->nExpandible-1);
      else
	nc=0;     

      /* Genereate the boundary point from the selected vertex */
      ok=PolytopeBoundaryPointFromExternalCornerInt(nc,rSample,nv,t,mp);
    }
  return(ok);
}

void PolytopeBoundaryPointsFromExternalCorners(double rSample,unsigned int *n,unsigned int **nv,
					       double ***t,Tcpolytope *mp)
{
  if (mp->emptyPolytope)
    DefinePolytope(mp);
    
  *n=mp->nExpandible;
  if (*n==0)
    {
      *nv=NULL;
      *t=NULL;
    }
  else
    {
      unsigned int i;

      NEW(*nv,*n,unsigned int);
      NEW(*t,*n,double*);
      
      for(i=0;i<mp->nExpandible;i++)
	{
	  NEW((*t)[i],mp->k,double);
	  
	  if (!PolytopeBoundaryPointFromExternalCornerInt(i,rSample,&((*nv)[i]),(*t)[i],mp))
	    {
	      free((*t)[i]);
	      (*t)[i]=NULL;
	    }
	}
    }
}

boolean PolytopeRandomPointOnBoundary(double rSample,double *t,Tcpolytope *mp)
{
  randomOnBall(rSample,mp->k,t);
  return(InsidePolytope(t,mp));
}

boolean RandomPointInPolytope(double *t,Tcpolytope *mp)
{
  boolean havePoint;

  if (mp->emptyPolytope)
    {
      unsigned int i;
      double v;
      Tinterval r;
      
      /* For empty polytopes the bounding box is not yet
         defined */
      v=POLYTOPE_R_ENLARGEMENT*mp->r;
      NewInterval(-v,+v,&r);

      for(i=0;i<mp->k;i++)
	t[i]=randomInInterval(&r);

      havePoint=TRUE;
    }
  else
    {
      RandomPointInBox(NULL,t,&(mp->bb));
      havePoint=InsidePolytope(t,mp);
    }

  return(havePoint);
}

double PolytopeMaxVolume(Tcpolytope *mp)
{
  if (mp->emptyPolytope)
    return(pow(2*POLYTOPE_R_ENLARGEMENT*mp->r,mp->k));
  else
    return(GetBoxVolume(NULL,&(mp->bb)));
}

double PolytopeVolume(Tcpolytope *mp)
{
  if (mp->v<0)
    {
      unsigned int i,s,n;
      double *t;

      NEW(t,mp->k,double);
      s=0;
      n=(unsigned int)floor(pow(10,mp->k));
      if (n>10000) n=10000;
      for(i=0;i<n;i++)
	{
	  RandomPointInPolytope(t,mp);
	  if (InsidePolytope(t,mp))
	    s++;
	}
      free(t);
      mp->v=PolytopeMaxVolume(mp)*((double)s)/((double)n);
    }
  return(mp->v);
}

unsigned int PolytopeNumNeighbours(Tcpolytope *mp)
{
  unsigned int k;
  
  k=0;
  if (!mp->emptyPolytope)
    {
      unsigned int i;

      for(i=0;i<mp->nFaces;i++)
	{
	  if (mp->ID[i]!=NO_UINT)
	    k++;
	}
    }
  return(k);
}

unsigned int PolytopeNeighbourID(unsigned int n,Tcpolytope *mp)
{
  boolean found;
  unsigned int i,k,nID;

  found=FALSE;
  if (!mp->emptyPolytope)
    {
      k=0;
      i=0;
      while((!found)&&(i<mp->nFaces))
	{
	  if (mp->ID[i]==NO_UINT)
	    i++;
	  else
	    {
	      if (k==n)
		found=TRUE;
	      else
		{
		  k++;
		  i++;
		}
	    }
	}
    }
  
  if (found)
    nID=mp->ID[i];
  else
    nID=NO_UINT;

  return(nID);
}

void GetPolytopeVertices(unsigned int k,unsigned int *nv,double ***v,Tcpolytope *mp)
{
  unsigned int i;

  if (k<mp->k)
    Error("Wrong dimension in GetPolytopeVertices");
  
  if (mp->emptyPolytope)
    DefinePolytope(mp);

  *nv=0;
  for(i=0;i<mp->maxVertices;i++)
    {
      if (mp->maxIndices[i]>0)
	(*nv)++;
    }
  if ((*nv)>0)
    {
      unsigned int j;

      NEW(*v,*nv,double*);
      j=0;
      for(i=0;i<mp->maxVertices;i++)
	{
	  if (mp->maxIndices[i]>0)
	    {
	      NEWZ((*v)[j],k,double); // 0 for non used components
	      memcpy((*v)[j],mp->vertex[i],sizeof(double)*mp->k);
	      j++;
	    }
	}
    }
  else
    **v=NULL;
}


void GetPolytopeNeighboursFromVertices(unsigned int *nv,unsigned int **cID1,unsigned int **cID2,Tcpolytope *mp)
{
  unsigned int i,j,k1,ne,ncf,*faces;
  
  if (mp->k!=2)
    Error("GetPolytopeNeighboursFromVertices only works for bidimensional manifolds");

  if (mp->emptyPolytope)
    DefinePolytope(mp);

  /* First count the number of vertices */
  *nv=0;
  for(i=0;i<mp->maxVertices;i++)
    {
      if (mp->maxIndices[i]>0)
	(*nv)++;
    }
  if ((*nv)>0)
    {
      NEW((*cID1),*nv,unsigned int);
      NEW((*cID2),*nv,unsigned int);
      
      /* Now, for all edges, determine their extremes */
      NEW(faces,mp->nFaces,unsigned int); /*space needed by HaveEdge*/
      k1=0;
      for(i=0;i<mp->maxVertices;i++)
	{
	  if (mp->maxIndices[i]>0) /* if vertex in use */
	    {
	      ne=0; /* number of edges of vertex k1 */
	      for(j=0;j<mp->maxVertices;j++)
		{
		  if ((i!=j)&&(mp->maxIndices[j]>0)) /* if vertex in use */
		    {
		      if (HaveEdge(i,j,&ncf,faces,mp))
			{
			  /* ncf (number of common faces) is 1 for k=2 
			     and faces[0] is the identifier of the
			     face (edge) connecting vertices i and j */
			  if (ne==0)
			    (*cID1)[k1]=mp->ID[faces[0]];
			  else
			    {
			      if (ne==1)
				(*cID2)[k1]=mp->ID[faces[0]];
			      else
				Error("Three edges in the same vertex?");
			    }
			  ne++;
			}
		    }
		}
	      k1++;
	    }
	}
      free(faces);
    }
  else
    {
      Error("A chart without vertices");
      cID1=NULL;
      cID2=NULL;
    }
}

void GetPolytopeEdges(unsigned int *ne,unsigned int **vID1,unsigned int **vID2,
		      Tcpolytope *mp)
{
  unsigned int i,j,k,k1,k2,ncf;
  unsigned int *faces;

  if (mp->emptyPolytope)
    DefinePolytope(mp);

  NEW(faces,mp->nFaces,unsigned int); /*space needed by HaveEdge*/

  k=mp->nVertices*mp->nVertices/2; /*bound to the maximum number of edges*/
  NEW(*vID1,k,unsigned int);
  NEW(*vID2,k,unsigned int);

  k1=0;
  k2=0;
  *ne=0;
  for(i=0;i<mp->maxVertices;i++)
    {
      if (mp->maxIndices[i]>0) /* if vertex in use */
	{
	  k2=k1+1;
	  for(j=i+1;j<mp->maxVertices;j++)
	    {
	      if (mp->maxIndices[j]>0) /* if vertex in use */
		{
		  if (HaveEdge(i,j,&ncf,faces,mp))
		    {
		      (*vID1)[*ne]=k1;
		      (*vID2)[*ne]=k2;
		      (*ne)++;
		    }
		  k2++;
		}
	    }
	  k1++;
	}
    }

  free(faces);
}

unsigned int PolytopeMemSize(Tcpolytope *mp)
{
  unsigned int i,b;

  b=sizeof(double)*mp->nFaces*(mp->k+1); /* face[][] */
  b+=sizeof(unsigned int)*mp->maxFaces; /* ID[] */

  b+=sizeof(double)*mp->nVertices*mp->k; /* vertex[][] */
  b+=sizeof(boolean)*mp->maxVertices; /* expandible[] */
  
  b+=sizeof(unsigned int)*mp->maxVertices; /* nIndices[] */
  b+=sizeof(unsigned int)*mp->maxVertices; /* maxIndices[] */
  for(i=0;i<mp->maxVertices;i++)
    b+=(sizeof(unsigned int)*mp->maxIndices[i]); /* indices[][] */

  return(b);
}

void SavePolytope(FILE *f,Tcpolytope *mp)
{
  unsigned int i,j;

  fprintf(f,"%u\n",mp->k);
  fprintf(f,"%f\n",mp->r);
  fprintf(f,"%f\n",mp->v);

  fprintf(f,"%u\n",mp->open);

  fprintf(f,"%u\n",mp->emptyPolytope);
  
  if (!mp->emptyPolytope)
    {
      fprintf(f,"%u\n",mp->nExpandible);
      fprintf(f,"%u\n",mp->nVertices);
      fprintf(f,"%u\n",mp->maxVertices);

      if (mp->maxVertices>0)
	{
	  for(i=0;i<mp->maxVertices;i++)
	    {
	      fprintf(f,"%u\n",mp->maxIndices[i]);
	      if (mp->maxIndices[i]>0)
		{
		  for(j=0;j<mp->k;j++)
		    fprintf(f,"%.12f ",mp->vertex[i][j]);
		  fprintf(f,"\n");
	  
		  fprintf(f,"%u\n",mp->nIndices[i]);
		  for(j=0;j<mp->nIndices[i];j++)
		    fprintf(f,"%u ",mp->indices[i][j]);
		  fprintf(f,"\n");
		}
	      else
		fprintf(f,"%u\n",mp->nIndices[i]);

	      fprintf(f,"%u\n",mp->expandible[i]);	  
	    }
	  fprintf(f,"%u\n",mp->freeVertex);

	  fprintf(f,"%u\n",mp->nFaces);
	  if (mp->nFaces>0)
	    {  
	      fprintf(f,"%u\n",mp->maxFaces);
	      for(i=0;i<mp->nFaces;i++)
		{
		  if (mp->face[i]==NULL)
		    fprintf(f,"0\n");
		  else
		    {
		      fprintf(f,"1\n");
		      for(j=0;j<mp->k+1;j++)
			fprintf(f,"%.12f ",mp->face[i][j]);
		      fprintf(f,"\n");
		      fprintf(f,"%u\n",mp->ID[i]);
		    }
		}
	    }
	}

      PrintBox(f,&(mp->bb));
    }
}

void LoadPolytope(FILE *f,Tcpolytope *mp)
{
  unsigned int i,j,flag;

  fscanf(f,"%u",&(mp->k));
  fscanf(f,"%lf",&(mp->r));
  fscanf(f,"%lf",&(mp->v));

  fscanf(f,"%u",&(mp->open));

  fscanf(f,"%u",&(mp->emptyPolytope));
  
  if (!mp->emptyPolytope)
    {
      fscanf(f,"%u",&(mp->nExpandible));
      fscanf(f,"%u",&(mp->nVertices));
      fscanf(f,"%u",&(mp->maxVertices));

      if (mp->maxVertices>0)
	{
	  NEW(mp->vertex,mp->maxVertices,double*);
	  NEW(mp->maxIndices,mp->maxVertices,unsigned int);
	  NEW(mp->nIndices,mp->maxVertices,unsigned int);
	  NEW(mp->indices,mp->maxVertices,unsigned int*);
	  NEW(mp->expandible,mp->maxVertices,boolean);
	  for(i=0;i<mp->maxVertices;i++)
	    {
	      fscanf(f,"%u",&(mp->maxIndices[i]));
	      if (mp->maxIndices[i]>0)
		{
		  NEW(mp->vertex[i],mp->k,double);
		  for(j=0;j<mp->k;j++)
		    fscanf(f,"%lf",&(mp->vertex[i][j]));
	      
		  NEW(mp->indices[i],mp->maxIndices[i],unsigned int);
		  fscanf(f,"%u",&(mp->nIndices[i]));
		  for(j=0;j<mp->nIndices[i];j++)
		    fscanf(f,"%u",&(mp->indices[i][j]));
		}
	      else
		{
		  mp->vertex[i]=NULL;
		  mp->indices[i]=NULL;
		  fscanf(f,"%u",&(mp->nIndices[i]));
		}
	      fscanf(f,"%u",&(mp->expandible[i]));
	    }
	  fscanf(f,"%u",&(mp->freeVertex));

	  fscanf(f,"%u",&(mp->nFaces));
	  if (mp->nFaces>0)
	    {  
	      fscanf(f,"%u",&(mp->maxFaces));
	      NEW(mp->face,mp->maxFaces,double *);
	      NEW(mp->ID,mp->maxFaces,unsigned int);
	      for(i=0;i<mp->nFaces;i++)
		{
		  fscanf(f,"%u",&flag);
		  if (flag)
		    {
		      NEW(mp->face[i],mp->k+1,double);
		      for(j=0;j<mp->k+1;j++)
			fscanf(f,"%lf",&(mp->face[i][j]));
		  
		      fscanf(f,"%u",&(mp->ID[i]));
		    }
		  else
		    {
		      mp->face[i]=NULL;
		      mp->ID[i]=NO_UINT;
		    }
		}
	    }
	  else
	    {
	      mp->face=NULL;
	      mp->maxFaces=0;
	    }

	  ReadBox(f,&(mp->bb));
	}
      else
	{
	  mp->face=NULL;
	  mp->nFaces=0;
	  mp->maxFaces=0;
      
	  mp->vertex=NULL;
	  mp->nIndices=NULL;
	  mp->maxIndices=NULL;
	  mp->indices=NULL;
	  mp->expandible=NULL;

	  mp->freeVertex=NO_UINT;
	}
    }
}

void PrintPolytopeInfo(Tcpolytope *mp)
{
  unsigned int i,j;
  unsigned int nf;

  if (mp->emptyPolytope)
    DefinePolytope(mp);

  nf=0;
  for (i=0;i<mp->maxFaces;i++)
    {
      if (mp->face!=NULL)
	nf++;
    }
  printf("Num vertices     : %u\n",mp->nVertices);
  printf("Num faces        : %u\n",nf);
  printf("New face         : %u\n",mp->nFaces);
  for(i=0;i<mp->maxVertices;i++)
    {
      if (mp->maxIndices[i]>0)
	{
	  printf("Vertex %u -> [ ",i);
	  for(j=0;j<mp->nIndices[i];j++)
	    printf("%u ",mp->indices[i][j]);
	  printf("]\n");
	}
    }
  fflush(stdout);
}

void DeletePolytope(Tcpolytope *mp)
{
  if (!mp->emptyPolytope)
    {
      unsigned int i;
      
      for(i=0;i<mp->nFaces;i++)
	{
	  if (mp->face[i]!=NULL)
	    free(mp->face[i]);
	}
      free(mp->face);
      mp->face=NULL;
      mp->nFaces=0;
      mp->maxFaces=0;

      free(mp->ID);
      mp->ID=NULL;

      for(i=0;i<mp->maxVertices;i++)
	{
	  /* if the vertex is not-free. */
	  if (mp->maxIndices[i]>0) /* same as  mp->vertices[i]!=NULL */
	    {
	      free(mp->vertex[i]);
	      free(mp->indices[i]);
	    }
	}
      free(mp->vertex);
      free(mp->nIndices);
      free(mp->maxIndices);
      free(mp->indices);
      free(mp->expandible);

      mp->nExpandible=0;
      mp->nVertices=0;
      
      mp->vertex=NULL;
      mp->nIndices=NULL;
      mp->maxIndices=NULL;
      mp->indices=NULL;
      mp->expandible=NULL;

      mp->maxVertices=0;
      mp->freeVertex=NO_UINT;

      DeleteBox(&(mp->bb));
    }
}
