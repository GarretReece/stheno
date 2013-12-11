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

int wX = 1024, wY = 768;
render_object scene_root;

double t = 0.0;
const double dt = 0.01;

double current_time, accumulator = 0.0;

float alpha = 1.0f;

double current_time_in_sec()
{
	timeval a;
	gettimeofday(&a, 0);
	return (double)a.tv_sec + (double)(a.tv_usec/1000000.0f);
}

void init()
{
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	current_time = current_time_in_sec();

	physics_object *m = new physics_object();
	m->translate() += vector3f(wX/2, wY/2, 0);
	m->current.angular_momentum[2] = -1.0f;
	scene_root.add_child(m);

	sprite *spr = new sprite("sprites/rocket.bmp");

	ship *s = new ship(spr);
	s->translate() += vector3f(50,0,0);
	//s->current.angular_momentum[2] = 1.0f;
	s->scale() *= 0.8f;
	m->add_child(s);

	s = new ship(spr);
	s->translate() += vector3f(100, 200, 0);
	s->current.angular_momentum[2] = 7.5f;
	s->scale() *= 1.25f;
	scene_root.add_child(s);
}

void simulate()
{
	double new_time = current_time_in_sec();
	double frame_time = new_time - current_time;
	if (frame_time <= 0.0f) return;
	if (frame_time > 0.25) frame_time = 0.25;
	current_time = new_time;

	accumulator += frame_time;

	while (accumulator >= dt)
	{
		//set previous state = current state
		//call integrate(current state, t, dt)
		scene_root.update(t, dt);
		t += dt;
		accumulator -= dt;
	}

	alpha = accumulator / dt;

	glutPostRedisplay();
}

void drawFrame()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	scene_root.draw(alpha);
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
