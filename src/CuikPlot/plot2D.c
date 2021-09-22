#include "plot2D.h"

#include "defines.h"

#include <stdio.h>
#include <stdlib.h>

/** 
    \file plot2D.c

    \brief Implementation of the functions to generate 2d plots.

    Implementation of the functions to generate 2d plots.

    \sa Tplot, plot2D.h.
*/

/**
   \brief Scale factor between centimiters and xfig units.

   Scale factor between centimiters and xfig units.
*/
#define CM2POINTS 450.0 /*number of points of each cm in Xfig*/

/**
   \brief Scale factor between  xfig units and centimiters.

   Scale factor between xfig units and centimiters.
*/
#define POINTS2CM (1.0/CM2POINTS)

/**
   \brief Converts a x-y point in R^2 into a xfig point.

   Converts a x-y point in R^2 into a xfig point.

   \param x X-coordinate for the R^2 point.
   \param y Y-coordinate for the R^2 point.
   \param p The plot.
*/
#define USER2XFIG(x,y,p) (signed int)(((p)->offset_x+(x))*CM2POINTS),\
                         (signed int)(((p)->offset_y-(y))*CM2POINTS)

/**
   \brief Writes a preamble common to all xfig elements.

   Writes a preamble common to all xfig elements with the line style, line
   width,....

   \param p The plot.
*/
#define PRINTXFIGPREAMBLE(p) fprintf((p)->f," %d %d %d %d %d -1 %d %f ",\
				     (p)->line_style,(p)->line_width,(p)->pen_color,\
				     (p)->fill_color,(p)->depth,(p)->fill_intensity,\
				     (((p)->line_style==SOLID_LINE)?0.0:4.0))

/*
 * Inits the plot structure and start the Xfig file (writes the header)
 */
void InitPlot(const char *name,Tplot *p)
{

  p->f=fopen(name,"w");
  if (!p->f)
    {
      fprintf(stderr,"File %s can not be created in function InitPlot\n",name);
      exit(1);
    }

  p->offset_x=0.0;
  p->offset_y=0.0;

  p->line_width=1;
  p->line_style=SOLID_LINE;

  p->pen_color=-1; /*default*/
  p->fill_color=-1; /*default*/
  p->fill_intensity=-1; /* no fill (20 = full intensity)*/
  p->depth=50;  /*standard depth*/

  /*print de preamble for the xfig file*/
  fprintf(p->f,"#FIG 3.2\n");
  fprintf(p->f,"Landscape\n");
  fprintf(p->f,"Center\n");
  fprintf(p->f,"Metric\n");
  fprintf(p->f,"A4\n");
  fprintf(p->f,"100.00\n");
  fprintf(p->f,"Single\n");
  fprintf(p->f,"-2\n");
  fprintf(p->f,"1200 2\n");
}

/*
 * Changhes the line width for the object that are drawn after calling this
 * function
 */
void SetLineWidth(unsigned int width,Tplot *p)
{
  p->line_width=width;
}

/*
 * Sets a new line style for the new objects
 */
void SetLineStyle(unsigned int style,Tplot *p)
{
  p->line_style=style;
}

/*
 * Defines a new coordinate frame for the objects. The offsets are defined from
 * the top left corner of the sheet (and positive towards the bottom right corner)
 * This origin modification is useful to avoid the picture to be drawn out of the 
 * sheet.
 */
void SetOrigin(double offset_x,double offset_y,Tplot *p)
{
  p->offset_x=offset_x;
  p->offset_y=offset_y;
}

void SetPenColor(int color,Tplot *p)
{
  if ((color>-2)&&(color<32))
    p->pen_color=color;
}

void SetFillColor(int color,Tplot *p)
{
  if ((color>-2)&&(color<32))
    p->fill_color=color;
}

void SetFillIntensity(unsigned int intensity,Tplot *p)
{
  if (intensity<21)
    p->fill_intensity=intensity;
}


void SetDepth(unsigned int depth,Tplot *p)
{
  p->depth=depth;
}

/*
 * Draws a circle at position cx, cy and with radius r
 */
void PlotCircle(double cx,double cy,double r,Tplot *p)
{
  fprintf(p->f,"1 3");

  PRINTXFIGPREAMBLE(p);

  fprintf(p->f,"1 0.0000 %d %d %d %d %d %d %d %d\n",
	  USER2XFIG(cx,cy,p),
	  (signed int)(r*CM2POINTS),(signed int)(r*CM2POINTS), /*1 cm radius*/
	  USER2XFIG(cx,cy,p),
	  USER2XFIG(-r,cy,p));
}

/*
 * Draws a rectangle
 */
