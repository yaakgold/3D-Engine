#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

namespace hummus
{
	bool Texture::Create(const std::string& fileName, void* renderer)
	{
		return CreateTexture(fileName);
	}

	void Texture::Destroy()
	{
		glDeleteTextures(1, &m_texture);
	}

	bool Texture::CreateTexture(const std::string& fileName, GLenum target, GLuint uint)
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (surface == nullptr)
		{
			SDL_Log("Failed to create surface: %s", SDL_GetError());
			return false;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(target, m_texture);

		GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP);

		return true;
	}
}