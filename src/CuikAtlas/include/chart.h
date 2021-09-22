#ifndef CHARTH
#define CHARTH

#include "boolean.h"
#include "parameters.h"
#include "cpolytope.h"
#include "scpolytope.h"
#include "jacobian.h"

#include "plot3d.h"

#include "geom.h"

#include "cuiksystem.h"
#include "world.h"

/** 
   \file chart.h
   \brief Definition of a local chart on a manifold.

   Definition of a local chart on a point on a manifold.

   \sa Tchart,chart.c
*/



/** 
   \brief Select the procedure to compute the LQR policy.

   If 1, we use the procedure based on closed form expressions depending
   on the time (T). Otherwise, we use the standard
   approach based on the Runge-Kutta integration rule (recursive
   formulas instead of closed expresions). The later is less accurate
   but may be faster.

   This flag is defined here since the selected produre has
   influence in the data computed and stored in the chart
   after linearizing the dynamics.
*/
#define COMPUTE_LQRPOLICY_IN_T 1

/** 
   \brief Set to 1 to project charts to the manifold before plotting.

   Charts are defined as polytopes in the tangent space. If the error is large the
   vertices of these polytopes are quite far away from the manifold and the
   plots have apparent gaps between the different charts.
   Those gaps can be minimized projecting the vertices of the charts to the manifold
   before plotting.

   Note: When using large charts  this should
   be set to zero (points far away from the chart center do not properly converge
   to the manifold).
*/
#define PLOT_ON_MANIFOLD 0

/** 
   \brief Set to 1 to get a nicer plot for 2D manifolds.

   In general a chart is ploted using the edges between the vertices
   bounding the chart area of influence. For 2D manifolds the representation
   can be enhanced. In this case the edges define a polygon that can be
   filled. This results in a smoother graphical representation.
*/
#define PLOT_AS_POLYGONS 1


/**  \brief Relative minimum sampling radius.

    Sampling radius below this can not be reduced.

    Note that this is a ratio with respect to the original chart radius.
*/
#define MIN_SAMPLING_RADIUS 1e-3

/** 
   \brief A chart on a manifold.

   Combination of a map on a manifold and a polytope defined on the tangent
   space of the map. The polytope can be normal (\ref Tcpolytope) or
   simple (\ref Tscpolytope).

   \sa chart.h,chart.c.
*/
typedef struct {
  /* The chart information */
  TAtlasBase *w;      /**< The world structure on which the chart is defined */
  unsigned int m;     /**< Number of variables. Dimension of the ambient space. */
  unsigned int k;     /**< Dimension of the manifold. Dimension of the tangent space. */
  unsigned int da;    /**< Dimension of the action space. Only used for linearized dynamics. */
  unsigned int n;     /**< Number of non-redundant equations (equalities) defining the manifold */
  unsigned int nrJ;   /**< Number of equations. Number of rows of the Jacobian.
			   This is \e n for well constrained systems and it is
			   larger than \e n for overconstrained sytems. */
  double error;       /**< Maximum error for the linear approximation of the manifold. */
  double eCurv;       /**< Maximum cuvature error between the charts and the manifold */
  double r;           /**< Temptative radious of influence of the chart. This is stored
		           in the polytpe, but we cache it here for convenience. */
  unsigned int degree;/**< Used to detect bifurcations. */
  boolean collision;  /**< TRUE if the chart center is in collision. */
  boolean frontier;   /**< TRUE for charts with the center out of the domain either
			   because of the domain limits or due to a collision.
			   Those charts are not to be extended. */
  boolean singular;   /**< TRUE for charts defined on singularities. This occurs
		           during branch switching. Singular charts do not have a
		           Jacobian basis defined */

  double *center;     /**< Linearization point on the manifold. */
  double *T;          /**< Basis of the tangent space of the manifold at \e p
                           (m x k matrix) stored in the form of a vector. */
  boolean *BJ;        /**< TRUE for the rows of the Jacobian that form a
			   basis. This is used to compute the degree of the chart
		           and, thus it is only defined for non-singular charts. */
    
  unsigned int ml;    /**< Maximum number of charts linked to this one.
			   Singular charts are linked with other singular charts
			   (typically one) representing the bifurcation. */
  unsigned int nl;    /**< Current number of charts linked with this one. */
  unsigned int *l;    /**< Identifiers of the linked charts. */

  /* Polytope information (can be full or simple) */
  boolean simple;     /**< TRUE is we use a simple polytope. */
  Tcpolytope *p;      /**< The polytope information. */
  Tscpolytope *sp;    /**< The simple polytope information. */

  /* Information about the linearized dynamics (optional) */
  double *A;          /**< Derivative of the acceleration in tangent space
			   with respect to the parameters (k x k)  */
  double *B;          /**< Derivative of the acceleration in tangent space
		           with respect to the actions (k x k/2) */
  double *c;          /**< Offset of the linearized dynamics,
		            Vector of size k */
  double *d;          /**< A^-1*c */
  double *iRBt;       /**< Product of matrices R^-1 and B^t, where R is
			   the regulation costs. Matrix k/2 x k */
  double *BiRBt;      /**< Product of B with iRBt. Matrix k x k */
} Tchart;

