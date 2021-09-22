#include "atlas.h"

#include "defines.h"
#include "error.h"
#include "random.h"
#include "algebra.h"
#include "samples.h"

#include <string.h>
#include <math.h>
#ifdef _OPENMP
  #include <omp.h>
#endif

/** 
   \file atlas.c

   \brief Implementation of an atlas on a manifold.

   Implementation of a set of local charts on a manifold.

   \sa Tatlas,atlas.h
*/

/***************************************************************/

/** 
   \brief A minimization trace.

   Trace followed during minimization on the atlas. 
*/
typedef struct {
  unsigned int st; /**< Steps taken in the minimization of this branch */
  unsigned int nc; /**< The current chart. Chart from where the minimization
                        must continue. */
  unsigned int ns; /**< The number of samples along the minimization path. */
  unsigned int ms; /**< The maximum number of samples in the path. */
  double **path;   /**< The minimization path so far. */
} TMinTrace;



/***************************************************************/

/** 
   \brief Information of each node (chart) being visited in the A* search.

   Information of each node (chart) visited in the A* search.
*/
typedef struct {
  double cost;         /**< Cost from the start node. */
  double heuristic;    /**< Heuristic estimation of the cost to the goal. */
  unsigned int status; /**< Status: 0: don't know  1:open  2:closed */
} TAStarInfo;

/***************************************************************/

/** 
   \brief Init the atlas built statistics.
   
   Init the atlas built statistics.

   \param ast The atlas statistics to update.
*/
void InitAtlasStatistics(TAtlasStatistics *ast);

/** 
   \brief New attempt to extend the atlas.

   New attempt to extend the atlas.

   \param ast The atlas statistics to update.
*/
void NewAtlasExtension(TAtlasStatistics *ast);

/** 
   \brief New attempt to generate a point on the boundary.

   New attempt to generate a point on the boundary.

   \param ast The atlas statistics to update.
*/
void NewBoundaryAttempt(TAtlasStatistics *ast);
/** 
   \brief New time we failed to generate a point on the boundary.

   New time we failed to generate a point on the boundary.

   \param ast The atlas statistics to update.
*/
void NewNotInBoundary(TAtlasStatistics *ast);
/** 
   \brief New time the point in the tangent space was too far form the manifold.

   New time the point in the tangent space was too far form the manifold.

   \param ast The atlas statistics to update.
*/
void NewLargeError(TAtlasStatistics *ast);
/** 
   \brief New time we could not initialize a new chart.

   The chart initialization failed since the given point is
   non-regular up to the given numerical error.

   \param ast The atlas statistics to update.
*/
void NewNonRegularPoint(TAtlasStatistics *ast);
/** 
   \brief New time we could not initialize a new chart.

   The chart initialization failed since the given point is
   not on the manifold.

   \param ast The atlas statistics to update.
*/
void NewNotInManifold(TAtlasStatistics *ast);
/** 
   \brief New time we could not initialize a new chart.

   The chart initialization failed since the QR or SVD
   decomposition used to compute the tangent space failed.

   \param ast The atlas statistics to update.
*/
void NewDecompositionError(TAtlasStatistics *ast);
/** 
   \brief New time the point was too far from parent.

   New time the point was too far from parent. The distance is measured not
   only in Euclidena space but we also compare the tangent spaces (they must
   be similar).

   \param ast The atlas statistics to update.
*/
void NewFarFromParent(TAtlasStatistics *ast);
/** 
   \brief New time the point was in collision.

   New time the point was too far in collision.

   \param ast The atlas statistics to update.
*/
void NewInCollision(TAtlasStatistics *ast);

/** 
   \brief New time we had to change the sampling radious to get a new chart.

   New time we had to change the sampling radious to get a new chart.

   \param ast The atlas statistics to update.
*/
void NewRadiousChange(TAtlasStatistics *ast);
/** 
   \brief New time we actually succeeded in creating a new chart.
   
   New time we actually succeeded in creating a new chart.

   \param ast The atlas statistics to update.
*/
void NewGoodExtension(TAtlasStatistics *ast);

/** 
   \brief New Error when extending from/toward a point.

   When extending from a point we progressively
   reduce the radious of expansion until we find a point
   where it its possible to properly define a new chart.
   In some wear situations even reducing the radius below
   the given \ref MIN_SAMPLING_RADIUS, it is impossible
   to generate a child chart. Note that this should never happen
   but it actually occurs due to numerical issues.

   When extending towards a point, the situations arises
   when even at the first step of the motion toward the new
   point the generation of a new chart fails.

   In general this is a ill-posed situation and we should
   trigger an error and stop the chart construction. In some
   cases, however we just mark the problematic point and
   continue the atlas extension. Note that this can lead
   to incomplete atlas if the skiped point was actually
   necessary to complete the manifold coverage.

   If we tolerate this error, at least we count
   how many times this awful situation actually occurs.
   If it occurs few times we can assume that the chart is
   fully constructed (the skiped point is likely to be
   covered when expanding from/toward another point).
   If we have many situations of this type we have to assume
   we ended up with an incomplete atlas and to solve the issue.
   Many times using a smaller \e Epsilon.
*/
void NewImpossible(TAtlasStatistics *ast);

/** 
   \brief New time we could not extend a singular chart.

   This is like the situation for \ref NewImpossible but
   when it occurs on a singular chart. We have to tolerate
   this situations since the mapping from the chart to the
   manifold then to be ill-conditioned when close to the
   singularity and it may fail. For normal charts we have
   the hypothesis that this mapping is safer as closer
   to the chart center.
*/
void NewSingularImpossible(TAtlasStatistics *ast);

/** 
   \brief New processed bifurcation.
   
   A new bifurcation is processed.

   \param ast The atlas statistics to update.
*/
void NewBifurcation(TAtlasStatistics *ast);

/** 
   \brief Small angle between the charts at a bifurcation.

   We managed to detect the bifurcation, detect the singular
   point and jump but the tangent space at the new point
   is too similar to the one at the known branch of the
   variety. This problably means that the ended up in 
   the same branch of the variety (it could also mean
   that the two branches intersect with a very small angle)
*/
void NewSmallAngleAtBifurcation(TAtlasStatistics *ast);

/** 
   \brief New missed singular point.
   
   We detected a bifurcation but did not manage to locate the singular
   point.

   \param ast The atlas statistics to update.
*/
void NewSingularPointMissed(TAtlasStatistics *ast);

/** 
   \brief New not singular engoug point.

   We detected a bifurcation and located a singular point but the
   tangent space defined at the singular point is only of dimension
   'k' (it should be of dimension k+1). Without the additional vector
   in the tangent space we can not jump to the new branch.
*/
void NewNoSingularEnough(TAtlasStatistics *ast);

/** 
   \brief The jump to the other branch failed.

   We detected the bifurcation, located the singular point, computed
   the additional vector of the tangent space at this point but
   we did not managed to actually jump to the other branch of the
   variety.
*/
void NewNoJumpBranch(TAtlasStatistics *ast);
/** 
   \brief Print the information stored in the statistics..

   \param pr The set of parameters.
   \param ast The atlas statistics to print.
*/
void PrintAtlasStatistics(Tparameters *pr,TAtlasStatistics *ast);

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/** 
   \brief Determines if there is a chart close to a given point.

   Determines if we already hava a chart close to a given point. This is
   used to avoid inserting (almost) the same chart twice when
   building an atlas in parallel.

   \param eps The accuracy in the comparison.
   \param p The point.
   \param a The atlas to query.
*/
boolean HaveChartAtPoint(double eps,double *p,Tatlas *a);

/** 
   \brief Post-processes the charts added since the last call to this function.

   Charts are added to the atlas and latter on they are post-processed. In this
   post-process we determine the neighbours for each chart and detect possible
   bifurcations. The post-process must be called after any atlas extension for
   a given chart (this can include the generation of one or more children charts).

   \param pr The set of parameters.
   \param bif TRUE if the post-process has to include the bifurcation detection.
   \param parentID The parent chart. The chart used to generate the new
                   charts.
   \param st The atlas statistics.
   \param a The atlas to post-process.
*/
void PostProcessNewCharts(Tparameters *pr,boolean bif,unsigned int parentID,
			  TAtlasStatistics *st,Tatlas *a);

/** 
   \brief Generates a chart from a vertex taken from a parent chart.

   This is very similar to \ref ExtendAtlasFromPoint but we do not take 
   statistics of the atlas construction and the treatment of the atlas 
   borders is simpler.
   Moreover, we do not add the chart to the atlas, but just generate a new
   chart (if no error is encountered in the process).

   Latter on we have to add the generated chart to the atlas (detecting
   neighbours and dealing with bifurcations, if any).

   This is used when parallelizing the atlas construction process: all the
   external vertexes of a chart can be processed in parallel and the resulting
   charts added to the atlas (search for neighbours and treat bifurcations)
   in sequence.

   \param pr The set of parameters.
   \param parentID The chart from which the new point is selected.
   \param t Parameters giving the point (on the chart ball).
   \param newChart The generated new chart, if any. Set to NULL if the chart
                   can not be defined.
   \param a The atlas.
   
*/
void NewChartFromPoint(Tparameters *pr,unsigned int parentID,double *t,
		       Tchart **newChart,Tatlas *a);

/** 
   \brief Reconstructs the path between the stat/goal configurations.

   Defines the path between the start and goal configurations navigating
   along the paths found in the atlas.

   \param pr The set of parameters.
   \param pred The parent for each chart in the atlas.
   \param mID The identifier of the chart containing the goal (the start is assumed
              to be in chart 0).
   \param goal The final goal of the sample.
   \param nv Number of variables to keep for each path step.
   \param systemVars Boolean array identifying the variables we want to keep for
                     each step in the path.
   \param pl The length of the output path.
   \param ns The number of steps of the output path.
   \param path The output path (array with points in the mainifold).
   \param a The atlas.

   \sa Connect2Atlas,Connect2AtlasRRT.
*/
void ReconstructAtlasPath(Tparameters *pr,unsigned int *pred,
			  unsigned int mID,double *goal,unsigned int nv,
			  boolean *systemVars,
			  double *pl,unsigned int *ns,double ***path,Tatlas *a);

/** 
   \brief Determines the neighbours of a chart.

   Searches for charts close to the current one, determines if they are actually
   neighbours (close enough and with similar tangent spaces) and crops the 
   two charts so that they do not overlap. The crop is performed in the
   polytope bounding the chart ball (defined in tangent space).
   
   This is typically used for chart generated from other charts (using
   \ref ExtendAtlasTowardPoint or \ref ExtendAtlasFromPoint). In those cases
   the new chart center is close to its parent chart and there must be and
   intersection between the parent and the child. If there is not an error is
   triggered. When charts are generated in this hierarchical fashion, we only
   check for singularities in the transitions between parents and children.
   This save many checks but still ensures that singularities will be detected.

   However, this function can also be used for a chart generated from a point
   not necessaritly close to any other chart (i.e. for a new chart with not
   known parent). In this case no error is triggered is the chart does not
   intersect with any special chart. Moreover, in this case we check for
   singularity detection in any neighgouring relation.

   We assume that the chart 'cmID' has never been checked for intersection
   with the rest of the atlas.

   \param pr The set of parameters.
   \param bif TRUE if we want to detect bifurcation points. This is always TRUE
              except when searching for the neighbours of a bifurcation point.
   \param cmID The identifier of the chart to connect to the atlas.
   \param parentID The identifier of the parent chart, the chart from which the 
                   chart 'cmID' was generated. Use NO_UINT if the parent is not
		   known.
   \param a The atlas to update.

   \return TRUE if no issue was detected when determining the neighbours
           FALSE if an issue was detected. Typically a neighbour chart defined on a 
	   singularity at the given numerical accuracy. This cause bifurcations 
	   to be undetected. Can only be FALSE if parameter bif is TRUE.
*/
boolean DetermineChartNeighbours(Tparameters *pr,boolean bif,
				 unsigned int cmID,unsigned int parentID,Tatlas *a);

/** 
   \brief Approximates the geodesic distance between the centers of two charts.

   Approximates the geodesic distance between the centers of two charts by 
   computing intermediated points from the center of the parent chart to
   the center of the child chart.

   If the path between the two chart centers is blocked by obstacles the
   return is inf.

   The steps are taken by linear interpolation between the chart centers
   and the projecting to the manifold via Newton.
   We do not use the tangent space at the parent chart to do the parametrization
   since its validity area might not reach the center of the child.
   
   If in any of the intermediate steps we did not manage to determine a point
   on the manifold the process is stopped and the return is inf (meaining it
   is not posssible to directly connect the two chart centers.

   \param pr The set of parameters.
   \param parentID The chart from where to start to measure.
   \param childID The targed chart.
   \param a The atlas with the charts.

   \return Approximated distance over the manifold between the centers
           of the two given charts.
*/
double GeodesicDistance(Tparameters *pr,unsigned int parentID,unsigned int childID,
			Tatlas *a);

/** 
   \brief Initializes the topology array in the atlas.

   Initializes the topology array in the atlas.

   \param pr The set of parameters.
   \param a The atlas where to initialize the topology.
*/
void SetAtlasTopology(Tparameters *pr,Tatlas *a);

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/** 
   \brief Determines if there is a bifurcation between the center of two charts.

   Determines if there is a bifurcation between the center of two charts.

   This process potentially generates a set of new bifurcations that are latter
   processed using \ref ProcessBifurcation.

   \param pr The set of parameters.
   \param mID1 The first chart.
   \param mID2 The second chart.
   \param a The atlas.
   
   \return TRUE if the bifurcation detection encountered no problem and FALSE
           if an error was detected (typically that one of the charts is 
	   defined on a singularity at the current numerical accuracy).
*/
boolean DetectBifurcation(Tparameters *pr,unsigned int mID1,unsigned int mID2,Tatlas *a);

/** 
   \brief Searches for a singular point.
   
   Once a bifurcation is detected, we have to determine the singular point, i.e., the
   point where the bifurcation actually occur. If found, the point is stored
   in the corresponding bifurcation structure.
   
   Note that since all our procedures are accurate up to epsilon, the singular point
   is not actually found, but we find an approximation of it. This means that at
   the returned point the Jacobian is not perfectly singular (but close to be singular).

   This is one of the steps executed in the \ref ProcessBifurcation procedure.

   \todo Stop the search if we end up in the other branch just by chance.

   \param pr the set of parameters.
   \param bID The bifurcation we are processing.
   \param a The atlas.

   \return TRUE if the singular point could be actually found.
*/
boolean FindSingularPoint(Tparameters *pr,unsigned int bID,Tatlas *a);

/** 
   \brief Improves the locatin f a singular point.

   This function was intented as a replacement of \ref FindSingularPoint with
   the idea of defining the singular points analytically and using a Newton
   process to avoid the slow dicotomic search in \ref FindSingularPoint.

   However, the Newton process does not converge to the singularity unless
   we start the process very close to it (and even in this case it is
   many times divergent). 
   Thus we reformulate this function as a refinement of the singular point
   localization implemented in \ref FindSingularPoint.
   
   Note that this function is not actually used but we keep it because we
   expended a lot of effort in its implementation and it could be actually
   useful if we ever improve it.
   For instance, if this function worked properly, we could save the
   use of \ref FindRightNullVector since the lambda part of the solution
   found (but not used by this function) is the new right null vector
   now determined in \ref FindRightNullVector
   
   \param pr the set of parameters.
   \param bID The bifurcation we are processing.
   \param a The atlas.

   \return TRUE if the singular point could be accurately determined.
*/
boolean RefineSingularPoint(Tparameters *pr,unsigned int bID,Tatlas *a);

/** 
   \brief Finds the right null vector that does not belong to the tangent space.

   Finds the right null vector that does not belong to the tangent space.
   We basically compute a basis of the kernel of the Jacobian at the singular point.
   If theory (when the perfectly determined the singular point) the kernel will
   have dimension k+1. In practice we have dimension k plus one vector corresponding
   to a small (but not zero) eigenvalue. The kernel vectors (plus the addiontal one)
   can be determined finding the lowest eigenvalues (or value of the diagonal of R
   assuming as 0 those not present).

   We proceed as when computing the kernel of a Jacobian and we check for each candiate
   to belong to the basis of the kernel if it is aligned with the provided tangent
   space (an approximation of the tangent space at the singularity). We return
   the less aligned vector.

   \param pr The set of parameters.
   \param bID The bifuraction in process.
   \param phi Space for the output right null vector.
   \param a The atlas.
   
   \return 0 if we could determine the right null vector properly, 
           1 if the bifurcation structure is actually defined in the other aspect 
             of the manifold, and
           2 if we could not determine the right null vector.
*/
unsigned int FindRightNullVector(Tparameters *pr,unsigned int bID,
				double **phi,Tatlas *a);


/** 
   \brief Searches for a point in the other manifold branch.

   Once we detected a bifurcation point (\ref DetectBifurcation), we precisely
   locate it (\ref FindSingularPoint) and we have the additional vector of
   the null space of the Jacobian (\ref FindRightNullVector), we have now to
   locate a point in the other branch manifold.
 
   To do it, we move in the from the singular point in the direction of the new
   vector of the Jacobian kernel basis. This generates a point away from the
   current manifold branch (which localy is close to the tangent space at the
   bifrucation that is approximated by the tangent space on one of the points
   used to detect the singular point).
   
   From this point we try to reach the manifold but moving on a sub-space parallel
   to the tangent space of the for the known manifold branch. In this way we 
   maximize the probability of reaching the other manifold branch.
   
   The solution point should be on the manifold (\f$F(x)=0\f$) and should be in the kernel
   of the Jacobian at the singular point (\f$J x=0\f$). When solving this using Newton
   we have a matrix A with two Jacobians, one at the current point and another
   at the singularity (actually we have one basis of the Jacobian at the bifurcation
   point and a full Jacobian, possibly with redundant equations, at the current point).

   This procedure does not works alwasy but is is simple and works in many cases.
   
   \todo Intoduce checks to  see is we converged relatively close to the departing point.
         If we converge too far away we had better not use the the final point.

   \param pr The set of parameters.
   \param bID The bifurcation in process.
   \param phi The new null vector of the kernel of the Jacobian.
   \param p The output point on the manifold.
   \param a The atlas.

   \return TRUE if we managed to reach the manifod (even if it is in the already
           known branch.
*/
boolean FindPointInOtherBranch(Tparameters *pr,unsigned int bID,double *phi,double **p,Tatlas *a);


