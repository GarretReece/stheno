#ifndef _render_object_h_
#define _render_object_h_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <list>
#include "vector3f.h"
#include "quaternion.h"

class render_object
{
	public:
		render_object();
		virtual ~render_object();

		virtual void draw();
		virtual void pre_render();
		virtual void render();
		virtual void post_render();

		virtual void add_child(render_object *child);
		virtual void remove_child(render_object *child);

		vector3f translate;
		quaternion rotate;
		vector3f scale;

	private:
		std::list<render_object*> children;
};
#endif
