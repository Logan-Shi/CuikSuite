#ifndef PLOTH
#define PLOTH 

#include <stdio.h>

/** 
    \file plot2D.h

    \brief Module to generate 2d plots.

    Module to generate 2d plots. Right now the output is in <a href="http://www.xfig.org">xfig</a>
    format.

    This could be re-implement this using <a href="http://www.gnu.org/software/plotutils/">libplot</a>. 
    However this is not urgent at all since 2d plots are not very useful.

    \sa Tplot, plot.c, Tplot3d, plot3d.h
*/

/************************************************************************************/
/** \brief Solid line in 2d.

    Solid line in 2d.

    \sa plot.c
*/
#define SOLID_LINE   0

/** \brief Dashed line in 2d.

    Dashed line in 2d.

    \sa plot.c
*/
#define DASHED_LINE  1

/** \brief Dotted line in 2d.

    Dotted line in 2d.

    \sa plot.c
*/
#define DOTTED_LINE 2
/************************************************************************************/

/**
   \brief A 2D plot.

   A structure containing the information to plot in 2D.   
*/
typedef struct {
  FILE *f; /**< The file where to store the output. */
  double offset_x; /**< Offset along the X axis for the origin of the plot. */
  double offset_y; /**< Offset along the Y axis for the origin of the plot. */
  unsigned int line_style; /**< Line style (SOLID_LINE, DASHED_LINE, DOTTED_LINE). */
  unsigned int line_width; /**< Line width*/
  int fill_color; /**< Fill color. See SetPenColor for a list of colors. */
  int pen_color; /**< Pen color.  See SetPenColor for a list of colors. */
  int fill_intensity; /**< Fill intensity ranging from 0 to 20. */
  int depth; /**< Current depth used to draw elements */
  
} Tplot;

/**
   \brief Constructor.

   Initilizes a plot with

   \param name Name for the file where to store the plot.
   \param p The plot to initialize.
*/
void InitPlot(const char *name,Tplot *p);

/**
   \brief Changes the current line width.

   Changes the current line width. It will be used to plot elements
   from this point on.

   \param width New line width.
   \param p The plot to update.
*/
void SetLineWidth(unsigned int width,Tplot *p);
/**
   \brief Changes the current line stype.

   Changes the current line style. It will be used to plot elements
   from this point on.

   \param style New line style. Possible styles are SOLID_LINE, DASHED_LINE, DOTTED_LINE
   \param p The plot to update.

   \sa defines.h
*/
void SetLineStyle(unsigned int style,Tplot *p);
/**
   \brief Changes the current origin of the plot.

   Changes the current origin of the plot. Elements from now on will be refered
   to this new origin.

   \param offset_x New offset in x for the origin.
   \param offset_y New offset in y for the origin.
   \param p The plot to update.
*/
void SetOrigin(double offset_x,double offset_y,Tplot *p);
/**
   \brief Changes the current pen color.

   Changes the current pen color. Elements from now on will be plotted
   with this color. Possible colors are:

   - -1:default 0:black 1:blue 2:green 3:cyan 4:red 5 magenta 6 yellow
     7 white 8 blue4 9 blue3 10 blue2 11 ltblue 12 green4 12 green3 14 green2
     15 cyan4 16 cyan3 17 cyan2 18 read4 19 read3 20 read2 21 magenta4 22 magenta3
     23 magenta2 24 brown4 25 brown3 26 brown2 27 pink4 28 pink3 29 pink2 30 pink
     31 gold.
   .

   \param color The new pen color.
   \param p The plot to update.
*/
void SetPenColor(int color,Tplot *p);
/**
   \brief Changes the current fill color.

   Changes the current fill color. Elements from now on will be filled
   with this color. Possible colors are:

   - -1:default 0:black 1:blue 2:green 3:cyan 4:red 5 magenta 6 yellow
     7 white 8 blue4 9 blue3 10 blue2 11 ltblue 12 green4 12 green3 14 green2
     15 cyan4 16 cyan3 17 cyan2 18 read4 19 read3 20 read2 21 magenta4 22 magenta3
     23 magenta2 24 brown4 25 brown3 26 brown2 27 pink4 28 pink3 29 pink2 30 pink
     31 gold.
   .

   \param color The new fill color.
   \param p The plot to update.
*/
void SetFillColor(int color,Tplot *p);

