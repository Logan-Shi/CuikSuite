#ifndef CPOLYTOPE
#define CPOLYTOPE


#include "boolean.h"
#include "box.h"
#include "parameters.h"
#include "scpolytope.h" /* To get some common constants */
#include "wcs.h"

/** 
   \file cpolytope.h
   \brief Definition of a polytope associated to a chart.

   Definition of a polytope defined in the tangent space of a
   chart bounding the area of applicability of the chart.

   Tcspolytope is a simplified version of this object where
   we only store the faces implicitly defining the polytope.

   \sa Tcpolytope,cpolytope.c
*/


/** 
   \brief Factor to expand the polytope w.r.t. the included box.

   Whe initially defining the polytope, we define a box side slightly
   larger than the included ball (to avoid tangencies with it). 
   This is the expansion ratio used.

   We used 5.01 for the voronoi plot in our TRO19_steering paper.
*/
#define POLYTOPE_R_ENLARGEMENT 1.01

/** 
   \brief If set, polytopes are define as circles in 2D spaces.

   This is used for nice plotting where we want the border charts
   in 2D tangent spaces to be shown as circular shapes instead of
   boxes.

   The actual number is the number of segments used to approximate
   the circle.

   We used 200 for the voronoi plot in our TRO19_steering paper.
*/
#define CIRCULAR_POLYTOPE 0

/** 
   \brief A polytope associated with chart on a manifold.
   
   The area of influence of a chart is bounded by a polytope. This is used to
   determine which charts are exterior (belong to the expanding frontier of the
   exploration) and which are interior (completely sorrounded by other local charts).
   (See the \ref Tatlas "atlas" structure to see how charts are ensambled together.)
   The polytope is represented as a set of vertices that is updated every time
   a new chart is added to the atlas. In this case, the polytope stored in the chart
   is cut (removing vertices and adding new ones) with a plane derived from the
   intersection with the new neighbouring charts. Charts with all vertices inside
   the (hyper)sphere are interior.
   
   Being able to differentiate between interior and exterior charts allows to
   control the ratio of expansion/refinement of the atlas.

   \sa chart.h,chart.c.
*/
typedef struct {
  unsigned int k;   /**< Dimension of the feasible velocity space. Can be 
		         lower than the dimension of the manifold in the presence
		         of kino-constraints. If so, the 'k' here is lower
		         than the 'k' in the corresponding chart. Parameter
		         here only use the first components of the tangent space
		         (the rest, used in chart. are assumed to be zero). */
  double r;         /**< Radius around \e p (in tangent space) where the linearization holds.
		         About half the size of the box containing the ball (it is not
		         exactly half due to the \ref POLYTOPE_R_ENLARGEMENT). */
  
  double v;         /**< Volume of the polytope. */

  boolean emptyPolytope;     /**< TRUE if the polytope information is initialized. 
			          We defer the polytope initialization as much as possible.
			          In this way temporary charts never have polytope with the
				  savings in memory allocation/free.
			     */

  unsigned int nFaces;       /**< Num faces defining the polytope so far. */
  unsigned int maxFaces;     /**< Space for faces */
  double **face;             /**< Parameters of the faces defining the polytope */

  unsigned int *ID;          /**< Identifiers of the neighbouring charts (one per face). */

  unsigned int maxVertices;  /**< Space for vertices. */
  unsigned int nVertices;    /**< Number of vertices (if 0 the chart is un-used)*/
  double **vertex;           /**< Polytope vertices. */
  boolean *expandible;       /**< TRUE for that can not be used to expand the chart 
                                  (vertices out of the chart ball, vertices with some error) */
  unsigned int nExpandible;  /**< Number of expandible vertices for the chart. */

  unsigned int freeVertex;   /**< First free vertex. */

  unsigned int *nIndices;    /**< Number of face index per vertex.  */
  unsigned int *maxIndices;  /**< Space for face indices. Also used to link free vertices. */ 
  unsigned int **indices;    /**< Indices of the faces defining a vertex. Vertices with
			          k-1 common faces define an edge. Edges that cross new
			          faces added to the polytope define the new vertices 
				  (and the vertices to be removed). */
  Tbox bb;                   /**< Axis aligned bounding box of the polytope. */
  
  boolean open;              /**< TRUE if the polytope has "open" borders, i.e., faces not given
				  by another chart but with an undefined neighbour. These are
				  undefined or given by the global domain borders. */
} Tcpolytope;


