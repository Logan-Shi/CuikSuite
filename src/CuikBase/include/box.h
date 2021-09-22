#ifndef BOXH
#define BOXH

#include "interval.h"
#include "boolean.h"
#include "variable_set.h"
#include "vector.h"

#include <stdio.h>


/** \file box.h
    \brief Definition of the Tbox type and the associated functions.

    Definition of the Tbox type and the associated functions.

    \sa Tbox, box.c.
*/

/************************************************************************************/
/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. The box includes no solution.        
*/
#define EMPTY_BOX                 0

/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. The simplex process trigered and
    error.   
*/
#define ERROR_IN_PROCESS          1

/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. The box reduced.
*/
#define REDUCED_BOX               2

/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. 
    The range that we are trying to reduce can not be bounded.
*/
#define UNBOUNDED_BOX             3

/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. The box reduced and is validated
    to include a solution.
*/
#define REDUCED_BOX_WITH_SOLUTION 4

/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. The box did not significatively
    reduced.
*/
#define NOT_REDUCED_BOX           5

/** \brief One of the possible results of reducing a box.

    One of the possible results of reducing a box. 
*/
#define BOX_OK                    6
/************************************************************************************/

/** 
 \brief A box.

 A box is a <em>n</em>-dimensional orthotope, i.e., a vector of intervals delimiting a subset of the
 seach space. The whole search space (i.e., the largest possible box) is defined from the ranges 
 of the variables. ReduceBox operations shrink boxes and bisection operations
 create new boxes.<br>
 The initial box has level 1. Boxes created via bisection of a box of level <em>m</em> have
 level <em>m+1</em>. Thus, the level of a box is a measure of how deep it is in the search
 tree explored by <b>cuik</b>. This level is printed in the normal output of <b>cuik</b>. 
 If the average level of boxes that become empty or solutions are above, say 25, there are
 few chances for the problem to be solved in finite time.

 \sa box.h
*/
typedef struct {
  unsigned int level; /**< Number of bisections applied to create this box. Also level of the search tree at which this box is created. */
  unsigned int n; /**< Number of dimensions of the box. */
  Tinterval *is; /**< Set of intervals that define the box. One interval per dimension. */
} Tbox;

/** 
    \brief Initializes a box.

    Creates a new box with the given parameters.

    \param dim Dimension of the new box (i.e., number of intervals).
    \param is Vector of intervals used to initilize the new box. If the pointer is NULL
              the box intervals are set to [0,0].
    \param b The box to initialize.
*/
void InitBox(unsigned int dim,Tinterval *is,Tbox *b);

/** 
    \brief Initializes a box from a point.
 
    Creates a new box with punctual intervals from a given vector.

    \param dim Dimension of the new box (i.e., number of intervals).
    \param p The point to use to initialize the box.
    \param b The box to initialize.
*/
void InitBoxFromPoint(unsigned int dim,double *p,Tbox *b);

/** 
    \brief Enlarges all the intervals of a box.

    Enlarges all the intervals of the box by substracting/adding
    a given value to their lower/upper limits.

    \param lo The offset to add to all interval lower limits.
    \param uo The offset to add to all interval upper limits.
    \param b The box to modify.

    \sa EnlargeInterval.
*/
void EnlargeBox(double lo,double uo,Tbox *b);

/** 
    \brief Expands a box so that it includes a given point.

    Expands a box so that it includes a given point.

    \param p The point.
    \param b The box to modify.

    \sa ExpandInterval.
*/
void ExpandBox(double *p,Tbox *b);

/** 
    \brief Returns the size of a box when converted to an array of doubles.

    In a multiprocessors system, the master and the slave processors exchange boxes and they
    do so by converting boxes into arrays of doubles. This function returns the number
    of doubles that takes a box when converted to into doubles. Typically, in the array
    of doubles we store some heading information plus the lower and upper limits for each
    one of the intervals in the box.

    \param b The box to convert to an array of doubles.
    \return The number of doubles that the box conversion will use.

    \sa Box2Buffer, Buffer2Box
*/ 
unsigned int GetBoxBufferSize(Tbox *b); 

