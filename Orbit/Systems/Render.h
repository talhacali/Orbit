#pragma once

#include "ECS/include/System.h"
#include "ECS/include/ECS.h"
#include "../Components/Renderable.h"
#include "../Components/Transform.h"
#include "../glm/glm.hpp"

namespace Orbit
{
	class Render : public ECS::System<Render>
	{
	public:
		Render(ECS::EntityComponentSystem* ecsInstance_) { ecsInstance = ecsInstance_; }
		ECS::EntityComponentSystem* ecsInstance;
		void Init() override;
		void Update(float dt) override;
	};

}