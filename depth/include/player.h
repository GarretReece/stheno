#ifndef _player_h_
#define _player_h_

#include "ship.h"
#include "keylistener.h"

class player : public ship, public keylistener
{
	public:
	player(key_state &k, sprite *spr);
	virtual void apply_forces(physics_state &state, float t, physics_derivative &output);
};
#endif
