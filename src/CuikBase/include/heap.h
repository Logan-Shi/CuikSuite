#ifndef HEAPH
#define HEAPH

#include "vector.h"

/** 
   \file heap.h
   \brief Definition of a binary heap used to implement priority queues.

   Implementation of a generic binary heap to be used to implement priority queues.
   The implementation works on generic objects as far as they have
     - A copy constructor.
     - A destructor.
     - A comparison operator identifying the lower of two given objects.

   The implementation heavely relies in the use of the \ref Tvector "vector"
   structure and, thus, default opeators (constructor, destructor, comparison)
   for doubles, integers, and pointers are already provided.

   The only distintive feature of this implementation is that element can
   have an identifier assigned by the caller attending to the semantic of
   the objects in the heap. This is useful to efficiently retrive the position 
   in the heap of an element given its identifier. This is required in several
   applications (for instance by efficient incremental A* algorithms).

   \sa Theap, heap.c.
*/

/** 
   \brief Comparison operator for identifiers.
   
   Comparison operator for identifiers identifying the lower
   of the two given identifiers.

   \param a Pointer to the first identifier to compare.
   \param b Pointer to the second identifier to compare.
   \param userData Pointer to the user data given when defining the heap.
                   It is not used in this case but given for compatibility
		   with more complex LessThan operators.

   \return TRUE if the first input is smaller than the second.
*/
boolean LessThanID(void *a,void *b,void *userData);


/** 
   \brief Comparison operator for doubles.
   
   Comparison operator for doubles identifying the lower
   of the two given doubles.

   \param a Pointer to the first double to compare.
   \param b Pointer to the second double to compare.
   \param userData Pointer to the user data given when defining the heap.
                   It is not used in this case but given for compatibility
		   with more complex LessThan operators.

   \return TRUE if the first input is smaller than the second.
*/
boolean LessThanDouble(void *a,void *b,void *userData);

/** 
   \brief Comparison operator for paris of doubles.
   
   Comparison operator for doubles identifying the lower
   of the two given pairs of doubles.
   The first double has priority and the second one
   is only considered if the first one are the same.

   \param a Pointer to the first pair of doubles to compare.
   \param b Pointer to the second pairs of doubles to compare.
   \param userData Pointer to the user data given when defining the heap.
                   It is not used in this case but given for compatibility
		   with more complex LessThan operators.

   \return TRUE if the first input is smaller than the second.
*/
boolean LessThanDoublePair(void *a,void *b,void *userData);

/** 
   \brief Comparison operator for pointers.
   
   Comparison operator for pointers identifying the lower
   of the two given pointers.

   \param a Pointer to the first pointer to compare.
   \param b Pointer to the second pointer to compare.
   \param userData Pointer to the user data given when defining the heap.
                   It is not used in this case but given for compatibility
		   with more complex LessThan operators.

   \return TRUE if the first input is smaller than the second.
*/
boolean LessThanPtr(void *a,void *b,void *userData);


/** 
   \brief A generic binary heap.

   A generic binary heap.

   \sa heap.h, heap.c.
   
 */
typedef struct
{  
  Tvector data; /**< The binary heap stored as a vector*/
  boolean hasIDs; /**< TRUE if elements have associated identifiers. */
  Tvector id2data; /**< Used to efficiently retrive the position in the heap of
		        an object given its identifier */
  Tvector data2id; /**< Used to efficiently retrive the identifier of the object 
                        given its position in the heap */
  unsigned int last; /**< Last vector position used so far. */
  boolean (* LessThan)(void*,void*,void*);  /**< The comparison operator to sort the
		       		                 elements in the heap.*/
  void *userData; /**< Pointer to a user defined block of data that is passed to
		       the LessThan operator as a third parameter. This allows to
		       define complex LessThan operators such as comparision with
		       a prototype and not just direct comparison between the
		       two elements in the heap. */
} Theap;

