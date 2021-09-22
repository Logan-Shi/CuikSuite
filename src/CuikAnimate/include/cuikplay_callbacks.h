#ifndef CUIKPLAYCALLBACKSH
#define CUIKPLAYCALLBACKSH

#include <gtk/gtk.h>

/** 
    \file src/CuikAnimate/include/cuikplay_callbacks.h

    \brief Headers of the GTK callback functions for \ref cuikplay.c "cuikplay".

    Headers of the GTK callback functions for \ref cuikplay.c "cuikplay".
    
    \sa cuikplay_callbacks.c
*/

/** 
   \brief Callback function for the play button.
   
   Callback function for the play button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikplay.c "cuikplay".
*/
void on_cuikplay_play_clicked(GtkButton *button,
			      gpointer user_data);

/** 
   \brief Callback function for the pause button.
   
   Callback function for the pause button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikplay.c "cuikplay".
*/
void on_cuikplay_pause_clicked(GtkButton *button,
			       gpointer user_data);

/** 
   \brief Callback function for the quit button.
   
   Callback function for the quit button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikplay.c "cuikplay".
*/
void on_cuikplay_quit(GtkButton *button,
		      gpointer user_data);

/** 
   \brief Callback function for the slider bar.
   
   Callback function for the slider bar: it is called whenever the
   slider value is changed.

   \param range The pointer to the GTK range.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikplay.c "cuikplay".
*/
void on_cuikplay_slider_changed(GtkRange *range,
				gpointer user_data);

#endif
