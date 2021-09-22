#ifndef POLYHEDRONH
#define POLYHEDRONH

#include "plot3d.h"
#include "htransform.h"
#include "filename.h"
#include "color.h"

#include <stdlib.h>

/** 
    \file polyhedron.h
    \brief Definition of the Tpolyhedron type and the associated functions.

    Definition of the Tpolyhedron  type and the associated functions.

    \sa Tpolyhedron, polyhedron.c.
*/

/************************************************************************************/
/** \brief  One of the possible type of shapes.

    One of the possible type of shapes.  A normal shape is show and
    considered for collisions.

    \sa Tpolyhedron
*/
#define NORMAL_SHAPE 0

/** \brief  One of the possible type of shapes.

    One of the possible type of shapes.  A hiden shape is not show but it is
    considered for collisions.

    \sa Tpolyhedron
*/
#define HIDDEN_SHAPE 1

/** \brief  One of the possible type of shapes.

    One of the possible type of shapes.  A decor(ation) shape is show but it is not
    considered for collisions.

    \sa Tpolyhedron
*/
#define DECOR_SHAPE  2

/************************************************************************************/
/************************************************************************************/
/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. An OFF is a
    general polyhedron defined by its vertices and its faces.
    This is a standard <a href="http://www.geomview.org">geomview</a>
    construction.

    \sa Tpolyhedron
*/
#define OFF      0

/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. An COFF is an
    OFF with color information per vertex.

    \sa Tpolyhedron
*/
#define COFF      1

/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. An SPHERE
    is defined by a center (x,y,z) and a radius. This is a 
    standard <a href="http://www.geomview.org">geomview</a>
    construction.

    \sa Tpolyhedron
*/
#define SPHERE   2

/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. A CYLINDER
    is defined by two 3d points. This is not standard in 
    <a href="http://www.geomview.org">geomview</a>.

    \sa Tpolyhedron
*/
#define CYLINDER 3

/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. A LINE
    is defined by two 3d points. This is standard in 
    <a href="http://www.geomview.org">geomview</a>.

    \sa Tpolyhedron
*/
#define LINE 4

/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. A set
    of SEGMENTS is defined by a set of pairs of 3d points. 
    This is standard in <a href="http://www.geomview.org">geomview</a>.

    \sa Tpolyhedron
*/
#define SEGMENTS 5


/** \brief  One of the possible type of polyhedrons.

    One of the possible type of polyhedrons. 
    Used when there is an error in the definition of the object.

    \sa Tpolyhedron
*/
#define EMPTY_BODY 6

/************************************************************************************/

/** 
   \brief A polyhedron.

   Polyhedron implementation.

   Originally this was designed for convex polyhedrons but now we can 
   deal with non-convex ones also.

   Note that we can have cylinders, spheres and general polyhedrons 
   (<a href="http://www.geomview.org">geomview</a> non-colored OFFs)
   However, the shapes are only used for display purposes since internally
   all objects are represented/approximated as polyhedrons (i.e., OFFs). 
   This is specially relevant for collision detection since a polytope approximating 
   the cylinder and the sphere is used. The granularity of this approximation adjusted
   in the \e .world files.

   See \ref InitPolyhedronFromFile for more details.

   \sa  polyhedron.h, polyhedron.c.
*/
typedef struct {
  unsigned int type; /**< Type of body: SEGMENTS, LINE, CYLINDER, SPHERE, OFF. */

  unsigned int status; /**< Display status of the body: NORMAL (shown and used for collision 
			    detection), HIDDEN (not shown, but used in collision detection), 
			    DECOR (shown but not used in collision detection). */

  Tcolor color;        /**< The color of the body. */

  unsigned int obj3d;  /**< Identifier of the body. Used when plotting (see Tplot3d).*/

  unsigned int nv;     /**< Number of vertices.*/
  unsigned int nf;     /**< Number of faces. */
  unsigned int ne;     /**< Number of edges (not used). */
  double **v;          /**< The vertices (3d points).*/
  Tcolor *cv;          /**< Color for each vertice. Only used in COFFs. */
  unsigned int *nvf;   /**< Number of vertices per face. */
  unsigned int **fv;   /**< Face vertices. */

  double rad;          /**< Radius of the sphere/cylinder. */
  unsigned int gr;     /**< Granularity of spheres*/
  
  double center[3];    /**< Center of the sphere.*/

  double p1[3];        /**< Origin of the cylinder axes. */ 
  double p2[3];        /**< End of the cylinder axes.*/

  double maxCoord;     /**< Maximum of the X,Y,Z coordinates used to represent the 
                            polyhedron. This provides a conservative bounding box for this
			    object. */

} Tpolyhedron;

