#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "quaternion.h"
quaternion cameraQuaternion;
vector3f cameraPosition(0,0,0);
vector3f cameraVelocity(0,0,0);

#include <iostream>
#include <sys/time.h>

double current_time_in_sec()
{
	timeval a;
	gettimeofday(&a, 0);
	return (double)a.tv_sec + (double)(a.tv_usec/1000000.0);
}

double last_camera_write_time = 0.0;

double last_camera_update_time = 0.0;
const double camera_update_period = 0.0166667f;
const double camera_rotate_speed = 2.0f*3.14159/20.0;
const double camera_slide_speed = 0.5f;

const int BAD_MOUSE = 0x7fff;
int old_mouse_x = BAD_MOUSE, old_mouse_y = BAD_MOUSE;

quaternion rot = quaternion::from_axis(vector3f(0,0,1), camera_update_period * camera_rotate_speed);

GLfloat light_position[] = { 0.0, 3.0, 1.0, 0.0 };

void init()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 3.0, 1.0, 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

int count = 0;
int spin = 0;
void display()
{
	if ((current_time_in_sec() - last_camera_update_time) < camera_update_period)
	{
		return;
	}
	cameraPosition += cameraVelocity*camera_update_period;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glMultMatrixf(cameraQuaternion.to_matrix().data);

	glColor3f(0.3, 0.3, 0.8);
	glutSolidTeapot(0.75);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(cameraPosition[0],cameraPosition[1],cameraPosition[2]);
	glRotated((GLdouble) spin, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.1);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glutSwapBuffers();
}

void mouseMoved(int x, int y)
{
	if (old_mouse_x == BAD_MOUSE && old_mouse_y == BAD_MOUSE)
	{
		old_mouse_x = x;
		old_mouse_y = y;
		return;
	}
	double dx = old_mouse_x - x;
	double dy = old_mouse_y - y;

	old_mouse_x = x;
	old_mouse_y = y;

	vector3f axisY(0, 1, 0);
	vector3f axisX(1, 0, 0);

	float sensitivity = 0.005f;
	quaternion q1 = quaternion::from_axis(axisY, dx*sensitivity);
	quaternion q2 = quaternion::from_axis(axisX, -dy*sensitivity);
	cameraQuaternion = cameraQuaternion * q2;
	cameraQuaternion = q1 * cameraQuaternion;
	//quaternion m = q1 * q2;
	//quaternion j = m * cameraQuaternion;
	//j.normalize();
	//cameraQuaternion = j;
}

void processMouseClicks(int button, int state, int x, int y)
{
	std::cout << "mouseClick: " << button << "," << state << std::endl;
	if (button == 3 && state == GLUT_DOWN)
		cameraPosition[2] += 1.0f;
	if (button == 4 && state == GLUT_DOWN)
		cameraPosition[2] -= 1.0f;
}

void pressKey(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP: cameraVelocity[2] += camera_slide_speed; break;
		case GLUT_KEY_DOWN: cameraVelocity[2] -= camera_slide_speed; break;
		case 'r': 
			cameraPosition = vector3f(0,0,0);
			cameraQuaternion = quaternion(1,0,0,0);
			break;
	}
}

void releaseKey(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP: cameraVelocity[2] -= camera_slide_speed; break;
		case GLUT_KEY_DOWN: cameraVelocity[2] += camera_slide_speed; break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512);
	glutCreateWindow("SHIPS");

	init();

	cameraQuaternion = quaternion(1, 0, 0, 0);

	last_camera_write_time = current_time_in_sec();
	last_camera_update_time = last_camera_write_time;

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutPassiveMotionFunc(mouseMoved);
	glutMouseFunc(processMouseClicks);
	glutIdleFunc(display);

	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutMainLoop();
	return 1;
}
