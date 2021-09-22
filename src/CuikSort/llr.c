/*  
 * LLR 0.1 
 * List Library 0.2
 * (c) Lluis Ros 1995-2005
 *
 * Filename: llr.c
 * Creation: April 1995
 * Last revision: December 2005
 *
 * What are LLR and GLR?
 *
 *    LLR (List Library)
 *      is a library of functions to handle lists.
 *
 *    GLR (Graph Library)
 *      is a library of functions to handle (undirected) graphs. The 
 *      implementation of GLR's functions makes use of many (low level)
 *      functions included in LLR. The functions are compiled and grouped
 *      in libglr.a. Basically, the routines in GLR allow to create a 
 *      (non-directed) graph and work with it: create/destroy nodes/branches, 
 *      perform depth-first searches, find the set of fundamental cycles, 
 *      count the number of spanning trees in a graph, and so on.
 *
 * Who designed the code in LLR and GLR?
 *
 *    LLR:
 *      The major part of the code in LLR has been taken from the book by 
 *      Jeffrey Esakov & Tom Weiss "Data Structures, an Advanced Approach Using C".
 *      These are: allocate_node, free_node, init_list, empty_list, insert, append delete,
 *      delete_node, find_key, list_iterator, destroy_list. The rest of routines are 
 *      by myself (concatenate, length,print_prolog_list...).
 * 
 *    GLR:
 *      All routines are by myself. However, you'll see they follow Esakov & Weiss's programming
 *      style. The code in GLR implements most of this book's primitive operations over the
 *      'graph abstract data type' and many others I added. The main difference between my
 *      implementation of the basic primitive operations and Esakov's is that I do not assume 
 *      a "static" vertex set. That is: you may add or remove vertices from the graph as the 
 *      computations go on. To this end, the set of vertices has been stored in a dynamic list 
 *      rather than in a statically-dimensioned vector. Another difference is that I allow 
 *      vertices to have the label you want (in Esakov's implementation they must be numbered 
 *      from 1 to n). Finally, both edges and vertices may store information (only edges can in
 *      Esakov's).
 *
 * Acknowledgements: 
 *
 *    Special thanks to Pablo Jimenez, Manel Guerris, Albert Castellet, Gorka Bonals, and 
 *    Josep M. Porta for using LLR/GLR 0.1 and act as beta-testers. They suggested several
 *    improvements of the code and its documentation.
 */

#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "llr.h"

