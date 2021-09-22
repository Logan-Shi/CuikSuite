#include "variable.h"

#include "error.h"
#include "defines.h"

#include <stdlib.h>
#include <string.h>


/** 
   \file variable.c

   \brief Implementation of the functions operating on box Tvariable. 

   Implementation of the functions operating on box Tvariable. 

   \sa Tvariable, variable.h.
*/

void NewVariable(unsigned int type,char *name,Tvariable *v)
{
  v->type=type;
  v->topology=TOPOLOGY_R;

  NEW(v->name,strlen(name)+1,char);
  strcpy(v->name,name);

  NewInterval(-INF,INF,&(v->is)); /*default range for the variable*/
}

void CopyVariable(Tvariable *v_dst,Tvariable *v_src)
{
  v_dst->type=v_src->type;
  v_dst->topology=v_src->topology;

  NEW(v_dst->name,strlen(v_src->name)+1,char);
  strcpy(v_dst->name,v_src->name);

  CopyInterval(&(v_dst->is),&(v_src->is));
}

void SetVariableTopology(unsigned int t,Tvariable *v)
{
  if ((t!=TOPOLOGY_R)&&(t!=TOPOLOGY_S))
    Error("Undefined topology in SetVariableTopology");

  v->topology=t;
}

unsigned int GetVariableTopology(Tvariable *v)
{
  if ((v->topology==TOPOLOGY_S)&&(IntervalSize(&(v->is))<(M_2PI-ZERO)))
    return(TOPOLOGY_R);
  else
    return(v->topology);
}

unsigned int GetVariableType(Tvariable *v)
{
  return(v->type);
}

char *GetVariableName(Tvariable *v)
{
  return(v->name);
}

void SetVariableInterval(Tinterval *i,Tvariable *v)
{ 
  CopyInterval(&(v->is),i);
}

Tinterval *GetVariableInterval(Tvariable *v)
{
  return(&(v->is));
}

void PrintVariable(FILE *f,Tvariable *v)
{
  PRINT_VARIABLE_NAME(f,v->name);
  if (v->topology==TOPOLOGY_S)
    {
      fprintf(f," ~ [-PI,PI]");
      //PrintSymbolInterval(f,&(v->is));
    }
  else
    {
      fprintf(f," : ");
      PrintInterval(f,&(v->is));
    }
}

void DeleteVariable(Tvariable *v)
{
  free(v->name);
}
