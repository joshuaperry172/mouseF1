#include <AFMotor.h>

#define SWITCH_RIGHT A0
#define SWITCH_FORWARD A1
#define SWITCH_LEFT A2

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int activePin = 0;
int NORMAL_SPEED = 150;

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
}

void loop() {

	bool right = (digitalRead(SWITCH_RIGHT) == LOW);
	bool forward = (digitalRead(SWITCH_FORWARD) == LOW);
	bool left = (digitalRead(SWITCH_LEFT) == LOW);
	int pressedCount = right + forward + left;

	if (pressedCount > 1) {
	  activePin = 0;  // ambiguous input — stop
	} 
	else if (right) {
	  activePin = 1;
	} 
	else if (forward) {
	  activePin = 2;
	} 
	else if (left) {
	  activePin = 3;
	} 
	else {
	  activePin = 0;
	}
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
      motor3.run(BACKWARD);
      motor4.run(FORWARD);
      break;
    case 2:
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      break;
    case 3:
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(BACKWARD);
      break;
  }
 }
