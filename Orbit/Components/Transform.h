#pragma once
#include "ECS/include/Component.h"
#include "../Dependencies/glm/glm.hpp"

namespace Orbit
{
	class Transform : public ECS::Component<Transform>
	{
	public:
		Transform(glm::vec3 position, glm::vec3 rotation, float angle);
		glm::vec3 position, rotation;
		float angle;
	};
}