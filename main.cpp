#include <vector>
#include "logger.h"
#include <iostream>
int main()
{
	Logger logger;
	std::vector<std::string> logs;
	std::vector<std::thread> threads{};
	srand((unsigned int) time(NULL));
	std::cout << "\033[45m HELLO THREADS \033[0m" << std::endl;
	for (auto i = 0; i < 100; i++)
	{
		logs.push_back("User" + std::to_string(static_cast<size_t>(rand() % 10) + 1) + " to User"\
			+ std::to_string(static_cast<size_t>(rand() % 10) + 1) + " : test msg");
	}
	for (auto i = 0; i < 100; i++)
	{
		logs.push_back("User" + std::to_string(static_cast<size_t>(rand() % 10) + 1) + " connected!");
	}
	for (auto i = 0; i < 100; i++)
	{
		logs.push_back("User" + std::to_string(static_cast<size_t>(rand() % 10) + 1) + " disconnected!");
	}
	for (auto i = 0; i < 100; i++)
	{
		logs.push_back("database error");
	}
	for (auto i = 0; i < 100; i++)
	{
		logs.push_back("network error");
	}
	for (auto i = 0; i < logs.size() * 2; i += 2)
	{
		threads.push_back(std::thread(&Logger::writeLog, std::ref(logger), std::ref(logs[i / 2])));
		threads.push_back(std::thread(&Logger::readLog,  std::ref(logger), static_cast<size_t>(rand() % 999) + 1));
	}

	for (auto & threads : threads) threads.join();

	return 0;
}