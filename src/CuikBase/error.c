#include "error.h"

#include <stdlib.h>
#include <stdio.h>

/** \file readcuiksystem.l
    \brief Lexical analizer of \e .cuik files

    Lexical analizer of \e .cuik files. This file is processed by lex to produce
    a \e C parser. This file contains  the keyword and regular expressions accepted
    in \e .cuik files.

    \sa readcuiksystem.y.
*/ 

/** \file readcuiksystem.y
    \brief Syntactic analizer of \e .cuik files

    Syntactic analizer of \e .cuik files. This file is processed by yacc to produce
    a \e C syntax analizer. This file contains  the grammar  accepted
    in \e .cuik files.

    \sa readcuiksystem.l.
*/ 

/** \file readparameters.l
    \brief Lexical analizer of \e .param files.

    Lexical analizer of \e .param files. This file is processed by lex to produce
    a \e C parser. This file contains  the keyword and regular expressions accepted
    in \e .param files.

    The syntax for \e .cuik files is described <a href="../images/cuik.pdf">here</a>.

    \sa readparameters.y.
*/

/** \file readparameters.y
    \brief Syntactic analizer of \e .cuik files

    Syntactic analizer of \e .param files. This file is processed by yacc to produce
    a \e C syntax analizer. This file contains  the grammar  accepted
    in \e .param files.
    
    To add one parameter we have to:
        - Edit parameters.h to increment the constant NPARAMETERS and add a new
          constant to designate the new constant.
        - Add an identifier for the constant in readparameters.l
        - Define the new toke in the file readparameters.y
        - Add a new initialization rule in readparameters.y
        .

    \sa readparameters.l.
*/ 

/** 
   \file error.c

   \brief Implementation of error and warning functions.

   Implementation of error and warning functions.
   
   \sa error.h.
*/

/** 
   \brief Number of the line currently parsed when reading a \e .cuik file.

   Number of the line currently parsed when reading a \e .cuik file.   
*/
unsigned int RCSline=0; /*defined in the yac module*/

/** 
   \brief Number of the line currently parsed when reading a \e .param file.

   Number of the line currently parsed when reading a \e .param file.   
*/
unsigned int RPNline=0; 

void Error(const char *s)
{
  fprintf(stderr,"\nERROR: %s.\n\n",s);
  fflush(stdout);
  fflush(stderr);
  exit(EXIT_FAILURE);
}

int Readcuiksystemerror(const char *s) 
{ 
  char ErrorText[500];

  sprintf(ErrorText,"\nSyntax Error in .cuik file at line %u (%s)",RCSline,s);
  Error(ErrorText);

  return(EXIT_FAILURE);
}

int ReadParameterserror(const char *s)
{ 
  char ErrorText[500];

  sprintf(ErrorText,"\nSyntax Error in .param file at line %u (%s)",RPNline,s);
  Error(ErrorText);

  return(EXIT_FAILURE);
}

void ReadcuiksystemSemanticError(const char *s)
{
   char ErrorText[500];

  sprintf(ErrorText,"\nSemantic Error at line %u: %s",RCSline,s);
  Error(ErrorText); 
}

void Warning(const char *s)
{
  fprintf(stderr,"\nWARNING: %s.\n\n",s);
  fflush(stderr);
}
