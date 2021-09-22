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
#define yyparse         ReadParametersparse
#define yylex           ReadParameterslex
#define yyerror         ReadParameterserror
#define yydebug         ReadParametersdebug
#define yynerrs         ReadParametersnerrs
#define yylval          ReadParameterslval
#define yychar          ReadParameterschar

/* First part of user prologue.  */
#line 1 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
 
/** \cond */

#include "parameters.h"
#include "error.h"
#include "boolean.h"
#include "defines.h"

#include <stdlib.h> 
#include <stdio.h>
#include <math.h>

  Tparameters *rp_ps; /*global pointer used from inside the parser to refer to the current set of
		       parameter being read*/

  /*Lex and Yacc variables*/
  extern FILE *ReadParametersin; 

  /*Lex and Yacc functions*/
  int ReadParameterslex(void); 

  /*Our own variables*/
  extern unsigned int RPNline; /*line number currently processed (incremented by the LEX processor)*/


#line 103 "readparameters.tab.c"

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

#line 255 "readparameters.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE ReadParameterslval;

int ReadParametersparse (void);

#endif /* !YY_READPARAMETERS_READPARAMETERS_TAB_H_INCLUDED  */



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
#define YYFINAL  101
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   732

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

#define YYUNDEFTOK  2
#define YYMAXUTOK   350


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     104,   105,    99,    97,     2,    98,     2,   100,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   107,     2,
      95,   103,    96,   106,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   101,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
     102
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    59,    59,    60,    63,    70,    77,    85,    92,    99,
     106,   113,   120,   127,   134,   141,   150,   159,   169,   178,
     185,   194,   203,   212,   221,   226,   231,   238,   243,   248,
     253,   258,   267,   276,   284,   294,   306,   318,   323,   328,
     333,   340,   349,   357,   366,   374,   382,   392,   400,   405,
     410,   422,   430,   440,   449,   457,   465,   473,   481,   489,
     497,   505,   513,   521,   529,   537,   545,   553,   561,   569,
     577,   585,   593,   601,   609,   617,   625,   633,   641,   649,
     657,   665,   673,   681,   689,   697,   705,   713,   721,   729,
     737,   745,   753,   761,   769,   777,   785,   793,   801,   809,
     817,   825,   835,   839,   843,   847,   851,   855,   859,   863,
     867,   873,   877,   881,   890,   894,   898,   902,   908,   912,
     916,   920,   924,   928,   932,   938,   942,   946,   950,   956,
     960,   965,   970,   974,   978,   982,   986,   990,   994,   998,
    1002,  1006,  1013,  1017,  1021,  1025,  1029,  1033,  1037,  1041,
    1045,  1049,  1053,  1057,  1063,  1072,  1081,  1085,  1089,  1093,
    1097,  1103,  1107
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_TRUE", "_FALSE", "_OR", "_AND", "_NOT",
  "_GEQ", "_LEQ", "_EQU", "_PI", "_COS", "_SIN", "_TAN", "_EXP", "_LOG",
  "_SQRT", "_INF", "_EPSILON", "_REPRESENTATION", "_SIGMA", "_SMALL_SIGMA",
  "_R", "_SR", "_E", "_CE", "_DELTA", "_BETA", "_RHO", "_STATE_PERIOD",
  "_N_SOLUTIONS", "_MAX_NEWTON_ITERATIONS", "_N_DOF", "_GAMMA", "_DUMMIFY",
  "_SPLIT_TYPE", "_SAFE_SIMPLEX", "_SIMPLIFICATION_LEVEL", "_LR2TM_Q",
  "_LR2TM_S", "_VDW_RATIO", "_LINKS", "_FLINKS", "_QLINKS", "_JOINTS",
  "_CUT_X", "_CUT_Y", "_CUT_Z", "_COEF_TEMP", "_NFAIL_MAX",
  "_DETECT_BIFURCATIONS", "_MAX_PLANNING_TIME", "_MAX_CHARTS",
  "_MAX_PLANNING_ITERATIONS", "_MAX_NODES_RRT", "_BI_RRT", "_RRT_GRAPH",
  "_DYNAMIC_DOMAIN", "_CD_ENGINE", "_SOLID", "_VCOLLIDE", "_PQP", "_FCL",
  "_C_FCL", "_BULLET", "_C_BULLET", "_RIGIDCLL", "_NONE", "_SAMPLING",
  "_TANGENT_SAMPLING", "_AMBIENT_SAMPLING", "_KDTREE_SAMPLING",
  "_PRETENSION", "_DYNAMICS", "_L_TRAPEZOID", "_L_EULER", "_L_RK4",
  "_EULER", "_RK4", "_INTEGRATION_TIME", "_DEFAULT_MAX_VELOCITY",
  "_N_DYNAMIC_ACTIONS", "_DYNAMIC_GOAL_ERROR", "_G_COMPENSATION",
  "_NEG_LM", "_G_AXIS", "_X", "_Y", "_Z", "_TAU", "_LQR_PLANNING_TIME",
  "_INTEGER", "_REAL", "_MIN_PRECEDENCE", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'^'", "_MAX_PRECEDENCE", "'='", "'('", "')'", "'?'",
  "':'", "$accept", "parameters", "parameter", "ct", "col_engine",
  "sampling_mode", "rep_type", "int_method", "select_axis", "opt_sign",
  "expr", "boolean_value", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,    60,    62,    43,    45,    42,
      47,    94,   350,    61,    40,    41,    63,    58
};
# endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     641,   -67,   -66,   -54,   -53,   -37,   -30,   -29,   -28,   -25,
     -21,   -20,   -19,   -18,   -14,   -10,     5,     6,     7,     8,
       9,    10,    13,    14,    16,    17,    18,    19,    20,    21,
      22,    23,    26,    30,    31,    32,    33,    34,    35,    36,
      37,    45,    47,    48,    49,    58,    60,    70,    72,    81,
      86,   641,   332,    15,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,    39,    -9,
     332,   236,   332,   332,   332,   332,   332,   332,   428,   332,
     332,   -68,   -68,   -68,   -68,   332,   -68,    90,    97,    98,
      99,   112,   120,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   332,   332,   332,   -68,   558,
     -68,   -68,   -68,   -68,   -68,   -68,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   558,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   558,   558,   558,   558,   558,   558,   558,   332,
     332,   -68,   -17,   558,   558,   558,   -68,   332,   332,   332,
     332,   332,   332,   -68,   -68,    59,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   -68,   -68,
     -68,    71,    82,   122,   394,   525,   536,   -68,   332,    -5,
      61,    92,    92,    92,    92,    92,    -5,    -5,    61,    61,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,    46,   332,   547,
     -68
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,     0,
       0,     1,     2,   161,   162,     0,   134,     0,     0,     0,
       0,     0,     0,   135,    53,    54,    56,    57,    60,    61,
      58,    59,    62,    63,    55,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    84,    83,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   132,   133,     0,     0,     0,   137,     4,
     136,   114,   115,   116,   117,     5,     7,     8,    11,    12,
       9,    10,    13,    14,     6,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    35,    34,    36,    37,    38,    39,
     102,   103,   104,   105,   106,   107,   108,   109,   110,    40,
     111,   112,   113,    41,    42,   118,   119,   120,   121,   122,
     123,    43,   124,    44,    45,    46,    47,    48,    49,   129,
     130,    50,     0,   125,    51,    52,   153,     0,     0,     0,
       0,     0,     0,   138,   139,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   126,   127,
     128,     0,     0,     0,     0,     0,     0,   140,     0,   155,
     154,   159,   158,   160,   156,   157,   142,   143,   144,   146,
     145,   147,   148,   149,   150,   151,   152,     0,     0,     0,
     141
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,    67,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -52,   -68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    50,    51,   168,   219,   223,   175,   231,   241,   242,
     253,   170
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     169,   257,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,    52,    53,   224,   232,
     233,   234,   235,   236,   237,   238,   243,   244,   245,    54,
      55,   256,   257,   246,   258,   259,   260,   171,   172,   173,
     174,   220,   221,   222,   256,   257,    56,   258,   259,   260,
     268,   269,   270,    57,    58,    59,   256,   257,    60,   258,
     259,   260,    61,    62,    63,    64,   101,   256,   257,    65,
     258,   259,   260,    66,   265,   266,   267,   256,   257,   210,
     211,   212,   213,   214,   215,   216,   217,   218,    67,    68,
      69,    70,    71,    72,   254,   255,    73,    74,   102,    75,
      76,    77,    78,    79,    80,    81,    82,   256,   257,    83,
     258,   259,   260,    84,    85,    86,    87,    88,    89,    90,
      91,   261,   262,   263,   264,   265,   266,   267,    92,     0,
      93,    94,    95,   298,   261,   262,   263,   264,   265,   266,
     267,    96,   267,    97,   277,   278,   261,   262,   263,   264,
     265,   266,   267,    98,     0,    99,   291,   261,   262,   263,
     264,   265,   266,   267,   100,     0,     0,   292,   254,   263,
     264,   265,   266,   267,   247,   271,   272,   273,   274,   275,
     276,   248,   249,   250,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   251,   261,   262,   263,
     264,   265,   266,   267,   252,     0,   297,   293,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,     0,     0,   105,     0,     0,   299,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,     0,
       0,     0,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,     0,     0,     0,     0,
       0,     0,     0,     0,   225,   151,     0,     0,     0,   152,
     153,   226,   227,   228,   229,   230,   154,   155,   156,   157,
     158,   159,   160,     0,     0,     0,   161,   162,   163,   164,
       0,     0,     0,   165,   166,   103,   104,     0,     0,   105,
     167,     0,     0,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,     0,     0,     0,     0,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,     0,     0,     0,     0,     0,     0,     0,   256,
     257,   151,   258,   259,   260,   152,   153,     0,     0,     0,
       0,     0,   154,   155,   156,   157,   158,   159,   160,     0,
       0,     0,   161,   162,   163,   164,     0,     0,     0,   165,
     166,   103,   104,     0,     0,   105,   167,     0,     0,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
       0,     0,     0,     0,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,     0,   261,
     262,   263,   264,   265,   266,   267,     0,   151,     0,   294,
       0,   152,   153,     0,     0,     0,     0,     0,   154,   155,
     156,   157,   158,   159,   160,     0,     0,     0,   161,   162,
     163,   164,     0,     0,     0,   239,   240,     0,     0,     0,
     256,   257,   167,   258,   259,   260,     0,     0,     0,     0,
       0,   256,   257,     0,   258,   259,   260,     0,     0,     0,
       0,     0,   256,   257,     0,   258,   259,   260,     0,     0,
       0,     0,     0,   256,   257,     0,   258,   259,   260,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     261,   262,   263,   264,   265,   266,   267,     0,     0,     0,
     295,   261,   262,   263,   264,   265,   266,   267,     0,     0,
       0,   296,   261,   262,   263,   264,   265,   266,   267,     0,
       0,     0,   300,   261,   262,   263,   264,   265,   266,   267,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,     0,     0,     0,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,    39,    40,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,    46,    47,     0,     0,
       0,    48,    49
};

