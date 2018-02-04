#version 330

layout (location=0) in vec2 vertex_positions;

uniform mat4 proj_mat;
uniform mat4 model_mat;
uniform mat4 view_mat;

void main(void){
	vec4 world_position = model_mat * vec4(vertex_positions, 0.0f, 1.0f);
	gl_Position = proj_mat * view_mat * world_position;
}