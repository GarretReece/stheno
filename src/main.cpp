#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>

#include <iostream>
#include <sys/time.h>

#include "ship.h"
#include "render_object.h"
#include "quaternion.h"
#include "player.h"

int wX = 1024, wY = 768;
render_object scene_root;

double t = 0.0;
const double dt = 0.01;

double current_time, accumulator = 0.0;

float alpha = 1.0f;

key_state keys;

player *p;

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

	scene_root.translate() += vector3f(wX/2, wY/2, 0);

	sprite *spr = new sprite("sprites/rocket.bmp");

	p = new player(keys, spr);
	p->translate() += vector3f(50,0,0);
	//s->rotate() = quaternion::from_axis(vector3f(0, 0, 1), 2.0f*3.1415f);
	//s->scale() *= 0.25f;
	scene_root.add_child(p);

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

	quaternion player_orientation = p->rotate();
	vector3f player_pos = p->current.velocity;
	printf("pos(%.2f,%.2f,%.2f)   rot(%f,%f,%f,%f)\r", player_pos[0],player_pos[1],player_pos[2],player_orientation.w,player_orientation.x,player_orientation.y,player_orientation.z);

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

void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == 27)
	{
		exit(0);
	}
}

void pressKey(int key, int xx, int yy)
{
	switch(key)
	{
		case GLUT_KEY_UP: keys.up_arrow = true; break;
		case GLUT_KEY_DOWN: keys.down_arrow = true; break;
		case GLUT_KEY_RIGHT: keys.right_arrow = true; break;
		case GLUT_KEY_LEFT: keys.left_arrow = true; break;
	}
}

void releaseKey(int key, int xx, int yy)
{
	switch(key)
	{
		case GLUT_KEY_UP: keys.up_arrow = false; break;
		case GLUT_KEY_DOWN: keys.down_arrow = false; break;
		case GLUT_KEY_RIGHT: keys.right_arrow = false; break;
		case GLUT_KEY_LEFT: keys.left_arrow = false; break;
	}
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
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	//glutMotionFunc(processMouseMovement);
	//glutPassiveMotionFunc(processMouseMovement);
	//glutMouseFunc(processMouseClicks);
	glutIdleFunc(simulate);
	glutMainLoop();
	return 1;
}
