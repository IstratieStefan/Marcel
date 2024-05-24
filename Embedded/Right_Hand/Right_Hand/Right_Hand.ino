#include <Servo.h>

Servo inner_shoulder;
Servo outer_shoulder;
Servo under_shoulder;
Servo elbow;

#define INNER_SHOULDER 11
#define OUTER_SHOULDER 10
#define UNDER_SHOULDER 9
#define ELBOW 6

char serial_input = 0;
const int smoothingDelay = 12; // Delay between steps in milliseconds
const int stepSize = 3; // Step size for each increment/decrement

void return_position() {
  smoothMove(inner_shoulder, inner_shoulder.read(), 0);
  smoothMove(outer_shoulder, outer_shoulder.read(), 20);
  smoothMove(under_shoulder, under_shoulder.read(), 90);
  smoothMove(elbow, elbow.read(), 0);
}

void setup() {
  inner_shoulder.attach(INNER_SHOULDER);
  outer_shoulder.attach(OUTER_SHOULDER);
  under_shoulder.attach(UNDER_SHOULDER);
  elbow.attach(ELBOW);
  return_position();
  Serial.begin(9600);
}

void salute() {
  smoothMove(outer_shoulder, outer_shoulder.read(), 110);
  smoothMove(under_shoulder, under_shoulder.read(), 180);
  delay(50);
  for (int i = 0; i < 3 * 2; i++) {
    if (i % 2 == 0)
      smoothMove(elbow, elbow.read(), 80);
    else
      smoothMove(elbow, elbow.read(), 0);
    delay(300);
  }
  delay(300);
  return_position();
}

void hand_shake() {
  smoothMove(inner_shoulder, inner_shoulder.read(), 50);
  smoothMove(elbow, elbow.read(), 40);
  delay(3000);
  return_position();
}

void loop() {
  serial_input = Serial.read();
  if (serial_input == '1') {
    hand_shake();
  } else if (serial_input == '2') {
    salute();
  } else if (serial_input == '3') {
    return_position();
  }
}

void smoothMove(Servo &servo, int startAngle, int endAngle) {
  if (startAngle < endAngle) {
    for (int pos = startAngle; pos <= endAngle; pos += stepSize) {
      servo.write(pos);
      delay(smoothingDelay);
    }
  } else {
    for (int pos = startAngle; pos >= endAngle; pos -= stepSize) {
      servo.write(pos);
      delay(smoothingDelay);
    }
  }
}