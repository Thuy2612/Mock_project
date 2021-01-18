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
/* Define Macro for Queue.h */
#define NUMBER_LINE_IN_QUEUE_MAX            4u
#define START_INDEX_LINE_IN_QUEUE           0u
#define NUMBER_CHAR_IN_LINE_MAX             80u
#define START_INDEX_CHAR_IN_LINE            0u
#define QUEUE_EMPTY                         1u
#define QUEUE_NOT_EMPTY                     0u
#define QUEUE_FULL                          1u
#define QUEUE_NOT_FULL                      0u

/* Prototype function */
uint8_t QUEUE_checkEmpty(void);
uint8_t QUEUE_checkFull(void);
void QUEUE_Push(void);
void QUEUE_Pop(void);
uint8_t* QUEUE_Peek(void);
uint8_t* QUEUE_getFreeElement(void);

#endif /* INCLUDES_QUEUE_H_ */

/***********************************************************************
 * EOF
 ***********************************************************************/
