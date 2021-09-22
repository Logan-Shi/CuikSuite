#include "chart.h"

#include "defines.h"
#include "error.h"
#include "random.h"
#include "algebra.h"
#include "samples.h"

#include <string.h>
#include <math.h>

/** 
   \file chart.c
   \brief Implementation of a local chart on a manifold.

   Implementation of a local chart on a point on a manifold.

   This basically follows the implementation of Dr. Henderson
   for MultiFario but adapted to our requirements.

   \sa Tchart,chart.h
*/

/** 
   \brief Constructor.

   Shared code between \ref InitChart and \ref InitSingularChart
   The only difference is that the second does not check if the given point
   is singular (and generates some structures to link the singular chart with
   other chart, at a bifurcation).

   \param trusted TRUE if the given point is for sure on the manifold and collision
                  free. This is so during the AtlasRRT construction.
   \param singular TRUE if we expect the point to be singular. In this case, the chart
                   is created even if the point is singular, i.e., when the return
		   values are 0 or 1. If singular is FALSE, the chart is only
		   created if the return code is 0. Otherwise no memory is actually
		   allocated (and, thus, no memory need to be realesed).
   \param forceRS If TRUE raises an error if a point is singular and is not expected
                  to be so (i.e. singular==FALSE). If singular is TRUE we just enforce
		  the chart to be singular even if it is not detected as so due to
		  numerical issues.
   \param pr The set of parameters.
   \param simple TRUE if we want to use a simple polytope.
   \param domain The box defining the domain over which the manifold is defined (or
                 of interest).
   \param tp Topology for each variable.
   \param m The dimension of the ambient space.
   \param k The dimension of the manifold
   \param p A point on the manifold.
   \param e Naximum distance respect to the manifold.
   \param eCurv Maximum curvature error respecto to the manifold.
   \param r The radius of validity of the local parametrization.
   \param T The tangent space. Only provided for some charts defined
            at a bifurcation. When provided it is not computed.
	    If given, it implies singular=TRUE and forceRS=TRUE.
   \param sJ Symbolic Jacobian.
   \param w The world with the equations and obstacles.
   \param c The chart to create. Note that no chart is actually created if an error is
            detected. Any ouput different from 0 means that the chart is not created,
	    except when singular is TRUE where the chart is also created when the
	    return code is 1.

   \return 0 if we could actually define the chart, 1 if there the kernel is
             too large (i.e., the given point is singular), 2 if the chart could not be defined
	     since the kernel is too small at the given point, 3 if there is an error while
	     performing QR decomposition, and 4 if the error w.r.t. the manifold is
	     too large. Most of these outputs come directly from \ref AnalyzeKernel.
*/
unsigned int InitChartInt(boolean trusted,boolean singular,boolean forceRS,Tparameters *pr,boolean simple,
			  Tbox *domain,unsigned int *tp,unsigned int m,unsigned int k,double *p,double e,
			  double eCurv,double r,double *T,TJacobian *sJ,TAtlasBase *w,Tchart *c);

/** 
   \brief Computes the kernel of the Jacobian and, optionally its basis.

   Computes the Jacobian kernel. For wide matrices (matrices with more columns
   than rows, it also computes the Jacobian basis. This function initializes
   the T field of charts  and, optionally, the BJ field too.

   For wide matrices we use QR and for tall matrices we use SVD.

   This is an auxiliary function of \ref InitChart. To have a separate function
   is more inefficient but we defined it just to keep the code understandable.

   \param epsilon Numerical accuracy.
   \param sJ Symbolic Jacobian.
   \param c The chart with the point where to compute the Jacobian (and the
            parameters like the dimensionality of the kernel).

   \return 0 if there was no error when computing the kernel. 3 if there
             is a numerical error in computing the QR of the SVD decomposition,
	     2 if the kernel is larger than expected, and 1 if it is smaller
	     than expected.
*/
unsigned int ComputeJacobianKernelBasis(double epsilon,TJacobian *sJ,Tchart *c);

/** 
   \brief Add a map indentifier to the list of linked charts.

   Auxiliary function of \ref LinkCharts.

   \param id Map identifer to add to the list.
   \param c Map where to add the identifier as a linked chart.
*/
void LinkChart(unsigned int id,Tchart *c);

/** 
   \brief Intersects two local charts.

   This is a function that implements the common functionality for
   \ref CloseCharts and \ref IntersectCharts.

   \param pr The set of parameters (basically to use \ref CT_EPSILON)
   \param cut If TRUE we implement the \ref IntersectCharts behavior (we do nt
              only detect if two charts are close but we also cut their polytopes).
   \param tp The topology for each variable.
   \param ambient The ambient space.
   \param id1 Identifier of the first chart to modify. Not used if \e cut is \ref FALSE.
   \param c1 The first chart to modify.
   \param id2 Identifier of the second chart to modify. Not used if \e cut is \ref FALSE.
   \param c2 The second chart to modify.

   \return TRUE if \e c1 and \e c2 are neighbours.
*/
boolean IntersectChartsInt(Tparameters *pr,boolean cut,
			   unsigned int *tp,Tbox *ambient,
			   unsigned int id1,Tchart *c1,
			   unsigned int id2,Tchart *c2);


/** 
   \brief Plots a 3d projection of a local chart as a filled polygon.

   Plots a 3d projection of a local chart as a filled polygon.

   In only works for 2D manifolds.

   In 2D the chart area is bounded by a polygon. In \ref PlotChart we
   plot the edges defining this polygon. In this function we \e fill
   the polygon and plot it all and not only its boundaries.

   Observe that this function does not take into account the topology of the
   variables in order to avoid plotting weird charts.  When plotting on
   variables with topology \ref TOPOLOGY_S a cut is introduced at pi and
   since plots are in generated in R. Charts over pi will produce vertices
   larger/smaller than pi/-pi. The resulting plot won't be continuous.

   \param pr The set of parameters.
   \param fcost File from where to get the cost associated with this chart.
                This translates to a different color for the chart in function
		of the cost. Set to NULL if the chart is to have a uniform color.
   \param sJ Symbolic Jacobian. This is only used when ploting the edges after
             projecting them on the manifold (to check the overlap between them).
   \param xID First dimension for the projection (in the original system including
              system vars and dummies).
   \param yID Second dimension for the projection (in the original system including
              system vars and dummies).
   \param zID Third dimension for the projection (in the original system including
              system vars and dummies).
   \param p3d The 3d plot where to add the
   \param c The chart to plot.
*/
void PlotChartAsPolygon(Tparameters *pr,FILE *fcost,TJacobian *sJ,
			unsigned int xID,unsigned int yID,unsigned int zID,
			Tplot3d *p3d,Tchart *c);


/** 
   \brief Plots a 3d chart as a box.

   Plots a 3d chart as a box, i.e. the cube defining the maximum applicability
   area for the chart.

   \param pr The set of parameters.
   \param xID First dimension for the projection (in the original system including
              system vars and dummies).
   \param yID Second dimension for the projection (in the original system including
              system vars and dummies).
   \param zID Third dimension for the projection (in the original system including
              system vars and dummies).
   \param p3d The 3d plot where to add the
   \param c The chart to plot.
*/
void PlotChartAsBox(Tparameters *pr,
		    unsigned int xID,unsigned int yID,unsigned int zID,
		    Tplot3d *p3d,Tchart *c);

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

unsigned int ComputeJacobianKernelBasis(double epsilon,TJacobian *sJ,Tchart *c)
{
  unsigned int out;
  double *JT;

  NEW(JT,c->m*c->nrJ,double);
  EvaluateTransposedJacobianInVector(c->center,c->m,c->nrJ,JT,sJ);

  #if (_DEBUG>5)
    fprintf(stderr,"         Computing kernel+basis\n");
    PrintVector(stderr,"           c",c->m,c->center);
    PrintTMatrix(stderr,"           J",c->m,c->nrJ,JT);
  #endif

  out=FindKernelAndIndependentRows(c->nrJ,c->m,JT,c->k,epsilon,&(c->singular),&(c->BJ),&(c->T));

  #if (_DEBUG>5)
    PrintTMatrix(stderr,"           T",c->m,c->k,c->T); 
  #endif

  free(JT);

  return(out);
}

void LinkChart(unsigned int id,Tchart *c)
{
  if (!c->singular)
    Error("Only singular maps can be linked to other singular maps");

  if (c->nl==c->ml)
    MEM_DUP(c->l,c->ml,unsigned int);

  c->l[c->nl]=id;
  c->nl++;
}

