#include "screen.h"

// window key events
void Screen::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){		
	
	// priority to escape event
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else {					
		Screen * currentScreen = (Screen *)glfwGetWindowUserPointer(window);
		Camera* activeCamera = currentScreen->activeScene->cameras[currentScreen->activeScene->activeCamIndex];

		float upValue = 0.1f;
		if (action == GLFW_REPEAT || action == GLFW_PRESS) {
			// camera movements
			if (key == GLFW_KEY_W) {
				activeCamera->moveFORWARD(upValue);
			}
			// DOWN
			if (key == GLFW_KEY_S) {
				upValue *= -1;
				activeCamera->moveFORWARD(upValue);
			}

			// RIGHT
			float rightValue = 0.1f;
			if (key == GLFW_KEY_D) {
				activeCamera->moveRIGHT(rightValue);
			}
			// LEFT
			if (key == GLFW_KEY_A) {
				rightValue *= -1;
				activeCamera->moveRIGHT(rightValue);
			}

			// flashing background color
			if (key == GLFW_KEY_ENTER) { // change color 		
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			} else {
				glClearColor(.01f, .01f, .01f, 1.0f);
			}

			if (key == GLFW_KEY_SPACE) {
				activeCamera->returnToStartConfig();
			}
		}
		activeCamera->setViewMatrix();
	}
}


void Screen::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
	Screen* currentScreen = (Screen*)glfwGetWindowUserPointer(window);
	Camera* activeCamera = currentScreen->activeScene->cameras[currentScreen->activeScene->activeCamIndex];

	if (currentScreen->rotationLock) {
		if (currentScreen->firstMouseMove) {
			currentScreen->lastCursorPosition.x = (float)xPos;
			currentScreen->lastCursorPosition.y = (float)yPos;
			currentScreen->firstMouseMove = false;
		}
		float upValue = .01f * (-(float)yPos + currentScreen->lastCursorPosition.y);
		activeCamera->moveUP(upValue);
		float rightValue = .01f * ((float)xPos - currentScreen->lastCursorPosition.x);
		activeCamera->moveRIGHT(rightValue);
		currentScreen->lastCursorPosition.x = (float)xPos;
		currentScreen->lastCursorPosition.y = (float)yPos;
	} else {
		if (currentScreen->firstMouseMove) {
			currentScreen->lastCursorPosition.x = (float)xPos;
			currentScreen->lastCursorPosition.y = (float)yPos;
			currentScreen->firstMouseMove = false;
		}
		else {
			activeCamera->yaw += ((float)xPos - currentScreen->lastCursorPosition.x) * 0.1f;
			activeCamera->pitch += (-(float)yPos + currentScreen->lastCursorPosition.y) * 0.1f;

			if (activeCamera->pitch > 89.0f) {
				activeCamera->pitch = 89.0f;
			}
			else if (activeCamera->pitch < -89.0f) {
				activeCamera->pitch = -89.0f;
			}

			float roll = 0.0f;
			activeCamera->rotate(activeCamera->yaw, activeCamera->pitch, roll);
			currentScreen->lastCursorPosition.x = (float)xPos;
			currentScreen->lastCursorPosition.y = (float)yPos;
		}
	}
	activeCamera->setViewMatrix();
}

void Screen::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	Screen* currentScreen = (Screen*)glfwGetWindowUserPointer(window);
	Camera* activeCamera = currentScreen->activeScene->cameras[currentScreen->activeScene->activeCamIndex];
	float yOffsetsimple = (float)yOffset * 0.1f;
	activeCamera->moveFORWARD(yOffsetsimple);
	activeCamera->setViewMatrix();
}

void Screen::mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
	Screen* currentScreen = (Screen*)glfwGetWindowUserPointer(window);
	
	if (action == GLFW_PRESS) {
		currentScreen->rotationLock = true;
	}else if (action == GLFW_RELEASE) {
		currentScreen->rotationLock = false;
		currentScreen->firstMouseMove = true;
	}
	
}