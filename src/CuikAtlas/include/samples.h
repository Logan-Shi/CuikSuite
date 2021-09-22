#ifndef SAMPLESH
#define SAMPLESH

#include "chart.h"
#include "parameters.h"
#include "link.h"
#include "filename.h"
#include "dynamics.h"

/**  
   \file samples.h

   \brief Auxiliary functions to deal with sets of samples.

   Auxiliary functions to deal with sets of samples.
   
   Samples are used as start/goal for the planning and
   solution paths are sets of samples.

   \sa samples.c
*/

/** 
   \brief Initial number of samples (or steps) in a path.

   Initial number of samples (or steps) in a path. This will be
   enlarged if necessary.
*/
#define INIT_NUM_SAMPLES 50

/**  
   \brief Selects the way to plot paths.

   Paths are plotted with red lines connecting nodes and blue crosses defining each
   node. If this flag is set to 0, the crosses are not plotted (only
   the lines are shown).
*/
#define PATH_NODES 1


/** 
   \brief One of the possible smoothing methods.

   Using this method paths are shortened trying to define shorcuts between
   randomly selected elements in the original path. This methods is
   quite effective.
*/
#define SMOOTH_RANDOM 0

/** 
   \brief One of the possible smoothing methods.

   Using this method paths the length of the path is reduced using
   gradient descent. This produces very smooth paths but it is
   slow reaching a local minimum. Moreover, this minimum is typically
   local even in the current homotopy class. 
*/
#define SMOOTH_GRADIENT 1


/** 
   \brief One of the possible smoothing methods.

   This is like the \ref SMOOTH_RANDOM but the shotcuts are defined
   in a systematic way: try to reach as far as possible with a direct
   path from the first sample and so on.
*/
#define SMOOTH_SHORTCUT 2

/** 
   \brief One of the possible smoothing methods.

   This is \ref SMOOTH_GRADIENT but the measure to optimize is
   the control effort instead than the path lenght.
   This only make sense in tensegrity structures since they have
   an associated potential energy.
   In other structures this is very close the the path lenght
   optimization.
*/
#define SMOOTH_EFFORT 3

/** 
   \brief One of the possible smoothing methods.

   This is \ref SMOOTH_GRADIENT but the measure to optimize is
   the dispersion of the points along the path (i.e., try to
   make all steps of the same size). This is only used for
   debug since the dispersion is typically a secondary
   objective.
*/
#define SMOOTH_DISPERSION 4

/** 
   \brief Macro to easily switch the connection method.

   We have to modes to connect samples moving on the manifold
   of constratints: \ref ConnectSamples and \ref ConnectSamplesChart.
   The first one has been extensively tested. The second
   one is faster but less robust (we are working on improving
   this). This macro is just used to compare and debug
   these two connection methods.
*/
#define DEFAULT_CONNECT ConnectSamplesChart

/** 
   \brief Focus on the kinematic sub-space.

   If set to 1, functions like path length or some
   aspects of the path effort
   or even smooth path (using gradient descent!) focus
   on the kinematic sub-space, not considering the
   force-related variables.

   Obviously, this only has an effect if the problem
   includes force-related variables (i.e., in
   tensegrity problems).
*/
#define KINEMATIC_SUBSPACE 0

/** 
   \brief Corrects the 3d position of a point.

   When ploting a point we have to take into account the cuts in
   the 3D space introduced to avoid cuts in the middle of
   a cyclic manifold.

   \param cx Cut along the x dimension.
   \param cy Cut along the y dimension.
   \param cz Cut along the z dimension.
   \param x x dimension to correct.
   \param y y dimension to correct.
   \param z z dimension to correct.
*/
#define CORRECT_POINT_PLOT(cx,cy,cz,x,y,z){ if ((cx<0)&&(x<cx)) x+=M_2PI;if ((cx>0)&&(x>cx)) x-=M_2PI;if ((cy<0)&&(y<cy)) y+=M_2PI;if ((cy>0)&&(y>cy)) y-=M_2PI;if ((cz<0)&&(z<cz)) z+=M_2PI;if ((cz>0)&&(z>cz)) z-=M_2PI; }

