#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

class Util {
public:
	static std::string readFile(const char *filePath);
	static bool parse_file_into_str(const char *file_name, char *shader_str, int max_len);
	static float random_range(float LO, float HI);

};