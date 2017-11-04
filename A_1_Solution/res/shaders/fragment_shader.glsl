#version 330

in vec3 n_eye;

out vec4 frag_color;

void main(){
	frag_color = vec4(n_eye, 1.0);
}