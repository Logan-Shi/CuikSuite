#include "cuikplay.h"

#include "world.h"
#include "box_list.h"
#include "error.h"
#include "samples.h"

#include "cuikplay_interface.h"
#include "cuikplay_support.h"

#include <gtk/gtk.h>

#include <string.h>
#include <unistd.h>
#include <sys/time.h>


/** \file cuikplay.c

    \brief Main body of the \ref cuikplay.c "cuikplay" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikanimate    [label="cuikanimate"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"    color="#ff9999" ];
      cgl     [label="stdout"   color="#ff9999" ];

      param -> cuikanimate
      world -> cuikanimate
      sol -> cuikanimate
      cuikanimate -> cgl;
    }
    \enddot
    </center>

    This application allows to \e play a animation. 
    This is like \ref cuikanimate.c "cuikanimate" but shows a dialog
    that allow to control the animation (play, pause, move to a particular
    frame).

    This application produces a stream that must be redirected to actually
    see the animation. This is automatially done by the cuikplayer
    script (see the \ref scripts.txt "scripts" folder).
*/


/** 
   \brief Flag to store snapshots of the animations.

   Set to 1 if you want to store snapshots during the animation.
   The snapshots are stored at /tmp/worldname_\e num.ppm where
   \e num is the frame number.
*/
#define RECORD 0


