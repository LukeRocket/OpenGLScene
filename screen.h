#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "camera.h"
#include "scene.h"

class Screen{
public:
	int w, h;
	GLFWwindow* window;
	Scene* activeScene;

	bool firstMouseMove = true;
	bool rotationLock = false;
	glm::vec2 lastCursorPosition = glm::vec2(0.0f, 0.0f);

	Screen(int width = 800, int height = 600) : w(width), h(height) {
		/// GLFW
		glfwInit();
		// context is OpenGL (remember the state machine concept)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// simpler OpenGL profile avoid past extensions ecc.
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// actual instanciation of the window
		window = glfwCreateWindow(w, h, "Draw project", NULL, NULL);
		if (window == NULL) {
			std::cout << "Error in the creation of the window" << std::endl;
			glfwTerminate();
			throw;
		}
		//make the context of our window the main context on the current thread
		glfwMakeContextCurrent(window);

		/* GLAD */
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "error in the GLAD initilization" << std::endl;
			throw;
		}
		
		// set default background color 
		glClearColor(.01f, .01f, .01f, 1.0f);

		// create camera		
		glfwSetWindowUserPointer(window, (void *)this);

		// set callbacks
		glfwSetFramebufferSizeCallback(window, sizeCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetScrollCallback(window, scrollCallback);		
		glfwSetScrollCallback(window, scrollCallback);
		glfwSetMouseButtonCallback(window, mouseClickCallback);
	}			


	void setCurrentScene(Scene *scene) {
		this->activeScene = scene;
	}

	static void sizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

	static void scrollCallback(GLFWwindow * window, double xOffset, double yOffset);

	static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
};


