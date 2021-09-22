#include "averages.h"

#include "error.h"
#include "algebra.h"
#include "defines.h"

#include <math.h>
#include <time.h>
#include <unistd.h>

/** 
   \file averages.c

   \brief Implementation of the auxiliary functions to compute averages of sets of experiments.

   Implementation of the auxiliary functions to compute averages of sets of experiments.
   
   \sa averages.h
*/

void InitAverages(unsigned int m,boolean useCharts,boolean useSamples,
		  unsigned int maxIt,Taverages *av)
{
  av->maxExperiments=m;
  av->nSuccess=0;

  NEW(av->times,m,double);
  NEW(av->memory,m,double);
  NEW(av->pathLength,m,double);
  NEW(av->pathCost,m,double);

  if (useCharts)
    { NEW(av->nCharts,m,double); }
  else
    av->nCharts=NULL;

  if (useSamples)
    { NEW(av->nSamples,m,double); }
  else
    av->nSamples=NULL;

  av->maxIt=maxIt;

  if (maxIt!=NO_UINT)
    {
      unsigned int i;

      NEW(av->time,maxIt,double);
      NEW(av->timeStd,maxIt,double);

      NEW(av->cost,maxIt,double);
      NEW(av->costStd,maxIt,double);
      NEW(av->ncost,maxIt,unsigned int);

      for(i=0;i<maxIt;i++)
	{
	  av->time[i]=0;
	  av->timeStd[i]=0;
	  av->cost[i]=0;
	  av->costStd[i]=0;
	  av->ncost[i]=0;
	}
    }
  else
    {
      av->time=NULL;
      av->timeStd=NULL;

      av->cost=NULL;
      av->costStd=NULL;
      av->ncost=NULL;
    }
}

void NewSuccesfulExperiment(double t,unsigned int mem,double pl,double pc,
			    unsigned int nc,unsigned int ns,
			    double *time,double *cost,Taverages *av)
{
  double m;

  if (av->nSuccess>=av->maxExperiments)
    Error("More succesful experiments than maximum experiments");

  fprintf(stderr,"Data about the execution:\n");
  av->times[av->nSuccess]=t;
  fprintf(stderr,"  Elapsed time     : %f sec\n",t);

  m=((double)mem)/(1024.0*1024.0);
  av->memory[av->nSuccess]=m;
  fprintf(stderr,"  Used memory      : %f Mb\n",m);

  av->pathLength[av->nSuccess]=pl;
  fprintf(stderr,"  Path length      : %f\n",pl);
	      
  av->pathCost[av->nSuccess]=pc;
  fprintf(stderr,"  Path cost/time   : %f\n",pc);


  if (av->nCharts!=NULL)
    {
      av->nCharts[av->nSuccess]=nc;
      fprintf(stderr,"  Num charts       : %u\n",nc);
    }

  if (av->nSamples!=NULL)
    {
      av->nSamples[av->nSuccess]=ns;
      fprintf(stderr,"  Num samples      : %u\n",ns);
    }
  
  if (av->maxIt!=NO_UINT)
    {
      if ((time==NULL)||(cost==NULL))
	{
	  /* Time and cost are expected but they are not
	      actually given -> delete them. They would
	      be used/expected any more. */
	  free(av->time);
	  free(av->timeStd);
	  free(av->cost);
	  free(av->costStd);
	  free(av->ncost);

	  av->maxIt=NO_UINT;
	}
      else
	{
	  unsigned int i;

	  for(i=0;i<av->maxIt;i++)
	    {
	      av->time[i]+=time[i];
	      av->timeStd[i]+=(time[i]*time[i]);

	      if (cost[i]>-0.5)
		{
		  /* If we have cost data at this iteration */
		  av->cost[i]+=cost[i];
		  av->costStd[i]+=(cost[i]*cost[i]);
		  av->ncost[i]++;
		}
	    }
	}
    }

  av->nSuccess++;
}

void PrintAveragesHeader(FILE *f,int argc, char **arg,Taverages *av)
{
  unsigned int i;
  time_t t;
  char hostname[150];
  char *path;

  fprintf(f,"\n\n%% **************************************************\n");
  t=time(NULL);
  gethostname(hostname,50);
  path=getcwd(NULL,0);
  fprintf(f,"Date        : %s",ctime(&t));
  fprintf(f,"Machine     : %s\n",hostname);
  fprintf(f,"Path        : %s\n",path);
  free(path);
  fprintf(f,"Command line: ");
  for(i=0;i<(unsigned int)argc;i++)
    fprintf(f,"%s ",arg[i]);
  fprintf(f,"\n");
}

