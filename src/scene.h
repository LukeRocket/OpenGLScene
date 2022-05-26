#pragma once
#include <glad.h>
#include <glfw3.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "light.h"
#include "skybox.h"

class Scene
{
public:
	std::vector<Camera*> cameras;
	unsigned int activeCamIndex;
	bool lightsVisible;
	Skybox* skybox;

	Scene(const std::vector<Camera*> cams, std::vector<Object*>& objs, const std::vector<Light*> &lights, Skybox * skBox = nullptr, bool lightsVisible = false) :
	cameras(cams), objectCollection(objs), lightCollection(lights), lightsVisible(lightsVisible), skybox(skBox) {
		this->setActiveCameraIndex(0);
	}

	~Scene() {
		for (Object* obj : objectCollection) {
			delete obj;
		}

		for (Light* light : lightCollection) {
			delete light;
		}

		if (skybox) {
			delete skybox->cMap;
			delete skybox;
		}		
	}

	// executed each frame
	void update();

	std::vector<Object *> objectCollection;
	std::vector<Light *> lightCollection;	

	void setActiveCameraIndex(unsigned int index);
 };
