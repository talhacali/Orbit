#pragma once

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../glm/glm.hpp"
#include "../Camera/FlyCamera.h"

#include "ECS/include/ECS.h"
#include "../Renderer/Material.h"

#include "../Entities/Cube.h"
#include "../Components/Renderable.h"
#include "../Components/Transform.h"
#include "../Systems/Render.h"

namespace Orbit
{
	class Game
	{
	public:
		void Init();
		void MainLoop();
		std::shared_ptr<Camera> camera;

		ECS::EntityHandle cube;
		ECS::ComponentHandle renderable;
		ECS::ComponentHandle transform;
		ECS::SystemHandle render;

		std::vector<PointLight> pointLights;

	private:
		GLFWwindow* window;
		ECS::EntityComponentSystem ecs;
		

		/*
		ECS::EntityHandle cube;
		ECS::ComponentHandle renderable;
		ECS::ComponentHandle transform;
		ECS::SystemHandle render;*/
	};
}

