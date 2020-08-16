#pragma once

#include "ISystem.h"
#include <vector>

namespace ECS
{
	class SystemHandle
	{
	public:
		SystemHandle() : systemId(0), classID(0) {}
		SystemHandle(unsigned int systemID_, unsigned int classID_) : systemId(systemID_), classID(classID_) {}

		SystemID systemId;
		ClassID classID;
	};

	template<class T>
	class System : public ISystem
	{
	public:
		static const ClassID classID;

		std::vector<EntityID> entities;
		
		System() { systemID = STATIC_ID_COUNTER++; }

		virtual void Init() {};
		virtual void Update(float dt) {};

		void RegisterEntity(const EntityID& entityID)
		{
			entities.push_back(entityID);
		}
		
		void UnregisterEntity(const EntityID& entityID)
		{
			for (unsigned int i = 0; i < entities.size(); i++)
			{
				if (entities[i] == entityID)
				{
					entities.erase(entities.begin() + i);
				}
			}

		}

	private:
		static SystemID STATIC_ID_COUNTER;

	};

	template<class T>
	const ClassID System<T>::classID = FamilyID<ISystem>::Get<T>();

	template<class T>
	SystemID System<T>::STATIC_ID_COUNTER = 0;
	
	
}