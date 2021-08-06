#include <Arduino.h>
#include <Servo.h>

Servo lock;             // Locking mechanism
const int button = A0;  // Analog read of voltage at end of resistor ladder
int passcode[4];
int attempt[4];
int readButtons(int buttonsArr[4]);

void setup() {
  lock.attach(3);
  Serial.begin(9600);

  readButtons(passcode);
}

void loop() {}

int readButtons(int buttonsArr[4]) {  // Function to take button inputs and
                                      // store in input array
                                      // array
  int buttonsPressed = 0;

  while (buttonsPressed < 4) {
    int buttonVal = analogRead(A0);  // Read voltage at end of resistor ladder

    if (buttonVal < 50) {  // Ignore noise
      continue;
    } else if (buttonVal <= 180) {  // button 0 pressed
      buttonsArr[buttonsPressed] = 0;
    } else if (buttonVal <= 220) {  // button 1 pressed
      buttonsArr[buttonsPressed] = 1;
    } else if (buttonVal <= 290) {  // button 2 pressed
      buttonsArr[buttonsPressed] = 2;
    } else if (buttonVal <= 400) {  // button 3 pressed
      buttonsArr[buttonsPressed] = 3;
    } else if (buttonVal <= 750) {  // button 4 pressed
      buttonsArr[buttonsPressed] = 4;
    } else if (buttonVal <= 1024) {  // button 5 pressed
      buttonsArr[buttonsPressed] = 5;
    }
    buttonsPressed++;
    delay(200);  // delay to avoid multiple inputs
    Serial.print(buttonsPressed);
    Serial.println();
  }

  Serial.print("Input was: ");

  for (int i = 0; i < 4; i++) {
    Serial.print(buttonsArr[i]);
  }

  Serial.println();

  return 0;
}