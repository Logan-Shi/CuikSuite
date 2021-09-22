#include "heap.h"

#include "error.h"
#include "defines.h"

#include <math.h>

/** 
   \file heap.c
   \brief Implementation of the functions operating on Theap.

   Implementation of the functions operating on Theap.

   \sa Theap,heap.h.
*/

/** 
   \brief Returns the identifier of a parent node in a binary heap.

   Returns the identifier of a parent node in a binary heap from
   the identifier of the child node.

   \param i The identifier of the heap node.
 */
#define HEAP_PARENT(i) ((unsigned int)floor(((i)-1)/2))

/** 
   \brief Returns the identifier of a child node in a binary heap.

   Returns the identifier of a child node in a binary heap from the
   identifier of the parent nodel

   Actually a node has two children. The first is directly the identifier
   returned here, the second is the returned value +1.

   \param i The identifier of the heap node.
 */
#define HEAP_CHILD(i) (2*(i)+1)

/** 
    \brief Verifies the integrity of the heap.

    Used for debug only.

    \param heap The heap to check.
*/
void CheckHeap(Theap *heap);

/** 
   \brief Moves an element up in the heap.
   
    Moves an element up in the heap until it reaches a parent
    node larger than the moved node

    The nodes are compared using the LessThan function given in the
    heap constructor.
    
    \param i The index of the element to move up.
    \param heap The heap to update.

    \return TRUE if the element was actually moved.
*/
boolean HeapUp(unsigned int i,Theap *heap);

/** 
   \brief Moves an element down in the heap.
   
    Moves an element up in the heap until it reaches a children
    nodes smaller than the moved node

    The nodes are compared using the LessThan function given in the
    heap constructor.
    
    \param i The index of the element to move up.
    \param heap The heap to update.

    \return TRUE if the element was actually moved.
*/
boolean  HeapDown(unsigned int i,Theap *heap);

/********************************************************/
void CheckHeap(Theap *heap)
{
  unsigned int i,m;
  unsigned int *p,*s;

  if (heap->last>0)
    {
      m=VectorSize(&(heap->id2data));
      for(i=0;i<m;i++)
	{
	  p=(unsigned int *)GetVectorElement(i,&(heap->id2data));
	  if (p!=NULL)
	    {
	      if (*p>=heap->last)
		Error("Error in heap (I)");
	      s=(unsigned int *)GetVectorElement(*p,&(heap->data2id));
	      if (s==NULL)
		Error("Error in heap (II)");
	      if (i!=*s)
		Error("Error in heap (III)");
	    }
	}
      
      for(i=0;i<heap->last;i++)
	{
	  p=(unsigned int *)GetVectorElement(i,&(heap->data2id));
	  if (p==NULL)
	    Error("Error in heap (IV)");
	  s=(unsigned int *)GetVectorElement(*p,&(heap->id2data));
	  if (s==NULL)
	    Error("Error in heap (V)");
	  if (i!=*s)
	    Error("Error in heap (VI)");
	}
    }
}

boolean HeapUp(unsigned int i,Theap *heap)
{ 
  unsigned int p,c;
  void *ep,*ec;
  boolean swap;
  unsigned int idC,idP;
  boolean moved;

  swap=TRUE;
  moved=FALSE;
  c=i;
  ec=GetVectorElement(c,&(heap->data));
  while((c>0)&&(swap))
    {
      p=HEAP_PARENT(c);
      ep=GetVectorElement(p,&(heap->data));
      
      if (heap->LessThan(ec,ep,heap->userData))
	{
	  if (heap->hasIDs)
	    {
	      idC=*(unsigned int *)GetVectorElement(c,&(heap->data2id));
	      idP=*(unsigned int *)GetVectorElement(p,&(heap->data2id));
	      SwapVectorElements(idC,idP,&(heap->id2data));
	      SwapVectorElements(c,p,&(heap->data2id));
	    }
	  SwapVectorElements(c,p,&(heap->data));

	  moved=TRUE;
	  swap=TRUE;
	  /*Prepare to continue moving up*/
	  c=p;
	  ec=GetVectorElement(c,&(heap->data));
	}
      else
	swap=FALSE;
    }
  return(moved);
}

boolean HeapDown(unsigned int i,Theap *heap)
{
  unsigned int p,c,c1,c2;
  void *ep,*ec,*ec1,*ec2;
  boolean swap;
  unsigned int idC,idP;
  boolean moved;

  moved=FALSE;
  swap=TRUE;
  p=i;
  ep=GetVectorElement(p,&(heap->data));
  while((p<heap->last)&&(swap))
    {
      swap=FALSE;
      c1=HEAP_CHILD(p);
      /* determine the child with lower priority */
      if (c1<heap->last)
	{
	  ec1=GetVectorElement(c1,&(heap->data));
	  c2=c1+1;
	  if (c2<heap->last)
	    {
	      ec2=GetVectorElement(c2,&(heap->data));
	      if (heap->LessThan(ec1,ec2,heap->userData))
		{c=c1; ec=ec1;}
	      else
		{c=c2; ec=ec2;}
	    }
	  else
	    {c=c1; ec=ec1;}

	  if (heap->LessThan(ec,ep,heap->userData))
	    {
	      if (heap->hasIDs)
		{
		  idC=*(unsigned int *)GetVectorElement(c,&(heap->data2id));
		  idP=*(unsigned int *)GetVectorElement(p,&(heap->data2id));
		  SwapVectorElements(idC,idP,&(heap->id2data));
		  SwapVectorElements(c,p,&(heap->data2id));
		}
	      SwapVectorElements(c,p,&(heap->data));
	      
	      moved=TRUE;
	      swap=TRUE;
	      
	      /*Prepare to continue moving down*/
	      p=c;
	      ep=GetVectorElement(p,&(heap->data));
	    }
	}
    }
  return(moved);
}

