/**
 * @file SerialManager.cpp
 * @brief Dual UART management implementation
 */

#include "SerialManager.h"
#include <stdarg.h>

// Global instance
SerialManager serialManager;

void SerialManager::begin(unsigned long logBaud, unsigned long dataBaud) {
    _logBaud = logBaud;
    _dataBaud = dataBaud;

    // LOG_UART başlat (debug/PC)
    DEBUG_SERIAL.begin(_logBaud);

    // LP_UART başlat (harici cihaz)
    DATA_SERIAL.begin(_dataBaud);

    _initialized = true;

    // Başlangıç gecikmesi - USB stabilizasyonu için
    delay(100);
}

// ============================================================================
// Debug/PC iletişimi (LOG_UART)
// ============================================================================

void SerialManager::logPrint(const char* msg) {
    DEBUG_SERIAL.print(msg);
}

void SerialManager::logPrint(const String& msg) {
    DEBUG_SERIAL.print(msg);
}

void SerialManager::logPrint(int value) {
    DEBUG_SERIAL.print(value);
}

void SerialManager::logPrint(float value, int decimals) {
    DEBUG_SERIAL.print(value, decimals);
}

void SerialManager::logPrintln(const char* msg) {
    DEBUG_SERIAL.println(msg);
}

void SerialManager::logPrintln(const String& msg) {
    DEBUG_SERIAL.println(msg);
}

void SerialManager::logPrintln(int value) {
    DEBUG_SERIAL.println(value);
}

void SerialManager::logPrintln(float value, int decimals) {
    DEBUG_SERIAL.println(value, decimals);
}

void SerialManager::logPrintln() {
    DEBUG_SERIAL.println();
}

void SerialManager::logPrintf(const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    DEBUG_SERIAL.print(buffer);
}

void SerialManager::printBoardInfo() {
    logPrintln("================================");
    logPrintf("Board: %s\n", BOARD_NAME);
    logPrintf("GPIO Count: %d\n", BOARD_GPIO_COUNT);
    logPrintf("ADC Count: %d\n", BOARD_ADC_COUNT);
    logPrintf("I2C Count: %d\n", BOARD_I2C_COUNT);
    logPrintf("Has RGB LED: %s\n", BOARD_HAS_RGB_LED ? "Yes" : "No");
    logPrintf("Has HS_I2C: %s\n", BOARD_HAS_HS_I2C ? "Yes" : "No");
    logPrintf("LOG_UART Baud: %lu\n", _logBaud);
    logPrintf("DATA_UART Baud: %lu\n", _dataBaud);
    logPrintln("================================");
}

// ============================================================================
// Harici cihaz iletişimi (LP_UART)
// ============================================================================

bool SerialManager::dataAvailable() {
    return DATA_SERIAL.available() > 0;
}

String SerialManager::readDataLine(unsigned long timeout) {
    String result = "";
    unsigned long startTime = millis();

    while (millis() - startTime < timeout) {
        if (DATA_SERIAL.available()) {
            char c = DATA_SERIAL.read();
            if (c == '\n') {
                break;
            } else if (c != '\r') {
                result += c;
            }
        }
    }

    return result;
}

int SerialManager::readDataByte() {
    if (DATA_SERIAL.available()) {
        return DATA_SERIAL.read();
    }
    return -1;
}

size_t SerialManager::readDataBytes(uint8_t* buffer, size_t length, unsigned long timeout) {
    size_t count = 0;
    unsigned long startTime = millis();

    while (count < length && (millis() - startTime < timeout)) {
        if (DATA_SERIAL.available()) {
            buffer[count++] = DATA_SERIAL.read();
        }
    }

    return count;
}

void SerialManager::sendData(const char* data) {
    DATA_SERIAL.print(data);
}

void SerialManager::sendData(const String& data) {
    DATA_SERIAL.print(data);
}

void SerialManager::sendData(uint8_t* buffer, size_t length) {
    DATA_SERIAL.write(buffer, length);
}

void SerialManager::sendDataLine(const char* data) {
    DATA_SERIAL.println(data);
}

void SerialManager::sendDataLine(const String& data) {
    DATA_SERIAL.println(data);
}

// ============================================================================
// Utility
// ============================================================================

void SerialManager::flushDataBuffer() {
    while (DATA_SERIAL.available()) {
        DATA_SERIAL.read();
    }
}

void SerialManager::flushLogBuffer() {
    DEBUG_SERIAL.flush();
}
