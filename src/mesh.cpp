#include "mesh.h"

void Mesh::transform(glm::vec3 translation, glm::vec3 rotationAxes, float angle, glm::vec3 scale) {
	// include transforms
	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 normalTransform = glm::mat4(1.0f);

	if (!glm::all(glm::lessThan(glm::abs(translation), glm::vec3(EPSILON))))
		transform = glm::translate(transform, translation);
	if (abs(angle) > EPSILON)
		transform = glm::rotate(transform, angle, rotationAxes);
	if (!glm::all(glm::lessThan(glm::abs(scale), glm::vec3(EPSILON))))
		transform = glm::scale(transform, scale);

	normalTransform = glm::transpose(glm::inverse(transform));

	this->transformationMatrices = {
		{"transform", transform},
		{"normalTransform", normalTransform}
	};
}

void Mesh::draw(ShaderProgram* shaderProg, Camera* c, std::vector<std::vector<glm::vec3>> lightsData, Skybox *skybox) {
	shaderProg->use();
	// temp solution	
	shaderProg->sendMatrixUniforms(this->transformationMatrices, glUniformMatrix4fv, 1);
	// view
	/*shaderProg->sendMatrixUniforms(
		std::unordered_map<std::string, glm::mat4>{ { "view", c->getViewMatrix()},
													{ "project", c->getProjMatrix() }}, glUniformMatrix4fv, 1);*/

	glm::vec3 lightPosition = c->cameraPosVector;
	if (lightsData[0].size() > 0) {
		lightPosition = lightsData[0][0];
		int nLights = (int)lightsData[0].size();
		glm::vec3* position = &lightsData[0][0];
		glm::vec3* color = &lightsData[1][0];

		// send lights data 
		for (int i = 0; i < lightsData[0].size(); i++) {
			// todo: find a better way to implement this
			shaderProg->sendVecUniforms(
				std::unordered_map<std::string, glm::vec3>{ {"lightsLocations[" + std::to_string(i) + "]", position[i]},
															{ "lightsColors[" + std::to_string(i) + "]", color[i] }}, glUniform3fv, 1);
		}

		// send camera coords
		shaderProg->sendVecUniforms(std::unordered_map<std::string, glm::vec3>{ {"cameraCoords", c->cameraPosVector}}, glUniform3fv, 1);
	}


	// passing mesh textures 
	for(int i = 0; i < this->textures.size(); i++){
		glActiveTexture(GL_TEXTURE0 + i);
		std::string shdVarName = "textureMap" + std::to_string(i);	
		glUniform1i(glGetUniformLocation(shaderProg->shaderProgr, shdVarName.c_str()), i);			
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);		
	}

	// passing skybox 
	if (skybox) {		
		glActiveTexture(GL_TEXTURE0 + this->textures.size());
		glUniform1i(glGetUniformLocation(shaderProg->shaderProgr, "skybox"), this->textures.size());
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->cMap->id);
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->nVertices, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_POINTS, this->nVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);	
}
