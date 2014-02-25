#ifndef _mirabilis_entity_h_
#define _mirabilis_entity_h_
#include "location.h"
namespace mirabilis
{
	class entity
	{
		public:
		entity();
		entity(::location l);
		::location loc;
		unsigned int light_radius;
		bool visible;
	};
}
#endif
