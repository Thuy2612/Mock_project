/*
 * Button.h
 *
 *  Created on: Jan 19, 2021
 *      Author: ThuyTT61
 */

#ifndef INCLUDES_BUTTON_H_
#define INCLUDES_BUTTON_H_

#include "MKL46Z4.h"

/* Define macro for Button.h */
#define NOT_PRESS_BUTTON        (GPIOC->PDIR & (1ul << 3u))

/* Prototype function */
void BUTTON_Init();

#endif /* INCLUDES_BUTTON_H_ */
/* **********************************************************************
 * EOF
 ***********************************************************************/
