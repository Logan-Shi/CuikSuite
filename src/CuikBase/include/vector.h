#ifndef VECTORH
#define VECTORH 

#include "boolean.h"
#include <stdio.h>

/** 
   \file vector.h
   \brief Definition of the Tvector type and the associated functions. 

   Definition of the Tvector type and the associated functions implementing
   a generic vector structure.

   The vectors are like arrays of any possible type. To define a vector on
   a particular type, we need of two basic operators defined on this type:
   - A copy constructor.
   - A destructor
   . 
   Optionally, to perform search operations we will need a comparison operator.
   
   In this same file (vector.h) we give copy constructors, destructor and comparison
   operators for the basic and most common types used to define vectors: identifiers
   (i.e., unsigned int), doubles, and pointers.

   Note that when removing an element from a vector the vector is not compacted and,
   thus, the vector can have empty entries. Therefore, before using the elements obtained
   from a vector, we have to check whether they are valid or not (a NULl pointer is
   returned when accessing an empty vector position).

   Many sets (constants, variables, equations,....) could be implemented using
   \ref Tvector. Currently this is not so for legacy reason (those objects where implemented
   much before \ref Tvector, for previous versions of cuik). A similar issue occurs
   with \ref Tlist : it could be implemented using the philosophy  of \ref Tvector (with
   a copy constructor, a destructor,... stored in the generic data, \ref Tlist in this case).
   This is not this way becaus \ref Tlist was implemented much before \ref Tvector.

   \sa Tvector, vector.c.
*/


/** 
   \brief Comparison operator for identifiers.
   
   Comparison operator for identifiers. To be used when defining a vector of
   identifiers (i.e., unsigned int).

   \param a Pointer to the first identifier to compare.
   \param b Pointer to the second identifier to compare.

   \return TRUE if the two inputs are the same.
*/
boolean CmpID(void *a,void *b);

/** 
   \brief Copy constructor for identifiers.
   
   Copy constructor for identifiers. To be used when defining a vector of
   identifiers (i.e., unsigned int). This is a direct assignation. 

   \param a Pointer to the identifier to initialize.
   \param b Pointer to the identifier from where to copy.
*/
void CopyID(void *a,void *b);
/** 
   \brief Destructor for identifiers.
   
   Destructor for identifiers. To be used when defining a vector of
   identifiers (i.e., unsigned int). This basically frees the space taken by 
   the identifier.

   \param a Pointer to the identifier to delete.
*/
void DeleteID(void *a);


/** 
   \brief Comparison operator for doubles.
   
   Comparison operator for doubles. To be used when defining a vector of
   doubles. 

   \param a Pointer to the first double to compare.
   \param b Pointer to the second double to compare.

   \return TRUE if the two inputs are the same.
*/
boolean CmpDouble(void *a,void *b);
/** 
   \brief Copy constructor for doubles.
   
   Copy constructor for doubles. To be used when defining a vector of
   doubles. This is a direct assignation.

   \param a Pointer to the double to initialize.
   \param b Pointer to the double from where to copy.
*/
void CopyDouble(void *a,void *b);
/** 
   \brief Destructor for doubles.
   
   Destructor for doubles. To be used when defining a vector of
   doubles. This basically frees the space taken by the double.

   \param a Pointer to the double to delete.
*/
void DeleteDouble(void *a);


/** 
   \brief A pair of dubles.

   A pair of doubles.
*/
typedef struct {
  double f; /**< The first double in the pair. */
  double s; /**< The second double in the pair. */
} TDoublePair;

/** 
    \brief Constructor.

    Defines a double pair form two doubles.
    
    \param f The first double.
    \param s The second double.
    \param p The resulting pair structure.
*/
void NewDoublePair(double f,double s,TDoublePair *p);

/** 
    \brief The first element of a pair.

    Returns the first element of a pair of doubles.
    
    \param p The pair.

    \return The first element of 'p'.
*/
double FirstInPair(TDoublePair *p);

/** 
    \brief The second element of a pair.

    Returns the second element of a pair of doubles.
    
    \param p The pair.

    \return The second element of 'p'.
*/
double SecondInPair(TDoublePair *p);

/** 
   \brief Comparison operator for paris of doubles.
   
   Comparison operator for pairs of doubles. To be used when defining a vector of
   pairs of doubles. 

   \param a Pointer to the first pair of doubles to compare.
   \param b Pointer to the second pair of doubles to compare.

   \return TRUE if the two inputs are the same.
*/
boolean CmpDoublePair(void *a,void *b);

/** 
   \brief Copy constructor for pairs of doubles.
   
   Copy constructor for pairs of doubles. To be used when defining a vector of
   pairs of doubles. This is a direct assignation.

   \param a Pointer to the pair of doubles to initialize.
   \param b Pointer to the pair of doubles from where to copy.
*/
void CopyDoublePair(void *a,void *b);

