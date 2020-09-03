#pragma once

#include "ECS/include/Component.h"
#include "../Dependencies/glm/glm.hpp"

namespace Orbit
{
	class Movable : public ECS::Component<Movable>
	{
	public:
		Movable(glm::vec3 centerPoint_,float speed_) : centerPoint(centerPoint_), speed(speed_){}
		glm::vec3 centerPoint;
		float speed;
	};
}
