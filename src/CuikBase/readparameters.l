%{ 
/*
* Lexical analizer for parameter files
*/

/** \cond */

#include <stdlib.h> 
#include <string.h>

#include "defines.h"
#include "readparameters.tab.h"

int ReadParameterslex(void);

extern unsigned int RPNline; /*current line number (declared in the YACC module and updated here)*/

/** \endcond */

%} 
 
%s IN_COMMENT

EMPTY                           [ \t]+ 
RETURN                          \n
DIGIT                           [0-9] 
LETTER                          [a-zA-Z] 
R_NUMBER                        (({DIGIT}+(\.{DIGIT}+)?)|(\.{DIGIT}+))((E|e)[+-]?{DIGIT}+)? 
I_NUMBER                        {DIGIT}+ 
IDENTIFIER                      {LETTER}({DIGIT}|{LETTER}|"_")* 
COMMENT                         \%[^\n]*
COMMENT2                        \#[^{\n|\{}]* 
COMMENT3                        \/\/[^{\n|\r\n|\{}]*
 
%%

{COMMENT}                       { }   
{COMMENT2}                      { }  
{COMMENT3}                      { }  

<INITIAL>{
  "/*"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
  "*/"      BEGIN(INITIAL);
  [^*\n]+   // eat comment in chunks
  "*"       // eat the lone star
  \n        RPNline++;
}

{EMPTY}                         { } 

{RETURN}                        { RPNline++; } 

TRUE                            { return(_TRUE);}
FALSE                           { return(_FALSE);}

ON                              { return(_TRUE);}
OFF                             { return(_FALSE);}

OR                              { return(_OR); }
AND                             { return(_AND); }
NOT                             { return(_NOT); }

'>='                            { return(_GEQ); }
'<='                            { return(_LEQ); }
'=='                            { return(_EQU); }

PI                              { return(_PI);}
COS                             { return(_COS); }
SIN                             { return(_SIN); }
TAN                             { return(_TAN); }
EXP                             { return(_EXP); }
LOG                             { return(_LOG); }
SQRT                            { return(_SQRT); }

LINKS                           { return(_LINKS); }
FLINKS                          { return(_FLINKS); }
QLINKS                          { return(_QLINKS); } 
JOINTS                          { return(_JOINTS); }

SOLID                           { return(_SOLID); }
VCOLLIDE                        { return(_VCOLLIDE); }
PQP                             { return(_PQP); }
FCL                             { return(_FCL); }
C_FCL                           { return(_C_FCL); }
BULLET                          { return(_BULLET); }
C_BULLET                        { return(_C_BULLET); }
RIGIDCLL                        { return(_RIGIDCLL); }
NONE                            { return(_NONE); }

INF                             { return(_INF); }

EPSILON                         { return(_EPSILON); }

REPRESENTATION                  { return(_REPRESENTATION); }

RHO                             { return(_RHO); }

SIGMA                           { return(_SIGMA); }
SMALL_SIGMA                     { return(_SMALL_SIGMA); }

R                               { return(_R); }
SR                              { return(_SR); }
E                               { return(_E); }
CE                              { return(_CE); }
DELTA                           { return(_DELTA); }
BETA                            { return(_BETA); }

STATE_PERIOD                    { return(_STATE_PERIOD); }

N_SOLUTIONS                     { return(_N_SOLUTIONS); }
MAX_NEWTON_ITERATIONS           { return(_MAX_NEWTON_ITERATIONS); }
N_DOF                           { return(_N_DOF); }
GAMMA                           { return(_GAMMA); }

DUMMIFY                         { return(_DUMMIFY); }
SPLIT_TYPE                      { return(_SPLIT_TYPE); }
ERROR_SPLIT                     { return(_SPLIT_TYPE); }  
SAFE_SIMPLEX                    { return(_SAFE_SIMPLEX); }
SIMPLIFICATION_LEVEL            { return(_SIMPLIFICATION_LEVEL); }
LR2TM_Q                         { return(_LR2TM_Q); }
LR2TM_S                         { return(_LR2TM_S); }

VDW_RATIO                       { return(_VDW_RATIO); }

CUT_X                           { return(_CUT_X); }
CUT_Y                           { return(_CUT_Y); }
CUT_Z                           { return(_CUT_Z); }
COEF_TEMP                       { return(_COEF_TEMP); }
NFAIL_MAX                       { return(_NFAIL_MAX); }

DETECT_BIFURCATIONS             { return(_DETECT_BIFURCATIONS); }

MAX_PLANNING_TIME               { return(_MAX_PLANNING_TIME); }
MAX_PLANNING_ITERATIONS         { return(_MAX_PLANNING_ITERATIONS); }
MAX_CHARTS                      { return(_MAX_CHARTS); }
MAX_NODES_RRT                   { return(_MAX_NODES_RRT); }
BI_RRT                          { return(_BI_RRT); }
RRT_GRAPH                       { return(_RRT_GRAPH); }
DYNAMIC_DOMAIN                  { return(_DYNAMIC_DOMAIN); }
CD_ENGINE                       { return(_CD_ENGINE); }

TANGENT_SAMPLING                { return(_TANGENT_SAMPLING); }
AMBIENT_SAMPLING                { return(_AMBIENT_SAMPLING); }
KDTREE_SAMPLING                 { return(_KDTREE_SAMPLING); }

SAMPLING                        { return(_SAMPLING); }

PRETENSION                      { return(_PRETENSION); }

DYNAMICS                        { return(_DYNAMICS); }
LOCAL_TRAPEZOID                 { return(_L_TRAPEZOID); }
LOCAL_EULER                     { return(_L_EULER); }
LOCAL_RK4                       { return(_L_RK4); }
EULER                           { return(_EULER); }
RK4                             { return(_RK4); }

INTEGRATION_TIME                { return(_INTEGRATION_TIME); }
DEFAULT_MAX_VELOCITY            { return(_DEFAULT_MAX_VELOCITY); }
N_DYNAMIC_ACTIONS               { return(_N_DYNAMIC_ACTIONS); }
DYNAMIC_GOAL_ERROR              { return(_DYNAMIC_GOAL_ERROR); }
G_COMPENSATION                  { return(_G_COMPENSATION); }
NEG_LM                          { return(_NEG_LM); }
G_AXIS                          { return(_G_AXIS); }
X                               { return(_X); }
Y                               { return(_Y); }
Z                               { return(_Z); }
TAU                             { return(_TAU); }
LQR_PLANNING_TIME               { return(_LQR_PLANNING_TIME); }

{I_NUMBER}                      {
				  char string_tmp[100];
				  
				  memcpy(string_tmp,ReadParameterstext,(unsigned int)ReadParametersleng);
				  string_tmp[ReadParametersleng]=0;
				  ReadParameterslval.realValue=(double)atoi(string_tmp);
				  return(_INTEGER); 
				} 
 
{R_NUMBER}                      { 
				  char string_tmp[100];
				  
				  memcpy(string_tmp,ReadParameterstext,(unsigned int)ReadParametersleng);
				  string_tmp[ReadParametersleng]=0;
				  ReadParameterslval.realValue=atof(string_tmp);
				  
				  return(_REAL);
				}
 
.                               { return(ReadParameterstext[0]); }
 
%%

/**
  \brief Function called at the end of the parsing process.

  This function is automatically called by the parser at the end of a file.
  If 1 is returned the lexical analysis is stopped.
 
  \return 1 to stop the parsing. 
*/
int ReadParameterswrap()
{
  return(1);
}
   
