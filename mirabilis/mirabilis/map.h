#ifndef _mirabilis_map_h_
#define _mirabilis_map_h_

#include "location.h"
#include "misc.h"

namespace mirabilis
{
	class map
	{
		public:
		bool in_range(const ::location l) const;
		visible_object::visible_object_t get_element(const ::location l) const;
		bool is_lit(const ::location l) const;

		bool is_traversable(const ::location l) const;

		protected:
		
	};
}
#endif
