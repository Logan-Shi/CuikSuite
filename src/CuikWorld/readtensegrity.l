%{
/** \cond */

/*
* Lexical analizer for tensegrity files
*/


#include <stdlib.h> 
#include <string.h>
#include "defines.h"
#include "error_tensegrity.h"
#include "color.h" /* Tcolor used in %union */
#include "interval.h" /* Tinterval used in %union */
#include "htransform.h" /* Tinterval used in %union */
#include "readtensegrity.tab.h"

int ReadTensegritylex(void);

extern unsigned int RTline; /*current line number (declared in the YACC module and updated here)*/

/** \endcond */
%}
%s IN_COMMENT

EMPTY                           [ \t]+ 
RETURN                          \n
DIGIT                           [0-9] 
LETTER                          [a-zA-Z]
R_NUMBER                        (({DIGIT}+(\.{DIGIT}+)?)|(\.{DIGIT}+))((E|e)[+-]?{DIGIT}+)? 
I_NUMBER                        {DIGIT}+ 
STRING                          \"[^\"]+\"
IDENTIFIER                      {LETTER}({DIGIT}|{LETTER}|"_")*
COMMENT                         \%[^\n]*
COMMENT2                        \#[^\n]*
COMMENT3                        \/\/[^\n]*

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
  \n        RTline++;
}

{EMPTY}                         { } 

{RETURN}                        { RTline++; } 

"[CONSTANTS]"                   {
                                  return(_CONSTANTS);
                                }

":="                            {
                                  return(_ASSIGN); 
                                }

"=="                            {
                                  return(_EQUAL); 
                                }

"!="                            {
                                  return(_NOT_EQUAL); 
                                }

"<="                            {
                                  return(_LESS_EQUAL); 
                                }

">="                            {
                                  return(_GREATER_EQUAL); 
                                }

"<"                             {
                                  return(_LESS); 
                                }

">"                             {
                                  return(_GREATER); 
                                }

PI                              {
                                  return(_PI);
                                }

EXP                             {
                                  return(_EXP);
                                }

