#pragma once
#include "object.h"

class Light {
public:
	Object* shape;
	Light(glm::vec3 position, glm::vec3 color, Object* shape = nullptr) :
		position(position), color(color), shape(shape), attenuation(attenuation) {
	}

	void draw(Camera* c) {
		shape->draw(c);
	}

	std::vector<float> attenuation;

	glm::vec3 position;
	glm::vec3 color;
};


class DirectionalLight : public Light {
public:
	glm::vec3 direction;
	DirectionalLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, Object* shape = nullptr) :
		Light(position, color, shape), direction(direction) {}
};


class SpotLight : public Light {
public:
	glm::vec3 direction;
	float cutOff;

	SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, Object* shape = nullptr) :
		Light(position, color, shape), direction(direction) {}

};

class FlashLight : public SpotLight {
public:
	void updatePosition(glm::vec3 newPosition) {
		this->position = newPosition;
	}

	void updateDirection(glm::vec3 newDirection) {
		this->direction = newDirection;
	}

	FlashLight(glm::vec3 position, glm::vec3 color, glm::vec3 directiom, Object* shape = nullptr) :
		SpotLight(position, color, directiom, shape) {}

};
