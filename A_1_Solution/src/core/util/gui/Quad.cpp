#include "Quad.h"

Quad::Quad(float positions[]) {
	glGenVertexArrays(1, &mesh_vao);
	glBindVertexArray(mesh_vao);

	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

Quad::~Quad() {}

void Quad::render() {
	glBindVertexArray(mesh_vao);
	glEnableVertexAttribArray(0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

}

void Quad::update() {}
