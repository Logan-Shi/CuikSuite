/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         Readcuiksystemparse
#define yylex           Readcuiksystemlex
#define yyerror         Readcuiksystemerror
#define yydebug         Readcuiksystemdebug
#define yynerrs         Readcuiksystemnerrs
#define yylval          Readcuiksystemlval
#define yychar          Readcuiksystemchar

/* First part of user prologue.  */
#line 1 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
 
/** \cond */
#include "cuiksystem.h"
#include "readcuiksystemtypes.h"

#include "boolean.h"
#include "error.h"
#include "interval.h"
#include "monomial.h"
#include "equations.h"
#include "equation.h"
#include "mequation.h"
#include "kequation.h"
#include "variable.h"
#include "variable_set.h"
#include "defines.h"
#include "parameters.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>

  /*Lex and Yacc variables*/
  extern FILE *Readcuiksystemin; 

  /*Lex and Yacc functions*/
  int Readcuiksystemlex(void); 

  /*Our own variables*/
  extern unsigned int RCSline; /*line number currently processed (incremented by the LEX processor)*/
  
  double rcs_sgn=1.0; /* sign for the monomials added to an equation. */

  Tparameters *rcs_parameters=NULL;

  /*Global pointer to allow the different parts of the parser to acces the equations being initialized*/
  TCuikSystem *rcs_cuiksystem=NULL;
  
  Tequation rcs_equation;
  TMequation rcs_mequation;
  TMequation rcs_vmequation;
  TKequation rcs_kequation;
  Tmonomial rcs_monomial;

  unsigned int rcs_scaleID;
  
  unsigned int rcs_i;
  double **rcs_point;

  double rcs_vect[3];

  unsigned int rcs_eq_type=SYSTEM_EQ;
  unsigned int rcs_var_type=SYSTEM_VAR;

  unsigned int rcs_topology;
  
  Tconstants *rcs_constants;

  /* if true, variable identifiers are prefixed with '_'. This is used in atomatically
     generated equation files (and only internally). We only need to add the prefix
     when adding equations to an automatically generated system (in memory) */
  boolean rcs_prefixID;
  /* space to store the identifiers with prefix */
  char *rcs_ID;

#line 144 "readcuiksystem.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 276 "readcuiksystem.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE Readcuiksystemlval;

int Readcuiksystemparse (void);

#endif /* !YY_READCUIKSYSTEM_READCUIKSYSTEM_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1135

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  376

#define YYUNDEFTOK  2
#define YYMAXUTOK   327


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    77,
      79,    80,    74,    72,    83,    73,     2,    75,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,    87,
       2,     2,     2,    81,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    84,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   101,   101,   104,   105,   108,   109,   112,   128,   146,
     154,   162,   170,   178,   186,   194,   205,   213,   224,   232,
     240,   248,   256,   264,   272,   277,   282,   290,   298,   306,
     314,   322,   330,   338,   346,   354,   365,   373,   381,   397,
     433,   464,   469,   476,   477,   480,   481,   482,   483,   484,
     488,   487,   495,   494,   502,   501,   509,   508,   516,   515,
     524,   523,   528,   531,   532,   535,   536,   539,   543,   549,
     612,   664,   663,   669,   673,   672,   677,   681,   680,   685,
     689,   688,   694,   698,   697,   707,   710,   713,   718,   722,
     726,   736,   735,   743,   747,   746,   763,   762,   772,   771,
     778,   781,   782,   785,   786,   792,   793,   796,   803,   810,
     836,   862,   888,   914,   947,   951,   992,  1028,  1033,  1038,
    1042,  1046,  1053,  1052,  1063,  1067,  1066,  1076,  1079,  1085,
    1095,  1098,  1117,  1123,  1124,  1127,  1158,  1207,  1249,  1275,
    1280,  1285,  1289,  1293,  1297,  1301,  1305,  1309,  1313,  1317,
    1321,  1325,  1329,  1335,  1339,  1343,  1347,  1351,  1355,  1361
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_CONSTANTS", "_SYSTEM_VARS",
  "_SECONDARY_VARS", "_DUMMY_VARS", "_CARTESIAN_VARS", "_VELOCITY_VARS",
  "_NON_DYNAMIC_VARS", "_SYSTEM_EQS", "_COORD_EQS", "_DUMMY_EQS",
  "_VELOCITY_EQS", "_NON_DYNAMIC_EQS", "_SEARCH", "_DEPTH", "_BREADTH",
  "_FIRST", "_MIN", "_EQU", "_LEQ", "_GEQ", "_ASSIGN", "_INF", "_PI",
  "_SIN", "_COS", "_TAN", "_COT", "_ACOS", "_ASIN", "_ATAN", "_ATAN2",
  "_EXP", "_PWP", "_SQRT", "_ABS", "_DIFF", "_PARAMETER", "_PRINT", "_TR",
  "_TX", "_TY", "_TZ", "_TV", "_PA", "_RX", "_RY", "_RZ", "_ID", "_Z",
  "_DRX", "_DRY", "_DRZ", "_DPA_U", "_DPA_V", "_DDRX", "_DDRY", "_DDRZ",
  "_DDPA_UU", "_DDPA_UV", "_DDPA_VV", "_INV", "_EQUAL", "_LESS",
  "_GREATER", "_IDENTIFIER", "_INTEGER", "_REAL", "_MIN_PRECEDENCE",
  "_NOT_EQUAL", "'+'", "'-'", "'*'", "'/'", "'^'", "'\\''",
  "_MAX_PRECEDENCE", "'('", "')'", "'?'", "':'", "','", "'~'", "'['",
  "']'", "';'", "$accept", "problem", "ct_defs", "ct_list",
  "ct_definition", "expr", "var_defs", "var_block", "system_vars", "$@1",
  "secondary_vars", "$@2", "dummy_vars", "$@3", "cartesian_vars", "$@4",
  "velocity_vars", "$@5", "non_dynamic_vars", "$@6", "range_list",
  "vrange_list", "topology", "range_definition", "vrange_definition",
  "system_eqs", "$@7", "coord_eqs", "$@8", "dummy_eqs", "$@9",
  "non_dynamic_eqs", "$@10", "velocity_eqs", "$@11", "search",
  "search_type", "eq_list", "$@12", "equation", "$@13", "monomials",
  "$@14", "more_monomials", "$@15", "opt_sign", "sign", "monomial", "item",
  "power", "cmp", "meq_list", "$@16", "vmeq_list", "$@17",
  "mequation_list", "scaled_mequation", "scale_mequation", "mequation",
  "mitem", "opt_invert", "trans_type", "patch_type", "four_points", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,    43,    45,    42,    47,    94,    39,   327,    40,
      41,    63,    58,    44,   126,    91,    93,    59
};
# endif

