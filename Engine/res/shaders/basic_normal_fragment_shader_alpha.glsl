#version 330

in vec3 n_eye;
in vec3 normal;
out vec4 frag_color;

float LinearizeDepth(){
    float zNear = 2;
    float zFar  = 10000.0;
    float depth = gl_FragCoord.z;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main(){
    float c = LinearizeDepth();
	vec4 out_color = vec4(normal.x, normal.y, normal.z, 1);	
	frag_color = out_color;

}