#pragma once
#include <string>
#ifdef _DEBUG	
	#include <iostream>
	#define LOG(str) std::cout << str << std::endl
#else
	#define LOG(str)
#endif

#define LOG_WARNING_FILE_CANNOT_OPEN(path) LOG(std::string("Warning::Cannot open file: ") + path)
#define LOG_WARNING(str) LOG(std::string("Warning::") + str)