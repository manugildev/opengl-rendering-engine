#version 140

in vec2 texture_coords;
out vec4 out_Color;
uniform sampler2D gui_texture;

void main(void){
    out_Color = texture(gui_texture, texture_coords);
}
