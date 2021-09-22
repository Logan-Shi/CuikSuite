#ifndef ATLASH
#define ATLASH

#include "box.h"
#include "heap.h"
#include "chart.h"
#if (_KDTREE)
  #include "btree.h"
#endif
#include "jacobian.h"
#include "hessian.h"
#include "filename.h"


/** 
   \file atlas.h
   \brief Definition of an atlas on a manifold.

   Definition of a set of local charts on a manifold.

   \sa Tatlas,atlas.c
*/

/**  \brief Vebosity of the atlas operations

    Vebosity of the atlas operations. If set to 0 only  minimalistic
    information is printed.
*/
#define ATLAS_VERBOSE (_DEBUG>4?1:0)

/**  \brief Activate/deactivate the colors in the atlas plot.

    When set to 1 charts are plotted in different colors according to whether
    they are singular (green), open (red), singular open (yellow), close (blue), etc.
    Otherwise all charts are plotted in blue.
   
    This is only used if the user does not provide a cost map associated with the atlas.
*/
#define PLOT_ATLAS_IN_COLORS 1

/**  \brief Select between the two types of projection when interpolating between configurations.
   
    Select between the two types of projection when interpolating between configurations.
    In the first type of projection a Newton (or Jacobian pseudo-inverse) method is used.
    This method does not warrantee any separation between the samples when projected.
    When we force the projection to lie in a plane orthogonal to the interpolation
    direction, projected samples are  at least as separated as the interpolation steps.

    Right now this is only used when approximatting the geodesic distance between samples
    that is part of the A* search (used to determine if there is a collision between the
    centers of two charts: collision = INF distance).
*/
#define PROJECT_WITH_PLANE 1


/**  \brief Initial number of charts of an atlas.

    Initial number of charts of an atlas. It will be expanded as needed.
*/
#define INIT_NUM_CHARTS  100

/**   \brief Initial number of bifurcations of an atlas.
     
     Initial number of bifurcations of an atlas. It will be expanded as needed.
*/
#define INIT_NUM_BIFURCATIONS  100

/** 
   \brief Whether to use a binary tree to search for neighbouring charts.

   Set to 1 to use a binary tree to search for nighbouring charts.
   In general should be 1. For very small problems 0 could be better but
   the difference in execution time will be minor.
*/
#if (_KDTREE)
  #define USE_ATLAS_TREE 1
#else
  #define USE_ATLAS_TREE 0
#endif

/**  \brief Ratio at which the sampling radius is reduced.

    Ratio at which the sampling radius is reduced when sampling fails.
*/
#define SAMPLING_RADIUS_REDUCTION_FACTOR 0.9

/** \brief If 1, the border of the atlas are roughly approximated.

    With this flag on only a rough approximation of the domain borders 
    is performed. It is more efficient.
*/
#define SIMPLE_BORDER 1

/** ***********************************************************************/

/** 
   \brief Initial number of elements in the heap of local charts.

   Initial number of elements in the heap of local chart used int \ref AtlasGBF.
   This is extended as needed.
*/
#define INIT_NUM_CHARTS_IN_ATLAS_HEAP 100

/**  
   \brief Data about the atlas construction.

   Statistical data collected during the atlas construction. The atlas is
   built generating new charts from previous charts already in the manifold.
   
*/
typedef struct {
  unsigned int nBoundaryAttempts;/**< Times we tried to generate a point on the
				      boundary. */
  unsigned int nNotInBoundary;   /**< Times we failed to generate a point on the 
				      boundary. */
  unsigned int nExtensions;      /**< Times we tried to extend a chart. Extension
				      attemps would end up in one of the following.*/
  unsigned int nImpossible;      /**< Errors when trying to expand from/toward a point. */
  unsigned int nSingImpossible;  /**< Errors when trying to expand from/toward a point form
			  	      a singular chart */
  unsigned int nLargeError;      /**< Times the point on the tangent space was too 
				      far away from the manifold. */
  unsigned int nNonRegularPoint; /**< Times we tried to generate a chart on a non-regular
				      point. */
  unsigned int nNotInManifold;   /**< Times we tried to generate a chart from a point 
				      not in the manifold. */
  unsigned int nQRSVDError;      /**< Times we tried to generate a chart on a point
				      where the QR or the SVD fails. */
  unsigned int nFarFromParent;   /**< Times the new chart was too far from its parent. */
  unsigned int nInCollision;     /**< Times we detected a collision */
  unsigned int nRadiousChange;   /**< Times we had to change the radius (get close/further to 
				      the previous chart) when to create a new chart. */
  unsigned int nGoodExtension;   /**< Times we actually succeeded in the creation of a new 
				      chart. */
  unsigned int nBifurcations;    /**< Number of processed bifurcations. */
  unsigned int nSmallAngle;      /**< Number of small angles at bifurcation. Most likely
				      mean we could not actually jump to the other branch. */
  unsigned int nSPMissed;        /**< Number of errors finding the singular point. */
  unsigned int nNoSingularEnough;/**< Times the singular point was not singular engoug. */
  unsigned int nNoJumpBranch;    /**< Times we could not find to the other branch. */
} TAtlasStatistics;

