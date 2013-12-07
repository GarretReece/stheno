#ifndef _physics_object_h_
#define _physics_object_h_

class physics_state
{
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
	float intertia;
	float inverse_inertia;

	void recalculate()
	{
		velocity = momentum * inverseMass;

		angular_velocity = angular_momentum * inverse_inertia;
		orientation.normalize();
		spin = 0.5f * quaternion(0, angular_velocity) * orientation;
	}
};

class physics_derivative
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

	void apply_forces(physics_state &state, float t, physics_derivative &output);

	void update_physics(float t, float dt);
	virtual void pre_render();
	virtual void render();

	physics_state current, previous;
};
#endif