/** 
    \brief Converts a box into an array of doubles.

    Packs a box into an array of doubles and adds some heading information to the array.

    \param c Status information related to the box (EMPTY_BOX, REDUCED_BOX, etc.).
    \param n Process information related to the box. Right now this is used to store
             the number of time a box is reduced in a slave processors before it is returned to the
	     master processors. The master collects this informations into a global statistics.
    \param buffer The buffer of doubles where the box is to be stored. The size of this
                  buffer should be, at least, the number returned by GetBoxBufferSize.
    \param b The box to convert to an array of doubles.

    \sa GetBoxBufferSize
*/
void Box2Buffer(unsigned int c,unsigned int n,double *buffer,Tbox *b);

/** 
    \brief Converts a buffer of doubles into a box.

    Converts an array of doubles into a box.

    This is \b not a box constructor. The box is to be initialized before calling
    this function and if the box size and the buffer size do not match this
    function will trigger an error. The idea is to convert a box into a buffer, send
    it to slave processor, and then update the box with the information sent by the
    slave.

    \param c Recovers the box status (EMPTY_BOX, REDUCED_BOX, etc.) from the buffer.
    \param n Recovers process information related to the box. Right now it returns the
             number box reductions applied in the slave processors in order to crop the box.
    \param buffer The buffer from which the box is to be defined.
    \param b The output box.

    \sa GetBoxBufferSize
*/
void Buffer2Box(unsigned int *c,unsigned int *n,double *buffer,Tbox *b);

/** 
    \brief Box copy operator.

    Copies one box into another. This is a copy constructor and, therefore, the
    output box is initialized inside the CopyBox (i.e., there is no need to
    init the box beforehand). 
    <br>
    The parameters are given as a void pointers to define a generic copy function
    that is used in box list or box vectors.

    \param b_out Output box. Box constructed by the copy.
    \param b_in Input box. Box used to create b_out.

*/
void CopyBox(void *b_out,void *b_in);

/** 
   \brief Concats two boxes.

   Defines a box as a concatenation of two boxes.

   \param b1 The first box to concat.
   \param b2 The second box to concat.
   \param bout The box to be created.
*/
void MergeBoxes(Tbox *b1,Tbox *b2,Tbox *bout);

/** 
    \brief Creates a box from a sub-set of a given box.

    This is a constructor that builds a box form a subset of intervals
    of a given box.<br>
    The parameters are given as a void pointers to define a generic copy function
    that is used in box list or box vectors.

    \param used Array of booleans, one for each interval of the input box (b_in). If the
                boolean is TRUE, the corresponding interval is used in the selective copy.
		If the given pointer is NULL, all intervals are used (i.e., in this case
		CopyBoxSubset is the same as CopyBox).
    \param b_out Output box. Box constructed by the copy.
    \param b_in Input box. Box used to create b_out.

*/
void CopyBoxSubset(boolean *used,void *b_out,void *b_in);

/** 
    \brief Changes a sub-set of ranges in a given box.

    Replaces the ranges selected by the flags \e used of box \b
    by the ranges in box \e bset.
    Box \e bset only need to have as many ranges as flags to TRUE
    in \e used but the array of flags need as many entries as
    elements in \e b.

    \param used Array of booleans, one for each interval of the input box (b_in). If the
                boolean is TRUE, the corresponding interval is used in the selective copy.
		If the given pointer is NULL, all intervals are used (i.e., in this case
		CopyBoxSubset is the same as CopyBox).
    \param bset The box with the new sub-set of ranges.
    \param b The box to modify.
*/
void SetBoxSubset(boolean *used,Tbox *bset,Tbox *b);

/** 
    \brief Replaces the box intervals with a new set.

    Replaces the box intervals with a new set of intervals.

    \param is Array with the new set of intervals. The array must
    have as many elements as those in the box, otherwise the effect
    of SetBoxIntervals is undefined.
    \param b The box to be modified.

*/
void SetBoxIntervals(Tinterval *is,Tbox *b);


/** 
    \brief Replaces a particular interval in a box.

    Replaces a particular interval in a box by the given one.

    \param n The index of the interval to replace.
    \param is The new interval.
    \param b The box to be modified.

*/
void SetBoxInterval(unsigned int n,Tinterval *is,Tbox *b);


