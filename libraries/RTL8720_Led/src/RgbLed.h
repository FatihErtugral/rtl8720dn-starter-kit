/**
 * @file RgbLed.h
 * @brief RGB LED control class
 *
 * Üç ayrı LED'den oluşan RGB LED modülünü kontrol eder.
 * 7 farklı renk kombinasyonu destekler.
 */

#ifndef RGB_LED_H
#define RGB_LED_H

#include <Arduino.h>
#include "Led.h"

/**
 * @brief RGB renk kombinasyonları
 *
 * Bit yapısı: 0bRGB
 * - Bit 2: Red
 * - Bit 1: Green
 * - Bit 0: Blue
 */
enum class Color : uint8_t {
    None    = 0b000,  // Kapalı
    Red     = 0b100,  // Kırmızı
    Green   = 0b010,  // Yeşil
    Blue    = 0b001,  // Mavi
    Yellow  = 0b110,  // Sarı (Red + Green)
    Cyan    = 0b011,  // Cyan (Green + Blue)
    Magenta = 0b101,  // Magenta (Red + Blue)
    White   = 0b111   // Beyaz (All on)
};

class RgbLed {
public:
    /**
     * @brief RGB LED constructor
     * @param redPin Kırmızı LED pin
     * @param greenPin Yeşil LED pin
     * @param bluePin Mavi LED pin
     * @param activeLow Active LOW mu? (default: true)
     */
    RgbLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool activeLow = true);

    /**
     * @brief Tüm LED'leri başlat
     */
    void begin();

    /**
     * @brief Renk ayarla (enum ile)
     */
    void setColor(Color color);

    /**
     * @brief Renk ayarla (ayrı boolean'lar ile)
     */
    void setColor(bool red, bool green, bool blue);

    /**
     * @brief Tüm LED'leri kapat
     */
    void off();

    /**
     * @brief Belirli süre renk göster sonra kapat
     */
    void flash(Color color, unsigned long duration = 1000);

    /**
     * @brief Ana renkleri (R, G, B) döngüle
     */
    void cyclePrimary(unsigned long duration = 1000);

    /**
     * @brief Tüm renkleri döngüle
     */
    void cycleAll(unsigned long duration = 500);

    /**
     * @brief Mevcut rengi döndür
     */
    Color getColor() const;

    // Bireysel LED erişimi
    Led& red();
    Led& green();
    Led& blue();

private:
    Led _red;
    Led _green;
    Led _blue;
    Color _currentColor;
};

#endif // RGB_LED_H
