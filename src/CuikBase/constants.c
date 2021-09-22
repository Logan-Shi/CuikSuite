#include "constants.h"

#include "error.h"
#include "boolean.h"
#include "defines.h"

#include <stdlib.h>
#include <string.h>

/** \file constants.c
    \brief Implementations of the functions operating on Tconstants.
    
    Implementations of the functions operating on the Tconstants.
    
    \sa Tconstant, constants.h.
*/

/*
 * Init the set of constants.
 */
void InitConstants(Tconstants *cts)
{
  cts->max_constants=INIT_NUM_CONSTANTS;

  NEW(cts->cts,cts->max_constants,Tconstant);

  cts->n=0;
}

void CopyConstants(Tconstants *cts_dst,Tconstants *cts_src)
{
  unsigned int i;

  cts_dst->max_constants=cts_src->max_constants;
  NEW(cts_dst->cts,cts_dst->max_constants,Tconstant);
  cts_dst->n=0;
  for(i=0;i<cts_dst->n;i++)
    AddConstant(cts_src->cts[i].name,cts_src->cts[i].vs,cts_dst);
}


void MergeConstants(Tconstants *c1,Tconstants *c2,Tconstants *cout)
{
  unsigned int i;

  if (cout!=c1)
    CopyConstants(cout,c1);

  for(i=0;i<c2->n;i++)
    AddConstant(c2->cts[i].name,c2->cts[i].vs,cout);
}

/*
 * Returns the number of constants includes in the set 'vs'.
 */
unsigned int NConstants(Tconstants *cts)
{
  return(cts->n);
}

/*
 * Adds a new constant with name 'name' value 'v' and degrees flag 'd' in the set 'vs'
 * NOTE: It does not test whether or not there is another constant with the same name!!!!
 * This must be tested before using AddConstant calling the function 'GetConstantWithName'
 */
unsigned int AddConstant(char *name,double v,Tconstants *cts)
{
  unsigned int num;

  if (cts->n==cts->max_constants)
    MEM_DUP(cts->cts,cts->max_constants,Tconstant);
  
  num=cts->n;

  NEW(cts->cts[num].name,strlen(name)+1,char);
  strcpy(cts->cts[num].name,name);
  cts->cts[num].vs=v;

  cts->n++;

  return(num);
}

/*
 * Returns the identifier of the constant with name 'name' in the set 'vs'.
 * If there is no constant with that name, it returns (-1).
 * This function can be used to test if a constant with a given name has been already defined.
 */
unsigned int GetConstantWithName(char *name,Tconstants *cts)
{
  boolean found;
  unsigned int i;

  found=FALSE;
  i=0;
  while((!found)&&(i<cts->n))
    {
      if (strcmp(name,cts->cts[i].name)==0)
	found=TRUE;
      else
	i++;
    }

  if (found)
    return(i);
  else
    return(NO_UINT);
}

/*
 * Returns the value of constant number 'n' in the set 'vs'.
 * If there is no constant number 'n' it issues an error.
 */
double GetConstantValue(unsigned int n,Tconstants *cts)
{
  if (n<cts->n)
    return(cts->cts[n].vs);
  else
    Error("Undefined constant referenced in function GetConstant");
  return(0.0);
}

/*
 * Prints the information of constant set 'vs' (Identifier and name for all constants)
 * on file 'f'.
 */
void PrintConstants(FILE *f,Tconstants *cts)
{
  unsigned int i;
  
  for(i=0;i<cts->n;i++)
    fprintf(f,"%3u  %s=%f\n",i,cts->cts[i].name,cts->cts[i].vs);
}

/*
 * Deletes the constant set 'vs'.
 */
void DeleteConstants(Tconstants *cts)
{
  unsigned int i;

  for(i=0;i<cts->n;i++)
    free(cts->cts[i].name);
  free(cts->cts);
}
