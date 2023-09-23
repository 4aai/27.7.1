#pragma once
#include <string>
#include <fstream>
#include <shared_mutex>
#include <ctime>
#include <iomanip>
#include <sstream>
constexpr auto LOG_FILE_NAME = "logs.txt";
class Logger
{
	std::fstream logFile_;
	std::shared_mutex sMtx_;
	
public:

	void writeLog(std::string const& messageToLog);
	void readLog(size_t stringNumber);
	Logger();
	~Logger();
};