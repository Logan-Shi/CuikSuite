#include "rrt.h"

#include "defines.h"
#include "algebra.h"
#include "random.h"
#include "samples.h"
#include "filename.h"

#include <string.h>
#include <math.h>

/** 
   \file rrt.c
   \brief Implementation of the RRT functions.

   Implements the functions defining a RRT on a variety.

   \sa Trrt,rrt.h
*/


/** 
    \brief New branch creation.

    To be called everty time we start a new RRT branch.

    \param rst The RRT statistics to modify.
*/
void NewRRTBranch(TRRTStatistics *rst);

/** 
    \brief New no empty branch.

    To be called every time we managed to add a non-emtpy branch
    to the RRT.

    \param rst The RRT statistics to modify.
*/
void NewRRTNoEmptyBranch(TRRTStatistics *rst);

/** 
    \brief New attempt to connect the two trees.

    New attempt to connect the two trees. This is only updated
    in bi-directional  RRTs.

    \param rst The RRT statistics to modify.
*/
void NewRRTTreeConnection(TRRTStatistics *rst);

/** 
    \brief New non-void attempt to connect the two trees.

    New attempt to connect the two trees that resulted in a
    non empty branch. This is only updated
    in bi-directional  RRTs.

    \param rst The RRT statistics to modify.
*/
void NewRRTNoEmptyTreeConnection(TRRTStatistics *rst);

/** 
    \brief New step in branch extension.

    To be called everytime we add a new step to a branch.

    \param rst The RRT statistics to modify.
*/
void NewRRTStep(TRRTStatistics *rst);

/** 
    \brief New distance to q_rand.

    New distance from q_rand to the tree. These distances are
    accumulated and then we compute the average using the number
    of attempts for branch extension.

    \param dqr New tree-q_rand distance.
    \param rst The RRT statistics to modify.
*/
void NewRRTDistanceQrand(double dqr,TRRTStatistics *rst);

/** 
   \brief Random sample reached.

   To be called every time the random sample is reached.

   \param rst The RRT statistics to modify.
*/
void NewRRTQrandReached(TRRTStatistics *rst);

/** 
   \brief Convergence error.

   Error converging to the manifold.

   \param rst The RRT statistics to modify.
*/
void NewRRTConvergenceError(TRRTStatistics *rst);

/** 
   \brief A high cost configuration is reached.

   A high cost configuration is reached. Only possible
   in transition-based RRTs.

   \param rst The RRT statistics to modify.
*/
void NewRRTHighCost(TRRTStatistics *rst);

/** 
   \brief The branch leaves the domain.

   The branch extension is stopped because it leves the problem domain.

   \param rst The RRT statistics to modify.
*/
void NewRRTOutOfDomain(TRRTStatistics *rst);

/** 
   \brief The distance to q_rand increase.

   The branch extension is stopped because the distance to q_rand increases.

   \param rst The RRT statistics to modify.
*/
void NewRRTDistanceIncreases(TRRTStatistics *rst);

/** 
   \brief New collision.

   To be called every time a branch extension is stopped
   due to a collision.

   \param rst The RRT statistics to modify.
*/
void NewRRTCollision(TRRTStatistics *rst);

/** 
   \brief New large step.

   To be called every time a branch extension is stopped
   if a sample that is too far from the previous sample.

   \param rst The RRT statistics to modify.
*/
void NewRRTTooFar(TRRTStatistics *rst);

/** 
   \brief New stalled branch.

   To be called every time a branch extension is stalled
   (it grows but too slow).

   \param rst The RRT statistics to modify.
*/
void NewRRTStalled(TRRTStatistics *rst);

/** 
    \brief New sample.

    To be called every time we actually add a node (or sample)
    to the RRT.

    \param rst The RRT statistics to modify.
*/
void NewRRTSample(TRRTStatistics *rst);

/** 
    \brief New random sample.

    Counts the number of random samples generated.
*/
void NewRRTRandomSample(TRRTStatistics *rst);

/** 
   \brief New sample rejection.

   Counts the number os random samples rejected.
*/
void NewRRTSampleRejection(TRRTStatistics *rst);

/** 
   \brief New collision check.

   New collision check.
*/
void NewRRTCollisionCheck(TRRTStatistics *rst);


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void InitRRTStatistics(TRRTStatistics *rst)
{
  if (rst!=NULL)
    {
      rst->n=0;

      rst->nBranch=0;
      rst->nNoEmptyBranch=0;

      rst->nTreeConnection=0;
      rst->nNoEmptyTreeConnection=0;

      rst->nStep=0;
      rst->dQrand=0.0;

      rst->nQrandReached=0;
      rst->nConvergenceError=0;
      rst->nHighCost=0;
      rst->nOutOfDomain=0;
      rst->nDistanceIncreases=0;
      rst->nCollision=0;
      rst->nTooFar=0;
      rst->nStalled=0;

      rst->nSample=0;

      rst->nRandom=0;
      rst->nRejections=0;

      rst->nCollisionChecks=0;
    }
}

void NewRRTBranch(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nBranch++;
}

void NewRRTNoEmptyBranch(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nNoEmptyBranch++;
}

void NewRRTTreeConnection(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nTreeConnection++;
}

void NewRRTNoEmptyTreeConnection(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nNoEmptyTreeConnection++;
}

void NewRRTDistanceQrand(double dqr,TRRTStatistics *rst)
{
  if (rst!=NULL) rst->dQrand+=dqr;
}

void NewRRTStep(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nStep++;
}

void NewRRTQrandReached(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nQrandReached++;
}

void NewRRTConvergenceError(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nConvergenceError++;
}

void NewRRTHighCost(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nHighCost++;
}

void NewRRTOutOfDomain(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nOutOfDomain++;
}

void NewRRTDistanceIncreases(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nDistanceIncreases++;
}

void NewRRTCollision(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nCollision++;
}

void NewRRTTooFar(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nTooFar++;
}

void NewRRTStalled(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nStalled++;
}

void NewRRTSample(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nSample++;
}

void NewRRTRandomSample(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nRandom++;
}

void NewRRTSampleRejection(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nRejections++;
}

void NewRRTCollisionCheck(TRRTStatistics *rst)
{
  if (rst!=NULL) rst->nCollisionChecks++;
}

void AccumulateRRTStatistics(TRRTStatistics *rst1,TRRTStatistics *rst2)
{
  if ((rst1!=NULL)&&(rst2!=NULL))
    {
      if (rst1->n==0)
	rst2->n++;
      else
	rst2->n+=rst1->n;

      rst2->nBranch+=rst1->nBranch;
      rst2->nNoEmptyBranch+=rst1->nNoEmptyBranch;

      rst2->nTreeConnection+=rst1->nTreeConnection;
      rst2->nNoEmptyTreeConnection+=rst1->nNoEmptyTreeConnection;

      rst2->nStep+=rst1->nStep;
      rst2->dQrand+=rst1->dQrand;

      rst2->nQrandReached+=rst1->nQrandReached;
      rst2->nOutOfDomain+=rst1->nOutOfDomain;
      rst2->nDistanceIncreases+=rst1->nDistanceIncreases;
      rst2->nCollision+=rst1->nCollision;
      rst2->nTooFar+=rst1->nTooFar;
      rst2->nStalled+=rst1->nStalled;

      rst2->nSample+=rst1->nSample;

      rst2->nRandom+=rst1->nRandom;
      rst2->nRejections+=rst1->nRejections;

      rst2->nCollisionChecks+=rst1->nCollisionChecks;
    }
}

