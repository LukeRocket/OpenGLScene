#pragma once
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <vector>
#include <unordered_map>
#include "shader.h"
#include "camera.h"
#include "variables.h"
#include "texture.h" 
#include "mesh.h"


class Object
{
public:
	std::unordered_map<std::string, Texture> loadedTextures = {};
	std::string objDirectory;


	Object(std::string path, ShaderProgram *shaderProg) : shaderProgram(shaderProg){
		this->objDirectory = path.substr(0, path.find_last_of('/') + 1);
		this->load(path);		
	}
	
	std::vector<Mesh> meshes;
	ShaderProgram* shaderProgram = nullptr;
	std::vector<Texture*> textures = {};

	void draw(Camera* c, std::vector<std::vector<glm::vec3>> lightsData = {});
	void load(std::string path);
	void getNodeMeshes(aiNode * node, const aiScene * scene);
	//converters
	Mesh convertAssimpToMesh(aiMesh* mesh, aiMaterial ** sceneMeterials);
	std::vector<Texture> convertAssimpToTexture(aiMaterial* material, aiTextureType type);
};
