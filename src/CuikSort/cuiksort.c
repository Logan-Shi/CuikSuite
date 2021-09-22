#include "box_list.h"
#include "box.h"
#include "glr.h"
#include "llr.h"
#include "defines.h"
#include "error.h"
#include "filename.h"


#include <string.h>
#include <stdlib.h>

/** \file cuiksort.c

    \brief Main body of the \ref cuiksort.c "cuiksort" application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuiksort    [label="cuiksort"  color="#99ff99" shape=ellipse];
      
      param   [label="param"   color="#ff9999" ];
      solIn   [label="sol"  color="#ff9999" ];
      solOut  [label="_X.sol" color="#ff9999" ];

      param -> cuiksort
      solIn -> cuiksort;
      cuiksort -> solOut;
    }
    \enddot
    </center>


    Continuous solution sets need to be sorted for
    for its animation to be smooth. Moreover, when sorting the boxes we determine
    the number of connected components of the solution set.

    This code and its dependencies (llist.h, llist.c, glr.h, glr.c, general.h)
    are not documented using doxygen but directly in the code because they come
    from old developments. 

*/
/************************************************************************************/
/** \cond */
/* Topologies used when sorting boxes */

#define RN_TOPOLOGY 0       // Defines Rn topology to be used in graph construction
#define TORUS_TOPOLOGY 1    // Defines Torus topology to be used in graph construction

/* Ways to traverse a graph*/
#define TRAVERSE_DEPTH_FIRST    0   // Traverse the graph in depth-first order
#define TRAVERSE_CYCLES         1   // Traverse only the cycles of the graph
#define TRAVERSE_WITHOUT_ORDER  2   // Traverse the graph with no specific order

/* Tolerance in the box intersection when defining a graph  */
#define INTERSECT_TOL   1e-3  // Threshold to decide whether two boxes intersect

boolean NormalIntervalsIntersect(Tinterval *i1, Tinterval *i2);
boolean AngleIntervalsIntersect(Tinterval *i1, Tinterval *i2);
boolean BoxesAreNeighboring(Tbox* box1, Tbox* box2, double tolerance, int topology);
boolean BoxesIntersect(Tbox* box1, Tbox* box2, double tolerance, int topology);
void ConnectFirstBoxInGraphOfBoxes(graph G,double tolerance,int topology);
graph GraphOfBoxes(Tlist* boxlist, double tolerance, int topology);
status TraverseDepthFirstComponent(graph_vertex root_v, graph_vertex curr_v, Tlist* boxlist);
llist TraverseDepthFirstGraphOfBoxes(graph G);
llist TraverseCyclesGraphOfBoxes(graph G, int nskip);
llist TraverseAllNodesWithoutOrder(graph G);
llist TraverseGraphOfBoxes(graph G, int traversal_type);
void PrintWalk(FILE* f, llist walk, int stepsize);

//*******************************************************************************

//******************************************************************************
// NormalIntervalsIntersect
//
// Tells whether two "normal" intervals intersect. The intervals must have their
// lower limit below their upper limit.
//******************************************************************************
boolean NormalIntervalsIntersect(Tinterval *i1, Tinterval *i2)
{
  return(Intersect(i1,i2));
}

//******************************************************************************
// AngleIntervalsIntersect
//
// Tells whether two angle intervals intersect. The intervals must be in the 
// range [0,2pi]. Intervals with lower limit > upper limit are allowed, provided 
// the limits are within the [0,2pi] range.
//******************************************************************************
boolean AngleIntervalsIntersect(Tinterval *i1, Tinterval *i2)
{
  double i1l, i1u, i2l, i2u;
  Tinterval a, b, c, d;

  // Interval limits
  i1l =  i1->lower_limit;  i1u =  i1->upper_limit;
  i2l =  i2->lower_limit;  i2u =  i2->upper_limit;

  // If intervals are "normal" (with lower < upper)...
  if(i1l <= i1u && i2l <= i2u)
    {
      // ... check first whether they are connected through 0 or 2pi
      if((i1l == 0 && i2u == 2*M_PI) || (i2l == 0 && i1u == 2*M_PI))
	return(TRUE);
      // else check intersection in the normal way
      else
	return(Intersect(i1,i2));
    }

  // If i1 has lower > upper ...
  if(i1l > i1u)
    { 
      // ... split i1 into two intervals a and b, and call me again
      NewInterval(i1l,2*M_PI,&a);
      NewInterval(0,i1u,&b);
      return(AngleIntervalsIntersect(&a,i2) || AngleIntervalsIntersect(&b,i2));
    }

  // If i2 has lower > upper ...
  if(i2l > i2u)
    {
      // ... split i2 into two intervals c and d, and call me again
      NewInterval(i2l,2*M_PI,&c);
      NewInterval(0,i2u,&d);
      return(AngleIntervalsIntersect(i1,&c) || AngleIntervalsIntersect(i1,&d));
    }

  return(FALSE);
}

