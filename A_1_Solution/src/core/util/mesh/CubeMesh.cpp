#include "CubeMesh.h"

CubeMesh::CubeMesh() : Mesh(CUBE_OBJ_PATH) {}

void CubeMesh::draw(GLenum mode) {
	glBindVertexArray(this->mesh_vao);
	glDrawArrays(mode, 0, this->mesh_draw_count );
	glBindVertexArray(0);
}

CubeMesh::~CubeMesh() {}