#define YYPACT_NINF (-278)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-103)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      28,   -12,    68,    84,     5,    56,  -278,   -12,  -278,  -278,
    -278,  -278,  -278,  -278,    64,    84,  -278,  -278,  -278,  -278,
    -278,  -278,   970,  -278,    29,    29,    29,    29,    60,  -278,
      89,  -278,  -278,  -278,    38,    52,    55,    63,    70,    83,
      87,   101,   102,   110,   112,   113,   128,   130,  -278,  -278,
    -278,   970,   970,   970,   946,   -31,  -278,    29,  -278,  -278,
    -278,   131,  -278,    60,    29,  -278,    96,   970,   970,   970,
     970,   970,   970,   970,   970,   970,   970,   970,   970,    73,
     123,  -278,  -278,   599,   970,   970,   970,   970,   970,   970,
     970,   970,   970,   970,   970,  -278,  -278,    78,  -278,   141,
    -278,  -278,   998,  -278,   127,   612,   625,   638,   660,   673,
     686,   699,   198,   720,   733,   746,   759,   132,   133,  -278,
     970,    80,    80,    80,    80,    80,    80,   -63,   -63,    59,
      59,  -278,   970,   137,  -278,  -278,  1073,  -278,    94,  1019,
    -278,    32,  -278,   197,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,   970,  -278,  -278,  -278,  -278,  -278,  -278,   579,   257,
     143,   145,  -278,  -278,  -278,   147,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,   -13,  -278,   148,   156,   998,  -278,  -278,  -278,
    -278,   160,   158,   159,   163,   165,   166,   173,   160,   160,
     160,  -278,   179,  -278,    50,  -278,   241,   780,   970,   970,
     170,   970,   970,   206,  1073,   970,   970,  -278,   -16,   191,
    -278,   970,   970,   970,   970,   970,   199,  -278,  -278,  -278,
     -16,  1019,  -278,   998,  -278,   250,  -278,   793,   157,   970,
     270,   284,   180,  -278,   806,   304,   181,   193,  -278,   819,
     840,   853,   866,   879,   202,  -278,  1019,  -278,  1073,   998,
      61,  -278,  -278,  -278,   317,   970,   970,  -278,   220,   970,
     217,  -278,   160,   160,   160,   160,   160,   160,  -278,  -278,
    1073,   267,   268,   -16,  -278,   970,   330,   343,  1073,  -278,
    -278,   363,   205,  -278,  -278,  -278,  -278,  -278,  -278,   -16,
    -278,    -5,  -278,   216,  -278,  -278,  -278,   175,   970,   970,
    -278,   970,   226,  -278,   243,  1073,  1051,  -278,  -278,   376,
     389,    37,   218,   210,  -278,   222,   970,   970,   970,   220,
    -278,   235,    54,   900,   402,  -278,  1073,   229,   970,   220,
     970,  -278,  -278,   422,  -278,   435,   970,   970,   448,    72,
     970,   970,   461,   481,   970,   970,   111,   494,   970,   970,
     507,   129,   970,   970,   520,   540,   970,   970,   553,   566,
     970,   970,   913,   946,   220,  -278
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     6,     0,    44,     0,     0,     3,     6,     1,    50,
      52,    54,    56,    58,    62,    44,    45,    46,    47,    48,
      49,     8,     0,     5,    64,    64,    64,    64,    66,    60,
      73,    43,    25,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    41,
      42,     0,     0,     0,     7,     0,    51,    64,    53,    55,
      57,     0,    59,    66,    64,    71,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,    68,     0,    63,     0,
      65,    61,    93,    74,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
       0,    20,    21,    18,    22,    23,    19,    11,    12,    13,
      15,    14,     0,     0,   103,   104,   124,    91,     0,     0,
     101,   102,    77,    82,    26,    27,    28,    29,    31,    30,
      32,     0,    34,    35,    36,    37,    39,    38,     0,     0,
       0,     0,   141,   142,   143,     0,   153,   144,   145,   146,
     147,   148,   149,   154,   155,   150,   151,   152,   156,   157,
     158,    72,     0,   134,     0,     0,    93,   119,   120,   121,
      94,   118,     0,     0,     0,     0,     0,     0,   118,   118,
     118,    96,   106,    75,   102,    80,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,   102,     0,
     114,     0,     0,     0,     0,     0,     0,   116,   108,   107,
     100,     0,    78,    93,    83,    87,    33,     0,     0,     0,
       0,     0,     0,   133,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,    97,     0,   105,   124,    93,
       0,     2,    17,    69,     0,     0,     0,   122,   140,     0,
       0,    95,   118,   118,   118,   118,   118,   118,    98,    81,
     127,     0,     0,   102,    86,     0,     0,     0,   124,   139,
     137,     0,     0,   109,   110,   111,   112,   113,   115,   100,
      84,     0,   129,   132,    88,    89,    90,     0,     0,     0,
     123,     0,     0,    99,     0,     0,     0,   130,    70,     0,
       0,     0,     0,     0,   128,     0,     0,     0,     0,   140,
     125,     0,     0,     0,     0,   138,   127,     0,     0,   140,
       0,   126,   131,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   140,   135
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -278,  -278,  -278,   303,  -278,   -51,   298,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
     142,   251,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -138,  -278,  -278,
    -278,  -212,  -278,    18,  -278,  -278,  -225,  -202,  -278,  -190,
    -278,  -228,  -278,   -18,  -278,  -278,     9,  -278,  -266,  -210,
    -277,  -278,  -278,  -278
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     7,    54,    14,    15,    16,    24,
      17,    25,    18,    26,    19,    27,    20,    28,    30,    64,
      56,    62,    97,    57,    63,    66,   102,   104,   141,   143,
     204,   206,   233,   235,   259,   261,   284,   136,   186,   137,
     218,   138,   230,   255,   299,   139,   140,   201,   202,   220,
     190,   181,   288,   300,   336,   301,   302,   317,   182,   183,
     290,   184,   185,   246
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    82,    83,   203,   243,   256,   247,   213,   227,   228,
     229,    92,    93,    94,   303,   314,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,     4,   257,
     279,     1,   -93,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   -93,   -93,   -93,   -93,   217,   303,
     -93,    95,   335,    96,   278,     5,   134,   135,    84,    85,
     310,   214,   344,   -93,   -93,   -93,   232,   315,     8,   158,
     303,   306,    21,    29,   256,    84,    85,   281,   282,    22,
     283,   159,   293,   294,   295,   296,   297,   298,     9,    10,
      11,    12,    13,    84,    85,   258,    55,   375,    61,    65,
     207,    86,    87,    88,   134,   135,   243,   103,    89,    90,
      91,    92,    93,    94,   187,   188,   189,    67,    86,    87,
      88,   280,   134,   135,   328,    89,    90,    91,    92,    93,
      94,    68,    84,    85,    69,    94,    86,    87,    88,   142,
     117,   338,    70,    89,    90,    91,    92,    93,    94,    71,
      84,    85,    90,    91,    92,    93,    94,   237,   238,   351,
     240,   241,    72,   132,   244,   245,    73,    58,    59,    60,
     249,   250,   251,   252,   253,    86,    87,    88,    84,    85,
      74,    75,    89,    90,    91,    92,    93,    94,   264,    76,
     118,    77,    78,    86,    87,    88,    84,    85,   358,    98,
      89,    90,    91,    92,    93,    94,   101,    79,   133,    80,
      99,   205,   156,   157,   286,   287,   363,   160,   291,    84,
      85,    86,    87,    88,   211,   210,   212,   215,    89,    90,
      91,    92,    93,    94,   307,   216,   219,   221,   222,    86,
      87,    88,   223,   263,   224,   225,    89,    90,    91,    92,
      93,    94,   226,   231,   234,   239,   242,   319,   320,   248,
     321,   318,    86,    87,    88,   260,   254,   267,   270,    89,
      90,    91,    92,    93,    94,   332,   333,   334,    84,    85,
     271,   151,   277,   289,   292,   304,   305,   343,   312,   345,
     316,    84,    85,   322,   323,   348,   349,   330,   329,   352,
     353,   331,   337,   356,   357,    84,    85,   360,   361,   342,
      23,   364,   365,    31,   100,   368,   369,   313,   341,   372,
     373,    86,    87,    88,   324,    84,    85,     0,    89,    90,
      91,    92,    93,    94,    86,    87,    88,     0,    84,    85,
     209,    89,    90,    91,    92,    93,    94,     0,    86,    87,
      88,    84,    85,   265,     0,    89,    90,    91,    92,    93,
      94,     0,     0,     0,    84,    85,     0,   266,    86,    87,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
      94,    86,    87,    88,    84,    85,     0,   269,    89,    90,
      91,    92,    93,    94,    86,    87,    88,    84,    85,     0,
     285,    89,    90,    91,    92,    93,    94,    86,    87,    88,
      84,    85,     0,   308,    89,    90,    91,    92,    93,    94,
       0,     0,     0,    84,    85,     0,   309,    86,    87,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,    94,
      86,    87,    88,    84,    85,     0,   311,    89,    90,    91,
      92,    93,    94,    86,    87,    88,    84,    85,     0,   326,
      89,    90,    91,    92,    93,    94,    86,    87,    88,    84,
      85,     0,   327,    89,    90,    91,    92,    93,    94,     0,
       0,     0,    84,    85,     0,   340,    86,    87,    88,     0,
       0,     0,     0,    89,    90,    91,    92,    93,    94,    86,
      87,    88,    84,    85,     0,   346,    89,    90,    91,    92,
      93,    94,    86,    87,    88,    84,    85,     0,   347,    89,
      90,    91,    92,    93,    94,    86,    87,    88,    84,    85,
       0,   350,    89,    90,    91,    92,    93,    94,     0,     0,
       0,    84,    85,     0,   354,    86,    87,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,    86,    87,
      88,    84,    85,     0,   355,    89,    90,    91,    92,    93,
      94,    86,    87,    88,    84,    85,     0,   359,    89,    90,
      91,    92,    93,    94,    86,    87,    88,    84,    85,     0,
     362,    89,    90,    91,    92,    93,    94,     0,     0,     0,
      84,    85,     0,   366,    86,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    86,    87,    88,
      84,    85,     0,   367,    89,    90,    91,    92,    93,    94,
      86,    87,    88,    84,    85,     0,   370,    89,    90,    91,
      92,    93,    94,    86,    87,    88,    84,    85,     0,   371,
      89,    90,    91,    92,    93,    94,     0,     0,     0,    84,
      85,   208,     0,    86,    87,    88,     0,     0,     0,     0,
      89,    90,    91,    92,    93,    94,    86,    87,    88,   119,
     120,    84,    85,    89,    90,    91,    92,    93,    94,    86,
      87,    88,   144,     0,    84,    85,    89,    90,    91,    92,
      93,    94,    86,    87,    88,   145,     0,    84,    85,    89,
      90,    91,    92,    93,    94,     0,     0,     0,   146,     0,
      84,    85,     0,     0,    86,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    86,    87,    88,
     147,    84,    85,     0,    89,    90,    91,    92,    93,    94,
      86,    87,    88,   148,    84,    85,     0,    89,    90,    91,
      92,    93,    94,    86,    87,    88,   149,    84,    85,     0,
      89,    90,    91,    92,    93,    94,     0,     0,     0,   150,
      84,    85,     0,     0,    86,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    86,    87,    88,
     152,    84,    85,     0,    89,    90,    91,    92,    93,    94,
      86,    87,    88,   153,    84,    85,     0,    89,    90,    91,
      92,    93,    94,    86,    87,    88,   154,    84,    85,     0,
      89,    90,    91,    92,    93,    94,     0,     0,     0,   155,
      84,    85,     0,     0,    86,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    86,    87,    88,
     236,    84,    85,     0,    89,    90,    91,    92,    93,    94,
      86,    87,    88,   262,    84,    85,     0,    89,    90,    91,
      92,    93,    94,    86,    87,    88,   268,    84,    85,     0,
      89,    90,    91,    92,    93,    94,     0,     0,     0,   272,
      84,    85,     0,     0,    86,    87,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    86,    87,    88,
     273,    84,    85,     0,    89,    90,    91,    92,    93,    94,
      86,    87,    88,   274,    84,    85,     0,    89,    90,    91,
      92,    93,    94,    86,    87,    88,   275,     0,     0,     0,
      89,    90,    91,    92,    93,    94,     0,     0,     0,   276,
       0,     0,     0,     0,    86,    87,    88,    84,    85,     0,
       0,    89,    90,    91,    92,    93,    94,    86,    87,    88,
     339,     0,     0,     0,    89,    90,    91,    92,    93,    94,
       0,     0,     0,   374,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      86,    87,    88,     0,     0,     0,     0,    89,    90,    91,
      92,    93,    94,  -102,  -102,  -102,  -102,     0,     0,     0,
       0,     0,  -102,  -102,     0,     0,  -102,    48,    49,    50,
       0,     0,    51,    52,   191,   192,   193,   194,     0,    53,
       0,     0,     0,   195,   196,     0,     0,   197,     0,     0,
       0,     0,     0,     0,     0,  -102,  -102,  -102,     0,     0,
     134,   135,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   198,   199,   200,   325,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,     0,     0,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   161,   162,   163,   164,   165,   166,
     167,   168,   169,     0,     0,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180
};

