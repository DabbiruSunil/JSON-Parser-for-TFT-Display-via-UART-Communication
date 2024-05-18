/**
* \file parser.c
* \author P. Fromm
* \date 8.12.19
*
* \brief Parser implementation
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
#include "parser.h"

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
 * Create a parser object
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_init(Parser_t *const me)
{
    PARSER_clear(me);
    return RC_SUCCESS;
}

/**
 * Clear a parser object
 * \param Parser_t *const me - [OUT] Parser object pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_clear(Parser_t *const me)
{
    
    jsmn_init(&me->parser);
    
    return RC_SUCCESS;
}

/**
 * Add a char to the buffer
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param char data - [IN] next char of the json string
 * \return RC_SUCCESS
 */
RC_t PARSER_addChar(Parser_t *const me, char data)
{
    
}


/**
 * Add an endl to the buffer
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_addEndl(Parser_t *const me)
{
    
}

/**
 * Perform the parsing and create the token list
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param char data - [IN] next char of the json string
 * \return RC_SUCCESS
 */
RC_t PARSER_parse(Parser_t *const me)

{
    
}

/**
 * Get the next token of the list
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param jsmntok_t const* token - [OUT] Next token of the list
 * \return RC_SUCCESS
 */
RC_t PARSER_getNextToken(Parser_t *const me, jsmntok_t *const token)
{
    
}

/**
 * Reset token iterator
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_resetNextToken(Parser_t *const me)
{
    
}


//--------------------- Some debugging aid


/**
 * Print a parser object content
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_dbg_printContent(Parser_t *const me)
{
    
}

/**
 * Print a parser object content
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_dbg_printToken(Parser_t *const me)
{
    
}

/* [] END OF FILE */
