/*
 * Queue.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "Queue.h"

static uint8_t queue[NUMBER_LINE_IN_QUEUE_MAX][NUMBER_CHAR_IN_LINE_MAX];
static uint8_t line_pushIndex;
static uint8_t line_popIndex;

void QUEUE_Init(void)
{
    line_pushIndex = START_INDEX_LINE_IN_QUEUE;
    line_popIndex = START_INDEX_LINE_IN_QUEUE;

}
uint8_t QUEUE_checkEmpty(void)
{
    uint8_t checkEmpty = QUEUE_NOT_EMPTY;
    if(line_popIndex == line_pushIndex)
    {
        checkEmpty = QUEUE_EMPTY;
    }
    return checkEmpty;
}

uint8_t QUEUE_checkFull(void)
{
    uint8_t checkFull = QUEUE_NOT_FULL;
    if( ((line_popIndex == 0) && (line_pushIndex == 4)) ||( (line_pushIndex - line_popIndex) == 1 ))
    {
        checkFull = QUEUE_FULL;
    }

    return checkFull;
}

uint8_t* QUEUE_Peek(void)
{
    uint8_t* ptr_peekAddress = NULL;

        ptr_peekAddress = queue[line_pushIndex];

    return ( ptr_peekAddress );
}

uint8_t* QUEUE_getFreeElement(void)
{
    uint8_t* ptr_freeSpace = NULL;
        ptr_freeSpace = queue[line_popIndex];

    return ptr_freeSpace;
}

void QUEUE_Push(void)
{
    line_pushIndex++;
    line_pushIndex = line_pushIndex % NUMBER_LINE_IN_QUEUE_MAX;
}

void QUEUE_Pop(void)
{
    line_popIndex++;
    line_popIndex = line_popIndex % NUMBER_LINE_IN_QUEUE_MAX;
}
