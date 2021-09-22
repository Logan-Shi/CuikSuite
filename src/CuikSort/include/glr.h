#ifndef GLRH
#define GLRH

/*******************************************************************
 * GLR 0.1 
 * Graph Library 0.2
 *
 * Filename: glr.h
 * Copyright: (c) Lluis Ros 1995-2005
 * Creation: April 1995
 * Last revision: December 2005
 * 
 *******************************************************************/

#include "llr.h"

/********************************************************************
 *  graph type
 ********************************************************************/
typedef llist graph;  /* A graph is simply a list of vertices */

/********************************************************************
 *  graph_vertex and vertex_data types.
 ********************************************************************/
typedef llist graph_vertex;       /* Graph vertex data type */

typedef unsigned int vertex_id;  /* Vertex_id data type */
typedef struct{
  vertex_id vertex_number;       /* Numerical identifyier of the vertex */
  llist emanating;                /* List of edges emanating from the vertex */
  boolean visited;               /* Visited flag used in traversal routines */
  int label;                     /* Multipurpose label, e.g. to colour cycles */
  llist labels;                   /* List of labels of fundamental cycles that 
                                  * pass through this vertex 
				  */
  double x, y;                   /* (x,y) coords of the vertex (for eventual plots) */
  generic_ptr specific_data;     /* Pointer to the data stored in the vertex */
} vertex_data;

/* 
 * Accessor macros of a vertex 
 */

#define VERTEX_NUMBER(V)        (((vertex_data*)DATA(V))->vertex_number)
#define EMANATING(V)	        (((vertex_data*)DATA(V))->emanating)
#define VISITED(V)              (((vertex_data*)DATA(V))->visited)
#define LABEL(V)                (((vertex_data*)DATA(V))->label)
#define THISLABEL(L)            (*((int*)DATA(L)))
#define LABELS(V)               (((vertex_data*)DATA(V))->labels)
#define X(V)                    (((vertex_data*)DATA(V))->x)
#define Y(V)                    (((vertex_data*)DATA(V))->y)
#define SPECIFIC_VERTEX_DATA(V) (((vertex_data*)DATA(V))->specific_data)

/********************************************************************
 *  edge_data type
 ********************************************************************/
typedef llist graph_edge;    /* Graph_edge data type */
typedef struct{
  vertex_id vertex_ini;     /* Vertex id of the initial vertex of this edge */
  vertex_id vertex_number;  /* Vertex id of the final vertex of this edge */
  llist vertex_pointer;      /* Vertex pointer of the final vertex of this edge */
  int copy;                 /* 1 or 2, depending of whether this is the (i,j) or 
			     * (j,i) edge. See the function add_edge_with_pointers. 
                             */ 
  int sense;                 /* Sense of a vertex during a depth-1st seach 
                              * (UP, DOWN, or NOSENSE), as defined below. 
			      */
  generic_ptr specific_data; /* Pointer to the data stored in the edge */
} edge_data;

/* 
 * Accessor macros of an edge
 */

#define SOURCE(E)             (((edge_data*)DATA(E))->vertex_ini)
#define DESTINATION(E)        (((edge_data*)DATA(E))->vertex_number)
#define VERTEX_POINTER(E)     (((edge_data*)DATA(E))->vertex_pointer)
#define COPY(E)               (((edge_data*)DATA(E))->copy)
#define SENSE(E)              (((edge_data*)DATA(E))->sense)
#define SPECIFIC_EDGE_DATA(E) (((edge_data*)DATA(E))->specific_data)

/********************************************************************
 *  Cycle_data type
 ********************************************************************/
typedef struct {
  llist vertices; /* list of vertices of the cycle */
  llist edges;    /* list of edges of the cycle */
  int label;     /* label of this cycle */
} cycle_data;
  
#define CYC_VERTICES(C) (((cycle_data*)DATA(C))->vertices)
#define CYC_EDGES(C)    (((cycle_data*)DATA(C))->edges)
#define CYC_LABEL(C)    (((cycle_data*)DATA(C))->label)

/********************************************************************
 *  Other macros
 ********************************************************************/

#define UP 1     
#define DOWN 0
#define NOSENSE -1
#define NOLABEL -1

/* end condition for the up() function */
#define BY_NODE_ID 1
#define BY_LABEL 0

/* labeling mode for up() */
#define DOLABEL 1
#define DONTLABEL 0


/********************************************************************
 *  Primitive operations of the "graph" abstract data type
 ********************************************************************/

/*
 * Section 1 - Graph constructors
 */

