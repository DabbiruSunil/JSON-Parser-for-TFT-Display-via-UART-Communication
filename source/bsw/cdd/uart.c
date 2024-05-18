/**
* \file uart.c
* \author P. Fromm
* \date 8.12.19
*
* \brief UART wrapper
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <string.h>

#include "uart.h"
#include "uart_cfg.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Init a Uart Port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or error code
 */
RC_t UART_init(UART_t *const me)
{
    RB_init(&me->m_rxBuffer);
    RB_init(&me->m_txBuffer);
    
    UART_start();
}

/**
 * Write a string to the UART, Using Ringbuffer and ISR
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @param uint8_t const * const s : IN - pointer to the string to be transmitted
 * @return <return description>
 */
RC_t UART_writeString(UART_t *const me, uint8_t const * const s)
{
    //Write data into ringbuffer
    uint16_t len = strlen(s);
    uint16_t capacity = RB_getCapacity(&me->m_txBuffer);
    
    if (len < capacity)
    {
        for (uint16_t i = 0; i < len; i++)
        {
            RB_write(&me->m_txBuffer, &s[i]);
        }
    
        //Initiate transfer
        //Can be optimized in terms of speed
        uint8_t firstElement = 0;
        RB_read(&me->m_txBuffer, &firstElement);
        
        //Send to driver
        //Rest will be transmitted by TX_isr;
        UART_writeByte(firstElement);
    }
    else
    {
        return RC_ERROR_MEMORY;
    }
    
    return RC_SUCCESS;
}
/**
 * Write a read to the UART, Using Ringbuffer and ISR
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @param uint8_t const * const s : OUT - pointer to the string to be received
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_readString(UART_t *const me, uint8_t const * const s)
{
   //read data from ringbuffer
    
}

/**
 * Write next char to the UART port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_TX_isrHandler(UART_t *const me)
{
    
    if (RB_getNumberOfStoredElements(&me->m_txBuffer))
    {
        uint8_t nextElement = 0;
        RB_read(&me->m_txBuffer, &nextElement);
        
        //Send to driver
        UART_writeByte(nextElement);
        
        return RC_SUCCESS;
    }
    else
    {
        //do nothing, transfer ended
        return RC_ERROR_BUFFER_EMTPY;
    }
    
}
/**
 * Read next char to the UART port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_RX_isrHandler(UART_t *const me)
{
    uint8_t data=UART_LOG_GetChar();
    
    RB_write(&me->m_rxBuffer,&data);
    
    if(data=='$')
    {
        SetEvent(tsk_json,endOfLine);
    }
    
}