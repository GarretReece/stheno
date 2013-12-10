#include "sprite.h"

#include <stdio.h>

const unsigned int PIXEL_WIDTH = 3;

sprite::sprite(const char *filename, unsigned int height, unsigned int width):
	height(height), width(width)
{
	FILE *file = fopen(filename, "rb");
	if (NULL == file)
	{
		return; //TODO: raise exception
	}
	unsigned char *data = new unsigned char[width*height*PIXEL_WIDTH]();
	unsigned int total_read = 0;
	int data_read = fread(data, width*height*PIXEL_WIDTH, 1, file);
	while (data_read != 0 && (total_read+data_read) < width*height*PIXEL_WIDTH)
	{
		total_read += data_read;
		data_read = fread(data, (width*height*PIXEL_WIDTH)-total_read, 1, file);
	}
	fclose(file);
	for (int i = 0; i < width*height; ++i)
	{
		int index = i*3;
		unsigned char B = data[index];
		data[index] = data[index+2];
		data[index+2] = B;
	}
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

}
