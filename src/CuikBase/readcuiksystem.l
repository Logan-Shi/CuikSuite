%{ 
/*
* Lexical analizer for the function that initilizes a set of equations from a file
*/

/** \cond */

#include <stdlib.h> 
#include <string.h>

#include "defines.h" 
#include "error.h"
#include "readcuiksystemtypes.h" 
#include "readcuiksystem.tab.h" 

int Readcuiksystemlex(void);

extern unsigned int RCSline;

%}
%s IN_COMMENT

EMPTY                           [ \t]+ 
RETURN                          [\n|\r\n]
DIGIT                           [0-9] 
LETTER                          [a-zA-Z] 
R_NUMBER                        (({DIGIT}+(\.{DIGIT}+)?)|(\.{DIGIT}+))((E|e)[+-]?{DIGIT}+)? 
I_NUMBER                        {DIGIT}+
IDENTIFIER                      {LETTER}({DIGIT}|{LETTER}|"_")* 
COMMENT                         \%[^{\n|\r\n|\{}]*
COMMENT2                        \#[^{\n|\r\n|\{}]*
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
  \n        RCSline++;
}

{EMPTY}                         { } 

{RETURN}                        { RCSline++; } 

"[CONSTANTS]"                   {
                                  return(_CONSTANTS);
                                }

"[SYSTEM VARS]"                 {
                                  return(_SYSTEM_VARS);
                                }

"[SECONDARY VARS]"              {
                                  return(_SECONDARY_VARS);
                                }

"[DUMMY VARS]"                  {
                                  return(_DUMMY_VARS);
                                }

"[CARTESIAN VARS]"              {
                                  return(_CARTESIAN_VARS);
                                }

"[VELOCITY VARS]"               {
                                  return(_VELOCITY_VARS);
                                }

"[NON DYNAMIC VARS]"            {
                                  return(_NON_DYNAMIC_VARS);
                                }

"[SYSTEM EQS]"                  {
                                  return(_SYSTEM_EQS);
                                }

"[COORD EQS]"                   {
                                  return(_COORD_EQS);
                                }

"[DUMMY EQS]"                   {
                                  return(_DUMMY_EQS);
                                }

"[VELOCITY EQS]"                {
                                  return(_VELOCITY_EQS);
                                }

"[NON DYNAMIC EQS]"             {
                                  return(_NON_DYNAMIC_EQS);
                                }

"[SEARCH]"                      {
                                  return(_SEARCH);
                                }

DEPTH                           {
                                  return(_DEPTH);
                                }

FIRST                           {
                                  return(_FIRST);
                                }

BREADTH                         {
                                  return(_BREADTH);
                                }

MIN                             { 
                                  return(_MIN);
                                }

INF                             { 
                                  return(_INF);
                                }

PI                              {
                                  return(_PI);
                                }

SIN                             {
                                  return(_SIN);
                                }

COS                             {
                                  return(_COS);
                                }

TAN                             {
                                  return(_TAN);
                                }

COT                             {
                                  return(_COT);
                                }

ACOS                            {
                                  return(_ACOS);
                                }

ASIN                            {
                                  return(_ASIN);
                                }

ATAN                            {
                                  return(_ATAN);
                                }

ATAN2                           {
                                  return(_ATAN2);
                                }

EXP                             {
                                  return(_EXP);
                                }

PWP                             {
                                  return(_PWP);
                                }

SQRT                            {
                                  return(_SQRT);
                                }

ABS                             {
                                  return(_ABS);
                                }

DIFF                            {
                                  return(_DIFF);
                                }

PARAMETER                       {
                                  return(_PARAMETER);
                                }

PRINT                           {
                                  return(_PRINT);
                                }

TR                              {
                                  return(_TR);
                                }

TX                              {
                                  return(_TX);
                                }

TY                              {
                                  return(_TY);
                                }

TZ                              {
                                  return(_TZ);
                                }

TV                              {
                                  return(_TV);
                                }

PA                              {
                                  return(_PA);
                                }

RX                              {
                                  return(_RX);
                                }

RY                              {
                                  return(_RY);
                                }

RZ                              {
                                  return(_RZ);
                                }

DRX                             {
                                  return(_DRX);
                                }

DRY                             {
                                  return(_DRY);
                                }

DRZ                             {
                                  return(_DRZ);
                                }

DPA_U                           {
                                  return(_DPA_U);
                                }

DPA_V                           {
                                  return(_DPA_V);
                                }

DDRX                            {
                                  return(_DDRX);
                                }

DDRY                            {
                                  return(_DDRY);
                                }

DDRZ                            {
                                  return(_DDRZ);
                                }

DDPA_UU                         {
                                  return(_DDPA_UU);
                                }

DDPA_UV                         {
                                  return(_DDPA_UV);
                                }

DDPA_VV                         {
                                  return(_DDPA_VV);
                                }

ID                              {
                                  return(_ID);
                                }

ZE                              {
                                  return(_Z);
                                }

"^-1"                           {
                                  return(_INV);
                                }

"="                             {
                                  return(_EQU); 
                                }

">="                            {
                                  return(_GEQ); 
                                }

"<="                            {
                                  return(_LEQ); 
                                }

">"                             {
                                  return(_GREATER); 
                                }

"<"                             {
                                  return(_LESS); 
                                }

"=="                            {
                                  return(_EQUAL); 
                                }

"!="                            {
                                  return(_NOT_EQUAL); 
                                }

":="                            {
                                  return(_ASSIGN); 
                                }

{I_NUMBER}                      { 
				  char string_tmp[100];

				  if (Readcuiksystemleng>100)
                                    Readcuiksystemerror("Integer numbers can not have more than 100 digits");

				  memcpy(string_tmp,Readcuiksystemtext,(unsigned int)Readcuiksystemleng);
				  string_tmp[Readcuiksystemleng]=0;
				  Readcuiksystemlval.int_number=atoi(string_tmp);
				  return(_INTEGER); 
				} 
 
{R_NUMBER}                      { 
				  char string_tmp[100];
				  
				  if (Readcuiksystemleng>100)
                                    Readcuiksystemerror("Real numbers can not have more than 100 digits");

				  memcpy(string_tmp,Readcuiksystemtext,(unsigned int)Readcuiksystemleng);
				  string_tmp[Readcuiksystemleng]=0;
				  Readcuiksystemlval.real_number=atof(string_tmp);
				  
				  return(_REAL);
				} 
  
{IDENTIFIER}                    { 
                                  if (Readcuiksystemleng>100)
                                    Readcuiksystemerror("Identifiers can not have more than 100 characters");

                                  NEW(Readcuiksystemlval.id,Readcuiksystemleng+1,char);
 				  memcpy(Readcuiksystemlval.id,Readcuiksystemtext,(unsigned int)Readcuiksystemleng);
  
 				  Readcuiksystemlval.id[Readcuiksystemleng]=0;

				  return(_IDENTIFIER);  
				} 

\{                              {
                                   Readcuiksystemerror("The input file can not include the symbol '{'");
                                }

.                               { return(Readcuiksystemtext[0]); }

%%
/** \endcond */

/**
  \brief Function called at the end of the parsing process.

  This function is automatically called by the parser at the end of a file.
  If 1 is returned the lexical analysis is stopped.
 
  \return 1 to stop the parsing. 
*/
int Readcuiksystemwrap()
{
  return(1);
}
   
