#include "scpolytope.h"

#include "defines.h"
#include "random.h"
#include "algebra.h"
#include "geom.h"

#include "math.h"
#include "string.h"

/** 
   \file scpolytope.c
   \brief Implementation of a polytope associated to a chart.

   Implements the functions for the polytope defined in a chart
   (i.e., in the tangent space to a variety defined on a given point).

   \sa Tscpolytope,scpolytope.h
*/

void InitEmptySPolytope(double delta,unsigned int k,double r,double sr,Tscpolytope *mp)
{
  mp->r=r;

  mp->sr=sr;  
  mp->lsr=mp->r+2*delta;
  if (mp->sr<mp->lsr)
    mp->sr=mp->lsr;
  mp->msr=mp->sr;

  mp->k=k;

  mp->nFaces=0;
  mp->maxFaces=0;

  /* Empty space for faces*/
  mp->face=NULL;
  mp->ID=NULL;

  mp->v=SPolytopeMaxVolume(mp);
}

void DefineSPolytope(Tscpolytope *mp)
{
  if (mp->maxFaces==0)
    {
      /* Define space for the faces */
      mp->maxFaces=INIT_NUM_FACES; 
      NEW(mp->face,mp->maxFaces,double *);
      NEW(mp->ID,mp->maxFaces,unsigned int);
    }
}

void CopySPolytope(Tscpolytope *mp_dst,Tscpolytope *mp_src)
{
  mp_dst->k=mp_src->k;
  mp_dst->r=mp_src->r;
  mp_dst->sr=mp_src->sr;
  mp_dst->lsr=mp_src->lsr;
  mp_dst->msr=mp_src->msr;
  mp_dst->v=mp_src->v;

  mp_dst->nFaces=mp_src->nFaces;
  mp_dst->maxFaces=mp_src->maxFaces;

  if (mp_src->maxFaces>0)
    {
      unsigned int i,j;

      NEW(mp_dst->face,mp_dst->maxFaces,double *);
      NEW(mp_dst->ID,mp_dst->maxFaces,unsigned int);
      for(i=0;i<mp_dst->nFaces;i++)
	{
	  NEW(mp_dst->face[i],mp_dst->k+1,double);
	  for(j=0;j<mp_dst->k+1;j++)
	    mp_dst->face[i][j]=mp_src->face[i][j];

	  mp_dst->ID[i]=mp_src->ID[i];
	}
    }
  else
    {
      mp_dst->face=NULL;
      mp_dst->ID=NULL;
    }
}

boolean InsideSPolytope(double *t,Tscpolytope *mp)
{
  unsigned int i;
  boolean inside;

  inside=(Norm(mp->k,t)<=mp->msr);
  
  //PrintVector(stderr,"x:",mp->k,t);
  //fprintf(stderr,"faces %u\n",mp->nFaces);
  i=0;
  while((i<mp->nFaces)&&(inside))
    {
      inside=(GeneralDotProduct(mp->k,mp->face[i],t)+mp->face[i][mp->k]<=0);
      
      /*
      PrintVector(stderr,"  f:",mp->k+1,mp->face[i]);
      if (inside)
	fprintf(stderr,"  inside %f\n",GeneralDotProduct(mp->k,mp->face[i],t)+mp->face[i][mp->k]);
      else
	fprintf(stderr,"  outside %f\n",GeneralDotProduct(mp->k,mp->face[i],t)+mp->face[i][mp->k]);
      */
      i++;
    }

  return(inside);
}

