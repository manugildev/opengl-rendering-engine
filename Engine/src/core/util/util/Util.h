#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

// TODO: Remove Util from the util folder and make it a static class with no .cpp

class Util {
public:
	static std::string readFile(const char *filePath);
	static bool parse_file_into_str(const char *file_name, char *shader_str, int max_len);
	static float random_range(float LO, float HI);
	static std::string get_dir_by_path(std::string path);

};