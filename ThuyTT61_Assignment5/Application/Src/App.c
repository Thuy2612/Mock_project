/*
 * App.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "App.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : App_Boot
 * Description   : Not value return, Loading APP program.
 *                 If button is pressed -> load APP program
 *                 if button isn't pressed -> run APP program
 *
 *END**************************************************************************/


void App_Boot(void)
{
    /* Variable local */
    uint8_t index;
    parseStatus_t lineParse;
    uint8_t* srecLine;
    parseData_Struct_t outPutData;
    RESET myReset;
    uint8_t completeParse = COMPLETE_PARSE;

    UART0_Init(BAUD_RATE, SREC_callBack);
    SREC_Init();
    BUTTON_Init();

 //   UART0_Tx_Msg("Press SW1 to load APP program to Flash\r\n");

    if(!NOT_PRESS_BUTTON)
    { /* Button is pressed, load APP program in to FLASH */

        while(!NOT_PRESS_BUTTON); /* wait button unpress */

        __disable_irq(); /* Disable all interrupt and pending */
        Erase_Multi_Sector(USER_APP_START_ADDRESS, NUMBER_SECTOR_IN_FLASH); /* Erase all flash */
        __enable_irq(); /* Enable  interrupt and pending again */

        UART0_Tx_Msg("Choose 'Send File' to start program!\r\n");

        while( !completeParse)
            {
                if( !QUEUE_checkEmpty())
                {
                    srecLine = QUEUE_Peek(); /* peek line srec to handl */

                    lineParse = SREC_lineParse(srecLine, &outPutData); /* Handling line srec */

                    QUEUE_Pop(); /* increase line srec */

                    switch(lineParse)
                    {
                        case parseStatus_Start:
                            UART0_Tx_Msg("Finish\r\n");
                            break;

                        case parseStatus_Done:
                            UART0_Tx_Msg("DONE\r\n");
                            UART0_Tx_Msg( "Press Reset button to run program\r\n" );
                            completeParse = COMPLETE_PARSE; /* complete parse processing */
                            break;

                        case parseStatus_InvalidChecksum:
                        case parseStatus_InvalidSrecType:
                            UART0_Tx_Msg("Error\r\n"); /* SREC file have error */
                            break;

                        default:
                            UART0_Tx_Msg( "LOADING\r\n ");

                            for( index = 0; index < outPutData.length ; index += 4)
                            {
                                __disable_irq();

                                /* Program Address and Data (8bit pointer) into Flash Memory */
                                Program_LongWord_8B( (outPutData.address + index), (outPutData.data + index));

                                __enable_irq();
                            }

                            break;
                    }
                }
            }
    }

    else
    {
        myReset = (RESET)(*((uint32_t*)(0xA004))); /* Get RESET function address */

        __set_MSP(*(__IO uint32_t*) 0xA000); /* Set main stack pointer again */

        SCB ->VTOR = 0;
        SCB -> VTOR = (uint32_t)(0xA000); /* Load the vector table address of the user application*/
        myReset(); /* Call back RESET function */
    }


}
/* **********************************************************************
 * EOF
 ***********************************************************************/
