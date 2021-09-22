#ifndef SAMPLEH
#define SAMPLEH

#include "vector.h"
#include "box.h"


/**
    \file sample.h
    \brief Definition of the Tsample type and the associated functions.

    Definition of the Tsample  type and the associated functions.

    \sa Tsample, sample.c.
*/

/************************************************************************************/
/** \brief Alias of NO_UINT for samples.

    Alias of NO_UINT for samples.
*/
#define NO_SAMPLE_ID NO_UINT
/************************************************************************************/


/**
   \brief A sample.

   A sample, that is, a point in the configuration space of the mechanism at hand.
   Therefore, sample can be called also \e configurations. We use the name sample
   because we mainly use them in the contex of probabilistic path planning.

   For samples, only the system variables of the mechanisms are used since these are
   the only ones that are involved in the motion of the mechanism.
 
   \sa sample.h,sample.c.
*/
typedef struct {
  unsigned int sID; /**< Identifier of the sample.*/
  unsigned int boxID; /**< Identifier of the box in the graph of boxes
			   that includes the sample. */
  Tvector v; /**< Vector of doubles, one for each one of the system variables 
		  of the mechanism. */
} Tsample;

/**
   \brief Constructor.
   
   Initializes a new sample.

   \param sID The identifier assigned to the sample.
   \param n Number of system variables in the mechanism at hand.
   \param v Array of doubles, one for each system variable in the mechanism.
   \param boxID Identifier of the box that holds the sample. NO_UINT if the
                sample is not assiged to any box yet.
   \param s The sample to initialize.
*/
void InitSample(unsigned int sID,unsigned int n,double *v,unsigned int boxID,Tsample *s);

/**
   \brief Constructor.
   
   Initializes a new sample from a box. The values for the sample are taken from
   the box center for the system variables.

   \param sID The identifier assigned to the sample.
   \param systemVar Array of booleans, one for each dimension of the given box where
                    only entries for system variables are set to TRUE.
   \param b The box from where to get the values.
   \param boxID Identifier of the box that holds the sample. NO_UINT if the
                sample is not assiged to any box yet.
   \param s The sample to initialize.
*/
void InitSampleFromBox(unsigned int sID,boolean *systemVar,Tbox *b,unsigned int boxID,Tsample *s);

/**
   \brief Gets the values of the sample.

   Gets the values of the sample.

   \param s The sample to query.

   \return A pointer to the vector with the doubles, one for each system variable
           in the mechanism at hand.
*/
Tvector *GetSampleValues(Tsample *s);

/**
   \brief Gets the value for a given dimension of the sample.

   Gets the value for a given dimension of the sample.

   \param n The dimension to query
   \param s The sample to query.

   \return The value of the sample along the requested dimension.
*/
double GetSampleValue(unsigned int n,Tsample *s);

/**
   \brief Gets the identifier of the box that includes the sample.

   Gets the identifier of the box that includes the sample.

   \param s The sample to query.

   \return The identifier of the box that includes the sample. Can be NO_UINT if the
           sample is not assigned to any box yet.
*/
unsigned int GetSampleBoxID(Tsample *s);

/**
   \brief Gets the identifier of the sample.

   Gets the identifier of the sample.

   \param s The sample to query.

   \return The identifier of the sample.
*/
unsigned int GetSampleID(Tsample *s);

/**
   \brief Changes the identifier of the box to which the sample is linked.

   Changes the identifier of the box to which the sample is linked.

   \param boxID The new box identifier to store in the sample.
   \param s The sample to update.
*/
void SetSampleBoxID(unsigned int boxID,Tsample *s);

/** 
    \brief Constructor.
  
    Creates a new sample copying the information from another sample.

    \param s_dst The sample to initialize.
    \param s_src The sample from where to copy the data.
*/
void CopySample(void *s_dst,void *s_src);

/** 
    \brief Returns the dimensionality of the space where the sample
           is defined.
  
    Returns the dimensionality of the space where the sample
    is defined, i.e., the dimensionality of the configuration
    space.

    \param s The sample to query.
*/
unsigned int GetSampleDim(Tsample *s);


/** 
    \brief Computes the Euclidean distance between two samples.
    
    Computes the Euclidean distance between two samples. This is a lower
    bound of the distance between the two samples on the configuration
    space.

    \param s1 The first sample.
    \param s2 The second sample.
*/
double GetSampleDistance(Tsample *s1,Tsample *s2);

/**
   \brief Prints a sample.

   Prints the information stored in the sample. Only
   the values for each one of the system variables is printed.
   This is in contrast with \ref SaveSample that prints allç
   the information stored in the sample (values for the variables,
   identifier, box identifier, etc).

   \param f The file where to save the data.
   \param s The sample to print.
*/
void PrintSample(FILE *f,Tsample *s);

/** 
    \brief Saves the information of the sample in a file.

    Saves the information of the sample in a file.

    \param f The file where to save the data.
    \param s The sample to save.
*/
void SaveSample(FILE *f,Tsample *s);


/** 
    \brief Constructor.
  
    Creates a new sample reading the information from a file.

    \param f The file from where to read the information.
    \param s The sample to initialize.
*/
void LoadSample(FILE *f,Tsample *s);

/** 
    \brief Destructor.
    
    Deletes the information stored in a Tsample and frees the allocated memory.

    \param s The sample to delete.
*/
void DeleteSample(void *s);

#endif