/** 
   \brief Defines an empty chart polytope.

   Defines an empty chart polytope.

   \param k Dimensinality of the space where to define the polytope.
   \param r Radius of the ball to be enclosed by the polytope.
   \param mp The polytope to initialize.
*/
void InitEmptyPolytope(unsigned int k,double r,Tcpolytope *mp);

/** 
   \brief Initial definition of the polytope bounding the local chart.

   Defines a box with all vertices outside the ball defining the polytope.
   This polytope is refined as the local chart intersects with other local charts.
   In this refinement the external vertices progresively moves inside the
   ball. When all points are inside the ball, the chart is no longer in the
   frontier of expansion of the atlas.

   \param mp The polytope to initialize.
*/
void DefinePolytope(Tcpolytope *mp);

/** 
   \brief Defines a chart polytope from a simple chart polytope.

   Defines a chart polytope from a simple chart polytope.
   
   \param pr The set of parameters.
   \param sp The simple polytope from where to get the data.
   \param p The polytope to create.
*/
void SPolytope2Polytope(Tparameters *pr,Tscpolytope *sp,Tcpolytope *p);


/** 
   \brief Defines a simple chart polytope from a normal/full chart polytope.

   Defines a simple chart polytope from a normal/full chart polytope.
   
   \param pr The set of parameters.
   \param p The normal polytope from where to get the data.
   \param sp The simple polytope to create.
*/
void Polytope2SPolytope(Tparameters *pr,Tcpolytope *p,Tscpolytope *sp);


/** 
   \brief Copies the polytope from one chart to another.

   Copies the data defining the polytope from one chart to another.

   Assumes the other fiels of the chart are already copied from
   \e src to \e dst (i.e., this is to be called at the end of the
   chart copy constructor).

   \param mp_dst The polytope where to copy the information.
   \param mp_src The polytope from where to copy the information.
*/
void CopyPolytope(Tcpolytope *mp_dst,Tcpolytope *mp_src);

/** 
   \brief Crops the polytope  bounding chart with a plane.

   Reduces a polytope bounding chart cropping it with a plane defined
   by the intersection of the chart ball with a ball centered at \e t
   with radious \e r. This ball is an approximation in the chart plane
   of the ball bounding another chart.

   This is basically a particular case for \ref CutPolytopeWithFace where the
   face is defined from the intersection of two balls.

   \param pr The set of parameters.
   \param t Center of the new ball.
   \param r Radius of the new ball. This is typically the same as the ball
            for the current polytope. 
   \param id Identifier of the chart generating the cut. This is used to
             update the list of neighbours.  
   \param wcs The equations defining the problem at hand. 
   \param c Pointer to the chart.
   \param m The dimensionality of the ambient space.
   \param tp The topology of the ambient space. 
   \param ambient The ambient space.
   \param mp The chart with the polytope to crop.

   \return TRUE if the polytope still has faces not generated by a neighboring chart (i.e.,
           the intial faces or faces generated due crop with the domain limits).
*/
boolean CutPolytope(Tparameters *pr,double *t,double r,unsigned int id,void *wcs,void *c,
		    unsigned int m,unsigned int *tp,Tbox *ambient,Tcpolytope *mp);

