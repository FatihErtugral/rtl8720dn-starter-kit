/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* NICEMCU_8720_v1 (RTL8720DN) */

#ifndef _VARIANT_ARDUINO_AMEBA_
#define _VARIANT_ARDUINO_AMEBA_

#include "Arduino.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C"{
#include "PinNames.h"

#define portOutputRegister(P) ((volatile uint32_t *)(0x48014000 + (P) * 0x400))
#define portInputRegister(P)  ((volatile uint32_t *)(0x48014050 + (P) * 0x400))
#define portModeRegister(P)   ((volatile uint32_t *)(0x48014004 + (P) * 0x400))

/*
 * Wait until enter debug mode
 *
 * Check DHCSR(0xE000EDF0) register and hold until bit C_DEBUGEN is set.
 * Use this function along with J-LINK or other debug tool
 **/
extern void wait_for_debug(void);
}
#endif

#define MAIN_THREAD_STACK_SIZE                  (4096 * 4)

#define TOTAL_GPIO_PIN_NUM                      (15)
#define TOTAL_PWM_PIN_NUM                       (7)

#define digitalPinToInterrupt(p)    (((p)<TOTAL_GPIO_PIN_NUM)?(p):-1)

/* Digital pin mapping refer to g_APinDescription */
#define AMB_D0                                  0  // PA_7  - LOG_TX
#define AMB_D1                                  1  // PA_8  - LOG_RX
#define AMB_D2                                  2  // PA_27 - SWD_DATA
#define AMB_D3                                  3  // PA_30 - PWM7
#define AMB_D4                                  4  // PB_1  - LP_UART_RX, ADC4
#define AMB_D5                                  5  // PB_2  - LP_UART_TX, ADC5
#define AMB_D6                                  6  // PB_3  - ADC6, SWD_CLK
#define AMB_D7                                  7  // PA_25 - I2C_SCL, PWM4
#define AMB_D8                                  8  // PA_26 - I2C_SDA, PWM5
#define AMB_D9                                  9  // PA_15 - SPI_CS
#define AMB_D10                                 10 // PA_14 - SPI_CLK, LED_B
#define AMB_D11                                 11 // PA_13 - SPI_MISO, PWM1, LED_G
#define AMB_D12                                 12 // PA_12 - SPI_MOSI, PWM0, LED_R
#define AMB_D13                                 13 // PB_20 - HS_I2C_SCL, PWM12
#define AMB_D14                                 14 // PB_21 - HS_I2C_SDA, PWM13

/* Pin name aliases */
#define PA7                                     AMB_D0
#define PA8                                     AMB_D1
#define PA27                                    AMB_D2
#define PA30                                    AMB_D3
#define PB1                                     AMB_D4
#define PB2                                     AMB_D5
#define PB3                                     AMB_D6
#define PA25                                    AMB_D7
#define PA26                                    AMB_D8
#define PA15                                    AMB_D9
#define PA14                                    AMB_D10
#define PA13                                    AMB_D11
#define PA12                                    AMB_D12
#define PB20                                    AMB_D13
#define PB21                                    AMB_D14

/* Analog pin mapping */
#define A0                                      AMB_D4  // PB_1 3.3V ADC4
#define A1                                      AMB_D5  // PB_2 3.3V ADC5
#define A2                                      AMB_D6  // PB_3 3.3V ADC6

/* LED pin mapping (active low on board) */
#define LED_R                                   AMB_D12 // PA_12 Red
#define LED_G                                   AMB_D11 // PA_13 Green
#define LED_B                                   AMB_D10 // PA_14 Blue
#define LED_BUILTIN                             LED_G   // Green as default

/* ADC/DAC pin mapping */
#define FEATURE_ADC
//#define FEATURE_DAC

/* SPI pin mapping */
#define SPI_MOSI                                AMB_D12 // PA_12
#define SPI_MISO                                AMB_D11 // PA_13
#define SPI_SCLK                                AMB_D10 // PA_14
#define SPI_SS                                  AMB_D9  // PA_15

/* Arduino style SPI pin mapping */
static const uint8_t SS = SPI_SS;
static const uint8_t MOSI = SPI_MOSI;
static const uint8_t MISO = SPI_MISO;
static const uint8_t SCK = SPI_SCLK;

/* TwoWire/I2C pin mapping (LP_I2C - default) */
#define I2C_SDA                                 AMB_D8  // PA_26
#define I2C_SCL                                 AMB_D7  // PA_25

/* TwoWire/I2C pin mapping (HS_I2C - secondary) */
#define I2C1_SDA                                AMB_D14 // PB_21
#define I2C1_SCL                                AMB_D13 // PB_20

/* IR Device pin mapping */
#define IR_TX                                   AMB_D7  // PA_25
#define IR_RX                                   AMB_D8  // PA_26

/* UART pin mapping */
#define LOG_UART_MODIFIABLE_BAUD_RATE           1
#define SERIAL_ONE_UART_MODIFIABLE_BAUD_RATE    1
#define SERIAL_TWO_UART_MODIFIABLE_BAUD_RATE    1
#define LOG_TX                                  AMB_D0  // PA_7  UART_LOG_TX
#define LOG_RX                                  AMB_D1  // PA_8  UART_LOG_RX
#define SERIAL1_TX                              AMB_D5  // PB_2  LP_UART_TX
#define SERIAL1_RX                              AMB_D4  // PB_1  LP_UART_RX

/* SWD pin mapping */
#define SWD_DATA                                AMB_D2  // PA_27
#define SWD_CLK                                 AMB_D6  // PB_3

#endif /* _VARIANT_ARDUINO_AMEBA_ */