void AddBorderConstraint(Tparameters *pr,double *t,unsigned int *tp,Tbox *ambient,Tchart *c)
{
  double nm;
  
  nm=Norm(c->k,t);
  /* To avoid numerical instabilities, do not use too small vectors. */
  //if (nm>MIN_SAMPLING_RADIUS)
  {
    if (c->simple)
      CutSPolytopeWithFace(t,nm*nm/2,NO_UINT,c->sp);
    else
      CutPolytopeWithFace(pr,t,nm*nm/2,NO_UINT,(void *)c->w,(void *)c,c->m,tp,ambient,c->p);
  }
}

void ForceChartCut(Tparameters *pr,unsigned int *tp,Tbox *ambient,
		   unsigned int id1,Tchart *c1,
		   unsigned int id2,Tchart *c2)
{
  double *t;

  NEW(t,c1->k,double);

  Manifold2Chart(c2->center,tp,t,c1);
  if (c1->simple)
    CutSPolytope(t,c2->r,id2,c1->sp);
  else
    CutPolytope(pr,t,c2->r,id2,(void *)c1->w,(void *)c1,c1->m,tp,ambient,c1->p);

  Manifold2Chart(c1->center,tp,t,c2);
  if (c2->simple)
    CutSPolytope(t,c1->r,id1,c2->sp);
  else
    CutPolytope(pr,t,c1->r,id1,(void *)c2->w,(void *)c2,c2->m,tp,ambient,c2->p);

  free(t);
}

boolean IntersectChartsInt(Tparameters *pr,boolean cut,
			   unsigned int *tp,Tbox *ambient,
			   unsigned int id1,Tchart *c1,
			   unsigned int id2,Tchart *c2)
{
  boolean neighbours;

  neighbours=FALSE;

  if ((c1->w==c2->w)&&(c1->m==c2->m)&&(c1->k==c2->k))
    {
      double d,sr;
      double *t1,*t2;
      double n1,n2;
      double e;

      d=DistanceTopology(c1->m,tp,c1->center,c2->center);

      /* At a given point we used a reduced radius for
         the ball projected in the "other" tangent space.
         We even mention this in our papers but we have
         to fix it.
	 Using a reduced radius is appealing since the
	 projection of a ball has less area/volume than
	 the original ball. However, intersecting balls
	 with different radius does not warrantee the
	 balls to intersect at all and, if they do, the
	 plane defined by the intersection does not
	 necessarity cuts out the polytope vertex used
	 to generate the new chart. This is specially true
	 when the new chart is generated very close
	 to the previous one (this occurs in high curvature
	 ares). If the vertex used to generate the new
	 chart is not removed from the polytope the algorithm
	 iterates forever selecting the same vertice and
	 generating the same new chart forever.
	 To avoid this problem we use keep the original
	 radius for the projected ball. Two balls with the
	 same radius always intersect and the resulting plane
	 always crosses the line in between the two ball
	 centers cropping one vertex from the polyedron.
      */
      sr=c1->r+c2->r;
      
      if (d<sr)
	{
	  /*center of chart1 in chart2*/
	  NEW(t1,c2->k,double);
	  n1=Manifold2Chart(c1->center,tp,t1,c2);

	  /* n1 = norm(t1) */
	  /* Points are typically selected on the ball of radius 'r'
	     and we allow for some error in the back-projection */
	  //if ((n1<1.1*c2->r)&&(n1/d>(1.0-c2->eCurv)))
	  {
	    /* compute 'e': distance from the center of c1 to c2 */
	    e=d*d-n1*n1;

	    if (e<-ZERO)
	      Error("Non-orthonormal tangent space in IntersectChartsInt (1)?");
	    if (e<ZERO) e=0.0; /* tiny neg. values are set to zero */
	    e=sqrt(e);
	    	    
	    if (e<c2->error)
	      {
		/*center of chart2 in chart1*/
		NEW(t2,c1->k,double);
		n2=Manifold2Chart(c2->center,tp,t2,c1);

		/* n2 = norm(t2) */
		//if ((n2<1.1*c1->r)&&(n2/d>(1.0-c1->eCurv)))
		{
		  /* compute 'e': distance from the center of c2 to c1 */
		  e=d*d-n2*n2;
		  if (e<-ZERO)
		    Error("Non-orthonormal tangent space in IntersectChartsInt (2)?");
		  if (e<ZERO) e=0.0; /* tiny neg. values are set to zero */
		  e=sqrt(e);
		  
		  if (e<c1->error)
		    {
		      boolean compare;

		      compare=((c1->n==0)||(CompareTangentSpaces(c1,c2)));
		      if (compare)
			{			  
			  neighbours=TRUE;
			  if (cut)
			    {
			      if (c1->simple)
				CutSPolytope(t2,c2->r,id2,c1->sp);
			      else
				CutPolytope(pr,t2,c2->r,id2,(void *)c1->w,(void *)c1,c1->m,tp,ambient,c1->p);

			      if (c2->simple)
				CutSPolytope(t1,c1->r,id1,c2->sp);
			      else
				CutPolytope(pr,t1,c1->r,id1,(void *)c2->w,(void *)c2,c2->m,tp,ambient,c2->p);
			    }
			}
		    }
		}
		free(t2);
	      }
	  }
	  free(t1);
	}
    }
  else
    Error("Intersecting non-compatible local charts");

  return(neighbours);
}


void PlotChartAsPolygon(Tparameters *pr,FILE *fcost,TJacobian *sJ,
			unsigned int xID,unsigned int yID,unsigned int zID,
			Tplot3d *p3d,Tchart *c)
{
  double cost;
  Tcolor color;

  if (c->k!=2)
    Error("PlotChartAsFace only works for 2d manifolds");

  /* Read the cost associated with the chart, if any.  */
  if (fcost!=NULL)
    {
      if (fscanf(fcost,"%lf",&cost)!=1)
	Error("No enough data in the cost file");
      if (cost>0)
	CostColor(cost,1e-4,&color);
    }

  /* When plotting with a cost function the frontier charts are not plotted (?) */
  if ((fcost==NULL)||(!c->frontier))
    {
      unsigned int nv;
      double **v;
      Tcpolytope *pol;
      
      if (c->simple)
	{
	  NEW(pol,1,Tcpolytope);
	  SPolytope2Polytope(pr,c->sp,pol);
	}
      else
	pol=c->p;

      GetPolytopeVertices(c->k,&nv,&v,pol);

      if (nv>0)
	{
	  unsigned int ne;
	  unsigned int *v1;
	  unsigned int *v2;
	  unsigned int i,k;
	  double **p,*g,*o;
	  unsigned int current,n1,n2,nc;
	  boolean found;
	  boolean *visited;
	  unsigned int *fv;
	  boolean e;

	  NEW(p,nv,double *);
	  NEW(g,c->m,double);
	  NEW(visited,nv,boolean);
	  NEW(fv,nv,unsigned int); /*face vertices in order*/

	  for(i=0;i<nv;i++)
	    {
	      NEW(p[i],3,double);
	      if ((!PLOT_ON_MANIFOLD)||
		  (Chart2Manifold(pr,sJ,v[i],NULL,NULL,g,c)==INF))
		Local2Global(v[i],NULL,g,c);
	      CS_WD_REGENERATE_ORIGINAL_POINT(pr,g,&o,c->w);

	      p[i][0]=o[xID];
	      p[i][1]=o[yID];
	      p[i][2]=o[zID];

	      free(o);

	      visited[i]=FALSE;
	    }

	  //if (!ON_CUIKSYSTEM(c->w))
	  {
	    unsigned int rep;

	    rep=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
	    if (rep==REP_JOINTS)
	      {
		double ox,oy,oz;
		double cx,cy,cz;

		cx=GetParameter(CT_CUT_X,pr);
		cy=GetParameter(CT_CUT_Y,pr);
		cz=GetParameter(CT_CUT_Z,pr);

		/* If any of the points in the polygon is above the cut
		   displace the whole polygon -2pi */
		ox=0;
		oy=0;
		oz=0;
		for(i=0;i<nv;i++)
		  {
		    if ((cx<0)&&(p[i][0]<cx))
		      ox=+M_2PI;
		    if ((cx>0)&&(p[i][0]>cx))
		      ox=-M_2PI;
		    if ((cy<0)&&(p[i][1]<cy))
		      oy=+M_2PI;
		    if ((cy>0)&&(p[i][1]>cy))
		      oy=-M_2PI;
		    if ((cz<0)&&(p[i][2]<cz))
		      oz=+M_2PI;
		    if ((cz>0)&&(p[i][2]>cz))
		      oz=-M_2PI;
		  }

		for(i=0;i<nv;i++)
		  {
		    p[i][0]+=ox;
		    p[i][1]+=oy;
		    p[i][2]+=oz;
		  }
	      }
	  }

	  GetPolytopeEdges(&ne,&v1,&v2,pol);

	  /* Start the face at the first vertex*/
	  fv[0]=0;
	  current=0;
	  visited[0]=TRUE;
	  nc=1; /*number of vertices already in the face*/
	  e=FALSE; /* error in the polygon */

	  while(nc<nv)
	    {
	      /*look for a not visited neighbour*/
	      found=FALSE;
	      i=0;
	      while((!found)&&(i<ne))
		{
		  /*Extremes of the edges*/
		  n1=v1[i];
		  n2=v2[i];

		  if ((n1==current)&&(!visited[n2]))
		    {
		      found=TRUE;
		      k=n2;
		    }
		  else
		    {
		      if ((n2==current)&&(!visited[n1]))
			{
			  found=TRUE;
			  k=n1;
			}
		      else
			i++;
		    }
		}
	      if (!found)
		{
		  Warning("A vertex without neighbours!!");
		  //e=TRUE;
		}
	      visited[k]=TRUE;
	      fv[nc]=k;
	      current=k;
	      nc++;
	    }

	  if (!e)
	    {
	      if (fcost!=NULL)
		{
		  if (cost>0)
		    Plot3dObjectWithColor(nv,1,0,p,&nv,&fv,&color,p3d);
		}
	      else
		Plot3dObject(nv,1,0,p,&nv,&fv,p3d);
	    }

	  for(i=0;i<nv;i++)
	    {
	      free(v[i]);
	      free(p[i]);
	    }

	  free(p);
	  free(v);
	  free(v1);
	  free(v2);
	  free(g);
	  free(visited);
	  free(fv);
	}

      if (c->simple)
	{
	  DeletePolytope(pol);
	  free(pol);
	}
    }
}


