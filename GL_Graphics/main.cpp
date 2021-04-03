#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// size of window
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("Init GLFW ERROR!\n");
		glfwTerminate();
		return 1;
	}

	// Setup window GLFW OpenGl ver
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// COre profile = NO Backwards Compatibles
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward Comtability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "LOL", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation fail\n");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	int bufferWIdth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWIdth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!\n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWIdth, bufferHeight);

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}