//******************************************************************************
// ConnectFirstBoxInGraphOfBoxes - Connects the first box of a box graph to any 
//                                 neighboring boxes.
//******************************************************************************

boolean BoxesAreNeighboring(Tbox* box1, Tbox* box2, double tolerance, int topology)
{
  return(BoxesIntersect(box1,box2,tolerance,topology));
}

//******************************************************************************
// BoxesIntersect - Returns TRUE if the given boxes intersect
// Two boxes intersect iff no pair of corresponding intervals are disjoint
//******************************************************************************
boolean BoxesIntersect(Tbox* box1, Tbox* box2, double tolerance, int topology)
{
  Tinterval* intv1;
  Tinterval* intv2;
  unsigned int i, dim;
  double i1l, i1u, i2l, i2u;
  boolean intersect;
  
  // Get boxes dimension
  dim = GetBoxNIntervals(box1);

  // Iterate over all intervals of the boxes
  intersect=TRUE;
  for(i=0;((intersect)&&(i<dim));i++)
    {
      // Get corresponding intervals
      intv1 = GetBoxInterval(i,box1);
      intv2 = GetBoxInterval(i,box2);

      // Backup interval limits
      i1l =  intv1->lower_limit;  i1u =  intv1->upper_limit;
      i2l =  intv2->lower_limit;  i2u =  intv2->upper_limit;

      // Enlarge intervals a samll amount
      intv1->lower_limit =  intv1->lower_limit - tolerance;
      intv1->upper_limit =  intv1->upper_limit + tolerance;
      intv2->lower_limit =  intv2->lower_limit - tolerance;
      intv2->upper_limit =  intv2->upper_limit + tolerance;

      // Test intersection
      switch(topology)
	{
	case RN_TOPOLOGY:
	  intersect = NormalIntervalsIntersect(intv1,intv2);
	  break;
	case TORUS_TOPOLOGY:
	  intersect = AngleIntervalsIntersect(intv1,intv2);
	  break;
	}

      // Restore original intervals
      intv1->lower_limit = i1l;  intv1->upper_limit = i1u;
      intv2->lower_limit = i2l;  intv2->upper_limit = i2u;
    }

  // If all intervals intersect, the boxes intersect
  return(intersect);
}

//******************************************************************************
// ConnectFirstBoxInGraphOfBoxes - Connects the first box of a box graph to any 
//                                 neighboring boxes.
//******************************************************************************
void ConnectFirstBoxInGraphOfBoxes(graph G,double tolerance,int topology)
{
  llist curr_v;
  llist first_v;
  Tbox* first_box;
  Tbox* curr_box;
  static int edge_count=1;

  // Pointer to first vertex and its box
  first_v = G;
  if(first_v==NULL)
    Error("Error: empty graph in ConnectFirstBox");

  first_box = (Tbox*)SPECIFIC_VERTEX_DATA(first_v);

  // Iterate from the second to the last vertices (boxes)
  for(curr_v=NEXT(first_v); curr_v!=NULL; curr_v=NEXT(curr_v))
    {
      curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(curr_v);
      if(BoxesAreNeighboring(first_box,curr_box,tolerance,topology))
	{
	  add_edge_with_pointers(first_v,curr_v,NULL);
	  printf("Edge added number %d\n", edge_count);
	  edge_count++;
	}
    }
}

