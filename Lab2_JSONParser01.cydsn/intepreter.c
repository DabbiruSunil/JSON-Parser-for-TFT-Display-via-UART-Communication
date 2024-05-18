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

#include "intepreter.h"

RC_t inteprete(Drawing_t* drawing, Parser_t* parser){
    drawing->size = 0;
    Drawer_t drawer;
    
        // Go through the parser and get the next drawing command
        while (!(DRAWER_getNextDrawCommand(&drawer, parser)))
        {
            // assign drawing to drawer elemnt
            drawing->drawer[drawing->size] = drawer;
            drawing->size = drawing->size + 1; 
            // If 20 drawings receives return
            if (drawing->size >= 20){
                return RC_ERROR_BUFFER_FULL;
            }
        }

        return RC_SUCCESS;
}


/* [] END OF FILE */
