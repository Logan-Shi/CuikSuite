#ifndef AVERAGESH
#define AVERAGESH

#include "boolean.h"
#include "parameters.h"

#include <stdio.h>

/** 
   \file averages.h

   \brief Auxiliary functions to deal averages of path planner executions.

   Auxiliary functions to deal averages of path planner executions.
   
   \sa averages.c
*/

/** 
  \brief Iterations between printed data on time/cost.

  Iterations between printed data on time/cost.
*/
#define ITERATIONS_BETWEEN_DATA 100

/** 
    \brief Structure to store expeeriment results.

    Structure used to store results from path planning experiments and
    then to compute their average in serveral dimensions.
*/
typedef struct {
  unsigned int maxExperiments;  /**< Maximum number of experiments to perform. */
  unsigned int nSuccess;        /**< Number of succesful experiments so far. */

  double *times;                /**< Time used in each succesful experiment. */
  double *memory;               /**< Memory used in each succesful experiment. */
  double *pathLength;           /**< Path length for each succesful experiment. */
  double *pathCost;             /**< PathCost  for each succesful experiment. */

  double *nCharts;              /**< Number of charts used in in each succesful experiment. */
  double *nSamples;             /**< Number of samples used in in each succesful experiment. */

  unsigned int maxIt;           /**< Maximum number of iterations per experiment. NO_UINT
				     unless you want to collect data of the time/cost
				     per iteration. */

  double *time;                 /**< Time per iteration. */
  double *timeStd;              /**< Std. deviation of the time per iteration. */

  double *cost;                 /**< Cost per iteration. */
  double *costStd;              /**< Std. deviation of the cost per iteration. */
  unsigned int *ncost;          /**< Number of cost measures considered per iteration.
				     The cost data is only coolected from the point the
				     goal is found. Different executions give data from
				     different iterations. So, each cost is averaged
				     for a different number of data. */

} Taverages;

/** 
    \brief Initializes a set of averages.

   Initializes a set of averages. This is used by different planners and, thus,
   it is parametrizable since each planner uses its own elements (samples, charts
   or both).

   \param m Max number of experiments.
   \param useCharts TRUE if the experiment involves charts.
   \param useSamples TRUE if the experiment involves samples.
   \param maxIt If different from NO_UINT, we store statistics of the cost 
                and time per iteration. This is only used in RRTStar algorithms.
   \param av The average set.
*/
void InitAverages(unsigned int m,boolean useCharts,boolean useSamples,
		  unsigned int maxIt,Taverages *av);

/** 
    \brief Adds data of a new experiment.

   \param t Time used (in seconds).
   \param mem The memory used (in bytes).
   \param pl Path lenght.
   \param pc Path cost.
   \param nc Number of charts (sometimes not used, see \ref InitAverages).
   \param ns Number of samples (sometimes not used, see \ref InitAverages).
   \param time Execution time per iteration. Only used if different form NULL
               and if maxIt is different form NO_UINT in \ref InitAverages.
   \param cost Cost to goal per iteration. Only used if different form NULL
               and if maxIt is different form NO_UINT in \ref InitAverages.
   \param av The average set to update.
*/
void NewSuccesfulExperiment(double t,unsigned int mem,double pl,double pc,
			    unsigned int nc,unsigned int ns,
			    double *time,double *cost,
			    Taverages *av);

/** 
    \brief Prints a header to the averages results.

   Prints the header of the averages of a set of experiments.

   This is separated from \ref PrintAverages because in some
   cases we insert some information between the header and the
   averages themselves.

   \param f The file where to print the header.
   \param argc Number of parameters used when calling the program.
   \param arg The parameters.
   \param av The averages to print.
*/
void PrintAveragesHeader(FILE *f,int argc, char **arg,Taverages *av);

/** 
    \brief Prints the averages of a set of experiments.

   Prints the averages of a set of experiments.
   If 'p' and 'pn' are different from NULL, the header is automatically
   added before the statistics info.

   \param f The file where to print the averages.
   \param av The averages to print.
*/
void PrintAverages(FILE *f,Taverages *av);

/** 
    \brief Deletes the space used by a set of averages.

   Release the memory used by a set of averages.

   \param av The set of averages.
*/
void DeleteAverages(Taverages *av);

#endif
