#pragma once

#include "..\texture\Texture.h"

struct Vertex {
	Vertex(glm::vec3 pos, glm::vec2 tex_coord, glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent) :
			pos(pos), tex_coord(tex_coord), normal(normal), tangent(tangent), bitangent(bitangent) {}

	glm::vec3 pos;
	glm::vec2 tex_coord;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct IndexedModel {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> tex_coords;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	std::vector<GLuint> indices;
};

class Mesh {
public:
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	virtual void draw(GLenum mode = GL_TRIANGLES);
	glm::vec3 get_size();
	void set_material_index(GLuint material_index);
	GLuint get_material_index();

protected:
	GLuint mesh_vao = 0;
	GLuint mesh_draw_count;
	GLuint material_index;

	void init_mesh(const IndexedModel & model);
	void calculate_size(std::vector<glm::vec3> positions);
	glm::vec3 size;
	enum { POSITION_VB, TEXCOORD_VB, NORMAL_VB, TANGENT_VB, BITANGENT_VB, INDEX_VB, NUM_BUFFERS };
	GLuint mesh_vab[NUM_BUFFERS];

private:
};

