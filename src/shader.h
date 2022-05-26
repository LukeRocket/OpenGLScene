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

	ShaderProgram(const std::unordered_map<GLenum, std::unordered_map<const char*, const char *>> &paths) {
		std::vector<unsigned int > shaders = {};
		shaderProgr = glCreateProgram();

		for (auto const &p : paths) {	
			std::string tempShaderString = readShaderFile_(p.second.at("path"));
			const char * shaderSource = tempShaderString.c_str();
			unsigned int shader = glCreateShader(p.first);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);
			testShader(shader, p.second.at("errorLog"));
			glAttachShader(shaderProgr, shader);
			shaders.push_back(shader);
		}		
				
		glLinkProgram(shaderProgr);
		testShader(shaderProgr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		
		for (unsigned int s : shaders)
			glDeleteShader(s);

		// link camera uniform buffer obj
		unsigned int blockIndex = glGetUniformBlockIndex(shaderProgr, "cameraMatrices");
		glUniformBlockBinding(shaderProgr, blockIndex, 0);
	}

	
	template<typename T, typename F>
	void sendMatrixUniforms(std::unordered_map<std::string, T> attrs, F sender, int nPerAttr) {
		if (!attrs.empty()) {
			for (auto const attr : attrs) {
				unsigned int transfLoc = glGetUniformLocation(this->shaderProgr, attr.first.c_str());
				sender(transfLoc, nPerAttr, GL_FALSE, glm::value_ptr(attr.second));
			}
		}
	}

	template<typename T, typename F>
	void sendVecUniforms(std::unordered_map<std::string, T> attrs, F sender, int nPerAttr) {
		if (!attrs.empty()) {
			for (auto const attr : attrs) {
				unsigned int transfLoc = glGetUniformLocation(this->shaderProgr, attr.first.c_str());
				sender(transfLoc, nPerAttr, glm::value_ptr(attr.second));
			}
		}
	}

	template<typename T, typename F>
	void sendMonodimUniforms(std::string attrName, T attr, F sender) {
		unsigned int transfLoc = glGetUniformLocation(this->shaderProgr, attrName.c_str());
		sender(transfLoc, attr);
	}

	void use();
};

