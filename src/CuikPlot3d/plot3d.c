#include "plot3d.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include <signal.h>

/** 
    \file plot3d.c

    \brief Implementation of the functions operating on Tplot3d.

    Implementation of the functions to generate 3d plots.

    \sa Tplot3d, plot3d.h.
*/

/** \cond */

/* Documented but not included in the doxygen documentation because it
   screws up the IRI format. */

/** 
   \brief String defining a cylinder of length one aligned with the X axis.

   String defining a cylinder of length one aligned with the X axis using
   a bezier surface. This surface is extended and rotated to draw any
   cylinder.

   \sa PlotCylinder
*/
#define CYLINDER_STRING "{INST geom { CBEZ223 2 1 0 1 1 0 0 1 0 2 1 1 1 1 1 0 1 1 2 0 1 1 0 1 0 0 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 } transforms{ = TLIST 0.5 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0.5 0 0 0 0 0 1 0 0 -1 0 0 0 0 0 1 0.5 0 0 0 0 -1 0 0 0 0 -1 0 0 0 0 1 0.5 0 0 0 0 0 -1 0 0 1 0 0 0 0 0 1}}"

/** \endcond */

#if __APPLE__
  /** 
     \brief Locks stdtout.

     Locks stdout.

     \param p The 3d plot structure.
  */
  #define LOCK_OUT(p) dispatch_semaphore_wait(p->lout,DISPATCH_TIME_FOREVER)

  /** 
     \brief Unlocks stdtout.

     Unlocks stdout.

     \param p The 3d plot structure.
  */
  #define UNLOCK_OUT(p) dispatch_semaphore_signal(p->lout)

  /** 
     \brief Locks pick info.

     Locks pick info.

     \param p The pick info structure.
  */
  #define LOCK_PICK(p) dispatch_semaphore_wait(p->lpick,DISPATCH_TIME_FOREVER)

  /** 
     \brief Unlocks stdtout.

     Unlocks stdout.

     \param p The pick info structure.
  */
  #define UNLOCK_PICK(p) dispatch_semaphore_signal(p->lpick)

#else
  /** 
     \brief Locks stdtout.

     Locks stdout.

     \param p The 3d plot structure.
  */
  #define LOCK_OUT(p) sem_wait(&(p->lout))

  /** 
     \brief Unlocks stdtout.

     Unlocks stdout.

     \param p The 3d plot structure.
  */
  #define UNLOCK_OUT(p) sem_post(&(p->lout))

  /** 
     \brief Locks pick info.

     Locks pick info.

     \param p The pick info structure.
  */
  #define LOCK_PICK(p) sem_wait(&(p->lpick))

  /** 
     \brief Unlocks pick info.

     Unlocks pinck info.

     \param p The pick info structure.
  */
  #define UNLOCK_PICK(p) sem_post(&(p->lpick))

#endif

/** 
   \brief Locks the output only at the beginnig of a top level block.

   Locks the output only at the beginnig of a top level block.

   \param p The 3d block structure.
*/
#define LOCK_OUT_LEVEL(p) if (p->blockLevel==0) LOCK_OUT(p)


/** 
   \brief Unlocks the output only at the end of a top level block.

   Unlocks the output only at the end of a top level block.

   \param p The 3d block structure.
*/
#define UNLOCK_OUT_LEVEL(p) if (p->blockLevel==0) UNLOCK_OUT(p)

/** 
    \brief Fuction picking mouse clicks on geomview.

    Fuction picking mouse clicks on geomview.
    
    This function implements an infinite loop receiving characters from geomview (from stdout)
    and 

    \param param A pointer to the associated 3d plot.
*/
void *pick(void *param);

/** 
   \brief Handles the signal reception for \ref pick

   Function called when the pick function receives a signal.

   \param sig The identifier of the received signal.
*/
void pickKill(int sig);

/** 
   \brief Prints the information retrived from a pick event.

   Prints the information retrived from a pick event.

   \param f The file where to print the info.
   \param pi The information to print.
*/
void PrintPickInfo(FILE *f,TpickInfo *pi);

