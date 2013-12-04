#include "render_object.h"

render_object::render_object():
scale(1.0, 1.0, 1.0)
{ }

render_object::~render_object() { }

void render_object::draw()
{
	pre_render();
	render();
	for (std::list<render_object*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->draw();
	}
	post_render();
}

void render_object::pre_render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(scale[0], scale[1], scale[2]);
	glTranslatef(translate[0], translate[1], translate[2]);
	glMultMatrixf(rotate.to_matrix().data);
};

void render_object::post_render()
{
	glPopMatrix();
}

void render_object::render()
{
}

void render_object::add_child(render_object *child)
{
	children.push_back(child);
}

void render_object::remove_child(render_object *child)
{
	children.remove(child);
}
