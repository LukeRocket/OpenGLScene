#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 transform;
//uniform mat4 view;
//uniform mat4 project;


layout (std140) uniform cameraMatrices 
{
	mat4 project;
	mat4 view;
};


void main()
{	
	gl_Position = project * view * transform * vec4(position, 1.0f);			
} 