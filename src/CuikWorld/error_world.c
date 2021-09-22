#include "error_world.h"

#include "error.h"

#include <stdlib.h>
#include <stdio.h>

/** \file readworld.l
    \brief Lexical analizer of \e .world files.

    Lexical analizer of \e .world files. This file is processed by lex to produce
    a \e C parser. This file contains  the keyword and regular expressions accepted
    in \e .world files.

    \sa readworld.y
*/

/** \file readworld.y
    \brief Syntactic analizer of \e .world files

    Syntactic analizer of \e .world files. This file is processed by yacc to produce
    a \e C syntax analizer. This file contains  the grammar  accepted
    in \e .world files.

    The syntax for \e .world files is described <a href="../images/world.pdf">here</a>.

    \sa readworld.l
*/ 

/** 
   \file error_world.c

   \brief Implementation of world error and warning functions.

   Implementation of world error and warning functions.
   
   \sa error_world.h
*/

/** 
   \brief Number of the line currently parsed when reading a \e .world file.

   Number of the line currently parsed when reading a \e .world file.   
*/
unsigned int RWline=0; 

int ReadWorlderror(const char *s) 
{ 
  char ErrorText[500];

  sprintf(ErrorText,"Syntax Error in .world file at line %u (%s)",RWline,s);
  Error(ErrorText);

  return(EXIT_FAILURE);
}
