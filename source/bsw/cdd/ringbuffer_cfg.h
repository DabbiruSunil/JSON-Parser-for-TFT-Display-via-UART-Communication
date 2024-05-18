/**
* \file ringbuffer_cfg.h
* \author P. Fromm
* \date 8.12.19
*
* \brief Configuration file for ringbuffer
*
*
* \note In order to easily support MPU systems, the memory for the ringbuffer is part of the ringbuffer structure. 
*      Limitation: only one size possible per project.
*
*      Only elementary data types are supported.
*
* \todo <todos>
*
*  Changelog:\n
*  - 1.0; 8.12.19; Peter Fromm
*            - Initial release
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


 
#ifndef RBCFG_H
#define RBCFG_H
    
#include "global.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines / Macros / Typedefs

#define RB_SIZE 100              /**< \brief Size of the ringbuffer in elements */

typedef uint8_t RB_data_t;      /**< \brief data type to be stored. */


#endif /* RBCFG_H */
