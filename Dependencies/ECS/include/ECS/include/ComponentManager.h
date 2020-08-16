#pragma once

#include <map>
#include "../../Memory/include/PoolAllocator.h"
#include <unordered_map>
#include "Component.h"
#include "Entity.h"



namespace ECS
{
	class IComponentCollection
	{
	public:
		using EntityComponentMap = std::map<EntityID, IComponent*>;
		//using ComponentEntityMap = std::map<ComponentID, IEntity*>;

		EntityComponentMap entityComponentMap;
		//ComponentEntityMap componentEntityMap;

		MemoryManager::PoolAllocator componentAllocator;

		IComponentCollection(size_t memsize, size_t objectsize) : componentAllocator(memsize, objectsize)
		{

		}

		~IComponentCollection()
		{
			for (auto it : entityComponentMap)
			{
				componentAllocator.Free(it.second);
			}

		}
	};

	class EntityComponentSystem;

	template<class T>
	class ComponentCollection : public IComponentCollection
	{
	private:
		
		EntityComponentSystem* ecsInstance;
	public:
		ComponentCollection(EntityComponentSystem* ecsInstance_) : IComponentCollection(sizeof(T) * 100, sizeof(T)) { ecsInstance = ecsInstance_; }

		static const ClassID classID;

		template<class T,class E, class... Args>
		ComponentHandle CreateComponent(EntityID entityID,Args... args)
		{
			T* component = MemoryManager::Allocate<T>(componentAllocator, std::forward<Args>(args)...);
			entityComponentMap[entityID] = component;
			//componentEntityMap[component->componentID] = ecsInstance->GetEntity<E>(eHandle);

			return ComponentHandle(component->componentID, component->classID);
		}

		template<class T>
		IComponent* GetComponent(const EntityID& entityID)
		{
			if (entityComponentMap.find(entityID) == entityComponentMap.end())
				return nullptr;

			return entityComponentMap[entityID];
		}

		template<class T>
		void DeleteComponent(const ComponentHandle& componentHandle, const EntityID& entityID)
		{
			T* component = static_cast<T*>(GetComponent<T>(entityID));
			entityComponentMap.erase(entityID);
			MemoryManager::Delete<T>(componentAllocator, component);
		}

	};

	template<class T>
	const ClassID ComponentCollection<T>::classID = FamilyID<IComponentCollection>::Get<T>();

	class ComponentManager
	{
	private:
		EntityComponentSystem* ecsInstance;
	public:
		ComponentManager(EntityComponentSystem* ecsInstance_) { ecsInstance = ecsInstance_; }

		using ComponentCollectionMap = std::unordered_map<ClassID, IComponentCollection*>;

		ComponentCollectionMap collectionMap;

		template<class T>
		ComponentCollection<T>* GetComponentCollection()
		{
			auto it = collectionMap.find(T::classID);
			ComponentCollection<T>* collection = nullptr;

			if (it == collectionMap.end())
			{
				collection = new ComponentCollection<T>(ecsInstance);
				collectionMap[T::classID] = collection;
			}
			else
			{
				collection = static_cast<ComponentCollection<T>*>(it->second);
			}

			return collection;
		}

	public:
		~ComponentManager()
		{
			for (auto it : collectionMap)
			{
				delete it.second;
			}

		}
	
		template<class T,class E,class... Args>
		ComponentHandle CreateComponent(EntityID entityID,Args... args)
		{
			ComponentCollection<T>* collection = GetComponentCollection<T>();
			return collection->CreateComponent<T,E>(entityID,std::forward<Args>(args)...);
		}

		template<class T>
		void DeleteComponent(const ComponentHandle& componentHandle, const EntityID& entityID)
		{
			ComponentCollection<T>* collection = GetComponentCollection<T>();
			collection->DeleteComponent<T>(componentHandle, entityID);
		}
		
		template<class T>
		IComponent* GetComponent(const EntityID& entityID)
		{
			ComponentCollection<T>* collection = GetComponentCollection<T>();
			return collection->GetComponent<T>(entityID);
		}

	};

	
}