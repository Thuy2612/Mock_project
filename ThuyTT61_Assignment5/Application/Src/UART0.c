/*
 * UART0.c
 *
 *  Created on: Jan 7, 2021
 *      Author: ThuyTT61
 */

#include "UART0.h"

/* Prototype Function*/
static void UART0_Tx_Char(uint8_t c_char);
static void UART0_Calculated_baud(uint32_t baudRate);

static CALL_BACK s_callBack = NULL;

/*FUNCTION**********************************************************************
 *
 * Function Name : UART0_Calculated_baud
 * Description   : Not value return, calculate value for OSR & SBR with baud rate
 *                 is defined in macro
 *
 *END**************************************************************************/
static void UART0_Calculated_baud(uint32_t baudRate)
{
    uint8_t osr;
    uint8_t sbr;
    uint8_t osr_choice;
    uint8_t sbr_choice =0;
    int32_t sub;
    uint32_t baud_cal = baudRate;
    uint32_t min = baudRate;

    for(osr = OSR_MIN; osr <= OSR_MAX; osr++)
    {
        /* the sbr value is calculated from the osr value */
        sbr = (DEFAULT_SYSTEM_CLOCK)/((osr+1)*baudRate);

        /* Recalculate the baud rate from osr and sbr */
        baud_cal = (DEFAULT_SYSTEM_CLOCK)/(sbr*(osr+1));

        /* Compare the calculated baud rate with the desired baud rate */
        sub = baudRate - baud_cal;

        /* if the variable "sub" is negative */
        if(sub < 0)
        {
            sub = -sub;
        }
        if(sub < min)
        {
            min = sub;

            /* values of osr and sbr to achieve the desired baud rate */
            osr_choice = osr;
            sbr_choice = sbr;
        }
    }

    UART0 -> C4 = osr_choice;     /* OSR = 6 */
    UART0 -> BDH &= ~UART0_BDH_SBR_MASK;
    UART0 -> BDH |= (sbr_choice >> 8) & UART0_BDH_SBR_MASK;
    UART0 -> BDL = ( sbr_choice & UART0_BDL_SBR_MASK);    /* SBR = 26 */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART0_Init
 * Description   : Not value return, Config UART0 with baud rate = 115200,
 *                 parity none, data bit =8, stop bit =1
 *
 *END**************************************************************************/
void UART0_Init(uint32_t baudRate, CALL_BACK callBack )
{
    s_callBack = callBack;
    /* Clock to UART0 MCGFLLCLK 20,971,520hz */
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1u);
    SIM->SOPT2 &= ~ SIM_SOPT2_PLLFLLSEL_MASK;


    /* Connection to UART_TX and UART_RX(Module to module interconnect) Clear bit 2,1 and 0 */
    SIM->SOPT5 &= ~SIM_SOPT5_UART0RXSRC_MASK;
    SIM->SOPT5 &= ~SIM_SOPT5_UART0TXSRC_MASK;

    /* set bit 10 for giving clock to UART0 */
    SIM->SCGC4 |= SIM_SCGC4_UART0(1u);

    /* Set bit 9 for giving clock to PORTA */
    SIM->SCGC5=SIM_SCGC5_PORTA(1u);

    /* PTA1 as UART1_RX (set bit  9 for alternative 2 which is UART0_RX) */
    PORTA->PCR[1] &= ~PORT_PCR_MUX_MASK;
    PORTA->PCR[1] |=  PORT_PCR_MUX(2u);

    /* PTA2 as UART1_RX (set bit  9 for alternative 2 which is UART0_TX) */
    PORTA->PCR[2] &= ~PORT_PCR_MUX_MASK;
    PORTA->PCR[2] |=  PORT_PCR_MUX(2u);

    /* TX and RX both disabled */
    UART0->C2 &= ~ UART0_C2_RE_MASK;
    UART0->C2 &= ~ UART0_C2_TE_MASK;

    /* Baud = 115200 */
    UART0_Calculated_baud(baudRate);

    /* Receiver and transmitter use 8-bit data characters. */
    UART0 -> C1 &= ~ UART0_C1_M_MASK;
    UART0 -> C4 &= ~ UART0_C4_M10_MASK;

    /* Parity None */
    UART0 -> C1 &= ~ UART0_C1_PE_MASK;

    /* Stop bit =1 */
    UART0 -> BDH &= ~ UART0_BDH_SBNS_MASK;

    /* choose LSB */
    UART0->S2 &= ~ UART0_S2_MSBF_MASK;

    /* Enable RX interrupt*/
    UART0->C2 |= UART0_C2_RIE(1u);

    /* TX and RX enable */
    UART0->C2 |= UART0_C2_RE_MASK | UART0_C2_TE_MASK;

   NVIC_EnableIRQ(UART0_IRQn); /* Enable NIVIC for UART0 */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART0_Tx_Char
 * Description   : Not value return, trasmitte a char to terminal
 *
 *END**************************************************************************/
static void UART0_Tx_Char(uint8_t c_char)
{
    UART0->D = c_char;
    while( (UART0->S1 & UART0_S1_TC_MASK) == 0); /* Transmission Complete Flag */

}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART0_Tx_Msg
 * Description   : Not value return, trasmitte a string to terminal
 *
 *END**************************************************************************/
void UART0_Tx_Msg(uint8_t* msg)
{
    while((*msg != '\n'))
    {
        UART0_Tx_Char(*(msg));
        msg++;
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : UART0_IRQHandler
 * Description   : Not value return, UART0 interrupt function, if queue isn't full,
 *                 push data into queue
 *END**************************************************************************/
void UART0_IRQHandler(void)
{
    uint8_t character;
    character = UART0->D;
    s_callBack(character);

}

/* **********************************************************************
 * EOF
 ***********************************************************************/



