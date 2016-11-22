#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include "CGfxOpenGL.h"
#include "timer.h"

long windowWidth = 1024;
long windowHeight = 768;
CGfxOpenGL *g_glRender = NULL;
CHiResTimer *g_hiResTimer = NULL;

void idle() {
	glutPostRedisplay();
}

//The fact I have to do this is dumb. C (and by extension GLUT) can't handle non-static member pointers thus the need for these ugly globals. Why do people still support C?
void renderFunc() {
	g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
	g_glRender->Render();
	glutSwapBuffers();
}
void handleKeyPress(unsigned char key, int x, int y) {
	g_glRender->handleKeyPress(key, x, y);
}
void handleSpecialKey(int key, int x, int y) {
	g_glRender->handleSpecialKey(key, x, y);
}
void handleSpecialKeyUp(int key, int x, int y) {
	g_glRender->handleSpecialKeyUp(key, x, y);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("GLEW Test");
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	}
	//fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	g_glRender = new CGfxOpenGL;
	g_hiResTimer = new CHiResTimer;
	g_glRender->Init();
	g_hiResTimer->Init();
	g_glRender->SetupProjection(windowWidth, windowHeight);
	glutDisplayFunc(renderFunc);
	glutIdleFunc(idle);
	glutKeyboardFunc(handleKeyPress);
	glutSpecialFunc(handleSpecialKey);
	glutSpecialUpFunc(handleSpecialKeyUp);
	glutMainLoop();

	return 0;
}