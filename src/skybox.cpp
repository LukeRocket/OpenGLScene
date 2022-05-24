#include "skybox.h"

void Skybox::updateVertices(float cubeSideMultiplier) {

    float skyboxVertices[] = {
        // positions          
        -cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,

        -cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,
        -cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
        -cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,

         cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,

        -cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,
        -cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,

        -cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier,  cubeSideMultiplier,
        -cubeSideMultiplier,  cubeSideMultiplier, -cubeSideMultiplier,

        -cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier, -cubeSideMultiplier,
        -cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier,
         cubeSideMultiplier, -cubeSideMultiplier,  cubeSideMultiplier
    };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);    
}


void Skybox::draw(Camera* c) {
	shaderProgram->sendMatrixUniforms(true,
		std::unordered_map<std::string, glm::mat4>{ { "view", c->getViewMatrix()},
		                            				{ "project", c->getProjMatrix() }}, glUniformMatrix4fv, 1);	

	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cMap->id);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}