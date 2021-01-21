/*
 * Queue.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "Queue.h"


/* Define Macro for Queue.h */
#define NUMBER_LINE_IN_QUEUE_MAX            4u
#define START_INDEX_LINE_IN_QUEUE           0u
#define NUMBER_CHAR_IN_LINE_MAX             518u
#define START_INDEX_CHAR_IN_LINE            0u


/* Variable static globle */
static uint8_t s_queue[NUMBER_LINE_IN_QUEUE_MAX][NUMBER_CHAR_IN_LINE_MAX];
static uint8_t s_queue_pushIndex = START_INDEX_LINE_IN_QUEUE;
static uint8_t s_queue_popIndex = START_INDEX_LINE_IN_QUEUE;
static uint8_t s_queue_level =0;

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_checkEmpty
 * Description   : Return TRUE if queue empty, return false if not empty
 *END**************************************************************************/

bool QUEUE_checkEmpty(void)
{
    uint8_t checkEmpty = false;
    if( s_queue_level == 0)
    {
        checkEmpty = true;
    }
    return checkEmpty;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_checkFull
 * Description   : Return TRUE if queue full, return false if not full
 *END**************************************************************************/

bool QUEUE_checkFull(void)
{
    uint8_t checkFull = false;
    if( s_queue_level == NUMBER_LINE_IN_QUEUE_MAX)
    {
        checkFull = true;
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

    if( !QUEUE_checkEmpty())
    {
        ptr_peekAddress = s_queue[s_queue_popIndex];
    }

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

    if( !QUEUE_checkFull() )
    {
        ptr_freeSpace = s_queue[s_queue_pushIndex];
    }

    return ptr_freeSpace;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_Push
 * Description   : Not value return, increase line push index
 *END**************************************************************************/

void QUEUE_Push(void)
{
    if( !QUEUE_checkFull() )
    {
        s_queue_pushIndex++;
        s_queue_level ++;
        s_queue_pushIndex = s_queue_pushIndex % NUMBER_LINE_IN_QUEUE_MAX;
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUEUE_Pop
 * Description   : Not value return, increase line pop index
 *END**************************************************************************/

void QUEUE_Pop(void)
{
    if( !QUEUE_checkEmpty() )
    {
        s_queue_popIndex++;
        s_queue_level--;
        s_queue_popIndex = s_queue_popIndex % NUMBER_LINE_IN_QUEUE_MAX;
    }

}

/* **********************************************************************
 * EOF
 ***********************************************************************/
