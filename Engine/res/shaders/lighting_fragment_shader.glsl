#version 330

#define number_of_point_lights 9

#define PI 3.14159265

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
in vec3 eye_dir;
in vec3 normal;
in vec2 tex_coords;

uniform vec3 view_pos;
uniform vec3 object_color;
uniform float ambient_strength;
uniform float specular_strength;
uniform int specular_power;
uniform float mix_power;
uniform bool toon;
uniform bool cook = false;

uniform float cook_f = 0.1;
uniform float cook_r = 0.1;
uniform float cook_k = 0.7;

uniform DirLight dir_light;
uniform PointLight point_lights[number_of_point_lights];
uniform Material material;

uniform sampler2D texture_0;

vec3 calc_dir_light_phong(DirLight light, vec3 normal, vec3 view_dir);
vec3 calc_dir_light_cook(DirLight light, vec3 normal, vec3 view_dir);
vec3 calc_point_light_phong(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec3 calc_point_light_cook(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec3 limit(float value, vec3 color);

vec3 texture_blend;

const float levels = 9.0f;
float spec_power = 1;


void main(){
	texture_blend = mix(vec3(texture(texture_0, tex_coords)), object_color, mix_power);
	if(specular_power > 1) spec_power = specular_power;
	else spec_power = material.shininess;

	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_pos - eye_dir);

	// Directional Lighting
	vec3 dir_lighting = vec3(0.0f, 0.0f, 0.0f);
	if (!cook) dir_lighting = calc_dir_light_phong(dir_light, norm, view_dir);
	else dir_lighting = calc_dir_light_cook(dir_light, norm, view_dir);

	// Point Lights
	vec3 point_lighting = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < number_of_point_lights; i++) {
		if(!cook) point_lighting += calc_point_light_phong(point_lights[i], norm, frag_pos, view_dir);
		else point_lighting += calc_point_light_cook(point_lights[i], norm, frag_pos, view_dir);
	}

	// Calculate Result
	vec3 result = dir_lighting + point_lighting;
	frag_color = vec4(result, 1.0f);

}

vec3 calc_dir_light_phong(DirLight light, vec3 normal, vec3 view_dir) {
	vec3 light_dir = normalize(-light.direction);
	
	// Ambient Lighting
	vec3 ambient = ambient_strength * light.light_color * texture_blend * material.ambient_color;

	// Diffuse Lighting
	float diff = max(dot(light_dir, normal), 0.0f);	
	if (toon) diff = floor(diff * levels) / levels;
	vec3 color = material.diffuse_color;
	//if (toon) color = limit(diff, color);
	
	vec3 diffuse = light.light_color * diff * texture_blend * color;

	// Specular Lighting
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), spec_power);	// TODO: Change material specular to  power shininess
	
	color = material.specular_color;
	if (toon) spec = floor(spec * levels) / levels;
	//if (toon) color = limit(spec, color);

	vec3 specular;
	if (diff > 0.0f) specular = light.light_color * spec * texture_blend * color * specular_strength;
	return (ambient + diffuse + specular);
}

vec3 calc_point_light_phong(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
	vec3 light_dir = normalize(light.position - frag_pos);

	// Attenuation 
	float distance = length(light.position - frag_pos);
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
		
	// Ambient Lighting
	vec3 ambient = ambient_strength * light.light_color * texture_blend * material.ambient_color;
	ambient *= attenuation;

	// Diffuse Lighting
	float diff = max(dot(normal, light_dir), 0.0f);	
	if (toon) diff = floor(diff * levels) / levels;
	vec3 color = material.diffuse_color;
	vec3 diffuse = diff * light.light_color * texture_blend * color;
	diffuse *= attenuation;

	// Specular Lighting
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), spec_power);
	if (toon) spec = 0.1 + floor(spec * levels) / levels;
	color = material.specular_color;
	//if (toon) color = limit (spec, color);

	vec3 specular;
	if (diff > 0.0f) {
		specular = spec * light.light_color * texture_blend * color * specular_strength;
		specular *= attenuation;
	}
	
	return (ambient + diffuse + specular);
}

