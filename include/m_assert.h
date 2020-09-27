#pragma once

#include <iostream>

#define m_assert(expr, msg) \
	if(!(expr)) { \
		std::cerr << "[Error]: " << msg << std::endl; \
		abort(); \
	} \