void PlotChartAsBox(Tparameters *pr,
		    unsigned int xID,unsigned int yID,unsigned int zID,
		    Tplot3d *p3d,Tchart *c)
{
  double *o;

  if (c->k!=3)
    Error("PlotChartAsBox only works for 3d manifolds");

  CS_WD_REGENERATE_ORIGINAL_POINT(pr,c->center,&o,c->w);

  PlotBox3d(o[xID]-c->r,o[xID]+c->r,
	    o[yID]-c->r,o[yID]+c->r,
	    o[zID]-c->r,o[zID]+c->r,
	    p3d);

  free(o);
}

void InitCSWDFromFile(Tparameters *pr,char *name,TAtlasBase *wcs)
{
  FILE *f;
  Tfilename fn;

  CreateFileName(NULL,name,NULL,CUIK_EXT,&fn);
  f=fopen(GetFileFullName(&fn),"r");
  if (f)
    {
      /* The cuik file exists -> read from it */
      fclose(f);
      fprintf(stderr,"Reading cuik from                 : %s\n",GetFileFullName(&fn));

      wcs->isCS=TRUE;
      wcs->w=NULL;
      NEW(wcs->cs,1,TCuikSystem);
      InitCuikSystemFromFile(pr,GetFileFullName(&fn),wcs->cs);
    }
  else
    {
      /* The cuik file does not exits -> try to read the world one */
      wcs->isCS=FALSE;
      wcs->cs=NULL;
      NEW(wcs->w,1,Tworld);
      InitWorldFromFile(pr,FALSE,TRUE,name,wcs->w);
    }
  DeleteFileName(&fn);
}

unsigned int InitChartInt(boolean trusted,boolean singular,boolean forceRS,Tparameters *pr,boolean simple,
			  Tbox *domain,unsigned int *tp,unsigned int m,unsigned int k,double *p,double e,
			  double eCurv,double r,double *T,TJacobian *sJ,TAtlasBase *w,Tchart *c)
{
  double epsilon;
  double error;
  double sr; /* sampling radious */
  unsigned int out;
  double delta;
  unsigned int nrJ,ncJ;

  out=0; /* no problem generating the chart. */

  epsilon=GetParameter(CT_EPSILON,pr);
  delta=GetParameter(CT_DELTA,pr);
  
  sr=GetParameter(CT_SR,pr);
  if (sr==0)
    sr=(double)k;
  if (sr<r+2*delta)
    sr=r+2*delta;

  c->w=w;

  c->m=m; /* number of variables */
  c->k=k; /* dimensionality of the manifold*/
  c->da=0; /* no linearized dynamics on the chart so far */
  c->n=c->m-c->k; /* number of non-redundant equations (equalities) */

  if ((c->k==0)||(c->m==0)||(c->k>c->m))
    Error("Dimension missmatch in InitChart (2)");

  GetJacobianSize(&nrJ,&ncJ,sJ);
  if ((c->m!=ncJ)||(c->n>nrJ))
    Error("Jacobian-system missmatch in InitChart (1)");

  /* Default initialization */
  c->center=NULL;
  c->T=NULL;
  c->BJ=NULL;
  c->singular=FALSE;
  c->ml=0;
  c->nl=0;
  c->l=NULL;
  c->degree=NO_UINT; /* We defer the computation of the degree until needed */
  c->simple=simple;
  c->p=NULL;
  c->sp=NULL;

  /* Copy the center */
  NEW(c->center,c->m,double);
  memcpy(c->center,p,c->m*sizeof(double));

  /* Note that PointInBoxTopology can modify the center !! */
  if (trusted)
    {
      c->frontier=FALSE;
      if (tp!=NULL)
	ArrayPi2Pi(c->m,tp,c->center);
    }
  else
    c->frontier=((!PointInBoxTopology(NULL,TRUE,c->m,c->center,epsilon,tp,domain))||
		 (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,c->center,c->w)));

  /* Check if the (modified) center is actually on the manifold */
  if ((trusted)||(c->n==0))
    error=0.0;
  else
    error=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,c->center,c->w);

  if (error>epsilon)
    out=4; /* The map can not be defined since the given point is not in the manifold */
  else
    {
      c->error=e;
      c->eCurv=eCurv;
      c->r=r;

      if (trusted)
	c->collision=FALSE;
      else
	{ CS_WD_IN_COLLISION(c->collision,pr,c->center,NULL,c->w); }

      c->frontier=((c->frontier)||(c->collision));

      c->nrJ=nrJ;

      if (c->n>0)  /* no empty problem */
	{
	  if (T!=NULL)
	    {
	      NEW(c->T,c->m*c->k,double);
	      memcpy(c->T,T,sizeof(double)*(c->m*c->k));
	    }
	  else
	    {
	      /* Initialize c->T, c->BJ and c->singular */
	      out=ComputeJacobianKernelBasis(epsilon,sJ,c);

	      if ((!singular)&&(forceRS)&&(c->singular))
		{
		  PrintVector(stderr,"c",c->m,c->center);
		  Error("The point is not regular (and is supposed to be)");
		}
	    }
	}

      if (out<(singular?2:1)) /* If the chart could be actually created */
	{ 
	  if ((singular)||(T!=NULL))
	    {
	      /* Even if ComputeJacobianKernelBasis determines that the point
		 is not singular, we force it to be singular (we are for sure
		 close to a singularity). */
	      if ((forceRS)||(T!=NULL))
		c->singular=TRUE;

	      /* Initialize the list of related charts (at a singular point
	         we can define more than one chart (one for each branch). */
	      c->ml=1;
	      NEW(c->l,c->ml,unsigned int);
	    }

	  /* Create the polytope to expand the chart. Note that we use k1
	     (i.e., we only take into account the feasible velocity sub-space). */
	  if (c->simple)
	    {
	      NEW(c->sp,1,Tscpolytope);
	      InitEmptySPolytope(delta,c->k,r,sr,c->sp);
	    }
	  else
	    {
	      NEW(c->p,1,Tcpolytope);
	      
	      InitEmptyPolytope(c->k,r,c->p);
	    }
	}

    }
 
  /* We reset the dynamic information. If necessary, the dynamic information must
     be explicitly added using SetLinearizedDynamics */
  c->A=NULL;
  c->B=NULL;
  c->c=NULL;
  c->d=NULL;
  c->iRBt=NULL;
  c->BiRBt=NULL;

  /* If there was any error in the map definition release (possibly) used memory*/
  if (out>(singular?1:0))
    DeleteChart(c);

  /*
    0 if we could actually define the chart, 1 if there the kernel is
    too large (i.e., the given point is singular), 2 if the chart could not be defined
    since the kernel is too small at the given point, 3 if there is an error while
    performing QR decomposition, and 4 if the error w.r.t. the manifold is
    too large. Most of these outputs come directly from \ref AnalyzeKernel.
  */
  return(out);
}

unsigned int InitChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
		       unsigned int m,unsigned int k,double *p,double e,double eCurv,double r,
		       TJacobian *sJ,TAtlasBase *w,Tchart *c)
{
  /* trusted=FALSE  singular=FALSE  forceRS=TRUE (error if not regular) */
  return(InitChartInt(FALSE,FALSE,TRUE,pr,simple,domain,tp,m,k,p,e,eCurv,r,NULL,sJ,w,c));
}