/** 
   \brief Constructor.

   Defines a new chart that locally parametrizes a manifold. This chart
   is supposed to be on a regular point. Otherwise an error is triggered.

   We do not extract \e m and \e k from the number of variables/equations in the
   world since our systems are overconstrained (we include redundant equations).

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
   \param sJ Symbolic Jacobian.
   \param w The world with the equations and obstacles.
   \param c The chart to create.The chart is actually created (and must be
            deleted by the caller) when the return code is 0.

   \return 0 if we could actually define the chart, 1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined
           since the kernel is too small at the given point, 3 if there is an error while
	   performing QR decomposition, and 4 if the error w.r.t. the manifold is
	   too large.
*/
unsigned int InitChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
		       unsigned int m,unsigned int k,double *p,double e, double eCurv,double r,
		       TJacobian *sJ,TAtlasBase *w,
		       Tchart *c);
/** 
   \brief Constructor.

   The same as \ref InitChart but for charts possibly defined from singular points.
   No error is triggered if the point is not regular and charts are not forced to
   be singular.

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
   \param sJ Symbolic Jacobian.
   \param w The world with the equations and obstacles.
   \param c The chart to create. The chart is actually created (and must be
            deleted by the caller) when the return code is 0 or 1.

   \return 0 if we could actually define the chart, 1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined
           since the kernel is too small at the given point, 3 if there is an error while
	   performing QR decomposition, and 4 if the error w.r.t. the manifold is
	   too large.
*/
unsigned int InitPossiblySingularChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
				       unsigned int m,unsigned int k,double *p,double e, double eCurv,double r,
				       TJacobian *sJ,TAtlasBase *w,
				       Tchart *c);

/** 
   \brief Constructor.

   The same as \ref InitChart but for charts defined from singular points. Charts as marked as
   singular even if numerically they are determined to be regular.

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
   \param sJ Symbolic Jacobian.
   \param w The world with the equations and obstacles.
   \param c The chart to create. The chart is actually created (and must be
            deleted by the caller) when the return code is 0 or 1.

   \return 0 if we could actually define the chart, 1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined
           since the kernel is too small at the given point, 3 if there is an error while
	   performing QR decomposition, and 4 if the error w.r.t. the manifold is
	   too large.
*/
unsigned int InitSingularChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
			       unsigned int m,unsigned int k,double *p,double e, double eCurv,double r,
			       TJacobian *sJ,TAtlasBase *w,
			       Tchart *c);

/** 
   \brief Constructor.

   The same as \ref InitChart but for points that are for sure on the manifold and
   collision free.

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
   \param sJ Symbolic Jacobian.
   \param w The world with the equations and obstacles.
   \param c The chart to create. The chart is actually created (and must be
            deleted by the caller) when the return code is 0 or 1.

   \return 0 if we could actually define the chart, 1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined
           since the kernel is too small at the given point, 3 if there is an error while
	   performing QR decomposition, and 4 if the error w.r.t. the manifold is
	   too large.
*/
unsigned int InitTrustedChart(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
			      unsigned int m,unsigned int k,double *p,double e, double eCurv,double r,
			      TJacobian *sJ,TAtlasBase *w,
			      Tchart *c);

/** 
   \brief Constructor.

   Defines a new chart that locally parametrizes a manifold.

   This is like \ref InitChart but here the tangent space is given instead of computed
   from the Jacobian. This is used during branch switching where the tangent space is
   computed externally.

   \param pr The set of parameters.
   \param simple TRUE if we want to use a simple polytope.
   \param domain The box defining the domain over which the manifold is defined (or
                 of interest).
   \param tp Topology for each variable.
   \param m The dimension of the ambient space.
   \param k The dimension of the manifold
   \param p A point on the manifold.
   \param T The tangent space at this point.
   \param e Epsilon.
   \param eCurv maximum curvature error
   \param r The radius of validity of the local parametrization.
   \param sJ Symbolic Jacobian.
   \param w The world with the equations and obstacles.
   \param c The chart to create. The chart is actually created (and must be
            deleted by the caller) when the return code is 0 or 1.

   \return 0 if we could actually define the chart, 1 if there the kernel is
	   too large (i.e., the given point is singular), 2 if the chart could not be defined
           since the kernel is too small at the given point, 3 if there is an error while
	   performing QR decomposition, and 4 if the error w.r.t. the manifold is
	   too large.
*/
unsigned int InitChartWithTangent(Tparameters *pr,boolean simple,Tbox *domain,unsigned int *tp,
				  unsigned int m,unsigned int k,double *p,double *T,
				  double e, double eCurv, double r,TJacobian *sJ,
				  TAtlasBase *w,Tchart *c);

/** 
   \brief Stores the linearized dynamics in the chart.

   Stores the linearized dynamic information in the chart. The linearization
   is supposed to be defined in the chart center (but is up to the caller to
   define the linearization point).

   This can be seen as a complement to the constructor that is only used in
   dynamical systems.

   Note that we do not only store the provided information but also some products
   of the given matrices to speed up dynamic computations.

   CAUTION: In this method we re-use (point to) the buffers provided by the caller
   so, please, do not free them!. They will be freed when deleting the chart.

   \param da Dimension of the action space.
   \param mA Matrix A (k x k matri).
   \param mB Matrix B (k x k/2 matrix).
   \param vc Vector c (k vector).
   \param iR (k/2 x k/2 matrix)
   \param c The chart to update.
*/
void SetLinearizedDynamics(unsigned int da,double *mA,double *mB,double *vc,double *iR,Tchart *c);

