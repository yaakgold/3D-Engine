#pragma once
#include "Math.h"

namespace hummus
{
	struct Transform
	{
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform() : translation{ 0 }, rotation{ 0 }, scale{ 1 } {}
		Transform(const glm::vec3& translation, const glm::vec3& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 }) :
			translation {translation},
			rotation{ rotation },
			scale{ scale } {}

		operator glm::mat4() const
		{
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), scale);
			glm::mat4 rotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1), translation);

			return (translationMatrix * rotationMatrix * scaleMatrix);
		}

	};
}