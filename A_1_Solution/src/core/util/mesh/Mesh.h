#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>

struct Vertex {
	Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 tex_coord) : pos(pos), normal(normal), tex_coord(tex_coord) {}
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tex_coord;
	
};


class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int num_of_vertices);
	~Mesh();

	void draw();
private:
	enum {POSITION_VB,
		  NORMAL_VB,
		  TEXCOORD_VB,
		  NUM_BUFFERS};

	GLuint mesh_vao = 0;
	GLuint mesh_vab[NUM_BUFFERS];
	unsigned int mesh_draw_count;
};

