#include "WindowGL.h"

// Global carible VAO VBO SHADER program and uniform varible
GLuint VAO, VBO, Shaders, uniforModel;

WindowGL::WindowGL()
{}

int WindowGL::Init()
{
	// Init GLFW
	if (!glfwInit())
	{
		printf("Init GLFW ERROR!\n");
		glfwTerminate();
		return 1;
	}

	// Init Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// set core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// forward compact
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	// Create window
	mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Wind", NULL, NULL);

	// buffers init
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	// Set context for GLEW
	glfwMakeContextCurrent(mainWindow);
	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	// Added viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	// Create Figure Object, shader program
	AddTriangle();		// Figure Object
	CompilerShader();	// Shader Program
	uniforModel = glGetUniformLocation(Shaders, "model");

	return 0;
}

void WindowGL::AddTriangle()
{
	// Create and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Create and bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Import triangle data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(trig1), trig1, GL_STATIC_DRAW);
	// Enable vertex atribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// include writing attributes
	glEnableVertexAttribArray(0);

	// Unbind VBO VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void WindowGL::AddShader(GLuint theProgram, const char* shaderCode, GLenum ShaderType)
{
	// Create GLuint Shader with shaderType
	GLuint theShader = glCreateShader(ShaderType);
	// Add shader char
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	// Count length of shaders
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);
	// Compile shader program GLSL translate to OpenGl shader language
	// Translate to source
	glShaderSource(theShader, 1, theCode, codeLength);
	// Compile program from source
	glCompileShader(theShader);
	// Error list chaeck
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	// Get shader Status error
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		// Get Log of Program
		glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compilint the %d shader : '%s'\n", ShaderType, eLog);
		return;
	}
	// Attach program thread
	glAttachShader(theProgram, theShader);
}

void WindowGL::CompilerShader()
{
	// Create shader programs 
	Shaders = glCreateProgram();
	// Cheack created programs
	if (!Shaders)
	{
		printf("Error creating shader program!\n");
		return;
	}
	// Create somes shaders program(Fragment shader and vertex shader)
	AddShader(Shaders, vShader, GL_VERTEX_SHADER);
	AddShader(Shaders, fShader, GL_FRAGMENT_SHADER);
	// Create for Error varible
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	// Linking compile program
	glLinkProgram(Shaders);
	// Get shader Status error
	glGetProgramiv(Shaders, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(Shaders, sizeof(eLog), NULL, eLog);
		printf("Error linking program '%s' : \n", eLog);
		return;
	}
	// Validation created program and cheack error after validation
	glValidateProgram(Shaders);
	glGetProgramiv(Shaders, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(Shaders, sizeof(eLog), NULL, eLog);
		printf("Error validating program '%s' : \n", eLog);
		return;
	}
}

void WindowGL::MainLoop()
{
	// Main loop of window and program
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Set handle users inputs events, input events
		glfwPollEvents(); // Close window event
		// Clear(refresh) window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Initialization use GLSL shaders program in OpenGL mainLoop
		glUseProgram(Shaders); // Procced program in init and use this

		// CODE ...

		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(0.78f, -0.25f, 0.0f));
		glUniformMatrix4fv(uniforModel, 1, GL_FALSE, glm::value_ptr(model));

		// CODE ...

		// Bind undind vertex array VAO
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Begin from zero end on three
		glBindVertexArray(0);
		// End of proccecing swap buffers main and color
		glUseProgram(0);
		glfwSwapBuffers(mainWindow);
	}
}