graph GraphOfBoxes(Tlist* boxlist, double tolerance, int topology)
{
  graph G;
  Tbox* curr_box;
  Titerator iter;
  int boxnumber;

  // Initialize graph of boxes  
  if(init_graph(&G)==ERROR)
    Error("Error:: init_graph() failed in GraphOfBoxes()");

  // Iterate over the list of boxes
  InitIterator(&iter,boxlist);
  First(&iter);
  boxnumber=1;
  while(!EndOfList(&iter))
    {
      // Get a box from the list
      curr_box=(Tbox*)GetCurrent(&iter);
      printf("Adding box %d to the graph\n", boxnumber);

      // Add it as the first box of the graph
      if(insert_vertex(&G,boxnumber,(void*)curr_box)==ERROR)
	Error("Error in Graph of Boxes: couldn't insert vertex");

      // Connect the box to its neighbouring boxes
      ConnectFirstBoxInGraphOfBoxes(G,tolerance,topology);

      // Advance cursors and box number
      Advance(&iter);
      boxnumber++;
    }

  return(G);
}


//*******************************************************************************
// TraverseDepthFirstComponent
// Preconditions: at the top-level call all vertices must be marked as non-visited.
//*******************************************************************************

status TraverseDepthFirstComponent(graph_vertex root_v, 
				   graph_vertex curr_v, 
				   Tlist* boxlist)
{
  llist curr_e;           // Current edge: an edge emanating from current vertex
  llist adj_v;            // The vertex adjacent to current vertex 
  Tbox* curr_box;        // The box stored in current vertex
/*   static int count = 0; */

  // protection against the case of NULL pointers 
  if(root_v==NULL || curr_v==NULL)
    return ERROR;
  
/*   // Print the degree */
/*   if(degree(curr_v)>2) */
/*     { */
/*       printf("%d:: degree = %d\n", count, degree(curr_v)); */
/*       curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(curr_v); */
/*       PrintBox(stdout,curr_box); */
/*     } */
/*   count++; */

  // mark the current vertex as visited
  VISITED(curr_v)=TRUE;
  
  // store the box in it
  curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(curr_v);
  AddLastElement((void*)curr_box,boxlist);
  
  // for all neighboring vertices of curr_v ... 
  for(curr_e=EMANATING(curr_v); curr_e!=NULL; curr_e=NEXT(curr_e))
    {
      // get pointer to the current adjacent vertex 
      adj_v = VERTEX_POINTER(curr_e);
      
      // if adjacent vertex is not yet visited ... 
      if(!VISITED(adj_v))
	{
	  // visit the vertex and its descendants ... 
	  if(TraverseDepthFirstComponent(root_v,adj_v,boxlist)==ERROR)
	    return ERROR;
	  // store the box again upon backtracking 
	  // AddLastElement((void*)curr_box,boxlist);
	}
    }
  
  return OK;
}

//*******************************************************************************
// TraverseAllNodesWithoutOrder
//*******************************************************************************

llist TraverseAllNodesWithoutOrder(graph G)
{
  llist walk_list;           // A list of connected box components
  graph_vertex curr_v;      // Current vertex while searching for connected components
  Tlist* box_list;          // A list of boxes for a walk
  Tbox* curr_box;           // The box stored in current vertex

  // pertinent protection
  if(G==NULL)
    Error("Error in TraverseDepthFirstGraphOfBoxes: empty graph");

  // Initialize list of walks to be returned
  if(init_list(&walk_list)==ERROR)
    Error("Error in TraverseDepthFirstGraphOfBoxes: unable to initialize list");

  // Traverse the graph
  NEW(box_list,1,Tlist);
  InitListOfBoxes(box_list);
  
  for(curr_v=G; curr_v!=NULL; curr_v=NEXT(curr_v)) 
    {
      curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(curr_v);
      AddLastElement((void*)curr_box,box_list);
    }
  
  // Insert list of boxes into walk_list
  insert(&walk_list,(generic_ptr)box_list);

  // Return list of walks
  return(walk_list);
}


//*******************************************************************************
// TraverseDepthFirstGraphOfBoxes
// 
// Traverses all connected components of a graph G, in depth first order. Returns
// a list of walks, where wach walk is a depth-first traversal of a connected 
// component. Each node of this returned list actually points to a list of boxes, 
// the boxes corresponding to the mentioned walk.
//*******************************************************************************

