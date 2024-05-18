/**
* \file main
* \author OPeter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
* The file contains two cyclic tasks, whioch both access the same UART to create a critical region
* Depending on priority and timing configuration, the data may get corrupted.
*
*
*
* \note Tracealyser is connected over USB
*
*  Changelog:\n
*  - 1.0; 5.12.19; P. Fromm
*            - Initial version
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

/**
 * Task cyclic has priority 4 "Poor lonesome cowboay", task cyclic_2 has priority 5 "Bang"
 *
 * Testcase 1 - As is
 * Testcase 2 - Set activation time of high priority task tsk_cyclic2 to 101 
 * Testcase 3 - Using TX isr
 * Testcase 4 - Using ressources
**/
/*
#define TESTCASE 3


#if TESTCASE == 1

    #undef TIMINGOFFSET
    #define TXBLOCKING
    #undef RESSOURCE
    
#endif

#if TESTCASE == 2

    #define TIMINGOFFSET
    #define TXBLOCKING
    #undef RESSOURCE
    
#endif

#if TESTCASE == 3

    #define TIMINGOFFSET
    #undef TXBLOCKING
    #undef RESSOURCE
    
#endif

#if TESTCASE == 4

    #define TIMINGOFFSET
    #define TXBLOCKING
    #define RESSOURCE
    
#endif
    */


#include "project.h"
#include "global.h"
#include "trcRecorder.h"

#include "led.h"
#include "uart.h"

/********************************************************************************
 * Global objects
 ********************************************************************************/

UART_t UART_port;

traceHandle TRC_ISRUartTxHandle;

/********************************************************************************
 * Systick
 ********************************************************************************/

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}


/********************************************************************************
 * Main
 ********************************************************************************/


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
    
    //Enable trace
    vTraceEnable(TRC_INIT);
    TRC_ISRUartTxHandle = xTraceSetISRProperties("ISR_UART_TX", 1);
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
        
        
}

/********************************************************************************
 * Exception Handler
 ********************************************************************************/


void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}


/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    
    //Init MCAL Drivers
	//UART_LOG_Start();
    UART_init(&UART_port);
    
    LED_Init();

        
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the alarm with 100ms cycle time
  //  SetRelAlarm(alrm_cyclic,100,100);
    
#ifdef TIMINGOFFSET
    SetRelAlarm(alrm_cyclic2,101,100);
#else
   // SetRelAlarm(alrm_cyclic2,100,100);
#endif
    
    //Alarm for calling the tracealyser communiction task
  //  SetRelAlarm(alrm_TaskTrzCtrl,200,200); 

    //Activate all extended and the background task
    ActivateTask(tsk_background);
    ActivateTask(tsk_json);
    TerminateTask();
    
}
TASK(tsk_json)
{
    EventMaskRefType ev=0;
    while(1)
    {
        
        WaitEvent(endOfLine);
        GetEvent(tsk_json,&ev);
        ClearEvent(ev);
        
        UART_writeString(&UART_port,UART_port.m_rxBuffer.m_data);
    }
}
/**
 * Task tsk_cyclic
 * Activated by alrm_cyclic
 * 
 * Priority 4 (lower)
 **/
TASK(tsk_cyclic)
{
    LED_Toggle(LED_YELLOW);
    
    
#ifdef RESSOURCE
    GetResource(res_uart);
#endif
    
#ifdef TXBLOCKING
    //This one will not use an interrupt to transfer data
    UART_LOG_PutString("I'm a poor low priority cyclic task having a hell of a job!\n");
    //UART_LOG_PutString("Short\n");
#else
    //This one will use an interrupt to transfer data
    UART_writeString(&UART_port, "I'm a poor low priority cyclic task having a hell of a job!\n");
#endif

#ifdef RESSOURCE
    ReleaseResource(res_uart);
#endif

    TerminateTask();
}

/**
 * Task tsk_cyclic
 * Activated by alrm_cyclic2
 * 
 * Priority 5 (higher)
 **/
TASK(tsk_cyclic2)
{
    LED_Toggle(LED_GREEN);
#ifdef RESSOURCE
    GetResource(res_uart);
#endif
        
#ifdef TXBLOCKING
        //This one will not use an interrupt to transfer data
    UART_LOG_PutString("Bang!!!!\n");
#else
    //This one will use an interrupt to transfer data
    UART_writeString(&UART_port, "Bang!!!!\n");
#endif    

 #ifdef RESSOURCE
    ReleaseResource(res_uart);
#endif

    TerminateTask();
}


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

/*
ISR2(isr_Button)
{
    SetEvent(tsk_sevenSet,ev_reset);   
}
*/

ISR2(isr_DEBUG_tx)
{

  //  vTraceStoreISRBegin(TRC_ISRUartTxHandle);
    
    UART_TX_isrHandler(&UART_port);
    
  //  vTraceStoreISREnd(0);
}

ISR2(isr_DEBUG_rx)
{
     UART_RX_isrHandler(&UART_port);
}


/* [] END OF FILE */
