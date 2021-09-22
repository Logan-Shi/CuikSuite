#ifndef CUIKEXPLORECALLBACKSH
#define CUIKEXPLORECALLBACKSH

#include <gtk/gtk.h>

/** 
    \file src/CuikAnimate/include/cuikexplore_callbacks.h

    \brief Headers of the GTK callback functions for \ref cuikexplore.c "cuikexplore".

    Headers of the GTK callback functions for \ref cuikexplore.c "cuikexplore".

    \sa cuikexplore_callbacks.c
*/

/** 
   \brief Callback function for the plus buttons.
   
   Callback function called when a plus button is clicked 
   (pressed and released).

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_plus_clicked(GtkButton *button,
				 gpointer user_data);

/** 
   \brief Callback function for the plus buttons.
   
   Callback function called when a up button is pressed.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_up_pressed(GtkButton *button,
				 gpointer user_data);

/** 
   \brief Callback function for the plus buttons.
   
   Callback function called when a plus button is released.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_up_released(GtkButton *button,
				  gpointer user_data);

/** 
   \brief Callback function for the plus buttons.
   
   Callback function called when a minus button is clicked 
   (pressed and released).

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_minus_clicked(GtkButton *button,
				  gpointer user_data);

/** 
   \brief Callback function for the minus buttons.
   
   Callback function called when a minus button is pressed.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_down_pressed(GtkButton *button,
				  gpointer user_data);

/** 
   \brief Callback function for the plus buttons.
   
   Callback function called when a minus button is released.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_down_released(GtkButton *button,
				   gpointer user_data);

/** 
   \brief Callback function for the menus.
   
   Callback function called when one of the menus is changed.
   This implies to change the parametrization.

   \param menu The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_menu_changed(GtkComboBox *menu,
				 gpointer user_data);
/** 
   \brief Callback function for the quit button.
   
   Callback function for the quit button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_quit(GtkButton *button,
			 gpointer user_data);

/** 
   \brief Callback function for the save button.
   
   Callback function for the save button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_save(GtkButton *button,
			 gpointer user_data);

/** 
   \brief Callback function for the step entry.
   
   Callback function for the step entry.

   \param entry The pointer to the GTK entry.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_step_changed(GtkEntry *entry,
				 gpointer user_data);

/** 
   \brief Callback function for the reset button.
   
   Callback function for the reset button.

   \param button The pointer to the GTK button.
   \param user_data Pointer to the structure with the control data 
                    of \ref cuikexplore.c "cuikexplore".
*/
void on_cuikexplore_reset(GtkButton *button,
			  gpointer user_data);

#endif
