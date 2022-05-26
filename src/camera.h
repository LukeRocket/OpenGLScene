#pragma once
#include <glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "variables.h"

class Camera
{
public:
	glm::vec3 upVector;
	glm::vec3 cameraPosVector;
	glm::vec3 centerVector;		

	unsigned int cameraMatricesUBO;

	float yaw;
	float pitch;
	float roll;
	
	Camera(const glm::vec3 & cameraPosition, const glm::vec3 & center, const glm::vec3 & up) :
		upVector(up), cameraPosVector(cameraPosition), centerVector(center) {		
		// generate UBO
		glGenBuffers(1, &cameraMatricesUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, cameraMatricesUBO);
		glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4), NULL, GL_STATIC_DRAW); 
		// unbind
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, cameraMatricesUBO, 0, 2*sizeof(glm::mat4));				
		
		this->setViewMatrix();
		this->setProjMatrix();

		glm::vec3 direction = glm::normalize(this->centerVector - this->cameraPosVector);		
		// init yaw, pitch and roll
		this->pitch = glm::degrees(glm::asin(direction.y));
		this->yaw = glm::degrees(glm::acos(direction.x / glm::cos(glm::radians(this->pitch))));
		this->roll = 0.0f;

		startPositionConfig = { this->cameraPosVector, this->centerVector, this->upVector};
		startRotationConfig = { this->pitch, this->yaw, this->roll };
	}

	void returnToStartConfig() {
		this->cameraPosVector = this->startPositionConfig[0];
		this->centerVector = this->startPositionConfig[1];
		this->upVector = this->startPositionConfig[2];

		this->pitch = this->startRotationConfig[0];
		this->yaw = this->startRotationConfig[1];
		this->roll = this->startRotationConfig[2];
	}

	void setViewMatrix(glm::vec3 *cameraPosition = nullptr,
							glm::vec3 *center = nullptr, glm::vec3 *up = nullptr) {
		if (!cameraPosition || !center || !up) {
			cameraPosition = &cameraPosVector;
			center = &centerVector;
			up = &upVector;
		}
		viewMatrix = glm::lookAt(*cameraPosition, *center, *up);
		// send view matrix subdata 
		glBindBuffer(GL_UNIFORM_BUFFER, cameraMatricesUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMatrix));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void setProjMatrix() {
		projectionMatrix = glm::perspective(FOV, (float)WINDOW_W / WINDOW_H, NEAR, FAR);
		// send projection matrix subdata 
		glBindBuffer(GL_UNIFORM_BUFFER, cameraMatricesUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	
	glm::mat4 getViewMatrix() { return this->viewMatrix; }
	glm::mat4 getProjMatrix() { return this->projectionMatrix; }

	void moveUP(float &value);
	void moveFORWARD(float &value);
	void moveRIGHT(float &value);

	void rotate(float &yaw, float &pitch, float &roll);

	glm::vec3 getCameraDirection();
	glm::vec3 getCameraRight();
	glm::vec3 getCameraUp();
private:
	std::vector<glm::vec3> startPositionConfig;
	std::vector<float> startRotationConfig;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};
