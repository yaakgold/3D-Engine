#pragma once
#include <string>

#ifndef NDEBUG

#define ASSERT(condition) _assert((!!condition), #condition, __FILE__, __LINE__, __func__)
#define ASSERT_MSG(condition, message) _assert((!!condition), #condition, __FILE__, __LINE__, __func__, message)

#else

#define ASSERT(condition) ((void)0)
#define ASSERT_MSG(condition, message) ((void)0)

#endif

void _assert(bool condition, 
	const std::string& conditionString, 
	const std::string& fileName, 
	int line,
	const std::string& functionName);

void _assert(bool condition, 
	const std::string& conditionString, 
	const std::string& fileName,
	int line, 
	const std::string& functionName,
	const std::string& message);