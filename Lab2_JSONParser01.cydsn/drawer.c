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

#include "drawer.h"

// lookup-table which maps a string to the value
item items[] = {
        {"red", 0x001F}, {"blue", 0xF800}, {"green", 0x07E0}, {"white", 0xFFFF},
        {"black", 0x0000}, {"magenta", 0xF81F}, {"yellow", 0x07FF}};

// number of items in the lookup table
size_t num_items = sizeof(items) / sizeof(item);

// Prototype of function mapArrayToTFTColor
void mapArrayToTFTColor(uint8_t* color, uint8_t length, TFT_color_t tft_color);

/**
 * Translates a JSON tag into a command type for the TFT
 * \param Drawer_t *const me            - [OUT] the next command
 * \param Parser_t *const parser        - [IN/OUT] Parser object pointer
 * \return RC_SUCCESS if a command was found, RC_ERROR_BUFFER_EMTPY if parsing has come to an end, other error code as required
 */
RC_t DRAWER_getNextDrawCommand(Drawer_t *const me, Parser_t *const parser){
    jsmntok_t crnt_token;
    uint8_t coordinates[4] = {0,0,0,0};
    TFT_color_t tft_color;
    Drawer_commandType_t command;
   
    // Return if function call failes
    if (PARSER_getNextToken(parser, &crnt_token) != 0){
            return RC_ERROR;
    }

    // Get next token if token type is object
    if (crnt_token.type == JSMN_OBJECT){
        PARSER_getNextToken(parser, &crnt_token);
    }
    
        switch(crnt_token.type){            
            case JSMN_STRING:
                // Check if content is 'c'
                if(parser->content[crnt_token.start] == 'c'){
                    
                        // Return if function call failes
                    if (PARSER_getNextToken(parser, &crnt_token) != 0){
                        return RC_ERROR;
                    }
                    
                    // Check if tokentype is not a string
                    if (crnt_token.type != JSMN_STRING){
                        return RC_ERROR;
                    }
            
                    // Allocate dynamic array
                    uint8_t colorLength = crnt_token.end - crnt_token.start;
                    uint8_t *color = (uint8_t*) malloc(colorLength * sizeof(uint8_t)); 
                    
                    // Get the string which indicates the color
                    for(unsigned int it_colorLength = 0; it_colorLength<colorLength; it_colorLength++){
                        color[it_colorLength] = parser->content[crnt_token.start + it_colorLength];
                        if(it_colorLength == colorLength-1){
                            color[it_colorLength+1] = '\0'; 
                        }
                    }
                    
                    // Search for values which correspons with string and set it to tft_color
                    item* found = search(items, num_items, color);
                    tft_color = found->value;
                    
                    // Set the command and the color
                    me->command = DRAWER_CMD_COLOR; 
                    me->data.color = tft_color;
                    
                    // Free memory
                    free(color); 
                } 
                
                else if(parser->content[crnt_token.start] == 'd'){
                        // Get next token 
                        if (PARSER_getNextToken(parser, &crnt_token) != 0){
                            return RC_ERROR;
                        }
                        
                        // Go through the next 4 tokens and get the vlaues
                        for(int allTokens = 0; allTokens <4; allTokens++){
                            // Get next token 
                            if (PARSER_getNextToken(parser, &crnt_token) != 0){
                                return RC_ERROR;
                            }
                            
                            // Check if token is a primitive
                            if (crnt_token.type != JSMN_PRIMITIVE){
                                return RC_ERROR;
                            }
                            
                            // Allocate memory
                            uint8_t primitiveLength = crnt_token.end - crnt_token.start;
                            char* coordinate = (char*) malloc(primitiveLength * sizeof(char));
                        
                            // Get the values as a string
                            for(uint8_t it_primitive = 0; it_primitive<primitiveLength; it_primitive++){
                                coordinate[it_primitive] = parser->content[crnt_token.start + it_primitive]; 
                                if(it_primitive == (primitiveLength - 1)){
                                    coordinate[it_primitive+1] = '\0'; 
                                }   
                            }
                            // Convert string to an integer
                            uint8_t value = (uint8_t) atoi(coordinate);
                            
                            // Free Space
                            free(coordinate); 
                            
                            // Assign value to coordinate array
                            me->data.coordinate[allTokens] = value; 
                        }
                    
                        me->command = DRAWER_CMD_DRAW;
                } 
            break; 
           
            default:
                return RC_ERROR; 
            break;
            }
    
    return RC_SUCCESS;
}

item* search(item* items, size_t size, const char* color){
    // Go through lookup table and compare string to string of the lookup table
    for (size_t it=0; it<size; it++) {
        // When found return the value
        if (strcmp(items[it].color, color) == 0) {
            return &items[it];
        }
    }
    return NULL;
}

/* [] END OF FILE */