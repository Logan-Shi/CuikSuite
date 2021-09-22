#ifndef INTERVALH
#define INTERVALH

#include "boolean.h"

#include <stdio.h>

/** \file interval.h
    \brief Definition of the Tinterval type and the associated functions.

    Definition of the Tinterval type and the associated functions.

    \sa Tinterval, interval.c.
 */


/** 
    \brief Defines a interval.

    Defines a fragment of the Real line bounded by a lower and an upper limit.
    <br>
    Unbounded intervals are not implemented: they are not necessary for
    our current range of application since variables are always bounded. 
    Might be necessary for other applications in the future, though.
    <br>
    The size of an interval is the upper limit minus the lower limit.
    <br>
    If the upper limit is lower than the lower limit (i.e., if the interval size
    is negative), the interval is said to be empty.
    
    \sa interval.h interval.c 
 */
typedef struct
{
  double lower_limit; /**< Lower limit for the interval */
  double upper_limit; /**< Upper limit for the interval */
} Tinterval;

/** 
   \brief Constructor.
   
   Defines a new interval with the given limits.

   \param lower The lower limit for the new interval.
   \param upper The upper limit for the new interval.
   \param i The interval to define.
*/
void NewInterval(double lower,double upper,Tinterval *i);

/** 
   \brief Copy constructor.
   
   Defines a new interval from another interval.

   \param i_dst The interval to create.
   \param i_org The interval from where to copy.
*/
void CopyInterval(Tinterval *i_dst,Tinterval *i_org);

/** 
   \brief Compares two intervals.
   
    Compares two intervals.

   \param i1 The first interval.
   \param i2 The second interval.

   \return TRUE if the two given intervals are the same.
*/
boolean CmpIntervals(Tinterval *i1,Tinterval *i2);

/** 
   \brief Gets the lower limit.
   
   Gets the lower limit of an interval

   \param i The  interval.

   \return The lower limit defining the interval.
*/
double LowerLimit(Tinterval *i);

/** 
   \brief Gets the uppser limit.
   
   Gets the upper limit of an interval.

   \param i The  interval.

   \return The upper limit defining the interval.
*/
double UpperLimit(Tinterval *i);

/** 
   \brief Gets the uppser limit.
   
   Gets the upper limit of an interval.

   \param i The  interval.

   \return The upper limit defining the interval.
*/
double IntervalSize(Tinterval *i);

/** 
   \brief Distance to an interval.

   Distance of a point to an interval.
   This is zero for pointsin the interval.
   
   \param p The query point.
   \param i The query interval.

   \return The distance between the point and the interval.
*/
double DistanceToInterval(double p,Tinterval *i);

/** 
   \brief Checks if a value is inside an interval.
   
   Checks if a value is inside an interval.

   \param p The value
   \param tol Tolerance in the comparison.
   \param i The interval.

   \return TRUE if the point is inside the interval.
*/
boolean IsInside(double p,double tol,Tinterval *i);

/** 
   \brief Gets the interval center.
   
   Computes the interval center, i.e., the average between the upper and the
   lower limit.

   \param i The interval.

   \return The interval center.
*/
double IntervalCenter(Tinterval *i);

/** 
   \brief Gets a point inside the interval.
   
   Computes a point inside the interval by linear interpolation 
   between the extremes.

   If the interval is [-INF,INF] the output is 0, irrespectively of r.
   
   If one of the extremes of the interval is +/-INF, the returned
   point is one plus/less than the other extreme of the interval.

   \param r The interpoltion factor (must be in  [0,1], otherwise the
            given value is cropped to this range).
   \param i The interval.

   \return The point in the interval.
*/
double PointInInterval(double r,Tinterval *i);

/** 
   \brief Sets a new lower limit.
   
   Changes the lower limit for an interval.

   \param c The new lower limit.
   \param i The interval.
*/
void SetLowerLimit(double c,Tinterval *i);