void PrintRRTStatistics(Trrt *rrt,TRRTStatistics *rst)
{
  if (rst!=NULL)
    {
      unsigned int m,nExt;

      if (rst->n==0)
	rst->n=1;

      nExt=rst->nBranch+rst->nTreeConnection;

      fprintf(stderr,"%% **************************************************\n");
      if (rst->n>1)
	fprintf(stderr,"RRT Statistics (averaged over %u repetitions)\n",rst->n);
      else
	fprintf(stderr,"RRT Statistics\n\n");
      fprintf(stderr,"  Num. random samples             : %.2f\n",
	      (double)rst->nRandom/(double)rst->n);
      fprintf(stderr,"  Num. rejected random samples    : %.2f (%.2f)\n",
	      (double)rst->nRejections/(double)rst->n,
	      (double)rst->nRejections/(double)rst->nRandom);
      fprintf(stderr,"  Num. accepted random samples    : %.2f (%.2f)\n",
	      (double)(rst->nRandom-rst->nRejections)/(double)rst->n,
	      (double)(rst->nRandom-rst->nRejections)/(double)rst->nRandom);

      if ((rst->n==1)&&(rrt!=NULL)&&(DynamicDomainRRT(rrt)))
	{
	  unsigned int i,n;
	  double miDD,maDD,avDD,r;

	  miDD=+INF;
	  maDD=-INF;
	  avDD=0.0;
	  n=0;
	  for(i=0;i<rrt->ns;i++)
	    {
	      r=GetDynamicDomainRadius(i,rrt);
	      if (r>0)
		{
		  if (r<miDD)
		    miDD=r;
		  if (r>maDD)
		    maDD=r;
		  avDD+=r;
		  n++;
		}
	    }
	  if (n==0)
	    fprintf(stderr,"  No dynamic domain effect.");
	  else
	    fprintf(stderr,"  Dynamic domain radius           : %.2f <-- %.2f --> %.2f (%u/%u)\n",
		    miDD,avDD/(double)n,maDD,n,rrt->ns);
	}
      fprintf(stderr,"  Average  distance to Qrand      : %.2f\n",
	      rst->dQrand/(double)rst->nBranch);

      if (rst->nTreeConnection>0)
	{
	  fprintf(stderr,"  Num. direct RRT extensions      : %.2f\n",
		  (double)rst->nBranch/(double)rst->n);

	  m=rst->nNoEmptyBranch;
	  fprintf(stderr,"  Num. no-empty direct extensions : %.2f (%.2f)\n",
		  (double)m/(double)rst->n,
		  (double)m/(double)rst->nBranch);

	  fprintf(stderr,"  Num. RRT connections            : %.2f\n",
		  (double)rst->nTreeConnection/(double)rst->n);
	  m=rst->nNoEmptyTreeConnection;
	  fprintf(stderr,"  Num. no-empty RRT connections   : %.2f (%.2f)\n",
		  (double)m/(double)rst->n,
		  (double)m/(double)rst->nTreeConnection);

	  fprintf(stderr,"  Total branches                  : %.2f\n",
		  (double)nExt/(double)rst->n);
	  m=(rst->nNoEmptyBranch+rst->nNoEmptyTreeConnection);
	  fprintf(stderr,"  Total no-empty branches         : %.2f (%.2f)\n",
		  (double)m/(double)rst->n,
		  (double)m/(double)nExt);
	}
      else
	{
	  fprintf(stderr,"  Total branches                  : %.2f\n",
		  (double)rst->nBranch/(double)rst->n);
	  m=rst->nNoEmptyBranch;
	  fprintf(stderr,"  Total no-empty branches         : %.2f (%.2f)\n",
		  (double)m/(double)rst->n,
		  (double)m/(double)rst->nBranch);
	}
      fprintf(stderr,"  Reasons to stop the branch/connection\n");
      m=rst->nQrandReached;
      fprintf(stderr,"    q_rand reached                : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nConvergenceError;
      fprintf(stderr,"    Convergence errors            : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nHighCost;
      fprintf(stderr,"    High cost configurations      : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nOutOfDomain;
      fprintf(stderr,"    Out of domain                 : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nDistanceIncreases;
      fprintf(stderr,"    Distance to q_rand increases  : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nCollision;
      fprintf(stderr,"    Collision                     : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nTooFar;
      fprintf(stderr,"    Too far from previous sample  : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);

      m=rst->nStalled;
      fprintf(stderr,"    Stalled branch                : %.2f (%.2f)\n",
	      (double)m/(double)rst->n,
	      (double)m/(double)nExt);


      fprintf(stderr,"  Num. extension steps            : %.2f\n",
	      (double)rst->nStep/(double)rst->n);
      fprintf(stderr,"    Num. steps per branch         : %.2f\n",
	      (double)rst->nStep/(double)nExt);

      fprintf(stderr,"  Num. collision checks           : %.2f\n",
	      (double)rst->nCollisionChecks/(double)rst->n);


      fprintf(stderr,"  Num. samples in (bi)RRT         : %.2f\n",
	      (double)rst->nSample/(double)rst->n);
      fprintf(stderr,"    Samples per non-empty extens. : %.2f\n",
	      (double)rst->nSample/(double)(rst->nNoEmptyBranch+rst->nNoEmptyTreeConnection));
    }
}

void DeleteRRTStatistics(TRRTStatistics *rst)
{
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


/** 
   \brief Initializes the topology array in the RRT.

   Initializes the topology array in the RRT.

   \param pr The set of parameters.
   \param rrt The RRT where to initialize the topology.
*/
void SetRRTTopology(Tparameters *pr,Trrt *rrt);

/** 
   \brief Extends a RRT as much as possible towards a given sample.

   As a single branch to the RRT with the purpose of reaching a given sample.

   The branch might include  many samples if many small steps are performed
   toward de targed.

   The extension proceeds as far as there is no collision, and the distance
   to the targed sample decreases.

   During the generation of the branch we check if the global goal is reached.

   \param pr The set of parameters.
   \param ccRRT TRUE if the branch extension has to use the ccRRT strategy proposed
                by Dallibart et at. and FALSE if it has to use the one by Berenson et at.
		(see \ref ccRRT and \ref cBiRRT). Note that typically, in the first case the
		thee is one-directional and in the second it is bidirectional (but this is
		not compulsatory).
   \param tree The current tree.
               Only considered in bidirectional RRTs. Otherwise all points are added
	       in the START2GOAL tree (the only one defined).
   \param i_near Index of the sample in the RRT from where to start the extension.
   \param q_rand The targed sample. This must be given in the simplefied system.
   \param goal Global goal for the RRT (also given in simplified form).
   \param lastSample Identifier of the last sample added along the new branch.
                     It will be i_near if the branch is empty.
   \param costF The cost Function used in TRRT. NULL for normal RRT exploration.
   \param costData The last parameter for the cost function.
   \param rst Statistics about the RRT construction. Only used if \ref GET_RRT_STATISTICS
              is set.
   \param rrt the RRT to extend.

   \return TRUE if the goal has been reached (sufficiently close) or if the
           maximum number of samples in the RRT have been reached.
*/
boolean AddBranchToRRT(Tparameters *pr,boolean ccRRT,
		       unsigned int tree,unsigned int i_near,
		       double *q_rand,double *goal,
		       unsigned int *lastSample,
		       double (*costF)(Tparameters*, boolean , double*, void*),
		       void *costData,
		       TRRTStatistics *rst,Trrt *rrt);

/** 
    \brief Defines a path from a vector of steps.

    Defines a path (a collection of close enough samples) from a set
    of steps defined as nodes in a RRT.

    \param pr The set of parameters.
    \param steps The vector of steps to follow.
    \param pl The length of the output path, if any. If no path is found.
              this is undefined.
    \param pc The cost of the output path, if any. If no path is found.
              this is undefined.
    \param ns Number of samples in the output path.
    \param path The output path.
    \param action Action to reach each state (if dynamics).
    \param time Time to reach each state (if dynamics).
    \param rrt The RRT structure to query.

    \return The size of each path step (system variables stored for each step).
*/
unsigned int Steps2PathinRRT(Tparameters *pr,Tvector *steps,double *pl,double* pc,
			     unsigned int *ns,double ***path,double ***action,double **time,
			     Trrt *rrt);

/** 
   \brief Path length from a sample to the root.

   Computes the length of the

   \param pr The set of parameteres.
   \param sID Sample to connect to the root of the tree.
   \param rrt The RRT structure to query.

   \return The length of the path.
*/
double RRTPathLength(Tparameters *pr,unsigned int sID,Trrt *rrt);

/** 
   \brief Extend strategy for the RRT.

   Extends a RRT adding a node from q_near to q_rand. This implements a RRT-Extend
   strategy while AddBranchToRRT implements a RRT-Connect.

   Right now this is only used for the RRT* but it could be used for other
   types of RRT without any problem.

   \param pr The set of parameters.
   \param i_near Index of the node in the tree from where to extend it.
   \param q_rand Node giving the direction to extend the tree.
   \param goal Global goal for the RRT. Set to NULL if goal detection is
               deactivated.
   \param i_goal Identifier of the goal sample in the RRT. NO_UINT while the
                 goal has not been reached.
		 This is an input/output parameter. Must be initialized to
		 NO_UINT before the first call to this function and it will
		 be updated inside it.
		 Only used if goal is not NULL.
   \param rst Statistics on the RRT construction process (only used if
              \ref GET_RRT_STATISTICS is set).
   \param rrt The RRT to extend.

   \return Identifier of the node added to the RRT.
*/
unsigned int AddStepToRRTstar(Tparameters *pr,unsigned int i_near,
			      double *q_rand,double *goal,
			      unsigned int *i_goal,
			      TRRTStatistics *rst,Trrt *rrt);
/** 
   \brief Wires a node to the RRT star.

   Selects the best parent among all neighbouring nodes for a node just
   added to the tree.

   \param pr The set of parameters.
   \param id_new Identifier of the last node added to the tree.
   \param i_near Parent of the node just added to the tree.
   \param gamma Radius of search used to determine the neighbours.
   \param nn Number of neighbours.
   \param n Array with the indices of the neighbouring nodes.
   \param c Array where we store the cost to the neighbours. This is
            useful in re-wire to avoid recomputing symmetrical costs.
	    (see \ref RRTSTAR_SYMMETRIC_COST and the graph mode of \ref Trrt).
   \param h Heuristic cost to the goal. Only used if
            the RRT is in graph mode.
   \param q Priority queue to propagate changes in the tree. Only
            used the RRT is in graph mode.
   \param t The trees of the neighbouring nodes. This in only relevant
            in bi-directional RRTs.
   \param rst Statistics on the RRT construction process (only used if
              \ref GET_RRT_STATISTICS is set).
   \param rrt The RRT to wire.
*/
void WireRRTstar(Tparameters *pr,unsigned int id_new,unsigned int i_near,
		 double gamma,unsigned int nn,unsigned int *n,double **c,
		 double h,Theap *q,unsigned int *t,
		 TRRTStatistics *rst,Trrt *rrt);

/** 
   \brief Rewires an RRT star.

   Uses the last added node to the RRT to try to reduce the cost
   of the neighbouring nodes.

   \param pr The set of parameters.
   \param id_new Identifier of the last node added to the tree.
   \param gamma Radius of search used to determine the neighbours.
   \param nn Number of neighbours.
   \param n Array with the indices of the neighbouring nodes.
   \param c Array where we with the cost to the neighbours.
            Computed in \ref WireRRTstar
	    if \ref RRTSTAR_SYMMETRIC_COST is 1 and
	    RRT is not in graph mode.
   \param steps The steps forming the solution path.
   \param l Best estimation of the cost start-goal up to now.
            Only updated in bidirectional trees.
   \param rrt The RRT to rewire.
*/
void ReWireRRTstar(Tparameters *pr,
		   unsigned int id_new,double gamma,
		   unsigned int nn,unsigned int *n,double *c,
		   Tvector *steps,double *l,
		   Trrt *rrt);

/** 
   \brief Prints information about the RRT* iteration.

   Prints information about the RRT* iteration.

   \param it The current iteration.
   \param id_goal The identifier of the goal. If not found yet, NO_UINT.
   \param time Elapsed time from the start of the RRT*
   \param gamma Value of the threshold for nearest neighbours.
   \param times Array to store information about the execution time per
                iteration.
   \param costs Array to store information about the cost to the goal per
                iteration.
   \param rrt The RRT.
*/
void RRTstarCloseIteration(unsigned int it,unsigned int id_goal,
			   double time,double gamma,
			   double *times,double *costs,
			   Trrt *rrt);

/** 
   \brief Prints information about the BiRRT* iteration.

   Prints information about the BiRRT* iteration.

   \param it The current iteration.
   \param l Cost of the path start/goal via s1 and s2.
   \param time Elapsed time from the start of the RRT*
   \param gamma Value of the threshold for nearest neighbours.
   \param times Array to store information about the execution time per
                iteration.
   \param costs Array to store information about the cost to the goal per
                iteration.
   \param rrt The RRT.
*/
void BiRRTstarCloseIteration(unsigned int it,double l,
			     double time,double gamma,
			     double *times,double *costs,
			     Trrt *rrt);

/**********************************************************************************/
/**********************************************************************************/
/**********************************************************************************/

void CopyRRTStep(void *a,void *b)
{
  ((TRRTStep *)a)->id=((TRRTStep *)b)->id;
  ((TRRTStep *)a)->cost=((TRRTStep *)b)->cost;
}


void SetRRTTopology(Tparameters *pr,Trrt *rrt)
{
  boolean hasS;
  unsigned int i;

  if (CS_WD_GET_SIMP_TOPOLOGY(pr,&(rrt->tp),rrt->w)!=rrt->m)
    Error("Missmatch number of variables in SetRRTTopology");

  /* Search for a "circular" variable */
  hasS=FALSE;
  i=0;
  while((i<rrt->m)&&(!hasS))
    {
      hasS=(rrt->tp[i]==TOPOLOGY_S);
      i++;
    }
  if (!hasS)
    {
      /* if all variables are real no need to consider topology */
      free(rrt->tp);
      rrt->tp=NULL;
    }
}

void AddEdgeToRRT(unsigned int i,unsigned int j,double c,Trrt *rrt)
{
  if (rrt->graph)
    {
      TRRTSampleInfo *si;
      unsigned int k;

      if ((i>=rrt->ns)||(j>=rrt->ns))
	Error("Nodes out of range in AddEdgeToRRT");

      for(k=0;k<2;k++)
	{
	  si=(k==0?rrt->si[i]:rrt->si[j]);
	  if (si->nn==si->m)
	    {
	      MEM_DUP(si->n,si->m,unsigned int);
	      MEM_EXPAND(si->cn,si->m,double);
	    }
	  si->n[si->nn]=(k==0?j:i);
	  si->cn[si->nn]=c;
	  si->nn++;
	}
    }
}

boolean TransitionTestRRT(Tparameters *pr,unsigned int parent,double* q_next,double deltaStep,double *cost,
			  double (*costF)(Tparameters*,boolean,double*,void*),void *costData,Trrt *rrt)
{
  double prevCost;
  double threshold;
  boolean success;
  double epsilon;
  double coefTemp;
  double nFailMax;

  *cost=costF(pr,TRUE,q_next,costData);
  prevCost=rrt->si[parent]->cost;

  epsilon=GetParameter(CT_EPSILON,pr);

  if ((prevCost+epsilon)>(*cost))
    return(TRUE);
  else
    {
      threshold=exp((prevCost-(*cost))/(rrt->temperature*deltaStep));
      coefTemp=GetParameter(CT_COEF_TEMP,pr);
      success=(randomDouble()<threshold);
      if(success)
	{
	  rrt->nFail=0;
	  rrt->temperature=rrt->temperature/pow(coefTemp,((*cost)-prevCost)/10);
	}
      else
	{
	  rrt->nFail=rrt->nFail+1;
	  nFailMax=GetParameter(CT_NFAIL_MAX,pr);
	  if (rrt->nFail>nFailMax)
	    {
	      rrt->temperature=rrt->temperature*coefTemp;
	      rrt->nFail=0;
	    }
	}
      return(success);
    }
}

boolean AddBranchToRRT(Tparameters *pr,boolean ccRRT,
		       unsigned int tree,unsigned int i_near,
		       double *q_rand,double *goal,
		       unsigned int *lastSample,
		       double (*costF)(Tparameters*,boolean,double*,void*),
		       void *costData,
		       TRRTStatistics *rst,Trrt *rrt)
{
  double epsilon;
  boolean validSample,inDomain,inCollision,goalReached,distanceDecrease,tooFar,
          qRandReached,tooClose;
  unsigned int it;
  double d,d1,dp;
  double *v,*q_near,*q_next,*q_tmp;
  unsigned int parent;
  double eps;
  boolean trans;
  double cost;

  epsilon=GetParameter(CT_EPSILON,pr);
  if (ccRRT)
    eps=0;
  else
    eps=rrt->delta/50.0; /* for delta = 0.05 -> eps= 0.001 (value used in original cbirrt2) */

  q_near=rrt->si[i_near]->samples;

  NEW(v,rrt->m,double);
  NEW(q_next,rrt->m,double);
  NEW(q_tmp,rrt->m,double);
  memcpy(q_next,q_near,rrt->m*sizeof(double)); /* start from q_near */
  parent=i_near; /* inear will be parent for 1st sample if any */
  *lastSample=i_near;

  DifferenceVectorTopology(rrt->m,rrt->tp,q_rand,q_next,v); /* q_next=q_near */
  d1=Norm(rrt->m,v);
  if (d1>rrt->delta)
    ScaleVector(rrt->delta/d1,rrt->m,v);
  #if (WEIGTHED_REACHED_GOAL>1)
    d1=WeightedDistanceTopology(rrt->m,rrt->tp,rrt->weight,q_next,q_rand);
  #endif

  #if (_DEBUG>1)
    printf("  Distance q_rand-tree: %f (%.12f)\n",d1,rrt->delta);
  #endif

  goalReached=FALSE;
  validSample=TRUE;
  inDomain=TRUE;
  inCollision=FALSE;
  distanceDecrease=TRUE;
  tooFar=FALSE;
  tooClose=FALSE;
  qRandReached=FALSE;
  trans=TRUE;

  it=1;
  while((!goalReached)&&(validSample)&&(!qRandReached)&&(inDomain)&&(trans)&&
	(!inCollision)&&(distanceDecrease)&&(!tooFar)&&(!tooClose))
    {
      if (ccRRT)
        SumVectorScale(rrt->m,q_near,(double)it,v,q_next);
      else
	AccumulateVector(rrt->m,v,q_next);

      if (rrt->n>0)
	validSample=(CS_WD_NEWTON_IN_SIMP(pr,q_next,rrt->w)!=DIVERGED);

      if (validSample)
	{
	  /* Compute the distance to previous sample */
	  dp=DistanceTopology(rrt->m,rrt->tp,rrt->si[parent]->samples,q_next);

	  /* Distance to previous sample should not be too small */
	  tooClose=(dp<eps);
	  if (!tooClose)
	    {
	      /* Distance to previous sample should not too large */
	      tooFar=(dp>2*rrt->delta);
	      if (!tooFar)
		{
		  /* Distance to q_rand should not increase */
		  d=d1;
		  d1=DistanceTopology(rrt->m,rrt->tp,q_next,q_rand);
		  /* new < previous ? */
		  #if (WEIGTHED_REACHED_GOAL>1)
		    distanceDecrease=(WeightedDistanceTopology(rrt->m,rrt->tp,rrt->weight,q_next,q_rand)<d);
		  #else
		    distanceDecrease=(d1<d);
		  #endif

		  if (distanceDecrease)
		    {
		      /* before checking the inDomain condition, we have to
		         move the ranges to [-pi,pi], if necessary*/
		      inDomain=((PointInBoxTopology(NULL,FALSE,rrt->m,q_next,epsilon,rrt->tp,rrt->ambient))&&
				(CS_WD_SIMP_INEQUALITIES_HOLD(pr,q_next,rrt->w)));
		      if (inDomain)
			{
			  if(costF!=NULL)
			    trans=TransitionTestRRT(pr,parent,q_next,dp,&cost,costF,costData,rrt);

			  if(trans)
			    {
			      CS_WD_IN_COLLISION(inCollision,pr,q_next,rrt->si[parent]->samples,rrt->w);
			      #if (GET_RRT_STATISTICS)
				NewRRTCollisionCheck(rst);
			      #endif
			      if (!inCollision)
				{
				  // fprintf(stderr," exp Step:  %f \n",dp);
				  qRandReached=AddNodeToRRT(pr,tree,parent,q_next,q_rand,
							    lastSample,NULL,dp,cost,FALSE,NULL,0,
							    0,NULL,NULL,NULL,rst,rrt);
				  #if (GET_RRT_STATISTICS)
				    if (qRandReached)
				      NewRRTQrandReached(rst);
				  #endif

				  /* currentNode will be parent for next iteration,
				     if any */
				  parent=*lastSample;

                                  #if (!EXPLORATION_RRT)
				    #if (WEIGTHED_REACHED_GOAL)
				      goalReached=(WeightedDistanceTopology(rrt->m,rrt->tp,rrt->weight,q_next,goal)<rrt->delta);
				    #else
				      goalReached=(DistanceTopology(rrt->m,rrt->tp,q_next,goal)<rrt->delta);
				    #endif
                                  #endif

				  if ((!ccRRT)&&(!goalReached))
				    {
				      DifferenceVectorTopology(rrt->m,rrt->tp,
							       q_rand,q_next,v);
				      /* d1 computed above =
					 distance(q_rand_q_next)*/
				      if (d1>rrt->delta)
					ScaleVector(rrt->delta/d1,rrt->m,v);
				    }
				}
			      #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
			      else
				{
				  #if (GET_RRT_STATISTICS)
				    NewRRTCollision(rst);
				  #endif
				  #if (RRT_VERBOSE)
				    fprintf(stderr,"  Configuration in collision.\n");
				  #endif
				}
                              #endif
			    }
                          #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
			  else
			    {
			      #if (GET_RRT_STATISTICS)
			        NewRRTHighCost(rst);
			      #endif
			      #if (RRT_VERBOSE)
			        fprintf(stderr,"  Configuration cost too high.\n");
			      #endif
			    }
			  #endif
			}
		      #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
		      else
			{
			  #if (GET_RRT_STATISTICS)
			    NewRRTOutOfDomain(rst);
			  #endif
			  #if (RRT_VERBOSE)
			    fprintf(stderr,"  Configuration not in domain.\n");
			  #endif
			}
		      #endif
		    }
                  #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
		  else
		    {
		      #if (GET_RRT_STATISTICS)
		        NewRRTDistanceIncreases(rst);
		      #endif
		      #if (RRT_VERBOSE)
			fprintf(stderr,"  Distance to q_rand increases (or stalled)\n");
		      #endif
		    }
		  #endif
		}
	      #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
	      else
		{
		  #if (GET_RRT_STATISTICS)
		    NewRRTTooFar(rst);
		  #endif
		  #if (RRT_VERBOSE)
		    fprintf(stderr,"  Previous configuration is too far (too large advance step)\n");
		  #endif
		}
	      #endif
	    }
          #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
	  else
	    {
	      #if (GET_RRT_STATISTICS)
	        NewRRTStalled(rst);
	      #endif
	      #if (RRT_VERBOSE)
		fprintf(stderr,"  Previous configuration is too close (small advance step)\n");
	      #endif
	    }
	  #endif
	}
      #if ((RRT_VERBOSE)||(GET_RRT_STATISTICS))
      else
	{
	  #if (GET_RRT_STATISTICS)
	    NewRRTConvergenceError(rst);
	  #endif
	  #if (RRT_VERBOSE)
	    fprintf(stderr,"  Sample does not converge to manifold.\n");
	  #endif
	}
      #endif
      it++;
    }

  if (rrt->dd>0)
    AdjustDynamicDomain(i_near,inCollision,rrt);

  free(v);
  free(q_next);
  free(q_tmp);

  return(goalReached);
}


unsigned int ReconstructRRTPath(Tparameters *pr,unsigned int sID,double *pl,double *pc,
				unsigned int *ns,double ***path,double ***action,double **time,
				Trrt *rrt)
{
  Tvector steps;
  unsigned int nvs;

  RRTPathSteps(sID,&steps,rrt);

  nvs=Steps2PathinRRT(pr,&steps,pl,pc,ns,path,action,time,rrt);

  DeleteVector(&steps);

  return(nvs);
}

unsigned int Steps2PathinRRT(Tparameters *pr,Tvector *steps,double *pl,double *pc,
			     unsigned int *ns,double ***path,double ***action,double **time,
			     Trrt *rrt)
{
  TRRTStep *st;
  unsigned int nv,nvs,ms,n,i,j,current,previous,l;
  signed int k;
  double *o,c;
  boolean *systemVars;
  unsigned int lns;
  double **lpath;
  boolean reached,collision;
  double epsilon,dc;
  TRRTStep *stprevious;

  *pl=0; /* path length (or time in dynamic systems) */
  if (pc!=NULL) /* path cost (mechanical work) */
    {
      *pc=0;
      epsilon=GetParameter(CT_EPSILON,pr);
    }

  /* Identify system variables */
  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,rrt->w);
  nvs=0;
  for(i=0;i<nv;i++)
    {
      if (systemVars[i])
	nvs++;
    }

  n=VectorSize(steps);

  if (rrt->da>0)
    {
      double tm;
      
      InitTrajectory(&ms,ns,path,rrt->da,action,time);
      tm=0.0;
      for(k=(signed int)(n-1);k>=0;k--)
	{
	  st=(TRRTStep *)GetVectorElement(k,steps);
	  current=st->id;

	  if (k<(signed int)(n-1))
	    {
	      stprevious=(TRRTStep *)GetVectorElement(k+1,steps);
	      previous=stprevious->id;
	      
	      c=0.0;
	      tm=0.0;
	      for(l=0;l<rrt->si[st->id]->ns;l++)
		{
		  CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[current]->path[l],&o,rrt->w);
		  AddStep2Trajectory(nv,o,nvs,systemVars,rrt->si[current]->actions[l],rrt->si[current]->times[l],
				     &ms,ns,path,rrt->da,action,time);
		  free(o);
		  
		  if (l==0)
		    c+=DistanceTopology(rrt->m,rrt->tp,rrt->si[previous]->samples,rrt->si[current]->path[l]);
		  else
		    c+=DistanceTopology(rrt->m,rrt->tp,rrt->si[current]->path[l-1],rrt->si[current]->path[l]);
		  tm+=rrt->si[current]->times[l];
		}
	  
	      if (rrt->si[current]->ns>0)
		c+=DistanceTopology(rrt->m,rrt->tp,rrt->si[current]->path[rrt->si[st->id]->ns-1],rrt->si[current]->samples);
	      else
		c=DistanceTopology(rrt->m,rrt->tp,rrt->si[previous]->samples,rrt->si[current]->samples);

	      
	      if (pc!=NULL) /* path cost (in the terms of TRRT: mechanical work) */
		{
		  dc=rrt->si[previous]->cost-rrt->si[current]->cost;
		  (*pc)+=(dc>0?dc:0)+epsilon*c;
		}
	      
	      (*pl)+=c; /* path length */
	    }
	  
	  CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[current]->samples,&o,rrt->w);
	  AddStep2Trajectory(nv,o,nvs,systemVars,rrt->si[current]->u,rrt->si[current]->time-tm,
			     &ms,ns,path,rrt->da,action,time);
	  free(o);

	}
    }
  else
    {
      InitSamples(&ms,ns,path);
      if (action!=NULL) *action=NULL;
      if (time!=NULL) *time=NULL;

      k=(signed int)n-1;
      while (k>=0)
	{
	  st=(TRRTStep *)GetVectorElement(k,steps);
	  current=st->id;
	  
	  if (k<(signed int)(n-1))
	    {
	      stprevious=(TRRTStep *)GetVectorElement(k+1,steps);
	      previous=stprevious->id;

	      c=0.0;
	      for(l=0;l<rrt->si[current]->ns;l++)
		{
		  CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[current]->path[l],&o,rrt->w);
		  AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
		  free(o);
	      
		  if (l==0)
		    c+=DistanceTopology(rrt->m,rrt->tp,rrt->si[previous]->samples,rrt->si[current]->path[l]);
		  else
		    c+=DistanceTopology(rrt->m,rrt->tp,rrt->si[current]->path[l-1],rrt->si[current]->path[l]);
		}

	      if (rrt->si[current]->ns>0)
		c+=DistanceTopology(rrt->m,rrt->tp,rrt->si[current]->path[rrt->si[st->id]->ns-1],rrt->si[current]->samples);
	      else
		{
		  c=ConnectSamples(pr,rrt->tp,NULL,rrt->ambient,rrt->m,rrt->n,
				   rrt->si[previous]->samples,rrt->si[current]->samples,INF,
				   FALSE,NULL,&reached,&collision,NULL,&lns,&lpath,rrt->w);

		  if (!reached)
		    Warning("Path segment could not be reconstructed in Steps2PathinRRT");
	      
		  for(j=0;j<lns;j++)
		    {
		      CS_WD_REGENERATE_ORIGINAL_POINT(pr,lpath[j],&o,rrt->w);
		      AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
		      free(o);
		    }
		  DeleteSamples(lns,lpath);
		}
	  
	      #if (RRT_VERBOSE)
	        fprintf(stderr,"{%u->%u}[%g]",previous,current,c);
	      #endif

	      (*pl)+=c; /* Update the path length */
	  
	      if(pc!=NULL) /* Update the path cost (mechanical work) */
		{
		  dc=rrt->si[previous]->cost-rrt->si[current]->cost;
		  (*pc)+=(dc>0?dc:0)+epsilon*c;
		}
	    }
	  
	  CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[current]->samples,&o,rrt->w);
	  AddSample2Samples(nv,o,nvs,systemVars,&ms,ns,path);
	  free(o);
	  
	  k--;
	}
    }

  free(systemVars);

  return(nvs);
}

double RRTPathLength(Tparameters *pr,unsigned int sID,Trrt *rrt)
{
  unsigned int i;
  double pl;

  pl=0;
  i=sID;
  while (i!=NO_UINT)
    {
      if (rrt->si[i]->parent!=NO_UINT)
	pl+=DistanceTopology(rrt->m,rrt->tp,
			     rrt->si[i]->samples,rrt->si[rrt->si[i]->parent]->samples);
      i=rrt->si[i]->parent;
    }

  return(pl);
}

/**********************************************************************************/
/**********************************************************************************/
/**********************************************************************************/

void InitRRT(Tparameters *pr,boolean parallel,boolean simp,double *ps,
	     unsigned int mode,boolean graph,double *pg,
	     unsigned int m,unsigned int da,TAtlasBase *w,Trrt *rrt)
{
  double epsilon,er,*pWithDummies;
  unsigned int i;
  boolean collision=FALSE;
  unsigned int samplingMode;
  double dr;
  Tinterval *range;

  #if (EXPLORATION_RRT)
    if (mode!=ONE_TREE)
      Error("An EXPLORATION_RRT must be one directional");
  #endif

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);
  dr=GetParameter(CT_DYNAMIC_DOMAIN,pr);

  /* Set up the possible parallel execution */
  rrt->parallel=FALSE; /* The default is not to execute in parallel */
  #ifdef _OPENMP
    if (parallel)
      {
	rrt->nCores=omp_get_max_threads();
	/* even if having many cores ans OpenMP we only execute in parallel
	   large problems. */
	rrt->parallel=(rrt->nCores>1);
      }
  #endif
  //rrt->parallel=FALSE;
  if (!rrt->parallel)
    rrt->nCores=1;

  fprintf(stderr,"Number of computing cores (rrt)   : %u\n",rrt->nCores);

  /* The base information with the equations, collions,... */
  rrt->w=w;

  /* one_tree two_trees, two_trees_with_swap */
  rrt->mode=mode;
  rrt->graph=graph;
  /* in kdtree sampling mode the dynamic domain is fixed
     by the kdtree, and not in the samples. */
  if (samplingMode==KDTREE_SAMPLING)
    rrt->dd=0.0;
  else
    rrt->dd=dr;

  /* dimension of the action space */
  rrt->da=da;

  /* only used for t-rrt */
  rrt->temperature=TEMPERATURE_INIT;
  rrt->nFail=0;

  /* Information for each sample */
  rrt->ms=INIT_NUM_SAMPLES_RRT;
  rrt->ns=0;
  NEW(rrt->si,rrt->ms,TRRTSampleInfo*);
  for(i=0;i<rrt->ms;i++)
    rrt->si[i]=NULL;

  /* Initialize the collision detection, just in case */
  CS_WD_INIT_CD(pr,rrt->nCores,rrt->w);

  NEW(rrt->si[0],1,TRRTSampleInfo);
  if (simp)
    {
      /* If the input point is already in simplified form, use
         it directly. This is not the usual case. */
      rrt->m=m;
      NEW(rrt->si[0]->samples,rrt->m,double);
      memcpy(rrt->si[0]->samples,ps,sizeof(double)*rrt->m);
      if (rrt->mode!=ONE_TREE)
	{
	  /* In bi-directional trees the goal is also added */
	  NEW(rrt->si[1],1,TRRTSampleInfo);
	  NEW(rrt->si[1]->samples,rrt->m,double);
	  memcpy(rrt->si[1]->samples,pg,sizeof(double)*rrt->m);
	}
    }
  else
    {
      /* Simplify the input point and add it to the tree */
      CS_WD_REGENERATE_SOLUTION_POINT(pr,ps,&pWithDummies,rrt->w);
      rrt->m=CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,
					     &(rrt->si[0]->samples),rrt->w);
      free(pWithDummies);

      if (rrt->mode!=ONE_TREE)
	{
	  /* In bi-directional trees the goal is also added */
	  NEW(rrt->si[1],1,TRRTSampleInfo);
	  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,rrt->w);
	  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,
					  &(rrt->si[1]->samples),rrt->w);
	  free(pWithDummies);
	}
    }

  // rrt->m dimension of the ambient space
  rrt->k=(unsigned int)GetParameter(CT_N_DOF,pr); //dimension of the manifold
  rrt->n=rrt->m-rrt->k; //num of independent equations
  rrt->delta=GetParameter(CT_DELTA,pr);

  SetRRTTopology(pr,rrt);

  /* Box enclosing the part of the manifold to explore */
  NEW(rrt->ambient,1,Tbox);
  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,rrt->ambient,rrt->w);

  #if (WEIGTHED_NN)
    if (GetDistanceWeightsFromBox(&(rrt->weight),rrt->ambient)!=rrt->m)
      {
	fprintf(stderr,"%u vs %u",rrt->ambient->n,rrt->m);
	Error("Size missmatch in InitRRT");
      }
  #else
    rrt->weight=NULL;
  #endif
  
  if ((!PointInBoxTopology(NULL,TRUE,rrt->m,rrt->si[0]->samples,epsilon,rrt->tp,rrt->ambient))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,rrt->si[0]->samples,rrt->w)))
    Error("The start point is not in domain");

  /* Verify the start/goal samples, now that they are already simplified
     and added to the RRT */
  if (rrt->n==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,rrt->si[0]->samples,rrt->w);
  if (er>epsilon)
    Error("The start point is not on the manifold");

  CS_WD_IN_COLLISION(collision,pr,rrt->si[0]->samples,NULL,rrt->w);
  if (collision)
    Error("Start point for the RRT is in collision");

  rrt->si[0]->costp=0.0;
  rrt->si[0]->cost=0.0;
  rrt->si[0]->blocked=0.0;
  rrt->si[0]->ddr=0.0;
  rrt->si[0]->tree=START2GOAL;
  rrt->si[0]->parent=NO_UINT;
  if (rrt->da==0)
    rrt->si[0]->u=NULL;
  else
    {NEWZ(rrt->si[0]->u,rrt->da,double);}
  rrt->si[0]->time=0.0;
  rrt->si[0]->ns=0;
  rrt->si[0]->path=NULL;
  rrt->si[0]->actions=NULL;
  rrt->si[0]->times=NULL;
  
  if (rrt->graph)
    {
      rrt->si[0]->g=0;
      rrt->si[0]->m=10; /* initial space for 10 neighbours (extended when necessary) */
      rrt->si[0]->nn=0;
      NEW(rrt->si[0]->n,rrt->si[0]->m,unsigned int);
      NEW(rrt->si[0]->cn,rrt->si[0]->m,double);
    }
  rrt->ns=1;

  if (rrt->mode!=ONE_TREE)
    {
      rrt->si[1]->costp=0.0;
      rrt->si[1]->cost=0.0;
      rrt->si[1]->blocked=0.0;
      rrt->si[1]->ddr=0.0;
      rrt->si[1]->tree=GOAL2START;
      rrt->si[1]->parent=NO_UINT;
      if (rrt->da==0)
	rrt->si[1]->u=NULL;
      else
	{NEWZ(rrt->si[1]->u,rrt->da,double);}
      rrt->si[1]->time=0.0;
      rrt->si[1]->ns=0;
      rrt->si[1]->path=NULL;
      rrt->si[1]->actions=NULL;
      rrt->si[1]->times=NULL;
  
      if (rrt->graph)
	{
	  rrt->si[1]->g=0;
	  rrt->si[1]->m=10; /* initial space for 10 neighbours (extended when necessary) */
	  rrt->si[1]->nn=0;
	  NEW(rrt->si[1]->n,rrt->si[1]->m,unsigned int);
	  NEW(rrt->si[1]->cn,rrt->si[1]->m,double);
	}
      rrt->ns=2;

      if ((!PointInBoxTopology(NULL,TRUE,rrt->m,rrt->si[1]->samples,epsilon,rrt->tp,rrt->ambient))||
	  (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,rrt->si[1]->samples,rrt->w)))
	Error("The goal point is not in domain");

      if (rrt->n==0)
	er=0;
      else
	er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,rrt->si[1]->samples,rrt->w);
      if (er>epsilon)
	Error("The goal point is not on the manifold");

      CS_WD_IN_COLLISION(collision,pr,rrt->si[1]->samples,NULL,rrt->w);
      if (collision)
	Error("Goal point for the RRT is in collision");
    }
  
  #if (_KDTREE==1)
  {
    unsigned int nd;
    Trectangle rec;

    nd=GetBoxNIntervals(rrt->ambient);
    if (rrt->m!=nd)
      Error("Dimension missmatch in InitRRT");
    
    InitRectangle(nd,NULL,NULL,&rec);
    for(i=0;i<nd;i++)
      {
	range=GetBoxInterval(i,rrt->ambient);
	SetRectangleLimits(i,LowerLimit(range),UpperLimit(range),&rec);
      }
    i=0;
    rrt->treeS2G=InitKDTree(&rec,rrt->tp,rrt->weight,25,dr,1,&(rrt->si[0]->samples),&i);

    if (rrt->mode!=ONE_TREE)
      {
	i=1;
	if (rrt->mode==TWO_TREES)
	  rrt->treeG2S=InitKDTree(&rec,rrt->tp,rrt->weight,25,dr,1,&(rrt->si[1]->samples),&i);
	else
	  /* TWO_TREES_WITH_SWAP -> only one tree is used */
	  AddPoint2KDtree(rrt->si[1]->samples,i,&(rrt->treeS2G));
      }
    else
      rrt->treeG2S=NULL;

    DeleteRectangle(&rec);
  }
  #endif

  #if (_KDTREE==2)
  {
    double *w2;

    NEW(w2,rrt->m,double);
    for(i=0;i<nd;i++)
      {
	if (rrt->weight==NULL)
	  w2[i]=1.0;
	else
	  w2[i]=sqrt(rrt->weight[i]); /* In this kdtree weights are squared inside */
      }

    /* Create the start 2 goal tree */
    if ((!RRT_NN_TOPOLOGY)||(rrt->tp==NULL))
      rrt->treeS2G=CreateKDTreeS(rrt->m,w2);
    else
      rrt->treeS2G=CreateKDTreeTS(rrt->m,(int *)rrt->tp,w2);

    AddPoint2KDTree(rrt->si[0]->samples,rrt->treeS2G);
    if (rrt->mode!=ONE_TREE)
      {
	/* and the goal to start, if necessary */
	if (rrt->mode==TWO_TREES)
	  {
	    if ((!RRT_NN_TOPOLOGY)||(rrt->tp==NULL))
	      rrt->treeG2S=CreateKDTree(rrt->m);
	    else
	      rrt->treeG2S=CreateKDTreeT(rrt->m,(int *)rrt->tp);

	    AddPoint2KDTree(rrt->si[1]->samples,rrt->treeG2S);

	    rrt->maxNodesT1=rrt->ms;
	    rrt->maxNodesT2=rrt->ms;

	    NEW(rrt->t1ToId,rrt->maxNodesT1,unsigned int);
	    NEW(rrt->t2ToId,rrt->maxNodesT2,unsigned int);

	    rrt->t1ToId[0]=0;
	    rrt->t2ToId[0]=1;

	    rrt->nodesT1=1;
	    rrt->nodesT2=1;
	  }
	else
	  {
	    /* TWO_TREES_WITH_SWAP -> only one kd-tree is used
	       to speed up the search for nearest neighbours,
	       independent of the tree. Searches in a particular
	       three, though, will be serial */
	    AddPoint2KDTree(rrt->si[1]->samples,rrt->treeS2G);
	  }
      }
    else
      {
	rrt->treeG2S=NULL;
	rrt->t1ToId=NULL;
	rrt->t2ToId=NULL;
      }
    free(w2);
  }
  #endif
}

