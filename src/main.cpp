#include <Arduino.h>
#include <Servo.h>

Servo lock;             // Locking mechanism
const int button = A0;  // Analog read of voltage at end of resistor ladder
int buttonVal;

void setup() {
  lock.attach(3);
  Serial.begin(9600);
}

void loop() {
  buttonVal = analogRead(A0);

  if (buttonVal != 0) {
    Serial.println(buttonVal);
    delay(100);
  }
}