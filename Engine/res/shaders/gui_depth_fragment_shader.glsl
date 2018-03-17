#version 450

in vec2 texture_coords;
out vec4 out_color;
uniform sampler2D gui_texture;

float LinearizeDepth(in vec2 uv){
    float zNear = 2;
    float zFar  = 1000.0;
    float depth = texture2D(gui_texture, uv).x;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(void){
    float c = LinearizeDepth(texture_coords);
    out_color = vec4(c, c, c, 1.0);
}
