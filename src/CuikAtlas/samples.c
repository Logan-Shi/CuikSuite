#include "samples.h"

#include "filename.h"
#include "algebra.h"
#include "parameters.h"
#include "list.h"
#include "random.h"
#include "dynamics.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
/** 
   \file samples.c

   \brief Implementation of the auxiliary functions to deal with sets of samples.

   Implementation of the auxiliary functions to deal with sets of samples.
   
   \sa samples.h
*/

/** 
   \brief Evenly distribute points on the path.

   If set, the cost and the gradient are complemented with a penalty
   term that penalized path steps with different lengths. In other words,
   we try to evenly distribute the steps along the path.

   Long steps are too
   far from the manifold and, thus, they introduce large errors, but they
   are shorter that paths that closely follow the manifold. This is way
   long steps often appear when minimizing the path length (and related
   measures) since the error with respect to the manifold is not
   taken into account.

   Long steps appear more often if we remove steps along the paths
   (if we remove the points that are very close the its neightours).
   In this case the minimization of the dispersion is a must
   \see REMOVE_POINTS.

   See \ref StepDispersion and \ref StepDispersionGradient.
*/
#define DISPERSION 1

/** 
   \brief To remove points when optimizint paths via gradient.

   If set, we remove the points that are too close each other
   during the path gradient optimization.
   
   It can only be set if \ref DISPERSION is also set.
*/
#define REMOVE_POINTS ((DISPERSION)&&(1))


/** 
   \brief Speed up gradient smooth by using approximated charts.

   When displacing a point along a gradient we have to
   compute the chart at this point. Howerver, this chart
   is very close to the chart at the original point (the point
   before the gradient displacement. If this flag is set,
   we use the already computed chart as an approximation of the
   chart at the new point.
   
   \todo Verify that this results in actual speed up.
*/
#define APPROXIMATED_CHARTS_IN_GRADIENT 1

/** 
   \brief Dispersion path step.

   Penalizes path steps that have different length. This is used
   to evenly distribute the path step along the path. 

   For a path sequence (x_1,x_2,x_3), the formula to optimize is
      - (|x_2-x_1|-|x_3-x_2|)^2
      .
   i.e., penalizes the difference in length of the two path steps
   around x_2. This is applied for all points on the path (except
   for 'stalled' points, i.e., points that can not be moved due
   to collision, for instance).

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xp First point in the path (simplified).
   \param x Second point along the path. This is the point 
             used to compute the cost.
   \param xn Third point along the path.
   \param current Which of the three points is the current
                  (i.e., the point for which we evaluate the cost).
   \param cp Chart on c1. Atually not used. Can be NULL.
   \param c Chart on c2. Atually not used. Can be NULL.
   \param cn Chart on c3. Atually not used. Can be NULL.
   \param w The world structure.
*/
double StepDispersion(Tparameters *p,unsigned int *tp,
		      boolean *sv,unsigned int m,
		      double *xp,double *x,double *xn,
		      unsigned int current,
		      Tchart *cp,Tchart *c,Tchart *cn,
		      Tworld *w);

/** 
   \brief Gradient of the step dispersion penalty term.

   Gradient of the \ref StepDispersion cost funtion.

   Note that the actual position of a point (say x_3) affects
   the cost of different triplets of points
       - (x_1,x_2,x_3)
       - (x_2,x_3,x_4)
       - (x_3,x_4,x_5)
       .
   We have to accumulate the gradient in the three cases.
   This is why this function consideres sequences of 5 points
   (x_1,x_2,x_3,x_4,x_5), but returns the derivative w.r.t x_3.

   Note that the step dispersion is orthogonal ot any other cost
   to evaluate on the path. Thus it can be  applied on the top
   of different cost functions (path length, path effort, ...).

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp First point in the sequence. NULL at the beginning
              of the path.
   \param xp Second point in the sequence.
   \param x Third point in the sequence.
   \param xn Fourth point in the sequence.
   \param xnn Fith point in the sequence. NULL at the end of the path.
   \param cpp Chart at xpp.
   \param cp Chart at xp.
   \param c Chart at x.
   \param cn Chart at xn.
   \param cnn Chart at xnn.
   \param sJ The symbolic Jacobian of the constraints. Not used.
             Can be NULL.
   \param cost Cost function. Not used. Can be NULL.
   \param u The resulting gradient (in tangent space!) of the cost
            function w.r.t. x_3.
   \param w The world structure.

   \return TRUE if the gradient could be computed.
*/
boolean StepDispersionGradient(Tparameters *p,unsigned int *tp,
			       boolean *sv,unsigned int m,
			       double *xpp,double *xp,double *x,double *xn,double *xnn,
			       Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			       TJacobian *sJ,TStepCost cost,
			       double *u,Tworld *w);

/** 
   \brief Length path step.

   Auxiliary function used to compute the path length.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xp Fist poinnt in the path. Not used. Can be NULL.
   \param x Second point in the path (simplified).
   \param xn  point along the path. Not used. Can be NULL.

   \param current Which of the three points is the current
                  (i.e., the point for which we evaluate the cost).
   \param cp A chart on xp
   \param c A chart defined on x.
   \param cn A chart defined on xn. Not used. Cam be NULL.
   \param w The world structure.
*/
double StepLength(Tparameters *p,unsigned int *tp,
		  boolean *sv,unsigned int m,
		  double *xp,double *x,double *xn,
		  unsigned int current,
		  Tchart *cp,Tchart *c,Tchart *cn,
		  Tworld *w);

/** 
   \brief Gradient of the length of a path step.

   Auxiliary function used to compute the gradient of a 
   path step length (see \ref StepLength).

   It is used also when smoothing a path via gradient 
   descent.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp Previous of the previous point in the path. 
              Not used. Can be NULL.
   \param xp Previous point in the path.
   \param x Current point. We compute the gradient with
            respect to this point.
   \param xn Next point in the path.
   \param xnn Next of the next point in the path. 
              Not used. Can be NULL.
   \param cpp Chart at xpp. Not used. Can be NULL.
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn.
   \param cnn Chart at xnn. Not used. Can be NULL.
   \param sJ The symbolic Jacobian of the constraints.
   \param cost Cost function.
   \param u The output gradient (in tangent space!)
   \param w The world structure.

   \return TRUE if the gradient can be actually computed.
*/
boolean StepLengthGradient(Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xpp,double *xp,double *x,double *xn,double *xnn,
			   Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			   TJacobian *sJ,TStepCost cost,
			   double *u,Tworld *w);
/** 
   \brief Control effort of a path step.

   Auxiliary function used to compute the path control effort 
   (see \ref PathEffort).

   Computes the control effort of moving from x1 to x2 taking into
   account the drift introduced by the potential energy gradient.
   If there is no such a gradient, the output is close to the
   step length.

   Note that we actually compute and approximation of the control
   effort. The shorter the steps in the path, the closer
   the approximation.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xp Previous point in the path. Actually not used. 
             Can be NULL.
   \param x Current point in the path (simplified).
   \param xn Next point along the path.
   \param current Which of the three points is the current
                  (i.e., the point for which we evaluate the cost).
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn. Actually not used. 
             Can be NULL.
   \param w The world structure.
*/
double StepEffort(Tparameters *p,unsigned int *tp,
		  boolean *sv,unsigned int m,
		  double *xp,double *x,double *xn,
		  unsigned int current,
		  Tchart *cp,Tchart *c,Tchart *cn,Tworld *w);

/** 
   \brief Gradient of the control effort of a path step.

   Auxiliary function used to compute the gradient of a 
   path step control effort (see \ref StepEffort).

   This is also used to smooth a path via gradient descent.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp Previous of the previous point in the path. 
              Not used. Can be NULL.
   \param xp Previous point in the path.
   \param x Current point. We compute the gradient with
            respect to this point.
   \param xn Next point in the path.
   \param xnn Next of the next point in the path. 
              Not used. Can be NULL.
   \param cpp Chart at xpp. Not used. Can be NULL.
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn.
   \param cnn Chart at xnn. Not used. Can be NULL.
   \param sJ The symbolic Jacobian of the constraints.
   \param cost Cost function.
   \param u The output gradient (in tangent space!)
   \param w The world structure.

   \return TRUE if the gradient can be actually computed.
*/
boolean StepEffortGradient(Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xpp,double *xp,double *x,double *xn,double *xnn,
			   Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			   TJacobian *sJ,TStepCost cost,
			   double *u,Tworld *w);

/** 
   \brief Generic numerical gradient.

   Numerical gradient. Works for any cost function but it is
   slower than a specific gradient.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp Previous of the previous point in the path. 
              Not used. Can be NULL.
   \param xp Previous point in the path.
   \param x Current point. We compute the gradient with
            respect to this point.
   \param xn Next point in the path.
   \param xnn Next of the next point in the path. 
              Not used. Can be NULL.
   \param cpp Chart at xpp. Not used. Can be NULL.
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn.
   \param cnn Chart at xnn. Not used. Can be NULL.
   \param sJ The symbolic Jacobian of the constraints.
   \param cost Cost function.
   \param u The output gradient (in tangent space!)
   \param w The world structure.

   \return TRUE if the gradient can be actually computed.
*/
boolean StepCostNumericalGradient(Tparameters *p,unsigned int *tp,
				  boolean *sv,unsigned int m,
				  double *xpp,double *xp,double *x,double *xn,double *xnn,
				  Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
				  TJacobian *sJ,TStepCost cost,
				  double *u,Tworld *w);
/** 
   \brief Combines two cost functions.

   Adds two cost functions.
   
   \param c1 The first cost function to add.
   \param c2 The second cost function to add.
   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xp Previous point in the path. Actually not used. 
             Can be NULL.
   \param x Current point in the path (simplified).
   \param xn Next point along the path.
   \param current Which of the three points is the current
                  (i.e., the point for which we evaluate the cost).
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn. Actually not used. 
             Can be NULL.
   \param w The world structure.
*/
double CombineCosts(TStepCost c1,TStepCost c2,
		    Tparameters *p,unsigned int *tp,
		    boolean *sv,unsigned int m,
		    double *xp,double *x,double *xn,
		    unsigned int current,
		    Tchart *cp,Tchart *c,Tchart *cn,Tworld *w);

/** 
   \brief Combines two gradients.

   Gradient of \ref CombineCosts (if called with the right
   set of parameters).

   \param g1 The first gradient to add.
   \param g2 Teh second gradient to add.
   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp Previous of the previous point in the path. 
              Not used. Can be NULL.
   \param xp Previous point in the path.
   \param x Current point. We compute the gradient with
            respect to this point.
   \param xn Next point in the path.
   \param xnn Next of the next point in the path. 
              Not used. Can be NULL.
   \param cpp Chart at xpp. Not used. Can be NULL.
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn.
   \param cnn Chart at xnn. Not used. Can be NULL.
   \param sJ The symbolic Jacobian of the constraints.
   \param cost Cost function.
   \param u The output gradient (in tangent space!)
   \param w The world structure.

   \return TRUE if the gradient can be actually computed.
*/
boolean CombineGradients(TStepCostGradient g1,
			 TStepCostGradient g2,
			 Tparameters *p,unsigned int *tp,
			 boolean *sv,unsigned int m,
			 double *xpp,double *xp,double *x,double *xn,double *xnn,
			 Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			 TJacobian *sJ,TStepCost cost,
			 double *u,Tworld *w);

/** 
   \brief Combines length and dispersion cost functions.

   Adds the length and dispersion cost functions.
   See \ref CombineCosts.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xp Previous point in the path. Actually not used. 
             Can be NULL.
   \param x Current point in the path (simplified).
   \param xn Next point along the path.
   \param current Which of the three points is the current
                  (i.e., the point for which we evaluate the cost).
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn. Actually not used. 
             Can be NULL.
   \param w The world structure.
*/
double LengthAndDispersion(Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xp,double *x,double *xn,
			   unsigned int current,
			   Tchart *cp,Tchart *c,Tchart *cn,Tworld *w);

/** 
   \brief Gradient of the length and dispersion.

   Gradient of \ref LengthAndDispersion.

   See \ref CombineGradients.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp Previous of the previous point in the path. 
              Not used. Can be NULL.
   \param xp Previous point in the path.
   \param x Current point. We compute the gradient with
            respect to this point.
   \param xn Next point in the path.
   \param xnn Next of the next point in the path. 
              Not used. Can be NULL.
   \param cpp Chart at xpp. Not used. Can be NULL.
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn.
   \param cnn Chart at xnn. Not used. Can be NULL.
   \param sJ The symbolic Jacobian of the constraints.
   \param cost Cost function.
   \param u The output gradient (in tangent space!)
   \param w The world structure.

   \return TRUE if the gradient can be actually computed.
*/
boolean LengthAndDispersionGradient(Tparameters *p,unsigned int *tp,
				    boolean *sv,unsigned int m,
				    double *xpp,double *xp,double *x,double *xn,double *xnn,
				    Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
				    TJacobian *sJ,TStepCost cost,
				    double *u,Tworld *w);
/** 
   \brief Combines control effort and dispersion cost functions.

   Adds the control effort and dispersion cost functions.

   See \ref CombineCosts.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xp Previous point in the path. Actually not used. 
             Can be NULL.
   \param x Current point in the path (simplified).
   \param xn Next point along the path.
   \param current Which of the three points is the current
                  (i.e., the point for which we evaluate the cost).
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn. Actually not used. 
             Can be NULL.
   \param w The world structure.
*/
double EffortAndDispersion(Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xp,double *x,double *xn,
			   unsigned int current,
			   Tchart *cp,Tchart *c,Tchart *cn,Tworld *w);

/** 
   \brief Gradient of the effort and dispersion.

   Gradient of \ref EffortAndDispersion.

   See \ref CombineGradients.

   \param p The set of parameters.
   \param tp The topology of the variables (in simplified system).
   \param sv The selected variables to compute the path length 
             component of the effort.
   \param m The size of the points (in simplified system!)
   \param xpp Previous of the previous point in the path. 
              Not used. Can be NULL.
   \param xp Previous point in the path.
   \param x Current point. We compute the gradient with
            respect to this point.
   \param xn Next point in the path.
   \param xnn Next of the next point in the path. 
              Not used. Can be NULL.
   \param cpp Chart at xpp. Not used. Can be NULL.
   \param cp A chart defined on xp.
   \param c A chart defined on x.
   \param cn A chart defined on xn.
   \param cnn Chart at xnn. Not used. Can be NULL.
   \param sJ The symbolic Jacobian of the constraints.
   \param cost Cost function.
   \param u The output gradient (in tangent space!)
   \param w The world structure.

   \return TRUE if the gradient can be actually computed.
*/
boolean EffortAndDispersionGradient(Tparameters *p,unsigned int *tp,
				    boolean *sv,unsigned int m,
				    double *xpp,double *xp,double *x,double *xn,double *xnn,
				    Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
				    TJacobian *sJ,TStepCost cost,
				    double *u,Tworld *w);

