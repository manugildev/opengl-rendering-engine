#pragma once

#include <sstream>
#include <GLEW\glew.h>
#include <glm\glm.hpp>

class ShaderProgram {
public:
	ShaderProgram(std::string vertex_file, std::string fragment_file);
	~ShaderProgram();

	void link_shader();
	void validate_shader();
	void start();
	void stop();
	void init();

	GLuint program_id;

private:
	static GLuint load_shader(const std::string file_name, const GLenum shader_type);

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;

protected:
	virtual void bind_attributes() = 0 ;
	virtual void get_all_uniform_locations() = 0;

	void bind_attribute(int attribute, std::string variable_name);
	GLuint ShaderProgram::get_uniform_location(std::string uniform_name);

	void modify_vec3(GLuint location, glm::vec3 vector);
	void modify_boolean(GLuint location, bool value);
	void modify_float(GLuint location, float value);
	void modify_int(GLuint location, int value);
	void modify_mat4(GLuint location, glm::mat4 mat); 
	void modify_texture(GLuint location, int value);

};

