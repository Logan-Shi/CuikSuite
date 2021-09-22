#ifndef DEFINESH
#define DEFINESH

#include "error.h" /*The NEW macros call error()*/
#include <stdlib.h> /*The NEW macros call malloc,..*/
#include <fenv.h> /*FPU control*/

/** 
   \file defines.h 

   \brief Definitions of constants and macros used in several parts of the cuik library.

   Definitions of constants and macros used in several parts of the cuik library.

   \sa geom.h
*/

/************************************************************************************/
/************************************************************************************/
/** 
   \brief Floating point operations giving a value below this constant (in absolute value)
   are considered 0.

   Floating point operations giving a value below this constant (in absolute value)
   are considered 0. 

   We use 1e-11 because trigonometric operations (sin/cos/...) give an error typically
   around 1e-12. Moreover, we print doubles with 12 decimals and, thus the last one
   typically varies when performing operations. Note that 1e-11 is far below the typical
   precission used inside the simplex algorithms (1e-6).

   No to be confused with parameter \e EPSILON. ZERO is used as a general
   threshold to round towards 0 and Epsilon is used only when passing parameters
   to the simplex. For a super-numerically-stable simplex \e EPSILON and ZERO
   would be the same.
*/
#define ZERO 1e-11

/** 
   \brief If 0 we avoid any randomness in the cuiksuite behavior.

    If set to 0 we avoid any randomness in the cuiksuite behavior. This is
    basically used for debug. In norma mode, the applications in the cuiksuite
    rely on some randomness (to select the variable to split a box, to select
    the split point,...). This is usefull to improve the performance in 
    degenerate situations and it does not hinder the convergence in the
    usual cases.
    For debug purposes, though, this randomness can be quite annoying and can
    be deactivated here.

    Right now we only use random behavior when in optimized mode.

    \todo Remove this in the final version. This is for debug only
*/
#define RANDOMNESS (_DEBUG<2)

/************************************************************************************/
/************************************************************************************/
    
/** \def INF 
    \brief Infinite.
    
    Infinite.
*/
#if (_SIMPLEX_ENGINE==_CLP)
  #include <coin/Coin_C_defines.h>
  #include <float.h>

  #ifndef COIN_DBL_MAX
    #define INF DBL_MAX
  #else
    #define INF COIN_DBL_MAX
  #endif
#else
  #define INF 1e10
#endif

#ifndef M_PI
  /** \brief Pi.

      Pi
  */
  #define M_PI 3.14159265358979323846
#endif


#ifndef M_PI_2
  /** \brief Pi/2.

      Pi/2
  */
  #define M_PI_2 1.57079632679489661923
#endif

#ifndef M_2PI
  /** \brief 2*Pi.

      2*Pi
  */
  #define M_2PI (2.0*M_PI)
#endif

#ifndef M_E
  /** \brief e.

      Base of the natural log.
  */
  #define M_E 2.718281828459045
#endif

#ifndef M_C
  /** 
      \brief Speed of light in meter per second.
  */
  #define M_C 299792458
#endif

#ifndef M_G
  /** 
      \brief Gravity acceleration.
  */
  #define M_G 9.80665 
#endif

/************************************************************************************/
/************************************************************************************/

/** \brief One of the possible topologies.
    
    The range of the variables is defined over the reals.
*/
#define TOPOLOGY_R 1

/** \brief One of the possible topologies.
    
    The range of the variables is defined over a circle.

    IMPORTANT: Only variables with range equal (or larger) than 2*pi
    are actually considered to have TOPOLOGY_S. Variables defined
    with TOPOLOGY_S but with small ranges are actually treated
    as varaibles with TOPOLOGY_R.

    If a variable x has TOPOLOGY_S it means that we can replace
    this variable by x+k*2*pi (k any integer) and the system
    of equations remains the same. 
    If a variable is defined with TOPOLOGY_S but it does not
    fulfills the above condition an error is likely to occur.
*/
#define TOPOLOGY_S 2

