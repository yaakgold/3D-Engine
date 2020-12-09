#include "pch.h"
#include "Light.h"
#include "Camera.h"
#include "Scene.h"

namespace hummus
{
	void Light::SetProgram(Program& program)
	{
		program.Use();

		program.SetUniform("light.ambient", ambient);
		program.SetUniform("light.diffuse", diffuse);
		program.SetUniform("light.specular", specular);

		Camera* camera = m_scene->Get<Camera>("Camera");
		glm::vec4 position = camera->view() * glm::vec4(m_transform.translation, 1);
		program.SetUniform("light.position", position);
	}
}