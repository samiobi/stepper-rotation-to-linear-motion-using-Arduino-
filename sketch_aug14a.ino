#include <Stepper.h>

// === Stepper motor setup ===
const int stepsPerRevolution = 2000; // Change according to your stepper
const int motorPin1 = 8; // dir +
const int motorPin2 = 9; // pul +

Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2);

// === Buttons ===
const int btnCW = 2;   // Clockwise button
const int btnCCW = 3;  // Counterclockwise button

// === Potentiometer ===
const int potPin = A0;

void setup() {
  pinMode(btnCW, INPUT_PULLUP);  // internal pull-up
  pinMode(btnCCW, INPUT_PULLUP); // internal pull-up

  Serial.begin(9600);
}

void loop() {
  // Read potentiometer (speed control)
  int potValue = analogRead(potPin);
  int rpm = map(potValue, 0, 1023, 50, 200); // adjust min/max RPM
  myStepper.setSpeed(rpm);

  // Read buttons (LOW = pressed)
  bool cwPressed = (digitalRead(btnCW) == LOW);
  bool ccwPressed = (digitalRead(btnCCW) == LOW);

  if (cwPressed && !ccwPressed) {
    myStepper.step(1);  // Step one step clockwise
  }
  else if (ccwPressed && !cwPressed) {
    myStepper.step(-1); // Step one step counterclockwise
  }
  // If no button pressed, do nothing (motor stops)
}
