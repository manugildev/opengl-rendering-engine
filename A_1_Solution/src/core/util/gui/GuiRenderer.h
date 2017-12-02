#pragma once
#include <vector>
#include "GuiTexture.h"

class GuiRenderer {
public:
	GuiRenderer();
	~GuiRenderer();

	void render(std::vector<GuiTexture> guis);
};

