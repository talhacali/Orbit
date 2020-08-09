#pragma once

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../glm/glm.hpp"
#include "../Camera/FlyCamera.h"

namespace Orbit
{
	class Game
	{
	public:
		void Init();
		void MainLoop();
		FlyCamera camera;

	private:
		GLFWwindow* window;
		
	};
}