static const yytype_int16 yycheck[] =
{
      52,     6,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   103,   103,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   103,
     103,     5,     6,   105,     8,     9,    10,    42,    43,    44,
      45,    70,    71,    72,     5,     6,   103,     8,     9,    10,
      87,    88,    89,   103,   103,   103,     5,     6,   103,     8,
       9,    10,   103,   103,   103,   103,     0,     5,     6,   103,
       8,     9,    10,   103,    99,   100,   101,     5,     6,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   103,   103,
     103,   103,   103,   103,   166,   167,   103,   103,    51,   103,
     103,   103,   103,   103,   103,   103,   103,     5,     6,   103,
       8,     9,    10,   103,   103,   103,   103,   103,   103,   103,
     103,    95,    96,    97,    98,    99,   100,   101,   103,    -1,
     103,   103,   103,   107,    95,    96,    97,    98,    99,   100,
     101,   103,   101,   103,   105,   106,    95,    96,    97,    98,
      99,   100,   101,   103,    -1,   103,   105,    95,    96,    97,
      98,    99,   100,   101,   103,    -1,    -1,   105,   240,    97,
      98,    99,   100,   101,   104,   247,   248,   249,   250,   251,
     252,   104,   104,   104,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   104,    95,    96,    97,
      98,    99,   100,   101,   104,    -1,   278,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,     7,    -1,    -1,   298,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    -1,    -1,    -1,    90,    91,    92,    93,
      -1,    -1,    -1,    97,    98,     3,     4,    -1,    -1,     7,
     104,    -1,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
       6,    69,     8,     9,    10,    73,    74,    -1,    -1,    -1,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    -1,
      -1,    -1,    90,    91,    92,    93,    -1,    -1,    -1,    97,
      98,     3,     4,    -1,    -1,     7,   104,    -1,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    95,
      96,    97,    98,    99,   100,   101,    -1,    69,    -1,   105,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    90,    91,
      92,    93,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,
       5,     6,   104,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,     5,     6,    -1,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,     5,     6,    -1,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,     5,     6,    -1,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,    -1,    -1,    -1,
     105,    95,    96,    97,    98,    99,   100,   101,    -1,    -1,
      -1,   105,    95,    96,    97,    98,    99,   100,   101,    -1,
      -1,    -1,   105,    95,    96,    97,    98,    99,   100,   101,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    -1,    -1,
      -1,    90,    91
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    69,    73,
      74,    80,    81,    82,    83,    84,    85,    86,    90,    91,
     109,   110,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,     0,   109,     3,     4,     7,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    69,    73,    74,    80,    81,    82,    83,    84,    85,
      86,    90,    91,    92,    93,    97,    98,   104,   111,   118,
     119,    42,    43,    44,    45,   114,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
      60,    61,    62,    63,    64,    65,    66,    67,    68,   112,
      70,    71,    72,   113,   118,    68,    75,    76,    77,    78,
      79,   115,   118,   118,   118,   118,   118,   118,   118,    97,
      98,   116,   117,   118,   118,   118,   118,   104,   104,   104,
     104,   104,   104,   118,   118,   118,     5,     6,     8,     9,
      10,    95,    96,    97,    98,    99,   100,   101,    87,    88,
      89,   118,   118,   118,   118,   118,   118,   105,   106,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   105,   105,   105,   105,   105,   105,   118,   107,   118,
     105
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   113,   114,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   116,   116,   116,   116,   117,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     7,     3,     3,     3,     3,     3,     4,     4,     4,
       4,     4,     4,     2,     3,     3,     3,     3,     3,     3,
       3,     1,     1
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
  case 4:
#line 64 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 0
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter EPSILON must be greater than (or equal to) 0.0");
	      SetParameter(CT_EPSILON,"EPSILON",(yyvsp[0].realValue),rp_ps);
            }
