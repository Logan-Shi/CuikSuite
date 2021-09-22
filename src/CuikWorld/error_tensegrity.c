#include "error_tensegrity.h"

#include "error.h"

#include <stdlib.h>
#include <stdio.h>

/** \file readtensegrity.l
    \brief Lexical analizer of \e .tensegrity files.

    Lexical analizer of \e .tensegrity files. This file is processed by lex to produce
    a \e C parser. This file contains  the keyword and regular expressions accepted
    in \e .tensegrity files.

    \sa readtensegrity.y
*/

/** \file readtensegrity.y
    \brief Syntactic analizer of \e .tensegrity files

    Syntactic analizer of \e .tensegrity files. This file is processed by yacc to produce
    a \e C syntax analizer. This file contains  the grammar  accepted
    in \e .tensegrity files.

    The syntax for \e .tensegrity files is described <a href="../images/tensegrity.pdf">here</a>.

    \sa readtensegrity.l
*/ 

/** 
   \file error_tensegrity.c

   \brief Implementation of tensegrity error and warning functions.

   Implementation of tensegrity error and warning functions.
   
   \sa error_tensegrity.h
*/

/** 
   \brief Number of the line currently parsed when reading a \e .tensegrity file.

   Number of the line currently parsed when reading a \e .tensegrity file.   
*/
unsigned int RTline=0; 

int ReadTensegrityerror(const char *s) 
{ 
  char ErrorText[500];

  sprintf(ErrorText,"Syntax Error in .tens file at line %u (%.400s)",RTline,s);
  Error(ErrorText);

  return(EXIT_FAILURE);
}
