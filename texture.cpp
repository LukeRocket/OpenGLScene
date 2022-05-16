#include "texture.h"

unsigned char* Texture::loadImage(std::string path, int &width, int &height, int &channels) {
	stbi_set_flip_vertically_on_load(true);
	// do not specify the default number of channels
	return stbi_load(path.c_str(), &width, &height, &channels, 0);
}