/** 
   \brief Symmetrically increases the size of an interval.

   Modifies an interval adding offsets to its lower/upper limit.

   Note that after this operation the interval might become
   empty if you use the wrong offsets. Use at your own risk.
   
   \param lo Value to add to the lower limit.
   \param uo Value to add to the upper limit.
   \param i The interval to enlarge.
 */
void EnlargeInterval(double lo,double uo,Tinterval *i);

/** 
   \brief Changes the interval limits to include a given point.
   
   Changes  the interval limits to include a given point..

   \param v The point to be included in the interval.
   \param i The interval.
*/
void ExpandInterval(double v,Tinterval *i);

/** 
   \brief Sets a new upper limit.
   
   Changes the upper limit for an interval.

   \param c The new lower limit.
   \param i The interval.
*/
void SetUpperLimit(double c,Tinterval *i);

/** 
   \brief Updates the lower limit.
   
   Changes the lower limit for an interval only in the new
   value is upper than the current lower limit.

   \param c The temptative new lower limit.
   \param i The interval.
*/
void UpdateLowerLimit(double c,Tinterval *i);

/** 
   \brief Updates the upper limit.
   
   Changes the upper limit for an interval only in the new
   value is lower than the current upper limit.

   \param c The new temptative upper limit.
   \param i The interval.
*/
void UpdateUpperLimit(double c,Tinterval *i);

/** 
   \brief Checks is a given interval is fully included into another interval.
   
   Checks is a given interval is fully included into another interval.

   \param i1 The interval to be included.
   \param i2 The inclusion interval.

   \return TRUE if \e i1 is fully included in \e i2.
*/
boolean IntervalInclusion(Tinterval *i1,Tinterval *i2);

/** 
   \brief Checks is a two intervals intersect.
   
   Checks two given intervals have a non-empty intersection.

   \param i1 The first interval.
   \param i2 The second interval.

   \return TRUE if \e i1 and \e i2 intersect.
*/
boolean Intersect(Tinterval *i1,Tinterval *i2);

/** 
   \brief Computes the intersection of two intervals.
   
   Computes the intersection of two intervals.

   \param i1 The first interval.
   \param i2 The second interval.
   \param i_out The output intersection interval, possibly empty.

   \return TRUE if \e i_out is not empty.
*/
boolean Intersection(Tinterval *i1,Tinterval *i2,Tinterval *i_out);

/** 
   \brief Computes the union of two intervals.
   
   Computes the union of two intervals.

   \param i1 The first interval.
   \param i2 The second interval.
   \param i_out The output union interval, possibly empty.

   \return TRUE if \e i_out is not empty. The union of two intervals
   is empty if the two input intervals were empty.
*/
boolean Union(Tinterval *i1,Tinterval *i2,Tinterval *i_out);

/** 
   \brief Checks if a given interval is empty.
   
   Checks if a given interval is empty.

   \param i The interval to check.

   \return TRUE if \e i is empty.
*/
boolean EmptyInterval(Tinterval *i);

/** 
   \brief Checks if a given interval is zero.
   
   Checks if a given interval is zero, i.e.
   lower and upper equal to zero up to a tiny
   constant.

   \param i The interval to check.

   \return TRUE if \e i is zero.
*/
boolean ZeroInterval(Tinterval *i);

/** 
   \brief Scales an interval.

   Product of an interval and a constant.
   
   \param i1 The input interval.
   \param e The scale factor.
   \param i_out The resulting interval.
*/
void IntervalScale(Tinterval *i1,double e,Tinterval *i_out);

/** 
   \brief Product of two intervals.

   Product of two intervals.
   
   \param i1 The first interval.
   \param i2 The second interval.
   \param i_out The resulting interval.
*/
void IntervalProduct(Tinterval *i1,Tinterval *i2,Tinterval *i_out);

/** 
   \brief Addition of two intervals.

   Sum of two intervals.
   
   \param i1 The first interval.
   \param i2 The second interval.
   \param i_out The resulting interval.
*/
void IntervalAdd(Tinterval *i1,Tinterval *i2,Tinterval *i_out);

