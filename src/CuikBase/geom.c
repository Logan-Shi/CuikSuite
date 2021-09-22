#include "geom.h"

#include "error.h"
#include "defines.h"

#include <math.h>

/** 
   \file geom.c

   \brief Implementation of the basic geometric functions. 

   Implementation of the basic geometric functions. 
   
   \sa geom.h.
*/

boolean pointLeftOfLine(double px,double py,
			double x1,double y1,double x2,double y2)
{
  //        |x1 y1 1|
  //  det = |x2 y2 1| >= 0
  //        |px py 1|
  double det;

  ROUNDDOWN;
  det=(x2*py-px*y2)-(x1*py-px*y1)+(x1*y2-x2*y1);
  ROUNDNEAR;

  return(det>=0);
}


boolean pointRightOfLine(double px,double py,
			 double x1,double y1,double x2,double y2)
{
  //        |x1 y1 1|
  //  det = |x2 y2 1| <= 0
  //        |px py 1|
  double det;

  ROUNDUP;
  det=(x2*py-px*y2)-(x1*py-px*y1)+(x1*y2-x2*y1);
  ROUNDNEAR;

  return (det<=0);
}

/*
 * Computes two intervals that delimite the bounding box for a set of 'n' coordinates
 * in the x,y plane
 */
void ComputeBoundingBox(unsigned int n,double *x,double *y,
			Tinterval *ix,Tinterval *iy)
{ 
  unsigned int i; 
  double x_min,x_max; 
  double y_min,y_max; 

  x_min=x_max=x[0]; 
  y_min=y_max=y[0]; 
  for(i=1;i<n;i++) 
    { 
      if (x[i]>x_max) x_max=x[i]; 
      else {if (x[i]<x_min) x_min=x[i];} 
      if (y[i]>y_max) y_max=y[i]; 
      else {if (y[i]<y_min) y_min=y[i];} 
    }  
  NewInterval(x_min,x_max,ix); 
  NewInterval(y_min,y_max,iy); 
}

void ComputeBoundingBox3d(unsigned int n,double *x,double *y,double *z,
			  Tinterval *ix,Tinterval *iy,Tinterval *iz)
{ 
  unsigned int i; 
  double x_min,x_max; 
  double y_min,y_max; 
  double z_min,z_max; 

  x_min=x_max=x[0]; 
  y_min=y_max=y[0]; 
  z_min=z_max=z[0]; 
  for(i=1;i<n;i++) 
    { 
      if (x[i]>x_max) x_max=x[i]; 
      else {if (x[i]<x_min) x_min=x[i];} 
      if (y[i]>y_max) y_max=y[i]; 
      else {if (y[i]<y_min) y_min=y[i];} 
      if (z[i]>z_max) z_max=z[i]; 
      else {if (z[i]<z_min) z_min=z[i];} 
    }  
  NewInterval(x_min,x_max,ix); 
  NewInterval(y_min,y_max,iy);  
  NewInterval(z_min,z_max,iz); 
}

