#version 330 core

const int nLights = 2;

uniform vec3 lightsLocations[nLights];
uniform vec3 lightsColors[nLights];

uniform samplerCube skybox;
uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
uniform vec3 cameraCoords;

in COORDS_OUT{
	vec2 textureCoords;
	vec3 normalCoords;
	vec3 fragPosition;
} coords_in;

out vec4 FragColor;

void main()
{					
	// skybox reflection
	/*vec3 I = normalize(-cameraCoords + coords_in.fragPosition);
	vec3 R1 = reflect(I, normalize(coords_in.normalCoords));	
	vec3 R2 = refract(I, normalize(coords_in.normalCoords), 0.658);	
	vec4 reflColor = mix(texture(skybox, R1),texture(skybox, R2), 0.2);*/

	vec4 ambientLightColor = vec4(0.25, 0.25, 0.25, 1.0) * texture(textureMap0, coords_in.textureCoords);
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0);

	for (int i = 0; i < nLights; i++){	
		vec3 lightDirection = normalize(lightsLocations[i] - coords_in.fragPosition);			
		vec3 reflRayDirection = reflect(-lightDirection, normalize(coords_in.normalCoords));
		vec4 diffuse = max(dot(lightDirection, normalize(coords_in.normalCoords)), 0.0f) * vec4(lightsColors[i], 1.0f) * texture(textureMap0, coords_in.textureCoords);
		vec4 reflection = pow(max(dot(reflRayDirection, normalize(cameraCoords-coords_in.fragPosition)), 0.0f), 135.0f) * vec4(lightsColors[i], 1.0f) *  vec4(vec3(texture(textureMap1, coords_in.textureCoords).r), 1.0f);
		//finalColor += (reflection + diffuse + ambientLightColor);		
		finalColor = clamp(finalColor + (reflection + diffuse + ambientLightColor), 0.0, 1.0);
	}

	FragColor =  finalColor;			
	/*if (gl_FrontFacing && gl_FragCoord.x < 400){
		FragColor =  finalColor;			
	}else{
		FragColor =  vec4(1.0, 0.5, 0.6, 1.0);			
		//FragColor =  reflColor;			
	}*/
}