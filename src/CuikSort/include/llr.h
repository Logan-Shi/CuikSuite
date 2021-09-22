
#ifndef LLRH
#define LLRH

/*******************************************************************
 * LLR 0.1 
 * List Library 0.2
 * (c) Lluis Ros 1995-2005
 *
 * Filename: llr.h
 * Creation: April 1995
 * Last revision: December 2005
 * 
 *******************************************************************/

#include "general.h"
#include <stdio.h>

/*
 *  List types and prototypes
 */

typedef struct node node;
typedef struct node* llist;
struct node {
    generic_ptr datapointer;
    llist next;
};

/* 
 * List type accessor macros
 */

#define DATA(L) ((L)->datapointer)
#define NEXT(L) ((L)->next)

/*
 * Prototypes of public operations of the list abstract data type
 */

status  init_list(llist *p_L);
boolean empty_list(llist L);
status  append(llist *p_L, generic_ptr data);
status  insert(llist *p_L, generic_ptr data);
status  delete_first(llist* p_L, generic_ptr* p_data, void (*p_func_f)(void*));
status  delete_node(llist* p_L, llist node, void (*p_func_f)(void*));
status  find_key(llist L, generic_ptr key, int (*p_cmp_f)(generic_ptr,generic_ptr), llist* p_keynode);
llist    list_iterator(llist L, llist lastreturn);
void    destroy_list(llist* p_L, void (*p_func_f)(void*));
int     length(llist L);
llist    last(llist L);
llist    first(llist L);
void    free_node(llist *p_L);
status  concatenate(llist* p_list1, llist* p_list2);
void    print_prolog_list(FILE* fd, llist alist, void (*p_print_funct)(FILE*,llist));
status  copy_list(llist List1, llist* p_List2, status (*p_cp_dat)(generic_ptr,generic_ptr*));

#endif /* LLRH */