double GetTRRTTemperature(Trrt *rrt)
{
  return(rrt->temperature);
}

boolean IsRRTGraph(Trrt *rrt)
{
  return(rrt->graph);
}

boolean RRTSample(unsigned int samplingMode,unsigned int tree,
		  double *goal,double *q_rand,
		  TRRTStatistics *rst,Trrt *rrt)
{
  boolean expand2Goal;

  #if (GET_RRT_STATISTICS)
    if (rst!=NULL)
      NewRRTRandomSample(rst);
  #endif

  expand2Goal=((rrt->mode==ONE_TREE)&&(goal!=NULL)&&(randomDouble()<0.01));
  if (expand2Goal)
    {
      memcpy(q_rand,goal,rrt->m*sizeof(double));
      #if (RRT_VERBOSE)
        fprintf(stderr,"  Expanding to goal----------------------------------\n");
      #endif
    }
  else
    {
      #if (_KDTREE==1)
      if (samplingMode==KDTREE_SAMPLING)
	{
	  if ((rrt->mode==ONE_TREE)||(tree==START2GOAL)||
	      ((tree==BOTHTREES)&&(randomDouble()<0.5)))
	    SampleInKDtree(q_rand,rrt->treeS2G);
	  else
	    SampleInKDtree(q_rand,rrt->treeG2S);
	}
      else
      #endif
      /* samplingMode != KDTREE_SAMPLING  (AMBIENT or TANGENT) */
      RandomPointInBox(NULL,q_rand,rrt->ambient);
    }

  return(expand2Goal);
}

boolean RRTValidateSample(Tparameters *pr,double *q_rand,unsigned int tree,boolean expand2goal,
			  double *goal,double l,double *h,unsigned int *i_near,
			  TRRTStatistics *rst,Trrt *rrt)
{
  boolean validSample=TRUE;

  /* First check the optimality heuristics, if any */
  if ((expand2goal)||(goal==NULL))
    *h=0.0;
  else
    {
      *h=DistanceTopology(rrt->m,rrt->tp,q_rand,goal);
      if ((l<INF)&&((HEURISTIC_RRT_STAR)&(1)))
	validSample=((DistanceTopology(rrt->m,rrt->tp,rrt->si[0]->samples,q_rand)+*h)<=l);
    }

  /* Now check the domain */
  if (validSample)
    validSample=((expand2goal)||(CS_WD_SIMP_INEQUALITIES_HOLD(pr,q_rand,rrt->w)));

  /* Now the NN conditions (dynamic domain) */
  if (validSample)
    {
      *i_near=GetRRTNN(tree,q_rand,rrt);

      if (rrt->dd>0)
	validSample=InDynamicDomain(*i_near,q_rand,rrt);
    }

  #if (GET_RRT_STATISTICS)
    if (!validSample)
      NewRRTSampleRejection(rst);
  #endif

  return(validSample);
}

boolean PointInRRT(double epsilon,unsigned int tree,double *q,Trrt *rrt)
{
  double d;

  #if (_KDTREE==1)
  if ((rrt->mode!=TWO_TREES_WITH_SWAP)||(tree==BOTHTREES))
    {
      if (rrt->mode==TWO_TREES)
	{
	  if (tree==START2GOAL)
	    NearestNeighbour(q,&d,rrt->treeS2G);
	  else
	    {
	      if (tree==GOAL2START)
		NearestNeighbour(q,&d,rrt->treeG2S);
	      else
		{
		  /* BOTHTREES */
		  double d1,d2;

		  NearestNeighbour(q,&d1,rrt->treeS2G);
		  NearestNeighbour(q,&d2,rrt->treeG2S);

		  d=(d1<d2?d1:d2);
		}
	    }
	}
      else
	/* rrt->mode==ONE_TREE or (rrt->mode==TWO_TREES_WITH_SWAP and tree==BOTHTREES) */
	NearestNeighbour(q,&d,rrt->treeS2G);

      return(d<epsilon);
    }
  else
  #endif

  #if (_KDTREE==2)
  if ((rrt->mode!=TWO_TREES_WITH_SWAP)||(tree==BOTHTREES))
    {
      signed int inear;

      if (rrt->mode==TWO_TREES)
	{
	  if (tree==START2GOAL)
	    QueryKDTree(q,&inear,&d,rrt->treeS2G);
	  else
	    {
	      if (tree==GOAL2START)
		QueryKDTree(q,&inear,&d,rrt->treeG2S);
	      else
		{
		  /* NN in any of the two trees */
		  double d1,d2;
		  signed int inear1,inear2;

		  QueryKDTree(q,&inear1,&d1,rrt->treeG2S);
		  QueryKDTree(q,&inear2,&d2,rrt->treeS2G);

		  d=(d1<d2?d1:d2);
		}
	    }
	}
      else
	/* rrt->mode==ONE_TREE or (rrt->mode==TWO_TREES_WITH_SWAP and tree==BOTHTREES) */
	QueryKDTree(q,&inear,&d,rrt->treeS2G);

      return(d<epsilon);
    }
  else
  #endif
    {
      unsigned int j;
      double d1;

      /* _KDTREE==0 or (BOTH_TREES_WITH_SWAP and tree!=BOTH_TREES) */
      d=INF;
      for(j=0;j<rrt->ns;j++)
	{
	  if ((rrt->mode==ONE_TREE)||(rrt->si[j]->tree&tree))
	    {
	      d1=WeightedDistanceTopologyMin(d,rrt->m,rrt->tp,rrt->weight,q,rrt->si[j]->samples);
	      if (d1<d)
		d=d1;
	    }
	}
      return(d<epsilon);
    }
}

unsigned int GetRRTNN(unsigned int tree,double *q_rand,Trrt *rrt)
{
  double d;

  #if (_KDTREE==1)
  if ((rrt->mode!=TWO_TREES_WITH_SWAP)||(tree==BOTHTREES))
    {
      unsigned int inear;

      if (rrt->mode==TWO_TREES)
	{
	  if (tree==START2GOAL)
	    inear=NearestNeighbour(q_rand,&d,rrt->treeS2G);
	  else
	    {
	      if (tree==GOAL2START)
		inear=NearestNeighbour(q_rand,&d,rrt->treeG2S);
	      else
		{
		  /* BOTHTREES */
		  unsigned int inear1,inear2;
		  double d1,d2;

		  inear1=NearestNeighbour(q_rand,&d1,rrt->treeS2G);
		  inear2=NearestNeighbour(q_rand,&d2,rrt->treeG2S);

		  inear=(d1<d2?inear1:inear2);
		}
	    }
	}
      else
	/* rrt->mode==ONE_TREE or (rrt->mode==TWO_TREES_WITH_SWAP and tree==BOTHTREES) */
	inear=NearestNeighbour(q_rand,&d,rrt->treeS2G);

      return(inear);
    }
  else
  #endif

  #if (_KDTREE==2)
  if ((rrt->mode!=TWO_TREES_WITH_SWAP)||(tree==BOTHTREES))
    {
      signed int inear;

      if (rrt->mode==TWO_TREES)
	{
	  if (tree==START2GOAL)
	    {
	      QueryKDTree(q_rand,&inear,&d,rrt->treeS2G);
	      inear=rrt->t1ToId[inear];
	    }
	  else
	    {
	      if (tree==GOAL2START)
		{
		  QueryKDTree(q_rand,&inear,&d,rrt->treeG2S);
		  inear=rrt->t2ToId[inear];
		}
	      else
		{
		  /* NN in any of the two trees */
		  double d1,d2;
		  signed int inear1,inear2;

		  QueryKDTree(q_rand,&inear1,&d1,rrt->treeG2S);
		  QueryKDTree(q_rand,&inear2,&d2,rrt->treeS2G);

		  if (d1<d2)
		    inear=rrt->t1ToId[inear1];
		  else
		    inear=rrt->t2ToId[inear2];
		}
	    }
	}
      else
	/* rrt->mode==ONE_TREE or (rrt->mode==TWO_TREES_WITH_SWAP and tree==BOTHTREES) */
	QueryKDTree(q_rand,&inear,&d,rrt->treeS2G);

      return((unsigned int)inear);
    }
  else
  #endif
    {
      unsigned int j,inear;
      double d1;

      /* _KDTREE==0 or (BOTH_TREES_WITH_SWAP and tree!=BOTH_TREES) */
      d=INF;
      inear=NO_UINT;
      for(j=0;j<rrt->ns;j++)
	{
	  if ((rrt->mode==ONE_TREE)||(rrt->si[j]->tree&tree))
	    {
	      d1=WeightedDistanceTopologyMin(d,rrt->m,rrt->tp,rrt->weight,q_rand,rrt->si[j]->samples);
	      if (d1<d)
		{
		  d=d1;
		  inear=j;
		}
	    }
	}
      return(inear);
    }
}

