/**
 * @file BoardConfig.h
 * @brief Board selection dispatcher for RTL8720DN variants
 *
 * Bu dosya build-time board seçimini yönetir.
 * Kullanım: arduino-cli compile --build-property "build.extra_flags=-DBOARD_NICEMCU"
 *
 * Desteklenen boardlar:
 * - BOARD_NICEMCU   : NICEMCU_8720_v1 (15 GPIO, 3 ADC, HS_I2C)
 * - BOARD_BW16KIT   : BW16-Kit v1.2 (13 GPIO, 1 ADC)
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// Board seçimi
#if defined(BOARD_NICEMCU)
    #include "boards/nicemcu_8720_v1.h"
#elif defined(BOARD_BW16KIT)
    #include "boards/bw16_kit_v1_2.h"
#else
    // Default: NICEMCU - geliştirme sırasında warning göster
    #warning "Board tanımlı değil! -DBOARD_NICEMCU veya -DBOARD_BW16KIT kullanın. Default: NICEMCU"
    #include "boards/nicemcu_8720_v1.h"
#endif

// Board bilgisi kontrolü
#ifndef BOARD_NAME
    #error "BOARD_NAME tanımlı değil! Board header dosyası eksik."
#endif

// Ortak tanımlamalar (her iki board için geçerli)
#define RTL8720DN_CHIP          1
#define WIFI_DUAL_BAND          1   // 2.4GHz + 5.8GHz
#define BLE_SUPPORTED           1

// Serial port tanımlamaları
#define DEBUG_SERIAL            Serial      // LOG_UART (USB)
#define DATA_SERIAL             Serial1     // LP_UART (harici cihaz)

// Default baud rates
#ifndef DEBUG_BAUD_RATE
    #define DEBUG_BAUD_RATE     115200
#endif

#ifndef DATA_BAUD_RATE
    #define DATA_BAUD_RATE      9600
#endif

#endif // BOARD_CONFIG_H
