#include "CubeMap.h"

#define FRONT "cube_map/back.png"
#define BACK "cube_map/front.png"
#define TOP "cube_map/top.png"
#define BOTTOM "cube_map/bot.png"
#define LEFT "cube_map/left.png"
#define RIGHT "cube_map/right.png"

#define STB_IMAGE_IMPLEMENTATION
#include <std_image\stb_image.h>

CubeMap::CubeMap() {}

void CubeMap::init(BasicShader* shader_program){
	this->shader_program = shader_program;
    vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    create_cube_map(FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT, &cube_map_texture);

}

bool CubeMap::load_cube_map_side(GLuint texture, GLenum side_target, const char *file_name) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int x, y, n;
    int force_channels = 4;
    unsigned char *image_data = stbi_load(file_name, &x, &y, &n, force_channels);
    if (!image_data) {
        fprintf(stderr, "ERROR: could not load %s\n", file_name);
        return false;
    }
    // non-power-of-2 dimensions check
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
        fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n",
                file_name);
    }

    // copy image data into 'target' side of cube map
    glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image_data);
    free(image_data);
    return true;
}

void CubeMap::create_cube_map(const char *front, const char *back, const char *top,
                               const char *bottom, const char *left, const char *right,
                               GLuint *tex_cube) {
    // generate a cube-map texture to hold all the sides
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, tex_cube);

    // load each image and copy into a side of the cube-map texture
    (load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front));
    (load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back));
    (load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top));
    (load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));
    (load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left));
    (load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right));
    // format cube map texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void CubeMap::render(glm::mat4 v, glm::mat4 p) {
    glDepthMask(GL_FALSE);
	this->shader_program->start();
	glBindVertexArray(vao);
	this->shader_program->set_view_matrix(v);
	this->shader_program->set_proj_matrix(p);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	this->shader_program->stop();
}