#include "filename.h"
#include "box_list.h"
#include "error.h"
#include "defines.h"
#include "parameters.h"
#include "world.h"
#include "chart.h"


#include <stdio.h>
#include <math.h>

/** \file cuikcost.c

    \brief Main body of the \ref cuikcost.c "cuikcost" aplication.
   
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikcost    [label="cuikcost"  color="#99ff99" shape=ellipse];

      param [label="param" color="#ff9999" ];
      world [label="world" color="#ff9999" ];
      sol   [label="sol"   color="#ff9999" ];
      cost  [label="cost"  color="#ff9999" ];

      param -> cuikcost;
      world -> cuikcost;
      sol -> cuikcost;
      cuikcost -> cost;
    }
    \enddot
    </center>

     A tool compute the cost of a given set of configurations.
     In the world files the cost is defined using the "avoid limit" clause.
     In the cuik files it can be defined as an arbitrary equation invoving the
     problem variables.

     This program gets a solution file, computes the cost for all solutions
     and generates a cost file that can be latter used to visualize the
     configuration spaces (using for instance \ref cuikplotatlas.c "cuikplotatlas").
*/


/** 
    \brief Main body of the \ref cuikcost.c "cuikcost" application.
   
    Main body of the \ref cuikcost.c "cuikcost" application.

    A tool compute the cost of a given set of configurations.
    In the world files the cost is defined using the "avoid limit" clause.
    In the cuik files it can be defined as an arbitrary equation invoving the
    problem variables.
    
    This program gets a solution file, computes the cost for all solutions
    and generates a cost file that can be latter used to visualize the
    configuration spaces (using for instance \ref cuikplotatlas.c "cuikplotatlas").

    Use:<br>
       - \b cuikcost \e problem_name \e sol_name
       .
    where
       - \e problem_name is the file with the molecuar information (typically a pdb).
       - \e sol_name file with the points to evaluate in the form of solutions
         (boxes). This file name is used (with the cost extension) to produce the output.
       .
   The file extensions are not required.

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikcost command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;
  TAtlasBase world;
  Tfilename fparam,fsols,fcost;
  Tbox *box;
  FILE *fout;
  unsigned int n,k,nBoxes;
  double *point;
  Tlist boxList;
  Titerator i;
  double *cost,minCost,maxCost,c;

  if (argc>2)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      /*Read the world from file*/
      CS_WD_INIT(&parameters,arg[1],&world);

      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      ReadListOfBoxes(GetFileFullName(&fsols),&boxList);
      nBoxes=ListSize(&boxList);
      if (nBoxes==0)
	Error("Empty solution file in cuikcost");

      /* Compute the energy for each conformation */
      InitIterator(&i,&boxList);
      First(&i);
      k=0;
      NEW(cost,nBoxes,double);
      while(!EndOfList(&i))
	{
	  box=(Tbox *)GetCurrent(&i);
	  if (k==0)
	    {
	      n=GetBoxNIntervals(box);
	      NEW(point,n,double);
	    }
	  GetBoxCenter(NULL,point,box);
	  cost[k]=CS_WD_COST(&parameters,FALSE,point,&world); 
	  if (k==0)
	    {
	      minCost=cost[k];
	      maxCost=cost[k];
	    }
	  else
	    {
	      if (cost[k]>maxCost)
		maxCost=cost[k];
	      else
		{
		  if (cost[k]<minCost)
		    minCost=cost[k];
		}
	    }
	  k++;
	  Advance(&i);
	}
      fprintf(stderr,"Extreme costs                     : %g %g\n",minCost,maxCost);

      /* Normalize and write */
      CreateFileName(NULL,arg[2],NULL,COST_EXT,&fcost);
      fprintf(stderr,"Writing cost file                 : %s\n",GetFileFullName(&fcost));

      fout=fopen(GetFileFullName(&fcost),"w");
      if (!fout)
	Error("Output file for costs can not be opened");
      
      for(k=0;k<nBoxes;k++)
	{
	  c=(cost[k]-minCost)/(maxCost-minCost);
	  if (c<1e-4) c=1e-4;
	  fprintf(fout,"%g\n",c);
	}
	
      fclose(fout);

      DeleteFileName(&fsols);
      DeleteFileName(&fcost);
      DeleteFileName(&fparam);
      
      free(point);
      free(cost);
      DeleteListOfBoxes(&boxList);
      DeleteParameters(&parameters);
      CS_WD_DELETE(&world);
    }
  else
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikcost <problem_name>  <sol_name> \n");
      fprintf(stderr,"    <problem_name> the input problem.\n");
      fprintf(stderr,"    <sol_name> Configurations to evaluate.\n");
      fprintf(stderr,"  The ouput file is <sol_name>.cost\n");
    }

  return(EXIT_SUCCESS);
}
