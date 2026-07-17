#include <Servo.h>

Servo scanServo;
int servoPin = 12;

void setup() {
  scanServo.attach(servoPin);
  scanServo.write(90);
  delay(500);
}

void loop() {
  scanServo.write(30);
  delay(1000);

  scanServo.write(90);
  delay(1000);

  scanServo.write(150);
  delay(1000);

  scanServo.write(90);
  delay(1000);
}
