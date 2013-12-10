#include "ship.h"

ship::ship(sprite* spr):
	spr(spr)
{
}
void ship::render(float)
{
	//glColor3f(0.3, 0.3, 0.8);
	if (spr)
	{
		//sprite render?
		const GLfloat texVerts[] = {
			0, 0,
			1, 0, 
			1, 1,
			0, 1
		};
		glBindTexture(GL_TEXTURE_2D, spr->texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
	}
	const GLfloat verts[] = {
		16, 32,
		16,-32,
		-16, 32,
		-16, -32
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glDrawArrays(GL_QUAD_STRIP, 0, 4);
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
