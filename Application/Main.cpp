#include "pch.h"
#include <glad\glad.h>
#include "Engine/Engine.h"
#include "Engine/Graphics/VertexIndexArray.h"

int main(int argc, char** argv)
{
	hummus::Engine engine;
	engine.Startup();
	//hummus::Renderer renderer;
	//renderer.Startup();
	//renderer.Create("OpenGL", 800, 600);

	//Init
	//float vertices[] =
	//{
	//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // point1
	//	 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, // point2
	//	 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f  // point3
	//};

	static float vertices[] =
	{
		//Front
		-1.f, -1.f, 1.f, 0.f, 0.f,
		1.f,  -1.f, 1.f, 1.f, 0.f,
		1.f,  1.f,  1.f, 1.f, 1.f,
		-1.f, 1.f,  1.f, 0.f, 1.f,
		//Back
		-1.f, -1.f, -1.f, 1.f, 0.f,
		1.f,  -1.f, -1.f, 0.f, 0.f,
		1.f,  1.f,  -1.f, 0.f, 1.f,
		-1.f, 1.f,  -1.f, 1.f, 1.f
	};

	static GLushort indecies[] =
	{
		//Front
		0, 1, 2,
		2, 3, 0,
		//Right
		1, 5, 6,
		6, 2, 1,
		//Back
		7, 6, 5,
		5, 4, 7,
		//Left
		4, 0, 3,
		3, 7, 4,
		//Bottom
		4, 5, 1,
		1, 0, 4,
		//Top
		3, 2, 6,
		6, 7, 3
	};

	hummus::Program program;
	program.CreateShaderFromFile("Shaders\\basic.vert", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("Shaders\\basic.frag", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	// create vertex buffers
	hummus::VertexIndexArray vertexArray;
	vertexArray.Create("vertex");
	vertexArray.CreateBuffer(sizeof(vertices), sizeof(vertices) / (sizeof(float) * 5), vertices);
	vertexArray.SetAttribute(0, 3, 5 * sizeof(float), 0);
	vertexArray.SetAttribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));

	//create index buffers
	vertexArray.CreateIndexBuffer(GL_UNSIGNED_SHORT, sizeof(indecies) / sizeof(GLushort), indecies);

	//Uniform
	glm::mat4 model = glm::mat4(1.f);
	program.SetUniform("transform", model);


	glm::mat4 projection = glm::perspective(glm::radians(45.f), 800 / 600.f, 0.01f, 1000.0f);

	glm::vec3 eye{ 0, 0, 5 };
	glm::mat4 view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	hummus::Texture texture;
	texture.CreateTexture("Textures\\llama.jpg");


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

		model = glm::rotate(model, glm::pi<float>() * engine.GetTimer().DeltaTime(), glm::vec3(0, 1, 0));

		float angle = 0;

#pragma region Inputs
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == hummus::InputSystem::eButtonState::HELD)
		{
			eye.x -= 4 * engine.GetTimer().DeltaTime();
		}
		else if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == hummus::InputSystem::eButtonState::HELD)
		{
			eye.x += 4 * engine.GetTimer().DeltaTime();
		}

		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == hummus::InputSystem::eButtonState::HELD)
		{
			eye.z -= 4 * engine.GetTimer().DeltaTime();
		}
		else if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == hummus::InputSystem::eButtonState::HELD)
		{
			eye.z += 4 * engine.GetTimer().DeltaTime();
		}

		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_Q) == hummus::InputSystem::eButtonState::HELD)
		{
			eye.y += 4 * engine.GetTimer().DeltaTime();
		}
		else if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_E) == hummus::InputSystem::eButtonState::HELD)
		{
			eye.y -= 4 * engine.GetTimer().DeltaTime();
		}
#pragma endregion

		view = glm::lookAt(eye, eye + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		glm::mat4 mvp = projection * view * model;

		program.SetUniform("transform", mvp);

		engine.GetSystem<hummus::Renderer>()->StartFrame();

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//GLsizei numElements = sizeof(indecies) / sizeof(GLushort);
		//glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, 0);
		
		vertexArray.Draw();

		engine.GetSystem<hummus::Renderer>()->EndFrame();

	}

	engine.Shutdown();	

	return 0;
}