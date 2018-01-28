#version 330

layout (location=0) in vec3 vertex_positions;
layout (location=1) in vec2 vertex_tex_coords;
layout (location=2) in vec3 vertex_normals;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;

void main(){
	gl_Position = proj_mat * view_mat * model_mat * vec4(vertex_positions, 1.0);
}