
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "filename.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/** \file cuikmergeboxes.c

    \brief Main body of the \ref cuikmergeboxes.c "cuikmergeboxes" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikmergeboxes    [label="cuikmergeboxes"  color="#99ff99" shape=ellipse];
      
      solIn   [label="sol"    color="#ff9999" ];
      solOut  [label="_suffix.sol"    color="#ff9999" ];

      solIn -> cuikmergeboxes;
      cuikmergeboxes -> solOut;
    }
    \enddot
    </center>

     A utility to merge boxes in different files. 

    \sa cuiksystem.h cuiksystem.c 
*/

/**
   \brief Main body of the  \ref cuikmergeboxes.c "cuikmergeboxes" application.

   Main body of the \ref cuikmergeboxes.c "cuikmergeboxes" application.

   Use:
       - \b cuikmergeboxes \e suffix \e files.sol
       .
   where
       - \e suffix Is the suffix added to the output cuiksystem.
       - \e files Are the sol files with the boxes to merge.
       .
   The \e .sol  extensions are optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksimplify command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  Tbox bin,bout;

  Tfilename fsol;
  
  unsigned int i,n;
  FILE **fs,*fout;
  int token;
  
  if (argc>2)
    {
      n=argc-2;
      NEW(fs,n,FILE *);

      for(i=0;i<n;i++)
	{
	  CreateFileName(NULL,arg[2+i],NULL,SOL_EXT,&fsol);
	  #if (_DEBUG>0)
	    printf("Reading sol file               : %s\n",GetFileFullName(&fsol));
	  #endif
	  fs[i]=fopen(GetFileFullName(&fsol),"r");
	  if (!fs[i])
	    Error("Sol file does not exists in cuikmergeboxes");
	  DeleteFileName(&fsol);
	}

      CreateFileName(NULL,arg[2],arg[1],SOL_EXT,&fsol);
      fout=fopen(GetFileFullName(&fsol),"w");
      if (!fout)
	Error("Could not open the output file for the merged cuiksystem.");
      #if (_DEBUG>0)
        printf("Generating merged sol file     : %s\n",GetFileFullName(&fsol));
      #endif
      DeleteFileName(&fsol);
	
      token=~EOF;
      while(token!=EOF)
	{
	  i=0;
	  while((i<n)&&(token!=EOF))
	    {
	      token=ReadBox(fs[i],&bin);
	      if (token!=EOF)
		{
		  if (i==0)
		    CopyBox(&bout,&bin);
		  else
		    MergeBoxes(&bout,&bin,&bout);
		  DeleteBox(&bin);
		  i++;
		}
	    }
	  if (i==n)
	    PrintBox(fout,&bout);
	  if (i>0)
	    DeleteBox(&bout);
	}

      for(i=0;i<n;i++)
	fclose(fs[i]);
      fclose(fout);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikmergeboxes <suffx> <problem filenames>.sol \n");
     fprintf(stderr,"  where <problem filenames> contains the kinematic equations to merge\n");
     fprintf(stderr,"    (the '.cuik' extension is not required)\n");
   }
  return(EXIT_SUCCESS);
}