/** 
   \brief Returns the linearized dynamics.

   Returns the information stored in the chart using \ref SetLinearizedDynamics and
   the derived information.

   \param mA Pointer to matrix A. This is a pointer to the internal buffer in the chart.
             Do not modify it.
   \param mAt Pointer to matrix At.
   \param mB Pointer to matrix B.
   \param vc Pointer to vector c.
   \param vd Pointer to the vector with the product A^-1*vc
   \param iRBt Pointer to the product R^-1*B^t
   \param BiRBt Pointer to the product B*R^-1*B^t
   \param c the chart to query.
*/
void GetLinearizedDynamics(double **mA,double **mAt,double **mB,double**vc,double **vd,
			   double **iRBt,double **BiRBt,Tchart *c);

/** 
   \brief Copy constructor.

   Copies one chart into another.

   \param c_dst The chart to define.
   \param c_src The chart from where to copy.
*/
void CopyChart(Tchart *c_dst,Tchart *c_src);

/** 
   \brief Checks if the tangent spaces are similar.

   Computes the norm of the product of the tangent spaces on two
   charts. If they are similar, the norm of the resulting matrix must
   be below \e epsilon (the error).

   The comparison between tangent spaces is based on measuring the
   <a href="http://en.wikipedia.org/wiki/Principal_angles">principal angles</a>
   between the sub-spaces. Intuitively, similar sub-spaces have angles
   between them close to 0 or to pi.

   \param c1 The first chart to compare.
   \param c2 The second chart to compare.

   \return TRUE if norm(mp1->T^{trans}*mp2->T-I)<=epsilon
*/
boolean CompareTangentSpaces(Tchart *c1,Tchart *c2);

/** 
   \brief Computes the angle between the tangent spaces in the charts.

   This is a wrapper for \ref MinCosinusBetweenSubSpaces that can
   be used with charts.

   \param c1 The first chart.
   \param c2 The second chart.

   \return The cosinus of the maximum angle (i.e., the minimum cosinus)
           between the tangent spaces of the input charts.
*/
double MinCosinusBetweenCharts(Tchart *c1,Tchart *c2);

/** 
   \brief Returns the world defining the manifold.

   Returns a pointer to the world structure with the system of
   equations defining the manifold.

   This is used to determine is two charts are defined on the same
   manifold (i.e., the same world).

   \param c The chart to query

   \return Pointer to the world on which the chart is defined.
*/
TAtlasBase *GetChartWorld(Tchart *c);

/** 
  \brief Returns the center of the chart.

  Returns a pointer to the point from which the local chart is defined

  \param c The chart to query

  \return The center of the chart.
*/
double *GetChartCenter(Tchart *c);

/** 
  \brief Returns de range of the chart.

  Returns the radious of influence for the chart.

  \param c The chart to query.

  \return The radius of the chart.
*/
double GetChartRadius(Tchart *c);

/** 
  \brief Returns de sampling range of the chart.

  Returns the adjusted radious of influence for the chart.

  Right now there is no difference between the radius and the
  sampling radious. This can change in the future.

  \param c The chart to query.

  \return The sampling radius of the chart.
*/
double GetChartSamplingRadius(Tchart *c);

/** 
   \brief Returns the maximum error between  the chart and the manifold.

   Returns the maximum error between  the chart and the manifold.

   \param c The chart to query

   \return The maximum error between the chart and the manifold.
*/
double GetChartMaxError(Tchart *c);

/** 
   \brief Returns the maximum oriented curvature error between  the chart and the manifold.

   Returns the maximum oriented curvature error between  the chart and the manifold.

   \param c The chart to query

   \return The maximum oriented curvature error between the chart and the manifold.
*/
double GetChartMaxCurvError(Tchart *c);

/** 
   \brief Dimensionality of the ambient space.

   Returns the dimensionality of the ambient space where the manifold is defined

   \param c The chart to query.

   \return \e m (see \ref Tchart)
*/
unsigned int GetChartAmbientDim(Tchart *c);

/** 
   \brief Dimensionality of the manifold space.

   Returns the dimensionality of the manifold.

   \param c The chart to query.

   \return \e k (see \ref Tchart)
*/
unsigned int GetChartManifoldDim(Tchart *c);

/** 
   \brief Gets the chart tangent space.

   Returns a pointer to the matrix defining a basis of the chart tangent space.
   This matrix is m x k.

   \param c The chart to query.

   \return The pointer to the matrix.
*/
double *GetChartTangentSpace(Tchart *c);

/** 
   \brief Identify charts defined on singularities.

   Returns TRUE for charts defined on singularities (i.e., points
   where the Jacobian is not full rang).

   \param c Them ap to query.

   \return TRUE if the chart is defined on a singularity.
*/
boolean SingularChart(Tchart *c);

