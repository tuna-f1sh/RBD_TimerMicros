// Arduino RBD TimerMicros Library v1.0.0 - Manage many timed events.
// https://github.com/tuna-f1sh/RBD_TimerMicros
// Copyright (c) 2015 Alex Taujenis - MIT License

#include <Arduino.h>
#include <RBD_TimerMicros.h> // https://github.com/tuna-f1sh/RBD_TimerMicros

namespace RBD {
  TimerMicros::TimerMicros() {}

  TimerMicros::TimerMicros(unsigned long value) {
    setTimeout(value);
  }

  void TimerMicros::setTimeout(unsigned long value) {
    _timeout = (value > 0) ? value : 1;
  }

  unsigned long TimerMicros::getTimeout() {
    return _timeout;
  }

  void TimerMicros::setHertz(int value) {
    _hertz   = constrain(value, 1, 1e6);
    _timeout = (unsigned long)(1e6 / _hertz);
  }

  int TimerMicros::getHertz() {
    return _hertz;
  }

  void TimerMicros::restart() {
    _waypoint         = micros();
    _state            = ACTIVE;
    _has_been_active  = false;
    _has_been_expired = false;
  }

  void TimerMicros::stop() {
    _state = STOPPED;
  }

  void TimerMicros::expire() {
    _state = EXPIRED;
  }

  bool TimerMicros::isActive() {
    _updateState();
    return _state == ACTIVE;
  }

  bool TimerMicros::isExpired() {
    _updateState();
    return _state == EXPIRED;
  }

  bool TimerMicros::isStopped() {
    return _state == STOPPED;
  }

  bool TimerMicros::onRestart() {
    if(isExpired()) {
      restart();
      return true;
    }
    return false;
  }

  bool TimerMicros::onActive() {
    if(!_has_been_active && isActive()) {
      return _has_been_active = true;
    }
    return false;
  }

  bool TimerMicros::onExpired() {
    if(!_has_been_expired && isExpired()) {
      return _has_been_expired = true;
    }
    return false;
  }

  unsigned long TimerMicros::getValue() {
    return micros() - _waypoint;
  }

  unsigned long TimerMicros::getInverseValue() {
    return _timeout - getValue();
  }

  int TimerMicros::getPercentValue() {
    if(_timeout == 0) {return 0;}
    return getValue() / float(_timeout) * 100;
  }

  int TimerMicros::getInversePercentValue() {
    return 100 - getPercentValue();
  }


  // private

  void TimerMicros::_updateState() {
    if(_state == ACTIVE && getValue() >= _timeout) {
      _state = EXPIRED;
    }
  }
}
