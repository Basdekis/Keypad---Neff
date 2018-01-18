/** \file console.h
*
* \brief Console input and output with stdio.
*
* \author    Wolfgang Neff
* \version   1.1
* \date      2014-10-17
*
* \par History
*      Created: 2013-07-20 \n
*      Modified: 2014-10-17
*/

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
	#endif

	void console_init(int (*get)(FILE*),int (*put)(char, FILE*));

	#ifdef __cplusplus
}
#endif

#endif /* CONSOLE_H_ */