/************************************************************************************/
/************************************************************************************/
/** 
   \brief Maximum number of nested included files.

   A maximum of recursively included files to avoid infinite loops.
*/
#define MAX_INCLUDES 100

/************************************************************************************/
/************************************************************************************/
/** 
   \brief Swaps two values.

   Swaps two values using an intermediate storage.

   \param a First value to swap.
   \param b Second value to swap.
   \param c Intermediate storage for the swap.
*/
#define SWAP(a,b,c) {c=a;a=b;b=c;}

/************************************************************************************/
/************************************************************************************/
/** \brief Constant to transform from degrees to radiants.

    Constant to transform from degrees to radiants.
*/
#define DEG2RAD (M_PI/180.0)

/** \brief Constant to transform from radiants to degrees.

    Constant to transform from radiants to degrees.
*/
#define RAD2DEG (180.0/M_PI)

/************************************************************************************/
/************************************************************************************/
/** \brief Returns the sign of a floating point.

     Returns the sign of a floating point: -1 for negative and 1 for possitive or zero.

     \param a The number to operate.
*/
#define SGN(a) (a>=0?1:-1)

/************************************************************************************/
/************************************************************************************/
/** \brief Adjust a real to 0,1,-1, if possible.

    Adjust a real to 0,1,-1, if possible.

    \param a The number to adjust.
*/
#define ADJUST_REAL(a) (fabs(a)<ZERO?0.0:(fabs(a-1.0)<ZERO?+1.0:(fabs(a+1.0)<ZERO?-1.0:a)))

/************************************************************************************/
/************************************************************************************/
/** \brief Forces an angle go be in [-pi,pi].

    Forces an angle go be in [-pi,pi].
    This is intended to be used with a variable as a parameter
    (using an expression would be ineficient).
*/
#define PI2PI(a) {if ((a<-M_PI-ZERO)||(a>M_PI+ZERO)) {a=fmod(a,M_2PI); while(a>M_PI) a-=M_2PI; while (a<-M_PI) a+=M_2PI;}}

/************************************************************************************/
/************************************************************************************/
/** \brief Sets the floating point operations in rounding up mode.

    Sets the floating point operations in rounding up mode.
*/
#define ROUNDUP   fesetround(FE_UPWARD)

/** \brief Sets the floating point operations in rounding down mode.

    Sets the floating point operations in rounding down mode.
*/
#define ROUNDDOWN fesetround(FE_DOWNWARD) 

/** \brief Sets the floating point operations in round near mode.

    Sets the floating point operations in round near mode. This is the default mode.
*/
#define ROUNDNEAR fesetround(FE_TONEAREST)

/************************************************************************************/
/************************************************************************************/

/** 
   \brief Sets a number, without going beyond +/-inf.

   Sets a number, without going beyond +/-inf..

   \param a The number to check.
*/
#define INF_CUT(a) ((a<=-INF?-INF:(a>=INF)?INF:a))

/** 
   \brief Identifies +/-inf.

   TRUE if the number is either inf or -inf.

   \param a The number to check.
*/
#define IS_INF(a) ((a==-INF)||(a==INF))

/** 
   \brief Identifies not +/-inf.

   TRUE if the number is not inf or -inf.

   \param a The number to check.
*/
#define IS_NOT_INF(a) ((a!=-INF)&&(a!=INF))

/** 
   \brief Scales a number, possibly inf or -inf.

    Scales a number, possibly inf or -inf.

    \sa  INF_PROD if 's' can be inf also.

    \param s The scale factor (this is not +/-inf).
    \param a The number to scale.
*/
#define INF_SCALE(s,a) (IS_INF(a)?(s<0?-a:a):(s*a))

/** 
   \brief Exponentional of a number, possibly inf or -inf.

    Exponentional of a number, possibly inf or -inf.

    \param a The number to operate.
*/
#define INF_EXP(a) ((a==-INF)?0:((a==INF)?INF:exp(a)))

