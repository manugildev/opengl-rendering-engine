#pragma once
#include "core\Application.h"

class Bone : public GameObject {
public:
	Bone(std::string name, Application * app, Model* model, glm::vec3 object_color, float length);
	~Bone();

	void update(float delta_time) override;
	void render() override;
	void set_shader_program(ShaderProgram * shader_program) override;
	void set_parent(GameObject* parent) override;
	void set_children(Bone* bone);
	Bone* get_children();
	
	GameObject* origin;
	GameObject* end;
	Bone* children;

	glm::vec3 origin_pos;
	glm::vec3 end_pos;
	glm::quat quaternion;
	
	void set_origin_pos(glm::vec3 pos);
	void set_end_pos(glm::vec3 pos);

	void update_childrens(glm::vec3 origin, glm::quat new_rotation);
	float length = 0;
};