/**
   \brief Changes the current fill intensity.

   Changes the current fill intensity. Elements from now on will be filled
   with this intensity. The valid ranges for intensities are [0,20] with
   0 \e no-fill and 20 \e full_fill.

   \param intensity The new fill intensity.
   \param p The plot to update.
*/
void SetFillIntensity(unsigned int intensity,Tplot *p);
/**
   \brief Changes the current plot depth.

   Changes the current plot depth. Elements from now on will be plotted
   at this depth.

   \param depth The new depth.
   \param p The plot to update.
*/
void SetDepth(unsigned int depth,Tplot *p);

/**
   \brief Plots a circle.

   Adds a circle to a plot.

   \param cx X coordinate for the center of the circle.
   \param cy Y coordinate for the center of the circle.
   \param r Radius for the circle.
   \param p The plot to update.
*/
void PlotCircle(double cx,double cy,double r,Tplot *p);
/**
   \brief Plots a rectangle.

   Adds a rectangle to a plot.

   \param x_left X-lower coordinate.
   \param y_sup Y-upper coordinate.
   \param x_right X-upper coordinate.
   \param y_inf Y-lower coordinate.
   \param p The plot to update.
*/
void PlotRectangle(double x_left,double y_sup,double x_right,double y_inf,Tplot *p);
/**
   \brief Plots a triangle.

   Adds a triangle to a plot.

   \param x1 X coordinate for the first point of the triangle.
   \param y1 Y coordinate for the first point of the triangle.
   \param x2 X coordinate for the second point of the triangle.
   \param y2 Y coordinate for the second point of the triangle.
   \param x3 X coordinate for the third point of the triangle.
   \param y3 Y coordinate for the third point of the triangle.
   \param p The plot to update.
*/
void PlotTriangle(double x1,double y1,double x2,double y2,double x3,double y3,Tplot *p);

/**
   \brief Plots a segment.

   Adds a segment to a plot.

   \param x0 X coordinate for the origin of the segment.
   \param y0 Y coordinate for the origin of the segment.
   \param x1 X coordinate for the end of the segment.
   \param y1 Y coordinate for the end of the segment.
   \param p The plot to update.
*/
void PlotLine(double x0,double y0,double x1,double y1,Tplot *p);
/**
   \brief Plots a segment with an arrow

   Adds a segment with an arrow at the end to a plot.

   \param x0 X coordinate for the origin of the arrow.
   \param y0 Y coordinate for the origin of the arrow.
   \param x1 X coordinate for the end of the arrow.
   \param y1 Y coordinate for the end of the arrow.
   \param p The plot to update.
*/
void PlotArrow(double x0,double y0,double x1,double y1,Tplot *p);
/**
   \brief Plots a text.

   Adds a text with to a plot.

   \param x X coordinate for the text.
   \param y Y coordinate for the text.
   \param text The text to plot.
   \param p The plot to update.
*/
void PlotText(double x,double y,const char *text,Tplot *p);
/**
   \brief Plots a X-Y axis.

   Adds X-Y axis to the plot.

   \param nx Label for the X axis.
   \param min_x Value at which the X axis have to start.
   \param max_x Value at which the X axis have to end.
   \param ny Label for the Y axis.
   \param min_y Value at which the Y axis have to start.
   \param max_y Value at which the Y axis have to end.
   \param step Separation between ticks along the axis.
   \param p The plot to update.
*/
void PlotAxis(const char *nx,double min_x,double max_x,
	      const char *ny,double min_y,double max_y,
	      double step,
	      Tplot *p);

/**
   \brief Destructor.

   Flushes the information to the output file, closes the file,
   and frees all the allocated memory for the plot structure.
   
   \param p The plot to close.
*/
void ClosePlot(Tplot *p);

#endif
