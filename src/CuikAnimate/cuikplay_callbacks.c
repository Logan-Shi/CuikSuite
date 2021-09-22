#include "cuikplay.h"

#include "cuikplay_callbacks.h"
#include "cuikplay_interface.h"
#include "cuikplay_support.h"

#include <gtk/gtk.h>

#include <sys/time.h>

/**  
    \file src/CuikAnimate/cuikplay_callbacks.c

    \brief Implementation of the GTK callback functions for cuikplay.

    Implementation of the GTK callback functions for \ref cuikplay.c "cuikplay".

    \sa cuikplay_callbacks.h
*/

void on_cuikplay_play_clicked(GtkButton *button,
			      gpointer user_data)
{
  TCuikPlayControl *c;

  c=(TCuikPlayControl *)user_data;

  if (c->currentFrame<c->maxFrame)
    {
      double t,delay;
      
      c->mode=PLAYING; 

      /* time at which current frame was displayed (right now) */
      if (c->delay!=NULL)
	delay=c->delay[c->currentFrame+1];
      else
 	delay=c->defaultDelay;
      GET_TIME(t);
      c->nextTime=t+delay;
      #if (_DEBUG>1)
        fprintf(stderr,">> Entering in PLAY mode\n");
        fprintf(stderr,">> Next frame (%u) has to be displayed at %f (%f+%f)\n",c->currentFrame+1,c->nextTime,t,delay);
      #endif
    }
}

void on_cuikplay_pause_clicked(GtkButton *button,
			       gpointer user_data)
{
  TCuikPlayControl *c;

  c=(TCuikPlayControl *)user_data;
  c->mode=PAUSED;
  #if (_DEBUG>1)
    fprintf(stderr,">> Entering in PAUSE mode\n");
  #endif
}

void on_cuikplay_slider_changed(GtkRange *range,
				gpointer user_data)
{
  TCuikPlayControl *c;
  gdouble v;

  c=(TCuikPlayControl *)user_data;

  v=gtk_range_get_value(range);
  c->nextFrame=(unsigned int)v;

  #if (_DEBUG>1)
    fprintf(stderr,">> Jumping to frame: %u\n",c->nextFrame);
  #endif
}

void on_cuikplay_quit(GtkButton *button,
		      gpointer user_data)

{
  TCuikPlayControl *c;

  c=(TCuikPlayControl *)user_data;
  c->end=TRUE;
}
