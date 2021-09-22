#include "box.h"

#include "defines.h"
#include "error.h"
#include "random.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>


/** \file box.c
    \brief Implementation of the functions operating on Tbox.

    Implementation of the functions operating on Tbox.

    \sa box.h, Tbox.
*/

/*
 * Inits an empty box in a  'dim' dimensional space
 */
void InitBox(unsigned int dim,Tinterval *is,Tbox *b)
{ 
  b->level=1; /* Default level */
  b->n=dim;
  if (b->n==0)
    b->is=NULL;
  else
    {
      NEW(b->is,b->n,Tinterval);
      if (is!=NULL)
	memcpy(b->is,is,b->n*sizeof(Tinterval));
      else
	{
	  unsigned int i;
	  for(i=0;i<dim;i++)
	    NewInterval(0.0,0.0,&(b->is[i]));
	}
    }
}

void InitBoxFromPoint(unsigned int dim,double *p,Tbox *b)
{
  b->level=1; /* Default level */
  b->n=dim;
  if (b->n==0)
    b->is=NULL;
  else
    {
      unsigned int i;

      NEW(b->is,b->n,Tinterval);
      for(i=0;i<b->n;i++)
	NewInterval(p[i],p[i],&(b->is[i]));
    }
}

void EnlargeBox(double lo,double uo,Tbox *b)
{
   unsigned int i; 
   
   for(i=0;i<b->n;i++)
     EnlargeInterval(lo,uo,&(b->is[i]));
}

void ExpandBox(double *p,Tbox *b)
{
   unsigned int i; 
   
   for(i=0;i<b->n;i++)
     ExpandInterval(p[i],&(b->is[i]));
}


unsigned int GetBoxBufferSize(Tbox *b)
{
  return(b->n*2+4);
}

void Box2Buffer(unsigned int c,unsigned int n,double *buffer,Tbox *b)
{
  unsigned int k,i;

  /* Set the error code (from child to scheduler) */
  switch(c)
    {
    case EMPTY_BOX:
      buffer[0]=-1.0; /*and in the other direction, the first double is also used to send output messages to the scheduler*/
      break;
      
    case ERROR_IN_PROCESS:
      buffer[0]=-2.0; 
      break;
      
    case REDUCED_BOX_WITH_SOLUTION:
      buffer[0]=1.0;
      break;

    case REDUCED_BOX:
      buffer[0]=0.0;
      break;

    default:
      Error("Unknown reduceBox output in Box2Buffer");
      break;
    }
  
  /* Set 'n' (this is used to send info from scheduler to childs and back)*/
  buffer[1]=(double)n;

  buffer[2]=(double)b->level;
  buffer[3]=(double)b->n;
  k=4;
  for(i=0;i<b->n;i++)
    {
      buffer[k++]=LowerLimit(&(b->is[i]));
      buffer[k++]=UpperLimit(&(b->is[i]));
    }
}

void Buffer2Box(unsigned int *c,unsigned int *n,double *buffer,Tbox *b)
{
  unsigned int i,k;

  if (buffer[0]<-1.5)
    *c=ERROR_IN_PROCESS;
  else
    {
      if (buffer[0]<-0.5)
	*c=EMPTY_BOX;
      else
	{
	  if (buffer[0]>0.5)
	    *c=REDUCED_BOX_WITH_SOLUTION;
	  else
	    *c=REDUCED_BOX;
	} 
    }
  
  *n=(unsigned int)(buffer[1]);

  b->level=(unsigned int)(buffer[2]);

  if ((unsigned int)(buffer[3])!=b->n)
    Error("Box and buffer have different size");
  
  k=4;
  for(i=0;i<b->n;i++)
    {
      NewInterval(buffer[k],buffer[k+1],&(b->is[i]));
      k+=2;
    }
}

/*
 * Copies b_in into b_out
 * b_out is supposed initiallized
 */
