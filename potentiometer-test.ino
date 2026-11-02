#include <AccelStepper.h>
AccelStepper step(1, 2, 5);
const int pot = A0;
const int deadband = 3;
int val = 0;
int prev = 0;
int newval = 0;
void setup() {
  step.setCurrentPosition(0);
  step.setMaxSpeed(1000);
  step.setAcceleration(100);
  step.setSpeed(500);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);
  Serial.println(val);
  if((val > prev + deadband) || (val < prev - deadband)){
    newval = map(val, 0, 1023, 0, 200);
    // Serial.println(newval);
    step.runToNewPosition(newval);
    prev = val;
  }
}