boolean LessThanID(void *a,void *b,void *userData)
{
  return(*((unsigned int *)a)<*((unsigned int *)b));
}

boolean LessThanDouble(void *a,void *b,void *userData)
{
  return(*((double *)a)<*((double *)b));
}

boolean LessThanDoublePair(void *a,void *b,void *userData)
{
  return((((TDoublePair *)a)->f<((TDoublePair *)b)->f)||
	 ((((TDoublePair *)a)->f==((TDoublePair *)b)->f)&&
	  (((TDoublePair *)a)->s<((TDoublePair *)b)->s)));
}

boolean LessThanPtr(void *a,void *b,void *userData)
{
  return(*((void **)a)<*((void **)b));
}


void InitHeap(unsigned int ele_size,
	      void (* Copy)(void *,void*),
	      void (* Delete)(void *),
	      boolean (* LessThan)(void *,void*,void *),
	      void *userData,
	      boolean hasIDs,
	      unsigned int max_ele,Theap *heap)
{
  InitVector(ele_size,Copy,Delete,max_ele,&(heap->data));
  heap->hasIDs=hasIDs;
  if (heap->hasIDs)
    {
      InitVector(sizeof(unsigned int),CopyID,DeleteID,max_ele,&(heap->data2id));
      /*mapping id2data can be larger that max_element but it will be extended
	as necessary*/
      InitVector(sizeof(unsigned int),CopyID,DeleteID,max_ele,&(heap->id2data));
    }
  heap->last=0;
  heap->LessThan=LessThan;
  heap->userData=userData;
}

void CopyHeap(Theap *h_dst,Theap *h_src)
{
  CopyVector(&(h_dst->data),&(h_src->data));
  h_dst->hasIDs=h_src->hasIDs;
  if (h_dst->hasIDs)
    {
      CopyVector(&(h_dst->data2id),&(h_src->data2id));
      CopyVector(&(h_dst->id2data),&(h_src->id2data));
    }
  h_dst->last=h_src->last;
  h_dst->LessThan=h_src->LessThan;
  h_dst->userData=h_src->userData;
}

void ResetHeap(Theap *heap)
{
  if (heap->hasIDs)
    {
      ResetVector(&(heap->data2id));
      ResetVector(&(heap->id2data));
    }
  ResetVector(&(heap->data));
  heap->last=0;
}

unsigned int HeapSize(Theap *heap)
{
  return(heap->last);
}

boolean HeapEmpty(Theap *heap)
{
  return(heap->last==0);
}

void AddElement2Heap(unsigned int id,void *e,Theap *heap)
{
  SetVectorElement(heap->last,e,&(heap->data));
  if (heap->hasIDs)
    {
      SetVectorElement(heap->last,&id,&(heap->data2id));
      SetVectorElement(id,&(heap->last),&(heap->id2data));
    }

  heap->last++;
  
  HeapUp(heap->last-1,heap);
}

void UpdateHeapElement(unsigned int id,void *e,Theap *heap)
{
  if (heap->hasIDs)
    {
      unsigned int i,*p;
      
      p=(unsigned int *)GetVectorElement(id,&(heap->id2data));
      if (p==NULL)
	AddElement2Heap(id,e,heap);
      else
	{
	  i=*p;
	  if (i>=heap->last) Error("Incorrect reference to a heap position");
	  SetVectorElement(i,e,&(heap->data));
	  
	  if (!HeapUp(i,heap))
	    HeapDown(i,heap);
	}
    }
  else
    Error("Elements without associated identifier can not be updated");
}

void *GetHeapElement(unsigned int i,Theap *heap)
{
  if (i<heap->last)
    return(GetVectorElement(i,&(heap->data)));
  else
    return(NULL);
}


void *GetHeapElementWithID(unsigned int id,Theap *heap)
{
  if (heap->hasIDs)
    return(GetHeapElement(GetHeapPosition(id,heap),heap));
  else
    return((void *)NULL);
}

unsigned int GetHeapPosition(unsigned int id,Theap *heap)
{
  if (heap->hasIDs)
    return(*(unsigned int *)GetVectorElement(id,&(heap->id2data)));
  else
    return(NO_UINT);
}

unsigned int ExtractMinElement(void *e,Theap *heap)
{
  unsigned int idFirst,idLast;
  
  idFirst=NO_UINT;

  if (heap->last>0)
    {
      if (heap->hasIDs)
	{ 
	  idFirst=*(unsigned int *)GetVectorElement(0,&(heap->data2id));
	  idLast=*(unsigned int *)GetVectorElement(heap->last-1,&(heap->data2id));
	  
	  SwapVectorElements(idLast,idFirst,&(heap->id2data));
	  RemoveVectorElement(idFirst,&(heap->id2data));

	  SwapVectorElements(heap->last-1,0,&(heap->data2id));
	  RemoveVectorElement(heap->last-1,&(heap->data2id));
	}

      SwapVectorElements(heap->last-1,0,&(heap->data));
      ExtractVectorElement(heap->last-1,e,&(heap->data));

      heap->last--;
      HeapDown(0,heap);
    }
  else
    Error("Extracting an element from a empty heap");

  return(idFirst);
}

void DeleteHeap(Theap *heap)
{
  ResetHeap(heap);
  if (heap->hasIDs)
    {
      DeleteVector((void *)&(heap->id2data));
      DeleteVector((void *)&(heap->data2id));
    }
  DeleteVector((void *)&(heap->data));
}