void GetRRTNNInBall(unsigned int tree,double *q_rand,double r,
		    unsigned int *nn,unsigned int **n,Trrt *rrt)
{
  #if (_KDTREE==1)
  if ((rrt->mode!=TWO_TREES_WITH_SWAP)||(tree==BOTHTREES))
    {
      if (rrt->mode==TWO_TREES)
	{
	  if (tree==START2GOAL)
	    NeighboursInBall(q_rand,r,nn,n,rrt->treeS2G);
	  else
	    {
	      if (tree==GOAL2START)
		NeighboursInBall(q_rand,r,nn,n,rrt->treeG2S);
	      else
		{
		  unsigned int i;
		  unsigned int nn1,nn2;
		  unsigned int *n1,*n2;

		  NeighboursInBall(q_rand,r,&nn1,&n1,rrt->treeS2G);
		  NeighboursInBall(q_rand,r,&nn2,&n2,rrt->treeG2S);

		  *nn=nn1+nn2;
		  NEW(*n,*nn,unsigned int);
		  for(i=0;i<nn1;i++)
		    (*n)[i]=n1[i];

		  for(i=0;i<nn2;i++)
		    (*n)[nn1+i]=n2[i];
		}
	    }
	}
      else
	/* rrt->mode==ONE_TREE or (rrt->mode==TWO_TREES_WITH_SWAP and tree==BOTHTREES) */
	NeighboursInBall(q_rand,r,nn,n,rrt->treeS2G);
    }
  else
  #endif
  #if (_KDTREE==2)
  if ((rrt->mode!=TWO_TREES_WITH_SWAP)||(tree==BOTHTREES))
    {
      double *dst;

      if (rrt->mode==TWO_TREES)
	{
	  unsigned int i;

	  if (tree==START2GOAL)
	    {
	      QueryKDTreeR(q_rand,r,(int *)(nn),(int **)(n),&dst,rrt->treeS2G);
	      free(dst);

	      for(i=0;i<*nn;i++)
		(*n)[i]=rrt->t1ToId[(*n)[i]];
	    }
	  else
	    {
	      if (tree==GOAL2START)
		{
		  QueryKDTreeR(q_rand,r,(int *)(nn),(int **)(n),&dst,rrt->treeG2S);
		  free(dst);

		  for(i=0;i<*nn;i++)
		    (*n)[i]=rrt->t2ToId[(*n)[i]];
		}
	      else
		{
		  /* Both trees */
		  unsigned int nn1,nn2;
		  unsigned int *n1,*n2;

		  QueryKDTreeR(q_rand,r,(int *)(&nn1),(int **)(&n1),&dst,rrt->treeS2G);
		  free(dst);
		  QueryKDTreeR(q_rand,r,(int *)(&nn2),(int **)(&n2),&dst,rrt->treeG2S);
		  free(dst);

		  *nn=nn1+nn2;
		  NEW(*n,*nn,unsigned int);
		  for(i=0;i<nn1;i++)
		    (*n)[i]=rrt->t1ToId[n1[i]];

		  for(i=0;i<nn2;i++)
		    (*n)[nn1+i]=rrt->t2ToId[n2[i]];
		}
	    }
	}
      else
	{
	  /* rrt->mode==ONE_TREE or (rrt->mode==TWO_TREES_WITH_SWAP and tree==BOTHTREES) */
	  QueryKDTreeR(q_rand,r,(int *)(nn),(int **)(n),&dst,rrt->treeS2G);
	  free(dst);
	}
    }
  else
  #endif
    {
      unsigned int m,j;
      double d1;

      /* _KDTREE==0 or BOTH_TREES_WITH_SWAP and tree!=BOTH_TREES */
      m=10;
      *nn=0;
      NEW(*n,m,unsigned int);
      for(j=0;j<rrt->ns;j++)
	{
	  if ((rrt->mode==ONE_TREE)||(rrt->si[j]->tree&tree))
	    {
	      d1=WeightedDistanceTopologyMin(r,rrt->m,rrt->tp,rrt->weight,q_rand,rrt->si[j]->samples);
	      if (d1<r)
		{
		  if (*nn==m)
		    MEM_DUP(*n,m,unsigned int);
		  (*n)[*nn]=j;
		  (*nn)++;
		}
	    }
	}
    }
}

void GetRRTNNInBranch(unsigned int tree,
		      unsigned int n1,unsigned int n2,
		      unsigned int *n,unsigned int *nn,
		      Trrt *rrt)
{
  double md,cd;
  unsigned int cn;
  int cnn;

  /* Conceptually this operation is used only in bi-directional trees (altough in practice
     it could be implemented in single-trees too */
  if (rrt->mode==ONE_TREE)
    Error("GetRRTNNInBranch is only defined for bidirectional RRTs");

  if (rrt->si[n1]->tree!=rrt->si[n2]->tree)
    Error("The two nodes defining the branch in GetRRTNNInBranch are not in the same tree");

  if (tree==rrt->si[n1]->tree)
    Error("Parameter missmatch in GetRRTNNInBranch (the branch is in the query tree)");

  if (tree==BOTHTREES)
    Error("Can not query both trees in GetRRTNNInBranch");
  
  cn=n2; /* current node */
  md=INF; /* minimum distance so far */
  *n=NO_UINT;
  *nn=NO_UINT;
  while((cn!=n1)||(cn==NO_UINT))
    {
      #if (_KDTREE==1)
      if (rrt->mode!=TWO_TREES_WITH_SWAP)
	{
	  if (tree==START2GOAL)
	    cnn=NearestNeighbour(rrt->si[cn]->samples,&cd,rrt->treeS2G);
	  else
	    /* tree==GOAL2START */
	    cnn=NearestNeighbour(rrt->si[cn]->samples,&cd,rrt->treeG2S);
	}
      else
      #endif
      #if (_KDTREE==2)
      if (rrt->mode!=TWO_TREES_WITH_SWAP)
	{
	  if (tree==START2GOAL)
	    {
	      QueryKDTree(rrt->si[cn]->samples,&cnn,&cd,rrt->treeS2G);
	      cnn=rrt->t1ToId[cnn];
	    }
	  else
	    {
	      /* tree==GOAL2START */
	      QueryKDTree(rrt->si[cn]->samples,&cnn,&cd,rrt->treeG2S);
	      cnn=rrt->t2ToId[cnn];
	    }
	}
      else
      #endif
	{
	  /* search without any kd-tree */
	  unsigned int j;
	  double d1;

	  cd=INF;
	  cnn=NO_UINT;
	  for(j=0;j<rrt->ns;j++)
	    {
	      if (rrt->si[j]->tree==tree)
		{
		  d1=WeightedDistanceTopologyMin(md,rrt->m,rrt->tp,rrt->weight,rrt->si[cn]->samples,rrt->si[j]->samples);
		  if (d1<cd)
		    {
		      cd=d1;
		      cnn=j;
		    }
		}
	    }
	}
    
      if (cd<md) /* current distance lower than the minimum so far */
	{
	  md=cd;
	  *n=cn;
	  *nn=cnn;
	}
      cn=rrt->si[cn]->parent;
    }
  
  if (cn==NO_UINT)
    Error("Wrongly delimited branch in GetRRTNNInBranch");
}

boolean AddNodeToRRT(Tparameters *pr,unsigned int tree,
		     unsigned int i_near,double *sample,
		     double *goal,unsigned int *lastSample,
		     void *info,double costp,double cost,boolean blocked,
		     double *u,double time,
		     unsigned int ns,double **path,double **actions,double *times,
		     TRRTStatistics *rst,Trrt *rrt)
{
  TRRTSampleInfo *si;

  #if (GET_RRT_STATISTICS)
    if (rst!=NULL)
      NewRRTSample(rst);
  #endif

  if (tree==BOTHTREES)
    Error("Samples must be assigned to a single tree in AddNodeToRRT");

  if (rrt->ns==rrt->ms)
    MEM_DUP(rrt->si,rrt->ms,TRRTSampleInfo *);

  NEW(rrt->si[rrt->ns],1,TRRTSampleInfo);
  si=rrt->si[rrt->ns];

  NEW(si->samples,rrt->m,double);
  memcpy(si->samples,sample,rrt->m*sizeof(double));
  if (rrt->tp!=NULL)
    ArrayPi2Pi(rrt->m,rrt->tp,si->samples);

  si->parent=i_near;
  si->userInfo=info;
  si->costp=costp;
  si->cost=cost;
  
  #if (PENALIZE_BLOCKED_NODES)
    si->blocked=(blocked?1.0:0.0);
    #if (PENALIZE_PARENT_NODES)
    {
      unsigned int i;
      double p;
      
      i=i_near;
      p=si->blocked;
      while(i!=NO_UINT)
	{
	  p/=2.0;
	  rrt->si[i]->blocked+=p;
	  i=rrt->si[i]->parent;
	}
    }
    #endif
  #else
    si->blocked=0.0;
  #endif
    
  if (u==NULL)
    {
      if (rrt->da>0)
	Error("Empty action in a dynamical system");
      si->u=NULL;
    }
  else
    {
      NEW(si->u,rrt->da,double);
      memcpy(si->u,u,sizeof(double)*rrt->da);
    }
  si->time=time;

  si->ns=ns;
  if (si->ns>0)
    {
      if (path==NULL)
	Error("Inconsistent path info in AddNodeToRRT");
      si->path=path;
      if ((actions!=NULL)&&(times!=NULL))
	{
	  if (rrt->da==0)
	    Error("Giving actions/times in a non-dynamical problem");
	  si->actions=actions;
	  si->times=times;
	}
      else
	{
	  if (rrt->da>0)
	    Error("Empty actions/times in AddNodeToRRT");
	  si->actions=NULL;
	  si->times=NULL;
	}
    }
  else
    {
      if (path!=NULL)
	DeleteTrajectory(ns,path,actions,times);
      si->path=NULL;
      si->actions=NULL;
      si->times=NULL;
    }
  
  si->ddr=0.0; /* dynamic domain set to 0 -> infty. */
  
  /* the tree of the node can be different from that of its parent!!
     This can happen when loading a BiRRT* that is not fully updated
     (see \ref UpdateCostAndPath) */
  si->tree=tree;

  #if (_KDTREE==1)
    if (rrt->mode==TWO_TREES)
      {	
	if (tree==START2GOAL)
	  AddPoint2KDtree(si->samples,rrt->ns,&(rrt->treeS2G));
	else
	  AddPoint2KDtree(si->samples,rrt->ns,&(rrt->treeG2S));
      }
    else
      AddPoint2KDtree(si->samples,rrt->ns,&(rrt->treeS2G));
  #endif

  #if (_KDTREE==2)
    if (rrt->mode==TWO_TREES)
      {
	if (tree==START2GOAL)
	  {
	    if (rrt->nodesT1==rrt->maxNodesT1)
	      MEM_DUP(rrt->t1ToId,rrt->maxNodesT1,unsigned int);
	    rrt->t1ToId[rrt->nodesT1]=rrt->ns;
	    rrt->nodesT1++;

	    AddPoint2KDTree(si->samples,rrt->treeS2G);
	  }
	else
	  {
	    /* tree is GOAL2START */
	    if (rrt->nodesT2==rrt->maxNodesT2)
	      MEM_DUP(rrt->t2ToId,rrt->maxNodesT2,unsigned int);
	    rrt->t2ToId[rrt->nodesT2]=rrt->ns;
	    rrt->nodesT2++;

	    AddPoint2KDTree(si->samples,rrt->treeG2S);
	  }
      }
    else
      AddPoint2KDTree(si->samples,rrt->treeS2G);
  #endif
    
  #if (RRT_VERBOSE)
    fprintf(stderr,"  New sample rrt %u dp:%f\n",rrt->ns,
	    DistanceTopology(rrt->m,rrt->tp,rrt->si[i_near]->samples,sample));
  #endif

  *lastSample=rrt->ns;
  rrt->ns++;

  if (rrt->graph)
    {
      si->g=INF;
      si->m=10; /* initial space for 10 neighbours (extended when necessary) */
      si->nn=0;
      NEW(si->n,si->m,unsigned int);
      NEW(si->cn,si->m,double);
      AddEdgeToRRT(*lastSample,i_near,costp,rrt);
    }

  if (goal!=NULL)
    return(DistanceTopology(rrt->m,rrt->tp,sample,goal)<GetParameter(CT_EPSILON,pr));
  else
    return(FALSE);
}

unsigned int AddStepToRRTstar(Tparameters *pr,unsigned int i_near,
			      double *q_rand,double *goal,
			      unsigned int *i_goal,
			      TRRTStatistics *rst,Trrt *rrt)
{
  double *q_next,d;
  unsigned int i_next;
  boolean goalFound,collision,reached;
  unsigned int tree;

  NEW(q_next,rrt->m,double);

  d=ConnectSamples(pr,rrt->tp,NULL,rrt->ambient,
		   rrt->m,rrt->n,rrt->si[i_near]->samples,q_rand,(double)INF,
		   TRUE,NULL,&reached,&collision,q_next,NULL,NULL,rrt->w);

  if (rrt->dd>0)
    AdjustDynamicDomain(i_near,collision,rrt);

  i_next=NO_UINT;

  tree=rrt->si[i_near]->tree; /* the sample is assigned to the tree of the nearest-node */

  if (d>0)
    {
      goalFound=AddNodeToRRT(pr,tree,i_near,q_next,goal,&i_next,NULL,
			     d,rrt->si[i_near]->cost+d,FALSE,NULL,0,
			     0,NULL,NULL,NULL,rst,rrt);

      if ((goal!=NULL)&&(i_goal!=NULL)&&(goalFound)&&(*i_goal==NO_UINT))
	{
	  /* The first time we are close enough to the goal we add the goal as a
	     node in the RRT */
	  double d,epsilon;

	  epsilon=GetParameter(CT_EPSILON,pr);
	  d=DistanceTopology(rrt->m,rrt->tp,q_next,goal);

	  if (d<epsilon)
	    *i_goal=i_next;
	  else
	    AddNodeToRRT(pr,tree,i_next,goal,goal,i_goal,NULL,d,
			 rrt->si[i_next]->cost+d,FALSE,NULL,0,
			 0,NULL,NULL,NULL,rst,rrt);
	  #if (RRT_VERBOSE)
	    fprintf(stderr,"     {%u->%u}[%g] **\n",*i_goal,rrt->si[*i_goal]->parent,
		    rrt->si[*i_goal]->costp);
	  #endif
	}
    }
  free(q_next);

  return(i_next);
}

void WireRRTstar(Tparameters *pr,unsigned int id_new,unsigned int i_near,
		 double gamma,unsigned int nn,unsigned int *n,double **c,
		 double h,Theap *q,unsigned int *t,
		 TRRTStatistics *rst,Trrt *rrt)
{
  unsigned int i;
  double ic,cn,c_new,epsilon,*q_new;
  boolean *reached;
  TRRTSampleInfo *sNew;
  TDoublePair pair;
  double *cost;

  epsilon=GetParameter(CT_EPSILON,pr);

  /*******************************************************************/
  /* Search for the lowest cost path to the new node */
  #if (RRT_VERBOSE)
    fprintf(stderr,"  Wire %u [nn:%u g:%g]\n",id_new,nn,gamma);
  #endif
  #if (RRTSTAR_SYMMETRIC_COST)
    if (!rrt->graph)
       NEW(*c,nn,double);
  #endif
  sNew=rrt->si[id_new];
  ic=sNew->costp; /*cost to i_near*/
  q_new=sNew->samples;
  *t=0; /* initially no tree in the set of neighbours */

  NEW(reached,nn,boolean);
  NEW(cost,nn,double);

  #pragma omp parallel for private(i) schedule(dynamic) if ((!omp_in_parallel())&&(rrt->parallel))
  for(i=0;i<nn;i++)
    {
      /* do not consider connection to itself */
      if (n[i]==id_new)
	reached[i]=FALSE;
      else
	{
	  if (n[i]==i_near)
	    {
	      /* we already know the connection to i_near */
	      cost[i]=ic;
	      reached[i]=TRUE;
	    }
	  else
	    {
	      boolean collision;

	      /* compute the connection to other samples */
	      cost[i]=ConnectSamples(pr,rrt->tp,NULL,rrt->ambient,
				     rrt->m,rrt->n,rrt->si[n[i]]->samples,q_new,gamma,
				     TRUE,NULL,&(reached[i]),&collision,NULL,NULL,NULL,rrt->w);
	    }
	}
    }

  for(i=0;i<nn;i++)
    {
      if (n[i]!=id_new)
	{
	  #if (GET_RRT_STATISTICS)
	    NewRRTBranch(rst);
	  #endif
	  (*t)|=rrt->si[n[i]]->tree; /* take note of the tree of this neighbour (even if not reached)*/
	}

      if (reached[i])
	{
	  cn=cost[i];

	  /* Ensure that cost and tree are correct before using this node */
	  /* This might be unnecessary when in graph mode (but it's cheap)  */
	  #if (GET_RRT_STATISTICS)
	    NewRRTNoEmptyBranch(rst);
	  #endif

	  #if (!RRTSTAR_UPDATE_COSTS)
	  if (rrt->mode==TWO_TREES_WITH_SWAP)
	  #endif
	    UpdateCostAndTree(n[i],rrt);

	  /* Add a bidirectional edge with the given cost. */
	  if (rrt->graph)
	    AddEdgeToRRT(id_new,n[i],cn,rrt);

	  c_new=rrt->si[n[i]]->cost+cn;
	  if (c_new<(sNew->cost-epsilon))
	    {
              #if (RRT_VERBOSE)
	        fprintf(stderr,"     {%u->%u}[%g] ->",id_new,sNew->parent,sNew->costp);
              #endif

	      SetRRTCostAndParent(id_new,n[i],cn,c_new,rrt);

	      #if (RRT_VERBOSE)
		fprintf(stderr,"{%u->%u}[%g]\n",id_new,sNew->parent,sNew->costp);
	      #endif
	    }
	}
      else
	cn=INF;

      #if (RRTSTAR_SYMMETRIC_COST)
        if (!rrt->graph) /* if graph, the cost are already stored in the graph edges. */
	  (*c)[i]=cn;
      #endif
    }
  free(reached);
  free(cost);

  if (rrt->graph)
    {
      if (!q)
	Error("RRT must be in graph mode to use a heap");
      c_new=rrt->si[id_new]->cost;
      NewDoublePair(c_new+h,c_new,&pair);
      AddElement2Heap(id_new,(void *)&pair,q);
    }
}

void RecursiveReWireRRTstar(Tparameters *pr,Theap *q,double *g,
			    Tvector *steps,double *l,
			    Trrt *rrt)
{
  unsigned int id_new,i;
  double c_new,epsilon,ct;
  TRRTSampleInfo *sNew,*sNear;
  TDoublePair pair;

  if (!rrt->graph)
    Error("RecursiveReWireRRTstar can only be used if RRT in graph mode");

  epsilon=GetParameter(CT_EPSILON,pr);

  #if (RRT_VERBOSE)
    fprintf(stderr,"  Rewire\n");
  #endif
  while ((!HeapEmpty(q))&&(FirstInPair((TDoublePair *)GetHeapElement(0,q))<=(*l)))
    {
      id_new=ExtractMinElement(&pair,q);
      if (id_new==NO_UINT)
	Error("Reading an inconsistent node from the priority queue in RecursiveReWireRRTstar");

      sNew=rrt->si[id_new];
      sNew->g=sNew->cost; /* convert the node to stationary */

      for(i=0;i<sNew->nn;i++)
	{
	  sNear=rrt->si[sNew->n[i]];

	  /* ensure that cost and tree are correct before using this node. This is already updated
	     in the wire but might change during the re-wire */
	  if (rrt->mode==TWO_TREES_WITH_SWAP)
	    UpdateCostAndTree(sNew->n[i],rrt);

	  /* cost to n[i] via id_new */
	  c_new=sNew->cost+sNew->cn[i];
	  if (c_new<(sNear->cost-epsilon)) /* recall that here, cost = rhs */
	    {
	      #if (RRT_VERBOSE)
	        fprintf(stderr,"     {%u->%u}[%g %g] ->",sNew->n[i],sNear->parent,sNear->costp,sNear->cost);
	      #endif

	      /* sets 'rhs' (cost) but not 'g' -> inconsistent node */
	      SetRRTCostAndParent(sNew->n[i],id_new,sNew->cn[i],c_new,rrt);

	      ct=sNear->cost+DistanceTopology(rrt->m,rrt->tp,sNear->samples,g);
	      NewDoublePair(ct,sNear->cost,&pair);
	      UpdateHeapElement(sNew->n[i],(void *)&pair,q); /* updates/adds */

	      #if (RRT_VERBOSE)
	        fprintf(stderr,"{%u->%u}[%g %g]\n",sNew->n[i],sNear->parent,sNear->costp,sNear->cost);
	      #endif
	    }
	  else
	    {
	      /* if the node is connected to a sample in a different tree, update the optimal path */
	      if ((rrt->mode==TWO_TREES_WITH_SWAP)&&(steps!=NULL)&&(sNear->tree!=sNew->tree))
		{
		  c_new+=sNear->cost; /* Total cost of start<->goal via this connection between trees.*/
		  if (c_new<*l)
		    *l=ChangeBiRRTSteps(sNew->n[i],id_new,sNew->cn[i],steps,rrt);
		}
	    }
	}
    }
}

