#include <Bonezegei_Keypad.h>

// Define row and column pins connected to Arduino UNO (Pins 9-2)
const uint8_t ROW_PINS[4] = {9, 8, 7, 6};
const uint8_t COL_PINS[4] = {5, 4, 3, 2};

// Initialize keypad class
Bonezegei_Keypad keypad(ROW_PINS, COL_PINS);

void setup() {
    Serial.begin(9600);
    keypad.begin();
    Serial.println("Bonezegei Keypad 4x4 Ready!");
}

void loop() {
    char key = keypad.getKey();

    if (key != '\0') {
        Serial.print("Pressed Key: ");
        Serial.println(key);
    }
}