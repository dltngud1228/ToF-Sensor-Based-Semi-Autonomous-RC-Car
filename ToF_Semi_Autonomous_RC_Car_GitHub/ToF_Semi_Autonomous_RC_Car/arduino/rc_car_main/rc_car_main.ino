#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>
#include <SoftwareSerial.h>

VL53L0X sensor;
Servo scanServo;
SoftwareSerial bluetooth(10, 11);

int leftFrontA = 2;
int leftFrontB = 3;
int leftRearA = 4;
int leftRearB = 5;
int rightFrontA = 6;
int rightFrontB = 7;
int rightRearA = 8;
int rightRearB = 9;
int servoPin = 12;

int mode = 0;
int semiRunning = 0;

int obstacleDistance = 300;
int centerAngle = 90;
int leftAngle = 150;
int rightAngle = 30;

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

  scanServo.attach(servoPin);
  scanServo.write(centerAngle);
  delay(500);

  Wire.begin();
  Wire.setClock(100000);

  sensor.setTimeout(500);

  if (!sensor.init()) {
    while (1) {
      stopCar();
    }
  }

  sensor.startContinuous(100);
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();
    controlCommand(command);
  }

  if (mode == 1 && semiRunning == 1) {
    semiAutoDrive();
  }
}

void controlCommand(char command) {
  if (command == 'M') {
    stopCar();
    semiRunning = 0;

    if (mode == 0) {
      mode = 1;
    } else {
      mode = 0;
    }

    return;
  }

  if (command == 'S') {
    stopCar();
    semiRunning = 0;
    return;
  }

  if (mode == 0) {
    if (command == 'F') {
      moveForward();
    } else if (command == 'B') {
      moveBackward();
    } else if (command == 'L') {
      turnLeft();
    } else if (command == 'R') {
      turnRight();
    }
  } else {
    if (command == 'F') {
      semiRunning = 1;
    } else if (command == 'B') {
      semiRunning = 0;
      moveBackward();
    } else if (command == 'L') {
      semiRunning = 0;
      turnLeft();
    } else if (command == 'R') {
      semiRunning = 0;
      turnRight();
    }
  }
}

void semiAutoDrive() {
  int frontDistance = readDistance();

  if (frontDistance <= obstacleDistance) {
    avoidObstacle();
  } else {
    moveForward();
  }
}

void avoidObstacle() {
  stopCar();
  delay(300);

  int leftDistance = scanDistance(leftAngle);
  int rightDistance = scanDistance(rightAngle);

  scanServo.write(centerAngle);
  delay(300);

  if (leftDistance <= obstacleDistance && rightDistance <= obstacleDistance) {
    escapeUShape();
  } else if (leftDistance > rightDistance) {
    turnLeft();
    delay(900);
    stopCar();
    delay(200);
    moveForward();
  } else {
    turnRight();
    delay(900);
    stopCar();
    delay(200);
    moveForward();
  }
}

int scanDistance(int angle) {
  scanServo.write(angle);
  delay(500);
  return readDistance();
}

int readDistance() {
  int distance = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    return 8190;
  }

  return distance;
}

void escapeUShape() {
  moveBackward();
  delay(3000);

  turnLeft();
  delay(3000);

  moveForward();
  delay(1500);

  turnRight();
  delay(3000);

  moveForward();
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