/** 
   \brief Constructor.

   Define a Tpolyhedron from a file.

   The default geometry file used in the CuikSuite are an variant of the geomview
   OFF files. Originally, the OFF files only include polygonal geometry (vertices
   and faces). We extended it to include also spheres, cylinders, lines and
   sets of 3D segments.

   Additionally, the CuikSuite can natively read binary STL files.

   Finally, if the <a href="http://assimp.sourceforge.net">Assimp libary</a> is available
   we can read any of the file types supported by this libary. This includes,
   for instance, collada or blender files. The full list of supported
   file types is <a href="http://assimp.sourceforge.net/main_features_formats.html">here</a>.
   All those file formats are converted to a general OFF structure (vertices
   and faces).

   \param fname The name of the file from where to read the information.
   \param c The color of the object.
   \param gr The granularity to define polyhedrons for spheres and cylinders.
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void InitPolyhedronFromFile(Tfilename *fname,Tcolor *c,
			    unsigned int gr,unsigned int bs,Tpolyhedron *p);

/** 
   \brief Constructor.

   Defines an OFF object from a set of triangles.

   \param nv Number of vertexes defining the triangulated surface.
   \param v The 3D vertexes defining the surface.
   \param nt Number of triangles.
   \param t The triangle vertexes (indices of the vertexes defining the triangles).
   \param c The color of the sphere.
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void InitPolyhedronFromTriangles(unsigned int nv,double **v,
				 unsigned int nt,unsigned int **t,
				 Tcolor *c,unsigned int bs,Tpolyhedron *p);

/** 
   \brief Used for objects that failed to initialize.

   Denotes geometric objects that are defined but can not be displayed
   (i.e., boxes with size 0). It is not worth to add such objects
   to any mechanism.

   \param p The object to query.

   \return TRUE if it is empty.
*/
boolean EmptyPolyhedron(Tpolyhedron *p);

/** 
   \brief Simplifies a polyhedron
   
   Simplifies a polyhedron. Right now we only elimiate repeated vertices in (C)OFFs.

   \param p The polyhedron to simplify.
*/
void SimplifyPolyhedron(Tpolyhedron *p);

