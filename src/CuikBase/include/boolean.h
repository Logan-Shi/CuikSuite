#ifndef BOOLEANH 
#define BOOLEANH
 
/** \file boolean.h
    \brief Definition of the boolean type.
*/

/**
 \brief Boolean type.

 Type with two possible values: TRUE,FALSE.
*/
typedef unsigned int boolean; 

#ifndef TRUE
  /**
     \brief TRUE

     TRUE   
  */
  #define TRUE  1
#endif

#ifndef FALSE
  /**
     \brief FALSE

     FALSE   
  */
  #define FALSE 0
#endif
 
#endif
