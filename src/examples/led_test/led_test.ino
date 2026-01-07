/**
 * @file led_test.ino
 * @brief RGB LED Test Example
 *
 * RTL8720DN tabanlı kartlarda RGB LED kontrolü örneği.
 * src/led/ modülünü kullanarak tüm renkleri döngüler.
 *
 * Desteklenen kartlar:
 * - NICEMCU_8720_v1 (-DBOARD_NICEMCU)
 * - BW16-Kit v1.2 (-DBOARD_BW16KIT)
 *
 * Build:
 *   arduino-cli compile --fqbn realtek:AmebaD:... \
 *     --build-property "build.extra_flags=-DBOARD_NICEMCU" .
 */

#include <BoardConfig.h>
#include <HardwareAbstraction.h>
#include <RgbLed.h>

// RGB LED instance (BoardConfig'den pin tanımları)
RgbLed rgbLed(PIN_LED_RED, PIN_LED_GREEN, PIN_LED_BLUE, LED_ACTIVE_LOW);

// Timing
const unsigned long BLINK_DELAY = 2000;  // 2 saniye - takip etmek için yavaş

void setup() {
    // Serial başlat
    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);
    delay(1000);

    // Board bilgisi
    DEBUG_SERIAL.println();
    Hardware.printInfo();
    DEBUG_SERIAL.println();

    // LED başlat
    rgbLed.begin();

    DEBUG_SERIAL.println("RGB LED initialized");
    DEBUG_SERIAL.println("Starting color cycle...");
    DEBUG_SERIAL.println();
}

void loop() {
    DEBUG_SERIAL.println("RED");
    rgbLed.flash(Color::Red, BLINK_DELAY);

    DEBUG_SERIAL.println("GREEN");
    rgbLed.flash(Color::Green, BLINK_DELAY);

    DEBUG_SERIAL.println("BLUE");
    rgbLed.flash(Color::Blue, BLINK_DELAY);

    DEBUG_SERIAL.println("YELLOW (R+G)");
    rgbLed.flash(Color::Yellow, BLINK_DELAY);

    DEBUG_SERIAL.println("CYAN (G+B)");
    rgbLed.flash(Color::Cyan, BLINK_DELAY);

    DEBUG_SERIAL.println("MAGENTA (R+B)");
    rgbLed.flash(Color::Magenta, BLINK_DELAY);

    DEBUG_SERIAL.println("WHITE (R+G+B)");
    rgbLed.flash(Color::White, BLINK_DELAY);

    DEBUG_SERIAL.println("--- Cycle complete ---");
    DEBUG_SERIAL.println();

    delay(1000);
}
