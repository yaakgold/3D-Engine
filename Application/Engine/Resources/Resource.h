#pragma once
#include <string>

namespace hummus
{
	class Resource
	{
	public:
		virtual bool Create(const std::string& fileName, void* data = nullptr) = 0;
		virtual void Destroy() = 0;
	};
}