void ReWireRRTstar(Tparameters *pr,
		   unsigned int id_new,double gamma,
		   unsigned int nn,unsigned int *n,double *c,
		   Tvector *steps,double *l,
		   Trrt *rrt)
{
  unsigned int i,parent;
  boolean reached;
  double cn,c_new,epsilon;
  TRRTSampleInfo *sNew,*sNear;
  #if (!RRTSTAR_SYMMETRIC_COST)
    double *q_new;
    boolean collision;
  #endif

  if (rrt->graph)
    Error("ReWireRRTstar must not be used if the RRT is in graph  mode");

  epsilon=GetParameter(CT_EPSILON,pr);

  #if (RRT_VERBOSE)
    fprintf(stderr,"  Rewire\n");
  #endif
  sNew=rrt->si[id_new];
  #if (!RRTSTAR_SYMMETRIC_COST)
    /* if symmetric costs -> cost to neighbours given as parameters */
    q_new=sNew->samples;
  #endif
  parent=sNew->parent;
  for(i=0;i<nn;i++)
    {
      sNear=rrt->si[n[i]];

      /* There is no need to re-wire the best parent of the new node
	 (it will produce an inf. loop) or the new node itself. */
      if ((n[i]==id_new)||(n[i]==parent))
	reached=FALSE;
      else
	{
	  #if (RRTSTAR_SYMMETRIC_COST)
	    cn=c[i];
	    reached=(cn<INF);
	  #else
	    cn=ConnectSamples(pr,rrt->tp,NULL,rrt->ambient,
			      rrt->m,rrt->n,q_new,sNear->samples,gamma,
			      TRUE,NULL,&reached,&collision,NULL,NULL,NULL,rrt->w);
	  #endif
	}

      if (reached)
	{
	  /* Ensure that any previous-rewire is propagated to the currently tested node */
	  if (rrt->mode==TWO_TREES_WITH_SWAP)
	    UpdateCostAndTree(n[i],rrt);

	  c_new=sNew->cost+cn;
	  if (c_new<sNear->cost-epsilon)
	    {
	      #if (RRT_VERBOSE)
	        fprintf(stderr,"     {%u->%u}[%g] ->",n[i],sNear->parent,sNear->costp);
	      #endif

	      SetRRTCostAndParent(n[i],id_new,cn,c_new,rrt);

	      #if (RRT_VERBOSE)
	        fprintf(stderr,"{%u->%u}[%g]\n",n[i],sNear->parent,sNear->costp);
	      #endif
	    }
	  else
	    {
	      /* if the node is connected to a sample in a different tree, update the optimal path */
	      if ((rrt->mode==TWO_TREES_WITH_SWAP)&&(steps!=NULL)&&(l!=NULL)&&(sNear->tree!=sNew->tree))
		{
		  c_new+=sNear->cost; /* Total cost of start<->goal via this connection between trees.*/
		  if (c_new<*l)
		    *l=ChangeBiRRTSteps(n[i],id_new,cn,steps,rrt);
		}
	    }
	}
    }
}

void RRTstarCloseIteration(unsigned int it,unsigned int id_goal,
			   double time,double gamma,
			   double *times,double *costs,
			   Trrt *rrt)
{
  if ((RRT_VERBOSE)||((it%1000)==0))
    {
      if (id_goal!=NO_UINT)
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g g:%g c:%g [%g])\n",it,rrt->ns,time,gamma,
		  rrt->si[id_goal]->cost,CostToRoot(id_goal,rrt));
	}
      else
	fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,rrt->ns,time);
      fflush(stdout);
    }

  if (times!=NULL)
    times[it]=time;

  if (costs!=NULL)
    {
      if (id_goal==NO_UINT)
	costs[it]=-1.0;
      else
	costs[it]=rrt->si[id_goal]->cost; //CostToRoot(id_goal,rrt);
    }
}

void BiRRTstarCloseIteration(unsigned int it,double l,
			     double time,double gamma,
			     double *times,double *costs,
			     Trrt *rrt)
{
  if ((RRT_VERBOSE)||((it%1000)==0))
    {
      if (l<INF)
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g g:%g c:%g)\n",it,rrt->ns,time,gamma,l);
	}
      else
	fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,rrt->ns,time);
      fflush(stdout);
    }

  if (times!=NULL)
    times[it]=time;

  if (costs!=NULL)
    {
      if (l<INF)
	costs[it]=-1.0;
      else
	costs[it]=l;
    }
}

boolean RRTstar(Tparameters *pr,double *pg,
		unsigned int *it,double *times,double *costs,
		double *planningTime,double *pl,unsigned int *ns,double ***path,
		TRRTStatistics *grst,Trrt *rrt)
{
  if (EXPLORATION_RRT)
    Error("RRTstar is not designed for exploration RRTs");

  if (rrt->mode!=ONE_TREE)
    return(BiRRTstar(pr,pg,it,times,costs,planningTime,pl,ns,path,grst,rrt));
  else
    {
      double *pWithDummies,*pgs,*q_rand;
      unsigned int samplingMode;
      unsigned int i_near;
      double epsilon;
      boolean expand2Goal;
      double er;
      Tstatistics st; /* used just to measure execution time */
      boolean collision;
      double time;
      double *c; /* if the cost function is symmetrical, we cache
		    the evaluation of the cost to neighbour. */
      /* neighbours for each new node */
      unsigned int nn;
      unsigned int *n;
      /* distance q_rand,tree */
      double gamma,ct_gamma;
      unsigned int i,id_new,id_goal;
      double *q_new;
      boolean done,optimal,validSample;
      double maxTime;
      unsigned int maxIterations;
      double h,l;
      Theap q;
      unsigned int vt; /* trees in  set of neighbours, only relevant in bi-RRTs */
      unsigned int numSamples;
      TRRTStatistics *rst;

      if (rrt->ns>1)
	Error("RRTstart must be used to a just initilized RRT");

      #if (GET_RRT_STATISTICS)
      {
	unsigned int i;

	NEW(rst,1,TRRTStatistics);
	InitRRTStatistics(rst);

	for(i=0;i<rrt->ns;i++)
	  NewRRTSample(rst);
      }
      #endif

      /* Init the RRT structure */
      epsilon=GetParameter(CT_EPSILON,pr);
      ct_gamma=GetParameter(CT_GAMMA,pr);
      maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
      maxIterations=(unsigned int)GetParameter(CT_MAX_PLANNING_ITERATIONS,pr);
      samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);


      CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,rrt->w);
      CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,rrt->w);

      if ((!PointInBoxTopology(NULL,TRUE,rrt->m,pgs,epsilon,rrt->tp,rrt->ambient))||
	  (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,rrt->w)))
	Error("The targed point for the RRTstar is not in domain");

      if (rrt->n==0)
	er=0;
      else
	er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,rrt->w);
      if (er>epsilon)
	Error("The target point for the RRTstar is not on the manifold");

      collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,rrt->w);
      if (collision)
	Error("The target point for the RRTstar is in collision");
      free(pWithDummies);

      /* Room for the randomly generated samples (and its correspoinding point
	 on the manifold) */
      NEW(q_rand,rrt->m,double);

      /* Reset the output statistics (just in case maxIterations
	 is not reached) */
      for(i=0;i<maxIterations;i++)
	{
	  times[i]=0;
	  costs[i]=-1;
	}

      if (rrt->graph)
	InitHeap(sizeof(TDoublePair),CopyDoublePair,DeleteDoublePair,
		 LessThanDoublePair,NULL,TRUE,rrt->ms,&q);

      gamma=ct_gamma;
      optimal=(gamma>0.0);

      id_goal=NO_UINT;
      *it=0;

      InitStatistics(rrt->nCores,0,&st);
      time=0.0;
      done=FALSE;
      l=INF; /* cost to goal (INF while goal not found) */
      c=NULL; /* default -> no cache of costs to neighbours */

      while ((!done)&&(time<maxTime)&&(*it<maxIterations))
	{
	  #if (HEURISTIC_RRT_STAR&(1))
	    /* keep the cost to goal up to date so that the heuristic
	       is more effective*/
	    if (id_goal!=NO_UINT)
	      UpdateCostAndTree(id_goal,rrt);
	  #endif
	  /*******************************************************************/
	  /* best estimation of the cost to goal (up to now) */
	  if (id_goal==NO_UINT)
	    l=INF;
	  else
	    l=rrt->si[id_goal]->cost;

	  /*******************************************************************/
	  /* Random sample */
	  do {
	    /* Generate a random sample */
	    expand2Goal=RRTSample(samplingMode,START2GOAL,(id_goal==NO_UINT?pgs:NULL),
				  q_rand,rst,rrt);

	    /* Check if the sample is valid */
	    validSample=RRTValidateSample(pr,q_rand,START2GOAL,expand2Goal,pgs,l,
					  &h,&i_near,rst,rrt);
	    time=GetElapsedTime(&st);
	  } while((!validSample)&&(time<maxTime));

	  if (time<maxTime)
	    {
	      /*******************************************************************/
	      /* Extend the RRT from q_near to q_rand using the cbiRRT extend method */
	      /* Note that here we try to reach q_rand but we do not add samples along the path */
	      id_new=AddStepToRRTstar(pr,i_near,q_rand,pgs,&id_goal,rst,rrt);

	      /*******************************************************************/
	      if (!optimal)
		{
		  if (id_goal!=NO_UINT)
		    done=TRUE;
		}
	      else
		{
		  /* If we actually added something */
		  if ((id_new!=NO_UINT)&&((((HEURISTIC_RRT_STAR)&(2))==0)||(id_goal!=NO_UINT)))
		    {
		      /* q_new is the last sample added to the tree */
		      q_new=rrt->si[id_new]->samples;
		      h=DistanceTopology(rrt->m,rrt->tp,q_new,pgs);

		      /*******************************************************************/
		      /* Search for the set of potential neighbours */
		      numSamples=(rrt->ns<3?3:rrt->ns);
		      gamma=ct_gamma*pow(log(numSamples)/numSamples,1/(double)rrt->k);
		      gamma=(gamma<rrt->delta?rrt->delta:gamma);

		      GetRRTNNInBall(START2GOAL,q_new,gamma,&nn,&n,rrt);

		      /*******************************************************************/
		      /* Wire: Search for the lowest cost path to the new node */
		      WireRRTstar(pr,id_new,i_near,gamma,nn,n,&c,h,(rrt->graph?&q:NULL),&vt,rst,rrt);

		      /*******************************************************************/
		      /* Rewire the tree around the new point */
		      if (rrt->graph)
			RecursiveReWireRRTstar(pr,&q,pgs,NULL,&l,rrt);
		      else
			ReWireRRTstar(pr,id_new,gamma,nn,n,c,NULL,&l,rrt);

		      /*******************************************************************/
		      /* release the data (cost (if actually used) and neighbours) */
		      if (c!=NULL)
			free(c);
		      free(n);
		    }
		  #if (RRT_VERBOSE)
		  else
		    {
		      if (id_new==NO_UINT)
			fprintf(stderr,"  Blocked [%u]\n",i_near);
		    }
		  #endif
		}

	      /*******************************************************************/
	      /* Conclude the iteration */
	      time=GetElapsedTime(&st);

	      RRTstarCloseIteration(*it,id_goal,time,gamma,times,costs,rrt);

	      (*it)++;
	    }
	}

      DeleteStatistics(&st);
      #if (GET_RRT_STATISTICS)
        if (grst==NULL)
	  PrintRRTStatistics(rrt,rst);
	else
	  AccumulateRRTStatistics(rst,grst);
	DeleteRRTStatistics(rst);
	free(rst);
      #endif

      if (rrt->graph)
	DeleteHeap(&q);

      *planningTime=GetElapsedTime(&st);

      fprintf(stderr,"Final number of samples: %u\n",rrt->ns);

      /* Reconstruct the path (if any) */
      if (id_goal!=NO_UINT)
	ReconstructRRTPath(pr,id_goal,pl,NULL,ns,path,NULL,NULL,rrt);


      /* Release memory */
      free(q_rand);
      free(pgs);

      return(id_goal!=NO_UINT);
    }
}

boolean BiRRTstar(Tparameters *pr,double *pg,
		  unsigned int *it,double *times,double *costs,
		  double *planningTime,double *pl,unsigned int *ns,double ***path,
		  TRRTStatistics *grst,Trrt *rrt)
{
  if (EXPLORATION_RRT)
    Error("RRTstar is not designed for exploration RRTs");

  if (rrt->mode!=TWO_TREES_WITH_SWAP)
    {
      if (rrt->mode!=ONE_TREE)
	Error("RRTstar operates on two-directional RRTs");

      return(RRTstar(pr,pg,it,times,costs,planningTime,pl,ns,path,grst,rrt));
    }
  else
    {
      double *q_rand,*g;
      unsigned int i_near;
      Tstatistics st; /* used just to measure execution time */
      double time;
      double *c; /* if the cost function is symmetrical, we cache
		    the evaluation of the cost to neighbour. */
      /* neighbours for each new node */
      unsigned int nn;
      unsigned int *n;
      /* distance q_rand,tree */
      double gamma,ct_gamma;
      unsigned int i,id_new;
      double *q_new;
      boolean done,optimal,validSample;
      double l;           /* length of the shortest path so far */
      Tvector steps;
      double maxTime;
      unsigned int maxIterations,samplingMode;
      Theap q;
      double h;
      unsigned int vt; /* trees in the set of neighbours. */
      unsigned int numSamples;
      double l1,c12;
      boolean connected,collision;
      TRRTStatistics *rst;

      if (rrt->ns>2)
	Error("RRTstart must be used to a just initilized RRT");

      #if (GET_RRT_STATISTICS)
      {
	unsigned int i;

	NEW(rst,1,TRRTStatistics);
	InitRRTStatistics(rst);

	for(i=0;i<rrt->ns;i++)
	  NewRRTSample(rst);
      }
      #endif

      /* Init the RRT structure */
      ct_gamma=GetParameter(CT_GAMMA,pr);
      maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
      maxIterations=(unsigned int)GetParameter(CT_MAX_PLANNING_ITERATIONS,pr);
      /* for BiRRTStart the sampling mode should be "ambient_sampling" but we accept
         other modes just for the sake of completeness. */
      samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

      /* Room for the randomly generated samples (and its correspoinding point
	 on the manifold) */
      NEW(q_rand,rrt->m,double);

      /* Reset the output statistics (just in case maxIterations
	 is not reached) */
      for(i=0;i<maxIterations;i++)
	{
	  times[i]=0;
	  costs[i]=-1;
	}

      if (rrt->graph)
	InitHeap(sizeof(TDoublePair),CopyDoublePair,DeleteDoublePair,
		 LessThanDoublePair,NULL,TRUE,rrt->ms,&q);

      gamma=ct_gamma;
      optimal=(gamma>0.0);

      *it=0;

      InitStatistics(rrt->nCores,0,&st);
      time=0.0;
      done=FALSE;

      InitVector(sizeof(TRRTStep),CopyRRTStep,NULL,100,&steps);
      l=INF;
      c=NULL; /* default not to use cache of cost to neighbours */

      while ((!done)&&(time<maxTime)&&(*it<maxIterations))
	{
	  /* Keep the current path up to date (if any) */
	  if (l<INF)
	    l=UpdateBiRRTSteps(&steps,rrt);

	  /*******************************************************************/
	  do {
	    /* Generate a random sample */
	    RRTSample(samplingMode,BOTHTREES,NULL,q_rand,rst,rrt);

	    /* Check if the sample is valid */
	    validSample=RRTValidateSample(pr,q_rand,BOTHTREES,FALSE,rrt->si[1]->samples,l,
					  &h,&i_near,rst,rrt);
	    time=GetElapsedTime(&st);
	  } while((!validSample)&&(time<maxTime));

	  if (time<maxTime)
	    {
	      /*******************************************************************/
	      /* heuristic w.r.t distance from q_rand to goal */
	      if (rrt->si[i_near]->tree==START2GOAL)
		g=rrt->si[1]->samples;
	      else
		g=rrt->si[0]->samples;
	      h=DistanceTopology(rrt->m,rrt->tp,q_rand,g);

	      /*******************************************************************/
	      /* Extend the RRT from q_near to q_rand using the cbiRRT extend method */
	      /* Note that here we use a extend strategy (we only add one sample) */

	      id_new=AddStepToRRTstar(pr,i_near,q_rand,NULL,NULL,rst,rrt);

	      /* If we actually added something */
	      if ((id_new!=NO_UINT)&&((((HEURISTIC_RRT_STAR)&(2))==0)||(l<INF)))
		{
		  /* q_new is the last samples added to the tree */
		  q_new=rrt->si[id_new]->samples;
		  h=DistanceTopology(rrt->m,rrt->tp,q_new,g);

		  /*******************************************************************/
		  /* Search for the set of potential neighbours */
		  numSamples=(rrt->ns<3?3:rrt->ns);
		  gamma=ct_gamma*pow(log(numSamples)/numSamples,1/(double)rrt->k);
		  gamma=(gamma<rrt->delta?rrt->delta:gamma);

		  GetRRTNNInBall(BOTHTREES,q_new,gamma,&nn,&n,rrt);

		  /*******************************************************************/
		  /* Wire: Search for the lowest cost path to the new node */
		  WireRRTstar(pr,id_new,i_near,gamma,nn,n,&c,h,(rrt->graph?&q:NULL),&vt,rst,rrt);

		  /*******************************************************************/
		  /* Rewire the tree around the new point */
		  if (rrt->graph)
		    RecursiveReWireRRTstar(pr,&q,g,&steps,&l,rrt);
		  else
		    ReWireRRTstar(pr,id_new,gamma,nn,n,c,&steps,&l,rrt);

		  /*******************************************************************/
		  /* release the data (cost (if actually used) and neighbours) */
		  if (c!=NULL)
		    free(c);
		  free(n);

		  /*******************************************************************/
		  /* If the set of neighbours does not include nodes in the two trees
		     and we do not have a path start<->goal we try to connect the two
		     trees (this is hardly used since when l=INF, gamma is large and
		     the neighbours always include nodes in the two trees) */
		  //if ((vt!=BOTHTREES)&&(l==INF))
		  if (vt!=BOTHTREES)
		    {
		      /* In the re-wire the current sample might end up in tree 't2'
			 and the connection must be always with the other tree */
		      if (rrt->si[id_new]->tree==START2GOAL)
			i_near=GetRRTNN(GOAL2START,q_new,rrt);
		      else
			i_near=GetRRTNN(START2GOAL,q_new,rrt);

		      l1=rrt->si[id_new]->cost+rrt->si[i_near]->cost;
		      c12=ConnectSamples(pr,rrt->tp,NULL,rrt->ambient,
					 rrt->m,rrt->n,q_new,rrt->si[i_near]->samples,l-l1,
					 TRUE,NULL,&connected,&collision,NULL,NULL,NULL,rrt->w);
		      if (connected)
			{
			  if (rrt->graph)
			    AddEdgeToRRT(id_new,i_near,c12,rrt);
			  l1+=c12;
			  if (l1<l)
			    l=ChangeBiRRTSteps(id_new,i_near,c12,&steps,rrt);
			}
		    }
		}
	      #if (RRT_VERBOSE)
	      else
		{
		  if (id_new==NO_UINT)
		    fprintf(stderr,"  Blocked [%u]\n",i_near);
		}
	      #endif

	      if (!optimal)
		done=(l<INF);

	      /*******************************************************************/
	      /* Conclude the iteration */
	      time=GetElapsedTime(&st);

	      BiRRTstarCloseIteration(*it,l,time,gamma,times,costs,rrt);

	      (*it)++;
	    }
	}

      DeleteStatistics(&st);
      #if (GET_RRT_STATISTICS)
        if (grst==NULL)
	  PrintRRTStatistics(rrt,rst);
	else
	  AccumulateRRTStatistics(rst,grst);
	DeleteRRTStatistics(rst);
	free(rst);
      #endif

      if (rrt->graph)
	DeleteHeap(&q);

      *planningTime=GetElapsedTime(&st);

      fprintf(stderr,"Final number of samples: %u\n",rrt->ns);

      /* Reconstruct the path (if any) */
      if (l<INF)
	Steps2PathinRRT(pr,&steps,pl,NULL,ns,path,NULL,NULL,rrt);

      /* Release memory */
      free(q_rand);
      DeleteVector(&steps);

      return(l<INF);
    }
}

