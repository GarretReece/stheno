#include "ship.h"

void ship::render(float)
{
	glColor3f(0.3, 0.3, 0.8);
	GLfloat verts[] = {
		50.0f, 0.0f,
		0.0f, 100.0f,
		0.0f, -25.0f,
		-50.0f,0.0f};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	/*glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(50, 0.0);
		glVertex2f(0.0, 100);
		glVertex2f(0.0, -25);
		glVertex2f(-50, 0.0);
	glEnd();*/
}

void ship::apply_forces(physics_state &state, float t, physics_derivative &output)
{

}