#line 1748 "readparameters.tab.c"
    break;

  case 5:
#line 71 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 1
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter REPRESENTATION must be an integer");
	      SetParameter(CT_REPRESENTATION,"REPRESENTATION",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 1759 "readparameters.tab.c"
    break;

  case 6:
#line 78 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 2
	      if (((yyvsp[0].realValue)>0.0)&&((yyvsp[0].realValue)<1.0))
		SetParameter(CT_RHO,"RHO",(yyvsp[0].realValue),rp_ps);
	      else
		Error("Parameter RHO must in the interval (0,1)");
	    }
#line 1771 "readparameters.tab.c"
    break;

  case 7:
#line 86 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 3
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter SIGMA  must be greater than (or equal to) 0.0");
	      SetParameter(CT_SIGMA,"SIGMA",(yyvsp[0].realValue),rp_ps);
            }
#line 1782 "readparameters.tab.c"
    break;

  case 8:
#line 93 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 4 
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter SMALL SIGMA  must be greater than (or equal to) 0.0");
	      SetParameter(CT_SMALL_SIGMA,"SMALL_SIGMA",(yyvsp[0].realValue),rp_ps);
            }
#line 1793 "readparameters.tab.c"
    break;

  case 9:
#line 100 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 5
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter E must be greater than (or equal to) 0.0");
	      SetParameter(CT_E,"E",(yyvsp[0].realValue),rp_ps);
            }
#line 1804 "readparameters.tab.c"
    break;

  case 10:
#line 107 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 6
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter CE must be greater than (or equal to) 0.0");
	      SetParameter(CT_CE,"CE",(yyvsp[0].realValue),rp_ps);
            }
#line 1815 "readparameters.tab.c"
    break;

  case 11:
#line 114 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 7
	      if ((yyvsp[0].realValue)<=0.0)
		Error("Parameter R must be greater than 0.0");
	      SetParameter(CT_R,"R",(yyvsp[0].realValue),rp_ps);
            }
#line 1826 "readparameters.tab.c"
    break;

  case 12:
#line 121 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 8
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter SR must be below 0.0");
	      SetParameter(CT_SR,"SR",(yyvsp[0].realValue),rp_ps);
            }
#line 1837 "readparameters.tab.c"
    break;

  case 13:
#line 128 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 9
	      if ((yyvsp[0].realValue)<0.0)
		Error("Parameter DELTA must be greater than (or equal to) 0.0");
	      SetParameter(CT_DELTA,"DELTA",(yyvsp[0].realValue),rp_ps);
            }
#line 1848 "readparameters.tab.c"
    break;

  case 14:
#line 135 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 10
	      if ((yyvsp[0].realValue)<1.0)
		Error("Parameter BETA must be larger or equal to 1");
	      SetParameter(CT_ATLASGBF_BETA,"BETA",(yyvsp[0].realValue),rp_ps);
            }
#line 1859 "readparameters.tab.c"
    break;

  case 15:
#line 142 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 11
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter STATE_PERIOD  must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter STATE_PERIOD must be greater than (or equal to) 0");
	      SetParameter(CT_STATE_PERIOD,"STATE_PERIOD",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 1872 "readparameters.tab.c"
    break;

  case 16:
#line 151 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 12
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter N_SOLUTIONS must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter N_SOLUTIONS must be greater than (or equal to) 0");
	      SetParameter(CT_N_SOLUTIONS,"N_SOLUTIONS",floor((yyvsp[0].realValue)),rp_ps);
	    }
#line 1885 "readparameters.tab.c"
    break;

  case 17:
#line 160 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 13
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter MAX_NEWTON_ITERATIONS must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter MAX_NEWTON_ITERATIONS must be greater than (or equal to) 0");
	      
	      SetParameter(CT_MAX_NEWTON_ITERATIONS,"MAX_NEWTON_ITERATIONS",floor((yyvsp[0].realValue)),rp_ps);
	    }
#line 1899 "readparameters.tab.c"
    break;

  case 18:
#line 170 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 14
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter N_DOF must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter N_DOF must be greater than (or equal to) 0");
	      SetParameter(CT_N_DOF,"N_DOF",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 1912 "readparameters.tab.c"
    break;

  case 19:
#line 179 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 15
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter GAMNA must be greater than (or equal to) 0");
	      SetParameter(CT_GAMMA,"GAMMA",(yyvsp[0].realValue),rp_ps);
            }
#line 1923 "readparameters.tab.c"
    break;

  case 20:
#line 186 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 16
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter DUMMIFY must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter DUMMIFY can not be negative");
	      SetParameter(CT_DUMMIFY,"DUMMIFY",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 1936 "readparameters.tab.c"
    break;

  case 21:
#line 195 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 17
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter SPLIT_TYPE must be an integer");
	      if (((yyvsp[0].realValue)<0)||((yyvsp[0].realValue)>2))
		Error("Parameter SPLIT_TYPE must be 0, 1, or 2");
	      SetParameter(CT_SPLIT_TYPE,"SPLIT_TYPE",(yyvsp[0].realValue),rp_ps);
            }
#line 1949 "readparameters.tab.c"
    break;

  case 22:
#line 204 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 18
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter SAFE_SIMPLEX must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter SAFE_SIMPLEX can not be negative");
	      SetParameter(CT_SAFE_SIMPLEX,"SAVE_SIMPLEX",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 1962 "readparameters.tab.c"
    break;

  case 23:
#line 213 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 19
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter SIMPLIFICATION_LEVEL must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter SIMPLIFICATION_LEVEL can not be negative");
	      SetParameter(CT_SIMPLIFICATION_LEVEL,"SIMPLIFICATION_LEVEL",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 1975 "readparameters.tab.c"
    break;

  case 24:
#line 222 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 20
	      SetParameter(CT_LR2TM_Q,"LR2TM_Q",(yyvsp[0].realValue),rp_ps);
            }
#line 1984 "readparameters.tab.c"
    break;

  case 25:
#line 227 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 21
	      SetParameter(CT_LR2TM_S,"LR2TM_S",(yyvsp[0].realValue),rp_ps);
            }
#line 1993 "readparameters.tab.c"
    break;

  case 26:
#line 232 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 22
	      if ((yyvsp[0].realValue)<=0.0)
		Error("Parameter VDW_RATIO must positive");
	      SetParameter(CT_VDW_RATIO,"VDW_RATIO",(yyvsp[0].realValue),rp_ps);
            }
#line 2004 "readparameters.tab.c"
    break;

  case 27:
#line 239 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 23
	      SetParameter(CT_CUT_X,"CUT_X",(yyvsp[0].realValue),rp_ps);
            }
