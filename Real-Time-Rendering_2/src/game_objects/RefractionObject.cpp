#include "RefractionObject.h"
#include "..\shaders\RefractionShader.h"

RefractionObject::RefractionObject(Application * app, Model * model, glm::vec3 color) : GameObject(app, model, color) {
}


RefractionObject::~RefractionObject() {
}

void RefractionObject::update(float delta_time) {
	GameObject::update(delta_time);
}

void RefractionObject::render() {
	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	if (!shader_program) return;
	shader_program->start();

	RefractionShader* refraction_shader = dynamic_cast<RefractionShader*>(shader_program);
	if (refraction_shader) {
		refraction_shader->set_environment_map(1); //TODO: Not efficient, renew this variables whenever we reload shaders
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, environment_map_id);

		refraction_shader->set_view_matrix(view);
		refraction_shader->set_proj_matrix(perspective_proj);
		refraction_shader->set_model_matrix(model_mat);
		refraction_shader->set_object_color(this->get_color());
		refraction_shader->set_view_pos(this->camera->get_pos());
	}
	
	if (this->app->is_debug()) { 
		this->model->draw(this->shader_program, GL_LINES);
	}
	else this->model->draw(this->shader_program);

	this->shader_program->stop();
}

void RefractionObject::update_lights() {
	shader_program->start();
	RefractionShader* refraction_shader = dynamic_cast<RefractionShader*>(shader_program);
	if (!refraction_shader) return;
	refraction_shader->set_directional_light(app->get_dir_light());
	shader_program->stop();
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
