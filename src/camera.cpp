#include "camera.h"

void Camera::moveUP(float upValue) {	
	this->cameraPosVector = glm::translate(glm::mat4(1.0f), upValue * this->getCameraUp()) * glm::vec4(this->cameraPosVector, 1.0f);
	this->rotate(this->yaw, this->pitch, this->roll);
}

void Camera::moveFORWARD(float forwardValue) {
	this->cameraPosVector += forwardValue * (this->centerVector - this->cameraPosVector);
	this->rotate(this->yaw, this->pitch, this->roll);
}

void Camera::moveRIGHT(float rightValue) {
	//this->cameraPosVector += rightValue*glm::cross(glm::normalize(this->centerVector - this->cameraPosVector), this->upVector);
	//this->rotate(this->yaw, this->pitch, this->roll);
	this->cameraPosVector = glm::translate(glm::mat4(1.0f), rightValue * this->getCameraRight()) * glm::vec4(this->cameraPosVector, 1.0f);
	this->rotate(this->yaw, this->pitch, this->roll);
}

void Camera::rotate(float yaw, float pitch, float roll) {
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.y = glm::sin(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

	this->centerVector = this->cameraPosVector + glm::normalize(direction);	
}

glm::vec3 Camera::getCameraDirection() {
	return  glm::normalize(this->cameraPosVector - this->centerVector);
}

glm::vec3 Camera::getCameraRight() {
	return glm::normalize(glm::cross(this->upVector, this->Camera::getCameraDirection()));
}

glm::vec3 Camera::getCameraUp(){
	return glm::cross(this->getCameraDirection(), this->getCameraRight());
}