/** 
   \brief Defines two related charts on a bifurcation point.

   When we detecta a bifurcation, we define two charts, one at the current branch
   of the variety, and one at the new branch. These two charts are related so that
   we can eventually cross the singularity without jumps when planning.

   This is typically the final step of \ref ProcessBifurcation but we can use
   it as soon as we identify a point in the new branch of the variety (this can
   happen in the process of finding the bifurcation point).

   \param pr The set of parameters. 
   \param bID The index of the bifurcation.
   \param v A point in the other branch of the varity.
   \param ast Statistics about the atlas construction. Can be NULL if no statistics 
              are collected.
   \param a The atlas where to add the charts.
*/
void DefineChartsAtBifurcation(Tparameters *pr,unsigned int bID,double *v,
			       TAtlasStatistics *ast,Tatlas *a);

/** 
   \brief Processes the bifurcation points not yet processed.

   Processes the bifurcation points generated in the last calls to \ref DetectBifurcation
   that are not yet processed. This amounts to detect the singular point in between
   the two chart centers, to generate a chart in the \e other branch of the manifold, and
   to search for its neighbours.

   \todo Implement this!

   \param pr The set of parameters.
   \param bID The index of the bifurcation to process.
   \param ast Statistics about the atlas construction. Can be NULL if no statistics 
              are collected.
   \param a The atlas with the bifurcation information to process.
*/
void ProcessBifurcation(Tparameters *pr,unsigned int bID,TAtlasStatistics *ast,Tatlas *a);

/** 
   \brief Loads the bifurcation information from a file.

   Loads the bifurcation information from a file.
   
   \param f The file from where to read the information.
   \param a The atlas where to store it.
*/
void LoadBifurcations(FILE *f,Tatlas *a);

/** 
   \brief Saves the bifurcation information to a file.

   Saves the bifurcation information to a file.
   
   \param f The file where to store the information.
   \param a The atlas where to take it.
*/
void SaveBifurcations(FILE *f,Tatlas *a);

/** 
   \brief Plots the bifurcation information.

   Plots a red line connecting the chart center that are at the two sides
   of a bifurcation.
   
   \param pr The set of parameters.
   \param p3d The 3d plot where to add the lines.
   \param xID The first ambient dimension  where to project (in the original system including
              system vars and dummies). 
   \param yID The second ambient dimension  where to project (in the original system including
              system vars and dummies). 
   \param zID The thrid ambient dimension  where to project (in the original system including
              system vars and dummies).
   \param a The atlas where to take the bifurcation information.
*/
void PlotBifurcations(Tparameters *pr,Tplot3d *p3d,
		      unsigned int xID,unsigned int yID,unsigned int zID,Tatlas *a);

/** 
   \brief Deletes the bifurcation information.
   
   Deletes the bifurcation information stored in the atlas.
   
   \param a The atlas with the bifurcation information to delete.
*/
void DeleteBifurcations(Tatlas *a);

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

void InitAtlasStatistics(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    {
      ast->nExtensions=0;
      ast->nBoundaryAttempts=0;
      ast->nNotInBoundary=0;
      ast->nLargeError=0;
      ast->nNonRegularPoint=0;
      ast->nNotInManifold=0;
      ast->nQRSVDError=0;
      ast->nFarFromParent=0;
      ast->nInCollision=0;
      ast->nRadiousChange=0;
      ast->nGoodExtension=0;
      ast->nImpossible=0;
      ast->nSingImpossible=0;
      ast->nBifurcations=0;
      ast->nSmallAngle=0;
      ast->nSPMissed=0;
      ast->nNoSingularEnough=0;
      ast->nNoJumpBranch=0;
    }
}

void NewAtlasExtension(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nExtensions++;
}

void NewBoundaryAttempt(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nBoundaryAttempts++;
}

void NewNotInBoundary(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nNotInBoundary++;
}

void NewLargeError(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nLargeError++;
}

void NewNonRegularPoint(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nNonRegularPoint++;
}

void NewNotInManifold(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nNotInManifold++;
}

void NewDecompositionError(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nQRSVDError++;
}

void NewFarFromParent(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nFarFromParent++;
}

void NewInCollision(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nInCollision++;
}

void NewRadiousChange(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nRadiousChange++;
}

void NewGoodExtension(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nGoodExtension++;
}

void NewImpossible(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nImpossible++;
}

void NewSingularImpossible(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nSingImpossible++;
}

void NewBifurcation(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nBifurcations++;
}

void NewSmallAngleAtBifurcation(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nSmallAngle++;
}

void NewSingularPointMissed(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nSPMissed++;
}

void NewNoSingularEnough(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nNoSingularEnough++;
}

void NewNoJumpBranch(TAtlasStatistics *ast)
{
  if (ast!=NULL)
    ast->nNoJumpBranch++;
}

void PrintAtlasStatistics(Tparameters *pr,TAtlasStatistics *ast)
{ 
  unsigned int db;

  if (ast!=NULL)
    {
      printf("Boundary attempts: %u\n",ast->nBoundaryAttempts);      
      printf("  Not in Boundary   : %u (%3.2f)\n",
	     ast->nNotInBoundary,
	     100*(double)ast->nNotInBoundary/(double)ast->nBoundaryAttempts);
      printf("Num Extensions   : %u\n",ast->nExtensions);
      printf("  Errors            : %u (%3.2f)\n",
	     ast->nImpossible,
	     100*(double)ast->nImpossible/(double)ast->nExtensions);
      printf("  Errors (Sing)     : %u (%3.2f)\n",
	     ast->nSingImpossible,
	     100*(double)ast->nSingImpossible/(double)ast->nExtensions);
      printf("  Large Error       : %u (%3.2f)\n",
	     ast->nLargeError,
	     100*(double)ast->nLargeError/(double)ast->nExtensions);    
      printf("  Non-regular point : %u (%3.2f)\n",
	     ast->nNonRegularPoint,
	     100*(double)ast->nNonRegularPoint/(double)ast->nExtensions);
      printf("  Not in Manifold   : %u (%3.2f)\n",
	     ast->nNotInManifold,
	     100*(double)ast->nNotInManifold/(double)ast->nExtensions);
      printf("  Decomp. Error     : %u (%3.2f)\n",
	     ast->nQRSVDError,
	     100*(double)ast->nQRSVDError/(double)ast->nExtensions);
      printf("  Far From Parent   : %u (%3.2f)\n",
	     ast->nFarFromParent,
	     100*(double)ast->nFarFromParent/(double)ast->nExtensions);
      printf("  Radius Changes    : %u (%3.2f)\n",
	     ast->nRadiousChange,
	     100*(double)ast->nRadiousChange/(double)ast->nExtensions);
      printf("  Collisions        : %u (%3.2f)\n",
	     ast->nInCollision,
	     100*(double)ast->nInCollision/(double)ast->nExtensions);
      printf("  Good ones         : %u (%3.2f)\n",
	     ast->nGoodExtension,
	     100*(double)ast->nGoodExtension/(double)ast->nExtensions);

      db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr);
      if (db==0)
        printf("Bifurcation detection disabled\n");
      else
	{
	  printf("Detected bifurcations: %u\n",ast->nBifurcations);
	  if (ast->nBifurcations>0)
	    {
	      unsigned int n;
	      
	      n=(ast->nBifurcations-ast->nSPMissed-ast->nNoSingularEnough-ast->nNoJumpBranch);
	      printf("  Correct jumps         : %u (%3.2f)\n",
		     n,100*n/(double)ast->nBifurcations);
	      if (n>0)
		printf("    Num Small angle     : %u (%3.2f)\n",ast->nSmallAngle,
		       100*(double)ast->nSmallAngle/(double)n);
	      printf("  Missed singular points: %u (%3.2f)\n",ast->nSPMissed,
		     100*(double)ast->nSPMissed/(double)ast->nBifurcations);
	      printf("  Not enough singular   : %u (%3.2f)\n",ast->nNoSingularEnough,
		     100*(double)ast->nNoSingularEnough/(double)ast->nBifurcations);
	      printf("  Error jumping         : %u (%3.2f)\n",ast->nNoJumpBranch,
		     100*(double)ast->nNoJumpBranch/(double)ast->nBifurcations);
	    }
	}
    }
}

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

boolean HaveChartAtPoint(double eps,double *p,Tatlas *a)
{
  boolean found;
  
  #if (USE_ATLAS_TREE)
    found=PointInBTree(eps,p,&(a->tree));
  #else
    unsigned int i;
    double e2,d;
    
    found=FALSE;
    e2=eps*eps;
    for(i=0;((!found)&&(i<a->currentChart));i++)
      {
	d=SquaredDistanceTopologyMin(e2,a->m,a->tp,
				     p,GetChartCenter(a->charts[i]));
	found=(d<e2);
      }
  #endif
  return(found);
}

void PostProcessNewCharts(Tparameters *pr,boolean bif,unsigned int parentID,
			  TAtlasStatistics *st,Tatlas *a)
{
  unsigned int i;
  
  for(i=a->npCharts;i<a->currentChart;i++)
    {
      if (!DetermineChartNeighbours(pr,bif,i,parentID,a))
	Warning("Bifurcation undetected in PostProcessNewCharts. Redude epsilon?");
    }
  a->npCharts=a->currentChart;
  
  /* If parentID is NO_UINT we are defining charts at a bifurcation (we are inside
     ProcessBifurcation) and, thus, we have to avoid infitinte loops. */
  if (parentID!=NO_UINT)
    {
      /* if bif==FALSE no new bifurcations will be detected and, thus, the code
	 below is not used (nBifurcations==npBifurcations). In some cases, though
	 bifurcations are detected externally (see AddChart2AtlasNS) and, thus
	 they are processed here. */
      for(i=a->npBifurcations;i<a->nBifurcations;i++)
	ProcessBifurcation(pr,i,st,a);
      a->npBifurcations=a->nBifurcations;
    }
}

void NewChartFromPoint(Tparameters *pr,unsigned int parentID,double *t,
		       Tchart **newChart,Tatlas *a)
{ 
  /* If the vertex is already inside the ball, we are refining the approximation of the
     domain border. Thus, we have to avoid the eventual creation of new charts.*/
  if (Norm(a->k,t)<0.99*a->r)
    *newChart=NULL;
  else
    {
      double s;
      boolean canContinue,chartCreated,smallError,closeEnough,wrong,outOfDomain;
      double *pt,*ct;
      unsigned int chartCode;
      double epsilon;

      NEW(pt,a->m,double);
      
      NEW(*newChart,1,Tchart);
      
      /* current set of parameters */
      NEW(ct,a->k,double);      

      epsilon=GetParameter(CT_EPSILON,pr);

      s=1.0;
      canContinue=TRUE;
      chartCreated=FALSE;
      closeEnough=FALSE;
      smallError=FALSE;
      outOfDomain=FALSE;

      do {
	/* update the current set of paremter (ct) using the given parameters (t)
	   and the current scale factor (s) */
	memcpy(ct,t,a->k*sizeof(double));
	ScaleVector(s,a->k,ct);

	smallError=(Chart2Manifold(pr,&(a->J),ct,NULL,NULL,pt,a->charts[parentID])<=a->e);

	if (smallError)
	  {
	    chartCode=InitChart(pr,a->simpleChart,a->ambient,a->tp,
				a->m,a->k,pt,a->e,a->ce,a->r,&(a->J),a->w,
				*newChart);
	    chartCreated=(chartCode==0);
	    
	    if (chartCreated)
	      {
		if ((CollisionChart(*newChart))||
		    (!PointInBoxTopology(NULL,TRUE,a->m,pt,epsilon,a->tp,a->ambient))||
		    (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pt,a->w)))
		  outOfDomain=TRUE;
		else
		  closeEnough=(CloseCharts(pr,a->tp,
					   a->charts[parentID],
					   *newChart));
	      }
	  }

	if (!outOfDomain)
	  {
	    wrong=((!smallError)||(!chartCreated)||(!closeEnough));
	    
	    if (wrong)
	      {
		canContinue=(s>MIN_SAMPLING_RADIUS);
		if (canContinue)
		  {
		    s*=SAMPLING_RADIUS_REDUCTION_FACTOR;

		    /* We will create a new chart -> delete the just generated one, if any */
		    if (chartCreated)
		      {
			DeleteChart(*newChart);
			chartCreated=FALSE;
		      }
		  }
	      }
	  }
      } while((!outOfDomain)&&(wrong)&&(canContinue));
      
      /* If we didn't manage to create the new chart, we remove any possibly created chart. */
      if ((outOfDomain)||(!canContinue))
	{
	  if (outOfDomain)
	    ChartIsFrontier(a->charts[parentID]);
	  if (chartCreated)
	    DeleteChart(*newChart);
	  free(*newChart);
	  *newChart=NULL;
	}
      free(ct);
      free(pt);	    
    }
}

boolean ExtendAtlasFromPoint(Tparameters *pr,unsigned int parentID,double *t,
			     TAtlasStatistics *st,Tatlas *a)
{
  double s;
  boolean canContinue,canInitChart,smallError,closeEnough,wrong;
  boolean searchBorder,inside;
  double *pt,*ct;
  boolean ok;
  unsigned int chartCode;
  double epsilon;
  #if (!SIMPLE_BORDER)
    boolean outOfDomain;
    double l,u;
  #endif

  ok=FALSE; /* No new chart is generated */

  NEW(pt,a->m,double);

  if (a->currentChart==a->maxCharts)
    MEM_DUP(a->charts,a->maxCharts,Tchart *);

  NEW(a->charts[a->currentChart],1,Tchart);
  
  /* current set of parameters */
  NEW(ct,a->k,double);
  
  /* If the vertex is already inside the ball, we are refining the approximation of the
     domain border. Thus, we have to avoid the eventual creation of new charts.*/
  inside=(Norm(a->k,t)<0.99*a->r);

  epsilon=GetParameter(CT_EPSILON,pr);

  s=1.0;
  canContinue=TRUE;
  canInitChart=FALSE;
  closeEnough=FALSE;
  smallError=FALSE;
  searchBorder=FALSE;
  #if (!SIMPLE_BORDER)
    outOfDomain=FALSE;
  #endif

  do {
    NewAtlasExtension(st);

    canInitChart=FALSE; /* Just to indicate that no chart has been created so far in this iteration */

    /* update the current set of paremter (ct) using the given parameters (t)
       and the current scale factor (s) */
    memcpy(ct,t,a->k*sizeof(double));
    ScaleVector(s,a->k,ct);

    smallError=(Chart2Manifold(pr,&(a->J),ct,NULL,NULL,pt,a->charts[parentID])<=a->e);

    if (smallError)
      {
	/* We skip the chart construction during the dichotomic search for the border.
	   A valid chart was already been defined when triggering the search. */
	if (searchBorder)
	  {
	    #if (!SIMPLE_BORDER)
	      outOfDomain=((!PointInBoxTopology(NULL,TRUE,a->m,pt,epsilon,a->tp,a->ambient))||
			   (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pt,a->w)));
	      if (!outOfDomain)
		CS_WD_IN_COLLISION(outOfDomain,pr,pt,NULL,a->w);
	    #endif
	    
	    chartCode=NO_UINT; /* -> chart actually not created */
	  }
	else
	  {
	    chartCode=InitChart(pr,a->simpleChart,a->ambient,a->tp,
				a->m,a->k,pt,a->e,a->ce,a->r,&(a->J),a->w,
				a->charts[a->currentChart]);
	    canInitChart=(chartCode==0);

	    if (canInitChart)
	      {
		if ((CollisionChart(a->charts[a->currentChart]))||
		    (!PointInBoxTopology(NULL,TRUE,a->m,pt,epsilon,a->tp,a->ambient))||
		    (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pt,a->w)))
		  {
		    #if (!SIMPLE_BORDER)
		      outOfDomain=TRUE;
		    #endif
		    searchBorder=TRUE;
		    #if (!SIMPLE_BORDER)
		      l=0;
		      u=s;
		    #endif
		  }
		else
		  {
		    #if (!SIMPLE_BORDER)
		      outOfDomain=FALSE;
		    #endif

		    closeEnough=(CloseCharts(pr,a->tp,
					     a->charts[parentID],
					     a->charts[a->currentChart]));
		    if (!closeEnough)
		      {
			NewFarFromParent(st);
			searchBorder=FALSE; /* if searching for border -> stop the search */
		      }
		    else
		      NewGoodExtension(st);
		  }
	      }
	    else
	      {
		switch (chartCode)
		  {
		  case 1:
		  case 2:
		    NewNonRegularPoint(st);
		    break;
		  case 3:
		    NewDecompositionError(st);
		    break;
		  case 4:
		    NewNotInManifold(st);
		    break;
		  default:
		    Error("Unknown chart creation error code");
		  }	
	      }
	  }
      }
    else
      {
	NewLargeError(st);
	searchBorder=FALSE; /* if searching for border -> stop the search */
      }

    wrong=((searchBorder)||(!smallError)||(!canInitChart)||(!closeEnough));

    if (wrong)
      {
	/* If something when wrong but we created a chart -> delete it */
	if (canInitChart)
	  {
	    DeleteChart(a->charts[a->currentChart]);
	    canInitChart=FALSE; /* this indicates that the chart is already deleted */
	  }

	if (searchBorder)
	  {
	    /* dichotomic search for the border */
	    #if (SIMPLE_BORDER)
	      /* Simple boder -> vertices out of the domain are marked as such
	         and no refinement is triggered. */
	      canContinue=FALSE;
	    #else
	      canContinue=((u-l)>MIN_SAMPLING_RADIUS);
	      if (canContinue)
		{
		  if (outOfDomain)
		    u=s;
		  else
		    l=s;
		  s=(u+l)/2.0;
		}
	    #endif
	  }
	else
	  {
	    canContinue=(s>MIN_SAMPLING_RADIUS);
	    if (canContinue)
	      {
		s*=SAMPLING_RADIUS_REDUCTION_FACTOR;
		NewRadiousChange(st);
	      }
	  }
      }
  } while((wrong)&&(canContinue));
  
  if (searchBorder)
    {
      #if (!SIMPLE_BORDER)
        /* Define a linear constraint to the parent chart along the border */
        AddBorderConstraint(pr,ct,a->tp,a->ambient,a->charts[parentID]);
      #endif

      ChartIsFrontier(a->charts[parentID]);
    }
  else
    {
      if (!inside)
	{
	  if (!canContinue)
	    {
	      if (SingularChart(a->charts[parentID]))
		{
		  NewSingularImpossible(st);
		  printf("  Could not extend singular chart\n");
		}
	      else
		{
		  //Error("The impossible happened (I)");
		  NewImpossible(st);
		}
	    }
	  else
	    {
	      #if (ATLAS_VERBOSE) 
  	        printf("  New Chart %u [p:%u]\n",a->currentChart,parentID);
	      #endif
	      a->currentChart++;
	      PostProcessNewCharts(pr,TRUE,parentID,st,a);
	      ok=TRUE; /* We actually generated a new chart */
	    }
	}
    }

  /* If no chart is actually generated, just release the allocated memory */
  if (!ok)
    {
      /* Just in case we cancelled the chart  */
      if (canInitChart)
	DeleteChart(a->charts[a->currentChart]);
      free(a->charts[a->currentChart]);
    }

  free(ct);
  free(pt);

  return(ok);
}