/** 
   \brief Cuts a polytope with a given plane.

   This is the generic function cutting a polytope by a plane that can come
   from the intersection of two balls or from anywhere else.

   The plane is given in the form
    \f[ offset+\sum_{i=1}^{k} x_i t_i \leq 0 \f]
   where the \f$ t_i \f$ are given in \e t, the \f$ x_i \f$ are the variables
   in the tangent space, and  \f$ k \f$ is the dimension of this space.

   \param pr The set of parameters.
   \param t Parameters of the plane.
   \param offset Offset of the plane.
   \param id Identifier of the chart generating the cut. This is used to
             update the list of neighbours.
   \param wcs The equations defining the problem at hand.
   \param c Pointer to the chart.
   \param m The dimensionality of the ambient space.
   \param tp The topology of the ambient space. 
   \param ambient The ambient space.
   \param mp The chart with the polytope to crop.

   \return TRUE if the polytope still has faces not generated by a neighboring chart (i.e.,
           the intial faces or faces generated due crop with the domain limits).
*/
boolean CutPolytopeWithFace(Tparameters *pr,double *t,double offset,unsigned int id,void *wcs,
			    void *c,unsigned int m,unsigned int *tp,Tbox *ambient,Tcpolytope *mp);

/** 
   \brief Computes the center of the polytope.

   Computes the center of the polytope.
    
   \param t Space to store the center.
   \param mp The chart with the polytope to use.
*/
void PolytopeCenter(double *t,Tcpolytope *mp);

/** 
   \brief Identifies points inside a chart polytope.

   Decides wheter or not a point in inside the polytope bounding a chart.
   
   \param t The point.
   \param mp The polytope.
   
   \return TRUE point \e t is inside the polytope of chart \e mp.
*/
boolean InsidePolytope(double *t,Tcpolytope *mp);


/** 
   \brief Returns the simple polytope radius.

   Returns the radious of the ball included in the initial polytope.

   \param mp The simple polytope to query.

   \return The radius.
*/
double GetPolytopeRadius(Tcpolytope *mp);

/** 
   \brief Returns the simple polytope dimensionality.

   Returns the dimensionality of the space where the simple polytope is defined.

   \param mp The simple polytope to query.

   \return The dimensionality.
*/
unsigned int GetPolytopeDim(Tcpolytope *mp);

/** 
   \brief Returns the simple polytope bounding box.

   Returns the axis aligned box bounding the polytope.

   \param mp The simple polytope to query.

   \return The bounding box.
*/
Tbox *GetPolytopeBB(Tcpolytope *mp);

/** 
   \brief Modifies the bounding box of the polytope.

   Sets a new bounding box for the polytope. 
   Use carefully since a wrong bounding box could render
   the polytope inconsitent/useless.

   \param bb The new bounding box.
   \param mp The simple polytope to change.
*/
void SetPolytopeBB(Tbox *bb,Tcpolytope *mp);


/** 
   \brief Identifies polytopes not fully bounded.

   Checks if a polytope has vertices that can be sued to expand it, i.e.,
   to generate a new neighbour.

   \param mp The polytope to query.

   \return TRUE if the polytope still has vertices outside the ball.
*/
boolean ExpandiblePolytope(Tcpolytope *mp);

/** 
   \brief Mark a vertex as wrong.

   If we tried to extend a chart towards a selected vertex and we could
   not do it, we mark the corner as problematic and avoid using it
   for future chart extensions.
   This is no an issue as far as the whole manifold can be covered
   in many ways.

   \param nv The vertex to mark
   \param mp The polytope.
*/
void WrongPolytopeCorner(unsigned int nv,Tcpolytope *mp);

/** 
   \brief Returns a point inside the ball and the polytope.

    Returns a point inside the ball and the polytope. This point is
    used to define lines to external polytope corners that crosses
    the ball.

    \param rSample The radiuos of the ball. It can be smaller than
                   the initial one.
    \param t Space to store the interal point.
    \param mp The chart with the polytope.

    \return TRUE if the internal point can actually be computed.
*/
boolean GetPolytopeInteriorPoint(double rSample,double *t,Tcpolytope *mp);

