#pragma once

#include "ECS/include/Component.h"
#include <memory>
#include "../Dependencies/Renderer/Material.h"

namespace Orbit
{
	class Renderable : public ECS::Component<Renderable>
	{
	public:
		Renderable(Material material, float persWidth, float persHeight,
			std::shared_ptr<Camera> camera);

		std::shared_ptr<Camera> camera;
		Material material;
		unsigned int VBO, VAO;
		std::vector<float> vertices;
		float persWidth, persHeight;
	};

}