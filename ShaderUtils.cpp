#include "./ShaderUtils.h"

std::string readShaderFile_(const char * path) {
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	shaderFile.open(path);
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();
	return shaderStream.str();	
}

void testShader(unsigned int shader, std::string errorMsg) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << errorMsg << infoLog << std::endl;
	}
}
