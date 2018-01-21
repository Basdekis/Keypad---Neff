

#include <avr/io.h>
#include <util/delay.h>
#include "board.h"
#include "switch.h"
#include "pad.h"
#include "usart.h"
#include "console.h"


int main(void)
{

	LED_PORT.DIR = LED0_PIN_bm;
 //
	//BUTTON0_PINCTRL = PORT_OPC_PULLUP_gc;
	//BUTTON1_PINCTRL = PORT_OPC_PULLUP_gc;
	//BUTTON2_PINCTRL = PORT_OPC_PULLUP_gc;
	//BUTTON3_PINCTRL = PORT_OPC_PULLUP_gc;
//
	//USB_USART_PORT.OUT |= USB_USART_TX_PIN_bm;                   
	//USB_USART_PORT.DIR |= USB_USART_TX_PIN_bm;                  
	//USB_USART_PORT.DIR &= ~USB_USART_RX_PIN_bm;                 
//
	//
	//
	//USB_USART_MODULE.BAUDCTRLA = 11;
	//USB_USART_MODULE.BAUDCTRLB = (-7<<USART_BSCALE_gp);
	//
	//USB_USART_MODULE.CTRLC = (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc);
	//
	//USB_USART_MODULE.CTRLB = (USART_RXEN_bm | USART_TXEN_bm);
	
	usart_init();
	console_init(usart_getc, usart_putc);

	int keyPressed = 0;
	
	/*
				4	3	2	1
				
			8	1   2   3   A
			7	4	5	6	B
			6	7	8	9	C
			5	*	0	#	D
				
			1 - GPIO 3
			2 - GPIO 2
			3 - GPIO 1
			4 - GPIO 0
			
			5 - GPIO 7
			6 - GPIO 6
			7 - GPIO 5
			8 - GPIO 4
	
	*/
	
	
	
	while(1)
	{
		//if (!(BUTTON_LOW_PORT.IN & BUTTON0_PINCTRL)) {  
			//while(!(USB_USART_MODULE.STATUS & USART_DREIF_bm));  
			//USB_USART_MODULE.DATA = pad_scan();
		//}
		
		//printf("%04x", pad_scan());
		
		printf("B"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(pad_scan()));
		
		printf("\n");
		_delay_ms(100);
	}
}


