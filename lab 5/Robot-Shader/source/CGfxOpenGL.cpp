#ifdef _WINDOWS
#include <windows.h>
#endif

#include <GL/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "CGfxOpenGL.h"
#include "Robot.h"
// disable implicit float-double casting
#pragma warning(disable:4305)


CGfxOpenGL::CGfxOpenGL()
{
}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init()
{	
	theRobot = new Robot;

	rotationAngle = 0.0f;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	compileShaders();

	return true;
}

bool CGfxOpenGL::Shutdown()
{
	delete theRobot;

	return true;
}

void CGfxOpenGL::compileShaders()
{
	ifstream inFile("shader/basic.vert");
	if (!inFile) {
		fprintf(stderr, "Error opening file: shader/basic.vert\n");
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	if (0 == vertShader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = { codeStr.c_str() };
	glShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the shader
	glCompileShader(vertShader);

	// Check compilation status
	GLint result;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file into shaderCode here
	ifstream fragFile;
	fragFile = ifstream("shader/basic.frag");
	if (!fragFile) {
		fprintf(stderr, "Error opening file: shader/basic.frag\n");
		exit(1);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Create the shader object
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == fragShader) {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	glShaderSource(fragShader, 1, codeArray, NULL);

	// Compile the shader
	glCompileShader(fragShader);

	// Check compilation status
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Fragment shader compilation failed!\n");

		GLint logLen;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	linkShader(vertShader, fragShader);
	perspectiveID = glGetUniformLocation(programHandle, "mProjection");
	viewID = glGetUniformLocation(programHandle, "mView");
	modelID = glGetUniformLocation(programHandle, "mModel");
}

void CGfxOpenGL::linkShader(GLint vertShader, GLint fragShader)
{
	// Create the program object
	programHandle = glCreateProgram();
	if (0 == programHandle) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}


	// Attach the shaders to the program object
	glAttachShader(programHandle, vertShader);
	glAttachShader(programHandle, fragShader);

	// Link the program
	glLinkProgram(programHandle);

	// Check for successful linking
	GLint status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	if (FALSE == status) {

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	else {
		glUseProgram(programHandle);
	}
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;					
	}

	//glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	//glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	//glLoadIdentity();						// reset projection matrix

	//// calculate aspect ratio of window
	//gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	//glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	//glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
	perspective = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Update view and projection matrices in shaders
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(perspectiveID, 1, false, glm::value_ptr(perspective));
	
}

void CGfxOpenGL::Prepare(float dt)
{
	rotationAngle += 45.0f * dt;					// increase our rotation angle counter
	if (rotationAngle >= 360.0f)					// if we've gone in a circle, reset counter
		rotationAngle = 0.0f;

	theRobot->Prepare(dt);
}

void CGfxOpenGL::Render()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//update global rotation
	glm::mat4 model = modelView;
	model = glm::translate(glm::vec3(0.0f, -0.5f, -4.0f)) * glm::rotate(glm::radians(rotationAngle), glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0.0f, 0.5f, 4.0f)) * model;
	glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(model));
	//Render robot
	theRobot->DrawRobot(0.0f, 0.0f, 0.0f);
}
