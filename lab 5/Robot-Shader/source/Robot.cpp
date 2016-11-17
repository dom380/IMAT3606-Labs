#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Robot.h"
#include <vector>
using std::vector;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Robot::Robot()
{
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	vector<GLfloat> colour = {
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f
	};

	vector<GLfloat> vertices = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,
		0.0f, -1.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
	};

	vector<GLubyte> indices = {
		0,1,2, //Front face
		0,2,3, 
		1,5,6, // Right face
		1,6,2,
		4,5,6, //back face
		4,6,7,
		4,0,3, //left face
		4,3,7,
		3,2,6, //top face
		3,6,7,
		0,1,5, //bottom face
		0,5,4
	};
	GLuint vboHandles[3];
	glGenBuffers(3, vboHandles);
	//Create IBO
	GLuint indiceBuffer = vboHandles[0];
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//Create VBO
	GLuint vertexBuffer = vboHandles[1];
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Create VBO for colours
	GLuint colourBuffer = vboHandles[2];
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colour.size(), &colour[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Create Vertex Array Object
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//Bind VBOs to VAO
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 0, (GLubyte *)NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, 0, (GLubyte *)NULL);
	//Bind IBO to VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBuffer);
	//unbind VAO
	glBindVertexArray(0);
	indexSize = indices.size();
}

Robot::~Robot()
{
}

void Robot::DrawCube(float xPos, float yPos, float zPos)
{
	//glPushMatrix();
	//	glTranslatef(xPos, yPos, zPos);
	//	glBegin(GL_POLYGON);
	//		glVertex3f(0.0f, 0.0f, 0.0f);	// top face
	//		glVertex3f(0.0f, 0.0f, -1.0f);
	//		glVertex3f(-1.0f, 0.0f, -1.0f);
	//		glVertex3f(-1.0f, 0.0f, 0.0f);
	//		glVertex3f(0.0f, 0.0f, 0.0f);	// front face
	//		glVertex3f(-1.0f, 0.0f, 0.0f);
	//		glVertex3f(-1.0f, -1.0f, 0.0f);
	//		glVertex3f(0.0f, -1.0f, 0.0f);
	//		glVertex3f(0.0f, 0.0f, 0.0f);	// right face
	//		glVertex3f(0.0f, -1.0f, 0.0f);
	//		glVertex3f(0.0f, -1.0f, -1.0f);
	//		glVertex3f(0.0f, 0.0f, -1.0f);
	//		glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
	//		glVertex3f(-1.0f, 0.0f, -1.0f);
	//		glVertex3f(-1.0f, -1.0f, -1.0f);
	//		glVertex3f(-1.0f, -1.0f, 0.0f);
	//		glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
	//		glVertex3f(0.0f, -1.0f, -1.0f);
	//		glVertex3f(-1.0f, -1.0f, -1.0f);
	//		glVertex3f(-1.0f, -1.0f, 0.0f);
	//		glVertex3f(0.0f, 0.0f, 0.0f);	// back face
	//		glVertex3f(-1.0f, 0.0f, -1.0f);
	//		glVertex3f(-1.0f, -1.0f, -1.0f);
	//		glVertex3f(0.0f, -1.0f, -1.0f);
	//	glEnd();
	//glPopMatrix();
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glBindVertexArray(0);
}

void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);	// red
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);		// arm is a 1x4x1 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);	// white
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 2.0f);		// head is a 2x2x2 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);	// blue
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);		// torso is a 3x5x2 cube
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		
		// draw the foot
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			DrawFoot(0.0f, -5.0f, 0.0f);
		glPopMatrix();		
		
		glScalef(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
		glColor3f(1.0f, 1.0f, 0.0f);	// yellow
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawFoot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 0.5f, 3.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawRobot(float xPos, float yPos, float zPos)
{
	//glPushMatrix();	
	//	glTranslatef(xPos, yPos, zPos);	// draw robot at desired coordinates

	//	// draw head and torso parts
	//	DrawHead(1.0f, 2.0f, 0.0f);		
	//	DrawTorso(1.5f, 0.0f, 0.0f);

	//	// move the left arm away from the torso and rotate it to give "walking" effect
	//	glPushMatrix();
	//		glTranslatef(0.0f, -0.5f, 0.0f);
	//		glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
	//		DrawArm(2.5f, 0.0f, -0.5f);
	//	glPopMatrix();

	//	// move the right arm away from the torso and rotate it to give "walking" effect
	//	glPushMatrix();
	//		glTranslatef(0.0f, -0.5f, 0.0f);
	//		glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	//		DrawArm(-1.5f, 0.0f, -0.5f);
	//	glPopMatrix();

	//	// move the left leg away from the torso and rotate it to give "walking" effect
	//	glPushMatrix();					
	//		glTranslatef(0.0f, -0.5f, 0.0f);
	//		glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
	//		DrawLeg(-0.5f, -5.0f, -0.5f);
	//	glPopMatrix();

	//	// move the right leg away from the torso and rotate it to give "walking" effect
	//	glPushMatrix();
	//		glTranslatef(0.0f, -0.5f, 0.0f);
	//		glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	//		DrawLeg(1.5f, -5.0f, -0.5f);
	//	glPopMatrix();

	//glPopMatrix();	// pop back to original coordinate system
	DrawCube(0.0f, 0.0f, 0.0f);
}

void Robot::Prepare(float dt)
{
	// if leg is moving forward, increase angle, else decrease angle
	for (char side = 0; side < 2; side++)
	{
		// arms
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += 20.0f * dt;
		else
			armAngles[side] -= 20.0f * dt;

		// change state if exceeding angles
		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = FORWARD_STATE;

		// legs
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 20.0f * dt;
		else
			legAngles[side] -= 20.0f * dt;

		// change state if exceeding angles
		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = FORWARD_STATE;		
	}
}