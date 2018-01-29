#version 450

in vec2 texture_coords;
out vec4 out_color;
uniform sampler2D gui_texture;

void main(void){
    out_color = texture(gui_texture, texture_coords);
}