boolean ExtendAtlasTowardPoint(Tparameters *pr,unsigned int parentID,double *t,
			       boolean collisionStops,
			       TAtlasStatistics *st,Tatlas *a)
{
  double delta,s;
  double *tp,*pt,*ptGood;
  Tchart mTmp;
  boolean moved,inCollision,canInitChart,smallError,closeEnough;
  double r,n;
  unsigned int chartCode;
  double currentDelta;
  double epsilon;

  NEW(pt,a->m,double);
  NEW(tp,a->k,double);
  /* ptGood is the last point where we managed to generate a valid chart.
     Inintially, the center of the current chart but we try to move
     far from here. */
  NEW(ptGood,a->m,double);
  memcpy(ptGood,GetChartCenter(a->charts[parentID]),a->m*sizeof(double));

  n=Norm(a->k,t); 
  r=GetChartRadius(a->charts[parentID]);
  epsilon=GetParameter(CT_EPSILON,pr);
  delta=GetParameter(CT_DELTA,pr);
  s=0.0; /* how much we advanced so far */
  currentDelta=delta; /* size of current step */

  inCollision=FALSE;
  canInitChart=TRUE;
  closeEnough=TRUE;
  smallError=TRUE;
  moved=FALSE;
  
  /* When extending a chart it is crucial to be able to generate at least
     one point in the given direction (except if there is an obstacle
     blocking this direction). Once we have at least one point in the
     given direction, we can generate a new chart on it that extends
     the atlas. Therefore we carefully adjust the advance step
     in case we are in a problematic area (singular, large curvature). */
  do {
    NewAtlasExtension(st);
    NewRadiousChange(st);
    /* See if vector t scaled by 's' is collision free and has small error */
    memcpy(tp,t,a->k*sizeof(double));
    ScaleVector((s+currentDelta)/n,a->k,tp);

    smallError=(Chart2Manifold(pr,&(a->J),tp,NULL,ptGood,pt,a->charts[parentID])<=a->e);

    if (smallError)
      {
	chartCode=InitChart(pr,a->simpleChart,a->ambient,a->tp,
			    a->m,a->k,pt,a->e,a->ce,a->r,
			    &(a->J),a->w,&mTmp);
	canInitChart=(chartCode==0);

	if (canInitChart)
	  {
	    closeEnough=(CloseCharts(pr,a->tp,a->charts[parentID],&mTmp));
	    if (closeEnough)
	      {
		if (collisionStops)
		  inCollision=CollisionChart(&mTmp);

		if (!inCollision)
		  {
		    moved=TRUE;
		    /* consolidate the advance */
		    s+=currentDelta;
		    
		    /* If we moved beyond the chart radious-> stop here */
		    if (s>=r)
		      smallError=FALSE;

		    /* Store the just generated valid point (this is how
		       far we managed to get so far). */
		    memcpy(ptGood,pt,sizeof(double)*a->m);

		    NewGoodExtension(st); 

		    if (currentDelta!=delta)
		      {
			/* We managed to generate a problematic
			   initial point -> stop here */
			closeEnough=FALSE;
		      }
		  }
		else
		  NewInCollision(st);
	      }
	    else
	      NewFarFromParent(st);
	    DeleteChart(&mTmp);
	  }
	else
	  {
	    switch (chartCode)
	      {
	      case 1:
	      case 2:
		NewNonRegularPoint(st);
		break;
	      case 3:
		NewDecompositionError(st);
		break;
	      case 4:
		NewNotInManifold(st);
		break;
	      default:
		Error("Unknown chart creation error code");
	      }	
	  }
      }
    else
      NewLargeError(st);

    /* If not moved (i.e., we do not have a good point) 
       for a reason different from a collision, try to
       adjust the avance step */
    if ((!moved)&&(!inCollision))
      {
	/* If we are not trying to jump over a singularity */
	if (currentDelta<=delta)
	  {
	    if (currentDelta>epsilon)
	      {
		/* We are trying to generate the first point in
		   a difficult area (singular or with very high
		   curvature). Try to reduce the advance step with
		   the purpose of finding a point just outside this
		   problematic area. Note that the center of the
		   current chart is outside this area and, thus
		   we try to approach it.
		*/
		currentDelta*=0.5;
		canInitChart=TRUE;
		smallError=TRUE;
		closeEnough=TRUE;
	      }
	    else
	      {
		if (!canInitChart) /* assume charCode==1 */
		  {
		    /* We are in a singular area and  the current
		       chart is just at the border of this singular
		       area (we can not create any other chart closer
		       to the singular area). In this case we try
		       to jump over the singular area with a large
		       jump. Note that this can produce some
		       collisions that are not detected. This large
		       jump is only tried once. If it does not work
		       the extension is declared a failure and a warning
		       is issued.

		       In theory, singularities are zero volum areas but
		       in practice they have some thickness that is given
		       by the used numerical accuracy (epsilon)
		    */
		    currentDelta=5*delta;
		    canInitChart=TRUE;
		    smallError=TRUE;
		    closeEnough=TRUE;
		  }
	      }
	  }
      }
    
  } while((smallError)&&(canInitChart)&&(closeEnough)&&(!inCollision));

  if (!moved)
    {
      /* Could not extend at all */
      if (!inCollision)
	{
	  if ((currentDelta>delta)||(!canInitChart)||(SingularChart(a->charts[parentID])))
	    {
	      NewSingularImpossible(st);
	      printf("  Could not jump over a singularity (decrease epsilon?)");
	    }
	  else
	    {
	      /* !smallError or !closeEnough */
	      NewImpossible(st);
	      Error("  The impossible happened (II)");
	    }
	}
    }
  else
    {	 
      /* Generate the new chart. In the case where extending the atlas in parallel,
         this part has to be executed sequentially. */
      if (a->currentChart==a->maxCharts)
	MEM_DUP(a->charts,a->maxCharts,Tchart *);

      NEW(a->charts[a->currentChart],1,Tchart);
	
      if (InitChart(pr,a->simpleChart,a->ambient,a->tp,
		    a->m,a->k,ptGood,a->e,a->ce,a->r,
		    &(a->J),a->w,a->charts[a->currentChart])!=0)
	Error("Can not create a chart already created just above?");
	
      #if (ATLAS_VERBOSE) 
        printf("  New Chart %u\n",a->currentChart);
      #endif

      a->currentChart++;
      PostProcessNewCharts(pr,TRUE,parentID,st,a);
    }

  free(pt);
  free(ptGood);
  free(tp);
 
  return(moved);
}

void ReconstructAtlasPath(Tparameters *pr,unsigned int *pred,
			  unsigned int mID,double *goal,unsigned int nv,
			  boolean *systemVars,
			  double *pl,unsigned int *ns,double ***path,Tatlas *a)
{
  unsigned int nvs,i,k;
  unsigned int ms;
  unsigned int *chartID;
  signed int s;
  double *t,*o;
  Tchart *cp,*c;

  *pl=0;

  NEW(t,a->k,double);

  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }
  
  InitSamples(&ms,ns,path);

  /* Count the number of charts to be visited along the path */
  i=mID;
  k=0;
  while (i!=NO_UINT) 
    {
      k++;
      i=pred[i];
    }

  /* Store the charts to be visited along the path (in the correct
     order) */
  NEW(chartID,k,unsigned int);
  s=k-1; 
  i=mID;
  while (i!=NO_UINT) 
    {
      chartID[s]=i;
      s--;
      i=pred[i];
    }
  
  /* Reconstruct the path in each chart (from the center of the
     chart to the projection of the center of next chart) */      
  cp=a->charts[chartID[0]];
  for(i=1;i<k;i++)
    {	      
      c=a->charts[chartID[i]];
      Manifold2Chart(GetChartCenter(c),a->tp,t,cp);
      #if (_DEBUG>4)
        printf("    Step to %u  %f\n",chartID[i],Norm(a->k,t));
      #endif
      if (!PathInChart(pr,t,a->tp,&(a->J),nvs,systemVars,&ms,pl,ns,path,cp))
	{
	  if (ATLAS_VERBOSE)
	    Warning("Collision when reconstructing path in atlas");
	}
      cp=c;
    }
  
  /* And now the path on last chart to the goal */
  Manifold2Chart(goal,a->tp,t,cp);
  #if (_DEBUG>4)
    printf("    Last step  %f\n",Norm(a->k,t));
  #endif
  if (!PathInChart(pr,t,a->tp,&(a->J),nvs,systemVars,&ms,pl,ns,path,cp))
    {
      if (ATLAS_VERBOSE)
	Warning("Collision when reconstructing path in atlas");
    }

  /* and add the goal */
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,goal,&o,c->w);
  AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
  free(o);

  free(chartID);
  free(t);
}

boolean DetermineChartNeighbours(Tparameters *pr,boolean bif,
				 unsigned int cmID,unsigned int parentID,
				 Tatlas *a)
{
  unsigned int i;
  unsigned int db;
  boolean singular;

  singular=FALSE;

  db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr);

  if ((a->n==0)||(db==0))
    /* Overide the caller setting if we do not want to detect bifurcations */
    bif=FALSE;

  if (ChartNumNeighbours(a->charts[cmID])>0)
    Error("DetermineChartNeighbours must be used for charts without any neighbour.");
  
  #if (USE_ATLAS_TREE)
    unsigned int nn=0,id;
    unsigned int *n=NULL;
    boolean intersectWithParent;
    
    SearchInBtree(a->charts[cmID],&nn,&n,&(a->tree));
    intersectWithParent=FALSE;

    for(i=0;i<nn;i++)
      {
	id=n[i];
	
	if (id==cmID)
	  Error("The chart was not supposed to be in the tree");

        #if (_DEBUG>3)
	  if (Distance(a->m,GetChartCenter(a->charts[cmID]),GetChartCenter(a->charts[id]))<1e-8)
	    Error("Repeated chart center");
	#endif
	  
	if (IntersectCharts(pr,a->tp,a->ambient,
			    id,a->charts[id],cmID,a->charts[cmID]))
	  {
	    #if (ATLAS_VERBOSE)
	      fprintf(stderr,"  Chart %u intersects with chart %u [parent %u]\n",cmID,id,parentID);
	     #endif
	    if ((bif)&&((db>1)||(parentID==NO_UINT)||(id==parentID)))
	      singular|=(!DetectBifurcation(pr,cmID,id,a)); /* id=parent*/

	    if (id==parentID)
	      intersectWithParent=TRUE;
	  }
      }
    
    if ((parentID!=NO_UINT)&&(!intersectWithParent))
      Error("A chart that does not intersect with its parent (1)");
    
    if (nn>0)
      free(n);

    /* We add the chart to the tree at the end to avoid self-intersection. */
    AddChart2Btree(cmID,a->charts[cmID],&(a->tree));
  #else
    for(i=0;i<a->currentChart;i++)
      {
	if (i!=cmID)
	  {
	    if (IntersectCharts(pr,a->tp,a->ambient,
				i,a->charts[i],cmID,a->charts[cmID]))
	      {

		#if (ATLAS_VERBOSE)
		  fprintf(stderr,"  Chart %u intersects with chart %u\n",cmID,i);
		#endif
		if ((bif)&&((db>1)||(parentID==NO_UINT)||(i==parentID)))
		  singular|=(!DetectBifurcation(pr,cmID,i,a));
	      }
	    else
	      {
		if (i==parentID)
		  Error("A chart that does not intersect with its parent (2)");
	      }
	  }
      }
  #endif

  return(!singular);
}

double GeodesicDistance(Tparameters *pr,unsigned int parentID,unsigned int childID,
			Tatlas *a)
{
  double d;

  if (a->n==0)
    d=DistanceTopology(a->m,a->tp,
		       GetChartCenter(a->charts[parentID]),
		       GetChartCenter(a->charts[childID]));
  else
    {
      double *v,*pt,*ptPrev;
      Tchart *c;
      double *start,*goal;
      double dStep;
      double delta;
      boolean projectionOk,inCollision,reached;
      unsigned int step; 
      #if (PROJECT_WITH_PLANE)
        double *ptp;
      #endif

      NEW(v,a->m,double);
      NEW(pt,a->m,double);
      NEW(ptPrev,a->m,double);
      #if (PROJECT_WITH_PLANE)
        NEW(ptp,a->m,double);
      #endif

      c=a->charts[parentID];
      start=GetChartCenter(c);
      goal=GetChartCenter(a->charts[childID]);

      DifferenceVectorTopology(a->m,a->tp,goal,start,v);

      delta=GetParameter(CT_DELTA,pr);
      d=0.0;
      step=1;
      memcpy(ptPrev,start,a->m*sizeof(double));

      projectionOk=TRUE;
      inCollision=FALSE;
      reached=FALSE;

      while((projectionOk)&&(!inCollision)&&(!reached)&&(d<INF))
	{
	  SumVectorScale(a->m,start,(double)step*delta,v,pt);	
      
	  #if (PROJECT_WITH_PLANE)
	    memcpy(ptp,pt,a->m*sizeof(double));
	    projectionOk=Newton2ManifoldPlane(pr,ptp,v,ptPrev,pt,a);
	  #else
	    projectionOk=(CS_WD_NEWTON_IN_SIMP(pr,pt,a->w)!=DIVERGED);
	  #endif

	  if (projectionOk)
	    {
	      CS_WD_IN_COLLISION(inCollision,pr,pt,ptPrev,a->w);
	  
	      if (!inCollision)
		{
		  dStep=DistanceTopology(a->m,a->tp,ptPrev,pt);
		  if (dStep<(delta/100.0))
		    d=INF; /* The advance is stalled-> declare impossible path */
		  else
		    {
		      d+=dStep;
		      memcpy(ptPrev,pt,a->m*sizeof(double));
		      reached=(DistanceTopology(a->m,a->tp,pt,goal)<delta);
		    }
		}
	      else
		{
		  d=INF;
		  //printf("d[%u,%u]=INF due to collision (%u)\n",parentID,childID,step);
		}
	    }
	  else
	    {
	      /* This should never happen. We print a message to warn */
	      d=INF;
	      //printf("d[%u,%u]=INF due to not convergence (%u)\n",parentID,childID,step);
	    }

	  step++;
	}

      //if (d<INF)
      //  printf("d[%u,%u]=%g\n",parentID,childID,d);

      free(v);
      free(pt);
      free(ptPrev);
      #if (PROJECT_WITH_PLANE)
        free(ptp);
      #endif
    }
  return(d);
}

/******************************************************************/
/******************************************************************/
/******************************************************************/

boolean DetectBifurcation(Tparameters *pr,unsigned int mID1,unsigned int mID2,Tatlas *a)
{
  double *T;
  Tchart *mp1,*mp2;
  unsigned int d1,d2;
  boolean singular,singular1,singular2;
  
  singular=FALSE;
  
  mp1=a->charts[mID1];
  mp2=a->charts[mID2];

  if ((!SingularChart(mp1))&&(!SingularChart(mp2)))
    {
      T=GetChartTangentSpace(mp1);
      d1=GetChartDegree(pr,T,&(a->J),&singular1,mp1);
      d2=GetChartDegree(pr,T,&(a->J),&singular2,mp2);
      
      singular=((singular1)||(singular2));

      #if (_DEBUG>4)
        printf("  *Degree of chart %u -> %u [%u]\n",mID1,d1,singular1);
        printf("  -Degree of chart %u -> %u [%u]\n",mID2,d2,singular2);
      #endif

      /* When very close to a singularity, the chart might be declared
         non singular in creation but be singular in practice when 
         computing it degree. */
      if ((!singular1)&&(!singular2)&&(d1!=d2))
	{
	  if (a->nBifurcations==a->mBifurcations)
	    MEM_DUP(a->bifurcation,a->mBifurcations,Tbifurcation *);
	  
	  NEW(a->bifurcation[a->nBifurcations],1,Tbifurcation);
	  a->bifurcation[a->nBifurcations]->mID1=mID1;
	  a->bifurcation[a->nBifurcations]->d1=d1;
	  a->bifurcation[a->nBifurcations]->mID2=mID2;
	  a->bifurcation[a->nBifurcations]->d2=d2;
	  a->bifurcation[a->nBifurcations]->p=NULL;
	  a->nBifurcations++;
	}
    }
  return(!singular);
}

