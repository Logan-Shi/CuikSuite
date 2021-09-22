#include "box_heap.h"

#include "interval.h"

#include "boolean.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \file box_heap.c
    \brief Implementation of the functions operating on box Theap.

    Implementation of the functions operating on Theap with Tbox
    as a basic type.

    \sa box_heap.h, heap.h, Theap, Tbox.
*/

void InitHeapOfBoxes(boolean (* LessThan)(void *,void*,void*),void *userData,Theap *h)
{
  InitHeap(sizeof(Tbox),CopyBox,DeleteBox,LessThan,userData,FALSE,INIT_NUM_BOXES_IN_HEAP,h);
}

void AddBox2HeapOfBoxes(Tbox *b,Theap *h)
{
  AddElement2Heap(NO_UINT,(void *)b,h);
}

double HeapOfBoxesVolume(boolean *used,Theap *h)
{ 
  unsigned int i,n;
  double v;

  n=HeapSize(h);

  v=0;
  for(i=0;i<n;i++)
    v+=GetBoxVolume(used,(Tbox *)GetHeapElement(i,h));

  return(v);
}

double HeapOfBoxesMaxDiagonal(boolean *used,Theap *h)
{
  unsigned int i,n;
  double d,md;

  n=HeapSize(h);

  md=0;
  for(i=0;i<n;i++)
    {
      d=GetBoxDiagonal(used,(Tbox *)GetHeapElement(i,h));
      if (d>md)
	md=d;
    }

  return(md);
}

double HeapOfBoxesMaxSize(boolean *used,Theap *h)
{
  unsigned int i,n;
  double s,ms;

  n=HeapSize(h);

  ms=0;
  for(i=0;i<n;i++)
    {
      s=GetBoxSize(used,(Tbox *)GetHeapElement(i,h));
      if (s>ms)
	ms=s;
    }

  return(ms);
}


void Heap2List(Tlist *l,Theap *h)
{
  unsigned int i,n;
  Tbox b;

  InitListOfBoxes(l);

  n=HeapSize(h);
  for(i=0;i<n;i++)
    {
      CopyBox(&b,GetHeapElement(i,h));
      AddLastElement(&b,l);
    }
}

void AddList2Heap(Tlist *l,Theap *h)
{
  Titerator i;

  InitIterator(&i,l);
  First(&i);  
  while(!EndOfList(&i))
    {
      AddElement2Heap(NO_UINT,GetCurrent(&i),h);
      Advance(&i);
    }
}

void PrintHeapOfBoxes(FILE *f,boolean *used,char *heading,Theap *h)
{
  unsigned int i,n;

  n=HeapSize(h);
  for(i=0;i<n;i++)
    {
      if (heading!=NULL) fprintf(f,"%s ",heading);
      fprintf(f,"%u : ",i);
      PrintBoxSubset(f,used,NULL,(Tbox *)GetHeapElement(i,h));
    }
  fflush(f);
}


