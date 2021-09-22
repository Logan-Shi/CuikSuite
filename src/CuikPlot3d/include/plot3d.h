#ifndef PLOT3D
#define PLOT3D

#include "defines.h"

#include "boolean.h"
#include "htransform.h"
#include "color.h"

#include <stdio.h>
#include <pthread.h>
#if __APPLE__
  #include <dispatch/dispatch.h>
#else
  #include <semaphore.h>
#endif

/** 
    \file plot3d.h

    \brief Definition of the Tplot3d type and the associated functions.

    Module to generate 3d plots. Right now the output is in 
    <a href="http://www.geomview.org">geomview</a> format.

    \sa Tplot3d, plot3d.c, Tplot, plot.h.
*/

/****************************************************************************/
/** \brief Default dice.

   Default value for the dice: smoothness in the representation of spheres
   and cylinders.
*/

#define DEFAULT_DICE 15

/************************************************************************************/
/** \brief  Red component of the default color of 3d objects.

    Red component of the default color of 3d objects.

    \sa Tplot3d
*/
#define DCP3D_R 0

/** \brief  Green component of the default color of 3d objects.

    Green component of the default color of 3d objects.

    \sa Tplot3d
*/
#define DCP3D_G 0

/** \brief  Blue component of the default color of 3d objects.

    Blue component of the default color of 3d objects.

    \sa Tplot3d
*/
#define DCP3D_B 1
/************************************************************************************/

/** \brief Maximum number of vertices in a picked face.

    Maximum number of vertices in a picked face. The face may have more vertices but
    they are not stored. 
    If necessary, the rest of vertices can be obtained from the face identifier.
*/
#define MAX_VERTEX_FACE_PICK 10
/************************************************************************************/

/** 
   \brief Pick info.

   Information about a pick even comming from geomview.
*/
typedef struct {
  unsigned int oID;                     /**< Identifier of the picked object. NO_UINT if no object is selected. */
  double point[4];                      /**< The clicked point. Each point has four components: x,y,z,a (a=alpha channel). */
  
  boolean haveVertex;                   /**< TRUE if a vertex is picked. */
  double vertex[4];                     /**< Coordinates of the vertex, if any. */
  
  boolean haveEdge;                     /**< TRUE if an edge is picked. */
  double edge[2][4];                    /**< The coordinates of the edge end-poits, if any. */
  
  boolean haveFace;                     /**< TRUE if a face is picked. */
  unsigned int nvf;                     /**< Number of vertices in the face. */
  double face[MAX_VERTEX_FACE_PICK][3]; /**< Coordinates of the face vertices. At most \ref MAX_VERTEX_FACE_PICK  are stored. */
  
  int vertexID;                         /**< Identifier of the selected vertex. -1 if no vertex is selected, i.e., if \e haveVertex is FALSE. */
  int edgeID[2];                        /**< Identifier of the end-point vertices of the edges, if any. */
  int faceID;                           /**< Identifier of the face, if any. */
   #if __APPLE__
    dispatch_semaphore_t lpick;         /**< Used to lock the access to the pick information while being updated. */
  #else 
    sem_t lpick;                        /**< Used to lock the access to the pick information while being updated. */
  #endif
} TpickInfo;  

/** 
   \brief A 3D plot.

   A structure containing the information to plot in 3D.   
*/
typedef struct {
  FILE *f;                      /**< File where to store the 3d geometry.*/
  char *fileName;               /**< Name of the file where we store geometry with the '/' and '.' replaced
		                     by '_'. This string is used to name the geometric elements stored in the file.
		                     In this way geometric elements from different files have different
		                     names and can be safely merged. */
  unsigned int nobj;            /**< Number of geometric objects created. Used to give identifiers to the
		                     geometric objects.*/
  Tcolor color;                 /**< Color for the object in definition. */

  unsigned int blockLevel;      /**< Number of blocks being defined. */
  boolean inObject;             /**< TRUE when we are in the middle of the definition of a geometric
		                     body composed from different elementary objects. */
  unsigned int lpid;            /**< Length of the string containing the process identifier. */
  pthread_t thread;             /**< Thread used to get input from geomview. Only used when \e f is
		                     stdout (when directly connecting to geomview). */
  TpickInfo pickInfo;           /**< Information about the last pick event. */
  #if __APPLE__
    dispatch_semaphore_t lout;  /**< Used to lock the access to stdout (stream used to communicate with geomview) */
  #else
    sem_t lout;                 /**< Used to lock the access to stdout (stream used to communicate with geomview) */
  #endif
} Tplot3d;
 
/** 
   \brief Constructor.

   Initializes a 3d plot.

   \param name Name of the file where to store the geometry.
   \param axes TRUE if we have to add the axes.
   \param argc Number of strings to be added to the geometry file header as comments.
   \param arg Strings to be added to the geometry file header as comments. Right now, this is used
              to store in the geometry file the command line used to create it.
   \param p The plot to initialize.
*/
void InitPlot3d(char *name,boolean axes,int argc,char **arg,Tplot3d *p);

