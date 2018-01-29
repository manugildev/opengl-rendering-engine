#version 450

struct DirLight {
	vec3 direction;
	vec3 light_color;
};

out vec4 frag_color;

in vec3 frag_pos;
in vec3 eye_dir;
in vec3 normal;
in vec2 tex_coords;
in vec3 reflected_vector;
in vec3 refracted_vector;

uniform sampler2D texture_0;
uniform samplerCube environment_map;

uniform DirLight dir_light;

const vec3 light_direction = normalize(vec3(0.2, -1.0, 0.3));
const float ambient = 0.1;

void main(){
	float brightness = max(dot(-light_direction, normalize(normal)), 0.0) + ambient;
	vec4 result = texture(texture_0, tex_coords) * brightness;
	frag_color = result;

	vec4 reflected_color = texture(environment_map, reflected_vector);
	vec4 refracted_color = texture(environment_map, refracted_vector);
	vec4 enviro_color = mix(reflected_color, refracted_color, 0.3f);

	frag_color = mix(frag_color, enviro_color, .9f);

}