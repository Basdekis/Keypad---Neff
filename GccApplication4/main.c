

#include <avr/io.h>
#include <util/delay.h>
#include "board.h"
#include "switch.h"


int main(void)
{




	LED_PORT.DIR = LED0_PIN_bm;
 
	BUTTON0_PINCTRL = PORT_OPC_PULLUP_gc;
	BUTTON1_PINCTRL = PORT_OPC_PULLUP_gc;
	BUTTON2_PINCTRL = PORT_OPC_PULLUP_gc;
	BUTTON3_PINCTRL = PORT_OPC_PULLUP_gc;

	USB_USART_PORT.OUT |= USB_USART_TX_PIN_bm;                   
	USB_USART_PORT.DIR |= USB_USART_TX_PIN_bm;                   
	USB_USART_PORT.DIR &= ~USB_USART_RX_PIN_bm;                  

	
	USB_USART_MODULE.BAUDCTRLA = 11;
	USB_USART_MODULE.BAUDCTRLB = (-7<<USART_BSCALE_gp);
	
	USB_USART_MODULE.CTRLC = (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc);
	
	USB_USART_MODULE.CTRLB = (USART_RXEN_bm | USART_TXEN_bm);

	int keyPressed = 0;
	while(1)
	{
		if (!(BUTTON_LOW_PORT.IN & BUTTON0_PINCTRL)) {  
			while(!(USB_USART_MODULE.STATUS & USART_DREIF_bm));  
			USB_USART_MODULE.DATA = 0x32;
		}
	}
}


