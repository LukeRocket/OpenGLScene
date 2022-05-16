#include "scene.h"

void Scene::update(){
	// apply transformations
	for (int i = 0; i < this->objectCollection.size(); i++) {
		for (Mesh &m : this->objectCollection[i]->meshes){
			//m.transform(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.5f, 0.0f, 1.0f), (float)glfwGetTime(), glm::vec3(10.0f, 10.0f, 10.0f));
			m.transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 1.0f), (float)glfwGetTime(), glm::vec3(.8f, .8f, .8f));
		}		
	}

	std::vector<std::vector<glm::vec3>> lightsData = { {}, {} };
	for (int i = 0; i < this->lightCollection.size(); i++) {
		if (this->lightCollection[i]->shape) {
			this->lightCollection[i]->shape->meshes[0].transform(this->lightCollection[i]->position, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(0.2f, 0.2f, 0.2f));
		}
		// get lights position and color 
		lightsData[0].push_back(this->lightCollection[i]->position);
		lightsData[1].push_back(this->lightCollection[i]->color);
	}

	// send to shader
	for (Object* obj : this->objectCollection) {
		obj->draw(this->cameras[this->activeCamIndex], lightsData);
	}

	if (lightsVisible) {
		for (Light* light : this->lightCollection) {
			if (light->shape) {
				light->draw(this->cameras[this->activeCamIndex]);
			}
		}
	}
}


void Scene::setActiveCamera(unsigned int index) {
	activeCamIndex = index;
}