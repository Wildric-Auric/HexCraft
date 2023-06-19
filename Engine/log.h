#pragma once
#include <string>
#ifdef _DEBUG	
	#include <iostream>
	#include <glew.h>
	#define LOG(str) std::cout << str << std::endl
	#define LOG_OPENGL_ERROR() if (int __log_err = glGetError())\
										LOG(std::to_string(__log_err));
#else
	#define LOG(str)
	#define LOG_OPENGL_ERROR() 
#endif

#define LOG_WARNING_FILE_CANNOT_OPEN(path) LOG(std::string("Warning::Cannot open file: ") + path)
#define LOG_WARNING(str) LOG(std::string("Warning::") + str)