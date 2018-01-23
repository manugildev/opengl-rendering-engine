#version 330

#define number_of_point_lights 9

struct DirLight {
	vec3 direction;
	vec3 light_color;
};

struct PointLight {
	vec3 position;
	vec3 light_color;
	float constant;
	float linear;
	float quadratic;
};

struct Material {
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
}; 
  

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coords;

uniform vec3 view_pos;
uniform vec3 object_color;
uniform float ambient_strength;
uniform float specular_strength;
uniform int specular_power;
uniform float mix_power;


uniform DirLight dir_light;
uniform PointLight point_lights[number_of_point_lights];
uniform Material material;

uniform sampler2D texture_0;

vec3 calc_dir_light(DirLight light, vec3 normal, vec3 view_dir);
vec3 calc_point_light(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

vec3 texture_blend;

void main(){
	texture_blend = mix(vec3(texture(texture_0, tex_coords)), object_color, mix_power);

	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_pos - frag_pos);

	// Directional Lighting
	vec3 dir_lighting = calc_dir_light(dir_light, norm, view_dir);

	// Point Lights
	vec3 point_lighting = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < number_of_point_lights; i++) {
		point_lighting += calc_point_light(point_lights[i], norm, frag_pos, view_dir);
	}

	// Calculate Result
	vec3 result = dir_lighting + point_lighting;
	frag_color = vec4(result, 1.0f);

}

vec3 calc_dir_light(DirLight light, vec3 normal, vec3 view_dir) {
	vec3 light_dir = normalize(-light.direction);
	
	// Ambient Lighting
	vec3 ambient = light.light_color * texture_blend * material.ambient_color;

	// Diffuse Lighting
	float diff = max(dot(normal, light_dir), 0.0f);	
	vec3 diffuse = light.light_color * diff * texture_blend * mix(material.diffuse_color, object_color, mix_power);

	// Specular Lighting
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_power);
	vec3 specular = light.light_color * spec * texture_blend * material.specular_color;

	return (ambient + diffuse + specular);
}

vec3 calc_point_light(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
	vec3 light_dir = normalize(light.position - frag_pos);

	// Attenuation 
	float distance = length(light.position - frag_pos);
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
			
	// Ambient Lighting
	vec3 ambient = light.light_color * texture_blend * material.ambient_color;
	ambient *= attenuation;

	// Diffuse Lighting
	float diff = max(dot(normal, light_dir), 0.0f);	
	vec3 diffuse = light.light_color * texture_blend * material.diffuse_color;
	diffuse *= attenuation;

	// Specular Lighting
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_power);
	vec3 specular = light.light_color * texture_blend * material.specular_color;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}