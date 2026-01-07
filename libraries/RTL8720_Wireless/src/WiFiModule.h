/**
 * @file WiFiModule.h
 * @brief WiFi module wrapper for RTL8720DN
 *
 * RTL8720DN dual-band WiFi özelliklerini saran modül.
 * - 2.4GHz (802.11 b/g/n)
 * - 5.8GHz (802.11 a/n/ac)
 */

#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <Arduino.h>
#include <WiFi.h>
#include <BoardConfig.h>

/**
 * @brief WiFi ağ bilgisi yapısı
 */
struct WiFiNetworkInfo {
    String ssid;
    int32_t rssi;
    uint8_t encryptionType;
    uint8_t channel;
    bool is5GHz;
};

/**
 * @brief WiFi Module sınıfı
 *
 * Düşük seviye WiFi işlemleri için wrapper.
 * RTL8720DN SDK API'sine uygun implementasyon.
 */
class WiFiModule {
public:
    WiFiModule() = default;

    // ========================================================================
    // Connection
    // ========================================================================

    /**
     * @brief Station modunda başlat
     * RTL8720DN default olarak station modunda çalışır
     * NOT: WiFi.disconnect() başlatılmadan çağrılmamalı - SDK taramada otomatik başlatır
     */
    void beginStation() {
        // WiFi sadece bağlıysa disconnect yap
        if (WiFi.status() == WL_CONNECTED) {
            WiFi.disconnect();
            delay(100);
        }
        // Driver hazırlığı için bekle
        delay(500);
    }

    /**
     * @brief Access Point modunda başlat
     * @param ssid AP adı
     * @param password Şifre (min 8 karakter, nullptr ise açık ağ)
     * @param channel WiFi kanalı string olarak ("1"-"13")
     */
    bool beginAP(const char* ssid, const char* password = nullptr,
                 const char* channel = "1") {
        char ssidBuf[33];
        char channelBuf[4];
        strncpy(ssidBuf, ssid, sizeof(ssidBuf) - 1);
        ssidBuf[sizeof(ssidBuf) - 1] = '\0';
        strncpy(channelBuf, channel, sizeof(channelBuf) - 1);
        channelBuf[sizeof(channelBuf) - 1] = '\0';

        if (password != nullptr && strlen(password) >= 8) {
            char passBuf[65];
            strncpy(passBuf, password, sizeof(passBuf) - 1);
            passBuf[sizeof(passBuf) - 1] = '\0';
            return WiFi.apbegin(ssidBuf, passBuf, channelBuf) == WL_CONNECTED;
        } else {
            return WiFi.apbegin(ssidBuf, channelBuf) == WL_CONNECTED;
        }
    }

    /**
     * @brief Ağa bağlan
     */
    bool connect(const char* ssid, const char* password = nullptr,
                 unsigned long timeout = 30000) {
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
                return false;
            }
            delay(100);
        }
        return true;
    }

    /**
     * @brief Bağlantıyı kes
     */
    void disconnect() {
        WiFi.disconnect();
    }

    /**
     * @brief Bağlı mı?
     */
    bool isConnected() const {
        return WiFi.status() == WL_CONNECTED;
    }

    // ========================================================================
    // Network Info
    // ========================================================================

    String getSSID() const { return String(WiFi.SSID()); }
    int32_t getRSSI() const { return WiFi.RSSI(); }

    String getLocalIP() const {
        IPAddress ip = WiFi.localIP();
        char buf[16];
        snprintf(buf, sizeof(buf), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
        return String(buf);
    }

    String getMacAddress() const {
        uint8_t mac[6];
        WiFi.macAddress(mac);
        char buf[18];
        snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return String(buf);
    }

    String getGatewayIP() const {
        IPAddress ip = WiFi.gatewayIP();
        char buf[16];
        snprintf(buf, sizeof(buf), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
        return String(buf);
    }

    String getSubnetMask() const {
        IPAddress ip = WiFi.subnetMask();
        char buf[16];
        snprintf(buf, sizeof(buf), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
        return String(buf);
    }

    // ========================================================================
    // Scanning
    // ========================================================================

    /**
     * @brief Ağ taraması yap
     * @return Bulunan ağ sayısı
     */
    int scan() {
        return WiFi.scanNetworks();
    }

    /**
     * @brief Tarama sonucu al
     * @param index Ağ indexi
     * @param info Bilgi yapısı (output)
     * @return true başarılı
     */
    bool getNetworkInfo(int index, WiFiNetworkInfo& info) {
        if (index < 0) return false;

        info.ssid = String(WiFi.SSID(index));
        info.rssi = WiFi.RSSI(index);
        info.encryptionType = WiFi.encryptionType(index);

        // RTL8720DN SDK doesn't expose channel directly
        // Channel bilgisi encryptionTypeEx'ten alınabilir ama basit tutuyoruz
        info.channel = 0;  // Not available in this SDK
        info.is5GHz = false; // Estimate from RSSI if needed

        return true;
    }

    /**
     * @brief Şifreleme tipini string'e çevir
     * RTL8720DN encryption types from wl_definitions.h
     */
    static const char* encryptionTypeToString(uint8_t encType) {
        switch (encType) {
            case 0: return "Open";      // RTK_SECURITY_OPEN
            case 1: return "WEP";       // RTK_SECURITY_WEP_PSK
            case 2: return "WPA";       // RTK_SECURITY_WPA_TKIP_PSK
            case 3: return "WPA2";      // RTK_SECURITY_WPA2_AES_PSK
            case 4: return "WPA/WPA2";  // RTK_SECURITY_WPA_WPA2_MIXED
            case 5: return "WPA2-E";    // RTK_SECURITY_WPA2_ENTERPRISE
            case 6: return "WPA3";      // RTK_SECURITY_WPA3_AES_PSK
            default: return "Unknown";
        }
    }

    // ========================================================================
    // Power Management
    // ========================================================================

    /**
     * @brief WiFi güç tasarrufunu devre dışı bırak
     */
    void disablePowerSave() {
        WiFi.disablePowerSave();
    }
};

#endif // WIFI_MODULE_H
