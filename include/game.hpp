/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : game.hpp
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
#ifndef _GAME_HPP_
#define _GAME_HPP_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_GAME
/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "gameObject.h"
#include "gameLevel.h"
#include "ballObject.h"
#include "particle_generator.h"
#include "postProcess.h"
#include "powerUp.h"
#include "texRender.h"
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
//????????????
enum GameState {
    GAME_ACTIVE,//??????
    GAME_MENU,//??????
    GAME_WIN,//??????
    GAME_ABOUT//??????
};
//????????????
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};	
//????????????
enum Menu{
	LEVELS,
	ABOUT,
	MenuNum,
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; 

/******************************************************************************
 *                        Global Variable Declare Section                     
 ******************************************************************************/

/******************************************************************************
 *                            Function Declare Section                        *
 ******************************************************************************/
class Game
{
	public:
	    // ??????????????????
	    GameState              State;	
	    GLboolean              Keys[1024];
		GLboolean KeysProcessed[1024];
	    GLuint                 Width, Height;
		std::vector<GameLevel> Levels;
   		GLuint                 Level;    
		std::vector<PowerUp>  PowerUps;
		GLuint Lives;//???????????????
		glm::vec3 MenuColor[MenuNum];
		GLuint MenuID;
	    // ?????????????????????
	    Game(GLuint width, GLuint height);
	    ~Game();
	    // ?????????????????????????????????????????????????????????????????????
	    void Init();
	    // ????????????
	    void ProcessInput(GLfloat dt);
	    void Update(GLfloat dt);
	    void Render();
		void DoCollisions();
		GLboolean CheckCollisionAABB(GameObject &one, GameObject &two);//AABB-AABB
		Collision CheckCollisionRidus(BallObject &one, GameObject &two); // AABB - Circle collision
		Direction VectorDirection(glm::vec2 target);
		void ResetLevel();
		void ResetPlayer();
		void SpawnPowerUps(GameObject &block);
        void UpdatePowerUps(GLfloat dt);
};


#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/


