#version 330

layout (location=0) in vec3 vertex_positions;
layout (location=1) in vec3 vertex_normals;
layout (location=2) in vec2 vertex_tex_coords;

out vec3 normal;
out vec3 frag_pos;
out vec2 tex_coords;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;

void main(){
	gl_Position = proj_mat * view_mat * model_mat * vec4(vertex_positions, 1.0);
	frag_pos = vec3(model_mat * vec4(vertex_positions, 1.0f));
	normal = mat3(transpose(inverse(model_mat))) * vertex_normals;
	tex_coords = vertex_tex_coords; 
}