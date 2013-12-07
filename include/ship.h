#ifndef _ship_h_
#define _ship_h_

#include "render_object.h"
#include "physics_object.h"

class ship: public render_object
{
	public:
	virtual void render();
	virtual void integrate(double, double);

	physics_state state;
	physics_derivative derivatives;
};

#endif