/** 
   \brief Representation of a bifurcation.

   A bifurcation is the connection between two aspects (or branches) of the same manifold.
   Bifucation occurs at the singular points.
   
   We detect singularities analysing pairs of consecutive charts (see \ref DetermineChartNeighbours).
   If there is a change in the degree between the couple of charts (see \ref GetChartDegree)
   we know for sure there is a singularity between the centers of the two charts.
   Then we trigger a process to isolate the singular point and then to generate
   a point (and a chart) in the \e other aspect (or branch) of the manifold.

   Note that the new chart is not neighbour of the two charts used to detect the singularity
   (their tangent spaces are two different). Thus, in some sense this structure is used
   to store the neighbouring relations not directly stored in the charts.
*/
typedef struct {
  unsigned int mID1;   /**< Identifier of the first chart used to detect the singularity. */
  unsigned int d1;     /**< Degree for the center of the first chart */
  unsigned int mID2;   /**< Identifier of the second chart used to detect the singularity. */
  unsigned int d2;     /**< Degree for the center of the second chart */
  double *p;           /**< Representative point for this bifurcation. */
} Tbifurcation;

/** ***********************************************************************/

/** 
   \brief Structure used for the elements of the heap of charts.

   In \ref AtlasGBF we need to use a heap of charts to select
   the one closest to the target point. This structure represents
   one element of this heap.
*/
typedef struct {
  unsigned int chartID;      /**< Identifier of the local chart. */
  double cost;               /**< Estimated cost (including the heuristic) to reach the goal. */
  double beta;               /**< Factor used to penalize the cost. */ 
  unsigned int nPenalized;   /**< Times we used this chart to extend the atlas. */
} TAtlasHeapElement;

/** 
   \brief Constructor of TAtlasHeapElement.

   Defines a new atlas heap element.

   \param mID Chart identifier.
   \param c Cost (includes the cost from origin plus the heuristic to goal, if any).
   \param beta The penalization factor (>1).
   \param he The element to initialize.
*/
void InitAtlasHeapElement(unsigned int mID,double c,double beta,TAtlasHeapElement *he);

/** 
   \brief Copy constructor.

   Defines a new atlas heap element from another.
   We use void pointers to use the generic heap implementation.

   \param he1 The heap element to define.
   \param he2 The heap element from where to copy.
*/
void CopyAtlasHeapElement(void *he1,void *he2);

/** 
   \brief Gets the chart identifier.

   Gets the chart identifer stored in an atlas heap element.

   \param he The heap element to query.

   \return The chart identifier stored in the elemement.
*/
unsigned int GetAtlasHeapElementID(TAtlasHeapElement *he);

/** 
   \brief Gets the cost.

   Gets the cost stored in an atlas heap element.

   \param he The heap element to query.

   \return The cost stored in the elemement.
*/
double GetAtlasHeapElementCost(TAtlasHeapElement *he);

/** 
   \brief Comparison between atlas heap elements.

   Identifies atlas heap element with lower cost.
   
   \param he1 The first heap element to compare.
   \param he2 The second heap element to compare.
   \param userData Not used. Included for compatibility with the generic
          heap implementation.

   \return TRUE if \e he1 is cheaper than \e he2.

   \sa Theap.
*/
boolean LessThanAtlasHeapElement(void *he1,void *he2,void *userData);

