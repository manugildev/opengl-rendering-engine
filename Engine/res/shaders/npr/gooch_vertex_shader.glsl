#version 450

layout (location=0) in vec3 vertex_positions;
layout (location=1) in vec2 vertex_tex_coords;
layout (location=2) in vec3 vertex_normals;

out vec3 normal;
out vec3 frag_pos;
out vec3 eye_dir;
out vec2 tex_coords;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;

void main(){
	vec4 world_position = model_mat * vec4(vertex_positions , 1.0f);
	
	gl_Position = proj_mat * view_mat * world_position;	
	normal = mat3(model_mat) * vertex_normals;
	frag_pos = (model_mat * vec4(vertex_positions, 1.0f)).xyz;
	eye_dir = -(transpose(view_mat) * world_position).xyz;
	tex_coords = vertex_tex_coords;
}