/*
 * Queue.h
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#ifndef INCLUDES_QUEUE_H_
#define INCLUDES_QUEUE_H_

#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

/* Define Macro for Queue.h */
#define NUMBER_LINE_IN_QUEUE_MAX            4u
#define START_INDEX_LINE_IN_QUEUE           0u
#define NUMBER_CHAR_IN_LINE_MAX             518u
#define START_INDEX_CHAR_IN_LINE            0u


/* Prototype function */
void QUEUE_Init(void);
bool QUEUE_checkEmpty(void);
bool QUEUE_checkFull(void);
void QUEUE_Push(void);
void QUEUE_Pop(void);
uint8_t* QUEUE_Peek(void);
uint8_t* QUEUE_getFreeElement(void);

#endif /* INCLUDES_QUEUE_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
