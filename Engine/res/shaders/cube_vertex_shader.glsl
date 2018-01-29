#version 410

layout (location=0) in vec3 vertex_positions;
uniform mat4 proj_mat, view_mat;
out vec3 texcoords;

void main () {
	texcoords = vertex_positions;
	gl_Position = proj_mat * view_mat * vec4 (vertex_positions, 1.0);
}