/** 
    \brief Compares two unsigned in integers.

    Auxiliary function used for qsort inside \ref RandomSmooth
    when we exploit parallelism to speed up the smoothing.

    \param a Pointer to the first unsigned integer.
    \param b Pointer to the second unsigned integer.

    \return -1 if a<b, 0 if a==b, or 1 if a>b.
*/
int cmpUInt(const void *a,const void *b);

/** 
   \brief Fixed-cut based smoothing.

   This is like the \ref RandomSmooth but the tentative shortcuts
   are selected systematically: from the first sample as far
   as possible and so on.

   \param pr The set of parameters.
   \param sv The variables to use in the distance computations.
   \param stime Statistics initilized at the beginning of the smoothing process.
   \param np Number of points defining the path.
   \param point The points defining the path.
   \param w The world/cuiksystem on which the sample is defined.
*/
void ShortcutSmooth(Tparameters *pr,boolean *sv,Tstatistics *stime,
		    unsigned int *np,double ***point,TAtlasBase *w);

/** 
   \brief Random-based path smoothing.

   Tries to reduce the lenght of a path by ramdomly selecting points 
   on the path and verifying if a direct collision free path between them exists.
   If so, the new path replaces a segment of the previous path.

   IMPORTANT: this is a sub-process of \ref SmoothSamples and it is
   intended for internal use only and the points are defined
   in the simplified system and not in the original system as most of
   the functions on samples.

   \param pr The set of parameters.
   \param nCores Number of computing cores available.
   \param maxIterations Maximum number of iterations. To be scaled
                        by the number of steps in the path.
   \param sv Array with the components to use distance computations.
   \param stime Statistics initilized at the beginning of the smoothing process.
   \param np Number of points defining the path.
   \param point The points defining the path.
   \param w The world/cuiksystem on which the sample is defined.
*/
void RandomSmooth(Tparameters *pr,unsigned int nCores,unsigned int maxIterations,
		  boolean *sv,Tstatistics *stime,
		  unsigned int *np,double ***point,TAtlasBase *w);

/** 
   \brief Gradient-based path smoothing.

   Reduces the length of a path by applying a movement to the points
   forming the path according the the gradient of the path lenght for
   w.r.t. the parameters of this points.

   IMPORTANT: this is a sub-process of \ref SmoothSamples and it is
   intended for internal use only and the points are defined
   in the simplified system and not in the original system as most of
   the functions on samples.

   \param pr The set of parameters.
   \param nCores Number of computing cores available. Up to now this is not used.
   \param maxIterations Maximum number of iterations. To be scaled
                        by the number of steps in the path.
   \param sv Array with the components to use distance computations.
   \param stime Statistics initilized at the beginning of the smoothing process.
   \param np Number of points defining the path.
   \param point The points defining the path.
   \param stepCost Function giving the cost of moving between two path steps
                   See \ref TStepCost
   \param stepCostGradient Function giving the gradient of the cost
                           when moving a point in between two other points
			   along the path. See \ref TStepCostGradient
			   If NULL a numerical gradient is used.
   \param w The world/cuiksystem on which the sample is defined.

   \todo Implement a parallel version of the \ref GradientSmooth function.
*/
void GradientSmooth(Tparameters *pr,
		    unsigned int nCores,unsigned int maxIterations,
		    boolean *sv,Tstatistics *stime,
		    unsigned int *np,double ***point,
		    TStepCost stepCost,
		    TStepCostGradient stepCostGradient,
		    TAtlasBase *w);



/**  
   \brief Internal function to save a set of samples to a file.

   Internal function to save a set of samples to a file. This includes code
   shared by \ref SaveSamples and \ref SaveSamplesN.

   \param fpath Name of the file where to store the samples.
   \param nvs The dimensionality of each sample.
   \param ns The number of samples defining the path.
   \param path The collection of samples defining the path.
   \param da Dimension of the action space.
   \param action Action executed at each time step.
                 Optional. NULL if not given.
   \param time Execution time for each action.
               Optional. NULL if not given.
*/
void SaveSamplesInt(Tfilename *fpath,unsigned int nvs,
		    unsigned int ns,double **path,
		    unsigned int da,double **action,double *time);

/********************************************************************/
/********************************************************************/
/********************************************************************/

void InitSamples(unsigned int *ms,unsigned int *ns,double ***path)
{
  *ms=INIT_NUM_SAMPLES;
  *ns=0;
  NEW((*path),*ms,double*);
}

void InitSamplesReplay(unsigned int *ms,unsigned int *ns,double ***path,
		       boolean **newChart,double **time,double **cost)
{
  InitSamples(ms,ns,path);
  if (newChart!=NULL)
    NEW((*newChart),*ms,boolean);
  if (time!=NULL)
    NEW((*time),*ms,double);
  if (cost!=NULL)
    NEW((*cost),*ms,double);
}

void InitTrajectory(unsigned int *ms,unsigned int *ns,double ***path,
		    unsigned int da,double ***actions,double **times)
{
  InitSamples(ms,ns,path);
  NEW((*actions),*ms,double*);
  NEW((*times),*ms,double);
}

void AddSample2Samples(unsigned int nv,double *sample,
		       unsigned int nvs,boolean *systemVars,
		       unsigned int *ms,unsigned int *ns,double ***path)
{
  unsigned int i,k;
  
  if (*ns==*ms)
    MEM_DUP(*path,*ms,double *);
  
  NEW((*path)[*ns],nvs,double);
  k=0;
  for(i=0;i<nv;i++)
    {
      if ((systemVars==NULL)||(systemVars[i]))
	{
	  (*path)[*ns][k]=sample[i];
	  k++;
	}
    }
  (*ns)++;
}

void AddSample2SamplesReplay(unsigned int nv,double *sample,boolean nc,double h,double c,
			     unsigned int nvs,boolean *systemVars,
			     unsigned int *ms,unsigned int *ns,double ***path,
			     boolean **newChart,double **time,double **cost)
{
  unsigned int i,k;
  
  if (*ns==*ms)
    {
      MEM_DUP(*path,*ms,double *);
      if (newChart!=NULL)
	MEM_EXPAND(*newChart,*ms,boolean);
      if (time!=NULL)
	MEM_EXPAND(*time,*ms,double);
      if (cost!=NULL)
	MEM_EXPAND(*cost,*ms,double);
    }
  
  NEW((*path)[*ns],nvs,double);
  k=0;
  for(i=0;i<nv;i++)
    {
      if ((systemVars==NULL)||(systemVars[i]))
	{
	  (*path)[*ns][k]=sample[i];
	  k++;
	}
    }
  if (newChart!=NULL)
    (*newChart)[*ns]=nc;
  if (time!=NULL)
    (*time)[*ns]=h;
  if (cost!=NULL)
    (*cost)[*ns]=c;
  (*ns)++;
}

void AddStep2Trajectory(unsigned int nv,double *sample,
			unsigned int nvs,boolean *systemVars,
			double *action,double time,
			unsigned int *ms,unsigned int *ns,double ***path,
			unsigned int da,double ***actions,double **times)
{
  unsigned int i,k;
  
  if (*ns==*ms)
    {
      MEM_DUP(*path,*ms,double *);
      MEM_EXPAND(*actions,*ms,double*);
      MEM_EXPAND(*times,*ms,double);
    }
  
  NEW((*path)[*ns],nvs,double);
  k=0;
  for(i=0;i<nv;i++)
    {
      if ((systemVars==NULL)||(systemVars[i]))
	{
	  (*path)[*ns][k]=sample[i];
	  k++;
	}
    }
  
  NEW((*actions)[*ns],da,double);
  for(i=0;i<da;i++)
    (*actions)[*ns][i]=(action==NULL?0.0:action[i]);
  
  (*times)[*ns]=time;
  
  (*ns)++;  
}

double ConnectDynamicStatesID(Tparameters *pr,unsigned int *tp,Tbox *ambient,boolean collision,
			      unsigned int m,unsigned int k,unsigned int da,
			      double *state,double *action,double time,double *goal,
			      unsigned int *ns,double ***path,double ***actions,double **times,
			      TJacobian *J,TDynamicSpace *ds,TAtlasBase *w)
{
  double t,h,delta;
  boolean done;
  Tchart c;
  double *currentS,*currentT,*nextS,*nextT,*currentA;
  unsigned int ms,it;
  double e,mt;

  delta=GetParameter(CT_DELTA,pr);
  
  NEWZ(currentS,m,double);
  NEWZ(currentT,k,double);
  NEWZ(nextS,m,double);
  NEWZ(nextT,k,double);
  NEWZ(currentA,da,double);

  InitTrajectory(&ms,ns,path,da,actions,times);
  /* here we use currentS as a long vector of zeros! */
  AddStep2Trajectory(m,state,m,NULL,currentS,0.0,&ms,ns,path,da,actions,times);
  
  memcpy(currentS,state,sizeof(double)*m);
  
  t=0;
  done=FALSE;
  while((!done)&&(t<time))
    {
      done=(InitChart(pr,TRUE,ambient,tp,m,k,currentS,0.1,0.1,1,J,w,&c)!=0);
      if (!done)
	{
	  /* This is always zero, but just in case we do not
	     generate charts at each step */
	  //Manifold2Chart(currentS,tp,currenT,&c);

	  /* remaining time */
	  mt=time-t;
	  
	  /* compute the desired acceleration (re-use nextS to store
	     the desired acceleration) */
	  Manifold2Chart(goal,tp,nextT,&c);
	  Local2Global(nextT,tp,nextS,&c);
	  ScaleVector(1/mt,m,nextS);
	  
	  /* adjust the action via inverse dynamics */
	  ComputeInverseDynamics(pr,FALSE,&c,currentS,nextS,currentA,ds);

	  /* apply the action for a limited time */
	  if (mt>0.1) mt=0.1;
	  
	  /* compute next state */
	  done=(NextDynamicState(pr,START2GOAL,delta,FALSE,
				 currentS,currentT,&c,currentA,
				 &h,mt,nextS,&it,ds)>0);
	  if (collision)
	    {
	      CS_WD_IN_COLLISION(done,pr,currentS,nextS,w);
	    }

	  if (!done)
	    {
	      AddStep2Trajectory(m,nextS,m,NULL,currentA,h,&ms,ns,path,da,actions,times);
	      t+=h;
	    }
	  DeleteChart(&c);

	  memcpy(currentS,nextS,sizeof(double)*m);
	}
    }

  if (*ns==1)
    {
      memset(currentS,0,da*sizeof(double));
      AddStep2Trajectory(m,goal,m,NULL,currentS,0.01,&ms,ns,path,da,actions,times);
    }
    
  
  if (done)
    e=INF;
  else
    e=DistanceTopology(m,tp,nextS,goal);
  
  free(currentS);
  free(currentT);
  free(nextS);
  free(nextT);
  free(currentA);
  
  return(e);
}

double ConnectDynamicStates(Tparameters *pr,unsigned int *tp,Tbox *ambient,boolean collision,
			    unsigned int m,unsigned int k,unsigned int da,
			    double *state,double *action,double time,double *goal,
			    unsigned int *ns,double ***path,double ***actions,double **times,
			    TJacobian *J,TDynamicSpace *ds,TAtlasBase *w)
{
  double t,h,delta;
  boolean done;
  Tchart c;
  double *currentS,*currentT,*nextS;
  unsigned int ms,it;
  double e,mt;

  NEWZ(currentS,m,double);
  NEWZ(currentT,k,double);
  NEWZ(nextS,m,double);

  InitTrajectory(&ms,ns,path,da,actions,times);
  /* here we use currentS as a long vector of zeros! */
  AddStep2Trajectory(m,state,m,NULL,currentS,0.0,&ms,ns,path,da,actions,times);
  
  memcpy(currentS,state,sizeof(double)*m);
  
  t=0;
  done=FALSE;
  while((!done)&&(t<time))
    {
      delta=GetParameter(CT_DELTA,pr);
      done=(InitChart(pr,TRUE,ambient,tp,m,k,currentS,0.1,0.1,1,J,w,&c)!=0);
      if (!done)
	{
	  /* This is always zero, but just in case we do not
	     generate charts at each step */
	  //Manifold2Chart(currentS,tp,currenT,&c);
	  mt=time-t;
	  if (mt>0.1) mt=0.1;
	  done=(NextDynamicState(pr,START2GOAL,delta,FALSE,
				 currentS,currentT,&c,action,
				 &h,mt,nextS,&it,ds)>0);
	  if (collision)
	    {
	      CS_WD_IN_COLLISION(done,pr,currentS,nextS,w);
	    }

	  if (!done)
	    {
	      AddStep2Trajectory(m,nextS,m,NULL,action,h,&ms,ns,path,da,actions,times);
	      t+=h;
	    }
	  DeleteChart(&c);

	  memcpy(currentS,nextS,sizeof(double)*m);
	}
    }

  if (*ns==1)
    {
      memset(currentS,0,da*sizeof(double));
      AddStep2Trajectory(m,goal,m,NULL,currentS,0.01,&ms,ns,path,da,actions,times);
    }
    
  
  if (done)
    e=INF;
  else
    e=DistanceTopology(m,tp,nextS,goal);
  
  free(currentS);
  free(currentT);
  free(nextS);
  
  return(e);
}

