/** \file board.h
*
* \brief Header file for the XMEGA-A1 Xplained evaluation board.
*
* This header provides constants for the following components on the board:
*
* * \ref header
* * \ref gpio
* * \ref leds
* * \ref buttons
* * \ref gateway
* * \ref light
* * \ref temperature
* * \ref speaker
* * \ref oscillators
*
* \author    Wolfgang Neff
* \version   1.6
* \date      2017-04-04
*
* \par History
*      Created: 2013-07-16 \n
*      Modified: 2013-07-24 \n
*      Modified: 2015-01-27 \n
*      Modified: 2016-06-11 \n
*      Modified: 2016-11-26 \n
*      Modified: 2017-06-04 \n
*      Modified: 2017-08-04
*
* \note
*      **USB:** Parameter for the USART-to-USB gateway: 115200 8N1. \n
*      **F_CPU:** Default 2000000. Use default or set it via Project/Properties/Toolchain/Compiler/Symbols. \n
*      **FreeROTS:** TCC1 used as tick generator. Default: 1000 low level interrupts ticks per second.
*/

#ifndef XMEGA_A1_XPLAINED_H_
#define XMEGA_A1_XPLAINED_H_

/** @defgroup header Header configuration
 <summary>Pin assignment of the I/O header.</summary>
@{
 | Pin | Communication Port | Analog Port      | GPIO Port         | Communication Port        |
 |-----|------------------- | -----------------|-------------------|---------------------------|
 |     |  <B>Jumper J1</B>  | <B>Jumper J2</B> | <B>Jumper: J3</B> | <B>Jumper: J4</B>         |
 |  1  |  PF0 (SDA/RTS)     | PA0 (ADC/AREF)   | PD0 (GPIO)        | PC0 (SDA/RTS/PWM/CAPTURE) |
 |  2  |  PF1 (SCL/CTS/XCK) | PA1 (ADC)        | PD1 (GPIO)        | PC1 (SCL/CTS/PWM/CAPTURE) |
 |  3  |  PF2 (RXD)         | PA2 (ADC/DAC)    | PD2 (GPIO)        | PC2 (RXD/PWM/CAPTURE)     |
 |  4  |  PF3 (TXD)         | PA3 (ADC/DAC)    | PD3 (GPIO)        | PC3 (TXD/PWM/CAPTURE)     |
 |  5  |  PF4 (SS)          | PA4 (ADC/AC_P)   | PD4 (GPIO)        | PC4 (SS/PWM/CAPTURE)      |
 |  6  |  PF5 (MOSI)        | PA5 (ADC/AC_N)   | PD5 (GPIO)        | PC5 (MOSI/PWM/CAPTURE)    |
 |  7  |  PF6 (MISO)        | PA6 (ADC/AC_P)   | PR0 (GPIO)        | PC6 (MISO/PWM)            |
 |  8  |  PF7 (SCK)         | PA7 (ADC/AC_N)   | PR1 (GPIO)        | PC7 (SCK/PWM)             |
 |  9  |  GND               | GND              | GND               | GND                       |
 | 10  |  VCC_P3V3          | VCC_ANA_P3V3     | VCC_USB_VBUS_P5V0 | VCC_P3V3                  |
@} */

/** @defgroup gpio GPIO
 <summary>Constants for the GPIO port.</summary>
 <remarks>
 Jumper J3 is used for GPIO. \n
 __Note:__ buttons and GPIO share the same port.
 </remarks>
@{ */
/****** General-purpose input/output ******/
#define GPIO_LOW_PORT PORTD
#define GPIO_HIGH_PORT PORTR
#define GPIO_LOW_PINS_gp 0
#define GPIO_LOW_PINS_gm 0x3F
#define GPIO_HIGH_PINS_gp 6
#define GPIO_HIGH_PINS_gm 0xC0