static const yytype_int16 yycheck[] =
{
      51,    52,    53,   141,   214,   230,   218,    20,   198,   199,
     200,    74,    75,    76,   280,    20,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    40,   231,
     258,     3,     0,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    12,    13,    14,    15,   186,   315,
       0,    82,   329,    84,   256,    67,    72,    73,    21,    22,
     288,    74,   339,    13,    14,    15,   204,    72,     0,   120,
     336,   283,    67,     9,   299,    21,    22,    16,    17,    23,
      19,   132,   272,   273,   274,   275,   276,   277,     4,     5,
       6,     7,     8,    21,    22,   233,    67,   374,    38,    10,
     151,    64,    65,    66,    72,    73,   316,    11,    71,    72,
      73,    74,    75,    76,    20,    21,    22,    79,    64,    65,
      66,   259,    72,    73,    87,    71,    72,    73,    74,    75,
      76,    79,    21,    22,    79,    76,    64,    65,    66,    12,
      67,    87,    79,    71,    72,    73,    74,    75,    76,    79,
      21,    22,    72,    73,    74,    75,    76,   208,   209,    87,
     211,   212,    79,    85,   215,   216,    79,    25,    26,    27,
     221,   222,   223,   224,   225,    64,    65,    66,    21,    22,
      79,    79,    71,    72,    73,    74,    75,    76,   239,    79,
      67,    79,    79,    64,    65,    66,    21,    22,    87,    57,
      71,    72,    73,    74,    75,    76,    64,    79,    67,    79,
      79,    14,    80,    80,   265,   266,    87,    80,   269,    21,
      22,    64,    65,    66,    79,    82,    79,    79,    71,    72,
      73,    74,    75,    76,   285,    79,    76,    79,    79,    64,
      65,    66,    79,    86,    79,    79,    71,    72,    73,    74,
      75,    76,    79,    74,    13,    85,    50,   308,   309,    68,
     311,    86,    64,    65,    66,    15,    67,    87,    87,    71,
      72,    73,    74,    75,    76,   326,   327,   328,    21,    22,
      87,    83,    80,    63,    67,    18,    18,   338,    83,   340,
      74,    21,    22,    67,    51,   346,   347,    87,    80,   350,
     351,    79,    67,   354,   355,    21,    22,   358,   359,    80,
       7,   362,   363,    15,    63,   366,   367,   299,   336,   370,
     371,    64,    65,    66,   315,    21,    22,    -1,    71,    72,
      73,    74,    75,    76,    64,    65,    66,    -1,    21,    22,
      83,    71,    72,    73,    74,    75,    76,    -1,    64,    65,
      66,    21,    22,    83,    -1,    71,    72,    73,    74,    75,
      76,    -1,    -1,    -1,    21,    22,    -1,    83,    64,    65,
      66,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    64,    65,    66,    21,    22,    -1,    83,    71,    72,
      73,    74,    75,    76,    64,    65,    66,    21,    22,    -1,
      83,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      21,    22,    -1,    83,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    21,    22,    -1,    83,    64,    65,    66,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      64,    65,    66,    21,    22,    -1,    83,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    21,    22,    -1,    83,
      71,    72,    73,    74,    75,    76,    64,    65,    66,    21,
      22,    -1,    83,    71,    72,    73,    74,    75,    76,    -1,
      -1,    -1,    21,    22,    -1,    83,    64,    65,    66,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    64,
      65,    66,    21,    22,    -1,    83,    71,    72,    73,    74,
      75,    76,    64,    65,    66,    21,    22,    -1,    83,    71,
      72,    73,    74,    75,    76,    64,    65,    66,    21,    22,
      -1,    83,    71,    72,    73,    74,    75,    76,    -1,    -1,
      -1,    21,    22,    -1,    83,    64,    65,    66,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    64,    65,
      66,    21,    22,    -1,    83,    71,    72,    73,    74,    75,
      76,    64,    65,    66,    21,    22,    -1,    83,    71,    72,
      73,    74,    75,    76,    64,    65,    66,    21,    22,    -1,
      83,    71,    72,    73,    74,    75,    76,    -1,    -1,    -1,
      21,    22,    -1,    83,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      21,    22,    -1,    83,    71,    72,    73,    74,    75,    76,
      64,    65,    66,    21,    22,    -1,    83,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    21,    22,    -1,    83,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    21,
      22,    82,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    64,    65,    66,    80,
      81,    21,    22,    71,    72,    73,    74,    75,    76,    64,
      65,    66,    80,    -1,    21,    22,    71,    72,    73,    74,
      75,    76,    64,    65,    66,    80,    -1,    21,    22,    71,
      72,    73,    74,    75,    76,    -1,    -1,    -1,    80,    -1,
      21,    22,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      80,    21,    22,    -1,    71,    72,    73,    74,    75,    76,
      64,    65,    66,    80,    21,    22,    -1,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    80,    21,    22,    -1,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    80,
      21,    22,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      80,    21,    22,    -1,    71,    72,    73,    74,    75,    76,
      64,    65,    66,    80,    21,    22,    -1,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    80,    21,    22,    -1,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    80,
      21,    22,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      80,    21,    22,    -1,    71,    72,    73,    74,    75,    76,
      64,    65,    66,    80,    21,    22,    -1,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    80,    21,    22,    -1,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    80,
      21,    22,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      80,    21,    22,    -1,    71,    72,    73,    74,    75,    76,
      64,    65,    66,    80,    21,    22,    -1,    71,    72,    73,
      74,    75,    76,    64,    65,    66,    80,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    64,    65,    66,    21,    22,    -1,
      -1,    71,    72,    73,    74,    75,    76,    64,    65,    66,
      80,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    80,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      64,    65,    66,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    25,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    34,    35,    -1,    -1,    38,    67,    68,    69,
      -1,    -1,    72,    73,    25,    26,    27,    28,    -1,    79,
      -1,    -1,    -1,    34,    35,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    -1,    -1,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    38,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    89,    90,    40,    67,    91,    92,     0,     4,
       5,     6,     7,     8,    94,    95,    96,    98,   100,   102,
     104,    67,    23,    91,    97,    99,   101,   103,   105,     9,
     106,    94,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    67,    68,
      69,    72,    73,    79,    93,    67,   108,   111,   108,   108,
     108,    38,   109,   112,   107,    10,   113,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    93,    93,    93,    21,    22,    64,    65,    66,    71,
      72,    73,    74,    75,    76,    82,    84,   110,   108,    79,
     109,   108,   114,    11,   115,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    67,    67,    80,
      81,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    85,    67,    72,    73,   125,   127,   129,   133,
     134,   116,    12,   117,    80,    80,    80,    80,    80,    80,
      80,    83,    80,    80,    80,    80,    80,    80,    93,    93,
      80,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   139,   146,   147,   149,   150,   126,    20,    21,    22,
     138,    25,    26,    27,    28,    34,    35,    38,    67,    68,
      69,   135,   136,   125,   118,    14,   119,    93,    82,    83,
      82,    79,    79,    20,    74,    79,    79,   125,   128,    76,
     137,    79,    79,    79,    79,    79,    79,   137,   137,   137,
     130,    74,   125,   120,    13,   121,    80,    93,    93,    85,
      93,    93,    50,   147,    93,    93,   151,   129,    68,    93,
      93,    93,    93,    93,    67,   131,   134,   135,   125,   122,
      15,   123,    80,    86,    93,    83,    83,    87,    80,    83,
      87,    87,    80,    80,    80,    80,    80,    80,   135,   139,
     125,    16,    17,    19,   124,    83,    93,    93,   140,    63,
     148,    93,    67,   137,   137,   137,   137,   137,   137,   132,
     141,   143,   144,   146,    18,    18,   129,    93,    83,    83,
     139,    83,    83,   131,    20,    72,    74,   145,    86,    93,
      93,    93,    67,    51,   144,    38,    83,    83,    87,    80,
      87,    79,    93,    93,    93,   148,   142,    67,    87,    80,
      83,   141,    80,    93,   148,    93,    83,    83,    93,    93,
      83,    87,    93,    93,    83,    83,    93,    93,    87,    83,
      93,    93,    83,    87,    93,    93,    83,    83,    93,    93,
      83,    83,    93,    93,    80,   148
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      97,    96,    99,    98,   101,   100,   103,   102,   105,   104,
     107,   106,   106,   108,   108,   109,   109,   110,   110,   111,
     112,   114,   113,   113,   116,   115,   115,   118,   117,   117,
     120,   119,   119,   122,   121,   121,   123,   123,   124,   124,
     124,   126,   125,   125,   128,   127,   130,   129,   132,   131,
     131,   133,   133,   134,   134,   135,   135,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   137,   137,   138,
     138,   138,   140,   139,   139,   142,   141,   141,   143,   143,
     144,   145,   145,   146,   146,   147,   147,   147,   147,   148,
     148,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   150,   151
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     9,     2,     0,     2,     0,     3,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     7,     3,     3,
       3,     3,     3,     3,     1,     1,     4,     4,     4,     4,
       4,     4,     4,     6,     4,     4,     4,     4,     4,     4,
       1,     1,     1,     2,     0,     1,     1,     1,     1,     1,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     2,     0,     2,     0,     1,     1,     7,
      10,     0,     4,     0,     0,     3,     0,     0,     3,     0,
       0,     4,     0,     0,     4,     0,     2,     0,     2,     2,
       2,     0,     3,     0,     0,     5,     0,     4,     0,     4,
       0,     1,     0,     1,     1,     3,     1,     2,     2,     5,
       5,     5,     5,     5,     2,     5,     2,     2,     0,     1,
       1,     1,     0,     6,     0,     0,     6,     0,     3,     1,
       2,     5,     0,     3,     1,    27,    11,     5,     9,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,    23
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 7:
#line 113 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
               {
		 if (GetConstantWithName((yyvsp[-2].id),rcs_constants)!=NO_UINT)
		   {
		     char s[250];
		     
		     sprintf(s,"Duplicated constant %.150s",(yyvsp[-2].id));
		     ReadcuiksystemSemanticError(s);
		   }

		 if ((yyvsp[0].expr).id!=NULL)
		   ReadcuiksystemSemanticError("Constant assigned to a variable");

	         AddConstant((yyvsp[-2].id),(yyvsp[0].expr).value,rcs_constants);
		 free((yyvsp[-2].id));
               }
#line 1884 "readcuiksystem.tab.c"
    break;

  case 8:
#line 129 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
               {
		 unsigned int nc;
		 
		 nc=GetConstantWithName((yyvsp[0].id),rcs_constants);
		 if (nc==NO_UINT)
		   {
		     char ms[250];
		     
		     sprintf(ms,"Undefined constant: %.150s",(yyvsp[0].id));
		     ReadcuiksystemSemanticError(ms);
		   }
		 fprintf(stderr,"  %s = %.12f\n",(yyvsp[0].id),GetConstantValue(nc,rcs_constants));
		 free((yyvsp[0].id));
	       }
#line 1903 "readcuiksystem.tab.c"
    break;

  case 9:
#line 147 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[0].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[0].expr).value;
         }
