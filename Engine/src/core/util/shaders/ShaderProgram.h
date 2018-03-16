#pragma once
#include "En.h"

class ShaderProgram {
public:
	ShaderProgram(std::string vertex_file, std::string fragment_file);
	~ShaderProgram();

	int link_shader();
	int validate_shader();
	void start();
	void stop();
	void init();
	void reload();

	GLuint program_id;
	GLuint get_uniform_location(std::string uniform_name);

	void modify_vec3(GLuint location, glm::vec3 vector);
	void modify_boolean(GLuint location, bool value);
	void modify_float(GLuint location, float value);
	void modify_int(GLuint location, int value);
	void modify_mat4(GLuint location, glm::mat4 mat);
	void modify_texture(GLuint location, int value);
	void check_if_modified();
	void set_last_access_time();

private:
	static GLuint load_shader(const std::string file_name, const GLenum shader_type);

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	std::string vertex_file, fragment_file;
	
protected:
	virtual void bind_attributes() = 0;
	virtual void get_all_uniform_locations() = 0;
	void bind_attribute(int attribute, std::string variable_name);
	double fragment_file_last_write_time;
	double vertex_file_last_write_time;
};

