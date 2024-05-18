/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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
#include "circularRingbuffer.h"


RC_t circularRingbuffer_init(circularRingbuffer_t* ringbuffer, uint16_t size){
    // Initiliaze with 0.
    ringbuffer->read_idx = 0; 
    ringbuffer->write_idx = 0; 
    ringbuffer->filllevel = 0;
    
    if(size == 0){
        return RC_ERROR_ZERO; 
    }
    
    ringbuffer->size = size;
    
    // allocate memory
    ringbuffer->data = (uint8_t*)malloc(size * sizeof(uint8_t));
    
    // fill ringbuffer with default character
    for(int i=0; i<(ringbuffer->size); i++){
        ringbuffer->data[i] = ' '; 
    }
    
    return RC_SUCCESS; 
}


RC_t circularRingbuffer_read(circularRingbuffer_t* ringbuffer, uint8_t* data){
    // Read from the ringbuffer. 
    *data = ringbuffer->data[ringbuffer->read_idx]; 
    
    // Increment read index
    ringbuffer->read_idx = ringbuffer->read_idx + 1;
    ringbuffer->read_idx %= ringbuffer->size;
    
    // Decrease filllevel
    ringbuffer->filllevel= ringbuffer->filllevel - 1; 
    
    return RC_SUCCESS; 
}


RC_t circularRingbuffer_write(circularRingbuffer_t* ringbuffer, uint8_t data){
    // Read from the ringbuffer
    ringbuffer->data[ringbuffer->write_idx] = data; 
    
    // Inrement write index
    ringbuffer->write_idx = ringbuffer ->write_idx + 1;
    ringbuffer->write_idx %= ringbuffer->size;
    
    // Increase filllevel. 
    ringbuffer->filllevel = ringbuffer->filllevel + 1; 
    
    return RC_SUCCESS; 
}


RC_t circularRingbuffer_clear(circularRingbuffer_t* ringbuffer){
    // Fill the ringbuffer with default values
    for(int i = 0; i<(ringbuffer->size); i++){
        ringbuffer->data[i] = 0x00; 
    }
    
    return RC_SUCCESS; 
}

RC_t circularRingbuffer_UART_print(circularRingbuffer_t* ringbuffer){
    // Get filllevel
    uint8_t amountOfData = ringbuffer->filllevel; 
    
    // Print the elements of the ringbuffer 
    for(uint8_t i = 0; i<amountOfData; i++){
        UART_LOG_PutChar(ringbuffer->data
            [(ringbuffer->read_idx)+i]); 
    }
    
    return RC_SUCCESS; 
}

RC_t circularRingbuffer_checkForChar(circularRingbuffer_t* ringbuffer, uint8_t searchValue, uint8_t* numberOfFoundValues){
    // Get filllevel and set found values to zero
    uint8_t length = ringbuffer->filllevel; 
    *numberOfFoundValues = 0; 
    
    // Increment found values if char is found
    for(uint8_t i = 0; i<length; i++){
        if(ringbuffer->data
            [(ringbuffer->read_idx)+i] == searchValue){
                *numberOfFoundValues += 1; 
            }
    }
    return RC_SUCCESS; 
}