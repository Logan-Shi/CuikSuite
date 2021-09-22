#include "boolean.h"
#include "plot2D.h"
#include "box.h"
#include "defines.h"
#include "filename.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>


/** \file cuikplot.c

    \brief Main body of the \ref cuikplot.c "cuikplot" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplot    [label="cuikplot"  color="#99ff99" shape=ellipse];
      
      sol     [label="sol"   color="#ff9999" ];
      fig     [label="fig"   color="#ff9999" ];

      sol -> cuikplot;
      cuikplot -> fig;
    }
    \enddot
    </center>

     A utility to generate 2d plots of boxes. The output is in 
     <a href="http://www.xfig.org/">xfig</a> format. 

    \sa cuikplot3d.c 
*/


/** 
   \brief Main body of the \ref cuikplot.c "cuikplot" application.

   Main body of the \ref cuikplot.c "cuikplot"  application.

   Use:<br>
       - \b cuikplot \e solution_name \e dimx \e dimy \e plot_name
       .
   where
       - \e solution_name is the file with the solutions to be ploted
       - \e dimx, \e dimy are the two dimensions to be plotted (numbered from 1)
       - \e plot_name is the output \e .fig file.
       .
 
   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikplot command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tbox box;
  Tplot plot;
  int token;
  FILE *PSin; 
  Tinterval *x,*y;
  unsigned int dim_x,dim_y;
  double min_x,max_x,min_y,max_y;
  unsigned int nb;
  char nx[10]; /*name for the axis to be ploted*/
  char ny[10];
  Tfilename fsols,fplot;

  if (argc<5)
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikplot <filename> dimx dimy <plotname>\n");
      fprintf(stderr,"    <filename> the input .sol file\n");
      fprintf(stderr,"    dimx dimy the two dimensions to be plotted (numbered from 1)\n");
      fprintf(stderr,"    <plotname> the output .fig file\n");
    }
  else
    {
      CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsols);
      
      /*Parse the input parameters*/

      PSin=fopen(GetFileFullName(&fsols),"r");
      if (!PSin)
	Error("Input file can not be opened");

      dim_x=(unsigned int)atoi(arg[2]);
      dim_y=(unsigned int)atoi(arg[3]);

      /*Check if the dimensions are right*/
      if ((dim_x==0)||(dim_y==0))
	Error("Dimensions are numbered from 1\n");

      if (dim_x==dim_y)
	Error("Plotting dimensions must be different\n");

      dim_x=dim_x-1;
      dim_y=dim_y-1;

      CreateFileName(NULL,arg[4],NULL,PLOT2D_EXT,&fplot);
      InitPlot(GetFileFullName(&fplot),&plot);
    
      SetOrigin(0.0,0.0,&plot);

      sprintf(nx,"V%u",dim_x);
      sprintf(ny,"V%u",dim_y);
      PlotAxis(nx,-3,3,ny,-3,3,0.5,&plot);

      nb=1;
      do {
	token=ReadBox(PSin,&box);
	
	if (token!=EOF)
	  {
	    /*Get the interval of the box in the projection dimentions*/
	    x=GetBoxInterval(dim_x,&box);
	    y=GetBoxInterval(dim_y,&box);
	    
	    /*and get the extreme of the intervals*/
	    min_x=LowerLimit(x);
	    max_x=UpperLimit(x);
	    
	    min_y=LowerLimit(y);
	    max_y=UpperLimit(y);
	    
	    PlotRectangle(min_x,max_y,max_x,min_y,&plot);
	    
	    nb++;

	    DeleteBox(&box);
	  }
      } while(token!=EOF);

      DeleteFileName(&fplot);
      DeleteFileName(&fsols);
      ClosePlot(&plot);
      fclose(PSin);
    }
  return(EXIT_SUCCESS);
}

