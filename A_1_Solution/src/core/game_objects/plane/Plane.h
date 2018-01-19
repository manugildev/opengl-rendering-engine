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

private:
	GameObject * propeller;
	GameObject * wheels;
	GameObject * green_arrow;
	GameObject * blue_arrow;
	GameObject * red_arrow;

};

