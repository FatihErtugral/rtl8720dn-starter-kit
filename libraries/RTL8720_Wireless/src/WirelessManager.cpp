/**
 * @file WirelessManager.cpp
 * @brief Wireless connectivity manager implementation
 *
 * RTL8720DN SDK API'sine uygun implementasyon.
 */

#include "WirelessManager.h"
#include <WiFi.h>

WirelessManager::WirelessManager()
    : _wifiState(WirelessState::Disconnected)
    , _bleState(WirelessState::Disconnected)
    , _wifiEnabled(false)
    , _bleEnabled(false)
{
}

// ============================================================================
// Initialization
// ============================================================================

void WirelessManager::begin(bool enableWifi, bool enableBle) {
    _wifiEnabled = enableWifi;
    _bleEnabled = enableBle;

    if (_wifiEnabled) {
        // RTL8720DN default olarak station modunda çalışır
        // WiFi sadece bağlıysa disconnect yap - SDK taramada otomatik başlatır
        if (WiFi.status() == WL_CONNECTED) {
            WiFi.disconnect();
            delay(100);
        }
        // Driver hazırlığı için bekle
        delay(500);
        DEBUG_SERIAL.println("[Wireless] WiFi initialized (Station mode)");
    }

    if (_bleEnabled) {
        beginBLE();
    }
}

void WirelessManager::end() {
    if (_wifiEnabled) {
        disconnectWiFi();
        // RTL8720DN doesn't have WiFi.mode(WIFI_OFF)
        _wifiEnabled = false;
    }

    if (_bleEnabled) {
        endBLE();
        _bleEnabled = false;
    }
}

// ============================================================================
// WiFi Operations
// ============================================================================

void WirelessManager::setWiFiMode(WiFiMode mode) {
    switch (mode) {
        case WiFiMode::Station:
            // Default mode - sadece bağlıysa disconnect yap
            if (WiFi.status() == WL_CONNECTED) {
                WiFi.disconnect();
            }
            break;
        case WiFiMode::AccessPoint:
            // Will be set when calling apbegin
            break;
        case WiFiMode::StationAP:
            // Use enableConcurrent for STA+AP mode
            WiFi.enableConcurrent();
            break;
    }
}

bool WirelessManager::connectWiFi(const char* ssid, const char* password,
                                   unsigned long timeout) {
    if (!_wifiEnabled) {
        DEBUG_SERIAL.println("[Wireless] WiFi not enabled!");
        return false;
    }

    _wifiState = WirelessState::Connecting;

    DEBUG_SERIAL.print("[Wireless] Connecting to: ");
    DEBUG_SERIAL.println(ssid);

    // RTL8720DN requires char* not const char*
    char ssidBuf[33];
    strncpy(ssidBuf, ssid, sizeof(ssidBuf) - 1);
    ssidBuf[sizeof(ssidBuf) - 1] = '\0';

    if (password != nullptr) {
        WiFi.begin(ssidBuf, password);
    } else {
        WiFi.begin(ssidBuf);
    }

    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startTime > timeout) {
            DEBUG_SERIAL.println("\n[Wireless] Connection timeout!");
            _wifiState = WirelessState::Error;
            return false;
        }
        delay(500);
        DEBUG_SERIAL.print(".");
    }

    DEBUG_SERIAL.println();
    DEBUG_SERIAL.println("[Wireless] Connected!");
    DEBUG_SERIAL.print("[Wireless] IP: ");
    DEBUG_SERIAL.println(WiFi.localIP());

    _wifiState = WirelessState::Connected;
    return true;
}

void WirelessManager::disconnectWiFi() {
    WiFi.disconnect();
    _wifiState = WirelessState::Disconnected;
    DEBUG_SERIAL.println("[Wireless] WiFi disconnected");
}

bool WirelessManager::isWiFiConnected() const {
    return WiFi.status() == WL_CONNECTED;
}

int WirelessManager::getWiFiRSSI() const {
    if (!isWiFiConnected()) return 0;
    return WiFi.RSSI();
}

String WirelessManager::getWiFiSSID() const {
    return String(WiFi.SSID());
}

String WirelessManager::getLocalIP() const {
    IPAddress ip = WiFi.localIP();
    char buf[16];
    snprintf(buf, sizeof(buf), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    return String(buf);
}

int WirelessManager::scanNetworks() {
    DEBUG_SERIAL.println("[Wireless] Scanning networks...");
    int numNetworks = WiFi.scanNetworks();
    DEBUG_SERIAL.print("[Wireless] Found ");
    DEBUG_SERIAL.print(numNetworks);
    DEBUG_SERIAL.println(" network(s)");
    return numNetworks;
}

// ============================================================================
// BLE Operations (Placeholder)
// ============================================================================

void WirelessManager::beginBLE(const char* deviceName) {
    // TODO: BLE implementation
    // RTL8720DN BLE API kullanılacak
    DEBUG_SERIAL.print("[Wireless] BLE initialized as: ");
    DEBUG_SERIAL.println(deviceName);
    _bleState = WirelessState::Disconnected;
    _bleEnabled = true;
}

void WirelessManager::endBLE() {
    // TODO: BLE cleanup
    _bleState = WirelessState::Disconnected;
    _bleEnabled = false;
    DEBUG_SERIAL.println("[Wireless] BLE disabled");
}

bool WirelessManager::isBLEActive() const {
    return _bleEnabled;
}

// ============================================================================
// Status
// ============================================================================

void WirelessManager::printStatus() const {
    DEBUG_SERIAL.println("================================");
    DEBUG_SERIAL.println("     Wireless Status");
    DEBUG_SERIAL.println("================================");

    // WiFi Status
    DEBUG_SERIAL.println("[WiFi]");
    DEBUG_SERIAL.print("  Enabled: ");
    DEBUG_SERIAL.println(_wifiEnabled ? "Yes" : "No");

    if (_wifiEnabled) {
        DEBUG_SERIAL.print("  State: ");
        switch (_wifiState) {
            case WirelessState::Disconnected:
                DEBUG_SERIAL.println("Disconnected");
                break;
            case WirelessState::Connecting:
                DEBUG_SERIAL.println("Connecting...");
                break;
            case WirelessState::Connected:
                DEBUG_SERIAL.println("Connected");
                DEBUG_SERIAL.print("  SSID: ");
                DEBUG_SERIAL.println(getWiFiSSID());
                DEBUG_SERIAL.print("  IP: ");
                DEBUG_SERIAL.println(getLocalIP());
                DEBUG_SERIAL.print("  RSSI: ");
                DEBUG_SERIAL.print(getWiFiRSSI());
                DEBUG_SERIAL.println(" dBm");
                break;
            case WirelessState::Error:
                DEBUG_SERIAL.println("Error");
                break;
        }
    }

    // BLE Status
    DEBUG_SERIAL.println("[BLE]");
    DEBUG_SERIAL.print("  Enabled: ");
    DEBUG_SERIAL.println(_bleEnabled ? "Yes" : "No");

    DEBUG_SERIAL.println("================================");
}
