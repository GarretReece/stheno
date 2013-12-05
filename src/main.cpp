#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sys/time.h>

#include "ship.h"
#include "render_object.h"
#include "quaternion.h"

int wX = 512, wY = 512;
render_object scene_root;
ship *s;

double t = 0.0;
const double dt = 0.01;

double current_time, accumulator = 0.0;

double current_time_in_sec()
{
	timeval a;
	gettimeofday(&a, 0);
	return a.tv_sec + (a.tv_usec/1000000);
}

void init()
{
	current_time = current_time_in_sec();

	s = new ship();
	s->translate += vector3f(128, 128, 0);
	s->rotate = quaternion::from_axis(vector3f(0,0,1),3.1415f/2.0f);
	scene_root.add_child(s);
}

void simulate()
{
	double new_time = current_time_in_sec();
	double frame_time = new_time = current_time;
	if (frame_time > 0.25) frame_time = 0.25;
	current_time = new_time;

	accumulator += frame_time;

	while (accumulator >= dt)
	{
		//set previous state = current state
		//call integrate(current state, t, dt)
		t += dt;
		accumulator -= dt;
	}

	const double alpha = accumulator / dt;
	//interpolate: State state = current_state * alpha + previous_state * (1.0-alpha)

	glutPostRedisplay();

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

	init();

	glutDisplayFunc(drawFrame);
	glutReshapeFunc(changeSize);
	//glutMotionFunc(processMouseMovement);
	//glutPassiveMotionFunc(processMouseMovement);
	//glutMouseFunc(processMouseClicks);
	glutIdleFunc(simulate);
	glutMainLoop();
	return 1;
}