llist TraverseDepthFirstGraphOfBoxes(graph G)
{
  llist walk_list;           // A list of connected box components
  graph_vertex curr_v;      // Current vertex while searching for connected components
  Tlist* box_list;          // A list of boxes for a walk

  // pertinent protection
  if(G==NULL)
    Error("Error in TraverseDepthFirstGraphOfBoxes: empty graph");

  // Initialize list of walks to be returned
  if(init_list(&walk_list)==ERROR)
    Error("Error in TraverseDepthFirstGraphOfBoxes: unable to initialize list");

  // Traverse the graph
  mark_all_unvisited(G);
  for(curr_v=G; curr_v!=NULL; curr_v=NEXT(curr_v)) {
    if(!VISITED(curr_v)) {
      // Traverse the connected component of current vertex, ntimes times
      NEW(box_list,1,Tlist);
      InitListOfBoxes(box_list);
      TraverseDepthFirstComponent(curr_v, curr_v, box_list);
      insert(&walk_list,(generic_ptr)box_list);
    }
  }
  
  // Return list of walks
  return(walk_list);
}


//*******************************************************************************
// TraverseCyclesGraphOfBoxes
//
// Traverses the cycles of a graph G. Returns a list of cycles. Each node in this 
// list points to a cycle of boxes.
//*******************************************************************************

llist TraverseCyclesGraphOfBoxes(graph G, int nskip)
{
  llist components;       // List of components of G
  llist root;             // Pointer to a vertex of current component
  llist cycles;           // List of cycles of a component
  llist walk_list;        // List of walks to be returned
  Tlist* box_list;       // The list of boxes of a walk
  Tbox* curr_box;        // The box stored in current vertex
  llist node_comp;        // A node of the lit "components"
  llist node_cyc;         // A node of the list "cycles"
  llist node_vert;        // A node of the list CYC_VERTICES(cycles)
  int i;

  // Initialize list of walks to be returned
  if(init_list(&walk_list)==ERROR)
    Error("Error in TraverseCyclesGraphOfBoxes: unable to initialize list");

  // Generate list of connected components
  init_list(&components);
  if(connected_components(G,&components)==ERROR)
    Error("Error in TraverseCyclesGraphOfBoxes: connected_components failed");

  printf("Generating list of walks. One walk for each cycle of the graph...\n");
  printf("\tNumber of connected components is %d\n", length(components));

  // Get the cycles of each connected component
  for(node_comp=components; node_comp!=NULL; node_comp=NEXT(node_comp)) 
    {
      // Get pointer to current component
      root = (llist)(DATA(node_comp));
      printf("\tNew component:\n");

      // Obtain the cycles of this component
      init_list(&cycles);
      if(detect_fundamental_cycles(root, &cycles, NULL)==ERROR)
	Error("Error in TraverseCyclesGraphOfBoxes: failed to detect fundamental cycles");
      printf("\t\tNumber of cycles of this component is %d\n", length(cycles));

      // Generate a walk for each cycle, and add it to the list of walks
      for(node_cyc = cycles; node_cyc!=NULL; node_cyc=NEXT(node_cyc))
	{
	  // Generate the list of boxes of this cycle (of type Tlist) 
	  NEW(box_list,1,Tlist);
	  InitListOfBoxes(box_list);
	  for(node_vert=CYC_VERTICES(node_cyc); node_vert!=NULL; node_vert=NEXT(node_vert)) 
	    {
	      // We convert the *list* of vertices to a *Tlist* of boxes
	      // curr_vertex = (graph_vertex)DATA(node_vert);
	      // curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(curr_vertex);
	      curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(node_vert);
	      AddLastElement((void*)curr_box,box_list);
	      
	      // Skip nskip boxes (usefull when clustering exists, e.g. cycloheptane)
	      i=0;
	      while(NEXT(node_vert)!=NULL && i<nskip)
		{
		  node_vert=NEXT(node_vert);
		  i++;
		}
	    }

	  // Add the list of boxes as a node of the list of walks (of type list)
	  append(&walk_list,(generic_ptr)box_list);
	}
      
      // Destroy temporary list of cycles
      destroy_list(&cycles,NULL);
    }
  
  // Destroy dynamic memory
  destroy_list(&components,NULL);

  return(walk_list);
}

