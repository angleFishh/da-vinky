//AccelStepper library
#include <AccelStepper.h> 

//number of potentiometers and array for the pins
int potCount = 6; 
int potPins[] = { A0, A1, A2, A3, A4, A5}; 

//array for stepper motor pins and math for number of stepper motors
AccelStepper steppers[] = {
  { AccelStepper::DRIVER, 13, 12 }, { AccelStepper::DRIVER, 2, 5 }, 
  { AccelStepper::DRIVER, 3, 6 }, { AccelStepper::DRIVER, 4, 7 }, 
  { AccelStepper::DRIVER, 8, 10 },{ AccelStepper::DRIVER, 9, 11 }
};
const uint8_t stepperCount = sizeof(steppers) / sizeof(steppers[0]);

//setup values for stepper motors
int maxSpeed = 2000;
int accel = 500;
int speed = 1000;
int currentPosition = 0;

//array for potentiometer mapping stuff
int val[] = { 0, 0, 0, 0, 0  };
int prev[] = { 0, 0, 0, 0, 0 };
int newVal[] = { 0, 0, 0, 0, 0 };

//stepper rotation range of 1 full rotation in either direction, deadband to prevent stepper movement when potentiometer is not moving
int min = -200; 
int max = 200;
int deadband = 3;

void setup() {
  //setup for all potentiometers
  for (int i = 0; i < potCount; i++) {
    pinMode(potPins[i], INPUT);
  }
  //setup for all stepper motors
  for (int i = 0; i < stepperCount; i++) {
    steppers[i].setMaxSpeed(maxSpeed);
    steppers[i].setCurrentPosition(currentPosition);
    steppers[i].setAcceleration(accel);
    steppers[i].setSpeed(speed);
  }
}


void loop() {
  /*applies to all stepper motors: 
   read paired potentiometer, if the value read from the potentiometer is different than the previous value
   and greater than the deadband value, map the potentiometer movement to the stepper range, and move stepper motor 
   then store the current value as the previous value */
  for (int i = 0; i < stepperCount; i++) {
    val[i] = analogRead(potPins[i]);
    if((val[i] > prev[i] + deadband) || (val[i] < prev[i] - deadband)){
      newVal[i] = map(val[i], 0, 1023, min, max);
      steppers[i].runToNewPosition(newVal[i]);
        prev[i] = val[i];
    }
  }
}

