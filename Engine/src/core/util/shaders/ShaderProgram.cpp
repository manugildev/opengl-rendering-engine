#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include "..\Logger.h"
#include <windows.h>

ShaderProgram::ShaderProgram(std::string vertex_file, std::string fragment_file) : vertex_file(vertex_file), fragment_file(fragment_file) {
	vertex_shader_id = load_shader(vertex_file, GL_VERTEX_SHADER);
	fragment_shader_id = load_shader(fragment_file, GL_FRAGMENT_SHADER);

	program_id = glCreateProgram();
	if (program_id == 0) LOG_MESSAGE("Error creating shader program\n");

	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	this->set_last_access_time();
}

void ShaderProgram::init() {
	bind_attributes();
	if (!link_shader()) return;
	if (!validate_shader()) return;
	get_all_uniform_locations();
}

int ShaderProgram::link_shader() {
	GLint success = 0;
	GLchar error_log[1024] = { 0 };

	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program_id, sizeof(error_log), NULL, error_log);
		std::cout << "\n=============================================================" << std::endl;
		fprintf_s(stderr, "Error linking shader program: '%s'", error_log);
		std::cout << "\n=============================================================" << std::endl;
		return 0;
	}
	return 1;
}

int ShaderProgram::validate_shader() {
	GLint success = 0;
	GLchar error_log[1024] = { 0 };

	glValidateProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program_id, sizeof(error_log), NULL, error_log);
		std::cout << "\n=============================================================" << std::endl;
		fprintf_s(stderr, "Error validating shader program: '%s'", error_log);
		std::cout << "\n=============================================================" << std::endl;
		return 0;
	}
	return 1;
}

void ShaderProgram::start() {
	glUseProgram(program_id);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::bind_attribute(int attribute, std::string variable_name) {
	glBindAttribLocation(program_id, attribute, variable_name.c_str());
}

GLuint ShaderProgram::get_uniform_location(std::string uniform_name) {
	return glGetUniformLocation(program_id, uniform_name.c_str());
}

#pragma region SHADER_SETTERS
void ShaderProgram::modify_vec3(GLuint location, glm::vec3 vector) {
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::modify_boolean(GLuint location, bool value) {
	glUniform1i(location, value ? 1 : 0);
}

void ShaderProgram::modify_float(GLuint location, float value) {
	glUniform1f(location, value);
}

void ShaderProgram::modify_int(GLuint location, int value) {
	glUniform1i(location, value);
}

void ShaderProgram::modify_mat4(GLuint location, glm::mat4 mat) {
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::modify_texture(GLuint location, int value) {
	glUniform1i(location, value);
}

void ShaderProgram::check_if_modified() {
	__int64* val_v;
	__int64* val_f;
	WIN32_FILE_ATTRIBUTE_DATA fInfo;
	GetFileAttributesEx(vertex_file.c_str(), GetFileExInfoStandard, &fInfo);
	val_v = (__int64*)&fInfo.ftLastWriteTime;
	double time_vertex = static_cast<double>(*val_v) / 10000000.0 - 11644473600.0;
	GetFileAttributesEx(fragment_file.c_str(), GetFileExInfoStandard, &fInfo);
	val_f = (__int64*)&fInfo.ftLastWriteTime;
	double time_fragment = static_cast<double>(*val_f) / 10000000.0 - 11644473600.0;


	if (time_vertex != vertex_file_last_write_time || time_fragment != fragment_file_last_write_time) {
		vertex_file_last_write_time = time_vertex;
		fragment_file_last_write_time = time_fragment;
		this->reload();
		std::cout << "Shader has changed" << std::endl;
	}
}

void ShaderProgram::set_last_access_time(){
	__int64* val_v;
	__int64* val_f;
	WIN32_FILE_ATTRIBUTE_DATA fInfo;
	GetFileAttributesEx(vertex_file.c_str(), GetFileExInfoStandard, &fInfo);
	val_v = (__int64*)&fInfo.ftLastWriteTime;
	vertex_file_last_write_time = static_cast<double>(*val_v) / 10000000.0 - 11644473600.0;
	GetFileAttributesEx(fragment_file.c_str(), GetFileExInfoStandard, &fInfo);
	val_f = (__int64*)&fInfo.ftLastWriteTime;
	fragment_file_last_write_time = static_cast<double>(*val_f) / 10000000.0 - 11644473600.0;
}


#pragma endregion

GLuint ShaderProgram::load_shader(const std::string file_name, const GLenum shader_type) {
	std::ifstream file(file_name.c_str());
	if (file.fail()) {
		char temp[300];
		sprintf_s(temp, "Ërror loading shader file: %s", file_name.c_str());
		LOG_MESSAGE(temp);
	}

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();

	// TODO: Clean this
	std::string shader_text = stream.str();
	const char * shader_source = (const GLchar *)shader_text.c_str();

	GLuint shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &shader_source, NULL);
	glCompileShader(shader_id);

	GLint success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar info_log[1024];
		glGetShaderInfoLog(shader_id, 1024, NULL, info_log);
		std::cout << "\n=============================================================" << std::endl;
		fprintf_s(stderr, "Error compiling shader.\nShader_Name: %s - Type %d\n'%s'", file_name.c_str(), shader_type, info_log);
		std::cout << "\n=============================================================" << std::endl;
		return 0;
	}

	return shader_id;
}

void ShaderProgram::reload() {
	// Unbind the Shader just for being safe
	this->stop();

	// We detach and delete the shaders 
	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	// Load the files again
	this->vertex_shader_id = load_shader(vertex_file, GL_VERTEX_SHADER);
	this->fragment_shader_id = load_shader(fragment_file, GL_FRAGMENT_SHADER);
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	// Bind, link and validate shaders
	this->bind_attributes();
	if (!this->link_shader()) return;
	if (!this->validate_shader()) return;
	this->get_all_uniform_locations();

	this->set_last_access_time();


}



ShaderProgram::~ShaderProgram() {
	stop();
	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	glDeleteProgram(program_id);
}