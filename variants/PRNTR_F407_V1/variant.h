/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
*/

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
extern const PinName digitalPin[];

//P1 connector Right side
#define PC0  0
#define PC2  1  // A0
#define PA0  2
#define PA2  3
#define PA4  4
#define PA6  5
#define PC4  6  // A1
#define PB0  7  // A2
#define PB2  8
#define PE8  9
#define PE10 10
#define PE12 11
#define PE14 12
#define PB10 13
#define PB12 14
#define PB14 15
#define PD8  16
#define PD10 17
#define PD12 18
#define PD14 19
//P2 connector Left side
#define PH0  20
#define PC14 21
#define PE6  22
#define PE4  23
#define PE2  24
#define PE0  25
#define PB8  26
#define PB6  27
#define PB4  28
#define PD7  29
#define PD5  30
#define PD3  31
#define PD1  32
#define PC12 33
#define PC10 34
#define PA10 35
#define PA8  36
#define PC8  37
#define PC6  38
//P1 Connector Left Side
#define PC1  39 // A3
#define PC3  40 // A4
#define PA1  41 // A5
#define PA3  42
#define PA5  43
#define PA7  44
#define PC5  45 // A6
#define PB1  46 // A7
#define PE7  47
#define PE9  48
#define PE11 49
#define PE13 50
#define PE15 51
#define PB11 52
#define PB13 53
#define PB15 54
#define PD9  55
#define PD11 56
#define PD13 57
#define PD15 58
//P2 connector Right side
#define PH1  59
#define PC15 60
#define PC13 61
#define PE5  62
#define PE3  63
#define PE1  64
#define PB9  65
#define PB7  66
#define PB5  67
#define PB3  68
#define PD6  69
#define PD4  70
#define PD2  71
#define PD0  72
#define PC11 73
#define PA15 74
#define PA13 75
#define PA9  76
#define PC9  77
#define PC7  78

// This must be a literal
#define NUM_DIGITAL_PINS        87
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       8
#define NUM_ANALOG_FIRST        79

// On-board LED pin number
#define LED_BUILTIN             PD12
#define LED_GREEN               LED_BUILTIN
#define LED_BLUE                PD15
#define LED_RED                 PD14
#define LED_ORANGE              PD13

// On-board user button
#define USER_BTN                2

// SPI Definitions
#define PIN_SPI_SS2             14
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            5
#define PIN_SPI_SCK             PA5

// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB8

// Timer Definitions
// Do not use timer used by PWM pin. See PinMap_PWM.
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    2 //Connected to ST-Link

// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA3
#define PIN_SERIAL_TX           PA2

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR     Serial
#define SERIAL_PORT_HARDWARE    Serial1
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