/** 
   \brief Gets the index of the basis of the Jacobian vectors forming a basis.

   Returns a pointer to an array of booleans indicating the linearly independent
   vectors of the Jacobian. This can be NULL if the Jacobian basis is not yet
   computed.

   \param c The chart to query.

   \return The pointer to array of boolean flags.
*/
boolean *GetChartJacobianBasis(Tchart *c);

/** 
   \brief Returns the chart degree.

   The degree the modulo 2 of the number of non-negative real eigenvalues (i.e., possitive,
   or complex) of the squared matrix formed by the Jacobian in the top rows
   and the transposed tangent space (given in the function call) in the bottom rows.

   The degree of a chart is the degree for the center of this chart (i.e., the Jacobian is
   evaluated at the center of the chart).

   The degree is used to detect bifurcations (a change in the degree between two
   points on the manifold indicates that the line connecting the points crosses a
   bifurcation.

   Note that for this procedure to work effectively, we have to use the \e same
   tangent space to complement the Jacobian of the two points to be tested.
   That is, we use the tangent space of one of the points to evaluate the degrees
   of the two points. That is, the degree is not something intrinsec of a chart
   that can be computed and stored forever but depends on couples of charts (that use
   the same tangent space). When computing the degree for a pair of charts \e (a,b) we
   use the tangent space of \e a for the two evaluations. We use the cached degree
   for \e a and compute that of \e b from scratch using the tangent space of \e a.
   If we evaluate the possible existance of a bifurcation in between \e (b,a) we
   re-use the cached degree in \e b and we recompute that for \e a using the
   tangent space of \e b.


   \param pr The set of parameters.
   \param T The tangent space to complement the Jacobian basis. If this is the same
            as the tangent space in the chart, the result is cached in the chart for
	    future uses.
   \param sJ Symbolic Jacobian.
   \param singular Is set to TRUE if we realize that the chart is defined on
                   an almost singular point. In some cases (when very close to the
		   singularity but not exacty on it) this could not be detected
		   during chart initilization but is detected here.
   \param c The chart to query.

   \return The degree for the center of the chart.
*/
unsigned int GetChartDegree(Tparameters *pr,double *T,TJacobian *sJ,
			    boolean *singular,Tchart *c);

/** 
   \brief Returns the parametrization of a point.

   Returns the parametrization on the tangent space of a point on the manifold.

   In principle any point can be projected to the tangent space, even those
   given parameters out of the radius of the chart.

   This corresponds to the logarithmic map in differential geometry.

   In some cases we have to take into account the topology of the ambient space
   and in others not. When trying to determine which charts are neighbours, we
   take it into account so that we obtain the closest projection of a point
   to the current chart center. When defining RRT branches on the tangnent space
   the topology is not considered so that we define the correct advance direction
   towards the random/goal sample.

   We directly project the points to the tangent space, without transforming
   the point to project into canonical form (i.e,. move it in the range -pi,pi
   for the dimensions with circular topology). It is the user option to
   transform the point to project before actually projecting it.

   Observe that transforming a point before projecting it can actually
   generate a set of parameters that do not give the shortest displacement
   to the projected sample. This is critical when defining RRT-like structures
   using the charts.

   \param p The point to parametrize.
   \param tp The topology of the ambient space.
   \param t The output set of parameters.
   \param c The chart to use to get the parametrization.

   \return The norm of the parameter vector \e t (i.e., how far is \e t from
           the center of the chart).
*/
double Manifold2Chart(double *p,unsigned int *tp,double *t,Tchart *c);

/** 
   \brief Returns the point in the manifold for a given set of parameteres.

   Returns a point in the mainifold corresponding to a set of parameters
   in a given chart.

   Note that not all parameters can be savely mapped to the manifold.
   The implicit function theorem guarantees the mapping to be valid for
   a ball around the linealization point. In principle this ball should
   reach the singularity locus possibly sourronding the central point.
   However, this mapping is implemented using a numerical procedure
   than can fail to converge even far from the singularity frontier.

   This corresponds to the exponential map in differential geometry.

   In many cases, this function not applies the pi2pi mapping since the output
   points can be used with many purposes (not only creating new charts).
   Thus, this function can produce points larger/smaller than pi/-pi
   in circular dimensions. The trick here is:
       - When creating a new chart, enforce the [-pi,pi] range.
       - Detect that points around the border +/-pi are neighbours
         (the kd-tree takes care of this). This avoids an atlas to expand
	 repetitively over a circular range.
       .
   To skip the pi2pi mapping just call the function with tp set to NULL.

   \param pr The set of parameters.
   \param sJ Symbolic Jacobian.
   \param t The set of parameters.
   \param tp The topology of the variables. NULL if all are \ref TOPOLOGY_R.
   \param pInit Initial estimation for the expected output \e p. Set to NULL to
          start the process from the the point on the tangent space given by \e t.
   \param p The output point on the manifold.
   \param c The mpa to use.

   \return If the process converges, the distance between the point on the manifold
           and the tangent space, if not \ref INF.
*/
double Chart2Manifold(Tparameters *pr,TJacobian *sJ,
		      double *t,unsigned int *tp,double *pInit,
		      double *p,Tchart *c);