double ConnectSamplesChart(Tparameters *pr,unsigned int *tp,
			   boolean *sv,Tbox *domain,
			   unsigned int m,unsigned int n,
			   double *s1,double *s2,
			   double md,boolean checkCollisions,
			   TJacobian *sJ,
			   boolean *reached,boolean *collision,
			   double *lastSample,unsigned int *ns,double ***path,
			   TAtlasBase *w)
{
  boolean blocked,validChart,first;
  double dist;
  double *s,*s_next,*s_goal,*t,*t_next,*t_goal;
  unsigned int i,k,a,b;
  double delta,step,epsilon,d,df,dtmp,distFull,d12,e,ce,r,nt;
  unsigned int ms;
  Tchart c;

  epsilon=GetParameter(CT_EPSILON,pr);
  delta=GetParameter(CT_DELTA,pr);
  k=(unsigned int)GetParameter(CT_N_DOF,pr);
  e=GetParameter(CT_E,pr);
  ce=GetParameter(CT_CE,pr);
  r=GetParameter(CT_R,pr);

  /* Assume that the CD is already initialized */

  GetJacobianSize(&a,&b,sJ);
  if (b!=m)
    Error("Jacobian size missmatch in ConnectSamplesChart");
  
  if ((ns!=NULL)&&(path!=NULL))
    InitSamples(&ms,ns,path);
  else
    ms=0;

  /* we keep track of the current sample in the path
     and the previous one to compute the displacement
     between them */
  if (lastSample==NULL)
    { NEW(s,m,double); }
  else
    s=lastSample;
  memcpy(s,s1,m*sizeof(double)); /* current sample */
  NEW(s_next,m,double); /* space for the next sample */
  NEW(s_goal,m,double); /* goal sample projected to the current chart */
  NEW(t,k,double);      /* parameters for 's' */
  NEW(t_next,k,double); /* parameters for 's_next' */
  NEW(t_goal,k,double); /* parameters for 's_goal' */

  d12=DistanceTopology(m,tp,s1,s2);
  dist=0.0;
  distFull=0.0;
  *reached=(d12<delta);
  *collision=FALSE;
  blocked=FALSE;
  
  while ((!*reached)&&(!blocked)&&(!*collision))
    {  
      /* Initialize the chart at the current sample */
      if (tp!=NULL)
	ArrayPi2Pi(m,tp,s);
      
      //fprintf(stderr,"New chart\n");
      if (InitChart(pr,TRUE,domain,tp,m,k,s,e,ce,r,sJ,w,&c)!=0)
	{
	  //fprintf(stderr,"  Blocked (error init chart)\n");
	  blocked=TRUE;
	}
      else
	{
	  /* 's' is 0 in the new chart */
	  for(i=0;i<k;i++)
	    t[i]=0.0;

	  /* Determine the advance direction */
	  DifferenceVectorTopology(m,tp,s2,s,s_goal);
	  AccumulateVector(m,s,s_goal);
	  Manifold2Chart(s_goal,NULL,t_goal,&c); /* without topology now */
	  nt=Norm(k,t_goal);
	  if (nt<1e-3)
	    {
	      //fprintf(stderr,"  Blocked (small projection)\n");
	      blocked=TRUE; /* it is not clear which direction to take */
	    }
	  else
	    {
	      //fprintf(stderr,"tg:%g\n",Norm(k,t_goal));
	      /* when far from the goal, we move the goal far enough to ensure
	         the creation of new charts, if necessary. */
	      if (DistanceTopology(m,tp,s2,s)>r)
		ScaleVector(2.0*r/nt,k,t_goal); /* move the goal far enough */

	      /* Move in the current chart as far as possible */
	      validChart=TRUE;
	      step=delta;
	      first=TRUE;
	      while ((validChart)&&(!*reached)&&(!blocked)&&(!*collision))
		{
		  /* Define t_next from t and t_goal */
		  DifferenceVector(k,t_goal,t,t_next);
		  nt=Norm(k,t_next);
		  if (nt>step)
		    {
		      SumVectorScale(k,t,step/nt,t_next,t_next);
		      nt=step;
		    }
		  else
		    AccumulateVector(k,t,t_next);
		  //fprintf(stderr,"  New step-> dg:%g (%g) st:%g  tn:%g  tg:%g (%g)\n",nt,DistanceTopology(m,tp,s2,s),nt,Norm(k,t_next),Norm(k,t_goal),Distance(k,NULL,t_next,t_goal));
		  
		  if (0) //(Norm(k,t_next)>r) /* TO BE REMOVED */
		    {
		      /* We use the current chart as much as possible. 'r' limits the use of the
		         chart without any reason. It is only useful when storing the charts to
		         generate regular pavings of the manifold. */
		      //fprintf(stderr,"  Change chart (r)\n");
		      validChart=FALSE;
		    }
		  else
		    {
		      /* and project to the manifold to obtain q_next */
		      if (Chart2Manifold(pr,sJ,t_next,NULL,s,s_next,&c)>e)
			{
			  //fprintf(stderr,"  Change chart (e)\n");
			  validChart=FALSE;
			}
		      else
			{
			  if ((nt<epsilon)&&(DistanceTopology(m,tp,s_next,s2)>delta))
			    {
			      /* we reached the targed in tangent space but the projection does not correspond
				 to the actual goal. Try to advance generating a new chart. */
			      if (first)
				{
				  /* Note that it is not worth to reduce the step since we are already taking
				     steps of size epsilon. */
				  //fprintf(stderr,"  Blocked (tangent vs ambient)\n");
				  blocked=TRUE;
				}
			      else
				{
				  /* The current sample does not have a chart. Try to define a new chart on in
				     Hopefully, the projection of the goal in the new chart will define a more
				     clear advance direction. */
				  //fprintf(stderr,"  Change chart (tangent vs ambient)\n");
				  validChart=FALSE;
				}
			    }
			  else
			    {
			      if ((!PointInBoxTopology(NULL,FALSE,m,s_next,epsilon,tp,domain))||
				  (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,s_next,w)))
				{
				  //fprintf(stderr,"  Blocked (out of domain)\n");
				  blocked=TRUE;
				}
			      else
				{
				  if (checkCollisions)
				    CS_WD_IN_COLLISION(*collision,pr,s_next,s,w);
				  if (*collision)
				    {
				      //fprintf(stderr,"  Blocked (collision)\n");
				      blocked=TRUE;
				    }
				  else
				    {
				      df=DistanceTopology(m,tp,s,s_next);
				      if (sv==NULL)
					d=df;
				      else
					d=DistanceTopologySubset(m,tp,sv,s,s_next);
				      dtmp=dist+d;
				      distFull+=df;

				      /* Sanity check to avoid infinite connections or even oscilations. 
					 The constants (2 and 1.5) could be changed, but they are resonable in our experience. */
				      if ((dtmp>md)||(distFull>2.0*d12)||(DistanceTopology(m,tp,s1,s_next)>1.5*d12))
					{
					  /*
					  if (dtmp>md)
					    fprintf(stderr,"  Blocked (max dist reached)\n");
					  if (dtmp>2.0*d12)
					    fprintf(stderr,"  Blocked (path too long)\n");
					  if (DistanceTopology(m,tp,s1,s_next)>1.5*d12)
					    fprintf(stderr,"  Blocked (too far from origin)\n");
					  */
					  blocked=TRUE;
					}
				      else
					{
					  /* Check if it is time to define a new chart along the connection */
					  /* We do the check before copying s_next to s -> the new chart is
					     defined in the last good sample */
					  df=DistanceTopology(m,tp,s,s_next);
					  if (nt/df<(1.0-ce)) /* nt=actual step in tangent space (can be < step at the end) */
					    {
					      //fprintf(stderr,"  Change chart (ce)\n");
					      validChart=FALSE;
					    }
					  else
					    {
					      dist=dtmp;
					  
					      *reached=(DistanceTopology(m,tp,s_next,s2)<delta);
					      /*
					      fprintf(stderr,"  New sample (%g)\n",dist);
					      if (*reached)
						fprintf(stderr,"  Reached\n");
					      */
					      /* since everything is ok, we will continue from the last point */
					      memcpy(t,t_next,k*sizeof(double));
					      memcpy(s,s_next,m*sizeof(double));
					  
					      /* t_next and s_next alredy backed up-> we can modify them */
					      if (tp!=NULL)
						ArrayPi2Pi(m,tp,s_next);
					  
					      /* Here we have a new valid sample */
					      if ((ms>0)&&(!(*reached)))
						AddSample2Samples(m,s_next,m,NULL,&ms,ns,path);
					  
					      first=FALSE; /* we already have one sample */
					      step=delta; /* the following steps will be normal size */
					    }
					}
				    }
				}
			    }
			}
		    }
		  if ((!validChart)&&(first))
		    { 
		      /* we already have a chart at the last 's' -> we need sample close to 's'
		         where to generate the new chart. This only happens on very curved
		         manifolds or close to singularities. */
		      step*=0.9;
		      if (step<epsilon)
			{
			  //fprintf(stderr,"  Blocked (impossible)\n");
			  blocked=TRUE;
			}
		      validChart=TRUE;
		    }
		}
	    }
	  DeleteChart(&c);
	}
    }

  if (*reached)
    dist+=d; /* epsilon/delta size */
  else
    {
      if (ms>0) 
	{
	  DeleteSamples(*ns,*path);
	  ns=0;
	}
    }

  if (lastSample==NULL)
    free(s);
  free(s_next);
  free(s_goal);
  free(t);
  free(t_next);
  free(t_goal);

  return(dist);
}

double ConnectSamples(Tparameters *pr,unsigned int *tp,
		      boolean *sv,Tbox *domain,
		      unsigned int m,unsigned int n,
		      double *s1,double *s2,
		      double md,boolean checkCollisions,
		      TJacobian *sJ,
		      boolean *reached,boolean *collision,
		      double *lastSample,unsigned int *ns,double ***path,
		      TAtlasBase *w)
{
  boolean blocked;
  double c;
  double *v,*s,*s_next,*s_tmp;
  double delta,epsilon,d,small,d1, d_new;
  unsigned int ms;

  delta=GetParameter(CT_DELTA,pr);
  epsilon=GetParameter(CT_EPSILON,pr);
  small=delta/50; // for delta=0.05 delta/50 gives the value used by Berenson
                  // Use 10 for RRT*, to avoid too irregular samples
  if (tp!=NULL)
    {
      ArrayPi2Pi(m,tp,s1);
      ArrayPi2Pi(m,tp,s2);
    }

  if ((ns!=NULL)&&(path!=NULL))
    InitSamples(&ms,ns,path);
  else
    ms=0;

  /* displacement from current sample to goal */
  NEW(v,m,double);
  /* we keep track of the current sample in the path
     and the previous one to compute the displacement
     between them */
  if (lastSample==NULL)
    { NEW(s,m,double); }
  else
    s=lastSample;
  memcpy(s,s1,sizeof(double)*m);
  NEW(s_next,m,double);
  NEW(s_tmp,m,double);
 
  DifferenceVectorTopology(m,tp,s2,s,v);
  d=Norm(m,v);
  *reached=(d<delta);
  *collision=FALSE;
  blocked=FALSE;

  c=0;

  while ((!*reached)&&(!blocked)&&(!*collision))
    {      
      if (d<delta+small)
	memcpy(s_next,s2,m*sizeof(double));
      else
	{
	  SumVectorScale(m,s,delta/d,v,s_next);

	  if (n==0)
	    blocked=FALSE;
	  else
	    blocked=(CS_WD_NEWTON_IN_SIMP(pr,s_next,w)==DIVERGED);
	}

      if (!blocked)
	{
	  memcpy(s_tmp,s_next,m*sizeof(double));
	  if (tp!=NULL)
	    ArrayPi2Pi(m,tp,s_tmp);
	  if ((!PointInBoxTopology(NULL,FALSE,m,s_tmp,epsilon,tp,domain))||
	      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,s_tmp,w)))
	    blocked=TRUE;
	  else
	    {
	      if (checkCollisions)
		CS_WD_IN_COLLISION(*collision,pr,s_next,s,w);
	      if (!*collision)
		{
		  d1=DistanceTopology(m,tp,s,s_next);
		  if (d1<small) /* If stalled -> stop */
		    blocked=TRUE;
		  else
		    {
		      if (sv!=NULL)
			d1=DistanceTopologySubset(m,tp,sv,s,s_next);
		      if ((c+d1)>md) /* If beyond the max displacement -> stop */
			blocked=TRUE;
		      else
			{
			  memcpy(s,s_next,sizeof(double)*m);
			  DifferenceVectorTopology(m,tp,s2,s,v);
			  d_new=Norm(m,v);
			  if(d_new>d) 
			    blocked=TRUE;
			  else 
			    {
			      c+=d1;
			      d=d_new;
			      *reached=(d<epsilon);
			      if ((ms>0)&&(!(*reached)))
				AddSample2Samples(m,s_next,m,NULL,&ms,ns,path);
			    }
			}
		    }
		}
	    }
	}
    }
  if (*reached)
    c+=DistanceTopologySubset(m,tp,sv,s,s2); /* epsilon size */
  else
    {
      if (ms>0) 
	{
	  DeleteSamples(*ns,*path);
	  ns=0;
	}
    }

  free(v);
  if (lastSample==NULL)
    free(s);
  free(s_next);
  free(s_tmp);

  return(c);
}

double PathLength(unsigned int *tp,
		  boolean *sv,unsigned int m,
		  unsigned int np,double **point)
{
  double l;
  unsigned int i;

  /* do not execute in parallel: it's simple and it's used
     inside other parellel context. */
  l=0.0;
  for(i=1;i<np;i++)
    l+=DistanceTopologySubset(m,tp,sv,point[i-1],point[i]);
  
  return(l);
}

double StepDispersion(Tparameters *p,unsigned int *tp,
		      boolean *sv,unsigned int m,
		      double *xp,double *x,double *xn,
		      unsigned int current,
		      Tchart *cp,Tchart *c,Tchart *cn,
		      Tworld *w)
{
  double d1,d2,e;

  /* dispersion is not defined for the first/last step on the path */
  if ((xp!=NULL)&&(x!=NULL)&&(xn!=NULL))
    {
      d1=DistanceTopologySubset(m,tp,sv,xp,x);
      d2=DistanceTopologySubset(m,tp,sv,x,xn);
      e=(d1-d2);
      e*=e;
    }
  else
    e=0.0;

  return(e);
}

boolean StepDispersionGradient(Tparameters *p,unsigned int *tp,
			       boolean *sv,unsigned int m,
			       double *xpp,double *xp,double *x,double *xn,double *xnn,
			       Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			       TJacobian *sJ,TStepCost cost,
			       double *u,Tworld *w)
{
  unsigned int k;
  double epsilon;
  double *s1,*s2,*g;
  double d0,d1,d2,d3,c1,c2;
  boolean ok=TRUE;

  if ((xp==NULL)||(x==NULL)||(xn==NULL))
    ok=FALSE;
  else
    {
      k=(unsigned int)GetParameter(CT_N_DOF,p);
      epsilon=GetParameter(CT_EPSILON,p);

      NEW(s1,3*m,double);
      s2=&(s1[m]);
      g=&(s2[m]);

      DifferenceVectorTopologySubset(m,tp,sv,x,xp,s1);
      d1=Norm(m,s1);
      if (d1<epsilon)
	ok=FALSE;
      else
	{  
	  DifferenceVectorTopologySubset(m,tp,sv,xn,x,s2);
	  d2=Norm(m,s2);
	  if (d2<epsilon)
	    ok=FALSE;
	  else
	    {
	      if (xpp==NULL)
		c1=d1-d2;
	      else
		{
		  d0=DistanceTopologySubset(m,tp,sv,xpp,xp);
		  c1=2*d1-d0-d2;
		}
	      if (xnn==NULL)
		c2=-(d1-d2);
	      else
		{
		  d3=DistanceTopologySubset(m,tp,sv,xn,xnn);
		  c2=2*d2-d1-d3;
		}
	  
	      memcpy(g,s1,m*sizeof(double));
	      ScaleVector(2*c1/d1,m,g);
	      SumVectorScale(m,g,-2*c2/d2,s2,g);
    
	      if (k==m)
		memcpy(u,g,k*sizeof(double));
	      else
		TMatrixVectorProduct(m,k,GetChartTangentSpace(c),g,u);
	    }
	}
  
      free(s1);
    }

  return(ok);
}

