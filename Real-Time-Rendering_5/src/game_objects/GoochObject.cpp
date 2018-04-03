#include "GoochObject.h"

GoochObject::GoochObject(std::string name, Application * app, Model* model, glm::vec3 object_color) : GameObject(name, app, model, object_color){
}


GoochObject::~GoochObject(){
}

void GoochObject::update(double delta_time){
	GameObject::update(delta_time);
}

void GoochObject::render(){
	if (!this->shader_program) return;
	this->shader_program->start();
	this->update_shader_properties();	
	this->model->draw(this->shader_program);
	this->shader_program->stop();
}

void GoochObject::set_initial_shader_values(){
	GoochShader* gooch_shader = dynamic_cast<GoochShader*>(shader_program);
	if (gooch_shader) {
		gooch_shader->modify_vec3(gooch_shader->location_object_color, get_color());
		gooch_shader->modify_vec3(gooch_shader->location_dir_light.direction, app->get_dir_light()->get_direction());
		gooch_shader->modify_vec3(gooch_shader->location_dir_light.light_color, app->get_dir_light()->get_color());
	}
}

void GoochObject::update_shader_properties(){
	glm::mat4 view_matrix = this->camera->get_view_matrix();
	glm::mat4 projection_matrix = this->camera->get_persp_proj_matrix();
	glm::vec3 camera_pos = this->camera->get_pos();
	GoochShader* gooch_shader = dynamic_cast<GoochShader*>(shader_program);
	if (gooch_shader) {
		gooch_shader->modify_mat4(gooch_shader->location_view_mat, view_matrix);
		gooch_shader->modify_mat4(gooch_shader->location_proj_mat, projection_matrix);
		gooch_shader->modify_mat4(gooch_shader->location_model_mat, model_mat);
		gooch_shader->modify_vec3(gooch_shader->location_view_position, camera_pos);

		gooch_shader->modify_vec3(gooch_shader->location_object_color, get_color());
		gooch_shader->modify_vec3(gooch_shader->location_dir_light.direction, app->get_dir_light()->get_direction());
		gooch_shader->modify_vec3(gooch_shader->location_dir_light.light_color, app->get_dir_light()->get_color());
		gooch_shader->modify_boolean(gooch_shader->location_use_object_color, use_object_color);
		gooch_shader->modify_boolean(gooch_shader->location_use_phong, use_phong);
	}
}
