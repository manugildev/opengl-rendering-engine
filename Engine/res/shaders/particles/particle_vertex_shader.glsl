#version 330

layout (location=0) in vec2 vertex_positions;
layout (location=1) in mat4 model_mat1;


out vec2 texture_coords;

uniform mat4 model_mat;
uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform float number_of_rows;

void main(void){
	vec4 world_position = model_mat * vec4(vertex_positions, 0.0f, 1.0f);
	gl_Position = proj_mat * view_mat * world_position;
	 texture_coords = vec2((vertex_positions.x + 1.0) / 2.0, 1 - (vertex_positions.y + 1.0) / 2.0);
}