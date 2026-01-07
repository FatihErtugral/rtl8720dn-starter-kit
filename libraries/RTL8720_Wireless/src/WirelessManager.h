/**
 * @file WirelessManager.h
 * @brief Wireless connectivity manager for RTL8720DN
 *
 * BLE ve WiFi bağlantılarını yöneten üst düzey sınıf.
 * Her iki bağlantı türünü tek bir interface üzerinden sunar.
 *
 * RTL8720DN özellikleri:
 * - Dual-band WiFi (2.4GHz + 5.8GHz)
 * - Bluetooth Low Energy (BLE) 5.0
 * - Co-existence mode (WiFi + BLE aynı anda)
 */

#ifndef WIRELESS_MANAGER_H
#define WIRELESS_MANAGER_H

#include <Arduino.h>
#include <BoardConfig.h>

// Forward declarations
class WiFiModule;
class BleModule;

/**
 * @brief Wireless bağlantı durumu
 */
enum class WirelessState {
    Disconnected,
    Connecting,
    Connected,
    Error
};

/**
 * @brief WiFi bağlantı modu
 */
enum class WiFiMode {
    Station,        // Client modu
    AccessPoint,    // AP modu
    StationAP       // Her ikisi
};

/**
 * @brief Wireless Manager sınıfı
 *
 * WiFi ve BLE bağlantılarını yönetir.
 * Singleton pattern kullanır.
 */
class WirelessManager {
public:
    /**
     * @brief Singleton instance al
     */
    static WirelessManager& getInstance() {
        static WirelessManager instance;
        return instance;
    }

    // ========================================================================
    // Initialization
    // ========================================================================

    /**
     * @brief Wireless sistemini başlat
     * @param enableWifi WiFi'ı etkinleştir
     * @param enableBle BLE'yi etkinleştir
     */
    void begin(bool enableWifi = true, bool enableBle = false);

    /**
     * @brief Wireless sistemini kapat
     */
    void end();

    // ========================================================================
    // WiFi Operations
    // ========================================================================

    /**
     * @brief WiFi modunu ayarla
     */
    void setWiFiMode(WiFiMode mode);

    /**
     * @brief WiFi ağına bağlan
     * @param ssid Ağ adı
     * @param password Şifre (açık ağ için nullptr)
     * @param timeout Bağlantı timeout (ms)
     * @return true başarılı, false başarısız
     */
    bool connectWiFi(const char* ssid, const char* password = nullptr,
                     unsigned long timeout = 30000);

    /**
     * @brief WiFi bağlantısını kes
     */
    void disconnectWiFi();

    /**
     * @brief WiFi bağlı mı?
     */
    bool isWiFiConnected() const;

    /**
     * @brief WiFi sinyal gücü (RSSI)
     */
    int getWiFiRSSI() const;

    /**
     * @brief Bağlı ağın SSID'si
     */
    String getWiFiSSID() const;

    /**
     * @brief Local IP adresi
     */
    String getLocalIP() const;

    /**
     * @brief Ağ taraması yap
     * @return Bulunan ağ sayısı
     */
    int scanNetworks();

    // ========================================================================
    // BLE Operations (Placeholder - sonra implement edilecek)
    // ========================================================================

    /**
     * @brief BLE'yi başlat
     * @param deviceName BLE cihaz adı
     */
    void beginBLE(const char* deviceName = "RTL8720DN");

    /**
     * @brief BLE'yi kapat
     */
    void endBLE();

    /**
     * @brief BLE aktif mi?
     */
    bool isBLEActive() const;

    // ========================================================================
    // Status
    // ========================================================================

    /**
     * @brief WiFi durumu
     */
    WirelessState getWiFiState() const { return _wifiState; }

    /**
     * @brief BLE durumu
     */
    WirelessState getBLEState() const { return _bleState; }

    /**
     * @brief Durum bilgisini yazdır
     */
    void printStatus() const;

private:
    // Private constructor (Singleton)
    WirelessManager();

    // Delete copy constructor and assignment
    WirelessManager(const WirelessManager&) = delete;
    WirelessManager& operator=(const WirelessManager&) = delete;

    // State
    WirelessState _wifiState;
    WirelessState _bleState;
    bool _wifiEnabled;
    bool _bleEnabled;
};

// Global erişim için kısayol
#define Wireless WirelessManager::getInstance()

#endif // WIRELESS_MANAGER_H
