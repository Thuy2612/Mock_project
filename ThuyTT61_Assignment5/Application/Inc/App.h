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

#define BAUD_RATE                   115200ul

/* Define function pointer Reset */
typedef void(*switchToApp) (void);

/* Prototype function */
void APP_delay(uint32_t timeDelay);
bool APP_checkInvalidApp(void);
void APP_jumpToAPP(void);
void APP_loadFirmware(void);
void App_Boot(void);

#endif /* INCLUDES_APP_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
