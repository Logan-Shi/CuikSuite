#ifndef GEOMH
#define GEOMH

#include "interval.h"

/** 
   \file geom.h

   \brief Definition of basic functions. 

   Definition of basic functions (basically geomtric functions but
   also some other mathematical functions). 
   
   \todo Separate non-geometric functions fom the purely geometric ones.

   \sa geom.c.
*/

/** 
   \brief Determines if a point is at the left of a vector.

   Determines if a 2D point is at the left of a vector in R^2.
   
   \param px X coordinate of the point.
   \param py Y coordinate of the point.
   \param x1 X coordinate of the first point defining the vector.
   \param y1 Y coordinate of the first point defining the vector.
   \param x2 X coordinate of the second point defining the vector.
   \param y2 Y coordinate of the second point defining the vector.

   \return TRUE if point at the left of the vector.

   \sa pointRightOfLine
*/
boolean pointLeftOfLine(double px,double py,
			double x1,double y1,double x2,double y2);

/** 
   \brief Determines if a point is at the right of a vector.

   Determines if a 2D point is at the right of a vector in R^2.
   

   \param px X coordinate of the point.
   \param py Y coordinate of the point.
   \param x1 X coordinate of the first point defining the vector.
   \param y1 Y coordinate of the first point defining the vector.
   \param x2 X coordinate of the second point defining the vector.
   \param y2 Y coordinate of the second point defining the vector.

   \return TRUE if point at the right of the vector.

   \sa pointLeftOfLine
*/
boolean pointRightOfLine(double px,double py,
			 double x1,double y1,double x2,double y2);

/** 
   \brief Determines the axis aligned bounding box of a set of points in R^2.

   Determines the axis aligned bounding box of a set of points in R^2.

   \param n The number of points to be bounded.
   \param x Array with the X coordinates of the points.
   \param y Array with the Y coordinates of the points.
   \param ix Output interval in the X axis.
   \param iy Output interval in the Y axis.
*/
void ComputeBoundingBox(unsigned int n,double *x,double *y,
			Tinterval *ix,Tinterval *iy);

/** 
   \brief Determines the axis aligned bounding box of a set of points in R^3.

   Determines the axis aligned bounding box of a set of points in R^3.

   \param n The number of points to be bounded.
   \param x Array with the X coordinates of the points.
   \param y Array with the Y coordinates of the points.
   \param z Array with the Z coordinates of the points.
   \param ix Output interval in the X axis.
   \param iy Output interval in the Y axis.
   \param iz Output interval in the Z axis.
*/
void ComputeBoundingBox3d(unsigned int n,double *x,double *y,double *z,
			  Tinterval *ix,Tinterval *iy,Tinterval *iz);

/** 
   \brief Intersects a segment and a circle.

   Intersects the circle \f[x^2+y^2=r^2\f] with the segment
   defined by two 2d points given in vectors \e x and \e y.

   The output includes at most two points (stored in \e xi and \e yi
   whose space must be allocated by the caller)
   
   The implementation is numerically save in the sense that it returns
   as many solutions are possible. However the returned solution can be
   slightly out of the segment due to numerical issues (the only way
   to avoid this is to return an interva instead of a point).

   \param r2 Squared radious of the circle.
   \param x X component of the two points defining the segment.
   \param y Y component of the two points defining the segment.
   \param tol Numerical tolerance. Used to accept as a solutions points 
              not extrictly on the segment but very close to its extremes.
   \param n Number of intersections. This can be 0, 1 or 2.
   \param xi X component of the \e n intersection points detected.
   \param yi Y component of the \e n intersection points detected.
*/
void SegmentCircleIntersection(double r2,
			       double *x,double *y,
			       double tol,
			       unsigned int *n,
			       double *xi,double *yi);

/** 
   \brief Intersects a segment and a sphere.

   Intersects the circle \f[x^2+y^2+z^2=r^2\f] with the segment
   defined by two 3d points given in vectors \e x, \e y, and \e z.

   The output includes at most two points (stored in \e xi, \e yi, and \e zi
   whose space must be allocated by the caller)
   
   The implementation is numerically save in the sense that it returns
   as many solutions are possible. However the returned solution can be
   slightly out of the segment due to numerical issues (the only way
   to avoid this is to return an interva instead of a point).

   \param r2 Squared radious of the circle.
   \param x X component of the two points defining the segment.
   \param y Y component of the two points defining the segment.
   \param z Z component of the two points defining the segment.
   \param tol Numerical tolerance. Used to accept as a solutions points 
              not extrictly on the segment but very close to its extremes.
   \param n Number of intersections. This can be 0, 1 or 2.
   \param xi X component of the \e n intersection points detected.
   \param yi Y component of the \e n intersection points detected.
   \param zi Z component of the \e n intersection points detected.
*/
void SegmentSphereIntersection(double r2,
			       double *x,double *y,double *z,
			       double tol,
			       unsigned int *n,
			       double *xi,double *yi,double *zi);

