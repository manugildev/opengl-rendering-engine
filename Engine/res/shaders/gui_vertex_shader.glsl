#version 140

in vec2 vertex_positions;
out vec2 texture_coords;
uniform mat4 transformation_matrix;

void main(void){
    gl_Position = transformation_matrix * vec4(vertex_positions, 0.0, 1.0);
    texture_coords = vec2((vertex_positions.x + 1.0) / 2.0, 1 - (vertex_positions.y + 1.0) / 2.0);
}
