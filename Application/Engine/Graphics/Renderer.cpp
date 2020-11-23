#include "pch.h"
#include "Renderer.h"
#include <glad/glad.h>

namespace hummus
{
    bool hummus::Renderer::Startup()
    {
        int result = SDL_Init(SDL_INIT_VIDEO);
        if (result != 0)
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        }

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

        return true;
    }

    void hummus::Renderer::Update()
    {

    }

    void hummus::Renderer::Shutdown()
    {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
    }

    bool Renderer::Create(const std::string& windowName, int w, int h)
    {
        m_window = SDL_CreateWindow(windowName.c_str(), 100, 100, w, h, SDL_WINDOW_OPENGL);
        if (m_window == nullptr)
        {
            SDL_Log("Failed to create windw: %s", SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetSwapInterval(1);

        m_context = SDL_GL_CreateContext(m_window);
        if (!gladLoadGL())
        {
            SDL_Log("Failed to create OpenGL context");
            exit(-1);
        }

        glViewport(0, 0, 800, 600);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return true;
    }

    void Renderer::StartFrame()
    {
        glClearColor(0.0f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndFrame()
    {
        SDL_GL_SwapWindow(m_window);
    }
}