/** 
   \brief Penalized the cost stored in a atlas heap element.

   Penalizes the cost of the atlas heap element. Every time this function is called
   we increase the counter in the heap element and, thus, we penalize the cost accordingly.
   The idea is that charts where it is difficult to sample should be penalized to 
   deviate the search to neighbouring charts with larger external border.

   \param he The atlas heap element to updated.
*/
void PenalizeAtlasHeapElement(TAtlasHeapElement *he);

/** 
   \brief Atlas heap element destructor.

   Releases the memory alloated in the atlas heap element, if any.

   \param he The heap element to remove.
*/
void DeleteAtlasHeapElement(void *he);

/** ***********************************************************************/


/** 
   \brief A atlas on a manifold.

   A collection of charts.

   Note that charts and atlas are defined on a simplified cuiksystem. Recall that
   the system as defined in by the user (in the .cuik file) is the \e original
   system. This system is simplified and later dummified. Charts and atlas are
   defined in the intermeditate system (the simplified but not dummified). 
   This is the smaller system in terms of variables and equations and, thus,
   the atlas is generated faster. 

   However, input (the seed from where to start the atlas or the goal for
   the path on the atlas) and output points (the path) are given in the original
   system and including only system variables. Therefore, all input points
   are processed to first find out the values of the dummy variables from the
   system ones and then the values of the variables in the simplified system.
   Output points undergo the reverse transformation.

   \sa chart.h,chart.c,atlas.c.
*/
typedef struct {
  TAtlasBase *w;                   /**< The world on which the atlas is defined */
  
  unsigned int m;                  /**< Number of variables. Dimension of the ambient space. */
  unsigned int k;                  /**< Dimension of the manifold */
  unsigned int n;                  /**< Number of equations (equalities) defining the manifold. */
  double e;                        /**< Maximum error for the linear approximation of the manifold. */
  double ce;                       /**< Maximum cuvature error between the charts and the manifold */
  double r;                        /**< Radius around \e p (in tangent space) where the linearization holds. */
  boolean simpleChart;             /**< TRUE if the atlas is to be defined on simple charts. */

  unsigned int nCores;             /**< Available computing cores. */
  boolean parallel;                /**< TRUE if it is worth to use parallelism. Right now ony the altas
				        construction exploits parallelism. */

  unsigned int *tp;                /**< Topology for each variable. */
  
  unsigned int maxCharts;          /**< Maximum numer of charts in the atlas. Expanded as needed. */
  unsigned int currentChart;       /**< Current number of charts in the atlas. */
  unsigned int npCharts;           /**< Number of charts already processed. Charts are added to
				        atlas and latter on they are post-processed (search for
				        neighbours, detect bifurcations, etc). */
  Tchart **charts;                 /**< Set of local charts */

  unsigned int nrJ;                /**< Number of rows of the symbolic Jacobian. */
  unsigned int ncJ;                /**< Number of columns of the symbolic Jacobian. */
  TJacobian J;                     /**< Symbolic Jacobian of the underlying system of equations. 
				        Cached to avoid recomputing it every time we define 
					a new chart. */
  THessian *H;                     /**< Hessian. Computed from the Jacobian. Only used when
				        refining singular points (\ref RefineSingularPoint) */
  Tbox *ambient;                   /**< Area where the manifold is defined. This can be used
				        to clip a manifold. In general this is determined by the
				        ranges of the variables. */
  
  
  unsigned int mBifurcations;      /**< Maximum space for bifurcations in \e bifurcations. Enlarged as needed. */
  unsigned int nBifurcations;      /**< Current number of bifurcations. */
  unsigned int npBifurcations;     /**< Number of bifurcations already processed. The bifurcations
				        are generated in groups when searching for neighbouring
					charts. We process them in groups too. */
  Tbifurcation **bifurcation;      /**< The bifurcation information. */

  #if (USE_ATLAS_TREE)
    TBTree tree;                   /**< A binary tree of charts to speed up the search for neighbours.*/
  #endif
} Tatlas;