/** 
   \brief Transforms a parameter in tangent space to a point in ambient space.

   Uses the center and the base of the tangent space to generate a point in
   ambient space from a parameter set in tangent space.

   \param t The parameters in tangent space.
   \param tp Topology of the ambient space.
   \param p The output point in ambient space.
   \param c The chart to use
*/
void Local2Global(double *t,unsigned int *tp,double *p,Tchart *c);

/** 
   \brief Identifies points inside the defined error.

   Transforms \e t to the ambient space (via \ref Local2Global) and compute
   the distance to \e p.

   The point \e p and the paramters \e t are supposed to correspond each other
   (via the \ref Chart2Manifold and \ref Manifold2Chart mappings). In this
   way we compute the distance from the manifold to the tangent space for
   a given point.

   \param t The parameters of the point to compare.
   \param p The second point to compare.
   \param tp The topology. One entry per variable: \ref TOPOLOGY_R
             or \ref TOPOLOGY_S.
   \param c Tha chart to query.

   \return The norm of \e Local2Global(t)-p.

   \sa Local2Global, ChartError.
*/
double ChartErrorFromParameters(double *t,double *p,
				unsigned int *tp,Tchart *c);

/** 
   \brief Distance from the manifold to the tangent space.

   Basically combines \ref Manifold2Chart with \ref ChartErrorFromParameters.

   \param p The point in the manifold to project and compare.
   \param tp The topology of the variables.
   \param c Tha chart to query.

   \return The distance of \e p to the tangent space.

   \sa Manifold2Chart, ChartErrorFromParameters.
*/
double Error2Chart(double *p,unsigned int *tp,Tchart *c);

/** 
   \brief Identifies close local charts.

   Determines if two local charts are close and have similar tangent
   spaces.

   \param pr The set of parameters (basically to use \ref CT_EPSILON).
   \param tp The topology for each variable.
   \param c1 The first chart to modify.
   \param c2 The second chart to modify.

   \return TRUE if \e mp1 and \e mp2 are neighbours.
*/
boolean CloseCharts(Tparameters *pr,unsigned int *tp,
		    Tchart *c1,Tchart *c2);

/** 
   \brief Intersects two local charts.

   Determines if two chart are neighbours and intersect the corresponding
   polytopes.

   \param pr The set of parameters (basically to use \ref CT_EPSILON).
   \param tp The topology for each variable.
   \param ambient The ambient space.
   \param id1 Identifier of the first chart to modify.
   \param c1 The first chart to modify.
   \param id2 Identifier of the second chart to modify.
   \param c2 The second chart to modify.

   \return TRUE if \e mp1 and \e mp2 are neighbours.
*/
boolean IntersectCharts(Tparameters *pr,unsigned int *tp,Tbox *ambient,
			unsigned int id1,Tchart *c1,
			unsigned int id2,Tchart *c2);

/** 
   \brief Identifies collision charts.

   Identifies charts that are in collision

   \param c The chart to query.

   \return TRUE for colliding charts.
*/
boolean CollisionChart(Tchart *c);

/** 
   \brief Identifies frontier charts.

   Identifies charts that are at the borders of the domain.

   \param c The chart to query.

   \return TRUE for boundary charts.
*/
boolean FrontierChart(Tchart *c);

/** 
   \brief Marks a chart as a frontier chart.

   Marks a chart as a frontier chart. Frontier charts
   are note expanded.

   \param c The chart to modify.
*/
void ChartIsFrontier(Tchart *c);

/** 
   \brief Identifies boundary charts.

   TRUE for external (frontier) charts, i.e., charts that can be
   used to expand the atlas.

   If the chart is based on simple polytope this function will
   trigger an error since simple polytopes can not identify
   open charts.

   \param c The chart to query.

   \return TRUE for external (frontier) charts.
*/
boolean ExpandibleChart(Tchart *c);

/** 
   \brief Identifies charts not fully sorrounded by other charts.

   TRUE for charts with polytope vertices still outside
   the ball. Those vertices can still be used to generate
   neighbours for the chart.

   If the chart is based on simple polytope this function
   will return TRUE always since for simple polytopes it is
   not possible to determine if a chart is closed or not.

   This is equivalent to \ref ExpandibleChart but this function does
   not trigger error for charts based on simple polytopes.

   \param c The chart to query.

   \return TRUE for charts with vertices out of the ball.
*/
boolean OpenChart(Tchart *c);

/** 
   \brief Mark a vertex as wrong.

   Wrapper for \ref WrongPolytopeCorner.

   \param nv The vertex to mark
   \param c The chart.
*/
void WrongCorner(unsigned int nv,Tchart *c);

/** 
   \brief Checks if a parameter point is inside the chart polytope.

   Wrapper for \ref InsidePolytope (or \ref InsideSPolytope).

   \param t The parameters.
   \param c The chart.

   \return TRUE if the point is inside the polytope defining the
           area of influence of the chart.
*/
boolean InsideChartPolytope(double *t,Tchart *c);

/** 
   \brief Determines the neighbouring chart containing a given point.

   This function determines the neighbouring chart that includes a
   point inside the chart radius but outside the polytope.
   This is implemented determining the chart borders crossed when moving
   to the point.

   \param epsilon Numerical accuracy.
   \param t The point.
   \param c The chart.
*/
unsigned int DetermineChartNeighbour(double epsilon,double *t,Tchart *c);