void CopyBox(void *b_out,void *b_in)
{
  ((Tbox *)b_out)->n=((Tbox *)b_in)->n;
  ((Tbox *)b_out)->level=((Tbox *)b_in)->level;
  NEW(((Tbox *)b_out)->is,((Tbox *)b_out)->n,Tinterval);
  if (((Tbox *)b_out)->n==0)
    ((Tbox *)b_out)->is=NULL;
  else
    memcpy(((Tbox *)b_out)->is,((Tbox *)b_in)->is,((Tbox *)b_out)->n*sizeof(Tinterval));
}

void MergeBoxes(Tbox *b1,Tbox *b2,Tbox *bout)
{
  if (bout==b1)
    {
      MEM_EXPAND(b1->is,b1->n+b2->n,Tinterval);
      memcpy(&(b1->is[b1->n]),b2->is,b2->n*sizeof(Tinterval));
      b1->n+=b2->n;
    }
  else
    {
      if (bout==b2)
	{
	  Tbox baux;
	  
	  CopyBox(&baux,b2);
	  
	  b2->n+=b1->n;
	  MEM_EXPAND(b2->is,b2->n,Tinterval);
	  memcpy(b2->is,b1->is,b1->n*sizeof(Tinterval));
	  memcpy(&(b2->is[b1->n]),baux.is,baux.n*sizeof(Tinterval));

	  DeleteBox(&baux);
	}
      else
	{
	  bout->n=b1->n+b2->n;
	  bout->level=b1->level;
	  NEW(bout->is,bout->n,Tinterval);
	  memcpy(bout->is,b1->is,b1->n*sizeof(Tinterval));
	  memcpy(&(bout->is[b1->n]),b2->is,b2->n*sizeof(Tinterval));
	}
    }
    
}

/*
 * Copies b_in into b_out for some selected variables
 * b_out is supposed initiallized
 */
void CopyBoxSubset(boolean *used,void *b_out,void *b_in)
{
  unsigned int i,n,k;
  
  if (used==NULL)
    n=((Tbox *)b_in)->n;
  else
    {
      n=0;
      for(i=0;i<((Tbox *)b_in)->n;i++)
	if (used[i]) n++;
    }
    

  ((Tbox *)b_out)->n=n;
  ((Tbox *)b_out)->level=((Tbox *)b_in)->level;
  NEW(((Tbox *)b_out)->is,n,Tinterval);
  k=0;
  for (i=0;i<((Tbox *)b_in)->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  CopyInterval(&(((Tbox *)b_out)->is[k]),&(((Tbox *)b_in)->is[i]));
	  k++;
	}
    }
}

void SetBoxSubset(boolean *used,Tbox *bset,Tbox *b)
{
  unsigned int i,k;
  
  k=0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  CopyInterval(&(b->is[i]),&(bset->is[k]));
	  k++;
	}
    }
}

void SetBoxIntervals(Tinterval *is,Tbox *b)
{
  if (b->n>0)
    memcpy(b->is,is,b->n*sizeof(Tinterval));
}

void SetBoxInterval(unsigned int n,Tinterval *is,Tbox *b)
{
  if (n<b->n)
    CopyInterval(&(b->is[n]),is);
  else
    Error("Index out of range in SetBoxInterval");
}

unsigned int GetDistanceWeightsFromBox(double **w,Tbox *b)
{
  unsigned int i;
  double s,f;
  boolean one;

  NEW(*w,b->n,double);
  one=TRUE;
  for(i=0;i<b->n;i++)
    {
      s=IntervalSize(&(b->is[i]));
      (*w)[i]=1.0/(s*s);
      if (i==0)
	{
	  f=(*w)[i];
	  (*w)[i]=1.0;
	}
      else
	(*w)[i]/=f;
	
      one=((one)&&(fabs((*w)[i]-1.0)<1e-3));
    }

  if (one)
    {
      /* All the weights are the same -> just don't use weights */
      free(*w);
      *w=NULL;
    }
  
  return(b->n);
}

/*
 * Returns a pointer to the interval number 'n' of box 'b'
 */
Tinterval *GetBoxInterval(unsigned int n, /*number of the interval to be obtained*/
			  Tbox *b         /*Box*/
			  )
{
  if (n<b->n)
    return(&(b->is[n]));
  else
    Error("Index out of range in GetBoxInterval");
  return(NULL);
}

