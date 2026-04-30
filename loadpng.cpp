#include "stdafx.h"

// C&P
// Introduction to OpenGL ES 2.0 by a Kevin
// http://www.codesampler.com/2010/11/02/introduction-to-opengl-es-2-0/

unsigned int Load_PNG_Texture(char* filename, int* width, int* height)
{
	//
	// Load and decode a PNG file so we can make a texture out of it.
	//

	std::vector< unsigned char > rawImage;
	LodePNG::loadFile(rawImage, filename);

	LodePNG::Decoder decoder;
	std::vector< unsigned char > image;
	decoder.decode( image, rawImage.empty() ? 0 : &rawImage[0],
				(unsigned)rawImage.size() );

	if (height != 0)
		*height = decoder.getHeight();
	if (width != 0)
		*width = decoder.getWidth();
	
	//
	// Create the OpenGL texture and fill it with our PNG image.
	//
	
	unsigned int uiTexture;

	// Allocates one texture handle
	glGenTextures( 1, &uiTexture );

	// Binds this texture handle so we can load the data into it
	glBindTexture( GL_TEXTURE_2D, uiTexture );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, decoder.getWidth(),
				  decoder.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				  &image[0] );

	return uiTexture;
}