void PrintAverages(FILE *f,Taverages *av)
{
  fprintf(f,"%% **************************************************\n");
  fprintf(f,"Execution averages over %u repetitions\n",av->maxExperiments);
  fprintf(f,"  Success ratio: %u / %u = %g\n",av->nSuccess,av->maxExperiments,
	  (double)av->nSuccess/(double)av->maxExperiments);

  if (av->nSuccess>0)
    {
      unsigned int i;
      double mt,ml,mc,ms;
	  
      if (av->maxIt!=NO_UINT)
	{
	  /* Print statistics about time and cost per iteration */
	  fprintf(f,"****************************************************\n");
	  fprintf(f,"It  Mean_time  Std_time  Mean_cost  Std_cost  N_cost\n");

	  /* Compute the mean of time/cost */
	  for (i=0;i<av->maxIt;i++)
	    {
	      av->time[i]/=(double)av->nSuccess; 
	      if (av->ncost[i]>0)
		av->cost[i]/=(double)av->ncost[i];
	    }
	  /* Compute the standard deviation of time/cost */
	  /*
	    (1/n)*\sum (x_i-m_i)^2 = (1/n)*\sum (x_i^2-2*x_i*m_i+m_i^2)=
            (1/n)*\sum x_i^2 - (1/n)*2*m_i*\sum x_i + m_i^2 = (1/n)*\sum x_i^2 - m_i^2
	  */
	  for (i=0;i<av->maxIt;i++)
	    {
	      av->timeStd[i]=sqrt(av->timeStd[i]/(double)av->nSuccess-pow(av->time[i],2));
	      if (av->ncost[i]>0)
		av->costStd[i]=sqrt(av->costStd[i]/(double)av->ncost[i]-pow(av->cost[i],2));
	    }

	  /* print the results */
	  for (i=0;i<av->maxIt;i++)
	    {
	      if ((i%ITERATIONS_BETWEEN_DATA)==0)
		{
		  fprintf(f, "%u %g %g ",i,av->time[i],av->timeStd[i]);
		  if (av->ncost[i]==0)
		    fprintf(stderr, "0 0 0\n");
		  else
		    fprintf(stderr, "%g %g %g\n",av->cost[i],av->costStd[i],(double)av->ncost[i]/(double)av->maxExperiments);
		}
	    }
	  fprintf(f,"**************************************************\n");
	}

      /* Print the rest of statistics (exec time, path lenght,...) */
      mt=Mean(av->nSuccess,av->times);
      fprintf(f,"  Time (CPU sec) \n"); 
      fprintf(f,"    Mean         : %g\n",mt);
      fprintf(f,"    Std dev      : %g\n",StdDev(av->nSuccess,mt,av->times));

      mt=Mean(av->nSuccess,av->memory);
      fprintf(f,"  Memory (Mb) \n"); 
      fprintf(f,"    Mean         : %g\n",mt);
      fprintf(f,"    Std dev      : %g\n",StdDev(av->nSuccess,mt,av->memory));

      ml=Mean(av->nSuccess,av->pathLength);
      fprintf(f,"  Path length\n");
      fprintf(f,"    Mean         : %g\n",ml);
      fprintf(f,"    Std dev      : %g\n",StdDev(av->nSuccess,ml,av->pathLength));
	      
      ml=Mean(av->nSuccess,av->pathCost);
      fprintf(f,"  Path Cost/Time\n");
      fprintf(f,"    Mean         : %g\n",ml);
      fprintf(f,"    Std dev      : %g\n",StdDev(av->nSuccess,ml,av->pathCost));

      if (av->nCharts!=NULL)
	{
	  mc=Mean(av->nSuccess,av->nCharts);
	  fprintf(f,"  Charts\n");
	  fprintf(f,"    Mean         : %g\n",mc);
	  fprintf(f,"    Std dev      : %g\n",StdDev(av->nSuccess,mc,av->nCharts));
	}
 
      if (av->nSamples!=NULL)
	{
	  ms=Mean(av->nSuccess,av->nSamples);
	  fprintf(f,"  Samples\n");
	  fprintf(f,"    Mean         : %g\n",ms);
	  fprintf(f,"    Std dev      : %g\n",StdDev(av->nSuccess,ms,av->nSamples));
	}
    }
  else
    fprintf(f,"  Not enough successes to generate statistics\n");  
}

void DeleteAverages(Taverages *av)
{
  free(av->times);
  free(av->memory);
  free(av->pathLength); 
  free(av->pathCost);
 
  if (av->nCharts!=NULL)
    free(av->nCharts);

  if (av->nSamples!=NULL)
    free(av->nSamples);

  if (av->maxIt!=NO_UINT)
    {
      free(av->time);
      free(av->timeStd);
      free(av->cost);
      free(av->costStd);
      free(av->ncost);
    }
}
