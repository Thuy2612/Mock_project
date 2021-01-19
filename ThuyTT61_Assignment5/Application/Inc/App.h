/*
 * App.h
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#ifndef INCLUDES_APP_H_
#define INCLUDES_APP_H_

#include "Srec_parse.h"
#include "UART0.h"
#include "Flash.h"
#include "Button.h"

/* Define function pointer Reset */
typedef void(*RESET) (void);

/* Define macro for App.h */
#define BAUD_RATE       115200ul
#define USER_APP_START_ADDRESS      (0xA000u)
#define USER_APP_STOP_ADDRESS       (0x3FFFFu)
#define NUMBER_BYTE_IN_SECTOR       1024u
#define NUMBER_SECTOR_IN_FLASH      ((USER_APP_STOP_ADDRESS - USER_APP_START_ADDRESS)/ NUMBER_BYTE_IN_SECTOR)
#define COMPLETE_PARSE              0u

/* Prototype function */
void App_Boot(void);

#endif /* INCLUDES_APP_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
