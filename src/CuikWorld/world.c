#include "world.h"
#include "defines.h"
#include "error.h"
#include "varnames.h"
#include "random.h"
#include "list.h"
#include "shtransform.h"
#include "basic_algebra.h"

#include <math.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#ifdef _OPENMP
  #include <omp.h>
#endif

/** \file world.c
    \brief Implementaton of the function operating on Tworld.
    
    Implementaton of the function operating on Tworld.

    \sa Tworld, world.h
*/


/** 
   \brief Constructor.

   Defines an empty kinematic chain.

   \param b The kinematic chain to initialize.
*/
void CreateBranch(Tbranch *b);

/** 
   \brief Copy constructor.

   Defines a kinematic chain from another chain.

   \param b_dst The kinematic chain to initialize.
   \param b_src The kinematic chain from where to copy the data.
*/
void CopyBranch(Tbranch *b_dst,Tbranch *b_src);

/** 
   \brief Adds a step to a kinematic chain.

   Adds a step to a kinematic chain.

   \param s The sign of the step (1 if the given joint has to be used as given
            or -1 if it has to be used \e reversed).
   \param joint The joint to use to extend the kinematic branch.
   \param b The kinematic chain from where to copy the data.
*/
void AddStepToBranch(double s,Tjoint *joint,Tbranch *b);

/** 
   \brief Gets the number of steps in a kinematic chain.
   
   Gets the number of steps in a kinematic chain.
   
   \param b The kinematic branch to query.
   
   \return The number of steps in a kinematic chain.
*/
unsigned int nStepsBranch(Tbranch *b);

/** 
   \brief Retrives a particular step form a kinematic chain.
   
   Retrives a particular step form a kinematic chain.

   If there is no step with the given number in the kinematic chain,
   this funtion triggers an error.

   \param i The number of step to get.
   \param s Output with the sign of the requested step.
   \param joint Output with the joint used in the requested step.
   \param b The kinematic branch to query.
*/
void GetBranchStep(unsigned int i,double *s,Tjoint **joint,Tbranch *b);

/** 
   \brief Returns the identifier of the link where the kinematic chain starts.

   Returns the identifier of the link where the kinematic chain starts.

   \param b The kinematic branch to query.

   \return The identifier of the link where the kinematic chain starts.
*/
unsigned int GetBranchOrigin(Tbranch *b);

/** 
   \brief Returns the identifier of the link where the kinematic chain ends.

   Returns the identifier of the link where the kinematic chain ends.

   \param b The kinematic branch to query.

   \return The identifier of the link where the kinematic chain ends.
*/
unsigned int GetBranchDestination(Tbranch *b);


/** 
   \brief Merge two kinematic branches.

   We get two branches, \e b1,\e b2, representing two paths from, typically,
   the groundLink to the same link. 
   The output, \e b, will be the closed branch resulting from
   eliminating from \e b1 and \e b2 the initial common path
   from the groudnLink to the point where the paths diverge.
   
   \param b1 The first kinematic branch to merge.
   \param b2 The second kinematic branch to merge.
   \param b The resulting kinematic branch.
*/
void MergeBranches(Tbranch *b1,Tbranch *b2,Tbranch *b);

/** 
   \brief Defines the transform taking to the end of the branch.

   Defines te transfrom taking from the origin to the destination of the
   branch by accumulating the transforms for the joints involved in the
   branch.

   \param tj The set of transforms for each individual joint.
   \param t The output transform.
   \param b The branch.
*/
void GetTransformFromBranch(THTransform *tj,THTransform *t,Tbranch *b);

/** 
   \brief Destructor.

   Deletes the information stored in a kinematic branch and frees the allocated memory.

   \param b The branch to delete.
*/
void DeleteBranch(Tbranch *b);

/*********************************************************************/