unsigned int DetermineSPolytopeNeighbour(double epsilon,double *t,Tscpolytope *mp)
{
  if ((Norm(mp->k,t)<=mp->r)&&(!InsideSPolytope(t,mp)))
    {
      unsigned int nv,s;
      unsigned int *v;
      double a1,a2,ac;
      double *p;
      unsigned int i,id;
      boolean found;

      NEW(v,mp->nFaces,unsigned int); 
      nv=0;
      for(i=0;i<mp->nFaces;i++)
	{
	  if (GeneralDotProduct(mp->k,mp->face[i],t)+mp->face[i][mp->k]>0)
	    {
	      v[nv]=i;
	      nv++;
	    }
	}
     
      if (nv>1)
	{
	  NEW(p,mp->k,double);
	  a1=0.0;
	  a2=1.0;
	  ac=0.9;
	  found=FALSE;
	  while(!found)
	    {
	      memcpy(p,t,sizeof(double)*mp->k);
	      ScaleVector(ac,mp->k,p);
	      
	      s=0;
	      for(i=0;i<nv;i++)
		{
		  id=v[i];
		  if (GeneralDotProduct(mp->k,mp->face[id],p)+mp->face[id][mp->k]>0)
		    s++;
		}
	      
	      found=((s==1)||((a2-a1)<epsilon));
	      if (!found)
		{
		  if (nv==0)
		    a1=ac;
		  else
		    a2=ac;
		  ac=0.1*a1+0.9*a2;
		}
	    }
	  free(p);
	}

      id=mp->ID[v[0]];
      free(v);
  
      return(id);
    }
  else
    return(NO_UINT);
}


void EnlargeSPolytope(double *t,Tscpolytope *mp)
{
  unsigned int i;
  double v;

  for(i=0;i<mp->nFaces;i++)
    {
      v=(GeneralDotProduct(mp->k,mp->face[i],t)+mp->face[i][mp->k]);
      if (v>0)
	{
	  mp->face[i][mp->k]-=v;
	  mp->v=-1.0; /* the volume is invalidated */
	}
    }
}

void CutSPolytope(double *t,double r,unsigned int id,Tscpolytope *mp)
{
  double n;

  /*The plane separating the two spheres has parameters 't'
    and the offset  is computed here */
  n=Norm(mp->k,t);
  
  /* Note that typically mp->r==r and thus  
     -(mp->r*mp->r-r*r+n*n)/2.0 = -n*n/2.0*/
  CutSPolytopeWithFace(t,-(mp->r*mp->r-r*r+n*n)/2.0,id,mp);
}

void CutSPolytopeWithFace(double *t,double offset,unsigned int id,Tscpolytope *mp)
{
  #if (HALF_PLANES)
    unsigned int i;

    /* empty identifiers are used in normal polytopes to bound the 
       initial polytope (a box). Here the box is explicitly defined 
       (no need of this extra faces). */
    if (id!=NO_UINT)
      {
	if (mp->maxFaces==0)
	  DefineSPolytope(mp); /*make initial room for the faces*/
      
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

	/*
	  fprintf(stderr,"New face[%u]: %u\n",mp->nFaces,id);
	  PrintVector(stderr,"  t",mp->k,t);
	  fprintf(stderr,"  nm: %f\n",Norm(mp->k,t)); 
	  fprintf(stderr,"  of: %f\n",offset);
	  fprintf(stderr,"  id: %u\n",id);
	  PrintVector(stderr,"f",mp->k+1,mp->face[mp->nFaces]);
	*/
      
	mp->nFaces++;
      
	mp->v=-1.0; /* the volume is invalidated */
      }
  #endif
}

double GetSPolytopeRadius(Tscpolytope *mp)
{
  return(mp->r);
}

double GetSPolytopeBoxSide(Tscpolytope *mp)
{ 
  return(2*mp->sr);
}

unsigned int GetSPolytopeDim(Tscpolytope *mp)
{
  return(mp->k);
}

unsigned int GetSPolytopeNFaces(Tscpolytope *mp)
{
  return(mp->nFaces);
}

void GetSPolytopeFace(unsigned int n,double *f,Tscpolytope *mp)
{
  if (n<mp->nFaces)
    memcpy(f,mp->face[n],(mp->k+1)*sizeof(double));
}

boolean SPolytopeRandomPointOnBoundary(double rSample,double *t,Tscpolytope *mp)
{
  randomOnBall(rSample,mp->k,t);
  return(InsideSPolytope(t,mp));
}


boolean RandomPointInSPolytope(double scale,double *t,Tscpolytope *mp)
{
  boolean havePoint;
  double sr;

  sr=scale*mp->sr;
  if (sr>mp->msr) sr=mp->msr;
  else if (sr<mp->lsr) sr=mp->lsr;

  randomInBall(sr,mp->k,t);

  #if (RANDOM_HALF_PLANES)
    if (mp->nFaces==0)
      havePoint=TRUE;
    else
      havePoint=InsideSPolytope(t,mp);
  #else
     havePoint=TRUE;
  #endif

  return(havePoint);
}

