/**
 * @file wifi_scan.ino
 * @brief WiFi Network Scan Example
 *
 * RTL8720DN dual-band WiFi ile ağ tarama örneği.
 * 2.4GHz ve 5.8GHz bantlarında erişilebilir ağları listeler.
 *
 * Çıktı:
 * - SSID (ağ adı)
 * - RSSI (sinyal gücü dBm)
 * - Şifreleme tipi
 * - Kanal
 *
 * Desteklenen kartlar:
 * - NICEMCU_8720_v1 (-DBOARD_NICEMCU)
 * - BW16-Kit v1.2 (-DBOARD_BW16KIT)
 */

#include <BoardConfig.h>
#include <HardwareAbstraction.h>
#include <WiFiModule.h>

// Tarama aralığı
const unsigned long SCAN_INTERVAL = 10000;  // 10 saniye

// LED feedback
const uint8_t LED_PIN = PIN_LED_BLUE;

// WiFi Module instance
WiFiModule wifi;

void setup() {
    // Serial başlat
    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);
    delay(1000);

    // LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // Kapalı

    // Board bilgisi
    DEBUG_SERIAL.println();
    Hardware.printInfo();

    DEBUG_SERIAL.println("WiFi: Dual-band 2.4GHz/5.8GHz");
    DEBUG_SERIAL.println();

    // WiFi'ı station modunda başlat
    DEBUG_SERIAL.println("Initializing WiFi...");
    wifi.beginStation();

    // İlk tarama için WiFi driver'ın tam başlamasını bekle
    delay(2000);

    DEBUG_SERIAL.println("WiFi initialized in Station mode");
    DEBUG_SERIAL.println();
    DEBUG_SERIAL.println("Starting network scan...");
    DEBUG_SERIAL.println();
}

void scanNetworks() {
    // LED'i aç (tarama başladı)
    digitalWrite(LED_PIN, LOW);

    DEBUG_SERIAL.println("Scanning networks...");
    DEBUG_SERIAL.println();

    int numNetworks = wifi.scan();

    if (numNetworks == 0) {
        DEBUG_SERIAL.println("No networks found!");
    } else {
        DEBUG_SERIAL.print("Found ");
        DEBUG_SERIAL.print(numNetworks);
        DEBUG_SERIAL.println(" network(s):");
        DEBUG_SERIAL.println();

        // Tablo başlığı
        DEBUG_SERIAL.println("  #  | RSSI  | Encryption  | SSID");
        DEBUG_SERIAL.println("-----|-------|-------------|------------------------");

        for (int i = 0; i < numNetworks; i++) {
            WiFiNetworkInfo info;
            if (!wifi.getNetworkInfo(i, info)) continue;

            // Satır numarası
            DEBUG_SERIAL.print(" ");
            if (i < 9) DEBUG_SERIAL.print(" ");
            DEBUG_SERIAL.print(i + 1);
            DEBUG_SERIAL.print(" | ");

            // RSSI
            if (info.rssi > -100) DEBUG_SERIAL.print(" ");
            DEBUG_SERIAL.print(info.rssi);
            DEBUG_SERIAL.print(" | ");

            // Şifreleme
            const char* enc = WiFiModule::encryptionTypeToString(info.encryptionType);
            DEBUG_SERIAL.print(enc);
            // Padding
            for (size_t j = strlen(enc); j < 11; j++) {
                DEBUG_SERIAL.print(" ");
            }
            DEBUG_SERIAL.print(" | ");

            // SSID
            DEBUG_SERIAL.println(info.ssid);

            delay(10);  // Serial buffer için
        }
    }

    // LED'i kapat
    digitalWrite(LED_PIN, HIGH);

    DEBUG_SERIAL.println();
    DEBUG_SERIAL.print("Next scan in ");
    DEBUG_SERIAL.print(SCAN_INTERVAL / 1000);
    DEBUG_SERIAL.println(" seconds...");
    DEBUG_SERIAL.println("================================");
    DEBUG_SERIAL.println();
}

void loop() {
    scanNetworks();
    delay(SCAN_INTERVAL);
}
