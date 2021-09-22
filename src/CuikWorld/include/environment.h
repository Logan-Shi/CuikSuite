#ifndef ENVIRONMENTH
#define ENVIRONMENTH

#include "vector.h"
#include "cuiksystem.h"
#include "polyhedron.h"
#include "link.h"
#include "plot3d.h"

/****************************************************************************/


/** 
    \file environment.h
    \brief Definition of the Tenvironment type and the associated functions.

    Definition of the Tenvironment  type and the associated functions.

    \sa Tenvironment, environment.c.
*/

/****************************************************************************/
/** \brief Initial room for obstacles. 

    Initial room for obstacles. It will be enlarged if necessary.

    \sa Tenvironment
*/
#define INIT_NUM_OBSTACLES 10
/****************************************************************************/

/** 
   \brief A collection of obstacles (convex polyhedrons) with their names.

   A collection of obstacles (convex polyhedrons) with their names.

   \sa environment.h, environment.c, Tpolyhedron.
*/
typedef struct {
  double maxCoord; /**< Maximum coordinate value used in any of the bodies of the environment. */
  Tvector names; /**< One name for each obstacle in the environment. */
  Tvector obstacles; /**< The convex polyhedron defining each obstacle. */
} Tenvironment;

/** 
   \brief Constructor.

   Creates an empty environment.

   \param e The environment to intialize.
*/
void InitEnvironment(Tenvironment *e);

/** 
   \brief Adds an obstacle (i.e., a convex polyhedron) to the environment.

   Adds an obstacle (i.e., a convex polyhedron) to the environment.
   
   \param name The name of the obstacle.
   \param o The obstacle to add to the environment.
   \param e The environment where to add the new obstacle.

   \sa Tpolyhedron, InitPolyhedronFromFile.
*/
void AddShape2Environment(char *name,Tpolyhedron *o,Tenvironment *e);

/** 
   \brief Gets the number of obstacles in the environment.

   Gets the number of obstacles in the environment.

   \param e The environment to query.

   \return The number of obstacles in the environment.
*/
unsigned int GetEnvironmentNObstacles(Tenvironment *e);

/** 
   \brief Gets the idetifier of an obstacles given its name.

   Gets the idetifier of an obstacles given its name. The identifier
   of an obstacle is its position in the vectors name/obstacles of
   included in the Tenvironment structure.

   \param name The name of the obstacle.
   \param e The environment to query.

   \return The idetifier of an obstacles given its name or NO_UINT if there
           is no obstacle with the given name.
*/
unsigned int GetObstacleID(char *name,Tenvironment *e);

/** 
   \brief Gets the name of an obstacle given its identifier.

   Gets the name of an obstacle given its identifier.

   \param i The identifier of the object to query.
   \param e The environment to query.
   
   \return A pointer to the name of the requested obstacle or NULL if there
           is no obstacle with the given identifier.
*/
char *GetObstacleName(unsigned int i,Tenvironment *e);


/** 
   \brief Gets the convex polyhedron of an obstacle given its identifier.

   Gets the convex polyhedron of an obstacle given its identifier.

   \param i The identifier of the object to query.
   \param e The environment to query.
   
   \return A pointer to the convex polyhedron of the requested obstacle or NULL if there
           is no obstacle with the given identifier.
*/
Tpolyhedron *GetObstacleShape(unsigned int i,Tenvironment *e);


/** 
   \brief Gets the status (NORMAL, HIDDEN, DECOR) of an obstacle given its identifier.

   Gets the status (NORMAL, HIDDEN, DECOR) of an obstacle given its identifier.

   \param i The identifier of the object to query.
   \param e The environment to query.
   
   \return A the status (NORMAL, HIDDEN, DECOR) of the requested obstacle or NO_UINT if there
           is no obstacle with the given identifier.
*/
unsigned int GetObstacleShapeStatus(unsigned int i,Tenvironment *e);


/** 
   \brief Gets the color of an obstacle given its identifier.

   Gets the color of an obstacle given its identifier.

   \param i The identifier of the object to query.
   \param c The color of the requested obstacle.
   \param e The environment to query.
*/
void GetObstacleColor(unsigned int i,Tcolor *c,Tenvironment *e);

/** 
   \brief Returns the sum of the maximum coordinate value for all the convex polyhedrons
          in the environment.

   Returns the sum of the maximum coordinate value (either for X,Y or Z) for all the 
   convex polyhedrons in the environment.
   This is used in higher levels to define an over-estimate
   bounding-box of the world. This bounding box is used to define the ranges for some
   of the coordinate and separating planes variables.

   \param e The environment to query.

   \return The sum of the maximum coordinate values for all bodies in the environment.
*/
double GetEnvironmentMaxCoordinate(Tenvironment *e);

/** 
   \brief Stores the environment information into a file.

   Stores the environment information into a file in the format 
   valid to be read by \ref InitWorldFromFile.
   
   \param f The file where to store the information.
   \param path The working folder.
   \param e The environment to print.
*/
void PrintEnvironment(FILE *f,char *path,Tenvironment *e);

/** 
   \brief Displays the obstacles in the environment in a 3D geometry.

   Displays the obstacles in the environment in a 3D geometry.

   \param pt The 3D geometry where the to plot the environment.
   \param e The environment to plot.
*/
void PlotEnvironment(Tplot3d *pt,Tenvironment *e);


/** 
   \brief Destructor.

   Deletes the information stored in a Tenvironment and frees the allocated memory.

   \param e The environment to delete.
*/
void DeleteEnvironment(Tenvironment *e);

#endif