double SPolytopeGetSamplingRadius(Tscpolytope *mp)
{
  return(mp->sr);
}

void SPolytopeIncreaseSamplingRadius(Tscpolytope *mp)
{
  mp->sr*=(1.0+MOV_AVG_UP);
  if (mp->sr>mp->msr)
    mp->sr=mp->msr;
}

void SPolytopeDecreaseSamplingRadius(Tscpolytope *mp)
{
  mp->sr*=(1.0-MOV_AVG_DOWN);
  if (mp->sr<mp->lsr)
    mp->sr=mp->lsr;
}

double SPolytopeMaxVolume(Tscpolytope *mp)
{
  return(BallVolume(mp->k,mp->sr));
}

double SPolytopeVolume(Tscpolytope *mp)
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
	  randomInBall(mp->sr,mp->k,t);
	  if (InsideSPolytope(t,mp))
	    s++;
	}
      free(t);
      mp->v=BallVolume(mp->k,mp->sr)*((double)s)/((double)n);
    }
  return(mp->v);
}

unsigned int SPolytopeNumNeighbours(Tscpolytope *mp)
{
  return(mp->nFaces);
}

unsigned int SPolytopeNeighbourID(unsigned int n,Tscpolytope *mp)
{
  if (n<mp->nFaces)
    return(mp->ID[n]);
  else
    return(NO_UINT);
}

unsigned int SPolytopeMemSize(Tscpolytope *mp)
{
  unsigned int b;

  b=sizeof(double)*mp->nFaces*(mp->k+1); /* face[][] */
  b+=sizeof(unsigned int)*mp->nFaces; /* ID[] */

  return(b);
}

void SaveSPolytope(FILE *f,Tscpolytope *mp)
{
  unsigned int i,j;

  fprintf(f,"%u\n",mp->k);
  fprintf(f,"%f\n",mp->r);
  fprintf(f,"%f\n",mp->sr);
  fprintf(f,"%f\n",mp->lsr);
  fprintf(f,"%f\n",mp->msr);
  fprintf(f,"%f\n",mp->v);

  fprintf(f,"%u\n",mp->nFaces);
  fprintf(f,"%u\n",mp->maxFaces);

  if (mp->nFaces>0)
    {
      for(i=0;i<mp->nFaces;i++)
	{
	  for(j=0;j<mp->k+1;j++)
	    fprintf(f,"%.12f ",mp->face[i][j]);
	  fprintf(f,"\n");
	  fprintf(f,"%u\n",mp->ID[i]);
	}
    }
}

void LoadSPolytope(FILE *f,Tscpolytope *mp)
{
  unsigned int i,j;

  fscanf(f,"%u",&(mp->k));
  fscanf(f,"%lf",&(mp->r));
  fscanf(f,"%lf",&(mp->sr));
  fscanf(f,"%lf",&(mp->lsr));
  fscanf(f,"%lf",&(mp->msr));
  fscanf(f,"%lf",&(mp->v));

  fscanf(f,"%u",&(mp->nFaces));
  fscanf(f,"%u",&(mp->maxFaces));

  if (mp->maxFaces>0)
    {  
      NEW(mp->face,mp->maxFaces,double *);
      NEW(mp->ID,mp->maxFaces,unsigned int);
      for(i=0;i<mp->nFaces;i++)
	{
	  NEW(mp->face[i],mp->k+1,double);
	  for(j=0;j<mp->k+1;j++)
	    fscanf(f,"%lf",&(mp->face[i][j]));
	  
	  fscanf(f,"%u",&(mp->ID[i]));
	}
    }
  else
    {
      mp->face=NULL;
      mp->ID=NULL;
    }
}

void DeleteSPolytope(Tscpolytope *mp)
{
  if (mp->maxFaces>0)
    {
      unsigned int i;
      
      for(i=0;i<mp->nFaces;i++)
	{
	  if (mp->face[i]!=NULL)
	    free(mp->face[i]);
	}
      free(mp->face);
      mp->face=NULL;

      free(mp->ID);
      mp->ID=NULL;

      mp->nFaces=0;
      mp->maxFaces=0;
    }
}
