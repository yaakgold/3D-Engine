#include "pch.h"
#include <glad\glad.h>
#include "Engine/Graphics/Program.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Texture.h"

int main(int argc, char** argv)
{
	hummus::Renderer renderer;
	renderer.Startup();
	renderer.Create("OpenGL", 800, 600);

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
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set position pipeline (vertex attribute)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//set uv pipeline (vertex attribute)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//create index buffers
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	//Uniform
	glm::mat4 transform = glm::mat4(1.f);
	program.SetUniform("transform", transform);

	glm::mat4 projection = glm::perspective(glm::radians(45.f), 800 / 600.f, 0.01f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 2, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

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

		transform = glm::rotate(transform, 0.0004f, glm::vec3(0, 1, 0));

		glm::mat4 mvp = projection * view * transform;

		program.SetUniform("transform", mvp);

		renderer.StartFrame();

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		GLsizei numElements = sizeof(indecies) / sizeof(GLushort);
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, 0);
		
		renderer.EndFrame();

	}

	return 0;
}