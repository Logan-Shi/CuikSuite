#include "sample.h"

#include "defines.h"
#include "geom.h"

#include <math.h>

/** \file sample.c
    \brief Implementaton of the function operating on Tsample.
    
    Implementaton of the function operating on Tsample.

    \sa Tsample, sample.h.
*/

void InitSample(unsigned int sID,unsigned int n,double *v,unsigned int boxID,Tsample *s)
{
  unsigned int i;

  InitVector(sizeof(double),CopyDouble,DeleteDouble,n,&(s->v));

  for(i=0;i<n;i++)
    SetVectorElement(i,&(v[i]),&(s->v));

  s->boxID=boxID;
  s->sID=sID;
}

void InitSampleFromBox(unsigned int sID,boolean *systemVar,Tbox *b,unsigned int boxID,Tsample *s)
{
  double *v;
  unsigned int i,d,k,n;

  d=GetBoxNIntervals(b);
  if (systemVar==NULL)
    n=d;
  else
    {
      n=0;
      for(i=0;i<d;i++)
	{
	  if (systemVar[i]) n++;
	}
    }

  NEW(v,n,double);
  k=0;
  for(i=0;i<d;i++)
    {
      if ((systemVar==NULL)||(systemVar[i]))
	{
	  v[k]=IntervalCenter(GetBoxInterval(i,b));
	  k++;
	}
    }
  
  InitSample(sID,n,v,boxID,s);

  free(v);
}

void CopySample(void *s_dst,void *s_src)
{
  CopyVector(&(((Tsample *)s_dst)->v),&(((Tsample *)s_src)->v));
  ((Tsample *)s_dst)->boxID=((Tsample *)s_src)->boxID;
  ((Tsample *)s_dst)->sID=((Tsample *)s_src)->sID;
}

unsigned int GetSampleDim(Tsample *s)
{
  return(VectorSize(&(s->v)));
}

Tvector *GetSampleValues(Tsample *s)
{
  return(&(s->v));
}

double GetSampleValue(unsigned int n,Tsample *s)
{
  double *v;

  v=(double *)GetVectorElement(n,&(s->v));

  if (v==NULL)
    Error("Non-defined element in GetSampleValue");
  
  return(*v);
}

unsigned int GetSampleBoxID(Tsample *s)
{
  return(s->boxID);
}

unsigned int GetSampleID(Tsample *s)
{
  return(s->sID);
}

void SetSampleBoxID(unsigned int boxID,Tsample *s)
{
  s->boxID=boxID;
}

double GetSampleDistance(Tsample *s1,Tsample *s2)
{
  unsigned int i,n1,n2;
  double d,r;

  n1=GetSampleDim(s1);
  n2=GetSampleDim(s2);
  if (n1!=n2)
    Error("Samples of different dimensionality in GetSampleDistance");

  d=0.0;
  for(i=0;i<n1;i++)
    {
      r=GetSampleValue(i,s1)-GetSampleValue(i,s2);
      d+=(r*r);
    }

  return(sqrt(d));
}

void PrintSample(FILE *f,Tsample *s)
{
  unsigned int i,n;
  double v;

  n=VectorSize(&(s->v));

  for(i=0;i<n;i++)
    {
      v=*((double *)GetVectorElement(i,&(s->v)));
      PrintReal(f,v);
      fprintf(f," ");
    }
  fprintf(f,"\n");
}

void SaveSample(FILE *f,Tsample *s)
{
  fprintf(f,"%u %u %u ",s->sID,s->boxID,VectorSize(&(s->v)));
  PrintSample(f,s);
}

void LoadSample(FILE *f,Tsample *s)
{
  unsigned int i,n;
  double v;

  fscanf(f,"%u %u %u",&(s->sID),&(s->boxID),&n);
  
  InitVector(sizeof(double),CopyDouble,DeleteDouble,n,&(s->v));

  for(i=0;i<n;i++)
    {
      fscanf(f,"%lf",&v);
      SetVectorElement(i,&v,&(s->v));
    }
}

void DeleteSample(void *s)
{
  DeleteVector(&(((Tsample *)s)->v));
}
