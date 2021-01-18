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
    UART0_Init(BAUD_RATE);
    uint8_t* line_address; /* Save address of line data in queue */
    uint8_t count_line = 0; /* count number line data in srec file */
    uint8_t check_error = TRUE; /* condition to stop program*/

    UART0_Tx_Msg("Choose 'Send File' to read file\r\n");

    while(check_error == TRUE)
    {
        if( QUEUE_checkEmpty() == QUEUE_NOT_EMPTY)
        {
            line_address = QUEUE_Peek();

                if(line_address != NULL)
                {
                    count_line++;
                    if( CheckSrec( line_address, count_line))
                    {
                        UART0_Tx_Msg(">>\r\n");
                    }
                    else
                    {
                        UART0_Tx_Msg("ERROE\r\n");
                    }
                }
               QUEUE_Pop();
        }


    }


}

/* **********************************************************************
 * EOF
 ***********************************************************************/
