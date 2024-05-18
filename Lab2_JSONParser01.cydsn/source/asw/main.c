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

/**
* Include Files
*/
#include "project.h"
#include "global.h"
#include "circularRingbuffer.h"
#include "UART_LOG.h"
#include "jsmn.h"
#include "parser.h"
#include "drawer.h"
#include "messagebox.h"
#include "intepreter.h"
#include "tft.h"
#include "ST7735.h"

#define endofUARTInput '$'

/**
* Global Variables
*/

circularRingbuffer_t myRB;
messagebox_t messagebox; 
CY_ISR_PROTO(ISR_UART_RX); 

/**
* \brief Main funnction
*/ 
int main()
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    // Start UART RX ISR
    ISR_UART_RX_StartEx(ISR_UART_RX); 
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

/**
* \brief Function which is calles if an unhandled exception occurs.
*/
void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/**
* \brief Inittasks witch autostarts and initiates other tasks.
*/
TASK(tsk_init)
{
    // Init for UART 
    UART_LOG_Init();
    UART_LOG_Start();
    
    // Init for TFT
    TFT_init();
    TFT_setBacklight(80);
 
    // Activate Tasks json parser,background and hmi
    ActivateTask(tsk_json_parser);
    ActivateTask(tsk_hmi);
    ActivateTask(tsk_background);
    
    // Activate Tasks
    TerminateTask();
}

/**
* \brief Task which parses the JSON String and creates messages for the hmi task.
*/
TASK(tsk_json_parser)
{
    EventMaskType ev = 0;
    uint8_t data;
    
    // RINGBUFFER intialization
    RC_t ret = circularRingbuffer_init(&myRB, 800);

    // PARSER intialization
    char JSONString[PARSERSTRINGSIZE];
    Parser_t p; 
    ret = PARSER_init(&p);
    
    // DRAWER objects
    Drawer_t drawer;
    Drawing_t drawing; 
    
    // MESSAGING BOX intialization
    messagebox_init(&messagebox, 0, ev_drawing_command, tsk_hmi); 
    
    while(1)
    {
        //Wait, read and clear the event  
        WaitEvent(ev_received);
        GetEvent(tsk_json_parser, &ev);
        ClearEvent(ev);
                
        data=0;
        GetResource(ringbuffer_res);
        
        // Fill String with emptz data
        for(int i = 0; i<PARSERSTRINGSIZE; i++){
            JSONString[i] = ' ';  
        }
        
        while(1){ 
            // Get Byte and add to parser
            circularRingbuffer_read(&myRB, &data);
            PARSER_addChar(&p, data);
            
            // End of protocoll received
            if(data == endofUARTInput){
                // Parse and print 
                /*
                Data to be parsed as example { "c" : "red", "d" : [10, 10, 10, 100], "d" : [10, 100, 100, 100], "d" 
                                                : [100, 100, 100, 10], "d" : [100, 10, 10, 10 ] }

                */
                PARSER_parse(&p);
                PARSER_dbg_printContent(&p);
                
                // Get Resource and interprete into drawings
                GetResource(drawing_res); 
                inteprete(&drawing, &p);
                
                // Send out the messages one by one
                for(int i = 0; i <drawing.size; i++){
                    messagebox_send(&messagebox, &drawing.drawer[i], sizeof(drawing.drawer[i])); 
                }
                
                // Clear the parser and release drawing resource
                PARSER_clear(&p);
                ReleaseResource(drawing_res); 
                break;
            }
        }
        ReleaseResource(ringbuffer_res);
    }
}

/**
* \brief Task which receives the messages and draws lines to the tft display.
*/
TASK(tsk_hmi)
{
    EventMaskType ev = 0;
    //TFT and Drawer Objects
    RC_t res; 
    TFT_colors_t local_tft_color;
    Drawer_t local_drawer;
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_drawing_command);
        GetEvent(tsk_hmi, &ev);
        ClearEvent(ev);
        
        GetResource(drawing_res);
        
        // Get filllevel and through all messages
        int fillLevel =  messagebox.filllevel;
        for (int i = 0; i < fillLevel; i++)
        {
            // Get Message size
            uint16_t message_size = messagebox.message[messagebox.read_idx].m_size;
            if(message_size == 0) 
            {
                break; 
            }
                
            // Receive drawer 
            res = messagebox_receive(&messagebox, &local_drawer, message_size);
            
            // If message box successfully received message display lines or select colour  according to command
            if (res == RC_SUCCESS)
            {
                if (local_drawer.command == DRAWER_CMD_COLOR)
                {
                    local_tft_color = local_drawer.data.color;
                }
                else 
                {
                    TFT_writeLine(local_drawer.data.coordinate[0], 
                                    local_drawer.data.coordinate[1], 
                                        local_drawer.data.coordinate[2], 
                                            local_drawer.data.coordinate[3], 
                                                            local_tft_color);
                } 
            }
        }
        ReleaseResource(drawing_res); 
    }
}

/**
* \brief Background task which does absolutely nothing.
*/
TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/
/**
* \brief ISR of the UART RX.
*/
CY_ISR(ISR_UART_RX)
{
    // Get resource and write into ringbuffer
    GetResource(ringbuffer_res);
    uint8_t receivedData = UART_LOG_ReadRxData();
    circularRingbuffer_write(&myRB, receivedData);
    
    // Check if byte was eop
    if(receivedData == endofUARTInput){
        // Fire event to thhe parser task
        SetEvent(tsk_json_parser, ev_received); 
    }
    ReleaseResource(ringbuffer_res);
}


