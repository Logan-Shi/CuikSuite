#include "box_list.h"

#include "interval.h"

#include "boolean.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \file box_list.c
    \brief Implementation of the functions operating on box Tlist.

    Implementation of the functions operating on Tlist with Tbox
    as a basic type.

    \sa box_list.h, list.h, Tlist, Tbox.
*/

/*
 * Starts a list of boxes
 */
void InitListOfBoxes(Tlist *l)
{
  InitList(sizeof(Tbox),l);
}

void CopyListOfBoxes(Tlist *l_dst,Tlist *l_src)
{
  Titerator i;
  Tbox b;

  InitListOfBoxes(l_dst);

  InitIterator(&i,l_src);
  First(&i);  
  while(!EndOfList(&i))
    {
      CopyBox(&b,(Tbox *)GetCurrent(&i));
      AddLastElement((void *)&b,l_dst);
      Advance(&i);
    }
}

/*
 * Returns the total volume of the box stored in the list
 * (normalized using t_trans and t_rot)
 */
double ListOfBoxesVolume(boolean *used,Tlist *l)
{
  double v;
  Titerator i;

  InitIterator(&i,l);
  First(&i); 
  v=0.0;
  while(!EndOfList(&i))
    {
      v+=GetBoxVolume(used,(Tbox *)GetCurrent(&i));
      Advance(&i);
    }

  return(v);
}

/*
 * Returns the maximum diagonal for all boxes in the list
 */
double ListOfBoxesMaxDiagonal(boolean *used,Tlist *l)
{
  double d,d_max;
  Titerator i;

  InitIterator(&i,l);
  First(&i);
  d_max=0.0;
  while(!EndOfList(&i))
    {
      d=GetBoxDiagonal(used,(Tbox *)GetCurrent(&i));
      if (d>d_max) d_max=d;
      Advance(&i);
    }

  return(d_max);
}

/*
 * Returns the maximum size for all boxes in the list
 */
double ListOfBoxesMaxSize(boolean *used,Tlist *l)
{
  double s,s_max;
  Titerator i;

  InitIterator(&i,l);
  First(&i);
  s_max=0.0;
  while(!EndOfList(&i))
    {
      s=GetBoxSize(used,(Tbox *)GetCurrent(&i));
      if (s>s_max) s_max=s;
      Advance(&i);
    }

  return(s_max);
}

/*
 * Returns a box that fully includes all boxes in the list.
 * If the list is empty so is the box.
 */
void ListOfBoxesBB(boolean *used,Tbox *b,Tlist *l)
{
  if (ListSize(l)==0)
    InitBox(0,NULL,b);
  else
    {
        Titerator i;

	InitIterator(&i,l);
	First(&i);
	CopyBox(b,(Tbox *)GetCurrent(&i));
	Advance(&i);  
	while(!EndOfList(&i))
	  {
	    BoxUnion(used,(Tbox *)GetCurrent(&i),b,b);
	    Advance(&i);
	  }
    }
}


/*
 * Returns a list with the bounding boxes for all clusters of boxes
 * in l_in. 
 */
void ListOfBoxesCluster(boolean *used,Tlist *l_out,Tlist *l_in)
{
  unsigned int k,n,l,t;
  Titerator i;
  Titerator j;
  Titerator c;
  Tbox *b2,*b3,b_out,*cb;
  boolean modified;
  unsigned int *cluster,nc;

  /*Number of boxes to be clustered*/
  n=ListSize(l_in);

 /*Initially we have no cluster*/
  NEW(cluster,n,unsigned int);
  nc=0;
  for(k=0;k<n;k++)
    cluster[k]=(unsigned int)(-1);

  /*Initially the output is empty*/
  InitListOfBoxes(l_out);

  /*Proceed for all boxes in the input list not yet clustered*/
  InitIterator(&i,l_in);
  First(&i);
  k=0;
  while(!EndOfList(&i))
    {
      if (cluster[k]==(unsigned int)(-1)) /*= not clustered*/
	{
	  /*Start a new cluster*/
	  nc++;
	  cluster[k]=nc; 
	  NEW(cb,1,Tbox);
	  CopyBox(cb,(Tbox *)GetCurrent(&i)); /*'cb' is the bounding box for all boxes in the cluster*/

	  do {

	    /*For all boxes still to be clustered*/
	    modified=FALSE; /*Initally we assume the cluster to remain as it is now*/

	    /*and we check for the rest of boxes in the input list whether or not they
	      can be included in the current cluster*/
	    InitIterator(&j,l_in);
	    First(&j);
	    l=0;
	    while(!EndOfList(&j))
	      {
		if (cluster[l]==(unsigned int)(-1)) /*the box in not yet assigned to any cluster*/
		  {
		    b2=(Tbox *)GetCurrent(&j); /*this is the box candidate to joint the current cluster*/

		    /*Check if the non-clustered box has contact with one of the
		      boxes already in cluster 'nc'=cluster[k]*/
		    InitIterator(&c,l_in);
		    First(&c);
		    t=0;
		    while(!EndOfList(&c))
		      {
			if (cluster[t]==cluster[k])
			  {
			    b3=(Tbox *)GetCurrent(&c); /*This is a box already in cluster 'nc'*/
			    CopyBox(&b_out,b3);
			    if (BoxesIntersection(used,b2,b3,&b_out))
			      {
				cluster[l]=nc; /*box b2 (number 'l') is included in the current cluster*/
				BoxUnion(NULL,cb,b2,cb); /*Enlarge the cluster bounding box*/

				modified=TRUE; /*Indicate the current cluster has been modified*/
			      }
			    DeleteBox(&b_out); /*bout is an auxiliary box that must be deleted*/
			  }
			Advance(&c);
			t++;
		      }
		  }
		Advance(&j);
		l++;
	      }
	  } while(modified); /* If we added one or more boxex to the cluster we have to check whether
			        or not the cluster can be still extended*/


	  AddLastElement((void *)cb,l_out); /*Add the bounding box of the current cluster to the output list*/
	}
      Advance(&i);
      k++;
    }
  free(cluster);
}


