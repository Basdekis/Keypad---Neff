/** \file usart.h
*
* \brief This module implements an RS-232 based serial communication.
*
* \author    Wolfgang Neff
* \version   1.2
* \date      2015-01-28
*
* \par History
*      Created: 2012-09-03 \n
*      Modified: 2014-10-17 \n
*      Modified: 2015-01-28
*/

#ifndef USART_H_
#define USART_H_

#include <stdio.h>

#define USART_STD_BAUDRATE 115200

#define USART_PORT USB_USART_PORT
#define USART_MODULE USB_USART_MODULE
#define USART_RX_PIN_bp USB_USART_RX_PIN_bp
#define USART_RX_PIN_bm USB_USART_RX_PIN_bm
#define USART_TX_PIN_bp USB_USART_TX_PIN_bp
#define USART_TX_PIN_bm USB_USART_TX_PIN_bm
#define USART_RXC_vect USB_USART_RXC_vect
#define USART_DRE_vect USB_USART_DRE_vect

#define USART_FRAME_ERROR   0x0400    /* Framing Error by USART     */
#define USART_OVERRUN_ERROR 0x0200    /* Overrun condition by USART */
#define USART_PARITIY_ERROR 0x0100    /* Parity Error by USART      */
#define USART_BUSY          0x8000    /* Transmitter is busy        */
#define USART_NO_DATA       0x4000    /* No data received           */
#define USART_SUCCESS       0x0000    /* Operation succeeded        */
#define USART_ERROR(code) (code & 0xFF00)

#define USART_BSEL_BITS 12
#define USART_BAUD_TOLERANCE 20

#ifdef __cplusplus
extern "C"
{
	#endif

	/// <summary>Initialize USART.</summary>
	/// <remarks>
	/// Initializes the USART port for a serial communication via the RS-232
	/// protocol with the given standard baud rate and parameter 8N1.
	/// </remarks>
	void usart_init(void);

	/* Asynchronous functions */

	/// <summary>Receive asynchronously a byte.</summary>
	/// <remarks>
	/// Checks if new data has been received. If yes, it is returned
	/// together with a possible error code. If no, USART_NO_DATA is.
	/// returned.
	/// </remarks>
	/// </example><code>
	/// int data = usart_receive();
	/// if (data != USART_NO_DATA) {
	///     uint8_t byte = data;
	///     int status = USART_ERROR(data);
	///     if (status != USART_SUCCESS) {
	///         /// Error handling
	///     }
	/// }
	/// </code></example>
	/// <returns>Received data or USART_NO_DATA if there is none.</returns>
	int usart_receive(void);

	/// <summary>Transmit asynchronously a byte.</summary>
	/// <remarks>
	/// Checks if the USART is ready to transmit new data. If yes, it is
	/// transmited and USART_SUCCESS is returned. If no, USART_BUSY is
	/// returned.
	/// </remarks>
	/// <returns>
	/// USART_SUCCESS if the data has been transmitted or USART_BUSY otherwise.
	/// </returns>
	int usart_transmit(char c);

	/* Synchronous functions */

	/// <summary>Receive synchronously a byte.</summary>
	/// <remarks>
	/// Waits until a byte has been received. Then returns the bye together
	/// with a possible error code.
	/// </remarks>
	/// <returns>Received data.</returns>
	int usart_getchar(void);

	/// <summary>Receive synchronously a byte.</summary>
	/// <remarks>
	/// Same as <c>usart_getchar</c>. Used by <c>console</c> module.
	/// </remarks>
	/// <param name="stream">A dummy argument.</param>
	/// <returns>Received data.</returns>
	int usart_getc(FILE *stream);

	/// <summary>Transmit synchronously a byte.</summary>
	/// <remarks>
	/// Waits until a byte has been transmited and returns USART_SUCCESS.
	/// </remarks>
	/// <param name="c">The data to be transmitted.</param>
	/// <returns>USART_SUCCESS after the data has been transmitted.</returns>
	int usart_putchar(char c);

	/// <summary>Transmit synchronously a byte.</summary>
	/// <remarks>
	/// Same as <c>usart_putchar</c>. Used by <c>console</c> module.
	/// </remarks>
	/// <param name="c">The data to be transmitted.</param>
	/// <param name="stream">A dummy argument.</param>
	/// <returns>USART_SUCCESS after the data has been transmitted.</returns>
	int usart_putc(char c, FILE *stream);

	/// <summary>Transmit synchronously a string.</summary>
	/// <param name="s">The string to be transmitted.</param>
	/// <returns>USART_SUCCESS after the string has been transmitted.</returns>
	int usart_puts(const char *s);

	/// <summary>Transmit synchronously a string.</summary>
	/// <remarks>
	/// Same as <c>usart_puts</c> but works with strings stored in PROGMEM.
	/// </remarks>
	/// </example><code>
	/// #include <avr/pgmspace.h>
	/// const char message1[] PROGMEM = "This is message one.\n"
	/// usart_puts_P(message1);
	/// usart_puts_P(PSTR("This is message two.\n"));
	/// </code></example>
	/// <param name="s">The string to be transmitted.</param>
	/// <returns>USART_SUCCESS after the string has been transmitted.</returns>
	int usart_puts_P(const char *s);

	/* Auxiliary functions */

	/// <summary>Calculate BSEL.</summary>
	/// <remarks>
	/// Calculates the corresponding value for BSEL for a given F_CPU, baud
	/// rate, BSCALE and clock rate.
	/// </remarks>
	/// <param name="freq">The given value of F_CPU.</param>
	/// <param name="baud">The desired baud rate.</param>
	/// <param name="bscale">The desired value for BSCALE.</param>
	/// <param name="clk2x">Indicates if clock rate should be doubled.</param>
	/// <returns>The value of BESL to get the desired baud rate.</returns>
	int usart_bsel(long freq, long baud, int bscale, int clk2x);

	/// <summary>Calculate baud rate.</summary>
	/// <remarks>
	/// Calculates the resulting baud rate for a given F_CPU, BSEL, BSCALE and
	/// clock rate.
	/// </remarks>
	/// <param name="freq">The given value of F_CPU.</param>
	/// <param name="bsel">The given value of BSEL.</param>
	/// <param name="bscale">The given value of BSCALE.</param>
	/// <param name="clk2x">Indicates if clock rate should be doubled.</param>
	/// <returns>The resulting baud rate for the given parameters.</returns>
	long usart_baud(long freq, int bsel, int bscale, int clk2x);

	/// <summary>Calculate BSEL, BSCALE and clock rate.</summary>
	/// <remarks>
	/// Determines the the best values for BSEL, BSCALE and CLK2X for a given
	/// F_CPU and baud rate. Sets BSEL to -1 if no valid value can be found
	/// or if the resulting baud rate lies outside the given tolerance of
	/// USART_BAUD_TOLERANCE which is specified in per mill.
	/// </remarks>
	/// <param name="freq">The given value of F_CPU.</param>
	/// <param name="baud">The desired baud rate.</param>
	/// <param name="bsel">The resulting value for BSEL.</param>
	/// <param name="bscale">The resulting value for BSCALE.</param>
	/// <param name="clk2x">The resulting value for CLK2X.</param>
	/// <returns>
	/// The deviation of resulting baud rate from the given baud rate
	/// in per mill.
	/// </returns>
	int usart_params(long freq, long baud, int* bsel, int* bscale, int* clk2x);

	#ifdef __cplusplus
}
#endif

#endif /* USART_H_ */