boolean FindSingularPoint(Tparameters *pr,unsigned int bID,Tatlas *a)
{
  /* Detect the singularity point */
  unsigned int degreeLow,degreeUp,degree;
  double *d,*tg1,*tg2,*p,*T;
  boolean done,error;
  Tchart tmpM,*m1,*m2;
  double epsilon;
  unsigned int nm;
  double t,tLow,tUp;
  double c1,c2;
  boolean singular;
  double *p1,*p2,*tg;

  epsilon=GetParameter(CT_EPSILON,pr);

  degreeLow=a->bifurcation[bID]->d1;
  degreeUp =a->bifurcation[bID]->d2;
      
  if (degreeLow==degreeUp)
    Error("Degrees must be different at FindSingularPoint");

  m1=a->charts[a->bifurcation[bID]->mID1];
  m2=a->charts[a->bifurcation[bID]->mID2];

  NEW(tg1,a->k,double);
  NEW(tg2,a->k,double);

  NEW(p1,a->m,double);
  memcpy(p1,GetChartCenter(m1),a->m*sizeof(double));
  Manifold2Chart(p1,a->tp,tg1,m1); /*tg1 is zero*/
  
  NEW(p2,a->m,double);
  memcpy(p2,GetChartCenter(m2),a->m*sizeof(double));
  Manifold2Chart(p2,a->tp,tg2,m1);

  T=GetChartTangentSpace(m1);

  NEW(d,a->k,double);
  NEW(tg,a->k,double);
  NEW(p,a->m,double);
  memcpy(p,p2,a->m*sizeof(double));
  
  done=FALSE;
  error=FALSE;
  if (CompareTangentSpaces(m1,m2))
    error=FALSE;
  else
    {
      printf("  Incompatible initial charts in FindSingularPoint\n");
      error=TRUE;
    }

  DifferenceVector(a->k,tg2,tg1,d);
  tLow=0.0;
  tUp=1.0;

  while((!done)&&(!error))
    {
      t=tLow+(tUp-tLow)*0.5;
      
      SumVectorScale(a->k,tg1,t,d,tg);

      if (Chart2Manifold(pr,&(a->J),tg,NULL,p,p,m1)>a->e)
	error=TRUE;

      if ((!done)&&(!error))
	{
	  /* Some of the chart generated in the search might be almost singular. We 
	     do not trigger an error if they are singular but we do not force the
	     chart to be singular anyway. Just use the information from the numerical
	     procedure without pre-defining if the point is regular or not. */
	  nm=InitPossiblySingularChart(pr,a->simpleChart,a->ambient,a->tp,
				       a->m,a->k,p,a->e,a->ce,a->r,&(a->J),a->w,&tmpM);

	  if (nm<2) /* 0: no error   1: singular chart */
	    { 
	      if (SingularChart(&tmpM))
		done=TRUE;
	      else
		{
		  c1=MinCosinusBetweenCharts(m1,&tmpM);
		  c2=MinCosinusBetweenCharts(&tmpM,m2);
	      
		  if ((c1<(1-a->ce))||(c2<(1-a->ce)))
		    {
		      /* This is typically the case where, accidentally, we ended up 
			 in the other branch */
		      fprintf(stderr,"  Could not find singular point. Large tangent error %f (%f %f)\n",tUp-tLow,c1,c2);
		      error=TRUE;
		    }
		  else
		    {
		      degree=GetChartDegree(pr,T,&(a->J),&singular,&tmpM);
		  
		      if (singular)
			done=TRUE;
		      else
			{
			  if (degree==degreeLow)
			    {
			      tLow=t;
			      memcpy(p1,p,a->m*sizeof(double));
			    }
			  else
			    {
			      if (degree==degreeUp)
				{
				  tUp=t;
				  memcpy(p2,p,a->m*sizeof(double));
				}
			      else
				Error("Incoherent degree change");
			    }
		      
			  done=((tUp-tLow)<100*epsilon);
			}
		    }
		}
	      DeleteChart(&tmpM);
	    }
	  else
	    Error("Error initializing a new chart in FindSingularPoint");
	}
    }
  if (!error)
    {
      NEW(a->bifurcation[bID]->p,a->m,double);
      memcpy(a->bifurcation[bID]->p,p,a->m*sizeof(double)); 
      
      /* Try to improve the singular point estimation */
      //RefineSingularPoint(pr,bID,a);
    }
     
  free(tg);
  free(p1);
  free(p2);
  free(tg1);
  free(tg2);
  free(p);
  free(d);

  return(!error);
}

boolean RefineSingularPoint(Tparameters *pr,unsigned int bID,Tatlas *a)
{
  double epsilon,nullSingularValue;
  unsigned int maxIterations;
  unsigned int i,j,k;
  double *y,*x,*lambda;
  unsigned int s,c,r;
  Tchart *c1;
  double *p1;
  double *phi;
  unsigned int it;
  boolean converged;
  double dif,d1,d2,d3;
  
  TNewton newton;
  double *J;
  double *bData;
  double *aData;
  double *ptr; /* used to access bData */

  int err;

  double ***h;

  /* This routine requires the Hessian, compute it if no
     already computed */
  if (a->H==NULL)
    {
      NEW(a->H,1,THessian);
      InitHessian(&(a->J),a->H);
    }

  epsilon=GetParameter(CT_EPSILON,pr);
  maxIterations=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,pr);
  nullSingularValue=epsilon/100;

  c1=a->charts[a->bifurcation[bID]->mID1];
  p1=GetChartCenter(c1);
  phi=GetChartTangentSpace(c1); /*This is m x k = ncJ x k*/

  /* As an improvement we could use an interpolation between the
     tangent spaces for c1 and c2  */

  /* Number of variables/columns of the system adjusted via Newton*/
  c=a->ncJ+a->ncJ; /* The original variables plus lambda */
  /* Number of equations/rows of the system adjusted via Newton */
  r=(a->nrJ+a->nrJ+a->k+1); /*F + J*lambda + phi*lambda + 1*/

  /* Space for the current estimation */
  NEW(y,c,double);
  /* Direct pointers to the two components of 'y' */
  x=y;
  lambda=&(y[a->ncJ]);

  /* Set up the initial value for 'y' */

  /* Initialize x to the current estimation of the singular point  */
  if (a->bifurcation[bID]->p!=NULL)
    {
      /* We have an estimation of the singular point and want to
         refine it*/
      memcpy(x,a->bifurcation[bID]->p,sizeof(double)*a->ncJ);
    }
  else
    {
      /* Search the bifurcation from scratch. Depart from the
         center of the first chart */
      memcpy(x,p1,sizeof(double)*a->ncJ);
    }

  /* Space for the Jacobian evaluation */
  NEW(J,a->nrJ*a->ncJ,double); /* ncJ==m */

  #if (0)
    if (a->bifurcation[bID]->p!=NULL)
      {
	/* If we have an inintial estimation of the singular point, initialize lambda
	   with the eigenvector for the smaller non-null eigenvalue. 
	   For this vector J*lambda is close to zero. */

	double *K;
	
	NEW(K,a->ncJ*(a->k+1),double);
	
	/* Re-use vector 'J' to store J^t */
	EvaluateTransposedJacobianInVector(a->bifurcation[bID]->p,a->ncJ,a->nrJ,J,&(a->J));
	
	FindKernel(a->nrJ,a->ncJ,J,a->k+1,FALSE,epsilon,&K);
	
	/* The kernel is returned from largest eigen value to smaller */
	GetColumn(0,a->ncJ,a->k+1,K,lambda);

	free(K);
      }
    else
  #else
      {
	lambda[0]=1;
	for(i=1;i<a->ncJ;i++)
	  lambda[i]=0;
      }
  #endif  
  
  /* Allocate space for the matrices to be used at each Newton step */
  InitNewton(r,c,&newton);
  aData=GetNewtonMatrixBuffer(&newton);
  /* set all entries to zero (many blocks remain zero all along the process) */
  s=r*c;
  for(i=0;i<s;i++)
    aData[i]=0.0;

  bData=GetNewtonRHBuffer(&newton); /* r entries */
  
  AllocateHessianEvaluation(&h,a->H);

  it=0;
  converged=FALSE;
  while((!converged)&&(it<maxIterations))
    {      
      /* Set up the matrix */
      
      /* Get the Jacobian, we will use it in different steps below */
      EvaluateJacobianInVector(x,a->nrJ,a->ncJ,J,&(a->J));

      /* We first set up part of the matrix and then the residual since the
         residual evaluation needs the Jacobian, included in the matrix.*/

      /* The first block of the matrix comes from 
	 rows of the Jacobian (and a block of zeros at the end of each row) */
      SubMatrixFromMatrix(a->nrJ,a->ncJ,J,0,0,r,c,aData);

      /* Set up part of the residual (the one for 'x'). */
      /*F(x)=0*/
      CS_WD_EVALUATE_SIMP_EQUATIONS(pr,x,bData,a->w);

      /* Set up the rest of the residual (the one for 'lambda' that uses
	 J just stored in aData) */
      /* J*lambda=0 */
      ptr=&(bData[a->nrJ]);
      MatrixVectorProduct(a->nrJ,a->ncJ,J,lambda,ptr);

      /* Now force lambda to be different from the vectors in the known
         tangent space (approximatted by the tangent space at the initial
	 point, p1)
         phi' * lambda = 0 */
      TMatrixVectorProduct(a->m,a->k,phi,lambda,&(bData[a->nrJ+a->nrJ]));

      /* last element in the residual is lambda' lambda -1 =0 */
      bData[r-1]=GeneralDotProduct(a->ncJ,lambda,lambda)-1.0;

      d1=Norm(a->nrJ,bData);
      d2=Norm(a->nrJ,&(bData[a->nrJ]));
      d3=Norm(a->k,&(bData[a->nrJ+a->nrJ]));
      //d4=fabs(bData[r-1]);
      //if ((d1<epsilon)&&(d2<epsilon)&&(d3<epsilon)&&(d4<epsilon))
      if ((d1<10*epsilon)&&(d2<10*epsilon)&&(d3<10*epsilon))
	converged=TRUE;
      else
	{
	  /* The Hessian part*/ 
	  EvaluateHessian(x,h,a->H);

	  /* The second block of the matrix comes from the Hessian */
	  for(i=0;i<a->nrJ;i++)
	    {	      
	      for(j=0;j<a->ncJ;j++)
		{
		  aData[RC2INDEX(a->nrJ+i,j,r,c)]=0.0;
		  for(k=0;k<a->ncJ;k++)
		    aData[RC2INDEX(a->nrJ+i,j,r,c)]+=(h[i][k][j]*lambda[k]);
		}
	    }

	  /* now the Jacobian part (take the already computed one) */
	  SubMatrixFromMatrix(a->nrJ,a->ncJ,J,a->nrJ,a->ncJ,r,c,aData);

	  /* The known tangent space part (transposed tangent) */
	  SubMatrixFromTMatrix(a->m,a->k,phi,a->nrJ+a->nrJ,a->ncJ,r,c,aData);

	  /* The last row of the matrix only inclues a block of zeros and 2*lambda*/
	  for(i=0;i<a->ncJ;i++)
	    aData[RC2INDEX(r-1,a->ncJ+i,r,c)]=(2.0*lambda[i]);

	  /* Improve the solution */
	  err=NewtonStep(nullSingularValue,y,&dif,&newton);

	  if (err)
	    it=maxIterations;
	  else
	    it++;
	}
    }

  if (converged)
    {
      if (a->tp!=NULL)
	ArrayPi2Pi(a->m,a->tp,x);

      /* If we do not have an estimation for the singular point we
         initialize it, oherwise we improve the estimation. */
      if (a->bifurcation[bID]->p==NULL)
	NEW(a->bifurcation[bID]->p,a->m,double);

      /* Singular point found. Update the information about the bifurcation  */
      memcpy(a->bifurcation[bID]->p,x,a->m*sizeof(double));
    }

  /* release used memory */
  DeleteNewton(&newton);
  FreeHessianEvaluation(h,a->H);
  free(J);
  free(y);

  return(it<maxIterations);
}

unsigned int FindRightNullVector(Tparameters *pr,unsigned int bID,
				 double **phi,Tatlas *a)
{
  double *JTData;
  double *K=NULL;
  double s,sMin,*p;
  unsigned int it,itMin,ck;
  unsigned int out;
  double *T;
  double eps;

  //eps=sqrt(GetParameter(CT_EPSILON,pr)); /* typically 1e-3 */
  /* We use a large threshold just to avoid errors. This basically gets
     the k+1 vectors with smaller eigenvalues, irrespectively of the
     value of these eigenvalues. */
  eps=0.01;
  
  /* Number of columns of the matrix K defined below */
  ck=a->k+1;

  /*Use the tangent space at mp1 as an approximation of the tangent space at the
    bifurcation*/
  T=GetChartTangentSpace(a->charts[a->bifurcation[bID]->mID1]);

  if (a->bifurcation[bID]->p==NULL)
    Error("FindRightNullVector needs a singular point");

  /* The (almost) singular point */
  p=a->bifurcation[bID]->p;
 
  /* Space for the Jacobian */
  NEW(JTData,a->ncJ*a->nrJ,double);
  EvaluateTransposedJacobianInVector(p,a->ncJ,a->nrJ,JTData,&(a->J));
  #if (_DEBUG>3)
    PrintTMatrix(stdout,"J",a->ncJ,a->nrJ,JTData);
  #endif

  /* Now we retrive the k+1 vectors defining the kernel at the singularity.
     This is the same to that of \ref InitChart where we compute the
     kernel at a non-singular point. The difference is that here we
     have k+1 vector (instead of k) and that we have to be more generous with the
     criteria to consider eigen value as zero (the input point might not
     be exactly singular). In the extreme we can set the 'check' parameter
     to FALSE and then we just get the k+1 vectors for the smaller eigenvalues,
     irrespectively of their actual value. */
  out=FindKernel(a->nrJ,a->ncJ,JTData,ck,TRUE,eps,&K);

  #if (_DEBUG>3)
    PrintTMatrix(stdout,"T",a->m,a->k,T);
    PrintTMatrix(stdout,"K",a->m,ck,K);
  #endif
	
  /* Look for the vector more different from those in T.
     Note that we just get the vector that is more different
     for those in T, without any minimal dissimilarity.
     We could define a threshold and return only a valid
     vector it is different 'enough' from those in T */
  					
  /* Space for the output vector (not used if out!=0) */

  if (out==0)
    {
      double *Proj;

      NEW((*phi),a->m,double);
      NEW(Proj,a->k*ck,double);

      TMatrixMatrixProduct(a->m,a->k,T,ck,K,Proj);

      #if (_DEBUG>3)
        PrintMatrix(stdout,"Proj",a->k,ck,Proj);
      #endif

      #if (_DEBUG>3)
        printf("  Proj(T):[ ");
      #endif

      /* Compute the norm of the columns of Proj */
      sMin=INF;
      itMin=0; /* dummy value */
      for(it=0;it<=a->k;it++)
	{ 
	  s=ColumnSquaredNorm(it,a->k,ck,Proj);
	  #if (_DEBUG>3)
	    printf("%g ",s);
	  #endif
	  if (s<sMin)
	    {
	      sMin=s;
	      itMin=it;
	    }
	} 
      #if (_DEBUG>3)
        printf("]\n");
      #endif
      free(Proj);

      /* Get the column of K corresponding to the smaller
         projection on T */
      GetColumn(itMin,a->m,ck,K,(*phi));
    }
  else
    *phi=NULL;

  /* Release allocated space */
  if (K!=NULL)
    free(K);

  free(JTData);

  return(out);
}

boolean Newton2ManifoldPlane(Tparameters *pr,double *point,double *vector,
			     double *pInit,double *p,Tatlas *a)
{
  if (a->n==0)
    {
      memcpy(p,point,sizeof(double)*a->m);
      return(TRUE);
    }
  else
    {
      double epsilon,nullSingularValue;
      unsigned int j,it,maxIterations;
      boolean converged;

      TNewton newton;
      double *bData;
      double *aData;
      double *ptr;

      double errorVal;
      int err;

      epsilon=GetParameter(CT_EPSILON,pr);
      maxIterations=(unsigned int)GetParameter(CT_MAX_NEWTON_ITERATIONS,pr);
      nullSingularValue=epsilon/100;

      if (maxIterations==0)
	Error("MAX_NEWTON_ITERATIONS must be larger than 0 to use Newton2ManifoldPlane");

      InitNewton(a->nrJ+1,a->ncJ,&newton);
      aData=GetNewtonMatrixBuffer(&newton);
      bData=GetNewtonRHBuffer(&newton);

      if (pInit==NULL)
	memcpy(p,point,sizeof(double)*a->m);
      else
	memcpy(p,pInit,sizeof(double)*a->m);
  
      /* Iterate from this point to a point on the manifold */
      it=0;
      converged=FALSE;
      while((!converged)&&(it<maxIterations))
	{
	  /* Define the residual (right-had side of the system) */
	  CS_WD_EVALUATE_SIMP_EQUATIONS(pr,p,bData,a->w);
    
	  /* Complete the residual with the equation defining the
	     plane that might intersect with the other branch */
	  ptr=&(bData[a->nrJ]);
	  *ptr=0;
	  for(j=0;j<a->ncJ;j++) /* ncJ=m */
	    (*ptr)+=(vector[j]*(p[j]-point[j]));

	  errorVal=Norm(a->nrJ+1,bData);
      
	  if (errorVal<epsilon)
	    converged=TRUE;
	  else
	    {
	      /* Fill in the part of the 'A' corresponding to the Jacobian */
	      EvaluateJacobianInVector(p,a->nrJ+1,a->ncJ,aData,&(a->J));

	      /* Now the part of the 'A' matrix corresponding to the plane
		 that might intersect with the manifold. */
	      SetRow(vector,a->nrJ,a->nrJ+1,a->ncJ,aData); /*ncJ==m*/

	      /* Define the residual (right-had side of the system) */
	      CS_WD_EVALUATE_SIMP_EQUATIONS(pr,p,bData,a->w);
    
	      /* Complete the residual with the equation defining the
		 plane that might intersect with the other branch */
	      ptr=&(bData[a->nrJ]);
	      *ptr=0;
	      for(j=0;j<a->ncJ;j++) /* ncJ=m */
		(*ptr)+=(vector[j]*(p[j]-point[j]));
      
	      err=NewtonStep(nullSingularValue,p,&errorVal,&newton);

	      if (err)
		it=maxIterations;
	      else
		{
		  if(errorVal<epsilon) 
		    converged=TRUE;
		  it++;
		}
	    }
	}

      if ((converged)&&(a->tp!=NULL))
	ArrayPi2Pi(a->m,a->tp,p);

      /* release used memory */
      DeleteNewton(&newton);

      return(it<maxIterations);
    }
}

boolean FindPointInOtherBranch(Tparameters *pr,unsigned int bID,
			       double *phi,double **p,Tatlas *a)
{
  double d;
  double *p0;
  boolean converged;

  if (a->bifurcation[bID]->p==NULL)
    Error("FindPointInOtherBranch needs a singular point");

  /* Displace a bit along phi to get a point outside the manifold */
  /* To increase robustness, we may iterate decresing 0.01 until
     the jump is succesful */
  NEW(p0,a->m,double);
  SumVectorScale(a->m,a->bifurcation[bID]->p,0.01*a->r,phi,p0);

  /* Search for the intersection of a plane defined by
     the new vector of the kernel at the bifurcation found using
     \ref FindRightNullVector passing by a point just out
     of the variety. This point is also determined using
     the new vector of the kernel. */

  NEW((*p),a->m,double);
  converged=Newton2ManifoldPlane(pr,p0,phi,NULL,*p,a);

  if (converged)
    {
      d=DistanceTopology(a->m,a->tp,a->bifurcation[bID]->p,*p);
      if (d>a->r)
	{
	  converged=FALSE;
	  printf("  Converged too far from singularity\n");
	}
    }
  else
    {
      printf("  Could not jump to the other branch\n");
      free(*p);
    }
    
  free(p0);
  
  return(converged);
}

