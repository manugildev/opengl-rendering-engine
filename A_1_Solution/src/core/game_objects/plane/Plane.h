#pragma once
#include "..\GameObject.h"

class Application;

class Plane : public GameObject {
public:
	Plane(Application * app, Model * model, Camera* camera);
	void update(float delta_time) override;

	~Plane();

private:
	
};

