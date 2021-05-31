/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : shader.h
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
#ifndef _SHADER_H_
#define _SHADER_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_SHADER
/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"

/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _SHADER_CPP_
#define SHADER_EXT extern
#else
#define SHADER_EXT
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
class Shader
	{
	public:
		// State
		GLuint ID; 
		// Constructor
		Shader() { }
		// Sets the current shader as active
		Shader	&Use();
		// Compiles the shader from given source code
		void	Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional 
		// Utility functions
		void	SetFloat	(const GLchar *name, GLfloat value, GLboolean useShader = false);
		void	SetInteger	(const GLchar *name, GLint value, GLboolean useShader = false);
		void	SetVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
		void	SetVector2f (const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
		void	SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
		void	SetVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
		void	SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
		void	SetVector4f (const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
		void	SetMatrix4	(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
	private:
		// Checks if compilation or linking failed and if so, print the error logs
		void	checkCompileErrors(GLuint object, std::string type); 
};



#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/



