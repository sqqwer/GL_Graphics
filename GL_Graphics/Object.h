#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Object
{
public:
	Object();
	Object(int SI, int SF, unsigned int* SAI, GLfloat* SAF);
	~Object();
	GLuint VAO, VBO, IBO;
	GLfloat* figure;
	unsigned int* indexs;
	int size_indexs{0};
	int size_Figure{0};
};

