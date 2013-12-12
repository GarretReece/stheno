#ifndef _keylistener_h_
#define _keylistener_h_

struct key_state
{
	bool up_arrow;
	bool down_arrow;
	bool left_arrow;
	bool right_arrow;
};

class keylistener
{
	public:
	keylistener(key_state &k);
	key_state const &keys;
};
#endif
