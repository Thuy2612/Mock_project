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
typedef struct
{
    uint8_t data[256];
    uint16_t length;
    uint32_t address;
}parseData_Struct_t;

typedef enum parstStatus_t
{
    parseStatus_Start,
    parseStatus_Inprogress,
    invalidSrecType,
    optional,
    done,
    invalidChecksum,
    parseStatus_Error
}parseStatus_t;

void SREC_Init(void);
parseStatus_t SREC_lineParse(uint8_t *srecLine, parseData_Struct_t *outPutData);

void SREC_callBack(uint8_t character);

#endif /* INCLUDES_SREC_PARSE_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
