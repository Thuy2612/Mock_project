/*
 * Srec.c
 *
 *  Created on: Jan 10, 2021
 *      Author: ThuyTT61
 */

#include "Srec_parse.h"

uint8_t *ptr_put = NULL;

static uint8_t SREC_ConvertChar2Hex(unsigned char Hexchar);


/*FUNCTION**********************************************************************
 *
 * Function Name : SREC_Init
 * Description   : No value return, get address start of queue
 *END**************************************************************************/

void SREC_Init(void)
{
    ptr_put = QUEUE_getFreeElement();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SREC_ConvertChar2Hex
 * Description   : Return uint8_t, convert from character to hex
 *END**************************************************************************/

static uint8_t SREC_ConvertChar2Hex(unsigned char Hexchar)
{
  if((Hexchar>='A')&&(Hexchar<='F'))
  Hexchar = Hexchar - 'A' +10;
  else Hexchar =Hexchar-48;
  return Hexchar;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SREC_lineParse
 * Description   : Return parseStatus_t, get status of parse process
 *END**************************************************************************/

parseStatus_t SREC_lineParse(uint8_t *srecLine, parseData_Struct_t *outPutData)
{
    parseStatus_t status = parseStatus_Error;
    uint8_t srecType = 0;
    uint8_t byteCount = 0;
    uint8_t checkSum = 0;
    uint16_t dataOffset = 4u;
    uint16_t dataIndex = 0;
    uint8_t dataTpm = 0;
    uint8_t numberAddressByte = 0;
    uint32_t address = 0;

    if ('S' == srecLine[0])
    {
        /* Get srecord type */
        srecType = SREC_ConvertChar2Hex(srecLine[1]);
        /* Get byte count */
        byteCount = (uint8_t)((SREC_ConvertChar2Hex(srecLine[2]) << 4) \
                                        | (SREC_ConvertChar2Hex(srecLine[3])));
        checkSum = byteCount;
        /* Parst */
        switch (srecType)
        {
            case 0:
                status = parseStatus_Start;
                break;
            case 1:
            case 2:
            case 3:
                numberAddressByte = srecType + 1;
                status = parseStatus_Inprogress;
                break;
            case 4:
                status = parseStatus_InvalidSrecType;
                break;
            case 5:
            case 6:
                status = parseStatus_Optional;
                break;
            case 7:
            case 8:
            case 9:
                numberAddressByte = 11 - srecType;
                status = parseStatus_Done;
                break;
            default:
                status = parseStatus_InvalidSrecType;
                break;
        }

        /* Get address */
        for (dataIndex = 0; dataIndex < numberAddressByte; dataIndex++)
        {
            dataTpm = SREC_ConvertChar2Hex(srecLine[dataOffset]) << 4 \
                               | SREC_ConvertChar2Hex(srecLine[dataOffset + 1]);
            address = (address << 8) | dataTpm;
            dataOffset += 2;
            checkSum += dataTpm;
        }
        outPutData->address = address;
        outPutData->length = byteCount - numberAddressByte - 1;
        /* Get data */
        for (dataIndex = 0; dataIndex < outPutData->length; dataIndex++)
        {
            dataTpm = SREC_ConvertChar2Hex(srecLine[dataOffset]) << 4 \
                               | SREC_ConvertChar2Hex(srecLine[dataOffset + 1]);
            outPutData->data[dataIndex] = dataTpm;
            dataOffset += 2;
            checkSum += dataTpm;
        }
        /* Calculator checksum */
        dataTpm = SREC_ConvertChar2Hex(srecLine[dataOffset]) << 4 \
                               | SREC_ConvertChar2Hex(srecLine[dataOffset + 1]);
        checkSum += dataTpm;

        if (0xFF != checkSum)
        {
            status = parseStatus_InvalidChecksum;
        }
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : SREC_lineParse
 * Description   : No value return, call bcak funtion to push data into QUEUE
 *END**************************************************************************/

void SREC_callBack(uint8_t character)
{
    static uint8_t dataIndex = 0;

    ptr_put[dataIndex] = character;

    if( ptr_put[dataIndex] == '\n')
    {
        dataIndex = 0;
        QUEUE_Push();
        ptr_put = QUEUE_getFreeElement();
    }
    else
    {
        dataIndex ++;
    }
}
/* **********************************************************************
 * EOF
 ***********************************************************************/
