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

/* BW16-Kit v1.2 B&T (RTL8720DN) */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

void __libc_init_array(void);

/*
 * Pins descriptions
 *
 * PinDescription structure:
 *   - pin_name: MCU pin identifier (e.g., PA_7)
 *   - pin_type: TYPE_DIGITAL, TYPE_ANALOG, or both
 *   - pin_mode: Supported peripheral functions (GPIO, PWM, ADC, UART, I2C, SPI, IR)
 *   - pin_initial: Initial pin mode
 */
PinDescription g_APinDescription[TOTAL_GPIO_PIN_NUM] =
{
    // D0 - PA_7: LOG_UART_TX
    {PA_7,  TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_UART,                                                   MODE_NOT_INITIAL},

    // D1 - PA_8: LOG_UART_RX
    {PA_8,  TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_UART,                                                   MODE_NOT_INITIAL},

    // D2 - PA_27: SWD_DATA
    {PA_27, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ,                                                              MODE_NOT_INITIAL},

    // D3 - PA_30: LP_PWM1
    {PA_30, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM,                                                    MODE_NOT_INITIAL},

    // D4 - PB_1: LP_UART_TX (ADC not available on this board - used for UART)
    {PB_1,  TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_UART,                                                   MODE_NOT_INITIAL},

    // D5 - PB_2: LP_UART_RX (ADC not available on this board - used for UART)
    {PB_2,  TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_UART,                                                   MODE_NOT_INITIAL},

    // D6 - PB_3: ADC
    {PB_3,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ | PIO_ADC,                                                    MODE_NOT_INITIAL},

    // D7 - PA_25: LP_I2C_SCL, LP_PWM4, IR_TX
    {PA_25, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM | PIO_IR | PIO_I2C,                                 MODE_NOT_INITIAL},

    // D8 - PA_26: LP_I2C_SDA, LP_PWM5, IR_RX
    {PA_26, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM | PIO_IR | PIO_I2C,                                 MODE_NOT_INITIAL},

    // D9 - PA_15: SPI1_CS
    {PA_15, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_SPI,                                                    MODE_NOT_INITIAL},

    // D10 - PA_14: SPI1_CLK
    {PA_14, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_SPI,                                                    MODE_NOT_INITIAL},

    // D11 - PA_13: SPI1_MISO, LP_PWM1
    {PA_13, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM | PIO_SPI,                                          MODE_NOT_INITIAL},

    // D12 - PA_12: SPI1_MOSI, LP_PWM0, SWD_CLK
    {PA_12, TYPE_DIGITAL,               PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM | PIO_SPI,                                          MODE_NOT_INITIAL}
};

void *gpio_pin_struct[TOTAL_GPIO_PIN_NUM] = {NULL};
void *gpio_irq_handler_list[TOTAL_GPIO_PIN_NUM] = {NULL};

#ifdef __cplusplus
} // extern C
#endif

void serialEvent() __attribute__((weak));
bool Serial_available() __attribute__((weak));

// ----------------------------------------------------------------------------

void serialEventRun(void)
{
    if (Serial_available && serialEvent && Serial_available()) serialEvent();
}

void init(void)
{
    // Initialize C library
    __libc_init_array();
}

// ----------------------------------------------------------------------------

void wait_for_debug(void) {
    while (((CoreDebug->DHCSR) & CoreDebug_DHCSR_C_DEBUGEN_Msk) == 0) {
        asm("nop");
    }
    delay(1000);
}
