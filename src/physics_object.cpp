#include "physics_object.h"

physics_state::physics_state():
	orientation(quaternion::rotation_identity),
	mass(1),
	inverseMass(1),
	inertia(1),
	inverse_inertia(1)
{
}

void physics_state::recalculate(void)
{
	velocity = momentum * inverseMass;

	angular_velocity = angular_momentum * inverse_inertia;
	orientation.normalize();
	spin = 0.5f * quaternion(0, angular_velocity) * orientation;
}

physics_state interpolate(const physics_state &a, const physics_state &b, float alpha)
{
	physics_state state = b;
	state.position = a.position*(1-alpha) + b.position*alpha;
	state.momentum = a.momentum*(1-alpha) + b.momentum*alpha;
	state.orientation = a.orientation.slerp(b.orientation, alpha);
	state.angular_momentum = a.angular_momentum*(1-alpha) + b.angular_momentum*alpha;
	state.recalculate();
	return state;
}

physics_derivative physics_object::evaluate(physics_state state, float t, float dt, const physics_derivative &d)
{
	state.position += d.velocity * dt;
	state.velocity += d.force * dt;
	state.orientation += d.spin * dt;
	state.angular_momentum += d.torque * dt;
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
	state.angular_momentum += dt * 1.0f/6.0f * (a.torque + 2.0f*(b.torque + c.torque) + d.torque); 

	state.recalculate();
}

void physics_object::update(float t, float dt)
{
	previous = current;
	integrate(current, t, dt);
	update_children(t, dt);
}

void physics_object::pre_render(float alpha)
{
	interpolated = interpolate(previous, current, alpha);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	vector3f sc = scale();

	glTranslatef(interpolated.position[0], interpolated.position[1], interpolated.position[2]);
	glMultMatrixf(interpolated.orientation.to_matrix().data);
	glScalef(sc[0], sc[1], sc[2]);
}

void physics_object::post_render(float alpha)
{
	glPopMatrix();
}

vector3f& physics_object::translate()
{
	return current.position;
}

quaternion& physics_object::rotate()
{
	return current.orientation;
}

void physics_object::apply_forces(physics_state &state, float t, physics_derivative &output)
{
}

