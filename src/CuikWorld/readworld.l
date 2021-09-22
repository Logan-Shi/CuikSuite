%{
/*
* Lexical analizer for world files
*/

/** \cond */

#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "error_world.h"
#include "color.h" /* %union uses Tcolor */
#include "readworld.tab.h"

typedef struct {
  YY_BUFFER_STATE buffer; /**< Lex buffer */
  char *prefix;           /**< Prefix to be added to the all the identifiers in the current include level. */
  unsigned int pl;        /**< Prefix lenght. */
  unsigned int line;      /**< Line number where the current include occurs. Used to recover the line count at the end of the include process. */
  unsigned int fl;        /**< First link in this level of includes. */
  unsigned int fo;        /**< First object in this level of includes. */
} TincludeInfo;

TincludeInfo includeInfo[MAX_INCLUDES];
unsigned int currentIncludeLevel=0;

unsigned int firstLink;   /* first link in the current object */
unsigned int firstObject; /* first object in the current file */

int ReadWorldlex(void);

extern unsigned int RWline; /*current line number (declared in the YACC module and updated here)*/

void Switch2File(char *ln,unsigned int nl,unsigned int no,char *path,char *file);

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
EXT_IDENTIFIER                  {IDENTIFIER}("::"{IDENTIFIER})+
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
  \n        RWline++;
}

{EMPTY}                         { }

{RETURN}                        { RWline++; }

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

PARAMETER                       {
                                  return(_PARAMETER);
                                }

PRINT                           {
                                  return(_PRINT);
                                }

"[LINKS]"                       {
                                  return(_LINKS);
                                }

