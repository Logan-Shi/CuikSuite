
#include "box.h"

#include "defines.h"
#include "filename.h"

#include <string.h>


/** \file cuikatan2.c

    \brief Main body of the \ref cuikatan2.c "cuikatan2" application.
   
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikatan2    [label="cuikatan2"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      solIn   [label="sol"     color="#ff9999" ];
      solOut  [label="sol"     color="#ff9999" ];

      param -> cuikatan2
      solIn -> cuikatan2;
      cuikatan2 -> solOut;
    }
    \enddot
    </center>

     A utility to transform boxes with sin/cos to boxes with the
     correponding angles.
*/

/** 
   \brief Main body of the  \ref cuikatan2.c "cuikatan2" application.

   Main body of the \ref cuikatan2.c "cuikatan2" application.

   Use:
       - \b cuikatan2 \e input_name.sol \e dim_sin_1 \e dim_cos_1 ... \e dim_sin_n \e dim_cos_n \e output_name.sol
       .
   where
       - \e input_name contains the original boxes (those with sin/cos).
       - \e dim_sin_i the variable for the sinus for the \e i-th angle.
       - \e dim_cos_i the variable for the cosinus for the \e i-th angle.
       - \e output_name file to be generated contains the boxes with
                        angular variables.
       .
   The \e .sol  extensions are optional.

   \param argc Number of elements in the command line that starts the 
               application (i.e., the \b cuikatan2 command itself 
               and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and 
           EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  FILE *fileIn,*fileOut;
  Tbox boxIn,boxOut;
  Tinterval iAtan2;
  unsigned int *map,*dimSin,*dimCos,nIn,nOut;
  unsigned int k,l,t,na,nbox;
  int token;
  Tfilename fIn,fOut;
  boolean found;

  if ((argc<4)||((argc%2)==0))
    {
      fprintf(stderr,"Use:\n");
      fprintf(stderr,"  cuikatan2 <input_file> <dim_sin_1> <dim_cos_1> ... <dim_sin_n> <dim_cos_n>  <output_file>\n");
      fprintf(stderr,"    <input_file> the input .sol file\n");
      fprintf(stderr,"    <dim_sin_i> <dim_cos_i> the sin/cos dimensions (numbered from 1)\n");
      fprintf(stderr,"    <output_file> the .sol file to be generated\n");
    }
  else
    {
      CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fIn);
      CreateFileName(NULL,arg[argc-1],NULL,SOL_EXT,&fOut);
  
      fileIn=fopen(GetFileFullName(&fIn),"r");
      if (!fileIn)
	Error("Input file can not be opened");

      fileOut=fopen(GetFileFullName(&fOut),"w");
      if (!fileOut)
	Error("Output file can not be opened");


      na=(argc-3)/2;
      NEW(dimSin,na,unsigned int);
      NEW(dimCos,na,unsigned int);
      
      for(k=0;k<na;k++)
	{
	  dimSin[k]=(unsigned int)atoi(arg[2+2*k])-1;
	  dimCos[k]=(unsigned int)atoi(arg[3+2*k])-1;
	}

      nbox=0;
      do {
	token=ReadBox(fileIn,&boxIn);
	if (token!=EOF)
	  {
	    if (nbox==0)
	      {
		nIn=GetBoxNIntervals(&boxIn);

		nOut=nIn-na;

		NEW(map,nOut-na,unsigned int);
		l=0;
		for(k=0;k<nIn;k++)
		  {
		    found=FALSE;
		    t=0;
		    while((!found)&&(t<na))
		      {
			found=((k==dimSin[t])||(k==dimCos[t]));
			t++;
		      }
		    if (!found)
		      {
			map[l]=k;
			l++;
		      }
		  }
	      }

	    InitBox(nOut,NULL,&boxOut);
	    for(k=0;k<nOut-na;k++)
	      SetBoxInterval(k,GetBoxInterval(map[k],&boxIn),&boxOut);
	    
	    for(k=0;k<na;k++)
	      {
		IntervalAtan2(GetBoxInterval(dimSin[k],&boxIn),
			      GetBoxInterval(dimCos[k],&boxIn),
			      &iAtan2);
		SetBoxInterval(nOut-na+k,&iAtan2,&boxOut);
		DeleteInterval(&iAtan2);
	      }

	    PrintBox(fileOut,&boxOut);

	    DeleteBox(&boxIn);
	    DeleteBox(&boxOut);

	    nbox++;
	  }	
      } while (token!=EOF);
      

      fclose(fileIn);
      fclose(fileOut);


      if (nbox>0)
	free(map);
      free(dimSin);
      free(dimCos);

      DeleteFileName(&fIn);
      DeleteFileName(&fOut);
      
    }
  return(EXIT_SUCCESS);
}