/** 
   \brief Defines a line given two points.

   Defines the parameters of a 2d line given two points.
   
   \param x The X component of the two points.
   \param y The Y component of the two points.
   \param normalized TRUE if the output line parameters should be normalized.
   \param c The coeficients of the output line (3 values, space allocated by the caller).
*/
void Line2Points(double *x,double *y,boolean normalized,double *c);

/** 
   \brief Defines a plane given 3 points.

   Defines the parameters of a 3d plane given 3 points.

   \param x The X component of the three points.
   \param y The Y component of the three points.
   \param z The Z component of the three points.
   \param normalized TRUE if the output plane parameters should be normalized.
   \param c The coeficients of the output plane (4 values, space allocated by the caller).
*/
void Plane3Points(double *x,double *y,double *z,
		  boolean normalized,double *c);

/** 
   \brief Clips a rectangle and a circle.

   Reduces the ranges defining a 2D box so that it is adjusted to a zero
   centered circle with a given radius.

   \param r2 Squared radius of the circle.
   \param x Interval defining the X axis for the 2D box.
   \param y Interval defining the Y axis for the 2D box.
   \param x_new Interval defining the X axis of the box after the clipping.
   \param y_new Interval defining the Y axis of the box after the clipping.

   \return TRUE if the intersection is not empty.
*/
boolean RectangleCircleClipping(double r2,
				Tinterval *x,Tinterval *y,
				Tinterval *x_new,Tinterval *y_new);


/** 
   \brief Clips a 3D box and a sphere.

   Reduces the ranges defining a 3D box so that it is adjusted to a zero
   centered sphere with a given radius.

   \param r2 Squared radius of the sphere.
   \param x Interval defining the X axis for the 3D box.
   \param y Interval defining the Y axis for the 3D box.
   \param z Interval defining the Z axis for the 3D box.
   \param x_new Interval defining the X axis of the box after the clipping.
   \param y_new Interval defining the Y axis of the box after the clipping.
   \param z_new Interval defining the Z axis of the box after the clipping.

   \return TRUE if the intersection is not empty.
*/
boolean BoxSphereClipping(double r2,
			  Tinterval *x,Tinterval *y,Tinterval *z,
			  Tinterval *x_new,Tinterval *y_new,Tinterval *z_new);

/** 
   \brief Clips a 2D box and a scaled parabola.

   Reduces the ranges defining a 2D box so that it is adjusted to a
   offest, scaled parabola, \f$x^2+\alpha y=\beta\f$.

   \param x Interval defining the X axis for the 2D box.
   \param alpha The scale factor.
   \param beta The offset factor.
   \param y Interval defining the Y axis for the 2D box.
   \param x_new Interval defining the X axis of the box after the clipping.
   \param y_new Interval defining the Y axis of the box after the clipping.

   \return TRUE if the intersection is not empty.
*/
boolean RectangleParabolaClipping(Tinterval *x,double alpha,double beta,Tinterval *y,
				  Tinterval *x_new,Tinterval *y_new);

/** 
   \brief Clips a 3D box and a scaled saddle.

   Reduces the ranges defining a 3D box so that it is adjusted to offest, scaled saddle
   equation,  \f$x y + \alpha z= \beta\f$.

   \param x Interval defining the X axis for the 3D box.
   \param y Interval defining the Y axis for the 3D box.
   \param alpha The scale factor.
   \param beta The offset factor.
   \param z Interval defining the Z axis for the 3D box.
   \param x_new Interval defining the X axis of the box after the clipping.
   \param y_new Interval defining the Y axis of the box after the clipping.
   \param z_new Interval defining the Z axis of the box after the clipping.

   \return TRUE if the intersection is not empty.
*/
boolean BoxSaddleClipping(Tinterval *x,Tinterval *y,double alpha,double beta,Tinterval *z,
			  Tinterval *x_new,Tinterval *y_new,Tinterval *z_new);

