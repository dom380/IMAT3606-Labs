#ifndef __ROBOT_H
#define __ROBOT_H

#include <glm\glm\glm.hpp>

// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE  = 1;

// index constants for accessing arm and leg array data
const char LEFT  = 0;
const char RIGHT = 1;

class Robot
{
private:
	char legStates[2];	
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	GLuint vaoHandle;
	GLsizei indexSize;

	GLuint programHandle;

	// draws a unit cube
	void DrawCube(glm::mat4 modelMatrix);

	// methods to draw the parts of the robot
	void DrawArm(float xPos, float yPos, float zPos, glm::mat4 modelMatrix);
	void DrawHead(float xPos, float yPos, float zPos, glm::mat4 modelMatrix);
	void DrawTorso(float xPos, float yPos, float zPos, glm::mat4 modelMatrix);
	void DrawLeg(float xPos, float yPos, float zPos, glm::mat4 modelMatrix);
	void DrawFoot(float xPos, float yPos, float zPos, glm::mat4 modelMatrix);

public:

	Robot(GLuint shaderHandle);
	virtual ~Robot();

	// draws the entire robot
	void DrawRobot(float xPos, float yPos, float zPos, glm::mat4 modelMatrix);

	// updates the robot data
	void Prepare(float dt);
};

#endif