/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : texRender.h
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
 * 1    V1.0     2021-5-31   JiangYing    BreakOut     Original Version
 ******************************************************************************/

/******************************************************************************
 *                             Multi-Include-Prevent                          *
 ******************************************************************************/
#ifndef _TEXRENDER_H_
#define _TEXRENDER_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_TEXRENDER
/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"
#include "shader.h"
#include "texture.h"

/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _TEXRENDER_CPP_
#define TEXRENDER_EXT extern
#else
#define TEXRENDER_EXT
#endif
/******************************************************************************
 *                             Struct Define Section                          *
 ******************************************************************************/
struct Character {
	GLuint TextureID;	// ID handle of the glyph texture
	glm::ivec2 Size;	// Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; 	// Horizontal offset to advance to next glyph
};


/******************************************************************************
 *                        Global Variable Declare Section                     
 ******************************************************************************/

/******************************************************************************
 *                            Function Declare Section                        *
 ******************************************************************************/	
class TextRenderer
{
public:
	// Holds a list of pre-compiled Characters
	std::map<GLchar, Character> Characters; 
	// Shader used for text rendering
	Shader TextShader;
	// Constructor
	TextRenderer(GLuint width, GLuint height);
	// Pre-compiles a list of characters from the given font
	void Load(std::string font, GLuint fontSize);
	// Renders a string of text using the precompiled list of characters
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
private:
	// Render state
	GLuint VAO, VBO;
};



#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/



