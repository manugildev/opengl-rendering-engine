#ifndef GRAPHICS_CUBE_MAP_H
#define GRAPHICS_CUBE_MAP_H

#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "assert.h"
#include "stdio.h"
#include "..\..\util\shaders\basic\BasicShader.h"

#include "..\..\util\util\util.h"

#define FRONT_CM "cube_map/sky/back.png"
#define BACK_CM "cube_map/sky/front.png"
#define TOP_CM "cube_map/sky/top.png"
#define BOTTOM_CM "cube_map/sky/bot.png"
#define LEFT_CM "cube_map/sky/left.png"
#define RIGHT_CM "cube_map/sky/right.png"

class CubeMap {
public:
	CubeMap(int size=100, std::string front=FRONT_CM, std::string back=BACK_CM, std::string top=TOP_CM, std::string bottom=BOTTOM_CM, std::string left=LEFT_CM, std::string right=RIGHT_CM);
	GLfloat points[108] = {
			-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,

			1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,

			-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f
	};
	bool load_cube_map_side(GLuint texture, GLenum side_target, const char *file_name);
	void create_cube_map(const char *front, const char *back, const char *top, const char *bottom, const char *left,
						 const char *right, GLuint *tex_cube);
	void render(glm::mat4 r, glm::mat4 v);
	void init(BasicShader* shader_program);
	GLuint get_cube_map_texture();

private:
	BasicShader* shader_program;
	GLuint cube_program_id;
	GLint cube_V_location;
	GLint cube_P_location;
	GLuint cube_map_texture;
	GLuint vbo;
	GLuint vao;
	std::string front, back, left, bottom, right, top;
};


#endif //GRAPHICS_CUBE_MAP_H
