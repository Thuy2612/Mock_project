/*
 * Srec.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "Srec_parse.h"


static uint8_t HexConverter(uint8_t hexuint8_t);
static uint32_t LengthStr(uint8_t* str);
static uint8_t CheckS(uint8_t* str);
static uint8_t CheckType(uint8_t *str);
static uint8_t CheckChar(uint8_t *str);
static uint8_t CheckByteCount(uint8_t *str);
static uint8_t MatchChar(uint8_t num1,uint8_t num2);
static uint8_t CheckSum(uint8_t* str);
static uint8_t CheckNumberLine(uint8_t *str, uint32_t row);


/*FUNCTION**********************************************************************
 *
 * Function Name : HexConverter
 * Description   : Convert characters from HEX to DEC
 *
 *END**************************************************************************/
static uint8_t HexConverter(uint8_t hexChar)
{
    uint8_t charVal;
    if( ( hexChar >= '0' ) && ( hexChar <= '9' ) )
    {
        charVal = hexChar - '0';
    }

    if((hexChar>='A')&&(hexChar<='F'))
    {
        charVal=hexChar - 'A' + 10;
    }

    return charVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LengthStr
 * Description   : Get length of string str
 *
 *END**************************************************************************/

static uint32_t LengthStr( uint8_t* str )
{
    uint8_t i = 0;
    uint8_t count = 0;

    for( ;*(str+i) != '\n'; i++)
    {
        count ++;
    }
    return (count - 1); /* Except '\n' in file */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CheckS
 * Description   : Checking record start
 *
 *END**************************************************************************/
static uint8_t CheckS ( uint8_t* str )
{
    uint8_t check = FALSE;

    if( *str == 'S' )
    {
        check = TRUE;
    }

    return check;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CheckType
 * Description   : Checking record type- single numeric digit '0' to '9'
 *
 *END**************************************************************************/
static uint8_t CheckType( uint8_t *str )
{
    uint8_t check = FALSE;

    if( ( *(str+1)  >= '0' ) && ( *(str+1)  <= '9' ) && ( *(str+1)  != '4' ))
    {
        check= TRUE;
    }

    return check;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CheckChar
 * Description   : Checking character of string is ascii
 *
 *END**************************************************************************/
static uint8_t CheckChar(uint8_t *str)
{
    uint8_t check = FALSE;
    uint8_t i;
    uint8_t count = 0;
    uint8_t charVal;

    for( i= BYTE_COUNT_POS ; i < LengthStr(str) ; i++)
    {
        charVal = *(str+i);

        if(( (charVal>=48) && (charVal<=57) ) || ( (charVal >= 65 ) && ( charVal <= 70 ) ))  /* Check charVal ={ 0..9, A..F}*/
        {
            count++;
        }
    }

    if( CheckS(str) && CheckType(str) && ( count == LengthStr(str) - 2) )
    {
        check = TRUE;
    }
    return check;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MatchChar
 * Description   : Match two characters and convert to DEC
 *
 *END**************************************************************************/

static uint8_t MatchChar (uint8_t num1 , uint8_t num2)
{
    return( ( HexConverter(num1) << 4 ) | ( HexConverter(num2) ) );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CheckByteCount
 * Description   : Checking byte count = address + data + checksum
 *
 *END**************************************************************************/

static uint8_t CheckByteCount(uint8_t *str)
{
    uint8_t quantity;
    uint8_t count=0;
    uint8_t i;
    uint8_t check = FALSE;

    quantity = MatchChar( *(str+2) , *(str+3) );

    for( i= BYTE_COUNT_POS;  i < LengthStr(str) ; i++ )
    {
        count++;
    }
    if( (quantity * 2)== (count-2) )
    {
        check = TRUE;
    }

    return check;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : CheckSum
 * Description   : checking checksum of record structure
 *
 *END**************************************************************************/

static uint8_t CheckSum(uint8_t* str)
{
    uint32_t check = FALSE;
    uint8_t i;
    uint8_t sum = 0;
    uint8_t lengthStr;
    lengthStr = LengthStr(str);

    for( i = BYTE_COUNT_POS ; i < lengthStr ; i += 2 )
    {
        sum += MatchChar( *(str+i) , *(str+i+1) );
    }

    if( (sum & 0xFF) == 0xFF)
    {
        check = TRUE;
    }

    return check;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : CheckNumberLine
 * Description   : checking number line data with address in S5
 *
 *END**************************************************************************/


static uint8_t CheckNumberLine ( uint8_t *str , uint32_t row )
{
    uint8_t check = FALSE;
    uint8_t lengData;
    uint8_t data_index;
    uint8_t data[NUMBER_ELEMENT_MAX];
    uint8_t numData = 0;

    memset(data,0,NUMBER_ELEMENT_MAX); /* fill a block of memory with 0 */

    for(data_index = ADDRESS_POS ;data_index < LengthStr(str)-2 ; data_index++) /* Get data in S5*/
    {
        *(data + data_index - ADDRESS_POS) = *(str+data_index);
    }

    for( data_index = 0; *(data+data_index) != '\0'; data_index ++)
    {
        lengData ++;
    }

    for( data_index = 0 ; data_index <lengData ; data_index ++ ) /* Convert data in S5 to DEC */
    {
        numData |= HexConverter( *(data + data_index) ) << ( (lengData - data_index - 1) *4 );
    }

    if( numData == (row-2) )
    {
        check = TRUE;
    }

    return check;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CheckSrec
 * Description   : Checking file SREC error or error
 *
 *END**************************************************************************/
uint8_t CheckSrec( uint8_t *str , uint32_t row)
{
    uint8_t check = FALSE;

    if( CheckS(str) && CheckType(str) && CheckChar(str) && CheckByteCount(str) && CheckSum(str) )
    {
        check= TRUE;
    }

    if((*(str+1)=='5')||(*(str+1)=='6'))
    {
        if(!CheckNumberLine(str,row))
        {
            check = FALSE;
        }
    }
    return check;
}

/* **********************************************************************
 * EOF
 ***********************************************************************/