/*----------------------------------------------------------------------------------------------------*/
status allocate_node(llist* p_L, generic_ptr data)
/*
 * allocate_node() performs memory allocation for a list node. *p_L returns the
 * memory address where the node is being stored. The NEXT field is initialized 
 * to NULL (because at this moment the node is not yet linked to the list). The
 * node must store "data", and hence "data" is assigned to the node's DATA field.
 * allocate_node() returns ERROR if the memory allocation failed, OK otherwise.
 */
{
    llist L;
    
    L=(llist)malloc(sizeof(node));
    if(L==NULL) return ERROR;
    
    *p_L=L;
    DATA(L)=data;
    NEXT(L)=NULL;
    
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
void free_node(llist *p_L)
/* 
 * free_node() frees the memory space occupied by the node pointed to by *p_L.
 * Caution free_node() does not free the space occupied by the data that can be
 * reached through DATA(*p_L). This consideration must be taken into account by
 * any higher-level function that uses free_node(). See delete_node() and 
 * destroy_list() below. 
 * No error checking is performed, since it is difficult that free() fails, unless 
 * you pass an invalid/wrong address, and this is difficult to detect.
 */
{
    free(*p_L);
    *p_L=NULL;
}
/*----------------------------------------------------------------------------------------------------*/
status init_list(llist* p_L)
/*
 * As any other variable, a list variable must be declared and initialized. We
 * declare lists by stating:
 *                        "list listname;"
 * We initialize lists by stating:
 *                        initlist(*listaname);
 */
{
    *p_L=NULL;
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
boolean empty_list(llist L)
/*
 * Returns TRUE/FALSE if list L is empty/not-empty.
 */ 
{
    return ((L==NULL) ? TRUE : FALSE);
}
/*----------------------------------------------------------------------------------------------------*/
status insert(llist* p_L, generic_ptr data)
/*
 * insert() adds a new node to the begining of the list pointed to by *p_L.
 * Stores the data "data" in this node. Since we add the node at
 * the beginning of the list, *p_L will always change. Hence we declare
 * list* p_L (instead of list L) to give back the new address of the list.
 * IMPORTANT: we must cast data to the type generic_ptr in any call to
 * insert().
 * Returns ERROR if the memory allocation failed for this node. OK otherwise.
 */
{
    llist L;
    
    if(allocate_node(&L, data) == ERROR)
	return ERROR;
    
    NEXT(L)=*p_L;
    *p_L=L;
    
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status append(llist* p_L, generic_ptr data)
/*
 * append() adds a new node to the end of the list pointed to by 
 * *p_L. Stores the data "data" in this node. We declare list* p_L 
 * (instead of list L) since the list might possibly be empty.
 * IMPORTANT: we must cast data to the type generic_ptr in any call to
 * append(). * 
 * Returns ERROR if the memory allocation failed for this node. OK 
 * otherwise.
 */
{
    llist L, tmplist;
    
    if(allocate_node(&L, data)==ERROR)
	return ERROR;
    
    if(empty_list(*p_L)==TRUE)
	*p_L=L;
    else
    {
	for(tmplist=*p_L;NEXT(tmplist)!=NULL; tmplist=NEXT(tmplist));
	NEXT(tmplist)=L;
    }
    
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status delete_first(llist* p_L, generic_ptr* p_data, void (*p_func_f)(void*))
/* 
 * delete_first() deletes the first node of the list pointed to by 
 * *p_L. It returns the data stored in this node through the output
 * parameter p_data. The (old) second node of the list is passed to
 * be the first now. Since the deletion of the first node is a particular
 * case of deleting any node in a list, we implement delete_first() by
 * calling another primitive operation: delete_node(). 
 *
 * ON FREEING  USER DEFINED DATA:
 *    Since the list abstract data type is a polymorphic type, we don't
 *    know the structure of the data stored in the DATA field of a node.
 *    Hence, we cannot define a generic function that frees this data.
 *    It is the user who must write an specific function that frees all
 *    the memory space accessible through "DATA(list_node)". We provide 
 *    a means to pass the address of this user-defined "free_function" by
 *    adding the third parameter void (*p_func_f)(). The user defined
 *    function must look like this:
 *    void free_user_data(generic_ptr* data)
 */
{
    if(empty_list(*p_L)) return ERROR;
    *p_data=DATA(*p_L);
    return delete_node(p_L, *p_L, p_func_f);
}
/*----------------------------------------------------------------------------------------------------*/
status delete_node(llist* p_L, llist node, void (*p_func_f)(void*))
{
    if(empty_list(*p_L)==TRUE) return ERROR;
    
    /* si node es el primer */
    if(*p_L==node)
    {
	*p_L=NEXT(*p_L);
    }
    else
    {
	/* node no es el primer i el busquem */
        llist L;
	for(L=*p_L; L!=NULL && NEXT(L)!=node; L=NEXT(L));
	if(L==NULL)
	    return ERROR;
	else
	    NEXT(L)=NEXT(node);
    }
    if(p_func_f!=NULL)
	(*p_func_f)(DATA(node));
    free_node(&node);
    
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status find_key(llist L, generic_ptr key, int (*p_cmp_f)(generic_ptr,generic_ptr), llist* p_keynode)
{
    llist curr=NULL;

    while( (curr=list_iterator(L,curr))!=NULL)
    {
	if((*p_cmp_f)(key, DATA(curr))==0)
	{
	    *p_keynode=curr;
	    return OK;
	}
    }
    return ERROR;
}
/*----------------------------------------------------------------------------------------------------*/
llist list_iterator(llist L, llist lastreturn)
{
	return (lastreturn==NULL)? L : NEXT(lastreturn);
}
/*----------------------------------------------------------------------------------------------------*/
void destroy_list(llist* p_L, void (*p_func_f)(void *))
{
  if (empty_list(*p_L)==FALSE) {
    destroy_list(&NEXT(*p_L), p_func_f);
    if(p_func_f!=NULL) {
      /* 
       * (*p_func_f)(generic_ptr data) fa un free del que s'emmagatzema a DATA(*p_L)
       * però després cal posar DATA(*p_L) a NULL: per si les mosques.
       */
      (*p_func_f)(DATA(*p_L));
      DATA(*p_L)=NULL;
    }
    free_node(p_L);
  }
}
/*----------------------------------------------------------------------------------------------------*/
int length(llist L)
/*
 * Obtains the length of the list L.
 */
{
  int len=0;
  llist curr=NULL;
  while( (curr=list_iterator(L,curr))!=NULL)
    len++;
  return len;
}
/*-----------------------------------------------------------------------------------------------*/
llist first(llist L)
/* 
 * Returns a pointer to the first element of L
 */
{
  return L;
}
/*-----------------------------------------------------------------------------------------------*/
llist last(llist L)
/* 
 * Returns a pointer to the last element of L
 */
{
  llist curr=NULL;
  if(L==NULL) return NULL;
  for(curr=L; NEXT(curr)!=NULL; curr=NEXT(curr));
  return curr;
}
/*----------------------------------------------------------------------------------------------------*/
status concatenate(llist* p_list1, llist* p_list2)
/*
 * Concatenates 2 lists. Appends list2 to list1 leaving list2 unchanged. 
 * It does not copy the contents of list2 to list1, but connects them through pointers.
 *  - If *p_list1 is NULL ( and *p_list2 isn't ), on return 
 *    *p_list1 contains the same address as *p_list2. 
 *  - If *p_list2 is NULL (and *p_list1 isn't) then list1 remains unchanged.
 *  - If both *p_list1 and *p_list2 are NULL concatenate returns an ERROR.
 */
{
  llist L;
  if(*p_list1==NULL && *p_list2==NULL) 
    return ERROR;
  if(*p_list2==NULL)
    return OK;
  if(*p_list1==NULL)
  {
    *p_list1=*p_list2;
    return OK;
  }
  /* *p_list1 is not NULL: get a pointer to the last element */
  for(L=*p_list1; NEXT(L)!=NULL; L=NEXT(L));
  /* concatenate */
  NEXT(L)=*p_list2;
  return OK;
}
/*-----------------------------------------------------------------------------------------------*/
void print_prolog_list(FILE* fd, llist alist, void (*p_print_funct)(FILE*,llist))
/*
 * Prints the contents of a list to an ascii file, in a Prolog-like syntax
 */
{
  llist L;

  fprintf(fd, "[");
  if(alist!=NULL)
  {
    (*p_print_funct)(fd, alist);
    
    for(L=NEXT(alist); L!=NULL; L=NEXT(L))
    {
      fprintf(fd, ",");
      (*p_print_funct)(fd, L);
    }
  }
  fprintf(fd, "]");
}
/*-----------------------------------------------------------------------------------------------*/
status copy_list(llist List1, llist* p_List2, status (*p_cp_dat)(generic_ptr,generic_ptr*))
{
  llist curr=NULL;       /* pointer to the node under treatment  */
  generic_ptr data;   /* pointer to the data of the node curr */

  if(init_list(p_List2)==ERROR)
    return(ERROR);

  while((curr=list_iterator(List1, curr)) != NULL)
    if((*p_cp_dat)(DATA(curr), &data)==OK) {
      if(append(p_List2, data)==ERROR)
	return(ERROR);
    } 
    else {
      return(ERROR);
    }

  return(OK);
}