/*
 * Returns a pointer to the intervals stored in the box
*/
Tinterval *GetBoxIntervals(Tbox *b)
{
  return(b->is);
}

/*
 * bout will be the intersection of b1 and b2. If the boxes do not
 * intersect we return FALSE. We assumbe bout to be properly initialized
 */
boolean BoxesIntersection(boolean *used,Tbox *b1,Tbox *b2,Tbox *bout)
{
  unsigned int i;
  boolean boxes_intersect=TRUE;

  if (b1->n!=b2->n)
    Error("Input boxes with different size in BoxIntersection");
  
  for(i=0;((boxes_intersect)&&(i<b1->n));i++)
    {
      if ((used==NULL)||(used[i]))
	boxes_intersect=Intersection(&(b1->is[i]),&(b2->is[i]),&(bout->is[i]));
    }

  return(boxes_intersect);
}

/*
 * Returns a box that fully includes b_out and b.
 * Like in BoxesIntersection, we assume b_out to be properly initilized
 */
void BoxUnion(boolean *used,Tbox *b1,Tbox *b2,Tbox *b_out)
{
  unsigned int i;

  if (b1->n!=b2->n)
    Error("Input boxes with different size in BoxUnion");

  for(i=0;i<b1->n;i++)
    {
      if ((used==NULL)||(used[i]))
	Union(&(b1->is[i]),&(b2->is[i]),&(b_out->is[i]));
    }
}

void Crop2Box(boolean *used,unsigned int n,double *p,Tbox *b)
{
  unsigned int i;
  double l,u;
  
  if (n!=b->n)
    Error("Point and box of different dimensionality in Crop2Box");
  
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  l=LowerLimit(&(b->is[i]));
	  if (p[i]<l)
	    p[i]=l;
	  else
	    {
	      u=UpperLimit(&(b->is[i]));
	      if (p[i]>u)
		p[i]=u;
	    }
	}
    }
}

/*
 * Returns TRUE if point v is in box b
 */
boolean PointInBox(boolean *used,unsigned int n,double *v,double tol,Tbox *b)
{
  unsigned int i;
  boolean in;

  if (n!=b->n)
    Error("Point and box of different dimensionality in PointInBox");

  in=TRUE;
  for(i=0;((in)&&(i<n));i++)
    {
      if ((used==NULL)||(used[i]))
	in=IsInside(v[i],tol,&(b->is[i]));
    }

  return(in);
}

boolean PointInBoxTopology(boolean *used,boolean update,
			   unsigned int n,double *v,double tol,unsigned int *tp,Tbox *b)
{
  unsigned int i;
  boolean in;
  boolean c;
  double *nv;
  double l,u,a,r;

  if (n!=b->n)
    Error("Point and box of different dimensionality in PointInBox");

  in=TRUE;
 
  c=FALSE;
  NEW(nv,n,double);

  for(i=0;((in)&&(i<n));i++)
    {
      nv[i]=v[i];
      if ((used==NULL)||(used[i]))
	{

	  l=LowerLimit(&(b->is[i]));
	  u=UpperLimit(&(b->is[i]));
	  r=u-l;
	  
	  if ((tp==NULL)||(tp[i]==TOPOLOGY_R)||(l==u)||(r>M_2PI+ANGLE_ACCURACY))
	    /* topology real, null range, or range larger than 2pi */
	    in=IsInside(v[i],tol,&(b->is[i]));
	  else
	    { 
	      /* range size not larger than 2*pi */
	      if (r<(M_2PI-ANGLE_ACCURACY))
		{
		  /* range size lower than 2*pi */
		  PI2PI(l);
		  PI2PI(u);
		}
	      else
		{
		  /* range size 2*pi */
		  l=-M_PI;
		  u=+M_PI;
		}

	      a=v[i];
	      PI2PI(a);		  
	      if (v[i]!=a)
		{
		  nv[i]=a;
		  c=TRUE;
		}

	      if (u<l)
		in=((a<=(u+tol))||((l-tol)<=a));
	      else
		in=(((l-tol)<=a)&&(a<=(u+tol)));
	    }
	}
    }

  if ((update)&&(c))
    //if ((update)&&(in)&&(c))
    memcpy(v,nv,sizeof(double)*n);

  free(nv);

  return(in);
}

