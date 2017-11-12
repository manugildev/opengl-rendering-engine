#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "..\camera\Camera.h"
#include "..\util\texture\Texture.h"
#include "..\util\mesh\Mesh.h"
#include "..\util\mesh\Model.h"
#include "..\util\mesh\CubeModel.h"

class Application;
class LightingShader;

const glm::vec3 DEFAULT_OBJ_COLOR(1.0f);

class GameObject {
public:
	GameObject(Application *app, Model* mesh, glm::vec3 object_color = DEFAULT_OBJ_COLOR, Texture* texture = new Texture("textures/empty_pixel.jpg"));
	~GameObject();

	virtual void update(float delta_time);
	virtual void render();

	virtual void set_initial_shader_values();

	virtual void set_pos(glm::vec3 pos);
	void set_acceleration(glm::vec3 acc);
	void set_speed(glm::vec3 speed);
	void set_max_speed(glm::vec3 max_speed);
	void set_rotation(glm::vec3 pos);
	void set_rotation_acceleration(glm::vec3 acc);
	void set_rotation_speed(glm::vec3 speed);
	void set_max_rotation_speed(glm::vec3 max_speed);
	void set_parent(GameObject* parent);

	glm::vec3 get_pos();
	glm::vec3 get_rotation();
	glm::vec3 get_speed(); 
	glm::vec3 get_rotation_speed();

	void set_scale(glm::vec3 scale);
	void set_ambient_strength(float ambient_strength);
	void set_specular_strength(float specular_strength);
	void set_specular_power(int specular_power);
	void set_mix_power(float mix_power);
	void set_shader_program(LightingShader* shader_program);

	void update_lights();
	void update_model_mat();

	LightingShader* shader_program;


protected:
	Camera* camera;
	glm::mat4 model_mat;
	Model* mesh;
	Application* app;

private:
	GameObject* parent;
	glm::vec3 object_color;
	float mix_power;
	Texture* texture;
	CubeModel cube_mesh;

	glm::vec3 scale = glm::vec3(1.0f);

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 speed = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 max_speed = glm::vec3(std::numeric_limits<float>::max());

	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 rotation_speed = glm::vec3(0.0f);
	glm::vec3 rotation_acceleration = glm::vec3(0.0f);
	glm::vec3 max_rotation_speed = glm::vec3(std::numeric_limits<float>::max());
};