/** 
   \brief Destructor for pairs of doubles.
   
   Destructor for pairs of doubles. To be used when defining a vector of
   doubles. This basically frees the space taken by the pair of double.

   \param a Pointer to the double to delete.
*/
void DeleteDoublePair(void *a);


/** 
   \brief Comparison operator for void pointers.
   
   Comparison operator for doubles. To be used when defining a vector of
   pointers. 

   \param a Pointer to the first pointer to compare.
   \param b Pointer to the second pointer to compare.

   \return TRUE if the two inputs are the same.
*/
boolean CmpVoidPtr(void *a,void *b);
/** 
   \brief Copy constructor for void pointers.
   
   Copy constructor for doubles. To be used when defining a vector of
   pointers. This is a direct assignation.

   \param a Pointer to the pointer to initialize.
   \param b Pointer to the pointer from where to copy.
*/
void CopyVoidPtr(void *a,void *b);
/** 
   \brief Destructor for void pointers.
   
   Destructor for void pointers. To be used when defining a vector of
   pointers. This basically frees the space taken by the pointer.

   \param a Pointer to the pointer to delete.
*/
void DeleteVoidPtr(void *a);

/** 
   \brief A generic vector.

   A generic vector.

   \sa vector.h, vector.c.
   
 */
typedef struct
{  
  void **elements;              /**< Data stored in the vector. */
  unsigned int ele_size;        /**< Size of each element indexed from elements. */
  unsigned int num_ele;   	/**< Current number of elements of the vector. */
  unsigned int max_ele;   	/**< Maximum number of elements of the vector. Extended as necessary. */
  void (* Copy)(void *,void*);  /**< The copy operator*/
  void (* Delete)(void *);      /**< The delete operator */
} Tvector;

/** 
   \brief Constructor
   
   Initializes an empty vector
   Examples of use:
   - InitVector(sizeof(unsigned int),CopyID,DeleteID,MaxNumEle,&vector);
   - InitVector(sizeof(double),CopyDouble,DeleteDouble,MaxNumEle,&vector);
   - InitVector(sizeof(void *),CopyPtr,DeletePtr,MaxNumEle,&vector);
   .
   Alternatively you can also use
   - InitVector(sizeof(unsigned int),CopyID,NULL,MaxNumEle,&vector);
   - InitVector(sizeof(double),CopyDouble,NULL,MaxNumEle,&vector);
   - InitVector(sizeof(void *),CopyPtr,NULL,MaxNumEle,&vector);
   .
   since the delete functions are actually empty.

   \param ele_size Number of bytes taken by each element in the list.
   \param Copy Copy constructor for the elements in the list.
   \param Delete Destructor for the elements in the list.
   \param max_ele Initial number of elements in the vector. This can be extended on-line
                  but the execution it is more efficient if we have a good guess 
		  for this value.
   \param vector The vector to initialize.
 */
void InitVector(unsigned int ele_size,
		void (* Copy)(void *,void*),
		void (* Delete)(void *),
		unsigned int max_ele,Tvector *vector);

/** 
   \brief Resets a vector.
   
   Removes all the elements from a vector but it does not frees the
   allocated memory nor resets the maximum number of elements. If you
   plan to re-use a vector it is more efficient to reset it instead
   of deleting it and re-initializing it again.

   \param vector The vector to reset.
 */
void ResetVector(Tvector *vector);

/** 
   \brief Copy constructor
   
   Initializes a vector from another vector.

   \param v_dst The vector to initialize.
   \param v_src The vector from where to copy.
 */
void CopyVector(Tvector *v_dst,Tvector *v_src);

/** 
   \brief Finds a free position in the vector.
   
   Returns the first (i.e., with lower identifier) free position in a vector.

   \param vector The vector to query.

   \return The index of the free position.
 */
unsigned int VectorFirstFreePos(Tvector *vector);

/** 
   \brief Gets the number of elements in a vector.
   
   Returns  the number of elements in a vector. Note that the vector can
   have "holes", i.e., empty slots in position explicitly deleted using RemoveVectorElement.

   \param vector The vector to query.

   \return The number of elements in the vector.

   \sa RemoveVectorElement
 */
unsigned int VectorSize(Tvector *vector);

/** 
   \brief Gets the maximum number of elements in a vector.
   
   Returns  the maximum number of elements in a vector. Note that the vector can
   have "holes", i.e., empty slots in position explicitly deleted using RemoveVectorElement.

   \param vector The vector to query.

   \return The maximum number of elements in the vector.
 */
unsigned int VectorMaxSize(Tvector *vector);

/** 
   \brief Checks if a vector is empty.
   
   Checks if a vector is empty

   \param vector The vector to query.

   \return TRUE if there are no elements in the vector.
 */
boolean VectorEmpty(Tvector *vector);