/** 
   \brief Main body of the \ref cuikplay.c "cuikplay"  application.

   Main body of the \ref cuikplay.c "cuikplay" application.

   Use: <br>
     - \b cuikplay \e world_name.world \e solutions_name.sol \e axes_length \e frame_delay 
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e solutions_name:  Is the path of solutions to be animated.
     - \e axes_length: Is the length for the axes for each link.<br>
                       This parameter is optional and the default value is 0.
     - \e frame_delay: Delay in between frames. It is useful when "animating"
                       a set of isolated solutions to make each solution to be shown
                       enough time to be inspected.<br>
		       This parameter is optional and the default value is 0.1.
     .
   File extensions are optional. 

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  
  if (argc>2)
    {
      Tworld world;
      Tparameters parameters;
      Tfilename fsols;
      Tfilename fparam;
      Tfilename fworld;

      Tlist sol_box_list;
      Titerator it;
      boolean dynamic;
      unsigned int ns,nvs;
      double **path;
      unsigned int da;
      double **actions;
      double *times; /* Time increments */
      double *atimes; /* Accumulated time */
      Tbox boxPoint,*currentBox;
      unsigned int *frameID;
      
      Tplot3d pt;

      TCuikPlayControl status;
      double frameDelay,axesLength,t,delay;
      
      GtkWidget *window,*slider;
      #if (RECORD)
        char *snapshotFile;
	unsigned int l;

	fprintf(stderr,">> RECORD MODE ON\n");
      #endif
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      CreateFileName(NULL,arg[1],NULL,WORLD_EXT,&fworld);
      InitWorldFromFile(&parameters,TRUE,TRUE,arg[1],&world);
      #if (RECORD)
        l=strlen(GetFileName(&fworld));
	NEW(snapshotFile,l+100,char);
      #endif

      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      if (LoadTrajectory(&fsols,&nvs,&ns,&path,&da,&actions,&times))
	{
	  unsigned int i;

	  if (argc>4)
	    frameDelay=atof(arg[4]);
	  else
	    frameDelay=0.05;
	  	    
	  SparsifyTrajectory(frameDelay,&frameID,&ns,path,actions,times);
	  
	  dynamic=TRUE;
	  currentBox=&boxPoint;
	  NEW(atimes,ns,double);
	  atimes[0]=0.0;
	  for(i=1;i<ns;i++)
	    atimes[i]=atimes[i-1]+times[i];
	}
      else
	{
	  DeleteFileName(&fsols);
	  CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
	  if (!ReadListOfBoxes(GetFileFullName(&fsols),&sol_box_list))
	    Error("Solution file can not be opened");
	  
	  if (argc>4)
	    frameDelay=atof(arg[4]);
	  else
	    frameDelay=DEFAULT_TIME_DELAY;
      
	  dynamic=FALSE;
	}
      
      if (argc>3)
	axesLength=atof(arg[3]);
      else
	axesLength=0;

      InitPlot3d(NULL,FALSE,argc,arg,&pt);
     
      Start3dBlock(&pt);
        PlotWorld(&parameters,&pt,axesLength,&world);

	if (dynamic)
	  InitBoxFromPoint(nvs,path[0],currentBox);
	else
	  {
	    InitIterator(&it,&sol_box_list);
	    First(&it);
	    currentBox=(Tbox *)GetCurrent(&it);
	  }

	MoveWorld(&parameters,&pt,currentBox,&world);

	if (dynamic)
	  DeleteBox(currentBox);	
      Close3dBlock(&pt);
      LookPlot3d(&pt);
      
      if (dynamic)
	status.maxFrame=ns;
      else
	status.maxFrame=ListSize(&sol_box_list);
      if (status.maxFrame==0)
	Error("Empty list of solutions");

      status.end=FALSE;
      status.mode=PAUSED;
      status.currentFrame=0;
      status.nextFrame=0;
      if (dynamic)
	status.delay=times;
      else
	status.delay=NULL;
      status.defaultDelay=frameDelay;
	
      gtk_disable_setlocale();
      gtk_init(&argc,&arg);
      
      window=create_window_cuikplay((gpointer)(&status),status.maxFrame);
      slider=lookup_widget(window,"hscale1");
      gtk_widget_show(window);

      #if (_DEBUG>1)
        fprintf(stderr,">> Max frame %u \n",status.maxFrame);
      #endif
      while(!status.end)
	{
	  if (status.mode==PLAYING) 
	    {
	      /* when we reach the end -> pause */
	      if (status.currentFrame<(status.maxFrame-1))
		{
		  /* Not yet at the end: wait until it is time to display next configuration */
		  GET_TIME(t);
		  
		  /* if it is time to move to the next frame */
		  if (t>=status.nextTime)
		    {
		      /* Move the slider to currentFrame+1 and this will trigger and
			 even that actually sets nextFrame to currentFrame+1 and
			 actually displays the frame */
		      double v;

		      #if (_DEBUG>1)
		        fprintf(stderr,">> Moving to next frame %f vs %f\n",t,status.nextTime);
		      #endif
		      
		      v=(double)(status.currentFrame+1);

		      /* Change the slider */
		      #if (_DEBUG>1)
		        fprintf(stderr,">> Moving Slider from %g to %g \n",
				gtk_range_get_value(GTK_RANGE(slider)),v);
		      #endif

		      gtk_range_set_value(GTK_RANGE(slider),v);
		    }
		}
	      else
		status.mode=PAUSED; /*PAUSE*/
	    }

	  /* check for gtk events */
	  gtk_main_iteration_do(FALSE);
	  
	  /* if we have to display a new configuration (even it not playing) */
	  if (status.currentFrame!=status.nextFrame)
	    {
	      if (status.nextFrame<status.maxFrame)
		{
		  /* not yet at the end */
		  GET_TIME(t); 

		  /* Display the solution */
		  if (dynamic)
		    {
		      fprintf(stderr,">> Displaying: %u (t:%f)\n",frameID[status.nextFrame+1],atimes[status.nextFrame]);
		      InitBoxFromPoint(nvs,path[status.nextFrame],currentBox);
		    }
		  else
		    {
		      fprintf(stderr,">> Displaying: %u\n",status.nextFrame+1);
		      MoveTo(status.nextFrame,&it);
		      currentBox=(Tbox *)GetCurrent(&it);
		    }
		  MoveWorld(&parameters,&pt,currentBox,&world);

		  if (dynamic)
		    DeleteBox(currentBox);

		  /* if necessary take a snapshot */
		  #if (RECORD)
		    sprintf(snapshotFile,"/tmp/%s_%04u",GetFileName(&fworld),
			    status.nextFrame+1);
		    Take3dSnapshot(snapshotFile,&pt);
		  #endif

		  /* if playing and still not at the end of the sequence */
		  if ((status.mode==PLAYING)&&(status.nextFrame<status.maxFrame-1))
		    {
		      /* compute the time to display next frame */
		      if (status.delay!=NULL)
			delay=status.delay[status.nextFrame+1];
		      else
			delay=status.defaultDelay;
		      GET_TIME(t);
		      /* this frame shouls have been displayed at 'status.nextTime'
		         but it has been acually shown at time 't'. This difference
		         is typically constant and due to qt and geomview delays.
		         We can somehow take into account such delay and schedule
		         next frame accordingly (assuming that this uncontrolled 
			 delay for next frame will be the same as the ones for 
			 current frame) */
		      delay-=(t-status.nextTime);
		      if (delay<0.001) delay=0.001;
		      status.nextTime=t+delay;
		      #if (_DEBUG>1)
		        fprintf(stderr,">> Next frame (%u) has to be displayed at %f (%f+%f)\n",status.nextFrame+1,status.nextTime,t,delay);
		      #endif
		    }

		  /* We already displayed the nextFrame.  It now becomes the current frame */
		  status.currentFrame=status.nextFrame;
		}
	      else
		{
		  /* if we reached the end -> pause */
		  status.currentFrame=status.nextFrame=status.maxFrame;
		  status.mode=PAUSED; /*PAUSE*/
		}
	    }
	}

      ClosePlot3d(TRUE,&pt);

      if (dynamic)
	{
	  DeleteTrajectory(ns,path,actions,times);
	  free(atimes);
	}
      else
	DeleteListOfBoxes(&sol_box_list);
      

      DeleteFileName(&fsols);      
      DeleteFileName(&fworld);    
      DeleteFileName(&fparam);
      #if (RECORD)
        free(snapshotFile);
      #endif

      DeleteWorld(&world);
      DeleteParameters(&parameters);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikplay <world>.world <solutions>.sol [<axes> <delay>]\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <solutions>:  Is the path of solutions to be animated\n");
      fprintf(stdout,"     <axes>: Optional. Length for the axes for each link.\n");
      fprintf(stdout,"             The default value is 0, i.e., not to display them.\n");
      fprintf(stdout,"     <delay>: Optional. Delay (in seconds) between frames.\n");
      fprintf(stdout,"              The default delay is 0.1 seconds.\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