/** 
   \brief Finds the next element in a pick event.

    Finds the next element in a pick event.

    \param line The text describing the pick event.
    \param k The index on the text. This is incremented.
    \param n The number of charts in the line.
*/
#define NextElement(line,k,n) {while ((k<n)&&(line[k]!='(')&&(line[k]!='n')) k++; if (k<n) k++; else Error("Buffer end in pick event");}

/** 
   \brief Finds the next number in a pick event.

    Finds the next number in a pick event.

    \param line The text describing the pick event.
    \param k The index on the text. This is incremented.
    \param n The number of charts in the line.
*/
#define NextNumber(line,k,n) {while ((k<n)&&(line[k]!=' ')) k++; if (k<n) k++; else Error("Buffer end in pick event");}


/** 
   \brief Parses a point from a picked info string.

    Parses a point (x,y,z,a) from a picked info string.

    \param line The text describing the pick event.
    \param k The index on the text. 
    \param point The point where to store the parsed information.

    \return The number of inputs actually parsed. It should be 4 if everything is correct.
*/
#define ReadPoint(line,k,point) sscanf(&(line[k]),"%lf %lf %lf %lf",&(point[0]),&(point[1]),&(point[2]),&(point[3]))

/** 
   \brief Finds the next point in a pick event.

    Finds the next point in a pick event. A point is a sequence of four numbers (x,y,z,a).

    \param line The text describing the pick event.
    \param k The index on the text. This is incremented.
    \param n The number of charts in the line.
*/
#define NextPoint(line,k,n) {unsigned int i; for(i=0;((k<n)&&(i<4));i++) NextNumber(line,k,n)}

void pickKill(int sig)
{
  if (sig==SIGUSR1)
    pthread_exit(NULL);
}

void *pick(void *param)
{
  struct sigaction action;
  int c;
  char line[1000];
  unsigned int n,k,poID;
  Tplot3d *p;
  TpickInfo *pi;

  /* Configure the signal that will be used to kill the thread */
  action.sa_handler=pickKill;
  action.sa_flags=SA_RESTART;
  sigaction(SIGUSR1,&action,NULL);

  /* Wait the pick comming from geonview */
  n=0;
  p=(Tplot3d *)param;
  pi=&(p->pickInfo);
  
  while (TRUE)
    {
      c=getchar();
      line[n]=c;
      if ((c=='\n')||(n==999))
	{
	  /* End of string (just for debug purposes) */
	  n++;
	  line[n]=0;
	  
	  //fprintf(stderr,"%s",line);
	  k=26+p->lpid; // We can skip the first part of the string

	  //Save the previous selected object
	  poID=pi->oID;

	  /* avoid interferences while updating the pick info */
	  LOCK_PICK(pi);
	  
	  // Get the object identifier
	  if (sscanf(&(line[k]),"%u",&(pi->oID))!=1)
	    Error("Can not read object identifier in pick event");

	  // Get the point
	  NextElement(line,k,n);
	  if (ReadPoint(line,k,pi->point)!=4)
	    Error("Can not read poing in pick event");

	  // Get the vertex, if any
	  NextElement(line,k,n);
	  if (ReadPoint(line,k,pi->vertex)==4)
	    pi->haveVertex=TRUE;
	  else
	    pi->haveVertex=FALSE;
	  
	  // Get the edge if any
	  NextElement(line,k,n);
	  if (ReadPoint(line,k,pi->edge[0])==4)
	    {
	      pi->haveEdge=TRUE;
	      NextPoint(line,k,n);
	      if (ReadPoint(line,k,pi->edge[1])!=4)
		Error("Can not parse second exterme of a picked edge");
	    }
	  else
	    pi->haveEdge=FALSE;

	  // Get the face, if any
	  NextElement(line,k,n);
	  if (ReadPoint(line,k,pi->face[0])==4)
	    {
	      pi->haveFace=TRUE;
	      NextPoint(line,k,n);
	      pi->nvf=1;
	      while((pi->nvf<MAX_VERTEX_FACE_PICK)&&(ReadPoint(line,k,pi->face[pi->nvf])==4))
		{
		  pi->nvf++;
		  NextPoint(line,k,n);
		}
	    }
	  else
	    pi->haveFace=FALSE;

	  //Skip the 'path to the picked primitive'
	  NextElement(line,k,n);
	  NextNumber(line,k,n);
	  
	  //Read the vertex index
	  if (!sscanf(&(line[k]),"%d",&(pi->vertexID)))
	    pi->vertexID=-1;

	  //Go to the vertex indices
	  NextElement(line,k,n);
	  if (line[k]=='i') // We have 'nil' as vertex index list
	    {
	      pi->edgeID[0]=-1;
	      pi->edgeID[1]=-1;
	    }
	  else
	    {
	      if (!sscanf(&(line[k]),"%d",&(pi->edgeID[0])))
		Error("Can not parse the first edgeID in pick event");
	      NextNumber(line,k,n);
	      if (!sscanf(&(line[k]),"%d",&(pi->edgeID[1])))
		Error("Can not parse the second edgeID in pick event");
	    }
	      
	  //Go to the face index
	  NextNumber(line,k,n);
	  if (!sscanf(&(line[k]),"%d",&(pi->faceID))) pi->faceID=-1;

	  UNLOCK_PICK(pi);
	  
	  //Now we mark the selected object
	  if (!p->inObject)
	    {
	      PrintPickInfo(stderr,pi);

	      LOCK_OUT(p);

	      /* de-select the previous object */
	      if (poID!=NO_UINT)
		fprintf(p->f,"(merge-ap sol_%s_%u {*-edge})\n",p->fileName,poID);

	      /* Selet the new one */
	      if (poID!=pi->oID)
		fprintf(p->f,"(merge-ap sol_%s_%u {*+edge material {*edgecolor 1 1 1}})\n",p->fileName,pi->oID);
	      else
		pi->oID=NO_UINT; /* if the new is the same as the previous -> none is selected */
	      
	      fflush(p->f);

	      UNLOCK_OUT(p);
	    }
	  
	  n=0;
	}
      else
	n++;
    }
}

