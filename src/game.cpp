/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : game.cpp
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
 *                             Include File Section                           *
 ******************************************************************************/
#define _GAME_CPP_
#include "game.hpp"
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
 //渲染器
SpriteRenderer   *Renderer;
// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(100, 20);
// 初始化当班的速率
const GLfloat PLAYER_VELOCITY(500.0f);
//挡板对象
GameObject      *Player;
// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球的半径
const GLfloat BALL_RADIUS = 12.5f;
//球体
BallObject   *Ball; 
//梨子发生器
ParticleGenerator   *Particles; 
//特效
PostProcessor   *Effects;
GLfloat ShakeTime = 0.0f;  
//音频播放器
//ISoundEngine *SoundEngine = createIrrKlangDevice();
//文本渲染器
TextRenderer *Text;
glm::vec3 MenuChoiceColor=glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 MenuDefaultColor=glm::vec3(0.5f,0.5f,0.5f);


/******************************************************************************
 *                     File Static Variable Declare Section                   *
 ******************************************************************************/



/******************************************************************************
 *                           Function Declare Section                         *
 ******************************************************************************/
GLboolean ShouldSpawn(GLuint chance);
void ActivatePowerUp(PowerUp &powerUp);
GLboolean isOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type);


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
Game::Game(GLuint width,GLuint height):State(GAME_MENU),Keys(),Width(width),Height(height),Level(0),MenuID(0)
{
	print("this->menu=%d\n",this->State);
	print("Game Init successful\n");
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
Game::~Game()
{
	delete Renderer;
    delete Player;
    delete Ball;
    delete Particles;
	delete Effects;
	delete Text;
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
void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader("./include/shader/shadervs", 
    								"./include/shader/shaderfs", nullptr, "sprite");
	ResourceManager::LoadShader("./include/shader/particlevs",
								  "./include/shader/particlefs", nullptr, "particle");
	ResourceManager::LoadShader("./include/shader/postProcessvs",
								  "./include/shader/postProcessfs", nullptr, "postProcess");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
	
	ResourceManager::GetShader("particle").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);

    // Load textures
    ResourceManager::LoadTexture("./include/picture/paddle.png", GL_TRUE, "paddle");
    ResourceManager::LoadTexture("./include/picture/test.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("./include/picture/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("./include/picture/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("./include/picture/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("./include/picture/particle.png", GL_TRUE, "particle"); 
	ResourceManager::LoadTexture("./include/picture/powerup_chaos.png", GL_TRUE, "tex_chaos"); 
	ResourceManager::LoadTexture("./include/picture/powerup_confuse.png", GL_TRUE, "tex_confuse"); 
	ResourceManager::LoadTexture("./include/picture/powerup_increase.png", GL_TRUE, "tex_increase"); 
	ResourceManager::LoadTexture("./include/picture/powerup_passthrough.png", GL_TRUE, "tex_passthrough");
	ResourceManager::LoadTexture("./include/picture/powerup_speed.png", GL_TRUE, "tex_speed"); 
	ResourceManager::LoadTexture("./include/picture/powerup_sticky.png", GL_TRUE, "tex_sticky"); 

	// load Levels
    GameLevel one;
	one.Load("./include/Levels/level01", this->Width, this->Height * 0.5);
    GameLevel two; 
	two.Load("./include/Levels/level02", this->Width, this->Height * 0.5);
    GameLevel three; 
	three.Load("./include/Levels/level03", this->Width, this->Height * 0.5);
    GameLevel four; 
	four.Load("./include/Levels/level04", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);

	//加载音乐
	//SoundEngine->play2D("./include/audio/breakout.mp3", GL_TRUE);

	
    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	//挡板位置
	glm::vec2 playerPos = glm::vec2(
        this->Width / 2 - PLAYER_SIZE.x / 2, 
        this->Height - PLAYER_SIZE.y
    );
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	//球体位置
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));

	//粒子
	Particles = new ParticleGenerator(
        ResourceManager::GetShader("particle"), 
        ResourceManager::GetTexture("particle"), 
        500
    );

	//特效器
	Effects = new PostProcessor(ResourceManager::GetShader("postProcess"), this->Width, this->Height);

	//文本渲染器
	Text=new TextRenderer(this->Width,this->Height);
	Text->Load("./include/fonts/ariblk.ttf", 20);

	//玩家生命值
	this->Lives=3;
	this->MenuColor[0]=MenuChoiceColor;

	print("Game Init sucessful\n");
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
void Game::Update(GLfloat dt)
{
	//跟新位置
	Ball->Move(dt, this->Width,this->Height);
	 // 检测碰撞
    this->DoCollisions();
	// 更新粒子状态
    Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));
	//判断特效
	if (ShakeTime > 0.0f)
    {
        ShakeTime -= dt;
        if (ShakeTime <= 0.0f)
            Effects->Shake = GL_FALSE;
    }
	//更新powerUp
	UpdatePowerUps(dt);
	//判断是否重新游戏
	if (Ball->Position.y >= this->Height) // 球是否接触底部边界？
    {
         --this->Lives;
        // 玩家是否已失去所有生命值? : 游戏结束
        if (this->Lives == 0)
        {
            this->ResetLevel();
            this->State = GAME_MENU;
        }
        this->ResetPlayer();
    }
	//判断游戏是否完成
	 if (this->State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted())
    {
        this->ResetLevel();
        this->ResetPlayer();
        Effects->Chaos = GL_TRUE;
        this->State = GAME_WIN;
    }
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
void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // 移动挡板
        if (this->Keys[GLFW_KEY_LEFT])
        {
            if (Player->Position.x >= 0)
            {
                Player->Position.x -= velocity;
				if (Ball->Stuck)
             	   Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_RIGHT])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
				if (Ball->Stuck)
                	Ball->Position.x += velocity;
            }
        }
		//空格发射求
		if (this->Keys[GLFW_KEY_UP])
            Ball->Stuck = false;
    }
	//关卡选择
	if (this->State == GAME_MENU)
	{
	    if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
	    {
	    	switch(this->MenuID){
				case 0:
					this->State = GAME_ACTIVE;
					this->KeysProcessed[GLFW_KEY_ENTER]=GL_TRUE;
					break;
				case 1:
					this->State=GAME_ABOUT;
					this->KeysProcessed[GLFW_KEY_ENTER]=GL_TRUE;
					break;
				default:
					break;
			}
	    }
	    if (this->Keys[GLFW_KEY_RIGHT] && !this->KeysProcessed[GLFW_KEY_RIGHT])
	    {
	    	switch(this->MenuID){
				case 0:
					this->Level = (this->Level + 1) % 4;
					this->KeysProcessed[GLFW_KEY_RIGHT]=GL_TRUE;
					break;
				case 1:
					break;
				default:
					break;
			}        
	    }
	    if (this->Keys[GLFW_KEY_LEFT] && !this->KeysProcessed[GLFW_KEY_LEFT])
	    {
	   		switch(this->MenuID){
				case 0:
					if (this->Level> 0)
						--this->Level;
					else
						this->Level = 0;
					this->KeysProcessed[GLFW_KEY_LEFT]=GL_TRUE;
					break;
				case 1:
					break;
				default:
					break;
			}   
	    }
		if (this->Keys[GLFW_KEY_UP] && !this->KeysProcessed[GLFW_KEY_UP])
	    {
	    	this->MenuColor[MenuID]=MenuDefaultColor;
			MenuID++;
			MenuID %= MenuNum;
	        this->MenuColor[MenuID]=MenuChoiceColor;
			this->KeysProcessed[GLFW_KEY_UP]=GL_TRUE;
	    }
		if (this->Keys[GLFW_KEY_DOWN] && !this->KeysProcessed[GLFW_KEY_DOWN])
	    {
	        this->MenuColor[MenuID]=MenuDefaultColor;
			MenuID--;
			MenuID%= MenuNum;
	        this->MenuColor[MenuID]=MenuChoiceColor;
			this->KeysProcessed[GLFW_KEY_DOWN]=GL_TRUE;
	    }
	}
	//游戏胜利
	if (this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
            Effects->Chaos = GL_FALSE;
            this->State = GAME_MENU;
        }
    }
	//关于界面
	if (this->State == GAME_ABOUT)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
            Effects->Chaos = GL_FALSE;
            this->State = GAME_MENU;
        }
    }
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
void Game::Render()
{
	//游戏进行界面
    if(this->State == GAME_ACTIVE || this->State==GAME_MENU)
    {
    	//开始帧缓冲渲染
        Effects->BeginRender();
	        // 绘制背景
	        Renderer->DrawSprite(ResourceManager::GetTexture("background"), 
	          						  glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
	        // 绘制关卡
	        this->Levels[this->Level].Draw(*Renderer);

			//绘制powerUp
			for (PowerUp &powerUp : this->PowerUps)
	            if (!powerUp.Destroyed)
	                powerUp.Draw(*Renderer);

			//绘制挡板
			Player->Draw(*Renderer);

			//绘制粒子 
	        Particles->Draw();

			//绘制球体
			Ball->Draw(*Renderer);

			//绘制文本
       		Text->RenderText("Lives:" +to_string(this->Lives), 5.0f, 5.0f, 1.0f);
			
		Effects->EndRender();
		//特效
      Effects->Render(glfwGetTime());

    }

	//游戏菜单界面
	if (this->State == GAME_MENU)
    {
        Text->RenderText("Press ENTER to start", 150.0f, Height / 2-20.0f, 1.5f);
        Text->RenderText("Press UP or DOWN to select level", 150.0f, Height / 2 + 20.0f, 1.5f);
		//选项
		Text->RenderText("level:      "+to_string(this->Level+1), 210.0f, Height / 2 + 50.0f, 1.0f,this->MenuColor[0]);
		Text->RenderText("About Game", 210.0f, Height / 2 + 80.0f, 1.0f,this->MenuColor[1]);
    }
	//游戏胜利界面
	if (this->State == GAME_WIN)
    {
        Text->RenderText(
            "You WON!!!", 320.0, Height / 2 - 48.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
        );
        Text->RenderText(
            "Press ENTER to retry or ESC to quit", 200.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
        );
    }
	//游戏关于界面
	if (this->State == GAME_ABOUT)
    {
        Text->RenderText(
            "Author:JiangYing", 320.0, Height / 2 - 48.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
        );
		 Text->RenderText(
            "Date:2021-05-24", 320.0, Height / 2 - 48.0+30.0f, 1.0, glm::vec3(0.0, 1.0, 0.0)
        );
        Text->RenderText(
            "Press ENTER to retry or ESC to quit", 200.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
        );
    }
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
void Game::DoCollisions()
{
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
    	//方块碰撞处理
        if (!box.Destroyed)
        {
            Collision collision =this->CheckCollisionRidus(*Ball, box);
            if (std::get<0>(collision)) // 如果collision 是 true
            {
                // 如果不是实心的砖块则摧毁
                if (!box.IsSolid)
                {
                    box.Destroyed = GL_TRUE;
					this->SpawnPowerUps(box);
                }
                else
                {   // 如果是实心的砖块则激活shake特效
                    ShakeTime = 0.05f;
                    Effects->Shake = GL_TRUE;
                }
                // 碰撞处理
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid)) 
				{
	                if (dir == LEFT || dir == RIGHT) // 水平方向碰撞
	                {
	                    Ball->Velocity.x = -Ball->Velocity.x; // 反转水平速度
	                    // 重定位
	                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
	                    if (dir == LEFT)
	                        Ball->Position.x += penetration; // 将球右移
	                    else
	                        Ball->Position.x -= penetration; // 将球左移
	                }
	                else // 垂直方向碰撞
	                {
	                    Ball->Velocity.y = -Ball->Velocity.y; // 反转垂直速度
	                    // 重定位
	                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
	                    if (dir == UP)
	                        Ball->Position.y -= penetration; // 将球上移
	                    else
	                        Ball->Position.y += penetration; // 将球下移
	                }
				}
            }
     	}
    }