/** 
   \brief Constructor.

   Initializes an empty atlas.

   \param pr The set of parameters.
   \param parallel TRUE if the atlas might be generated/processed in parallel.
                   This parameter is used if OpenMP is available.
   \param simpleChart TRUE if the atlas is to be defined using simple charts.
   \param k The dimension of the manifold
   \param e Maximum error between charts and the manifold.
   \param ce  Maximum curvature error
   \param r The radius of validity of the local parametrization.
   \param w The world on which the atlas is to be defined.
   \param a The atlas to initialize.
*/
void InitAtlas(Tparameters *pr,boolean parallel,boolean simpleChart,
	       unsigned int k,double e,double ce, double r,TAtlasBase *w,
	       Tatlas *a);

/** 
   \brief Defines a new chart and adds it to the atlas.

   Defines a chart on the given point and adds it to the atlas updating the
   neighbouring relations and checking for the presence of singularities
   in between the centers of the charts dectected as neighbours, if any.

   Note that we could actually build an atlas by sampling random points on
   the manifold and using this function to create new charts until the atlas
   is compleated. However this estrategy is not guaranteed be be succesful
   and could produce atlas with charts for very different sizes. This
   is why higher dimensional continuation typically uses more principled
   ways to generate new charts from the existing ones 
   (see \ref BuildAtlasFromPoint).

   \param pr The set of parameters.
   \param ps The point (on the manifold) where to define the new chart.
             CAUTION. This point is assumed to be in the simplified system. 
	     (no in the original system as the point given in \ref InitAtlasFromPoint).
	     This kind of points typically result from any manipulation of an existing
	     atlas (\ref RandomPointInAtlas, \ref Chart2Manifold, etc).
   \param parentID Identifier of the parent chart. \ref  NO_UINT if unkown.
   \param singularity [Output] TRUE if the new chart of one of its neighbours is
                      (almost) on a singularity at the given numerical accuracy
		      (see the epsilon parameter). In this case bifurcations
		      might be undetected.
   \param a The atlas where to add the new chart.

   \return Identifier of the new chart or \ref NO_UINT if the chart could not be created.
*/
unsigned int AddChart2Atlas(Tparameters *pr,double *ps,unsigned int parentID,
			    boolean *singularity,Tatlas *a);

/** 
   \brief Defines a new chart and adds it to the atlas.

   Version of \ref AddChart2Atlas for atlas in AtlasRRT (construction of a RRT from
   an atlas and the reverse).
   
   In this special version, we add the chart to the atlas and we determine its
   neighbours but without any concern about detecting singularities nor enforcing
   intersection with the parent chart.
   Moreover, we trust that the input point is in the manifold and that its is
   collision free (these conditions are checked when generating the point).

   \param pr The set of parameters.
   \param ps The point (on the manifold) where to define the new chart.
             CAUTION. This point is assumed to be in the simplified system. 
	     (no in the original system as the point given in \ref InitAtlasFromPoint).
	     This kind of points typically result from any manipulation of an existing
	     atlas (\ref RandomPointInAtlas, \ref Chart2Manifold, etc).
   \param parentID Identifier of the parent chart. \ref  NO_UINT if unkown.
   \param singularity [Output] TRUE if the new chart of one of its neighbours is
                      (almost) on a singularity at the given numerical accuracy
		      (see the epsilon parameter). In this case bifurcations
		      might be undetected.
   \param a The atlas where to add the new chart.

   \return Identifier of the new chart or \ref NO_UINT if the chart could not be created.
*/
unsigned int AddTrustedChart2Atlas(Tparameters *pr,double *ps,unsigned int parentID,
				   boolean *singularity,Tatlas *a);

/** 
   \brief Initializes an atlas from a given point.
   
   Initializes an atlas defining a local chart from a given point.
   If the given point is not on the manifold nothing is added to the atlas.

   \param pr The set of parameters.
   \param parallel TRUE if the atlas might be generated/processed in parallel.
                   Only possible if OpenMP is available.
   \param simpleChart TRUE if the atlas is to be defined using simple charts.
   \param p A point on the manifold. A sample including only system variables in
            the original system of equations (not the simplified one).
   \param w The base type with the equations (and possibly obstacles).
   \param a The atlas to create.

   \return TRUE if the atlas can be actually created. Errors are triggered
           if the manifold is singular in the given point.
*/
boolean InitAtlasFromPoint(Tparameters *pr,boolean parallel,boolean simpleChart,double *p,
			   TAtlasBase *w,Tatlas *a);