//*******************************************************************************
// TraverseGraphOfBoxes
//
// Traverses a graph of boxes. Returns a list of walks. Each 
// walk is a list of boxes corresponding either to a cycle (when 
// traversal_type==TRAVERSE_CYCLES) or to a connected component traversed
// in a depth-first order (when traversal_type==TRAVERSE_DEPTH_FIRST)
//*******************************************************************************

llist TraverseGraphOfBoxes(graph G, int traversal_type)
{  
  llist walk_list=NULL;

  // Different traversals are possible
  switch(traversal_type) 
    {
    case TRAVERSE_CYCLES:
      // Returns a list of cycle traversals
      walk_list = TraverseCyclesGraphOfBoxes(G,0);
      break;    
    case TRAVERSE_DEPTH_FIRST:
      // Returns a list of connected component traversals
      walk_list = TraverseDepthFirstGraphOfBoxes(G);
      break;
    case TRAVERSE_WITHOUT_ORDER:
      // Returns a list of all boxes in the graph, with no specific order
      walk_list = TraverseAllNodesWithoutOrder(G);
      break;
    default:
      // Detect invalid traversal type
      Error("Error in TraverseGraphOfBoxes: invalid traversal type");
      break;
    }

  return(walk_list);
}  

//*******************************************************************************
// PrintWalk
// Prints the boxes of a walk to a file "f". 
//*******************************************************************************
void PrintWalk(FILE* f, llist walk, int stepsize)
{
  Tbox* curr_box;
  Titerator iter;
  Tlist* walk_box_list;
  unsigned int i;

  // Get the list of boxes of the walk
  walk_box_list = (Tlist*)DATA(walk);

  // Iterate over all boxes and print them
  InitIterator(&iter,walk_box_list);
  First(&iter);
  while(!EndOfList(&iter))
    {
      // Get current box 
      curr_box = (Tbox *)GetCurrent(&iter);

      // Print the box
      PrintBox(f,curr_box);

      // Forward stepsize elements
      for(i=0;i<(unsigned int)stepsize;i++)
      Advance(&iter); 
    }
}
/**\endcond*/