/** 
   \brief Template of step costs.

   Functions that evaluate the cost of a path
   step should be of this type.

   Cost functions can involve up to 5 points around
   a given point
      - [xpp xp x xn xnn]
      .
   but each elementary cost evaluation only involves
   3 of these points.
   With this, x can be in up to three triplets
      - [xpp xp x]
      - [xp x xn]
      - [x xn xnn]
      .
   In other words, the "variation" of x can affect
   the cost over these three triplets.

   Cost functions are typically evaluated over paths
   (not only for individual steps). Care must be taken
   for the cost function not to return twice the 
   cost of a given step. For instance, the path length
   is the sum of the step lengts and the step length
   ony computes the distance between the first and
   second paramter for the triplets
      - [xp x xn]
      - [x xn xnn]
      .
   but returns 0 for the triplet [xpp xp x]. When
   evaluated in sequence this efectively gives the
   path lenght.
   In contrast, the path dispersion returns values
   for the tree triplets. 
   The step length is a 3-step function but the
   step dispersion is a 5-step function.

   See \ref StepLength or \ref StepEffort for 
   examples of path step costs.

   This is used in \ref GradientSmooth.

   The parameteres of a cost function are
     - The set of parameters.
     - The topology of the variables (in simplified system).
     - The selected variables to compute the path length 
       component of the effort.
     - The size of the points (in simplified system!)
     - First point in the path (simplified).
     - Second point in the path 
     - Third point along the path.
     - Which of the three points is the current point (0,1,2)
       Which of the three triplets defined above are we
       passing to the cost function.
     - A chart defined on the first point in the path.
     - A chart defined on the second point in the path.
     - A chart defined on the third point in the path.
     - The world structure.
     .
   
   Some of them might not be used but are given with the
   aim of permetting very general cost functions.
*/
typedef double (*TStepCost)(Tparameters *,unsigned int *,
			   boolean *,
			   unsigned int,
			   double *,double *,double *,
			   unsigned int,
			   Tchart*,Tchart *,Tchart *,Tworld *);

/** 
   \brief Template of step cost gradients.

   Functions that evaluate the gradient of the cost of a path
   step should be of this type.

   Gradients are not evaluated in sequence and accumulated 
   but called for individual points. Thus, the output
   of the gradient is the accumulated gradient for the
   tree triplets
      - [xpp xp x]
      - [xp x xn]
      - [x xn xnn]
      .
    with [xpp xp x xn xnn] the five points around x.

   See \ref StepLengthGradient or \ref StepEffortGradient 
   for example of path step cost gradients.

   This is used in \ref GradientSmooth.

   The parameters of a gradient function are:
     - The set of parameters.
     - The topology of the variables (in simplified system).
     - The selected variables to compute the gradient.
     - The size of the points (in simplified system!)
     - Previous of the previous point in the path.
     - Previous point in the path.
     - Current point. We compute the gradient with respect to this point.
     - Next point in the path.
     - Next of the next point in the path.
     - A chart defined on x-2
     - A chart defined on x-1.
     - A chart defined on x.
     - A chart defined on x+1.
     - A chart defined on x+2
     - The Jacobian of the constraints. Only used for numerical gradients.
     - The cost function (only used in numerical evaluation).
     - The output gradient (in tangent space)
     - The world structure.
     .

   Some of them might not be used but are given with the
   aim of permetting very general cost functions.
*/
typedef boolean (*TStepCostGradient)(Tparameters *,unsigned int *,
				     boolean *,unsigned int,
				     double *,double *,double *,double *,double *,
				     Tchart *,Tchart *,Tchart *,Tchart *,Tchart *,
				     TJacobian *,TStepCost,
				     double *,Tworld *);

/** 
   \brief Initializes a set of samples.

   Initializes the space where to store the samples.

   \param ms Max number of samples in the set. This will be
             automatically enlarged in \ref AddSample2Samples if necessary.
   \param ns Number of samples in the set. 0 after initialization.
   \param path The sample set.
*/
void InitSamples(unsigned int *ms,unsigned int *ns,double ***path);

