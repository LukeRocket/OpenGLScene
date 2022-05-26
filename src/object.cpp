#include "object.h"
#include <assert.h>

void Object::draw(Camera* c, std::vector<std::vector<glm::vec3>> lightsData) {
	// temp solution
	for (Mesh mesh : meshes) {
		mesh.draw(this->shaderProgram, c, lightsData);
	}
}

void Object::load(const std::string & path) {
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||!scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}	

	// get root node
	this->getNodeMeshes(scene->mRootNode, scene);
}

std::vector<Texture> Object::convertAssimpToTexture(aiMaterial * material, const aiTextureType & type) {
	std::vector<Texture> textures = {};

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString textureLocation;
		material->GetTexture(type, i, &textureLocation);
		std::string path(this->objDirectory + textureLocation.C_Str());

		bool skip = false;
		for (auto& text : loadedTextures) {
			if (std::strcmp(text.first.c_str(), path.c_str()) == 0) {
				textures.push_back(text.second);
				skip = true;
				break;
			}
		}

		if (!skip) {
			// load image
			Texture t = Texture(path.c_str());
			textures.push_back(t);
			loadedTextures[path] = t;
		}					
	}
	return textures;
}

Mesh Object::convertAssimpToMesh(aiMesh * mesh, aiMaterial ** materials) {
	// vertices
	std::vector<Vertex> vertices = {};
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;		
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if (mesh->HasNormals())
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);			
		if (mesh->mTextureCoords[0])
			vertex.uvCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);	

		vertices.push_back(vertex);		
	}

	// indices 
	std::vector<unsigned int> indices = {};
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//textures
	std::vector<Texture> textures = {};

	if(mesh->mMaterialIndex >= 0) {
		aiMaterial * material = materials[mesh->mMaterialIndex];

		std::vector<Texture> meshTextures = this->convertAssimpToTexture(material, aiTextureType_DIFFUSE);			
		textures.insert(textures.end(), meshTextures.begin(), meshTextures.end());
		meshTextures = this->convertAssimpToTexture(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), meshTextures.begin(), meshTextures.end());
	}
	return Mesh(vertices, indices, textures);
}

void Object::getNodeMeshes(aiNode *node, const aiScene * scene) {	
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->convertAssimpToMesh(mesh, scene->mMaterials));
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		getNodeMeshes(node->mChildren[i], scene);
	}
}