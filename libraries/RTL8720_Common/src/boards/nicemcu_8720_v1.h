/**
 * @file nicemcu_8720_v1.h
 * @brief NICEMCU_8720_v1 board configuration
 *
 * RTL8720DN tabanlı NICEMCU geliştirme kartı.
 * - 15 GPIO pin
 * - 3 ADC kanalı (A0, A1, A2)
 * - 2 I2C bus (LP_I2C + HS_I2C)
 * - 7 PWM kanalı
 * - USB: CH340C
 *
 * Pin diyagramı için bkz: docs/NICEMCU_8720_v1_diagram_.jpg
 */

#pragma once

// ============================================================================
// Board Identification
// ============================================================================
#define BOARD_NAME              "NICEMCU_8720_v1"
#define BOARD_VARIANT           "nicemcu"

// ============================================================================
// Hardware Capabilities
// ============================================================================
#define BOARD_GPIO_COUNT        15
#define BOARD_ADC_COUNT         3
#define BOARD_PWM_COUNT         7
#define BOARD_I2C_COUNT         2

// Feature flags
#define BOARD_HAS_RGB_LED       1
#define BOARD_HAS_HS_I2C        1       // High-Speed I2C (PB20, PB21)
#define BOARD_HAS_LP_I2C        1       // Low-Power I2C (PA25, PA26)

// ============================================================================
// RGB LED Pins (Active LOW - HIGH=OFF, LOW=ON)
// Fiziksel test sonucu düzeltildi: Green=PA13, Blue=PA14
// ============================================================================
#define PIN_LED_RED             12      // AMB_D12 / PA_12
#define PIN_LED_GREEN           11      // AMB_D11 / PA_13 (fiziksel Green)
#define PIN_LED_BLUE            10      // AMB_D10 / PA_14 (fiziksel Blue)
#define LED_ACTIVE_LOW          1       // LED'ler active low

// ============================================================================
// UART Pins
// ============================================================================
// LOG_UART (Serial) - USB üzerinden debug/PC iletişimi
#define PIN_LOG_TX              0       // AMB_D0 / PA_7
#define PIN_LOG_RX              1       // AMB_D1 / PA_8

// LP_UART (Serial1) - Harici cihaz iletişimi
#define PIN_SERIAL1_TX          5       // AMB_D5 / PB_2
#define PIN_SERIAL1_RX          4       // AMB_D4 / PB_1

// ============================================================================
// I2C Pins
// ============================================================================
// LP_I2C (Wire) - Default I2C bus
#define PIN_I2C_SDA             8       // AMB_D8 / PA_26
#define PIN_I2C_SCL             7       // AMB_D7 / PA_25

// HS_I2C (Wire1) - High-Speed I2C bus (sadece bu boardda var)
#define PIN_I2C1_SDA            14      // AMB_D14 / PB_21
#define PIN_I2C1_SCL            13      // AMB_D13 / PB_20

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
#define PIN_ADC0                4       // AMB_D4 / PB_1 (A0)
#define PIN_ADC1                5       // AMB_D5 / PB_2 (A1)
#define PIN_ADC2                6       // AMB_D6 / PB_3 (A2)

// ============================================================================
// PWM Pins
// ============================================================================
#define PIN_PWM0                12      // AMB_D12 / PA_12 / HS_PWM0
#define PIN_PWM1                11      // AMB_D11 / PA_13 / HS_PWM1
#define PIN_PWM4                7       // AMB_D7 / PA_25 / HS_PWM4
#define PIN_PWM5                8       // AMB_D8 / PA_26 / HS_PWM5
#define PIN_PWM7                3       // AMB_D3 / PA_30 / HS_PWM7
#define PIN_PWM12               13      // AMB_D13 / PB_20 / HS_PWM12
#define PIN_PWM13               14      // AMB_D14 / PB_21 / HS_PWM13

// ============================================================================
// SWD Debug Pins
// ============================================================================
#define PIN_SWD_DATA            2       // AMB_D2 / PA_27
#define PIN_SWD_CLK             6       // AMB_D6 / PB_3

// ============================================================================
// IR Pins (opsiyonel)
// ============================================================================
#define PIN_IR_TX               7       // AMB_D7 / PA_25
#define PIN_IR_RX               8       // AMB_D8 / PA_26
