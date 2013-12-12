#include "render_object.h"

render_object::render_object(sprite *spr):
spr(spr),
active(true),
_scale(1.0, 1.0, 1.0)
{ }

render_object::~render_object() { }

void render_object::draw(float alpha)
{
	pre_render(alpha);
	if (active) render(alpha);
	draw_children(alpha);
	post_render(alpha);
}

void render_object::draw_children(float alpha)
{
	for (std::list<render_object*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->draw(alpha);
	}
}

void render_object::pre_render(float)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	vector3f sc = scale(), tr = translate();
	quaternion ro = rotate();
	glMultMatrixf(ro.to_matrix().data);
	glTranslatef(tr[0], tr[1], tr[2]);
	glScalef(sc[0], sc[1], sc[2]);
};

void render_object::post_render(float)
{
	glPopMatrix();
}

void render_object::render(float alpha)
{
}

void render_object::update(float t, float dt)
{
	update_children(t, dt);
}

void render_object::update_children(float t, float dt)
{
	for (std::list<render_object*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		(*iter)->update(t,dt);
	}
}

void render_object::add_child(render_object *child)
{
	children.push_back(child);
}

void render_object::remove_child(render_object *child)
{
	children.remove(child);
}

vector3f &render_object::translate()
{
	return _translate;
}

quaternion &render_object::rotate()
{
	return _rotate;
}

vector3f &render_object::scale()
{
	return _scale;
}
