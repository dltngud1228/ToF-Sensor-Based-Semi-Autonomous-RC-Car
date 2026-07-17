#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);

int leftFrontA = 2;
int leftFrontB = 3;
int leftRearA = 4;
int leftRearB = 5;
int rightFrontA = 6;
int rightFrontB = 7;
int rightRearA = 8;
int rightRearB = 9;

void setup() {
  pinMode(leftFrontA, OUTPUT);
  pinMode(leftFrontB, OUTPUT);
  pinMode(leftRearA, OUTPUT);
  pinMode(leftRearB, OUTPUT);
  pinMode(rightFrontA, OUTPUT);
  pinMode(rightFrontB, OUTPUT);
  pinMode(rightRearA, OUTPUT);
  pinMode(rightRearB, OUTPUT);

  stopCar();
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();

    if (command == 'F') {
      moveForward();
    } else if (command == 'B') {
      moveBackward();
    } else if (command == 'L') {
      turnLeft();
    } else if (command == 'R') {
      turnRight();
    } else if (command == 'S') {
      stopCar();
    }
  }
}

void moveForward() {
  digitalWrite(leftFrontA, HIGH);
  digitalWrite(leftFrontB, LOW);
  digitalWrite(leftRearA, HIGH);
  digitalWrite(leftRearB, LOW);
  digitalWrite(rightFrontA, HIGH);
  digitalWrite(rightFrontB, LOW);
  digitalWrite(rightRearA, HIGH);
  digitalWrite(rightRearB, LOW);
}

void moveBackward() {
  digitalWrite(leftFrontA, LOW);
  digitalWrite(leftFrontB, HIGH);
  digitalWrite(leftRearA, LOW);
  digitalWrite(leftRearB, HIGH);
  digitalWrite(rightFrontA, LOW);
  digitalWrite(rightFrontB, HIGH);
  digitalWrite(rightRearA, LOW);
  digitalWrite(rightRearB, HIGH);
}

void turnLeft() {
  digitalWrite(leftFrontA, LOW);
  digitalWrite(leftFrontB, HIGH);
  digitalWrite(leftRearA, LOW);
  digitalWrite(leftRearB, HIGH);
  digitalWrite(rightFrontA, HIGH);
  digitalWrite(rightFrontB, LOW);
  digitalWrite(rightRearA, HIGH);
  digitalWrite(rightRearB, LOW);
}

void turnRight() {
  digitalWrite(leftFrontA, HIGH);
  digitalWrite(leftFrontB, LOW);
  digitalWrite(leftRearA, HIGH);
  digitalWrite(leftRearB, LOW);
  digitalWrite(rightFrontA, LOW);
  digitalWrite(rightFrontB, HIGH);
  digitalWrite(rightRearA, LOW);
  digitalWrite(rightRearB, HIGH);
}

void stopCar() {
  digitalWrite(leftFrontA, LOW);
  digitalWrite(leftFrontB, LOW);
  digitalWrite(leftRearA, LOW);
  digitalWrite(leftRearB, LOW);
  digitalWrite(rightFrontA, LOW);
  digitalWrite(rightFrontB, LOW);
  digitalWrite(rightRearA, LOW);
  digitalWrite(rightRearB, LOW);
}
