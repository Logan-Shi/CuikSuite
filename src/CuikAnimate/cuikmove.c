#include "cuikmove.h"

#include "world.h"
#include "interval.h"
#include "defines.h"
#include "error.h"

#include "cuikmove_interface.h"
#include "cuikplay_support.h"

#include <gtk/gtk.h>

#include <string.h>
#include <unistd.h>
#include <time.h>

/** \file cuikmove.c

    \brief Main body of the \ref cuikmove.c "cuikmove" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikmove    [label="cuikmove"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      dof     [label="dof"     color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"     color="#ff9999" ];
      matlab  [label="GenerateContactEquations.m"     color="#ff9999" ];

      param -> cuikmove
      world -> cuikmove
      dof -> cuikmove
      cuikmove -> sol;
      cuikmove -> dof;
      cuikmove -> matlab;
    }
    \enddot
    </center>

    This application allows to interactively move a mechanism.

    This application produces a stream that must be redirected to actually
    see the animation. This is automatially done by the cuikmove
    script (see the \ref scripts.txt "scripts" folder).
*/


/** 
   \brief Main body of the \ref cuikmove.c "cuikmove"  application.

   Main body of the \ref cuikmove.c "cuikmove" application.

   Use: <br>
     - \b cuikmove \e world_name.world  \e initFiles.dof \e axes_length \e accuracy  
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e initFile: File from where to get the initial values for the dof.
                    This is optional. If not given, the center of each range
		    is used.
     - \e axes_length: Is the length for the axes for each link.<br>
                       This parameter is optional and the default value is 0.
     - \e accuracy:  Size in each step in each DOF (in decimal digits).
                     The default value is 3.
     .
   File extension is optional. The two las parameters are optional.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  
  if (argc>1)
    {
      Tworld world;
      Tparameters parameters;

      Tfilename fparam;
      Tfilename fworld;

      Tplot3d pt;
      double axesLength;

      TCuikMoveControl status;
      Tinterval range;
      unsigned int i;

      unsigned int accuracy,rep;
      boolean dynamics;

      GtkWidget *window_cuikmove;

      FILE *initFile;
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      rep=(unsigned int)(GetParameter(CT_REPRESENTATION,&parameters));
      if (rep!=REP_JOINTS)
	{
	  Warning("Changing the representation to joints (this may cause problems if the world includes user-defined equations)");
	  ChangeParameter(CT_REPRESENTATION,(double)REP_JOINTS,&parameters);
	}

      dynamics=(GetParameter(CT_DYNAMICS,&parameters)>0.5);
      if (dynamics)
	ChangeParameter(CT_DYNAMICS,0,&parameters);
      
      CreateFileName(NULL,arg[1],NULL,WORLD_EXT,&fworld);
      InitWorldFromFile(&parameters,TRUE,TRUE,arg[1],&world);

      if (argc>2)
	{
	  Tfilename finput;

	  CreateFileName(NULL,arg[2],NULL,JOINTS_EXT,&finput);
	  initFile=fopen(GetFileFullName(&finput),"r");
	  DeleteFileName(&finput);
	}
      else
	initFile=NULL;

      if (argc>3)
	axesLength=atof(arg[3]);
      else
	axesLength=0.0;

      if (argc>4)
	accuracy=atoi(arg[4]);
      else
	accuracy=3; /* about one 10th of a degree */


      status.ndof=GetWorldNDOF(&world);
      status.accuracy=accuracy;
      status.changed=TRUE;
      status.end=FALSE;
      NEW(status.min,status.ndof,double);
      NEW(status.max,status.ndof,double);
      NEW(status.dof,status.ndof,double);
      NEW(status.shown,status.ndof,boolean);
      status.nShown=0;
      for(i=0;i<status.ndof;i++)
	{
	  GetWorldRangeDOF(i,&range,&world);
	  status.min[i]=LowerLimit(&range);
	  if (initFile==NULL)
	    status.dof[i]=IntervalCenter(&range);
	  else
	    fscanf(initFile,"%lf",&(status.dof[i]));
	  status.max[i]=UpperLimit(&range);
	  status.shown[i]=(IntervalSize(&range)>ZERO);
	  if (status.shown[i]) status.nShown++;
	  DeleteInterval(&range);
	}
      status.p=&parameters;
      status.w=&world;
      status.fw=GetFileBaseName(&fworld);
      status.dynamics=dynamics;
      
      if (initFile!=NULL)
	fclose(initFile);

      gtk_disable_setlocale();
      gtk_init(&argc,&arg);
      
      window_cuikmove=create_window_cuikmove((gpointer)(&status));
      gtk_widget_show(window_cuikmove);

      InitPlot3d(NULL,FALSE,argc,arg,&pt);
      PlotWorld(&parameters,&pt,axesLength,&world); /* This initializes collision detection */
      MoveWorldDOF(&parameters,&pt,status.dof,&world);
      LookPlot3d(&pt);
      status.changed=FALSE;
      
      while(!status.end)
	{
	  if (status.changed)
	    {	      
	      MoveWorldDOF(&parameters,&pt,status.dof,&world);
	      status.changed=FALSE;
	    }

	  gtk_main_iteration_do(FALSE);
	}

      ClosePlot3d(TRUE,&pt);
      
      free(status.min);
      free(status.max);
      free(status.dof);
      free(status.shown);

      DeleteWorld(&world);
      DeleteParameters(&parameters);

      DeleteFileName(&fworld);    
      DeleteFileName(&fparam);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikmove <world>.world [<initFile>.dof <axes> <accuracy>]\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <initFile>: Optional. File from where to read the initial joint values.\n");
      fprintf(stdout,"     <axes>: Optional. Length for the axes for each link.\n");
      fprintf(stdout,"             The default value is 0, i.e., not to display them.\n");
      fprintf(stdout,"     <accurary>: Optional. Size of each step in each DOF");
      fprintf(stdout,"                 (in decimal digits).\n");
      fprintf(stdout,"                 The default value is 3.\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
