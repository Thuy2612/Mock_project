/*
 * Srec_parse.h
 *
 *  Created on: Jan 10, 2021
 *      Author: Admin
 */

#ifndef INCLUDES_SREC_PARSE_H_
#define INCLUDES_SREC_PARSE_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Define Macro for Srec_parse.h*/
#define TRUE                        1u
#define FALSE                       0u
#define BYTE_COUNT_POS              2u
#define ADDRESS_POS                 4u
#define NUMBER_ELEMENT_MAX          80u

/* Prototype function */

uint8_t CheckSrec( uint8_t *str , uint32_t row);
#endif /* INCLUDES_SREC_PARSE_H_ */

/* **********************************************************************
 * EOF
 ***********************************************************************/
