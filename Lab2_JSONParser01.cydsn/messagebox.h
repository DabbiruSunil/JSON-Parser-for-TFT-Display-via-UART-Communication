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

#include "global.h"
#include "project.h"

typedef struct
{
    uint16_t m_size;
    void* m_pBuffer; 
} message_t;

#define POSTBOX_SIZE 10

typedef struct
{
    EventMaskType m_ev; 
    TaskType m_task; 
    uint16_t m_size; 
    uint16_t read_idx;    /**< Next to be read element. */
    uint16_t write_idx;  /**< Next free byte to write. */
    uint16_t filllevel; 
    message_t message[POSTBOX_SIZE]; 
} messagebox_t;

/**
* Funtion to initiliaze the messagebox
*/
RC_t messagebox_init(messagebox_t* messagebox, uint16_t size, EventMaskType eventMaskType, TaskType taskType); 

/**
* Send Messagebox to a task
*/
RC_t messagebox_send(messagebox_t* messagebox, void* data, uint16_t size); 

/**
* Receive messagebox
*/
RC_t messagebox_receive(messagebox_t* messagebox, void* data, uint16_t size); 

/**
* Clear messagebox
*/ 
RC_t messagebox_clear(messagebox_t* messagebox);

/* [] END OF FILE */