void PrintPickInfo(FILE *f,TpickInfo *pi)
{
  if (pi->oID!=NO_UINT)
    {
      LOCK_PICK(pi);
      
      fprintf(f,"Pick info:\n");
      fprintf(f,"  Object: %u\n",pi->oID);
      
      fprintf(f,"  Point: (%f %f %f)\n",pi->point[0],pi->point[1],pi->point[2]);
      
      if (pi->haveVertex)
	fprintf(f,"  Vertex [%d]: (%f %f %f)\n",pi->vertexID,
		pi->vertex[0],pi->vertex[1],pi->vertex[2]);
      else
	fprintf(f,"  No vertex selected [%d]\n",pi->vertexID);
      
      if (pi->haveEdge)
	fprintf(f,"  Edge[%d %d]: (%f %f %f) (%f %f %f)\n",
		pi->edgeID[0],pi->edgeID[1],
		pi->edge[0][0],pi->edge[0][1],pi->edge[0][2],
		pi->edge[1][0],pi->edge[1][1],pi->edge[1][2]);
      else
	fprintf(f,"  No edge selected [%d %d]\n",pi->edgeID[0],pi->edgeID[1]);
      
      if (pi->haveFace)
	{
	  unsigned int i;
	  
	  fprintf(f,"  Face[%d]: ",pi->faceID);
	  for(i=0;i<pi->nvf;i++)
	    fprintf(f,"(%f %f %f) ",pi->face[i][0],pi->face[i][1],pi->face[i][2]);
	  fprintf(f,"\n");
	}
      else
	fprintf(f,"  No face selected [%d]\n",pi->faceID);

      UNLOCK_PICK(pi);
    }
}