/** 
   \brief Initializes a set of samples with flag

   Initializes the space where to store the samples used to reply
   a simulation (e.g., to re-grow an RRT branch without the
   computational burden of re-generating the samples, which is
   particularly expensive in problems with dynamics).

   \param ms Max number of samples in the set. This will be
             automatically enlarged in \ref AddSample2Samples if necessary.
   \param ns Number of samples in the set. 0 after initialization.
   \param path The sample set.
   \param newChart TRUE if a chart is generated at the corresponding step.
                   If this is NULL, it is not used.
   \param time Time lapse from the previous step.
               If NULL, it is not used.
   \param cost Cost of the transition.
               If NULL, it is not used.
*/
void InitSamplesReplay(unsigned int *ms,unsigned int *ns,double ***path,
		       boolean **newChart,double **time,double **cost);

/** 
   \brief Initializes a trajectory.

   Initializes the space where to store the trajectory.

   \param ms Max number of samples in the set. This will be
             automatically enlarged in \ref AddSample2Samples if necessary.
   \param ns Number of samples in the set. 0 after initialization.
   \param path The sample set.
   \param da Dimesion of the action space (of the action vectors).
   \param actions The action executed at each step.
   \param times The time for each step.
*/
void InitTrajectory(unsigned int *ms,unsigned int *ns,double ***path,
		    unsigned int da,double ***actions,double **times);
/** 
   \brief Path smoothing.

   Produces a path that (locally) minimizes the length and connects
   the two extremes of the given path.

   This implements a basic smoothing structure transforming the input
   samples (in the original system) to the simplified system and then
   call a speciallized smoothing procedure.

   Only path with more than 2 steps are suitable of optimization. 
   Otherwise this function triggers an error.

   \param pr The set of parameters.
   \param parallel TRUE if we have to execute a parallel vesion of
                   smoothing process. Not relevant in SMOOTH_CUT.
   \param mode Smoothing mode to be used: SMOOTH_RANDOM, SMOOTH_GRADIENT,
               or SMOOTH_CUT.
   \param maxIterations Maximum number of iterations. To be scaled
                        by the number of steps in the path.
   \param ns The numer of samples in the input path.
   \param path The samples in the input path.
   \param sns The number of samples in the output (smoothed) path.
   \param spath The samples in the output (smoothed) path.
   \param w The The world/cuiksystem on which the sample is defined.
*/
void SmoothSamples(Tparameters *pr,boolean parallel,int mode,
		   unsigned int maxIterations,
		   unsigned int ns,double **path,
		   unsigned int *sns,double ***spath,TAtlasBase *w);

/** 
   \brief Concats two path.

   Produces a path that is the concatenation of two paths.

   \param nvs The number of values per sample.
   \param ns1 The number of samples defining the first path.
   \param path1 The collection of samples defining the first path.
   \param ns2 The number of samples defining the second path.
   \param path2 The collection of samples defining the second path.
   \param ns The number of samples defining the output path.
   \param path The collection of samples defining the output path.
*/
void ConcatSamples(unsigned int nvs,
		   unsigned int ns1,double **path1,
		   unsigned int ns2,double **path2,
		   unsigned int *ns,double ***path);

/** 
   \brief Reverses and concats a path.

   Produces a path that is the concatenation of a path and the
   reverse of a second path. This is basically used to reconstruct
   paths for bidirectional (Atlas)RRTs.

   \param nvs The number of values per sample.
   \param ns1 The number of samples defining the first path.
   \param path1 The collection of samples defining the first path.
   \param ns2 The number of samples defining the second path.
   \param path2 The collection of samples defining the second path.
   \param ns The number of samples defining the output path.
   \param path The collection of samples defining the output path.
*/
void ReverseConcatSamples(unsigned int nvs,
			  unsigned int ns1,double **path1,
			  unsigned int ns2,double **path2,
			  unsigned int *ns,double ***path);
