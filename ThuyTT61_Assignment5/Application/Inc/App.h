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
typedef void(*switchToApp) (void);

/* Define macro for App.h */


/* Prototype function */
void App_Boot(void);

#endif /* INCLUDES_APP_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
