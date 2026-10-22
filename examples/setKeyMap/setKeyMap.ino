#include <Bonezegei_Keypad.h>

// Define pin numbers connected to Row and Column header pins
const uint8_t ROW_PINS[4] = {9, 8, 7, 6};
const uint8_t COL_PINS[4] = {5, 4, 3, 2};

// Initialize keypad object
Bonezegei_Keypad keypad(ROW_PINS, COL_PINS);

// Custom 4x4 layout mapping (e.g., Directional / Menu Navigation map)
const char myCustomMap[4][4] = {
    {'U', '1', '2', '3'},   // 'U' = Up
    {'D', '4', '5', '6'},   // 'D' = Down
    {'L', '7', '8', '9'},   // 'L' = Left
    {'R', 'E', '0', 'X'}    // 'R' = Right, 'E' = Enter, 'X' = Cancel
};

void setup() {
    Serial.begin(9600);

    // Load custom keymap array into library
    keypad.setKeyMap(myCustomMap);

    keypad.begin();
    Serial.println("Custom Keymap Keypad Initialized!");
}

void loop() {
    char key = keypad.getKey();

    if (key != '\0') {
        Serial.print("Action Triggered: ");
        Serial.println(key);

        // Perform action based on custom mapped key
        switch (key) {
            case 'U':
                Serial.println("-> Menu Navigate UP");
                break;
            case 'D':
                Serial.println("-> Menu Navigate DOWN");
                break;
            case 'E':
                Serial.println("-> OK / Select");
                break;
            case 'X':
                Serial.println("-> Cancel / Back");
                break;
            default:
                break;
        }
    }
}