#include "entity.h"

namespace mirabilis
{
	entity::entity(): loc(0,0,0), light_radius(0), visible(true) { }

	entity::entity(::location l): loc(l), light_radius(0), visible(true) { }
}
