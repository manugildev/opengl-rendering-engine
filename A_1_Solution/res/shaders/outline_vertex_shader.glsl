#version 330

// vertex attributes layout(location = 0) in vec3 i_position;
layout(location = 0) in vec3 vertex_positions;
layout(location = 1) in vec2 vertex_tex_coords;
layout(location = 2) in vec3 vertex_normals;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;

uniform float u_offset1;

void main(void) {
	vec4 tPos = vec4(vertex_positions + vertex_normals * u_offset1, 1.0);
	gl_Position = proj_mat * view_mat * model_mat * tPos;
}