#define GPIO_PIN0_bp PIN0_bp
#define GPIO_PIN1_bp PIN1_bp
#define GPIO_PIN2_bp PIN2_bp
#define GPIO_PIN3_bp PIN3_bp
#define GPIO_PIN4_bp PIN4_bp
#define GPIO_PIN5_bp PIN5_bp
#define GPIO_PIN6_bp PIN0_bp
#define GPIO_PIN7_bp PIN1_bp

#define GPIO_PIN0_bm PIN0_bm
#define GPIO_PIN1_bm PIN1_bm
#define GPIO_PIN2_bm PIN2_bm
#define GPIO_PIN3_bm PIN3_bm
#define GPIO_PIN4_bm PIN4_bm
#define GPIO_PIN5_bm PIN5_bm
#define GPIO_PIN6_bm PIN0_bm
#define GPIO_PIN7_bm PIN1_bm

#define GPIO_PIN0CTRL GPIO_LOW_PORT.PIN0CTRL
#define GPIO_PIN1CTRL GPIO_LOW_PORT.PIN1CTRL
#define GPIO_PIN2CTRL GPIO_LOW_PORT.PIN2CTRL
#define GPIO_PIN3CTRL GPIO_LOW_PORT.PIN3CTRL
#define GPIO_PIN4CTRL GPIO_LOW_PORT.PIN4CTRL
#define GPIO_PIN5CTRL GPIO_LOW_PORT.PIN5CTRL
#define GPIO_PIN6CTRL GPIO_HIGH_PORT.PIN0CTRL
#define GPIO_PIN7CTRL GPIO_HIGH_PORT.PIN1CTRL

/// \def GPIO_READ()
/// <summary>Read all GPIO pins</summary>
#define GPIO_READ() ((GPIO_LOW_PORT.IN & GPIO_LOW_PINS_gm) | ((GPIO_HIGH_PORT.IN << GPIO_HIGH_PINS_gp) & GPIO_HIGH_PINS_gm))

/// \def GPIO_WRITE(VAL)
/// <summary>Set all GPIO pins</summary>
/// <param name="VAL">The new value for the pins.</param>
#define GPIO_WRITE(VAL) GPIO_LOW_PORT.OUT = (VAL) & GPIO_LOW_PINS_gm; GPIO_HIGH_PORT.OUT = (((VAL) & GPIO_HIGH_PINS_gm) >> GPIO_HIGH_PINS_gp);
/// @}

/** @defgroup leds LEDs
 <summary>Constants for the active low LEDs.</summary>
 <remarks>
 There are eight active low LEDs on the board. Please
 consult the schematic for details. 
 \verbatim
  VCC_P3V3
     +
     |
     V -> EL17-21UYC/A2
     -
     |
     |
    .-.
    | | 220R
    | |
    '-'
     |
     |
 PE[7..0]
 \endverbatim
 </remarks>
@{ */
/****** Active low LEDs ******/
#define LED_PORT PORTE
#define LED_PINS_gp 0
#define LED_PINS_gm 0xFF

#define LED0_PIN_bp PIN0_bp
#define LED1_PIN_bp PIN1_bp
#define LED2_PIN_bp PIN2_bp
#define LED3_PIN_bp PIN3_bp
#define LED4_PIN_bp PIN4_bp
#define LED5_PIN_bp PIN5_bp
#define LED6_PIN_bp PIN6_bp
#define LED7_PIN_bp PIN7_bp

#define LED0_PIN_bm PIN0_bm
#define LED1_PIN_bm PIN1_bm
#define LED2_PIN_bm PIN2_bm
#define LED3_PIN_bm PIN3_bm
#define LED4_PIN_bm PIN4_bm
#define LED5_PIN_bm PIN5_bm
#define LED6_PIN_bm PIN6_bm
#define LED7_PIN_bm PIN7_bm
/// @}

