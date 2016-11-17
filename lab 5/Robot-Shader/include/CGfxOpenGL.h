#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

#define GLM_FORCE_RADIANS

#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>
using std::string;
#include <vector>
using std::vector;

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp> 
#include <glm/glm/gtx/transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Robot;

class CGfxOpenGL
{
private:
	Robot *theRobot;
	float rotationAngle;

	int m_windowWidth;
	int m_windowHeight;
	GLuint programHandle;

	glm::mat4 modelView = glm::mat4();
	glm::mat4 view = glm::mat4();
	glm::mat4 perspective = glm::mat4();

	GLint perspectiveID;
	GLint viewID;
	GLint modelID;

	void linkShader(GLint vertShader, GLint fragShader);

public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init();
	bool Shutdown();

	void compileShaders();
	
	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();
};

#endif