#include "list.h"

#include "error.h"
#include "defines.h"

#include <stdlib.h>
#include <string.h>

/**
   \file list.c
   \brief Implementation of the functions operating on Tlist.

   Implementation of the functions operating on Tlist.

   \sa Tlist,list.h,
*/

/**
  \brief Private function to delete an element from the list.

  Private function to delete an element from the list.

  \param node A pointer to the list node to be deleted.
  \param list The list
*/
void PrivDelEle(Tbuf *node,Tlist *list);


/**
  \brief Private function to add an element from the list.

  Private function to add an element from the list.

  \param Info Pointer to the buffer with the data to add to the list.
  \param pos Pointer to a node in the list.
  \param in_front TRUE if the element is to be added in front of the
         pointed node. FALSE if the element is to be added behind it.
  \param list The list
*/
void PrivAddElement(void *Info,Tbuf *pos,boolean in_front,Tlist *list);


/*Delete the element pointed by node from the list 'list'*/
void PrivDelEle(Tbuf *node, /*pointer to the element to be removed from the list*/
		Tlist *list /*list*/
		)
{
  if (node->previous!=(Tbuf *)NULL)
    node->previous->next=node->next;

  if (node->next!=(Tbuf *)NULL)
   node->next->previous=node->previous;
      
  if (node==list->first)
    list->first=node->next;
  if (node==list->last)
    list->last=node->previous;
      	
  list->num_ele--;

  free(node->data);
  free(node);
}

/*
 * Adds a new element (pointed by Info) in the position of the list pointed by pos.
 * If in_front is TRUE then the new element is inserted in front of that pointed by
 * pos and if not behind.
 * If the list is empty, the parameter pos is not used.
 */
void PrivAddElement(void *Info,       /*pointer to the data to de added to the list*/
		    Tbuf *pos,        /*pointer to the position of the list where the new data is added*/
		    boolean in_front, /*TRUE if info is added in front of the node*/
		    Tlist *list       /*list to be extended*/
		    )
{
  Tbuf *node;

  NEW(node,1,Tbuf);

  NEW(node->data,list->ele_size,char);
  
  memcpy(node->data,Info,list->ele_size);

  if (list->num_ele==0) /*pos must be NULL*/
    {
      node->previous=NULL;
      node->next=NULL;

      list->first=node;
      list->last=node;
    }
  else
    {
      if (in_front)
	{
	  node->next=pos;
	  node->previous=pos->previous;

	  if (node->previous!=NULL)
	    node->previous->next=node;
	  pos->previous=node;
	}
      else
	{
	  node->next=pos->next;
	  node->previous=pos;

	  if (node->next!=NULL)
	    node->next->previous=node;
	  pos->next=node;
	}
      
      if ((list->first==pos)&&(in_front))
	list->first=node;
      
      if ((list->last==pos)&&(!in_front))
	list->last=node;
    }

  list->num_ele++;
}

/**************************************************************************
 **************************************************************************/

/*PUBLIC FUNCTIONS*/

/*
 * Init a list with elements of size ele_size.
 * This size can be obtained usint sizeof(type)
 * where type is the type of elements to be stored
 * in the list.
 */
void InitList(unsigned int ele_size, /*size of the elements of the list*/
	      Tlist *list            /*list to be initialized*/
	      )
{

  list->num_ele=0;
  list->ele_size=ele_size;
  list->first=(Tbuf *)NULL;
  list->last=(Tbuf *)NULL;
}

/*
 * Deletes a list. 
 * No operation is done on each list element.
 * The user is in charge of deleting each element of the list using
 * the apropritate delete function (iterating on the list, getting and
 * deleting each element and the removing it from the list)
 */
void DeleteList(Tlist *list /*list to be deleted*/
		)
{  
  DeleteAllItems(list); 
}

/*
 * Deletes all the items of a list list. 
 */
void DeleteAllItems(Tlist *list /*list to be deleted*/
		)
{
  Tbuf *e,*next;

  e=list->first;
  while(e!=NULL)
    {
      next=e->next;
      PrivDelEle(e,list);
      e=next;
    }
}


/*
 * Returns the number of elements of the list
 */
unsigned int ListSize(Tlist *list)
{
  return(list->num_ele);
}

/*
 * Returns true if the list is empty
*/
boolean ListEmpty(Tlist *list)
{
  return(list->num_ele==0);
}

/*
 * Adds a new element at the head of the list
 */
void AddFirstElement(void *Info, /*pointer to the data to de added to the list*/
		     Tlist *list /*list to be extended*/
		     )
{
  PrivAddElement(Info,list->first,TRUE,list);
}

/*
 * Adds a new element at the end of the list
 */
