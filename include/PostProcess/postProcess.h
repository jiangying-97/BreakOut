/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : postProcess.h
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
 * 1    V1.0     2021-5-27   JiangYing    BreakOut     Original Version
 ******************************************************************************/

/******************************************************************************
 *                             Multi-Include-Prevent                          *
 ******************************************************************************/
#ifndef _POSTPROCESS_H_
#define _POSTPROCESS_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_POSTPROCESS
/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"
#include "sprite_renderer.h"
#include "shader.h"
#include "texture.h"


/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _POSTPROCESS_CPP_
#define POSTPROCESS_EXT extern
#else
#define POSTPROCESS_EXT
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
class PostProcessor
{
public:
	// State
	Shader PostProcessingShader;
	Texture2D Texture;
	GLuint Width, Height;
	// Options
	GLboolean Confuse, Chaos, Shake;
	// Constructor
	PostProcessor(Shader shader, GLuint width, GLuint height);
	// Prepares the postprocessor's framebuffer operations before rendering the game
	void BeginRender();
	// Should be called after rendering the game, so it stores all the rendered data into a texture object
	void EndRender();
	// Renders the PostProcessor texture quad (as a screen-encompassing large sprite)
	void Render(GLfloat time);
private:
	// Render state
	GLuint MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
	GLuint RBO; // RBO is used for multisampled color buffer
	GLuint VAO;
	// Initialize quad for rendering postprocessing texture
	void initRenderData();
};


#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/



