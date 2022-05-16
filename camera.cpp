#include "camera.h"


void Camera::moveUP(float upValue) {
	this->cameraPosVector += upValue * glm::normalize(this->upVector);
}

void Camera::moveFORWARD(float upValue) {	
	this->cameraPosVector += upValue*(this->centerVector - this->cameraPosVector);
	this->rotate(this->yaw, this->pitch, this->roll);
}

void Camera::moveRIGHT(float rightValue) {
	this->cameraPosVector += rightValue*glm::cross(glm::normalize(this->centerVector - this->cameraPosVector), this->upVector);
	this->rotate(this->yaw, this->pitch, this->roll);
}

void Camera::rotate(float yaw, float pitch, float roll) {
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.y = glm::sin(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

	this->centerVector = this->cameraPosVector + glm::normalize(direction);
}