/** 
   \brief Random point on the boundary from the polytope vetices.

   Returns a point on the ball selecting one of the external
   polytope vertices at random and connecting this vertex and
   the center of the ball.
   These points are typically in the border of expansion of the
   manifold discretization (i.e., good candidates for expansion).

   \param rSample Radious to use in the sampling. This is typically the radius
                 of the ball initially inside the polytope but it can be smaller
		 if many attempts to sample points fail.
   \param rand TRUE if the external corner has to be selected at random from all
               external ones of FALSE if we have to just pick the first one.
   \param nv The identifier of the selected vertex.
   \param t The output point on the chart ball boundary (if any)
   \param mp The polytope to sample.

   \return TRUE if the sampled point is actually on the boundary of the chart.
*/
boolean PolytopeBoundaryPointFromExternalCorner(double rSample,boolean rand,
						unsigned int *nv,double *t,Tcpolytope *mp);


/** 
   \brief Points on boundary from all the polytope vertexes.

   Generates all the possible points on the boundary from the polytope vertexes
   out of the ball with radius \e rSample.

   \param rSample The radius to determine if a polytope vertex is internal or external.
   \param n Number of generated points.
   \param nv Identifier of the vertex used to generate each point. The space is allocated
             internally but must be deallocated by the caller.
   \param t The generated points.The space is allocated
             internally but must be deallocated by the caller.
   \param mp The polytope.
*/
void PolytopeBoundaryPointsFromExternalCorners(double rSample,unsigned int *n,unsigned int **nv,
					       double ***t,Tcpolytope *mp);

/** 
   \brief Random point on the boundary of the chart.

   Returns a random point uniformly distributed in the boundary of
   the hypersphere defined in the tangent space.
   
   After sampling the point we check if it is actually outside the
   neighbouring charts. The border with the neighbouring charts are defined
   by the faces used to cut the polytope bounding the ball (see
   \ref IntersectCharts).

   Charts that are basically sorounded by neighbours and only have a
   small portion of its ball in the border or expansion of the manifold
   could be arbitrarily hard to sample.

   It is not allowed to sample interior charts (see \ref ExpandibleChart).

   \param rSample Radious to use in the sampling. This is typically the radius
                 of the ball initially inside the polytope but it can be smaller
		 if many attempts to sample points fail.
   \param t The output point on the chart ball boundary (if any)
   \param mp The polytope to sample.

   \return TRUE if the sampled point is actually on the boundary of the
           atlas.
*/
boolean PolytopeRandomPointOnBoundary(double rSample,double *t,Tcpolytope *mp);

/** 
   \brief Random point on the polytope with uniform distribution.

   Drawns a random point inside the polytope with uniform distribution.
   Rejection sampling is used so for some degenerate polytopes it can
   take long.
   
   \param t The array where to store the sample (must be allocated externally).
   \param mp The polytope to sample.

   \return TRUE if we could actually sample inside the polytope.
 */
boolean RandomPointInPolytope(double *t,Tcpolytope *mp);

/** 
    \brief Maximum volume of the polytope.

    Upper bound of the volume of the polytope.

    This is basically the volume of the area where \ref RandomPointInPolytope
    uses to generate random points.

    \param mp The polytope to measure.

    \return The polytope maximum volume.
*/
double PolytopeMaxVolume(Tcpolytope *mp);

/** 
   \brief Polytope volume.

   Returns an estimation of the polytope volume. Initially the estimation
   is tight but as the polytope is cut with new hyperplanes we estimate the
   volume via sampling.

   \param mp The polytope to query.

   \return The volume estimation.
*/
double PolytopeVolume(Tcpolytope *mp);

/** 
   \brief Number of neighbours of the polytope.

   Returns the number of neighbours of a polytope. The neighbours of a polytope
   are those detected when intersecting polytopes (see \ref CutPolytope).
   This only include neighbours with similar tangent spaces (not neighbours
   across singularities).

   Note that the neighbouring management is implemented in a way that is 
   slow for query but constant time for update. This is so since we want
   to optimize the construction of the atlas and not its query.

   Not that for charts at the border of the ambient space, this number might
   include "virtual" neighbours given by the intersection with the ambient
   limits. Thses "virtual" neighbours have NO_UINT as identifier 
   (see \ref PolytopeNeighbourID).

   \param mp The polytope to query.
   
   \return The numbe of neighbours of the polytope.
*/
unsigned int PolytopeNumNeighbours(Tcpolytope *mp);

