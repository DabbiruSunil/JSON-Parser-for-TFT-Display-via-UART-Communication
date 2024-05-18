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

#define JSMN_HEADER
#include "jsmn.h"
#include "parser.h"
#include "UART_LOG.h"

/**
 * Create a parser object
 * \param Parser_t *const me - [OUT] Parser object pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_init(Parser_t *const me){
    // init parser
    jsmn_init(&me->parser);
    me->nextFreePos = 0; 
    me->nextToken = 0; 
    
    return RC_SUCCESS;
}

/**
 * Clear a parser object
 * \param Parser_t *const me - [OUT] Parser object pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_clear(Parser_t *const me){
    // Clear parser by setting the attributes to zero
    me->parser.pos = 0;
    me->parser.toknext = 0;
    me->parser.toksuper = -1;
    me->nextFreePos = 0; 
    me->nextToken = 0;
    
    return RC_SUCCESS; 
}

/**
 * Add a char to the buffer
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param char data - [IN] next char of the json string
 * \return RC_SUCCESS
 */
RC_t PARSER_addChar(Parser_t *const me, char data){
    // Error handling tbd
    
    // Add character to content
    me->content[me->nextFreePos] = data;
    me->nextFreePos++; 
    return RC_SUCCESS; 
}

/**
 * Add an endl to the buffer
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_addEndl(Parser_t *const me){
    // Add endline
    me->content[me->nextFreePos] = 0x0A;
    me->nextFreePos++; 
    return RC_SUCCESS; 
}

/**
 * Perform the parsing and create the token list
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param char data - [IN] next char of the json string
 * \return RC_SUCCESS
 */
RC_t PARSER_parse(Parser_t *const me){
    // parse
    jsmn_parse(&me->parser, me->content, me->nextFreePos, me->token, PARSERMAXTOKEN); 
    return RC_SUCCESS; 
}

/**
 * Get the next token of the list
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param jsmntok_t const* token - [OUT] Next token of the list
 * \return RC_SUCCESS
 */
RC_t PARSER_getNextToken(Parser_t *const me, jsmntok_t *const token){
    // Error handling tbd
    if(me->nextToken >= me->parser.toknext){
        return RC_ERROR; 
    } 
    
    // get the next token 
    *token= me->token[me->nextToken];
    me->nextToken++; 
    
    return RC_SUCCESS; 
}

/**
 * Reset token iterator
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_resetNextToken(Parser_t *const me){
    me->nextToken = 0; 
    return RC_SUCCESS; 
}

//--------------------- Some debugging aid
/**
 * Print a parser object content
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_dbg_printContent(Parser_t *const me){
    UART_LOG_PutString("Data received from UART"); 
        
    // Print all tokens
    for(unsigned int i = 0; i<(me->parser.toknext); i++){
        switch(me->token[i].type){
            case JSMN_UNDEFINED:
            UART_LOG_PutString("Parsed token of type JSMN_UNDEFINED: ");
            break; 
            
            case JSMN_OBJECT:
            UART_LOG_PutString("Parsed token of type JSMN_OBJECT: ");
            break; 
            
            case JSMN_ARRAY:
            UART_LOG_PutString("Parsed token of type JSMN_ARRAY: ");
            break; 
            
            case JSMN_STRING:
            UART_LOG_PutString("Parsed token of type JSMN_STRING: ");
            break; 
            
            case JSMN_PRIMITIVE:
            UART_LOG_PutString("Parsed token of type JSMN_PRIMITIVE: ");
            break; 
            
            default:
            break; 
        }
        for(int j = 0; j < (me->token[i].end - me->token[i].start); j++){
            UART_LOG_PutChar(me->content[me->token[i].start + j]); 
        }
        UART_LOG_PutString("\r\n");
    }
    UART_LOG_PutString("Parsed the JSON data successfully\n"); 
    
}

/**
 * Print a parser object content
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_dbg_printToken(Parser_t *const me);

/* [] END OF FILE */
