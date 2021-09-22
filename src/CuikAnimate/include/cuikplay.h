#ifndef CUIKPLAYH
#define CUIKPLAYH

#include "boolean.h"

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
  #include <mach/clock.h>
  #include <mach/mach.h>
#endif

/** \file cuikplay.h

    \brief Definition of the \ref cuikplay.c "cuikplay" control structure.

    Definition of the control structure shared betweeen \ref cuikplay.c "cuikplay"
    and the interface callbacks.
*/

#ifdef __APPLE__ // OS X does not have clock_gettime, use clock_get_time
/** 
   \brief Time in seconds.

   Stores the time in seconds in the given variable (a double variable).
*/
#define GET_TIME(t) {clock_serv_t cclock;mach_timespec_t mts;host_get_clock_service(mach_host_self(),SYSTEM_CLOCK,&cclock);clock_get_time(cclock,&mts);mach_port_deallocate(mach_task_self(), cclock);t=((double)mts.tv_sec+(double)mts.tv_nsec/(double)NSEC_PER_SEC);}
#else
/** 
   \brief Time in seconds.

   Stores the time in seconds in the given variable (a double variable).
*/
#define GET_TIME(t) {struct timespec tp; clock_gettime(CLOCK_REALTIME,&tp); t=((double)tp.tv_sec+(double)tp.tv_nsec/1000000000.0);}
#endif


/** 
   \brief One of the modes of the player.

   The frames are displayed in order and at the required speed.
*/
#define PLAYING 0

/** 
   \brief One of the modes of the player.

   No frames are displayed.
*/
#define PAUSED 1

/** 
   \brief Default time delay.
   
   If the time between frames is not given this value is used.
*/
#define DEFAULT_TIME_DELAY 0.25

/** 
   \brief Definition of the \ref cuikplay.c "cuikplay" control structure.

   \ref cuikplay.c "cuikplay" control structure. This is shared
   between the \ref cuikplay.c "cuikplay"  main application and the
   interface callbacks.
*/
typedef struct {
  boolean end;               /**< TRUE if cuikplay is to be closed. */
  unsigned int mode;         /**< Mode of cuikplay: PLAY, PAUSE, MOVE (to frame).*/
  unsigned int currentFrame; /**< Identifier of the last displayed frame. */
  unsigned int nextFrame;    /**< Identifier of the frame to be displayed next. */
  unsigned int maxFrame;     /**< Identifier of the last possible frame. */
  double nextTime;           /**< Time at which the next frame has to be displayed. */
  double *delay;             /**< Delay between frames. If NULL the default delay
			          of \e defaultDelay is used. */
  double defaultDelay;       /**< Default frame delay. User given or the one 
			          fixed in \ref DEFAULT_TIME_DELAY */
} TCuikPlayControl;

#endif