void SegmentCircleIntersection(double r2,
			       double *x,double *y,
			       double tol,
			       unsigned int *n,
			       double *xi,double *yi)
{
  Tinterval x0,y0,vx,vy,a,b,c,d,t,pos,sqrtD,e,f,l,vl,s;
  
  NewInterval(x[0],x[0],&x0);
  NewInterval(y[0],y[0],&y0);

  IntervalOffset(&x0,-x[1],&vx);
  IntervalInvert(&vx,&vx);
  IntervalOffset(&y0,-y[1],&vy);
  IntervalInvert(&vy,&vy);

  IntervalPow(&vx,2,&a);
  IntervalPow(&vy,2,&t);
  IntervalAdd(&a,&t,&a);

  IntervalScale(&a,2,&f);

  if (IsInside(0,0,&f))
    Error("SegmentCircleIntersection with a 0-length segment");

  IntervalProduct(&x0,&vx,&b); 
  IntervalProduct(&y0,&vy,&t);
  IntervalAdd(&b,&t,&b);
  IntervalScale(&b,2,&b);

  IntervalPow(&x0,2,&c);
  IntervalPow(&y0,2,&t);
  IntervalAdd(&c,&t,&c);
  IntervalOffset(&c,-r2,&c);

  IntervalPow(&b,2,&d);
  IntervalProduct(&a,&c,&t);
  IntervalScale(&t,4,&t);
  IntervalSubstract(&d,&t,&d);

  NewInterval(0,INF,&pos);
  Intersection(&d,&pos,&d);
  
  if (EmptyInterval(&d))
    *n=0;
  else
    {
      NewInterval(0-tol,1+tol,&vl);

      IntervalSqrt(&d,&sqrtD);

      *n=0;
      IntervalSubstract(&sqrtD,&b,&e);
      IntervalDivision(&e,&f,&l);
      Intersection(&l,&vl,&l);
      if (!EmptyInterval(&l))
	{
	  IntervalProduct(&l,&vx,&s);
	  IntervalAdd(&x0,&s,&s);
	  xi[0]=IntervalCenter(&s);

	  IntervalProduct(&l,&vy,&s);
	  IntervalAdd(&y0,&s,&s);
	  yi[0]=IntervalCenter(&s);

	  (*n)++;
	}
      
      IntervalInvert(&sqrtD,&sqrtD);
      IntervalSubstract(&sqrtD,&b,&e);
      IntervalDivision(&e,&f,&l);
      Intersection(&l,&vl,&l);
      if (!EmptyInterval(&l))
	{
	  IntervalProduct(&l,&vx,&s);
	  IntervalAdd(&x0,&s,&s);
	  xi[*n]=IntervalCenter(&s);

	  IntervalProduct(&l,&vy,&s);
	  IntervalAdd(&y0,&s,&s);
	  yi[*n]=IntervalCenter(&s);

	  (*n)++;
	}
    }
}

void SegmentSphereIntersection(double r2,
			       double *x,double *y,double *z,
			       double tol,
			       unsigned int *n,
			       double *xi,double *yi,double *zi)
{
  Tinterval x0,y0,z0,vx,vy,vz,a,b,c,d,t,pos,sqrtD,e,f,l,vl,s;
  
  NewInterval(x[0],x[0],&x0);
  NewInterval(y[0],y[0],&y0);
  NewInterval(z[0],z[0],&z0);

  IntervalOffset(&x0,-x[1],&vx);
  IntervalInvert(&vx,&vx);
  IntervalOffset(&y0,-y[1],&vy);
  IntervalInvert(&vy,&vy);
  IntervalOffset(&z0,-z[1],&vz);
  IntervalInvert(&vz,&vz);

  IntervalPow(&vx,2,&a);
  IntervalPow(&vy,2,&t);
  IntervalAdd(&a,&t,&a);
  IntervalPow(&vz,2,&t);
  IntervalAdd(&a,&t,&a);

  IntervalScale(&a,2,&f);

  if (IsInside(0,0,&f))
    Error("SegmentCircleIntersection with a 0-length segment");

  IntervalProduct(&x0,&vx,&b); 
  IntervalProduct(&y0,&vy,&t);
  IntervalAdd(&b,&t,&b); 
  IntervalProduct(&z0,&vz,&t);
  IntervalAdd(&b,&t,&b);
  IntervalScale(&b,2,&b);

  IntervalPow(&x0,2,&c);
  IntervalPow(&y0,2,&t);
  IntervalAdd(&c,&t,&c);
  IntervalPow(&z0,2,&t);
  IntervalAdd(&c,&t,&c);
  IntervalOffset(&c,-r2,&c);

  IntervalPow(&b,2,&d);
  IntervalProduct(&a,&c,&t);
  IntervalScale(&t,4,&t);
  IntervalSubstract(&d,&t,&d);

  NewInterval(0,INF,&pos);
  Intersection(&d,&pos,&d);
  
  if (EmptyInterval(&d))
    *n=0;
  else
    {
      NewInterval(0-tol,1+tol,&vl);

      IntervalSqrt(&d,&sqrtD);

      *n=0;
      IntervalSubstract(&sqrtD,&b,&e);
      IntervalDivision(&e,&f,&l);
      Intersection(&l,&vl,&l);
      if (!EmptyInterval(&l))
	{
	  IntervalProduct(&l,&vx,&s);
	  IntervalAdd(&x0,&s,&s);
	  xi[0]=IntervalCenter(&s);

	  IntervalProduct(&l,&vy,&s);
	  IntervalAdd(&y0,&s,&s);
	  yi[0]=IntervalCenter(&s);

	  IntervalProduct(&l,&vz,&s);
	  IntervalAdd(&z0,&s,&s);
	  zi[0]=IntervalCenter(&s);

	  (*n)++;
	}
      
      IntervalInvert(&sqrtD,&sqrtD);
      IntervalSubstract(&sqrtD,&b,&e);
      IntervalDivision(&e,&f,&l);
      Intersection(&l,&vl,&l);
      if (!EmptyInterval(&l))
	{
	  IntervalProduct(&l,&vx,&s);
	  IntervalAdd(&x0,&s,&s);
	  xi[*n]=IntervalCenter(&s);

	  IntervalProduct(&l,&vy,&s);
	  IntervalAdd(&y0,&s,&s);
	  yi[*n]=IntervalCenter(&s);

	  IntervalProduct(&l,&vz,&s);
	  IntervalAdd(&z0,&s,&s);
	  zi[*n]=IntervalCenter(&s);

	  (*n)++;
	}
    }
}

