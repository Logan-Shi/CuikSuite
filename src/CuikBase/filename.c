#include "filename.h"

#include "error.h"
#include "defines.h"
#include "boolean.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** 
   \file filename.c

   \brief Implementation of the functions operating on sets of Tfilename.

    Functions to deal with Tfilename.

   \sa filename.h, Tfilename .
*/

void CreateFileName(char *path,char *name,char *suffix,char *ext,Tfilename *fn)
{
  char *p,*e;
  signed int len,lp,lPath,lNameOnly,lName,lSuffix,lExt,slashPos,dotPos,prot;
  boolean found;

  /* The actual file name is the string between the last '/' in the input name 
     and the first '.' after the '/'
     The string before the '/' is part of the path and the string after the '.'
     is the extension. 
     The path is added to the global path and the extension is discarted
     if the user provides an extension as a parameter or used, otherwise.
  */
  len=strlen(name);
  
  /*look for the last '/' in the given name*/
  slashPos=len-1;
  while((slashPos>=0)&&(name[slashPos]!='/'))
    slashPos--;
  
  dotPos=(slashPos>0?slashPos:0);
  while((dotPos<len)&&(name[dotPos]!='.'))
    dotPos++;

  /* skip the protocal, if any. Some filenames start with "file://" or "http://" 
     We must skip this part if present */
  found=FALSE;
  prot=0;
  while((!found)&&(prot<slashPos-1))
    {
      found=((name[prot]==':')&&(name[prot+1]=='/')&&(name[prot+2]=='/'));
      if (!found)
	prot++;
    }
  if (found)
    prot+=3;
  else
    prot=0;

  /*Set up the path = 'p' + part of the name till the last '/' */ 
  /*The path is either the given one or the one from the system*/
  if (name[prot]=='/')
    {
      /*The given name is a full path name*/
      lPath=slashPos+1;
      NEW(fn->path,lPath+1,char);
      memcpy(fn->path,&(name[prot]),(slashPos-prot)*sizeof(char));
    }
  else
    {
      if (path==NULL)
	p=getcwd(NULL,0);
      else 
	p=path;
      lp=strlen(p);
      /* if the path includes a '/' at the end remove it. It will
         be added latter. */
      if (p[lp-1]=='/')
	lp--;
    
      lPath=lp+(slashPos-prot)+2;
      if (lPath==0)
	Error("Empty file path");
      NEW(fn->path,lPath+1,char);
      memcpy(fn->path,p,lp*sizeof(char));
      fn->path[lp]='/';
      if ((slashPos-prot)>=0)
	memcpy(&(fn->path[lp+1]),&(name[prot]),(slashPos-prot)*sizeof(char));
      if (path==NULL)
      	free(p);
    }
  if (fn->path[lPath-2]!='/')
    {
      fn->path[lPath-1]='/';
      fn->path[lPath]=0;
    }
  else
    fn->path[lPath-1]=0;

  /*Set up the name */
  if (suffix==NULL)
    lSuffix=0;
  else
    lSuffix=strlen(suffix);
  lNameOnly=dotPos-slashPos-1;
  lName=lNameOnly+lSuffix;
  if (lName==0)
    Error("Empty file name");
  NEW(fn->name,lName+1,char);
  memcpy(fn->name,&(name[slashPos+1]),lNameOnly*sizeof(char));
  if (lSuffix>0)
    memcpy(&(fn->name[lNameOnly]),suffix,lSuffix*sizeof(char));
  fn->name[lName]=0;

  /*Set up the extension*/
  if (ext!=NULL)
    e=ext;
  else
    {
      if (dotPos==len)
	e=NULL;
      else
	e=&(name[dotPos+1]);
    }

  if (e==NULL) lExt=0;
  else lExt=strlen(e);

  if (lExt>0)
    {
      NEW(fn->ext,lExt+1,char);
      memcpy(fn->ext,e,lExt*sizeof(char));
      fn->ext[lExt]=0;
    }
  else
    fn->ext=NULL;

  /* concat everything but the extension in the basename */
  NEW(fn->baseName,lPath+lName+2,char);
  sprintf(fn->baseName,"%s%s",fn->path,fn->name);

  /* concat everything in the full name */
  NEW(fn->fullName,lPath+lName+lExt+2,char);
  if (lExt>0)
    sprintf(fn->fullName,"%s%s.%s",fn->path,fn->name,fn->ext);
  else
    sprintf(fn->fullName,"%s%s",fn->path,fn->name);
}

char *GetFileFullName(Tfilename *fn)
{
  return(fn->fullName);
}

char *GetFilePath(Tfilename *fn)
{
  return(fn->path);
}

char *GetFileName(Tfilename *fn)
{
  return(fn->name);
}

char *GetFileBaseName(Tfilename *fn)
{
  return(fn->baseName);
}

char *GetFileExtension(Tfilename *fn)
{
  return(fn->ext);
}


void LinkFileNameWithExtension(char *fn1,char *ext,Tfilename *fn2)
{
  FILE *f;
  Tfilename fin,fout;

  /* Create a symbolic link, if it original file exists
     If a the new file exist, we remove it. */
  CreateFileName(NULL,fn1,NULL,ext,&fin);
  f=fopen(GetFileFullName(&fin),"r");
  if (f)
    {
      fclose(f);
      CreateFileName(GetFilePath(fn2),GetFileName(fn2),NULL,ext,&fout);
      f=fopen(GetFileFullName(&fout),"r");
      if (f)
	{
	  fclose(f);
	  remove(GetFileFullName(&fout));
	}
      symlink(GetFileFullName(&fin),GetFileFullName(&fout));
      #if (_DEBUG>0)
        printf("Linking file                      : %s (-> %s)\n",GetFileFullName(&fout),GetFileFullName(&fin));
      #endif
      DeleteFileName(&fout);
    }
  DeleteFileName(&fin);
}

void DeleteFileName(Tfilename *fn)
{
  free(fn->path);
  free(fn->name);
  if (fn->ext!=NULL) free(fn->ext);
  free(fn->baseName);
  free(fn->fullName);
}
