#pragma once
#include <Engine/Core/System.h>

namespace hummus
{
	class Renderer : public System
	{
	public:
		virtual bool Startup() override;
		virtual void Update() override;
		virtual void Shutdown() override;

		bool Create(const std::string& windowName, int w, int h);
		void StartFrame();
		void EndFrame();

		friend class Texture;

	protected:
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
		SDL_GLContext m_context;
	};
}