/** 
   \brief Reverses and concats a trajectory.

   Version of \ref ReverseConcatSamples but for trajectories.

   We assume that the first path is from the \ref START2GOAL tree
   and that the second path is from the \ref GOAL2START tree. This
   is critical since the semantic of the actions is different
   in each tree.

   \param nvs The number of values per sample.
   \param da Dimension of the action space.
   \param ns1 The number of samples defining the first path.
   \param path1 The collection of samples defining the first path.
   \param action1 The action executed to reach the corresponding
                  state in \e path1
   \param time1 The time to execute the corresponding action in
                \e action1.
   \param ns2 The number of samples defining the second path.
   \param path2 The collection of samples defining the second path.
   \param action2 The action executed to reach the next 
                  state in \e path2. Note the difference with
		  respect to \e action1. Action1 is the action
		  from the previous state to the current and
		  action2 is the action from the current state
		  to the next.
   \param time2 The time to execute the corresponding action in
                \e action2.
   \param ns The number of samples defining the output path.
   \param path The collection of samples defining the output path.
   \param action Action executed to reach each sample.
   \param time Duration of each action.
*/
void ReverseConcatTrajectories(unsigned int nvs,unsigned int da,
			       unsigned int ns1,double **path1,double **action1,double *time1,
			       unsigned int ns2,double **path2,double **action2,double *time2,
			       unsigned int *ns,double ***path,double ***action,double **time);

/**  
  \brief Reverses a set of samples.

  Reverses a set of samples.

  \param ns Number of samples.
  \param path The samples to reverse.
*/
void ReverseSamples(unsigned int ns,double **path);

/**  
   \brief Adds a sample to a set of samples.

   Adds a sample to a set of samples. The sample is given in full form
   (including all variables) but we only store the system variables.

   \param nv Number of variables.
   \param sample The sample to add.
   \param nvs Number of system variables.
   \param systemVars Array to identify the system variables. Use NULL if
                     all variables are to be included in the sample.
   \param ms Max number of samples in the set. This will be
             automatically enlarged in \ref AddSample2Samples if necessary.
   \param ns Number of samples in the set. 0 after initialization.
   \param path The sample set.
*/
void AddSample2Samples(unsigned int nv,double *sample,
		       unsigned int nvs,boolean *systemVars,
		       unsigned int *ms,unsigned int *ns,double ***path);

/**  
   \brief Adds a sample to a set of samples for replay.

   Adds a sample to a set of samples used to reply simulations
   (i.e., to re-simulate a brach without the expensive process
   to generate the samples). See \ref InitSamplesReplay

   \param nv Number of variables.
   \param sample The sample to add.
   \param nc TRUE if a chart is created at the new sample.
   \param h The time from the previous sample.
   \param c The cost of the transition.
   \param nvs Number of system variables.
   \param systemVars Array to identify the system variables. Use NULL if
                     all variables are to be included in the sample.
   \param ms Max number of samples in the set. This will be
             automatically enlarged in \ref AddSample2Samples if necessary.
   \param ns Number of samples in the set. 0 after initialization.
   \param path The sample set.
   \param newChart TRUE if a chart is created at this step.
                   May be NULL and then it is not used.
   \param time Time lapse from the previous step.
               May be NULL and then it is not used.
   \param cost Cost of the transition.
               May be NULL and then it is not used.
*/
void AddSample2SamplesReplay(unsigned int nv,double *sample,boolean nc,double h,double c,
			     unsigned int nvs,boolean *systemVars,
			     unsigned int *ms,unsigned int *ns,double ***path,
			     boolean **newChart,double **time,double **cost);

/**  
   \brief Adds a step to a trajectory.

   Adds a step to a trajectory.

   \param nv Number of variables.
   \param sample The sample to add.
   \param nvs Number of system variables.
   \param systemVars Array to identify the system variables. Use NULL if
                     all variables are to be included in the sample.
   \param action The executed action. Vector of size da.
   \param time The duration of the action.
   \param ms Max number of samples in the set. This will be
             automatically enlarged in \ref AddSample2Samples if necessary.
   \param ns Number of samples in the set. 0 after initialization.
   \param path The sample set.
   \param da The dimension of the action space. The size of the action vectors
   \param actions The action executed at each time step.
   \param times The duration of each action.
*/
void AddStep2Trajectory(unsigned int nv,double *sample,
			unsigned int nvs,boolean *systemVars,
			double *action,double time,
			unsigned int *ms,unsigned int *ns,double ***path,
			unsigned int da,double ***actions,double **times);
