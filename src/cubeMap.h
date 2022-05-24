#pragma once 
#include "texture.h" 
#include <vector>
#include <string>

class CubeMap : public Texture {
public:	
	unsigned int id;
	CubeMap(std::vector<std::string> paths);
};