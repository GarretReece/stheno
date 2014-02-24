#ifndef _mirabilis_player_h_
#define _mirabilis_player_h_

#include "entity.h"
#include "location.h"

namespace mirabilis
{
	class player: public entity
	{
		public:
		player();
		player(::location l);
		int vision_range;
	};
}

#endif