unsigned int InitPossiblySingularChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
				       unsigned int m,unsigned int k,double *p,double e, double eCurv, double r,
				       TJacobian *sJ,TAtlasBase *w,Tchart *c)
{
  /* trusted=FALSE  singular=TRUE  forceRS=FALSE (no error if singular and do not force to mark it as singular) */
  return(InitChartInt(FALSE,TRUE,FALSE,pr,simple,domain,tp,m,k,p,e,eCurv,r,NULL,sJ,w,c));
}

unsigned int InitSingularChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
			       unsigned int m,unsigned int k,double *p,double e, double eCurv,double r,
			       TJacobian *sJ,TAtlasBase *w,Tchart *c)
{
  /* trusted=FALSE  singular=TRUE  forceRS=TRUE (mark as singular even if not detected as such) */
  return(InitChartInt(FALSE,TRUE,TRUE,pr,simple,domain,tp,m,k,p,e,eCurv,r,NULL,sJ,w,c));
}

unsigned int InitTrustedChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
			      unsigned int m,unsigned int k,double *p,double e, double eCurv,double r,
			      TJacobian *sJ,TAtlasBase *w,Tchart *c)
{
  /* trusted=TRUE  singular=FALSE  forceRS=TRUE  (error if not regular) */
  return(InitChartInt(TRUE,FALSE,TRUE,pr,simple,domain,tp,m,k,p,e,eCurv,r,NULL,sJ,w,c));
}

unsigned int InitChartWithTangent(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
				  unsigned int m,unsigned int k,double *p,double *T,
				  double e, double eCurv, double r,
				  TJacobian *sJ,TAtlasBase *w,Tchart *c)
{
  /* singular=FALSE  forceRS=TRUE (but forceRS plays no role since we give T) */
  return(InitChartInt(FALSE,TRUE,TRUE,pr,simple,domain,tp,m,k,p,e,eCurv,r,T,sJ,w,c));
}

void SetLinearizedDynamics(unsigned int da,double *mA,double *mB,double *vc,double *iR,Tchart *c)
{
  #if (COMPUTE_LQRPOLICY_IN_T)
    TLinearSystem ls;
  #endif
  
  if (c->k%2!=0)
    Error("Using SetLinearizedDynamics on a manifold that can not be a state space");

  c->da=da;
  c->A=mA;
  c->B=mB;
  c->c=vc;

  NEW(c->iRBt,c->da*c->k,double);
  MatrixTMatrixProduct(c->da,c->da,iR,c->k,mB,c->iRBt);

  NEW(c->BiRBt,c->k*c->k,double);
  MatrixMatrixProduct(c->k,c->da,mB,c->k,c->iRBt,c->BiRBt);
  SymmetrizeMatrix(c->k,c->BiRBt); /* To improve numerical stability */

  #if (COMPUTE_LQRPOLICY_IN_T)
    InitLS(c->k,c->k,1,&ls);
    memcpy(GetLSMatrixBuffer(&ls),mA,c->k*c->k*sizeof(double));
    memcpy(GetLSRHBuffer(&ls),vc,c->k*sizeof(double));
    if (LSSolve(&ls))
      Error("Singular A matrix in SetLinearizedDynamics");
    
    NEW(c->d,c->k,double);
    memcpy(c->d,GetLSSolutionBuffer(&ls),c->k*sizeof(double));
    
    DeleteLS(&ls);
  #else
    /* c->d will be not used but we define something just to avoid
       errors when saving the chart */
    NEWZ(c->d,c->k,double);
  #endif
  
}

void GetLinearizedDynamics(double **mA,double **mAt,double **mB,double**vc,double **vd,
			   double **iRBt,double **BiRBt,Tchart *c)
{
  *mA=c->A;
  *mB=c->B;
  *vc=c->c;
  *vd=c->d;
  *iRBt=c->iRBt;
  *BiRBt=c->BiRBt;
}

void CopyChart(Tchart *c_dst,Tchart *c_src)
{
  /* Copy chart */
  c_dst->w=c_src->w;

  c_dst->m=c_src->m;
  c_dst->k=c_src->k;
  c_dst->da=c_src->da;
  c_dst->n=c_src->n;
  c_dst->nrJ=c_src->nrJ;

  c_dst->error=c_src->error;
  c_dst->eCurv= c_src->eCurv;
  c_dst->r=c_src->r;
  c_dst->degree=c_src->degree;
  c_dst->frontier=c_src->frontier;
  c_dst->singular=c_src->singular;

  NEW(c_dst->center,c_dst->m,double);
  memcpy(c_dst->center,c_src->center,c_dst->m*sizeof(double));

  if ((c_src->n==0)||(c_src->T==NULL))
    c_dst->T=NULL;
  else
    {
      NEW(c_dst->T,c_dst->m*c_dst->k,double);
      memcpy(c_dst->T,c_src->T,sizeof(double)*(c_dst->m*c_dst->k));
    }

  /* maps defined with given tangent space don't have Jacobian basis */
  if ((c_src->nrJ==0)||(c_src->BJ==NULL)) /* c_src->singular==TRUE  */
    c_dst->BJ=NULL;
  else
    {
      NEW(c_dst->BJ,c_dst->nrJ,boolean);
      memcpy(c_dst->BJ,c_src->BJ,c_dst->nrJ*sizeof(boolean));
    }
  
  c_dst->ml=c_src->ml;
  if (c_dst->ml>0)
    {
      c_dst->nl=c_src->nl;
      NEW(c_dst->l,c_dst->ml,unsigned int);
      memcpy(c_dst->l,c_src->l,c_dst->nl*sizeof(unsigned int));
    }
  else
    {
      c_dst->nl=0;
      c_dst->l=NULL;
    }

  /* Copy Polytope */
  c_dst->simple=c_src->simple;

  if (c_src->sp!=NULL)
    {
      NEW(c_dst->sp,1,Tscpolytope);
      CopySPolytope(c_dst->sp,c_src->sp);
      c_dst->p=NULL;
    }

  if (c_src->p!=NULL)
    {
      NEW(c_dst->p,1,Tcpolytope);
      CopyPolytope(c_dst->p,c_src->p);
      c_dst->sp=NULL;
    }

  if (c_src->A==NULL)
    {
      c_dst->A=NULL;
      c_dst->B=NULL;
      c_dst->c=NULL;
      c_dst->iRBt=NULL;
      c_dst->BiRBt=NULL;
    }
  else
    {
      NEW(c_dst->A,c_dst->k*c_dst->k,double);
      memcpy(c_dst->A,c_src->A,c_dst->k*c_dst->k*sizeof(double));

      NEW(c_dst->B,c_dst->k*(c_dst->da),double);
      memcpy(c_dst->B,c_src->B,c_dst->k*(c_dst->da)*sizeof(double));

      NEW(c_dst->c,c_dst->k,double);
      memcpy(c_dst->c,c_src->c,c_dst->k*sizeof(double));
      
      NEW(c_dst->d,c_dst->k,double);
      memcpy(c_dst->d,c_src->d,c_dst->k*sizeof(double));

      NEW(c_dst->iRBt,(c_dst->da)*c_dst->k,double);
      memcpy(c_dst->iRBt,c_src->iRBt,(c_dst->da)*c_dst->k*sizeof(double));

      NEW(c_dst->BiRBt,c_dst->k*c_dst->k,double);
      memcpy(c_dst->BiRBt,c_src->BiRBt,c_dst->k*c_dst->k*sizeof(double));
    }
}

boolean CompareTangentSpaces(Tchart *c1,Tchart *c2)
{
  double d;
  double *aData;

  if (c1->w!=c2->w)
    Error("Comparing maps defined on diferent manifolds");

  /* we can assume c1->k==c2->k */

  NEW(aData,c1->k*c1->k,double);

  TMatrixMatrixProduct(c1->m,c1->k,c1->T,c2->k,c2->T,aData);

  d=fabs(MatrixDeterminant(c1->k,aData));

  free(aData);
  
  return(fabs(d-1)<=c1->eCurv);
}

double MinCosinusBetweenCharts(Tchart *c1,Tchart *c2)
{
  double mc;

  if (c1->w!=c2->w)
    Error("Comparing maps defined on diferent manifolds");

  mc=MinCosinusBetweenSubSpaces(c1->m,c1->k,c1->T,c2->T);

  return(mc);
}

TAtlasBase *GetChartWorld(Tchart *c)
{
  return(c->w);
}

double *GetChartCenter(Tchart *c)
{
  return(c->center);
}

