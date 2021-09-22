#include "statistics.h"

#include <unistd.h>
#include <time.h>


/** 
   \file statistics.c

   \brief Implementation of the functions operating on Tstatistics.
   
   Implementation of the functions operating on Tstatistics.

   \sa Tstatistics, statistics.h.
*/


/*
 * Resets the statistics
 */
void InitStatistics(unsigned int np,double v,Tstatistics *t)
{ 
  t->np=np;
  t->volume=v;
  t->s_volume=0.0;
  t->s_diagonal=0.0;

  t->n_max_level=0;

  t->n_processed_boxes=0;
  t->n_solution_boxes=0;
  t->n_validated_solution_boxes=0;
  t->n_empty_boxes=0;
  t->n_splitted_boxes=0;

  t->n_lost_boxes=0;

  t->n_box_reductions=0;

  t->n_errors=0;

  t->t_init=GetTime(t);
}

void CopyStatistics(Tstatistics *t_dst,Tstatistics *t_src)
{
  t_dst->volume=t_src->volume;
  t_dst->s_volume=t_src->s_volume;
  t_dst->s_diagonal=t_src->s_diagonal;

  t_dst->n_max_level=t_src->n_max_level;

  t_dst->n_processed_boxes=t_src->n_processed_boxes;
  t_dst->n_solution_boxes=t_src->n_solution_boxes;
  t_dst->n_validated_solution_boxes=t_src->n_validated_solution_boxes;
  t_dst->n_empty_boxes=t_src->n_empty_boxes;
  t_dst->n_splitted_boxes=t_src->n_splitted_boxes;

  t_dst->n_lost_boxes=t_src->n_lost_boxes;

  t_dst->n_box_reductions=t_src->n_box_reductions;

  t_dst->n_errors=t_src->n_errors;
  
  t_dst->t_init=t_src->t_init;
}

/*
  Auxiliary function to get the time since the current process was
  started. In a multi-processor environment
  the result is the number of seconds since
  the Epoch (this is still useful for counting elapsed times)
*/
double GetTime(Tstatistics *t)
{
  if (t->np>1)
    return((double)time(NULL));
  else
    {
      double ts;
      struct tms tm;

      times(&tm);
      ts=(double)sysconf(_SC_CLK_TCK); /*tics per second*/
      return((double)((tm.tms_utime)+(tm.tms_stime)+(tm.tms_cutime)+(tm.tms_cstime))/ts);
    } 
}

/*
  Returns the time (in seconds) since the InitStatistics was called
*/
double GetElapsedTime(Tstatistics *t)
{
  return(GetTime(t)-t->t_init);
}

/*
  Auxiliariy function to get the time at which InitStatistics was called
*/
double GetInitialTime(Tstatistics *t)
{
  return(t->t_init);
}

/*
  Auxiliariy function to set the time at which InitStatistics was called
  This is used when re-starting a process after a crash
*/
void SetInitialTime(double tm,Tstatistics *t)
{
  t->t_init=tm;
}

/*
 * To assess the maximum number of boxes in the list of boxes still to be processed
 */
void NewMaxLevel(unsigned int m,Tstatistics *t)
{
  if (m>t->n_max_level) 
    t->n_max_level=m;
}

/*
 * To assess the number of processes boxes
 */
void NewBoxProcessed(Tstatistics *t)
{
  t->n_processed_boxes++; 
}

/*
 * To assess the number of solution boxes
 */
void NewSolutionBox(boolean validated,double vs,double d,Tstatistics *t)
{
  if (d>t->s_diagonal) t->s_diagonal=d;
  t->s_volume+=vs;
  t->n_solution_boxes++;
  if (validated)
    t->n_validated_solution_boxes++;
}

/*
 * To assess the number of boxes that, after the process of the box,
 * become emtpy
 */
void NewEmptyBox(Tstatistics *t)
{
  t->n_empty_boxes++; 
}

/*
 * To assess the number of boxes that, after the process of the box,
 * are splitted
 */
