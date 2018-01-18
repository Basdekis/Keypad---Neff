/*
 * usart.c
 *
 * Version: 1.2
 * Created: 2012-09-03
 * Modified: 2014-10-17
 * Modified: 2015-01-28
 *  Author: Wolfgang Neff
 */ 

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "board.h"
#include "usart.h"

#define LIMIT ((1<<(USART_BSEL_BITS+1))-1)
#define USART_ERROR_CODE ((USART_MODULE.STATUS & 0x001C) << 6)

#ifndef F_CPU
#error "uart.c requires F_CPU to be defined"
#endif

void usart_init(void)
{
    int bsel, bscale, clk2x;
	USART_PORT.DIRSET = USART_TX_PIN_bm;
	USART_PORT.DIRCLR = USART_RX_PIN_bm;
	USART_MODULE.CTRLC = ( USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc);
	usart_params(F_CPU,USART_STD_BAUDRATE,&bsel,&bscale,&clk2x);
	USART_MODULE.BAUDCTRLA = bsel & USART_BSEL_gm;
	USART_MODULE.BAUDCTRLB = (bscale<<USART_BSCALE_gp) | ((bsel>>8) & ~USART_BSCALE_gm);
	USART_MODULE.CTRLB = (USART_RXEN_bm | USART_TXEN_bm | ((clk2x) ? USART_CLK2X_bm : 0));
}

int usart_receive(void)
{
	if (!(USART_MODULE.STATUS & USART_RXCIF_bm)) return USART_NO_DATA;
	return USART_ERROR_CODE | USART_MODULE.DATA;
}

int usart_transmit(char c)
{
	if (!(USART_MODULE.STATUS & USART_DREIF_bm)) return USART_BUSY;
	USART_MODULE.DATA = c;
	return USART_SUCCESS;
}

int usart_getc(FILE *stream)
{
	return usart_getchar();
}

int usart_getchar(void)
{
    char data;
	while (!(USART_MODULE.STATUS & USART_RXCIF_bm));
	data = USART_MODULE.DATA;
	return USART_ERROR_CODE | (data=='\r') ? '\n' : data;
}

int usart_putc(char c, FILE *stream)
{
	return usart_putchar(c);
}

int usart_putchar(char c)
{
	if (c == '\n') usart_putchar('\r');
	while (!(USART_MODULE.STATUS & USART_DREIF_bm));
	USART_MODULE.DATA = c;
	return USART_SUCCESS;
}

int usart_puts(const char *s)
{
    while (*s) usart_putchar(*s++);
	return USART_SUCCESS;
}

int usart_puts_P(const char *s)
{
    while (pgm_read_byte(s)) usart_putchar(pgm_read_byte(s++));
	return USART_SUCCESS;
}

int usart_bsel(long freq, long baud, int bscale, int clk2x)
{
	long num, denom;
	if (clk2x==0 && bscale>=0) {
		num = (freq/10)-(16*baud*(1<<bscale)/10);
		denom = 16*baud*(1<<bscale)/100;
	}
	else if (clk2x==0 && bscale<0) {
		num = (1<<-bscale)*(freq/10-16*baud/10);
		denom = 16*baud/100;
	}
	else if (clk2x==1 && bscale>=0) {
		num = (freq/10)-(8*baud*(1<<bscale)/10);
		denom = 8*baud*(1<<bscale)/100;
	}
	else if (clk2x==1 && bscale<0) {
		num = (1<<-bscale)*(freq/10-8*baud/10);
		denom = 8*baud/100;
	}
	#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	return (num<0 || denom==0) ? -1 : (num/denom+5)/10;
	#pragma GCC diagnostic warning "-Wmaybe-uninitialized"
}

long usart_baud(long freq, int bsel, int bscale, int clk2x)
{
	long num, denom;
	if (clk2x==0 && bscale>=0) {
		num = freq/(1<<bscale)*10;
		denom = 16*(bsel+1);
	}
	else if (clk2x==0 && bscale<0) {
		num = freq/16*(1<<-bscale)*10;
		denom = bsel+(1<<-bscale);
	}
	else if (clk2x==1 && bscale>=0) {
		num = freq/(1<<bscale)*10;
		denom = 8*(bsel+1);
	}
	else if (clk2x==1 && bscale<0) {
		num = freq/8*(1<<-bscale)*10;
		denom = bsel+(1<<-bscale);
	}
	#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	return (num<0 || denom==0) ? -1 : (num/denom+5)/10;
	#pragma GCC diagnostic warning "-Wmaybe-uninitialized"
}

int usart_params(long freq, long baud, int* bsel, int* bscale, int* clk2x)
{
	int error;
	if (baud > freq/16) {
		*bsel = -1;
		return 1000;
	}
	for (*clk2x=1;*clk2x>=0;(*clk2x)--) {
		for (*bscale=-7;*bscale<8;(*bscale)++) {
			*bsel = usart_bsel(freq,baud,*bscale,*clk2x);
			if (-1<*bsel && *bsel<LIMIT) goto found;
		}
	}
	found:
	error = 1000*(usart_baud(freq,*bsel,*bscale,*clk2x)-baud)/baud;
	*bsel = (*bsel>LIMIT || error>USART_BAUD_TOLERANCE) ? -1 : *bsel;
	return error;
}