void DefineChartsAtBifurcation(Tparameters *pr,unsigned int bID,
			       double *v,TAtlasStatistics *ast,Tatlas *a)
{
  double c;

  if (a->bifurcation[bID]->p==NULL)
    Error("DefineChartsAtBifurcation needs a singular point");

  /* 3.1.- We define a new chart on the singularity */
  if (a->currentChart==a->maxCharts)
    MEM_DUP(a->charts,a->maxCharts,Tchart *);

  NEW(a->charts[a->currentChart],1,Tchart);
		  
  if (InitChartWithTangent(pr,FALSE,a->ambient,a->tp,a->m,a->k,
			   a->bifurcation[bID]->p,
			   GetChartTangentSpace(a->charts[a->bifurcation[bID]->mID1]),
			   a->e,a->ce,a->r,
			   &(a->J),a->w,a->charts[a->currentChart])>1)
    Warning("Can not create a chart on the singular point");
  else
    {
      a->currentChart++;
      PostProcessNewCharts(pr,FALSE,NO_UINT,ast,a);
		    
      /* 3.2.- Define a new chart in the other branch */
      if (a->currentChart==a->maxCharts)
	MEM_DUP(a->charts,a->maxCharts,Tchart *);
		    
      NEW(a->charts[a->currentChart],1,Tchart);
		  
      if (InitSingularChart(pr,FALSE,a->ambient,a->tp,a->m,a->k,v,a->e,a->ce,a->r,
			    &(a->J),a->w,a->charts[a->currentChart])>1)
	  Warning("Can not create a chart on the other branch");
      else
	{	  
	  c=MinCosinusBetweenCharts(a->charts[a->currentChart-1],a->charts[a->currentChart]);
	  if (c>(1-a->ce))
	    NewSmallAngleAtBifurcation(ast);

	  printf("  New Bifurcation Chart %u (%f)\n",a->currentChart,c);

	  a->currentChart++;	
	  PostProcessNewCharts(pr,FALSE,NO_UINT,ast,a);

	  /* 3.3.- Link the two charts together */
	  LinkCharts(a->currentChart-2,a->charts[a->currentChart-2],
		     a->currentChart-1,a->charts[a->currentChart-1]);
	}
    }
}

void ProcessBifurcation(Tparameters *pr,unsigned int bID,TAtlasStatistics *ast,Tatlas *a)
{
  if ((bID>=a->npBifurcations)&&(bID<a->nBifurcations))
    { 
      NewBifurcation(ast);
      /* 
	 Now we have to detect a point in the "other" branch of the manifold,
	 start a chart there (IntChart) and search for neighbours 
	 (DetectChartNeighbours).
      */
      double *phi,*v;

      printf(" Searching for bifurcation\n");

      /* 1.- Determine the bifurcation point. This is an approximation since 
	     all our processes are epsilon accurate. The result is that the 
	     singular point is actually close to singular but not singular */

      if (FindSingularPoint(pr,bID,a))
	{
	  /* 2.- Find the right null vector (the vector for the smallest 
	         eigenvalue (it sould be zero but is not due to numerical 
		 problems) */
	  if (FindRightNullVector(pr,bID,&phi,a)==0)
	    {
	      /* 3.- Find a point in the other branch */
	      if (FindPointInOtherBranch(pr,bID,phi,&v,a))
		{
		  /* Define on chart at the current branch of the singularity,
		     another at the new branch and link them.*/
		  DefineChartsAtBifurcation(pr,bID,v,ast,a);

		  /* Release intermediate variables */
		  free(v);
		}
	      else
		NewNoJumpBranch(ast);

	      /*Release other intermediate variables*/
	      free(phi);
	    }
	  else
	    NewNoSingularEnough(ast);
	}
      else
	NewSingularPointMissed(ast);
    }
}

void LoadBifurcations(FILE *f,Tatlas *a)
{
  unsigned int i,j,p;

  fscanf(f,"%u",&(a->mBifurcations));
  fscanf(f,"%u",&(a->nBifurcations));
  fscanf(f,"%u",&(a->npBifurcations));

  NEW(a->bifurcation,a->mBifurcations,Tbifurcation*);
  
  
  for(i=0;i<a->nBifurcations;i++)
    {
      NEW(a->bifurcation[i],1,Tbifurcation);
      fscanf(f,"%u",&(a->bifurcation[i]->mID1));
      fscanf(f,"%u",&(a->bifurcation[i]->d1));
      fscanf(f,"%u",&(a->bifurcation[i]->mID2));
      fscanf(f,"%u",&(a->bifurcation[i]->d2));
      fscanf(f,"%u",&p);
      if (p!=0)
	{
	  NEW(a->bifurcation[i]->p,a->m,double);
	  for(j=0;j<a->m;j++)
	    fscanf(f,"%lf",&(a->bifurcation[i]->p[j]));
	}
      else
	a->bifurcation[i]->p=NULL;
    }
}

void SaveBifurcations(FILE *f,Tatlas *a)
{
  unsigned int i,j;

  fprintf(f,"%u\n",a->mBifurcations);
  fprintf(f,"%u\n",a->nBifurcations);
  fprintf(f,"%u\n",a->npBifurcations);

  for(i=0;i<a->nBifurcations;i++)
    {
      fprintf(f,"%u %u %u %u %u\n",
	      a->bifurcation[i]->mID1,a->bifurcation[i]->d1,
	      a->bifurcation[i]->mID2,a->bifurcation[i]->d2,
	      (a->bifurcation[i]->p!=NULL));
      if (a->bifurcation[i]->p!=NULL)
	{
	  for(j=0;j<a->m;j++)
	    fprintf(f,"%.12f ",a->bifurcation[i]->p[j]);
	  fprintf(f,"\n");
	}
    }
}

void PlotBifurcations(Tparameters *pr,Tplot3d *p3d,
		      unsigned int xID,unsigned int yID,unsigned int zID,Tatlas *a)
{
  unsigned int i;
  double *p;
  double x[2],y[2],z[2];
  double *o;
  Tchart *m;
  Tcolor color;

  NewColor(1,0,0,&color); /* red */
  StartNew3dObject(&color,p3d);

  for(i=0;i<a->nBifurcations;i++)
    {
      m=a->charts[a->bifurcation[i]->mID1];
      p=GetChartCenter(m);
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,p,&o,a->w);
      x[0]=o[xID];
      y[0]=o[yID];
      z[0]=o[zID];
      free(o);  

      m=a->charts[a->bifurcation[i]->mID2];
      p=GetChartCenter(m);  
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,p,&o,a->w);
      x[1]=o[xID];
      y[1]=o[yID];
      z[1]=o[zID];
      free(o);  

      PlotVect3d(2,x,y,z,p3d);
    }
    Close3dObject(p3d);
    DeleteColor(&color);
}

void DeleteBifurcations(Tatlas *a)
{
  unsigned int i;

  for(i=0;i<a->nBifurcations;i++)
    {
      if (a->bifurcation[i]->p!=NULL)
	free(a->bifurcation[i]->p);
      free(a->bifurcation[i]);
    }
  free(a->bifurcation);
  
  a->mBifurcations=0;
  a->nBifurcations=0;
  a->npBifurcations=0;
}

void InitAtlasHeapElement(unsigned int mID,double c,double beta,TAtlasHeapElement *he)
{
  he->chartID=mID;
  he->cost=c;
  if (beta<1)
    Error("The heap element penalty factor must be >1");
  he->beta=beta;
  he->nPenalized=1;
}

void CopyAtlasHeapElement(void *he1,void *he2)
{
  ((TAtlasHeapElement *)he1)->chartID=((TAtlasHeapElement *)he2)->chartID;
  ((TAtlasHeapElement *)he1)->cost=((TAtlasHeapElement *)he2)->cost;
  ((TAtlasHeapElement *)he1)->beta=((TAtlasHeapElement *)he2)->beta;
  ((TAtlasHeapElement *)he1)->nPenalized=((TAtlasHeapElement *)he2)->nPenalized;
}

unsigned int GetAtlasHeapElementID(TAtlasHeapElement *he)
{
  return(he->chartID);
}

double GetAtlasHeapElementCost(TAtlasHeapElement *he)
{
  return(he->cost);
}

boolean LessThanAtlasHeapElement(void *he1,void *he2,void *userData)
{
  double t,b1,b2,c1,c2;

  t=((TAtlasHeapElement *)he1)->nPenalized;
  b1=((TAtlasHeapElement *)he1)->beta;
  c1=pow(b1,t-1)*((TAtlasHeapElement *)he1)->cost;

  t=((TAtlasHeapElement *)he2)->nPenalized;
  b2=((TAtlasHeapElement *)he2)->beta;
  c2=pow(b2,t-1)*((TAtlasHeapElement *)he2)->cost;

  return(c1<=c2);
}

void PenalizeAtlasHeapElement(TAtlasHeapElement *he)
{
  he->nPenalized++;
}

void DeleteAtlasHeapElement(void *he)
{
}

void SetAtlasTopology(Tparameters *pr,Tatlas *a)
{
  boolean hasS;
  unsigned int i;
  
  if (CS_WD_GET_SIMP_TOPOLOGY(pr,&(a->tp),a->w)!=a->m)
    Error("Missmatch number of variables in SetAtlasTopology");

  /* Search for a non-real variable */
  hasS=FALSE;
  i=0;
  while((i<a->m)&&(!hasS))
    {
      hasS=(a->tp[i]==TOPOLOGY_S);
      i++;
    }
  if (!hasS)
    {
      /* if all variables are real no need to consider topology */
      free(a->tp);
      a->tp=NULL;
    }
}

void InitAtlas(Tparameters *pr,boolean parallel,boolean simpleChart,
	       unsigned int k,double e,double ce, double r,TAtlasBase *w,
	       Tatlas *a)
{  
  a->w=w;

  a->maxCharts=INIT_NUM_CHARTS;
  a->currentChart=0;
  a->npCharts=0;

  NEW(a->charts,a->maxCharts,Tchart *);

  NEW(a->ambient,1,Tbox);

  /* Since atlas are defined on the simplified system we get the
     corresponding Jacobian. */
  CS_WD_GET_SIMP_JACOBIAN(pr,&(a->J),a->w);
  GetJacobianSize(&(a->nrJ),&(a->ncJ),&(a->J));
  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,a->ambient,a->w);

  /* differ the Hessian computation */
  a->H=NULL;

  a->k=k;
  a->m=a->ncJ;
  a->n=a->m-a->k;
  a->r=r;
  a->e=e;
  a->ce=ce;

  a->mBifurcations=INIT_NUM_BIFURCATIONS;
  a->nBifurcations=0;
  a->npBifurcations=0;
  NEW(a->bifurcation,a->mBifurcations,Tbifurcation *);

  a->simpleChart=simpleChart;

  SetAtlasTopology(pr,a);
  
  /* The openMP parallel execution is only possible if OpenMP is active and
     it is only worth if the problem is large (in number of variables or
     dimension of the solution set). Moreover, collision detection 
     is typically not re-entrant. Do not use parallel execution in 
     this case (if operating on a world instead than on a cuik file). */

  a->parallel=FALSE; /* The default is not to execute in parallel */

  #ifdef _OPENMP
  if (parallel)
    {
      a->nCores=omp_get_max_threads();
      /* even if having many cores and OpenMP we only execute in parallel
         large problems. */
      a->parallel=((a->nCores>1)&&((a->m>10)||(a->k>2)));
    }
  #endif
  //a->parallel=FALSE; 
  if (!a->parallel)
    a->nCores=1;

  fprintf(stderr,"Number of computing cores (atlas) : %u\n",a->nCores);
  
  /* When using world, collisions are considered (if defined) */
  CS_WD_INIT_CD(pr,a->nCores,a->w);
}

boolean InitAtlasFromPoint(Tparameters *pr,boolean parallel,boolean simpleChart,double *p,
			   TAtlasBase *w,Tatlas *a)
{
  unsigned int chartCode;
  boolean initOK;
  double *ps,*pWithDummies;
  unsigned int k;
  double e,ce,r;

  k=(unsigned int)GetParameter(CT_N_DOF,pr);
  r=GetParameter(CT_R,pr);
  e=GetParameter(CT_E,pr);
  ce=GetParameter(CT_CE,pr);

  InitAtlas(pr,parallel,simpleChart,k,e,ce,r,w,a);

  /* We have to recover the full solution point from the values of the system
     variables in sample 'p' and then define the a point in the simplified system
     that is where the atlas is defined. 
     Note that the actual dimension of the ambient space is that of the number
     of variables in the simplified system. Moreover, note that both the simplified
     and the original system describe the same manifold (k is the same is the to of
     them)
  */
  CS_WD_REGENERATE_SOLUTION_POINT(pr,p,&pWithDummies,a->w);

  if (CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,a->w))
    Error("Starting point for the atlas is in collision");
  
  a->m=CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&ps,a->w);
  free(pWithDummies);

  if (a->k==0)
    {	
      /* We have to determine the dof assuming that the given point is regular */
      Warning("N_DOF parameter set to 0. Assuming that the initial point is regular");

      a->k=CS_WD_MANIFOLD_DIMENSION(pr,p,a->w);

      if (a->k==0)
	Error("System with mobility 0");
      
      fprintf(stderr,"Setting N_DOF=%u\n\n",a->k);

      /* Change the parameter !! */
      ChangeParameter(CT_N_DOF,(double)a->k,pr);
    }

  NEW(a->charts[0],1,Tchart);
  chartCode=InitChart(pr,a->simpleChart,a->ambient,a->tp,a->m,a->k,ps,a->e,a->ce,a->r,
		      &(a->J),a->w,a->charts[0]);
  
  switch (chartCode)
    {
    case 1:
      Error("The expected mobility is too low (increase N_DOF)");
      break;
    case 2:
      Error("The expected mobility is too high (decrease N_DOF)");
      break;
    case 3:
      Error("There is a numerical error when computing the tangent space");
      break;
    case 4:
      Error("The initial point is not on the manifold");
      break;
    }

  initOK=(chartCode==0);
  
  free(ps);
  
  if (initOK) 
    {
      if (FrontierChart(a->charts[0]))
	Error("The initial chart is out of the ambient space domain");

      a->currentChart=1;
      a->npCharts=1; /* No need to post-process the first chart. */
      #if (USE_ATLAS_TREE)
        InitBTree(0,a->charts[0],a->ambient,a->tp,&(a->tree));
      #endif
    }
  else
    free(a->charts[0]);  

  return(initOK);
}

unsigned int AddChart2Atlas(Tparameters *pr,double *ps,unsigned int parentID,boolean *singular,Tatlas *a)
{
  boolean initOK;
  unsigned int mID;

  *singular=FALSE;

  /* Generate the new chart */
  if (a->currentChart==a->maxCharts)
    MEM_DUP(a->charts,a->maxCharts,Tchart *);
  
  NEW(a->charts[a->currentChart],1,Tchart);

  initOK=(InitChart(pr,a->simpleChart,a->ambient,a->tp,a->m,a->k,ps,a->e,a->ce,a->r,
		    &(a->J),a->w,a->charts[a->currentChart])==0);
  if (initOK)
    {
      #if (ATLAS_VERBOSE) 
        printf("  New Chart %u [parent: %u]\n",a->currentChart,parentID);
      #endif
     
      fprintf(stderr,"nn: %u\n",ChartNumNeighbours(a->charts[parentID]));
      
      mID=a->currentChart;
      a->currentChart++;
      PostProcessNewCharts(pr,TRUE,parentID,NULL,a);

      fprintf(stderr,"nn: %u\n",ChartNumNeighbours(a->charts[parentID]));
    }
  else
    {
      mID=NO_UINT;
      free(a->charts[a->currentChart]);
    }

  return(mID);
}

unsigned int AddTrustedChart2Atlas(Tparameters *pr,double *ps,unsigned int parentID,boolean *singular,Tatlas *a)
{
  boolean initOK;
  unsigned int mID;
  unsigned int db;

  *singular=FALSE;

  /* Generate the new chart */
  if (a->currentChart==a->maxCharts)
    MEM_DUP(a->charts,a->maxCharts,Tchart *);

  NEW(a->charts[a->currentChart],1,Tchart);

  initOK=(InitTrustedChart(pr,a->simpleChart,a->ambient,a->tp,a->m,a->k,ps,a->e,a->ce,a->r,
			   &(a->J),a->w,a->charts[a->currentChart])==0);
  
  if (initOK)
    {
      #if (ATLAS_VERBOSE) 
        printf("  New Chart %u (%p)\n",a->currentChart,a->charts[a->currentChart]);
      #endif

      mID=a->currentChart;
      a->currentChart++;

      if (a->n>0)
	{
	  /* and now detect (and process) bifurcation from parent to child, even
	     if they are not neighbours yet. */
	  db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr);
	  
	  if ((db>0)&&(parentID!=NO_UINT))
	    *singular=DetectBifurcation(pr,parentID,mID,a);
	}
      /* detect neighbours and deal with the bifurcations if any */
      /* Intersect with the rest of charts (but without concern about singularities
	 and without enforcing intersection with parent). */
      PostProcessNewCharts(pr,FALSE,NO_UINT,NULL,a);
    }
  else
    {
      mID=NO_UINT;
      free(a->charts[a->currentChart]);
    }

  return(mID);
}

