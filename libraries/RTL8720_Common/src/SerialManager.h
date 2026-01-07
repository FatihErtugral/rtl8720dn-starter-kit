/**
 * @file SerialManager.h
 * @brief Dual UART management for RTL8720DN boards
 *
 * Bu sınıf iki UART portunu yönetir:
 * - LOG_UART (Serial)  : Debug/PC iletişimi (USB üzerinden)
 * - LP_UART (Serial1)  : Harici cihaz iletişimi (GPS, sensör vb.)
 */

#pragma once

#include <Arduino.h>
#include "BoardConfig.h"

class SerialManager {
public:
    /**
     * @brief Her iki UART portunu başlatır
     * @param logBaud LOG_UART baud rate (default: 115200)
     * @param dataBaud LP_UART baud rate (default: 9600)
     */
    void begin(unsigned long logBaud = DEBUG_BAUD_RATE,
               unsigned long dataBaud = DATA_BAUD_RATE);

    // ========================================================================
    // Debug/PC iletişimi (LOG_UART - Serial)
    // ========================================================================

    /**
     * @brief Debug mesajı yazdır (newline yok)
     */
    void logPrint(const char* msg);
    void logPrint(const String& msg);
    void logPrint(int value);
    void logPrint(float value, int decimals = 2);

    /**
     * @brief Debug mesajı yazdır (newline ile)
     */
    void logPrintln(const char* msg);
    void logPrintln(const String& msg);
    void logPrintln(int value);
    void logPrintln(float value, int decimals = 2);
    void logPrintln();  // Sadece newline

    /**
     * @brief Formatlanmış debug mesajı (printf-style)
     */
    void logPrintf(const char* format, ...);

    /**
     * @brief Board bilgisini yazdır
     */
    void printBoardInfo();

    // ========================================================================
    // Harici cihaz iletişimi (LP_UART - Serial1)
    // ========================================================================

    /**
     * @brief LP_UART'ta veri var mı?
     */
    bool dataAvailable();

    /**
     * @brief LP_UART'tan bir satır oku
     * @param timeout Timeout in ms (default: 1000)
     * @return Okunan string (boş ise timeout)
     */
    String readDataLine(unsigned long timeout = 1000);

    /**
     * @brief LP_UART'tan byte oku
     * @return Okunan byte (-1 ise veri yok)
     */
    int readDataByte();

    /**
     * @brief LP_UART'tan belirli sayıda byte oku
     * @param buffer Hedef buffer
     * @param length Okunacak byte sayısı
     * @param timeout Timeout in ms
     * @return Okunan byte sayısı
     */
    size_t readDataBytes(uint8_t* buffer, size_t length, unsigned long timeout = 1000);

    /**
     * @brief LP_UART'a veri gönder
     */
    void sendData(const char* data);
    void sendData(const String& data);
    void sendData(uint8_t* buffer, size_t length);

    /**
     * @brief LP_UART'a veri gönder (newline ile)
     */
    void sendDataLine(const char* data);
    void sendDataLine(const String& data);

    // ========================================================================
    // Utility
    // ========================================================================

    /**
     * @brief LP_UART buffer'ını temizle
     */
    void flushDataBuffer();

    /**
     * @brief LOG_UART buffer'ını temizle
     */
    void flushLogBuffer();

private:
    bool _initialized = false;
    unsigned long _logBaud = DEBUG_BAUD_RATE;
    unsigned long _dataBaud = DATA_BAUD_RATE;
};

// Global instance
extern SerialManager serialManager;
