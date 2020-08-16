#pragma once

#include "System.h"
#include "../../Memory/include/PoolAllocator.h"
#include <unordered_map>


namespace ECS
{
	class ISystemCollection
	{
	public:
		MemoryManager::PoolAllocator systemAllocator;
		using SystemMap = std::unordered_map<SystemID, ISystem*>;

		SystemMap systemMap;

		ISystemCollection(size_t memsize, size_t objectsize) : systemAllocator(memsize, objectsize)
		{

		}

		~ISystemCollection()
		{
			for (auto it : systemMap)
			{
				systemAllocator.Free(it.second);
			}
		}

		virtual void Init() = 0;
		virtual void Update(float dt) = 0;
		
	};

	template<class T>
	class SystemCollection : public ISystemCollection
	{
		
		

	public:
		SystemCollection() : ISystemCollection(sizeof(T) * 100, sizeof(T)) {}

		~SystemCollection()
		{
			
		}

		static const ClassID classID;

		template<class T, class... Args>
		SystemHandle CreateSystem(Args... args)
		{
			T* system = MemoryManager::Allocate<T>(systemAllocator, std::forward<Args>(args)...);

			systemMap[system->systemID] = system;

			return SystemHandle(system->systemID, system->classID);
		}

		template<class T>
		ISystem* GetSystem(const SystemID& systemID)
		{
			if (systemMap.find(systemID) == systemMap.end())
				return nullptr;

			return systemMap[systemID];
		}

		void Init()
		{
			for (auto it : systemMap)
			{
				it.second->Init();
			}
		}

		void Update(float dt)
		{
			for (auto it : systemMap)
			{
				it.second->Update(dt);
			}
		}

		

	};

	template<class T>
	const ClassID SystemCollection<T>::classID = FamilyID<ISystemCollection>::Get<T>();


	class SystemManager
	{

		using SystemCollectionMap = std::unordered_map<ClassID, ISystemCollection*>;

		SystemCollectionMap collectionMap;

		template<class T>
		SystemCollection<T>* GetSystemCollection()
		{
			auto it = collectionMap.find(T::classID);
			SystemCollection<T>* collection = nullptr;

			if (it == collectionMap.end())
			{
				collection = new SystemCollection<T>();
				collectionMap[T::classID] = collection;
			}
			else
			{
				collection = static_cast<SystemCollection<T>*>(it->second);
			}

			return collection;
		}



	public:
		~SystemManager()
		{
			for (auto it : collectionMap)
			{
				delete it.second;
			}

		}

		template<class T, class... Args>
		SystemHandle CreateSystem(Args... args)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();

			return collection->CreateSystem<T>(std::forward<Args>(args)...);
		}

		template<class T>
		ISystem* GetSystem(const SystemID& systemID)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();
			return collection->GetSystem<T>(systemID);
		}

		template<class T>
		void RegisterEntity(const SystemID& systemID,const EntityID& entityID)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();
			T* system =  (T*)collection->GetSystem<T>(systemID);

			system->RegisterEntity(entityID);
		}

		template<class T>
		void UnregisterEntity(const SystemID& systemID,const EntityID& entityID)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();
			T* system = (T*)collection->GetSystem<T>(systemID);

			system->UnregisterEntity(entityID);
		}

		void Init()
		{
			for (auto it : collectionMap)
			{
				it.second->Init();
			}
		}

		void Update(float dt)
		{
			for (auto it : collectionMap)
			{
				it.second->Update(dt);
			}
		}

	};
}

