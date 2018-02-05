#version 330

out vec4 out_colour;
in vec2 texture_coords;

uniform sampler2D particle_texture;

void main(void){
	out_colour = texture(particle_texture, texture_coords);
}