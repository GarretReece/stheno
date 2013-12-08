#ifndef _physics_object_h_
#define _physics_object_h_

#include "vector3f.h"
#include "quaternion.h"
#include "render_object.h"

struct physics_state
{
	physics_state();

	//primary
	vector3f position;
	vector3f momentum;
	quaternion orientation;
	vector3f angular_momentum;

	//secondary
	vector3f velocity;
	quaternion spin;
	vector3f angular_velocity;

	//constant
	float mass;
	float inverseMass;
	float inertia;
	float inverse_inertia;

	void recalculate();
};

struct physics_derivative
{
	vector3f velocity;
	vector3f force;

	quaternion spin;
	vector3f torque;
};

class physics_object : public render_object
{
	public:
	void integrate(physics_state &state, float t, float dt);
	physics_derivative evaluate(physics_state initial, float t, float dt, const physics_derivative &d);

	virtual void apply_forces(physics_state &state, float t, physics_derivative &output);

	virtual void update(float t, float dt);

	virtual void pre_render(float);
	virtual void post_render(float);

	virtual vector3f& translate();
	virtual quaternion& rotate();

	physics_state current, previous, interpolated;

};

physics_state interpolate(const physics_state &a, const physics_state &b, float alpha);
#endif