/** 
    \brief Computes the box intersection of two given boxes.

    The intersection of two boxes is a box (possibly empty). This function
    computes the intersection of two given boxes, along a sub-set
    of its intervals.<br>
    The two input boxes must have the same dimensionality.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the intersection.
		The non-used intervals are undefined in the output. 
		If the given pointer is NULL, all intervals are used.
    \param b1 The first box to be intersected.
    \param b2 The second box to be intersected.
    \param bout The box resulting from the intersection.

    \return Returns TRUE if the boxes actually intersect (i.e., if the output box
            is not empty).
	   
    \sa Intersection

*/
boolean BoxesIntersection(boolean *used,Tbox *b1,Tbox *b2,Tbox *bout);

/** 
    \brief Computes the box union of two given boxes.

    The union of two boxes is a box. This function
    computes the union of two given boxes, along a sub-set
    of its intervals.<br>
    The two input boxes must have the same dimensionality.<br>
    Note that the union of two boxes is never empty (if the input boxes are not
    empty).

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the intersection.
	        The non-used intervals are undefined in the output. 
	        If the given pointer is NULL, all intervals are used.
    \param b1 The first box to be intersected.
    \param b2 The second box to be intersected.
    \param b_out The box resulting from the intersection.

    \sa Union

*/
void BoxUnion(boolean *used,Tbox *b1,Tbox *b2,Tbox *b_out);


/** 
   \brief Forces a point to be inside a box.

   Checks if a point is inside a box and, if not, it changes
   the point coordinates to enforce the point to be in the box.
   
   \param used Array of booleans, one for each interval of the input boxes. If the
               boolean is TRUE, the corresponding interval is used in the check.
               If the given pointer is NULL, all intervals are used.
   \param n The size of the point.
   \param p The point.
   \param b The box.
*/
void Crop2Box(boolean *used,unsigned int n,double *p,Tbox *b);

/** 
    \brief Checks if a point is included in a(sub-) box.

    Checks if a point (defined by an array of <em>n</em> doubles) is included
    in a box. <br>

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the check.
	        If the given pointer is NULL, all intervals are used.
    \param n Length of the array of doubles. It must be the same as the box dimensionality.
    \param v The array of doubles defining the point.
    \param tol Tolerance in the comparison.
    \param b The box.

    \return TRUE if the point is inside the(sub-)box.

*/
boolean PointInBox(boolean *used,unsigned int n,double *v,double tol,Tbox *b);

/** 
    \brief Checks if a point is included in a(sub-) box.

    Checks if a point (defined by an array of <em>n</em> doubles) is included
    in a box taking into accont the topology of each variable.

    If the point can be made to enter the box by adjusting the angular 
    variables (adding/substracting 2*pi), the given point (v) is modified
    and at the end of the function it contains the values tha make
    the point to be inside the box.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the check.
	        If the given pointer is NULL, all intervals are used.
    \param update TRUE if the input point has to be updated using the topology.
    \param n Length of the array of doubles. It must be the same as the box dimensionality.
    \param v The array of doubles defining the point.
    \param tol Tolerance in the comparison.
    \param tp The topology for each variable.
    \param b The box.

    \return TRUE if the point is inside the (sub-)box.

*/
boolean PointInBoxTopology(boolean *used,boolean update,
			   unsigned int n,double *v,double tol,unsigned int *tp,Tbox *b);

/** 
    \brief Determines the violated box limit.

    For a point aut of the box, we determine the dimension for which the point
    is out of the box.
    
    We assume that the point is out of the box only in one of the dimensions. This
    is typically the case when tracing rays from inside the box to out of the box, where
    the point out of the box is acurately located via dichotomics search.

    \param used  Array of booleans, one for each interval of the input boxes. If the
                 boolean is TRUE, the corresponding interval is used in the check.
	         If the given pointer is NULL, all intervals are used.
    \param n Length of the array of doubles. It must be the same as the box dimensionality.
    \param v The array of doubles defining the point.    
    \param tp The topology for each variable.
    \param s [Output] -1 if the lower limit of the interval is violated and +1 if the upper
             limit is violated.
    \param b The box.

    \return The dimension along which the point is out of the box.
*/
unsigned int OutOfBoxTopology(boolean *used,unsigned int n,double *v,
			      unsigned int *tp,signed int *s,Tbox *b);

