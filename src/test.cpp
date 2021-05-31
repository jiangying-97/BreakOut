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
#define _TEST_CPP_
#include "test.h"
#include "stb_image.h"

#undef _TEST_CPP_
/******************************************************************************
 *                         Private Macro Define Section                       *
 ******************************************************************************/
#ifdef DEBUG_TEST
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

#define PI 3.14

/******************************************************************************
 *                             Struct Define Section                          *
 ******************************************************************************/



/******************************************************************************
 *                           Prototype Declare Section                        *
 ******************************************************************************/



/******************************************************************************
 *                        Global Variable Declare Section                     *
 ******************************************************************************/
GLFWwindow* window;
const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;
GLuint VBO;
float vertices[]=
{
	0.5f,0.5f,-0.5f, 1.0f,0.0f,0.0f, 1.0f,1.0f,//右上后
	0.5f,-0.5f,-0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下后
	-0.5f,-0.5f,-0.5f, 0.0f,0.0f,1.0f, 0.0f,0.0f,//左下后
	-0.5f,0.5f,-0.5f, 1.0f,1.0f,0.0f, 0.0f,1.0f,//左上后
	
	0.5f,0.5f,0.5f, 1.0f,0.0f,0.0f, 1.0f,1.0f,//右上前
	0.5f,-0.5f,0.5f, 0.0f,1.0f,0.0f, 1.0f,0.0f,//右下前
	-0.5f,-0.5f,0.5f, 0.0f,0.0f,1.0f, 0.0f,0.0f,//左下前
	-0.5f,0.5f,0.5f, 1.0f,1.0f,0.0f, 0.0f,1.0f//左上前
};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
};

unsigned int indices[]={
	0,1,3,//后
	1,2,3,

	4,5,7,//前
	5,6,7,

	0,1,4,//右
	1,5,4,

	2,3,6,//左
	3,7,6,

	0,4,3,//上
	3,7,4,
};

float vertices_01[]=
{
	0.0f,0.8f,0.0f,
	-0.8f,0.0f,0.0f,
	0.8f,0.0f,0.0f,

	-0.8f,0.0f,0.0f,
	0.8f,0.0f,0.0f,
	0.0f,-0.8f,0.0f
};

