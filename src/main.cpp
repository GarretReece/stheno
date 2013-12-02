#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sys/time.h>

#include "ship.h"
#include "render_object.h"

double current_time_in_sec();

int wX = 512, wY = 512;
render_object scene_root;
ship *s;

double t = 0.0;
const double dt = 0.01;

double current_time = current_time_in_sec();
double accumulator = 0.0;


double current_time_in_sec()
{
	timeval a;
	gettimeofday(&a, 0);
	return a.tv_sec + (a.tv_usec/1000000);
}

void init_ship_position()
{
	s = new ship();
	s->translate += vector3f(128, 128, 0);
	scene_root.add_child(s);
}

void drawFrame()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	scene_root.draw();
	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	wX = w;
	wY = h;
	if (wX <= 0) wX = 1;
	if (wY <= 0) wY = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, wX, wY);
	gluOrtho2D(wX,0,wY,0);	//swap around x axis to make windows and openGL coords match
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(wX, wY);
	glutCreateWindow("SHIPS");

	init_ship_position();

	glutDisplayFunc(drawFrame);
	glutReshapeFunc(changeSize);
	//glutMotionFunc(processMouseMovement);
	//glutPassiveMotionFunc(processMouseMovement);
	//glutMouseFunc(processMouseClicks);
	glutIdleFunc(drawFrame);
	glutMainLoop();
	return 1;
}