/** 
   \brief Constructor.

   Defines an triangular prism.
   Typically used to define triangles with some thick.

   \param p1 First point of the base of the prism 
   \param p2 Second point of the base of the prism 
   \param p3 Third poitn of the base of the prism 
   \param h Heigth of the prism 
   \param c The color of the sphere.
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void NewTriangularPrism(double *p1,double *p2,double *p3,
			double h,
			Tcolor *c,unsigned int bs,Tpolyhedron *p);
/** 
   \brief Constructor.

   Defines an axis aligned box.
   The box is actually defined as an OFF. So, this function is just a convenient
   way to define OFFs for this simple shape.

   \param xl The lower coordinate along the X axis.
   \param yl The lower coordinate along the Y axis.
   \param zl The lower coordinate along the Z axis.
   \param xu The upper coordinate along the X axis.
   \param yu The upper coordinate along the Y axis.
   \param zu The upper coordinate along the Z axis.
   \param c The color of the sphere.
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void NewBox(double xl,double yl,double zl,
	    double xu,double yu,double zu,
	    Tcolor *c,unsigned int bs,Tpolyhedron *p);

/** 
   \brief Constructor.

   Defines a sphere (and its polyhedric approximation for collision detection).

   \param r The radius of the sphere.
   \param center The center of the sphere.
   \param c The color of the sphere.
   \param gr The granularity to define approximating polyhedrons for the sphere. 
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void NewSphere(double r,double *center,Tcolor *c,
	       unsigned int gr,unsigned int bs,Tpolyhedron *p);

/** 
   \brief Constructor.

   Defines a cylinder (and its polyhedric approximation for collision detection).

   \param r The radius of the cylinder.
   \param p1 The initial point of the cylinder axis.
   \param p2 The final point of the cylinder axis.
   \param c The color of the cylinder.
   \param gr The granularity to define approximating polyhedrons for the cylinder. 
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void NewCylinder(double r,double *p1,double *p2,Tcolor *c,
		 unsigned int gr,unsigned int bs,Tpolyhedron *p);

/** 
   \brief Constructor.

   Defines a line.

   \param p1 The initial point of the line.
   \param p2 The final point of the line.
   \param c The color of the line.
   \param bs Status of the body: NORMAL, HIDDEN, DECOR.
   \param p The polyhedron to create.
*/
void NewLine(double *p1,double *p2,Tcolor *c,
	     unsigned int bs,Tpolyhedron *p);

/** 
   \brief Constructor.

   Defines a set of segments.

   \param n The number of points defining the segmetns
   \param x The x components of the segmets (2 entries per segment).
   \param y The x components of the segmets (2 entries per segment).
   \param z The x components of the segmets (2 entries per segment).
   \param c The color of the set of segments.
   \param p The polyhedron to create.
*/
void NewSegments(unsigned int n,double *x,double *y,double *z,Tcolor *c,
		 Tpolyhedron *p);

/** 
    \brief Defines a spring.

    Defines a polyline that resembles a spring. This is used to get
    nice plots in tensegrites.

    The spring is always aligned with the X axis and rooted
    at the origin. It has a initial segment, a set of loops
    and a final segment.

    \param length The length of the spring (along the X axis
                  from 0).
    \param start Fraction of the length before the spring loops.
    \param rad Radius of the spring loops.
    \param lps Number of loops of the spring. If 0, 80 loops
               are defined.
    \param c The color of the spring.
    \param p The polyhedron to create.
*/
void NewSpring(double length,double start,double rad,unsigned int lps,
	       Tcolor *c,Tpolyhedron *p);

/** 
   \brief Copy constructor.

   Defines a polyhedron from another polyhedron.

   \param p_dst The polyhedron to define.
   \param p_src The polyhedron from where to copy.
*/
void CopyPolyhedron(Tpolyhedron *p_dst,Tpolyhedron *p_src);

/** 
   \brief Applies a homogenoeus transform to a polyhedron.

   Applies a homogenoeus transform to a polyhedron.

   \param t The transform to apply.
   \param p The polyhedron to transform.
   
*/
void TransformPolyhedron(THTransform *t,Tpolyhedron *p);

/** 
    \brief Gets the center of the spheres.

     Gets the center of the spheres. When applied to other type
     of polyhedrons an error is triggered.

     \param c 3D vector where to return the center.
     \param p The (sphere) polyhedron.
*/
void GetPolyhedronCenter(double *c,Tpolyhedron *p);

/** 
   \brief Retrives the type of a polyhedron.

   Retrives the type of a polyhedron.

   \param p The polyhedron to query.

   \return The type of the polyhedron: OFF, SPHERE, CYLINDER, LINE, SEGMENTS.
*/
unsigned int GetPolyhedronType(Tpolyhedron *p);