boolean ccTRRT(Tparameters *pr,double *pg,double *time,
	       double *pl, double* pc, unsigned int *ns,double ***path,
	       double (*costF)(Tparameters*,boolean,double*,void*),
	       void *costData,
	       TRRTStatistics *grst,Trrt *rrt)
{
  double *pWithDummies,*pgs,*q_rand;
  unsigned int it,i_near;
  double epsilon;
  boolean pathFound,done,expand2Goal;
  unsigned int lastSample;
  double er,h;
  Tstatistics st; /* used just to measure execution time */
  boolean collision;
  double maxTime;
  unsigned int maxNodes;
  unsigned int samplingMode;
  boolean validSample;
  TRRTStatistics *rst;

  if(rrt->ns >1)
    Error("ccTRRT should only be initialized with the start config");

  if (rrt->mode!=ONE_TREE)
    Error("ccTRRT operates on one-directional RRTs");

  #if (GET_RRT_STATISTICS)
  {
    unsigned int i;

    NEW(rst,1,TRRTStatistics);
    InitRRTStatistics(rst);

    for(i=0;i<rrt->ns;i++)
      NewRRTSample(rst);
  }
  #endif

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,rrt->w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,rrt->w);

  if ((!PointInBoxTopology(NULL,TRUE,rrt->m,pgs,epsilon,rrt->tp,rrt->ambient))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,rrt->w)))
    Error("The targed point for the ccRRT is not in domain");

  if (rrt->n==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,rrt->w);
  if (er>epsilon)
    Error("The target point for the ccRRT is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,rrt->w);
  if (collision)
    Warning("The target point for the ccRRT is in collision");
  free(pWithDummies);

  /*init the cost of the first node*/
  rrt->si[0]->cost=costF(pr,TRUE,GetRRTNode(0,rrt),costData);

  /* Room for the randomly generated samples (and its correspoinding point
     on the manifold) */
  NEW(q_rand,rrt->m,double);

  done=FALSE;
  it=0;

  InitStatistics(rrt->nCores,0,&st);
  *time=0.0;

  while ((!done)&&(*time<maxTime)&&(rrt->ns<maxNodes))
    {
      if ((RRT_VERBOSE)||((it%1000)==0))
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,rrt->ns,*time);
	  fflush(stdout);
	}

      /*******************************************************************/
      /* Sample in ambient space (with bias toward goal) */
      do {
	/* Generate a random sample */
	expand2Goal=RRTSample(samplingMode,START2GOAL,(EXPLORATION_RRT?NULL:pgs),
			      q_rand,rst,rrt);

	/* Check if the sample is valid */
	validSample=RRTValidateSample(pr,q_rand,START2GOAL,expand2Goal,NULL,INF,
				      &h,&i_near,rst,rrt);

	*time=GetElapsedTime(&st);
      } while((!validSample)&&(*time<maxTime));

      if (*time<maxTime)
	{
	  /*******************************************************************/
	  /* Extend the RRT from q_near to q_rand using the ccRRT extend method */

	  #if (GET_RRT_STATISTICS)
	    NewRRTBranch(rst);
	    NewRRTDistanceQrand(DistanceTopology(rrt->m,rrt->tp,rrt->si[i_near]->samples,q_rand),rst);
	  #endif
	  done=AddBranchToRRT(pr,TRUE,START2GOAL,i_near,q_rand,pgs,&lastSample,
			      costF,costData,rst,rrt);
	  #if (GET_RRT_STATISTICS)
	    if (lastSample!=i_near)
	      NewRRTNoEmptyBranch(rst);
	  #endif

	  *time=GetElapsedTime(&st);
	  it++;
	}
    }

  fprintf(stderr,"Final number of samples: %u\n",rrt->ns);

  /* Reconstruct the path (if any) */
  pathFound=PathStart2GoalInRRT(pr,pgs,NO_UINT,NO_UINT,pl,pc,ns,path,NULL,NULL,rrt);
  if((pathFound)&&(!EXPLORATION_RRT))
    rrt->si[rrt->ns-1]->cost=costF(pr,TRUE,GetRRTNode(rrt->ns-1,rrt),costData);

  /* Release memory */
  DeleteStatistics(&st);
  #if (GET_RRT_STATISTICS)
    if (grst==NULL)
      PrintRRTStatistics(rrt,rst);
    else
      AccumulateRRTStatistics(rst,grst);
    DeleteRRTStatistics(rst);
    free(rst);
  #endif

  free(q_rand);
  free(pgs);

  return(pathFound);
}

boolean ccRRT(Tparameters *pr,double *pg,
	      double *time,
	      double *pl,unsigned int *ns,double ***path,
	      TRRTStatistics *grst,Trrt *rrt)
{
  double *pWithDummies,*pgs,*q_rand;
  unsigned int it,i_near;
  double epsilon;
  boolean pathFound,done,expand2Goal;
  unsigned int lastSample;
  double er,h;
  Tstatistics st; /* used just to measure execution time */
  boolean collision;
  double maxTime;
  unsigned int maxNodes;
  unsigned int samplingMode;
  boolean validSample;
  TRRTStatistics *rst;

  if (rrt->mode!=ONE_TREE)
    Error("ccRRT operates on one-directional RRTs");

  #if (GET_RRT_STATISTICS)
  {
    unsigned int i;

    NEW(rst,1,TRRTStatistics);
    InitRRTStatistics(rst);

    for(i=0;i<rrt->ns;i++)
      NewRRTSample(rst);
  }
  #endif

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  maxNodes=(unsigned int)GetParameter(CT_MAX_NODES_RRT,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,rrt->w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,rrt->w);

  if ((!PointInBoxTopology(NULL,TRUE,rrt->m,pgs,epsilon,rrt->tp,rrt->ambient))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,rrt->w)))
    Error("The targed point for the ccRRT is not in domain");

  if (rrt->n==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,rrt->w);
  if (er>epsilon)
    Error("The target point for the ccRRT is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,rrt->w);
  if (collision)
    Warning("The target point for the ccRRT is in collision");
  free(pWithDummies);

  /* Room for the randomly generated samples (and its correspoinding point
     on the manifold) */
  NEW(q_rand,rrt->m,double);

  done=FALSE;
  it=0;

  InitStatistics(rrt->nCores,0,&st);
  *time=0.0;

  while ((!done)&&(*time<maxTime)&&(rrt->ns<maxNodes))
    {
      if ((RRT_VERBOSE)||((it%1000)==0))
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,rrt->ns,*time);
	  fflush(stdout);
	}

      /*******************************************************************/
      /* Sample in ambient space (with bias toward goal) */
      do {
	/* Generate a random sample */
	expand2Goal=RRTSample(samplingMode,START2GOAL,(EXPLORATION_RRT?NULL:pgs),
			      q_rand,rst,rrt);

	/* Check the sample is valid */
	validSample=RRTValidateSample(pr,q_rand,START2GOAL,expand2Goal,NULL,INF,
				      &h,&i_near,rst,rrt);

      	*time=GetElapsedTime(&st);
      } while((!validSample)&&(*time<maxTime));

      if (*time<maxTime)
	{
	  /*******************************************************************/
	  /* Extend the RRT from q_near to q_rand using the ccRRT extend method */
	  #if (GET_RRT_STATISTICS)
	    NewRRTBranch(rst);
	    NewRRTDistanceQrand(DistanceTopology(rrt->m,rrt->tp,rrt->si[i_near]->samples,q_rand),rst);
	  #endif
	  done=AddBranchToRRT(pr,TRUE,START2GOAL,i_near,q_rand,pgs,&lastSample,
			      NULL,NULL,rst,rrt);
	  #if (GET_RRT_STATISTICS)
	    if (lastSample!=i_near)
	      NewRRTNoEmptyBranch(rst);
	  #endif

	  *time=GetElapsedTime(&st);
	  it++;
	}
    }

  fprintf(stderr,"Final number of samples: %u\n",rrt->ns);

  /* Reconstruct the path (if any) */
  pathFound=PathStart2GoalInRRT(pr,pgs,NO_UINT,NO_UINT,pl,NULL,ns,path,NULL,NULL,rrt);

  /* Release memory */
  DeleteStatistics(&st);
  #if (GET_RRT_STATISTICS)
    if (grst==NULL)
      PrintRRTStatistics(rrt,rst);
    else
      AccumulateRRTStatistics(rst,grst);
    DeleteRRTStatistics(rst);
    free(rst);
  #endif

  free(q_rand);
  free(pgs);

  return(pathFound);
}

boolean cBiRRT(Tparameters *pr,double *pg,
	       double *time,
	       double *pl,unsigned int *ns,double ***path,
	       TRRTStatistics *grst,Trrt *rrt)
{
  double *pWithDummies,*pgs,*q_rand;
  unsigned int it,i_near;
  double epsilon;
  boolean pathFound;
  double er,h;
  unsigned int t1,t2;
  unsigned int lastSample1;
  unsigned int samplingMode;
  Tstatistics st; /* used just to measure execution time */
  boolean collision;
  unsigned int lastSample2;
  double maxTime;
  boolean validSample;
  TRRTStatistics *rst;

  #if (EXPLORATION_RRT)
    Error("cBiRRT can not be used in exploration mode.");
  #endif

  if (rrt->mode!=TWO_TREES)
    Error("cBiRRT operates on bidirectional RRTs");

  #if (GET_RRT_STATISTICS)
  {
    unsigned int i;

    NEW(rst,1,TRRTStatistics);
    InitRRTStatistics(rst);

    for(i=0;i<rrt->ns;i++)
      NewRRTSample(rst);
  }
  #endif

  /* Init the RRT structure */
  epsilon=GetParameter(CT_EPSILON,pr);
  maxTime=GetParameter(CT_MAX_PLANNING_TIME,pr);
  samplingMode=(unsigned int)GetParameter(CT_SAMPLING,pr);

  CS_WD_REGENERATE_SOLUTION_POINT(pr,pg,&pWithDummies,rrt->w);
  CS_WD_GENERATE_SIMPLIFIED_POINT(pr,pWithDummies,&pgs,rrt->w);

  if ((!PointInBoxTopology(NULL,TRUE,rrt->m,pgs,epsilon,rrt->tp,rrt->ambient))||
      (!CS_WD_SIMP_INEQUALITIES_HOLD(pr,pgs,rrt->w)))
    Error("The targed point is not in domain");

  if (rrt->n==0)
    er=0;
  else
    er=CS_WD_ERROR_IN_SIMP_EQUATIONS(pr,pgs,rrt->w);
  if (er>epsilon)
    Error("The target point for the RRT is not on the manifold");

  collision=CS_WD_ORIGINAL_IN_COLLISION(pr,pWithDummies,NULL,rrt->w);
  if (collision)
    Warning("The target point for the RRT is in collision");
  free(pWithDummies);

  /* Room for the randomly generated samples (and its correspoinding point
     on the manifold) */
  NEW(q_rand,rrt->m,double);

  pathFound=FALSE;
  it=0;

  /* The two trees. This is only used for bidirectiononal RRTs. In norma
     RRTs only the START2GOAL tree is extended*/
  t1=START2GOAL;
  t2=GOAL2START;

  InitStatistics(rrt->nCores,0,&st);
  *time=0.0;

  while ((!pathFound)&&(*time<maxTime))
    {
      if ((RRT_VERBOSE)||((it%1000)==0))
	{
	  fprintf(stderr,"Iteration: %u (s:%u t:%g)\n",it,rrt->ns,*time);
	  fflush(stdout);
	}

      /*******************************************************************/
      /* Sample */
      do {
	/* Generate a random sample */
	RRTSample(samplingMode,t1,NULL,q_rand,rst,rrt);

	/* Check the sample is valid */
	validSample=RRTValidateSample(pr,q_rand,t1,FALSE,NULL,INF,
				      &h,&i_near,rst,rrt);

     	*time=GetElapsedTime(&st);
      } while((!validSample)&&(*time<maxTime));

      if (*time<maxTime)
	{
	  /*******************************************************************/
	  /* Extend the first tree from q_near toward q_rand */
	  #if (GET_RRT_STATISTICS)
	    NewRRTBranch(rst);
	    NewRRTDistanceQrand(DistanceTopology(rrt->m,rrt->tp,rrt->si[i_near]->samples,q_rand),rst);
	  #endif
	  AddBranchToRRT(pr,FALSE,t1,i_near,q_rand,q_rand,&lastSample1,
			 NULL,NULL,rst,rrt);
	  #if (GET_RRT_STATISTICS)
	    if (lastSample1!=i_near)
	      NewRRTNoEmptyBranch(rst);
	  #endif

	  /*******************************************************************/
	  /* The last node added to t1 is used as random sample */
	  memcpy(q_rand,rrt->si[lastSample1]->samples,rrt->m*sizeof(double));

	  /*******************************************************************/
	  /* Search for q_near in the second tree */
	  i_near=GetRRTNN(t2,q_rand,rrt);

	  /*******************************************************************/
	  /* Extend t2 toward the last sample added to t1 */
	  #if (GET_RRT_STATISTICS)
	    NewRRTTreeConnection(rst);
	  #endif
	  pathFound=AddBranchToRRT(pr,FALSE,t2,i_near,q_rand,q_rand,&lastSample2,
				   NULL,NULL,rst,rrt);
	  #if (GET_RRT_STATISTICS)
	    if (lastSample2!=i_near)
	      NewRRTNoEmptyTreeConnection(rst);
	  #endif

	  /*******************************************************************/
	  /* Swap the trees (t1 and t2) */
	  if ((it%2)==0)
	    {
	      t1=GOAL2START;
	      t2=START2GOAL;
	    }
	  else
	    {
	      t1=START2GOAL;
	      t2=GOAL2START;
	    }

	  *time=GetElapsedTime(&st);
	  it++;
	}
    }

  fprintf(stderr,"Final number of samples: %u\n",rrt->ns);

  /* Reconstruct the path, if possible */
  if (pathFound)
    {
      if (!PathStart2GoalInRRT(pr,pgs,lastSample1,lastSample2,pl,NULL,ns,path,NULL,NULL,rrt))
	Error("Inconsitancy in cBiRRT pathFound");
    }

  /* Release memory */
  DeleteStatistics(&st);
  #if (GET_RRT_STATISTICS)
    if (grst==NULL)
      PrintRRTStatistics(rrt,rst);
    else
      AccumulateRRTStatistics(rst,grst);
    DeleteRRTStatistics(rst);
    free(rst);
  #endif

  free(q_rand);
  free(pgs);

  return(pathFound);
}



double RRTPathSteps(unsigned int sID,Tvector *path,Trrt *rrt)
{
  TRRTStep st;
  unsigned int s;
  double l;

  InitVector(sizeof(TRRTStep),CopyRRTStep,NULL,100,path);

  s=sID;
  l=0;
  while (s!=NO_UINT)
    {
      st.id=s;
      st.cost=rrt->si[s]->costp;/* this is 0 for the root */
      NewVectorElement((void *)(&st),path);
      l+=st.cost;
      s=rrt->si[s]->parent; /* this is NO_UINT for the root */
    }
  return(l);
}

double ChangeBiRRTSteps(unsigned int l1,unsigned int l2,double c12,Tvector *steps,Trrt *rrt)
{
  Tvector v1,v2;
  double lp1,lp2;
  unsigned int n;
  TRRTStep st,*st1,*st2;
  int i;
  double c;

  if (rrt->da>0)
    Error("ChangeBiRRTSteps do not work on problems with dynamics");

  lp1=RRTPathSteps(l1,&v1,rrt);
  lp2=RRTPathSteps(l2,&v2,rrt);
  if (rrt->si[l1]->tree==START2GOAL)
    {
      /* reverse(v1) -> v2 */
      ResetVector(steps);
      n=VectorSize(&v1);
      for(i=n-1;i>=0;i--)
	{
	  st1=(TRRTStep *)GetVectorElement(i,&v1);
	  if (i==0)
	    c=c12;
	  else
	    {
	      st2=(TRRTStep *)GetVectorElement(i-1,&v1);
	      c=st2->cost;
	    }
	  st.id=st1->id;
	  st.cost=c;
	  NewVectorElement((void*)&st,steps);
	}
      ConcatVectors(&v2,steps);
    }
  else
    {
      /* reverse(v2) -> v1 */
      ResetVector(steps);
      n=VectorSize(&v2);
      for(i=n-1;i>=0;i--)
	{
	  st1=(TRRTStep *)GetVectorElement(i,&v2);
	  if (i==0)
	    c=c12;
	  else
	    {
	      st2=(TRRTStep *)GetVectorElement(i-1,&v2);
	      c=st2->cost;
	    }
	  st.id=st1->id;
	  st.cost=c;
	  NewVectorElement((void*)&st,steps);
	}
      ConcatVectors(&v1,steps);
    }
  DeleteVector(&v1);
  DeleteVector(&v2);

  return(lp1+c12+lp2);
}

