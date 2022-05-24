#include "texture.h"

unsigned char* Texture::loadImage(std::string path, int &width, int &height, int &channels, bool flip) {	
	stbi_set_flip_vertically_on_load(flip);
	// do not specify the default number of channels
	return stbi_load(path.c_str(), &width, &height, &channels, 0);
}