#ifndef BOX_HEAPH
#define BOX_HEAPH

#include "heap.h"
#include "box_list.h"
#include "box.h"
#include "boolean.h"


/** \file box_heap.h
    \brief Collection of methods to work on Theap of boxes. 

    This is a collection of functions working on box heaps. 
    A box heap is a special heap including boxes. 
    This specialization is handy since it facilitates the manipulation of
    sorted sets of boxes.

    \sa heap.h, box.h, Theap, Tbox.
*/

/** \brief Initial room for boxes in a heap of boxes.

    Initial room for boxes in a heap. It will be enlarged if necessary.

    \sa InitHeap
*/
#define INIT_NUM_BOXES_IN_HEAP 100

/**  
    \brief Constructor. 

    Defines an empty heap of boxes.

    \param LessThan The function defining the sorting criterion for
                    the boxes in the heap. 
    \param userData The pointer to the data to pass to the LessThan operator as a
                    third parameter.
    \param h The heap to create.

    \sa CmpBoxDepthFirst, CmpBoxBreadthFirst, InitHeap. 
*/
void InitHeapOfBoxes(boolean (* LessThan)(void *,void*,void*),void *userData,Theap *h);



/**  
    \brief Adds a box to a heap of boxes.

    Adds a box to a heap of boxes. The box is copied into the heap
    and, thus, it can be freely modified after calling this function.

    \param b The box to add.
    \param h The heap where to add the box.
*/
void AddBox2HeapOfBoxes(Tbox *b,Theap *h);

/**  
    \brief Computes the volume of a heap. 

    Computes the sum of the volume of the boxes stored in the heap.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param h The heap.

    \sa BoxVolume
*/
double HeapOfBoxesVolume(boolean *used,Theap *h);

/**  
    \brief Computes the maximum diagonal for all boxes in a heap. 

    Computes the maximum diagonal for all the boxes stored in the heap.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param h The heap.

    \sa BoxDiagonal
*/
double HeapOfBoxesMaxDiagonal(boolean *used,Theap *h);


/**  
    \brief Computes the maximum size for all boxes in a heap. 

    Computes the maximum size for all the boxes stored in the heap.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param h The heap.

    \sa BoxSize
*/
double HeapOfBoxesMaxSize(boolean *used,Theap *h);

/** 
    \brief Converts a heap of boxes into a list.

    Converts a heap of boxes into a list of boxes.
    The list is constructed (i.e., initialized) inside
    the function.
    
    \param l The list to defined.
    \param h The heap to convert into a list.
    
    \sa box_list.h
*/
void Heap2List(Tlist *l,Theap *h);

/** 
    \brief Adds a list of boxes into a heap.

    Adds a list of boxes into a previously initialized heap.
    
    \param l The list with the boxes to add to the heap.
    \param h The heap where to add the boxes.
    
    \sa box_list.h
*/
void AddList2Heap(Tlist *l,Theap *h);


/**  
    \brief Prints a heap of boxes. 

    Prints a heap of boxes to a stream that can be <em>stdout</em>.

    The elements of the heap are printed breadth first.
    
    \param f The stream where to write.
    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param heading A string to be printed before each box. Possibly NULL, in which case
           nothing is printed. This is used to differentiate heap printed in the
	   same file.
    \param h The heap to be printed.
    
    \sa PrintBox
*/
void PrintHeapOfBoxes(FILE *f,boolean *used,char *heading,Theap *h);

#endif
