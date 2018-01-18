/** \file switch.h
*
* \brief Debounce active low push-buttons.
*
* \author    Wolfgang Neff
* \version   1.3
* \date      2017-12-10
*
* \par History
*      Created: 2012-11-26 \n
*      Modified: 2014-10-17 \n
*      Modified: 2015-01-27 \n
*      Modified: 2017-12-10
*/

#ifndef SWITCH_H_
#define SWITCH_H_

#include "board.h"
#include <stdint.h>

#define SWITCH0_PRESSED() debounce(&BUTTON_LOW_PORT,BUTTON0_PIN_bm,0)
#define SWITCH1_PRESSED() debounce(&BUTTON_LOW_PORT,BUTTON1_PIN_bm,1)
#define SWITCH2_PRESSED() debounce(&BUTTON_LOW_PORT,BUTTON2_PIN_bm,2)
#define SWITCH3_PRESSED() debounce(&BUTTON_LOW_PORT,BUTTON3_PIN_bm,3)
#define SWITCH4_PRESSED() debounce(&BUTTON_LOW_PORT,BUTTON4_PIN_bm,4)
#define SWITCH5_PRESSED() debounce(&BUTTON_LOW_PORT,BUTTON5_PIN_bm,5)
#define SWITCH6_PRESSED() debounce(&BUTTON_HIGH_PORT,BUTTON6_PIN_bm,6)
#define SWITCH7_PRESSED() debounce(&BUTTON_HIGH_PORT,BUTTON7_PIN_bm,7)

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>Debounces active low push-buttons.</summary>
/// <remarks>
/// This routine debounces up to eight active low push-buttons. Each key
/// needs an arbitrary key number. This routine is not thread save.
/// </remarks>
/// <param name="port">Port of the key.</param>
/// <param name="mask">Bit mask of the key.</param>
/// <param name="key">Number assigned to the key.</param>
/// <returns>True if key is pressed.</returns>
uint8_t debounce(volatile PORT_t* port, uint8_t mask, uint8_t key);

#ifdef __cplusplus
}
#endif

#endif /* SWITCH_H_ */