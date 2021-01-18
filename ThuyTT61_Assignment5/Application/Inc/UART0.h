/*
 * UART0.h
 *
 *  Created on: Jan 7, 2021
 *      Author: ThuyTT61
 */

#ifndef INCLUDES_UART0_H_
#define INCLUDES_UART0_H_

#include "MKL46Z4.h"
#include "stdio.h"

/* Define Macro for UART.h*/

#define MCGFLLCLK       20971520ul
#define OSR_MIN         3u
#define OSR_MAX         31u

typedef void (*CALL_BACK)(uint8_t character);
/* Prototype function */

void UART0_Init(uint32_t baudRate, CALL_BACK callBack );
void UART0_Tx_Msg(uint8_t* msg);



#endif /* INCLUDES_UART0_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
