#version 450

layout (location=0) in vec3 vertex_positions;
layout (location=1) in vec2 vertex_tex_coords;
layout (location=2) in vec3 vertex_normals;

out vec3 normal;
out vec3 frag_pos;
out vec3 eye_dir;
out vec2 tex_coords;
out vec3 reflected_vector;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;
uniform vec3 view_pos;

void main(){
	vec4 world_position = model_mat * vec4(vertex_positions , 1.0f);
	gl_Position = proj_mat * view_mat * world_position;	
	tex_coords = vertex_tex_coords;

	normal = mat3(model_mat) * vertex_normals;
	eye_dir = view_pos - world_position.xyz;
	frag_pos = (model_mat * vec4(vertex_positions, 1.0f)).xyz;

	vec3 unit_normal = normalize(normal);
	reflected_vector = reflect(-eye_dir, unit_normal);
	//refracted_vector = refract(-eye_dir, unit_normal, 1.0f);
}