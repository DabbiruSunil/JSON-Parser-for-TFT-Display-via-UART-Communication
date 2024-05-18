/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef CIRCULARRINGBUFFER_H
#define CIRCULARRINGBUFFER_H
    
#include <project.h>
#include "global.h"
    
typedef struct{
    uint16_t size;       /**< Size of the buffer. */
    uint16_t read_idx;    /**< Next to be read element. */
    uint16_t write_idx;  /**< Next free byte to write. */
    uint16_t filllevel; 
    uint8_t* data;      /**< Pointer to buffe with length size. */
} circularRingbuffer_t; 

/**
* \brief Init the Ringbuffer. 
*/
RC_t circularRingbuffer_init(circularRingbuffer_t* ringbuffer, uint16_t size); 

/**
* \brief Read from the Ringbuffer.
*/
RC_t circularRingbuffer_read(circularRingbuffer_t* ringbuffer, uint8_t* data); 

/**
* \brief Write into the Ringbuffer.
*/
RC_t circularRingbuffer_write(circularRingbuffer_t* ringbuffer, uint8_t data); 

/**
* \brief Clear the Ringbuffer.
*/
RC_t circularRingbuffer_clear(circularRingbuffer_t* ringbuffer); 

/**
* \brief Print the Ringbuffer.
*/
RC_t circularRingbuffer_UART_print(circularRingbuffer_t* ringbuffer); 

/**
* \brief Checks for specific char in ringbuffer.
*/
RC_t circularRingbuffer_checkForChar(circularRingbuffer_t* ringbuffer, uint8_t searchValue, uint8_t* numberOfFoundValues); 

#endif
/* [] END OF FILE */