#line 2013 "readparameters.tab.c"
    break;

  case 28:
#line 244 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 24
	      SetParameter(CT_CUT_Y,"CUT_Y",(yyvsp[0].realValue),rp_ps);
            }
#line 2022 "readparameters.tab.c"
    break;

  case 29:
#line 249 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 25
	      SetParameter(CT_CUT_Z,"CUT_Z",(yyvsp[0].realValue),rp_ps);
            }
#line 2031 "readparameters.tab.c"
    break;

  case 30:
#line 254 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 26
	      SetParameter(CT_COEF_TEMP,"COEF_TEMP",(yyvsp[0].realValue),rp_ps);
            }
#line 2040 "readparameters.tab.c"
    break;

  case 31:
#line 259 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 27
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter NFAIL_MAX must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter NFAIL_MAX can not be negative");
	      SetParameter(CT_NFAIL_MAX,"NFAIL_MAX",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2053 "readparameters.tab.c"
    break;

  case 32:
#line 268 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 28
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter DETECT_BIFURCATIONS must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter DETECT_BIFURCATIONS can not be negative");
	      SetParameter(CT_DETECT_BIFURCATIONS,"DETECT_BIFURCATIONS",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2066 "readparameters.tab.c"
    break;

  case 33:
#line 277 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 29
	      if ((yyvsp[0].realValue)<=0)
		Error("Parameter MAX_PLANNING_TIME must positive");

	      SetParameter(CT_MAX_PLANNING_TIME,"MAX_PLANNING_TIME",(yyvsp[0].realValue),rp_ps);
            }
#line 2078 "readparameters.tab.c"
    break;

  case 34:
#line 285 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 30
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter MAX_PLANNING_ITERATIONS must be an integer");	      
	      if ((yyvsp[0].realValue)<1)
		Error("Parameter MAX_PLANNING_ITERATIONS must larger than 0");
	   
	      SetParameter(CT_MAX_PLANNING_ITERATIONS,"MAX_PLANNING_ITERATIONS",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2092 "readparameters.tab.c"
    break;

  case 35:
#line 295 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 31
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter MAX_CHARTS must be an integer");	      
	      if ((yyvsp[0].realValue)<1)
		Error("Parameter MAX_CHARTS must larger than 0");
	      if ((yyvsp[0].realValue)>1000000)
		Error("Parameter MAX_CHARTS must lower than 10000000 (or enlarge the kd-tree)");

	      SetParameter(CT_MAX_CHARTS,"MAX_CHARTS",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2108 "readparameters.tab.c"
    break;

  case 36:
#line 307 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 32
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter MAX_NODES_RRT must be an integer");	     
	      if ((yyvsp[0].realValue)<1)
		Error("Parameter MAX_NODES_RRT must larger than 1");
	      if ((yyvsp[0].realValue)>1000000)
		Error("Parameter MAX_NODES_RRT must lower than 10000000 (or enlarge the kd-tree)");
	   
	      SetParameter(CT_MAX_NODES_RRT,"MAX_NODES_RRT",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2124 "readparameters.tab.c"
    break;

  case 37:
#line 319 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 33
	      SetParameter(CT_BI_RRT,"BI_RRT",(double)((yyvsp[0].realValue)>0),rp_ps);
	    }
#line 2133 "readparameters.tab.c"
    break;

  case 38:
#line 324 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 34
	      SetParameter(CT_RRT_GRAPH,"RRT_GRAPH",(double)((yyvsp[0].realValue)>0),rp_ps);
	    }
#line 2142 "readparameters.tab.c"
    break;

  case 39:
#line 329 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 35
	      SetParameter(CT_DYNAMIC_DOMAIN,"DYNAMIC_DOMAIN",(yyvsp[0].realValue),rp_ps);
	    }
#line 2151 "readparameters.tab.c"
    break;

  case 40:
#line 334 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 36
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter CD_ENGINE must be an integer");
	      SetParameter(CT_CD_ENGINE,"CD_ENGINE",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2162 "readparameters.tab.c"
    break;

  case 41:
#line 341 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 37
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter SAMPLING must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter SAMPLING can not be negative");
	      SetParameter(CT_SAMPLING,"SAMPLING",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2175 "readparameters.tab.c"
    break;

  case 42:
#line 350 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 38
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter PRETENSION must larger than 0");
	      
	      SetParameter(CT_PRETENSION,"PRETENSION",(yyvsp[0].realValue),rp_ps);
            }
#line 2187 "readparameters.tab.c"
    break;

  case 43:
#line 358 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 39
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter DYNAMICS must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter DYNAMICS must larger than 0");
	      SetParameter(CT_DYNAMICS,"DYNAMICS",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2200 "readparameters.tab.c"
    break;

  case 44:
#line 367 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 40
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter INTEGRATION_TIME must larger than 0");
	      
	      SetParameter(CT_INTEGRATION_TIME,"INTEGRATION_TIME",(yyvsp[0].realValue),rp_ps);
            }
#line 2212 "readparameters.tab.c"
    break;

  case 45:
#line 375 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 41
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter DEFAULT_MAX_VELOCITY must larger than 0");
	      
	      SetParameter(CT_DEFAULT_MAX_VELOCITY,"DEFAULT_MAX_VELOCITY",(yyvsp[0].realValue),rp_ps);
            }
#line 2224 "readparameters.tab.c"
    break;

  case 46:
#line 383 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 42
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter N_DYNAMIC_ACTIONS must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter N_DYNAMIC_ACTIONS must larger than 0");
	      
	      SetParameter(CT_N_DYNAMIC_ACTIONS,"N_DYNAMIC_ACTIONS",floor((yyvsp[0].realValue)),rp_ps);
            }
#line 2238 "readparameters.tab.c"
    break;

  case 47:
#line 393 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 43
	      if ((yyvsp[0].realValue)<=0)
		Error("Parameter DYNAMIC_GOAL_ERROR must larger than 0");
	      
	      SetParameter(CT_DYNAMIC_GOAL_ERROR,"DYNAMIC_GOAL_ERROR",(yyvsp[0].realValue),rp_ps);
            }
#line 2250 "readparameters.tab.c"
    break;

  case 48:
#line 401 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 44
	      SetParameter(CT_G_COMPENSATION,"G_COMPENSATION",(double)((yyvsp[0].realValue)>0),rp_ps);
	    }
#line 2259 "readparameters.tab.c"
    break;

  case 49:
#line 406 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 45
	      SetParameter(CT_NEG_LM,"NEG_LM",(double)((yyvsp[0].realValue)>0),rp_ps);
            }
#line 2268 "readparameters.tab.c"
    break;

  case 50:
#line 411 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 46
	      if (fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)
		Error("Parameter G_AXIS  must be an integer");
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter G_AXIS must non-negative (0:x 1:y 2:z 3:-x 4:-y 5:-z)");
	      if ((yyvsp[0].realValue)>6)
		Error("Parameter G_AXIS must lower than 6");
	      
	      SetParameter(CT_G_AXIS,"G_AXIS",(yyvsp[0].realValue),rp_ps);
            }
#line 2284 "readparameters.tab.c"
    break;

  case 51:
#line 423 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 47
	      if ((yyvsp[0].realValue)<=0)
		Error("Parameter TAU must be possitive");
	      
	      SetParameter(CT_TAU,"TAU",(yyvsp[0].realValue),rp_ps);
            }
#line 2296 "readparameters.tab.c"
    break;

  case 52:
#line 431 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
            {
	      // 48
	      if ((yyvsp[0].realValue)<0)
		Error("Parameter LQR_PLANNING_TIME must be possitive");
	      
	      SetParameter(CT_LQR_PLANNING_TIME,"LQR_PLANNING_TIME",(yyvsp[0].realValue),rp_ps);
            }
#line 2308 "readparameters.tab.c"
    break;

  case 53:
#line 441 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 0
       if (ParameterSet(CT_EPSILON,rp_ps))
	 (yyval.realValue)=GetParameter(CT_EPSILON,rp_ps);
       else
	 Error("Undefined parameter in expression (EPSILON)");
     }
#line 2320 "readparameters.tab.c"
    break;

  case 54:
#line 450 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 1
       if (ParameterSet(CT_REPRESENTATION,rp_ps))
	 (yyval.realValue)=GetParameter(CT_REPRESENTATION,rp_ps);
       else
	 Error("Undefined parameter in expression (REPRESENTATION)");
     }
#line 2332 "readparameters.tab.c"
    break;

  case 55:
#line 458 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 2
      if (ParameterSet(CT_RHO,rp_ps))
	(yyval.realValue)=GetParameter(CT_RHO,rp_ps);
      else
	Error("Undefined parameter in expression (RHO)");
    }
#line 2344 "readparameters.tab.c"
    break;

  case 56:
#line 466 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 3
      if (ParameterSet(CT_SIGMA,rp_ps))
	(yyval.realValue)=GetParameter(CT_SIGMA,rp_ps);
      else
	Error("Undefined parameter in expression (SIGMA)");
    }
#line 2356 "readparameters.tab.c"
    break;

  case 57:
#line 474 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 4
      if (ParameterSet(CT_SMALL_SIGMA,rp_ps))
	(yyval.realValue)=GetParameter(CT_SMALL_SIGMA,rp_ps);
      else
	Error("Undefined parameter in expression (SMALL_SIGMA)");
    }
#line 2368 "readparameters.tab.c"
    break;

  case 58:
#line 482 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 5
      if (ParameterSet(CT_E,rp_ps))
	(yyval.realValue)=GetParameter(CT_E,rp_ps);
      else
	Error("Undefined parameter in expression (E)");
    }
#line 2380 "readparameters.tab.c"
    break;

  case 59:
#line 490 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 6
       if (ParameterSet(CT_CE,rp_ps))
	 (yyval.realValue)=GetParameter(CT_CE,rp_ps);
       else
	 Error("Undefined parameter in expression (CE)");
     }
#line 2392 "readparameters.tab.c"
    break;

  case 60:
#line 498 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 7
       if (ParameterSet(CT_R,rp_ps))
	 (yyval.realValue)=GetParameter(CT_R,rp_ps);
       else
	 Error("Undefined parameter in expression (R)");
     }
#line 2404 "readparameters.tab.c"
    break;

  case 61:
#line 506 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 8
       if (ParameterSet(CT_SR,rp_ps))
	 (yyval.realValue)=GetParameter(CT_SR,rp_ps);
       else
	 Error("Undefined parameter in expression (SR)");
     }
#line 2416 "readparameters.tab.c"
    break;

  case 62:
#line 514 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 9
       if (ParameterSet(CT_DELTA,rp_ps))
	 (yyval.realValue)=GetParameter(CT_DELTA,rp_ps);
       else
	 Error("Undefined parameter in expression (DELTA)");
     }
#line 2428 "readparameters.tab.c"
    break;

  case 63:
#line 522 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 10
      if (ParameterSet(CT_ATLASGBF_BETA,rp_ps))
	(yyval.realValue)=GetParameter(CT_ATLASGBF_BETA,rp_ps);
      else
	Error("Undefined parameter in expression (BETA)");
    }
#line 2440 "readparameters.tab.c"
    break;

  case 64:
#line 530 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 11
      if (ParameterSet(CT_STATE_PERIOD,rp_ps))
	(yyval.realValue)=GetParameter(CT_STATE_PERIOD,rp_ps);
      else
	Error("Undefined parameter in expression (STATE_PERIOD)");
    }
#line 2452 "readparameters.tab.c"
    break;

  case 65:
#line 538 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 12
      if (ParameterSet(CT_N_SOLUTIONS,rp_ps))
	(yyval.realValue)=GetParameter(CT_N_SOLUTIONS,rp_ps);
      else
	Error("Undefined parameter in expression (N_SOLUTIONS)");
    }
#line 2464 "readparameters.tab.c"
    break;

  case 66:
#line 546 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 13
      if (ParameterSet(CT_MAX_NEWTON_ITERATIONS,rp_ps))
	(yyval.realValue)=GetParameter(CT_MAX_NEWTON_ITERATIONS,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_NEWTON_ITERATIONS)");
    }
#line 2476 "readparameters.tab.c"
    break;

  case 67:
#line 554 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 14
      if (ParameterSet(CT_N_DOF,rp_ps))
	(yyval.realValue)=GetParameter(CT_N_DOF,rp_ps);
      else
	Error("Undefined parameter in expression (N_DOF)");
    }
#line 2488 "readparameters.tab.c"
    break;

  case 68:
#line 562 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 15
      if (ParameterSet(CT_GAMMA,rp_ps))
	(yyval.realValue)=GetParameter(CT_GAMMA,rp_ps);
      else
	Error("Undefined parameter in expression (GAMMA)");
    }
#line 2500 "readparameters.tab.c"
    break;

  case 69:
#line 570 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 15
      if (ParameterSet(CT_DUMMIFY,rp_ps))
	(yyval.realValue)=GetParameter(CT_DUMMIFY,rp_ps);
      else
	Error("Undefined parameter in expression (DUMMIFY)");
    }
#line 2512 "readparameters.tab.c"
    break;

  case 70:
#line 578 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 17
       if (ParameterSet(CT_SPLIT_TYPE,rp_ps))
	 (yyval.realValue)=GetParameter(CT_SPLIT_TYPE,rp_ps);
       else
	 Error("Undefined parameter in expression (SPLIT_TYPE)");
     }
#line 2524 "readparameters.tab.c"
    break;

  case 71:
#line 586 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 18
      if (ParameterSet(CT_SAFE_SIMPLEX,rp_ps))
	(yyval.realValue)=GetParameter(CT_SAFE_SIMPLEX,rp_ps);
      else
	Error("Undefined parameter in expression (SAFE_SIMPLEX)");
    }
#line 2536 "readparameters.tab.c"
    break;

  case 72:
#line 594 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 19
      if (ParameterSet(CT_SIMPLIFICATION_LEVEL,rp_ps))
	(yyval.realValue)=GetParameter(CT_SIMPLIFICATION_LEVEL,rp_ps);
      else
	Error("Undefined parameter in expression (SIMPLIFICATION_LEVEL)");
    }
#line 2548 "readparameters.tab.c"
    break;

  case 73:
#line 602 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 20
      if (ParameterSet(CT_LR2TM_Q,rp_ps))
	(yyval.realValue)=GetParameter(CT_LR2TM_Q,rp_ps);
      else
	Error("Undefined parameter in expression (LR2TM_Q)");
    }
#line 2560 "readparameters.tab.c"
    break;

  case 74:
#line 610 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 21
      if (ParameterSet(CT_LR2TM_S,rp_ps))
	(yyval.realValue)=GetParameter(CT_LR2TM_S,rp_ps);
      else
	Error("Undefined parameter in expression (LR2TM_S)");
    }
#line 2572 "readparameters.tab.c"
    break;

  case 75:
#line 618 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 22
      if (ParameterSet(CT_VDW_RATIO,rp_ps))
	(yyval.realValue)=GetParameter(CT_VDW_RATIO,rp_ps);
      else
	Error("Undefined parameter in expression (VDW_RATIO)");
    }
#line 2584 "readparameters.tab.c"
    break;

  case 76:
#line 626 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 23
      if (ParameterSet(CT_CUT_X,rp_ps))
	(yyval.realValue)=GetParameter(CT_CUT_X,rp_ps);
      else
	Error("Undefined parameter in expression (CUT_X)");
    }
#line 2596 "readparameters.tab.c"
    break;

  case 77:
#line 634 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 24
      if (ParameterSet(CT_CUT_Y,rp_ps))
	(yyval.realValue)=GetParameter(CT_CUT_Y,rp_ps);
      else
	Error("Undefined parameter in expression (CUT_Y)");
    }
#line 2608 "readparameters.tab.c"
    break;

  case 78:
#line 642 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 25
      if (ParameterSet(CT_CUT_Z,rp_ps))
	(yyval.realValue)=GetParameter(CT_CUT_Z,rp_ps);
      else
	Error("Undefined parameter in expression (CUT_Z)");
    }
#line 2620 "readparameters.tab.c"
    break;

  case 79:
#line 650 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 26
      if (ParameterSet(CT_COEF_TEMP,rp_ps))
	(yyval.realValue)=GetParameter(CT_COEF_TEMP,rp_ps);
      else
	Error("Undefined parameter in expression (COEF_TEMP)");
    }
#line 2632 "readparameters.tab.c"
    break;

  case 80:
#line 658 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 27
      if (ParameterSet(CT_NFAIL_MAX,rp_ps))
	(yyval.realValue)=GetParameter(CT_NFAIL_MAX,rp_ps);
      else
	Error("Undefined parameter in expression (N_FAILS)");
    }
#line 2644 "readparameters.tab.c"
    break;

  case 81:
#line 666 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 28
      if (ParameterSet(CT_DETECT_BIFURCATIONS,rp_ps))
	(yyval.realValue)=GetParameter(CT_DETECT_BIFURCATIONS,rp_ps);
      else
	Error("Undefined parameter in expression (DETECT_BIFURCATIONS)");
    }
#line 2656 "readparameters.tab.c"
    break;

  case 82:
#line 674 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 29
      if (ParameterSet(CT_MAX_PLANNING_TIME,rp_ps))
	(yyval.realValue)=GetParameter(CT_MAX_PLANNING_TIME,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_PLANNING_TIME)");
    }
#line 2668 "readparameters.tab.c"
    break;

  case 83:
#line 682 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 30
      if (ParameterSet(CT_MAX_PLANNING_ITERATIONS,rp_ps))
	(yyval.realValue)=GetParameter(CT_MAX_PLANNING_ITERATIONS,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_PLANNING_ITERATIONS)");
    }
#line 2680 "readparameters.tab.c"
    break;

  case 84:
#line 690 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 31
      if (ParameterSet(CT_MAX_CHARTS,rp_ps))
	(yyval.realValue)=GetParameter(CT_MAX_CHARTS,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_CHARTS)");
    }
#line 2692 "readparameters.tab.c"
    break;

  case 85:
#line 698 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 32
      if (ParameterSet(CT_MAX_NODES_RRT,rp_ps))
	(yyval.realValue)=GetParameter(CT_MAX_NODES_RRT,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_NODES_RRT)");
    }
#line 2704 "readparameters.tab.c"
    break;

  case 86:
#line 706 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 33
       if (ParameterSet(CT_BI_RRT,rp_ps))
	 (yyval.realValue)=GetParameter(CT_BI_RRT,rp_ps);
       else
	 Error("Undefined parameter in expression (BI_RRT)");
     }
#line 2716 "readparameters.tab.c"
    break;

  case 87:
#line 714 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 34
       if (ParameterSet(CT_RRT_GRAPH,rp_ps))
	 (yyval.realValue)=GetParameter(CT_RRT_GRAPH,rp_ps);
       else
	 Error("Undefined parameter in expression (RRT_GRAPH)");
     }
#line 2728 "readparameters.tab.c"
    break;

  case 88:
#line 722 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 35
      if (ParameterSet(CT_DYNAMIC_DOMAIN,rp_ps))
	(yyval.realValue)=GetParameter(CT_DYNAMIC_DOMAIN,rp_ps);
      else
	Error("Undefined parameter in expression (DYNAMIC_DOMAIN)");
    }
#line 2740 "readparameters.tab.c"
    break;

  case 89:
#line 730 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 36
      if (ParameterSet(CT_CD_ENGINE,rp_ps))
	(yyval.realValue)=GetParameter(CT_CD_ENGINE,rp_ps);
      else
	Error("Undefined parameter in expression (CD_ENGINE)");
    }
#line 2752 "readparameters.tab.c"
    break;

  case 90:
#line 738 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 37
      if (ParameterSet(CT_SAMPLING,rp_ps))
	(yyval.realValue)=GetParameter(CT_SAMPLING,rp_ps);
      else
	Error("Undefined parameter in expression (SAMPLING)");
    }
#line 2764 "readparameters.tab.c"
    break;

  case 91:
#line 746 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 38
      if (ParameterSet(CT_PRETENSION,rp_ps))
	(yyval.realValue)=GetParameter(CT_PRETENSION,rp_ps);
      else
	Error("Undefined parameter in expression (PRETENSION)");
    }
#line 2776 "readparameters.tab.c"
    break;

  case 92:
#line 754 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      //  39
      if (ParameterSet(CT_DYNAMICS,rp_ps))
	(yyval.realValue)=GetParameter(CT_DYNAMICS,rp_ps);
      else
	Error("Undefined parameter in expression (DYNAMICS)");
    }
#line 2788 "readparameters.tab.c"
    break;

  case 93:
#line 762 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      //40
      if (ParameterSet(CT_INTEGRATION_TIME,rp_ps))
	(yyval.realValue)=GetParameter(CT_INTEGRATION_TIME,rp_ps);
      else
	Error("Undefined parameter in expression (INTEGRATION_TIME)");
    }
#line 2800 "readparameters.tab.c"
    break;

  case 94:
#line 770 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 41
      if (ParameterSet(CT_DEFAULT_MAX_VELOCITY,rp_ps))
	(yyval.realValue)=GetParameter(CT_DEFAULT_MAX_VELOCITY,rp_ps);
      else
	Error("Undefined parameter in expression (MAX_VELOCITY)");
    }