/** 
   \brief Main body of the \b cuiksort application.

   Main body of the \b cuiksort application.

   Usage:<br>
     - \b cuiksort \e base_name \e tolerance \e topology \e trav_mode \e step_size
     .
   Where:
     - \e base_name:  The name of the \e .sol file without the extension.
     - \e tolerance:  Tolerance when detecting box intersections.
     - \e topology:  May be 'r' (for Rn topology) or 't' (for torus topology). Optional. The
                     default value is 'r'.
     - \e trav_mode:  May be 'd' (depth 1st) or 'c' (for cycles) or 'u' (for unordered). Optional. The
                      default value is 'd'.
     - \e step_size:  Stepsize used when printing the boxes of a walk to a file. Optional. The
                      default value is '1'.
     .
   If one of the optional parameters is given then all the previous parameters need to be
   given too.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuiksort command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{
  if (argc<2)
    {
      fprintf(stdout,"Use:\n");
      fprintf(stdout,"     cuiksort <basename> <tolerance> <topology> <travmode> <stepsize> \n");
      fprintf(stdout,"Where:\n");
      fprintf(stdout,"     basename :  The basename of the *.sol input file\n");
      fprintf(stdout,"     tolerance:  Tolerance when detecting box intersections\n");
      fprintf(stdout,"     topology :  May be 'r' (for Rn topology) or 't' (for torus topology)\n");
      fprintf(stdout,"     travmode :  May be 'd' (depth 1st) or 'c' (for cycles) or 'u' (for unordered)\n");
      fprintf(stdout,"     stepsize :  Stepsize used when printing the boxes of a walk to a file\n");
      fprintf(stdout,"Examples:\n");
      fprintf(stdout,"     sortboxes ./examples/cyclohexane r d 1\n");
      fprintf(stdout,"     sortboxes ./examples/cycloheptane r d 1\n");
      fprintf(stdout,"     sortboxes ./examples/cycloctane r d 1\n");
    }
  else
    {
      char suffix[50];
      Tlist sol_box_list;   // List of solution boxes 
      graph G;              // Graph of boxes, made out of sol_box_list
      llist walk_list;       // List of walks, altogether integrating a traversal of G
      llist curr_walk;       // Current walk in the previous list
      Tlist* walk_box_list; // List of boxes of a walk
      int traversal_type=0;
      int walk_number;
      int topology;
      double tolerance;
      FILE *fd;
      int nisol;
      graph_vertex curr_v;
      Tbox* curr_box;
      int stepsize;
      Tfilename fsols,fout;
      

      if (argc<3)
	tolerance = INTERSECT_TOL; //default tolerance
      else
	{
	  tolerance = atof(arg[2]);
	  // Tolerance can not be negative
	  if (tolerance < 0)
	    tolerance = INTERSECT_TOL; 
	}
      
      if (argc<4)
	topology = RN_TOPOLOGY; //default topology
      else
	{
	  // Get topology
	  switch(arg[3][0])
	    {
	    case 'r':
	      topology = RN_TOPOLOGY; 
	      printf("Using Rn topology\n");
	      break;
	    case 't':
	      topology = TORUS_TOPOLOGY; 
	      printf("Using torus topology\n");
	      break;
	    }
	}

      if (argc<5)
	traversal_type = TRAVERSE_DEPTH_FIRST; // default traverse mode
      else
	{
	  // Get traversal type
	  switch(arg[4][0])
	    {
	    case 'd':
	      traversal_type = TRAVERSE_DEPTH_FIRST; 
	      printf("Walks in depth-first mode\n");
	      break;
	    case 'c':
	      traversal_type = TRAVERSE_CYCLES; 
	      printf("Walks in cycles mode\n");
	      break;
	    case 'u':
	      traversal_type = TRAVERSE_WITHOUT_ORDER; 
	      printf("Walks in unordered mode\n");
	      break;
	    default:
	      Error("Unknown traversal mode\n");
	      break;
	    }
	}

      if (argc<6)
	stepsize=1;
      else
	{
	  // Get stepsize
	  stepsize = (unsigned int)(atoi(arg[5]));
	}

      // Read the list of solution boxes (TRUE avoids reading duplicated variables)
      CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsols);
      ReadListOfBoxes(GetFileFullName(&fsols),&sol_box_list);
      if(ListSize(&sol_box_list)==0)
	Error("Couldn't open solutions file\n");

      // Generate graph of boxes
      G = GraphOfBoxes(&sol_box_list,tolerance,topology);

      // Traverse the graph, generating a list of walks
      walk_list = TraverseGraphOfBoxes(G,traversal_type);

      // Generate one *.sol file for each walk, excluding one-box walks
      walk_number=1;
      for(curr_walk=walk_list; curr_walk!=NULL; curr_walk=NEXT(curr_walk)) 
	{
	  // Get list of boxes in current walk
	  walk_box_list = (Tlist*)DATA(curr_walk);

	  if(ListSize(walk_box_list) > 1)
	    {
	      // Open output file
	      sprintf(suffix,"_%d",walk_number);
	      CreateFileName(NULL,arg[1],suffix,SOL_EXT,&fout);
	      printf("Generating %s ...",GetFileFullName(&fout));
	      fd = fopen(GetFileFullName(&fout),"w");
	      if(fd==NULL) 
		Error("Couldn't open output file\n");

	      // Print the walk
	      PrintWalk(fd,curr_walk,stepsize);
	      fclose(fd);
	      printf("done.\n");
	      DeleteFileName(&fout);

	      walk_number++;
	    }
	}

      // Generate an extra *.sol with all isolated boxes
      nisol = 0;   
      CreateFileName(NULL,arg[1],"_isol",SOL_EXT,&fout);
      fd = fopen(GetFileFullName(&fout),"w");
      if(fd==NULL) 
	Error("Couldn't open file\n");
      printf("Generating %s ...",GetFileFullName(&fout));
      for(curr_v=G; curr_v!=NULL; curr_v = NEXT(curr_v))
	{
	  if(degree(curr_v)==0)
	    {
	      curr_box = (Tbox*)SPECIFIC_VERTEX_DATA(curr_v);
	      PrintBox(fd,curr_box);
	      nisol ++;
	    }
	}      
      fclose(fd);
      printf("done.\n");
      printf("%d isolated boxes.\n",nisol);

      DeleteFileName(&fout);
      DeleteFileName(&fsols);
    }

  return(EXIT_SUCCESS);
}

