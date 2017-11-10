#include "Mesh.h"
#include <vector>

Mesh::Mesh(const std::string & file_name) {
	IndexedModel model = OBJModel(file_name).ToIndexedModel();
	this->init_mesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int num_of_vertices, unsigned int * indices, unsigned int num_of_indices) {

	IndexedModel model;
	
	for (int i = 0; i < num_of_vertices; i++) {
		model.positions.push_back(vertices[i].pos);
		model.texCoords.push_back(vertices[i].tex_coord);
		model.normals.push_back(vertices[i].normal);
	}

	for (int i = 0; i < num_of_indices; i++) {
		model.indices.push_back(indices[i]);
	}

	this->init_mesh(model);

}

void Mesh::init_mesh(const IndexedModel& model) {
	this->mesh_draw_count = model.indices.size();
	
	glGenVertexArrays(1, &mesh_vao);
	glBindVertexArray(mesh_vao);

	glGenBuffers(NUM_BUFFERS, mesh_vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vab[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteBuffers(NUM_BUFFERS, mesh_vab);
	glDeleteVertexArrays(1, &mesh_vao);
}

void Mesh::draw() {
	glBindVertexArray(mesh_vao);

	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	glDrawElementsBaseVertex(GL_TRIANGLES, mesh_draw_count, GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}

