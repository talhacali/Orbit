#pragma once

#include <iostream>
#include <random>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/Camera/FlyCamera.h"

#include "ECS/include/ECS.h"
#include "../Dependencies/Renderer/Material.h"

#include "../Entities/Cube.h"
#include "../Components/Renderable.h"
#include "../Components/Transform.h"
#include "../Components/Movable.h"
#include "../Systems/Render.h"
#include "../Systems/Movement.h"

namespace Orbit
{
	class Game
	{
	public:
		void Init();
		void MainLoop();

		std::shared_ptr<Camera> camera;
		ECS::SystemHandle render;
		ECS::SystemHandle movement;
		std::vector<PointLight> pointLights;

	private:
		GLFWwindow* window;
		ECS::EntityComponentSystem ecs;
	};
}

