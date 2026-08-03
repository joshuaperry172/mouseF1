//Original code done by Max Spivey, Randolph-Macon College, last edited 4/13/21
//Adapted from instructable: https://www.instructables.com/Rat-Cars/
//Archived here, unmodified, as our reference baseline
//See GitHub for known bugs and fixes in main.ino

#include <Wire.h>
#include <Adafruit_MotorShield.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

//Pin to keep track of which switch the driver activated
int activePin = 0;
//Constants for normal speed and no speed, use NORMAL_SPEED to change the speed at which the vehicle moves out of 250
int NORMAL_SPEED = 150;
int NO_SPEED = 0;

void setup() {
  //Set the pins for input mode and to use resistors. This causes the pins to automatically be high.
  //Therefore opposite behavior should be expected with the pins.
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  //This initializes the Adafruit Motor Shield
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Set the speed to start, from 0 (off) to 255 (max speed)
  // This turns on the motors
  motor1->setSpeed(NORMAL_SPEED);
  motor2->setSpeed(NORMAL_SPEED);
  motor3->setSpeed(NORMAL_SPEED);
  motor4->setSpeed(NORMAL_SPEED);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
}

void loop() {
  //Check the pins to see if they are active. 
  //We check to see if they are LOW due to INPUT_PULLUP having the pins automatically HIGH.
  if (digitalRead(1) == LOW)
  {
    activePin = 1;
  }
  else if (digitalRead(2) == LOW)
  {
    activePin = 2;
  }
  else if ( digitalRead(3) == LOW)
  {
    activePin = 3;
  }
  else
  {
    activePin = 0;
  }
  /* 
  Depending on what the activePin is, activate the case.
  case 0: Stop the car, no pins are active
  case 1: Pin 1 is active, turn right
  case 2: Pin 2 is active, move forward
  case 3: Pin 3 is active, turn left
  If two pins are activated then the last one to be activated will be the active pin.
  */
  switch (activePin) {
    case 0:
      motor1->run(RELEASE);
      motor2->run(RELEASE);
      motor3->run(RELEASE);
      motor4->run(RELEASE);
      break;
    case 1:
      motor1->run(BACKWARD);
      motor2->run(FORWARD);
      motor3->run(BACKWARD);
      motor4->run(FORWARD);
      break;
    case 2:
      motor1->run(FORWARD);
      motor2->run(FORWARD);
      motor3->run(FORWARD);
      motor4->run(FORWARD);
      break;
    case 3:
      motor1->run(FORWARD);
      motor2->run(BACKWARD);
      motor3->run(FORWARD);
      motor4->run(BACKWARD);
      break;
  }
 }
