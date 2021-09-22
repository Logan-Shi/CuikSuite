#include "environment.h"

#include <string.h>

/** \file environment.c
    \brief Implementaton of the function operating on Tenvironment.
    
    Implementaton of the function operating on Tenvironment.

    \sa Tenvironment, environment.h.
*/

void InitEnvironment(Tenvironment *e)
{
  e->maxCoord=0;
  InitVector(sizeof(void *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_OBSTACLES,&(e->names));
  InitVector(sizeof(void *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_OBSTACLES,&(e->obstacles));
}

void AddShape2Environment(char *name,Tpolyhedron *o,Tenvironment *e)
{
  if (!EmptyPolyhedron(o))
    {
      char *namei;
      Tpolyhedron *pi;
      unsigned int k;
      double mc;

      NEW(namei,strlen(name)+1,char);
      strcpy(namei,name);
      k=NewVectorElement(&namei,&(e->names));

      NEW(pi,1,Tpolyhedron);
      CopyPolyhedron(pi,o);
      SetVectorElement(k,&pi,&(e->obstacles));
  
      mc=GetPolyhedronMaxCoordinate(o);
      if (mc>e->maxCoord)
	e->maxCoord=mc;
    }
}

unsigned int GetEnvironmentNObstacles(Tenvironment *e)
{
  return(VectorSize(&(e->obstacles))); /*Equal to the size of 'name' vector*/
}

unsigned int GetObstacleID(char *name,Tenvironment *e)
{
  char **namei;
  boolean found;
  unsigned int i,n;
  
  n=VectorSize(&(e->names));
  found=FALSE;
  i=0;
  while((!found)&&(i<n))
    {
      namei=(char **)GetVectorElement(i,&(e->names));
      if (namei!=NULL)
	{
	  if (strcmp(name,*namei)==0)
	    found=TRUE;
	}
      if (!found)
	i++;
    }
  if (found)
    return(i);
  else
    return(NO_UINT);
}

char *GetObstacleName(unsigned int i,Tenvironment *e)
{
  char **n;

  n=(char **)GetVectorElement(i,&(e->names));
  if (n==NULL)
    return(NULL);
  else
    return(*n);
}

Tpolyhedron *GetObstacleShape(unsigned int i,Tenvironment *e)
{
  Tpolyhedron **p;

  p=(Tpolyhedron **)GetVectorElement(i,&(e->obstacles));
  if (p==NULL)
    return(NULL);
  else
    return(*p);
}

unsigned int GetObstacleShapeStatus(unsigned int i,Tenvironment *e)
{
  Tpolyhedron **p;

  p=(Tpolyhedron **)GetVectorElement(i,&(e->obstacles));
  if (p==NULL)
    return(NO_UINT);
  else
    return(GetPolyhedronStatus(*p));
}

void GetObstacleColor(unsigned int i,Tcolor *c,Tenvironment *e)
{
  Tpolyhedron **p;

  p=(Tpolyhedron **)GetVectorElement(i,&(e->obstacles));
  if (p==NULL)
    Error("Undefined body in GetObstacleColor");
  else
    GetPolyhedronColor(c,*p);
}

double GetEnvironmentMaxCoordinate(Tenvironment *e)
{
  return(e->maxCoord);
}

void PrintEnvironment(FILE *f,char *path,Tenvironment *e)
{
  unsigned int i,n;
  char *name;
  Tpolyhedron *p;
  
  n=GetEnvironmentNObstacles(e);  
  if (n>0)
    fprintf(f,"[OBSTACLES]\n\n");
  for(i=0;i<n;i++)
    {
      name=GetObstacleName(i,e);
      p=GetObstacleShape(i,e);
      if ((name!=NULL)&&(p!=NULL))
	{
	  fprintf(f,"  %s : ",name);
	  PrintPolyhedron(f,path,strlen(name),NULL,i,p);
	}
    }
  fprintf(f,"\n");
}

void PlotEnvironment(Tplot3d *pt,Tenvironment *e)
{
  unsigned int i;
  unsigned int n;
  Tpolyhedron *p;
  Tcolor c;

  n=GetEnvironmentNObstacles(e);
  NewColor(DCP3D_R,DCP3D_G,DCP3D_G,&c); /*Default color. Actually not used since
					  each polyhedron has its own color. */
  for(i=0;i<n;i++)
    {
      p=GetObstacleShape(i,e);
      if (p!=NULL)
	{
	  StartNew3dObject(&c,pt);
	  PlotPolyhedron(pt,p);
	  Close3dObject(pt);
	}
    }
  DeleteColor(&c);
}

void DeleteEnvironment(Tenvironment *e)
{
  unsigned int i,n;
  Tpolyhedron *p;
  char *name;

  n=GetEnvironmentNObstacles(e);
  for(i=0;i<n;i++)
    {
      p=GetObstacleShape(i,e);
      if (p!=NULL)
	{
	  DeletePolyhedron(p);
	  free(p);
	}
      name=GetObstacleName(i,e);
      if (name!=NULL)
	free(name);
    }
  DeleteVector(&(e->obstacles));
  DeleteVector(&(e->names));
}