/** 
   \brief Returns the identifier of one of the neighbours of a polytope.

   Returns the identifier of one of the neighbours of a polytope. This 
   includes only neighbours with similar tangent spaces (neighbours in
   the same aspect of the manifold)

   \param n The number  of neighbour to query (numbered from 0).
   \param mp The chart to query.

   \return The neighbour identifer. \ref NO_UINT if \e i is larger than
           the actual number of neighbours of the polytope of if the
	   requested neighbour is not defined.
*/
unsigned int PolytopeNeighbourID(unsigned int n,Tcpolytope *mp);

/** 
   \brief Gets the set of vertices of the polytope.

   Returns the set of vertices of the polytope.

   \param k The dimension of the vertices. Can be larger than the
            internal dimension due to the presence of kino-constraints.
   \param nv The number of vertices returned.
   \param v The set of vertices (allocated internally). If the polytope 
            has no vertices \e v is set to NULL.
   \param mp The polytope to query.
 */
void GetPolytopeVertices(unsigned int k,unsigned int *nv,double ***v,Tcpolytope *mp);

/** 
   \brief Identifiy the three charts coincident at a vertex.

   For bidimensional manifold, we identify the two neighbouring charts coincident
   for each vertex. These two charts together with the current chart form one
   of the triangles of the triangulation of the atlas.

   \param nv Number of vertices.
   \param cID1 For each vertex, the identifier of the chart neighbouring by one of
               the two edges defining this vertex. The space for this array is allocated
	       internally.
   \param cID2 For each vertex, the identifier of the chart neighbouring by other
               edge defining this vertex. The space for this array is allocated
	       internally.
   \param mp The polytope to query.
*/
void GetPolytopeNeighboursFromVertices(unsigned int *nv,unsigned int **cID1,unsigned int **cID2,Tcpolytope *mp);

/** 
   \brief Gets the set of edges of the polytope.

   Returns the set of edges of the polytope.
   
   Edges are returned as pairs of identifiers of vertices. The identifers correspond
   to the edges are returned by \ref GetPolytopeVertices.

   \param ne The number of edges returned.
   \param vID1 The identifier of the first point for each edge (allocated internally).
   \param vID2 The identifier of the second point for each edge (allocated internally).
   \param mp The polytope to query.
 */
void GetPolytopeEdges(unsigned int *ne,unsigned int **vID1,unsigned int **vID2,
		      Tcpolytope *mp);


/** 
    \brief Computes the memory used by the polytope.

    Computes the approximated memory used by the polytope (in bytes).

    \param mp The polytope.

    \return The number of bytes used.
*/
unsigned int PolytopeMemSize(Tcpolytope *mp);

/** 
   \brief Saves the chart polytope to a file.

   Saves the information about the chart polytope (if any) to a given
   file.
   
   \param f The file where to store the polytope information.
   \param mp The chart with the polytope to save.
*/
void SavePolytope(FILE *f,Tcpolytope *mp);

/** 
   \brief Reads the chart polytope from a file.

   Initializes the information about the chart polytope (if any) from a given
   file.
   
   \param f The file from where to read the polytope information.
   \param mp The chart with the polytope to initialize.
*/
void LoadPolytope(FILE *f,Tcpolytope *mp);

/** 
   \brief Prints information about the polytope.

   Prints some debugging information about the polytope.
*/
void PrintPolytopeInfo(Tcpolytope *mp);

/** 
   \brief Deletes the structure allocated by \ref DefinePolytope.

   Deletes the structure allocated by \ref DefinePolytope. 

   \param mp The polytope to free.
*/
void DeletePolytope(Tcpolytope *mp);

#endif
