#pragma once
#include <Engine/Resources/Resource.h>
#include <string>
#include <SDL.h>

namespace hummus
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& fileName, void* null) override;
		void Destroy() override;

		bool CreateTexture(const std::string& filename, GLenum target = GL_TEXTURE_2D, GLuint uint = GL_TEXTURE0);

	protected:
		GLenum m_target{ GL_TEXTURE_2D };
		GLuint m_unit{ GL_TEXTURE0 };
		GLuint m_texture{ 0 };
	};
}