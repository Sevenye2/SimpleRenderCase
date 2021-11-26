//------opengl-------
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//------stb_image------
#define STB_IMAGE_IMPLEMENTATION
#include "../packages/stb-master/stb_image.h"
//------other----------
#include <iostream>
#include <string>

#include "Shader.h"

// which you wanna render
//#define RollSpace
#define WorldMap

float verteices[] =
{
	//---position---   ---texcoord---
	-0.5f, 0.5f,0.5f,	0.0f,1.0f,
	 0.5f, 0.5f,0.5f,	1.0f,1.0f,
	 0.5f,-0.5f,0.5f,	1.0f,0.0f,
	-0.5f,-0.5f,0.5f,	0.0f,0.0f
};
	
int indices[] =
{
	0,1,2,
	0,2,3
};

void load_image(const char* path, GLint internalformat)
{
	int width, height, nrChannel;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);

	// error notication
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, internalformat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Fail to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void ReadRollSpaceTexture()
{
#pragma region TEXTURE



#pragma endregion
}
void ReadWorldMapTexture(int tex, int )
{

}

int main(int argc,char* argv[])
{
#pragma region init and open window
	glfwInit(); //initalize
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Main Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//Sub version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Configuration

	GLFWwindow* window = glfwCreateWindow(600, 600, "MY WINDOW", NULL, NULL);

	if (NULL == window)
	{
		printf("failed in open window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // set this window to operational window

	//Init GLWE
	glewExperimental = true;

	if (GLEW_OK != glewInit())
	{
		printf("there is some problem happend that i don't know");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 1280, 1280);// size of view window
#pragma endregion

#pragma region binding vao vbo
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verteices), verteices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);
#pragma endregion
	float borderColor[4] = { 0.0f,0.0f,0.0f,0.0f };
#ifdef RollSpace
//Load RollSpace
	glActiveTexture(GL_TEXTURE0);
	unsigned int rollTex;
	glGenTextures(1, &rollTex);
	glBindTexture(GL_TEXTURE_2D, rollTex);

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//horizontal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//vertical

	stbi_set_flip_vertically_on_load(true);
	load_image("Texture/T_UIshape_02.tga", GL_RGBA);

	Shader* rollSpace = new Shader("Shader/vertxCommon.txt", "Shader/m_RollSpaceFrag.txt");

#endif
#ifdef WorldMap

//Load World Map 
	glActiveTexture(GL_TEXTURE0);
	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	stbi_set_flip_vertically_on_load(true);
	load_image("Texture/T_GlobalMap.tga", GL_RGBA);

	glActiveTexture(GL_TEXTURE1);
	unsigned int sphereUV;
	glGenTextures(1, &sphereUV);
	glBindTexture(GL_TEXTURE_2D, sphereUV);

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//ºáÖá
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//×ÝÖá
	stbi_set_flip_vertically_on_load(true);
	load_image("Texture/T_UV_Sphere_F.tga", GL_RGB);

	Shader* worldMap = new Shader("Shader/vertxCommon.txt", "Shader/m_WorldMapFrag.txt");
#endif

#pragma region GL Setting
	glClearColor(0.0f, 0.0f, 0.0f, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, true);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// get time
		double t = glfwGetTime();

#ifdef RollSpace
		rollSpace->setFloat("time", t);
		rollSpace->use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif

#ifdef WorldMap
		glActiveTexture(GL_TEXTURE0);
		worldMap->setInt("tex", 0);
		glBindTexture(GL_TEXTURE_2D, tex);

		glActiveTexture(GL_TEXTURE1);
		worldMap->setInt("sphereUV", 1);
		glBindTexture(GL_TEXTURE_2D, sphereUV);
		worldMap->setFloat("time", t);
		worldMap->use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}