#ifndef _mirabilis_input_h_
#define _mirabilis_input_h_

namespace mirabilis
{

class input
{
	public:
	enum actionType
	{
		FIRST = 0,
		INVALID = 0,
		QUIT,
		MOVEMENT_FIRST,
		PLAYER_MOVE_NORTH = MOVEMENT_FIRST,
		PLAYER_MOVE_SOUTH,
		PLAYER_MOVE_EAST,
		PLAYER_MOVE_WEST,
		PLAYER_MOVE_NORTHEAST,
		PLAYER_MOVE_NORTHWEST,
		PLAYER_MOVE_SOUTHEAST,
		PLAYER_MOVE_SOUTHWEST,
		MOVEMENT_LAST = PLAYER_MOVE_SOUTHWEST,
		LAST
	};

	actionType action;

	input(actionType a): action(a) {}

};


}
#endif