#line 1915 "readcuiksystem.tab.c"
    break;

  case 10:
#line 155 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[0].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=-(yyvsp[0].expr).value;
         }
#line 1927 "readcuiksystem.tab.c"
    break;

  case 11:
#line 163 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[-2].expr).value+(yyvsp[0].expr).value;
         }
#line 1939 "readcuiksystem.tab.c"
    break;

  case 12:
#line 171 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[-2].expr).value-(yyvsp[0].expr).value;
         }
#line 1951 "readcuiksystem.tab.c"
    break;

  case 13:
#line 179 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[-2].expr).value*(yyvsp[0].expr).value;
         }
#line 1963 "readcuiksystem.tab.c"
    break;

  case 14:
#line 187 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=pow((yyvsp[-2].expr).value,(yyvsp[0].expr).value);
         }
#line 1975 "readcuiksystem.tab.c"
    break;

  case 15:
#line 195 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   if ((yyvsp[0].expr).value==0.0)
	     ReadcuiksystemSemanticError("Division by zero");
	   
	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[-2].expr).value/(yyvsp[0].expr).value;
         }
#line 1990 "readcuiksystem.tab.c"
    break;

  case 16:
#line 206 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[-1].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[-1].expr).value;
         }
#line 2002 "readcuiksystem.tab.c"
    break;

  case 17:
#line 214 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-5].expr).id!=NULL)||((yyvsp[-3].expr).id!=NULL)||((yyvsp[-1].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    if ((yyvsp[-5].expr).value)
	      (yyval.expr).value=(yyvsp[-3].expr).value;
	    else
	      (yyval.expr).value=(yyvsp[-1].expr).value;
	  }
#line 2017 "readcuiksystem.tab.c"
    break;

  case 18:
#line 225 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	     ReadcuiksystemSemanticError("No operation is allowed with variables");

	    (yyval.expr).id=NULL;
	    (yyval.expr).value=((yyvsp[-2].expr).value==(yyvsp[0].expr).value);
	  }
#line 2029 "readcuiksystem.tab.c"
    break;

  case 19:
#line 233 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=((yyvsp[-2].expr).value!=(yyvsp[0].expr).value);
	  }
#line 2041 "readcuiksystem.tab.c"
    break;

  case 20:
#line 241 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=((yyvsp[-2].expr).value<=(yyvsp[0].expr).value);
	  }
#line 2053 "readcuiksystem.tab.c"
    break;

  case 21:
#line 249 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=((yyvsp[-2].expr).value>=(yyvsp[0].expr).value);
	  }
#line 2065 "readcuiksystem.tab.c"
    break;

  case 22:
#line 257 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=((yyvsp[-2].expr).value<(yyvsp[0].expr).value);
	  }
#line 2077 "readcuiksystem.tab.c"
    break;

  case 23:
#line 265 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=((yyvsp[-2].expr).value>(yyvsp[0].expr).value);
	  }
#line 2089 "readcuiksystem.tab.c"
    break;

  case 24:
#line 273 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=M_PI;
	  }
#line 2098 "readcuiksystem.tab.c"
    break;

  case 25:
#line 278 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=INF;
	  }
#line 2107 "readcuiksystem.tab.c"
    break;

  case 26:
#line 283 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=sin((yyvsp[-1].expr).value);
	  }
#line 2119 "readcuiksystem.tab.c"
    break;

  case 27:
#line 291 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=cos((yyvsp[-1].expr).value);
	  }
#line 2131 "readcuiksystem.tab.c"
    break;

  case 28:
#line 299 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=tan((yyvsp[-1].expr).value);
	  }
#line 2143 "readcuiksystem.tab.c"
    break;

  case 29:
#line 307 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=tan(M_PI_2-(yyvsp[-1].expr).value);
	  }
#line 2155 "readcuiksystem.tab.c"
    break;

  case 30:
#line 315 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=asin((yyvsp[-1].expr).value);
	  }
#line 2167 "readcuiksystem.tab.c"
    break;

  case 31:
#line 323 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=acos((yyvsp[-1].expr).value);
	  }
#line 2179 "readcuiksystem.tab.c"
    break;

  case 32:
#line 331 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((yyvsp[-1].expr).id!=NULL)
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=atan((yyvsp[-1].expr).value);
	  }
#line 2191 "readcuiksystem.tab.c"
    break;

  case 33:
#line 339 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if (((yyvsp[-3].expr).id!=NULL)||((yyvsp[-1].expr).id!=NULL))
	      ReadcuiksystemSemanticError("No operation is allowed with variables");
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=atan2((yyvsp[-3].expr).value,(yyvsp[-1].expr).value);
	  }
#line 2203 "readcuiksystem.tab.c"
    break;

  case 34:
#line 347 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[-1].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   (yyval.expr).id=NULL;
	   (yyval.expr).value=exp((yyvsp[-1].expr).value);
	 }
#line 2215 "readcuiksystem.tab.c"
    break;

  case 35:
#line 355 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[-1].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   (yyval.expr).id=NULL;
	   if ((yyvsp[-1].expr).value<0.0)
	     (yyval.expr).value=(yyvsp[-1].expr).value*(yyvsp[-1].expr).value;
	   else
	     (yyval.expr).value=0.0;
	 }
#line 2230 "readcuiksystem.tab.c"
    break;

  case 36:
#line 366 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[-1].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   (yyval.expr).id=NULL;
	   (yyval.expr).value=sqrt((yyvsp[-1].expr).value);
	 }
#line 2242 "readcuiksystem.tab.c"
    break;

  case 37:
#line 374 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   if ((yyvsp[-1].expr).id!=NULL)
	     ReadcuiksystemSemanticError("No operation is allowed with variables");
	   
	   (yyval.expr).id=NULL;
	   (yyval.expr).value=fabs((yyvsp[-1].expr).value);
	 }
#line 2254 "readcuiksystem.tab.c"
    break;

  case 38:
#line 382 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    unsigned int n;
	    
	    n=GetParameterID((yyvsp[-1].id),rcs_parameters);
	    if (n==NO_UINT)
	      {
		char ms[250];
		
		sprintf(ms,"Undefined parameter: %.150s",(yyvsp[-1].id));
		ReadcuiksystemSemanticError(ms);
	      }
	    
	    (yyval.expr).id=NULL;
	    (yyval.expr).value=GetParameter(n,rcs_parameters);
	  }
#line 2274 "readcuiksystem.tab.c"
    break;

  case 39:
#line 398 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   unsigned int nc;
	   
	   if (rcs_prefixID)
	     ReadcuiksystemSemanticError("Can not use velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
 
	   nc=GetConstantWithName((yyvsp[-1].id),rcs_constants);

	   if (nc!=NO_UINT)
	     {
	       char s[250];
	       
	       sprintf(s,"Constants (%.150s) can not be differentiated",(yyvsp[-1].id));
	       ReadcuiksystemSemanticError(s);
	     }
	   else
	     {
	       NEW(rcs_ID,strlen((yyvsp[-1].id))+20,char);
	       if (rcs_prefixID)
		 sprintf(rcs_ID,"_diff(%s)",(yyvsp[-1].id));
	       else
		 sprintf(rcs_ID,"diff(%s)",(yyvsp[-1].id));
	       
	       if (GetCSVariableID(rcs_ID,rcs_cuiksystem)==NO_UINT) 
		 {
		   char s[250];
		   
		   sprintf(s,"Undefined variable diff(%.150s)",(yyvsp[-1].id));
		   ReadcuiksystemSemanticError(s);
		 }
	       else
		 (yyval.expr).id=rcs_ID;
	     }
	   free((yyvsp[-1].id));
	 }
#line 2314 "readcuiksystem.tab.c"
    break;

  case 40:
#line 434 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   unsigned int nc;

	   nc=GetConstantWithName((yyvsp[0].id),rcs_constants);

	   if (nc!=NO_UINT)
	     {
	       (yyval.expr).id=NULL;
	       (yyval.expr).value=GetConstantValue(nc,rcs_constants);
	     }
	   else
	     {
	       NEW(rcs_ID,strlen((yyvsp[0].id))+2,char);
	       if (rcs_prefixID)
		 sprintf(rcs_ID,"_%s",(yyvsp[0].id));
	       else
		 strcpy(rcs_ID,(yyvsp[0].id));
	       
	       if (GetCSVariableID(rcs_ID,rcs_cuiksystem)==NO_UINT) 
		 {
		   char s[250];
		   
		   sprintf(s,"Undefined variable %.150s",(yyvsp[0].id));
		   ReadcuiksystemSemanticError(s);
		 }
	       else
		 (yyval.expr).id=rcs_ID;
	     }
	   free((yyvsp[0].id));
	 }
#line 2349 "readcuiksystem.tab.c"
    break;

  case 41:
#line 465 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(double)(yyvsp[0].int_number);
         }
#line 2358 "readcuiksystem.tab.c"
    break;

  case 42:
#line 470 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   (yyval.expr).id=NULL;
	   (yyval.expr).value=(yyvsp[0].real_number);
         }
#line 2367 "readcuiksystem.tab.c"
    break;

  case 50:
#line 488 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       rcs_var_type=SYSTEM_VAR;
	     }
#line 2375 "readcuiksystem.tab.c"
    break;

  case 52:
#line 495 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                { 
		  rcs_var_type=SECONDARY_VAR;
	        }
#line 2383 "readcuiksystem.tab.c"
    break;

  case 54:
#line 502 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
            { 
	      rcs_var_type=DUMMY_VAR;
	    }
#line 2391 "readcuiksystem.tab.c"
    break;

  case 56:
#line 509 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                {
		  rcs_var_type=CARTESIAN_VAR;	
	        }
#line 2399 "readcuiksystem.tab.c"
    break;

  case 58:
#line 516 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
               {
		 Warning("Velocity variables should be defined automatically and not given in a cuik file. This may lead to an inconsisten system");
		 rcs_var_type=VELOCITY_VAR;
	       }
#line 2408 "readcuiksystem.tab.c"
    break;

  case 60:
#line 524 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                  {
		    rcs_var_type=NON_DYNAMIC_VAR;
		  }
#line 2416 "readcuiksystem.tab.c"
    break;

  case 67:
#line 540 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    rcs_topology=TOPOLOGY_R;
	  }
#line 2424 "readcuiksystem.tab.c"
    break;

  case 68:
#line 544 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    rcs_topology=TOPOLOGY_S;
	  }
#line 2432 "readcuiksystem.tab.c"
    break;

  case 69:
#line 550 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                  {
		    Tinterval i_user; 
		    Tvariable v;

		    if (((yyvsp[-3].expr).id!=NULL)||((yyvsp[-1].expr).id!=NULL))
		      ReadcuiksystemSemanticError("Can not define a range with variables");

		    if (GetConstantWithName((yyvsp[-6].id),rcs_constants)!=NO_UINT)  
		      {
			char s[250];
			
			sprintf(s,"Constant %.150s redefined as a variable",(yyvsp[-6].id));
			ReadcuiksystemSemanticError(s);
		      }
		    
		    NEW(rcs_ID,strlen((yyvsp[-6].id))+2,char);
		    if (rcs_prefixID)
		      sprintf(rcs_ID,"_%s",(yyvsp[-6].id));
		    else
		      strcpy(rcs_ID,(yyvsp[-6].id));
		    
		    if (GetCSVariableID(rcs_ID,rcs_cuiksystem)!=NO_UINT) 
		      {
			char s[250];
			
			sprintf(s,"Repeated range declaration for variable %s",(yyvsp[-6].id));
			ReadcuiksystemSemanticError(s);
		      }
		    
		    if (rcs_topology==TOPOLOGY_S)
		      {
			if ((fabs((yyvsp[-3].expr).value+M_PI)>ZERO)||(fabs((yyvsp[-1].expr).value-M_PI)>ZERO))
			  {
			    char s[250];
			    
			    sprintf(s,"Circular variable %.150s must have range [-pi,pi]",(yyvsp[-6].id));
			    ReadcuiksystemSemanticError(s);
			  }
			NewInterval(-M_PI,+M_PI,&i_user);
		      }
		    else
		      NewInterval((yyvsp[-3].expr).value,(yyvsp[-1].expr).value,&i_user);
		    
		    if (EmptyInterval(&i_user))
		      ReadcuiksystemSemanticError("Empty Interval");

		    if ((rcs_prefixID)&&(rcs_var_type==VELOCITY_VAR))
			  ReadcuiksystemSemanticError("Can not define velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
		
		    NewVariable(rcs_var_type,rcs_ID,&v);
		    SetVariableInterval(&i_user,&v);
		    if (rcs_topology==TOPOLOGY_S)
		      SetVariableTopology(TOPOLOGY_S,&v);

		    AddVariable2CS(&v,rcs_cuiksystem);

		    DeleteVariable(&v);
		    free(rcs_ID);
		    free((yyvsp[-6].id));
		  }
#line 2497 "readcuiksystem.tab.c"
    break;

  case 70:
#line 613 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                   {
		     Tinterval i_user,c; 
		     Tvariable v;

		     if (((yyvsp[-3].expr).id!=NULL)||((yyvsp[-1].expr).id!=NULL))
		       ReadcuiksystemSemanticError("Can not define a range with variables");
		     
		     if (rcs_prefixID)
		       ReadcuiksystemSemanticError("Can not define velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
 
		     if (GetConstantWithName((yyvsp[-7].id),rcs_constants)!=NO_UINT)  
		       {
			 char s[250];
			
			 sprintf(s,"Constant %.150s redefined as a velocity variable",(yyvsp[-7].id));
			 ReadcuiksystemSemanticError(s);
		       }
		    
		     NEW(rcs_ID,strlen((yyvsp[-7].id))+10,char);
		     if (rcs_prefixID)
		       sprintf(rcs_ID,"_diff(%s)",(yyvsp[-7].id));
		     else
		       sprintf(rcs_ID,"diff(%s)",(yyvsp[-7].id));
		    
		     if (GetCSVariableID(rcs_ID,rcs_cuiksystem)!=NO_UINT) 
		       {
			 char s[300];
			
			 sprintf(s,"Repeated range declaration for variable diff(%s)",(yyvsp[-7].id));
			 ReadcuiksystemSemanticError(s);
		       }

		     NewInterval(-M_C,M_C,&c);
		     NewInterval((yyvsp[-3].expr).value,(yyvsp[-1].expr).value,&i_user);
		     Intersection(&c,&i_user,&i_user);
		    
		     if (EmptyInterval(&i_user))
		       ReadcuiksystemSemanticError("Empty Interval");

		     NewVariable(VELOCITY_VAR,rcs_ID,&v);
		     SetVariableInterval(&i_user,&v);

		     AddVariable2CS(&v,rcs_cuiksystem);

		     DeleteVariable(&v);
		     free(rcs_ID);
		     free((yyvsp[-7].id));
		   }
