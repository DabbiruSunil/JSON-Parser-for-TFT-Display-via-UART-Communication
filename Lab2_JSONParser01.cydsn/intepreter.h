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
#include "parser.h"
#include "drawer.h"

/**
* Typedef struct which has drawers and the size as attributes. 
*/
typedef struct{
    Drawer_t drawer[20]; 
    int size; 
} Drawing_t; 

/**
* \breif Function to interprete the parser into drawings.
*/
RC_t inteprete(Drawing_t* drawing, Parser_t* parser);


/* [] END OF FILE */
