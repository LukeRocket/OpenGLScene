#version 330 core
layout (location=0) in vec3 aPos;

out vec3 textureCoords;

layout (std140) uniform cameraMatrices 
{
	mat4 project;
	mat4 view;
};


//uniform mat4 project;
//uniform mat4 view;

void main(){
	textureCoords = aPos;
	vec4 position = project * view * vec4(aPos, 1.0);
	gl_Position = position.xyww;	
}