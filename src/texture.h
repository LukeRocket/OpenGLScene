#pragma once
#include <glad.h>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
	unsigned int id;
	int w, h;

	Texture() {}

	Texture(unsigned char * image_data, int width, int height, int channels = 3): w(width), h(height) {
		// generate texture
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		// settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		if (image_data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, (channels == 3) ? GL_RGB : GL_RED, width, height, 0, (channels == 3) ? GL_RGB:GL_RED, GL_UNSIGNED_BYTE, image_data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}	
	}

	Texture(std::string path) {
		int width, height, channels;
		unsigned char* data = loadImage(path, width, height, channels);
		*this = Texture::Texture(data, width, height, channels);
		// free image data memory 
		stbi_image_free(data);
	}

	unsigned char* loadImage(std::string path, int & width, int & height, int & channels, bool flip = true);		
};
