#include "GameObject.h"

#include "..\Application.h"
#include "..\src\core\util\shaders\lighting\LightingShader.h"

GameObject::GameObject(std::string name, Application *app, Model* model, glm::vec3 object_color) : name(name), app(app), camera(app->get_camera()), model(model), object_color(object_color) {
	this->model_mat = glm::mat4(1.0f);
}

void GameObject::set_shader_program(ShaderProgram* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}


void GameObject::set_initial_shader_values() {
	shader_program->start();
	//shader_program->set_ambient_strength(.02f);
	//shader_program->set_specular_strength(0.1f);
	//shader_program->set_mix_power(0.0f);
	//shader_program->set_specular_power(4);
	shader_program->stop();
}

void GameObject::update_lights() {
	// TODO: Only working for one light right now, implement shaders for multi lighting
	shader_program->start();
	LightingShader* lighting_shader = dynamic_cast<LightingShader*>(shader_program);
	if (!lighting_shader) return;
	lighting_shader->set_directional_light(app->get_dir_light());
	lighting_shader->set_point_lights(app->get_point_lights());
	shader_program->stop();
}

void GameObject::update(double delta_time) {
	this->position -= rotation_factor;
	if (distance_from_center != 0) this->circular_angle += this->circular_speed * delta_time;
	//model_mat = glm::rotate(model_mat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 new_speed = this->speed + (this->acceleration * delta_time);
	if (glm::all(glm::lessThan(new_speed, this->max_speed))) this->speed = new_speed;
	this->position += this->speed * delta_time;
	if (distance_from_center != 0) rotation_factor = this->calculate_rotation_position();	
	this->set_pos(this->position + rotation_factor);

	glm::vec3 new_rotation_speed = this->rotation_speed + (this->rotation_acceleration * delta_time);
	if (glm::all(glm::lessThan(new_rotation_speed, this->max_rotation_speed))) this->rotation_speed = new_rotation_speed;
	this->rotation += this->rotation_speed * delta_time;

	glm::quat rotX = glm::angleAxis(glm::radians(rotation[0]), glm::vec3(1.f, 0.f, 0.f));
	glm::quat rotY = glm::angleAxis(glm::radians(rotation[1]), glm::vec3(0.f, 1.f, 0.f));
	glm::quat rotZ = glm::angleAxis(glm::radians(rotation[2]), glm::vec3(0.f, 0.f, 1.f));
	quaternion = rotZ * rotY * rotX;
	
	this->update_model_mat();
}

void GameObject::update_model_mat() {
	this->model_mat = glm::scale(glm::mat4(1.0f), this->scale);
	glm::mat4 rotation_mat = glm::toMat4(quaternion);
	this->model_mat = rotation_mat * model_mat;
	this->model_mat[3][0] = this->get_pos()[0];
	this->model_mat[3][1] = this->get_pos()[1];
	this->model_mat[3][2] = this->get_pos()[2];

	this->global_model_mat = this->model_mat;
	
	if (parent != nullptr) this->model_mat = parent->model_mat * this->model_mat;
}

void GameObject::render() {
	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	if (!shader_program) return;
	this->shader_program->start();

	// Todo: Why LightingShader and not ShaderProgram?? This should be abstracted to another class
	LightingShader* lighting_shader = dynamic_cast<LightingShader*>(shader_program);
	if (lighting_shader) {
		lighting_shader->set_view_matrix(view);
		lighting_shader->set_proj_matrix(perspective_proj);
		lighting_shader->set_model_matrix(model_mat);
		lighting_shader->set_view_pos(this->camera->get_pos());
		lighting_shader->set_toon_shading(toon_shading);
		lighting_shader->set_object_color(object_color);
		lighting_shader->set_specular_strength(specular_strength);
		lighting_shader->set_ambient_strength(ambient_strength);
		lighting_shader->set_specular_power(specular_power);
		lighting_shader->set_mix_power(mix_power);
		lighting_shader->set_cook_shading(cook_shading);
		lighting_shader->show_normal_texture(show_normal_texture);
		lighting_shader->apply_normal_map(apply_normal_map);
		lighting_shader->set_cook_shading(cook_shading);
		if (cook_shading) {
			lighting_shader->set_cook_r(cook_r);
			lighting_shader->set_cook_f(cook_f0);
			lighting_shader->set_cook_k(cook_k);
		}
	}

	if (this->app->is_debug()) {
		this->model->draw(this->shader_program, GL_LINES);
	} else this->model->draw(this->shader_program);
	
	if (lighting_shader) lighting_shader->set_toon_shading(false);
	this->shader_program->stop();
}

#pragma region PROPERTIES_SETTERS
void GameObject::set_pos(glm::vec3 pos) {
	this->position = pos;
}

void GameObject::set_acceleration(glm::vec3 acc) {
	this->acceleration = acc;
}

void GameObject::set_speed(glm::vec3 speed) {
	this->speed = speed;
}

void GameObject::set_max_speed(glm::vec3 max_speed) {
	this->max_speed = max_speed;
}