/** 
   \brief Looks the full scene.

   Positions the camera so that the full scene is seen.

   \param p The plot3D to show.
*/
void LookPlot3d(Tplot3d *p);

/** 
   \brief Start a composed object.

   Start the definition of a geometric object composed by one or more basic geometric elements.

   \param c Color for the object. Use a null color (see \ref NullColor) for objects whose color
            does not need to be defined globally, i.e., whose color is already defined inside
	    the elements included in the 3d object (see \ref Plot3dObjectWithColors).
   \param p The plot to update.

   \return The identifier of the started object.
*/
unsigned int StartNew3dObject(Tcolor *c,Tplot3d *p);


/** 
   \brief Closes a composed object without assigning any color.

   Ends the definition of a geometric object composed by many basic geometric elements.
   In this case the object is not colored but we assume that each individual element
   has it own color.

   \param p The plot to update.
*/
void Close3dObjectNoColor(Tplot3d *p);

/** 
   \brief Closes a composed object.

   Ends the definition of a geometric object composed by many basic geometric elements.

   \param p The plot to update.
*/
void  Close3dObject(Tplot3d *p);

/** 
   \brief Deletes a previously created geometric object.

   Deletes a previously created geometric object. This is used when creating animations.

   \param nobj The identifier of the object to be deleted (i.e., the return of StartNew3dObject
               when the object was created).
   \param p The plot to update.
*/
void  Delete3dObject(unsigned int nobj,Tplot3d *p);

/** 
   \brief Starts a block of commands.

   Starts a block of commands that have to be executed simultaneously.
   Commands are, for instance, the generation of new geometry of the
   transformation/deletion of existing objects.

   \param p The plot to update.
*/
void Start3dBlock(Tplot3d *p);
/** 
   \brief Ends a block of commands.

   Ends a block of commands that have to be executed simultaneously.

   \param p The plot to update.
*/
void Close3dBlock(Tplot3d *p);

/** 
   \brief Changes the color of an object.

   Changes the color of an object.

   \param nobj The object identifier as returned by StartNew3dObject.
   \param c Color for the object.
   \param p The plot to update.
*/
void SetColor3dObject(unsigned int nobj,Tcolor *c,Tplot3d *p);

/** 
   \brief Introduces a delay in the generation of the geometry.

   Introduces a delay in the generation of the geometry. Used for animations.
						
   \param t Length in seconds of the delay.
   \param p The plot to update.
*/
void Delay3dObject(double t,Tplot3d *p);


/** 
   \brief Moves a 3d object.

   Moves a 3d object.
	
   \param nobj The identifier of the object to move, as returned by StartNew3dObject.
   \param t The homogenous transoform to apply to the object.
   \param p The plot to update.
*/
void Move3dObject(unsigned int nobj,THTransform *t,Tplot3d *p);

/** 
   \brief Adds an axis aligned box to the current object.

   Adds an axis aligned box to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param min_x Lower limit for the box along the X axis.
   \param max_x Upper limit for the box along the X axis.
   \param min_y Lower limit for the box along the Y axis.
   \param max_y Upper limit for the box along the Y axis.
   \param min_z Lower limit for the box along the Z axis.
   \param max_z Upper limit for the box along the Z axis.
   \param p The plot to update.
*/
void PlotBox3d(double min_x,double max_x,
	       double min_y,double max_y,
	       double min_z,double max_z,
	       Tplot3d *p);
/** 
   \brief Adds a triangle to the current object.

   Adds triangle to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param x1 X coordinate for the first point of the triangle.
   \param y1 Y coordinate for the first point of the triangle.
   \param z1 Z coordinate for the first point of the triangle.
   \param x2 X coordinate for the second point of the triangle.
   \param y2 Y coordinate for the second point of the triangle.
   \param z2 Z coordinate for the second point of the triangle.
   \param x3 X coordinate for the third point of the triangle.
   \param y3 Y coordinate for the third point of the triangle.
   \param z3 Z coordinate for the third point of the triangle.
   \param p The plot to update.
*/
void PlotTriangle3d(double x1,double y1,double z1,
		    double x2,double y2,double z2,
		    double x3,double y3,double z3,
		    Tplot3d *p);
/** 
   \brief Adds a polytope to the current object.

   Adds polytope to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   What we denote as polytope are geomview
   <a href="http://www.geomview.org/docs/html/OFF.html">OFF</a>s.

   \param nv Number of vertexes of the polytope.
   \param nf Number of faces of the polytope.
   \param ne Number of edges of the polytope (not used).
   \param v Pointer to 3d array with the (x,y,z) coordinates of the vertexes.
   \param nvf Pointer to an array with the number of vertexes for each face.
   \param fv Pointer to an array with the vertexes for each face.
   \param p The plot to update.
*/
void  Plot3dObject(unsigned int nv,unsigned int nf,unsigned int ne,
		   double **v,
		   unsigned int *nvf,
		   unsigned int **fv,Tplot3d *p);

