#ifndef _mirabilis_model_h_
#define _mirabilis_model_h_

#include <string>
#include "player.h"
#include "location.h"
#include "input.h"
#include "map.h"
#include "misc.h"

namespace mirabilis
{

class model
{
	public:
	model();
	void interact(input &i);
	void apply_input(input);
	bool playing() const { return m_playing; }
	::location get_player_location() const;

	visible_object::visible_object_t get_map_element(::location l) const;
	visible_object::visible_object_t get_map_element(int x, int y, int z = 0) const;

	protected:
	bool player_can_move(::location l) const;
	bool player_can_see(::location l) const;

	private:
	bool m_playing;
	player m_player;
	map m_map;
};

}
#endif