/** 
   \brief Defines a unitary vector normal to a given vector.

   Defines a unitary vector normal to a given vector in R^3.
   Observe that there is a continous set of normal vectors to
   a given vector. We just pick one of them.
   
   \param v The output vector.
   \param n The reference vector.
*/
void DefineNormalVector(double *v,double *n);

/** 
   \brief Computes the cross product of two 3d vectors.

   Computes the cross product of two 3d vectors.

   \param v1 First 3d vector.
   \param v2 Second 3d vector.
   \param v3 The output 3d vector.
*/
void CrossProduct(double *v1,double *v2,double *v3);

/** 
   \brief Computes the dot product of two 3d vectors.

   Computes the dot product of two 3d vectors.

   \param v1 First 3d vector.
   \param v2 Second 3d vector.

   \return The dot produt.
*/
double DotProduct(double *v1,double *v2);

/** 
   \brief Determines if two sets of vertices define a neighbouring triangle.

   Determines if two triangles are neighbours. Checks if the two triangles
   share two vertices.

   Whe assume the vertices in each triangle to be different.

   \param v1 The index of the three vertices defining the first triangle.
   \param v2 The index of the three vertices defining the second triangle.

   \return TRUE if the two triangles share two vertices.
*/
boolean NeighbouringTriangles(unsigned int *v1,unsigned int *v2);

/** 
   \brief Identifies triangles formed by the same set of vertices.

   Determines if two triangles are defined over the same set of vertices.

   Whe assume the vertices in each triangle to be different.

   \param v1 The index of the three vertices defining the first triangle.
   \param v2 The index of the three vertices defining the second triangle.

   \return TRUE if the two triangles share the three vertices.
*/
boolean SameTriangle(unsigned int *v1,unsigned int *v2);

/** 
   \brief Determinant of a 2x2 matrix.

   Determinant of a 2x2 matrix given by columns.
   This is used to solve small lineal systems.

   \param c1 The first column.
   \param c2 The first column.
   
   \return The determinant.
*/
double Det2x2(double *c1,double *c2);

/** 
   \brief Determinant of a 3x3 matrix.

   Determinant of a 3x3 matrix given by columns.
   This is used to solve small lineal systems.

   \param c1 The first column.
   \param c2 The first column.
   \param c3 The first column.
   
   \return The determinant.
*/
double Det3x3(double *c1,double *c2,double *c3);

/** 
    \brief Volume of of a n-ball.

    Volume of a ball of a given radius in a given dimensional space.

    Computed using the recursion given in
    http://en.wikipedia.org/wiki/Volume_of_an_n-ball

    \param n The dimension of the space.
    \param r The radius of the ball.

    \return The volume of the 'n'-dimensional ball of radius 'r'.
*/
double BallVolume(unsigned int n,double r);

/** 
  \brief Initializes a combination.

  Initializes a combination of \e n numbers with 0 to \e m (included)
  options per number.

  \param n The number of entries in the combiation.
  \param m The number of options for each entry.
  \param cb Array where to store the combination.
*/
void FirstCombination(unsigned int n,unsigned int m,unsigned int *cb);

/** 
  \brief Moves to the next combination.

  Iterates to the next combination of \e n numbers with up to \e m
  values per number.

  \param n The number of entries in the combiation.
  \param m The number of options for each entry.
  \param cb Array where to store the combination.

  \return TRUE if the next combination actually exits.
*/
boolean NextCombination(unsigned int n,unsigned int m,unsigned int *cb);

/** 
   \brief Pretty print a real number.

   Prints a real number rounding to 0,1,-1, if it is the case.

   \param f The file where to print the number.
   \param r The number to print.
*/
void PrintReal(FILE *f,double r);

/** 
   \brief Pretty print three real number.

   Prints three real numbers separated by commas.

   \param f The file where to print the number.
   \param r1 The first number to print.
   \param r2 The second number to print.
   \param r3 The third number to print.
*/
void Print3Reals(FILE *f,double r1,double r2,double r3);

/** 
   \brief Pretty print an angle.

   Prints an angle rounding to 0,pi,-pi,pi/2,-pi/2, if it is the case.

   \param f The file where to print the number.
   \param r The angle to print.
*/
void PrintAngle(FILE *f,double r);

#endif
