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
#include "sprite.h"

class render_object
{
	public:
		render_object(sprite *spr = NULL);
		virtual ~render_object();

		virtual void draw(float alpha = 1.0f);
		virtual void draw_children(float alpha);

		virtual void pre_render(float);
		virtual void render(float);
		virtual void post_render(float);

		virtual void update(float, float);
		virtual void update_children(float, float);

		virtual void add_child(render_object *child);
		virtual void remove_child(render_object *child);

		virtual vector3f& translate();
		virtual quaternion& rotate();
		virtual vector3f& scale();
	
		bool active;

		sprite *spr;

	private:
		std::list<render_object*> children;
		vector3f _translate;
		quaternion _rotate;
		vector3f _scale;
};
#endif