vec3 limit(float value, vec3 color){
	if (value > 0.95) color = vec3(1.0, 1.0, 1.0) * color;
	else if (value > 0.75) color = vec3(0.7, 0.7, 0.7) * color;
	else if (value > 0.3) color = vec3(0.5, 0.5, 0.5) * color;
	else if (value > 0.05) color = vec3(0.25, 0.25, 0.25) * color;
	else color = vec3(0.1, 0.1, 0.1) * color;
	return color;
}

float beckmannDistribution(float x, float cook_r) {
  float NdotH = max(x, 0.0001);
  float cos2Alpha = NdotH * NdotH;
  float tan2Alpha = (cos2Alpha - 1.0) / cos2Alpha;
  float cook_r2 = cook_r * cook_r;
  float denom = 3.141592653589793 * cook_r2 * cos2Alpha * cos2Alpha;
  return exp(tan2Alpha / cook_r2) / denom;
}

float cookTorranceSpecular(vec3 lightDirection,vec3 viewDirection, vec3 surfaceNormal, float roughness, float albedo) {
  float LdotV = dot(lightDirection, viewDirection);
  float NdotL = dot(lightDirection, surfaceNormal);
  float NdotV = dot(surfaceNormal, viewDirection);

  float s = LdotV - NdotL * NdotV;
  float t = mix(1.0, max(NdotL, NdotV), step(0.0, s));

  float sigma2 = roughness * roughness;
  float A = 1.0 + sigma2 * (albedo / (sigma2 + 0.13) + 0.5 / (sigma2 + 0.33));
  float B = 0.5 * sigma2 / (sigma2 + 0.09);

  return albedo * max(0.0, NdotL) * (A + B * s / t) / PI;
}


vec3 calc_dir_light_cook(DirLight light, vec3 normal, vec3 view_dir){
	vec3 light_dir = normalize(-light.direction);
	float NdotL = max(0, dot(normal, light_dir));
	float power = 0.0f;
	power = cookTorranceSpecular(light_dir, view_dir, normal, cook_r, cook_f);
	float cook_value = (cook_k + power * (1.0 - cook_k));
		
	// Ambient Lighting
	vec3 ambient = ambient_strength * light.light_color * texture_blend * material.ambient_color;

	// Diffuse Lighting
	float diff = max(dot(normal, light_dir), 0.0f);		
	vec3 diffuse = light.light_color * diff * texture_blend * material.diffuse_color;

	// Specular Lighting
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_power);
	vec3 specular;
	if (diff > 0.0f) specular = (light.light_color * texture_blend * material.specular_color * cook_value);

	return (ambient + diffuse + specular);

}

vec3 calc_point_light_cook(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir){
	vec3 light_dir = normalize(light.position - frag_pos);
	float NdotL = max(0, dot(normal, light_dir));
	float power = 0.0f;
	power = cookTorranceSpecular(light_dir, view_dir, normal, cook_r, cook_f);
	float cook_value = (cook_k + power * (1.0 - cook_k));

	// Attenuation 
	float distance = length(light.position - frag_pos);
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
			
	// Ambient Lighting
	vec3 ambient = ambient_strength * light.light_color * texture_blend * material.ambient_color;
	ambient *= attenuation;

	// Diffuse Lighting
	float diff = max(dot(normal, light_dir), 0.0f);	
	vec3 diffuse = diff * light.light_color * texture_blend * material.diffuse_color;
	diffuse *= attenuation;

	// Specular Lighting
	vec3 reflect_dir = reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), spec_power);

	vec3 specular;
	if (diff > 0.0f) {
		specular = (light.light_color * texture_blend * material.specular_color * cook_value);
		specular *= attenuation;
	}
	
	return (ambient + diffuse + specular);
}