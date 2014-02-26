#include "model.h"

using namespace mirabilis;

model::model(): m_playing(true), 
	m_player(::location(1,1,1))
{
}

void model::apply_input(input i)
{
	if (i.action >= input::MOVEMENT_FIRST && i.action <= (int)input::MOVEMENT_LAST)
	{
		::location delta(0,0,0);
		switch(i.action)
		{
		case input::PLAYER_MOVE_NORTH:
			delta = ::location(0, -1, 0);
			break;
		case input::PLAYER_MOVE_SOUTH:
			delta = ::location(0,1,0);
			break;
		case input::PLAYER_MOVE_EAST:
			delta = ::location(1,0,0);
			break;
		case input::PLAYER_MOVE_WEST:
			delta = ::location(-1,0,0);
			break;
		}
		if (player_can_move(delta)) m_player.loc += delta;
		return;
	}

	switch (i.action)
	{
		case input::QUIT:
			m_playing = false;
			break;
		default:
			break;
	}
}

::location model::get_player_location() const
{
	return m_player.loc;
}

bool model::player_can_move(::location delta) const
{
	return m_map.is_traversable(get_player_location() + delta);
}

bool model::player_can_see(::location l) const
{
	location diff = get_player_location() - l;
	double mag = diff.magnitude();
	return mag < m_player.vision_range;
}

visible_object::visible_object_t model::get_map_element(::location l) const
{
	if (!m_map.in_range(l)) return visible_object::NOTHING;
	if (!player_can_see(l)) return visible_object::NOTHING;
	return m_map.get_element(l);
}

visible_object::visible_object_t model::get_map_element(int x, int y, int z) const
{
	return get_map_element(location(x,y,z));
}