#if 1
	//挡板碰撞处理
	Collision result = this->CheckCollisionRidus(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result))
    {
        // 检查碰到了挡板的哪个位置，并根据碰到哪个位置来改变速度
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // 依据结果移动
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength; 
        //Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);  //粘板问题处理
        Ball->Stuck = Ball->Sticky;
    } 
	
	//poerUp检测
	for (PowerUp &powerUp : this->PowerUps)
	{
      	if (!powerUp.Destroyed)
    	{
	        if (powerUp.Position.y >= this->Height)
	            powerUp.Destroyed = GL_TRUE;
	        if (this->CheckCollisionAABB(powerUp,*Player))
	        {   // 道具与挡板接触，激活它！
	            ActivatePowerUp(powerUp);
	            powerUp.Destroyed = GL_TRUE;
	            powerUp.Activated = GL_TRUE;
				print("--------------mick-->\n");
	        }
      	}
    }
#endif
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
GLboolean Game::CheckCollisionAABB(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // x轴方向碰撞？
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // y轴方向碰撞？
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // 只有两个轴向都有碰撞时才碰撞
    return collisionX && collisionY;
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
Collision Game::CheckCollisionRidus(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // 获取圆的中心 
    glm::vec2 center(one.Position + one.Radius);
    // 计算AABB的信息（中心、半边长）
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_extents.x, 
        two.Position.y + aabb_half_extents.y
    );
    // 获取两个中心的差矢量
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
    glm::vec2 closest = aabb_center + clamped;
    // 获得圆心center和最近点closest的矢量并判断是否 length <= radius
    difference = closest - center;
	if (glm::length(difference) <= one.Radius)
        return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
    else
        return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
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
Direction Game::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // 上
        glm::vec2(1.0f, 0.0f),  // 右
        glm::vec2(0.0f, -1.0f), // 下
        glm::vec2(-1.0f, 0.0f)  // 左
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
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
void Game::ResetLevel()
{
    if (this->Level == 0)this->Levels[0].Load("./include/Levels/level01", this->Width, this->Height * 0.5f);
    else if (this->Level == 1)
        this->Levels[1].Load("./include/Levels/level02", this->Width, this->Height * 0.5f);
    else if (this->Level == 2)
        this->Levels[2].Load("./include/Levels/level03", this->Width, this->Height * 0.5f);
    else if (this->Level == 3)
        this->Levels[3].Load("./include/Levels/level04", this->Width, this->Height * 0.5f);
	this->Lives = 3;//初始生命值3
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
void Game::ResetPlayer()
{
    // Reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
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
void Game::SpawnPowerUps(GameObject &block)
{
    if (ShouldSpawn(75)) // 1/75的几率
        this->PowerUps.push_back(
             PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, 
             ResourceManager::GetTexture("tex_speed")        ));
    if (ShouldSpawn(75))
        this->PowerUps.push_back(
            PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position,
            ResourceManager::GetTexture("tex_sticky")         ));
    if (ShouldSpawn(75))
        this->PowerUps.push_back(
            PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, 
            ResourceManager::GetTexture("tex_passthrough")       ));
    if (ShouldSpawn(75))
        this->PowerUps.push_back(
            PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, 
            ResourceManager::GetTexture("tex_increase")      ));
    if (ShouldSpawn(15)) // 负面道具被更频繁地生成
        this->PowerUps.push_back(
            PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, 
            ResourceManager::GetTexture("tex_confuse")        ));
    if (ShouldSpawn(15))
        this->PowerUps.push_back(
            PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, 
            ResourceManager::GetTexture("tex_chaos")        ));
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
void Game::UpdatePowerUps(GLfloat dt)
{
	for (PowerUp &powerUp : this->PowerUps)
	{
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{
			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f)
			{
				// 之后会将这个道具移除
				powerUp.Activated = GL_FALSE;
				// 停用效果
				if (powerUp.Type == "sticky")
				{
					if (!isOtherPowerUpActive(this->PowerUps, "sticky"))
					{	// 仅当没有其他sticky效果处于激活状态时重置，以下同理
						Ball->Sticky = GL_FALSE;
						Player->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if (!isOtherPowerUpActive(this->PowerUps, "pass-through"))
					{
						Ball->PassThrough = GL_FALSE;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!isOtherPowerUpActive(this->PowerUps, "confuse"))
					{
						Effects->Confuse = GL_FALSE;
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!isOtherPowerUpActive(this->PowerUps, "chaos"))
					{
						Effects->Chaos = GL_FALSE;
					}
				}				 
			}
		}
	}
	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
		[](const PowerUp &powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
	), this->PowerUps.end());
}  

