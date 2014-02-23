#include "sprite.h"

#include <stdio.h>

#ifdef GL_BGR
const bool needs_bgr_swap = false;
#else
const bool needs_bgr_swap = true;
#endif

GLuint load_bitmap(const char *);

sprite::sprite(const char *filename)
{
	texture = load_bitmap(filename);
}


GLuint load_bitmap(const char *filename)
{
	GLuint texture;

	FILE *file = fopen(filename, "rb");
	if (NULL == file)
	{
		printf("unable to open %s\n", filename);
		return 0; //TODO: raise exception
	}

	unsigned char header[54];
	unsigned int dataPos, imageSize, width, height;
	unsigned char *data;

	if (fread(header, 1, 54, file) != 54)
	{
		printf("%s not a valid bmp\n", filename);
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		return 0;
	}

	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	if (imageSize == 0) imageSize = width*height*3;
	if (dataPos == 0) dataPos = 54;

	fseek(file, dataPos, SEEK_SET);

	data = new unsigned char[imageSize];

	int total_read = 0;

	total_read = fread(data, 1, imageSize, file);

	while (total_read < imageSize)
	{
		total_read += fread(&data[total_read], 1, imageSize-total_read, file);
	}

	fclose(file);

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );

#ifdef GL_BGR
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
#else
	for (int i = 0; i < imageSize; i += 3)
	{
		unsigned char t = data[i];
		data[i] = data[i+2];
		data[i+2] = t;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	delete data;

	return texture;
}
