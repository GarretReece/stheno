#ifndef _mirabilis_terminal_view_h_
#define _mirabilis_terminal_view_h_

#include "view.h"
#include <curses.h>

namespace mirabilis
{
	class terminal_view: public view
	{
		public:
		terminal_view(model &game);
		void display();
		void cleanup();
		
		protected:
		void draw_map();
		void draw_player();
		int viewport_x_dim, viewport_y_dim;
		int viewport_x_offset, viewport_y_offset;

		const char char_from_model_obj(visible_object::visible_object_t t) const;

		WINDOW *map_win, *status_win;
	};

	class terminal_controller
	{
		public:
		terminal_controller(model &g);
		input collect_input();
		private:
		model &game;
	};

}

#endif