/*============================== Internal Function ===========================*/
/***/
GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % chance;
    return random == 0;
}
/***/
void ActivatePowerUp(PowerUp &powerUp)
{
    // 根据道具类型发动道具
    if (powerUp.Type == "speed")
    {
        Ball->Velocity *= 1.2;
    }
    else if (powerUp.Type == "sticky")
    {
        Ball->Sticky = GL_TRUE;
        Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
    }
    else if (powerUp.Type == "pass-through")
    {
        Ball->PassThrough = GL_TRUE;
        Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
    }
    else if (powerUp.Type == "pad-size-increase")
    {
        Player->Size.x += 50;
    }
    else if (powerUp.Type == "confuse")
    {
        if (!Effects->Chaos)
            Effects->Confuse = GL_TRUE; // 只在chaos未激活时生效，chaos同理
    }
    else if (powerUp.Type == "chaos")
    {
        if (!Effects->Confuse)
            Effects->Chaos = GL_TRUE;
    }
} 
/***/
GLboolean isOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type)
{
    for (const PowerUp &powerUp : powerUps)
    {
        if (powerUp.Activated)
            if (powerUp.Type == type)
                return GL_TRUE;
    }
    return GL_FALSE;
}  




/*********** (C) COPYRIGHT 2019  Studio  Industry ******* END OF FILE **********/

