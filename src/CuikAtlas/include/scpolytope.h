#ifndef SCPOLYTOPE
#define SCPOLYTOPE

#include "boolean.h"
#include "box.h"

/** 
   \brief (De)activates the generation of half planes.

   Activates/Deactivates the generation of half planes.
   This is used for testing/debugging.
*/
#define HALF_PLANES 1

/** 
   \brief (De)activates the use of the half planes when sampling.

   Activates/Deactivates the use of the half planes when generating
   random samples.

   This is used for testing/debugging.
*/
#define RANDOM_HALF_PLANES 1

/** 
   \file scpolytope.h
   \brief Definition of a smple polytope associated to a chart.

   Simplified version of a polytope associated with a chart.
   To see the full version check \ref cpolytope.h.

   \sa Tscpolytope,scpolytope.c
*/

/** 
   \brief Initial space for faces.

   Initial space for faces. Extended as much as necessary.
*/
#define INIT_NUM_FACES 10

/** 
   \brief A simplified polytope associated with chart on a manifold.
   
   The area of influence of a chart is bounded by a polytope. In this case
   the polytope is bounded by a set of faces but no vertex is explicitlly 
   stored. This way we save memory and complexity.
   The drawback is that we have to store all the faces defining the polytope
   (we can not detect useless faces) and the bounding boxes are less tight.
   Moreover all the charts that at any point intersected with the current chart
   will be keept as neighbours, even if from a given time they are no 
   neighbours any more.
   One solution for this is to define a full Tpolytope (this has vertices and
   a minimum set of faces) from the simple polytope and then keep the surviving
   faces and the tighter bounding box.

   The simple polytope is only usefull in the AtlasRRT combination.

   \todo Implement the conversions between Tpolytope and Tspolytope.

   \sa chart.h,chart.c.
*/
typedef struct {
  unsigned int k;   /**< Dimension of the feasible velocity space. Can be 
		         lower than the dimension of the manifold in the presence
		         of kino-constraints. If so, the 'k' here is lower
		         than the 'k' in the corresponding chart. Parameter
		         here only use the first components of the tangent space
		         (the rest, used in chart. are assumed to be zero). */
  double r;         /**< Radius around \e p (in tangent space) where the linearization 
		         holds. */
  double sr;        /**< Current sampling radius. */
  double lsr;       /**< Lower bound for the sampling radius. This minimum ensures that the
		         sampling area always includes the applicability area of a chart. 
		         This ensures probabilistic completeness. */
  double msr;       /**< Upper bound for the sampling radius. */
  double v;         /**< Volume, */

  unsigned int nFaces;       /**< Num faces defining the polytope so far. */
  unsigned int maxFaces;     /**< Space for faces */
  double **face;             /**< Parameters of the faces defining the polytope */

  unsigned int *ID;          /**< Identifiers of the neighbouring charts (one per face). */
} Tscpolytope;


/** 
   \brief Defines an empty chart simplieifed polytope.

   Defines an empty chart simplified polytope.

   \param delta Distance between two samples. We must ensure outher ball
                larger than this so that new samples can eventually trigger the
 	        generation of new charts.
   \param k Dimensinality of the space where to define the polytope.
   \param r Radius of the ball to be enclosed by the polytope.
   \param sr Sampling radius.
   \param mp The simple polytope to initialize.

   \sa InitEmptyCharPolytope.
*/
void InitEmptySPolytope(double delta,unsigned int k,double r,double sr,Tscpolytope *mp);

/** 
   \brief Initial definition of the simple polytope bounding the local chart.

   Defines a box.

   \param mp The polytope to initialize.

   \sa DefineChartPolytope.
*/
void DefineSPolytope(Tscpolytope *mp);

/** 
   \brief Copies the simplified polytope from one chart to another.

   Copies the data defining the simple polytope from one chart to another.

   \param mp_dst The simple polytope where to copy the information.
   \param mp_src The simple polytope from where to copy the information.

   \sa CopyChartPolytope.
*/
void CopySPolytope(Tscpolytope *mp_dst,Tscpolytope *mp_src);

/** 
   \brief Crops the polytope bounding chart with a plane.

   Reduces a polytope bounding chart cropping it with a plane defined
   by the intersection of the chart ball with a ball centered at \e t
   with radious \e r. This ball is an approximation in the chart plane
   of the ball bounding another chart.

   \param t Center of the new ball.
   \param r Radius of the new ball.  This is typically the same as the ball
            for the current polytope.
   \param id Identifier of the chart generating the cut. This is used to
             update the list of neighbours.
   \param mp The chart with the polytope to crop.

   \sa CutPolytope.
*/
void CutSPolytope(double *t,double r,unsigned int id,Tscpolytope *mp);

