#pragma once
#include "Util.h"

std::string Util::readFile(const char *filePath) {
	std::cout << filePath << std::endl;
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

bool Util::parse_file_into_str(const char *file_name, char *shader_str, int max_len) {
	shader_str[0] = '\0'; // reset string
	FILE *file = fopen(file_name, "r");
	if (!file) {
		printf("ERROR: opening file for reading: %s\n", file_name);
		return false;
	}
	int current_len = 0;
	char line[2048];
	strcpy(line, ""); // remember to clean up before using for first time!
	while (!feof(file)) {
		if (NULL != fgets(line, 2048, file)) {
			current_len += strlen(line); // +1 for \n at end
			if (current_len >= max_len) {
				printf("ERROR: shader length is longer than string buffer length %i\n",
					   max_len);
			}
			strcat(shader_str, line);
		}
	}
	if (EOF == fclose(file)) { // probably unnecesssary validation
		printf("ERROR: closing file from reading %s\n", file_name);
		return false;
	}
	return true;
}

float Util::random_range(float LO, float HI) {
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

std::string Util::get_dir_by_path(std::string path) {
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = path.find_last_of("/");
	std::string dir;

	if (SlashIndex == std::string::npos)  dir = ".";
	else if (SlashIndex == 0) dir = "/";
	else dir = path.substr(0, SlashIndex);
	return dir;
}
