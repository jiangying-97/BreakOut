/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : texture.h
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
#ifndef _TEXTURE_H_
#define _TEXTURE_H_


/******************************************************************************
 *                              Debug Switch Section                          *
 ******************************************************************************/
#define DEBUG_TEXTURE

/******************************************************************************
 *                             Include File Section                           *
 ******************************************************************************/
#include "types.h"

/******************************************************************************
 *                          Pubilc Macro Define Section                       *
 ******************************************************************************/
#ifndef _TEXTURE_CPP_
#define TEXTURE_EXT extern
#else
#define TEXTURE_EXT
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
class Texture2D
{
	public:
		// Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
		GLuint ID;
		// Texture image dimensions
		GLuint Width, Height; // Width and height of loaded image in pixels
		// Texture Format
		GLuint Internal_Format; // Format of texture object
		GLuint Image_Format; // Format of loaded image
		// Texture configuration
		GLuint Wrap_S; // Wrapping mode on S axis
		GLuint Wrap_T; // Wrapping mode on T axis
		GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
		GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
		// Constructor (sets default texture modes)
		Texture2D();
		// Generates texture from image data
		void Generate(GLuint width, GLuint height, unsigned char* data);
		// Binds the texture as the current active GL_TEXTURE_2D texture object
		void Bind() const;
};


#endif

/*********** (C) COPYRIGHT 2020 Voyager Industry ******** END OF FILE ********/