float vertices_02[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float texCoords[]=
{
	0.0f,0.0f,
	1.0f,0.0f,
	0.5f,1.0f
};


const char* vertexShaderSource="#version 330 core\n"
									"layout (location=0) in vec3 aPos;\n"
									"layout (location=1) in vec3 aColor;\n"
									"layout (location=2) in vec2 aTexCoord;\n"

									"out vec3 ourColor;\n"
									"out vec2 TexCoord;\n"

									"uniform mat4 transform;\n"
									"uniform mat4 view;\n"
									"uniform mat4 projection;\n"
									"uniform mat4 model;\n"

									"void main()\n"
									"{\n"
									"gl_Position=projection * view * model *  vec4(aPos,1.0);\n"
									"ourColor=aColor;\n"
									"TexCoord=vec2(aTexCoord.x,aTexCoord.y);\n"
									"}\n";

unsigned int vertexShader;

const char* fragMentShaderSource="#version 330 core\n"
									"out vec4 FragColor;\n"

									"in vec3 ourColor;\n"
									"in vec2 TexCoord;\n"

									"uniform sampler2D ourTexture1;\n"
									"uniform sampler2D ourTexture2;\n"
									"void main()\n"
									"{\n"
										"FragColor=mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.4);\n"
									"}\n";
									
unsigned int fragMentShader;

unsigned int shaderProgram;

GLuint VAO;
GLuint EBO;

float roate;

float cameraSpeed=0.5;
float deltaTime=0.0f;
float lastFrame=0.0f;

float lastX=400;
float lastY=300;
float pitch=0.0f;
float fov=45.0f;
float yaw=-90.0f;
bool firstMouse=true;
	
glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 cameraUp=glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 cameraFront=glm::vec3(0.0f,0.0f,-1.0f);


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
void mouse_callback(GLFWwindow* window,double xpos,double ypos)
{
	if(firstMouse)
	{
		lastX=xpos;
		lastY=ypos;
		firstMouse=false;
	}

	float xoffset=xpos-lastX;
	float yoffset=lastY-ypos;
	lastX=xpos;
	lastY=ypos;

	float sensitivity=0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw +=xoffset;
	pitch+= yoffset;

	if(pitch>89.0f)
		pitch=89.0f;
	if(pitch<-89.0f)
		pitch=-89.0f;

	glm::vec3 front;
	front.x=cos(glm::radians(yaw))*cos(glm::radians(pitch));
	front.y=sin(glm::radians(pitch));
	front.z=sin(glm::radians(yaw))*cos(glm::radians(pitch));
	cameraFront=glm::normalize(front);
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
void scroll_callback(GLFWwindow *window,double xoffset,double yoffset)
{
	fov-=(float)yoffset;
	if(fov<1.0f)
		fov=1.0f;
	if(fov>45.0f)
		fov=45.0f;
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
int Create_Window(void)
{
	window=glfwCreateWindow(800,600,"JiangYing",NULL,NULL);
	if(window==NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	return 0;
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
void Framebuffer_size_callback(GLFWwindow* window,int width,int height)
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
void Input_Process(GLFWwindow* window)
{
	cameraSpeed=2.5f*deltaTime;

	if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
	if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
	{
		cameraPos+=cameraSpeed*cameraFront;
	}
	if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
	{
		cameraPos-=glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
	}
	if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
	{
		cameraPos+=glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
	}
	if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
	{
		cameraPos-=cameraSpeed*cameraFront;
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
void Clear_Window()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
int testFun(int argc,char** argv)
{
	int success;
	char infoLog[512];

	//init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	
	if(Create_Window()<0){
		cout<<"Failed to create GLFW window"<<endl;
		return -1;
	}

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window,Framebuffer_size_callback);
	
	glEnable(GL_DEPTH_TEST);

	//VAO/VBO/EBO
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	//shaders
	vertexShader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout<<"ERROR::SHADER::VERTEX::COMPILEATION_FAILED\n"<<infoLog<<endl;
	}

	fragMentShader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragMentShader,1,&fragMentShaderSource,NULL);
	glCompileShader(fragMentShader);
	glGetShaderiv(fragMentShader,GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(fragMentShader,512,NULL,infoLog);
		cout<<"ERROR::SHADER::FRAGMENT::COMPILEATION_FAILED\n"<<infoLog<<endl;
	}

	
	shaderProgram=glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragMentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
		cout<<"ERROR::PROGRAM::VERTEX::COMPILEATION_FAILED\n"<<infoLog<<endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragMentShader);
	
	//Attribute
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	glBindVertexArray(VAO);

	//texture
	float timeValue;
	float greenValue;
	int vertexColorLocation;

	unsigned int texture1;
	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D,texture1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	int width,height,nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data=stbi_load("./include/picture/test.jpg",&width,&height,&nrChannels,0);
	if(!data)
	{
		cout<<"Failed to load texture1"<<endl;
	}
	else{	
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	unsigned int texture2;
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D,texture2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	data=stbi_load("./include/picture/container.jpg",&width,&height,&nrChannels,0);
	if(!data)
	{
		cout<<"Failed to load textur2"<<endl;
	}
	else{	
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	glUniform1i(glGetUniformLocation(shaderProgram,"ourTexture1"),0);

	glm::mat4 trans=glm::mat4(1.0f);
	glm::mat4 model=glm::mat4(1.0f);
	glm::mat4 view=glm::mat4(1.0f);
	glm::mat4 projection=glm::mat4(1.0f);

	unsigned int transformLoc,modelLoc,viewLoc,projectionLoc;
	float angle;
	int i;


	glm::vec3 cameraTarget = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 cameraDirection=glm::normalize(cameraPos-cameraTarget);
	glm::vec3 up=glm::vec3(0.0f,1.0f,0.0f);
	glm::vec3 cameraRight=glm::cross(cameraDirection,cameraRight);
	float radius=5.0f;
	float camX=sin(glfwGetTime())*radius;
	float camZ=cos(glfwGetTime())*radius;
	float currentFrame;

	glfwSetCursorPosCallback(window,mouse_callback);
	glfwSetScrollCallback(window,scroll_callback);
	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	while(!glfwWindowShouldClose(window))
	{
		Input_Process(window);
		Clear_Window();

		glUseProgram(shaderProgram);

		trans=glm::mat4(1.0f);
		view=glm::mat4(1.0f);
		model=glm::mat4(1.0f);
		projection=glm::mat4(1.0f);


		camX=sin(glfwGetTime())*radius;
		camZ=cos(glfwGetTime())*radius;
		view=glm::lookAt(cameraPos,
					cameraPos+cameraFront,
					cameraUp);

	//	trans=glm::translate(trans,glm::vec3(0.0f,0.0f,0.0f));
		trans=glm::rotate(trans,glm::radians(roate),glm::vec3(0.0f,0.0f,1.0f));
		projection=glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
		/*	
			timeValue=glfwGetTime();
		greenValue=(sin(timeValue)/2.0f)+0.5f;
		vertexColorLocation=glGetUniformLocation(shaderProgram,"aAlphy");
		glUniform1f(vertexColorLocation,greenValue);
		*/

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,texture2);

		glBindVertexArray(VAO);
		transformLoc=glGetUniformLocation(shaderProgram,"transform");
		modelLoc=glGetUniformLocation(shaderProgram,"model");
		viewLoc=glGetUniformLocation(shaderProgram,"view");
		projectionLoc=glGetUniformLocation(shaderProgram,"projection");
		glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(trans));
		glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

		//glDrawArrays(GL_TRIANGLES,0,36);

		for(i=1;i<11;i++)
		{
			model=glm::mat4(1.0f);
			model=glm::translate(model,cubePositions[i]);
			angle=10.0f*i;

			model=glm::rotate(model,(float)glfwGetTime()*glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
			glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));

			glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
			
		}
		
		currentFrame=glfwGetTime();
		deltaTime=currentFrame-lastFrame;
		lastFrame=currentFrame;
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;

}





/*********** (C) COPYRIGHT 2019  Studio  Industry ******* END OF FILE **********/


