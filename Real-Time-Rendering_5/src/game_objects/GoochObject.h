#pragma once
#include "Engine.h"

class GoochObject : public GameObject{
public:
	GoochObject(std::string name, Application *, Model* model, glm::vec3 object_color);
	~GoochObject();

	virtual void update(double delta_time);
	virtual void render();
	virtual void set_initial_shader_values();
	virtual void update_lights();
	bool use_object_color = true;
	bool use_phong = false;

private:
	void update_shader_properties();
};

