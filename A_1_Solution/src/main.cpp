#include "core\Application.h"
#include "core\game_objects\GameObject.h"
int main(void) {
	Application *app = new Application();
	GameObject *teapot = new GameObject();
	GameObject *objects[1] = {teapot};
	app->runMainGameLoop(objects, 1);
}