/** 
    \brief Checks if a point is included in a (sub-)box.

    Checks if a point (defined by an array of doubles) is included
    in a (sub-)box. The (sub-)box is selected using an array of flags.<br>
    The difference with PointInBox is that <em>v</em> only need to include
    as many elements as TRUE elements in the <em>used</em> array. Moreover,
    here the point is defined as a <em>Tvector</em> and not as an array of
    doubles. The <em>Tvector</em> is used to facilitate the queries from the
    sample structures that store the configurations in the form of vectors.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the check.
		If the given pointer is NULL, all intervals are used.
    \param v The vector defining the point.
    \param tol Tolerance in the comparisons.
    \param b The box.

    \return TRUE if the point is inside the (sub-)box.

    \sa PointInBox, Tvector, Tsample

*/
boolean PointInSubBox(boolean *used,Tvector *v,double tol,Tbox *b);

/** 
    \brief Computes the distance from a point to the center of a
    (sub-)box.

    Computes the distance from a point to the center of a
    (sub-)box. The (sub-)box is selected using an array of flags.
    <br>
    The point is described using an vector of doubles with one entry for each
    one of the dimensions to be checked. The <em>Tvector</em> is used to facilitate 
    the queries from the sample structures that store the configurations in the form 
    of vectors.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the check.
		If the given pointer is NULL, all intervals are used.
    \param v The vector defining the point.
    \param b The box.

    \return The distance of the point to the center of the (sub-)box.

    \sa Tvector
*/
double DistanceToSubBoxCenter(boolean *used,Tvector *v,Tbox *b);

/** 
    \brief Checks if a (sub-)box is (almost) punctual.

    Returns TRUE if the input box is (amost) punctual along the selected
    dimensions. A <em>punctual</em> interval is an interval whose size
    is below <em>epsilon</em>.
    <br>

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the check.
		If the given pointer is NULL, all intervals are used.
    \param epsilon The threshold to decide when an interval is <em>punctual</em>.
    \param b The box.

    \return TRUE if the all selected ranges in the (sub-)box have size below <em>epsilon</em>.

*/
boolean IsPunctualBox(boolean *used,double epsilon,Tbox *b);

/** 
    \brief Checks if a (sub-)box is fully included in another box.

    Returns TRUE if the the first box is fully included in the second box.
    <br>

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the check.
		If the given pointer is NULL, all intervals are used.
    \param b1 The <em>small</em> box, the one to be fully sourrounded by <em>b2</em>.
    \param b2 The box that is to include <em>b1</em>.

    \return TRUE <em>b1</em> is fully included in <em>b2</em>.

*/
boolean BoxInclusion(boolean *used,Tbox *b1,Tbox *b2);


/** 
    \brief Gets the weights for distances between points in a box.

    Gets the weights that normalize the (Euclidean) distance compuation (assigns
    equal importance to all dimensions, irrespectively of their size).

    \param w The output vector of weights. Is allocated internally but must be
             deallocated externally. It will be NULL if all the weights are
	     the same.
    \param b The box.

    \return The dimension of the output vector.
*/
unsigned int GetDistanceWeightsFromBox(double **w,Tbox *b);

/** 
    \brief Returns a pointer to one of the intervals defining the box.

    Returns a pointer to the <em>n</em> interval of the box.

    \param n The interval to retrive.
    \param b The box.

    \return A pointer to the required interval or NULL if <em>n</em> is
            larger than the box dimensionality.<br>
	    Note that we give access directly to the box internal structures.
	    This allow to directly modify the interval. If you <em>free</em>
	    the pointer, the behavior will be undefined.
*/
Tinterval *GetBoxInterval(unsigned int n,Tbox *b);