/** 
   \brief Ensures that a chart includes a given point.

   Ensures that a chart includes a given point possibly modifying the
   faces enlarging the polytope.

   Note that this function is not implemented for normal polytpes
   since moving a face will represent to recompute all vertices and
   this is too expensive. Thus, this function is only used from
   AtlasRRT where charts are defined with simple polytopes.

   \param t The point.
   \param c The chart.
*/
void EnlargeChart(double *t,Tchart *c);

/** 
   \brief Random point on the chart boundary from the polytope vetices.

   Wapper for \ref PolytopeBoundaryPointFromExternalCorner.

   \param rand TRUE if the external corner has to be selected at random from all
               external ones of FALSE if we have to just pick the first one.
   \param nv The identifier of the selected vertex. This is set to NO_UINT if
             no boundary point can be actually returned.
   \param t The output point on the chart ball boundary (if any)
   \param c The chart to sample.

   \return TRUE if the sampled point is actually on the boundary of the
           atlas.
*/
boolean BoundaryPointFromExternalCorner(boolean rand,unsigned int *nv,double *t,Tchart *c);

/** 
   \brief All the possible points on the chart's boundary from polytope vertices.

   This is the same as \ref BoundaryPointFromExternalCorner but instead of selecting
   one vertex returns points for all the possible vertices.

   This is used when parallelizing the generation of children charts from a given chart.

   \param n The number of returned points.
   \param nv Array with the vertex identifiers. The space is allocated internally, but must
             be deallocated by the caller. This is set to NO_UINT if
             no boundary point can be actually returned.
   \param t Array with the returned points. Each point is of size c->k.
            The space is allocated internally, but must be deallocated by the caller.
   \param c The chart to query.
*/
void BoundaryPointsFromExternalCorners(unsigned int *n,unsigned int **nv,double ***t,Tchart *c);

/** 
   \brief Random point on the boundary of the chart

   Wrapper for \ref PolytopeRandomPointOnBoundary.

   \param t The output point on the chart ball boundary (if any)
   \param c The chart to sample.

   \return TRUE if the sampled point is actually on the boundary of the chart.
*/
boolean RandomPointOnBoundary(double *t,Tchart *c);

/** 
   \brief Samples a random point in the area covered by the chart.

   Selects a point on a chart with uniform distribution.

   Points are given in the tangent space associated with the chart and not on
   the manifold. However, given the chart manifold, a point on the tangent
   is supposed to give a point on the manifold.

   This is basically a wrapper  \ref RandomPointInPolytope plus a
   conversion of local points to global.

   \param pr The set of parameters.
   \param scale Global scale factor for the sampling area for each chart. This
                is only used simple charts. The default value is 1.
		See \ref RandomPointInSPolytope.
   \param tp Topology of the ambient space.
   \param t Parameters (in the chart) for the output point.
   \param p The output point.
   \param c The chart to sample.

   \return TRUE if we could actually sample a point in the chart.
*/
boolean RandomPointInChart(Tparameters *pr,double scale,
			   unsigned int *tp,double *t,double *p,Tchart *c);

/** 
    \brief Increase the sampling radious of the chart.

    Valid sampling on a chart leads to an increment of the sampling area.

    \param c The chart whose sampling radius we have to adjust.
*/
void IncreaseChartSamplingRadius(Tchart *c);

/** 
    \brief Decrease the sampling radious of the chart.

    Rejection sampling on a chart leads to a reduction of the sampling area.

    \param c The chart whose sampling radius we have to adjust.
*/
void DecreaseChartSamplingRadius(Tchart *c);

/** 
    \brief Estimate the volume of a chart.

    This is a simplified version of \ref ChartVolume where collisions
    are not taken into account. Thus this returns an upper bound
    approximation of the collision free volume of the chart.

    This is used to fix some thresholds in  RRT*.

    \param c The chart to measure.

    \return The chart volume.
*/
double ChartMaxVolume(Tchart *c);

/** 
   \brief Estimate the volume of a chart.

   Estimate the volume of part of the manifold covered by a chart.
   The volume is estimated via MonteCarlo on the tangent space.

   Note that this function replicates \ref PolytopeVolume and
   \ref SPolytopeVolume but including the collision detection,
   which is not computable at the level of polytopes.

   \param pr The set of parameters.
             Only used if collisionFree is TRUE.
   \param collisionFree TRUE if only the collision free volume
                        has to be computed.
   \param tp The topology for each variable.
             Only used if collisionFree is TRUE.
   \param sJ The simbolic Jacobian.
             Only used if collisionFree is TRUE.
   \param c The chart to measure.

   \return The chart volume.
*/
double ChartVolume(Tparameters *pr,boolean collisionFree,
		   unsigned int *tp,TJacobian *sJ,Tchart *c);

/** 
   \brief Generates point on the boundary towards a given goal.

   Tries to generate a point on the chart boundary that is aligned
   with a given point on the manifold.

   \param p The goal point (on the manifold, with ambient dimension).
   \param tp The ambient space topology.
   \param t The output point on the chart ball boundary (if any)
   \param c The chart to sample.

   \return TRUE if the sampled point is actually on the boundary of the
           atlas.
*/
boolean FocusedPointOnBoundary(double *p,unsigned int *tp,double *t,Tchart *c);


