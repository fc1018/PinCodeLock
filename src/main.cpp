#include <Arduino.h>
#include <Servo.h>

Servo lock;             // Locking mechanism
const int button = A0;  // Analog read of voltage at end of resistor ladder

int passcode = 0;
int attempt = 0;

int readButtons(int& passcode);
bool isPasscodeRight();

void setup() {
  lock.attach(3);
  Serial.begin(9600);

  lock.write(0);  // Lock deactivated

  readButtons(passcode);

  lock.write(90);  // Lock activated
}

void loop() {
  do {
    readButtons(attempt);
    isPasscodeRight();
  } while (isPasscodeRight() == false);

  lock.write(0);  // lock deactivated

  delay(10000);

  lock.write(90);  // lock reactivated
}

int readButtons(int& passcode) {  // Function to take button inputs and
                                  // store in input array
  int buttonsPressed = 0;
  while (buttonsPressed < 4) {
    int buttonVal = analogRead(A0);  // Read voltage at end of resistor ladder

    if (buttonVal < 50) {  // Ignore noise
      continue;
    } else if (buttonVal <= 180) {  // button 0 pressed
      // passcode += 0 * round(pow(10, 3 - buttonsPressed));
    } else if (buttonVal <= 220) {  // button 1 pressed
      passcode += 1 * round(pow(10, 3 - buttonsPressed));

    } else if (buttonVal <= 290) {  // button 2 pressed
      passcode += 2 * round(pow(10, 3 - buttonsPressed));
    } else if (buttonVal <= 400) {  // button 3 pressed
      passcode += 3 * round(pow(10, 3 - buttonsPressed));
    } else if (buttonVal <= 750) {  // button 4 pressed
      passcode += 4 * round(pow(10, 3 - buttonsPressed));
    } else if (buttonVal <= 1024) {  // button 5 pressed
      passcode += 5 * round(pow(10, 3 - buttonsPressed));
    }
    buttonsPressed++;
    delay(200);  // delay to avoid multiple inputs
  }

  Serial.print("Input was: ");

  Serial.print(passcode);
  Serial.println();

  return 0;
}

bool isPasscodeRight() { return passcode == attempt; }