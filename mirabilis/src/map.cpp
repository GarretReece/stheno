#include "map.h"

const char hidden_map_element = ' ';
const int map_x_max = 14, map_x_min = 0;
const int map_y_max = 9, map_y_min = 0;
const char *map_chars[] = 
{
	"###############",
	"#   #    #    #",
	"#   # #       #",
	"###     #  ## #",
	"#  #        # #",
	"#     #   # # #",
	"#         # # #",
	"#      #  # ###",
	"#         #   #",
	"###############",
};



namespace mirabilis
{
	bool map::in_range(const ::location l) const
	{
		return l.x <= map_x_max && l.x >= map_x_min && l.y >= map_y_min && l.y <= map_y_max;
	}

	visible_object::visible_object_t map::get_element(const ::location l) const
	{
		if (in_range(l))
		{
			switch(map_chars[l.y][l.x])
			{
				case '#':
					return visible_object::WALL;
				case ' ':
					return visible_object::FLOOR;
			}
		}
		return visible_object::NOTHING;
	}

	bool map::is_lit(const ::location l) const
	{
		return true;
	}

	bool map::is_traversable(const ::location l) const
	{
		return get_element(l) == visible_object::FLOOR;
	}

}
