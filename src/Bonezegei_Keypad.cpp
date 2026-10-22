/*
    Simple Keypad Library
    Author: Jofel Batutay (Bonezegei)
    Date: October 22, 2026 
*/
#include "Bonezegei_Keypad.h"

Bonezegei_Keypad::Bonezegei_Keypad(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3,
                                   uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3)
    : _lastKey('\0'), _lastDebounceTime(0), _debounceDelay(50) {
    _rowPins[0] = r0; _rowPins[1] = r1; _rowPins[2] = r2; _rowPins[3] = r3;
    _colPins[0] = c0; _colPins[1] = c1; _colPins[2] = c2; _colPins[3] = c3;

    char defaultMap[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };
    setKeyMap(defaultMap);
}

Bonezegei_Keypad::Bonezegei_Keypad(const uint8_t rowPins[4], const uint8_t colPins[4])
    : _lastKey('\0'), _lastDebounceTime(0), _debounceDelay(50) {
    for (int i = 0; i < 4; i++) {
        _rowPins[i] = rowPins[i];
        _colPins[i] = colPins[i];
    }

    char defaultMap[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };
    setKeyMap(defaultMap);
}

void Bonezegei_Keypad::begin() {
    for (int i = 0; i < 4; i++) {
        pinMode(_rowPins[i], INPUT_PULLUP);
        pinMode(_colPins[i], INPUT_PULLUP);
    }
}

void Bonezegei_Keypad::setKeyMap(const char userMap[4][4]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            _keymap[r][c] = userMap[r][c];
        }
    }
}

void Bonezegei_Keypad::setDebounceTime(unsigned long ms) {
    _debounceDelay = ms;
}

char Bonezegei_Keypad::getKey() {
    char currentPressedKey = '\0';

    // Scan matrix rows and columns
    for (int r = 0; r < 4; r++) {
        pinMode(_rowPins[r], OUTPUT);
        digitalWrite(_rowPins[r], LOW);

        for (int c = 0; c < 4; c++) {
            if (digitalRead(_colPins[c]) == LOW) {
                currentPressedKey = _keymap[r][c];
                break;
            }
        }

        pinMode(_rowPins[r], INPUT_PULLUP);

        if (currentPressedKey != '\0') {
            break;
        }
    }

    // Debounce and edge-trigger standard single press
    if (currentPressedKey != _lastKey) {
        if ((millis() - _lastDebounceTime) > _debounceDelay) {
            _lastDebounceTime = millis();
            _lastKey = currentPressedKey;
            return _lastKey;
        }
    }

    return '\0';
}

bool Bonezegei_Keypad::isPressed() {
    return (getKey() != '\0');
}