"BODY"                          {
                                  return(_BODY);
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

"[JOINTS]"                      {
                                  return(_JOINTS);
                                }

"FIX"                           {
                                  return(_FIX);
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

"TR"                            {
                                  return(_TR);
                                }

"^-1"                           {
                                  return(_INV);
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

"TORQUE"                        {
                                  return(_TORQUE);
                                }

"FORCE"                         {
                                  return(_FORCE);
                                }

"EFFORT"                        {
                                  return(_EFFORT);
                                }

"COST"                          {
                                  return(_COST);
                                }

"FRICTION"                      {
                                  return(_FRICTION);
                                }

"DAMPING"                       {
                                  return(_DAMPING);
                                }

"PRISMATIC"                     {
                                  return(_PRISMATIC);
                                }

"REVOLUTE"                      {
                                  return(_REVOLUTE);
                                }

"CREVOLUTE"                     {
                                  return(_CREVOLUTE);
                                }

"SPHERICAL"                     {
                                  return(_SPHERICAL);
                                }

"UNIVERSAL"                     {
                                  return(_UNIVERSAL);
                                }

"SPH_SPH"                       {
                                  return(_SPH_SPH);
                                }

"SPH_PRS_SPH"                   {
                                  return(_SPH_PRS_SPH);
                                }

"SPRING"                        {
                                  return(_SPRING);
                                }

"XYSPRING"                      {
                                  return(_XYSPRING);
                                }

"C_CABLE"                       {
                                  return(_C_CABLE);
                                }

"C_SPRING"                      {
                                  return(_C_SPRING);
                                }

"C_LEG"                         {
                                  return(_C_LEG);
                                }

"REST"                          {
                                  return(_REST);
                                }

"STIFFNESS"                     {
                                  return(_STIFFNESS);
                                }

"IN_PATCH"                      {
                                  return(_IN_PATCH);
                                }

"LENGTH"                        {
                                  return(_LENGTH);
                                }

"RADIUS"                        {
                                  return(_RADIUS);
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

"SOLID"                          {
                                  return(_SOLID);
                                }

"ELLIPSOID"                     {
                                  return(_ELLIPSOID);
                                }

"CYLINDER"                      {
                                  return(_CYLINDER);
                                }

"ROD_X"                         {
                                  return(_ROD_X);
                                }

"ROD_Y"                         {
                                  return(_ROD_Y);
                                }

"ROD_Z"                         {
                                  return(_ROD_Z);
                                }

"CYLINDER_X"                    {
                                  return(_CYLINDER_X);
                                }

"CYLINDER_Y"                    {
                                  return(_CYLINDER_Y);
                                }

"CYLINDER_Z"                    {
                                  return(_CYLINDER_Z);
                                }

"LINE"                          {
                                  return(_LINE);
                                }

"SEGMENTS"                      {
                                  return(_SEGMENTS);
                                }


"[OBSTACLES]"                   {
                                  return(_OBSTACLES);
                                }

"[COLLISIONS]"                  {
                                  return(_COLLISIONS);
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

"RANGE"                         {
                                  return(_RANGE);
                                }

"REFERENCE"                     {
                                  return(_REFERENCE);
                                }

"CHECK"                         {
                                  return(_CHECK);
                                }

"DO NOT"                        {
                                  return(_NO);
                                }

"ALL"                           {
                                  return(_ALL);
                                }

"CONNECTED"                     {
                                  return(_CONNECTED);
                                }

"SELFCOLLISIONS"                {
                                  return(_SELFCOLLISIONS);
                                }

"AVOID"                         {
                                  return(_AVOID);
                                }

"LIMITS"                        {
                                  return(_LIMITS);
                                }

"[INCLUDE]"                     {
                                  return(_INCLUDE);
                                }

"[EQUATIONS]"                   {
                                  return(_EQUATIONS);
                                }

"EQFILE"                        {
                                  return(_EQFILE);
                                }

{I_NUMBER}                      {
				  char string_tmp[100];

				  memcpy(string_tmp,ReadWorldtext,(unsigned int)ReadWorldleng);
				  string_tmp[ReadWorldleng]=0;
				  ReadWorldlval.int_number=atoi(string_tmp);
				  return(_INTEGER);
				}

{R_NUMBER}                      {
				  char string_tmp[100];

				  memcpy(string_tmp,ReadWorldtext,(unsigned int)ReadWorldleng);
				  string_tmp[ReadWorldleng]=0;
				  ReadWorldlval.real_number=atof(string_tmp);

				  return(_REAL);
				}

{STRING}                        {
                                  NEW(ReadWorldlval.string,ReadWorldleng,char);

 				  memcpy(ReadWorldlval.string,&(ReadWorldtext[1]),(unsigned int)ReadWorldleng-2);
				  ReadWorldlval.string[ReadWorldleng-2]=0;

				  return(_STRING);
				}

{IDENTIFIER}                    {
	                          if (currentIncludeLevel==0)
	                            {
	                               NEW(ReadWorldlval.id,ReadWorldleng+1,char);
 				       memcpy(ReadWorldlval.id,ReadWorldtext,(unsigned int)ReadWorldleng);

 				       ReadWorldlval.id[ReadWorldleng]=0;
	                            }
	                          else
	                            {
	                              NEW(ReadWorldlval.id,includeInfo[currentIncludeLevel-1].pl+2+ReadWorldleng+1,char);
	                              sprintf(ReadWorldlval.id,"%s__%s",includeInfo[currentIncludeLevel-1].prefix,ReadWorldtext);
                                      ReadWorldlval.id[includeInfo[currentIncludeLevel-1].pl+ReadWorldleng+2]=0;
	                            }

				  return(_IDENTIFIER);
                                }

{EXT_IDENTIFIER}                {
                                  unsigned int i;

	                          if (currentIncludeLevel==0)
	                            {
	                               NEW(ReadWorldlval.id,ReadWorldleng+1,char);
 				       memcpy(ReadWorldlval.id,ReadWorldtext,(unsigned int)ReadWorldleng);

 				       ReadWorldlval.id[ReadWorldleng]=0;

 				       for(i=0;i<ReadWorldleng;i++)
 				         {
 				           if (ReadWorldlval.id[i]==':')
 				             ReadWorldlval.id[i]='_';
 				         }
	                            }
	                          else
	                            {
	                              unsigned int k;

	                              NEW(ReadWorldlval.id,includeInfo[currentIncludeLevel-1].pl+2+ReadWorldleng+1,char);
	                              sprintf(ReadWorldlval.id,"%s__%s",includeInfo[currentIncludeLevel-1].prefix,ReadWorldtext);
                                      ReadWorldlval.id[includeInfo[currentIncludeLevel-1].pl+ReadWorldleng+2]=0;

 				      for(i=0,k=includeInfo[currentIncludeLevel-1].pl+2;i<ReadWorldleng;i++,k++)
 				        {
 				          if (ReadWorldlval.id[k]==':')
 				            ReadWorldlval.id[k]='_';
 				        }
	                            }

				  return(_EXT_IDENTIFIER);
				}

<<EOF>>                         {
                                  if (currentIncludeLevel>0)
                                    {
                                      currentIncludeLevel--;

                                      /* Recover the line number */
                                      RWline=includeInfo[currentIncludeLevel].line;

                                      /* Deletes the prefix */
                                      free(includeInfo[currentIncludeLevel].prefix);

				      /* Recover the first link/object in the upper file */
				      firstLink=includeInfo[currentIncludeLevel].fl;
				      firstObject=includeInfo[currentIncludeLevel].fo;

                                      /* Deletes the lex buffer and switch */
                                      yy_delete_buffer(YY_CURRENT_BUFFER);
                                      yy_switch_to_buffer(includeInfo[currentIncludeLevel].buffer);
                                    }
                                  else
                                    yyterminate();
                                }

.                               { return(ReadWorldtext[0]); }

%%
/** \cond */

/*
 * This function is automatically called by the parser at the end of a file.
 * If 1 is returned the lexical analysis is stopped.
 */
int ReadWorldwrap()
{
  return(1);
}

/** \endcond */


void Switch2File(char *ln,unsigned int nl,unsigned int no,char *path,char *file)
{
  FILE *f;
  unsigned int l1,l2;
  char *name;

  if (currentIncludeLevel>=MAX_INCLUDES)
    ReadWorlderror("Includes nested too deeply. A loop of includes?" );

  /* in the new file, lines are numbered from 1 again :) */
  includeInfo[currentIncludeLevel].line=RWline;
  RWline=1;

  /* Store the first link/object in the current file and reset them */
  includeInfo[currentIncludeLevel].fl=firstLink;
  includeInfo[currentIncludeLevel].fo=firstObject;
  firstLink=nl;
  firstObject=no;

  /* identifiers in the new file will need the prefix defined next */
  l2=strlen(ln);
  if (currentIncludeLevel>0)
    {
      /* If we have a previous prefix, add it to the current prefix */
      l1=includeInfo[currentIncludeLevel-1].pl;
      NEW(includeInfo[currentIncludeLevel].prefix,l1+l2+2,char);
      memcpy(includeInfo[currentIncludeLevel].prefix,includeInfo[currentIncludeLevel-1].prefix,l1*sizeof(char));
      includeInfo[currentIncludeLevel].prefix[l1]='_';
      l1++;
    }
  else
    {
      l1=0;
      NEW(includeInfo[currentIncludeLevel].prefix,l2+1,char);
    }
  /* add the link name to the prefix */
  memcpy(&(includeInfo[currentIncludeLevel].prefix[l1]),ln,l2*sizeof(char));
  includeInfo[currentIncludeLevel].prefix[l1+l2]=0;

  includeInfo[currentIncludeLevel].pl=l1+l2; /* cache of the prefix lenght */

  /* stack the yybuffer */
  includeInfo[currentIncludeLevel].buffer=YY_CURRENT_BUFFER;
  currentIncludeLevel++;

  /* Now try to open the file to be included */
  l1=strlen(path);
  l2=strlen(file);
  NEW(name,l1+l2+1,char);
  memcpy(name,path,l1*sizeof(char));
  memcpy(&(name[l1]),file,l2*sizeof(char));
  name[l1+l2]=0;

  f=fopen(name,"r");
  if (!f)
    {
      char *m;

      NEW(m,l1+l1+100,char);
      sprintf(m,"Can not open included file: %s",name);
      ReadWorlderror(m);
      free(m);
    }
  else
   {
    yy_switch_to_buffer(yy_create_buffer(f,YY_BUF_SIZE));
    BEGIN(INITIAL);
   }
}
