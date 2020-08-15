#pragma once

#include "../glm/glm.hpp"
#include "../Renderer/Shader.h"

namespace Orbit
{
	class DirectionalLight
	{
	public:
		DirectionalLight() = default;
		DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular):
			direction(direction),ambient(ambient),diffuse(diffuse),specular(specular){}

		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}