double GetChartRadius(Tchart *c)
{
  return(c->r);
}

double GetChartSamplingRadius(Tchart *c)
{
  if (!c->simple)
    Error("GetChartSamplingRadius is only defined for simple charts");
  return(SPolytopeGetSamplingRadius(c->sp));
}

double GetChartMaxError(Tchart *c)
{
  return(c->error);
}

double GetChartMaxCurvError(Tchart *c)
{
  return(c->eCurv);
}

unsigned int GetChartAmbientDim(Tchart *c)
{
  return(c->m);
}

unsigned int GetChartManifoldDim(Tchart *c)
{
  return(c->k);
}

double *GetChartTangentSpace(Tchart *c)
{
  return(c->T);
}

boolean *GetChartJacobianBasis(Tchart *c)
{
  return(c->BJ);
}

boolean SingularChart(Tchart *c)
{
  return(c->singular);
}

unsigned int GetChartDegree(Tparameters *pr,double *T,TJacobian *sJ,
			    boolean *singular,Tchart *c)
{
  double *A;
  int sg;
  unsigned int d;

  d=0; /* default output*/

  if (c->singular)
    *singular=TRUE;
  else
    {
      if (c->BJ==NULL)
	Error("A non-singular chart without Jacobian basis?");

      *singular=FALSE;

      if ((T==c->T)&&(c->degree!=NO_UINT))
	d=c->degree;
      else
	{
	  /* Evaluate the Jacobian */
	  NEW(A,c->m*c->m,double);

	  /* We only take the c->n independent rows of the Jacobian */
	  EvaluateJacobianSubSetInVector(c->center,c->BJ,c->m,c->m,A,sJ);

	  /* The lower part of A is T' */
	  SubMatrixFromTMatrix(c->m,c->k,T,c->n,0,c->m,c->m,A);

	  #if (_DEBUG>5)
	    PrintVector(stdout,NULL,c->m,c->center);
	    PrintMatrix(stdout,NULL,c->m,c->m,A);
	  #endif

	  sg=MatrixDeterminantSgn(GetParameter(CT_EPSILON,pr),c->m,A);

	  if (sg>0) d=1;
	  else
	    {
	      if (sg<0) d=0;
	      else *singular=TRUE;
	    }

	  free(A);
	}
    }
  return(d);
}

double Manifold2Chart(double *p,unsigned int *tp,double *t,Tchart *c)
{
  if (c->n==0) /* k==m */
    
    {
      if (tp!=NULL)
	DifferenceVectorTopology(c->m,tp,p,c->center,t);
      else
	DifferenceVector(c->m,p,c->center,t);
      
      return(Norm(c->m,t));
    }
  else
    {
      double *p1;

      /* Project a point to the tangent space */
      /* t=T'*(p-center)*/
      NEW(p1,c->m,double);

      DifferenceVector(c->m,p,c->center,p1);
      if (tp!=NULL)
	ArrayPi2Pi(c->m,tp,p1);

      TMatrixVectorProduct(c->m,c->k,c->T,p1,t);

      free(p1);
      
      return(Norm(c->k,t));
    }
}



double Chart2Manifold(Tparameters *pr,TJacobian *sJ,
		      double *t,unsigned int *tp,double *pInit,
		      double *p,Tchart *c)
{
  if (c->n==0) /* k==m */
    {
      SumVector(c->m,c->center,t,p);
      if (tp!=NULL)
	ArrayPi2Pi(c->m,tp,p);
      return(0.0);
    }
  else
    {
      double d;
      double epsilon;
      unsigned int i,it,maxIterations,nr,nrJ;
      boolean converged;

      TLinearSystem ls;
      double *aData;
      double *bData;
      double *xData;
      double error;
      double *p0;
      int err;
      double *dif;

      epsilon=GetParameter(CT_EPSILON,pr);
      maxIterations=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,pr);

      if (maxIterations==0)
	Error("MAX_NEWTON_ITERATIONS must be larger than 0 to use Map2Manifold");

      /* If we already identified a basis of the Jacobian (most of the cases), we
         can use these rows only. This produces a smaller system without changing
         the solution. If actually produces a squared sytem which are solved faster
         (non-squared systems are solved via less-squares which is slower). */
      if (c->BJ==NULL)
	nrJ=c->nrJ;
      else
	nrJ=c->n; /* squared system */
      nr=nrJ+c->k;

      /* Initializes the structure to solve linear systems */
      InitLS(nr,c->m,1,&ls);

      /* direct acces to the LS structures */
      aData=GetLSMatrixBuffer(&ls);
      bData=GetLSRHBuffer(&ls);
      xData=GetLSSolutionBuffer(&ls);

      /* Point on the tangent space corresponding to the given paremeters 't' */
      NEW(p0,c->m,double);
      Local2Global(t,tp,p0,c);

      /* If the user provides an initial estimation for the output use it
	 (otherwise we will depart from the tangent space estimation. */
      if (pInit!=NULL)
	{
	  /* pInit can be pi2pi-ed and this can cause a large error in
	     the intial estimation when there is not such error.
	     This is why we have to use DifferenceVectorTopology inside
	     the loop. */
	  if (p!=pInit)
	    memcpy(p,pInit,sizeof(double)*c->m);
	}
      else
	memcpy(p,p0,sizeof(double)*c->m);

      /* Space for the difference between current point (p) and p0
	 taking into account topology */
      NEW(dif,c->m,double);

      /* Iterate from this point to a point on the manifold */
      it=0;
      converged=FALSE;
      err=0;
      while((!converged)&&(it<maxIterations))
	{
	  /* Define the residual (right-had side of the system) */
	  if (c->BJ==NULL)
	    { CS_WD_EVALUATE_SIMP_EQUATIONS(pr,p,bData,c->w); }
	  else
	    { CS_WD_EVALUATE_SUBSET_SIMP_EQUATIONS(pr,c->BJ,p,bData,c->w); }

	  /* Complete the the right-hand side of the system of equations */
	  DifferenceVectorTopology(c->m,tp,p,p0,dif);
	  TMatrixVectorProduct(c->m,c->k,c->T,dif,&(bData[nrJ]));

	  error=Norm(nr,bData);

	  if (error<epsilon)
	    //if ((it>0)&&(error<epsilon))
	    converged=TRUE;
	  else
	    {
	      /* To avoid overflows we assume that convergence
		 is impossible with too large errors */
	      if (error>1e10)
		it=maxIterations;
	      else
		{
		  /* Fill in the part of the 'A' corresponding to the Jacobian */
		  if (c->BJ==NULL)
		    EvaluateJacobianInVector(p,nr,c->m,aData,sJ);
		  else
		    EvaluateJacobianSubSetInVector(p,c->BJ,nr,c->m,aData,sJ);

		  /* Now the part of the 'A' matrix corresponding to the tangent
		     space (transposed) */
		  SubMatrixFromTMatrix(c->m,c->k,c->T,nrJ,0,nr,c->m,aData);

		  /* Once A and b are defined, solve the system */
		  err=LSSolve(&ls);

		  /* Update the estimate */
		  if (err)
		    it=maxIterations;
		  else
		    {
		      for(i=0;i<c->m;i++)
			{
			  p[i]-=xData[i];
			  if ((tp!=NULL)&&(tp[i]==TOPOLOGY_S))
			    PI2PI(p[i]);
			}
		      it++;
		    }
		}
	    }
	}

      free(dif);
      DeleteLS(&ls);

      if (it<maxIterations)
	d=DistanceTopology(c->m,tp,p,p0);
      else
	d=INF;
      free(p0);

      return(d);
    }
}

void Local2Global(double *t,unsigned int *tp,double *p,Tchart *c)
{
  if (c->n==0) /* k==m */
    {
      /*p=center+t*/
      SumVector(c->m,c->center,t,p);
    }
  else
    {
      /*p=center+T*t*/
      MatrixVectorProduct(c->m,c->k,c->T,t,p);
      AccumulateVector(c->m,c->center,p);
    }
  if (tp!=NULL)
    ArrayPi2Pi(c->m,tp,p);
}

double ChartErrorFromParameters(double *t,double *p,unsigned int *tp,
				Tchart *c)
{
  if (c->n==0)
    return(0.0);
  else
    {
      double *p2,e;

      NEW(p2,c->m,double);
      Local2Global(t,tp,p2,c);
      e=DistanceTopology(c->m,tp,p,p2);
      free(p2);

      return(e);
    }
}

double Error2Chart(double *p,unsigned int *tp,Tchart *c)
{
  if (c->n==0)
    return(0.0);
  else
    {
      double *t,e;

      NEW(t,c->k,double);
      Manifold2Chart(p,tp,t,c);
      e=ChartErrorFromParameters(t,p,tp,c);
      free(t);

      return(e);
    }
}

