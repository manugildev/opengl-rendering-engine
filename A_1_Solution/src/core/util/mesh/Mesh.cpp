#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex * vertices, unsigned int num_of_vertices) {
	this->mesh_draw_count = num_of_vertices;

	glGenVertexArrays(1, &mesh_vao);
	glBindVertexArray(mesh_vao);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> tex_coords;

	positions.reserve(num_of_vertices);
	normals.reserve(num_of_vertices);
	tex_coords.reserve(num_of_vertices);

	for (int i = 0; i < num_of_vertices; i++) {
		positions.push_back(vertices[i].pos);
		normals.push_back(vertices[i].normal);
		tex_coords.push_back(vertices[i].tex_coord);
	}


	glGenBuffers(NUM_BUFFERS, mesh_vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_of_vertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	glBindVertexArray(0);

	glGenBuffers(NUM_BUFFERS, mesh_vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_of_vertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(1);

	glGenBuffers(NUM_BUFFERS, mesh_vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_of_vertices * sizeof(tex_coords[0]), &tex_coords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(2);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &mesh_vao);
}

void Mesh::draw() {
	glBindVertexArray(mesh_vao);

	glDrawArrays(GL_TRIANGLES, 0, mesh_draw_count);

	glBindVertexArray(0);
}
