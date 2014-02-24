
#ifndef _mirabilis_view_h_
#define _mirabilis_view_h_

#include "model.h"

namespace mirabilis
{
	class view
	{
		public:
		view(model &game): game(game) { }
		virtual void display() = 0;
		virtual void cleanup() = 0;
		protected:
		model &game;
	};
}
#endif
