#include "Movement.h"
#include <cmath>

namespace Orbit
{
	void Orbit::Movement::Init()
	{
		time = 0;
	}

	void Orbit::Movement::Update(float dt)
	{
		time += dt;

		const float PI = 3.141592653589793238463f;
		for (auto it : entities)
		{
			Transform* transform = (Transform*) ecsInstance->GetComponent<Transform>(it);
			Movable* movable = (Movable*) ecsInstance->GetComponent<Movable>(it);

			float x, z;

			transform->position.x -= movable->centerPoint.x;
			transform->position.z -= movable->centerPoint.z;

			x = transform->position.x * cos(dt * movable->speed) - transform->position.z * sin(dt * movable->speed);
			z = transform->position.x * sin(dt * movable->speed) + transform->position.z * cos(dt * movable->speed);

			transform->position.x = x + movable->centerPoint.x;
			transform->position.z = z + movable->centerPoint.z;

			/*transform->position.x += sin(time) * movable->radius * movable->speed;
			transform->position.z += cos(time) * movable->radius * movable->speed;*/


			/*float x = transform->position.x, y = transform->position.y;
			
			transform->position.x = movable->centerPoint.x + ((x - movable->centerPoint.x) * cos(time) * movable->speed)
				- ((y - movable->centerPoint.y) * sin(time) * movable->speed);
			transform->position.y = movable->centerPoint.y + ((x - movable->centerPoint.x) * sin(time) * movable->speed)
				+ ((y - movable->centerPoint.y) * cos(time) * movable->speed);*/
			
		}

	}
}