/** 
   \brief Forwarnd integration of the equations of motion.

   Version of \ref ConnectDynamicStates where the action is adjusted 
   at each step using inverse dynamics.

   \param pr The set of parameters.
   \param tp The topology of the variables.
   \param ambient The ambient space limits.
   \param collision TRUE if collisions have to be avoided.
   \param m The size of each sample. IMPORTANT: here samples are suposed to be
            given in the simplified form and not in the non-simplified one, as it is
	    the case of many of the functions on samples.
   \param k The dimension of the tangent space.
   \param da The dimension of the action space.
   \param state The state from where to start the simulation.
   \param action The action to execute.
   \param time The time to execute the action.
   \param goal The goal to be reached.
   \param ns The number of stats of the integrated trajectory.
   \param path The states in the integrated trajectory.
   \param actions The action in the integrated trajectory. This is just
                  a repetition of the input \e action.
   \param times The integration step of each step.
   \param J The Jacobian of the system of equations.
   \param ds The dynamics space (memory space used during integration).
   \param w The world/cuiksystem on which the sample is defined.

   \return The distance to the goal or \ref INF if the integration
           fails for any reason (for instance if a collision is detected).
*/
double ConnectDynamicStatesID(Tparameters *pr,unsigned int *tp,Tbox *ambient,boolean collision,
			      unsigned int m,unsigned int k,unsigned int da,
			      double *state,double *action,double time,double *goal,
			      unsigned int *ns,double ***path,double ***actions,double **times,
			      TJacobian *J,TDynamicSpace *ds,TAtlasBase *w);

/** 
   \brief Forwarnd integration of the equations of motion.

   Integrates the dynamic constraints with the aim of reaching a particular goal
   This is the dynamic version of \ref ConnectSamples.

   \param pr The set of parameters.
   \param tp The topology of the variables.
   \param ambient The ambient space limits.
   \param collision TRUE if collisions have to be avoided.
   \param m The size of each sample. IMPORTANT: here samples are suposed to be
            given in the simplified form and not in the non-simplified one, as it is
	    the case of many of the functions on samples.
   \param k The dimension of the tangent space.
   \param da The dimension of the action space.
   \param state The state from where to start the simulation.
   \param action The action to execute.
   \param time The time to execute the action.
   \param goal The goal to be reached.
   \param ns The number of stats of the integrated trajectory.
   \param path The states in the integrated trajectory.
   \param actions The action in the integrated trajectory. This is just
                  a repetition of the input \e action.
   \param times The integration step of each step.
   \param J The Jacobian of the system of equations.
   \param ds The dynamics space (memory space used during integration).
   \param w The world/cuiksystem on which the sample is defined.

   \return The distance to the goal or \ref INF if the integration
           fails for any reason (for instance if a collision is detected).
*/
double ConnectDynamicStates(Tparameters *pr,unsigned int *tp,Tbox *ambient,boolean collision,
			    unsigned int m,unsigned int k,unsigned int da,
			    double *state,double *action,double time,double *goal,
			    unsigned int *ns,double ***path,double ***actions,double **times,
			    TJacobian *J,TDynamicSpace *ds,TAtlasBase *w);