unsigned int OutOfBoxTopology(boolean *used,unsigned int n,double *v,
			      unsigned int *tp,signed int *s,Tbox *b)
{
  unsigned int i;
  double l,u,c,d1,d2,r;

  *s=0;
  i=0;
  while((i<n)&&((*s)==0))
    {
      if ((used==NULL)||(used[i]))
	{ 
	  l=LowerLimit(&(b->is[i]));
	  u=UpperLimit(&(b->is[i]));
	  r=u-l;
	  c=v[i];

	  if ((tp==NULL)||(tp[i]==TOPOLOGY_R)||(l==u)||(r>M_2PI+ANGLE_ACCURACY))
	    {
	      /* topology real, null range, or range >2pi */

	      if (c<l) *s=-1;
	      if (c>u) *s=+1;
	    }
	  else
	    {
	      /* range size not larger than 2*pi */
	      if (r<=(M_2PI-ANGLE_ACCURACY))
		{
		  /* range size lower than 2*pi */
		  PI2PI(l);
		  PI2PI(u);
		}
	      else
		{
		  /* range equal to 2*pi */
		  l=-M_PI;
		  u=+M_PI;
		}
	      PI2PI(c);

	      if (u<l)
		{
		  if ((u<c)&&(c<l))
		    {
		      d1=c-u;
		      d2=l-c;
		      if (d1<d2)
			*s=+1;
		      else
			*s=-1;
		    }
		}
	      else
		{
		  /* l<u */
		  if (c<l)
		    {
		      d1=l-c;
		      if (d1>M_PI) d1=M_2PI-d1;
		      d2=u-c;
		      if (d2>M_PI) d2=M_2PI-d2;
		      
		      if (d1<d2)
			*s=-1;
		      else
			*s=+1;
		    }
		  else
		    {
		      if (c>u)
			{
			  d1=c-l;
			  if (d1>M_PI) d1=M_2PI-d1;
			  d2=c-u;
			  if (d2>M_PI) d2=M_2PI-d2;
		      
			  if (d1<d2)
			    *s=-1;
			  else
			    *s=+1;
			}
		    }
		}
	    }
	}
      if ((*s)==0)
	i++;
    }

  if ((*s)==0)
    return(NO_UINT);
  else
    return(i);
}

/*
  'used' has as many elements as ranges in 'b' but 'v' only
  has as many values as TRUE elements in 'used'
*/
boolean PointInSubBox(boolean *used,Tvector *v,double tol,Tbox *b)
{
  unsigned int i,k;
  boolean in;

  in=TRUE;
  k=0;
  for(i=0;((in)&&(i<b->n));i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  in=IsInside(*(double *)GetVectorElement(k,v),tol,&(b->is[i]));
	  k++;
	}
    }

  return(in);
}

/* Computes the distance of a point to the center of a sub-box.
   The ranges defining the sub-box are defined by "used" */
double DistanceToSubBoxCenter(boolean *used,Tvector *v,Tbox *b)
{
  unsigned int i,k;
  double d,d1;

  d=0.0;
  k=0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  d1=(*(double *)GetVectorElement(k,v))-IntervalCenter(&(b->is[i]));
	  d+=d1*d1;
	  k++;
	}
    }

  return(sqrt(d));
}

/*
 * Returns TRUE if the box is basically a point, i.e., if all
 * intervals are smaller than 'epsilon'
 */
boolean IsPunctualBox(boolean *used,double epsilon,Tbox *b)
{
  unsigned int i;
  boolean point;

  i=0;
  point=TRUE;
  while((i<b->n)&&(point))
    { 
      if ((used==NULL)||(used[i]))
	point=(IntervalSize(&(b->is[i]))<=epsilon);
      i++;
    }

  return(point);
}

/*
 * Returns TRUE if the b1 is fully included in b2
 */