/** 
   \brief Product of two numbers, possibly inf or -inf.

   Product of two numbers, possibly inf or -inf.

   When rounding down, INF*(-INF)  is set to -INF, otherwise to INF.

   \param a The first number to operate.
   \param b The second number to operate.
   \param d TRUE if rounding down.
*/
#define INF_PROD(a,b,d) (IS_NOT_INF(a)&&IS_NOT_INF(b)?(a*b):(IS_INF(a)&&IS_INF(b)?(a==b?a:(d?-INF:INF)):(IS_INF(a)?(b>ZERO?a:(b<-ZERO?-a:0.0)):(a>ZERO?b:(a<-ZERO?-b:0.0)))))

/** 
   \brief Adds two numbers, possibly inf or -inf.

   Adds two numbers, possibly inf or -inf.

   When rounding down, INF+(-INF)  is set to -INF, otherwise to INF.

   \param a The first number to operate.
   \param b The second number to operate.
   \param d TRUE if rounding down.
*/
#define INF_ADD(a,b,d) (IS_NOT_INF(a)&&IS_NOT_INF(b)?(a+b):(IS_INF(a)&&IS_INF(b)?(a==b?a:(d?-INF:INF)):(IS_INF(a)?a:b)))

/** 
   \brief Substract two numbers, possibly inf or -inf.

   Substract two numbers, possibly inf or -inf.

   When rounding down, INF-INF  is set to -INF, otherwise to INF.

   \param a The first number to operate.
   \param b The second number to operate.
   \param d TRUE if rounding down.
*/
#define INF_SUBS(a,b,d) (IS_NOT_INF(a)&&IS_NOT_INF(b)?(a-b):(IS_INF(a)&&IS_INF(b)?(a==b?(d?-INF:INF):a):(IS_INF(a)?a:-b)))

/** 
   \brief Power of a number, possibly +/-inf.

   Power of a number, possibly +/-inf.

   \param a The number to operate.
   \param p The power (integer possitive).
*/
#define INF_POW(a,p) (IS_NOT_INF(a)?pow(a,(double)p):((a==-INF)?(((p%2)==0)?INF:-INF):INF))

/** 
   \brief Sqrt of a number, possibly +/-inf.

   Sqrt of a number, possibly +/-inf.

   \param a The number to operate.
*/
#define INF_SQRT(a) ((a==INF)?INF:(a<0.0?0.0:sqrt(a)));

/** 
   \brief Prints a number (possibly +/-inf) to a file.

   Prints a number (possibly +/-inf) to a file.
   
   \param f The file.
   \param a The number.
*/
#define INF_PRINT(f,a) (a==INF?fprintf(f,"inf"):(a==-INF?fprintf(f,"-inf"):fprintf(f,"%.12g",a)))

/** 
   \brief Accuracy for the rounding to +/-PI, +/-PI/2.

   Accuracy used when rounding values to +/-PI and +/-PI/2
*/
#define ANGLE_ACCURACY 1e-4

/** 
   \brief Round to +/-PI, +/-PI/2.

   When reading values from equation files, we round them to +/-PI or to +/-PI/2 to gain accuracy.
   The rounding is only applied for variables that are known to be angles.
   
   \param a The angular value to round.
*/
#define ROUND2SYMBOL(a) (fabs((a)+M_PI)<ANGLE_ACCURACY?-M_PI:(fabs((a)-M_PI)<ANGLE_ACCURACY?M_PI:(fabs((a)+M_PI_2)<ANGLE_ACCURACY?-M_PI_2:(fabs((a)-M_PI_2)<ANGLE_ACCURACY?M_PI_2:a))))

