/**
 * @file Led.h
 * @brief Single LED control class
 *
 * Tek bir LED'i kontrol etmek için kullanılan sınıf.
 * Active LOW ve Active HIGH LED'leri destekler.
 */

#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
public:
    /**
     * @brief LED constructor
     * @param pin GPIO pin numarası
     * @param activeLow true ise LOW=açık, HIGH=kapalı (default: true)
     */
    explicit Led(uint8_t pin, bool activeLow = true);

    /**
     * @brief LED'i başlat (pinMode ayarla, kapat)
     */
    void begin();

    /**
     * @brief LED'i aç
     */
    void on();

    /**
     * @brief LED'i kapat
     */
    void off();

    /**
     * @brief LED durumunu tersine çevir
     */
    void toggle();

    /**
     * @brief LED durumunu ayarla
     * @param state true=açık, false=kapalı
     */
    void set(bool state);

    /**
     * @brief LED açık mı?
     */
    bool isOn() const;

    /**
     * @brief LED'i belirli süre yak sonra kapat
     * @param duration Açık kalma süresi (ms)
     */
    void blink(unsigned long duration = 1000);

    /**
     * @brief GPIO pin numarasını döndür
     */
    uint8_t getPin() const;

private:
    uint8_t _pin;
    bool _activeLow;
    bool _state;

    void writeState();
};

#endif // LED_H