/** 
   \brief Adds a colored polytope to the current object.

   Adds colored polytope to the current object. 

   This command can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   What we denote as polytope are geomview
   <a href="http://www.geomview.org/docs/html/OFF.html">OFF</a>s.

   \param nv Number of vertexes of the polytope.
   \param nf Number of faces of the polytope.
   \param ne Number of edges of the polytope (not used).
   \param v Pointer to 3d array with the (x,y,z) coordinates of the vertexes.
   \param nvf Pointer to an array with the number of vertexes for each face.
   \param fv Pointer to an array with the vertexes for each face.
   \param c The color.
   \param p The plot to update.
*/
void Plot3dObjectWithColor(unsigned int nv,unsigned int nf,unsigned int ne,
			   double **v,
			   unsigned int *nvf,
			   unsigned int **fv,Tcolor *c,Tplot3d *p);
/** 
   \brief Adds a colored polytope to the current object.

   Adds colored polytope to the current object. The difference with respect
   to \ref Plot3dObjectWithColor is that here we have a color for each
   vertex of the polytope. Thus, the renderer takes care of interpolating
   the color inside each face. This typically produces smoother figures.

   This command can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
   
   Note that if this function is used, the global color of the 
   3d object is set to null (see \ref NullColor) so that the colors
   defined inside this object are not overriden by the global color.
	
   What we denote as polytope are geomview
   <a href="http://www.geomview.org/docs/html/COFF.html">COFF</a>s.

   \param nv Number of vertexes of the polytope.
   \param nf Number of faces of the polytope.
   \param ne Number of edges of the polytope (not used).
   \param v Pointer to 3d array with the (x,y,z) coordinates of the vertexes.
   \param c The colors. One for each vertex.
   \param nvf Pointer to an array with the number of vertexes for each face.
   \param fv Pointer to an array with the vertexes for each face.
   \param p The plot to update.
*/
void Plot3dObjectWithColors(unsigned int nv,unsigned int nf,unsigned int ne,
			    double **v,Tcolor *c,
			    unsigned int *nvf,
			    unsigned int **fv,Tplot3d *p);

/** 
   \brief Adds a sphere to the current object.

   Adds sphere to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param r The radius of the sphere.
   \param x The X component of the center of the sphere.
   \param y The Y component of the center of the sphere.
   \param z The Z component of the center of the sphere.
   \param p The plot to update.
*/
void PlotSphere(double r,double x,double y,double z,Tplot3d *p);

/** 
   \brief Adds a cylinder to the current object.

   Adds cylinder to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param r The radius of the cylinder.
   \param p1 Array with the (x,y,z) point where the cylinder has
             to start.
   \param p2 Array with the (x,y,z) point where the cylinder has
             to end.
   \param p The plot to update.
*/
void PlotCylinder(double r,double *p1,double *p2,Tplot3d *p);

/** 
   \brief Adds a line to the current object.

   Adds line to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param p1 Origin of the line (3D point).
   \param p2 End of the line (3D point).
   \param p The plot to update.
*/
void PlotLine(double *p1,double *p2,Tplot3d *p);

/** 
   \brief Adds a collecion of segments to the current object.

   Adds a collection of segments to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param n Number of points defining the polyline.
   \param pt Array of 3D points defining the segments (a pair of entries
            for each segment).
   \param p The plot to update.
*/
void PlotSegments(unsigned int n,double **pt,Tplot3d *p);

/** 
   \brief Adds a polyline to the current object.

   Adds polyline (i.e., a collection of concatenated lines) 
   to the current object. This command
   can only be used in between a call to StartNew3dObject and
   the corresponding call to Close3dObject.
	
   \param n Number of points defining the polyline.
   \param x Array with the x component for the points in the polyline.
   \param y Array with the y component for the points in the polyline.
   \param z Array with the z component for the points in the polyline.
   \param p The plot to update.
*/
void PlotVect3d(unsigned int n,
		double *x,double *y,double *z,
		Tplot3d *p);
/** 
   \brief Takes a screenshot of the geometry.

   Takes a screenshot of the geometry. Used to create videos from animations.
	
   The screenshot format are  \e .ppm files that can be browsed/manipulated
   easily.

   \param file Name of the file where to store the snapshot.
   \param p The plot to update.
*/		
void Take3dSnapshot(char *file,Tplot3d *p);

/** 
   \brief Destructor.

   Closes a 3d plot. Before closing the file, all geometric
   objects are offset by <em>(average_x,average_y,average_z)</em>.
   This is used to center the scene in the (0,0,0) and facilitates
   the on-line manipulation (rotations, translations,...) using geomview.
	
   \param quit TRUE if we want to quit geomview right after displaying the
               geometry. Used to quit after an animation.
   \param p The plot to update.
*/
void ClosePlot3d(boolean quit,Tplot3d *p);

#endif
