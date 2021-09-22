#ifndef BOX_LISTH
#define BOX_LISTH

#include "list.h"
#include "box.h"
#include "boolean.h"


/** \file box_list.h
    \brief Collection of methods to work on Tlist of boxes. 

    This is a collection of functions working on box lists. 
    A box list is a special list including boxes. 
    This specialization is handy since it facilitates the manipulation of sets
    of boxes.<br>
    It its assumed that all boxes in a list have the same dimensionality.
    If this is not so, some of the functions implement here will generate errors.

    \sa list.h, box.h, Tlist, Tbox.
*/

/**  
    \brief Constructor. 

    Defines an empty list of boxes.

    \param l The list to create.
*/
void InitListOfBoxes(Tlist *l);


/**  
    \brief Copy constructor. 

    Copies one list into another.<br>
    
    The boxes in <em>l_src</em> are duplicated before
    inserting them into <em>l_dst</em>. 

    \param l_dst The new list to create.
    \param l_src The source list from which to copy.
*/
void CopyListOfBoxes(Tlist *l_dst,Tlist *l_src);

/**  
    \brief Computes the volume of a list. 

    Computes the sum of the volume of the boxes stored in the list.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param l The list.

    \sa BoxVolume
*/
double ListOfBoxesVolume(boolean *used,Tlist *l);


/**  
    \brief Computes the maximum diagonal for all boxes in a list. 

    Computes the maximum diagonal for all the boxes stored in the list.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param l The list.

    \sa BoxDiagonal
*/
double ListOfBoxesMaxDiagonal(boolean *used,Tlist *l);


/**  
    \brief Computes the maximum size for all boxes in a list. 

    Computes the maximum size for all the boxes stored in the list.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param l The list.

    \sa BoxSize
*/
double ListOfBoxesMaxSize(boolean *used,Tlist *l);

/**  
    \brief Computes an axis-aligned bounding box for all boxes in a list. 

    Computes a box that is an axis-aligned bounding box for all boxes in a list.<br>
    This is a box constructor and, therefore box <em>b</em> does not need to be
    initialized externally before calling this function.<br>
    The dimensionality of the output box is that of the boxes in the list.<br>
    If the list is empty it returns a dimension-less box.

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param b The output box defining the bounding box for the boxes in the list
             for the <em>used</em> dimensions.
    \param l The list.

    \sa BoxUnion
*/
void ListOfBoxesBB(boolean *used,Tbox *b,Tlist *l);

/**  
    \brief Clusters a list of boxes. 

    Computes a list of boxes, with one box bounding each one of the connected
    components defined by the boxes in the input list.<br>
    A box is included in a connected component if it has a non-null intersection with
    one of the boxes already in the component.<br>

    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param l_out The output list, with one box for each one of the clusters of the input
                 list.
    \param l_in The input list to be clustered.
*/
void ListOfBoxesCluster(boolean *used,Tlist *l_out,Tlist *l_in);

/**
   \brief Concats two lists.
   
   Adds \e l_new at the end of \e l. We assume \e l to be
   properly initialized.

   \param l_new The list to add.
   \param l The list where to add.
*/
void ConcatListOfBoxes(Tlist *l_new,Tlist *l);

/**
   \brief Reverses a list.
   
   Reverses the order of a list.

   This is a constructor and, thus, \e l is initialized
   inside the function.

   \param l_orig The list to reverse.
   \param l The ouput reversed list.
*/
void ReverseListOfBoxes(Tlist *l_orig,Tlist *l);

/**  
    \brief Prints a list of boxes. 

    
    Prints a list of boxes to a stream that can be <em>stdout</em>.
    
    \param f The stream where to write.
    \param used Array of booleans, one for each interval of the input boxes. If the
           boolean is TRUE, the corresponding interval is used in the computations. 
	   If the given pointer is NULL, all intervals are used.
    \param heading A string to be printed before each box. Possibly NULL, in which case
           nothing is printed. This is used to differentiate list printed in the
	   same file.
    \param l The list to be printed.
    
    \sa PrintBox
*/
void PrintListOfBoxes(FILE *f,boolean *used,char *heading,Tlist *l);


/**  
    \brief Reads a list of boxes from a file. 

    This is a constructor from a file.
    
    \param filename The name of the file from where to read the boxes.
    \param l The list to initialize.
    
    \return TRUE if the given file exists and it could be opened 
            and \ref FALSE otherwise.

    \sa ReadBox
*/

boolean ReadListOfBoxes(char *filename,Tlist *l);

/**  
    \brief Saves a list of boxes. 

    
    Saves a list of boxes to a stream in binary format.
    
    \param f The stream where to write.
    \param l The list to be saved.
    
    \sa SaveBox
*/
void SaveListOfBoxes(FILE *f,Tlist *l);

/**  
    \brief Loads a list of boxes from a file. 

    This is a constructor from a file in binary format.
    
    \param f The binary stream from where to read the list.
    \param l The list to be created from the binary file.
    
    \sa LoadBox
*/
void LoadListOfBoxes(FILE *f,Tlist *l);


/**  
    \brief Destructor

    Destructor
    
    \param l The list to be deleted.
    
    \sa DeleteBox
*/
void DeleteListOfBoxes(Tlist *l);

#endif
