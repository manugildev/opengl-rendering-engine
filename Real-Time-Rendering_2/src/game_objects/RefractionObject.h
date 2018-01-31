#pragma once
#include "core\Application.h"

class RefractionObject : public GameObject {
public:
	RefractionObject(Application * app, Model * model, glm::vec3 color);
	~RefractionObject();

	virtual void update(float delta_time);
	virtual void render();
	virtual void update_lights();
	virtual void set_shader_program(ShaderProgram* shader_program);
	void set_environment_map_id(GLuint environment_map_id);

	void set_fresnel(bool fresnel);
	void set_ambient_brightness(float ambient_brightness);
	void set_ior(float ior);
	void set_chromatic_offset(float chromatic_offset);
	void set_refractive_power(float refractive_power);
	void set_refractive_factor(float refractive_factor);
	void set_refractive_strength(float refractive_strength);
	void set_mix_power(float mix_power);

private:
	GLuint environment_map_id = 0;

	bool fresnel;
	float ambient_brightness = 0;
	float ior = 1;
	float chromatic_offset = 0;
	float refractive_power = 1;
	float refractive_factor = 1;
	float refractive_strength = 1;
	float mix_power = 1;

	void update_shader_properties();

};

