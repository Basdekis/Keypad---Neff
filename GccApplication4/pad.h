/** \file pad.h
*
* \brief This module implements a 4x4 keypad driver.
*
* This file defines the pin mapping for the 74HC237 3-to-8 line decoder with address latches.
*
* \author    Wolfgang Neff
* \version   1.0
* \date      2016-07-12
*
* \par History
*      Created: 2016-07-12
*/

#ifndef PAD_H_
#define PAD_H_

#define PAD_COLS 4
#define PAD_ROWS 4

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>Initialize keypad.</summary>
/// <remarks>
/// Initializes the ports for the keypad and activates the
/// pulldown resistors.
/// </remarks>
void pad_init(void);

/// <summary>Scan keypad.</summary>
/// <remarks>
/// Scans the keypad and returns the state of the keys. The
/// state of the sixteen keys encoded as a sixteen bit integer.
/// </remarks>
/// <returns>The state of the keys.</returns>
uint16_t pad_scan(void);

/// <summary>Return newly pressed keys.</summary>
/// <param name="current">Current state of the keys.</param>
/// <param name="previous">Previous state of the keys.</param>
/// <returns>Keys newly pressed since the last scan.</returns>
uint16_t pad_pressed(uint16_t current, uint16_t previous);

/// <summary>Return newly released keys.</summary>
/// <param name="current">Current state of the keys.</param>
/// <param name="previous">Previous state of the keys.</param>
/// <returns>Keys newly released since the last scan.</returns>
uint16_t pad_released(uint16_t current, uint16_t previous);

#ifdef __cplusplus
}
#endif

#endif /* PAD_H_ */