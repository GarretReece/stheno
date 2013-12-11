#include "ship.h"

ship::ship(sprite* spr):
	spr(spr)
{
}
void ship::render(float)
{
	const GLfloat verts[] = {
		16, -32,
		-16,-32,
		16, 32,
		-16, 32
	};

	glVertexPointer(2, GL_FLOAT, 0, verts);
	if (spr)
	{
		const GLfloat texVerts[] = {
			1, 0, 
			0, 0,
			1, 1,
			0, 1,
		};
		glBindTexture(GL_TEXTURE_2D, spr->texture);
		glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ship::apply_forces(physics_state &state, float t, physics_derivative &output)
{
	
}
