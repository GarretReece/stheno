#ifndef _sprite_h_
#define _sprite_h_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class sprite
{
	public:
	sprite(const char *filename);

	unsigned int height, width;

	GLuint texture;

};

#endif