boolean BoxInclusion(boolean *used,Tbox *b1,Tbox *b2)
{
  unsigned int i;
  boolean included;

  i=0;
  included=(b1->n==b2->n);

  while((i<b1->n)&&(included))
    { 
      if ((used==NULL)||(used[i]))
	included=IntervalInclusion(&(b1->is[i]),&(b2->is[i]));
      i++;
    }

  return(included); 
}

/*
 * Returns the size of box 'b'.
 */
double GetBoxSize(boolean *used,Tbox *b)         /*box to be measured*/
{
  if (b->n==0)
    return(0);
  else
    return(IntervalSize(&(b->is[GetBoxMaxDim(used,b)])));
}

double GetBoxMaxSizeVarSet(Tvariable_set *vars,Tbox *b)
{
  unsigned int i,n,k;
  double s,smax;
  
  smax=0.0;
  n=VariableSetSize(vars);
  for(i=0;i<n;i++)
    {
      k=GetVariableN(i,vars);
      s=IntervalSize(&(b->is[k]));
      if (s>smax)
	smax=s;
    }

  return(smax);
}

double GetBoxMinSizeVarSet(Tvariable_set *vars,Tbox *b)
{
  unsigned int i,n,k;
  double s,smin;
  
  smin=0.0;
  n=VariableSetSize(vars);
  for(i=0;i<n;i++)
    {
      k=GetVariableN(i,vars);
      s=IntervalSize(&(b->is[k]));
      if ((i==0)||(s<smin))
	smin=s;
    }

  return(smin);
}

/*
 * Returns the length of the diagonal of box 'b'.
 */
double GetBoxDiagonal(boolean *used,Tbox *b)
{
  unsigned int i;
  double d,d1;

  d=0.0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  d1=IntervalSize(&(b->is[i]));
	  d=d+(d1*d1);
	}
    }

  return(sqrt(d));
}

/*
 * Returns the level (or depth) of a given box. The level corresponds
 * to the depth in the search three at which the box is stored 
*/
unsigned int GetBoxLevel(Tbox *b)
{
  return(b->level);
}


void RandomPointInBox(boolean *used,double *c,Tbox *b)
{
  unsigned int i,k;
  
  k=0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  c[k]=randomInInterval(&(b->is[i]));
	  k++;
	}
    }
}

void GetBoxCenter(boolean *used,double *c,Tbox *b)
{
  unsigned int i,k;
  
  k=0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  c[k]=IntervalCenter(&(b->is[i]));
	  k++;
	}
    }
}

/*
 * Returns the distance between the center of two boxes
 */
double GetBoxCenterDistance(boolean *used,Tbox *b1,Tbox *b2)
{
  double d,c1,c2,c;
  unsigned int i;

  if (b1->n!=b2->n)
    Error("Can not compute distance between different size boxes");

  d=0;
  for(i=0;i<b1->n;i++)
    {      
      if ((used==NULL)||(used[i]))
	{
	  c1=IntervalCenter(&(b1->is[i]));
	  c2=IntervalCenter(&(b2->is[i]));
	  c=c1-c2;
	  d+=(c*c);
	}
    }

  return(sqrt(d));
}

double SquaredDistancePointToBox(double t,double *p,Tbox *b)
{
  unsigned int i;
  double d,v;
  
  d=0.0;
  for(i=0;((i<b->n)&&(d<=t));i++)
    {
      v=DistanceToInterval(p[i],&(b->is[i]));
      d+=v*v;
    }

  return(d);
}

double DistancePointToBox(double *p,Tbox *b)
{
  return(sqrt(SquaredDistancePointToBox(INF,p,b)));
}