/** @defgroup buttons Buttons
 <summary>Constants for the active low push buttons.</summary>
 <remarks>
 There are eight active push buttons on the board. They are
 connected with jumper J3.  Please consult the schematic for
 details. 
 \verbatim
  Header J3
     |
    .-.
    | | 330R
    | |
    '-'
     |
     |
   | o
 |=|>
   | o
     |
     |
    ===
    GND
 \endverbatim
 </remarks>
@{ */ 
/****** Active low push buttons ******/
#define BUTTON_LOW_PORT PORTD
#define BUTTON_HIGH_PORT PORTR
#define BUTTON_LOW_PINS_gp 0
#define BUTTON_LOW_PINS_gm 0x3F
#define BUTTON_HIGH_PINS_gp 6
#define BUTTON_HIGH_PINS_gm 0xC0

#define BUTTON0_PIN_bp PIN0_bp
#define BUTTON1_PIN_bp PIN1_bp
#define BUTTON2_PIN_bp PIN2_bp
#define BUTTON3_PIN_bp PIN3_bp
#define BUTTON4_PIN_bp PIN4_bp
#define BUTTON5_PIN_bp PIN5_bp
#define BUTTON6_PIN_bp PIN0_bp
#define BUTTON7_PIN_bp PIN1_bp

#define BUTTON0_PIN_bm PIN0_bm
#define BUTTON1_PIN_bm PIN1_bm
#define BUTTON2_PIN_bm PIN2_bm
#define BUTTON3_PIN_bm PIN3_bm
#define BUTTON4_PIN_bm PIN4_bm
#define BUTTON5_PIN_bm PIN5_bm
#define BUTTON6_PIN_bm PIN0_bm
#define BUTTON7_PIN_bm PIN1_bm

#define BUTTON0_PINCTRL BUTTON_LOW_PORT.PIN0CTRL
#define BUTTON1_PINCTRL BUTTON_LOW_PORT.PIN1CTRL
#define BUTTON2_PINCTRL BUTTON_LOW_PORT.PIN2CTRL
#define BUTTON3_PINCTRL BUTTON_LOW_PORT.PIN3CTRL
#define BUTTON4_PINCTRL BUTTON_LOW_PORT.PIN4CTRL
#define BUTTON5_PINCTRL BUTTON_LOW_PORT.PIN5CTRL
#define BUTTON6_PINCTRL BUTTON_HIGH_PORT.PIN0CTRL
#define BUTTON7_PINCTRL BUTTON_HIGH_PORT.PIN1CTRL

/// \def BUTTONS_READ()
/// <summary>Read all push buttons</summary>
#define BUTTONS_READ() ((BUTTON_LOW_PORT.IN & BUTTON_LOW_PINS_gm) | ((BUTTON_HIGH_PORT.IN << BUTTON_HIGH_PINS_gp) & BUTTON_HIGH_PINS_gm))

/// \def BUTTON_PRESSED(BUTTON)
/// <summary>Check if push button is pressed</summary>
/// <param name="BUTTON">Number of button to be checked.</param>
#define BUTTON_PRESSED(BUTTON) (!(BUTTONS_READ() & (1 << BUTTON)))
/// @}

/** @defgroup gateway Gateway
 <summary>Constants for the USART-to-USB gateway.</summary>
 <remarks>
 USARTC0 is connected with a USART-to-USB gateway.
 The configuration for the gateway is: 115200 8N1.
 </remarks>
@{ */
/****** USART-to-USB gateway ******/
#define USART0_RX_PIN_bm PIN2_bm
#define USART0_TX_PIN_bm PIN3_bm
#define USART1_RX_PIN_bm PIN6_bm
#define USART1_TX_PIN_bm PIN7_bm

#define USB_USART_PORT PORTC
#define USB_USART_MODULE USARTC0
#define USB_USART_RX_PIN_bm USART0_RX_PIN_bm
#define USB_USART_TX_PIN_bm USART0_TX_PIN_bm
#define USB_USART_RXC_vect USARTC0_RXC_vect
#define USB_USART_DRE_vect USARTC0_DRE_vect

#define USB_USART_BAUDRATE 115200
#define USB_USART_CONFIG (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc)
/// @}

