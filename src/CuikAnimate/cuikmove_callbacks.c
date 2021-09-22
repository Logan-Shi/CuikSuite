#include "cuikmove.h"

#include "cuikmove_callbacks.h"
#include "cuikmove_interface.h"
#include "cuikplay_support.h"

#include <gtk/gtk.h>

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/**  
    \file src/CuikAnimate/cuikmove_callbacks.c

    \brief Implementation of the GTK callback functions for cuikmove.

    Implementation of the GTK callback functions for \ref cuikmove.c "cuikmove".

    \sa cuikmove_callbacks.h
*/

void on_cuikmove_slider_changed(GtkRange *range,
				gpointer user_data)
{
  TCuikMoveControl *c;
  signed int k;
  const char *name;
  

  c=(TCuikMoveControl *)user_data;

  name=gtk_widget_get_name(GTK_WIDGET(range));
  k=atoi(&(name[1]));

  c->dof[k]=gtk_range_get_value(range);

  fprintf(stderr,"DoF %u changed (%g)\n",k,c->dof[k]);

  c->changed=TRUE;
}

void on_cuikmove_quit(GtkButton *button,
		      gpointer user_data)
{
  TCuikMoveControl *c;

  c=(TCuikMoveControl *)user_data;
  c->end=TRUE;
}

void on_cuikmove_save(GtkButton *button,
		      gpointer user_data)
{
  Tfilename fn,fm;
  unsigned int i,n,m;
  TCuikMoveControl *c;
  Tbox b;
  double *sol;
  FILE *f;
  boolean *systemVars;
  char **varNames;

  c=(TCuikMoveControl *)user_data;

  /**/
  #if (0)
  {
    boolean done,lessError,increased;
    double d,e,e1,delta;

    done=FALSE;
    delta=0.01;
    while (!done)
      {
	d=0.0;
	e=WorldErrorFromDOFs(c->p,c->dof,c->w);
	for(i=0;i<c->ndof;i++)
	  {
	    /*Try to increse*/
	    increased=FALSE;
	    do {
	      c->dof[i]+=delta;
	      e1=WorldErrorFromDOFs(c->p,c->dof,c->w);
	      if (e1<e)
		{
		  increased=TRUE;
		  d+=(e-e1);
		  e=e1;
		  lessError=TRUE;
		}
	      else
		{
		  c->dof[i]-=delta;
		  lessError=FALSE;
		}
	    } while (lessError);

	    if (!increased)
	      {
		do {
		  c->dof[i]-=delta;
		  e1=WorldErrorFromDOFs(c->p,c->dof,c->w);
		  if (e1<e)
		    {
		      d+=(e-e1);
		      e=e1;
		      lessError=TRUE;
		    }
		  else
		    {
		      c->dof[i]+=delta;
		      lessError=FALSE;
		    }
		} while (lessError);
	      }
	  }
	fprintf(stderr,"Error %f (d: %f)\n",e,d);
		  
	if (d==0)
	  done=TRUE;
      }
    c->changed=TRUE;
  }
  #endif
  /**/

  /* Print the degrees of freedom defining the current configuration  */
  CreateFileName(NULL,c->fw,NULL,JOINTS_EXT,&fn);
  f=fopen(GetFileFullName(&fn),"w");
  if (!f)
    Error("Can not open output file for dofs from cuikmove");
  
  fprintf(stderr,"\n\n\nSaving dof to          : %s\n",GetFileFullName(&fn));

  for(i=0;i<c->ndof;i++)
    fprintf(f,"%.12f ",c->dof[i]);
  fprintf(f,"\n");

  if (c->dynamics)
    {
      for(i=0;i<c->ndof;i++)
	fprintf(f,"0 ");
      fprintf(f,"\n");
    }
  
  fclose(f);
  DeleteFileName(&fn);

  /* Now print the solution in the form of a box and in the cuik variables */
  CreateFileName(NULL,c->fw,NULL,SOL_EXT,&fn);
  f=fopen(GetFileFullName(&fn),"w");
  if (!f)
    Error("Can not open output file for solutions from cuikmove");

  fprintf(stderr,"Saving solution to     : %s\n",GetFileFullName(&fn));

  n=WorldDOF2Sol(c->p,c->dof,&sol,&b,c->w);

  m=GetWorldSystemVars(&systemVars,c->w);
  if (n!=m)
    Error("Inconsistent number of variables in on_cuikmove_save");

  NEW(varNames,n,char *);
  GetWorldVarNames(varNames,c->w);

  PrintBoxSubset(f,systemVars,varNames,&b);

  free(varNames);
  DeleteBox(&b);

  fclose(f);
  DeleteFileName(&fn);

#if (0)
  /* Now print the solution in the form of a point */
  CreateFileName(NULL,c->fw,"_kin",SAMPLE_EXT,&fn);
  f=fopen(GetFileFullName(&fn),"w");
  if (!f)
    Error("Can not open output file for samples from cuikmove");

  fprintf(stderr,"Saving sample to       : %s\n",GetFileFullName(&fn));

  for(i=0;i<n;i++)
    {
      if (systemVars[i])
	fprintf(f,"%.12f ",sol[i]);
    }
  fprintf(f,"\n\n");
  free(systemVars);

  fclose(f);
  DeleteFileName(&fn);
#endif

  free(sol);

  /* Now print the a matlab script */
  if (AnyCollision(c->w))
    {
      CreateFileName(NULL,c->fw,NULL,NULL,&fn);
      CreateFileName(GetFilePath(&fn),"matlab/GenerateContactEquations",NULL,"m",&fm);

      f=fopen(GetFileFullName(&fm),"w");
      if (!f)
	Warning("Matlab script not created (not Matlab folder)");
      else
	{
	  fprintf(stderr,"Saving matlab script to: %s\n\n\n",GetFileFullName(&fm));
	  
	  PrintWorldCollisionInfo(f,c->fw,c->w);
	  
	  fclose(f);
	}
      DeleteFileName(&fm);
      DeleteFileName(&fn);
    }
}