void Line2Points(double *x,double *y,boolean normalized,double *c)
{
  double vx,vy;
  double n;

  vx=x[1]-x[0];
  vy=y[1]-y[0];

  n=sqrt(vx*vx+vy*vy);
  if (n<ZERO)
    Error("Punctual segment in Line2Points");

  c[0]= vy;
  c[1]=-vx;
  c[2]=-x[0]*vy+y[0]*vx;

  if (normalized)
    {
      c[0]/=n;
      c[1]/=n;
      c[2]/=n;
    }
}

void Plane3Points(double *x,double *y,double *z,
		  boolean normalized,double *c)
{
  double v1[3],v2[3];
  double n;

  v1[0]=x[1]-x[0];
  v1[1]=y[1]-y[0];
  v1[2]=z[1]-z[0];

  v2[0]=x[2]-x[0];
  v2[1]=y[2]-y[0];
  v2[2]=z[2]-z[0];
  
  CrossProduct(v1,v2,c);

  n=sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
  
  if (n<ZERO)
    Error("Aligned points in Plane3Points");

  if (normalized)
    {
      c[0]/=n;
      c[1]/=n;
      c[2]/=n;
    }

  c[3]=-(c[0]*x[0]+c[1]*y[0]+c[2]*z[0]);
}

/*
 * Performs the Clipping between a rectangle and a circle.
 */
boolean RectangleCircleClipping(double r2,
				Tinterval *x,Tinterval *y,
				Tinterval *x_new,Tinterval *y_new)
{
  Tinterval d,md,a,b,diameter,rad2;
  boolean full;
  double r;

  /* First, both x,y must be inside the square +/-r 
     This is basically to deal with infinite ranges */
  ROUNDUP;
  r=sqrt(r2);
  ROUNDNEAR;
  NewInterval(-r,+r,&diameter);
  full=((Intersection(x,&diameter,x_new))&&
	(Intersection(y,&diameter,y_new)));

  if (full)
    {
      NewInterval(r2-ZERO,r2+ZERO,&rad2);
      /* y = sqrt(r2 - x^2) */
      IntervalPow(x_new,2,&d);
      IntervalInvert(&d,&d);
      IntervalAdd(&d,&rad2,&d);
      IntervalSqrt(&d,&d);
      IntervalInvert(&d,&md);
  
      Intersection(y_new,&d,&a);
      Intersection(y_new,&md,&b);

      full=Union(&a,&b,y_new);
  
      if (full)
	{ 
	  /* x = sqrt(r2 - y_new^2) */
	  IntervalPow(y_new,2,&d);
	  IntervalInvert(&d,&d);
	  IntervalAdd(&d,&rad2,&d);
	  IntervalSqrt(&d,&d);
	  IntervalInvert(&d,&md);
      
	  Intersection(x_new,&d,&a);
	  Intersection(x_new,&md,&b);

	  full=Union(&a,&b,x_new);
	}
    }
  return(full); 
}