double SquaredDistanceToBoxDimensionTopology(unsigned int dim,double p,unsigned int *tp,Tbox *b)
{
  double l,u,d,c,d1,d2,r;
  
  l=LowerLimit(&(b->is[dim]));
  u=UpperLimit(&(b->is[dim]));
  r=u-l;
  d=0.0;
  if ((tp==NULL)||(tp[dim]==TOPOLOGY_R)||(l==u)||(r>(M_2PI+ANGLE_ACCURACY)))
    {
      /* topology real, null interval, or range size larger than 2pi */
      /* This is DistanceToInterval but inlined for efficiency */
      if (p<l)
	d=l-p;
      else
	{
	  if (p>u)
	    d=p-u;
	}
    }
  else
    {
      /* range size not larger than 2*pi */
      if (r<=(M_2PI-ANGLE_ACCURACY))
	{
	  /* range size lower than 2*pi */
	  PI2PI(l);
	  PI2PI(u);
	}
      else
	{
	  /* range equal to 2*pi */
	  l=-M_PI;
	  u=+M_PI;
	}
      c=p;
      PI2PI(c);

      if (u<l)
	{
	  if ((u<=c)&&(c<=l))
	    {
	      d1=c-u;
	      d2=l-c;
	      d=(d1<d2?d1:d2);
	    }
	}
      else
	{
	  /* l<u */
	  if (c<l)
	    {
	      d1=l-c;
	      if (d1>M_PI) d1=M_2PI-d1;
	      d2=u-c;
	      if (d2>M_PI) d2=M_2PI-d2;
	      d=(d1<d2?d1:d2);
	    }
	  else
	    {
	      if (c>u)
		{
		  d1=c-l;
		  if (d1>M_PI) d1=M_2PI-d1;
		  d2=c-u;
		  if (d2>M_PI) d2=M_2PI-d2;
		  d=(d1<d2?d1:d2);
		}
	    }
	}
    }
  return(d*d);
}


double SquaredDistancePointToBoxTopology(double t2,double *p,unsigned int *tp,Tbox *b)
{
  unsigned int i;
  double l,u,d,v,c,d1,d2,r;
  
  d=0.0;
  if (tp==NULL)
    {
      for(i=0;((i<b->n)&&(d<t2));i++)
	{
	  l=LowerLimit(&(b->is[i]));
	  u=UpperLimit(&(b->is[i]));

	  /* This is DistanceToInterval but inlined for efficiency */
	  if (p[i]<l)
	    {
	      v=l-p[i];
	      d+=v*v;
	    }
	  else
	    {
	      if (p[i]>u)
		{
		  v=p[i]-u;
		  d+=v*v;
		}
	    }
	}
    }
  else
    {
      for(i=0;((i<b->n)&&(d<t2));i++)
	{
	  l=LowerLimit(&(b->is[i]));
	  u=UpperLimit(&(b->is[i]));
	  r=(u-l);

	  if ((tp[i]==TOPOLOGY_R)||(l==u)||(r>M_2PI+ANGLE_ACCURACY))
	    {
	      /* topology real, null range, or range size > 2pi */
	      /* This is DistanceToInterval but inlined for efficiency */
	      if (p[i]<l)
		{
		  v=l-p[i];
		  d+=v*v;
		}
	      else
		{
		  if (p[i]>u)
		    {
		      v=p[i]-u;
		      d+=v*v;
		    }
		}
	    }
	  else
	    {
	      /* range size not larger than 2*pi */
	      if (r<=(M_2PI-ANGLE_ACCURACY))
		{
		  /* range size lower than 2*pi */
		  PI2PI(l);
		  PI2PI(u);
		}
	      else
		{
		  /* range equal to 2*pi */
		  l=-M_PI;
		  u=+M_PI;
		}
	      c=p[i];
	      PI2PI(c); 

	      if (u<l)
		{
		  if ((u<=c)&&(c<=l))
		    {
		      d1=c-u;
		      d2=l-c;
		      d=(d1<d2?d1:d2);
		    }
		}
	      else
		{
		  /*l<u*/
		  if (c<l)
		    {
		      d1=l-c;
		      if (d1>M_PI) d1=M_2PI-d1;
		      d2=u-c;
		      if (d2>M_PI) d2=M_2PI-d2;
		      v=(d1<d2?d1:d2);
		      d+=v*v;
		    }
		  else
		    {
		      if (c>u)
			{
			  d1=c-l;
			  if (d1>M_PI) d1=M_2PI-d1;
			  d2=c-u;
			  if (d2>M_PI) d2=M_2PI-d2;
			  v=(d1<d2?d1:d2);
			  d+=v*v;
			}
		    }
		}
	    }
	}
    }

  return(d);
}

