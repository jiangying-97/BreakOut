/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : ballObject.cpp
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
 *                             Include File Section                           *
 ******************************************************************************/
#define _GAME_CPP_
#include "ballObject.h"
#undef _GAME_CPP_
/******************************************************************************
 *                         Private Macro Define Section                       *
 ******************************************************************************/
#ifdef DEBUG_GAME
#define BUG_INFO(FMT, arg...)       DEBUG_INFO(FMT,##arg)
#define BUG_WARNING(FMT, arg...)       DEBUG_WARNING(FMT,##arg)
#define BUG_ERROR(FMT, arg...)       DEBUG_ERROR(FMT,##arg)
#define print(FMT, arg...)			printf("[%s:%s:%d]:",__FILE__,__func__,__LINE__);\
									printf(FMT,##arg)
#else
#define BUG_INFO(...)
#define BUG_WARNING(...)
#define BUG_ERROR(...)
#endif
/******************************************************************************
 *                             Struct Define Section                          *
 ******************************************************************************/



/******************************************************************************
 *                           Prototype Declare Section                        *
 ******************************************************************************/



/******************************************************************************
 *                        Global Variable Declare Section                     *
 ******************************************************************************/



/******************************************************************************
 *                     File Static Variable Declare Section                   *
 ******************************************************************************/



/******************************************************************************
 *                           Function Declare Section                         *
 ******************************************************************************/

/*============================== External Function ===========================*/

/******************************************************************************
 * Function Name:
 * Description  :
 * Calls        :
 * Called By    :
 * Input        :
 * Output       :
 * Return Value :
 * Others       :
 *-------------------------------- Revision History ---------------------------
 * No. Version Date       Revised by   Item    Description
 * 1   V1.0    2020-12-9  Tom          WLAN    Original  Version
 ******************************************************************************/
BallObject::BallObject() 
    : GameObject(), Radius(12.5f), Stuck(true) ,Sticky(GL_FALSE), PassThrough(GL_FALSE) 
{

}

/******************************************************************************
 * Function Name:
 * Description  :
 * Calls        :
 * Called By    :
 * Input        :
 * Output       :
 * Return Value :
 * Others       :
 *-------------------------------- Revision History ---------------------------
 * No. Version Date       Revised by   Item    Description
 * 1   V1.0    2020-12-9  Tom          WLAN    Original  Version
 ******************************************************************************/
BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
    :  GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), Stuck(true) ,Sticky(GL_FALSE), PassThrough(GL_FALSE) 
{

}

/******************************************************************************
 * Function Name:
 * Description  :
 * Calls        :
 * Called By    :
 * Input        :
 * Output       :
 * Return Value :
 * Others       :
 *-------------------------------- Revision History ---------------------------
 * No. Version Date       Revised by   Item    Description
 * 1   V1.0    2020-12-9  Tom          WLAN    Original  Version
 ******************************************************************************/
glm::vec2 BallObject::Move(GLfloat dt, GLuint window_width,GLuint window_height)
{
    // If not stuck to player board
    if (!this->Stuck)
    {
        // Move the ball
        this->Position += this->Velocity * dt;
        // Then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
		
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }

    }
    return this->Position;
}

/******************************************************************************
 * Function Name:
 * Description  :
 * Calls        :
 * Called By    :
 * Input        :
 * Output       :
 * Return Value :
 * Others       :
 *-------------------------------- Revision History ---------------------------
 * No. Version Date       Revised by   Item    Description
 * 1   V1.0    2020-12-9  Tom          WLAN    Original  Version
 ******************************************************************************/
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
	this->Sticky = GL_FALSE;
    this->PassThrough = GL_FALSE;
}

/*============================== Internal Function ===========================*/





/*********** (C) COPYRIGHT 2019  Studio  Industry ******* END OF FILE **********/


