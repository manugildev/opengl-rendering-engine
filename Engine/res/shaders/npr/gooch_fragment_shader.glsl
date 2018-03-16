#version 450

struct DirLight {
	vec3 direction;
	vec3 light_color;
};

struct Material {
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
}; 

out vec4 frag_color;

in vec3 frag_pos;
in vec3 eye_dir;
in vec3 normal;
in vec2 tex_coords;

uniform vec3 view_pos;
uniform sampler2D texture_0;
uniform DirLight dir_light;
uniform vec3 object_color = vec3(1, 1, 1);
uniform float mix_power = 0;
uniform vec3 cool_color = vec3(0.0, 0.0, 0.6);
uniform vec3 warm_color = vec3(0.6, 0.6, 0.0);
uniform float specular_power = 32;
uniform float diffuse_cool = 0.45;
uniform float diffuse_warm = 0.45;

float diffuse_reflection;
vec3 reflection_vector;

void main(){
	vec3 kcool = min(cool_color + diffuse_cool * object_color, 1.0);
	vec3 kwarm = min(warm_color + diffuse_warm * object_color, 1.0);

	vec3 light_direction = normalize(-dir_light.direction);	
	vec3 norm = normalize(normal);
	reflection_vector = normalize(reflect(-light_direction, norm));
	diffuse_reflection = (dot(light_direction, norm) + 1.0) * 0.5; 

	vec3 kfinal = mix(kcool, kwarm, diffuse_reflection);	
	vec3 nreflect = normalize(reflection_vector);
	vec3 nview = normalize(view_pos - normalize(eye_dir));

	float spec = max(dot(nreflect, nview), 0.0);
	spec = pow(spec, specular_power);
	frag_color = vec4(min(kfinal + spec, 1.0), 1.0); 
}