/** 
   \brief Defines an atlas from a given point.
   
   Defines an atlas from a given point and covering the whole connected component
   including this point.
   
   This procedure can be quite time demanding for high-dimensional manifolds.
   For these cases, we implement a parallel version (via MP). However, currently
   the parallel version can not deal with obstacles (i.e., it can only run
   on cuik files but not on world files).

   \todo Make collision detection re-entrant so that we can use openMP with it
         This basically means to have as many collision detection structures
	 as prallel threads.

   \param pr The set of parameters.
   \param p A point on the manifold. A sample including only system variables. This
            is a point in the original system, with values for all the variables.
   \param simpleChart TRUE if the atlas is to be defined using simple charts.
   \param w The base type with the equations (and possibly obstacles).
   \param a The atlas to create.
*/
void BuildAtlasFromPoint(Tparameters *pr,double *p,boolean simpleChart,
			 TAtlasBase *w,Tatlas *a);

/** 
   \brief Gradient minimization on an manifold.

   Local minimization of a cost function defined on the atlas. The minimization
   is done using gradient descent. The gradient is numerically evaluated.
   The presence of bifurcation si taken into account (if the appropiate
   parameteres are set, see \ref CT_DETECT_BIFURCATIONS) and, thus, different minima
   can be determined. 
   The paths to the minima are stored in separate files.
   
   \param pr The set of parameters.
   \param fname Base name used for the output paths.
   \param p The initial point.
   \param w The base type with the equations (and possibly obstacles).
   \param maxSteps Maximum number of steps of the minimization process.
   \param costF The cost function.
   \param costG The gradient of the cost function, if available. Otherwise
                set to NULl and the gradient is computed numerically.
   \param costData The last parameter of the cost funtion.
   \param a The atlas to be generated during minimization

   \return TRUE if the minimization detected no issue. FALSE if the 
           minimization stepped on a singularity and it could not be
	   determined if it corresponds to a bifurcation. In this case
	   the minimization process might be incomplete.
*/
boolean MinimizeOnAtlas(Tparameters *pr,char *fname,double *p,TAtlasBase *w,
			unsigned int maxSteps,
			double (*costF)(Tparameters*,boolean,double*,void*),
			void (*costG)(Tparameters*,boolean,double*,double**,void*),
			void *costData,
			Tatlas *a);

/** 
   \brief Radius used in the charts.

   Returns the radius used to initialize the charts.

   \param a The atlas to query.

   \return The radius used to initialize all radius.
*/
double GetAtlasRadius(Tatlas *a);

/** 
   \brief Maximum error for all the charts.

   Returns the maximum error from the chart to the manifold.

   \param a The atlas to query.

   \return The maximum error used to initialize all the chart in the atlas.
*/
double GetAtlasError(Tatlas *a);

/** 
   \brief Maximum curvature error for all the charts.

   Returns the maximum curvature error for all the charts, i.e., the maximum
   angle between neighbouring charts.

   \param a The atlas to query.

   \return The maximum curvature error used to initialize all the chart in the atlas.
*/
double GetAtlasErrorCurv(Tatlas *a);

/** 
   \brief Gets the world structure on which the atlas is defined.

   Returns the workd structure defining the manifold to be described by the
   atlas.
   
   \param a The atlas to query.

   \return The world structure with the manifold description.
*/
TAtlasBase* GetAtlasWorld(Tatlas *a);

/** 
   \brief Ambient dimensionality.

   Returns the number of variables of the problem.

   \param a The atlas to query.

   \return The dimensionality of the ambient space.
*/
unsigned int GetAtlasAmbientDim(Tatlas *a);

/** 
   \brief Manifold dimensionality.

   Returns the dimensionality of the manifold described by the atlas.

   \param a The atlas to query.

   \return The dimensionality of the manifold.
*/
unsigned int GetAtlasManifoldDim(Tatlas *a);

