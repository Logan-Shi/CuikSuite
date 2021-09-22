/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_READCUIKSYSTEM_READCUIKSYSTEM_TAB_H_INCLUDED
# define YY_READCUIKSYSTEM_READCUIKSYSTEM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int Readcuiksystemdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _CONSTANTS = 258,
    _SYSTEM_VARS = 259,
    _SECONDARY_VARS = 260,
    _DUMMY_VARS = 261,
    _CARTESIAN_VARS = 262,
    _VELOCITY_VARS = 263,
    _NON_DYNAMIC_VARS = 264,
    _SYSTEM_EQS = 265,
    _COORD_EQS = 266,
    _DUMMY_EQS = 267,
    _VELOCITY_EQS = 268,
    _NON_DYNAMIC_EQS = 269,
    _SEARCH = 270,
    _DEPTH = 271,
    _BREADTH = 272,
    _FIRST = 273,
    _MIN = 274,
    _EQU = 275,
    _LEQ = 276,
    _GEQ = 277,
    _ASSIGN = 278,
    _INF = 279,
    _PI = 280,
    _SIN = 281,
    _COS = 282,
    _TAN = 283,
    _COT = 284,
    _ACOS = 285,
    _ASIN = 286,
    _ATAN = 287,
    _ATAN2 = 288,
    _EXP = 289,
    _PWP = 290,
    _SQRT = 291,
    _ABS = 292,
    _DIFF = 293,
    _PARAMETER = 294,
    _PRINT = 295,
    _TR = 296,
    _TX = 297,
    _TY = 298,
    _TZ = 299,
    _TV = 300,
    _PA = 301,
    _RX = 302,
    _RY = 303,
    _RZ = 304,
    _ID = 305,
    _Z = 306,
    _DRX = 307,
    _DRY = 308,
    _DRZ = 309,
    _DPA_U = 310,
    _DPA_V = 311,
    _DDRX = 312,
    _DDRY = 313,
    _DDRZ = 314,
    _DDPA_UU = 315,
    _DDPA_UV = 316,
    _DDPA_VV = 317,
    _INV = 318,
    _EQUAL = 319,
    _LESS = 320,
    _GREATER = 321,
    _IDENTIFIER = 322,
    _INTEGER = 323,
    _REAL = 324,
    _MIN_PRECEDENCE = 325,
    _NOT_EQUAL = 326,
    _MAX_PRECEDENCE = 327
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 69 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
 
  char *id; 
  int int_number;
  double real_number;
  Texpr expr;

#line 137 "readcuiksystem.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE Readcuiksystemlval;

int Readcuiksystemparse (void);

#endif /* !YY_READCUIKSYSTEM_READCUIKSYSTEM_TAB_H_INCLUDED  */
