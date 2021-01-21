/*
 * App.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "App.h"

/* Define macro for App.h */

#define USER_APP_START_ADDRESS      (0xA000u)
#define USER_APP_STOP_ADDRESS       (0x3FFFFu)
#define USER_APP_START_RESET        (0xA004)
#define NUMBER_BYTE_IN_SECTOR       1024u
#define NUMBER_SECTOR_IN_FLASH      ((USER_APP_STOP_ADDRESS - USER_APP_START_ADDRESS)/ NUMBER_BYTE_IN_SECTOR)
#define COMPLETE_PARSE              0u
#define INVALID_U32                 0xFFFFFFFF

static void APP_EraseFlash(void);

/*FUNCTION**********************************************************************
 *
 * Function Name : APP_delay
 * Description   : Not value return, creat time delay with time = timeDelay
 *
 *END**************************************************************************/

void APP_delay( uint32_t timeDelay)
{
    while(timeDelay--);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : APP_checkInvalidApp
 * Description   : Not value return, check Flash don't have data
 *
 *END**************************************************************************/

bool APP_checkInvalidApp(void)
{
    bool checkInvalid = false;

    if( *(uint32_t*)(USER_APP_START_ADDRESS) == INVALID_U32)
    {
        checkInvalid = true;
    }
    return checkInvalid;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : APP_EraseFlash
 * Description   : Not value return, Erase all sector in Flash
 *
 *END**************************************************************************/

static void APP_EraseFlash(void)
{
    __disable_irq(); /* Disable all interrupt and pending */
    Erase_Multi_Sector(USER_APP_START_ADDRESS, NUMBER_SECTOR_IN_FLASH); /* Erase all flash */
    __enable_irq(); /* Enable  interrupt and pending again */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : APP_loadFirmware
 * Description   : Not value return, load app program into flash
 *
 *END**************************************************************************/

void APP_loadFirmware(void)
{
    /* Variable local */
    uint8_t index;
    parseStatus_t lineParse;
    uint8_t* srecLine;
    parseData_Struct_t outPutData;

    APP_EraseFlash();
    UART0_Tx_Msg( "Press 'Send file' to get data\r\n ");
    while(true)
    {
        srecLine = QUEUE_Peek(); /* peek line srec to handl */

        if( srecLine != NULL)
        {
            lineParse = SREC_lineParse(srecLine, &outPutData); /* Handling line srec */

            QUEUE_Pop(); /* increase line srec */

            switch(lineParse)
            {
                case parseStatus_Start:
                    UART0_Tx_Msg("Start parse\r\n");
                    break;

                case parseStatus_Done:
                    UART0_Tx_Msg("Complete parse\r\n");
                    UART0_Tx_Msg( "Press Reset button to run APP\r\n" );
                    //completeParse = COMPLETE_PARSE; /* complete parse processing */
                    break;

                case parseStatus_InvalidChecksum:
                case parseStatus_InvalidSrecType:
                    UART0_Tx_Msg("Error\r\n"); /* SREC file have error */
                    break;

                case parseStatus_Inprogress:
                    UART0_Tx_Msg( "...\r\n ");

                    for( index = 0; index < outPutData.length ; index += 4)
                    {
                        __disable_irq();

                        /* Program Address and Data (8bit pointer) into Flash Memory */
                        Program_LongWord_8B( (outPutData.address + index), \
                                             (outPutData.data + index));

                        __enable_irq();
                    }

                    break;

                default:
                    break;
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : APP_jumpToAPP
 * Description   : Not value return, jump to Reset function of APP and run APP 
 *                 program
 *
 *END**************************************************************************/

void APP_jumpToAPP(void)
{
    switchToApp switchAPP;

    switchAPP = (switchToApp)(*((uint32_t*)(USER_APP_START_RESET))); /* Get RESET function address */

    __set_MSP(*(__IO uint32_t*) USER_APP_START_ADDRESS); /* Set main stack pointer again */

    SCB -> VTOR = (uint32_t)(0xA000); /* Load the vector table address of the user application*/
    switchAPP(); /* Call back RESET function */
}

/* **********************************************************************
 * EOF
 ***********************************************************************/
