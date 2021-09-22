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

#ifndef YY_READPARAMETERS_READPARAMETERS_TAB_H_INCLUDED
# define YY_READPARAMETERS_READPARAMETERS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ReadParametersdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _TRUE = 258,
    _FALSE = 259,
    _OR = 260,
    _AND = 261,
    _NOT = 262,
    _GEQ = 263,
    _LEQ = 264,
    _EQU = 265,
    _PI = 266,
    _COS = 267,
    _SIN = 268,
    _TAN = 269,
    _EXP = 270,
    _LOG = 271,
    _SQRT = 272,
    _INF = 273,
    _EPSILON = 274,
    _REPRESENTATION = 275,
    _SIGMA = 276,
    _SMALL_SIGMA = 277,
    _R = 278,
    _SR = 279,
    _E = 280,
    _CE = 281,
    _DELTA = 282,
    _BETA = 283,
    _RHO = 284,
    _STATE_PERIOD = 285,
    _N_SOLUTIONS = 286,
    _MAX_NEWTON_ITERATIONS = 287,
    _N_DOF = 288,
    _GAMMA = 289,
    _DUMMIFY = 290,
    _SPLIT_TYPE = 291,
    _SAFE_SIMPLEX = 292,
    _SIMPLIFICATION_LEVEL = 293,
    _LR2TM_Q = 294,
    _LR2TM_S = 295,
    _VDW_RATIO = 296,
    _LINKS = 297,
    _FLINKS = 298,
    _QLINKS = 299,
    _JOINTS = 300,
    _CUT_X = 301,
    _CUT_Y = 302,
    _CUT_Z = 303,
    _COEF_TEMP = 304,
    _NFAIL_MAX = 305,
    _DETECT_BIFURCATIONS = 306,
    _MAX_PLANNING_TIME = 307,
    _MAX_CHARTS = 308,
    _MAX_PLANNING_ITERATIONS = 309,
    _MAX_NODES_RRT = 310,
    _BI_RRT = 311,
    _RRT_GRAPH = 312,
    _DYNAMIC_DOMAIN = 313,
    _CD_ENGINE = 314,
    _SOLID = 315,
    _VCOLLIDE = 316,
    _PQP = 317,
    _FCL = 318,
    _C_FCL = 319,
    _BULLET = 320,
    _C_BULLET = 321,
    _RIGIDCLL = 322,
    _NONE = 323,
    _SAMPLING = 324,
    _TANGENT_SAMPLING = 325,
    _AMBIENT_SAMPLING = 326,
    _KDTREE_SAMPLING = 327,
    _PRETENSION = 328,
    _DYNAMICS = 329,
    _L_TRAPEZOID = 330,
    _L_EULER = 331,
    _L_RK4 = 332,
    _EULER = 333,
    _RK4 = 334,
    _INTEGRATION_TIME = 335,
    _DEFAULT_MAX_VELOCITY = 336,
    _N_DYNAMIC_ACTIONS = 337,
    _DYNAMIC_GOAL_ERROR = 338,
    _G_COMPENSATION = 339,
    _NEG_LM = 340,
    _G_AXIS = 341,
    _X = 342,
    _Y = 343,
    _Z = 344,
    _TAU = 345,
    _LQR_PLANNING_TIME = 346,
    _INTEGER = 347,
    _REAL = 348,
    _MIN_PRECEDENCE = 349,
    _MAX_PRECEDENCE = 350
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
 
  double realValue;

#line 157 "readparameters.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE ReadParameterslval;

int ReadParametersparse (void);

#endif /* !YY_READPARAMETERS_READPARAMETERS_TAB_H_INCLUDED  */
