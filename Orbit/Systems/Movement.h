#pragma once

#include "ECS/include/ECS.h"
#include "ECS/include/System.h"

#include "../Components/Movable.h"
#include "../Components/Transform.h"

#include "../Dependencies/glm/glm.hpp"

namespace Orbit
{
	class Movement : public ECS::System<Movement>
	{
	public:
		Movement(ECS::EntityComponentSystem* ecsInstance_) { ecsInstance = ecsInstance_; }
		ECS::EntityComponentSystem* ecsInstance;
		void Init() override;
		void Update(float dt) override;
	private:
		float time;
	};
}