#line 2812 "readparameters.tab.c"
    break;

  case 95:
#line 778 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 42
      if (ParameterSet(CT_N_DYNAMIC_ACTIONS,rp_ps))
	(yyval.realValue)=GetParameter(CT_N_DYNAMIC_ACTIONS,rp_ps);
      else
	Error("Undefined parameter in expression (N_DYNAMIC_ACTIONS)");
    }
#line 2824 "readparameters.tab.c"
    break;

  case 96:
#line 786 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 43
      if (ParameterSet(CT_DYNAMIC_GOAL_ERROR,rp_ps))
	(yyval.realValue)=GetParameter(CT_DYNAMIC_GOAL_ERROR,rp_ps);
      else
	Error("Undefined parameter in expression (DYNAMIC_GOAL_ERROR)");
    }
#line 2836 "readparameters.tab.c"
    break;

  case 97:
#line 794 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
     {
       // 44
       if (ParameterSet(CT_G_COMPENSATION,rp_ps))
	 (yyval.realValue)=GetParameter(CT_G_COMPENSATION,rp_ps);
       else
	 Error("Undefined parameter in expression (G_COMPENSATION)");
     }
#line 2848 "readparameters.tab.c"
    break;

  case 98:
#line 802 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 45
      if (ParameterSet(CT_NEG_LM,rp_ps))
	(yyval.realValue)=GetParameter(CT_NEG_LM,rp_ps);
      else
	Error("Undefined parameter in expression (NEG_LM)");
    }
#line 2860 "readparameters.tab.c"
    break;

  case 99:
#line 810 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 46
      if (ParameterSet(CT_G_AXIS,rp_ps))
	(yyval.realValue)=GetParameter(CT_G_AXIS,rp_ps);
      else
	Error("Undefined parameter in expression (G_AXIS)");
    }
#line 2872 "readparameters.tab.c"
    break;

  case 100:
#line 818 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 47
      if (ParameterSet(CT_TAU,rp_ps))
	(yyval.realValue)=GetParameter(CT_TAU,rp_ps);
      else
	Error("Undefined parameter in expression (TAU)");
    }
#line 2884 "readparameters.tab.c"
    break;

  case 101:
#line 826 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
    {
      // 48
      if (ParameterSet(CT_LQR_PLANNING_TIME,rp_ps))
	(yyval.realValue)=GetParameter(CT_LQR_PLANNING_TIME,rp_ps);
      else
	Error("Undefined parameter in expression (LQR_PLANNING_TIME)");
    }
#line 2896 "readparameters.tab.c"
    break;

  case 102:
#line 836 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=SOLID;
	     }
#line 2904 "readparameters.tab.c"
    break;

  case 103:
#line 840 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=VCOLLIDE;
	     }
#line 2912 "readparameters.tab.c"
    break;

  case 104:
#line 844 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=PQP;
	     }
#line 2920 "readparameters.tab.c"
    break;

  case 105:
#line 848 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=FCL;
	     }
#line 2928 "readparameters.tab.c"
    break;

  case 106:
#line 852 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=C_FCL;
	     }
#line 2936 "readparameters.tab.c"
    break;

  case 107:
#line 856 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=BULLET;
	     }
#line 2944 "readparameters.tab.c"
    break;

  case 108:
#line 860 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=C_BULLET;
	     }
#line 2952 "readparameters.tab.c"
    break;

  case 109:
#line 864 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=RIGIDCLL;
	     }
#line 2960 "readparameters.tab.c"
    break;

  case 110:
#line 868 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=NOCD;
	     }
#line 2968 "readparameters.tab.c"
    break;

  case 111:
#line 874 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
                {
		  (yyval.realValue)=TANGENT_SAMPLING;
		}
#line 2976 "readparameters.tab.c"
    break;

  case 112:
#line 878 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
                {
		  (yyval.realValue)=AMBIENT_SAMPLING;
		}
#line 2984 "readparameters.tab.c"
    break;

  case 113:
#line 882 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
                {
		  #if (_KDTREE!=1)
		    Error("KDTREE_SAMPLING can only be used if the cuik-kdtree library is available");
		  #endif
		  (yyval.realValue)=KDTREE_SAMPLING;
		}
#line 2995 "readparameters.tab.c"
    break;

  case 114:
#line 891 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
         {
	   (yyval.realValue)=REP_LINKS;
	 }
#line 3003 "readparameters.tab.c"
    break;

  case 115:
#line 895 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
         {
	   (yyval.realValue)=REP_FLINKS;
	 }
#line 3011 "readparameters.tab.c"
    break;

  case 116:
#line 899 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
         {
	   (yyval.realValue)=REP_QLINKS;
	 }
#line 3019 "readparameters.tab.c"
    break;

  case 117:
#line 903 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
         {
	   (yyval.realValue)=REP_JOINTS;
	 }
#line 3027 "readparameters.tab.c"
    break;

  case 118:
#line 909 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=0;
	     }
#line 3035 "readparameters.tab.c"
    break;

  case 119:
#line 913 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=1;
	     }
#line 3043 "readparameters.tab.c"
    break;

  case 120:
#line 917 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=2;
	     }
#line 3051 "readparameters.tab.c"
    break;

  case 121:
#line 921 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=3;
	     }
#line 3059 "readparameters.tab.c"
    break;

  case 122:
#line 925 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=4;
	     }
#line 3067 "readparameters.tab.c"
    break;

  case 123:
#line 929 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=5;
	     }
#line 3075 "readparameters.tab.c"
    break;

  case 124:
#line 933 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
             {
	       (yyval.realValue)=(yyvsp[0].realValue);
	     }
#line 3083 "readparameters.tab.c"
    break;

  case 125:
#line 939 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
              {
		(yyval.realValue)=(yyvsp[0].realValue);
	      }
#line 3091 "readparameters.tab.c"
    break;

  case 126:
#line 943 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
              {
		(yyval.realValue)=((yyvsp[-1].realValue)<0?4:1);
	      }
#line 3099 "readparameters.tab.c"
    break;

  case 127:
#line 947 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
              {
		(yyval.realValue)=((yyvsp[-1].realValue)<0?5:2);
	      }
#line 3107 "readparameters.tab.c"
    break;

  case 128:
#line 951 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
              {
		(yyval.realValue)=((yyvsp[-1].realValue)<0?6:3);
	      }
#line 3115 "readparameters.tab.c"
    break;

  case 129:
#line 957 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
           {
	     (yyval.realValue)=+1.0;
	   }
#line 3123 "readparameters.tab.c"
    break;

  case 130:
#line 961 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
           {
	     (yyval.realValue)=-1.0;
	   }
#line 3131 "readparameters.tab.c"
    break;

  case 131:
#line 965 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
           {
	     (yyval.realValue)=+1.0;
	   }
#line 3139 "readparameters.tab.c"
    break;

  case 132:
#line 971 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[0].realValue);
       }
#line 3147 "readparameters.tab.c"
    break;

  case 133:
#line 975 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[0].realValue);
       }
#line 3155 "readparameters.tab.c"
    break;

  case 134:
#line 979 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=M_PI;
       }
#line 3163 "readparameters.tab.c"
    break;

  case 135:
#line 983 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=INF;
       }
