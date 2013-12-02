#ifndef _physics_state_h_
#define _physics_state_h_

#include "vector3f.h"
#include "quaternion.h"

class physics_state
{
	//primary
	quaternion orientation;
	vector3f angular_momentum;

	//secondary
	quaternion spin;
	vector3f angular_velocity;

	//constant
	double intertia;
	double inverse_inertia;

	void recalculate()
	{
		angular_velocity = angular_momentum * inverse_inertia;
		orientation.normalize();
		spin = 0.5f * quaternion(0, angular_velocity) * orientation;
	}
};

class physics_derivatives
{
	quaternion spin;
	vector3f torque;
};

#endif
