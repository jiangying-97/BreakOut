/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : resource_manager.h
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
#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_RESOURCE_MANAGER
#define GLEW_STATIC

/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"
#include "shader.h"
#include "texture.h"

/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _RESOURCE_MANAGER_CPP_
#define RESOURCE_MANAGER_EXT extern
#else
#define RESOURCE_MANAGER_EXT
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
class ResourceManager
	{
	public:
		// Resource storage
		static std::map<std::string,Shader>	Shaders;
		static std::map<std::string,Texture2D> Textures;
		// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
		static Shader	LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
		// Retrieves a stored sader
		static Shader	GetShader(std::string name);
		// Loads (and generates) a texture from file
		static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
		// Retrieves a stored texture
		static Texture2D GetTexture(std::string name);
		// Properly de-allocates all loaded resources
		static void 	 Clear();
		
	private:
		// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
		ResourceManager() { }
		// Loads and generates a shader from file
		static Shader	 loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
		// Loads a single texture from file
		static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};



#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/



