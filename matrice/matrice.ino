#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

// Create an object of keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  static String codeBuffer = ""; // Buffer to store the accumulated code

  char key = keypad.getKey(); // Read the key

  if (key) {
    // Accumulate the code until 'A' is pressed
    if (key != 'A') {
      codeBuffer += key;
    } else {
      // 'A' is pressed, send the accumulated code via serial
      Serial.println(codeBuffer);

      // Clear the buffer for the next code
      codeBuffer = "";
    }
  }
}