/**  
   \brief Determines the connection between two points on the manifold.

   Determines if two points on the manifold can be connected with a path of length
   below a given threshold.

   This is the same as \ref ConnectSamples but using a chart-based way to 
   move over the manifold from s1 to s2.

   As in the case of \ref ConnectSamples the connection can fail depending
   on the shape of the manifold. However, for close samples it typically
   works fine.

   This can be seen as a simple version of \ref AddBranchToAtlasRRT. The main
   difference is that here we do not maintain an atlas: we generate charts as
   we advance over the manifold but we release them when they are not any longer
   useful.

   IMPORTANT: here samples are suposed to be
   given in the simplified form and not in the non-simplified one, as it is
   the case of many of the functions on samples.

   \param pr The set of parameters.
   \param tp The topology for the variables.
   \param sv Components of the configuration to use to compute the length of the connection.
             If NULL all components are used. Up to now, it is only used for path smoothing 
	     purposes.
   \param domain The domain for the variables.
   \param m The size of each sample. IMPORTANT: here samples are suposed to be
            given in the simplified form and not in the non-simplified one, as it is
	    the case of many of the functions on samples.
   \param n The number of equations in the problem. This is actually not used in
            this function but we keep this parameter for compatibility with
	    \ref ConnectSamples.
   \param s1 The first sample to connect.
   \param s2 The second sample to connect.
   \param md Maximum displacement between the two samples (along the
             components selected by 'sv').
   \param checkCollisions TRUE if the path has to be collision free.
   \param sJ The symbolic Jacobian.
   \param reached (output) TRUE if s2 can be reached form s1.
   \param collision (output) TRUE if the connection can not be established due
                    to a collision.
   \param lastSample Buffer to store the last sample generated along the path 
                     from s1 to s2. Set to NULL if this sample is not requiered. 
   \param ns Number of steps of the path connecting the two samples.
   \param path Samples along the path connecting the two samples. Set ns or path to
               NULL if you are not interested in the path but only in verifying that
	       the two samples can be connected. Note that the two given samples are
	       NOT included in this output path.
   \param w The world/cuiksystem on which the sample is defined.

   \return The maximum distance travelled form s1 to s2. The distance from s1 to
           the sample stored in 'lastSample', if any.
*/
double ConnectSamplesChart(Tparameters *pr,unsigned int *tp,
			   boolean *sv,Tbox *domain,
			   unsigned int m,unsigned int n,
			   double *s1,double *s2,
			   double md,boolean checkCollisions,
			   TJacobian *sJ,
			   boolean *reached,boolean *collision,double *lastSample,
			   unsigned int *ns,double ***path,
			   TAtlasBase *w);

/**  
   \brief Determines the connection between two points on the manifold.

   Determines if two points on the manifold can be connected with a path of length
   below a given threshold.

   The method used to determine the path does not return the sortest path and it can
   fail in many cases, specially when the samples are far away.

   IMPORTANT: here samples are suposed to be
   given in the simplified form and not in the non-simplified one, as it is
   the case of many of the functions on samples.

   \param pr The set of parameters.
   \param tp The topology for the variables.
   \param sv Components of the configuration to use to compute the length of the connection.
             If NULL all components are used. Up to now, it is only used for path smoothing 
	     purposes.
   \param domain The domain for the variables.
   \param m The size of each sample. IMPORTANT: here samples are suposed to be
            given in the simplified form and not in the non-simplified one, as it is
	    the case of many of the functions on samples.
   \param n The number of equations in the problem.
   \param s1 The first sample to connect.
   \param s2 The second sample to connect.
   \param md Maximum displacement between the two samples (along the
             components selected by 'sv').
   \param checkCollisions TRUE if the path has to be collision free.
   \param sJ The symbolic Jacobian. It is actually not used in this function but
             the parameter is keep for compatibility with \ref ConnectSamplesChart.
	     You can safely set it to NULL in this case.
   \param reached (output) TRUE if s2 can be reached form s1.
   \param collision (output) TRUE if the connection can not be established due
                    to a collision.
   \param lastSample Buffer to store the last sample generated along the path 
                     from s1 to s2. Set to NULL if this sample is not requiered. 
   \param ns Number of steps of the path connecting the two samples.
   \param path Samples along the path connecting the two samples. Set ns or path to
               NULL if you are not interested in the path but only in verifying that
	       the two samples can be connected. Note that the two given samples are
	       NOT included in this output path.
   \param w The The world/cuiksystem on which the sample is defined.

   \return The maximum distance travelled form s1 to s2. The distance from s1 to
           the sample stored in 'lastSample', if any.
*/
double ConnectSamples(Tparameters *pr,unsigned int *tp,
		      boolean *sv,Tbox *domain,
		      unsigned int m,unsigned int n,
		      double *s1,double *s2,
		      double md,boolean checkCollisions,
		      TJacobian *sJ,
		      boolean *reached,boolean *collision,double *lastSample,
		      unsigned int *ns,double ***path,
		      TAtlasBase *w);

/** 
   \brief Length of a path formed by a set of samples.

   Computes the length of a path defined by a set of points. 
   IMPORTANT: this is for internal use only and the points are defined
   in the simplified system and not in the original system as most of
   the functions on samples.

   \param tp The topology of the variables.
   \param sv The components to use in the distance computation.
   \param m The size of each point.
   \param np Number of points in the path.
   \param point The set of points.

   \return The path length.
*/
double PathLength(unsigned int *tp,
		  boolean *sv,unsigned int m,
		  unsigned int np,double **point);

