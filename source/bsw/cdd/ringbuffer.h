/**
* \file ringbuffer.h
* \author P. Fromm
* \date 8.12.19
*
* \brief ringbuffer
*
*
* \note <notes>
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 8.12.19, Peter Fromm
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


 
#ifndef RB_H
#define RB_H
    
#include "global.h"
#include "ringbuffer_cfg.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/


//####################### Structures
/**
* \brief The rinbuffer structure contains all data elements representing a ringbuffer object
*
*/
struct sRB {
    RB_data_t   m_data[RB_SIZE];
    uint16_t    m_readIndex;
    uint16_t    m_writeIndex;
    uint16_t    m_fillLevel;
};
typedef struct sRB RB_t;

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Ringbuffer
{
public:
#endif /* Together */

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Initialisation of a ringbuffer
 * @param RB_t  * const me : IN/OUT - pointer to ringbuffer object 
 * @return RC_SUCCESS or error code
 */
RC_t RB_init(RB_t * const me);

/**
 * Clearing of a ringbuffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return RC_SUCCESS or error code
 */
RC_t RB_clear(RB_t * const me);

/**
 * Write one element to the ringbuffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @param RB_data_t const * const data : IN - Data to be written
 * @return RC_SUCCESS or error code
 */
RC_t RB_write(RB_t * const me, RB_data_t const * const data);

/**
 * Read one element from the ringbuffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @param RB_data_t * const data : OUT - Data read
 * @return RC_SUCCESS or error code
 */
RC_t RB_read(RB_t * const me, RB_data_t * const data);

/**
 * Provide available space in buffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return Available number of elements to be stored
 */
uint16_t RB_getCapacity(RB_t * const me);

/**
 * Check how much data is stored
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return number of byte stored
 */
uint16_t RB_getNumberOfStoredElements(RB_t * const me);

#ifdef TOGETHER
};
#endif /* Together */

#endif /* RB_H */
