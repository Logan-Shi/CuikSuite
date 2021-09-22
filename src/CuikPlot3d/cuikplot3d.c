#include "boolean.h"
#include "plot3d.h"
#include "box.h"
#include "defines.h"
#include "filename.h"
#include "color.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>

/** \file cuikplot3d.c

    \brief Main body of the \ref cuikplot3d.c "cuikplot3d" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikplot3d    [label="cuikplot3d"  color="#99ff99" shape=ellipse];
      
      sol     [label="sol"   color="#ff9999" ];
      gcl     [label="gcl"   color="#ff9999" ];

      sol -> cuikplot3d;
      cuikplot3d -> gcl;
    }
    \enddot
    </center>

     A tool to plot solution boxes. Actually it represents 3d projections
     of the boxes in a solution set in the form of a <em>gcl</em> file that can be
     visualized using <a href="http://www.geomview.org/">geomview</a>. 

    \sa cuikplot.c 
*/


/** 
   \brief Main body of the \ref cuikplot3d.c "cuikplot3d" application.

   Main body of the \ref cuikplot3d.c "cuikplot3d" application.

   Use:<br>
       - \b cuikplot3d \e solution_name \e dimx \e dimy \e dimz \e min_size \e plot_name
       .
   where
       - \e solution_name is the file with the solutions to be ploted.
       - \e dimx, \e dimy, \e dimz  Are the three dimensions to be plotted (numbered from 1).
       - \e min_size is the minimum size for the output boxes (so that tiny boxes are 
            also visible).
       - \e plot_name is the output \e .gcl file.
       .
 
   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikplot3d command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tbox box;
  int token;
  Tplot3d plot;
  FILE *PSin; 
  Tinterval *x,*y,*z;
  unsigned int dim_x,dim_y,dim_z;
  double min_x,max_x,min_y,max_y, min_z,max_z;
  double minSize;
  Tfilename fsols,fplot;
  Tcolor plotColor;
  
  if (argc<7)
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikplot3d <filename> dimx dimy dimz min_size <plotname> \n");
      fprintf(stderr,"    <filename> the input .sol file\n");
      fprintf(stderr,"    dimx dimy dimz -> the three dimensions to be plotted (numbered from 1)\n");
      fprintf(stderr,"    min_size -> minimum size for the boxes\n");
      fprintf(stderr,"    <plotname> the output .gcl file\n");
    }
  else
    {
      CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsols);

      /*"Parse" the input parameters*/
      
      /*Input file name*/
      PSin=fopen(GetFileFullName(&fsols),"r");
      if (!PSin)
	Error("Input file can not be opened");
      #if (_DEBUG>0)
        fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      #endif

      /*Dimension on which to project*/
      dim_x=(unsigned int)atoi(arg[2]);
      dim_y=(unsigned int)atoi(arg[3]);
      dim_z=(unsigned int)atoi(arg[4]);
      
      /*Check that the dimensions are ok (positive not repeated)*/
      if ((dim_x==0)||(dim_y==0)||(dim_z==0))
	Error("Dimensions are numbered from 1\n");
      /*
      if ((dim_x==dim_y)||(dim_x==dim_z)||(dim_y==dim_z))
	Error("Plotting dimensions must be different\n");
      */
      dim_x=dim_x-1;
      dim_y=dim_y-1;
      dim_z=dim_z-1;
	  
      /*Rewin the file*/
      fclose(PSin);

      PSin=fopen(GetFileFullName(&fsols),"r");

      /*Get the minSize parameter*/
      minSize=(double)atof(arg[5]);

      /*and now we plot in 3D*/
      CreateFileName(NULL,arg[6],NULL,PLOT3D_EXT,&fplot);
      InitPlot3d(GetFileFullName(&fplot),FALSE,argc,arg,&plot);
      #if (_DEBUG>0)
        printf("Creating plot file                : %s\n",GetFileFullName(&fplot));
      #endif
      DeleteFileName(&fplot);

      NewColor(DCP3D_R,DCP3D_G,DCP3D_B,&plotColor);
      StartNew3dObject(&plotColor,&plot);
      DeleteColor(&plotColor);

      do {
	token=ReadBox(PSin,&box);
	if (token!=EOF)
	  { 
	    /*Get the interval of the box in the projection dimentions*/
	    x=GetBoxInterval(dim_x,&box);
	    y=GetBoxInterval(dim_y,&box);
	    z=GetBoxInterval(dim_z,&box);
	   
	    /*and get the extreme of the intervals*/
	    min_x=LowerLimit(x);
	    max_x=UpperLimit(x);
	    
	    min_y=LowerLimit(y);
	    max_y=UpperLimit(y);
	    
	    min_z=LowerLimit(z);
	    max_z=UpperLimit(z);

	    /* Hack to move the boxes*/
	    #if (0)
	    if (min_x>0.5)
	      {
		min_x-=M_2PI;
		max_x-=M_2PI;
	      }
	    #endif

	    /*if the box is too small we enlarge it (otherwise we have "invisible" boxes*/
	    if (((max_x-min_x)<minSize)&&
		((max_y-min_y)<minSize)&&
		((max_z-min_z)<minSize))
	      {
		double r;

		r=minSize/2;

		max_x+=r; min_x-=r;
		max_y+=r; min_y-=r;
		max_z+=r; min_z-=r;
	      }

	    /*and add the box to the plot*/

	    PlotBox3d(min_x,max_x,min_y,max_y,min_z,max_z,&plot);

	    //if (isolated)
	    //  StartNew3dObject(0,0,1,&plot);

	    DeleteBox(&box);
	  }
      } while (token!=EOF);

      ClosePlot3d(FALSE,&plot);

      DeleteFileName(&fsols);
      fclose(PSin);
    }
  
  return(EXIT_SUCCESS);
}
