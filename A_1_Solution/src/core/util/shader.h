#pragma once
#include <fstream>
#include <sstream>
#include "Logger.h"

std::string read_shader_source(const std::string & file_name) {
	std::ifstream file(file_name.c_str());
	if (file.fail()) {
		char temp[300];
		sprintf_s(temp, "Ërror loading shader; %s", file_name);
		LOG_MESSAGE(temp);
		exit(1);
	}

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	return stream.str();
}