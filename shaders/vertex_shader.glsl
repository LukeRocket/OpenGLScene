#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureUV;
uniform mat4 transform;

//uniform mat4 view;
//uniform mat4 project;

uniform mat4 normalTransform;


layout (std140) uniform cameraMatrices 
{
	mat4 project;
	mat4 view;
};

// passing block of variables from vertex to fragment shader 
out COORDS_OUT{
	vec2 textureCoords;
	vec3 normalCoords;
	vec3 fragPosition;
} coords_out;

void main()
{	
	coords_out.fragPosition = vec3(transform * vec4(position, 1.0f));
	gl_Position = project * view * vec4(coords_out.fragPosition, 1.0f);		
	coords_out.textureCoords = vec2(textureUV.xy);	
	coords_out.normalCoords = mat3(normalTransform) * normal;
} 