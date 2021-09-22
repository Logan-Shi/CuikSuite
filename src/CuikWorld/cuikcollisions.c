#include "world.h"
#include "error.h"


/** \file cuikcollisions.c

    \brief Main body of the \ref cuikcollisions.c "cuikcollisions" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikcollisions    [label="cuikcollisions"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"     color="#ff9999" ];
      cost    [label="cost"    color="#ff9999" ];

      param -> cuikcollisions
      world -> cuikcollisions
      sol -> cuikcollisions
      cuikcollisions -> cost;
    }
    \enddot
    </center>

    This application check collision for a list of solution boxes.
*/

/** 
   \brief Main body of the \ref cuikcollisions.c "cuikcollisions"  application.

   Main body of the \ref cuikcollisions.c "cuikcollisions" application.

   Use: <br>
     - \b cuikcollisions \e world_name.world \e solutions_name.sol
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e solutions_name: Is the solution to test for collision.
     .
   File extensions are optional. 

   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuikanimate command itself and its arguments).
   \param arg Strings with the arguments.

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  
  if (argc>2)
    {
      Tworld world;
      Tparameters parameters;

      Tbox box;
      int token;
      double *s,*sfull;
      boolean collision;

      Tfilename fcollisions;
      Tfilename fsols;
      Tfilename fparam;

      unsigned int total,good;

      FILE *fin,*fout;
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      fin=fopen(GetFileFullName(&fsols),"r");
      if (!fin)
	Error("The file with the solution boxes can not be opened");

      CreateFileName(NULL,arg[2],"_collision",COST_EXT,&fcollisions);
      fprintf(stderr,"Writing collisions file           : %s\n",GetFileFullName(&fcollisions));

      fout=fopen(GetFileFullName(&fcollisions),"w");
      if (!fout)
	Error("The file for the collision information can not be opened");
    
      /* Init the collision detection */
      InitWorldCD(&parameters,1,&world);
      /* Check all the given solutions for possible collsion */
      total=0;
      good=0;
      do {
	token=ReadBox(fin,&box);
	if (token!=EOF)
	  {
	    /* Get the center of the box as a solution point. */
	    NEW(s,GetBoxNIntervals(&box),double);
	    GetBoxCenter(NULL,s,&box);

	    /* The solutions are stored using only the system variables.
	       Before checking for collision we have to regenerate the
	       solution and create values for the non-sytem variables */
	    RegenerateWorldSolutionPoint(&parameters,s,&sfull,&world);
	    
	    /* Check for collision and store the result */
	    collision=MoveAndCheckCD(&parameters,FALSE,0,sfull,NULL,&world);
	    if (collision)
	      fprintf(fout,"1\n");
	    else
	      {
		fprintf(fout,"0.1\n");
		good++;
	      }

	    /* Release the memory used for this solution. */
	    free(sfull);
	    free(s);
	    DeleteBox(&box);
	    total++;
	  }
      } while(token!=EOF);

      fprintf(stderr,"Collision-free ratio              : %g\n",(double)good/(double)total);
      
      fclose(fin);
      fclose(fout);

      DeleteFileName(&fcollisions);  
      DeleteFileName(&fsols);      
      DeleteFileName(&fparam);

      DeleteWorld(&world);
      DeleteParameters(&parameters);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikcollisions <world>.world <solutions>.sol\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <solutions>:  Solutions for which to extract the axes.\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