/** 
   \brief Prints a number (possibly +/-PI, +/-PI/2, or +/-inf) to a file.

   Prints a number (possibly +/-PI, +/-PI/2, or +/-inf) to a file.
   Numbers close (up to 1e-4 to +/-PI or +/-PI/2 are printed symbolically). This increases accuracy when
   reading these values.

   This type of printing is only used for variables that are known to be angles.
   
   \param f The file.
   \param a The angular value to print.
*/
#define SYMBOL_PRINT(f,a) (fabs((a)+M_PI)<ANGLE_ACCURACY?fprintf(f,"-PI"):(fabs((a)-M_PI)<ANGLE_ACCURACY?fprintf(f,"PI"):(fabs((a)+M_PI_2)<ANGLE_ACCURACY?fprintf(f,"-PI/2"):(fabs((a)-M_PI_2)<ANGLE_ACCURACY?fprintf(f,"PI/2"):INF_PRINT(f,a)))))

/************************************************************************************/
/************************************************************************************/
/** \brief Allocates memory space.

    Allocates memory space for \e _n elements of type \e _type and assigns the pointer to \e _var.
    If the memory can not be allocated, triggers an error.
*/
#define NEW(_var,_n,_type) {(_var)=(_type *)malloc(sizeof(_type)*(_n)); \
                            if (!(_var)) Error("Memory allocation error");}

/** \brief Allocates and cleans memory space.

    Allocates memory space for \e _n elements of type \e _type and assigns the pointer to \e _var
    and initializes the space to zero.
    If the memory can not be allocated, triggers an error.
*/
#define NEWZ(_var,_n,_type) {(_var)=(_type *)calloc(_n,sizeof(_type)); \
                             if (!(_var)) Error("Memory allocation error");}

/** \brief Expands a previously allocated memory space.

    Expands a previously reserved memory space
    so that it can accomodate \e _n elements of type \e _type  assigns the pointer to \e _var.
    The previously allocated space is pointed by \e _var.
    If the memory can not be expanded, triggers an error.
*/
#define MEM_EXPAND(_var,_n,_type) {(_var)=(_type *)realloc((void *)(_var),sizeof(_type)*(_n)); \
                                   if (!(_var)) Error("Memory reallocation error");}
/** \brief Duplicates a previously allocated memory space.

    Dublicates a previously reserved memory space
    that accomodates \e _n elements of type \e _type.
    After the \e duplication, the pointer \e _var takes to a memory space
    that can accomodate 2*\e _n elements and the value of variable \e _n 
    is also doubled.
*/
#define MEM_DUP(_var,_n,_type) {(_n)*=2;MEM_EXPAND(_var,_n,_type);}

/************************************************************************************/
/************************************************************************************/
/** \brief Prints a variable name into a file.

    Automatically generated variables have a name that starts with a '_'. This is done
    to avoid the generation of a variable with the same name of a variable defined by
    the user (the syntax does not allow for variables starting with a '_').<br>
    When printing the name of the variable into a file we remove the starting '_' to
    allow the input parser to read the output file. If this results in a duplicated
    variable the parser will detect it.
*/
#define PRINT_VARIABLE_NAME(f,name) if (name[0]=='_') fprintf(f,"%s",&(name[1])); else  fprintf(f,"%s",name)

/************************************************************************************/
/************************************************************************************/
/** \brief Used to denote an identifier that has not been initialized.

    Used to denote an identifier that has not been initialized.
*/
#define NO_UINT ((unsigned int)(-1))

/************************************************************************************/
/************************************************************************************/

/** \brief Weight of new data when computing moving averages.

    Weight used for the new data when computing moving averages. In particular this
    constant gives the weight when increasing the average.

    This is typically used to self-tune parameters.

    This value must be between 0 and 1. If 0 the new data is not taken into account.
    If 1 only the new data is used (forgetting the previous one). A standard
    value for this parameter is in the range [0.01, 0.1].
*/
#define MOV_AVG_UP 0.1

/************************************************************************************/
/************************************************************************************/

/** \brief Weight of new data when computing moving averages.

    Weight used for the new data when computing moving averages. In particular this
    constant gives the weight when decreasing the average.

    This is typically used to self-tune parameters.

    This value must be between 0 and 1. If 0 the new data is not taken into account.
    If 1 only the new data is used (forgetting the previous one). A standard
    value for this parameter is in the range [0.01, 0.1].
*/
#define MOV_AVG_DOWN 0.1


#endif
