#include "Model.h"

#include "..\util\Util.h"
#include "..\shaders\lighting\LightingShader.h"
#include <glm\ext.hpp>
Model::Model(const std::string & file_name) :file_name(file_name) {
	this->load_model(file_name.c_str());
}

void Model::load_model(const char* file_name) {
	// Read file via ASSIMP
	const aiScene *scene = aiImportFile(file_name, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {    ///Deterimine if the scene is null, if there was an error reading, or if the first node is blank
		std::cout << file_name << " had error reading: " << file_name << ":" << aiGetErrorString() << std::endl;
		return;
	}
	// Process ASSIMP's root node recursively
	aiApplyPostProcessing(scene, aiProcess_CalcTangentSpace);
	this->processNode(scene->mRootNode, scene);
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

	/* Process Materials */
	if (scene->mNumMaterials == 0) {
		Material mat;
		mat.ambient_color = glm::vec3(1);
		mat.diffuse_color = glm::vec3(1);
		mat.specular_color = glm::vec3(1);
		mat.shininess = 0;
		mat.shininess_strengh = 0;

		MaterialTextures mT;
		mT.diffuse_texture = new Texture();
		mT.diffuse_texture->load();
		mT.normal_texture = new Texture(DEFAULT_NORMAL_MAP);
		mT.normal_texture->load();
		textures.push_back(mT);

		mat.diffuse_texture = mT.diffuse_texture;
		mat.normal_texture = mT.normal_texture;
		materials.push_back(mat);
		return;
	}

	/* Process Materials */
	for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = scene->mMaterials[i];
		aiColor4D ambient_color = aiColor4D(1, 1, 1, 1);
		aiColor4D diffuse_color = aiColor4D(1, 1, 1, 1);
		aiColor4D specular_color = aiColor4D(1, 1, 1, 1);
		float shininess = 0;
		float shininess_strengh = 0;

		aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_AMBIENT, &ambient_color);
		aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &diffuse_color);
		aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_SPECULAR, &specular_color);
		aiGetMaterialFloat(pMaterial, AI_MATKEY_SHININESS, &shininess);
		aiGetMaterialFloat(pMaterial, AI_MATKEY_SHININESS_STRENGTH, &shininess_strengh);
		if (shininess == 0) shininess = 1;

		//std::cout << shininess_strengh << std::endl;

		//std::cout << "Has Materials " << file_name << " " << scene->HasMaterials() << std::endl;

		// TODO: Save colors
		// TODO: Add more Texture Types
		MaterialTextures mT;
		mT.normal_texture = new Texture(DEFAULT_NORMAL_MAP);
		mT.normal_texture->load();

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			mT.diffuse_texture = load_texture(i, pMaterial, aiTextureType_DIFFUSE);
		}
		else {
			// There is no texture > we load the white pixel texture
			mT.diffuse_texture = new Texture();
			mT.diffuse_texture->load();
		}

		if (pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0) {
			mT.normal_texture = load_texture(i, pMaterial, aiTextureType_HEIGHT);
		}
		else {
			mT.normal_texture = new Texture(DEFAULT_NORMAL_MAP);
			mT.normal_texture->load();
		}

		textures.push_back(mT);

		// TODO: Check if maybe there is no material in the texture, and set a default one.
		Material mat;
		mat.ambient_color = glm::vec3(ambient_color.r, ambient_color.g, ambient_color.b);
		mat.diffuse_color = glm::vec3(diffuse_color.r, diffuse_color.g, diffuse_color.b);
		mat.specular_color = glm::vec3(specular_color.r, specular_color.g, specular_color.b);
		mat.shininess = shininess;
		mat.shininess_strengh = shininess_strengh;
		mat.diffuse_texture = mT.diffuse_texture;
		mat.normal_texture = mT.normal_texture;
		materials.push_back(mat);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {

	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coord;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		// Positions
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;

		// Normals
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) { // Does the mesh contain texture coordinates?
			tex_coord.x = mesh->mTextureCoords[0][i].x;
			tex_coord.y = mesh->mTextureCoords[0][i].y;

			tangent.x = mesh->mTangents[i].x;
			tangent.y = mesh->mTangents[i].y;
			tangent.z = mesh->mTangents[i].z;

			bitangent.x = mesh->mBitangents[i].x;
			bitangent.y = mesh->mBitangents[i].y;
			bitangent.z = mesh->mBitangents[i].z;
		}
		else {
			tex_coord = glm::vec2(0.0f, 0.0f);
			tangent = glm::vec3(0.0f, 0.0f, 0.0f);
			bitangent = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		Vertex vertex(position, tex_coord, normal, tangent, bitangent);
		vertices.push_back(vertex);
	}

	// Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	/* We create the Mesh that we are going to return */
	Mesh result_mesh(vertices, indices);
	result_mesh.set_material_index(mesh->mMaterialIndex);
	return result_mesh;
}

Texture* Model::load_texture(int i, const aiMaterial* pMaterial, aiTextureType texture_type) {
	std::string dir = Util::get_dir_by_path(file_name);
	aiString path;

	TextureType t_type;
	if (texture_type == aiTextureType_HEIGHT) t_type = NORMAL_TEXTURE;
	else t_type = DIFFUSE_TEXTURE;

	if (pMaterial->GetTexture(texture_type, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
		std::string full_path = dir + "/" + path.data;

		Texture* t_loaded = texture_is_loaded(full_path);
		if (t_loaded) return t_loaded;
		else {
			Texture* new_texture = new Texture(full_path.c_str());
			if (new_texture->load() == -1) {
				printf("Error loading texture '%s', loading the white pixel texture instead.\n", full_path.c_str());
				new_texture = new Texture();
			}
			new_texture->set_texture_type(t_type);
			return new_texture;

		}
	}

}

// Returns nullptr if the texture is not loaded yet, and returns the Texture pointer if it is
//TODO: Not working
Texture * Model::texture_is_loaded(std::string full_path) {
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i].diffuse_texture->get_file_name() == full_path) {
			return textures[i].diffuse_texture;
		}
		if (textures[i].normal_texture->get_file_name() == full_path) {
			return textures[i].normal_texture;
		}
	}
	return nullptr;
}

bool has_texture(Texture* texture, TextureType texture_type) {
	if (texture) {
		if (texture->texture_type == texture_type) {
			return true;
		}
	}
	return false;
}

void Model::draw(ShaderProgram* shader_program, GLenum mode) { //TODO: Maybe bring shader_program here to bind the correct texture in case we have 2 loaded for the same model eg (diffuse, ambient)
	for (GLuint i = 0; i < this->meshes.size(); i++) {
		const unsigned int m_index = meshes[i].get_material_index();
		LightingShader* lighting_shader = dynamic_cast<LightingShader*>(shader_program);
		if (lighting_shader) lighting_shader->set_material(materials[m_index]);

		textures[m_index].diffuse_texture->bind(0);
		textures[m_index].normal_texture->bind(1);
		if (lighting_shader) lighting_shader->set_diffuse_texture(0);
		if (lighting_shader) lighting_shader->set_normal_texture(1);

		this->meshes[i].draw(mode);
		textures[m_index].diffuse_texture->unbind();
		textures[m_index].normal_texture->unbind();
	}
}


Model::~Model() {
	for (unsigned int i = 0; i < textures.size(); i++) {
		delete textures[i].diffuse_texture;
		delete textures[i].normal_texture;
		textures[i].diffuse_texture = NULL;
		textures[i].normal_texture = NULL;
	}
}