/*
 * Srec_parse.h
 *
 *  Created on: Jan 10, 2021
 *      Author: Admin
 */

#ifndef INCLUDES_SREC_PARSE_H_
#define INCLUDES_SREC_PARSE_H_

#include <stdbool.h>
#include <stdint.h>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

/* Define type parseData_Struct_t */
typedef struct
{
    uint8_t data[256];
    uint16_t length;
    uint32_t address;
}parseData_Struct_t;

/* Define type parseStatus_t*/
typedef enum parstStatus_t
{
    parseStatus_Start,
    parseStatus_Inprogress,
    parseStatus_InvalidSrecType,
    parseStatus_Optional,
    parseStatus_Done,
    parseStatus_InvalidChecksum,
    parseStatus_Error
}parseStatus_t;

/* Prototype Function */
void SREC_Init(void);
void SREC_callBack(uint8_t character);

#endif /* INCLUDES_SREC_PARSE_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
