/**
 * @file uart_test.ino
 * @brief Dual UART Test Example
 *
 * RTL8720DN'de iki UART portu test örneği:
 * - LOG_UART (Serial)  : USB üzerinden PC ile iletişim (debug)
 * - LP_UART (Serial1)  : Harici cihaz ile iletişim
 *
 * Bu örnek:
 * 1. Her iki UART'ı başlatır
 * 2. LOG_UART'tan gelen veriyi LP_UART'a yönlendirir
 * 3. LP_UART'tan gelen veriyi LOG_UART'a yönlendirir
 *
 * Test için:
 * - USB ile PC'ye bağlayın (Serial Monitor 115200)
 * - LP_UART pinlerine (PB1/TX, PB2/RX) başka bir cihaz bağlayın
 *
 * Desteklenen kartlar:
 * - NICEMCU_8720_v1 (-DBOARD_NICEMCU)
 * - BW16-Kit v1.2 (-DBOARD_BW16KIT)
 */

#include <BoardConfig.h>
#include <SerialManager.h>

// Buffer boyutu
const size_t BUFFER_SIZE = 256;
char inputBuffer[BUFFER_SIZE];
size_t bufferIndex = 0;

// LED feedback (veri alındığında yanıp söner)
const uint8_t LED_PIN = PIN_LED_GREEN;

void setup() {
    // SerialManager ile her iki UART'ı başlat
    serialManager.begin(DEBUG_BAUD_RATE, DATA_BAUD_RATE);

    // LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // Kapalı (Active LOW)

    delay(1000);

    // Header
    serialManager.logPrintln("================================");
    serialManager.logPrintln("    Dual UART Test Example");
    serialManager.logPrintln("================================");
    serialManager.printBoardInfo();
    serialManager.logPrintln();

    serialManager.logPrintln("UART Configuration:");
    serialManager.logPrintf("  LOG_UART (Serial):  %lu baud - USB/PC\n", (unsigned long)DEBUG_BAUD_RATE);
    serialManager.logPrintf("  LP_UART (Serial1):  %lu baud - External device\n", (unsigned long)DATA_BAUD_RATE);
    serialManager.logPrintln();

    serialManager.logPrintln("Pin Assignments:");
    serialManager.logPrintf("  LOG_TX: D%d (PA_7)\n", PIN_LOG_TX);
    serialManager.logPrintf("  LOG_RX: D%d (PA_8)\n", PIN_LOG_RX);
    serialManager.logPrintf("  SERIAL1_TX: D%d\n", PIN_SERIAL1_TX);
    serialManager.logPrintf("  SERIAL1_RX: D%d\n", PIN_SERIAL1_RX);
    serialManager.logPrintln();

    serialManager.logPrintln("Instructions:");
    serialManager.logPrintln("  - Type in Serial Monitor -> sent to LP_UART");
    serialManager.logPrintln("  - Data from LP_UART -> shown in Serial Monitor");
    serialManager.logPrintln("  - LED blinks on data receive");
    serialManager.logPrintln();
    serialManager.logPrintln("Ready! Waiting for data...");
    serialManager.logPrintln("================================");
    serialManager.logPrintln();
}

void blinkLed() {
    digitalWrite(LED_PIN, LOW);   // Aç
    delay(50);
    digitalWrite(LED_PIN, HIGH);  // Kapat
}

void loop() {
    // LOG_UART'tan veri var mı? (PC'den gelen)
    while (DEBUG_SERIAL.available()) {
        char c = DEBUG_SERIAL.read();

        // Echo to debug
        DEBUG_SERIAL.print(c);

        // LP_UART'a gönder
        DATA_SERIAL.print(c);

        // Enter tuşuna basıldıysa bilgi ver
        if (c == '\n') {
            serialManager.logPrintln("[Sent to LP_UART]");
            blinkLed();
        }
    }

    // LP_UART'tan veri var mı? (Harici cihazdan gelen)
    while (DATA_SERIAL.available()) {
        char c = DATA_SERIAL.read();

        // Buffer'a ekle
        if (bufferIndex < BUFFER_SIZE - 1) {
            inputBuffer[bufferIndex++] = c;
        }

        // Satır sonu veya buffer doldu
        if (c == '\n' || bufferIndex >= BUFFER_SIZE - 1) {
            inputBuffer[bufferIndex] = '\0';

            // LOG_UART'a yazdır
            serialManager.logPrint("[LP_UART] ");
            serialManager.logPrint(inputBuffer);

            // Buffer'ı sıfırla
            bufferIndex = 0;

            blinkLed();
        }
    }
}