void InitPlot3d(char *name,boolean axes,int argc,char **arg,Tplot3d *p)
{
  char command[200];
  unsigned int i;
  char pid[20];
  unsigned int lname;
  time_t t;
  char hostname[50];

  /* To avoid strange numerical formats (, instead of . for decimals) that confuse geomview. */
  setlocale(LC_ALL,"C");

  if (name!=NULL)
    {
      p->f=fopen(name,"w");

      if (!p->f)
	Error("Can not create output file in InitPlot3d");
    }
  else
    p->f=stdout;

  //start the ooglfile
  if (argc>0)
    {
      fprintf(p->f,"#\n# Geomview plot generated with the following command line:\n#      ");
      for(i=0;i<(unsigned int)argc;i++)
	fprintf(p->f,"%s ",arg[i]);
    }
  else
    fprintf(p->f,"#\n# Geomview plot generated");
  t=time(NULL);
  gethostname(hostname,50);
  fprintf(p->f,"\n# on %s# executed at %s\n#\n",ctime(&t),hostname);
      
  fprintf(p->f,"(progn ");
  fprintf(p->f,"(normalization World none)\n");  
  fprintf(p->f,"(bbox-draw World no)\n");

  /*do not show the main pannel of geomview*/
  /*fprintf(p->f,"(ui-panel geomview off)\n");*/

  /*show the tools pannel of geomview*/
  /*fprintf(p->f,"(ui-panel tools on)\n");*/

  fprintf(p->f,"(backcolor World 1.0 1.0 1.0)\n");  /*background color de fons*/
  if (p->f==stdout)
    fprintf(p->f,"(backcolor Camera 1.0 1.0 1.0)\n"); /*background color de fons*/

  fprintf(p->f,"(dice World %u)\n",DEFAULT_DICE); /*granularity of curbed objects*/
  fprintf(p->f," )\n");

  sprintf(pid,"_%d",(unsigned int)getpid());
  p->lpid=strlen(pid);
  if (name==NULL)
    {
      NEW(p->fileName,7+p->lpid,char);
      strcpy(p->fileName,"stdout");
      strcpy(&(p->fileName[6]),pid);
    }
  else
    {
      lname=strlen(name);
      i=lname+p->lpid+1;
      NEW(p->fileName,i,char);
      strcpy(p->fileName,name);
      strcpy(&(p->fileName[lname]),pid);
      i=0;
      while (p->fileName[i]!=0)
	{
	  if ((p->fileName[i]=='/')||(p->fileName[i]=='.'))
	    p->fileName[i]='_';
	  i++;
	}
    }

  if (axes)
    {
      //axes (we assign them identifier 0)
      fprintf(p->f,"(geometry sol_%s_0 ",p->fileName);
      if (p->f!=stdout) fclose(p->f);

      if (p->f==stdout)
	sprintf(command,"cat %s/share/axes.list",_CUIK_SUITE_MAIN_DIR);
      else
	sprintf(command,"cat %s/share/axes.list >> %s",_CUIK_SUITE_MAIN_DIR,name);
      
      system(command);

      if (p->f!=stdout) p->f=fopen(name,"a");
      fprintf(p->f," )\n");
    }

  p->nobj=0; /* Last object added to the scene */

  NewColor(DCP3D_R,DCP3D_G,DCP3D_G,&(p->color));
  
  p->inObject=FALSE;

  //Resize the camera
  fprintf(p->f,"(window Camera position 500 1500 100 1000)\n");

  p->pickInfo.oID=NO_UINT;
  if (p->f==stdout)
    {
      /* create a tread to pick mouse evens */
      if (pthread_create(&(p->thread),NULL,pick,p))
	Error("Can not create pick thread");
      fprintf(p->f,"(event-pick on)\n");
      fprintf(p->f,"(pick-invisible no)\n");
      fprintf(p->f,"(interest (pick world))\n");
    }

  p->blockLevel=0;
  
  #if __APPLE__
    p->lout=dispatch_semaphore_create(1);
    p->pickInfo.lpick=dispatch_semaphore_create(1);
  #else
    sem_init(&(p->lout),0,1);
    sem_init(&(p->pickInfo.lpick),0,1);
  #endif
}

void LookPlot3d(Tplot3d *p)
{
  if (p->inObject)
    Error("Can not modify 3d view while defining an object");
   
  LOCK_OUT_LEVEL(p);
  
  fprintf(p->f,"(look)\n");
  fflush(p->f);
  
  UNLOCK_OUT_LEVEL(p);
}

void Start3dBlock(Tplot3d *p)
{
  if (p->inObject)
    Error("Can not start a 3d block inside an object definition");
  
  LOCK_OUT_LEVEL(p);
  p->blockLevel++;
  
  fprintf(p->f,"(progn \n");
}

void Close3dBlock(Tplot3d *p)
{
  
  if (p->inObject)
    Error("Can not close a 3d block inside an object definition");

  if (p->blockLevel==0)
    Error("Closing a non-opened 3d block");
  
  fprintf(p->f,")\n");
  fflush(p->f);
  
  p->blockLevel--;
  UNLOCK_OUT_LEVEL(p);
}