/** 
    \brief Returns a pointer to the array of intervals defining the box.

    Returns a pointer to the intervals defining the box. This allows fast
    access to the whole set of intervals of the box, i.e., we do not have
    to access them one at a time.<br>

    \param b The box.

    \return A pointer to the array of intervals.<br>
	    Note that we give access directly to the box internal structures.
	    This allow to directly modify the interval. If you <em>free</em>
	    the pointer, the behavior will be undefined.
*/
Tinterval *GetBoxIntervals(Tbox *b);

/** 
    \brief Computes the size of the box.

    Determines the largest box side, among the sub-set of intervals selected
    via the array of booleans <em>used</em>.
    

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b The box.
    
    \return The box size.
*/
double GetBoxSize(boolean *used,Tbox *b);

/** 
    \brief Computes the size of the box.

    Determines the largest box side, among the sub-set of variables included
    in the variable set <em>vars</em>.

    \param vars Set of variables (i.e., box dimensions) to be taken into account in 
           the computation.
    \param b The box.
    
    \return The box size.

    \sa Tvariable_set
*/
double GetBoxMaxSizeVarSet(Tvariable_set *vars,Tbox *b);

/** 
    \brief Computes the minimum size of the box.

    Determines the smallest box side, among the sub-set of variables included
    in the variable set <em>vars</em>.

    \param vars Set of variables (i.e., box dimensions) to be taken into account in 
           the computation.
    \param b The box.
    
    \return The box size.

    \sa Tvariable_set
*/
double GetBoxMinSizeVarSet(Tvariable_set *vars,Tbox *b);

/** 
    \brief Computes the diagonal of a (sub-)box.

    Determines the diagonal of a sub-box of <em>b</em> determined using
    the array <em>used</em>.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b The box.
    
    \return The (sub-)box diagonal.
*/
double GetBoxDiagonal(boolean *used,Tbox *b);

/** 
    \brief Returns the box level.

    Returns the box level, i.e., the number of bisections form the first
    box used to cretate this box.

    \param b The box.
    
    \return The box level.
*/
unsigned int GetBoxLevel(Tbox *b);

/** 
    \brief Returns the a random point along the selected dimensions.

    Computes a random point along the selected dimensions.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param c Space where to store the random point (should be allocated by the caller
             with, at least, space for the point along the selected dimensions).
    \param b The box.
*/
void RandomPointInBox(boolean *used,double *c,Tbox *b);

/** 
    \brief Returns the box center along the selected dimensions.

    Computes the box center along the selected dimensions.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param c Space where to store the center (should be allocated by the caller
             with, at least, space for the center along the selected dimensions).
    \param b The box.
*/
void GetBoxCenter(boolean *used,double *c,Tbox *b);

/** 
    \brief Computes distance between the center of two (sub-)boxes.

    Determines the distance between the cener of two  (sub-)boxes determined using
    the array <em>used</em>. 

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b1 One of the boxes.
    \param b2 The other box.
    
    \return The (sub-)box center distance.
*/
double GetBoxCenterDistance(boolean *used,Tbox *b1,Tbox *b2);

/** 
   \brief Distance from a point to a box.

   Computes the square of the minimum distance from a point to a box.

   \param t2 Threshold. Only poits closer than 't' to the box are relevant.
            Use INF if all points must be considered. Using a threshold
	    accelerates the computation. This value is a squared distance!.
   \param p The point.
   \param b The box.

   \return The minimum distance between the input parameters.

   \sa DistancePointToBox
*/
double SquaredDistancePointToBox(double t2,double *p,Tbox *b);

/** 
   \brief Distance from a point to a box.

   Computes the minimum distance from a point to a box.

   \param p The point.
   \param b The box.

   \return The minimum distance between the input parameters.

   \sa SquqredDistancePointToBox, DistanceToInterval
*/
double DistancePointToBox(double *p,Tbox *b);

/** 
   \brief Squared distance from a value to a given box dimension.

   Squared distance of a value to the interval defining a box along a given dimension.

   \param dim The dimension.
   \param p The point.
   \param tp The topology of the space where the box and the point
             are defined.
   \param b The box.

   \return The squared distance from the value to the interval.
*/
double SquaredDistanceToBoxDimensionTopology(unsigned int dim,double p,unsigned int *tp,Tbox *b);

