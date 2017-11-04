#include "Logger.h"
#include <ctime>
#include <iostream>
#include <iomanip>

Logger *logger = new Logger();

Logger::Logger() {
	if (!logger) {
		logStream = &std::cout;
	}
}

// TODO: Support different types of messages and colors for those messages
void Logger::print(const std::string message) const {
	if (!logger) return;
	time_t rawtime = std::time(nullptr);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);

	*logStream << std::put_time(&timeinfo, "%d/%m/%Y %H:%M:%S") << " - " << message.c_str() << std::endl;

}

Logger::~Logger() {
	delete logStream;
	delete logger;

}
