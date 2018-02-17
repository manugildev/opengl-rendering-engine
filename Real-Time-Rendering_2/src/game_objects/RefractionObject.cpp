#include "RefractionObject.h"
#include "..\shaders\RefractionShader.h"

RefractionObject::RefractionObject(std::string name, Application * app, Model * model, glm::vec3 color) : GameObject(app, model, color) {
}


RefractionObject::~RefractionObject() {
}

void RefractionObject::update(float delta_time) {
	GameObject::update(delta_time);
}

void RefractionObject::render() {
	if (!this->shader_program) return;
	this->shader_program->start();
	this->update_shader_properties();	
	
	if (this->app->is_debug()) { 
		this->model->draw(this->shader_program, GL_LINES);
	}
	else this->model->draw(this->shader_program);

	this->shader_program->stop();
}

void RefractionObject::set_shader_program(ShaderProgram * shader_program) {
	this->shader_program = shader_program;
	this->shader_program->start();
	RefractionShader* refraction_shader = dynamic_cast<RefractionShader*>(shader_program);
	refraction_shader->set_environment_map(1);
	this->shader_program->stop();
}


void RefractionObject::set_environment_map_id(GLuint environment_map_id) {
	this->environment_map_id = environment_map_id;
}

void RefractionObject::set_fresnel(bool fresnel){
	this->fresnel = fresnel;
}

void RefractionObject::set_ambient_brightness(float ambient_brightness){
	this->ambient_brightness = ambient_brightness;
}

void RefractionObject::set_ior(float ior){
	this->ior = ior;
}

void RefractionObject::set_chromatic_offset(float chromatic_offset){
	this->chromatic_offset = chromatic_offset;
}

void RefractionObject::set_refractive_power(float refractive_power){
	this->refractive_power = refractive_power;
}

void RefractionObject::set_refractive_factor(float refractive_factor){
	this->refractive_factor = refractive_factor;
}

void RefractionObject::set_refractive_strength(float refractive_strength) {
	this->refractive_strength = refractive_strength;
}

void RefractionObject::set_mix_power(float mix_power){
	this->mix_power = mix_power;
}

void RefractionObject::update_shader_properties() {
	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();
	RefractionShader* refraction_shader = dynamic_cast<RefractionShader*>(shader_program);
	if (refraction_shader) {
		refraction_shader->set_environment_map(1); //TODO: Not efficient, renew this variables whenever we reload shaders
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, environment_map_id);
		refraction_shader->set_view_matrix(view);
		refraction_shader->set_proj_matrix(perspective_proj);
		refraction_shader->set_model_matrix(model_mat);
		refraction_shader->set_object_color(get_color());
		refraction_shader->set_view_pos(camera->get_pos());
		refraction_shader->set_fresnel(fresnel);
		refraction_shader->set_ior(ior);
		refraction_shader->set_chormatic_offset(chromatic_offset);
		refraction_shader->set_ambient_brightness(ambient_brightness);
		refraction_shader->set_refractive_factor(refractive_factor);
		refraction_shader->set_refractive_power(refractive_power);
		refraction_shader->set_refractive_strength(refractive_strength);
		refraction_shader->set_mix_power(mix_power);
	}
}

void RefractionObject::update_lights() {
	shader_program->start();
	RefractionShader* refraction_shader = dynamic_cast<RefractionShader*>(shader_program);
	if (!refraction_shader) return;
	refraction_shader->set_directional_light(app->get_dir_light());
	shader_program->stop();
}
