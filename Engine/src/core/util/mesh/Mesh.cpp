#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = vertices;
	this->indices = indices;

	IndexedModel model;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		model.positions.push_back(vertices[i].pos);
		model.tex_coords.push_back(vertices[i].tex_coord);
		model.normals.push_back(vertices[i].normal);
		model.tangents.push_back(vertices[i].tangent);
		model.bitangents.push_back(vertices[i].bitangent);
	}

	for (unsigned int i = 0; i < indices.size(); i++) {
		model.indices.push_back(indices[i]);
	}

	this->init_mesh(model);
}

void Mesh::init_mesh(const IndexedModel& model) {
	this->mesh_draw_count = model.indices.size();
	this->calculate_size(model.positions);

	glGenVertexArrays(1, &mesh_vao);
	glBindVertexArray(mesh_vao);

	glGenBuffers(NUM_BUFFERS, mesh_vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.tex_coords[0]), &model.tex_coords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[TANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.tangents.size() * sizeof(model.tangents[0]), &model.tangents[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[BITANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.bitangents.size() * sizeof(model.bitangents[0]), &model.bitangents[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vab[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::calculate_size(std::vector<glm::vec3> positions) {
	float max_x = std::numeric_limits<float>::min(), min_x = std::numeric_limits<float>::max();
	float max_y = std::numeric_limits<float>::min(), min_y = std::numeric_limits<float>::max();
	float max_z = std::numeric_limits<float>::min(), min_z = std::numeric_limits<float>::max();

	for (unsigned int i = 0; i < positions.size(); i++) {
		max_x = std::max(max_x, positions[i].x);
		min_x = std::min(min_x, positions[i].x);
		max_y = std::max(max_y, positions[i].y);
		min_y = std::min(min_y, positions[i].y);
		max_z = std::max(max_z, positions[i].z);
		min_z = std::min(min_z, positions[i].z);
	}

	this->size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
}

void Mesh::draw(GLenum mode) {
	glBindVertexArray(mesh_vao);
	glDrawElementsBaseVertex(mode, mesh_draw_count, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0);
}

glm::vec3 Mesh::get_size() {
	return this->size;
}

void Mesh::set_material_index(GLuint material_index) {
	this->material_index = material_index;
}

GLuint Mesh::get_material_index() {
	return this->material_index;
}

Mesh::~Mesh() {
}

