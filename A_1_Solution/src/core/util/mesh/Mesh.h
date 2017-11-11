#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include <iostream>
#include <vector>
#include "..\obj_loader\obj_loader.h"

struct Vertex {
	Vertex(glm::vec3 pos, glm::vec2 tex_coord, glm::vec3 normal) : pos(pos), tex_coord(tex_coord), normal(normal) {}
	glm::vec3 pos;
	glm::vec2 tex_coord;
	glm::vec3 normal;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int num_of_vertices, unsigned int * indices, unsigned int num_of_indices);
	Mesh(const std::string& file_name);
	~Mesh();

	virtual void draw(GLenum mode = GL_TRIANGLES);
	glm::vec3 get_size();

protected:
	GLuint mesh_vao = 0;
	unsigned int mesh_draw_count;

	void init_mesh(const IndexedModel & model);
	void calculate_size(std::vector<glm::vec3> positions);
	enum { POSITION_VB, TEXCOORD_VB, NORMAL_VB, INDEX_VB, NUM_BUFFERS };
	GLuint mesh_vab[NUM_BUFFERS];
	glm::vec3 size;

private:
};

