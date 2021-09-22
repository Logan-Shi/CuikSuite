/*  
 * GLR 0.1 
 * Graph Library 0.2
 * (c) Lluis Ros 1995-2005
 *
 * Filename: glr.c
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
 *
 * The functions are organized into the following sections:
 *
 *    Section 1 - Graph constructors
 *        Functions to construct a graph, and add individual vertices and edges
 *    Section 2 - Graph destructors
 *        Functions to destruct a graph, and delete individual vertices and edges
 *    Section 3 - Graph traverse functions
 *        Functions to perform actions on vertices/edges while traversing the graph
 *    Section 4 - Detection of fundamental cycles and connected components
 *        Functions to compute a fundamental cycle basis and detect connected components
 *    Section 5 - Graph analysis functions
 *        Functions to analyze the graph (count #vertices, #edges, #components, #cycles,...)
 *    Section 6 - Graph printing functions
 *        Functions to print the graph, and related data structures
 *    Section 7 - Miscelaneous functions
 *        Miscelaneous functions
 *
 * Acknowledgements: 
 *
 *    Special thanks to Pablo Jimenez, Manel Guerris, Albert Castellet, Gorka Bonals, and 
 *    Josep M. Porta for using LLR/GLR 0.1 and act as beta-testers. They suggested several
 *    improvements of the code and its documentation.
 *
 * Wish list:
 *
 * - Generate a minimal documentation for LLR/GLR!
 * - We distinguish between graph, graph_vertex and graph_edge in all function prototypes.
 *   To be formally consistent, we should do so in the functions' body too. Now all of 
 *   them are simply lists there.
 * - Remove all static variables (e.g. in cycle_search and find_fundamental_cycles)
 * - Name all vertex pointers equally: now we have "pv", "curr", "vertex_pointer", ...
 * - cycle_search() should probably replicate the data fields of the vertices/edges, instead of
 *   storing pointers to them. 
 * - Review when does cycle_search backtrack().
 * - Can we succintly modify GLR to handle digraphs. I guess not.
 */


#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "llr.h"
#include "glr.h"

/* 
 * Private function prototypes 
 */

static status simply_visit(graph_vertex vertex_pointer);
static status find_fundamental_cycles(graph G, 
				      graph_vertex vertex_pointer, 
				      boolean (*p_is_reachable)(llist,llist), 
				      llist* cycles);
static status cycle_search(graph_vertex curr_vertex, 
			   graph_edge curr_edge, 
			   graph_vertex end_vertex, 
			   int label, 
			   llist* vertices, llist* edges);
static status recursive_count_vertices_edges_component(graph_vertex curr_vertex, 
						       int* nvertices, int* nedges);
static void   free_vertex_data(generic_ptr data);
static void   free_edge_data(generic_ptr data);

/*****************************************************************************************************
 *
 *  Section 1 - Graph constructors
 *
 *****************************************************************************************************/

