#include "filename.h"
#include "box_list.h"
#include "error.h"
#include "defines.h"
#include "parameters.h"
#include "bioworld.h"


#include <stdio.h>
#include <math.h>
#include <strings.h>

/** \file cuikenergy.c

    \brief Main body of the \ref cuikenergy.c "cuikenergy" aplication.
   
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikenergy    [label="cuikenergy"  color="#99ff99" shape=ellipse];

      param [label="param" color="#ff9999" ];
      pdb   [label="tens/pdb" color="#ff9999" ];
      sol   [label="sol" color="#ff9999" ];
      cost  [label="cost" color="#ff9999" ];

      param -> cuikenergy;
      pdb -> cuikenergy;
      sol -> cuikenergy;
      cuikenergy -> cost;
    }
    \enddot
    </center>

     A tool compute the energy of a set of conformations, typically the centers
     of the atlas computec by \ref cuikatlas.c "cuikatlas" and extracted using 
     \ref cuikatlascenters.c "cuikatlascenters".
     This produces a \e cost file that can be used to plot the atlas "with colors"
     using \ref cuikplotatlas.c "cuikplotatlas".
*/

/** 
   \brief Main body of the \ref cuikenergy.c "cuikenergy" application.

   Main body of the \ref cuikenergy.c "cuikenergy" application.

   A tool compute the energy of a set of conformations, typically the centers
   of the atlas computec by \ref cuikatlas.c "cuikatlas" and extracted using 
   \ref cuikatlascenters.c "cuikatlascenters".
   This produces a \e cost file that can be used to plot the atlas "with colors"
   using \ref cuikplotatlas.c "cuikplotatlas".

   This application is basically designed to evaluate the potential energy
   of tensegrity structures or of molecular files. It would not produce
   sensible results in any other case (the potential energy for other
   systems is 0 in all configurations). Note that we first try to read
   the tensegrity file and if this fail, we then try to read a molecular
   file.

   Use:<br>
       - \b cuikenergy [log|nolog scale|noscale] \e problem_name \e sol_name
       .
   where
       - log|nolog [optional] Compute (or not) the log of the energy (default: nolog).
       - scale|noscale [optional] Scale (or not) the energy to the [0,1] range (default: scale).
       - \e problem_name is the file with the molecuar information (typically a 
                         tensegrity of a pdb file).
       - \e sol_name file with the points to evaluate in the form of solutions
         (boxes). This file name is used (with the cost extension) to produce the output.
       .

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikenergy command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;
  Tworld world;
  TBioWorld bioWorld;
  boolean bio;
  Tfilename fparam,fsols,fcost;
  Tbox *box;
  FILE *fout;
  unsigned int n,k,nBoxes;
  double *point;
  Tlist boxList;
  Titerator i;
  double *cost,minCost,maxCost;
  double *conf;
  unsigned int nMin,nMax;
  double e;
  boolean log_cost,scale_cost;

  if (argc>2)
    {
      /* default flags */
      log_cost=FALSE;
      scale_cost=TRUE;
      
      /* parse parameters */
      for(k=1;k<(unsigned int)argc-2;k++)
	{
	  if (strcasecmp(arg[k],"scale")==0)
	    scale_cost=TRUE;
	  if (strcasecmp(arg[k],"log")==0)
	    log_cost=TRUE;
	  if (strcasecmp(arg[k],"noscale")==0)
	    scale_cost=FALSE;
	  if (strcasecmp(arg[k],"nolog")==0)
	    log_cost=FALSE;
	}
      
      /*Init parameters*/
      CreateFileName(NULL,arg[argc-2],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      if (InitBioWorld(&parameters,arg[argc-2],NO_UINT,&conf,&bioWorld))
	bio=TRUE;
      else
	{
	  InitWorldFromFile(&parameters,FALSE,TRUE,arg[argc-2],&world);
	  bio=FALSE;
	}
      
      CreateFileName(NULL,arg[argc-1],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      ReadListOfBoxes(GetFileFullName(&fsols),&boxList);
      nBoxes=ListSize(&boxList);
      if (nBoxes==0)
	Error("Empty solution file in cuikenergy");

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
	  if (bio)
	    e=BioWorldEnergy(&parameters,FALSE,point,(void *)&bioWorld);
	  else
	    e=WorldPotentialEnergy(&parameters,FALSE,point,(void *)&world);
	  
	  if (log_cost)
	    cost[k]=log(e);
	  else
	    cost[k]=e;
		
	  fprintf(stderr,"%u -> %g (%g)\n",k,cost[k],e);

	  if (k==0)
	    {
	      minCost=cost[k]; nMin=k;
	      maxCost=cost[k]; nMax=k;
	    }
	  else
	    {
	      if (cost[k]>maxCost)
		{ maxCost=cost[k]; nMax=k; }
	      else
		{
		  if (cost[k]<minCost)
		    { minCost=cost[k]; nMin=k; }
		}
	    }
	  k++;
	  Advance(&i);
	}
      fprintf(stderr,"Extreme energies                  : %g (%u) -- %g (%u)\n",minCost,nMin,maxCost,nMax);
      fprintf(stderr,"Parameters: ");
      if (log_cost)
	fprintf(stderr,"log,");
      else
	fprintf(stderr,"nolog,");
      if (scale_cost)
	fprintf(stderr,"scale\n");
      else
	fprintf(stderr,"noscale\n");
	

      /* Normalize and write */
      CreateFileName(NULL,arg[argc-1],NULL,COST_EXT,&fcost);
      fprintf(stderr,"Writing cost file                 : %s\n",GetFileFullName(&fcost));

      fout=fopen(GetFileFullName(&fcost),"w");
      if (!fout)
	Error("Output file for costs can not be opened");
      
      for(k=0;k<nBoxes;k++)
	{ 
	  if (scale_cost)
	    {
	      e=((cost[k]-minCost)/(maxCost-minCost))*(1-1e-3)+1e-3;
	      fprintf(fout,"%g\n",e);
	    }
	  else
	    fprintf(fout,"%g\n",cost[k]);
	}
      fclose(fout);

      DeleteFileName(&fsols);
      DeleteFileName(&fcost);
      DeleteFileName(&fparam);
      
      free(point);
      free(cost);
      DeleteListOfBoxes(&boxList);
      DeleteParameters(&parameters);
      if (bio)
	{
	  DeleteBioWorld(&bioWorld);
	  free(conf);
	}
      else
	DeleteWorld(&world);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");
      fprintf(stderr,"    cuikenergy [log|nolog, scale|noscale] <problem_name>.pdb  <sol_name>\n");
      fprintf(stderr,"   where:\n");
      fprintf(stderr,"      <log|nolog> [optional] Applies (or not) the log to the energy (default: nolog).\n");
      fprintf(stderr,"      <scale|noscale> [optional] Scales (or not) the energy to the range [0,1] (default: scale).\n");
      fprintf(stderr,"      <problem_name> the input molecular information file (pdb).\n");
      fprintf(stderr,"      <sol_name> Configurations to evaluate.\n");
      fprintf(stderr,"  The extension (e.g., '.pdb') is required\n");
      fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
      fprintf(stderr,"  The ouput file is <sol_name>.cost\n");
    }

  return(EXIT_SUCCESS);
}
