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

uniform sampler2D texture_0;
uniform samplerCube environment_map;
uniform DirLight dir_light;
uniform vec3 object_color;

const float ambient = 0.9;

void main(){
	float brightness = max(dot(-dir_light.direction, normalize(normal)), 0.0) + ambient;
	vec4 result = texture(texture_0, tex_coords) * brightness;
	// Without texture
	result = vec4(object_color, 1.0f) * brightness * vec4(dir_light.light_color, 1.0f);

	frag_color = result;

	vec4 reflected_color = texture(environment_map, reflected_vector);

	float IOR = 0.9f;
	float offset = 0.03f;
	vec3 refraction_r = refract(-eye_dir, normalize(normal), IOR + offset);
	vec3 refraction_g = refract(-eye_dir, normalize(normal), IOR);
	vec3 refraction_b = refract(-eye_dir, normalize(normal), IOR - offset);

	vec4 refracted_color;
	refracted_color.r = texture(environment_map, refraction_r).r;
	refracted_color.g = texture(environment_map, refraction_g).g;
	refracted_color.b = texture(environment_map, refraction_b).b;
		
	vec3 view_vector = normalize(eye_dir);
	float refractive_factor = dot(view_vector, normalize(normal));
	
	refractive_factor = pow(refractive_factor, 3);
	vec4 enviro_color = mix(reflected_color, refracted_color,  refractive_factor);


	frag_color = mix(frag_color, enviro_color, .8f);

}