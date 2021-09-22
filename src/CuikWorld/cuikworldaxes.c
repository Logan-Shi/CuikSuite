#include "world.h"
#include "error.h"


/** \file cuikworldaxes.c

    \brief Main body of the \ref cuikworldaxes.c "cuikworldaxes" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikworldaxes    [label="cuikworldaxes"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      world   [label="world"   color="#ff9999" ];
      sol     [label="sol"     color="#ff9999" ];
      axes    [label="axes"    color="#ff9999" ];

      param -> cuikworldaxes
      world -> cuikworldaxes
      sol -> cuikworldaxes
      cuikworldaxes -> axes;
    }
    \enddot
    </center>

    This application extracts joint axes from solution boxes.
*/

/** 
   \brief Main body of the \ref cuikworldaxes.c "cuikworldaxes"  application.

   Main body of the \ref cuikworldaxes.c "cuikworldaxes" application.

   Use: <br>
     - \b cuikworldaxes \e world_name.world \e solutions_name.sol
     .
   Where: 
     - \e world_name:  File describing the problem.
     - \e solutions_name: Is the solution set for which to extract the axes.
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
      unsigned int nvs;

      Tfilename faxes;
      Tfilename fsols;
      Tfilename fparam;

      FILE *fin,*fout;
      
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      InitWorldFromFile(&parameters,FALSE,TRUE,arg[1],&world);

      nvs=GetWorldNumSystemVariables(&world);
      
      CreateFileName(NULL,arg[2],NULL,SOL_EXT,&fsols);
      fprintf(stderr,"Reading solution file             : %s\n",GetFileFullName(&fsols));
      fin=fopen(GetFileFullName(&fsols),"r");
      if (!fin)
	Error("The file with the solution boxes can not be opened");

      CreateFileName(NULL,arg[2],NULL,AXES_EXT,&faxes);
      fprintf(stderr,"Writing axes file                 : %s\n",GetFileFullName(&faxes));
      fout=fopen(GetFileFullName(&faxes),"w");
      if (!fout)
	Error("The file for the axes can not be opened");
    
      do {
	token=ReadBox(fin,&box);
	if (token!=EOF)
	  {
	    if (nvs>GetBoxNIntervals(&box))
	      Error("Box size missmatch");
	    PrintWorldAxes(&parameters,fout,&box,&world);
	    DeleteBox(&box);
	  }
      } while(token!=EOF);
      
      fclose(fin);
      fclose(fout);

      DeleteFileName(&faxes);  
      DeleteFileName(&fsols);      
      DeleteFileName(&fparam);

      DeleteWorld(&world);
      DeleteParameters(&parameters);
    }
  else
    {
      fprintf(stdout,"  Wrong number of parameters.\n");
      fprintf(stdout,"  Use:\n");
      fprintf(stdout,"     cuikworldaxes <world>.world <solutions>.sol\n");
      fprintf(stdout,"  Where:\n");
      fprintf(stdout,"     <world>:  File describing the problem\n");
      fprintf(stdout,"     <solutions>:  Solutions for which to extract the axes.\n");
      fprintf(stdout,"  File extensions are not required\n");
    }
    
  return(EXIT_SUCCESS);
}
