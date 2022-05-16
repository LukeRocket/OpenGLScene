#pragma once
#include <glad.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include "shader.h"
#include "variables.h"
#include "camera.h"
#include "texture.h"

// Vertex 
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uvCoords;
};


// Mesh 
class Mesh {
public:
	std::unordered_map<std::string, glm::mat4> transformationMatrices;	
	glm::vec3 startPosition;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int nVertices;
	std::vector<Texture> textures;


	Mesh(std::vector<Vertex> vertices = {}, std::vector<unsigned int> indices = {}, std::vector<Texture> textures = {}, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) :
		startPosition(position), nVertices(indices.size()), textures(textures) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// bind vertex buffer 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 
		// bind element buffer		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nVertices * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// link vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvCoords));
		glEnableVertexAttribArray(2);
	}

	/*~Mesh() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}*/

	void transform(glm::vec3 translation, glm::vec3 rotationAxes, float angle, glm::vec3 scale);
	void draw(ShaderProgram* shaderProg, Camera * c, std::vector<std::vector<glm::vec3>> lightsData);
};