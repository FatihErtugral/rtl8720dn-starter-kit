/**
 * @file Led.cpp
 * @brief Single LED control implementation
 */

#include "Led.h"

Led::Led(uint8_t pin, bool activeLow)
    : _pin(pin)
    , _activeLow(activeLow)
    , _state(false)
{
}

void Led::begin() {
    pinMode(_pin, OUTPUT);
    off();
}

void Led::on() {
    _state = true;
    writeState();
}

void Led::off() {
    _state = false;
    writeState();
}

void Led::toggle() {
    _state = !_state;
    writeState();
}

void Led::set(bool state) {
    _state = state;
    writeState();
}

bool Led::isOn() const {
    return _state;
}

void Led::blink(unsigned long duration) {
    on();
    delay(duration);
    off();
}

uint8_t Led::getPin() const {
    return _pin;
}

void Led::writeState() {
    // Active LOW: on=LOW, off=HIGH
    // Active HIGH: on=HIGH, off=LOW
    if (_activeLow) {
        digitalWrite(_pin, _state ? LOW : HIGH);
    } else {
        digitalWrite(_pin, _state ? HIGH : LOW);
    }
}
