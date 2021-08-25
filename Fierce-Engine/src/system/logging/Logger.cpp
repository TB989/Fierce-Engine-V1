#include "Logger.h"

#include <time.h>

HANDLE Logger::handle = GetStdHandle(STD_OUTPUT_HANDLE);
bool Logger::useColors = true;
bool Logger::printType = false;
bool Logger::printName = true;
bool Logger::printDate = false;
bool Logger::printTime = true;

Logger::Logger(std::string name) {
	m_name = name;
}

void Logger::log(const char* type, const char* text, ...) {
	if (printDate || printTime) {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		if (printDate)
			printf("[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		if (printTime)
			printf("[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	}
	if (printName)
		printf("[%s]", m_name.c_str());
	if (printType)
		printf("[%s]", type);

	printf(": ");
	va_list valist;
	va_start(valist, text);
	vprintf(text, valist);
	va_end(valist);
	printf("\n");
}

void Logger::info(const char* text, ...) {
	if (useColors)
		SetConsoleTextAttribute(handle, 2);
	if (printDate || printTime) {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		if (printDate)
			printf("[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		if (printTime)
			printf("[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	}
	if (printName)
		printf("[%s]", m_name.c_str());
	if (printType)
		printf("[%s]", "INFO");

	printf(": ");
	va_list valist;
	va_start(valist, text);
	vprintf(text, valist);
	va_end(valist);
	printf("\n");
}

void Logger::warn(const char* text, ...) {
	if (useColors)
		SetConsoleTextAttribute(handle, 6);
	if (printDate || printTime) {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		if (printDate)
			printf("[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		if (printTime)
			printf("[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	}
	if (printName)
		printf("[%s]", m_name.c_str());
	if (printType)
		printf("[%s]", "WARNING");

	printf(": ");
	va_list valist;
	va_start(valist, text);
	vprintf(text, valist);
	va_end(valist);
	printf("\n");
}

void Logger::error(const char* text, ...) {
	if (useColors)
		SetConsoleTextAttribute(handle, 4);
	if (printDate || printTime) {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		if (printDate)
			printf("[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		if (printTime)
			printf("[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	}
	if (printName)
		printf("[%s]", m_name.c_str());
	if (printType)
		printf("[%s]", "ERROR");

	printf(": ");
	va_list valist;
	va_start(valist, text);
	vprintf(text, valist);
	va_end(valist);
	printf("\n");
}

Logger* Loggers::CORE = new Logger("CORE");
Logger* Loggers::GL = new Logger("GL");
Logger* Loggers::VK = new Logger("VK");
Logger* Loggers::DX = new Logger("DX");
Logger* Loggers::MATH = new Logger("MATH");
Logger* Loggers::ECS = new Logger("ECS");