/** 
   \brief Finds a point in the intersection of the manifold and a plane.

   Determines a point in the intersection of a given plane and the manifold.
   This is an auxiliary function of \ref FindPointInOtherBranch but it is also
   used when defining an (Atlas)RRT (to incrementally extend a branch of the tree
   toward a given point).

   The point is searched using a Newton procedure where the system of equations 
   defining the manifold is extended with the equation defining the given plane.

   \param pr The set of parameters.
   \param point A passing poing for the plane.
   \param vector The vector defining the plane.
   \param pInit Initial estimation for the solution. If NULL, \e point is used.
   \param p The solution point, if any. The space for this point must be allocated
            externally.
   \param a The atlas.

   \return TRUE if the process converged to a solution.
*/
boolean Newton2ManifoldPlane(Tparameters *pr,double *point,double *vector,
			     double *pInit,double *p,Tatlas *a);

/** 
   \brief Tries to expand the atlas from a chart from a given point.

   Tries to expand the atlas from a given point defined on
   the chart tangent space. This point is assumed to be on the border
   of the atlas (on the ball defined in the given chart and not in any
   other ball from other charts).

   If the new chart can not be properly defined, the we try to try to generate
   it closer to the center of the parent chart.
   When very close to the parent chart center we are supposed to be able to generate
   a new chart without any issues.

   \param pr The set of parameters.
   \param parentID The identifier of the chart where the point is defined. This is the parent
                   of the new chart, if we manage to create it.
   \param t The point in the tangent space to use to expand the atlas..
   \param st To collect statitic information on the atlas extension process.
   \param a The atlas to extend.
   
   \return TRUE if the altas could be actually extended.
*/
boolean ExtendAtlasFromPoint(Tparameters *pr,unsigned int parentID,double *t,
			     TAtlasStatistics *st,Tatlas *a);
/** 
   \brief Tries to expand the atlas from a chart toward a given point.

   This is like \ref ExtendAtlasFromPoint but the process is started close to the
   center of the parent chart and the new chart is progressively generated towards the
   targed point as we have success in generating the new chart.
   In this process, we could even go further that the targed point.
   
   Another difference with \ref ExtendAtlasFromPoint is that here we take into account
   obstacles.

   \param pr The set of parameters.
   \param parentID The identifier of the chart where the point is defined. This is the parent
                   of the new chart, if we manage to create it.
   \param t The point in the tangent space to use to expand the atlas.
   \param collisionStops Set to TRUE if the extension has to be stopped when
                         we detect a collision with an obstacle. Otherwise, the
			 extension proceed while the error is moderate.
   \param st To collect statitic information on the atlas extension process.
   \param a The atlas to extend.
   
   \return TRUE if we could actually extend the atlas.
*/
boolean ExtendAtlasTowardPoint(Tparameters *pr,unsigned int parentID,double *t,
			       boolean collisionStops,
			       TAtlasStatistics *st,Tatlas *a);

/** 
   \brief Expands the atlas to reach a given point.

   Expands the atlas with the purpose to reach a given configuration using
   a A* search strategy.

   \param pr The set of parameters.
   \param p The point to reach.
   \param time The actual time used in planning.
   \param pl Path lenght.
   \param ns The number of steps of the solution path. Zero if no solution exists.
   \param path Sequence of \e ns points to go from the target point to the center of
               the first chart in the atlas.
   \param a The atlas to extend.

   \return TRUE if \e p could be actually reached.
*/
boolean AtlasAStar(Tparameters *pr,double *p,double *time,
		   double *pl,unsigned int *ns,double ***path,Tatlas *a);

/** 
   \brief Expands the atlas to reach a given point.

   Expands the atlas with the purpose to reach a given configuration using
   a Greedy Best First search strategy.

   \param pr The set of parameters.
   \param p The point to reach.
   \param time The actual time used in planning.
   \param pl Path lenght.
   \param ns The number of steps of the solution path. Zero if no solution exists.
   \param path Sequence of \e ns points to go from the target point to the center of
               the first chart in the atlas.
   \param a The atlas to extend.

   \return TRUE if \e p could be actually reached.
*/
boolean AtlasGBF(Tparameters *pr,double *p,double *time,
		 double *pl,unsigned int *ns,double ***path,Tatlas *a);

