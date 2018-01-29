#include "Quad.h"
#include "..\shaders\gui\GuiShader.h"

Quad::Quad(GuiShader* shader_program) {

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		-1.0f,  1.0f,  // Top-left
		 1.0f,  1.0f,   // Top-right
		 1.0f, -1.0f,   // Bottom-right
		-1.0f, -1.0f,  // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Specify the layout of the vertex data
	// Vertex_Positions are always the same, we change the tranformation_matrix - should work
	GLint posAttrib = glGetAttribLocation(shader_program->program_id, "vertex_positions");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
}

Quad::~Quad() {}

void Quad::render() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

GLuint Quad::get_vao() {
	return vao;
}
