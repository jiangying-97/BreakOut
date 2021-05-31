/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : types.h
 * Description :This code is part of Breakout.
 *				   Breakout is free software: you can redistribute it and/or modify
 * 				   it under the terms of the CC BY 4.0 license as published by
 * 				   Creative Commons, either version 4 of the License, or (at your
 *                 option) any later version.
 * Version      : V1.0
 * Function List:
 *                 1.
 *------------------------------Revision History-------------------------------
 * No.  Version  Date        Revised By   Item         Description
 * 1    V1.0     2021-5-24   JiangYing    BreakOut     Original Version
 ******************************************************************************/

/******************************************************************************
 *                             Multi-Include-Prevent                          *
 ******************************************************************************/
#ifndef _TYPES_H_
#define _TYPES_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_TYPES
#define GLEW_STATIC

/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>

//#include <SOIL/SOIL.h>


#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"





using namespace std;
/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _GAME_CPP_
#define GAME_EXT extern
#else
#define GAME_EXT
#endif
/******************************************************************************
 *                             Struct Define Section                          *
 ******************************************************************************/

/******************************************************************************
 *                        Global Variable Declare Section                     
 ******************************************************************************/

/******************************************************************************
 *                            Function Declare Section                        *
 ******************************************************************************/


#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/