/** 
   \brief Squared distance from a point to a box.

   Computes the minimum squared distance from a point to a box but considering
   a possible special topology for the input box and the input point.

   \param t Threshold. Only poits closer than 't' to the box are relevant.
            Use INF if all points must be considered. Using a threshold
	    accelerates the computation.
   \param p The point.
   \param tp The topology of the space where the box and the point
             are defined.
   \param b The box.

   \return The minimum distance between the input parameters.
*/
double SquaredDistancePointToBoxTopology(double t,double *p,unsigned int *tp,Tbox *b);

/** 
   \brief Distance from a point to a box.

   Computes the minimum distance from a point to a box but considering
   a possible special topology for the input box and the input point.

   \param p The point.
   \param tp The topology of the space where the box and the point
             are defined.
   \param b The box.

   \return The minimum distance between the input parameters.

   \sa SquaredDistancePointToBoxTopology
*/
double DistancePointToBoxTopology(double *p,unsigned int *tp,Tbox *b);

/** 
    \brief Computes the volume of the box.

    Determines the volume of a box (i.e., the product of the box sides), 
    for a sub-set of intervals selected via the array of booleans <em>used</em>.
    

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b The box.
    
    \return The box volume.
*/
double GetBoxVolume(boolean *used,Tbox *b);

/** 
    \brief Computes the sum of the sides of the box.

    Determines the sum of the sides of the box,
    for a sub-set of intervals selected via the array of booleans <em>used</em>.
    
    This function is used to determine if a box shrinks in any of its sides and
    it provides information even if the box is 0-size along any of its dimensions,
    while \ref GetBoxVolume does not. Intuitively, \ref GetBoxVolume corresponds
    to the determinant and \ref GetBoxSumSide to the trace of a matrix. They provide
    different norms useful for different purposes.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b The box.
    
    \return The sum of the sides.
*/
double GetBoxSumSide(boolean *used,Tbox *b);

/** 
    \brief Box dimensionality.

    Returns the box dimensionality, i.e., the number of intervals defining the box.
    
    \param b The box.
    
    \return The box dimensionality.
*/
unsigned int GetBoxNIntervals(Tbox *b);

/**     
    \brief The dimension of the (sub-)box along which the box has maximum size.

    Returns dimension of the (sub-)box along which the box has maximum size.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b The box.
    
    \return The dimension of the box with maximal size. If the box is dimension-less
            this function returns NO_UINT.
*/
unsigned int GetBoxMaxDim(boolean *used,Tbox *b);

/**     
    \brief Computes the box dimension for which it is better to split the box.

    Computes the box dimension for which it is better to split the box. Right now
    this function is an alias to GetBoxMaxDim.

    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the computations. 
		If the given pointer is NULL, all intervals are used.
    \param b The box.
    
    \return The best split dimension for the given box.

    \sa GetBoxMaxDim
*/
unsigned int GetBoxSplitDim(boolean *used,Tbox *b);

/**     
    \brief Splits a box.

    Splits a given box in two sub-boxes. This can be seen as a constructor
    method, that is, the two sub-boxes are created (or initilized) inside
    this function.<br>
    If the dimension for which we want to split the box is larger than the
    box dimensionality this functions generates an error. <br>
    If the cut point is outside th box (i.e., <em>r</em> is below 0 or larger
    than 1) this functions generates an error. 

    \param n The dimension 
    \param r A double in (0,1) defining the cut point along dimension <em>n</em>
             given in relative to the box size along this dimension.
    \param b1 The first resulting box. This is a copy of <em>b</em> but for
              dimension <em>n</em> where this box only includes the lower
	      part of the original interval.
    \param b2 The second resulting box.This is a copy of <em>b</em> but for
              dimension <em>n</em> where this box only includes the upper
	      part of the original interval.
    \param b The original box to split.
*/
void SplitBox(unsigned int n,double r,Tbox *b1,Tbox *b2,Tbox *b);

/**     
    \brief Scales a box.

    Scales a box for all its dimensions with the given scale factor.

    \param max_upper The scale factor
    \param b The box to scale.
    
*/
void ScaleBox(double max_upper,Tbox *b);