double StepLength(Tparameters *p,unsigned int *tp,
		  boolean *sv,unsigned int m,
		  double *xp,double *x,double *xn,
		  unsigned int current,
		  Tchart *cp,Tchart *c,Tchart *cn,Tworld *w)
{
  double cost;
  
  if (current>2)
    Error("Wrong 'current' parameter in StepLength");
  
  if (current==2)
    cost=0.0;
  else
    /* path length from xp to x */
    /* d = norm(x-xp) = sqrt( sum_j (x^j-xp^j)^2 ) */
    cost=DistanceTopologySubset(m,tp,sv,x,xp);

  return(cost);
}

boolean StepLengthGradient(Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xpp,double *xp,double *x,double *xn,double *xnn,
			   Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			   TJacobian *sJ,TStepCost cost,
			   double *u,Tworld *w)
{
  boolean ok=FALSE;

  if ((xp!=NULL)&&(x!=NULL)&&(xn!=NULL))
    {
      double d,epsilon,*v,*g;
      unsigned int k;
  
      epsilon=GetParameter(CT_EPSILON,p);
      k=(unsigned int)GetParameter(CT_N_DOF,p);

      NEW(v,2*m,double);
      g=&(v[m]);
      
      /*  gradient = diff d / diff x1 */
      DifferenceVectorTopologySubset(m,tp,sv,x,xp,g);
      d=Norm(m,g);
      if (d>epsilon)
	{
	  ScaleVector(1.0/d,m,g);

	  /*  gradient = diff d / diff x2 */
	  DifferenceVectorTopologySubset(m,tp,sv,xn,x,v);
	  d=Norm(m,v);
	  if (d>epsilon)
	    {
	      SumVectorScale(m,g,-1.0/d,v,g);
	      ok=TRUE;
	    }
	}
  
      if (ok)
	{
	  /* Project to tangent space: the only feasible motions are in this space */
	  if (k==m)
	    memcpy(u,g,k*sizeof(double));
	  else
	    TMatrixVectorProduct(m,k,GetChartTangentSpace(c),g,u);
	}
  
      free(v);
    }
  return(ok);
}
  
double StepEffort(Tparameters *p,unsigned int *tp,
		  boolean *sv,unsigned int m,
		  double *xp,double *x,double *xn,
		  unsigned int current,
		  Tchart *cp,Tchart *c,Tchart *cn,Tworld *w)
{
  double epsilon,cost;
  double *s;       /* speed vector in ambient space */
  double *coa;     /* control in ambient space */
  double *co;      /* control in tangent space */
  double d;        /* norm of s */
  double *f;       /* force field in ambient space */
  unsigned int k;
  
  if (w==NULL)
    Error("Control effort can not be computed on cuik files");

  /* The computation of the control effort relies on some assumptions that only
     hold when working in full configuration space and not only on a sub-set of 
     it. For instance, the control projects vectors to the tangent space (as
     defined in the full conf. space) and the vectors from a point to the next
     must be close to this tangent space. This is typically the case for paths
     with small steps in conf. space, but not for paths when projected to a
     subspace, even if the steps are small. */
  if (KINEMATIC_SUBSPACE)
    Error("ControlEffort assumes full configuration space (not kinematic sub-space)");
  
  if (current>2)
    Error("Wrong 'current' parameter in StepEffort");
  
  if (current==2)
    cost=0.0;
  else
    {
      /* control effort for going from xp to x */
      epsilon=GetParameter(CT_EPSILON,p);
      k=(unsigned int)GetParameter(CT_N_DOF,p);
      cost=0.0;

      NEW(s,2*m+k,double);
      DifferenceVectorTopologySubset(m,tp,sv,x,xp,s);
      d=Norm(m,s);
      if (d>epsilon)
	{
	  coa=&(s[m]);
	  co=&(s[2*m]);
      
	  ScaleVector(1.0/d,m,s);
      
	  WorldForceField(p,TRUE,xp,&f,w);
	  DifferenceVector(m,s,f,coa); /* c=s-f */
	  if (k==m)
	    cost=GeneralDotProduct(m,coa,coa)*d;
	  else
	    {
	      TMatrixVectorProduct(m,k,GetChartTangentSpace(cp),coa,co);
	      cost=GeneralDotProduct(k,co,co)*d;
	    }
	  
	  free(f);
	}
      else
	cost=d;
  
      free(s);
    }
  return(cost);
}

boolean StepEffortGradient(Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xpp,double *xp,double *x,double *xn,double *xnn,
			   Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
			   TJacobian *SJ,TStepCost cost,
			   double *u,Tworld *w)
{
  boolean ok=FALSE;

  if ((xp!=NULL)&&(x!=NULL)&&(xn!=NULL))
    {
      unsigned int k,j;
      double *g,*f,*fg,*coa,*s,*co,*proj,d,nco,epsilon;

      if (w==NULL)
	Error("Control effort can not be computed on cuik files");
  
      epsilon=GetParameter(CT_EPSILON,p);
      k=(unsigned int)GetParameter(CT_N_DOF,p);
  
      NEW(s,4*m+k,double);
      coa=&(s[m]);
      proj=&(coa[m]);
      g=&(proj[m]);
      co=&(g[m]);

      /*  
         cost(previous->current) = co^T co * d
         with
           co = Phi_p^T (s-f)
           Phi_p -> tangent space at xp
           s = unit speed at xp
           f = force field at xp
           d = distance xp->x  (norm(x-xp))

         diff cost(previous->current) / diff x
            diff cost = diff (co^T co) * d 
                        + co^T co * diff d^T
         with
            diff (co^T co) = 2 * co^T * diff co 
              diff co = Phi_p^T * [ diff s - diff f ]
                diff s = diff (x-xp)/d 
                       = 1/d^2 * [ diff (x-xp) * d - (x-xp) * diff d^T]
                  diff (x-xp) = I_m   (identity of size 'm' with 1's
	                               only in the 'sv' entries)
                  diff d = s
                  diff f = 0
         So summarizing
            diff cost = 2 * co^T * Phi_p^T * [ I_m  -  s * s^T] 
                        + co^T co * s^T
                      = [ 2 * Phi_p * co ]^T * [ I_m  -  s * s^T]
                        + co^T co * s^T
                      = proj^T * [ I_m - s * s^T] + nco * s^T
         with 
            proj = [ 2 * Phi_p * co ]
            nco = co^T co
         The most efficient evaluation of this formula is (avoid the generation
         of large matrices):
            diff cost =  proj^T - [ proj^T * s ] * s^T + nco * s^T
            diff cost =  proj^T + [ nco - proj^T * s ] * s^T 
      */
      /* s = (x-xp) / | x-xp | 
         We store the values in s_i actually since this is the space for this thread */
      DifferenceVectorTopologySubset(m,tp,sv,x,xp,s);
      d=Norm(m,s);
      if (d>epsilon)
	{
	  ScaleVector(1.0/d,m,s);

	  /* co = Phi_p^T * (s-f) */
	  WorldForceField(p,TRUE,xp,&f,w);
	  DifferenceVector(m,s,f,coa);      
	  if (k==m)
	    memcpy(co,coa,k*sizeof(double));
	  else
	    TMatrixVectorProduct(m,k,GetChartTangentSpace(cp),coa,co);

	  /* nco = co^T * co */
	  nco=GeneralDotProduct(k,co,co);

	  /* p = 2 * \Phi_p * co */
	  if (k==m)
	    memcpy(proj,co,m*sizeof(double));
	  else
	    MatrixVectorProduct(m,k,GetChartTangentSpace(cp),co,proj);
	  ScaleVector(2,m,proj);

	  /* g = proj^T (only for the 'sv' entries) */
	  if (sv==NULL)
	    memcpy(g,proj,m*sizeof(double));
	  else
	    {
	      for(j=0;j<m;j++)
		{
		  if (sv[j])
		    g[j]=proj[j];
		  else
		    g[j]=0.0;
		}
	    }
		  
	  /* g -= [ proj_^T * s + nco] * s^T*/
	  SumVectorScale(m,g,nco-GeneralDotProduct(m,proj,s),s,g);

	  free(f);
 
	  ok=TRUE;
	}

      if (ok)
	{
          /*  
             cost(current->next) = co^T co * d
             with
               co = Phi^T (s-f)
               Phi -> tangent space at x
               s = unit speed at x
               f = force field at x
               d = distance x->xn (norm(xn-x))

             diff cost(current->next) / diff x
                diff cost = diff (co^T co) * d 
                            + co^T co * diff d^T
             with
                diff (co^T co) = 2 * co^T * diff co 
                  diff co = Phi^T * [ diff s - diff f ]
                    diff s = diff (xn-x)/d 
                           = 1/d^2 * [ diff (xn-x) * d - (xn-x) * diff d^T]
                      diff (xn-x) = -I_m   (identity of size 'm' with 1's
    		                           only in the 'sv' entries)
                      diff d = -s
                      diff f = H (hessian matix)
             So summarizing
                diff cost = 2 * co^T * Phi_1^T * [ -I_m  +  s * s^T - H * d ] 
                            - co^T co * s^T
                          = [ 2 * Phi_1 * co ]^T * [ -I_m  +  s * s^T - H * d ]
                            - co^T co * s^T
                          = proj^T * [ -I_m + s * s^T - H * d ] - nco * s^T
             with 
                proj = [ 2 * Phi_1 * co ]
                nco = co^T co
             The most efficient evaluation of this formula is (avoid the generation
             of large matrices):
                diff cost = - proj^T + [ proj^T * s -nco ] * s^T - d * pH 
    	     with
	        pH = proj^T*H         

    	     Note that actually Phi would change with x, but we assume it constant
	     (we approximate Phi(x) by Phi at x
          */
	  DifferenceVectorTopologySubset(m,tp,sv,xn,x,s);
	  d=Norm(m,s);
	  if (d<epsilon)
	    ok=FALSE;
	  else
	    {
	      ScaleVector(1/d,m,s);

	      /* co = Phi^T * (s-f) */
	      WorldForceField(p,TRUE,x,&f,w);
	      DifferenceVector(m,s,f,coa);
	      if (k==m)
		memcpy(co,coa,k*sizeof(double));
	      else
		TMatrixVectorProduct(m,k,GetChartTangentSpace(c),coa,co);

	      /* nco = co^T * co */
	      nco=GeneralDotProduct(k,co,co); 

	      /* p = 2 * \Phi * co */
	      if (k==m)
		memcpy(proj,co,m*sizeof(double));
	      else
		MatrixVectorProduct(m,k,GetChartTangentSpace(c),co,proj);
	      ScaleVector(2,m,proj);

	      /* g -= proj^T (only for the 'sv' entries) */
	      if (sv==NULL)
		SumVectorScale(m,g,-1,proj,g);
	      else
		{
		  for(j=0;j<m;j++)
		    {
		      if (sv[j])
			g[j]-=proj[j];
		    }
		}
	  		  
	      /* g += [ proj_^T * s - nco] * s^T*/
	      SumVectorScale(m,g,GeneralDotProduct(m,proj,s)-nco,s,g);

	      /* g -= d * ( proj^T * H ) */
	      WorldForceFieldProjectedGradient(p,TRUE,proj,x,&fg,w);
	      SumVectorScale(m,g,-d,fg,g);

	      free(f);
	      free(fg);
	    }
	}

      if (ok)
	{
	  /* Project to tangent space: the only feasible motions are in this space */
	  if (k==m)
	    memcpy(u,g,k*sizeof(double));
	  else
	    TMatrixVectorProduct(m,k,GetChartTangentSpace(c),g,u);
	}
      
      free(s);
    }
  return(ok);
}

boolean StepCostNumericalGradient(Tparameters *p,unsigned int *tp,
				  boolean *sv,unsigned int m,
				  double *xpp,double *xp,double *x,double *xn,double *xnn,
				  Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
				  TJacobian *sJ,TStepCost cost,
				  double *u,Tworld *w)
{
  boolean ok=FALSE;

  if (x!=NULL)
    {
      double epsilon,st,ct,new_ct,*delta,*newX;
      unsigned int i,k;
  
      epsilon=GetParameter(CT_EPSILON,p);
      k=(unsigned int)GetParameter(CT_N_DOF,p);
  
      st=5*epsilon; /* small step */

      ct=cost(p,tp,sv,m,xpp,xp,x,2,cpp,cp,c,w)+
	 cost(p,tp,sv,m,xp,x,xn,1,cp,cn,c,w)+
	 cost(p,tp,sv,m,x,xn,xnn,0,c,cn,cnn,w);
  
      NEW(delta,k+m,double);
      newX=&(delta[k]);
      for(i=0;i<k;i++)
	delta[i]=0.0;
  
      ok=TRUE;
      for(i=0;((ok)&&(i<k));i++)
	{
	  delta[i]=st;

	  if (Chart2Manifold(p,sJ,delta,tp,NULL,newX,c)==INF)
	    ok=FALSE;
	  else
	    {
	      /* newCost using 'c' as an approximation of the chart at newX */
	      new_ct=cost(p,tp,sv,m,xpp,xp,newX,2,cpp,cp,c,w)+
		     cost(p,tp,sv,m,xp,newX,xn,1,cp,c,cn,w)+
		     cost(p,tp,sv,m,newX,xn,xnn,0,c,cn,cnn,w);
	  
	      u[i]=(new_ct-ct)/st;
	  
	      delta[i]=0.0;
	    }
	}

      free(delta);
    }
  return(ok);
}

inline double CombineCosts(TStepCost c1,TStepCost c2,
			   Tparameters *p,unsigned int *tp,
			   boolean *sv,unsigned int m,
			   double *xp,double *x,double *xn,
			   unsigned int current,
			   Tchart *cp,Tchart *c,Tchart *cn,Tworld *w)
{
  return(c1(p,tp,sv,m,xp,x,xn,current,cp,c,cn,w)+
	 c2(p,tp,sv,m,xp,x,xn,current,cp,c,cn,w));
}

inline boolean CombineGradients(TStepCostGradient g1,
				TStepCostGradient g2,
				Tparameters *p,unsigned int *tp,
				boolean *sv,unsigned int m,
				double *xpp,double *xp,double *x,double *xn,double *xnn,
				Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
				TJacobian *sJ,TStepCost cost,
				double *u,Tworld *w)
{
  boolean ok;
  unsigned int k;
  double *ud;

  k=(unsigned int)GetParameter(CT_N_DOF,p);
  NEW(ud,k,double);

  ok=g1(p,tp,sv,m,
	xpp,xp,x,xn,xnn,
	cpp,cp,c,cn,cnn,
	sJ,StepLength,u,w);

  if (ok)
    {
      ok=g2(p,tp,sv,m,
	    xpp,xp,x,xn,xnn,
	    cpp,cp,c,cn,cnn,
	    sJ,StepDispersion,ud,w);
      if (ok)
	SumVector(k,u,ud,u);
    }
  
  free(ud);
  
  return(ok);
}

