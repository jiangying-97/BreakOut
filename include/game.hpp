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
//游戏状态
enum GameState {
    GAME_ACTIVE,//激活
    GAME_MENU,//菜单
    GAME_WIN,//胜利
    GAME_ABOUT//关于
};
//方向美剧
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};	
//菜单选项
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
	    // 游戏状态变量
	    GameState              State;	
	    GLboolean              Keys[1024];
		GLboolean KeysProcessed[1024];
	    GLuint                 Width, Height;
		std::vector<GameLevel> Levels;
   		GLuint                 Level;    
		std::vector<PowerUp>  PowerUps;
		GLuint Lives;//玩家生命值
		glm::vec3 MenuColor[MenuNum];
		GLuint MenuID;
	    // 构造、析构函数
	    Game(GLuint width, GLuint height);
	    ~Game();
	    // 初始化游戏状态（加载着色器、贴图、绑定对象等）
	    void Init();
	    // 游戏循环
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


