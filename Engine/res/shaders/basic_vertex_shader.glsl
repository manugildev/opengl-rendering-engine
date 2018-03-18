#version 330

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec2 vertex_tex_coord;
layout (location=2) in vec3 vertex_normal;
layout (location=3) in vec3 vertex_tangent;
layout (location=4) in vec3 vertex_bitangent;

out vec3 n_eye;
out vec3 normal;
out vec2 tex_coord;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;

void main(){
	vec4 world_position = model_mat * vec4(vertex_position , 1.0f);
	tex_coord = vertex_tex_coord; 	
	gl_Position = proj_mat * view_mat * world_position;	
	normal = mat3(model_mat) * vertex_normal;
	n_eye = (view_mat * vec4(vertex_normal, 0.0)).xyz;
}