#line 3171 "readparameters.tab.c"
    break;

  case 136:
#line 987 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[0].realValue);
       }
#line 3179 "readparameters.tab.c"
    break;

  case 137:
#line 991 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[0].realValue);
       }
#line 3187 "readparameters.tab.c"
    break;

  case 138:
#line 995 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[0].realValue);
       }
#line 3195 "readparameters.tab.c"
    break;

  case 139:
#line 999 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=-(yyvsp[0].realValue);
       }
#line 3203 "readparameters.tab.c"
    break;

  case 140:
#line 1003 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[-1].realValue);
       }
#line 3211 "readparameters.tab.c"
    break;

  case 141:
#line 1007 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 if ((yyvsp[-5].realValue)>0)
	   (yyval.realValue)=(yyvsp[-3].realValue);
	 else
	   (yyval.realValue)=(yyvsp[-1].realValue);
       }
#line 3222 "readparameters.tab.c"
    break;

  case 142:
#line 1014 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[-2].realValue)+(yyvsp[0].realValue);
       }
#line 3230 "readparameters.tab.c"
    break;

  case 143:
#line 1018 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 (yyval.realValue)=(yyvsp[-2].realValue)-(yyvsp[0].realValue);
       }
#line 3238 "readparameters.tab.c"
    break;

  case 144:
#line 1022 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[-2].realValue)*(yyvsp[0].realValue);
       }
#line 3246 "readparameters.tab.c"
    break;

  case 145:
#line 1026 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=pow((yyvsp[-2].realValue),(yyvsp[0].realValue));
       }
#line 3254 "readparameters.tab.c"
    break;

  case 146:
#line 1030 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=(yyvsp[-2].realValue)/(yyvsp[0].realValue);
       }
#line 3262 "readparameters.tab.c"
    break;

  case 147:
#line 1034 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=cos((yyvsp[-1].realValue));
       }
#line 3270 "readparameters.tab.c"
    break;

  case 148:
#line 1038 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=sin((yyvsp[-1].realValue));
       }
#line 3278 "readparameters.tab.c"
    break;

  case 149:
#line 1042 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=tan((yyvsp[-1].realValue));
       }
#line 3286 "readparameters.tab.c"
    break;

  case 150:
#line 1046 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=exp((yyvsp[-1].realValue));
       }
#line 3294 "readparameters.tab.c"
    break;

  case 151:
#line 1050 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=log((yyvsp[-1].realValue));
       }
#line 3302 "readparameters.tab.c"
    break;

  case 152:
#line 1054 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 (yyval.realValue)=sqrt((yyvsp[-1].realValue));
       }
#line 3310 "readparameters.tab.c"
    break;

  case 153:
#line 1058 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 if ((fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)||((yyvsp[0].realValue)<0)||((yyvsp[0].realValue)>1))
	   Error("Boolean operation on a non-logical expresion");
	 (yyval.realValue)=!(((yyvsp[0].realValue))>0);
       }
#line 3320 "readparameters.tab.c"
    break;

  case 154:
#line 1064 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 if ((fabs((yyvsp[-2].realValue)-floor((yyvsp[-2].realValue)))>1e-10)||((yyvsp[-2].realValue)<0)||((yyvsp[-2].realValue)>1))
	   Error("Boolean operation on a non-logical expresion");	 
	 if ((fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)||((yyvsp[0].realValue)<0)||((yyvsp[0].realValue)>1))
	   Error("Boolean operation on a non-logical expresion");
	 
	 (yyval.realValue)=((((yyvsp[-2].realValue))>0)&&(((yyvsp[0].realValue))>0));
       }
#line 3333 "readparameters.tab.c"
    break;

  case 155:
#line 1073 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       {
	 if ((fabs((yyvsp[-2].realValue)-floor((yyvsp[-2].realValue)))>1e-10)||((yyvsp[-2].realValue)<0)||((yyvsp[-2].realValue)>1))
	   Error("Boolean operation on a non-logical expresion");	 
	 if ((fabs((yyvsp[0].realValue)-floor((yyvsp[0].realValue)))>1e-10)||((yyvsp[0].realValue)<0)||((yyvsp[0].realValue)>1))
	   Error("Boolean operation on a non-logical expresion");
	 
	 (yyval.realValue)=((((yyvsp[-2].realValue))>0)||(((yyvsp[0].realValue))>0));
       }
#line 3346 "readparameters.tab.c"
    break;

  case 156:
#line 1082 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 (yyval.realValue)=(((yyvsp[-2].realValue))<((yyvsp[0].realValue)));
       }
#line 3354 "readparameters.tab.c"
    break;

  case 157:
#line 1086 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 (yyval.realValue)=(((yyvsp[-2].realValue))>((yyvsp[0].realValue)));
       }
#line 3362 "readparameters.tab.c"
    break;

  case 158:
#line 1090 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 (yyval.realValue)=(((yyvsp[-2].realValue))<=((yyvsp[0].realValue)));
       }
#line 3370 "readparameters.tab.c"
    break;

  case 159:
#line 1094 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 (yyval.realValue)=(((yyvsp[-2].realValue))>=((yyvsp[0].realValue)));
       }
#line 3378 "readparameters.tab.c"
    break;

  case 160:
#line 1098 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
       { 
	 (yyval.realValue)=(((yyvsp[-2].realValue))==((yyvsp[0].realValue)));
       }
#line 3386 "readparameters.tab.c"
    break;

  case 161:
#line 1104 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
                {
	          (yyval.realValue)=1.0;
                }
#line 3394 "readparameters.tab.c"
    break;

  case 162:
#line 1108 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"
                {
	          (yyval.realValue)=0.0;
                }
#line 3402 "readparameters.tab.c"
    break;


#line 3406 "readparameters.tab.c"

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
#line 1113 "/home/logan/Downloads/CuikSuite3/src/CuikBase/readparameters.y"

/** \endcond */
boolean ReadParameters(char *file,Tparameters *p)
{
  unsigned int i;
  boolean fileExists;

  ReadParametersin=fopen(file,"r");
  if (!ReadParametersin) 
    fileExists=FALSE;
  else
    {
      fileExists=TRUE;
    
      /*Set up the global pointer to make the parameter structure under initialization
	to be accesible form everywhere in the parser*/
      rp_ps=p;
  
      /*Reset the lines numbering*/
      RPNline=1;

      /*and process the file*/
      ReadParametersparse();

      for(i=0;i<NPARAMETERS;i++)
	{
	  if ((*p)[i].name==NULL)
	    {
	      char ErrorText[200];
	      
	      sprintf(ErrorText,"Parameter number %u is undefined (see sources/parameters.h to see parameter numbering)",i);
	      Error(ErrorText);
	    }
	}

      if (GetParameter(CT_SMALL_SIGMA,p)>GetParameter(CT_SIGMA,p))
	Error("SMALL_SIGMA can not be larger than SIGMA");

      if (GetParameter(CT_EPSILON,p)>GetParameter(CT_SIGMA,p))
	Error("EPSILON can not be larger than SIGMA");

      if (GetParameter(CT_DELTA,p)>=GetParameter(CT_R,p))
	Error("DELTA can not be larger than R");

      fclose(ReadParametersin);
    }

  return(fileExists);
} 