void CreateBranch(Tbranch *b)
{
  InitVector(sizeof(void *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_JOINTS,&(b->steps)); 
}

void CopyBranch(Tbranch *b_dst,Tbranch *b_src)
{
  unsigned int i,n;
  double s;
  Tjoint *jo;

  CreateBranch(b_dst);
  n=nStepsBranch(b_src);
  for(i=0;i<n;i++)
    {
      GetBranchStep(i,&s,&jo,b_src);
      AddStepToBranch(s,jo,b_dst);
    }
}

void AddStepToBranch(double s,Tjoint *joint,Tbranch *b)
{
  TBranchStep *st;

  NEW(st,1,TBranchStep);

  st->joint=joint;
  st->sign=s;

  NewVectorElement(&st,&(b->steps));
}

unsigned int nStepsBranch(Tbranch *b)
{
  return(VectorSize(&(b->steps)));
}

void GetBranchStep(unsigned int i,double *s,Tjoint **joint,Tbranch *b)
{
  TBranchStep **st;

  st=(TBranchStep **)GetVectorElement(i,&(b->steps));
  if (st==NULL)
      Error("Wrong index in GetBranchStep");
  else
    {
     *s=(*st)->sign;
     *joint=(*st)->joint;
    }
}

unsigned int GetBranchOrigin(Tbranch *b)
{
  Tjoint *jo;
  double s;
  unsigned int k;

  GetBranchStep(0,&s,&jo,b);
  if (s>0) 
    k=JointFromID(jo);
  else
    k=JointToID(jo);

  return(k);
}

unsigned int GetBranchDestination(Tbranch *b)
{
  Tjoint *jo;
  double s;
  unsigned int k;

  GetBranchStep(nStepsBranch(b)-1,&s,&jo,b);
  if (s>0) 
    k=JointToID(jo);
  else
    k=JointFromID(jo);

  return(k);
}

void MergeBranches(Tbranch *b1,Tbranch *b2,Tbranch *b)
{
  /* We get two branches (b1,b2) representing two paths from
     the groundLink to the same link. 
     The output 'b' will be the closed branch resulting from
     eliminating from 'b1' and 'b2' the initial common path
     from the groudnLink to where the paths differ */

  signed int k,n1,n2,i,nm;
  Tjoint *jo1,*jo2;
  boolean equal;
  double s;

  n1=(signed int)nStepsBranch(b1);
  n2=(signed int)nStepsBranch(b2);
  nm=(n1<n2?n1:n2);
  k=0;
  equal=((n1>0)&&(n2>0));
  while ((k<nm)&&(equal))
    {
      GetBranchStep((unsigned int)k,&s,&jo1,b1);
      GetBranchStep((unsigned int)k,&s,&jo2,b2);
      if (jo1==jo2)
	k++;
      else
	equal=FALSE;
    }
  
  CreateBranch(b);

  for(i=k;i<n1;i++)
    {    
      GetBranchStep(i,&s,&jo1,b1);
      AddStepToBranch(s,jo1,b);
    }

  for(i=n2-1;i>=k;i--)
    {    
      GetBranchStep(i,&s,&jo2,b2);
      AddStepToBranch(-s,jo2,b);
    }
}

void GetTransformFromBranch(THTransform *tj,THTransform *t,Tbranch *b)
{
  unsigned int i,n;
  TBranchStep *st;
  THTransform ti;

  HTransformIdentity(t);
  n=nStepsBranch(b);
  for(i=0;i<n;i++)
    {    
      st=*(TBranchStep **)GetVectorElement(i,&(b->steps));
      if (st->sign>0)
	HTransformProduct(t,&(tj[GetJointID(st->joint)]),t);
      else
	{
	  HTransformInverse(&(tj[GetJointID(st->joint)]),&ti);
	  HTransformProduct(t,&ti,t);
	}
    }
}

void DeleteBranch(Tbranch *b)
{ 
  unsigned int i,n;
  TBranchStep *st;

  n=nStepsBranch(b);
  for(i=0;i<n;i++)
    {    
      st=*(TBranchStep **)GetVectorElement(i,&(b->steps));
      free(st);
    }
  DeleteVector(&(b->steps));
}


/*********************************************************************/

/** 
   \brief Determines kinematic branch from a link to all other links.

   Considering the mechanisms as a graph where the vertices are the
   links and the edges are defined by the joints, this function 
   determines the shortest from link \e f to all the other links,
   if possible (some links might be disconnected form link \e f).
   
   \param from The identifier of the initial link for the branch to generate.
   \param links Output. The list of links as they are visited during the
                generation of the branches. The space for this array
		of size 'nl' must be allocated externally.
   \param predLink Output. Predecesor link. The space for this array
		   of size 'nl' must be allocated externally.
   \param jointTo Ouput. The joint necessary to reach each link (i.e., joint
                  taking from the predecesor link to the current link, link[i]).
                  The space for this array of size 'nl' must be allocated 
		  externally.
   \param jointS Orientation of the joint: -1 if the joint has to be reversed
                 to reach the current link from the predecesor link, +1 otherwise.
   \param isLeaf Output. TRUE for the links that are at the extreme of
                 the tree (no other link is reached from them). 
		 The space for this array of size 'nl' must be 
		 allocated externally.
   \param b The output branches. The space for this array
	    of size 'nl' must be allocated externally.
   \param w The world to query.

   \return The number of visited links (valid elements in 'links'). 
           Must be (w->nl-w->ncl) if we managed to visit all 
	   links but the connection ones (i.e., if the graph is 
	   fully connected).
*/
unsigned int Branches2Links(unsigned int from,
			    unsigned int *links,unsigned int *predLink,unsigned int *jointTo,signed int *jointS,
			    boolean *isLeaf,Tbranch *b,Tworld *w);

/** 
   \brief Builds a kinematic tree departing from the ground link.

   
   Builds a kinematic tree departing from the ground link. From the
   kinematic tree we extract two types of branches
   - Closed loops: Branches created when, at a given point, links appear 
     from leaves of the tree to internal three nodes. Closed branches are
     then build using \ref MergeBranches. 
   - Open branches: Branches that connect the ground link to links with open
     branches, i.e., without loops. These are the kind of loops that appear
     in tree like mechanisms.
   .
   A mechanism can have the two types of branches.

   Before building the kinematic tree, we ensure the mechanism to be fully 
   connected: Parts of the mechanism disconnected from the ground link are
   connected to it using free-joints.

   \param bOut Vector with the open and closed branches extracted from the
               kinematic tree.
   \param w The world to query.
*/
void GenerateKinTree(Tvector *bOut,Tworld *w);

/** 
   \brief Generates a matrix equation from a branch.

   Generates a matrix equatoin from a branch by accumulating
   the (symbolic) transforms for the joints in the branch.

   \param p The set of parameters.
   \param b The branch.
   \param meq The resulting matrix equation.
   \param w The world.
*/
void GenerateMEquationFromBranch(Tparameters *p,Tbranch *b,TMequation *meq,Tworld *w);

/** 
   \brief Generate equations from a branch.

   Generate equations from a branch considering the branch merely as a sum of vectors.

   The difference with \ref GenerateEquationsFromBranch is that for open branches
   we do not add to the resulting equations the variables representing the position
   of the link reached by this open branch. Thus, the output equations here only
   involve system equations.

   Moreove, the resulting equations are not added to a cuiksystem but returned
   to the caller.
   
   \param p The set of parameters.
   \param eq_type Type for the equations to generete (SYSTEM_EQS, COORD_EQS).
   \param eqs Space for 3 equations where to store the result.
   \param b The branch from where to generate the equations.
   \param w The world on which we have to operate.
*/
void GenerateTransEquationsFromBranch(Tparameters *p,unsigned int eq_type,
				      Tequation *eqs,Tbranch *b,Tworld *w);

/** 
   \brief Generate equations from a branch.

   Generate equations from a branch. 

   If the branch is closed, we generate 
   3 loop equations (X, Y and Z) that are added to the given cuiksystem.

   If the branch is open we generate equations that give the 3D position
   in the global frame of reference of the origin of the frame of reference 
   of the last link in the branch.
   
   This function uses \ref GenerateTransEquationsFromBranch and then completes
   equations for open branches and add the results to the given cuiksystem.

   \param p The set of parameters used when generating the equations 
            (DUMMIFY_LEVEL,...).
   \param eq_type Type for the equations to generete (SYSTEM_EQS, COORD_EQS).
   \param cs The cuiksystem where to add the equations.
   \param b The branch from where to generate the equations.
   \param w The world on which we have to operate.
   
   \return \ref TRUE if the branch is open and new reference variables are
           added to the CuikSystem.
*/
boolean GenerateEquationsFromBranch(Tparameters *p,unsigned int eq_type,
				    TCuikSystem *cs,Tbranch *b,Tworld *w);


/** 
   \brief Removes the collision information stored in a Tworld.
   
   Removes the collision information stored in a Tworld: the 
   Tworld::checkCollisionsLL and Tworld::checkCollisionsLO arrays.

   \param w The world whose collision information we want to delete.
*/
void DeleteWorldCollisionInfo(Tworld *w);

/** 
   \brief Collects information about the DOF of the mechanism.

   Collects information about the DOF of the mechanism from the
   joints.
   
   \param w The world whose DOF we want to determine.
*/
void WorldInitDOFInfo(Tworld *w);

/** 
   \brief Deletes the information collected at \ref WorldInitDOFInfo.

   Deletes the information collected at \ref WorldInitDOFInfo.

   \param w The world with the information to release.
*/
void WorldDeleteDOFInfo(Tworld *w);

/** 
   \brief Define transforms for the links from the DOF.

   Computes a transform giving the pose for each link from
   values for the different degrees of freedom of the mechanisms.

   \param dof The values for the degrees of freedom.
   \param tl The output transforms. The space is allocated inside
             this function.
   \param def Configuration parameter for each link.
   \param w the world.
*/
void GetLinkTransformsFromDOF(double *dof,THTransform **tl,TLinkConf **def,Tworld *w);

/** 
   \brief Define transforms for the links from the a solution point.

   Computes a transform giving the pose for each link from
   values for a solution point. 
   Note that if solutions are given as degrees of freedom this
   is equivalent to \ref GetLinkTransformsFromDOF.

   The difference with respect to \ref GetLinkTransformsFromSolutionPoint
   is that here the point includes values for all variables and in
   \ref GetLinkTransformsFromSolutionPoint only the system variables
   are given.

   \param p The parameters.
   \param sol The solution point (including all variables, system, 
              dummies...)
   \param tl The output transforms. The space is allocated inside
             this function.
   \param def Array with the configuration parameters for each link.
   \param w the world.
*/
void GetLinkTransformsFromSolution(Tparameters *p,double *sol,
				   THTransform **tl,TLinkConf **def,Tworld *w);

/** 
   \brief Identifies links articulated with only two revolute joints.

   Identifies links articulated with only two co-punctual revolute joints. 
   For those links it is possible to re-define the reference frame so that 
   simpler equations will be obtained.

   \param nl The identifier of the link to be checked.
   \param p Space to store four points defining the rotation axis for the 
            revolute axes.<br>
            The indexing is p[i][j][k] where \e i is the number of axis (0,1)
	    \e j the number of point in the axis (0,1) and \e k the component
	    (0,1,2 for x, y, z).
   \param w The world with the information of links and joints.
   
   \return TRUE if the link with the given identifier is a revolute, binary
           link.

   \sa ChangeLinkReferenceFrame
*/
boolean IsRevoluteBinaryLink(unsigned int nl,double ***p,Tworld *w);

/** 
   \brief Initializes the kinematic sub-problem of a Tworld structure.

   Initializes the kinematic sub-problem of a Tworld structure.

   \param p A set of parameters used when generating the equations 
            (DUMMIFY_LEVEL,...).
   \param w The world on which we have to operate.
*/
void InitWorldKinCS(Tparameters *p,Tworld *w);

/** 
   \brief Initializes the cuiksystems in a Tworld structure.

   Initializes the cuiksystems in a Tworld structure.
   The Tworld::kinCS is initialized as an empty cuiksystem.
   Equations are added to this system using \ref InitWorldKinCS.

   \param w The world structure to initialzie.
   
*/
void InitWorldCS(Tworld *w);

/** 
  \brief Deletes the world cuik system.

  Deletes the equations stored in the world.

  \param w The world with the cuiksystem.
*/
void DeleteWorldCS(Tworld *w);

/** 
   \brief Deletes the collision information stored in the world.

   Deletes the collision information stored in the world, if any.

   \param w The world structure with the collision information to release.
*/
void DeleteWorldCD(Tworld *w);

/************************************************************************/
unsigned int Branches2Links(unsigned int from,
			    unsigned int *links,unsigned int *predLink,unsigned int *jointTo,signed int *jointS,
			    boolean *isLeaf,Tbranch *b,Tworld *w)
{
  boolean *visited; /* visited links */
  unsigned int c; /* current link in expansion (index in 'links' array) */
  unsigned int i,j,t,f,nte,o,d;
  Tjoint *jo;
  double s;
  boolean found;

  NEW(visited,w->nl,boolean);
  for(i=0;i<w->nl;i++)
    {
      visited[i]=FALSE;
      isLeaf[i]=FALSE;
      jointTo[i]=NO_UINT;
      jointS[i]=0;
      predLink[i]=NO_UINT;
      links[i]=NO_UINT;
    }

  c=0; /* current position in 'links' */
  links[c]=from; /* we start expanding form node 'from' */
  visited[from]=TRUE;
  nte=1; /* number of elements in 'links' */
  jointTo[from]=NO_UINT; /* node 'from' is the root (no joint lead to it). */
  jointS[from]=0;
  predLink[from]=NO_UINT;
  isLeaf[from]=TRUE; /* initially 'from' is a leaf link */

  /* Initialize the branch to the first link (the only visited so far) */
  CreateBranch(&(b[from])); 
    
  while(c<nte)
    {
      /* look all the joints that end/start at current links[c] */
      found=FALSE;
      for(j=0;((!found)&&(j<w->nj));j++)
	{
	  jo=GetMechanismJoint(j,&(w->m));
	  t=JointToID(jo);
	  f=JointFromID(jo);
	  /* It is probably a good idea to try to avoid "inverse" joints
	     as much as possible */
	  if ((t==links[c])||(f==links[c]))
	    {
	      if (t==links[c])
		{o=t;d=f;s=-1.0;}
	      else
		{o=f;d=t;s=+1.0;}
		 
	      if (!visited[d])
		{
		  //fprintf(stderr,"Visiting link %u from link %u via joint %u with sign %g\n",d,o,j,s);
		  /* Depth-first search produces longer equations */
		  /*found=TRUE;*/ /* comment this to get a Breadth-first search */

		  isLeaf[o]=FALSE; /* Now link 'o' has a child */
		  links[nte++]=d;  /* Add link 'd' to the list of nodes to expand */
		  visited[d]=TRUE; /* link 'd' is already reached */
		  jointTo[d]=j;
		  predLink[d]=o;
		  jointS[d]=SGN(s);
		  isLeaf[d]=TRUE; /* initially link 'd' is a leaf */
		  CopyBranch(&(b[d]),&(b[o]));
		  AddStepToBranch(s,jo,&(b[d]));
		}
	    }
	}
      c++;
    }
  
  /* Create an empty branch for the non-visited links (if any).
     Connection links are alwoys non-visited since they are not attached
     the the mechanism by any joint */
  for(i=0;i<w->nl;i++)
    {
      if (!visited[i])
	CreateBranch(&(b[i]));
    }

  free(visited);

  return(nte);
}

void GenerateKinTree(Tvector *bOut,Tworld *w)
{
  boolean *usedJoint;
  Tbranch *b,*b1;
  unsigned int i,n,j,lfID,ltID;
  Tjoint newJoint,*jo;
  Tlink *ground;

  /*First we ensure that the mechanism is fully connected*/
  ground=GetMechanismLink(0,&(w->m));
  
  NEW(w->branch2Link,w->nl,Tbranch);
  NEW(w->sortedLinks,w->nl,unsigned int);
  NEW(w->jointTo,w->nl,unsigned int);
  NEW(w->jointS,w->nl,signed int);
  NEW(w->predLink,w->nl,unsigned int);
  NEW(w->openLink,w->nl,boolean);
  NEW(w->closingJoint,w->nj,boolean);
  n=Branches2Links(0,w->sortedLinks,w->predLink,w->jointTo,w->jointS,w->openLink,w->branch2Link,w);
  if (n!=(w->nl-w->ncl))
    {
      /* we need to reach all non-connection links (link 0 is root!) */
      for(i=1;i<w->nl;i++)
	{
	  if ((nStepsBranch(&(w->branch2Link[i]))==0)&&
	      (GetLinkType(GetMechanismLink(i,&(w->m)))!=LINK_Connect))
	    {
	      NewFreeJoint(w->nj,
			   0,ground,
			   i,GetMechanismLink(i,&(w->m)),
			   INF,INF,INF,1.0,0.0,0.0,&newJoint);
	      j=AddJoint2Mechanism(&newJoint,&(w->m));
	      w->nj++;  
	      DeleteJoint(&newJoint);

	      /* define the tree info for this link */
	      AddStepToBranch(1.0,GetMechanismJoint(j,&(w->m)),&(w->branch2Link[i]));
	      w->sortedLinks[n++]=i;
	      w->jointTo[i]=j;
	      w->jointS[i]=+1;
	      w->predLink[i]=0; /* directly connected to root */
	      w->openLink[0]=FALSE; /* just in case :) */
	      w->openLink[i]=TRUE;
	    }
	}
    }

  NEW(usedJoint,w->nj,boolean);
  for(i=0;i<w->nj;i++)
    {
      usedJoint[i]=FALSE;
      w->closingJoint[i]=FALSE;
    }
  for(i=1;i<w->nl;i++) /* no joint takes to link 0! */
    {
      if (w->jointTo[i]!=NO_UINT)
	usedJoint[w->jointTo[i]]=TRUE;
    }

  /* Initialize the vector with the pointers to the loop (or not loop) equations. */
  InitVector(sizeof(void *),CopyVoidPtr,DeleteVoidPtr,w->nl,bOut);

  /* Here, the non-used joints form a basis of cycles */
  NEW(w->sortedClosures,w->nj-w->nl+1,unsigned int);
  w->nLoops=0;
  
  for(i=0;i<w->nj;i++)
    {
      if (!usedJoint[i])
	{
	  
	  if (w->nLoops==(w->nj-w->nl+1))
	    Error("Incongruent number of loops");
	  w->sortedClosures[w->nLoops]=i;
	  w->nLoops++;
	  
	  w->closingJoint[i]=TRUE;
	  
	  jo=GetMechanismJoint(i,&(w->m));
	  lfID=JointFromID(jo);
	  ltID=JointToID(jo);
	  
	  /* Add the non-used joint to one of the branches to close the loop */
	  NEW(b1,1,Tbranch);
	  CopyBranch(b1,&(w->branch2Link[lfID]));
	  AddStepToBranch(1,jo,b1);

	  NEW(b,1,Tbranch);
	  MergeBranches(b1,&(w->branch2Link[ltID]),b);
	  NewVectorElement(&b,bOut);

	  DeleteBranch(b1);
	  free(b1);

	  /* Just in case, the two links are not open any more */
	  w->openLink[lfID]=FALSE;
	  w->openLink[ltID]=FALSE;
	}
    }

  /* Open non-connection links define open branches */
  for(i=0;i<w->nl;i++)
    {
      if ((w->openLink[i])&&  /* this is already false for connection links but... */
	  (GetLinkType(GetMechanismLink(i,&(w->m)))!=LINK_Connect))
	{
	  NEW(b,1,Tbranch);
	  CopyBranch(b,&(w->branch2Link[i]));
	  NewVectorElement(&b,bOut);
	}
    }

  /* Release memory */
  free(usedJoint);
}

void GenerateMEquationFromBranch(Tparameters *p,Tbranch *b,TMequation *meq,Tworld *w)
{
  unsigned int i,n;
  double s;
  Tjoint *jo;
  Tlink *l;
  TTransSeq ts;

  /*  Id = Id */
  InitMEquation(meq);

  /* Now add the variable terms, if any */
  n=nStepsBranch(b);
  for(i=0;i<n;i++)
    {
      GetBranchStep(i,&s,&jo,b);

      /* Traverse the current link (only has effect in case of
	 deformable links) */
      l=JointFrom(jo);
      GetLinkTransSeq(p,&(w->kinCS),&ts,l);     
      AddTransSeq2MEquation(s,&ts,meq);
      DeleteTransSeq(&ts);
	
      GetJointTransSeq(p,&(w->kinCS),&ts,jo);      
      AddTransSeq2MEquation(s,&ts,meq);
      DeleteTransSeq(&ts);
    }
  
  SimplifyMEquation(meq);
  
  /* for open branches we are only interested in the translation */
  if ((n==0)||(GetBranchOrigin(b)!=GetBranchDestination(b)))
    MakeTranslationMEquation(meq);
}

void GenerateTransEquationsFromBranch(Tparameters *p,unsigned int eq_type,
				      Tequation *eq,Tbranch *b,Tworld *w)
{
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    Error("GenerateTransEquationsFromBranch should not be used in JOINT-based representations");
  else
    {
      /*A Loop is a closed branch: a path from one link to itself
	going through other links*/
      unsigned int n,i;
      double s;
      Tjoint *jo;
  
      for(i=0;i<3;i++)
	{
	  InitEquation(&(eq[i]));
	  SetEquationType(eq_type,&(eq[i]));
	  SetEquationCmp(EQU,&(eq[i]));
	}

      n=nStepsBranch(b);
      for(i=0;i<n;i++)
	{
	  /*Get current joint destination link (by treating the 
	    destitation we deal with all links since the first link 
	    is the ground link and does not require to be
	    processed)*/
	  GetBranchStep(i,&s,&jo,b);
      
	  GenerateJointEquationsInBranch(p,s,&(w->kinCS),eq,jo);
	}
    }
}

boolean GenerateEquationsFromBranch(Tparameters *p,unsigned int eq_type,
				    TCuikSystem *cs,Tbranch *b,Tworld *w)
{
  unsigned int origin,destination,i;
  boolean closedBranch;
  Tequation eq[3];
  Tmonomial f;
  char *vname,*l1name;
  Tlink *l1;
  Tvariable var;
  Tinterval rangeInf;
  unsigned int vID;
  unsigned int r;

  if (nStepsBranch(b)==0)
    {
      /* An empty branch is a branch from ground link to ground link and it
         ony appears when trying to give coordinates to the ground link ??*/
      origin=0;
      destination=0;
      closedBranch=FALSE;
    }
  else
    {
      origin=GetBranchOrigin(b);
      destination=GetBranchDestination(b);
      closedBranch=(origin==destination);
    }

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    {
      if (closedBranch)
	{
	  TMequation meq;

	  GenerateMEquationFromBranch(p,b,&meq,w);
	  AddMatrixEquation2CS(p,&meq,cs);
	  DeleteMEquation(&meq);
	}
    }
  else
    {
      GenerateTransEquationsFromBranch(p,eq_type,eq,b,w);

      InitMonomial(&f);
      NewInterval(-w->maxCoord,w->maxCoord,&rangeInf);
      for(i=0;i<3;i++)
	{
	  if (!closedBranch)
	    {
	      l1=GetMechanismLink(destination,&(w->m));
	      l1name=GetLinkName(l1); 

	      NEW(vname,strlen(l1name)+100,char);
	      LINK_TRANS(vname,l1name,i); 

	      NewVariable(SYSTEM_VAR,vname,&var);
	      free(vname);
	      SetVariableInterval(&rangeInf,&var);

	      vID=AddVariable2CS(&var,cs);

	      DeleteVariable(&var);

	      AddCt2Monomial(-1.0,&f);
	      AddVariable2Monomial(NFUN,vID,1,&f);
	      AddMonomial(&f,&(eq[i]));
	      ResetMonomial(&f);

	      SetEquationType(SYSTEM_EQ,&(eq[i]));
	    }
	  
	  AddEquation2CS(p,&(eq[i]),cs);
	  DeleteEquation(&(eq[i]));
	}
      DeleteInterval(&rangeInf);
      DeleteMonomial(&f);

    }
  return(!closedBranch);
}


boolean IsRevoluteBinaryLink(unsigned int nl,double ***p,Tworld *w)
{
  unsigned int i,j,nr,f,t,nnr;
  Tjoint *jo;

  i=0;
  nr=0; /* number of revolute joints in link */
  nnr=0;/* numnrt of non-revolute joints in link */
  while ((i<w->nj)&&(nnr==0)&&(nr<3))
    {
      jo=GetMechanismJoint(i,&(w->m));
      f=JointFromID(jo);
      t=JointToID(jo);

      if ((f==nl)||(t==nl))
	{
	  if (GetJointType(jo)==REV_JOINT)
	    {
	      if (nr<2)
		{
		  for(j=0;j<2;j++)
		    GetJointPoint(((f==nl)?0:1),j,p[nr][j],jo);
		}
	      nr++; /*a new revolute joint on the link*/
	    }
	  else
	    nnr++; /*a new non-revolute joint on the link*/
	}

      i++;
    }
  /*
    Uncomment the last expression to force the axes to be co-puntual
   */
  return((nnr==0)&&(nr==2)); //&&(Distance(3,p[0][0],p[1][0])<ZERO));
}

void InitWorldKinCS(Tparameters *p,Tworld *w)
{
  unsigned int i,j;
  Tvector branches;
  unsigned int nBranches;
  Tbranch *b;
  Tjoint *jo;
  double ***points;
  unsigned int r;

  if (w->nl==0)
    Error("Empty mechanism");

  if (w->nl==1)
    Error("A world with just one ground link makes no sense");
  else
    {
      r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
	
      /*In some cases it is advisable to re-define the reference frame for the
	links to get simpler equations*/
      if ((r!=REP_JOINTS)&&(AllRevolute(&(w->m))))
	{
	  NEW(points,2,double **);
	  for(i=0;i<2;i++)
	    {
	      NEW(points[i],2,double *);
	      for(j=0;j<2;j++)
		NEW(points[i][j],3,double);
	    }

	  for(i=0;i<w->nl;i++)
	    {
	      if (IsRevoluteBinaryLink(i,points,w))
		ChangeLinkReferenceFrame(r,points[0],points[1],
					 GetMechanismLink(i,&(w->m)));
	    }

	  for(i=0;i<2;i++)
	    {
	      for(j=0;j<2;j++)
		free(points[i][j]);
	      free(points[i]);
	    }
	  free(points);
	}

      /* All links appear in the kinCS: we add the variables and equations 
	 defining the rotation matrix for each link. */
      for(i=0;i<w->nl;i++)
	GenerateLinkRot(p,i,&(w->kinCS),GetMechanismLink(i,&(w->m)));

      /* Compute the paths from ground link to all other links (this ensures 
	 that links are fully connected adding as many free joints as 
	 necessary. */
      GenerateKinTree(&branches,w);
      nBranches=VectorSize(&branches);

      /* All joints appear in the kinCS: we add variables and equations 
	 for the joint and joint limits. IMPORTANT: the GenerateKinTree
	 function can generate new joints !!! */
      for(i=0;i<w->nj;i++)
	{
	  jo=GetMechanismJoint(i,&(w->m));
	  GenerateJointEquations(p,w->maxCoord,&(w->kinCS),jo);
	  GenerateJointRangeEquations(p,&(w->kinCS),jo);
	}
      
      /* Generate the equations for the loops (and branches to terminal links) 
	 involved in the mechanism */
      for(i=0;i<nBranches;i++)
	{
	  b=*(Tbranch **)GetVectorElement(i,&branches);
	  GenerateEquationsFromBranch(p,SYSTEM_EQ,&(w->kinCS),b,w);
	  DeleteBranch(b);
	  free(b);
	}
  
      DeleteVector(&branches);
    }
}

void InitWorldCS(Tworld *w)
{
  InitCuikSystem(&(w->kinCS));
}

void DeleteWorldCS(Tworld *w)
{
  unsigned int i;
  
  for(i=0;i<w->nl;i++)
    DeleteBranch(&(w->branch2Link[i]));
  free(w->branch2Link);

  DeleteEquations(&(w->refEqs));
  DeleteJacobian(&(w->refEqsJ));

  free(w->closingJoint);
  free(w->sortedClosures);
  free(w->openLink);
  free(w->sortedLinks);
  free(w->predLink);
  free(w->jointTo);
  free(w->jointS);
  
  DeleteCuikSystem(&(w->kinCS));

  free(w->systemVars);

  WorldDeleteDOFInfo(w);
}


/*********************************************************************/
/*********************************************************************/


void InitWorldCD(Tparameters *pr,unsigned int mt,Tworld *w)
{ 
  if (w->stage!=WORLD_DEFINED)
    Error("Complete the workd definition before using the InitWorldCD function");

  if (w->wcd!=NULL)
    {
      DeleteCD(w->wcd);
      free(w->wcd);
      w->wcd=NULL;
    }

  /* The collision detection engine is only initialized if there is any
     collision to detect. */
  if (AnyCollision(w))
    {
      unsigned int e,i;

      e=(unsigned int)(GetParameter(CT_CD_ENGINE,pr));

      if (mt==0)
	Error("Wrong maximum number of threads in InitWorldCD");

      w->nwcd=mt;
      NEW(w->wcd,w->nwcd,TworldCD);
      
      /* when mt>0 is because OpenMP is available and will be used -> initialize in parallel */
      #pragma omp parallel for private(i) if (mt>1)
      for(i=0;i<mt;i++)
	InitCD(e,(mt>1),&(w->m),&(w->e),w->checkCollisionsLL,w->checkCollisionsLO,&(w->wcd[i]));
    }
}

boolean WorldCanCollide(Tworld *w)
{
  return(w->wcd!=NULL);
}

boolean WorldContinuousCD(Tworld *w)
{
  if (w->wcd==NULL)
    return(FALSE);
  else
    /* we query the first collision detecion structure, even if we have many. */
    return(GetCDEngine(w->wcd)==C_FCL);
}

boolean MoveAndCheckCDFromTransforms(boolean all,unsigned int tID,
				     THTransform *tl,TLinkConf *def,
				     THTransform *tlPrev,TLinkConf *defPrev,
				     Tworld *w)
{
  if (w->wcd!=NULL)
    {
      boolean col;
      
      /* If sequential force it, even if tID is different from 0. */
      if (w->nwcd==0)
	col=CheckCollision(all,tl,def,tlPrev,defPrev,&(w->wcd[0]));
      else
	col=CheckCollision(all,tl,def,tlPrev,defPrev,&(w->wcd[tID]));
      
      if ((all)&&((w->nwcd==0)||(tID==0)))
	PrintCollisionInfo(tl,&(w->m),&(w->e),w->wcd);
      
      return(col);
    }
  else
    return(FALSE); /* no collison to detect */
}


boolean MoveAndCheckCD(Tparameters *p,boolean all,unsigned int tID,
		       double *sol,double *solPrev,Tworld *w)
{
  if (w->wcd!=NULL)
    {
      THTransform *tl,*tlPrev=NULL;
      boolean c;
      TLinkConf *def,*defPrev=NULL;

      GetLinkTransformsFromSolution(p,sol,&tl,&def,w);
      if ((solPrev!=NULL)&&(GetCDEngine(w->wcd)==C_FCL)) 
	GetLinkTransformsFromSolution(p,sol,&tlPrev,&defPrev,w);

      c=MoveAndCheckCDFromTransforms(all,tID,tl,def,tlPrev,defPrev,w);
      
      DeleteLinkTransforms(tl,def,w);
      if (tlPrev!=NULL)
	DeleteLinkTransforms(tlPrev,defPrev,w);
      
      return(c);
    }
  else
    return(FALSE); /* no collison to detect */
}

void DeleteWorldCD(Tworld *w)
{
  if (w->wcd!=NULL)
    {
      unsigned int i;
      
      for(i=0;i<w->nwcd;i++)
	DeleteCD(&(w->wcd[i]));

      free(w->wcd);
      w->wcd=NULL;
    }
}


/*********************************************************************/
/*********************************************************************/

void GetLinkTransformsFromDOF(double *dof,THTransform **tl,TLinkConf **def,Tworld *w)
{
  unsigned int i,lID,parent,jID;
  THTransform *tj,t;
  Tjoint *j;
  Tlink *l;

  /* get the configuration parameters for each link. */
  NEW(*def,w->nl,TLinkConf);
  for(i=0;i<w->nl;i++)
    {
      l=GetMechanismLink(i,&(w->m));
      GetLinkConfFromDOF(&(dof[w->link2dof[i]]),&((*def)[i]),l);
    }
  
  NEW(tj,w->nj,THTransform);
  for(i=0;i<w->nj;i++)
    {
      j=GetMechanismJoint(i,&(w->m));	
      GetJointTransform(&(dof[w->joint2dof[i]]),&(tj[i]),j);

      /* if necessary apply transforms depending on the
         previous link configuration (i.e., traverse a
         deformable link). */
      l=JointFrom(j);
      lID=JointFromID(j);
      if (IsVariableLengthLink(l))
	{
	  GetLinkTransform(&(dof[w->link2dof[lID]]),&t,l);
	  HTransformProduct(&t,&(tj[i]),&(tj[i]));
	  HTransformDelete(&t);
	}
    }
  
  NEW(*tl,w->nl,THTransform);
#if (0)
  /* The old, slower way to obtain the transform for each link.  */
  for(i=0;i<w->nj;i++)
    GetTransformFromBranch(tj,&((*tl)[i]),&(w->branch2Link[i]));
#else
  /* The new way takes advantage of the kinematic tree structure
     to reduce the number of matrix products (does not repeat
     computations). */
  HTransformIdentity(&((*tl)[0]));
  for(i=1;i<w->nl;i++)
    {
      lID=w->sortedLinks[i]; /* next link whose pose can be easily computed */
      
      if (lID!=NO_UINT) /* skip links not used in the kinematic tree (e.g., connection links) */
	{
	  jID=w->jointTo[lID]; /* joint to use to compute such pose */
	  j=GetMechanismJoint(jID,&(w->m));
	  l=GetMechanismLink(lID,&(w->m)); /* REMOVE ME for debug only */
	  if (lID==JointToID(j))
	    {
	      parent=JointFromID(j); 
	      HTransformProduct(&((*tl)[parent]),&(tj[jID]),&((*tl)[lID]));
	    }
	  else
	    {
	      parent=JointToID(j); 
	      HTransformInverse(&(tj[jID]),&t);
	      HTransformProduct(&((*tl)[parent]),&t,&((*tl)[lID]));
	      HTransformDelete(&t);
	    }
	}
    }
#endif

  /* Now compute the pose for the connection links */
  for(i=0;i<w->nl;i++)
    {
      l=GetMechanismLink(i,&(w->m));
      if (GetLinkType(l)==LINK_Connect)
	GetTransform2ConnectionLink(*tl,&((*tl)[i]),&((*def)[i]),l);
    }

  /* Release memory */
  for(i=0;i<w->nj;i++)
    HTransformDelete(&(tj[i]));
  free(tj);
}

void GetLinkTransformsFromSolutionPoint(Tparameters *p,boolean simp,double *sol,
					THTransform **tl,TLinkConf **def,Tworld *w)
{
  unsigned int r;

  if (w->stage!=WORLD_DEFINED)
   Error("The equations and variables are not yet defined");

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (r==REP_JOINTS)
    {
      if (simp)
	{
	  double *fullDOF;

	  /* 'sol' is a simplified point in JOINTS */
	  RegenerateOriginalPoint(p,sol,&fullDOF,&(w->kinCS));
	  GetLinkTransformsFromDOF(fullDOF,tl,def,w);

	  free(fullDOF);
	}
      else
	/* 'sol' already includes all the JOINTS */
	GetLinkTransformsFromDOF(sol,tl,def,w);	
    }
  else
    {
      double *v;
      
      if (simp)
	{
	  /* unsimplify */
	  RegenerateOriginalPoint(p,sol,&v,&(w->kinCS));
	  /* fill the gaps (dummy/force) vars not appearing in simplification */
	  RegenerateMechanismSolution(p,&(w->kinCS),v,&(w->m));
	}
      else
	/* get dummy/force vars (i.e. not system vars) */
	RegenerateWorldSolutionPoint(p,sol,&v,w);

      GetLinkTransformsFromSolution(p,v,tl,def,w);

      free(v);
    }
}

unsigned int GetSolutionPointFromLinkTransforms(Tparameters *p,THTransform *tl,TLinkConf *def,
						double **sol,Tworld *w)
{
  unsigned int rep,n;
  
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  n=GetCSNumSystemVariables(&(w->kinCS));
  NEW(*sol,n,double);

  if (rep==REP_JOINTS) 
    GetMechanismDOFsFromTransforms(p,tl,def,*sol,&(w->m));
  else
    {
      unsigned int i,nv,k;
      double *dof,*sample;

      /* Get the dof from the transforms */
      NEW(dof,w->ndof,double);
      GetMechanismDOFsFromTransforms(p,tl,def,dof,&(w->m));
      
      /* Get the sample from the dof */
      nv=WorldDOF2Sol(p,dof,&sample,NULL,w);

      /* and keep only the system variables */
      k=0;
      for(i=0;i<nv;i++)
	{
	  if (w->systemVars[i])
	    {
	      (*sol)[k]=sample[i];
	      k++;
	    }
	}

      /* Release used memory */
      free(sample);
      free(dof);
    }

  return(GetCSNumSystemVariables(&(w->kinCS)));
}


void GetLinkTransformsFromSolution(Tparameters *p,double *sol,
				   THTransform **tl,TLinkConf **def,Tworld *w)
{
  unsigned int rep;

  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (rep==REP_JOINTS)
    GetLinkTransformsFromDOF(sol,tl,def,w);
  else
    {  
      unsigned int i;
      Tlink *l;
      double *r;

      NEW(*tl,w->nl,THTransform);
      NEW(*def,w->nl,TLinkConf);

      NEW(r,3*w->nl,double);
      EvaluateEqualityEquations(FALSE,sol,r,&(w->refEqs));
      
      for(i=0;i<w->nl;i++)
	{
	  l=GetMechanismLink(i,&(w->m));
	  if (GetLinkType(l)!=LINK_Connect)
	    GetTransform2Link(p,&(w->kinCS),sol,IsGroundLink(i),
			      &(r[3*i]),&((*tl)[i]),&((*def)[i]),l);
	}
      free(r);
      
      /* Now compute the pose for the connection links */
      for(i=0;i<w->nl;i++)
	{
	  l=GetMechanismLink(i,&(w->m));
	  if (GetLinkType(l)==LINK_Connect)
	    GetTransform2ConnectionLink(*tl,&((*tl)[i]),&((*def)[i]),l);
	}
    }
}

void DeleteLinkTransforms(THTransform *tl,TLinkConf *def,Tworld *w)
{
  unsigned int i;

  for(i=0;i<w->nl;i++)
    {
      HTransformDelete(&(tl[i]));
      DeleteLinkConf(&(def[i]));
    }

  free(tl);
  free(def);
}



/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

void InitWorld(Tworld *w)
{
  InitEnvironment(&(w->e));
  InitMechanism(&(w->m));

  w->nl=0;
  w->ncl=0;
  w->nj=0;
  w->no=0;
  w->nb=0;
  w->np=0;
  w->nvars=0;
  w->nsvars=0;
  w->systemVars=NULL;
  w->checkCollisionsLL=NULL;
  w->checkCollisionsLO=NULL;
  
  w->endEffector=NO_UINT;

  w->branch2Link=NULL;

  w->stage=WORLD_IN_DEFINITION;

  w->wcd=NULL;

  w->ndof=0;
  w->da=0;
}

unsigned int AddLink2World(Tlink *l,boolean endEffector,Tworld *w)
{
  unsigned int j,k;

  if (w->stage!=WORLD_IN_DEFINITION)
    Error("Links can only be added during the world definition");

  if (GetWorldLinkID(GetLinkName(l),w)!=NO_UINT)
    Error("Duplicated link identifier");
  
  if (endEffector)
    w->endEffector=w->nl;

  w->nl++;
  if (GetLinkType(l)==LINK_Connect)
    w->ncl++;
  k=LinkNBodies(l);
  w->nb+=k;
  w->np+=k;

  /* define a new row and column in he LL table */

  /* expand the previous rows, if any */
  for(j=0;j<w->nl-1;j++)
    {
      MEM_EXPAND(w->checkCollisionsLL[j],w->nl,boolean); /* enlarge */
      w->checkCollisionsLL[j][w->nl-1]=FALSE;
    }
  
  /* create a new row */
  if (w->checkCollisionsLL==NULL)
    { NEW(w->checkCollisionsLL,w->nl,boolean*); } /* create */
  else
    { MEM_EXPAND(w->checkCollisionsLL,w->nl,boolean*); } /* enlarge */

  /* allocate and initialize the new row */
  NEW(w->checkCollisionsLL[w->nl-1],w->nl,boolean);
  for(j=0;j<w->nl;j++)
    w->checkCollisionsLL[w->nl-1][j]=FALSE;

  if (w->no>0)
    {
      /* define a new row in he LO table */
      if (w->checkCollisionsLO==NULL)
	{ NEW(w->checkCollisionsLO,w->nl,boolean*); } /* create */
      else
	{ MEM_EXPAND(w->checkCollisionsLO,w->nl,boolean*); } /* enlarge */
      NEW(w->checkCollisionsLO[w->nl-1],w->no,boolean);
      for(j=0;j<w->no;j++)
	w->checkCollisionsLO[w->nl-1][j]=FALSE;
    }

  return(AddLink2Mechanism(l,&(w->m)));
}

unsigned int AddJoint2World(Tjoint *j,Tworld *w)
{
  if (w->stage!=WORLD_IN_DEFINITION)
    Error("Joints can only be added during the world definition");

  w->nj++;

  if (ActuatedJoint(j))
    w->da+=GetJointDOF(j);
  
  return(AddJoint2Mechanism(j,&(w->m)));
}

void AddLeg2World(char *name,
		  boolean planar,
		  unsigned int type,
		  unsigned int lID1,unsigned int lID2,
		  double **points,
		  Tinterval *length,double stiffness,
		  Tinterval *rest,Tinterval *force,
		  double radius,unsigned int gr,
		  Tcolor *color,unsigned int bs,
		  double mass,double **iMatrix,THTransform *iFrame,
		  double ve,double ac,double ef,double ct,double fr,double da,
		  Tworld *w)
{
  Tlink l;
  Tjoint j;
  Tpolyhedron b;
  double **p;
  unsigned int lID,k;
  double nominalLength;
  Tinterval negative,positive;
  Tcolor colorUp;
	  
  NewInterval(-INF,0.0,&negative);
  NewInterval(0.0,+INF,&positive);
      
  /* for extensible elements the nominalLength is set to 1
     (i.e., no deformation) */
  if (((type==CABLE)&&(IntervalSize(length)>ZERO))||
      (type==SPRING)||(type==PRISMATIC_BAR)||
      (type==PRISMATIC_LEG))
    nominalLength=1.0; /* override the input parameter */
  else
    nominalLength=IntervalCenter(length); /* normal legs, struts, bars,
					     or non-extensible cables (ct length) */

  NEW(p,2,double*);
  for(k=0;k<2;k++)
    {
      NEW(p[k],3,double);
      p[k][0]=p[k][1]=p[k][2]=0.0;
    }

  /* Tests common to all kind of legs */
  if (!Intersection(length,&positive,length))
    Error("Leg length must be positive");
  
  if (!Intersection(rest,&positive,rest))
    Error("Leg rest length must be positive");

  if (LowerLimit(rest)>UpperLimit(length))
    Error("Rest length must be lower than the leg length");

  if (radius<ZERO)
    Error("The leg radius must be possitive");
  
  /* Tests and representation specific for each type of leg */
  switch(type)
    {
    case LEG:
      if (IntervalSize(length)>ZERO)
	Error("Leg length must be constant");
      
      if ((fabs(stiffness)>ZERO)||(!ZeroInterval(rest))||(!ZeroInterval(force)))
	Error("Legs do not carry force information");

      InitAxisXLink(name,NO_FORCE,length,force,mass,iMatrix,iFrame,&l);

      p[0][0]=0.0;
      p[1][0]=nominalLength;
      
      NewSphere(1.5*radius,p[0],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(radius,p[0],p[1],color,2*gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(1.5*radius,p[1],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      break;
    case STRUT:
      /* force must be negative */
      if ((stiffness>0)||
	  (!Intersection(force,&negative,force)))
	Error("Struts can only support compressions (negative forces)");
      /* do not break */
    case BAR:
      if (IntervalSize(length)>ZERO)
	Error("Strut/bar length must be constant");

      /* A link fixed length.... */
      if (ZeroInterval(force))
	InitAxisXLink(name,NO_FORCE,length,force,mass,iMatrix,iFrame,&l);
      else
	InitAxisXLink(name,VAR_FORCE,length,force,mass,iMatrix,iFrame,&l);
      
      p[0][0]=radius;
      p[1][0]=nominalLength-radius;
      
      NewSphere(radius,p[0],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(radius,p[0],p[1],color,2*gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(radius,p[1],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      break;
    case PRISMATIC_LEG:
      if ((fabs(stiffness)>ZERO)||(!ZeroInterval(rest))||(!ZeroInterval(force)))
	Error("Legs do not carry force information");

      if (IntervalSize(length)>LowerLimit(length))
	Error("Wrong range in prismatic leg");

      InitPrismaticXLink(name,NO_FORCE,length,stiffness,rest,force,mass,iMatrix,iFrame,&l);
	
      p[0][0]=0.0;
      p[1][0]=LowerLimit(length)-2*radius;
      
      NewSphere(1.5*radius,p[0],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(radius,p[0],p[1],color,2*gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(radius,p[1],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);

      CopyColor(&colorUp,color);
      Add2Color(1.0,&colorUp);
      
      /* Add the upper part of the prs leg */
      p[0][0]= 0.0;
      p[1][0]=-IntervalSize(length);
      
      NewSphere(1.5*radius,p[0],&colorUp,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(0.5*radius,p[0],p[1],&colorUp,2*gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(0.5*radius,p[0],&colorUp,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      DeleteColor(&colorUp);
      
      break;
    case PRISMATIC_BAR:
      if (IntervalSize(length)>LowerLimit(length))
	Error("Wrong range in prismatic leg");
      
      if ((fabs(stiffness)<ZERO)&&(ZeroInterval(rest))&&(ZeroInterval(force)))
	Error("Prismatic bars must carry force information");
      
      InitPrismaticXLink(name,LINEAR_FORCE,length,stiffness,rest,force,mass,iMatrix,iFrame,&l);
      
      p[0][0]=radius;
      p[1][0]=LowerLimit(length)-radius;
      
      NewSphere(radius,p[0],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(radius,p[0],p[1],color,2*gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(radius,p[1],color,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);

      CopyColor(&colorUp,color);
      Add2Color(1.0,&colorUp);
      
      /* Add the upper part of the prs leg */
      p[0][0]=-radius;
      p[1][0]=-IntervalSize(length);
      
      NewSphere(radius,p[0],&colorUp,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(0.5*radius,p[0],p[1],&colorUp,2*gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(0.5*radius,p[0],&colorUp,gr,bs,&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      DeleteColor(&colorUp);
      
      break;
    case CABLE:
      /* force must be possitive */
      if ((stiffness<0)||
	  (!Intersection(force,&positive,force)))
	Error("Cables can only support tension (postive forces)");
      
      if ((fabs(stiffness)<ZERO)&&(ZeroInterval(rest))&&(ZeroInterval(force)))
	Error("Cables must carry force information");

      if (IntervalSize(length)<ZERO)
	{
	  if ((fabs(stiffness)>ZERO)||(!ZeroInterval(rest)))
	    Error("Can not give linear force model for constant length cables");
	  InitAxisXLink(name,VAR_FORCE,length,force,mass,iMatrix,iFrame,&l);
	}
      else
	InitDeformXLink(name,(IntervalSize(length)<ZERO?VAR_FORCE:LINEAR_FORCE),
			length,stiffness,rest,force,mass,iMatrix,iFrame,&l);
      
      p[0][0]=radius;
      p[1][0]=nominalLength-radius;

      NewSphere(radius,p[0],color,gr,(bs==HIDDEN_SHAPE?bs:DECOR_SHAPE),&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewCylinder(radius,p[0],p[1],color,2*gr,(bs==HIDDEN_SHAPE?bs:DECOR_SHAPE),&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      NewSphere(radius,p[1],color,gr,(bs==HIDDEN_SHAPE?bs:DECOR_SHAPE),&b);
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);
      
      if (bs!=DECOR_SHAPE)
	{
	  /* the object used for collision detection has
	     some gap at the extremes to avoid collisions
	     with the adjacent links */
	  p[0][0]=0.1*nominalLength;
	  p[1][0]=0.9*nominalLength;
	  
	  NewCylinder(radius,p[0],p[1],color,gr,HIDDEN_SHAPE,&b);
	  AddBody2Link(&b,&l);
	  DeletePolyhedron(&b);
	}
      
      break;
    case SPRING:

      /* force must be possitive */
      if ((stiffness<0)||
	  (!Intersection(force,&positive,force)))
	Error("Springs can only support tension (postive forces)");
      
      if ((fabs(stiffness)<ZERO)&&(ZeroInterval(rest))&&(ZeroInterval(force)))
	Error("Springs must carry force information");

      if (IntervalSize(rest)>ZERO)
	Error("Springs must have constant rest length");

    case KSPRING:
      
      if (IntervalSize(length)<ZERO)
	Error("Spring length can not be constant");
       
      if (type==SPRING)
	InitDeformXLink(name,LINEAR_FORCE,length,stiffness,rest,force,mass,iMatrix,iFrame,&l);
      else
	InitDeformXLink(name,NO_FORCE,length,stiffness,rest,force,mass,iMatrix,iFrame,&l);
      
      if (bs!=HIDDEN_SHAPE)
	NewSpring(1.0,0.1,radius,gr,color,&b); /* for springs parameter 'gr'
						  is actually the number of loops*/
      AddBody2Link(&b,&l);
      DeletePolyhedron(&b);

      if (bs!=DECOR_SHAPE)
	{
	  /* the object used for collision detection has
	     some gap at the extremes to avoid collisions
	     with the adjacent links */
	  p[0][0]=0.1;
	  p[1][0]=1.0-0.1;
	  
	  NewCylinder(radius,p[0],p[1],color,gr,HIDDEN_SHAPE,&b);
	  AddBody2Link(&b,&l);
	  DeletePolyhedron(&b);
	}
      
      break;
    default:
      Error("Unknown type of leg");
    }
  
  lID=AddLink2World(&l,FALSE,w);
  DeleteLink(&l);

  /* Now define the joints between the links */
  /* First the lower joint */
  for(k=0;k<3;k++)
    {
      p[0][k]=points[0][k];
      p[1][k]=0.0;
    }
  if (planar)
    NewRevLowJoint(GetWorldNJoints(w),
		   lID1,GetWorldLink(lID1,w),
		   lID,GetWorldLink(lID,w),
		   p,ve,ac,ef,ct,fr,da,&j);
  else
    NewSphSphLowJoint(GetWorldNJoints(w),
		      lID1,GetWorldLink(lID1,w),
		      lID,GetWorldLink(lID,w),
		      p,ve,ac,ef,ct,fr,da,&j);
  AddJoint2World(&j,w);
  DeleteJoint(&j);
  
  /* Now the upper joint */
  for(k=0;k<3;k++)
    {
      p[0][k]=0.0;
      p[1][k]=points[1][k];
    }
  p[0][0]=nominalLength;
  if (planar)
    NewRevUpJoint(GetWorldNJoints(w),
		  lID,GetWorldLink(lID,w),
		  lID2,GetWorldLink(lID2,w),
		  p,ve,ac,ef,ct,fr,da,&j);
  else
    NewSphSphUpJoint(GetWorldNJoints(w),
		     lID,GetWorldLink(lID,w),
		     lID2,GetWorldLink(lID2,w),
		     p,ve,ac,ef,ct,fr,da,&j);
  AddJoint2World(&j,w);
  DeleteJoint(&j);
      
  for(k=0;k<2;k++)
    free(p[k]);
  free(p);
}

void AddObstacle2World(char *name,Tpolyhedron *o,Tworld *w)
{
  unsigned int j;

  if (w->stage!=WORLD_IN_DEFINITION)
    Error("Obstacles can only be added during the world definition");

  w->no++;
  w->np++;

  if (w->nl>0)
    {
      /* the first obstacle, we create the LO table */
      if (w->no==1)
	NEW(w->checkCollisionsLO,w->nl,boolean*);

      /* Add a column to the LO table */
      for(j=0;j<w->nl;j++)
	{
	  if (w->no==1)
	    { NEW(w->checkCollisionsLO[j],w->no,boolean); /*create*/}
	  else
	    { MEM_EXPAND(w->checkCollisionsLO[j],w->no,boolean); /* enlarge */}
	  w->checkCollisionsLO[j][w->no-1]=FALSE;
	}
      
      /* initialize the new row */
      for(j=0;j<w->no;j++)
	w->checkCollisionsLO[w->nl-1][j]=FALSE;
    }

  AddShape2Environment(name,o,&(w->e));
}

unsigned int GetWorldMobility(Tworld *w)
{
  return(GetMechanismMobility(&(w->m)));
}

boolean IsMechanismInWorldAllSpheres(Tworld *w)
{
  return(IsMechanismAllSpheres(&(w->m)));
}

boolean WorldHasVelocity(Tparameters *p,Tworld *w)
{
  return(CuikHasVelocity(p,&(w->kinCS)));
}

unsigned int GetWorldLinkID(char *linkName,Tworld *w)
{
  return(GetLinkID(linkName,&(w->m)));
}

unsigned int GetWorldObstacleID(char *obsName,Tworld *w)
{
  return(GetObstacleID(obsName,&(w->e)));
}

char *GetWorldObstacleName(unsigned int id,Tworld *w)
{
  return(GetObstacleName(id,&(w->e)));
}

Tlink *GetWorldLink(unsigned int linkID,Tworld *w)
{
  return(GetMechanismLink(linkID,&(w->m)));
}

Tjoint *GetWorldJoint(unsigned int jointID,Tworld *w)
{
  return(GetMechanismJoint(jointID,&(w->m)));
}

Tpolyhedron *GetWorldObstacle(unsigned int obsID,Tworld *w)
{
  return(GetObstacleShape(obsID,&(w->e)));
}

unsigned int GetWorldNLinks(Tworld *w)
{
  return(w->nl);
}

unsigned int GetWorldNJoints(Tworld *w)
{
  return(w->nj);
}

unsigned int GetWorldNObstacles(Tworld *w)
{
  return(w->no);
}

unsigned int GetWorldNConvexBodiesInLinks(Tworld *w)
{
  return(w->nb);
}

unsigned int GetWorldNConvexBodies(Tworld *w)
{
  return(w->np);
}

void DeleteWorldCollisionInfo(Tworld *w)
{
  unsigned int i;

  if (w->checkCollisionsLL!=NULL)
    {
      for(i=0;i<w->nl;i++)
	free(w->checkCollisionsLL[i]);
      free(w->checkCollisionsLL);
    }

  if (w->checkCollisionsLO!=NULL)
    {
      for(i=0;i<w->nl;i++)
	free(w->checkCollisionsLO[i]);
      free(w->checkCollisionsLO);
    }
}

void WorldInitDOFInfo(Tworld *w)
{
  unsigned int i,s,k,n,p,dl,dj;
  Tjoint *j;
  Tlink *l;

  if (w->stage!=WORLD_DEFINED)
    Error("The DOF info is to be defined at the end of the world definition");

  dl=0;
  for(i=0;i<w->nl;i++)
    {
      l=GetMechanismLink(i,&(w->m));
      dl+=NumLinkDOF(l);
    }
  dj=0;
  for(i=0;i<w->nj;i++)
    {
       j=GetMechanismJoint(i,&(w->m));
       dj+=GetJointDOF(j);
    }
  
  w->ndof=dl+dj;
 
  NEW(w->link2dof,w->nl,unsigned int);
  NEW(w->dof2link,w->ndof,unsigned int); /* only used for link-dofs */
  NEW(w->dof2param,w->ndof,unsigned int); /* only used for link-dofs */
  
  NEW(w->joint2dof,w->nj,unsigned int);
  NEW(w->dof2joint,w->ndof,unsigned int); /* only used for joint-dofs */
  NEW(w->dof2range,w->ndof,unsigned int); /* only used for joint-dofs */

  for(i=0;i<w->ndof;i++)
    {
      w->dof2link[i]=NO_UINT;
      w->dof2param[i]=NO_UINT;
      
      w->dof2joint[i]=NO_UINT;
      w->dof2range[i]=NO_UINT;
    }
  
  n=0;
  for(i=0;i<w->nl;i++)
    {
       l=GetMechanismLink(i,&(w->m));
       k=NumLinkDOF(l);
       if (k>0)
	 {
	   w->link2dof[i]=n;
	   
	   for(s=0;s<k;s++)
	     {
	       w->dof2link[n]=i;
	       w->dof2param[n]=s;
	       n++;
	     }
	 }
    }
  
  for(i=0;i<w->nj;i++)
    {
      j=GetMechanismJoint(i,&(w->m));
      p=CoupledWith(j);
      if (p==NO_UINT)
	{
	  /* Note that if Num_DOF==0 (FIX_JOINT) nothing is done 
	     and the dof2joint and joint2dof mappings are not
	     actually used. */

	  w->joint2dof[i]=n;

	  k=GetJointDOF(j);
	  for(s=0;s<k;s++)
	    {
	      w->dof2joint[n]=i;
	      w->dof2range[n]=s;
	      n++;
	    }
	}
      else
	{
	  if (p>=i)
	    Error("Joints can only be coupled with preceeding joints");
	  /* We will re-use the values from the original joint. */
	  w->joint2dof[i]=w->joint2dof[p];
	}
    }
}


void WorldDeleteDOFInfo(Tworld *w)
{
  free(w->link2dof);
  free(w->dof2link);
  free(w->dof2param);
  
  free(w->joint2dof);
  free(w->dof2joint);
  free(w->dof2range);
}

unsigned int GetWorldNDOF(Tworld *w)
{
  return(w->ndof);
}

unsigned int GetWorldActionDimension(Tworld *w)
{
  return(w->da);
}

void GetWorldRangeDOF(unsigned int ndof,Tinterval *r,Tworld *w)
{
  Tlink *l;
  Tjoint *j;

  if (ndof>=w->ndof)
    Error("DOF out of range in GetWorldRangeDOF");

  if (w->dof2joint[ndof]==NO_UINT)
    {
      /* A link dof */
      l=GetMechanismLink(w->dof2link[ndof],&(w->m));
      CopyInterval(r,GetLinkDOFRange(w->dof2param[ndof],l));
    }
  else
    {
      /* A joint dof */
      j=GetMechanismJoint(w->dof2joint[ndof],&(w->m));
      GetJointRangeN(w->dof2range[ndof],w->maxCoord,r,j);
    }
}

void GetWorldJointLabel(unsigned int ndof,char **string,Tworld *w)
{
  if (w->dof2joint==NULL)
    Error("Uninitialized dof info in GetWorkdJointLabel");

  /* Only return a string for the first dof of each joint */
  if (w->dof2range[ndof]==0)
    GetJointName(string,GetMechanismJoint(w->dof2joint[ndof],&(w->m)));
  else
    *string=NULL;
}

void GetWorldDOFLabel(unsigned int ndof,char **string,Tworld *w)
{

  if (w->dof2joint==NULL)
    Error("Uninitialized dof info in GetWorkdDOFLabel");

  if (w->dof2joint[ndof]==NO_UINT)
    {
      Tlink *l;
      char *linkName,*paramName;
      
      /* Link dof */

      l=GetMechanismLink(w->dof2link[ndof],&(w->m));

      linkName=GetLinkName(l);
      GetLinkDOFLabel(w->dof2param[ndof],&paramName,l);
      
      NEW(*string,strlen(linkName)+strlen(paramName)+10,char);
      sprintf(*string,"%s %s",paramName,linkName);

      free(paramName);
    }
  else
    {
      Tjoint *j;
      
      /* Joint motion dof */
      j=GetMechanismJoint(w->dof2joint[ndof],&(w->m));
      if (GetJointDOF(j)==1)
	GetJointName(string,j);
      else
	{
	  Tjoint *j;
	  char *jointName,*dofName;

	  j=GetMechanismJoint(w->dof2joint[ndof],&(w->m));
	  
	  GetJointName(&jointName,j);
	  GetJointDOFName(w->dof2range[ndof],&dofName,j);

	  NEW(*string,strlen(jointName)+strlen(dofName)+10,char);
	  if (dofName!=NULL)
	    sprintf(*string,"%s %s",jointName,dofName);
	  else
	    sprintf(*string,"%s",jointName);
	  
	  free(jointName);
	  free(dofName);
	}
    }
}

unsigned int GetWorldJoint2Dof(unsigned int n,Tworld *w)
{
  if (n>=w->nj)
    Error("Index out of range in GetWorldJoint2Dof");
  return(w->joint2dof[n]);
}

unsigned int GetWorldJointTo(unsigned int n,signed int *s,Tworld *w)
{

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  if (n>=w->nl)
    Error("Index out of range in GetWorldJointTo");
  
  *s=w->jointS[n];
  return(w->jointTo[n]);
}

unsigned int GetWorldLinkN(unsigned int n,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");
  
  if (n>=w->nl)
    Error("Index out of range in GetWorldLinkN");
  
  return(w->sortedLinks[n]);
}

unsigned int GetWorldPredLink(unsigned int n,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  if (n>=w->nl)
    Error("Index out of range in GetWorldPredLink");
  
  return(w->predLink[n]);
}

unsigned int GetWorldClosureN(unsigned int n,Tworld *w)
{
   if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");
  
  if (n>=w->nLoops)
    Error("Index out of range in GetWorldClosureN");
  
  return(w->sortedClosures[n]);
}

boolean IsClosingJoint(unsigned int n,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  if (n>=w->nj)
    Error("Index out of range in IsClosingJoint");
  
  return(w->closingJoint[n]);
}
  
unsigned int NumLoops(Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");
  
  return(w->nLoops);
}

inline boolean IsWorldPolynomial(Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");
  
  return(IsCSPolynomial(&(w->kinCS)));
}

void CheckAllCollisions(unsigned int fl,unsigned int fo,Tworld *w)
{
  unsigned int i,j;

  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  CheckSelfCollisions(fl,w);
  
  if (w->no>fo)
    {
      /* All link-obstacles are checked for collision except
         the ground link with any obstacle */
      for(i=fl;i<w->nl;i++)
	{
	  for(j=fo;j<w->no;j++)
	    w->checkCollisionsLO[i][j]=((!IsGroundLink(i))&&
					(GetObstacleShapeStatus(j,&(w->e))!=DECOR_SHAPE));
	}
    }
}

void NoCheckAllCollisions(unsigned int fl,unsigned int fo,Tworld *w)
{
  unsigned int i,j;

  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  NoCheckSelfCollisions(fl,w);
  
  if (w->no>fo)
    {
      for(i=fl;i<w->nl;i++)
	{
	  for(j=fo;j<w->no;j++)
	    w->checkCollisionsLO[i][j]=FALSE;
	}
    }
}

void CheckSelfCollisions(unsigned int fl,Tworld *w)
{
  unsigned int i,j;

  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  /* Collisions of a link with itself are not checked */
  for(i=fl;i<w->nl;i++)
    {
      for(j=fl;j<w->nl;j++)
	w->checkCollisionsLL[i][j]=(i!=j);
    }
}

void NoCheckSelfCollisions(unsigned int fl,Tworld *w)
{
  unsigned int i,j;

  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  for(i=fl;i<w->nl;i++)
    {
      for(j=fl;j<w->nl;j++)
	w->checkCollisionsLL[i][j]=FALSE;
    }
}

void CheckLinkLinkCollision(unsigned int a,unsigned int b,Tworld *w)
{
  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  if (a==b)
    Error("Repeated link identifier in NoCheckLinkLinkCollision");
  
  if ((a<w->nl)&&(b<w->nl))
    w->checkCollisionsLL[a][b]=w->checkCollisionsLL[b][a]=TRUE;
}

void NoCheckLinkLinkCollision(unsigned int a,unsigned int b,Tworld *w)
{
  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  if (a==b)
    Error("Repeated link identifier in NoCheckLinkLinkCollision");
  
  if ((a<w->nl)&&(b<w->nl))
    w->checkCollisionsLL[a][b]=w->checkCollisionsLL[b][a]=FALSE;
}

void CheckLinkObstacleCollision(unsigned int a,unsigned int b,Tworld *w)
{ 
  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  if ((a<w->nl)&&(!IsGroundLink(a))&&(b<w->no))
    w->checkCollisionsLO[a][b]=TRUE;
}

void NoCheckLinkObstacleCollision(unsigned int a,unsigned int b,Tworld *w)
{
  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The geometry information must be added while defining the world");

  if ((a<w->nl)&&(b<w->no))
    w->checkCollisionsLO[a][b]=FALSE;
}

void CheckObstacleCollision(unsigned int fl,unsigned int b,Tworld *w)
{
  unsigned int i;

  for(i=fl;i<w->nl;i++)
    CheckLinkObstacleCollision(i,b,w);
}

void NoCheckObstacleCollision(unsigned int fl,unsigned int b,Tworld *w)
{
  unsigned int i;

  for(i=fl;i<w->nl;i++)
    NoCheckLinkObstacleCollision(i,b,w);
}

void NoCheckConnectedCollisions(unsigned int fl,Tworld *w)
{
  unsigned int i,j,k,l1,l2;
  Tjoint *jo,*jo1,*jo2;
  Tlink *lk;

  /* skip the collision detection between links directly connected
     by a joint */
  for(i=0;i<w->nj;i++)
    {
      jo=GetMechanismJoint(i,&(w->m));
      l1=JointFromID(jo);
      l2=JointToID(jo);
      if ((l1>=fl)&&(l2>=fl))
	NoCheckLinkLinkCollision(l1,l2,w);
    }
  /* Skip the collision detection between links coincident at at
     NoRot link (punctual link connecting tensegrity elements) */
  for(i=fl;i<w->nl;i++)
    {
      lk=GetMechanismLink(i,&(w->m));
      if (GetLinkType(lk)==LINK_NoRot)
	{
	  for(j=0;j<w->nj;j++)
	    {
	      jo1=GetMechanismJoint(j,&(w->m));
	      if ((JointFromID(jo1)==i)||(JointToID(jo1)==i))
		{
		  for(k=j+1;k<w->nj;k++)
		    {
		      jo2=GetMechanismJoint(k,&(w->m));
		      if ((JointFromID(jo2)==i)||(JointToID(jo2)==i))
			{
			  /* Determine the links not common beetween jo1 and jo2 */
			  if (JointFromID(jo1)==JointFromID(jo2))
			    {
			      l1=JointToID(jo1);
			      l2=JointToID(jo2);
			    }
			  else
			    {
			      if (JointFromID(jo1)==JointToID(jo2))
				{
				  l1=JointToID(jo1);
				  l2=JointFromID(jo2);
				}
			      else
				{
				  if (JointToID(jo1)==JointFromID(jo2))
				    {
				      l1=JointFromID(jo1);
				      l2=JointToID(jo2);
				    }
				  else
				    {
				      l1=JointFromID(jo1);
				      l2=JointFromID(jo2);
				    } 
				}
			    }
			  NoCheckLinkLinkCollision(l1,l2,w);
			}
		    }
		}
	    }
	}
    }
}

boolean AnyCollision(Tworld *w)
{
  unsigned int i;
  boolean any;

  any=FALSE;
  for(i=0;((i<w->nl)&&(!any));i++)
    any=LinkCanCollide(i,w->nl,w->no,w->checkCollisionsLL,w->checkCollisionsLO);

  return(any);
}

void PrintCollisions(FILE *f,Tworld *w)
{
  if (AnyCollision(w))
    {
      unsigned int i,j;
      char *l;

      fprintf(f,"[COLLISIONS]\n\n");
      fprintf(f,"  do not check: all\n");
      for(i=0;i<w->nl;i++)
	{
	  l=GetLinkName(GetMechanismLink(i,&(w->m)));
	  for(j=i+1;j<w->nl;j++)
	    {
	      if ((w->checkCollisionsLL[i][j])||(w->checkCollisionsLL[j][i]))
		fprintf(f,"  check: %s,%s\n",l,GetLinkName(GetMechanismLink(j,&(w->m))));
	    }
	}
      for(i=0;i<w->nl;i++)
	{
	  l=GetLinkName(GetMechanismLink(i,&(w->m)));
	  for(j=0;j<w->no;j++)
	    if (w->checkCollisionsLO[i][j])
	      fprintf(f,"  check: %s,%s\n",l,GetObstacleName(j,&(w->e)));
	}
      fprintf(f,"\n");
    }
}

boolean NewtonInWorld(Tparameters *p,double *v,Tbox *b_sol,Tworld *w)
{
  double *vA;
  Tbox b_solA;
  boolean converged;
  unsigned int i,k,nv,nvs;
  boolean *systemVarsKin;

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  nv=GetCSSystemVars(&systemVarsKin,&(w->kinCS));
  NEW(vA,nv,double);

  converged=CuikNewton(p,vA,&b_solA,&(w->kinCS));

  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVarsKin[i])
	nvs++;
    }

  InitBox(nvs,NULL,b_sol);

  k=0;
  for(i=0;i<nv;i++)
    {
      if (systemVarsKin[i])
	{
	  v[k]=vA[i];
	  SetBoxInterval(k,GetBoxInterval(i,&b_solA),b_sol);
	  k++;
	}
    }
  DeleteBox(&b_solA);
  free(vA);
  free(systemVarsKin);

  #if (_DEBUG>2)
    printf("Newton generated box:");
    PrintBox(stdout,b_sol);
    fflush(stdout);
  #endif

  return(converged);
}

inline unsigned int GetWorldSystemVars(boolean **sv,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSSystemVars(sv,&(w->kinCS)));
}

inline unsigned int GetWorldPositionVars(boolean **pv,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSPositionVars(pv,&(w->kinCS)));
}

inline unsigned int GetWorldPositionEqs(boolean **pe,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSPositionEqs(pe,&(w->kinCS)));
}

inline unsigned int GetWorldPositionVelocityVars(boolean **pv,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSPositionVelocityVars(pv,&(w->kinCS)));
}

inline unsigned int GetWorldPositionVelocityEqs(boolean **pe,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSPositionVelocityEqs(pe,&(w->kinCS)));
}

inline unsigned int GetWorldVarTopology(unsigned int vID,Tworld *w)
{
  return(GetCSVarTopology(vID,&(w->kinCS)));
}

unsigned int GetWorldSimpVariableMask(Tparameters *p,boolean **sv,Tworld *w)
{
  unsigned int i,n;

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  n=GetCSNumVariables(&(w->kinCS));

  NEW((*sv),n,boolean);
  for(i=0;i<n;i++)
    (*sv)[i]=FALSE;

  for(i=0;i<w->nl;i++)
    GetLinkPoseSimpVars(p,*sv,&(w->kinCS),GetMechanismLink(i,&(w->m)));

  return(n);
}

inline void GetWorldVarNames(char **vn,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSVariableNames(vn,&(w->kinCS)));
}

inline char *GetWorldSystemVarName(unsigned int nv,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  return(GetCSSystemVariableName(nv,&(w->kinCS)));
} 

void GenerateWorldEquations(Tparameters *p,Tconstants *cts,char *eqFile,Tworld *w)
{  
  unsigned int i,rep;
  Tvariables vs;
  
  if (w->stage!=WORLD_IN_DEFINITION)
    Error("The equations are alrady defined");

  w->stage=WORLD_DEFINED;

  InitWorldCS(w);

  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  w->maxCoord=GetMechanismMaxCoordinate(&(w->m))+
              GetEnvironmentMaxCoordinate(&(w->e));

  /*Generate the kinematic equations: this includes link reference variables
    and equations, joint variables and equations, joint limit variables and
    equations and loop equations. Note that all links and joints are used in the kinCS 
    and thus, after generating it, we can assume that the variables associated
    to links and joints are all already defined. 
    This already initializes the branch2link, the sortedLinks and the jointTo
    arrays.
  */
  InitWorldKinCS(p,w);


  /* We generate the equations defining the translation 
     from the ground link to all other links. These equations are the
     same as those generated by \ref GenerateEquationsFromBranch but for
     open branches we do not add the variables defining the X-Y-Z 
     of the link reference.
  */

  InitEquations(&(w->refEqs));
  if (rep==REP_JOINTS)
    {
      TMequation ref;
      
      for(i=0;i<w->nl;i++) 
	{
	  GenerateMEquationFromBranch(p,&(w->branch2Link[i]),&ref,w);
	  AddMatrixEquation(&ref,&(w->refEqs));
	  DeleteMEquation(&ref);
	}
    }
  else
    {
      Tequation ref[3];
      unsigned int j;

      for(i=0;i<w->nl;i++) 
	{
	  GenerateTransEquationsFromBranch(p,COORD_EQ,ref,&(w->branch2Link[i]),w);
	  for(j=0;j<3;j++)
	    {
	      AddEquationNoSimp(&(ref[j]),&(w->refEqs));
	      DeleteEquation(&(ref[j]));
	    }
	}
    }

  /* Define the dof information (this is used when defining max velocity!) */
  WorldInitDOFInfo(w);

  
  /* Add the user provided equations, if any */
  if (eqFile!=NULL)
    AddCuikSystemFromFile(p,TRUE,cts,eqFile,&(w->kinCS));
  
  /* if necessary add the velocity equations */
  if (GetParameter(CT_DYNAMICS,p)>0)
    {
      unsigned int jID;
      double *ms,mv;

      if (rep==REP_JOINTS)
	{
	  mv=GetParameter(CT_DEFAULT_MAX_VELOCITY,p);
	  NEW(ms,w->ndof,double);

	  for(i=0;i<w->ndof;i++)
	    {
	      jID=w->dof2joint[i];
	      if (jID==NO_UINT)
		ms[i]=mv;
	      else
		ms[i]=GetJointVelocity(GetMechanismJoint(jID,&(w->m)));
	    }
	}
      else
	ms=NULL;
      
      AddVelocityEquations(p,ms,&(w->kinCS));
      
      if (ms!=NULL)
	free(ms);
    }
  
  /* When all equations are defined, cache information about them */
  GetCSVariables(&vs,&(w->kinCS));
  InitJacobian(&vs,&(w->refEqs),&(w->refEqsJ));
  DeleteVariables(&vs);
  
  /*identify the system variables to use later on*/
  w->nvars=GetCSSystemVars(&(w->systemVars),&(w->kinCS));
  w->nsvars=0;
  for(i=0;i<w->nvars;i++)
    {
      if (w->systemVars[i])
	w->nsvars++;
    }
}

void GenerateForceEquilibriumEquations(Tparameters *p,Tworld *w)
{
  unsigned int rep;

  if (w->stage<WORLD_DEFINED)
    Error("GenerateForceEquilibriumEquations assumes that the equations are already generated (GenerateWorldEquations)");
  
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (rep!=REP_JOINTS)
    {
      unsigned int i,j;
      Tequation eq[3],eqn;
      Tmonomial f;
      unsigned int x,y,z,le,re,fr;
      Tlink *l;
      double pt;
  
      for(i=0;i<w->nl;i++)
	{
	  l=GetMechanismLink(i,&(w->m));
	  if (IsForceEquilibriumLink(l))
	    {
	      for(j=0;j<3;j++)
		{
		  InitEquation(&(eq[j]));
		  SetEquationType(SYSTEM_EQ,&(eq[j]));
		  SetEquationCmp(EQU,&(eq[j]));
		  SetEquationValue(-GetForceOnLink(j,l),&(eq[j]));
		}

	      for(j=0;j<w->nj;j++)
		JointForceEquation(p,i,&(w->kinCS),eq,GetMechanismJoint(j,&(w->m)));
      
	      for(j=0;j<3;j++)
		{
		  AddEquation2CS(p,&(eq[j]),&(w->kinCS));
		  DeleteEquation(&(eq[j]));
		}
	    }
	}

      pt=GetParameter(CT_PRETENSION,p);
      if (pt<-ZERO)
	Error("Pretension paramter can not be negative");

      if (pt>ZERO)
	{
	  /* Normalize tension to compensate for one pretension (we always have one at least).
	     If more pre-tensions are possible, fix some tension to a constant to avoid it */
	  InitEquation(&(eqn));
	  SetEquationType(SYSTEM_EQ,&(eqn));
	  SetEquationCmp(EQU,&(eqn));
	  SetEquationValue(pt*pt,&(eqn));
	  InitMonomial(&f);

	  for(i=0;i<w->nl;i++)
	    {
	      l=GetMechanismLink(i,&(w->m));
	      if (GetLinkForceModel(l)!=NO_FORCE)
		{
		  GetLinkForceVars(rep,&x,&y,&z,&le,&re,&fr,&(w->kinCS),l);
		  AddVariable2Monomial(NFUN,fr,2,&f);
		  AddMonomial(&f,&eqn);
		  ResetMonomial(&f);
		}
	    }
	  DeleteMonomial(&f);

	  AddEquation2CS(p,&(eqn),&(w->kinCS));
	  DeleteEquation(&(eqn));
	}
    }
}

unsigned int WorldForceVars(Tparameters *p,boolean **fv,Tworld *w)
{
  unsigned int i,k,n,r;
  
  if (w->stage<WORLD_DEFINED)
    Error("WorldForceVars assumes that the equations are already generated (GenerateWorldEquations)");

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  
  /* Identify the force variables in the system */
  NEW(*fv,w->nvars,boolean);
  for(i=0;i<w->nvars;i++)
    (*fv)[i]=FALSE;

  n=0;
  for(i=0;i<w->nl;i++)
    n+=SetForceVars(r,*fv,&(w->kinCS),GetMechanismLink(i,&(w->m)));

  if (n>0)
    {
      /* Compact so that only system variables are returned */
      k=0;
      for(i=0;i<w->nvars;i++)
	{
	  (*fv)[k]=(*fv)[i];
	  if (w->systemVars[k]) k++;
	}
    }
  return(n);
}

unsigned int WorldSimpKinematicVars(Tparameters *p,boolean **kv,Tworld *w)
{
  boolean *fv;
  unsigned int i,n,r;
  
 if (w->stage<WORLD_DEFINED)
    Error("WorldSimpKinematicVars assumes that the equations are already generated (GenerateWorldEquations)");

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  
  /* Identify the force variables in the system */
  NEW(fv,w->nvars,boolean);
  for(i=0;i<w->nvars;i++)
    fv[i]=FALSE;

  n=0;
  for(i=0;i<w->nl;i++)
    n+=SetForceRelatedVars(r,fv,&(w->kinCS),GetMechanismLink(i,&(w->m)));
  if (n==0)
    *kv=NULL;
  else
    {
      /* The kinematic vars are the non-force related vars */
      for(i=0;i<w->nvars;i++)
	fv[i]=!fv[i];
      
      n=SimplifyBooleanArray(p,fv,kv,&(w->kinCS)); /* Now simplify fv */
    }
  free(fv);
  
  return(n);
}

unsigned int WorldForceVarsIndices(Tparameters *p,unsigned int **iv,Tworld *w)
{
  unsigned int n;
  boolean *fv;

  n=WorldForceVars(p,&fv,w);
  if (n==0)
    iv=NULL;
  else
    {
      unsigned int i,k,ns;
      
      NEW(*iv,n,unsigned int);
      ns=GetWorldNumSystemVariables(w);
      k=0;
      for(i=0;i<ns;i++)
	{
	  if (fv[i])
	    {
	      (*iv)[k]=i;
	      k++;
	    }
	}
      if (k!=n)
	Error("Wrong number of force variables in WorldForceVarsIndices");
    }
  free(fv);

  return(n);
}

double WorldPotentialEnergy(Tparameters *p,boolean simp,double *sol,void *w)
{
  unsigned int rep;
  double e;
  Tworld *wp;

  wp=(Tworld *)w;

  if (wp->stage<WORLD_DEFINED)
    Error("WorldPotentialEnergy assumes that the equations are already generated (GenerateWorldEquations)");
  
  e=0.0;
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
 
  if (rep!=REP_JOINTS)
    {
      unsigned int i;
      double *fullSol;
      Tlink *l;

      if (simp)
	{
	  /* unsimplify */
	  RegenerateOriginalPoint(p,sol,&fullSol,&(wp->kinCS));
	  /* fill the gaps (dummy/force) vars not appearing in simplification */
	  RegenerateMechanismSolution(p,&(wp->kinCS),fullSol,&(wp->m));
	}
      else
	/* get dummy/force vars (i.e. non-system vars) not in the input */
	RegenerateWorldSolutionPoint(p,sol,&fullSol,wp);
      
      for(i=0;i<wp->nl;i++)
	{
	  l=GetMechanismLink(i,&(wp->m));
	  e+=LinkPotentialEnergy(rep,&(wp->kinCS),fullSol,l);
	}
      free(fullSol);
    }

  return(e);
}

void WorldForceField(Tparameters *p,boolean simp,double *sol,
		     double **g,void *w)
{
  unsigned int rep;
  Tworld *wp;
  double *gFull;

  wp=(Tworld *)w;
  
  if (wp->stage<WORLD_DEFINED)
    Error("WorldPotentialEnergyGradient assumes that the equations are already generated (GenerateWorldEquations)");

  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  /* gradient in original system (initially zero) */
  NEWZ(gFull,wp->nvars,double);
  
  if (rep!=REP_JOINTS)
    {
      unsigned int i;
      double *fullSol;
      Tlink *l;

      if (simp)
	{
	  /* unsimplify */
	  if (RegenerateOriginalPoint(p,sol,&fullSol,&(wp->kinCS))!=wp->nvars)
	    Error("Missmatch in the number of variables");
	  /* fill the gaps (dummy/force) vars not appearing in simplification */
	  RegenerateMechanismSolution(p,&(wp->kinCS),fullSol,&(wp->m));
	}
      else
	/* get dummy/force vars (i.e. non-system vars) not in the input */
	RegenerateWorldSolutionPoint(p,sol,&fullSol,w);
   
      for(i=0;i<wp->nl;i++)
	{
	  l=GetMechanismLink(i,&(wp->m));
	  LinkForceField(rep,&(wp->kinCS),fullSol,gFull,l);
	}
      
      free(fullSol);
    }
  
  if (simp)
    {
      /* If the input is in the simplified system, so is the output. */
      GenerateSimplifiedPoint(p,gFull,g,&(wp->kinCS));
      free(gFull);
    }
  else
      *g=gFull;
}

void WorldForceFieldProjectedGradient(Tparameters *p,boolean simp,
				      double *proj,double *sol,
				      double **g,void *w)
{
  WorldForceField(p,simp,proj,g,w);
}

void FixLinks(Tparameters *p,Tworld *w)
{
  unsigned int rep;

  if (w->stage<WORLD_DEFINED)
    Error("FixLinks assumes that the equations are already generated (GenerateWorldEquations)");
  
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (rep!=REP_JOINTS)
    {
      Tequation ref[3],eq;
      unsigned int i,j;
      double v;
      Tlink *l;
  
      for(i=0;i<w->nl;i++) 
	{
	  l=GetMechanismLink(i,&(w->m));
	  if (GetLinkType(l)!=LINK_Connect)
	    {
	      GenerateTransEquationsFromBranch(p,SYSTEM_EQ,ref,&(w->branch2Link[i]),w);
	      for(j=0;j<3;j++)
		{
		  v=GetLinkTrans(j,l);
		  if (v!=INF)
		    {
		      CopyEquation(&eq,&(ref[j]));
		      SetEquationValue(GetEquationValue(&eq)+v,&eq);
		      AddEquation2CS(p,&eq,&(w->kinCS));
		      DeleteEquation(&eq);
		    }
		  DeleteEquation(&(ref[j]));
		}
	    }
	}
    }
}

void WorldFixTensegrityAddon(Tparameters *p,unsigned int linkID,
			     double **point,unsigned int *n,Tworld *w)
{
  unsigned int i,j;
  Tequation eq[3];
  char *lname,*vname;
  Tlink *l;
  Tmonomial f;
  unsigned int vID;
  
  l=GetMechanismLink(linkID,&(w->m));
  lname=GetLinkName(l); 

  NEW(vname,strlen(lname)+100,char);

  InitMonomial(&f);
  
  for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
	GenerateTransEquationsFromBranch(p,SYSTEM_EQ,eq,&(w->branch2Link[n[i]]),w);

      for(j=0;j<3;j++)
	{
	  LINK_TRANS(vname,lname,j);

	  vID=GetCSVariableID(vname,&(w->kinCS));
	  if (vID==NO_UINT)
	    Error("Undefined variable in WorldFixTensegrityAddon");
	  
	  AddCt2Monomial(-1.0,&f);
	  AddVariable2Monomial(NFUN,vID,1,&f);
	  AddMonomial(&f,&(eq[j]));
	  ResetMonomial(&f);
	}
      
      ApplyLinkRot(p,-1,NO_UINT,point[i],eq,&(w->kinCS),FALSE,l);
      
       for(j=0;j<3;j++)
	 {
	   AddEquation2CS(p,&(eq[j]),&(w->kinCS));
	   DeleteEquation(&(eq[j]));
	 }
    }
  free(vname);
  DeleteMonomial(&f);
}

void FixZToZero(Tparameters *p,Tworld *w)
{
  unsigned int rep;

  if (w->stage<WORLD_DEFINED)
    Error("FixZToZero assumes that the equations are already generated (GenerateWorldEquations)");
  
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (rep!=REP_JOINTS)
    {
      unsigned int i;
      Tlink *l;
      
      for(i=0;i<w->nl;i++) 
	{
	  l=GetMechanismLink(i,&(w->m));
	  if (GetLinkType(l)!=LINK_Connect)
	    FixLinkZToZero(p,i,&(w->kinCS),l);
	}
    }
} 

void WorldCoupleTensegrityVariable(Tparameters *p,
				   unsigned int t,
				   unsigned int lID1,unsigned int lID2,
				   double scale,THTransform *r,
				   Tworld *w)
{
  unsigned int rep;

  if (w->stage<WORLD_DEFINED)
    Error("WorldCoupleTensegrityVariable assumes that the equations are already generated (GenerateWorldEquations)");

  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (rep!=REP_JOINTS)
    {
      Tlink *l1,*l2;
      unsigned int vID[3];
      unsigned int le1,re1,f1;
      unsigned int le2,re2,f2;
      

      l1=GetWorldLink(lID1,w);
      l2=GetWorldLink(lID2,w);
      
      if (t==COUPLE_ORIENTATION)
	{
	  Tequation eq[3];
	  unsigned int i,j;
	  Tmonomial f;

	  if ((GetLinkType(l1)==LINK_NoRot)||
	      (GetLinkType(l2)==LINK_NoRot))
	    Error("Coupling the orientation of links without orientation");
	  
	  InitMonomial(&f);

	  for(i=0;i<3;i++)
	    InitEquation(&(eq[i]));

	  GetLinkForceVars(rep,&(vID[0]),&(vID[1]),&(vID[2]),
			   &le1,&re1,&f1,&(w->kinCS),l1);

	  /* director vector of link 1 = */
	  for(i=0;i<3;i++)
	    {
	      AddVariable2Monomial(NFUN,vID[i],1,&f);
	      AddMonomial(&f,&(eq[i]));
	      ResetMonomial(&f);
	    }
	     
	  GetLinkForceVars(rep,&(vID[0]),&(vID[1]),&(vID[2]),
			   &le2,&re2,&f2,&(w->kinCS),l2);

	  /* R * director vector of link 2 */
	  for(i=0;i<3;i++)
	    {
	       for(j=0;j<3;j++)
		 {
		   AddCt2Monomial(-HTransformGetElement(i,j,r),&f);
		   AddVariable2Monomial(NFUN,vID[j],1,&f);
		   AddMonomial(&f,&(eq[i]));
		   ResetMonomial(&f);
		 }
	    }
	  	  
	  for(i=0;i<3;i++)
	    {  
	      SetEquationCmp(EQU,&(eq[i]));
	      SetEquationValue(0,&(eq[i]));
	      SetEquationType(SYSTEM_EQ,&(eq[i]));
	      
	      AddEquation2CS(p,&(eq[i]),&(w->kinCS));
	      DeleteEquation(&(eq[i]));
	    }
	  
	  DeleteMonomial(&f);
	}
      else
	{
	  Tequation eq;
	  Tmonomial f;
	  
	  if (GetLinkForceModel(l1)==NO_FORCE)
	    Error("Defining a force couple over a non-tensegrity link");
	  
	  if (GetLinkForceModel(l2)==NO_FORCE)
	    Error("Defining a force couple over a non-tensegrity link");
      
	  GetLinkForceVars(rep,&(vID[0]),&(vID[1]),&(vID[2]),
			   &le1,&re1,&f1,&(w->kinCS),l1);
	  GetLinkForceVars(rep,&(vID[0]),&(vID[1]),&(vID[2]),
			   &le2,&re2,&f2,&(w->kinCS),l2);

	  InitEquation(&eq);
	  InitMonomial(&f);
	  
	  switch(t)
	    {
	    case COUPLE_LENGTH:
	      if ((!IsVariableLengthLink(l1))||
		  (!IsVariableLengthLink(l2)))
		Error("Can not couple the length of fixed-length links");
	      AddVariable2Monomial(NFUN,le1,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      AddCt2Monomial(-scale,&f); 
	      AddVariable2Monomial(NFUN,le2,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);
	      break;

	    case COUPLE_REST:
	       if ((GetLinkForceModel(l1)!=LINEAR_FORCE)||
		  (GetLinkForceModel(l2)!=LINEAR_FORCE))
		Error("Can not couple the rest length of links without linear force model");
	      
	      AddVariable2Monomial(NFUN,re1,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      AddCt2Monomial(-scale,&f); 
	      AddVariable2Monomial(NFUN,re2,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);
	      break;
	      
	    case COUPLE_FORCE:
	       if ((GetLinkForceModel(l1)==NO_FORCE)||
		  (GetLinkForceModel(l2)==NO_FORCE))
		Error("Can not couple the forces of links without force model");
	       
	      AddVariable2Monomial(NFUN,f1,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      AddCt2Monomial(-scale,&f); 
	      AddVariable2Monomial(NFUN,f2,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);
	      break;
	    default:
	      Error("Unknow type of couple in WorldCoupleTensegrityVariable");
	    }
	  
	  SetEquationCmp(EQU,&eq);
	  SetEquationValue(0,&eq);
	  SetEquationType(SYSTEM_EQ,&eq);
	  
	  AddEquation2CS(p,&eq,&(w->kinCS));
	  DeleteEquation(&eq);
	}
    }
}

void GenerateWorldSingularityEquations(Tparameters *p,char *ln,TCuikSystem *cs,Tworld *w)
{
  unsigned int i,rep;

  if (w->stage!=WORLD_DEFINED)
    GenerateWorldEquations(p,NULL,NULL,w); /* Generate kin equations only */
  
  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  if (rep==REP_JOINTS)
    Error("GenerateWorldSingularityEquations is not defined for DOF-based representations");

  CopyCuikSystem(cs,&(w->kinCS));

  for(i=0;i<w->nj;i++)
    GenerateJointRangeSingularityEquations(p,cs,GetMechanismJoint(i,&(w->m)));

  if (ln!=NULL)
    {
      unsigned int lk;

      lk=GetMechanismLinkID(ln,&(w->m));
      if (lk!=NO_UINT)
	{
	  Tequation eq;
	  char *vname;
	  Tlink *l;
	  char *lname;
	  Tinterval rangeInf;
	  Tvariable var;
	  Tmonomial f;
	  unsigned int vID;
	  
	  l=GetMechanismLink(lk,&(w->m));
	  lname=GetLinkName(l); 
	  NEW(vname,strlen(lname)+100,char);
	  NewInterval(-w->maxCoord,w->maxCoord,&rangeInf);
	  InitMonomial(&f);

	  for(i=0;i<3;i++)
	    {
	      CopyEquation(&eq,GetEquation(lk*3+i,&(w->refEqs)));

	      LINK_TRANS(vname,lname,i); 

	      NewVariable(CARTESIAN_VAR,vname,&var);
	      SetVariableInterval(&rangeInf,&var);
	      vID=AddVariable2CS(&var,cs);
	      DeleteVariable(&var);

	      AddCt2Monomial(-1.0,&f);
	      AddVariable2Monomial(NFUN,vID,1,&f);
	      AddMonomial(&f,&eq);
	      ResetMonomial(&f);

	      SetEquationType(COORD_EQ,&eq);

	      AddEquation2CS(p,&eq,cs);

	      DeleteEquation(&eq);
	    }
	  free(vname);
	  DeleteMonomial(&f);
	}
    }
}
void GenerateWorldTWSEquations(Tparameters *p,char *ln,TCuikSystem *cs,Tworld *w)
{
  unsigned int i,nv,vID;
  boolean *selectedVars;
  char *vname;

  GenerateWorldSingularityEquations(p,ln,cs,w);

  nv=GetCSNumVariables(cs);
  NEW(selectedVars,nv,boolean);

  /*in principle all variables are to be used in the Jacobian*/
  for(i=0;i<nv;i++)
    selectedVars[i]=TRUE; 

  /*but we exclude those for translation*/
  NEW(vname,strlen(ln)+100,char);
  for(i=0;i<3;i++)
    {
      LINK_TRANS(vname,ln,i);

      vID=GetCSVariableID(vname,cs);
      if (vID==NO_UINT)
	Error("Translation variable is not included in the cuiksystem (in GenerateWorldTWSEquations)");
      selectedVars[vID]=FALSE;
    }
 
  AddSimplifiedJacobianEquations(p,selectedVars,cs);

  free(selectedVars);
  free(vname);
}

inline void GetWorldJacobian(TJacobian *J,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in GetWorldKinJacobian");

  GetCSJacobian(J,&(w->kinCS));
}

inline void GetWorldSimpJacobian(Tparameters *p,TJacobian *J,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in GetWorldKinJacobian");

  GetSimpCSJacobian(p,J,&(w->kinCS));
}

inline boolean GetWorldSimpNJacobian(Tparameters *p,TNJacobian *nJ,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in GetWorldSimpNJacobian");

  return(GetSimpCSNJacobian(p,nJ,&(w->kinCS)));
}

inline boolean GetWorldSimpNHessian(Tparameters *p,TJacobian *sJ,TNHessian *nH,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in GetWorldSimpNHessian");

  return(GetSimpCSNHessian(p,sJ,nH,&(w->kinCS)));
}

inline unsigned int GetWorldSimpTopology(Tparameters *p,
					 unsigned int **t,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in GetWorldSimpTopology"); 
  
  return(GetSimpCSTopology(p,t,&(w->kinCS)));
}

inline unsigned int GetWorldTopology(Tparameters *p,
				     unsigned int **t,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in GetWorldTopology"); 
  
  return(GetCSTopology(p,t,&(w->kinCS)));
}

unsigned int WorldDOFTopology(unsigned int **t,Tworld *w)
{
  unsigned int i;
  Tjoint *j;

  NEW(*t,w->ndof,unsigned int);
  for(i=0;i<w->ndof;i++)
    {
      if (w->dof2joint[i]==NO_UINT)
	{
	  /* Link parameters are all real */
	  (*t)[i]=TOPOLOGY_R;
	}
      else
	{
	  j=GetMechanismJoint(w->dof2joint[i],&(w->m));
	  (*t)[i]=GetJointRangeTopology(w->dof2range[i],j);
	}
    }
  return(w->ndof);
}

inline unsigned int WorldSimpCuikNewton(Tparameters *p,double *pt,Tworld *w)
{
  return(CuikNewtonSimp(p,pt,&(w->kinCS)));
}

inline void EvaluateWorldJacobian(double *pt,double ***J,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");
  
  EvaluateCSJacobian(pt,J,&(w->kinCS));
}

inline void WorldEvaluateEquations(double *pt,double *r,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");
  
  EvaluateCSEquations(pt,r,&(w->kinCS));
}

inline boolean WorldInequalitiesHold(double *pt,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldInequalitiesHold");

  return(InequalitiesHoldOnPoint(pt,&(w->kinCS)));
}

inline boolean WorldSimpInequalitiesHold(Tparameters *p,double *pt,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldInequalitiesHold");

  return(SimpInequalitiesHoldOnPoint(p,pt,&(w->kinCS)));
}

inline double WorldErrorInSimpInequalities(Tparameters *p,double *pt,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldErrorInSimpInequalities");

  return(ErrorInSimpInequalitiesOnPoint(p,pt,&(w->kinCS)));
}

inline void WorldEvaluateSimpEquations(Tparameters *p,double *pt,double *r,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldEvaluateSimpEquations");
  
  EvaluateSimpCSEquations(p,pt,r,&(w->kinCS));
}

inline void WorldEvaluateSubSetSimpEquations(Tparameters *p,boolean *se,double *pt,double *r,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldEvaluateSubSetSimpEquations");
  
  EvaluateSubSetSimpCSEquations(p,se,pt,r,&(w->kinCS));
}

double WorldErrorInEquations(Tparameters *pr,double *pt,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldErrorInEquations");
  
  return(ErrorInCSEquations(pr,pt,&(w->kinCS)));
}

inline double WorldErrorInSimpEquations(Tparameters *p,double *pt,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in WorldErrorInSimpEquations");
  
  return(ErrorInSimpCSEquations(p,pt,&(w->kinCS)));
}

double WorldErrorFromDOFs(Tparameters *p,double *dof,Tworld *w)
{
  double e,*v;

  WorldDOF2Sol(p,dof,&v,NULL,w);
  e=WorldErrorInEquations(p,v,w);
  free(v);

  return(e);
}

inline double EvaluateWorldCost(Tparameters *p,boolean simp,double *pt,void *w)
{
  if (((Tworld *)w)->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldCost");
  
  return(EvaluateCSCost(p,simp,pt,(void *)&(((Tworld *)w)->kinCS)));
}

unsigned int GetWorldNumVariables(Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");
  
  return(GetCSNumVariables(&(w->kinCS)));
}

inline unsigned int GetWorldNumSystemVariables(Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");
  
  return(GetCSNumSystemVariables(&(w->kinCS)));
}

inline unsigned int RegenerateWorldOriginalPoint(Tparameters *p,double *s,
						 double **o,Tworld *w)
{
  unsigned int nv,r;

  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    {
      /* in JOINTS all variables are system variables. Just unsimplify */
      nv=RegenerateOriginalPoint(p,s,o,&(w->kinCS));
    }
  else
    {
      /* Revover the original system variables and some of the dummies  */
      nv=RegenerateOriginalPoint(p,s,o,&(w->kinCS));

      /* Some dummy variables that only appear in dummy equations are 
	 not present in the simplified system and their value can not be
	 determined using 'RegenerateOriginalPoint'. We have to use the
	 semantic of the variables to recover their value. */
      RegenerateMechanismSolution(p,&(w->kinCS),*o,&(w->m));
    }
  return(nv);
}

unsigned int RegenerateWorldOriginalSystemPoint(Tparameters *p,double *s,
						double **o,Tworld *w)
{
  double *oAll;
  unsigned int ns,nAll,i,k;

  /* Solution point with all the variables */
  nAll=RegenerateWorldOriginalPoint(p,s,&oAll,w);

  /* Now select the system variables */
  ns=GetCSNumSystemVariables(&(w->kinCS));
  NEW(*o,ns,double);

  k=0;
  for(i=0;i<nAll;i++)
    {
      /*The input box only has values for the input variables*/
      if (w->systemVars[i])
	{
	  (*o)[k]=oAll[i];
	  k++;
	}
    }

  free(oAll);
  return(ns);
}

inline unsigned int WorldGenerateSimplifiedPoint(Tparameters *p,double *o,double **s,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");

  return(GenerateSimplifiedPoint(p,o,s,&(w->kinCS)));
}

unsigned int WorldGenerateSimplifiedPointFromSystem(Tparameters *p,double *o,double **s,Tworld *w)
{
  unsigned int ns;
  double *oAll;
  
  if (w->stage!=WORLD_DEFINED)
    Error("World without equations in EvaluateWorldKinJacobian");
  
  /* get dummy/force vars (i.e. non-system vars) not in the input */
  RegenerateWorldSolutionPoint(p,o,&oAll,w);
  
  ns=GenerateSimplifiedPoint(p,oAll,s,&(w->kinCS));

  free(oAll);

  return(ns);
}

inline void GetWorldInitialBox(Tbox *b,Tworld *w)
{
   if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  GenerateInitialBox(b,&(w->kinCS)); 
}

inline void GetWorldSimpInitialBox(Tparameters *p,Tbox *b,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  GenerateSimpInitialBox(p,b,&(w->kinCS)); 
}

unsigned int WorldManifoldDimension(Tparameters *p,double *point,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");
  
  return(ManifoldDimension(p,point,&(w->kinCS)));
}

unsigned int MaxWorldReduction(Tparameters *p,Tbox *b,double *reduction,Tworld *w)
{ 
  unsigned int s;
  
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");
  
  #if ((!_USE_MPI)&&(_DEBUG==1)) 
  {
    double sizeIn;
    
    sizeIn=GetBoxSize(w->systemVars,b);
    printf("            Kin <s:%g,l:%u>-> ",sizeIn,GetBoxLevel(b));
  }
  #endif

  s=MaxReduction(p,SYSTEM_VAR,reduction,b,&(w->kinCS));
  /*
    s can be EMPTY_BOX
             REDUCED_BOX
             REDUCED_BOX_WITH_SOLUTION
             ERROR_IN_PROCESS
  */
  
  #if ((!_USE_MPI)&&(_DEBUG==1))
    if (s==EMPTY_BOX)
      printf("e\n");
    else
      {
	double sizeOut;

	sizeOut=GetBoxSize(w->systemVars,b);
	printf("%g (s:%g)\n",*reduction,sizeOut);
      }
    fflush(stdout);
  #endif

  return(s);
}

void PlotWorld(Tparameters *pr,Tplot3d *pt,double axesLength,Tworld *w)
{
  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  /* We init the collision detection to be able to print
     collision information when moving the world */
  if (w->wcd==NULL)
    InitWorldCD(pr,1,w);

  Start3dBlock(pt);
    PlotEnvironment(pt,&(w->e));
    PlotMechanism(pt,axesLength,&(w->m));
  Close3dBlock(pt);
}

unsigned int RegenerateWorldSolutionPoint(Tparameters*pr,double *p,double **v,Tworld *w)
{
  unsigned int i,n,k;

  if (w->stage!=WORLD_DEFINED)
   Error("The equations and variables are not yet defined");

  n=GetCSNumVariables(&(w->kinCS));
  NEW(*v,n,double);

  k=0;
  for(i=0;i<n;i++)
    {
      /*The input box only has values for the input variables*/
      if (w->systemVars[i])
	{
	  (*v)[i]=p[k];
	  k++;
	}
      else
	(*v)[i]=0.0; /*Non system variables are set to 0. See below! */
    }

  RegenerateMechanismSolution(pr,&(w->kinCS),*v,&(w->m));
  
  return(n);
}

void WorldPrintAtoms(Tparameters *pr,FILE *f,double *pt,Tworld *w)
{  
  THTransform *tl;
  TLinkConf *def;

  if (GetEnvironmentNObstacles(&(w->e)))
    Warning("The bodies in the environment would not be considered");

  GetLinkTransformsFromSolutionPoint(pr,FALSE,pt,&tl,&def,w);
 
  MechanismPrintAtoms(f,tl,&(w->m));

  DeleteLinkTransforms(tl,def,w);
}

void WorldStoreRigidGroups(Tparameters *pr,FILE *f,double *pt,Tworld *w)
{  
  THTransform *tl;
  TLinkConf *def;

  if (GetEnvironmentNObstacles(&(w->e)))
    Warning("The bodies in the environment would not be considered");

  GetLinkTransformsFromSolutionPoint(pr,FALSE,pt,&tl,&def,w);

  MechanismStoreRigidAtoms(f,tl,&(w->m));

  DeleteLinkTransforms(tl,def,w);
}

void WorldAtomJacobian(Tparameters *pr,double *sol,unsigned int *nr,unsigned int *nc,double ***J,Tworld *w)
{
  double *a;
  unsigned int ta,*na,nb;
  unsigned int i,j,k,r;
  Tlink *l;
  Tpolyhedron *b;
  
  if (!IsMechanismAllSpheres(&(w->m)))
    Error("The world is not sphere-only (WorldAtomJacobian)");

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
  if (r!=REP_JOINTS)
    Error("WorldAtomJacobian is only defined for JOINT-based representations");

  /* Count the number of atoms (total and per link) */
  NEW(na,w->nl,unsigned int); /* number of atoms per link */
  ta=0;
  for(i=0;i<w->nl;i++)
    {
      l=GetMechanismLink(i,&(w->m));
      na[i]=0;
      if (GetLinkType(l)!=LINK_Connect)
	{
	  nb=LinkNBodies(l);
	  for(j=0;j<nb;j++)
	    {
	      b=GetLinkBody(j,l);
	      if (GetPolyhedronType(b)==SPHERE)
		na[i]++;
	    }
	}
      ta+=na[i];
    }

  /* Get the coordinates for each atom */
  NEW(a,3*ta,double); /* coordinates for each atom */
  k=0;
  for(i=0;i<w->nl;i++)
    {
      l=GetMechanismLink(i,&(w->m));
      if (GetLinkType(l)!=LINK_Connect)
	{
	  nb=LinkNBodies(l);
	  for(j=0;j<nb;j++)
	    {
	      b=GetLinkBody(j,l);
	      if (GetPolyhedronType(b)==SPHERE)
		{
		  GetPolyhedronCenter(&(a[k]),b);
		  k+=3;
		}
	    }
	}
    }
  
  EvaluateJacobianXVectors(sol,ta,w->nl,na,a,nr,nc,J,&(w->refEqsJ));

  free(a);
}

void MoveWorld(Tparameters *pr,Tplot3d *pt,Tbox *b,Tworld *w)
{
  unsigned int n,r;
  double *v;

  if (w->stage!=WORLD_DEFINED)
   Error("The equations and variables are not yet defined");

  if (GetCSNumSystemVariables(&(w->kinCS))<GetBoxNIntervals(b))
    Warning("System-solution dimension missmatch in MoveWorld (using only the first values in the solution)");

  if (GetCSNumSystemVariables(&(w->kinCS))>GetBoxNIntervals(b))
    Error("Not enough values in the solution (using a different REPRESENTATION parameter?)");


  r=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
  if (r==REP_JOINTS)
    {
      /* In dof repre. all variables are system variables */
      n=GetCSNumVariables(&(w->kinCS));
      NEW(v,n,double);
      
      GetBoxCenter(NULL,v,b);
      MoveWorldDOF(pr,pt,v,w);
    }
  else
    {
      THTransform *tl;
      TLinkConf *def;
      double *vSystem;

      n=GetBoxNIntervals(b);
      NEW(vSystem,n,double);
      GetBoxCenter(NULL,vSystem,b);

      /* obtain the non-system variables form the system ones */
      RegenerateWorldSolutionPoint(pr,vSystem,&v,w);

      GetLinkTransformsFromSolution(pr,v,&tl,&def,w);

      if (MoveAndCheckCDFromTransforms(TRUE,0,tl,def,NULL,NULL,w)) 
	fprintf(stderr,"  Configuration is in collision\n"); 
      else 
	fprintf(stderr,"  Configuration is NOT in collision\n"); 
   
      fprintf(stderr,"  Configuration error: %g\n",WorldErrorInEquations(pr,v,w));

      MoveMechanismFromTransforms(pr,pt,tl,def,&(w->m));

      DeleteLinkTransforms(tl,def,w);
      free(vSystem);
    }
  free(v);
      
}

void PrintWorldAxes(Tparameters *pr,FILE *f,Tbox *b,Tworld *w)
{
  unsigned int i,n;
  double *r;
  double *v,*vSystem;
  Tjoint *j;
  unsigned int rep;

  if (w->stage!=WORLD_DEFINED)
   Error("The equations and variables are not yet defined");

  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,pr));
  if (rep==REP_JOINTS)
    Error("PrintWorldAxes is not defined for JOINT-based representations");

  n=GetBoxNIntervals(b);
  NEW(vSystem,n,double);
  GetBoxCenter(NULL,vSystem,b);
   
  /* obtain the non-system variables form the system ones */
  RegenerateWorldSolutionPoint(pr,vSystem,&v,w);

  NEW(r,w->nl*3,double);
  EvaluateEqualityEquations(FALSE,v,r,&(w->refEqs));

  for(i=0;i<w->nj;i++)
    {
      j=GetMechanismJoint(i,&(w->m));
      PrintJointAxes(pr,f,&(w->kinCS),v,r,j);
    }
  fprintf(f,"\n");

  free(r);

  free(v);
}

void PrintWorldCollisionInfo(FILE *f,char *fname,Tworld *w)
{
  if (w->wcd!=NULL)
    StoreCollisionInfo(f,fname,w->endEffector,&(w->m),w->wcd);
}

void MoveWorldDOF(Tparameters *pr,Tplot3d *pt,double *dof,Tworld *w)
{
  THTransform *tl;
  TLinkConf *def;
  double *sample;

  if (w->stage!=WORLD_DEFINED)
   Error("The equations and variables are not yet defined");

  GetLinkTransformsFromDOF(dof,&tl,&def,w);
  
  if (MoveAndCheckCDFromTransforms(TRUE,0,tl,def,NULL,NULL,w)) 
    {
      fprintf(stderr,"  Configuration is in collision\n"); 
      //PrintCollisionInfo(tl,&(w->m),&(w->e),w->wcd);
    }
  else 
    fprintf(stderr,"  Configuration is NOT in collision\n"); 

  WorldDOF2Sol(pr,dof,&sample,NULL,w);
  fprintf(stderr,"  Configuration error: %g\n",WorldErrorInEquations(pr,sample,w));
  free(sample);

  MoveMechanismFromTransforms(pr,pt,tl,def,&(w->m));

  DeleteLinkTransforms(tl,def,w);
}

unsigned int WorldDOF2Sol(Tparameters *p,double *dof,double **sol,Tbox *b,Tworld *w)
{
  unsigned int r,i,n;
  Tjoint *j;

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  /* Ensure that the input dofs are in correct range */
  for(i=0;i<w->ndof;i++)
    {
      /* only joint dof can have topology_s */
      if (w->dof2joint[i]!=NO_UINT)
	{
	  j=GetMechanismJoint(w->dof2joint[i],&(w->m));
	  if (GetJointRangeTopology(w->dof2range[i],j)==TOPOLOGY_S)
	    PI2PI(dof[i]);
	}
    }
  
  n=GetCSNumVariables(&(w->kinCS));
  NEW(*sol,n,double);
  for(i=0;i<n;i++)
    (*sol)[i]=INF;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  if (r==REP_JOINTS)
    /* in dof all variables are system variables */
    memcpy(*sol,dof,n*sizeof(double));
  else
    {
      unsigned int k,l1,l2;
      THTransform *tl;
      TLinkConf *def;
      Tjoint *j;
      Tlink *l;

      GetLinkTransformsFromDOF(dof,&tl,&def,w);
      
      for(i=0;i<w->nl;i++)
	{
	  l=GetMechanismLink(i,&(w->m));
	  /* no need to pass 'dof' to GenerateLinkSolution since the relevant dof 
	     are already stored in 'def' */
	  GenerateLinkSolution(p,&(tl[i]),&(def[i]),&(w->kinCS),*sol,IsGroundLink(i),l);
	  if (w->openLink[i])
	    {
	      /* Some links are at the end of an open chain of links (i.e., the
		 mechanism is not fully composed by closed chains). In this case
		 the system includes variables to represent the end position (x,y,z)
		 of those links. Here we define the value for these variables from
		 the translation part of the corresponding link transform. */
	      char *vname,*ln;
	      unsigned int vID;

	      ln=GetLinkName(l); 
	      NEW(vname,strlen(ln)+100,char);

	      for(k=0;k<3;k++)
		{
		  LINK_TRANS(vname,ln,k);
 
		  vID=GetCSVariableID(vname,&(w->kinCS));
		  if (vID==NO_UINT)
		    Error("Undefined reference variable in WorldDOF2Sol");

		  (*sol)[vID]=HTransformGetElement(k,AXIS_H,&(tl[i]));
		}
	      free(vname);
	    }
	}

      for(i=0;i<w->nj;i++)
	{ 
	  j=GetMechanismJoint(i,&(w->m));
	  l1=JointFromID(j);
	  l2=JointToID(j);
	  GenerateJointSolution(p,&(dof[w->joint2dof[i]]),
				&(tl[l1]),&(tl[l2]),
				&(w->kinCS),*sol,j);
	}

      DeleteLinkTransforms(tl,def,w);
    }

  if (b!=NULL)
    InitBoxFromPoint(n,*sol,b);

  return(n);
}

void WorldSample2DOF(Tparameters *p,double *sample,double *dof,Tworld *w)
{
  unsigned int r ;

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));
  
  if (r==REP_JOINTS)
    {
      /* In JOINTS all variables are system variables */
      memcpy(dof,sample,sizeof(double)*w->ndof);
    }
  else
    {
      THTransform *tl;
      TLinkConf *def;
      double *v;

      /* Wee need a complete solution, not only one with system variables */
      RegenerateWorldSolutionPoint(p,sample,&v,w);
      
      /* Get a transform giving the absolute pose for each link using 
	 the full solution point. */
      GetLinkTransformsFromSolution(p,v,&tl,&def,w); 
      
      free(v);
      
      /* Obtain the joint variables from the link absolute poses and the
         link configuration */
      GetMechanismDOFsFromTransforms(p,tl,def,dof,&(w->m));
      
      DeleteLinkTransforms(tl,def,w);
    }
}

void AnimateWorld(Tparameters *pr,char *pname,double axesLength,
		  double frameDelay,Tlist *p,Tworld *w)
{
  Tplot3d p3d;
  boolean start;
  Titerator it;

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  if (axesLength<0) axesLength=0;

  if (frameDelay<0) frameDelay=0;
  
  InitPlot3d(pname,FALSE,0,NULL,&p3d);
  
  Start3dBlock(&p3d);
  Delay3dObject(INITIAL_FRAME_DELAY,&p3d);

  PlotWorld(pr,&p3d,axesLength,w);

  InitIterator(&it,p);
  First(&it);

  if (GetBoxNIntervals((Tbox *)GetCurrent(&it))<GetCSNumNonDummyVariables(&(w->kinCS)))
    Error("The input boxes does not have enough number of variables");

  start=TRUE;
  while(!EndOfList(&it))
    {
      MoveWorld(pr,&p3d,(Tbox *)GetCurrent(&it),w);
      if (start) 
	{
	  Close3dBlock(&p3d);
	  LookPlot3d(&p3d);
	  start=FALSE;
	}
      Delay3dObject(FRAME_RATE+frameDelay,&p3d);

      Advance(&it);
    }
  Delay3dObject(FINAL_FRAME_DELAY,&p3d);
  ClosePlot3d(TRUE,&p3d); /*TRUE -> quit geomview after the animation*/
}

void PrintWorldCS(Tparameters *p,char *fname,Tworld *w)
{
  Tfilename fout;
  FILE *f;

  if (w->stage!=WORLD_DEFINED)
    Error("The equations and variables are not yet defined");

  CreateFileName(NULL,fname,NULL,CUIK_EXT,&fout);
  f=fopen(GetFileFullName(&fout),"w");
  if (!f) Error("Could not open file in PrintWorldCS");
  #if (_DEBUG>0)
    printf("Generating cuik file              : %s\n",GetFileFullName(&fout));
  #endif

  fprintf(f,"%% Kinematic equations\n");
  PrintCuikSystem(p,f,&(w->kinCS));
  fclose(f);
  DeleteFileName(&fout);
}

void PrintWorld(char *fname,int argc,char **arg,Tworld *w)
{
  Tfilename fworld;
  FILE *f;
  time_t t;
  char hostname[50];

  CreateFileName(NULL,fname,NULL,WORLD_EXT,&fworld);
  fprintf(stderr,"Writing world to                  : %s\n",GetFileFullName(&fworld));
 
  f=fopen(GetFileFullName(&fworld),"w");
  if (!f)
    Error("Could not open the file to store the world");

  /* Do not document the link/joint/obstacle definitions. */
  fprintf(f,"/** \\cond */\n\n");

  PrintMechanism(f,GetFilePath(&fworld),GetFileName(&fworld),&(w->m));

  PrintEnvironment(f,GetFilePath(&fworld),&(w->e));

  /* Print the collision information */
  PrintCollisions(f,w);

  /* Autognerated documentation to avoid errors when generating the documentation. */
  fprintf(f,"/** \\endcond */\n");
  fprintf(f,"/**\n");
  fprintf(f,"   \\file %s.%s\n\n",GetFileName(&fworld),GetFileExtension(&fworld));
  fprintf(f,"   \\brief Automatically generated world file.\n\n");
  if ((argc>0)&&(arg!=NULL))
    {
      unsigned int i;

      fprintf(f,"   Automatically generated world file with the command:\n\n      - ");
      for(i=0;i<(unsigned int)argc;i++)
	fprintf(f,"%s ",arg[i]);
      fprintf(f,"\n      .\n\n");
    }
  else
    fprintf(f,"   Automatically generated world file.\n");
  t=time(NULL);
  gethostname(hostname,50);
  fprintf(f,"   Created on: %s   Executed at: %s\n",ctime(&t),hostname);
  fprintf(f,"*/\n");

  fclose(f);

  DeleteFileName(&fworld);
}

void DeleteWorld(Tworld *w)
{
  DeleteEnvironment(&(w->e));
  DeleteMechanism(&(w->m));
  DeleteWorldCollisionInfo(w);
  DeleteWorldCD(w);

  /* if GenerateWorldEquationSystems was called */
  if (w->stage==WORLD_DEFINED)
    DeleteWorldCS(w);
}
