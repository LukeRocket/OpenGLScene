#version 330 core

in vec3  textureCoords;
uniform samplerCube textureSampler;

out vec4 fragColor;

void main(){
	fragColor = texture(textureSampler, textureCoords);
}