/** 
   \brief Defines the path to a point in the chart.

   Defines the path to a point in the chart. The samples added to the path
   are those resulting from using the chart projection moving at steps
   of size delta towards the given set of parameters.
   The final point is also added to the path.

   This is used when reconstructing the path from the start point to the goal
   and the segment of path on this chart is concatenated to the path
   already found.

   \param pr The set of parameters.
   \param t The parameters for the point.
   \param tp The topology of the variables.
   \param sJ Symbolic Jacobian.
   \param nvs Number of system variables.
   \param systemVars Flags indicating the sytem varibles. Only those are
                     added to the path.
   \param ms Maximum number of samples in the path.
   \param pl Accumulated path lenght.
   \param ns Current number of samples in the path.
   \param path The path where to add the samples. Samples found on this
               chart are added at the end of this path.
   \param c The chart.

   \return TRUE if there is no collision along the path (i.e., if the determined
           path is actually valid).
 */
boolean PathInChart(Tparameters *pr,double *t,unsigned int *tp,TJacobian *sJ,
		    unsigned int nvs,boolean *systemVars,
		    unsigned int *ms,
		    double *pl,unsigned int *ns,double ***path,
		    Tchart *c);

/** 
   \brief Distance between the center of a chart and a point on this chart.

   Approximates the geodesic distance between the center of a chart and
   a point on this chart. This is like \ref GeodesicDistance but this
   function only operates on points on the same chart.

   If the path is not collision free, this function returns \ref INF.

   \param pr The set of parameters.
   \param t The parameters for the point.
   \param tp The topology of the variables.
   \param sJ Symbolic Jacobian.
   \param c The chart.
*/
double DistanceOnChart(Tparameters *pr,double *t,unsigned int *tp,TJacobian *sJ,
		       Tchart *c);

/** 
   \brief Identify points on a chart.

   Identifies points that are inside the area of influence of a given chart.

   \param pr The set of parameters (to get the numerical tolerance).
   \param sJ Symbolic Jacobian.
   \param p The point.
   \param tp The topology of the variables. NULL if all are \ref TOPOLOGY_R.
   \param t The parameters of the point on the chart. Only holds the correct
            value if the point is actually on this chart.
   \param c The chart that should include the point.

   \return TRUE if the point \e belongs to the chart.
*/
boolean PointOnChart(Tparameters *pr,TJacobian *sJ,
		     double *p,unsigned int *tp,
		     double *t,Tchart *c);

/** 
   \brief Identifies the position of a point w.r.t. a given chart.

   Computes the relative position of a point with respect to a given chart.
   The point can be
      - 4: The point is completely out of the scope of the chart.
      - 3: The point is outside the scope due to convergence problems.
      - 2: The point is outside the scope, but inside the ball. This means that
           the point must be inside the scope of one of the neighbouring charts.
      - 1: The point is inside the scope of the chart, but outside the ball.
      - 0: The point is inside the scope of the chart.
      .
   Codes 0 and 1 correspont to points inside the scope of the chart, although
   in different circumstances. In the first case the point wil for sure move
   to a neighbouring chart as new charts are created and in the second this
   is less likely to occur (but not impossible).

   \param pr The set of parameters (to get the numerical tolerance).
   \param error TRUE if the error between the chart and the manifold for
                the given point should be also considered.
                If this is set to \ref FALSE this function never returns 3.
   \param sJ Symbolic Jacobian.
   \param p The point.
   \param tp The topology of the variables. NULL if all are \ref TOPOLOGY_R.
   \param t The parameters of the point on the chart. Only holds the correct
            value if the point is actually on this chart.
   \param c The chart that should include the point.

   \return A code (see above) with the position of the point with respect to the
           chart.
*/
unsigned int ClassifyPointInChart(Tparameters *pr,boolean error,TJacobian *sJ,
				  double *p,unsigned int *tp,
				  double *t,Tchart *c);
/** 
   \brief Connect charts at singularities.

   At bifurcation points we generate two charts, one at the singular point with
   tangent space aligned with the charts that allowed to detect the bifurcation
   and a chart at the other branch of the manifold.
   These two charts overlap because they are almost defined at the same point but with
   different tangent spaces.
   Since they have different tangent spaces they will not be considered
   neighbours by \ref IntersectCharts and they have to be linked explicitly
   using this function.

   Explicitly linked chats also appear in the list of neighbours as retrieved
   using \ref ChartNumNeighbours or \ref ChartNeighbourID.


   \param id1 Identifier of the first chart to link.
   \param c1 The first charts to link.
   \param id2 Identifier of the second chart to link.
   \param c2 The second chart to link.
*/
void LinkCharts(unsigned int id1,Tchart *c1,unsigned int id2,Tchart *c2);

/** 
   \brief Crops the domain for a given chart.

   Crops the domain of a given chart with a constraint derived form
   the global domain. This is used for charts that are at the
   border of the global domain.

   \param pr The set of parameters.
   \param t Parameters of the point that are just outside the domain.
   \param tp The topology of the ambient space.
   \param ambient The ambient space box.
   \param c The chart to modify.
*/
void AddBorderConstraint(Tparameters *pr,double *t,unsigned int *tp,Tbox *ambient,Tchart *c);