/** 
   \brief Constructor
   
   Initializes an empty heap
   Examples of use:
   - InitHeap(sizeof(unsigned int),CopyID,DeleteID,LessThanID,NULL,MaxNumEle,&heap);
   - InitHeap(sizeof(double),CopyDouble,DeleteDouble,LessThanDouble,NULL,MaxNumEle,&heap);
   - InitHeap(sizeof(void *),CopyPtr,DeletePtr,LessThanPtr,NULL,MaxNumEle,&heap);
   .

   \param ele_size Number of bytes taken by each element in the list.
   \param Copy Copy constructor for the elements in the list.
   \param Delete Destructor for the elements in the list.
   \param LessThan The operator to use when sorting the elements in the heap. Smaller 
                   elements are in the top of the heap and, thus, are returned first
		   using \ref ExtractMinElement.
   \param userData The pointer to the data to pass to the LessThan operator as a
                   third parameter.
   \param hasIDs TRUE if elements in the heap have will have an identifier.
   \param max_ele Initial number of elements in the heap. This can be extended on-line
                  but the execution it is more efficient if we have a good guess for this value.
   \param heap The heap to initialize.
 */
void InitHeap(unsigned int ele_size,
	      void (* Copy)(void *,void*),
	      void (* Delete)(void *),
	      boolean (* LessThan)(void *,void *,void *),
	      void *userData,
	      boolean hasIDs,
	      unsigned int max_ele,Theap *heap);

/** 
   \brief Copy constructor.

   Copies \e h_src into \e h_dst. This is a constructor and, thus,
   \e h_dst is initialized inside this function.

   \param h_dst The heap to define.
   \param h_src The heap from where to get the data.  
*/
void CopyHeap(Theap *h_dst,Theap *h_src);

/** 
   \brief Resets a heap.
   
   Removes all the elements from a heap.

   \param heap The heap to reset.
 */
void ResetHeap(Theap *heap);

/** 
   \brief Gets the number of elements in a heap.
   
   Returns  the number of elements in a heap. 

   \param heap The heap to query.

   \return The number of elements in the heap.
 */
unsigned int HeapSize(Theap *heap);

/** 
   \brief Checks if a heap is empty.
   
   Checks if a heap is empty

   \param heap The heap to query.

   \return TRUE if there are no elements in the heap.
 */
boolean HeapEmpty(Theap *heap);

/** 
   \brief Adds an element to the heap.
   
   Adds an element to the heap.

   \param id The identifier of the element.
   \param e Pointer to the element add to the heap. 
   \param heap The heap to update.
*/
void AddElement2Heap(unsigned int id,void *e,Theap *heap);

/** 
   \brief Updates the position of an element in the heap.
   
   Updates the position of an element in the heap given its identifier.

   This function only works for heaps whose elements have an
   associated identifier (the identifier is required to locate
   the element to update in the heap). If the elements have
   no asssocated identifer this function triggers an error.

   If the element is not included in the heap, it is added.
   
   \param id The identifier the element whose priority need to be
             reconsidered.
   \param e The new value for the heap element with the given
            identifier.
   \param heap The heap to update.
*/
void UpdateHeapElement(unsigned int id,void *e,Theap *heap);

/** 
   \brief Returns a pointer to a heap element.
   
   Returns a pointer to a given heap element.

   \param i The heap position to retrive.
   \param heap The heap to query.

   \return A pointer to the requested heap element or NULL if the
           heap position \e i is free.
 */
void *GetHeapElement(unsigned int i,Theap *heap);

/** 
   \brief Returns a pointer to a heap element given the element
          identifier.
  
   Returns a pointer to a heap element given the element
   identifier.

   \param id The identifier of the object to retrive.
   \param heap The heap to query.
*/
void *GetHeapElementWithID(unsigned int id,Theap *heap);

/** 
   \brief Returns the current position in the heap of an element
          given its identifier.

    Returns the current position in the heap of an element
    given its identifier.

    \param id The identifier of the object whose position is to be
              retrived.
    \param heap The heap to query.
*/
unsigned int GetHeapPosition(unsigned int id,Theap *heap);

/** 
   \brief Extracts and removes the minimal element of a heap.
   
   Returns a pointer to a the minimal (i.e., the first) element 
   of a heap and removes the element from the heap.

   This function triggers an error if the heap is empty.

   \param e Pointer to a space where to store the element to be
            extracted from the heap.
   \param heap The heap to query and update.
   
   \return The identifier of the extracted element, if any. NO_UINT otherwise.
 */
unsigned int ExtractMinElement(void *e,Theap *heap);

/** 
   \brief Destructor.
   
   Deletes the information stored in the heap and frees the allocated memory space.

   \param heap The heap to be deleted.
 */
void DeleteHeap(Theap *heap);

#endif
