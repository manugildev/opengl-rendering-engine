#include "core\Application.h"
#include "core\camera\Camera.h"
#include "core\game_objects\GameObject.h"
#include "core\game_objects\Light.h"
#include <iostream>

int main(void) {

	Camera camera(glm::vec3(0.0f, 0.0f, 90.0f));

	Application *app = new Application(&camera);
	GameObject *teapot = new GameObject(app);

	// TODO: Test if vectors would be a better option than arrays
	GameObject *objects[1] = {teapot};
	app->runMainGameLoop(objects, 1);
}