inline double LengthAndDispersion(Tparameters *p,unsigned int *tp,
				  boolean *sv,unsigned int m,
				  double *xp,double *x,double *xn,
				  unsigned int current,
				  Tchart *cp,Tchart *c,Tchart *cn,Tworld *w)
{
  return(CombineCosts(StepLength,StepDispersion,
		      p,tp,sv,m,xp,x,xn,current,cp,c,cn,w));
}

inline boolean LengthAndDispersionGradient(Tparameters *p,unsigned int *tp,
					   boolean *sv,unsigned int m,
					   double *xpp,double *xp,double *x,double *xn,double *xnn,
					   Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
					   TJacobian *sJ,TStepCost cost,
					   double *u,Tworld *w)
{
  return(CombineGradients(StepLengthGradient,StepDispersionGradient,
			  p,tp,sv,m,
			  xpp,xp,x,xn,xnn,
			  cpp,cp,c,cn,cnn,
			  sJ,StepLength,u,w));
}


inline double EffortAndDispersion(Tparameters *p,unsigned int *tp,
				  boolean *sv,unsigned int m,
				  double *xp,double *x,double *xn,
				  unsigned int current,
				  Tchart *cp,Tchart *c,Tchart *cn,Tworld *w)
{
  return(CombineCosts(StepEffort,StepDispersion,
		      p,tp,sv,m,xp,x,xn,current,cp,c,cn,w));
}

inline boolean EffortAndDispersionGradient(Tparameters *p,unsigned int *tp,
					   boolean *sv,unsigned int m,
					   double *xpp,double *xp,double *x,double *xn,double *xnn,
					   Tchart *cpp,Tchart *cp,Tchart *c,Tchart *cn,Tchart *cnn,
					   TJacobian *sJ,TStepCost cost,
					   double *u,Tworld *w)
{
  return(CombineGradients(StepEffortGradient,StepDispersionGradient,
			  p,tp,sv,m,
			  xpp,xp,x,xn,xnn,
			  cpp,cp,c,cn,cnn,
			  sJ,StepLength,u,w));
}


double PathEffort(Tparameters *p,
		  unsigned int m,unsigned int np,double **point,
		  Tworld *w)
{
  TAtlasBase wb;
  unsigned int i;
  unsigned int ms;
  double cost;
  double **pointS;
  Tbox domain;
  unsigned int *tp;
  unsigned int k;
  double e,ce,r;
  Tchart *c;
  TJacobian sJ;
  boolean *sv;
  double *ct;
  
  if (np<2)
    Error("Too short path in PathEffort");

  CS_WD_FROM_WORLD(w,&wb);

  GetWorldSimpInitialBox(p,&domain,w);
  ms=GetWorldSimpTopology(p,&tp,w);

  if (KINEMATIC_SUBSPACE)
    WorldSimpKinematicVars(p,&sv,w);
  else
    sv=NULL;
  
  /* simplify the input points and generate a chart on each
     one of the simplified points */
  NEW(pointS,np,double*);
  k=(unsigned int)GetParameter(CT_N_DOF,p);
  if (k==0)
    {
      k=WorldManifoldDimension(p,point[0],w);
      ChangeParameter(CT_N_DOF,(double)k,p);
    }
  e=GetParameter(CT_E,p);
  ce=GetParameter(CT_CE,p);
  r=GetParameter(CT_R,p);
  GetWorldSimpJacobian(p,&sJ,w);  
  NEW(c,np,Tchart);
  NEW(ct,np,double);
  
  #pragma omp parallel for private(i) schedule(dynamic)
  for(i=0;i<np;i++)
    {
      double *od;
      
      /* recover the dummy variables from the system ones
         for the point in original system */
      RegenerateWorldSolutionPoint(p,point[i],&od,w);
      /* Get the point in the simplified form */
      WorldGenerateSimplifiedPoint(p,od,&(pointS[i]),w);
      free(od);
      
      if (InitTrustedChart(p,TRUE,&domain,tp,
			   ms,k,pointS[i],e,ce,r,
			   &sJ,&wb,&(c[i]))!=0)
	Error("Can not init a chart in a path step");
    }
  
  #pragma omp parallel for private(i) schedule(dynamic)
  for(i=1;i<np;i++)
    ct[i]=StepEffort(p,tp,sv,ms,
		     pointS[i-1],pointS[i],NULL,
		     1,
		     &(c[i-1]),&(c[i]),NULL,
		     w);
  
  cost=0.0;
  for(i=1;i<np;i++)
    cost+=ct[i];
      
  #pragma omp parallel for private(i) schedule(dynamic)
  for(i=0;i<np;i++)
    {
      free(pointS[i]);
      DeleteChart(&(c[i]));
    }
  free(ct);
  free(pointS);
  free(c);
  DeleteJacobian(&sJ);
  DeleteBox(&domain);
  free(tp);
  if (sv!=NULL)
    free(sv);
  
  return(cost);
}

int cmpUInt(const void *a,const void *b)
{
  int out;

  out=0;

  if ((*(unsigned int *)a)<(*(unsigned int *)b))
    out=-1;
  else
    {
      if ((*(unsigned int *)a)>(*(unsigned int *)b))
	out=+1;
    }
  return(out);
}

void ShortcutSmooth(Tparameters *pr,boolean *sv,Tstatistics *stime,
		    unsigned int *np,double ***point,TAtlasBase *w)
{
  unsigned int c,g,b,i,k,m,s,ne;
  double ll,nl;
  unsigned int newNS,lastNS,lastS;
  boolean pathOk,collision,done;
  double **newPath,**lastPath;
  unsigned int *tp;
  Tbox domain;
  TJacobian sJ;

  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&domain,w);
  m=CS_WD_GET_SIMP_TOPOLOGY(pr,&tp,w);
  ne=m-(unsigned int)GetParameter(CT_N_DOF,pr);
  CS_WD_INIT_CD(pr,1,w);
  CS_WD_GET_SIMP_JACOBIAN(pr,&sJ,w);

  //fprintf(stderr,"Initial num steps: %u\n",*np);
  c=0; /* current */
  while(c<*np-1)
    {
      /* dichotomic search of the largest cut possible from l and up to the end of the path*/      
      /* 'g' and 'b' provide a lower/upper bound the index of the futhers step that can
         be reached from 'l' without any collision. This searched index is 's' */
      g=c+1;   /* last known good step (step we can directly connect from 'c') */
      b=*np-1; /* last bad step (step that can not be directly connected from 'c') */
      s=g;
      pathOk=FALSE;
      lastPath=NULL;
      done=FALSE;
      while (!done)
	{
	  s=(g+b)/2;
	  //fprintf(stderr,"[%u - %u - %u]\n",g,s,b);

	  ll=PathLength(tp,sv,m,s-c+1,&((*point)[c]));
	  
	  nl=DEFAULT_CONNECT(pr,tp,sv,&domain,m,ne,(*point)[c],(*point)[s],ll,
			     TRUE,&sJ,&pathOk,&collision,NULL,
			     &newNS,&newPath,w);
	  
	  //nl=10000;pathOk=FALSE;
	  if (pathOk)
	    {
	      /* keep the last valid path */
	      if (lastPath!=NULL)
		{
		  for(i=0;i<lastNS;i++)
		    free(lastPath[i]);
		  free(lastPath);
		}
	      lastNS=newNS;
	      lastPath=newPath;
	      lastS=s;

	      // fprintf(stderr,"  [%u %u] good\n",c,s);
	      if (s==g) /*[g,b] has size 0 or 1*/
		done=TRUE;
	      else
		g=s+1; /* the searched index is larger than 's' */
	    }
	  else
	    {
	      // fprintf(stderr,"  [%u %u] blocked (%u)\n",c,s,collision);
	      if (s==g) /*[g,b] has size 0 or 1*/
		done=TRUE;
	      else
		b=s-1; /* the searched index is lower than 's' */
	    }
	}
      
      //fprintf(stderr,"Test %u->%u : steps %u->%u  length %g->%g\n",c,lastS,lastS-c+1,lastNS,ll,nl);
      if ((lastPath!=NULL)&&(c<lastS-1)&&(lastNS<lastS-c+1)&&(nl<ll)) /* replace only if theres is a minimum gap and the num
      							 	         of steps of the new path is lower */
	{
	  // fprintf(stderr,"Shorcut from %u to %u in %u steps (%u) ",c,lastS,lastNS,lastS-c+1);
		      
	  /* replace segment c->lastS with the new path */
	  for(i=c+1;i<lastS;i++)
	    free((*point)[i]);

	  for(i=0,k=c+1;i<lastNS;i++,k++)
	    (*point)[k]=lastPath[i];
	  free(lastPath);
	      
	  for(i=lastS,k=c+1+lastNS;i<*np;i++,k++)
	    (*point)[k]=(*point)[i];

	  *np=c+1+lastNS+(*np-lastS);
	  c=c+1+lastNS;

	  fprintf(stderr,"Steps: %u  Path length %g  Time: %g\n",*np,
		  PathLength(tp,sv,m,*np,*point),GetElapsedTime(stime));
	}
      else
	{
	  if (lastPath!=NULL)
	    DeleteSamples(lastNS,lastPath);
	  /* continue from 'b' */
	  c=lastS;
	}
    }
  DeleteJacobian(&sJ);
  free(tp);
  DeleteBox(&domain);
}

void RandomSmooth(Tparameters *pr,unsigned int nCores,unsigned int maxIterations,
		  boolean *sv,Tstatistics *stime,
		  unsigned int *np,double ***point,TAtlasBase *w)
{
  unsigned int s,n,i,n1,n2,k,ne;
  double nl,pl;
  unsigned int lns;
  double **lpath;
  unsigned int m;
  Tbox domain;
  unsigned int *tp;
  double **newPoint;
  unsigned int nnp;
  boolean reached,collision;
  unsigned int *step,*newStep,j,dnCores,*localLength,*newLocalLength,*newLocalNS;
  unsigned int *first,*middle,*last;
  boolean *localPathOK;
  double ***newLocalPath;
  unsigned int nCuts;
  TJacobian sJ;

  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&domain,w);
  m=CS_WD_GET_SIMP_TOPOLOGY(pr,&tp,w);
  ne=m-(unsigned int)GetParameter(CT_N_DOF,pr);
  CS_WD_INIT_CD(pr,nCores,w);
  CS_WD_GET_SIMP_JACOBIAN(pr,&sJ,w); /* depending on the ConnectSamples method this might be
				        not used. */
  
  if (nCores>1)
    {
      dnCores=2*nCores;
      NEW(step,dnCores,unsigned int);
      NEW(newStep,nCores,unsigned int);
      NEW(first,nCores,unsigned int);
      NEW(middle,nCores,unsigned int);
      NEW(last,nCores,unsigned int);
      NEW(localLength,nCores,unsigned int);
      NEW(localPathOK,nCores,boolean);
      NEW(newLocalLength,nCores,unsigned int);
      NEW(newLocalNS,nCores,unsigned int);
      NEW(newLocalPath,nCores,double**);
    }

  n=(*np);
  for (s=0;s<maxIterations*n;s++)
    {
      if (nCores>1)
	{
	  /* Select the start/end of the tentative shortcuts (note that we can have repeated random numbers!) */
	  /* It is not convenient to process in parallel too many shorctus since then all shortcuts are
	     small which results in poor path improvement. */
	  nCuts=randomMax(nCores-2)+1; 
	  for(j=0;j<2*nCuts;j++)
	    step[j]=randomMax(*np-1);
	  qsort(step,2*nCuts,sizeof(unsigned int),cmpUInt);

	  /* Compute the possible shorcuts */
          #pragma omp parallel for private(j,n1,n2,collision) schedule(static) if(nCores>1)
	  for(j=0;j<nCuts;j++)
	    {
	      n1=step[2*j];
	      n2=step[2*j+1];

	      /* 
		 The path is split in 'nCuts' different segments. For each
		 segment first[j] is the first element in the segment,
		 middle[j] is the element just after the segment to (potentially)
		 improve and last[j] is the last element included in the segment.
	      */
	      first[j]=n1+1;
	      middle[j]=n2+(n1<n2 ? 0:1); /* if n1==n2, n1 belongs to the previous segment, skip it */
	      last[j]=(j==nCuts-1?(*np)-1:step[2*j+2]);

	      if (first[j]<middle[j])
		{
		  /* We hava at least one point in the segment to optimize */
		  localLength[j]=PathLength(tp,sv,m,n2-n1+1,&((*point)[n1]));
		  newLocalLength[j]=DEFAULT_CONNECT(pr,tp,sv,&domain,m,ne,(*point)[n1],(*point)[n2],localLength[j],
						    TRUE,&sJ,&(localPathOK[j]),&collision,NULL,
						    &(newLocalNS[j]),&(newLocalPath[j]),w);
		}
	      else
		{
		  localLength[j]=0;
		  newLocalLength[j]=0;
		  localPathOK[j]=FALSE;
		}
	    }
	  /* New number of path steps taking into account the possible new shortcuts */
	  nnp=first[0];
	  for(j=0;j<nCuts;j++)
	    {
	      newStep[j]=nnp;

	      if ((localPathOK[j])&&(newLocalLength[j]<localLength[j]))
		nnp+=newLocalNS[j];
	      else
		nnp+=(middle[j]-first[j]);

	      /* now the connecting segments in betwen the possibly smoothed ones */
	      nnp+=(last[j]-middle[j])+1;
	    }

	  NEW(newPoint,nnp,double*);

	  /* The initial non-smoothed segment */
	  for(i=0;i<first[0];i++)
	    newPoint[i]=(*point)[i];

	  /* now the possibly smoothed segments (in parallel since they store
	     different parts of the new path) */
	  #pragma omp parallel for private(i,j,k) schedule(static) if(nCores>1)
	  for(j=0;j<nCuts;j++)
	    {
	      k=newStep[j];
	      if ((localPathOK[j])&&(newLocalLength[j]<localLength[j]))
		{
		  /* keep the new path segment */
		  for(i=0;i<newLocalNS[j];i++)
		    { newPoint[k]=newLocalPath[j][i]; k++; }

		  /* delete the previous path segment */
		  for(i=step[2*j]+1;i<step[2*j+1];i++)
		    free((*point)[i]);
		}
	      else
		{
		  if (first[j]<middle[j])
		    {
		      /* Delete the new path segment, if any */
		      if (localPathOK[j])
			DeleteSamples(newLocalNS[j],newLocalPath[j]);
			
		      /* keep the previous path segment */
		      for(i=first[j];i<middle[j];i++)
			{ newPoint[k]=(*point)[i]; k++; }
		    }
		}

	      /* The non-smoothed segment till next step (or the tail
		 non-smoothed segment). */
	      for(i=middle[j];i<=last[j];i++)
		{ newPoint[k]=(*point)[i]; k++; }
	    }

	  /* update the path */
	  free(*point);
	  *point=newPoint;
	  *np=nnp;
	}
      else
	{
	  /* nCores==1 */
	  n1=randomMax(*np-2);
	  n2=n1+1+randomMax(*np-2-n1);
	    
	  pl=PathLength(tp,sv,m,n2-n1+1,&((*point)[n1]));	

	  nl=DEFAULT_CONNECT(pr,tp,sv,&domain,m,ne,(*point)[n1],(*point)[n2],pl,
			     TRUE,&sJ,&reached,&collision,NULL,&lns,&lpath,w);
	  /*
	  if (reached)
	    fprintf(stderr,"Test %u->%u. pl:%g  st:%u  -> nl:%g  nst:%u %s\n",n1,n2,pl,n2-n1+2,nl,lns,(((reached)&&(nl<pl))?"(*)":" "));
	  else
	    fprintf(stderr,"Test %u->%u. pl:%g  st:%u  failed \n",n1,n2,pl,n2-n1+1);
	  */
	  if ((reached)&&(nl<pl))
	    {
	      /* Replace the path segment with the new path */

	      /* Concat the sequences in a temporary buffer */
	      nnp=n1+1+lns+(*np-n2); /* new number of points */
	      NEW(newPoint,nnp,double*);
	      k=0;
	      for(i=0;i<=n1;i++)
		{ newPoint[k]=(*point)[i]; k++; }

	      for(i=0;i<lns;i++)
		{ newPoint[k]=lpath[i]; k++; }

	      for(i=n1+1;i<n2;i++)
		free((*point)[i]);
	    
	      for(i=n2;i<*np;i++)
		{ newPoint[k]=(*point)[i]; k++; }
	    
	      /* Replace the points by the new points */
	      free(*point);
	      *point=newPoint;
	      *np=nnp;
	      /* the samples in the path are already pointed from point */
	      free(lpath);
	    }
	  else
	    {
	      if (reached)
		DeleteSamples(lns,lpath);
	    }
	}

      /* Print info for debug only */
      if (s%10==0)
	fprintf(stderr,"Shortcut (%u/%u)  Path steps: %u  Path length %g  Time: %g\n",
		s,n*maxIterations,*np,PathLength(tp,sv,m,*np,*point),GetElapsedTime(stime));
    }

  if (nCores>1)
    {
      free(step);
      free(newStep);
      free(first);
      free(middle);
      free(last);
      free(localLength);
      free(localPathOK);
      free(newLocalLength);
      free(newLocalNS);
      free(newLocalPath);
    }
  DeleteJacobian(&sJ);
  DeleteBox(&domain);
  free(tp);
}

