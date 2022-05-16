#pragma once
#include <glad.h>
#include <glfw3.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "light.h"


class Scene
{
public:
	std::vector<Camera*> cameras;
	unsigned int activeCamIndex;
	bool lightsVisible;

	Scene(std::vector<Camera*> cams, std::vector<Object*> objs = {}, std::vector<Light*> lights = {}, bool lightsVisible = false) :
	cameras(cams), objectCollection(objs), lightCollection(lights), lightsVisible(lightsVisible) {
		this->setActiveCamera(0);
	}

	~Scene() {
		for (Object* obj : objectCollection) {
			delete obj;
		}

		for (Light* light : lightCollection) {
			delete light;
		}
	}

	// executed each frame
	void update();

	std::vector<Object *> objectCollection;
	std::vector<Light *> lightCollection;	

	void setActiveCamera(unsigned int index);
 };
