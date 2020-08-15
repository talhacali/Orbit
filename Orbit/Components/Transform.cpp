#include "Transform.h"

namespace Orbit
{
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, float angle)
	{
		this->position = position;
		this->rotation = rotation;
		this->angle = angle;
	}
}