#version 450

in vec2 texture_coords;
out vec4 out_color;
uniform sampler2D gui_texture;

void make_kernel(inout vec4 n[9], sampler2D tex, vec2 coord) {
	float w = 1.0 / textureSize(tex, 0).x;
	float h = 1.0 / textureSize(tex, 0).y;

	n[0] = texture2D(tex, coord + vec2( -w, -h));
	n[1] = texture2D(tex, coord + vec2(0.0, -h));
	n[2] = texture2D(tex, coord + vec2(  w, -h));
	n[3] = texture2D(tex, coord + vec2( -w, 0.0));
	n[4] = texture2D(tex, coord);
	n[5] = texture2D(tex, coord + vec2(  w, 0.0));
	n[6] = texture2D(tex, coord + vec2( -w, h));
	n[7] = texture2D(tex, coord + vec2(0.0, h));
	n[8] = texture2D(tex, coord + vec2(  w, h));
}

void main(void) {
	vec4 n[9];
	make_kernel(n, gui_texture, texture_coords);

	vec4 sobel_edge_h = n[2] + (2.0*n[5]) + n[8] - (n[0] + (2.0*n[3]) + n[6]);
  	vec4 sobel_edge_v = n[0] + (2.0*n[1]) + n[2] - (n[6] + (2.0*n[7]) + n[8]);
	vec4 sobel = sqrt((sobel_edge_h * sobel_edge_h) + (sobel_edge_v * sobel_edge_v));
	vec3 c = 1 - sobel.rgb;

	float Cmax = max(max(c.r, c.g), c.b);
    float Cmin = min(min(c.r, c.g), c.b);
	float delta = Cmax - Cmin;
	float saturation = delta / Cmax;

	out_color = vec4(c, 1);
}