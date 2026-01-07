/**
 * @file RgbLed.cpp
 * @brief RGB LED control implementation
 */

#include "RgbLed.h"

RgbLed::RgbLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool activeLow)
    : _red(redPin, activeLow)
    , _green(greenPin, activeLow)
    , _blue(bluePin, activeLow)
    , _currentColor(Color::None)
{
}

void RgbLed::begin() {
    _red.begin();
    _green.begin();
    _blue.begin();
}

void RgbLed::setColor(Color color) {
    _currentColor = color;
    uint8_t colorBits = static_cast<uint8_t>(color);
    _red.set(colorBits & 0b100);
    _green.set(colorBits & 0b010);
    _blue.set(colorBits & 0b001);
}

void RgbLed::setColor(bool red, bool green, bool blue) {
    _red.set(red);
    _green.set(green);
    _blue.set(blue);

    uint8_t colorBits = (red ? 0b100 : 0) | (green ? 0b010 : 0) | (blue ? 0b001 : 0);
    _currentColor = static_cast<Color>(colorBits);
}

void RgbLed::off() {
    setColor(Color::None);
}

void RgbLed::flash(Color color, unsigned long duration) {
    setColor(color);
    delay(duration);
    off();
}

void RgbLed::cyclePrimary(unsigned long duration) {
    flash(Color::Red, duration);
    flash(Color::Green, duration);
    flash(Color::Blue, duration);
}

void RgbLed::cycleAll(unsigned long duration) {
    flash(Color::Red, duration);
    flash(Color::Green, duration);
    flash(Color::Blue, duration);
    flash(Color::Yellow, duration);
    flash(Color::Cyan, duration);
    flash(Color::Magenta, duration);
    flash(Color::White, duration);
}

Color RgbLed::getColor() const {
    return _currentColor;
}

Led& RgbLed::red() { return _red; }
Led& RgbLed::green() { return _green; }
Led& RgbLed::blue() { return _blue; }
