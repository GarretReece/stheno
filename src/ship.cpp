#include "ship.h"

void ship::render(float)
{
	glColor3f(0.3, 0.3, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(50, 0.0);
		glVertex2f(0.0, 100);
		glVertex2f(0.0, -25);
		glVertex2f(-50, 0.0);
	glEnd();
}

void ship::apply_forces(physics_state &state, float t, physics_derivative &output)
{

}
