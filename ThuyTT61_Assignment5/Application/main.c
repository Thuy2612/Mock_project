#include "App.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : Main
 * Description   : Loading APP program.
 *                 If button is pressed or not data in flash -> boot program
 *                 if button isn't pressed -> run APP program
 *
 *END**************************************************************************/
int main()
{
    UART0_Init(BAUD_RATE, SREC_callBack);
    SREC_Init();
    BUTTON_Init();

    APP_delay(100000);

    UART0_Tx_Msg("Press SW1 to load APP program to Flash\r\n");

    if((!NOT_PRESS_BUTTON) || ( APP_checkInvalidApp() ))
    { /* Button is pressed, load APP program in to FLASH */

        while(!NOT_PRESS_BUTTON); /* wait button unpress */

        APP_loadFirmware();
    }

    else
    {
        APP_jumpToAPP();
    }
}

/* **********************************************************************
 * EOF
 ***********************************************************************/
