#ifndef LISTH
#define LISTH 

#include "boolean.h"
#include <stdio.h> 

/** 
   \file list.h
   \brief  Definition of the Tlist type and the associated functions. 

   Definition of the Tlist type and the associated functions implementing
   a generic list structure..

   \sa Tlist, list.c.
*/


/** 
  \brief A node in a list.
 
  Each node in a list has a pointer to the previous node, a pointer to the next node,
  and a pointer to the data stored in the node.
  
  \sa Tlist
*/
typedef struct Tbuf
{
  struct Tbuf *previous; /**< Link to the previous item of the list*/
  struct Tbuf *next;     /**< Link to the next item of the list*/
  void *data;            /**< Pointer to the data stored at this position of the list*/
} Tbuf;

/** 
  \brief A generic list.
 
  A double linked collection of nodes where each node is a Tbuf.

  The data is stored as a sequence of bytes, without any regard about what is the
  meaning of the data. For instance to build a list of doubles we use sizeof(double)
  as the size of the data stored in the list.<br>
  Note that, if the elements stored in the list are more complex types with pointers to other
  data, we only copy the pointers and not the data pointed by them.

  \sa list.h, list.c.
*/
typedef struct
{  
  Tbuf *first; /**< First node in the list. */
  Tbuf *last;  /**< Last node in the list. */
  unsigned int ele_size; /**< Size of the elements inside the list (in bytes). */
  unsigned int num_ele; /**< Number of elements of the list. */
} Tlist;

/** 
  \brief List iterator.
 
  Structure used to store the state of an iterator on a given list.
  
  \sa Tlist, list.h, list.c
*/
typedef struct
{
  Tbuf *current;/**< Current node pointed by the iterator. */
  Tlist *list; /**< List that the interator is following. */
} Titerator;


/** 
  \brief Constructor.
 
  Initializes an empty list for data with a given size.

  \param ele_size The size (in bytes) of the data to be stored in the list.
  \param list The list to be initialized.
*/
void InitList(unsigned int ele_size,Tlist *list);

/** 
  \brief Destructor.
 
  Deletes a list and frees all the allocated memory in all the nodes
  still in the list.

  \param list The list to be deleted.
*/
void DeleteList(Tlist *list);

/** 
  \brief Resets a list.
 
  Delete all the elements stored in the list.

  \param list The list to be reseted.
*/
void DeleteAllItems(Tlist *list);

/** 
  \brief Gets the number of elements in the list.

  Gets the number of elements in the list.

  \param list The list.

  \return The number of elements in the list.
*/
unsigned int ListSize(Tlist *list);


/** 
  \brief Checks if a list is empty.

  Checks if a list is empty.

  \param list The list.

  \return TRUE if the list is empty.
*/
boolean ListEmpty(Tlist *list);

/** 
  \brief Adds an element at the head of the list.

  Adds an element at the head of the list.

  \param Info A pointer to a memory block of size
              ele_size bytes with the data to be
	      stored in the list.
  \param list The list.
*/
void AddFirstElement(void *Info,Tlist *list);


/** 
  \brief Adds an element at the tail of the list.

  Adds an element at the tail of the list.

  \param Info A pointer to a memory block of size
              ele_size bytes with the data to be
	      stored in the list.
  \param list The list.
*/
void AddLastElement(void *Info,Tlist *list);

/** 
  \brief Extracts the first element from the list.

  Copies the first element from the list into the given
  pointer and remove the element from the list.

  \param Info A pointer to a memory block of size
              ele_size bytes where the first list element is
	      to be stored.
  \param list The list.
*/
void ExtractFirst(void *Info,Tlist *list);

/** 
  \brief Extracts the last element from the list.

  Copies the last element from the list into the given
  pointer and remove the element from the list.

  \param Info A pointer to a memory block of size
              ele_size bytes where the first list element is
	      to be stored.
  \param list The list.
*/
void ExtractLast(void *Info,Tlist *list);