void GradientSmooth(Tparameters *pr,
		    unsigned int nCores,unsigned int maxIterations,
		    boolean *sv,Tstatistics *stime,
		    unsigned int *np,double ***point,
		    TStepCost stepCost,
		    TStepCostGradient stepCostGradient,
		    TAtlasBase *w)
{
  unsigned int i,k,m,n,it;
  double delta,epsilon,e2,e,ce,r;
  Tbox domain;
  TJacobian sJ;
  unsigned int *tp;
  double stepSize,maxStepSize;
  double *ct;           /* Cost of each step */
  Tchart *c;            /* A chart at each point in the path*/
  #if (!APPROXIMATED_CHARTS_IN_GRADIENT)
    Tchart *newc;         /* A chart at each new point in the path (possible replacement for c[.])*/
  #endif
  #if (REMOVE_POINTS)
    boolean *remove;      /* points that can be safely removed */
    unsigned int new_np;  /* new number of points (after trimming points that are too close) */
  #endif
  unsigned int npStart; /* Number of points at start. Used to deallocate space. */
  double **u;           /* Gradient in tangent space */
  double *nu;           /* Squared norm of the gradient at a given path step */
  double **newPoint;    /* New point after the gradient displacement */

  boolean *stalled;     /* Points that must remain fixed */
  double cost,newCost,ng,sc,sa;
  TStepCostGradient gradient;
  boolean done;
  
  k=(unsigned int)GetParameter(CT_N_DOF,pr);
  epsilon=GetParameter(CT_EPSILON,pr);
  e2=epsilon*epsilon;
  delta=GetParameter(CT_DELTA,pr);
  e=GetParameter(CT_E,pr);
  ce=GetParameter(CT_CE,pr);
  r=GetParameter(CT_R,pr);    
  
  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&domain,w);
  CS_WD_GET_SIMP_JACOBIAN(pr,&sJ,w);  
  CS_WD_GET_SIMP_TOPOLOGY(pr,&tp,w);
  CS_WD_INIT_CD(pr,nCores,w);
  
  GetJacobianSize(&n,&m,&sJ); /* 'n' not used */

  if (stepCostGradient!=NULL)
    gradient=stepCostGradient;
  else
    gradient=StepCostNumericalGradient;
  
  /* Apply gradient-based length reduction */
  /* Allocate memory for the minimization process */
  NEW(ct,*np,double);        /* cost of each step */
  NEW(c,*np,Tchart);         /* chart at x_i */
  #if (!APPROXIMATED_CHARTS_IN_GRADIENT)
    NEW(newc,*np,Tchart);      /* chart at temptative x_i */
  #endif
  #if (REMOVE_POINTS)
    NEW(remove,*np,boolean);
  #endif
  NEW(u,*np,double*);        /* gradient at x_i (in tangent space) */
  NEW(nu,*np,double);        /* squared norm of u */
  NEW(newPoint,*np,double*); /* new point after gradient motion */ 
  NEW(stalled,*np,boolean);  /* TRUE for points that can not move */

  #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
  for(i=0;i<*np;i++)
    {
      /* allocate space */
      NEWZ(u[i],k,double);
      NEW(newPoint[i],m,double);
      
      /* Initialize the distance charts over points */
      if (InitTrustedChart(pr,TRUE,&domain,tp,
			   m,k,(*point)[i],e,ce,r,
			   &sJ,w,&(c[i]))!=0)
	Error("Can not define a chart on a path step");

      /* default values */
      stalled[i]=FALSE;
      ct[i]=0.0;
      nu[i]=0.0;
      #if (REMOVE_POINTS)
        remove[i]=FALSE;
      #endif
    }
  npStart=*np; /* store the number of points to deallocate */
  
  /* The start/end of the path have to remain fixed */
  stalled[0]=TRUE;
  stalled[*np-1]=TRUE;

  done=FALSE;
  maxStepSize=2*delta;
  stepSize=delta;
  
  for(it=0;((!done)&&(it<maxIterations));it++)
    {
     #if (REMOVE_POINTS)
        /* try to reduce the number of points in the path. This speeds up the
           computation and helps to reduce the cost (if length-related). This
	   is only robust if we penalize the uneven distribution of points
	   along the smoothed path. */
        remove[0]=FALSE;
	for(i=1;i<*np-1;i++)
	  remove[i]=((!stalled[i])&&(!remove[i-1])&&
		     (DistanceTopology(m,tp,(*point)[i-1],(*point)[i+1])<delta));
	remove[*np-1]=FALSE;
	
	new_np=1; /* point[0] is keep for sure */
	for(i=1;i<*np;i++)
	  {
	    if (remove[i])
	      DeleteChart(&(c[i]));
	    else
	      {
		/* info(new_np) <- info(i) */
		if (new_np!=i)
		  {
		    stalled[new_np]=stalled[i];
		    memcpy((*point)[new_np],(*point)[i],m*sizeof(double));
		    CopyChart(&(c[new_np]),&(c[i]));
		    DeleteChart(&(c[i]));
		  }
		new_np++;
	      }
	  }
	*np=new_np; 
      #endif
      
      /* Compute the gradient */
      #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
      for(i=1;i<*np-1;i++)
	{
	  if (stalled[i])
	    nu[i]=0.0;
	  else
	    {
	      /*
	      StepCostNumericalGradient(pr,tp,sv,m,
				        (i<2?NULL:(*point)[i-2]),
					(*point)[i-1],(*point)[i],(*point)[i+1],
					(i>*np-3?NULL:(*point)[i+2]),
					(i<2?NULL:&(c[i-2])),
					&(c[i-1]),&(c[i]),&(c[i+1]),
					(i>*np-3?NULL:&(c[i+2])),
					&sJ,stepCost,
					u[i],GET_WORLD(w));
	      PrintVector(stderr,"u_numeric ",k,u[i]);
	      
	      stepCostGradient(pr,tp,sv,m,
			       (i<2?NULL:(*point)[i-2]),
			       (*point)[i-1],(*point)[i],(*point)[i+1],
			       (i>*np-3?NULL:(*point)[i+2]),
			       (i<2?NULL:&(c[i-2])),
			       &(c[i-1]),&(c[i]),&(c[i+1]),
			       (i>*np-3?NULL:&(c[i+2])),
			       &sJ,stepCost,
			       u[i],GET_WORLD(w));
	       PrintVector(stderr,"u_analitic",k,u[i]);
	       fprintf(stderr,"\n");
	       if (i>100)
		 exit(0);
	      */

	      /* Evaluate the gradient of the user-provided cost */
	      stalled[i]=!gradient(pr,tp,sv,m,
				   (i<2?NULL:(*point)[i-2]),
				   (*point)[i-1],(*point)[i],(*point)[i+1],
				   (i>*np-3?NULL:(*point)[i+2]),
				   (i<2?NULL:&(c[i-2])),
				   &(c[i-1]),&(c[i]),&(c[i+1]),
				   (i>*np-3?NULL:&(c[i+2])),
				   &sJ,stepCost,
				   u[i],GET_WORLD(w));
	      
	      if (stalled[i])
		nu[i]=0.0;
	      else
		nu[i]=GeneralDotProduct(k,u[i],u[i]); /* squared norm of nu[i] */
	    }
	}

      /* first/last are stalled */
      nu[0]=nu[*np-1]=0.0;
      
      /* Compute the norm of the whole gradient */
      ng=0.0;
      for(i=0;i<*np;i++)
	ng+=nu[i];
      ng=sqrt(ng);
      
      if (ng<(*np)*epsilon)
	{
	  done=TRUE; /* If too small, stop the minimization */
	  fprintf(stderr,"Null gradient\n");
	}
      else
	{
	  /* Compute the current cost (updated as we move the path) */
	  #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
	  for(i=1;i<*np;i++)
	    ct[i]=stepCost(pr,tp,sv,m,
			   (*point)[i-1],(*point)[i],(i<*np-1?(*point)[i+1]:NULL),
			   1,
			   &(c[i-1]),&(c[i]),(i<*np-1?&(c[i+1]):NULL),GET_WORLD(w));
	  
	  cost=0.0;
	  for(i=1;i<*np;i++)
	    cost+=ct[i];
	  
	  stepSize*=2.0;
	  if (stepSize>maxStepSize)
	    stepSize=maxStepSize;
	  
	  /* Print information about the minimization process */
	  if (it%100==0)
	    fprintf(stderr,"Iteration %u  Path steps: %u  Step size: %g  Path cost: %g  Time: %g  Norm g: %.12f\n",
		    it,*np,stepSize,cost,GetElapsedTime(stime),ng);

	  sc=-stepSize/ng;
	  sa=fabs(sc); /* abs value used to scale the norm of the gradient */
	  
	  /* Displace the whole path along the gradient */
	  do {
	    #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
	    for(i=0;i<*np;i++)
	      {
		if (stalled[i])
		  memcpy(newPoint[i],(*point)[i],m*sizeof(double));
		else
		  {
		    ScaleVector(sc,k,u[i]); /* Normalize/Scale */
		    nu[i]*=(sa*sa); /* correct the squared norm of this gradient */
		    
		    if ((nu[i]<e2)||
			(Chart2Manifold(pr,&sJ,u[i],tp,NULL,newPoint[i],&(c[i]))==INF))
		      memcpy(newPoint[i],(*point)[i],m*sizeof(double));
		  }
	      }

	    /* We changed the individual gradients -> change the global norm */
	    ng*=sa; 
	    done=(ng<(*np)*epsilon);
	    if (done)
	      fprintf(stderr,"Can not decrease error\n");
	    
	    if (!done)
	      {
		sc=sa=0.5; /* in next steps, if any, we scale the gradient */
		stepSize*=0.5; /* this will affect future iterations */

		#if (!APPROXIMATED_CHARTS_IN_GRADIENT)
		  /* compute the cost at the modified path */
		  #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
		  for(i=0;i<*np;i++)
		    {
		      if (!stalled[i])
			{
			  /* for fixed points, the chart remains stable */
			  if (InitTrustedChart(pr,TRUE,&domain,tp,
					       m,k,newPoint[i],e,ce,r,
					       &sJ,w,&(newc[i]))!=0)
			    {
			      /* If we can not define a chart in the new point, we fix the point */
			      stalled[i]=TRUE;
			      memcpy(newPoint[i],(*point)[i],m*sizeof(double));
			    }
			}
		    }
		#endif
		
		#pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
		for(i=1;i<*np;i++)
		  {
		    #if (APPROXIMATED_CHARTS_IN_GRADIENT)
		      ct[i]=stepCost(pr,tp,sv,m,
				     newPoint[i-1],newPoint[i],(i<*np-1?newPoint[i+1]:NULL),
				     1,
				     &(c[i-1]),&(c[i]),(i<*np-1?&(c[i+1]):NULL),
				     GET_WORLD(w));
		    #else
		      ct[i]=stepCost(pr,tp,sv,m,
				     newPoint[i-1],newPoint[i],(i<*np-1?newPoint[i+1]:NULL),
				     1,
				     (stalled[i-1]?&(c[i-1]):&(newc[i-1])),
				     (stalled[i]?&(c[i]):&(newc[i])),
				     (i<*np-1?(stalled[i+1]?&(c[i+1]):&(newc[i+1])):NULL),
				     GET_WORLD(w));
		    #endif
		  }
		
		newCost=0;
		for(i=1;i<*np;i++)
		  newCost+=ct[i];

		#if (!APPROXIMATED_CHARTS_IN_GRADIENT)
		if (newCost>cost)
		  {
		    /* if we will iterate once more -> release the newc since we will
		       eventually recompute them */
		    #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
		    for(i=0;i<*np;i++)
		      {
			if (!stalled[i])
			  DeleteChart(&(newc[i]));
		      }
		  }
		#endif
	      }
	    
	  } while((!done)&&(newCost>cost));

	  if (!done)
	    {
	      cost=newCost;

	      /* Update the path and check if any of its steps become
	         stalled (in collision or out of domain). Note that we
	         allow for small penetration (size delta) */
	      #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
	      for(i=0;i<*np;i++)
		{
		  if (!stalled[i])
		    {
		      DeleteChart(&(c[i]));
		      #if (APPROXIMATED_CHARTS_IN_GRADIENT)
		        /* now we have the new set of points -> compute the charts at them */
		        if (InitTrustedChart(pr,TRUE,&domain,tp,
					     m,k,newPoint[i],e,ce,r,
					     &sJ,w,&(c[i]))!=0)
			  {
			    /* If we can not define a chart in the new point,
			       move to the previous point and fix it. */
			    stalled[i]=TRUE;
			    memcpy(newPoint[i],(*point)[i],m*sizeof(double));
			    if (InitTrustedChart(pr,TRUE,&domain,tp,
						 m,k,newPoint[i],e,ce,r,
						 &sJ,w,&(c[i]))!=0)
			      Error("Error redefining a chart?");
			  }
		      #else
		        /* using pointers to charts this would be more efficient but... */
			CopyChart(&(c[i]),&(newc[i]));
			DeleteChart(&(newc[i]));
		      #endif

		      if (!stalled[i])
			{
			  memcpy((*point)[i],newPoint[i],m*sizeof(double));
			  
			  stalled[i]=(!PointInBoxTopology(NULL,FALSE,m,(*point)[i],epsilon,tp,&domain));
			  if (!stalled[i])
			    CS_WD_IN_COLLISION(stalled[i],pr,(*point)[i],NULL,w);
			}
		    }
		}
	    }
	}
    }

  #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
  for(i=0;i<*np;i++)
    DeleteChart(&(c[i]));
  for(i=*np;i<npStart;i++)
    free((*point)[i]);
  for(i=0;i<npStart;i++)
    {
      free(u[i]);
      free(newPoint[i]);
    }
  free(newPoint);
  free(nu);
  free(u);
  free(c);
  free(ct);
  free(stalled);
  #if (!APPROXIMATED_CHARTS_IN_GRADIENT)
    free(newc);
  #endif
  #if (REMOVE_POINTS)
    free(remove);
  #endif

  DeleteBox(&domain);
  free(tp);
  DeleteJacobian(&sJ);
}

