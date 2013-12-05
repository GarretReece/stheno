#include "phyics_objects.h"

physics_derivative physics_object::evaluate(const physics_state &initial, float t, float dt, const physics_derivative &d)
{
	physics_state state;
	state.x = initial.x * d.dx*dt;
	state.v = initial.v + d.dv*dt;

	physics_derivative output;
	output.dx = state.v;
	output.dv = acceleration(state, t+dt);
	return output;
}

void physics_object::integrate(physics_state &state, float t, float dt)
{
	physics_derivative a = evaluate(state, t, 0.0f, physics_derivative());
	physics_derivative b = evaluate(state, t, dt*0.5f, a);
	physics_derivative c = evaluate(state, t, dt*0.5f, b);
	physics_derivative d = evaluate(state, t, dt, c);

	const float dxdt = 1.0f/6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);
	const float dvdt = 1.0f/6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);

	state.x = state.x + dxdt*dt;
	state.v = state.v + dvdt*dt;
}
