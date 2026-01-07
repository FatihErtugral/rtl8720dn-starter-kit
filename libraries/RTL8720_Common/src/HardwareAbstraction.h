/**
 * @file HardwareAbstraction.h
 * @brief Hardware Abstraction Layer for RTL8720DN boards
 *
 * Bu dosya board-agnostic donanım erişimi sağlar.
 * Pin işlemleri, peripheral başlatma ve board özelliklerini
 * tek bir interface üzerinden sunar.
 */

#ifndef HARDWARE_ABSTRACTION_H
#define HARDWARE_ABSTRACTION_H

#include <Arduino.h>
#include "BoardConfig.h"

/**
 * @brief Hardware Abstraction Layer sınıfı
 *
 * Singleton pattern ile tek instance kullanımı sağlar.
 */
class HardwareAbstraction {
public:
    /**
     * @brief Singleton instance al
     */
    static HardwareAbstraction& getInstance() {
        static HardwareAbstraction instance;
        return instance;
    }

    // ========================================================================
    // Board Info
    // ========================================================================

    /**
     * @brief Board adını döndür
     */
    const char* getBoardName() const {
        return BOARD_NAME;
    }

    /**
     * @brief GPIO pin sayısını döndür
     */
    uint8_t getGpioCount() const {
        return BOARD_GPIO_COUNT;
    }

    /**
     * @brief ADC kanal sayısını döndür
     */
    uint8_t getAdcCount() const {
        return BOARD_ADC_COUNT;
    }

    /**
     * @brief HS_I2C mevcut mu?
     */
    bool hasHighSpeedI2C() const {
        return BOARD_HAS_HS_I2C;
    }

    /**
     * @brief RGB LED mevcut mu?
     */
    bool hasRgbLed() const {
        return BOARD_HAS_RGB_LED;
    }

    // ========================================================================
    // LED Pins
    // ========================================================================

    uint8_t getLedRedPin() const { return PIN_LED_RED; }
    uint8_t getLedGreenPin() const { return PIN_LED_GREEN; }
    uint8_t getLedBluePin() const { return PIN_LED_BLUE; }

    // ========================================================================
    // UART Pins
    // ========================================================================

    uint8_t getLogTxPin() const { return PIN_LOG_TX; }
    uint8_t getLogRxPin() const { return PIN_LOG_RX; }
    uint8_t getSerial1TxPin() const { return PIN_SERIAL1_TX; }
    uint8_t getSerial1RxPin() const { return PIN_SERIAL1_RX; }

    // ========================================================================
    // I2C Pins
    // ========================================================================

    uint8_t getI2cSdaPin() const { return PIN_I2C_SDA; }
    uint8_t getI2cSclPin() const { return PIN_I2C_SCL; }

#if BOARD_HAS_HS_I2C
    uint8_t getI2c1SdaPin() const { return PIN_I2C1_SDA; }
    uint8_t getI2c1SclPin() const { return PIN_I2C1_SCL; }
#endif

    // ========================================================================
    // SPI Pins
    // ========================================================================

    uint8_t getSpiMosiPin() const { return PIN_SPI_MOSI; }
    uint8_t getSpiMisoPin() const { return PIN_SPI_MISO; }
    uint8_t getSpiSclkPin() const { return PIN_SPI_SCLK; }
    uint8_t getSpiSsPin() const { return PIN_SPI_SS; }

    // ========================================================================
    // ADC
    // ========================================================================

    /**
     * @brief ADC değeri oku
     * @param channel ADC kanalı (0, 1, 2)
     * @return ADC değeri (0-4095) veya -1 hata durumunda
     */
    int readAdc(uint8_t channel) const {
        if (channel >= BOARD_ADC_COUNT) {
            return -1;
        }

        switch (channel) {
            case 0: return analogRead(PIN_ADC0);
#if BOARD_ADC_COUNT >= 2
            case 1: return analogRead(PIN_ADC1);
#endif
#if BOARD_ADC_COUNT >= 3
            case 2: return analogRead(PIN_ADC2);
#endif
            default: return -1;
        }
    }

    // ========================================================================
    // Utility
    // ========================================================================

    /**
     * @brief Board bilgilerini Serial'a yazdır
     */
    void printInfo() const {
        DEBUG_SERIAL.println("================================");
        DEBUG_SERIAL.print("Board: ");
        DEBUG_SERIAL.println(BOARD_NAME);
        DEBUG_SERIAL.print("GPIO Count: ");
        DEBUG_SERIAL.println(BOARD_GPIO_COUNT);
        DEBUG_SERIAL.print("ADC Count: ");
        DEBUG_SERIAL.println(BOARD_ADC_COUNT);
        DEBUG_SERIAL.print("I2C Count: ");
        DEBUG_SERIAL.println(BOARD_I2C_COUNT);
        DEBUG_SERIAL.print("Has HS_I2C: ");
        DEBUG_SERIAL.println(BOARD_HAS_HS_I2C ? "Yes" : "No");
        DEBUG_SERIAL.print("Has RGB LED: ");
        DEBUG_SERIAL.println(BOARD_HAS_RGB_LED ? "Yes" : "No");
        DEBUG_SERIAL.println("================================");
    }

private:
    // Private constructor (Singleton)
    HardwareAbstraction() {}

    // Delete copy constructor and assignment
    HardwareAbstraction(const HardwareAbstraction&) = delete;
    HardwareAbstraction& operator=(const HardwareAbstraction&) = delete;
};

// Global erişim için kısayol
#define Hardware HardwareAbstraction::getInstance()

#endif // HARDWARE_ABSTRACTION_H
