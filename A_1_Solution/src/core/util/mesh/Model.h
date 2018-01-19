#pragma once

#include "Model.h"
#include <iostream>
#include <GLEW/glew.h>
#include <vector>
#include "Mesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class LightingShader;

struct Material {
	glm::vec3 ambient_color = glm::vec3(0.0f);
	glm::vec3 diffuse_color = glm::vec3(0.0f);
	glm::vec3 specular_color = glm::vec3(0.0f);
	float shininess = 0.0f;
	Texture* diffuse_texture = nullptr;
};

class Model {
public:
	const std::string file_name;

	Model(const std::string & file_name = "models/cube.obj");

	void load_model(const char* file_name);
	void draw(LightingShader* shader_program = nullptr, GLenum mode = GL_TRIANGLES);

	~Model();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	void load_texture(int i, const aiMaterial* pMaterial, aiTextureType texture_type);
	Texture* texture_is_loaded(std::string full_path);

	std::vector<Mesh> meshes;
	std::vector<Texture*> textures; // TODO; Work on this to not repeat textures, this has to be global not model dependent. If a texture is already loade why load it again? IDEA: AssetManager
	std::vector<Material> materials;
};