void ConcatListOfBoxes(Tlist *l_new,Tlist *l)
{
  Titerator i;
  Tbox b;

  InitIterator(&i,l_new);
  First(&i);
  while(!EndOfList(&i))
    { 
      CopyBox(&b,(Tbox *)GetCurrent(&i));
      AddLastElement((void *)&b,l);
      Advance(&i);
    }
}

void ReverseListOfBoxes(Tlist *l_orig,Tlist *l)
{
  Titerator i;
  Tbox b;

  InitListOfBoxes(l);

  InitIterator(&i,l_orig);
  First(&i);
  while(!EndOfList(&i))
    { 
      CopyBox(&b,(Tbox *)GetCurrent(&i));
      AddFirstElement((void *)&b,l);
      Advance(&i);
    }
}

/*
 * Prints a given list of boxes
 */
void PrintListOfBoxes(FILE *f,boolean *used,char *heading,Tlist *l)
{
  Titerator i;
  unsigned int k;

  InitIterator(&i,l);
  First(&i);
  k=1;
  while(!EndOfList(&i))
    {	       
      if (heading!=NULL) fprintf(f,"%s ",heading);
      fprintf(f,"%u : ",k++);
      PrintBoxSubset(f,used,NULL,(Tbox *)GetCurrent(&i));
      Advance(&i);
    }
  fflush(f);
}

/*
 * Read a list of boxes from a file (wrote by cuik).
 */
boolean ReadListOfBoxes(char *filename,Tlist *l)
{
  FILE *PSin;
  int token=~EOF; 
  Tbox box;

  InitList(sizeof(Tbox),l);

  PSin=fopen(filename,"r");
  if (PSin)
    {
      do {
	//read a box from the file
	token=ReadBox(PSin,&box);
	//if we got a proper box (no end of file)...
	if (token!=EOF)
	  {
	    //and add the box to the list (this re-uses the
	    //intervals in 'box' so there is no need to call
	    //DeleteBox(&box) afterwards
	    AddLastElement((void *)&box,l);
	  }
      } while (token!=EOF);
      return(TRUE);
    }
  else
    return(FALSE);
}

/* Now the binary alternatives to save/load boxes */
void SaveListOfBoxes(FILE *f,Tlist *list)
{
  unsigned int n;
  Titerator i;

  n=ListSize(list);
  fwrite(&n,sizeof(unsigned int),1,f);

  InitIterator(&i,list);
  First(&i);
  n=0;
  while(!EndOfList(&i))
    {
      SaveBox(f,(Tbox *)GetCurrent(&i));
      Advance(&i);
    }
}

void LoadListOfBoxes(FILE *f,Tlist *list)
{
  unsigned int i,n;
  Tbox box;

  fread(&n,sizeof(unsigned int),1,f);

  InitListOfBoxes(list);

  for(i=0;i<n;i++)
    {
      LoadBox(f,&box);
      AddLastElement((void *)&box,list);
    }
}

/*
 * Deletes a given list of boxes
 */
void DeleteListOfBoxes(Tlist *l)
{
  Titerator i;

  InitIterator(&i,l);
  First(&i);
  while(!EndOfList(&i))
    {
      DeleteBox((Tbox *)GetCurrent(&i));
      DeleteCurrent(&i);
    }
}

