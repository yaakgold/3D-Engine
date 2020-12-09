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

#pragma region OldCode


	// create vertex buffers
	/*hummus::VertexIndexArray vertexArray;
	vertexArray.Create("vertex");
	vertexArray.CreateBuffer(sizeof(vertices), sizeof(vertices) / (sizeof(float) * 5), vertices);
	vertexArray.SetAttribute(0, 3, 5 * sizeof(float), 0);
	vertexArray.SetAttribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));*/

	//create index buffers
	//vertexArray.CreateIndexBuffer(GL_UNSIGNED_SHORT, sizeof(indecies) / sizeof(GLushort), indecies);
#pragma endregion

	hummus::VertexArray vertexArray;
	vertexArray.Create("vertex");

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	hummus::Model::Load("models/cube.obj", positions, normals, texcoords);

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

	//vertexArray.CreateBuffer(sizeof(vertices), sizeof(vertices) / (sizeof(float) * 6), vertices);
	//vertexArray.SetAttribute(0, 3, 6 * sizeof(float), 0);
	//vertexArray.SetAttribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));

	//Uniform
	glm::mat4 model = glm::mat4(1.f);
	program.SetUniform("transform", model);

	//camera
	glm::vec3 eye{ 0, 0, 5 };
	hummus::Camera cam{ "Camera" };
	scene.Add(&cam);
	cam.SetProjection(45.f, 800 / 600.f, 0.01f, 1000.0f);
	cam.SetLookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//glm::mat4 projection = glm::perspective(glm::radians(45.f), 800 / 600.f, 0.01f, 1000.0f);
	//glm::mat4 view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	hummus::Texture texture;
	texture.CreateTexture("Textures\\ogre_diffuse_flip.bmp");

	hummus::Material mat{ glm::vec3{ 1 }, glm::vec3{ 1 }, glm::vec3{ 1 }, 32.0f };
	mat.AddTexture(texture);
	mat.SetProgram(program);

	hummus::Light light{ "light", hummus::Transform{{5, 2, 5}}, glm::vec3{ 0.1f }, glm::vec3{ 1 }, glm::vec3{ 1 } };
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

		model = glm::rotate(model, glm::pi<float>() * engine.GetTimer().DeltaTime(), glm::vec3(0, 1, 0));

		float angle = 0;

		glm::mat4 mvp = cam.projection() * cam.view() * model;

		program.SetUniform("mvp", mvp);

		glm::mat4 model_View = cam.view() * model;
		program.SetUniform("model_View", model_View);

		std::vector<hummus::Light*> lights = scene.Get<hummus::Light>();
		for (auto l : lights)
		{
			l->SetProgram(program);
		}

		//glm::vec4 position = cam.view() * light;
		//program.SetUniform("light.position", position);

		engine.GetSystem<hummus::Renderer>()->StartFrame();

		vertexArray.Draw();

		engine.GetSystem<hummus::Renderer>()->EndFrame();

	}

	engine.Shutdown();	

	return 0;
}