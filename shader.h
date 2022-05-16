#pragma once
#include <glad.h>
#include <string>
#include <vector>
#include <unordered_map>`
#include "ShaderUtils.h"
#include <glm/gtc/type_ptr.hpp>


class ShaderProgram
{
public:	
	unsigned int shaderProgr;

	ShaderProgram(std::unordered_map<GLenum, std::unordered_map<const char*, const char *>> paths) {
		std::vector<unsigned int > shaders = {};
		for (auto const &p : paths) {	
			std::string tempShaderString = readShaderFile_(p.second.at("path"));
			const char * shaderSource = tempShaderString.c_str();
			unsigned int shader = glCreateShader(p.first);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);
			testShader(shader, p.second.at("errorLog"));
			shaders.push_back(shader);
		}		
		shaderProgr = glCreateProgram();
		for (unsigned int s : shaders) 		
			glAttachShader(shaderProgr, s);

		glLinkProgram(shaderProgr);
		testShader(shaderProgr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		
		for (unsigned int s : shaders)
			glDeleteShader(s);
	}

	
	template<typename T, typename F>
	void sendMatrixUniforms(bool activateProgram, std::unordered_map<std::string, T> attrs, F sender, int nPerAttr) {
		if (activateProgram)
			glUseProgram(this->shaderProgr);

		if (!attrs.empty()) {
			for (auto const attr : attrs) {
				unsigned int transfLoc = glGetUniformLocation(this->shaderProgr, attr.first.c_str());
				sender(transfLoc, nPerAttr, GL_FALSE, glm::value_ptr(attr.second));
			}
		}
	}

	template<typename T, typename F>
	void sendVecUniforms(bool activateProgram, std::unordered_map<std::string, T> attrs, F sender, int nPerAttr) {
		if (activateProgram)
			glUseProgram(this->shaderProgr);

		if (!attrs.empty()) {
			for (auto const attr : attrs) {
				unsigned int transfLoc = glGetUniformLocation(this->shaderProgr, attr.first.c_str());
				sender(transfLoc, nPerAttr, glm::value_ptr(attr.second));
			}
		}
	}

	template<typename T, typename F>
	void sendMonodimUniforms(bool activateProgram,  std::string attrName, T attr, F sender) {
		if (activateProgram)
			glUseProgram(this->shaderProgr);	
		unsigned int transfLoc = glGetUniformLocation(this->shaderProgr, attrName.c_str());
		sender(transfLoc, attr);
	}

};

