/** \file cuikexplore_interface.c

    \brief Implementation of the GTK interface functions for \ref cuikexplore.c "cuikexplore".

    Implementation of the GTK interface functions for \ref cuikexplore.c "cuikexplore".
    
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

#include "cuikexplore.h"
#include "chart.h"

#include "cuikexplore_callbacks.h"
#include "cuikexplore_interface.h"
#include "cuikplay_support.h"

GtkWidget *create_window_cuikexplore(gpointer status)
{
  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *Quit;
  GtkWidget *Save;
  GtkWidget *reset;
  GtkWidget *entry;
  GtkWidget *plus;
  GtkWidget *up;
  GtkWidget *minus;
  GtkWidget *down;
  GtkWidget *menu;
  GtkWidget *alignment;
  GtkWidget *hbox;
  GtkWidget *image;
  GtkWidget *label;
  char *string;
  TCuikexploreControl *c;
  unsigned int i,j;
  char name[200];
  unsigned int h;

  c=(TCuikexploreControl *)status;

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

  h=35;
  gtk_widget_set_size_request(window,500,(h+4)*(1+c->k)); 
  gtk_container_border_width (GTK_CONTAINER(window),3);
  gtk_window_set_title(GTK_WINDOW(window),_("Cuikexplore"));
  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

  GLADE_HOOKUP_OBJECT_NO_REF(window,window,"window");

  g_signal_connect((gpointer)window,"destroy",
		   G_CALLBACK(on_cuikexplore_quit),
		   status);

  table=gtk_table_new(c->k+1,5,FALSE);
  gtk_widget_show(table);
  gtk_container_add(GTK_CONTAINER(window),table);

  gtk_table_set_row_spacings(GTK_TABLE(table),2);
  gtk_table_set_col_spacings(GTK_TABLE(table),2);

  /***********************************************************/

  for(i=0;i<c->k;i++)
    {      
      down=gtk_button_new();
      gtk_widget_show(down);

      gtk_table_attach_defaults(GTK_TABLE(table),down,0,1,i,i+1);

      gtk_widget_set_size_request(down,50,31);

      gtk_widget_set_tooltip_text(down,"Fast backward (while pressed)");

      sprintf(name,"D%u",i);
      gtk_widget_set_name(down,name);

      alignment=gtk_alignment_new(0.5,0.5,0,0);
      gtk_widget_show(alignment);
      gtk_container_add(GTK_CONTAINER(down),alignment);

      hbox=gtk_hbox_new(FALSE,2);
      gtk_widget_show(hbox);
      gtk_container_add(GTK_CONTAINER(alignment),hbox);

      //image=gtk_image_new_from_icon_name("gtk-media-forward-rtl",GTK_ICON_SIZE_BUTTON);  
      image=gtk_image_new_from_stock("gtk-media-rewind",GTK_ICON_SIZE_BUTTON);  
      gtk_widget_show(image);
      gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

      g_signal_connect((gpointer)down,"pressed",
		       G_CALLBACK(on_cuikexplore_down_pressed),
		       status);
      g_signal_connect((gpointer)down,"released",
		       G_CALLBACK(on_cuikexplore_down_released),
		       status);


      GLADE_HOOKUP_OBJECT(window,down,name);
      sprintf(name,"AD%u",i);GLADE_HOOKUP_OBJECT(window,alignment,name);
      sprintf(name,"BD%u",i);GLADE_HOOKUP_OBJECT(window,hbox,name);
      sprintf(name,"ID%u",i);GLADE_HOOKUP_OBJECT(window,image,name);

      /*--------------------------------------*/
      minus=gtk_button_new();
      gtk_widget_show(minus);

      gtk_table_attach_defaults(GTK_TABLE(table),minus,1,2,i,i+1);

      gtk_widget_set_size_request(minus,50,31);

      gtk_widget_set_tooltip_text(minus,"One step backward");

      sprintf(name,"M%u",i);
      gtk_widget_set_name(minus,name);

      alignment=gtk_alignment_new(0.5,0.5,0,0);
      gtk_widget_show(alignment);
      gtk_container_add(GTK_CONTAINER(minus),alignment);

      hbox=gtk_hbox_new(FALSE,2);
      gtk_widget_show(hbox);
      gtk_container_add(GTK_CONTAINER(alignment),hbox);

      //image=gtk_image_new_from_icon_name("gtk-media-next-rtl",GTK_ICON_SIZE_BUTTON);  
      image=gtk_image_new_from_stock("gtk-media-previous",GTK_ICON_SIZE_BUTTON);  
      gtk_widget_show(image);
      gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

      g_signal_connect((gpointer)minus,"clicked",
		       G_CALLBACK(on_cuikexplore_minus_clicked),
		       status);

      GLADE_HOOKUP_OBJECT(window,minus,name);
      sprintf(name,"AM%u",i);GLADE_HOOKUP_OBJECT(window,alignment,name);
      sprintf(name,"BM%u",i);GLADE_HOOKUP_OBJECT(window,hbox,name);
      sprintf(name,"IM%u",i);GLADE_HOOKUP_OBJECT(window,image,name);


      /*--------------------------------------*/

      menu=gtk_combo_box_new_text();

      gtk_table_attach_defaults(GTK_TABLE(table),menu,2,3,i,i+1);

      gtk_widget_set_size_request(menu,150,31);

      gtk_widget_set_tooltip_text(menu,"Select a (not yet selected) parameter");

      sprintf(name,"O%u",i);
      gtk_widget_set_name(menu,name);

      for(j=0;j<c->d;j++)
	{
	  if (c->d2e[j]!=NO_UINT)
	    {
	      GetWorldDOFLabel(j,&string,GET_WORLD(c->w));
	      if (string==NULL)
		Error("A dof without a name?");
	      
	      /* coupled fixed/joints have no name */
	      gtk_combo_box_append_text(GTK_COMBO_BOX(menu),string);
	      free(string);
	    }
	}
      fprintf(stderr,"Setting menu %u to entry %u [%u][%u]**************\n",i,c->d2e[c->ndx[i]],c->ndx[i],i);
      gtk_combo_box_set_active(GTK_COMBO_BOX(menu),c->d2e[c->ndx[i]]);

      gtk_widget_show(menu);

      g_signal_connect((gpointer)menu,"changed",
		       G_CALLBACK(on_cuikexplore_menu_changed),
		       status);
      
      GLADE_HOOKUP_OBJECT(window,menu,name);

      /*--------------------------------------*/
      plus=gtk_button_new();
      gtk_widget_show(plus);

      gtk_table_attach_defaults(GTK_TABLE(table),plus,3,4,i,i+1);

      gtk_widget_set_size_request(plus,50,31);

      gtk_widget_set_tooltip_text(plus,"One step forward");

      sprintf(name,"P%u",i);
      gtk_widget_set_name(plus,name);

      alignment=gtk_alignment_new(0.5,0.5,0,0);
      gtk_widget_show(alignment);
      gtk_container_add(GTK_CONTAINER(plus),alignment);

      hbox=gtk_hbox_new(FALSE,2);
      gtk_widget_show(hbox);
      gtk_container_add(GTK_CONTAINER(alignment),hbox);

      //image=gtk_image_new_from_icon_name("gtk-media-next-ltr",GTK_ICON_SIZE_BUTTON);
      image=gtk_image_new_from_stock("gtk-media-next",GTK_ICON_SIZE_BUTTON);  
      gtk_widget_show(image);
      gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

      g_signal_connect((gpointer)plus,"clicked",
		       G_CALLBACK (on_cuikexplore_plus_clicked),
		       status);

      GLADE_HOOKUP_OBJECT(window,plus,name);
      sprintf(name,"AP%u",i);GLADE_HOOKUP_OBJECT(window,alignment,name);
      sprintf(name,"BP%u",i);GLADE_HOOKUP_OBJECT(window,hbox,name);
      sprintf(name,"IP%u",i);GLADE_HOOKUP_OBJECT(window,image,name);

      /*--------------------------------------*/
      up=gtk_button_new();
      gtk_widget_show(up);

      gtk_table_attach_defaults(GTK_TABLE(table),up,4,5,i,i+1);

      gtk_widget_set_size_request(up,50,31);

      gtk_widget_set_tooltip_text(up,"Fast forward (while pressed)");
  
      sprintf(name,"U%u",i);
      gtk_widget_set_name(up,name);

      alignment=gtk_alignment_new(0.5,0.5,0,0);
      gtk_widget_show(alignment);
      gtk_container_add(GTK_CONTAINER(up),alignment);

      hbox=gtk_hbox_new(FALSE,2);
      gtk_widget_show(hbox);
      gtk_container_add(GTK_CONTAINER(alignment),hbox);

      //image=gtk_image_new_from_icon_name("gtk-media-forward-ltr",GTK_ICON_SIZE_BUTTON);
      image=gtk_image_new_from_stock("gtk-media-forward",GTK_ICON_SIZE_BUTTON);
      gtk_widget_show(image);
      gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

      g_signal_connect((gpointer)up,"pressed",
		       G_CALLBACK (on_cuikexplore_up_pressed),
		       status);
      g_signal_connect((gpointer)up,"released",
		       G_CALLBACK (on_cuikexplore_up_released),
		       status);

      GLADE_HOOKUP_OBJECT(window,up,name);
      sprintf(name,"AU%u",i);GLADE_HOOKUP_OBJECT(window,alignment,name);
      sprintf(name,"BU%u",i);GLADE_HOOKUP_OBJECT(window,hbox,name);
      sprintf(name,"IU%u",i);GLADE_HOOKUP_OBJECT(window,image,name);
    }

  /***********************************************************/

  Save=gtk_button_new();
  gtk_widget_show(Save);

  gtk_table_attach_defaults(GTK_TABLE(table),Save,0,1,c->k,c->k+1);

  gtk_widget_set_size_request(Save,50,31);

  gtk_widget_set_tooltip_text(Save,"Save the current configuration");

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
		   G_CALLBACK (on_cuikexplore_save),
		   status);

  GLADE_HOOKUP_OBJECT(window,Save,"Save");
  GLADE_HOOKUP_OBJECT(window,alignment,"alignment_save");
  GLADE_HOOKUP_OBJECT(window,hbox,"hbox_save");
  GLADE_HOOKUP_OBJECT(window,image,"image_save");
  GLADE_HOOKUP_OBJECT(window,label,"label_save");

  /***********************************************************/
  label=gtk_label_new("Step size:");
  gtk_label_set_text(GTK_LABEL(label),"Step size:");
  gtk_table_attach_defaults(GTK_TABLE(table),label,1,2,c->k,c->k+1);
  gtk_widget_show(label);

  entry=gtk_entry_new();
  
  gtk_table_attach_defaults(GTK_TABLE(table),entry,2,3,c->k,c->k+1);

  gtk_widget_set_size_request(entry,50,31);

  gtk_widget_set_tooltip_text(entry,"Set the motion step");

  sprintf(name,"%g",c->step);
  gtk_entry_set_text(GTK_ENTRY(entry),name);
  gtk_widget_show(entry);

  g_signal_connect((gpointer)entry,"activate",
		   G_CALLBACK(on_cuikexplore_step_changed),
		   status);

  GLADE_HOOKUP_OBJECT(window,entry,"Entry");
  GLADE_HOOKUP_OBJECT(window,label,"label_entry");

  /***********************************************************/
  reset=gtk_button_new();
  gtk_widget_show(reset);

  gtk_table_attach_defaults(GTK_TABLE(table),reset,3,4,c->k,c->k+1);

  gtk_widget_set_size_request(reset,50,31);

  gtk_widget_set_tooltip_text(reset,"Reset to the initial position");

  alignment=gtk_alignment_new(0.5,0.5,0,0);
  gtk_widget_show(alignment);
  gtk_container_add(GTK_CONTAINER(reset),alignment);

  hbox=gtk_hbox_new(FALSE,2);
  gtk_widget_show(hbox);
  gtk_container_add(GTK_CONTAINER(alignment),hbox);

  image=gtk_image_new_from_stock("gtk-refresh",GTK_ICON_SIZE_BUTTON);
  gtk_widget_show(image);
  gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);

  label=gtk_label_new_with_mnemonic(_("reset"));
  gtk_widget_show(label);
  gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);

  g_signal_connect((gpointer)reset,"clicked",
		   G_CALLBACK(on_cuikexplore_reset),
		   status);

  GLADE_HOOKUP_OBJECT(window,reset,"reset");
  GLADE_HOOKUP_OBJECT(window,alignment,"alignment_reset");
  GLADE_HOOKUP_OBJECT(window,hbox,"hbox_reset");
  GLADE_HOOKUP_OBJECT(window,image,"image_reset");
  GLADE_HOOKUP_OBJECT(window,label,"label_reset");

  /***********************************************************/
  Quit=gtk_button_new();
  gtk_widget_show(Quit);

  gtk_table_attach_defaults(GTK_TABLE(table),Quit,4,5,c->k,c->k+1);

  gtk_widget_set_size_request(Quit,50,31);

  gtk_widget_set_tooltip_text(Quit,"Exit cuikexplore");

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
		   G_CALLBACK(on_cuikexplore_quit),
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
