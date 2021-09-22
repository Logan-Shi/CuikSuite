/** \file cuikmove_interface.c

    \brief Implementation of the GTK interface functions for \ref cuikmove.c "cuikmove".

    Implementation of the GTK interface functions for \ref cuikmove.c "cuikmove".
    
    This file was automatically generated and is not documented here.
*/

/** \cond */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "cuikmove.h"

#include "cuikmove_callbacks.h"
#include "cuikmove_interface.h"
#include "cuikplay_support.h"

GtkWidget *create_window_cuikmove(gpointer status)
{
  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *hscale;
  GtkWidget *Quit;
  GtkWidget *Save;
  GtkWidget *alignment;
  GtkWidget *hbox;
  GtkWidget *image;
  GtkWidget *label;
  TCuikMoveControl *c;

  c=(TCuikMoveControl *)status;
  unsigned int i;
  char name[20];
  char *string;
  char *bstring;
  double stepSize,pageSize;
  unsigned int w,l,h,sh,k;
  GdkScreen *screen;

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  w=0;
  for(i=0;i<c->ndof;i++)
    {
      if (c->shown[i])
	{
	  GetWorldDOFLabel(i,&string,c->w);
	  if (string!=NULL)
	    {
	      l=strlen(string);
	      if (l>w) w=l;
	      free(string);
	    }
	}
    }

  screen=gtk_window_get_screen(GTK_WINDOW(window)); 
  sh=gdk_screen_get_height(screen);
  if ((35+4)*(1+c->nShown)>sh)
    h=(unsigned int)(floor((double)sh/(double)(1+c->nShown)))-4;
  else
    h=35;
  gtk_widget_set_size_request(window,250+w*10,(h+4)*(1+c->nShown));    
  gtk_container_border_width (GTK_CONTAINER(window),3);
  gtk_window_set_title(GTK_WINDOW(window),_("CuikMove"));
  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

  GLADE_HOOKUP_OBJECT_NO_REF(window,window,"window");

  g_signal_connect((gpointer)window, "destroy",
		   G_CALLBACK(on_cuikmove_quit),
		   status);

  table=gtk_table_new(c->nShown+1,2,FALSE);
  gtk_widget_show(table);
  gtk_container_add(GTK_CONTAINER(window),table);

  gtk_table_set_row_spacings(GTK_TABLE(table),2);
  gtk_table_set_col_spacings(GTK_TABLE(table),2);

  stepSize=1.0/pow(10,(double)c->accuracy);

  /***********************************************************/
  k=0;
  for(i=0;i<c->ndof;i++)
    {
      GetWorldDOFLabel(i,&string,c->w);
      //GetWorldJointLabel(i,&string,c->w);
      if (c->shown[i]) /* DOF with ct range are not shown */
	{
	  if (string!=NULL)
	    {
	      label=gtk_label_new(string);
	      NEW(bstring,strlen(string)+20,char);
	      sprintf(bstring,"<b>%s</b>",string);
	      gtk_label_set_markup(GTK_LABEL(label),bstring);
	      gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,k,k+1);
	      gtk_widget_show(label);

	      free(bstring);
	      free(string);
	    }

	  pageSize=0.01*(c->max[i]-c->min[i]);
	  hscale=gtk_hscale_new(GTK_ADJUSTMENT(gtk_adjustment_new(c->dof[i],c->min[i], 
								  c->max[i],stepSize,
								  pageSize,10*stepSize)));

	  gtk_widget_show(hscale);

	  gtk_table_attach_defaults(GTK_TABLE(table),hscale,1,2,k,k+1);

	  gtk_widget_set_size_request(hscale,250,h);
	  gtk_scale_set_draw_value(GTK_SCALE(hscale),TRUE);
	  gtk_scale_set_digits(GTK_SCALE(hscale),c->accuracy);

	  sprintf(name,"S%u",i); /* keep 'i' to have the id of the true dof */
	  gtk_widget_set_name(hscale,name);
      
	  g_signal_connect((gpointer)hscale,"value_changed",
			   G_CALLBACK(on_cuikmove_slider_changed),
			   status);

	  GLADE_HOOKUP_OBJECT(window,hscale,name);
	  k++;
	}
    }

  /***********************************************************/

  Save=gtk_button_new();
  gtk_widget_show(Save);

  gtk_table_attach_defaults(GTK_TABLE(table),Save,0,1,c->nShown,c->nShown+1);

  alignment=gtk_alignment_new(0.5,0.5,0,0);
  gtk_widget_show(alignment);
  gtk_container_add(GTK_CONTAINER(Save),alignment);

  hbox=gtk_hbox_new(FALSE,2);
  gtk_widget_show(hbox);
  gtk_container_add(GTK_CONTAINER(alignment),hbox);

  image=gtk_image_new_from_stock("gtk-save",GTK_ICON_SIZE_BUTTON);
  gtk_widget_show(image);
  gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

  label=gtk_label_new_with_mnemonic(_("Save"));
  gtk_widget_show(label);
  gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);

  g_signal_connect((gpointer)Save,"clicked",
		   G_CALLBACK (on_cuikmove_save),
		   status);

  GLADE_HOOKUP_OBJECT(window,Save,"Save");
  GLADE_HOOKUP_OBJECT(window,alignment,"alignment_save");
  GLADE_HOOKUP_OBJECT(window,hbox,"hbox_save");
  GLADE_HOOKUP_OBJECT(window,image,"image_save");
  GLADE_HOOKUP_OBJECT(window,label,"label_save");

  /***********************************************************/
  Quit=gtk_button_new();
  gtk_widget_show(Quit);

  gtk_table_attach_defaults(GTK_TABLE(table),Quit,1,2,c->nShown,c->nShown+1);

  gtk_widget_set_size_request(Quit,70,31);

  alignment=gtk_alignment_new(0.5,0.5,0,0);
  gtk_widget_show(alignment);
  gtk_container_add(GTK_CONTAINER(Quit),alignment);

  hbox=gtk_hbox_new(FALSE,2);
  gtk_widget_show(hbox);
  gtk_container_add(GTK_CONTAINER(alignment),hbox);

  image=gtk_image_new_from_stock("gtk-quit",GTK_ICON_SIZE_BUTTON);
  gtk_widget_show(image);
  gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

  label=gtk_label_new_with_mnemonic(_("Quit"));
  gtk_widget_show(label);
  gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);

  g_signal_connect((gpointer)Quit,"clicked",
		   G_CALLBACK(on_cuikmove_quit),
		   status);

  GLADE_HOOKUP_OBJECT(window,Quit,"Quit");
  GLADE_HOOKUP_OBJECT(window,alignment,"alignment_quit");
  GLADE_HOOKUP_OBJECT(window,hbox,"hbox_quit");
  GLADE_HOOKUP_OBJECT(window,image,"image_quit");
  GLADE_HOOKUP_OBJECT(window,label,"label_quit");

  /***********************************************************/

  return window;
}

/** \endcond */
