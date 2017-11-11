#version 330

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coords;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 object_color;
uniform vec3 light_color;
uniform float ambient_strength;
uniform float specular_strength;
uniform int specular_power;

uniform sampler2D texture_0;

void main(){
	// Ambient Lighting
	vec3 ambient = ambient_strength * vec3(texture(texture_0, tex_coords));

	// Diffuse Lighting
	vec3 norm = normalize(normal);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diff = max(dot(norm, light_dir), 0.0f);
	vec3 diffuse = diff * light_color * vec3(texture(texture_0, tex_coords)); 

	// Specular Lighting
	vec3 view_dir = normalize(view_pos - frag_pos);
	vec3 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_power);
	vec3 specular = specular_strength * spec * light_color * vec3(texture(texture_0, tex_coords));

	vec3 result = (ambient + diffuse + specular) * mix(vec3(texture(texture_0, tex_coords)), object_color, 0.9f);

	frag_color = vec4(result, 1.0f);

}