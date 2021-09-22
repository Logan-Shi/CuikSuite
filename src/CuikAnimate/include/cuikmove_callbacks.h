#ifndef CUIKMOVECALLBACKSH
#define CUIKMOVECALLBACKSH

#include <gtk/gtk.h>

/** 
    \file src/CuikAnimate/include/cuikmove_callbacks.h

    \brief Headers of the GTK callback functions for \ref cuikmove.c "cuikmove".

    Headers of the GTK callback functions for \ref cuikmove.c "cuikmove".

    \sa cuikmove_callbacks.c
*/


/** 
   \brief Callback function for the slider bar.
   
   Callback function for the slider bar: it is called whenever the
   slider value is changed.

   \param range The pointer to the GTK range.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikmove.c "cuikmove".
*/
void on_cuikmove_slider_changed(GtkRange *range,
				gpointer user_data);


/** 
   \brief Callback function for the quit button.
   
   Callback function for the quit button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikmove.c "cuikmove".
*/
void on_cuikmove_quit(GtkButton *button,
		      gpointer user_data);

/** 
   \brief Callback function for the save button.
   
   Callback function for the save button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikmove.c "cuikmove".
*/
void on_cuikmove_save(GtkButton *button,
		      gpointer user_data);


#endif
