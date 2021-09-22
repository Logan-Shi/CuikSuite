
#include "vector.h"

#include "defines.h"

#include <stdlib.h>
#include <string.h>

/** 
   \file vector.c
   \brief Implementation of the functions operating on Tvector.

   Implementation of the functions operating on Tvector.

   \sa Tvector,vector.h,
*/

/**************************************************************************/
inline boolean CmpID(void *a,void *b)
{
  return(*((unsigned int *)a)==*((unsigned int *)b));
}

inline void CopyID(void *a,void *b)
{
  (*((unsigned int *)a)=*((unsigned int *)b));
}

inline void DeleteID(void *a)
{
}

/**************************************************************************/
inline boolean CmpDouble(void *a,void *b)
{
  return(*((double *)a)==*((double *)b));
}

inline void CopyDouble(void *a,void *b)
{
  (*((double *)a)=*((double *)b));
}

inline void DeleteDouble(void *a)
{
}

/**************************************************************************/
inline void NewDoublePair(double f,double s,TDoublePair *p)
{
  p->f=f;
  p->s=s;
}

inline double FirstInPair(TDoublePair *p)
{
  return(p->f);
}

inline double SecondInPair(TDoublePair *p)
{
  return(p->s);
}

inline boolean CmpDoublePair(void *a,void *b)
{
  return((((TDoublePair *)a)->f==((TDoublePair *)b)->f)&&
	 (((TDoublePair *)a)->s==((TDoublePair *)b)->s));
}

inline void CopyDoublePair(void *a,void *b)
{
  ((TDoublePair *)a)->f=((TDoublePair *)b)->f;
  ((TDoublePair *)a)->s=((TDoublePair *)b)->s;
}

inline void DeleteDoublePair(void *a)
{
}

/**************************************************************************/
inline boolean CmpVoidPtr(void *a,void *b)
{
  return(*((void **)a)==*((void **)b));
}

inline void CopyVoidPtr(void *a,void *b)
{
  (*((void **)a)=*((void **)b));
}

inline void DeleteVoidPtr(void *a)
{
  /*The data actually pointed by the pointer stored in the vector
    should be deleted by the caller*/
}

/**************************************************************************/

void InitVector(unsigned int ele_size,void (* Copy)(void *,void*),void (* Delete)(void *),unsigned int max_ele,Tvector *vector)
{
  unsigned int i;

  vector->max_ele=max_ele;
  vector->num_ele=0;
  vector->ele_size=ele_size;
  if (ele_size==0)
    Error("The element size can not be zero in InitVector");
  vector->Delete=Delete;
  if (Copy==NULL)
    Error("The copy operator can not be null in InitVector");
  vector->Copy=Copy;

  NEW(vector->elements,vector->max_ele,void *);

  for(i=0;i<vector->max_ele;i++)
    vector->elements[i]=NULL;
}

void ResetVector(Tvector *vector)
{
  unsigned int i;

  for(i=0;i<vector->num_ele;i++)
    {
      if (vector->elements[i]!=NULL)
	{
	  if (vector->Delete!=NULL)
	    vector->Delete(vector->elements[i]);
	  free(vector->elements[i]);
	  vector->elements[i]=NULL; 
	}
    }

  vector->num_ele=0;
}

void CopyVector(Tvector *v_dst,Tvector *v_src)
{
  unsigned int i;

  v_dst->max_ele=v_src->max_ele;
  v_dst->num_ele=v_src->num_ele;
  v_dst->ele_size=v_src->ele_size;
  v_dst->Delete=v_src->Delete;
  v_dst->Copy=v_src->Copy;

  NEW(v_dst->elements,v_dst->max_ele,void *);

  for(i=0;i<v_dst->max_ele;i++)
    {
      if (v_src->elements[i]==NULL)
	v_dst->elements[i]=NULL;
      else
	{
	  NEW(v_dst->elements[i],v_dst->ele_size,char);
	  v_dst->Copy(v_dst->elements[i],v_src->elements[i]);
	}
    }
}

unsigned int VectorFirstFreePos(Tvector *vector)
{
  unsigned int k;

  k=0;
  while((k<vector->num_ele)&&(vector->elements[k]!=NULL))
    k++;

  return(k);
}

unsigned int VectorSize(Tvector *vector)
{
  return(vector->num_ele);
}

unsigned int VectorMaxSize(Tvector *vector)
{
  return(vector->max_ele);
}

boolean VectorEmpty(Tvector *vector)
{
  return(vector->num_ele==0);
}

boolean ElementInVector(void *e,boolean (* cmp)(void *,void*),Tvector *vector)
{
  return(FindPos(e,cmp,vector)!=((unsigned int)(-1)));
}