/** 
    \brief Adds a margin to all dimensions of a box.

    Adds a margin to all dimensions of a box. 

    \param m The margin to add.
    \param b The box to expand.
*/
void AddMargin2Box(double m,Tbox *b);


/** 
   \brief Determines which box to explore first in depth first mode.

   Returns TRUE if box \e b1 is to be explored first in depth first.

   This is to be used as a LessThan operator in a heap of boxes.

   \param b1 The first box.
   \param b2 The second box.  
   \param userData The pointer to the data to pass to the LessThan operator as a
                   third parameter. In this particular LessThan this parameter
		   is not used.

   \return TRUE if the first parameter is to be explored before than the
           second one when in depth first mode.

   \sa box_heap.h, Theap.
*/
boolean CmpBoxDepthFirst(void *b1,void *b2,void *userData);

/** 
   \brief Determines which box to explore first in breadth first mode.

   Returns TRUE if box \e b1 is to be explored first in breadth first.

   This is to be used as a LessThan operator in a heap of boxes.

   \param b1 The first box.
   \param b2 The second box.
   \param userData The pointer to the data to pass to the LessThan operator as a
                   third parameter. In this particular LessThan this parameter
		   is not used.

   \return TRUE if the first parameter is to be explored before than the
           second one when in breadth first mode.

   \sa  box_heap.h, Theap.
*/
boolean CmpBoxBreadthFirst(void *b1,void *b2,void *userData);

/**     
    \brief Prints a box.

    Writes a box in file <em>f</em>, that can be <em>stdout</em>.
    The ouput is of the form <em>{n [l1,u1]...[ln,un]}</em> where
    <em>n</em> is the dimensionality of the box and <em>[lx,ux]</em>
    are the intervals defining the box.<br>
    All along <b>CuikSuite</b> <em>print</em>/<em>read</em> funtions are used to
    print/read in ASCII format and save/load are equivalen funcitions in
    binary format.

    \param f The stream where to write.
    \param b The box to write.
    
*/
void PrintBox(FILE *f,Tbox *b);

/**     
    \brief Prints a (sub-)box.

    Writes a box in file <em>f</em>, that can be <em>stdout</em>.
    The ouput is of the form <em>{n v1:[l1,u1]...vn:[ln,un]}</em> where
    <em>n</em> is the dimensionality of the box <em>vx</em> is the
    name of the variable for dimension <em>x</em> and <em>[lx,ux]</em>
    is the corresponding interval. The variable names are only
    printed if <em>vars</em> is not NULL.<br>
    All along <b>CuikSuite</b> <em>print</em>/<em>read</em> funtions are used to
    print/read in ASCII format and save/load are equivalen funcitions in
    binary format.

    \param f The stream where to write.
    \param used Array of booleans, one for each interval of the input boxes. If the
                boolean is TRUE, the corresponding interval is used in the print. 
		If the given pointer is NULL, all intervals are used.
    \param varNames The name for variables.
    \param b The box to write.
    
*/
void PrintBoxSubset(FILE *f,boolean *used,char **varNames,Tbox *b);

/**     
    \brief Reads a box from a file.

    Read a box from file <em>f</em>.
    The format of the boxes in the file is the same as that printed
    by PrintBox or PrintBoxSubset.<br>
    This function can be seen as a constructor, i.e., it generates
    a new box.

    \param f The stream from which to read the box.
    \param b The box to read.

    \return EOF if the file finishes before the box could be read.
*/
int ReadBox(FILE *f,Tbox *b);


/**     
    \brief Saves a box in binary format.

    Writes a box in file <em>f</em> in binary format.

    \param f The stream where to write.
    \param b The box to write.
    
*/
void SaveBox(FILE *f,Tbox *b);

/** 
    \brief Reads a box in binary format.

    Reads a box from file <em>f</em> in binary format.<br>
    This function is a box constructor method.

    \param f The stream from where to read. 
    \param b The box to write. 
    
*/
void LoadBox(FILE *f,Tbox *b);

/**     
    \brief Destructor

    Deletes a previously generated box (either via InitBox, ReadBox, CopyBox,...).

    \param b The box to be deleted.
      
*/
void DeleteBox(void *b);

#endif
