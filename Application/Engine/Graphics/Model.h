#pragma once

namespace hummus
{
	class Model
	{
	public:
		static bool Load(const std::string& filename, 
			std::vector<glm::vec3>& positions, 
			std::vector<glm::vec3>& normals, 
			std::vector<glm::vec2>& texcoords);
	};
}