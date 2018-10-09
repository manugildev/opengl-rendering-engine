#version 450
#define number_of_point_lights 128

#define PI 3.14159265

struct PointLight {
	vec3 position;
	vec3 light_color;
	float constant;
	float linear;
	float quadratic;
};
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

uniform Material material;
uniform vec3 view_pos;
uniform sampler2D texture_0;
uniform DirLight dir_light;
uniform PointLight point_lights[number_of_point_lights];
uniform int point_lights_size = 0;
uniform vec3 object_color = vec3(1, 1, 1);
uniform float mix_power = 0;
uniform vec3 cool_color = vec3(0.0, 0.0, 0.9);
uniform vec3 warm_color = vec3(0.58, 0.78, 0.29);
uniform float specular_power = 32;
uniform float diffuse_cool = 0.45;
uniform float diffuse_warm = 0.45;
uniform bool use_object_color = true;
uniform bool use_phong = true;

float diffuse_reflection;
vec3 reflection_vector;
vec3 calc_point_light_phong(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main(){
	vec3 kcool;
	vec3 kwarm = vec3(0.8, 0.78, 0.29);
	vec3 final_color;
	
	vec3 light_direction = normalize(-dir_light.direction);	
	vec3 norm = normalize(normal);
	reflection_vector = normalize(reflect(-light_direction, norm));
	diffuse_reflection = (dot(light_direction, norm) + 1.0) * 0.5; 	
	vec3 nreflect = normalize(reflection_vector);
	vec3 nview = normalize(view_pos - normalize(eye_dir));
	float spec = max(dot(nreflect, nview), 0.0);
	spec = pow(spec, specular_power);

	if(use_phong){	
		vec3 ambient = dir_light.light_color * material.ambient_color;	
		
		float diff = max(dot(light_direction, norm), 0.4f);	
		vec3 diffuse = dir_light.light_color * diff * material.diffuse_color;

		vec3 specular;
		if (diff > 0.0f) specular = dir_light.light_color * spec *  material.specular_color;
		final_color = (ambient + diffuse + specular);
	
	} else {
		if(use_object_color){
			kcool = min(cool_color + diffuse_cool * object_color, 1.0);
			kwarm = min(vec3(0.58, 0.28, 0.89) + diffuse_warm * object_color, 1.0);
		} else {
			kcool = min(cool_color + diffuse_cool * material.diffuse_color, 1.0);
			kwarm = min(vec3(0.58, 0.78, 0.89) + diffuse_warm * material.diffuse_color, 1.0);	
		}		
		vec3 kfinal = mix(kcool, kwarm, diffuse_reflection);
		final_color = min(kfinal + spec, 1.0);
	}

	
	frag_color = vec4(final_color, 1.0); 
}