/** 
  \brief Searches an element in the list.

  Determines if a given element is already in the list.

  \param Info A pointer to a memory block of size
              ele_size bytes where there is the element we want
	      to search in the list.
  \param cmp A function working on the elements stored in the list
             that retuns TRUE if the two inputs are the same.
  \param list The list.
*/
boolean HasElement(void *Info,boolean (* cmp)(void *,void*),Tlist *list);

/** 
  \brief Prints a list to \e stdout.

  Prints the list as a set of pointers. Mainly used for debug.

  \param l The list.
*/
void PrintList(Tlist *l);

/** 
  \brief Constructor.

  Generates an iterator linked to a list. Note that
  this constructor does not point the interator to any
  particular position in the list (not the first, not the
  last,...).

  \param i The iterator to be initialized.
  \param list The list.
*/
void InitIterator(Titerator *i,Tlist *list);

/** 
  \brief Copy constructor.

  Generates an iterator from another iterator.

  \param dst The iterator to be initialized.
  \param src The iterator from where to copy.
*/
void CopyIterator(Titerator *dst,Titerator *src);

/** 
  \brief Gets the element pointed by the iterator.

  Gets the element pointed by the iterator.

  \param i The iterator from where to copy.

  \return A pointer to the data of the list node poited by the iterator.
*/
void *GetCurrent(Titerator *i);


/** 
  \brief Extract the element pointed by the iterator from the list.

  Copies the element pointed by the iterator into the given buffer
  and removes the element from the list. The iterator is moved
  to the next element in the list.

  \param Info Buffer where to copy the element pointed by the iterator.
  \param i The iterator.
*/
void ExtractCurrent(void *Info,Titerator *i);

/** 
  \brief Adds an element to the list in front of the position pointed
         by the iterator.

  Adds an element to the list in front of the position pointed
  by the iterator.

  \param Info A pointer to the buffer with the data to add to the list.
  \param i The iterator.
*/
void AddInFrontOfCurrent(void *Info,Titerator *i);

/** 
  \brief Adds an element to the list behind the position pointed
         by the iterator.

  Adds an element to the list behind the position pointed
  by the iterator.

  \param Info A pointer to the buffer with the data to add to the list.
  \param i The iterator.
*/
void AddBehindCurrent(void *Info,Titerator *i);

/** 
  \brief Destructor.

  Deletes a Titerator structure.

  \param i The iterator to be deleted.
*/
void DeleteCurrent(Titerator *i);


/** 
  \brief Moves an iterator to the first position of its associated list.

  Moves an iterator to the first position of its associated list.

  \param i The iterator to be updated.
*/
void First(Titerator *i);

/** 
  \brief Moves an iterator to the last position of its associated list.

  Moves an iterator to the last position of its associated list.

  \param i The iterator to be updated.
*/
void Last(Titerator *i);

/** 
  \brief Moves an iterator to the next position of its associated list.

  Moves an iterator to the next position of its associated list.

  \param i The iterator to be updated.

  \return TRUE if the iterator can be actually displaced (i.e., it was not
          at the last position of the list).
*/
boolean Advance(Titerator *i);

/** 
  \brief Moves an iterator to the previuos position of its associated list.

  Moves an iterator to the previous position of its associated list.

  \param i The iterator to be updated.

  \return TRUE if the iterator can be actually displaced (i.e., it was not
          at the first position of the list).
*/
boolean Bacward(Titerator *i);


/** 
  \brief Moves an iterator to a given position of its associated list.

  Moves an iterator to a given position of its associated list.

  \param n The position where the iterator has to point.
  \param i The iterator to be updated.

  \return TRUE if the iterator can be actually displaced (i.e., the
          list has, at least, \e n elements).
*/
boolean MoveTo(unsigned int n,Titerator *i);


/** 
  \brief Checks if an iterator is pointing at the end of the list.

  Checks if an iterator is pointing at the end of the list.

  \param i The iterator to be checked.

  \return TRUE if the iterator is at the end of the list.
*/
boolean EndOfList(Titerator *i);

#endif
