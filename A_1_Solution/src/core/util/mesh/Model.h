#pragma once

#include "Model.h"
#include <iostream>
#include <GLEW/glew.h>
#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class Model {
public:
	const std::string file_name;

	Model(const std::string & file_name);

	void load_model(const char* file_name);
	void draw(GLenum mode = GL_TRIANGLES);

	~Model();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Mesh> meshes;
	std::vector<Texture*> textures;
	std::vector<Texture> loaded_textures; // TODO; Work on this to not repeat textures
};