/****** Sensors ******/
#define SENSOR_PORT PORTB
#define SENSOR_ADC_MODULE ADCB

/** @defgroup light Light sensor
 <summary>Constants for the light sensor.</summary>
 <remarks>
 There is an ambient light sensor on the board.
 Darkness provides higher voltages. Please consult
 the schematic for details. 
 \verbatim
    VCC_P3V3
       +
       |
      .-.
      | | 100k
      | |
      '-'
       |
       o--- Lightsensor
       |
 ->  |/
    -|   Phototransistor
 ->  |>  TEMT6000
       |
       |
      ===
      GND
 \endverbatim
 </remarks>
@{ */ 
/****** Light sensor ******/
#define LIGHT_SENSOR_SIGNAL_PIN_bp PIN1_bp
#define LIGHT_SENSOR_SIGNAL_PIN_bm PIN1_bm
#define LIGHT_SENSOR_ADC_INPUT ADC_CH_MUXPOS_PIN1_gc
/// @}

/** @defgroup temperature Temperature sensor
 <summary>Constants for the temperature sensor.</summary>
 <remarks>
 There is a voltage divider with an NTC on the board. It is
 used as temperature sensor. It has an active low enable input
 and lower voltages for higher temperatures. Please consult
 the schematic for details. 
 \verbatim
 VCC_P3V3
    +
    |
   .-.
   | | 1M
   | |
   '-'
    |
    o---- NTC_TEMP
    |
   .-.
   | |<-- NCP18WF104J03RB
   | |
   '-'
    |
    '---- NTC_EN
 \endverbatim
 </remarks>
@{ */ 
/****** Temperature sensor ******/
#define TEMPERATURE_SENSOR_SIGNAL_PIN_bp PIN0_bp
#define TEMPERATURE_SENSOR_SIGNAL_PIN_bm PIN0_bm
#define TEMPERATURE_SENSOR_ENABLE_PIN_bp PIN3_bp
#define TEMPERATURE_SENSOR_ENABLE_PIN_bm PIN3_bm
#define TEMPERATURE_SENSOR_ADC_INPUT ADC_CH_MUXPOS_PIN0_gc
/// @}

/** @defgroup speaker Speaker
 <summary>Constants for the speaker.</summary>
 <remarks>
 There is a speaker on the board. It has an active low
 shutdown input. Please consult the schematic for details.
 \verbatim
               1u       TPA0253DGQR
               ||   ___     __
 AUDIO_OUT  ---||--|___|--o|  |      .---|
               ||   30k    |  |o-----|   |
                           |  |o-----|   |
 AUDIO_SD    --------o----o|__|      '---|
                     |              NDT-03C
                    .-.
                    | | 100k
                    | |
                    '-'
                     |
                     |
                    ===
                    GND
 \endverbatim
 </remarks>
@{ */ 
/****** Speaker ******/
#define SPEAKER_SIGNAL_PORT PORTB
#define SPEAKER_SIGNAL_PIN_bp PIN2_bp
#define SPEAKER_SIGNAL_PIN_bm PIN2_bm
#define SPEAKER_SHUTDOWN_PORT PORTQ
#define SPEAKER_SHUTDOWN_PIN_bp PIN3_bp
#define SPEAKER_SHUTDOWN_PIN_bm PIN3_bm
#define SPEAKER_DAC_MODULE DACB
#define SPEAKER_DAC_CHANNEL 0
/// @}

/** @defgroup oscillators Oscillators
 <summary>Constants for the oscillators.</summary>
@{ */
/****** Internal oscillator ******/
#define OSC_INTERNAL_2HZ 2000000L
#define OSC_INTERNAL_32HZ 32000000L

/****** Default oscillator ******/
#define OSC_DEFAULT_HZ OSC_INTERNAL_2HZ

/****** F_CPU ******/
#ifndef F_CPU
#define F_CPU OSC_INTERNAL_2HZ
#warning "F_CPU initialized with default value"
#endif
/// @}

#endif /* XMEGA_A1_XPLAINED_H_ */
