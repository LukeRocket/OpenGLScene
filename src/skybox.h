#pragma once
#include <vector>
#include "cubeMap.h"
#include "shader.h"
#include "camera.h"

class Skybox
{
public:
	CubeMap* cMap;
	unsigned int VAO;
	unsigned int VBO;
	ShaderProgram* shaderProgram;

	Skybox(CubeMap * map, ShaderProgram * shaderProg) : cMap(map), shaderProgram(shaderProg) {
		updateVertices(100.0f);
	}

	void draw(Camera* c);

	void updateVertices(float cubeSideMultiplier);
};
