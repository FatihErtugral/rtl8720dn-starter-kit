/**
 * @file bw16_kit_v1_2.h
 * @brief BW16-Kit v1.2 (B&T) board configuration
 *
 * RTL8720DN tabanlı B&T BW16-Kit geliştirme kartı.
 * - 13 GPIO pin
 * - 1 ADC kanalı (A0 / PB3)
 * - 1 I2C bus (LP_I2C)
 * - 5 PWM kanalı
 * - FCC ID: 2AHMR-BW16
 *
 * Pin diyagramı için bkz: docs/bw16-kit.jpg
 * LED bilgisi için bkz: docs/bw16-kit_rgb-define.jpg
 */

#pragma once

// ============================================================================
// Board Identification
// ============================================================================
#define BOARD_NAME              "BW16-Kit_v1.2"
#define BOARD_VARIANT           "bw16kit"

// ============================================================================
// Hardware Capabilities
// ============================================================================
#define BOARD_GPIO_COUNT        13
#define BOARD_ADC_COUNT         1
#define BOARD_PWM_COUNT         5
#define BOARD_I2C_COUNT         1

// Feature flags
#define BOARD_HAS_RGB_LED       1
#define BOARD_HAS_HS_I2C        0       // HS_I2C yok (PB20, PB21 mevcut değil)
#define BOARD_HAS_LP_I2C        1       // Low-Power I2C (PA25, PA26)

// ============================================================================
// RGB LED Pins (Active HIGH - LOW=OFF, HIGH=ON)
// Fiziksel test sonucu: Green=PA14(D10), Blue=PA13(D11)
// ============================================================================
#define PIN_LED_RED             12      // AMB_D12 / PA_12 (fiziksel Red)
#define PIN_LED_GREEN           10      // AMB_D10 / PA_14 (fiziksel Green)
#define PIN_LED_BLUE            11      // AMB_D11 / PA_13 (fiziksel Blue)
#define LED_ACTIVE_LOW          0       // LED'ler active HIGH!

// ============================================================================
// UART Pins
// ============================================================================
// LOG_UART (Serial) - USB üzerinden debug/PC iletişimi
#define PIN_LOG_TX              0       // AMB_D0 / PA_7
#define PIN_LOG_RX              1       // AMB_D1 / PA_8

// LP_UART (Serial1) - Harici cihaz iletişimi
#define PIN_SERIAL1_TX          4       // AMB_D4 / PB_1
#define PIN_SERIAL1_RX          5       // AMB_D5 / PB_2

// ============================================================================
// I2C Pins
// ============================================================================
// LP_I2C (Wire) - Tek I2C bus
#define PIN_I2C_SDA             8       // AMB_D8 / PA_26
#define PIN_I2C_SCL             7       // AMB_D7 / PA_25

// HS_I2C mevcut değil - bu pinler tanımlı değil
// #define PIN_I2C1_SDA         // Yok
// #define PIN_I2C1_SCL         // Yok

// ============================================================================
// SPI Pins
// ============================================================================
#define PIN_SPI_MOSI            12      // AMB_D12 / PA_12 (LED_R ile paylaşımlı!)
#define PIN_SPI_MISO            11      // AMB_D11 / PA_13 (LED_B ile paylaşımlı!)
#define PIN_SPI_SCLK            10      // AMB_D10 / PA_14 (LED_G ile paylaşımlı!)
#define PIN_SPI_SS              9       // AMB_D9 / PA_15

// ============================================================================
// ADC Pins
// ============================================================================
#define PIN_ADC0                6       // AMB_D6 / PB_3 (A0) - Tek ADC!

// PB1 ve PB2 bu boardda LP_UART için kullanılıyor, ADC olarak kullanılamaz
// #define PIN_ADC1             // Yok (LP_UART_TX)
// #define PIN_ADC2             // Yok (LP_UART_RX)

// ============================================================================
// PWM Pins
// ============================================================================
#define PIN_PWM0                12      // AMB_D12 / PA_12 / LP_PWM0
#define PIN_PWM1                11      // AMB_D11 / PA_13 / LP_PWM1
#define PIN_PWM4                7       // AMB_D7 / PA_25 / LP_PWM4
#define PIN_PWM5                8       // AMB_D8 / PA_26 / LP_PWM5
// PA_30 da PWM destekliyor ama LP_PWM1 ile paylaşımlı
#define PIN_PWM1_ALT            3       // AMB_D3 / PA_30 / LP_PWM1 (alternatif)

// ============================================================================
// SWD Debug Pins
// ============================================================================
#define PIN_SWD_DATA            2       // AMB_D2 / PA_27
#define PIN_SWD_CLK             12      // AMB_D12 / PA_12 (SPI_MOSI ile paylaşımlı!)

// ============================================================================
// IR Pins (opsiyonel)
// ============================================================================
#define PIN_IR_TX               7       // AMB_D7 / PA_25
#define PIN_IR_RX               8       // AMB_D8 / PA_26