void  Delete3dObject(unsigned int nobj,Tplot3d *p)
{
  LOCK_OUT_LEVEL(p);
  
  fprintf(p->f,"(delete sol_%s_%u )\n",p->fileName,nobj);
  
  UNLOCK_OUT_LEVEL(p);
}

unsigned int StartNew3dObject(Tcolor *c,Tplot3d *p)
{
  Close3dObject(p); /* Just in case we are inside an object definition */

  LOCK_OUT_LEVEL(p);
  
  p->inObject=TRUE;
  
  CopyColor(&(p->color),c);

  p->nobj++; /* We increase the object identifier (empty objects also use an identifier although they are never created) */

  fprintf(p->f,"(geometry sol_%s_%u {LIST \n",p->fileName,p->nobj); 

  return(p->nobj); /*Return the identifier that will be assigned to the new object*/
}

void Close3dObject(Tplot3d *p)
{
  if (p->inObject)
    {
      /*close the previous appearance and object, if any*/
      fprintf(p->f,"})\n"); 
      fprintf(p->f,"(merge-ap sol_%s_%u {shading flat})\n",p->fileName,p->nobj);
      
      p->inObject=FALSE;
      UNLOCK_OUT_LEVEL(p);
      
      SetColor3dObject(p->nobj,&(p->color),p);
    }
}

void Close3dObjectNoColor(Tplot3d *p)
{
  if (p->inObject)
    {
      /*close the previous appearance and object, if any*/
      fprintf(p->f,"})\n"); 
      fprintf(p->f,"(merge-ap sol_%s_%u {shading flat})\n",p->fileName,p->nobj);
      
      p->inObject=FALSE;
      
      UNLOCK_OUT_LEVEL(p);
    }
}

void SetColor3dObject(unsigned int nobj,Tcolor *c,Tplot3d *p)
{
  if (!p->inObject)
    {
      if (!NullColor(c))
	{
	  LOCK_OUT_LEVEL(p);
	  
	  fprintf(p->f,"(merge-ap sol_%s_%u {material {kd 0.75 ",p->fileName,nobj);
	  fprintf(p->f," ambient ");PrintColor(p->f,c);
	  fprintf(p->f," *diffuse ");PrintColor(p->f,c);
	  fprintf(p->f," edgecolor ");PrintColor(p->f,c);
	  fprintf(p->f,"}})\n");

	  UNLOCK_OUT_LEVEL(p);
	}
    }
}

void Delay3dObject(double t,Tplot3d *p)
{
  if (t!=0.0)
    {
      LOCK_OUT_LEVEL(p);
      
      fprintf(p->f,"(sleep-for %f)\n",t);
      
      UNLOCK_OUT_LEVEL(p);
    }
}

void Move3dObject(unsigned int nobj,THTransform *t,Tplot3d *p)
{
  if (p->inObject)
    Error("Can not move an object while defining another object");
  
  LOCK_OUT_LEVEL(p);
  
  fprintf(p->f,"(xform-set sol_%s_%u {",p->fileName,nobj);
  HTransformPrintT(p->f,t);
  fprintf(p->f,"})\n");
  
  UNLOCK_OUT_LEVEL(p);
}

void PlotBox3d(double min_x,double max_x,
	       double min_y,double max_y,
	       double min_z,double max_z,
	       Tplot3d *p)
{
  if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
  
  fprintf(p->f,"{OFF 8 6 1\n");
 
  /*vertices*/
  fprintf(p->f,"%f %f %f\n",min_x,min_y,min_z);
  fprintf(p->f,"%f %f %f\n",min_x,max_y,min_z);
  fprintf(p->f,"%f %f %f\n",max_x,max_y,min_z);
  fprintf(p->f,"%f %f %f\n",max_x,min_y,min_z);

  fprintf(p->f,"%f %f %f\n",min_x,min_y,max_z);
  fprintf(p->f,"%f %f %f\n",min_x,max_y,max_z);
  fprintf(p->f,"%f %f %f\n",max_x,max_y,max_z);
  fprintf(p->f,"%f %f %f\n",max_x,min_y,max_z);

  /*faces*/
  fprintf(p->f,"4 3 2 1 0\n");
  fprintf(p->f,"4 4 5 6 7\n");
  fprintf(p->f,"4 0 1 5 4\n"); 
  fprintf(p->f,"4 2 3 7 6\n"); 
  fprintf(p->f,"4 3 0 4 7\n");
  fprintf(p->f,"4 1 2 6 5}\n"); 

  fflush(p->f);
}