/** 
   \brief Approximated control effort of a path.

   Computes the approximated control effort of a path.
   This only makes sense in problems where there is 
   an associated energy which generates a force field
   (i.e., the gradient of the energy).
   The control effort is the effort to compensate this
   force field and to drive the robot along the path.
   If no force filed is defined, the control effort
   gives the path length (see \ref PathLength).

   The control effort is defined over the continuous
   path and we approximate it at discrete times
   (i.e., an integral approximated as a discrete sum).

   \param p The set of parameters.
   \param m The size of each point.
   \param np Number of points in the path.
   \param point The set of points.
   \param w The world structure giving semantic to the path
            points.

   \return The (approximated) control effort along the path.
*/
double PathEffort(Tparameters *p,
		  unsigned int m,unsigned int np,double **point,
		  Tworld *w);
  
/**  
   \brief Reads one sample from a file.

   Reads one sample from a file.
   
   If the mechanisms representation is DOF-based (see \ref REP_JOINTS)
   the samples are read from a .dof file. Otherwise they are read
   from a .samples file.

   \param p The set of parameters.
   \param fname File from where to read the sample.
   \param nvs Number of system variables in the problem = Number of values 
              in the sample.
   \param s Where to store the sample. The space is allocated internally.
   
   \return The dimensionality of the sample. Number of system variables
           of \e w.
*/
unsigned int ReadOneSample(Tparameters *p,char *fname,unsigned int nvs,double **s);

/**  
   \brief Reads two samples from a file.

   Reads two sample from a file.

   If the mechanisms representation is DOF-based (see \ref REP_JOINTS)
   the samples are read from a .dof file. Otherwise they are read
   from a .samples file.

   \param p The set of parameters.
   \param fname File from where to read the sample.
   \param nvs Number of system variables in the problem = Number of values 
              in the sample.
   \param s1 Where to store the first sample. The space is allocated internally.
   \param s2 Where to store the second sample. The space is allocated internally.
   
   \return The dimensionality of the sample. Number of system variables
           of \e w.
*/
unsigned int ReadTwoSamples(Tparameters *p,char *fname,unsigned int nvs,double **s1,double **s2);

/**  
   \brief Saves a set of samples to a file.

   Saves a set of samples (possibly defining a solution path) to a file.

   \param fname The file where to store the samples.
   \param suffix Suffix to be added to the filename. It is used
                 when generating smoothed paths.
   \param nvs The dimensionality of each sample.
   \param ns The number of samples defining the path.
   \param path The collection of samples defining the path.
*/
void SaveSamples(char *fname,char *suffix,unsigned int nvs,
		 unsigned int ns,double **path);

/**  
   \brief Saves a set of samples to a file including action and timing information.

   Saves a set of samples (possibly defining a solution path) to a file
   including action and timing information. Thus, the result is a trajectory.

   \param fname The file where to store the samples.
   \param suffix Suffix to be added to the filename. It is used
                 when generating smoothed paths.
   \param nvs The dimensionality of each sample.
   \param ns The number of samples defining the path.
   \param path The collection of samples defining the path.
   \param da The dimension of the action space (of the action vectors).
   \param action Actions executed at each time step.
   \param time Duration of the execution of each action.
*/
void SaveTrajectory(char *fname,char *suffix,unsigned int nvs,
		    unsigned int ns,double **path,
		    unsigned int da,double **action,double *time);

/**  
   \brief Saves a set of samples to a file.

   Saves a set of samples (possibly defining a solution path) to a file.
   This function is used to save sets of paths.

   \param fname The file where to store the samples.
   \param smooth TRUE if the set of samples is the result of a smoothing
                 process.
   \param n The number of this path. Used to define a different name
            for a sequence of paths to store.
   \param nvs The dimensionality of each sample.
   \param ns The number of samples defining the path.
   \param path The collection of samples defining the path.
*/
void SaveSamplesN(char *fname,boolean smooth,unsigned int n,unsigned int nvs,
		  unsigned int ns,double **path);