/** 
   \brief Cuts a simple polytope with a given plane.

   This is the generic function cutting a simple polytope by a plane that can come
   from the intersection of two balls or from anywhere else.

   The plane is given in the form
    \f[ offset+\sum_{i=1}^{k} x_i t_i \leq 0 \f]
   where the \f$ t_i \f$ are given in \e t, the \f$ x_i \f$ are the variables
   in the tangent space, and  \f$ k \f$ is the dimension of this space.

   We simply add the face to the set of faces implicitly defining the polytope.

   \param t Parameters of the plane.
   \param offset Offset of the plane.
   \param id Identifier of the chart generating the cut. This is used to
             update the list of neighbours.
   \param mp The chart with the polytope to crop.

   \sa CutPolytopeWithFace.
*/
void CutSPolytopeWithFace(double *t,double offset,unsigned int id,Tscpolytope *mp);


/** 
   \brief Identifies points inside a chart simple polytope.

   Decides wheter or not a point in inside the simple polytope bounding a chart.
   
   \param t The point.
   \param mp The polytope.
   
   \return TRUE point \e t is inside the simple polytope of chart \e mp.
   
   \sa InsidePolytope.
*/
boolean InsideSPolytope(double *t,Tscpolytope *mp);

/** 
   \brief Identifes the neighbour containing a given point.

   This function returns the neighbouring chart including
   a point in the polytope radious but outside the polytope.

   For points outside the chart ball or inside the polytope this
   function returns \ref NO_UINT.

   \param epsilon Numerical accuracy.
   \param t The point.
   \param mp The poytope.
*/
unsigned int DetermineSPolytopeNeighbour(double epsilon,double *t,Tscpolytope *mp);

/** 
   \brief Ensures that a polytompe includes a given point.

   Ensures that a polytope includes a given point possibly modifying the
   faces.

   \param t The point.
   \param mp The polytope.
*/
void EnlargeSPolytope(double *t,Tscpolytope *mp);

/** 
   \brief Returns the simple polytope radius.

   Returns the radious of the ball included in the initial polytope.

   \param mp The simple polytope to query.

   \return The radius.
*/
double GetSPolytopeRadius(Tscpolytope *mp);

/** 
   \brief Returns the size of the box side.

   Simple convex polytopes have an enclosing ball.
   This function returns the side of a box fully
   enclosing ths enclosing ball. This is basically used for
   plotting purposes. 

   \todo Frontier charts should be represented by balls and 
         not by boxes.

   \param mp The simple polytope to query.

   \return The box side.
*/
double GetSPolytopeBoxSide(Tscpolytope *mp);

/** 
   \brief Returns the simple polytope dimensionality.

   Returns the dimensionality of the space where the simple polytope is defined.

   \param mp The simple polytope to query.

   \return The dimensionality.
*/
unsigned int GetSPolytopeDim(Tscpolytope *mp);

/** 
   \brief Number of faces of a simple chart polytope.

   Returns the number of faces of a simple chart polytope.

   \param mp The simple polytope to query.
   
   \return The number of faces.
*/
unsigned int GetSPolytopeNFaces(Tscpolytope *mp);

/** 
   \brief Gets a face.

   Returns the coeficients defining the face for a simple polytope
   associated to a chart.

   If \e n is above the number of faces of the polytope, nothing
   is changed in \e f.

   \param n The face number.
   \param f Space where to store the face coefients (including the offest).
            It must have \e k+1 entries and must be allocated externally.
   \param mp The simple polytope to query.
*/
void GetSPolytopeFace(unsigned int n,double *f,Tscpolytope *mp);

/** 
   \brief Random point on the boundary of the chart.

   Returns a random point uniformly distributed in the boundary of
   the hypersphere defined in the tangent space.
   
   After sampling the point we check if it is actually inside the polytope.

   Charts that are basically sorounded by neighbours and only have a
   small portion of its ball in the border or expansion of the manifold
   could be arbitrarily hard to sample.

   \param rSample Radious to use in the sampling. This is typically the radius
                 of the ball initially inside the polytope but it can be smaller
		 if many attempts to sample points fail.
   \param t The output point on the chart ball boundary (if any)
   \param mp The polytope to sample.

   \return TRUE if the sampled point is actually on the boundary of the
           atlas.
*/
boolean SPolytopeRandomPointOnBoundary(double rSample,double *t,Tscpolytope *mp);

