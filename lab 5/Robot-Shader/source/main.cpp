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

void renderFunc() {
	g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
	g_glRender->Render();
	glutSwapBuffers();
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
	glutMainLoop();

	return 0;
}