/** 
   \brief Changes the color of a polyhedron.

   Changes the color of a polyhedron.

   \param c The new color for the polyhedron.
   \param p The polyhedron to update.
*/
void SetPolyhedronColor(Tcolor *c,Tpolyhedron *p);

/** 
   \brief Gets the color of a polyhedron.

   Gets the color of a polyhedron.

   \param c The color of the polyhedron.
   \param p The polyhedron to query.
*/
void GetPolyhedronColor(Tcolor *c,Tpolyhedron *p);

/** 
   \brief Gets the status of a polyhedron (NORMAL, HIDDEN, DECOR).

   Gets the status of a polyhedron (NORMAL, HIDDEN, DECOR).

   \param p The polyhedron to query.

   \return The status of a polyhedron.
*/
unsigned int GetPolyhedronStatus(Tpolyhedron *p);

/** 
  \brief Gets the OFF information.

  Returns the OFF information defining a shape (an OFF is the format
  for polyhedrons used in Geomview). Note that this can also be used
  for spheres and cylinders since they also have an OFF defined (a polygon 
  approximating them).

  This function returns pointers to the internal structures in the polyhedron.
  Use them with care (for query but without modifying them)

  \param nv Number of vertexes in the OFF.
  \param v Vertexes defining the OFF.
  \param nf Number of faces in the OFF.
  \param nvf Number of vertexes for each face.
  \param fv The index of the vertexes for each face.
  \param p The polyhedron.
*/
void GetOFFInfo(unsigned int *nv,double ***v,unsigned int *nf,
		unsigned int **nvf,unsigned int ***fv,Tpolyhedron *p);

/** 
   \brief Gets the number of vertexes of a polyhedron.

   Gets the number of vertexes of a polyhedron.

   \param p The polyhedron to query.

   \return The number of vertexes of a polyhedron.
*/
unsigned int GetPolyhedronNVertex(Tpolyhedron *p);

/** 
   \brief Gets a point defining a a object.

   Gets the coordinates of a point defining of a object.

   A SEGMENTS is a set of segments defined by pairs of points.
   In this case one of the points defining the segment is returned.

   A LINE is defined by two points: the initial and the end
   points of the cylinder.

   A CYLINDER is defined by two points: the initial and the end
   points of the cylinder.

   A SPHERE is defined by one point: the center of the sphere.

   For OFFs, all vertexes are considered \e defining points.

   If the polyhedron has less \e defining points than the requested
   number, this function triggers an error.

   \param i Number of the defining point to retrive.
   \param point Space to store the three coordinates of the requested vertex.
   \param p The polyhedron to query.
*/
void GetPolyhedronDefiningPoint(unsigned int i,double *point,Tpolyhedron *p);

/** 
   \brief Returns the granularity used in the definition of the object.

   Returns the granularity used in the definition of the object. 

   \param p The polyhedron to query.

   \return The granularity used in the object definition, if any.
*/
double GetPolyhedronGranularity(Tpolyhedron *p);

/** 
   \brief Returns the radius used in the definition of the object.

   Returns the radius used in the definition of the object. This function
   is only defined for SPHEREs and CYLINDERs. It triggers an error if used on a OFF.

   \param p The polyhedron to query.

   \return The radius used in the object definition, if any.
*/
double GetPolyhedronRadius(Tpolyhedron *p);

/** 
   \brief Gets a vertex of a polyhedron.

   Gets the coordinates of the vertex of a polyhedron.
   
   For cylinders and spheres point on the approximating OFF are
   returned.

   If the polyhedron has less vertexes than the requested
   element, this function triggers an error.

   \param i Number of the vertex to retrive.
   \param point Space to store the three coordinates of the requested vertex.
   \param p The polyhedron to query.
*/
void GetPolyhedronVertex(unsigned int i,double *point,Tpolyhedron *p);

