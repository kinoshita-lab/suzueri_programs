#pragma once

class Solenoider {
public:
  Solenoider() : outPin(-1), timerCounter(0), timerCounterMax(0) { reset(); }

  virtual ~Solenoider() {}

  void pin(const int pin) {
    outPin = pin;
    pinMode(outPin, OUTPUT);
  }

  void time(const int time) { timerCounterMax = time; }

  void reset() {
    state = State::Reset;
    timerCounter = 0;
  }

  void activate() {
    state = State::Push;
    if (outPin != -1) {
      digitalWrite(outPin, HIGH);
    }
  }

  void tick() {
    if (state != State::Push) {
      return;
    }

    timerCounter++;
    if (timerCounter >= timerCounterMax) {
      if (outPin != -1) {
        digitalWrite(outPin, LOW);
      }

      reset();
    }
  }

protected:
  int outPin;
  int timerCounter;
  int timerCounterMax;

  enum class State {
    Reset,
    Push,
  };
  State state;
};