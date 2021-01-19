/*
 * Queue.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "Queue.h"

/* Variable static globle */
static uint8_t s_queue[NUMBER_LINE_IN_QUEUE_MAX][NUMBER_CHAR_IN_LINE_MAX];
static uint8_t s_line_pushIndex;
static uint8_t s_line_popIndex;

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_Init
 * Description   : Not value return
 *END**************************************************************************/

void QUEUE_Init(void)
{
    s_line_pushIndex = START_INDEX_LINE_IN_QUEUE;
    s_line_popIndex = START_INDEX_LINE_IN_QUEUE;

}
/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_checkEmpty
 * Description   : Return TRUE if queue empty, return false if not empty
 *END**************************************************************************/

uint8_t QUEUE_checkEmpty(void)
{
    uint8_t checkEmpty = QUEUE_NOT_EMPTY;
    if(s_line_popIndex == s_line_pushIndex)
    {
        checkEmpty = QUEUE_EMPTY;
    }
    return checkEmpty;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_checkFull
 * Description   : Return TRUE if queue full, return false if not full
 *END**************************************************************************/

uint8_t QUEUE_checkFull(void)
{
    uint8_t checkFull = QUEUE_NOT_FULL;
    if( ((s_line_popIndex == 0) && (s_line_pushIndex == 4)) ||( (s_line_pushIndex - s_line_popIndex) == 1 ))
    {
        checkFull = QUEUE_FULL;
    }

    return checkFull;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_Peek
 * Description   : Return address of line srec have data to handl
 *END**************************************************************************/

uint8_t* QUEUE_Peek(void)
{
    uint8_t* ptr_peekAddress = NULL;

        ptr_peekAddress = s_queue[s_line_popIndex];

    return ( ptr_peekAddress );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_getFreeElement
 * Description   : Return address of line srec free to push data into queue
 *END**************************************************************************/

uint8_t* QUEUE_getFreeElement(void)
{
    uint8_t* ptr_freeSpace = NULL;
        ptr_freeSpace = s_queue[s_line_pushIndex];

    return ptr_freeSpace;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_Push
 * Description   : Not value return, increase line push index
 *END**************************************************************************/

void QUEUE_Push(void)
{
    s_line_pushIndex++;
    s_line_pushIndex = s_line_pushIndex % NUMBER_LINE_IN_QUEUE_MAX;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_Pop
 * Description   : Not value return, increase line pop index
 *END**************************************************************************/

void QUEUE_Pop(void)
{
    s_line_popIndex++;
    s_line_popIndex = s_line_popIndex % NUMBER_LINE_IN_QUEUE_MAX;
}

/* **********************************************************************
 * EOF
 ***********************************************************************/