unsigned int FindPos(void *e,boolean (* cmp)(void *,void*),Tvector *vector)
{
  boolean found;
  unsigned int i;
  
  found=FALSE;
  i=0;
  while ((!found)&&(i<vector->num_ele))
    {
      if (vector->elements[i]!=NULL)
	{
	  if (cmp(e,vector->elements[i]))
	    found=TRUE;
	  else
	    i++;
	}
    }
  if (found)
    return(i);
  else
    return((unsigned int)(-1));
}

unsigned int NewVectorElement(void *e,Tvector *vector)
{
  unsigned int k;

  k=vector->num_ele;

  SetVectorElement(vector->num_ele,e,vector);

  return(k);
}

unsigned int NewFreeVectorElement(void *e,Tvector *vector)
{
  unsigned int k;

  k=VectorFirstFreePos(vector);
 
  SetVectorElement(k,e,vector);

  return(k);
}

void SetVectorElement(unsigned int i,void *e,Tvector *vector)
{
  if (i>=vector->num_ele)
    {
      vector->num_ele=i+1;
      if (i>=vector->max_ele)
	{
	  unsigned int k,j;
	      
	  k=vector->max_ele;
	  vector->max_ele=i*2;
	  MEM_EXPAND(vector->elements,vector->max_ele,void *);
	      
	  for(j=k;j<vector->max_ele;j++)
	    vector->elements[j]=NULL;
	}
    }
      
  if (vector->elements[i]==NULL) /* If element 'i' is still empty */
    {
      NEW(vector->elements[i],vector->ele_size,char); /* reserve memory */
    }
  else
    {
      /* We have some info in the vector we have to destroy before copying the new info */
      if (vector->Delete!=NULL)
	vector->Delete(vector->elements[i]);
    }
      
  vector->Copy((void *)(vector->elements[i]),e); /* copy the user data in the reserved memory */
}

void *GetVectorElement(unsigned int i,Tvector *vector)
{
  if (i<vector->num_ele)
    return(vector->elements[i]);
  else
    return(NULL);
}

void *GetLastElement(Tvector *vector)
{
  if (vector->num_ele==0)
    return(NULL);
  else
    return(vector->elements[vector->num_ele-1]);
}

void RemoveVectorElement(unsigned int i,Tvector *vector)
{
  if ((i<vector->num_ele)&&(vector->elements[i]!=NULL))
    {
      if (vector->Delete!=NULL)
	vector->Delete(vector->elements[i]);
      free(vector->elements[i]);
      vector->elements[i]=NULL;
      if (i==vector->num_ele-1)
	vector->num_ele--;
    }
}

void SwapVectorElements(unsigned int i,unsigned int j,Tvector *vector)
{
  void *vi,*vj;

  if ((i<vector->num_ele)&&(j<vector->num_ele))
    {
      vi=vector->elements[i];
      vj=vector->elements[j];
      if ((vi!=NULL)&&(vj!=NULL))
	{
	  vector->elements[i]=vj;
	  vector->elements[j]=vi;
	}
      else
	Error("Swapping non-exiting elements in a vector.");
    }
  else
    Error("Swapping non-exiting elements in a vector.");
}

void ReverseVector(Tvector *vector)
{
  int i,j;
  void *vi,*vj;

  for(i=0,j=vector->num_ele-1;i<j;i++,j--)
    {
      vi=vector->elements[i];
      vj=vector->elements[j];
      vector->elements[i]=vj;
      vector->elements[j]=vi;
    }
}

void ConcatVectors(Tvector *vector1,Tvector *vector)
{
  unsigned int i;

  for(i=0;i<vector1->num_ele;i++)
    NewVectorElement(vector1->elements[i],vector);
}


void ExtractVectorElement(unsigned int i,void *e,Tvector *vector)
{
  void *vi;

  if (i<vector->num_ele)
    {
     
      vi=(void *)(vector->elements[i]);
      if (vi!=NULL)
	{
	  vector->Copy(e,vi);
	  RemoveVectorElement(i,vector);
	}
      else
	Error("Extracting a non-exiting elements in a vector.");
    }
  else
    Error("Extracting a non-exiting elements in a vector.");
    
}

void MoveVectorElement(unsigned int i,unsigned int ni,Tvector *vector)
{
  void *vi,*vn;

  if ((i<vector->num_ele)&&(ni<vector->num_ele))
    {
      if (i!=ni)
	{
	  vi=(void *)(vector->elements[i]);
	  if (vi!=NULL)
	    {
	      vn=(void *)(vector->elements[ni]);
	      if (vn!=NULL)
		RemoveVectorElement(ni,vector);
	      
	      vector->elements[ni]=vi;
	      vector->elements[i]=NULL;
	    }
	  else
	    Error("Moving a vector existing vector element.");
	}
    }
  else
    Error("Moving a vector element from/to a non existing position.");
}

void DeleteVector(void *vector)
{
  ResetVector((Tvector *)vector);
  free(((Tvector *)vector)->elements);
}
