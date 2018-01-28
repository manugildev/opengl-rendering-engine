#pragma once

#include <ostream>

#define LOG_MESSAGE(MESSAGE) logger->print(MESSAGE);

class Logger {
public:
	Logger();
	~Logger();

	void print(const std::string message) const;

private:
	std::ostream *logStream;
};

extern Logger *logger;