#ifndef COLORH
#define COLORH

#include "boolean.h"

#include <stdio.h>

/** 
    \file color.h

    \brief Definition of the Tcolor type and the associated functions.

    Definition of the Tcolor type and the associated functions.

    \sa Tcolor, color.c.
*/

/** 
    \brief Red.

    One of the pre-defined colors: Red.
*/
#define RED 0

/** 
    \brief Green.

    One of the pre-defined colors: Green.
*/
#define GREEN 1

/** 
    \brief Blue.

    One of the pre-defined colors: Blue.
*/
#define BLUE 2

/** 
    \brief Black.

    One of the pre-defined colors: Black.
*/
#define BLACK 3

/** 
    \brief Grey.

    One of the pre-defined colors: Grey.
*/
#define GREY 4

/** 
    \brief White.

    One of the pre-defined colors: White.
*/
#define WHITE 5

/** 
    \brief Yellow.

    One of the pre-defined colors: Yellow.
*/
#define YELLOW 6

/** 
    \brief Purple.

    One of the pre-defined colors: Purple.
*/
#define PURPLE 7

/** 
    \brief Cyan.

    One of the pre-defined colors: Gyan.
*/
#define CYAN 8

/** 
   \brief A color.

    A color defined with red, green and blue components.
*/
typedef struct {
  double r; /**< Red component for the color. */
  double g; /**< Green component for the color. */
  double b; /**< Blue component for the color. */
} Tcolor;


/** 
   \brief Constructor.

   Creates new color.

   \param r The red component for the new color.
   \param g The green component for the new color.
   \param b The blue component for the new color.
   \param c The color to intialize.
*/
void NewColor(double r,double g,double b,Tcolor *c);

/** 
   \brief Constructor.

   Creates new color.

   \param id Identifier of the color (0 for red, etc).
   \param c The color to intialize.
*/
void NewColorWithID(unsigned int id,Tcolor *c);

/** 
   \brief Copy constructor.

   Creates new color from another color.

   \param c_dst The color to create.
   \param c_src The color from where to copy.
*/
void CopyColor(Tcolor *c_dst,Tcolor *c_src);

/** 
   \brief Identifies a non-valid color.

   Identifies colors with negative values of red, green or blue.
  
   Null-color is used to define a 3d object whose color
   does not need to be set globally since the elements of in
   the 3d objec already define its color.

   \param c The color to query.

   \return TRUE if the color is null.
*/
boolean NullColor(Tcolor *c);

/** 
   \brief Identifies identical colors.

   Returns true if two colors are (almost) the same.

   \param c1 The first color to compare.
   \param c2 The second color to compare.

   \return TRUE if the two colors are (almost) identical.
*/
boolean SameColor(Tcolor *c1,Tcolor *c2);

/** 
   \brief Adds to a color.

   Creates new color by a constant factor
   to all the components of a given color.

   \param s The factor to add.
   \param c The color to modify.
*/
void Add2Color(double s,Tcolor *c);

/** 
   \brief Scales a color.

   Creates new color by scaling a existing color.
   Scale factors larger than one create lighter colors and
   scale factors below one create darker colors.

   \param s The scale factor.
   \param c The color to scale.
*/
void ScaleColor(double s,Tcolor *c);

/** 
   \brief Adds a color.

   Creates new color by adding two colors.

   \param c1 The color to add.
   \param c The color where to accumulate c1.
*/
void AccumulateColor(Tcolor *c1,Tcolor *c);

/**  
   \brief Definees a color in function of a cost.

   Defines a color in  function of a cost. The lowest cost is plot in black and
   the rest in a gradient from red to green.

   This is basically used to color atlas (and atlases triangulations) 
   with associated cost functions.

  \param cost The cost. Must be scaled in [0,1].
  \param minCost Threshold from below which the cost is considered zero. Color
                 below this cost is black.
  \param c The color to define.
*/
void CostColor(double cost,double minCost,Tcolor *c);

/** 
   \brief Changes the red component of a color.

   Changes the red component of a color.

   \param r The new red component.
   \param c The color to update.
*/
void SetRed(double r,Tcolor *c);

/** 
   \brief Changes the green component of a color.

   Changes the green component of a color.

   \param g The new green component.
   \param c The color to update.
*/
void SetGreen(double g,Tcolor *c);

/** 
   \brief Changes the blue component of a color.

   Changes the blue component of a color.

   \param b The new blue component.
   \param c The color to update.
*/
void SetBlue(double b,Tcolor *c);

/** 
   \brief Gets the red component of a color.

   Gets the red component of a color.

   \param c The color to query.
   \return The red component of the color.
*/
double GetRed(Tcolor *c);

/** 
   \brief Gets the green component of a color.

   Gets the green component of a color.

   \param c The color to query.
   \return The green component of the color.
*/
double GetGreen(Tcolor *c);

/** 
   \brief Gets the blue component of a color.

   Gets the blue component of a color.

   \param c The color to query.
   \return The blue component of the color.
*/
double GetBlue(Tcolor *c);

/** 
   \brief Prints the color.

   Prints the three components of a color in a file.
   
   The componts (red, blue, and green) are printed as
   doubles, without any separation mark. This is the way
   in which Geomview uses colors.
   
   \sa plot3d.h, Tplot3d.

   \param f The file where to write the color
   \param c The color to print.
*/
void PrintColor(FILE *f,Tcolor *c);

/** 
   \brief Destructor.

   Deletes the information stored in a Tcolor and frees the allocated memory, if any.

   \param c The color to delete.
*/
void DeleteColor(Tcolor *c);

#endif

