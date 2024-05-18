/**
* \file uart_cfg.h
* \author P. Fromm
* \date 8.12.19
*
* \brief uart driver wrapper, using own ringbuffer
*
*
* \note <notes>
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 8.12.19, P. Fromm
*            - Initial Release
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
**/


 
#ifndef UARTCFG_H
#define UARTCFG_H

#include "project.h"
#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/** 
 * \brief The macros map the functions the the real driver
 */

#define UART_start() UART_LOG_Start()
    
#define UART_writeByte(data) UART_LOG_WriteTxData(data)
    
#define UART_readByte(data) UART_LOG_GetByte(data)   

    


#endif /* UARTCFG_H */
