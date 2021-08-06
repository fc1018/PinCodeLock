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

    } else if (buttonVal >= 50 && buttonVal <= 180) {  // button 0 pressed
      buttonsArr[buttonsPressed] = 0;  // Store 0 input in buttons array
      buttonsPressed++;                // Increment button counter by 1
      delay(200);                      // Delay to avoid multiple inputs
      Serial.println(buttonsPressed);
    } else if (buttonVal > 180 && buttonVal <= 220) {  // button 1 pressed
      buttonsArr[buttonsPressed] = 1;  // Store 1 input in buttons array
      buttonsPressed++;
      delay(200);
      Serial.println(buttonsPressed);
    } else if (buttonVal > 220 && buttonVal <= 290) {  // button 2 pressed
      buttonsArr[buttonsPressed] = 2;  // Store 2 input in buttons array
      buttonsPressed++;
      delay(200);
      Serial.println(buttonsPressed);
    } else if (buttonVal > 290 && buttonVal <= 400) {  // button 3 pressed
      buttonsArr[buttonsPressed] = 3;  // Store 3 input in buttons array
      buttonsPressed++;
      delay(200);
      Serial.println(buttonsPressed);
    } else if (buttonVal > 400 && buttonVal <= 750) {  // button 4 pressed
      buttonsArr[buttonsPressed] = 4;  // Store 4 input in buttons array
      buttonsPressed++;
      delay(200);
      Serial.println(buttonsPressed);
    } else if (buttonVal > 750 && buttonVal <= 1024) {  // button 5 pressed
      buttonsArr[buttonsPressed] = 5;  // Store 5 input in buttons array
      buttonsPressed++;
      delay(200);
      Serial.println(buttonsPressed);
    }
  }

  Serial.print("Input was: ");

  for (int i = 0; i < 4; i++) {  // Prints stored code in terminal
    Serial.print(buttonsArr[i]);
  }

  Serial.println();

  return 0;
}