#line 2550 "readcuiksystem.tab.c"
    break;

  case 71:
#line 664 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       rcs_eq_type=SYSTEM_EQ;
	     }
#line 2558 "readcuiksystem.tab.c"
    break;

  case 74:
#line 673 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
            {
	      rcs_eq_type=COORD_EQ;
	    }
#line 2566 "readcuiksystem.tab.c"
    break;

  case 77:
#line 681 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
            {
	      rcs_eq_type=DUMMY_EQ;
	    }
#line 2574 "readcuiksystem.tab.c"
    break;

  case 80:
#line 689 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                  {
	             rcs_eq_type=NON_DYNAMIC_EQ;
		  }
#line 2582 "readcuiksystem.tab.c"
    break;

  case 83:
#line 698 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
               {
		 if (rcs_prefixID)
		   Error("Can not add velocity equations to a world");
		 
		 Warning("Velocity equations should be defined automatically and not given in a cuik file. This may lead to an inconsisten system");
	         rcs_eq_type=VELOCITY_EQ;
	       }
#line 2594 "readcuiksystem.tab.c"
    break;

  case 87:
#line 713 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
        { 
	  SetCSSearchMode(DEPTH_FIRST_SEARCH,NULL,rcs_cuiksystem);
        }
#line 2602 "readcuiksystem.tab.c"
    break;

  case 88:
#line 719 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
               SetCSSearchMode(DEPTH_FIRST_SEARCH,NULL,rcs_cuiksystem);
             }
#line 2610 "readcuiksystem.tab.c"
    break;

  case 89:
#line 723 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
               SetCSSearchMode(BREADTH_FIRST_SEARCH,NULL,rcs_cuiksystem);
             }
#line 2618 "readcuiksystem.tab.c"
    break;

  case 90:
#line 727 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       SetEquationType(SYSTEM_EQ,&rcs_equation);
	       SetEquationCmp(EQU,&rcs_equation);
               SetCSSearchMode(MINIMIZATION_SEARCH,&(rcs_equation),rcs_cuiksystem);
	       ResetEquation(&rcs_equation);
             }
#line 2629 "readcuiksystem.tab.c"
    break;

  case 91:
#line 736 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
         {
	   AddEquation2CS(rcs_parameters,&rcs_equation,rcs_cuiksystem);

	   /*Get ready for next equation definition*/
	   ResetEquation(&rcs_equation);
	 }
#line 2640 "readcuiksystem.tab.c"
    break;

  case 94:
#line 747 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    rcs_sgn=-1.0;
          }
#line 2648 "readcuiksystem.tab.c"
    break;

  case 95:
#line 751 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    if ((rcs_prefixID)&&(rcs_eq_type==VELOCITY_EQ))
	      ReadcuiksystemSemanticError("Can not define velocity equations in the equations files included into a world file. Velocity variables/equations are automatically defined");

	    SetEquationType(rcs_eq_type,&rcs_equation);
	    SetEquationCmp((yyvsp[-3].int_number),&rcs_equation);

	    rcs_sgn=1.0;
	  }
#line 2662 "readcuiksystem.tab.c"
    break;

  case 96:
#line 763 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {
	    AddCt2Monomial(rcs_sgn,&rcs_monomial);
	    AddMonomial(&rcs_monomial,&rcs_equation);
	    ResetMonomial(&rcs_monomial);
	  }
#line 2672 "readcuiksystem.tab.c"
    break;

  case 98:
#line 772 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
              {
		AddCt2Monomial(rcs_sgn,&rcs_monomial);
	        AddMonomial(&rcs_monomial,&rcs_equation);
	        ResetMonomial(&rcs_monomial);
	      }
#line 2682 "readcuiksystem.tab.c"
    break;

  case 104:
#line 787 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 AddCt2Monomial(-1.0,&rcs_monomial);
       }
#line 2690 "readcuiksystem.tab.c"
    break;

  case 107:
#line 797 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[0].int_number)==1)
	   AddCt2Monomial((yyvsp[-1].real_number),&rcs_monomial);
	 else
	   AddCt2Monomial(pow((yyvsp[-1].real_number),(double)(yyvsp[0].int_number)),&rcs_monomial);
       }
#line 2701 "readcuiksystem.tab.c"
    break;

  case 108:
#line 804 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[0].int_number)==1)
	   AddCt2Monomial((double)(yyvsp[-1].int_number),&rcs_monomial);
	 else
	   AddCt2Monomial(pow((double)(yyvsp[-1].int_number),(double)(yyvsp[0].int_number)),&rcs_monomial);
       }
#line 2712 "readcuiksystem.tab.c"
    break;

  case 109:
#line 811 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[-2].expr).id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(SINV,id,(yyvsp[0].int_number),&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",(yyvsp[-2].expr).id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free((yyvsp[-2].expr).id);
	   }
	 else
	   {
	     if ((yyvsp[0].int_number)==1)
	       AddCt2Monomial(sin((yyvsp[-2].expr).value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(sin((yyvsp[-2].expr).value),(double)(yyvsp[0].int_number)),&rcs_monomial);  
	   }
       }
#line 2742 "readcuiksystem.tab.c"
    break;

  case 110:
#line 837 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[-2].expr).id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(COSV,id,(yyvsp[0].int_number),&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",(yyvsp[-2].expr).id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free((yyvsp[-2].expr).id);
	   }
	 else
	   {
	     if ((yyvsp[0].int_number)==1)
	       AddCt2Monomial(cos((yyvsp[-2].expr).value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(cos((yyvsp[-2].expr).value),(double)(yyvsp[0].int_number)),&rcs_monomial);  
	   }  
       }
#line 2772 "readcuiksystem.tab.c"
    break;

  case 111:
#line 863 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[-2].expr).id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(TANV,id,(yyvsp[0].int_number),&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",(yyvsp[-2].expr).id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free((yyvsp[-2].expr).id);
	   }
	 else
	   {
	     if ((yyvsp[0].int_number)==1)
	       AddCt2Monomial(tan((yyvsp[-2].expr).value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(tan((yyvsp[-2].expr).value),(double)(yyvsp[0].int_number)),&rcs_monomial);  
	   }  
       }
#line 2802 "readcuiksystem.tab.c"
    break;

  case 112:
#line 889 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[-2].expr).id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(EXPV,id,(yyvsp[0].int_number),&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",(yyvsp[-2].expr).id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free((yyvsp[-2].expr).id);
	   }
	 else
	   {
	     if ((yyvsp[0].int_number)==1)
	       AddCt2Monomial(exp((yyvsp[-2].expr).value),&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(exp((yyvsp[-2].expr).value),(double)(yyvsp[0].int_number)),&rcs_monomial);  
	   }  
       }
#line 2832 "readcuiksystem.tab.c"
    break;

  case 113:
#line 915 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 if ((yyvsp[-2].expr).id!=NULL)
	   {
	     unsigned int id;

	     id=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(PWPV,id,(yyvsp[0].int_number),&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable %.150s",(yyvsp[-2].expr).id);
		 ReadcuiksystemSemanticError(s);
	       }
	     free((yyvsp[-2].expr).id);
	   }
	 else
	   {
	     double v;
	     
	     if ((yyvsp[-2].expr).value<0.0)
	       v=(yyvsp[-2].expr).value*(yyvsp[-2].expr).value;
	     else
	       v=0.0;
	     
	     if ((yyvsp[0].int_number)==1)
	       AddCt2Monomial(v,&rcs_monomial); 
	     else
	       AddCt2Monomial(pow(v,(double)(yyvsp[0].int_number)),&rcs_monomial);  
	   }  
       }
#line 2869 "readcuiksystem.tab.c"
    break;

  case 114:
#line 948 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 AddCt2Monomial(pow(M_PI,(double)((yyvsp[0].int_number))),&rcs_monomial);
       }
#line 2877 "readcuiksystem.tab.c"
    break;

  case 115:
#line 952 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 unsigned int id;
	 unsigned int nc;

	 nc=GetConstantWithName((yyvsp[-2].id),rcs_constants);

	 if (nc!=NO_UINT)
	   {
	     char s[250];
	     
	     sprintf(s,"Constants have no differential %.150s",(yyvsp[-2].id));
	     ReadcuiksystemSemanticError(s);
	   }
	 else
	   { 
	     NEW(rcs_ID,strlen((yyvsp[-2].id))+20,char);
	     if (rcs_prefixID)
	       sprintf(rcs_ID,"_diff(%.150s)",(yyvsp[-2].id));
	     else
	       sprintf(rcs_ID,"diff(%.150s)",(yyvsp[-2].id));
	     
	     id=GetCSVariableID(rcs_ID,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       {
		 if (rcs_prefixID)
		   ReadcuiksystemSemanticError("Can not define velocity variables in the equation files included into a world file. Velocity variables/equations are automatically defined");
	    
		 AddVariable2Monomial(NFUN,id,(yyvsp[0].int_number),&rcs_monomial);
	       }
	     else
	       {
		 char s[300];
		 
		 sprintf(s,"Unknown variable diff(%.150s)",(yyvsp[-2].id));
		 ReadcuiksystemSemanticError(s);
	       }
	     free(rcs_ID);
	   }
	 free((yyvsp[-2].id));
       }
