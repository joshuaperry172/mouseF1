#include <AFMotor.h>
#include <Stepper.h>

const int SWITCH_RIGHT    = A0;
const int SWITCH_FORWARD  = A1;
const int SWITCH_LEFT     = A2;
const int SENSOR_PIN      = A3;
const int IN1             = A4;
const int IN2             = A5;
const int IN3             = 2;
const int IN4             = 12;

const int STEPS_PER_REV   = 2048;   // number of steps per full revolution for auger (can be modified in testing)
const int ROTATION_SPEED  = 12;     // highest auger rotation speed possible while remaining confidently reliable (higher = not enough torque)
const int NORMAL_SPEED    = 150;    // speed of rotation of wheels when activated

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Stepper myStepper(STEPS_PER_REV, IN1, IN3, IN2, IN4);

int lastSensorValue = 0;
int stepsRemaining = 0;

void setup() {
  pinMode(SWITCH_RIGHT, INPUT_PULLUP);
	pinMode(SWITCH_FORWARD, INPUT_PULLUP);
	pinMode(SWITCH_LEFT, INPUT_PULLUP);
  
  motor1.setSpeed(NORMAL_SPEED);
  motor2.setSpeed(NORMAL_SPEED);
  motor3.setSpeed(NORMAL_SPEED);
  motor4.setSpeed(NORMAL_SPEED);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  myStepper.setSpeed(ROTATION_SPEED);
}

void loop() {

	bool right   = (digitalRead(SWITCH_RIGHT)   == LOW);
	bool forward = (digitalRead(SWITCH_FORWARD) == LOW);
	bool left    = (digitalRead(SWITCH_LEFT)    == LOW);
	
  int pressedCount = right + forward + left;
  int activePin    = 0;

	if      (pressedCount > 1)  { activePin = 0; }  // ambiguous input — stop 
	else if (right)             { activePin = 1; } 
	else if (forward)           { activePin = 2; } 
	else if (left)              { activePin = 3; } 
	else                        { activePin = 0; }
  /* 
  Depending on what the activePin is, activate the case.
  case 0: Stop the car, no pins are active
  case 1: SWITCH_RIGHT is active, turn right
  case 2: SWITCH_FORWARD is active, move forward
  case 3: SWITCH_LEFT is active, turn left
  */
  switch (activePin) {
    case 0:
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      break;
    case 1:
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(BACKWARD);
      break;
    case 2:
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      break;
    case 3:
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(FORWARD);
      break;
  }
  
  int currentSensorValue = analogRead(SENSOR_PIN); // input from A3 (returns 0-1023)
  if (currentSensorValue > 500 && lastSensorValue <= 500) stepsRemaining = STEPS_PER_REV; //triggers action past a certain threshold (threshold can be modified)

  lastSensorValue = currentSensorValue;

  // allows the stepper to operate on a nonblocking basis
  if (stepsRemaining > 0) {
    myStepper.step(1);
    stepsRemaining--;
  }
 }
