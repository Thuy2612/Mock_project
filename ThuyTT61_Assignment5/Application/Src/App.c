/*
 * App.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "App.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : App_Check_and_Pop
 * Description   : Not value return, Check Srec for line data in queue, if check
 *                 true, print ">>" in termainal, else stop program
 *
 *END**************************************************************************/

void App_Check_and_Pop(void)
{
    UART0_Init(BAUD_RATE, SREC_callBack);

    SREC_Init();
    parseStatus_t lineParse;
    uint8_t* srecLine;
    parseData_Struct_t outPutData;

    UART0_Tx_Msg("Finish\r\n");

    while(1)
    {
        if( QUEUE_checkEmpty() == QUEUE_NOT_EMPTY)
        {
            srecLine = QUEUE_Peek();
            lineParse = SREC_lineParse(srecLine, &outPutData);
            QUEUE_Pop();

            // switch(lineParse)
            // {
            //     case parseStatus_Start:
            //         UART0_Tx_Msg("Finish\r\n");
            //         break;
            //     case done:
            //         UART0_Tx_Msg("Done\r\n");
            //         break;
            //     case invalidChecksum:
            //         UART0_Tx_Msg("Error\r\n");
            //         break;
            //     default:
                    UART0_Tx_Msg(srecLine);
                    // break;

            }
        }
    }

/* **********************************************************************
 * EOF
 ***********************************************************************/
