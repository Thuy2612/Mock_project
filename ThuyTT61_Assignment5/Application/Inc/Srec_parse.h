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
    parseStatus_Start = 0x00 ,
    parseStatus_Inprogress = 0x01,
    parseStatus_InvalidSrecType =0x02,
    parseStatus_Optional =0x03,
    parseStatus_Done =0x04,
    parseStatus_InvalidChecksum =0x05,
    parseStatus_Error =0x06
}parseStatus_t;

/* Prototype Function */
void SREC_Init(void);
void SREC_callBack(uint8_t character);
parseStatus_t SREC_lineParse(uint8_t *srecLine, parseData_Struct_t *outPutData);

#endif /* INCLUDES_SREC_PARSE_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