/** 
   \brief Search for an element in a vector.
   
   Looks for an element in a vector.

   \param e The element we are looking for. 
   \param cmp The comparison operator to use to determine if two
              elements are the same. Note that for structured types
	      the comparison can be based on a particular field and
	      that only those field need to be initialized in parameter \e e.
   \param vector The vector to query.

   \return TRUE if the vector includes the requested element.
 */
boolean ElementInVector(void *e,boolean (* cmp)(void *,void*),Tvector *vector);
/** 
   \brief Search for an element in a vector.
   
   Looks for an element in a vector.

   \param e The element we are looking for. 
   \param cmp The comparison operator to use to determine if two
              elements are the same. Note that for structured types
	      the comparison can be based on a particular field and
	      that only those field need to be initialized in parameter \e e.
   \param vector The vector to query.

   \return The position in the vector holding the requested element or NO_UINT if the
           vector does not include the element.
 */
unsigned int FindPos(void *e,boolean (* cmp)(void *,void*),Tvector *vector);

/** 
   \brief Adds an element to the vector.
   
   Adds an element at the end of the list.

   \param e Pointer to the element add to the vector. 
   \param vector The vector to update.

   \return The position in the vector where the element has been stored.
 */
unsigned int NewVectorElement(void *e,Tvector *vector);

/** 
   \brief Adds an element to the vector.
   
   Looks for a free vector position and stores the given element.

   \param e The element add to the vector. 
   \param vector The vector to update.

   \return The position in the vector where the element has been stored.
 */
unsigned int NewFreeVectorElement(void *e,Tvector *vector);
/** 
   \brief Adds an element to the vector in a given position.
   
    Adds an element to the vector in a given position. If the vector
    position was already occupied, the stored element is deleted before
    copying the new element.

   \param i The vector position where to store the element.
   \param e Pointer to the element add to the vector. 
   \param vector The vector to update.
 */
void SetVectorElement(unsigned int i,void *e,Tvector *vector);

/** 
   \brief Returns a pointer to a vector element.
   
   Returns a pointer to a given vector element.

   \param i The vector position to retrive.
   \param vector The vector to query.

   \return A pointer to the requested vector element or NULL if the
           vector position \e i is free.
 */
void *GetVectorElement(unsigned int i,Tvector *vector);

/** 
   \brief Returns a pointer to the last element of a vector.
   
   Returns a pointer to a the last element of a  vector.

   \param vector The vector to query.

   \return A pointer to the last element of the vector.
 */
void *GetLastElement(Tvector *vector);

/** 
   \brief Removes an element from the vector.
   
   Removes an element from the vector. Note that elements in the vector are
   not compacted after the deletion. In this way indexes in other
   data structured refered to this vector still hold after the deletion.
   The drawnback is that we can end up with a vector with  "holes"
   and we have to be carefull when retriving elements from the vector.

   \param i The vector position to delete.
   \param vector The vector to query.
 */
void RemoveVectorElement(unsigned int i,Tvector *vector);

/** 
   \brief Swaps two elements in a vector.

   Swaps two elements in a vector. This operation is provided since
   it is more efficient than extracting the two elements and then
   inserting them again in the vector in their new positions.

   If one of the two elements to swap is empty, this function triggers
   an error.

   \param i Index of the first element to swap.
   \param j Index of the second element to swap.
   \param vector The vector to update.
   
*/
void SwapVectorElements(unsigned int i,unsigned int j,Tvector *vector);

/** 
    \brief Reverses a vector.

    Reverses the elements in a vector.

    \param vector The vector to reverse.
*/
void ReverseVector(Tvector *vector);

/** 
    \brief Concatenates two vectors.

    Adds a vector to the end of another vector.

    \param vector1 The vector to add.
    \param vector The vector where to add.
*/
void ConcatVectors(Tvector *vector1,Tvector *vector);

/** 
   \brief Extracts an element from a vector.

   Extracts an element from a vector.

   The element is copied to the given buffer and removed from the vector.

   If the given element of the vector is empty, this function triggers
   an error.

   \param i Index of the element to be extracted.
   \param e Buffer where to copy the extracted element.
   \param vector The vector to update.
   
*/
void ExtractVectorElement(unsigned int i,void *e,Tvector *vector);

/** 
   \brief Moves a vector element from one position to another.

   Moves a vector element from one position to another.
   
   If the element to move is empty, this function triggers an error.

   If the element where to store the moved element is full, it is
   removed before the moving.

   \param i The index of the element to move.
   \param ni The desired new index for this element.
   \param vector The vector to update.
*/
void MoveVectorElement(unsigned int i,unsigned int ni,Tvector *vector);

/** 
   \brief Destructor.
   
   Deletes the information stored in the vector and frees the allocated memory space.

   \param vector The vector to be deleted.
 */
void DeleteVector(void *vector);

#endif