void BuildAtlasFromPoint(Tparameters *pr,double *p,boolean simpleChart,
			 TAtlasBase *w,Tatlas *a)
{ 
  Theap h;
  TAtlasHeapElement he,he2;
  unsigned int mID;
  double *t;
  TAtlasStatistics *st;
  unsigned int cm,cmPrev;
  double d;
  unsigned int nv,k;
  double beta;
  unsigned int maxCharts;
  /* just in case parallel=TRUE */
  unsigned int i,*cornerID,*chartID,maxInProcess,ncInProcess;
  double **tv;
  Tchart **newCharts;
  TAtlasHeapElement *heInProcess;

  /* Init the atlas trying to exploit parallelism, if available and worth */
  if (!InitAtlasFromPoint(pr,TRUE,simpleChart,p,w,a))
    Error("Can not start atlas from the given point (BuildAtlasFromPoint)");

  k=(unsigned int)GetParameter(CT_N_DOF,pr);

  maxCharts=(unsigned int)GetParameter(CT_MAX_CHARTS,pr);

  InitHeap(sizeof(TAtlasHeapElement),
	   CopyAtlasHeapElement,
	   DeleteAtlasHeapElement,
	   LessThanAtlasHeapElement,
	   NULL,FALSE,INIT_NUM_CHARTS_IN_ATLAS_HEAP,&h);

  beta=GetParameter(CT_ATLASGBF_BETA,pr);
  /* one-dim solution sets (k==1) -> process charts in sequence */
  InitAtlasHeapElement(0,(k==1?1:0),beta,&he);
  AddElement2Heap(NO_UINT,(void *)(&he),&h);

  if (a->parallel)
    {
      fprintf(stderr,"Executing in %u parallel threads\n",a->nCores);
      /* some charts are difficult to process it's better to have more
         charts in queue... let the other threads to process the simple
         ones */
      maxInProcess=(unsigned int)(1.5*a->nCores);
      NEW(chartID,maxInProcess,unsigned int);
      NEW(cornerID,maxInProcess,unsigned int);
      NEW(tv,maxInProcess,double *);
      for(i=0;i<maxInProcess;i++)
	NEWZ(tv[i],a->k,double);  /* if kino equations some elements of t not used (keep to 0) */
      NEW(heInProcess,maxInProcess,TAtlasHeapElement);
      NEW(newCharts,maxInProcess,Tchart*);
      st=NULL;
    }
  else
    {
      NEWZ(t,a->k,double); /* if kino equations some elements of t not used (keep to 0) */
      NEW(st,1,TAtlasStatistics);
      InitAtlasStatistics(st);
    }

  while((!HeapEmpty(&h))&&(a->currentChart<maxCharts))
    {
      cmPrev=a->currentChart;

      if (!a->parallel)
	{
	  ExtractMinElement((void *)(&he),&h);
	  mID=GetAtlasHeapElementID(&he);

	  //if (ExpandibleChart(a->charts[mID]))
	  if (OpenChart(a->charts[mID]))
	    {
	      printf("Extending chart %u\n",mID);

	      NewBoundaryAttempt(st);

	      /* Treat one external corner at a time */
	      if (BoundaryPointFromExternalCorner(RANDOMNESS,&nv,t,a->charts[mID]))
		{
		  /* This generates a new chart on the direction of 't', if possible. */
		  ExtendAtlasFromPoint(pr,mID,t,st,a);

		  /* Just in case the selected vertex is not actually used, we eliminate it
		     from the list of expandible vetexes. In general this has no effect since
		     the extension already eliminated the vertex (and created new vertexes) */
		  WrongCorner(nv,a->charts[mID]);
		}
	      else
		NewNotInBoundary(st);

	      /* Just in case the chart still has external corners (still open) */
	      AddElement2Heap(NO_UINT,(void *)(&he),&h);
	    }
	}
      else
	{
	  /* Select several open charts, and a corner of each chart */
	  ncInProcess=0;
	  while((!HeapEmpty(&h))&&(ncInProcess<maxInProcess))
	    {
	      ExtractMinElement((void *)(&(heInProcess[ncInProcess])),&h);
	      chartID[ncInProcess]=GetAtlasHeapElementID(&(heInProcess[ncInProcess]));
	      if (OpenChart(a->charts[chartID[ncInProcess]]))
		ncInProcess++;	 
	    }

          #pragma omp parallel for private(i) schedule(dynamic)
	  for(i=0;i<ncInProcess;i++)
	    {
	      if (BoundaryPointFromExternalCorner(RANDOMNESS,&(cornerID[i]),
						  tv[i],a->charts[chartID[i]]))
		{
		  #ifdef _OPENMP 
		    printf("Extending chart %u (%u)\n",chartID[i],omp_get_thread_num());
		  #else
		    printf("Extending chart %u\n",chartID[i]);
		  #endif
		  newCharts[i]=NULL;
		  NewChartFromPoint(pr,chartID[i],tv[i],&(newCharts[i]),a); 
		}
	      /* We selected ncInProcess *different* charts, we can do the
	         'WrongCorner' in parallel too */
	      WrongCorner(cornerID[i],a->charts[chartID[i]]);
	    }

	  /* The post process of the generated charts is serialized */
	  /* Add the charts to the atlas one at a time. */
	  for(i=0;i<ncInProcess;i++)
	    {
	      if (newCharts[i]!=NULL)
		{ 
		  if (HaveChartAtPoint(1e-6,GetChartCenter(newCharts[i]),a))
		    {
		      /* We generated a redundant chart -> remove it 
		         (the nasty side-effect of executing in parallel and
			  selecting nearby charts for expansion).
		          1e-6 is hard-coded in the kd-tree */
		      DeleteChart(newCharts[i]);
		      newCharts[i]=NULL;
		    }
		  else
		    {
		      if (a->currentChart==a->maxCharts)
			MEM_DUP(a->charts,a->maxCharts,Tchart *);
		    
		      /* We directly re-use the charts to safe one copy. */
		      a->charts[a->currentChart]=newCharts[i];
		      a->currentChart++;

		      /* Now detect neighbours and the possible bifurcations */
		      PostProcessNewCharts(pr,TRUE,chartID[i],st,a);
		    }
		}
	    }	 

	  /* Add the charts just processed to the heap, just in case they are still open */
	  for(i=0;i<ncInProcess;i++)
	    AddElement2Heap(NO_UINT,(void *)(&(heInProcess[i])),&h);
	}

      /* The above can generate several charts (when not using OpenMP or due to bifurcations) */
      /* Now we add them to the heap */
      for(cm=cmPrev;cm<a->currentChart;cm++)
	{
	  /* Now add the new chart to the heap */
	  if (k==1) /* one-dim solution sets -> process charts in sequence */
	    d=1/(double)(cm+1);
	  else
	    {
	      /* when executing in parallel we assign the expansion priority at random
	         to minimize the prob. of expanding close charts in parallel. This produces
	         more charts than those really necessary. */
	      if (a->parallel)
		d=randomDouble();
	      else
		d=DistanceTopology(a->m,a->tp,p,GetChartCenter(a->charts[cm]));
	    }
	  InitAtlasHeapElement(cm,d,beta,&he2);
	  AddElement2Heap(NO_UINT,(void *)(&he2),&h);
	}
    }
	
  if (a->parallel)
    {
      free(chartID);
      free(cornerID);
      for(i=0;i<a->nCores;i++)
	free(tv[i]);
      free(tv);
      free(newCharts);
      free(heInProcess);
    }
  else
    {
      PrintAtlasStatistics(pr,st);
      free(st);
      free(t);
    }

  DeleteHeap(&h);
}

boolean MinimizeOnAtlas(Tparameters *pr,char *fname,double *p,TAtlasBase *w,
			unsigned int maxSteps,
			double (*costF)(Tparameters*,boolean,double*,void*),
			void (*costG)(Tparameters*,boolean,double*,double**,void*),
			void *costData,
			Tatlas *a)
{
  unsigned int i,j,k,l,nv,nvs,nt,mt,pnc;
  TMinTrace **t;
  boolean *systemVars,done;
  double *o,*currentPoint;
  double cost,cost1;
  double *g,*newPoint,*d,ng,*gFull;
  double delta,epsilon,e;
  Tchart *currentChart;
  unsigned int db;
  boolean sing,ok;
  boolean retraction;
  double stepSize;

  db=(unsigned int)GetParameter(CT_DETECT_BIFURCATIONS,pr);

  if (db>1)
    ChangeParameter(CT_DETECT_BIFURCATIONS,1,pr);
    
  delta=GetParameter(CT_DELTA,pr); 
  epsilon=GetParameter(CT_EPSILON,pr); 
  e=GetParameter(CT_E,pr); 
  
  /* Init the atlas */
  if (!InitAtlasFromPoint(pr,FALSE,FALSE,p,w,a))
    Error("Can not start atlas from the given point (MinimizeOnAtlas)");

  k=(unsigned int)GetParameter(CT_N_DOF,pr);

  /* Get the system varibles */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,a->w);
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }

  /* Init the set of traces */
  mt=5;  /* In general only one trace will be followed */
  NEW(t,mt,TMinTrace*);
  nt=1;  /* So far we only have one trace */
  /* Init the first trace */
  NEW(t[0],1,TMinTrace);
  t[0]->st=0;
  t[0]->nc=0; /* Start the minimization from the first chart. */
  InitSamples(&(t[0]->ms),&(t[0]->ns),&(t[0]->path));

  NEW(g,k,double); /* gradient (in tangent space) */
  NEW(d,k,double); /* displacement */
  NEW(newPoint,a->m,double); /* new temptative point */
  
  /* Start by tracing the path from the given point */
  l=0;

  /* Add the first point to the path */
  currentPoint=GetChartCenter(a->charts[t[l]->nc]);
  CS_WD_REGENERATE_ORIGINAL_POINT(pr,currentPoint,&o,a->w);
  AddSample2Samples(nv,o,nvs,systemVars,&(t[l]->ms),&(t[l]->ns),&(t[l]->path));
  free(o);

  /* Compute the initial cost (debug purposes only) */
  cost=costF(pr,TRUE,currentPoint,costData);
  fprintf(stderr,"  Initial cost: %g\n",cost);


  stepSize=delta;
  ok=TRUE; /* if false at the end, indicates that we defined a chart at a singularity */

  while(l<nt)
    {
      done=FALSE;
      
      while (!done)
	{
	  /* Point from where to continue the minimization */
	  currentChart=a->charts[t[l]->nc];
	  currentPoint=GetChartCenter(currentChart);

	  /* Evaluation of -gradient */
	  if (costG==NULL)
	    {
	      /* Numerical */
	      cost=costF(pr,TRUE,currentPoint,costData);

	      for(i=0;i<k;i++)
		d[i]=0;
	 
	      for(i=0;i<k;i++)
		{
		  d[i]=100*epsilon;
		  if (Chart2Manifold(pr,&(a->J),d,NULL,currentPoint,newPoint,currentChart)<INF)
		    {
		      cost1=costF(pr,TRUE,newPoint,costData);
		      g[i]=-(cost1-cost)/(100*epsilon);
		    }
		  else
		    Error("Can not converge to the manifold in MinimizeOnAtlas");
		  d[i]=0.0;
		}
	    }
	  else
	    {
	      /* using a user-provided function */
	      costG(pr,TRUE,currentPoint,&gFull,costData);
	      
	      if (a->k==a->m)
		memcpy(g,gFull,a->k*sizeof(double));
	      else
		TMatrixVectorProduct(a->m,a->k,GetChartTangentSpace(currentChart),gFull,g);
	      
	      free(gFull);
	      
	      ScaleVector(-1,a->k,g);
	    }
	  ng=Norm(k,g);
	  done=(Norm(k,g)<epsilon);
	  
	  if (!done)
	    {
	      /* start with a temptative step sizer of twice
	         the size of last step */
	      stepSize*=2;
	      if (stepSize>delta)
		stepSize=delta;
	      
	      if (ng<stepSize)
		ScaleVector(stepSize/ng,k,g);
	      
	      pnc=a->currentChart; /* charts in the atlas before adding the new one */

	      do {
		retraction=FALSE;

		if (Chart2Manifold(pr,&(a->J),g,NULL,currentPoint,newPoint,currentChart)>e)
		  retraction=TRUE;
		else
		  {
		    cost1=costF(pr,TRUE,newPoint,costData);
		    if (cost1>cost)
		      retraction=TRUE;
		    else
		      {
			//AddChart2Atlas(pr,newPoint,t[l]->nc,&sing,a);
			AddChart2Atlas(pr,newPoint,NO_UINT,&sing,a);
			if (pnc==a->currentChart)
			  retraction=TRUE;
			else
			  {
			    /* at least one chart created -> check it */
			    done=FrontierChart(a->charts[pnc]);
			    ok&=(!sing);
			  }
		      }
		  }
		
		if (retraction)
		  {
		    ScaleVector(0.5,k,g);
		    done=(Norm(k,g)<epsilon);
		    stepSize*=0.5;
		  }
	      } while((retraction)&&(!done));

	      if ((maxSteps<150)||(t[l]->st%100==1))
		{
		  fprintf(stderr,"  Branch %u  step %u:  point: [%g %g ...]\n",l,t[l]->st,newPoint[0],newPoint[1]);
		  fprintf(stderr,"    cost: %g\n",cost1);
		  fprintf(stderr,"    norm gradient: %g\n",ng);
		  fprintf(stderr,"    norm disp.: %g\n",Norm(k,g));
		}
	      
	      if (!done)
		{
		  if (a->currentChart>pnc+1)
		    {
		      fprintf(stderr,"    ******* BIFURCATION *******\n");
		      /* We stepped over a singularity -> bifurcate the path */
		      /* duplicate the path */
		      if (nt==mt)
			{ MEM_DUP(t,mt,TMinTrace*); }

		      NEW(t[nt],1,TMinTrace);

		      InitSamples(&(t[nt]->ms),&(t[nt]->ns),&(t[nt]->path));
		      for(j=0;j<t[l]->ns;j++)
			AddSample2Samples(nvs,t[l]->path[j],nvs,NULL,
					  &(t[nt]->ms),&(t[nt]->ns),&(t[nt]->path));
		      t[nt]->st=t[l]->st;

		      /* Now extend the current path */
		      currentPoint=GetChartCenter(a->charts[pnc+1]); /* point at bifurcation */
		      CS_WD_REGENERATE_ORIGINAL_POINT(pr,currentPoint,&o,a->w);
		      AddSample2Samples(nv,o,nvs,systemVars,&(t[l]->ms),&(t[l]->ns),&(t[l]->path));
		      free(o);
		      currentPoint=GetChartCenter(a->charts[pnc+0]); /* point at current branch (== newPoint) */
		      CS_WD_REGENERATE_ORIGINAL_POINT(pr,currentPoint,&o,a->w);
		      AddSample2Samples(nv,o,nvs,systemVars,&(t[l]->ms),&(t[l]->ns),&(t[l]->path));
		      free(o);
		      t[l]->nc=pnc+0;

		      /* And extend the new path */
		      currentPoint=GetChartCenter(a->charts[pnc+1]); /* point at bifurcation */
		      CS_WD_REGENERATE_ORIGINAL_POINT(pr,currentPoint,&o,a->w);
		      AddSample2Samples(nv,o,nvs,systemVars,&(t[nt]->ms),&(t[nt]->ns),&(t[nt]->path));
		      free(o);
		      currentPoint=GetChartCenter(a->charts[pnc+2]); /* point in new brach */
		      CS_WD_REGENERATE_ORIGINAL_POINT(pr,currentPoint,&o,a->w);
		      AddSample2Samples(nv,o,nvs,systemVars,&(t[nt]->ms),&(t[nt]->ns),&(t[nt]->path));
		      free(o);
		      t[nt]->nc=pnc+2;

		      /* We have a new path already stareted */
		      nt++;
		    }
		  else
		    {
		      /* Add the point to the path */
		      currentPoint=GetChartCenter(a->charts[pnc]); /* == newPoint */
		      CS_WD_REGENERATE_ORIGINAL_POINT(pr,currentPoint,&o,a->w);
		      AddSample2Samples(nv,o,nvs,systemVars,&(t[l]->ms),&(t[l]->ns),&(t[l]->path));
		      free(o);
		      t[l]->nc=pnc;
		    }
		  
		  t[l]->st++;
		  done=(t[l]->st>maxSteps);
		}
	    }
	}

      /* Continue next pending minimization path */
      l++;
    }
  
  free(d);
  free(g);
  free(newPoint);
  
  if (!ok)
    Warning("A singularity was detected during the minimization but it could not be determined if it was a bifurcation. Try a smaller epsilon or a larger delta?");

  /* Save the stored paths */
  if (nt==1)
    SaveSamples(fname,FALSE,nvs,t[0]->ns,t[0]->path);
  else
    {
      for(l=0;l<nt;l++)
	SaveSamplesN(fname,FALSE,l,nvs,t[l]->ns,t[l]->path);
    }

  free(systemVars);
  
  return(ok);
}

double GetAtlasRadius(Tatlas *a)
{
  return(a->r);
}

double GetAtlasError(Tatlas *a)
{
  return(a->e);
}

double GetAtlasErrorCurv(Tatlas *a)
{
  return(a->ce);
}

TAtlasBase* GetAtlasWorld(Tatlas *a)
{
  return(a->w);
}

unsigned int GetAtlasAmbientDim(Tatlas *a)
{
  return(a->m);
}

unsigned int GetAtlasManifoldDim(Tatlas *a)
{
  return(a->k);
}

