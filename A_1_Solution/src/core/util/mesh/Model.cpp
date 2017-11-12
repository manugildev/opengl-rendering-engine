#include "Model.h"

Model::Model(const std::string & file_name) { this->load_model(file_name.c_str()); }

void Model::load_model(const char* file_name) {
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(file_name, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// Process ASSIMP's root node recursively
	this->processNode(scene->mRootNode, scene);
}

void Model::draw() {
	for (GLuint i = 0; i < this->meshes.size(); i++) {
		this->meshes[i].draw();
	}
}


void Model::processNode(aiNode* node, const aiScene* scene) {
	// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		// The node object only contains indices to index the actual objects in the scene.
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coord;

		// Positions
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));

		// Normals
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		
		// Texture Coordinates
		if (mesh->mTextureCoords[0]) { // Does the mesh contain texture coordinates?
			tex_coord.x = mesh->mTextureCoords[0][i].x;
			tex_coord.y = mesh->mTextureCoords[0][i].y;
		} else {
			tex_coord = glm::vec2(0.0f, 0.0f);
		}
		Vertex vertex(position, tex_coord, normal);
		vertices.push_back(vertex);
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	
	return Mesh(vertices, indices);
}

Model::~Model() {}