void NewSplittedBox(Tstatistics *t)
{
  t->n_splitted_boxes++; 
}

/*
 * Number of errors in the Reduce Box process
 * 
 */
void NewRBError(Tstatistics *t)
{
  t->n_errors++; 
}

/*
 * Number of boxes send to process that returned too late and that were re-submitted
*/
void NewLostBox(Tstatistics *t)
{
  t->n_lost_boxes++;
}

/*
 * Number of times the function ReduceBox (Trapezoid Clipping) is used
 */
void NewBoxReduction(Tstatistics *t)
{  
  t->n_box_reductions++;  
}

unsigned int GetNBoxReductions(Tstatistics *t)
{
  return(t->n_box_reductions);
}

unsigned int GetNSolutionBoxes(Tstatistics *t)
{
  return(t->n_solution_boxes);
}

void ResetNBoxReductions(Tstatistics *t)
{
  t->n_box_reductions=0; 
}

void AddNBoxReductions(unsigned int nr,Tstatistics *t)
{
  t->n_box_reductions+=nr; 
}

/*
 * Prints all the collected statistics
 */   
void PrintStatistics(FILE *f,Tstatistics *t)
{
  double tm;

  tm=GetElapsedTime(t);

  fprintf(f,"STATITISTICS FOR Cuik:\n\n");

  fprintf(f,"Volume of the search space: %g\n",t->volume);
  fprintf(f,"Volume of the solution space: %g\n",t->s_volume);
  if (t->volume>0.0)
    fprintf(f,"  Volume ratio: %5.2f %%\n",t->s_volume/t->volume);
  fprintf(f,"Max solution diagonal: %g\n",t->s_diagonal);

  fprintf(f,"Number of processors: %u\n",t->np);
  fprintf(f,"User time in process: %f seg (%f min)\n",tm,tm/60.0);
 
  fprintf(f,"Box level information:\n");
  fprintf(f,"  N processed boxes : %6u\n",t->n_processed_boxes);
  fprintf(f,"  Max depth         : %6u\n",t->n_max_level);
  fprintf(f,"  Types of boxes:\n");  

  fprintf(f,"    N solution boxes: %6u (%u)",t->n_solution_boxes,t->n_validated_solution_boxes);
  if (t->n_processed_boxes>0)
    fprintf(f," (%5.2f%%)",(double)t->n_solution_boxes/(double)t->n_processed_boxes*100.0);
  fprintf(f,"\n");

  fprintf(f,"    N empty boxes   : %6u ",t->n_empty_boxes);
  if (t->n_processed_boxes>0)
    fprintf(f," (%5.2f%%)",(double)t->n_empty_boxes/(double)t->n_processed_boxes*100.0);
  fprintf(f,"\n");

  fprintf(f,"    N bisected boxes: %6u ",t->n_splitted_boxes);
  if (t->n_processed_boxes>0)
    fprintf(f," (%5.2f%%)",(double)t->n_splitted_boxes/(double)t->n_processed_boxes*100.0);
  fprintf(f,"\n");

  #if (_USE_MPI)
    fprintf(f,"    N lost boxes    : %6u ",t->n_lost_boxes);
    if (t->n_processed_boxes>0)
      fprintf(f," (%5.2f%%)",(double)t->n_lost_boxes/(double)t->n_processed_boxes*100.0);
    fprintf(f,"\n");
  #endif

  fprintf(f,"  Box Reductions    : %6u\n",t->n_box_reductions);
  fprintf(f,"  N Errors          : %6u \n\n",t->n_errors);

  fprintf(f,"\n==========================================================================\n\n");
}

/* saves in binary format */
void SaveStatistics(FILE *f,Tstatistics *t)
{
  fwrite(t,sizeof(Tstatistics),1,f);
}

/* loads from binary file */
void LoadStatistics(FILE *f,Tstatistics *t)
{
  fread(t,sizeof(Tstatistics),1,f);
}

/*
 * Deletes the statistics structure
 */
void DeleteStatistics(Tstatistics *t)
{
}
