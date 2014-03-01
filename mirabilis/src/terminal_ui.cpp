#include "terminal_ui.h"
#include <curses.h>
#include <string.h>

#include "input.h"

const int KEY_ESCAPE = 27;
const int KEY_EOF = 4;

namespace mirabilis
{
	terminal_view::terminal_view(model &game): view(game),
		viewport_x_dim(15), viewport_y_dim(10),
		viewport_x_offset(0), viewport_y_offset(0)
	{
		(void) initscr();
		keypad(stdscr, TRUE);
		(void) nonl();
		(void) cbreak;
		(void) noecho();
		curs_set(0);

		refresh();
		status_win = newwin(1, COLS, 0, 0);
		wrefresh(status_win);
		map_win = newwin(viewport_y_dim, viewport_x_dim, 1, 10);
		wrefresh(map_win);

		if (has_colors())
		{
			start_color();

			init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
			init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
			init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
			init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
			init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
			init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
			init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
			init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
		}
		display();

	}

	void terminal_view::display()
	{
		mvwaddstr(status_win,0,0,"hit Esc to quit");
		draw_map();
		draw_player();
		wrefresh(map_win);
		wrefresh(status_win);
	}

	void terminal_view::draw_map()
	{
		//only draw map characters inside viewport
		for (int x = 0; x < viewport_x_dim; ++x)
		{
			for (int y = 0; y < viewport_y_dim; ++y)
			{
				mvwaddch(map_win, y, x, char_from_model_obj(game.get_map_element(x+viewport_x_offset, y+viewport_y_offset)));
			}
		}
	}

	void terminal_view::draw_player()
	{
		::location player_loc = game.get_player_location();
		//player must be inside viewport
		if (player_loc.x + viewport_x_offset < viewport_x_dim && 
			player_loc.y + viewport_y_offset < viewport_y_dim)
		{
			mvwaddch(map_win, player_loc.y, player_loc.x, char_from_model_obj(visible_object::PLAYER));
		}
	}

	void terminal_view::cleanup()
	{
		endwin();
	}

	const char terminal_view::char_from_model_obj(visible_object::visible_object_t t) const
	{
		switch(t)
		{
			case visible_object::FLOOR:
				return '.';
			case visible_object::WALL:
				return '#';
			case visible_object::NOTHING:
				return ' ';
			case visible_object::PLAYER:
				return '@';
		}
		return ' ';
	};

	terminal_controller::terminal_controller() { }

	input terminal_controller::collect_input()
	{
		input::actionType action = input::INVALID;
		switch(getch())
		{
			case KEY_UP:
				action = input::PLAYER_MOVE_NORTH;
				break;
			case KEY_DOWN:
				action = input::PLAYER_MOVE_SOUTH;
				break;
			case KEY_LEFT:
				action = input::PLAYER_MOVE_WEST;
				break;
			case KEY_RIGHT:
				action = input::PLAYER_MOVE_EAST;
				break;
			case KEY_EOF:
			case KEY_ESCAPE:
				action = input::QUIT;
				break;
		}
		return input(action);
	}
}

