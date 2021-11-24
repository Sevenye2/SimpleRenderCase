//------opengl-------
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//------stb_image------
#define STB_IMAGE_IMPLEMENTATION
#include "../packages/stb-master/stb_image.h"
//------other----------
#include <iostream>
#include <string>

#include "Shader.h"

float verteices[] =
{
	//---λ��------    ----����-----
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

	//����
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

int main(int argc,char* argv[])
{
#pragma region ��ʼ�� �� ����
	glfwInit();//��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//�����ļ�

	GLFWwindow* window = glfwCreateWindow(600, 600, "MY WINDOW", NULL, NULL);

	if (NULL == window)
	{
		printf("����ʧ��");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//���ô�������Ϊ��������

	//Init GLWE
	glewExperimental = true;

	if (GLEW_OK != glewInit())
	{
		printf("������");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 600, 600);//�Ӵ����δ�С
#pragma endregion

#pragma region ��vao vbo
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verteices), verteices, GL_STATIC_DRAW);
//������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//��������
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);
#pragma endregion

#pragma region TEXTURE

	glActiveTexture(GL_TEXTURE0);//��������0λ�� ��ʼ����
	unsigned int tex01;
	glGenTextures(1, &tex01);
	glBindTexture(GL_TEXTURE_2D, tex01);

	float borderColor[4] = { 0.0f,0.0f,0.0f,0.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//����

	stbi_set_flip_vertically_on_load(true);
	load_image("T_UIshape_02.tga", GL_RGBA);

#pragma endregion

#pragma region SHADER
	Shader* rollSpace = new Shader("vertex.txt", "fragment.txt");
#pragma endregion

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

		double t = glfwGetTime();
		rollSpace->setFloat("time", t);
		rollSpace->setVec2("pos", 0.5f * cos(t),0.5f * sin(t));
		rollSpace->use();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}