/** 
   \brief Returns the maximum coordinate value used in a polyhedron.

   Returns the maximum coordinate value (either in X, Y, or Z) used in a 
   polyhedron. This is used in higher levels to define an over-estimate
   bounding-box of the mechanism. This bounding box is used to define the ranges for some
   of the coordinate and separating planes variables.

   \param p The polyhedron to query.

   \return The maximum coordinate value.
*/
double GetPolyhedronMaxCoordinate(Tpolyhedron *p);

/** 
   \brief Adds the polyhedron to a 3D geometry.

   Adds the polyhedron to a 3D geometry. Each object in a 3D scene
   gets an identifier that is stored in the polyhedron object for
   future reference.

   \param pt The 3D geometry where to add the polyhedron.
   \param p The polyhedron to plot.
*/
void PlotPolyhedron(Tplot3d *pt,Tpolyhedron *p);

/** 
    \brief Prints the center of a sphere to a file.
    
    Prints the center of spheres to a file. Other types of polyhedrons
    are non  considered (they are just skiped).

    This is used only whent the world represents a molecule and we want
    to store the atom (i.e., the sphere) positions into a file.

    This is also useful to get particular points from configurations
    of mechanisms (we just put a sphere on the point and then use
    \ref cuiksamples2atoms.c "cuiksamples2atoms" to convert configurations
    to samples.

    Note that the sphere centers are translated to gobal coordinates
    before printing them.

    \param f The file where to store the sphere center.
    \param t The transform to get the global coordinates of the center.
    \param p The polyhedron to process.
*/
void PolyhedronPrintCenter(FILE *f,THTransform *t,Tpolyhedron *p);

/** 
    \brief Prints the center and the radius of a sphere to a file.
    
    Prints the center of spheres and the radius to a file. Other types of polyhedrons
    are non  considered (they are just skiped).

    This is an auxiliary function of \ref LinkStoreAtoms.

    \param f The file where to store the sphere center.
    \param t The transform to get the global coordinates of the center.
    \param p The polyhedron to process.
*/
void PolyhedronPrintCenterAndRadius(FILE *f,THTransform *t,Tpolyhedron *p);

/** 
   \brief Moves an object previously added to a 3D scene.

   Moves an object previously added to a 3D scene.

   \param pt The 3D geometry where the polyhedron was added.
   \param t The homogeneous transform to apply to the polyhedron.
   \param p The polyhedron to move.
*/
void MovePolyhedron(Tplot3d *pt,THTransform *t,Tpolyhedron *p);

/** 
   \brief Stores the geometic information of a polyhedron into a file.

   Stores the geometic information of a polyhedron into a file.
   Basically, it creates a file that can be latter read using
   \ref InitPolyhedronFromFile

   \param fileName Name of the file where to store the geometric information.
   \param p The polyhedron to save.
*/
void SavePolyhedron(char *fileName,Tpolyhedron *p);

/** 
   \brief Saves meshes in dae (collada) format.

   This is a variant of \ref SavePolyhedron for meshes (OFFs) only
   that stores the mesh in collada (dae) format.

   \param fn Name of the file where to store the mesh information.
   \param p The polyhedron to save.
*/
boolean WriteDAEMesh(char *fn,Tpolyhedron *p);

/** 
   \brief Stores the polyhedron information into a file.

   Stores the polyhedron information into a file in the format 
   valid to be read by \ref InitWorldFromFile.

   Spheres and cylinders are directly written, but OFFs are stored
   in a separate file.
   
   \param f The file where to store the information.
   \param path The working folder.
   \param l Length of the name of the link. Used to indent.
   \param label Sting identifying the entity containing the polyhedron.
   \param n Identifier of the polyhedron in the link.
   \param p The polyhedron to save.
*/
void PrintPolyhedron(FILE *f,char *path,unsigned int l,char *label,
		     unsigned int n,Tpolyhedron *p);

/** 
   \brief Destructor.

   Deletes the information stored in a Tpolyhedron and frees the allocated memory.

   \param p The polyhedron to delete.
*/
void DeletePolyhedron(Tpolyhedron *p);

#endif
