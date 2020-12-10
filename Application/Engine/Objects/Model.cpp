#include "pch.h"
#include "Model.h"
#include <sstream> 
#include "Camera.h"
#include "Scene.h"

namespace hummus
{
	bool Model::Load(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords)
	{
		std::vector<glm::vec3> model_positions;
		std::vector<glm::vec3> model_normals;
		std::vector<glm::vec2> model_texcoords;

		std::ifstream stream(filename, std::ios::binary);
		if (!stream.is_open())
		{
			SDL_Log("Error opening model file: %s", filename.c_str());
			return false;
		}

		//Read model data

		std::string line;
		while (std::getline(stream, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				std::istringstream string_stream{ line.substr(2) };
				glm::vec3 pos;
				string_stream >> pos.x;
				string_stream >> pos.y;
				string_stream >> pos.z;

				model_positions.push_back(pos);
			}
			else if (line.substr(0, 3) == "vn ")
			{
				std::istringstream string_stream{ line.substr(3) };
				glm::vec3 norm;
				string_stream >> norm.x;
				string_stream >> norm.y;
				string_stream >> norm.z;

				model_normals.push_back(norm);
			}
			else if (line.substr(0, 3) == "vt ")
			{
				std::istringstream string_stream{ line.substr(3) };
				glm::vec2 coord;
				string_stream >> coord.x;
				string_stream >> coord.y;

				model_texcoords.push_back(coord);
			}
			//else if (line.substr(0, 2) == "f ")
			//{
			//	std::istringstream stream{ line.substr(2) };
			//	std::string str; 
			//	while (std::getline(stream, str, ' '))
			//	{
			//		std::istringstream stream(str); 
			//		std::string indexString; 
			//		size_t i = 0;
			//		unsigned int index[3] = { 0, 0, 0 };// position, texcoord, normal
			//											
			//		// read each index separated by '/'
			//		while (std::getline(stream, indexString, '/'))
			//		{
			//			if (!indexString.empty())
			//			{
			//				std::istringstream indexStream{ indexString };
			//				indexStream >> index[i];
			//			}
			//			i++;
			//		}
			//		if (index[0])
			//		{
			//			glm::vec3 position = model_positions[index[0] - 1];
			//			positions.push_back(position);
			//		}
			//		
			//		if (index[1]) 
			//		{
			//			glm::vec3 normal = model_normals[index[1] - 1];
			//			normals.push_back(normal);
			//		}
			//		
			//		if (index[2])
			//		{
			//			glm::vec2 texCoord = model_texcoords[index[2] - 1];
			//			texcoords.push_back(texCoord);
			//		}
			//	}
			//}
			else if (line.substr(0, 2) == "f ")
			{
				std::istringstream sstream{ line.substr(2) };
				std::string str;
				while (std::getline(sstream, str, ' '))
				{
					std::istringstream sstream(str);
					std::string indexString;

					size_t i = 0;
					unsigned int index[3] = { 0, 0, 0 };
					while (std::getline(sstream, indexString, '/'))
					{
						if (!indexString.empty())
						{
							std::istringstream indexStream{ indexString };
							indexStream >> index[i];
						}
						i++;
					}

					if (index[0])
					{
						glm::vec3 position = model_positions[index[0] - 1];
						positions.push_back(position);
					}

					if (index[1])
					{
						glm::vec2 texcoord = model_texcoords[index[1] - 1];
						texcoords.push_back(texcoord);
					}

					if (index[2])
					{
						glm::vec3 normal = model_normals[index[2] - 1];
						normals.push_back(normal);
					}
				}

			}
		}

		stream.close();

		return true;
	}

	VertexArray Model::Load(const std::string& fileName)
	{
		VertexArray vertexArray;
		vertexArray.Create("vertex");

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texcoords;
		Model::Load(fileName, positions, normals, texcoords);

		if (!positions.empty())
		{
			vertexArray.CreateBuffer(positions.size() * sizeof(glm::vec3), static_cast<GLsizei>(positions.size()), positions.data());
			vertexArray.SetAttribute(0, 3, 0, 0);
		}

		if (!normals.empty())
		{
			vertexArray.CreateBuffer(normals.size() * sizeof(glm::vec3), static_cast<GLsizei>(normals.size()), normals.data());
			vertexArray.SetAttribute(1, 3, 0, 0);
		}

		if (!texcoords.empty())
		{
			vertexArray.CreateBuffer(texcoords.size() * sizeof(glm::vec2), static_cast<GLsizei>(texcoords.size()), texcoords.data());
			vertexArray.SetAttribute(2, 2, 0, 0);
		}


		return vertexArray;
	}

	void Model::Draw()
	{
		m_program.Use();

		m_material.SetProgram(m_program);

		Camera* camera = m_scene->Get<Camera>("Camera");
		ASSERT(camera != NULL);

		glm::mat4 mvp = camera->projection() * camera->view() * (glm::mat4)m_transform;
		m_program.SetUniform("mvp", mvp);

		glm::mat4 model_view = camera->view() * (glm::mat4)m_transform;
		m_program.SetUniform("model_view", model_view);

		m_vertexArray.Draw(GL_TRIANGLES);
	}
}
