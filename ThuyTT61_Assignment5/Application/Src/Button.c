/*
 * Button.c
 *
 *  Created on: Jan 19, 2021
 *      Author: ThuyTT61
 */
#include "Button.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : BUTTON_Init
 * Description   : Not value return, Config PTC3 (SW1) mode GPIO - Input - Pull up
 *END**************************************************************************/

void BUTTON_Init()
{
	/* Enable clock for PORTC */
	SIM -> SCGC5 |=SIM_SCGC5_PORTC(1u);

    /* Configure Button */
    PORTC -> PCR[3] |= PORT_PCR_MUX(1u) | PORT_PCR_PE(1u) | PORT_PCR_PS(1u) | PORT_PCR_IRQC(10u); /* PTC3 mode GPIO & pull up */
    PORTC -> PCR[12] |= PORT_PCR_MUX(1u) | PORT_PCR_PE(1u) | PORT_PCR_PS(1u) | PORT_PCR_IRQC(10u); /* PTC12 mode GPIO & pull up */
    GPIOC -> PDDR	&= ~(1ul << 3); /* PTC3 mode GPIO Input*/
    GPIOC -> PDDR	&= ~ (1ul << 12); /* PTC12 mode GPIO Input*/

}

/* **********************************************************************
 * EOF
 ***********************************************************************/