/**  
   \brief Reads a set of samples from file.
   
   Reads a set of samples from a file created using \ref SaveSamples.

   \param fname Name of the file containing the samples.
   \param nvs Number of entries for each sample.
   \param ns Number of samples (output).
   \param path The set of samples (output).

   \return TRUE if the sample set could be actually read.
*/
boolean LoadSamples(Tfilename *fname,unsigned int *nvs,
		    unsigned int *ns,double ***path);

/**  
   \brief Reads a trajectory from file.
   
   Reads a trajectory \ref SaveTrajectory.

   \param fname Name of the file containing the samples.
   \param nvs Number of entries for each sample.
   \param ns Number of samples (output).
   \param path The set of samples (output).
   \param da Dimension of the action space (output).
   \param action The action applied at each step (output).
   \param time The time each action is executed (output).

   \return TRUE if the sample set could be actually read.
*/
boolean LoadTrajectory(Tfilename *fname, unsigned int *nvs,
		       unsigned int *ns,double ***path,
		       unsigned int *da,
		       double ***action,double **time);

/**  
   \brief Ensures a mininum time between two consecutive trajectory steps.
   
   Ensures a mininum time between two consecutive trajectory steps. This is
   use before visualizing a trajectory since if the time between frames is
   too short there are delays in the visualization and it looks unnatural.

   \param tm The minimum time in between steps.
   \param id The identifiers of the steps that are keep in the
             sparsified trajectory.
   \param ns Number of samples.
   \param path The set of samples.
   \param action The action applied at each step.
   \param time The time each action is executed.

   \return TRUE if the sample set could be actually read.
*/
void SparsifyTrajectory(double tm,unsigned int **id,
			unsigned int *ns,double **path,
			double **action,double *time);
/**  
   \brief Plots a 3D projection of a path.
   
   Plots a 3D projection of a set of samples representing a path. The path
   is represented by a green line.

   \param p The set of parametres.
   \param p3d The 3d plot where to add the plot.
   \param xID First dimension for the projection (in the original system including
              system vars only).
   \param yID Second dimension for the projection (in the original system including
              system vars only).
   \param zID Third dimension for the projection (in the original system including
              system vars only).
   \param ns The number of samples.
   \param path The set of samples.
*/
void PlotSamples(Tparameters *p,Tplot3d *p3d,
		 unsigned int xID,unsigned int yID,unsigned int zID,
		 unsigned int ns,double **path);

/** 
   \brief Plots the force-field on a set of points.
   
   Plots a 3D projection of the force field on a set of points.
   The force filed is represented as a short line on each point
   pointing in the direction of the force field and with length
   proportional to the force-field magnitude.
   
   \param p The set of parametres.
   \param p3d The 3d plot where to add the plot.
   \param xID First dimension for the projection (in the original system including
              system vars only).
   \param yID Second dimension for the projection (in the original system including
              system vars only).
   \param zID Third dimension for the projection (in the original system including
              system vars only).
   \param w The world from where to compute the force field.
   \param ns The number of solution points.
   \param sols The set of solution points.
*/
void PlotForceField(Tparameters *p,Tplot3d *p3d,
		    unsigned int xID,unsigned int yID,unsigned int zID,
		    Tworld *w,
		    unsigned int ns,double **sols);

/**  
   \brief Deletes the space used by a set of samples.

   Release the memory used by a set of samples.

   \param ns The number of samples.
   \param path The set of samples.
*/
void DeleteSamples(unsigned int ns,double **path);

/**  
   \brief Deletes the space used by a set of samples with flags.

   Release the memory used by a set of samples with flags.
   See \ref InitSamplesReplay.

   \param ns The number of samples.
   \param path The set of samples.
   \param newChart TRUE if a chart is created at the corresponding step.
                   Can be NULL.
   \param time Time lapse from the previous step.
               Can be NULL.
   \param cost Cost of the transition.
               Can be NULL.
*/
void DeleteSamplesReplay(unsigned int ns,double **path,
			 boolean *newChart,double *time,double *cost);

/**  
   \brief Deletes the space used by a trajectory.

   Release the memory used by a trajectory.

   \param ns The number of samples.
   \param path The set of samples.
   \param action The action applied at each step.
   \param time The time each action is executed.
*/
void DeleteTrajectory(unsigned int ns,double **path,
		      double **action,double *time);

#endif
