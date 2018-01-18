/*
 * console.c
 *
 * Version: 1.1
 * Created: 2013-07-20
 * Modified: 2014-10-17
 *  Author: Wolfgang Neff
 */ 

#include "console.h"

static FILE console_in = FDEV_SETUP_STREAM(NULL, NULL, _FDEV_SETUP_READ);
static FILE console_out = FDEV_SETUP_STREAM(NULL, NULL, _FDEV_SETUP_WRITE);


void console_init(int (*get)(FILE*),int (*put)(char, FILE*))
{
	console_in.get = get;
	console_out.put = put;
	if (get) {
    	stdin  = &console_in;
	}
	if (put) {
	    stderr = &console_out;
	    stdout = &console_out;
	}
}