void PlotRectangle(double x_left,double y_sup,double x_right,double y_inf,Tplot *p)
{
  fprintf(p->f,"2 2");

  PRINTXFIGPREAMBLE(p);

  fprintf(p->f,"0 0 -1 0 0 5\n");

  fprintf(p->f,"	 ");

  /*add the five (first repeated) extremes points of the rectangle*/

  fprintf(p->f,"%d %d  ",USER2XFIG(x_left -POINTS2CM,y_inf-POINTS2CM,p)); 
  fprintf(p->f,"%d %d  ",USER2XFIG(x_right+POINTS2CM,y_inf-POINTS2CM,p)); 
  fprintf(p->f,"%d %d  ",USER2XFIG(x_right+POINTS2CM,y_sup+POINTS2CM,p)); 
  fprintf(p->f,"%d %d  ",USER2XFIG(x_left -POINTS2CM,y_sup+POINTS2CM,p)); 
  fprintf(p->f,"%d %d\n",USER2XFIG(x_left -POINTS2CM,y_inf-POINTS2CM,p));

/*
  fprintf(p->f,"%d %d  ",USER2XFIG(x_left ,y_inf,p));
  fprintf(p->f,"%d %d  ",USER2XFIG(x_right,y_inf,p));
  fprintf(p->f,"%d %d  ",USER2XFIG(x_right,y_sup,p));
  fprintf(p->f,"%d %d  ",USER2XFIG(x_left ,y_sup,p));
  fprintf(p->f,"%d %d\n",USER2XFIG(x_left ,y_inf,p));
*/

  fflush(p->f);
}

void PlotTriangle(double x1,double y1,double x2,double y2,double x3,double y3,Tplot *p)
{
  
  fprintf(p->f,"2 3");

  PRINTXFIGPREAMBLE(p);

  fprintf(p->f,"0 0 -1 0 0 4\n");

  fprintf(p->f,"	 ");
  fprintf(p->f,"%d %d  ",USER2XFIG(x1,y1,p)); 
  fprintf(p->f,"%d %d  ",USER2XFIG(x2,y2,p)); 
  fprintf(p->f,"%d %d  ",USER2XFIG(x3,y3,p));  
  fprintf(p->f,"%d %d\n",USER2XFIG(x1,y1,p)); 

  fflush(p->f);
}

/*
 * Draws a line 
 */
void PlotLine(double x0,double y0,double x1,double y1,Tplot *p)
{
  fprintf(p->f,"2 1");

  PRINTXFIGPREAMBLE(p);

  fprintf(p->f," 0 0 -1 0 0 2 \n      %d %d %d %d\n",USER2XFIG(x0,y0,p),USER2XFIG(x1,y1,p));
}

/*
 * Draws an arrow with a pre-defined arrow style 
 */
void PlotArrow(double x0,double y0,double x1,double y1,Tplot *p)
{
  fprintf(p->f,"2 1");

  PRINTXFIGPREAMBLE(p);

  fprintf(p->f," 0 0 -1 1 0 2 \n      1 1 5.00 60.00 120.00 \n     %d %d %d %d\n",USER2XFIG(x0,y0,p),USER2XFIG(x1,y1,p));
}

/*
 * Writes a string at a given position (with predefined font and size (14 points))
 */
void PlotText(double x,double y,const char *text,Tplot *p)
{
  fprintf(p->f,"4 0 0 50 0 0 14 0.0000 4 150 150 %d %d %s\\001\n",USER2XFIG(x,y,p),text);
}

/*
 * Draw X.Y axis naming axis as 'nx' and 'ny'
 */
void PlotAxis(const char *nx,double min_x,double max_x,
	      const char *ny,double min_y,double max_y,
	      double step,
	      Tplot *p)
{
  signed int i;

  /*print the axis*/
  SetLineStyle(SOLID_LINE,p);

  PlotArrow(min_x,0.0,max_x,0.0,p);
  PlotText(max_x+0.5,0.0,nx,p);

  for(i=(signed int)(min_x/step);i<(signed int)(max_x/step);i++)
    PlotLine(1.0*i*step,-0.1*step,1.0*i*step,0.1*step,p);

  PlotArrow(0.0,min_y,0.0,max_y,p);
  PlotText(0.5,max_y-0.5,ny,p);

  for(i=(signed int)(min_y/step);i<(signed int)(max_y/step);i++)
    PlotLine(-0.1*step,1.0*i*step,0.1*step,1.0*i*step,p);

}

/*
 * Finishes the plot. It just draws the coordinate axis (the last defined ones) and
 * closes the file.
 */
void ClosePlot(Tplot *p)
{
  if (p->f!=stdout)
    fclose(p->f);
}