boolean AtlasAStar(Tparameters *pr,double *p,double *time,
		   double *pl,unsigned int *ns,double ***path,Tatlas *a)
{
  Theap h;
  unsigned int i;
  TAtlasHeapElement he,he2,*hePtr;
  unsigned int *chartID;
  unsigned int mID;
  TAStarInfo *info,*infoID,*infoParent;
  /* The 'pred' must be stored apart to re-use the path reconstruction function */
  unsigned int *pred;   /**< Predecesor. Previou node in the best path to the start node. */
  boolean found;
  double *t;
  double epsilon;
  unsigned int nn,id;
  double c,dst;
  double *pID,*pmID;
  double *ps,*pWithDummies;
  double er;
  unsigned int nv;
  boolean *systemVars;
  unsigned int cm,cmPrev,mmPrev;
  TAtlasStatistics *st;
  unsigned int nc;
  unsigned int it;
  Tstatistics stime;  
  double beta;
  boolean collision=FALSE;
  double maxTime;
  unsigned int maxCharts;
  unsigned int nce;
  unsigned int *vs; /* set of vertex indices (only used in parallel execution). */
  double **ts; /* set of vertex coordinates (only used in parallel execution). */
  Tchart **newCharts; /* set of generated charts (only used in parallel execution). */

  if (a->currentChart!=1)
    Error("AtlasAStar assumes an initial atlas with only one local chart");

  epsilon=GetParameter(CT_EPSILON,pr);
  beta=GetParameter(CT_ATLASGBF_BETA,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxCharts=(unsigned int)GetParameter(CT_MAX_CHARTS,pr);

  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,a->w);
  CS_WD_REGENERATE_SOLUTION_POINT(pr,p,&pWithDummies,a->w);
  if (CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&ps,a->w)!=a->m)
    Error("Dimension missmatch in AtlasAStar");
  free(pWithDummies);
  if (a->n==0)
    er=0.0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,ps,a->w);
  if (er>epsilon)
    Error("Target point for the AtlasAStar is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,a->w);
  if (collision)
    Warning("Target point for the AtlasAStar is in collision");

  InitHeap(sizeof(TAtlasHeapElement),
	   CopyAtlasHeapElement,
	   DeleteAtlasHeapElement,
	   LessThanAtlasHeapElement,
	   NULL,FALSE,INIT_NUM_CHARTS_IN_ATLAS_HEAP,&h);
  
  NEW(t,a->k,double);

  NEW(info,a->maxCharts,TAStarInfo);
  NEW(pred,a->maxCharts,unsigned int);

  info[0].cost=0;
  info[0].heuristic=DistanceTopology(a->m,a->tp,ps,GetChartCenter(a->charts[0]));
  info[0].status=1; /*open*/
  pred[0]=NO_UINT;

  if (a->parallel)
    {
      st=NULL;
      NEW(chartID,a->nCores,unsigned int);
      NEW(newCharts,a->nCores,Tchart *);
      NEW(vs,a->nCores,unsigned int);
      NEW(ts,a->nCores,double*);
      for(i=0;i<a->nCores;i++)
	NEW(ts[i],a->k,double);
    }
  else
    {
      NEW(st,1,TAtlasStatistics);
      InitAtlasStatistics(st);
    }

  InitAtlasHeapElement(0,info[0].cost+info[0].heuristic,beta,&he);
  AddElement2Heap(NO_UINT,(void *)(&he),&h);

  found=FALSE;

  it=0;
  
  InitStatistics(a->nCores,0,&stime);
  *time=0.0;

  while ((!found)&&(!HeapEmpty(&h))&&(*time<maxTime)&&(a->currentChart<maxCharts))
    {
      if ((ATLAS_VERBOSE)||((it%1000)==0))
	{
	  printf("Iteration %u (c:%u  t:%g)\n",it,a->currentChart,*time);
	  fflush(stdout);
	}

      ExtractMinElement((void *)(&he),&h);
      mID=GetAtlasHeapElementID(&he);
      infoParent=&(info[mID]);

      /* If the current chart already includes the goal we are done */
      if ((PointOnChart(pr,&(a->J),ps,a->tp,t,a->charts[mID]))&&
	  (DistanceOnChart(pr,t,a->tp,&(a->J),a->charts[mID])<INF))
	found=TRUE;
      else
	{
	  /* already closed element? The heap can hold alternative paths to 
	     the same node that have been improved over time. Instead of 
	     removing them from the heap as better paths are found we leave 
	     them as just ignore them when extracted. 
	     Moreover, we do not expand nodes whose cost is INF
	  */
	  if ((infoParent->status!=2)&&(infoParent->cost<INF))
	    {
	      cmPrev=a->currentChart;
	      mmPrev=a->maxCharts;

	      if (a->parallel)
		{
		  while(ExpandibleChart(a->charts[mID]))
		    {
		      /* We have to genere new neighbors for chart 'mID'. 
			 Select up to 'nCores' other expandible charts and generate neighbours
		         in parallel with the aim of saving time in future interations. */
		      chartID[0]=mID;
		      nce=1;
		      i=0;
		      while((i<HeapSize(&h))&&(nce<a->nCores))
			{
			  hePtr=(TAtlasHeapElement*)GetHeapElement(i,&h); /* does not remove from heap */
			  
			  chartID[nce]=GetAtlasHeapElementID(hePtr);
			  if (ExpandibleChart(a->charts[chartID[nce]]))
			    nce++;
			  i++;
			}
                      #pragma omp parallel for private(i) schedule(static)
		      for(i=0;i<nce;i++)
			{
			  newCharts[i]=NULL;
			  if (BoundaryPointFromExternalCorner(FALSE,&(vs[i]),ts[i],a->charts[chartID[i]]))
			    {
			      NewChartFromPoint(pr,chartID[i],ts[i],&(newCharts[i]),a); 

			      /* ensure that the selected corner is maked as "already used" */
			      WrongCorner(vs[i],a->charts[chartID[i]]);
			    }
			}

		      /* Add the new charts to the atlas */
		      for(i=0;i<nce;i++)
			{
			  if (newCharts[i]!=NULL)
			    {
			      if (a->currentChart==a->maxCharts)
				MEM_DUP(a->charts,a->maxCharts,Tchart *);
			  
			      /* We directly re-use the charts to safe one copy. */
			      a->charts[a->currentChart]=newCharts[i];
			      a->currentChart++;

			      /* Now detect neighbours and the possible bifurcations */
			      PostProcessNewCharts(pr,TRUE,chartID[i],st,a);
			    }	
			}
		    }
		}
	      else
		{
		  /* Generating all neighbours for this chart: one for each external vertex */
		  while(ExpandibleChart(a->charts[mID]))
		    {
		      NewBoundaryAttempt(st);
		      if (!BoundaryPointFromExternalCorner(FALSE,&nc,t,a->charts[mID]))
			{
			  NewNotInBoundary(st);
			  Error("Can not generate neighbouring charts");
			}
		      else
			{
			  ExtendAtlasFromPoint(pr,mID,t,st,a);

			  /* ensure that the selected corner is maked as "already used" */
			  WrongCorner(nc,a->charts[mID]);
			}
		    } /* end of generate all neighbours */
		}

	      /* set the A*-related information for the new charts */
	      if (mmPrev<a->maxCharts)
		{
		  MEM_EXPAND(info,a->maxCharts,TAStarInfo);
		  MEM_EXPAND(pred,a->maxCharts,unsigned int);
		}
	      
	      for(cm=cmPrev;cm<a->currentChart;cm++)
		{
		  /*Mark the new charts as un-visited*/
		  info[cm].status=0;/* not open nor closed*/
		  info[cm].heuristic=0;
		  info[cm].cost=0;
		  pred[cm]=NO_UINT;
		}
	      
	      /* Now that we have all the neighbours explicited proceed with 
		 the A* */
	      pmID=GetChartCenter(a->charts[mID]);

	      nn=ChartNumNeighbours(a->charts[mID]);
	      for(i=0;i<nn;i++)
		{
		  id=ChartNeighbourID(i,a->charts[mID]);
		  if (id!=NO_UINT)
		    {
		      infoID=&(info[id]);

		      #if (_DEBUG>3)
		        printf("    N[%u->%u][%u] : ",mID,id,infoID->status);
		      #endif

		      if (infoID->status!=2) /*not closed (closed can not be improved)*/
			{
			  pID=GetChartCenter(a->charts[id]);

			  /* Geodesic distance is more accurate than euclidean and
			     includes the presence of obstacles, if any. If obstacles
			     are for sure not present, we just use the Euclidean
			     distance.
			     
			     Caution: The GeodesicDistance function is not always
			     able to find the path when it exists. This can induce
			     sub-optimatility in the search. Moreover, the returned
			     path is not the true geodesic, but at least is a path
			     on the manifold. Use with caution.
			  */
			  if (ON_CUIKSYSTEM(a->w))
			    dst=DistanceTopology(a->m,a->tp,pmID,pID);
			  else
			    dst=GeodesicDistance(pr,mID,id,a); /* This might be parallelized */

			  c=infoParent->cost+dst;

			  if ((infoID->status==0)|| /* 1st time we see this node */
			      (c<infoID->cost))     /* status must be 1 (open) */
			    { 
			      #if (_DEBUG>3)
			        if (infoID->status==0)
				  printf("new %g -> %g\n",dst,c);
				else
				  printf("cheaper %g -> %g<%g\n",dst,c,infoID->cost);
			      #endif
			      /*not open not closed (1st time we see this node) */
			      pred[id]=mID;
			      infoID->cost=c;
			      infoID->heuristic=DistanceTopology(a->m,a->tp,pID,ps);

			      /* if open we are re-adding it to the heap. The cheapest
			         path will have higher priority in the heap. */
			      InitAtlasHeapElement(id,infoID->cost+infoID->heuristic,beta,
						   &he2);
			      AddElement2Heap(NO_UINT,(void *)(&he2),&h);

			      infoID->status=1; /*open*/
			    }
			  #if (_DEBUG>3)
			    else
			      printf("%g > %g\n",c,infoID->cost);
			  #endif
			}
		      #if (_DEBUG>3)
		      else
			printf("closed (%g)\n",infoID->cost);
		      #endif
		    }
		}

	      infoParent->status=2; /*we close the current node node (all neighbors already explored) */

	    } /*alrady closed element*/
	} /*if objective found*/
      
      it++;
      *time=GetElapsedTime(&stime);
    } /*loop until objective found*/

  DeleteStatistics(&stime);
  
  /* Use the pred to reconstruct the path */
  if (found)
    ReconstructAtlasPath(pr,pred,mID,ps,nv,systemVars,pl,ns,path,a);
  else
    {
      *ns=0;
      path=NULL;
    }

  if (a->parallel)
    {
      free(chartID);
      free(newCharts);
      free(vs);
      for(i=0;i<a->nCores;i++)
	free(ts[i]);
      free(ts);
    }

  if (st!=NULL)
    {
      PrintAtlasStatistics(pr,st);
      free(st);
    }

  free(info);
  free(pred);

  free(t);
  free(ps);
  DeleteHeap(&h);
  free(systemVars);

  return(found);
}

boolean AtlasGBF(Tparameters *pr,double *p,double *time,
		 double *pl,unsigned int *ns,double ***path,Tatlas *a)
{
  Theap h;
  TAtlasHeapElement he,he2;
  unsigned int mID;
  double heuristic;
  unsigned int *pred;
  boolean found;
  double *t;
  double epsilon;
  double *ps,*pWithDummies;
  double er;
  unsigned int nv;
  boolean *systemVars;
  unsigned int cm,cmPrev,mmPrev;
  TAtlasStatistics st;
  unsigned int it;
  Tstatistics stime;  
  double beta;
  boolean collision=FALSE;
  double maxTime;
  unsigned int maxCharts;

  if (a->currentChart!=1)
    Error("Connect2Atlas assumes an initial atlas with only one local chart");

  epsilon=GetParameter(CT_EPSILON,pr);
  beta=GetParameter(CT_ATLASGBF_BETA,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxCharts=(unsigned int)GetParameter(CT_MAX_CHARTS,pr);

  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,a->w);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,p,&pWithDummies,a->w);
  if (CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&ps,a->w)!=a->m)
    Error("Dimension missmatch in AtlasGBF");
  if (a->n==0)
    er=0.0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,ps,a->w);
  if (er>epsilon)
    Error("Target point for the AtlasGBF is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,a->w);
  if (collision)
    Warning("Target point for the AtlasGBF is in collision");
  free(pWithDummies);
  
  InitHeap(sizeof(TAtlasHeapElement),
	   CopyAtlasHeapElement,
	   DeleteAtlasHeapElement,
	   LessThanAtlasHeapElement,
	   NULL,FALSE,INIT_NUM_CHARTS_IN_ATLAS_HEAP,&h);
  
  NEW(t,a->k,double);

  NEW(pred,a->maxCharts,unsigned int);

  heuristic=DistanceTopology(a->m,a->tp,GetChartCenter(a->charts[0]),ps);
  pred[0]=NO_UINT;

  InitAtlasStatistics(&st);

  InitAtlasHeapElement(0,heuristic,beta,&he);
  AddElement2Heap(NO_UINT,(void *)(&he),&h);

  found=FALSE;

  it=0;
  InitStatistics(a->nCores,0,&stime);
  *time=0.0;

  while ((!found)&&(!HeapEmpty(&h))&&(*time<maxTime)&&(a->currentChart<maxCharts))
    {
      ExtractMinElement((void *)(&he),&h);
      mID=GetAtlasHeapElementID(&he);

      if ((ATLAS_VERBOSE)||((it%1000)==0))
	{
	  printf("Iteration %u (c:%u  t:%g)\n",it,a->currentChart,*time);
	  fflush(stdout);
	}

      if ((PointOnChart(pr,&(a->J),ps,a->tp,t,a->charts[mID]))&&
	  (DistanceOnChart(pr,t,a->tp,&(a->J),a->charts[mID])<INF))
	found=TRUE;
      else
	{
	  if (ExpandibleChart(a->charts[mID]))
	    {
	      NewBoundaryAttempt(&st);
	     
	      if (!RandomPointOnBoundary(t,a->charts[mID]))
		{
		  NewNotInBoundary(&st);
		  PenalizeAtlasHeapElement(&he);
		}
	      else
		{
		  /*printf("  New random point: ");PrintVector(stdout,a->k,t);*/

		  cmPrev=a->currentChart;
		  mmPrev=a->maxCharts;
		  if (ExtendAtlasTowardPoint(pr,mID,t,TRUE,&st,a))
		    { 
		      /* If we extended the room for charts, we have to
			 extend the associated information accordingly*/
		      if (mmPrev<a->maxCharts)
			MEM_EXPAND(pred,a->maxCharts,unsigned int);

		      for(cm=cmPrev;cm<a->currentChart;cm++)
			{
			  pred[cm]=mID;
			  heuristic=DistanceTopology(a->m,a->tp,
						     GetChartCenter(a->charts[cm]),
						     ps);
			  InitAtlasHeapElement(cm,heuristic,beta,&he2);
			  AddElement2Heap(NO_UINT,(void *)(&he2),&h);
			}
		    }
		  else
		    PenalizeAtlasHeapElement(&he);
		}

	      AddElement2Heap(NO_UINT,(void *)(&he),&h);
	    } /* if ExpandibleChart() = chart that can be expanded*/
	} /*if objective found*/

      it++;
      *time=GetElapsedTime(&stime);
    } /*loop until objective found*/
  DeleteStatistics(&stime);

  /* Use the pred to reconstruct the path */
  if (found)
    ReconstructAtlasPath(pr,pred,mID,ps,nv,systemVars,pl,ns,path,a);
  else
    {
      *ns=0;
      path=NULL;
    }

  PrintAtlasStatistics(pr,&st);

  free(pred);
  free(t);
  free(ps);
  DeleteHeap(&h);
  free(systemVars);

  return(found);
}

unsigned int AtlasMemSize(Tatlas *a)
{
  unsigned int b,i;

  b=0;
  for(i=0;i<a->currentChart;i++)
    b+=ChartMemSize(a->charts[i]); /* charts[][] */

  return(b);
}

void SaveAtlas(Tparameters *pr,Tfilename *fname,Tatlas *a)
{
  FILE *f;
  unsigned int i;
  
  f=fopen(GetFileFullName(fname),"w");
  if (!f)
    Error("Could not open fiel to store atlas");
  
  fprintf(f,"%u\n",a->m);
  fprintf(f,"%u\n",a->k);
  fprintf(f,"%u\n",a->n);
  fprintf(f,"%.12f\n",a->e);
  fprintf(f,"%.12f\n",a->ce);
  fprintf(f,"%.12f\n",a->r);
  fprintf(f,"%u\n",a->simpleChart);
  
  fprintf(f,"%u\n",a->maxCharts);
  fprintf(f,"%u\n",a->currentChart);
  for(i=0;i<a->currentChart;i++)
    SaveChart(f,a->charts[i]);

  SaveBifurcations(f,a);

  fclose(f);
}

void LoadAtlas(Tparameters *pr,Tfilename *fname,TAtlasBase *w,Tatlas *a)
{
  FILE *f;
  unsigned int i;
  
  f=fopen(GetFileFullName(fname),"r");
  if (!f)
    Error("Could not open file to read atlas");

  fscanf(f,"%u",&(a->m));
  fscanf(f,"%u",&(a->k));
  fscanf(f,"%u",&(a->n));
  fscanf(f,"%lf",&(a->e));
  fscanf(f,"%lf",&(a->ce));
  fscanf(f,"%lf",&(a->r));
  fscanf(f,"%u",&(a->simpleChart));

  a->w=w;
  
  NEW(a->ambient,1,Tbox);
  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,a->ambient,a->w);
  
  SetAtlasTopology(pr,a);
  
  fscanf(f,"%u",&(a->maxCharts));
  fscanf(f,"%u",&(a->currentChart));
  NEW(a->charts,a->maxCharts,Tchart *);
  for(i=0;i<a->currentChart;i++)
    {
      NEW(a->charts[i],1,Tchart);
      LoadChart(f,a->w,a->charts[i]);

      #if (USE_ATLAS_TREE)
        if (i==0)
	  InitBTree(i,a->charts[i],a->ambient,a->tp,&(a->tree));
	else
	  AddChart2Btree(i,a->charts[i],&(a->tree));
      #endif
    }

  LoadBifurcations(f,a);

  fclose(f);

  /* The Jacobian is not saved but re-computed */
  CS_WD_GET_SIMP_JACOBIAN(pr,&(a->J),a->w);
  GetJacobianSize(&(a->nrJ),&(a->ncJ),&(a->J));
 
  /* delay the Hessian computation */
  a->H=NULL;

  /* The parallelism information is not stored! */
  #ifdef _OPENMP
    a->nCores=omp_get_max_threads();
    a->parallel=((a->nCores>1)&&((a->m>25)||(a->k>2)));
  #else
    a->parallel=FALSE;
  #endif

  if (!a->parallel)
    a->nCores=1;
}

unsigned int GetAtlasNumCharts(Tatlas *a)
{
  return(a->currentChart);
}

Tchart *GetAtlasChart(unsigned int id,Tatlas *a)
{
  if (id<a->currentChart)
    return(a->charts[id]);
  else
    return(NULL);
}

boolean RandomPointInAtlas(Tparameters *pr,double scale,double *w,
			   unsigned int *nm,
			   double *t,double *p,Tatlas *a)
{
  boolean havePoint;

  if (w==NULL)
    {
      /* Uniform distribution on charts*/
      *nm=randomMax(a->currentChart-1);
    }
  else
    {
      /* Select the charts from the given distribution */
      randomWithDistribution(a->currentChart,0.0,w);
    }
  /* Get a point from the selected chart */
  havePoint=RandomPointInChart(pr,scale,a->tp,t,p,a->charts[*nm]);
 
  return(havePoint);
}

double AtlasVolume(Tparameters *pr,boolean collisionFree,Tatlas *a)
{
  unsigned int i;
  double v,vc;

  v=0.0;
  for(i=0;i<a->currentChart;i++)
    {
      if (!FrontierChart(a->charts[i]))
	{
	  vc=ChartVolume(pr,collisionFree,a->tp,&(a->J),a->charts[i]);
	  #if (ATLAS_VERBOSE)
	    printf("  Volume of chart %u: %g\n",i,vc);
	  #endif
	  v+=vc;
	}
    }

  return(v);
}

void SaveAtlasGraph(char *fname,Tatlas *a)
{
  Tfilename fg;
  FILE *f;
  unsigned int i,j,n;

  CreateFileName(NULL,fname,NULL,ATLAS_GRAPH_EXT,&fg);
  f=fopen(GetFileFullName(&fg),"w");
  if (!f)
    Error("Could not open the file to store the atlas graph in SaveAtlasGraph");
  fprintf(stderr,"Writing atlas graph to            : %s\n",GetFileFullName(&fg));

  fprintf(f,"%u\n",a->currentChart);
  for(i=0;i<a->currentChart;i++)
    {
      n=ChartNumNeighbours(a->charts[i]);
      fprintf(f,"%u ",n);
      for(j=0;j<n;j++)
	fprintf(f,"%u ",ChartNeighbourID(j,a->charts[i]));
      fprintf(f,"\n");
    }
  
  fclose(f);
  DeleteFileName(&fg);
}

