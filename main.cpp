/*
	TODOs:  
		- Fix the buffer destruction in mesh.h  (called by object  push_back in getNodeMeshes)

		- complete the Tutorial 
		+ fix the import of the fbx file 
*/

#include <glad.h>
#include <iostream>
#include <vector>
#include <string>
#include "screen.h"
#include "texture.h"
#include "scene.h"
#include "object.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "variables.h"


void run() {	
	
	/* WINDOW */
	Screen* screen = new Screen(WINDOW_W, WINDOW_H);
	glEnable(GL_DEPTH_TEST);
		
	/* SHADERS */
	std::unordered_map<GLenum, std::unordered_map<const char*, const char*>> paths = {
		{GL_VERTEX_SHADER,
			{
				{"path", "./shaders/vertex_shader.glsl"},
				{"errorLog", "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"}
			}
		},
		{GL_FRAGMENT_SHADER,
			{
				{"path", "./shaders/fragment_shader.glsl"},
				{"errorLog", "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"}
			}
		}
	};

	ShaderProgram* s_prog = new ShaderProgram(paths);

	paths = {
	{GL_VERTEX_SHADER,
		{
			{"path", "./shaders/light_vertex_shader.glsl"},
			{"errorLog", "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"}
		}
	},
	{GL_FRAGMENT_SHADER,
		{
			{"path", "./shaders/light_fragment_shader.glsl"},
			{"errorLog", "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"}
		}
	}
	};

	ShaderProgram* lightProg = new ShaderProgram(paths);

	/* SCENE */	
	std::string objectPath = "./resources/backpack/backpack.obj";

	Object* obj1 = new Object(objectPath, s_prog);
		
	Light* light = new Light(glm::vec3(0.0f, -2.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Light* light2 = new Light(glm::vec3(0.0f, -2.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f));

	std::vector<Object*> objCollection = {obj1};
	std::vector<Light*> lightCollection = {light2, light};
	Camera * camera = new Camera(glm::vec3(0.0, -5.0, -1.0),
								 glm::vec3(0.0, 0.0, 1.0),
								 glm::vec3(0.0, 1.0, 0.0));
	Scene* scene = new Scene({ camera }, objCollection, lightCollection, true);

	screen->setCurrentScene(scene);

	// infinite loop
	while (!glfwWindowShouldClose(screen->window)) {
		// rendering 		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
		scene->update();
		
		glfwSwapBuffers(screen->window); 
		glfwPollEvents();		 
	}

	glDeleteProgram(s_prog->shaderProgr);

	delete screen;
	delete scene;
	
	glfwTerminate();	
}

int main() {
	run();
	return 0;
}