/** 
   \brief Defines a tree of charts on a manifold.

   Tries to define a tree covereing the manifold. \

   \param pr The set of parameters.
   \param nNodes The number of charts (or nodes) of the tree.
   \param a The atlas to defined. Must have a chart from where to start.
*/
void AtlasTree(Tparameters *pr,unsigned int nNodes,Tatlas *a);

/** 
   \brief Number of charts in the atlas.

   Returns the number of charts in the atlas.

   \param a The atlas to query.

   \return The number of charts in the atlas.
*/
unsigned int GetAtlasNumCharts(Tatlas *a);

/** 
   \brief Gets one of the charts of the chart.

   Returns a pointer to one of the charts of the atlas. 
   Care should be taken not to manipulate the chart (use
   it for query only).

   \param id The identifier of the chart.
   \param a The atlas to query.

   \return A pointer to the requested chart of NULL if no charts with the given
           identifier exists.
*/
Tchart *GetAtlasChart(unsigned int id,Tatlas *a);

/** 
   \brief Samples a random point on the atlas.

   Samples a random point on the part of the manifold covered
   by the atlas with uniform distribution.

   We select a chart with uniform distribution and then a point
   in the tangent space of the selected chart.

   \param pr The set of parameters.
   \param scale Global scale for sampling areas of the charts. This is
                only used for simple charts (see \ref RandomPointInChart).
   \param w Weight for the charts. If NULL uniform distribution is used.
   \param nm Identifier of the chart used to generate the random point.
   \param t Parameters in the chart for the random point.
   \param p The output point in the ambient space (the point int he
            chart given by \e t possibly projected to the manifold).
   \param a The atlas to sample.

   \return TRUE if we actually managed to sample a point in the atlas
           with the given requirements.
*/
boolean RandomPointInAtlas(Tparameters *pr,double scale,double *w,
			   unsigned int *nm,
			   double *t,double *p,Tatlas *a);

/** 
    \brief Approximates the volume of the manifold.

    Approximates the volume of the manifold parametrized by an atlas.

    \param pr  The set of parameters.
    \param collisionFree TRUE if only volume of the collision free of the
                         manifold has to be approximated.
    \param a The atlas.

    \return The volume of the manifold.
*/
double AtlasVolume(Tparameters *pr,boolean collisionFree,Tatlas *a);

/** 
    \brief Saves the graph structure of the atlas.

    Generates a file with the graph structure of the atlas, i.e., storing
    the neighbouring relations between charts.
    The file has
      - The number of charts in the atlas.
      - For each chart
          - The number of neighbours.
	  - The identifier for each neighbour.
	  .
      .

   \param fname Name to use for the two output file. The extension is ".agraph"
   \param a The atlas with the graph structure to store.
*/
void SaveAtlasGraph(char *fname,Tatlas *a);

/** 
   \brief Stores the centers of the charts.

   Stores the centers of the charts in the form of boxes.

   \param pr The set of parameters.
   \param fname Name to use for the two output file. The extension is ".sol"
   \param saveWithDummies TRUE if the output has to include de dummies.
                          This is necessary only if you plan to unsimplify the output
			  points.
   \param a The atlas to query.
*/
void SaveChartCenters(Tparameters *pr,char *fname,
		      boolean saveWithDummies,Tatlas *a);

/** 
   \brief Stores the centers of the singular charts.

   Stores the centers of the singular charts in the form of boxes.

   \param pr The set of parameters.
   \param fname Name to use for the two output file.
   \param saveWithDummies TRUE if the output has to include de dummies.
                          This is necessary only if you plan to unsimplify the output
			  points.

   \param a The atlas to query.
*/
void SaveSingularCharts(Tparameters *pr,char *fname,
			boolean saveWithDummies,Tatlas *a);

