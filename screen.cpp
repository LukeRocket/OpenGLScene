#include "screen.h"

// window key events
void Screen::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){		
	
	// priority to escape event
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else {	
		// flashing background color
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) { // change color 		
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		} else {
			glClearColor(.01f, .01f, .01f, 1.0f);
		}	

		// camera movements
		// UP
		Screen * currentScreen = (Screen *)glfwGetWindowUserPointer(window);

		Camera* activeCamera = currentScreen->activeScene->cameras[currentScreen->activeScene->activeCamIndex];

		float upValue = 0.1f;
		if (action == GLFW_REPEAT || action == GLFW_PRESS) {

			if (key == GLFW_KEY_W) { // change color wwwwwwww					
				activeCamera->moveUP(upValue);
			}
			// DOWN
			if (key == GLFW_KEY_S) {
				activeCamera->moveUP(-upValue);
			}

			// RIGHT
			float rightValue = 0.1f;
			if (key == GLFW_KEY_D) { // change color 		
				activeCamera->moveRIGHT(rightValue);
			}
			// LEFT
			if (key == GLFW_KEY_A) {
				activeCamera->moveRIGHT(-rightValue);
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

		activeCamera->moveUP(.1f*(-(float)yPos + currentScreen->lastCursorPosition.y));
		activeCamera->moveRIGHT(.1f*((float)xPos - currentScreen->lastCursorPosition.x));
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

			activeCamera->rotate(activeCamera->yaw, activeCamera->pitch, 0.0f);
			currentScreen->lastCursorPosition.x = (float)xPos;
			currentScreen->lastCursorPosition.y = (float)yPos;
		}
	}
	activeCamera->setViewMatrix();
}

void Screen::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	Screen* currentScreen = (Screen*)glfwGetWindowUserPointer(window);
	Camera* activeCamera = currentScreen->activeScene->cameras[currentScreen->activeScene->activeCamIndex];
	activeCamera->moveFORWARD(yOffset);
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