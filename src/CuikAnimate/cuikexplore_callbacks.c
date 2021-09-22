#include "cuikexplore.h"

#include "cuikexplore_callbacks.h"
#include "cuikexplore_interface.h"
#include "cuikplay_support.h"

#include <gtk/gtk.h>

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/**  
    \file src/CuikAnimate/cuikexplore_callbacks.c

    \brief Implementation of the GTK callback functions for cuikexplore.

    Implementation of the GTK callback functions for \ref cuikexplore.c "cuikexplore".

    \sa cuikexplore_callbacks.h
*/

void on_cuikexplore_plus_clicked(GtkButton *button,
				 gpointer user_data)
{
  TCuikexploreControl *c;
  signed int k;
  const char *name;
  
  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(button));
  k=atoi(&(name[1]));

  c->vectDOF[c->ndx[k]]+=c->step;

  fprintf(stderr,"+[%u]\n",c->ndx[k]);

  c->changed=TRUE;
  c->oneStep=TRUE;
}

void on_cuikexplore_up_pressed(GtkButton *button,
			       gpointer user_data)
{
  TCuikexploreControl *c;
  signed int k;
  const char *name;

  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(button));
  k=atoi(&(name[1]));

  c->vectDOF[c->ndx[k]]+=c->step;

  fprintf(stderr,"<+[%u]\n",c->ndx[k]);

  c->changed=TRUE;
  c->oneStep=FALSE;
}

void on_cuikexplore_up_released(GtkButton *button,
				gpointer user_data)
{
  TCuikexploreControl *c;
  signed int k;
  const char *name;
  
  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(button));
  k=atoi(&(name[1]));

  c->vectDOF[c->ndx[k]]=0;

  fprintf(stderr,"+[%u]>\n",c->ndx[k]);

  c->changed=FALSE;
}

void on_cuikexplore_minus_clicked(GtkButton *button,
				  gpointer user_data)
{
  TCuikexploreControl *c;
  signed int k;
  const char *name;
  
  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(button));
  k=atoi(&(name[1]));

  c->vectDOF[c->ndx[k]]-=c->step;

  fprintf(stderr,"-[%u]\n",c->ndx[k]);

  c->changed=TRUE;
  c->oneStep=TRUE;
}


void on_cuikexplore_down_pressed(GtkButton *button,
				 gpointer user_data)
{
  TCuikexploreControl *c;
  signed int k;
  const char *name;
  
  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(button));
  k=atoi(&(name[1]));

  c->vectDOF[c->ndx[k]]-=c->step;

  fprintf(stderr,"<-[%u]\n",c->ndx[k]);
  c->changed=TRUE;
  c->oneStep=FALSE;
}

void on_cuikexplore_down_released(GtkButton *button,
				  gpointer user_data)
{
  TCuikexploreControl *c;
  signed int k;
  const char *name;  

  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(button));
  k=atoi(&(name[1]));

  c->vectDOF[c->ndx[k]]=0;

  fprintf(stderr,"-[%u]>\n",c->ndx[k]);

  c->changed=FALSE;
}

void on_cuikexplore_quit(GtkButton *button,
			 gpointer user_data)
{
  TCuikexploreControl *c;

  c=(TCuikexploreControl *)user_data;
  c->end=TRUE;
}

void on_cuikexplore_menu_changed(GtkComboBox *menu,
				 gpointer user_data)
{
  TCuikexploreControl *c;
  unsigned int i,k,new;
  boolean found;
  const char *name;
  
  c=(TCuikexploreControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(menu));
  k=(unsigned int)atoi(&(name[1]));

  new=c->e2d[gtk_combo_box_get_active(menu)];
  found=FALSE;
  i=0;
  while((!found)&&(i<c->k))
    {
      found=((i!=k)&&(c->ndx[i]==new));
      i++;
    }
  if (found)
    {
      fprintf(stderr,"Parameter %u is already in use\n",new);
      gtk_combo_box_set_active(menu,c->d2e[c->ndx[k]]);
    }
  else
    {
      c->ndx[k]=new; //c->d2e[gtk_combo_box_get_active(menu)];
      fprintf(stderr,"Menu[%u]=%u\n",k,new);
    }
}


void on_cuikexplore_save(GtkButton *button,
			 gpointer user_data)
{
  Tfilename fn;
  FILE *f;
  unsigned int i;
  TCuikexploreControl *c;

  c=(TCuikexploreControl *)user_data;

  if (c->rep==REP_JOINTS)
    CreateFileName(NULL,c->fw,"_explore",JOINTS_EXT,&fn);
  else
    CreateFileName(NULL,c->fw,"_explore",LINKS_EXT,&fn);
  f=fopen(GetFileFullName(&fn),"w");
  if (!f)
    Error("Can not open output file for dofs from cuikexplore");
  
  fprintf(stderr,"\n\n\nSaving configuration to     : %s\n",GetFileFullName(&fn));

  for(i=0;i<c->m;i++)
    fprintf(f,"%.16f ",c->point[i]);
  
  if (c->dynamics)
    {
      /* Zero velocity (if the original problem had dynamics) */
      for(i=0;i<c->m;i++)
	fprintf(f,"0 ");
    }
  fprintf(f,"\n");

  fclose(f);
  DeleteFileName(&fn);
}

void on_cuikexplore_step_changed(GtkEntry *entry,
				 gpointer user_data)
{
  TCuikexploreControl *c;
  double newStep;
  char string[20];

  c=(TCuikexploreControl *)user_data;
  newStep=atof(gtk_entry_get_text(entry));
  if (newStep==0)
    fprintf(stderr,"Error in the input step\n");
  else
    {
      c->step=newStep;
      fprintf(stderr,"New advance step: %g\n",c->step);
    }
  sprintf(string,"%f",c->step);
  gtk_entry_set_text(entry,string);
}

void on_cuikexplore_reset(GtkButton *button,
			  gpointer user_data)
{
  TCuikexploreControl *c;

  c=(TCuikexploreControl *)user_data;

  c->reset=TRUE;
}