inline boolean CloseCharts(Tparameters *pr,unsigned int *tp,
			   Tchart *c1,Tchart *c2)
{
  return(IntersectChartsInt(pr,FALSE,tp,NULL,NO_UINT,c1,NO_UINT,c2));
}

boolean IntersectCharts(Tparameters *pr,unsigned int *tp,Tbox *ambient,
			unsigned int id1,Tchart *c1,
			unsigned int id2,Tchart *c2)
{
  return(IntersectChartsInt(pr,TRUE,tp,ambient,id1,c1,id2,c2));
}

inline boolean CollisionChart(Tchart *c)
{
  return(c->collision);
}

inline boolean FrontierChart(Tchart *c)
{
  return(c->frontier);
}

inline void ChartIsFrontier(Tchart *c)
{
  c->frontier=TRUE;
}

inline boolean ExpandibleChart(Tchart *c)
{
  if (c->simple)
    Error("ExpandibleChart is undefined for simple charts");

  return((!c->frontier)&&(ExpandiblePolytope(c->p)));
}

inline boolean OpenChart(Tchart *c)
{
  return((c->simple)||(ExpandiblePolytope(c->p)));
}

void WrongCorner(unsigned int nv,Tchart *c)
{
  if (c->simple)
    Error("WrongCorner is undefined for simple charts");

  WrongPolytopeCorner(nv,c->p);
}

boolean InsideChartPolytope(double *t,Tchart *c)
{
  if (c->simple)
    return(InsideSPolytope(t,c->sp));
  else
    return(InsidePolytope(t,c->p));
}

unsigned int DetermineChartNeighbour(double epsilon,double *t,Tchart *c)
{
  if (c->simple)
    return(DetermineSPolytopeNeighbour(epsilon,t,c->sp));
  else
    {
      Error("DetermineChartNeighbour is only defined for simple charts");
      return(NO_UINT);
    }
}

void EnlargeChart(double *t,Tchart *c)
{
  if (c->simple)
    EnlargeSPolytope(t,c->sp);
  else
    Error("EnlargeChart is only defined for simple charts");
}

boolean BoundaryPointFromExternalCorner(boolean rand,unsigned int *nv,double *t,Tchart *c)
{
  boolean ok;

  if (c->simple)
    Error("BoundaryPointFromExternalCorner is undefined for simple charts");

  ok=PolytopeBoundaryPointFromExternalCorner(c->r,rand,nv,t,c->p);

  return(ok);
}

void BoundaryPointsFromExternalCorners(unsigned int *n,unsigned int **nv,double ***t,Tchart *c)
{
  if (c->simple)
    Error("BoundaryPointsFromExternalCorners is undefined for simple charts");

  PolytopeBoundaryPointsFromExternalCorners(c->r,n,nv,t,c->p);
}

boolean RandomPointOnBoundary(double *t,Tchart *c)
{
  boolean ok;

  if (c->simple)
    ok=SPolytopeRandomPointOnBoundary(c->r,t,c->sp);
  else
    ok=PolytopeRandomPointOnBoundary(c->r,t,c->p);

  return(ok);
}

boolean RandomPointInChart(Tparameters *pr,double scale,unsigned int *tp,double *t,double *p,Tchart *c)
{
  boolean canSample;

  if (c->simple)
    canSample=RandomPointInSPolytope(scale,t,c->sp);
  else
    canSample=RandomPointInPolytope(t,c->p);

  if (canSample)
    Local2Global(t,tp,p,c);

  return(canSample);
}

void IncreaseChartSamplingRadius(Tchart *c)
{
  if (c->simple)
    SPolytopeIncreaseSamplingRadius(c->sp);
}

void DecreaseChartSamplingRadius(Tchart *c)
{
  if (c->simple)
    SPolytopeDecreaseSamplingRadius(c->sp);
}

double ChartMaxVolume(Tchart *c)
{
  double v;

  /* use the cached volume stored in the charts. This
     significantly speeds up the query if we ask for the
     volume of a chart many times */
  if (c->simple)
    v=SPolytopeVolume(c->sp);
  else
    v=PolytopeVolume(c->p);

  return(v);
}

double ChartVolume(Tparameters *pr,boolean collisionFree,
		   unsigned int *tp,TJacobian *sJ,Tchart *c)
{
  double v;

  if (!collisionFree)
    v=ChartMaxVolume(c);
  else
    {
      double *t,*s;
      unsigned int i,n,in;
      boolean valid,inCollision;

      /* If collisions must be taken into account, we have to replicate
         the rejection sampling implemented in Polytope and SPolytope
	 but including rejection due to obstacles */

      NEW(t,c->k,double);
      NEW(s,c->m,double);

      n=(unsigned int)floor(pow(10,c->k));
      if (n>10000) n=10000;
      in=0;
      for(i=0;i<n;i++)
	{
	  if (c->simple)
	    valid=RandomPointInSPolytope(1.0,t,c->sp);
	  else
	    valid=RandomPointInPolytope(t,c->p);
	  if (valid)
	    {
	      if (Chart2Manifold(pr,sJ,t,tp,NULL,s,c)<INF)
		{
		  CS_WD_IN_COLLISION(inCollision,pr,s,NULL,c->w);
		  if (!inCollision)
		    in++;
		}
	    }
	}
      free(t);
      free(s);

      if (c->simple)
	v=SPolytopeMaxVolume(c->sp);
      else
	v=PolytopeMaxVolume(c->p);

      v*=((double)in/(double)n);
    }
  return(v);
}

boolean FocusedPointOnBoundary(double *p,unsigned int *tp,
			       double *t,Tchart *c)
{
  if (c->simple)
    Error("FocusedPointOnBoundary is undefined for simple charts");

  if (ExpandibleChart(c))
    {
      double nm;

      /* 't' is 'p' in tangent */
      nm=Manifold2Chart(p,tp,t,c);

      /* find out the intersection of the ellipsoid and the line passing by the origin and 't' */
      /* This is a quadratic equation with 
            a=t^T *W *t
            b=0
            c=-r^2
         whose solution is l=sqrt(-c)/sqrt(a)
	 Observe that Manifold2Chart already returns the sqrt(a) and that sqrt(-c)=r.
	 Thus the solution is trivially c->r/nm
      */
    
      /* and scale the vector with the solution of the quadratic equation */
      ScaleVector(c->r/nm,c->k,t);

      return(InsidePolytope(t,c->p));
    }
  else
    return(FALSE);
}

boolean PathInChart(Tparameters *pr,double *t,unsigned int *tp,TJacobian *sJ,
		    unsigned int nvs,boolean *systemVars,
		    unsigned int *ms,
		    double *pl,unsigned int *ns,double ***path,
		    Tchart *c)
{
  double *nt,*p,*pPrev;
  double delta,n;
  boolean projectionOk,collision,reached,close;
  unsigned int step,nv;
  double *o,*oPrev;

  delta=GetParameter(CT_DELTA,pr);

  NEW(p,c->m,double);
  NEW(pPrev,c->m,double);
  NEW(nt,c->k,double);

  /* We move from the center of the chart toward 't' */
  step=0; /* start at 0 to add the center */
  projectionOk=TRUE;
  collision=FALSE;
  n=Norm(c->k,t);
  reached=(n<delta);
  close=FALSE;

  /* depart from the center */
  memcpy(pPrev,c->center,c->m*sizeof(double));
  nv=CS_WD_REGENERATE_ORIGINAL_POINT(pr,pPrev,&oPrev,c->w);

  while((projectionOk)&&(!reached))
    {
      memcpy(nt,t,c->k*sizeof(double));

      /* If in the last step we where close to 't' just use
         it as a new set of parameters. Otherwise approach it */
      if (close)
	reached=TRUE;
      else
	ScaleVector(((double)step)*delta/n,c->k,nt);

      projectionOk=(Chart2Manifold(pr,sJ,nt,tp,pPrev,p,c)<=c->error);

      if (projectionOk)
	{
	  (*pl)+=DistanceTopology(c->m,tp,pPrev,p);

	  nv=CS_WD_REGENERATE_ORIGINAL_POINT(pr,p,&o,c->w);
	  AddSample2Samples(nv,o,nvs,systemVars,ms,ns,path);

	  collision=((collision)||(CS_WD_ORIGINAL_IN_COLLISION(pr,o,oPrev,c->w)));

	  memcpy(oPrev,o,nv*sizeof(double));
	  free(o);

	  memcpy(pPrev,p,c->m*sizeof(double));
	  close=(Distance(c->k,nt,t)<delta);
	}

      step++;
    }
  free(p);
  free(pPrev);
  free(nt);
  free(oPrev);

  return(!collision);
}

