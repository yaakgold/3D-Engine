#include "pch.h"
#include <glad\glad.h>
#include "Engine/Engine.h"
#include "Engine/Graphics/VertexIndexArray.h"

int main(int argc, char** argv)
{
	hummus::Engine engine;
	engine.Startup();

	hummus::Scene scene{ &engine };

#pragma region OldVerts

	//static float vertices[] =
	//{
	//	//Front
	//	-1.f, -1.f, 1.f, 0.f, 0.f,
	//	1.f,  -1.f, 1.f, 1.f, 0.f,
	//	1.f,  1.f,  1.f, 1.f, 1.f,
	//	-1.f, 1.f,  1.f, 0.f, 1.f,
	//	//Back
	//	-1.f, -1.f, -1.f, 1.f, 0.f,
	//	1.f,  -1.f, -1.f, 0.f, 0.f,
	//	1.f,  1.f,  -1.f, 0.f, 1.f,
	//	-1.f, 1.f,  -1.f, 1.f, 1.f
	//};

	//static GLushort indecies[] =
	//{
	//	//Front
	//	0, 1, 2,
	//	2, 3, 0,
	//	//Right
	//	1, 5, 6,
	//	6, 2, 1,
	//	//Back
	//	7, 6, 5,
	//	5, 4, 7,
	//	//Left
	//	4, 0, 3,
	//	3, 7, 4,
	//	//Bottom
	//	4, 5, 1,
	//	1, 0, 4,
	//	//Top
	//	3, 2, 6,
	//	6, 7, 3
	//};
#pragma endregion

	static float vertices[] =
	{
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,

		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,

		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
	};

	hummus::Program program;
	program.CreateShaderFromFile("Shaders\\phong.vert", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("Shaders\\phong.frag", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	hummus::VertexArray vertexArray = hummus::Model::Load("models/ogre.obj");

	hummus::Texture texture;
	texture.CreateTexture("Textures\\ogre_diffuse_flip.bmp");

	hummus::Material mat{ glm::vec3{ 1 }, glm::vec3{ 1 }, glm::vec3{ 1 }, 32.0f };
	mat.AddTexture(texture);
	mat.SetProgram(program);

	hummus::Model model{ "model", hummus::Transform{}, vertexArray, program, mat };
	scene.Add(&model);

	//camera
	glm::vec3 eye{ 0, 0, 5 };
	hummus::Camera cam{ "Camera" };
	scene.Add(&cam);
	cam.SetProjection(45.f, 800 / 600.f, 0.01f, 1000.0f);
	cam.SetLookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	hummus::Light light{ "light", hummus::Transform{{5, 2, 5}}, glm::vec3{ 0.5f }, glm::vec3{ 1 }, glm::vec3{ 1 } };
	scene.Add(&light);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		default:
			break;
		}

		SDL_PumpEvents();
		engine.Update();

		scene.Update(engine.GetTimer().DeltaTime());

		float angle = 0;
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_R) == hummus::InputSystem::eButtonState::HELD)
		{
			angle = 2.0f;
		}
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_T) == hummus::InputSystem::eButtonState::HELD)
		{
			angle = -2.0f;
		}

		model.transform().rotation.y += angle * engine.GetTimer().DeltaTime();

		std::vector<hummus::Light*> lights = scene.Get<hummus::Light>();
		for (auto l : lights)
		{
			l->SetProgram(program);
		}

		engine.GetSystem<hummus::Renderer>()->StartFrame();

		scene.Draw();

		engine.GetSystem<hummus::Renderer>()->EndFrame();

	}

	engine.Shutdown();	

	return 0;
}