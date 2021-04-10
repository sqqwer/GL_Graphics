#pragma once

#include <cmath>
#include <stdio.h>
#include <string.h>

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
uniform mat4 model;												\n\
																\n\
void main()														\n\
{																\n\
	vec4  as = vec4(0.1f*pos.x, 0.1f*pos.y, pos.z, 1.0f);		\n\
	gl_Position = model * as;									\n\
}";
// work with colour and set red color (Fragment shader)
static const char* fShader = "								\n\
#version 330												\n\
															\n\
out vec4 colour;											\n\
															\n\
void main()													\n\
{															\n\
	colour = vec4(1.0f, 0.0, 0.0, 1.0);						\n\
}";

// size of window
static const GLint WIDTH = 800, HEIGHT = 600;

class WindowGL
{
public:
	WindowGL();
	int Init();
	void MainLoop();
	void AddTriangle();
	void CompilerShader();
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
private:
	GLfloat trig1[9] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	GLFWwindow* mainWindow;
	// Get buffer size information
	int bufferWidth, bufferHeight;
};

