#include <iostream>
#include "logger.h"

#pragma warning(disable : 4996)

void Logger::writeLog(std::string const &log)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10 + 1)));
	sMtx_.lock();
	logFile_.open(LOG_FILE_NAME, std::ios::app);
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
	logFile_ << "[" << oss.str() << "] " << log << std::endl;
	logFile_.close();
	std::cout << "\033[45mthread# " << std::setw(7) << std::this_thread::get_id() << std::setw(51) \
		<< " \033[45mwrite: \033[0m \033[43m \033[0m \033[35m" \
		<< log << "\033[0m" << std::endl;
	sMtx_.unlock();
}

void Logger::readLog(size_t strID)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10 + 1)));
	sMtx_.lock();
	logFile_.open(LOG_FILE_NAME, std::ios::in);
	std::string str;
	size_t counter = 1;
	while (!logFile_.eof())
	{
		getline(logFile_, str);
		if (strID == counter)
			break;
		++counter;
	}
	logFile_.close();
	if (!str.empty())
		std::cout << "\033[46mthread# " << std::setw(7) << std::this_thread::get_id() << std::setw(20) << " read string# "\
		<< std::setw(3) << strID << ": \033[0m \033[43m \033[0m \033[36m" << str << "\033[0m" << std::endl;
	else
		std::cout << "\033[100mthread# " << std::setw(7) << std::this_thread::get_id() << std::setw(20) << " read string# "\
		<< std::setw(3) << strID << ": \033[0m " << "\033[43m \033[0m" << " not found" << std::endl;
	sMtx_.unlock();
}

Logger::Logger()
{
	logFile_.open(LOG_FILE_NAME, std::ios::out | std::ios::in );
	if (!logFile_.is_open())
	{
		logFile_.open(LOG_FILE_NAME, std::ios::out | std::ios::in | std::ios::trunc);
		if (!logFile_.is_open())
			std::cout << "error IO" << LOG_FILE_NAME
				<< std::endl;
	}
	logFile_.close();
}

Logger::~Logger()
{
	logFile_.close();
}

