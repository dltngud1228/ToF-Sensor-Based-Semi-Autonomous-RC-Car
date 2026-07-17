#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000);

  sensor.setTimeout(500);

  if (!sensor.init()) {
    Serial.println("VL53L0X init failed");
    while (1) {
    }
  }

  sensor.startContinuous(100);
}

void loop() {
  int distance = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.println("TIMEOUT");
  } else {
    Serial.print(distance);
    Serial.println(" mm");
  }

  delay(100);
}
