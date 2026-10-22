/*
    Simple Keypad Library
    Author: Jofel Batutay (Bonezegei)
    Date: October 22, 2026 
*/

#ifndef BONEZEGEI_KEYPAD_H
#define BONEZEGEI_KEYPAD_H

#include <Arduino.h>

class Bonezegei_Keypad {
public:
    // Constructor using explicit pin lists: (R0, R1, R2, R3, C0, C1, C2, C3)
    Bonezegei_Keypad(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3,
                     uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3);

    // Constructor using arrays
    Bonezegei_Keypad(const uint8_t rowPins[4], const uint8_t colPins[4]);

    // Initialize row and column pin modes
    void begin();

    // Returns pressed character once per press (non-blocking, debounced), or '\0' if none
    char getKey();

    // Returns true if any key is currently pressed
    bool isPressed();

    // Custom key mapping override
    void setKeyMap(const char userMap[4][4]);

    // Set debounce delay in milliseconds (default 50ms)
    void setDebounceTime(unsigned long ms);

private:
    uint8_t _rowPins[4];
    uint8_t _colPins[4];
    char _keymap[4][4];

    char _lastKey;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
};

#endif // BONEZEGEI_KEYPAD_H