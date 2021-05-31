/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : resource_manager.cpp
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
#define _RESOURCE_MANAGER_CPP_
#include "resource_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef _RESOURCE_MANAGER_CPP_
/******************************************************************************
 *                         Private Macro Define Section                       *
 ******************************************************************************/
#ifdef DEBUG_RESOURCE_MANAGER
#define BUG_INFO(FMT, arg...)       DEBUG_INFO(FMT,##arg)
#define BUG_WARNING(FMT, arg...)    DEBUG_WARNING(FMT,##arg)
#define BUG_ERROR(FMT, arg...)      DEBUG_ERROR(FMT,##arg)
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
std::map<std::string,Texture2D>     ResourceManager::Textures;
std::map<std::string,Shader>     ResourceManager::Shaders;



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
Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
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
Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
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
Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
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
Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
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
void ResourceManager::Clear()
{
    // (Properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
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
Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
		print("Open shader files successful\n");
    }
    catch (std::exception e)
    {
       print("ERROR::SHADER: Failed to read shader files\n");
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
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
Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // Load image
    int width, height,nrChannels;
/*
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
*/
	stbi_set_flip_vertically_on_load(true);
	unsigned char *image = stbi_load(file, &width, &height, &nrChannels, 0);
	if (image)
    {
		print("file=%s\n weight=%d\n height=%d\n nrChannels=%d\n",file,width,height,nrChannels);
		print("texture ID=%d\n",texture.ID);
    }
    else
    {
        print("Failed to load texture\n");
    }
    // Now generate texture
    texture.Generate(width, height, image);
    // And finally free image data
/*
    SOIL_free_image_data(image);
*/
	stbi_image_free(image);

	print("Generate Texture successful\n");
    return texture;
}

/*============================== Internal Function ===========================*/





/*********** (C) COPYRIGHT 2019  Studio  Industry ******* END OF FILE **********/