status init_graph(graph* p_G)
{
    return(init_list(p_G));
}
/*----------------------------------------------------------------------------------------------------*/
status add_vertex(graph* p_G, vertex_id vertex_number, generic_ptr specific_data)
{
    vertex_data* p_vertexdata;

    /* allocate memory space for the data stored in this vertex */
    p_vertexdata=(vertex_data*)malloc(sizeof(vertex_data));
    if(p_vertexdata==NULL)
	return ERROR;

    /* store the data */
    p_vertexdata->specific_data=specific_data;
    p_vertexdata->emanating=NULL;
    p_vertexdata->vertex_number=vertex_number;
    p_vertexdata->visited=FALSE;
    p_vertexdata->label=NOLABEL;
    p_vertexdata->labels=NULL;
    p_vertexdata->x=0.0;
    p_vertexdata->y=0.0;

    /* append the node corresponding to this vertex to the list of vertices */
    if(append(p_G, (generic_ptr)p_vertexdata)==ERROR) {
	free(p_vertexdata);
	p_vertexdata=NULL;
	return ERROR;
    }
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status append_vertex(graph* p_G, vertex_id vertex_number, generic_ptr specific_data)
{
  return(add_vertex(p_G,vertex_number,specific_data));
}
/*----------------------------------------------------------------------------------------------------*/
status insert_vertex(graph* p_G, vertex_id vertex_number, generic_ptr specific_data)
/* Differs from append_vertex in that it calls "insert", instead of "append"
 * Code to be simplified.
 */
{
    vertex_data* p_vertexdata;

    /* allocate memory space for the data stored in this vertex */
    p_vertexdata=(vertex_data*)malloc(sizeof(vertex_data));
    if(p_vertexdata==NULL)
	return ERROR;

    /* store the data */
    p_vertexdata->specific_data=specific_data;
    p_vertexdata->emanating=NULL;
    p_vertexdata->vertex_number=vertex_number;
    p_vertexdata->visited=FALSE;
    p_vertexdata->label=NOLABEL;
    p_vertexdata->labels=NULL;
    p_vertexdata->x=0.0;
    p_vertexdata->y=0.0;

    /* append the node corresponding to this vertex to the list of vertices */
    if(insert(p_G, (generic_ptr)p_vertexdata)==ERROR) {
	free(p_vertexdata);
	p_vertexdata=NULL;
	return ERROR;
    }
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status add_edge(graph G, vertex_id vertex1, vertex_id vertex2, generic_ptr specific_data)
/*
 * Warning: The user must be careful so as not to add an already existing edge, since
 * this is not automatically detected.
 */ 
{
    llist pv1=NULL;
    llist pv2=NULL;
    
    if( (pv1=find_vertex(G, vertex1))==NULL) return ERROR;
    if( (pv2=find_vertex(G, vertex2))==NULL) return ERROR;
  
    return(add_edge_with_pointers(pv1, pv2, specific_data));
}
/*----------------------------------------------------------------------------------------------------*/
status add_edge_with_pointers(graph_vertex pv1, graph_vertex pv2, generic_ptr specific_data)
/*
 * Warning: The user must be careful so as not to add an already existing edge, since
 * this is not automatically detected.
 */ 
{
  vertex_id vertex1, vertex2;

  if(pv1==NULL || pv2==NULL) return ERROR;
  
  vertex1 = VERTEX_NUMBER(pv1);
  vertex2 = VERTEX_NUMBER(pv2);

  if(edge_append(&EMANATING(pv1), vertex1, vertex2, specific_data, pv2, 1)==ERROR) 
    return ERROR;	
  if(edge_append(&EMANATING(pv2), vertex2, vertex1, specific_data, pv1, 2)==ERROR)
    return ERROR;

  return OK; 
}
/*----------------------------------------------------------------------------------------------------*/
status edge_append(llist* p_L, 
		   vertex_id vertex_ini,
		   vertex_id vertex_fi, 
		   generic_ptr specific_data, 
		   graph_vertex vertex_pointer, int copy)
{
    edge_data* p_edgedata;

    p_edgedata=(edge_data*)malloc(sizeof(edge_data));
    if(p_edgedata==NULL) return ERROR;
    
    p_edgedata->specific_data=specific_data;
    p_edgedata->vertex_ini=vertex_ini;
    p_edgedata->vertex_number=vertex_fi;
    p_edgedata->vertex_pointer=vertex_pointer;
    p_edgedata->copy=copy;
    p_edgedata->sense=NOSENSE;
    
    if(append(p_L,(generic_ptr)p_edgedata)==ERROR) {
	free(p_edgedata);
	p_edgedata=NULL;
	return ERROR;
    }
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status duplicate_graph(graph G1, 
		       graph* G2, 
		       status (*p_copy_vertex)(generic_ptr,generic_ptr*), 
		       status (*p_copy_edge)(generic_ptr,generic_ptr*))
/*
 * Makes a copy of the graph G1 and returns it as G2. The user may choose whether to copy all 
 * specific data in G1 to G2 or not. If p_copy_vertex==NULL and p_copy_edge==NULL, then specific
 * data is not copied. In that case, pointers to the specific data in G1 will be set up from G2 
 * and the user should be careful when destroying one of G1 or G2. If p_copy_vertex and p_copy_edge
 * point to actual copy functions, then all specific data is duplicated using them. In this second 
 * case, G1 and G2 become fully independent graphs, destroyable 'a volonté'.
 *
 * Preconditions: G2 must have been previously initialized with init_graph(&G2);
 *
 * Note that the implementation could be sped up at the cost of obscuring the code a bit: vertex
 * duplication is fast, but edge duplication uses add_edge() instead of add_edge_with_pointers().
 */
{
  llist pv;             /* Pointer to a vertex */
  llist pe;             /* Pointer to an edge */
  vertex_id initial;   /* Initial vertex id. of the edge to copy */
  vertex_id final;     /* Final vertex id. of the vertex to copy */
  generic_ptr olddata; /* Pointer to the specific data fields of G1 */
  generic_ptr newdata; /* Pointer to the specific data fields of G2 */
  status err;          /* Error code returned by the copy functions */

  if(G1==NULL)
    return(ERROR);

  olddata = NULL;
  newdata = NULL;

  /* Visit and copy all vertices */
  for(pv=G1; pv!=NULL; pv=NEXT(pv))
    {
      /* If the user asked so, we duplicate the specific vertex_data */
      olddata = SPECIFIC_VERTEX_DATA(pv);
      if(p_copy_vertex!=NULL) 
	{
	  if(olddata==NULL)
	    glr_error("User asked to duplicate vertex data, but there's no such data");
	  err = (*p_copy_vertex)(olddata,&newdata);
	  if(err==ERROR)
	    glr_error("Error:: copy_vertex() failed in duplicate graph");
	}
      else
	{
	  newdata = olddata;
	}

      /* Actual vertex duplication */
      if(add_vertex(G2,VERTEX_NUMBER(pv),newdata)==ERROR)
	return(ERROR);
    }
  
  /* Visit and copy all edges */
  for(pv=G1; pv!=NULL; pv=NEXT(pv))
    {
      for(pe=EMANATING(pv);pe!=NULL;pe=NEXT(pe))
	{
	  /* Avoid duplicating edges twice */
	  if(COPY(pe)==1) 
	    {
	      /* Identifyiers and pointers of this edge's vertices */
	      initial = VERTEX_NUMBER(pv);
	      final   = VERTEX_NUMBER(VERTEX_POINTER(pe));

	      /* If the user asked so, we duplicate the specific edge data */
	      olddata = SPECIFIC_EDGE_DATA(pe);
	      if(p_copy_edge!=NULL)
		{
		  if(olddata==NULL)
		    glr_error("User asked to duplicate specific vertex data, but there's no such data");
		  err = (*p_copy_edge)(olddata,&newdata);
		  if(err==ERROR)
		    glr_error("Error:: copy_edge() failed in duplicate graph");
		}
	      else
		{
		  newdata = olddata;
		}

	      /* Actual edge duplication */
	      if(add_edge(*G2,initial,final,newdata)==ERROR)
		return(ERROR);
	    }
	}
    }

  /* Thumbs up */
  return(OK);
}


/*****************************************************************************************************
 *
 *  Section 2 - Graph destructors
 *
 *****************************************************************************************************/

void destroy_graph(graph* p_G, 
		   void (*p_free_specific_vertex_data)(generic_ptr),
		   void (*p_free_specific_edge_data)(generic_ptr))
/* 
 * Destroys the graph pointed to by *p_G. *p_G is set to the NULL value.
 * Destruction proceeds in two phases. In the first one, the specific vertex
 * and edge data fields are destroyed using the functions pointed to by 
 *
 *     p_free_specific_vertex_data
 *     p_free_specific_edge_data
 *
 * (If some of the pointers is NULL, the corresponding specific data is not 
 * freed.) These functions must receive a (generic) pointer to the specific data 
 * as input, cast this pointer into the real type of the data, and destroy
 * it. In a second phase, the vertex and edge lists are deleted by calling 
 * destroy_list, which receives (as input) a pointer to a proper destructor 
 * for the data in these lists. We use these destructors to this end:
 *
 *     free_vertex_data()  for the vertex data field
 *     free_edge_data()    for the edge data field.
 */
{
  llist pv = NULL;  /* Pointer to vertex */
  status err;      /* Returned error code */

  /* Do nothing if the graph is empty */
  if(empty_graph(*p_G))
    return;

  /* First destroy specific vertex and edge data */
  err = destroy_graph_specific_data(*p_G,
				    p_free_specific_vertex_data,
				    p_free_specific_edge_data);

  if(err==ERROR)
    glr_error("Error:: destroy_graph_specific_data() failed in destroy graph()");

  /* Then we destroy all lists of edges  */
  while((pv=list_iterator(*p_G, pv))!=NULL) 
    {
      /* The call destroy_list already sets EMANATING(pv) to NULL */
      destroy_list(&EMANATING(pv), free_edge_data);
    }

  /* Finally, we destroy the vertices (*p_G is set to NULL inlist of  destroy_list */
  destroy_list(p_G, free_vertex_data); 
}
/*----------------------------------------------------------------------------------------------------*/
status destroy_graph_specific_data(graph G, 
				   void (*p_free_specific_vertex_data)(generic_ptr),
				   void (*p_free_specific_edge_data)(generic_ptr))
/*
 * Destroys the specific vertex and edge data of a graph. 
 * Pointers to these fields will be set to NULL on exit.
 */
{
  llist pv=NULL;  /* Pointer to vertex */
  llist pe=NULL;  /* Pointer to edge */
  
  if(G==NULL)
    return(ERROR);

  /* First destroy specific vertex and edge data */
  for(pv=G;pv!=NULL;pv=NEXT(pv))
    {
      /* Destroy specific edge data if the user demands it */
      if(p_free_specific_edge_data!=NULL)
	{
	  /* Do it on all emanating edges of this vertex */
	  for(pe=EMANATING(pv);pe!=NULL;pe=NEXT(pe))
	    {
	      /* Actuall destruction, but only from one of the two edge copies */
	      if(COPY(pe)==1)
		{
		  (*p_free_specific_edge_data)(SPECIFIC_EDGE_DATA(pe));
		}
	      /* We set the pointer to NULL in any case */
	      SPECIFIC_EDGE_DATA(pe)=NULL;
	    }
	}
      
      /* Destroy specific vertex data if the user demands it */
      if(p_free_specific_vertex_data!=NULL)
	{
	  (*p_free_specific_vertex_data)(SPECIFIC_VERTEX_DATA(pv));
	  SPECIFIC_VERTEX_DATA(pv)=NULL;
	}
    }
  return(OK);
}
/*----------------------------------------------------------------------------------------------------*/
status delete_vertex(graph* p_G, vertex_id vertex_number, 
		     void (*p_free_specific_vertex_data)(generic_ptr))
/*
 * Deletes a vertex only when it has no incident edges. Use delete_vertex_and_edges or
 * delete_vertex_and_edges_with_pointer if you want to also delete the incident edges.
 */
{
    llist vertex_pointer=NULL;

    /* Check whether the vertex exists */
    if((vertex_pointer=find_vertex(*p_G, vertex_number))==NULL)
      return ERROR;
    
    /* Call delete_vertex_with_pointer */
    if(delete_vertex_with_pointer(p_G,vertex_pointer,p_free_specific_vertex_data)==ERROR)
      return(ERROR);
    else
      return(OK);
}
/*----------------------------------------------------------------------------------------------------*/
status delete_vertex_with_pointer(graph* p_G, graph_vertex vertex_pointer, 
				  void (*p_free_specific_vertex_data)(generic_ptr))
/*
 * Deletes a vertex only when it has no incident edges. Use delete_vertex_and_edges or
 * delete_vertex_and_edges_with_pointer if you want to also delete the incident edges.
 */
{
    /* Check whether the vertex exists and has no edges involving it */
    if(vertex_pointer==NULL || (*p_G)==NULL)
	return ERROR;
    if(!empty_list(EMANATING(vertex_pointer)))
	return ERROR;
    
    /* Free specific vertex data if the user demanded it */
    if(p_free_specific_vertex_data!=NULL)
      {
	(*p_free_specific_vertex_data)(SPECIFIC_VERTEX_DATA(vertex_pointer));
	SPECIFIC_VERTEX_DATA(vertex_pointer)=NULL;
      }

    /* Delete the standard vertex data */
    if(delete_node(p_G,vertex_pointer,free_vertex_data)==ERROR)
      return ERROR;
    else
      return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status delete_vertex_and_edges(graph* p_G, vertex_id vertex_number, 
			       void (*p_free_specific_vertex_data)(generic_ptr),
			       void (*p_free_specific_edge_data)(generic_ptr))
/*
 * Deletes a vertex and all its incident edges. The vertex is specified by its id.
 */
{
    llist vertex_pointer=NULL;

    /* Check whether the vertex exists */
    if((vertex_pointer=find_vertex(*p_G, vertex_number))==NULL)
      return ERROR;
    
    /* Call delete_vertex_with_pointer */
    return(delete_vertex_and_edges_with_pointer(p_G, vertex_pointer,
						 p_free_specific_vertex_data,
						 p_free_specific_edge_data));
}
/*----------------------------------------------------------------------------------------------------*/
status delete_vertex_and_edges_with_pointer(graph* p_G, graph_vertex vertex_pointer,
					    void (*p_free_specific_vertex_data)(generic_ptr),
					    void (*p_free_specific_edge_data)(generic_ptr))
/*
 * Deletes a vertex and all its incident edges. The vertex is specified by a pointer to it.
 */
{
  graph_vertex vertex1, vertex2;
  graph_edge edge1, edge2;
  status err;

  /* First delete all emanating edges */
  vertex1 = vertex_pointer;
  while((edge1=EMANATING(vertex_pointer))!=NULL)
    {
      vertex2 = VERTEX_POINTER(edge1);
      edge2 = find_destin_with_pointer(EMANATING(vertex2), vertex1);
      if(edge2==NULL) 
	return(ERROR);
      err = delete_edge_with_pointers(vertex1, edge1, 
				      vertex2, edge2, 
				      p_free_specific_edge_data);
      if(err==ERROR)
	return(ERROR);
    }

  /* Then delete the vertex */
  return(delete_vertex_with_pointer(p_G, vertex1, p_free_specific_edge_data));

}
/*----------------------------------------------------------------------------------------------------*/
status delete_edge(graph G, 
		   vertex_id vid1, vertex_id vid2, 
		   void (*p_free_specific_edge_data)(generic_ptr))
{
  graph_vertex vertex1, vertex2;
  graph_edge edge1, edge2;
  status err;
  
  /* Check whether the two copies of the edge exist */
  if((vertex1=find_vertex(G, vid1))==NULL)
    return ERROR;
  if((vertex2=find_vertex(G, vid2))==NULL)
    return ERROR;
  if((edge1=find_destin(EMANATING(vertex1), vid2))==NULL)
    return ERROR;
  if((edge2=find_destin(EMANATING(vertex2), vid1))==NULL)
    return ERROR;
  
  /* Call delete_edge_with_pointers */
  err = delete_edge_with_pointers(vertex1, edge1, 
				  vertex2, edge2, 
				  p_free_specific_edge_data);
  return(err);
}
/*----------------------------------------------------------------------------------------------------*/
status delete_edge_with_pointers(graph_vertex vertex1, graph_edge edge1, 
				 graph_vertex vertex2, graph_edge edge2, 
				 void (*p_free_specific_edge_data)(generic_ptr))
/*
 * Deletes an edge from G through its pointers.
 * vertex1 (vertex2): pointer to the first (second) vertex of the edge
 * edge1 (edge2): pointer to the edge, seen as emanating from vertex1 (vertex2).
 */
{
  if(vertex1==NULL || edge1==NULL || vertex2==NULL || edge2 ==NULL)
    return(ERROR);

  /* Delete specific edge data first, if required by the user */
  if(p_free_specific_edge_data!=NULL)
    {
      /* We only need to call the following for one of the oriented edges */
      (*p_free_specific_edge_data)(SPECIFIC_EDGE_DATA(edge1));
      SPECIFIC_EDGE_DATA(edge1)=NULL;

      /* Set the pointer from this edge's 2nd copy to NULL too */
      SPECIFIC_EDGE_DATA(edge2)=NULL;
    }

  /* Then delete standard data (This also sets to NULL the EMANATING pointers) */
  if(delete_node(&EMANATING(vertex1), edge1, free_edge_data)==ERROR)
    return ERROR;
  if(delete_node(&EMANATING(vertex2), edge2, free_edge_data)==ERROR)
    return ERROR;
  return OK;
}
/*----------------------------------------------------------------------------------------------------*/
static void free_vertex_data(generic_ptr data)
/*
 * Frees all space occupied by the data linked to a vertex.
 * We assume the space occupied by specific_vertex_data has been previously freed 
 * (e.g., by delete_vertex), or (otherwise) that the user doesn't want to free it. 
 * We also assume that the list of emanating edges has been destroyed, or that the
 * user does not want to destroy it. The list of labels is completely destroyed.
 */
{
  vertex_data* garbage = (vertex_data*)data;

  if(garbage!=NULL) 
    {
      destroy_list(&(garbage->labels), free);
      garbage->emanating=NULL;
      garbage->specific_data=NULL;
      free(data);
    }
  else
    {
      glr_error("Error:: free_vertex_data() attempted to free NULL data");
    }    
}
/*----------------------------------------------------------------------------------------------------*/
static void free_edge_data(generic_ptr data)
/* 
 * Frees all space occupied by the data linked to an edge.
 * We assume the space occupied by specific_edge_data has been previously freed 
 * (e.g., by delete_edge_with_pointers), or (otherwise) that the user doesn't 
 * want to free it.
 */
{
  edge_data* garbage = (edge_data*)data;

  if(garbage!=NULL) 
    {
      /* Set the specifc edge data pointer to NULL */
      garbage->specific_data=NULL;
      garbage->vertex_pointer=NULL;
      free(data);
    }
  else
    {
      glr_error("Error in free_edge_data():: attempted to free NULL data");
    } 
}

/*****************************************************************************************************
 *
 *  Section 3 - Graph traverse functions
 *
 *****************************************************************************************************/

status simply_visit_all(graph G)
{
    return(depth_first(G, G, simply_visit)==ERROR);
}
/*----------------------------------------------------------------------------------------------------*/
status depth_first(graph G, graph_vertex vertex_pointer, status (*p_visit_f)(llist))
/*
 * Preconditions: on entry, all vertices must be marked as non-visited.
 */
{
    llist edge_pointer;
    
    /* protection against the case of NULL pointers */
    if(G==NULL || vertex_pointer==NULL)
	return ERROR;
    
    VISITED(vertex_pointer)=TRUE;
    if((*p_visit_f)(vertex_pointer)==ERROR) 
	return ERROR;
    
    /* for all neighboring vertices of vertex_pointer ... */
    edge_pointer = NULL;
    while((edge_pointer=list_iterator(EMANATING(vertex_pointer), edge_pointer))!=NULL)
      /* if the vertex has not been visited */
      if(!VISITED(VERTEX_POINTER(edge_pointer)))
	/* visit the vertex and its descendants */
	if(depth_first(G, VERTEX_POINTER(edge_pointer), p_visit_f)==ERROR)
	  return ERROR;
    
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status depth_first_vertices_edges(graph G, graph_vertex vertex_pointer, 
				  boolean (*p_is_reachable)(llist,llist),
				  status  (*p_action_vertex_before)(llist),
				  status  (*p_action_edge_before)(llist,llist,llist),
				  status  (*p_action_edge_after)(llist,llist,llist))
/*
 * Visits all vertices of the graph G, in a depth-first order, and calls the following
 * functions on the edges and vertices found along the way: 
 *
 *     function (*p_action_vertex_before)(): is an action on the current vertex (pointed to by 
 *            vertex_pointer), in the descending phase.
 *     function (*p_action_edge_before)(): is an action on the current edge (pointed to by 
 *            edge_pointer), in the descending phase.
 *     function (*p_action_edge_after)(): is an action on the current edge in the ascending 
 *            phase, once all vertices of the graph have been reached.
 *
 * If some of these functions is specified by a NULL pointer, the vertex/edge is not visited.
 * The function traverses all arcs of the graph that "are traversable". The user can provide
 * a function (*p_is_reachable)(list,list) to determine whether a given edge is traversable. 
 * If NULL is specifid instead of this function, then all edges are traversable.
 *
 * All (reachable) vertices will have been visited at the end, but only (reachable) edges
 * of the depth-first spanning tree will be visited. No action can be done, thus on the 
 * edges creating a cycle.
 *
 * Preconditions: at the top-level call, all vertices must be marked as non-visited.
 */
{
    llist edge_pointer;
    llist adj_vertex_pointer;
    boolean is_reachable;

    adj_vertex_pointer=NULL;

    /* protection against the case of NULL pointers */
    if(G==NULL || vertex_pointer==NULL)
	return ERROR;
    
    /* mark the current vertex as visited and do action_vertex_before() on it, if specified */
    VISITED(vertex_pointer)=TRUE;
    if(p_action_vertex_before != NULL)
      (*p_action_vertex_before)(vertex_pointer);
      
    /* for all neighboring vertices of vertex_pointer ... */
    edge_pointer = NULL;
    while((edge_pointer=list_iterator(EMANATING(vertex_pointer), edge_pointer))!=NULL){

      /* get pointer to the current adjacent vertex */
      adj_vertex_pointer = VERTEX_POINTER(edge_pointer);

      /* see if the current adjacent vertex is reachable under the user's criterion (if provided) */
      if(p_is_reachable == NULL)
	is_reachable = TRUE;
      else
	is_reachable = (*p_is_reachable)(edge_pointer, adj_vertex_pointer);

      /* if adjacent vertex is reachable and not yet visited ... */
      if(is_reachable && !VISITED(adj_vertex_pointer)){
	/* do action_edge_before() on the edge */
	if(p_action_edge_before !=NULL)
	  (*p_action_edge_before)(vertex_pointer, edge_pointer, adj_vertex_pointer);
	/* visit the vertex and its descendants ... */
	if(depth_first_vertices_edges(G, adj_vertex_pointer, 
				      p_is_reachable, 
				      p_action_vertex_before,
				      p_action_edge_before, 
				      p_action_edge_after)==ERROR){
	  return ERROR;
	}
	/* do action_edge_after() on the edge */
	if(p_action_edge_after !=NULL)
	  (*p_action_edge_after)(vertex_pointer, edge_pointer, adj_vertex_pointer);	
      }
    }
    return OK;
}
/*----------------------------------------------------------------------------------------------------*/
status mark_all_unvisited(graph G)
{
    llist vertex;
    vertex=NULL;
    if(G==NULL) return ERROR;
    while((vertex=list_iterator(G, vertex))!=NULL)
	VISITED(vertex)=FALSE;
    return OK;
}
/*-----------------------------------------------------------------------------------------------*/
status mark_senses_down(graph G, graph_vertex vertex_pointer, boolean (*p_is_reachable)(llist,llist))
/*
 * Preconditions on first entry: it requires that all sense fields at all edges be equal to NOSENSE.
 * Marks the relative position of a vertex when seen from another.
 * The relative position of vertex v is DOWN from vertex u if edge (u,v) is traversed
 * from u to v in a depth-first search, otherwise it is UP. The attribute UP or DOWN
 * is stored in the nodes of the EMANATING list of a particular vertex. 
 * Initially, all edges have to be labeled with sense NOSENSE. See edge_append().
 */
{
  llist edge_pointer;
  llist other_edge_pointer;
  llist adj_vertex_pointer;
  boolean is_reachable;

  /* protection against the case of NULL pointers */
  if(G==NULL || vertex_pointer==NULL)
    return ERROR;
  
  VISITED(vertex_pointer)=TRUE;
  
  edge_pointer = NULL;
  while((edge_pointer=list_iterator(EMANATING(vertex_pointer), edge_pointer))!=NULL)
  {
    /* get pointer to the current adjacent vertex */
    adj_vertex_pointer = VERTEX_POINTER(edge_pointer);

    /* see if the current adjacent vertex is reachable under the user's criterion (if provided) */
    if(p_is_reachable == NULL)
      is_reachable = TRUE;
    else
      is_reachable = (*p_is_reachable)(edge_pointer, adj_vertex_pointer);

    if(is_reachable) {

      /* mark sense of this edge. The sense is DOWN at the current edge_pointer, and UP in the other one  */
      if(SENSE(edge_pointer)==NOSENSE) SENSE(edge_pointer)=DOWN;
      if((other_edge_pointer=find_destin(EMANATING(adj_vertex_pointer), 
					 VERTEX_NUMBER(vertex_pointer)))==NULL)
	glr_error("Error:: find_destin() failed in mark_senses_down()");
      if(SENSE(other_edge_pointer)==NOSENSE) SENSE(other_edge_pointer)=UP;
      
      /* go on with the DFS */
      if(!VISITED(adj_vertex_pointer))
	if(mark_senses_down(G, adj_vertex_pointer, p_is_reachable)==ERROR)
	  return ERROR;
    }
  }
  return OK;
}
/*-----------------------------------------------------------------------------------------------*/
void clear_all_senses(graph G)
{
  llist V=NULL;
  llist E=NULL;

  while((V=list_iterator(G,V))!=NULL)
    while((E=list_iterator(EMANATING(V),E))!=NULL)
      SENSE(E)=NOSENSE;
}
/*----------------------------------------------------------------------------------------------------*/
static status simply_visit(graph_vertex vertex_pointer)
{
    if(vertex_pointer==NULL) return ERROR;
    printf("visiting vertex %u\n", VERTEX_NUMBER(vertex_pointer));
    return OK;
}

/*****************************************************************************************************
 *
 *  Section 4 - Detection of fundamental cycles and connected components
 *
 *****************************************************************************************************/

status detect_fundamental_cycles(graph G, llist* cycles, boolean (*p_is_reachable)(llist,llist) )
/*
 * Obtains a set of fundamental cycles on the graph G. The output parameter "cycles" is a 
 * "list of cycles". Each element of the list stores the edges and vertices of a fundamental 
 * cycle. See find_fundamental_cycles below.
 *
 * The argument p_is_reachable can be used to provide a boolean function that says whether an 
 * edge can be traversed or not. If p_is_reachable is passed as NULL, all edges can be traversed.
 */
{
  /* Give a sense to each one of the edges */
  mark_all_unvisited(G);
  clear_all_senses(G);
  mark_senses_down(G, G, p_is_reachable);

  /* Reset the visited field to FALSE */
  mark_all_unvisited(G);
  
  /* Call the recursive function that detects all cycles of G */
  if(find_fundamental_cycles(G, G, p_is_reachable, cycles)==ERROR)
    return ERROR;

  return OK;
}
/*----------------------------------------------------------------------------------------------------*/
void free_cycles_data(generic_ptr data)
/*
 * Frees all the space occupied by the data linked to a list of cycles.
 * Each node of this list contains information relative to one cycle.
 * This info is stored in the data field of the node, and consists of:
 *     a list of vertices of the cycle
 *     a list of edges of the cycle
 *     an integer label identifying the cycle
 */
{
  cycle_data* garbage = (cycle_data*)(data);

  if(garbage!=NULL) {
    /* compte, no hem de destruir el camp de dades de la llista edges
      * o vertices, car es precisament el camp de dades d'un vertex del
      * graf, i el graf el volem deixar intacte. Per aixo especifiquem
      * NULL com a funcio de destruccio de dades.
      */
    destroy_list(&(garbage->vertices), NULL);
    destroy_list(&(garbage->edges), NULL);
    free(data);
  }
}
/*----------------------------------------------------------------------------------------------------*/
status connected_components(graph G, llist* components)
{
  llist curr_v;

  if(G==NULL)
    return(ERROR);
  
  // Mark all vertices as unvisited
  mark_all_unvisited(G);

  // Iterate over all vertices of the graph
  for(curr_v=G; curr_v!=NULL; curr_v=NEXT(curr_v)) 
    {
      // An unvisited vertex means a new connected component has been found
      if(!VISITED(curr_v)) 
	{
	  // Insert the component into the list of components
	  if(insert(components,(generic_ptr)curr_v)==ERROR)
	    return(ERROR);
	  // Traverse the connected component of current vertex
	  if(depth_first_vertices_edges(curr_v,curr_v,NULL,NULL,NULL,NULL)==ERROR)
	    return(ERROR);
	}
    }
  return(OK);
}
/*-----------------------------------------------------------------------------------------------*/
static status find_fundamental_cycles(graph G, 
			       graph_vertex curr_vertex, 
			       boolean (*p_is_reachable)(llist,llist),
			       llist* cycles)
/*
 * Recursive function.
 * Given a connected graph G, this function finds a set of fundamental cycles of G.
 * This set is returned via the "cycles" argument, which is a listd by reference.
 * Each node (pointed to by pNode) of the cycles list stores the following information related to 
 * one cycle:
 *
 *      CYC_VERTICES(pNode): a list of the vertices of the cycle
 *      CYC_EDGES(pNode)   : a list of the edges of the cycle
 *      CYC_LABEL(pNode)   : the label of this cycle. After 'find_fundamental_cycles' is
 *                            done, all vertices along the cycle will remain labelled with
 *                            CYC_LABEL(pNode). This label being stored in the field 'labels'
 *                            of vertex_data structure.
 *
 * The argument p_is_reachable can be used to provide a boolean function that says whether an 
 * edge can be traversed or not. If p_is_reachable is passed as NULL, all edges can be traversed.
 */
{
    llist edge_pointer;
    static int label=0;
    llist vertices, edges;
    cycle_data* p_cycle_data;
    llist adj_vertex_pointer;
    boolean is_reachable;

    if(G==NULL || curr_vertex==NULL)
      return ERROR;  

    VISITED(curr_vertex)=TRUE;    
    
    /* 
     * execute a depth-first travel along  the graph searching for already 
     * visited vertices which determine the existence of a cycle along them.
     */
    edge_pointer = NULL;
    while((edge_pointer=list_iterator(EMANATING(curr_vertex), edge_pointer))!=NULL)  {

      /* get pointer to the current adjacent vertex */
      adj_vertex_pointer = VERTEX_POINTER(edge_pointer);
      
      /* see if the current adjacent vertex is reachable under the (eventual) user's criterion */
      if(p_is_reachable == NULL)
	is_reachable = TRUE;
      else
	is_reachable = (*p_is_reachable)(edge_pointer, adj_vertex_pointer);
      
      /* if adjacent vertex is reachable and not yet visited ... */
      if(is_reachable){	
	if(!VISITED(adj_vertex_pointer)) {
	  if(find_fundamental_cycles(G, adj_vertex_pointer, p_is_reachable, cycles)==ERROR)
	    return ERROR;
	}
	else if(SENSE(edge_pointer)==DOWN)	  {
	  /* 
	   * verify that this sense is down!! the edge could be the one leading 
	   * to the parent node from where we are coming!!
	   */
	  
	  /* new cycle detected */
	  label++;
	  
	  /* printf("Found a cycle. Cycle %d.\n", label); fflush(stdout); */
	  /* initialize lists "vertices" and "edges" */
	  if(init_list(&vertices)==ERROR || init_list(&edges)==ERROR)
	    glr_error("Error:: init_list() failed in find_fundamental_cycles()");
	  
	  /* 
	   * go backwards to reach the vertex pointed to by 
	   * adj_vertex_pointer once again 
	   */
	  if(cycle_search(curr_vertex, edge_pointer, 
			  adj_vertex_pointer, 
			  label, 
			  &vertices, 
			  &edges)==ERROR)
	    glr_error("Error:: cycle_search() failed in find_fundamental_cycles()");

	  /* store cycle in cycles list */
	  if((p_cycle_data=(cycle_data*)malloc(sizeof(cycle_data)))==NULL)
	    glr_error("Error:: malloc() failed in find_fundamental_cycles()\n");
	  p_cycle_data->vertices=vertices;
	  p_cycle_data->edges=edges;
	  p_cycle_data->label=label;
	  if(append(cycles, (generic_ptr)p_cycle_data)==ERROR)
	    glr_error("Error:: append() failed in find_fundamental_cycles()\n");
	}
      }
    }
    return OK;
}
/*-----------------------------------------------------------------------------------------------*/
static status cycle_search(graph_vertex curr_vertex, 
		    graph_edge curr_edge, 
		    graph_vertex end_vertex, 
		    int label, 
		    llist* vertices, llist* edges)
/*
 * Recursive function.
 * Given the vertex "curr_vertex" cycle_search() goes upwards in the graph until it finds
 * the vertex "end_vertex". Along the way, cycle_search() inserts "curr_vertex" in the 
 * "vertices" list and "curr_edge" in the "edges" list. cycle_search() is used to search 
 * for all edges and vertices of a cycle, once its presence has been detected by 
 * find_fundamental_cycles().
 * 
 * The lists "vertices" and "edges" must have been initialized by the calling function.
 * Order inside vertices (edges): The cycle vertices (edges) are stored in the oposite 
 * sense in which they are found during the cycle's tracing.
 */
{
  llist edge;
  static boolean found=FALSE;
  int* p_label_data;

  if(curr_vertex==NULL) 
    return ERROR;

  LABEL(curr_vertex)=label;

  /* insert current vertex and last edge in vertices and edges */
  if(insert(vertices, (generic_ptr)(DATA(curr_vertex)))==ERROR)
    glr_error("Error:: insert() failed to insert vertex in cycle_search()");
  if(insert(edges, (generic_ptr)(DATA(curr_edge)))==ERROR)
    glr_error("Error:: insert() failed to insert edge in cycle_search()"); 

  /* insert current label in the labels list associated to this vertex */
  if((p_label_data=(int*)malloc(sizeof(int)))==NULL)
    glr_error("Error:: malloc() failed in cycle_search()");
  (*p_label_data)=label;
  if(insert(&LABELS(curr_vertex), (generic_ptr)p_label_data)==ERROR)
    glr_error("Error:: insert() failed to insert label in cycle_search()");
  
  found = (curr_vertex==end_vertex);
  
  edge = NULL;
  while((edge=list_iterator(EMANATING(curr_vertex), edge))!=NULL && !found)
  {
    /* printf("exploring through edge to %u\n", DESTINATION(edge));*/
    if(SENSE(edge)==UP && LABEL(VERTEX_POINTER(edge))!=label)
      if(cycle_search(VERTEX_POINTER(edge), edge, end_vertex, label, vertices, edges)==ERROR) 
	return ERROR;
  }
  if(!found) 
  {
    /* 
     * There is only one case in which the last while loop cannot find "end_vertex".
     * This happens when the upwards travel along G enters a cycle inside the cycle we
     * are following (see documentation). We must provide backtracking capability
     * to go on with the search.
     */
    
    LABEL(curr_vertex)=NOLABEL;
    delete_node(vertices, *vertices, NULL);
    delete_node(edges, *edges, NULL);
    delete_node(&(LABELS(curr_vertex)), LABELS(curr_vertex), free);
  }  
  return OK;
}


/*****************************************************************************************************
 *
 *  Section 5 - Graph analysis functions
 *
 *****************************************************************************************************/

void analyze_graph(graph G, FILE* fd)
{
  int nedges, nvertices, comp_number, cyc_number;
  llist components;
  llist node_comp, node_cyc;
  llist curr_component;
  llist cycles;
  

  // Heading
  fprintf(fd,"Graph structure:\n");

  // Generate list of connected components
  init_list(&components);
  if(connected_components(G,&components)==ERROR)
    glr_error("Error in AnalyzeGraph: connected_components failed");
  fprintf(fd,"\tGraph has %d connected components\n",length(components));

  // Rough analysis of edges, vertices and cycles of each component
  comp_number=1;
  for(node_comp=components;node_comp!=NULL; node_comp=NEXT(node_comp)) 
    {
      // Get pointer to current component
      curr_component = (llist)(DATA(node_comp));

      // Count and print vertices, edges, and cycles of this component
      count_vertices_edges_component(curr_component, &nvertices, &nedges);
      fprintf(fd,"\tComponent number %d: %d vertices, %d edges, %d cycles \n", 
	     comp_number, nvertices, nedges, nedges-nvertices+1);
      comp_number++;
    }

  // Detailed analysis of the cycles of each component
  fprintf(fd,"Analysis of cycles for each component:\n");
  comp_number=1;
  for(node_comp=components;node_comp!=NULL; node_comp=NEXT(node_comp)) 
    {
      // Get pointer to current component
      curr_component = (llist)(DATA(node_comp));

      // Obtain and print the cycles of this component
      fprintf(fd,"\tComponent number %d:\n", comp_number);
      init_list(&cycles);
      if(detect_fundamental_cycles(curr_component, &cycles, NULL)==ERROR)
	glr_error("Error in AnalyzeGraph: failed to detect fundamental cycles");
      cyc_number = 1;
      for(node_cyc = cycles; node_cyc!=NULL; node_cyc=NEXT(node_cyc))
	{
	  fprintf(fd,"\t\tCycle %d has %d vertices\n", cyc_number, length(CYC_VERTICES(node_cyc)));
	  // printf("\t\tCycle %d has:\n", cyc_number);
	  // printf("\t\t\t%d vertices\n", length(CYC_VERTICES(node_cyc)));
	  // printf("\t\t\t%d edges\n", length(CYC_EDGES(node_cyc)));
	  // printf("\t\t\tLabel %d\n", CYC_LABEL(node_cyc));
	  cyc_number++;
	}

      // Prepare next iteration
      comp_number++;
      destroy_list(&cycles,free_cycles_data);
    }

  // Destroy dynamic memory
  destroy_list(&components,NULL);
}
/*-----------------------------------------------------------------------------------------------*/
int count_vertices(graph G)
{
  llist V;
  int count=0;
  
  V=NULL;
  while((V=list_iterator(G,V))!=NULL)
    count++;
  return(count);
}
/*-----------------------------------------------------------------------------------------------*/
int count_edges(graph G)
{
  llist V, E;
  int count = 0;

  for(V=G; V!=NULL; V=NEXT(V))
    for(E=EMANATING(V); E!=NULL; E=NEXT(E))
      count ++;
  return (count/2);
}
/*-----------------------------------------------------------------------------------------------*/
int degree(graph_vertex vertex_pointer)
{
    int degree=0;
    llist edge_pointer;
    llist L;

    if(vertex_pointer==NULL) 
	return -1;

    L=EMANATING(vertex_pointer);
    edge_pointer = NULL;
    while((edge_pointer=list_iterator(L, edge_pointer))!=NULL)
	degree++;

    return degree;
}
/*-----------------------------------------------------------------------------------------------*/
status count_vertices_edges_component(llist component, int* nvertices, int* nedges)
/*
 * Counts the number of vertices and edges of a connected component. 
 * This is a wrapper function of recursive_count_vertices_edges_component
 */
{
  *nvertices=0; *nedges=0;

  if(mark_all_unvisited(component)==ERROR)
    return(ERROR);

  if(recursive_count_vertices_edges_component(component, nvertices, nedges)==ERROR)
    return(ERROR);

  //nedges = (int)((double)nedges / 2.0);
  (*nedges) = (*nedges)/2;

  return(OK);
}
/*-----------------------------------------------------------------------------------------------*/
static status recursive_count_vertices_edges_component(graph_vertex curr_vertex, 
						       int* nvertices, 
						       int* nedges)
/*
 * Counts the number of vertices and edges of the connected component reachable 
 * from curr_vertex. 
 * Preconditions: on entry, all vertices must be marked as non-visited, 
 * and *nvertices and *nedges must be zero.
 *
 * A typical call to this function is:
 *     ...
 *     nvertices = 0; nedges = 0;
 *     count_vertices_edges_component(component, NULL, &nvertices, &nedges);
 *     ...
 */
{
    llist edge_pointer;
    llist neigh_vertex;
    
    /* Protection against the case of NULL pointers */
    if(curr_vertex==NULL)
	return ERROR;
    
    /* Mark current vertex as visited */
    VISITED(curr_vertex)=TRUE;
    
    /* Increase vertex and edge counts */
    (*nvertices)++;
    (*nedges) += length(EMANATING(curr_vertex));

    /* For all neighboring vertices of curr_vertex ... */
    for(edge_pointer=EMANATING(curr_vertex); edge_pointer!=NULL; edge_pointer=NEXT(edge_pointer))
      {
	/* Pointer to current neighboring vertex */
	neigh_vertex = VERTEX_POINTER(edge_pointer);

	/* If neighboring vertex has not been visited yet (this stops looping) */
	if(!VISITED(neigh_vertex)) 
	  /* Visit the vertex and its descendants */
	  if(recursive_count_vertices_edges_component(neigh_vertex, nvertices, nedges)==ERROR)
	    return ERROR;
      }

    return OK;
}


/*****************************************************************************************************
 *
 *  Section 6 - Graph printing functions
 *
 *****************************************************************************************************/

void print_graph(FILE* fd, graph G, 
		 status(*p_print_vertex)(FILE*, generic_ptr), 
		 status(*p_print_edge)(FILE*, generic_ptr))
/*
 * Prints the graph to a file. Uses p_print_vertex() and p_print_edge() to print 
 * the specific vertex and edge data of the graph. These are user-defined functions
 * passed to print_graph as pointers to them. Use print_graph_skeleton if you
 * just need to concisely print out the basic adjacency list structure.
 */
{
    llist V=NULL;
    llist E=NULL;
    status err;

    /* Exit if empty graph */
    if(G==NULL) 
    {
      fprintf(fd, "Empty graph in print_graph()\n");
	return;
    }

    /* Iterate over all vertices */
    fprintf(fd, "\n\nGraph map\n");
    while((V=list_iterator(G, V))!=NULL)
    {

      /* Print info of this vertex */
      fprintf(fd,"Vertex number %u:\n", VERTEX_NUMBER(V));
      fprintf(fd,"\tVisited = %d\n", VISITED(V));
      fprintf(fd,"\tLabel = %d\n", LABEL(V));
      fprintf(fd,"\tList of labels = ");
      print_prolog_list(fd, LABELS(V), print_label_id);
      fprintf(fd,"\n");
      fprintf(fd, "\tCoordinates (x,y) = (%.2f,%.2f)\n", X(V), Y(V));
      if(p_print_vertex!=NULL)
	{
	  if(SPECIFIC_VERTEX_DATA(V)==NULL)
	    glr_error("User asked to print spec. vertex data that does not exist");

	  fprintf(fd, "\tSpecific vertex data:\n");
	  err = (*p_print_vertex)(fd, SPECIFIC_VERTEX_DATA(V));
	  if(err==ERROR)
	    glr_error("Error:: printing of specific vertex data failed in print_graph");
	}
      fprintf(fd, "\tEmanating edges:\n");
      
      /* Print info of all EMANATING edges */
      for(E=EMANATING(V); E!=NULL; E=NEXT(E))
	{
	  fprintf(fd,"\t\tEdge (%d,%d):\n", SOURCE(E), DESTINATION(E));
	  fprintf(fd,"\t\t\tCopy  = %d\n", COPY(E));
	  fprintf(fd,"\t\t\tSense = %d\n", SENSE(E));
	  if(p_print_edge!=NULL)
	    {
	      if(SPECIFIC_EDGE_DATA(E)==NULL)
		glr_error("User asked to print spec. edge data that does not exist");

	      fprintf(fd, "\t\t\tSpecific edge data:\n");
	      err = (*p_print_edge)(fd, SPECIFIC_EDGE_DATA(E));
	      if(err==ERROR)
		glr_error("Error:: Printing of specifc_edge_data failed in print_graph");
	    }
	}
    }
}
/*-----------------------------------------------------------------------------------------------*/
void print_graph_skeleton(FILE* fd, graph G)
/*
 * Print the "skeleton" of a graph, i.e., only the basic structure of the adjacency list model. 
 * It does not print information contained in the specific_*_data typed fields of the vertices 
 * and edges. (Use "print_graph" for that purpose.)
 */
{
    llist V;
    
    if(G==NULL) 
    {
      fprintf(fd, "Empty graph in print_graph()\n");
	return;
    }
    fprintf(fd, "\n\nGraph map\n");

    V=NULL;
    while((V=list_iterator(G, V))!=NULL)
    {

      /* Print info of this vertex */
      fprintf(fd,"[%u]", VERTEX_NUMBER(V));
      print_prolog_list(fd, LABELS(V), print_label_id);
      fprintf(fd,"-->");
      
      /* Print the list of EMANATING vertices */
      {
	llist E=NULL;
	fprintf(fd,"[vdest,sense]: ");
	while((E=list_iterator(EMANATING(V), E))!=NULL)
	  fprintf(fd,"[%u,%d] ",
		 DESTINATION(E), 
		 SENSE(E));
      }
      fprintf(fd,"\n");
    }
    fprintf(fd,"\n");
}
/*-----------------------------------------------------------------------------------------------*/
void print_graph_analysis(FILE* fd, graph G)
{
  analyze_graph(G,fd);
}
/*-----------------------------------------------------------------------------------------------*/
void print_label_id(FILE* fd, llist label_pointer)
{
  fprintf(fd, "\'%d\'", THISLABEL(label_pointer));
}
/*-----------------------------------------------------------------------------------------------*/
void print_vertex_id(FILE* fd, graph_vertex vertex_pointer)
{
  if(DATA(vertex_pointer)!=NULL)
    fprintf(fd, "\'%u\'", VERTEX_NUMBER(vertex_pointer));
  else
    glr_error("Fatal error:: print_vertex_id() failed, there's no data stored in this vertex!!");
}
/*-----------------------------------------------------------------------------------------------*/
void print_list_vertices(FILE* fd, llist vertices)
{
  print_prolog_list(fd, vertices, print_vertex_id);
}
/*-----------------------------------------------------------------------------------------------*/
void print_list_cycles(FILE* fd, llist cycles)
/* 
 * Prints the contents of the list cycles, the one obtained after detect_fundamental_cycles()
 */
{
  llist curr_C;
  int n=0;
  
  if(cycles == NULL)
    fprintf(fd,"There are no cycles\n");

  for(curr_C=cycles; curr_C!=NULL; curr_C=NEXT(curr_C))
  {
    fprintf(fd,"Cycle %d\n", n);
    fprintf(fd,"-----------------------------\n");
    fprintf(fd,"list of vertices=");
    print_list_vertices(stdout, CYC_VERTICES(curr_C));
    fprintf(fd,"\n");
    fprintf(fd,"\n");
    n++;
  }
}

/*****************************************************************************************************
 *
 *  Section 6 - Miscellaneous functions
 *
 *****************************************************************************************************/

boolean empty_graph(graph G)
{
  return(G==NULL);
}
/*----------------------------------------------------------------------------------------------------*/
status copy_adjacent(graph_vertex pv, llist* adjacent)
/*
 * Generates a list "adjacent" of pointers to the adjacent vertices of 
 * vertex pv (a vertex pointer actually). Before calling copy_adjacent(), the list 
 * "adjacent" must have been previously initialized with init_list().
 * The returned list "adjacent" can be viewed as a "list of vertices" and, thus,
 * it is legal to ask for VERTEX_NUMBER(node), VISITED(node), for any "node" of 
 * "adjacent". To destroy "adjacent", you might want to do
 *
 *     destroy_list(&adjacent,NULL)
 *
 * in order not to destroy the vertices themselves.
 */
{
  llist curr_e;
  graph_vertex pdv; 

  if(pv==NULL || EMANATING(pv)==NULL)
    return(ERROR);
  
  /* Visit emanating edges and ... */
  for(curr_e=EMANATING(pv);curr_e!=NULL;curr_e=NEXT(curr_e)) 
    {
      /* ... copy the pointer to their destination vertex */
      pdv = VERTEX_POINTER(curr_e);
      if(append(adjacent, (generic_ptr)(DATA(pdv)))==ERROR)
	glr_error("Error:: CopyAdjacent() failed to insert a node to adjacent.");
    }
  
  return(OK);
}
/*----------------------------------------------------------------------------------------------------*/
int cmp_vertex(generic_ptr p_datapointer1, generic_ptr p_datapointer2)
{
  return( ((vertex_data*)p_datapointer1)->vertex_number - 
	  ((vertex_data*)p_datapointer2)->vertex_number );
}
/*-----------------------------------------------------------------------------------------------*/
llist find_vertex(graph G, vertex_id vertex_number)
{
    llist vertex_pointer;
    vertex_data v;

    v.vertex_number=vertex_number;
    if(find_key(G, (generic_ptr)&v, cmp_vertex, &vertex_pointer)==ERROR)
	return(NULL);

    return(vertex_pointer);
}
/*----------------------------------------------------------------------------------------------------*/
llist find_destin(llist Edges, vertex_id vertex_number)
/*
 * Finds the edge "e" within the list of "Edges" whose DESTINATION(e) is 
 * "vertex_number". Returns NULL if no such edge is not found.
 */
{
  llist curr=NULL;
  while( (curr=list_iterator(Edges, curr))!=NULL)
    if(DESTINATION(curr)==vertex_number)
      return curr;
  return NULL;
}
/*----------------------------------------------------------------------------------------------------*/
llist find_destin_with_pointer(llist Edges, graph_vertex pv)
/*
 * Finds the edge "e" within Edges whose VERTEX_POINTER(e) is "pv".
 * Returns NULL if this edge is not found.
 */
{
  llist curr=NULL;
  while( (curr=list_iterator(Edges, curr))!=NULL)
    if(VERTEX_POINTER(curr)==pv)
      return curr;
  return NULL;
}
/*-----------------------------------------------------------------------------------------------*/
void glr_error(char* error)
{
  fprintf(stderr,"%s\n", error);
  fprintf(stderr, "Exiting...\n");
  exit(1);
}
