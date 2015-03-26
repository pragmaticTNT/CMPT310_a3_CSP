
#include <signal.h>
#include <sys/time.h>

static int expired;

// ****************************************
//  Signal handler for when timer expires.
// ****************************************

static void expire(int param)
{
  expired = 1;
}


// ********************************************
//  Answer whether a preset timer has expired.
// ********************************************

int time_expired()
{
  return( expired );
}


// ***********************************************************************
//  Set a timer (an alarm) that will expire after ``time_limit'' seconds.
//  The timer counts in virtual time (CPU time) or real time, depending
//  on ``type''.
// ***********************************************************************

void set_limit( TIMER_TYPE type, int time_limit )
{
  struct itimerval value;
  
  
  expired = 0;
  
  
  // Setting it_interval to zero causes timer to be disabled
  // after its next expiration (assuming it_value is non-zero).
  value.it_interval.tv_sec = 0;
  value.it_interval.tv_usec = 0;
  
  // If it_value is non-zero, it indicates the time to the next
  // timer expiration.
  value.it_value.tv_sec = time_limit;
  value.it_value.tv_usec = 0;
  
  // Set the signal handler and start the timer.
  if( type == REAL ) {
    // ITIMER_REAL is a timer that decrements in real time.
    //  A SIGALRM signal is delivered when it expires.
    signal( SIGALRM, expire);
    setitimer( ITIMER_REAL, &value, (struct itimerval *) NULL );
  }
  else
    if( type == VIRTUAL ) {
       // ITIMER_VIRTUAL is a timer that decrements in process
       // virtual time.  It runs only when the process is executing.
       // A SIGVTALRM signal is delivered when it expires.
      signal( SIGVTALRM, expire);
      setitimer( ITIMER_VIRTUAL, &value, (struct itimerval *) NULL );
    }
}

