#include "Bone.h"
#include "..\util\maths.h"

Bone::Bone(std::string name, Application * app, Model* model, glm::vec3 object_color, float length) : GameObject(name, app, model, object_color), length(length){
	origin = new GameObject("origin", app, new Model("models/sphere.obj"), glm::vec3(1));
	origin->set_pos(glm::vec3(0, 0, 0));
	origin->set_scale(glm::vec3(0.06));
	end = new GameObject("end", app, new Model("models/sphere.obj"), glm::vec3(1));
	end->set_pos(glm::vec3(0, length, 0));
	end->set_scale(glm::vec3(0.06));

	origin_pos = glm::vec3(0);
	end_pos = glm::vec3(0, length, 0);

	set_scale(glm::vec3(length));

}

Bone::~Bone(){
	delete origin;
	delete end;
	origin = nullptr;
	end = nullptr;
}

void Bone::update(double delta_time){

	this->model_mat = glm::scale(glm::mat4(1.0f), this->scale);
	glm::quat new_quat = maths::rotation_between_vectors(glm::vec3(0, 1, 0), end_pos - origin_pos);
	glm::mat4 rotation_mat = glm::toMat4(new_quat);
	this->model_mat = rotation_mat * model_mat;
	if (parent != nullptr) { 
		Bone* p = dynamic_cast<Bone*>(parent);
		this->origin->set_pos(p->end_pos);
		this->model_mat[3][0] = p->end_pos[0];
		this->model_mat[3][1] = p->end_pos[1];
		this->model_mat[3][2] = p->end_pos[2];
	}
	this->global_model_mat = this->model_mat;

	this->end->set_pos(this->end_pos);
	this->origin->update(delta_time);
	this->end->update(delta_time);
	this->set_pos(origin_pos);
}

void Bone::render() {
	GameObject::render();
	//this->origin->render();
	//this->end->render();
}

void Bone::set_shader_program(ShaderProgram * shader_program) {
	GameObject::set_shader_program(shader_program);
	this->origin->set_shader_program(shader_program);
	this->end->set_shader_program(shader_program);
}

void Bone::set_origin_pos(glm::vec3 pos) {
	this->origin_pos = pos;
}

void Bone::set_end_pos(glm::vec3 pos) {
	this->end_pos = pos;
}

void Bone::update_childrens(glm::vec3 origin, glm::quat new_rotation) {
	if (children != nullptr) {
		children->origin_pos = dynamic_cast<Bone*>(children->get_parent())->end_pos;
		children->end_pos = maths::rotate_around_point(children->end_pos, origin, new_rotation);		
		children->update_childrens(origin, new_rotation);
	}
}

void Bone::set_children(Bone * bone) {
	this->children = bone;
}

Bone* Bone::get_children() {
	return children;
}

void Bone::set_parent(GameObject* parent) {
	GameObject::set_parent(parent);
	if (parent != nullptr) {
		Bone* p = dynamic_cast<Bone*>(parent);
		set_origin_pos(p->end_pos);
		set_end_pos(origin_pos + (glm::vec3(0, length, 0)));
	}
}