double DistancePointToBoxTopology(double *p,unsigned int *tp,Tbox *b)
{
  return(sqrt(SquaredDistancePointToBoxTopology(INF,p,tp,b)));
}


/*
 * Returns the normalized volume of a box
 */
double GetBoxVolume(boolean *used,Tbox *b)
{
  double volume;
  unsigned int i;

  volume=1.0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	volume*=(IntervalSize(&(b->is[i])));
    }

  if (b->n==0)
    return(0);
  else
    return(volume);
}

double GetBoxSumSide(boolean *used,Tbox *b)
{
  double ss;
  unsigned int i;

  ss=0.0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	ss+=(IntervalSize(&(b->is[i])));
    }

  if (b->n==0)
    return(0);
  else
    return(ss);
}

unsigned int GetBoxNIntervals(Tbox *b)
{
  return(b->n);
}

/*
 * Returns the dimension along which the box has its maximal size
 */
unsigned int GetBoxMaxDim(boolean *used,Tbox *b)
{
  unsigned int i;
  unsigned int i_max;
  double s;
  double s_max;

  i_max=0;
  s_max=0.0;
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  s=IntervalSize(&(b->is[i]));
	  if (s>s_max)
	    {
	      s_max=s;
	      i_max=i;
	    }
	}
    }
  if (b->n==0)
    return(NO_UINT);
  else
    return(i_max);
}

/*
 * Returns a dimension along which the box has to be splitted
 */
unsigned int GetBoxSplitDim(boolean *used,Tbox *b)
{  

  return(GetBoxMaxDim(used,b));
}

/*
 * Produces two symetrical boxes from 'b' ('b1' and 'b2') that result from
 * spliting 'b' along th 'n' dimension.
 */
void SplitBox(unsigned int n, /*dimension along which the box is splited*/
	      double r,       /*r in [0,1] where to split*/
	      Tbox *b1,       /*first resulting box*/
	      Tbox *b2,       /*second resulting box*/
	      Tbox *b         /*original box*/
	      )
{
  double lp,up,cp;

  if ((r>1.0)||(r<0.0))
    Error("Wrong size to split a box");
  if (n<b->n)
    {  
      /*b1,b2 created here*/

      #if (_DEBUG>6)
        printf("Splitting box along dimension %u\n",n);
      #endif

      b1->n=b->n;
      b2->n=b->n;

      NEW(b1->is,b1->n,Tinterval);/* Lower box */
      NEW(b2->is,b2->n,Tinterval);/* Upper box */
 
      memcpy(b1->is,b->is,b1->n*sizeof(Tinterval)); /*the sub-boxes are the same as the original*/
      memcpy(b2->is,b->is,b1->n*sizeof(Tinterval)); /*but for the split dimension*/

      lp=LowerLimit(&(b->is[n])); /*lower point*/
      up=UpperLimit(&(b->is[n])); /*upper point*/
      cp=PointInInterval(r,&(b->is[n])); /*point scaling in between lower and upper */

      NewInterval(lp,cp,&(b1->is[n]));
      NewInterval(cp,up,&(b2->is[n]));
      
      b1->level=b2->level=b->level+1; /* the boxes resulting from a split are of the next level of the search */
    }
  else
    Error("Index out of range in SplitBox");
}


/*
 * Scales a box taking into account the original ranges for the variables
 */
void ScaleBox(double max_upper,Tbox *b)
{
  unsigned int i;

  for(i=0;i<b->n;i++)
    IntervalScale(&(b->is[i]),max_upper,&(b->is[i]));
}

void AddMargin2Box(double m,Tbox *b)
{
  unsigned int i;
  Tinterval *r;

  for(i=0;i<b->n;i++)
    {
      r=&(b->is[i]);
      NewInterval(LowerLimit(r)-m,UpperLimit(r)+m,r);
    }
}

boolean CmpBoxDepthFirst(void *b1,void *b2,void *userData)
{
  return(((Tbox *)b1)->level>((Tbox *)b2)->level);
}

boolean CmpBoxBreadthFirst(void *b1,void *b2,void *userData)
{
  return(((Tbox *)b1)->level<((Tbox *)b2)->level);
}

