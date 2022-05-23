#include <Arduino.h>
#include <Servo.h>

Servo lock;             // Locking mechanism
const int button = A0;  // Analog read of voltage at end of transistor ladder
int passcode[4];
int attempt[4];

int readbuttons(int buttonsArr[4]);
bool isPasscodeRight();

void setup() {
  lock.attach(3);
  Serial.begin(9600);

  lock.write(0)
      :  // Lock deactivated

        readbuttons(passcode);

  lock.write(90) :  // Lock activated
}

void loop() {
  do {
    readbuttons(attempt);
    isPasscodeRight();
  } while (isPasscodeRight() == false);

  lock.write(0);  // lock deactivated

  delay(10000);

  lock.write(90);  // lock reactivated
}

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

bool isPasscodeRight() {
  if (passcode[0] != attempt[0]) {
    return false;
  } else if (passcode[1] != attempt[1]) {
    return false;
  } else if (passcode[2] != attempt[2]) {
    return false;
  } else if (passcode[3] != attempt[3]) {
    return false;
  } else {
    return true;
  }
}