void GameObject::set_rotation(glm::vec3 rotation) {
	glm::quat qPitch = glm::angleAxis(glm::radians(rotation[0]), glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(glm::radians(rotation[1]), glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(glm::radians(rotation[2]), glm::vec3(0, 0, 1));

	quaternion = qYaw * qPitch * qRoll;

	this->rotation = rotation;
}

void GameObject::set_rotation_acceleration(glm::vec3 acc) {
	this->rotation_acceleration = acc;
}

void GameObject::set_rotation_speed(glm::vec3 speed) {
	this->rotation_speed = speed;
}

void GameObject::set_max_rotation_speed(glm::vec3 max_speed) {
	this->max_rotation_speed = max_speed;
}

std::string GameObject::get_name(){
	return name;
}

glm::vec3 GameObject::get_pos() {
	return position;
}

glm::vec3 GameObject::get_rotation() {
	return this->rotation;
}

glm::vec3 GameObject::get_speed() {
	return this->speed;
}

glm::vec3 GameObject::get_rotation_speed() {
	return this->rotation_speed;
}

glm::mat4 GameObject::get_model_mat(){
	return this->model_mat;
}

glm::mat4 GameObject::get_global_model_mat() {
	return this->global_model_mat;
}

glm::quat GameObject::get_quaternion() { return this->quaternion; }

int GameObject::get_specular_power() {
	return this->specular_power;
}

float GameObject::get_specular_strength(){
	return this->specular_strength;
}

float GameObject::get_cook_f0() {
	return this->cook_f0;
}

float GameObject::get_cook_r() {
	return this->cook_r;
}

float GameObject::get_cook_k() {
	return this->cook_k;
}

float GameObject::get_mix_power(){
	return this->mix_power;
}

bool GameObject::get_apply_normal_map(){
	return this->apply_normal_map;
}

bool GameObject::get_show_normal_texture(){
	return this->show_normal_texture;
}

GameObject * GameObject::get_parent(){
	return this->parent;
}

ShaderProgram * GameObject::get_shader_program(){
	return shader_program;
}

Model * GameObject::get_model(){
	return model;
}

glm::vec3 GameObject::get_color() {
	return this->object_color;
}

void GameObject::set_scale(glm::vec3 scale) {
	this->scale = scale;
}

void GameObject::set_ambient_strength(float ambient_strength) {
	this->ambient_strength = ambient_strength;
}

void GameObject::set_specular_strength(float specular_strength) {
	if (specular_strength > 1 || specular_strength < 0) return;
	this->specular_strength = specular_strength;
}

void GameObject::set_specular_power(int specular_power) {
	if (specular_power <= 1) return; // Limit it
	this->specular_power = specular_power;
}

void GameObject::set_mix_power(float mix_power) {
	this->mix_power = mix_power;
}

void GameObject::set_cook_f0(float value){
	if (cook_f0 > 1) { cook_f0 = 1; return; }
	if (cook_f0 < 0) { cook_f0 = 0; return; }
	this->cook_f0 = value;
}

void GameObject::set_cook_r(float value){
	if (cook_r > 1) { cook_r = 1; return; }
	if (cook_r < 0) { cook_r = 0; return; }
	this->cook_r = value;
}

void GameObject::set_cook_k(float value){
	if (cook_k > 1) { cook_k = 1; return; }
	if (cook_k < 0) { cook_k = 0; return; }
	this->cook_k = value;
}

void GameObject::set_circular_speed(glm::vec2 value){
	this->circular_speed = value;
}

void GameObject::set_distance_from_center(float value){
	this->distance_from_center = value;
}

void GameObject::set_circular_angle(glm::vec2 value){
	this->circular_angle = value;
}

void GameObject::set_toon_shading(bool toon_shading) {
	this->toon_shading = toon_shading;
}

void GameObject::set_cook_shading(bool cook_shading) {
	this->cook_shading = cook_shading;
}

void GameObject::set_show_normal_texture(bool value){
	this->show_normal_texture = value;
}

void GameObject::set_apply_normal_map(bool value){
	this->apply_normal_map = value;
}


void GameObject::set_parent(GameObject* parent) {
	this->parent = parent;
}

void GameObject::set_model_mat(glm::mat4 model_mat) {
	this->model_mat = model_mat;
}

void GameObject::set_global_model_mat(glm::mat4 model_mat) {
	this->global_model_mat = model_mat;
}

void GameObject::set_quaternion(glm::quat quaternion) {
	this->quaternion = quaternion;
}

void GameObject::set_name(std::string name) {
	this->name = name;
}

void GameObject::set_model(Model * model){
	this->model = model;
}

glm::vec3 GameObject::calculate_rotation_position() {	
	glm::vec2 radian_angle = glm::radians(circular_angle);
	float new_x = distance_from_center * glm::cos(radian_angle.x) * glm::sin(radian_angle.y);
	float new_y = distance_from_center * glm::sin(radian_angle.x) * glm::sin(radian_angle.y);
	float new_z = distance_from_center * glm::cos(radian_angle.y);
	return glm::vec3(new_x, new_y, new_z);
}


#pragma endregion

GameObject::~GameObject() {
	delete camera;
	delete shader_program;
	delete model;
	camera = NULL;
	shader_program = NULL;
	model = NULL;

}
