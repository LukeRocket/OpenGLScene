#version 330

#define MAX_VERTICES 27

in COORDS_OUT{
	vec2 textureCoords;
	vec3 normalCoords;
	vec3 fragPosition;
} coords[];

out COORDS_OUT{
	vec2 textureCoords;
	vec3 normalCoords;
	vec3 fragPosition;
} coords_out;

layout (triangles) in;
layout (triangle_strip, max_vertices=MAX_VERTICES) out;

void main(){
	for(int i =0 ; i < MAX_VERTICES; i++){
		gl_Position = gl_in[0].gl_Position  + vec4(i * 10.0, 0.0, 0.0, 1.0);
		coords_out.textureCoords = coords[0].textureCoords;
		coords_out.normalCoords = coords[0].normalCoords;
		coords_out.fragPosition = coords[0].fragPosition + vec3(i * 10.0, 0.0, 0.0);
		EmitVertex();
		gl_Position = gl_in[1].gl_Position  + vec4(i * 10.0, 0.0, 0.0, 1.0);
		coords_out.textureCoords = coords[1].textureCoords;
		coords_out.normalCoords = coords[1].normalCoords;
		coords_out.fragPosition = coords[1].fragPosition + vec3(i * 10.0, 0.0, 0.0);
		EmitVertex();
		gl_Position = gl_in[2].gl_Position  + vec4(i * 10.0, 0.0, 0.0, 1.0);
		coords_out.textureCoords = coords[2].textureCoords;
		coords_out.normalCoords = coords[2].normalCoords;
		coords_out.fragPosition = coords[2].fragPosition + vec3(i * 10.0, 0.0, 0.0);
		EmitVertex();
		EndPrimitive();	
	}
}