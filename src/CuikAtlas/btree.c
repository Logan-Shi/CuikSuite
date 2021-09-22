#include "btree.h"

#include "algebra.h"

#include <string.h>

/** 
   \file btree.c
   \brief Implementation binary tree of charts.

   Implements a binary tree to speed up the search for neighouring 
   charts in the atlas.

   Right now it offers an interface to the kdtree by Yershova and Lavalle.

   \sa btree.h,Tbtree,Tatlas,atlas.c
*/

void InitBTree(unsigned int id,Tchart *mp,Tbox *ambient,unsigned int *topology,TBTree *t)
{
  double *weight;
  Tinterval *range;
  
  t->m=GetChartAmbientDim(mp);

  if (t->m!=GetBoxNIntervals(ambient))
     Error("Size missmatch in InitBTree");

  if (topology==NULL)
    t->tp=NULL;
  else
    {
      NEW(t->tp,t->m,unsigned int);
      memcpy(t->tp,topology,sizeof(unsigned int)*t->m);
    }

  #if (W_BTREE)
    if (GetDistanceWeightsFromBox(&weight,ambient)!=t->m)
      Error("Size missmatch in InitBTree");
  #else
    weight=NULL;
  #endif
    
  /* Threshold larger than 'r' since charts center are not in the same
     tangent space. The distance between the centers of the charts will
     be larger than 'r'  (probably r/CE, CE the user defined parameter.
     We somehow assume that CE is always below 0.5  (i.e. that the angle
     between tangent spaces is always below 60 deg, which is very large)*/
  #if (W_BTREE)
  if (weight!=NULL)
    t->r=2*MaxVector(t->m,weight)*GetChartRadius(mp);
  else
  #endif
    t->r=2*GetChartRadius(mp);
    
  #if (_KDTREE==1)
  {
    unsigned int i;
    double *p;
    Trectangle rec;

    /* Convert from box to rectangle */
    InitRectangle(t->m,NULL,NULL,&rec);
    for(i=0;i<t->m;i++)
      {
	range=GetBoxInterval(i,ambient);
	SetRectangleLimits(i,LowerLimit(range),UpperLimit(range),&rec);
      }

    p=GetChartCenter(mp);

    t->kdtree=InitKDTree(&rec,topology,weight,25,0,1,&p,&id);

    DeleteRectangle(&rec);
  }
  #endif

  #if (_KDTREE==2)
  {
    double *w2;

    NEW(w2,t->m,double);
    for(i=0;i<t->m;i++)
      {
	#if (W_BTREE)
	  w2[i]=sqrt(weight[i]);
	#else
	  w2[i]=1.0;
	#endif
      }
    
    if (t->tp==NULL)
      t->kdtree=CreateKDTreeS(t->m,w2); 
    else
      t->kdtree=CreateKDTreeTS(t->m,(int *)t->tp,w2);

    t->mp=INIT_NUM_POINTS_IN_BTREE;
    t->np=0;
    NEW(t->n2id,t->mp,unsigned int);

    AddChart2Btree(id,mp,t);
    
    free(w2);
  }
  #endif

  free(weight);
}

void AddChart2Btree(unsigned int id,Tchart *mp,TBTree *t)
{
  #if (_KDTREE==1)
    AddPoint2KDtree(GetChartCenter(mp),id,&(t->kdtree));
  #endif

  #if (_KDTREE==2)
    if (t->np==1000000)
      Error("The kd-tree in the NN library can only hold one million points");
  
    if (t->np==t->mp)
      MEM_DUP(t->n2id,t->mp,unsigned int);
    t->n2id[t->np]=id;
    t->np++;

    if (t->tp==NULL)
      AddPoint2KDTree(GetChartCenter(mp),t->kdtree);
    else
      {
	/* The NN library can only deal with angles in [-pi,pi] but
	   we might have larger angles (specially in helix). Thus,
	   we map all angular variables in the stored points to [-pi,pi].
	   This will return a larger list of potential neighbours
	   when using angular ranges larger than [-pi,pi]
	*/
	double *p;

	NEW(p,t->m,double);
	memcpy(p,GetChartCenter(mp),sizeof(double)*t->m);
	ArrayPi2Pi(t->m,t->tp,p);
      
	AddPoint2KDTree(p,t->kdtree);
      
	free(p);
      }
  #endif
}

boolean PointInBTree(double eps,double *p,TBTree *t)
{
  boolean found;
  unsigned int nn,*n;
  
  #if (_KDTREE==1)
    NeighboursInBall(p,eps,&nn,&n,t->kdtree);
   
    found=(nn>0);
    if (found)
      free(n);
  #endif

  #if (_KDTREE==2)
    double *d;
    
    QueryKDTreeR(p,eps,(int *)(&nn),(int **)(&n),&d,t->kdtree);
    
    found=(nn>0);
    if (found)
      {
	free(n);
	free(d);
      }
  #endif
    
  return(found);
}

void SearchInBtree(Tchart *mp,unsigned int *nn,unsigned int **n,TBTree *t)
{  
  #if (_KDTREE==1)
    NeighboursInBall(GetChartCenter(mp),t->r,nn,n,t->kdtree);
  #endif

  #if (_KDTREE==2)
    double *d;
    unsigned int i;

    if (t->tp==NULL)
      QueryKDTreeR(GetChartCenter(mp),t->r,(int *)nn,(int **)n,&d,t->kdtree);
    else
      {
	/* The NN library can only deal with angles in [-pi,pi] but
	   we might have larger angles (specially in helix). Thus,
	   we map all angular variables in the query point to [-pi,pi].
	   This will return a larger list of potential neighbours
	   when using angular ranges larger than [-pi,pi]
	*/
	double *p;

	NEW(p,t->m,double);
	memcpy(p,GetChartCenter(mp),sizeof(double)*t->m);
	ArrayPi2Pi(t->m,t->tp,p);
      
	QueryKDTreeR(p,t->r,(int *)nn,(int **)n,&d,t->kdtree);
      
	free(p);
      }

    if (*nn>0)
      {
	free(d); /* distance to each point not used */

	/* Translate from cardinals to identifiers.  */
	for(i=0;i<*nn;i++)
	  (*n)[i]=t->n2id[(*n)[i]];
      }
  #endif
}

void DeleteBTree(TBTree *t)
{
  if (t->tp!=NULL)
    free(t->tp);

  #if (_KDTREE==1)
    DeleteKDtree(t->kdtree);
  #endif

  #if (_KDTREE==2)
    free(t->n2id);
    DeleteKDTree(t->kdtree);
  #endif
}

