#pragma once

#ifdef _DEBUG	
	#include <iostream>
	#define LOG(str) std::cout << str << std::endl;
#else
	#define LOG(str)
#endif