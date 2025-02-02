// Arduino RBD TimerMicros Library v1.4.0 - Manage many timed events.
// https://github.com/tuna-f1sh/RBD_TimerMicros
// Copyright (c) 2015 Alex Taujenis - MIT License

#ifndef RBD_TIMER_MICROS_H
#define RBD_TIMER_MICROS_H

#include "Arduino.h"

namespace RBD {
  class TimerMicros {
    public:
      TimerMicros();                              // constructor with zero timeout, starts in "expired" state by default
      TimerMicros(unsigned long value);           // overloaded constructor: provide a setTimeout in microseconds, starts in "expired" state by default
      void setTimeout(unsigned long value); // set/change how long the timer will run until it expires in microseconds
      void setHertz(int value);             // set/change how many times onRestart will return true in one second
      void restart();                       // reset and start the timer
      void stop();                          // stop the timer
      void expire();                        // expire the timer without changing the timeout
      bool isActive();                      // check if time is left
      bool isExpired();                     // returns true if time has run out
      bool isStopped();                     // returns true if the timer is stopped
      bool onRestart();                     // returns true if the timer is expired and restarts the timer automatically
      bool onActive();                      // returns true once the timer is active, then waits for it to expire and go active again
      bool onExpired();                     // returns true once the timer is expired, then waits for it to go active and expire again
      unsigned long getTimeout();           // returns the value of setTimeout, which is how long the timer will run until it expires in microseconds
      int getHertz();                       // returns the value of setHertz, which is how many times onRestart will return true in one second
      unsigned long getValue();             // how many microseconds that have passed since the start of the timer
      unsigned long getInverseValue();      // how many microseconds the timer has until finished
      int getPercentValue();                // how much time has passed as a percentage of the interval
      int getInversePercentValue();         // how much time is left as a percentage of the interval
    private:
      unsigned long _timeout  = 0;          // how long this timer should run for
      unsigned long _waypoint = 0;          // the point in time the timer was started or reset
      int _hertz              = 0;          // the value given to setHertz
      bool _has_been_active   = false;      // helps fire the onActive event only once
      bool _has_been_expired  = false;      // helps fire the onExpired event only once
      void _updateState();                  // maintains timer current state, helps eliminate rollover issues
      enum {ACTIVE, EXPIRED, STOPPED} _state = EXPIRED;  // timer internal states, constructed in "expired" state by default
  };
}
#endif