/** 
   \brief Pots a projection of an atlas.

   Plots a 3d projection of an atlas defined on a manifold.

   Although the ambien space can have arbitrary dimension we project
   it on 3 dimensions. Only 2D manifolds plots can be properly visualized.

   The output plot can be visualized using geomview.

   \param fname File where to store the plot.
   \param argc Number arguments given to the program calling this function. 
               This is used to write commnets in the output \e gcl file so that the
	       plot can be easiy reproduced.
   \param arg Arguments given to the program calling this function. This is used
              This is used to write commnets in the output \e gcl file so that the
	      plot can be easiy reproduced.
   \param pr The set of parameters.
   \param fcost One cost for each chart in the atlas. Used to associate cost maps
                with the atlas representing each chart with a different color.
                Set to NULL if the atlas is to have a uniform color.
   \param xID The first ambient dimension  where to project (in the original system including
              system vars and dummies). 
   \param yID The second ambient dimension  where to project (in the original system including
              system vars and dummies). 
   \param zID The thrid ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param a The atlas to plot.

   \sa PlotChart.
*/
void PlotAtlas(char *fname,int argc,char **arg,Tparameters *pr,FILE *fcost,
	       unsigned int xID,unsigned int yID,unsigned int zID,Tatlas *a);

/** 
   \brief Pots the triangular mesh defined by the an atlas.

   Plots a 3d projection of triangular mesh formed by the atlas centers.
   This is only well defined for surfaces, i.e., for manifolds of
   dimension 2.
   
   The difference with PlotAtlas is that here only the chart centers
   are used and, thus, the charts are not displayed. 
   The use of a triangular mesh on the chart centers results in
   a smoother visualization. The plot generated with PlotAtlas
   creates a separate polytope for each atlas and, thus there
   are "discontinuities" in between charts. The triangular mesh
   is fully continuous and can be properly smoothed and shaded.

   Although the ambien space can have arbitrary dimension we project
   it on 3 dimensions.

   The output plot can be visualized using geomview.
   
   \param fname File where to store the plot.
   \param argc Number arguments given to the program calling this function. 
               This is used to write commnets in the output \e gcl file so that the
	       plot can be easiy reproduced.
   \param arg Arguments given to the program calling this function. This is used
              This is used to write commnets in the output \e gcl file so that the
	      plot can be easiy reproduced.
   \param pr The set of parameters.
   \param fcost One cost for each chart in the atlas. Used to associate cost maps
                with the atlas representing each chart with a different color.
                Set to NULL if the atlas is to have a uniform color.
   \param xID The first ambient dimension  where to project (in the original system including
              system vars and dummies). 
   \param yID The second ambient dimension  where to project (in the original system including
              system vars and dummies). 
   \param zID The thrid ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param a The atlas to plot.

   \sa PlotAtlas.
*/
void TriangulateAtlas(char *fname,int argc,char **arg,Tparameters *pr,FILE *fcost,
		      unsigned int xID,unsigned int yID,unsigned int zID,Tatlas *a);

/** 
    \brief Memory used by a given atlas.

    Returns the approximated memory used (in bytes) by a given atlas.

    \param a The atlas.

    \return The size of the atlas in bytes.
*/
unsigned int AtlasMemSize(Tatlas *a);

/** 
   \brief Stores the atlas information on a file.

   Stores all the information in the atlas in a file.

   \todo Save atlas (and charts) in binary format.

   \param pr The set of parameters.
   \param fname Name of the file where to store the atlas.
   \param a The atlas to store.
*/
void SaveAtlas(Tparameters *pr,Tfilename *fname,Tatlas *a);

/** 
   \brief Defines an atlas from the information on a file.

   Construct an atlas from the information previously stored in a file
   by \ref SaveAtlas.

   \param pr The set of parameters.
   \param fname The name of the file from where to get the information.
   \param w The world with the equations defining the manifold where the atlas
            is defined. This is not stored in the file and must be provided
	    externally.
   \param a The atlas to define.
*/
void LoadAtlas(Tparameters *pr,Tfilename *fname,TAtlasBase *w,Tatlas *a);

/** 
   \brief Average number of neighbouring charts.

   Computes the average number of neighbouring charts. This is only
   used for debugging purposes.

   \param a The atlas

   \return The average number of neighbours per chart.
*/
double AverageNumNeighbours(Tatlas *a);

/** 
   \brief Prints defines.

   Prints the defines in atlas.h

   This is used only for debug purposes.
   
   \param f The file where to store the values.
*/
void PrintAtlasDefines(FILE *f);

/** 
   \brief Destructor.

   Deletes the information stored in the atlas.

   \param a The atlas to delete.
   
*/
void DeleteAtlas(Tatlas *a);

#endif
