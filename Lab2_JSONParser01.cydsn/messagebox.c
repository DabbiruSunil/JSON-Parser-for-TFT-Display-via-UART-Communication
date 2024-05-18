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
#include "messagebox.h"

RC_t messagebox_init(messagebox_t* messagebox, uint16_t size, EventMaskType eventMaskType, TaskType taskType){
    // Initiliaze attributes
    messagebox->m_size = size;
    messagebox->m_ev = eventMaskType; 
    messagebox->m_task = taskType; 
    messagebox->filllevel = 0; 
    messagebox->read_idx = 0; 
    messagebox->write_idx = 0; 
    
    return RC_SUCCESS; 
}

RC_t messagebox_send(messagebox_t* messagebox, void* data, uint16_t size){
    // Check size
    if(messagebox->m_size >= POSTBOX_SIZE){
        //UART_LOG_PutString("MESSAGEBOX SEND FAILED!"); 
        return RC_ERROR_BUFFER_FULL; 
    }
    
    // Allocate memory
    void* pMalloc = malloc(size * sizeof(uint8_t));
    
    // Return if not successful
    if(pMalloc == NULL){
        //UART_LOG_PutString("MESSAGEBOX SEND FAILED!"); 
        return RC_ERROR_MEMORY; 
    }
    
    // Write pointer to Buffer of message
    messagebox->message[messagebox->write_idx].m_pBuffer = pMalloc;
    
    // Cast the pointers
    uint8_t *castedPointer = (uint8_t*)data;
    uint8_t *castedMpBuffer = (uint8_t*)messagebox->message[messagebox->write_idx].m_pBuffer;
    
    // Write data into m_pBuffer
    for (int it_size = 0; it_size< size; it_size++)
    {
        castedMpBuffer[it_size] = castedPointer[it_size];
    }
    
    // Increment size and write index
    messagebox->message[messagebox->write_idx].m_size = size;
    messagebox->write_idx = messagebox->write_idx +1;
    messagebox->write_idx = messagebox->write_idx % POSTBOX_SIZE;
    messagebox->filllevel = messagebox->filllevel +1;
    
    SetEvent(messagebox->m_task, messagebox->m_ev);
    
    return RC_SUCCESS; 
}

RC_t messagebox_receive(messagebox_t* messagebox, void* data, uint16_t size)
{
    message_t* local_message; 
    // Check fill level
    if (messagebox->filllevel <= 0){
        //UART_LOG_PutString("MESSAGEBOX RECEIVE FAILED!"); 
        return RC_ERROR_BUFFER_EMTPY;
    }
    
    // get message as pointer
    local_message = &messagebox->message[messagebox->read_idx]; 
    
    // check if pointer is NULL
    if(local_message == 0){
        //UART_LOG_PutString("MESSAGEBOX RECEIVE FAILED!"); 
        return RC_ERROR_MEMORY;
    }
    
    // Fill data with the elements of the message
    for (int i = 0; i < size; i++)
    {
        ((uint8_t*)data)[i] = ((uint8_t*)local_message->m_pBuffer)[i];    
    }
    
    // Free the memory
    free(local_message->m_pBuffer);
    
    // INcrement read index and decrement filllevel
    messagebox->read_idx = messagebox->read_idx + 1;
    messagebox->read_idx = messagebox->read_idx % POSTBOX_SIZE;
    messagebox->filllevel = messagebox->filllevel - 1;
    
    return RC_SUCCESS;
}



/* [] END OF FILE */