#line 2922 "readcuiksystem.tab.c"
    break;

  case 116:
#line 993 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 unsigned int id;
	 unsigned int nc;

	 nc=GetConstantWithName((yyvsp[-1].id),rcs_constants);

	 if (nc!=NO_UINT)
	   AddCt2Monomial(pow(GetConstantValue(nc,rcs_constants),(double)((yyvsp[0].int_number))),&rcs_monomial);
	 else
	   {
	     if (rcs_prefixID)
	       {
		 NEW(rcs_ID,strlen((yyvsp[-1].id))+2,char);
		 sprintf(rcs_ID,"_%s",(yyvsp[-1].id));
	       }
	     else
	       rcs_ID=(yyvsp[-1].id);
	     
	     id=GetCSVariableID(rcs_ID,rcs_cuiksystem);
	     if (id!=NO_UINT) /*a known variable*/
	       AddVariable2Monomial(NFUN,id,(yyvsp[0].int_number),&rcs_monomial);
	     else
	       {
		 char s[250];
		 
		 sprintf(s,"Unknown variable or constant %.150s",rcs_ID);
		 ReadcuiksystemSemanticError(s);
	       }
	     if (rcs_prefixID)
	       free(rcs_ID);
	   }
	 free((yyvsp[-1].id));
       }
#line 2960 "readcuiksystem.tab.c"
    break;

  case 117:
#line 1029 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
        {
	  (yyval.int_number)=(yyvsp[0].int_number);
	}
#line 2968 "readcuiksystem.tab.c"
    break;

  case 118:
#line 1033 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
        {
	  (yyval.int_number)=1;
	}
#line 2976 "readcuiksystem.tab.c"
    break;

  case 119:
#line 1039 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
      {
        (yyval.int_number)=EQU;
      }
#line 2984 "readcuiksystem.tab.c"
    break;

  case 120:
#line 1043 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
      {
        (yyval.int_number)=LEQ;
      }
#line 2992 "readcuiksystem.tab.c"
    break;

  case 121:
#line 1047 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
      {
        (yyval.int_number)=GEQ;
      }
#line 3000 "readcuiksystem.tab.c"
    break;

  case 122:
#line 1053 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
          {   
	    IdentityRHSMEquation(&rcs_mequation);
	    SimplifyMEquation(&rcs_mequation);
	    if ((rcs_prefixID)||(rcs_eq_type==NON_DYNAMIC_EQ))
	      MarkAsNonDynamicMEquation(&rcs_vmequation);
	    AddMatrixEquation2CS(rcs_parameters,&rcs_mequation,rcs_cuiksystem);

	    ResetMEquation(&rcs_mequation);
	  }
#line 3014 "readcuiksystem.tab.c"
    break;

  case 125:
#line 1067 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
           {
	     ZeroRHSMEquation(&rcs_vmequation); // Not necessary but...
	     MarkAsVelocityMEquation(&rcs_vmequation);
	     SimplifyMEquation(&rcs_vmequation);
	     AddMatrixEquation2CS(rcs_parameters,&rcs_vmequation,rcs_cuiksystem);
	     /* Matrix equations with more than one term can not be reset -> destroy + allocate */
	     DeleteMEquation(&rcs_vmequation);	 
	   }
#line 3027 "readcuiksystem.tab.c"
    break;

  case 128:
#line 1080 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                 {
		   ZeroRHSMEquation(&rcs_mequation);
		   AccumulateMEquations(rcs_scaleID,&rcs_mequation,&rcs_vmequation);
		   ResetMEquation(&rcs_mequation);
		 }
#line 3037 "readcuiksystem.tab.c"
    break;

  case 129:
#line 1086 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                 {
		   ZeroRHSMEquation(&rcs_mequation);
		   CopyMEquation(&rcs_vmequation,&rcs_mequation); /* This already initializes vmequation */
		   if (rcs_scaleID!=NO_UINT)
		     ScaleMEquation(rcs_scaleID,&rcs_vmequation);
		   ResetMEquation(&rcs_mequation);
		 }
#line 3049 "readcuiksystem.tab.c"
    break;

  case 131:
#line 1099 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                  {
		    char vname[250];

		    if (rcs_prefixID)
		      sprintf(vname,"_diff(%.150s)",(yyvsp[-1].id));
		    else
		      sprintf(vname,"diff(%.150s)",(yyvsp[-1].id));
		    rcs_scaleID=GetCSVariableID(vname,rcs_cuiksystem);
		    if (rcs_scaleID==NO_UINT) /*a known variable*/
		      {
			char s[300];
		 
			sprintf(s,"Unknown velocity variable diff(%.150s)",(yyvsp[-1].id));
			ReadcuiksystemSemanticError(s);
		      }
		    free((yyvsp[-1].id));
		  }
#line 3071 "readcuiksystem.tab.c"
    break;

  case 132:
#line 1117 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
                  {
		    rcs_scaleID=NO_UINT;
		  }
#line 3079 "readcuiksystem.tab.c"
    break;

  case 135:
#line 1128 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 THTransform t;

	 if (((yyvsp[-24].expr).id!=NULL)||((yyvsp[-22].expr).id!=NULL)||((yyvsp[-20].expr).id!=NULL)||((yyvsp[-18].expr).id!=NULL)||
	     ((yyvsp[-16].expr).id!=NULL)||((yyvsp[-14].expr).id!=NULL)||((yyvsp[-12].expr).id!=NULL)||((yyvsp[-10].expr).id!=NULL)||
	     ((yyvsp[-8].expr).id!=NULL)||((yyvsp[-6].expr).id!=NULL)||((yyvsp[-4].expr).id!=NULL)||((yyvsp[-2].expr).id!=NULL))
	   ReadcuiksystemSemanticError("Error defining a constant transform");
	 
	 HTransformIdentity(&t);
	 
	 HTransformSetElement(0,0,(yyvsp[-24].expr).value,&t);
	 HTransformSetElement(0,1,(yyvsp[-22].expr).value,&t);
	 HTransformSetElement(0,2,(yyvsp[-20].expr).value,&t);
	 HTransformSetElement(0,3,(yyvsp[-18].expr).value,&t);
	 HTransformSetElement(1,0,(yyvsp[-16].expr).value,&t);
	 HTransformSetElement(1,1,(yyvsp[-14].expr).value,&t);
	 HTransformSetElement(1,2,(yyvsp[-12].expr).value,&t);
	 HTransformSetElement(1,3,(yyvsp[-10].expr).value,&t);
	 HTransformSetElement(2,0,(yyvsp[-8].expr).value,&t);
	 HTransformSetElement(2,1,(yyvsp[-6].expr).value,&t);
	 HTransformSetElement(2,2,(yyvsp[-4].expr).value,&t);
	 HTransformSetElement(2,3,(yyvsp[-2].expr).value,&t);
	 
	 if ((yyvsp[0].int_number)<0)
	   HTransformInverse(&t,&t);
	 
	 AddCtTrans2MEquation(&t,&rcs_mequation);
	 
	 HTransformDelete(&t);
       }
#line 3114 "readcuiksystem.tab.c"
    break;

  case 136:
#line 1159 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 unsigned int nv,nc;
	 double ctValue;
	 boolean constant;

	 /* Translation along a vector */

	 if (((yyvsp[-8].expr).id!=NULL)||((yyvsp[-6].expr).id!=NULL)||((yyvsp[-4].expr).id!=NULL))
	   ReadcuiksystemSemanticError("Error defining a TV transform");
	 
	 constant=FALSE;
	 if ((yyvsp[-2].expr).id==NULL)
	   {
	     constant=TRUE;
	     ctValue=(double)(yyvsp[0].int_number)*(yyvsp[-2].expr).value;
	   }
	 else
	   {
	     nc=GetConstantWithName((yyvsp[-2].expr).id,rcs_constants);
	     if (nc!=NO_UINT)
	       {
		 constant=TRUE;
		 ctValue=(double)(yyvsp[0].int_number)*GetConstantValue(nc,rcs_constants);
	       }
	   }

	 if (constant)
	   {
	     /* Actually defining a ct transform */
	     THTransform t;

	     HTransformTxyz(ctValue*(yyvsp[-8].expr).value,ctValue*(yyvsp[-6].expr).value,ctValue*(yyvsp[-4].expr).value,&t);
	     AddCtTrans2MEquation(&t,&rcs_mequation); 
	     HTransformDelete(&t);
	   }
	 else
	   {
	     nv=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     
	     rcs_vect[0]=(yyvsp[-8].expr).value;
	     rcs_vect[1]=(yyvsp[-6].expr).value;
	     rcs_vect[2]=(yyvsp[-4].expr).value;

	     AddDispTrans2MEquation((yyvsp[0].int_number),nv,rcs_vect,&rcs_mequation);
	   }
	 if ((yyvsp[-2].expr).id!=NULL)
	   free((yyvsp[-2].expr).id);
       }
#line 3167 "readcuiksystem.tab.c"
    break;

  case 137:
