#ifndef _ship_h_
#define _ship_h_

#include "render_object.h"
#include "physics_object.h"
#include "sprite.h"

class ship: public physics_object
{
	public:
	ship(sprite *spr=NULL);
	virtual void render(float);
	virtual void apply_forces(physics_state &state, float t, physics_derivative &output);

	private:
	sprite *spr;

};

#endif
