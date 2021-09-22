#include "filename.h"
#include "box_list.h"
#include "error.h"
#include "defines.h"
#include "parameters.h"
#include "bioworld.h"


#include <stdio.h>
#include <math.h>

/** \file cuikrmse.c

    \brief Main body of the \ref cuikrmse.c "cuikrmse" aplication.
   
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikrmse    [label="cuikrmse"  color="#99ff99" shape=ellipse];

      param [label="param" color="#ff9999" ];
      pdb   [label="pdb" color="#ff9999" ];
      sol   [label="sol" color="#ff9999" ];
      cost  [label="cost" color="#ff9999" ];

      param -> cuikrmse;
      pdb -> cuikrmse;
      sol -> cuikrmse;
      cuikrmse -> cost;
    }
    \enddot
    </center>

     A tool determine the conformation with minimum Root Mean Square Error (RMSE)
     with respect to the native conformation encoded in the pdb.
*/

/** 
    \brief Set to 1 if we use a user-provided RMSE

    This is only used for debug.
*/
#define CUSTOM_RMSE 0

/** 
   \brief Main body of the \ref cuikrmse.c "cuikrmse" application.

   Main body of the \ref cuikrmse.c "cuikrmse" application.

   A tool determine the conformation with minimum Root Mean Square Error (RMSE)
   with respect to the native conformation encoded in the pdb.

   Use:<br>
       - \b cuikrmse \e problem_name.pdb \e sol_name
       .
   where
       - \e problem_name is the file with the molecuar information (typically a pdb).
       - \e sol_name file with the points to evaluate in the form of solutions (boxes).
       .
   The pdb extension is required (any file type that can be read by openBabel can
   be used).

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikrmse command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  Tparameters parameters;
  TBioWorld bioWorld;
  Tfilename fparam,fsols;
  Tbox *box;
  unsigned int n,k,nBoxes,na;
  double *point,*pos;
  Tlist boxList;
  Titerator i;
  double e,eMin;
  double *conf;
  unsigned int nMin;

  if (argc>2)
    { 
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameters                : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      InitBioWorld(&parameters,arg[1],NO_UINT,&conf,&bioWorld);
      na=BioWorldNAtoms(&bioWorld);
      NEW(pos,na*3,double);

      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      ReadListOfBoxes(GetFileFullName(&fsols),&boxList);
      nBoxes=ListSize(&boxList);
      if (nBoxes==0)
	Error("Empty solution file in cuikrmse");

      /* Compute the RMSE for each conformation */
      InitIterator(&i,&boxList);
      First(&i);
      k=0;
      eMin=INF;
#if (CUSTOM_RMSE)
      InitWorldCD(FALSE,&(bioWorld.w));
#endif
      while(!EndOfList(&i))
	{
	  box=(Tbox *)GetCurrent(&i);
	  if (k==0)
	    {
	      n=GetBoxNIntervals(box);
	      NEW(point,n,double);
	    }
	  GetBoxCenter(NULL,point,box);
	  BioWordGetAtomPositionsFromConformation(&parameters,FALSE,point,pos,&bioWorld);
#if (!CUSTOM_RMSE)
	  e=BioWorldRMSE(pos,&bioWorld);
#else
	  {
	    /* Code used to fix one rigid body w.r.t another in the example/Bio/2LAO.pdb
	       Here we fix the pos. of atoms 2095, 1384, and 2463 (in rigid2) w.r.t.
	       atoms 1090, 2926, and 1362 (in rigid1, ground link) */
	    double d[19];
	    /* Refrence taken from the distances encoded in 1LST.pdb */
	    double ref[19]={3.1123,3.4769,11.0310,10.7216,6.4688,5.3507,7.9431,6.9768,9.5976,8.3534,6.8026,5.5221,6.0632,9.8894,3.9570,8.9912,9.0433,8.3446,8.2828};
	    boolean collision;
	    double *sfull;
            
            /* Check for collision and store the result */
	    RegenerateWorldSolutionPoint(&parameters,point,&sfull,&(bioWorld.w));
            collision=MoveAndCheckCD(&parameters,sfull,&(bioWorld.w));
	    if (collision)
	      e=INF;
	    else
	      {
		d[0]=Distance(3,&(pos[3*1090]),&(pos[3*2905]));
		d[1]=Distance(3,&(pos[3*1090]),&(pos[3*2906]));
		d[2]=Distance(3,&(pos[3*1090]),&(pos[3*1382]));
		d[3]=Distance(3,&(pos[3*1090]),&(pos[3*1381]));

		d[4]=Distance(3,&(pos[3*2924]),&(pos[3*2905]));
		d[5]=Distance(3,&(pos[3*2924]),&(pos[3*2906]));
		d[6]=Distance(3,&(pos[3*2924]),&(pos[3*1382]));
		d[7]=Distance(3,&(pos[3*2924]),&(pos[3*1381]));

		d[8]=Distance(3,&(pos[3*1362]),&(pos[3*2905]));
		d[9]=Distance(3,&(pos[3*1362]),&(pos[3*2906]));
		d[10]=Distance(3,&(pos[3*1362]),&(pos[3*1382]));
		d[11]=Distance(3,&(pos[3*1362]),&(pos[3*1381]));

		d[12]=Distance(3,&(pos[3*1090]),&(pos[3*2924]));
		d[13]=Distance(3,&(pos[3*1090]),&(pos[3*1362]));
		d[14]=Distance(3,&(pos[3*2924]),&(pos[3*1362]));

		d[15]=Distance(3,&(pos[3*2905]),&(pos[3*1382]));
		d[16]=Distance(3,&(pos[3*2905]),&(pos[3*1381]));
		d[17]=Distance(3,&(pos[3*2906]),&(pos[3*1382]));
		d[18]=Distance(3,&(pos[3*2906]),&(pos[3*1381]));

		e=Distance(19,d,ref);
	      }
	    free(sfull);
	    fprintf(stderr,"%u %g\n",k,e);
	  }
#endif
	  if (e<eMin)
	    {
	      eMin=e;
	      nMin=k;
	    }
	  k++;
	  Advance(&i);
	}
      fprintf(stderr,"Minimum RMSE                      : %g (%u)\n",eMin,nMin);

      DeleteFileName(&fsols);
      DeleteFileName(&fparam);
      
      free(conf);
      free(point);
      free(pos);
      DeleteListOfBoxes(&boxList);
      DeleteParameters(&parameters);
      DeleteBioWorld(&bioWorld);
    }
  else
    {
      fprintf(stderr,"  Wrong number of parameters.\n");
      fprintf(stderr,"  Use:\n");
      fprintf(stderr,"    cuikrmse <problem_name>.pdb  <sol_name>\n");
      fprintf(stderr,"   where:\n");
      fprintf(stderr,"      <problem_name> the input molecular information file (pdb).\n");
      fprintf(stderr,"      <sol_name> Configurations to evaluate.\n");
      fprintf(stderr,"  The extension (e.g., '.pdb') is required\n");
      fprintf(stderr,"  All the extensions managed by OpenBabel can be used\n");
    }

  return(EXIT_SUCCESS);
}