/** 
   \brief Substraction of two intervals.

   Substraction of two intervals.
   
   \param i1 The first interval.
   \param i2 The second interval.
   \param i_out The resulting interval.
*/
void IntervalSubstract(Tinterval *i1,Tinterval *i2,Tinterval *i_out);

/** 
   \brief Change of sign of a given interval.

    Change of sign of a given interval. Equivalen to scale the interval
    with \e -1.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalInvert(Tinterval *i,Tinterval *i_out);

/** 
   \brief Exponentional of an interval.

   Computes the exponentional of a given interval.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalExp(Tinterval *i,Tinterval *i_out);

/** 
   \brief Power of a given interval by a integer power factor.

    Computes <br>
    <center><em>i_out=i_in^p</em></center>.

   \param i The input interval.
   \param p The power.
   \param i_out The resulting interval.
*/
void IntervalPow(Tinterval *i,unsigned int p,Tinterval *i_out);

/** 
   \brief Interval square root.

    Computes the square root of an interval. Negative parts of the interval
    are not taken into account. If the whole input interval is negative
    the result is an empty interval.

   \param i The input interval.
   \param i_out The resulting interval.

   \return TRUE if the output interval is NULL.
*/
boolean IntervalSqrt(Tinterval *i,Tinterval *i_out);

/** 
   \brief Interval division.

    Divides one interval by another. If the denominator includes
    the zero, this function triggers an error.

   \param num The interval numerator.
   \param den The interval denominator.
   \param i_out The resulting interval.
*/
void IntervalDivision(Tinterval *num,Tinterval *den,Tinterval *i_out);

/** 
   \brief Interval offset.

   Displaces an interval by a constant value.

   \param i The input interval.
   \param offset The quantity to add to the interval limits.
   \param i_out The resulting interval.
*/
void IntervalOffset(Tinterval *i,double offset,Tinterval *i_out);

/** 
   \brief Interval sine.

   Computes the bound of the sinus on a given interval.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalSine(Tinterval *i,Tinterval *i_out);

/** 
   \brief Interval cosine.

   Computes the bound of the cosinus on a given interval.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalCosine(Tinterval *i,Tinterval *i_out);

/** 
   \brief Interval tangent.

   Computes the bound of the tangent on a given interval.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalTangent(Tinterval *i,Tinterval *i_out);

/** 
   \brief Interval squared secant per tangent.

   Computes the bound of the squared secant on a given interval
   per its tangent.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalSecant2Tangent(Tinterval *i,Tinterval *i_out);

/** 
   \brief Interval squared secant.

   Computes the bound of the squared secant on a given interval.

   \param i The input interval.
   \param i_out The resulting interval.
*/
void IntervalSecant2(Tinterval *i,Tinterval *i_out);

/** 
   \brief Interval atan2.

   Computes the bound of the atan2 on a given sin/cos
   intervals.
   
   The current implementation is tailored to post-process
   solution files and in only works for small intervals.

   The output in in the range \f$[-\pi,\pi]\f$ except for
   the case where \e is and \e ic include (-1,0). In this
   case the output interval is in the range \f$[0,2\:\pi]\f$.

   \param is The sinus interval.
   \param ic The cosinus interval.
   \param i_out The resulting interval.
*/
void IntervalAtan2(Tinterval *is,Tinterval *ic,Tinterval *i_out);

/** 
   \brief Prints an angular interval.

   Writes an interval to a stream that can be \e stdout.
   Values like +/-PI or +/-PI/2 are printed symbolically to
   avoid rounding.

   This should only be used for angular variables.

   \param f The strem.
   \param i The interval to write.
*/
void PrintSymbolInterval(FILE *f,Tinterval *i);

/** 
   \brief Prints an interval.

   Writes an interval to a stream that can be \e stdout.

   \param f The strem.
   \param i The interval to write.
*/
void PrintInterval(FILE *f,Tinterval *i);

/** 
   \brief Destructor.

   Deletes an interval structure.

   \param i The interval to delete.
*/
void DeleteInterval(Tinterval *i);

#endif
