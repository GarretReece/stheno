#include "player.h"

namespace mirabilis
{
	player::player(): entity::entity(), vision_range(4) { }

	player::player(::location l): entity::entity(l), vision_range(4) { }

}
