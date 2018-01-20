#pragma once
#include "..\GameObject.h"

class Application;

class Plane : public GameObject {
public:
	Plane(Application* app, Model* model, Camera* camera);
	void attach_wheels(Application * app);
	void attach_propeller(Application * app);
	void attach_arrows(Application* app);
	void update(float delta_time) override;
	void render() override;
	void set_shader_program(LightingShader* shader_program) override;

	GameObject* get_red_arrow();
	GameObject* get_blue_arrow();
	GameObject* get_green_arrow();

	bool show_debug = false;

	~Plane();
	


	glm::vec3 normal = glm::vec3(0, 1, 0);			//inital vectors of the plane, defines coordinate space for plane
	glm::vec3 forwardVector = glm::vec3(0, 0, 1);
	glm::vec3 barrel = glm::vec3(-1, 0, 0);
	glm::quat transform;							//transofmration quaternion
	glm::quat axis1;								//forwardVector axis quaterion
	glm::quat axis2;								//horizaontal axis quaternion
	glm::quat axis3;								//top axis quaternion

private:
	GameObject * propeller;
	GameObject * wheels;
	GameObject * green_arrow;
	GameObject * blue_arrow;
	GameObject * red_arrow;

};