double DistanceOnChart(Tparameters *pr,double *t,unsigned int *tp,TJacobian *sJ,
		       Tchart *c)
{
  double *nt,*p,*pPrev;
  double delta,n,d;
  boolean projectionOk,inCollision,reached;
  unsigned int step;

  delta=GetParameter(CT_DELTA,pr);

  NEW(p,c->m,double);
  NEW(pPrev,c->m,double);
  NEW(nt,c->k,double);

  /* We move from the center of the chart toward 't' */
  step=1;
  projectionOk=TRUE;
  inCollision=FALSE;
  n=Norm(c->k,t);
  reached=(n<delta);
  d=0.0;
  memcpy(pPrev,c->center,c->m*sizeof(double));

  while((projectionOk)&&(!inCollision)&&(!reached)&&(d<INF))
    {
      memcpy(nt,t,c->k*sizeof(double));
      ScaleVector(((double)step)*delta/n,c->k,nt);

      projectionOk=(Chart2Manifold(pr,sJ,nt,tp,pPrev,p,c)<=c->error);

      if (projectionOk)
	{
	  CS_WD_IN_COLLISION(inCollision,pr,p,pPrev,c->w);

	  if (!inCollision)
	    {
	      d+=DistanceTopology(c->m,tp,pPrev,p);
	      memcpy(pPrev,p,c->m*sizeof(double));
	      reached=(Distance(c->k,nt,t)<delta);
	    }
	  else
	    d=INF;
	}
      else
	d=INF;

      step++;
    }

  free(p);
  free(pPrev);
  free(nt);

  return(d);
}

boolean PointOnChart(Tparameters *pr,TJacobian *sJ,
		     double *p,unsigned int *tp,
		     double *t,Tchart *c)
{
  boolean inside;

  inside=FALSE;

  if ((Manifold2Chart(p,tp,t,c)<c->r)&&
      (InsideChartPolytope(t,c)))
    {
      double eps;
      double *p1;

      eps=GetParameter(CT_EPSILON,pr);

      NEW(p1,c->m,double);

      inside=((Chart2Manifold(pr,sJ,t,tp,NULL,p1,c)<c->error)&&
	      (DistanceTopology(c->m,tp,p1,p)<eps));

      free(p1);
    }

  return(inside);
}

unsigned int ClassifyPointInChart(Tparameters *pr,boolean error,TJacobian *sJ,
				  double *p,unsigned int *tp,
				  double *t,Tchart *c)
{
  double eps;
  double *p1;
  unsigned int cs;

  eps=GetParameter(CT_EPSILON,pr);
  NEW(p1,c->m,double);

  if (Manifold2Chart(p,tp,t,c)>c->r)
    {
      /* out of the ball */
      if (InsideChartPolytope(t,c)) /* but still inside the polytope */
	cs=1; /* In the chart scope but out of the ball */
      else
	cs=4; /* Completely out of the scope of the chart */
    }
  else
    {
      /* In the ball */
      if (InsideChartPolytope(t,c))
	{
	  if ((error)&&((Chart2Manifold(pr,sJ,t,tp,NULL,p1,c)>c->error)||
			(DistanceTopology(c->m,tp,p1,p)>eps)))
	    cs=3; /* Out of the scope due to lack of convergence or large error */
	  else
	    cs=0; /* In inside the scope of this chart */
	}
      else
	cs=2; /* Was inside the scope of this chart but is in a neighbouring chart now */
    }

  free(p1);

  return(cs);
}

void LinkCharts(unsigned int id1,Tchart *c1,unsigned int id2,Tchart *c2)
{
  LinkChart(id1,c2);
  LinkChart(id2,c1);
}

unsigned int ChartNumNeighbours(Tchart *c)
{
  unsigned int n;

  if (c->simple)
    n=SPolytopeNumNeighbours(c->sp);
  else
    n=PolytopeNumNeighbours(c->p);

  return(c->nl+n);
}

unsigned int ChartNeighbourID(unsigned int n,Tchart *c)
{
  unsigned int id;

  if (n<c->nl)
    id=c->l[n];
  else
    {
      if (c->simple)
	id=SPolytopeNeighbourID(n-c->nl,c->sp);
      else
	id=PolytopeNeighbourID(n-c->nl,c->p);
    }

  return(id);
}

void GetChartNeighboursFromVertices(Tparameters *pr,
				    unsigned int *nn,unsigned int **cID1,unsigned int **cID2,Tchart *c)
{
  Tcpolytope *p;

  if (c->simple)
    {
      NEW(p,1,Tcpolytope);
      SPolytope2Polytope(pr,c->sp,p);
    }
  else
    p=c->p;

  GetPolytopeNeighboursFromVertices(nn,cID1,cID2,p);

  if (c->simple)
    {
      DeletePolytope(p);
      free(p);
    }
}

void PlotChart(Tparameters *pr,FILE *fcost,TJacobian *sJ,
	       unsigned int xID,unsigned int yID,unsigned int zID,
	       Tplot3d *p3d,Tchart *c)
{
  if (c->k>3)
    Error("PlotChart only works for 2/3d manifolds");

  if ((PLOT_AS_POLYGONS)&&((c->k==2)||(c->k==3)))
    {
      if (c->k==2)
	PlotChartAsPolygon(pr,fcost,sJ,xID,yID,zID,p3d,c);
      else
	PlotChartAsBox(pr,xID,yID,zID,p3d,c);
    }
  else
    {
      unsigned int nv;
      double **v;
      Tcpolytope *p;

      if (c->simple)
	{
	  NEW(p,1,Tcpolytope);
	  SPolytope2Polytope(pr,c->sp,p);
	}
      else
	p=c->p;

      GetPolytopeVertices(c->k,&nv,&v,p);

      if (nv>0)
	{
	  unsigned int i,k,n1,n2;
	  unsigned int ne;
	  unsigned int *v1;
	  unsigned int *v2;
	  double *x,*y,*z;
	  double *g,*o;
	  double ox,oy,oz;
	  double cx,cy,cz;

	  /* Collect the edges of the polytope bounding the chart (local coordinates) */
	  GetPolytopeEdges(&ne,&v1,&v2,p);

	  /* Transform the polytope edges from local to gobal */

	  NEW(g,c->m,double); /* space for the points in global */

	  NEW(x,2*ne,double); /* space for the vertices in global */
	  NEW(y,2*ne,double);
	  NEW(z,2*ne,double);

	  for(i=0,k=0;i<ne;i++,k+=2)
	    {
	      /*Extremes of the edges*/
	      n1=v1[i];
	      n2=v2[i];

	      if ((!PLOT_ON_MANIFOLD)||
		  (Chart2Manifold(pr,sJ,v[n1],NULL,NULL,g,c)==INF))
		Local2Global(v[n1],NULL,g,c);
	      CS_WD_REGENERATE_ORIGINAL_POINT(pr,g,&o,c->w);
	      x[k]=o[xID];
	      y[k]=o[yID];
	      z[k]=o[zID];
	      free(o);

	      if ((!PLOT_ON_MANIFOLD)||
		  (Chart2Manifold(pr,sJ,v[n2],NULL,NULL,g,c)==INF))
		Local2Global(v[n2],NULL,g,c);
	      CS_WD_REGENERATE_ORIGINAL_POINT(pr,g,&o,c->w);
	      x[k+1]=o[xID];
	      y[k+1]=o[yID];
	      z[k+1]=o[zID];
	      free(o);
	    }

	  /* If any of the vertices is out of the box in global coordiantes
	     offset the whole polygon */
	  cx=GetParameter(CT_CUT_X,pr);
	  cy=GetParameter(CT_CUT_Y,pr);
	  cz=GetParameter(CT_CUT_Z,pr);

	  ox=0;
	  oy=0;
	  oz=0;

	  for(k=0;k<2*ne;k++)
	    {
	      if ((cx<0)&&(x[k]<cx))
		ox=+M_2PI;
	      if ((cx>0)&&(x[k]>cx))
		ox=-M_2PI;
	      if ((cy<0)&&(y[k]<cy))
		oy=+M_2PI;
	      if ((cy>0)&&(y[k]>cy))
		oy=-M_2PI;
	      if ((cz<0)&&(z[k]<cz))
		oz=+M_2PI;
	      if ((cz>0)&&(z[k]>cz))
		oz=-M_2PI;
	    }

	  /* Apply the offset if any */
	  for(k=0;k<2*ne;k++)
	    {
	      x[k]+=ox;
	      y[k]+=oy;
	      z[k]+=oz;
	    }

	  /* Plot the edges defining the polygon (possibly with offset) */
	  for(k=0;k<2*ne;k+=2)
	    PlotVect3d(2,&(x[k]),&(y[k]),&(z[k]),p3d);

	  /* Release allocated space */
	  free(g);

	  free(x);
	  free(y);
	  free(z);

	  for(i=0;i<nv;i++)
	    free(v[i]);
	  free(v);
	  free(v1);
	  free(v2);
	}
      if (c->simple)
	{
	  DeletePolytope(p);
	  free(p);
	}
    }
}

