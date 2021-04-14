#include "WindowGL.h"

// Global carible VAO VBO SHADER program and uniform varible
GLuint VAO, VBO, Shaders, uniforModel, IBO; // index buffer ovbject (new buffer object)
GLuint uniformProjection; // This value for creative the viewport scrren camera()
// Data to move object on screen
bool directionX = true;
float MoveX = 0.0f;
float MoveEndSideX = 0.7f;
float MoveIncrementX = 0.005f;
// For Y asix
bool directionY = true;
float MoveY = 0.0f;
float MoveEndSideY = 0.7f;
float MoveIncrementY = 0.00005f;
// For Z asix
bool directionZ = true;
float MoveZ = 0.0f;
float MoveEndSideZ = 5.0f;
float MoveIncrementZ = 0.00005f;

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
	// Enable Intepolation and depth
	glEnable(GL_DEPTH_TEST);

	// Added viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	// Create Figure Object, shader program

	// CODE ...
			//AddTriangle(trig1, Indices);		// Figure Object
			//Fig1.push_back(Object(36, 24, Indices, trig1));
			Fig3.push_back(std::unique_ptr<Object>(new Object(36, 24, Indices, trig1)));
			//Fig2 = std::unique_ptr<Object>(new Object(36, 24, Indices, trig1));
			// Fig1 = new Object(36, 24, Indices, trig1);
			//AddObject(Fig1);
			//AddObject(Fig2);
			AddObject(Fig3[0]);
	// CODE ...

	CompilerShader();	// Shader Program
	// Uniform model projection and Shaders
	uniforModel = glGetUniformLocation(Shaders, "model");
	uniformProjection = glGetUniformLocation(Shaders, "projection");

	return 0;
}

void WindowGL::AddObject(std::unique_ptr<Object> & Obj)
{
	// Create and Bind VAO
	glGenVertexArrays(1, &Obj.get()->VAO);
	glBindVertexArray(Obj.get()->VAO);
	// Create And Bind IBO
	glGenBuffers(1, &Obj.get()->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Obj.get()->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Obj.get()->indexs) * 
					Obj.get()->size_indexs, Obj.get()->indexs, GL_STATIC_DRAW);
	// Create and Bind VBO
	glGenBuffers(1, &Obj.get()->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, Obj.get()->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Obj.get()->figure) * 
					Obj.get()->size_Figure, Obj.get()->figure, GL_STATIC_DRAW);
	// Enable vertex Atribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Unbind
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void WindowGL::AddTriangle(std::unique_ptr<GLfloat[]> Object, unsigned int* Index)
{
	// Create and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Create IBO object and Bind this (index buffer object)
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index)*36, Index, GL_STATIC_DRAW);
	// Create and bind VBO Import triangle data to the buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Object.get())*24, Object.get(), GL_STATIC_DRAW);
	// Enable vertex atribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// include writing attributes
	glEnableVertexAttribArray(0);
	// Unbind VBO VAO IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	// Create projection out of main loop
		glm::mat4 projection = glm::perspective(70.0f, GLfloat(bufferWidth)/GLfloat(bufferHeight), 1.0f, 100.0f);
	// Main loop of window and program
	while (!glfwWindowShouldClose(mainWindow))
	{
		
		// Create Event of Move Object
			// Logic zone of view
				MoveObject(directionX, MoveX, MoveIncrementX, MoveEndSideX);
				MoveObject(directionY, MoveY, MoveIncrementY, MoveEndSideY);
				MoveObject(directionZ, MoveZ, MoveIncrementZ, MoveEndSideZ);
		// Set handle users inputs events, input events
		glfwPollEvents(); // Close window event
		// Clear(refresh) window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Initialization use GLSL shaders program in OpenGL mainLoop
		glUseProgram(Shaders); // Procced program in init and use this

		// CODE ...
		// Create projection out of main loop
			glm::mat4 model(1);
			ShowMatrix(model);
		// model = glm::translate(model, glm::vec3(Move, -0.25f, 0.0f));
			model = MyTranlate(model, glm::vec3(MoveX, MoveX + 0.0005f, MoveZ + 0.005f));
		//model = glm::rotate_slow(model, MoveX * (3.14f * 180.0f), glm::vec3(MoveX, MoveX, MoveY));
			ShowMatrix(model);
			model = glm::rotate_slow(model, MoveY * (3.14f * 180.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			ShowMatrix(model);
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	
			//ShowMatrix(projection);
			//ShowMatrix(model);

			glUniformMatrix4fv(uniforModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// CODE ...
		BindBuffers(Fig3[0]);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		UnBindBuffers();
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Begin from zero end on three
	// End of proccecing swap buffers main and color
		glfwSwapBuffers(mainWindow);
	}
}
// Function Bind VAO IBO buffers
void WindowGL::BindBuffers(std::unique_ptr<Object> & Obj)
{
	glBindVertexArray(Obj.get()->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Obj.get()->IBO);
}
void WindowGL::UnBindBuffers()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Attach proccesing
	glUseProgram(0);
}
// Other function
void ShowMatrix(glm::mat4 model)
{
	std::cout << std::endl;	std::cout << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << model[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	std::cout << std::endl;
}

glm::mat4 MyTranlate(glm::mat4 &model, glm::vec3 vectore)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				model[i][j] = 1;
			else
				model[i][j] = 0;
			if (i == 3 && j < 3)
				model[i][j] = vectore[j];
		}
	}

	return model;
}

void MoveObject(bool & direction, float & Move, float & MoveIncrement, float & MoveEndSide)
{
	if (direction)
	{
		Move += MoveIncrement;
	}
	else
	{
		Move -= MoveIncrement;
	}
	if (std::abs(Move) >= MoveEndSide )
	{
		direction = !direction;
	}
}