double UpdateBiRRTSteps(Tvector *steps,Trrt *rrt)
{
  TRRTStep *st;
  unsigned int i,n,current,next,id1,id2;
  double c12,l,ct;

  /* Ensure that all nodes in the path are correctly assigned
     to the trees (and that theirs costs are up to date) */
  n=VectorSize(steps);
  for(i=0;i<n;i++)
    {
      st=(TRRTStep *)GetVectorElement(i,steps);
      UpdateCostAndTree(st->id,rrt);
    }

  /* Search for the best transition between trees along the path */
  st=(TRRTStep *)GetVectorElement(0,steps);
  current=st->id;
  c12=st->cost;
  l=INF;
  id1=NO_UINT;
  id2=NO_UINT;
  for(i=1;i<n;i++)
    {
      st=(TRRTStep *)GetVectorElement(i,steps);
      next=st->id;
      if ((current==NO_UINT)||(next==NO_UINT))
	Error("Undefined node in path in BiRRT");
      if ((rrt->si[current]->tree!=rrt->si[next]->tree)&&
	  ((rrt->si[current]->cost+c12+rrt->si[next]->cost)<l))
	{
	  id1=current;
	  id2=next;
	  ct=c12;
	  l=rrt->si[id1]->cost+ct+rrt->si[id2]->cost;
	}
      current=next;
      c12=st->cost;
    }
  if (id1==NO_UINT) /* (id2==NO_UINT) (l==INF) */
    Error("A global path in a BiRRT without transition between trees?");

  return(ChangeBiRRTSteps(id1,id2,ct,steps,rrt));
}

boolean PathStart2GoalInRRT(Tparameters *pr,double *pgs,
			    unsigned int l1,unsigned int l2,
			    double *pl,double* pc,
			    unsigned int *ns,double ***path,double ***action,double **time,
			    Trrt *rrt)
{
  boolean pathFound;

  #if (EXPLORATION_RRT)
    /* We reconstruct the path from root to last sample in the tree */
    pathFound=TRUE;
    ReconstructRRTPath(pr,rrt->ns-1,pl,pc,ns,path,action,time,rrt);
  #else
    double pl1,pl2,d12;

    if (rrt->mode!=ONE_TREE)
      {
	#if (WEIGTHED_REACHED_GOAL)
	  d12=WeightedDistanceTopology(rrt->m,rrt->tp,rrt->weight,rrt->si[l1]->samples,rrt->si[l2]->samples);
	#else
	  d12=DistanceTopology(rrt->m,rrt->tp,rrt->si[l1]->samples,rrt->si[l2]->samples);
	#endif

	if (GetParameter(CT_DYNAMICS,pr)>0)
	  pathFound=(d12<GetParameter(CT_DYNAMIC_GOAL_ERROR,pr));
	else
	  {
	    pathFound=(d12<2.0*rrt->delta);
	    if (action!=NULL) *action=NULL;
	    if (time!=NULL) *time=NULL;
	  }

	if (pathFound)
	  {
	    unsigned int ns1,ns2;
	    double **p1,**p2;
	    double **a1,**a2;
	    double *t1,*t2;
	    unsigned int nvs;

	    nvs=ReconstructRRTPath(pr,l1,&pl1,pc,&ns1,&p1,&a1,&t1,rrt);
	    ReconstructRRTPath(pr,l2,&pl2,pc,&ns2,&p2,&a2,&t2,rrt);

	    /* TO BE REMOVED */
	    fprintf(stderr,"Samples in the path: %u (%u+%u)\n",ns1+ns2,ns1,ns2);
	    
	    if (rrt->si[l1]->tree==START2GOAL)
	      ReverseConcatTrajectories(nvs,rrt->da,
					ns1,p1,a1,t1,
					ns2,p2,a2,t2,
					ns,path,action,time);
	    else
	      ReverseConcatTrajectories(nvs,rrt->da,
					ns2,p2,a2,t2,
					ns1,p1,a1,t1,
					ns,path,action,time);

	    DeleteTrajectory(ns1,p1,a1,t1);
	    DeleteTrajectory(ns2,p2,a2,t2);

	    #if (WEIGTHED_REACHED_GOAL)
	      d12=DistanceTopology(rrt->m,rrt->tp,rrt->si[l1]->samples,rrt->si[l2]->samples);
	    #endif
	    *pl=pl1+d12+pl2;
	  }
      }
    else
      {
	unsigned int nn;
	double d;
	boolean dynamics;

	nn=GetRRTNN(START2GOAL,pgs,rrt);
	
	#if (WEIGTHED_REACHED_GOAL)
	  d=WeightedDistanceTopology(rrt->m,rrt->tp,rrt->weight,rrt->si[nn]->samples,pgs);
	#else
	  d=DistanceTopology(rrt->m,rrt->tp,rrt->si[nn]->samples,pgs);
	#endif
	
	if (GetParameter(CT_DYNAMICS,pr)>0)
	  {
	    dynamics=TRUE;
	    pathFound=(d<GetParameter(CT_DYNAMIC_GOAL_ERROR,pr));
	  }
	else
	  {
	    dynamics=FALSE;
	    pathFound=(d<2.0*rrt->delta);
	  }
	if (pathFound)
	  {

	    if (dynamics)
	      ReconstructRRTPath(pr,nn,pl,pc,ns,path,action,time,rrt);
	    else
	      {
		unsigned int g;

		/* Todo : compute the cost of the goal if required*/
		AddNodeToRRT(pr,START2GOAL,nn,pgs,pgs,&g,NULL,d,0,FALSE,NULL,0,
			     0,NULL,NULL,NULL,NULL,rrt);
		ReconstructRRTPath(pr,g,pl,pc,ns,path,action,time,rrt);
	      }
	  }
      }
  #endif

  return(pathFound);
}

boolean Bidirectional(Trrt *rrt)
{
  return(rrt->mode!=ONE_TREE);
}


unsigned int GetRRTMode(Trrt *rrt)
{
  return(rrt->mode);
}

boolean InDynamicDomain(unsigned int i,double *q,Trrt *rrt)
{
  if ((rrt->dd>0)&&(rrt->si[i]->ddr>0.0))
    return(DistanceTopology(rrt->m,rrt->tp,rrt->si[i]->samples,q)<rrt->si[i]->ddr);
  else
    return(TRUE);
}

void AdjustDynamicDomain(unsigned int i,boolean collision,Trrt *rrt)
{
  if (rrt->dd>0) /*  If the dynamic domain is active */
    {
      if (rrt->si[i]->ddr==0.0)
	{
	  /* The dynamic domain radius is not set yet. Set it if we
	     detected a collision during branch extension. */
	  if (collision)
	    rrt->si[i]->ddr=rrt->dd; /* Set to the initial radius. */
	}
      /* up to here we have the basic dynamic domain technique where
         the radius is set after detecting the first collision and not
         modified latter on */
#if (0)
      /* with the code below, the dydnamic domain radius is self-adjusted
         This is deactivated because it is not very effective,
	 in our experience. */
      else
	{
	  /* Adjust the radious according to the collision status.
	     Branches interrupted by a collision -> decrease the radius
	     Branches fully extended -> increase the radius */
	  if (collision)
	    rrt->si[i]->ddr*=(1.0-MOV_AVG_DOWN);
	  else
	    rrt->si[i]->ddr*=(1.0+MOV_AVG_UP);
	}
#endif
    }
}

double GetDynamicDomainRadius(unsigned int i,Trrt *rrt)
{
  if (rrt->dd>0)
    return(rrt->si[i]->ddr);
  else
    return(0.0);
}

boolean DynamicDomainRRT(Trrt *rrt)
{
  return(rrt->dd>0);
}

unsigned int GetRRTNumNodes(Trrt *rrt)
{
  return(rrt->ns);
}

unsigned int GetRRTActionSpaceDimension(Trrt *rrt)
{
  return(rrt->da);
}

double *GetRRTNode(unsigned int i,Trrt *rrt)
{
  if (i>=rrt->ns)
    return(NULL);
  else
    return(rrt->si[i]->samples);
}

unsigned int GetRRTNodeTree(unsigned int i,Trrt *rrt)
{
  if (i>=rrt->ns)
    return(NO_UINT);
  else
    {
      if (rrt->mode==ONE_TREE)
	return(START2GOAL);
      else
	return(rrt->si[i]->tree);
    }
}

unsigned int GetRRTParent(unsigned int i,Trrt *rrt)
{
  if (i>=rrt->ns)
    return(NO_UINT);
  else
    return(rrt->si[i]->parent);
}

void SetRRTParent(unsigned int i,unsigned int p,Trrt *rrt)
{
  if ((i>=rrt->ns)||(p>=rrt->ns))
    Error("Wrong node/parent in SetRRTParent");

  if (rrt->si[i]->parent==NO_UINT)
    Error("Can not change the parent of a root node");

  rrt->si[i]->parent=p;
  if (rrt->si[i]->tree!=rrt->si[p]->tree)
    {
      if (rrt->mode!=TWO_TREES_WITH_SWAP)
	Error("Nodes can only swap trees in TWO_TREES_WITH_SWAP RRTs");
      rrt->si[i]->tree=rrt->si[p]->tree;
    }
}

double *GetRRTAction(unsigned int i,Trrt *rrt)
{
  if (i>=rrt->ns)
    return(NULL);
  else
    return(rrt->si[i]->u);
}

double GetRRTTime(unsigned int i,Trrt *rrt)
{
  if (i>=rrt->ns)
    return(0.0);
  else
    return(rrt->si[i]->time);
}

double GetRRTTimeFromRoot(unsigned int i,Trrt *rrt)
{
  if (i>=rrt->ns)
    return(0.0);
  else
    {
      double t;
      unsigned int node;

      t=0.0;
      node=i;
      while(node!=NO_UINT)
	{
	  t+=rrt->si[node]->time;
	  node=rrt->si[node]->parent;
	}
      
      return(t);
    }
}

void *GetRRTNodeInfo(unsigned int i,Trrt *rrt)
{
  if (i<rrt->ns)
    return(rrt->si[i]->userInfo);
  else
    return(NULL);
}

void SetRRTNodeInfo(unsigned int i,void *info,Trrt *rrt)
{
  if (i<rrt->ns)
    rrt->si[i]->userInfo=info;
  else
    Error("RRT node out of range in SetRRTNodeInfo");
}

double GetRRTNodeCostFromParent(unsigned int i,Trrt *rrt)
{
  if (i<rrt->ns)
    return(rrt->si[i]->costp);
  else
    return(0.0);
}

double GetRRTNodeCost(unsigned int i,Trrt *rrt)
{
  if (i<rrt->ns)
    return(rrt->si[i]->cost);
  else
    return(0.0);
}

void SetRRTNodeCost(unsigned int i,double costp,double cost,Trrt *rrt)
{
  if (i<rrt->ns)
    {
      rrt->si[i]->costp=costp;
      rrt->si[i]->cost=cost;
    }
  else
    Error("RRT node out of range in SetRRTNodeCost");
}

void SetRRTCostAndParent(unsigned int i,unsigned int p,double costp,double cost,Trrt *rrt)
{
  if (i<rrt->ns)
    { 
      #if (_DEBUG>1)
        if (rrt->si[i]->ns>0)
	  Error("RRT* can not include paths in the edges");
      #endif
      rrt->si[i]->costp=costp;
      rrt->si[i]->cost=cost;
      rrt->si[i]->parent=p;
      if (rrt->si[i]->tree!=rrt->si[p]->tree)
	{
	  if (rrt->mode!=TWO_TREES_WITH_SWAP)
	    Error("A RRT node moved from one tree to another in SetRRTCostAndParent");
	  rrt->si[i]->tree=rrt->si[p]->tree;
	}
    }
  else
    Error("RRT node out of range in SetRRTCostAndParent");
}

double RRTBlockedProb(unsigned int i,Trrt *rrt)
{
  if (i<rrt->ns)
    {
      double p;

      /* the more the times we hit an obstacle, the more the prob of
         finding an obstacle again. This also works for domain limits */
      p=(rrt->si[i]->blocked)/(rrt->si[i]->blocked+1.0);
      
      if (p>0.9) p=0.9;
      
      return(p);
    }
  else
    return(1.0); /* This should trigger an error... */
}

unsigned int *GetRRTTopology(Trrt *rrt)
{
  return(rrt->tp);
}

double *GetRRTWeights(Trrt *rrt)
{
  return(rrt->weight);
}

double CostToRoot(unsigned int sID,Trrt* rrt)
{
  double l;
  unsigned int s;

  l=0.0;
  s=sID;
  while (s!=NO_UINT)
    {
      l+=rrt->si[s]->costp;
      s=rrt->si[s]->parent;
    }
  return(l);
}

void UpdateCostToRoot(unsigned int sID,Trrt* rrt)
{
  rrt->si[sID]->cost=CostToRoot(sID,rrt);
}

void UpdateTree(unsigned int sID,Trrt* rrt)
{
  unsigned int s,p;

  if (rrt->mode!=TWO_TREES_WITH_SWAP)
    Error("Nodes can only change trees in TWO_TREES_WITH_SWAP mode");

  s=sID;
  p=NO_UINT; /* parent node */
  while (s!=NO_UINT)
    {
      p=s;
      s=rrt->si[s]->parent;
    }
  if (p==NO_UINT)
    Error("Undefined root node in UpdateTree");

  /* here p is the root of the tree including sample sID (0 or 1) */
  if (p>2)
    Error("Wrong root in UpdateTree");

  /* update the tree assigment for this node */
  /* alternatively we could update the tree assigment all along the branch */
  if (p==0)
    rrt->si[sID]->tree=START2GOAL;
  else
    rrt->si[sID]->tree=GOAL2START;
}

void UpdateCostAndTree(unsigned int sID,Trrt* rrt)
{
  double l;
  unsigned int s,p;

  /* This is just cut+paste+joint of CostToRoot, UpdateCost, and UpdateTree
     defined to gain some efficiency. */

  l=0.0;
  s=sID;
  p=NO_UINT; /* previous node */
  while (s!=NO_UINT)
    {
      l+=rrt->si[s]->costp;
      p=s;
      s=rrt->si[s]->parent;
    }

  /* update the cost and the tree of the given node */
  rrt->si[sID]->cost=l;
  /* the update of the tree only has effect in TWO_TREES_WITH_SWAP mode */
  if (p==0)
    rrt->si[sID]->tree=START2GOAL;
  else
    rrt->si[sID]->tree=GOAL2START;
}

unsigned int StepsToRoot(unsigned int sID,Trrt* rrt)
{
  unsigned int l;
  unsigned int s;

  l=0;
  s=sID;
  while (s!=NO_UINT)
    {
      l++;
      s=rrt->si[s]->parent;
    }
  return(l);
}

void PlotRRT(char *fname,int argc, char **arg,Tparameters *pr,
	     unsigned int xID,unsigned int yID,unsigned int zID,
	     double *p1,double *p2,Trrt *rrt)
{
  Tplot3d p3d;
  unsigned int i,j;
  Tcolor color;
  double *o;
  double *px,*py,*pz;
  unsigned int ms;
  double *x,*y,*z;
  double cx,cy,cz;
  boolean cut;
  double dx,dy,dz;

  if (rrt->mode==TWO_TREES_WITH_SWAP)
    {
      /* To obtain nicer plots we update the tree assigment for all nodes */
      for(i=0;i<rrt->ns;i++)
	UpdateTree(i,rrt);
    }

  cx=GetParameter(CT_CUT_X,pr);
  cy=GetParameter(CT_CUT_Y,pr);
  cz=GetParameter(CT_CUT_Z,pr);
  cut=((fabs(cx)>1e-10)||(fabs(cy)>1e-10)||(fabs(cz)>1e-10));

  /* Project the RRT nodes */
  NEW(px,rrt->ns,double);
  NEW(py,rrt->ns,double);
  NEW(pz,rrt->ns,double);

  for(i=0;i<rrt->ns;i++)
    {
      CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[i]->samples,&o,rrt->w);

      px[i]=o[xID];
      py[i]=o[yID];
      pz[i]=o[zID];

      CORRECT_POINT_PLOT(cx,cy,cz,px[i],py[i],pz[i]);

      free(o);
    }

  InitPlot3d(fname,FALSE,argc,arg,&p3d);

  /* Start */
  if (p1!=NULL)
    {
      NewColor(1,1,0,&color); /*yelow*/
      StartNew3dObject(&color,&p3d);

      CORRECT_POINT_PLOT(cx,cy,cz,p1[0],p1[1],p1[2]);

      PlotSphere(GetParameter(CT_DELTA,pr),p1[0],p1[1],p1[2],&p3d);

      DeleteColor(&color);
      Close3dObject(&p3d);
    }

  /* Goal */
  if (p2!=NULL)
    {
      NewColor(1,0,0,&color); /*red*/
      StartNew3dObject(&color,&p3d);

      CORRECT_POINT_PLOT(cx,cy,cz,p2[0],p2[1],p2[2]);

      //if (GetParameter(CT_DYNAMICS,pr)>0)
      //  PlotSphere(GetParameter(CT_DYNAMIC_GOAL_ERROR,pr),p2[0],p2[1],p2[2],&p3d);
      //else
        PlotSphere(GetParameter(CT_DELTA,pr),p2[0],p2[1],p2[2],&p3d);

      DeleteColor(&color);
      Close3dObject(&p3d);
    }

  /*Edges*/
  ms=0;
  for(i=0;i<rrt->ns;i++)
    {
      if (ms<rrt->si[i]->ns)
	ms=rrt->si[i]->ns;
    }
  ms+=2;
  NEW(x,ms,double);
  NEW(y,ms,double);
  NEW(z,ms,double);
  
  NewColor(1,0,0,&color); /*red*/
  StartNew3dObject(&color,&p3d);

  for(i=((rrt->mode!=ONE_TREE)?2:1);i<rrt->ns;i++)
    {
      if ((rrt->mode==ONE_TREE)||(rrt->si[i]->tree==START2GOAL))
	{
	  x[0]=px[rrt->si[i]->parent];
	  y[0]=py[rrt->si[i]->parent];
	  z[0]=pz[rrt->si[i]->parent];

	  for(j=0;j<rrt->si[i]->ns;j++)
	    {
	      CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[i]->path[j],&o,rrt->w);
	      
	      x[j+1]=o[xID];
	      y[j+1]=o[yID];
	      z[j+1]=o[zID];
	      
	      CORRECT_POINT_PLOT(cx,cy,cz,x[j+1],y[j+1],z[j+1]);
	      
	      free(o);
	    }
	  
	  x[rrt->si[i]->ns+1]=px[i];
	  y[rrt->si[i]->ns+1]=py[i];
	  z[rrt->si[i]->ns+1]=pz[i];

	  dx=x[rrt->si[i]->ns+1]-x[0];
	  dy=y[rrt->si[i]->ns+1]-y[0];
	  dz=z[rrt->si[i]->ns+1]-z[0];
	  if ((!cut)||(sqrt(dx*dx+dy*dy+dz*dz)<M_PI))
	    PlotVect3d(rrt->si[i]->ns+2,x,y,z,&p3d);
	}
    }

  DeleteColor(&color);
  Close3dObject(&p3d);
  
  if (rrt->mode!=ONE_TREE)
    {
      NewColor(0,1,0,&color); /*green*/
      StartNew3dObject(&color,&p3d);

      for(i=2;i<rrt->ns;i++)
	{
	  if (rrt->si[i]->tree==GOAL2START)
	    {
	      x[0]=px[rrt->si[i]->parent];
	      y[0]=py[rrt->si[i]->parent];
	      z[0]=pz[rrt->si[i]->parent];

	      for(j=0;j<rrt->si[i]->ns;j++)
		{
		  CS_WD_REGENERATE_ORIGINAL_POINT(pr,rrt->si[i]->path[j],&o,rrt->w);
	      
		  x[j+1]=o[xID];
		  y[j+1]=o[yID];
		  z[j+1]=o[zID];
	      
		  CORRECT_POINT_PLOT(cx,cy,cz,x[j+1],y[j+1],z[j+1]);
	      
		  free(o);
		}
	  
	      x[rrt->si[i]->ns+1]=px[i];
	      y[rrt->si[i]->ns+1]=py[i];
	      z[rrt->si[i]->ns+1]=pz[i];

	      dx=x[rrt->si[i]->ns+1]-x[0];
	      dy=y[rrt->si[i]->ns+1]-y[0];
	      dz=z[rrt->si[i]->ns+1]-z[0];
	      if ((!cut)||(sqrt(dx*dx+dy*dy+dz*dz)<M_PI))
		PlotVect3d(rrt->si[i]->ns+2,x,y,z,&p3d);
	    }
	}

      DeleteColor(&color);
      Close3dObject(&p3d);
    }
  
  #if (RRT_PLOT_NODES)
    /* Dots, one per node */
    NewColor(0,0,1,&color); /*blue*/
    StartNew3dObject(&color,&p3d);

    for(i=0;i<rrt->ns;i++)
      {
	x[0]=px[i]-0.01;
	y[0]=py[i];
	z[0]=pz[i];

	x[1]=px[i]+0.01;
	y[1]=py[i];
	z[1]=pz[i];

	PlotVect3d(2,x,y,z,&p3d);

	x[0]=px[i];
	y[0]=py[i]-0.01;
	z[0]=pz[i];

	x[1]=px[i];
	y[1]=py[i]+0.01;
	z[1]=pz[i];

	PlotVect3d(2,x,y,z,&p3d);

	x[0]=px[i];
	y[0]=py[i];
	z[0]=pz[i]-0.01;

	x[1]=px[i];
	y[1]=py[i];
	z[1]=pz[i]+0.01;

	PlotVect3d(2,x,y,z,&p3d);
      }

    DeleteColor(&color);
    Close3dObject(&p3d);
  #endif

  free(x);
  free(y);
  free(z);
  
  ClosePlot3d(FALSE,&p3d);

  free(px);
  free(py);
  free(pz);
}

