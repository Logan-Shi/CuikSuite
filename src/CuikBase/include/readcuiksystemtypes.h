#ifndef YACTYPESCSH
#define YACTYPESCSH


/** 
   \file readcuiksystemtypes.h

   \brief Definition of data types shared between the lexical and the syntactical
          analizer for \e .cuik files. 

   Definition of data types shared between the lexical and the syntactical
   analizer for \e .cuik files. 

   \sa readcuiksystem.l, readcuiksystem.y
*/

/** 
   \brief Expressions that appear in the constant declarations
          are either variables (and have and name) or constants 
	  (and have a value).

   Expressions that appear in the constant declarations
   are either variables (and have and name) or constants 
   (and have a value).
	  
   \sa readcuiksystem.l, readcuiksystem.y
*/
typedef struct {  
  char *id; /**< If the expression is a variable, we store its name */
  double value; /**< If the expression is constant, we store its value. */
} Texpr;

#endif
