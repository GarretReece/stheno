#include <iostream>
#include <signal.h>

#include "model.h"
#include "input.h"
#include "view.h"
#include "terminal_ui.h"

int main()
{
	mirabilis::model game;
	mirabilis::terminal_view view(game);
	mirabilis::terminal_controller controller;

	while(game.playing())
	{
		view.display();
		game.apply_input(controller.collect_input());
	}

	view.cleanup();
	return 0;
}