PARAMETER                       {
                                  return(_PARAMETER);
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

SQRT                            {
                                  return(_SQRT);
                                }

ABS                             {
                                  return(_ABS);
                                }

PRINT                           {
                                  return(_PRINT);
                                }

"PLANAR"                        {
                                  return(_PLANAR);
                                }

"FREE"                          {
                                  return(_FREE);
                                }

"FLYING"                        {
                                  return(_FLYING);
                                }

"STRUCTURE"                     {
                                  return(_STRUCTURE);
                                }

"STRUT"                         {
                                  return(_STRUT);
                                }

"BAR"                           {
                                  return(_BAR);
                                }

"PRISMATIC"                     {
                                  return(_PRISMATIC);
                                }

"CABLE"                         {
                                  return(_CABLE);
                                }

"SPRING"                        {
                                  return(_SPRING);
                                }

"LOOPS"                         {
                                  return(_LOOPS);
                                }

"STIFFNESS"                     {
                                  return(_STIFFNESS);
                                }

"REST"                          {
                                  return(_REST);
                                }

"FORCE"                        {
                                  return(_FORCE);
                                }

"GRANULARITY"                   {
                                  return(_GRANULARITY);
                                }

"HIDDEN"                        {
                                  return(_HIDDEN);
                                }

"DECORATION"                    {
                                  return(_DECORATION);
                                }

"[COUPLE]"                      {
                                  return(_COUPLE);
                                }

"ORIENTATION"                   {
                                  return(_ORIENTATION);
                                }

"[FORCES]"                      {
                                  return(_FORCES);
                                }

"[ADDONS]"                      {
                                  return(_ADDONS);
                                }

"NO"                            {
                                  return(_NO);
                                }

"NULL"                          {
                                  return(_NULL);
                                }

"[FIXED POINTS]"                {
                                  return(_FIXED_POINTS);
                                }

"X"                             {
                                  return(_X);
                                }

"Y"                             {
                                  return(_Y);
                                }

"Z"                             {
                                  return(_Z);
                                }

"[OBSTACLES]"                   {
                                  return(_OBSTACLES);
                                }

"BODY"                          {
                                  return(_BODY);
                                }

"LENGTH"                        {
                                  return(_LENGTH);
                                }

"RADIUS"                        {
                                  return(_RADIUS);
                                }

"ID"                            {
                                  return(_ID);
                                }

"TX"                            {
                                  return(_TX);
                                }

"TY"                            {
                                  return(_TY);
                                }

"TZ"                            {
                                  return(_TZ);
                                }

"TXYZ"                          {
                                  return(_TXYZ);
                                }

"RX"                            {
                                  return(_RX);
                                }

"RY"                            {
                                  return(_RY);
                                }

"RZ"                            {
                                  return(_RZ);
                                }

"MASS"                          {
                                  return(_MASS);
                                }

"INERTIAL"                      {
                                  return(_INERTIAL);
                                }   

"FRAME"                         {
                                  return(_FRAME);
                                }   

"INERTIA"                       {
                                  return(_INERTIA);
                                }                  

"MATRIX"                        {
                                  return(_MATRIX);
                                }  

"VELOCITY"                      {
                                  return(_VELOCITY);
                                }  

"ACCELERATION"                  {
                                  return(_ACCELERATION);
                                }  

"EFFORT"                        {
                                  return(_EFFORT);
                                }    

"COST"                         {
                                  return(_COST);
                                }  

"FRICTION"                      {
                                  return(_FRICTION);
                                }  

"DAMPING"                       {
                                  return(_DAMPING);
                                }

"BOX"                           {
                                  return(_BOX);
                                }

"PRISM"                         {
                                  return(_PRISM);
                                }

"SPHERE"                        {
                                  return(_SPHERE);
                                }

"CYLINDER"                      {
                                  return(_CYLINDER);
                                }

"COLOR"                         {
                                  return(_COLOR);
                                }

"RED"                           {
                                  return(_RED);
                                }

"GREEN"                         {
                                  return(_GREEN);
                                }

"BLUE"                          {
                                  return(_BLUE);
                                }

"WHITE"                         {
                                  return(_WHITE);
                                }

"BLACK"                         {
                                  return(_BLACK);
                                }

"GREY"                          {
                                  return(_GREY);
                                }

"YELLOW"                        {
                                  return(_YELLOW);
                                }

"CYAN"                          {
                                  return(_CYAN);
                                }

"PURPLE"                        {
                                  return(_PURPLE);
                                }

"[COLLISIONS]"                  {
                                  return(_COLLISIONS);
                                }

"CHECK"                         {
                                  return(_CHECK);
                                }

"DO"                            {
                                  return(_DO);
                                }

"NOT"                           {
                                  return(_NOT);
                                }

"ALL"                           {
                                  return(_ALL);
                                }

"CONNECTED"                     {
                                  return(_CONNECTED);
                                }

{I_NUMBER}                      { 
				  char string_tmp[100];
				  
				  memcpy(string_tmp,ReadTensegritytext,(unsigned int)ReadTensegrityleng);
				  string_tmp[ReadTensegrityleng]=0;
				  ReadTensegritylval.int_number=atoi(string_tmp);
				  return(_INTEGER); 
				} 
 
{R_NUMBER}                      { 
				  char string_tmp[100];
				  
				  memcpy(string_tmp,ReadTensegritytext,(unsigned int)ReadTensegrityleng);
				  string_tmp[ReadTensegrityleng]=0;
				  ReadTensegritylval.real_number=atof(string_tmp);
				  
				  return(_REAL);
				} 

{STRING}                        { 
                                  NEW(ReadTensegritylval.string,ReadTensegrityleng,char);
				  
 				  memcpy(ReadTensegritylval.string,&(ReadTensegritytext[1]),(unsigned int)ReadTensegrityleng-2);
				  ReadTensegritylval.string[ReadTensegrityleng-2]=0;
				  
				  return(_STRING);
				} 

{IDENTIFIER}                    { 
                                  NEW(ReadTensegritylval.id,ReadTensegrityleng+1,char);
 				  memcpy(ReadTensegritylval.id,ReadTensegritytext,(unsigned int)ReadTensegrityleng);
  
 				  ReadTensegritylval.id[ReadTensegrityleng]=0;

 				  return(_IDENTIFIER);  
                                }

.                               { return(ReadTensegritytext[0]); }
 
%%

/** \cond */

/*
 * This function is automatically called by the parser at the end of a file.
 * If 1 is returned the lexical analysis is stopped.
 */
int ReadTensegritywrap()
{
  return(1);
}

/** \endcond */
