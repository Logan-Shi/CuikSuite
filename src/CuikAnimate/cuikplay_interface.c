/** \file cuikplay_interface.c

    \brief Implementation of the GTK interface functions for \ref cuikplay.c "cuikplay".

    Implementation of the GTK interface functions for \ref cuikplay.c "cuikplay".
    
    This file was automatically generated and is not documented here.
*/

/** \cond */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "cuikplay_callbacks.h"
#include "cuikplay_interface.h"
#include "cuikplay_support.h"

GtkWidget *create_window_cuikplay(gpointer status,unsigned int ms)
{
  GtkWidget *window1;
  GtkWidget *hbox3;
  GtkWidget *Play;
  GtkWidget *alignment4;
  GtkWidget *hbox4;
  GtkWidget *image2;
  GtkWidget *label2;
  GtkWidget *Pause;
  GtkWidget *alignment5;
  GtkWidget *hbox5;
  GtkWidget *image3;
  GtkWidget *label3;
  GtkWidget *hscale1;
  GtkWidget *Quit;
  GtkWidget *alignment6;
  GtkWidget *hbox6;
  GtkWidget *image4;
  GtkWidget *label4;

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 500, 30);
  gtk_window_set_title (GTK_WINDOW (window1), _("CuikAnimation"));
  gtk_window_set_resizable (GTK_WINDOW (window1), FALSE);

  GLADE_HOOKUP_OBJECT_NO_REF(window1,window1,"window1");
  
  g_signal_connect((gpointer)window1,"destroy",
		   G_CALLBACK(on_cuikplay_quit),
		   status);
  
  hbox3 = gtk_hbox_new (FALSE, 3);
  gtk_widget_show (hbox3);
  gtk_container_add (GTK_CONTAINER (window1), hbox3);

  Play = gtk_button_new ();
  gtk_widget_show (Play);
  gtk_box_pack_start (GTK_BOX (hbox3), Play, FALSE, FALSE, 0);
  gtk_widget_set_size_request (Play, 70, 30);

  alignment4 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment4);
  gtk_container_add (GTK_CONTAINER (Play), alignment4);

  hbox4 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox4);
  gtk_container_add (GTK_CONTAINER (alignment4), hbox4);

  image2 = gtk_image_new_from_stock ("gtk-media-play", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image2);
  gtk_box_pack_start (GTK_BOX (hbox4), image2, FALSE, FALSE, 0);

  label2 = gtk_label_new_with_mnemonic (_("Play"));
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (hbox4), label2, FALSE, FALSE, 0);

  Pause = gtk_button_new ();
  gtk_widget_show (Pause);
  gtk_box_pack_start (GTK_BOX (hbox3), Pause, FALSE, FALSE, 0);
  gtk_widget_set_size_request (Pause, 70, 30);

  alignment5 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment5);
  gtk_container_add (GTK_CONTAINER (Pause), alignment5);

  hbox5 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox5);
  gtk_container_add (GTK_CONTAINER (alignment5), hbox5);

  image3 = gtk_image_new_from_stock ("gtk-media-pause", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image3);
  gtk_box_pack_start (GTK_BOX (hbox5), image3, FALSE, FALSE, 0);

  label3 = gtk_label_new_with_mnemonic (_("Pause"));
  gtk_widget_show (label3);
  gtk_box_pack_start (GTK_BOX (hbox5), label3, FALSE, FALSE, 0);

  hscale1 = gtk_hscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (0, 0, ms, 1, 1, 1)));
  gtk_widget_show (hscale1);
  gtk_box_pack_start (GTK_BOX (hbox3), hscale1, FALSE, FALSE, 0);
  gtk_widget_set_size_request (hscale1, 280, 20);
  gtk_scale_set_draw_value (GTK_SCALE (hscale1), FALSE);
  gtk_scale_set_digits (GTK_SCALE (hscale1), 0);

  Quit = gtk_button_new ();
  gtk_widget_show (Quit);
  gtk_box_pack_start (GTK_BOX (hbox3), Quit, FALSE, FALSE, 0);
  gtk_widget_set_size_request (Quit, 70, 30);

  alignment6 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment6);
  gtk_container_add (GTK_CONTAINER (Quit), alignment6);

  hbox6 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox6);
  gtk_container_add (GTK_CONTAINER (alignment6), hbox6);

  image4 = gtk_image_new_from_stock ("gtk-quit", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image4);
  gtk_box_pack_start (GTK_BOX (hbox6), image4, FALSE, FALSE, 0);

  label4 = gtk_label_new_with_mnemonic (_("Quit"));
  gtk_widget_show (label4);
  gtk_box_pack_start (GTK_BOX (hbox6), label4, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) Play, "clicked",
                    G_CALLBACK (on_cuikplay_play_clicked),
                    status);
  g_signal_connect ((gpointer) Pause, "clicked",
                    G_CALLBACK (on_cuikplay_pause_clicked),
                    status);
  g_signal_connect ((gpointer) hscale1, "value_changed",
                    G_CALLBACK (on_cuikplay_slider_changed),
                    status);
  g_signal_connect ((gpointer) Quit, "clicked",
                    G_CALLBACK (on_cuikplay_quit),
                    status);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT (window1, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (window1, Play, "Play");
  GLADE_HOOKUP_OBJECT (window1, alignment4, "alignment4");
  GLADE_HOOKUP_OBJECT (window1, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (window1, image2, "image2");
  GLADE_HOOKUP_OBJECT (window1, label2, "label2");
  GLADE_HOOKUP_OBJECT (window1, Pause, "Pause");
  GLADE_HOOKUP_OBJECT (window1, alignment5, "alignment5");
  GLADE_HOOKUP_OBJECT (window1, hbox5, "hbox5");
  GLADE_HOOKUP_OBJECT (window1, image3, "image3");
  GLADE_HOOKUP_OBJECT (window1, label3, "label3");
  GLADE_HOOKUP_OBJECT (window1, hscale1, "hscale1");
  GLADE_HOOKUP_OBJECT (window1, Quit, "Quit");
  GLADE_HOOKUP_OBJECT (window1, alignment6, "alignment6");
  GLADE_HOOKUP_OBJECT (window1, hbox6, "hbox6");
  GLADE_HOOKUP_OBJECT (window1, image4, "image4");
  GLADE_HOOKUP_OBJECT (window1, label4, "label4");

  return window1;
}

/** \endcond */