/** 
   \brief Random point on the polytope with uniform distribution.

   Drawns a random point inside the polytope with uniform distribution.
   Rejection sampling is used so for some degenerate polytopes it can
   take long.
   
   \param scale Scale factor for the sampling area.
   \param t The array where to store the sample (must be allocated externally).
   \param mp The polytope to sample.
   
   \return TRUE if we could actually sample inside the simple polytope.

   \sa RandomPointInPolytope.
 */
boolean RandomPointInSPolytope(double scale,double *t,Tscpolytope *mp);

/** 
    \brief Returns the current sampling radius.

    Returns the current sampling radius.

    \param mp The simple polytope to query.
    
    \return The sampling radius.
*/
double SPolytopeGetSamplingRadius(Tscpolytope *mp);

/** 
    \brief Increases the sampling radius.

    Increases the sampling radius after a succesful sampling or a succesful 
    branch extension. The aim here is to try to reach further, if possible.
    
    When extending the sampling radious we keep track of the
    maximum sampling radius ever. All samples belonging to the polytope
    can not be further than this maximum from the center.

    \param mp The simple polytope to adjust.
*/
void SPolytopeIncreaseSamplingRadius(Tscpolytope *mp);

/** 
    \brief Decreases the sampling radious
    
    Decreases the sampling radious after an unsuceessful sampling or
    a collisiong when trying the create a new branch.

    When decresing the sampling radius we take care of not
    reducing it below a given threshold so that it is always
    significantly larger than the radius r.
*/
void SPolytopeDecreaseSamplingRadius(Tscpolytope *mp);

/** 
    \brief Maximum volume of the simple polytope.

    Upper bound of the volume of the polytope.
    
    This is basically the area that \ref RandomPointInSPolytope 
    uses to drawn random samples.

    \param mp The polytope to measure.

    \return The polytope maximum volume.
*/
double SPolytopeMaxVolume(Tscpolytope *mp);

/** 
    \brief Volume of the simple polytope.

    Volume of the simple polytope considering the
    neighbouring relations (i.e., initial volume or maximum
    volume)

    \param mp The polytope to measure.

    \return The polytope volume.
    
*/
double SPolytopeVolume(Tscpolytope *mp);

/** 
   \brief Number of neighbours of the simple polytope.

   Returns the number of neighbours of a polytope. 
   Note that a simple polytope can consider as neighbours charts
   that where neighbours but are not neighbours any more.

   \param mp The simple polytope to query.
   
   \return The numbe of neighbours of the simple polytope.

   \sa PolytopeNumNeighbours.
*/
unsigned int SPolytopeNumNeighbours(Tscpolytope *mp);

/** 
   \brief Returns the identifier of one of the neighbours of a polytope.

   Returns the identifier of one of the neighbours of a polytope. 
   Note that a simple polytope can consider as neighbours charts
   that where neighbours but are not neighbours any more.

   \param n The number  of neighbour to query (numbered from 0).
   \param mp The chart to query.

   \return The neighbour identifer. \ref NO_UINT if \e i is larger thatn
           the actual number of neighbours of the polytope.

   \sa PolytopeNeighbourID.
*/
unsigned int SPolytopeNeighbourID(unsigned int n,Tscpolytope *mp);

/** 
    \brief Computes the memory used by the polytope.

    Computes the approximated memory used by the polytope (in bytes).

    \param mp The polytope.

    \return The number of bytes used.
*/
unsigned int SPolytopeMemSize(Tscpolytope *mp);

/** 
   \brief Saves the chart polytope to a file.

   Saves the information about the chart simple polytope (if any) to a given
   file.
   
   \param f The file where to store the polytope information.
   \param mp The chart with the polytope to save.

   \sa SaveChartPolytope.
*/
void SaveSPolytope(FILE *f,Tscpolytope *mp);

/** 
   \brief Reads the chart polytope from a file.

   Initializes the information about the chart polytope (if any) from a given
   file.
   
   \param f The file from where to read the polytope information.
   \param mp The chart with the polytope to initialize.

   \sa LoadChartPolytope.
*/
void LoadSPolytope(FILE *f,Tscpolytope *mp);

/** 
   \brief Deletes the structure allocated by \ref DefineSPolytope.

   Deletes the structure allocated by \ref DefineSPolytope. 

   \param mp The polytope to free.

   \sa DeleteChartPolytope.
*/
void DeleteSPolytope(Tscpolytope *mp);

#endif