/*
 * Performs the Clipping between a 3d box and a sphere.
 */
boolean BoxSphereClipping(double r2,
			  Tinterval *x,Tinterval *y,Tinterval *z,
			  Tinterval *x_new,Tinterval *y_new,Tinterval *z_new)
{
  Tinterval d,md,a,b,rad2,diameter;
  boolean full;
  double r;

  /* First, both x,y must be inside the square +/-r 
     This is basically to deal with infinite ranges */
  ROUNDUP;
  r=sqrt(r2);
  ROUNDNEAR;
  NewInterval(-r,+r,&diameter);
  full=((Intersection(x,&diameter,x_new))&&
	(Intersection(y,&diameter,y_new))&&
	(Intersection(z,&diameter,z_new)));

  if (full)
    {
      /* z = sqrt(r2 - x^2 - y^2) */
      NewInterval(r2-ZERO,r2+ZERO,&rad2);
      IntervalPow(x_new,2,&a);
      IntervalPow(y_new,2,&b);
      IntervalAdd(&a,&b,&d);
      IntervalInvert(&d,&d);
      IntervalAdd(&d,&rad2,&d);
      IntervalSqrt(&d,&d);
      IntervalInvert(&d,&md);
  
      Intersection(z_new,&d,&a);
      Intersection(z_new,&md,&b);
      full=Union(&a,&b,z_new);
  
      if (full)
	{ 
	  /* y = sqrt(r2 - x^2 - z_new^2) */
	  IntervalPow(x_new,2,&a);
	  IntervalPow(z_new,2,&b);
	  IntervalAdd(&a,&b,&d);
	  IntervalInvert(&d,&d);
	  IntervalAdd(&d,&rad2,&d);
	  IntervalSqrt(&d,&d);
	  IntervalInvert(&d,&md);
      
	  Intersection(y_new,&d,&a);
	  Intersection(y_new,&md,&b);
	  full=Union(&a,&b,y_new);

	  if (full)
	    {
	      /* x = sqrt(r2 - y_new^2 - z_new^2) */
	      IntervalPow(y_new,2,&a);
	      IntervalPow(z_new,2,&b);
	      IntervalAdd(&a,&b,&d);
	      IntervalInvert(&d,&d);
	      IntervalAdd(&d,&rad2,&d);
	      IntervalSqrt(&d,&d);
	      IntervalInvert(&d,&md);
	  
	      Intersection(x_new,&d,&a);
	      Intersection(x_new,&md,&b);
	      full=Union(&a,&b,x_new);
	    }
	}
    }
  return(full);
}

/*
 * Clipping of a 2d box with the function  x^2 + \alpha y= \beta
*/
boolean RectangleParabolaClipping(Tinterval *x,double alpha,double beta,Tinterval *y,
				  Tinterval *x_new,Tinterval *y_new)
{
  Tinterval d,md,a,b,s;
  boolean full;
  double s1,s2;

  /* y = (1/alpha) *(beta - x^2) */
  ROUNDDOWN;
  s1=1/alpha;
  ROUNDUP;
  s2=1/alpha;
  ROUNDNEAR;
  NewInterval(s1,s2,&s);

  IntervalPow(x,2,&d);
  IntervalInvert(&d,&d);
  IntervalOffset(&d,beta,&d);
  IntervalProduct(&d,&s,&d);

  full=Intersection(y,&d,y_new);

  if (full)
    { 
      /* x = +/- sqrt(beta-alpha * y_new)*/
      IntervalScale(y_new,alpha,&d);
      IntervalInvert(&d,&d);
      IntervalOffset(&d,beta,&d);
    
      IntervalSqrt(&d,&d);
      IntervalInvert(&d,&md);
      
      Intersection(x,&d,&a);
      Intersection(x,&md,&b);
      full=Union(&a,&b,x_new);
    }
  
  return(full);
}