/*
 * Prints box 'b' on file 'f'
 */
void PrintBox(FILE *f,Tbox *b)
{ 
  unsigned int i;

  fprintf(f,"{ %u  ",b->n);
  for(i=0;i<b->n;i++)
    {
      //fprintf(f," %u:",i);
      PrintInterval(f,&(b->is[i]));
      fprintf(f," ");
    }

  fprintf(f,"}\n");
  
}

/*
 * Prints box 'b' on file 'f' for some selected variables.
 * This is basically used when printing solutions.
 */
void PrintBoxSubset(FILE *f,boolean *used,char **varNames,Tbox *b)
{ 
  unsigned int i,n;
  
  if (used==NULL)
    n=b->n;
  else
    {
      n=0;
      for(i=0;i<b->n;i++)
	if (used[i]) n++;
    }
    
  fprintf(f,"{ %u  ",n);
  for(i=0;i<b->n;i++)
    {
      if ((used==NULL)||(used[i]))
	{
	  if (varNames!=NULL)
	    {
	      PRINT_VARIABLE_NAME(f,varNames[i]);
	    }
	  PrintInterval(f,&(b->is[i]));
	  fprintf(f," ");
	}
    }

  fprintf(f,"}\n");
}

/*
 * Reads a box from an opened file. Returns EOF if the file finishes before
 * the box could be read
*/
int ReadBox(FILE *f,Tbox *b)
{
  int token=~EOF;
  Tinterval *is;
  double i_min,i_max;
  unsigned int i;
  unsigned int n;

  do token=fgetc(f); while ((token!=EOF)&&(token!='{')); /* skip everything till the beginning of the box */

  if (token!=EOF)
    {
      fscanf(f,"%u",&n);
 
      NEW(is,n,Tinterval);
      
      /* Check whether we have a box with some intervals or an empty box */
      do token=fgetc(f); while ((token!=EOF)&&(token!='[')&&(token!='}'));
      if (token=='}')
	{
	  /* We have an empty box (the old type of box files). Skip the box and advance until the
             first interval of the next box (or end of file) */
	  do token=fgetc(f); while ((token!=EOF)&&(token!='['));
	}
      i=0;
      while ((token!=EOF)&&(token!='}')) //while the box is not closed (and there is something in the file)
	{
	  if (token=='[') //if the interval exists
	    {
	      //read the extremes of the interval
	      if (fscanf(f,"%lf",&i_min)!=EOF)
		{
		  do token=fgetc(f); while ((token!=EOF)&&(token!=','));
		  if (fscanf(f,"%lf",&i_max)!=EOF)  
		    {		    
		      //if there was no problem reading the extremes set up a new interval
		      NewInterval(i_min,i_max,&(is[i++]));
		      
		      if (i>n)
			Error("Too many intervals in the box");
		    }
		  else
		    token=EOF;
		}
	    }
	  //go to the begining of next interval (if it exists)
	  do token=fgetc(f);  while ((token!=EOF)&&(token!='[')&&(token!='}'));

	}

      if (i<n)
	Error("Too few intervals in the box");

      if (token!=EOF)  //if the box was read correctly
	InitBox(n,is,b); /*and set the new ones*/
      free(is);
    }
  
  return(token);
}

/*Saves in binary format*/
void SaveBox(FILE *f,Tbox *b)
{
  fwrite(&(b->n),sizeof(unsigned int),1,f);
  fwrite(&(b->level),sizeof(unsigned int),1,f);
  if (b->n>0)
    fwrite(b->is,sizeof(Tinterval),b->n,f);
}

void LoadBox(FILE *f,Tbox *b)
{
  fread(&(b->n),sizeof(unsigned int),1,f);
  fread(&(b->level),sizeof(unsigned int),1,f);

  if (b->n==0)
    b->is=NULL;
  else
    {
      NEW(b->is,b->n,Tinterval);
      fread(b->is,sizeof(Tinterval),b->n,f);
    }
}

/*
 * Deletes the internal data of a box
 */
void DeleteBox(void *b)
{
  free(((Tbox *)b)->is);
}
