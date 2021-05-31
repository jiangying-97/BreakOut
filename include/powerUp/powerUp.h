/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : powerUp.h
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
 * 1    V1.0     2021-5-28   JiangYing    BreakOut     Original Version
 ******************************************************************************/

/******************************************************************************
 *                             Multi-Include-Prevent                          *
 ******************************************************************************/
#ifndef _POWERUP_H_
#define _POWERUP_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_POWERUP
/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"
#include "gameObject.h"
/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _POWERUP_CPP_
#define POWER_EXT extern
#else
#define POWER_EXT
#endif
/******************************************************************************
 *                             Struct Define Section                          *
 ******************************************************************************/


/******************************************************************************
 *                        Global Variable Declare Section                     
 ******************************************************************************/
// The size of a PowerUp block
const glm::vec2 SIZE(60, 20);
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 150.0f);

/******************************************************************************
 *                            Function Declare Section                        *
 ******************************************************************************/
class PowerUp : public GameObject 
{
public:
	// PowerUp State
	std::string Type;
	GLfloat 	Duration;	
	GLboolean	Activated;
	// Constructor
	PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture) 
		: GameObject(position, SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated() { }
};


#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/