void SmoothSamples(Tparameters *pr,boolean parallel,int mode,unsigned int maxIterations,
		   unsigned int ns,double **path,
		   unsigned int *sns,double ***spath,TAtlasBase *w)
{
  unsigned int i,m,np,mp,k;
  double **point;
  double *o,l,delta;
  Tbox domain;
  unsigned int *tp;
  unsigned int sms;
  unsigned int nv,nvs;
  boolean *systemVars;
  Tstatistics stime;  
  unsigned int nCores;
  boolean *sv;
  
  if (ns<3)
    Error("Too small path in SmoothSamples (only paths with at least 3 samples are considered)");

  if (parallel)
    {
      #ifdef _OPENMP
        nCores=omp_get_max_threads();
	if (ns<nCores*3)
	  nCores=1;
      #else
        nCores=1;
      #endif
    }
  else
    nCores=1;

  delta=GetParameter(CT_DELTA,pr);
  k=(unsigned int)GetParameter(CT_N_DOF,pr);
  if (k==0)
    {
      k=CS_WD_MANIFOLD_DIMENSION(pr,path[0],w);
      ChangeParameter(CT_N_DOF,(double)k,pr);
    }
  
  InitStatistics(nCores,0,&stime);

  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,&domain,w);
  
  /* Simplify the path */
  m=CS_WD_GET_SIMP_TOPOLOGY(pr,&tp,w);
  
  if ((!KINEMATIC_SUBSPACE)||(ON_CUIKSYSTEM(w)))
    sv=NULL;
  else
    {
      /* Path length on kinematic variables only */
      if (WorldSimpKinematicVars(pr,&sv,GET_WORLD(w))!=m)
	Error("Missmatch in the number of variables");
    }
  
  mp=ns;
  np=ns;

  NEW(point,mp,double*);
  #pragma omp parallel for private(i) schedule(dynamic) if(nCores>1)
  for(i=0;i<np;i++)
    {
      double *od;
      
      /* recover the dummy variables from the system ones
         for the point in original system */
      CS_WD_REGENERATE_SOLUTION_POINT(pr,path[i],&od,w);
      /* Get the point in the simplified form */
      CS_WD_GENERATE_SIMPLIFIED_POINT(pr,od,&(point[i]),w);

      free(od);
    }
  /********************************************/
  /* Compute the initial lenght */
  l=PathLength(tp,sv,m,np,point);
  fprintf(stderr,"Initial lenght                    : %g\n",l);
  fprintf(stderr,"Number of processing cores        : %u\n",nCores);

  /* If the path is not densily sampled the Euclidean 
     distance between samples is too far from the Geodesic
     one and then the smoothing is not meaningful */
  if ((m!=k)&&(l/(double)np)>2*delta)
    Error("The input path is not dense enough");

  fprintf(stderr,"Path steps                        : %u\n",np);
  switch(mode)
    {
    case SMOOTH_RANDOM:
      fprintf(stderr,"Smooth method                     : RANDOM\n");
      fprintf(stderr,"Measure to optimize               : Path length\n");
      RandomSmooth(pr,nCores,maxIterations,sv,&stime,&np,&point,w);
      break;
    case SMOOTH_GRADIENT:
      fprintf(stderr,"Smooth method                     : GRADIENT\n");
      #if (DISPERSION)
        fprintf(stderr,"Measure to optimize               : Path length + dispersion\n");
        GradientSmooth(pr,nCores,maxIterations,sv,&stime,&np,&point,
		       LengthAndDispersion,LengthAndDispersionGradient,w);
      #else
        fprintf(stderr,"Measure to optimize               : Path length\n");
	GradientSmooth(pr,nCores,maxIterations,sv,&stime,&np,&point,
		       StepLength,StepLengthGradient,w);
      #endif
      break;
    case SMOOTH_SHORTCUT:
      fprintf(stderr,"Smooth method                     : SHORTCUT\n");
      fprintf(stderr,"Measure to optimize               : Path length\n");
      ShortcutSmooth(pr,sv,&stime,&np,&point,w);
      break;
    case SMOOTH_EFFORT:
      fprintf(stderr,"Smooth method                     : GRADIENT\n");
      #if (DISPERSION)
        fprintf(stderr,"Measure to optimize               : Control effort + dispersion\n");
        GradientSmooth(pr,nCores,maxIterations,sv,&stime,&np,&point,
		       EffortAndDispersion,EffortAndDispersionGradient,w);
      #else
        fprintf(stderr,"Measure to optimize               : Control effort\n");
        GradientSmooth(pr,nCores,maxIterations,sv,&stime,&np,&point,
		       StepEffort,StepEffortGradient,w);
      #endif
      break;
    case SMOOTH_DISPERSION:
      fprintf(stderr,"Smooth method                     : GRADIENT\n");
      fprintf(stderr,"Measure to optimize               : Dispersion\n");
      GradientSmooth(pr,nCores,maxIterations,sv,&stime,&np,&point,
		     StepDispersion,StepDispersionGradient,w);
      break;
    default:
      Error("Unknown smoothing method in SmoothSamples");
    }

  if (mode!=SMOOTH_EFFORT)
    fprintf(stderr,"Final length (in simplified system): %g\n",PathLength(tp,sv,m,np,point));

  /********************************************/
  /* The minimization is done, now define the new optimized path */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,w);
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }
  sms=np;
  NEW(*spath,sms,double*);
  *sns=0;
  for(i=0;i<np;i++)
    {
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,point[i],&o,w);
      AddSample2Samples(nv,o,nvs,systemVars,&sms,sns,spath);
      free(o);
    }
  free(systemVars);

  /********************************************/
  /* Release the data used to represent the path */
  for(i=0;i<np;i++)
    free(point[i]);
  free(point);
  if (sv!=NULL)
    free(sv);
  free(tp);

  DeleteBox(&domain);

  fprintf(stderr,"Optimization time: %g\n",GetElapsedTime(&stime));
  DeleteStatistics(&stime);
}

void ConcatSamples(unsigned int nvs,
		   unsigned int ns1,double **path1,
		   unsigned int ns2,double **path2,
		   unsigned int *ns,double ***path)
{
  unsigned int i;

  *ns=(ns1+ns2);
  NEW((*path),*ns,double*);
  for(i=0;i<ns1;i++)
    {
      NEW((*path)[i],nvs,double);
      memcpy((*path)[i],path1[i],nvs*sizeof(double));
    }
  for(i=0;i<ns2;i++)
    {
      NEW((*path)[ns1+i],nvs,double);
      memcpy((*path)[ns1+i],path2[i],nvs*sizeof(double));
    }
}

void ReverseConcatSamples(unsigned int nvs,
			  unsigned int ns1,double **path1,
			  unsigned int ns2,double **path2,
			  unsigned int *ns,double ***path)
{
  unsigned int i;
  signed int s;

  *ns=(ns1+ns2);

  NEW((*path),*ns,double*);
  for(i=0;i<ns1;i++)
    {
      NEW((*path)[i],nvs,double);
      memcpy((*path)[i],path1[i],nvs*sizeof(double));
    }
  s=ns2-1;
  for(i=0;i<ns2;i++)
    {
      NEW((*path)[ns1+i],nvs,double);
      memcpy((*path)[ns1+i],path2[s],nvs*sizeof(double));
      s--;
    }
}

void ReverseConcatTrajectories(unsigned int nvs,unsigned int da,
			       unsigned int ns1,double **path1,double **action1,double *time1,
			       unsigned int ns2,double **path2,double **action2,double *time2,
			       unsigned int *ns,double ***path,double ***action,double **time)
{
  if ((time1==NULL)||(time2==NULL))
    {
      if (time1!=time2)  /* both should be null */
	Error("Inconsistent input trajectories in ReverseConcatTrajectories");
      
      *action=NULL;
      *time=NULL;
      ReverseConcatSamples(nvs,ns1,path1,ns2,path2,ns,path);
    }
  else
    {
      unsigned int i;
      signed int s;
      
      if (((action1==NULL)&&(action2!=NULL))||
	  ((action1!=NULL)&&(action2==NULL)))
	Error("Inconsistent input trajectories in ReverseConcatTrajectories");
      
      *ns=(ns1+ns2);
  
      NEW((*path),*ns,double*);
      if (da==0)
	*action=NULL; /* autonomous system */
      else
	NEW((*action),*ns,double*);
      
      NEW((*time),*ns,double);
      
      for(i=0;i<ns1;i++)
	{
	  NEW((*path)[i],nvs,double);
	  memcpy((*path)[i],path1[i],nvs*sizeof(double));
	  if (da>0)
	    {
	      NEW((*action)[i],da,double);
	      memcpy((*action)[i],action1[i],da*sizeof(double));
	    }
	  (*time)[i]=time1[i];
	}
      /* We put NULL action: This should be fixed and use
         an inverse dynamics to compute the correct action. */
      NEW((*path)[ns1],nvs,double);
      memcpy((*path)[ns1],path2[ns2-1],nvs*sizeof(double));
      if (da>0)
	{
	  NEWZ((*action)[ns1],da,double);
	}
      /* The time in the transition is the average of the
         previous and the next steps */
      //(*time)[ns1]=(time1[ns1-1]+time2[ns2-1])/2.0;
      /* Negative time to mark the connection */
      (*time)[ns1]=-1.0;
      /**/
      s=ns2-2;
      for(i=1;i<ns2;i++)
	{
	  NEW((*path)[ns1+i],nvs,double);
	  memcpy((*path)[ns1+i],path2[s],nvs*sizeof(double));
	  if (da>0)
	    {
	      NEW((*action)[ns1+i],da,double);
	      memcpy((*action)[ns1+i],action2[s+1],da*sizeof(double));
	    }
	  (*time)[ns1+i]=time2[s+1];
	  s--;
	}
    }
}

void ReverseSamples(unsigned int ns,double **path)
{
  if (ns>0)
    {
      unsigned int s,k;
      double *step;
      
      s=ns-1;
      k=0;
      while(s>k)
	{
	  step=path[s];
	  path[s]=path[k];
	  path[k]=step;
	  s--;
	  k++;
	}
    }
}

unsigned int ReadOneSample(Tparameters *p,char *fname,unsigned int nvs,double **s)
{
  unsigned int i;
  Tfilename fsamples;
  FILE *f;
  unsigned int r;

  NEW(*s,nvs,double);

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r==REP_JOINTS)
    CreateFileName(NULL,fname,NULL,JOINTS_EXT,&fsamples);
  else
    CreateFileName(NULL,fname,NULL,LINKS_EXT,&fsamples);
  f=fopen(GetFileFullName(&fsamples),"r");
  if (!f)
    Error("Could not open sample file");

  fprintf(stderr,"Reading samples from              : %s\n",GetFileFullName(&fsamples));
  for(i=0;i<nvs;i++)
    {
      if (fscanf(f,"%lf",&((*s)[i]))!=1)
	Error("Sample in file with less values than system variables");
    } 
  fclose(f);

  DeleteFileName(&fsamples);

  return(nvs);
}

unsigned int ReadTwoSamples(Tparameters *p,char *fname,unsigned int nvs,double **s1,double **s2)
{
  unsigned int i;
  Tfilename fsamples;
  FILE *f;
  unsigned int r;
  double epsilon;

  NEW(*s1,nvs,double);
  NEW(*s2,nvs,double);

  epsilon=GetParameter(CT_EPSILON,p);
  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r==REP_JOINTS)
    CreateFileName(NULL,fname,NULL,JOINTS_EXT,&fsamples);
  else
    CreateFileName(NULL,fname,NULL,LINKS_EXT,&fsamples);
  f=fopen(GetFileFullName(&fsamples),"r");
  if (!f)
    Error("Could not open sample file");
  
  fprintf(stderr,"Reading samples from              : %s\n",GetFileFullName(&fsamples));
  for(i=0;i<nvs;i++)
    {
      if (fscanf(f,"%lf",&((*s1)[i]))!=1)
	Error("Sample in file with less values than system variables");
    } 
  for(i=0;i<nvs;i++)
    {
      if (fscanf(f,"%lf",&((*s2)[i]))!=1)
	Error("Sample in file with less values than system variables");
    }
  fclose(f);

  if (Distance(nvs,*s1,*s2)<epsilon)
    Error("Repeated sample in input file");
  
  DeleteFileName(&fsamples);

  return(nvs);
}

