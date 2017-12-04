#ifndef GRAPHICS_CUBE_MAP_H
#define GRAPHICS_CUBE_MAP_H

#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "assert.h"
#include "stdio.h"
#include "..\..\util\shaders\basic\BasicShader.h"

#include "..\..\util\util\util.h"

class CubeMap {
public:
	CubeMap();
	GLfloat points[108] = {
			-1000.0f, 1000.0f, -1000.0f, -1000.0f, -1000.0f, -1000.0f, 1000.0f, -1000.0f, -1000.0f,
			1000.0f, -1000.0f, -1000.0f, 1000.0f, 1000.0f, -1000.0f, -1000.0f, 1000.0f, -1000.0f,

			-1000.0f, -1000.0f, 1000.0f, -1000.0f, -1000.0f, -1000.0f, -1000.0f, 1000.0f, -1000.0f,
			-1000.0f, 1000.0f, -1000.0f, -1000.0f, 1000.0f, 1000.0f, -1000.0f, -1000.0f, 1000.0f,

			1000.0f, -1000.0f, -1000.0f, 1000.0f, -1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f,
			1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, -1000.0f, 1000.0f, -1000.0f, -1000.0f,

			-1000.0f, -1000.0f, 1000.0f, -1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f,
			1000.0f, 1000.0f, 1000.0f, 1000.0f, -1000.0f, 1000.0f, -1000.0f, -1000.0f, 1000.0f,

			-1000.0f, 1000.0f, -1000.0f, 1000.0f, 1000.0f, -1000.0f, 1000.0f, 1000.0f, 1000.0f,
			1000.0f, 1000.0f, 1000.0f, -1000.0f, 1000.0f, 1000.0f, -1000.0f, 1000.0f, -1000.0f,

			-1000.0f, -1000.0f, -1000.0f, -1000.0f, -1000.0f, 1000.0f, 1000.0f, -1000.0f, -1000.0f,
			1000.0f, -1000.0f, -1000.0f, -1000.0f, -1000.0f, 1000.0f, 1000.0f, -1000.0f, 1000.0f
	};
	GLuint vbo;
	GLuint vao;
	bool load_cube_map_side(GLuint texture, GLenum side_target, const char *file_name);
	void create_cube_map(const char *front, const char *back, const char *top, const char *bottom, const char *left,
						 const char *right, GLuint *tex_cube);
	void render(glm::mat4 r, glm::mat4 v);
	GLuint cube_program_id;
	GLint cube_V_location;
	GLint cube_P_location;
	GLuint cube_map_texture;
	void init(BasicShader* shader_program);

private:
	BasicShader* shader_program;
};


#endif //GRAPHICS_CUBE_MAP_H
