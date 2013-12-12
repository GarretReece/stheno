#include "ship.h"
#include <limits>

ship::ship(sprite* spr):
	physics_object(spr),
	max_velocity(std::numeric_limits<double>::infinity()),
	max_angular_velocity(std::numeric_limits<double>::infinity())
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
	if (state.velocity.length() > max_velocity) state.velocity = state.velocity.normalize() * max_velocity;

	if (output.velocity.length() > max_velocity) output.velocity = output.velocity.normalize() * max_velocity;

	if (state.angular_velocity[2] > max_angular_velocity) state.angular_velocity[2] = max_angular_velocity;
	if (state.angular_momentum[2] > max_angular_velocity) state.angular_momentum[2] = max_angular_velocity;
}
