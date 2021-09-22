#ifndef STATISTICSH
#define STATISTICSH

#include "boolean.h"

#include <time.h>
#include <sys/times.h>
#include <stdio.h>


/** 
   \file statistics.h
   \brief  Definition of the Tstatistics type and the associated functions. 
   
   Module for keeping track of the workings of the CuikSolve process.

   \sa Tstatistics, statistics.c.
*/


/** 
   \brief Statistics associated with a solving process.

   Statistics associated with a solving process.

   \sa statistics.h, statistics.c
*/
typedef struct { 

  double t_init; /**< Time at which CuikSolve was started 
                      (actually at which InitStatistics was called). */

  unsigned int np; /**< Number of processors used. */
  
  double volume; /**< Volume of the search space. */
  double s_volume; /**< Volume of the solution list.*/
  double s_diagonal;   /**< Max diagonal for all solution boxes.*/

  unsigned int n_max_level;             /**< Maximum depth of the (in process) boxes tree.*/

  unsigned int n_processed_boxes;       /**< Total number of boxes processes.*/
  unsigned int n_solution_boxes;        /**< Total number of solution boxes found.*/ 
  unsigned int n_validated_solution_boxes; /**< Total number of validated solution boxes found.*/
  unsigned int n_empty_boxes;           /**< Boxes that become empty while they are processed*/
  unsigned int n_splitted_boxes;        /**< Boxes that had to be split*/

  unsigned int n_lost_boxes;            /**< Lost boxes, i.e., boxes sent to other processors that returned late. */

  unsigned int n_box_reductions;        /**< Number fo time the ReduceBox function was used. */
   
  unsigned int n_errors;                /**< Number of errors (simplex errors!) while reducing a box. */
} Tstatistics;

/** 
   \brief Constructor

   Initializes a set of statistics.

   \param np Number of processors.
   \param v Volume of the search space.
   \param t The statistics to initialize.
*/
void InitStatistics(unsigned int np,double v,Tstatistics *t);

/** 
   \brief Copy constructor

   Initializes a set of statistics fom another set.

   \param t_dst The statistics to initialize.
   \param t_src The statistics from where to copy.
*/
void CopyStatistics(Tstatistics *t_dst,Tstatistics *t_src);

/** 
   \brief Curent time

   Returns the current time. The wayt to get the time is different
   for single-processor or for multiple-processor environments.

   \param t The statistics.

   \return The current time.
*/
double GetTime(Tstatistics *t);

/** 
   \brief Elapsed time

   Returns the time since the statistics where initialized.

   \param t The statistics to query.

   \return The elapsed time.
 */
double GetElapsedTime(Tstatistics *t);

/** 
   \brief Initial time

   Returns the time at which the statistics where initialized.

   \param t The statistics to query.

   \return The initialization time.
*/
double GetInitialTime(Tstatistics *t);


/** 
   \brief Sets a new initial time.

   Sets a new initial time. This is used when re-starting a process after a crash.

   \param tm The new initial time.
   \param t The statistics to query.
*/
void SetInitialTime(double tm,Tstatistics *t);

/** 
   \brief Sets a new maximum level.

   Sets a new max level. If the given level is below the stored
   one nothing is done.

   \param m The new maximum level.
   \param t The statistics to udpate.
*/
void NewMaxLevel(unsigned int m,Tstatistics *t);

/** 
   \brief Increases the number of processed boxes.

   Increases the number of processed boxes.
 
   \param t The statistics to update.
*/
void NewBoxProcessed(Tstatistics *t);

/** 
   \brief Increases the number of solution boxes.

   Increases the number of solution boxes.
 
   \param validated TRUE if the solution is validated to include a solution point.
   \param v Volume of the solution box.
   \param d Diagonal of the solution box.
   \param t The statistics to update.
 */
void NewSolutionBox(boolean validated,double v,double d,Tstatistics *t);

/**
   \brief Increases the number of empty boxes.

   Increases the number of empty boxes.
 
   \param t The statistics to update.
 */
void NewEmptyBox(Tstatistics *t);

/** 
   \brief Increases the number of splitted boxes.

   Increases the number of splitted boxes.
 
   \param t The statistics to update.
*/
void NewSplittedBox(Tstatistics *t);

/** 
   \brief Increases the number of errors when reducing a boxe.

   Increases the number of errors when reducing a boxe.
 
   \param t The statistics to update.
*/
void NewRBError(Tstatistics *t);

/** 
   \brief Increases the number of lost boxes.

   Increases the number of lost boxes.
 
   \param t The statistics to update.
*/
void NewLostBox(Tstatistics *t);

/** 
   \brief Increases the number of reduced boxes.

   Increases the number of reduced boxes.
 
   \param t The statistics to update.
*/
void NewBoxReduction(Tstatistics *t);

/** 
   \brief Gets the number of reduced boxes.

   Gets the number of reduced boxes.
 
   \param t The statistics to query.
   
   \return The number of reduced boxes up to the moment.
*/
unsigned int GetNBoxReductions(Tstatistics *t);

/** 
   \brief Gets the number of solution boxes.

   Gets the number of solution boxes.
 
   \param t The statistics to query.
   
   \return The number of solution boxes up to the moment.
*/
unsigned int GetNSolutionBoxes(Tstatistics *t);

/** 
   \brief Resets the number of reduced boxes.

   Resets the number of reduced boxes.
 
   \param t The statistics to update.
*/
void ResetNBoxReductions(Tstatistics *t);

/** 
   \brief Increases the number of reduced boxes.

   Increases the number of reduced boxes.
   
   \param nr Number of reduced boxes to add to the current statistis.
   \param t The statistics to update.
*/
void AddNBoxReductions(unsigned int nr,Tstatistics *t);

/** 
   \brief Prints the statistics to a file.

   Write the statistics sets to a stream that can be \e stdout.
   The moment at which the statistics are written is taken
   as the moment at which the solving process is done.

   \param f The stream
   \param t The statistics to print.
*/
void PrintStatistics(FILE *f,Tstatistics *t);

/** 
   \brief Saves the statistics to a file in binary format.

   Saves the statistics to a file in binary format. Used to save the internal
   state of the solver.

   \param f The file
   \param t The statistics to print.
*/
void SaveStatistics(FILE *f,Tstatistics *t);

/** 
   \brief Loads the statistics from a file in binary format.

   Loads the statistics from a file in binary format. Used to retrive the internal
   state of the solver from a \e .state file.

   \param f The file
   \param t The statistics to print.
*/
void LoadStatistics(FILE *f,Tstatistics *t);

/** 
   \brief Destructor

   Deletes the statistics structure and frees the allocated memory.

   \param t The statistics to delete.
*/
void DeleteStatistics(Tstatistics *t);

#endif