unsigned int ChartMemSize(Tchart *c)
{
  unsigned int b;

  b=sizeof(double)*c->m; /* center */
  b+=sizeof(double)*(c->m*c->k); /* T */

  if (c->simple)
    b+=SPolytopeMemSize(c->sp);
  else
    b+=PolytopeMemSize(c->p);

  return(b);
}

void SaveChart(FILE *f,Tchart *c)
{
  unsigned int i;

  /* Save map */
  fprintf(f,"%u\n",c->m);
  fprintf(f,"%u\n",c->k);
  fprintf(f,"%u\n",c->da);
  fprintf(f,"%u\n",c->n);
  fprintf(f,"%u\n",c->nrJ);

  fprintf(f,"%f\n",c->error);
  fprintf(f,"%f\n",c->eCurv);
  fprintf(f,"%f\n0\n",c->r); /* the 0 is for rSample (back-compatibility) */
  fprintf(f,"%u\n",c->degree);
  fprintf(f,"%u\n",c->frontier);
  fprintf(f,"%u\n",c->singular);

  for(i=0;i<c->m;i++)
    fprintf(f,"%.16f ",c->center[i]);
  fprintf(f,"\n");

  if (c->n>0)
    {
      for(i=0;i<c->m*c->k;i++)
	fprintf(f,"%.16f ",c->T[i]);
      fprintf(f,"\n");

      if (c->BJ==NULL)
	fprintf(f,"0\n");
      else
	{
	  fprintf(f,"1\n");
	  for(i=0;i<c->nrJ;i++)
	    fprintf(f,"%u ",c->BJ[i]);
	  fprintf(f,"\n");
	}
    }
  
  fprintf(f,"%u\n",c->ml);
  if (c->ml>0)
    {
      fprintf(f,"%u\n",c->nl);
      for(i=0;i<c->nl;i++)
	fprintf(f,"%u ",c->l[i]);
      fprintf(f,"\n");
    }

  /* Save polytope */
  fprintf(f,"%u\n",c->simple);
  if (c->simple)
    SaveSPolytope(f,c->sp);
  else
    SavePolytope(f,c->p);

  if (c->A==NULL)
    fprintf(f,"0\n");
  else
    {
      fprintf(f,"1\n");

      for(i=0;i<c->k*c->k;i++)
	fprintf(f,"%.16f ",c->A[i]);
      fprintf(f,"\n");

      for(i=0;i<c->k*c->da;i++)
	fprintf(f,"%.16f ",c->B[i]);
      fprintf(f,"\n");

      for(i=0;i<c->k;i++)
	fprintf(f,"%.16f ",c->c[i]);
      fprintf(f,"\n");

      for(i=0;i<c->k;i++)
	fprintf(f,"%.16f ",c->d[i]);
      fprintf(f,"\n");
      
      for(i=0;i<c->da*c->k;i++)
	fprintf(f,"%.16f ",c->iRBt[i]);
      fprintf(f,"\n");

      for(i=0;i<c->k*c->k;i++)
	fprintf(f,"%.16f ",c->BiRBt[i]);
      fprintf(f,"\n");
    }
}

void LoadChart(FILE *f,TAtlasBase *w,Tchart *c)
{
  unsigned int i,flag;
  double rSample;

  /* Load map */
  c->w=w;

  fscanf(f,"%u",&(c->m));
  fscanf(f,"%u",&(c->k));
  fscanf(f,"%u",&(c->da));
  fscanf(f,"%u",&(c->n));
  fscanf(f,"%u",&(c->nrJ));

  fscanf(f,"%lf",&(c->error));
  fscanf(f,"%lf",&(c->eCurv));
  fscanf(f,"%lf",&(c->r));
  fscanf(f,"%lf",&rSample); /*for back-compatibility*/
  fscanf(f,"%u",&(c->degree));
  fscanf(f,"%u",&(c->frontier));
  fscanf(f,"%u",&(c->singular));

  NEW(c->center,c->m,double);
  for(i=0;i<c->m;i++)
    fscanf(f,"%lf",&(c->center[i]));

  if (c->n==0)
    {
      c->T=NULL;
      c->BJ=NULL;
    }
  else
    {
      NEW(c->T,c->m*c->k,double);
      for(i=0;i<c->m*c->k;i++)
	fscanf(f,"%lf",&(c->T[i]));

      /* Do not load the Jacobian Basis. We keep the
	 read code for back-compatibility. */
      fscanf(f,"%u",&flag);
      if (flag)
	{
	  NEW(c->BJ,c->nrJ,boolean);
	  for(i=0;i<c->nrJ;i++)
	    fscanf(f,"%u",&(c->BJ[i]));
	}
      else
	c->BJ=NULL;
    }
  
  fscanf(f,"%u",&(c->ml));
  
  if (c->ml>0)
    {
      NEW(c->l,c->ml,unsigned int);
      fscanf(f,"%u",&(c->nl));
      for(i=0;i<c->nl;i++)
	fscanf(f,"%u",&(c->l[i]));
    }
  else
    {
      c->nl=0;
      c->l=NULL;
    }

  /* Load Polytope */
  fscanf(f,"%u\n",&(c->simple));
  if (c->simple)
    {
      NEW(c->sp,1,Tscpolytope);
      LoadSPolytope(f,c->sp);
      c->p=NULL;
    }
  else
    {
      NEW(c->p,1,Tcpolytope);
      LoadPolytope(f,c->p);
      c->sp=NULL;
    }

  fscanf(f,"%u",&(flag));
  if (flag==0)
    {
      c->A=NULL;
      c->B=NULL;
      c->c=NULL;
      c->d=NULL;
      c->iRBt=NULL;
      c->BiRBt=NULL;
    }
  else
    {
      NEW(c->A,c->k*c->k,double);
      for(i=0;i<c->k*c->k;i++)
	fscanf(f,"%lf",&(c->A[i]));
      
      NEW(c->B,c->k*c->da,double);
      for(i=0;i<c->k*c->da;i++)
	fscanf(f,"%lf",&(c->B[i]));
      
      NEW(c->c,c->k,double);
      for(i=0;i<c->k;i++)
	fscanf(f,"%lf",&(c->c[i]));
      
      NEW(c->d,c->k,double);
      for(i=0;i<c->k;i++)
	fscanf(f,"%lf",&(c->d[i]));
      
      NEW(c->iRBt,c->da*c->k,double);
      for(i=0;i<c->da*c->k;i++)
	fscanf(f,"%lf",&(c->iRBt[i]));

      NEW(c->BiRBt,c->k*c->k,double);
      for(i=0;i<c->k*c->k;i++)
	fscanf(f,"%lf",&(c->BiRBt[i]));
    }
}

void PrintChartDefines(FILE *f)
{
  fprintf(f,"\n   %% Chart defines\n");
  fprintf(f,"   COMPUTE_LQRPOLICY_IN_T %u\n",COMPUTE_LQRPOLICY_IN_T);
  fprintf(f,"   PLOT_ON_MANIFOLD %u\n",PLOT_ON_MANIFOLD);
  fprintf(f,"   PLOT_AS_POLYGONS %u\n",PLOT_AS_POLYGONS);
  fprintf(f,"   MIN_SAMPLING_RADIUS %.4f\n",MIN_SAMPLING_RADIUS);
  fprintf(f,"   HALF_PLANES %u\n",HALF_PLANES); // This is defined in scpolitope.h
  fprintf(f,"   RANDOM_HALF_PLANES %u\n",RANDOM_HALF_PLANES); // This is defined in scpolitope.h
}

void DeleteChart(Tchart *c)
{
  /* Delete map center */
  if (c->center!=NULL)
    free(c->center);

  /* Delete tangent space */
  if (c->T!=NULL)
    free(c->T);

  /* Delete Jacobian basis */
  if (c->BJ!=NULL)
    free(c->BJ);
    
  /* Delete the list of linked charts */
  if (c->l!=NULL)
    free(c->l);

  /* Delete Polytope */
  if (c->p!=NULL)
    {
      DeletePolytope(c->p);
      free(c->p);
    }
  if (c->sp!=NULL)
    {
      DeleteSPolytope(c->sp);
      free(c->sp);
    }
  if (c->A!=NULL)
    {
      free(c->A);
      free(c->B);
      free(c->c);
      free(c->d);
      free(c->iRBt);
      free(c->BiRBt);
    }
}