/** 
   \brief Intersect two charts that might be non-neighbours.

   Intersects two charts without checking first if they are actually
   neighbours. This is used in the AtlasRRT when using loose controls
   aboud curvature. In this case we can end up generating a chart that
   is not neighbour with its parent (but it must be almost neighbour).
   In this situation we enforce the neighbouring relation between them.

   \param pr The set of parameters.
   \param tp The topology of the ambient space.
   \param ambient The ambient space.
   \param id1 The identifier of the first chart.
   \param c1 The first chart.
   \param id2 The identifier of the second chart.
   \param c2 The second chart.
*/
void ForceChartCut(Tparameters *pr,unsigned int *tp,Tbox *ambient,
		   unsigned int id1,Tchart *c1,
		   unsigned int id2,Tchart *c2) ;

/** 
   \brief Number of neighbours of the chart.

   Returns the number of neighbouring charts.

   Note that for charts at the border of the ambient space, this returns
   and overestimation of the number of neighbours: it includes "virtual"
   neighbours generated by cropping the chart with the ambient space
   borders. These virtual neighbours have NO_UINT as identifier.

   \param c The chart to query.

   \return The number of neighbours of the chart.
*/
unsigned int ChartNumNeighbours(Tchart *c);

/** 
   \brief Returns the identifier of one of the neighbours of a chart.

   Gives the identifer for one of the neighbours of a chart. For
   the virtual neighbours eventually generated due to the intersection
   of the chart with the ambient space domain, NO_UINT is returned.
   The caller must take care of not using output of this function in
   these special cases.

   \param n The number  of neighbour to query (numbered from 0).
   \param c The chart to query.

   \return The neighbour identifer. \ref NO_UINT if \e i is larger thatn
           the actual number of neighbours of the chart.
*/
unsigned int ChartNeighbourID(unsigned int n,Tchart *c);

/** 
   \brief Returns the identifier of neighbouring charts coincident at a vertex.

   When triangulating an atlas we want to define a triangle for each vertex of
   the atlas. Thus, for each vertex, we identify the three coincident charts
   so that we can connect their centers forming a triangle.
   The charts are the one defining the polytope whose vertex we are analyzing
   plust the two charts defining the edges coincident at that vertex.

   This only operates for bidimendional manifolds and does not return the neighbours
   through singularities.

   This is only used when triangulating atlas.

   \param pr The set of parameters.
   \param nn Number of neighbours (output).
   \param cID1 For each vertex, the identifier of the chart neighbouring by one of
               the two edges defining this vertex. The space for this array is allocated
	       internally  (output).
   \param cID2 For each vertex, the identifier of the chart neighbouring by other
               edge defining this vertex. The space for this array is allocated
	       internally  (output).
   \param c The chart to query.
*/
void GetChartNeighboursFromVertices(Tparameters *pr,
				    unsigned int *nn,unsigned int **cID1,unsigned int **cID2,Tchart *c);

/** 
   \brief Plots a 3d projection of a local chart.

   Plots a 3d projection of a local chart.

   In only works for 2D or 3D manifolds.

   We plot the edges delimiting the chart.

   Observe that this function does not take into account the topology of the
   variables in order to avoid plotting weird charts. When plotting on
   variables with topology \ref TOPOLOGY_S a cut is introduced at pi and
   since plots are in generated in R. Charts over pi will produce vertices
   larger/smaller than pi/-pi. The resulting plot won't be continuous.

   \todo Speed up this function caching the vertex projection on the manifold
         instead as recomputing them as many times as needed.

   \param pr The set of parameters.
   \param fcost File from where to get the cost associated with this chart.
                This translates to a different color for the chart in function
                of the cost. Set to NULL if the chart is to have a uniform color.
                This is only used if the chart is plotted as a polygon, otherwise
		it makes no sense to color the chart.
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
void PlotChart(Tparameters *pr,FILE *fcost,TJacobian *sJ,
	       unsigned int xID,unsigned int yID,unsigned int zID,
	       Tplot3d *p3d,Tchart *c);

/** 
    \brief Memory used by a given chart.

    Returns the approximated memory used (in bytes) by a given chart.

    \param c The chart.

    \return The size of the chart in bytes.
*/
unsigned int ChartMemSize(Tchart *c);

/** 
   \brief Stores the chart information on a file.

   Stores the chart information on a file.

   \param f The file where to store the information.
   \param c The chart to store.
*/
void SaveChart(FILE *f,Tchart *c);

/** 
   \brief Defines a chart from the information on a file.

   Chart constructor from the information on a file.
   The information is to be generated with \ref SaveChart.

   \param f The file from where to read the data.
   \param w The world to which the chart is refereed.
   \param c The chart to define.
*/
void LoadChart(FILE *f,TAtlasBase *w,Tchart *c);

/** 
   \brief Prints defines.

   Prints the defines in chart.h

   This is used only for debug purposes.
   
   \param f The file where to store the values.
*/
void PrintChartDefines(FILE *f);

/** 
   \brief Destructor.

   Deletes the information stored in a chartping.

   \param c The chart to delete.
*/
void DeleteChart(Tchart *c);

#endif
