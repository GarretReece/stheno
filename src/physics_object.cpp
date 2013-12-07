#include "phyics_objects.h"

physics_derivative physics_object::evaluate(physics_state state, float t, float dt, const physics_derivative &d)
{
	state.position += d.velocity * dt;
	state.velocity += d.force * dt;
	state.orientation += d.spin * dt;
	state.angularMomentum += d.torque * dt;
	state.recalculate();

	physics_derivative output;
	output.velocity = state.velocity;
	output.spin = state.spin;
	apply_forces(state, t+dt, output);
	return output;
}

void physics_object::integrate(physics_state &state, float t, float dt)
{
	physics_derivative a = evaluate(state, t, 0.0f, physics_derivative());
	physics_derivative b = evaluate(state, t, dt*0.5f, a);
	physics_derivative c = evaluate(state, t, dt*0.5f, b);
	physics_derivative d = evaluate(state, t, dt, c);

	state.position += dt * 1.0f/6.0f * (a.velocity + 2.0f*(b.velocity + c.velocity) + d.velocity);
	state.momentum += dt * 1.0f/6.0f * (a.force + 2.0f*(b.force + c.force) + d.force);

	state.orientation += dt * 1.0f/6.0f * (a.spin + 2.0f*(b.spin + c.spin) + d.spin);
	state.angularMomentum += dt * 1.0f/6.0f * (a.torque + 2.0f*(b.torque + c.torque) + d.torque); 

	state.recalculate();
}

void physics_object::update_physics(float t, float dt)
{
	previous = current;
	integrate(current, t, dt);
}

void physics_object::pre_render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(scale[0], scale[1], scale[2]);
}
