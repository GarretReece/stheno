#include <iostream>
#include <signal.h>

#include "mirabilis/model.h"
#include "mirabilis/input.h"
#include "mirabilis/view.h"
#include "mirabilis/terminal_ui.h"

int main()
{
	mirabilis::model game;
	mirabilis::terminal_view view(game);
	mirabilis::terminal_controller controller(game);

	while(game.playing())
	{
		view.display();
		game.apply_input(controller.collect_input());
	}

	view.cleanup();
	return 0;
}