void PlotTriangle3d(double x1,double y1,double z1,
		    double x2,double y2,double z2,
		    double x3,double y3,double z3,
		    Tplot3d *p)
{
   if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
   
  /*vertices*/
  fprintf(p->f,"{OFF 3 1 1\n");
  fprintf(p->f,"%f %f %f\n",x1,y1,z1);
  fprintf(p->f,"%f %f %f\n",x2,y2,z2);
  fprintf(p->f,"%f %f %f\n",x3,y3,z3);
  
  /*faces*/
  fprintf(p->f,"3 0 1 2}\n"); 

  fflush(p->f);
}

void Plot3dObject(unsigned int nv,unsigned int nf,unsigned int ne,
		  double **v,
		  unsigned int *nvf,
		  unsigned int **fv,Tplot3d *p)
{
  unsigned int i,j;

  if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
  
  fprintf(p->f,"OFF\n");
  fprintf(p->f,"%u %u %u\n",nv,nf,ne);
  fprintf(p->f,"\n");
  for(i=0;i<nv;i++)
    fprintf(p->f,"%f %f %f\n",v[i][0],v[i][1],v[i][2]);

  fprintf(p->f,"\n");
  for(i=0;i<nf;i++)
    {
      fprintf(p->f,"%u   ",nvf[i]);
      for(j=0;j<nvf[i];j++)
	fprintf(p->f,"%u ",fv[i][j]);

      fprintf(p->f,"\n");
    }
  fprintf(p->f,"\n");
}

void Plot3dObjectWithColor(unsigned int nv,unsigned int nf,unsigned int ne,
			   double **v,
			   unsigned int *nvf,
			   unsigned int **fv,Tcolor *c,Tplot3d *p)
{
  unsigned int i,j;

  if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
  
  fprintf(p->f,"OFF\n");
  fprintf(p->f,"%u %u %u\n",nv,nf,ne);
  fprintf(p->f,"\n");
  for(i=0;i<nv;i++)
    fprintf(p->f,"%f %f %f\n",v[i][0],v[i][1],v[i][2]);

  fprintf(p->f,"\n");
  for(i=0;i<nf;i++)
    {
      fprintf(p->f,"%u   ",nvf[i]);
      for(j=0;j<nvf[i];j++)
	fprintf(p->f,"%u ",fv[i][j]);

      PrintColor(p->f,c);

      fprintf(p->f," 1 \n");
    }
  fprintf(p->f,"\n");
}

void Plot3dObjectWithColors(unsigned int nv,unsigned int nf,unsigned int ne,
			    double **v,Tcolor *c,
			    unsigned int *nvf,
			    unsigned int **fv,Tplot3d *p)
{
  unsigned int i,j;

  if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
  
  /* Disable the global color for the object so that the colors 
      provided here are actually visible. */
  NewColor(-1,-1,-1,&(p->color));

  fprintf(p->f,"COFF\n");
  fprintf(p->f,"%u %u %u\n",nv,nf,ne);
  fprintf(p->f,"\n");
  for(i=0;i<nv;i++)
    {
      fprintf(p->f,"%f %f %f ",v[i][0],v[i][1],v[i][2]);
      PrintColor(p->f,&(c[i]));
      fprintf(p->f," 1 \n");
    }

  fprintf(p->f,"\n");
  for(i=0;i<nf;i++)
    {
      fprintf(p->f,"%u   ",nvf[i]);
      for(j=0;j<nvf[i];j++)
	fprintf(p->f,"%u ",fv[i][j]);
      fprintf(p->f,"\n");
    }
  fprintf(p->f,"\n");
}

void PlotSphere(double r,double x,double y,double z,Tplot3d *p)
{
  if (!p->inObject)
    Error("Adding geometry to a non-existing object");
 
  /* Since we are inside an object definition, out is already locked */
  
  fprintf(p->f,"{SPHERE %f %f %f %f}\n",r,x,y,z);
}

