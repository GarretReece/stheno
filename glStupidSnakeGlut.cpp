#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <list>
#include <sys/time.h>


void drawFrame();
void initPositions();

const int nPoints = 32;
int wX = 256 << 1;
int wY = 256 << 1;
int count = -1;
bool bDown = false;		//is left mouse button down?
timeval last_frame_time;
double frame_time = 1000000.0 / 60.0;

struct pVect {
	short x,y;
	pVect(short px, short py) : x(px),y(py) { }
	pVect(const pVect &in) : x(in.x), y(in.y) { }
	void copy(const pVect& in) {x = in.x; y = in.y;}
	void pos() { 
		if (x < 0) x *= -1; 
		if (y < 0) y *= -1; 
		if (x >= wX) x = (wX << 1) - 1 - x; 
		if (y >= wY) y = (wY << 1) - y - 1; 
	}
};

pVect bVect(128,128);	//bVect is the mouse coords

std::list<pVect> pList;

double diff_in_micros(timeval &a, timeval &b)
{
	double result = a.tv_sec - b.tv_sec;
	result *= 1000000;
	result += a.tv_usec - b.tv_usec;
	return result;
}

void initPositions() {
	srand(time(0));
	pVect input(128,128);
	pList.push_back(input);
	for (int i = 0; i < nPoints - 1; i++) {
		//input.copy(*pList.end());
		input.x += rand() % 4 - 2;
		input.y += rand() % 4 - 2;
		input.pos();
		pList.push_back(input);
	}
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
	gluOrtho2D(0,wX,wY,0);	//swap around x axis to make windows and openGL coords match
}

void drawFrame() {

	timeval t;
	gettimeofday(&t, 0);

	if (diff_in_micros(t, last_frame_time) < frame_time) return;

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
		glVertex2s(1,1);
		glVertex2s(wX-1,1);
		glVertex2s(wX-1,wY-1);
		glVertex2s(1,wY-1);
		glVertex2s(1,1);
	glEnd();


	int j,k;
	float color = 0.0;
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for (std::list<pVect>::iterator iter = pList.begin(); 
			iter != pList.end(); 
			++iter, color += (1.0 / (float)nPoints)) {
		j = iter->x;
		k = iter->y;
		glColor3f(1.0 - color,0.0,color);
		glVertex2s(iter->x,iter->y);
	}
	glEnd();
	
	pList.pop_front();
	pVect foo(pList.back());
	if (bDown) {
		foo.x += (rand() % 16) * (foo.x - bVect.x < 0 ? 1 : -1);
		foo.y += (rand() % 16) * (foo.y - bVect.y < 0 ? 1 : -1);
	} else {
		foo.x += (rand() % 32) - 16;
		foo.y += (rand() % 32) - 16;
	}
	foo.pos();
	pList.push_back(foo);
	glutSwapBuffers();
	gettimeofday(&last_frame_time, 0);
}

void processKeys(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
}

void processMouseClicks(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) bDown = state == GLUT_DOWN;
}

void processMouseMovement(int x, int y)
{
	bVect.x = x;
	bVect.y = y;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(wX, wY);
	glutCreateWindow("GLUT Tutorial");

	initPositions();
	gettimeofday(&last_frame_time, 0);

	glutDisplayFunc(drawFrame);
	glutReshapeFunc(changeSize);
	glutMotionFunc(processMouseMovement);
	glutPassiveMotionFunc(processMouseMovement);
	glutMouseFunc(processMouseClicks);
	glutIdleFunc(drawFrame);
	glutMainLoop();
	return 1;
}
