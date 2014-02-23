#ifndef _physics_obj_2d_h_
#define _physics_obj_2d_h_

struct physics_state_2d
{
	physics_state_2d();

	vector2f position;
	vector2f momentum;
	float bearing;
	float angular_momentum;

	vector2f velocity;
	float angular_velocity;

	vector2f force;
	double angular_force;
}

class physics_object_2d: public render_object
{
	public:
	physics_object_2d(sprite *spr = NULL);
	void integrate(physics_state_2d &state, float t, float dt);
	physics_derivative_2d evaluate(physics_state_2d initial, float t, float dt, const physics_derivative_2d &d);

	virtual void apply_forces(physics_state_2d &state, float t, physics_derivative &output);

	virtual void update(float t, float dt);

	virtual void pre_render(float);
	virtual void post_render(float);

	virtual vector3f& translate();
	virtual quaternion& rotate();

	physics_state_2d current, previous, interpolated;
};
#endif
