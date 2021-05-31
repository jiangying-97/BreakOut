/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : ballObject.h
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
 * 1    V1.0     2021-5-26   JiangYing    BreakOut     Original Version
 ******************************************************************************/

/******************************************************************************
 *                             Multi-Include-Prevent                          *
 ******************************************************************************/
#ifndef _BALLOBJECT_H_
#define _BALLOBJECT_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_BALLOBJECT
/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"
#include "sprite_renderer.h"
#include "gameObject.h"
#include "resource_manager.h"
#include "texture.h"
/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _BALLOBJECT_CPP_
#define BALLOBJECT_EXT extern
#else
#define BALLOBJECT_EXT
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
class BallObject : public GameObject
{
public:
    // Ball state	
    GLfloat   Radius;
    GLboolean Stuck;
	GLboolean Sticky, PassThrough;
    // Constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(GLfloat dt, GLuint window_width,GLuint window_height);
    // Resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};


#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/





