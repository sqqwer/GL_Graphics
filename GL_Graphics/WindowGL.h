#pragma once

#include "Object.h"

#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// First created solo Vertex shader
static const char* vShader = "									\n\
#version 330													\n\
																\n\
layout (location = 0) in vec3 pos;								\n\
																\n\
out vec4 vCol;													\n\
																\n\
uniform mat4 model;												\n\
uniform mat4 projection;										\n\
																\n\
void main()														\n\
{																\n\
	gl_Position = model * vec4(pos, 1.0f);						\n\
	vCol = projection * vec4(clamp(pos, 0.0f, 1.0f), 1.0f);		\n\
}";
// work with colour and set red color (Fragment shader)
static const char* fShader = "								\n\
#version 330												\n\
															\n\
in vec4 vCol;												\n\
															\n\
out vec4 colour;											\n\
															\n\
void main()													\n\
{															\n\
	colour = vCol;											\n\
}";

// size of window
static const GLint WIDTH = 800, HEIGHT = 600;
// Declarate User function
void MoveObject(bool& direction, float& Move, float& MoveIncrement, float& MoveEndSide);
void ShowMatrix(glm::mat4 model);
glm::mat4 MyTranlate(glm::mat4& model, glm::vec3 vectore);


class WindowGL
{
public:
	WindowGL();
	int Init();
	void MainLoop();
	void AddTriangle(std::unique_ptr<GLfloat[]> Object, unsigned int* Index);
	void CompilerShader();
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void AddObject(std::unique_ptr<Object> & Obj);

	unsigned int Indices[36] =
	{
		0, 1, 2, 
		2, 3, 1,
		0, 2, 4,
		2, 4, 6,
		3, 2, 7,
		2, 7, 6,
		1, 3, 7,
		1, 5, 7,
		1, 0, 4,
		5, 4, 1,
		4, 6, 5,
		5, 7, 6
	};
	GLfloat trig1[24] = {
		-1.0f, -1.0f, 0.0f, // Zero left bottom
		-1.0f, 1.0f, 0.0f, // One Top Left
		1.0f, -1.0f, 0.0f, // Two Right bottom 
		1.0f, 1.0f, 0.0f, // Tree Right Top
		-1.0f, -1.0f, 1.0f, // BFour left bottom
		-1.0f, 1.0f, 1.0f, // BFive Top Left
		1.0f, -1.0f, 1.0f, // BSix Right bottom 
		1.0f, 1.0f, 1.0f // BSeven Right Top 
	};
	GLfloat trig2[15] = {
		-1.0f, -1.0f, 0.0f, // Lest side of triangle
		0.0f, -1.0f, 1.0f,  // Back side
		1.0f, -1.0f, 0.0f, // Top side of triangle
		0.0f, 1.0f, 0.0f,  // Left side of triangle
		0.0f, -1.0f, 0.0f
	};
	GLFWwindow* mainWindow;
	// Get buffer size information
	int bufferWidth, bufferHeight;

	std::vector<std::unique_ptr<Object>> Fig3;
	std::unique_ptr<Object> Fig2;
	Object* Fig1;
	//std::vector<Object> Fig1;
private:
	void BindBuffers(std::unique_ptr<Object> & Obj);
	void UnBindBuffers();
};