#line 1208 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 unsigned int nv,nc;
	 double ctValue;
	 boolean constant;

	 constant=FALSE;
	 if ((yyvsp[-2].expr).id==NULL)
	   {
	     constant=TRUE;
	     ctValue=(double)(yyvsp[0].int_number)*(yyvsp[-2].expr).value;
	   }
	 else
	   {
	     nc=GetConstantWithName((yyvsp[-2].expr).id,rcs_constants);
	     if (nc!=NO_UINT)
	       {
		 constant=TRUE;
		 ctValue=(double)(yyvsp[0].int_number)*GetConstantValue(nc,rcs_constants);
	       }
	   }

	 if (constant)
	   {
	     /* Actually defining a ct transform */
	     THTransform t;

	     if (((yyvsp[-4].int_number)!=TX)&&((yyvsp[-4].int_number)!=TY)&&((yyvsp[-4].int_number)!=TZ)&&((yyvsp[-4].int_number)!=RX)&&((yyvsp[-4].int_number)!=RY)&&((yyvsp[-4].int_number)!=RZ))
	       ReadcuiksystemSemanticError("Only basic transforms (Tx,Ty,Tz,Rx,Ry,Rz) can be set to constant");
	       
	     HTransformCreate((yyvsp[-4].int_number),ctValue,&t);
	     AddCtTrans2MEquation(&t,&rcs_mequation); 
	     HTransformDelete(&t);
	   }
	 else
	   {
	     nv=GetCSVariableID((yyvsp[-2].expr).id,rcs_cuiksystem);
	     AddVarTrans2MEquation((yyvsp[-4].int_number),(yyvsp[0].int_number),nv,&rcs_mequation);
	   }	 
	 if ((yyvsp[-2].expr).id!=NULL)
	   free((yyvsp[-2].expr).id);
       }
#line 3213 "readcuiksystem.tab.c"
    break;

  case 138:
#line 1250 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
       {
	 unsigned int u,v;

	 u=GetCSVariableID((yyvsp[-4].id),rcs_cuiksystem);
	 if (u==NO_UINT) 
	   {
	     char s[250];
	     
	     sprintf(s,"Undefined variable %.150s",(yyvsp[-4].id));
	     ReadcuiksystemSemanticError(s);
	   }

	 v=GetCSVariableID((yyvsp[-2].id),rcs_cuiksystem);
	 if (v==NO_UINT) 
	   {
	     char s[250];
	     
	     sprintf(s,"Undefined variable %.150s",(yyvsp[-2].id));
	     ReadcuiksystemSemanticError(s);
	   }

	 AddPatchTrans2MEquation((yyvsp[-8].int_number),(yyvsp[0].int_number),u,v,rcs_point,&rcs_mequation);
       }
#line 3241 "readcuiksystem.tab.c"
    break;

  case 139:
#line 1276 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=-1;
             }
#line 3249 "readcuiksystem.tab.c"
    break;

  case 140:
#line 1280 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=1;
             }
#line 3257 "readcuiksystem.tab.c"
    break;

  case 141:
#line 1286 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=TX;
	     }
#line 3265 "readcuiksystem.tab.c"
    break;

  case 142:
#line 1290 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=TY;
	     }
#line 3273 "readcuiksystem.tab.c"
    break;

  case 143:
#line 1294 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=TZ;
	     }
#line 3281 "readcuiksystem.tab.c"
    break;

  case 144:
#line 1298 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=RX;
	     }
#line 3289 "readcuiksystem.tab.c"
    break;

  case 145:
#line 1302 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=RY;
	     }
#line 3297 "readcuiksystem.tab.c"
    break;

  case 146:
#line 1306 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=RZ;
	     }
#line 3305 "readcuiksystem.tab.c"
    break;

  case 147:
#line 1310 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=dRX;
	     }
#line 3313 "readcuiksystem.tab.c"
    break;

  case 148:
#line 1314 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=dRY;
	     }
#line 3321 "readcuiksystem.tab.c"
    break;

  case 149:
#line 1318 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=dRZ;
	     }
#line 3329 "readcuiksystem.tab.c"
    break;

  case 150:
#line 1322 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=ddRX;
	     }
#line 3337 "readcuiksystem.tab.c"
    break;

  case 151:
#line 1326 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=ddRY;
	     }
#line 3345 "readcuiksystem.tab.c"
    break;

  case 152:
#line 1330 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=ddRZ;
	     }
#line 3353 "readcuiksystem.tab.c"
    break;

  case 153:
#line 1336 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=PA;
	     }
#line 3361 "readcuiksystem.tab.c"
    break;

  case 154:
#line 1340 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=dPA_U;
	     }
#line 3369 "readcuiksystem.tab.c"
    break;

  case 155:
#line 1344 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=dPA_V;
	     }
#line 3377 "readcuiksystem.tab.c"
    break;

  case 156:
#line 1348 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=ddPA_UU;
	     }
#line 3385 "readcuiksystem.tab.c"
    break;

  case 157:
#line 1352 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=ddPA_UV;
	     }
#line 3393 "readcuiksystem.tab.c"
    break;

  case 158:
#line 1356 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
             {
	       (yyval.int_number)=ddPA_VV;
	     }
#line 3401 "readcuiksystem.tab.c"
    break;

  case 159:
#line 1362 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"
               {
		 if (((yyvsp[-22].expr).id!=NULL)||((yyvsp[-20].expr).id!=NULL)||((yyvsp[-18].expr).id!=NULL)||
		     ((yyvsp[-16].expr).id!=NULL)||((yyvsp[-14].expr).id!=NULL)||((yyvsp[-12].expr).id!=NULL)||
		     ((yyvsp[-10].expr).id!=NULL)||((yyvsp[-8].expr).id!=NULL)||((yyvsp[-6].expr).id!=NULL)||
		     ((yyvsp[-4].expr).id!=NULL)||((yyvsp[-2].expr).id!=NULL)||((yyvsp[0].expr).id!=NULL))
		   ReadcuiksystemSemanticError("Error defining a patch transform");

		 rcs_point[0][0]=(yyvsp[-22].expr).value;
		 rcs_point[0][1]=(yyvsp[-20].expr).value;
		 rcs_point[0][2]=(yyvsp[-18].expr).value;

		 rcs_point[1][0]=(yyvsp[-16].expr).value;
		 rcs_point[1][1]=(yyvsp[-14].expr).value;
		 rcs_point[1][2]=(yyvsp[-12].expr).value;

		 rcs_point[2][0]=(yyvsp[-10].expr).value;
		 rcs_point[2][1]=(yyvsp[-8].expr).value;
		 rcs_point[2][2]=(yyvsp[-6].expr).value;

		 rcs_point[3][0]=(yyvsp[-4].expr).value;
		 rcs_point[3][1]=(yyvsp[-2].expr).value;
		 rcs_point[3][2]=(yyvsp[0].expr).value;
	       }
#line 3429 "readcuiksystem.tab.c"
    break;


#line 3433 "readcuiksystem.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1387 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readcuiksystem.y"

/** \endcond */
/*
 * Reads a file containing the constants definitions, kinematic equations to be solved, 
 * and the range constrains for the variables.
 */
void InitCuikSystemFromFile(Tparameters *p,char *filename,TCuikSystem *cs)
{
  
  /*Start the data structures*/
  InitCuikSystem(cs);

  /*Add information to the data structure */
  AddCuikSystemFromFile(p,FALSE,NULL,filename,cs);
  
  if (GetParameter(CT_DYNAMICS,rcs_parameters)>0)
    AddVelocityEquations(p,NULL,cs);
} 

void AddCuikSystemFromFile(Tparameters *p,boolean prefix,Tconstants *cts,char *filename,TCuikSystem *cs)
{
  unsigned int i;

  rcs_parameters=p;
  
  Readcuiksystemin=fopen(filename,"r");
  if (!Readcuiksystemin) 
    {
      char ErrorText[500];

      sprintf(ErrorText,"File %.450s does not exists",filename);
      Error(ErrorText);
    }
  
  /* If true where are adding equations to a system automatically generated
     from a world file. Then, all variables must be preceeded with a '_' symbol */
  rcs_prefixID=prefix;
  
  /* and re-use the previously defined constants (they can appear in the added equations). */
  if (cts!=NULL)
    MergeConstants(&(cs->constants),cts,&(cs->constants));
  
  rcs_constants=&(cs->constants);
  
  /*Reset the lines numbering*/
  RCSline=1;

  /*we initalize the global pointer to make the parameters accesibles to any one inside the YACC module*/
  rcs_cuiksystem=cs;
  
  /*Get ready for first equation*/
  InitEquation(&rcs_equation);
  InitMEquation(&rcs_mequation);
  InitKEquation(&rcs_kequation);
  InitMonomial(&rcs_monomial);

  /* space for points */
  NEW(rcs_point,4,double *);
  for(i=0;i<4;i++)
    { NEW(rcs_point[i],3,double); }

  /*and process the file*/
  Readcuiksystemparse();

  /* and release structures */
  for(i=0;i<4;i++)
    free(rcs_point[i]);
  free(rcs_point);

  DeleteEquation(&rcs_equation);
  DeleteKEquation(&rcs_kequation);
  DeleteMEquation(&rcs_mequation);
  DeleteMonomial(&rcs_monomial);

  cs->updated=FALSE;
  fclose(Readcuiksystemin);
} 
 
