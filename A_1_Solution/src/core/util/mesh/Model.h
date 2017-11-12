#pragma once

#include "Model.h"
#include <iostream>
#include <GLEW/glew.h>
#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model {
public:
	Model(const std::string & file_name);

	void load_model(const char* file_name);
	void draw();

	~Model();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Mesh> meshes;
};