void AddLastElement(void *Info,
		    Tlist *list)
{
  PrivAddElement(Info,list->last,FALSE,list);
}

void ExtractFirst(void *Info,Tlist *list)
{
  if (list->first!=NULL)
    {
      Tbuf *e;

      memcpy(Info,list->first->data,list->ele_size);

      e=list->first->next;
      PrivDelEle(list->first,list);
      list->first=e;
    }
  else
    Error("Empty list");
}

void ExtractLast(void *Info,Tlist *list)
{
  if (list->last!=NULL)
    {
      Tbuf *e;

      memcpy(Info,list->last->data,list->ele_size);

      e=list->last->next;
      PrivDelEle(list->last,list);
      list->last=e;
    }
  else
    Error("Empty list");
}

boolean HasElement(void *Info,boolean (* cmp)(void *,void*),Tlist *list)
{
  Tbuf *current;
  boolean found;

  current=list->first;

  found=FALSE;
  while((!found)&&(current!=NULL))
    {
      found=cmp(Info,current->data);
      if (!found)
	current=current->next;
    }
  return(found);
}

void PrintList(Tlist *l)
{
  Tbuf *current;
  printf("L:[");
  
  current=l->first;

  while(current!=NULL)
    {
      printf("%p (%p)  ",current,current->data);
      current=current->next;
    }

  printf(" ]\n");
}

/**************************************************************************/

/*Iterators functions*/

/*
 * Starts a new itarator for a given list
 */
void InitIterator(Titerator *i,Tlist *list)
{
  i->current=NULL;
  i->list=list;  
}

void CopyIterator(Titerator *dst,Titerator *src)
{
  dst->current=src->current;
  dst->list=src->list;
}

/*
 * Returns a pointer to the data stored at the position of the list pointed by 'i->current'
 */
void *GetCurrent(Titerator *i)
{
  return(i->current->data);
}

/*
 * Makes a copy of the element pointed by the iterator
 * and deletes the element from the list
 */
void ExtractCurrent(void *Info,Titerator *i)
{
  if (i->current!=NULL)
    {
      Tbuf *e;

      memcpy(Info,i->current->data,i->list->ele_size);

      e=i->current->next;
      PrivDelEle(i->current,i->list);
      i->current=e;
    }
}

/*
 * Adds a new item in front of the element pointed by i->current
 */
void AddInFrontOfCurrent(void *Info,Titerator *i)
{
  PrivAddElement(Info,i->current,TRUE,i->list);
}

/*
 * Adds a new item behind the element pointed by i->current
 */
void AddBehindCurrent(void *Info,Titerator *i)
{
  PrivAddElement(Info,i->current,FALSE,i->list);
}

/*
 * Removes the element pointed by i->current from the list
 */
void DeleteCurrent(Titerator *i)
{
  if (i->current!=NULL)
    {
      Tbuf *e;

      e=i->current->next;
      PrivDelEle(i->current,i->list);
      i->current=e;
    }
}

/*
 * Moves the iterator to the behning of the list
 */
void First(Titerator *i)
{
  i->current=i->list->first;
}

/*
 * Moves the iterator to the end of the list
 */
void Last(Titerator *i)
{
  i->current=i->list->last;
}

/*
 * Moves the iterator forward on the list
 * Returns FALSE if the movement can not be performed
 */
boolean Advance(Titerator *i)
{
  boolean b;

  if (i->current!=NULL)
    {
      i->current=i->current->next;
      if (i->current!=NULL)
	b=TRUE;
      else
	b=FALSE;
    }
  else
    b=FALSE;

  return(b);
}

/*
 * Moves the iterator backwards on the list
 * Returns FALSE if the movement can not be performed
 */
boolean Bacward(Titerator *i)
{
  boolean b;

  if (i->current!=NULL)
    {
      i->current=i->current->previous;
      if (i->current!=NULL)
	b=TRUE;
      else
	b=FALSE;
    }
  else
    b=FALSE;

  return(b);
}

/*
 * Moves the iterator to the position 'n' of the list
 * Returns FALSE if the movement can not be performed
 */
boolean MoveTo(unsigned int n,Titerator *i)
{
  unsigned int j;
  boolean b;

  if (n>=i->list->num_ele)
    {
      i->current=NULL;
      b=FALSE;
    }
  else
    {
      i->current=i->list->first;
      j=0;
      while(j<n)
	{
	  i->current=i->current->next;
	  j++;
	}
      b=TRUE;
    }

  return(b);
}

/*
 * Returns TRUE if the iterator points to a non valid element
 */
boolean EndOfList(Titerator *i)
{
  return(i->current==NULL);
}