void SaveSamplesInt(Tfilename *fpath,unsigned int nvs,
		    unsigned int ns,double **path,
		    unsigned int da,double **action,double *time)
{ 
  Tbox bp;
  unsigned int i,j;
  FILE *f;

  f=fopen(GetFileFullName(fpath),"w");
  if (!f)
    Error("Could not open file to store the solution path on mainfold");

  fprintf(stderr,"Writing solution path to          : %s\n",GetFileFullName(fpath));

  fprintf(f,"%u %u %u %u\n",ns,nvs,da,(time==NULL?0:1));
  for(i=0;i<ns;i++)
    { 
      if ((action!=NULL)&&(da>0))
	{
	  if (action[i]==NULL)
	      Error("Incomplete Trajectory");
	  for(j=0;j<da;j++)
	    fprintf(f,"%.12f ",action[i][j]);
	  fprintf(f,"\n");
	}
      
      if (time!=NULL)
	{
	  if (time[i]>0.0)
	    fprintf(f,"%.12f\n",time[i]);
	  else
	    fprintf(f,"0\n");
	}
      
      for(j=0;j<nvs;j++)
	fprintf(f,"%.12f ",path[i][j]);
      fprintf(f,"\n");
    }

  fprintf(f,"\n\n\n");
  
  /*We will also write the path in the form of boxes (for animation)*/
  for(i=0;i<ns;i++)
    {
      /* The action/time information is actually not used -> do not store it */
      InitBoxFromPoint(nvs,path[i],&bp);
      PrintBox(f,&bp);
      DeleteBox(&bp);
    }

  fclose(f);
}


void SaveSamples(char *fname,char *suffix,unsigned int nvs,
		 unsigned int ns,double **path)
{
  Tfilename fpath;

  if (suffix!=NULL)
    CreateFileName(NULL,fname,suffix,SOL_EXT,&fpath);
  else
    CreateFileName(NULL,fname,"_path",SOL_EXT,&fpath);

  SaveSamplesInt(&fpath,nvs,ns,path,0,NULL,NULL);

  DeleteFileName(&fpath);
}

void SaveTrajectory(char *fname,char *suffix,unsigned int nvs,
		    unsigned int ns,double **path,
		    unsigned int da,double **action,double *time)
{
  Tfilename fpath;

  if (suffix!=NULL)
    CreateFileName(NULL,fname,suffix,SOL_EXT,&fpath);
  else
    {
      if (time!=NULL)
	CreateFileName(NULL,fname,"_traj",SOL_EXT,&fpath);
      else
	CreateFileName(NULL,fname,"_path",SOL_EXT,&fpath);	
    }

  SaveSamplesInt(&fpath,nvs,ns,path,da,action,time);

  DeleteFileName(&fpath);
}

void SaveSamplesN(char *fname,boolean smooth,unsigned int n,unsigned int nvs,
		  unsigned int ns,double **path)
{
  Tfilename fpath;
  char s[100];

  if (smooth)
    sprintf(s,"_spath_%u",n);
  else
    sprintf(s,"_path_%u",n);
  
  CreateFileName(NULL,fname,s,SOL_EXT,&fpath);

  SaveSamplesInt(&fpath,nvs,ns,path,0,NULL,NULL);

  DeleteFileName(&fpath);
}


boolean LoadSamples(Tfilename *fname, unsigned int *nvs,
		    unsigned int *ns,double ***path)
{
  FILE *f;
  Tlist lb;
  Tbox *b;
  Titerator i;
  unsigned int k;

  f=fopen(GetFileFullName(fname),"r");
  if (f)
    {
      /*Load the path from a _path.sol file */
      fprintf(stderr,"Loading solution points from      : %s\n",GetFileFullName(fname));

      /* We take advantage that the sample list is stored as a box list to read it.
         This reads the file as a path even if it is a trajectory (i.e., if it 
	 includes times and actions). */
      ReadListOfBoxes(GetFileFullName(fname),&lb);

      *ns=ListSize(&lb);
      NEW(*path,*ns,double *);
      InitIterator(&i,&lb);
      First(&i);
      k=0;
      while(!EndOfList(&i))
	{
	  b=(Tbox *)GetCurrent(&i);
	  if (k==0)
	    *nvs=GetBoxNIntervals(b); 
	  else
	    {
	      if (*nvs!=GetBoxNIntervals(b))
		Error("Incongruent size of step in path");
	    }
	  NEW((*path)[k],*nvs,double);
	  GetBoxCenter(NULL,(*path)[k],b);
	  Advance(&i);
	  k++;
	}
      fclose(f);
      DeleteListOfBoxes(&lb);

      return(TRUE);
    }
  else
    {
      *path=NULL;
      return(FALSE);
    }
      
}

boolean LoadTrajectory(Tfilename *fname, unsigned int *nvs,
		       unsigned int *ns,double ***path,
		       unsigned int *da,
		       double ***action,double **time)
{
  FILE *f;
  unsigned int i,j,hasT;
  boolean ok;

  /* default output */
  *path=NULL;
  *action=NULL;
  *time=NULL;
  
  f=fopen(GetFileFullName(fname),"r");
  if (f)
    {
      char *line=NULL;
      size_t len = 0;
     
      fprintf(stderr,"Loading trajectory from           : %s\n",GetFileFullName(fname));
      
      if (getline(&line,&len,f)<0)
	ok=FALSE;
      else
	{
	  if (sscanf(line,"%u %u %u %u",ns,nvs,da,&hasT)!=4)
	    ok=FALSE;
	  else
	    {
	      if ((*ns==0)||(*nvs==0))
		Error("Wrong trajectory file (empty)");
      
	      if (!hasT)
		/* the input file is not a trajectory file but probably 
		   just a path file */
		ok=FALSE;
	      else
		{
		  NEW(*path,*ns,double *);
		  
		  /* autonomous systems may have no action */
		  if (*da>0)
		    {NEW(*action,*ns,double*);}
		  else
		    *action=NULL;
		  
		  NEW(*time,*ns,double);
	  
		  for(i=0;i<*ns;i++)
		    {
		      if (*da>0)
			{
			  NEW((*action)[i],*da,double);
			  for(j=0;j<*da;j++)
			    fscanf(f,"%lf",&((*action)[i][j]));
			}
	      
		      fscanf(f,"%lf",&((*time)[i]));
	      
		      NEW((*path)[i],*nvs,double);
		      for(j=0;j<*nvs;j++)
			fscanf(f,"%lf",&((*path)[i][j]));
		    }
		  fclose(f);
      
		  ok=TRUE;
		}
	    }
	}
      if (line!=NULL)
	free(line);
    }
  else
    ok=FALSE;
  
  return(ok);
}

void SparsifyTrajectory(double tm,unsigned int **id,unsigned int *ns,double **path,
			double **action,double *time)
{
  unsigned int i,k,m;
  double ct;

  NEW(*id,*ns,unsigned int);
  (*id)[0]=0;
  ct=0.0;
  k=1;
  m=*ns-1;
  for(i=1;i<m;i++)
    {
      if (ct+time[i]<tm)
	{
	  free(path[i]);
	  free(action[i]);
	  ct+=time[i];
	}
      else
	{
	  path[k]=path[i];
	  action[k]=action[i];
	  time[k]=ct+time[i];
	  (*id)[k]=i;
	  k++;
	  ct=0.0;
	}
    }
  path[k]=path[m];
  action[k]=action[m];
  time[k]=ct+time[m];
  (*id)[k]=m;
  *ns=k;
}


void PlotSamples(Tparameters *p,Tplot3d *p3d,
		 unsigned int xID,unsigned int yID,unsigned int zID,
		 unsigned int ns,double **path)
{
  unsigned int i;
  double *x,*y,*z;
  Tcolor pathColor;
  double cx,cy,cz;
  double dx,dy,dz;
  #if (PATH_NODES)
    double xc[2],yc[2],zc[2];
    Tcolor blue;
  #endif

  cx=GetParameter(CT_CUT_X,p);
  cy=GetParameter(CT_CUT_Y,p);
  cz=GetParameter(CT_CUT_Z,p);

  NEW(x,ns,double);
  NEW(y,ns,double);
  NEW(z,ns,double);

  for(i=0;i<ns;i++)
    {	      
      /* For the paths we only store system variables */
      x[i]=path[i][xID];
      y[i]=path[i][yID];
      z[i]=path[i][zID];

      CORRECT_POINT_PLOT(cx,cy,cz,x[i],y[i],z[i]);
    }

  /* start */
  NewColor(1,1,0,&pathColor); /*yelow*/
  StartNew3dObject(&pathColor,p3d); 
  PlotSphere(0.02,x[0],y[1],z[2],p3d);
  DeleteColor(&pathColor);
  Close3dObject(p3d);

  /* goal */
  NewColor(1,0,0,&pathColor); /*red*/
  StartNew3dObject(&pathColor,p3d);
  PlotSphere(0.02,x[ns-1],y[ns-1],z[ns-1],p3d);
  DeleteColor(&pathColor);
  Close3dObject(p3d);

  /* the path */
  NewColor(0,1,0,&pathColor); /* green */
  StartNew3dObject(&pathColor,p3d);
  //PlotVect3d(ns,x,y,z,p3d);
  for(i=0;i<ns-1;i++)
    {
      dx=x[i+1]-x[i];
      dy=y[i+1]-y[i];
      dz=z[i+1]-z[i];
      //if (((cx!=0)||(cy!=0)||(cz!=0))&&
      //	  (sqrt(dx*dx+dy*dy+dz*dz)<M_PI))
      if (sqrt(dx*dx+dy*dy+dz*dz)<M_PI)
	PlotVect3d(2,&(x[i]),&(y[i]),&(z[i]),p3d);
    }
  Close3dObject(p3d);
  DeleteColor(&pathColor);

  #if (PATH_NODES)
  if (ns>2)
    {
      NewColor(0,0,1,&blue);
      StartNew3dObject(&blue,p3d);
      for(i=0;i<ns;i++)
	{
	  xc[0]=x[i]-0.01;
	  yc[0]=y[i];
	  zc[0]=z[i];

	  xc[1]=x[i]+0.01;
	  yc[1]=y[i];
	  zc[1]=z[i];

	  PlotVect3d(2,xc,yc,zc,p3d);

	  xc[0]=x[i];
	  yc[0]=y[i]-0.01;
	  zc[0]=z[i];

	  xc[1]=x[i];
	  yc[1]=y[i]+0.01;
	  zc[1]=z[i];

	  PlotVect3d(2,xc,yc,zc,p3d);

	  xc[0]=x[i];
	  yc[0]=y[i];
	  zc[0]=z[i]-0.01;

	  xc[1]=x[i];
	  yc[1]=y[i];
	  zc[1]=z[i]+0.01;

	  PlotVect3d(2,xc,yc,zc,p3d);
	}
  
      DeleteColor(&blue);
      Close3dObject(p3d);  
    }
  #endif

  free(x);
  free(y);
  free(z);
}

void PlotForceField(Tparameters *p,Tplot3d *p3d,
		    unsigned int xID,unsigned int yID,unsigned int zID,
		    Tworld *w,
		    unsigned int ns,double **sols)
{
  unsigned int i,k,nv,nx,ny,nz;
  boolean *systemVars;
  double *fullS,*ff,**f,**s,mg,epsilon;
  double n,maxn,minn; /* to compute the max norm of the force field. */
  Tcolor ffColor;

  mg=2.0*GetParameter(CT_DELTA,p); /* maximum size of the lines 
				      representing the ff */
  epsilon=GetParameter(CT_EPSILON,p);
  
  /* Translate indices from system variables only to 
     the whole set of variables */
  nv=GetWorldSystemVars(&systemVars,w);
  k=0;
  nx=ny=nz=NO_UINT;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	{
	  if (xID==k)
	    nx=i;
	  if (yID==k)
	    ny=i;
	  if (zID==k)
	    nz=i;
	  k++;
	}
    }
  if ((nx==NO_UINT)||(ny==NO_UINT)||(nz==NO_UINT))
    Error("Undefined projection dimension in PlotForceField");

  /* Compute the projection of the pionts where to evalute the
     force filed and the projection of the force field at 
     each of these points. */
  NEW(s,ns,double*);
  NEW(f,ns,double*);
  maxn=0;
  minn=INF;
  for(i=0;i<ns;i++)
    {
      NEW(s[i],3,double);
      RegenerateWorldSolutionPoint(p,sols[i],&fullS,w);
      s[i][0]=fullS[nx];
      s[i][1]=fullS[ny];
      s[i][2]=fullS[nz];
      
      NEW(f[i],3,double);
      WorldForceField(p,FALSE,fullS,&ff,w);
      f[i][0]=ff[nx];
      f[i][1]=ff[ny];
      f[i][2]=ff[nz];

      n=Norm(3,f[i]);
      //n=Norm(nv,ff);
      if (n>maxn)
	maxn=n;
      else
	{
	  if (n<minn)
	    minn=n;
	}
      free(ff);
      free(fullS);
    }

  if (maxn<epsilon)
    Error("Null force field");
  if ((maxn-minn)<epsilon)
    Warning("Constant force field");
  else
    fprintf(stderr,"Force field range                 : [%g,%g]\n",minn,maxn);
  
  /* Plot the scaled force field at the given points */
  NewColor(0,0,0,&ffColor); /* black */
  StartNew3dObject(&ffColor,p3d);
  
  for(i=0;i<ns;i++)
    {
      ScaleVector(mg/maxn,3,f[i]);
      f[i][0]+=s[i][0];
      f[i][1]+=s[i][1];
      f[i][2]+=s[i][2];
      PlotLine(s[i],f[i],p3d);
    }

  Close3dObject(p3d);
  DeleteColor(&ffColor);
      
  /* Deallocate memory */
  for(i=0;i<ns;i++)
    {
      free(s[i]);
      free(f[i]);
    }
  free(f);
  free(s);
}

void DeleteSamples(unsigned int ns,double **path)
{
  if (path!=NULL)
    {
      unsigned int i;
  
      for(i=0;i<ns;i++)
	free(path[i]);
      free(path);
    }
}

void DeleteSamplesReplay(unsigned int ns,double **path,
			 boolean *newChart,double *time,double *cost)
{
  DeleteSamples(ns,path);
  if (newChart!=NULL)
    free(newChart);
  if (time!=NULL)
    free(time);
  if (cost!=NULL)
    free(cost);
}

void DeleteTrajectory(unsigned int ns,double **path,
		      double **action,double *time)
{ 
  DeleteSamples(ns,path);
  if (action!=NULL)
    {
      unsigned int i;
      
      for(i=0;i<ns;i++)
	free(action[i]);
      free(action);
    }
  if (time!=NULL)
    free(time);
}