void PlotCylinder(double r,double *p1,double *p2,Tplot3d *p)
{
  THTransform f;

  if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
  
  HTransformX2Vect(r,r,p1,p2,&f);

  fprintf(p->f,"{INST\n");
  fprintf(p->f,"  geom       %s \n",CYLINDER_STRING);
  fprintf(p->f,"  transform ");
  HTransformPrintT(p->f,&f);
  fprintf(p->f,"}\n");
  
  HTransformDelete(&f);
}

void PlotLine(double *p1,double *p2,Tplot3d *p)
{
  if (!p->inObject)
    Error("Adding geometry to a non-existing object");
 
  /* Since we are inside an object definition, out is already locked */
  
  fprintf(p->f,"{VECT 1 2 1 \n   2 \n   1\n");

  fprintf(p->f,"   %f %f %f\n",p1[0],p1[1],p1[2]);
  fprintf(p->f,"   %f %f %f\n",p2[0],p2[1],p2[2]);

  PrintColor(p->f,&(p->color));
  fprintf(p->f," 0}\n"); /*alpha component is 0*/

  fflush(p->f);
}


void PlotSegments(unsigned int n,double **pt,Tplot3d *p)
{
  unsigned int k,i;

  if (!p->inObject)
    Error("Adding geometry to a non-existing object");

  /* Since we are inside an object definition, out is already locked */
  
  if (n%2)
    Error("PlotSegments requires a even number of vertices");
  k=n/2;

  fprintf(p->f,"{VECT %u %u 1 \n",k,n);

  /* two vertices per line */
  for(i=0;i<k;i++)
    fprintf(p->f," 2");
  fprintf(p->f,"\n");

  /* Just one color will be provided for all polylines */
  fprintf(p->f,"1");
  for(i=1;i<k;i++)
    fprintf(p->f," 0");
  fprintf(p->f,"\n");
  
  /* The vertices */
  for(i=0;i<n;i++)
    fprintf(p->f,"   %f %f %f\n",pt[i][0],pt[i][1],pt[i][2]);

  /* the color for all segments (just one color) */
  PrintColor(p->f,&(p->color));
  fprintf(p->f," 0}\n"); /*alpha component is 0*/

  fflush(p->f);
}

void PlotVect3d(unsigned int n,
		double *x,double *y,double *z,
		Tplot3d *p)
{
  unsigned int i;

  if (!p->inObject)
    Error("Adding geometry to a non-existing object");
 
  /* Since we are inside an object definition, out is already locked */
  
  fprintf(p->f,"{VECT 1 %u 1 \n   %u \n   1\n",n,n);

  for(i=0;i<n;i++)
    fprintf(p->f,"   %f %f %f\n",x[i],y[i],z[i]);

  PrintColor(p->f,&(p->color));
  fprintf(p->f," 0}\n"); /*alpha component is 0*/

  fflush(p->f);
}

void Take3dSnapshot(char *name,Tplot3d *p)
{
  LOCK_OUT_LEVEL(p);
  
  /*fprintf(p->f,"(snapshot Camera \"| convert - %s.gif\")\n",name);*/
  fprintf(p->f,"(snapshot Camera \"%s.ppm\")\n",name);

  UNLOCK_OUT_LEVEL(p);
}

void ClosePlot3d(boolean quit,Tplot3d *p)
{
  if (p->f==stdout)
    {
      /* Quit the thread reciving pick events */
      pthread_kill(p->thread,SIGUSR1);
      if (pthread_join(p->thread,NULL))
	Error("Can not stop pick thread");
    }
  
  Close3dObject(p);
  
  while(p->blockLevel>0)
    Close3dBlock(p);

  if (quit)
    {
      LOCK_OUT(p);
      fprintf(p->f,"(quit)\n"); 
      UNLOCK_OUT(p);
    }
  
  if (p->f!=stdout)
    fclose(p->f);
  
  free(p->fileName);

  #if __APPLE__
    dispatch_release(p->lout);
    dispatch_release(p->pickInfo.lpick);
  #else
    sem_destroy(&(p->lout));
    sem_destroy(&(p->pickInfo.lpick));
  #endif
}
