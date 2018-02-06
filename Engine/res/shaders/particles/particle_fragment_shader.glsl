#version 330

out vec4 out_colour;
in vec2 texture_coords;

uniform sampler2D particle_texture;
uniform vec3 object_color;

void main(void){
	out_colour = texture(particle_texture, texture_coords);
	out_colour = out_colour * vec4(object_color, 1);
}