#ifndef _physics_object_h_
#define _physics_object_h_

#include "physics_state.h"

class physics_object
{
	public:
	void integrate(physics_state &state, float t, float dt);
	physics_derivative evaluate(const physics_state &initial, float t, float dt, const physics_derivative &dt);
}
#endif