void SaveChartCenters(Tparameters *pr,char *fname,
		      boolean saveWithDummies,Tatlas *a)
{   
  double *o;
  unsigned int i,j,nv,nvs;
  boolean *systemVars;
  double *c;
  FILE *fo;
  Tfilename fsol;

  if (saveWithDummies)
    CreateFileName(NULL,fname,"_center",SOL_WITH_DUMMIES_EXT,&fsol);
  else
    CreateFileName(NULL,fname,"_center",SOL_EXT,&fsol);
  fprintf(stderr,"Writing boxes to                  : %s\n",GetFileFullName(&fsol));
  fo=fopen(GetFileFullName(&fsol),"w");
  if (!fo)
    Error("Could not open the file to store the boxes in GetChartCenters");

  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,a->w);
  nvs=0;
  for(j=0;j<nv;j++)
    {
      if (systemVars[j])
	nvs++;
    }
    
  for(i=0;i<a->currentChart;i++)
    {
      c=GetChartCenter(a->charts[i]);
      
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,c,&o,a->w);
      
      if (saveWithDummies)
	fprintf(fo,"%u { %u ",i,nv);
      else
	fprintf(fo,"%u { %u ",i,nvs);
      for(j=0;j<nv;j++)
	{
	  if ((saveWithDummies)||(systemVars[j]))
	    fprintf(fo,"[%.12g,%.12g] ",o[j],o[j]);
	}
      fprintf(fo,"}\n");

      free(o);  
    }
 
  fclose(fo);

  free(systemVars);
  
  DeleteFileName(&fsol);
}

void SaveSingularCharts(Tparameters *pr,char *fname,
			boolean saveWithDummies,Tatlas *a)
{   
  double *o;
  unsigned int i,j,nv,nvs;
  boolean *systemVars;
  double *c;
  FILE *fo;
  Tfilename fsol;

  if (saveWithDummies)
    CreateFileName(NULL,fname,"_singular",SOL_WITH_DUMMIES_EXT,&fsol);
  else
    CreateFileName(NULL,fname,"_singular",SOL_EXT,&fsol);
  fprintf(stderr,"Writing boxes to                  : %s\n",GetFileFullName(&fsol));
  fo=fopen(GetFileFullName(&fsol),"w");
  if (!fo)
    Error("Could not open the file to store the boxes in GetChartCenters");

  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,a->w);
  nvs=0;
  for(j=0;j<nv;j++)
    {
      if (systemVars[j])
	nvs++;
    }

  for(i=0;i<a->currentChart;i++)
    {
      if (SingularChart(a->charts[i])) 
      	{
	  c=GetChartCenter(a->charts[i]);
      
	  CS_WD_REGENERATE_ORIGINAL_POINT(pr,c,&o,a->w);
      
	  if (saveWithDummies)
	    fprintf(fo,"%u { %u ",i,nv);
	  else
	    fprintf(fo,"%u { %u ",i,nvs);
	  for(j=0;j<nv;j++)
	    {
	      if ((saveWithDummies)||(systemVars[j]))
		fprintf(fo,"[%.12g,%.12g] ",o[j],o[j]);
	    }
	  fprintf(fo,"}\n");

	  free(o);
	}
    }
  fclose(fo);

  free(systemVars);
  
  DeleteFileName(&fsol);
}

void PlotAtlas(char *fname,int argc,char **arg,Tparameters *pr,FILE *fcost,
	       unsigned int xID,unsigned int yID,unsigned int zID,Tatlas *a)
{
  Tplot3d p3d;
  unsigned int i;
  Tcolor color;
  unsigned int obj,np;

  InitPlot3d(fname,FALSE,argc,arg,&p3d);

  /* When plotting as polytopes all charts are plotted in blue and not
     bifurcation info is plotted */
 
  NewColor(0.5,0.5,1,&color); /*default color :blue*/
  obj=StartNew3dObject(&color,&p3d);
  np=0;
  for(i=0;i<a->currentChart;i++)
    {
      if ((fcost!=NULL)||(a->simpleChart)||
	  ((PLOT_ATLAS_IN_COLORS)&&(!ExpandibleChart(a->charts[i]))&&
	   (!SingularChart(a->charts[i])&&(!FrontierChart(a->charts[i])))))
	{
	  PlotChart(pr,fcost,&(a->J),xID,yID,zID,&p3d,a->charts[i]);
	  //PrintVector(stderr,NULL,a->m,a->charts[i]->center);
	  np++;
	}
    }
  if ((a->k==2)&&(fcost!=NULL))
    Close3dObjectNoColor(&p3d); /* the cost already gave the color when plotting */
  else
    Close3dObject(&p3d);
  if (np==0)
    Delete3dObject(obj,&p3d);
  DeleteColor(&color);
  
  if ((PLOT_ATLAS_IN_COLORS)&&(fcost==NULL)&&(!a->simpleChart))
    { 
      /* Singular charts in green */
      NewColor(0,1,0,&color); /*green*/
      obj=StartNew3dObject(&color,&p3d);
      np=0;
      for(i=0;i<a->currentChart;i++)
	{
	  if ((!ExpandibleChart(a->charts[i]))&&(SingularChart(a->charts[i])&&(!FrontierChart(a->charts[i]))))
	    {
	      np++;
	      PlotChart(pr,NULL,&(a->J),xID,yID,zID,&p3d,a->charts[i]);
	      //PrintVector(stderr,NULL,a->m,a->charts[i]->center);
	    }
	}
    
      Close3dObject(&p3d);
      DeleteColor(&color);
      if (np==0)
	Delete3dObject(obj,&p3d);
    
      /* Open charts if red (Open = expansion is still possible)  */
      NewColor(1,0.5,0.5,&color); /*red*/
      obj=StartNew3dObject(&color,&p3d);
      np=0;
      for(i=0;i<a->currentChart;i++)
	{
	  if ((ExpandibleChart(a->charts[i]))&&(!SingularChart(a->charts[i])&&(!FrontierChart(a->charts[i]))))
	    {
	      np++;
	      PlotChart(pr,NULL,&(a->J),xID,yID,zID,&p3d,a->charts[i]);
	    }
	}
    
      Close3dObject(&p3d);
      DeleteColor(&color);
      if (np==0)
	Delete3dObject(obj,&p3d);
    
      /* Expandible singular charts in yellow  */
      NewColor(1,1,0,&color); /*yellow*/
      obj=StartNew3dObject(&color,&p3d);
      np=0;
      for(i=0;i<a->currentChart;i++)
	{
	  if ((ExpandibleChart(a->charts[i]))&&(SingularChart(a->charts[i])&&(!FrontierChart(a->charts[i]))))
	    {
	      np++;
	      PlotChart(pr,NULL,&(a->J),xID,yID,zID,&p3d,a->charts[i]);
	    }
	}
    
      Close3dObject(&p3d);
      DeleteColor(&color);
      if (np==0)
	Delete3dObject(obj,&p3d);    

      /* Frontier charts in dark red  */
      NewColor(0.25,0,0,&color); /* */
      obj=StartNew3dObject(&color,&p3d);
      np=0;
      for(i=0;i<a->currentChart;i++)
	{
	  //if ((!ExpandibleChart(a->charts[i]))&&(!SingularChart(a->charts[i])&&(FrontierChart(a->charts[i]))))
	  if (FrontierChart(a->charts[i]))
	    {
	      np++;
	      PlotChart(pr,NULL,&(a->J),xID,yID,zID,&p3d,a->charts[i]);
	    }
	}
    
      Close3dObject(&p3d);
      DeleteColor(&color);
      if (np==0)
	Delete3dObject(obj,&p3d);    

      /* Now plot a line connecting chart at the two sides of a singularity */
      //PlotBifurcations(pr,&p3d,xID,yID,zID,a);
    }

  /*line for the neighbouring relations*/
#if (0)
  {
    unsigned int j;
    double *pi,*pj;
    double x[2],y[2],z[2];
    unsigned int nn,nj;
    double *o;

    NewColor(1,1,0,&color);
    StartNew3dObject(&color,&p3d);
    for(i=0;i<a->currentChart;i++)
      {
	pi=GetChartCenter(a->charts[i]);  
	CS_WD_REGENERATE_ORIGINAL_POINT(pr,pi,&o,a->w);
	x[0]=o[xID];
	y[0]=o[yID];
	z[0]=o[zID];
	free(o);

	nn=ChartNumNeighbours(a->charts[i]);
	if (nn==0)
	  fprintf(stderr,"Chart %u has no neighbours",i);
	for(j=0;j<nn;j++)
	  {
	    nj=ChartNeighbourID(j,a->charts[i]);
	    if ((nj!=NO_UINT)&&(nj>i))
	      { 
		pj=GetChartCenter(a->charts[nj]);
		CS_WD_REGENERATE_ORIGINAL_POINT(pr,pj,&o,a->w);
		x[1]=o[xID];
		y[1]=o[yID];
		z[1]=o[zID];
		free(o);
		PlotVect3d(2,x,y,z,&p3d);
	      }
	  }
      }
    Close3dObject(&p3d);
    DeleteColor(&color);
  }
#endif

  ClosePlot3d(FALSE,&p3d);
}

void TriangulateAtlas(char *fname,int argc,char **arg,Tparameters *pr,FILE *fcost,
		      unsigned int xID,unsigned int yID,unsigned int zID,Tatlas *a)
{
  Tplot3d p3d;
  unsigned int i,j,k;
  Tcolor color;
  double *p,*o;
  double cost;
  double **v; /* Vertices */
  Tcolor *c; /* One color per vertex (might not be used) */
  unsigned int mf,nf; /* Max faces (space allocated for faces) and current number
		         of faces */
  unsigned int *nvf,**fv; /* Vertex per face, and vertices in each face. */
  unsigned int nTmp;
  double v1[3],v2[3],cosAngle;
  boolean *corrected,*used;
  double **normal;
  unsigned int nc;
  boolean correctionDone;
  unsigned int nn,*nID1,*nID2;
  boolean found;
  unsigned int *tp;
  unsigned int rep;
  double cx,cy,cz;

  if (a->k!=2)
    Error("TriangulateAtlas only operates on surfaces (manifold dim=2)");

  NEW(tp,3,unsigned int);
  tp[0]=CS_WD_GET_VAR_TOPOLOGY(xID,a->w);
  tp[1]=CS_WD_GET_VAR_TOPOLOGY(yID,a->w);
  tp[2]=CS_WD_GET_VAR_TOPOLOGY(zID,a->w);

  if ((tp[0]==TOPOLOGY_R)&&(tp[1]==TOPOLOGY_R)&&(tp[2]==TOPOLOGY_R))
    {
      free(tp);
      tp=NULL;
    }

  InitPlot3d(fname,FALSE,argc,arg,&p3d);

  /* Now store the vertices, one per chart (i.e., the center), possibly
     with associated colors */
  NEW(v,a->currentChart,double*);
  if (fcost!=NULL)
    NEW(c,a->currentChart,Tcolor);

  cx=GetParameter(CT_CUT_X,pr);
  cy=GetParameter(CT_CUT_Y,pr);
  cz=GetParameter(CT_CUT_Z,pr);
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
  
  for(i=0;i<a->currentChart;i++)
    {
      NEW(v[i],3,double);
      p=GetChartCenter(a->charts[i]);  
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,p,&o,a->w);
      v[i][0]=o[xID];
      v[i][1]=o[yID];
      v[i][2]=o[zID];
      if (rep==REP_JOINTS)
	{
	  if ((cx<0)&&(v[i][0]<cx))
	    v[i][0]+=M_2PI;
	  if ((cx>0)&&(v[i][0]>cx))
	    v[i][0]-=M_2PI;
	  if ((cy<0)&&(v[i][1]<cy))
	    v[i][1]+=M_2PI;
	  if ((cy>0)&&(v[i][1]>cy))
	    v[i][1]-=M_2PI;
	  if ((cz<0)&&(v[i][2]<cz))
	    v[i][2]+=M_2PI;
	  if ((cz>0)&&(v[i][2]>cz))
	    v[i][2]-=M_2PI;
	}
      free(o);
      if (fcost!=NULL)
	{
	  /* Set up the color for this vertex */
	  if (fscanf(fcost,"%lf",&cost)!=1)
	    Error("No enough data in the cost file");
	  
	  CostColor(cost,1e-1,&(c[i]));
	}
    }

  /* Now set up the faces */
  mf=a->currentChart;
  nf=0;
  NEW(fv,mf,unsigned int*);
  for(i=0;i<a->currentChart;i++)
    {
      GetChartNeighboursFromVertices(pr,&nn,&nID1,&nID2,a->charts[i]);
      for(j=0;j<nn;j++)
	{
	  /* Vertices corresponding to the border of the atlas still
	      have the default faces with NO_UINT as ID -> not use these
	      vertices*/
	  if ((nID1[j]!=NO_UINT)&&(nID2[j]!=NO_UINT))
	    {
	      if (nf==mf)
		MEM_DUP(fv,mf,unsigned int*);
	      NEW(fv[nf],3,unsigned int);
	      
	      fv[nf][0]=i;
	      fv[nf][1]=nID1[j];
	      fv[nf][2]=nID2[j];

	      /* Triangles that cross the borders imposed by the topology
	         should not be considered. */
	      if (tp==NULL)
		found=FALSE;
	      else
		{
		  /*
		  found=((CrossTopologyBorder(a->m,a->tp,
					      GetChartCenter(a->charts[i]),
					      GetChartCenter(a->charts[nID1[j]])))||
			 (CrossTopologyBorder(a->m,a->tp,
					      GetChartCenter(a->charts[i]),
					      GetChartCenter(a->charts[nID2[j]])))||
			 (CrossTopologyBorder(a->m,a->tp,
					      GetChartCenter(a->charts[nID1[j]]),
					      GetChartCenter(a->charts[nID1[j]]))));
		  */
		  found=((CrossTopologyBorder(3,tp,
					      v[i],
					      v[nID1[j]]))||
			 (CrossTopologyBorder(3,tp,
					      v[i],
					      v[nID2[j]]))||
			 (CrossTopologyBorder(3,tp,
					      v[nID1[j]],
					      v[nID2[j]])));
		}

	      k=0;
	      while ((!found)&&(k<nf))
		{
		  found=SameTriangle(fv[nf],fv[k]);
		  k++;
		}
	      if (!found)
		nf++; 
	    }
	}
      free(nID1);
      free(nID2);
    }
  if (tp!=NULL)
    free(tp);

  /* All faces have 3 vertices */
  NEW(nvf,nf,unsigned int);
  for(i=0;i<nf;i++)
    nvf[i]=3;
  /* Fix the orientation for the triangles */
  NEW(used,nf,boolean);
  NEW(corrected,nf,boolean);
  NEW(normal,nf,double*);
  for(i=0;i<nf;i++)
    {
      used[i]=FALSE;
      corrected[i]=FALSE;
      NEW(normal[i],3,double);
    }
  /* Start from the first triangle */
  corrected[0]=TRUE;
  DifferenceVector(3,v[fv[0][1]],v[fv[0][0]],v1);
  DifferenceVector(3,v[fv[0][2]],v[fv[0][0]],v2);
  CrossProduct(v1,v2,normal[0]);
  nc=1;
  correctionDone=FALSE;
  while((!correctionDone)&&(nc<nf))
    {
      /* Search for a corrected no used face */
      i=0;
      while ((i<nf)&&((used[i])||(!corrected[i])))
	i++;
      if (i==nf)
	correctionDone=TRUE;

      if (!correctionDone)
	{
	  /* Align all neighbours with the normal at this face */
	  j=0;
	  while(j<nf)
	    {
	      if (!corrected[j])
		{
		  if (NeighbouringTriangles(fv[i],fv[j]))
		    {
		      DifferenceVector(3,v[fv[j][1]],v[fv[j][0]],v1);
		      DifferenceVector(3,v[fv[j][2]],v[fv[j][0]],v2);
		      CrossProduct(v1,v2,normal[j]);

		      cosAngle=DotProduct(normal[i],normal[j]);
		      if (cosAngle<0)
			{
			  /* Swap the orientation of face j */
			  nTmp=fv[j][1];
			  fv[j][1]=fv[j][2];
			  fv[j][2]=nTmp;
			  ScaleVector(-1.0,3,normal[j]);
			}
		      corrected[j]=TRUE;
		      nc++;
		    }
		}
	      j++;
	    }
	  used[i]=TRUE;
	}
    }
  free(used);
  free(corrected);
  for(i=0;i<nf;i++)
    free(normal[i]);
  free(normal);

  /* Define the object */
  /* Normal charts in blue */
  NewColor(-1,-1,-1,&color); /*blue*/
  StartNew3dObject(&color,&p3d);

  if (fcost==NULL)
    Plot3dObject(a->currentChart,nf,1,v,nvf,fv,&p3d);
  else
    Plot3dObjectWithColors(a->currentChart,nf,1,v,c,nvf,fv,&p3d);

  Close3dObject(&p3d);
  ClosePlot3d(FALSE,&p3d);

  /* Release memory */
  for(i=0;i<a->currentChart;i++)
    free(v[i]);
  free(v);

  if (fcost!=NULL)
    free(c);

  for(i=0;i<nf;i++)
    free(fv[i]);
  free(fv);
  free(nvf);
}

double AverageNumNeighbours(Tatlas *a)
{
  double nn;
  unsigned int i;

  nn=0.0;
  for(i=0;i<a->currentChart;i++)
    nn+=(double)ChartNumNeighbours(a->charts[i]);
  
  return(nn/(double)a->currentChart);
}

void PrintAtlasDefines(FILE *f)
{
  PrintChartDefines(f);
  fprintf(f,"\n   %% Atlas defines\n");
  fprintf(f,"   ATLAS_VERBOSE %u\n",ATLAS_VERBOSE);
  fprintf(f,"   PLOT_ATLAS_IN_COLORS %u\n",PLOT_ATLAS_IN_COLORS);
  fprintf(f,"   PROJECT_WITH_PLANE %u\n",PROJECT_WITH_PLANE);
  fprintf(f,"   USE_ATLAS_TREE %u\n",USE_ATLAS_TREE);
  fprintf(f,"   SAMPLING_RADIUS_REDUCTION_FACTOR %.2f\n",SAMPLING_RADIUS_REDUCTION_FACTOR);
  fprintf(f,"   SIMPLE_BORDER %u\n",SIMPLE_BORDER);
  fprintf(f,"   W_BTREE %u\n",W_BTREE); // This is defined in btree
}

void DeleteAtlas(Tatlas *a)
{
  unsigned int i;

  DeleteJacobian(&(a->J));

  if (a->H!=NULL)
    {
      DeleteHessian(a->H);
      free(a->H);
    }

  for(i=0;i<a->currentChart;i++)
    {
      DeleteChart(a->charts[i]);
      free(a->charts[i]);
    }

  free(a->charts);

  if (a->ambient!=NULL)
    {
      DeleteBox(a->ambient);
      free(a->ambient);
    }

  if (a->tp!=NULL)
    free(a->tp);
  
  DeleteBifurcations(a);
  
  #if (USE_ATLAS_TREE)
    if (a->currentChart>0)
      DeleteBTree(&(a->tree));
  #endif
}
