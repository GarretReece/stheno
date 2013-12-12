#include "player.h"

player::player(key_state &k, sprite *spr):
	ship(spr),
	keylistener(k)
{
}

void player::apply_forces(physics_state &state, float t, physics_derivative &output)
{
	if (!keys.up_arrow && keys.down_arrow)
	{
		output.force = state.orientation * vector3f(0, 1.0f, 0) * -10.0f;
		output.force[0] *= -1;
	}
	if (keys.up_arrow && !keys.down_arrow)
	{
		output.force = state.orientation * vector3f(0, 1.0f, 0) * 10.0f;
		output.force[0] *= -1;
	}
	if (!keys.left_arrow && keys.right_arrow)
	{
		output.torque = vector3f(0, 0, -1);
	}
	if (keys.left_arrow && !keys.right_arrow)
	{
		output.torque = vector3f(0, 0, 1); 
	}
}
