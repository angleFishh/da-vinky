#include <AccelStepper.h>

AccelStepper stepper(1, 2, 5);

void setup(){
  Serial.begin(9600);
  stepper.setMaxSpeed(100);
  stepper.setSpeed(100);
  stepper.setCurrentPosition(0);
}

void loop(){
  if (Serial.available() > 0){
    int inByte = Serial.read();
    switch (inByte){
      case '+':
      stepper.moveTo(200);
      break;
      case '-':
      stepper.moveTo(-200);
      break;
    }
  }
  stepper.run();
}