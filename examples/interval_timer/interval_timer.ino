// Arduino RBD Timer Library v1.4.0 Example - A three second interval timer that prints to serial.
// https://github.com/tuna-f1sh/RBD_TimerMicros
// Copyright (c) 2015 Alex Taujenis - MIT License

#include <RBD_TimerMicros.h> // https://github.com/tuna-f1sh/RBD_TimerMicros

RBD::Timer timer;

void setup() {
  Serial.begin(115200);
  timer.setTimeout(3000);
  timer.restart();
}

void loop() {
  if(timer.onRestart()) {
    Serial.println("Three seconds passed");
  }
}