/*
  A saddle is a function of the form
     x * y + \alpha z = \beta
  This implements the clipping between a saddle and a 3d box
*/
boolean BoxSaddleClipping(Tinterval *x,Tinterval *y,double alpha,double beta,Tinterval *z,
			  Tinterval *x_new,Tinterval *y_new,Tinterval *z_new)

{
  Tinterval d,s;
  boolean full;
  double s1,s2;

  /* z=(1/alpha)*(beta-x*y) */
  ROUNDDOWN;
  s1=1/alpha;
  ROUNDUP;
  s2=1/alpha;
  ROUNDNEAR;
  NewInterval(s1,s2,&s);

  IntervalProduct(x,y,&d);
  IntervalInvert(&d,&d);
  IntervalOffset(&d,beta,&d);
  IntervalProduct(&s,&d,&d);

  full=Intersection(z,&d,z_new);

  if (full)
    { 
      /* x=(beta-alpha*z_new)/y */
      if (IsInside(0.0,0.0,y))
	CopyInterval(x_new,x);
      else
	{
	  IntervalScale(z_new,-alpha,&d);
	  IntervalOffset(&d,beta,&d);
	  IntervalDivision(&d,y,&d);
	  full=Intersection(x,&d,x_new);
	}

      if (full)
	{ 
	  /* y=(beta-alpha*z_new)/x_new */
	  if (IsInside(0.0,0.0,x_new))
	    CopyInterval(y_new,y);
	  else
	    {
	      IntervalScale(z_new,-alpha,&d);
	      IntervalOffset(&d,beta,&d);
	      IntervalDivision(&d,x_new,&d);
	      full=Intersection(y,&d,y_new);
	    }
	}
    }
   return(full);
}

void DefineNormalVector(double *v,double *n)
{
  unsigned int i;
  double norm;
  
  /* First check if we have a trivial case (X,Y,Z vector) */
  if ((n[1]==0.0)&&(n[2]==0.0)) // X-vector
    {
      v[0]=0.0;v[1]=1.0;v[2]=0.0; // Y
    }
  else
    {
      if ((n[0]==0.0)&&(n[2]==0.0)) // Y-vector
	{
	  v[0]=-1.0;v[1]=0.0;v[2]=0.0; // -X (Stay in the XY plane just in case)
	} 
      else
	{
	  if ((n[0]==0.0)&&(n[1]==0.0)) // Z-vector (already out of the XY plane)
	    {
	      v[0]=1.0;v[1]=0.0;v[2]=0.0; // X
	    } 
	  else
	    {
	      if (n[2]==0.0) /* A vector in the X-Y plane */
		{
		  v[0]=-n[1]; /* x=-y */
		  v[1]= n[0]; /* y= x */
		  v[2]=0.0;
		}
	      else
		{
		  /* The general case */
		  if (n[0]!=0.0)
		    {
		      v[1]=v[2]=1.0;
		      v[0]=-(n[1]+n[2])/n[0];
		    }
		  else
		    {
		      if (n[1]!=0.0)
			{
			  v[0]=v[2]=1.0;
			  v[1]=-(n[0]+n[2])/n[1];
			}
		      else
			{ 
			  if (n[2]!=0.0)
			    {
			      v[0]=v[1]=1.0;
			      v[2]=-(n[0]+n[1])/n[2];
			    }
			  else
			    Error("Null input vector in DefineNormalVector");
			}
		    }
		}
	      norm=0.0;
	      for(i=0;i<3;i++)
		norm=norm+v[i]*v[i];
	      norm=sqrt(norm);
	      for(i=0;i<3;i++)
		v[i]/=norm;
	    }
	}
    }
}