void SaveRRTNodes(Tparameters *pr,char *fname,boolean saveWithDummies,Trrt *rrt)
{
  double *o;
  unsigned int i,j,nv,nvs;
  boolean *systemVars;
  double *c;
  FILE *fo;
  Tfilename fsol;

  if (saveWithDummies)
    CreateFileName(NULL,fname,"_nodes",SOL_WITH_DUMMIES_EXT,&fsol);
  else
    CreateFileName(NULL,fname,"_nodes",SOL_EXT,&fsol);
  fprintf(stderr,"Writing boxes to                  : %s\n",GetFileFullName(&fsol));
  fo=fopen(GetFileFullName(&fsol),"w");
  if (!fo)
    Error("Could not open the file to store the boxes in SaveRRTNodes");

  nv=CS_WD_GET_SYSTEM_VARS(&systemVars,rrt->w);
  nvs=0;
  for(j=0;j<nv;j++)
    {
      if (systemVars[j])
	nvs++;
    }

  for(i=0;i<rrt->ns;i++)
    {
      c=rrt->si[i]->samples;

      CS_WD_REGENERATE_ORIGINAL_POINT(pr,c,&o,rrt->w);

      if (saveWithDummies)
	fprintf(fo,"%u { %u ",i,nv);
      else
	fprintf(fo,"%u { %u ",i,nvs);
      for(j=0;j<nv;j++)
	{
	  if ((saveWithDummies)||(systemVars[j]))
	    fprintf(fo,"[%.12g,%.12g] ",o[j],o[j]);
	}
      fprintf(fo,"}\n");

      free(o);
    }

  fclose(fo);
  free(systemVars);
  DeleteFileName(&fsol);
}

void SaveRRTCosts(Tparameters *pr,char *fname,Trrt *rrt)
{
  unsigned int i;
  FILE *fo;
  Tfilename fcost;
  double ma,mi;
  unsigned int ima,imi;
  double c;

  CreateFileName(NULL,fname,"_nodes",COST_EXT,&fcost);
  fprintf(stderr,"Writing costs to                  : %s\n",GetFileFullName(&fcost));

  fo=fopen(GetFileFullName(&fcost),"w");
  if (!fo)
    Error("Could not open the file to store the costs in SaveRRTCosts");

  ma=-INF;
  mi=INF;
  for(i=0;i<rrt->ns;i++)
    {
      c=rrt->si[i]->cost;
      fprintf(fo,"%f\n",c);
      if (c>ma)
	{
	  ma=c;
	  ima=i;
	}
      if (c<mi)
	{
	  mi=c;
	  imi=i;
	}
    }
  fprintf(stderr,"  Extreme costs                   : %f (%u) -- %f (%u)\n",mi,imi,ma,ima);

  fclose(fo);
  DeleteFileName(&fcost);
}

unsigned int RRTMemSize(Trrt *rrt)
{
  unsigned int b,i;

  /* The samples */
  b=sizeof(double)*rrt->m*rrt->ns;

  if (rrt->graph)
    {
      /* The neighbours */
      for(i=0;i<rrt->ns;i++)
	b+=rrt->si[i]->nn*(sizeof(double)+sizeof(unsigned int));
    }

  return(b);
}

void SaveRRT(Tfilename *fname,Trrt *rrt)
{
  FILE *f;
  unsigned int i,j,k;


  f=fopen(GetFileFullName(fname),"w");
  if (!f)
    Error("Could not open file to store rrt");

  fprintf(f,"%u\n",rrt->graph);
  fprintf(f,"%u\n",rrt->mode);
  fprintf(f,"%f\n",rrt->dd);
  #if (_KDTREE==1)
    fprintf(f,"%.12f\n",KDtreeSamplingExpansion(rrt->treeS2G));
  #else
    fprintf(f,"0\n");
  #endif
  fprintf(f,"%u\n",rrt->da);

  fprintf(f,"%u\n",rrt->m);
  fprintf(f,"%u\n",rrt->k);
  fprintf(f,"%u\n",rrt->n);

  fprintf(f,"%.12f\n",rrt->delta);

  fprintf(f,"%.12f\n",rrt->temperature);
  fprintf(f,"%u\n",rrt->nFail);

  fprintf(f,"%u\n",rrt->ms);
  fprintf(f,"%u\n",rrt->ns);
  
  for(i=0;i<rrt->ns;i++)
    {
      for(j=0;j<rrt->m;j++)
	fprintf(f,"%.12f ",rrt->si[i]->samples[j]);
      fprintf(f,"\n");

      for(j=0;j<rrt->da;j++)
	fprintf(f,"%.12f ",rrt->si[i]->u[j]);
      fprintf(f,"\n");

      fprintf(f,"%u %u %.12f %.12f %.12f %.12f %.12f\n",rrt->si[i]->parent,rrt->si[i]->tree,
              rrt->si[i]->costp,rrt->si[i]->cost,rrt->si[i]->blocked,rrt->si[i]->ddr,rrt->si[i]->time);

      fprintf(f,"%u\n",rrt->si[i]->ns);
      if (rrt->si[i]->ns>0)
	{	  
	  for(j=0;j<rrt->si[i]->ns;j++)
	    {
	      for(k=0;k<rrt->m;k++)
		fprintf(f,"%.12f ",rrt->si[i]->path[j][k]);
	      fprintf(f,"\n");

	      if (rrt->da>0)
		{
		  for(k=0;k<rrt->da;k++)
		    fprintf(f,"%.12f ",rrt->si[i]->actions[j][k]);
		  fprintf(f,"\n");
	
		  fprintf(f,"%.12f\n",rrt->si[i]->times[j]);
		}
	    }
	}
      
      if (rrt->graph)
	{
	  fprintf(f,"%f %u %u",rrt->si[i]->g,rrt->si[i]->m,rrt->si[i]->nn);
	  for(j=0;j<rrt->si[i]->nn;j++)
	    fprintf(f," %u %.12f",rrt->si[i]->n[j],rrt->si[i]->cn[j]);
	  fprintf(f,"\n");
	}
    }

  fclose(f);
}

void LoadRRT(Tparameters *pr,Tfilename *fname,TAtlasBase *w,Trrt *rrt)
{
  FILE *f;
  unsigned int i,j,k;
  double dr;
  Tinterval *range;

  f=fopen(GetFileFullName(fname),"r");
  if (!f)
    Error("Could not open file to read the RRT");

  rrt->w=w;

  fscanf(f,"%u",&(rrt->graph));
  fscanf(f,"%u",&(rrt->mode));
  fscanf(f,"%lf",&(rrt->dd));
  fscanf(f,"%lf",&dr);
  fscanf(f,"%u",&(rrt->da));

  fscanf(f,"%u",&(rrt->m));
  fscanf(f,"%u",&(rrt->k));
  fscanf(f,"%u",&(rrt->n));

  fscanf(f,"%lf",&(rrt->delta));

  fscanf(f,"%lf",&(rrt->temperature));
  fscanf(f,"%u",&(rrt->nFail));

  fscanf(f,"%u",&(rrt->ms));
  fscanf(f,"%u",&(rrt->ns));

  NEW(rrt->si,rrt->ms,TRRTSampleInfo*);
  for(i=0;i<rrt->ms;i++)
    rrt->si[i]=NULL;

  SetRRTTopology(pr,rrt);

  NEW(rrt->ambient,1,Tbox);
  CS_WD_GENERATE_SIMP_INITIAL_BOX(pr,rrt->ambient,rrt->w);

  #if (WEIGTHED_NN)
    if (GetDistanceWeightsFromBox(&(rrt->weight),rrt->ambient)!=rrt->m)
      Error("Size missmatch in LoadRRT");
  #else
    rrt->weight=NULL;
  #endif
  
  #if (_KDTREE==1)
  {
    unsigned int nd;
    Trectangle rec;

    nd=GetBoxNIntervals(rrt->ambient);
    if (rrt->m!=nd)
      Error("Dimension missmatch in LoadRRT");
    
    InitRectangle(nd,NULL,NULL,&rec);
    for(i=0;i<nd;i++)
      {
	range=GetBoxInterval(i,rrt->ambient);
	SetRectangleLimits(i,LowerLimit(range),UpperLimit(range),&rec);
      }

    rrt->treeS2G=InitKDTree(&rec,rrt->tp,rrt->weight,25,dr,0,NULL,NULL);
    if (rrt->mode==TWO_TREES)
      rrt->treeG2S=InitKDTree(&rec,rrt->tp,rrt->weight,25,dr,0,NULL,NULL);

    DeleteRectangle(&rec);
  }
  #endif

  #if (_KDTREE==2)
  {
    double *w2;
    
    NEW(w2,rrt->m,double);
    for(i=0;i<nd;i++)
      w2[i]=sqrt(rrt->weight[i]); /* In this kdtree weights are squared inside */
 
    if ((!RRT_NN_TOPOLOGY)||(rrt->tp==NULL))
      rrt->treeS2G=CreateKDTreeS(rrt->m,w2);
    else
      rrt->treeS2G=CreateKDTreeTS(rrt->m,(int *)rrt->tp,w2);

    if (rrt->mode==TWO_TREES)
      {
	if ((!RRT_NN_TOPOLOGY)||(rrt->tp==NULL))
	  rrt->treeG2S=CreateKDTreeS(rrt->m,w2);
	else
	  rrt->treeG2S=CreateKDTreeTS(rrt->m,(int *)rrt->tp,w2);

	rrt->maxNodesT1=rrt->ms;
	rrt->maxNodesT2=rrt->ms;

	NEW(rrt->t1ToId,rrt->maxNodesT1,unsigned int);
	NEW(rrt->t2ToId,rrt->maxNodesT2,unsigned int);

	rrt->nodesT1=0;
	rrt->nodesT2=0;
      }
    free(w2);
  }
  #endif

  for(i=0;i<rrt->ns;i++)
    {
      NEW(rrt->si[i],1,TRRTSampleInfo);

      NEW(rrt->si[i]->samples,rrt->m,double);
      for(j=0;j<rrt->m;j++)      /* sample */
	fscanf(f,"%lf",&(rrt->si[i]->samples[j]));

      if (rrt->da==0)
	rrt->si[i]->u=NULL;
      else
	{
	  NEW(rrt->si[i]->u,rrt->da,double);
	  for(j=0;j<rrt->da;j++)      /* action */
	    fscanf(f,"%lf",&(rrt->si[i]->u[j]));
	}

      fscanf(f,"%u",&(rrt->si[i]->parent));
      fscanf(f,"%u",&(rrt->si[i]->tree));
      fscanf(f,"%lf",&(rrt->si[i]->costp));
      fscanf(f,"%lf",&(rrt->si[i]->cost));
      fscanf(f,"%lf",&(rrt->si[i]->blocked));
      fscanf(f,"%lf",&(rrt->si[i]->ddr));
      fscanf(f,"%lf",&(rrt->si[i]->time));

      fscanf(f,"%u",&(rrt->si[i]->ns));
      if (rrt->si[i]->ns>0)
	{
	  NEW(rrt->si[i]->path,rrt->si[i]->ns,double*);
	  if (rrt->da>0)
	    {
	      NEW(rrt->si[i]->actions,rrt->si[i]->ns,double*);
	      NEW(rrt->si[i]->times,rrt->si[i]->ns,double);
	    }
	  else
	    {
	      rrt->si[i]->actions=NULL;
	      rrt->si[i]->times=NULL;
	    }
	  
	  for(j=0;j<rrt->si[i]->ns;j++)
	    {
	      NEW(rrt->si[i]->path[j],rrt->m,double);
	      for(k=0;k<rrt->m;k++)
		fscanf(f,"%lf",&(rrt->si[i]->path[j][k]));

	      if (rrt->da>0)
		{
		  NEW(rrt->si[i]->actions[j],rrt->da,double);
		  for(k=0;k<rrt->da;k++)
		    fscanf(f,"%lf",&(rrt->si[i]->actions[j][k]));
	
		  fscanf(f,"%lf",&(rrt->si[i]->times[j]));
		}
	    }
	}
      else
	{
	  rrt->si[i]->path=NULL;
	  rrt->si[i]->actions=NULL;
	  rrt->si[i]->times=NULL;
	}

      rrt->si[i]->userInfo=NULL; /* This information is not stored :( */

      #if (_KDTREE==1)
        if (rrt->mode==TWO_TREES)
	  {
	    if (rrt->si[i]->tree==START2GOAL)
	      AddPoint2KDtree(rrt->si[i]->samples,i,&(rrt->treeS2G));
	    else
	      AddPoint2KDtree(rrt->si[i]->samples,i,&(rrt->treeG2S));
	  }
	else
	  AddPoint2KDtree(rrt->si[i]->samples,i,&(rrt->treeS2G));
      #endif

      #if (_KDTREE==2)
	if (rrt->mode==TWO_TREES)
	  {
	    if (rrt->si[i]->tree==START2GOAL)
	      {
		rrt->t1ToId[rrt->nodesT1]=i;
		rrt->nodesT1++;
		AddPoint2KDTree(rrt->si[i]->samples,rrt->treeS2G);
	      }
	    else
	      {
		rrt->t2ToId[rrt->nodesT2]=i;
		rrt->nodesT2++;
		AddPoint2KDTree(rrt->si[i]->samples,rrt->treeG2S);
	      }
	  }
	else
	  AddPoint2KDTree(rrt->si[i]->samples,rrt->treeS2G);
      #endif

      if (rrt->graph)
	{
	  fscanf(f,"%lf",&(rrt->si[i]->g));
	  fscanf(f,"%u",&(rrt->si[i]->m));
	  fscanf(f,"%u",&(rrt->si[i]->nn));
	  NEW(rrt->si[i]->n,rrt->si[i]->m,unsigned int);
	  NEW(rrt->si[i]->cn,rrt->si[i]->m,double);
	  for(j=0;j<rrt->si[i]->nn;j++)
	    {
	      fscanf(f,"%u",&(rrt->si[i]->n[j]));
	      fscanf(f,"%lf",&(rrt->si[i]->cn[j]));
	    }
	}
    }

  fclose(f);
    
  /* The parallelism information is not stored! We de-activate it
     when loading an RRT (load is typically used for visualization
     and not for further processing)*/
  rrt->nCores=1;
  rrt->parallel=FALSE;
}

void PrintRRTDefines(FILE *f)
{
  fprintf(f,"\n   %% RRT defines\n");
  fprintf(f,"   RRT_VERBOSE %u\n",RRT_VERBOSE);
  fprintf(f,"   GET_RRT_STATISTICS %u\n",GET_RRT_STATISTICS);
  fprintf(f,"   EXPLORATION_RRT %u\n",EXPLORATION_RRT);
  fprintf(f,"   WEIGTHED_NN %u\n",WEIGTHED_NN);
  fprintf(f,"   WEIGTHED_REACHED_GOAL %u\n",WEIGTHED_REACHED_GOAL);
  fprintf(f,"   PENALIZE_BLOCKED_NODES %u\n",PENALIZE_BLOCKED_NODES);
  fprintf(f,"   HEURISTIC_RRT_STAR %u\n",HEURISTIC_RRT_STAR);
  fprintf(f,"   RRTSTAR_UPDATE_COSTS %u\n",RRTSTAR_UPDATE_COSTS);
  fprintf(f,"   RRTSTAR_SYMMETRIC_COST %u\n",RRTSTAR_SYMMETRIC_COST);
  fprintf(f,"   TEMPERATURE_INIT %.4f\n",TEMPERATURE_INIT);
  fprintf(f,"   RRT_PLOT_NODES %u\n",RRT_PLOT_NODES);
  fprintf(f,"   RRT_NN_TOPOLOGY %u\n",RRT_NN_TOPOLOGY);
}

void DeleteRRT(Trrt *rrt)
{
  unsigned int i;

  for(i=0;i<rrt->ns;i++)
    {
      free(rrt->si[i]->samples);
      if (rrt->si[i]->u!=NULL)
	free(rrt->si[i]->u);
      if (rrt->graph)
	{
	  free(rrt->si[i]->n);
	  free(rrt->si[i]->cn);
	}

      if (rrt->si[i]->ns>0)
	{
	  if (rrt->da>0)
	    DeleteTrajectory(rrt->si[i]->ns,rrt->si[i]->path,rrt->si[i]->actions,rrt->si[i]->times);
	  else
	    DeleteSamples(rrt->si[i]->ns,rrt->si[i]->path);
	}
      
      free(rrt->si[i]);
    }

  free(rrt->si);

  if (rrt->tp!=NULL)
    free(rrt->tp);

  if (rrt->ambient!=NULL)
    {
      DeleteBox(rrt->ambient);
      free(rrt->ambient);
    }

  #if (_KDTREE==1)
    DeleteKDtree(rrt->treeS2G);
     if (rrt->mode==TWO_TREES)
       DeleteKDtree(rrt->treeG2S);
  #endif
  #if (_KDTREE==2)
    DeleteKDTree(rrt->treeS2G);
    if (rrt->mode==TWO_TREES)
      {
	DeleteKDTree(rrt->treeG2S);

	free(rrt->t1ToId);
	free(rrt->t2ToId);
      }
  #endif

  if (rrt->weight!=NULL)
    free(rrt->weight);
}
