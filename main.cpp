/******************************************************************************
 *                                    BreakOut
 *        (c) Copyright 2021, RD Department,  Studio  Industry Co.Ltd
 *                               All Rights Reserved
 *
 * FileName     : main.cpp
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
#define _MAIN_CPP_
#include "types.h"
#include "game.hpp"
#include "test.h"
#include "resource_manager.h"
#include <stb_image.h>

#undef _MAIN_CPP_
/******************************************************************************
 *                         Private Macro Define Section                       *
 ******************************************************************************/
 #define DEBUG_MAIN
#ifdef DEBUG_MAIN
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


#define TESTFUNC    (0)
/******************************************************************************
 *                             Struct Define Section                          *
 ******************************************************************************/



/******************************************************************************
 *                           Prototype Declare Section                        *
 ******************************************************************************/



/******************************************************************************
 *                        Global Variable Declare Section                     *
 ******************************************************************************/
// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;
//Game object
Game Breakout(SCREEN_WIDTH,SCREEN_HEIGHT);


/******************************************************************************
 *                     File Static Variable Declare Section                   *
 ******************************************************************************/



/******************************************************************************
 *                           Function Declare Section                         *
 ******************************************************************************/
// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mainFramebuffer_size_callback(GLFWwindow* window,int width,int height);


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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
        {
            Breakout.Keys[key] = GL_FALSE;
		 	Breakout.KeysProcessed[key] = GL_FALSE;
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
void mainFramebuffer_size_callback(GLFWwindow* window,int width,int height)
{
	glViewport(0,0,width,height);
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
 const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSourceTest = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSourceTest = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


 // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
 // ---------------------------------------------------------------------------------------------------------
 void processInput(GLFWwindow *window)
 {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		 glfwSetWindowShouldClose(window, true);
 }
 
 // glfw: whenever the window size changed (by OS or user resize) this callback function executes
 // ---------------------------------------------------------------------------------------------
 void framebuffer_size_callback(GLFWwindow* window, int width, int height)
 {
	 // make sure the viewport matches the new window dimensions; note that width and 
	 // height will be significantly larger than specified on retina displays.
	 glViewport(0, 0, width, height);
 }

 int test(){
	// glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	//glEnable(GL_CULL_FACE);//面剔除
	glEnable(GL_BLEND);//混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//透明alpha通道


    // build and compile our shader program
    // ------------------------------------
/*
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceTest, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceTest, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
*/

	Shader shader=ResourceManager::LoadShader("./include/shader/particlevs", 
										  			"./include/shader/particlefs", nullptr,"test");
//	Shader shader=ResourceManager::LoadShader("./include/shader/shadervs", 
//										  			"./include/shader/shaderfs", nullptr,"test");

	GLuint shaderProgram=shader.ID;
	ResourceManager::LoadTexture("./include/picture/awesomeface.png", GL_TRUE, "test");
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)SCREEN_WIDTH,(GLfloat)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("test").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("test").Use().SetMatrix4("projection", projection);
	SpriteRenderer* Renderer = new SpriteRenderer(ResourceManager::GetShader("test"));
	ParticleGenerator* Particles = new ParticleGenerator(
			ResourceManager::GetShader("test"), 
			ResourceManager::GetTexture("test"), 
			10
	);

/*
	// load and create a texture 
    // -------------------------
    unsigned int texture;
    // texture 1
    // ---------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("./include/picture/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
*/	
	
#if 0
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    GLfloat vertices[] = { 
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

	 glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("awesomeface").ID);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_TRIANGLES,0,6);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
#else
	while (!glfwWindowShouldClose(window)){
        // Calculate delta time
        glfwPollEvents();



        // Render
       	glClearColor(0.5f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
       // Renderer->DrawSprite(ResourceManager::GetTexture("test"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		//绘制粒子 
        Particles->Draw();
	   glfwSwapBuffers(window);

	}
	ResourceManager::Clear();
    glfwTerminate();
#endif
    return 0;
 }

/*============================== Internal Function ===========================*/
int main(int argc, char *argv[])
{
#if TESTFUNC
	cout<<"----------------------------------BreakOut----------------------------------"<<endl;
	cout<<"Test model"<<endl;
	//testFun(argc, argv);
	test();
#else
	cout<<"----------------------------------BreakOut----------------------------------"<<endl;
	cout<<"Normal model"<<endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
	if(window==NULL){
		print("Create window failed\n");
		return -1;
	}
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    glfwSetKeyCallback(window, key_callback);

    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window,mainFramebuffer_size_callback);
	
    glEnable(GL_CULL_FACE);//面剔除
    glEnable(GL_BLEND);//混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//透明alpha通道

    // Initialize game
    Breakout.Init();

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // Start Game within Menu State
    Breakout.State = GAME_MENU;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        //deltaTime = 0.001f;
        // Manage user input
        Breakout.ProcessInput(deltaTime);

        // Update Game state
        Breakout.Update(deltaTime);

        // Render
       	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        glfwSwapBuffers(window);
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();

	printf("----------------------------------BREAKOUT END----------------------\n");
    return 0;
#endif

}



/*********** (C) COPYRIGHT 2019  Studio  Industry ******* END OF FILE **********/


