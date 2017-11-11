#pragma once
#include "Mesh.h"

const std::string CUBE_OBJ_PATH = "models/cube.obj";

class CubeMesh : public Mesh {	
public:
	CubeMesh();
	~CubeMesh();

	void draw(GLenum mode = GL_LINES) override;
};

