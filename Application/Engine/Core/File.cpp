#include "pch.h"
#include "File.h"
#include <sstream>

namespace hummus
{
	bool ReadFileToString(const std::string& filename, std::string& filestring)
	{
		std::ifstream fileStream(filename, std::ios::in);
		if (!fileStream.is_open())
		{
			SDL_Log("Error: Failed to open file: %s", filename.c_str());
			return false;
		}

		std::stringstream content;
		content << fileStream.rdbuf();
		fileStream.close();

		filestring = content.str();

		return true;
	}
}