void CrossProduct(double *v1,double *v2,double *v3)
{
  double a,b,c;

  a= (v1[1]*v2[2])-(v1[2]*v2[1]);
  b=-(v1[0]*v2[2])+(v1[2]*v2[0]);
  c= (v1[0]*v2[1])-(v1[1]*v2[0]);

  v3[0]=a;
  v3[1]=b;
  v3[2]=c;
}

double DotProduct(double *v1,double *v2)
{
  return(v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]);
}

boolean NeighbouringTriangles(unsigned int *v1,unsigned int *v2)
{
  unsigned int i;
  unsigned int ns;

  ns=0;
  for(i=0;i<3;i++)
    {
      if ((v1[i]==v2[0])||(v1[i]==v2[1])||(v1[i]==v2[2]))
	ns++;
    }
  return(ns==2);
}

boolean SameTriangle(unsigned int *v1,unsigned int *v2)
{
  unsigned int i;
  boolean same;

  same=TRUE;
  for(i=0;((same)&&(i<3));i++)
    same=((v1[i]==v2[0])||(v1[i]==v2[1])||(v1[i]==v2[2]));
  return(same);
}

double BallVolume(unsigned int n,double r)
{
  unsigned int i,s;
  double v;

  if ((n%2)==1)
    {
      // 1,3,5,...
      s=3;
      v=2*r;
    }
  else
    {
      // 0,2,4,....
      s=2;
      v=1;
    }
  /* V_n = (2*pi*R^2/n) * V_{n-2} */
  for(i=s;i<=n;i+=2)
    v*=(2.0*M_PI*r*r/(double)i);

  return(v);
}

void FirstCombination(unsigned int n,unsigned int m,unsigned int *cb)
{
  unsigned int i;
  
  for(i=0;i<n;i++)
    cb[i]=0;
}

boolean NextCombination(unsigned int n,unsigned int m,unsigned int *cb)
{
  unsigned int i;
  boolean end;
  
  end=FALSE;
  for(i=0;((!end)&&(i<n));i++)
    {
      if (cb[i]<m)
	{
	  cb[i]++;
	  end=TRUE;
	}
      else
	cb[i]=0;
    }

  return(end);
}

double Det2x2(double *c1,double *c2)
{
  return((c1[0]*c2[1])-(c1[1]*c2[0]));
}

double Det3x3(double *c1,double *c2,double *c3)
{
  return((c1[0]*c2[1]*c3[2]+c1[2]*c2[3]*c3[1]+c2[1]*c3[2]*c1[3])-
	 (c1[2]*c2[1]*c3[0]+c1[1]*c2[0]*c3[3]+c1[0]*c2[3]*c3[1]));
}

void PrintReal(FILE *f,double r)
{
  if (fabs(r)<ZERO)
    fprintf(f,"0");
  else
    {
      if (fabs(1-r)<ZERO)
	fprintf(f,"1");
      else
	{
	  if (fabs(-1-r)<ZERO)
	    fprintf(f,"-1");
	  else
	    fprintf(f,"%.16f",r);
	}
    }
}

void Print3Reals(FILE *f,double r1,double r2,double r3)
{
  PrintReal(f,r1);
  fprintf(f,",");
  PrintReal(f,r2);
  fprintf(f,",");
  PrintReal(f,r3);
}


void PrintAngle(FILE *f,double a)
{
  if (fabs(a)<ZERO)
    fprintf(f,"0");
  else
    {
      if (fabs(M_PI-a)<ZERO)
	fprintf(f,"pi");
      else
	{
	  if (fabs(-M_PI-a)<ZERO)
	    fprintf(f,"-pi");
	  else
	    {
	      if (fabs(M_PI-a)<ZERO)
		fprintf(f,"pi/2");
	      else
		{
		  if (fabs(-M_PI-a)<ZERO)
		    fprintf(f,"-pi/2");
		  else
		    fprintf(f,"%.16f",a);
		}
	    }
	}
    }
}
