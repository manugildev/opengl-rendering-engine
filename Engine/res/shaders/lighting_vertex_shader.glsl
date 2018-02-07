#version 330

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec2 vertex_tex_coord;
layout (location=2) in vec3 vertex_normal;
layout (location=3) in vec3 vertex_tangent;
layout (location=4) in vec3 vertex_bitangent;

out vec3 normal;
out vec3 frag_pos;
out vec3 eye_dir;
out vec2 tex_coord;
out mat3 TBN;

uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform mat4 model_mat;
uniform vec3 view_pos;

void main(){
	vec4 world_position = model_mat * vec4(vertex_position , 1.0f);
	gl_Position = proj_mat * view_mat * world_position;	
	tex_coord = vertex_tex_coord; 	
	normal = mat3(model_mat) * vertex_normal;

	vec3 T = normalize(vec3(model_mat * vec4(vertex_tangent,   0.0)));
    vec3 B = normalize(vec3(model_mat * vec4(vertex_bitangent, 0.0)));
    vec3 N = normalize(vec3(model_mat * vec4(vertex_normal,    0.0)));
    
	T = normalize(T - dot(T, N) * N);

	TBN = mat3(T, B, N);

	eye_dir = -(view_mat * world_position).xyz;
	frag_pos = (model_mat * vec4(vertex_position, 1.0f)).xyz;

}