status  init_graph(graph *p_G);
status  add_vertex(graph* p_G, vertex_id vertex_number, generic_ptr specific_data);
status  append_vertex(graph* p_G, vertex_id vertex_number, generic_ptr specific_data);
status  insert_vertex(graph* p_G, vertex_id vertex_number, generic_ptr specific_data);
status  add_edge(graph G, vertex_id vertex1, vertex_id vertex2, generic_ptr specific_data);
status  add_edge_with_pointers(graph_vertex pv1, graph_vertex pv2, generic_ptr specific_data);
status  edge_append(llist* p_L, vertex_id vertex_ini, vertex_id vertex_number, 
		    generic_ptr specific_data, graph_vertex vertex_pointer, int copy);
status  duplicate_graph(graph G1, graph* G2, 
			status (*p_copy_vertex)(generic_ptr,generic_ptr*), 
			status (*p_copy_edge)(generic_ptr,generic_ptr*));

/*
 * Section 2 - Graph destructors
 */

void   destroy_graph(graph* p_G, 
		     void (*p_free_specific_vertex_data)(generic_ptr),
		     void (*p_free_specific_edge_data)(generic_ptr));
status destroy_graph_specific_data(graph G, 
				   void (*p_free_specific_vertex_data)(generic_ptr),
				   void (*p_free_specific_edge_data)(generic_ptr));
status delete_vertex(graph* p_G, vertex_id vertex_number, 
		     void (*p_free_specific_edge_data)(generic_ptr));
status delete_vertex_with_pointer(graph* p_G, graph_vertex vertex_pointer, 
				  void (*p_free_specific_edge_data)(generic_ptr));
status delete_vertex_and_edges(graph* p_G, vertex_id vertex_number, 
			       void (*p_free_specific_vertex_data)(generic_ptr),
			       void (*p_free_specific_edge_data)(generic_ptr));
status delete_vertex_and_edges_with_pointer(graph* p_G, graph_vertex vertex_pointer,
					    void (*p_free_specific_vertex_data)(generic_ptr),
					    void (*p_free_specific_edge_data)(generic_ptr));
status delete_edge(graph G, vertex_id vid1, vertex_id vid2, 
		   void (*p_free_specific_edge_data)(generic_ptr));
status delete_edge_with_pointers(graph_vertex origin1, graph_edge destin1, 
				 graph_vertex origin2, graph_edge destin2, 
				 void (*p_free_specific_edge_data)(generic_ptr));


/*
 * Section 3 - Graph traverse functions
 */

status  simply_visit_all(graph G);
status  depth_first(graph G, graph_vertex vertex_pointer, status (*p_visit_f)(llist));
status  depth_first_vertices_edges(graph G, graph_vertex vertex_pointer, 
				   boolean (*p_is_reachable)(llist,llist),
				   status  (*p_action_vertex_before)(llist),
				   status  (*p_action_edge_before)(llist,llist,llist),
				   status  (*p_action_edge_after)(llist,llist,llist));
status  mark_all_unvisited(graph G);
status  mark_senses_down(graph G, graph_vertex vertex_pointer, boolean (*p_is_reachable)(llist,llist) );
void    clear_all_senses(graph G);

/*
 * Section 4 - Detection of fundamental cycles and connected components
 */

status  detect_fundamental_cycles(graph G, llist* cycles,boolean (*p_is_reachable)(llist,llist)); 
void    free_cycles_data(generic_ptr data);
status  connected_components(graph G, llist* components);

/*
 * Section 5 - Graph analysis functions
 */

void    analyze_graph(graph G, FILE* fd);
int     count_vertices(graph G);
int     count_edges(graph G);
int     degree(graph_vertex vertex_pointer);
status  count_vertices_edges_component(llist component, int* nvertices, int* nedges);

/*
 * Section 6 - Graph printing functions
 */
void    print_graph(FILE* fd, graph G, 
		    status(*p_print_vertex)(FILE*, generic_ptr), 
		    status(*p_print_edge)(FILE*, generic_ptr));
void    print_graph_skeleton(FILE* fd, graph G);
void    print_graph_analysis(FILE* fd, graph G);
void    print_label_id(FILE* fd, llist label_pointer);
void    print_vertex_id(FILE* fd, graph_vertex vertex_pointer);
void    print_list_vertices(FILE* fd, llist vertices);
void    print_list_cycles(FILE* fd, llist cycles);


/*
 * Section 7 - Miscelaneous functions
 */

boolean empty_graph(graph G);
status  copy_adjacent(graph_vertex pv, llist* adjacent);
int     cmp_vertex(generic_ptr p_datapointer1, generic_ptr p_datapointer2);
llist    find_vertex(graph G, vertex_id vertex_number);
llist    find_destin(llist Edges, vertex_id vertex_number);
llist    find_destin_with_pointer(llist Edges, graph_vertex pv);
void    glr_error(char* error);

#endif /* GLRH */
